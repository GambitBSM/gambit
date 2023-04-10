//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the DarkSUSY backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2022 January, 2023
///
///  *********************************************

#define BACKENDNAME DarkSUSY_generic_wimp
#define BACKENDLANG FORTRAN
#define VERSION 6.4.0
#define SAFE_VERSION 6_4_0
#define REFERENCE Gondolo:2004sc,Bringmann:2018lay

// Load the library
LOAD_LIBRARY

// Include common DarkSUSY frontend declarations shared across all model-specific versions of the backend
#include "gambit/Backends/frontends/shared_includes/DarkSUSY_6.hpp"

// Common blocks in the DarkSUSY core library that are not identical for all DS6 versions
BE_VARIABLE(rdpars, DS_RDPARS,     "rdpars_",    "rdpars")    // gRD Parameters

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
