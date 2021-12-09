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

// File generated at Thu 10 Oct 2019 17:27:09

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yd.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yd_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (oneOver16PiSqr*(-0.06666666666666667*Yd*(-45*traceYdAdjYd - 15*
      traceYeAdjYe + 7*Sqr(g1) + 45*Sqr(g2) + 80*Sqr(g3)) + 3*(Yd*Yd.adjoint()*
      Yd) + Yd*Yu.adjoint()*Yu)).real();


   return beta_Yd;
}

/**
 * Calculates the 2-loop beta function of Yd.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yd_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (twoLoop*(0.011111111111111112*Yd*(-810*traceYdAdjYdYdAdjYd - 270*
      traceYdAdjYuYuAdjYd - 270*traceYeAdjYeYeAdjYe + 287*Quad(g1) + 675*Quad(
      g2) - 160*Quad(g3) - 36*traceYdAdjYd*Sqr(g1) + 108*traceYeAdjYe*Sqr(g1) +
      90*Sqr(g1)*Sqr(g2) + 1440*traceYdAdjYd*Sqr(g3) + 80*Sqr(g1)*Sqr(g3) + 720
      *Sqr(g2)*Sqr(g3)) + 0.2*(-45*traceYdAdjYd - 15*traceYeAdjYe + 4*Sqr(g1) +
      30*Sqr(g2))*(Yd*Yd.adjoint()*Yd) + 0.2*(-15*traceYuAdjYu + 4*Sqr(g1))*(Yd
      *Yu.adjoint()*Yu) - 4*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 2*(Yd*Yu.
      adjoint()*Yu*Yd.adjoint()*Yd) - 2*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu))).
      real();


   return beta_Yd;
}

/**
 * Calculates the 3-loop beta function of Yd.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yd_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;


   Eigen::Matrix<double,3,3> beta_Yd;

   const Eigen::Matrix<double,3,3> beta_Yd_1 = ((0.00007407407407407407*
      threeLoop*Yd*(729000*traceAdjYdYd*traceAdjYdYdAdjYdYd + 40500*
      traceAdjYdYdAdjYdYdAdjYdYd + 243000*traceAdjYdYdAdjYdYd*traceAdjYeYe +
      243000*traceAdjYdYd*traceAdjYeYeAdjYeYe + 81000*traceAdjYeYe*
      traceAdjYeYeAdjYeYe + 13500*traceAdjYeYeAdjYeYeAdjYeYe + 243000*
      traceAdjYuYu*traceAdjYuYuAdjYdYd + 121500*traceAdjYuYuAdjYuYuAdjYdYd +
      389302*Power6(g1) + 2328750*Power6(g2) + 2720000*Power6(g3) - 212625*
      traceAdjYdYd*Quad(g1) - 427275*traceAdjYeYe*Quad(g1) - 81900*traceAdjYuYu
      *Quad(g1) - 1063125*traceAdjYdYd*Quad(g2) - 354375*traceAdjYeYe*Quad(g2)
      - 607500*traceAdjYuYu*Quad(g2) - 1440000*traceAdjYdYd*Quad(g3) - 720000*
      traceAdjYuYu*Quad(g3) + 40500*traceAdjYdYdAdjYdYd*Sqr(g1) + 121500*
      traceAdjYeYeAdjYeYe*Sqr(g1) - 32400*traceAdjYuYuAdjYdYd*Sqr(g1) + 114750*
      Quad(g2)*Sqr(g1) + 318000*Quad(g3)*Sqr(g1) + 121500*traceAdjYdYdAdjYdYd*
      Sqr(g2) + 40500*traceAdjYeYeAdjYeYe*Sqr(g2) + 243000*traceAdjYuYuAdjYdYd*
      Sqr(g2) + 29430*Quad(g1)*Sqr(g2) + 918000*Quad(g3)*Sqr(g2) - 4050*
      traceAdjYdYd*Sqr(g1)*Sqr(g2) - 109350*traceAdjYeYe*Sqr(g1)*Sqr(g2) +
      972000*traceAdjYdYdAdjYdYd*Sqr(g3) + 324000*traceAdjYuYuAdjYdYd*Sqr(g3) +
      233520*Quad(g1)*Sqr(g3) + 1890000*Quad(g2)*Sqr(g3) - 255600*traceAdjYdYd*
      Sqr(g1)*Sqr(g3) - 1782000*traceAdjYdYd*Sqr(g2)*Sqr(g3) - 21600*Sqr(g1)*
      Sqr(g2)*Sqr(g3)) - 0.004*threeLoop*(-4500*traceAdjYdYdAdjYdYdAdjYdYd -
      1500*traceAdjYeYeAdjYeYeAdjYeYe + 2786*Power6(g1) - 78750*Power6(g2) -
      160000*Power6(g3) + 385*traceAdjYdYd*Quad(g1) - 405*traceAdjYeYe*Quad(g1)
      + 23625*traceAdjYdYd*Quad(g2) + 7875*traceAdjYeYe*Quad(g2) + 4000*
      traceAdjYdYd*Quad(g3) - 2700*traceAdjYdYdAdjYdYd*Sqr(g1) + 2700*
      traceAdjYeYeAdjYeYe*Sqr(g1) - 2100*traceAdjYuYuAdjYdYd*Sqr(g1) + 4050*
      Quad(g2)*Sqr(g1) + 8800*Quad(g3)*Sqr(g1) - 13500*traceAdjYdYdAdjYdYd*Sqr(
      g2) - 4500*traceAdjYeYeAdjYeYe*Sqr(g2) + 1890*Quad(g1)*Sqr(g2) + 36000*
      Quad(g3)*Sqr(g2) + 2250*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 4050*traceAdjYeYe*
      Sqr(g1)*Sqr(g2) + 36000*traceAdjYdYdAdjYdYd*Sqr(g3) + 12000*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 6160*Quad(g1)*Sqr(g3) + 54000*Quad(g2)*Sqr(
      g3) - 5600*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 36000*traceAdjYdYd*Sqr(g2)*Sqr(
      g3))*(Yd*1.2020569031595942) - 0.0033333333333333335*threeLoop*(-16200*
      traceAdjYdYdAdjYdYd + 5400*traceAdjYdYd*traceAdjYeYe - 5400*
      traceAdjYeYeAdjYeYe - 5400*traceAdjYuYuAdjYdYd + 5269*Quad(g1) + 16425*
      Quad(g2) - 2400*Quad(g3) - 3060*traceAdjYdYd*Sqr(g1) + 1380*traceAdjYeYe*
      Sqr(g1) - 13500*traceAdjYdYd*Sqr(g2) - 4500*traceAdjYeYe*Sqr(g2) + 3810*
      Sqr(g1)*Sqr(g2) + 7200*traceAdjYdYd*Sqr(g3) - 7200*traceAdjYeYe*Sqr(g3) +
      2960*Sqr(g1)*Sqr(g3) + 27600*Sqr(g2)*Sqr(g3) + 8100*Sqr(traceAdjYdYd) +
      900*Sqr(traceAdjYeYe))*(Yd*Yd.adjoint()*Yd) - 0.0033333333333333335*
      threeLoop*(-1800*traceAdjYuYuAdjYdYd - 5400*traceAdjYuYuAdjYuYu + 3767*
      Quad(g1) + 3375*Quad(g2) - 800*Quad(g3) - 600*traceAdjYuYu*Sqr(g1) - 5400
      *traceAdjYuYu*Sqr(g2) + 1770*Sqr(g1)*Sqr(g2) + 2400*traceAdjYuYu*Sqr(g3)
      + 4080*Sqr(g1)*Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYuYu))*(
      Yd*Yu.adjoint()*Yu) + 0.02*threeLoop*(7*Quad(g1) - 2025*Quad(g2) + 510*
      Sqr(g1)*Sqr(g2) + 960*Sqr(g1)*Sqr(g3) + 4800*Sqr(g2)*Sqr(g3))*(Yd*Yd.
      adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_Yd_2 = ((-0.4*threeLoop*(680*Quad(g3) +
      27*traceAdjYdYd*Sqr(g1) - 21*traceAdjYeYe*Sqr(g1) + 135*traceAdjYdYd*Sqr(
      g2) + 45*traceAdjYeYe*Sqr(g2) - 360*traceAdjYdYd*Sqr(g3))*(Yd*Yd.adjoint(
      )*Yd*1.2020569031595942) + 0.006666666666666667*threeLoop*(143*Quad(g1) -
      4725*Quad(g2) - 13600*Quad(g3) - 720*traceAdjYuYu*Sqr(g1) + 1350*Sqr(g1)*
      Sqr(g2) + 7200*traceAdjYuYu*Sqr(g3) + 1280*Sqr(g1)*Sqr(g3))*(Yd*Yu.
      adjoint()*Yu*1.2020569031595942) + 0.13333333333333333*threeLoop*(90*
      traceAdjYdYd + 30*traceAdjYeYe + Sqr(g1) + 45*Sqr(g2) + 320*Sqr(g3))*(Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.06666666666666667*threeLoop*(90*
      traceAdjYdYd + 30*traceAdjYeYe - 180*traceAdjYuYu + 29*Sqr(g1) - 135*Sqr(
      g2) - 320*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) +
      0.3333333333333333*threeLoop*(18*traceAdjYuYu + 11*Sqr(g1) - 9*Sqr(g2) +
      64*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 3.6*threeLoop*(Sqr(g1)
      - 5*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*1.2020569031595942) - 6*
      threeLoop*(Sqr(g1) - 3*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 6*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) + 2*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) - 2*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) + 4*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) + 18*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*1.2020569031595942) + 6*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_Yd = beta_Yd_1 + beta_Yd_2;


   return beta_Yd;
}

/**
 * Calculates the 4-loop beta function of Yd.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yd_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = ZEROMATRIX(3,3);


   return beta_Yd;
}

/**
 * Calculates the 5-loop beta function of Yd.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Yd_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = ZEROMATRIX(3,3);


   return beta_Yd;
}

} // namespace flexiblesusy
