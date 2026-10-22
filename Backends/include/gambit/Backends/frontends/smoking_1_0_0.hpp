//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the smoking backend v1.0.0.
///
///  smoking computes NLO+NLL hadronic cross-sections for
///  slepton and electroweakino pair production.
///
///  The backend exposes three extern "C" functions from
///  libsmoking_gambit.so:
///
///    init_SMOKING          -- initialise integrators, PDFs, processes
///    Calculate_cross_section -- run the calculation for one SLHA point
///    finalise_SMOKING      -- clean up all resources
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Chang
///          (c.j.chang@fys.uio.no)
///  \date 2026 Apr
///
///  *********************************************

#define BACKENDNAME smoking
#define BACKENDLANG CXX
#define VERSION 1.0.0
#define SAFE_VERSION 1_0_0
#define REFERENCE TODO

// Load the shared library
LOAD_LIBRARY

// Pull in the GAMBIT-side mirror of smoking's types
#include "gambit/Backends/backend_types/smoking.hpp"

/* Syntax:
 * BE_FUNCTION(gambit_name, return_type, (arg_types), "symbol_name", "capability_name")
 *
 * The symbol names are unmangled because the functions are declared extern "C"
 * in smoking's gambit_interface.cpp.
 */

BE_FUNCTION(smoking_init,    int,  (smoking_variables&), "init_SMOKING",            "smoking_init")
BE_FUNCTION(smoking_calc,    std::vector<Result>, (smoking_variables&), "Calculate_cross_section", "smoking_calc")
BE_FUNCTION(smoking_finalise, int, (),                   "finalise_SMOKING",        "smoking_finalise")

// Initialisation function
BE_INI_FUNCTION                                                                                                                                                                       
{                                                                                                                                                                                     
}                                                                                                                                                                                     
END_BE_INI_FUNCTION


// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
