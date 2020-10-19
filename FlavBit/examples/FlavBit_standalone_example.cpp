//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Example of GAMBIT FlavBit standalone
///  main program.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Martin White
///          (martin.white@adelaide.edu.au)
///  \date Jan 2016
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date Sep 2016
///
///  \author Nazila Mahmoudi
///          (nazila@cern.ch)
///  \date Aug 2019
///
///  \author Markus Prim
///          (markus.prim@cern.ch)
///  \date Oct 2020
///
///  *********************************************

// Always required in any standalone module main file
#include "gambit/Elements/standalone_module.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"

// Just required in this one
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"

using namespace FlavBit::Functown;      // Functors wrapping the module's actual module functions
using namespace BackendIniBit::Functown;    // Functors wrapping the backend initialisation functions

// Default SLHA file for input, if not given on the command line.
std::string infile("FlavBit/data/example.slha");

QUICK_FUNCTION(FlavBit, unimproved_MSSM_spectrum, NEW_CAPABILITY, createSpectrum, Spectrum, (MSSM30atQ,MSSM30atMGUT))
QUICK_FUNCTION(FlavBit, MSSM_spectrum, NEW_CAPABILITY, relabelSpectrum, Spectrum, (MSSM30atQ,MSSM30atMGUT), (unimproved_MSSM_spectrum, Spectrum))
QUICK_FUNCTION(FlavBit, Z_decay_rates, NEW_CAPABILITY, GammaZ, DecayTable::Entry)
QUICK_FUNCTION(FlavBit, W_plus_decay_rates, NEW_CAPABILITY, GammaW, DecayTable::Entry)

namespace Gambit
{
  namespace FlavBit
  {

    /// Make an unimproved GAMBIT spectrum object from an SLHA file
    void createSpectrum(Spectrum& outSpec)
    {
      outSpec = spectrum_from_SLHA<MSSMSimpleSpec>(infile, Spectrum::mc_info(), Spectrum::mr_info());
    }

    /// Relabel it as a complete spectrum
    void relabelSpectrum(Spectrum& outSpec)
    {
      outSpec = *Pipes::relabelSpectrum::Dep::unimproved_MSSM_spectrum;
    }

    /// W decays -- only need the total width for SuperIso
    void GammaW(DecayTable::Entry& result)
    {
      result.width_in_GeV = 2.085;
    }

    /// Z decays -- only need the total width for SuperIso
    void GammaZ(DecayTable::Entry& result)
    {
      result.width_in_GeV = 2.4952;
    }

  }
}

