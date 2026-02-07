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

#include "gambit/ColliderBit/ColliderBit_types.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloOutput
    {
      struct OutputConfig
      {
        bool screen_output = true;
        bool write_file = false;
        std::string output_file;
        std::string output_format = "json";
        std::string schema_version = "cbs-solo-loglike-v1";
        int json_indent = 2;
      };

      void validate_output_config(const OutputConfig& config);

      void emit_outputs(
        const OutputConfig& config,
        int n_events,
        double combined_loglike,
        const AnalysisDataPointers& analyses,
        const map_str_AnalysisLogLikes& analysis_loglikes,
        bool with_contur,
        double contur_total_loglike,
        const std::map<std::string, double>& contur_pool_loglikes,
        const std::map<std::string, std::string>& contur_pool_info
      );
    }
  }
}
