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

// File generated at Wed 29 Mar 2017 15:35:47

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Ye.
 *
 * @return one-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Ye_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (0.25*oneOver16PiSqr*(Ye*(12*traceYdAdjYd + 4*traceYeAdjYe -
      15*Sqr(g1) - 9*Sqr(g2)) + 6*(Ye*Ye.adjoint()*Ye))).real();


   return beta_Ye;
}

/**
 * Calculates the two-loop beta function of Ye.
 *
 * @return two-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Ye_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (0.020833333333333332*twoLoop*(2*Ye*(5*traceYdAdjYd*(5*Sqr(
      g1) + 27*Sqr(g2) + 96*Sqr(g3)) + 3*(161*Power(g1,4) - 42*Power(g2,4) + 8*
      Lambda3*Lambda4 - 54*traceYdAdjYdYdAdjYd - 18*traceYdAdjYuYuAdjYd - 18*
      traceYeAdjYeYeAdjYe + 18*Sqr(g1)*Sqr(g2) + 5*traceYeAdjYe*(5*Sqr(g1) + 3*
      Sqr(g2)) + 12*Sqr(Lambda1) + 8*Sqr(Lambda3) + 8*Sqr(Lambda4) + 12*Sqr(
      Lambda5) + 36*Sqr(Lambda6) + 12*Sqr(Lambda7))) + 9*((-32*Lambda1 - 36*
      traceYdAdjYd - 12*traceYeAdjYe + 43*Sqr(g1) + 45*Sqr(g2))*(Ye*Ye.adjoint(
      )*Ye) + 8*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye)))).real();


   return beta_Ye;
}

/**
 * Calculates the three-loop beta function of Ye.
 *
 * @return three-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Ye_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = ZEROMATRIX(3,3);


   return beta_Ye;
}

} // namespace flexiblesusy
