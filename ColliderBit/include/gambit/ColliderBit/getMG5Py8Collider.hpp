//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  collider Monte Carlo event simulators.
///  TODO: This is a WIP
///  This is very similar to getPy8Collider.hpp, but
///  in the initialisation step of Pythia, it first runs
///  MadGraph. The events from MadGraph are read into Pythia via an LHE file.
///  TODO: In the future this will patch pythia so that LHE files are not written.
///  TODO: I need to be careful with parallelisation since the different threads need to all read from the same LHE file.
///        Perhaps this can be solved if MadGraph can be instructed to generate nthread lhe files
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date   2023
///
///  *********************************************


#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    /// Retrieve a Pythia hard-scattering Monte Carlo simulation
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void getMG5Py8Collider(Py8Collider<PythiaT, EventT, hepmc_writerT>& result,
                        const MCLoopInfo& RunMC,
                        const SLHAstruct& slha,
                        const str model_suffix,
                        const int iteration,
                        void(*wrapup)(),
                        const Options& runOptions,
                        int (*MG_RunEvents)(str&, str&, std::vector<str>&))
    {
      static bool first = true;
      static str pythia_doc_path;
      static double xsec_veto_fb;
      static str OutputFolderName;
      str mg5_dir = GAMBIT_DIR "/Backends/installed/MadGraph/3.4.2/";

      if (iteration == BASE_INIT)
      {
        // Setup the Pythia documentation path and print the banner once
        if (first)
        {
          // TODO: Print the MadGraph Banner as well
        
          const str be = "Pythia" + model_suffix;
          const str ver = Backends::backendInfo().default_version(be);
          pythia_doc_path = Backends::backendInfo().path_dir(be, ver) + "/../share/Pythia8/xmldoc/";
          result.banner(pythia_doc_path);
          first = false;
        }
      }


      // To make sure that the Pythia instance on each OMP thread gets all the
      // options it should, all the options parsing and initialisation happens in
      // COLLIDER_INIT_OMP (OMP parallel) rather than COLLIDER_INIT (only thread 0).
      // We may want to split this up, so that all the yaml options are parsed in
      // COLLIDER_INIT (by thread 0), and used to initialize the 'result' instance
      // of each thread within COLLIDER_INIT_OMP.
      //
      // else if (iteration == COLLIDER_INIT)
      // {
      //   // Do the option parsing here?
      // }
      
      // In COLLIDER_INIT_OMP step, run MadGraph
      else if (iteration == COLLIDER_INIT)
      {
        std::vector<str> MadGraphOptions;
        str OutputFolderName_default = "MyMadGraphTesting_default";
        if (runOptions.hasKey(RunMC.current_collider()))
        {
          YAML::Node colNode = runOptions.getValue<YAML::Node>(RunMC.current_collider());
          Options colOptions(colNode);

          
          OutputFolderName = colOptions.getValueOrDef<str>(OutputFolderName_default, "MG_OutputFolderName");

          // TODO: Check whether the output folder exists, and if not throw an error
          
          // TODO: Check for some necessary settings??

          if (colOptions.hasKey("MadGraph_settings"))
          {
            std::vector<str> addMadGraphOptions = colNode["MadGraph_settings"].as<std::vector<str> >();
            MadGraphOptions.insert(MadGraphOptions.end(), addMadGraphOptions.begin(), addMadGraphOptions.end());
          }
        }
        int MG_success = MG_RunEvents(mg5_dir, OutputFolderName, MadGraphOptions);
        if (MG_success != 0) { std::cout << "HEY! I failed in the MadGraph stage. This message should be replaced with a proper error raise.\n";}
      }

      else if (iteration == COLLIDER_INIT_OMP)
      {
        std::string LHEpath = GAMBIT_DIR "/Backends/installed/MadGraph/3.4.2/" + OutputFolderName + "/Events/run_01/unweighted_events.lhe";

        std::vector<str> pythiaOptions;

        // By default we tell Pythia to be quiet. (Can be overridden from yaml settings)
        pythiaOptions.push_back("Print:quiet = on");
        pythiaOptions.push_back("SLHA:verbose = 0");

        pythiaOptions.push_back("Beams:frametype = 4");
        pythiaOptions.push_back("Beams:LHEF = " + LHEpath);

        // Get options from yaml file.
        const double xsec_veto_default = 0.0;
        const bool partonOnly_default = false;
        const double antiktR_default = 0.4;
        if (runOptions.hasKey(RunMC.current_collider()))
        {
          YAML::Node colNode = runOptions.getValue<YAML::Node>(RunMC.current_collider());
          Options colOptions(colNode);
          xsec_veto_fb = colOptions.getValueOrDef<double>(xsec_veto_default, "xsec_veto");
          result.partonOnly = colOptions.getValueOrDef<bool>(partonOnly_default, "partonOnly");
          result.antiktR = colOptions.getValueOrDef<double>(antiktR_default, "antiktR");
          if (colOptions.hasKey("pythia_settings"))
          {
            std::vector<str> addPythiaOptions = colNode["pythia_settings"].as<std::vector<str> >();
            pythiaOptions.insert(pythiaOptions.end(), addPythiaOptions.begin(), addPythiaOptions.end());
          }
        }
        else
        {
          xsec_veto_fb = xsec_veto_default;
          result.partonOnly = partonOnly_default;
          result.antiktR = antiktR_default;
        }

        // We need showProcesses for the xsec veto. // TODO: Perhaps I should be doing the xsec veto from the MadGraph part earlier.
        pythiaOptions.push_back("Init:showProcesses = on");

        // We need "SLHA:file = slhaea" for the SLHAea interface.
        //pythiaOptions.push_back("SLHA:file = slhaea"); // TODO: If the LHE file hsa the slha block (which it should from MG), it should be fine to ignore this option.

        // If the collider energy is given in the list of Pythia options, we raise an ignore it.
        bool has_beam_energy_option = std::any_of(pythiaOptions.begin(), pythiaOptions.end(), [](const str& s){ return s.find("Beams:e") != str::npos; });
        if (has_beam_energy_option)
        {
          logger() << LogTags::debug << "'Beams:eCM' is not neccessary to set, since this is defined in the LHE file." << EOM;
        }

        // Variables needed for the xsec veto
        std::stringstream processLevelOutput;
        str _junk, readline;
        int code, nxsec;
        double xsec, totalxsec;

        // Each thread needs an independent Pythia instance at the start
        // of each event generation loop.
        // Thus, the actual Pythia initialization is
        // *after* COLLIDER_INIT, within omp parallel.

        result.clear();

        // Add the thread-specific seed to the Pythia options
        str seed = std::to_string(int(Random::draw() * 899990000.));
        pythiaOptions.push_back("Random:seed = " + seed);

        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "getPythia"+model_suffix+": My Pythia seed is: " << seed << endl;
        #endif

        try
        {
          result.init(pythia_doc_path, pythiaOptions, &slha, processLevelOutput);
        }
        catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::InitializationError& e)
        {
          // Append new seed to override the previous one
          int newSeedBase = int(Random::draw() * 899990000.);
          pythiaOptions.push_back("Random:seed = " + std::to_string(newSeedBase));
          try
          {
            result.init(pythia_doc_path, pythiaOptions, &slha, processLevelOutput);
          }
          catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::InitializationError& e)
          {
            #ifdef COLLIDERBIT_DEBUG
              cout << DEBUG_PREFIX << "Py8Collider::InitializationError caught in getMG5Py8Collider. Will discard this point." << endl;
            #endif
            piped_invalid_point.request("Bad point: Pythia can't initialize");
            wrapup();
            return;
          }
        }

        // Should we apply the xsec veto and skip event generation?

        // - Get the upper limt xsec as estimated by Pythia
        code = -1;
        nxsec = 0;
        totalxsec = 0.;
        while(true)
        {
          std::getline(processLevelOutput, readline);
          std::istringstream issPtr(readline);
          issPtr.seekg(47, issPtr.beg);
          issPtr >> code;
          if (!issPtr.good() && nxsec > 0) break;
          issPtr >> _junk >> xsec;
          if (issPtr.good())
          {
            totalxsec += xsec;
            nxsec++;
          }
        }

        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "totalxsec [fb] = " << totalxsec * 1e12 << ", veto limit [fb] = " << xsec_veto_fb << endl;
        #endif

        // - Check for NaN xsec
        if (Utils::isnan(totalxsec))
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Got NaN cross-section estimate from Pythia." << endl;
          #endif
          piped_invalid_point.request("Got NaN cross-section estimate from Pythia.");
          wrapup();
          return;
        }

        // - Wrap up loop if veto applies
        if (totalxsec * 1e12 < xsec_veto_fb)
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Cross-section veto applies. Will now call Loop::wrapup() to skip event generation for this collider." << endl;
          #endif
          wrapup();
        } else {

          // Create a dummy event to make Pythia fill its internal list of process codes
          EventT dummy_pythia_event;
          try
          {
            result.nextEvent(dummy_pythia_event);
          }
          catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::EventGenerationError& e)
          {
            // Try again...
            try
            {
              result.nextEvent(dummy_pythia_event);
            }
            catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::EventGenerationError& e)
            {
              piped_invalid_point.request("Failed to generate dummy test event. Will invalidate point.");

              #ifdef COLLIDERBIT_DEBUG
                cout << DEBUG_PREFIX << "Failed to generate dummy test event during COLLIDER_INIT_OMP in getMG5Py8Collider. Check the logs for event details." << endl;
              #endif
              #pragma omp critical (pythia_event_failure)
              {
                std::stringstream ss;
                dummy_pythia_event.list(ss, 1);
                logger() << LogTags::debug << "Failed to generate dummy test event during COLLIDER_INIT_OMP iteration in getMG5Py8Collider. Pythia record for the event that failed:\n" << ss.str() << EOM;
              }
            }
          }

        }

      }

    }


    // TODO: Would this be a problem of duplicate definitions?
    /// Work out last template arg of Py8Collider depending on whether we are using HepMC
    #ifdef EXCLUDE_HEPMC
      #define HEPMC_TYPE(PYTHIA_NS) void
    #elseRunEvents
      #define HEPMC_TYPE(PYTHIA_NS) PYTHIA_NS::Pythia8::GAMBIT_hepmc_writer
    #endif

    /// Retrieve a specific Pythia hard-scattering Monte Carlo simulation
    #define GET_SPECIFIC_PYTHIA_MG(NAME, PYTHIA_NS, MODEL_EXTENSION)                     \
    void NAME(Py8Collider<PYTHIA_NS::Pythia8::Pythia,                                 \
                          PYTHIA_NS::Pythia8::Event,                                  \
                          HEPMC_TYPE(PYTHIA_NS)> &result)                             \
    {                                                                                 \
      using namespace Pipes::NAME;                                                    \
      static SLHAstruct slha;                                                         \
                                                                                      \
      if (*Loop::iteration == BASE_INIT)                                              \
      {                                                                               \
        /* SLHAea object constructed from dependencies on the spectrum and decays. */ \
        slha.clear();                                                                 \
        slha = *Dep::SpectrumAndDecaysForPythia;     /* TODO: This can probably be something empty */        \
      }                                                                               \
                                                                                       \
      int (*MG_RunEvents)(str&, str&, std::vector<str>&) = BEreq::MG_RunEvents.pointer();  \
                                                                                   \
      getMG5Py8Collider(result, *Dep::RunMC, slha, #MODEL_EXTENSION,                     \
        *Loop::iteration, Loop::wrapup, *runOptions, MG_RunEvents);                                 \
    }


  }

}
