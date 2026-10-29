//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Output helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "gambit/ColliderBit/ColliderBit_types.hpp"
#include "gambit/ColliderBit/MCLoopInfo.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloOutput
    {
      struct InputFileSummaryEntry
      {
        std::string file, process, collider;
        long long n_events = 0;
        double sum_weights = 0.0, sum_weights2 = 0.0;
        std::string nominal_name;
        int nominal_index = -1;
        double weight_scale = 1.0;
        double process_cross_section_fb = 0.0, process_cross_section_uncert_fb = 0.0;
      };
      /// Terminal layout. JSON output is unaffected by this choice.
      enum class ScreenReport
      {
        summary,
        full
      };

      /// Independently enable terminal output and JSON output to the specified path.
      struct OutputConfig
      {
        bool screen_output = true;
        bool write_file = false;
        std::string output_file;
        ScreenReport screen_report = ScreenReport::summary;
        // Directory holding the JSON, Contur log and optional YODA file.
        // Empty when this run does not group those files.
        std::string run_directory;
        // Child collider processes write artifacts into the parent's run
        // directory and leave the closing path announcement to the parent.
        bool announce_outputs = true;
        bool write_yoda_file = false;
        std::vector<std::string> contur_logs;
        std::vector<std::string> yoda_files;
      };

      /// Create the directory containing output_file and return its absolute path.
      /// An output name with no directory uses the current directory.
      std::string prepare_output_directory(const std::string& output_file);

      /// Short fixed-point or scientific text for the screen. JSON keeps full precision.
      std::string format_screen_number(double value, int significant = 6);

      /// Accept "summary" or "full".
      ScreenReport screen_report_from_string(const std::string& value);

      /// Run conditions, inputs and normalisation of one CBS collider, with cross section in fb.
      struct ColliderSummaryEntry
      {
        std::string name;
        int beam_pid_1 = 0;
        int beam_pid_2 = 0;
        double beam_energy_1_GeV = 0.0;
        double beam_energy_2_GeV = 0.0;
        double collision_energy_TeV = 0.0;
        std::size_t n_files = 0;
        long long n_events = 0;
        double cross_section_fb = 0.0;
        double cross_section_uncert_fb = 0.0;
        std::vector<std::string> analyses;
      };

      /// Printable sampling allocation for one physics process, with cross section in fb.
      struct SamplingAdviceProcessEntry
      {
        std::string process_name;
        double cross_section_fb = 0.0;
        long long processed_events = 0;
        long long recommended_additional_events = 0;
      };

      /// Printable event budget and process allocations for one MC uncertainty target.
      struct SamplingAdviceTargetEntry
      {
        double target_fractional_uncert = 0.0;
        bool need_more_mc = false;
        double current_fractional_uncert = 0.0;
        double scale_factor = 1.0;
        long long current_total_events = 0;
        long long recommended_total_events = 0;
        long long recommended_additional_events = 0;
        std::vector<SamplingAdviceProcessEntry> process_recommendations;
      };

      /// Printable signal uncertainty and sampling targets for one selected signal region.
      struct SamplingAdviceEntry
      {
        std::string analysis_name;
        std::string sr_label;
        int sr_index = -1;
        double n_sig_scaled = 0.0;
        double n_sig_scaled_err = 0.0;
        double fractional_uncert = 0.0;
        double effective_events = 0.0;
        std::vector<SamplingAdviceTargetEntry> targets;
      };

      /// Reject an empty path when JSON file output is requested.
      void validate_output_config(const OutputConfig& config);

      /// Write the configured terminal and JSON results for a single or merged run.
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
        const std::vector<SamplingAdviceEntry>& sampling_advice = std::vector<SamplingAdviceEntry>(),
        const std::vector<InputFileSummaryEntry>& input_files = {},
        const MCLoopInfo* input_loop = nullptr,
        const std::vector<std::string>& rivet_analyses = {}
      );
    }
  }
}
