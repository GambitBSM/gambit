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

// File generated at Thu 10 May 2018 14:43:17

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
 * Calculates the 1-loop beta function of Kappa.
 *
 * @return 1-loop beta function
 */
double SSM_soft_parameters::calc_beta_Kappa_1_loop(const Soft_traces& soft_traces) const
{


   double beta_Kappa;

   beta_Kappa = Re(6*oneOver16PiSqr*(K1*K2 + 6*LambdaS*Kappa));


   return beta_Kappa;
}

/**
 * Calculates the 2-loop beta function of Kappa.
 *
 * @return 2-loop beta function
 */
double SSM_soft_parameters::calc_beta_Kappa_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Kappa;

   beta_Kappa = Re(twoLoop*(-72*K1*K2*LambdaS - 36*K1*K2*traceYdAdjYd -
      12*K1*K2*traceYeAdjYe - 36*K1*K2*traceYuAdjYu + 7.2*K1*K2*Sqr(g1) + 36*K1
      *K2*Sqr(g2) - 24*K1*Sqr(K2) - 9*Kappa*Sqr(K2) - 828*Kappa*Sqr(LambdaS)));


   return beta_Kappa;
}

/**
 * Calculates the 3-loop beta function of Kappa.
 *
 * @return 3-loop beta function
 */
double SSM_soft_parameters::calc_beta_Kappa_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Kappa;

   beta_Kappa = 0;


   return beta_Kappa;
}

} // namespace flexiblesusy
