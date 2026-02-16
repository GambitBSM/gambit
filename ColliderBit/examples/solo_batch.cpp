//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Batch execution and merge helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_batch.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <unistd.h>

#include "gambit/Utils/json.hpp"
#include "yaml-cpp/yaml.h"

#ifdef __cpp_lib_filesystem
  #include <filesystem>
  namespace fs = std::filesystem;
#else
  #include <boost/filesystem.hpp>
  namespace fs = boost::filesystem;
#endif

namespace Gambit
{
  namespace ColliderBit
  {
    // Implemented in ColliderBit/src/LHC_likelihoods.cpp.
    void calc_LHC_LogLikes_common(
      map_str_AnalysisLogLikes& result,
      bool use_fulllikes,
      AnalysisDataPointers& ana,
      const Options& runOptions,
      double (*marginaliser)(const int&, const double&, const double&, const double&),
      bool skip_calc,
      bool (*FullLikes_FileExists)(const str&),
      int (*FullLikes_ReadIn)(const str&, const str&, const str&),
      double (*FullLikes_Evaluate)(std::map<str,double>&,const str&),
      double xsec,
      int n_mc
    );

    namespace SoloBatch
    {
      namespace
      {
        struct RunJob
        {
          str process_name;
          str hepmc_file;
          double cross_section_fb = 0.0;
          double cross_section_uncert_fb = 0.0;
          fs::path yaml_file;
          fs::path output_json_file;
        };

        struct SRPayload
        {
          int sr_index = -1;
          std::string sr_label;
          double n_obs = 0.0;
          double n_bkg = 0.0;
          double n_bkg_err = 0.0;
          double n_sig_scaled = 0.0;
          double n_sig_scaled_err = 0.0;
        };

        struct AnalysisAccumulator
        {
          AnalysisData data;
          std::vector<double> n_sig_scaled_err2;
        };

        std::string shell_quote(const std::string& input)
        {
          std::string result = "'";
          for (char c : input)
          {
            if (c == '\'')
            {
              result += "'\"'\"'";
            }
            else
            {
              result.push_back(c);
            }
          }
          result += "'";
          return result;
        }

        void write_yaml_file(const YAML::Node& root, const fs::path& yaml_path)
        {
          YAML::Emitter out;
          out << root;
          std::ofstream ofs(yaml_path.string());
          if (!ofs)
          {
            throw std::runtime_error("Failed to write temporary YAML file: " + yaml_path.string());
          }
          ofs << out.c_str() << '\n';
        }

        nlohmann::json read_json_file(const fs::path& json_path)
        {
          std::ifstream ifs(json_path.string());
          if (!ifs)
          {
            throw std::runtime_error("Failed to open JSON output file: " + json_path.string());
          }

          nlohmann::json root;
          try
          {
            ifs >> root;
          }
          catch (const std::exception& e)
          {
            throw std::runtime_error("Failed to parse JSON output file " + json_path.string() + ": " + e.what());
          }
          return root;
        }

        std::vector<RunJob> build_run_jobs(
          const SoloInput::PreparedInput& prepared_input,
          const fs::path& temp_dir)
        {
          std::vector<RunJob> jobs;
          std::size_t run_index = 0;

          for (const SoloInput::ProcessInput& process : prepared_input.processes)
          {
            long long process_generated_events = 0;
            for (const SoloInput::HepMCFileInput& file : process.files)
            {
              process_generated_events += file.generated_events;
            }
            if (process_generated_events <= 0)
            {
              throw std::runtime_error("Invalid generated-events total for process " + process.name + ".");
            }

            for (const SoloInput::HepMCFileInput& file : process.files)
            {
              RunJob job;
              job.process_name = process.name;
              job.hepmc_file = file.filename;
              const double fraction =
                static_cast<double>(file.generated_events) / static_cast<double>(process_generated_events);
              job.cross_section_fb = process.cross_section_fb * fraction;
              job.cross_section_uncert_fb = process.cross_section_uncert_fb * fraction;

              std::ostringstream stem;
              stem << "run_" << run_index;
              job.yaml_file = temp_dir / (stem.str() + ".yaml");
              job.output_json_file = temp_dir / (stem.str() + ".json");

              jobs.push_back(job);
              ++run_index;
            }
          }

          if (jobs.empty())
          {
            throw std::runtime_error("No batch jobs were created from settings.processes.");
          }

          return jobs;
        }

