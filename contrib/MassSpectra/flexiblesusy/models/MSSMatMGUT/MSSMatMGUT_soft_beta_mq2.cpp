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

// File generated at Thu 10 May 2018 15:08:43

#include "MSSMatMGUT_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of mq2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_mq2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = (oneOver16PiSqr*(2*mHd2*(Yd.adjoint()*Yd) + 2*mHu2*(
      Yu.adjoint()*Yu) + 2*((TYd).adjoint()*TYd) + 2*((TYu).adjoint()*TYu) +
      mq2*Yd.adjoint()*Yd + mq2*Yu.adjoint()*Yu + 2*(Yd.adjoint()*md2*Yd) +
      Yd.adjoint()*Yd*mq2 + 2*(Yu.adjoint()*mu2*Yu) + Yu.adjoint()*Yu*mq2 +
      0.06666666666666667*(3.872983346207417*g1*Tr11 - 2*AbsSqr(MassB)*Sqr(g1)
      - 90*AbsSqr(MassWB)*Sqr(g2) - 160*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3)))
      .real();


   return beta_mq2;
}

/**
 * Calculates the 2-loop beta function of mq2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_mq2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceconjTYdTpTYd = TRACE_STRUCT.traceconjTYdTpTYd;
   const double traceconjTYeTpTYe = TRACE_STRUCT.traceconjTYeTpTYe;
   const double tracemd2YdAdjYd = TRACE_STRUCT.tracemd2YdAdjYd;
   const double traceme2YeAdjYe = TRACE_STRUCT.traceme2YeAdjYe;
   const double traceml2AdjYeYe = TRACE_STRUCT.traceml2AdjYeYe;
   const double tracemq2AdjYdYd = TRACE_STRUCT.tracemq2AdjYdYd;
   const double traceconjTYdTpYd = TRACE_STRUCT.traceconjTYdTpYd;
   const double traceconjTYeTpYe = TRACE_STRUCT.traceconjTYeTpYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double traceconjTYuTpYu = TRACE_STRUCT.traceconjTYuTpYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr22 = TRACE_STRUCT.Tr22;
   const double Tr23 = TRACE_STRUCT.Tr23;


   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = (twoLoop*((-2*(3*traceconjTYdTpTYd + traceconjTYeTpTYe + 3*
      tracemd2YdAdjYd + traceme2YeAdjYe + traceml2AdjYeYe + 3*tracemq2AdjYdYd +
      6*mHd2*traceYdAdjYd + 2*mHd2*traceYeAdjYe) + 0.8*mHd2*Sqr(g1) + 1.6*
      AbsSqr(MassB)*Sqr(g1))*(Yd.adjoint()*Yd) + (-2*(3*traceconjTYdTpYd +
      traceconjTYeTpYe) - 0.8*Conj(MassB)*Sqr(g1))*(Yd.adjoint()*TYd) + (-6*(
      traceconjTYuTpTYu + tracemq2AdjYuYu + tracemu2YuAdjYu + 2*mHu2*
      traceYuAdjYu) + 1.6*mHu2*Sqr(g1) + 3.2*AbsSqr(MassB)*Sqr(g1))*(Yu.adjoint
      ()*Yu) + (-6*traceconjTYuTpYu - 1.6*Conj(MassB)*Sqr(g1))*(Yu.adjoint()*
      TYu) + (-2*(3*traceAdjYdTYd + traceAdjYeTYe) - 0.8*MassB*Sqr(g1))*((TYd)
      .adjoint()*Yd) + (-2*(3*traceYdAdjYd + traceYeAdjYe) + 0.8*Sqr(g1))*((TYd
      ).adjoint()*TYd) + (-6*traceAdjYuTYu - 1.6*MassB*Sqr(g1))*((TYu).adjoint(
      )*Yu) + (-6*traceYuAdjYu + 1.6*Sqr(g1))*((TYu).adjoint()*TYu) + (-3*
      traceYdAdjYd - traceYeAdjYe + 0.4*Sqr(g1))*(mq2*Yd.adjoint()*Yd) + (-3*
      traceYuAdjYu + 0.8*Sqr(g1))*(mq2*Yu.adjoint()*Yu) + (-2*(3*traceYdAdjYd +
      traceYeAdjYe) + 0.8*Sqr(g1))*(Yd.adjoint()*md2*Yd) + (-3*traceYdAdjYd -
      traceYeAdjYe + 0.4*Sqr(g1))*(Yd.adjoint()*Yd*mq2) + (-6*traceYuAdjYu +
      1.6*Sqr(g1))*(Yu.adjoint()*mu2*Yu) + (-3*traceYuAdjYu + 0.8*Sqr(g1))*(
      Yu.adjoint()*Yu*mq2) - 8*mHd2*(Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 4*(
      Yd.adjoint()*Yd*(TYd).adjoint()*TYd) - 4*(Yd.adjoint()*TYd*(TYd).adjoint(
      )*Yd) - 8*mHu2*(Yu.adjoint()*Yu*Yu.adjoint()*Yu) - 4*(Yu.adjoint()*Yu*(
      TYu).adjoint()*TYu) - 4*(Yu.adjoint()*TYu*(TYu).adjoint()*Yu) - 4*((TYd)
      .adjoint()*Yd*Yd.adjoint()*TYd) - 4*((TYd).adjoint()*TYd*Yd.adjoint()*Yd)
      - 4*((TYu).adjoint()*Yu*Yu.adjoint()*TYu) - 4*((TYu).adjoint()*TYu*
      Yu.adjoint()*Yu) - 2*(mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 2*(mq2*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu) - 4*(Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd
      ) - 4*(Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd) - 4*(Yd.adjoint()*Yd*
      Yd.adjoint()*md2*Yd) - 2*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2) - 4*(
      Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu) - 4*(Yu.adjoint()*Yu*mq2*Yu.adjoint(
      )*Yu) - 4*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu) - 2*(Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*mq2) + 0.0044444444444444444*(30*(g1*(g1*Tr2U111 +
      7.745966692414834*Tr31) + 45*Tr22*Quad(g2) + 80*Tr23*Quad(g3)) + 80*Conj(
      MassG)*Sqr(g3)*((MassB + 2*MassG)*Sqr(g1) + 45*(2*MassG + MassWB)*Sqr(g2)
      - 120*MassG*Sqr(g3)) + Conj(MassB)*Sqr(g1)*(597*MassB*Sqr(g1) + 45*(2*
      MassB + MassWB)*Sqr(g2) + 80*(2*MassB + MassG)*Sqr(g3)) + 45*Conj(MassWB)
      *Sqr(g2)*((MassB + 2*MassWB)*Sqr(g1) + 165*MassWB*Sqr(g2) + 80*(MassG + 2
      *MassWB)*Sqr(g3)))*UNITMATRIX(3))).real();


   return beta_mq2;
}

/**
 * Calculates the 3-loop beta function of mq2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_mq2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double tracemd2 = TRACE_STRUCT.tracemd2;
   const double traceme2 = TRACE_STRUCT.traceme2;
   const double traceml2 = TRACE_STRUCT.traceml2;
   const double tracemq2 = TRACE_STRUCT.tracemq2;
   const double tracemu2 = TRACE_STRUCT.tracemu2;
   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjTYdYd = TRACE_STRUCT.traceAdjTYdYd;
   const double traceAdjTYeYe = TRACE_STRUCT.traceAdjTYeYe;
   const double traceAdjTYuYu = TRACE_STRUCT.traceAdjTYuYu;
   const double traceTYdAdjYd = TRACE_STRUCT.traceTYdAdjYd;
   const double traceTYdAdjTYd = TRACE_STRUCT.traceTYdAdjTYd;
   const double traceTYeAdjYe = TRACE_STRUCT.traceTYeAdjYe;
   const double traceTYeAdjTYe = TRACE_STRUCT.traceTYeAdjTYe;
   const double traceTYuAdjYu = TRACE_STRUCT.traceTYuAdjYu;
   const double traceTYuAdjTYu = TRACE_STRUCT.traceTYuAdjTYu;
   const double traceYdAdjYdmd2 = TRACE_STRUCT.traceYdAdjYdmd2;
   const double traceYeAdjYeme2 = TRACE_STRUCT.traceYeAdjYeme2;
   const double traceYuAdjYumu2 = TRACE_STRUCT.traceYuAdjYumu2;
   const double traceAdjYdYdmq2 = TRACE_STRUCT.traceAdjYdYdmq2;
   const double traceAdjYeYeml2 = TRACE_STRUCT.traceAdjYeYeml2;
   const double traceAdjYuYumq2 = TRACE_STRUCT.traceAdjYuYumq2;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjYuYuAdjTYuYu = TRACE_STRUCT.traceAdjYuYuAdjTYuYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYu =
      TRACE_STRUCT.traceAdjYuTYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYu =
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjYdYdAdjTYdYd = TRACE_STRUCT.traceAdjYdYdAdjTYdYd;
   const double traceAdjYeYeAdjTYeYe = TRACE_STRUCT.traceAdjYeYeAdjTYeYe;
   const double traceAdjTYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceAdjTYuTYuAdjYuYu =
      TRACE_STRUCT.traceAdjTYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceTYdAdjTYuYuAdjYd =
      TRACE_STRUCT.traceTYdAdjTYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2;
   const double traceYuAdjYdYdAdjYumu2 =
      TRACE_STRUCT.traceYuAdjYdYdAdjYumu2;
   const double traceYuAdjYuYuAdjYumu2 =
      TRACE_STRUCT.traceYuAdjYuYuAdjYumu2;
   const double traceAdjYdYdAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYuYumq2;
   const double traceAdjYuYuAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2;
   const double traceAdjYdTYdAdjTYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjTYdYd;
   const double traceAdjYeTYeAdjTYeYe =
      TRACE_STRUCT.traceAdjYeTYeAdjTYeYe;
   const double traceAdjTYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjTYdTYdAdjYdYd;
   const double traceAdjTYeTYeAdjYeYe =
      TRACE_STRUCT.traceAdjTYeTYeAdjYeYe;
   const double traceYdAdjYdYdAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdmd2;
   const double traceYeAdjYeYeAdjYeme2 =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeme2;
   const double traceAdjYdYdAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdmq2;
   const double traceAdjYeYeAdjYeYeml2 =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeml2;
   const double traceAdjYuYuAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYuYumq2;


   Eigen::Matrix<double,3,3> beta_mq2;

   const Eigen::Matrix<double,3,3> beta_mq2_1 = (threeLoop*(Power6(g1)*(
      -0.5306666666666666*mHd2 - 0.5306666666666666*mHu2 - 0.3537777777777778*
      tracemd2 - 1.0613333333333332*traceme2 - 0.5306666666666666*traceml2 -
      0.1768888888888889*tracemq2 - 1.4151111111111112*tracemu2 +
      28.156793810928004*Sqr(MassB)) + Quad(g3)*(MassG*(106.66666666666667*
      traceAdjTYdYd + 106.66666666666667*traceAdjTYuYu) - 64.*mHd2*traceAdjYdYd
      - 64.*traceAdjYdYdmq2 - 64.*mHu2*traceAdjYuYu - 64.*traceAdjYuYumq2 + (
      -320.*traceAdjYdYd - 320.*traceAdjYuYu)*Sqr(MassG) + Sqr(g3)*(
      35.55555555555556*tracemd2 + 71.11111111111111*tracemq2 +
      11510.908127376795*Sqr(MassG))) + Sqr(g1)*(Quad(g3)*(-61.160723075982006*
      MassB*MassG - 0.35555555555555557*tracemd2 - 0.7111111111111111*tracemq2
      - 0.35555555555555557*tracemu2 - 18.847028204657676*Sqr(MassB) -
      89.6077512806396*Sqr(MassG)) + Quad(g2)*(-27.893287324741706*MassB*MassWB
      - 0.2*mHd2 - 0.2*mHu2 - 0.2*traceml2 - 0.6*tracemq2 - 8.546643662370855*
      Sqr(MassB) - 41.03993098711257*Sqr(MassWB)) + Sqr(g2)*Sqr(g3)*(-6.4*MassB
      *MassG - 6.4*MassB*MassWB - 6.4*MassG*MassWB - 6.4*Sqr(MassB) - 6.4*Sqr(
      MassG) - 6.4*Sqr(MassWB))) + Quad(g1)*(0.9333333333333333*MassB*
      traceAdjTYdYd + 1.2*MassB*traceAdjTYeYe + 1.7333333333333334*MassB*
      traceAdjTYuYu - 0.56*mHd2*traceAdjYdYd - 0.56*traceAdjYdYdmq2 - 0.72*mHd2
      *traceAdjYeYe - 0.72*traceAdjYeYeml2 - 1.04*mHu2*traceAdjYuYu - 1.04*
      traceAdjYuYumq2 - 2.8*traceAdjYdYd*Sqr(MassB) - 3.6000000000000005*
      traceAdjYeYe*Sqr(MassB) - 5.2*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(
      -10.027183418709308*MassB*MassG - 0.21333333333333335*mHd2 -
      0.21333333333333335*mHu2 - 0.14222222222222222*tracemd2 -
      0.4266666666666667*traceme2 - 0.21333333333333335*traceml2 -
      0.07111111111111111*tracemq2 - 0.5688888888888889*tracemu2 -
      15.040775128063965*Sqr(MassB) - 3.8402583760213207*Sqr(MassG)) + Sqr(g2)*
      (-4.312885821649448*MassB*MassWB - 0.12*mHd2 - 0.12*mHu2 - 0.08*tracemd2
      - 0.24*traceme2 - 0.12*traceml2 - 0.04*tracemq2 - 0.32*tracemu2 -
      6.469328732474171*Sqr(MassB) - 1.796442910824724*Sqr(MassWB))) + Quad(g3)
      *Sqr(g2)*(-628.3847762199263*MassG*MassWB - 16.*tracemd2 - 32.*tracemq2 -
      16.*tracemu2 - 846.5771643298895*Sqr(MassG) - 266.19238810996313*Sqr(
      MassWB)) + Power6(g2)*(-3.*mHd2 - 3.*mHu2 - 3.*traceml2 - 9.*tracemq2 +
      6700.775093943266*Sqr(MassWB)) + Quad(g2)*(MassWB*(90.*traceAdjTYdYd +
      30.000000000000004*traceAdjTYeYe + 90.*traceAdjTYuYu) - 54.*mHd2*
      traceAdjYdYd - 54.*traceAdjYdYdmq2 - 18.*mHd2*traceAdjYeYe - 18.*
      traceAdjYeYeml2 - 54.*mHu2*traceAdjYuYu - 54.*traceAdjYuYumq2 + Sqr(g3)*(
      -638.5771643298895*MassG*MassWB - 16.*mHd2 - 16.*mHu2 - 16.*traceml2 -
      48.*tracemq2 - 247.28858216494473*Sqr(MassG) - 893.8657464948342*Sqr(
      MassWB)) + (-270.*traceAdjYdYd - 90.*traceAdjYeYe - 270.*traceAdjYuYu)*
      Sqr(MassWB)))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_2 = ((threeLoop*(
      35.55555555555556*tracemu2*Power6(g3) + (-0.56*traceTYdAdjTYd +
      0.9333333333333333*MassB*traceTYdAdjYd - 0.72*traceTYeAdjTYe + 1.2*MassB*
      traceTYeAdjYe - 1.04*traceTYuAdjTYu + 1.7333333333333334*MassB*
      traceTYuAdjYu - 0.56*traceYdAdjYdmd2 - 0.72*traceYeAdjYeme2 - 1.04*
      traceYuAdjYumu2)*Quad(g1) + (-54.*traceTYdAdjTYd + 90.*MassWB*
      traceTYdAdjYd - 18.*traceTYeAdjTYe + 30.000000000000004*MassWB*
      traceTYeAdjYe - 54.*traceTYuAdjTYu + 90.*MassWB*traceTYuAdjYu - 54.*
      traceYdAdjYdmd2 - 18.*traceYeAdjYeme2 - 54.*traceYuAdjYumu2)*Quad(g2) + (
      -64.*traceTYdAdjTYd + 106.66666666666667*MassG*traceTYdAdjYd - 64.*
      traceTYuAdjTYu + 106.66666666666667*MassG*traceTYuAdjYu - 64.*
      traceYdAdjYdmd2 - 64.*traceYuAdjYumu2)*Quad(g3)) + threeLoop*(72.*
      traceAdjTYdTYdAdjYdYd + 12.*traceAdjTYdTYdAdjYuYu + 24.*
      traceAdjTYeTYeAdjYeYe + 12.*traceAdjTYuTYuAdjYdYd + 72.*
      traceAdjYdTYdAdjTYdYd + 108.*mHd2*traceAdjYdYdAdjYdYd + 72.*
      traceAdjYdYdAdjYdYdmq2 + 12.*traceAdjYdYdAdjYuYumq2 - 36.*traceAdjYdYd*
      traceAdjYdYdmq2 + 24.*traceAdjYeTYeAdjTYeYe - 36.*mHd2*traceAdjYdYd*
      traceAdjYeYe - 12.*traceAdjYdYdmq2*traceAdjYeYe + 36.*mHd2*
      traceAdjYeYeAdjYeYe + 24.*traceAdjYeYeAdjYeYeml2 - 12.*traceAdjYdYd*
      traceAdjYeYeml2 - 4.*traceAdjYeYe*traceAdjYeYeml2 + 12.*
      traceAdjYuTYuAdjTYdYd + 24.*mHd2*traceAdjYuYuAdjYdYd + 12.*mHu2*
      traceAdjYuYuAdjYdYd + 12.*traceAdjYuYuAdjYdYdmq2 - 36.*traceAdjYdYd*
      traceTYdAdjTYd - 12.*traceAdjYeYe*traceTYdAdjTYd + 5.333333333333333*mHd2
      *Quad(g3) + 16.*MassG*traceAdjTYdYd*Sqr(g3) - 16.*MassG*traceAdjTYeYe*Sqr
      (g3) - 32.*mHd2*traceAdjYdYd*Sqr(g3) - 16.*traceAdjYdYdmq2*Sqr(g3) + 32.*
      mHd2*traceAdjYeYe*Sqr(g3) + 16.*traceAdjYeYeml2*Sqr(g3) - 16.*
      traceTYdAdjTYd*Sqr(g3) + Quad(g1)*(-13.14*mHd2 - 0.48*mHu2 - 0.32*
      tracemd2 - 0.96*traceme2 - 0.48*traceml2 - 0.16*tracemq2 - 1.28*tracemu2
      - 75.96*Sqr(MassB)) + 32.*Quad(g3)*Sqr(MassG) - 32.*traceAdjYdYd*Sqr(g3)*
      Sqr(MassG) + 32.*traceAdjYeYe*Sqr(g3)*Sqr(MassG) + Sqr(g1)*(-6.4*MassB*
      traceAdjTYdYd + 3.2*MassB*traceAdjTYeYe + 12.8*mHd2*traceAdjYdYd + 6.4*
      traceAdjYdYdmq2 - 6.4*mHd2*traceAdjYeYe - 3.2*traceAdjYeYeml2 + 6.4*
      traceTYdAdjTYd + 12.8*traceAdjYdYd*Sqr(MassB) - 6.4*traceAdjYeYe*Sqr(
      MassB) + Sqr(g3)*(-20.266666666666666*MassB*MassG - 10.133333333333333*
      mHd2 - 20.266666666666666*Sqr(MassB) - 20.266666666666666*Sqr(MassG)) +
      Sqr(g2)*(-16.4*MassB*MassWB - 8.2*mHd2 - 16.4*Sqr(MassB) - 16.4*Sqr(
      MassWB))) + Quad(g2)*(-22.5*mHd2 - 135.*Sqr(MassWB)) + Sqr(g2)*(MassWB*(
      -36.*traceAdjTYdYd - 12.*traceAdjTYeYe) + 72.*mHd2*traceAdjYdYd + 36.*
      traceAdjYdYdmq2 + 24.*mHd2*traceAdjYeYe + 12.*traceAdjYeYeml2 + 36.*
      traceTYdAdjTYd + Sqr(g3)*(-16.*MassG*MassWB - 8.*mHd2 - 16.*Sqr(MassG) -
      16.*Sqr(MassWB)) + (72.*traceAdjYdYd + 24.*traceAdjYeYe)*Sqr(MassWB)) -
      54.*mHd2*Sqr(traceAdjYdYd) - 6.*mHd2*Sqr(traceAdjYeYe))*(Yd.adjoint()*Yd)
      )*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_3 = ((threeLoop*(12.*
      traceTYdAdjTYuYuAdjYd - 36.*traceAdjTYdYd*traceTYdAdjYd - 12.*
      traceAdjTYeYe*traceTYdAdjYd - 12.*traceAdjYdYd*traceTYeAdjTYe - 4.*
      traceAdjYeYe*traceTYeAdjTYe - 12.*traceAdjTYdYd*traceTYeAdjYe - 4.*
      traceAdjTYeYe*traceTYeAdjYe - 36.*traceAdjYdYd*traceYdAdjYdmd2 - 12.*
      traceAdjYeYe*traceYdAdjYdmd2 + 72.*traceYdAdjYdYdAdjYdmd2 + 12.*
      traceYdAdjYuYuAdjYdmd2 - 12.*traceAdjYdYd*traceYeAdjYeme2 - 4.*
      traceAdjYeYe*traceYeAdjYeme2 + 24.*traceYeAdjYeYeAdjYeme2 + 12.*
      traceYuAdjYdYdAdjYumu2 + (-6.4*MassB*traceTYdAdjYd - 3.2*traceTYeAdjTYe +
      3.2*MassB*traceTYeAdjYe + 6.4*traceYdAdjYdmd2 - 3.2*traceYeAdjYeme2)*Sqr
      (g1) - 36.*MassWB*traceTYdAdjYd*Sqr(g2) + 12.*traceTYeAdjTYe*Sqr(g2) -
      12.*MassWB*traceTYeAdjYe*Sqr(g2) + 36.*traceYdAdjYdmd2*Sqr(g2) + 12.*
      traceYeAdjYeme2*Sqr(g2) + 16.*MassG*traceTYdAdjYd*Sqr(g3) + 16.*
      traceTYeAdjTYe*Sqr(g3) - 16.*MassG*traceTYeAdjYe*Sqr(g3) - 16.*
      traceYdAdjYdmd2*Sqr(g3) + 16.*traceYeAdjYeme2*Sqr(g3))*(Yd.adjoint()*Yd)
      + threeLoop*(12.*traceAdjTYuYuAdjYdYd - 36.*traceAdjTYdYd*traceAdjYdYd -
      12.*traceAdjTYeYe*traceAdjYdYd + 72.*traceAdjYdYdAdjTYdYd - 12.*
      traceAdjTYdYd*traceAdjYeYe - 4.*traceAdjTYeYe*traceAdjYeYe + 24.*
      traceAdjYeYeAdjTYeYe + 12.*traceAdjYuYuAdjTYdYd + 25.32*MassB*Quad(g1) +
      45.*MassWB*Quad(g2) - 10.666666666666666*MassG*Quad(g3) - 16.*
      traceAdjTYdYd*Sqr(g3) + 16.*traceAdjTYeYe*Sqr(g3) + 16.*MassG*
      traceAdjYdYd*Sqr(g3) - 16.*MassG*traceAdjYeYe*Sqr(g3) + Sqr(g1)*(6.4*
      traceAdjTYdYd - 3.2*traceAdjTYeYe - 6.4*MassB*traceAdjYdYd + 3.2*MassB*
      traceAdjYeYe + (8.2*MassB + 8.2*MassWB)*Sqr(g2) + (10.133333333333333*
      MassB + 10.133333333333333*MassG)*Sqr(g3)) + Sqr(g2)*(36.*traceAdjTYdYd +
      12.*traceAdjTYeYe - 36.*MassWB*traceAdjYdYd - 12.*MassWB*traceAdjYeYe +
      (8.*MassG + 8.*MassWB)*Sqr(g3)))*(Yd.adjoint()*TYd) + threeLoop*(12.*
      traceAdjTYdTYdAdjYuYu + 12.*traceAdjTYuTYuAdjYdYd + 72.*
      traceAdjTYuTYuAdjYuYu + 12.*traceAdjYdYdAdjYuYumq2 + 12.*
      traceAdjYuTYuAdjTYdYd + 72.*traceAdjYuTYuAdjTYuYu + 12.*mHd2*
      traceAdjYuYuAdjYdYd + 24.*mHu2*traceAdjYuYuAdjYdYd + 12.*
      traceAdjYuYuAdjYdYdmq2 + 108.*mHu2*traceAdjYuYuAdjYuYu + 72.*
      traceAdjYuYuAdjYuYumq2 + 5.333333333333333*mHu2*Quad(g3) + 16.*MassG*
      traceAdjTYuYu*Sqr(g3) - 32.*mHu2*traceAdjYuYu*Sqr(g3) + Quad(g1)*(-0.96*
      mHd2 - 26.073333333333334*mHu2 - 150.68*Sqr(MassB)) + 32.*Quad(g3)*Sqr(
      MassG) - 32.*traceAdjYuYu*Sqr(g3)*Sqr(MassG) + Sqr(g1)*(-4.*MassB*
      traceAdjTYuYu + 8.*mHu2*traceAdjYuYu + 4.*traceAdjYuYumq2 + 8.*
      traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(-54.4*MassB*MassG - 27.2*mHu2 - 54.4*
      Sqr(MassB) - 54.4*Sqr(MassG)) + Sqr(g2)*(-23.6*MassB*MassWB - 11.8*mHu2 -
      23.6*Sqr(MassB) - 23.6*Sqr(MassWB))) + Quad(g2)*(-22.5*mHu2 - 135.*Sqr(
      MassWB)) + Sqr(g2)*(-36.*MassWB*traceAdjTYuYu + 72.*mHu2*traceAdjYuYu +
      Sqr(g3)*(-16.*MassG*MassWB - 8.*mHu2 - 16.*Sqr(MassG) - 16.*Sqr(MassWB))
      + 72.*traceAdjYuYu*Sqr(MassWB)) - 54.*mHu2*Sqr(traceAdjYuYu))*(Yu.adjoint
      ()*Yu))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_4 = ((threeLoop*(-36.*
      traceAdjYuYu*traceAdjYuYumq2 + 12.*traceTYdAdjTYuYuAdjYd - 36.*
      traceAdjYuYu*traceTYuAdjTYu - 36.*traceAdjTYuYu*traceTYuAdjYu + 12.*
      traceYdAdjYuYuAdjYdmd2 + 12.*traceYuAdjYdYdAdjYumu2 - 36.*traceAdjYuYu*
      traceYuAdjYumu2 + 72.*traceYuAdjYuYuAdjYumu2 - 0.64*tracemd2*Quad(g1) -
      1.92*traceme2*Quad(g1) - 0.96*traceml2*Quad(g1) - 0.32*tracemq2*Quad(g1)
      - 2.56*tracemu2*Quad(g1) + 4.*traceTYuAdjTYu*Sqr(g1) - 4.*MassB*
      traceTYuAdjYu*Sqr(g1) + 4.*traceYuAdjYumu2*Sqr(g1) + (36.*traceAdjYuYumq2
      + 36.*traceTYuAdjTYu - 36.*MassWB*traceTYuAdjYu + 36.*traceYuAdjYumu2)*
      Sqr(g2) + (-16.*traceAdjYuYumq2 - 16.*traceTYuAdjTYu + 16.*MassG*
      traceTYuAdjYu - 16.*traceYuAdjYumu2)*Sqr(g3))*(Yu.adjoint()*Yu) +
      threeLoop*(12.*traceAdjTYuYuAdjYdYd - 36.*traceAdjTYuYu*traceAdjYuYu +
      12.*traceAdjYuYuAdjTYdYd + 72.*traceAdjYuYuAdjTYuYu + 50.22666666666667*
      MassB*Quad(g1) + 45.*MassWB*Quad(g2) - 10.666666666666666*MassG*Quad(g3)
      - 16.*traceAdjTYuYu*Sqr(g3) + 16.*MassG*traceAdjYuYu*Sqr(g3) + Sqr(g1)*(
      4.*traceAdjTYuYu - 4.*MassB*traceAdjYuYu + (11.8*MassB + 11.8*MassWB)*Sqr
      (g2) + (27.2*MassB + 27.2*MassG)*Sqr(g3)) + Sqr(g2)*(36.*traceAdjTYuYu -
      36.*MassWB*traceAdjYuYu + (8.*MassG + 8.*MassWB)*Sqr(g3)))*(Yu.adjoint()*
      TYu) + threeLoop*(72.*traceAdjYdTYdAdjYdYd + 24.*traceAdjYeTYeAdjYeYe +
      12.*traceAdjYuTYuAdjYdYd - 36.*traceAdjYdYd*traceTYdAdjYd - 12.*
      traceAdjYeYe*traceTYdAdjYd + 12.*traceTYdAdjYuYuAdjYd - 12.*traceAdjYdYd*
      traceTYeAdjYe - 4.*traceAdjYeYe*traceTYeAdjYe + 25.32*MassB*Quad(g1) +
      45.*MassWB*Quad(g2) - 10.666666666666666*MassG*Quad(g3) + 16.*MassG*
      traceAdjYdYd*Sqr(g3) - 16.*MassG*traceAdjYeYe*Sqr(g3) - 16.*traceTYdAdjYd
      *Sqr(g3) + 16.*traceTYeAdjYe*Sqr(g3) + Sqr(g1)*(-6.4*MassB*traceAdjYdYd +
      3.2*MassB*traceAdjYeYe + 6.4*traceTYdAdjYd - 3.2*traceTYeAdjYe + (8.2*
      MassB + 8.2*MassWB)*Sqr(g2) + (10.133333333333333*MassB +
      10.133333333333333*MassG)*Sqr(g3)) + Sqr(g2)*(-36.*MassWB*traceAdjYdYd -
      12.*MassWB*traceAdjYeYe + 36.*traceTYdAdjYd + 12.*traceTYeAdjYe + (8.*
      MassG + 8.*MassWB)*Sqr(g3)))*((TYd).adjoint()*Yd) + threeLoop*(36.*
      traceAdjYdYdAdjYdYd - 12.*traceAdjYdYd*traceAdjYeYe + 12.*
      traceAdjYeYeAdjYeYe + 12.*traceAdjYuYuAdjYdYd - 12.66*Quad(g1) - 22.5*
      Quad(g2) + 5.333333333333333*Quad(g3) + Sqr(g1)*(6.4*traceAdjYdYd - 3.2*
      traceAdjYeYe - 8.2*Sqr(g2) - 10.133333333333333*Sqr(g3)) + Sqr(g2)*(36.*
      traceAdjYdYd + 12.*traceAdjYeYe - 8.*Sqr(g3)) - 16.*traceAdjYdYd*Sqr(g3)
      + 16.*traceAdjYeYe*Sqr(g3) - 18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe)
      )*((TYd).adjoint()*TYd) + threeLoop*(12.*traceAdjYuTYuAdjYdYd +
      50.22666666666667*MassB*Quad(g1) + 45.*MassWB*Quad(g2) -
      10.666666666666666*MassG*Quad(g3) + (8.*MassG + 8.*MassWB)*Sqr(g2)*Sqr(g3
      ) + Sqr(g1)*((11.8*MassB + 11.8*MassWB)*Sqr(g2) + (27.2*MassB + 27.2*
      MassG)*Sqr(g3)))*((TYu).adjoint()*Yu))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_5 = ((threeLoop*(72.*
      traceAdjYuTYuAdjYuYu + 12.*traceTYdAdjYuYuAdjYd - 36.*traceAdjYuYu*
      traceTYuAdjYu + (-4.*MassB*traceAdjYuYu + 4.*traceTYuAdjYu)*Sqr(g1) - 36.
      *MassWB*traceAdjYuYu*Sqr(g2) + 36.*traceTYuAdjYu*Sqr(g2) + 16.*MassG*
      traceAdjYuYu*Sqr(g3) - 16.*traceTYuAdjYu*Sqr(g3))*((TYu).adjoint()*Yu) +
      threeLoop*(12.*traceAdjYuYuAdjYdYd + 36.*traceAdjYuYuAdjYuYu -
      25.113333333333333*Quad(g1) - 22.5*Quad(g2) + 5.333333333333333*Quad(g3)
      + Sqr(g1)*(4.*traceAdjYuYu - 11.8*Sqr(g2) - 27.2*Sqr(g3)) + Sqr(g2)*(36.*
      traceAdjYuYu - 8.*Sqr(g3)) - 16.*traceAdjYuYu*Sqr(g3) - 18.*Sqr(
      traceAdjYuYu))*((TYu).adjoint()*TYu) + threeLoop*(18.*traceAdjYdYdAdjYdYd
      - 6.*traceAdjYdYd*traceAdjYeYe + 6.*traceAdjYeYeAdjYeYe + 6.*
      traceAdjYuYuAdjYdYd - 6.33*Quad(g1) - 11.25*Quad(g2) + 2.6666666666666665
      *Quad(g3) + Sqr(g1)*(3.2*traceAdjYdYd - 1.6*traceAdjYeYe - 4.1*Sqr(g2) -
      5.066666666666666*Sqr(g3)) + Sqr(g2)*(18.*traceAdjYdYd + 6.*traceAdjYeYe
      - 4.*Sqr(g3)) - 8.*traceAdjYdYd*Sqr(g3) + 8.*traceAdjYeYe*Sqr(g3) - 9.*
      Sqr(traceAdjYdYd) - 1.*Sqr(traceAdjYeYe))*(mq2*Yd.adjoint()*Yd) +
      threeLoop*(6.*traceAdjYuYuAdjYdYd + 18.*traceAdjYuYuAdjYuYu -
      12.556666666666667*Quad(g1) - 11.25*Quad(g2) + 2.6666666666666665*Quad(g3
      ) + Sqr(g1)*(2.*traceAdjYuYu - 5.9*Sqr(g2) - 13.6*Sqr(g3)) + Sqr(g2)*(18.
      *traceAdjYuYu - 4.*Sqr(g3)) - 8.*traceAdjYuYu*Sqr(g3) - 9.*Sqr(
      traceAdjYuYu))*(mq2*Yu.adjoint()*Yu) + threeLoop*(36.*traceAdjYdYdAdjYdYd
      - 12.*traceAdjYdYd*traceAdjYeYe + 12.*traceAdjYeYeAdjYeYe + 12.*
      traceAdjYuYuAdjYdYd - 12.66*Quad(g1) - 22.5*Quad(g2) + 5.333333333333333*
      Quad(g3) + Sqr(g1)*(6.4*traceAdjYdYd - 3.2*traceAdjYeYe - 8.2*Sqr(g2) -
      10.133333333333333*Sqr(g3)) + Sqr(g2)*(36.*traceAdjYdYd + 12.*
      traceAdjYeYe - 8.*Sqr(g3)) - 16.*traceAdjYdYd*Sqr(g3) + 16.*traceAdjYeYe*
      Sqr(g3) - 18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe))*(Yd.adjoint()*md2
      *Yd) + threeLoop*(Quad(g1)*(0.4666666666666667*mHd2 + 2.8*Sqr(MassB)) +
      Quad(g3)*(-181.33333333333334*mHd2 - 1088.*Sqr(MassG)) + Sqr(g3)*(-96.*
      MassG*traceAdjTYdYd + 192.*mHd2*traceAdjYdYd + 96.*traceAdjYdYdmq2 + 96.*
      traceTYdAdjTYd - 96.*MassG*traceTYdAdjYd + 192.*traceAdjYdYd*Sqr(MassG))
      + Quad(g2)*(-62.99999999999999*mHd2 - 378.*Sqr(MassWB)) + Sqr(g1)*(9.6*
      MassB*traceAdjTYdYd - 4.8*MassB*traceAdjTYeYe - 19.2*mHd2*traceAdjYdYd -
      9.6*traceAdjYdYdmq2 + 9.6*mHd2*traceAdjYeYe + 4.8*traceAdjYeYeml2 - 9.6*
      traceTYdAdjTYd + 9.6*MassB*traceTYdAdjYd + 4.8*traceTYeAdjTYe - 19.2*
      traceAdjYdYd*Sqr(MassB) + 9.6*traceAdjYeYe*Sqr(MassB) + Sqr(g3)*(
      34.13333333333333*MassB*MassG + 17.066666666666666*mHd2 +
      34.13333333333333*Sqr(MassB) + 34.13333333333333*Sqr(MassG)) + Sqr(g2)*(
      7.200000000000001*MassB*MassWB + 3.6000000000000005*mHd2 +
      7.200000000000001*Sqr(MassB) + 7.200000000000001*Sqr(MassWB))))*(
      Yd.adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_6 = ((threeLoop*((-4.8*MassB*
      traceTYeAdjYe - 9.6*traceYdAdjYdmd2 + 4.8*traceYeAdjYeme2)*Sqr(g1) + 96.*
      traceYdAdjYdmd2*Sqr(g3))*(Yd.adjoint()*Yd*1.2020569031595942) + threeLoop
      *(18.*traceAdjYdYdAdjYdYd - 6.*traceAdjYdYd*traceAdjYeYe + 6.*
      traceAdjYeYeAdjYeYe + 6.*traceAdjYuYuAdjYdYd - 6.33*Quad(g1) - 11.25*Quad
      (g2) + 2.6666666666666665*Quad(g3) + Sqr(g1)*(3.2*traceAdjYdYd - 1.6*
      traceAdjYeYe - 4.1*Sqr(g2) - 5.066666666666666*Sqr(g3)) + Sqr(g2)*(18.*
      traceAdjYdYd + 6.*traceAdjYeYe - 4.*Sqr(g3)) - 8.*traceAdjYdYd*Sqr(g3) +
      8.*traceAdjYeYe*Sqr(g3) - 9.*Sqr(traceAdjYdYd) - 1.*Sqr(traceAdjYeYe))*(
      Yd.adjoint()*Yd*mq2) + threeLoop*(-0.9333333333333333*MassB*Quad(g1) +
      125.99999999999999*MassWB*Quad(g2) + 362.6666666666667*MassG*Quad(g3) + (
      96.*traceAdjTYdYd - 96.*MassG*traceAdjYdYd)*Sqr(g3) + Sqr(g1)*(-9.6*
      traceAdjTYdYd + 4.8*traceAdjTYeYe + 9.6*MassB*traceAdjYdYd - 4.8*MassB*
      traceAdjYeYe + (-3.6000000000000005*MassB - 3.6000000000000005*MassWB)*
      Sqr(g2) + (-17.066666666666666*MassB - 17.066666666666666*MassG)*Sqr(g3))
      )*(Yd.adjoint()*TYd*1.2020569031595942) + threeLoop*(12.*
      traceAdjYuYuAdjYdYd + 36.*traceAdjYuYuAdjYuYu - 25.113333333333333*Quad(
      g1) - 22.5*Quad(g2) + 5.333333333333333*Quad(g3) + Sqr(g1)*(4.*
      traceAdjYuYu - 11.8*Sqr(g2) - 27.2*Sqr(g3)) + Sqr(g2)*(36.*traceAdjYuYu -
      8.*Sqr(g3)) - 16.*traceAdjYuYu*Sqr(g3) - 18.*Sqr(traceAdjYuYu))*(
      Yu.adjoint()*mu2*Yu) + threeLoop*(Quad(g1)*(1.906666666666667*mHu2 +
      11.44*Sqr(MassB)) + Quad(g3)*(-181.33333333333334*mHu2 - 1088.*Sqr(MassG)
      ) + Sqr(g3)*(-96.*MassG*traceAdjTYuYu + 192.*mHu2*traceAdjYuYu + 96.*
      traceAdjYuYumq2 + 96.*traceTYuAdjTYu - 96.*MassG*traceTYuAdjYu + 96.*
      traceYuAdjYumu2 + 192.*traceAdjYuYu*Sqr(MassG)) + Quad(g2)*(
      -62.99999999999999*mHu2 - 378.*Sqr(MassWB)) + Sqr(g1)*(9.6*MassB*
      traceAdjTYuYu - 19.2*mHu2*traceAdjYuYu - 9.6*traceAdjYuYumq2 - 9.6*
      traceTYuAdjTYu + 9.6*MassB*traceTYuAdjYu - 9.6*traceYuAdjYumu2 - 19.2*
      traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(34.13333333333333*MassB*MassG +
      17.066666666666666*mHu2 + 34.13333333333333*Sqr(MassB) +
      34.13333333333333*Sqr(MassG)) + Sqr(g2)*(36.*MassB*MassWB + 18.*mHu2 +
      36.*Sqr(MassB) + 36.*Sqr(MassWB))))*(Yu.adjoint()*Yu*1.2020569031595942)
      + threeLoop*(6.*traceAdjYuYuAdjYdYd + 18.*traceAdjYuYuAdjYuYu -
      12.556666666666667*Quad(g1) - 11.25*Quad(g2) + 2.6666666666666665*Quad(g3
      ) + Sqr(g1)*(2.*traceAdjYuYu - 5.9*Sqr(g2) - 13.6*Sqr(g3)) + Sqr(g2)*(18.
      *traceAdjYuYu - 4.*Sqr(g3)) - 8.*traceAdjYuYu*Sqr(g3) - 9.*Sqr(
      traceAdjYuYu))*(Yu.adjoint()*Yu*mq2) + threeLoop*(-3.813333333333334*
      MassB*Quad(g1) + 125.99999999999999*MassWB*Quad(g2) + 362.6666666666667*
      MassG*Quad(g3) + (96.*traceAdjTYuYu - 96.*MassG*traceAdjYuYu)*Sqr(g3) +
      Sqr(g1)*(-9.6*traceAdjTYuYu + 9.6*MassB*traceAdjYuYu + (-18.*MassB - 18.*
      MassWB)*Sqr(g2) + (-17.066666666666666*MassB - 17.066666666666666*MassG)*
      Sqr(g3)))*(Yu.adjoint()*TYu*1.2020569031595942) + threeLoop*(
      -0.9333333333333333*MassB*Quad(g1) - 3.6000000000000005*MassB*Sqr(g1)*Sqr
      (g2))*((TYd).adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_7 = ((threeLoop*(
      125.99999999999999*MassWB*Quad(g2) + 362.6666666666667*MassG*Quad(g3) + (
      -96.*MassG*traceAdjYdYd + 96.*traceTYdAdjYd)*Sqr(g3) + Sqr(g1)*(9.6*MassB
      *traceAdjYdYd - 4.8*MassB*traceAdjYeYe - 9.6*traceTYdAdjYd + 4.8*
      traceTYeAdjYe - 3.6000000000000005*MassWB*Sqr(g2) + (-17.066666666666666*
      MassB - 17.066666666666666*MassG)*Sqr(g3)))*((TYd).adjoint()*Yd*
      1.2020569031595942) + threeLoop*(0.4666666666666667*Quad(g1) -
      62.99999999999999*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*
      traceAdjYdYd*Sqr(g3) + Sqr(g1)*(-9.6*traceAdjYdYd + 4.8*traceAdjYeYe +
      3.6000000000000005*Sqr(g2) + 17.066666666666666*Sqr(g3)))*((TYd).adjoint(
      )*TYd*1.2020569031595942) + threeLoop*(-3.813333333333334*MassB*Quad(g1)
      + 125.99999999999999*MassWB*Quad(g2) + 362.6666666666667*MassG*Quad(g3) +
      (-96.*MassG*traceAdjYuYu + 96.*traceTYuAdjYu)*Sqr(g3) + Sqr(g1)*(9.6*
      MassB*traceAdjYuYu - 9.6*traceTYuAdjYu + (-18.*MassB - 18.*MassWB)*Sqr(g2
      ) + (-17.066666666666666*MassB - 17.066666666666666*MassG)*Sqr(g3)))*((
      TYu).adjoint()*Yu*1.2020569031595942) + threeLoop*(1.906666666666667*Quad
      (g1) - 62.99999999999999*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*
      traceAdjYuYu*Sqr(g3) + Sqr(g1)*(-9.6*traceAdjYuYu + 18.*Sqr(g2) +
      17.066666666666666*Sqr(g3)))*((TYu).adjoint()*TYu*1.2020569031595942) +
      threeLoop*(0.23333333333333334*Quad(g1) - 31.499999999999996*Quad(g2) -
      90.66666666666667*Quad(g3) + 48.*traceAdjYdYd*Sqr(g3) + Sqr(g1)*(-4.8*
      traceAdjYdYd + 2.4*traceAdjYeYe + 1.8000000000000003*Sqr(g2) +
      8.533333333333333*Sqr(g3)))*(mq2*Yd.adjoint()*Yd*1.2020569031595942) +
      threeLoop*(0.9533333333333335*Quad(g1) - 31.499999999999996*Quad(g2) -
      90.66666666666667*Quad(g3) + 48.*traceAdjYuYu*Sqr(g3) + Sqr(g1)*(-4.8*
      traceAdjYuYu + 9.*Sqr(g2) + 8.533333333333333*Sqr(g3)))*(mq2*Yu.adjoint()
      *Yu*1.2020569031595942) + threeLoop*(0.4666666666666667*Quad(g1) -
      62.99999999999999*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*
      traceAdjYdYd*Sqr(g3) + Sqr(g1)*(-9.6*traceAdjYdYd + 4.8*traceAdjYeYe +
      3.6000000000000005*Sqr(g2) + 17.066666666666666*Sqr(g3)))*(Yd.adjoint()*
      md2*Yd*1.2020569031595942) + threeLoop*(0.23333333333333334*Quad(g1) -
      31.499999999999996*Quad(g2) - 90.66666666666667*Quad(g3) + 48.*
      traceAdjYdYd*Sqr(g3) + Sqr(g1)*(-4.8*traceAdjYdYd + 2.4*traceAdjYeYe +
      1.8000000000000003*Sqr(g2) + 8.533333333333333*Sqr(g3)))*(Yd.adjoint()*Yd
      *mq2*1.2020569031595942) + threeLoop*(36.*mHd2*traceAdjYdYd + 12.*
      traceAdjYdYdmq2 + 12.*mHd2*traceAdjYeYe + 4.*traceAdjYeYeml2 + 12.*
      traceTYdAdjTYd + 4.*traceTYeAdjTYe + 12.*traceYdAdjYdmd2 + 4.*
      traceYeAdjYeme2 - 12.*mHd2*Sqr(g2) + Sqr(g1)*(1.8666666666666667*mHd2 +
      1.8666666666666667*Sqr(MassB)) + Sqr(g3)*(85.33333333333333*mHd2 +
      85.33333333333333*Sqr(MassG)) - 12.*Sqr(g2)*Sqr(MassWB))*(Yd.adjoint()*Yd
      *Yd.adjoint()*Yd) + threeLoop*(12.*traceAdjTYdYd + 4.*traceAdjTYeYe -
      0.9333333333333333*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2) - 42.666666666666664
      *MassG*Sqr(g3))*(Yd.adjoint()*Yd*Yd.adjoint()*TYd) + threeLoop*(12.*
      traceTYdAdjYd + 4.*traceTYeAdjYe - 0.9333333333333333*MassB*Sqr(g1) + 6.*
      MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yd.adjoint()*Yd*(TYd)
      .adjoint()*Yd) + threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe +
      0.9333333333333333*Sqr(g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yd.adjoint()*Yd*(TYd).adjoint()*TYd) + threeLoop*(-0.9333333333333333*
      MassB*Sqr(g1) + 6.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(
      Yd.adjoint()*TYd*Yd.adjoint()*Yd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_8 = ((threeLoop*(12.*
      traceAdjTYdYd + 4.*traceAdjTYeYe)*(Yd.adjoint()*TYd*Yd.adjoint()*Yd) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 0.9333333333333333*Sqr(g1
      ) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yd.adjoint()*TYd*(TYd)
      .adjoint()*Yd) + threeLoop*(1.906666666666667*Quad(g1) -
      62.99999999999999*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*
      traceAdjYuYu*Sqr(g3) + Sqr(g1)*(-9.6*traceAdjYuYu + 18.*Sqr(g2) +
      17.066666666666666*Sqr(g3)))*(Yu.adjoint()*mu2*Yu*1.2020569031595942) +
      threeLoop*(0.9533333333333335*Quad(g1) - 31.499999999999996*Quad(g2) -
      90.66666666666667*Quad(g3) + 48.*traceAdjYuYu*Sqr(g3) + Sqr(g1)*(-4.8*
      traceAdjYuYu + 9.*Sqr(g2) + 8.533333333333333*Sqr(g3)))*(Yu.adjoint()*Yu*
      mq2*1.2020569031595942) + threeLoop*(36.*mHu2*traceAdjYuYu + 12.*
      traceAdjYuYumq2 + 12.*traceTYuAdjTYu + 12.*traceYuAdjYumu2 - 12.*mHu2*Sqr
      (g2) + Sqr(g1)*(14.666666666666666*mHu2 + 14.666666666666666*Sqr(MassB))
      + Sqr(g3)*(85.33333333333333*mHu2 + 85.33333333333333*Sqr(MassG)) - 12.*
      Sqr(g2)*Sqr(MassWB))*(Yu.adjoint()*Yu*Yu.adjoint()*Yu) + threeLoop*(12.*
      traceAdjTYuYu - 7.333333333333333*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yu.adjoint()*Yu*Yu.adjoint()*TYu) +
      threeLoop*(12.*traceTYuAdjYu - 7.333333333333333*MassB*Sqr(g1) + 6.*
      MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yu.adjoint()*Yu*(TYu)
      .adjoint()*Yu) + threeLoop*(12.*traceAdjYuYu + 7.333333333333333*Sqr(g1)
      - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yu.adjoint()*Yu*(TYu).adjoint
      ()*TYu) + threeLoop*(12.*traceAdjTYuYu - 7.333333333333333*MassB*Sqr(g1)
      + 6.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yu.adjoint()*TYu
      *Yu.adjoint()*Yu) + threeLoop*(12.*traceAdjYuYu + 7.333333333333333*Sqr(
      g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yu.adjoint()*TYu*(TYu)
      .adjoint()*Yu) + threeLoop*(12.*traceTYdAdjYd + 4.*traceTYeAdjYe -
      0.9333333333333333*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2) - 42.666666666666664
      *MassG*Sqr(g3))*((TYd).adjoint()*Yd*Yd.adjoint()*Yd) + threeLoop*(12.*
      traceAdjYdYd + 4.*traceAdjYeYe + 0.9333333333333333*Sqr(g1) - 6.*Sqr(g2)
      + 42.666666666666664*Sqr(g3))*((TYd).adjoint()*Yd*Yd.adjoint()*TYd) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 0.9333333333333333*Sqr(g1
      ) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*((TYd).adjoint()*TYd*
      Yd.adjoint()*Yd) + threeLoop*(12.*traceTYuAdjYu - 7.333333333333333*MassB
      *Sqr(g1) + 6.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*((TYu)
      .adjoint()*Yu*Yu.adjoint()*Yu) + threeLoop*(12.*traceAdjYuYu +
      7.333333333333333*Sqr(g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*((
      TYu).adjoint()*Yu*Yu.adjoint()*TYu) + threeLoop*(12.*traceAdjYuYu +
      7.333333333333333*Sqr(g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*((
      TYu).adjoint()*TYu*Yu.adjoint()*Yu) + threeLoop*(6.*traceAdjYdYd + 2.*
      traceAdjYeYe + 0.4666666666666667*Sqr(g1) - 3.*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd) +
      threeLoop*(6.*traceAdjYuYu + 3.6666666666666665*Sqr(g1) - 3.*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 0.9333333333333333*Sqr(g1
      ) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yd.adjoint()*md2*Yd*
      Yd.adjoint()*Yd) + threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe +
      0.9333333333333333*Sqr(g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd) + threeLoop*(0.9333333333333333*Sqr(
      g1) - 6.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yd.adjoint()*Yd*
      Yd.adjoint()*md2*Yd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_9 = ((threeLoop*(12.*
      traceAdjYdYd + 4.*traceAdjYeYe)*(Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd) +
      threeLoop*(Sqr(g1)*(-4.8*mHd2 - 4.8*Sqr(MassB)) + Sqr(g2)*(72.*mHd2 + 72.
      *Sqr(MassWB)))*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      threeLoop*(6.*traceAdjYdYd + 2.*traceAdjYeYe + 0.4666666666666667*Sqr(g1)
      - 3.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(Yd.adjoint()*Yd*Yd.adjoint()
      *Yd*mq2) + threeLoop*(2.4*MassB*Sqr(g1) - 36.*MassWB*Sqr(g2))*(Yd.adjoint
      ()*Yd*Yd.adjoint()*TYd*1.2020569031595942) + threeLoop*(2.4*MassB*Sqr(g1)
      - 36.*MassWB*Sqr(g2))*(Yd.adjoint()*Yd*(TYd).adjoint()*Yd*
      1.2020569031595942) + threeLoop*(-2.4*Sqr(g1) + 36.*Sqr(g2))*(Yd.adjoint(
      )*Yd*(TYd).adjoint()*TYd*1.2020569031595942) + threeLoop*(2.4*MassB*Sqr(
      g1) - 36.*MassWB*Sqr(g2))*(Yd.adjoint()*TYd*Yd.adjoint()*Yd*
      1.2020569031595942) + threeLoop*(-2.4*Sqr(g1) + 36.*Sqr(g2))*(Yd.adjoint(
      )*TYd*(TYd).adjoint()*Yd*1.2020569031595942) + threeLoop*(12.*
      traceAdjYuYu + 7.333333333333333*Sqr(g1) - 6.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu) +
      threeLoop*(12.*traceAdjYuYu + 7.333333333333333*Sqr(g1) - 6.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu) +
      threeLoop*(12.*traceAdjYuYu + 7.333333333333333*Sqr(g1) - 6.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu) +
      threeLoop*(Sqr(g1)*(-24.*mHu2 - 24.*Sqr(MassB)) + Sqr(g2)*(72.*mHu2 + 72.
      *Sqr(MassWB)))*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) +
      threeLoop*(6.*traceAdjYuYu + 3.6666666666666665*Sqr(g1) - 3.*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2) +
      threeLoop*(12.*MassB*Sqr(g1) - 36.*MassWB*Sqr(g2))*(Yu.adjoint()*Yu*
      Yu.adjoint()*TYu*1.2020569031595942) + threeLoop*(12.*MassB*Sqr(g1) - 36.
      *MassWB*Sqr(g2))*(Yu.adjoint()*Yu*(TYu).adjoint()*Yu*1.2020569031595942)
      + threeLoop*(-12.*Sqr(g1) + 36.*Sqr(g2))*(Yu.adjoint()*Yu*(TYu).adjoint()
      *TYu*1.2020569031595942) + threeLoop*(12.*MassB*Sqr(g1) - 36.*MassWB*Sqr(
      g2))*(Yu.adjoint()*TYu*Yu.adjoint()*Yu*1.2020569031595942) + threeLoop*(
      -12.*Sqr(g1) + 36.*Sqr(g2))*(Yu.adjoint()*TYu*(TYu).adjoint()*Yu*
      1.2020569031595942) + threeLoop*(2.4*MassB*Sqr(g1) - 36.*MassWB*Sqr(g2))*
      ((TYd).adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + threeLoop*(-2.4
      *Sqr(g1) + 36.*Sqr(g2))*((TYd).adjoint()*Yd*Yd.adjoint()*TYd*
      1.2020569031595942) + threeLoop*(-2.4*Sqr(g1) + 36.*Sqr(g2))*((TYd)
      .adjoint()*TYd*Yd.adjoint()*Yd*1.2020569031595942) + threeLoop*(12.*MassB
      *Sqr(g1) - 36.*MassWB*Sqr(g2))*((TYu).adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + threeLoop*(-12.*Sqr(g1) + 36.*Sqr(g2))*((TYu)
      .adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) + threeLoop*(-12.*Sqr(
      g1) + 36.*Sqr(g2))*((TYu).adjoint()*TYu*Yu.adjoint()*Yu*
      1.2020569031595942) + threeLoop*(-1.2*Sqr(g1) + 18.*Sqr(g2))*(mq2*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + threeLoop*(-6.*Sqr(
      g1) + 18.*Sqr(g2))*(mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + threeLoop*(-2.4*Sqr(g1) + 36.*Sqr(g2))*(Yd.adjoint(
      )*md2*Yd*Yd.adjoint()*Yd*1.2020569031595942) + threeLoop*(-2.4*Sqr(g1) +
      36.*Sqr(g2))*(Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*1.2020569031595942) +
      threeLoop*(-2.4*Sqr(g1) + 36.*Sqr(g2))*(Yd.adjoint()*Yd*Yd.adjoint()*md2*
      Yd*1.2020569031595942) + threeLoop*(-1.2*Sqr(g1) + 18.*Sqr(g2))*(
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*1.2020569031595942) + (16.*mHd2 + 8.*
      mHu2)*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 8.*
      threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*(TYd).adjoint()*TYd) + 8.*
      threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*TYu*(TYd).adjoint()*Yd) + 8.*
      threeLoop*(Yd.adjoint()*Yd*(TYu).adjoint()*Yu*Yd.adjoint()*TYd) + 8.*
      threeLoop*(Yd.adjoint()*Yd*(TYu).adjoint()*TYu*Yd.adjoint()*Yd) + 8.*
      threeLoop*(Yd.adjoint()*TYd*Yu.adjoint()*Yu*(TYd).adjoint()*Yd) + 8.*
      threeLoop*(Yd.adjoint()*TYd*(TYu).adjoint()*Yu*Yd.adjoint()*Yd) +
      threeLoop*(-12.*Sqr(g1) + 36.*Sqr(g2))*(Yu.adjoint()*mu2*Yu*Yu.adjoint()*
      Yu*1.2020569031595942) + threeLoop*(-12.*Sqr(g1) + 36.*Sqr(g2))*(
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*1.2020569031595942) + (8.*mHd2 + 16.*
      mHu2)*threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*Yd*(TYu).adjoint()*TYu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*TYd*(TYu).adjoint()*Yu) +
      threeLoop*(-12.*Sqr(g1) + 36.*Sqr(g2))*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*
      Yu*1.2020569031595942) + threeLoop*(-6.*Sqr(g1) + 18.*Sqr(g2))*(
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*1.2020569031595942) + 8.*threeLoop*(
      Yu.adjoint()*Yu*(TYd).adjoint()*Yd*Yu.adjoint()*TYu) + 8.*threeLoop*(
      Yu.adjoint()*Yu*(TYd).adjoint()*TYd*Yu.adjoint()*Yu) + 8.*threeLoop*(
      Yu.adjoint()*TYu*Yd.adjoint()*Yd*(TYu).adjoint()*Yu) + 8.*threeLoop*(
      Yu.adjoint()*TYu*(TYd).adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*((TYd
      ).adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_10 = ((8.*threeLoop*((TYd)
      .adjoint()*Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd) + 8.*threeLoop*((TYd)
      .adjoint()*TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 8.*threeLoop*((TYu)
      .adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu) + 8.*threeLoop*((TYu)
      .adjoint()*Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu) + 8.*threeLoop*((TYu)
      .adjoint()*TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 4.*threeLoop*(mq2*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 4.*threeLoop*(mq2*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(
      Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 8.*threeLoop*(
      Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 36.*mHd2*threeLoop
      *(Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*(TYd).adjoint()*TYd*
      1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*TYd*(
      TYd).adjoint()*Yd*1.2020569031595942) + 8.*threeLoop*(Yd.adjoint()*Yd*
      Yu.adjoint()*mu2*Yu*Yd.adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*
      Yu.adjoint()*Yu*mq2*Yd.adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*md2*Yd) + 4.*threeLoop*(Yd.adjoint()*Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*mq2) + 12.*threeLoop*(Yd.adjoint()*Yd*(
      TYd).adjoint()*Yd*Yd.adjoint()*TYd*1.2020569031595942) + 12.*threeLoop*(
      Yd.adjoint()*Yd*(TYd).adjoint()*TYd*Yd.adjoint()*Yd*1.2020569031595942) +
      12.*threeLoop*(Yd.adjoint()*TYd*Yd.adjoint()*Yd*(TYd).adjoint()*Yd*
      1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*TYd*(TYd).adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 8.*threeLoop*(Yu.adjoint()*mu2*Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.adjoint()*Yu*mq2*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.adjoint()*Yu*
      Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.adjoint()*Yu*
      Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.adjoint()*Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*mu2*Yu) + 4.*threeLoop*(Yu.adjoint()*Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*mq2) + 36.*mHu2*threeLoop*(Yu.adjoint()*
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYu).adjoint()*TYu*1.2020569031595942) +
      12.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*TYu*(TYu).adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*(TYu).adjoint()*Yu*
      Yu.adjoint()*TYu*1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*(
      TYu).adjoint()*TYu*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(
      Yu.adjoint()*TYu*Yu.adjoint()*Yu*(TYu).adjoint()*Yu*1.2020569031595942) +
      12.*threeLoop*(Yu.adjoint()*TYu*(TYu).adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*((TYd).adjoint()*Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*TYd*1.2020569031595942) + 12.*threeLoop*((TYd).adjoint()*Yd*
      Yd.adjoint()*TYd*Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*((
      TYd).adjoint()*TYd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      12.*threeLoop*((TYu).adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*
      1.2020569031595942) + 12.*threeLoop*((TYu).adjoint()*Yu*Yu.adjoint()*TYu*
      Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*((TYu).adjoint()*TYu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 6.*threeLoop*(mq2*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 6.*
      threeLoop*(mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*mq2*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(
      Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*
      1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*md2*Yd*1.2020569031595942) + 6.*threeLoop*(Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*1.2020569031595942) + 12.*threeLoop*(
      Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) +
      12.*threeLoop*(Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*
      Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*1.2020569031595942) +
      6.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*
      1.2020569031595942))*UNITMATRIX(3)).real();

   beta_mq2 = beta_mq2_1 + beta_mq2_2 + beta_mq2_3 + beta_mq2_4 +
      beta_mq2_5 + beta_mq2_6 + beta_mq2_7 + beta_mq2_8 + beta_mq2_9 +
      beta_mq2_10;


   return beta_mq2;
}

} // namespace flexiblesusy
