//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Fronted header for the CaptnGeneral backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  Aaron Vincent
///  \date 2017 Sep-Nov
///  *********************************************

#define BACKENDNAME CaptnGeneral
#define BACKENDLANG FORTRAN
#define VERSION 1.0
#define SAFE_VERSION 1_0

// Load the library
LOAD_LIBRARY

BE_ALLOW_MODELS(Halo_Einasto_rho0,Halo_gNFW_rho0)
// Functions
BE_FUNCTION(captn_init,void,(const char&,const double&,const double&,const double&,const double&),"captn_init_","captn_init")
BE_FUNCTION(captn_general, void, (const double&,const double&,const int&,const int&,const int&,double&), "captn_general_", "cap_Sun_vnqn_isoscalar")
BE_FUNCTION(captn_specific, void, (const double&,const double&,const double&,double&,double&), "captn_specific_", "cap_Sun_v0q0_isoscalar")
BE_FUNCTION(captn_maxcap, void, (const double&,double&), "captn_maxcap_", "cap_sun_saturation")

// Undefine macros to avoid conflict with other backends

BE_INI_DEPENDENCY(RD_fraction,double)
#include "gambit/Backends/backend_undefs.hpp"
