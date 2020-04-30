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

#define CAPABILITY THDM_spectrum
START_CAPABILITY
// Create Spectrum object from SMInputs structs, SM Higgs parameters,
// and the THDM parameters
  #define FUNCTION get_THDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(THDM,THDMatQ)
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

// TODO: Remove all the commented capabilities below
// they can be extracted from the spectrum
/*
#define CAPABILITY mh0_pole
START_CAPABILITY
  #define FUNCTION obs_mh0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mh0_running
START_CAPABILITY
  #define FUNCTION obs_mh0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mH0_pole
START_CAPABILITY
  #define FUNCTION obs_mH0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mH0_running
START_CAPABILITY
  #define FUNCTION obs_mH0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mA0_pole
START_CAPABILITY
  #define FUNCTION obs_mA0_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mA0_running
START_CAPABILITY
  #define FUNCTION obs_mA0_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mHpm_pole
START_CAPABILITY
  #define FUNCTION obs_mHpm_pole
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mHpm_running
START_CAPABILITY
  #define FUNCTION obs_mHpm_running
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY tanb
START_CAPABILITY
  #define FUNCTION obs_tanb
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY alpha
START_CAPABILITY
  #define FUNCTION obs_alpha
  START_FUNCTION(double)
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


#define CAPABILITY lambda_1
START_CAPABILITY
  #define FUNCTION obs_lambda_1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_2
START_CAPABILITY
  #define FUNCTION obs_lambda_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_3
START_CAPABILITY
  #define FUNCTION obs_lambda_3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_4
START_CAPABILITY
  #define FUNCTION obs_lambda_4
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_5
START_CAPABILITY
  #define FUNCTION obs_lambda_5
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_6
START_CAPABILITY
  #define FUNCTION obs_lambda_6
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda_7
START_CAPABILITY
  #define FUNCTION obs_lambda_7
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY m12_2
START_CAPABILITY
  #define FUNCTION obs_m12_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY m11_2
START_CAPABILITY
  #define FUNCTION obs_m11_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY m22_2
START_CAPABILITY
  #define FUNCTION obs_m22_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_1
START_CAPABILITY
  #define FUNCTION obs_Lambda_1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_2
START_CAPABILITY
  #define FUNCTION obs_Lambda_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_3
START_CAPABILITY
  #define FUNCTION obs_Lambda_3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_4
START_CAPABILITY
  #define FUNCTION obs_Lambda_4
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_5
START_CAPABILITY
  #define FUNCTION obs_Lambda_5
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_6
START_CAPABILITY
  #define FUNCTION obs_Lambda_6
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Lambda_7
START_CAPABILITY
  #define FUNCTION obs_Lambda_7
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY M12_2
START_CAPABILITY
  #define FUNCTION obs_M12_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY M11_2
START_CAPABILITY
  #define FUNCTION obs_M11_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY M22_2
START_CAPABILITY
  #define FUNCTION obs_M22_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yu1
START_CAPABILITY
  #define FUNCTION obs_Yu1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yu2
START_CAPABILITY
  #define FUNCTION obs_Yu2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yu3
START_CAPABILITY
  #define FUNCTION obs_Yu3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yd1
START_CAPABILITY
  #define FUNCTION obs_Yd1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yd2
START_CAPABILITY
  #define FUNCTION obs_Yd2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Yd3
START_CAPABILITY
  #define FUNCTION obs_Yd3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Ye1
START_CAPABILITY
  #define FUNCTION obs_Ye1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Ye2
START_CAPABILITY
  #define FUNCTION obs_Ye2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Ye3
START_CAPABILITY
  #define FUNCTION obs_Ye3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY g1
START_CAPABILITY
  #define FUNCTION obs_g1
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY g2
START_CAPABILITY
  #define FUNCTION obs_g2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY g3
START_CAPABILITY
  #define FUNCTION obs_g3
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY vev
START_CAPABILITY
  #define FUNCTION obs_vev
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY
*/
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
  // physical models are checked in this likelihood so must be allowed
  ALLOW_MODEL(THDMI_physical, THDMII_physical, THDMLS_physical, THDMflipped_physical)     
  ALLOW_MODEL(THDMI_physicalatQ, THDMII_physicalatQ, THDMLS_physicalatQ, THDMflipped_physicalatQ)
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

#define CAPABILITY vacuum_global_minimum
START_CAPABILITY
  #define FUNCTION check_vacuum_global_minimum
  START_FUNCTION(int)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY h0_loop_order_corrections
START_CAPABILITY
  #define FUNCTION check_h0_loop_order_corrections
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_scalar_loop_order_corrections
START_CAPABILITY
  #define FUNCTION check_THDM_scalar_loop_order_corrections
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
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

#define CAPABILITY THDM_couplings_HB
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_HB
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings_HB_SM_like_model
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_HB_SM_like_model
  START_FUNCTION(std::vector<thdmc_couplings>)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings_HB_effc
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_HB_effc
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODEL(THDM, THDMI, THDMII, THDMLS, THDMflipped)     
  ALLOW_MODEL(THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_couplings_HB_effc_SM_like_model
START_CAPABILITY
  #define FUNCTION get_THDM_couplings_HB_effc_SM_like_model
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
