//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source code for utilities needed in module CosmoBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 20190 Mar, June
///  *********************************************

#include "gambit/CosmoBit/CosmoBit_utils.hpp"
#include "gambit/Utils/numerical_constants.hpp"

namespace Gambit
{
  namespace CosmoBit
  {
    namespace CosmoBit_utils
    {

      // Return entropy density of SM as function of Temperature T. By default: T interpreted to be in K,
      // set T_in_eV = True if T is in eV
      double entropy_density_SM(double T, bool T_in_eV)
      {
        const double N_eff = 3.045;
        const double gstar_s = 2. + 2. * N_eff * 7./8. * 4./11.;

        if(T_in_eV == true) {T = T/kB_eV_over_K;}

        return (2.*pow(pi,2)/45.) * gstar_s * pow((kB_eV_over_K*T),3);
      }
    }
  }
}
