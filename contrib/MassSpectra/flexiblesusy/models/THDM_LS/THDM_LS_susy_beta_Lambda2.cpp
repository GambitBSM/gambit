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

// File generated at Tue 7 Apr 2020 14:55:42

#include "THDM_LS_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda2.
 *
 * @return 1-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda2_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(oneOver16PiSqr*(4*Lambda3*Lambda4 + 12*Lambda2*
      traceYdAdjYd - 12*traceYdAdjYdYdAdjYd + 12*Lambda2*traceYuAdjYu - 12*
      traceYuAdjYuYuAdjYu + 2*AbsSqr(Lambda5) + 24*AbsSqr(Lambda7) + 0.75*Quad(
      g1) + 2.25*Quad(g2) - 3*Lambda2*Sqr(g1) - 9*Lambda2*Sqr(g2) + 1.5*Sqr(g1)
      *Sqr(g2) + 12*Sqr(Lambda2) + 4*Sqr(Lambda3) + 2*Sqr(Lambda4)));


   return beta_Lambda2;
}

/**
 * Calculates the 2-loop beta function of Lambda2.
 *
 * @return 2-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda2_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYdYdAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYuYuAdjYu =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYu;


   double beta_Lambda2;

   beta_Lambda2 = Re(twoLoop*(-20*Lambda2*Lambda3*Lambda4 - 20*Lambda5*
      Lambda6*Lambda7 - 3*Lambda2*traceYdAdjYdYdAdjYd + 60*
      traceYdAdjYdYdAdjYdYdAdjYd - 24*traceYdAdjYdYdAdjYuYuAdjYd - 42*Lambda2*
      traceYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - 12*
      traceYdAdjYuYuAdjYuYuAdjYd - 8*Lambda3*Lambda4*traceYeAdjYe - 3*Lambda2*
      traceYuAdjYuYuAdjYu + 60*traceYuAdjYuYuAdjYuYuAdjYu - 318*Lambda2*AbsSqr(
      Lambda7) - 132*Lambda3*AbsSqr(Lambda7) - 140*Lambda4*AbsSqr(Lambda7) - 72
      *traceYdAdjYd*AbsSqr(Lambda7) - 24*traceYeAdjYe*AbsSqr(Lambda7) - 72*
      traceYuAdjYu*AbsSqr(Lambda7) + (6*Lambda2*Lambda6 - 4*(9*Lambda3 + 7*
      Lambda4)*(Lambda6 + Lambda7))*Conj(Lambda6) - 36*Lambda3*Lambda6*Conj(
      Lambda7) - 28*Lambda4*Lambda6*Conj(Lambda7) - 78*Cube(Lambda2) - 16*Cube(
      Lambda3) - 12*Cube(Lambda4) - 16.375*Power6(g1) + 36.375*Power6(g2) +
      27.125*Lambda2*Quad(g1) + 5*Lambda3*Quad(g1) + 2.5*Lambda4*Quad(g1) + 2.5
      *traceYdAdjYd*Quad(g1) - 9.5*traceYuAdjYu*Quad(g1) - 6.375*Lambda2*Quad(
      g2) + 15*Lambda3*Quad(g2) + 7.5*Lambda4*Quad(g2) - 4.5*traceYdAdjYd*Quad(
      g2) - 4.5*traceYuAdjYu*Quad(g2) + 8*Lambda3*Lambda4*Sqr(g1) +
      4.166666666666667*Lambda2*traceYdAdjYd*Sqr(g1) + 2.6666666666666665*
      traceYdAdjYdYdAdjYd*Sqr(g1) + 14.166666666666666*Lambda2*traceYuAdjYu*Sqr
      (g1) - 5.333333333333333*traceYuAdjYuYuAdjYu*Sqr(g1) + 36*AbsSqr(Lambda7)
      *Sqr(g1) - 12.625*Quad(g2)*Sqr(g1) + 24*Lambda3*Lambda4*Sqr(g2) + 22.5*
      Lambda2*traceYdAdjYd*Sqr(g2) + 22.5*Lambda2*traceYuAdjYu*Sqr(g2) + 108*
      AbsSqr(Lambda7)*Sqr(g2) - 23.875*Quad(g1)*Sqr(g2) + 9.75*Lambda2*Sqr(g1)*
      Sqr(g2) + 5*Lambda4*Sqr(g1)*Sqr(g2) + 9*traceYdAdjYd*Sqr(g1)*Sqr(g2) + 21
      *traceYuAdjYu*Sqr(g1)*Sqr(g2) + 80*Lambda2*traceYdAdjYd*Sqr(g3) - 64*
      traceYdAdjYdYdAdjYd*Sqr(g3) + 80*Lambda2*traceYuAdjYu*Sqr(g3) - 64*
      traceYuAdjYuYuAdjYu*Sqr(g3) - 72*traceYdAdjYd*Sqr(Lambda2) - 72*
      traceYuAdjYu*Sqr(Lambda2) + 18*Sqr(g1)*Sqr(Lambda2) + 54*Sqr(g2)*Sqr(
      Lambda2) - 20*Lambda2*Sqr(Lambda3) - 24*Lambda4*Sqr(Lambda3) - 8*
      traceYeAdjYe*Sqr(Lambda3) + 8*Sqr(g1)*Sqr(Lambda3) + 24*Sqr(g2)*Sqr(
      Lambda3) - 12*Lambda2*Sqr(Lambda4) - 32*Lambda3*Sqr(Lambda4) - 4*
      traceYeAdjYe*Sqr(Lambda4) + 4*Sqr(g1)*Sqr(Lambda4) + 6*Sqr(g2)*Sqr(
      Lambda4) - 10*Lambda5*Sqr(Lambda6) - 74*Lambda5*Sqr(Lambda7) - 2*Conj(
      Lambda5)*(10*Conj(Lambda6)*Conj(Lambda7) + Lambda5*(7*Lambda2 + 20*
      Lambda3 + 22*Lambda4 + 2*traceYeAdjYe + Sqr(g1)) + 5*Sqr(Conj(Lambda6)) +
      37*Sqr(Conj(Lambda7)))));


   return beta_Lambda2;
}

/**
 * Calculates the 3-loop beta function of Lambda2.
 *
 * @return 3-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda2_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda2;

   beta_Lambda2 = 0;


   return beta_Lambda2;
}

} // namespace flexiblesusy
