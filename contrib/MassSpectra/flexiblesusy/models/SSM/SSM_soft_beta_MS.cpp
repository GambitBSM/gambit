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
 * Calculates the 1-loop beta function of MS.
 *
 * @return 1-loop beta function
 */
double SSM_soft_parameters::calc_beta_MS_1_loop(const Soft_traces& soft_traces) const
{


   double beta_MS;

   beta_MS = Re(4*oneOver16PiSqr*(3*LambdaS*MS + K2*mu2 + Sqr(K1) + Sqr(
      Kappa)));


   return beta_MS;
}

/**
 * Calculates the 2-loop beta function of MS.
 *
 * @return 2-loop beta function
 */
double SSM_soft_parameters::calc_beta_MS_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_MS;

   beta_MS = Re(twoLoop*(4.8*Sqr(g1)*(K2*mu2 + Sqr(K1)) - 2*(12*K2*mu2*
      traceYdAdjYd + 4*K2*mu2*traceYeAdjYe + 12*K2*mu2*traceYuAdjYu + 8*K1*K2*
      Kappa + 2*(5*K2 + 6*LambdaS + 6*traceYdAdjYd + 2*traceYeAdjYe + 6*
      traceYuAdjYu)*Sqr(K1) - 12*Sqr(g2)*(K2*mu2 + Sqr(K1)) + MS*Sqr(K2) + 4*
      mu2*Sqr(K2) + 60*MS*Sqr(LambdaS) + 60*LambdaS*Sqr(Kappa))));


   return beta_MS;
}

/**
 * Calculates the 3-loop beta function of MS.
 *
 * @return 3-loop beta function
 */
double SSM_soft_parameters::calc_beta_MS_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_MS;

   beta_MS = 0;


   return beta_MS;
}

} // namespace flexiblesusy
