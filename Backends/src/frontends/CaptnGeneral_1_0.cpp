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
                                                                    "/solarmodels/struct_b16_agss09_reduce10_nohead.dat", "solarmodel"));
	//Capgen checks whether the arrays are already allocated, so it's fine to do this at point-level
	  captn_init(solarmodel[0],rho0,vsun,v0,vesc);
	  captn_init_oper();

    //double m = *Param["m"];
    //double j = *Param["j"];
  	
    //Load every coupling constant in
    // is there a way to do default values? (eg if param == Null, set to 0.0?)
/*
    double const0c1 = *Param["0c1"];
    double const0c2 = *Param["0c2"];
  	double const0c3 = *Param["0c3"];
  	double const0c4 = *Param["0c4"];
  	double const0c5 = *Param["0c5"];
  	double const0c6 = *Param["0c6"];
  	double const0c7 = *Param["0c7"];
  	double const0c8 = *Param["0c8"];
  	double const0c9 = *Param["0c9"];
  	double const0c10 = *Param["0c10"];
  	double const0c11 = *Param["0c11"];
  	double const0c12 = *Param["0c12"];
  	double const0c13 = *Param["0c13"];
  	double const0c14 = *Param["0c14"];
  	double const0c15 = *Param["0c15"];

    double const1c1 = *Param["1c1"];
    double const1c2 = *Param["1c2"];
  	double const1c3 = *Param["1c3"];
  	double const1c4 = *Param["1c4"];
  	double const1c5 = *Param["1c5"];
  	double const1c6 = *Param["1c6"];
  	double const1c7 = *Param["1c7"];
  	double const1c8 = *Param["1c8"];
  	double const1c9 = *Param["1c9"];
  	double const1c10 = *Param["1c10"];
  	double const1c11 = *Param["1c11"];
  	double const1c12 = *Param["1c12"];
  	double const1c13 = *Param["1c13"];
  	double const1c14 = *Param["1c14"];
  	double const1c15 = *Param["1c15"];

    double coupling_array [2][15] = {{const0c1, const0c2, const0c3, const0c4, const0c5, const0c6, const0c7, const0c8, const0c9, const0c10, const0c11, const0c12, const0c13, const0c14, const0c15}, {const1c1, const1c2, const1c3, const1c4, const1c5, const1c6, const1c7, const1c8, const1c9, const1c10, const1c11, const1c12, const1c13, const1c14, const1c15}};
*/
    for(int i=0; i<2; i++)
      {
        for(int j=1; j<16; j++)
        {
          if (j != 2) // 2 is not an allowed coupling constant
          {
            populate_array(0, j, i);
          }
        }
      }

}
END_BE_INI_FUNCTION
