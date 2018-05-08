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

// File generated at Wed 29 Mar 2017 15:35:44

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Lambda5.
 *
 * @return one-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda5;

   beta_Lambda5 = Re(oneOver16PiSqr*(2*Lambda1*Lambda5 + 2*Lambda2*
      Lambda5 + 8*Lambda3*Lambda5 + 12*Lambda4*Lambda5 + 4*Lambda6*Lambda7 + 6*
      Lambda5*traceYdAdjYd + 2*Lambda5*traceYeAdjYe + 6*Lambda5*traceYuAdjYu -
      3*Lambda5*Sqr(g1) - 9*Lambda5*Sqr(g2) + 10*Sqr(Lambda6) + 10*Sqr(Lambda7)
      ));


   return beta_Lambda5;
}

/**
 * Calculates the two-loop beta function of Lambda5.
 *
 * @return two-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda5;

   beta_Lambda5 = Re(twoLoop*(19.625*Power(g1,4)*Lambda5 - 28.875*Power(
      g2,4)*Lambda5 - 40*Lambda1*Lambda3*Lambda5 - 40*Lambda2*Lambda3*Lambda5 -
      44*Lambda1*Lambda4*Lambda5 - 44*Lambda2*Lambda4*Lambda5 - 76*Lambda3*
      Lambda4*Lambda5 + 6*Power(Lambda5,3) - 20*Lambda1*Lambda6*Lambda7 - 20*
      Lambda2*Lambda6*Lambda7 - 80*Lambda3*Lambda6*Lambda7 - 88*Lambda4*Lambda6
      *Lambda7 - 168*Lambda5*Lambda6*Lambda7 - 1.5*Lambda5*traceYdAdjYdYdAdjYd
      - 33*Lambda5*traceYdAdjYuYuAdjYd - 0.5*Lambda5*traceYeAdjYeYeAdjYe - 12*
      Lambda2*Lambda5*traceYuAdjYu - 24*Lambda3*Lambda5*traceYuAdjYu - 36*
      Lambda4*Lambda5*traceYuAdjYu - 12*Lambda6*Lambda7*traceYuAdjYu - 1.5*
      Lambda5*traceYuAdjYuYuAdjYu - 2*Lambda1*Lambda5*Sqr(g1) - 2*Lambda2*
      Lambda5*Sqr(g1) + 16*Lambda3*Lambda5*Sqr(g1) + 24*Lambda4*Lambda5*Sqr(g1)
      - 4*Lambda6*Lambda7*Sqr(g1) + 7.083333333333333*Lambda5*traceYuAdjYu*Sqr
      (g1) + 36*Lambda3*Lambda5*Sqr(g2) + 72*Lambda4*Lambda5*Sqr(g2) + 11.25*
      Lambda5*traceYuAdjYu*Sqr(g2) + 4.75*Lambda5*Sqr(g1)*Sqr(g2) + 40*Lambda5*
      traceYuAdjYu*Sqr(g3) - 7*Lambda5*Sqr(Lambda1) - 7*Lambda5*Sqr(Lambda2) -
      28*Lambda5*Sqr(Lambda3) - 32*Lambda5*Sqr(Lambda4) - 74*Lambda1*Sqr(
      Lambda6) - 10*Lambda2*Sqr(Lambda6) - 72*Lambda3*Sqr(Lambda6) - 76*Lambda4
      *Sqr(Lambda6) - 72*Lambda5*Sqr(Lambda6) + 20*Sqr(g1)*Sqr(Lambda6) + 54*
      Sqr(g2)*Sqr(Lambda6) + 0.25*traceYeAdjYe*(25*Lambda5*Sqr(g1) + 15*Lambda5
      *Sqr(g2) - 16*(Lambda1*Lambda5 + 2*Lambda3*Lambda5 + 3*Lambda4*Lambda5 +
      Lambda6*Lambda7 + 5*Sqr(Lambda6))) + 0.08333333333333333*traceYdAdjYd*(25
      *Lambda5*Sqr(g1) + 3*(45*Lambda5*Sqr(g2) + 16*(10*Lambda5*Sqr(g3) - 3*(
      Lambda1*Lambda5 + 2*Lambda3*Lambda5 + 3*Lambda4*Lambda5 + Lambda6*Lambda7
      + 5*Sqr(Lambda6))))) - 10*Lambda1*Sqr(Lambda7) - 74*Lambda2*Sqr(Lambda7)
      - 72*Lambda3*Sqr(Lambda7) - 76*Lambda4*Sqr(Lambda7) - 72*Lambda5*Sqr(
      Lambda7) - 60*traceYuAdjYu*Sqr(Lambda7) + 20*Sqr(g1)*Sqr(Lambda7) + 54*
      Sqr(g2)*Sqr(Lambda7)));


   return beta_Lambda5;
}

/**
 * Calculates the three-loop beta function of Lambda5.
 *
 * @return three-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda5_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda5;

   beta_Lambda5 = 0;


   return beta_Lambda5;
}

} // namespace flexiblesusy
