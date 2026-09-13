//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Output helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <map>
#include <string>
#include <vector>

#include "gambit/ColliderBit/ColliderBit_types.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloOutput
    {
      /// Independently enable terminal output and JSON output to the specified path.
      struct OutputConfig
      {
        bool screen_output = true;
        bool write_file = false;
        std::string output_file;
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
        double combined_loglike,
        const AnalysisDataPointers& analyses,
        const map_str_AnalysisLogLikes& analysis_loglikes,
        bool with_contur,
        double contur_total_loglike,
        const std::map<std::string, double>& contur_pool_loglikes,
        const std::map<std::string, std::string>& contur_pool_info,
        const std::vector<SamplingAdviceEntry>& sampling_advice = std::vector<SamplingAdviceEntry>()
      );
    }
  }
}
