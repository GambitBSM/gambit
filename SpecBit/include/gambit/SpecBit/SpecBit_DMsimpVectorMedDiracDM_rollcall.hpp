//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for routines declared 
///  in SpecBit_DMsimpVectorMedDiracDM.cpp.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:26PM on June 07, 2022
///
///  \author Chris Chang
///  \date Jun 2022
///                                                
///  ********************************************* 

#ifndef __SpecBit_DMsimpVectorMedDiracDM_hpp__
#define __SpecBit_DMsimpVectorMedDiracDM_hpp__

  // Spectrum object
  #define CAPABILITY DMsimpVectorMedDiracDM_spectrum
  START_CAPABILITY

    // Create simple object from SMInputs & new params.
    #define FUNCTION get_DMsimpVectorMedDiracDM_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, DMsimpVectorMedDiracDM)
    MODEL_GROUP(higgs, (StandardModel_Higgs))
    MODEL_GROUP(DMsimpVectorMedDiracDM_group, (DMsimpVectorMedDiracDM))
    ALLOW_MODEL_COMBINATION(higgs, DMsimpVectorMedDiracDM_group)
    #undef FUNCTION
    
    // Map for Spectrum, for printing.
    #define FUNCTION get_DMsimpVectorMedDiracDM_spectrum_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(DMsimpVectorMedDiracDM_spectrum, Spectrum)
    ALLOW_MODELS(DMsimpVectorMedDiracDM)
    #undef FUNCTION

  #undef CAPABILITY
  
  // Test against a known unitarity bound
  #define CAPABILITY Unitarity_Bound_DMsimpVectorMedDiracDM
    #define FUNCTION Unitarity_Bound_DMsimpVectorMedDiracDM
    START_FUNCTION(double)
    DEPENDENCY(DMsimpVectorMedDiracDM_spectrum, Spectrum)
    ALLOW_MODELS(DMsimpVectorMedDiracDM)
    #undef FUNCTION
  #undef CAPABILITY

#endif
