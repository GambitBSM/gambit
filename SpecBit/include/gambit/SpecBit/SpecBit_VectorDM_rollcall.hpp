//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_VectorDM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///    \date 2016 Aug, 2017 Jun
///
///  *********************************************

#ifndef __SpecBit_VectorDM_hpp__
#define __SpecBit_VectorDM_hpp__

  // Spectrum object for VectorDM model  (tree-level masses)
  #define CAPABILITY VectorDM_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the VectorDM parameters
    #define FUNCTION get_VectorDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, VectorDM)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(vector, (VectorDM))
    ALLOW_MODEL_COMBINATION(higgs, vector)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_VectorDM_spectrum_as_map 
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(VectorDM_spectrum, Spectrum)
    #undef FUNCTION    

  #undef CAPABILITY

#endif

