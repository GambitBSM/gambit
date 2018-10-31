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

// File generated at Wed 31 Oct 2018 19:35:36

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

   beta_Lambda7 = Re(oneOver16PiSqr*(2*Lambda5*Lambda6 + 12*Lambda2*
      Lambda7 + 10*Lambda5*Lambda7 + 6*Lambda3*(Lambda6 + Lambda7) + 4*Lambda4*
      (Lambda6 + 2*Lambda7) + 9*Lambda7*traceYdAdjYd + 3*Lambda7*traceYeAdjYe +
      9*Lambda7*traceYuAdjYu - 3*Lambda7*Sqr(g1) - 9*Lambda7*Sqr(g2)));


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

   beta_Lambda7 = Re(twoLoop*(-18*Lambda1*Lambda3*Lambda6 - 18*Lambda2*
      Lambda3*Lambda6 - 14*Lambda1*Lambda4*Lambda6 - 14*Lambda2*Lambda4*Lambda6
      - 56*Lambda3*Lambda4*Lambda6 - 10*Lambda1*Lambda5*Lambda6 - 10*Lambda2*
      Lambda5*Lambda6 - 40*Lambda3*Lambda5*Lambda6 - 44*Lambda4*Lambda5*Lambda6
      - 18*Lambda1*Lambda3*Lambda7 - 66*Lambda2*Lambda3*Lambda7 - 14*Lambda1*
      Lambda4*Lambda7 - 70*Lambda2*Lambda4*Lambda7 - 68*Lambda3*Lambda4*Lambda7
      - 10*Lambda1*Lambda5*Lambda7 - 74*Lambda2*Lambda5*Lambda7 - 72*Lambda3*
      Lambda5*Lambda7 - 76*Lambda4*Lambda5*Lambda7 - 72*Lambda2*Lambda7*
      traceYdAdjYd - 18*Lambda3*Lambda7*traceYdAdjYd - 24*Lambda4*Lambda7*
      traceYdAdjYd - 30*Lambda5*Lambda7*traceYdAdjYd - 8.25*Lambda7*
      traceYdAdjYdYdAdjYd - 19.5*Lambda7*traceYdAdjYuYuAdjYd - 24*Lambda2*
      Lambda7*traceYeAdjYe - 6*Lambda3*Lambda7*traceYeAdjYe - 8*Lambda4*Lambda7
      *traceYeAdjYe - 10*Lambda5*Lambda7*traceYeAdjYe - 2.75*Lambda7*
      traceYeAdjYeYeAdjYe - 72*Lambda2*Lambda7*traceYuAdjYu - 18*Lambda3*
      Lambda7*traceYuAdjYu - 24*Lambda4*Lambda7*traceYuAdjYu - 30*Lambda5*
      Lambda7*traceYuAdjYu - 8.25*Lambda7*traceYuAdjYuYuAdjYu - 42*Cube(Lambda6
      ) - 111*Cube(Lambda7) + 0.125*(30*Lambda6 + 187*Lambda7)*Quad(g1) + 0.375
      *(30*Lambda6 - 47*Lambda7)*Quad(g2) + 1.125*(16*Lambda3*(2*Lambda6 +
      Lambda7) + 16*Lambda4*(Lambda6 + 2*Lambda7) + Lambda7*(48*Lambda2 + 48*
      Lambda5 + 5*(3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu)))*Sqr(g2) +
      0.125*Sqr(g1)*(64*Lambda4*Lambda6 - 16*Lambda5*Lambda6 + 144*Lambda2*
      Lambda7 + 80*Lambda4*Lambda7 + 160*Lambda5*Lambda7 + 48*Lambda3*(2*
      Lambda6 + Lambda7) + 25*Lambda7*traceYdAdjYd + 75*Lambda7*traceYeAdjYe +
      85*Lambda7*traceYuAdjYu + (20*Lambda6 + 58*Lambda7)*Sqr(g2)) + 60*Lambda7
      *traceYdAdjYd*Sqr(g3) + 60*Lambda7*traceYuAdjYu*Sqr(g3) + 1.5*Lambda7*Sqr
      (Lambda1) - 79.5*Lambda7*Sqr(Lambda2) - 36*Lambda6*Sqr(Lambda3) - 32*
      Lambda7*Sqr(Lambda3) - 34*Lambda6*Sqr(Lambda4) - 34*Lambda7*Sqr(Lambda4)
      - 42*Lambda6*Sqr(Lambda5) - 36*Lambda7*Sqr(Lambda5) - 33*Lambda7*Sqr(
      Lambda6) - 126*Lambda6*Sqr(Lambda7)));


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
