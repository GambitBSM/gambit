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

// File generated at Thu 10 May 2018 14:42:26

#include "SingletDMZ3_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of LamSH.
 *
 * @return 1-loop beta function
 */
double SingletDMZ3_susy_parameters::calc_beta_LamSH_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_LamSH;

   beta_LamSH = Re(0.1*LamSH*oneOver16PiSqr*(20*(3*LamH + LamS + LamSH +
      3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) - 9*Sqr(g1) - 45*Sqr(g2))
      );


   return beta_LamSH;
}

/**
 * Calculates the 2-loop beta function of LamSH.
 *
 * @return 2-loop beta function
 */
double SingletDMZ3_susy_parameters::calc_beta_LamSH_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_LamSH;

   beta_LamSH = Re(0.0025*LamSH*twoLoop*(1671*Quad(g1) + 10*Sqr(g1)*(2*(
      144*LamH + 6*LamSH + 25*traceYdAdjYd + 75*traceYeAdjYe + 85*traceYuAdjYu)
      + 45*Sqr(g2)) - 25*(145*Quad(g2) - 12*(48*LamH + 2*LamSH + 5*(3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu))*Sqr(g2) + 4*(24*LamS*LamSH
      + 24*LamSH*traceYdAdjYd + 54*traceYdAdjYdYdAdjYd + 84*
      traceYdAdjYuYuAdjYd + 8*LamSH*traceYeAdjYe + 18*traceYeAdjYeYeAdjYe + 24*
      LamSH*traceYuAdjYu + 24*LamH*(3*LamSH + 6*traceYdAdjYd + 2*traceYeAdjYe +
      6*traceYuAdjYu) + 54*traceYuAdjYuYuAdjYu - 160*traceYdAdjYd*Sqr(g3) -
      160*traceYuAdjYu*Sqr(g3) + 60*Sqr(LamH) + 10*Sqr(LamS) + 11*Sqr(LamSH))))
      );


   return beta_LamSH;
}

/**
 * Calculates the 3-loop beta function of LamSH.
 *
 * @return 3-loop beta function
 */
double SingletDMZ3_susy_parameters::calc_beta_LamSH_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_LamSH;

   beta_LamSH = 0;


   return beta_LamSH;
}

} // namespace flexiblesusy
