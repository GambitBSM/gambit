//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Redirection macros for generic observable and 
///  likelihood function macro definitions, for 
///  inclusion from actual module source code.
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
//
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

#ifndef __module_macros_inmodule_hpp__
#define __module_macros_inmodule_hpp__

#include "gambit/Elements/module_macros_inmodule_defs.hpp"

/// \name Rollcall macros
/// These are called from within rollcall headers in each module to
/// register module functions, their capabilities, return types, dependencies,
/// and backend requirements.
/// @{
// Redirect the rollcall macros to their in-module variants
#define START_MODULE                                      MODULE_START_MODULE
#define START_CAPABILITY                                  MODULE_START_CAPABILITY(MODULE)
#define LONG_START_CAPABILITY(MODULE, C)                  MODULE_START_CAPABILITY(MODULE)
#define DECLARE_FUNCTION(TYPE, CAN_MANAGE)                MODULE_DECLARE_FUNCTION(MODULE, FUNCTION, TYPE, CAN_MANAGE, NOT_MODEL)
#define LONG_DECLARE_FUNCTION(MODULE, C, FUNCTION, TYPE, CAN_MANAGE) \
                                                          MODULE_DECLARE_FUNCTION(MODULE, FUNCTION, TYPE, CAN_MANAGE, NOT_MODEL)
#define DEPENDENCY(DEP, TYPE)                             MODULE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION, NOT_MODEL)
#define LONG_DEPENDENCY(MODULE, FUNCTION, DEP, TYPE)      MODULE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION, NOT_MODEL)
#define NEEDS_MANAGER(...)                                MODULE_NEEDS_MANAGER_REDIRECT(__VA_ARGS__)
#define ALLOW_MODELS(...)                                 ALLOW_MODELS_AB(MODULE, FUNCTION, __VA_ARGS__)
#define ALLOWED_MODEL(MODULE,FUNCTION,MODEL)              MODULE_ALLOWED_MODEL(MODULE,FUNCTION,MODEL,NOT_MODEL)
#define ALLOWED_MODEL_DEPENDENCE(MODULE,FUNCTION,MODEL)   MODULE_ALLOWED_MODEL(MODULE,FUNCTION,MODEL,NOT_MODEL)
#define ALLOW_MODEL_COMBINATION(...)                      DUMMYARG(__VA_ARGS__)
#define MODEL_GROUP(GROUPNAME, GROUP)                     DUMMYARG(GROUPNAME, GROUP)

#define BE_GROUP(GROUP)                                   MODULE_BE_GROUP(GROUP,NOT_MODEL)
#define DECLARE_BACKEND_REQ(GROUP, REQUIREMENT, TAGS, TYPE, ARGS, IS_VARIABLE) \
                                                          MODULE_BACKEND_REQ(MODULE, FUNCTION, GROUP, REQUIREMENT, TAGS, TYPE, ARGS, IS_VARIABLE, NOT_MODEL)
#define LONG_DECLARE_BACKEND_REQ(MODULE, C, FUNCTION, GROUP, REQUIREMENT, TAGS, TYPE, ARGS, IS_VARIABLE) \
                                                          MODULE_BACKEND_REQ(MODULE, FUNCTION, GROUP, REQUIREMENT, TAGS, TYPE, ARGS, IS_VARIABLE, NOT_MODEL)
#define ACTIVATE_BACKEND_REQ_FOR_MODELS(MODELS,TAGS)      DUMMYARG(MODELS,TAGS)
#define START_CONDITIONAL_DEPENDENCY(TYPE)                MODULE_DEPENDENCY(CONDITIONAL_DEPENDENCY, TYPE, MODULE, FUNCTION, NOT_MODEL)
#define ACTIVATE_DEP_BE(BACKEND_REQ, BACKEND, VERSTRING)  DUMMYARG(BACKEND_REQ, BACKEND, VERSTRING)
#define ACTIVATE_FOR_MODELS(...)                          DUMMYARG(__VA_ARGS__)
#define MODEL_CONDITIONAL_DEPENDENCY(DEP, TYPE, ...)      MODULE_DEPENDENCY(DEP, TYPE, MODULE, FUNCTION, NOT_MODEL)
#define BACKEND_OPTION(BACKEND_AND_VERSIONS,TAGS)         DUMMYARG(BACKEND_AND_VERSIONS,TAGS)
#define LONG_BACKEND_OPTION(MODULE, CAPABILITY, FUNCTION, BACKEND_AND_VERSIONS,TAGS) \
                                                          DUMMYARG(BACKEND_AND_VERSIONS,TAGS)
#define FORCE_SAME_BACKEND(...)                           DUMMYARG(__VA_ARGS__)
#define CLASSLOAD_NEEDED(...)                             DUMMYARG(__VA_ARGS__)
/// @}


#endif // defined __module_macros_inmodule_hpp__

