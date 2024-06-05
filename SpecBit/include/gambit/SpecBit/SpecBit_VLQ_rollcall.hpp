//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for routines declared 
///  in SpecBit_VLQ.cpp.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 11:38AM on June 05, 2024
///                                                
///  ********************************************* 

#ifndef __SpecBit_VLQ_hpp__
#define __SpecBit_VLQ_hpp__

  // Spectrum object
  #define CAPABILITY VLQ_spectrum
  START_CAPABILITY

    // Create simple object from SMInputs & new params.
    #define FUNCTION get_VLQ_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, VLQ)
    MODEL_GROUP(higgs, (StandardModel_Higgs))
    MODEL_GROUP(VLQ_group, (VLQ))
    ALLOW_MODEL_COMBINATION(higgs, VLQ_group)
    #undef FUNCTION
    
    // Map for Spectrum, for printing.
    #define FUNCTION get_VLQ_spectrum_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(VLQ_spectrum, Spectrum)
    ALLOW_MODELS(VLQ)
    #undef FUNCTION

  #undef CAPABILITY

#endif
