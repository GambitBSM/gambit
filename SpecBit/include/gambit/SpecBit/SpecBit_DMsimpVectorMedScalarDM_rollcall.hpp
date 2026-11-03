//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for routines declared 
///  in SpecBit_DMsimpVectorMedScalarDM.cpp.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:28PM on June 07, 2022
///                                                
///  ********************************************* 

#ifndef __SpecBit_DMsimpVectorMedScalarDM_hpp__
#define __SpecBit_DMsimpVectorMedScalarDM_hpp__

  // Spectrum object
  #define CAPABILITY DMsimpVectorMedScalarDM_spectrum
  START_CAPABILITY

    // Create simple object from SMInputs & new params.
    #define FUNCTION get_DMsimpVectorMedScalarDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, DMsimpVectorMedScalarDM)
    MODEL_GROUP(higgs, (StandardModel_Higgs))
    MODEL_GROUP(DMsimpVectorMedScalarDM_group, (DMsimpVectorMedScalarDM))
    ALLOW_MODEL_COMBINATION(higgs, DMsimpVectorMedScalarDM_group)
    #undef FUNCTION
    
    // Map for Spectrum, for printing.
    #define FUNCTION get_DMsimpVectorMedScalarDM_spectrum_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(DMsimpVectorMedScalarDM_spectrum, Spectrum)
    ALLOW_MODELS(DMsimpVectorMedScalarDM)
    #undef FUNCTION

  #undef CAPABILITY

#endif
