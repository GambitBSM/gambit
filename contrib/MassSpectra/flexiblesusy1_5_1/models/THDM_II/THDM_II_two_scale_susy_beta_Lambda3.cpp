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

// File generated at Wed 29 Mar 2017 15:35:46

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Lambda3.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda3_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;


   double beta_Lambda3;

   beta_Lambda3 = Re(oneOver16PiSqr*(0.75*Power(g1,4) + 2.25*Power(g2,4)
      + 6*Lambda1*Lambda3 + 6*Lambda2*Lambda3 + 2*Lambda1*Lambda4 + 2*Lambda2*
      Lambda4 + 16*Lambda6*Lambda7 + 6*Lambda3*traceYdAdjYd - 12*
      traceYdAdjYuYuAdjYd + 2*Lambda3*traceYeAdjYe + 6*Lambda3*traceYuAdjYu - 3
      *Lambda3*Sqr(g1) - 9*Lambda3*Sqr(g2) - 1.5*Sqr(g1)*Sqr(g2) + 4*Sqr(
      Lambda3) + 2*Sqr(Lambda4) + 2*Sqr(Lambda5) + 4*Sqr(Lambda6) + 4*Sqr(
      Lambda7)));


   return beta_Lambda3;
}

/**
 * Calculates the two-loop beta function of Lambda3.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda3_two_loop(const Susy_traces& susy_traces) const
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


   double beta_Lambda3;

   const double beta_Lambda3_1 = Re(-0.041666666666666664*twoLoop*(393*
      Power(g1,6) - 3*Power(g1,4)*(30*Lambda1 + 30*Lambda2 + 197*Lambda3 + 20*
      Lambda4 + 10*traceYdAdjYd - 50*traceYeAdjYe + 101*Sqr(g2)) - Sqr(g1)*(33*
      Power(g2,4) + 288*Lambda2*Lambda3 + 96*Lambda2*Lambda4 + 96*Lambda1*(3*
      Lambda3 + Lambda4) + 768*Lambda6*Lambda7 + 50*Lambda3*traceYdAdjYd - 32*
      traceYdAdjYuYuAdjYd + 150*Lambda3*traceYeAdjYe - 6*(10*Lambda1 + 10*
      Lambda2 - 11*Lambda3 + 12*Lambda4 - 18*traceYdAdjYd - 22*traceYeAdjYe)*
      Sqr(g2) + 48*Sqr(Lambda3) - 48*Sqr(Lambda4) + 96*Sqr(Lambda5) + 48*Sqr(
      Lambda6) + 48*Sqr(Lambda7)) + 3*(-291*Power(g2,6) - 3*Power(g2,4)*(30*
      Lambda1 + 30*Lambda2 - 37*Lambda3 + 20*Lambda4 - 6*traceYdAdjYd - 2*
      traceYeAdjYe) - 6*Sqr(g2)*(-16*Lambda3*Lambda4 + 24*Lambda1*(2*Lambda3 +
      Lambda4) + 24*Lambda2*(2*Lambda3 + Lambda4) + 144*Lambda6*Lambda7 + 15*
      Lambda3*traceYdAdjYd + 5*Lambda3*traceYeAdjYe + 8*Sqr(Lambda3) + 8*Sqr(
      Lambda4)) + 4*(24*Power(Lambda3,3) + 24*Power(Lambda4,3) + 352*Lambda3*
      Lambda6*Lambda7 + 176*Lambda4*Lambda6*Lambda7 + 144*Lambda5*Lambda6*
      Lambda7 + 96*Lambda6*Lambda7*traceYdAdjYd + 27*Lambda3*
      traceYdAdjYdYdAdjYd - 24*traceYdAdjYdYdAdjYuYuAdjYd - 30*Lambda3*
      traceYdAdjYuYuAdjYd - 48*traceYdAdjYuYuAdjYdYdAdjYd - 72*
      traceYdAdjYuYuAdjYuYuAdjYd + 32*Lambda6*Lambda7*traceYeAdjYe + 9*Lambda3*
      traceYeAdjYeYeAdjYe - 80*Lambda3*traceYdAdjYd*Sqr(g3) + 128*
      traceYdAdjYuYuAdjYd*Sqr(g3) + (30*Lambda3 + 8*Lambda4)*Sqr(Lambda1) + (30
      *Lambda3 + 8*Lambda4)*Sqr(Lambda2) + 8*Lambda4*Sqr(Lambda3) + 24*
      traceYdAdjYd*Sqr(Lambda3) + 8*traceYeAdjYe*Sqr(Lambda3) + 32*Lambda3*Sqr(
      Lambda4) + 12*traceYdAdjYd*Sqr(Lambda4) + 4*traceYeAdjYe*Sqr(Lambda4) +
      36*Lambda3*Sqr(Lambda5) + 88*Lambda4*Sqr(Lambda5) + 12*traceYdAdjYd*Sqr(
      Lambda5) + 4*traceYeAdjYe*Sqr(Lambda5) + 120*Lambda3*Sqr(Lambda6) + 136*
      Lambda4*Sqr(Lambda6) + 136*Lambda5*Sqr(Lambda6) + 48*traceYdAdjYd*Sqr(
      Lambda6) + 16*traceYeAdjYe*Sqr(Lambda6) + 120*Lambda3*Sqr(Lambda7) + 136*
      Lambda4*Sqr(Lambda7) + 136*Lambda5*Sqr(Lambda7) + 4*Lambda1*(22*Lambda6*
      Lambda7 + 6*Lambda4*traceYdAdjYd + 2*Lambda4*traceYeAdjYe + 2*Lambda3*(4*
      Lambda4 + 9*traceYdAdjYd + 3*traceYeAdjYe) + 18*Sqr(Lambda3) + 7*Sqr(
      Lambda4) + 9*Sqr(Lambda5) + 31*Sqr(Lambda6) + 11*Sqr(Lambda7)) + 4*
      Lambda2*(8*Lambda3*Lambda4 + 22*Lambda6*Lambda7 + 18*Sqr(Lambda3) + 7*Sqr
      (Lambda4) + 9*Sqr(Lambda5) + 11*Sqr(Lambda6) + 31*Sqr(Lambda7))))));
   const double beta_Lambda3_2 = Re(-0.08333333333333333*twoLoop*(57*
      Power(g1,4)*traceYuAdjYu - traceYuAdjYu*Sqr(g1)*(85*Lambda3 + 126*Sqr(g2)
      ) + 3*(9*Power(g2,4)*traceYuAdjYu - 45*Lambda3*traceYuAdjYu*Sqr(g2) + 2*(
      -80*Lambda3*traceYuAdjYu*Sqr(g3) + 3*(8*Lambda2*(3*Lambda3 + Lambda4)*
      traceYuAdjYu + 9*Lambda3*traceYuAdjYuYuAdjYu + 8*traceYuAdjYu*Sqr(Lambda3
      ) + 4*traceYuAdjYu*(4*Lambda7*(2*Lambda6 + Lambda7) + Sqr(Lambda4) + Sqr(
      Lambda5)))))));

   beta_Lambda3 = beta_Lambda3_1 + beta_Lambda3_2;


   return beta_Lambda3;
}

/**
 * Calculates the three-loop beta function of Lambda3.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda3_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda3;

   beta_Lambda3 = 0;


   return beta_Lambda3;
}

} // namespace flexiblesusy
