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
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/cats.hpp"
// #include "gambit/Backends/backend_rollcall.hpp"

#define NULIKE_VERSION "1.0.9"
#define NULIKE_SAFE_VERSION 1_0_9

#define RIVET_VERSION "3.1.5"
#define RIVET_SAFE_VERSION 3_1_5
#define CONTUR_VERSION "2.1.1"
#define CONTUR_SAFE_VERSION 2_1_1

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
    // Check the number of command line arguments
    if (argc < 2)
    {
      // Tell the user how to run the program and exit
      cerr << endl << "Usage: " << argv[0] << " <your CBS yaml file>" << endl << endl;
      return 1;
    }

    // Make sure that nulike is present.
    if (not Backends::backendInfo().works[str("nulike")+NULIKE_VERSION]) backend_error().raise(LOCAL_INFO, str("nulike ")+NULIKE_VERSION+" is missing!");

    // Check if Rivet and Contur are there: permit runs without that don't ask for them:
    bool conturWorks = true;
    bool rivetWorks = true;
    if (not Backends::backendInfo().works[str("Contur")+CONTUR_VERSION]) { conturWorks = false;}
    if (not Backends::backendInfo().works[str("Rivet")+RIVET_VERSION]) { rivetWorks = false;}

    // Make sure that ATLAS FullLikes is present.
    if (not Backends::backendInfo().works[str("ATLAS_FullLikes") + FULLLIKES_VERSION]) backend_error().raise(LOCAL_INFO, str("ATLAS_FullLikes ")+FULLLIKES_VERSION" is missing!");

    // Print the banner (if you could call it that)
    cout << endl;
    cout << "==================================" << endl;
    cout << "||                              ||" << endl;
    cout << "||    CBS: ColliderBit Solo     ||" << endl;
    cout << "||  GAMBIT Collider Workgroup   ||" << endl;
    cout << "||                              ||" << endl;
    cout << "==================================" << endl;
    cout << endl;

    // Read input file name
    const std::string filename_in = argv[1];

    // Read the settings in the input file
    YAML::Node infile;
    std::vector<str> analyses;
    Options settings;
    try
    {
      // Load up the file
      infile = YAML::LoadFile(filename_in);
      // Retrieve the analyses
      if (infile["analyses"]) analyses = infile["analyses"].as<std::vector<str>>();
      else throw std::runtime_error("Analyses list not found in "+filename_in+".  Quitting...");
      // Retrieve the other settings
      if (infile["settings"]) settings = Options(infile["settings"]);
      else throw std::runtime_error("Settings section not found in "+filename_in+".  Quitting...");
    }
    catch (YAML::Exception &e)
    {
      throw std::runtime_error("YAML error in "+filename_in+".\n(yaml-cpp error: "+std::string(e.what())+" )");
    }


    // Translate relevant settings into appropriate variables
    bool debug = settings.getValueOrDef<bool>(false, "debug");
    // TODO: Use the use_FullLikes setting to allow CBS runs without having ATLAS_FullLikes installed
    // bool use_FullLikes = settings.getValueOrDef<bool>(false, "use_FullLikes"); 
    bool use_lnpiln = settings.getValueOrDef<bool>(false, "use_lognormal_distribution_for_1d_systematic");
    double jet_pt_min = settings.getValueOrDef<double>(10.0, "jet_pt_min");
    str event_filename = settings.getValue<str>("event_file");
    bool event_file_is_HepMC = (   Gambit::Utils::endsWith(event_filename, ".hepmc")
                                || Gambit::Utils::endsWith(event_filename, ".hepmc2")
                                || Gambit::Utils::endsWith(event_filename, ".hepmc3") );
    if (not event_file_is_HepMC)
      throw std::runtime_error("Unrecognised event file format in "+event_filename+"; must be .hepmc.");

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

    // Choose the event file reader according to file format
    if (debug) cout << "Reading HepMC" << " file: " << event_filename << endl;
    auto& getEvent = getHepMCEvent;
    auto& convertEvent = convertHepMCEvent_HEPUtils;

    // Initialise logs
    logger().set_log_debug_messages(debug);
    initialise_standalone_logs("CBS_logs/");
    logger()<<"Running CBS"<<LogTags::info<<EOM;

    // Initialise the random number generator, using a hardware seed if no seed is given in the input file.
    int seed = settings.getValueOrDef<int>(-1, "seed");
    Random::create_rng_engine("default", seed);

    // Pass options to the main event loop
    YAML::Node CBS(infile["settings"]);
    CBS["analyses"] = analyses;
    CBS["min_nEvents"] = (long long)(1000);
    CBS["max_nEvents"] = (long long)(1000000000);
    operateLHCLoop.setOption<YAML::Node>("CBS", CBS);
    operateLHCLoop.setOption<bool>("silenceLoop", not debug);

    // Pass the filename and the jet pt cutoff to the HepMC reader/HEPUtils converter function
    getEvent.setOption<str>("hepmc_filename", event_filename);
    convertEvent.setOption<double>("jet_pt_min", jet_pt_min);

    // Pass options to the cross-section function
    if (settings.hasKey("cross_section_pb"))
    {
      getYAMLCrossSection.setOption<double>("cross_section_pb", settings.getValue<double>("cross_section_pb"));
      if (settings.hasKey("cross_section_fractional_uncert")) { getYAMLCrossSection.setOption<double>("cross_section_fractional_uncert", settings.getValue<double>("cross_section_fractional_uncert")); }
      else {getYAMLCrossSection.setOption<double>("cross_section_uncert_pb", settings.getValue<double>("cross_section_uncert_pb")); }
    }
    else // <-- must have option "cross_section_fb"
    {
      getYAMLCrossSection.setOption<double>("cross_section_fb", settings.getValue<double>("cross_section_fb"));
      if (settings.hasKey("cross_section_fractional_uncert")) { getYAMLCrossSection.setOption<double>("cross_section_fractional_uncert", settings.getValue<double>("cross_section_fractional_uncert")); }
      else { getYAMLCrossSection.setOption<double>("cross_section_uncert_fb", settings.getValue<double>("cross_section_uncert_fb")); }
    }

    // Pass options to the likelihood function
    // TODO: I'm not specifying the defaults here. I'll add the argument only if the user supplies it.
    // ColliderBit can then fall back to its defaults if nothing is supplied.
    apply_setting_if_present<bool>("use_covariances", settings, calc_LHC_LogLikes_full);//Default true
    apply_setting_if_present<bool>("use_marginalising", settings, calc_LHC_LogLikes_full);//Default False
    apply_setting_if_present<bool>("combine_SRs_without_covariances", settings, calc_LHC_LogLikes_full);//Default False

    apply_setting_if_present<double>("nuisance_prof_initstep", settings, calc_LHC_LogLikes_full);//Default 0.1
    apply_setting_if_present<double>("nuisance_prof_convtol", settings, calc_LHC_LogLikes_full);//Default 0.01
    apply_setting_if_present<int>("nuisance_prof_maxsteps", settings, calc_LHC_LogLikes_full);//Default 10000
    apply_setting_if_present<double>("nuisance_prof_convacc", settings, calc_LHC_LogLikes_full);//Default 0.01
    apply_setting_if_present<double>("nuisance_prof_simplexsize", settings, calc_LHC_LogLikes_full);//Default 1e-5
    apply_setting_if_present<int>("nuisance_prof_method", settings, calc_LHC_LogLikes_full);//Default 6

    apply_setting_if_present<double>("nuisance_marg_convthres_abs", settings, calc_LHC_LogLikes_full);//Default 0.05
    apply_setting_if_present<double>("nuisance_marg_convthres_rel", settings, calc_LHC_LogLikes_full);//Default 0.05
    apply_setting_if_present<long>("nuisance_marg_nsamples_start", settings, calc_LHC_LogLikes_full);//Default 1000000
    apply_setting_if_present<bool>("nuisance_marg_nulike1sr", settings, calc_LHC_LogLikes_full);//Default true

    bool calc_noerr_loglikes = apply_setting_if_present<bool>("calc_noerr_loglikes", settings, calc_LHC_LogLikes_full);//Default false
    bool calc_expected_loglikes= apply_setting_if_present<bool>("calc_expected_loglikes", settings, calc_LHC_LogLikes_full);//Default false
    bool calc_expected_noerr_loglikes = apply_setting_if_present<bool>("calc_expected_noerr_loglikes", settings, calc_LHC_LogLikes_full);//Default false
    bool calc_scaledsignal_loglikes = apply_setting_if_present<bool>("calc_scaledsignal_loglikes", settings, calc_LHC_LogLikes_full);//Default false
    apply_setting_if_present<double>("signal_scalefactor", settings, calc_LHC_LogLikes_full);//Default 1.0

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
    calc_combined_LHC_LogLike.resolveDependency(&calc_LHC_LogLikes_full);
    calc_combined_LHC_LogLike.resolveDependency(&operateLHCLoop);
    get_LHC_LogLike_per_analysis.resolveDependency(&calc_LHC_LogLikes_full);
    calc_LHC_LogLikes_full.resolveDependency(&CollectAnalyses);
    calc_LHC_LogLikes_full.resolveDependency(&operateLHCLoop);
    calc_LHC_LogLikes_full.resolveBackendReq(use_lnpiln ? &nulike_lnpiln : &nulike_lnpin);
    calc_LHC_LogLikes_full.resolveBackendReq(&FullLikes_FileExists);
    calc_LHC_LogLikes_full.resolveBackendReq(&FullLikes_ReadIn);
    calc_LHC_LogLikes_full.resolveBackendReq(&FullLikes_Evaluate);
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

    // Call the initialisation function for backends
    CAT_3(nulike_,NULIKE_SAFE_VERSION,_init).reset_and_calculate();
    if (withRivet)
    {
      CAT_3(Contur_, CONTUR_SAFE_VERSION,_init).reset_and_calculate();
      CAT_3(Rivet_, RIVET_SAFE_VERSION,_init).reset_and_calculate();
    }

    // Run the detector sim and selected analyses on all the events read in.
    operateLHCLoop.reset_and_calculate();
    CollectAnalyses.reset_and_calculate();
    calc_LHC_LogLikes_full.reset_and_calculate();
    get_LHC_LogLike_per_analysis.reset_and_calculate();
    calc_combined_LHC_LogLike.reset_and_calculate();
    if (withContur)
    {
      Contur_LHC_measurements_LogLike.reset_and_calculate();
      Contur_LHC_measurements_LogLike_perPool.reset_and_calculate();
      Contur_LHC_measurements_histotags_perPool.reset_and_calculate();
    }

    // Retrieve and print the predicted + observed counts and likelihoods for the individual SRs and analyses, as well as the total likelihood.
    int n_events = operateLHCLoop(0).event_count.at("CBS");
    std::stringstream summary_line;
    for (size_t analysis = 0; analysis < CollectAnalyses(0).size(); ++analysis)
    {
      const Gambit::ColliderBit::AnalysisData& adata = *(CollectAnalyses(0).at(analysis));
      const str& analysis_name = adata.analysis_name;
      const Gambit::ColliderBit::AnalysisLogLikes& analysis_loglikes = calc_LHC_LogLikes_full(0).at(analysis_name);
      summary_line << "  " << analysis_name << ": " << endl;
      for (size_t sr_index = 0; sr_index < adata.size(); ++sr_index)
      {
        const Gambit::ColliderBit::SignalRegionData srData = adata[sr_index];
        const double combined_s_uncertainty = srData.calc_n_sig_scaled_err();
        const double combined_bg_uncertainty = srData.n_bkg_err;
        summary_line << "    Signal region " << srData.sr_label << " (SR index " << sr_index << "):" << endl;
        summary_line << "      Observed events: " << srData.n_obs << endl;
        summary_line << "      SM prediction: " << srData.n_bkg << " +/- " << combined_bg_uncertainty << endl;
        summary_line << "      Signal prediction: " << srData.n_sig_scaled << " +/- " << combined_s_uncertainty << endl;
        summary_line << "      Log-likelihood: " << analysis_loglikes.sr_loglikes.at(sr_index) << endl;
        if (calc_noerr_loglikes) {summary_line << "      No-Error Log-Likelihood: " << analysis_loglikes.alt_sr_loglikes.at("noerr").at(sr_index) << "\n";}
        if (calc_expected_loglikes) {summary_line << "      Expected Log-Likelihood: " << analysis_loglikes.alt_sr_loglikes.at("expected").at(sr_index) << "\n";}
        if (calc_expected_noerr_loglikes) {summary_line << "      Expected No-Error Log-Likelihood: " << analysis_loglikes.alt_sr_loglikes.at("expected_noerr").at(sr_index) << "\n";}
        if (calc_scaledsignal_loglikes) {summary_line << "      Scaled Signal Log-Likelihood: " << analysis_loglikes.alt_sr_loglikes.at("scaledsignal").at(sr_index) << std::endl;}
      }
      summary_line << "    Selected signal region: " << analysis_loglikes.combination_sr_label << endl;
      summary_line << "    Total log-likelihood for analysis:" << analysis_loglikes.combination_loglike << endl << endl;
    }
    if (withContur)
    {
      summary_line << "\nContur results:" << std::endl;
      summary_line << "Total Contur Log-Likelihood: " << Contur_LHC_measurements_LogLike(0) << std::endl;
      map_str_dbl pool_LLRs = Contur_LHC_measurements_LogLike_perPool(0);
      map_str_str pool_info = Contur_LHC_measurements_histotags_perPool(0);
      for (const auto & pool : pool_LLRs){
        summary_line << "\tPool " << pool.first << ":" << "\n\t\tLog-likelihood: " <<
          pool.second << "\n\t\tDominant measurement: " << pool_info[pool.first] << std::endl;
      }
    }
    double loglike = calc_combined_LHC_LogLike(0);

    cout.precision(5);
    cout << endl;
    cout << "Read and analysed " << n_events << " events from HepMC file." << endl << endl;
    cout << "Analysis details:" << endl << endl << summary_line.str() << endl;
    // TODO: Mention LHCb as contur can include an LHCb pool?
    cout << std::scientific << "Total combined ATLAS+CMS" << (withContur?" analysis and searches ":" ") 
         << "log-likelihood: " << loglike << endl;
    cout << endl;

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

