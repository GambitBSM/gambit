//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source code for types for module CosmoBit.
///  For instructions on adding new types, see
///  the corresponding header.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///
///  \author Selim Hotinli
///  \date 2018 Jan
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#include <string>
#include <iostream>
#include <valarray>

#include "gambit/CosmoBit/CosmoBit_types.hpp"

namespace Gambit
{
  namespace CosmoBit
  {
    // return Parametrised_ps members A_s, n_s, r, and N_pivot as str to double map for printing
    map_str_dbl Parametrised_ps::get_parametrised_ps_map()
    {
      map_str_dbl result;
      result["ln10A_s"] = ln10A_s;
      result["n_s"] = n_s;
      result["r"] = r;
      result["N_pivot"] = N_pivot;

      return result;
    };

    void Primordial_ps::fill_k(double *k_array, int len)
    {
      std::vector<double> K(k_array, k_array+len);
      k = std::move(K);
      vec_size = len;
    }

    void Primordial_ps::fill_P_s(double *P_s_array, int len)
    {
      std::vector<double> ps(P_s_array, P_s_array+len);
      P_s = std::move(ps);
    }

    void Primordial_ps::fill_P_s_iso(double *P_s_iso_array, int len)
    {
      std::vector<double> psi(P_s_iso_array, P_s_iso_array+len);
      P_s_iso = std::move(psi);
    }

    void Primordial_ps::fill_P_t(double *P_t_array, int len)
    {
      std::vector<double> pt(P_t_array, P_t_array+len);
      P_t = std::move(pt);
    }
  }
}
