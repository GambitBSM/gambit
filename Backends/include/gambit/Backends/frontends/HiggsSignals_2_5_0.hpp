//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for HiggsSignals backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///  \date Aug 2014
///
///  \author Pat Scott
///
///  \author Ankit Beniwal
///  \date Jul 2019
///  \date Jul 2020
///
///  \author Jonathan Cornell
///  \date Mar 2020
///
///  *****************************************


#define BACKENDNAME HiggsSignals
#define BACKENDLANG FORTRAN
#define VERSION 2.5.0
#define SAFE_VERSION 2_5_0

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

BE_FUNCTION(initialize_HiggsSignals, void, (int&, int&, char*, size_t), "initialize_higgssignals_", "initialize_HiggsSignals")
BE_FUNCTION(initialize_HiggsSignals_latestresults, void, (int&, int&), "initialize_higgssignals_latestresults_", "initialize_HiggsSignals_latestresults")
BE_FUNCTION(initialize_HiggsBounds_int_HS, void, (int&, int&, int&), "initialize_higgsbounds_int_", "initialize_HiggsBounds_int_HS")

BE_FUNCTION(setup_pdf, void, (int&), "setup_pdf_", "setup_pdf")
BE_FUNCTION(run_HiggsSignals_LHC_Run1_combination, void, (double&, double&, double&, int&, double&), "run_higgssignals_lhc_run1_combination_", "run_HiggsSignals_LHC_Run1_combination")
BE_FUNCTION(run_HiggsSignals, void, (double&, double&, double&, int&, double&), "run_higgssignals_", "run_HiggsSignals")
BE_FUNCTION(run_HiggsSignals_STXS, void, (double&, double&, double&, int&, double&), "run_higgssignals_stxs_", "run_HiggsSignals_STXS")
BE_FUNCTION(HiggsSignals_neutral_input_MassUncertainty, void, (double*), "higgssignals_neutral_input_massuncertainty_", "HiggsSignals_neutral_input_MassUncertainty")
BE_FUNCTION(HiggsBounds_get_LEPChisq, void, (double&, double&, double&, int&), "higgsbounds_get_lepchisq_", "HiggsBounds_get_LEPChisq")


BE_FUNCTION(finish_HiggsSignals, void, (), "finish_higgssignals_", "finish_HiggsSignals")
BE_FUNCTION(finish_HiggsBounds_HS, void, (), "finish_higgsbounds_", "finish_HiggsBounds_HS")

// Input sub-routines
BE_FUNCTION(HiggsBounds_input_SLHA_HS, void, (const char&), "higgsbounds_input_slha_", "HiggsBounds_input_SLHA_HS")
BE_FUNCTION(HiggsBounds_neutral_input_properties_HS, void, (double*, double*, double*), "higgsbounds_neutral_input_properties_", "HiggsBounds_neutral_input_properties_HS")
BE_FUNCTION(HiggsBounds_neutral_input_effC_HS, void, (double*, double*, double*, double*,
						      double*, double*, double*, double*,
						      double*, double*, double*, double*,
						      double*, double*, double*, double*,
						      double*, Farray<double, 1,3, 1,3>&), "higgsbounds_neutral_input_effc_", "HiggsBounds_neutral_input_effC_HS")

BE_FUNCTION(HiggsBounds_neutral_input_SMBR_HS, void, (double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*),
	    "higgsbounds_neutral_input_smbr_", "HiggsBounds_neutral_input_SMBR_HS")
BE_FUNCTION(HiggsBounds_neutral_input_nonSMBR_HS, void, (double*, Farray<double, 1,3, 1,3, 1,3>&, Farray<double, 1,3, 1,3>&, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_neutral_input_nonsmbr_", "HiggsBounds_neutral_input_nonSMBR_HS")

BE_FUNCTION(HiggsBounds_neutral_input_LEP_HS, void, (double*, double*, double*, Farray<double, 1,3, 1,3>&),
	    "higgsbounds_neutral_input_lep_", "HiggsBounds_neutral_input_LEP_HS")
BE_FUNCTION(HiggsBounds_neutral_input_hadr_HS, void, (int&, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3, 1,3>&),
	    "higgsbounds_neutral_input_hadr_", "HiggsBounds_neutral_input_hadr_HS")

BE_FUNCTION(HiggsBounds_charged_input_HS, void, (double*, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_charged_input_", "HiggsBounds_charged_input_HS")
BE_FUNCTION(HiggsBounds_charged_input_hadr_HS, void, (int&, double*, double*, double*, double*, double*, double*, double*, double*, double*, Farray<double, 1,3>&),
	    "higgsbounds_charged_input_hadr_","HiggsBounds_charged_input_hadr_HS")

// Allowed model usage
BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, NMSSM66atQ, THDM, THDMI, THDMII, THDMLS, THDMflipped, THDMatQ, THDMIatQ, THDMIIatQ, THDMLSatQ, THDMflippedatQ)

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
