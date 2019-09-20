//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  collider Monte Carlo events.
///
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Andy Buckley
///
///  \author Chris Rogan
///          (crogan@cern.ch)
///  \date 2014 Aug
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2018 Jan
///  \date 2019 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date   2017 March
///  \date   2018 Jan
///  \date   2018 May
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

 #define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// Generate a hard scattering event with Pythia
    template<typename PythiaT, typename EventT>
    void generateEventColliderPythia(EventT& result,
                                     const MCLoopInfo& RunMC,
                                     const ColliderPythia<PythiaT,EventT>& HardScatteringSim,
                                     const int iteration,
                                     void(*wrapup)())
    {
      static int nFailedEvents;

      // If the event loop has not been entered yet, reset the counter for the number of failed events
      if (iteration == BASE_INIT)
      {
        // Although BASE_INIT should never be called in parallel, we do this in omp_critical just in case.
        #pragma omp critical (pythia_event_failure)
        {
          nFailedEvents = 0;
        }
        return;
      }

      // If in any other special iteration, do nothing
      if (iteration < BASE_INIT) return;

      // Reset the event
      result.clear();

      // Attempt (possibly repeatedly) to generate an event
      while(nFailedEvents <= RunMC.current_maxFailedEvents())
      {
        try
        {
          HardScatteringSim.nextEvent(result);
          break;
        }
        catch (typename ColliderPythia<PythiaT,EventT>::EventGenerationError& e)
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << debug_prefix() << "ColliderPythia::EventGenerationError caught in generatePythia8Event. Check the ColliderBit log for event details." << endl;
          #endif
          #pragma omp critical (pythia_event_failure)
          {
            // Update global counter
            nFailedEvents += 1;
            // Store Pythia event record in the logs
            std::stringstream ss;
            result.list(ss, 1);
            logger() << LogTags::debug << "ColliderPythia::EventGenerationError error caught in generatePythia8Event. Pythia record for event that failed:\n" << ss.str() << EOM;
          }
        }
      }
      // Wrap up event loop if too many events fail.
      if(nFailedEvents > RunMC.current_maxFailedEvents())
      {
        piped_warnings.request(LOCAL_INFO,"exceeded maxFailedEvents");
        wrapup();
        return;
      }
    }

    /// Generate a hard scattering event with a specific Pythia
    #define GET_PYTHIA_EVENT(NAME, EVENT_TYPE)                   \
    void NAME(EVENT_TYPE& result)                                \
    {                                                            \
      using namespace Pipes::NAME;                               \
      generateEventColliderPythia(result, *Dep::RunMC,           \
       *Dep::HardScatteringSim, *Loop::iteration, Loop::wrapup); \
    }

  }

}