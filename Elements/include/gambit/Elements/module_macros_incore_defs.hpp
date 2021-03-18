//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Redirection macros for generic observable and
///  likelihood function macro definitions, for
///  inclusion from the Core.
///
///
///  Note here that \link FUNCTION() FUNCTION
///  \endlink is the actual module function name,
///  whereas both \link CAPABILITY() CAPABILITY
///  \endlink and all \em DEPs refer to the
///  abstract physical quantities that functions
///  may provide or require.  Thus, the provides()
///  methods expect a quantity input (i.e.
///  corresponding to a \link CAPABILITY()
///  CAPABILITY\endlink), the requires() methods
///  expect a quantity input for the dependency but a
///  function name input (i.e. corresponding to a
///  \link FUNCTION() FUNCTION\endlink) for
///  the actual dependent function, and all other
///  things operate on the basis of the function
///  name, not the quantity that is calculated.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2012 Nov
///  \date 2013,14 Foreverrrrr
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
///  \date 2019 Jul
///
///  *********************************************

#ifndef __module_macros_incore_defs_hpp__
#define __module_macros_incore_defs_hpp__

/// Change this to 1 if you really don't care about parameter clashes.
#define ALLOW_DUPLICATES_IN_PARAMS_MAP 0

#include <map>

#include "gambit/Elements/functors.hpp"
#include "gambit/Elements/types_rollcall.hpp"
#include "gambit/Elements/module_macros_common.hpp"
#include "gambit/Elements/safety_bucket.hpp"
#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Elements/elements_extras.hpp"
#include "gambit/Elements/terminator.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Utils/exceptions.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Models/claw_singleton.hpp"
#include "gambit/Models/safe_param_map.hpp"
#ifndef STANDALONE
  #include "gambit/Core/ini_functions.hpp"
#endif

#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/cat.hpp>


/// \name Tag-registration macros
/// @{
/// Add a regular tag to the current namespace
#define ADD_TAG_IN_CURRENT_NAMESPACE(TAG) namespace Tags { struct TAG; }
/// Add a backend tag to the current namespace
#define ADD_BETAG_IN_CURRENT_NAMESPACE(TAG) namespace BETags { struct TAG; }
/// Add a backend tag to the current namespace
#define ADD_MODEL_TAG_IN_CURRENT_NAMESPACE(TAG) namespace ModelTags { struct TAG; }
/// @}


//  *******************************************************************************
/// \name Actual in-core rollcall macros
/// These macros do the actual heavy lifting within the rollcall system.
/// @{

// Determine whether to make registration calls to the Core in the START_MODULE
// macro, depending on STANDALONE flag
#ifdef STANDALONE
  #define CORE_START_MODULE_COMMON(MODULE)                                     \
          CORE_START_MODULE_COMMON_MAIN(MODULE)
#else
  #define CORE_START_MODULE_COMMON(MODULE)                                     \
          CORE_START_MODULE_COMMON_MAIN(MODULE)                                \
          const int module_registered = register_module(STRINGIFY(MODULE));
#endif

/// Redirection of \link START_MODULE() START_MODULE\endlink when invoked from
/// within the core.
#define CORE_START_MODULE                                                      \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_MODULE."))                                                           \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Module errors */                                                      \
      error& CAT(MODULE,_error)()                                              \
      {                                                                        \
        static error local("A problem has been raised by " STRINGIFY(MODULE)   \
                           ".", STRINGIFY(MODULE) "_error");                   \
        return local;                                                          \
      }                                                                        \
                                                                               \
      /* Module warnings */                                                    \
      warning& CAT(MODULE,_warning)()                                          \
      {                                                                        \
        static warning local("A problem has been raised by " STRINGIFY(MODULE) \
                           ".", STRINGIFY(MODULE) "_warning");                 \
        return local;                                                          \
      }                                                                        \
                                                                               \
      /* Register the module error and warning objects by calling the          \
         above functions. */                                                   \
      error& temp_error_reference = CAT(MODULE,_error)();                      \
      warning& temp_warning_reference = CAT(MODULE,_warning)();                \
                                                                               \
      /* Register the module with the log system.  Not done for models. */     \
      const int log_registered = register_module_with_log(STRINGIFY(MODULE));  \
                                                                               \
                                                                               \
      CORE_START_MODULE_COMMON(MODULE)                                         \
                                                                               \
    }                                                                          \
                                                                               \
  }                                                                            \


