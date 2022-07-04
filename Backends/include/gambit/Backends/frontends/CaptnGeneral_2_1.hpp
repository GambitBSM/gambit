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
///  Neal Avis Kozar
///  \date 2019 Jan-2021 Mar
///  *********************************************

#define BACKENDNAME CaptnGeneral
#define BACKENDLANG FORTRAN
#define VERSION 2.1
#define SAFE_VERSION 2_1
#define REFERENCE GAMBIT:2018eea,Kozar:2021iur

// Load the library
LOAD_LIBRARY

BE_ALLOW_MODELS(Halo_Einasto_rho0,Halo_gNFW_rho0,NREO_DiracDM,NREO_MajoranaDM,NREO_scalarDM,DMEFT)
// Functions
BE_FUNCTION(captn_init, void, (const char&, const double&, const double&, const double&, const double&),"captn_init_","captn_init")
BE_FUNCTION(captn_general, void, (const double&, const double&, const int&, const int&, const int&, const double&, double&), "captn_general_", "cap_Sun_vnqn_isoscalar")
BE_FUNCTION(captn_specific, void, (const double&, const double&, const double&, double&, double&), "captn_specific_", "cap_Sun_v0q0_isoscalar")
BE_FUNCTION(maxcap, double, (const double&), "maxcap_", "cap_sun_saturation")
BE_FUNCTION(captn_init_oper,void,(),"captn_init_oper_","captn_init_oper")
BE_FUNCTION(captn_oper,void,(const double&, const double&, const int&, double&),"captn_oper_","captn_NREO")
BE_FUNCTION(populate_array, void, (const double&, const int&, const int&), "populate_array_", "captn_populate_array")

// Undefine macros to avoid conflict with other backends

BE_INI_DEPENDENCY(RD_fraction,double)
#include "gambit/Backends/backend_undefs.hpp"
