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
 * Calculates the 1-loop beta function of LambdaS.
 *
 * @return 1-loop beta function
 */
double SSM_susy_parameters::calc_beta_LambdaS_1_loop(const Susy_traces& susy_traces) const
{


   double beta_LambdaS;

   beta_LambdaS = Re(oneOver16PiSqr*(Sqr(K2) + 36*Sqr(LambdaS)));


   return beta_LambdaS;
}

/**
 * Calculates the 2-loop beta function of LambdaS.
 *
 * @return 2-loop beta function
 */
double SSM_susy_parameters::calc_beta_LambdaS_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_LambdaS;

   beta_LambdaS = Re(twoLoop*(1.2*Sqr(g1)*Sqr(K2) + 6*Sqr(g2)*Sqr(K2) - 2
      *(2*Cube(K2) + 408*Cube(LambdaS) + (10*LambdaS + 3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu)*Sqr(K2))));


   return beta_LambdaS;
}

/**
 * Calculates the 3-loop beta function of LambdaS.
 *
 * @return 3-loop beta function
 */
double SSM_susy_parameters::calc_beta_LambdaS_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_LambdaS;

   beta_LambdaS = 0;


   return beta_LambdaS;
}

} // namespace flexiblesusy