/// Central module definition macro, used by modules and models.
#define CORE_START_MODULE_COMMON_MAIN(MODULE)                                  \
                                                                               \
      /* Resolve dependency DEP_TAG in function TAG */                         \
      template <typename DEP_TAG, typename TAG>                                \
      void resolve_dependency(functor*, module_functor_common*)                \
      {                                                                        \
        cout<<STRINGIFY(MODULE)<<" does not"<<endl;                            \
        cout<<"have this dependency for this function.";                       \
      }                                                                        \
                                                                               \
      /* Resolve backend requirement BE_REQ in function TAG */                 \
      template <typename BE_REQ, typename TAG>                                 \
      void resolve_backendreq(functor*)                                        \
      {                                                                        \
        cout<<STRINGIFY(MODULE)<<" does not"<<endl;                            \
        cout<<"have this backend requirement for this function.";              \
      }                                                                        \
                                                                               \
      /* Runtime registration function for dependency DEP_TAG of function TAG*/\
      template <typename DEP_TAG, typename TAG>                                \
      void rt_register_dependency ()                                           \
      {                                                                        \
        cout<<STRINGIFY(MODULE)<<" does not"<<endl;                            \
        cout<<"have this dependency for this function.";                       \
      }                                                                        \
                                                                               \
      /* Runtime registration of conditional dependency DEP_TAG of function    \
      TAG, where dependency exists if TAG requires backend function BE_REQ,    \
      and BE_REQ is provided by backend BE.*/                                  \
      template <typename DEP_TAG, typename TAG, typename BE_REQ, typename BE>  \
      void rt_register_conditional_dependency ()                               \
      {                                                                        \
        rt_register_conditional_dependency<DEP_TAG, TAG>();                    \
      }                                                                        \
      template <typename DEP_TAG, typename TAG>                                \
      void rt_register_conditional_dependency ()                               \
      {                                                                        \
        cout<<STRINGIFY(MODULE)<<" does not"<<endl;                            \
        cout<<"have any matching conditional dependency.";                     \
      }                                                                        \
                                                                               \
      /* Runtime registration function for backend req BE_REQ of               \
      function TAG*/                                                           \
      template <typename BE_REQ, typename TAG>                                 \
      void rt_register_req ()                                                  \
      {                                                                        \
        cout<<STRINGIFY(MODULE)<<" does not"<<endl;                            \
        cout<<"have this backend requirement for this function.";              \
      }                                                                        \


/// Redirection of \link START_CAPABILITY() START_CAPABILITY\endlink when
/// invoked from within the core.
#define CORE_START_CAPABILITY(MODULE, CAPABILITY, IS_MODEL)                    \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_CAPABILITY."))                                                       \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling START_CAPABILITY. Please check the rollcall header for "           \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Add CAPABILITY to the global set of things that can be calculated*/     \
    ADD_TAG_IN_CURRENT_NAMESPACE(CAPABILITY)                                   \
                                                                               \
  }                                                                            \


/// Redirection of \link START_FUNCTION() START_FUNCTION\endlink when invoked
/// from within the core.
#define CORE_DECLARE_FUNCTION(MODULE, CAPABILITY, FUNCTION, TYPE, FLAG, IS_MODEL)\
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_FUNCTION."))                                                         \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling START_FUNCTION. Please check the rollcall header for "             \
   STRINGIFY(MODULE) "."))                                                     \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "START_FUNCTION. Please check the rollcall header for "                     \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    /* Fail if a void-type function is declared, unless it can manage loops or \
       is an initialisation function. */                                       \
    BOOST_PP_IIF(BOOST_PP_BITAND(IS_TYPE(void,TYPE), BOOST_PP_EQUAL(FLAG, 0)), \
      FAIL("Module functions cannot have void results, unless they manage "    \
       "loops or are initialisation functions.  Loop managers are declared "   \
       "by adding CAN_MANAGE_LOOPS as the second argument of START_FUNCTION."  \
       "Initialisation functions are declared from frontend headers by using " \
       "the BE_INI_FUNCTION macro.  Please check the header file for module "  \
       STRINGIFY(MODULE) ", function " STRINGIFY(FUNCTION) ".")                \
    ,)                                                                         \
                                                                               \
    BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_NOT(IS_TYPE(void,TYPE)),             \
                                 BOOST_PP_EQUAL(FLAG, 2) ),                    \
      /* Fail if an initialisation function has a non-void return type */      \
      FAIL("Initialisation functions must have void results. This is "         \
       "indicated by using the BE_INI_FUNCTION macro in a frontend header.")   \
    ,)                                                                         \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Add FUNCTION to the module's set of recognised functions. */          \
      ADD_TAG_IN_CURRENT_NAMESPACE(FUNCTION)                                   \
                                                                               \
      /* Register (prototype) the function */                                  \
      BOOST_PP_IIF(IS_TYPE(void,TYPE),                                         \
        void FUNCTION();                                                       \
      ,                                                                        \
        void FUNCTION (TYPE &);                                                \
      )                                                                        \
                                                                               \
      /* Wrap it in a functor */                                               \
      MAKE_FUNCTOR(FUNCTION,TYPE,CAPABILITY,MODULE,BOOST_PP_EQUAL(FLAG, 1))    \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


// Determine whether to make registration calls to the Core in the MAKE_FUNCTOR
// macro, depending on STANDALONE flag
#ifdef STANDALONE
  #define MAKE_FUNCTOR(FUNCTION,TYPE,CAPABILITY,ORIGIN,CAN_MANAGE)             \
          MAKE_FUNCTOR_MAIN(FUNCTION,TYPE,CAPABILITY,ORIGIN,CAN_MANAGE)
#else
  #define MAKE_FUNCTOR(FUNCTION,TYPE,CAPABILITY,ORIGIN,CAN_MANAGE)             \
          MAKE_FUNCTOR_MAIN(FUNCTION,TYPE,CAPABILITY,ORIGIN,CAN_MANAGE)        \
          const int CAT(FUNCTION,_registered2) =                               \
           register_module_functor_core(Functown::FUNCTION);
#endif


