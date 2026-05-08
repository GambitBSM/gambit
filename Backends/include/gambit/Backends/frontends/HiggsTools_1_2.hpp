//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the HiggsTools backend (Python interface).
///
///  *********************************************

#define BACKENDNAME HiggsTools
#define BACKENDLANG Python3
#define VERSION 1.2
#define SAFE_VERSION 1_2
#define REFERENCE Bahl:2022igd

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_CONV_FUNCTION(HiggsTools_LHC_LogLike, double, (const HiggsTools_input&), "HiggsTools_LHC_LogLike")
  BE_CONV_FUNCTION(HiggsTools_run_bounds,  double, (const HiggsTools_input&), "HiggsTools_run_bounds")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
