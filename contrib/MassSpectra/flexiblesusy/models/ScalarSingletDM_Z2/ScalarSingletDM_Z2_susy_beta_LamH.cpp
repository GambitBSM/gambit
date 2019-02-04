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

// File generated at Sat 26 May 2018 14:35:16

#include "ScalarSingletDM_Z2_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of LamH.
 *
 * @return 1-loop beta function
 */
double ScalarSingletDM_Z2_susy_parameters::calc_beta_LamH_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_LamH;

   beta_LamH = Re(oneOver16PiSqr*(12*LamH*traceYdAdjYd - 12*
      traceYdAdjYdYdAdjYd + 4*LamH*traceYeAdjYe - 4*traceYeAdjYeYeAdjYe + 12*
      LamH*traceYuAdjYu - 12*traceYuAdjYuYuAdjYu + 0.27*Quad(g1) + 2.25*Quad(g2
      ) - 9*LamH*Sqr(g2) + 0.9*Sqr(g1)*(-2*LamH + Sqr(g2)) + 12*Sqr(LamH) + Sqr
      (LamSH)));


   return beta_LamH;
}

/**
 * Calculates the 2-loop beta function of LamH.
 *
 * @return 2-loop beta function
 */
double ScalarSingletDM_Z2_susy_parameters::calc_beta_LamH_2_loop(const Susy_traces& susy_traces) const
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


   double beta_LamH;

   beta_LamH = Re(twoLoop*(-3*LamH*traceYdAdjYdYdAdjYd + 60*
      traceYdAdjYdYdAdjYdYdAdjYd - 24*traceYdAdjYdYdAdjYuYuAdjYd - 42*LamH*
      traceYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - 12*
      traceYdAdjYuYuAdjYuYuAdjYd - LamH*traceYeAdjYeYeAdjYe + 20*
      traceYeAdjYeYeAdjYeYeAdjYe - 3*LamH*traceYuAdjYuYuAdjYu + 60*
      traceYuAdjYuYuAdjYuYuAdjYu - 78*Cube(LamH) - 4*Cube(LamSH) - 3.411*Power6
      (g1) + 38.125*Power6(g2) - 0.125*(73*LamH + 12*(3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu))*Quad(g2) + 1.5*LamH*(36*LamH + 5*(3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu))*Sqr(g2) - 0.015*Quad(g1)*(
      -629*LamH - 60*traceYdAdjYd + 300*traceYeAdjYe + 228*traceYuAdjYu + 559*
      Sqr(g2)) + 80*LamH*traceYdAdjYd*Sqr(g3) - 64*traceYdAdjYdYdAdjYd*Sqr(g3)
      + 80*LamH*traceYuAdjYu*Sqr(g3) - 64*traceYuAdjYuYuAdjYu*Sqr(g3) - 72*
      traceYdAdjYd*Sqr(LamH) - 24*traceYeAdjYe*Sqr(LamH) - 72*traceYuAdjYu*Sqr(
      LamH) - 0.025*Sqr(g1)*(289*Quad(g2) - 6*(39*LamH + 36*traceYdAdjYd + 44*
      traceYeAdjYe + 84*traceYuAdjYu)*Sqr(g2) - 4*(5*LamH*(5*traceYdAdjYd + 15*
      traceYeAdjYe + 17*traceYuAdjYu) + 16*(traceYdAdjYdYdAdjYd - 3*
      traceYeAdjYeYeAdjYe - 2*traceYuAdjYuYuAdjYu) + 108*Sqr(LamH))) - 5*LamH*
      Sqr(LamSH)));


   return beta_LamH;
}

/**
 * Calculates the 3-loop beta function of LamH.
 *
 * @return 3-loop beta function
 */
double ScalarSingletDM_Z2_susy_parameters::calc_beta_LamH_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_LamH;

   beta_LamH = 0;


   return beta_LamH;
}

} // namespace flexiblesusy
