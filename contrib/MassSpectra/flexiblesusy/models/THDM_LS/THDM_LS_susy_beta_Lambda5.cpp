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

// File generated at Tue 7 Apr 2020 14:55:38

#include "THDM_LS_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda5.
 *
 * @return 1-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda5_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda5;

   beta_Lambda5 = Re(oneOver16PiSqr*(4*Conj(Lambda6)*Conj(Lambda7) +
      Lambda5*(2*(Lambda1 + Lambda2 + 4*Lambda3 + 6*Lambda4 + 3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu) - 3*Sqr(g1) - 9*Sqr(g2)) + 10*Sqr(Conj(
      Lambda6)) + 10*Sqr(Conj(Lambda7))));


   return beta_Lambda5;
}

/**
 * Calculates the 2-loop beta function of Lambda5.
 *
 * @return 2-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda5_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda5;

   beta_Lambda5 = Re(twoLoop*(-40*Lambda1*Lambda3*Lambda5 - 40*Lambda2*
      Lambda3*Lambda5 - 44*Lambda1*Lambda4*Lambda5 - 44*Lambda2*Lambda4*Lambda5
      - 76*Lambda3*Lambda4*Lambda5 - 12*Lambda2*Lambda5*traceYdAdjYd - 24*
      Lambda3*Lambda5*traceYdAdjYd - 36*Lambda4*Lambda5*traceYdAdjYd + 4.5*
      Lambda5*traceYdAdjYdYdAdjYd + 3*Lambda5*traceYdAdjYuYuAdjYd - 4*Lambda1*
      Lambda5*traceYeAdjYe - 8*Lambda3*Lambda5*traceYeAdjYe - 12*Lambda4*
      Lambda5*traceYeAdjYe - 2.5*Lambda5*traceYeAdjYeYeAdjYe - 12*Lambda2*
      Lambda5*traceYuAdjYu - 24*Lambda3*Lambda5*traceYuAdjYu - 36*Lambda4*
      Lambda5*traceYuAdjYu - 7.5*Lambda5*traceYuAdjYuYuAdjYu - 72*Lambda5*
      AbsSqr(Lambda7) - 84*Lambda5*Lambda6*Conj(Lambda7) + 19.625*Lambda5*Quad(
      g1) - 6.25*traceYeAdjYe*Quad(g1) - 28.875*Lambda5*Quad(g2) - 0.75*
      traceYeAdjYe*Quad(g2) - 2*Lambda1*Lambda5*Sqr(g1) - 2*Lambda2*Lambda5*Sqr
      (g1) + 16*Lambda3*Lambda5*Sqr(g1) + 24*Lambda4*Lambda5*Sqr(g1) +
      2.0833333333333335*Lambda5*traceYdAdjYd*Sqr(g1) + 6.25*Lambda5*
      traceYeAdjYe*Sqr(g1) + 7.083333333333333*Lambda5*traceYuAdjYu*Sqr(g1) - 4
      *Conj(Lambda6)*(3*Lambda5*(6*Lambda6 + 7*Lambda7) + Conj(Lambda7)*(5*
      Lambda1 + 5*Lambda2 + 20*Lambda3 + 22*Lambda4 + 3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu + Sqr(g1))) + 36*Lambda3*Lambda5*Sqr(g2) +
      72*Lambda4*Lambda5*Sqr(g2) + 11.25*Lambda5*traceYdAdjYd*Sqr(g2) + 3.75*
      Lambda5*traceYeAdjYe*Sqr(g2) + 11.25*Lambda5*traceYuAdjYu*Sqr(g2) + 4.75*
      Lambda5*Sqr(g1)*Sqr(g2) + 5.5*traceYeAdjYe*Sqr(g1)*Sqr(g2) + 40*Lambda5*
      traceYdAdjYd*Sqr(g3) + 40*Lambda5*traceYuAdjYu*Sqr(g3) - 7*Lambda5*Sqr(
      Lambda1) - 7*Lambda5*Sqr(Lambda2) - 28*Lambda5*Sqr(Lambda3) - 32*Lambda5*
      Sqr(Lambda4) + 6*Conj(Lambda5)*Sqr(Lambda5) + 2*(-37*Lambda1 - 5*Lambda2
      - 36*Lambda3 - 38*Lambda4 - 10*traceYeAdjYe + 10*Sqr(g1) + 27*Sqr(g2))*
      Sqr(Conj(Lambda6)) - 10*Lambda1*Sqr(Conj(Lambda7)) - 74*Lambda2*Sqr(Conj(
      Lambda7)) - 72*Lambda3*Sqr(Conj(Lambda7)) - 76*Lambda4*Sqr(Conj(Lambda7))
      - 60*traceYdAdjYd*Sqr(Conj(Lambda7)) - 60*traceYuAdjYu*Sqr(Conj(Lambda7)
      ) + 20*Sqr(g1)*Sqr(Conj(Lambda7)) + 54*Sqr(g2)*Sqr(Conj(Lambda7))));


   return beta_Lambda5;
}

/**
 * Calculates the 3-loop beta function of Lambda5.
 *
 * @return 3-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda5_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda5;

   beta_Lambda5 = 0;


   return beta_Lambda5;
}

} // namespace flexiblesusy
