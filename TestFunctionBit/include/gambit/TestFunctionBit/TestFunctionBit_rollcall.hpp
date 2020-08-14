//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module TestFunctionBit.
///
///  Compile-time registration of available
///  observables and likelihoods, as well as their
///  dependencies.
///
///  Add to this if you want to add an observable
///  or likelihood to this module.
///
///  Don't put typedefs or other type definitions
///  in this file; see
///  Elements/include/gambit/Elements/types_rollcall.hpp
///  for further instructions on how to add new
///  types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@qq.com)
///  \date 2020 August
///
///  *********************************************


#ifndef __TestFunctionBit_rollcall_hpp__
#define __TestFunctionBit_rollcall_hpp__

#define MODULE TestFunctionBit
START_MODULE

  #define CAPABILITY gaussian
  START_CAPABILITY
    #define FUNCTION gaussian
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY rosenbrock
  START_CAPABILITY
    #define FUNCTION rosenbrock
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY himmelblau
  START_CAPABILITY
    #define FUNCTION himmelblau
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_2d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY mccormick
  START_CAPABILITY
    #define FUNCTION mccormick
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_2d)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE

#endif  // __TestFunctionBit_rollcall_hpp__
