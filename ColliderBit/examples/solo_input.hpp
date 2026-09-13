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
      /// A checked HepMC input path; event counts are read from the file at run time.
      struct HepMCFileInput
      {
        str filename;
      };

      /// Files sampling one physics process, with cross section and absolute error in fb.
      struct ProcessInput
      {
        str name;
        double cross_section_fb = 0.0;
        double cross_section_uncert_fb = 0.0;
        std::vector<HepMCFileInput> files;
      };

      /// Resolved settings, retained analyses and validated event-file specifications.
      /// Preserve physics-process membership alongside the flat list of input paths.
      struct PreparedInput
      {
        YAML::Node infile;
        std::vector<str> analyses;
        std::vector<str> analysis_warnings;
        Options settings;

        std::vector<ProcessInput> processes;

        std::vector<str> hepmc_filenames;

        double total_cross_section_fb = 0.0;
        double total_cross_section_uncert_fb = 0.0;
      };

      /// Parse CBS YAML and prepare a flat list of HepMC files.
      PreparedInput parse_and_prepare_input(const std::string& filename_in);
    }
  }
}
