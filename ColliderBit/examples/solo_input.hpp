//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Input parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/yaml_options.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloInput
    {
      struct HepMCFileInput
      {
        str filename;
      };

      struct ProcessInput
      {
        str name;
        double cross_section_fb = 0.0;
        double cross_section_uncert_fb = 0.0;
        std::vector<HepMCFileInput> files;
      };

      /// Run conditions extracted from the first physical HepMC event.
      struct HepMCRunInfo
      {
        int beam_pid_1 = 0;
        int beam_pid_2 = 0;
        double beam_energy_1_GeV = 0.0;
        double beam_energy_2_GeV = 0.0;
        double collision_energy_TeV = 0.0;
      };

      struct PreparedInput
      {
        YAML::Node infile;
        std::vector<str> requested_analyses;
        std::vector<str> analyses;
        std::vector<str> analysis_warnings;
        Options settings;

        std::vector<ProcessInput> processes;

        std::vector<str> hepmc_filenames;
        std::vector<HepMCRunInfo> hepmc_run_infos;

        HepMCRunInfo run_info;
        double collision_energy_TeV = 0.0;
        double total_cross_section_fb = 0.0;
        double total_cross_section_uncert_fb = 0.0;
      };

      /// Parse CBS YAML and prepare a flat list of HepMC files.
      PreparedInput parse_and_prepare_input(const std::string& filename_in);
    }
  }
}
