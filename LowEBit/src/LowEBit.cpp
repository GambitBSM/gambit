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
             *1.16E-4;
          result.Cd[1] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *1.45E-4;
          result.Cs[1] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *1.45E-5;
          result.Cu[2] = (*Param["kappaU"])*(*Param["SinPhiU"])
             *(-1.07E-4);
          result.Cd[2] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *(-1.14E-4);
          result.Cs[2] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *(-1.14E-4);
      }

      void EDM_q_Wilson(dq &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
      // TODO: Make work at any scale.
      {
         using namespace Pipes::EDM_q_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = sqrt(2)*gf*2/3*mu*c.Cu[1]*gevtocm;
         result.d = sqrt(2)*gf*(-1/3)*md*c.Cd[1]*gevtocm;
         result.s = sqrt(2)*gf*(-1/3)*ms*c.Cs[1]*gevtocm;
         //Heavy quarks for completeness??
      }

      void CEDM_q_Wilson(dq &result)
	  // Calculation of quark chromoEDMs (at mu_had) from Wilson Coefficients in cm
      // TODO: Make work at any scale.
      {
         using namespace Pipes::CEDM_q_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = -sqrt(2)*gf*mu*c.Cu[2]*gevtocm;
         result.d = -sqrt(2)*gf*md*c.Cd[2]*gevtocm;
         result.s = -sqrt(2)*gf*ms*c.Cs[2]*gevtocm;
         //Heavy quarks for completeness??
      }

      void EDM_n_quark(double &result)
      // Calculation of neutron EDM from quark EDMs and CEDMs in e cm
      {
         using namespace Pipes::EDM_n_quark;

    	 double e = sqrt(4*pi/Dep::SMINPUTS->alphainv);
         dq dEDM = *Dep::EDM_q;
         dq dCEDM = *Dep::CEDM_q;

         result = ((*Param["rhoD"])*dCEDM.d+(*Param["rhoU"])*dCEDM.u)/e
            + (*Param["gTu"])*dEDM.u + (*Param["gTd"])*dEDM.d
			+ (*Param["gTs"])*dEDM.s;
      }

   }
}
