//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the HepLike data package.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Jan, Feb
///
///  *********************************************

#define BACKENDNAME HepLikeData
#define BACKENDLANG Data
#define VERSION 1.8
#define SAFE_VERSION 1_8
#define REFERENCE Bhom:2020bfe

// Load it
LOAD_LIBRARY

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