/// Main parts of the functor creation
#define MAKE_FUNCTOR_MAIN(FUNCTION,TYPE,CAPABILITY,ORIGIN,CAN_MANAGE)          \
                                                                               \
  namespace Functown                                                           \
  {                                                                            \
    /* Create the function wrapper object (functor) */                         \
    BOOST_PP_IIF(IS_TYPE(ModelParameters,TYPE),                                \
      model_functor                                                            \
    ,                                                                          \
      module_functor<TYPE>                                                     \
    )                                                                          \
    FUNCTION (&ORIGIN::FUNCTION, STRINGIFY(FUNCTION), STRINGIFY(CAPABILITY),   \
     STRINGIFY(TYPE), STRINGIFY(ORIGIN), Models::ModelDB());                   \
    /* Set up a helper function to call the iterate method if the functor is   \
    able to manage loops. */                                                   \
    BOOST_PP_IIF(BOOST_PP_EQUAL(CAN_MANAGE, 1),                                \
     void CAT(FUNCTION,_iterate)(long long it) { FUNCTION.iterate(it); }       \
    ,)                                                                         \
    /* Create a helper function to indicate whether a given model is in use. */\
    BOOST_PP_IIF(IS_TYPE(ModelParameters,TYPE), ,                              \
     bool CAT(FUNCTION,_modelInUse)(str model)                                 \
     {                                                                         \
       return FUNCTION.getActiveModelFlag(model);                              \
     }                                                                         \
    )                                                                          \
  }                                                                            \
                                                                               \
  namespace Pipes                                                              \
  {                                                                            \
                                                                               \
    namespace FUNCTION                                                         \
    {                                                                          \
      /* Create a map to hold pointers to all the model parameters accessible  \
      to this functor */                                                       \
      Models::safe_param_map<safe_ptr<const double> > Param;                   \
      /* Pointer to function indicating whether a given model is in use.*/     \
      BOOST_PP_IIF(IS_TYPE(ModelParameters,TYPE), ,                            \
       bool (*ModelInUse)(str) = &Functown::CAT(FUNCTION,_modelInUse); )       \
      /* Declare a safe pointer to the functor's run options. */               \
      safe_ptr<Options> runOptions;                                            \
      /* Set up Downstream pipes */                                            \
      namespace Downstream                                                     \
      {                                                                        \
         /* Create a pipe to hold a vector of all capability,type pairs of     \
         functors that get connected downstream of this one. */                \
         safe_ptr<std::set<sspair>> dependees;                                 \
         /* Create a pipe to hold all subcaps given for downstream functors */ \
         safe_ptr<Options> subcaps;                                            \
      }                                                                        \
      /* Set up Loop pipes */                                                  \
      namespace Loop                                                           \
      {                                                                        \
        BOOST_PP_IIF(CAN_MANAGE,                                               \
         /* Create a pointer to the single iteration of the loop that can      \
         be executed by this functor */                                        \
         void (*executeIteration)(long long)=&Functown::CAT(FUNCTION,_iterate);\
         /* Declare a safe pointer to the flag indicating that a managed loop  \
         is ready for breaking. */                                             \
         safe_ptr<bool> done;                                                  \
         /* Declare a function that is used to reset the done flag. */         \
         void reset() { Functown::FUNCTION.resetLoop(); }                      \
        ,)                                                                     \
      }                                                                        \
    }                                                                          \
                                                                               \
  }                                                                            \
                                                                               \
  /* Register the function */                                                  \
  const int UNUSED_OK CAT(FUNCTION,_registered1) =                             \
   register_function(Functown::FUNCTION,                                       \
   CAN_MANAGE,                                                                 \
   BOOST_PP_IIF(CAN_MANAGE, &Pipes::FUNCTION::Loop::done, NULL),               \
   Pipes::FUNCTION::runOptions,                                                \
   Pipes::FUNCTION::Downstream::dependees,                                     \
   Pipes::FUNCTION::Downstream::subcaps);                                      \

// Determine whether to make registration calls to the Core in the
// CORE_NEEDS_MANAGER macro, depending on STANDALONE flag
#ifdef STANDALONE
  #define CORE_NEEDS_MANAGER(...)                                              \
          CORE_NEEDS_MANAGER_REDIRECT(__VA_ARGS__)
#else
  #define CORE_NEEDS_MANAGER(...)                                              \
          CORE_NEEDS_MANAGER_REDIRECT(__VA_ARGS__)                             \
          namespace Gambit { namespace MODULE { const int CAT(FUNCTION,        \
           _registered3) = register_management_req(Functown::FUNCTION); } }
#endif

/// Variadic redirection for NEEDS_MANAGER when invoked within the Core
/// @{
#define CORE_NEEDS_MANAGER_REDIRECT_2(_1, _2) CORE_NEEDS_MANAGER_2(_1,  _2)
#define CORE_NEEDS_MANAGER_REDIRECT_1(_1)     CORE_NEEDS_MANAGER_1(_1)
#define CORE_NEEDS_MANAGER_REDIRECT(...)      VARARG(CORE_NEEDS_MANAGER_REDIRECT, __VA_ARGS__)
/// @}

/// Redirection of NEEDS_MANAGER(LOOPMAN) when invoked from within the Core.
#define CORE_NEEDS_MANAGER_1(LOOPMAN)                                          \
  CORE_NEEDS_MANAGER_MAIN(LOOPMAN, any)

/// Redirection of NEEDS_MANAGER(LOOPMAN,TYPE) when invoked from within the Core.
#define CORE_NEEDS_MANAGER_2(LOOPMAN,TYPE)                                     \
  CORE_NEEDS_MANAGER_MAIN(LOOPMAN,TYPE)                                        \
  DEPENDENCY(LOOPMAN,TYPE)

