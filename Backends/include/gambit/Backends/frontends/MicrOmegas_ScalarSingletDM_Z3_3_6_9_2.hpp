//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas ScalarSingletDM_Z3 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Jonathan Cornell
/// \date May 2015, April 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_ScalarSingletDM_Z3
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_ALLOW_MODELS(ScalarSingletDM_Z3,ScalarSingletDM_Z3_running)

//Take function declarations from the common SingletDM header
#include "gambit/Backends/frontends/shared_includes/MicrOmegas_SingletDM_3_6_9_2.hpp"

BE_INI_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum)

#include "gambit/Backends/backend_undefs.hpp"