        YAML::Node build_single_run_yaml(
          const SoloInput::PreparedInput& prepared_input,
          const Options& settings,
          const RunJob& job)
        {
          YAML::Node root;
          root["analyses"] = prepared_input.analyses;

          YAML::Node settings_node = YAML::Clone(prepared_input.infile["settings"]);
          settings_node.remove("processes");
          settings_node.remove("event_file");
          settings_node.remove("cross_section_fb");
          settings_node.remove("cross_section_pb");
          settings_node.remove("cross_section_uncert_fb");
          settings_node.remove("cross_section_uncert_pb");
          settings_node.remove("cross_section_fractional_uncert");
          settings_node.remove("output");

          settings_node["event_file"] = job.hepmc_file;
          settings_node["cross_section_fb"] = job.cross_section_fb;
          // Keep per-run xsec uncertainty off and combine MC errors externally.
          settings_node["cross_section_uncert_fb"] = 0.0;

          settings_node["screen_output"] = false;
          settings_node["output"] = job.output_json_file.string();
          settings_node["output_format"] = "json";
          settings_node["output_schema"] = "cbs-solo-loglike-v1";
          settings_node["output_json_indent"] = 0;

          root["settings"] = settings_node;

          if (prepared_input.infile["rivet-settings"] || prepared_input.infile["contur-settings"])
          {
            throw std::runtime_error("Batch mode does not support rivet-settings/contur-settings.");
          }

          (void) settings;
          return root;
        }

        void run_single_job(const std::string& cbs_executable, const fs::path& yaml_file)
        {
          const std::string cmd =
            shell_quote(cbs_executable) + " " + shell_quote(yaml_file.string());
          const int rc = std::system(cmd.c_str());
          if (rc != 0)
          {
            std::ostringstream msg;
            msg << "Batch run command failed with exit code " << rc
                << " for YAML file " << yaml_file.string() << ".";
            throw std::runtime_error(msg.str());
          }
        }

        std::vector<SRPayload> parse_sorted_sr_payloads(const nlohmann::json& analysis_json)
        {
          if (!analysis_json.contains("signal_regions"))
          {
            throw std::runtime_error("Missing signal_regions in a per-file JSON output.");
          }

          std::vector<SRPayload> payloads;
          for (const auto& sr_item : analysis_json.at("signal_regions").items())
          {
            const std::string sr_label = sr_item.key();
            const nlohmann::json& sr = sr_item.value();

            SRPayload payload;
            payload.sr_index = sr.at("sr_index").get<int>();
            payload.sr_label = sr_label;
            payload.n_obs = sr.at("n_obs").get<double>();
            payload.n_bkg = sr.at("n_bkg").get<double>();
            payload.n_bkg_err = sr.at("n_bkg_err").get<double>();
            payload.n_sig_scaled = sr.at("n_sig_scaled").get<double>();
            payload.n_sig_scaled_err = sr.at("n_sig_scaled_err").get<double>();
            payloads.push_back(payload);
          }

          std::sort(
            payloads.begin(),
            payloads.end(),
            [](const SRPayload& a, const SRPayload& b)
            {
              return a.sr_index < b.sr_index;
            });

          for (std::size_t i = 0; i < payloads.size(); ++i)
          {
            if (payloads[i].sr_index != static_cast<int>(i))
            {
              throw std::runtime_error("Signal-region indices in JSON output are not contiguous.");
            }
          }

          return payloads;
        }

        bool is_consistent(double a, double b, double tol = 1e-8)
        {
          const double scale = std::max({1.0, std::fabs(a), std::fabs(b)});
          return std::fabs(a - b) <= tol * scale;
        }

        Eigen::MatrixXd parse_covariance_matrix_or_empty(const nlohmann::json& analysis_json)
        {
          if (!analysis_json.contains("covariance"))
          {
            return Eigen::MatrixXd();
          }

          const nlohmann::json& cov_json = analysis_json.at("covariance");
          if (!cov_json.is_array())
          {
            throw std::runtime_error("covariance entry in JSON output must be a matrix.");
          }

          const int rows = static_cast<int>(cov_json.size());
          Eigen::MatrixXd cov(rows, rows);
          for (int i = 0; i < rows; ++i)
          {
            const nlohmann::json& row = cov_json.at(i);
            if (!row.is_array() || static_cast<int>(row.size()) != rows)
            {
              throw std::runtime_error("covariance matrix in JSON output must be square.");
            }
            for (int j = 0; j < rows; ++j)
            {
              cov(i, j) = row.at(j).get<double>();
            }
          }
          return cov;
        }