/// Main redirection of NEEDS_MANAGER(LOOPMAN,TYPE) when invoked from within the Core.
#define CORE_NEEDS_MANAGER_MAIN(LOOPMAN,TYPE)                                  \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "NEEDS_MANAGER_WITH_CAPABILITY."))                                          \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling NEEDS_MANAGER_WITH_CAPABILITY. Please check the rollcall header "  \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "NEEDS_MANAGER_WITH_CAPABILITY. Please check the rollcall header for "      \
   STRINGIFY(MODULE) "."))                                                     \
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
            /* Create a safe pointer to the iteration number of the loop this  \
            functor is running within. */                                      \
            omp_safe_ptr<long long> iteration;                                 \
            /* Create a loop-breaking function that can be called to tell the  \
            functor's loop manager that it is time to break. */                \
            void wrapup() { Functown::FUNCTION.breakLoopFromManagedFunctor(); }\
            /* Create a function that can be called to break a loop            \
            immediately,, without finishing the current iteration. */          \
            void halt() { throw halt_loop_exception(); }                       \
            /* Create an iteration-skipping function that can be called to skip\
            on to the next iteration. */                                       \
            void cycle() { throw invalid_loop_iteration_exception(); }         \
          }                                                                    \
          /* Register the fact that this FUNCTION must be run by a manager with\
          capability LOOPMAN. */                                               \
          const int nest_reg = register_function_nesting(Functown::FUNCTION,   \
           Loop::iteration, STRINGIFY(LOOPMAN), STRINGIFY(TYPE));              \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }                                                                            \


/// Common components of CORE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION) and
/// CORE_START_CONDITIONAL_DEPENDENCY(TYPE).
#define DEPENDENCY_COMMON(DEP, TYPE, MODULE, FUNCTION)                         \
                                                                               \
      /* Given that TYPE is not void, create a safety_bucket for the           \
      dependency result. To be initialized automatically at runtime            \
      when the dependency is resolved. */                                      \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          BOOST_PP_IIF(IS_TYPE(void,TYPE), ,                                   \
           namespace Dep {dep_bucket<TYPE> DEP(STRINGIFY(MODULE),              \
           STRINGIFY(FUNCTION),STRINGIFY(DEP));})                              \
        }                                                                      \
      }                                                                        \
                                                                               \
      /* Resolve dependency DEP in FUNCTION */                                 \
      template <>                                                              \
      void resolve_dependency<Gambit::Tags::DEP, Tags::FUNCTION>(functor*      \
       dep_functor, module_functor_common* BOOST_PP_IIF(IS_TYPE(void,TYPE), ,  \
       this_functor))                                                          \
      {                                                                        \
        /* First try casting the dep pointer passed in to a module_functor */  \
        module_functor<TYPE> * ptr =                                           \
         dynamic_cast<module_functor<TYPE>*>(dep_functor);                     \
                                                                               \
        /* Now test if that cast worked */                                     \
        if (ptr == 0)  /* It didn't; throw an error. */                        \
        {                                                                      \
          str errmsg = "Null returned from dynamic cast of";                   \
          errmsg +=  "\ndependency functor in MODULE::resolve_dependency, for" \
                     "\ndependency DEP of function FUNCTION.  Attempt was to"  \
                     "\nresolve to " + dep_functor->name() + " in " +          \
                     dep_functor->origin() + ".";                              \
          utils_error().raise(LOCAL_INFO,errmsg);                              \
        }                                                                      \
                                                                               \
        /* It did! Now initialize the safety_bucket using the functors.*/      \
        BOOST_PP_IIF(IS_TYPE(void,TYPE), ,                                     \
          Pipes::FUNCTION::Dep::DEP.initialize(ptr,this_functor);              \
        )                                                                      \
                                                                               \
      }                                                                        \


/// Redirection of DEPENDENCY(DEP, TYPE) when invoked from within the core.
#define CORE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION, IS_MODEL_DEP)             \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
                                                                               \
    /* Add DEP to global set of tags of recognised module capabilities/deps */ \
    ADD_TAG_IN_CURRENT_NAMESPACE(DEP)                                          \
                                                                               \
    /* Put everything inside the Models namespace if this is a model dep */    \
    BOOST_PP_IIF(IS_MODEL_DEP, namespace Models {, )                           \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      DEPENDENCY_COMMON(DEP, TYPE, MODULE, FUNCTION)                           \
                                                                               \
      const int CAT_3(DEP,_for_,FUNCTION) = register_dependency(               \
       Functown::FUNCTION, STRINGIFY(DEP), STRINGIFY(TYPE),                    \
       &resolve_dependency<Gambit::Tags::DEP, Tags::FUNCTION>);                \
    }                                                                          \
                                                                               \
    /* Close the Models namespace if this is a model dep */                    \
    BOOST_PP_IIF(IS_MODEL_DEP, }, )                                            \
                                                                               \
  }                                                                            \

/// Redirection of ALLOW_MODEL when invoked from within the core.
#define CORE_ALLOWED_MODEL(MODULE,FUNCTION,MODEL,IS_MODEL)                     \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ALLOW_MODEL(S)."))                                                         \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ALLOW_MODEL(S). Please check the rollcall header for "                     \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    /* Add MODEL to global set of tags of recognised models */                 \
    ADD_MODEL_TAG_IN_CURRENT_NAMESPACE(MODEL)                                  \
    CORE_ALLOWED_MODEL_ARRANGE_DEP(MODULE,FUNCTION,MODEL)                      \
    CORE_ALLOW_MODEL(MODULE,FUNCTION,MODEL)                                    \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \

