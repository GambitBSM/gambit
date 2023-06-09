//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  collider Monte Carlo events.
///  This is similar to generateEventPy8Collider.hpp
///  with small tweaks for events generated with MadGraph
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    /// Drop a HepMC file for the event
    #ifndef EXCLUDE_HEPMC
      template<typename PythiaT, typename hepmc_writerT>
      void dropHepMCEventMG5Py8Collider(const PythiaT* Pythia, const safe_ptr<Options>& runOptions)
      {
        // Write event to HepMC file
        static const bool drop_HepMC2_file = runOptions->getValueOrDef<bool>(false, "drop_HepMC2_file");
        static const bool drop_HepMC3_file = runOptions->getValueOrDef<bool>(false, "drop_HepMC3_file");
        if (drop_HepMC2_file or drop_HepMC3_file)
        {
          thread_local hepmc_writerT hepmc_writer;
          thread_local bool first = true;

          if (first)
          {
            str filename = "GAMBIT_collider_events.omp_thread_";
            filename += std::to_string(omp_get_thread_num());
            filename += ".hepmc";
            hepmc_writer.init(filename, drop_HepMC2_file, drop_HepMC3_file);
            first = false;
          }

          if(drop_HepMC2_file)
            hepmc_writer.write_event_HepMC2(const_cast<PythiaT*>(Pythia));
          if(drop_HepMC3_file)
            hepmc_writer.write_event_HepMC3(const_cast<PythiaT*>(Pythia));

        }
      }
    #endif

    /// Generate a hard scattering event with Pythia
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void generateEventMG5Py8Collider(EventT& pythia_event,
                                  const MCLoopInfo& RunMC,
                                  const Py8Collider<PythiaT,EventT,hepmc_writerT>& HardScatteringSim,
                                  const int iteration,
                                  void(*wrapup)(),
                                  const safe_ptr<Options>& runOptions)
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

      // Reset the Pythia event
      pythia_event.clear();

      // Attempt (possibly repeatedly) to generate an event
      // TODO: If the first N events fail, perhaps end early?
      while(nFailedEvents <= RunMC.current_maxFailedEvents())
      {
        try
        {
          #ifdef COLLIDERBIT_DEBUG
          cerr << DEBUG_PREFIX << "Will now call HardScatteringSim.nextEvent(pythia_event)..." << endl;
          #endif

          HardScatteringSim.nextEvent(pythia_event);
          break;
        }
        catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::EventGenerationError& e)
        {
          #ifdef COLLIDERBIT_DEBUG
          cerr << DEBUG_PREFIX << "Py8Collider::EventGenerationError caught in generateEventMG5Py8Collider. Check the ColliderBit log for event details." << endl;
          #endif
          #pragma omp critical (pythia_event_failure)
          {
            // Update global counter
            nFailedEvents += 1;
            // Store Pythia event record in the logs
            std::stringstream ss;
            pythia_event.list(ss, 1);
            logger() << LogTags::debug << "Py8Collider::EventGenerationError error caught in generateEventMG5Py8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
          }
        }
      }

      // Wrap up event loop if too many events fail.
      if(nFailedEvents > RunMC.current_maxFailedEvents())
      {
        // Tell the MCLoopInfo instance that we have exceeded maxFailedEvents
        RunMC.report_exceeded_maxFailedEvents();
        if(RunMC.current_invalidate_failed_points())
        {
          piped_invalid_point.request("exceeded maxFailedEvents");
        }
        wrapup();
        return;
      }

      #ifndef EXCLUDE_HEPMC
        dropHepMCEventMG5Py8Collider<PythiaT,hepmc_writerT>(HardScatteringSim.pythia(), runOptions);
      #endif

    }

    /// Generate a hard scattering event with Pythia and convert it to HEPUtils::Event
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void convertEventToHEPUtilsMG5Py8Collider(HEPUtils::Event& event,
                                  const EventT &pythia_event,
                                  const Py8Collider<PythiaT,EventT,hepmc_writerT>& HardScatteringSim,
                                  const EventWeighterFunctionType& EventWeighterFunction,
                                  const int iteration,
                                  void(*wrapup)(),
                                  const safe_ptr<Options>& runOptions)

    {

      // If in any other special iteration, do nothing
      if (iteration <= BASE_INIT) return;

      // Clear the HEPUtils event
      event.clear();

      static const double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");

      // Attempt to convert the Pythia event to a HEPUtils event
      try
      {
        if (HardScatteringSim.partonOnly)
          convertPartonEvent(pythia_event, event, HardScatteringSim.antiktR, jet_pt_min);
        else
          convertParticleEvent(pythia_event, event, HardScatteringSim.antiktR, jet_pt_min);
      }
      // No good.
      catch (Gambit::exception& e)
      {
        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Gambit::exception caught during event conversion in convertEventToHEPUtilsMG5Py8Collider. Check the ColliderBit log for details." << endl;
        #endif

        #pragma omp critical (event_conversion_error)
        {
          // Store Pythia event record in the logs
          std::stringstream ss;
          pythia_event.list(ss, 1);
          logger() << LogTags::debug << "Gambit::exception caught in convetEventToHEPUtilsPy8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
        }

        str errmsg = "Bad point: convertEventToHEPUtilsMG5Py8Collider caught the following runtime error: ";
        errmsg    += e.what();
        piped_invalid_point.request(errmsg);
        wrapup();
        return;
      }

      // Assign weight to event
      EventWeighterFunction(event, &HardScatteringSim);
    }

    #ifndef EXCLUDE_HEPMC
      /// Generate a hard scattering event with Pythia and convert it to HepMC event
      template<typename PythiaT, typename EventT, typename hepmc_writerT>
      void convertEventToHepMCMG5Py8Collider(HepMC3::GenEvent& event,
                                    const EventT &pythia_event,
                                    const Py8Collider<PythiaT,EventT,hepmc_writerT>& HardScatteringSim,
                                    const int iteration,
                                    void(*wrapup)())
      {

        // If in any other special iteration, do nothing
        if (iteration <= BASE_INIT) return;

        // Clear the HepMC event
        event.clear();

        // Attempt to convert the Pythia event to a HepMC event
        try
        {
          thread_local hepmc_writerT hepmc_writer;
          thread_local bool first = true;

          if (first)
          {
            hepmc_writer.init("", false, false);
            first = false;
          }

          hepmc_writer.convert_to_HepMC_event(const_cast<PythiaT*>(HardScatteringSim.pythia()), event);
        }
        // No good.
        catch (Gambit::exception& e)
        {
          #ifdef COLLIDERBIT_DEBUG
            cout << DEBUG_PREFIX << "Gambit::exception caught during event conversion in convertEventToHepMCMG5Py8Collider. Check the ColliderBit log for details." << endl;
          #endif

          #pragma omp critical (event_conversion_error)
          {
            // Store Pythia event record in the logs
            std::stringstream ss;
            pythia_event.list(ss, 1);
            logger() << LogTags::debug << "Gambit::exception caught in convertEventToHepMCMG5Py8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
          }

          str errmsg = "Bad point: convertEventToHepMCMG5Py8Collider caught the following runtime error: ";
          errmsg    += e.what();
          piped_invalid_point.request(errmsg);
          wrapup();
          return;
        }

      }
    #endif


    /// Generate a hard scattering event with a specific Pythia,
    #define GET_MGPYTHIA_EVENT(NAME, PYTHIA_EVENT_TYPE)          \
    void NAME(PYTHIA_EVENT_TYPE &result)                         \
    {                                                            \
      using namespace Pipes::NAME;                               \
      generateEventMG5Py8Collider(result, *Dep::RunMC,           \
       *Dep::HardScatteringSim, *Loop::iteration,                \
       Loop::wrapup, runOptions);                                \
                                                                 \
    }                                                            \
                                                                 \
    void CAT(NAME,_HEPUtils)(HEPUtils::Event& result)            \
    {                                                            \
      using namespace Pipes::CAT(NAME,_HEPUtils);                \
      convertEventToHEPUtilsMG5Py8Collider(result,               \
       *Dep::HardScatteringEvent, *Dep::HardScatteringSim,       \
       *Dep::EventWeighterFunction, *Loop::iteration,            \
       Loop::wrapup, runOptions);                                \
    }                                                            \
                                                                 \
    IF_NOT_DEFINED(EXCLUDE_HEPMC,                                \
        void CAT(NAME,_HepMC)(HepMC3::GenEvent& result)          \
        {                                                        \
          using namespace Pipes::CAT(NAME,_HepMC);               \
          convertEventToHepMCMG5Py8Collider(result,              \
           *Dep::HardScatteringEvent, *Dep::HardScatteringSim,   \
           *Loop::iteration, Loop::wrapup);                      \
        }                                                        \
    )

  }

}
