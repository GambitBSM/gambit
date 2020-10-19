//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas DiracSingletDM_Z2 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Jonathan Cornell
/// \date May 2015, April 2017
///
/// \author Ankit Beniwal
/// \date Oct 2016, Jun 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_DiracSingletDM_Z2
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_ALLOW_MODELS(DiracSingletDM_Z2)

//Take function declarations from the common SingletDM header
#include "gambit/Backends/frontends/shared_includes/MicrOmegas_SingletDM_3_6_9_2.hpp"

BE_INI_DEPENDENCY(DiracSingletDM_Z2_spectrum, Spectrum)

#include "gambit/Backends/backend_undefs.hpp"

