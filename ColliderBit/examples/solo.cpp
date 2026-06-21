//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  ColliderBit Solo: an event-based LHC recast
///  tool using the GAMBIT ColliderBit module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  (p.scott@imperial.ac.uk)
///  \date May 2019
///
///  \author Tomek Procter
///  (t.procter.1@research.gla.ac.uk)
///  \date November 2021
///
///  \author Pengxuan Zhu
///  (pengxuan.zhu@adelaide.edu.au)
///  \date Feburary 2025
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "fastjet/ClusterSequence.hh"
#include "solo_batch.hpp"
#include "solo_input.hpp"
#include "solo_output.hpp"
// #include "gambit/Backends/backend_rollcall.hpp"
#include <cstdlib>
#include <cstring>
#include <limits>
#include <utility>

#define NULIKE_VERSION "1.0.9"
#define NULIKE_SAFE_VERSION 1_0_9

#define RIVET_VERSION "4.1.0"
#define RIVET_SAFE_VERSION 4_1_0
#define CONTUR_VERSION "3.0.0"
#define CONTUR_SAFE_VERSION 3_0_0

#define FULLLIKES_VERSION "1.0"
#define FULLLIKES_SAFE_VERSION 1_0

using namespace ColliderBit::Functown;
using namespace BackendIniBit::Functown;
using namespace CAT(Backends::nulike_,NULIKE_SAFE_VERSION)::Functown;
using namespace CAT(Backends::ATLAS_FullLikes_,FULLLIKES_SAFE_VERSION)::Functown;
using namespace CAT(Backends::Contur_,CONTUR_SAFE_VERSION)::Functown;
using namespace CAT(Backends::Rivet_,RIVET_SAFE_VERSION)::Functown;

