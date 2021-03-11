//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the nulike backend.
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 May
///  \date 2014 March
///  \date 2015 Aug
///
///  *********************************************

#define BACKENDNAME nulike
#define BACKENDLANG Fortran
#define VERSION 1.0.8
#define SAFE_VERSION 1_0_8

// Load it
LOAD_LIBRARY

// Import functions
BE_FUNCTION(nulike_init, void, (const char&, const char&, const char&, const char&, const char&, double&, bool&, bool&), "nulike_init_", "nulike_init")
BE_FUNCTION(nulike_bounds, void, (const char&, const double&, const double&, nuyield_function_pointer, double&, double&, int&,
                                  double&, double&, const int&, const double&, const int&, const bool&, const double&, const double&, void*&, const bool&),
                                  "nulike_bounds", "nubounds")
BE_FUNCTION(nulike_lnpiln, double, (const int&, const double&, const double&, const double&), "nulike_lnpiln_", "lnlike_marg_poisson_lognormal_error")
BE_FUNCTION(nulike_lnpin,  double, (const int&, const double&, const double&, const double&), "nulike_lnpin_",  "lnlike_marg_poisson_gaussian_error")
// Arguments for the last two above are:
//  int    nobs   number of observed events
//  double npred1 number of predicted events with no uncertainty
//  double npred2 number of predicted events with an associated prediction uncertainty due to e.g. efficiency error
//  double error  fractional uncertainty on prediction npred2
// Note that the split into npred1 and npred2 is just for distinguishing which part of the
// predicition has the fractional uncertainty associated with it.  If the uncertainty is on
// the entire prediction, set npred1 = 0 and npred2 = total predicted events.

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

