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
 * Calculates the one-loop beta function of Lambda1.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   double beta_Lambda1;

   beta_Lambda1 = Re(oneOver16PiSqr*(0.75*Power(g1,4) + 2.25*Power(g2,4)
      + 4*Lambda3*Lambda4 + 12*Lambda1*traceYdAdjYd - 12*traceYdAdjYdYdAdjYd +
      4*Lambda1*traceYeAdjYe - 4*traceYeAdjYeYeAdjYe - 3*Lambda1*Sqr(g1) - 9*
      Lambda1*Sqr(g2) + 1.5*Sqr(g1)*Sqr(g2) + 12*Sqr(Lambda1) + 4*Sqr(Lambda3)
      + 2*Sqr(Lambda4) + 2*Sqr(Lambda5) + 24*Sqr(Lambda6)));


   return beta_Lambda1;
}

/**
 * Calculates the two-loop beta function of Lambda1.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYeYeAdjYe =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeYeAdjYe;


   double beta_Lambda1;

   beta_Lambda1 = Re(twoLoop*(-16.375*Power(g1,6) + 36.375*Power(g2,6) +
      27.125*Power(g1,4)*Lambda1 - 6.375*Power(g2,4)*Lambda1 - 78*Power(Lambda1
      ,3) + 5*Power(g1,4)*Lambda3 + 15*Power(g2,4)*Lambda3 - 16*Power(Lambda3,3
      ) + 2.5*Power(g1,4)*Lambda4 + 7.5*Power(g2,4)*Lambda4 - 20*Lambda1*
      Lambda3*Lambda4 - 12*Power(Lambda4,3) - 72*Lambda3*Lambda6*Lambda7 - 56*
      Lambda4*Lambda6*Lambda7 - 40*Lambda5*Lambda6*Lambda7 - 3*Lambda1*
      traceYdAdjYdYdAdjYd + 60*traceYdAdjYdYdAdjYdYdAdjYd - 9*Lambda1*
      traceYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - Lambda1*
      traceYeAdjYeYeAdjYe + 20*traceYeAdjYeYeAdjYeYeAdjYe - 24*Lambda3*Lambda4*
      traceYuAdjYu - 12.625*Power(g2,4)*Sqr(g1) + 8*Lambda3*Lambda4*Sqr(g1) +
      2.6666666666666665*traceYdAdjYdYdAdjYd*Sqr(g1) - 8*traceYeAdjYeYeAdjYe*
      Sqr(g1) - 23.875*Power(g1,4)*Sqr(g2) + 24*Lambda3*Lambda4*Sqr(g2) + 9.75*
      Lambda1*Sqr(g1)*Sqr(g2) + 5*Lambda4*Sqr(g1)*Sqr(g2) - 64*
      traceYdAdjYdYdAdjYd*Sqr(g3) + 18*Sqr(g1)*Sqr(Lambda1) + 54*Sqr(g2)*Sqr(
      Lambda1) - 20*Lambda1*Sqr(Lambda3) - 24*Lambda4*Sqr(Lambda3) - 24*
      traceYuAdjYu*Sqr(Lambda3) + 8*Sqr(g1)*Sqr(Lambda3) + 24*Sqr(g2)*Sqr(
      Lambda3) - 12*Lambda1*Sqr(Lambda4) - 32*Lambda3*Sqr(Lambda4) - 12*
      traceYuAdjYu*Sqr(Lambda4) + 4*Sqr(g1)*Sqr(Lambda4) + 6*Sqr(g2)*Sqr(
      Lambda4) - 14*Lambda1*Sqr(Lambda5) - 40*Lambda3*Sqr(Lambda5) - 44*Lambda4
      *Sqr(Lambda5) - 12*traceYuAdjYu*Sqr(Lambda5) - 2*Sqr(g1)*Sqr(Lambda5) +
      traceYdAdjYd*(2.5*Power(g1,4) - 4.5*Power(g2,4) + Sqr(g1)*(
      4.166666666666667*Lambda1 - 9*Sqr(g2)) + 22.5*Lambda1*Sqr(g2) + 80*
      Lambda1*Sqr(g3) - 72*Sqr(Lambda1) - 72*Sqr(Lambda6)) - 318*Lambda1*Sqr(
      Lambda6) - 132*Lambda3*Sqr(Lambda6) - 140*Lambda4*Sqr(Lambda6) - 148*
      Lambda5*Sqr(Lambda6) - 72*traceYuAdjYu*Sqr(Lambda6) + 36*Sqr(g1)*Sqr(
      Lambda6) + 108*Sqr(g2)*Sqr(Lambda6) - 0.5*traceYeAdjYe*(25*Power(g1,4) +
      Sqr(g1)*(-25*Lambda1 + 22*Sqr(g2)) + 3*(Power(g2,4) - 5*Lambda1*Sqr(g2) +
      16*(Sqr(Lambda1) + Sqr(Lambda6)))) + 6*Lambda1*Sqr(Lambda7) - 36*Lambda3
      *Sqr(Lambda7) - 28*Lambda4*Sqr(Lambda7) - 20*Lambda5*Sqr(Lambda7)));


   return beta_Lambda1;
}

/**
 * Calculates the three-loop beta function of Lambda1.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda1;

   beta_Lambda1 = 0;


   return beta_Lambda1;
}

} // namespace flexiblesusy
