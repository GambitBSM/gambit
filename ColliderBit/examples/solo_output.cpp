//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Output helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_output.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>

#include "gambit/Utils/json.hpp"

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
    namespace SoloOutput
    {
      namespace
      {
        const std::string kSchemaVersion = "cbs-solo-loglike-v1";
        const int kJsonIndent = 2;

        void ensure_parent_directory_exists(const std::string& output_file)
        {
          const std::size_t last_slash = output_file.find_last_of("/\\");
          if (last_slash == std::string::npos) return;

          const std::string directory = output_file.substr(0, last_slash);
          if (directory.empty()) return;

          if (!fs::exists(directory))
          {
            fs::create_directories(directory);
          }
        }

        void write_json_to_file(const nlohmann::json& root, const std::string& output_file, int indent)
        {
          ensure_parent_directory_exists(output_file);

          std::ofstream ofs(output_file);
          if (!ofs)
          {
            throw std::runtime_error("Unable to open output file for writing: " + output_file);
          }

          ofs << root.dump(indent) << '\n';
        }

        void append_term(
          nlohmann::json& terms,
          const std::string& term_id,
          const std::string& component,
          const std::string& analysis_name,
          const std::string& sr_label,
          const std::string& variant,
          double loglike,
          bool safe_to_sum,
          const std::string& exclusive_group,
          bool selected_in_default
        )
        {
          nlohmann::json term;
          term["term_id"] = term_id;
          term["component"] = component;
          term["variant"] = variant;
          term["loglike"] = loglike;
          term["safe_to_sum"] = safe_to_sum;
          term["exclusive_group"] = exclusive_group;
          term["selected_in_default"] = selected_in_default;

          if (!analysis_name.empty()) term["analysis_name"] = analysis_name;
          if (!sr_label.empty()) term["sr_label"] = sr_label;

          terms.push_back(term);
        }

        nlohmann::json build_cutflows_json(const Cutflows& cutflows)
        {
          nlohmann::json cutflows_json = nlohmann::json::array();

          for (const Cutflow& cutflow : cutflows.cfs)
          {
            nlohmann::json cutflow_json;
            cutflow_json["name"] = cutflow.name;
            nlohmann::json cuts_json = nlohmann::json::array();
            const double initial_count =
              (cutflow.counts.empty() ? 0.0 : cutflow.counts.front());

            for (std::size_t i = 0; i < cutflow.counts.size(); ++i)
            {
              nlohmann::json cut_json;
              cut_json["cut_index"] = i;
              cut_json["cut_name"] =
                (i == 0)
                  ? "initial"
                  : ((i - 1 < cutflow.cuts.size()) ? cutflow.cuts.at(i - 1) : "unknown_cut");
              cut_json["count"] = cutflow.counts.at(i);

              if (initial_count > 0.0)
              {
                cut_json["acceptance_cumulative"] = cutflow.counts.at(i) / initial_count;
              }
              else
              {
                cut_json["acceptance_cumulative"] = nullptr;
              }

              if (i == 0)
              {
                cut_json["acceptance_incremental"] = nullptr;
              }
              else if (cutflow.counts.at(i - 1) > 0.0)
              {
                cut_json["acceptance_incremental"] = cutflow.counts.at(i) / cutflow.counts.at(i - 1);
              }
              else
              {
                cut_json["acceptance_incremental"] = nullptr;
              }

              cuts_json.push_back(cut_json);
            }

            cutflow_json["cuts"] = cuts_json;
            cutflows_json.push_back(cutflow_json);
          }

          return cutflows_json;
        }

        nlohmann::json build_histograms_json(const Histograms& histograms)
        {
          nlohmann::json result;

          // 1D histograms
          nlohmann::json h1d_arr = nlohmann::json::array();
          for (const Histogram1D& h : histograms.histos1d)
          {
            nlohmann::json hobj;
            hobj["name"] = h.name;
            hobj["x_label"] = h.x_label;
            hobj["edges"] = h.edges;
            hobj["nbins"] = h.nbins();
            hobj["is_signal_region"] = h.is_signal_region();
            if (h.is_signal_region())
            {
              hobj["obs"] = h.obs;
              hobj["bkg"] = h.bkg;
              hobj["bkg_err"] = h.bkg_err;
            }

            nlohmann::json bins_arr = nlohmann::json::array();
            for (size_t i = 0; i < h.nbins(); ++i)
            {
              nlohmann::json bin;
              bin["bin_index"] = i;
              bin["x_low"] = h.edges[i];
              bin["x_high"] = h.edges[i + 1];
              bin["count"] = h.counts[i];
              bin["error"] = h.bin_error(i);
              bin["sumw2"] = h.sumw2[i];
              if (h.is_signal_region())
              {
                bin["n_obs"] = h.obs[i];
                bin["n_bkg"] = h.bkg[i];
                bin["n_bkg_err"] = h.bkg_err[i];
                bin["sr_label"] = h.name + "_bin" + std::to_string(i);
              }
              bins_arr.push_back(bin);
            }
            hobj["bins"] = bins_arr;
            hobj["underflow"] = h.underflow;
            hobj["overflow"] = h.overflow;
            hobj["underflow_error"] = std::sqrt(h.underflow_sumw2);
            hobj["overflow_error"] = std::sqrt(h.overflow_sumw2);
            hobj["integral"] = h.integral();
            h1d_arr.push_back(hobj);
          }
          result["1d"] = h1d_arr;

          // 2D histograms
          nlohmann::json h2d_arr = nlohmann::json::array();
          for (const Histogram2D& h : histograms.histos2d)
          {
            nlohmann::json hobj;
            hobj["name"] = h.name;
            hobj["x_label"] = h.x_label;
            hobj["y_label"] = h.y_label;
            hobj["x_edges"] = h.x_edges;
            hobj["y_edges"] = h.y_edges;
            hobj["nx_bins"] = h.nx_bins();
            hobj["ny_bins"] = h.ny_bins();

            nlohmann::json counts_2d = nlohmann::json::array();
            nlohmann::json errors_2d = nlohmann::json::array();
            nlohmann::json sumw2_2d = nlohmann::json::array();
            for (size_t ix = 0; ix < h.nx_bins(); ++ix)
            {
              counts_2d.push_back(h.counts[ix]);
              nlohmann::json err_row = nlohmann::json::array();
              nlohmann::json sw2_row = nlohmann::json::array();
              for (size_t iy = 0; iy < h.ny_bins(); ++iy)
              {
                err_row.push_back(h.bin_error(ix, iy));
                sw2_row.push_back(h.sumw2[ix][iy]);
              }
              errors_2d.push_back(err_row);
              sumw2_2d.push_back(sw2_row);
            }
            hobj["counts"] = counts_2d;
            hobj["errors"] = errors_2d;
            hobj["sumw2"] = sumw2_2d;
            hobj["overflow_total"] = h.overflow_total;
            hobj["integral"] = h.integral();
            h2d_arr.push_back(hobj);
          }
          result["2d"] = h2d_arr;

          return result;
        }

        void print_screen_summary(
          int n_events,
          double combined_loglike,
          const AnalysisDataPointers& analyses,
          const map_str_AnalysisLogLikes& analysis_loglikes,
          bool with_contur,
          double contur_total_loglike,
          const std::map<std::string, double>& contur_pool_loglikes,
          const std::map<std::string, std::string>& contur_pool_info,
          const std::vector<SamplingAdviceEntry>& sampling_advice
        )
        {
          std::stringstream summary_line;

          std::cout.precision(5);

          for (const AnalysisData* analysis_ptr : analyses)
          {
            if (analysis_ptr == nullptr) continue;

            const AnalysisData& analysis = *analysis_ptr;
            const std::string& analysis_name = analysis.analysis_name;
            const auto ll_it = analysis_loglikes.find(analysis_name);
            if (ll_it == analysis_loglikes.end())
            {
              throw std::runtime_error("Missing AnalysisLogLikes entry for analysis " + analysis_name);
            }

            const AnalysisLogLikes& ll = ll_it->second;
            summary_line << "  " << analysis_name << ":\n";

            std::cout << "Combined Cutflows for analysis " << analysis_name << ":\n";
            std::cout << analysis.cutflows << std::endl;

            for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
            {
              const SignalRegionData& sr_data = analysis[sr_index];
              const double combined_s_uncertainty = sr_data.calc_n_sig_scaled_err();
              const double combined_bg_uncertainty = sr_data.n_bkg_err;

              summary_line << "    Signal region " << sr_data.sr_label
                           << " (SR index " << sr_index << "):\n";
              summary_line << "      Observed events:        " << sr_data.n_obs << '\n';
              summary_line << "      SM prediction:          " << sr_data.n_bkg
                           << " +/- " << combined_bg_uncertainty << '\n';
              summary_line << "      Signal prediction (MC): " << sr_data.n_sig_MC
                           << " +/- " << sr_data.n_sig_MC_stat << '\n';
              summary_line << "      Signal prediction:      " << sr_data.n_sig_scaled
                           << " +/- " << combined_s_uncertainty << '\n';
              summary_line << "      Log-likelihood:         " << ll.sr_loglikes.at(sr_index) << '\n';

              for (const auto& alt_pair : ll.alt_sr_loglikes)
              {
                const std::string& alt_key = alt_pair.first;
                const std::vector<double>& alt_values = alt_pair.second;
                if (sr_index < alt_values.size())
                {
                  summary_line << "      " << alt_key
                               << " Log-Likelihood: " << alt_values[sr_index] << '\n';
                }
              }
            }

            summary_line << "    Selected signal region: " << ll.combination_sr_label << '\n';
            summary_line << "    Total log-likelihood for analysis: "
                         << ll.combination_loglike << "\n\n";
          }

          if (with_contur)
          {
            summary_line << "\nContur results:\n";
            summary_line << "Total Contur Log-Likelihood: " << contur_total_loglike << '\n';
            for (const auto& pool : contur_pool_loglikes)
            {
              const auto info_it = contur_pool_info.find(pool.first);
              const std::string dominant_measurement =
                (info_it != contur_pool_info.end()) ? info_it->second : "";
              summary_line << "\tPool " << pool.first
                           << ":\n\t\tLog-likelihood: " << pool.second
                           << "\n\t\tDominant measurement: " << dominant_measurement << '\n';
            }
          }

          if (!sampling_advice.empty())
          {
            summary_line << "\nMC sampling advice (selected SR per analysis):\n";
            for (const SamplingAdviceEntry& entry : sampling_advice)
            {
              summary_line << "  " << entry.analysis_name << " / " << entry.sr_label
                          //  << " (SR index " << entry.sr_index << "): "
                           << "\n\tS = " << entry.n_sig_scaled
                           << ", sigma_MC = " << entry.n_sig_scaled_err
                           << ", frac = " << entry.fractional_uncert
                           << ", N_eff = " << entry.effective_events << '\n';
              for (const SamplingAdviceTargetEntry& target : entry.targets)
              {
                std::ostringstream target_percent_ss;
                target_percent_ss
                  << std::fixed << std::setprecision(1)
                  << (target.target_fractional_uncert * 100.0);

                if (!target.need_more_mc)
                {
                  summary_line << "    target " << target_percent_ss.str()
                               << "%:\trequirement met\n";
                }
                else
                {
                  summary_line << "    target " << target_percent_ss.str()
                               << "%:\trequirement not met, need\n\t ->\t"
                               << target.recommended_additional_events
                               << " additional MC events\n";
                }
              }
            }
          }

          std::cout << '\n';
          std::cout << "Read and analysed " << n_events << " events from HepMC file(s).\n\n";
          std::cout << "Analysis details:\n\n" << summary_line.str() << '\n';
          std::cout << std::scientific
                    << "Total combined ATLAS+CMS"
                    << (with_contur ? " analysis and searches " : " ")
                    << "log-likelihood: " << combined_loglike
                    << '\n';
          std::cout << '\n';
        }
      }

      void validate_output_config(const OutputConfig& config)
      {
        if (config.write_file && config.output_file.empty())
        {
          throw std::runtime_error("File output requested, but output path is empty.");
        }
      }

      void emit_outputs(
        const OutputConfig& config,
        int n_events,
        double combined_loglike,
        const AnalysisDataPointers& analyses,
        const map_str_AnalysisLogLikes& analysis_loglikes,
        bool with_contur,
        double contur_total_loglike,
        const std::map<std::string, double>& contur_pool_loglikes,
        const std::map<std::string, std::string>& contur_pool_info,
        const std::vector<SamplingAdviceEntry>& sampling_advice
      )
      {
        if (config.screen_output)
        {
          print_screen_summary(
            n_events,
            combined_loglike,
            analyses,
            analysis_loglikes,
            with_contur,
            contur_total_loglike,
            contur_pool_loglikes,
            contur_pool_info,
            sampling_advice
          );
        }

        if (!config.write_file) return;

        nlohmann::json root;
        root["schema_version"] = kSchemaVersion;
        root["run"] = {
          {"n_events", n_events},
          {"with_contur", with_contur}
        };

        nlohmann::json analyses_json = nlohmann::json::object();
        nlohmann::json terms = nlohmann::json::array();
        nlohmann::json default_total_terms = nlohmann::json::array();
        std::set<std::string> enabled_variants = {"nominal"};

        for (const AnalysisData* analysis_ptr : analyses)
        {
          if (analysis_ptr == nullptr) continue;

          const AnalysisData& analysis = *analysis_ptr;
          const std::string& analysis_name = analysis.analysis_name;
          const auto ll_it = analysis_loglikes.find(analysis_name);
          if (ll_it == analysis_loglikes.end())
          {
            throw std::runtime_error("Missing AnalysisLogLikes entry for analysis " + analysis_name);
          }

          const AnalysisLogLikes& ll = ll_it->second;
          nlohmann::json analysis_obj;
          analysis_obj["n_signal_regions"] = analysis.size();
          analysis_obj["luminosity"] = analysis.luminosity;
          analysis_obj["bkgjson_path"] = analysis.bkgjson_path;

          if (analysis.srcov.rows() > 0 && analysis.srcov.cols() > 0)
          {
            nlohmann::json covariance = nlohmann::json::array();
            for (int i = 0; i < analysis.srcov.rows(); ++i)
            {
              nlohmann::json row = nlohmann::json::array();
              for (int j = 0; j < analysis.srcov.cols(); ++j)
              {
                row.push_back(analysis.srcov(i, j));
              }
              covariance.push_back(row);
            }
            analysis_obj["covariance"] = covariance;
          }

          nlohmann::json combination;
          combination["selected_sr_label"] = ll.combination_sr_label;
          combination["selected_sr_index"] = ll.combination_sr_index;
          combination["nominal_loglike"] = ll.combination_loglike;
          combination["alternatives"] = nlohmann::json::object();
          for (const auto& alt_pair : ll.alt_combination_loglikes)
          {
            combination["alternatives"][alt_pair.first] = alt_pair.second;
            enabled_variants.insert(alt_pair.first);
          }
          analysis_obj["combination"] = combination;
          analysis_obj["cutflows"] = build_cutflows_json(analysis.cutflows);
          analysis_obj["histograms"] = build_histograms_json(analysis.histograms);

          nlohmann::json signal_regions = nlohmann::json::object();
          for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
          {
            const SignalRegionData& sr_data = analysis[sr_index];
            nlohmann::json sr_obj;
            sr_obj["sr_index"] = sr_index;
            sr_obj["n_obs"] = sr_data.n_obs;
            sr_obj["n_bkg"] = sr_data.n_bkg;
            sr_obj["n_bkg_err"] = sr_data.n_bkg_err;
            sr_obj["n_sig_MC"] = sr_data.n_sig_MC;
            sr_obj["n_sig_MC_stat"] = sr_data.n_sig_MC_stat;
            sr_obj["n_sig_scaled"] = sr_data.n_sig_scaled;
            sr_obj["n_sig_scaled_err"] = sr_data.calc_n_sig_scaled_err();
            sr_obj["loglike"] = ll.sr_loglikes.at(sr_index);

            nlohmann::json sr_alt_loglikes = nlohmann::json::object();
            for (const auto& alt_pair : ll.alt_sr_loglikes)
            {
              const std::string& alt_key = alt_pair.first;
              const std::vector<double>& alt_values = alt_pair.second;
              if (sr_index < alt_values.size())
              {
                sr_alt_loglikes[alt_key] = alt_values[sr_index];
                enabled_variants.insert(alt_key);
              }
            }
            sr_obj["alt_loglikes"] = sr_alt_loglikes;
            signal_regions[sr_data.sr_label] = sr_obj;

            const std::string sr_group = "analysis_sr::" + analysis_name + "::" + sr_data.sr_label;
            append_term(
              terms,
              analysis_name + "::" + sr_data.sr_label + "::nominal",
              "signal_region",
              analysis_name,
              sr_data.sr_label,
              "nominal",
              ll.sr_loglikes.at(sr_index),
              false,
              sr_group,
              false
            );

            for (const auto& alt_pair : ll.alt_sr_loglikes)
            {
              const std::string& alt_key = alt_pair.first;
              const std::vector<double>& alt_values = alt_pair.second;
              if (sr_index < alt_values.size())
              {
                append_term(
                  terms,
                  analysis_name + "::" + sr_data.sr_label + "::" + alt_key,
                  "signal_region",
                  analysis_name,
                  sr_data.sr_label,
                  alt_key,
                  alt_values[sr_index],
                  false,
                  sr_group,
                  false
                );
              }
            }
          }
          analysis_obj["signal_regions"] = signal_regions;

          analyses_json[analysis_name] = analysis_obj;

          const std::string analysis_group = "analysis::" + analysis_name;
          const std::string nominal_term_id = analysis_name + "::combined::nominal";
          append_term(
            terms,
            nominal_term_id,
            "analysis_combined",
            analysis_name,
            "",
            "nominal",
            ll.combination_loglike,
            true,
            analysis_group,
            true
          );
          default_total_terms.push_back(nominal_term_id);

          for (const auto& alt_pair : ll.alt_combination_loglikes)
          {
            append_term(
              terms,
              analysis_name + "::combined::" + alt_pair.first,
              "analysis_combined",
              analysis_name,
              "",
              alt_pair.first,
              alt_pair.second,
              true,
              analysis_group,
              false
            );
          }
        }

        root["analyses"] = analyses_json;
        root["terms"] = terms;

        nlohmann::json summary;
        summary["n_analyses"] = analyses_json.size();
        summary["combined_loglike"] = combined_loglike;
        if (with_contur) summary["contur_loglike"] = contur_total_loglike;
        root["summary"] = summary;

        if (!sampling_advice.empty())
        {
          nlohmann::json advice_json;
          advice_json["allocation_rule"] = "cross_section_proportional";
          advice_json["analyses"] = nlohmann::json::array();

          for (const SamplingAdviceEntry& entry : sampling_advice)
          {
            nlohmann::json analysis_advice_json;
            analysis_advice_json["analysis_name"] = entry.analysis_name;
            analysis_advice_json["selected_sr_label"] = entry.sr_label;
            analysis_advice_json["selected_sr_index"] = entry.sr_index;
            analysis_advice_json["n_sig_scaled"] = entry.n_sig_scaled;
            analysis_advice_json["n_sig_scaled_err"] = entry.n_sig_scaled_err;
            analysis_advice_json["fractional_uncert"] = entry.fractional_uncert;
            analysis_advice_json["effective_events"] = entry.effective_events;
            analysis_advice_json["targets"] = nlohmann::json::array();

            for (const SamplingAdviceTargetEntry& target : entry.targets)
            {
              nlohmann::json target_json;
              target_json["target_fractional_uncert"] = target.target_fractional_uncert;
              target_json["current_fractional_uncert"] = target.current_fractional_uncert;
              target_json["need_more_mc"] = target.need_more_mc;
              target_json["scale_factor"] = target.scale_factor;
              target_json["current_total_events"] = target.current_total_events;
              target_json["recommended_total_events"] = target.recommended_total_events;
              target_json["recommended_additional_events"] = target.recommended_additional_events;
              target_json["process_recommendations"] = nlohmann::json::array();

              for (const SamplingAdviceProcessEntry& process : target.process_recommendations)
              {
                nlohmann::json process_json;
                process_json["process_name"] = process.process_name;
                process_json["cross_section_fb"] = process.cross_section_fb;
                process_json["processed_events"] = process.processed_events;
                process_json["recommended_additional_events"] = process.recommended_additional_events;
                target_json["process_recommendations"].push_back(process_json);
              }

              analysis_advice_json["targets"].push_back(target_json);
            }

            advice_json["analyses"].push_back(analysis_advice_json);
          }

          root["sampling_advice"] = advice_json;
        }

        nlohmann::json predefined_sets = nlohmann::json::object();
        predefined_sets["default_total"] = default_total_terms;
        root["predefined_sets"] = predefined_sets;

        nlohmann::json variants_json = nlohmann::json::array();
        for (const std::string& variant : enabled_variants)
        {
          variants_json.push_back(variant);
        }
        root["run"]["enabled_variants"] = variants_json;

        if (with_contur)
        {
          nlohmann::json contur_json;
          contur_json["total_loglike"] = contur_total_loglike;
          contur_json["pools"] = nlohmann::json::object();
          for (const auto& pool_pair : contur_pool_loglikes)
          {
            const std::string& pool_name = pool_pair.first;
            const double pool_loglike = pool_pair.second;
            const auto info_it = contur_pool_info.find(pool_name);
            const std::string dominant_measurement =
              (info_it != contur_pool_info.end()) ? info_it->second : "";

            nlohmann::json pool_obj;
            pool_obj["loglike"] = pool_loglike;
            pool_obj["dominant_measurement"] = dominant_measurement;
            contur_json["pools"][pool_name] = pool_obj;

            append_term(
              terms,
              "contur_pool::" + pool_name + "::nominal",
              "contur_pool",
              "",
              pool_name,
              "nominal",
              pool_loglike,
              false,
              "contur_pool::" + pool_name,
              false
            );
          }

          const std::string contur_total_term = "contur::total::nominal";
          append_term(
            terms,
            contur_total_term,
            "contur_total",
            "",
            "",
            "nominal",
            contur_total_loglike,
            true,
            "contur::total",
            true
          );
          root["terms"] = terms;
          root["predefined_sets"]["default_total"].push_back(contur_total_term);
          root["contur"] = contur_json;
        }

        write_json_to_file(root, config.output_file, kJsonIndent);
      }
    }
  }
}
