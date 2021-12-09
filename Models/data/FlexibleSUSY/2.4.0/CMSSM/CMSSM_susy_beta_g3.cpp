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

// File generated at Thu 10 Oct 2019 17:27:12

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of g3.
 *
 * @return 1-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g3_1_loop(const Susy_traces& susy_traces) const
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
double CMSSM_susy_parameters::calc_beta_g3_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_g3;

   beta_g3 = Re(0.2*twoLoop*Cube(g3)*(-20*traceYdAdjYd - 20*traceYuAdjYu + 11*
      Sqr(g1) + 45*Sqr(g2) + 70*Sqr(g3)));


   return beta_g3;
}

/**
 * Calculates the 3-loop beta function of g3.
 *
 * @return 3-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g3_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;


   double beta_g3;

   beta_g3 = Re(0.013333333333333334*threeLoop*Cube(g3)*(900*
      traceAdjYdYdAdjYdYd + 450*traceAdjYdYd*traceAdjYeYe + 600*
      traceAdjYuYuAdjYdYd + 900*traceAdjYuYuAdjYuYu - 1702*Quad(g1) - 2025*Quad
      (g2) + 8675*Quad(g3) - 160*traceAdjYdYd*Sqr(g1) - 220*traceAdjYuYu*Sqr(g1
      ) - 900*traceAdjYdYd*Sqr(g2) - 900*traceAdjYuYu*Sqr(g2) - 45*Sqr(g1)*Sqr(
      g2) - 2600*traceAdjYdYd*Sqr(g3) - 2600*traceAdjYuYu*Sqr(g3) + 110*Sqr(g1)
      *Sqr(g3) + 450*Sqr(g2)*Sqr(g3) + 1350*Sqr(traceAdjYdYd) + 1350*Sqr(
      traceAdjYuYu)));


   return beta_g3;
}

/**
 * Calculates the 4-loop beta function of g3.
 *
 * @return 4-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g3_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_g3;

   beta_g3 = 0;


   return beta_g3;
}

/**
 * Calculates the 5-loop beta function of g3.
 *
 * @return 5-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g3_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_g3;

   beta_g3 = 0;


   return beta_g3;
}

} // namespace flexiblesusy
