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
   }
}
