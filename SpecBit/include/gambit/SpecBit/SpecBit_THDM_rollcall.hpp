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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2016 July
///  \date 2020 Apr
///
///  \author James McKay
///           (j.mckay14@imperial.ac.uk)
///  \date 2016 October
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
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

  #define CAPABILITY sba
  START_CAPABILITY
    #define FUNCTION obs_sba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY cba
  START_CAPABILITY
    #define FUNCTION obs_cba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY ba
  START_CAPABILITY
    #define FUNCTION obs_ba
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unitarity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_unitarity_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY NLO_unitarity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_NLO_unitarity_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY perturbativity_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_perturbativity_likelihood_THDM
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)     
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY perturbativity_yukawas_LL
  START_CAPABILITY
    #define FUNCTION simple_perturbativity_yukawas_LL
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY stability_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_stability_likelihood_THDM
    START_FUNCTION(double)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY alignment_likelihood_THDM
  START_CAPABILITY
    #define FUNCTION get_alignment_likelihood_THDM
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
    ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY vacuum_global_minimum
  START_CAPABILITY
    #define FUNCTION check_vacuum_global_minimum
    START_FUNCTION(int)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY h0_loop_order_corrections
  START_CAPABILITY
    #define FUNCTION check_h0_loop_order_corrections
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY THDM_scalar_loop_order_corrections
  START_CAPABILITY
    #define FUNCTION check_THDM_scalar_loop_order_corrections
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY THDM_scalar_masses
  START_CAPABILITY
    #define FUNCTION check_THDM_scalar_masses
    START_FUNCTION(double)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODEL(THDM, THDMatQ)
    BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
    BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
    #undef FUNCTION
  #undef CAPABILITY

  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings
    #define FUNCTION THDM_higgs_couplings_pwid
    START_FUNCTION(HiggsCouplingsTable)
    DEPENDENCY(THDM_spectrum, Spectrum)
    //DEPENDENCY(SMlike_Higgs_PDG_code, int)
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

    #define FUNCTION THDM_higgs_couplings_2HDMC
    START_FUNCTION(HiggsCouplingsTable)
    NEEDS_CLASSES_FROM(THDMC,default)
    DEPENDENCY(THDM_spectrum, Spectrum)
    //DEPENDENCY(SMlike_Higgs_PDG_code, int)
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
