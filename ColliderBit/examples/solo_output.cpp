//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Output helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_output.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <nlohmann/json.hpp>

#include <filesystem>
namespace fs = std::filesystem;

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

        constexpr std::size_t screen_rule_width = 100;

        std::string format_screen_number(double value)
        {
          std::ostringstream formatted;
          formatted << std::setprecision(6) << std::defaultfloat << value;
          return formatted.str();
        }

        std::string format_screen_uncertainty(double value, double uncertainty)
        {
          return format_screen_number(value) + " +/- " + format_screen_number(uncertainty);
        }

        std::string format_screen_percent(double fraction)
        {
          std::ostringstream formatted;
          formatted << std::fixed << std::setprecision(1) << (fraction * 100.0) << '%';
          return formatted.str();
        }

        void print_screen_rule(std::ostream& output, char character = '-')
        {
          output << std::string(screen_rule_width, character) << '\n';
        }

        struct ScreenSignalRegionRow
        {
          bool selected = false;
          std::string label;
          std::string observed;
          std::string background;
          std::string signal_mc;
          std::string signal;
          std::string loglike;
        };

        void print_signal_region_table(
          std::ostream& output,
          const AnalysisData& analysis,
          const AnalysisLogLikes& loglikes)
        {
          std::vector<ScreenSignalRegionRow> rows;
          rows.reserve(analysis.size());

          std::size_t label_width = std::string("Signal region").size();
          std::size_t observed_width = std::string("Obs.").size();
          std::size_t background_width = std::string("Background").size();
          std::size_t signal_mc_width = std::string("Signal (MC)").size();
          std::size_t signal_width = std::string("Signal").size();
          std::size_t loglike_width = std::string("log L").size();

          for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
          {
            const SignalRegionData& sr_data = analysis[sr_index];
            ScreenSignalRegionRow row;
            row.selected =
              loglikes.combination_sr_index == static_cast<int>(sr_index)
              || (loglikes.combination_sr_index < 0
                  && loglikes.combination_sr_label == sr_data.sr_label);
            row.label = sr_data.sr_label;
            row.observed = format_screen_number(sr_data.n_obs);
            row.background = format_screen_uncertainty(sr_data.n_bkg, sr_data.n_bkg_err);
            row.signal_mc = format_screen_uncertainty(sr_data.n_sig_MC, sr_data.n_sig_MC_stat);
            row.signal = format_screen_uncertainty(
              sr_data.n_sig_scaled, sr_data.calc_n_sig_scaled_err());
            row.loglike = format_screen_number(loglikes.sr_loglikes.at(sr_index));

            label_width = std::max(label_width, row.label.size());
            observed_width = std::max(observed_width, row.observed.size());
            background_width = std::max(background_width, row.background.size());
            signal_mc_width = std::max(signal_mc_width, row.signal_mc.size());
            signal_width = std::max(signal_width, row.signal.size());
            loglike_width = std::max(loglike_width, row.loglike.size());
            rows.push_back(std::move(row));
          }

          output << "  * marks the selected signal region.\n\n";
          output << "  " << ' ' << ' ' << std::left << std::setw(label_width) << "Signal region"
                 << "  " << std::right << std::setw(observed_width) << "Obs."
                 << "  " << std::setw(background_width) << "Background"
                 << "  " << std::setw(signal_mc_width) << "Signal (MC)"
                 << "  " << std::setw(signal_width) << "Signal"
                 << "  " << std::setw(loglike_width) << "log L" << '\n';
          output << "  " << '-' << ' ' << std::string(label_width, '-')
                 << "  " << std::string(observed_width, '-')
                 << "  " << std::string(background_width, '-')
                 << "  " << std::string(signal_mc_width, '-')
                 << "  " << std::string(signal_width, '-')
                 << "  " << std::string(loglike_width, '-') << '\n';

          for (const ScreenSignalRegionRow& row : rows)
          {
            output << "  " << (row.selected ? '*' : ' ') << ' '
                   << std::left << std::setw(label_width) << row.label
                   << "  " << std::right << std::setw(observed_width) << row.observed
                   << "  " << std::setw(background_width) << row.background
                   << "  " << std::setw(signal_mc_width) << row.signal_mc
                   << "  " << std::setw(signal_width) << row.signal
                   << "  " << std::setw(loglike_width) << row.loglike << '\n';
          }
        }

        void print_alternative_loglikes(
          std::ostream& output,
          const AnalysisData& analysis,
          const AnalysisLogLikes& loglikes)
        {
          if (loglikes.alt_sr_loglikes.empty() && loglikes.alt_combination_loglikes.empty()) return;

          output << "\n  Alternative log-likelihoods\n";
          if (!loglikes.alt_combination_loglikes.empty())
          {
            std::size_t variant_width = std::string("Variant").size();
            std::size_t loglike_width = std::string("Combined log L").size();
            for (const auto& entry : loglikes.alt_combination_loglikes)
            {
              variant_width = std::max(variant_width, entry.first.size());
              loglike_width = std::max(loglike_width, format_screen_number(entry.second).size());
            }

            output << "    " << std::left << std::setw(variant_width) << "Variant"
                   << "  " << std::right << std::setw(loglike_width) << "Combined log L" << '\n'
                   << "    " << std::string(variant_width, '-')
                   << "  " << std::string(loglike_width, '-') << '\n';
            for (const auto& entry : loglikes.alt_combination_loglikes)
            {
              output << "    " << std::left << std::setw(variant_width) << entry.first
                     << "  " << std::right << std::setw(loglike_width)
                     << format_screen_number(entry.second) << '\n';
            }
          }

          if (!loglikes.alt_sr_loglikes.empty())
          {
            std::size_t label_width = std::string("Signal region").size();
            std::size_t variant_width = std::string("Variant").size();
            std::size_t loglike_width = std::string("log L").size();
            for (const auto& entry : loglikes.alt_sr_loglikes)
            {
              variant_width = std::max(variant_width, entry.first.size());
              for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
              {
                label_width = std::max(label_width, analysis[sr_index].sr_label.size());
                if (sr_index < entry.second.size())
                {
                  loglike_width = std::max(
                    loglike_width, format_screen_number(entry.second[sr_index]).size());
                }
              }
            }

            output << "\n    " << std::left << std::setw(label_width) << "Signal region"
                   << "  " << std::setw(variant_width) << "Variant"
                   << "  " << std::right << std::setw(loglike_width) << "log L" << '\n'
                   << "    " << std::string(label_width, '-')
                   << "  " << std::string(variant_width, '-')
                   << "  " << std::string(loglike_width, '-') << '\n';
            for (const auto& entry : loglikes.alt_sr_loglikes)
            {
              for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
              {
                if (sr_index >= entry.second.size()) continue;
                output << "    " << std::left << std::setw(label_width)
                       << analysis[sr_index].sr_label
                       << "  " << std::setw(variant_width) << entry.first
                       << "  " << std::right << std::setw(loglike_width)
                       << format_screen_number(entry.second[sr_index]) << '\n';
              }
            }
          }
        }

        void print_cutflow_summary(std::ostream& output, const AnalysisData& analysis)
        {
          if (analysis.cutflows.cfs.empty()) return;

          output << "\n  Cutflow diagnostics\n"
                 << "  " << std::string(80, '-') << '\n'
                 << analysis.cutflows;
        }

        void print_contur_summary(
          std::ostream& output,
          double contur_total_loglike,
          const std::map<std::string, double>& contur_pool_loglikes,
          const std::map<std::string, std::string>& contur_pool_info)
        {
          output << "\n[Contur]\n"
                 << "  Total log L : " << format_screen_number(contur_total_loglike) << '\n';
          if (contur_pool_loglikes.empty()) return;

          std::size_t pool_width = std::string("Pool").size();
          std::size_t loglike_width = std::string("log L").size();
          std::size_t measurement_width = std::string("Dominant measurement").size();
          for (const auto& pool : contur_pool_loglikes)
          {
            pool_width = std::max(pool_width, pool.first.size());
            loglike_width = std::max(loglike_width, format_screen_number(pool.second).size());
            const auto info_it = contur_pool_info.find(pool.first);
            if (info_it != contur_pool_info.end())
            {
              measurement_width = std::max(measurement_width, info_it->second.size());
            }
          }

          output << "\n  " << std::left << std::setw(pool_width) << "Pool"
                 << "  " << std::right << std::setw(loglike_width) << "log L"
                 << "  " << std::left << std::setw(measurement_width) << "Dominant measurement" << '\n'
                 << "  " << std::string(pool_width, '-')
                 << "  " << std::string(loglike_width, '-')
                 << "  " << std::string(measurement_width, '-') << '\n';
          for (const auto& pool : contur_pool_loglikes)
          {
            const auto info_it = contur_pool_info.find(pool.first);
            const std::string dominant_measurement =
              (info_it != contur_pool_info.end()) ? info_it->second : "-";
            output << "  " << std::left << std::setw(pool_width) << pool.first
                   << "  " << std::right << std::setw(loglike_width)
                   << format_screen_number(pool.second)
                   << "  " << std::left << std::setw(measurement_width)
                   << dominant_measurement << '\n';
          }
        }

        void print_sampling_advice(
          std::ostream& output,
          const std::vector<SamplingAdviceEntry>& sampling_advice)
        {
          if (sampling_advice.empty()) return;

          struct SamplingRow
          {
            std::string analysis;
            std::string signal_region;
            std::string signal;
            std::string fractional_uncertainty;
            std::string effective_events;
            std::string target;
            std::string status;
            std::string additional_events;
          };

          std::vector<SamplingRow> rows;
          for (const SamplingAdviceEntry& entry : sampling_advice)
          {
            for (const SamplingAdviceTargetEntry& target : entry.targets)
            {
              SamplingRow row;
              row.analysis = entry.analysis_name;
              row.signal_region = entry.sr_label;
              row.signal = format_screen_uncertainty(entry.n_sig_scaled, entry.n_sig_scaled_err);
              row.fractional_uncertainty = format_screen_percent(entry.fractional_uncert);
              row.effective_events = format_screen_number(entry.effective_events);
              row.target = format_screen_percent(target.target_fractional_uncert);
              row.status = target.need_more_mc ? "need more MC" : "met";
              row.additional_events = target.need_more_mc
                ? std::to_string(target.recommended_additional_events) : "-";
              rows.push_back(std::move(row));
            }
          }
          if (rows.empty()) return;

          std::size_t analysis_width = std::string("Analysis").size();
          std::size_t sr_width = std::string("Selected SR").size();
          std::size_t signal_width = std::string("Signal +/- MC").size();
          std::size_t frac_width = std::string("MC frac.").size();
          std::size_t neff_width = std::string("N_eff").size();
          std::size_t target_width = std::string("Target").size();
          std::size_t status_width = std::string("Status").size();
          std::size_t extra_width = std::string("Extra MC events").size();
          for (const SamplingRow& row : rows)
          {
            analysis_width = std::max(analysis_width, row.analysis.size());
            sr_width = std::max(sr_width, row.signal_region.size());
            signal_width = std::max(signal_width, row.signal.size());
            frac_width = std::max(frac_width, row.fractional_uncertainty.size());
            neff_width = std::max(neff_width, row.effective_events.size());
            target_width = std::max(target_width, row.target.size());
            status_width = std::max(status_width, row.status.size());
            extra_width = std::max(extra_width, row.additional_events.size());
          }

          output << "\nMC sampling advice\n";
          print_screen_rule(output);
          output << "  " << std::left << std::setw(analysis_width) << "Analysis"
                 << "  " << std::setw(sr_width) << "Selected SR"
                 << "  " << std::setw(signal_width) << "Signal +/- MC"
                 << "  " << std::right << std::setw(frac_width) << "MC frac."
                 << "  " << std::setw(neff_width) << "N_eff"
                 << "  " << std::setw(target_width) << "Target"
                 << "  " << std::left << std::setw(status_width) << "Status"
                 << "  " << std::right << std::setw(extra_width) << "Extra MC events" << '\n';
          output << "  " << std::string(analysis_width, '-')
                 << "  " << std::string(sr_width, '-')
                 << "  " << std::string(signal_width, '-')
                 << "  " << std::string(frac_width, '-')
                 << "  " << std::string(neff_width, '-')
                 << "  " << std::string(target_width, '-')
                 << "  " << std::string(status_width, '-')
                 << "  " << std::string(extra_width, '-') << '\n';
          for (const SamplingRow& row : rows)
          {
            output << "  " << std::left << std::setw(analysis_width) << row.analysis
                   << "  " << std::setw(sr_width) << row.signal_region
                   << "  " << std::setw(signal_width) << row.signal
                   << "  " << std::right << std::setw(frac_width) << row.fractional_uncertainty
                   << "  " << std::setw(neff_width) << row.effective_events
                   << "  " << std::setw(target_width) << row.target
                   << "  " << std::left << std::setw(status_width) << row.status
                   << "  " << std::right << std::setw(extra_width) << row.additional_events << '\n';
          }
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
          std::cout << '\n';
          print_screen_rule(std::cout, '=');
          std::cout << "CBS result summary\n";
          print_screen_rule(std::cout);
          std::cout << "  Events analysed : " << n_events << '\n'
                    << "  Native analyses : " << analyses.size() << '\n'
                    << "  Combined log L  : " << format_screen_number(combined_loglike) << '\n';
          if (with_contur)
          {
            std::cout << "  Contur          : included\n";
          }
          print_screen_rule(std::cout, '=');

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

            const AnalysisLogLikes& loglikes = ll_it->second;
            std::cout << "\n[" << analysis_name << "]\n"
                      << "  Selected result : " << loglikes.combination_sr_label;
            if (loglikes.combination_sr_index >= 0)
            {
              std::cout << " (SR index " << loglikes.combination_sr_index << ')';
            }
            std::cout << '\n'
                      << "  Analysis log L  : " << format_screen_number(loglikes.combination_loglike)
                      << "\n\n";
            print_signal_region_table(std::cout, analysis, loglikes);
            print_alternative_loglikes(std::cout, analysis, loglikes);
            print_cutflow_summary(std::cout, analysis);
          }

          if (with_contur)
          {
            print_contur_summary(
              std::cout, contur_total_loglike, contur_pool_loglikes, contur_pool_info);
          }
          print_sampling_advice(std::cout, sampling_advice);
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
