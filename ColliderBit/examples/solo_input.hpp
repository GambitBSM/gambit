//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Input parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <cstddef>
#include <map>
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
      /// All files of a process share one set of run conditions, and so one collider.
      struct ProcessInput
      {
        str name;
        double cross_section_fb = 0.0;
        double cross_section_uncert_fb = 0.0;
        std::vector<HepMCFileInput> files;
        str collider_name;
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

      /// HepMC inputs sharing one set of beams and collision energy, named after
      /// them (e.g. CBS_pp_13TeV).  Its analyses are evaluated on these files only,
      /// normalised to the summed cross section of the collider's processes.
      struct ColliderInput
      {
        str name;
        HepMCRunInfo run_info;
        std::vector<std::size_t> process_indices;
        std::vector<str> hepmc_filenames;
        std::vector<str> analyses;
        double cross_section_fb = 0.0;
        double cross_section_uncert_fb = 0.0;
      };

      /// Resolved settings, retained analyses and validated event-file specifications.
      /// Preserve physics-process membership alongside the flat list of input paths.
      struct PreparedInput
      {
        YAML::Node infile;
        std::vector<str> requested_analyses;
        std::vector<str> analyses;
        std::map<str, str> analysis_disable_reasons;
        std::vector<str> analysis_warnings;
        Options settings;

        std::vector<ProcessInput> processes;

        std::vector<str> hepmc_filenames;
        std::vector<HepMCRunInfo> hepmc_run_infos;

        /// Colliders in order of first appearance, and the collider of each retained analysis.
        std::vector<ColliderInput> colliders;
        std::map<str, str> analysis_colliders;
      };

      /// Parse CBS YAML, group the HepMC files into colliders by their run
      /// conditions and assign each retained analysis to its collider.
      PreparedInput parse_and_prepare_input(const std::string& filename_in);

      /// Return the prepared collider with the given name.
      const ColliderInput& find_collider(const PreparedInput& prepared, const str& collider_name);
    }
  }
}
