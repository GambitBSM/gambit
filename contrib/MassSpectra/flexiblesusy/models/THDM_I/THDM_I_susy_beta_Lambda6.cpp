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

// File generated at Wed 1 Apr 2020 20:45:01

#include "THDM_I_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda6.
 *
 * @return 1-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda6_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda6;

   beta_Lambda6 = Re(oneOver16PiSqr*(12*Lambda1*Lambda6 + 6*Lambda3*
      Lambda6 + 8*Lambda4*Lambda6 + 6*Lambda3*Lambda7 + 4*Lambda4*Lambda7 + 3*
      Lambda6*traceYdAdjYd + Lambda6*traceYeAdjYe + 3*Lambda6*traceYuAdjYu + 10
      *Lambda5*Conj(Lambda6) + 2*Lambda5*Conj(Lambda7) - 3*Lambda6*Sqr(g1) - 9*
      Lambda6*Sqr(g2)));


   return beta_Lambda6;
}

/**
 * Calculates the 2-loop beta function of Lambda6.
 *
 * @return 2-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda6_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda6;

   beta_Lambda6 = Re(twoLoop*(-63*Lambda1*Lambda3*Lambda6 - 18*Lambda2*
      Lambda3*Lambda6 - 67*Lambda1*Lambda4*Lambda6 - 14*Lambda2*Lambda4*Lambda6
      - 65*Lambda3*Lambda4*Lambda6 + 1.5*Lambda1*Lambda2*Lambda7 - 16.5*
      Lambda1*Lambda3*Lambda7 - 16.5*Lambda2*Lambda3*Lambda7 - 12.5*Lambda1*
      Lambda4*Lambda7 - 12.5*Lambda2*Lambda4*Lambda7 - 53*Lambda3*Lambda4*
      Lambda7 - 18*Lambda3*Lambda6*traceYdAdjYd - 24*Lambda4*Lambda6*
      traceYdAdjYd - 36*Lambda3*Lambda7*traceYdAdjYd - 24*Lambda4*Lambda7*
      traceYdAdjYd - 6.75*Lambda6*traceYdAdjYdYdAdjYd + 1.5*Lambda6*
      traceYdAdjYuYuAdjYd - 6*Lambda3*Lambda6*traceYeAdjYe - 8*Lambda4*Lambda6*
      traceYeAdjYe - 12*Lambda3*Lambda7*traceYeAdjYe - 8*Lambda4*Lambda7*
      traceYeAdjYe - 2.25*Lambda6*traceYeAdjYeYeAdjYe - 18*Lambda3*Lambda6*
      traceYuAdjYu - 24*Lambda4*Lambda6*traceYuAdjYu - 36*Lambda3*Lambda7*
      traceYuAdjYu - 24*Lambda4*Lambda7*traceYuAdjYu - 6.75*Lambda6*
      traceYuAdjYuYuAdjYu - 1.5*(23*Lambda6 + 27*Lambda7)*AbsSqr(Lambda5) - 11*
      Lambda6*AbsSqr(Lambda7) - 8.5*Lambda1*Lambda5*Conj(Lambda7) - 8.5*Lambda2
      *Lambda5*Conj(Lambda7) - 37*Lambda3*Lambda5*Conj(Lambda7) - 41*Lambda4*
      Lambda5*Conj(Lambda7) - 12*Lambda5*traceYdAdjYd*Conj(Lambda7) - 4*Lambda5
      *traceYeAdjYe*Conj(Lambda7) - 12*Lambda5*traceYuAdjYu*Conj(Lambda7) +
      23.375*Lambda6*Quad(g1) + 3.75*Lambda7*Quad(g1) - 17.625*Lambda6*Quad(g2)
      + 11.25*Lambda7*Quad(g2) + 18*Lambda1*Lambda6*Sqr(g1) + 6*Lambda3*
      Lambda6*Sqr(g1) + 10*Lambda4*Lambda6*Sqr(g1) + 12*Lambda3*Lambda7*Sqr(g1)
      + 8*Lambda4*Lambda7*Sqr(g1) + 1.0416666666666667*Lambda6*traceYdAdjYd*
      Sqr(g1) + 3.125*Lambda6*traceYeAdjYe*Sqr(g1) + 3.5416666666666665*Lambda6
      *traceYuAdjYu*Sqr(g1) - 2*Lambda5*Conj(Lambda7)*Sqr(g1) + 54*Lambda1*
      Lambda6*Sqr(g2) + 18*Lambda3*Lambda6*Sqr(g2) + 36*Lambda4*Lambda6*Sqr(g2)
      + 36*Lambda3*Lambda7*Sqr(g2) + 18*Lambda4*Lambda7*Sqr(g2) + 5.625*
      Lambda6*traceYdAdjYd*Sqr(g2) + 1.875*Lambda6*traceYeAdjYe*Sqr(g2) + 5.625
      *Lambda6*traceYuAdjYu*Sqr(g2) + 7.25*Lambda6*Sqr(g1)*Sqr(g2) + 2.5*
      Lambda7*Sqr(g1)*Sqr(g2) + 20*Lambda6*traceYdAdjYd*Sqr(g3) + 20*Lambda6*
      traceYuAdjYu*Sqr(g3) - 78*Lambda6*Sqr(Lambda1) + 1.5*Lambda6*Sqr(Lambda2)
      - 30.5*Lambda6*Sqr(Lambda3) - 34.5*Lambda7*Sqr(Lambda3) - 32.5*Lambda6*
      Sqr(Lambda4) - 32.5*Lambda7*Sqr(Lambda4) - 42*Conj(Lambda7)*Sqr(Lambda6)
      + Conj(Lambda6)*(-71*Lambda1*Lambda5 - 10*Lambda2*Lambda5 - 69*Lambda3*
      Lambda5 - 73*Lambda4*Lambda5 - 84*Lambda6*Lambda7 - 30*Lambda5*
      traceYdAdjYd - 10*Lambda5*traceYeAdjYe - 30*Lambda5*traceYuAdjYu + 20*
      Lambda5*Sqr(g1) + 54*Lambda5*Sqr(g2) - 111*Sqr(Lambda6) - 22*Sqr(Lambda7)
      ) - 42*Conj(Lambda7)*Sqr(Lambda7)));


   return beta_Lambda6;
}

/**
 * Calculates the 3-loop beta function of Lambda6.
 *
 * @return 3-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda6_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda6;

   beta_Lambda6 = 0;


   return beta_Lambda6;
}

} // namespace flexiblesusy
