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
/// \ July 2016
///
///   \author James McKay
///  \ October 2016
///
///
///  *********************************************

#ifndef __SpecBit_THDM_hpp__
#define __SpecBit_THDM_hpp__

#define CAPABILITY THDM_spectrum
START_CAPABILITY
// Create Spectrum object from SMInputs structs, SM Higgs parameters,
// and the THDM parameters
  #define FUNCTION get_THDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)
    ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
   // Convert spectrum into a standard map so that it can be printed
  #define FUNCTION get_THDM_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY test_THDM_spectrum_1
START_CAPABILITY
  #define FUNCTION test_THDM_spectrum_1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY test_THDM_spectrum_2
START_CAPABILITY
  #define FUNCTION test_THDM_spectrum_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY obs_mh0
START_CAPABILITY
  #define FUNCTION obs_mh0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
  #define FUNCTION obs_mh0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY obs_mH0
START_CAPABILITY
  #define FUNCTION obs_mH0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
  #define FUNCTION obs_mH0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY obs_mA0
START_CAPABILITY
  #define FUNCTION obs_mA0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
  #define FUNCTION obs_mA0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY obs_mHpm
START_CAPABILITY
  #define FUNCTION obs_mHpm_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
  #define FUNCTION obs_mHpm_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY


#define CAPABILITY unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY NLO_unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_NLO_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY perturbativity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_perturbativity_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY stability_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_stability_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY alignment_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_alignment_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY oblique_parameters_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_oblique_parameters_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY global_minimum_discriminant_likelihood
START_CAPABILITY
  #define FUNCTION get_global_minimum_discriminant_likelihood
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings
START_CAPABILITY
  #define FUNCTION get_THDM_couplings
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings_for_HiggsBounds
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_for_HiggsBounds
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings_SM_like_model
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_SM_like_model
  START_FUNCTION(std::vector<thdmc_couplings>)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

// Generalised Higgs couplings
#define CAPABILITY Higgs_Couplings
  #define FUNCTION THDM_higgs_couplings_pwid
  START_FUNCTION(HiggsCouplingsTable)
  DEPENDENCY(THDM_spectrum, const Spectrum*)
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
#undef CAPABILITY



#endif
