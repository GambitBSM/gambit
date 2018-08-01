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

// File generated at Wed 1 Aug 2018 14:15:30

#include "THDM_II_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda5.
 *
 * @return 1-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda5;

   beta_Lambda5 = Re(oneOver16PiSqr*(-3*Lambda5*Sqr(g1) - 9*Lambda5*Sqr(
      g2) + 2*(Lambda1*Lambda5 + Lambda2*Lambda5 + 4*Lambda3*Lambda5 + 6*
      Lambda4*Lambda5 + 2*Lambda6*Lambda7 + 3*Lambda5*traceYdAdjYd + Lambda5*
      traceYeAdjYe + 3*Lambda5*traceYuAdjYu + 5*Sqr(Lambda6) + 5*Sqr(Lambda7)))
      );


   return beta_Lambda5;
}

/**
 * Calculates the 2-loop beta function of Lambda5.
 *
 * @return 2-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_2_loop(const Susy_traces& susy_traces) const
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
      - 76*Lambda3*Lambda4*Lambda5 - 20*Lambda1*Lambda6*Lambda7 - 20*Lambda2*
      Lambda6*Lambda7 - 80*Lambda3*Lambda6*Lambda7 - 88*Lambda4*Lambda6*Lambda7
      - 168*Lambda5*Lambda6*Lambda7 - 12*Lambda1*Lambda5*traceYdAdjYd - 24*
      Lambda3*Lambda5*traceYdAdjYd - 36*Lambda4*Lambda5*traceYdAdjYd - 12*
      Lambda6*Lambda7*traceYdAdjYd - 1.5*Lambda5*traceYdAdjYdYdAdjYd - 33*
      Lambda5*traceYdAdjYuYuAdjYd - 4*Lambda1*Lambda5*traceYeAdjYe - 8*Lambda3*
      Lambda5*traceYeAdjYe - 12*Lambda4*Lambda5*traceYeAdjYe - 4*Lambda6*
      Lambda7*traceYeAdjYe - 0.5*Lambda5*traceYeAdjYeYeAdjYe - 12*Lambda2*
      Lambda5*traceYuAdjYu - 24*Lambda3*Lambda5*traceYuAdjYu - 36*Lambda4*
      Lambda5*traceYuAdjYu - 12*Lambda6*Lambda7*traceYuAdjYu - 1.5*Lambda5*
      traceYuAdjYuYuAdjYu + 6*Cube(Lambda5) + 19.625*Lambda5*Quad(g1) - 28.875*
      Lambda5*Quad(g2) + 40*Lambda5*traceYdAdjYd*Sqr(g3) + 40*Lambda5*
      traceYuAdjYu*Sqr(g3) - 7*Lambda5*Sqr(Lambda1) - 7*Lambda5*Sqr(Lambda2) -
      28*Lambda5*Sqr(Lambda3) - 32*Lambda5*Sqr(Lambda4) - 74*Lambda1*Sqr(
      Lambda6) - 10*Lambda2*Sqr(Lambda6) - 72*Lambda3*Sqr(Lambda6) - 76*Lambda4
      *Sqr(Lambda6) - 72*Lambda5*Sqr(Lambda6) - 60*traceYdAdjYd*Sqr(Lambda6) -
      20*traceYeAdjYe*Sqr(Lambda6) - 10*Lambda1*Sqr(Lambda7) - 74*Lambda2*Sqr(
      Lambda7) - 72*Lambda3*Sqr(Lambda7) - 76*Lambda4*Sqr(Lambda7) - 72*Lambda5
      *Sqr(Lambda7) - 60*traceYuAdjYu*Sqr(Lambda7) + Sqr(g1)*(-2*Lambda1*
      Lambda5 - 2*Lambda2*Lambda5 + 16*Lambda3*Lambda5 + 24*Lambda4*Lambda5 - 4
      *Lambda6*Lambda7 + 2.0833333333333335*Lambda5*traceYdAdjYd + 6.25*Lambda5
      *traceYeAdjYe + 7.083333333333333*Lambda5*traceYuAdjYu + 4.75*Lambda5*Sqr
      (g2) + 20*Sqr(Lambda6) + 20*Sqr(Lambda7)) + 0.75*Sqr(g2)*(48*Lambda3*
      Lambda5 + 96*Lambda4*Lambda5 + 15*Lambda5*traceYdAdjYd + 5*Lambda5*
      traceYeAdjYe + 15*Lambda5*traceYuAdjYu + 72*Sqr(Lambda6) + 72*Sqr(Lambda7
      ))));


   return beta_Lambda5;
}

/**
 * Calculates the 3-loop beta function of Lambda5.
 *
 * @return 3-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda5;

   beta_Lambda5 = 0;


   return beta_Lambda5;
}

} // namespace flexiblesusy
