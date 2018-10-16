//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for Capt'n General 1.0 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  Aaron Vincent
///  25/09/2017
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/CaptnGeneral_1_0.hpp"


// Capgen Initialisation function (definition)
BE_INI_FUNCTION
{
    double rho0  = *Param["rho0"]*(*Dep::RD_fraction);
    double v0    = *Param["v0"];
    double vsun  = *Param["vrot"];
    double vesc  = *Param["vesc"];

    const int clen = 300;
    char solarmodel[clen];
    Utils::strcpy2f(solarmodel, clen, runOptions->getValueOrDef<str>(backendDir +
                                                                    "/solarmodels/struct_b16_agss09_nohead.dat", "solarmodel"));
// //Capgen checks whether the arrays are already allocated, so it's fine to do this at point-level
  captn_init(solarmodel[0],rho0,vsun,v0,vesc);


}
END_BE_INI_FUNCTION
