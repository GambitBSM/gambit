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

// File generated at Thu 10 Oct 2019 17:27:11

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of g1.
 *
 * @return 1-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g1_1_loop(const Susy_traces& susy_traces) const
{


   double beta_g1;

   beta_g1 = Re(6.6*oneOver16PiSqr*Cube(g1));


   return beta_g1;
}

/**
 * Calculates the 2-loop beta function of g1.
 *
 * @return 2-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g1_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_g1;

   beta_g1 = Re(0.04*twoLoop*Cube(g1)*(-70*traceYdAdjYd - 90*traceYeAdjYe - 130
      *traceYuAdjYu + 199*Sqr(g1) + 135*Sqr(g2) + 440*Sqr(g3)));


   return beta_g1;
}

/**
 * Calculates the 3-loop beta function of g1.
 *
 * @return 3-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g1_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;


   double beta_g1;

   beta_g1 = Re(-0.0026666666666666666*threeLoop*Cube(g1)*(-4050*
      traceAdjYdYdAdjYdYd - 6300*traceAdjYdYd*traceAdjYeYe - 4050*
      traceAdjYeYeAdjYeYe - 4350*traceAdjYuYuAdjYdYd - 6300*traceAdjYuYuAdjYuYu
       + 32117*Quad(g1) + 6075*Quad(g2) - 12100*Quad(g3) + 245*traceAdjYdYd*Sqr
      (g1) + 1215*traceAdjYeYe*Sqr(g1) + 845*traceAdjYuYu*Sqr(g1) + 2475*
      traceAdjYdYd*Sqr(g2) + 4725*traceAdjYeYe*Sqr(g2) + 6525*traceAdjYuYu*Sqr(
      g2) + 1035*Sqr(g1)*Sqr(g2) + 6400*traceAdjYdYd*Sqr(g3) + 8800*
      traceAdjYuYu*Sqr(g3) + 5480*Sqr(g1)*Sqr(g3) + 1800*Sqr(g2)*Sqr(g3) - 2700
      *Sqr(traceAdjYdYd) - 1800*Sqr(traceAdjYeYe) - 6750*Sqr(traceAdjYuYu)));


   return beta_g1;
}

/**
 * Calculates the 4-loop beta function of g1.
 *
 * @return 4-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g1_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_g1;

   beta_g1 = 0;


   return beta_g1;
}

/**
 * Calculates the 5-loop beta function of g1.
 *
 * @return 5-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_g1_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_g1;

   beta_g1 = 0;


   return beta_g1;
}

} // namespace flexiblesusy
