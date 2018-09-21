//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Z boson decays to supersymmetric particles at tree-level
///
///  \example MSSM_Z.cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.fowlie@monash.edu)
///  \date 2018 May
///
///  *********************************************

#ifndef DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_Z_HPP_
#define DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_Z_HPP_

#include <array>
#include <cmath>

namespace Gambit {
  namespace DecayBit {
    namespace MSSM_Z {

      double gamma_chi_0(int i,
        int j,
        std::array<double, 4> m,
        std::array<std::array<double, 4>, 4> Z,
        double g2 = 0.652,
        double MZ = 91.,
        double sw2 = 0.22) {
        /**
           @brief \f$\Gamma(Z \to \chi_i \chi_j)\f$ in GeV

           @warning Tree-level formula

           @returns \f$\Gamma(h \to \chi_i \chi_j)\f$ in GeV
           @param m Neutralino masses, \f$m_{\chi_i}\f$, without phases
           @param Z Real neutralino mixing matrix
           @param g2 \f$g_2\f$
           @param MZ \f$M_Z\f$, Z-boson mass
           @param sw2 Weinberg angle, \f$\sin^2\theta_W\f$
        */

        const double p2 = (pow(MZ, 2) - pow(m[i] + m[j], 2)) *
          (pow(MZ, 2) - pow(m[i] - m[j], 2)) / (4. * pow(MZ, 2));
        const double ei = (pow(MZ, 2) - pow(m[j], 2) + pow(m[i], 2)) / (2. * MZ);
        const double ej = (pow(MZ, 2) - pow(m[i], 2) + pow(m[j], 2)) / (2. * MZ);

        if (!(p2 > 0. && ei > 0. && ej > 0.)) {
          return 0.;
        }

        const double cw = std::sqrt(1. - sw2);

        const double gz = g2 / (2. * cw) * (Z[i][2] * Z[j][2] - Z[i][3] * Z[j][3]);
        double gamma = sqrt(p2) / (2. * M_PI * pow(MZ, 2)) * pow(gz, 2) *
          (ei * ej + p2 / 3. - m[i] * m[j]);

        if (i == j) {
          gamma *= 0.5;
        }

        return gamma;
      }
    }  // namespace MSSM_Z
  }  // namespace DecayBit
}  // namespace Gambit

#endif  //  DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_Z_HPP_
