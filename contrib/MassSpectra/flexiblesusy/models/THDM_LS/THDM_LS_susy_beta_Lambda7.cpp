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

// File generated at Tue 7 Apr 2020 14:55:39

#include "THDM_LS_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda7.
 *
 * @return 1-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda7_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda7;

   beta_Lambda7 = Re(oneOver16PiSqr*(4*Lambda4*Lambda6 + 12*Lambda2*
      Lambda7 + 8*Lambda4*Lambda7 + 6*Lambda3*(Lambda6 + Lambda7) + 9*Lambda7*
      traceYdAdjYd + Lambda7*traceYeAdjYe + 9*Lambda7*traceYuAdjYu + 2*Conj(
      Lambda5)*(Conj(Lambda6) + 5*Conj(Lambda7)) - 3*Lambda7*Sqr(g1) - 9*
      Lambda7*Sqr(g2)));


   return beta_Lambda7;
}

/**
 * Calculates the 2-loop beta function of Lambda7.
 *
 * @return 2-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda7_2_loop(const Susy_traces& susy_traces) const
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
      - 56*Lambda3*Lambda4*Lambda6 - 18*Lambda1*Lambda3*Lambda7 - 66*Lambda2*
      Lambda3*Lambda7 - 14*Lambda1*Lambda4*Lambda7 - 70*Lambda2*Lambda4*Lambda7
      - 68*Lambda3*Lambda4*Lambda7 - 72*Lambda2*Lambda7*traceYdAdjYd - 18*
      Lambda3*Lambda7*traceYdAdjYd - 24*Lambda4*Lambda7*traceYdAdjYd - 14.25*
      Lambda7*traceYdAdjYdYdAdjYd - 19.5*Lambda7*traceYdAdjYuYuAdjYd - 12*
      Lambda3*Lambda6*traceYeAdjYe - 8*Lambda4*Lambda6*traceYeAdjYe - 6*Lambda3
      *Lambda7*traceYeAdjYe - 8*Lambda4*Lambda7*traceYeAdjYe - 2.25*Lambda7*
      traceYeAdjYeYeAdjYe - 72*Lambda2*Lambda7*traceYuAdjYu - 18*Lambda3*
      Lambda7*traceYuAdjYu - 24*Lambda4*Lambda7*traceYuAdjYu - 2.25*Lambda7*
      traceYuAdjYuYuAdjYu - 84*Lambda6*AbsSqr(Lambda7) + 3.75*Lambda6*Quad(g1)
      + 23.375*Lambda7*Quad(g1) + 11.25*Lambda6*Quad(g2) - 17.625*Lambda7*Quad(
      g2) + 12*Lambda3*Lambda6*Sqr(g1) + 8*Lambda4*Lambda6*Sqr(g1) + 18*Lambda2
      *Lambda7*Sqr(g1) + 6*Lambda3*Lambda7*Sqr(g1) + 10*Lambda4*Lambda7*Sqr(g1)
      + 3.125*Lambda7*traceYdAdjYd*Sqr(g1) + 3.125*Lambda7*traceYeAdjYe*Sqr(g1
      ) + 10.625*Lambda7*traceYuAdjYu*Sqr(g1) - 2*Conj(Lambda5)*(3*Lambda5*(7*
      Lambda6 + 6*Lambda7) + Conj(Lambda6)*(5*Lambda1 + 5*Lambda2 + 20*Lambda3
      + 22*Lambda4 + 2*traceYeAdjYe + Sqr(g1)) + Conj(Lambda7)*(5*Lambda1 + 37*
      Lambda2 + 36*Lambda3 + 38*Lambda4 + 15*traceYdAdjYd + 5*traceYeAdjYe + 15
      *traceYuAdjYu - 10*Sqr(g1) - 27*Sqr(g2))) + 36*Lambda3*Lambda6*Sqr(g2) +
      18*Lambda4*Lambda6*Sqr(g2) + 54*Lambda2*Lambda7*Sqr(g2) + 18*Lambda3*
      Lambda7*Sqr(g2) + 36*Lambda4*Lambda7*Sqr(g2) + 16.875*Lambda7*
      traceYdAdjYd*Sqr(g2) + 1.875*Lambda7*traceYeAdjYe*Sqr(g2) + 16.875*
      Lambda7*traceYuAdjYu*Sqr(g2) + 2.5*Lambda6*Sqr(g1)*Sqr(g2) + 7.25*Lambda7
      *Sqr(g1)*Sqr(g2) + 60*Lambda7*traceYdAdjYd*Sqr(g3) + 60*Lambda7*
      traceYuAdjYu*Sqr(g3) + 1.5*Lambda7*Sqr(Lambda1) - 79.5*Lambda7*Sqr(
      Lambda2) - 36*Lambda6*Sqr(Lambda3) - 32*Lambda7*Sqr(Lambda3) - 34*Lambda6
      *Sqr(Lambda4) - 34*Lambda7*Sqr(Lambda4) - 22*Conj(Lambda7)*Sqr(Lambda6) -
      111*Conj(Lambda7)*Sqr(Lambda7) - Conj(Lambda6)*(11*Lambda6*Lambda7 + 42*
      Sqr(Lambda6) + 42*Sqr(Lambda7))));


   return beta_Lambda7;
}

/**
 * Calculates the 3-loop beta function of Lambda7.
 *
 * @return 3-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda7_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda7;

   beta_Lambda7 = 0;


   return beta_Lambda7;
}

} // namespace flexiblesusy
