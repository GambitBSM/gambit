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

// File generated at Tue 31 Jul 2018 21:11:38

#include "THDM_II_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda1.
 *
 * @return 1-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_1_loop(const Susy_traces& susy_traces) const
{


   double beta_Lambda1;

   beta_Lambda1 = Re(0.25*oneOver16PiSqr*(3*Quad(g1) + 9*Quad(g2) - 36*
      Lambda1*Sqr(g2) + 6*Sqr(g1)*(-2*Lambda1 + Sqr(g2)) + 8*(2*Lambda3*Lambda4
      + 6*Sqr(Lambda1) + 2*Sqr(Lambda3) + Sqr(Lambda4) + Sqr(Lambda5) + 12*Sqr
      (Lambda6))));


   return beta_Lambda1;
}

/**
 * Calculates the 2-loop beta function of Lambda1.
 *
 * @return 2-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda1;

   beta_Lambda1 = Re(twoLoop*(-16.375*Power6(g1) + 36.375*Power6(g2) + (
      -6.375*Lambda1 + 7.5*(2*Lambda3 + Lambda4))*Quad(g2) + 0.125*Quad(g1)*(
      217*Lambda1 + 20*(2*Lambda3 + Lambda4) - 191*Sqr(g2)) + 6*Sqr(g2)*(4*
      Lambda3*Lambda4 + 9*Sqr(Lambda1) + 4*Sqr(Lambda3) + Sqr(Lambda4) + 18*Sqr
      (Lambda6)) + Sqr(g1)*(8*Lambda3*Lambda4 - 12.625*Quad(g2) + (9.75*Lambda1
      + 5*Lambda4)*Sqr(g2) + 18*Sqr(Lambda1) + 8*Sqr(Lambda3) + 4*Sqr(Lambda4)
      - 2*Sqr(Lambda5) + 36*Sqr(Lambda6)) - 2*(39*Cube(Lambda1) + Lambda1*(10*
      Lambda3*Lambda4 + 10*Sqr(Lambda3) + 6*Sqr(Lambda4) + 7*Sqr(Lambda5) + 159
      *Sqr(Lambda6) - 3*Sqr(Lambda7)) + 2*(10*Lambda5*Lambda6*Lambda7 + 4*Cube(
      Lambda3) + 3*Cube(Lambda4) + 2*(3*Lambda4 + 3*traceYdAdjYd + traceYeAdjYe
      + 3*traceYuAdjYu)*Sqr(Lambda3) + (3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu)*Sqr(Lambda4) + 3*traceYdAdjYd*Sqr(Lambda5) + traceYeAdjYe*
      Sqr(Lambda5) + 3*traceYuAdjYu*Sqr(Lambda5) + 37*Lambda5*Sqr(Lambda6) + 18
      *traceYdAdjYd*Sqr(Lambda6) + 6*traceYeAdjYe*Sqr(Lambda6) + 18*
      traceYuAdjYu*Sqr(Lambda6) + 5*Lambda5*Sqr(Lambda7) + Lambda3*(18*Lambda6*
      Lambda7 + 2*Lambda4*(3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) + 8*
      Sqr(Lambda4) + 10*Sqr(Lambda5) + 33*Sqr(Lambda6) + 9*Sqr(Lambda7)) +
      Lambda4*(11*Sqr(Lambda5) + 7*(2*Lambda6*Lambda7 + 5*Sqr(Lambda6) + Sqr(
      Lambda7)))))));


   return beta_Lambda1;
}

/**
 * Calculates the 3-loop beta function of Lambda1.
 *
 * @return 3-loop beta function
 */
double THDM_II_susy_parameters::calc_beta_Lambda1_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda1;

   beta_Lambda1 = 0;


   return beta_Lambda1;
}

} // namespace flexiblesusy
