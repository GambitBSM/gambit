//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for creating Python backend functions
///  and variables.
///
///  *********************************************
///
///  Authos (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************

#ifndef __python_macros_hpp__
#define __python_macros_hpp__

#include "gambit/cmake/cmake_variables.hpp"

#ifndef HAVE_PYBIND11

  // Just use the dummy functions if pybind11 is missing
  #define BE_FUNCTION_I_PY BE_FUNCTION_I_DUMMY
  #define BE_VARIABLE_I_PY BE_VARIABLE_I_DUMMY

#else

  #include "gambit/Utils/util_macros.hpp"
  #include "gambit/Backends/python_function.hpp"
  #include "gambit/Backends/python_variable.hpp"

  /// Backend function macro for Python backends
  #define BE_FUNCTION_I_PY(NAME, TYPE, ARGLIST, SYMBOLNAME, CAPABILITY, MODELS)                 \
  namespace Gambit                                                                              \
  {                                                                                             \
    namespace Backends                                                                          \
    {                                                                                           \
      namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                               \
      {                                                                                         \
        /* Define a python_function object to hold all the nasty conversion internals. */       \
        python_function<TYPE INSERT_NONEMPTY(STRIP_VARIADIC_ARG(ARGLIST)) >                     \
         NAME##_function(STRINGIFY(BACKENDNAME), STRINGIFY(VERSION), SYMBOLNAME);               \
                                                                                                \
        /* Define a regular function wrapper to call the python_function object. */             \
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

  /// Backend variable macro for Python
  #define BE_VARIABLE_I_PY(NAME, TYPE, SYMBOLNAME, CAPABILITY, MODELS)                          \
  namespace Gambit                                                                              \
  {                                                                                             \
    namespace Backends                                                                          \
    {                                                                                           \
      namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                               \
      {                                                                                         \
        extern python_variable<TYPE>* const NAME =                                              \
          new python_variable<TYPE>(STRINGIFY(BACKENDNAME),STRINGIFY(VERSION),SYMBOLNAME);      \
        python_variable<TYPE>* CAT(getptr,NAME)() { return NAME; }                              \
      }                                                                                         \
    }                                                                                           \
  }

#endif // HAVE_PYBIND11

#endif // #defined __python_macros_hpp