// Helper function to check if setting in CBS yaml and then set it
// TODO: It would be nice also to template final arg as Gambit::module_functor<typename T>. I think this breaks setOption is itself a templated function?
template <typename Tsetting>
bool apply_setting_if_present(const std::string &setting, Options& settings, Gambit::module_functor<ColliderBit::map_str_AnalysisLogLikes> &the_functor)
{
  if (settings.hasKey(setting))
  {
    the_functor.setOption<Tsetting>(setting, settings.getValue<Tsetting>(setting));
    return true;
  }
  return false;
}
/// ColliderBit Solo main program
int main(int argc, char* argv[])
{
  try
  {
    const auto env_flag_enabled = [](const char* value) -> bool
    {
      if (value == nullptr) return false;
      if (std::strcmp(value, "1") == 0) return true;
      if (std::strcmp(value, "true") == 0) return true;
      if (std::strcmp(value, "TRUE") == 0) return true;
      if (std::strcmp(value, "yes") == 0) return true;
      if (std::strcmp(value, "YES") == 0) return true;
      if (std::strcmp(value, "on") == 0) return true;
      if (std::strcmp(value, "ON") == 0) return true;
      return false;
    };

    // Check the number of command line arguments
    if (argc < 2)
    {
      // Tell the user how to run the program and exit
      cerr << endl << "Usage: " << argv[0] << " <your CBS yaml file>" << endl << endl;
      return 1;
    }

    // Initialise required backends (static loadLibrary calls may be optimised
    // away at -O2, so we must trigger loading via the init functors explicitly).
    CAT_3(nulike_,NULIKE_SAFE_VERSION,_init).reset_and_calculate();

    // Make sure that nulike is present.
    if (not Backends::backendInfo().works[str("nulike")+NULIKE_VERSION]) backend_error().raise(LOCAL_INFO, str("nulike ")+NULIKE_VERSION+" is missing!");

    // Check if Rivet and Contur are there: permit runs without that don't ask for them:
    bool conturWorks = true;
    bool rivetWorks = true;
    if (not Backends::backendInfo().works[str("Contur")+CONTUR_VERSION]) { conturWorks = false;}
    if (not Backends::backendInfo().works[str("Rivet")+RIVET_VERSION]) { rivetWorks = false;}

    // Print the CBS startup banner once, unless suppressed for subprocess runs.
    const bool suppress_startup_banner = env_flag_enabled(std::getenv("CBS_SUPPRESS_BANNER"));
    if (!suppress_startup_banner)
    {
      cout << endl;
      cout << "==================================" << endl;
      cout << "||                              ||" << endl;
      cout << "||    CBS: ColliderBit Solo     ||" << endl;
      cout << "||  GAMBIT Collider Workgroup   ||" << endl;
      cout << "||                              ||" << endl;
      cout << "==================================" << endl;
      cout << endl;
    }

    // Read input file name
    const std::string filename_in = argv[1];

    // Read and prepare the settings in the input file
    ColliderBit::SoloInput::PreparedInput prepared_input;
    prepared_input = ColliderBit::SoloInput::parse_and_prepare_input(filename_in);

    YAML::Node infile;
    std::vector<str> analyses;
    Options settings;
    infile = prepared_input.infile;
    analyses = prepared_input.analyses;
    settings = prepared_input.settings;


    // Translate relevant settings into appropriate variables
    bool debug = settings.getValueOrDef<bool>(false, "debug");
    const bool suppress_fastjet_banner =
      settings.getValueOrDef<bool>(false, "suppress_fastjet_banner");
    if (suppress_fastjet_banner)
    {
      fastjet::ClusterSequence::set_fastjet_banner_stream(nullptr);
    }
    bool use_FullLikes = settings.getValueOrDef<bool>(false, "use_FullLikes");
    module_functor<ColliderBit::map_str_AnalysisLogLikes>* calcLogLikes =
      use_FullLikes ? &calc_LHC_LogLikes_full : &calc_LHC_LogLikes;
    if (use_FullLikes)
    {
      CAT_3(ATLAS_FullLikes_,FULLLIKES_SAFE_VERSION,_init).reset_and_calculate();
      if (not Backends::backendInfo().works[str("ATLAS_FullLikes") + FULLLIKES_VERSION]) backend_error().raise(LOCAL_INFO, str("ATLAS_FullLikes ")+FULLLIKES_VERSION" is missing!");
    }

    bool use_lnpiln = settings.getValueOrDef<bool>(false, "use_lognormal_distribution_for_1d_systematic");
    // Single runtime cutflow switch for CBS. Cutflow filling relies on extra
    // per-event bookkeeping compiled only when CMake CUTFLOW is enabled.
    const bool requested_check_cutflow = settings.getValueOrDef<bool>(false, "check_cutflow");
#ifdef CHECK_CUTFLOW
    const bool check_cutflow = requested_check_cutflow;
#else
    const bool check_cutflow = false;
    if (requested_check_cutflow)
    {
      std::cerr
        << "WARNING: check_cutflow was requested, but this CBS binary was built "
        << "without CUTFLOW support. Reconfigure with -DCUTFLOW=ON to enable it."
        << std::endl;
    }
#endif
    ColliderBit::Cutflow::set_check_cutflow(check_cutflow);

    // Runtime histogram switch for CBS.
    const bool check_histogram = settings.getValueOrDef<bool>(false, "check_histogram");
    ColliderBit::Histogram1D::set_check_histogram(check_histogram);
    double jet_pt_min = settings.getValueOrDef<double>(10.0, "jet_pt_min");

    // Extract the jet collections yaml node
    YAML::Node jet_collections = settings.getValue<YAML::Node>("jet_collections");
    std::string jet_collection_taus = settings.getValueOrDef<std::string>("antikt_R04", "jet_collection_taus");

    // Check if Rivet & Contur requested and/or enabled then extract options from yaml
    bool withRivet;
    bool withContur;
    Options rivet_settings;
    std::vector<std::string> contur_options;
    try
    {
      if (infile["rivet-settings"])
      {
        withRivet = true;
        rivet_settings = Options(infile["rivet-settings"]);
      } else {withRivet = false;}
      // TODO: Should we just assume contur with no options if rivet settings are specified and Contur not?
      if (infile["contur-settings"])
      {
        withContur = true;
        contur_options = infile["contur-settings"].as<std::vector<std::string>>();
      }
      else
      {
        withContur = false;
      }
      // Throw out cases where things won't work, with informative errors:
      if (withContur && !withRivet)
      {
        throw std::runtime_error("Can't run contur without rivet. Try adding a rivet-settings section to your yaml-file. Quitting...");
      }
      else if (!withContur && withRivet)
      {
        throw std::runtime_error("Can't run rivet without contur. Try adding a contur-settings section to your yaml-file. Quitting...");
      }
      else if (withContur && !conturWorks)
      {
        backend_error().raise(LOCAL_INFO, str("yaml file requests contur, but Contur ")+CONTUR_VERSION+" is missing!");
      }
      else if (withRivet && !rivetWorks)
      {
        backend_error().raise(LOCAL_INFO, str("yaml file requests rivet, but Rivet ")+RIVET_VERSION+" is missing!");
      }
      else if (withContur && withRivet)
      {
        // Ok, we're good to go with Rivet and Contur,
        // TODO: Proper citation message?
        std::cout << "\nUsing RIVET " << RIVET_VERSION << " and CONTUR " <<
          CONTUR_VERSION << " on this run.\n";
      }
    }
    catch (YAML::Exception &e)
    {
      throw std::runtime_error("YAML error in "+filename_in+".\n(yaml-cpp error: "+std::string(e.what())+" )");
    }

    ColliderBit::SoloOutput::OutputConfig output_config;
    output_config.screen_output = settings.getValueOrDef<bool>(true, "screen_output");
    output_config.write_file = settings.hasKey("output");
    if (output_config.write_file)
    {
      output_config.output_file = settings.getValueOrDef<std::string>("CBS_output.json", "output");
    }
    ColliderBit::SoloOutput::validate_output_config(output_config);

    // Process-mode batch running: run one standard CBS pass per file, then merge.
    if (!prepared_input.processes.empty())
    {
      if (withRivet || withContur)
      {
        throw std::runtime_error("settings.processes batch mode does not support rivet-settings/contur-settings.");
      }

      // In batch mode each file is run in a subprocess; print FastJet banner only once here.
      if (!suppress_fastjet_banner)
      {
        fastjet::ClusterSequence::print_banner();
      }

      double (*marginaliser)(const int&, const double&, const double&, const double&) =
        use_lnpiln
          ? nulike_lnpiln.handoutFunctionPointer()
          : nulike_lnpin.handoutFunctionPointer();

      bool (*fullLikesFileExists)(const str&) =
        use_FullLikes ? FullLikes_FileExists.handoutFunctionPointer() : nullptr;
      int (*fullLikesReadIn)(const str&, const str&, const str&) =
        use_FullLikes ? FullLikes_ReadIn.handoutFunctionPointer() : nullptr;
      double (*fullLikesEvaluate)(std::map<str,double>&, const str&) =
        use_FullLikes ? FullLikes_Evaluate.handoutFunctionPointer() : nullptr;

      ColliderBit::SoloBatch::MergedRunResult merged = ColliderBit::SoloBatch::run_and_merge(
        argv[0],
        prepared_input,
        settings,
        marginaliser,
        fullLikesFileExists,
        fullLikesReadIn,
        fullLikesEvaluate
      );

      const std::vector<ColliderBit::SoloBatch::AnalysisSamplingAdvice> batch_sampling_advice =
        ColliderBit::SoloBatch::build_sampling_advice(merged, prepared_input, settings);

      std::vector<ColliderBit::SoloOutput::SamplingAdviceEntry> output_sampling_advice;
      output_sampling_advice.reserve(batch_sampling_advice.size());
      for (const ColliderBit::SoloBatch::AnalysisSamplingAdvice& in_analysis : batch_sampling_advice)
      {
        ColliderBit::SoloOutput::SamplingAdviceEntry out_analysis;
        out_analysis.analysis_name = in_analysis.analysis_name;
        out_analysis.sr_label = in_analysis.sr_label;
        out_analysis.sr_index = in_analysis.sr_index;
        out_analysis.n_sig_scaled = in_analysis.n_sig_scaled;
        out_analysis.n_sig_scaled_err = in_analysis.n_sig_scaled_err;
        out_analysis.fractional_uncert = in_analysis.fractional_uncert;
        out_analysis.effective_events = in_analysis.effective_events;
        out_analysis.targets.reserve(in_analysis.targets.size());

        for (const ColliderBit::SoloBatch::SamplingTargetAdvice& in_target : in_analysis.targets)
        {
          ColliderBit::SoloOutput::SamplingAdviceTargetEntry out_target;
          out_target.target_fractional_uncert = in_target.target_fractional_uncert;
          out_target.need_more_mc = in_target.need_more_mc;
          out_target.current_fractional_uncert = in_target.current_fractional_uncert;
          out_target.scale_factor = in_target.scale_factor;
          out_target.current_total_events = in_target.current_total_events;
          out_target.recommended_total_events = in_target.recommended_total_events;
          out_target.recommended_additional_events = in_target.recommended_additional_events;
          out_target.process_recommendations.reserve(in_target.process_recommendations.size());

          for (const ColliderBit::SoloBatch::ProcessSamplingAdvice& in_process :
               in_target.process_recommendations)
          {
            ColliderBit::SoloOutput::SamplingAdviceProcessEntry out_process;
            out_process.process_name = in_process.process_name;
            out_process.cross_section_fb = in_process.cross_section_fb;
            out_process.processed_events = in_process.processed_events;
            out_process.recommended_additional_events = in_process.recommended_additional_events;
            out_target.process_recommendations.push_back(std::move(out_process));
          }

          out_analysis.targets.push_back(std::move(out_target));
        }

        output_sampling_advice.push_back(std::move(out_analysis));
      }

      std::map<std::string, double> empty_contur_pool_loglikes;
      std::map<std::string, std::string> empty_contur_pool_info;
      ColliderBit::SoloOutput::emit_outputs(
        output_config,
        merged.total_events,
        merged.combined_loglike,
        merged.analyses,
        merged.analysis_loglikes,
        false,
        0.0,
        empty_contur_pool_loglikes,
        empty_contur_pool_info,
        output_sampling_advice
      );
      return 0;
    }

    // Choose the event file reader according to file format
    if (debug)
    {
      if (prepared_input.hepmc_filenames.size() == 1)
      {
        cout << "Reading HepMC file: " << prepared_input.hepmc_filenames.front() << endl;
      }
      else
      {
        cout << "Reading " << prepared_input.hepmc_filenames.size() << " HepMC files." << endl;
      }
    }
    auto& getEvent = getHepMCEvent;
    auto& convertEvent = convertHepMCEvent_HEPUtils;
    auto& AnalysisNumbers = CollectAnalyses;
    AnalysisNumbers.setOption<bool>("check_cutflow", check_cutflow);
    AnalysisNumbers.setOption<bool>("print_cutflows", check_cutflow);
    AnalysisNumbers.setOption<bool>("normalized_cutflows", false);

    // Initialise logs
    logger().set_log_debug_messages(debug);
    initialise_standalone_logs("CBS_logs/");
    logger()<<"Running CBS"<<LogTags::info<<EOM;
    
    // Initialise settings for printer (required)
    YAML::Node printerNode = get_standalone_printer("cout", "CBS_logs/", "");
    Printers::PrinterManager printerManager(printerNode, false);
    set_global_printer_manager(&printerManager);

    // Initialise the random number generator, using a hardware seed if no seed is given in the input file.
    int seed = settings.getValueOrDef<int>(-1, "seed");
    Random::create_rng_engine("default", seed);

    // Pass options to the main event loop
    YAML::Node CBS(infile["settings"]);
    CBS["analyses"] = analyses;
    CBS["min_nEvents"] = (long long)(1000);
    CBS["max_nEvents"] = (long long)(std::numeric_limits<int>::max());
    // CBS policy: always process all events provided by the user (no convergence-based early stop).
    CBS["run_convergence_checks"] = false;
    operateLHCLoop.setOption<YAML::Node>("CBS", CBS);
    operateLHCLoop.setOption<bool>("silenceLoop", not debug);

    // Tell operateLHCLoop to use the "CBS" collider
    std::vector<std::string> use_colliders = {"CBS"};
    operateLHCLoop.setOption<std::vector<std::string>>("use_colliders", use_colliders);

    // Pass the event filename and the jet pt cutoff to the HepMC reader/HEPUtils converter function
    getEvent.setOption<str>("hepmc_filename", prepared_input.hepmc_filenames.front());
    convertEvent.setOption<double>("jet_pt_min", jet_pt_min);

    // Pass the jet collections yaml node to the hepMC reader/HEPUtils converter function
    getEvent.setOption<std::string>("jet_collection_taus", jet_collection_taus);
    getEvent.setOption<YAML::Node>("jet_collections", jet_collections);
    convertEvent.setOption<std::string>("jet_collection_taus", jet_collection_taus);
    convertEvent.setOption<YAML::Node>("jet_collections", jet_collections);

    // Pass options to the cross-section function
    getYAMLCrossSection.setOption<std::string>("collider", "CBS");
    getYAMLCrossSection.setOption<double>("cross_section_fb", prepared_input.total_cross_section_fb);
    getYAMLCrossSection.setOption<double>("cross_section_uncert_fb", prepared_input.total_cross_section_uncert_fb);

    // Pass options to the likelihood function
    // TODO: I'm not specifying the defaults here. I'll add the argument only if the user supplies it.
    // ColliderBit can then fall back to its defaults if nothing is supplied.
    apply_setting_if_present<bool>("use_covariances", settings, *calcLogLikes);//Default true
    apply_setting_if_present<bool>("use_marginalising", settings, *calcLogLikes);//Default False
    apply_setting_if_present<bool>("combine_SRs_without_covariances", settings, *calcLogLikes);//Default False

    apply_setting_if_present<double>("nuisance_prof_initstep", settings, *calcLogLikes);//Default 0.1
    apply_setting_if_present<double>("nuisance_prof_convtol", settings, *calcLogLikes);//Default 0.01
    apply_setting_if_present<int>("nuisance_prof_maxsteps", settings, *calcLogLikes);//Default 10000
    apply_setting_if_present<double>("nuisance_prof_convacc", settings, *calcLogLikes);//Default 0.01
    apply_setting_if_present<double>("nuisance_prof_simplexsize", settings, *calcLogLikes);//Default 1e-5
    apply_setting_if_present<int>("nuisance_prof_method", settings, *calcLogLikes);//Default 6

    apply_setting_if_present<double>("nuisance_marg_convthres_abs", settings, *calcLogLikes);//Default 0.05
    apply_setting_if_present<double>("nuisance_marg_convthres_rel", settings, *calcLogLikes);//Default 0.05
    apply_setting_if_present<long>("nuisance_marg_nsamples_start", settings, *calcLogLikes);//Default 1000000
    apply_setting_if_present<bool>("nuisance_marg_nulike1sr", settings, *calcLogLikes);//Default true

    apply_setting_if_present<bool>("calc_noerr_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_expected_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_expected_noerr_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_scaledsignal_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<double>("signal_scalefactor", settings, *calcLogLikes);//Default 1.0

    // If Rivet/Contur, set Rivet/Contur options
    if (withRivet)
    {
      Rivet_measurements.setOption<bool>("drop_YODA_file", rivet_settings.getValueOrDef<bool>(true, "drop_YODA_file"));
      Rivet_measurements.setOption<bool>("runningStandalone", true);
      Rivet_measurements.setOption<std::vector<std::string>>("analyses",
                                                rivet_settings.getValue<std::vector<std::string>>("analyses"));
      Rivet_measurements.setOption<std::vector<std::string>>("exclude_analyses",
                                                rivet_settings.getValueOrDef<std::vector<std::string>>({},"exclude_analyses"));
      std::vector<std::string> contur_options = infile["contur-settings"].as<std::vector<std::string>>();
      Contur_LHC_measurements_from_stream.setOption("contur_options", contur_options);
    }


    // Resolve ColliderBit dependencies and backend requirements
    convertEvent.resolveDependency(&getEvent);
    calc_combined_LHC_LogLike.resolveDependency(calcLogLikes);
    calc_combined_LHC_LogLike.resolveDependency(&operateLHCLoop);
    get_LHC_LogLike_per_analysis.resolveDependency(calcLogLikes);
    calcLogLikes->resolveDependency(&CollectAnalyses);
    calcLogLikes->resolveDependency(&operateLHCLoop);
    calcLogLikes->resolveDependency(&getYAMLCrossSection);
    calcLogLikes->resolveBackendReq(use_lnpiln ? &nulike_lnpiln : &nulike_lnpin);
    if (use_FullLikes)
    {
      calcLogLikes->resolveBackendReq(&FullLikes_FileExists);
      calcLogLikes->resolveBackendReq(&FullLikes_ReadIn);
      calcLogLikes->resolveBackendReq(&FullLikes_Evaluate);
    }
    CollectAnalyses.resolveDependency(&runATLASAnalyses);
    CollectAnalyses.resolveDependency(&runCMSAnalyses);
    CollectAnalyses.resolveDependency(&runIdentityAnalyses);
    runATLASAnalyses.resolveDependency(&getATLASAnalysisContainer);
    runATLASAnalyses.resolveDependency(&smearEventATLAS);
    runCMSAnalyses.resolveDependency(&getCMSAnalysisContainer);
    runCMSAnalyses.resolveDependency(&smearEventCMS);
    runIdentityAnalyses.resolveDependency(&getIdentityAnalysisContainer);
    runIdentityAnalyses.resolveDependency(&copyEvent);
    getATLASAnalysisContainer.resolveDependency(&getYAMLCrossSection);
    getCMSAnalysisContainer.resolveDependency(&getYAMLCrossSection);
    getIdentityAnalysisContainer.resolveDependency(&getYAMLCrossSection);
    smearEventATLAS.resolveDependency(&getBuckFastATLAS);
    smearEventATLAS.resolveDependency(&convertEvent);
    smearEventCMS.resolveDependency(&getBuckFastCMS);
    smearEventCMS.resolveDependency(&convertEvent);
    copyEvent.resolveDependency(&getBuckFastIdentity);
    copyEvent.resolveDependency(&convertEvent);
    // If using Rivet/Contur, resolve Rivet/Contur dependencies:
    if (withRivet)
    {
      Rivet_measurements.resolveDependency(&getEvent);
      Rivet_measurements.resolveBackendReq(&Contur_get_analyses_from_beam);

      Contur_LHC_measurements_from_stream.resolveDependency(&Rivet_measurements);
      Contur_LHC_measurements_from_stream.resolveBackendReq(&Contur_LogLike_from_stream);
      Contur_LHC_measurements_LogLike.resolveDependency(&Contur_LHC_measurements_from_stream);
      Contur_LHC_measurements_LogLike_perPool.resolveDependency(&Contur_LHC_measurements_from_stream);
      Contur_LHC_measurements_histotags_perPool.resolveDependency(&Contur_LHC_measurements_from_stream);
    }

    // Resolve loop manager for ColliderBit event loop
    getEvent.resolveLoopManager(&operateLHCLoop);
    convertEvent.resolveLoopManager(&operateLHCLoop);
    getBuckFastATLAS.resolveLoopManager(&operateLHCLoop);
    getBuckFastCMS.resolveLoopManager(&operateLHCLoop);
    getBuckFastIdentity.resolveLoopManager(&operateLHCLoop);
    getATLASAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getCMSAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getIdentityAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    smearEventATLAS.resolveLoopManager(&operateLHCLoop);
    smearEventCMS.resolveLoopManager(&operateLHCLoop);
    copyEvent.resolveLoopManager(&operateLHCLoop);
    getYAMLCrossSection.resolveLoopManager(&operateLHCLoop);
    runATLASAnalyses.resolveLoopManager(&operateLHCLoop);
    runCMSAnalyses.resolveLoopManager(&operateLHCLoop);
    runIdentityAnalyses.resolveLoopManager(&operateLHCLoop);
    std::vector<functor*> nested_functions = initVector<functor*>(&getEvent,
                                                                  &convertEvent,
                                                                  &getBuckFastATLAS,
                                                                  &getBuckFastCMS,
                                                                  &getBuckFastIdentity,
                                                                  &getYAMLCrossSection,
                                                                  &getATLASAnalysisContainer,
                                                                  &getCMSAnalysisContainer,
                                                                  &getIdentityAnalysisContainer,
                                                                  &smearEventATLAS,
                                                                  &smearEventCMS,
                                                                  &copyEvent,
                                                                  &runATLASAnalyses,
                                                                  &runCMSAnalyses,
                                                                  &runIdentityAnalyses);
    // If using contur and rivet:
    if (withRivet)
    {
      Rivet_measurements.resolveLoopManager(&operateLHCLoop);
      Contur_LHC_measurements_from_stream.resolveLoopManager(&operateLHCLoop);

      nested_functions.push_back(&Rivet_measurements);
      nested_functions.push_back(&Contur_LHC_measurements_from_stream);
    }

    operateLHCLoop.setNestedList(nested_functions);

    // Call the initialisation function for remaining backends
    // (nulike and optional ATLAS_FullLikes are already initialised before the works[] checks above)
    if (withRivet)
    {
      CAT_3(Contur_, CONTUR_SAFE_VERSION,_init).reset_and_calculate();
      CAT_3(Rivet_, RIVET_SAFE_VERSION,_init).reset_and_calculate();
    }

    // Run the detector sim and selected analyses on all the events read in.
    operateLHCLoop.reset_and_calculate();
    CollectAnalyses.reset_and_calculate();
    calcLogLikes->reset_and_calculate();
    get_LHC_LogLike_per_analysis.reset_and_calculate();
    calc_combined_LHC_LogLike.reset_and_calculate();
    if (withContur)
    {
      Contur_LHC_measurements_LogLike.reset_and_calculate();
      Contur_LHC_measurements_LogLike_perPool.reset_and_calculate();
      Contur_LHC_measurements_histotags_perPool.reset_and_calculate();
    }

    const int n_events = operateLHCLoop(0).event_count.at("CBS");
    const double loglike = calc_combined_LHC_LogLike(0);

    std::map<std::string, double> contur_pool_loglikes;
    std::map<std::string, std::string> contur_pool_info;
    double contur_total_loglike = 0.0;
    if (withContur)
    {
      contur_total_loglike = Contur_LHC_measurements_LogLike(0);
      contur_pool_loglikes = Contur_LHC_measurements_LogLike_perPool(0);
      contur_pool_info = Contur_LHC_measurements_histotags_perPool(0);
    }

    const auto& analysis_results = CollectAnalyses(0);
    const auto& analysis_loglikes = (*calcLogLikes)(0);

    ColliderBit::SoloOutput::emit_outputs(
      output_config,
      n_events,
      loglike,
      analysis_results,
      analysis_loglikes,
      withContur,
      contur_total_loglike,
      contur_pool_loglikes,
      contur_pool_info
    );

    // No more to see here folks, go home.
    return 0;
  }

  catch (std::exception& e)
  {
    cerr << "CBS has exited with fatal exception: " << e.what() << endl;
  }

  // Finished, but an exception was raised.
  return 1;

}
