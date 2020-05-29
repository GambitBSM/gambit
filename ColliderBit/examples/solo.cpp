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
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/cats.hpp"

#define NULIKE_VERSION "1.0.7"
#define NULIKE_SAFE_VERSION 1_0_7

using namespace ColliderBit::Functown;
using namespace BackendIniBit::Functown;
using namespace CAT(Backends::nulike_,NULIKE_SAFE_VERSION)::Functown;

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
    bool use_lnpiln = settings.getValueOrDef<bool>(false, "use_lognormal_distribution_for_1d_systematic");
    double jet_pt_min = settings.getValueOrDef<double>(10.0, "jet_pt_min");
    str event_filename = settings.getValue<str>("event_file");
    bool event_file_is_LHEF = Gambit::Utils::endsWith(event_filename, ".lhe");
    bool event_file_is_HepMC = (   Gambit::Utils::endsWith(event_filename, ".hepmc")
                                || Gambit::Utils::endsWith(event_filename, ".hepmc2")
                                || Gambit::Utils::endsWith(event_filename, ".hepmc3") );
    if (not event_file_is_LHEF and not event_file_is_HepMC)
     throw std::runtime_error("Unrecognised event file format in "+event_filename+"; must be .lhe or .hepmc.");

    // Choose the event file reader according to file format
    if (debug) cout << "Reading " << (event_file_is_LHEF ? "LHEF" : "HepMC") << " file: " << event_filename << endl;
    auto& getEvent = (event_file_is_LHEF ? getLHEvent : getHepMCEvent);

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

    // Pass the filename and the jet pt cutoff to the LHEF/HepMC reader function
    getEvent.setOption<str>((event_file_is_LHEF ? "lhef_filename" : "hepmc_filename"), event_filename);
    getEvent.setOption<double>("jet_pt_min", jet_pt_min);

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
    calc_LHC_LogLikes.setOption<int>("covariance_nsamples_start", settings.getValue<int>("covariance_nsamples_start"));
    calc_LHC_LogLikes.setOption<double>("covariance_marg_convthres_abs", settings.getValue<double>("covariance_marg_convthres_abs"));
    calc_LHC_LogLikes.setOption<double>("covariance_marg_convthres_rel", settings.getValue<double>("covariance_marg_convthres_rel"));

    // Resolve ColliderBit dependencies and backend requirements
    calc_combined_LHC_LogLike.resolveDependency(&get_LHC_LogLike_per_analysis);
    calc_combined_LHC_LogLike.resolveDependency(&operateLHCLoop);
    get_LHC_LogLike_per_analysis.resolveDependency(&calc_LHC_LogLikes);
    calc_LHC_LogLikes.resolveDependency(&CollectAnalyses);
    calc_LHC_LogLikes.resolveDependency(&operateLHCLoop);
    calc_LHC_LogLikes.resolveBackendReq(use_lnpiln ? &nulike_lnpiln : &nulike_lnpin);
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
    smearEventATLAS.resolveDependency(&getEvent);
    smearEventCMS.resolveDependency(&getBuckFastCMS);
    smearEventCMS.resolveDependency(&getEvent);
    copyEvent.resolveDependency(&getBuckFastIdentity);
    copyEvent.resolveDependency(&getEvent);

    // Resolve loop manager for ColliderBit event loop
    getEvent.resolveLoopManager(&operateLHCLoop);
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
    operateLHCLoop.setNestedList(nested_functions);

    // Call the initialisation function for nulike
    nulike_1_0_7_init.reset_and_calculate();

    // Run the detector sim and selected analyses on all the events read in.
    operateLHCLoop.reset_and_calculate();
    CollectAnalyses.reset_and_calculate();
    calc_LHC_LogLikes.reset_and_calculate();
    get_LHC_LogLike_per_analysis.reset_and_calculate();
    calc_combined_LHC_LogLike.reset_and_calculate();

    // Retrieve and print the predicted + observed counts and likelihoods for the individual SRs and analyses, as well as the total likelihood.
    int n_events = operateLHCLoop(0).event_count.at("CBS");
    std::stringstream summary_line;
    for (size_t analysis = 0; analysis < CollectAnalyses(0).size(); ++analysis)
    {
      const Gambit::ColliderBit::AnalysisData& adata = *(CollectAnalyses(0).at(analysis));
      const str& analysis_name = adata.analysis_name;
      const Gambit::ColliderBit::AnalysisLogLikes& analysis_loglikes = calc_LHC_LogLikes(0).at(analysis_name);
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
        auto loglike_it = analysis_loglikes.sr_loglikes.find(srData.sr_label);
        if (loglike_it != analysis_loglikes.sr_loglikes.end())
        {
          summary_line << "      Log-likelihood: " << loglike_it->second << endl;
        }
      }
      summary_line << "    Selected signal region: " << analysis_loglikes.combination_sr_label << endl;
      summary_line << "    Total log-likelihood for analysis:" << analysis_loglikes.combination_loglike << endl << endl;
    }
    double loglike = calc_combined_LHC_LogLike(0);

    cout.precision(5);
    cout << endl;
    cout << "Read and analysed " << n_events << " events from " << (event_file_is_LHEF ? "LHE" : "HepMC") << " file." << endl << endl;
    cout << "Analysis details:" << endl << endl << summary_line.str() << endl;
    cout << std::scientific << "Total combined ATLAS+CMS log-likelihood: " << loglike << endl;
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

