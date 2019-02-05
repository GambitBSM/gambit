//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions of LowEBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jonathan.cornell@uc.edu)
///  \date 2019 Jan
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/LowEBit/LowEBit_rollcall.hpp"

namespace Gambit
{
   namespace LowEBit
   {
      void CPV_Wilson_q_Simple(CPV_WC_q &result)
  	  // Simple calculation 3.4-3.6 of 1811.05480, ignoring
      // uncertainties
      {
          using namespace Pipes::CPV_Wilson_q_Simple;

          result.Cu[1] = (*Param["kappaU"])*(*Param["SinPhiU"])
             *8.2E-5;
          result.Cd[1] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *10.1E-5;
          result.Cs[1] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *10.1E-5;
          result.Cu[2] = (*Param["kappaU"])*(*Param["SinPhiU"])
             *(-6.6E-5);
          result.Cd[2] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *(-6.6E-5);
          result.Cs[2] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *(-6.6E-5);
      }

      void EDM_q_Wilson(dq &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients
      // TODO: Make work at any scale.
      {
         using namespace Pipes::EDM_q_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double e = sqrt(4*pi/Dep::SMINPUTS->alphainv);
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = sqrt(2)*gf*2/3*e*mu*c.Cu[1];
         result.d = sqrt(2)*gf*(-1/3)*e*md*c.Cd[1];
         result.s = sqrt(2)*gf*(-1/3)*e*ms*c.Cs[1];
         //Heavy quarks for completeness??
      }
   }
}
