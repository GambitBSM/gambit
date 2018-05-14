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

// File generated at Thu 10 May 2018 15:14:30

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
 * Calculates the 1-loop beta function of TYd.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYd_1_loop(const Soft_traces& soft_traces) const
{
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_TYd;

   beta_TYd = (oneOver16PiSqr*(0.13333333333333333*Yd*(7*MassB*Sqr(g1) +
      5*(9*traceAdjYdTYd + 3*traceAdjYeTYe + 9*MassWB*Sqr(g2) + 16*MassG*Sqr(g3
      ))) + (3*traceYdAdjYd + traceYeAdjYe - 0.4666666666666667*Sqr(g1) - 3*Sqr
      (g2) - 5.333333333333333*Sqr(g3))*TYd + 4*(Yd*Yd.adjoint()*TYd) + 2*(Yd*
      Yu.adjoint()*TYu) + 5*(TYd*Yd.adjoint()*Yd) + TYd*Yu.adjoint()*Yu)).real(
      );


   return beta_TYd;
}

/**
 * Calculates the 2-loop beta function of TYd.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYd_2_loop(const Soft_traces& soft_traces) const
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

   beta_TYd = (twoLoop*(0.011111111111111112*(-4*Yd*(287*MassB*Quad(g1) +
      Sqr(g1)*(18*(traceAdjYdTYd - 3*traceAdjYeTYe - MassB*traceYdAdjYd + 3*
      MassB*traceYeAdjYe) + 45*(MassB + MassWB)*Sqr(g2) + 40*(MassB + MassG)*
      Sqr(g3)) + 5*(27*(6*traceYdAdjYdTYdAdjYd + traceYdAdjYuTYuAdjYd + 2*
      traceYeAdjYeTYeAdjYe + traceYuAdjYdTYdAdjYu) + 135*MassWB*Quad(g2) - 32*
      MassG*Quad(g3) - 144*(traceAdjYdTYd - MassG*traceYdAdjYd)*Sqr(g3) + 72*(
      MassG + MassWB)*Sqr(g2)*Sqr(g3))) + (287*Quad(g1) + 2*Sqr(g1)*(-18*
      traceYdAdjYd + 54*traceYeAdjYe + 45*Sqr(g2) + 40*Sqr(g3)) + 5*(-54*(3*
      traceYdAdjYdYdAdjYd + traceYdAdjYuYuAdjYd + traceYeAdjYeYeAdjYe) + 135*
      Quad(g2) - 32*Quad(g3) + 288*traceYdAdjYd*Sqr(g3) + 144*Sqr(g2)*Sqr(g3)))
      *TYd) + (-1.6*MassB*Sqr(g1) - 6*(3*traceAdjYdTYd + traceAdjYeTYe + 2*
      MassWB*Sqr(g2)))*(Yd*Yd.adjoint()*Yd) + (-4*(3*traceYdAdjYd +
      traceYeAdjYe) + 1.2*Sqr(g1) + 6*Sqr(g2))*(Yd*Yd.adjoint()*TYd) + (-6*
      traceAdjYuTYu - 1.6*MassB*Sqr(g1))*(Yd*Yu.adjoint()*Yu) + (-6*
      traceYuAdjYu + 1.6*Sqr(g1))*(Yd*Yu.adjoint()*TYu) + (-5*(3*traceYdAdjYd +
      traceYeAdjYe) + 1.2*Sqr(g1) + 12*Sqr(g2))*(TYd*Yd.adjoint()*Yd) + (-3*
      traceYuAdjYu + 0.8*Sqr(g1))*(TYd*Yu.adjoint()*Yu) - 6*(Yd*Yd.adjoint()*Yd
      *Yd.adjoint()*TYd) - 8*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd) - 2*(Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*TYd) - 4*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*
      TYu) - 4*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd) - 4*(Yd*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu) - 6*(TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 4*(TYd*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 2*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu
      ))).real();


   return beta_TYd;
}

/**
 * Calculates the 3-loop beta function of TYd.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_soft_parameters::calc_beta_TYd_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdYdAdjYdYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeTYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceTYdAdjYuYuAdjYuYuAdjYd;


   Eigen::Matrix<double,3,3> beta_TYd;

   const Eigen::Matrix<double,3,3> beta_TYd_1 = ((-0.00044444444444444447
      *threeLoop*Yd*(389302*MassB*Power6(g1) + 5*Quad(g1)*(15*(-2*MassB*(945*
      traceAdjYdYd + 1899*traceAdjYeYe + 364*traceAdjYuYu) + 945*traceTYdAdjYd
      + 1899*traceTYeAdjYe + 364*traceTYuAdjYu) + 1962*(2*MassB + MassWB)*Sqr(
      g2) + 15568*(2*MassB + MassG)*Sqr(g3)) + 50*Sqr(g1)*(54*(-10*
      traceAdjYdTYdAdjYdYd - 30*traceAdjYeTYeAdjYeYe + 4*traceAdjYuTYuAdjYdYd +
      MassB*(5*traceAdjYdYdAdjYdYd + 15*traceAdjYeYeAdjYeYe - 4*
      traceAdjYuYuAdjYdYd) + 4*traceTYdAdjYuYuAdjYd) + 765*(MassB + 2*MassWB)*
      Quad(g2) + 2120*(MassB + 2*MassG)*Quad(g3) - 1704*(MassB*traceAdjYdYd +
      MassG*traceAdjYdYd - traceTYdAdjYd)*Sqr(g3) - 9*Sqr(g2)*(3*MassWB*
      traceAdjYdYd + 81*MassWB*traceAdjYeYe + 3*MassB*(traceAdjYdYd + 27*
      traceAdjYeYe) - 3*traceTYdAdjYd - 81*traceTYeAdjYe + 16*(MassB + MassG +
      MassWB)*Sqr(g3))) + 125*(18630*MassWB*Power6(g2) + 45*Quad(g2)*(-6*MassWB
      *(21*traceAdjYdYd + 7*traceAdjYeYe + 12*traceAdjYuYu) + 63*traceTYdAdjYd
      + 21*traceTYeAdjYe + 36*traceTYuAdjYu + 112*(MassG + 2*MassWB)*Sqr(g3)) +
      36*Sqr(g2)*(-18*traceAdjYdTYdAdjYdYd + 3*MassWB*(3*traceAdjYdYdAdjYdYd +
      traceAdjYeYeAdjYeYe + 6*traceAdjYuYuAdjYdYd) - 6*(traceAdjYeTYeAdjYeYe +
      3*(traceAdjYuTYuAdjYdYd + traceTYdAdjYuYuAdjYd)) + 68*(2*MassG + MassWB)
      *Quad(g3) - 132*(MassG*traceAdjYdYd + MassWB*traceAdjYdYd - traceTYdAdjYd
      )*Sqr(g3)) + 4*(-27*(3*traceAdjYdYdAdjYdTYdAdjYdYd + 12*traceAdjYdYd*
      traceAdjYeTYeAdjYeYe + 4*traceAdjYeTYeAdjYeYe*traceAdjYeYe + 12*
      traceAdjYdTYdAdjYdYd*(3*traceAdjYdYd + traceAdjYeYe) +
      traceAdjYeYeAdjYeTYeAdjYeYe + 3*traceAdjYuTYuAdjYuYuAdjYdYd + 6*
      traceAdjYuTYuAdjYdYd*traceAdjYuYu + 3*traceAdjYuYuAdjYuTYuAdjYdYd + 18*
      traceAdjYdYdAdjYdYd*traceTYdAdjYd + 6*traceAdjYeYeAdjYeYe*traceTYdAdjYd +
      6*traceAdjYuYu*traceTYdAdjYuYuAdjYd + 3*traceTYdAdjYuYuAdjYuYuAdjYd + 6*
      traceAdjYdYdAdjYdYd*traceTYeAdjYe + 2*traceAdjYeYeAdjYeYe*traceTYeAdjYe +
      6*traceAdjYuYuAdjYdYd*traceTYuAdjYu) + 5440*MassG*Power6(g3) - 480*(2*
      MassG*(2*traceAdjYdYd + traceAdjYuYu) - 2*traceTYdAdjYd - traceTYuAdjYu)*
      Quad(g3) - 216*(6*traceAdjYdTYdAdjYdYd + traceAdjYuTYuAdjYdYd - MassG*(3*
      traceAdjYdYdAdjYdYd + traceAdjYuYuAdjYdYd) + traceTYdAdjYuYuAdjYd)*Sqr(g3
      )))) + 0.016*threeLoop*(4179*MassB*Power6(g1) + 25*(108*
      traceAdjYdTYdAdjYdYd + 81*(MassB + 2*MassWB)*Quad(g2) + 176*(MassB + 2*
      MassG)*Quad(g3))*Sqr(g1) + 35*Quad(g1)*(11*MassB*traceAdjYdYd + 27*(2*
      MassB + MassWB)*Sqr(g2) + 88*(2*MassB + MassG)*Sqr(g3)) - 375*(315*MassWB
      *Power6(g2) + 640*MassG*Power6(g3) - 12*(3*traceAdjYdTYdAdjYdYd + 4*(2*
      MassG + MassWB)*Quad(g3))*Sqr(g2) + 96*traceAdjYdTYdAdjYdYd*Sqr(g3) - 72*
      (MassG + 2*MassWB)*Quad(g2)*Sqr(g3)))*(Yd*1.2020569031595942))*UNITMATRIX
      (3)).real();
   const Eigen::Matrix<double,3,3> beta_TYd_2 = (((-0.04*threeLoop*(162*
      MassB*traceAdjYeYe + 77*traceTYdAdjYd - 81*traceTYeAdjYe)*Quad(g1) + 0.4*
      threeLoop*Sqr(g1)*(-6*(18*traceAdjYeTYeAdjYeYe + MassB*(9*
      traceAdjYdYdAdjYdYd - 9*traceAdjYeYeAdjYeYe + 7*traceAdjYuYuAdjYdYd) - 7*
      (traceAdjYuTYuAdjYdYd + traceTYdAdjYuYuAdjYd)) + 9*(5*MassB*traceAdjYdYd
      + 5*MassWB*traceAdjYdYd - 9*MassB*traceAdjYeYe - 9*MassWB*traceAdjYeYe -
      5*traceTYdAdjYd + 9*traceTYeAdjYe)*Sqr(g2) - 112*(MassB*traceAdjYdYd +
      MassG*traceAdjYdYd - traceTYdAdjYd)*Sqr(g3)) + threeLoop*(63*(2*MassWB*(3
      *traceAdjYdYd + traceAdjYeYe) - 3*traceTYdAdjYd - traceTYeAdjYe)*Quad(g2)
      - 36*Sqr(g2)*(3*MassWB*traceAdjYdYdAdjYdYd - 2*traceAdjYeTYeAdjYeYe +
      MassWB*traceAdjYeYeAdjYeYe + 8*(MassG*traceAdjYdYd + MassWB*traceAdjYdYd
      - traceTYdAdjYd)*Sqr(g3)) + 4*(9*(3*traceAdjYdYdAdjYdTYdAdjYdYd +
      traceAdjYeYeAdjYeTYeAdjYeYe) + 8*(2*MassG*traceAdjYdYd - traceTYdAdjYd)*
      Quad(g3) - 24*(traceAdjYuTYuAdjYdYd - MassG*(3*traceAdjYdYdAdjYdYd +
      traceAdjYuYuAdjYdYd) + traceTYdAdjYuYuAdjYd)*Sqr(g3))))*(Yd*
      1.2020569031595942) - 0.004*threeLoop*(2786*Power6(g1) + 5*Quad(g1)*(77*
      traceAdjYdYd - 81*traceAdjYeYe + 378*Sqr(g2) + 1232*Sqr(g3)) + 50*Sqr(g1)
      *(-6*(9*traceAdjYdYdAdjYdYd - 9*traceAdjYeYeAdjYeYe + 7*
      traceAdjYuYuAdjYdYd) + 81*Quad(g2) + 176*Quad(g3) + 9*(5*traceAdjYdYd - 9
      *traceAdjYeYe)*Sqr(g2) - 112*traceAdjYdYd*Sqr(g3)) - 125*(630*Power6(g2)
      - 9*Quad(g2)*(7*(3*traceAdjYdYd + traceAdjYeYe) + 48*Sqr(g3)) - 36*Sqr(g2
      )*(-3*traceAdjYdYdAdjYdYd - traceAdjYeYeAdjYeYe + 8*Quad(g3) - 8*
      traceAdjYdYd*Sqr(g3)) + 4*(3*(3*traceAdjYdYdAdjYdYdAdjYdYd +
      traceAdjYeYeAdjYeYeAdjYeYe) + 320*Power6(g3) - 8*traceAdjYdYd*Quad(g3) -
      24*(3*traceAdjYdYdAdjYdYd + traceAdjYuYuAdjYdYd)*Sqr(g3))))*(TYd*
      1.2020569031595942) + 0.013333333333333334*threeLoop*(5269*MassB*Quad(g1)
      + 5*Sqr(g1)*(-306*MassB*traceAdjYdYd + 138*MassB*traceAdjYeYe + 306*
      traceTYdAdjYd - 138*traceTYeAdjYe + 381*(MassB + MassWB)*Sqr(g2) + 296*(
      MassB + MassG)*Sqr(g3)) + 75*(219*MassWB*Quad(g2) + 2*Sqr(g2)*(15*(-(
      MassWB*(3*traceAdjYdYd + traceAdjYeYe)) + 3*traceTYdAdjYd + traceTYeAdjYe
      ) + 92*(MassG + MassWB)*Sqr(g3)) - 4*(3*(-18*traceAdjYdTYdAdjYdYd - 6*
      traceAdjYeTYeAdjYeYe - 3*traceAdjYuTYuAdjYdYd + 9*traceAdjYdYd*
      traceTYdAdjYd + 3*traceAdjYeYe*traceTYdAdjYd - 3*traceTYdAdjYuYuAdjYd + 3
      *traceAdjYdYd*traceTYeAdjYe + traceAdjYeYe*traceTYeAdjYe) + 8*MassG*Quad(
      g3) - 12*(MassG*traceAdjYdYd - MassG*traceAdjYeYe - traceTYdAdjYd +
      traceTYeAdjYe)*Sqr(g3))))*(Yd*Yd.adjoint()*Yd) - 0.013333333333333334*
      threeLoop*(1792*Quad(g1) + 5*Sqr(g1)*(-201*traceAdjYdYd + 252*Sqr(g2) +
      224*Sqr(g3)) + 25*(198*Quad(g2) - 32*Quad(g3) + 9*Sqr(g2)*(-21*
      traceAdjYdYd + 32*Sqr(g3))))*(Yd*Yd.adjoint()*TYd))*UNITMATRIX(3)).real()
      ;
   const Eigen::Matrix<double,3,3> beta_TYd_3 = ((threeLoop*(72*
      traceAdjYdYdAdjYdYd - 24*traceAdjYdYd*traceAdjYeYe + 24*
      traceAdjYeYeAdjYeYe + 24*traceAdjYuYuAdjYdYd - 6.2*traceAdjYeYe*Sqr(g1) +
      21*traceAdjYeYe*Sqr(g2) - 32*(traceAdjYdYd - traceAdjYeYe)*Sqr(g3) - 36*
      Sqr(traceAdjYdYd) - 4*Sqr(traceAdjYeYe))*(Yd*Yd.adjoint()*TYd) +
      0.013333333333333334*threeLoop*(3767*MassB*Quad(g1) + 15*Sqr(g1)*(59*(
      MassB + MassWB)*Sqr(g2) + 4*(-5*MassB*traceAdjYuYu + 5*traceTYuAdjYu + 34
      *(MassB + MassG)*Sqr(g3))) + 25*(36*(traceAdjYuTYuAdjYdYd + 6*
      traceAdjYuTYuAdjYuYu + traceTYdAdjYuYuAdjYd - 3*traceAdjYuYu*
      traceTYuAdjYu) + 135*MassWB*Quad(g2) - 32*MassG*Quad(g3) + 48*(MassG*
      traceAdjYuYu - traceTYuAdjYu)*Sqr(g3) + 12*Sqr(g2)*(-9*MassWB*
      traceAdjYuYu + 9*traceTYuAdjYu + 2*(MassG + MassWB)*Sqr(g3))))*(Yd*
      Yu.adjoint()*Yu) - 0.006666666666666667*threeLoop*(3767*Quad(g1) + 30*Sqr
      (g1)*(-20*traceAdjYuYu + 59*Sqr(g2) + 136*Sqr(g3)) + 25*(-72*(
      traceAdjYuYuAdjYdYd + 3*traceAdjYuYuAdjYuYu) + 135*Quad(g2) - 32*Quad(g3)
      + 96*traceAdjYuYu*Sqr(g3) + 24*Sqr(g2)*(-9*traceAdjYuYu + 2*Sqr(g3)) +
      108*Sqr(traceAdjYuYu)))*(Yd*Yu.adjoint()*TYu) - 0.0033333333333333335*
      threeLoop*(8639*Quad(g1) + 29475*Quad(g2) + 3600*Sqr(g2)*(-2*(3*
      traceAdjYdYd + traceAdjYeYe) + 15*Sqr(g3)) + 10*Sqr(g1)*(-516*
      traceAdjYdYd + 228*traceAdjYeYe + 639*Sqr(g2) + 440*Sqr(g3)) + 500*(-8*
      Quad(g3) + 24*(traceAdjYdYd - traceAdjYeYe)*Sqr(g3) + 3*(-18*
      traceAdjYdYdAdjYdYd + 6*traceAdjYdYd*traceAdjYeYe - 6*traceAdjYeYeAdjYeYe
      - 6*traceAdjYuYuAdjYdYd + 9*Sqr(traceAdjYdYd) + Sqr(traceAdjYeYe))))*(
      TYd*Yd.adjoint()*Yd) + (6*threeLoop*traceAdjYuYuAdjYdYd + 18*threeLoop*
      traceAdjYuYuAdjYuYu - 12.556666666666667*threeLoop*Quad(g1) - 11.25*
      threeLoop*Quad(g2) + 2.6666666666666665*threeLoop*Quad(g3) - 8*threeLoop*
      traceAdjYuYu*Sqr(g3) - 0.1*threeLoop*Sqr(g1)*(-20*traceAdjYuYu + 59*Sqr(
      g2) + 136*Sqr(g3)) + Sqr(g2)*(18*threeLoop*traceAdjYuYu - 4*threeLoop*Sqr
      (g3)) - 9*threeLoop*Sqr(traceAdjYuYu))*(TYd*Yu.adjoint()*Yu) - 0.08*
      threeLoop*(7*MassB*Quad(g1) + 15*Sqr(g1)*(17*(MassB + MassWB)*Sqr(g2) + 2
      *(-9*MassB*traceAdjYdYd + 7*MassB*traceAdjYeYe + 9*traceTYdAdjYd - 7*
      traceTYeAdjYe + 16*(MassB + MassG)*Sqr(g3))) - 25*(81*MassWB*Quad(g2) +
      16*Sqr(g3)*(-9*MassG*traceAdjYdYd + 9*traceTYdAdjYd + 34*MassG*Sqr(g3)) -
      6*Sqr(g2)*(-3*MassWB*(3*traceAdjYdYd + traceAdjYeYe) + 9*traceTYdAdjYd +
      3*traceTYeAdjYe + 16*(MassG + MassWB)*Sqr(g3))))*(Yd*Yd.adjoint()*Yd*
      1.2020569031595942) + 0.02666666666666667*threeLoop*(14*Quad(g1) + 5*Sqr(
      g1)*(-117*traceAdjYdYd + 81*traceAdjYeYe + 90*Sqr(g2) + 208*Sqr(g3)) - 25
      *(108*Quad(g2) - 9*Sqr(g2)*(-9*traceAdjYdYd + 16*Sqr(g3)) + 32*Sqr(g3)*(
      -9*traceAdjYdYd + 17*Sqr(g3))))*(Yd*Yd.adjoint()*TYd*1.2020569031595942))
      *UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYd_4 = ((-18*threeLoop*
      traceAdjYeYe*Sqr(g2)*(Yd*Yd.adjoint()*TYd*1.2020569031595942) -
      0.02666666666666667*threeLoop*(143*MassB*Quad(g1) - 25*(189*MassWB*Quad(
      g2) + 544*MassG*Quad(g3) - 144*(MassG*traceAdjYuYu - traceTYuAdjYu)*Sqr(
      g3)) + 5*Sqr(g1)*(135*(MassB + MassWB)*Sqr(g2) + 8*(-9*MassB*traceAdjYuYu
      + 9*traceTYuAdjYu + 16*(MassB + MassG)*Sqr(g3))))*(Yd*Yu.adjoint()*Yu*
      1.2020569031595942) + 0.013333333333333334*threeLoop*(143*Quad(g1) + 10*
      Sqr(g1)*(-72*traceAdjYuYu + 135*Sqr(g2) + 128*Sqr(g3)) - 25*(189*Quad(g2)
      + 544*Quad(g3) - 288*traceAdjYuYu*Sqr(g3)))*(Yd*Yu.adjoint()*TYu*
      1.2020569031595942) + 0.006666666666666667*threeLoop*(7*Quad(g1) + 10*Sqr
      (g1)*(-252*traceAdjYdYd + 216*traceAdjYeYe + 279*Sqr(g2) + 448*Sqr(g3)) -
      25*(297*Quad(g2) - 72*Sqr(g2)*(-9*traceAdjYdYd - 3*traceAdjYeYe + 16*Sqr
      (g3)) + 160*(17*Quad(g3) - 9*traceAdjYdYd*Sqr(g3))))*(TYd*Yd.adjoint()*Yd
      *1.2020569031595942) + 0.006666666666666667*threeLoop*(143*Quad(g1) + 10*
      Sqr(g1)*(-72*traceAdjYuYu + 135*Sqr(g2) + 128*Sqr(g3)) - 25*(189*Quad(g2)
      + 544*Quad(g3) - 288*traceAdjYuYu*Sqr(g3)))*(TYd*Yu.adjoint()*Yu*
      1.2020569031595942) - 0.26666666666666666*threeLoop*(MassB*Sqr(g1) + 5*(
      -18*traceTYdAdjYd - 6*traceTYeAdjYe + 9*MassWB*Sqr(g2) + 64*MassG*Sqr(g3)
      ))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + (0.6*threeLoop*Sqr(g1) +
      threeLoop*(18*traceAdjYdYd + 6*traceAdjYeYe + 3*Sqr(g2) + 64*Sqr(g3)))*(
      Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd) + 0.26666666666666666*threeLoop*(Sqr
      (g1) + 5*(18*traceAdjYdYd + 6*traceAdjYeYe + 9*Sqr(g2) + 64*Sqr(g3)))*(Yd
      *Yd.adjoint()*TYd*Yd.adjoint()*Yd) + 0.13333333333333333*threeLoop*(29*
      MassB*Sqr(g1) - 5*(6*(3*traceTYdAdjYd + traceTYeAdjYe - 6*traceTYuAdjYu)
      + 27*MassWB*Sqr(g2) + 64*MassG*Sqr(g3)))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()
      *Yd) + (-6*threeLoop*traceAdjYdYd - 2*threeLoop*traceAdjYeYe + 12*
      threeLoop*traceAdjYuYu - 1.9333333333333333*threeLoop*Sqr(g1) + 9*
      threeLoop*Sqr(g2) + 21.333333333333332*threeLoop*Sqr(g3))*(Yd*Yu.adjoint(
      )*Yu*Yd.adjoint()*TYd) - 0.6666666666666666*threeLoop*(11*MassB*Sqr(g1) -
      9*(2*traceTYuAdjYu + MassWB*Sqr(g2)) + 64*MassG*Sqr(g3))*(Yd*Yu.adjoint(
      )*Yu*Yu.adjoint()*Yu) + 0.6666666666666666*threeLoop*(18*traceAdjYuYu +
      11*Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu
      ) - 0.13333333333333333*threeLoop*(29*Sqr(g1) - 5*(-6*(3*traceAdjYdYd +
      traceAdjYeYe - 6*traceAdjYuYu) + 27*Sqr(g2) + 64*Sqr(g3)))*(Yd*Yu.adjoint
      ()*TYu*Yd.adjoint()*Yd) + 0.6666666666666666*threeLoop*(18*traceAdjYuYu +
      11*Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*
      Yu) + (-0.2*threeLoop*Sqr(g1) + threeLoop*(18*traceAdjYdYd + 6*
      traceAdjYeYe + 15*Sqr(g2) + 64*Sqr(g3)))*(TYd*Yd.adjoint()*Yd*Yd.adjoint(
      )*Yd) - 0.13333333333333333*threeLoop*(29*Sqr(g1) - 5*(-6*(3*traceAdjYdYd
      + traceAdjYeYe - 6*traceAdjYuYu) + 27*Sqr(g2) + 64*Sqr(g3)))*(TYd*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 0.3333333333333333*threeLoop*(18*
      traceAdjYuYu + 11*Sqr(g1) - 9*Sqr(g2) + 64*Sqr(g3))*(TYd*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu) - 1.2*threeLoop*(Sqr(g1) - 15*Sqr(g2))*(Yd*Yd.adjoint()*
      Yd*Yd.adjoint()*TYd*1.2020569031595942) - 7.2*MassB*threeLoop*Sqr(g1)*(Yd
      *Yu.adjoint()*Yu*Yd.adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real
      ();
   const Eigen::Matrix<double,3,3> beta_TYd_5 = ((0.00007407407407407407*
      threeLoop*(389302*Power6(g1) + 15*Quad(g1)*(-15*(945*traceAdjYdYd + 1899*
      traceAdjYeYe + 364*traceAdjYuYu) + 1962*Sqr(g2) + 15568*Sqr(g3)) + 150*
      Sqr(g1)*(54*(5*traceAdjYdYdAdjYdYd + 15*traceAdjYeYeAdjYeYe - 4*
      traceAdjYuYuAdjYdYd) + 765*Quad(g2) + 2120*Quad(g3) - 1704*traceAdjYdYd*
      Sqr(g3) - 9*Sqr(g2)*(3*traceAdjYdYd + 81*traceAdjYeYe + 16*Sqr(g3))) +
      125*(18630*Power6(g2) + 135*Quad(g2)*(-3*(21*traceAdjYdYd + 7*
      traceAdjYeYe + 12*traceAdjYuYu) + 112*Sqr(g3)) + 108*Sqr(g2)*(3*(3*
      traceAdjYdYdAdjYdYd + traceAdjYeYeAdjYeYe + 6*traceAdjYuYuAdjYdYd) + 68*
      Quad(g3) - 132*traceAdjYdYd*Sqr(g3)) + 4*(27*(3*
      traceAdjYdYdAdjYdYdAdjYdYd + 18*traceAdjYdYdAdjYdYd*traceAdjYeYe + 6*
      traceAdjYeYe*traceAdjYeYeAdjYeYe + 18*traceAdjYdYd*(3*traceAdjYdYdAdjYdYd
      + traceAdjYeYeAdjYeYe) + traceAdjYeYeAdjYeYeAdjYeYe + 18*traceAdjYuYu*
      traceAdjYuYuAdjYdYd + 9*traceAdjYuYuAdjYuYuAdjYdYd) + 5440*Power6(g3) -
      1440*(2*traceAdjYdYd + traceAdjYuYu)*Quad(g3) + 648*(3*
      traceAdjYdYdAdjYdYd + traceAdjYuYuAdjYdYd)*Sqr(g3))))*TYd + 36*MassWB*
      threeLoop*Sqr(g2)*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*1.2020569031595942)
      + 3.6*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*
      TYd*1.2020569031595942) + 12*threeLoop*(MassB*Sqr(g1) - 3*MassWB*Sqr(g2))
      *(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) - 12*threeLoop*(
      Sqr(g1) - 3*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(Yd*Yu.adjoint(
      )*TYu*Yd.adjoint()*Yd*1.2020569031595942) - 12*threeLoop*(Sqr(g1) - 3*Sqr
      (g2))*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu*1.2020569031595942) + 1.2*
      threeLoop*(Sqr(g1) - 15*Sqr(g2))*(TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      1.2020569031595942) + 7.2*threeLoop*(Sqr(g1) - 5*Sqr(g2))*(TYd*Yu.adjoint
      ()*Yu*Yd.adjoint()*Yd*1.2020569031595942) - 6*threeLoop*(Sqr(g1) - 3*Sqr(
      g2))*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 6*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd) + 12*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd) + 6*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd) + 4*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd) + 12*
      threeLoop*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 4*
      threeLoop*(Yd*Yd.adjoint()*TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 2*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd) + 8*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu) - 4*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd) + 8*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu) + 6*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()*TYd) + 12*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yd.adjoint()*Yd) - 4*
      threeLoop*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 8*
      threeLoop*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 12*
      threeLoop*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 12*
      threeLoop*(TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 4*
      threeLoop*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) + 4*
      threeLoop*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 12*
      threeLoop*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 24*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*
      1.2020569031595942) + 36*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*
      Yd.adjoint()*Yd*1.2020569031595942) + 36*threeLoop*(Yd*Yd.adjoint()*TYd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 12*threeLoop*(Yd*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) + 12
      *threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12*threeLoop*(Yd*Yu.adjoint()*TYu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*1.2020569031595942) + 30*threeLoop*(TYd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 6*threeLoop*(TYd*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942))*
      UNITMATRIX(3)).real();

   beta_TYd = beta_TYd_1 + beta_TYd_2 + beta_TYd_3 + beta_TYd_4 +
      beta_TYd_5;


   return beta_TYd;
}

} // namespace flexiblesusy
