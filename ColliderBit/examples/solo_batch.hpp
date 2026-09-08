//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Batch execution and merge helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <string>
#include <vector>

#include "solo_input.hpp"

#include "gambit/ColliderBit/ColliderBit_types.hpp"
#include "gambit/Utils/yaml_options.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloBatch
    {
      struct ProcessSamplingAdvice
      {
        std::string process_name;
        double cross_section_fb = 0.0;
        long long processed_events = 0;
        long long recommended_additional_events = 0;
      };

      struct SamplingTargetAdvice
      {
        double target_fractional_uncert = 0.0;
        bool need_more_mc = false;
        double current_fractional_uncert = 0.0;
        double scale_factor = 1.0;
        long long current_total_events = 0;
        long long recommended_total_events = 0;
        long long recommended_additional_events = 0;
        std::vector<ProcessSamplingAdvice> process_recommendations;
      };

      struct AnalysisSamplingAdvice
      {
        std::string analysis_name;
        std::string sr_label;
        int sr_index = -1;
        double n_sig_scaled = 0.0;
        double n_sig_scaled_err = 0.0;
        double fractional_uncert = 0.0;
        double effective_events = 0.0;
        std::vector<SamplingTargetAdvice> targets;
      };

      struct MergedRunResult
      {
        int total_events = 0;
        long long total_process_events = 0;
        std::map<std::string, long long> process_event_counts;
        std::vector<AnalysisData> analyses_storage;
        AnalysisDataPointers analyses;
        map_str_AnalysisLogLikes analysis_loglikes;
        double combined_loglike = 0.0;
      };

      MergedRunResult run_and_merge(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      );

      std::vector<AnalysisSamplingAdvice> build_sampling_advice(
        const MergedRunResult& merged,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings
      );
    } // namespace SoloBatch
  }   // namespace ColliderBit
} // namespace Gambit
