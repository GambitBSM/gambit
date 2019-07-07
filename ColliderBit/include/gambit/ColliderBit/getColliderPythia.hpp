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
///  \date 2019 Jan, Feb
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

    /// Retrieve a Pythia hard-scattering Monte Carlo simulation
    template<typename PythiaT, typename EventT>
    void getColliderPythia(ColliderPythia<PythiaT, EventT>& result,
                           const MCLoopInfo& RunMC,
                           const Spectrum& spectrum,
                           const DecayTable& decay_rates,
                           const str model_suffix,
                           const int iteration,
                           void(*wrapup)(),
                           const Options& runOptions,
                           bool is_SUSY)
    {
      static bool first = true;
      static std::vector<str> filenames;
      static str pythia_doc_path;
      static std::vector<str> pythiaCommonOptions;
      static SLHAstruct slha;
      static SLHAstruct slha_spectrum;
      static double xsec_veto_fb;
      static unsigned int fileCounter = 0;

      if (iteration == BASE_INIT)
      {
        // Setup the Pythia documentation path and print the banner once
        if (first)
        {
          const str be = "Pythia" + model_suffix;
          const str ver = Backends::backendInfo().default_version(be);
          pythia_doc_path = Backends::backendInfo().path_dir(be, ver) + "/../share/Pythia8/xmldoc/";
          result.banner(pythia_doc_path);
          if (runOptions.hasKey("SLHA_filenames"))
          {
            filenames = runOptions.getValue<std::vector<str> >("SLHA_filenames");
          }
          first = false;
        }

        if (filenames.empty())
        {
          // SLHAea object constructed from dependencies on the spectrum and decays.
          slha.clear();
          slha_spectrum.clear();
          slha = decay_rates.getSLHAea(2);
          // SLHAea in SLHA2 format, please.
          slha_spectrum = spectrum.getSLHAea(2);
          slha.insert(slha.begin(), slha_spectrum.begin(), slha_spectrum.end());
          if (is_SUSY)
          {
            SLHAea::Block block("MODSEL");
            block.push_back("BLOCK MODSEL              # Model selection");
            SLHAea::Line line;
            line << 1 << 0 << "# Tell Pythia that this is a SUSY model.";
            block.push_back(line);
            slha.push_front(block);
          }
        }
        else
        {
          if (filenames.size() <= fileCounter) invalid_point().raise("No more SLHA files. My work is done.");
        }

      }

      else if (iteration == COLLIDER_INIT)
      {
        // Collect Pythia options that are common across all OMP threads
        pythiaCommonOptions.clear();

        // By default we tell Pythia to be quiet. (Can be overridden from yaml settings)
        pythiaCommonOptions.push_back("Print:quiet = on");
        pythiaCommonOptions.push_back("SLHA:verbose = 0");

        // Get options from yaml file.
        double xsec_veto_default = 0.0;
        if (runOptions.hasKey(RunMC.current_collider()))
        {
          YAML::Node colNode = runOptions.getValue<YAML::Node>(RunMC.current_collider());
          Options colOptions(colNode);
          xsec_veto_fb = colOptions.getValueOrDef<double>(xsec_veto_default, "xsec_veto");

          if (colOptions.hasKey("pythia_settings"))
          {
            std::vector<str> addPythiaOptions = colNode["pythia_settings"].as<std::vector<str> >();
            pythiaCommonOptions.insert(pythiaCommonOptions.end(), addPythiaOptions.begin(), addPythiaOptions.end());
          }
        }
        else xsec_veto_fb = xsec_veto_default;

        // We need showProcesses for the xsec veto.
        pythiaCommonOptions.push_back("Init:showProcesses = on");

        // We need "SLHA:file = slhaea" for the SLHAea interface, and the filename for the SLHA interface.
        str slha_string = (filenames.empty() ? "slhaea" : filenames.at(fileCounter));
        pythiaCommonOptions.push_back("SLHA:file = " + slha_string);
      }

      else if (iteration == START_SUBPROCESS)
      {
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

        if (not filenames.empty() and omp_get_thread_num() == 0)
          logger() << "Reading SLHA file: " << filenames.at(fileCounter) << EOM;

        // Get the Pythia options that are common across all OMP threads ('pythiaCommonOptions')
        // and then add the thread-specific seed
        std::vector<str> pythiaOptions = pythiaCommonOptions;
        str seed = std::to_string(int(Random::draw() * 899990000.));
        pythiaOptions.push_back("Random:seed = " + seed);

        #ifdef COLLIDERBIT_DEBUG
          cout << debug_prefix() << "getPythia"+model_suffix+": My Pythia seed is: " << seed << endl;
        #endif

        try
        {
          if (filenames.empty())
          {
            result.init(pythia_doc_path, pythiaOptions, &slha, processLevelOutput);
          }
          else
          {
            result.init(pythia_doc_path, pythiaOptions, processLevelOutput);
          }
        }
        catch (typename ColliderPythia<PythiaT,EventT>::InitializationError& e)
        {
          // Append new seed to override the previous one
          int newSeedBase = int(Random::draw() * 899990000.);
          pythiaOptions.push_back("Random:seed = " + std::to_string(newSeedBase));
          try
          {
            if (filenames.empty())
            {
              result.init(pythia_doc_path, pythiaOptions, &slha, processLevelOutput);
            }
            else
            {
              result.init(pythia_doc_path, pythiaOptions, processLevelOutput);
            }
          }
          catch (typename ColliderPythia<PythiaT,EventT>::InitializationError& e)
          {
            #ifdef COLLIDERBIT_DEBUG
              cout << debug_prefix() << "ColliderPythia::InitializationError caught in getColliderPythia. Will discard this point." << endl;
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
        cout << debug_prefix() << "totalxsec [fb] = " << totalxsec * 1e12 << ", veto limit [fb] = " << xsec_veto_fb << endl;
        #endif

        // - Check for NaN xsec
        if (Utils::isnan(totalxsec))
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << debug_prefix() << "Got NaN cross-section estimate from Pythia." << endl;
          #endif
          piped_invalid_point.request("Got NaN cross-section estimate from Pythia.");
          wrapup();
          return;
        }

        // - Wrap up loop if veto applies
        if (totalxsec * 1e12 < xsec_veto_fb)
        {
          #ifdef COLLIDERBIT_DEBUG
          cout << debug_prefix() << "Cross-section veto applies. Will now call Loop::wrapup() to skip event generation for this collider." << endl;
          #endif
          wrapup();
        }

      }

      else if (iteration == BASE_FINALIZE and not filenames.empty()) fileCounter++;

    }

    /// Retrieve a specific Pythia hard-scattering Monte Carlo simulation
    #define IS_SUSY true
    #define NOT_SUSY false
    #define GET_SPECIFIC_PYTHIA(NAME, PYTHIA_NS, SPECTRUM, MODEL_EXTENSION, SUSY_FLAG)\
    void NAME(ColliderPythia<PYTHIA_NS::Pythia8::Pythia,                              \
                             PYTHIA_NS::Pythia8::Event> &result)                      \
    {                                                                                 \
      using namespace Pipes::NAME;                                                    \
      getColliderPythia(result, *Dep::RunMC, *Dep::SPECTRUM,                          \
       *Dep::decay_rates, #MODEL_EXTENSION, *Loop::iteration,                         \
       Loop::wrapup, *runOptions, SUSY_FLAG);                             \
    }

    /// Get a specific Pythia hard-scattering sim as a generator-independent pointer-to-BaseCollider
    #define GET_PYTHIA_AS_BASE_COLLIDER(NAME)           \
    void NAME(const BaseCollider* &result)              \
    {                                                   \
      result = &(*Pipes::NAME::Dep::HardScatteringSim); \
    }                                                   \

  }

}
