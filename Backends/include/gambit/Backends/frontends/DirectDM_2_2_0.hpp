//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the DirectDM backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Sep, Oct
///  \date 2020 Mar
///
///  \author Markus Prim
///          (markus.prim@cern.ch)
///  \date 2020 Dec
///
///  *********************************************

#define BACKENDNAME DirectDM
#define BACKENDLANG Python
#define VERSION 2.2.0
#define SAFE_VERSION 2_2_0
#define REFERENCE Bishara:2017nnn,Brod:2017bsw

LOAD_LIBRARY

// Forward declaration of custom return type (defined in gambit/Backends/backend_types/DDCalc.hpp)
namespace Gambit { class NREO_DM_nucleon_couplings; }

BE_CONV_FUNCTION(get_NR_WCs_flav, NREO_DM_nucleon_couplings, (map_str_dbl&, double&, int&, std::string&, map_str_dbl&), "get_NR_WCs_flav")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
