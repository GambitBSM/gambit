//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The Z-boson observables at two-loop from
///
///  Higher-order electroweak corrections to the partial widths and branching
///  ratios of the Z boson
///  By Ayres Freitas.
///  arXiv:1401.2447 [hep-ph].
///  10.1007/JHEP04(2014)070.
///  JHEP 1404 (2014) 070.
///
///  I refer to tables and equations in v3 (https://arxiv.org/abs/1401.2447v3).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.fowlie@monash.edu)
///  \date 2018 Apr
///
///  *********************************************

#ifndef SM_Z_HPP_
#define SM_Z_HPP_

#include <cmath>

namespace SM_Z {

// The central values in eq. 46.

constexpr struct {
  const double mh_OS = 125.7;  // GeV
  const double mt_OS = 173.2;
  const double MZ_OS = 91.1876;
  const double alpha_s_MSbar_MZ = 0.1184;
  const double delta_alpha_OS = 0.059;
} hat;

// Data in Table 7.

constexpr int kRows = 12;
constexpr int kCols = 17;
constexpr double table_7[kRows][kCols] = {
  {83.966, -0.1017, -0.06352, 0.05500, -0.00145, 0.8051, -0.027, -0.017,
    0.0066, -0.095, -0.010, -0.015, 0.23, -1.1, 0.064, 285, 0.0015},
  {83.776, -0.1016, -0.06339, 0.05488, -0.00145, 0.8036, -0.026, -0.017,
    0.0066, -0.095, -0.010, -0.015, 0.23, -1.1, 0.064, 285, 0.0015},
  {167.157, -0.1567, -0.1194, 0.1031, -0.00269, 1.258, -0.13, -0.020, 0.0133,
    -0.19, -0.018, -0.021, 0.34, -0.084, 0.064, 503, 0.002},
  {299.936, -0.5681, -0.2636, 0.2334, -0.00592, 4.057, -0.50, -0.058, 0.0352,
    14.26, 1.6, -0.081, 1.7, -11.1, 0.19, 1251, 0.006},
  {299.859, -0.5680, -0.2635, 0.2334, -0.00592, 4.056, -0.50, -0.058, 0.0352,
    14.26, 1.6, -0.081, 1.7, -11.1, 0.19, 1251, 0.006},
  {382.770, -0.6199, -0.3182, 0.2800, -0.00711, 3.810, -0.25, -0.060, 0.0420,
    10.20, -2.4, -0.083, 0.65, -10.1, 0.19, 1468, 0.006},
  {375.723, -0.5744, -0.3074, 0.2725, -0.00703, -2.292, -0.027, -0.013, 0.0428,
    10.53, -2.4, -0.088, 1.2, -10.1, 0.19, 1456, 0.006},
  {2494.24, -3.725, -2.019, 1.773, -0.04554, 19.63, -2.0, -0.36, 0.257, 58.60,
    -4.1, -0.53, 7.6, -56.0, 1.3, 9256, 0.04},
  {20750.9, -10.00, -1.83, 1.878, -0.0343, -38.8, -11, 1.2, 0.72, 732.1, -44,
    -0.64, 5.6, -357, -4.7, 11771},
  {172.23, -0.034, -0.0058, 0.0054, -0.00012, 1.00, -0.15, -0.0074, 0.00091,
    2.3, 1.3, -0.0013, 0.35, -1.2, 0.014, 37,  0.01},
  {215.80, 0.036, 0.0057, -0.0044, 6.2e-5, -2.98, 0.20, 0.020, -0.00036, -1.3,
    -0.84, -0.0019, 0.054, 0.73, -0.011, -18,  0.01},
  {41488.4, 3.88, 0.829, -0.911, 0.0076, 61.10, 16, -2.0, -0.59, -579.4, 38,
    -0.26, 6.5, 84, 9.5, -86152,  0.25}
};


// Data in Table 6, though re-arranged to match columns in Table 7.
// The final entry isn't in the table and instead comes from the text below
// eq. 35.
constexpr int kEntries = 12;
constexpr double table_6[kEntries] =
  {0.012, 0.012, 0.12, 0.12, 0.09, 0.09, 0.21, 0.5, 5.e-3, 5.e-5, 1.5e-4, 6.};

class TwoLoop {
  /*
    Z-boson observables at two-loop and the residual theory errors.
  */
 public:
  // Partial widths in MeV
  double gamma_e() {return observable(0);}
  double gamma_mu() {return gamma_e();}
  double gamma_tau() {return observable(1);}
  double gamma_nu_e() {return observable(2);}
  double gamma_nu_mu() {return gamma_nu_e();}
  double gamma_invisible() {return 3. * gamma_nu_e();}
  double gamma_nu_tau() {return observable(2);}
  double gamma_u() {return observable(3);}
  double gamma_c() {return observable(4);}
  double gamma_t() {return 0.;}
  double gamma_d() {return observable(5);}
  double gamma_s() {return gamma_s();}
  double gamma_b() {return observable(6);}
  double gamma_total() {return observable(7);}

  // Residual theory error in partial widths in MeV
  double error_gamma_e() {return error(0);}
  double error_gamma_mu() {return error_gamma_e();}
  double error_gamma_tau() {return error(1);}
  double error_gamma_nu_e() {return error(2);}
  double error_gamma_nu_mu() {return error_gamma_nu_e();}
  double error_gamma_invisible() {return 3. * error_gamma_nu_e();}
  double error_gamma_nu_tau() {return error(2);}
  double error_gamma_u() {return error(3);}
  double error_gamma_c() {return error(4);}
  double error_gamma_t() {return 0.;}
  double error_gamma_d() {return error(5);}
  double error_gamma_s() {return error_gamma_d();}
  double error_gamma_b() {return error(6);}
  double error_gamma_total() {return error(7);}

