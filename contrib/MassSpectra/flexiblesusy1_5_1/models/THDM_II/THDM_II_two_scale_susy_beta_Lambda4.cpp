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

// File generated at Wed 29 Mar 2017 15:35:45

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Lambda4.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda4_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;


   double beta_Lambda4;

   beta_Lambda4 = Re(oneOver16PiSqr*(2*Lambda1*Lambda4 + 2*Lambda2*
      Lambda4 + 8*Lambda3*Lambda4 + 4*Lambda6*Lambda7 + 6*Lambda4*traceYdAdjYd
      + 12*traceYdAdjYuYuAdjYd + 2*Lambda4*traceYeAdjYe + 6*Lambda4*
      traceYuAdjYu - 3*Lambda4*Sqr(g1) - 9*Lambda4*Sqr(g2) + 3*Sqr(g1)*Sqr(g2)
      + 4*Sqr(Lambda4) + 8*Sqr(Lambda5) + 10*Sqr(Lambda6) + 10*Sqr(Lambda7)));


   return beta_Lambda4;
}

/**
 * Calculates the two-loop beta function of Lambda4.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda4_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYdYdAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;


   double beta_Lambda4;

   beta_Lambda4 = Re(twoLoop*(19.625*Power(g1,4)*Lambda4 - 28.875*Power(
      g2,4)*Lambda4 - 40*Lambda1*Lambda3*Lambda4 - 40*Lambda2*Lambda3*Lambda4 -
      20*Lambda1*Lambda6*Lambda7 - 20*Lambda2*Lambda6*Lambda7 - 80*Lambda3*
      Lambda6*Lambda7 - 160*Lambda4*Lambda6*Lambda7 - 96*Lambda5*Lambda6*
      Lambda7 - 13.5*Lambda4*traceYdAdjYdYdAdjYd - 12*
      traceYdAdjYdYdAdjYuYuAdjYd - 24*Lambda3*traceYdAdjYuYuAdjYd - 33*Lambda4*
      traceYdAdjYuYuAdjYd - 12*traceYdAdjYuYuAdjYdYdAdjYd - 24*
      traceYdAdjYuYuAdjYuYuAdjYd - 4.5*Lambda4*traceYeAdjYeYeAdjYe - 12*Lambda2
      *Lambda4*traceYuAdjYu - 24*Lambda3*Lambda4*traceYuAdjYu - 12*Lambda6*
      Lambda7*traceYuAdjYu - 13.5*Lambda4*traceYuAdjYuYuAdjYu - 14*Power(g2,4)*
      Sqr(g1) + 4*Lambda1*Lambda4*Sqr(g1) + 4*Lambda2*Lambda4*Sqr(g1) + 4*
      Lambda3*Lambda4*Sqr(g1) + 8*Lambda6*Lambda7*Sqr(g1) + 1.3333333333333333*
      traceYdAdjYuYuAdjYd*Sqr(g1) + 7.083333333333333*Lambda4*traceYuAdjYu*Sqr(
      g1) - 36.5*Power(g1,4)*Sqr(g2) + 36*Lambda3*Lambda4*Sqr(g2) + 11.25*
      Lambda4*traceYuAdjYu*Sqr(g2) + 5*Lambda1*Sqr(g1)*Sqr(g2) + 5*Lambda2*Sqr(
      g1)*Sqr(g2) + 2*Lambda3*Sqr(g1)*Sqr(g2) + 12.75*Lambda4*Sqr(g1)*Sqr(g2) -
      21*traceYuAdjYu*Sqr(g1)*Sqr(g2) + 64*traceYdAdjYuYuAdjYd*Sqr(g3) + 40*
      Lambda4*traceYuAdjYu*Sqr(g3) - 7*Lambda4*Sqr(Lambda1) - 7*Lambda4*Sqr(
      Lambda2) - 28*Lambda4*Sqr(Lambda3) - 20*Lambda1*Sqr(Lambda4) - 20*Lambda2
      *Sqr(Lambda4) - 28*Lambda3*Sqr(Lambda4) - 12*traceYuAdjYu*Sqr(Lambda4) +
      8*Sqr(g1)*Sqr(Lambda4) + 18*Sqr(g2)*Sqr(Lambda4) - 24*Lambda1*Sqr(Lambda5
      ) - 24*Lambda2*Sqr(Lambda5) - 48*Lambda3*Sqr(Lambda5) - 26*Lambda4*Sqr(
      Lambda5) - 24*traceYuAdjYu*Sqr(Lambda5) + 16*Sqr(g1)*Sqr(Lambda5) + 54*
      Sqr(g2)*Sqr(Lambda5) - 74*Lambda1*Sqr(Lambda6) - 10*Lambda2*Sqr(Lambda6)
      - 72*Lambda3*Sqr(Lambda6) - 68*Lambda4*Sqr(Lambda6) - 80*Lambda5*Sqr(
      Lambda6) + 14*Sqr(g1)*Sqr(Lambda6) + 54*Sqr(g2)*Sqr(Lambda6) - 0.25*
      traceYeAdjYe*(-15*Lambda4*Sqr(g2) + Sqr(g1)*(-25*Lambda4 + 44*Sqr(g2)) +
      16*(Lambda1*Lambda4 + 2*Lambda3*Lambda4 + Lambda6*Lambda7 + Sqr(Lambda4)
      + 2*Sqr(Lambda5) + 5*Sqr(Lambda6))) - 0.08333333333333333*traceYdAdjYd*(
      Sqr(g1)*(-25*Lambda4 + 108*Sqr(g2)) + 3*(-45*Lambda4*Sqr(g2) + 16*(-10*
      Lambda4*Sqr(g3) + 3*(Lambda1*Lambda4 + 2*Lambda3*Lambda4 + Lambda6*
      Lambda7 + Sqr(Lambda4) + 2*Sqr(Lambda5) + 5*Sqr(Lambda6))))) - 10*Lambda1
      *Sqr(Lambda7) - 74*Lambda2*Sqr(Lambda7) - 72*Lambda3*Sqr(Lambda7) - 68*
      Lambda4*Sqr(Lambda7) - 80*Lambda5*Sqr(Lambda7) - 60*traceYuAdjYu*Sqr(
      Lambda7) + 14*Sqr(g1)*Sqr(Lambda7) + 54*Sqr(g2)*Sqr(Lambda7)));


   return beta_Lambda4;
}

/**
 * Calculates the three-loop beta function of Lambda4.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda4_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda4;

   beta_Lambda4 = 0;


   return beta_Lambda4;
}

} // namespace flexiblesusy
