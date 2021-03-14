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

// File generated at Tue 7 Apr 2020 02:32:00

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
 * Calculates the 1-loop beta function of M122.
 *
 * @return 1-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M122_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_M122;

   beta_M122 = Re(oneOver16PiSqr*(-6*Lambda6*M112 + 2*Lambda3*M122 + 4*
      Lambda4*M122 - 6*Lambda7*M222 + 3*M122*traceYdAdjYd + M122*traceYeAdjYe +
      3*M122*traceYuAdjYu + 6*Conj(Lambda5)*Conj(M122) - 1.5*M122*Sqr(g1) -
      4.5*M122*Sqr(g2)));


   return beta_M122;
}

/**
 * Calculates the 2-loop beta function of M122.
 *
 * @return 2-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M122_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_M122;

   beta_M122 = Re(twoLoop*(18*Lambda1*Lambda6*M112 + 12*Lambda3*Lambda6*
      M112 + 12*Lambda4*Lambda6*M112 + 6*Lambda3*Lambda7*M112 + 6*Lambda4*
      Lambda7*M112 - 6*Lambda1*Lambda3*M122 - 6*Lambda2*Lambda3*M122 - 6*
      Lambda1*Lambda4*M122 - 6*Lambda2*Lambda4*M122 - 6*Lambda3*Lambda4*M122 +
      6*Lambda3*Lambda6*M222 + 6*Lambda4*Lambda6*M222 + 18*Lambda2*Lambda7*M222
      + 12*Lambda3*Lambda7*M222 + 12*Lambda4*Lambda7*M222 - 6*Lambda3*M122*
      traceYdAdjYd - 12*Lambda4*M122*traceYdAdjYd + 36*Lambda7*M222*
      traceYdAdjYd - 6.75*M122*traceYdAdjYdYdAdjYd + 1.5*M122*
      traceYdAdjYuYuAdjYd - 2*Lambda3*M122*traceYeAdjYe - 4*Lambda4*M122*
      traceYeAdjYe + 12*Lambda7*M222*traceYeAdjYe - 2.25*M122*
      traceYeAdjYeYeAdjYe - 6*Lambda3*M122*traceYuAdjYu - 12*Lambda4*M122*
      traceYuAdjYu + 36*Lambda7*M222*traceYuAdjYu - 6.75*M122*
      traceYuAdjYuYuAdjYu - 12*Lambda7*M122*Conj(Lambda6) - 12*Lambda6*M122*
      Conj(Lambda7) - 12*Lambda6*Lambda7*Conj(M122) + 9.5625*M122*Quad(g1) -
      15.1875*M122*Quad(g2) - 12*Lambda6*M112*Sqr(g1) + 4*Lambda3*M122*Sqr(g1)
      + 8*Lambda4*M122*Sqr(g1) - 12*Lambda7*M222*Sqr(g1) + 1.0416666666666667*
      M122*traceYdAdjYd*Sqr(g1) + 3.125*M122*traceYeAdjYe*Sqr(g1) +
      3.5416666666666665*M122*traceYuAdjYu*Sqr(g1) - 36*Lambda6*M112*Sqr(g2) +
      12*Lambda3*M122*Sqr(g2) + 24*Lambda4*M122*Sqr(g2) - 36*Lambda7*M222*Sqr(
      g2) + 5.625*M122*traceYdAdjYd*Sqr(g2) + 1.875*M122*traceYeAdjYe*Sqr(g2) +
      5.625*M122*traceYuAdjYu*Sqr(g2) + 1.875*M122*Sqr(g1)*Sqr(g2) + 3*Conj(
      Lambda5)*(Lambda5*M122 + 2*(2*M112 + M222)*Conj(Lambda6) + 2*(M112 + 2*
      M222)*Conj(Lambda7) - 2*Lambda1*Conj(M122) - 2*Lambda2*Conj(M122) - 4*
      Lambda3*Conj(M122) - 4*Lambda4*Conj(M122) - 6*traceYdAdjYd*Conj(M122) - 2
      *traceYeAdjYe*Conj(M122) - 6*traceYuAdjYu*Conj(M122) + 4*Conj(M122)*Sqr(
      g1) + 12*Conj(M122)*Sqr(g2)) + 20*M122*traceYdAdjYd*Sqr(g3) + 20*M122*
      traceYuAdjYu*Sqr(g3) + 1.5*M122*Sqr(Lambda1) + 1.5*M122*Sqr(Lambda2) - 12
      *Conj(M122)*Sqr(Lambda6) - 12*Conj(M122)*Sqr(Lambda7)));


   return beta_M122;
}

/**
 * Calculates the 3-loop beta function of M122.
 *
 * @return 3-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M122_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_M122;

   beta_M122 = 0;


   return beta_M122;
}

} // namespace flexiblesusy
