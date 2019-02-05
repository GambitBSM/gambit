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
///  *********************************************

#include "gambit/LowEBit/LowEBit_types.hpp"

namespace Gambit
{
   namespace LowEBit
   {
      CPV_WC_q::CPV_WC_q()
      {
    	  for (int i = 0; i <= 2; i++)
    		  Cu[i] = Cd[i] = Cs[i] = Cc[i] = Cb[i] = Ct[i] = 0;
      }

      dq::dq()
      {
    	  u = d = s = c = b = t = 0;
      }

      dcq::dcq()
      {
          u = d = s = c = b = t = 0;
      }
   }
}
