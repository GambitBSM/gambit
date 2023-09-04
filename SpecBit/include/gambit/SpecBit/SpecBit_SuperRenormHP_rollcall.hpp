//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_SingletDM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Inigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///    \date 2020 March
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#ifndef __SpecBit_SuperRenormHP_hpp__
#define __SpecBit_SuperRenormHP_hpp__

  // Spectrum object for SuperRenormHP model
  #define CAPABILITY SuperRenormHP_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs, SM Higgs parameters,
    // and the SuperRenormHP parameters
    #define FUNCTION get_SuperRenormHP_spectrum
    START_FUNCTION(Spectrum)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, SuperRenormHP)
    MODEL_GROUP(higgs,   (StandardModel_Higgs))
    MODEL_GROUP(singlet, (SuperRenormHP))
    ALLOW_MODEL_COMBINATION(higgs, singlet)
    #undef FUNCTION

    // // Convert spectrum into a standard map so that it can be printed
    // #define FUNCTION get_ScalarSingletDM_Z2_spectrum_as_map
    // START_FUNCTION(map_str_dbl) // Just a string to double map. Can't have commas in macro input
    // DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum)
    // #undef FUNCTION

  #undef CAPABILITY

#endif
*/
