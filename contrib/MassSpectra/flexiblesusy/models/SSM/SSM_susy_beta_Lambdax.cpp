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

// File generated at Thu 10 May 2018 14:43:16

#include "SSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambdax.
 *
 * @return 1-loop beta function
 */
double SSM_susy_parameters::calc_beta_Lambdax_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambdax;

   beta_Lambdax = Re(oneOver16PiSqr*(-12*traceYdAdjYdYdAdjYd - 4*
      traceYeAdjYeYeAdjYe - 12*traceYuAdjYuYuAdjYu + 12*traceYdAdjYd*Lambdax +
      4*traceYeAdjYe*Lambdax + 12*traceYuAdjYu*Lambdax + 0.27*Quad(g1) + 2.25*
      Quad(g2) - 9*Lambdax*Sqr(g2) + 0.9*Sqr(g1)*(-2*Lambdax + Sqr(g2)) + Sqr(
      K2) + 12*Sqr(Lambdax)));


   return beta_Lambdax;
}

/**
 * Calculates the 2-loop beta function of Lambdax.
 *
 * @return 2-loop beta function
 */
double SSM_susy_parameters::calc_beta_Lambdax_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYdYdAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYeYeAdjYe =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYuYuAdjYu =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYu;


   double beta_Lambdax;

   beta_Lambdax = Re(twoLoop*(60*traceYdAdjYdYdAdjYdYdAdjYd - 24*
      traceYdAdjYdYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - 12*
      traceYdAdjYuYuAdjYuYuAdjYd + 20*traceYeAdjYeYeAdjYeYeAdjYe + 60*
      traceYuAdjYuYuAdjYuYuAdjYu - 4*Cube(K2) - 78*Cube(Lambdax) - 3*
      traceYdAdjYdYdAdjYd*Lambdax - 42*traceYdAdjYuYuAdjYd*Lambdax -
      traceYeAdjYeYeAdjYe*Lambdax - 3*traceYuAdjYuYuAdjYu*Lambdax - 3.411*
      Power6(g1) + 38.125*Power6(g2) - 0.125*(36*traceYdAdjYd + 12*traceYeAdjYe
      + 36*traceYuAdjYu + 73*Lambdax)*Quad(g2) + 1.5*Lambdax*(15*traceYdAdjYd
      + 5*traceYeAdjYe + 15*traceYuAdjYu + 36*Lambdax)*Sqr(g2) - 0.015*Quad(g1)
      *(-60*traceYdAdjYd + 300*traceYeAdjYe + 228*traceYuAdjYu - 629*Lambdax +
      559*Sqr(g2)) - 64*traceYdAdjYdYdAdjYd*Sqr(g3) - 64*traceYuAdjYuYuAdjYu*
      Sqr(g3) + 80*traceYdAdjYd*Lambdax*Sqr(g3) + 80*traceYuAdjYu*Lambdax*Sqr(
      g3) - 5*Lambdax*Sqr(K2) - 72*traceYdAdjYd*Sqr(Lambdax) - 24*traceYeAdjYe*
      Sqr(Lambdax) - 72*traceYuAdjYu*Sqr(Lambdax) - 0.025*Sqr(g1)*(289*Quad(g2)
      - 6*(36*traceYdAdjYd + 44*traceYeAdjYe + 84*traceYuAdjYu + 39*Lambdax)*
      Sqr(g2) - 4*(16*traceYdAdjYdYdAdjYd - 48*traceYeAdjYeYeAdjYe - 32*
      traceYuAdjYuYuAdjYu + 25*traceYdAdjYd*Lambdax + 75*traceYeAdjYe*Lambdax +
      85*traceYuAdjYu*Lambdax + 108*Sqr(Lambdax)))));


   return beta_Lambdax;
}

/**
 * Calculates the 3-loop beta function of Lambdax.
 *
 * @return 3-loop beta function
 */
double SSM_susy_parameters::calc_beta_Lambdax_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambdax;

   beta_Lambdax = 0;


   return beta_Lambdax;
}

} // namespace flexiblesusy
