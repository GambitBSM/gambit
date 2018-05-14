//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for creating Mathematica functions and
///  sending and receiving packets through WSTP
///
///  *********************************************
///
///  Authos (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Oct
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************

#ifndef __MATHEMATICA_MACROS_HPP__
#define __MATHEMATICA_MACROS_HPP__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Backends/mathematica_function.hpp"
#include "gambit/Backends/mathematica_variable.hpp"

/// Backend function macro for mathematica
#define BE_FUNCTION_I_MATH(NAME, TYPE, ARGLIST, SYMBOLNAME, CAPABILITY, MODELS)               \
namespace Gambit                                                                              \
{                                                                                             \
  namespace Backends                                                                          \
  {                                                                                           \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                               \
    {                                                                                         \
                                                                                              \
      /* Define a mathematica_function object to hold all the nasty conversion internals. */  \
      mathematica_function<TYPE INSERT_NONEMPTY(STRIP_VARIADIC_ARG(ARGLIST)) >                \
       NAME##_function(STRINGIFY(BACKENDNAME), STRINGIFY(VERSION), SYMBOLNAME);               \
                                                                                              \
      /* Define a regular function wrapper to call the mathematica_function object. */        \
      TYPE NAME##_function_wrapper FUNCTION_ARGS(ARGLIST)                                     \
      {                                                                                       \
        return NAME##_function FUNCTION_ARG_NAMES(ARGLIST);                                   \
      }                                                                                       \
                                                                                             \
      /* Define a type NAME_type to be a suitable function pointer. */                        \
      typedef TYPE (*NAME##_type) CONVERT_VARIADIC_ARG(ARGLIST);                              \
                                                                                              \
      extern const NAME##_type NAME = NAME##_function_wrapper;                                \
    }                                                                                         \
  }                                                                                           \
}

/// Backend variable macro for Mathematica
#define BE_VARIABLE_I_MATH(NAME, TYPE, SYMBOLNAME, CAPABILITY, MODELS)                        \
namespace Gambit                                                                              \
{                                                                                             \
  namespace Backends                                                                          \
  {                                                                                           \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                               \
    {                                                                                         \
      extern mathematica_variable<TYPE>* const NAME =                                         \
        new mathematica_variable<TYPE>(STRINGIFY(BACKENDNAME),STRINGIFY(VERSION),SYMBOLNAME); \
      mathematica_variable<TYPE>* CAT(getptr,NAME)() { return NAME; }                         \
    }                                                                                         \
  }                                                                                           \
}

#endif // __MATHEMATICA_MACROS_HPP__
