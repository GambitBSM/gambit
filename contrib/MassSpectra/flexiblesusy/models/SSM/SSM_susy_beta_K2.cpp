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

// File generated at Thu 10 May 2018 14:43:15

#include "SSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of K2.
 *
 * @return 1-loop beta function
 */
double SSM_susy_parameters::calc_beta_K2_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_K2;

   beta_K2 = Re(0.1*K2*oneOver16PiSqr*(20*(2*K2 + 6*LambdaS + 3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu + 3*Lambdax) - 9*Sqr(g1) -
      45*Sqr(g2)));


   return beta_K2;
}

/**
 * Calculates the 2-loop beta function of K2.
 *
 * @return 2-loop beta function
 */
double SSM_susy_parameters::calc_beta_K2_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_K2;

   beta_K2 = Re(0.0025*K2*twoLoop*(1671*Quad(g1) + 10*Sqr(g1)*(24*K2 + 50
      *traceYdAdjYd + 150*traceYeAdjYe + 170*traceYuAdjYu + 288*Lambdax + 45*
      Sqr(g2)) - 25*(145*Quad(g2) - 12*(4*K2 + 15*traceYdAdjYd + 5*traceYeAdjYe
      + 15*traceYuAdjYu + 48*Lambdax)*Sqr(g2) + 8*(27*traceYdAdjYdYdAdjYd + 42
      *traceYdAdjYuYuAdjYd + 9*traceYeAdjYeYeAdjYe + 27*traceYuAdjYuYuAdjYu +
      72*traceYdAdjYd*Lambdax + 24*traceYeAdjYe*Lambdax + 72*traceYuAdjYu*
      Lambdax + 8*K2*(18*LambdaS + 3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu + 9*Lambdax) - 80*traceYdAdjYd*Sqr(g3) - 80*traceYuAdjYu*Sqr
      (g3) + 21*Sqr(K2) + 240*Sqr(LambdaS) + 30*Sqr(Lambdax)))));


   return beta_K2;
}

/**
 * Calculates the 3-loop beta function of K2.
 *
 * @return 3-loop beta function
 */
double SSM_susy_parameters::calc_beta_K2_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_K2;

   beta_K2 = 0;


   return beta_K2;
}

} // namespace flexiblesusy