        void initialize_accumulator(
          AnalysisAccumulator& acc,
          const std::string& analysis_name,
          const nlohmann::json& analysis_json,
          const std::vector<SRPayload>& sr_payloads)
        {
          acc.data.analysis_name = analysis_name;
          acc.data.collider_name = "CBS";
          acc.data.luminosity = analysis_json.value("luminosity", 0.0);
          acc.data.bkgjson_path = analysis_json.value("bkgjson_path", std::string());
          acc.data.srcov = parse_covariance_matrix_or_empty(analysis_json);

          acc.data.srdata.clear();
          acc.data.srdata_identifiers.clear();
          acc.n_sig_scaled_err2.clear();
          acc.n_sig_scaled_err2.resize(sr_payloads.size(), 0.0);

          for (const SRPayload& payload : sr_payloads)
          {
            SignalRegionData sr(
              payload.sr_label,
              payload.n_obs,
              0.0,
              payload.n_bkg,
              0.0,
              payload.n_bkg_err,
              0.0);
            sr.n_sig_MC_stat = 0.0;

            acc.data.srdata.push_back(sr);
            acc.data.srdata_identifiers[payload.sr_label] = payload.sr_index;
          }
        }

        void validate_payload_consistency(
          const AnalysisAccumulator& acc,
          const std::string& analysis_name,
          const std::vector<SRPayload>& sr_payloads,
          const nlohmann::json& analysis_json)
        {
          if (acc.data.srdata.size() != sr_payloads.size())
          {
            throw std::runtime_error("Inconsistent number of signal regions for analysis " + analysis_name + ".");
          }

          const double lumi = analysis_json.value("luminosity", 0.0);
          if (!is_consistent(acc.data.luminosity, lumi))
          {
            throw std::runtime_error("Inconsistent analysis luminosity across batch runs for " + analysis_name + ".");
          }

          const std::string bkgjson_path = analysis_json.value("bkgjson_path", std::string());
          if (acc.data.bkgjson_path != bkgjson_path)
          {
            throw std::runtime_error("Inconsistent bkgjson_path across batch runs for " + analysis_name + ".");
          }

          for (std::size_t i = 0; i < sr_payloads.size(); ++i)
          {
            const SRPayload& payload = sr_payloads[i];
            const SignalRegionData& target = acc.data.srdata[i];

            if (target.sr_label != payload.sr_label)
            {
              throw std::runtime_error("Signal-region ordering mismatch in analysis " + analysis_name + ".");
            }
            if (!is_consistent(target.n_obs, payload.n_obs)
                || !is_consistent(target.n_bkg, payload.n_bkg)
                || !is_consistent(target.n_bkg_err, payload.n_bkg_err))
            {
              throw std::runtime_error("Observed/background data mismatch across runs in analysis " + analysis_name + ".");
            }
          }
        }

        double compute_combined_loglike(
          const map_str_AnalysisLogLikes& analysis_loglikes,
          const Options& settings)
        {
          const str alt_loglike_key = settings.getValueOrDef<str>("", "alt_loglike");
          const bool use_alt_loglike = !alt_loglike_key.empty();
          const std::vector<str> skip_analyses =
            settings.getValueOrDef<std::vector<str>>(std::vector<str>(), "skip_analyses");
          const bool cap_individual =
            settings.getValueOrDef<bool>(false, "cap_loglike_individual_analyses");
          const bool cap_total = settings.getValueOrDef<bool>(false, "cap_loglike");

          double result = 0.0;
          for (const auto& pair : analysis_loglikes)
          {
            const str& analysis_name = pair.first;
            const AnalysisLogLikes& loglikes = pair.second;

            if (std::find(skip_analyses.begin(), skip_analyses.end(), analysis_name) != skip_analyses.end())
            {
              continue;
            }

            double analysis_loglike = 0.0;
            if (use_alt_loglike)
            {
              auto it = loglikes.alt_combination_loglikes.find(alt_loglike_key);
              if (it == loglikes.alt_combination_loglikes.end())
              {
                throw std::runtime_error(
                  "Unknown alt_loglike key '" + alt_loglike_key + "' while combining analyses.");
              }
              analysis_loglike = it->second;
            }
            else
            {
              analysis_loglike = loglikes.combination_loglike;
            }

            result += cap_individual ? std::min(analysis_loglike, 0.0) : analysis_loglike;
          }

          if (cap_total)
          {
            result = std::min(result, 0.0);
          }
          return result;
        }

        fs::path make_temp_dir()
        {
          const auto timestamp =
            std::chrono::high_resolution_clock::now().time_since_epoch().count();
          std::ostringstream name;
          name << "cbs_batch_" << static_cast<long long>(::getpid()) << "_" << timestamp;

          fs::path temp_dir = fs::temp_directory_path() / name.str();
          fs::create_directories(temp_dir);
          return temp_dir;
        }
      } // namespace

