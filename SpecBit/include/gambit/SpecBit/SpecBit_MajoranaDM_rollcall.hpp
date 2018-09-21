//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_MajoranaDM.cpp
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

#ifndef __SpecBit_MajoranaDM_hpp__
#define __SpecBit_MajoranaDM_hpp__

  // Spectrum object for MajoranaDM model  (tree-level masses)
  #define CAPABILITY MajoranaDM_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the MajoranaDM parameters
    #define FUNCTION get_MajoranaDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, MajoranaDM)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(majorana, (MajoranaDM))
    MODEL_GROUP(majorana_sps,   (MajoranaDM_sps))
    ALLOW_MODEL_COMBINATION(higgs, majorana)
    ALLOW_MODEL_COMBINATION(higgs, majorana_sps)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_MajoranaDM_spectrum_as_map 
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(MajoranaDM_spectrum, Spectrum)
    #undef FUNCTION    

  #undef CAPABILITY

#endif

