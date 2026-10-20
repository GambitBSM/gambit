//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Filling of a generator-neutral event record from a HepMC3 event.
///  Kept free of other GAMBIT headers so that it can be compiled and
///  tested on its own.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#pragma once

#ifndef EXCLUDE_HEPMC

#include "HepMC3/GenEvent.h"
#include "gambit/ColliderBit/colliders/EventRecord.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Fill an event record from a HepMC3 event. Record index i holds the HepMC
    /// particle at position i-1 of GenEvent::particles(); entry 0 is left empty.
    /// Final-state particles are those with status 1; the parton and hadron flags
    /// are set from the PDG code, counting diquarks as partons.
    void fillEventRecord(const HepMC3::GenEvent& event, EventRecord& record);

  }
}

#endif // EXCLUDE_HEPMC
