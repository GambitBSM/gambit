//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_THDM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author James McKay
///  \date 2016 July, October
///  \date 2020 Apr
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date   2020 Apr
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   May 2022
///
///  *********************************************

#ifndef __SpecBit_THDM_hpp__
#define __SpecBit_THDM_hpp__

  #ifndef MODULE
    #define MODULE SpecBit
  #endif

  // Type of THDM, determined at runtime via the Yukawas
  #define CAPABILITY THDM_Type
  START_CAPABILITY
    #define FUNCTION get_THDM_Type
    START_FUNCTION(THDM_TYPE)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // Get name of the SM-like scalar. Uses the Z2-even scalar for i2HDM, otherwise picks the one closest to 125 GeV
  #define CAPABILITY SM_like_scalar
  START_CAPABILITY
    #define FUNCTION get_SM_like_scalar
    START_FUNCTION(str)
    DEPENDENCY(THDM_spectrum,Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // Get name of the additional (non SM-like) CP-even scalar
  #define CAPABILITY additional_scalar
  START_CAPABILITY
    #define FUNCTION get_additional_scalar
    START_FUNCTION(str)
    DEPENDENCY(THDM_spectrum,Spectrum)
    DEPENDENCY(SM_like_scalar,str)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY THDM_spectrum_SPheno
  START_CAPABILITY
    // THDMII spectrum using SARAH-generated SPheno
    #define FUNCTION get_THDMII_spectrum_SPheno
      START_FUNCTION(Spectrum)
      ALLOW_MODELS(THDMII, THDMIIatQ) // adding atQ for comparison with FS
      DEPENDENCY(SMINPUTS, SMInputs)
      BACKEND_REQ(SARAHSPheno_gumTHDMII_spectrum, (libSPhenogumTHDMII), int, (Spectrum&, const Finputs&) )
      BACKEND_OPTION((SARAHSPheno_gumTHDMII, 4.0.3), (libSPhenogumTHDMII))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY THDM_spectrum
  START_CAPABILITY

    // THDM Spectrum using tree-level spectrum generator
    #define FUNCTION get_THDM_spectrum_tree
      START_FUNCTION(Spectrum)
      DEPENDENCY(SMINPUTS, SMInputs)
      DEPENDENCY(THDM_Type, THDM_TYPE)
      ALLOW_MODELS(THDM)
    #undef FUNCTION

    // THDM Spectrum using FlexibleSUSY loop-level spectrum generator
    #define FUNCTION get_THDM_spectrum_FS
      START_FUNCTION(Spectrum)
      DEPENDENCY(SMINPUTS, SMInputs)
      DEPENDENCY(THDM_Type, THDM_TYPE)
      ALLOW_MODELS(THDMatQ)
    #undef FUNCTION

    // // THDMII spectrum using SARAH-generated SPheno
    // #define FUNCTION convert_THDM_spectrum_SPheno
    //   START_FUNCTION(Spectrum)
    //   DEPENDENCY(THDM_spectrum_SPheno, Spectrum)
    // #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_THDM_spectrum_as_map
      START_FUNCTION(map_str_dbl)
      DEPENDENCY(THDM_Type, THDM_TYPE)
      DEPENDENCY(THDM_spectrum, Spectrum)
      ALLOW_MODELS(THDM, THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY

  // TODO: this should be replaced by standard CouplingTable
  #define CAPABILITY effective_couplings_THDM
    START_CAPABILITY
    #define FUNCTION effective_couplings_THDM
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(THDM_spectrum_SPheno, Spectrum)
    BACKEND_REQ(SARAHSPheno_gumTHDMII_conv_get_effective_couplings, (libSPhenogumTHDMII), void, (const Spectrum&, map_str_dbl&) )
    BACKEND_REQ(SARAHSPheno_gumTHDMII_decays, (libSPhenogumTHDMII), int, (const Spectrum&, DecayTable&, const Finputs&) )
    BACKEND_OPTION((SARAHSPheno_gumTHDMII, 4.0.3), (libSPhenogumTHDMII))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY couplingtable_THDM
  START_CAPABILITY
    
    // table of all couplings in the THDM (using Higgs basis)
    #define FUNCTION get_coupling_table_using_Higgs_basis
      START_FUNCTION(CouplingTable)
      DEPENDENCY(THDM_spectrum, Spectrum)
      ALLOW_MODELS(THDM, THDMatQ)
    #undef FUNCTION
    
    // table of all couplings in the THDM (using physical basis)
    #define FUNCTION get_coupling_table_using_physical_basis
      START_FUNCTION(CouplingTable)
      DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

    // table of all couplings in the THDM (using THDMC)
    #define FUNCTION get_coupling_table_THDMC
      START_FUNCTION(CouplingTable)
      DEPENDENCY(THDM_spectrum, Spectrum)
      BACKEND_REQ(setup_thdmc_spectrum, (libTHDMC), void ,(THDMsafe&, const Spectrum&))
      BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION

  #undef CAPABILITY

  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings
  START_CAPABILITY

    // THDM Higgs couplings using only partial widths
    #define FUNCTION THDM_higgs_couplings_pwid
    START_FUNCTION(HiggsCouplingsTable)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(Reference_SM_other_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(Reference_SM_A0_decay_rates, DecayTable::Entry)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(h0_2_decay_rates, DecayTable::Entry)
    DEPENDENCY(A0_decay_rates, DecayTable::Entry)
    DEPENDENCY(H_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(t_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(DarkMatter_ID, std::string, Inert2)
    MODEL_CONDITIONAL_DEPENDENCY(DarkMatterConj_ID, std::string, Inert2)
    #undef FUNCTION

    // THDM Higgs couplings using THDMC
    #define FUNCTION THDM_higgs_couplings_2HDMC
    START_FUNCTION(HiggsCouplingsTable)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(Reference_SM_other_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(Reference_SM_A0_decay_rates, DecayTable::Entry)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(h0_2_decay_rates, DecayTable::Entry)
    DEPENDENCY(A0_decay_rates, DecayTable::Entry)
    DEPENDENCY(H_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(t_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(DarkMatter_ID, std::string, Inert2)
    MODEL_CONDITIONAL_DEPENDENCY(DarkMatterConj_ID, std::string, Inert2)
    BACKEND_REQ(setup_thdmc_spectrum, (libTHDMC), void ,(THDMsafe&, const Spectrum&))
    BACKEND_REQ(setup_thdmc_sm_like_spectrum, (libTHDMC), void ,(THDMsafe&, const Spectrum&, double))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION

    // THDM Higgs couplings from SPheno
    #define FUNCTION gumTHDMII_higgs_couplings_SPheno
    START_FUNCTION(HiggsCouplingsTable)
    DEPENDENCY(THDM_spectrum_SPheno, Spectrum)
    DEPENDENCY(decay_rates, DecayTable)
    BACKEND_REQ(SARAHSPheno_gumTHDMII_HiggsCouplingsTable, (libSPhenogumTHDMII), int, (const Spectrum&, HiggsCouplingsTable&, const Finputs&) )
    #undef FUNCTION

  #undef CAPABILITY

  // basic set of theory constraints that can be applied before spectrum generation
  #define CAPABILITY basic_theory_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION basic_theory_LogLikelihood_THDM
    START_FUNCTION(double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // check if we can run spectrum without error
  #define CAPABILITY runToScaleTest_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION runToScaleTest_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unitarity_LogLikelihood_THDM
  START_CAPABILITY

    // Leading-Order unitarity constraint (soft-cutoff)
    #define FUNCTION LO_unitarity_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION

    // Next-to-Leading-Order unitarity constraint (soft-cutoff)
    #define FUNCTION NLO_unitarity_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(couplingtable_THDM, CouplingTable)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY perturbativity_LogLikelihood_THDM
  START_CAPABILITY

    // perturbativity constraint on the scalar couplings (soft-cutoff)
    #define FUNCTION perturbativity_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(couplingtable_THDM, CouplingTable)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION

    // simple perturbativity constraint which only checks lambdas (soft-cutoff)
    #define FUNCTION perturbativity_lambdas_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // simple yukawa perturbativity constraint
  #define CAPABILITY perturbativity_yukawas_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION perturbativity_yukawas_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY stability_LogLikelihood_THDM
  START_CAPABILITY

    // vacuum stability + meta-stability constraint (soft cutoff)
    #define FUNCTION stability_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // checks that the corrections to scalars are perturbative (hard-cutoff)
  #define CAPABILITY scalar_mass_corrections_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION scalar_mass_corrections_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(runToScaleTest_LogLikelihood_THDM, double)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // guides scanner towards mh = 125 GeV (soft-cutoff)
  #define CAPABILITY higgs_exp_mass_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION higgs_exp_mass_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(SM_like_scalar, str)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // only keeps points that correspond to hidden higgs scenario (hard-cutoff)
  #define CAPABILITY higgs_scenario_LogLikelihood_THDM
  START_CAPABILITY
    #define FUNCTION higgs_scenario_LogLikelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(SM_like_scalar, str)
    DEPENDENCY(additional_scalar, str)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

#endif
