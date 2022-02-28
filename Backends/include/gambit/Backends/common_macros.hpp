//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for backend registration that are used
///  from both frontend headers and source files.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2015 May
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************

#ifndef __COMMON_MACROS_HPP__
#define __COMMON_MACROS_HPP__

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Elements/types_rollcall.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

/// Turn classloading off by default (this is redefined by BOSSed backends).
#define DO_CLASSLOADING 0

/// Macro for assigning allowed models to an entire backend.
#define BE_ALLOW_MODELS(...) BOOST_PP_SEQ_FOR_EACH(BE_ALLOW_MODEL_INTERMEDIATE, , BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))

/// Intermediate macro for expanding BE_ALLOW_MODELS.
#define BE_ALLOW_MODEL_INTERMEDIATE(r,data,MODEL) BE_ALLOW_MODEL(MODEL)

/// Boilerplate code for point-level backend initialisation function definitions
#define BE_INI_FUNCTION                                                     \
namespace Gambit                                                            \
{                                                                           \
  namespace BackendIniBit                                                   \
  {                                                                         \
    namespace Pipes                                                         \
    {                                                                       \
      namespace CAT_4(BACKENDNAME,_,SAFE_VERSION,_init)                     \
      {                                                                     \
        const str backendDir = Backends::backendInfo().                     \
         path_dir(STRINGIFY(BACKENDNAME), STRINGIFY(VERSION));              \
      }                                                                     \
    }                                                                       \
    void CAT_4(BACKENDNAME,_,SAFE_VERSION,_init)()                          \
    {                                                                       \
      using namespace Pipes :: CAT_4(BACKENDNAME,_,SAFE_VERSION,_init) ;    \
      using namespace Backends :: CAT_3(BACKENDNAME,_,SAFE_VERSION) ;       \

/// Boilerplate code for convenience function definitions
#define BE_NAMESPACE                                                        \
namespace Gambit                                                            \
{                                                                           \
  namespace Backends                                                        \
  {                                                                         \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                             \

/// Closer for initialisation function definitional boilerplate.
#define END_BE_INI_FUNCTION }}}

/// Closer for convenience function definitional boilerplate.
#define END_BE_NAMESPACE }}

/// \name Variadic redirection macro for BE_VARIABLE(NAME, TYPE, SYMBOLNAME, CAPABILITY, [(ALLOWED_MODELS)], [REF])
#define BE_VARIABLE_6(_1, _2, _3, _4, _5, _6)      BE_VARIABLE_I(_1, _2, _3, _4, _5, _6)
#define BE_VARIABLE_5(_1, _2, _3, _4, _5)          BE_VARIABLE_I(_1, _2, _3, _4, _5, "")
#define BE_VARIABLE_4(_1, _2, _3, _4)              BE_VARIABLE_I(_1, _2, _3, _4, (), "")
#define BE_VARIABLE(...)                           VARARG(BE_VARIABLE, __VA_ARGS__)

/// \name Variadic redirection macro for BE_CONV_FUNCTION(NAME, TYPE, ARGSLIST, CAPABILITY, [(ALLOWED_MODELS)], [REF])
#define BE_CONV_FUNCTION_6(_1, _2, _3, _4, _5,_6) BE_CONV_FUNCTION_FULL(_1, _2, _3, _4, _5, _6)
#define BE_CONV_FUNCTION_5(_1, _2, _3, _4, _5)    BE_CONV_FUNCTION_FULL(_1, _2, _3, _4, _5, "")
#define BE_CONV_FUNCTION_4(_1, _2, _3, _4)        BE_CONV_FUNCTION_FULL(_1, _2, _3, _4, (), "")
#define BE_CONV_FUNCTION(...)                     VARARG(BE_CONV_FUNCTION, __VA_ARGS__)

/// Evaluates to ARG if and only if we have pybind11 and USING_PYTHON is true
#ifdef HAVE_PYBIND11
  #define IF_USING_PYBIND11(ARG) BOOST_PP_IF(USING_PYTHON, ARG, )
#else
  #define IF_USING_PYBIND11(ARG)
#endif

#endif // __COMMON_MACROS_HPP__
