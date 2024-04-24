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

// File generated at Tue 7 Apr 2020 02:31:56

#include "THDM_I_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda4.
 *
 * @return 1-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda4_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda4;

   beta_Lambda4 = Re(oneOver16PiSqr*(2*Lambda1*Lambda4 + 2*Lambda2*
      Lambda4 + 8*Lambda3*Lambda4 + 6*Lambda4*traceYdAdjYd + 2*Lambda4*
      traceYeAdjYe + 6*Lambda4*traceYuAdjYu + 8*AbsSqr(Lambda5) + 10*AbsSqr(
      Lambda7) + 2*(5*Lambda6 + Lambda7)*Conj(Lambda6) + 2*Lambda6*Conj(Lambda7
      ) - 3*Lambda4*Sqr(g1) - 9*Lambda4*Sqr(g2) + 3*Sqr(g1)*Sqr(g2) + 4*Sqr(
      Lambda4)));


   return beta_Lambda4;
}

/**
 * Calculates the 2-loop beta function of Lambda4.
 *
 * @return 2-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda4_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda4;

   beta_Lambda4 = Re(twoLoop*(-40*Lambda1*Lambda3*Lambda4 - 40*Lambda2*
      Lambda3*Lambda4 - 48*Lambda5*Lambda6*Lambda7 - 12*Lambda2*Lambda4*
      traceYdAdjYd - 24*Lambda3*Lambda4*traceYdAdjYd - 13.5*Lambda4*
      traceYdAdjYdYdAdjYd + 27*Lambda4*traceYdAdjYuYuAdjYd - 4*Lambda2*Lambda4*
      traceYeAdjYe - 8*Lambda3*Lambda4*traceYeAdjYe - 4.5*Lambda4*
      traceYeAdjYeYeAdjYe - 12*Lambda2*Lambda4*traceYuAdjYu - 24*Lambda3*
      Lambda4*traceYuAdjYu - 13.5*Lambda4*traceYuAdjYuYuAdjYu - 10*Lambda1*
      AbsSqr(Lambda7) - 74*Lambda2*AbsSqr(Lambda7) - 72*Lambda3*AbsSqr(Lambda7)
      - 68*Lambda4*AbsSqr(Lambda7) - 60*traceYdAdjYd*AbsSqr(Lambda7) - 20*
      traceYeAdjYe*AbsSqr(Lambda7) - 60*traceYuAdjYu*AbsSqr(Lambda7) - 10*
      Lambda1*Lambda6*Conj(Lambda7) - 10*Lambda2*Lambda6*Conj(Lambda7) - 40*
      Lambda3*Lambda6*Conj(Lambda7) - 80*Lambda4*Lambda6*Conj(Lambda7) - 6*
      Lambda6*traceYdAdjYd*Conj(Lambda7) - 2*Lambda6*traceYeAdjYe*Conj(Lambda7)
      - 6*Lambda6*traceYuAdjYu*Conj(Lambda7) + 19.625*Lambda4*Quad(g1) -
      28.875*Lambda4*Quad(g2) + 4*Lambda1*Lambda4*Sqr(g1) + 4*Lambda2*Lambda4*
      Sqr(g1) + 4*Lambda3*Lambda4*Sqr(g1) + 2.0833333333333335*Lambda4*
      traceYdAdjYd*Sqr(g1) + 6.25*Lambda4*traceYeAdjYe*Sqr(g1) +
      7.083333333333333*Lambda4*traceYuAdjYu*Sqr(g1) + 14*AbsSqr(Lambda7)*Sqr(
      g1) + 4*Lambda6*Conj(Lambda7)*Sqr(g1) - 14*Quad(g2)*Sqr(g1) + 36*Lambda3*
      Lambda4*Sqr(g2) + 11.25*Lambda4*traceYdAdjYd*Sqr(g2) + 3.75*Lambda4*
      traceYeAdjYe*Sqr(g2) + 11.25*Lambda4*traceYuAdjYu*Sqr(g2) + 54*AbsSqr(
      Lambda7)*Sqr(g2) - 36.5*Quad(g1)*Sqr(g2) + 5*Lambda1*Sqr(g1)*Sqr(g2) + 5*
      Lambda2*Sqr(g1)*Sqr(g2) + 2*Lambda3*Sqr(g1)*Sqr(g2) + 12.75*Lambda4*Sqr(
      g1)*Sqr(g2) + 9*traceYdAdjYd*Sqr(g1)*Sqr(g2) + 11*traceYeAdjYe*Sqr(g1)*
      Sqr(g2) + 21*traceYuAdjYu*Sqr(g1)*Sqr(g2) + 2*Conj(Lambda6)*(-37*Lambda1*
      Lambda6 - 5*Lambda2*Lambda6 - 36*Lambda3*Lambda6 - 34*Lambda4*Lambda6 - 5
      *Lambda1*Lambda7 - 5*Lambda2*Lambda7 - 20*Lambda3*Lambda7 - 40*Lambda4*
      Lambda7 - 3*Lambda7*traceYdAdjYd - Lambda7*traceYeAdjYe - 3*Lambda7*
      traceYuAdjYu + (7*Lambda6 + 2*Lambda7)*Sqr(g1) + 27*Lambda6*Sqr(g2)) + 40
      *Lambda4*traceYdAdjYd*Sqr(g3) + 40*Lambda4*traceYuAdjYu*Sqr(g3) - 7*
      Lambda4*Sqr(Lambda1) - 7*Lambda4*Sqr(Lambda2) - 28*Lambda4*Sqr(Lambda3) -
      20*Lambda1*Sqr(Lambda4) - 20*Lambda2*Sqr(Lambda4) - 28*Lambda3*Sqr(
      Lambda4) - 12*traceYdAdjYd*Sqr(Lambda4) - 4*traceYeAdjYe*Sqr(Lambda4) -
      12*traceYuAdjYu*Sqr(Lambda4) + 8*Sqr(g1)*Sqr(Lambda4) + 18*Sqr(g2)*Sqr(
      Lambda4) - 40*Lambda5*Sqr(Lambda6) - 40*Lambda5*Sqr(Lambda7) - 2*Conj(
      Lambda5)*(24*Conj(Lambda6)*Conj(Lambda7) + Lambda5*(12*Lambda1 + 12*
      Lambda2 + 24*Lambda3 + 13*Lambda4 + 12*traceYdAdjYd + 4*traceYeAdjYe + 12
      *traceYuAdjYu - 8*Sqr(g1) - 27*Sqr(g2)) + 20*Sqr(Conj(Lambda6)) + 20*Sqr(
      Conj(Lambda7)))));


   return beta_Lambda4;
}

/**
 * Calculates the 3-loop beta function of Lambda4.
 *
 * @return 3-loop beta function
 */
double THDM_I_susy_parameters::calc_beta_Lambda4_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda4;

   beta_Lambda4 = 0;


   return beta_Lambda4;
}

} // namespace flexiblesusy
