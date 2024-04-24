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

// File generated at Tue 7 Apr 2020 14:54:57

#include "THDM_flipped_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of v2.
 *
 * @return 1-loop beta function
 */
double THDM_flipped_soft_parameters::calc_beta_v2_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_v2;

   beta_v2 = Re(oneOver16PiSqr*v2*(-traceYeAdjYe - 3*traceYuAdjYu + Sqr(
      g1) + 3*Sqr(g2)));


   return beta_v2;
}

/**
 * Calculates the 2-loop beta function of v2.
 *
 * @return 2-loop beta function
 */
double THDM_flipped_soft_parameters::calc_beta_v2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_v2;

   beta_v2 = Re(0.010416666666666666*twoLoop*(-72*Lambda1*Lambda6*v1 - 72
      *Lambda3*Lambda6*v1 - 72*Lambda4*Lambda6*v1 - 72*Lambda5*Lambda6*v1 - 72*
      Lambda2*Lambda7*v1 - 72*Lambda3*Lambda7*v1 - 72*Lambda4*Lambda7*v1 - 72*
      Lambda5*Lambda7*v1 - 96*Lambda3*Lambda4*v2 + 216*traceYdAdjYuYuAdjYd*v2 +
      216*traceYeAdjYeYeAdjYe*v2 + 648*traceYuAdjYuYuAdjYu*v2 - 432*v2*AbsSqr(
      Lambda7) - 72*(Lambda1*v1 + Lambda3*v1 + Lambda4*v1 + 2*Lambda6*v2)*Conj(
      Lambda6) - 72*Lambda2*v1*Conj(Lambda7) - 72*Lambda3*v1*Conj(Lambda7) - 72
      *Lambda4*v1*Conj(Lambda7) - 72*Conj(Lambda5)*(2*Lambda5*v2 + v1*Conj(
      Lambda6) + v1*Conj(Lambda7)) - 429*v2*Quad(g1) + 1071*v2*Quad(g2) - 348*
      traceYeAdjYe*v2*Sqr(g1) - 484*traceYuAdjYu*v2*Sqr(g1) - 324*traceYeAdjYe*
      v2*Sqr(g2) - 972*traceYuAdjYu*v2*Sqr(g2) + 90*v2*Sqr(g1)*Sqr(g2) - 1920*
      traceYuAdjYu*v2*Sqr(g3) - 144*v2*Sqr(Lambda2) - 96*v2*Sqr(Lambda3) - 96*
      v2*Sqr(Lambda4)));


   return beta_v2;
}

/**
 * Calculates the 3-loop beta function of v2.
 *
 * @return 3-loop beta function
 */
double THDM_flipped_soft_parameters::calc_beta_v2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_v2;

   beta_v2 = 0;


   return beta_v2;
}

} // namespace flexiblesusy
