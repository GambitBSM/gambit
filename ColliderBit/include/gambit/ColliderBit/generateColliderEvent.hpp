//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  collider Monte Carlo events.
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
///  \date 2019 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date   2017 March
///  \date   2018 Jan
///  \date   2018 May
///  \date   2019 Sep
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Sep, Oct
///  \date 2020 Apr
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#pragma once

#include <functional>
#include <cstdlib>
#include <mutex>
#include <vector>

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/colliders/ColliderHandle.hpp"
#include "gambit/ColliderBit/colliders/EventConversion.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {


    /// Calculate a cross-section estimate outside of the main event loop.
    /// This is for the purpose of calculating an initial cross-section.
    /// It should run with the minimal required settings (e.g. no showering/clustering/hadronisation).
    /// Each thread uses its own collider, created with make_collider on first use and kept for the rest of the run.
    inline void PerformInitialCrossSection(initialxsec_container& result,
                                           SLHAstruct& slha,
                                           const Options& runOptions,
                                           std::function<BaseCollider*()> make_collider)
    {
      map_str_xsec_container TotalXsecContainer;
      map_str_map_int_process_xsec ProcessXsecContainer;

      static bool first = true;
      thread_local BaseCollider* collider = nullptr;

      // Print the banner once
      if (first)
      {
        if (collider == nullptr) collider = make_collider();
        if (collider == nullptr) ColliderBit_error().raise(LOCAL_INFO, "The collider backend failed to create a generator instance.");
        collider->banner();
        first = false;
      }

      // Retrieve all the names of all entries in the yaml options node.
      std::vector<str> vec = runOptions.getNames();
      std::vector<str> collider_names;
      // Step though the names, and accept only those with a "nEvents" sub-entry as colliders.
      for (str& name : vec)
      {
        YAML::Node node = runOptions.getNode(name);
        if (not node.IsScalar()) collider_names.push_back(name);
      }

      // Loop over colliders
      for (std::string collider_name : collider_names)
      {
        int nEvents = 0;
        int nFailedEvents = 0;
        YAML::Node colNode = runOptions.getValue<YAML::Node>(collider_name);
        Options colOptions(colNode);
        const int max_Nevents = colOptions.getValue<int>("nEvents");
        const int maxFailedEvents = colOptions.getValueOrDef<int>(1, "maxFailedEvents");

        std::vector<str> settings;

        // By default we tell Pythia to be quiet. (Can be overridden from yaml settings)
        settings.push_back("Print:quiet = on");
        settings.push_back("SLHA:verbose = 0");

        if (colOptions.hasKey("pythia_settings"))
        {
          std::vector<str> addPythiaOptions = colNode["pythia_settings"].as<std::vector<str> >();
          settings.insert(settings.end(), addPythiaOptions.begin(), addPythiaOptions.end());
        }

        settings.push_back("Init:showProcesses = off");
        settings.push_back("SLHA:file = slhaea");

        // Make sure the user has selected a collider energy in their Pythia settings by searching
        // for the substring "Beams:e", to match Pythia options "Beams:eCM", "Beams:eA" or "Beams:eB".
        bool has_beam_energy_option = std::any_of(settings.begin(), settings.end(), [](const str& s){ return s.find("Beams:e") != str::npos; });
        if (!has_beam_energy_option)
        {
          ColliderBit_error().raise(LOCAL_INFO,"Could not find a beam energy in the list of Pythia settings. Please add one, e.g. 'Beams:eCM = 13000'.");
        }

        bool startup_success = true;
        bool creation_failed = false;
        double combined_xsec = 0.0;
        double combined_xsecErr = 0.0;
        std::vector<int> combined_process_codes;
        std::map<int, double> combined_process_xsec;
        std::map<int, double> combined_process_xsecErr;

        #pragma omp parallel firstprivate(settings)
        {
          // Each thread uses its own collider
          if (collider == nullptr) collider = make_collider();
          if (collider == nullptr)
          {
            #pragma omp critical (collider_creation_failure)
            {
              creation_failed = true;
              startup_success = false;
            }
          }
          else
          {
            // Add a thread-specific seed to this thread's copy of the settings
            settings.push_back("Random:seed = " + std::to_string(int(Random::draw() * 899990000.)));

            collider->clear();
            bool initialised = collider->init(settings, &slha);
            if (!initialised)
            {
              // Try once more, with a new seed appended (the last Random:seed setting wins)
              settings.push_back("Random:seed = " + std::to_string(int(Random::draw() * 899990000.)));
              collider->clear();
              initialised = collider->init(settings, &slha);
              #ifdef COLLIDERBIT_DEBUG
                if (!initialised) cout << DEBUG_PREFIX << "Collider initialisation failed in PerformInitialCrossSection. Will discard this point." << endl;
              #endif
            }

            // Generate a dummy test event (two attempts)
            if (!initialised || (!collider->next_event() && !collider->next_event()))
            {
              #ifdef COLLIDERBIT_DEBUG
                cout << DEBUG_PREFIX << "Failed to initialise or generate a dummy test event in PerformInitialCrossSection. Check the logs for details." << endl;
              #endif
              startup_success = false;
            }
          }

          // Synchronise the threads, so that they can check all were successfully initialised
          #pragma omp barrier

          // Only do the event generation if the startup was successful for all threads
          if (startup_success)
          {
            // Generate dummy events to make the generator fill its internal list of process codes.
            // We are not analysing the events.
            while (nEvents < max_Nevents)
            {
              #pragma omp critical
              {
                nEvents++;
              }
              while (nFailedEvents <= maxFailedEvents)
              {
                if (collider->next_event()) break;

                #ifdef COLLIDERBIT_DEBUG
                  cout << DEBUG_PREFIX << "Failed to generate dummy test event in PerformInitialCrossSection. Check the logs for event details." << endl;
                #endif
                #pragma omp critical (pythia_event_failure)
                {
                  // Update global counter
                  nFailedEvents += 1;
                  std::stringstream ss;
                  collider->list_last_event(ss);
                  logger() << LogTags::debug << "Failed to generate dummy test event in PerformInitialCrossSection. Generator record for the event that failed:\n" << ss.str() << EOM;
                }
              }
            } // End loop over events

            // Combine together cross-sections
            #pragma omp critical
            {
              if (combined_xsec == 0.0)
              {
                combined_xsec = collider->xsec_fb();
                combined_xsecErr = collider->xsecErr_fb();
              }
              else
              {
                double thread_xsec = collider->xsec_fb();
                double thread_xsecErr = collider->xsecErr_fb();
                double w = 1./(combined_xsecErr*combined_xsecErr);
                double other_w = 1./(thread_xsecErr*thread_xsecErr);
                combined_xsec = (w * combined_xsec + other_w * thread_xsec) / (w + other_w);
                combined_xsecErr = 1./sqrt(w + other_w);
              }

              std::vector<int> thread_active_process_codes = collider->all_active_process_codes();

              for (int code : thread_active_process_codes)
              {
                // If the process is not already present in the combined objects
                if (std::find(combined_process_codes.begin(), combined_process_codes.end(), code) == combined_process_codes.end())
                {
                  combined_process_codes.push_back(code);
                  combined_process_xsec[code] = collider->xsec_fb(code);
                  combined_process_xsecErr[code] = collider->xsecErr_fb(code);
                }
                else
                {
                  double thread_xsec = collider->xsec_fb(code);
                  double thread_xsecErr = collider->xsecErr_fb(code);
                  double w = 1./(combined_process_xsecErr[code]*combined_process_xsecErr[code]);
                  double other_w = 1./(thread_xsecErr*thread_xsecErr);
                  combined_process_xsec[code] = (w * combined_process_xsec[code] + other_w * thread_xsec) / (w + other_w);
                  combined_process_xsecErr[code] = 1./sqrt(w + other_w);
                }
              }
            }
          } // End if block on startup_success
        } // End parallel block

        if (creation_failed)
        {
          ColliderBit_error().raise(LOCAL_INFO, "The collider backend failed to create a generator instance.");
        }

        if (!startup_success)
        {
          invalid_point().raise("Bad point: Pythia can't initialize");
        }

        // Invalidate point if too many events fail.
        if(nFailedEvents > maxFailedEvents)
        {
          invalid_point().raise("exceeded maxFailedEvents");
        }

        xsec_container xsContainer;
        xsContainer.set_xsec(combined_xsec, combined_xsecErr);
        TotalXsecContainer[collider_name] = xsContainer;

        // Fill a container of cross-sections for each process
        map_int_process_xsec int_proc_xsec_map;
        for (int code : combined_process_codes)
        {
          double process_xsec = combined_process_xsec[code];
          double process_xsecErr = combined_process_xsecErr[code];
          process_xsec_container newprocess;
          newprocess.set_xsec(process_xsec, process_xsecErr);
          newprocess.set_process_code(code);
          int_proc_xsec_map[code] = newprocess;
        }
        ProcessXsecContainer[collider_name] = int_proc_xsec_map;

      } // End loop over colliders

      // Store the results
      result.first = TotalXsecContainer;
      result.second = ProcessXsecContainer;
    }

    /// Run initial cross-section estimation with the collider backend
    #define GET_INITIAL_XSEC_PYTHIA(NAME)                                                     \
    void NAME(initialxsec_container& result)                                                  \
    {                                                                                         \
      using namespace Pipes::NAME;                                                            \
      SLHAstruct slha = *Dep::SpectrumAndDecaysForPythia;                                     \
                                                                                              \
      PerformInitialCrossSection(result, slha, *runOptions,                                   \
       []() -> BaseCollider* { return BEreq::create_collider(); });                           \
    }


    /// Drop a HepMC file for the event
    #ifndef EXCLUDE_HEPMC
      /// Register a collider whose HepMC files should be closed when the program exits.
      /// The files stay open across all points of a scan, so there is no earlier point
      /// at which every thread is known to be done with them.
      inline void closeHepMCFilesAtExit(BaseCollider* collider)
      {
        static std::mutex mutex;
        static std::vector<BaseCollider*> colliders;
        std::lock_guard<std::mutex> lock(mutex);
        if (colliders.empty())
        {
          std::atexit([]{ for (BaseCollider* c : colliders) c->close_HepMC_files(); });
        }
        colliders.push_back(collider);
      }

      inline void dropHepMCEvent(BaseCollider& collider, const safe_ptr<Options>& runOptions)
      {
        // Write event to HepMC file
        static const bool drop_HepMC2_file = runOptions->getValueOrDef<bool>(false, "drop_HepMC2_file");
        static const bool drop_HepMC3_file = runOptions->getValueOrDef<bool>(false, "drop_HepMC3_file");
        if (drop_HepMC2_file or drop_HepMC3_file)
        {
          thread_local bool first = true;

          if (first)
          {
            str filename = "GAMBIT_collider_events.omp_thread_";
            filename += std::to_string(omp_get_thread_num());
            filename += ".hepmc";
            if (!collider.open_HepMC_files(filename, drop_HepMC2_file, drop_HepMC3_file))
            {
              ColliderBit_error().raise(LOCAL_INFO, "Could not open HepMC output files: " + collider.last_error());
            }
            closeHepMCFilesAtExit(&collider);
            first = false;
          }

          if (!collider.write_last_event_to_HepMC_files())
          {
            ColliderBit_error().raise(LOCAL_INFO, "Could not write event to HepMC output files: " + collider.last_error());
          }
        }
      }
    #endif

    /// Generate a hard scattering event with the collider
    inline void generateEvent(GeneratorEvent& result,
                              const MCLoopInfo& RunMC,
                              BaseCollider& collider,
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

      // Forget the previous event
      result.reset();

      // Attempt (possibly repeatedly) to generate an event
      while(nFailedEvents <= RunMC.current_maxFailedEvents())
      {
        #ifdef COLLIDERBIT_DEBUG
        cerr << DEBUG_PREFIX << "Will now call collider.next_event()..." << endl;
        #endif

        if (collider.next_event())
        {
          result.set(&collider);
          break;
        }

        #ifdef COLLIDERBIT_DEBUG
        cerr << DEBUG_PREFIX << "Event generation failed in generateEvent. Check the ColliderBit log for event details." << endl;
        #endif
        #pragma omp critical (pythia_event_failure)
        {
          // Update global counter
          nFailedEvents += 1;
          // Store the generator's event record in the logs
          std::stringstream ss;
          collider.list_last_event(ss);
          logger() << LogTags::debug << "Event generation failed in generateEvent (" << collider.last_error() << "). Generator record for event that failed:\n" << ss.str() << EOM;
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
        dropHepMCEvent(collider, runOptions);
      #endif

    }

    /// Convert the generated hard scattering event to a HEPUtils::Event
    inline void convertEventToHEPUtils(HEPUtils::Event& event,
                                       const GeneratorEvent& generator_event,
                                       const ColliderHandle& HardScatteringSim,
                                       const EventWeighterFunctionType& EventWeighterFunction,
                                       const int iteration,
                                       void(*wrapup)(),
                                       const safe_ptr<Options>& runOptions)
    {

      // If in any other special iteration, do nothing
      if (iteration <= BASE_INIT) return;

      // Clear the HEPUtils event
      event.clear();

      // Nothing to convert if event generation failed (the loop is being wrapped up)
      if (!generator_event.valid()) return;

      static const double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");

      // Get the generator-neutral record of the event (one record per thread, reused between events)
      thread_local EventRecord record;
      if (!generator_event.to_record(record))
      {
        ColliderBit_error().raise(LOCAL_INFO, "Could not retrieve the event record from the generator: " + generator_event.collider()->last_error());
      }

      // Attempt to convert the record to a HEPUtils event
      try
      {
        if (HardScatteringSim.partonOnly)
          convertPartonEvent(record, event, HardScatteringSim.all_jet_collection_settings, HardScatteringSim.jetcollection_taus, jet_pt_min);
        else
          convertParticleEvent(record, event, HardScatteringSim.all_jet_collection_settings, HardScatteringSim.jetcollection_taus, jet_pt_min);
      }
      // No good.
      catch (std::exception& e)
      {
        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Exception caught during event conversion in convertEventToHEPUtils. Check the ColliderBit log for details." << endl;
        #endif

        #pragma omp critical (event_conversion_error)
        {
          // Store the generator's event record in the logs
          std::stringstream ss;
          generator_event.list(ss);
          logger() << LogTags::debug << "Exception caught in convertEventToHEPUtils: " << e.what() << "\nGenerator record for event that failed:\n" << ss.str() << EOM;
        }

        str errmsg = "Bad point: convertEventToHEPUtils caught the following runtime error: ";
        errmsg    += e.what();
        piped_invalid_point.request(errmsg);
        wrapup();
        return;
      }

      // Assign weight to event
      EventWeighterFunction(event, HardScatteringSim.get());
    }

    #ifndef EXCLUDE_HEPMC
      /// Convert the generated hard scattering event to a HepMC event
      inline void convertEventToHepMC(HepMC3::GenEvent& event,
                                      const GeneratorEvent& generator_event,
                                      const int iteration,
                                      void(*wrapup)())
      {

        // If in any other special iteration, do nothing
        if (iteration <= BASE_INIT) return;

        // Clear the HepMC event
        event.clear();

        // Nothing to convert if event generation failed (the loop is being wrapped up)
        if (!generator_event.valid()) return;

        // Attempt to convert the generator event to a HepMC event
        if (!generator_event.to_HepMC(event))
        {
          const str error = generator_event.collider()->last_error();

          #ifdef COLLIDERBIT_DEBUG
            cout << DEBUG_PREFIX << "Event conversion failed in convertEventToHepMC. Check the ColliderBit log for details." << endl;
          #endif

          #pragma omp critical (event_conversion_error)
          {
            // Store the generator's event record in the logs
            std::stringstream ss;
            generator_event.list(ss);
            logger() << LogTags::debug << "Event conversion failed in convertEventToHepMC (" << error << "). Generator record for event that failed:\n" << ss.str() << EOM;
          }

          str errmsg = "Bad point: convertEventToHepMC caught the following runtime error: ";
          errmsg    += error;
          piped_invalid_point.request(errmsg);
          wrapup();
          return;
        }

      }
    #endif


    /// Generate a hard scattering event with the collider backend, and
    /// provide it as a HEPUtils::Event and (if HepMC is available) a HepMC3::GenEvent
    #define GET_PYTHIA_EVENT(NAME)                                   \
    void NAME(GeneratorEvent &result)                                \
    {                                                                \
      using namespace Pipes::NAME;                                   \
      generateEvent(result, *Dep::RunMC,                             \
       **Dep::HardScatteringSim, *Loop::iteration,                   \
       Loop::wrapup, runOptions);                                    \
    }                                                                \
                                                                     \
    void CAT(NAME,_HEPUtils)(HEPUtils::Event& result)                \
    {                                                                \
      using namespace Pipes::CAT(NAME,_HEPUtils);                    \
      convertEventToHEPUtils(result, *Dep::HardScatteringEvent,      \
       *Dep::HardScatteringSim, *Dep::EventWeighterFunction,         \
       *Loop::iteration, Loop::wrapup, runOptions);                  \
    }                                                                \
                                                                     \
    IF_NOT_DEFINED(EXCLUDE_HEPMC,                                    \
        void CAT(NAME,_HepMC)(HepMC3::GenEvent& result)              \
        {                                                            \
          using namespace Pipes::CAT(NAME,_HepMC);                   \
          convertEventToHepMC(result, *Dep::HardScatteringEvent,     \
           *Loop::iteration, Loop::wrapup);                          \
        }                                                            \
    )

  }

}
