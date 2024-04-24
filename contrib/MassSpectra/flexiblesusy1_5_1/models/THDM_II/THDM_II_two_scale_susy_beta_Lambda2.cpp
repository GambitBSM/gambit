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
 * Calculates the one-loop beta function of Lambda2.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(oneOver16PiSqr*(0.75*Power(g1,4) + 2.25*Power(g2,4)
      + 4*Lambda3*Lambda4 + 12*Lambda2*traceYuAdjYu - 12*traceYuAdjYuYuAdjYu -
      3*Lambda2*Sqr(g1) - 9*Lambda2*Sqr(g2) + 1.5*Sqr(g1)*Sqr(g2) + 12*Sqr(
      Lambda2) + 4*Sqr(Lambda3) + 2*Sqr(Lambda4) + 2*Sqr(Lambda5) + 24*Sqr(
      Lambda7)));


   return beta_Lambda2;
}

/**
 * Calculates the two-loop beta function of Lambda2.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYuYuAdjYu =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(twoLoop*(-16.375*Power(g1,6) + 36.375*Power(g2,6) +
      27.125*Power(g1,4)*Lambda2 - 6.375*Power(g2,4)*Lambda2 - 78*Power(Lambda2
      ,3) + 5*Power(g1,4)*Lambda3 + 15*Power(g2,4)*Lambda3 - 16*Power(Lambda3,3
      ) + 2.5*Power(g1,4)*Lambda4 + 7.5*Power(g2,4)*Lambda4 - 20*Lambda2*
      Lambda3*Lambda4 - 12*Power(Lambda4,3) - 72*Lambda3*Lambda6*Lambda7 - 56*
      Lambda4*Lambda6*Lambda7 - 40*Lambda5*Lambda6*Lambda7 - 9*Lambda2*
      traceYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYuYuAdjYd - 9.5*Power(g1,4)*
      traceYuAdjYu - 4.5*Power(g2,4)*traceYuAdjYu - 3*Lambda2*
      traceYuAdjYuYuAdjYu + 60*traceYuAdjYuYuAdjYuYuAdjYu - 12.625*Power(g2,4)*
      Sqr(g1) + 8*Lambda3*Lambda4*Sqr(g1) + 14.166666666666666*Lambda2*
      traceYuAdjYu*Sqr(g1) - 5.333333333333333*traceYuAdjYuYuAdjYu*Sqr(g1) -
      23.875*Power(g1,4)*Sqr(g2) + 24*Lambda3*Lambda4*Sqr(g2) + 22.5*Lambda2*
      traceYuAdjYu*Sqr(g2) + 9.75*Lambda2*Sqr(g1)*Sqr(g2) + 5*Lambda4*Sqr(g1)*
      Sqr(g2) - 21*traceYuAdjYu*Sqr(g1)*Sqr(g2) + 80*Lambda2*traceYuAdjYu*Sqr(
      g3) - 64*traceYuAdjYuYuAdjYu*Sqr(g3) - 72*traceYuAdjYu*Sqr(Lambda2) + 18*
      Sqr(g1)*Sqr(Lambda2) + 54*Sqr(g2)*Sqr(Lambda2) - 20*Lambda2*Sqr(Lambda3)
      - 24*Lambda4*Sqr(Lambda3) + 8*Sqr(g1)*Sqr(Lambda3) + 24*Sqr(g2)*Sqr(
      Lambda3) - 12*Lambda2*Sqr(Lambda4) - 32*Lambda3*Sqr(Lambda4) + 4*Sqr(g1)*
      Sqr(Lambda4) + 6*Sqr(g2)*Sqr(Lambda4) - 14*Lambda2*Sqr(Lambda5) - 40*
      Lambda3*Sqr(Lambda5) - 44*Lambda4*Sqr(Lambda5) - 2*Sqr(g1)*Sqr(Lambda5) +
      6*Lambda2*Sqr(Lambda6) - 36*Lambda3*Sqr(Lambda6) - 28*Lambda4*Sqr(
      Lambda6) - 20*Lambda5*Sqr(Lambda6) - 318*Lambda2*Sqr(Lambda7) - 132*
      Lambda3*Sqr(Lambda7) - 140*Lambda4*Sqr(Lambda7) - 148*Lambda5*Sqr(Lambda7
      ) - 72*traceYuAdjYu*Sqr(Lambda7) + 36*Sqr(g1)*Sqr(Lambda7) + 108*Sqr(g2)*
      Sqr(Lambda7) - 12*traceYdAdjYd*(2*Lambda3*Lambda4 + 2*Sqr(Lambda3) + Sqr(
      Lambda4) + Sqr(Lambda5) + 6*Sqr(Lambda7)) - 4*traceYeAdjYe*(2*Lambda3*
      Lambda4 + 2*Sqr(Lambda3) + Sqr(Lambda4) + Sqr(Lambda5) + 6*Sqr(Lambda7)))
      );


   return beta_Lambda2;
}

/**
 * Calculates the three-loop beta function of Lambda2.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda2_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda2;

   beta_Lambda2 = 0;


   return beta_Lambda2;
}

} // namespace flexiblesusy
