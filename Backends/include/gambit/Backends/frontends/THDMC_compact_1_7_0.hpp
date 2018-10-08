//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for THDMC compact.
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Filip
///  \date 2018 Sept.
///
///  *********************************************

#define BACKENDNAME THDMC_compact
#define BACKENDLANG CXX
#define VERSION 1.7.0
#define SAFE_VERSION 1_7_0

LOAD_LIBRARY

BE_ALLOW_MODELS(THDMatQ)

BE_FUNCTION(init, void, (), "_ZN5THDMC4initEv", "init")
BE_FUNCTION(set_param_gen, bool, (double , double , double ,
			 double , double , double ,
			 double , double , double ), "_ZN5THDMC13set_param_genEddddddddd", "set_param_gen")
BE_FUNCTION(set_yukawas_type, void, (int), "_ZN5THDMC16set_yukawas_typeEi", "set_yukawas_type")

BE_FUNCTION(get_coupling_hhhh, void, (int,int,int,int,complex<double>&), "_ZN5THDMC17get_coupling_hhhhEiiiiRNSt3__17complexIdEE", "get_coupling_hhhh")

/* Convenience functions (declarations) */

// Initialisation function (dependencies)
// BE_INI_DEPENDENCY(SMINPUTS, SMInputs)
BE_INI_DEPENDENCY(THDM_spectrum, Spectrum)

// Undefine macros toa void conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
