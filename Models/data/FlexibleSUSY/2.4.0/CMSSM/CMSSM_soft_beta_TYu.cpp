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

// File generated at Thu 10 Oct 2019 17:27:32

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
 * Calculates the 1-loop beta function of TYu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYu_1_loop(const Soft_traces& soft_traces) const
{
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_TYu;

   beta_TYu = (oneOver16PiSqr*(0.06666666666666667*(90*traceAdjYuTYu*Yu + 26*
      MassB*Yu*Sqr(g1) + 90*MassWB*Yu*Sqr(g2) + 160*MassG*Yu*Sqr(g3) + 45*
      traceYuAdjYu*TYu - 13*Sqr(g1)*TYu - 45*Sqr(g2)*TYu - 80*Sqr(g3)*TYu) + 2*
      (Yu*Yd.adjoint()*TYd) + 4*(Yu*Yu.adjoint()*TYu) + TYu*Yd.adjoint()*Yd + 5
      *(TYu*Yu.adjoint()*Yu))).real();


   return beta_TYu;
}

/**
 * Calculates the 2-loop beta function of TYu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYu_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYdAdjYuTYuAdjYd = TRACE_STRUCT.traceYdAdjYuTYuAdjYd;
   const double traceYuAdjYdTYdAdjYu = TRACE_STRUCT.traceYuAdjYdTYdAdjYu;
   const double traceYuAdjYuTYuAdjYu = TRACE_STRUCT.traceYuAdjYuTYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_TYu;

   beta_TYu = (twoLoop*(0.0022222222222222222*(-2700*traceYdAdjYuTYuAdjYd*Yu -
      2700*traceYuAdjYdTYdAdjYu*Yu - 16200*traceYuAdjYuTYuAdjYu*Yu - 10972*
      MassB*Yu*Quad(g1) - 13500*MassWB*Yu*Quad(g2) + 3200*MassG*Yu*Quad(g3) +
      720*traceAdjYuTYu*Yu*Sqr(g1) - 720*MassB*traceYuAdjYu*Yu*Sqr(g1) - 900*
      MassB*Yu*Sqr(g1)*Sqr(g2) - 900*MassWB*Yu*Sqr(g1)*Sqr(g2) + 14400*
      traceAdjYuTYu*Yu*Sqr(g3) - 14400*MassG*traceYuAdjYu*Yu*Sqr(g3) - 2720*
      MassB*Yu*Sqr(g1)*Sqr(g3) - 2720*MassG*Yu*Sqr(g1)*Sqr(g3) - 7200*MassG*Yu*
      Sqr(g2)*Sqr(g3) - 7200*MassWB*Yu*Sqr(g2)*Sqr(g3) - 1350*
      traceYdAdjYuYuAdjYd*TYu - 4050*traceYuAdjYuYuAdjYu*TYu + 2743*Quad(g1)*
      TYu + 3375*Quad(g2)*TYu - 800*Quad(g3)*TYu + 360*traceYuAdjYu*Sqr(g1)*TYu
       + 450*Sqr(g1)*Sqr(g2)*TYu + 7200*traceYuAdjYu*Sqr(g3)*TYu + 1360*Sqr(g1)
      *Sqr(g3)*TYu + 3600*Sqr(g2)*Sqr(g3)*TYu) - 0.4*(15*traceAdjYdTYd + 5*
      traceAdjYeTYe + 2*MassB*Sqr(g1))*(Yu*Yd.adjoint()*Yd) + 0.4*(-15*
      traceYdAdjYd - 5*traceYeAdjYe + 2*Sqr(g1))*(Yu*Yd.adjoint()*TYd) - 0.4*(
      45*traceAdjYuTYu + 2*MassB*Sqr(g1) + 30*MassWB*Sqr(g2))*(Yu*Yu.adjoint()*
      Yu) + 1.2*(-10*traceYuAdjYu + Sqr(g1) + 5*Sqr(g2))*(Yu*Yu.adjoint()*TYu)
      + 0.2*(-15*traceYdAdjYd - 5*traceYeAdjYe + 2*Sqr(g1))*(TYu*Yd.adjoint()*
      Yd) + 3*(-5*traceYuAdjYu + 4*Sqr(g2))*(TYu*Yu.adjoint()*Yu) - 4*(Yu*Yd.
      adjoint()*Yd*Yd.adjoint()*TYd) - 2*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu)
      - 4*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd) - 4*(Yu*Yd.adjoint()*TYd*Yu.
      adjoint()*Yu) - 6*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu) - 8*(Yu*Yu.
      adjoint()*TYu*Yu.adjoint()*Yu) - 2*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd)
      - 4*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) - 6*(TYu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu))).real();


   return beta_TYu;
}

/**
 * Calculates the 3-loop beta function of TYu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYu_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYdTYdAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuTYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjYuYu;


   Eigen::Matrix<double,3,3> beta_TYu;

   const Eigen::Matrix<double,3,3> beta_TYu_1 = ((-0.00044444444444444447*
      threeLoop*Yu*(-40500*traceAdjYdTYdAdjYuYuAdjYdYd - 40500*
      traceAdjYdYdAdjYuTYuAdjYdYd - 81000*traceAdjYdYd*traceAdjYuTYuAdjYdYd -
      27000*traceAdjYeYe*traceAdjYuTYuAdjYdYd - 486000*traceAdjYuTYuAdjYuYu*
      traceAdjYuYu - 40500*traceAdjYuYuAdjYdTYdAdjYdYd - 40500*
      traceAdjYuYuAdjYuTYuAdjYuYu - 81000*traceAdjYuYuAdjYdYd*traceTYdAdjYd -
      81000*traceAdjYdYd*traceTYdAdjYuYuAdjYd - 27000*traceAdjYeYe*
      traceTYdAdjYuYuAdjYd - 27000*traceAdjYuYuAdjYdYd*traceTYeAdjYe - 243000*
      traceAdjYuYuAdjYuYu*traceTYuAdjYu + 704194*MassB*Power6(g1) + 2328750*
      MassWB*Power6(g2) + 2720000*MassG*Power6(g3) - 54600*MassB*traceAdjYdYd*
      Quad(g1) - 70200*MassB*traceAdjYeYe*Quad(g1) - 384750*MassB*traceAdjYuYu*
      Quad(g1) + 27300*traceTYdAdjYd*Quad(g1) + 35100*traceTYeAdjYe*Quad(g1) +
      192375*traceTYuAdjYu*Quad(g1) - 405000*MassWB*traceAdjYdYd*Quad(g2) -
      135000*MassWB*traceAdjYeYe*Quad(g2) - 708750*MassWB*traceAdjYuYu*Quad(g2)
      + 202500*traceTYdAdjYd*Quad(g2) + 67500*traceTYeAdjYe*Quad(g2) + 354375*
      traceTYuAdjYu*Quad(g2) - 480000*MassG*traceAdjYdYd*Quad(g3) - 960000*
      MassG*traceAdjYuYu*Quad(g3) + 240000*traceTYdAdjYd*Quad(g3) + 480000*
      traceTYuAdjYu*Quad(g3) - 5400*traceAdjYuTYuAdjYdYd*Sqr(g1) - 102600*
      traceAdjYuTYuAdjYuYu*Sqr(g1) + 5400*MassB*traceAdjYuYuAdjYdYd*Sqr(g1) +
      51300*MassB*traceAdjYuYuAdjYuYu*Sqr(g1) - 5400*traceTYdAdjYuYuAdjYd*Sqr(
      g1) + 38250*MassB*Quad(g2)*Sqr(g1) + 76500*MassWB*Quad(g2)*Sqr(g1) +
      43600*MassB*Quad(g3)*Sqr(g1) + 87200*MassG*Quad(g3)*Sqr(g1) - 81000*
      traceAdjYuTYuAdjYdYd*Sqr(g2) - 81000*traceAdjYuTYuAdjYuYu*Sqr(g2) + 81000
      *MassWB*traceAdjYuYuAdjYdYd*Sqr(g2) + 40500*MassWB*traceAdjYuYuAdjYuYu*
      Sqr(g2) - 81000*traceTYdAdjYuYuAdjYd*Sqr(g2) + 68220*MassB*Quad(g1)*Sqr(
      g2) + 34110*MassWB*Quad(g1)*Sqr(g2) + 612000*MassG*Quad(g3)*Sqr(g2) +
      306000*MassWB*Quad(g3)*Sqr(g2) - 25650*MassB*traceAdjYuYu*Sqr(g1)*Sqr(g2)
      - 25650*MassWB*traceAdjYuYu*Sqr(g1)*Sqr(g2) + 25650*traceTYuAdjYu*Sqr(g1)
      *Sqr(g2) - 108000*traceAdjYuTYuAdjYdYd*Sqr(g3) - 648000*
      traceAdjYuTYuAdjYuYu*Sqr(g3) + 108000*MassG*traceAdjYuYuAdjYdYd*Sqr(g3) +
      324000*MassG*traceAdjYuYuAdjYuYu*Sqr(g3) - 108000*traceTYdAdjYuYuAdjYd*
      Sqr(g3) + 212320*MassB*Quad(g1)*Sqr(g3) + 106160*MassG*Quad(g1)*Sqr(g3) +
      630000*MassG*Quad(g2)*Sqr(g3) + 1260000*MassWB*Quad(g2)*Sqr(g3) - 186000*
      MassB*traceAdjYuYu*Sqr(g1)*Sqr(g3) - 186000*MassG*traceAdjYuYu*Sqr(g1)*
      Sqr(g3) + 186000*traceTYuAdjYu*Sqr(g1)*Sqr(g3) - 594000*MassG*
      traceAdjYuYu*Sqr(g2)*Sqr(g3) - 594000*MassWB*traceAdjYuYu*Sqr(g2)*Sqr(g3)
      + 594000*traceTYuAdjYu*Sqr(g2)*Sqr(g3) - 7200*MassB*Sqr(g1)*Sqr(g2)*Sqr(
      g3) - 7200*MassG*Sqr(g1)*Sqr(g2)*Sqr(g3) - 7200*MassWB*Sqr(g1)*Sqr(g2)*
      Sqr(g3)) + 0.016*threeLoop*(7761*MassB*Power6(g1) - 118125*MassWB*Power6(
      g2) - 240000*MassG*Power6(g3) + 325*MassB*traceAdjYuYu*Quad(g1) + 23625*
      MassWB*traceAdjYuYu*Quad(g2) + 4000*MassG*traceAdjYuYu*Quad(g3) + 150*
      traceAdjYuTYuAdjYdYd*Sqr(g1) - 900*traceAdjYuTYuAdjYuYu*Sqr(g1) - 150*
      MassB*traceAdjYuYuAdjYdYd*Sqr(g1) + 2025*MassB*Quad(g2)*Sqr(g1) + 4050*
      MassWB*Quad(g2)*Sqr(g1) + 4400*MassB*Quad(g3)*Sqr(g1) + 8800*MassG*Quad(
      g3)*Sqr(g1) + 13500*traceAdjYuTYuAdjYuYu*Sqr(g2) + 3510*MassB*Quad(g1)*
      Sqr(g2) + 1755*MassWB*Quad(g1)*Sqr(g2) + 36000*MassG*Quad(g3)*Sqr(g2) +
      18000*MassWB*Quad(g3)*Sqr(g2) - 1575*MassB*traceAdjYuYu*Sqr(g1)*Sqr(g2) -
      1575*MassWB*traceAdjYuYu*Sqr(g1)*Sqr(g2) - 6000*traceAdjYuTYuAdjYdYd*Sqr(
      g3) - 36000*traceAdjYuTYuAdjYuYu*Sqr(g3) + 11440*MassB*Quad(g1)*Sqr(g3) +
      5720*MassG*Quad(g1)*Sqr(g3) + 27000*MassG*Quad(g2)*Sqr(g3) + 54000*MassWB
      *Quad(g2)*Sqr(g3) - 5200*MassB*traceAdjYuYu*Sqr(g1)*Sqr(g3) - 5200*MassG*
      traceAdjYuYu*Sqr(g1)*Sqr(g3) - 18000*MassG*traceAdjYuYu*Sqr(g2)*Sqr(g3) -
      18000*MassWB*traceAdjYuYu*Sqr(g2)*Sqr(g3))*(Yu*1.2020569031595942))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_2 = ((-0.2*threeLoop*(-540*
      traceAdjYuYuAdjYuTYuAdjYuYu + 13*traceTYuAdjYu*Quad(g1) + 945*
      traceTYuAdjYu*Quad(g2) + 160*traceTYuAdjYu*Quad(g3) - 36*MassB*
      traceAdjYuYuAdjYuYu*Sqr(g1) - 12*traceTYdAdjYuYuAdjYd*Sqr(g1) + 540*
      MassWB*traceAdjYuYuAdjYuYu*Sqr(g2) - 126*traceTYuAdjYu*Sqr(g1)*Sqr(g2) -
      480*MassG*traceAdjYuYuAdjYdYd*Sqr(g3) - 1440*MassG*traceAdjYuYuAdjYuYu*
      Sqr(g3) + 480*traceTYdAdjYuYuAdjYd*Sqr(g3) - 416*traceTYuAdjYu*Sqr(g1)*
      Sqr(g3) - 1440*traceTYuAdjYu*Sqr(g2)*Sqr(g3))*(Yu*1.2020569031595942) -
      0.004*threeLoop*(-4500*traceAdjYuYuAdjYuYuAdjYuYu + 5174*Power6(g1) -
      78750*Power6(g2) - 160000*Power6(g3) + 325*traceAdjYuYu*Quad(g1) + 23625*
      traceAdjYuYu*Quad(g2) + 4000*traceAdjYuYu*Quad(g3) - 300*
      traceAdjYuYuAdjYdYd*Sqr(g1) + 900*traceAdjYuYuAdjYuYu*Sqr(g1) + 4050*Quad
      (g2)*Sqr(g1) + 8800*Quad(g3)*Sqr(g1) - 13500*traceAdjYuYuAdjYuYu*Sqr(g2)
      + 3510*Quad(g1)*Sqr(g2) + 36000*Quad(g3)*Sqr(g2) - 3150*traceAdjYuYu*Sqr(
      g1)*Sqr(g2) + 12000*traceAdjYuYuAdjYdYd*Sqr(g3) + 36000*
      traceAdjYuYuAdjYuYu*Sqr(g3) + 11440*Quad(g1)*Sqr(g3) + 54000*Quad(g2)*Sqr
      (g3) - 10400*traceAdjYuYu*Sqr(g1)*Sqr(g3) - 36000*traceAdjYuYu*Sqr(g2)*
      Sqr(g3))*(TYu*1.2020569031595942) + 0.013333333333333334*threeLoop*(5400*
      traceAdjYdTYdAdjYdYd + 1800*traceAdjYeTYeAdjYeYe + 900*
      traceAdjYuTYuAdjYdYd - 2700*traceAdjYdYd*traceTYdAdjYd - 900*traceAdjYeYe
      *traceTYdAdjYd + 900*traceTYdAdjYuYuAdjYd - 900*traceAdjYdYd*
      traceTYeAdjYe - 300*traceAdjYeYe*traceTYeAdjYe + 1899*MassB*Quad(g1) +
      3375*MassWB*Quad(g2) - 800*MassG*Quad(g3) - 480*MassB*traceAdjYdYd*Sqr(g1
      ) + 240*MassB*traceAdjYeYe*Sqr(g1) + 480*traceTYdAdjYd*Sqr(g1) - 240*
      traceTYeAdjYe*Sqr(g1) - 2700*MassWB*traceAdjYdYd*Sqr(g2) - 900*MassWB*
      traceAdjYeYe*Sqr(g2) + 2700*traceTYdAdjYd*Sqr(g2) + 900*traceTYeAdjYe*Sqr
      (g2) + 615*MassB*Sqr(g1)*Sqr(g2) + 615*MassWB*Sqr(g1)*Sqr(g2) + 1200*
      MassG*traceAdjYdYd*Sqr(g3) - 1200*MassG*traceAdjYeYe*Sqr(g3) - 1200*
      traceTYdAdjYd*Sqr(g3) + 1200*traceTYeAdjYe*Sqr(g3) + 760*MassB*Sqr(g1)*
      Sqr(g3) + 760*MassG*Sqr(g1)*Sqr(g3) + 600*MassG*Sqr(g2)*Sqr(g3) + 600*
      MassWB*Sqr(g2)*Sqr(g3))*(Yu*Yd.adjoint()*Yd) - 0.006666666666666667*
      threeLoop*(-5400*traceAdjYdYdAdjYdYd + 1800*traceAdjYdYd*traceAdjYeYe -
      1800*traceAdjYeYeAdjYeYe - 1800*traceAdjYuYuAdjYdYd + 1899*Quad(g1) +
      3375*Quad(g2) - 800*Quad(g3) - 960*traceAdjYdYd*Sqr(g1) + 480*
      traceAdjYeYe*Sqr(g1) - 5400*traceAdjYdYd*Sqr(g2) - 1800*traceAdjYeYe*Sqr(
      g2) + 1230*Sqr(g1)*Sqr(g2) + 2400*traceAdjYdYd*Sqr(g3) - 2400*
      traceAdjYeYe*Sqr(g3) + 1520*Sqr(g1)*Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700
      *Sqr(traceAdjYdYd) + 300*Sqr(traceAdjYeYe))*(Yu*Yd.adjoint()*TYd) +
      0.013333333333333334*threeLoop*(2700*traceAdjYuTYuAdjYdYd + 16200*
      traceAdjYuTYuAdjYuYu + 2700*traceTYdAdjYuYuAdjYd - 8100*traceAdjYuYu*
      traceTYuAdjYu + 8561*MassB*Quad(g1) + 16425*MassWB*Quad(g2) - 2400*MassG*
      Quad(g3) - 1350*MassB*traceAdjYuYu*Sqr(g1) + 1350*traceTYuAdjYu*Sqr(g1) -
      6750*MassWB*traceAdjYuYu*Sqr(g2) + 6750*traceTYuAdjYu*Sqr(g2) + 2895*
      MassB*Sqr(g1)*Sqr(g2) + 2895*MassWB*Sqr(g1)*Sqr(g2) + 3600*MassG*
      traceAdjYuYu*Sqr(g3) - 3600*traceTYuAdjYu*Sqr(g3) + 2120*MassB*Sqr(g1)*
      Sqr(g3) + 2120*MassG*Sqr(g1)*Sqr(g3) + 13800*MassG*Sqr(g2)*Sqr(g3) +
      13800*MassWB*Sqr(g2)*Sqr(g3))*(Yu*Yu.adjoint()*Yu))*UNITMATRIX(3)).real()
      ;
   const Eigen::Matrix<double,3,3> beta_TYu_3 = ((-0.013333333333333334*
      threeLoop*(-1800*traceAdjYuYuAdjYdYd - 5400*traceAdjYuYuAdjYuYu + 3082*
      Quad(g1) + 4950*Quad(g2) - 800*Quad(g3) - 825*traceAdjYuYu*Sqr(g1) - 4725
      *traceAdjYuYu*Sqr(g2) + 1890*Sqr(g1)*Sqr(g2) + 2400*traceAdjYuYu*Sqr(g3)
      + 2080*Sqr(g1)*Sqr(g3) + 7200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYuYu))*(
      Yu*Yu.adjoint()*TYu) - 0.0033333333333333335*threeLoop*(-5400*
      traceAdjYdYdAdjYdYd + 1800*traceAdjYdYd*traceAdjYeYe - 1800*
      traceAdjYeYeAdjYeYe - 1800*traceAdjYuYuAdjYdYd + 1899*Quad(g1) + 3375*
      Quad(g2) - 800*Quad(g3) - 960*traceAdjYdYd*Sqr(g1) + 480*traceAdjYeYe*Sqr
      (g1) - 5400*traceAdjYdYd*Sqr(g2) - 1800*traceAdjYeYe*Sqr(g2) + 1230*Sqr(
      g1)*Sqr(g2) + 2400*traceAdjYdYd*Sqr(g3) - 2400*traceAdjYeYe*Sqr(g3) +
      1520*Sqr(g1)*Sqr(g3) + 1200*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYdYd) +
      300*Sqr(traceAdjYeYe))*(TYu*Yd.adjoint()*Yd) - 0.016666666666666666*
      threeLoop*(-1800*traceAdjYuYuAdjYdYd - 5400*traceAdjYuYuAdjYuYu + 2671*
      Quad(g1) + 5895*Quad(g2) - 800*Quad(g3) - 960*traceAdjYuYu*Sqr(g1) - 4320
      *traceAdjYuYu*Sqr(g2) + 1962*Sqr(g1)*Sqr(g2) + 2400*traceAdjYuYu*Sqr(g3)
      + 880*Sqr(g1)*Sqr(g3) + 10800*Sqr(g2)*Sqr(g3) + 2700*Sqr(traceAdjYuYu))*(
      TYu*Yu.adjoint()*Yu) - 0.13333333333333333*threeLoop*(7*MassB*Quad(g1) -
      945*MassWB*Quad(g2) - 2720*MassG*Quad(g3) - 72*MassB*traceAdjYdYd*Sqr(g1)
      + 36*MassB*traceAdjYeYe*Sqr(g1) + 72*traceTYdAdjYd*Sqr(g1) - 36*
      traceTYeAdjYe*Sqr(g1) + 27*MassB*Sqr(g1)*Sqr(g2) + 27*MassWB*Sqr(g1)*Sqr(
      g2) + 720*MassG*traceAdjYdYd*Sqr(g3) - 720*traceTYdAdjYd*Sqr(g3) + 128*
      MassB*Sqr(g1)*Sqr(g3) + 128*MassG*Sqr(g1)*Sqr(g3))*(Yu*Yd.adjoint()*Yd*
      1.2020569031595942) + 0.06666666666666667*threeLoop*(7*Quad(g1) - 945*
      Quad(g2) - 2720*Quad(g3) - 144*traceAdjYdYd*Sqr(g1) + 72*traceAdjYeYe*Sqr
      (g1) + 54*Sqr(g1)*Sqr(g2) + 1440*traceAdjYdYd*Sqr(g3) + 256*Sqr(g1)*Sqr(
      g3))*(Yu*Yd.adjoint()*TYd*1.2020569031595942) + 0.08*threeLoop*(117*MassB
      *Quad(g1) + 2025*MassWB*Quad(g2) + 13600*MassG*Quad(g3) - 90*MassB*
      traceAdjYuYu*Sqr(g1) + 90*traceTYuAdjYu*Sqr(g1) + 1350*MassWB*
      traceAdjYuYu*Sqr(g2) - 1350*traceTYuAdjYu*Sqr(g2) - 615*MassB*Sqr(g1)*Sqr
      (g2) - 615*MassWB*Sqr(g1)*Sqr(g2) - 3600*MassG*traceAdjYuYu*Sqr(g3) +
      3600*traceTYuAdjYu*Sqr(g3) + 160*MassB*Sqr(g1)*Sqr(g3) + 160*MassG*Sqr(g1
      )*Sqr(g3) - 2400*MassG*Sqr(g2)*Sqr(g3) - 2400*MassWB*Sqr(g2)*Sqr(g3))*(Yu
      *Yu.adjoint()*Yu*1.2020569031595942) - 0.02666666666666667*threeLoop*(52*
      Quad(g1) + 2700*Quad(g2) + 13600*Quad(g3) + 45*traceAdjYuYu*Sqr(g1) +
      2025*traceAdjYuYu*Sqr(g2) - 1260*Sqr(g1)*Sqr(g2) - 7200*traceAdjYuYu*Sqr(
      g3) - 80*Sqr(g1)*Sqr(g3) - 3600*Sqr(g2)*Sqr(g3))*(Yu*Yu.adjoint()*TYu*
      1.2020569031595942) + 0.03333333333333333*threeLoop*(7*Quad(g1) - 945*
      Quad(g2) - 2720*Quad(g3) - 144*traceAdjYdYd*Sqr(g1) + 72*traceAdjYeYe*Sqr
      (g1) + 54*Sqr(g1)*Sqr(g2) + 1440*traceAdjYdYd*Sqr(g3) + 256*Sqr(g1)*Sqr(
      g3))*(TYu*Yd.adjoint()*Yd*1.2020569031595942) - 0.03333333333333333*
      threeLoop*(169*Quad(g1) + 1485*Quad(g2) - 1206*Sqr(g1)*Sqr(g2) + 640*Sqr(
      g1)*Sqr(g3) - 5760*Sqr(g2)*Sqr(g3))*(TYu*Yu.adjoint()*Yu*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_4 = ((-1.3333333333333333*threeLoop
      *(340*Quad(g3) - 9*traceAdjYuYu*Sqr(g1) + 81*traceAdjYuYu*Sqr(g2) - 180*
      traceAdjYuYu*Sqr(g3))*(TYu*Yu.adjoint()*Yu*1.2020569031595942) -
      0.13333333333333333*threeLoop*(-90*traceTYdAdjYd - 30*traceTYeAdjYe + 7*
      MassB*Sqr(g1) - 45*MassWB*Sqr(g2) + 320*MassG*Sqr(g3))*(Yu*Yd.adjoint()*
      Yd*Yd.adjoint()*Yd) + 0.13333333333333333*threeLoop*(90*traceAdjYdYd + 30
      *traceAdjYeYe + 7*Sqr(g1) - 45*Sqr(g2) + 320*Sqr(g3))*(Yu*Yd.adjoint()*Yd
      *Yd.adjoint()*TYd) - 0.13333333333333333*threeLoop*(-180*traceTYdAdjYd -
      60*traceTYeAdjYe + 90*traceTYuAdjYu + 19*MassB*Sqr(g1) + 135*MassWB*Sqr(
      g2) + 320*MassG*Sqr(g3))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) +
      0.06666666666666667*threeLoop*(180*traceAdjYdYd + 60*traceAdjYeYe - 90*
      traceAdjYuYu + 19*Sqr(g1) + 135*Sqr(g2) + 320*Sqr(g3))*(Yu*Yd.adjoint()*
      Yd*Yu.adjoint()*TYu) + 0.13333333333333333*threeLoop*(90*traceAdjYdYd +
      30*traceAdjYeYe + 7*Sqr(g1) - 45*Sqr(g2) + 320*Sqr(g3))*(Yu*Yd.adjoint()*
      TYd*Yd.adjoint()*Yd) + 0.13333333333333333*threeLoop*(180*traceAdjYdYd +
      60*traceAdjYeYe - 90*traceAdjYuYu + 19*Sqr(g1) + 135*Sqr(g2) + 320*Sqr(g3
      ))*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu) - 1.3333333333333333*threeLoop*(
      -18*traceTYuAdjYu + 5*MassB*Sqr(g1) + 9*MassWB*Sqr(g2) + 64*MassG*Sqr(g3)
      )*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + threeLoop*(18*traceAdjYuYu + 7*
      Sqr(g1) + 3*Sqr(g2) + 64*Sqr(g3))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu) +
      1.3333333333333333*threeLoop*(18*traceAdjYuYu + 5*Sqr(g1) + 9*Sqr(g2) +
      64*Sqr(g3))*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu) + 0.06666666666666667*
      threeLoop*(90*traceAdjYdYd + 30*traceAdjYeYe + 7*Sqr(g1) - 45*Sqr(g2) +
      320*Sqr(g3))*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 0.13333333333333333*
      threeLoop*(180*traceAdjYdYd + 60*traceAdjYeYe - 90*traceAdjYuYu + 19*Sqr(
      g1) + 135*Sqr(g2) + 320*Sqr(g3))*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) +
      threeLoop*(18*traceAdjYuYu + 3*Sqr(g1) + 15*Sqr(g2) + 64*Sqr(g3))*(TYu*Yu
      .adjoint()*Yu*Yu.adjoint()*Yu) + 2.4*threeLoop*(MassB*Sqr(g1) - 15*MassWB
      *Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) - 2.4*
      threeLoop*(Sqr(g1) - 15*Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*
      1.2020569031595942) - 7.2*threeLoop*(MassB*Sqr(g1) - 5*MassWB*Sqr(g2))*(
      Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*1.2020569031595942) + 3.6*threeLoop*(
      Sqr(g1) - 5*Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*
      1.2020569031595942) - 2.4*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(Yu*Yd.adjoint
      ()*TYd*Yd.adjoint()*Yd*1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*
      Sqr(g2))*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*1.2020569031595942) - 6*
      threeLoop*(Sqr(g1) - 3*Sqr(g2))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      1.2020569031595942) - 1.2*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(TYu*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 7.2*threeLoop*(Sqr(g1)
      - 5*Sqr(g2))*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*1.2020569031595942) + 6
      *threeLoop*(Sqr(g1) - 3*Sqr(g2))*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 6*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.
      adjoint()*TYu) + 12*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*Yu.
      adjoint()*Yu) + 8*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*TYd) - 2*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.
      adjoint()*TYu) + 8*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yd.
      adjoint()*Yd) - 4*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yu.
      adjoint()*Yu) + 12*threeLoop*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 8*threeLoop*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) - 4*threeLoop*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*TYu) + 4*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yu.
      adjoint()*Yu) + 6*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*TYu) + 12*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yu.
      adjoint()*Yu) + 4*threeLoop*(Yu*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu) + 12*threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 12*threeLoop*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_5 = ((0.00007407407407407407*
      threeLoop*(121500*traceAdjYdYdAdjYuYuAdjYdYd + 243000*traceAdjYdYd*
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
      Sqr(g3))*TYu + 4*threeLoop*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) - 4*threeLoop*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 12*threeLoop*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu) + 12*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd*1.2020569031595942) + 12*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd*Yd.adjoint()*Yd*1.2020569031595942) + 12*threeLoop*(Yu*Yd.
      adjoint()*TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 24*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      1.2020569031595942) + 36*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu*1.2020569031595942) + 36*threeLoop*(Yu*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 6*threeLoop*(TYu*Yd
      .adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 30*
      threeLoop*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942))*UNITMATRIX(3)).real();

   beta_TYu = beta_TYu_1 + beta_TYu_2 + beta_TYu_3 + beta_TYu_4 + beta_TYu_5;


   return beta_TYu;
}

/**
 * Calculates the 4-loop beta function of TYu.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYu_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYu;

   beta_TYu = ZEROMATRIX(3,3);


   return beta_TYu;
}

/**
 * Calculates the 5-loop beta function of TYu.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYu_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYu;

   beta_TYu = ZEROMATRIX(3,3);


   return beta_TYu;
}

} // namespace flexiblesusy
