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

// File generated at Thu 10 May 2018 14:43:38

#include "HSSUSY_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of g1.
 *
 * @return 1-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_g1_1_loop(const Susy_traces& susy_traces) const
{


   double beta_g1;

   beta_g1 = Re(4.1*oneOver16PiSqr*Cube(g1));


   return beta_g1;
}

/**
 * Calculates the 2-loop beta function of g1.
 *
 * @return 2-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_g1_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_g1;

   beta_g1 = Re(0.02*twoLoop*Cube(g1)*(199*Sqr(g1) + 5*(-5*traceYdAdjYd -
      15*traceYeAdjYe - 17*traceYuAdjYu + 27*Sqr(g2) + 88*Sqr(g3))));


   return beta_g1;
}

/**
 * Calculates the 3-loop beta function of g1.
 *
 * @return 3-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_g1_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_g1;

   beta_g1 = Re(0.000041666666666666665*threeLoop*(-388613*Power7(g1) +
      10*Power5(g1)*(648*Lambdax + 1845*Sqr(g2) - 4384*Sqr(g3) - 8481*Sqr(Yu(2,
      2))) + 75*Cube(g1)*(3945*Quad(g2) - 6*Sqr(g2)*(-24*Lambdax + 32*Sqr(g3) +
      785*Sqr(Yu(2,2))) + 4*(4752*Quad(g3) + 945*Quad(Yu(2,2)) - 36*Sqr(
      Lambdax) - 464*Sqr(g3)*Sqr(Yu(2,2))))));


   return beta_g1;
}

} // namespace flexiblesusy
