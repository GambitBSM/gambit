//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for Rivet backend v3.0.0
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///  \date   2019 July
///
///  *********************************************

#define BACKENDNAME Rivet
#define BACKENDLANG CC
#define VERSION 3.0.0
#define SAFE_VERSION 3_0_0

LOAD_LIBRARY

// Initialisation function (definition)
BE_INI_FUNCTION{} END_BE_INI_FUNCTION

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

