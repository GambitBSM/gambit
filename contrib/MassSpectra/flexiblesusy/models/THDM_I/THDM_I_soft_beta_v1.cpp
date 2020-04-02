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
 * Calculates the 1-loop beta function of v1.
 *
 * @return 1-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_v1_1_loop(const Soft_traces& soft_traces) const
{


   double beta_v1;

   beta_v1 = Re(oneOver16PiSqr*v1*(Sqr(g1) + 3*Sqr(g2)));


   return beta_v1;
}

/**
 * Calculates the 2-loop beta function of v1.
 *
 * @return 2-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_v1_2_loop(const Soft_traces& soft_traces) const
{


   double beta_v1;

   beta_v1 = Re(0.03125*twoLoop*(-32*Lambda3*Lambda4*v1 - 24*Lambda1*
      Lambda6*v2 - 24*Lambda3*Lambda6*v2 - 24*Lambda4*Lambda6*v2 - 24*Lambda2*
      Lambda7*v2 - 24*Lambda3*Lambda7*v2 - 24*Lambda4*Lambda7*v2 - 48*v1*AbsSqr
      (Lambda7) - 24*(2*Lambda5*v1 + (Lambda6 + Lambda7)*v2)*Conj(Lambda5) - 24
      *(6*Lambda6*v1 + (Lambda1 + Lambda3 + Lambda4 + Lambda5)*v2)*Conj(Lambda6
      ) - 24*Lambda2*v2*Conj(Lambda7) - 24*Lambda3*v2*Conj(Lambda7) - 24*
      Lambda4*v2*Conj(Lambda7) - 24*Lambda5*v2*Conj(Lambda7) - 143*v1*Quad(g1)
      + 357*v1*Quad(g2) + 30*v1*Sqr(g1)*Sqr(g2) - 48*v1*Sqr(Lambda1) - 32*v1*
      Sqr(Lambda3) - 32*v1*Sqr(Lambda4)));


   return beta_v1;
}

/**
 * Calculates the 3-loop beta function of v1.
 *
 * @return 3-loop beta function
 */
double THDM_I_soft_parameters::calc_beta_v1_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_v1;

   beta_v1 = 0;


   return beta_v1;
}

} // namespace flexiblesusy
