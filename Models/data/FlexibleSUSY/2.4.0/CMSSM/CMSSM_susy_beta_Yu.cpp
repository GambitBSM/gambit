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

// File generated at Thu 10 Oct 2019 17:27:10

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(-0.06666666666666667*Yu*(-45*traceYuAdjYu + 13*
      Sqr(g1) + 45*Sqr(g2) + 80*Sqr(g3)) + Yu*Yd.adjoint()*Yd + 3*(Yu*Yu.
      adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(0.0022222222222222222*Yu*(-1350*traceYdAdjYuYuAdjYd -
      4050*traceYuAdjYuYuAdjYu + 2743*Quad(g1) + 3375*Quad(g2) - 800*Quad(g3) +
      360*traceYuAdjYu*Sqr(g1) + 450*Sqr(g1)*Sqr(g2) + 7200*traceYuAdjYu*Sqr(g3
      ) + 1360*Sqr(g1)*Sqr(g3) + 3600*Sqr(g2)*Sqr(g3)) + 0.2*(-15*traceYdAdjYd
      - 5*traceYeAdjYe + 2*Sqr(g1))*(Yu*Yd.adjoint()*Yd) + 0.2*(-45*
      traceYuAdjYu + 2*Sqr(g1) + 30*Sqr(g2))*(Yu*Yu.adjoint()*Yu) - 2*(Yu*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd) - 2*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) -
      4*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYdYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   const Eigen::Matrix<double,3,3> beta_Yu_1 = ((0.00007407407407407407*
      threeLoop*Yu*(121500*traceAdjYdYdAdjYuYuAdjYdYd + 243000*traceAdjYdYd*
      traceAdjYuYuAdjYdYd + 81000*traceAdjYeYe*traceAdjYuYuAdjYdYd + 729000*
      traceAdjYuYu*traceAdjYuYuAdjYuYu + 40500*traceAdjYuYuAdjYuYuAdjYuYu +
      704194*Power6(g1) + 2328750*Power6(g2) + 2720000*Power6(g3) - 81900*
      traceAdjYdYd*Quad(g1) - 105300*traceAdjYeYe*Quad(g1) - 577125*
      traceAdjYuYu*Quad(g1) - 607500*traceAdjYdYd*Quad(g2) - 202500*
      traceAdjYeYe*Quad(g2) - 1063125*traceAdjYuYu*Quad(g2) - 720000*
      traceAdjYdYd*Quad(g3) - 1440000*traceAdjYuYu*Quad(g3) + 16200*
      traceAdjYuYuAdjYdYd*Sqr(g1) + 153900*traceAdjYuYuAdjYuYu*Sqr(g1) + 114750
      *Quad(g2)*Sqr(g1) + 130800*Quad(g3)*Sqr(g1) + 243000*traceAdjYuYuAdjYdYd*
      Sqr(g2) + 121500*traceAdjYuYuAdjYuYu*Sqr(g2) + 102330*Quad(g1)*Sqr(g2) +
      918000*Quad(g3)*Sqr(g2) - 76950*traceAdjYuYu*Sqr(g1)*Sqr(g2) + 324000*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 972000*traceAdjYuYuAdjYuYu*Sqr(g3) + 318480
      *Quad(g1)*Sqr(g3) + 1890000*Quad(g2)*Sqr(g3) - 558000*traceAdjYuYu*Sqr(g1
      )*Sqr(g3) - 1782000*traceAdjYuYu*Sqr(g2)*Sqr(g3) - 21600*Sqr(g1)*Sqr(g2)*
      Sqr(g3)) - 0.004*threeLoop*(-4500*traceAdjYuYuAdjYuYuAdjYuYu + 5174*
      Power6(g1) - 78750*Power6(g2) - 160000*Power6(g3) + 325*traceAdjYuYu*Quad
      (g1) + 23625*traceAdjYuYu*Quad(g2) + 4000*traceAdjYuYu*Quad(g3) - 300*
      traceAdjYuYuAdjYdYd*Sqr(g1) + 900*traceAdjYuYuAdjYuYu*Sqr(g1) + 4050*Quad
      (g2)*Sqr(g1) + 8800*Quad(g3)*Sqr(g1) - 13500*traceAdjYuYuAdjYuYu*Sqr(g2)
      + 3510*Quad(g1)*Sqr(g2) + 36000*Quad(g3)*Sqr(g2) - 3150*traceAdjYuYu*Sqr(
      g1)*Sqr(g2) + 12000*traceAdjYuYuAdjYdYd*Sqr(g3) + 36000*
      traceAdjYuYuAdjYuYu*Sqr(g3) + 11440*Quad(g1)*Sqr(g3) + 54000*Quad(g2)*Sqr
      (g3) - 10400*traceAdjYuYu*Sqr(g1)*Sqr(g3) - 36000*traceAdjYuYu*Sqr(g2)*
      Sqr(g3))*(Yu*1.2020569031595942) - 0.0033333333333333335*threeLoop*(-5400
      *traceAdjYdYdAdjYdYd + 1800*traceAdjYdYd*traceAdjYeYe - 1800*
      traceAdjYeYeAdjYeYe - 1800*traceAdjYuYuAdjYdYd + 1899*Quad(g1) + 3375*
      Quad(g2) - 800*Quad(g3) - 960*traceAdjYdYd*Sqr(g1) + 480*traceAdjYeYe*Sqr
      (g1) - 5400*traceAdjYdYd*Sqr(g2) - 1800*traceAdjYeYe*Sqr(g2) + 1230*Sqr(
      g1)*Sqr(g2) + 2400*traceAdjYdYd*Sqr(g3) - 2400*traceAdjYeYe*Sqr(g3) +
      1520*Sqr(g1)*Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYdYd) +
      300*Sqr(traceAdjYeYe))*(Yu*Yd.adjoint()*Yd) - 0.0033333333333333335*
      threeLoop*(-5400*traceAdjYuYuAdjYdYd - 16200*traceAdjYuYuAdjYuYu + 8561*
      Quad(g1) + 16425*Quad(g2) - 2400*Quad(g3) - 2700*traceAdjYuYu*Sqr(g1) -
      13500*traceAdjYuYu*Sqr(g2) + 5790*Sqr(g1)*Sqr(g2) + 7200*traceAdjYuYu*Sqr
      (g3) + 4240*Sqr(g1)*Sqr(g3) + 27600*Sqr(g2)*Sqr(g3) + 8100*Sqr(
      traceAdjYuYu))*(Yu*Yu.adjoint()*Yu) + 0.03333333333333333*threeLoop*(7*
      Quad(g1) - 945*Quad(g2) - 2720*Quad(g3) - 144*traceAdjYdYd*Sqr(g1) + 72*
      traceAdjYeYe*Sqr(g1) + 54*Sqr(g1)*Sqr(g2) + 1440*traceAdjYdYd*Sqr(g3) +
      256*Sqr(g1)*Sqr(g3))*(Yu*Yd.adjoint()*Yd*1.2020569031595942) - 0.02*
      threeLoop*(117*Quad(g1) + 2025*Quad(g2) + 13600*Quad(g3) - 180*
      traceAdjYuYu*Sqr(g1) + 2700*traceAdjYuYu*Sqr(g2) - 1230*Sqr(g1)*Sqr(g2) -
      7200*traceAdjYuYu*Sqr(g3) + 320*Sqr(g1)*Sqr(g3) - 4800*Sqr(g2)*Sqr(g3))*(
      Yu*Yu.adjoint()*Yu*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_Yu_2 = ((0.06666666666666667*threeLoop*
      (90*traceAdjYdYd + 30*traceAdjYeYe + 7*Sqr(g1) - 45*Sqr(g2) + 320*Sqr(g3)
      )*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 0.06666666666666667*threeLoop*(
      180*traceAdjYdYd + 60*traceAdjYeYe - 90*traceAdjYuYu + 19*Sqr(g1) + 135*
      Sqr(g2) + 320*Sqr(g3))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) +
      0.6666666666666666*threeLoop*(18*traceAdjYuYu + 5*Sqr(g1) + 9*Sqr(g2) +
      64*Sqr(g3))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) - 1.2*threeLoop*(Sqr(g1)
      - 15*Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      3.6*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*
      1.2020569031595942) + 6*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 4*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) - 2*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 2*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*1.2020569031595942) + 18*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_Yu = beta_Yu_1 + beta_Yu_2;


   return beta_Yu;
}

/**
 * Calculates the 4-loop beta function of Yu.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yu_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

/**
 * Calculates the 5-loop beta function of Yu.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yu_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

} // namespace flexiblesusy
