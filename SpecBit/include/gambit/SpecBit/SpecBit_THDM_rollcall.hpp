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

// ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, THDM)
// MODEL_GROUP(higgs,   (StandardModel_Higgs))
// MODEL_GROUP(thdm, (THDM))
// ALLOW_MODEL_COMBINATION(higgs, thdm)

  // Spectrum object for SingletDM model  (tree-level masses)
#define CAPABILITY THDM_spectrum
START_CAPABILITY
// Create Spectrum object from SMInputs structs, SM Higgs parameters,
// and the THDM parameters
  #define FUNCTION get_THDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(THDM, THDMatQ)
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
  ALLOW_MODEL(THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY test_THDM_spectrum_2
START_CAPABILITY
  #define FUNCTION test_THDM_spectrum_2
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda1_coupling_basis
START_CAPABILITY
  #define FUNCTION print_lambda1_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda2_coupling_basis
START_CAPABILITY
  #define FUNCTION print_lambda2_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda3_coupling_basis
START_CAPABILITY
  #define FUNCTION print_lambda3_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda4_coupling_basis
START_CAPABILITY
  #define FUNCTION print_lambda4_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lambda5_coupling_basis
START_CAPABILITY
  #define FUNCTION print_lambda5_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY tanb_coupling_basis
START_CAPABILITY
  #define FUNCTION print_tanb_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY m12_2_coupling_basis
START_CAPABILITY
  #define FUNCTION print_m12_2_coupling_basis
  START_FUNCTION(double)
  DEPENDENCY(Coupling_Basis, thdm_coupling_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mh0_physical_basis
START_CAPABILITY
  #define FUNCTION print_mh0_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mH0_physical_basis
START_CAPABILITY
  #define FUNCTION print_mH0_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mHp_physical_basis
START_CAPABILITY
  #define FUNCTION print_mHp_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY mA_physical_basis
START_CAPABILITY
  #define FUNCTION print_mA_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY tanb_physical_basis
START_CAPABILITY
  #define FUNCTION print_tanb_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY sba_physical_basis
START_CAPABILITY
  #define FUNCTION print_sba_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY m12_2_physical_basis
START_CAPABILITY
  #define FUNCTION print_m12_2_phys_basis
  START_FUNCTION(double)
  DEPENDENCY(Physical_Basis, thdm_physical_basis)
  #undef FUNCTION
#undef CAPABILITY


#define CAPABILITY unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY


#define CAPABILITY NLO_unitarity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_NLO_unitarity_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY perturbativity_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_perturbativity_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM, THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY stability_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_stability_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM, THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY alignment_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_alignment_likelihood_THDM
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY oblique_parameters_likelihood_THDM
START_CAPABILITY
  #define FUNCTION get_oblique_parameters_likelihood_THDM
  START_FUNCTION(double)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY global_minimum_discriminant_likelihood
START_CAPABILITY
  #define FUNCTION get_global_minimum_discriminant_likelihood
  START_FUNCTION(double)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_Higgs_Couplings
START_CAPABILITY
  #define FUNCTION THDM_Couplings
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_Higgs_Couplings_For_HB
START_CAPABILITY
  #define FUNCTION THDM_Couplings_For_HB
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_Higgs_Couplings_SM_Like_Model_h01
START_CAPABILITY
  #define FUNCTION THDM_Couplings_SM_Like_Model_h01
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_Higgs_Couplings_SM_Like_Model_h02
START_CAPABILITY
  #define FUNCTION THDM_Couplings_SM_Like_Model_h02
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY THDM_Higgs_Couplings_SM_Like_Model_A0
START_CAPABILITY
  #define FUNCTION THDM_Couplings_SM_Like_Model_A0
  START_FUNCTION(thdmc_couplings)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY SLHA_THDM
START_CAPABILITY
  #define FUNCTION fill_THDM_SLHA
  START_FUNCTION(SLHAstruct)
  NEEDS_CLASSES_FROM(THDMC,default)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Coupling_Basis
START_CAPABILITY
  #define FUNCTION fill_THDM_coupling_basis
  START_FUNCTION(thdm_coupling_basis)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM, THDMatQ)
  #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY Physical_Basis
START_CAPABILITY
  #define FUNCTION fill_THDM_phys_basis
  START_FUNCTION(thdm_physical_basis)
  DEPENDENCY(THDM_spectrum, Spectrum)
  ALLOW_MODELS(THDM, THDMatQ)
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
  ALLOW_MODELS(THDM,THDMatQ)
  #undef FUNCTION
#undef CAPABILITY



#endif
