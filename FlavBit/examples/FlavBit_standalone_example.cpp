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
    deltaMB_likelihood.resolveDependency(&FH_DeltaMs);

    // FH_deltaMs depends on:
    //    - FH_FlavourObs
    FH_DeltaMs.resolveDependency(&FH_FlavourObs);

    // FH_FlavourObs has only one backend requirement:
    //    - FHFlavour
    FH_FlavourObs.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHFlavour);

    // The FeynHiggs initialisation function depends on:
    //    - unimproved_MSSM_spectrum
    FeynHiggs_2_11_3_init.resolveDependency(&createSpectrum);

    // Set up the b2sll_LL likelihood
    // Have to resolve dependencies by hand
    // b2sll_likelihood depends on:
    //    - b2sll_M
    b2sll_likelihood.resolveDependency(&b2sll_measurements);

    //SI_fill needs on:
    //   - BEreq Init_param
    //   - BEreq slha_adjust
    //   - BEreq mb_1S
    //   - MSSM_spectrum (or SM_spectrum)
    //   - W_plus_decay_rates
    //   - Z_decay_rates
    SI_fill.resolveDependency(&relabelSpectrum);
    SI_fill.resolveDependency(&GammaZ);
    SI_fill.resolveDependency(&GammaW);
    SI_fill.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Init_param);
    SI_fill.resolveBackendReq(&Backends::SuperIso_3_6::Functown::slha_adjust);
    SI_fill.resolveBackendReq(&Backends::SuperIso_3_6::Functown::mb_1S);

    // b2sll_measurements depends on:
    //   - BKstarmumu_11_25
    //   - BKstarmumu_25_40
    //   - BKstarmumu_40_60
    //   - BKstarmumu_60_80
    //   - BKstarmumu_15_17
    //   - BKstarmumu_17_19
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_11_25);
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_25_40);
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_40_60);
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_60_80);
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_15_17);
    b2sll_measurements.resolveDependency(&SI_BKstarmumu_17_19);

    // Now resolve dependencies of the BKstar mu mu measurements
    // Each depends on:
    // - SI_fill
    // Each has a BE requirement on:
    // - BKstarmumu_CONV (from SuperIso)
    SI_BKstarmumu_11_25.resolveDependency(&SI_fill);
    SI_BKstarmumu_11_25.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);
    SI_BKstarmumu_25_40.resolveDependency(&SI_fill);
    SI_BKstarmumu_25_40.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);
    SI_BKstarmumu_40_60.resolveDependency(&SI_fill);
    SI_BKstarmumu_40_60.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);
    SI_BKstarmumu_60_80.resolveDependency(&SI_fill);
    SI_BKstarmumu_60_80.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);
    SI_BKstarmumu_15_17.resolveDependency(&SI_fill);
    SI_BKstarmumu_15_17.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);
    SI_BKstarmumu_17_19.resolveDependency(&SI_fill);
    SI_BKstarmumu_17_19.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BKstarmumu_CONV);

    // Now do the b2ll likelihood
    b2ll_likelihood.resolveDependency(&b2ll_measurements);

    // b2ll_measurements depends on:
    // - Bsmumu_untag
    // - Bmumu
    b2ll_measurements.resolveDependency(&SI_Bsmumu_untag);
    b2ll_measurements.resolveDependency(&SI_Bmumu);

    // Resolve dependencies of SI_Bsmumu_untag
    // These are:
    //  - SI_fill
    // Plus BE reqs:
    //  - Bsll_untag_CONV
    SI_Bsmumu_untag.resolveDependency(&SI_fill);
    SI_Bsmumu_untag.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Bsll_untag_CONV);

    // Resolve dependencies of SI_Bmumu
    // These are:
    //  - SI_fill
    // Plus BE reqs:
    // - Bmumu
    // - CW_calculator
    // - C_calculator_base1
    // - CQ_calculator
    SI_Bmumu.resolveDependency(&SI_fill);
    SI_Bmumu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Bll_CONV);

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
    SI_Btaunu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Btaunu);
    SI_BDtaunu.resolveDependency(&SI_fill);
    SI_BDtaunu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BRBDlnu);
    SI_RD.resolveDependency(&SI_fill);
    SI_RD.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BDtaunu_BDenu);
    SI_RDstar.resolveDependency(&SI_fill);
    SI_RDstar.resolveBackendReq(&Backends::SuperIso_3_6::Functown::BDstartaunu_BDstarenu);
    SI_Dstaunu.resolveDependency(&SI_fill);
    SI_Dstaunu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Dstaunu);
    SI_Dsmunu.resolveDependency(&SI_fill);
    SI_Dsmunu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Dsmunu);
    SI_Dmunu.resolveDependency(&SI_fill);
    SI_Dmunu.resolveBackendReq(&Backends::SuperIso_3_6::Functown::Dmunu);

    // Now resolve dependencies for the b->sgamma likelihoods
    b2sgamma_likelihood.resolveDependency(&SI_bsgamma);

    // Resolve dependencies and backend requirements of SI_bsgamma:
    // - SI_fill
    // Plus BE reqs:
    // - bsgamma_CONV
    SI_bsgamma.resolveDependency(&SI_fill);
    SI_bsgamma.resolveBackendReq(&Backends::SuperIso_3_6::Functown::bsgamma_CONV);

    // Double-check which backend requirements have been filled with what
    std::cout << std::endl << "My function SI_fill has had its backend requirement on Init_param filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SI_fill::BEreq::Init_param.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::BEreq::Init_param.name() << std::endl;
    std::cout << std::endl << "My function SI_fill has had its backend requirement on slha_adjust filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SI_fill::BEreq::slha_adjust.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::BEreq::slha_adjust.name() << std::endl;

    // Double-check which backend requirements have been filled with what
    std::cout << std::endl << "My function SI_Bmumu  has had its backend requirement on Bll_CONV filled by:" << std::endl;
    std::cout << FlavBit::Pipes::SI_Bmumu::BEreq::Bll_CONV.origin() << "::";
    std::cout << FlavBit::Pipes::SI_Bmumu::BEreq::Bll_CONV.name() << std::endl;

    // Double-check which dependencies have been filled with whatever (not every combination is shown)
    std::cout << std::endl << "My function SI_fill has had its dependency on MSSM_spectrum filled by:" << endl;
    std::cout << FlavBit::Pipes::SI_fill::Dep::MSSM_spectrum.origin() << "::";
    std::cout << FlavBit::Pipes::SI_fill::Dep::MSSM_spectrum.name() << std::endl;

    std::cout << std::endl << "My function b2sll_likelihood has had its dependency on b2sll_M filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_likelihood::Dep::b2sll_M.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_likelihood::Dep::b2sll_M.name() << std::endl;

    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_11_25 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_11_25.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_11_25.name() << std::endl;
    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_25_40 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_25_40.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_25_40.name() << std::endl;
    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_40_60 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_40_60.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_40_60.name() << std::endl;
    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_60_80 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_60_80.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_60_80.name() << std::endl;
    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_15_17 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_15_17.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_15_17.name() << std::endl;
    std::cout << std::endl << "My function b2sll_measurements has had its dependency on BKstarmumu_17_19 filled by:" << endl;
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_17_19.origin() << "::";
    std::cout << FlavBit::Pipes::b2sll_measurements::Dep::BKstarmumu_17_19.name() << std::endl;

    // Now we start the actual calculations (which we would loop over if doing a scan).
    double loglike;
    std::cout << std::endl;

    // Initialise the spectra
    createSpectrum.reset_and_calculate();
    relabelSpectrum.reset_and_calculate();

    // Initialise the backends
    SuperIso_3_6_init.reset_and_calculate();
    FeynHiggs_2_11_3_init.reset_and_calculate();

    // Now call the module functions in an appropriate order
    SI_fill.reset_and_calculate();

    // Calculate the B meson mass asymmetry likelihood
    FH_FlavourObs.reset_and_calculate();
    FH_DeltaMs.reset_and_calculate();
    deltaMB_likelihood.reset_and_calculate();
    loglike = deltaMB_likelihood(0);
    std::cout << std::endl << "B meson mass asymmetry log-likelihood: " << loglike << std::endl;

    // Calculate the B -> ll likelihood
    SI_Bsmumu_untag.reset_and_calculate();
    SI_Bmumu.reset_and_calculate();
    b2ll_measurements.reset_and_calculate();
    b2ll_likelihood.reset_and_calculate();
    loglike = b2ll_likelihood(0);
    std::cout << "Fully leptonic B decays (B->ll) joint log-likelihood: " << loglike << std::endl;

    // Calculate the B -> Xs ll likelihood
    SI_BKstarmumu_11_25.reset_and_calculate();
    SI_BKstarmumu_25_40.reset_and_calculate();
    SI_BKstarmumu_40_60.reset_and_calculate();
    SI_BKstarmumu_60_80.reset_and_calculate();
    SI_BKstarmumu_15_17.reset_and_calculate();
    SI_BKstarmumu_17_19.reset_and_calculate();
    b2sll_measurements.reset_and_calculate();
    b2sll_likelihood.reset_and_calculate();
    loglike = b2sll_likelihood(0);
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
    SI_bsgamma.reset_and_calculate();
    b2sgamma_likelihood.reset_and_calculate();
    loglike = b2sgamma_likelihood(0);
    std::cout << "B->X_s gamma log-likelihood: " << loglike << std::endl;

    std::cout << endl;

  }

  catch (std::exception& e)
  {
    std::cout << "FlavBit_standalone example has exited with fatal exception: " << e.what() << std::endl;
  }

}
