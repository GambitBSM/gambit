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

// File generated at Tue 7 Apr 2020 02:31:58

#include "THDM_I_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Ye.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Ye_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (oneOver16PiSqr*(Ye*(3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu - 3.75*Sqr(g1) - 2.25*Sqr(g2)) + 1.5*(Ye*Ye.adjoint()*Ye)))
      .real();


   return beta_Ye;
}

/**
 * Calculates the 2-loop beta function of Ye.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Ye_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (twoLoop*(0.041666666666666664*Ye*(24*Lambda3*Lambda4 - 162*
      traceYdAdjYdYdAdjYd + 36*traceYdAdjYuYuAdjYd - 54*traceYeAdjYeYeAdjYe -
      162*traceYuAdjYuYuAdjYu + 36*AbsSqr(Lambda5) + 36*AbsSqr(Lambda6) + 108*
      AbsSqr(Lambda7) + 483*Quad(g1) - 126*Quad(g2) + 25*traceYdAdjYd*Sqr(g1) +
      75*traceYeAdjYe*Sqr(g1) + 85*traceYuAdjYu*Sqr(g1) + 135*traceYdAdjYd*Sqr
      (g2) + 45*traceYeAdjYe*Sqr(g2) + 135*traceYuAdjYu*Sqr(g2) + 54*Sqr(g1)*
      Sqr(g2) + 480*traceYdAdjYd*Sqr(g3) + 480*traceYuAdjYu*Sqr(g3) + 36*Sqr(
      Lambda2) + 24*Sqr(Lambda3) + 24*Sqr(Lambda4)) + 0.1875*(-4*(8*Lambda2 + 9
      *traceYdAdjYd + 3*traceYeAdjYe + 9*traceYuAdjYu) + 43*Sqr(g1) + 45*Sqr(g2
      ))*(Ye*Ye.adjoint()*Ye) + 1.5*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye))).real
      ();


   return beta_Ye;
}

/**
 * Calculates the 3-loop beta function of Ye.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Ye_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = ZEROMATRIX(3,3);


   return beta_Ye;
}

} // namespace flexiblesusy
