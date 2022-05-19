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
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   May 2022
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date   2020 Apr
///
///  \author James McKay
///  \date   October 2016
///
///
///  *********************************************

#ifndef __SpecBit_THDM_hpp__
#define __SpecBit_THDM_hpp__

// Create Spectrum object from SMInputs structs, SM Higgs parameters,
// and the THDM parameters
#define CAPABILITY THDM_spectrum
START_CAPABILITY
  #define FUNCTION get_THDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)
    ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

// Convert spectrum into a standard map so that it can be printed
#define CAPABILITY THDM_spectrum_map
START_CAPABILITY
  #define FUNCTION get_THDM_spectrum_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

// Observable: sin(beta-alpha)
#define CAPABILITY sba
START_CAPABILITY
  #define FUNCTION obs_sba
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

// Observable: cos(beta-alpha)
#define CAPABILITY cba
START_CAPABILITY
  #define FUNCTION obs_cba
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

// Observable: beta-alpha
#define CAPABILITY ba
START_CAPABILITY
  #define FUNCTION obs_ba
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

// Observable: Higgs VEV
#define CAPABILITY vev
START_CAPABILITY
  #define FUNCTION obs_vev
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: Leading-Order unitarity constraint (soft-cutoff)
#define CAPABILITY unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: Next-to-Leading-Order unitarity constraint (soft-cutoff)
#define CAPABILITY NLO_unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_NLO_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: perturbativity constraint (soft-cutoff)
#define CAPABILITY perturbativity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_perturbativity_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  ALLOW_MODEL(THDMI_physical, THDMII_physical, THDMLS_physical, THDMflipped_physical)     
  ALLOW_MODEL(THDMI_physicalatQ, THDMII_physicalatQ, THDMLS_physicalatQ, THDMflipped_physicalatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: vacuum stability + meta-stability constraint (soft+hard cutoff)
#define CAPABILITY stability_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_stability_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: guide scanner so that sba ~ 0.99 to 1.00, which is the alignment limit (soft-cutoff)
// Note: unneccesary since sampling density is actually much higher towards alignment limit
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

// OBSERVABLE: checks for vacuum meta-stability (T/F)
// Note: obsolete as it can now be done in the stability constraint
#define CAPABILITY vacuum_global_minimum
START_CAPABILITY
  #define FUNCTION check_vacuum_global_minimum
  START_FUNCTION(int)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: checks that the corrections to h0 are perturbative (hard-cutoff)
#define CAPABILITY h0_loop_order_corrections
START_CAPABILITY
  #define FUNCTION check_h0_loop_order_corrections
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: checks that the corrections to H0,A0,Hp are perturbative (hard-cutoff)
#define CAPABILITY THDM_scalar_loop_order_corrections
START_CAPABILITY
  #define FUNCTION check_THDM_scalar_loop_order_corrections
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: only keeps points that correspond to hidden higgs scenario (hard-cutoff)
#define CAPABILITY hidden_higgs_scenario_likelihood
START_CAPABILITY
  #define FUNCTION hidden_higgs_scenario_LL
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: guides scanner towards mh = 125 GeV, used to improve performance of HS (soft-cutoff)
#define CAPABILITY higgs_mass_likelihood
START_CAPABILITY
  #define FUNCTION higgs_mass_LL
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// LIKELIHOOD: mass range for each heavy scalar, specified in YAML file (soft-cutoff)
#define CAPABILITY THDM_scalar_masses
START_CAPABILITY
  #define FUNCTION check_THDM_scalar_masses
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY

// THDM Higgs couplings from partial widths only
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
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION

  // THDM Higgs couplings from THDMC
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
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  BACKEND_REQ(init_THDM_spectrum_container_CONV, (libTHDMC), void ,(THDM_spectrum_container&, const Spectrum&, int, double, int))
  BACKEND_OPTION( (THDMC, 1.8.0), (THDMC) )
  #undef FUNCTION
#undef CAPABILITY



#endif
