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
 * Calculates the one-loop beta function of Lambda7.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda7_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda7;

   beta_Lambda7 = Re(oneOver16PiSqr*(6*Lambda3*Lambda6 + 4*Lambda4*
      Lambda6 + 2*Lambda5*Lambda6 + 12*Lambda2*Lambda7 + 6*Lambda3*Lambda7 + 8*
      Lambda4*Lambda7 + 10*Lambda5*Lambda7 + 3*Lambda7*traceYdAdjYd + Lambda7*
      traceYeAdjYe + 9*Lambda7*traceYuAdjYu - 3*Lambda7*Sqr(g1) - 9*Lambda7*Sqr
      (g2)));


   return beta_Lambda7;
}

/**
 * Calculates the two-loop beta function of Lambda7.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda7_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda7;

   beta_Lambda7 = Re(twoLoop*(3.75*Power(g1,4)*Lambda6 + 11.25*Power(g2,4
      )*Lambda6 - 18*Lambda1*Lambda3*Lambda6 - 18*Lambda2*Lambda3*Lambda6 - 14*
      Lambda1*Lambda4*Lambda6 - 14*Lambda2*Lambda4*Lambda6 - 56*Lambda3*Lambda4
      *Lambda6 - 10*Lambda1*Lambda5*Lambda6 - 10*Lambda2*Lambda5*Lambda6 - 40*
      Lambda3*Lambda5*Lambda6 - 44*Lambda4*Lambda5*Lambda6 - 42*Power(Lambda6,3
      ) + 23.375*Power(g1,4)*Lambda7 - 17.625*Power(g2,4)*Lambda7 - 18*Lambda1*
      Lambda3*Lambda7 - 66*Lambda2*Lambda3*Lambda7 - 14*Lambda1*Lambda4*Lambda7
      - 70*Lambda2*Lambda4*Lambda7 - 68*Lambda3*Lambda4*Lambda7 - 10*Lambda1*
      Lambda5*Lambda7 - 74*Lambda2*Lambda5*Lambda7 - 72*Lambda3*Lambda5*Lambda7
      - 76*Lambda4*Lambda5*Lambda7 - 111*Power(Lambda7,3) - 6.75*Lambda7*
      traceYdAdjYdYdAdjYd - 21*Lambda7*traceYdAdjYuYuAdjYd - 2.25*Lambda7*
      traceYeAdjYeYeAdjYe - 72*Lambda2*Lambda7*traceYuAdjYu - 18*Lambda3*
      Lambda7*traceYuAdjYu - 24*Lambda4*Lambda7*traceYuAdjYu - 30*Lambda5*
      Lambda7*traceYuAdjYu - 8.25*Lambda7*traceYuAdjYuYuAdjYu + 12*Lambda3*
      Lambda6*Sqr(g1) + 8*Lambda4*Lambda6*Sqr(g1) - 2*Lambda5*Lambda6*Sqr(g1) +
      18*Lambda2*Lambda7*Sqr(g1) + 6*Lambda3*Lambda7*Sqr(g1) + 10*Lambda4*
      Lambda7*Sqr(g1) + 20*Lambda5*Lambda7*Sqr(g1) + 10.625*Lambda7*
      traceYuAdjYu*Sqr(g1) + 36*Lambda3*Lambda6*Sqr(g2) + 18*Lambda4*Lambda6*
      Sqr(g2) + 54*Lambda2*Lambda7*Sqr(g2) + 18*Lambda3*Lambda7*Sqr(g2) + 36*
      Lambda4*Lambda7*Sqr(g2) + 54*Lambda5*Lambda7*Sqr(g2) + 16.875*Lambda7*
      traceYuAdjYu*Sqr(g2) + 2.5*Lambda6*Sqr(g1)*Sqr(g2) + 7.25*Lambda7*Sqr(g1)
      *Sqr(g2) - 0.125*traceYeAdjYe*(32*Lambda5*Lambda6 + 80*Lambda5*Lambda7 +
      64*Lambda4*(Lambda6 + Lambda7) + 48*Lambda3*(2*Lambda6 + Lambda7) - 25*
      Lambda7*Sqr(g1) - 15*Lambda7*Sqr(g2)) + 60*Lambda7*traceYuAdjYu*Sqr(g3) +
      traceYdAdjYd*(-12*Lambda5*Lambda6 - 30*Lambda5*Lambda7 - 24*Lambda4*(
      Lambda6 + Lambda7) - 18*Lambda3*(2*Lambda6 + Lambda7) +
      1.0416666666666667*Lambda7*Sqr(g1) + 5.625*Lambda7*Sqr(g2) + 20*Lambda7*
      Sqr(g3)) + 1.5*Lambda7*Sqr(Lambda1) - 79.5*Lambda7*Sqr(Lambda2) - 36*
      Lambda6*Sqr(Lambda3) - 32*Lambda7*Sqr(Lambda3) - 34*Lambda6*Sqr(Lambda4)
      - 34*Lambda7*Sqr(Lambda4) - 42*Lambda6*Sqr(Lambda5) - 36*Lambda7*Sqr(
      Lambda5) - 33*Lambda7*Sqr(Lambda6) - 126*Lambda6*Sqr(Lambda7)));


   return beta_Lambda7;
}

/**
 * Calculates the three-loop beta function of Lambda7.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda7_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda7;

   beta_Lambda7 = 0;


   return beta_Lambda7;
}

} // namespace flexiblesusy
