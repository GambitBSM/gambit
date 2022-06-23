//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for HiggsBounds backend
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
///  \author Ankit Beniwal
///  \date Jul 2019
///  \date Jul 2020
///
///  *****************************************


#define BACKENDNAME HiggsBounds
#define BACKENDLANG FORTRAN
#define VERSION 5.3.2beta
#define SAFE_VERSION 5_3_2beta

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
BE_FUNCTION(run_HiggsBounds, void, (int&, int&, double&, int&), "run_higgsbounds_", "run_HiggsBounds")
BE_FUNCTION(run_HiggsBounds_classic, void, (int&, int&, double&, int&), "run_higgsbounds_classic_", "run_HiggsBounds_classic")
BE_FUNCTION(finish_HiggsBounds, void, (), "finish_higgsbounds_", "finish_HiggsBounds")
BE_FUNCTION(HiggsBounds_set_mass_uncertainties, void, (double*, double*), "higgsbounds_set_mass_uncertainties_", "HiggsBounds_set_mass_uncertainties")

// LEP chisq extension specific
BE_FUNCTION(initialize_HiggsBounds_chisqtables, void, (), "initialize_higgsbounds_chisqtables_", "initialize_HiggsBounds_chisqtables")
BE_FUNCTION(HB_calc_stats, void, (double&, double&, double&, int&), "hb_calc_stats_", "HB_calc_stats")
BE_FUNCTION(finish_HiggsBounds_chisqtables, void, (), "finish_higgsbounds_chisqtables_","finish_HiggsBounds_chisqtables")

// Input sub-routines
BE_FUNCTION(HiggsBounds_input_SLHA, void, (const char&), "higgsbounds_input_slha_", "HiggsBounds_input_SLHA")
BE_FUNCTION(HiggsBounds_neutral_input_properties, void, (double*, double*, double*), "higgsbounds_neutral_input_properties_", "HiggsBounds_neutral_input_properties")
BE_FUNCTION(HiggsBounds_neutral_input_effC, void, (double*, double*, double*, double*,
						  						   double*, double*, double*, double*,
                                                   double*, double*, double*, double*,
                                                   double*, double*, double*, double*,
                                                   double*, Farray<double, 1,3, 1,3>&), "higgsbounds_neutral_input_effc_", "HiggsBounds_neutral_input_effC")

BE_FUNCTION(HiggsBounds_neutral_input_SMBR, void, (double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*),
	    "higgsbounds_neutral_input_smbr_", "HiggsBounds_neutral_input_SMBR")
BE_FUNCTION(HiggsBounds_neutral_input_nonSMBR, void, (double*, Farray<double, 1,3, 1,3, 1,3>&, Farray<double, 1,3, 1,3>&, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_neutral_input_nonsmbr_", "HiggsBounds_neutral_input_nonSMBR")

BE_FUNCTION(HiggsBounds_neutral_input_LEP, void, (double*, double*, double*, Farray<double, 1,3, 1,3>&),
	    "higgsbounds_neutral_input_lep_", "HiggsBounds_neutral_input_LEP")
BE_FUNCTION(HiggsBounds_neutral_input_hadr, void, (int&, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3, 1,3>&),
	    "higgsbounds_neutral_input_hadr_", "HiggsBounds_neutral_input_hadr")

BE_FUNCTION(HiggsBounds_charged_input, void, (double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_charged_input_", "HiggsBounds_charged_input")
BE_FUNCTION(HiggsBounds_charged_input_hadr, void, (int&, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_charged_input_hadr_","HiggsBounds_charged_input_hadr")

// Allowed model usage
BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, NMSSM66atQ, THDM, THDMatQ)

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

