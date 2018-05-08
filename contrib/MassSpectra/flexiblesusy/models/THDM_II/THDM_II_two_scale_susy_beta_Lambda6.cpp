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

// File generated at Wed 29 Mar 2017 15:35:44

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Lambda6.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda6_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda6;

   beta_Lambda6 = Re(oneOver16PiSqr*(12*Lambda1*Lambda6 + 6*Lambda3*
      Lambda6 + 8*Lambda4*Lambda6 + 10*Lambda5*Lambda6 + 6*Lambda3*Lambda7 + 4*
      Lambda4*Lambda7 + 2*Lambda5*Lambda7 + 9*Lambda6*traceYdAdjYd + 3*Lambda6*
      traceYeAdjYe + 3*Lambda6*traceYuAdjYu - 3*Lambda6*Sqr(g1) - 9*Lambda6*Sqr
      (g2)));


   return beta_Lambda6;
}

/**
 * Calculates the two-loop beta function of Lambda6.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda6_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda6;

   beta_Lambda6 = Re(twoLoop*(23.375*Power(g1,4)*Lambda6 - 17.625*Power(
      g2,4)*Lambda6 - 66*Lambda1*Lambda3*Lambda6 - 18*Lambda2*Lambda3*Lambda6 -
      70*Lambda1*Lambda4*Lambda6 - 14*Lambda2*Lambda4*Lambda6 - 68*Lambda3*
      Lambda4*Lambda6 - 74*Lambda1*Lambda5*Lambda6 - 10*Lambda2*Lambda5*Lambda6
      - 72*Lambda3*Lambda5*Lambda6 - 76*Lambda4*Lambda5*Lambda6 - 111*Power(
      Lambda6,3) + 3.75*Power(g1,4)*Lambda7 + 11.25*Power(g2,4)*Lambda7 - 18*
      Lambda1*Lambda3*Lambda7 - 18*Lambda2*Lambda3*Lambda7 - 14*Lambda1*Lambda4
      *Lambda7 - 14*Lambda2*Lambda4*Lambda7 - 56*Lambda3*Lambda4*Lambda7 - 10*
      Lambda1*Lambda5*Lambda7 - 10*Lambda2*Lambda5*Lambda7 - 40*Lambda3*Lambda5
      *Lambda7 - 44*Lambda4*Lambda5*Lambda7 - 42*Power(Lambda7,3) - 8.25*
      Lambda6*traceYdAdjYdYdAdjYd - 21*Lambda6*traceYdAdjYuYuAdjYd - 2.75*
      Lambda6*traceYeAdjYeYeAdjYe - 18*Lambda3*Lambda6*traceYuAdjYu - 24*
      Lambda4*Lambda6*traceYuAdjYu - 30*Lambda5*Lambda6*traceYuAdjYu - 36*
      Lambda3*Lambda7*traceYuAdjYu - 24*Lambda4*Lambda7*traceYuAdjYu - 12*
      Lambda5*Lambda7*traceYuAdjYu - 6.75*Lambda6*traceYuAdjYuYuAdjYu + 18*
      Lambda1*Lambda6*Sqr(g1) + 6*Lambda3*Lambda6*Sqr(g1) + 10*Lambda4*Lambda6*
      Sqr(g1) + 20*Lambda5*Lambda6*Sqr(g1) + 12*Lambda3*Lambda7*Sqr(g1) + 8*
      Lambda4*Lambda7*Sqr(g1) - 2*Lambda5*Lambda7*Sqr(g1) + 3.5416666666666665*
      Lambda6*traceYuAdjYu*Sqr(g1) + 54*Lambda1*Lambda6*Sqr(g2) + 18*Lambda3*
      Lambda6*Sqr(g2) + 36*Lambda4*Lambda6*Sqr(g2) + 54*Lambda5*Lambda6*Sqr(g2)
      + 36*Lambda3*Lambda7*Sqr(g2) + 18*Lambda4*Lambda7*Sqr(g2) + 5.625*
      Lambda6*traceYuAdjYu*Sqr(g2) + 7.25*Lambda6*Sqr(g1)*Sqr(g2) + 2.5*Lambda7
      *Sqr(g1)*Sqr(g2) + 0.125*Lambda6*traceYeAdjYe*(-16*(12*Lambda1 + 3*
      Lambda3 + 4*Lambda4 + 5*Lambda5) + 75*Sqr(g1) + 45*Sqr(g2)) + 20*Lambda6*
      traceYuAdjYu*Sqr(g3) + 0.125*Lambda6*traceYdAdjYd*(25*Sqr(g1) + 3*(45*Sqr
      (g2) + 16*(-12*Lambda1 - 3*Lambda3 - 4*Lambda4 - 5*Lambda5 + 10*Sqr(g3)))
      ) - 79.5*Lambda6*Sqr(Lambda1) + 1.5*Lambda6*Sqr(Lambda2) - 32*Lambda6*Sqr
      (Lambda3) - 36*Lambda7*Sqr(Lambda3) - 34*Lambda6*Sqr(Lambda4) - 34*
      Lambda7*Sqr(Lambda4) - 36*Lambda6*Sqr(Lambda5) - 42*Lambda7*Sqr(Lambda5)
      - 126*Lambda7*Sqr(Lambda6) - 33*Lambda6*Sqr(Lambda7)));


   return beta_Lambda6;
}

/**
 * Calculates the three-loop beta function of Lambda6.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda6_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda6;

   beta_Lambda6 = 0;


   return beta_Lambda6;
}

} // namespace flexiblesusy
