//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_DiracSingletDM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///    \date 2016 Aug, Nov
///    \date 2017 Jun
///
///  *********************************************

#ifndef __SpecBit_DiracSingletDM_Z2_hpp__
#define __SpecBit_DiracSingletDM_Z2_hpp__

  // Spectrum object for DiracSingletDM_Z2 model  (tree-level masses)
  #define CAPABILITY DiracSingletDM_Z2_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the DiracSingletDM_Z2 parameters
    #define FUNCTION get_DiracSingletDM_Z2_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, DiracSingletDM_Z2)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(dirac,   (DiracSingletDM_Z2))
    MODEL_GROUP(dirac_sps,   (DiracSingletDM_Z2_sps))
    ALLOW_MODEL_COMBINATION(higgs, dirac)
    ALLOW_MODEL_COMBINATION(higgs, dirac_sps)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_DiracSingletDM_Z2_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(DiracSingletDM_Z2_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

#endif

