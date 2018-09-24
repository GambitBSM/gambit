//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Higgs boson decays to supersymmetric particles at tree-level from
///
///  The Anatomy of Electro-Weak Symmetry Breaking. II:
///  The Higgs bosons in the Minimal Supersymmetric Model
///  Abdelhak Djouadi
///  arXiv:hep-ph/0503173
///
///  I refer to equations in v2 (https://arxiv.org/abs/hep-ph/0503173v2).
///
///  \example MSSM_H.cpp
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

#ifndef DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_H_HPP_
#define DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_H_HPP_

#include <cmath>
#include <array>
#include <stdexcept>


namespace Gambit {
  namespace DecayBit {
    namespace MSSM_H {

      double lambda(double x, double y, double z) {
        /**
           @brief Phase-space function (similar to Kallen function)

           \f[
           \lambda(x, y; z) = (1 - x / z - y / z)^2 - 4 x y / z^2
           \f]
        */
        if (z == 0.) {
          throw std::invalid_argument("z must be greater than zero");
        }

        return pow(1. - x / z - y / z, 2) - 4. * x * y / pow(z, 2);
      }

      double gamma_h_chi_gL(std::array<double, 2> m,
        double gL,
        double mh = 125.,
        double mw = 80.385,
        double GF = 1.1663787e-5) {
        /**
           @brief Eq. 2.56 for charginos or neutralinos
           @returns \f$\Gamma(h \to \chi_i \chi_j)\f$ in GeV
           @param m Masses of final state particles
           @param gL Coupling \f$g_L\f$ in Eq. 1.112
           @param mh Lightest Higgs mass, \f$m_h\f$
           @param mw W-boson mass, \f$M_W\f$
           @param GF Fermi constant, \f$G_F\f$
        */
        const double eps_2 = 1.;
        const double gR = gL * eps_2;

        // Phase-space

        if (std::fabs(m[0]) + std::fabs(m[1]) >= mh) {
          return 0.;
        }

        const double l = lambda(pow(m[0], 2), pow(m[1], 2), pow(mh, 2));
        if (l <= 0.) {
          return 0.;
        }

        // Eq. 2.56 without common factor (without f$\sin\theta_W\f$ which cancels)
        const double gamma_no_prefactor = std::sqrt(l) * ((
          pow(gL, 2) + pow(gR, 2)) * (1. - (pow(m[0], 2) + pow(m[1], 2)) / pow(mh, 2))
          -4. * gL * gR * m[0] * m[1] / pow(mh, 2));

        // Eq. 2.56 with common factor
        return GF * pow(mw, 2) / (2. * M_SQRT2 * M_PI) * mh * gamma_no_prefactor;
      }

      double gamma_h_chi_0(int i,
        int j,
        std::array<double, 4> m,
        std::array<std::array<double, 4>, 4> Z,
        double alpha,
        double mh = 125.,
        double mw = 80.385,
        double GF = 1.1663787e-5,
        double sw2 = 0.22) {
        /**
           @brief Lightest Higgs boson decay to neutralinos at tree-level in GeV

           @warning Arguments \f$i\f$ and \f$j\f$ are zero-based
           @warning Tree-level formula

           @returns \f$\Gamma(h \to \chi_i \chi_j)\f$ in GeV
           @param i Neutralino \f$\chi_i\f$ in final state
           @param j Neutralino \f$\chi_j\f$ in final state
           @param m Neutralino mases with phases
           @param Z Real neutralino mixing matrix
           @param alpha \f$\alpha\f$, Higgs mixing angle
           @param mh Lightest Higgs mass, \f$m_h\f$
           @param mw W-boson mass, \f$M_W\f$
           @param GF Fermi constant, \f$G_F\f$
           @param sw2 Weinberg angle, \f$\sin^2\theta_W\f$
        */
        // Weinberg angle
        const double tw = std::sqrt(sw2) / std::sqrt(1. - sw2);

        // Eq. 1.113
        const double e2 = -std::sin(alpha);
        const double d2 = -std::cos(alpha);

        // Eq. 1.112 (without \f$\sin\theta_W\f$ which cancels)
        const double gL = 0.5 * (
          (Z[j][1] - tw * Z[j][0]) * (e2 * Z[i][2] + d2 * Z[i][3]) +
          (Z[i][1] - tw * Z[i][0]) * (e2 * Z[j][2] + d2 * Z[j][3]));

        std::array<double, 2> mf{{m[i], m[j]}};
        double gamma = gamma_h_chi_gL(mf, gL, mh, mw, GF);
        if (i == j) {
          gamma *= 0.5;
        }
        return gamma;
      }

