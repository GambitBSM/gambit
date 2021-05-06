//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Module function declarations for SpecBit_tests.cpp (new tests)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Aug
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Mar, June, Sept
///
///  *********************************************

#ifndef __SpecBit_tests_hpp__
#define __SpecBit_tests_hpp__

  #ifndef MODULE
    #define MODULE SpecBit
  #endif

   /// @{ Functions to test Spectrum objects

   #define CAPABILITY MathematicaTest
   START_CAPABILITY

     #define FUNCTION Math_test
     START_FUNCTION(bool)
     BACKEND_REQ(MathTest, (), double, (const int&,const int&))
     #undef FUNCTION

     #define FUNCTION SUSYHD_test
     START_FUNCTION(bool)
     DEPENDENCY(prec_mh, triplet<double>)
     #undef FUNCTION

   #undef CAPABILITY

   #define CAPABILITY run_MSSMspectrum_test
   START_CAPABILITY

     #define FUNCTION MSSMspectrum_test
     START_FUNCTION(bool)
     DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
     #undef FUNCTION

     #define FUNCTION SPheno_MSSM_test
     START_FUNCTION(bool)
     DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
     #undef FUNCTION

   #undef CAPABILITY

   #define CAPABILITY run_light_quark_test
   START_CAPABILITY

     #define FUNCTION light_quark_test
     START_FUNCTION(bool)
     DEPENDENCY(qedqcd_subspectrum, const SubSpectrum*)
     #undef FUNCTION

   #undef CAPABILITY

   /// @}

#endif
