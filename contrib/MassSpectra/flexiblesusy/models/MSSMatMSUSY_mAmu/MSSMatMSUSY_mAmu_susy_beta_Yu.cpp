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

// File generated at Thu 10 May 2018 14:25:37

#include "MSSMatMSUSY_mAmu_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(-0.06666666666666667*Yu*(-45*traceYuAdjYu +
      13*Sqr(g1) + 45*Sqr(g2) + 80*Sqr(g3)) + Yu*Yd.adjoint()*Yd + 3*(Yu*
      Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(Yu*(-3*traceYdAdjYuYuAdjYd - 9*traceYuAdjYuYuAdjYu
      + 6.095555555555555*Quad(g1) + 7.5*Quad(g2) - 1.7777777777777777*Quad(g3
      ) + 16*traceYuAdjYu*Sqr(g3) + 8*Sqr(g2)*Sqr(g3) + Sqr(g1)*(Sqr(g2) +
      0.08888888888888889*(9*traceYuAdjYu + 34*Sqr(g3)))) + (-3*traceYdAdjYd -
      traceYeAdjYe + 0.4*Sqr(g1))*(Yu*Yd.adjoint()*Yd) + (-9*traceYuAdjYu + 0.4
      *Sqr(g1) + 6*Sqr(g2))*(Yu*Yu.adjoint()*Yu) - 2*(Yu*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd) - 2*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) - 4*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYdYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   const Eigen::Matrix<double,3,3> beta_Yu_1 = ((0.00007407407407407407*
      threeLoop*Yu*(704194*Power6(g1) + 15*Quad(g1)*(-15*(364*traceAdjYdYd +
      468*traceAdjYeYe + 2565*traceAdjYuYu) + 6822*Sqr(g2) + 21232*Sqr(g3)) +
      150*Sqr(g1)*(765*Quad(g2) - 9*Sqr(g2)*(57*traceAdjYuYu + 16*Sqr(g3)) + 2*
      (54*traceAdjYuYuAdjYdYd + 513*traceAdjYuYuAdjYuYu + 436*Quad(g3) - 1860*
      traceAdjYuYu*Sqr(g3))) + 125*(18630*Power6(g2) + 135*Quad(g2)*(-3*(12*
      traceAdjYdYd + 4*traceAdjYeYe + 21*traceAdjYuYu) + 112*Sqr(g3)) + 108*Sqr
      (g2)*(9*(2*traceAdjYuYuAdjYdYd + traceAdjYuYuAdjYuYu) + 68*Quad(g3) - 132
      *traceAdjYuYu*Sqr(g3)) + 4*(81*(3*traceAdjYdYdAdjYuYuAdjYdYd + 6*
      traceAdjYdYd*traceAdjYuYuAdjYdYd + 2*traceAdjYeYe*traceAdjYuYuAdjYdYd +
      18*traceAdjYuYu*traceAdjYuYuAdjYuYu + traceAdjYuYuAdjYuYuAdjYuYu) + 5440*
      Power6(g3) - 1440*(traceAdjYdYd + 2*traceAdjYuYu)*Quad(g3) + 648*(
      traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu)*Sqr(g3)))) - 0.004*threeLoop
      *(5174*Power6(g1) + 65*Quad(g1)*(5*traceAdjYuYu + 54*Sqr(g2) + 176*Sqr(g3
      )) + 50*Sqr(g1)*(-6*traceAdjYuYuAdjYdYd + 18*traceAdjYuYuAdjYuYu + 81*
      Quad(g2) + 176*Quad(g3) - 63*traceAdjYuYu*Sqr(g2) - 208*traceAdjYuYu*Sqr(
      g3)) - 125*(630*Power6(g2) - 27*Quad(g2)*(7*traceAdjYuYu + 16*Sqr(g3)) -
      36*Sqr(g2)*(-3*traceAdjYuYuAdjYuYu + 8*Quad(g3) - 8*traceAdjYuYu*Sqr(g3))
      + 4*(9*traceAdjYuYuAdjYuYuAdjYuYu + 320*Power6(g3) - 8*traceAdjYuYu*Quad
      (g3) - 24*(traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu)*Sqr(g3))))*(Yu*
      1.2020569031595942) - 0.0033333333333333335*threeLoop*(1899*Quad(g1) + 10
      *Sqr(g1)*(-96*traceAdjYdYd + 48*traceAdjYeYe + 123*Sqr(g2) + 152*Sqr(g3))
      + 25*(135*Quad(g2) - 32*Quad(g3) + 96*(traceAdjYdYd - traceAdjYeYe)*Sqr(
      g3) + 24*Sqr(g2)*(-3*(3*traceAdjYdYd + traceAdjYeYe) + 2*Sqr(g3)) + 12*(
      -18*traceAdjYdYdAdjYdYd + 6*traceAdjYdYd*traceAdjYeYe - 6*
      traceAdjYeYeAdjYeYe - 6*traceAdjYuYuAdjYdYd + 9*Sqr(traceAdjYdYd) + Sqr(
      traceAdjYeYe))))*(Yu*Yd.adjoint()*Yd) + (-28.536666666666665*threeLoop*
      Quad(g1) - 54.75*threeLoop*Quad(g2) - 0.03333333333333333*threeLoop*Sqr(
      g1)*(-270*traceAdjYuYu + 579*Sqr(g2) + 424*Sqr(g3)) + Sqr(g2)*(45*
      threeLoop*traceAdjYuYu - 92*threeLoop*Sqr(g3)) + threeLoop*(18*
      traceAdjYuYuAdjYdYd + 54*traceAdjYuYuAdjYuYu + 8*Quad(g3) - 24*
      traceAdjYuYu*Sqr(g3) - 27*Sqr(traceAdjYuYu)))*(Yu*Yu.adjoint()*Yu) +
      0.03333333333333333*threeLoop*(7*Quad(g1) + 2*Sqr(g1)*(-72*traceAdjYdYd +
      36*traceAdjYeYe + 27*Sqr(g2) + 128*Sqr(g3)) - 5*(189*Quad(g2) + 544*Quad
      (g3) - 288*traceAdjYdYd*Sqr(g3)))*(Yu*Yd.adjoint()*Yd*1.2020569031595942)
      - 0.02*threeLoop*(117*Quad(g1) - 10*Sqr(g1)*(18*traceAdjYuYu + 123*Sqr(
      g2) - 32*Sqr(g3)) + 25*(81*Quad(g2) - 12*Sqr(g2)*(-9*traceAdjYuYu + 16*
      Sqr(g3)) + 32*Sqr(g3)*(-9*traceAdjYuYu + 17*Sqr(g3))))*(Yu*Yu.adjoint()*
      Yu*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_Yu_2 = ((0.06666666666666667*
      threeLoop*(7*Sqr(g1) + 5*(18*traceAdjYdYd + 6*traceAdjYeYe - 9*Sqr(g2) +
      64*Sqr(g3)))*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + (1.2666666666666666*
      threeLoop*Sqr(g1) + 9*threeLoop*Sqr(g2) + 0.6666666666666666*threeLoop*(
      18*traceAdjYdYd + 6*traceAdjYeYe - 9*traceAdjYuYu + 32*Sqr(g3)))*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 0.6666666666666666*threeLoop*(18*
      traceAdjYuYu + 5*Sqr(g1) + 9*Sqr(g2) + 64*Sqr(g3))*(Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu) - 1.2*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(Yu*Yd.adjoint()*
      Yd*Yd.adjoint()*Yd*1.2020569031595942) + 3.6*threeLoop*(Sqr(g1) - 5*Sqr(
      g2))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*1.2020569031595942) + 6*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 4*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 2*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 2*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 6*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 6*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      1.2020569031595942) + 18*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_Yu = beta_Yu_1 + beta_Yu_2;


   return beta_Yu;
}

} // namespace flexiblesusy
