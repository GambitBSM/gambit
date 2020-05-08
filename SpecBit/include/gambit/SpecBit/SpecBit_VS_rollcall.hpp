//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_VS.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date Nov 2015
///
///  \author Jos Eliel Camargo-Molina
///          (elielcamargomolina@gmail.com)
///  \date Jun 2018++
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date Sep 2019
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 July, Dec
///
///  *********************************************

#ifndef __SpecBit_VS_rollcall_hpp__
#define __SpecBit_VS_rollcall_hpp__

#include "gambit/SpecBit/SpecBit_types.hpp"

  #define CAPABILITY lnL_EW_vacuum
  START_CAPABILITY

    #define FUNCTION check_EW_stability_ScalarSingletDM_Z3
    START_FUNCTION(double)
    DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum)
    ALLOW_MODEL_DEPENDENCE(ScalarSingletDM_Z3)
    MODEL_GROUP(higgs,   (StandardModel_Higgs_running))
    MODEL_GROUP(singlet, (ScalarSingletDM_Z3_running))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY lnL_high_scale_vacuum
  START_CAPABILITY

    #define FUNCTION lnL_highscale_vacuum_decay_single_field
    START_FUNCTION(double)
    DEPENDENCY(high_scale_vacuum_info, dbl_dbl_bool)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY high_scale_vacuum_info
  START_CAPABILITY

    #define FUNCTION find_min_lambda_ScalarSingletDM_Z2
    START_FUNCTION(dbl_dbl_bool)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs_running, ScalarSingletDM_Z2_running)
    MODEL_GROUP(higgs,   (StandardModel_Higgs_running))
    MODEL_GROUP(singlet, (ScalarSingletDM_Z2_running))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION

    #define FUNCTION find_min_lambda_ScalarSingletDM_Z3
    START_FUNCTION(dbl_dbl_bool)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs_running, ScalarSingletDM_Z3_running)
    MODEL_GROUP(higgs,   (StandardModel_Higgs_running))
    MODEL_GROUP(singlet, (ScalarSingletDM_Z3_running))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION

    #define FUNCTION find_min_lambda_MDM
    START_FUNCTION(dbl_dbl_bool)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(MDM_spectrum, Spectrum)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs_running, MDM)
    MODEL_GROUP(higgs,   (StandardModel_Higgs_running))
    MODEL_GROUP(mdm, (MDM))
    ALLOW_MODEL_COMBINATION(higgs, mdm)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY expected_vacuum_lifetime
    START_CAPABILITY
    #define FUNCTION get_expected_vacuum_lifetime
    START_FUNCTION(double)
    DEPENDENCY(high_scale_vacuum_info, dbl_dbl_bool)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY check_perturbativity_to_lambda_min
    START_CAPABILITY
    #define FUNCTION check_perturb_min_lambda
    START_FUNCTION(double)
    DEPENDENCY(high_scale_vacuum_info, dbl_dbl_bool)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lambdaB
    START_CAPABILITY
    #define FUNCTION get_lambdaB
    START_FUNCTION(double)
    DEPENDENCY(high_scale_vacuum_info, dbl_dbl_bool)
    #undef FUNCTION
  #undef CAPABILITY

  /******************************************/
  /* Vacuum stability likelihoods & results */
  /******************************************/

  /// Tunnelling likelihood using global minimum as panic vacuum
  #define CAPABILITY VS_likelihood_global
  START_CAPABILITY
    #define FUNCTION get_likelihood_VS_global
      START_FUNCTION(double)
      DEPENDENCY(check_vacuum_stability_global, SpecBit::VevaciousResultContainer)
    #undef FUNCTION
  #undef CAPABILITY

  /// Tunnelling likelihood using nearest minimum as panic vacuum
  #define CAPABILITY VS_likelihood_nearest
  START_CAPABILITY
    #define FUNCTION get_likelihood_VS_nearest
      START_FUNCTION(double)
      DEPENDENCY(check_vacuum_stability_nearest, SpecBit::VevaciousResultContainer)
    #undef FUNCTION
  #undef CAPABILITY
  
  /// Get all vevacious results from a global run as str to dbl map to print them
  #define CAPABILITY VS_results_global
  START_CAPABILITY
    #define FUNCTION get_VS_results_global
      START_FUNCTION(map_str_dbl)
      DEPENDENCY(check_vacuum_stability_global, SpecBit::VevaciousResultContainer)
    #undef FUNCTION
  #undef CAPABILITY
    
  /// Get all vevacious results from a nearest run as str to dbl map to print them
  #define CAPABILITY VS_results_nearest
  START_CAPABILITY
    #define FUNCTION get_VS_results_nearest
      START_FUNCTION(map_str_dbl)
      DEPENDENCY(check_vacuum_stability_nearest, SpecBit::VevaciousResultContainer)
    #undef FUNCTION
  #undef CAPABILITY
  
  /**********************/
  /* VEVACIOUS ROUTINES */
  /**********************/

  /// Model dependent -- just tells vevacious the name and locations of the ini files
  /// for each model, since they might not be just <MODELNAME>.vin, etc.
  #define CAPABILITY vevacious_file_location
  START_CAPABILITY
    #define FUNCTION vevacious_file_location_MSSM
    START_FUNCTION(map_str_str)
    #undef FUNCTION
  #undef CAPABILITY

  // Initialize vevacious with a set of YAML runOptions.
  #define CAPABILITY init_vevacious
  START_CAPABILITY
    #define FUNCTION initialize_vevacious
    START_FUNCTION(std::string)
    DEPENDENCY(vevacious_file_location, map_str_str)
    #undef FUNCTION
  #undef CAPABILITY
   
  /// Function for computing the stability of the scalar potential w.r.t. global minimum. Model independent. 
  /// Just works with a filled instance of SpectrumEntriesForVevacious for the respective Model.
  /// calls two non-rollcalled helper functions: helper_run_vevacious & helper_catch_vevacious
  #define CAPABILITY check_vacuum_stability_global
  START_CAPABILITY
    #define FUNCTION check_vacuum_stability_vevacious_global
    START_FUNCTION(SpecBit::VevaciousResultContainer)
    // should eventually get the number of implemented pathFinders in vevacious in a non-hard coded way # todo
    //BACKEND_REQ(get_pathFinder_number,(vevtag), int, ())
    DEPENDENCY(pass_spectrum_to_vevacious, SpecBit::SpectrumEntriesForVevacious)
    DEPENDENCY(init_vevacious, std::string)
    NEEDS_CLASSES_FROM(vevacious, default)
  #undef FUNCTION
  #undef CAPABILITY
  
  /// Function for computing the stability of the scalar potential w.r.t to nearest minimum. Model independent. 
  /// Just works with a filled instance of SpectrumEntriesForVevacious for the respective Model.
  /// calls two non-rollcalled helper functions: helper_run_vevacious & helper_catch_vevacious
  #define CAPABILITY check_vacuum_stability_nearest
  START_CAPABILITY
    #define FUNCTION check_vacuum_stability_vevacious_nearest
    START_FUNCTION(SpecBit::VevaciousResultContainer)
    // should eventually get the number of implemented pathFinders in vevacious in a non-hard coded way # todo
    //BACKEND_REQ(get_pathFinder_number,(vevtag), int, ())
    DEPENDENCY(pass_spectrum_to_vevacious, SpecBit::SpectrumEntriesForVevacious)
    DEPENDENCY(init_vevacious, std::string)
    NEEDS_CLASSES_FROM(vevacious, default)
  #undef FUNCTION
  #undef CAPABILITY

  /// Function to create an object of type SpectrumEntriesForVevacious, holding all spectrum entries
  /// that have to be passed to vevacious (via SLHAea). Model dependent.
  /// Note that the actual execution of the passing is done in a non-rollcalled helper function 
  /// (exec_pass_spectrum_to_vevacious) to allow for several vevacious runs per parameter point. 
  #define CAPABILITY pass_spectrum_to_vevacious
  START_CAPABILITY

  #define FUNCTION prepare_pass_MSSM_spectrum_to_vevacious
    START_FUNCTION(SpecBit::SpectrumEntriesForVevacious)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    DEPENDENCY(init_vevacious, std::string)
    // (JR) I don't know which models should or should not be allowed here, best to check with Eliel # todo
    ALLOW_MODELS(MSSM, CMSSM, NUHM2) 
  #undef FUNCTION
  #undef CAPABILITY

#endif

