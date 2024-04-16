//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the MultiModeCode backend.
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Feb
///
///  *********************************************

#define BACKENDNAME MultiModeCode
#define BACKENDLANG FORTRAN
#define VERSION 2.0.0
#define SAFE_VERSION 2_0_0
#define REFERENCE Mortonson:2010er,Price:2014xpa

// Load it
LOAD_LIBRARY

BE_FUNCTION(multimodecode_primordial_ps, gambit_inflation_observables,
            (int&,int&,int&,int&,double*,double*,double*,double&,double&,double&,int&,double&,double&,int&,int&,int&,int&,int&),
            ("__multimodecode_gambit_MOD_multimodecode_gambit_driver","multimodecode_gambit_mp_multimodecode_gambit_driver_"), "multimodecode_primordial_ps")

BE_FUNCTION(multimodecode_parametrised_ps, gambit_inflation_observables,
            (int&,int&,int&,int&,double*,double*,double*,double&,double&,double&,int&,int&,int&,int&,int&),
            ("__multimodecode_gambit_MOD_multimodecode_parametrised_ps","multimodecode_gambit_mp_multimodecode_parametrised_ps_"), "multimodecode_parametrised_ps")

// Fortran error handling issue
BE_VARIABLE(ErrorHandler_cptr, fptr_void,
            ("__modpk_errorhandling_MOD_errorhandler_cptr","modpk_errorhandling_mp_errorhandler_cptr_"), "multimode_internal")

// Variable to silence MultiModeCode output
BE_VARIABLE(SilenceOutput, Flogical, ("__multimodecode_gambit_MOD_silenceoutput", "multimodecode_gambit_mp_silenceoutput_"), "multimode_internal")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