/// Redirection of ALLOW_MODEL_DEPENDENCE when invoked from within the core.
#define CORE_ALLOW_MODEL_DEPENDENCE(MODULE,FUNCTION,MODEL,IS_MODEL)            \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ALLOW_MODEL_DEPENDENCE."))                                                 \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ALLOW_MODEL_DEPENDENCE. Please check the rollcall header for "             \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    /* Add MODEL to global set of tags of recognised models */                 \
    ADD_MODEL_TAG_IN_CURRENT_NAMESPACE(MODEL)                                  \
    CORE_ALLOWED_MODEL_ARRANGE_DEP(MODULE,FUNCTION,MODEL)                      \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \

/// Set up the dependency on the parameters object of a given model.
#define CORE_ALLOWED_MODEL_ARRANGE_DEP(MODULE,FUNCTION,MODEL)                  \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Create a safety bucket to the model parameter values. To be filled    \
      automatically at runtime when the dependency is resolved. */             \
      namespace Pipes                                                          \
      {                                                                        \
        namespace FUNCTION                                                     \
        {                                                                      \
          namespace Dep                                                        \
          {                                                                    \
            dep_bucket<ModelParameters> CAT(MODEL,_parameters)                 \
             (STRINGIFY(MODULE),STRINGIFY(FUNCTION),                           \
             STRINGIFY(CAT(MODEL,_parameters)));                               \
          }                                                                    \
        }                                                                      \
      }                                                                        \
                                                                               \
      /* Resolve dependency on parameters of MODEL in FUNCTION */              \
      template <>                                                              \
      void resolve_dependency<ModelTags::MODEL, Tags::FUNCTION>                \
       (functor* params_functor, module_functor_common* this_functor)          \
      {                                                                        \
        /* First try casting the pointer passed in to a module_functor */      \
        module_functor<ModelParameters>* ptr =                                 \
         dynamic_cast<module_functor<ModelParameters>*>(params_functor);       \
                                                                               \
        /* Now test if that cast worked */                                     \
        if (ptr == 0)  /* It didn't; throw an error. */                        \
        {                                                                      \
          str errmsg = "Null returned from dynamic cast in";                   \
          errmsg +=  "\nMODULE::resolve_dependency, for model"                 \
                     "\nMODEL with function FUNCTION.  Attempt was to"         \
                     "\nresolve to " + params_functor->name() + " in " +       \
                     params_functor->origin() + ".";                           \
          utils_error().raise(LOCAL_INFO,errmsg);                              \
        }                                                                      \
                                                                               \
        /* It did! Now initialize the safety_bucket using the functors.*/      \
        Pipes::FUNCTION::Dep::CAT(MODEL,_parameters).initialize(ptr,           \
         this_functor);                                                        \
        /* Get a pointer to the parameter map provided by this MODEL */        \
        safe_ptr<ModelParameters> model_safe_ptr =                             \
         Pipes::FUNCTION::Dep::CAT(MODEL,_parameters).safe_pointer();          \
        /* Use that to add the parameters provided by this MODEL to the map    \
        of safe pointers to model parameters. */                               \
        for (std::map<str,double>::const_iterator it = model_safe_ptr->begin();\
         it != model_safe_ptr->end(); ++it)                                    \
        {                                                                      \
          BOOST_PP_IIF(ALLOW_DUPLICATES_IN_PARAMS_MAP, ,                       \
          if (Pipes::FUNCTION::Param.find(it->first) ==                        \
              Pipes::FUNCTION::Param.end())                                    \
          )                                                                    \
          {                                                                    \
            /* Add a safe pointer to the value of this parameter to the map*/  \
            Pipes::FUNCTION::Param.insert(                                     \
             std::pair<str,safe_ptr<const double> >(it->first,                 \
             safe_ptr<const double>(&(it->second)))                            \
            );                                                                 \
          }                                                                    \
          BOOST_PP_IIF(ALLOW_DUPLICATES_IN_PARAMS_MAP, ,                       \
          else                                                                 \
          {                                                                    \
            /* This parameter already exists in the map! Fail. */              \
            str errmsg = "Problem in " STRINGIFY(MODULE) "::resolve_";         \
            errmsg +=    "dependency, for model " STRINGIFY(MODEL)             \
                         " with function\n" STRINGIFY(FUNCTION) ".  Attempt "  \
                         "was to resolve to\n" + params_functor->name() +      \
                         " in " + params_functor->origin()                     \
                         + ".\nYou have tried to scan two models "             \
                         "simultaneously that have one or more\n parameters "  \
                         "in common.\nProblem parameter: " + it->first;        \
            utils_error().raise(LOCAL_INFO,errmsg);                            \
          }                                                                    \
          )                                                                    \
        }                                                                      \
      }                                                                        \
                                                                               \
      /* Register the dependency of the functor on the model parameters */     \
      const int CAT_3(MODEL,_params_for_,FUNCTION) =                           \
       register_model_parameter_dependency(Functown::FUNCTION,                 \
        STRINGIFY(MODEL), STRINGIFY(CAT(MODEL,_parameters)),                   \
         &resolve_dependency<ModelTags::MODEL, Tags::FUNCTION>);               \
                                                                               \
    }                                                                          \


