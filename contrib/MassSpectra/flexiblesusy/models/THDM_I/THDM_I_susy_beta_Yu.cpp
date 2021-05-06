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
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(Yu*(3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu - 1.4166666666666667*Sqr(g1) - 2.25*Sqr(g2) - 8*Sqr(g3)) -
      1.5*(Yu*Yd.adjoint()*Yd) + 1.5*(Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(Yu*(Lambda3*Lambda4 - 6.75*traceYdAdjYdYdAdjYd +
      1.5*traceYdAdjYuYuAdjYd - 2.25*traceYeAdjYeYeAdjYe - 6.75*
      traceYuAdjYuYuAdjYu + 1.5*AbsSqr(Lambda5) + 1.5*AbsSqr(Lambda6) + 4.5*
      AbsSqr(Lambda7) + 5.8657407407407405*Quad(g1) - 5.25*Quad(g2) - 108*Quad(
      g3) + 1.0416666666666667*traceYdAdjYd*Sqr(g1) + 3.125*traceYeAdjYe*Sqr(g1
      ) + 3.5416666666666665*traceYuAdjYu*Sqr(g1) + 5.625*traceYdAdjYd*Sqr(g2)
      + 1.875*traceYeAdjYe*Sqr(g2) + 5.625*traceYuAdjYu*Sqr(g2) - 0.75*Sqr(g1)*
      Sqr(g2) + 20*traceYdAdjYd*Sqr(g3) + 20*traceYuAdjYu*Sqr(g3) +
      2.111111111111111*Sqr(g1)*Sqr(g3) + 9*Sqr(g2)*Sqr(g3) + 1.5*Sqr(Lambda2)
      + Sqr(Lambda3) + Sqr(Lambda4)) + 0.020833333333333332*(-43*Sqr(g1) + 3*(
      60*traceYdAdjYd + 20*traceYeAdjYe + 60*traceYuAdjYu + 9*Sqr(g2) - 256*Sqr
      (g3)))*(Yu*Yd.adjoint()*Yd) + 0.020833333333333332*(-36*(8*Lambda2 + 9*
      traceYdAdjYd + 3*traceYeAdjYe + 9*traceYuAdjYu) + 223*Sqr(g1) + 405*Sqr(
      g2) + 768*Sqr(g3))*(Yu*Yu.adjoint()*Yu) + 2.75*(Yu*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd) - 0.25*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) - Yu*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd + 1.5*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu
      ))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_I_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

} // namespace flexiblesusy