      MergedRunResult run_and_merge(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      )
      {
        if (prepared_input.processes.empty())
        {
          throw std::runtime_error("Batch mode requested, but no processes were found in input.");
        }

        const bool keep_temp = settings.getValueOrDef<bool>(false, "keep_batch_tmp");
        const fs::path temp_dir = make_temp_dir();

        std::vector<RunJob> jobs = build_run_jobs(prepared_input, temp_dir);
        std::map<std::string, AnalysisAccumulator> accumulators;
        int total_events = 0;

        for (const RunJob& job : jobs)
        {
          YAML::Node run_yaml = build_single_run_yaml(prepared_input, settings, job);
          write_yaml_file(run_yaml, job.yaml_file);
          run_single_job(cbs_executable, job.yaml_file);

          const nlohmann::json run_json = read_json_file(job.output_json_file);
          const int n_events = run_json.at("run").at("n_events").get<int>();
          total_events += n_events;

          const nlohmann::json& analyses_json = run_json.at("analyses");
          for (const auto& analysis_item : analyses_json.items())
          {
            const std::string analysis_name = analysis_item.key();
            const nlohmann::json& analysis_json = analysis_item.value();
            const std::vector<SRPayload> sr_payloads = parse_sorted_sr_payloads(analysis_json);

            AnalysisAccumulator& acc = accumulators[analysis_name];
            if (acc.data.srdata.empty())
            {
              initialize_accumulator(acc, analysis_name, analysis_json, sr_payloads);
            }
            else
            {
              validate_payload_consistency(acc, analysis_name, sr_payloads, analysis_json);
            }

            for (std::size_t i = 0; i < sr_payloads.size(); ++i)
            {
              const SRPayload& payload = sr_payloads[i];
              acc.data.srdata[i].n_sig_scaled += payload.n_sig_scaled;
              acc.n_sig_scaled_err2[i] += payload.n_sig_scaled_err * payload.n_sig_scaled_err;
            }
          }
        }

        if (total_events <= 0)
        {
          throw std::runtime_error("Batch mode produced zero processed events.");
        }

        MergedRunResult merged;
        merged.total_events = total_events;

        // Preserve user-requested analysis ordering where possible.
        std::vector<std::string> analysis_order;
        for (const str& name : prepared_input.analyses)
        {
          if (accumulators.count(name) != 0) analysis_order.push_back(name);
        }
        for (const auto& pair : accumulators)
        {
          if (std::find(analysis_order.begin(), analysis_order.end(), pair.first) == analysis_order.end())
          {
            analysis_order.push_back(pair.first);
          }
        }

        merged.analyses_storage.reserve(analysis_order.size());
        for (const std::string& analysis_name : analysis_order)
        {
          AnalysisAccumulator& acc = accumulators.at(analysis_name);
          AnalysisData data = acc.data;

          for (std::size_t sr_index = 0; sr_index < data.srdata.size(); ++sr_index)
          {
            SignalRegionData& sr = data.srdata[sr_index];
            const double scaled_err = std::sqrt(acc.n_sig_scaled_err2[sr_index]);

            if (prepared_input.total_cross_section_fb > 0.0 && data.luminosity > 0.0)
            {
              const double scale =
                static_cast<double>(merged.total_events)
                / (data.luminosity * prepared_input.total_cross_section_fb);

              sr.n_sig_MC = sr.n_sig_scaled * scale;
              sr.n_sig_MC_stat = scaled_err * scale;
              sr.n_sig_MC_sys = 0.0;
            }
            else
            {
              sr.n_sig_MC = 0.0;
              sr.n_sig_MC_stat = 0.0;
              sr.n_sig_MC_sys = 0.0;
            }
          }

          merged.analyses_storage.push_back(std::move(data));
        }

        for (AnalysisData& analysis_data : merged.analyses_storage)
        {
          merged.analyses.push_back(&analysis_data);
        }

        Options loglike_options = settings;
        loglike_options.setValue(
          "poisson_like_estimator",
          settings.getValueOrDef<std::string>("MLE", "poisson_like_estimator"));

        const bool skip_calc = false;
        const bool use_fulllikes = true;
        calc_LHC_LogLikes_common(
          merged.analysis_loglikes,
          use_fulllikes,
          merged.analyses,
          loglike_options,
          marginaliser,
          skip_calc,
          FullLikes_FileExists,
          FullLikes_ReadIn,
          FullLikes_Evaluate,
          prepared_input.total_cross_section_fb,
          merged.total_events);

        merged.combined_loglike = compute_combined_loglike(merged.analysis_loglikes, settings);

        if (!keep_temp)
        {
          fs::remove_all(temp_dir);
        }

        return merged;
      }
    } // namespace SoloBatch
  }   // namespace ColliderBit
} // namespace Gambit

