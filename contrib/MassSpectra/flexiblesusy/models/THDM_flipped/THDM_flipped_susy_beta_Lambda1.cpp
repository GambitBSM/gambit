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

// File generated at Tue 7 Apr 2020 14:54:52

#include "THDM_flipped_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda1.
 *
 * @return 1-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;


   double beta_Lambda1;

   beta_Lambda1 = Re(oneOver16PiSqr*(4*Lambda3*Lambda4 + 12*Lambda1*
      traceYdAdjYd - 12*traceYdAdjYdYdAdjYd + 2*AbsSqr(Lambda5) + 24*AbsSqr(
      Lambda6) + 0.75*Quad(g1) + 2.25*Quad(g2) - 3*Lambda1*Sqr(g1) - 9*Lambda1*
      Sqr(g2) + 1.5*Sqr(g1)*Sqr(g2) + 12*Sqr(Lambda1) + 4*Sqr(Lambda3) + 2*Sqr(
      Lambda4)));


   return beta_Lambda1;
}

/**
 * Calculates the 2-loop beta function of Lambda1.
 *
 * @return 2-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;


   double beta_Lambda1;

   beta_Lambda1 = Re(twoLoop*(-20*Lambda1*Lambda3*Lambda4 - 20*Lambda5*
      Lambda6*Lambda7 - 3*Lambda1*traceYdAdjYdYdAdjYd + 60*
      traceYdAdjYdYdAdjYdYdAdjYd - 9*Lambda1*traceYdAdjYuYuAdjYd + 12*
      traceYdAdjYuYuAdjYdYdAdjYd - 8*Lambda3*Lambda4*traceYeAdjYe - 24*Lambda3*
      Lambda4*traceYuAdjYu + 6*Lambda1*AbsSqr(Lambda7) - 36*Lambda3*AbsSqr(
      Lambda7) - 28*Lambda4*AbsSqr(Lambda7) - 36*Lambda3*Lambda6*Conj(Lambda7)
      - 28*Lambda4*Lambda6*Conj(Lambda7) - 78*Cube(Lambda1) - 16*Cube(Lambda3)
      - 12*Cube(Lambda4) - 16.375*Power6(g1) + 36.375*Power6(g2) + 27.125*
      Lambda1*Quad(g1) + 5*Lambda3*Quad(g1) + 2.5*Lambda4*Quad(g1) + 2.5*
      traceYdAdjYd*Quad(g1) - 6.375*Lambda1*Quad(g2) + 15*Lambda3*Quad(g2) +
      7.5*Lambda4*Quad(g2) - 4.5*traceYdAdjYd*Quad(g2) + 8*Lambda3*Lambda4*Sqr(
      g1) + 4.166666666666667*Lambda1*traceYdAdjYd*Sqr(g1) + 2.6666666666666665
      *traceYdAdjYdYdAdjYd*Sqr(g1) - 12.625*Quad(g2)*Sqr(g1) + 24*Lambda3*
      Lambda4*Sqr(g2) + 22.5*Lambda1*traceYdAdjYd*Sqr(g2) - 23.875*Quad(g1)*Sqr
      (g2) + 9.75*Lambda1*Sqr(g1)*Sqr(g2) + 5*Lambda4*Sqr(g1)*Sqr(g2) + 9*
      traceYdAdjYd*Sqr(g1)*Sqr(g2) + 2*Conj(Lambda6)*(-159*Lambda1*Lambda6 - 66
      *Lambda3*Lambda6 - 70*Lambda4*Lambda6 - 18*Lambda3*Lambda7 - 14*Lambda4*
      Lambda7 - 36*Lambda6*traceYdAdjYd - 12*Lambda6*traceYeAdjYe - 36*Lambda6*
      traceYuAdjYu + 18*Lambda6*Sqr(g1) + 54*Lambda6*Sqr(g2)) + 80*Lambda1*
      traceYdAdjYd*Sqr(g3) - 64*traceYdAdjYdYdAdjYd*Sqr(g3) - 72*traceYdAdjYd*
      Sqr(Lambda1) + 18*Sqr(g1)*Sqr(Lambda1) + 54*Sqr(g2)*Sqr(Lambda1) - 20*
      Lambda1*Sqr(Lambda3) - 24*Lambda4*Sqr(Lambda3) - 8*traceYeAdjYe*Sqr(
      Lambda3) - 24*traceYuAdjYu*Sqr(Lambda3) + 8*Sqr(g1)*Sqr(Lambda3) + 24*Sqr
      (g2)*Sqr(Lambda3) - 12*Lambda1*Sqr(Lambda4) - 32*Lambda3*Sqr(Lambda4) - 4
      *traceYeAdjYe*Sqr(Lambda4) - 12*traceYuAdjYu*Sqr(Lambda4) + 4*Sqr(g1)*Sqr
      (Lambda4) + 6*Sqr(g2)*Sqr(Lambda4) - 74*Lambda5*Sqr(Lambda6) - 10*Lambda5
      *Sqr(Lambda7) - 2*Conj(Lambda5)*(10*Conj(Lambda6)*Conj(Lambda7) + Lambda5
      *(7*Lambda1 + 20*Lambda3 + 22*Lambda4 + 2*traceYeAdjYe + 6*traceYuAdjYu +
      Sqr(g1)) + 37*Sqr(Conj(Lambda6)) + 5*Sqr(Conj(Lambda7)))));


   return beta_Lambda1;
}

/**
 * Calculates the 3-loop beta function of Lambda1.
 *
 * @return 3-loop beta function
 */
double THDM_flipped_susy_parameters::calc_beta_Lambda1_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda1;

   beta_Lambda1 = 0;


   return beta_Lambda1;
}

} // namespace flexiblesusy
