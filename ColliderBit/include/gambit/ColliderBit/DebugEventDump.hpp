//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  DEBUG ONLY utility: stash the current HepMC event
///  per OMP thread, so that a single Analysis under
///  debugging can access the full-info HepMC event
///  matching the HEPUtils::Event it receives via the
///  normal Analysis::run() interface.
///
///  Not wired into any analysis by default. Remove this
///  file (and its uses) once debugging is done.
///
///  *********************************************

#pragma once

#ifndef EXCLUDE_HEPMC

#include <map>
#include <omp.h>
#include "HepMC3/GenEvent.h"

namespace Gambit
{

  namespace ColliderBit
  {

    namespace DebugEventDump
    {

      /// Thread-keyed stash of a pointer to the current iteration's HepMC event.
      /// Mirrors the thread-keyed map pattern used by AnalysisContainer::instances_map.
      inline std::map<int,const HepMC3::GenEvent*>& current_events()
      {
        static std::map<int,const HepMC3::GenEvent*> events;
        return events;
      }

      /// Record the HepMC event for the current thread. Only valid for the
      /// lifetime of the referenced event (i.e. the current loop iteration).
      inline void set_current_event(const HepMC3::GenEvent& ge)
      {
        current_events()[omp_get_thread_num()] = &ge;
      }

      /// Retrieve the HepMC event stashed for the current thread, or nullptr if none.
      inline const HepMC3::GenEvent* get_current_event()
      {
        auto it = current_events().find(omp_get_thread_num());
        return (it == current_events().end()) ? nullptr : it->second;
      }

    }

  }

}

#endif // EXCLUDE_HEPMC
