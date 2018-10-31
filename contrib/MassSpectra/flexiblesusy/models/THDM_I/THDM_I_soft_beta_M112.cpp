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

// File generated at Wed 31 Oct 2018 19:35:41

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

   beta_M112 = Re(oneOver16PiSqr*(6*Lambda1*M112 - 12*Lambda6*M122 + 4*
      Lambda3*M222 + 2*Lambda4*M222 - 1.5*M112*Sqr(g1) - 4.5*M112*Sqr(g2)));


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

   beta_M112 = Re(twoLoop*(-2*Lambda3*Lambda4*M112 + 36*Lambda1*Lambda6*
      M122 + 24*Lambda3*Lambda6*M122 + 24*Lambda4*Lambda6*M122 + 24*Lambda5*
      Lambda6*M122 + 12*Lambda3*Lambda7*M122 + 12*Lambda4*Lambda7*M122 + 12*
      Lambda5*Lambda7*M122 - 8*Lambda3*Lambda4*M222 + 36*Lambda6*M122*
      traceYdAdjYd - 24*Lambda3*M222*traceYdAdjYd - 12*Lambda4*M222*
      traceYdAdjYd + 12*Lambda6*M122*traceYeAdjYe - 8*Lambda3*M222*traceYeAdjYe
      - 4*Lambda4*M222*traceYeAdjYe + 36*Lambda6*M122*traceYuAdjYu - 24*
      Lambda3*M222*traceYuAdjYu - 12*Lambda4*M222*traceYuAdjYu + 0.0625*(193*
      M112 + 40*M222)*Quad(g1) - 0.1875*(41*M112 - 40*M222)*Quad(g2) + 12*(3*
      Lambda1*M112 - 6*Lambda6*M122 + 2*Lambda3*M222 + Lambda4*M222)*Sqr(g2) +
      Sqr(g1)*(4*(3*Lambda1*M112 - 6*Lambda6*M122 + 2*Lambda3*M222 + Lambda4*
      M222) + 1.875*M112*Sqr(g2)) - 15*M112*Sqr(Lambda1) - 2*M112*Sqr(Lambda3)
      - 8*M222*Sqr(Lambda3) - 2*M112*Sqr(Lambda4) - 8*M222*Sqr(Lambda4) - 3*
      M112*Sqr(Lambda5) - 12*M222*Sqr(Lambda5) - 27*M112*Sqr(Lambda6) - 18*M222
      *Sqr(Lambda6) + 3*M112*Sqr(Lambda7) - 18*M222*Sqr(Lambda7)));


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
