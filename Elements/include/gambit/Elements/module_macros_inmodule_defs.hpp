//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Generic observable and likelihood function
///  macro definitions, for inclusion from
///  macro redirection headers.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2012 Nov
///  \date 2013 All year
///  \date 2014 Foreverrrrr
///
///  \author Abram Krislock
///          (abram.krislock@fysik.su.se)
///  \date 2013 Jan, Feb
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jan, Feb, 2014 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Nov
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2015 Apr, 2019 Jul
///
///  *********************************************

#ifndef __module_macros_inmodule_defs_hpp__
#define __module_macros_inmodule_defs_hpp__

#include "gambit/Elements/safety_bucket.hpp"
#include "gambit/Elements/module_macros_common.hpp"
#include "gambit/Utils/exceptions.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Models/safe_param_map.hpp"

#include <vector>

//  *******************************************************************************
/// \name In-module rollcall macros
/// @{

/// Redirection of \link START_MODULE() START_MODULE\endlink when
/// invoked from within a module.
#define MODULE_START_MODULE                                                    \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_MODULE."))                                                           \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    namespace MODULE                                                           \
    {                                                                          \
      /* Module errors */                                                      \
      error& CAT(MODULE,_error)();                                             \
      /* Module warnings */                                                    \
      warning& CAT(MODULE,_warning)();                                         \
    }                                                                          \
  }                                                                            \


/// Redirection of \link START_CAPABILITY() START_CAPABILITY\endlink when
/// invoked from within a module.
/// bjf> Does this actually do anything? Isn't MODULE always defined because
/// it is the macro argument here?
#define MODULE_START_CAPABILITY(MODULE)                                        \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_CAPABILITY."))                                                       \

/// Redirection of \link START_FUNCTION() START_FUNCTION\endlink when invoked
/// from within a module (or model-module)
#define MODULE_DECLARE_FUNCTION(MODULE, FUNCTION, TYPE, CAN_MANAGE, IS_MODEL)  \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Let the module source know that this functor is declared*/            \
      namespace Functown { extern module_functor<TYPE> FUNCTION; }             \
                                                                               \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          /* Declare the parameters safe-pointer map as external. */           \
          extern Models::safe_param_map<safe_ptr<const double> > Param;        \
          /* Declare pointer to model-in-use function as external. */          \
          BOOST_PP_IIF(IS_TYPE(ModelParameters,TYPE), ,                        \
           extern bool (*ModelInUse)(str); )                                   \
          /* Declare the safe pointer to the run options as external. */       \
          extern safe_ptr<Options> runOptions;                                 \
          /* Set up Downstream pipes */                                        \
          namespace Downstream                                                 \
          {                                                                    \
             /* Declare the dependees pipe external */                         \
             extern safe_ptr<std::set<sspair>> dependees;                      \
             /* Pipes to test whether dependees include specific things */     \
             template<typename... Args>                                        \
             bool neededFor(Args&&... args)                                    \
             { return Utils::sspairset_contains(args..., *dependees); }        \
             /* Declare the subcaps pipe external */                           \
             extern safe_ptr<Options> subcaps;                                 \
          }                                                                    \
          /* Set up Loop pipes */                                              \
          namespace Loop                                                       \
          {                                                                    \
            BOOST_PP_IIF(BOOST_PP_EQUAL(CAN_MANAGE, 1),                        \
              /* Create a pointer to the single iteration of the loop that can \
              be executed by this functor */                                   \
              extern void (*executeIteration)(long long);                      \
              /* Declare a safe pointer to the flag indicating that a managed  \
              loop is ready for breaking. */                                   \
              extern safe_ptr<bool> done;                                      \
              /* Declare a function that is used to reset the done flag. */    \
              extern void reset();                                             \
            ,)                                                                 \
          }                                                                    \
        }                                                                      \
      }                                                                        \
                                                                               \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Variadic redirection for NEEDS_MANAGER when invoked from within a module.
/// @{
#define MODULE_NEEDS_MANAGER_REDIRECT_2(_1, _2) MODULE_NEEDS_MANAGER_2(_1,  _2)
#define MODULE_NEEDS_MANAGER_REDIRECT_1(_1)     MODULE_NEEDS_MANAGER_1(_1)
#define MODULE_NEEDS_MANAGER_REDIRECT(...)      VARARG(MODULE_NEEDS_MANAGER_REDIRECT, __VA_ARGS__)
/// @}

