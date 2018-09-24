//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_SingletDM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Mar
///
///  *********************************************

#ifndef __SpecBit_SingletDM_hpp__
#define __SpecBit_SingletDM_hpp__

  // Spectrum object for SingletDM model  (tree-level masses)
  #define CAPABILITY SingletDM_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the SingletDM parameters
    #define FUNCTION get_SingletDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, SingletDM)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(singlet, (SingletDM))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION

    #if(FS_MODEL_SingletDM_IS_BUILT)    
    #define FUNCTION get_SingletDM_spectrum_pole
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs_running, SingletDM_running)
    MODEL_GROUP(higgs_running,   (StandardModel_Higgs_running))
    MODEL_GROUP(singlet_running, (SingletDM_running))
    ALLOW_MODEL_COMBINATION(higgs_running, singlet_running)
    #undef FUNCTION
    #endif

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_SingletDM_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(SingletDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY SingletDMZ3_spectrum
  START_CAPABILITY

    #if(FS_MODEL_SingletDMZ3_IS_BUILT)    
    #define FUNCTION get_SingletDMZ3_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs_running, SingletDMZ3)
    MODEL_GROUP(higgs,   (StandardModel_Higgs_running))
    MODEL_GROUP(singlet, (SingletDMZ3))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION
    #endif
    // ==============================

    // Convert spectrum into a standard map so that it can be printed
 /*   #define FUNCTION get_SingletDM_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(SingletDMZ3_spectrum, Spectrum)
    #undef FUNCTION*/

  #undef CAPABILITY


  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings

    #define FUNCTION SingletDM_higgs_couplings_pwid
    START_FUNCTION(HiggsCouplingsTable)
    DEPENDENCY(SingletDM_spectrum, Spectrum)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(SingletDM, SingletDMZ3)
    #undef FUNCTION

  #undef CAPABILITY

#endif

