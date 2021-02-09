//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source code for types for module LowEBit.
///  For instructions on adding new types, see
///  the corresponding header.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jonathan.cornell@uc.edu)
///  \date 2019 Feb
///
///  \author Dimitrios Skodras
///          (dimitrios.skodras@udo.edu)
///  \date 2020 Dec
///
///  *********************************************

#include "gambit/LowEBit/LowEBit_types.hpp"

namespace Gambit
{
   namespace LowEBit
   {
      CPV_WC_q::CPV_WC_q()
      {
    	  for (int i = 0; i <= 2; i++)
    		  Cu[i] = Cd[i] = Cs[i] = Cc[i] = Cb[i] = Ct[i] = Cw[i] = 0;
      }

      CPV_WC_qTEST::CPV_WC_qTEST()
      {
    	  for (int i = 0; i <= 2; i++)
    		  Cu[i] = Cd[i] = Cs[i] = Cc[i] = Cb[i] = Ct[i] = Cw[i] = 0;
      }
      CPV_WC_l::CPV_WC_l()
      {
    	  for (int i = 0; i <= 2; i++)
    		  Ce[i] = Cmu[i] = Ctau[i] = 0;
      }


      dq::dq()
      {
    	  u = d = s = c = b = t = w = 0;
      }
      dqTEST::dqTEST()
      {
    	  u = d = s = c = b = t = w = 0;
      }
 
      dl::dl()
      {
    	  e = mu = tau = 0;
      }
 
   }
}
