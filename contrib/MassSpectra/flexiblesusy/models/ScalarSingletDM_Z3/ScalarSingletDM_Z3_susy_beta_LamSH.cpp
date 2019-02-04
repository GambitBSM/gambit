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

// File generated at Sat 26 May 2018 14:35:36

#include "ScalarSingletDM_Z3_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of LamSH.
 *
 * @return 1-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamSH_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_LamSH;

   beta_LamSH = Re(0.1*LamSH*oneOver16PiSqr*(20*(3*LamH + 4*LamS + 2*
      LamSH + 3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) - 9*Sqr(g1) - 45*
      Sqr(g2)));


   return beta_LamSH;
}

/**
 * Calculates the 2-loop beta function of LamSH.
 *
 * @return 2-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamSH_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_LamSH;

   beta_LamSH = Re(0.0025*LamSH*twoLoop*(1671*Quad(g1) + 10*Sqr(g1)*(288*
      LamH + 24*LamSH + 50*traceYdAdjYd + 150*traceYeAdjYe + 170*traceYuAdjYu +
      45*Sqr(g2)) - 25*(145*Quad(g2) - 12*(48*LamH + 4*LamSH + 5*(3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu))*Sqr(g2) + 8*(96*LamS*LamSH
      + 24*LamSH*traceYdAdjYd + 27*traceYdAdjYdYdAdjYd + 42*
      traceYdAdjYuYuAdjYd + 8*LamSH*traceYeAdjYe + 9*traceYeAdjYeYeAdjYe + 24*
      LamSH*traceYuAdjYu + 24*LamH*(3*LamSH + 3*traceYdAdjYd + traceYeAdjYe + 3
      *traceYuAdjYu) + 27*traceYuAdjYuYuAdjYu - 80*traceYdAdjYd*Sqr(g3) - 80*
      traceYuAdjYu*Sqr(g3) + 30*Sqr(LamH) + 80*Sqr(LamS) + 22*Sqr(LamSH)))));


   return beta_LamSH;
}

/**
 * Calculates the 3-loop beta function of LamSH.
 *
 * @return 3-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamSH_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_LamSH;

   beta_LamSH = 0;


   return beta_LamSH;
}

} // namespace flexiblesusy
