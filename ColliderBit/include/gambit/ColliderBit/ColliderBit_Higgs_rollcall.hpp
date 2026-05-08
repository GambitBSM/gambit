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

  // HiggsTools input model parameters
  #define CAPABILITY HiggsTools_ModelParameters
  START_CAPABILITY

    // SM-like Higgs model parameters, for SM and BSM models with only one Higgs.
    #define FUNCTION SMLikeHiggs_ModelParameters
    START_FUNCTION(HiggsTools_input)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, StandardModel_Higgs, StandardModel_Higgs_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    ALLOW_MODELS(StandardModel_Higgs_running, ScalarSingletDM_Z3_running, ScalarSingletDM_Z2_running)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

    // MSSM-like Higgs model parameters, for BSM models with MSSM-like sectors (MSSM, NMSSM, ...)
    #define FUNCTION MSSMLikeHiggs_ModelParameters
    START_FUNCTION(HiggsTools_input)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    #undef FUNCTION

  #undef CAPABILITY


  // Get an LHC Higgs chisq from HiggsTools (HiggsSignals).
  // HiggsTools 1.2 does not provide a dedicated LEP chi^2; the corresponding
  // capability has therefore been removed entirely along with the older
  // HiggsBounds/HiggsSignals Fortran backends.
  #define CAPABILITY LHC_Higgs_LogLike
  START_CAPABILITY

    #define FUNCTION calc_HiggsTools_LHC_LogLike
    START_FUNCTION(double)
    DEPENDENCY(HiggsTools_ModelParameters, HiggsTools_input)
    BACKEND_REQ(HiggsTools_LHC_LogLike, (libhiggstools), double, (const HiggsTools_input&))
    BACKEND_OPTION( (HiggsTools, 1.2), (libhiggstools) )
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


#undef MODULE
