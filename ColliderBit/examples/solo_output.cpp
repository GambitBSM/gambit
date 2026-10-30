//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Output helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_output.hpp"

#include <algorithm>
#include <cmath>
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
        std::string trim_trailing_zeros(std::string text)
        {
          if (text.find('e') != std::string::npos || text.find('E') != std::string::npos) return text;
          const auto dot = text.find('.');
          if (dot == std::string::npos) return text;
          while (!text.empty() && text.back() == '0') text.pop_back();
          if (!text.empty() && text.back() == '.') text.pop_back();
          if (text.empty() || text == "-" || text == "+") return "0";
          return text;
        }
      }

      /// At most `significant` digits, and at most four digits after the decimal.
      /// Magnitudes outside [1e-3, 1e6) use scientific notation. JSON stays exact.
      std::string format_screen_number(double value, int significant)
      {
        if (significant < 1) significant = 1;
        if (std::isnan(value)) return "nan";
        if (std::isinf(value)) return value < 0.0 ? "-inf" : "inf";
        if (value == 0.0) return "0";

        const double magnitude = std::abs(value);
        std::ostringstream formatted;
        if (magnitude >= 1.0e6 || magnitude < 1.0e-3)
        {
          formatted << std::scientific << std::setprecision(significant - 1) << value;
          const std::string text = formatted.str();
          const auto exponent = text.find_first_of("eE");
          if (exponent == std::string::npos) return text;
          return trim_trailing_zeros(text.substr(0, exponent)) + text.substr(exponent);
        }

        const int digits_before = magnitude >= 1.0
          ? static_cast<int>(std::floor(std::log10(magnitude))) + 1
          : 0;
        const int decimals = std::min(4, std::max(0, significant - digits_before));
        formatted << std::fixed << std::setprecision(decimals) << value;
        return trim_trailing_zeros(formatted.str());
      }

      namespace
      {
        // Identify the JSON format consumed by batch merging and downstream tools.
        const std::string kSchemaVersion = "cbs-solo-loglike-v2";
        const int kJsonIndent = 2;

        /// Create missing parent directories before opening an output file.
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

        /// Write formatted JSON, creating parent directories and reporting open failures.
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

        /// Append a likelihood term with its identity, variant and combination metadata.
        /// exclusive_group and selected_in_default identify alternatives and default use.
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

        /// Serialise raw cut counts and cumulative/incremental acceptances.
        /// Use JSON null when an acceptance has no positive denominator.
        nlohmann::json build_cutflows_json(const Cutflows& cutflows)
        {
          nlohmann::json cutflows_json = nlohmann::json::array();
          if (!Cutflow::check_cutflow()) return cutflows_json;

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

        /// Serialise 1D/2D binning, counts, errors and sumw2 for plots and batch merging.
        /// Include observed/background data and SR labels for 1D signal-region histograms.
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

        // Section rules keep a familiar minimum width; table columns grow to
        // retain every identifier and formatted number without truncation.
        constexpr std::size_t screen_rule_width = 80;
        constexpr std::size_t screen_column_gap = 2;

        void print_screen_cell(
          std::ostream& output,
          const std::string& value,
          std::size_t width,
          bool right_aligned = false)
        {
          output << (right_aligned ? std::right : std::left)
                 << std::setw(width) << value;
        }

        struct DecimalParts
        {
          std::string whole;
          std::string fraction;
        };

        DecimalParts split_decimal(const std::string& text)
        {
          DecimalParts parts;
          if (text.find('e') != std::string::npos || text.find('E') != std::string::npos)
          {
            parts.whole = text;
            return parts;
          }
          const auto dot = text.find('.');
          if (dot == std::string::npos)
          {
            parts.whole = text;
            return parts;
          }
          parts.whole = text.substr(0, dot);
          parts.fraction = text.substr(dot + 1);
          return parts;
        }

        // Pad numbers so their decimal points share a column. A missing "-" stays put.
        std::vector<std::string> align_number_column(const std::vector<std::string>& texts)
        {
          std::size_t whole_width = 0;
          std::size_t fraction_width = 0;
          std::vector<DecimalParts> parts(texts.size());
          for (std::size_t index = 0; index < texts.size(); ++index)
          {
            if (texts[index].empty() || texts[index] == "-") continue;
            parts[index] = split_decimal(texts[index]);
            whole_width = std::max(whole_width, parts[index].whole.size());
            fraction_width = std::max(fraction_width, parts[index].fraction.size());
          }

          const std::size_t width = whole_width + (fraction_width == 0 ? 0 : 1 + fraction_width);
          std::vector<std::string> aligned(texts.size());
          for (std::size_t index = 0; index < texts.size(); ++index)
          {
            if (texts[index].empty() || texts[index] == "-")
            {
              const std::string token = texts[index].empty() ? std::string("-") : texts[index];
              aligned[index] = token.size() >= width
                ? token
                : std::string(width - token.size(), ' ') + token;
              continue;
            }
            std::ostringstream rendered;
            rendered << std::right << std::setw(static_cast<int>(whole_width)) << parts[index].whole;
            if (fraction_width > 0)
            {
              if (parts[index].fraction.empty())
              {
                rendered << std::string(1 + fraction_width, ' ');
              }
              else
              {
                rendered << '.' << parts[index].fraction
                         << std::string(fraction_width - parts[index].fraction.size(), ' ');
              }
            }
            aligned[index] = rendered.str();
          }
          return aligned;
        }

        struct YieldText
        {
          bool missing = false;
          std::string value;
          std::string error;
        };

        // "246.7 +/- 40.55" with both sides decimal-aligned down the column.
        std::vector<std::string> align_yield_column(const std::vector<YieldText>& fields)
        {
          std::vector<std::string> values;
          std::vector<std::string> errors;
          values.reserve(fields.size());
          errors.reserve(fields.size());
          for (const YieldText& field : fields)
          {
            if (field.missing) continue;
            values.push_back(field.value);
            errors.push_back(field.error);
          }
          const std::vector<std::string> aligned_values = align_number_column(values);
          const std::vector<std::string> aligned_errors = align_number_column(errors);

          std::vector<std::string> rendered(fields.size(), "-");
          std::size_t width = 1;
          std::size_t cursor = 0;
          for (std::size_t index = 0; index < fields.size(); ++index)
          {
            if (fields[index].missing) continue;
            rendered[index] = aligned_values[cursor] + " +/- " + aligned_errors[cursor];
            width = std::max(width, rendered[index].size());
            ++cursor;
          }
          for (std::string& cell : rendered)
          {
            if (cell.size() >= width) continue;
            if (cell == "-")
            {
              const std::size_t pad = width - cell.size();
              cell = std::string(pad / 2, ' ') + cell + std::string(pad - pad / 2, ' ');
            }
            else
            {
              cell.append(width - cell.size(), ' ');
            }
          }
          return rendered;
        }

        std::string center_text(const std::string& text, std::size_t width)
        {
          if (text.size() >= width) return text;
          const std::size_t pad = width - text.size();
          return std::string(pad / 2, ' ') + text + std::string(pad - pad / 2, ' ');
        }

        YieldText missing_yield()
        {
          YieldText field;
          field.missing = true;
          return field;
        }

        YieldText yield_text(double value, double uncertainty, int significant = 4)
        {
          YieldText field;
          field.value = format_screen_number(value, significant);
          field.error = format_screen_number(uncertainty, significant);
          return field;
        }

        // Place short labels on either side of " +/- " using the same field widths
        // as the data. Empty when a label does not fit, so the caller can center
        // a plain heading instead of shifting the sign.
        std::string yield_column_header(
          const std::string& value_label,
          const std::string& error_label,
          const std::vector<std::string>& cells)
        {
          const std::string marker = " +/- ";
          for (const std::string& cell : cells)
          {
            const auto pos = cell.find(marker);
            if (pos == std::string::npos) continue;
            const std::size_t left_width = pos;
            const std::size_t right_width = cell.size() - (pos + marker.size());
            if (value_label.size() > left_width || error_label.size() > right_width) return {};
            return std::string(left_width - value_label.size(), ' ') + value_label
              + marker
              + error_label + std::string(right_width - error_label.size(), ' ');
          }
          return {};
        }

        struct AdditionalEventsText
        {
          bool met = false;
          std::string number;
          std::string suffix;
        };

        // Additional MC events. K/M/B figures are rounded up so the text is never
        // smaller than the integer recommendation.
        AdditionalEventsText format_additional_events(long long events, bool& used_suffix)
        {
          AdditionalEventsText text;
          if (events < 0) events = 0;
          const struct
          {
            double size;
            const char* suffix;
            const char* larger_suffix;
          } units[] = {
            {1.0e9, "B", nullptr},
            {1.0e6, "M", "B"},
            {1.0e3, "K", "M"},
          };

          for (const auto& unit : units)
          {
            if (static_cast<double>(events) < unit.size) continue;
            double scale = unit.size;
            const char* suffix = unit.suffix;
            const auto ceil_hundredths = [&](double unit_size)
            {
              return std::ceil(
                (static_cast<double>(events) / unit_size) * 100.0 - 1.0e-9) / 100.0;
            };
            double ceiled = ceil_hundredths(scale);
            if (ceiled >= 1000.0 && unit.larger_suffix != nullptr)
            {
              scale *= 1000.0;
              suffix = unit.larger_suffix;
              ceiled = ceil_hundredths(scale);
            }
            used_suffix = true;
            std::ostringstream formatted;
            formatted << std::fixed << std::setprecision(2) << ceiled;
            text.number = formatted.str();
            text.suffix = suffix;
            return text;
          }
          text.number = std::to_string(events);
          return text;
        }

        // "+ 51.09K MC" with the number decimal-aligned and the unit in its own column.
        std::vector<std::string> align_outcome_column(const std::vector<AdditionalEventsText>& fields)
        {
          std::vector<std::string> numbers;
          numbers.reserve(fields.size());
          std::size_t suffix_width = 0;
          for (const AdditionalEventsText& field : fields)
          {
            if (field.met) continue;
            numbers.push_back(field.number);
            suffix_width = std::max(suffix_width, field.suffix.size());
          }
          const std::vector<std::string> aligned_numbers = align_number_column(numbers);

          std::vector<std::string> rendered(fields.size());
          std::size_t width = std::string("met").size();
          std::size_t cursor = 0;
          for (std::size_t index = 0; index < fields.size(); ++index)
          {
            if (fields[index].met)
            {
              rendered[index] = "met";
              continue;
            }
            std::string suffix = fields[index].suffix;
            if (suffix.size() < suffix_width) suffix.append(suffix_width - suffix.size(), ' ');
            rendered[index] = "+" + aligned_numbers[cursor] + suffix + " MC";
            width = std::max(width, rendered[index].size());
            ++cursor;
          }
          for (std::string& cell : rendered)
          {
            if (cell.size() < width) cell.insert(0, width - cell.size(), ' ');
          }
          return rendered;
        }

        std::string format_screen_percent(double fraction)
        {
          std::ostringstream formatted;
          formatted << std::fixed << std::setprecision(1) << (fraction * 100.0) << '%';
          return formatted.str();
        }

        void print_screen_rule(
          std::ostream& output, char character = '-', std::size_t width = screen_rule_width)
        {
          output << std::string(width, character) << '\n';
        }

        struct ScreenSignalRegionRow
        {
          bool selected = false;
          std::string label;
          std::string observed;
          std::string background;
          std::string signal;
          std::string loglike;
        };

        void print_signal_region_table(
          std::ostream& output,
          const AnalysisData& analysis,
          const AnalysisLogLikes& loglikes)
        {
          std::size_t label_width = std::string("Signal region").size();
          std::size_t observed_width = std::string("Obs.").size();
          std::size_t background_width = std::string("Background").size();
          std::size_t signal_width = std::string("Signal").size();
          std::size_t loglike_width = std::string("log L").size();

          std::vector<ScreenSignalRegionRow> rows;
          std::vector<std::string> observed_texts;
          std::vector<std::string> loglike_texts;
          std::vector<YieldText> background_fields;
          std::vector<YieldText> signal_fields;
          rows.reserve(analysis.size());

          for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
          {
            const SignalRegionData& sr_data = analysis[sr_index];
            ScreenSignalRegionRow row;
            row.selected =
              loglikes.combination_sr_index == static_cast<int>(sr_index)
              || (loglikes.combination_sr_index < 0
                  && loglikes.combination_sr_label == sr_data.sr_label);
            row.label = sr_data.sr_label;
            observed_texts.push_back(format_screen_number(sr_data.n_obs));
            background_fields.push_back(yield_text(sr_data.n_bkg, sr_data.n_bkg_err));
            signal_fields.push_back(yield_text(
              sr_data.n_sig_scaled, sr_data.calc_n_sig_scaled_err()));
            loglike_texts.push_back(format_screen_number(loglikes.sr_loglikes.at(sr_index)));
            label_width = std::max(label_width, row.label.size());
            rows.push_back(std::move(row));
          }
          const std::vector<std::string> observed_column = align_number_column(observed_texts);
          const std::vector<std::string> background_column = align_yield_column(background_fields);
          const std::vector<std::string> signal_column = align_yield_column(signal_fields);
          const std::vector<std::string> loglike_column = align_number_column(loglike_texts);
          for (std::size_t index = 0; index < rows.size(); ++index)
          {
            rows[index].observed = observed_column[index];
            rows[index].background = background_column[index];
            rows[index].signal = signal_column[index];
            rows[index].loglike = loglike_column[index];
            observed_width = std::max(observed_width, rows[index].observed.size());
            background_width = std::max(background_width, rows[index].background.size());
            signal_width = std::max(signal_width, rows[index].signal.size());
            loglike_width = std::max(loglike_width, rows[index].loglike.size());
          }

          output << "  * marks the selected signal region.\n\n";
          output << "  " << ' ' << ' ';
          print_screen_cell(output, "Signal region", label_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Obs.", observed_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, center_text("Background", background_width), background_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, center_text("Signal", signal_width), signal_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "log L", loglike_width, true);
          output << '\n';
          output << "  " << '-' << ' ' << std::string(label_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(observed_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(background_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(signal_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(loglike_width, '-') << '\n';

          for (const ScreenSignalRegionRow& row : rows)
          {
            output << "  " << (row.selected ? '*' : ' ') << ' ';
            print_screen_cell(output, row.label, label_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.observed, observed_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.background, background_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.signal, signal_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.loglike, loglike_width, true);
            output << '\n';
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
            std::size_t variant_width = 52;
            std::vector<std::string> variants;
            std::vector<std::string> loglike_texts;
            for (const auto& entry : loglikes.alt_combination_loglikes)
            {
              variants.push_back(entry.first);
              loglike_texts.push_back(format_screen_number(entry.second));
              variant_width = std::max(variant_width, entry.first.size());
            }
            const std::vector<std::string> loglike_column = align_number_column(loglike_texts);
            std::size_t loglike_width = std::string("Combined log L").size();
            for (const std::string& cell : loglike_column)
              loglike_width = std::max(loglike_width, cell.size());

            output << "    ";
            print_screen_cell(output, "Variant", variant_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, "Combined log L", loglike_width, true);
            output << '\n'
                   << "    " << std::string(variant_width, '-')
                   << std::string(screen_column_gap, ' ') << std::string(loglike_width, '-') << '\n';
            for (std::size_t index = 0; index < variants.size(); ++index)
            {
              output << "    ";
              print_screen_cell(output, variants[index], variant_width);
              output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, loglike_column[index], loglike_width, true);
              output << '\n';
            }
          }

          if (!loglikes.alt_sr_loglikes.empty())
          {
            std::size_t label_width = std::string("Signal region").size();
            std::size_t variant_width = 36;
            for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
              label_width = std::max(label_width, analysis[sr_index].sr_label.size());

            struct AlternativeRow
            {
              std::string label;
              std::string variant;
            };
            std::vector<AlternativeRow> alt_rows;
            std::vector<std::string> loglike_texts;
            for (const auto& entry : loglikes.alt_sr_loglikes)
            {
              variant_width = std::max(variant_width, entry.first.size());
              for (std::size_t sr_index = 0; sr_index < analysis.size(); ++sr_index)
              {
                if (sr_index >= entry.second.size()) continue;
                alt_rows.push_back(
                  AlternativeRow{analysis[sr_index].sr_label, entry.first});
                loglike_texts.push_back(format_screen_number(entry.second[sr_index]));
              }
            }
            const std::vector<std::string> loglike_column = align_number_column(loglike_texts);
            std::size_t loglike_width = std::string("log L").size();
            for (const std::string& cell : loglike_column)
              loglike_width = std::max(loglike_width, cell.size());

            output << "\n    ";
            print_screen_cell(output, "Signal region", label_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, "Variant", variant_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, "log L", loglike_width, true);
            output << '\n'
                   << "    " << std::string(label_width, '-')
                   << std::string(screen_column_gap, ' ') << std::string(variant_width, '-')
                   << std::string(screen_column_gap, ' ') << std::string(loglike_width, '-') << '\n';
            for (std::size_t index = 0; index < alt_rows.size(); ++index)
            {
              output << "    ";
              print_screen_cell(output, alt_rows[index].label, label_width);
              output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, alt_rows[index].variant, variant_width);
              output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, loglike_column[index], loglike_width, true);
              output << '\n';
            }
          }
        }

        std::string format_screen_count(double value)
        {
          std::ostringstream formatted;
          formatted << std::fixed << std::setprecision(1) << value;
          return formatted.str();
        }

        std::string format_screen_acceptance(double numerator, double denominator)
        {
          if (denominator == 0.0) return "-";

          std::ostringstream formatted;
          formatted << std::fixed << std::setprecision(1)
                    << (100.0 * numerator / denominator) << '%';
          return formatted.str();
        }

        void print_cutflow_table(std::ostream& output, const Cutflow& cutflow)
        {
          std::size_t cut_width = 40;
          std::size_t count_width = 12;
          std::size_t cumulative_width = 10;
          std::size_t incremental_width = 10;
          for (const auto& cut : cutflow.cuts)
            cut_width = std::max(cut_width, cut.size() + 5); // "Pass " prefix
          for (std::size_t index = 0; index < cutflow.counts.size(); ++index)
          {
            count_width = std::max(count_width, format_screen_count(cutflow.counts[index]).size());
            cumulative_width = std::max(cumulative_width, format_screen_acceptance(
              cutflow.counts[index], cutflow.counts.front()).size());
            if (index > 0)
              incremental_width = std::max(incremental_width, format_screen_acceptance(
                cutflow.counts[index], cutflow.counts[index - 1]).size());
          }

          output << "  Cutflow: " << cutflow.name << '\n' << "  ";
          print_screen_cell(output, "Cut", cut_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Count", count_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "A_cumu", cumulative_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "A_incr", incremental_width, true);
          output << '\n'
                 << "  " << std::string(cut_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(count_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(cumulative_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(incremental_width, '-')
                 << '\n';

          for (std::size_t cut_index = 0; cut_index <= cutflow.ncuts; ++cut_index)
          {
            const std::string cut_name =
              (cut_index == 0)
                ? "initial"
                : ((cut_index - 1 < cutflow.cuts.size())
                    ? "Pass " + cutflow.cuts.at(cut_index - 1)
                    : "Pass (unknown)");
            const double count =
              (cut_index < cutflow.counts.size()) ? cutflow.counts.at(cut_index) : 0.0;
            const double previous_count =
              (cut_index > 0 && cut_index - 1 < cutflow.counts.size())
                ? cutflow.counts.at(cut_index - 1) : 0.0;

            output << "  ";
            print_screen_cell(output, cut_name, cut_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, format_screen_count(count), count_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(
              output, format_screen_acceptance(count, cutflow.counts.empty() ? 0.0 : cutflow.counts.front()),
              cumulative_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(
              output, cut_index == 0 ? "-" : format_screen_acceptance(count, previous_count),
              incremental_width, true);
            output << '\n';
          }
        }

        void print_cutflow_summary(std::ostream& output, const AnalysisData& analysis)
        {
          if (!Cutflow::check_cutflow() || analysis.cutflows.cfs.empty()) return;

          output << "\n  Cutflow diagnostics\n"
                 << "  " << std::string(screen_rule_width, '-') << '\n';
          for (std::size_t index = 0; index < analysis.cutflows.cfs.size(); ++index)
          {
            if (index != 0) output << '\n';
            print_cutflow_table(output, analysis.cutflows.cfs.at(index));
          }
        }

        // Contur joins jointly selected measurement paths with commas.
        std::vector<std::string> split_contur_measurements(const std::string& info)
        {
          std::vector<std::string> measurements;
          if (info.empty()) return measurements;
          std::istringstream stream(info);
          std::string measurement;
          while (std::getline(stream, measurement, ','))
            measurements.push_back(measurement);
          return measurements;
        }

        // The summary keeps one path in the cell. Further paths stay in the
        // full report and in the JSON dominant_measurement field.
        std::string compact_dominant_measurement(const std::string& info)
        {
          const std::vector<std::string> measurements = split_contur_measurements(info);
          if (measurements.empty() || measurements.front().empty()) return "-";
          if (measurements.size() == 1) return measurements.front();
          return measurements.front() + " (+"
            + std::to_string(measurements.size() - 1) + ")";
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

          struct PoolRow
          {
            std::string name;
            std::string loglike;
            std::vector<std::string> measurements;
          };
          std::vector<PoolRow> rows;
          std::vector<std::string> loglike_texts;
          std::size_t pool_width = 20;
          std::size_t measurement_width = 42;
          for (const auto& pool : contur_pool_loglikes)
          {
            PoolRow row;
            row.name = pool.first;
            loglike_texts.push_back(format_screen_number(pool.second));
            const auto info_it = contur_pool_info.find(pool.first);
            if (info_it != contur_pool_info.end())
            {
              for (const std::string& measurement : split_contur_measurements(info_it->second))
              {
                measurement_width = std::max(measurement_width, measurement.size());
                row.measurements.push_back(measurement);
              }
            }
            if (row.measurements.empty()) row.measurements.push_back("-");
            pool_width = std::max(pool_width, row.name.size());
            rows.push_back(std::move(row));
          }
          const std::vector<std::string> loglike_column = align_number_column(loglike_texts);
          std::size_t loglike_width = std::string("log L").size();
          for (std::size_t index = 0; index < rows.size(); ++index)
          {
            rows[index].loglike = loglike_column[index];
            loglike_width = std::max(loglike_width, rows[index].loglike.size());
          }

          output << "\n  ";
          print_screen_cell(output, "Pool", pool_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "log L", loglike_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Dominant measurement", measurement_width);
          output << '\n'
                 << "  " << std::string(pool_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(loglike_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(measurement_width, '-') << '\n';
          for (const PoolRow& row : rows)
          {
            for (std::size_t index = 0; index < row.measurements.size(); ++index)
            {
              output << "  ";
              print_screen_cell(output, index == 0 ? row.name : "", pool_width);
              output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, index == 0 ? row.loglike : "", loglike_width, true);
              output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, row.measurements[index], measurement_width);
              output << '\n';
            }
          }
        }

        /// One process name when it receives the whole row. A split row names
        /// each process with its own rounded share; the Outcome column stays the total.
        std::string format_sampling_process(
          const SamplingAdviceTargetEntry& target,
          bool& used_event_suffix)
        {
          std::vector<const SamplingAdviceProcessEntry*> named;
          for (const SamplingAdviceProcessEntry& process : target.process_recommendations)
          {
            if (process.recommended_additional_events > 0) named.push_back(&process);
          }
          if (!target.need_more_mc || named.empty()) return "-";
          if (named.size() == 1) return named.front()->process_name;

          std::ostringstream text;
          for (std::size_t index = 0; index < named.size(); ++index)
          {
            if (index != 0) text << ", ";
            const AdditionalEventsText share = format_additional_events(
              named[index]->recommended_additional_events, used_event_suffix);
            text << named[index]->process_name << " +" << share.number << share.suffix;
          }
          return text.str();
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
            std::string outcome;
            std::string process;
          };

          std::vector<SamplingRow> rows;
          std::vector<YieldText> signal_fields;
          std::vector<std::string> effective_texts;
          std::vector<AdditionalEventsText> outcome_fields;
          bool used_event_suffix = false;
          for (const SamplingAdviceEntry& entry : sampling_advice)
          {
            for (const SamplingAdviceTargetEntry& target : entry.targets)
            {
              SamplingRow row;
              row.analysis = entry.analysis_name;
              row.signal_region = entry.sr_label;
              signal_fields.push_back(yield_text(entry.n_sig_scaled, entry.n_sig_scaled_err));
              row.fractional_uncertainty = format_screen_percent(entry.fractional_uncert);
              effective_texts.push_back(format_screen_number(entry.effective_events, 4));
              row.target = format_screen_percent(target.target_fractional_uncert);
              if (target.need_more_mc)
              {
                outcome_fields.push_back(format_additional_events(
                  target.recommended_additional_events, used_event_suffix));
              }
              else
              {
                outcome_fields.push_back(AdditionalEventsText{});
                outcome_fields.back().met = true;
              }
              row.process = format_sampling_process(target, used_event_suffix);
              rows.push_back(std::move(row));
            }
          }
          if (rows.empty()) return;
          const std::vector<std::string> signal_column = align_yield_column(signal_fields);
          const std::vector<std::string> effective_column = align_number_column(effective_texts);
          const std::vector<std::string> outcome_column = align_outcome_column(outcome_fields);
          for (std::size_t index = 0; index < rows.size(); ++index)
          {
            rows[index].signal = signal_column[index];
            rows[index].effective_events = effective_column[index];
            rows[index].outcome = outcome_column[index];
          }

          std::string signal_header = yield_column_header("S", "MC", signal_column);
          const bool split_signal_header = !signal_header.empty();
          std::size_t analysis_width = std::string("Analysis").size();
          std::size_t sr_width = std::string("Selected SR").size();
          std::size_t signal_width = split_signal_header
            ? signal_header.size() : std::string("S +/- MC").size();
          std::size_t frac_width = std::string("MC frac.").size();
          std::size_t neff_width = std::string("N_eff").size();
          std::size_t target_width = std::string("Goal").size();
          std::size_t outcome_width = std::string("Outcome").size();
          std::size_t process_width = std::string("Process").size();
          for (const auto& row : rows)
          {
            analysis_width = std::max(analysis_width, row.analysis.size());
            sr_width = std::max(sr_width, row.signal_region.size());
            signal_width = std::max(signal_width, row.signal.size());
            frac_width = std::max(frac_width, row.fractional_uncertainty.size());
            neff_width = std::max(neff_width, row.effective_events.size());
            target_width = std::max(target_width, row.target.size());
            outcome_width = std::max(outcome_width, row.outcome.size());
            process_width = std::max(process_width, row.process.size());
          }
          if (!split_signal_header || signal_header.size() != signal_width)
            signal_header = center_text("S +/- MC", signal_width);
          const std::string outcome_header = center_text("Outcome", outcome_width);
          const auto table_width = 2 + 7 * screen_column_gap + analysis_width + sr_width
            + signal_width + frac_width + neff_width + target_width + outcome_width
            + process_width;

          output << "\nMC sampling advice\n";
          print_screen_rule(output, '-', table_width);
          output << "  ";
          print_screen_cell(output, "Analysis", analysis_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Selected SR", sr_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, signal_header, signal_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "MC frac.", frac_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "N_eff", neff_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Goal", target_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, outcome_header, outcome_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Process", process_width);
          output << '\n'
                 << "  " << std::string(analysis_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(sr_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(signal_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(frac_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(neff_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(target_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(outcome_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(process_width, '-') << '\n';
          for (const SamplingRow& row : rows)
          {
            output << "  ";
            print_screen_cell(output, row.analysis, analysis_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.signal_region, sr_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.signal, signal_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.fractional_uncertainty, frac_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.effective_events, neff_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.target, target_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.outcome, outcome_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, row.process, process_width);
            output << '\n';
          }
          std::set<std::string> named_processes;
          for (const SamplingAdviceEntry& entry : sampling_advice)
          {
            for (const SamplingAdviceTargetEntry& target : entry.targets)
            {
              for (const SamplingAdviceProcessEntry& process : target.process_recommendations)
              {
                if (process.recommended_additional_events > 0)
                  named_processes.insert(process.process_name);
              }
            }
          }
          if (named_processes.size() == 1)
          {
            output << "  Add HepMC files for " << *named_processes.begin()
                   << ", then run the same command. "
                   << "Completed files stay in the checkpoint and are merged with the new files.\n";
          }
          else if (!named_processes.empty())
          {
            output << "  Add HepMC files for the named processes, then run the same command. "
                   << "Completed files stay in the checkpoint and are merged with the new files.\n";
          }
          if (used_event_suffix)
          {
            output << "  K = 1,000, M = 1,000,000, B = 1,000,000,000. "
                   << "Additional events are rounded up.\n";
          }
        }

        std::string format_collision_energy(double collision_energy_TeV)
        {
          return format_screen_number(collision_energy_TeV, 6) + " TeV";
        }

        /// Print one row per collider: run conditions, events, cross section and analyses.
        void print_collider_table(
          std::ostream& output,
          const std::vector<ColliderSummaryEntry>& colliders)
        {
          if (colliders.empty()) return;

          std::size_t name_width = std::string("Collider").size();
          std::size_t energy_width = std::string("sqrt(s)").size();
          std::size_t events_width = std::string("Events").size();
          std::size_t analyses_width = std::string("Analyses").size();
          std::vector<YieldText> xsec_fields;
          xsec_fields.reserve(colliders.size());
          for (const auto& collider : colliders)
          {
            name_width = std::max(name_width, collider.name.size());
            energy_width = std::max(energy_width,
              format_collision_energy(collider.collision_energy_TeV).size());
            events_width = std::max(events_width, std::to_string(collider.n_events).size());
            analyses_width = std::max(analyses_width, std::to_string(collider.analyses.size()).size());
            xsec_fields.push_back(yield_text(
              collider.cross_section_fb, collider.cross_section_uncert_fb, 6));
          }
          const std::vector<std::string> xsec_column = align_yield_column(xsec_fields);
          std::size_t xsec_width = std::string("Cross section [fb]").size();
          for (const std::string& cell : xsec_column)
            xsec_width = std::max(xsec_width, cell.size());
          const std::string xsec_header = center_text("Cross section [fb]", xsec_width);
          const auto table_width = 2 + 4 * screen_column_gap + name_width + energy_width
            + events_width + xsec_width + analyses_width;

          output << "\nColliders\n";
          print_screen_rule(output, '-', table_width);
          output << "  ";
          print_screen_cell(output, "Collider", name_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "sqrt(s)", energy_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Events", events_width, true);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, xsec_header, xsec_width);
          output << std::string(screen_column_gap, ' ');
          print_screen_cell(output, "Analyses", analyses_width, true);
          output << '\n'
                 << "  " << std::string(name_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(energy_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(events_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(xsec_width, '-')
                 << std::string(screen_column_gap, ' ') << std::string(analyses_width, '-') << '\n';
          for (std::size_t index = 0; index < colliders.size(); ++index)
          {
            const ColliderSummaryEntry& collider = colliders[index];
            output << "  ";
            print_screen_cell(output, collider.name, name_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, format_collision_energy(collider.collision_energy_TeV), energy_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, std::to_string(collider.n_events), events_width, true);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, xsec_column[index], xsec_width);
            output << std::string(screen_column_gap, ' ');
            print_screen_cell(output, std::to_string(collider.analyses.size()), analyses_width, true);
            output << '\n';
          }
        }

        const SignalRegionData* selected_signal_region(
          const AnalysisData& analysis,
          const AnalysisLogLikes& loglikes)
        {
          if (loglikes.combination_sr_index >= 0)
          {
            const std::size_t index = static_cast<std::size_t>(loglikes.combination_sr_index);
            if (index < analysis.size()) return &analysis[index];
            return nullptr;
          }
          if (loglikes.combination_sr_label.empty()) return nullptr;
          for (std::size_t index = 0; index < analysis.size(); ++index)
          {
            if (analysis[index].sr_label == loglikes.combination_sr_label) return &analysis[index];
          }
          return nullptr;
        }

        void print_summary_table(
          std::ostream& output,
          const std::vector<std::string>& headers,
          const std::vector<std::vector<std::string>>& rows,
          const std::vector<bool>& right_align)
        {
          const std::size_t n_columns = headers.size();
          std::vector<std::size_t> widths(n_columns, 0);
          for (std::size_t column = 0; column < n_columns; ++column)
          {
            widths[column] = headers[column].size();
            for (const std::vector<std::string>& row : rows)
            {
              widths[column] = std::max(widths[column], row.at(column).size());
            }
          }

          const auto print_row = [&](const std::vector<std::string>& cells)
          {
            output << "  ";
            for (std::size_t column = 0; column < n_columns; ++column)
            {
              if (column != 0) output << std::string(screen_column_gap, ' ');
              print_screen_cell(output, cells[column], widths[column], right_align[column]);
            }
            output << '\n';
          };

          print_row(headers);
          output << "  ";
          for (std::size_t column = 0; column < n_columns; ++column)
          {
            if (column != 0) output << std::string(screen_column_gap, ' ');
            output << std::string(widths[column], '-');
          }
          output << '\n';
          for (const std::vector<std::string>& row : rows) print_row(row);
          output << std::left;
        }

        /// ColliderBit and Contur log L, then their sum when Contur ran.
        void print_likelihood_summary(
          std::ostream& output,
          double colliderbit_loglike,
          bool with_contur,
          double contur_loglike)
        {
          output << "\nSummary\n";
          const auto line = [&](const char* label, double value)
          {
            output << "  " << std::left << std::setw(20) << label << ": "
                   << format_screen_number(value) << '\n';
          };
          line("ColliderBit log L", colliderbit_loglike);
          if (with_contur)
          {
            line("Contur log L", contur_loglike);
            line("Total log L", colliderbit_loglike + contur_loglike);
          }
          output << std::left;
        }

        /// One row per native analysis, then the Contur pools whose log L is not
        /// zero, then the MC sampling advice. A covariance or FullLikes result has
        /// no single signal region: its SR is "all" and the yield columns are
        /// dashes. A Contur pool that
        /// joins several measurements shows the first path and a count of the
        /// rest. The full report lists every pool and every path.
        void print_compact_screen_summary(
          int n_events,
          double combined_loglike,
          const AnalysisDataPointers& analyses,
          const map_str_AnalysisLogLikes& analysis_loglikes,
          bool with_contur,
          double contur_total_loglike,
          const std::map<std::string, double>& contur_pool_loglikes,
          const std::map<std::string, std::string>& contur_pool_info,
          const std::vector<SamplingAdviceEntry>& sampling_advice)
        {
          std::cout << "\nCBS result summary\n"
                    << "  Events analysed : " << n_events << '\n';
          print_likelihood_summary(
            std::cout, combined_loglike, with_contur, contur_total_loglike);

          std::vector<std::string> analysis_names;
          std::vector<std::string> sr_labels;
          std::vector<std::string> observed_texts;
          std::vector<std::string> loglike_texts;
          std::vector<YieldText> background_fields;
          std::vector<YieldText> signal_fields;
          for (const AnalysisData* analysis_ptr : analyses)
          {
            if (analysis_ptr == nullptr) continue;
            const AnalysisData& analysis = *analysis_ptr;
            const auto ll_it = analysis_loglikes.find(analysis.analysis_name);
            if (ll_it == analysis_loglikes.end())
            {
              throw std::runtime_error(
                "Missing AnalysisLogLikes entry for analysis " + analysis.analysis_name);
            }
            const AnalysisLogLikes& loglikes = ll_it->second;
            const SignalRegionData* selected = selected_signal_region(analysis, loglikes);
            std::string sr_label = loglikes.combination_sr_label;
            if (selected != nullptr) sr_label = selected->sr_label;
            if (sr_label.empty()) sr_label = "-";

            analysis_names.push_back(analysis.analysis_name);
            sr_labels.push_back(sr_label);
            if (selected == nullptr)
            {
              observed_texts.push_back("-");
              background_fields.push_back(missing_yield());
              signal_fields.push_back(missing_yield());
            }
            else
            {
              observed_texts.push_back(format_screen_number(selected->n_obs));
              background_fields.push_back(yield_text(selected->n_bkg, selected->n_bkg_err));
              signal_fields.push_back(yield_text(
                selected->n_sig_scaled, selected->calc_n_sig_scaled_err()));
            }
            loglike_texts.push_back(format_screen_number(loglikes.combination_loglike));
          }

          if (!analysis_names.empty())
          {
            const std::vector<std::string> observed_column = align_number_column(observed_texts);
            const std::vector<std::string> background_column = align_yield_column(background_fields);
            const std::vector<std::string> signal_column = align_yield_column(signal_fields);
            const std::vector<std::string> loglike_column = align_number_column(loglike_texts);
            const auto centered_header = [](
              const std::string& label, const std::vector<std::string>& cells)
            {
              std::size_t width = label.size();
              for (const std::string& cell : cells) width = std::max(width, cell.size());
              return center_text(label, width);
            };

            std::vector<std::vector<std::string>> analysis_rows;
            for (std::size_t index = 0; index < analysis_names.size(); ++index)
            {
              analysis_rows.push_back({
                analysis_names[index],
                sr_labels[index],
                observed_column[index],
                background_column[index],
                signal_column[index],
                loglike_column[index]
              });
            }
            std::cout << "\nAnalyses\n";
            print_summary_table(
              std::cout,
              {"Analysis", "SR", "Obs.",
               centered_header("Background", background_column),
               centered_header("Signal", signal_column),
               "log L"},
              analysis_rows,
              {false, false, true, false, false, true});
          }

          if (with_contur)
          {
            std::cout << "\nContur\n";
            if (contur_pool_loglikes.empty())
            {
              std::cout << "  log L : " << format_screen_number(contur_total_loglike) << '\n';
            }
            else
            {
              std::vector<std::vector<std::string>> contur_rows;
              std::size_t omitted = 0;
              for (const auto& pool : contur_pool_loglikes)
              {
                if (pool.second == 0.0)
                {
                  ++omitted;
                  continue;
                }
                const auto info_it = contur_pool_info.find(pool.first);
                const std::string dominant =
                  (info_it != contur_pool_info.end())
                    ? compact_dominant_measurement(info_it->second) : "-";
                contur_rows.push_back({
                  pool.first,
                  dominant,
                  format_screen_number(pool.second)
                });
              }
              std::vector<std::string> contur_loglikes;
              contur_loglikes.reserve(contur_rows.size());
              for (const std::vector<std::string>& row : contur_rows) contur_loglikes.push_back(row[2]);
              const std::vector<std::string> aligned_loglikes = align_number_column(contur_loglikes);
              for (std::size_t index = 0; index < contur_rows.size(); ++index)
                contur_rows[index][2] = aligned_loglikes[index];
              if (contur_rows.empty())
              {
                std::cout << "  " << contur_pool_loglikes.size()
                          << (contur_pool_loglikes.size() == 1 ? " pool" : " pools")
                          << ", all with log L = 0\n"
                          << "  log L : " << format_screen_number(contur_total_loglike) << '\n';
              }
              else
              {
                if (omitted != 0)
                {
                  std::cout << "  " << omitted << " of " << contur_pool_loglikes.size()
                            << " pools have log L = 0 and are omitted\n\n";
                }
                print_summary_table(
                  std::cout,
                  {"Pool", "Dominant measurement", "log L"},
                  contur_rows,
                  {false, false, true});
              }
            }
          }

          print_sampling_advice(std::cout, sampling_advice);
          std::cout << '\n';
        }

        /// Print cutflows, SR yields, nominal/alternative likelihoods and the total.
        /// Include Contur results and sampling advice when supplied.
        void print_screen_summary(
          int n_events,
          const std::vector<ColliderSummaryEntry>& colliders,
          double combined_loglike,
          const AnalysisDataPointers& analyses,
          const map_str_AnalysisLogLikes& analysis_loglikes,
          bool with_contur,
          double contur_total_loglike,
          const std::map<std::string, double>& contur_pool_loglikes,
          const std::map<std::string, std::string>& contur_pool_info,
          const std::vector<SamplingAdviceEntry>& sampling_advice,
          ScreenReport screen_report
        )
        {
          if (screen_report == ScreenReport::summary)
          {
            print_compact_screen_summary(
              n_events,
              combined_loglike,
              analyses,
              analysis_loglikes,
              with_contur,
              contur_total_loglike,
              contur_pool_loglikes,
              contur_pool_info,
              sampling_advice);
            return;
          }

          std::cout << '\n';
          print_screen_rule(std::cout, '=');
          std::cout << "CBS result summary\n";
          print_screen_rule(std::cout);
          std::cout << "  Events analysed : " << n_events << '\n'
                    << "  Colliders       : " << colliders.size() << '\n'
                    << "  Native analyses : " << analyses.size() << '\n';
          print_likelihood_summary(
            std::cout, combined_loglike, with_contur, contur_total_loglike);
          print_screen_rule(std::cout, '=');
          print_collider_table(std::cout, colliders);

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
                      << "  Collider        : " << analysis.collider_name << '\n'
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

        void print_input_normalization(
          std::ostream& output,
          const std::vector<InputFileSummaryEntry>& input_files)
        {
          if (input_files.empty()) return;
          std::vector<std::vector<std::string>> rows;
          std::vector<std::string> sumw_texts;
          std::vector<std::string> sumw2_texts;
          std::vector<std::string> scale_texts;
          rows.reserve(input_files.size());
          for (const InputFileSummaryEntry& file : input_files)
          {
            rows.push_back({
              file.process,
              file.file,
              std::to_string(file.n_events),
              file.nominal_name.empty() ? "-" : file.nominal_name,
              std::to_string(file.nominal_index)
            });
            sumw_texts.push_back(format_screen_number(file.sum_weights));
            sumw2_texts.push_back(format_screen_number(file.sum_weights2));
            scale_texts.push_back(format_screen_number(file.weight_scale));
          }
          const std::vector<std::string> sumw_column = align_number_column(sumw_texts);
          const std::vector<std::string> sumw2_column = align_number_column(sumw2_texts);
          const std::vector<std::string> scale_column = align_number_column(scale_texts);
          for (std::size_t index = 0; index < rows.size(); ++index)
          {
            rows[index].push_back(sumw_column[index]);
            rows[index].push_back(sumw2_column[index]);
            rows[index].push_back(scale_column[index]);
          }
          output << "\nCBS nominal input normalization (independent positive-weight events)\n";
          print_summary_table(
            output,
            {"Process", "File", "Events", "Nominal", "Index", "sumW", "sumW2", "Scale"},
            rows,
            {false, false, true, false, true, true, true, true});
        }
      }

      ScreenReport screen_report_from_string(const std::string& value)
      {
        if (value == "summary") return ScreenReport::summary;
        if (value == "full") return ScreenReport::full;
        throw std::runtime_error(
          "settings.report must be 'summary' or 'full', got '" + value + "'.");
      }

      std::string prepare_output_directory(const std::string& output_file)
      {
        const fs::path output_path(output_file);
        fs::path directory = output_path.parent_path();
        if (directory.empty()) directory = ".";
        fs::create_directories(directory);
        return fs::weakly_canonical(directory).string();
      }

      /// Require a nonempty path when file output is enabled.
      void validate_output_config(const OutputConfig& config)
      {
        if (config.write_file && config.output_file.empty())
        {
          throw std::runtime_error("File output requested, but output path is empty.");
        }
      }

      /// Emit the requested screen summary and/or JSON result for a completed run.
      /// JSON retains per-SR data, analysis combinations, likelihood-term alternatives,
      /// histograms and optional Contur/sampling information for downstream consumers.
      void emit_outputs(
        const OutputConfig& config,
        int n_events,
        const std::vector<ColliderSummaryEntry>& colliders,
        double combined_loglike,
        const AnalysisDataPointers& analyses,
        const map_str_AnalysisLogLikes& analysis_loglikes,
        bool with_contur,
        double contur_total_loglike,
        const std::map<std::string, double>& contur_pool_loglikes,
        const std::map<std::string, std::string>& contur_pool_info,
        const std::vector<SamplingAdviceEntry>& sampling_advice,
        const std::vector<InputFileSummaryEntry>& input_files,
        const MCLoopInfo* input_loop,
        const std::vector<std::string>& rivet_analyses
      )
      {
        if (config.screen_output)
        {
          print_screen_summary(
            n_events,
            colliders,
            combined_loglike,
            analyses,
            analysis_loglikes,
            with_contur,
            contur_total_loglike,
            contur_pool_loglikes,
            contur_pool_info,
            sampling_advice,
            config.screen_report
          );
        }

        if (config.screen_output)
          print_input_normalization(std::cout, input_files);
        if (!config.write_file) return;

        nlohmann::json root;
        root["schema_version"] = kSchemaVersion;
        root["run"] = {
          {"n_events", n_events},
          {"with_contur", with_contur},
          {"check_cutflow", Cutflow::check_cutflow()}
        };

        root["run"]["input_files"] = nlohmann::json::array();
        for (const auto& file : input_files)
          root["run"]["input_files"].push_back({
            {"file", file.file}, {"process", file.process}, {"collider", file.collider},
            {"n_events", file.n_events}, {"sum_weights", file.sum_weights},
            {"sum_weights2", file.sum_weights2}, {"nominal_name", file.nominal_name},
            {"nominal_index", file.nominal_index}, {"weight_scale", file.weight_scale},
            {"process_cross_section_fb", file.process_cross_section_fb},
            {"process_cross_section_uncert_fb", file.process_cross_section_uncert_fb}});
        std::map<std::pair<std::string, std::string>, nlohmann::json> processes;
        for (const auto& file : input_files)
        {
          auto& process = processes[{file.collider, file.process}];
          if (process.is_null()) process = {{"name", file.process}, {"collider", file.collider},
            {"cross_section_fb", file.process_cross_section_fb},
            {"cross_section_uncert_fb", file.process_cross_section_uncert_fb},
            {"n_events", 0LL}, {"sum_weights", 0.0}, {"sum_weights2", 0.0},
            {"normalized_sum_weights", 0.0}, {"normalized_sum_weights2", 0.0}};
          process["n_events"] = process["n_events"].get<long long>() + file.n_events;
          process["sum_weights"] = process["sum_weights"].get<double>() + file.sum_weights;
          process["sum_weights2"] = process["sum_weights2"].get<double>() + file.sum_weights2;
          process["normalized_sum_weights"] = process["normalized_sum_weights"].get<double>()
            + file.weight_scale * file.sum_weights;
          process["normalized_sum_weights2"] = process["normalized_sum_weights2"].get<double>()
            + file.weight_scale * file.weight_scale * file.sum_weights2;
        }
        root["run"]["processes"] = nlohmann::json::array();
        for (const auto& process : processes) root["run"]["processes"].push_back(process.second);
        root["run"]["status"] = "complete";
        root["run"]["weight_normalization"] = "process_sigma_over_sum_nominal_weights";
        root["run"]["cross_section_source"] = "YAML process/event_file cross sections (fb internally)";
        root["run"]["mc_statistics"] = "Poisson sum(w^2), fixed normalization denominator";
        root["run"]["rivet_analyses"] = rivet_analyses;
        root["run"]["contur_evaluations"] = input_loop ? input_loop->contur_evaluations
                                                      : (with_contur ? colliders.size() : 0);
        if (input_loop && !input_loop->input_event_sources.empty())
        {
          root["run"]["event_sources"] = nlohmann::json::array();
          for (const auto& source : input_loop->input_event_sources)
          {
            const auto file = std::find_if(input_files.begin(), input_files.end(),
              [&](const InputFileSummaryEntry& input) { return input.file == source.file; });
            if (file == input_files.end()) throw std::runtime_error("Missing event source summary: " + source.file);
            root["run"]["event_sources"].push_back({{"iteration", source.iteration},
              {"process", file->process}, {"collider", file->collider},
              {"file", source.file}, {"file_event_index", source.file_event_index},
              {"original_event_number", source.original_event_number}});
          }
        }
        nlohmann::json colliders_json = nlohmann::json::array();
        for (const ColliderSummaryEntry& collider : colliders)
        {
          nlohmann::json collider_obj;
          collider_obj["name"] = collider.name;
          collider_obj["beam_ids"] = {collider.beam_pid_1, collider.beam_pid_2};
          collider_obj["beam_energies_GeV"] = {collider.beam_energy_1_GeV, collider.beam_energy_2_GeV};
          collider_obj["collision_energy_TeV"] = collider.collision_energy_TeV;
          collider_obj["n_files"] = collider.n_files;
          collider_obj["n_events"] = collider.n_events;
          collider_obj["cross_section_fb"] = collider.cross_section_fb;
          collider_obj["cross_section_uncert_fb"] = collider.cross_section_uncert_fb;
          collider_obj["analyses"] = collider.analyses;
          colliders_json.push_back(collider_obj);
        }
        root["run"]["colliders"] = colliders_json;

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
          analysis_obj["collider"] = analysis.collider_name;
          analysis_obj["detector"] = analysis.detector_name;
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
            sr_obj["n_sig_MC_sys"] = sr_data.n_sig_MC_sys;
            sr_obj["n_sig_MC_sumw2"] = sr_data.n_sig_MC_stat * sr_data.n_sig_MC_stat;
            if (sr_data.has_event_records) sr_obj["accepted_event_ids"] = sr_data.accepted_event_ids;
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

            // Individual SR terms are diagnostic: their combinations are represented
            // separately below to avoid counting the same data again in the default set.
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

          // Nominal and alternative combinations belong to one exclusive group.
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
        summary["n_colliders"] = colliders.size();
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
        if (config.announce_outputs)
        {
          const fs::path output_path(config.output_file);
          const fs::path printed = config.run_directory.empty()
            ? fs::absolute(output_path).lexically_normal()
            : fs::path(config.run_directory) / output_path.filename();
          std::cout << "Wrote " << printed.string() << std::endl;
          for (const std::string& log_path : config.contur_logs)
            std::cout << "Contur log: " << log_path << std::endl;
          for (const std::string& yoda_path : config.yoda_files)
            std::cout << "YODA: " << yoda_path << std::endl;
        }
      }
    }
  }
}
