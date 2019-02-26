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

using namespace std;

#ifndef __THDMC_types_hpp__
#define __THDMC_types_hpp__

namespace Gambit
{

  // Container for all THDMC couplings
  struct thdmc_couplings
  {   //hdd
      complex<double> hdd_cs[5][4][4], hdd_cp[5][4][4];
      //huu
      complex<double> huu_cs[5][4][4], huu_cp[5][4][4];
      //hll
      complex<double> hll_cs[5][4][4], hll_cp[5][4][4];
      //hdu
      complex<double> hdu_cs[5][4][4], hdu_cp[5][4][4];
      //
      complex<double> hln_cs[5][4][4], hln_cp[5][4][4];
      //
      complex<double> vhh[4][5][5];
      //
      complex<double> vvh[4][4][5];
      //
      complex<double> vvhh[4][4][5][5];
      //
      complex<double> hhh[5][5][5];
      //
      complex<double> hhhh[5][5][5][5];
  };

  struct thdmc_decay_widths
  {
      double gamma_uhd[4][5][4];
      //
      double gamma_hdd[5][4][4];
      //
      double gamma_huu[5][4][4];
      //
      double gamma_hdu[5][4][4];
      //
      double gamma_hll[5][4][4];
      //
      double gamma_hln[5][4][4];
      //
      double gamma_hgg[5];
      //
      double gamma_hgaga[5];
      //
      double gamma_hZga[5];
      //
      double gamma_hvv[5][4];
      //
      double gamma_hvh[5][4][5];
      //
      double gamma_hhh[5][5][5];
  };

  struct thdmc_total_widths
  {
    double gamma_tot_h[5], gamma_tot_t, gamma_tot_t_SM_contrib, gamma_tot_v[4];
    bool isValid;
  };
   

}

#endif
