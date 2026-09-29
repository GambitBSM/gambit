//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module Higgs functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Mar
///
///  *********************************************

#pragma once

#define MODULE ColliderBit

  // HiggsBounds input model parameters
  #define CAPABILITY HB_ModelParameters
  START_CAPABILITY

    // SM-like Higgs model parameters, for SM and BSM models with only one Higgs.
    #define FUNCTION SMLikeHiggs_ModelParameters
    START_FUNCTION(hb_ModelParameters)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, StandardModel_Higgs, StandardModel_Higgs_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    ALLOW_MODELS(StandardModel_Higgs_running, ScalarSingletDM_Z3_running, ScalarSingletDM_Z2_running)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

    // MSSM-like Higgs model parameters, for BSM models with MSSM-like sectors (MSSM, NMSSM, ...)
    #define FUNCTION MSSMLikeHiggs_ModelParameters
    START_FUNCTION(hb_ModelParameters)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

  #undef CAPABILITY


  // Get a LEP Higgs chisq
  #define CAPABILITY LEP_Higgs_LogLike
  START_CAPABILITY

    #define FUNCTION calc_HB_LEP_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters, hb_ModelParameters)
    BACKEND_REQ(HiggsBounds_neutral_input_part, (libhiggsbounds), void,
    (double*, double*, int*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*))
    BACKEND_REQ(HiggsBounds_charged_input, (libhiggsbounds), void,
    (double*, double*, double*, double*,
    double*, double*, double*, double*))
    BACKEND_REQ(HiggsBounds_set_mass_uncertainties, (libhiggsbounds), void, (double*, double*))
    BACKEND_REQ(run_HiggsBounds_classic, (libhiggsbounds), void, (int&, int&, double&, int&))
    BACKEND_REQ(HB_calc_stats, (libhiggsbounds), void, (double&, double&, double&, int&))
    BACKEND_OPTION( (HiggsBounds), (libhiggsbounds) )
    #undef FUNCTION

  #undef CAPABILITY


  // Get an LHC Higgs chisq
  #define CAPABILITY LHC_Higgs_LogLike
  START_CAPABILITY

    #define FUNCTION calc_HS_LHC_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters, hb_ModelParameters)
    BACKEND_REQ(HiggsBounds_neutral_input_part_HS, (libhiggssignals), void,
    (double*, double*, int*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*, double*, double*, double*, double*,
    double*, double*, double*))
    BACKEND_REQ(HiggsBounds_charged_input_HS, (libhiggssignals), void,
    (double*, double*, double*, double*,
     double*, double*, double*, double*))
    BACKEND_REQ(run_HiggsSignals, (libhiggssignals), void, (int&, double&, double&, double&, int&, double&))
    BACKEND_REQ(HiggsSignals_neutral_input_MassUncertainty, (libhiggssignals), void, (double*))
    BACKEND_REQ(setup_rate_uncertainties, (libhiggssignals), void, (double*, double*))
    BACKEND_OPTION( (HiggsSignals, 1.4), (libhiggssignals) )
    #undef FUNCTION

  #undef CAPABILITY


  // Higgs production cross-sections from FeynHiggs.
  // Not presently used by anything, but maybe useful in the future.
  #define CAPABILITY Higgs_Production_Xsecs
  START_CAPABILITY
    #define FUNCTION FeynHiggs_HiggsProd
    START_FUNCTION(fh_HiggsProd_container)
    BACKEND_REQ(FHHiggsProd, (libfeynhiggs), void, (int&, fh_real&, Farray< fh_real,1,52>&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    #undef FUNCTION
  #undef CAPABILITY

  // Total (gg->h + bb->h) production cross section at NNLO [pb], LHC 13 TeV,
  // for the lightest CP-even MSSM Higgs h, from SusHi.  Both channels come
  // from a single SusHi run (see SusHi_run_point), called directly here so
  // this capability can later be marked emulatable without paying for the
  // SusHi computation on points where the emulator's prediction is trusted.
  #define CAPABILITY SusHi_h_xsec_total_cap
  START_CAPABILITY
    #define FUNCTION getSusHi_h_xsec_total
    START_FUNCTION_EMULATABLE(double)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    BACKEND_REQ(SusHi_run_point, (libsushi), void, (const Spectrum&, double&, double&))
    ALLOW_MODELS( MSSM9batQ_mA, MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG )
    // BACKEND_OPTION( (SusHi, 1.7.0), (libsushi) )
    #undef FUNCTION
  #undef CAPABILITY

  // Signal strength mu_gammagamma = [sigma(pp->h) x BR(h->gammagamma)] / SM
  // reference, for the lightest MSSM CP-even Higgs h (candidate for the
  // ~95 GeV excess). ALLOW_MODELS restricted to the MSSM63at* family because
  // Higgs_decay_rates (unlike SusHi_h_xsec_total_cap) doesn't support
  // MSSM9batQ_mA. See getMu_gammagamma_h95 in ColliderBit_Higgs.cpp for full
  // sourcing of the SM reference value.
  #define CAPABILITY mu_gammagamma_h95_cap
  START_CAPABILITY
    #define FUNCTION getMu_gammagamma_h95
    START_FUNCTION(double)
    DEPENDENCY(SusHi_h_xsec_total_cap, double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS( MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG )
    #undef FUNCTION
  #undef CAPABILITY

  // sigma(pp->h) x BR(h->tautau) [pb], for the lightest MSSM CP-even Higgs h.
  // Compared directly against the CMS-quoted raw rate (not a ratio to SM) in
  // calc_Higgs95_LogLike -- see getSigmaBR_tautau_h95 in ColliderBit_Higgs.cpp.
  #define CAPABILITY sigmaBR_tautau_h95_cap
  START_CAPABILITY
    #define FUNCTION getSigmaBR_tautau_h95
    START_FUNCTION(double)
    DEPENDENCY(SusHi_h_xsec_total_cap, double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS( MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG )
    #undef FUNCTION
  #undef CAPABILITY

  // Combined chi^2-based log-likelihood for the ~95 GeV diphoton + ditau
  // excesses. Every target/reference value is read via runOptions (see
  // calc_Higgs95_LogLike in ColliderBit_Higgs.cpp for defaults, sources and
  // how to override them from a yaml Rules: entry without recompiling).
  #define CAPABILITY Higgs95_LogLike
  START_CAPABILITY
    #define FUNCTION calc_Higgs95_LogLike
    START_FUNCTION(double)
    DEPENDENCY(mu_gammagamma_h95_cap, double)
    DEPENDENCY(sigmaBR_tautau_h95_cap, double)
    ALLOW_MODELS( MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG )
    #undef FUNCTION
  #undef CAPABILITY


#undef MODULE
