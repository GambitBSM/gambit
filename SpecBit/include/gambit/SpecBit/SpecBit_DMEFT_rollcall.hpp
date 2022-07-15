//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for routines declared 
///  in SpecBit_DMEFT.cpp.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///                                                
///  ********************************************* 

#ifndef __SpecBit_DMEFT_hpp__
#define __SpecBit_DMEFT_hpp__

  // Spectrum object
  #define CAPABILITY DMEFT_spectrum
  START_CAPABILITY

    // Create simple object from SMInputs & new params.
    #define FUNCTION get_DMEFT_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, DMEFT)
    MODEL_GROUP(higgs, (StandardModel_Higgs))
    MODEL_GROUP(DMEFT_group, (DMEFT))
    ALLOW_MODEL_COMBINATION(higgs, DMEFT_group)
    #undef FUNCTION

    // Map for Spectrum, for printing.
    #define FUNCTION get_DMEFT_spectrum_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(DMEFT_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

#endif
