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
 * Calculates the 1-loop beta function of LamS.
 *
 * @return 1-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamS_1_loop(const Susy_traces& susy_traces) const
{


   double beta_LamS;

   beta_LamS = Re(2*oneOver16PiSqr*(10*Sqr(LamS) + Sqr(LamSH)));


   return beta_LamS;
}

/**
 * Calculates the 2-loop beta function of LamS.
 *
 * @return 2-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamS_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_LamS;

   beta_LamS = Re(-0.8*twoLoop*(300*Cube(LamS) + 25*LamS*Sqr(LamSH) + (-3
      *Sqr(g1) + 5*(2*LamSH + 3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu -
      3*Sqr(g2)))*Sqr(LamSH)));


   return beta_LamS;
}

/**
 * Calculates the 3-loop beta function of LamS.
 *
 * @return 3-loop beta function
 */
double ScalarSingletDM_Z3_susy_parameters::calc_beta_LamS_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_LamS;

   beta_LamS = 0;


   return beta_LamS;
}

} // namespace flexiblesusy
