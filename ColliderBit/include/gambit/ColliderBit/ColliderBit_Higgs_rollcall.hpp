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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#pragma once

#define MODULE ColliderBit

  // HiggsBounds input model parameters nuetral
  #define CAPABILITY HB_ModelParameters_neutral
  START_CAPABILITY

    // SM-like Higgs model parameters, for SM and BSM models with only one Higgs.
    #define FUNCTION SMLikeHiggs_ModelParameters
    START_FUNCTION(hb_ModelParameters)
    START_FUNCTION(hb_neutral_ModelParameters_part)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, StandardModel_Higgs, StandardModel_Higgs_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    ALLOW_MODELS(StandardModel_Higgs_running, ScalarSingletDM_Z3_running, ScalarSingletDM_Z2_running)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

    // MSSM-like Higgs model parameters, for BSM models with MSSM-like sectors (MSSM, NMSSM, ...)
    #define FUNCTION MSSMLikeHiggs_ModelParameters
    START_FUNCTION(hb_neutral_ModelParameters_part)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(THDM_spectrum, Spectrum, THDM, THDMatQ)
    ALLOW_MODELS(MSSM63atMGUT, MSSM63atQ, THDM, THDMatQ)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

    // MSSM-like Higgs model parameters, for BSM models with MSSM-like sectors (MSSM, NMSSM, ...) (effc)
    #define FUNCTION MSSMLikeHiggs_ModelParameters_effc
    START_FUNCTION(hb_neutral_ModelParameters_effc)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(THDM_spectrum, Spectrum, THDM, THDMatQ)
    ALLOW_MODELS(MSSM63atMGUT, MSSM63atQ, THDM, THDMatQ)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

  #undef CAPABILITY

  // HiggsBounds input model parameters charged
  #define CAPABILITY HB_ModelParameters_charged
  START_CAPABILITY

    // SM Higgs model parameters charged
    #define FUNCTION SMHiggs_ModelParameters_charged
    START_FUNCTION(hb_charged_ModelParameters)
    #undef FUNCTION

    // SM-like Higgs model parameters, for BSM models with only one Higgs (charged-version).
    #define FUNCTION SMLikeHiggs_ModelParameters_charged
    START_FUNCTION(hb_charged_ModelParameters)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    #undef FUNCTION

    // MSSM-like Higgs charged model parameters, for BSM models with MSSM-like sectors (MSSM, NMSSM, ...)
    #define FUNCTION MSSMLikeHiggs_ModelParameters_charged
    START_FUNCTION(hb_charged_ModelParameters)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(THDM_spectrum, Spectrum, THDM, THDMatQ)
    ALLOW_MODELS(MSSM63atMGUT, MSSM63atQ, THDM, THDMatQ)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

  #undef CAPABILITY

  // Get a LEP Higgs chisq
  #define CAPABILITY LEP_Higgs_LogLike
  START_CAPABILITY
    #define FUNCTION calc_HB_LEP_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters_neutral, hb_neutral_ModelParameters_part)
    DEPENDENCY(HB_ModelParameters_charged, hb_charged_ModelParameters)
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
    BACKEND_REQ(run_HiggsBounds_full, (libhiggsbounds), void, (int*, int*, double*, int*))
    BACKEND_REQ(HB_calc_stats, (libhiggsbounds), void, (double&, double&, double&, int&))
    BACKEND_OPTION( (HiggsBounds, 4.2.1, 4.3.1), (libhiggsbounds) )
    #undef FUNCTION

    #define FUNCTION calc_HB_5_LEP_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters_neutral, hb_neutral_ModelParameters_effc)
    DEPENDENCY(HB_ModelParameters_charged, hb_charged_ModelParameters)
    BACKEND_REQ(HiggsBounds_neutral_input_properties, (libhiggsbounds), void,
    (double*, double*, double*))
    BACKEND_REQ(HiggsBounds_neutral_input_effC, (libhiggsbounds), void,
    (double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, Farray<double, 1,3, 1,3>&))
    BACKEND_REQ(HiggsBounds_neutral_input_nonSMBR, (libhiggsbounds), void,
    (double*, Farray<double, 1,3, 1,3, 1,3>&, 
    Farray<double, 1,3, 1,3>&, double*, double*, 
    double*, Farray<double, 1,3>&))
    BACKEND_REQ(HiggsBounds_charged_input, (libhiggsbounds), void,
    (double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, Farray<double, 1,3>&))
    BACKEND_REQ(HiggsBounds_set_mass_uncertainties, (libhiggsbounds), void, (double*, double*))
    BACKEND_REQ(run_HiggsBounds_classic, (libhiggsbounds), void, (int&, int&, double&, int&))
    BACKEND_REQ(HiggsBounds_get_LEPChisq, (libhiggsbounds), void, (double&, double&, double&, int&))
    BACKEND_OPTION( (HiggsBounds, 5.8.0), (libhiggsbounds) )
    #undef FUNCTION

  #undef CAPABILITY


  // Get an LHC Higgs chisq
  #define CAPABILITY LHC_Higgs_LogLike
  START_CAPABILITY
  
    #define FUNCTION calc_HS_LHC_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters_neutral, hb_neutral_ModelParameters_part)
    DEPENDENCY(HB_ModelParameters_charged, hb_charged_ModelParameters)
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
    // BACKEND_REQ(setup_rate_uncertainties, (libhiggssignals), void, (double*, double*))
    BACKEND_OPTION( (HiggsSignals, 1.4), (libhiggssignals) )
    #undef FUNCTION

    #define FUNCTION calc_HS_2_LHC_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HB_ModelParameters_neutral, hb_neutral_ModelParameters_effc)
    DEPENDENCY(HB_ModelParameters_charged, hb_charged_ModelParameters)
    BACKEND_REQ(HiggsBounds_neutral_input_properties_HS, (libhiggssignals), void,
    (double*, double*, double*))
    BACKEND_REQ(HiggsBounds_neutral_input_effC_HS, (libhiggssignals), void,
    (double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, Farray<double, 1,3, 1,3>&))
    BACKEND_REQ(HiggsBounds_neutral_input_nonSMBR_HS, (libhiggssignals), void,
    (double*, Farray<double, 1,3, 1,3, 1,3>&, 
    Farray<double, 1,3, 1,3>&, double*, double*, 
    double*, Farray<double, 1,3>&))
    BACKEND_REQ(HiggsBounds_charged_input_HS, (libhiggssignals), void,
    (double*, double*, double*, double*,
    double*, double*, double*, double*,
    double*, double*, Farray<double, 1,3>&))
    BACKEND_REQ(run_HiggsSignals, (libhiggssignals), void, (double&, double&, double&, int&, double&))
    BACKEND_REQ(run_HiggsSignals_LHC_Run1_combination, (libhiggssignals), void, (double&, double&, double&, int&, double&))
    BACKEND_REQ(run_HiggsSignals_STXS, (libhiggssignals), void, (double&, double&, double&, int&, double&))
    BACKEND_REQ(HiggsSignals_neutral_input_MassUncertainty, (libhiggssignals), void, (double*))
    // BACKEND_REQ(setup_rate_uncertainties, (libhiggssignals), void, (double*, double*))
    BACKEND_OPTION( (HiggsSignals, 2.5.0), (libhiggssignals) )
    #undef FUNCTION

  #undef CAPABILITY


  // Higgs production cross-sections from FeynHiggs.
  // Not presently used by anything, but maybe useful in the future.
  #define CAPABILITY Higgs_Production_Xsecs
  START_CAPABILITY
    #define FUNCTION FH_HiggsProd
    START_FUNCTION(fh_HiggsProd)
    BACKEND_REQ(FHHiggsProd, (libfeynhiggs), void, (int&, fh_real&, Farray< fh_real,1,52>&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    #undef FUNCTION
  #undef CAPABILITY


#undef MODULE
