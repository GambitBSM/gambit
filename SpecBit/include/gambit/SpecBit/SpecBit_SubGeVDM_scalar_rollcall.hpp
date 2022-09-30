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
///  \author Felix Kahlhoefer
///          (kahlhoefer@kit.edu)
///    \date 2022 May
///
///  *********************************************

#ifndef __SpecBit_SubGeVDM_scalar_hpp__
#define __SpecBit_SubGeVDM_scalar_hpp__

  // Spectrum object for SubGeVDM_scalar model 
  #define CAPABILITY SubGeVDM_scalar_spectrum
  START_CAPABILITY

    // Create simple object from SMInputs & new params.
    #define FUNCTION get_SubGeVDM_scalar_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, SubGeVDM_scalar)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(SubGeVDM_scalar_group, (SubGeVDM_scalar))
    ALLOW_MODEL_COMBINATION(higgs, SubGeVDM_scalar_group)
    #undef FUNCTION

    // Convert spectrum into a standard map so that it can be printed
    #define FUNCTION get_SubGeVDM_scalar_spectrum_as_map
    START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    DEPENDENCY(SubGeVDM_scalar_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

#endif