  // Branching ratios
  double BR_e() {return gamma_e() / gamma_total();}
  double BR_mu() {return BR_e();}
  double BR_tau() {return gamma_tau() / gamma_total();}
  double BR_nu_e() {return gamma_nu_e() / gamma_total();}
  double BR_nu_mu() {return BR_nu_e();}
  double BR_nu_tau() {return BR_nu_e();}
  double BR_invisible() {return 3. * BR_nu_e();}
  double BR_u() {return gamma_u() / gamma_total();}
  double BR_c() {return gamma_c() / gamma_total();}
  double BR_t() {return 0.;}
  double BR_d() {return gamma_d() / gamma_total();}
  double BR_s() {return BR_d();}
  double BR_b() {return gamma_b() / gamma_total();}

  // Residual theory error in branching ratios
  double error_BR_e() {return error_BR(0);}
  double error_BR_mu() {return error_BR_e();}
  double error_BR_tau() {return error_BR(1);}
  double error_BR_nu_e() {return error_BR(2);}
  double error_BR_nu_mu() {return error_BR_nu_e();}
  double error_BR_invisible() {return 3. * error_BR_nu_e();}
  double error_BR_nu_tau() {return error_BR(2);}
  double error_BR_u() {return error_BR(3);}
  double error_BR_c() {return error_BR(4);}
  double error_BR_t() {return 0.;}
  double error_BR_d() {return error_BR(5);}
  double error_BR_s() {return error_BR_d();}
  double error_BR_b() {return error_BR(6);}

  // Ratios of partial widths, defined in eq. 27
  double Rl() {return 1.e-3 * observable(8);}
  double Rc() {return 1.e-3 * observable(9);}
  double Rb() {return 1.e-3 * observable(10);}

  // Residual theory error in ratios of partial widths
  double error_Rl() {return 1.e-3 * error(8);}
  double error_Rc() {return 1.e-3 * error(9);}
  double error_Rb() {return 1.e-3 * error(10);}

  // Hadronic peak cross section in pb, defined in eq. 10
  double sigma_0_had() {return observable(11);}

  // Residual theory error in hadronic peak cross section in pb
  double error_sigma_0_had() {return error(11);}

  TwoLoop(double mh_OS,
          double mt_OS,
          double MZ_OS,
          double alpha_s_MSbar_MZ,
          double delta_alpha_OS = hat.delta_alpha_OS) {
    /*
      @param mh_OS - Higgs mass in OS scheme
      @param mt_OS - Top quark mass in OS scheme
      @param MZ_OS - Z-mass in OS scheme
      @param alpha_s_MSbar_MZ - Strong coupling in MS-bar scheme at Q = M_Z
      @param delta_alpha_OS - \Delta\alpha parameter in OS scheme. Defined on p9
    */
    L_H = std::log(mh_OS / hat.mh_OS);
    delta_H = mh_OS / hat.mh_OS - 1.;
    delta_t = pow(mt_OS / hat.mt_OS, 2) - 1.;
    delta_z = MZ_OS / hat.MZ_OS - 1.;
    delta_alpha_s = alpha_s_MSbar_MZ / hat.alpha_s_MSbar_MZ - 1.;
    delta_delta_alpha = delta_alpha_OS / hat.delta_alpha_OS - 1.;
  }

 private:
  double L_H;
  double delta_H;
  double delta_t;
  double delta_z;
  double delta_alpha_s;
  double delta_delta_alpha;

  double error(int row) {
    /*
      Error in observable calculated from eq. 46. We add the error from the
      parametric formula and theory error in quadrature.

      @param row - row number of Table 7 corresponding to quantity.
    */
    return std::sqrt(pow(table_7[row][16], 2) + pow(table_6[row], 2));
  }

  double observable(int row) {
    /*
      The observable calculated from eq. 46.

      @param row - row number of Table 7 corresponding to quantity.
    */
    return table_7[row][0] +
           table_7[row][1] * L_H +
           table_7[row][2] * pow(L_H, 2) +
           table_7[row][3] * delta_H +
           table_7[row][4] * pow(delta_H, 2) +
           table_7[row][5] * delta_t +
           table_7[row][6] * pow(delta_t, 2) +
           table_7[row][7] * delta_t * L_H +
           table_7[row][8] * delta_t * pow(L_H, 2) +
           table_7[row][9] * delta_alpha_s +
           table_7[row][10] * pow(delta_alpha_s, 2) +
           table_7[row][11] * delta_alpha_s * L_H +
           table_7[row][12] * delta_alpha_s * delta_t +
           table_7[row][13] * delta_delta_alpha +
           table_7[row][14] * delta_delta_alpha * L_H +
           table_7[row][15] * delta_z;
  }

  double error_BR(int row) {
    /*
      The error in a branching ratio found by propagating errors.

      @param row - row number of Table 7 corresponding to quantity.
    */
    const double BR = observable(row) / gamma_total();
    const double frac_error_sq = pow(error_gamma_total() / gamma_total(), 2)
      + pow(error(row) / observable(row), 2);
    return std::sqrt(frac_error_sq) * BR;
  }
};

}  // namespace SM_Z

#endif  // SM_Z_HPP_
