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

// File generated at Tue 7 Apr 2020 14:55:42

#include "THDM_LS_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Ye.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_LS_susy_parameters::calc_beta_Ye_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (oneOver16PiSqr*(-0.25*Ye*(-4*traceYeAdjYe + 15*Sqr(g1) + 9*
      Sqr(g2)) + 1.5*(Ye*Ye.adjoint()*Ye))).real();


   return beta_Ye;
}

/**
 * Calculates the 2-loop beta function of Ye.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_LS_susy_parameters::calc_beta_Ye_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (twoLoop*(0.125*Ye*(8*Lambda3*Lambda4 - 18*
      traceYeAdjYeYeAdjYe + 12*AbsSqr(Lambda5) + 36*AbsSqr(Lambda6) + 12*AbsSqr
      (Lambda7) + 161*Quad(g1) - 42*Quad(g2) + 25*traceYeAdjYe*Sqr(g1) + 15*
      traceYeAdjYe*Sqr(g2) + 18*Sqr(g1)*Sqr(g2) + 12*Sqr(Lambda1) + 8*Sqr(
      Lambda3) + 8*Sqr(Lambda4)) + 0.1875*(-4*(8*Lambda1 + 3*traceYeAdjYe) + 43
      *Sqr(g1) + 45*Sqr(g2))*(Ye*Ye.adjoint()*Ye) + 1.5*(Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye))).real();


   return beta_Ye;
}

/**
 * Calculates the 3-loop beta function of Ye.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_LS_susy_parameters::calc_beta_Ye_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = ZEROMATRIX(3,3);


   return beta_Ye;
}

} // namespace flexiblesusy
