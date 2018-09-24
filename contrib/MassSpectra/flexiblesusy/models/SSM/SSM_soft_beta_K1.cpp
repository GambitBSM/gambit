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

// File generated at Thu 10 May 2018 14:43:18

#include "SSM_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of K1.
 *
 * @return 1-loop beta function
 */
double SSM_soft_parameters::calc_beta_K1_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_K1;

   beta_K1 = Re(oneOver16PiSqr*(4*K1*K2 + 6*K1*traceYdAdjYd + 2*K1*
      traceYeAdjYe + 6*K1*traceYuAdjYu + 2*K2*Kappa + 6*K1*Lambdax - 0.9*K1*Sqr
      (g1) - 4.5*K1*Sqr(g2)));


   return beta_K1;
}

/**
 * Calculates the 2-loop beta function of K1.
 *
 * @return 2-loop beta function
 */
double SSM_soft_parameters::calc_beta_K1_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_K1;

   beta_K1 = Re(0.0025*twoLoop*(1671*K1*Quad(g1) + 10*K1*Sqr(g1)*(24*K2 +
      50*traceYdAdjYd + 150*traceYeAdjYe + 170*traceYuAdjYu + 288*Lambdax + 45
      *Sqr(g2)) - 25*(128*K2*(K2 + 3*LambdaS)*Kappa + 145*K1*Quad(g2) - 12*K1*(
      4*K2 + 15*traceYdAdjYd + 5*traceYeAdjYe + 15*traceYuAdjYu + 48*Lambdax)*
      Sqr(g2) + 8*K1*(27*traceYdAdjYdYdAdjYd + 42*traceYdAdjYuYuAdjYd + 9*
      traceYeAdjYeYeAdjYe + 27*traceYuAdjYuYuAdjYu + 72*traceYdAdjYd*Lambdax +
      24*traceYeAdjYe*Lambdax + 72*traceYuAdjYu*Lambdax + 8*K2*(6*LambdaS + 3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu + 9*Lambdax) - 80*
      traceYdAdjYd*Sqr(g3) - 80*traceYuAdjYu*Sqr(g3) + 23*Sqr(K2) - 24*Sqr(
      LambdaS) + 30*Sqr(Lambdax)))));


   return beta_K1;
}

/**
 * Calculates the 3-loop beta function of K1.
 *
 * @return 3-loop beta function
 */
double SSM_soft_parameters::calc_beta_K1_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_K1;

   beta_K1 = 0;


   return beta_K1;
}

} // namespace flexiblesusy
