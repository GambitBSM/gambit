// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Wed 1 Apr 2020 20:45:24

#include "THDM_I_soft_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT soft_traces

namespace {

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(double n, const Eigen::MatrixBase<Derived>& m)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m - Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(double n, const Eigen::MatrixBase<Derived>& m)
{
   return - m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

} // anonymous namespace

/**
 * Calculates the 1-loop beta function of M112.
 *
 * @return 1-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M112_1_loop(const Soft_traces& soft_traces) const
{


   double beta_M112;

   beta_M112 = Re(oneOver16PiSqr*(6*Lambda1*M112 - 6*Lambda6*M122 + 4*
      Lambda3*M222 + 2*Lambda4*M222 - 6*Conj(Lambda6)*Conj(M122) - 1.5*M112*Sqr
      (g1) - 4.5*M112*Sqr(g2)));


   return beta_M112;
}

/**
 * Calculates the 2-loop beta function of M112.
 *
 * @return 2-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M112_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_M112;

   beta_M112 = Re(twoLoop*(-2*Lambda3*Lambda4*M112 + 16.5*Lambda1*Lambda6
      *M122 + 10.5*Lambda3*Lambda6*M122 + 10.5*Lambda4*Lambda6*M122 - 1.5*
      Lambda2*Lambda7*M122 + 4.5*Lambda3*Lambda7*M122 + 4.5*Lambda4*Lambda7*
      M122 - 8*Lambda3*Lambda4*M222 + 18*Lambda6*M122*traceYdAdjYd - 24*Lambda3
      *M222*traceYdAdjYd - 12*Lambda4*M222*traceYdAdjYd + 6*Lambda6*M122*
      traceYeAdjYe - 8*Lambda3*M222*traceYeAdjYe - 4*Lambda4*M222*traceYeAdjYe
      + 18*Lambda6*M122*traceYuAdjYu - 24*Lambda3*M222*traceYuAdjYu - 12*
      Lambda4*M222*traceYuAdjYu + 3*M112*AbsSqr(Lambda7) - 18*M222*AbsSqr(
      Lambda7) + 4.5*Lambda5*M122*Conj(Lambda7) - 1.5*Lambda2*Conj(Lambda7)*
      Conj(M122) + 4.5*Lambda3*Conj(Lambda7)*Conj(M122) + 4.5*Lambda4*Conj(
      Lambda7)*Conj(M122) + 1.5*Conj(Lambda5)*(-2*Lambda5*(M112 + 4*M222) + (7*
      Lambda6 + 3*Lambda7)*Conj(M122)) + 12.0625*M112*Quad(g1) + 2.5*M222*Quad(
      g1) - 7.6875*M112*Quad(g2) + 7.5*M222*Quad(g2) + 12*Lambda1*M112*Sqr(g1)
      - 12*Lambda6*M122*Sqr(g1) + 8*Lambda3*M222*Sqr(g1) + 4*Lambda4*M222*Sqr(
      g1) + 1.5*Conj(Lambda6)*(7*Lambda5*M122 - 6*Lambda6*(3*M112 + 2*M222) +
      Conj(M122)*(11*Lambda1 + 7*Lambda3 + 7*Lambda4 + 12*traceYdAdjYd + 4*
      traceYeAdjYe + 12*traceYuAdjYu - 8*Sqr(g1) - 24*Sqr(g2))) + 36*Lambda1*
      M112*Sqr(g2) - 36*Lambda6*M122*Sqr(g2) + 24*Lambda3*M222*Sqr(g2) + 12*
      Lambda4*M222*Sqr(g2) + 1.875*M112*Sqr(g1)*Sqr(g2) - 15*M112*Sqr(Lambda1)
      - 2*M112*Sqr(Lambda3) - 8*M222*Sqr(Lambda3) - 2*M112*Sqr(Lambda4) - 8*
      M222*Sqr(Lambda4)));


   return beta_M112;
}

/**
 * Calculates the 3-loop beta function of M112.
 *
 * @return 3-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M112_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_M112;

   beta_M112 = 0;


   return beta_M112;
}

} // namespace flexiblesusy
