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

// File generated at Tue 31 Jul 2018 21:11:41

#include "THDM_II_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda2.
 *
 * @return 1-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(0.25*oneOver16PiSqr*(3*Quad(g1) + 9*Quad(g2) - 36*
      Lambda2*Sqr(g2) + 6*Sqr(g1)*(-2*Lambda2 + Sqr(g2)) + 8*(2*Lambda3*Lambda4
      - 6*traceYdAdjYdYdAdjYd - 2*traceYeAdjYeYeAdjYe + 2*Lambda2*(3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) - 6*traceYuAdjYuYuAdjYu + 6
      *Sqr(Lambda2) + 2*Sqr(Lambda3) + Sqr(Lambda4) + Sqr(Lambda5) + 12*Sqr(
      Lambda7))));


   return beta_Lambda2;
}

/**
 * Calculates the 2-loop beta function of Lambda2.
 *
 * @return 2-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYdYdAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYeYeAdjYe =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYuYuAdjYu =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(twoLoop*(-20*Lambda2*Lambda3*Lambda4 - 72*Lambda3*
      Lambda6*Lambda7 - 56*Lambda4*Lambda6*Lambda7 - 40*Lambda5*Lambda6*Lambda7
      - 3*Lambda2*traceYdAdjYdYdAdjYd + 60*traceYdAdjYdYdAdjYdYdAdjYd - 24*
      traceYdAdjYdYdAdjYuYuAdjYd - 42*Lambda2*traceYdAdjYuYuAdjYd + 12*
      traceYdAdjYuYuAdjYdYdAdjYd - 12*traceYdAdjYuYuAdjYuYuAdjYd - Lambda2*
      traceYeAdjYeYeAdjYe + 20*traceYeAdjYeYeAdjYeYeAdjYe - 3*Lambda2*
      traceYuAdjYuYuAdjYu + 60*traceYuAdjYuYuAdjYuYuAdjYu - 78*Cube(Lambda2) -
      16*Cube(Lambda3) - 12*Cube(Lambda4) - 16.375*Power6(g1) + 36.375*Power6(
      g2) - 0.375*(17*Lambda2 + 4*(-10*Lambda3 - 5*Lambda4 + 3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu))*Quad(g2) - 0.125*Quad(g1)*(-217*Lambda2 -
      40*Lambda3 - 20*Lambda4 - 20*traceYdAdjYd + 100*traceYeAdjYe + 76*
      traceYuAdjYu + 191*Sqr(g2)) + 80*Lambda2*traceYdAdjYd*Sqr(g3) - 64*
      traceYdAdjYdYdAdjYd*Sqr(g3) + 80*Lambda2*traceYuAdjYu*Sqr(g3) - 64*
      traceYuAdjYuYuAdjYu*Sqr(g3) - 72*traceYdAdjYd*Sqr(Lambda2) - 24*
      traceYeAdjYe*Sqr(Lambda2) - 72*traceYuAdjYu*Sqr(Lambda2) - 20*Lambda2*Sqr
      (Lambda3) - 24*Lambda4*Sqr(Lambda3) - 12*Lambda2*Sqr(Lambda4) - 32*
      Lambda3*Sqr(Lambda4) - 14*Lambda2*Sqr(Lambda5) - 40*Lambda3*Sqr(Lambda5)
      - 44*Lambda4*Sqr(Lambda5) + 6*Lambda2*Sqr(Lambda6) - 36*Lambda3*Sqr(
      Lambda6) - 28*Lambda4*Sqr(Lambda6) - 20*Lambda5*Sqr(Lambda6) - 318*
      Lambda2*Sqr(Lambda7) - 132*Lambda3*Sqr(Lambda7) - 140*Lambda4*Sqr(Lambda7
      ) - 148*Lambda5*Sqr(Lambda7) - 72*traceYdAdjYd*Sqr(Lambda7) - 24*
      traceYeAdjYe*Sqr(Lambda7) - 72*traceYuAdjYu*Sqr(Lambda7) + 1.5*Sqr(g2)*(5
      *Lambda2*(3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) + 36*Sqr(
      Lambda2) + 4*(4*Lambda3*Lambda4 + 4*Sqr(Lambda3) + Sqr(Lambda4) + 18*Sqr(
      Lambda7))) - 0.041666666666666664*Sqr(g1)*(303*Quad(g2) - 6*(39*Lambda2 +
      20*Lambda4 - 36*traceYdAdjYd - 44*traceYeAdjYe - 84*traceYuAdjYu)*Sqr(g2
      ) - 4*(5*Lambda2*(5*traceYdAdjYd + 15*traceYeAdjYe + 17*traceYuAdjYu) +
      108*Sqr(Lambda2) + 4*(12*Lambda3*Lambda4 + 4*traceYdAdjYdYdAdjYd - 12*
      traceYeAdjYeYeAdjYe - 8*traceYuAdjYuYuAdjYu + 12*Sqr(Lambda3) + 6*Sqr(
      Lambda4) - 3*Sqr(Lambda5) + 54*Sqr(Lambda7))))));


   return beta_Lambda2;
}

/**
 * Calculates the 3-loop beta function of Lambda2.
 *
 * @return 3-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda2;

   beta_Lambda2 = 0;


   return beta_Lambda2;
}

} // namespace flexiblesusy
