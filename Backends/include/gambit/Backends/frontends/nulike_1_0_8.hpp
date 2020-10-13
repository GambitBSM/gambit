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

// Declare the relevant functions
#include "gambit/Backends/frontends/shared_includes/nulike_1_0.hpp"

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

