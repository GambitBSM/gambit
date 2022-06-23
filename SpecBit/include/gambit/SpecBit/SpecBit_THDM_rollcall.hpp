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

  #define CAPABILITY THDM_spectrum
  START_CAPABILITY
  // Create Spectrum object from SMInputs structs, SM Higgs parameters,
  // and the THDM parameters
    #define FUNCTION get_THDM_spectrum
      START_FUNCTION(Spectrum)
      DEPENDENCY(SMINPUTS, SMInputs)
      DEPENDENCY(THDM_Type, THDM_TYPE)
      ALLOW_MODEL(THDM,THDMatQ)
    #undef FUNCTION
     // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_THDM_spectrum_as_map
      START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
      DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // sin(beta-alpha)
  #define CAPABILITY sba
  START_CAPABILITY
    #define FUNCTION sba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // cos(beta-alpha)
  #define CAPABILITY cba
  START_CAPABILITY
    #define FUNCTION cba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // beta-alpha
  #define CAPABILITY ba
  START_CAPABILITY
    #define FUNCTION ba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  // Leading-Order unitarity constraint (soft-cutoff)
  #define CAPABILITY unitarity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_unitarity_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
    #define FUNCTION unitarity_lambdas_LL
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // Next-to-Leading-Order unitarity constraint (soft-cutoff)
  // TODO: Are these mutually exclusive or complementary?
  #define CAPABILITY NLO_unitarity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_NLO_unitarity_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // perturbativity constraint on lambdas (soft-cutoff)
  #define CAPABILITY perturbativity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_perturbativity_likelihood_THDM
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
    #define FUNCTION simple_perturbativity_lambdas_LL
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // perturbativity constraint on yukawas
  #define CAPABILITY perturbativity_yukawas_LL
  START_CAPABILITY
    #define FUNCTION simple_perturbativity_yukawas_LL
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // vacuum stability + meta-stability constraint (soft+hard cutoff)
  #define CAPABILITY stability_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_stability_likelihood_THDM
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
    #define FUNCTION stability_lambdas_LL
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // LIKELIHOOD: guide scanner so that sba ~ 0.99 to 1.00, which is the alignment limit (soft-cutoff)
  // Note: unneccesary since sampling density is actually much higher towards alignment limit
  // TODO: Should it be removed then?
  #define CAPABILITY alignment_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_alignment_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // OBSERVABLE: checks for vacuum meta-stability (T/F)
  // Note: obsolete as it can now be done in the stability constraint
  // TODO: Should it be removed then?
  #define CAPABILITY vacuum_global_minimum
  START_CAPABILITY
    #define FUNCTION check_vacuum_global_minimum
    START_FUNCTION(int)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // checks that the corrections to h0 are perturbative (hard-cutoff)
  #define CAPABILITY h0_loop_order_corrections
  START_CAPABILITY
    #define FUNCTION check_h0_loop_order_corrections
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // checks that the corrections to H0,A0,Hp are perturbative (hard-cutoff)
  #define CAPABILITY THDM_scalar_loop_order_corrections
  START_CAPABILITY
    #define FUNCTION check_THDM_scalar_loop_order_corrections
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // only keeps points that correspond to hidden higgs scenario (hard-cutoff)
  #define CAPABILITY hidden_higgs_scenario_likelihood
  START_CAPABILITY
    #define FUNCTION hidden_higgs_scenario_LL
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // guides scanner towards mh = 125 GeV, used to improve performance of HS (soft-cutoff)
  // TODO: This should be covered by HiggsSignals, so adding this in top may be redundant/wrong?
  #define CAPABILITY higgs_mass_likelihood
  START_CAPABILITY
    #define FUNCTION higgs_mass_LL
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // mass range for each heavy scalar, specified in YAML file (soft-cutoff)
  // TODO: Check what this is
  #define CAPABILITY THDM_scalar_masses
  START_CAPABILITY
    #define FUNCTION check_THDM_scalar_masses
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(THDM_Type, THDM_TYPE)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings
    // THDM Higgs couplings from partial widths only
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
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION

    // THDM Higgs couplings from THDMC
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
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

#endif
