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
      struct MergedRunResult
      {
        int total_events = 0;
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
    } // namespace SoloBatch
  }   // namespace ColliderBit
} // namespace Gambit

