//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall declarations for module functions
///  contained in SpecBit_SM.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Nov
///
///  *********************************************

#ifndef __SpecBit_SM_hpp__
#define __SpecBit_SM_hpp__

  /// Produce an SMInputs object (SLHA2 conventions)
  // i.e. provide Standard Model parameters in SLHA2 input conventions
  #define CAPABILITY SMINPUTS
  START_CAPABILITY

    #define FUNCTION get_SMINPUTS
    START_FUNCTION(SMInputs)
    ALLOW_MODELS(StandardModel_SLHA2)
    #undef FUNCTION

  #undef CAPABILITY

  // Spectrum object for Standard Model information
  // This contains more info than SMInputs including pole masses
  // for the bottom quark and the Higgs mass in the SM
  #define CAPABILITY SM_spectrum
  START_CAPABILITY

    // Create Spectrum object from SMInputs structs and SM Higgs parameters,
    #define FUNCTION get_SM_spectrum
    START_FUNCTION(Spectrum)
    ALLOW_MODELS(StandardModel_Higgs)
    DEPENDENCY(SMINPUTS, SMInputs)
    #undef FUNCTION

  #undef CAPABILITY

  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings

    #define FUNCTION SM_higgs_couplings
    START_FUNCTION(HiggsCouplingsTable)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    #undef FUNCTION

  #undef CAPABILITY

#endif

