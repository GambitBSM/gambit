//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Frontend for HiggsBounds backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///  \date Aug 2014
///
///  \author Pat Scott
///  \date Aug 2016
///
///  *****************************************


#define BACKENDNAME HiggsBounds
#define BACKENDLANG FORTRAN
#define VERSION 4.3.1
#define SAFE_VERSION 4_3_1
#define REFERENCE Bechtle:2008jh,Bechtle:2011sb,Bechtle:2013wla

/* The following macro loads the library using dlopen
 * when this header file is included somewhere. */

LOAD_LIBRARY

/* Next we use macros BE_VARIABLE and BE_FUNCTION to load pointers
 * (using dlsym) to the variables and functions within the library.
 *
 * The macros also set up a minimal interface providing 'get/set'
 * functions for the library variables and function pointers
 * for the library functions.
 *
 * These functions are then wrapped in functors that the core can connect
 * to the modules via the rollcall system */

/* Syntax for BE_FUNCTION:
 * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]") */

BE_FUNCTION(initialize_HiggsBounds_int, void, (int&, int&, int&), "initialize_higgsbounds_int_", "initialize_HiggsBounds_int")
BE_FUNCTION(run_HiggsBounds_classic, void, (int&, int&, double&, int&), "run_higgsbounds_classic_", "run_HiggsBounds_classic")
BE_FUNCTION(finish_HiggsBounds, void, (), "finish_higgsbounds_", "finish_HiggsBounds")
BE_FUNCTION(HiggsBounds_set_mass_uncertainties, void, (double*, double*), "higgsbounds_set_mass_uncertainties_", "HiggsBounds_set_mass_uncertainties")

// LEP chisq extension specific
BE_FUNCTION(initialize_HiggsBounds_chisqtables, void, (), "initialize_higgsbounds_chisqtables_", "initialize_HiggsBounds_chisqtables")
BE_FUNCTION(HB_calc_stats, void, (double&, double&, double&, int&), "hb_calc_stats_", "HB_calc_stats")
BE_FUNCTION(finish_HiggsBounds_chisqtables, void, (), "finish_higgsbounds_chisqtables_","finish_HiggsBounds_chisqtables")

// Input sub-routines
BE_FUNCTION(HiggsBounds_input_SLHA, void, (const char&), "higgsbounds_input_slha_", "HiggsBounds_input_SLHA")
BE_FUNCTION(HiggsBounds_neutral_input_part, void, (double*, double*, int*, double*, double*, double*, double*,
               double*, double*, double*, double*, double*, double*, double*,
               double*, double*, double*, double*, double*, double*, double*,
               double*, double*, double*, double*, double*, double*, double*,
               double*, double*, double*, double*, double*, double*, double*,
               double*, double*, double*), "higgsbounds_neutral_input_part_", "HiggsBounds_neutral_input_part")
BE_FUNCTION(HiggsBounds_charged_input, void, (double*, double*, double*, double*,
                double*, double*, double*, double*), "higgsbounds_charged_input_", "HiggsBounds_charged_input")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

