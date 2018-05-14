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

// File generated at Thu 10 May 2018 15:14:48

#include "MSSM_soft_parameters.hpp"
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
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYu_1_loop(const Soft_traces& soft_traces) const
{
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_TYu;

   beta_TYu = (oneOver16PiSqr*(0.06666666666666667*(2*Yu*(13*MassB*Sqr(g1
      ) + 45*(traceAdjYuTYu + MassWB*Sqr(g2)) + 80*MassG*Sqr(g3)) - (-45*
      traceYuAdjYu + 13*Sqr(g1) + 45*Sqr(g2) + 80*Sqr(g3))*TYu) + 2*(Yu*
      Yd.adjoint()*TYd) + 4*(Yu*Yu.adjoint()*TYu) + TYu*Yd.adjoint()*Yd + 5*(
      TYu*Yu.adjoint()*Yu))).real();


   return beta_TYu;
}

/**
 * Calculates the 2-loop beta function of TYu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYu_2_loop(const Soft_traces& soft_traces) const
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

   beta_TYu = (twoLoop*(-0.008888888888888889*Yu*(2743*MassB*Quad(g1) +
      25*(27*(traceYdAdjYuTYuAdjYd + traceYuAdjYdTYdAdjYu + 6*
      traceYuAdjYuTYuAdjYu) + 135*MassWB*Quad(g2) - 32*MassG*Quad(g3) - 144*(
      traceAdjYuTYu - MassG*traceYuAdjYu)*Sqr(g3) + 72*(MassG + MassWB)*Sqr(g2)
      *Sqr(g3)) + 5*Sqr(g1)*(45*(MassB + MassWB)*Sqr(g2) + 4*(-9*traceAdjYuTYu
      + 9*MassB*traceYuAdjYu + 34*(MassB + MassG)*Sqr(g3)))) + (-3*
      traceYdAdjYuYuAdjYd - 9*traceYuAdjYuYuAdjYu + 6.095555555555555*Quad(g1)
      + 7.5*Quad(g2) - 1.7777777777777777*Quad(g3) + 16*traceYuAdjYu*Sqr(g3) +
      8*Sqr(g2)*Sqr(g3) + Sqr(g1)*(Sqr(g2) + 0.08888888888888889*(9*
      traceYuAdjYu + 34*Sqr(g3))))*TYu + (-2*(3*traceAdjYdTYd + traceAdjYeTYe)
      - 0.8*MassB*Sqr(g1))*(Yu*Yd.adjoint()*Yd) + (-2*(3*traceYdAdjYd +
      traceYeAdjYe) + 0.8*Sqr(g1))*(Yu*Yd.adjoint()*TYd) - 0.4*(45*
      traceAdjYuTYu + 2*MassB*Sqr(g1) + 30*MassWB*Sqr(g2))*(Yu*Yu.adjoint()*Yu)
      + 1.2*(Sqr(g1) + 5*(-2*traceYuAdjYu + Sqr(g2)))*(Yu*Yu.adjoint()*TYu) +
      (-3*traceYdAdjYd - traceYeAdjYe + 0.4*Sqr(g1))*(TYu*Yd.adjoint()*Yd) + 3*
      (-5*traceYuAdjYu + 4*Sqr(g2))*(TYu*Yu.adjoint()*Yu) - 4*(Yu*Yd.adjoint()*
      Yd*Yd.adjoint()*TYd) - 2*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu) - 4*(Yu*
      Yd.adjoint()*TYd*Yd.adjoint()*Yd) - 4*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*
      Yu) - 6*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu) - 8*(Yu*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu) - 2*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 4*(TYu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu) - 6*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu
      ))).real();


   return beta_TYu;
}

/**
 * Calculates the 3-loop beta function of TYu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYu_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYdTYdAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuTYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYuYu;


   Eigen::Matrix<double,3,3> beta_TYu;

   const Eigen::Matrix<double,3,3> beta_TYu_1 = ((-0.00044444444444444447
      *threeLoop*Yu*(704194*MassB*Power6(g1) + 5*Quad(g1)*(15*(-2*MassB*(364*
      traceAdjYdYd + 468*traceAdjYeYe + 2565*traceAdjYuYu) + 364*traceTYdAdjYd
      + 468*traceTYeAdjYe + 2565*traceTYuAdjYu) + 6822*(2*MassB + MassWB)*Sqr(
      g2) + 21232*(2*MassB + MassG)*Sqr(g3)) + 50*Sqr(g1)*(54*(-2*
      traceAdjYuTYuAdjYdYd - 38*traceAdjYuTYuAdjYuYu + 2*MassB*
      traceAdjYuYuAdjYdYd + 19*MassB*traceAdjYuYuAdjYuYu - 2*
      traceTYdAdjYuYuAdjYd) + 765*(MassB + 2*MassWB)*Quad(g2) + 872*(MassB + 2*
      MassG)*Quad(g3) - 3720*(MassB*traceAdjYuYu + MassG*traceAdjYuYu -
      traceTYuAdjYu)*Sqr(g3) - 9*Sqr(g2)*(57*(MassB*traceAdjYuYu + MassWB*
      traceAdjYuYu - traceTYuAdjYu) + 16*(MassB + MassG + MassWB)*Sqr(g3))) +
      125*(18630*MassWB*Power6(g2) + 45*Quad(g2)*(-6*MassWB*(12*traceAdjYdYd +
      4*traceAdjYeYe + 21*traceAdjYuYu) + 36*traceTYdAdjYd + 12*traceTYeAdjYe +
      63*traceTYuAdjYu + 112*(MassG + 2*MassWB)*Sqr(g3)) + 4*(-27*(3*
      traceAdjYdTYdAdjYuYuAdjYdYd + 3*traceAdjYdYdAdjYuTYuAdjYdYd + 6*
      traceAdjYdYd*traceAdjYuTYuAdjYdYd + 2*traceAdjYeYe*traceAdjYuTYuAdjYdYd +
      36*traceAdjYuTYuAdjYuYu*traceAdjYuYu + 3*traceAdjYuYuAdjYdTYdAdjYdYd + 3
      *traceAdjYuYuAdjYuTYuAdjYuYu + 6*traceAdjYuYuAdjYdYd*traceTYdAdjYd + 6*
      traceAdjYdYd*traceTYdAdjYuYuAdjYd + 2*traceAdjYeYe*traceTYdAdjYuYuAdjYd +
      2*traceAdjYuYuAdjYdYd*traceTYeAdjYe + 18*traceAdjYuYuAdjYuYu*
      traceTYuAdjYu) + 5440*MassG*Power6(g3) - 480*(2*MassG*traceAdjYdYd + 4*
      MassG*traceAdjYuYu - traceTYdAdjYd - 2*traceTYuAdjYu)*Quad(g3) - 216*(
      traceAdjYuTYuAdjYdYd + 6*traceAdjYuTYuAdjYuYu - MassG*traceAdjYuYuAdjYdYd
      - 3*MassG*traceAdjYuYuAdjYuYu + traceTYdAdjYuYuAdjYd)*Sqr(g3)) + 36*Sqr(
      g2)*(9*(-2*traceAdjYuTYuAdjYdYd - 2*traceAdjYuTYuAdjYuYu + 2*MassWB*
      traceAdjYuYuAdjYdYd + MassWB*traceAdjYuYuAdjYuYu - 2*traceTYdAdjYuYuAdjYd
      ) + 68*(2*MassG + MassWB)*Quad(g3) - 132*(MassG*traceAdjYuYu + MassWB*
      traceAdjYuYu - traceTYuAdjYu)*Sqr(g3)))) + 0.016*threeLoop*(7761*MassB*
      Power6(g1) + 65*Quad(g1)*(5*MassB*traceAdjYuYu + 27*(2*MassB + MassWB)*
      Sqr(g2) + 88*(2*MassB + MassG)*Sqr(g3)) + 25*Sqr(g1)*(6*(
      traceAdjYuTYuAdjYdYd - 6*traceAdjYuTYuAdjYuYu - MassB*traceAdjYuYuAdjYdYd
      ) + 81*(MassB + 2*MassWB)*Quad(g2) + 176*(MassB + 2*MassG)*Quad(g3) - 63*
      (MassB + MassWB)*traceAdjYuYu*Sqr(g2) - 208*(MassB + MassG)*traceAdjYuYu*
      Sqr(g3)) - 125*(945*MassWB*Power6(g2) - 27*Quad(g2)*(7*MassWB*
      traceAdjYuYu + 8*(MassG + 2*MassWB)*Sqr(g3)) + 16*(120*MassG*Power6(g3) -
      2*MassG*traceAdjYuYu*Quad(g3) + 3*(traceAdjYuTYuAdjYdYd + 6*
      traceAdjYuTYuAdjYuYu)*Sqr(g3)) - 36*Sqr(g2)*(3*traceAdjYuTYuAdjYuYu + 4*(
      2*MassG + MassWB)*Quad(g3) - 4*(MassG + MassWB)*traceAdjYuYu*Sqr(g3))))*(
      Yu*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_2 = ((0.2*threeLoop*(540*
      traceAdjYuYuAdjYuTYuAdjYuYu - 13*traceTYuAdjYu*Quad(g1) - 945*
      traceTYuAdjYu*Quad(g2) - 160*traceTYuAdjYu*Quad(g3) + 36*MassB*
      traceAdjYuYuAdjYuYu*Sqr(g1) + 12*traceTYdAdjYuYuAdjYd*Sqr(g1) - 540*
      MassWB*traceAdjYuYuAdjYuYu*Sqr(g2) + 126*traceTYuAdjYu*Sqr(g1)*Sqr(g2) +
      32*(15*MassG*(traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu) - 15*
      traceTYdAdjYuYuAdjYd + 13*traceTYuAdjYu*Sqr(g1) + 45*traceTYuAdjYu*Sqr(g2
      ))*Sqr(g3))*(Yu*1.2020569031595942) - 0.004*threeLoop*(5174*Power6(g1) +
      65*Quad(g1)*(5*traceAdjYuYu + 54*Sqr(g2) + 176*Sqr(g3)) + 50*Sqr(g1)*(-6*
      traceAdjYuYuAdjYdYd + 18*traceAdjYuYuAdjYuYu + 81*Quad(g2) + 176*Quad(g3)
      - 63*traceAdjYuYu*Sqr(g2) - 208*traceAdjYuYu*Sqr(g3)) - 125*(630*Power6(
      g2) - 27*Quad(g2)*(7*traceAdjYuYu + 16*Sqr(g3)) - 36*Sqr(g2)*(-3*
      traceAdjYuYuAdjYuYu + 8*Quad(g3) - 8*traceAdjYuYu*Sqr(g3)) + 4*(9*
      traceAdjYuYuAdjYuYuAdjYuYu + 320*Power6(g3) - 8*traceAdjYuYu*Quad(g3) -
      24*(traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu)*Sqr(g3))))*(TYu*
      1.2020569031595942) + 0.013333333333333334*threeLoop*(1899*MassB*Quad(g1)
      + 5*Sqr(g1)*(-48*(2*MassB*traceAdjYdYd - MassB*traceAdjYeYe - 2*
      traceTYdAdjYd + traceTYeAdjYe) + 123*(MassB + MassWB)*Sqr(g2) + 152*(
      MassB + MassG)*Sqr(g3)) + 25*(135*MassWB*Quad(g2) + 12*Sqr(g2)*(-3*MassWB
      *(3*traceAdjYdYd + traceAdjYeYe) + 9*traceTYdAdjYd + 3*traceTYeAdjYe + 2*
      (MassG + MassWB)*Sqr(g3)) - 4*(3*(-18*traceAdjYdTYdAdjYdYd - 6*
      traceAdjYeTYeAdjYeYe - 3*traceAdjYuTYuAdjYdYd + 9*traceAdjYdYd*
      traceTYdAdjYd + 3*traceAdjYeYe*traceTYdAdjYd - 3*traceTYdAdjYuYuAdjYd + 3
      *traceAdjYdYd*traceTYeAdjYe + traceAdjYeYe*traceTYeAdjYe) + 8*MassG*Quad(
      g3) - 12*(MassG*(traceAdjYdYd - traceAdjYeYe) - traceTYdAdjYd +
      traceTYeAdjYe)*Sqr(g3))))*(Yu*Yd.adjoint()*Yd) - 0.006666666666666667*
      threeLoop*(1899*Quad(g1) + 10*Sqr(g1)*(-96*traceAdjYdYd + 48*traceAdjYeYe
      + 123*Sqr(g2) + 152*Sqr(g3)) + 25*(135*Quad(g2) - 32*Quad(g3) + 96*(
      traceAdjYdYd - traceAdjYeYe)*Sqr(g3) + 24*Sqr(g2)*(-3*(3*traceAdjYdYd +
      traceAdjYeYe) + 2*Sqr(g3)) + 12*(-18*traceAdjYdYdAdjYdYd + 6*traceAdjYdYd
      *traceAdjYeYe - 6*traceAdjYeYeAdjYeYe - 6*traceAdjYuYuAdjYdYd + 9*Sqr(
      traceAdjYdYd) + Sqr(traceAdjYeYe))))*(Yu*Yd.adjoint()*TYd) +
      0.013333333333333334*threeLoop*(8561*MassB*Quad(g1) + 5*Sqr(g1)*(270*(-(
      MassB*traceAdjYuYu) + traceTYuAdjYu) + 579*(MassB + MassWB)*Sqr(g2) + 424
      *(MassB + MassG)*Sqr(g3)) + 75*(36*(traceAdjYuTYuAdjYdYd + 6*
      traceAdjYuTYuAdjYuYu + traceTYdAdjYuYuAdjYd - 3*traceAdjYuYu*
      traceTYuAdjYu) + 219*MassWB*Quad(g2) - 32*MassG*Quad(g3) + 48*(MassG*
      traceAdjYuYu - traceTYuAdjYu)*Sqr(g3) + 2*Sqr(g2)*(45*(-(MassWB*
      traceAdjYuYu) + traceTYuAdjYu) + 92*(MassG + MassWB)*Sqr(g3))))*(Yu*
      Yu.adjoint()*Yu))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_3 = ((-0.013333333333333334*
      threeLoop*(3082*Quad(g1) + 5*Sqr(g1)*(-165*traceAdjYuYu + 378*Sqr(g2) +
      416*Sqr(g3)) + 25*(-72*(traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu) +
      198*Quad(g2) - 32*Quad(g3) + 96*traceAdjYuYu*Sqr(g3) + 9*Sqr(g2)*(-21*
      traceAdjYuYu + 32*Sqr(g3)) + 108*Sqr(traceAdjYuYu)))*(Yu*Yu.adjoint()*TYu
      ) - 0.0033333333333333335*threeLoop*(1899*Quad(g1) + 10*Sqr(g1)*(-96*
      traceAdjYdYd + 48*traceAdjYeYe + 123*Sqr(g2) + 152*Sqr(g3)) + 25*(135*
      Quad(g2) - 32*Quad(g3) + 96*(traceAdjYdYd - traceAdjYeYe)*Sqr(g3) + 24*
      Sqr(g2)*(-3*(3*traceAdjYdYd + traceAdjYeYe) + 2*Sqr(g3)) + 12*(-18*
      traceAdjYdYdAdjYdYd + 6*traceAdjYdYd*traceAdjYeYe - 6*traceAdjYeYeAdjYeYe
      - 6*traceAdjYuYuAdjYdYd + 9*Sqr(traceAdjYdYd) + Sqr(traceAdjYeYe))))*(
      TYu*Yd.adjoint()*Yd) - 0.016666666666666666*threeLoop*(2671*Quad(g1) +
      5895*Quad(g2) + 2160*Sqr(g2)*(-2*traceAdjYuYu + 5*Sqr(g3)) + 2*Sqr(g1)*(
      -480*traceAdjYuYu + 981*Sqr(g2) + 440*Sqr(g3)) - 100*(8*Quad(g3) - 24*
      traceAdjYuYu*Sqr(g3) + 9*(2*traceAdjYuYuAdjYdYd + 6*traceAdjYuYuAdjYuYu -
      3*Sqr(traceAdjYuYu))))*(TYu*Yu.adjoint()*Yu) - 0.13333333333333333*
      threeLoop*(7*MassB*Quad(g1) - 945*MassWB*Quad(g2) - 2720*MassG*Quad(g3) +
      720*(MassG*traceAdjYdYd - traceTYdAdjYd)*Sqr(g3) + Sqr(g1)*(-36*(2*MassB
      *traceAdjYdYd - MassB*traceAdjYeYe - 2*traceTYdAdjYd + traceTYeAdjYe) +
      27*(MassB + MassWB)*Sqr(g2) + 128*(MassB + MassG)*Sqr(g3)))*(Yu*
      Yd.adjoint()*Yd*1.2020569031595942) + 0.06666666666666667*threeLoop*(7*
      Quad(g1) + 2*Sqr(g1)*(-72*traceAdjYdYd + 36*traceAdjYeYe + 27*Sqr(g2) +
      128*Sqr(g3)) - 5*(189*Quad(g2) + 544*Quad(g3) - 288*traceAdjYdYd*Sqr(g3))
      )*(Yu*Yd.adjoint()*TYd*1.2020569031595942) + 0.08*threeLoop*(117*MassB*
      Quad(g1) - 5*Sqr(g1)*(18*MassB*traceAdjYuYu - 18*traceTYuAdjYu + 123*(
      MassB + MassWB)*Sqr(g2) - 32*(MassB + MassG)*Sqr(g3)) + 25*(81*MassWB*
      Quad(g2) + 16*Sqr(g3)*(-9*MassG*traceAdjYuYu + 9*traceTYuAdjYu + 34*MassG
      *Sqr(g3)) - 6*Sqr(g2)*(-9*MassWB*traceAdjYuYu + 9*traceTYuAdjYu + 16*(
      MassG + MassWB)*Sqr(g3))))*(Yu*Yu.adjoint()*Yu*1.2020569031595942) -
      0.02666666666666667*threeLoop*(52*Quad(g1) - 5*Sqr(g1)*(-9*traceAdjYuYu +
      252*Sqr(g2) + 16*Sqr(g3)) + 25*(108*Quad(g2) - 9*Sqr(g2)*(-9*
      traceAdjYuYu + 16*Sqr(g3)) + 32*Sqr(g3)*(-9*traceAdjYuYu + 17*Sqr(g3))))*
      (Yu*Yu.adjoint()*TYu*1.2020569031595942) + 0.03333333333333333*threeLoop*
      (7*Quad(g1) + 2*Sqr(g1)*(-72*traceAdjYdYd + 36*traceAdjYeYe + 27*Sqr(g2)
      + 128*Sqr(g3)) - 5*(189*Quad(g2) + 544*Quad(g3) - 288*traceAdjYdYd*Sqr(g3
      )))*(TYu*Yd.adjoint()*Yd*1.2020569031595942) - 0.03333333333333333*
      threeLoop*(169*Quad(g1) + 45*Sqr(g2)*(33*Sqr(g2) - 128*Sqr(g3)) + Sqr(g1)
      *(-1206*Sqr(g2) + 640*Sqr(g3)))*(TYu*Yu.adjoint()*Yu*1.2020569031595942))
      *UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_4 = ((-1.3333333333333333*
      threeLoop*(340*Quad(g3) - 9*traceAdjYuYu*(Sqr(g1) - 9*Sqr(g2)) - 180*
      traceAdjYuYu*Sqr(g3))*(TYu*Yu.adjoint()*Yu*1.2020569031595942) +
      threeLoop*(12*traceTYdAdjYd + 4*traceTYeAdjYe - 0.9333333333333333*MassB*
      Sqr(g1) + 6*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 0.13333333333333333*threeLoop*(7*Sqr(
      g1) + 5*(18*traceAdjYdYd + 6*traceAdjYeYe - 9*Sqr(g2) + 64*Sqr(g3)))*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*TYd) + threeLoop*(24*traceTYdAdjYd + 8*
      traceTYeAdjYe - 12*traceTYuAdjYu - 2.533333333333333*MassB*Sqr(g1) - 18*
      MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yu*Yd.adjoint()*Yd*
      Yu.adjoint()*Yu) + threeLoop*(12*traceAdjYdYd + 4*traceAdjYeYe - 6*
      traceAdjYuYu + 1.2666666666666666*Sqr(g1) + 9*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu) +
      0.13333333333333333*threeLoop*(7*Sqr(g1) + 5*(18*traceAdjYdYd + 6*
      traceAdjYeYe - 9*Sqr(g2) + 64*Sqr(g3)))*(Yu*Yd.adjoint()*TYd*Yd.adjoint()
      *Yd) + threeLoop*(24*traceAdjYdYd + 8*traceAdjYeYe - 12*traceAdjYuYu +
      2.533333333333333*Sqr(g1) + 18*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yu*
      Yd.adjoint()*TYd*Yu.adjoint()*Yu) - 1.3333333333333333*threeLoop*(-18*
      traceTYuAdjYu + 5*MassB*Sqr(g1) + 9*MassWB*Sqr(g2) + 64*MassG*Sqr(g3))*(
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + threeLoop*(18*traceAdjYuYu + 7*Sqr(
      g1) + 3*Sqr(g2) + 64*Sqr(g3))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu) +
      1.3333333333333333*threeLoop*(18*traceAdjYuYu + 5*Sqr(g1) + 9*Sqr(g2) +
      64*Sqr(g3))*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu) + threeLoop*(6*
      traceAdjYdYd + 2*traceAdjYeYe + 0.4666666666666667*Sqr(g1) - 3*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) +
      threeLoop*(24*traceAdjYdYd + 8*traceAdjYeYe - 12*traceAdjYuYu +
      2.533333333333333*Sqr(g1) + 18*Sqr(g2) + 42.666666666666664*Sqr(g3))*(TYu
      *Yd.adjoint()*Yd*Yu.adjoint()*Yu) + threeLoop*(18*traceAdjYuYu + 3*Sqr(g1
      ) + 15*Sqr(g2) + 64*Sqr(g3))*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 2.4*
      threeLoop*(MassB*Sqr(g1) - 15*MassWB*Sqr(g2))*(Yu*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) - 2.4*threeLoop*(Sqr(g1) - 15*Sqr(g2)
      )*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*1.2020569031595942) - 7.2*
      threeLoop*(MassB*Sqr(g1) - 5*MassWB*Sqr(g2))*(Yu*Yd.adjoint()*Yd*
      Yu.adjoint()*Yu*1.2020569031595942) + 3.6*threeLoop*(Sqr(g1) - 5*Sqr(g2))
      *(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*1.2020569031595942) - 2.4*threeLoop
      *(Sqr(g1) - 15*Sqr(g2))*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd*
      1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(Yu*Yd.adjoint(
      )*TYd*Yu.adjoint()*Yu*1.2020569031595942) - 6*threeLoop*(Sqr(g1) - 3*Sqr(
      g2))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) - 1.2*
      threeLoop*(Sqr(g1) - 15*Sqr(g2))*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(TYu*Yd.adjoint
      ()*Yd*Yu.adjoint()*Yu*1.2020569031595942) + 6*threeLoop*(Sqr(g1) - 3*Sqr(
      g2))*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 6*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()*TYu) + 12*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*Yu.adjoint()*Yu) + 8*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd) - 2*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu) + 8*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd) - 4*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu) + 12*
      threeLoop*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8*
      threeLoop*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 4*
      threeLoop*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 6*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu) + 4*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu) + 6*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu) + 12*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu) + 4*
      threeLoop*(Yu*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 12*
      threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 12*
      threeLoop*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYu_5 = ((0.00007407407407407407*
      threeLoop*(704194*Power6(g1) + 15*Quad(g1)*(-15*(364*traceAdjYdYd + 468*
      traceAdjYeYe + 2565*traceAdjYuYu) + 6822*Sqr(g2) + 21232*Sqr(g3)) + 150*
      Sqr(g1)*(765*Quad(g2) - 9*Sqr(g2)*(57*traceAdjYuYu + 16*Sqr(g3)) + 2*(54*
      traceAdjYuYuAdjYdYd + 513*traceAdjYuYuAdjYuYu + 436*Quad(g3) - 1860*
      traceAdjYuYu*Sqr(g3))) + 125*(18630*Power6(g2) + 135*Quad(g2)*(-3*(12*
      traceAdjYdYd + 4*traceAdjYeYe + 21*traceAdjYuYu) + 112*Sqr(g3)) + 108*Sqr
      (g2)*(9*(2*traceAdjYuYuAdjYdYd + traceAdjYuYuAdjYuYu) + 68*Quad(g3) - 132
      *traceAdjYuYu*Sqr(g3)) + 4*(81*(3*traceAdjYdYdAdjYuYuAdjYdYd + 6*
      traceAdjYdYd*traceAdjYuYuAdjYdYd + 2*traceAdjYeYe*traceAdjYuYuAdjYdYd +
      18*traceAdjYuYu*traceAdjYuYuAdjYuYu + traceAdjYuYuAdjYuYuAdjYuYu) + 5440*
      Power6(g3) - 1440*(traceAdjYdYd + 2*traceAdjYuYu)*Quad(g3) + 648*(
      traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu)*Sqr(g3))))*TYu + 4*threeLoop
      *(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 4*threeLoop*(TYu
      *Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 12*threeLoop*(TYu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu) + 12*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*1.2020569031595942) + 12
      *threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*
      1.2020569031595942) + 12*threeLoop*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 24*threeLoop*(Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) + 36*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*1.2020569031595942) + 36
      *threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 6*threeLoop*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 30*threeLoop*(TYu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942))*UNITMATRIX(3)).real(
      );

   beta_TYu = beta_TYu_1 + beta_TYu_2 + beta_TYu_3 + beta_TYu_4 +
      beta_TYu_5;


   return beta_TYu;
}

} // namespace flexiblesusy