/// Tell the functor that a single model is enough for it to be allowed to run.
#define CORE_ALLOW_MODEL(MODULE,FUNCTION,MODEL)                                \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Register the compatibility of the model with the functor */           \
      const int CAT_3(MODEL,_allowed_for_,FUNCTION) = register_model_singly(   \
        Functown::FUNCTION, STRINGIFY(MODEL));                                 \
    }                                                                          \


/// Redirection of ALLOW_MODEL_COMBINATION when invoked from the Core.
#define CORE_ALLOW_MODEL_COMBINATION(MODULE,FUNCTION,IS_MODEL,COMBO)           \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ALLOW_MODEL_COMBINATION."))                                                \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ALLOW_MODEL_COMBINATION. Please check the rollcall header for "            \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Register the combination as allowed with the functor */               \
      const int CAT_3(FUNCTION,_,BOOST_PP_SEQ_CAT(BOOST_PP_TUPLE_TO_SEQ((      \
       STRIP_PARENS(COMBO))))) = register_model_combination(Functown::FUNCTION,\
       STRINGIFY(COMBO));                                                      \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \


/// Redirection of MODEL_GROUP when invoked from within the Core.
#define CORE_MODEL_GROUP(MODULE,FUNCTION,GROUPNAME,GROUP,IS_MODEL)             \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "MODEL_GROUP."))                                                            \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "MODEL_GROUP. Please check the rollcall header for "                        \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  /* Register the group with the functor */                                    \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Register the model group with the functor */                          \
      const int CAT_3(GROUPNAME,_model_group_in_,FUNCTION) =                   \
       register_model_group(Functown::FUNCTION, STRINGIFY(GROUPNAME),          \
       STRINGIFY(GROUP));                                                      \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \

/// Redirection of BACKEND_GROUP(GROUP) when invoked from within the Core.
#define CORE_BE_GROUP(GROUP,IS_MODEL)                                          \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "BACKEND_GROUP."))                                                          \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling BACKEND_GROUP. Please check the rollcall header "                  \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "BACKEND_GROUP. Please check the rollcall header for "                      \
   STRINGIFY(MODULE) "."))                                                     \
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
          namespace BEgroup                                                    \
          {                                                                    \
            /* Declare a safe pointer to the functor's internal register of    \
            which backend requirement is activated from this group. */         \
            safe_ptr<str> GROUP =                                              \
             Functown::FUNCTION.getChosenReqFromGroup(STRINGIFY(GROUP));       \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
 }                                                                             \


/// Redirection of BACKEND_REQ(GROUP, REQUIREMENT, (TAGS), TYPE, [(ARGS)])
/// for declaring backend requirements when invoked from within the Core.
#define CORE_BACKEND_REQ(MODULE, CAPABILITY, FUNCTION, GROUP, REQUIREMENT,     \
                         TAGS, TYPE, ARGS, IS_VARIABLE, IS_MODEL)              \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "BACKEND_REQ."))                                                            \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling BACKEND_REQ. Please check the rollcall header "                    \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "BACKEND_REQ. Please check the rollcall header for "                        \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    /* If scan-level initialisation functions are implemented, the macro should\
    fail here if the user has tried to declare that a scan-level initialisation\
    function has a backend requirement. */                                     \
                                                                               \
    /* Add REQUIREMENT to global set of recognised backend func tags */        \
    ADD_BETAG_IN_CURRENT_NAMESPACE(REQUIREMENT)                                \
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
            typedef BEvariable_bucket<TYPE> CAT(REQUIREMENT,var);              \
            typedef BEfunction_bucket<BOOST_PP_IIF(IS_VARIABLE,int,TYPE(*)     \
             CONVERT_VARIADIC_ARG(ARGS)), TYPE                                 \
             INSERT_NONEMPTY(STRIP_VARIADIC_ARG(ARGS))>                        \
             CAT(REQUIREMENT,func);                                            \
            CAT(REQUIREMENT,BOOST_PP_IIF(IS_VARIABLE,var,func)) REQUIREMENT    \
             (STRINGIFY(MODULE),STRINGIFY(FUNCTION),STRINGIFY(REQUIREMENT));   \
          }                                                                    \
        }                                                                      \
      }                                                                        \
                                                                               \
      /* Resolve REQUIREMENT in FUNCTION */                                    \
      template <>                                                              \
      void resolve_backendreq<BETags::REQUIREMENT, Tags::FUNCTION>             \
       (functor* be_functor)                                                   \
      {                                                                        \
        /* First try casting the pointer passed in to a backend_functor*/      \
        typedef UNUSED_OK backend_functor<TYPE*(*)(), TYPE*>* var;             \
        typedef UNUSED_OK backend_functor<BOOST_PP_IIF(IS_VARIABLE,int,TYPE(*) \
         CONVERT_VARIADIC_ARG(ARGS)), TYPE                                     \
         INSERT_NONEMPTY(STRIP_VARIADIC_ARG(ARGS))>* func;                     \
        auto ptr =                                                             \
          dynamic_cast<BOOST_PP_IIF(IS_VARIABLE,var,func)>(be_functor);        \
                                                                               \
        /* Now test if that cast worked */                                     \
        if (ptr == 0)  /* It didn't; throw an error. */                        \
        {                                                                      \
          str errmsg = "Null returned from dynamic cast in";                   \
          errmsg +=  "\n" STRINGIFY(MODULE) "::resolve_backendreq, for backend"\
                     " requirement\n" STRINGIFY(REQUIREMENT) " of function "   \
                     STRINGIFY(FUNCTION) ".  Attempt was to"                   \
                     "\nresolve to " + be_functor->name() + " in " +           \
                     be_functor->origin() + ".";                               \
          utils_error().raise(LOCAL_INFO,errmsg);                              \
        }                                                                      \
                                                                               \
        /* It did! Now use the cast functor pointer to initialize              \
        the safety_bucket Pipes::FUNCTION::BEreq::REQUIREMENT. */              \
        Pipes::FUNCTION::BEreq::REQUIREMENT.initialize(ptr);                   \
      }                                                                        \
                                                                               \
      /* Register the backend requirement with the functor */                  \
      const int CAT_3(REQUIREMENT,_backend_for_,FUNCTION) =                    \
       register_backend_requirement(Functown::FUNCTION, STRINGIFY(GROUP),      \
       STRINGIFY(REQUIREMENT), STRINGIFY(TAGS), BOOST_PP_IIF(IS_VARIABLE,      \
       true, false), STRINGIFY(TYPE), STRINGIFY(CONVERT_VARIADIC_ARG(ARGS)),   \
       &resolve_backendreq<BETags::REQUIREMENT,Tags::FUNCTION>);               \
                                                                               \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of BACKEND_OPTION(BACKEND_AND_VERSIONS, TAGS) when invoked from
