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

// File generated at Thu 10 May 2018 14:43:39

#include "HSSUSY_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> HSSUSY_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(Yu*(3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu - 0.85*Sqr(g1) - 2.25*Sqr(g2) - 8*Sqr(g3)) - 1.5*(Yu*
      Yd.adjoint()*Yd) + 1.5*(Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> HSSUSY_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(0.0016666666666666668*Yu*(1187*Quad(g1) + 5*Sqr(g1
      )*(75*traceYdAdjYd + 225*traceYeAdjYe + 255*traceYuAdjYu - 54*Sqr(g2) +
      152*Sqr(g3)) - 75*(46*Quad(g2) + 864*Quad(g3) - 160*(traceYdAdjYd +
      traceYuAdjYu)*Sqr(g3) - 3*Sqr(g2)*(5*(3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu) + 24*Sqr(g3)) + 6*(9*traceYdAdjYdYdAdjYd - 2*
      traceYdAdjYuYuAdjYd + 3*traceYeAdjYeYeAdjYe + 9*traceYuAdjYuYuAdjYu - 2*
      Sqr(Lambdax)))) + 0.0125*(-43*Sqr(g1) + 5*(20*(3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu) + 9*Sqr(g2) - 256*Sqr(g3)))*(Yu*Yd.adjoint
      ()*Yd) + (-0.75*(9*traceYdAdjYd + 3*traceYeAdjYe + 9*traceYuAdjYu + 8*
      Lambdax) + 2.7875*Sqr(g1) + 8.4375*Sqr(g2) + 16*Sqr(g3))*(Yu*Yu.adjoint()
      *Yu) + 2.75*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.25*(Yu*Yd.adjoint()*
      Yd*Yu.adjoint()*Yu) - Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd + 1.5*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> HSSUSY_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (0.00005*PROJECTOR*threeLoop*(321980*Power6(g1) + 3396580*
      Power6(g2) - 5*Quad(g2)*(21375*Lambdax + 84288*Sqr(g3) - 67960*Sqr(Yu(2,2
      ))) - 5*Quad(g1)*(5445*Lambdax + 17768*Sqr(g2) + 89276*Sqr(g3) + 97688*
      Sqr(Yu(2,2))) - 10*Sqr(g1)*(9486*Quad(g2) + 30192*Quad(g3) + 60925*Quad(
      Yu(2,2)) - 4500*Sqr(Lambdax) + Sqr(g2)*(-2925*Lambdax + 32100*Sqr(g3) -
      69658*Sqr(Yu(2,2))) + 12700*Lambdax*Sqr(Yu(2,2)) - 36148*Sqr(g3)*Sqr(Yu(2
      ,2))) + 10*Sqr(g2)*(147308*Quad(g3) + 96740*Sqr(g3)*Sqr(Yu(2,2)) + 1125*(
      -177*Quad(Yu(2,2)) + 20*Sqr(Lambdax) - 60*Lambdax*Sqr(Yu(2,2)))) + 2*(
      -45000*Cube(Lambdax) - 6193500*Power6(g3) + 586028*Power6(Yu(2,2)) +
      990000*Lambdax*Quad(Yu(2,2)) + 3637640*Quad(g3)*Sqr(Yu(2,2)) + 9375*Sqr(
      Lambdax)*Sqr(Yu(2,2)) + 10000*Sqr(g3)*(-157*Quad(Yu(2,2)) + 8*Lambdax*Sqr
      (Yu(2,2)))))*Yu(2,2)).real();


   return beta_Yu;
}

} // namespace flexiblesusy
