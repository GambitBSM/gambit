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

// File generated at Thu 10 May 2018 15:08:03

#include "MSSMatMGUT_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of g3.
 *
 * @return 1-loop beta function
 */
double MSSMatMGUT_susy_parameters::calc_beta_g3_1_loop(const Susy_traces& susy_traces) const
{


   double beta_g3;

   beta_g3 = Re(-3*oneOver16PiSqr*Cube(g3));


   return beta_g3;
}

/**
 * Calculates the 2-loop beta function of g3.
 *
 * @return 2-loop beta function
 */
double MSSMatMGUT_susy_parameters::calc_beta_g3_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_g3;

   beta_g3 = Re(0.2*twoLoop*Cube(g3)*(11*Sqr(g1) + 5*(-4*traceYdAdjYd - 4
      *traceYuAdjYu + 9*Sqr(g2) + 14*Sqr(g3))));


   return beta_g3;
}

/**
 * Calculates the 3-loop beta function of g3.
 *
 * @return 3-loop beta function
 */
double MSSMatMGUT_susy_parameters::calc_beta_g3_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;


   double beta_g3;

   beta_g3 = Re(0.013333333333333334*threeLoop*Cube(g3)*(-1702*Quad(g1) -
      5*Sqr(g1)*(32*traceAdjYdYd + 44*traceAdjYuYu + 9*Sqr(g2) - 22*Sqr(g3)) -
      25*(81*Quad(g2) - 347*Quad(g3) + 104*(traceAdjYdYd + traceAdjYuYu)*Sqr(
      g3) - 18*Sqr(g2)*(-2*(traceAdjYdYd + traceAdjYuYu) + Sqr(g3)) - 6*(6*
      traceAdjYdYdAdjYdYd + 3*traceAdjYdYd*traceAdjYeYe + 4*traceAdjYuYuAdjYdYd
      + 6*traceAdjYuYuAdjYuYu + 9*Sqr(traceAdjYdYd) + 9*Sqr(traceAdjYuYu)))));


   return beta_g3;
}

} // namespace flexiblesusy
