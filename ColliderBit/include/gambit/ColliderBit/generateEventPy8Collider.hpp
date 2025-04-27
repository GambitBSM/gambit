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
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {


    // Calculate a Pythia cross-section estimate outside of the main event loop
    // This is for the purpose of calculating an initial cross-section
    // It should run with the minimal required settings (e.g. no showering/clustering/hadronisation)
    template<typename PythiaT, typename EventT>
    void PerformInitialCrossSection_Pythia(initialxsec_container& result,
                                           SLHAstruct& slha,
                                           const str model_suffix,
                                           const Options& runOptions)
    {
      map_str_xsec_container TotalXsecContainer;
      map_str_map_int_process_xsec ProcessXsecContainer;

      static bool first = true;
      static str pythia_doc_path;
      PythiaT pythia;

      // Setup the Pythia documentation path and print the banner once
      if (first)
      {
        const str be = "Pythia" + model_suffix;
        const str ver = Backends::backendInfo().default_version(be);
        pythia_doc_path = Backends::backendInfo().path_dir(be, ver) + "/../share/Pythia8/xmldoc/";
        pythia.banner(pythia_doc_path);
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
      for (std::string collider : collider_names)
      {
        int nFailedEvents = 0;
        int nEvents = 0;

        std::vector<str> pythiaOptions;
        pythiaOptions.push_back("Print:quiet = on");
        pythiaOptions.push_back("SLHA:verbose = 0");

        YAML::Node colNode = runOptions.getValue<YAML::Node>(collider);
        Options colOptions(colNode);
        int max_Nevents = colOptions.getValueOrDef<int>(10000, "nEvents");
        int maxFailedEvents = colOptions.getValueOrDef<int>(10, "maxFailedEvents");
        if (colOptions.hasKey("pythia_settings"))
        {
          std::vector<str> addPythiaOptions = colNode["pythia_settings"].as<std::vector<str> >();
          pythiaOptions.insert(pythiaOptions.end(), addPythiaOptions.begin(), addPythiaOptions.end());
        }

        pythiaOptions.push_back("Init:showProcesses = off");
        pythiaOptions.push_back("SLHA:file = slhaea");

        // Make sure the user has selected a collider energy in their Pythia settings by searching 
        // for the substring "Beams:e", to match Pythia options "Beams:eCM", "Beams:eA" or "Beams:eB".
        bool has_beam_energy_option = std::any_of(pythiaOptions.begin(), pythiaOptions.end(), [](const str& s){ return s.find("Beams:e") != str::npos; });
        if (!has_beam_energy_option)
        {
          ColliderBit_error().raise(LOCAL_INFO,"Could not find a beam energy in the list of Pythia settings. Please add one, e.g. 'Beams:eCM = 13000'.");
        }

        bool startup_success = true;
        double combined_xsec = 0.0;
        double combined_xsecErr = 0.0;
        std::vector<int> combined_process_codes;
        std::map<int, double> combined_process_xsec;
        std::map<int, double> combined_process_xsecErr;

        #pragma omp parallel firstprivate(pythia, pythiaOptions)
        {
          // Add a thread-specific seed to this thread's copy of the Pythia options
          str seed = std::to_string(int(Random::draw() * 899990000.));
          pythiaOptions.push_back("Random:seed = " + seed);

          try
          {
            pythia.init(pythia_doc_path, pythiaOptions, &slha);
          }
          catch (...)
          {
            // Append new seed to override the previous one
            int newSeedBase = int(Random::draw() * 899990000.);
            pythiaOptions.push_back("Random:seed = " + std::to_string(newSeedBase));
            try
            {
              pythia.init(pythia_doc_path, pythiaOptions, &slha);
            }
            catch (...)
            {
              #ifdef COLLIDERBIT_DEBUG
                cout << DEBUG_PREFIX << "Py8Collider::InitializationError caught in PerformInitialCrossSection_Pythia. Will discard this point." << endl;
              #endif
            }
          }

          EventT dummy_pythia_event;
          try
          {
            pythia.nextEvent(dummy_pythia_event);
          }
          catch (...)
          {
            #ifdef COLLIDERBIT_DEBUG
              cout << DEBUG_PREFIX << "Failed to generate dummy test event in PerformInitialCrossSection_Pythia. Check the logs for event details." << endl;
            #endif
            //Try a second time
            try
            {
              pythia.nextEvent(dummy_pythia_event);
            }
            catch (...)
            {
              #ifdef COLLIDERBIT_DEBUG
                cout << DEBUG_PREFIX << "Py8Collider::InitializationError caught in PerformInitialCrossSection_Pythia. Will discard this point." << endl;
              #endif
              startup_success = false;
            }
          }

          // Synchronise the threads, so that they can check all were successfully initialised
          #pragma omp barrier
        
          // Only do the event generation if the startup was successful for all threads
          if (startup_success)
          {
            // Create a dummy event to make Pythia fill its internal list of process codes
            // We are not analysing the event
            EventT pythia_event;
            while (nEvents < max_Nevents)
            {
              #pragma omp critical
              {
                nEvents++;
              }
              pythia_event.clear();
              while (nFailedEvents <= maxFailedEvents)
              {
                try
                {
                  pythia.nextEvent(pythia_event);
                  break;
                }
                catch (...)
                {
                  #ifdef COLLIDERBIT_DEBUG
                    cout << DEBUG_PREFIX << "Failed to generate dummy test event in PerformInitialCrossSection_Pythia. Check the logs for event details." << endl;
                  #endif
                  #pragma omp critical (pythia_event_failure)
                  {
                    // Update global counter
                    nFailedEvents += 1;
                    std::stringstream ss;
                    pythia_event.list(false, false, 1, ss);
                    logger() << LogTags::debug << "Failed to generate dummy test event in PerformInitialCrossSection_Pythia. Pythia record for the event that failed:\n" << ss.str() << EOM;
                  }
                }
              }
            } // End loop over events

            // Combine together cross-sections
            #pragma omp critical
            {
              if (combined_xsec == 0.0)
              {
                combined_xsec = pythia.xsec_fb();
                combined_xsecErr = pythia.xsecErr_fb();
              }
              else
              {
                double thread_xsec = pythia.xsec_fb();
                double thread_xsecErr = pythia.xsecErr_fb();
                double w = 1./(combined_xsecErr*combined_xsecErr);
                double other_w = 1./(thread_xsecErr*thread_xsecErr);
                combined_xsec = (w * combined_xsec + other_w * thread_xsec) / (w + other_w);
                combined_xsecErr = 1./sqrt(w + other_w);
              }

              std::vector<int> thread_active_process_codes = pythia.all_active_process_codes();

              for (int code : thread_active_process_codes)
              {
                // If the process is not already present in the combined objects
                if (std::find(combined_process_codes.begin(), combined_process_codes.end(), code) == combined_process_codes.end())
                {
                  combined_process_codes.push_back(code);
                  combined_process_xsec[code] = pythia.xsec_fb(code);
                  combined_process_xsecErr[code] = pythia.xsecErr_fb(code);
                }
                else
                {
                  double thread_xsec = pythia.xsec_fb(code);
                  double thread_xsecErr = pythia.xsecErr_fb(code);
                  double w = 1./(combined_process_xsecErr[code]*combined_process_xsecErr[code]);
                  double other_w = 1./(thread_xsecErr*thread_xsecErr);
                  combined_process_xsec[code] = (w * combined_process_xsec[code] + other_w * thread_xsec) / (w + other_w);
                  combined_process_xsecErr[code] = 1./sqrt(w + other_w);
                }
              }
            }
          } // End if block on startup_success
        } // End parallel block

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
        TotalXsecContainer[collider] = xsContainer;

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
        ProcessXsecContainer[collider] = int_proc_xsec_map;

      } // End loop over colliders

      // Store the results
      result.first = TotalXsecContainer;
      result.second = ProcessXsecContainer;
    }

    /// Run initial Pythia cross-section estimation
    #define GET_INITIAL_XSEC_PYTHIA(NAME, PYTHIA_COLLIDER, PYTHIA_NS)                                                                         \
    void NAME(initialxsec_container& result)                                                                                                  \
    {                                                                                                                                         \
      using namespace Pipes::NAME;                                                                                                            \
      static SLHAstruct slha = *Dep::SpectrumAndDecaysForPythia;                                                                              \
                                                                                                                                              \
      PerformInitialCrossSection_Pythia<PYTHIA_COLLIDER, PYTHIA_NS::Pythia8::Event>(result, slha, "", *runOptions);                           \
    }
    
    #define GET_SPECIFIC_INITIAL_XSEC_PYTHIA(NAME, PYTHIA_COLLIDER, PYTHIA_NS, MODEL_EXTENSION)                                               \
    void NAME(initialxsec_container& result)                                                                                                  \
    {                                                                                                                                         \
      using namespace Pipes::NAME;                                                                                                            \
      static SLHAstruct slha = *Dep::SpectrumAndDecaysForPythia;                                                                              \
                                                                                                                                              \
      PerformInitialCrossSection_Pythia<PYTHIA_COLLIDER, PYTHIA_NS::Pythia8::Event>(result, slha, #MODEL_EXTENSION, *runOptions);             \
    }


    /// Drop a HepMC file for the event
    #ifndef EXCLUDE_HEPMC
      template<typename PythiaT, typename hepmc_writerT>
      void dropHepMCEventPy8Collider(const PythiaT* Pythia, const safe_ptr<Options>& runOptions)
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
    void generateEventPy8Collider(EventT& pythia_event,
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
          cerr << DEBUG_PREFIX << "Py8Collider::EventGenerationError caught in generateEventPy8Collider. Check the ColliderBit log for event details." << endl;
          #endif
          #pragma omp critical (pythia_event_failure)
          {
            // Update global counter
            nFailedEvents += 1;
            // Store Pythia event record in the logs
            std::stringstream ss;
            pythia_event.list(false, false, 1, ss);
            logger() << LogTags::debug << "Py8Collider::EventGenerationError error caught in generateEventPy8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
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
        dropHepMCEventPy8Collider<PythiaT,hepmc_writerT>(HardScatteringSim.pythia(), runOptions);
      #endif

    }

    /// Generate a hard scattering event with Pythia and convert it to HEPUtils::Event
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void convertEventToHEPUtilsPy8Collider(HEPUtils::Event& event,
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
          convertPartonEvent(pythia_event, event, HardScatteringSim.all_jet_collection_settings, HardScatteringSim.jetcollection_taus, jet_pt_min);
        else
          convertParticleEvent(pythia_event, event, HardScatteringSim.all_jet_collection_settings, HardScatteringSim.jetcollection_taus, jet_pt_min);
      }
      // No good.
      catch (Gambit::exception& e)
      {
        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Gambit::exception caught during event conversion in convertEventToHEPUtilsPy8Collider. Check the ColliderBit log for details." << endl;
        #endif

        #pragma omp critical (event_conversion_error)
        {
          // Store Pythia event record in the logs
          std::stringstream ss;
          pythia_event.list(false, false, 1, ss);
          logger() << LogTags::debug << "Gambit::exception caught in convetEventToHEPUtilsPy8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
        }

        str errmsg = "Bad point: convertEventToHEPUtilsPy8Collider caught the following runtime error: ";
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
      void convertEventToHepMCPy8Collider(HepMC3::GenEvent& event,
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
            cout << DEBUG_PREFIX << "Gambit::exception caught during event conversion in convertEventToHepMCPy8Collider. Check the ColliderBit log for details." << endl;
          #endif

          #pragma omp critical (event_conversion_error)
          {
            // Store Pythia event record in the logs
            std::stringstream ss;
            pythia_event.list(false, false, 1, ss);
            logger() << LogTags::debug << "Gambit::exception caught in convertEventToHepMCPy8Collider. Pythia record for event that failed:\n" << ss.str() << EOM;
          }

          str errmsg = "Bad point: convertEventToHepMCPy8Collider caught the following runtime error: ";
          errmsg    += e.what();
          piped_invalid_point.request(errmsg);
          wrapup();
          return;
        }

      }
    #endif


    /// Generate a hard scattering event with a specific Pythia,
    #define GET_PYTHIA_EVENT(NAME, PYTHIA_EVENT_TYPE)            \
    void NAME(PYTHIA_EVENT_TYPE &result)                         \
    {                                                            \
      using namespace Pipes::NAME;                               \
      generateEventPy8Collider(result, *Dep::RunMC,              \
       *Dep::HardScatteringSim, *Loop::iteration,                \
       Loop::wrapup, runOptions);                                \
                                                                 \
    }                                                            \
                                                                 \
    void CAT(NAME,_HEPUtils)(HEPUtils::Event& result)            \
    {                                                            \
      using namespace Pipes::CAT(NAME,_HEPUtils);                \
      convertEventToHEPUtilsPy8Collider(result,                  \
       *Dep::HardScatteringEvent, *Dep::HardScatteringSim,       \
       *Dep::EventWeighterFunction, *Loop::iteration,            \
       Loop::wrapup, runOptions);                                \
    }                                                            \
                                                                 \
    IF_NOT_DEFINED(EXCLUDE_HEPMC,                                \
        void CAT(NAME,_HepMC)(HepMC3::GenEvent& result)          \
        {                                                        \
          using namespace Pipes::CAT(NAME,_HepMC);               \
          convertEventToHepMCPy8Collider(result,                 \
           *Dep::HardScatteringEvent, *Dep::HardScatteringSim,   \
           *Loop::iteration, Loop::wrapup);                      \
        }                                                        \
    )

  }

}
