//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Testing parts of rollcall header for module
///  SpecBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  *********************************************

#ifndef __SpecBit_sandbox_hpp__
#define __SpecBit_sandbox_hpp__

  #ifndef MODULE
    #define MODULE SpecBit
  #endif

 // For testing only
  #define CAPABILITY test_MSSM_spectrum
  START_CAPABILITY

    #define FUNCTION make_test_spectrum  // Get (pointer to) test MSSM spectrum
    START_FUNCTION(SubSpectrum*)
    #undef FUNCTION

  #undef CAPABILITY

  /// TEST FUNCTIONS
  // Just some functions for testing SpecBit and Spectrum object components

  #define CAPABILITY specbit_tests1
  START_CAPABILITY
     #define FUNCTION specbit_test_func1
     START_FUNCTION(double)
     DEPENDENCY(MSSM_spectrum, Spectrum)
     #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY specbit_tests2
  START_CAPABILITY
     #define FUNCTION specbit_test_func2
     START_FUNCTION(double)
     #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY specbit_tests3
  START_CAPABILITY
     #define FUNCTION specbit_test_func3
     START_FUNCTION(double)
     DEPENDENCY(SM_subspectrum, const SubSpectrum*)
     #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY specbit_test_Spectrum
  START_CAPABILITY
     #define FUNCTION specbit_test_Spectrum
     START_FUNCTION(double)
     DEPENDENCY(MSSM_spectrum, Spectrum)
     DEPENDENCY(SM_subspectrum, const SubSpectrum*)
   #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY specbit_test_show_SMInputs
  START_CAPABILITY
     #define FUNCTION specbit_test_show_SMInputs
     START_FUNCTION(double)
     DEPENDENCY(SMINPUTS, SMInputs)
   #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY SpecBit_examples
  START_CAPABILITY

      #define FUNCTION exampleRead
      START_FUNCTION(bool)
      DEPENDENCY(MSSM_spectrum, Spectrum)
      #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY test_Singlet_spectrum
  START_CAPABILITY

      #define FUNCTION test_Singlet_spectrum
      START_FUNCTION(bool)
      MODEL_GROUP(sm,      (StandardModel_SLHA2))
      MODEL_GROUP(higgs,   (StandardModel_Higgs))
      MODEL_GROUP(singlet, (SingletDM))
      ALLOW_MODEL_COMBINATION(sm, higgs, singlet)
      DEPENDENCY(SingletDM_spectrum, Spectrum)
      #undef FUNCTION

  #undef CAPABILITY

#endif /* defined(__SpecBit_sandbox_hpp__) */



