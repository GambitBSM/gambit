//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_VectorSingletDM.cpp
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

#ifndef __SpecBit_VectorSingletDM_Z2_hpp__
#define __SpecBit_VectorSingletDM_Z2_hpp__

  // Spectrum object for VectorSingletDM_Z2 model  (tree-level masses)
  #define CAPABILITY VectorSingletDM_Z2_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the VectorSingletDM_Z2 parameters
    #define FUNCTION get_VectorSingletDM_Z2_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, VectorSingletDM_Z2)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(vector, (VectorSingletDM_Z2))
    ALLOW_MODEL_COMBINATION(higgs, vector)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_VectorSingletDM_Z2_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(VectorSingletDM_Z2_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

#endif