      double gamma_h_chi_pm(int i,
        int j,
        std::array<double, 2> m,
        std::array<std::array<double, 2>, 2> U,
        std::array<std::array<double, 2>, 2> V,
        double alpha,
        double mh = 125.,
        double mw = 80.385,
        double GF = 1.1663787e-5) {
        /**
           @brief Lightest Higgs boson decay to charginos at tree-level in GeV

           @warning Arguments \f$i\f$ and \f$j\f$ are zero-based
           @warning Tree-level formula

           @returns \f$\Gamma(h \to \chi^-_i \chi^+_j)\f$ in GeV
           @param i Negative chargino \f$\chi^-_i\f$ in final state
           @param j Positive chargino \f$\chi^+_j\f$ in final state
           @param m Chargino masses
           @param U Real chargino mixing matrix
           @param V Real chargino mixing matrix
           @param alpha \f$\alpha\f$, Higgs mixing angle
           @param mh Lightest Higgs mass, \f$m_h\f$
           @param mw W-boson mass, \f$M_W\f$
           @param GF Fermi constant, \f$G_F\f$
        */
        // Eq. 1.113
        const double e2 = -std::sin(alpha);
        const double d2 = -std::cos(alpha);

        // Eq. 1.111 (without \f$\sin\theta_W\f$ which cancels)
        const double gL = M_SQRT1_2 *
          (e2 * V[j][0] * U[i][1] - d2 * V[j][1] * U[i][0]);

        std::array<double, 2> mf{{m[i], m[j]}};
        return gamma_h_chi_gL(mf, gL, mh, mw, GF);
      }

      double gamma_h_chi(std::array<double, 2> m_pm,
        std::array<double, 4> m_0,
        std::array<std::array<double, 2>, 2> U,
        std::array<std::array<double, 2>, 2> V,
        std::array<std::array<double, 4>, 4> Z,
        double alpha,
        double mh = 125.,
        double mw = 80.385,
        double GF = 1.1663787e-5,
        double sw2 = 0.22) {
        /**
           @brief Lightest Higgs boson decay to neutralinos and charginos at
           tree-level in GeV

           @warning Tree-level formula

           @returns \f$\Gamma(h \to \chi\chi)\f$ in GeV
           @param m_pm Chargino masses
           @param m_0 Neutralino mases with phases
           @param U Real chargino mixing matrix
           @param V Real chargino mixing matrix
           @param Z Real neutralino mixing matrix
           @param alpha \f$\alpha\f$, Higgs mixing angle
           @param mh Lightest Higgs mass, \f$m_h\f$
           @param mw W-boson mass, \f$M_W\f$
           @param GF Fermi constant, \f$G_F\f$
           @param sw2 Weinberg angle, \f$\sin^2\theta_W\f$
        */
          double gamma = 0.;

          for (int i = 0; i <= 3; i += 1) {
            // Do not double count e.g. 12 and 21 - they are not distinct
            for (int j = i; j <= 3; j += 1) {
              gamma += MSSM_H::gamma_h_chi_0(i, j, m_0, Z, alpha, mh, mw, GF, sw2);
            }
          }

          for (int i = 0; i <= 1; i += 1) {
            // Do count e.g. 12 and 21 - they are distinct
            for (int j = 0; j <= 1; j += 1) {
              gamma += MSSM_H::gamma_h_chi_pm(i, j, m_pm, U, V, alpha, mh, mw, GF);
            }
          }

          return gamma;
        }

    }  // namespace MSSM_H
  }  // namespace DecayBit
}  // namespace Gambit

#endif  //  DECAYBIT_INCLUDE_GAMBIT_DECAYBIT_MSSM_H_HPP_
