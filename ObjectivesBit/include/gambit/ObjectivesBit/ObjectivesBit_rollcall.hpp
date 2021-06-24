//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module ObjectivesBit.
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


#ifndef __ObjectivesBit_rollcall_hpp__
#define __ObjectivesBit_rollcall_hpp__

#define MODULE ObjectivesBit
START_MODULE

  #define CAPABILITY gaussian
  START_CAPABILITY
    #define FUNCTION gaussian
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
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
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
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

  #define CAPABILITY ackley
  START_CAPABILITY
    #define FUNCTION ackley
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY eggbox
  START_CAPABILITY
    #define FUNCTION eggbox
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY rastrigin
  START_CAPABILITY
    #define FUNCTION rastrigin
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY beale
  START_CAPABILITY
    #define FUNCTION beale
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_2d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY shells
  START_CAPABILITY
    #define FUNCTION shells
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY styblinski_tang
  START_CAPABILITY
    #define FUNCTION styblinski_tang
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY easom
  START_CAPABILITY
    #define FUNCTION easom
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_2d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY tf1
  START_CAPABILITY
    #define FUNCTION tf1
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY tf2
  START_CAPABILITY
    #define FUNCTION tf2
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY tf3
  START_CAPABILITY
    #define FUNCTION tf3
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY tf4
  START_CAPABILITY
    #define FUNCTION tf4
    START_FUNCTION(double)
    ALLOW_MODELS(trivial_1d,
                 trivial_2d,
                 trivial_3d,
                 trivial_4d,
                 trivial_5d,
                 trivial_7d,
                 trivial_10d)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE

#endif  // __ObjectivesBit_rollcall_hpp__
