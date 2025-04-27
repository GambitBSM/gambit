//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  collider Monte Carlo event simulators.
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
///  \date 2019 Jan, Feb, May
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
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    /// Retrieve a Pythia hard-scattering Monte Carlo simulation
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void getPy8Collider(Py8Collider<PythiaT, EventT, hepmc_writerT>& result,
                        const MCLoopInfo& RunMC,
                        const SLHAstruct& slha,
                        const str model_suffix,
                        const int iteration,
                        void(*wrapup)(),
                        const Options& runOptions)
    {
      static bool first = true;
      static str pythia_doc_path;
      static double xsec_veto_fb;

      if (iteration == BASE_INIT)
      {
        // Setup the Pythia documentation path and print the banner once
        if (first)
        {
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

      else if (iteration == COLLIDER_INIT_OMP)
      {
        std::vector<str> pythiaOptions;

        // By default we tell Pythia to be quiet. (Can be overridden from yaml settings)
        pythiaOptions.push_back("Print:quiet = on");
        pythiaOptions.push_back("SLHA:verbose = 0");

        // Get options from yaml file.
        const double xsec_veto_default = 0.0;
        const bool partonOnly_default = false;
        if (runOptions.hasKey(RunMC.current_collider()))
        {
          YAML::Node colNode = runOptions.getValue<YAML::Node>(RunMC.current_collider());
          Options colOptions(colNode);
          xsec_veto_fb = colOptions.getValueOrDef<double>(xsec_veto_default, "xsec_veto");
          result.partonOnly = colOptions.getValueOrDef<bool>(partonOnly_default, "partonOnly");

          // Fill the jet collection settings.
          result.all_jet_collection_settings.clear();
          result.jetcollection_taus = "";
          if (colOptions.hasKey("jet_collections"))
          {
            YAML::Node all_jetcollections_node = colOptions.getValue<YAML::Node>("jet_collections");
            Options all_jetcollection_options(all_jetcollections_node);
            std::vector<str> jetcollection_names = all_jetcollection_options.getNames();

            for (str key : jetcollection_names)
            {
              YAML::Node current_jc_node = all_jetcollection_options.getValue<YAML::Node>(key);
              Options current_jc_options(current_jc_node);

              str algorithm = current_jc_options.getValue<str>("algorithm");
              double R = current_jc_options.getValue<double>("R");
              str recombination_scheme = current_jc_options.getValue<str>("recombination_scheme");
              str strategy = current_jc_options.getValue<str>("strategy");

              (result.all_jet_collection_settings).push_back({key, algorithm, R, recombination_scheme, strategy});
            }

            result.jetcollection_taus = colOptions.getValue<str>("jet_collection_taus");
            // Throw an error if the "jet_collection_taus" setting does not match an entry in "jet_collections".
            if (std::find(jetcollection_names.begin(), jetcollection_names.end(), result.jetcollection_taus) == jetcollection_names.end())
            {
              ColliderBit_error().raise(LOCAL_INFO,"Please provide the jet_collection_taus setting for jet collections.");
            }
          }
          else
          {
            ColliderBit_error().raise(LOCAL_INFO,"Could not find jet_collections option for collider " + RunMC.current_collider() + ". Please provide this in the YAML file.");
          }
          if (colOptions.hasKey("pythia_settings"))
          {
            std::vector<str> addPythiaOptions = colNode["pythia_settings"].as<std::vector<str> >();
            pythiaOptions.insert(pythiaOptions.end(), addPythiaOptions.begin(), addPythiaOptions.end());
          }
        }
        else
        {
          ColliderBit_error().raise(LOCAL_INFO,"Could not find runOptions for collider " + RunMC.current_collider() + ".");
        }

        // We need showProcesses for the xsec veto.
        pythiaOptions.push_back("Init:showProcesses = on");

        // We need "SLHA:file = slhaea" for the SLHAea interface.
        pythiaOptions.push_back("SLHA:file = slhaea");

        // Make sure the user has selected a collider energy in their Pythia settings by searching 
        // for the substring "Beams:e", to match Pythia options "Beams:eCM", "Beams:eA" or "Beams:eB".
        bool has_beam_energy_option = std::any_of(pythiaOptions.begin(), pythiaOptions.end(), [](const str& s){ return s.find("Beams:e") != str::npos; });
        if (!has_beam_energy_option)
        {
          ColliderBit_error().raise(LOCAL_INFO,"Could not find a beam energy in the list of Pythia settings. Please add one, e.g. 'Beams:eCM = 13000'.");
        }

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
          result.init(pythia_doc_path, pythiaOptions, &slha);
        }
        catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::InitializationError& e)
        {
          // Append new seed to override the previous one
          int newSeedBase = int(Random::draw() * 899990000.);
          pythiaOptions.push_back("Random:seed = " + std::to_string(newSeedBase));
          try
          {
            result.init(pythia_doc_path, pythiaOptions, &slha);
          }
          catch (typename Py8Collider<PythiaT,EventT,hepmc_writerT>::InitializationError& e)
          {
            #ifdef COLLIDERBIT_DEBUG
              cout << DEBUG_PREFIX << "Py8Collider::InitializationError caught in getPy8Collider. Will discard this point." << endl;
            #endif
            piped_invalid_point.request("Bad point: Pythia can't initialize");
            wrapup();
            return;
          }
        }

        // Should we apply the xsec veto and skip event generation?

        // - Get the upper limt xsec as estimated by Pythia
        double max_xsec_fb = result.max_xsec_fb();

        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "max xsec [fb] = " << max_xsec_fb << ", veto limit [fb] = " << xsec_veto_fb << endl;
        #endif

        // - Check for NaN xsec
        if (Utils::isnan(max_xsec_fb))
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "Got NaN cross-section estimate from Pythia." << endl;
          #endif
          piped_invalid_point.request("Got NaN cross-section estimate from Pythia.");
          wrapup();
          return;
        }

        // - Wrap up loop if veto applies
        if (max_xsec_fb < xsec_veto_fb)
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
                cout << DEBUG_PREFIX << "Failed to generate dummy test event during COLLIDER_INIT_OMP in getPy8Collider. Check the logs for event details." << endl;
              #endif
              #pragma omp critical (pythia_event_failure)
              {
                std::stringstream ss;
                dummy_pythia_event.list(false, false, 1, ss);
                logger() << LogTags::debug << "Failed to generate dummy test event during COLLIDER_INIT_OMP iteration in getPy8Collider. Pythia record for the event that failed:\n" << ss.str() << EOM;
              }
            }
          }

        }

      }

    }


    // Get SLHAea object with spectrum and decays for Pythia -- SUSY version
    #define GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_SUSY(NAME, SPECTRUM)                           \
    void NAME(SLHAstruct& result)                                                             \
    {                                                                                         \
      using namespace Pipes::NAME;                                                            \
      static const int slha_version = runOptions->getValueOrDef<int>(2, "slha_version");      \
      static const bool write_summary_to_log =                                                \
       runOptions->getValueOrDef<bool>(false, "write_summary_to_log");                        \
                                                                                              \
      if ((slha_version != 1) && (slha_version != 2))                                       \
      {                                                                                     \
        ColliderBit_error().raise(LOCAL_INFO,                                               \
          "The option 'slha_version' must be set to 1 or 2 (default).");                    \
      }                                                                                     \
      result.clear();                                                                       \
      /* Get decays */                                                                      \
      result = Dep::decay_rates->getSLHAea(slha_version, false, *Dep::SLHA_pseudonyms);     \
      /* Get spectrum */                                                                    \
      SLHAstruct slha_spectrum = Dep::SPECTRUM->getSLHAea(slha_version);                    \
      result.insert(result.begin(), slha_spectrum.begin(), slha_spectrum.end());            \
      /* Add MODSEL block if not found */                                                   \
      if(result.find("MODSEL") == result.end())                                             \
      {                                                                                     \
        SLHAea::Block block("MODSEL");                                                      \
        block.push_back("BLOCK MODSEL              # Model selection");                     \
        SLHAea::Line line;                                                                  \
        line << 1 << 0 << "# Tell Pythia that this is a SUSY model.";                       \
        block.push_back(line);                                                              \
        result.push_front(block);                                                           \
      }                                                                                     \
                                                                                            \
      if (write_summary_to_log)                                                             \
      {                                                                                     \
        std::stringstream SLHA_log_output;                                                  \
        SLHA_log_output << "SLHA" << slha_version << " input to Pythia:\n" << result.str()  \
         << "\n";                                                                           \
        logger() << SLHA_log_output.str() << EOM;                                           \
      }                                                                                     \
    }


    // Get SLHAea object with spectrum and decays for Pythia -- non-SUSY version
    #define GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_NONSUSY(NAME, SPECTRUM)                \
    void NAME(SLHAstruct& result)                                                     \
    {                                                                                 \
      using namespace Pipes::NAME;                                                    \
      result.clear();                                                                 \
      /* Get decays */                                                                \
      result = Dep::decay_rates->getSLHAea(2);                                        \
      /* Get spectrum */                                                              \
      SLHAstruct slha_spectrum = Dep::SPECTRUM->getSLHAea(2);                         \
      result.insert(result.begin(), slha_spectrum.begin(), slha_spectrum.end());      \
    }


    /// Work out last template arg of Py8Collider depending on whether we are using HepMC
    #ifdef EXCLUDE_HEPMC
      #define HEPMC_TYPE(PYTHIA_NS) void
    #else
      #define HEPMC_TYPE(PYTHIA_NS) PYTHIA_NS::Pythia8::GAMBIT_hepmc_writer
    #endif

    /// Retrieve a specific Pythia hard-scattering Monte Carlo simulation
    #define GET_SPECIFIC_PYTHIA(NAME, PYTHIA_NS, MODEL_EXTENSION)                     \
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
        slha = *Dep::SpectrumAndDecaysForPythia;                                      \
      }                                                                               \
                                                                                      \
      getPy8Collider(result, *Dep::RunMC, slha, #MODEL_EXTENSION,                     \
        *Loop::iteration, Loop::wrapup, *runOptions);                                 \
    }


    /// Retrieve a specific Pythia hard-scattering Monte Carlo simulation
    /// from reading a SLHA file rather than getting a Spectrum + DecayTable
    #define GET_SPECIFIC_PYTHIA_SLHA(NAME, PYTHIA_NS, MODEL_EXTENSION)                \
    void NAME(Py8Collider<PYTHIA_NS::Pythia8::Pythia,                                 \
                          PYTHIA_NS::Pythia8::Event,                                  \
                          HEPMC_TYPE(PYTHIA_NS)> &result)                             \
    {                                                                                 \
      using namespace Pipes::NAME;                                                    \
      static SLHAstruct slha;                                                         \
                                                                                      \
      if (*Loop::iteration == COLLIDER_INIT)                                          \
      {                                                                               \
        const pair_str_SLHAstruct& filename_content_pair = *Dep::SLHAFileNameAndContent; \
        if (filename_content_pair.first.empty())                                      \
        {                                                                             \
          piped_invalid_point.request("Got empty SLHA filename. Will invalidate point."); \
        }                                                                             \
      }                                                                               \
                                                                                      \
      getPy8Collider(result, *Dep::RunMC, Dep::SLHAFileNameAndContent->second,        \
        #MODEL_EXTENSION, *Loop::iteration, Loop::wrapup, *runOptions);               \
    }


    /// Get a specific Pythia hard-scattering sim as a generator-independent pointer-to-BaseCollider
    #define GET_PYTHIA_AS_BASE_COLLIDER(NAME)           \
    void NAME(const BaseCollider* &result)              \
    {                                                   \
      result = &(*Pipes::NAME::Dep::HardScatteringSim); \
    }                                                   \

  }

}
