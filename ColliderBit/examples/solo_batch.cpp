//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Batch execution and merge helpers for ColliderBit Solo (CBS).
///  Local single-point recasting: run each HepMC file in a fresh CBS process,
///  wait for it to finish, then merge the per-file results. This execution
///  path does not provide scheduler-managed HPC batch support.
///
///  *********************************************

#include "solo_batch.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <fcntl.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>

#include <nlohmann/json.hpp>
#include "yaml-cpp/yaml.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace Gambit
{
  namespace ColliderBit
  {
    /// Recalculate likelihoods from merged analysis yields using the shared
    /// implementation in ColliderBit/src/LHC_likelihoods.cpp.
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
        /// One HepMC file, its physics-process normalisation and temporary I/O paths,
        /// with the collider it belongs to and the analyses assigned to that collider.
        struct RunJob
        {
          std::size_t process_index = 0;
          str process_name;
          str collider_name;
          std::vector<str> analyses;
          str hepmc_file;
          std::size_t file_index = 0;
          std::size_t file_count = 0;
          double cross_section_fb = 0.0;
          double cross_section_uncert_fb = 0.0;
          fs::path yaml_file;
          fs::path output_json_file;
        };

        /// One signal region read from a child run, including its scaled signal error.
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

        /// Shared analysis metadata and merged yields, with signal variances kept
        /// separately so independent per-file MC errors can be added in quadrature.
        struct AnalysisAccumulator
        {
          AnalysisData data;
          std::vector<double> n_sig_scaled_err2;
        };

        /// A child's result retained until the total event count of its process is known.
        struct CompletedRun
        {
          RunJob job;
          int n_events = 0;
          nlohmann::json analyses_json;
        };

        /// Translate a waitpid status into an exit-code or signal diagnostic.
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

        /// Describe a child's expected JSON file for a subprocess-failure message.
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

        /// Serialise one child's temporary CBS input, reporting file-open failures.
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

        /// Read a child's JSON result and include the path in I/O or parse errors.
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

        /// Expand physics-process inputs into per-file jobs with distinct output paths.
        /// Each job uses its full process cross section; file weights are applied later.
        /// Files of colliders without any enabled analysis are not run.
        std::vector<RunJob> build_run_jobs(
          const SoloInput::PreparedInput& prepared_input,
          const fs::path& temp_dir)
        {
          std::vector<RunJob> jobs;
          std::size_t run_index = 0;
          std::size_t file_count = 0;
          for (const SoloInput::ProcessInput& process : prepared_input.processes)
          {
            if (!SoloInput::find_collider(prepared_input, process.collider_name).analyses.empty())
            {
              file_count += process.files.size();
            }
          }
          std::size_t file_index = 0;

          for (std::size_t ip = 0; ip < prepared_input.processes.size(); ++ip)
          {
            const SoloInput::ProcessInput& process = prepared_input.processes[ip];
            const SoloInput::ColliderInput& collider =
              SoloInput::find_collider(prepared_input, process.collider_name);
            if (collider.analyses.empty()) continue;

            for (const SoloInput::HepMCFileInput& file : process.files)
            {
              RunJob job;
              job.process_index = ip;
              job.process_name = process.name;
              job.collider_name = collider.name;
              job.analyses = collider.analyses;
              job.hepmc_file = file.filename;
              job.file_index = ++file_index;
              job.file_count = file_count;
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

        /// Clone resolved settings into one event_file input with private JSON output.
        /// Remove batch settings to avoid recursion and disable per-run cross-section
        /// uncertainty so the merge accumulates MC errors from the child results.
        YAML::Node build_single_run_yaml(
          const SoloInput::PreparedInput& prepared_input,
          const Options& settings,
          const RunJob& job)
        {
          YAML::Node root;
          root["analyses"] = job.analyses;

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
          settings_node["cbs_collider_name"] = job.collider_name;
          settings_node["cross_section_fb"] = job.cross_section_fb;
          // Keep per-run xsec uncertainty off and combine MC errors externally.
          settings_node["cross_section_uncert_fb"] = 0.0;

          // Keep the parent run's live HepMC progress setting even though the
          // child suppresses its normal summary output.
          settings_node["hepmc_progress"] = settings.getValueOrDef<bool>(
            settings.getValueOrDef<bool>(true, "screen_output"), "hepmc_progress"
          );
          std::ostringstream progress_label;
          progress_label << "CBS HepMC File " << job.file_index << "/" << job.file_count
                         << " (" << job.collider_name << ")";
          settings_node["event_progress_label"] = progress_label.str();
          settings_node["screen_output"] = false;
          settings_node["output"] = job.output_json_file.string();
          root["settings"] = settings_node;

          if (prepared_input.infile["rivet-settings"] || prepared_input.infile["contur-settings"])
          {
            throw std::runtime_error("Batch mode does not support rivet-settings/contur-settings.");
          }

          (void) settings;
          return root;
        }

        /// Fork and exec one local CBS run, then wait for completion before returning.
        /// The fresh process isolates per-file state; a failed child aborts the batch.
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
                << ". Command: CBS_SUPPRESS_BANNER=1 "
                << executable << " " << yaml_filename << ".";
            throw std::runtime_error(msg.str());
          }
        }

        /// Restore signal regions in numeric index order and require contiguous indices.
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

        /// Reconstruct optional cutflows, with the first count representing input events.
        /// Missing cutflows give an empty collection; malformed entries are rejected.
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

        /// Compare metadata numbers using relative tolerance with a unit absolute floor.
        bool is_consistent(double a, double b, double tol = 1e-8)
        {
          const double scale = std::max({1.0, std::fabs(a), std::fabs(b)});
          return std::fabs(a - b) <= tol * scale;
        }

        /// Restore a square covariance matrix, or return an empty matrix if absent.
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

        /// Seed metadata, background data and cutflows from the first file, and
        /// initialise zero signal yields and variances for subsequent accumulation.
        void initialize_accumulator(
          AnalysisAccumulator& acc,
          const std::string& analysis_name,
          const std::string& collider_name,
          const nlohmann::json& analysis_json,
          const std::vector<SRPayload>& sr_payloads,
          const Cutflows& cutflows)
        {
          acc.data.analysis_name = analysis_name;
          acc.data.collider_name = collider_name;
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

        /// Require subsequent files to match SR ordering, observed/background data,
        /// luminosity and the background-likelihood path before adding their signals.
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

        /// Add raw cutflow counts after checking matching names and cut structure.
        /// These diagnostic counts are not weighted by process cross sections.
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

        /// Reconstruct optional 1D/2D histogram bins, sumw2 and overflow information.
        /// For SR histograms, accept background data stored at histogram or bin level.
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

        /// Combine histograms already scaled by their file's process weight.
        /// Check collection sizes and delegate bin accumulation to Histograms::combine.
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

        /// Sum per-analysis likelihoods with the configured alternative, skip list
        /// and individual/total capping options.
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

        /// Create a per-batch temporary directory for child YAML and JSON files.
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

        constexpr const char* kCheckpointSchema = "cbs-solo-checkpoint-v1";

        std::uint64_t fnv1a64(const std::string& text)
        {
          std::uint64_t hash = 14695981039346656037ull;
          for (unsigned char character : text)
          {
            hash ^= character;
            hash *= 1099511628211ull;
          }
          return hash;
        }

        std::string hex16(std::uint64_t value)
        {
          std::ostringstream out;
          out << std::hex << std::setfill('0') << std::setw(16) << value;
          return out.str();
        }

        /// Identity of one HepMC file. Card order is not part of the key.
        std::string checkpoint_key(const std::string& collider,
                                   const std::string& process,
                                   const std::string& path)
        {
          std::string text;
          text.reserve(collider.size() + process.size() + path.size() + 2);
          text.append(collider);
          text.push_back('\0');
          text.append(process);
          text.push_back('\0');
          text.append(path);
          return hex16(fnv1a64(text));
        }

        void atomic_write_json(const fs::path& path, const nlohmann::json& root)
        {
          const fs::path temporary = fs::path(path.string() + ".tmp");
          {
            std::ofstream out(temporary.string());
            if (!out)
              throw std::runtime_error("Failed to write " + temporary.string());
            out << root.dump(2) << '\n';
            if (!out)
              throw std::runtime_error("Failed to write " + temporary.string());
          }
          std::error_code error;
          fs::rename(temporary, path, error);
          if (error)
            throw std::runtime_error("Failed to publish " + path.string() + ": " + error.message());
        }

        std::string joined(const std::vector<std::string>& values)
        {
          std::ostringstream out;
          for (const std::string& value : values) out << value << '|';
          return out.str();
        }

        /// Collider-wide settings that change stored yields or Rivet fills.
        /// Cross sections, likelihood switches, report and screen layout are omitted:
        /// those are applied when the saved files are merged.
        std::string collider_fingerprint(
          const SoloInput::PreparedInput& prepared_input,
          const Options& settings,
          const SoloInput::ColliderInput& collider)
        {
          std::ostringstream text;
          text << std::setprecision(17);
          text << "collider=" << collider.name << '\n'
               << "beams=" << collider.run_info.beam_pid_1 << ','
               << collider.run_info.beam_pid_2 << '\n'
               << "energies=" << collider.run_info.beam_energy_1_GeV << ','
               << collider.run_info.beam_energy_2_GeV << '\n'
               << "sqrt_s=" << collider.run_info.collision_energy_TeV << '\n'
               << "analyses=" << joined(collider.analyses) << '\n'
               << "nominal=" << settings.getValueOrDef<std::string>("", "nominal_weight_name") << '\n'
               << "seed=" << settings.getValueOrDef<int>(-1, "seed") << '\n'
               << "jet_pt_min=" << settings.getValueOrDef<double>(10.0, "jet_pt_min") << '\n'
               << "jet_collection_taus="
               << settings.getValueOrDef<std::string>("antikt_R04", "jet_collection_taus") << '\n'
               << "jets=" << YAML::Dump(settings.getValue<YAML::Node>("jet_collections")) << '\n';
#ifdef CHECK_CUTFLOW
          text << "cutflow_support=1\n";
          text << "check_cutflow="
               << (settings.getValueOrDef<bool>(false, "check_cutflow") ? 1 : 0) << '\n';
#else
          text << "cutflow_support=0\ncheck_cutflow=0\n";
#endif
          text << "check_histogram="
               << (settings.getValueOrDef<bool>(false, "check_histogram") ? 1 : 0) << '\n'
               << "trace_input_events="
               << (settings.getValueOrDef<bool>(false, "trace_input_events") ? 1 : 0) << '\n'
               << "drop_accepted_events_file="
               << (settings.getValueOrDef<bool>(false, "drop_accepted_events_file") ? 1 : 0) << '\n';
          if (prepared_input.infile["rivet-settings"])
          {
            const Options rivet(prepared_input.infile["rivet-settings"]);
            text << "rivet=" << joined(rivet.getValue<std::vector<std::string>>("analyses")) << '\n'
                 << "rivet_exclude="
                 << joined(rivet.getValueOrDef<std::vector<std::string>>({}, "exclude_analyses"))
                 << '\n';
          }
          if (prepared_input.infile["contur-settings"])
          {
            text << "contur="
                 << joined(prepared_input.infile["contur-settings"].as<std::vector<std::string>>())
                 << '\n';
          }
          return hex16(fnv1a64(text.str()));
        }

        /// c_p in the single-loop mixture. Checkpoint YODA and the public JSON use this scale.
        double mixture_scale(long long collider_events,
                             double collider_sigma,
                             double process_sigma,
                             double process_sum)
        {
          if (!(process_sum > 0.0) || !std::isfinite(process_sum))
            throw std::runtime_error("Invalid total nominal weight while merging checkpoint files.");
          if (!(static_cast<double>(collider_events) > 0.0))
            throw std::runtime_error("Checkpoint merge requires events in the collider sample.");
          if (collider_sigma > 0.0)
            return (static_cast<double>(collider_events) / process_sum) * (process_sigma / collider_sigma);
          return static_cast<double>(collider_events) / process_sum;
        }

        /// Convert a child yield, baked at weight 1 and sigma_stored, into the process mixture.
        /// f * (L * sigma_stored / N_file * sum w) = L * sigma_new / S_p * sum w.
        double file_yield_factor(double sigma_stored, double sigma_new, long long n_events, double process_sum)
        {
          if (!(process_sum > 0.0) || !std::isfinite(process_sum) || n_events <= 0)
            throw std::runtime_error("Invalid file weight while merging a CBS checkpoint.");
          double ratio = 1.0;
          if (!(sigma_stored > 0.0) && sigma_new > 0.0)
          {
            throw std::runtime_error(
              "Stored CBS cross section is not positive. Run with --fresh after setting a positive cross section.");
          }
          if (sigma_stored > 0.0) ratio = sigma_new / sigma_stored;
          if (!std::isfinite(ratio) || ratio < 0.0)
            throw std::runtime_error("Invalid CBS cross-section ratio while merging a checkpoint.");
          return ratio * static_cast<double>(n_events) / process_sum;
        }

        std::vector<unsigned int> offset_event_ids(const std::vector<unsigned int>& ids,
                                                    unsigned long long offset)
        {
          if (offset > std::numeric_limits<unsigned int>::max())
            throw std::runtime_error("CBS checkpoint event offset does not fit in an event id.");
          std::vector<unsigned int> shifted;
          shifted.reserve(ids.size());
          for (unsigned int id : ids)
          {
            if (static_cast<unsigned long long>(id)
                > std::numeric_limits<unsigned int>::max() - offset)
              throw std::runtime_error("CBS checkpoint event id overflow while merging files.");
            shifted.push_back(static_cast<unsigned int>(static_cast<unsigned long long>(id) + offset));
          }
          return shifted;
        }

        /// One file child. Nominal weights only; the parent applies the mixture scale.
        /// Rivet writes RAW YODA and Contur is left to the parent.
        YAML::Node build_checkpoint_child_yaml(
          const SoloInput::PreparedInput& prepared_input,
          const Options& settings,
          const RunJob& job,
          const fs::path& json_tmp,
          const fs::path& yoda_tmp,
          bool with_rivet)
        {
          YAML::Node root;
          root["analyses"] = job.analyses;
          YAML::Node settings_node = YAML::Clone(prepared_input.infile["settings"]);
          for (const char* key : {"processes", "event_file", "cross_section_fb", "cross_section_pb",
                                  "cross_section_uncert_fb", "cross_section_uncert_pb",
                                  "cross_section_fractional_uncert", "output", "artifact_directory",
                                  "cbs_collider_name", "cbs_file_checkpoint", "cbs_file_weight_scale"})
          {
            settings_node.remove(key);
          }
          settings_node["event_file"] = job.hepmc_file;
          settings_node["cbs_collider_name"] = job.collider_name;
          settings_node["cbs_file_checkpoint"] = true;
          settings_node["cbs_file_weight_scale"] = 1.0;
          settings_node["cross_section_fb"] = job.cross_section_fb;
          settings_node["cross_section_uncert_fb"] = 0.0;
          settings_node["screen_output"] = false;
          settings_node["hepmc_progress"] = settings.getValueOrDef<bool>(
            settings.getValueOrDef<bool>(true, "screen_output"), "hepmc_progress");
          std::ostringstream progress_label;
          progress_label << "CBS HepMC File " << job.file_index << "/" << job.file_count
                         << " (" << job.collider_name << ")";
          settings_node["event_progress_label"] = progress_label.str();
          settings_node["output"] = json_tmp.string();
          root["settings"] = settings_node;
          if (with_rivet)
          {
            YAML::Node rivet = YAML::Clone(prepared_input.infile["rivet-settings"]);
            rivet.remove("drop_YODA_file");
            rivet.remove("YODA_output_directory");
            rivet["write_YODA_file"] = true;
            rivet["YODA_filename"] = yoda_tmp.string();
            root["rivet-settings"] = rivet;
          }
          return root;
        }

        struct PlannedFile
        {
          RunJob job;
          std::string key;
          std::string status;
          std::string reason;
          SoloInput::InputStatistics statistics;
          double sigma_stored = 0.0;
          fs::path json_path;
          fs::path yoda_path;
          fs::path stamp_path;
          bool execute = false;
          bool loaded = false;
          nlohmann::json result;
        };

        nlohmann::json file_stamp(const PlannedFile& planned,
                                 const SoloInput::PreparedInput& prepared_input,
                                 const std::string& fingerprint,
                                 bool with_rivet)
        {
          const SoloInput::HepMCRunInfo& run_info =
            SoloInput::find_collider(prepared_input, planned.job.collider_name).run_info;
          return {
            {"schema_version", kCheckpointSchema},
            {"key", planned.key},
            {"collider", planned.job.collider_name},
            {"process", planned.job.process_name},
            {"path", planned.job.hepmc_file},
            {"size_bytes", std::to_string(planned.statistics.size_bytes)},
            {"modified_ticks", std::to_string(planned.statistics.modified_ticks)},
            {"n_events", planned.statistics.n_events},
            {"sum_weights", planned.statistics.sum_weights},
            {"sum_weights2", planned.statistics.sum_weights2},
            {"nominal_name", planned.statistics.nominal_name},
            {"nominal_index", planned.statistics.nominal_index},
            {"beam_pid_1", run_info.beam_pid_1},
            {"beam_pid_2", run_info.beam_pid_2},
            {"beam_energy_1_GeV", run_info.beam_energy_1_GeV},
            {"beam_energy_2_GeV", run_info.beam_energy_2_GeV},
            {"collision_energy_TeV", run_info.collision_energy_TeV},
            {"sigma_stored_fb", planned.sigma_stored},
            {"settings_fingerprint", fingerprint},
            {"yoda", with_rivet}
          };
        }

        /// A stamp can be adopted when it still describes this scan and this binary's settings.
        bool stamp_matches(const nlohmann::json& stamp,
                           const PlannedFile& planned,
                           const std::string& fingerprint,
                           bool with_rivet)
        {
          try
          {
            if (stamp.value("schema_version", std::string()) != kCheckpointSchema) return false;
            if (stamp.value("key", std::string()) != planned.key) return false;
            if (stamp.value("collider", std::string()) != planned.job.collider_name) return false;
            if (stamp.value("process", std::string()) != planned.job.process_name) return false;
            if (stamp.value("path", std::string()) != planned.job.hepmc_file) return false;
            if (stamp.value("settings_fingerprint", std::string()) != fingerprint) return false;
            if (stamp.value("yoda", false) != with_rivet) return false;
            if (stamp.value("size_bytes", std::string()) != std::to_string(planned.statistics.size_bytes))
              return false;
            if (stamp.value("modified_ticks", std::string())
                != std::to_string(planned.statistics.modified_ticks))
              return false;
            if (stamp.at("n_events").get<long long>() != planned.statistics.n_events) return false;
            if (!is_consistent(stamp.at("sum_weights").get<double>(), planned.statistics.sum_weights))
              return false;
            if (!is_consistent(stamp.at("sum_weights2").get<double>(), planned.statistics.sum_weights2))
              return false;
            const double sigma = stamp.at("sigma_stored_fb").get<double>();
            if (!std::isfinite(sigma)) return false;
            return true;
          }
          catch (const std::exception&)
          {
            return false;
          }
        }

        bool stored_json_matches(const nlohmann::json& result, const PlannedFile& planned, double sigma_stored)
        {
          const auto& inputs = result.at("run").at("input_files");
          if (!inputs.is_array() || inputs.size() != 1) return false;
          if (inputs.at(0).at("file").get<std::string>() != planned.job.hepmc_file) return false;
          if (result.at("run").at("n_events").get<long long>() != planned.statistics.n_events) return false;
          if (!is_consistent(inputs.at(0).at("process_cross_section_fb").get<double>(), sigma_stored))
            return false;
          return result.contains("analyses");
        }

        CheckpointLock acquire_checkpoint_lock(const fs::path& lock_path)
        {
          const int fd = ::open(lock_path.string().c_str(), O_CREAT | O_RDWR | O_CLOEXEC, 0644);
          if (fd < 0)
          {
            throw std::runtime_error(
              "Failed to open CBS checkpoint lock " + lock_path.string() + ": " + std::strerror(errno));
          }
          if (::flock(fd, LOCK_EX | LOCK_NB) != 0)
          {
            const int open_error = errno;
            ::close(fd);
            if (open_error == EWOULDBLOCK || open_error == EAGAIN)
            {
              throw std::runtime_error(
                "CBS checkpoint is in use: " + lock_path.string()
                + ". Another CBS run holds this checkpoint.");
            }
            throw std::runtime_error(
              "Failed to lock CBS checkpoint " + lock_path.string() + ": " + std::strerror(open_error));
          }
          return CheckpointLock(fd);
        }
      } // namespace

      /// Execute per-file jobs sequentially for one parameter point and merge signals.
      /// Within each physics process, weight files by their nominal input sums;
      /// add the resulting process yields and independent MC variances.  Each analysis
      /// only receives the files of its own collider, and is normalised to that
      /// collider's cross section and event count when its likelihood is recomputed.
      /// Retain temporary files if requested.
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
        if (jobs.empty())
        {
          throw std::runtime_error("No batch jobs were created: no enabled analysis matches any HepMC collider.");
        }
        std::map<std::string, AnalysisAccumulator> accumulators;
        std::vector<long long> process_event_totals(prepared_input.processes.size(), 0);
        std::map<std::string, long long> collider_event_totals;
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
          process_event_totals.at(job.process_index) += n_events;
          collider_event_totals[job.collider_name] += n_events;

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
        // Common weight units: pool files with their nominal sums, not counts.
        for (const CompletedRun& completed : completed_runs)
        {
          const long long process_events = process_event_totals.at(completed.job.process_index);
          if (process_events <= 0)
          {
            throw std::runtime_error("Missing process event total for process " + completed.job.process_name + ".");
          }
          double process_sum_weights = 0.0;
          for (const auto& file : prepared_input.processes.at(completed.job.process_index).files)
            process_sum_weights += prepared_input.input_statistics.at(file.filename).sum_weights;
          const double process_weight = prepared_input.input_statistics.at(completed.job.hepmc_file).sum_weights
                                        / process_sum_weights;

          for (const auto& analysis_item : completed.analyses_json.items())
          {
            const std::string analysis_name = analysis_item.key();
            const auto collider_it = prepared_input.analysis_colliders.find(analysis_name);
            if (collider_it == prepared_input.analysis_colliders.end()
                || collider_it->second != completed.job.collider_name)
            {
              throw std::runtime_error(
                "Per-file CBS run for " + completed.job.hepmc_file + " (collider "
                + completed.job.collider_name + ") returned analysis " + analysis_name
                + ", which is not assigned to that collider.");
            }

            const nlohmann::json& analysis_json = analysis_item.value();
            const std::vector<SRPayload> sr_payloads = parse_sorted_sr_payloads(analysis_json);
            const Cutflows file_cutflows = parse_cutflows_or_empty(analysis_json);
            const Histograms file_histograms = parse_histograms_or_empty(analysis_json);
            Histograms weighted_histograms = file_histograms;
            weighted_histograms.scale(process_weight);

            AnalysisAccumulator& acc = accumulators[analysis_name];
            if (acc.data.srdata.empty())
            {
              initialize_accumulator(acc, analysis_name, completed.job.collider_name,
                                     analysis_json, sr_payloads, file_cutflows);
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
        merged.collider_event_counts = collider_event_totals;

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
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, data.collider_name);
          const long long collider_events = collider_event_totals.at(collider.name);

          for (std::size_t sr_index = 0; sr_index < data.srdata.size(); ++sr_index)
          {
            SignalRegionData& sr = data.srdata[sr_index];
            const double scaled_err = std::sqrt(acc.n_sig_scaled_err2[sr_index]);

            if (collider.cross_section_fb > 0.0 && data.luminosity > 0.0)
            {
              const double scale =
                static_cast<double>(collider_events)
                / (data.luminosity * collider.cross_section_fb);

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
        const bool use_fulllikes = FullLikes_FileExists != nullptr
                                && FullLikes_ReadIn != nullptr
                                && FullLikes_Evaluate != nullptr;

        // Recompute likelihoods collider by collider, as the cross section and
        // MC event count passed to the likelihood calculation are per collider.
        for (const SoloInput::ColliderInput& collider : prepared_input.colliders)
        {
          AnalysisDataPointers collider_analyses;
          for (AnalysisData* analysis_data : merged.analyses)
          {
            if (analysis_data->collider_name == collider.name) collider_analyses.push_back(analysis_data);
          }
          if (collider_analyses.empty()) continue;

          map_str_AnalysisLogLikes collider_loglikes;
          calc_LHC_LogLikes_common(
            collider_loglikes,
            use_fulllikes,
            collider_analyses,
            loglike_options,
            marginaliser,
            skip_calc,
            FullLikes_FileExists,
            FullLikes_ReadIn,
            FullLikes_Evaluate,
            collider.cross_section_fb,
            static_cast<int>(collider_event_totals.at(collider.name)));
          for (auto& loglike_pair : collider_loglikes)
          {
            merged.analysis_loglikes[loglike_pair.first] = std::move(loglike_pair.second);
          }
        }

        merged.combined_loglike = compute_combined_loglike(merged.analysis_loglikes, settings);

        if (!keep_temp)
        {
          fs::remove_all(temp_dir);
        }

        return merged;
      }

      // A collider is a complete physical mixture. Each child performs its
      // own input normalisation, raw Rivet merge and one Contur evaluation.
      MergedRunResult run_joint_colliders(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&))
      {
        const fs::path temp_dir = make_temp_dir();
        const bool with_contur = bool(prepared_input.infile["contur-settings"]);
        MergedRunResult merged;
        merged.process_event_counts.resize(prepared_input.processes.size(), 0);
        for (const auto& collider : prepared_input.colliders)
        {
          if (!with_contur && collider.analyses.empty()) continue;
          RunJob job;
          job.collider_name = collider.name;
          job.hepmc_file = collider.hepmc_filenames.front();
          job.yaml_file = temp_dir / (collider.name + ".yaml");
          job.output_json_file = temp_dir / (collider.name + ".json");
          YAML::Node child = YAML::Clone(prepared_input.infile);
          child["analyses"] = collider.analyses;
          auto child_settings = child["settings"];
          for (const char* key : {"event_file", "cross_section_fb", "cross_section_pb",
                                 "cross_section_uncert_fb", "cross_section_uncert_pb",
                                 "cross_section_fractional_uncert"}) child_settings.remove(key);
          YAML::Node processes(YAML::NodeType::Sequence);
          for (const auto index : collider.process_indices)
          {
            const auto& process = prepared_input.processes.at(index);
            YAML::Node item;
            item["name"] = process.name;
            item["cross_section_fb"] = process.cross_section_fb;
            item["cross_section_uncert_fb"] = process.cross_section_uncert_fb;
            item["files"] = YAML::Node(YAML::NodeType::Sequence);
            for (const auto& file : process.files) item["files"].push_back(file.filename);
            processes.push_back(item);
          }
          child_settings["processes"] = processes;
          child_settings["cbs_collider_name"] = collider.name;
          child_settings["screen_output"] = false;
          child_settings["hepmc_progress"] = settings.getValueOrDef<bool>(
            settings.getValueOrDef<bool>(true, "screen_output"), "hepmc_progress");
          child_settings["event_progress_label"] = "CBS HepMC " + collider.name;
          if (settings.hasKey("output"))
          {
            const std::string user_output = settings.getValue<std::string>("output");
            if (!user_output.empty())
            {
              child_settings["artifact_directory"] =
                SoloOutput::prepare_output_directory(user_output);
            }
          }
          child_settings["output"] = job.output_json_file.string();
          write_yaml_file(child, job.yaml_file);
          run_single_job(cbs_executable, job);
          const auto result = read_json_file(job.output_json_file);
          const auto& run = result.at("run");
          const int count = run.at("n_events").get<int>();
          if (count <= 0 || merged.total_events > std::numeric_limits<int>::max() - count)
            throw std::runtime_error("Invalid combined CBS event count for " + collider.name);
          merged.total_events += count;
          merged.total_process_events += count;
          merged.collider_event_counts[collider.name] = count;
          for (const auto& input : run.at("input_files"))
          {
            SoloOutput::InputFileSummaryEntry entry;
            entry.file = input.at("file").get<std::string>();
            entry.process = input.at("process").get<std::string>();
            entry.collider = collider.name;
            entry.n_events = input.at("n_events").get<long long>();
            entry.sum_weights = input.at("sum_weights").get<double>();
            entry.sum_weights2 = input.at("sum_weights2").get<double>();
            entry.nominal_name = input.at("nominal_name").get<std::string>();
            entry.nominal_index = input.at("nominal_index").get<int>();
            entry.weight_scale = input.at("weight_scale").get<double>();
            entry.process_cross_section_fb = input.at("process_cross_section_fb").get<double>();
            entry.process_cross_section_uncert_fb = input.at("process_cross_section_uncert_fb").get<double>();
            for (const auto index : collider.process_indices)
              if (prepared_input.processes[index].name == entry.process)
                merged.process_event_counts[index] += entry.n_events;
            merged.input_files.push_back(std::move(entry));
          }
          if (run.contains("event_sources"))
            for (const auto& source : run.at("event_sources"))
              merged.input_loop.input_event_sources.push_back({source.at("iteration").get<int>(),
                source.at("file").get<std::string>(), source.at("file_event_index").get<long long>(),
                source.at("original_event_number").get<int>()});
          merged.input_loop.contur_evaluations += run.at("contur_evaluations").get<int>();
          for (const auto& name : run.at("rivet_analyses"))
          {
            const auto analysis = name.get<std::string>();
            if (std::find(merged.rivet_analyses.begin(), merged.rivet_analyses.end(), analysis)
                == merged.rivet_analyses.end()) merged.rivet_analyses.push_back(analysis);
          }
          for (const auto& item : result.at("analyses").items())
          {
            const auto assigned = prepared_input.analysis_colliders.find(item.key());
            if (assigned == prepared_input.analysis_colliders.end() || assigned->second != collider.name)
              throw std::runtime_error("Unexpected child analysis " + item.key() + " for " + collider.name);
            const auto& json = item.value();
            AnalysisAccumulator accumulator;
            const auto payloads = parse_sorted_sr_payloads(json);
            initialize_accumulator(accumulator, item.key(), collider.name, json, payloads,
                                   parse_cutflows_or_empty(json));
            accumulator.data.histograms = parse_histograms_or_empty(json);
            accumulator.data.detector_name = json.at("detector").get<std::string>();
            for (std::size_t i = 0; i < payloads.size(); ++i)
            {
              auto& sr = accumulator.data.srdata[i];
              const auto& values = json.at("signal_regions").at(sr.sr_label);
              sr.n_sig_MC = values.at("n_sig_MC").get<double>();
              sr.n_sig_MC_stat = values.at("n_sig_MC_stat").get<double>();
              sr.n_sig_MC_sys = values.at("n_sig_MC_sys").get<double>();
              sr.n_sig_scaled = values.at("n_sig_scaled").get<double>();
              if (values.contains("accepted_event_ids"))
              {
                sr.accepted_event_ids = values.at("accepted_event_ids").get<std::vector<unsigned int>>();
                sr.has_event_records = true;
              }
            }
            merged.analyses_storage.push_back(std::move(accumulator.data));
          }
          if (with_contur)
          {
            if (run.at("contur_evaluations").get<int>() != 1)
              throw std::runtime_error("Expected exactly one Contur evaluation for " + collider.name);
            merged.contur_loglike += result.at("contur").at("total_loglike").get<double>();
            for (const auto& pool : result.at("contur").at("pools").items())
            {
              if (merged.contur_pool_loglikes.count(pool.key()))
                throw std::runtime_error("Contur pool " + pool.key()
                  + " appears in multiple colliders; a joint experimental covariance is required.");
              merged.contur_pool_loglikes[pool.key()] = pool.value().at("loglike").get<double>();
              merged.contur_pool_info[pool.key()] = pool.value().at("dominant_measurement").get<std::string>();
            }
          }
        }
        for (auto& analysis : merged.analyses_storage) merged.analyses.push_back(&analysis);
        Options loglike_options = settings;
        loglike_options.setValue("poisson_like_estimator",
          settings.getValueOrDef<std::string>("MLE", "poisson_like_estimator"));
        const bool use_fulllikes = FullLikes_FileExists && FullLikes_ReadIn && FullLikes_Evaluate;
        for (const auto& collider : prepared_input.colliders)
        {
          AnalysisDataPointers analyses;
          for (auto* analysis : merged.analyses)
            if (analysis->collider_name == collider.name) analyses.push_back(analysis);
          if (analyses.empty()) continue;
          map_str_AnalysisLogLikes loglikes;
          calc_LHC_LogLikes_common(loglikes, use_fulllikes, analyses, loglike_options, marginaliser,
            false, FullLikes_FileExists, FullLikes_ReadIn, FullLikes_Evaluate,
            collider.cross_section_fb, int(merged.collider_event_counts.at(collider.name)));
          merged.analysis_loglikes.insert(loglikes.begin(), loglikes.end());
        }
        merged.combined_loglike = compute_combined_loglike(merged.analysis_loglikes, settings);
        if (!settings.getValueOrDef<bool>(false, "keep_batch_tmp")) fs::remove_all(temp_dir);
        return merged;
      }

      /// Checkpoint driver. Each finished HepMC file is published before the next one starts.
      /// Search yields are rescaled here. Rivet files are returned unscaled for the caller.
      CheckpointResult run_with_checkpoints(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        const std::string& output_file,
        bool screen_output,
        bool fresh,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      )
      {
        if (prepared_input.processes.empty())
          throw std::runtime_error("CBS checkpoint requested, but the card has no processes.");
        if (output_file.empty())
          throw std::runtime_error("CBS checkpoint requested, but settings.output is empty.");

        const bool with_rivet = bool(prepared_input.infile["rivet-settings"]);
        const bool trace_sources = settings.getValueOrDef<bool>(false, "trace_input_events");
        const fs::path checkpoint_dir = fs::absolute(output_file).replace_extension(".cbs");
        const fs::path files_dir = checkpoint_dir / "files";
        const fs::path work_dir = checkpoint_dir / "work";
        const fs::path manifest_path = checkpoint_dir / "manifest.json";
        const fs::path lock_path = checkpoint_dir / "checkpoint.lock";
        fs::create_directories(checkpoint_dir);
        CheckpointLock lock = acquire_checkpoint_lock(lock_path);
        if (fresh)
        {
          std::error_code error;
          fs::remove_all(files_dir, error);
          fs::remove_all(work_dir, error);
          fs::remove(manifest_path, error);
        }
        fs::create_directories(files_dir);
        fs::create_directories(work_dir);
        if (!fresh && fs::exists(manifest_path))
        {
          const nlohmann::json existing = read_json_file(manifest_path);
          const std::string schema = existing.value("schema_version", std::string());
          if (schema != kCheckpointSchema)
          {
            throw std::runtime_error(
              "CBS checkpoint format in " + manifest_path.string()
              + " is not " + kCheckpointSchema + ". Run with --fresh to replace it.");
          }
        }

        std::map<std::string, std::string> fingerprints;
        for (const SoloInput::ColliderInput& collider : prepared_input.colliders)
          fingerprints[collider.name] = collider_fingerprint(prepared_input, settings, collider);

        std::vector<PlannedFile> planned;
        std::size_t included = 0;
        for (const SoloInput::ProcessInput& process : prepared_input.processes)
        {
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, process.collider_name);
          if (collider.analyses.empty() && !with_rivet) continue;
          included += process.files.size();
        }
        std::size_t file_index = 0;
        for (std::size_t ip = 0; ip < prepared_input.processes.size(); ++ip)
        {
          const SoloInput::ProcessInput& process = prepared_input.processes[ip];
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, process.collider_name);
          if (collider.analyses.empty() && !with_rivet) continue;
          for (const SoloInput::HepMCFileInput& file : process.files)
          {
            PlannedFile item;
            item.job.process_index = ip;
            item.job.process_name = process.name;
            item.job.collider_name = collider.name;
            item.job.analyses = collider.analyses;
            item.job.hepmc_file = file.filename;
            item.job.file_index = ++file_index;
            item.job.file_count = included;
            item.job.cross_section_fb = process.cross_section_fb;
            item.job.cross_section_uncert_fb = process.cross_section_uncert_fb;
            item.key = checkpoint_key(collider.name, process.name, file.filename);
            item.statistics = prepared_input.input_statistics.at(file.filename);
            item.json_path = files_dir / (item.key + ".json");
            item.yoda_path = files_dir / (item.key + ".yoda");
            item.stamp_path = files_dir / (item.key + ".stamp.json");
            item.job.yaml_file = work_dir / (item.key + ".yaml");
            item.job.output_json_file = work_dir / (item.key + ".json.tmp");
            const std::string& fingerprint = fingerprints.at(collider.name);

            item.execute = true;
            item.reason = "missing";
            if (fs::exists(item.stamp_path))
            {
              nlohmann::json stamp;
              bool parsed = true;
              try { stamp = read_json_file(item.stamp_path); }
              catch (const std::exception&) { parsed = false; }
              if (!parsed)
              {
                item.reason = "incomplete";
              }
              else if (stamp.value("settings_fingerprint", std::string()) != fingerprint)
              {
                item.reason = "settings changed";
              }
              else if (!stamp_matches(stamp, item, fingerprint, with_rivet))
              {
                item.reason = "file changed";
              }
              else
              {
                bool usable = false;
                try
                {
                  const bool yoda_ok = !with_rivet
                    || (fs::is_regular_file(item.yoda_path) && fs::file_size(item.yoda_path) > 0);
                  if (yoda_ok && fs::is_regular_file(item.json_path))
                  {
                    item.result = read_json_file(item.json_path);
                    item.sigma_stored = stamp.at("sigma_stored_fb").get<double>();
                    usable = stored_json_matches(item.result, item, item.sigma_stored);
                  }
                }
                catch (const std::exception&)
                {
                  usable = false;
                }
                if (usable)
                {
                  item.loaded = true;
                  item.execute = false;
                  item.reason = "complete";
                }
                else
                {
                  item.reason = "incomplete";
                }
              }
            }
            else if (fs::exists(item.json_path) || fs::exists(item.yoda_path))
            {
              item.reason = "incomplete";
            }
            item.status = item.execute ? (item.reason == "missing" ? "run" : "rerun") : "kept";
            planned.push_back(std::move(item));
          }
        }
        if (planned.empty())
          throw std::runtime_error("No checkpoint files were created from settings.processes.");

        if (screen_output)
        {
          const std::ios::fmtflags saved_flags = std::cout.flags();
          std::cout << "\nCBS checkpoint\n";
          for (const PlannedFile& item : planned)
          {
            std::cout << "  File " << item.job.file_index << "/" << item.job.file_count
                      << "  " << std::left << std::setw(6) << item.status
                      << "  " << std::setw(16) << item.reason
                      << "  " << item.job.hepmc_file << '\n';
          }
          std::cout.flags(saved_flags);
        }

        nlohmann::json manifest = {
          {"schema_version", kCheckpointSchema},
          {"files", nlohmann::json::object()}
        };
        for (const PlannedFile& item : planned)
        {
          if (item.execute) continue;
          const nlohmann::json stamp =
            file_stamp(item, prepared_input, fingerprints.at(item.job.collider_name), with_rivet);
          manifest["files"][item.key] = stamp;
          // Older stamps stored the weight totals without the beams. Write the
          // inspection once so the next run does not open this HepMC file.
          bool missing_inspection = true;
          if (fs::is_regular_file(item.stamp_path))
          {
            try
            {
              const nlohmann::json existing = read_json_file(item.stamp_path);
              missing_inspection = !existing.contains("beam_pid_1")
                || !existing.contains("nominal_name");
            }
            catch (const std::exception&)
            {
              missing_inspection = true;
            }
          }
          if (missing_inspection) atomic_write_json(item.stamp_path, stamp);
        }
        atomic_write_json(manifest_path, manifest);

        for (PlannedFile& item : planned)
        {
          if (!item.execute) continue;
          const fs::path json_tmp = item.job.output_json_file;
          // YODA picks the writer from the final extension. ".yoda.tmp" is rejected.
          const fs::path yoda_tmp = work_dir / (item.key + ".tmp.yoda");
          std::error_code remove_error;
          fs::remove(json_tmp, remove_error);
          fs::remove(yoda_tmp, remove_error);
          write_yaml_file(
            build_checkpoint_child_yaml(
              prepared_input, settings, item.job, json_tmp, yoda_tmp, with_rivet),
            item.job.yaml_file);
          // Flush before the child so an interrupted run names this HepMC file.
          if (screen_output)
          {
            std::cout << "  Running File " << item.job.file_index << "/"
                      << item.job.file_count << "  " << item.job.hepmc_file
                      << '\n' << std::flush;
          }
          run_single_job(cbs_executable, item.job);
          item.result = read_json_file(json_tmp);
          if (!item.result.contains("run") || !item.result.contains("analyses"))
            throw std::runtime_error("Checkpoint child JSON is incomplete: " + json_tmp.string());
          const double sigma_stored =
            item.result.at("run").at("input_files").at(0).at("process_cross_section_fb").get<double>();
          if (!is_consistent(sigma_stored, item.job.cross_section_fb))
          {
            throw std::runtime_error(
              "Checkpoint child used an unexpected cross section for " + item.job.hepmc_file);
          }
          item.sigma_stored = sigma_stored;
          if (!stored_json_matches(item.result, item, item.sigma_stored))
          {
            throw std::runtime_error(
              "Checkpoint child result does not match the scanned HepMC file " + item.job.hepmc_file);
          }
          if (with_rivet && (!fs::is_regular_file(yoda_tmp) || fs::file_size(yoda_tmp) == 0))
            throw std::runtime_error("Checkpoint child did not write YODA for " + item.job.hepmc_file);
          fs::rename(json_tmp, item.json_path);
          if (with_rivet) fs::rename(yoda_tmp, item.yoda_path);
          else fs::remove(item.yoda_path, remove_error);
          item.loaded = true;
          const nlohmann::json stamp =
            file_stamp(item, prepared_input, fingerprints.at(item.job.collider_name), with_rivet);
          atomic_write_json(item.stamp_path, stamp);
          manifest["files"][item.key] = stamp;
          atomic_write_json(manifest_path, manifest);
          fs::remove(item.job.yaml_file, remove_error);
          if (screen_output)
          {
            std::cout << "Checkpoint "
                      << fs::absolute(item.json_path).lexically_normal().string() << '\n';
          }
        }

        MergedRunResult merged;
        merged.process_event_counts.assign(prepared_input.processes.size(), 0);
        std::map<std::string, double> process_sums;
        std::map<std::string, long long> collider_events;
        for (const PlannedFile& item : planned)
        {
          merged.process_event_counts.at(item.job.process_index) += item.statistics.n_events;
          process_sums[item.job.process_name + "\n" + item.job.collider_name] += item.statistics.sum_weights;
          collider_events[item.job.collider_name] += item.statistics.n_events;
        }
        long long total_events = 0;
        for (const auto& count : collider_events)
        {
          if (count.second < 0 || total_events > std::numeric_limits<int>::max() - count.second)
            throw std::runtime_error("Combined CBS event count does not fit in the result.");
          total_events += count.second;
          merged.collider_event_counts[count.first] = count.second;
        }
        merged.total_events = static_cast<int>(total_events);
        merged.total_process_events = total_events;

        std::map<std::string, AnalysisAccumulator> accumulators;
        std::vector<CheckpointYodaFile> yoda_files;
        unsigned long long event_offset = 0;
        for (const PlannedFile& item : planned)
        {
          if (!item.loaded)
            throw std::runtime_error("CBS checkpoint is missing a result for " + item.job.hepmc_file);
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, item.job.collider_name);
          const SoloInput::ProcessInput& process = prepared_input.processes.at(item.job.process_index);
          const double process_sum = process_sums.at(process.name + "\n" + collider.name);
          const double factor = file_yield_factor(
            item.sigma_stored, process.cross_section_fb, item.statistics.n_events, process_sum);
          const double reported_scale = mixture_scale(
            collider_events.at(collider.name), collider.cross_section_fb,
            process.cross_section_fb, process_sum);
          if (!std::isfinite(reported_scale) || reported_scale < 0.0)
            throw std::runtime_error("Invalid mixture scale for process " + process.name);

          SoloOutput::InputFileSummaryEntry summary;
          summary.file = item.job.hepmc_file;
          summary.process = process.name;
          summary.collider = collider.name;
          summary.n_events = item.statistics.n_events;
          summary.sum_weights = item.statistics.sum_weights;
          summary.sum_weights2 = item.statistics.sum_weights2;
          summary.nominal_name = item.statistics.nominal_name;
          summary.nominal_index = item.statistics.nominal_index;
          summary.weight_scale = reported_scale;
          summary.process_cross_section_fb = process.cross_section_fb;
          summary.process_cross_section_uncert_fb = process.cross_section_uncert_fb;
          merged.input_files.push_back(summary);

          const nlohmann::json& run = item.result.at("run");
          if (trace_sources)
          {
            if (!run.contains("event_sources"))
              throw std::runtime_error("Checkpoint file has no event sources: " + item.job.hepmc_file);
            const nlohmann::json& sources = run.at("event_sources");
            if (sources.size() != static_cast<std::size_t>(item.statistics.n_events))
              throw std::runtime_error("Checkpoint event sources do not cover " + item.job.hepmc_file);
            for (const nlohmann::json& source : sources)
            {
              const long long iteration = source.at("iteration").get<long long>()
                + static_cast<long long>(event_offset);
              if (iteration < 0 || iteration > std::numeric_limits<int>::max())
                throw std::runtime_error("CBS checkpoint event number overflow.");
              merged.input_loop.input_event_sources.push_back({
                static_cast<int>(iteration),
                source.at("file").get<std::string>(),
                source.at("file_event_index").get<long long>(),
                source.at("original_event_number").get<int>()
              });
            }
          }
          if (event_offset > std::numeric_limits<unsigned long long>::max()
              - static_cast<unsigned long long>(item.statistics.n_events))
            throw std::runtime_error("CBS checkpoint event offset overflow.");
          const unsigned long long this_offset = event_offset;
          event_offset += static_cast<unsigned long long>(item.statistics.n_events);

          if (with_rivet)
          {
            CheckpointYodaFile yoda;
            yoda.key = item.key;
            yoda.collider = collider.name;
            yoda.process = process.name;
            yoda.hepmc_file = item.job.hepmc_file;
            yoda.yoda_file = item.yoda_path.string();
            yoda.scale = reported_scale;
            yoda_files.push_back(std::move(yoda));
          }

          for (const auto& name : run.at("rivet_analyses"))
          {
            const std::string analysis = name.get<std::string>();
            if (std::find(merged.rivet_analyses.begin(), merged.rivet_analyses.end(), analysis)
                == merged.rivet_analyses.end())
              merged.rivet_analyses.push_back(analysis);
          }

          for (const auto& analysis_item : item.result.at("analyses").items())
          {
            const std::string analysis_name = analysis_item.key();
            const auto assigned = prepared_input.analysis_colliders.find(analysis_name);
            if (assigned == prepared_input.analysis_colliders.end()
                || assigned->second != collider.name)
            {
              throw std::runtime_error(
                "Checkpoint file " + item.job.hepmc_file + " returned analysis " + analysis_name
                + ", which is not assigned to " + collider.name);
            }
            const nlohmann::json& analysis_json = analysis_item.value();
            const std::vector<SRPayload> payloads = parse_sorted_sr_payloads(analysis_json);
            const bool seeding = accumulators[analysis_name].data.srdata.empty();
            AnalysisAccumulator& accumulator = accumulators[analysis_name];
            if (seeding)
            {
              initialize_accumulator(
                accumulator, analysis_name, collider.name, analysis_json, payloads,
                parse_cutflows_or_empty(analysis_json));
              accumulator.data.detector_name = analysis_json.at("detector").get<std::string>();
              accumulator.data.histograms = parse_histograms_or_empty(analysis_json);
              accumulator.data.histograms.scale(factor);
            }
            else
            {
              validate_payload_consistency(accumulator, analysis_name, payloads, analysis_json);
              accumulate_cutflows(
                accumulator.data.cutflows, parse_cutflows_or_empty(analysis_json), analysis_name);
              Histograms weighted = parse_histograms_or_empty(analysis_json);
              weighted.scale(factor);
              accumulate_histograms(accumulator.data.histograms, weighted, analysis_name);
            }
            if (accumulator.n_sig_scaled_err2.size() != payloads.size())
              accumulator.n_sig_scaled_err2.assign(payloads.size(), 0.0);
            for (std::size_t sr_index = 0; sr_index < payloads.size(); ++sr_index)
            {
              SignalRegionData& signal_region = accumulator.data.srdata[sr_index];
              const nlohmann::json& values = analysis_json.at("signal_regions").at(signal_region.sr_label);
              const bool recorded = values.contains("accepted_event_ids");
              if (!seeding && recorded != signal_region.has_event_records)
              {
                throw std::runtime_error(
                  "Checkpoint files disagree on event records for " + analysis_name);
              }
              signal_region.n_sig_scaled += factor * payloads[sr_index].n_sig_scaled;
              accumulator.n_sig_scaled_err2[sr_index] +=
                std::pow(factor * payloads[sr_index].n_sig_scaled_err, 2);
              if (recorded)
              {
                const std::vector<unsigned int> shifted = offset_event_ids(
                  values.at("accepted_event_ids").get<std::vector<unsigned int>>(), this_offset);
                signal_region.accepted_event_ids.insert(
                  signal_region.accepted_event_ids.end(), shifted.begin(), shifted.end());
                signal_region.has_event_records = true;
              }
            }
          }
        }

        std::vector<std::string> analysis_order;
        for (const str& name : prepared_input.analyses)
          if (accumulators.count(name) != 0) analysis_order.push_back(name);
        for (const auto& pair : accumulators)
          if (std::find(analysis_order.begin(), analysis_order.end(), pair.first) == analysis_order.end())
            analysis_order.push_back(pair.first);

        merged.analyses_storage.reserve(analysis_order.size());
        for (const std::string& analysis_name : analysis_order)
        {
          AnalysisAccumulator& accumulator = accumulators.at(analysis_name);
          AnalysisData data = accumulator.data;
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, data.collider_name);
          const long long collider_count = collider_events.at(collider.name);
          if (!(collider.cross_section_fb > 0.0) || !(data.luminosity > 0.0))
          {
            throw std::runtime_error(
              "Checkpoint merge requires a positive cross section and luminosity for "
              + analysis_name);
          }
          const double to_mc = static_cast<double>(collider_count)
            / (data.luminosity * collider.cross_section_fb);
          for (std::size_t sr_index = 0; sr_index < data.srdata.size(); ++sr_index)
          {
            SignalRegionData& signal_region = data.srdata[sr_index];
            const double scaled_error = std::sqrt(accumulator.n_sig_scaled_err2[sr_index]);
            signal_region.n_sig_MC = signal_region.n_sig_scaled * to_mc;
            signal_region.n_sig_MC_stat = scaled_error * to_mc;
            signal_region.n_sig_MC_sys = 0.0;
          }
          merged.analyses_storage.push_back(std::move(data));
        }
        for (AnalysisData& analysis : merged.analyses_storage)
          merged.analyses.push_back(&analysis);

        Options loglike_options = settings;
        loglike_options.setValue(
          "poisson_like_estimator",
          settings.getValueOrDef<std::string>("MLE", "poisson_like_estimator"));
        const bool use_fulllikes = FullLikes_FileExists != nullptr
          && FullLikes_ReadIn != nullptr && FullLikes_Evaluate != nullptr;
        for (const SoloInput::ColliderInput& collider : prepared_input.colliders)
        {
          AnalysisDataPointers analyses;
          for (AnalysisData* analysis : merged.analyses)
            if (analysis->collider_name == collider.name) analyses.push_back(analysis);
          if (analyses.empty()) continue;
          const long long count = collider_events.at(collider.name);
          if (count > std::numeric_limits<int>::max())
            throw std::runtime_error("Collider event count does not fit in the likelihood call.");
          map_str_AnalysisLogLikes loglikes;
          calc_LHC_LogLikes_common(
            loglikes, use_fulllikes, analyses, loglike_options, marginaliser, false,
            FullLikes_FileExists, FullLikes_ReadIn, FullLikes_Evaluate,
            collider.cross_section_fb, static_cast<int>(count));
          for (auto& loglike : loglikes)
            merged.analysis_loglikes[loglike.first] = std::move(loglike.second);
        }
        merged.combined_loglike = compute_combined_loglike(merged.analysis_loglikes, settings);

        CheckpointResult result;
        result.merged = std::move(merged);
        result.merged.analyses.clear();
        for (AnalysisData& analysis : result.merged.analyses_storage)
          result.merged.analyses.push_back(&analysis);
        result.checkpoint_directory = checkpoint_dir.string();
        result.yoda_files = std::move(yoda_files);
        result.lock = std::move(lock);
        return result;
      }

      /// Estimate additional MC events for fractional-error targets in each selected SR.
      /// For finite positive yields and errors, extrapolate using 1/sqrt(N) scaling of the
      /// analysis's collider and distribute extra events over that collider's processes
      /// by cross section (event counts as fallback).
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

        for (const AnalysisData* analysis_ptr : merged.analyses)
        {
          if (analysis_ptr == nullptr) continue;
          const AnalysisData& analysis = *analysis_ptr;

          // Extra events for an analysis can only come from its own collider's processes.
          const auto collider_events_it = merged.collider_event_counts.find(analysis.collider_name);
          if (collider_events_it == merged.collider_event_counts.end() || collider_events_it->second <= 0) continue;
          const long long total_processed_events = collider_events_it->second;
          const SoloInput::ColliderInput& collider =
            SoloInput::find_collider(prepared_input, analysis.collider_name);

          std::vector<ProcessSamplingAdvice> process_templates;
          process_templates.reserve(collider.process_indices.size());
          double total_cross_section_fb = 0.0;
          for (std::size_t ip : collider.process_indices)
          {
            const SoloInput::ProcessInput& process = prepared_input.processes.at(ip);
            ProcessSamplingAdvice process_info;
            process_info.process_name = process.name;
            process_info.cross_section_fb = process.cross_section_fb;
            process_info.processed_events = merged.process_event_counts.at(ip);
            process_info.recommended_additional_events = 0;
            total_cross_section_fb += std::max(0.0, process_info.cross_section_fb);
            process_templates.push_back(process_info);
          }

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
              // Allocate whole events by rounding down each process share, then give
              // the remainder to the largest fractional parts to preserve the total.
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
