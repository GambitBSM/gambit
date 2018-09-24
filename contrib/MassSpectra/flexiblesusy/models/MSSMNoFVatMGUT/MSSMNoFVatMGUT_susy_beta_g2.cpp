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

// File generated at Thu 10 May 2018 14:49:54

#include "MSSMNoFVatMGUT_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of g2.
 *
 * @return 1-loop beta function
 */
double MSSMNoFVatMGUT_susy_parameters::calc_beta_g2_1_loop(const Susy_traces& susy_traces) const
{


   double beta_g2;

   beta_g2 = Re(oneOver16PiSqr*Cube(g2));


   return beta_g2;
}

/**
 * Calculates the 2-loop beta function of g2.
 *
 * @return 2-loop beta function
 */
double MSSMNoFVatMGUT_susy_parameters::calc_beta_g2_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_g2;

   beta_g2 = Re(0.2*twoLoop*Cube(g2)*(9*Sqr(g1) + 5*(-2*(3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu) + 25*Sqr(g2) + 24*Sqr(g3))));


   return beta_g2;
}

/**
 * Calculates the 3-loop beta function of g2.
 *
 * @return 3-loop beta function
 */
double MSSMNoFVatMGUT_susy_parameters::calc_beta_g2_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;


   double beta_g2;

   beta_g2 = Re(0.04*threeLoop*Cube(g2)*(-457*Quad(g1) + 5*Sqr(g1)*(-11*
      traceAdjYdYd - 21*traceAdjYeYe - 29*traceAdjYuYu + 9*Sqr(g2) - 8*Sqr(g3))
      + 25*(35*Quad(g2) + Sqr(g2)*(-11*(3*traceAdjYdYd + traceAdjYeYe + 3*
      traceAdjYuYu) + 24*Sqr(g3)) + 2*(12*traceAdjYdYdAdjYdYd + 6*traceAdjYdYd*
      traceAdjYeYe + 4*traceAdjYeYeAdjYeYe + 6*traceAdjYuYuAdjYdYd + 12*
      traceAdjYuYuAdjYuYu + 22*Quad(g3) - 16*(traceAdjYdYd + traceAdjYuYu)*Sqr(
      g3) + 9*Sqr(traceAdjYdYd) + Sqr(traceAdjYeYe) + 9*Sqr(traceAdjYuYu)))));


   return beta_g2;
}

} // namespace flexiblesusy
