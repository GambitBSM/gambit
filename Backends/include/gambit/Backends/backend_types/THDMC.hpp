//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of types
///  for the THDMC backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Filip Rajec
///  \date Aug 2016
///
///  *********************************************

#include "gambit/Utils/util_types.hpp"
#include <cmath>
#include <complex>

#ifndef __THDMC_types_hpp__
#define __THDMC_types_hpp__

namespace Gambit
{

  // NB: Containers offset by one to align with higgs & fermion numbers
  // Container for all THDMC couplings
  struct thdmc_couplings {
      std::complex<double> hdd_cs[5][4][4], hdd_cp[5][4][4];
      std::complex<double> huu_cs[5][4][4], huu_cp[5][4][4];
      std::complex<double> hll_cs[5][4][4], hll_cp[5][4][4];
      std::complex<double> hdu_cs[5][4][4], hdu_cp[5][4][4];
      std::complex<double> hln_cs[5][4][4], hln_cp[5][4][4];
      std::complex<double> vhh[4][5][5];
      std::complex<double> vvh[4][4][5];
      std::complex<double> vvhh[4][4][5][5];
      std::complex<double> hhh[5][5][5];
      std::complex<double> hhhh[5][5][5][5];
  };

  struct THDM_decay_widths {
      double gamma_uhd[4][5][4];
      double gamma_hdd[5][4][4];
      double gamma_huu[5][4][4];
      double gamma_hdu[5][4][4];
      double gamma_hll[5][4][4];
      double gamma_hln[5][4][4];
      double gamma_hgg[5];
      double gamma_hgaga[5];
      double gamma_hZga[5];
      double gamma_hvv[5][4];
      double gamma_hvh[5][4][5];
      double gamma_hhh[5][5][5];
  };

  struct THDM_total_widths {
    double gamma_tot_h[5], gamma_tot_t, gamma_tot_t_SM_contrib, gamma_tot_v[4];
    bool isValid;
  };

}

#endif
