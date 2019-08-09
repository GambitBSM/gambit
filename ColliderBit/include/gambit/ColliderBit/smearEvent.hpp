//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  events after detector simulation.
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

// #define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// Smear an event
    template<typename EventT>
    void smearEvent(HEPUtils::Event& result,
                    const EventT& HardScatteringEvent,
                    const BaseDetector<EventT>& Smearer,
                    const MCLoopInfo& RunMC,
                    const int iteration,
                    const str& ID,
                    const str& detname,
                    void(*wrapup)())
    {

      if (iteration <= BASE_INIT or not RunMC.current_analyses_exist_for(detname)) return;
      result.clear();

      // Attempt to get the next event from Pythia8, convert to HEPUtils::Event, and smear it
      try
      {
        Smearer.processEvent(HardScatteringEvent, result);
      }

      // No good.
      catch (Gambit::exception& e)
      {

        #ifdef COLLIDERBIT_DEBUG
          cout << debug_prefix() << "Gambit::exception caught during event conversion in "+ID+". Check the ColliderBit log for details." << endl;
        #endif

        #pragma omp critical (event_conversion_error)
        {
          // Store Pythia event record in the logs
          std::stringstream ss;
          HardScatteringEvent.list(ss, 1);
          logger() << LogTags::debug << "Gambit::exception caught in "+ID+". Pythia record for event that failed:\n" << ss.str() << EOM;
        }

        str errmsg = "Bad point: "+ID+" caught the following runtime error: ";
        errmsg    += e.what();
        piped_invalid_point.request(errmsg);
        wrapup();
        return;
      }
    }

    /// Smear an event using a simulation of EXPERIMENT
    #define SMEAR_EVENT(NAME, EXPERIMENT)                                                \
    void NAME(HEPUtils::Event& result)                                                   \
    {                                                                                    \
      using namespace Pipes::NAME;                                                       \
      smearEvent(result, *Dep::HardScatteringEvent, *(*Dep::CAT(EXPERIMENT,DetectorSim)),\
       *Dep::RunMC, *Loop::iteration, #NAME, #EXPERIMENT, Loop::wrapup);                 \
    }

  }

}