/// Redirection of NEEDS_MANAGER(LOOPMAN, TYPE) when invoked from within a module.
#define MODULE_NEEDS_MANAGER_2(LOOPMAN, TYPE)                                  \
  MODULE_NEEDS_MANAGER_1(LOOPMAN)                                              \
  MODULE_DEPENDENCY(LOOPMAN, TYPE, MODULE, FUNCTION, NOT_MODEL)

/// Redirection of NEEDS_MANAGER(LOOPMAN) when invoked from within a module.
#define MODULE_NEEDS_MANAGER_1(LOOPMAN)                                        \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    namespace MODULE                                                           \
    {                                                                          \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          namespace Loop                                                       \
          {                                                                    \
            /* Declare the safe pointer to the iteration number of the loop    \
            this functor is running within, as external. */                    \
            extern omp_safe_ptr<long long> iteration;                          \
            /* Create a loop-breaking function that can be called to tell the  \
            functor's loop manager that it is time to break. */                \
            extern void wrapup();                                              \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \

/// Redirection of DEPENDENCY(DEP, TYPE) when invoked from within a module.
#define MODULE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION, IS_MODEL_DEP)           \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model dep */    \
    BOOST_PP_IIF(IS_MODEL_DEP, namespace Models {, )                           \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Given that TYPE is not void, create a safety_bucket for the           \
      dependency result. To be initialized automatically at runtime            \
      when the dependency is resolved. */                                      \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          BOOST_PP_IIF(IS_TYPE(void,TYPE),,                                    \
            namespace Dep { extern dep_bucket<TYPE> DEP; } )                   \
        }                                                                      \
                                                                               \
      }                                                                        \
                                                                               \
    }                                                                          \
                                                                               \
    /* Close the Models namespace if this is a model dep */                    \
    BOOST_PP_IIF(IS_MODEL_DEP, }, )                                            \
                                                                               \
  }                                                                            \


/// Redirection of ALLOW_MODEL when invoked from within a module.
#define MODULE_ALLOWED_MODEL(MODULE,FUNCTION,MODEL,IS_MODEL)                   \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Create a safe pointer to the model parameters result. To be filled    \
      automatically at runtime when the dependency is resolved. */             \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          namespace Dep {extern dep_bucket<ModelParameters>                    \
           CAT(MODEL,_parameters); }                                           \
        }                                                                      \
      }                                                                        \
                                                                               \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of BACKEND_GROUP(GROUP) when invoked from within a module.
#define MODULE_BE_GROUP(GROUP,IS_MODEL)                                        \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
    namespace MODULE                                                           \
    {                                                                          \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          namespace BEgroup                                                    \
          {                                                                    \
            /* Declare a safe pointer to the functor's internal register of    \
            which backend requirement is activated from this group. */         \
            extern safe_ptr<str> GROUP;                                        \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
  }                                                                            \


/// Redirection of BACKEND_REQ(GROUP, REQUIREMENT, (TAGS), TYPE, [(ARGS)])
/// for declaring backend requirements when invoked from within a module.
#define MODULE_BACKEND_REQ(MODULE, FUNCTION, GROUP, REQ, TAGS, TYPE, ARGS,     \
                           IS_VARIABLE,IS_MODEL)                               \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          namespace BEreq                                                      \
          {                                                                    \
            /* Create a safety_bucket for the backend variable/function.       \
            To be initialized by the dependency resolver at runtime. */        \
            typedef BEvariable_bucket<TYPE> CAT(REQ,var);                      \
            typedef BEfunction_bucket<BOOST_PP_IIF(IS_VARIABLE,int,TYPE(*)     \
             CONVERT_VARIADIC_ARG(ARGS)), TYPE                                 \
             INSERT_NONEMPTY(STRIP_VARIADIC_ARG(ARGS))> CAT(REQ,func);         \
            extern CAT(REQ,BOOST_PP_IIF(IS_VARIABLE,var,func)) REQ;            \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \

/// @}

#endif // defined __module_macros_inmodule_defs_hpp__

