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

// File generated at Wed 1 Apr 2020 20:45:13

#include "THDM_I_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda7.
 *
 * @return 1-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda7_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda7;

   beta_Lambda7 = Re(oneOver16PiSqr*(6*Lambda3*Lambda6 + 4*Lambda4*
      Lambda6 + 12*Lambda2*Lambda7 + 6*Lambda3*Lambda7 + 8*Lambda4*Lambda7 + 9*
      Lambda7*traceYdAdjYd + 3*Lambda7*traceYeAdjYe + 9*Lambda7*traceYuAdjYu +
      2*Lambda5*Conj(Lambda6) + 10*Lambda5*Conj(Lambda7) - 3*Lambda7*Sqr(g1) -
      9*Lambda7*Sqr(g2)));


   return beta_Lambda7;
}

/**
 * Calculates the 2-loop beta function of Lambda7.
 *
 * @return 2-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda7_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda7;

   beta_Lambda7 = Re(0.125*twoLoop*(12*Lambda1*Lambda2*Lambda6 - 132*
      Lambda1*Lambda3*Lambda6 - 132*Lambda2*Lambda3*Lambda6 - 100*Lambda1*
      Lambda4*Lambda6 - 100*Lambda2*Lambda4*Lambda6 - 424*Lambda3*Lambda4*
      Lambda6 - 144*Lambda1*Lambda3*Lambda7 - 504*Lambda2*Lambda3*Lambda7 - 112
      *Lambda1*Lambda4*Lambda7 - 536*Lambda2*Lambda4*Lambda7 - 520*Lambda3*
      Lambda4*Lambda7 - 576*Lambda2*Lambda7*traceYdAdjYd - 144*Lambda3*Lambda7*
      traceYdAdjYd - 192*Lambda4*Lambda7*traceYdAdjYd - 18*Lambda7*
      traceYdAdjYdYdAdjYd - 156*Lambda7*traceYdAdjYuYuAdjYd - 192*Lambda2*
      Lambda7*traceYeAdjYe - 48*Lambda3*Lambda7*traceYeAdjYe - 64*Lambda4*
      Lambda7*traceYeAdjYe - 6*Lambda7*traceYeAdjYeYeAdjYe - 576*Lambda2*
      Lambda7*traceYuAdjYu - 144*Lambda3*Lambda7*traceYuAdjYu - 192*Lambda4*
      Lambda7*traceYuAdjYu - 114*Lambda7*traceYuAdjYuYuAdjYu - 12*(27*Lambda6 +
      23*Lambda7)*AbsSqr(Lambda5) - 672*Lambda6*AbsSqr(Lambda7) - 80*Lambda1*
      Lambda5*Conj(Lambda7) - 568*Lambda2*Lambda5*Conj(Lambda7) - 552*Lambda3*
      Lambda5*Conj(Lambda7) - 584*Lambda4*Lambda5*Conj(Lambda7) - 240*Lambda5*
      traceYdAdjYd*Conj(Lambda7) - 80*Lambda5*traceYeAdjYe*Conj(Lambda7) - 240*
      Lambda5*traceYuAdjYu*Conj(Lambda7) + 30*Lambda6*Quad(g1) + 187*Lambda7*
      Quad(g1) + 90*Lambda6*Quad(g2) - 141*Lambda7*Quad(g2) + 96*Lambda3*
      Lambda6*Sqr(g1) + 64*Lambda4*Lambda6*Sqr(g1) + 144*Lambda2*Lambda7*Sqr(g1
      ) + 48*Lambda3*Lambda7*Sqr(g1) + 80*Lambda4*Lambda7*Sqr(g1) + 25*Lambda7*
      traceYdAdjYd*Sqr(g1) + 75*Lambda7*traceYeAdjYe*Sqr(g1) + 85*Lambda7*
      traceYuAdjYu*Sqr(g1) + 160*Lambda5*Conj(Lambda7)*Sqr(g1) + 288*Lambda3*
      Lambda6*Sqr(g2) + 144*Lambda4*Lambda6*Sqr(g2) + 432*Lambda2*Lambda7*Sqr(
      g2) + 144*Lambda3*Lambda7*Sqr(g2) + 288*Lambda4*Lambda7*Sqr(g2) + 135*
      Lambda7*traceYdAdjYd*Sqr(g2) + 45*Lambda7*traceYeAdjYe*Sqr(g2) + 135*
      Lambda7*traceYuAdjYu*Sqr(g2) + 432*Lambda5*Conj(Lambda7)*Sqr(g2) + 20*
      Lambda6*Sqr(g1)*Sqr(g2) + 58*Lambda7*Sqr(g1)*Sqr(g2) + 480*Lambda7*
      traceYdAdjYd*Sqr(g3) + 480*Lambda7*traceYuAdjYu*Sqr(g3) + 12*Lambda7*Sqr(
      Lambda1) - 624*Lambda7*Sqr(Lambda2) - 276*Lambda6*Sqr(Lambda3) - 244*
      Lambda7*Sqr(Lambda3) - 260*Lambda6*Sqr(Lambda4) - 260*Lambda7*Sqr(Lambda4
      ) - 176*Conj(Lambda7)*Sqr(Lambda6) - 888*Conj(Lambda7)*Sqr(Lambda7) - 4*
      Conj(Lambda6)*(17*Lambda1*Lambda5 + 17*Lambda2*Lambda5 + 74*Lambda3*
      Lambda5 + 82*Lambda4*Lambda5 + 22*Lambda6*Lambda7 + 4*Lambda5*Sqr(g1) +
      84*Sqr(Lambda6) + 84*Sqr(Lambda7))));


   return beta_Lambda7;
}

/**
 * Calculates the 3-loop beta function of Lambda7.
 *
 * @return 3-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda7_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda7;

   beta_Lambda7 = 0;


   return beta_Lambda7;
}

} // namespace flexiblesusy
