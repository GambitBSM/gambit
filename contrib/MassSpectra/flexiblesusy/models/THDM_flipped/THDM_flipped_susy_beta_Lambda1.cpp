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

// File generated at Wed 31 Oct 2018 21:01:24

#include "THDM_flipped_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda1.
 *
 * @return 1-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;


   double beta_Lambda1;

   beta_Lambda1 = Re(0.25*oneOver16PiSqr*(3*Quad(g1) + 9*Quad(g2) - 36*
      Lambda1*Sqr(g2) + 6*Sqr(g1)*(-2*Lambda1 + Sqr(g2)) + 8*(2*Lambda3*Lambda4
      + 6*Lambda1*traceYdAdjYd - 6*traceYdAdjYdYdAdjYd + 6*Sqr(Lambda1) + 2*
      Sqr(Lambda3) + Sqr(Lambda4) + Sqr(Lambda5) + 12*Sqr(Lambda6))));


   return beta_Lambda1;
}

/**
 * Calculates the 2-loop beta function of Lambda1.
 *
 * @return 2-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;


   double beta_Lambda1;

   beta_Lambda1 = Re(twoLoop*(-20*Lambda1*Lambda3*Lambda4 - 72*Lambda3*
      Lambda6*Lambda7 - 56*Lambda4*Lambda6*Lambda7 - 40*Lambda5*Lambda6*Lambda7
      - 3*Lambda1*traceYdAdjYdYdAdjYd + 60*traceYdAdjYdYdAdjYdYdAdjYd - 9*
      Lambda1*traceYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - 8*Lambda3*
      Lambda4*traceYeAdjYe - 24*Lambda3*Lambda4*traceYuAdjYu - 78*Cube(Lambda1)
      - 16*Cube(Lambda3) - 12*Cube(Lambda4) - 16.375*Power6(g1) + 36.375*
      Power6(g2) - 0.375*(17*Lambda1 - 40*Lambda3 - 20*Lambda4 + 12*
      traceYdAdjYd)*Quad(g2) - 0.125*Quad(g1)*(-217*Lambda1 - 20*(2*Lambda3 +
      Lambda4 + traceYdAdjYd) + 191*Sqr(g2)) + 80*Lambda1*traceYdAdjYd*Sqr(g3)
      - 64*traceYdAdjYdYdAdjYd*Sqr(g3) - 72*traceYdAdjYd*Sqr(Lambda1) - 20*
      Lambda1*Sqr(Lambda3) - 24*Lambda4*Sqr(Lambda3) - 8*traceYeAdjYe*Sqr(
      Lambda3) - 24*traceYuAdjYu*Sqr(Lambda3) - 12*Lambda1*Sqr(Lambda4) - 32*
      Lambda3*Sqr(Lambda4) - 4*traceYeAdjYe*Sqr(Lambda4) - 12*traceYuAdjYu*Sqr(
      Lambda4) - 14*Lambda1*Sqr(Lambda5) - 40*Lambda3*Sqr(Lambda5) - 44*Lambda4
      *Sqr(Lambda5) - 4*traceYeAdjYe*Sqr(Lambda5) - 12*traceYuAdjYu*Sqr(Lambda5
      ) - 318*Lambda1*Sqr(Lambda6) - 132*Lambda3*Sqr(Lambda6) - 140*Lambda4*Sqr
      (Lambda6) - 148*Lambda5*Sqr(Lambda6) - 72*traceYdAdjYd*Sqr(Lambda6) - 24*
      traceYeAdjYe*Sqr(Lambda6) - 72*traceYuAdjYu*Sqr(Lambda6) + Sqr(g1)*(8*
      Lambda3*Lambda4 + 4.166666666666667*Lambda1*traceYdAdjYd +
      2.6666666666666665*traceYdAdjYdYdAdjYd - 12.625*Quad(g2) + (9.75*Lambda1
      + 5*Lambda4 - 9*traceYdAdjYd)*Sqr(g2) + 18*Sqr(Lambda1) + 8*Sqr(Lambda3)
      + 4*Sqr(Lambda4) - 2*Sqr(Lambda5) + 36*Sqr(Lambda6)) + 1.5*Sqr(g2)*(15*
      Lambda1*traceYdAdjYd + 36*Sqr(Lambda1) + 4*(4*Lambda3*Lambda4 + 4*Sqr(
      Lambda3) + Sqr(Lambda4) + 18*Sqr(Lambda6))) + 6*Lambda1*Sqr(Lambda7) - 36
      *Lambda3*Sqr(Lambda7) - 28*Lambda4*Sqr(Lambda7) - 20*Lambda5*Sqr(Lambda7)
      ));


   return beta_Lambda1;
}

/**
 * Calculates the 3-loop beta function of Lambda1.
 *
 * @return 3-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda1;

   beta_Lambda1 = 0;


   return beta_Lambda1;
}

} // namespace flexiblesusy
