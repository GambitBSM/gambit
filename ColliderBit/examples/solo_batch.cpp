//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Batch execution and merge helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_batch.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <sys/wait.h>
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

        struct CompletedRun
        {
          RunJob job;
          int n_events = 0;
          nlohmann::json analyses_json;
        };

        std::string describe_child_status(int status)
        {
          std::ostringstream msg;
          if (WIFEXITED(status))
          {
            msg << "exit status " << WEXITSTATUS(status);
          }
          else if (WIFSIGNALED(status))
          {
            const int signal_number = WTERMSIG(status);
            msg << "signal " << signal_number;
#ifdef WCOREDUMP
            if (WCOREDUMP(status)) msg << " (core dumped)";
#endif
          }
          else if (WIFSTOPPED(status))
          {
            msg << "stopped by signal " << WSTOPSIG(status);
          }
          else
          {
            msg << "unrecognised wait status " << status;
          }
          return msg.str();
        }

        std::string describe_output_json(const fs::path& output_json_file)
        {
          std::ostringstream msg;
          msg << output_json_file.string() << " (";
          try
          {
            if (fs::exists(output_json_file))
            {
              msg << "exists, " << fs::file_size(output_json_file) << " bytes";
            }
            else
            {
              msg << "missing";
            }
          }
          catch (const std::exception& e)
          {
            msg << "status unavailable: " << e.what();
          }
          msg << ")";
          return msg.str();
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
            for (const SoloInput::HepMCFileInput& file : process.files)
            {
              RunJob job;
              job.process_name = process.name;
              job.hepmc_file = file.filename;
              // Use full process cross section for each file, then combine files
              // for the same process with event-count weighting after runs finish.
              job.cross_section_fb = process.cross_section_fb;
              job.cross_section_uncert_fb = process.cross_section_uncert_fb;

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
          // Suppress repeated FastJet banners from per-file subprocesses.
          settings_node["suppress_fastjet_banner"] = true;

          root["settings"] = settings_node;

          if (prepared_input.infile["rivet-settings"] || prepared_input.infile["contur-settings"])
          {
            throw std::runtime_error("Batch mode does not support rivet-settings/contur-settings.");
          }

          (void) settings;
          return root;
        }

        void run_single_job(const std::string& cbs_executable, const RunJob& job)
        {
          const fs::path& yaml_file = job.yaml_file;
          std::string executable = cbs_executable;
          try
          {
            const fs::path executable_path(cbs_executable);
            if (executable_path.has_parent_path())
            {
              executable = fs::absolute(executable_path).string();
            }
          }
          catch (const std::exception&)
          {
            // Fall back to argv[0]; execvp below will report any real failure.
          }

          const std::string yaml_filename = yaml_file.string();
          const pid_t pid = fork();
          if (pid < 0)
          {
            throw std::runtime_error("Failed to fork CBS batch subprocess: " + std::string(std::strerror(errno)));
          }

          if (pid == 0)
          {
            setenv("GAMBIT_SUPPRESS_BANNER", "1", 1);
            setenv("CBS_SUPPRESS_BANNER", "1", 1);

            char* const argv[] = {
              const_cast<char*>(executable.c_str()),
              const_cast<char*>(yaml_filename.c_str()),
              nullptr
            };
            execvp(executable.c_str(), argv);

            std::ostringstream msg;
            msg << "Failed to exec CBS batch subprocess '" << executable
                << "' for YAML file " << yaml_filename << ": "
                << std::strerror(errno) << '\n';
            const std::string text = msg.str();
            (void) write(STDERR_FILENO, text.c_str(), text.size());
            _exit(127);
          }

          int status = 0;
          pid_t wait_result = 0;
          do
          {
            wait_result = waitpid(pid, &status, 0);
          } while (wait_result < 0 && errno == EINTR);

          if (wait_result < 0)
          {
            throw std::runtime_error("Failed to wait for CBS batch subprocess: " + std::string(std::strerror(errno)));
          }

          if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
          {
            std::ostringstream msg;
            msg << "Batch run command failed with " << describe_child_status(status)
                << " for YAML file " << yaml_filename
                << ". Output JSON: " << describe_output_json(job.output_json_file)
                << ". Command: GAMBIT_SUPPRESS_BANNER=1 CBS_SUPPRESS_BANNER=1 "
                << executable << " " << yaml_filename << ".";
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

        Cutflows parse_cutflows_or_empty(const nlohmann::json& analysis_json)
        {
          Cutflows cutflows;
          if (!analysis_json.contains("cutflows"))
          {
            return cutflows;
          }

          const nlohmann::json& cutflows_json = analysis_json.at("cutflows");
          if (!cutflows_json.is_array())
          {
            throw std::runtime_error("cutflows entry in JSON output must be an array.");
          }

          for (const nlohmann::json& cf_json : cutflows_json)
          {
            if (!cf_json.is_object())
            {
              throw std::runtime_error("Each cutflow entry in JSON output must be an object.");
            }

            const std::string cf_name = cf_json.value("name", std::string());
            if (cf_name.empty())
            {
              throw std::runtime_error("Cutflow entry in JSON output is missing a non-empty name.");
            }

            if (!cf_json.contains("cuts") || !cf_json.at("cuts").is_array())
            {
              throw std::runtime_error("Cutflow '" + cf_name + "' has invalid/missing cuts array in JSON output.");
            }

            const nlohmann::json& cuts_json = cf_json.at("cuts");
            if (cuts_json.empty())
            {
              throw std::runtime_error("Cutflow '" + cf_name + "' has an empty cuts array in JSON output.");
            }

            std::vector<std::string> cut_names;
            cut_names.reserve(cuts_json.size() - 1);
            std::vector<double> counts;
            counts.reserve(cuts_json.size());

            for (std::size_t i = 0; i < cuts_json.size(); ++i)
            {
              const nlohmann::json& cut_json = cuts_json.at(i);
              if (!cut_json.is_object() || !cut_json.contains("count"))
              {
                throw std::runtime_error(
                  "Cutflow '" + cf_name + "' has invalid cut entry in JSON output.");
              }

              counts.push_back(cut_json.at("count").get<double>());

              if (i > 0)
              {
                const std::string cut_name = cut_json.value("cut_name", std::string());
                cut_names.push_back(cut_name.empty() ? ("cut_" + std::to_string(i)) : cut_name);
              }
            }

            Cutflow cf(cf_name, cut_names);
            cf.counts = counts;
            cutflows.addCutflow(cf);
          }

          return cutflows;
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
          const std::vector<SRPayload>& sr_payloads,
          const Cutflows& cutflows)
        {
          acc.data.analysis_name = analysis_name;
          acc.data.collider_name = "CBS";
          acc.data.luminosity = analysis_json.value("luminosity", 0.0);
          acc.data.bkgjson_path = analysis_json.value("bkgjson_path", std::string());
          acc.data.srcov = parse_covariance_matrix_or_empty(analysis_json);
          acc.data.cutflows = cutflows;

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

        void accumulate_cutflows(
          Cutflows& target,
          const Cutflows& incoming,
          const std::string& analysis_name)
        {
          if (incoming.cfs.empty()) return;

          if (target.cfs.empty())
          {
            target = incoming;
            return;
          }

          if (target.cfs.size() != incoming.cfs.size())
          {
            throw std::runtime_error(
              "Inconsistent number of cutflows across batch runs for analysis " + analysis_name + ".");
          }

          for (std::size_t i = 0; i < target.cfs.size(); ++i)
          {
            Cutflow& dst = target.cfs[i];
            const Cutflow& src = incoming.cfs[i];

            if (dst.name != src.name || dst.cuts != src.cuts || dst.counts.size() != src.counts.size())
            {
              throw std::runtime_error(
                "Inconsistent cutflow structure across batch runs for analysis " + analysis_name + ".");
            }

            for (std::size_t j = 0; j < dst.counts.size(); ++j)
            {
              dst.counts[j] += src.counts[j];
            }
          }
        }

        Histograms parse_histograms_or_empty(const nlohmann::json& analysis_json)
        {
          Histograms histograms;
          if (!analysis_json.contains("histograms")) return histograms;

          const nlohmann::json& histo_json = analysis_json.at("histograms");

          // Parse 1D histograms
          if (histo_json.contains("1d") && histo_json.at("1d").is_array())
          {
            for (const auto& h_json : histo_json.at("1d"))
            {
              std::string hname = h_json.at("name").get<std::string>();
              std::vector<double> hedges = h_json.at("edges").get<std::vector<double>>();
              std::string xlabel = h_json.value("x_label", std::string());

              Histogram1D h(hname, hedges, xlabel);
              const auto& bins = h_json.at("bins");
              for (std::size_t i = 0; i < bins.size() && i < h.nbins(); ++i)
              {
                h.counts[i] = bins[i].at("count").get<double>();
                h.sumw2[i] = bins[i].at("sumw2").get<double>();
              }
              if (h_json.value("is_signal_region", false))
              {
                if (h_json.contains("obs") && h_json.contains("bkg") && h_json.contains("bkg_err"))
                {
                  h.set_signal_region_data(
                    h_json.at("obs").get<std::vector<double>>(),
                    h_json.at("bkg").get<std::vector<double>>(),
                    h_json.at("bkg_err").get<std::vector<double>>());
                }
                else
                {
                  std::vector<double> obs;
                  std::vector<double> bkg;
                  std::vector<double> bkg_err;
                  obs.reserve(h.nbins());
                  bkg.reserve(h.nbins());
                  bkg_err.reserve(h.nbins());
                  for (std::size_t i = 0; i < bins.size() && i < h.nbins(); ++i)
                  {
                    obs.push_back(bins[i].at("n_obs").get<double>());
                    bkg.push_back(bins[i].at("n_bkg").get<double>());
                    bkg_err.push_back(bins[i].at("n_bkg_err").get<double>());
                  }
                  h.set_signal_region_data(obs, bkg, bkg_err);
                }
              }
              h.underflow = h_json.value("underflow", 0.0);
              h.overflow = h_json.value("overflow", 0.0);
              double uf_err = h_json.value("underflow_error", 0.0);
              double of_err = h_json.value("overflow_error", 0.0);
              h.underflow_sumw2 = uf_err * uf_err;
              h.overflow_sumw2 = of_err * of_err;

              histograms.addHistogram(h);
            }
          }

          // Parse 2D histograms
          if (histo_json.contains("2d") && histo_json.at("2d").is_array())
          {
            for (const auto& h_json : histo_json.at("2d"))
            {
              std::string hname = h_json.at("name").get<std::string>();
              auto xedges = h_json.at("x_edges").get<std::vector<double>>();
              auto yedges = h_json.at("y_edges").get<std::vector<double>>();
              std::string xlabel = h_json.value("x_label", std::string());
              std::string ylabel = h_json.value("y_label", std::string());

              Histogram2D h(hname, xedges, yedges, xlabel, ylabel);
              const auto& counts_2d = h_json.at("counts");
              const auto& sumw2_2d = h_json.at("sumw2");
              for (std::size_t ix = 0; ix < h.nx_bins() && ix < counts_2d.size(); ++ix)
              {
                for (std::size_t iy = 0; iy < h.ny_bins() && iy < counts_2d[ix].size(); ++iy)
                {
                  h.counts[ix][iy] = counts_2d[ix][iy].get<double>();
                  h.sumw2[ix][iy] = sumw2_2d[ix][iy].get<double>();
                }
              }
              h.overflow_total = h_json.value("overflow_total", 0.0);
              double of_err = h_json.value("overflow_total_error", 0.0);
              h.overflow_total_sumw2 = of_err * of_err;

              histograms.addHistogram(h);
            }
          }

          return histograms;
        }

        void accumulate_histograms(
          Histograms& target,
          const Histograms& incoming,
          const std::string& analysis_name)
        {
          if (incoming.histos1d.empty() && incoming.histos2d.empty()) return;

          if (target.histos1d.empty() && target.histos2d.empty())
          {
            target = incoming;
            return;
          }

          if (target.histos1d.size() != incoming.histos1d.size() ||
              target.histos2d.size() != incoming.histos2d.size())
          {
            throw std::runtime_error(
              "Inconsistent number of histograms across batch runs for analysis " + analysis_name + ".");
          }

          target.combine(incoming);
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
        std::map<std::string, long long> process_event_totals;
        std::vector<CompletedRun> completed_runs;
        completed_runs.reserve(jobs.size());
        int total_events = 0;

        for (const RunJob& job : jobs)
        {
          YAML::Node run_yaml = build_single_run_yaml(prepared_input, settings, job);
          write_yaml_file(run_yaml, job.yaml_file);
          run_single_job(cbs_executable, job);

          const nlohmann::json run_json = read_json_file(job.output_json_file);
          const int n_events = run_json.at("run").at("n_events").get<int>();
          if (n_events <= 0)
          {
            throw std::runtime_error("A per-file CBS run produced zero events for " + job.hepmc_file + ".");
          }
          total_events += n_events;
          process_event_totals[job.process_name] += n_events;

          CompletedRun completed;
          completed.job = job;
          completed.n_events = n_events;
          completed.analyses_json = run_json.at("analyses");
          completed_runs.push_back(std::move(completed));
        }

        if (total_events <= 0)
        {
          throw std::runtime_error("Batch mode produced zero processed events.");
        }

        // Process-file combination rule:
        // for files belonging to the same process, combine with event-count weights.
        for (const CompletedRun& completed : completed_runs)
        {
          auto it_total = process_event_totals.find(completed.job.process_name);
          if (it_total == process_event_totals.end() || it_total->second <= 0)
          {
            throw std::runtime_error("Missing process event total for process " + completed.job.process_name + ".");
          }
          const double process_weight =
            static_cast<double>(completed.n_events) / static_cast<double>(it_total->second);

          for (const auto& analysis_item : completed.analyses_json.items())
          {
            const std::string analysis_name = analysis_item.key();
            const nlohmann::json& analysis_json = analysis_item.value();
            const std::vector<SRPayload> sr_payloads = parse_sorted_sr_payloads(analysis_json);
            const Cutflows file_cutflows = parse_cutflows_or_empty(analysis_json);
            const Histograms file_histograms = parse_histograms_or_empty(analysis_json);
            Histograms weighted_histograms = file_histograms;
            weighted_histograms.scale(process_weight);

            AnalysisAccumulator& acc = accumulators[analysis_name];
            if (acc.data.srdata.empty())
            {
              initialize_accumulator(acc, analysis_name, analysis_json, sr_payloads, file_cutflows);
              acc.data.histograms = weighted_histograms;
            }
            else
            {
              validate_payload_consistency(acc, analysis_name, sr_payloads, analysis_json);
              accumulate_cutflows(acc.data.cutflows, file_cutflows, analysis_name);
              accumulate_histograms(acc.data.histograms, weighted_histograms, analysis_name);
            }

            for (std::size_t i = 0; i < sr_payloads.size(); ++i)
            {
              const SRPayload& payload = sr_payloads[i];
              acc.data.srdata[i].n_sig_scaled += process_weight * payload.n_sig_scaled;
              acc.n_sig_scaled_err2[i] += std::pow(process_weight * payload.n_sig_scaled_err, 2);
            }
          }
        }

        MergedRunResult merged;
        merged.total_events = total_events;
        merged.total_process_events = total_events;
        merged.process_event_counts = process_event_totals;

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

      std::vector<AnalysisSamplingAdvice> build_sampling_advice(
        const MergedRunResult& merged,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings
      )
      {
        std::vector<AnalysisSamplingAdvice> advice;
        if (prepared_input.processes.empty()) return advice;

        std::vector<double> targets;
        if (settings.hasKey("sampling_advice_targets"))
        {
          targets = settings.getValue<std::vector<double>>("sampling_advice_targets");
        }
        else
        {
          targets.push_back(settings.getValueOrDef<double>(0.30, "target_fractional_uncert"));
          targets.push_back(0.10);
          targets.push_back(0.05);
        }

        std::vector<double> clean_targets;
        for (double target : targets)
        {
          if (!(target > 0.0) || !std::isfinite(target)) continue;
          bool duplicate = false;
          for (double existing : clean_targets)
          {
            if (std::fabs(existing - target) <= 1e-12 * std::max(1.0, std::fabs(existing)))
            {
              duplicate = true;
              break;
            }
          }
          if (!duplicate) clean_targets.push_back(target);
        }
        if (clean_targets.empty())
        {
          clean_targets.push_back(0.30);
        }

        std::vector<ProcessSamplingAdvice> process_templates;
        process_templates.reserve(prepared_input.processes.size());
        long long total_processed_events = merged.total_process_events;
        double total_cross_section_fb = 0.0;

        for (const SoloInput::ProcessInput& process : prepared_input.processes)
        {
          ProcessSamplingAdvice process_info;
          process_info.process_name = process.name;
          process_info.cross_section_fb = process.cross_section_fb;
          const auto it = merged.process_event_counts.find(process.name);
          process_info.processed_events = (it == merged.process_event_counts.end() ? 0 : it->second);
          process_info.recommended_additional_events = 0;
          total_cross_section_fb += std::max(0.0, process_info.cross_section_fb);
          process_templates.push_back(process_info);
        }

        if (total_processed_events <= 0)
        {
          return advice;
        }

        for (const AnalysisData* analysis_ptr : merged.analyses)
        {
          if (analysis_ptr == nullptr) continue;
          const AnalysisData& analysis = *analysis_ptr;

          const auto ll_it = merged.analysis_loglikes.find(analysis.analysis_name);
          if (ll_it == merged.analysis_loglikes.end()) continue;

          const AnalysisLogLikes& loglikes = ll_it->second;
          const int sr_index = loglikes.combination_sr_index;
          if (sr_index < 0 || sr_index >= static_cast<int>(analysis.size())) continue;

          const SignalRegionData& sr_data = analysis[sr_index];
          const double signal = sr_data.n_sig_scaled;
          const double signal_err = sr_data.calc_n_sig_scaled_err();

          AnalysisSamplingAdvice analysis_advice;
          analysis_advice.analysis_name = analysis.analysis_name;
          analysis_advice.sr_label = sr_data.sr_label;
          analysis_advice.sr_index = sr_index;
          analysis_advice.n_sig_scaled = signal;
          analysis_advice.n_sig_scaled_err = signal_err;

          if (signal > 0.0 && signal_err > 0.0 && std::isfinite(signal_err))
          {
            analysis_advice.fractional_uncert = signal_err / signal;
            analysis_advice.effective_events = std::pow(signal / signal_err, 2);
          }
          else if (signal > 0.0 && signal_err == 0.0)
          {
            analysis_advice.fractional_uncert = 0.0;
            analysis_advice.effective_events = std::numeric_limits<double>::infinity();
          }
          else
          {
            analysis_advice.fractional_uncert = std::numeric_limits<double>::infinity();
            analysis_advice.effective_events = 0.0;
          }

          for (double target : clean_targets)
          {
            SamplingTargetAdvice target_advice;
            target_advice.target_fractional_uncert = target;
            target_advice.current_fractional_uncert = analysis_advice.fractional_uncert;
            target_advice.current_total_events = total_processed_events;
            target_advice.recommended_total_events = total_processed_events;
            target_advice.scale_factor = 1.0;
            target_advice.need_more_mc = false;
            target_advice.recommended_additional_events = 0;
            target_advice.process_recommendations = process_templates;

            if (signal > 0.0 && signal_err > 0.0 && std::isfinite(analysis_advice.fractional_uncert))
            {
              const double factor =
                std::pow(analysis_advice.fractional_uncert / target, 2);
              target_advice.scale_factor = std::max(1.0, factor);

              const double rec_total_events_real =
                static_cast<double>(total_processed_events) * target_advice.scale_factor;
              const double rec_total_events_ceiled = std::ceil(rec_total_events_real);

              if (rec_total_events_ceiled > static_cast<double>(std::numeric_limits<long long>::max()))
              {
                target_advice.recommended_total_events = std::numeric_limits<long long>::max();
              }
              else
              {
                target_advice.recommended_total_events =
                  static_cast<long long>(rec_total_events_ceiled);
              }

              target_advice.recommended_additional_events =
                std::max<long long>(0, target_advice.recommended_total_events - total_processed_events);
              target_advice.need_more_mc = (target_advice.recommended_additional_events > 0);
            }

            if (target_advice.recommended_additional_events > 0
                && !target_advice.process_recommendations.empty())
            {
              std::vector<long long> base_alloc(
                target_advice.process_recommendations.size(), 0);
              std::vector<double> fractional_part(
                target_advice.process_recommendations.size(), 0.0);
              std::vector<double> share(
                target_advice.process_recommendations.size(), 0.0);

              if (total_cross_section_fb > 0.0)
              {
                for (std::size_t ip = 0; ip < target_advice.process_recommendations.size(); ++ip)
                {
                  share[ip] =
                    std::max(0.0, target_advice.process_recommendations[ip].cross_section_fb)
                    / total_cross_section_fb;
                }
              }
              else
              {
                for (std::size_t ip = 0; ip < target_advice.process_recommendations.size(); ++ip)
                {
                  share[ip] =
                    static_cast<double>(target_advice.process_recommendations[ip].processed_events)
                    / static_cast<double>(total_processed_events);
                }
              }

              const double share_sum =
                std::accumulate(share.begin(), share.end(), 0.0);
              if (share_sum > 0.0)
              {
                for (double& x : share) x /= share_sum;
              }
              else
              {
                const double uniform_share =
                  1.0 / static_cast<double>(share.size());
                for (double& x : share) x = uniform_share;
              }

              long long allocated = 0;
              for (std::size_t ip = 0; ip < target_advice.process_recommendations.size(); ++ip)
              {
                const double exact =
                  static_cast<double>(target_advice.recommended_additional_events) * share[ip];
                const long long rounded_down = static_cast<long long>(std::floor(exact));
                base_alloc[ip] = rounded_down;
                fractional_part[ip] = exact - rounded_down;
                allocated += rounded_down;
              }

              long long remainder = target_advice.recommended_additional_events - allocated;
              std::vector<std::size_t> order(target_advice.process_recommendations.size());
              std::iota(order.begin(), order.end(), 0);
              std::sort(
                order.begin(),
                order.end(),
                [&](std::size_t a, std::size_t b)
                {
                  return fractional_part[a] > fractional_part[b];
                });

              for (long long k = 0; k < remainder; ++k)
              {
                const std::size_t idx =
                  order[static_cast<std::size_t>(k) % order.size()];
                base_alloc[idx] += 1;
              }

              for (std::size_t ip = 0; ip < target_advice.process_recommendations.size(); ++ip)
              {
                target_advice.process_recommendations[ip].recommended_additional_events =
                  base_alloc[ip];
              }
            }

            analysis_advice.targets.push_back(std::move(target_advice));
          }

          advice.push_back(std::move(analysis_advice));
        }

        return advice;
      }
    } // namespace SoloBatch
  }   // namespace ColliderBit
} // namespace Gambit
