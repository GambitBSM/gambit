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

   beta_M122 = Re(oneOver16PiSqr*(2*Lambda3*M122 + 4*Lambda4*M122 + 3*
      M122*traceYdAdjYd + M122*traceYeAdjYe + 3*M122*traceYuAdjYu - 6*M112*Conj
      (Lambda6) - 6*M222*Conj(Lambda7) + 6*Conj(Lambda5)*Conj(M122) - 1.5*M122*
      Sqr(g1) - 4.5*M122*Sqr(g2)));


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

   beta_M122 = Re(twoLoop*(-6*Lambda1*Lambda3*M122 - 6*Lambda2*Lambda3*
      M122 - 6*Lambda1*Lambda4*M122 - 6*Lambda2*Lambda4*M122 - 6*Lambda3*
      Lambda4*M122 - 6*Lambda3*M122*traceYdAdjYd - 12*Lambda4*M122*traceYdAdjYd
      - 6.75*M122*traceYdAdjYdYdAdjYd + 1.5*M122*traceYdAdjYuYuAdjYd - 2*
      Lambda3*M122*traceYeAdjYe - 4*Lambda4*M122*traceYeAdjYe - 2.25*M122*
      traceYeAdjYeYeAdjYe - 6*Lambda3*M122*traceYuAdjYu - 12*Lambda4*M122*
      traceYuAdjYu - 6.75*M122*traceYuAdjYuYuAdjYu - 1.5*Lambda2*M112*Conj(
      Lambda7) + 4.5*Lambda3*M112*Conj(Lambda7) + 4.5*Lambda4*M112*Conj(Lambda7
      ) - 12*Lambda6*M122*Conj(Lambda7) + 16.5*Lambda2*M222*Conj(Lambda7) +
      10.5*Lambda3*M222*Conj(Lambda7) + 10.5*Lambda4*M222*Conj(Lambda7) + 36*
      M222*traceYdAdjYd*Conj(Lambda7) + 12*M222*traceYeAdjYe*Conj(Lambda7) + 36
      *M222*traceYuAdjYu*Conj(Lambda7) + 9.5625*M122*Quad(g1) - 15.1875*M122*
      Quad(g2) + 4*Lambda3*M122*Sqr(g1) + 8*Lambda4*M122*Sqr(g1) +
      1.0416666666666667*M122*traceYdAdjYd*Sqr(g1) + 3.125*M122*traceYeAdjYe*
      Sqr(g1) + 3.5416666666666665*M122*traceYuAdjYu*Sqr(g1) - 12*M222*Conj(
      Lambda7)*Sqr(g1) + 12*Lambda3*M122*Sqr(g2) + 24*Lambda4*M122*Sqr(g2) +
      5.625*M122*traceYdAdjYd*Sqr(g2) + 1.875*M122*traceYeAdjYe*Sqr(g2) + 5.625
      *M122*traceYuAdjYu*Sqr(g2) - 36*M222*Conj(Lambda7)*Sqr(g2) + 1.875*M122*
      Sqr(g1)*Sqr(g2) - 1.5*Conj(Lambda6)*(-11*Lambda1*M112 - 7*Lambda3*M112 -
      7*Lambda4*M112 + 8*Lambda7*M122 + Lambda1*M222 - 3*Lambda3*M222 - 3*
      Lambda4*M222 + 8*Conj(Lambda7)*Conj(M122) + 8*M112*Sqr(g1) + 24*M112*Sqr(
      g2)) + 1.5*Conj(Lambda5)*(7*Lambda6*M112 + 3*Lambda7*M112 + 2*Lambda5*
      M122 + 3*Lambda6*M222 + 7*Lambda7*M222 + 4*Conj(M122)*(-Lambda1 - Lambda2
      - 2*Lambda3 - 2*Lambda4 - 3*traceYdAdjYd - traceYeAdjYe - 3*traceYuAdjYu
      + 2*Sqr(g1) + 6*Sqr(g2))) + 20*M122*traceYdAdjYd*Sqr(g3) + 20*M122*
      traceYuAdjYu*Sqr(g3) + 1.5*M122*Sqr(Lambda1) + 1.5*M122*Sqr(Lambda2) - 12
      *Conj(M122)*Sqr(Conj(Lambda6)) - 12*Conj(M122)*Sqr(Conj(Lambda7))));


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
