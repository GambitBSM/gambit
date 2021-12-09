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

// File generated at Thu 10 Oct 2019 17:27:29

#include "CMSSM_soft_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT soft_traces

namespace {

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(double n, const Eigen::MatrixBase<Derived>& m)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m - Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(double n, const Eigen::MatrixBase<Derived>& m)
{
   return - m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

} // anonymous namespace

/**
 * Calculates the 1-loop beta function of TYd.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYd_1_loop(const Soft_traces& soft_traces) const
{
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_TYd;

   beta_TYd = (oneOver16PiSqr*(0.06666666666666667*(90*traceAdjYdTYd*Yd + 30*
      traceAdjYeTYe*Yd + 14*MassB*Yd*Sqr(g1) + 90*MassWB*Yd*Sqr(g2) + 160*MassG
      *Yd*Sqr(g3) + 45*traceYdAdjYd*TYd + 15*traceYeAdjYe*TYd - 7*Sqr(g1)*TYd -
      45*Sqr(g2)*TYd - 80*Sqr(g3)*TYd) + 4*(Yd*Yd.adjoint()*TYd) + 2*(Yd*Yu.
      adjoint()*TYu) + 5*(TYd*Yd.adjoint()*Yd) + TYd*Yu.adjoint()*Yu)).real();


   return beta_TYd;
}

/**
 * Calculates the 2-loop beta function of TYd.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYd_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYdTYdAdjYd = TRACE_STRUCT.traceYdAdjYdTYdAdjYd;
   const double traceYdAdjYuTYuAdjYd = TRACE_STRUCT.traceYdAdjYuTYuAdjYd;
   const double traceYeAdjYeTYeAdjYe = TRACE_STRUCT.traceYeAdjYeTYeAdjYe;
   const double traceYuAdjYdTYdAdjYu = TRACE_STRUCT.traceYuAdjYdTYdAdjYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   Eigen::Matrix<double,3,3> beta_TYd;

   beta_TYd = (twoLoop*(0.011111111111111112*(-3240*traceYdAdjYdTYdAdjYd*Yd -
      540*traceYdAdjYuTYuAdjYd*Yd - 1080*traceYeAdjYeTYeAdjYe*Yd - 540*
      traceYuAdjYdTYdAdjYu*Yd - 1148*MassB*Yd*Quad(g1) - 2700*MassWB*Yd*Quad(g2
      ) + 640*MassG*Yd*Quad(g3) - 72*traceAdjYdTYd*Yd*Sqr(g1) + 216*
      traceAdjYeTYe*Yd*Sqr(g1) + 72*MassB*traceYdAdjYd*Yd*Sqr(g1) - 216*MassB*
      traceYeAdjYe*Yd*Sqr(g1) - 180*MassB*Yd*Sqr(g1)*Sqr(g2) - 180*MassWB*Yd*
      Sqr(g1)*Sqr(g2) + 2880*traceAdjYdTYd*Yd*Sqr(g3) - 2880*MassG*traceYdAdjYd
      *Yd*Sqr(g3) - 160*MassB*Yd*Sqr(g1)*Sqr(g3) - 160*MassG*Yd*Sqr(g1)*Sqr(g3)
      - 1440*MassG*Yd*Sqr(g2)*Sqr(g3) - 1440*MassWB*Yd*Sqr(g2)*Sqr(g3) - 810*
      traceYdAdjYdYdAdjYd*TYd - 270*traceYdAdjYuYuAdjYd*TYd - 270*
      traceYeAdjYeYeAdjYe*TYd + 287*Quad(g1)*TYd + 675*Quad(g2)*TYd - 160*Quad(
      g3)*TYd - 36*traceYdAdjYd*Sqr(g1)*TYd + 108*traceYeAdjYe*Sqr(g1)*TYd + 90
      *Sqr(g1)*Sqr(g2)*TYd + 1440*traceYdAdjYd*Sqr(g3)*TYd + 80*Sqr(g1)*Sqr(g3)
      *TYd + 720*Sqr(g2)*Sqr(g3)*TYd) - 0.4*(45*traceAdjYdTYd + 15*
      traceAdjYeTYe + 4*MassB*Sqr(g1) + 30*MassWB*Sqr(g2))*(Yd*Yd.adjoint()*Yd)
      + 0.4*(-30*traceYdAdjYd - 10*traceYeAdjYe + 3*Sqr(g1) + 15*Sqr(g2))*(Yd*
      Yd.adjoint()*TYd) - 0.4*(15*traceAdjYuTYu + 4*MassB*Sqr(g1))*(Yd*Yu.
      adjoint()*Yu) + 0.4*(-15*traceYuAdjYu + 4*Sqr(g1))*(Yd*Yu.adjoint()*TYu)
      + 0.2*(-75*traceYdAdjYd - 25*traceYeAdjYe + 6*Sqr(g1) + 60*Sqr(g2))*(TYd*
      Yd.adjoint()*Yd) + 0.2*(-15*traceYuAdjYu + 4*Sqr(g1))*(TYd*Yu.adjoint()*
      Yu) - 6*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd) - 8*(Yd*Yd.adjoint()*TYd*Yd
      .adjoint()*Yd) - 2*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd) - 4*(Yd*Yu.
      adjoint()*Yu*Yu.adjoint()*TYu) - 4*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd)
      - 4*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu) - 6*(TYd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) - 4*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 2*(TYd*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_TYd;
}

/**
 * Calculates the 3-loop beta function of TYd.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYd_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceTYdAdjYd = TRACE_STRUCT.traceTYdAdjYd;
   const double traceTYeAdjYe = TRACE_STRUCT.traceTYeAdjYe;
   const double traceTYuAdjYu = TRACE_STRUCT.traceTYuAdjYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeTYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYuYuAdjYd = TRACE_STRUCT.
      traceTYdAdjYuYuAdjYuYuAdjYd;


   Eigen::Matrix<double,3,3> beta_TYd;

   const Eigen::Matrix<double,3,3> beta_TYd_1 = ((-0.00044444444444444447*
      threeLoop*Yd*(-486000*traceAdjYdTYdAdjYdYd*traceAdjYdYd - 40500*
      traceAdjYdYdAdjYdTYdAdjYdYd - 162000*traceAdjYdYd*traceAdjYeTYeAdjYeYe -
      162000*traceAdjYdTYdAdjYdYd*traceAdjYeYe - 54000*traceAdjYeTYeAdjYeYe*
      traceAdjYeYe - 13500*traceAdjYeYeAdjYeTYeAdjYeYe - 40500*
      traceAdjYuTYuAdjYuYuAdjYdYd - 81000*traceAdjYuTYuAdjYdYd*traceAdjYuYu -
      40500*traceAdjYuYuAdjYuTYuAdjYdYd - 243000*traceAdjYdYdAdjYdYd*
      traceTYdAdjYd - 81000*traceAdjYeYeAdjYeYe*traceTYdAdjYd - 81000*
      traceAdjYuYu*traceTYdAdjYuYuAdjYd - 40500*traceTYdAdjYuYuAdjYuYuAdjYd -
      81000*traceAdjYdYdAdjYdYd*traceTYeAdjYe - 27000*traceAdjYeYeAdjYeYe*
      traceTYeAdjYe - 81000*traceAdjYuYuAdjYdYd*traceTYuAdjYu + 389302*MassB*
      Power6(g1) + 2328750*MassWB*Power6(g2) + 2720000*MassG*Power6(g3) -
      141750*MassB*traceAdjYdYd*Quad(g1) - 284850*MassB*traceAdjYeYe*Quad(g1) -
      54600*MassB*traceAdjYuYu*Quad(g1) + 70875*traceTYdAdjYd*Quad(g1) + 142425
      *traceTYeAdjYe*Quad(g1) + 27300*traceTYuAdjYu*Quad(g1) - 708750*MassWB*
      traceAdjYdYd*Quad(g2) - 236250*MassWB*traceAdjYeYe*Quad(g2) - 405000*
      MassWB*traceAdjYuYu*Quad(g2) + 354375*traceTYdAdjYd*Quad(g2) + 118125*
      traceTYeAdjYe*Quad(g2) + 202500*traceTYuAdjYu*Quad(g2) - 960000*MassG*
      traceAdjYdYd*Quad(g3) - 480000*MassG*traceAdjYuYu*Quad(g3) + 480000*
      traceTYdAdjYd*Quad(g3) + 240000*traceTYuAdjYu*Quad(g3) - 27000*
      traceAdjYdTYdAdjYdYd*Sqr(g1) + 13500*MassB*traceAdjYdYdAdjYdYd*Sqr(g1) -
      81000*traceAdjYeTYeAdjYeYe*Sqr(g1) + 40500*MassB*traceAdjYeYeAdjYeYe*Sqr(
      g1) + 10800*traceAdjYuTYuAdjYdYd*Sqr(g1) - 10800*MassB*
      traceAdjYuYuAdjYdYd*Sqr(g1) + 10800*traceTYdAdjYuYuAdjYd*Sqr(g1) + 38250*
      MassB*Quad(g2)*Sqr(g1) + 76500*MassWB*Quad(g2)*Sqr(g1) + 106000*MassB*
      Quad(g3)*Sqr(g1) + 212000*MassG*Quad(g3)*Sqr(g1) - 81000*
      traceAdjYdTYdAdjYdYd*Sqr(g2) + 40500*MassWB*traceAdjYdYdAdjYdYd*Sqr(g2) -
      27000*traceAdjYeTYeAdjYeYe*Sqr(g2) + 13500*MassWB*traceAdjYeYeAdjYeYe*Sqr
      (g2) - 81000*traceAdjYuTYuAdjYdYd*Sqr(g2) + 81000*MassWB*
      traceAdjYuYuAdjYdYd*Sqr(g2) - 81000*traceTYdAdjYuYuAdjYd*Sqr(g2) + 19620*
      MassB*Quad(g1)*Sqr(g2) + 9810*MassWB*Quad(g1)*Sqr(g2) + 612000*MassG*Quad
      (g3)*Sqr(g2) + 306000*MassWB*Quad(g3)*Sqr(g2) - 1350*MassB*traceAdjYdYd*
      Sqr(g1)*Sqr(g2) - 1350*MassWB*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 36450*MassB*
      traceAdjYeYe*Sqr(g1)*Sqr(g2) - 36450*MassWB*traceAdjYeYe*Sqr(g1)*Sqr(g2)
      + 1350*traceTYdAdjYd*Sqr(g1)*Sqr(g2) + 36450*traceTYeAdjYe*Sqr(g1)*Sqr(g2
      ) - 648000*traceAdjYdTYdAdjYdYd*Sqr(g3) + 324000*MassG*
      traceAdjYdYdAdjYdYd*Sqr(g3) - 108000*traceAdjYuTYuAdjYdYd*Sqr(g3) +
      108000*MassG*traceAdjYuYuAdjYdYd*Sqr(g3) - 108000*traceTYdAdjYuYuAdjYd*
      Sqr(g3) + 155680*MassB*Quad(g1)*Sqr(g3) + 77840*MassG*Quad(g1)*Sqr(g3) +
      630000*MassG*Quad(g2)*Sqr(g3) + 1260000*MassWB*Quad(g2)*Sqr(g3) - 85200*
      MassB*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 85200*MassG*traceAdjYdYd*Sqr(g1)*Sqr
      (g3) + 85200*traceTYdAdjYd*Sqr(g1)*Sqr(g3) - 594000*MassG*traceAdjYdYd*
      Sqr(g2)*Sqr(g3) - 594000*MassWB*traceAdjYdYd*Sqr(g2)*Sqr(g3) + 594000*
      traceTYdAdjYd*Sqr(g2)*Sqr(g3) - 7200*MassB*Sqr(g1)*Sqr(g2)*Sqr(g3) - 7200
      *MassG*Sqr(g1)*Sqr(g2)*Sqr(g3) - 7200*MassWB*Sqr(g1)*Sqr(g2)*Sqr(g3)) +
      0.016*threeLoop*(4179*MassB*Power6(g1) - 118125*MassWB*Power6(g2) -
      240000*MassG*Power6(g3) + 385*MassB*traceAdjYdYd*Quad(g1) + 2700*
      traceAdjYdTYdAdjYdYd*Sqr(g1) + 2025*MassB*Quad(g2)*Sqr(g1) + 4050*MassWB*
      Quad(g2)*Sqr(g1) + 4400*MassB*Quad(g3)*Sqr(g1) + 8800*MassG*Quad(g3)*Sqr(
      g1) + 13500*traceAdjYdTYdAdjYdYd*Sqr(g2) + 1890*MassB*Quad(g1)*Sqr(g2) +
      945*MassWB*Quad(g1)*Sqr(g2) + 36000*MassG*Quad(g3)*Sqr(g2) + 18000*MassWB
      *Quad(g3)*Sqr(g2) - 36000*traceAdjYdTYdAdjYdYd*Sqr(g3) + 6160*MassB*Quad(
      g1)*Sqr(g3) + 3080*MassG*Quad(g1)*Sqr(g3) + 27000*MassG*Quad(g2)*Sqr(g3)
      + 54000*MassWB*Quad(g2)*Sqr(g3))*(Yd*1.2020569031595942))*UNITMATRIX(3)).
      real();
   const Eigen::Matrix<double,3,3> beta_TYd_2 = ((-0.04*threeLoop*(-2700*
      traceAdjYdYdAdjYdTYdAdjYdYd - 900*traceAdjYeYeAdjYeTYeAdjYeYe + 162*MassB
      *traceAdjYeYe*Quad(g1) + 77*traceTYdAdjYd*Quad(g1) - 81*traceTYeAdjYe*
      Quad(g1) - 9450*MassWB*traceAdjYdYd*Quad(g2) - 3150*MassWB*traceAdjYeYe*
      Quad(g2) + 4725*traceTYdAdjYd*Quad(g2) + 1575*traceTYeAdjYe*Quad(g2) -
      1600*MassG*traceAdjYdYd*Quad(g3) + 800*traceTYdAdjYd*Quad(g3) + 540*MassB
      *traceAdjYdYdAdjYdYd*Sqr(g1) + 1080*traceAdjYeTYeAdjYeYe*Sqr(g1) - 540*
      MassB*traceAdjYeYeAdjYeYe*Sqr(g1) - 420*traceAdjYuTYuAdjYdYd*Sqr(g1) +
      420*MassB*traceAdjYuYuAdjYdYd*Sqr(g1) - 420*traceTYdAdjYuYuAdjYd*Sqr(g1)
      + 2700*MassWB*traceAdjYdYdAdjYdYd*Sqr(g2) - 1800*traceAdjYeTYeAdjYeYe*Sqr
      (g2) + 900*MassWB*traceAdjYeYeAdjYeYe*Sqr(g2) - 450*MassB*traceAdjYdYd*
      Sqr(g1)*Sqr(g2) - 450*MassWB*traceAdjYdYd*Sqr(g1)*Sqr(g2) + 810*MassB*
      traceAdjYeYe*Sqr(g1)*Sqr(g2) + 810*MassWB*traceAdjYeYe*Sqr(g1)*Sqr(g2) +
      450*traceTYdAdjYd*Sqr(g1)*Sqr(g2) - 810*traceTYeAdjYe*Sqr(g1)*Sqr(g2) -
      7200*MassG*traceAdjYdYdAdjYdYd*Sqr(g3) + 2400*traceAdjYuTYuAdjYdYd*Sqr(g3
      ) - 2400*MassG*traceAdjYuYuAdjYdYd*Sqr(g3) + 2400*traceTYdAdjYuYuAdjYd*
      Sqr(g3) + 1120*MassB*traceAdjYdYd*Sqr(g1)*Sqr(g3) + 1120*MassG*
      traceAdjYdYd*Sqr(g1)*Sqr(g3) - 1120*traceTYdAdjYd*Sqr(g1)*Sqr(g3) + 7200*
      MassG*traceAdjYdYd*Sqr(g2)*Sqr(g3) + 7200*MassWB*traceAdjYdYd*Sqr(g2)*Sqr
      (g3) - 7200*traceTYdAdjYd*Sqr(g2)*Sqr(g3))*(Yd*1.2020569031595942) -
      0.004*threeLoop*(-4500*traceAdjYdYdAdjYdYdAdjYdYd - 1500*
      traceAdjYeYeAdjYeYeAdjYeYe + 2786*Power6(g1) - 78750*Power6(g2) - 160000*
      Power6(g3) + 385*traceAdjYdYd*Quad(g1) - 405*traceAdjYeYe*Quad(g1) +
      23625*traceAdjYdYd*Quad(g2) + 7875*traceAdjYeYe*Quad(g2) + 4000*
      traceAdjYdYd*Quad(g3) - 2700*traceAdjYdYdAdjYdYd*Sqr(g1) + 2700*
      traceAdjYeYeAdjYeYe*Sqr(g1) - 2100*traceAdjYuYuAdjYdYd*Sqr(g1) + 4050*
      Quad(g2)*Sqr(g1) + 8800*Quad(g3)*Sqr(g1) - 13500*traceAdjYdYdAdjYdYd*Sqr(
      g2) - 4500*traceAdjYeYeAdjYeYe*Sqr(g2) + 1890*Quad(g1)*Sqr(g2) + 36000*
      Quad(g3)*Sqr(g2) + 2250*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 4050*traceAdjYeYe*
      Sqr(g1)*Sqr(g2) + 36000*traceAdjYdYdAdjYdYd*Sqr(g3) + 12000*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 6160*Quad(g1)*Sqr(g3) + 54000*Quad(g2)*Sqr(
      g3) - 5600*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 36000*traceAdjYdYd*Sqr(g2)*Sqr(
      g3))*(TYd*1.2020569031595942) + 0.013333333333333334*threeLoop*(16200*
      traceAdjYdTYdAdjYdYd + 5400*traceAdjYeTYeAdjYeYe + 2700*
      traceAdjYuTYuAdjYdYd - 8100*traceAdjYdYd*traceTYdAdjYd - 2700*
      traceAdjYeYe*traceTYdAdjYd + 2700*traceTYdAdjYuYuAdjYd - 2700*
      traceAdjYdYd*traceTYeAdjYe - 900*traceAdjYeYe*traceTYeAdjYe + 5269*MassB*
      Quad(g1) + 16425*MassWB*Quad(g2) - 2400*MassG*Quad(g3) - 1530*MassB*
      traceAdjYdYd*Sqr(g1) + 690*MassB*traceAdjYeYe*Sqr(g1) + 1530*
      traceTYdAdjYd*Sqr(g1) - 690*traceTYeAdjYe*Sqr(g1) - 6750*MassWB*
      traceAdjYdYd*Sqr(g2) - 2250*MassWB*traceAdjYeYe*Sqr(g2) + 6750*
      traceTYdAdjYd*Sqr(g2) + 2250*traceTYeAdjYe*Sqr(g2) + 1905*MassB*Sqr(g1)*
      Sqr(g2) + 1905*MassWB*Sqr(g1)*Sqr(g2) + 3600*MassG*traceAdjYdYd*Sqr(g3) -
      3600*MassG*traceAdjYeYe*Sqr(g3) - 3600*traceTYdAdjYd*Sqr(g3) + 3600*
      traceTYeAdjYe*Sqr(g3) + 1480*MassB*Sqr(g1)*Sqr(g3) + 1480*MassG*Sqr(g1)*
      Sqr(g3) + 13800*MassG*Sqr(g2)*Sqr(g3) + 13800*MassWB*Sqr(g2)*Sqr(g3))*(Yd
      *Yd.adjoint()*Yd) - 0.013333333333333334*threeLoop*(1792*Quad(g1) + 4950*
      Quad(g2) - 800*Quad(g3) - 1005*traceAdjYdYd*Sqr(g1) - 4725*traceAdjYdYd*
      Sqr(g2) + 1260*Sqr(g1)*Sqr(g2) + 1120*Sqr(g1)*Sqr(g3) + 7200*Sqr(g2)*Sqr(
      g3))*(Yd*Yd.adjoint()*TYd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYd_3 = ((-0.2*threeLoop*(-360*
      traceAdjYdYdAdjYdYd + 120*traceAdjYdYd*traceAdjYeYe - 120*
      traceAdjYeYeAdjYeYe - 120*traceAdjYuYuAdjYdYd + 31*traceAdjYeYe*Sqr(g1) -
      105*traceAdjYeYe*Sqr(g2) + 160*traceAdjYdYd*Sqr(g3) - 160*traceAdjYeYe*
      Sqr(g3) + 180*Sqr(traceAdjYdYd) + 20*Sqr(traceAdjYeYe))*(Yd*Yd.adjoint()*
      TYd) + 0.013333333333333334*threeLoop*(900*traceAdjYuTYuAdjYdYd + 5400*
      traceAdjYuTYuAdjYuYu + 900*traceTYdAdjYuYuAdjYd - 2700*traceAdjYuYu*
      traceTYuAdjYu + 3767*MassB*Quad(g1) + 3375*MassWB*Quad(g2) - 800*MassG*
      Quad(g3) - 300*MassB*traceAdjYuYu*Sqr(g1) + 300*traceTYuAdjYu*Sqr(g1) -
      2700*MassWB*traceAdjYuYu*Sqr(g2) + 2700*traceTYuAdjYu*Sqr(g2) + 885*MassB
      *Sqr(g1)*Sqr(g2) + 885*MassWB*Sqr(g1)*Sqr(g2) + 1200*MassG*traceAdjYuYu*
      Sqr(g3) - 1200*traceTYuAdjYu*Sqr(g3) + 2040*MassB*Sqr(g1)*Sqr(g3) + 2040*
      MassG*Sqr(g1)*Sqr(g3) + 600*MassG*Sqr(g2)*Sqr(g3) + 600*MassWB*Sqr(g2)*
      Sqr(g3))*(Yd*Yu.adjoint()*Yu) - 0.006666666666666667*threeLoop*(-1800*
      traceAdjYuYuAdjYdYd - 5400*traceAdjYuYuAdjYuYu + 3767*Quad(g1) + 3375*
      Quad(g2) - 800*Quad(g3) - 600*traceAdjYuYu*Sqr(g1) - 5400*traceAdjYuYu*
      Sqr(g2) + 1770*Sqr(g1)*Sqr(g2) + 2400*traceAdjYuYu*Sqr(g3) + 4080*Sqr(g1)
      *Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYuYu))*(Yd*Yu.adjoint(
      )*TYu) - 0.0033333333333333335*threeLoop*(-27000*traceAdjYdYdAdjYdYd +
      9000*traceAdjYdYd*traceAdjYeYe - 9000*traceAdjYeYeAdjYeYe - 9000*
      traceAdjYuYuAdjYdYd + 8639*Quad(g1) + 29475*Quad(g2) - 4000*Quad(g3) -
      5160*traceAdjYdYd*Sqr(g1) + 2280*traceAdjYeYe*Sqr(g1) - 21600*
      traceAdjYdYd*Sqr(g2) - 7200*traceAdjYeYe*Sqr(g2) + 6390*Sqr(g1)*Sqr(g2) +
      12000*traceAdjYdYd*Sqr(g3) - 12000*traceAdjYeYe*Sqr(g3) + 4400*Sqr(g1)*
      Sqr(g3) + 54000*Sqr(g2)*Sqr(g3) + 13500*Sqr(traceAdjYdYd) + 1500*Sqr(
      traceAdjYeYe))*(TYd*Yd.adjoint()*Yd) - 0.0033333333333333335*threeLoop*(-
      1800*traceAdjYuYuAdjYdYd - 5400*traceAdjYuYuAdjYuYu + 3767*Quad(g1) +
      3375*Quad(g2) - 800*Quad(g3) - 600*traceAdjYuYu*Sqr(g1) - 5400*
      traceAdjYuYu*Sqr(g2) + 1770*Sqr(g1)*Sqr(g2) + 2400*traceAdjYuYu*Sqr(g3) +
      4080*Sqr(g1)*Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYuYu))*(
      TYd*Yu.adjoint()*Yu) - 0.08*threeLoop*(7*MassB*Quad(g1) - 2025*MassWB*
      Quad(g2) - 13600*MassG*Quad(g3) - 270*MassB*traceAdjYdYd*Sqr(g1) + 210*
      MassB*traceAdjYeYe*Sqr(g1) + 270*traceTYdAdjYd*Sqr(g1) - 210*
      traceTYeAdjYe*Sqr(g1) - 1350*MassWB*traceAdjYdYd*Sqr(g2) - 450*MassWB*
      traceAdjYeYe*Sqr(g2) + 1350*traceTYdAdjYd*Sqr(g2) + 450*traceTYeAdjYe*Sqr
      (g2) + 255*MassB*Sqr(g1)*Sqr(g2) + 255*MassWB*Sqr(g1)*Sqr(g2) + 3600*
      MassG*traceAdjYdYd*Sqr(g3) - 3600*traceTYdAdjYd*Sqr(g3) + 480*MassB*Sqr(
      g1)*Sqr(g3) + 480*MassG*Sqr(g1)*Sqr(g3) + 2400*MassG*Sqr(g2)*Sqr(g3) +
      2400*MassWB*Sqr(g2)*Sqr(g3))*(Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      0.02666666666666667*threeLoop*(14*Quad(g1) - 2700*Quad(g2) - 13600*Quad(
      g3) - 585*traceAdjYdYd*Sqr(g1) + 405*traceAdjYeYe*Sqr(g1) - 2025*
      traceAdjYdYd*Sqr(g2) + 450*Sqr(g1)*Sqr(g2) + 7200*traceAdjYdYd*Sqr(g3) +
      1040*Sqr(g1)*Sqr(g3) + 3600*Sqr(g2)*Sqr(g3))*(Yd*Yd.adjoint()*TYd*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYd_4 = ((-18*threeLoop*traceAdjYeYe*
      Sqr(g2)*(Yd*Yd.adjoint()*TYd*1.2020569031595942) - 0.02666666666666667*
      threeLoop*(143*MassB*Quad(g1) - 4725*MassWB*Quad(g2) - 13600*MassG*Quad(
      g3) - 360*MassB*traceAdjYuYu*Sqr(g1) + 360*traceTYuAdjYu*Sqr(g1) + 675*
      MassB*Sqr(g1)*Sqr(g2) + 675*MassWB*Sqr(g1)*Sqr(g2) + 3600*MassG*
      traceAdjYuYu*Sqr(g3) - 3600*traceTYuAdjYu*Sqr(g3) + 640*MassB*Sqr(g1)*Sqr
      (g3) + 640*MassG*Sqr(g1)*Sqr(g3))*(Yd*Yu.adjoint()*Yu*1.2020569031595942)
      + 0.013333333333333334*threeLoop*(143*Quad(g1) - 4725*Quad(g2) - 13600*
      Quad(g3) - 720*traceAdjYuYu*Sqr(g1) + 1350*Sqr(g1)*Sqr(g2) + 7200*
      traceAdjYuYu*Sqr(g3) + 1280*Sqr(g1)*Sqr(g3))*(Yd*Yu.adjoint()*TYu*
      1.2020569031595942) + 0.006666666666666667*threeLoop*(7*Quad(g1) - 7425*
      Quad(g2) - 68000*Quad(g3) - 2520*traceAdjYdYd*Sqr(g1) + 2160*traceAdjYeYe
      *Sqr(g1) - 16200*traceAdjYdYd*Sqr(g2) - 5400*traceAdjYeYe*Sqr(g2) + 2790*
      Sqr(g1)*Sqr(g2) + 36000*traceAdjYdYd*Sqr(g3) + 4480*Sqr(g1)*Sqr(g3) +
      28800*Sqr(g2)*Sqr(g3))*(TYd*Yd.adjoint()*Yd*1.2020569031595942) +
      0.006666666666666667*threeLoop*(143*Quad(g1) - 4725*Quad(g2) - 13600*Quad
      (g3) - 720*traceAdjYuYu*Sqr(g1) + 1350*Sqr(g1)*Sqr(g2) + 7200*
      traceAdjYuYu*Sqr(g3) + 1280*Sqr(g1)*Sqr(g3))*(TYd*Yu.adjoint()*Yu*
      1.2020569031595942) - 0.26666666666666666*threeLoop*(-90*traceTYdAdjYd -
      30*traceTYeAdjYe + MassB*Sqr(g1) + 45*MassWB*Sqr(g2) + 320*MassG*Sqr(g3))
      *(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 0.2*threeLoop*(90*traceAdjYdYd +
      30*traceAdjYeYe + 3*Sqr(g1) + 15*Sqr(g2) + 320*Sqr(g3))*(Yd*Yd.adjoint()*
      Yd*Yd.adjoint()*TYd) + 0.26666666666666666*threeLoop*(90*traceAdjYdYd +
      30*traceAdjYeYe + Sqr(g1) + 45*Sqr(g2) + 320*Sqr(g3))*(Yd*Yd.adjoint()*
      TYd*Yd.adjoint()*Yd) + 0.13333333333333333*threeLoop*(-90*traceTYdAdjYd -
      30*traceTYeAdjYe + 180*traceTYuAdjYu + 29*MassB*Sqr(g1) - 135*MassWB*Sqr(
      g2) - 320*MassG*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) -
      0.06666666666666667*threeLoop*(90*traceAdjYdYd + 30*traceAdjYeYe - 180*
      traceAdjYuYu + 29*Sqr(g1) - 135*Sqr(g2) - 320*Sqr(g3))*(Yd*Yu.adjoint()*
      Yu*Yd.adjoint()*TYd) - 0.6666666666666666*threeLoop*(-18*traceTYuAdjYu +
      11*MassB*Sqr(g1) - 9*MassWB*Sqr(g2) + 64*MassG*Sqr(g3))*(Yd*Yu.adjoint()*
      Yu*Yu.adjoint()*Yu) + 0.6666666666666666*threeLoop*(18*traceAdjYuYu + 11*
      Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu) -
      0.13333333333333333*threeLoop*(90*traceAdjYdYd + 30*traceAdjYeYe - 180*
      traceAdjYuYu + 29*Sqr(g1) - 135*Sqr(g2) - 320*Sqr(g3))*(Yd*Yu.adjoint()*
      TYu*Yd.adjoint()*Yd) + 0.6666666666666666*threeLoop*(18*traceAdjYuYu + 11
      *Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu)
      - 0.2*threeLoop*(-90*traceAdjYdYd - 30*traceAdjYeYe + Sqr(g1) - 75*Sqr(g2
      ) - 320*Sqr(g3))*(TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) -
      0.13333333333333333*threeLoop*(90*traceAdjYdYd + 30*traceAdjYeYe - 180*
      traceAdjYuYu + 29*Sqr(g1) - 135*Sqr(g2) - 320*Sqr(g3))*(TYd*Yu.adjoint()*
      Yu*Yd.adjoint()*Yd) + 0.3333333333333333*threeLoop*(18*traceAdjYuYu + 11*
      Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu) -
      1.2*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd
      *1.2020569031595942) - 7.2*MassB*threeLoop*Sqr(g1)*(Yd*Yu.adjoint()*Yu*Yd
      .adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYd_5 = ((0.00007407407407407407*
      threeLoop*(729000*traceAdjYdYd*traceAdjYdYdAdjYdYd + 40500*
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
      Sqr(g2)*Sqr(g3))*TYd + 36*MassWB*threeLoop*Sqr(g2)*(Yd*Yu.adjoint()*Yu*Yd
      .adjoint()*Yd*1.2020569031595942) + 3.6*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(
      Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd*1.2020569031595942) + 12*threeLoop*(
      MassB*Sqr(g1) - 3*MassWB*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) - 12*threeLoop*(Sqr(g1) - 3*Sqr(g2))*(Yd*Yu.adjoint()
      *Yu*Yu.adjoint()*TYu*1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*Sqr
      (g2))*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd*1.2020569031595942) - 12*
      threeLoop*(Sqr(g1) - 3*Sqr(g2))*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu*
      1.2020569031595942) + 1.2*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(TYd*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 7.2*threeLoop*(Sqr(g1)
      - 5*Sqr(g2))*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*1.2020569031595942) - 6
      *threeLoop*(Sqr(g1) - 3*Sqr(g2))*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 6*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd) + 12*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*Yd.
      adjoint()*Yd) + 6*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*TYd) + 4*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yd.
      adjoint()*Yd) + 12*threeLoop*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) + 4*threeLoop*(Yd*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) - 2*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd) + 8*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*TYu) - 4*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yd.
      adjoint()*Yd) + 8*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()*TYd) + 12*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yd.
      adjoint()*Yd) - 4*threeLoop*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) + 8*threeLoop*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 12*threeLoop*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) + 12*threeLoop*(TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) - 4*threeLoop*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd) + 4*threeLoop*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 12*threeLoop*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) + 24*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd*1.2020569031595942) + 36*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd*Yd.adjoint()*Yd*1.2020569031595942) + 36*threeLoop*(Yd*Yd.
      adjoint()*TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 12*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      1.2020569031595942) + 12*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu*1.2020569031595942) + 12*threeLoop*(Yd*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 30*threeLoop*(TYd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 6*
      threeLoop*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942))*UNITMATRIX(3)).real();

   beta_TYd = beta_TYd_1 + beta_TYd_2 + beta_TYd_3 + beta_TYd_4 + beta_TYd_5;


   return beta_TYd;
}

/**
 * Calculates the 4-loop beta function of TYd.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYd_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYd;

   beta_TYd = ZEROMATRIX(3,3);


   return beta_TYd;
}

/**
 * Calculates the 5-loop beta function of TYd.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYd_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYd;

   beta_TYd = ZEROMATRIX(3,3);


   return beta_TYd;
}

} // namespace flexiblesusy