int main(int argc, char** argv)
{

  cout << "Starting FlavBit_standalone" << endl;

  try
  {

    // Get the SLHA filename from the command line, if it has been given.
    if (argc >= 2) infile = argv[1];

    // Make a logging object
    std::map<std::string, std::string> loggerinfo;

    // Define where the logs will end up
    std::string prefix("runs/FlavBit_standalone/logs/");

    // Ensure that the above directory exists
    Utils::ensure_path_exists(prefix);

    // Add entries to the loggerinfo map
    loggerinfo["Core, Error"] = prefix+"core_errors.log";
    loggerinfo["Default"]     = prefix+"default.log";
    loggerinfo["Warning"]     = prefix+"warnings.log";
    loggerinfo["FlavBit, Info"] = prefix+"FlavBit_info.log";

    // Initialise global LogMaster object
    logger().initialise(loggerinfo);

    logger()<<"Running FlavBit standalone example"<<LogTags::info<<EOM;

    // Notify all module functions that care of the model being scanned.
    createSpectrum.notifyOfModel("MSSM30atQ");
    relabelSpectrum.notifyOfModel("MSSM30atQ");
    SI_fill.notifyOfModel("MSSM30atQ");

    // Arrange the spectrum chain
    relabelSpectrum.resolveDependency(&createSpectrum);

    // Set up the deltaMB_LL likelihood
    // Have to resolve dependencies by hand
    // deltaMB_likelihood depends on:
    //    - deltaMs
    deltaMB_likelihood.resolveDependency(&FeynHiggs_prediction_DeltaMs);

    // FeynHiggs_prediction_DeltaMs depends on:
    //    - FH_FlavourObs
    FeynHiggs_prediction_DeltaMs.resolveDependency(&FH_FlavourObs);

    // FH_FlavourObs has only one backend requirement:
    //    - FHFlavour
    FH_FlavourObs.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHFlavour);

    // The FeynHiggs initialisation function depends on:
    //    - unimproved_MSSM_spectrum
    FeynHiggs_2_11_3_init.resolveDependency(&createSpectrum);

    // Set up the HEPLike_B2KstarmumuAng_LogLikelihood_LHCb likelihood
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb);
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb);
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb);
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_4_6_LHCb);
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_6_8_LHCb);
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2KstarmumuAng_15_19_LHCb);

    //SI_fill needs on:
    //   - BEreq Init_param
    //   - BEreq slha_adjust
    //   - BEreq mcmc_from_pole
    //   - BEreq mb_1S
    //   - MSSM_spectrum (or SM_spectrum)
    //   - W_plus_decay_rates
    //   - Z_decay_rates
    SI_fill.resolveDependency(&relabelSpectrum);
    SI_fill.resolveDependency(&GammaZ);
    SI_fill.resolveDependency(&GammaW);
    SI_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::Init_param);
    SI_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::slha_adjust);
    SI_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::mcmc_from_pole);
    SI_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::mb_1S);

    // Now resolve dependencies of the BKstar mu mu measurements
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);
    
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);
    
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);
    
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);
    
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);
    
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.setOption<std::vector<std::string>>("obs_list", {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"});
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveDependency(&SI_fill);
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);

    // Now do the HEPLike_B2mumu_LogLikelihood_LHCb
    HEPLike_B2mumu_LogLikelihood_LHCb.setOption<std::vector<std::string>>("obs_list", {"BRuntag_Bsmumu", "BR_Bdmumu"});
    HEPLike_B2mumu_LogLikelihood_LHCb.resolveDependency(&SuperIso_prediction_B2mumu);

    // Resolve dependencies of SuperIso_prediction_B2mumu
    SuperIso_prediction_B2mumu.setOption<std::vector<std::string>>("obs_list", {"BRuntag_Bsmumu", "BR_Bdmumu"});
    SuperIso_prediction_B2mumu.resolveDependency(&SI_fill);
    SuperIso_prediction_B2mumu.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_B2mumu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_B2mumu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_B2mumu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_B2mumu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);

    // Now do the semi-leptonic likelihood SL_LL
    // This depends on:
    // - SL_M
    SL_likelihood.resolveDependency(&SL_measurements);

    // Resolve dependencies of SL_measurements
    // which are:
    // - RD
    // - RDstar
    // - BDmunu
    // - BDstarmunu
    // - Btaunu
    // - Dstaunu
    // - Dsmunu
    // - Dmunu
    SL_measurements.resolveDependency(&SI_RD);
    SL_measurements.resolveDependency(&SI_RDstar);
    SL_measurements.resolveDependency(&SI_BDmunu);
    SL_measurements.resolveDependency(&SI_BDstarmunu);
    SL_measurements.resolveDependency(&SI_Btaunu);
    SL_measurements.resolveDependency(&SI_Dsmunu);
    SL_measurements.resolveDependency(&SI_Dstaunu);
    SL_measurements.resolveDependency(&SI_Dmunu);

    // Resolve all of the individual dependencies and backend reqs
    // These are:
    // - SI_fill
    // BE Req: BDtaunu, etc
    SI_Btaunu.resolveDependency(&SI_fill);
    SI_Btaunu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::Btaunu);
    SI_BDtaunu.resolveDependency(&SI_fill);
    SI_BDtaunu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::BRBDlnu);
    SI_RD.resolveDependency(&SI_fill);
    SI_RD.resolveBackendReq(&Backends::SuperIso_4_1::Functown::BDtaunu_BDenu);
    SI_RDstar.resolveDependency(&SI_fill);
    SI_RDstar.resolveBackendReq(&Backends::SuperIso_4_1::Functown::BDstartaunu_BDstarenu);
    SI_Dstaunu.resolveDependency(&SI_fill);
    SI_Dstaunu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::Dstaunu);
    SI_Dsmunu.resolveDependency(&SI_fill);
    SI_Dsmunu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::Dsmunu);
    SI_Dmunu.resolveDependency(&SI_fill);
    SI_Dmunu.resolveBackendReq(&Backends::SuperIso_4_1::Functown::Dmunu);

    // Now resolve dependencies for the b->sgamma likelihoods
    HEPLike_b2sgamma_LogLikelihood.resolveDependency(&SuperIso_prediction_b2sgamma);

    // Resolve dependencies and backend requirements of SuperIso_prediction_b2sgamma:
    SuperIso_prediction_b2sgamma.resolveDependency(&SI_fill);
    SuperIso_prediction_b2sgamma.resolveDependency(&SI_nuisance_fill);
    SuperIso_prediction_b2sgamma.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);
    SuperIso_prediction_b2sgamma.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
    SuperIso_prediction_b2sgamma.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
    SuperIso_prediction_b2sgamma.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);

    // Double-check which backend requirements have been filled with what
    std::cout << std::endl << "My function SI_fill has had its backend requirement on Init_param filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SI_fill::BEreq::Init_param.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::BEreq::Init_param.name() << std::endl;
    std::cout << std::endl << "My function SI_fill has had its backend requirement on slha_adjust filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SI_fill::BEreq::slha_adjust.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::BEreq::slha_adjust.name() << std::endl;

    // Double-check which backend requirements have been filled with what
    std::cout << std::endl << "My function SuperIso_prediction_B2mumu  has had its backend requirement on Bll_CONV filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::get_predictions_nuisance.origin() << "::";
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::get_predictions_nuisance.name() << std::endl;
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::observables.origin() << "::";
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::observables.name() << std::endl;
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::convert_correlation.origin() << "::";
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::convert_correlation.name() << std::endl;
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::get_th_covariance_nuisance.origin() << "::";
    std::cout << FlavBit::Pipes::SuperIso_prediction_B2mumu::BEreq::get_th_covariance_nuisance.name() << std::endl;

    // Double-check which dependencies have been filled with whatever (not every combination is shown)
    std::cout << std::endl << "My function SI_fill has had its dependency on MSSM_spectrum filled by:" << endl;
    std::cout << FlavBit::Pipes::SI_fill::Dep::MSSM_spectrum.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::Dep::MSSM_spectrum.name() << std::endl;

    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_11_25 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb.name() << std::endl;
    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_25_40 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_1p1_2p5_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_1p1_2p5_LHCb.name() << std::endl;
    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_40_60 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_2p5_4_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_2p5_4_LHCb.name() << std::endl;
    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_60_80 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_2p5_4_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_2p5_4_LHCb.name() << std::endl;
    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_15_17 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_6_8_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_6_8_LHCb.name() << std::endl;
    std::cout << std::endl << "My function HEPLike_B2KstarmumuAng_LogLikelihood_LHCb has had its dependency on BKstarmumu_17_19 filled by:" << endl;
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_15_19_LHCb.origin() << "::";
    std::cout << FlavBit::Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb::Dep::prediction_B2KstarmumuAng_15_19_LHCb.name() << std::endl;

    // Now we start the actual calculations (which we would loop over if doing a scan).
    double loglike;
    std::cout << std::endl;

    // Initialise the spectra
    createSpectrum.reset_and_calculate();
    relabelSpectrum.reset_and_calculate();

    // Initialise the backends
    SuperIso_4_1_init.reset_and_calculate();
    FeynHiggs_2_11_3_init.reset_and_calculate();

    // Now call the module functions in an appropriate order
    SI_fill.reset_and_calculate();

    // Calculate the B meson mass asymmetry likelihood
    FH_FlavourObs.reset_and_calculate();
    FeynHiggs_prediction_DeltaMs.reset_and_calculate();
    deltaMB_likelihood.reset_and_calculate();
    loglike = deltaMB_likelihood(0);
    std::cout << std::endl << "B meson mass asymmetry log-likelihood: " << loglike << std::endl;

    // Calculate the B -> ll likelihood
    SuperIso_prediction_B2mumu.reset_and_calculate();
    HEPLike_B2mumu_LogLikelihood_LHCb.reset_and_calculate();
    loglike = HEPLike_B2mumu_LogLikelihood_LHCb(0);
    std::cout << "Fully leptonic B decays (B->ll) joint log-likelihood: " << loglike << std::endl;

    // Calculate the B -> Xs ll likelihood
    SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb.reset_and_calculate();
    SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb.reset_and_calculate();
    SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb.reset_and_calculate();
    SuperIso_prediction_B2KstarmumuAng_4_6_LHCb.reset_and_calculate();
    SuperIso_prediction_B2KstarmumuAng_6_8_LHCb.reset_and_calculate();
    SuperIso_prediction_B2KstarmumuAng_15_19_LHCb.reset_and_calculate();
    HEPLike_B2KstarmumuAng_LogLikelihood_LHCb.reset_and_calculate();
    loglike = HEPLike_B2KstarmumuAng_LogLikelihood_LHCb(0);
    std::cout << "Leptonic penguin B decays (B->X_s ll) joint log-likelihood: " << loglike << std::endl;

    // Calculate the semi-leptonic (SL) likelihood
    SI_Btaunu.reset_and_calculate();
    SI_BDtaunu.reset_and_calculate();
    SI_RD.reset_and_calculate();
    SI_RDstar.reset_and_calculate();
    SI_Dstaunu.reset_and_calculate();
    SI_Dsmunu.reset_and_calculate();
    SI_Dmunu.reset_and_calculate();
    SL_measurements.reset_and_calculate();
    SL_likelihood.reset_and_calculate();
    loglike = SL_likelihood(0);
    std::cout << "Semi-leptonic B decays (B->D l nu) joint log-likelihood: " << loglike << std::endl;

    // Calculate the B -> X_s gamma likelihood
    SuperIso_prediction_b2sgamma.reset_and_calculate();
    HEPLike_b2sgamma_LogLikelihood.reset_and_calculate();
    loglike = HEPLike_b2sgamma_LogLikelihood(0);
    std::cout << "B->X_s gamma log-likelihood: " << loglike << std::endl;

    std::cout << endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "testing new SuperIso v4.1 routines..." << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << endl;

    SI_nuisance_fill.resolveDependency(&SI_fill);
    SI_nuisance_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::set_nuisance);
    SI_nuisance_fill.resolveBackendReq(&Backends::SuperIso_4_1::Functown::set_nuisance_value_from_param);

    SI_compute_obs_list.setOption<std::vector<std::string>>("SuperIso_obs_list", {"AI_BKstargamma","BR_BXsgamma","BRuntag_Bsmumu","BR_Bdmumu","BR_BXsmumu_1_6","BR_BXsmumu_14.2_22","BR_BXsee_1_6","BR_BXsee_14.2_22","BR_B0Kstar0gamma","dGamma/dq2_B0Kstar0mumu_0.1_0.98"});
    SI_compute_obs_list.resolveDependency(&SI_fill);
    SI_compute_obs_list.resolveDependency(&SI_nuisance_fill);
    SI_compute_obs_list.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_predictions_nuisance);