/// within the core.
#define CORE_BACKEND_OPTION(MODULE, CAPABILITY, FUNCTION, BE_AND_VER, TAGS,    \
 IS_MODEL)                                                                     \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "BACKEND_OPTION."))                                                         \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling BACKEND_OPTION. Please check the rollcall header "                 \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "BACKEND_OPTION. Please check the rollcall header for "                     \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Apply the rule */                                                     \
      const int CAT_5(FUNCTION,_,BOOST_PP_TUPLE_ELEM(0,(STRIP_PARENS           \
       (BE_AND_VER))),_,BOOST_PP_SEQ_CAT(BOOST_PP_TUPLE_TO_SEQ((               \
       STRIP_PARENS(TAGS))))) = apply_backend_option_rule(Functown::FUNCTION,  \
       STRINGIFY(BE_AND_VER), STRINGIFY(TAGS));                                \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of FORCE_SAME_BACKEND(TAGS) when invoked from within the core.
#define CORE_FORCE_SAME_BACKEND(IS_MODEL,...)                                  \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "FORCE_SAME_BACKEND."))                                                     \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling FORCE_SAME_BACKEND. Please check the rollcall header "             \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "FORCE_SAME_BACKEND. Please check the rollcall header for "                 \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      const int CAT_3(FUNCTION,_,BOOST_PP_SEQ_CAT(BOOST_PP_TUPLE_TO_SEQ((      \
       STRIP_PARENS(__VA_ARGS__))))) =                                         \
       apply_backend_matching_rule(Functown::FUNCTION, #__VA_ARGS__);          \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \



/// Redirection of START_CONDITIONAL_DEPENDENCY(TYPE) when invoked from within
/// the core.
#define CORE_START_CONDITIONAL_DEPENDENCY(MODULE, CAPABILITY, FUNCTION,        \
 CONDITIONAL_DEPENDENCY, TYPE, IS_MODEL)                                       \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "START_CONDITIONAL_DEPENDENCY."))                                           \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling START_CONDITIONAL_DEPENDENCY. Please check the rollcall header "   \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "START_CONDITIONAL_DEPENDENCY. Please check the rollcall header for "       \
   STRINGIFY(MODULE) "."))                                                     \
  IF_TOKEN_UNDEFINED(CONDITIONAL_DEPENDENCY,FAIL("You must define "            \
   "CONDITIONAL_DEPENDENCY before calling START_CONDITIONAL_DEPENDENCY. Please"\
   " check the rollcall header for " STRINGIFY(MODULE) "."))                   \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Add dep to global set of tags of recognised module capabilities/deps */ \
    ADD_TAG_IN_CURRENT_NAMESPACE(CONDITIONAL_DEPENDENCY)                       \
                                                                               \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      DEPENDENCY_COMMON(CONDITIONAL_DEPENDENCY, TYPE, MODULE, FUNCTION)        \
                                                                               \
      const int CAT_3(CONDITIONAL_DEPENDENCY,_for_,FUNCTION) =                 \
       register_conditional_dependency(Functown::FUNCTION,                     \
       STRINGIFY(CONDITIONAL_DEPENDENCY), STRINGIFY(TYPE));                    \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of ACTIVATE_DEP_BE(BACKEND_REQ, BACKEND, VERSTRING) when
