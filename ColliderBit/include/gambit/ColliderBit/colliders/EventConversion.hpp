//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Conversion of generator-neutral event records (and of HepMC events,
///  via such a record) into unsmeared HEPUtils events.
///
///  This is where ColliderBit defines what a prompt lepton or photon is,
///  which particles enter the jet clustering, how b, c, tau, W, Z and
///  Higgs candidates are identified, the acceptance cut, and the missing
///  momentum. Every event generator goes through this same code.
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
///  \author Are Raklev  June 2021
///  \author Chris Chang Nov 2023
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#pragma once

#include <string>
#include <vector>

#include "HEPUtils/Event.h"
#include "gambit/ColliderBit/colliders/EventRecord.hpp"
#include "gambit/ColliderBit/colliders/HepMCEventRecord.hpp"
#include "gambit/ColliderBit/jet_collection_settings.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Convert a hadron-level event record into an unsmeared HEPUtils::Event.
    /// Raises a ColliderBit error if a final-state parton is found.
    void convertParticleEvent(const EventRecord& record, HEPUtils::Event& result,
                              const std::vector<jet_collection_settings>& all_jet_collection_settings,
                              const std::string& jetcollection_taus, double jet_pt_min);

    /// Convert a parton-level (no hadrons) event record into an unsmeared HEPUtils::Event.
    void convertPartonEvent(const EventRecord& record, HEPUtils::Event& result,
                            const std::vector<jet_collection_settings>& all_jet_collection_settings,
                            const std::string& jetcollection_taus, double jet_pt_min);

  }
}
