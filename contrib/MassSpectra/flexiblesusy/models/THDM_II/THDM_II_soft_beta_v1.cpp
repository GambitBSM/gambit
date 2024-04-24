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

// File generated at Thu 2 Aug 2018 15:04:50

#include "THDM_II_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of v1.
 *
 * @return 1-loop beta function
 */
double THDM_II_soft_parameters::calc_beta_v1_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   double beta_v1;

   beta_v1 = Re(oneOver16PiSqr*v1*(-3*traceYdAdjYd - traceYeAdjYe + Sqr(
      g1) + 3*Sqr(g2)));


   return beta_v1;
}

/**
 * Calculates the 2-loop beta function of v1.
 *
 * @return 2-loop beta function
 */
double THDM_II_soft_parameters::calc_beta_v1_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   double beta_v1;

   beta_v1 = Re(0.010416666666666666*twoLoop*(-429*v1*Quad(g1) + 2*v1*Sqr
      (g1)*(-2*(61*traceYdAdjYd + 87*traceYeAdjYe) + 45*Sqr(g2)) + 3*(357*v1*
      Quad(g2) - 108*(3*traceYdAdjYd + traceYeAdjYe)*v1*Sqr(g2) - 8*(4*Lambda3*
      Lambda4*v1 - 27*traceYdAdjYdYdAdjYd*v1 - 9*traceYdAdjYuYuAdjYd*v1 - 9*
      traceYeAdjYeYeAdjYe*v1 + 6*Lambda1*Lambda6*v2 + 6*Lambda3*Lambda6*v2 + 6*
      Lambda4*Lambda6*v2 + 6*Lambda5*Lambda6*v2 + 6*Lambda2*Lambda7*v2 + 6*
      Lambda3*Lambda7*v2 + 6*Lambda4*Lambda7*v2 + 6*Lambda5*Lambda7*v2 + 80*
      traceYdAdjYd*v1*Sqr(g3) + 6*v1*Sqr(Lambda1) + 4*v1*Sqr(Lambda3) + 4*v1*
      Sqr(Lambda4) + 6*v1*Sqr(Lambda5) + 18*v1*Sqr(Lambda6) + 6*v1*Sqr(Lambda7)
      ))));


   return beta_v1;
}

/**
 * Calculates the 3-loop beta function of v1.
 *
 * @return 3-loop beta function
 */
double THDM_II_soft_parameters::calc_beta_v1_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_v1;

   beta_v1 = 0;


   return beta_v1;
}

} // namespace flexiblesusy