//    SI_theory_covariance.setOption<std::vector<std::string>>("SuperIso_obs_list", {"AI_BKstargamma","BR_BXsgamma","BRuntag_Bsmumu","BR_Bdmumu","BR_BXsmumu_1_6","BR_BXsmumu_14.2_22","BR_BXsee_1_6","BR_BXsee_14.2_22","BR_B0Kstar0gamma","dGamma/dq2_B0Kstar0mumu_0.1_0.98"});
//    SI_theory_covariance.resolveDependency(&SI_fill);
//    SI_theory_covariance.resolveDependency(&SI_nuisance_fill);
//    SI_theory_covariance.resolveBackendReq(&Backends::SuperIso_4_1::Functown::observables);
//    SI_theory_covariance.resolveBackendReq(&Backends::SuperIso_4_1::Functown::convert_correlation);
//    SI_theory_covariance.resolveBackendReq(&Backends::SuperIso_4_1::Functown::get_th_covariance_nuisance);

//    SI_nuisance_fill.reset_and_calculate();
//    SI_compute_obs_list.reset_and_calculate();
//    SI_theory_covariance.reset_and_calculate();
  }

  catch (std::exception& e)
  {
    std::cout << "FlavBit_standalone example has exited with fatal exception: " << e.what() << std::endl;
  }

}