/// invoked from within the core.
#define CORE_ACTIVATE_DEP_BE(BACKEND_REQ, BACKEND, VERSTRING, IS_MODEL)        \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ACTIVATE_FOR_BACKEND."))                                                   \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling ACTIVATE_FOR_BACKEND. Please check the rollcall header "           \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ACTIVATE_FOR_BACKEND. Please check the rollcall header for "               \
   STRINGIFY(MODULE) "."))                                                     \
  IF_TOKEN_UNDEFINED(CONDITIONAL_DEPENDENCY,FAIL("You must define "            \
   "CONDITIONAL_DEPENDENCY before calling ACTIVATE_FOR_BACKEND. Please"        \
   " check the rollcall header for " STRINGIFY(MODULE) "."))                   \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    /* Add BACKEND to global set of recognised backend tags */                 \
    ADD_BETAG_IN_CURRENT_NAMESPACE(BACKEND)                                    \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Register the backend conditional dependency with the functor */       \
      const int CAT_7(CONDITIONAL_DEPENDENCY,_for_,FUNCTION,_with_,BACKEND_REQ,\
       _provided_by_,BACKEND) = register_backend_conditional_dependency(       \
       Functown::FUNCTION, STRINGIFY(BACKEND_REQ), STRINGIFY(BACKEND),         \
       VERSTRING, STRINGIFY(CONDITIONAL_DEPENDENCY), &resolve_dependency       \
       <Gambit::Tags::CONDITIONAL_DEPENDENCY, Tags::FUNCTION>);                \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of ACTIVATE_BACKEND_REQ_FOR_MODELS when invoked from the Core.
#define CORE_BE_MODEL_RULE(MODELS,TAGS,IS_MODEL)                               \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ACTIVATE_BACKEND_REQ_FOR_MODEL(S)."))                                      \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling ACTIVATE_BACKEND_REQ_FOR_MODEL(S). Please check the rollcall heade"\
   "r for " STRINGIFY(MODULE) "."))                                            \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ACTIVATE_BACKEND_REQ_FOR_MODEL(S). Please check the rollcall header for "  \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      /* Apply the rule.*/                                                     \
      const int CAT_6(apply_rule_,FUNCTION,_,                                  \
       BOOST_PP_SEQ_CAT(BOOST_PP_TUPLE_TO_SEQ((STRIP_PARENS(MODELS)))),_,      \
       BOOST_PP_SEQ_CAT(BOOST_PP_TUPLE_TO_SEQ((STRIP_PARENS(TAGS)))) ) =       \
       set_backend_rule_for_model(Functown::FUNCTION,#MODELS,#TAGS);           \
                                                                               \
    }                                                                          \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
  }                                                                            \


/// Redirection of ACTIVATE_FOR_MODELS(MODELSTRING) when invoked from within
/// the core, inside a CONDITIONAL_DEPENDENCY definition.
#define ACTIVATE_DEP_MODEL(MODULE, CAPABILITY, FUNCTION,                       \
 CONDITIONAL_DEPENDENCY,IS_MODEL,MODELSTRING)                                  \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "ACTIVATE_FOR_MODEL(S)."))                                                  \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling ACTIVATE_FOR_MODEL(S). Please check the rollcall header "          \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "ACTIVATE_FOR_MODEL(S). Please check the rollcall header for "              \
   STRINGIFY(MODULE) "."))                                                     \
  IF_TOKEN_UNDEFINED(CONDITIONAL_DEPENDENCY,FAIL("You must define "            \
  "CONDITIONAL_DEPENDENCY before calling ACTIVATE_FOR_MODEL(S)."               \
  " Please check the rollcall header for " STRINGIFY(MODULE) "."))             \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
      /* Register the conditional dependency. */                               \
      const int CAT_4(CONDITIONAL_DEPENDENCY,_for_,FUNCTION,_with_models) =    \
       register_model_conditional_dependency(Functown::FUNCTION,               \
       MODELSTRING, STRINGIFY(CONDITIONAL_DEPENDENCY),                         \
       &resolve_dependency<Gambit::Tags::CONDITIONAL_DEPENDENCY,               \
         Tags::FUNCTION>);                                                     \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \


/// Redirection of NEEDS_CLASSES_FROM when invoked from within the Core.
#define CORE_CLASSLOAD_NEEDED(BACKEND, VERSTRING, IS_MODEL)                    \
                                                                               \
  IF_TOKEN_UNDEFINED(MODULE,FAIL("You must define MODULE before calling "      \
   "NEEDS_CLASSES_FROM."))                                                     \
  IF_TOKEN_UNDEFINED(CAPABILITY,FAIL("You must define CAPABILITY before "      \
   "calling NEEDS_CLASSES_FROM. Please check the rollcall header "             \
   "for " STRINGIFY(MODULE) "."))                                              \
  IF_TOKEN_UNDEFINED(FUNCTION,FAIL("You must define FUNCTION before calling "  \
   "NEEDS_CLASSES_FROM. Please check the rollcall header for "                 \
   STRINGIFY(MODULE) "."))                                                     \
                                                                               \
  namespace Gambit                                                             \
  {                                                                            \
    /* Put everything inside the Models namespace if this is a model-module */ \
    BOOST_PP_IIF(IS_MODEL, namespace Models {, )                               \
                                                                               \
    namespace MODULE                                                           \
    {                                                                          \
                                                                               \
      const int CAT_4(classloading_from_,BACKEND,_for_,FUNCTION) =             \
       set_classload_requirements(Functown::FUNCTION, STRINGIFY(BACKEND),      \
       VERSTRING, STRINGIFY(CAT(Default_,BACKEND)));                           \
                                                                               \
    }                                                                          \
                                                                               \
    /* End Models namespace */                                                 \
    BOOST_PP_IIF(IS_MODEL, }, )                                                \
                                                                               \
  }                                                                            \

/// @}

#endif // defined __core_module_macros_incore_defs_hpp__

