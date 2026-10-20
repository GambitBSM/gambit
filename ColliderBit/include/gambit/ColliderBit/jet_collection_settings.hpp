//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Settings for a jet collection, and the mapping from the names used in
///  yaml files to FastJet's enums.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#pragma once

#include <stdexcept>
#include <string>

#include "HEPUtils/FastJet.h"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Settings for one jet collection
    struct jet_collection_settings
    {
      std::string key;
      std::string algorithm;
      double R;
      std::string recombination_scheme;
      std::string strategy;
    };

    /// FastJet jet algorithm from its name in a yaml file
    inline FJNS::JetAlgorithm FJalgorithm_map(const std::string& algorithm)
    {
      if (algorithm == "antikt") return FJNS::antikt_algorithm;
      if (algorithm == "cambridge") return FJNS::cambridge_algorithm;
      if (algorithm == "kt") return FJNS::kt_algorithm;
      if (algorithm == "genkt") return FJNS::genkt_algorithm;
      if (algorithm == "cambridge_for_passive") return FJNS::cambridge_for_passive_algorithm;
      throw std::invalid_argument("Unknown jet algorithm '" + algorithm + "'. Please add it to FJalgorithm_map in ColliderBit/include/gambit/ColliderBit/jet_collection_settings.hpp.");
    }

    /// FastJet clustering strategy from its name in a yaml file
    inline FJNS::Strategy FJstrategy_map(const std::string& strategy)
    {
      if (strategy == "Best") return FJNS::Best;
      if (strategy == "NlnN") return FJNS::NlnN;
      throw std::invalid_argument("Unknown jet strategy '" + strategy + "'. Please add it to FJstrategy_map in ColliderBit/include/gambit/ColliderBit/jet_collection_settings.hpp.");
    }

    /// FastJet recombination scheme from its name in a yaml file
    inline FJNS::RecombinationScheme FJRecomScheme_map(const std::string& reco_scheme)
    {
      if (reco_scheme == "E_scheme") return FJNS::E_scheme;
      if (reco_scheme == "pt_scheme") return FJNS::pt_scheme;
      if (reco_scheme == "pt2_scheme") return FJNS::pt2_scheme;
      throw std::invalid_argument("Unknown jet recombination scheme '" + reco_scheme + "'. Please add it to FJRecomScheme_map in ColliderBit/include/gambit/ColliderBit/jet_collection_settings.hpp.");
    }

  }
}
