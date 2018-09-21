//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_DiracDM.cpp
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

#ifndef __SpecBit_DiracDM_hpp__
#define __SpecBit_DiracDM_hpp__

  // Spectrum object for DiracDM model  (tree-level masses)
  #define CAPABILITY DiracDM_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the DiracDM parameters
    #define FUNCTION get_DiracDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, DiracDM)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(dirac,   (DiracDM))
    MODEL_GROUP(dirac_sps,   (DiracDM_sps))
    ALLOW_MODEL_COMBINATION(higgs, dirac)
    ALLOW_MODEL_COMBINATION(higgs, dirac_sps)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_DiracDM_spectrum_as_map 
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(DiracDM_spectrum, Spectrum)
    #undef FUNCTION    

  #undef CAPABILITY

#endif

