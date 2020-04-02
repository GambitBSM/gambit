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

// File generated at Wed 1 Apr 2020 20:45:25

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
 * Calculates the 1-loop beta function of M222.
 *
 * @return 1-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M222_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_M222;

   beta_M222 = Re(oneOver16PiSqr*(4*Lambda3*M112 + 2*Lambda4*M112 - 6*
      Lambda7*M122 + 6*Lambda2*M222 + 6*M222*traceYdAdjYd + 2*M222*traceYeAdjYe
      + 6*M222*traceYuAdjYu - 6*Conj(Lambda7)*Conj(M122) - 1.5*M222*Sqr(g1) -
      4.5*M222*Sqr(g2)));


   return beta_M222;
}

/**
 * Calculates the 2-loop beta function of M222.
 *
 * @return 2-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M222_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_M222;

   beta_M222 = Re(twoLoop*(-8*Lambda3*Lambda4*M112 - 1.5*Lambda1*Lambda6*
      M122 + 4.5*Lambda3*Lambda6*M122 + 4.5*Lambda4*Lambda6*M122 + 16.5*Lambda2
      *Lambda7*M122 + 10.5*Lambda3*Lambda7*M122 + 10.5*Lambda4*Lambda7*M122 - 2
      *Lambda3*Lambda4*M222 + 18*Lambda7*M122*traceYdAdjYd - 36*Lambda2*M222*
      traceYdAdjYd - 13.5*M222*traceYdAdjYdYdAdjYd - 21*M222*
      traceYdAdjYuYuAdjYd + 6*Lambda7*M122*traceYeAdjYe - 12*Lambda2*M222*
      traceYeAdjYe - 4.5*M222*traceYeAdjYeYeAdjYe + 18*Lambda7*M122*
      traceYuAdjYu - 36*Lambda2*M222*traceYuAdjYu - 13.5*M222*
      traceYuAdjYuYuAdjYu - 18*M112*AbsSqr(Lambda7) - 27*M222*AbsSqr(Lambda7) +
      10.5*Lambda5*M122*Conj(Lambda7) + 16.5*Lambda2*Conj(Lambda7)*Conj(M122)
      + 10.5*Lambda3*Conj(Lambda7)*Conj(M122) + 10.5*Lambda4*Conj(Lambda7)*Conj
      (M122) + 18*traceYdAdjYd*Conj(Lambda7)*Conj(M122) + 6*traceYeAdjYe*Conj(
      Lambda7)*Conj(M122) + 18*traceYuAdjYu*Conj(Lambda7)*Conj(M122) - 1.5*Conj
      (Lambda6)*(12*Lambda6*M112 - 3*Lambda5*M122 - 2*Lambda6*M222 + (Lambda1 -
      3*(Lambda3 + Lambda4))*Conj(M122)) + 1.5*Conj(Lambda5)*(-2*Lambda5*(4*
      M112 + M222) + (3*Lambda6 + 7*Lambda7)*Conj(M122)) + 2.5*M112*Quad(g1) +
      12.0625*M222*Quad(g1) + 7.5*M112*Quad(g2) - 7.6875*M222*Quad(g2) + 8*
      Lambda3*M112*Sqr(g1) + 4*Lambda4*M112*Sqr(g1) - 12*Lambda7*M122*Sqr(g1) +
      12*Lambda2*M222*Sqr(g1) + 2.0833333333333335*M222*traceYdAdjYd*Sqr(g1) +
      6.25*M222*traceYeAdjYe*Sqr(g1) + 7.083333333333333*M222*traceYuAdjYu*Sqr
      (g1) - 12*Conj(Lambda7)*Conj(M122)*Sqr(g1) + 24*Lambda3*M112*Sqr(g2) + 12
      *Lambda4*M112*Sqr(g2) - 36*Lambda7*M122*Sqr(g2) + 36*Lambda2*M222*Sqr(g2)
      + 11.25*M222*traceYdAdjYd*Sqr(g2) + 3.75*M222*traceYeAdjYe*Sqr(g2) +
      11.25*M222*traceYuAdjYu*Sqr(g2) - 36*Conj(Lambda7)*Conj(M122)*Sqr(g2) +
      1.875*M222*Sqr(g1)*Sqr(g2) + 40*M222*traceYdAdjYd*Sqr(g3) + 40*M222*
      traceYuAdjYu*Sqr(g3) - 15*M222*Sqr(Lambda2) - 8*M112*Sqr(Lambda3) - 2*
      M222*Sqr(Lambda3) - 8*M112*Sqr(Lambda4) - 2*M222*Sqr(Lambda4)));


   return beta_M222;
}

/**
 * Calculates the 3-loop beta function of M222.
 *
 * @return 3-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_M222_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_M222;

   beta_M222 = 0;


   return beta_M222;
}

} // namespace flexiblesusy
