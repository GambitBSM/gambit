//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for making things from frontend headers
///  accessible from within source files that
///  define backend convenience and initialisation
///  functions.
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
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Dec
///  \date 2021 Sep
///
///  *********************************************

#ifndef __FRONTEND_MACROS_HPP__
#define __FRONTEND_MACROS_HPP__

#include "gambit/Elements/module_macros_inmodule.hpp"
#include "gambit/Backends/common_macros.hpp"
#include "gambit/Backends/interoperability.hpp"
#include "gambit/Backends/backend_singleton.hpp"


/// Indicate that this is all occuring in some compile unit other than the main executable.
#define BACKEND_SPECIFIC_COMPILE_UNIT 1

/// Dependency macro for point-level backend initialisation functions (in BackendIniBit)
#define BE_INI_DEPENDENCY(DEP, TYPE) MODULE_DEPENDENCY(DEP, TYPE, BackendIniBit, CAT_5(BACKENDNAME,_,SAFE_VERSION,_,init), NOT_MODEL)

/// Model-conditional dependency macro for point-level backend initialisation functions (in BackendIniBit)
#define BE_INI_CONDITIONAL_DEPENDENCY(DEP, TYPE, ...) MODULE_DEPENDENCY(DEP, TYPE, BackendIniBit, CAT_5(BACKENDNAME,_,SAFE_VERSION,_,init), NOT_MODEL)

/// Macro for assigning a single allowed model to an entire backend.
#define BE_ALLOW_MODEL(MODEL) MODULE_ALLOWED_MODEL(BackendIniBit,           \
 CAT_4(BACKENDNAME,_,SAFE_VERSION,_init), MODEL, NOT_MODEL)                 \

/// Make the inUse pipe for a given backend functor.
#define MAKE_INUSE_POINTER(NAME)                                            \
  namespace BackendIniBit                                                   \
  {                                                                         \
    namespace Pipes                                                         \
    {                                                                       \
      namespace CAT_4(BACKENDNAME,_,SAFE_VERSION,_init)                     \
      {                                                                     \
        namespace InUse                                                     \
        {                                                                   \
          extern safe_ptr<bool> NAME;                                       \
        }                                                                   \
      }                                                                     \
    }                                                                       \
  }                                                                         \

/// Macro containing initialization code
#define LOAD_LIBRARY                                                        \
namespace Gambit                                                            \
{                                                                           \
  namespace Backends                                                        \
  {                                                                         \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                             \
    {                                                                       \
      extern std::vector<str> allowed_models;                               \
      /* Make backend path easily available to convenience functions. */    \
      extern const str backendDir;                                          \
      /* Make an easy reference to the actual backend module if it is a */  \
      /* Python backend. */                                                 \
      IF_USING_PYBIND11(extern pybind11::module& BACKENDNAME;)              \
    }                                                                       \
  }                                                                         \
}                                                                           \
                                                                            \
/* Register the initialisation function for this backend */                 \
MODULE_START_CAPABILITY(BackendIniBit)                                      \
MODULE_DECLARE_FUNCTION(BackendIniBit,                                      \
 CAT_4(BACKENDNAME,_,SAFE_VERSION,_init),                                   \
 void,2,NOT_MODEL)                                                          \

/// Main actual backend variable macro
#define BE_VARIABLE_I(NAME, TYPE, SYMBOLNAME, CAPABILITY, MODELS, REF)        \
namespace Gambit                                                              \
{                                                                             \
  namespace Backends                                                          \
  {                                                                           \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                               \
    {                                                                         \
      /* Choose the type to define the variable pointer */                    \
      typedef MATH_TYPE(TYPE) NAME##_type;                                    \
      /* Set the variable pointer and the getptr function. */                 \
      extern NAME##_type* const NAME;                                         \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* Create the safe pointer to the 'in use' flag of the functor. */          \
  MAKE_INUSE_POINTER(NAME)                                                    \
                                                                              \
} /* end namespace Gambit */                                                  \


/// \name Wrapping macros for backend-defined functions
///
/// BE_FUNCTION(NAME, TYPE, ARGSLIST, SYMBOLNAME, CAPABILITY, [(MODELS)], [REF]) is the
/// macro used for constructing pointers to library functions and
/// wrapping function pointers in backend functors.
///
/// The sixth argument (MODELS) is optional, and contains a list of models that you want this function to be able
/// to be used with.
/// The seventh argument REF is optional, and contains a string of citation keys as references for the backend function
/// @{

#define BE_FUNCTION_5(NAME, TYPE, ARGSLIST, SYMBOLNAME, CAPABILITY)                             \
  BE_FUNCTION_I(NAME, TYPE, ARGSLIST, SYMBOLNAME, CAPABILITY, (), "")

#define BE_FUNCTION_6(NAME, TYPE, ARGSLIST, SYMBOLNAME, CAPABILITY, MODELS)                     \
  BE_FUNCTION_I(NAME, TYPE, ARGSLIST, SYMBOLNAME, CAPABILITY, MODELS, "")

#define BE_FUNCTION_7(NAME, TYPE, ARGSLIST, SYMBOLNAMES, CAPABILITY, MODELS, REF)               \
  BE_FUNCTION_I(NAME, TYPE, ARGSLIST, SYMBOLNAMES, CAPABILITY, MODELS, REF)

#define BE_FUNCTION(...) VARARG(BE_FUNCTION, __VA_ARGS__)


/// Main actual backend function macro
#define BE_FUNCTION_I(NAME, TYPE, ARGLIST, SYMBOLNAME, CAPABILITY, MODELS, REF)                 \
namespace Gambit                                                                                \
{                                                                                               \
  namespace Backends                                                                            \
  {                                                                                             \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                                 \
    {                                                                                           \
      /* Define a type NAME_type to be a suitable function pointer. */                          \
      typedef TYPE (*NAME##_type) CONVERT_VARIADIC_ARG(ARGLIST);                                \
      /* Get the pointer to the function in the shared library. */                              \
      extern const NAME##_type NAME;                                                            \
    }                                                                                           \
  }                                                                                             \
                                                                                                \
  /* Create the safe pointer to the 'in use' flag of the functor. */                            \
  MAKE_INUSE_POINTER(NAME)                                                                      \
                                                                                                \
}                                                                                               \


/// \name Main wrapping macro for convenience functions
/// BE_CONV_FUNCTION(NAME, TYPE, ARGSLIST, CAPABILITY, [(MODELS)], [REF]) is the macro used
/// for wrapping convenience functions in backend functors.
#define BE_CONV_FUNCTION_FULL(NAME, TYPE, ARGSLIST, CAPABILITY, MODELS, REF)                    \
namespace Gambit                                                                                \
{                                                                                               \
  namespace Backends                                                                            \
  {                                                                                             \
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)                                                 \
    {                                                                                           \
      /* Forward declare function */                                                            \
      TYPE NAME(STRIP_PARENS(CONVERT_VARIADIC_ARG(ARGSLIST)));                                  \
    }                                                                                           \
  }                                                                                             \
  /* Create the safe pointer to the 'in use' flag of the functor. */                            \
  MAKE_INUSE_POINTER(NAME)                                                                      \
}                                                                                               \

#endif // __FRONTEND_MACROS_HPP__
