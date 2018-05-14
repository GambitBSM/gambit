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

// File generated at Thu 10 May 2018 15:09:00

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
 * Calculates the 1-loop beta function of md2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_md2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_md2;

   beta_md2 = (oneOver16PiSqr*(4*mHd2*(Yd*Yd.adjoint()) + 4*(TYd*(TYd)
      .adjoint()) + 2*(md2*Yd*Yd.adjoint()) + 4*(Yd*mq2*Yd.adjoint()) + 2*(Yd*
      Yd.adjoint()*md2) + 0.13333333333333333*(3.872983346207417*g1*Tr11 - 4*
      AbsSqr(MassB)*Sqr(g1) - 80*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_md2;
}

/**
 * Calculates the 2-loop beta function of md2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_md2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceconjTYdTpTYd = TRACE_STRUCT.traceconjTYdTpTYd;
   const double traceconjTYeTpTYe = TRACE_STRUCT.traceconjTYeTpTYe;
   const double tracemd2YdAdjYd = TRACE_STRUCT.tracemd2YdAdjYd;
   const double traceme2YeAdjYe = TRACE_STRUCT.traceme2YeAdjYe;
   const double traceml2AdjYeYe = TRACE_STRUCT.traceml2AdjYeYe;
   const double tracemq2AdjYdYd = TRACE_STRUCT.tracemq2AdjYdYd;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceconjTYdTpYd = TRACE_STRUCT.traceconjTYdTpYd;
   const double traceconjTYeTpYe = TRACE_STRUCT.traceconjTYeTpYe;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr23 = TRACE_STRUCT.Tr23;


   Eigen::Matrix<double,3,3> beta_md2;

   beta_md2 = (twoLoop*(0.8*(-15*traceconjTYdTpTYd - 5*traceconjTYeTpTYe
      - 15*tracemd2YdAdjYd - 5*traceme2YeAdjYe - 5*traceml2AdjYeYe - 15*
      tracemq2AdjYdYd - 30*mHd2*traceYdAdjYd - 10*mHd2*traceYeAdjYe + mHd2*Sqr(
      g1) + 2*AbsSqr(MassB)*Sqr(g1) + 15*mHd2*Sqr(g2) + 30*AbsSqr(MassWB)*Sqr(
      g2))*(Yd*Yd.adjoint()) - 0.8*(MassB*Sqr(g1) + 5*(3*traceAdjYdTYd +
      traceAdjYeTYe + 3*MassWB*Sqr(g2)))*(Yd*(TYd).adjoint()) - 0.8*(Conj(MassB
      )*Sqr(g1) + 5*(3*traceconjTYdTpYd + traceconjTYeTpYe + 3*Conj(MassWB)*Sqr
      (g2)))*(TYd*Yd.adjoint()) + 0.8*(-15*traceYdAdjYd - 5*traceYeAdjYe + Sqr(
      g1) + 15*Sqr(g2))*(TYd*(TYd).adjoint()) + (-2*(3*traceYdAdjYd +
      traceYeAdjYe) + 0.4*Sqr(g1) + 6*Sqr(g2))*(md2*Yd*Yd.adjoint()) + 0.8*(-15
      *traceYdAdjYd - 5*traceYeAdjYe + Sqr(g1) + 15*Sqr(g2))*(Yd*mq2*Yd.adjoint
      ()) + (-2*(3*traceYdAdjYd + traceYeAdjYe) + 0.4*Sqr(g1) + 6*Sqr(g2))*(Yd*
      Yd.adjoint()*md2) - 8*mHd2*(Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 4*(Yd*
      Yd.adjoint()*TYd*(TYd).adjoint()) - 4*(mHd2 + mHu2)*(Yd*Yu.adjoint()*Yu*
      Yd.adjoint()) - 4*(Yd*Yu.adjoint()*TYu*(TYd).adjoint()) - 4*(Yd*(TYd)
      .adjoint()*TYd*Yd.adjoint()) - 4*(Yd*(TYu).adjoint()*TYu*Yd.adjoint()) -
      4*(TYd*Yd.adjoint()*Yd*(TYd).adjoint()) - 4*(TYd*Yu.adjoint()*Yu*(TYd)
      .adjoint()) - 4*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()) - 4*(TYd*(TYu)
      .adjoint()*Yu*Yd.adjoint()) - 2*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 2
      *(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()) - 4*(Yd*mq2*Yd.adjoint()*Yd*
      Yd.adjoint()) - 4*(Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()) - 4*(Yd*
      Yd.adjoint()*md2*Yd*Yd.adjoint()) - 4*(Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint(
      )) - 2*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2) - 4*(Yd*Yu.adjoint()*mu2*Yu*
      Yd.adjoint()) - 4*(Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()) - 2*(Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*md2) + 0.035555555555555556*(Conj(MassB)*(
      303*MassB*Quad(g1) + 40*(2*MassB + MassG)*Sqr(g1)*Sqr(g3)) + 5*(3*g1*(g1*
      Tr2U111 + 3.872983346207417*Tr31) + 60*Tr23*Quad(g3) + 8*Conj(MassG)*Sqr(
      g3)*((MassB + 2*MassG)*Sqr(g1) - 30*MassG*Sqr(g3))))*UNITMATRIX(3))).real
      ();


   return beta_md2;
}

/**
 * Calculates the 3-loop beta function of md2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMGUT_soft_parameters::calc_beta_md2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdYdAdjTYdYd = TRACE_STRUCT.traceAdjYdYdAdjTYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjTYeYe = TRACE_STRUCT.traceAdjYeYeAdjTYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceAdjYdTYdAdjTYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjTYdYd;
   const double traceAdjYeTYeAdjTYeYe =
      TRACE_STRUCT.traceAdjYeTYeAdjTYeYe;
   const double traceAdjYuTYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjTYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjTYdTYdAdjYdYd;
   const double traceAdjTYdTYdAdjYuYu =
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYeTYeAdjYeYe =
      TRACE_STRUCT.traceAdjTYeTYeAdjYeYe;
   const double traceAdjTYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceTYdAdjTYuYuAdjYd =
      TRACE_STRUCT.traceTYdAdjTYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdmd2;
   const double traceYdAdjYuYuAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2;
   const double traceYeAdjYeYeAdjYeme2 =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeme2;
   const double traceYuAdjYdYdAdjYumu2 =
      TRACE_STRUCT.traceYuAdjYdYdAdjYumu2;
   const double traceAdjYdYdAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdmq2;
   const double traceAdjYdYdAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYuYumq2;
   const double traceAdjYeYeAdjYeYeml2 =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeml2;
   const double traceAdjYuYuAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2;


   Eigen::Matrix<double,3,3> beta_md2;

   const Eigen::Matrix<double,3,3> beta_md2_1 = ((threeLoop*(Power6(g1)*(
      -2.1546666666666665*mHd2 - 2.1546666666666665*mHu2 - 1.4364444444444444*
      tracemd2 - 4.309333333333333*traceme2 - 2.1546666666666665*traceml2 -
      0.7182222222222222*tracemq2 - 5.745777777777778*tracemu2 +
      110.40850857704534*Sqr(MassB)) + Quad(g3)*Sqr(g1)*(-88.89405640931534*
      MassB*MassG - 1.4222222222222223*tracemd2 - 2.8444444444444446*tracemq2 -
      1.4222222222222223*tracemu2 - 32.713694871324336*Sqr(MassB) -
      124.80775128063961*Sqr(MassG)) + Quad(g3)*(106.66666666666667*MassG*
      traceAdjTYdYd + 106.66666666666667*MassG*traceAdjTYuYu - 64.*mHd2*
      traceAdjYdYd - 64.*traceAdjYdYdmq2 - 64.*mHu2*traceAdjYuYu - 64.*
      traceAdjYuYumq2 - 64.*traceTYdAdjTYd + 106.66666666666667*MassG*
      traceTYdAdjYd - 64.*traceTYuAdjTYu + 106.66666666666667*MassG*
      traceTYuAdjYu - 64.*traceYdAdjYdmd2 - 64.*traceYuAdjYumu2 - 320.*
      traceAdjYdYd*Sqr(MassG) - 320.*traceAdjYuYu*Sqr(MassG) + Sqr(g3)*(
      35.55555555555556*tracemd2 + 71.11111111111111*tracemq2 +
      35.55555555555556*tracemu2 + 11510.908127376795*Sqr(MassG)) + Sqr(g2)*(
      -212.38477621992627*MassG*MassWB - 318.57716432988946*Sqr(MassG) -
      58.192388109963126*Sqr(MassWB))) + Quad(g1)*(3.7333333333333334*MassB*
      traceAdjTYdYd + 4.8*MassB*traceAdjTYeYe + 6.933333333333334*MassB*
      traceAdjTYuYu - 2.24*mHd2*traceAdjYdYd - 2.24*traceAdjYdYdmq2 - 2.88*mHd2
      *traceAdjYeYe - 2.88*traceAdjYeYeml2 - 4.16*mHu2*traceAdjYuYu - 4.16*
      traceAdjYuYumq2 - 2.24*traceTYdAdjTYd + 3.7333333333333334*MassB*
      traceTYdAdjYd - 2.88*traceTYeAdjTYe + 4.8*MassB*traceTYeAdjYe - 4.16*
      traceTYuAdjTYu + 6.933333333333334*MassB*traceTYuAdjYu - 2.24*
      traceYdAdjYdmd2 - 2.88*traceYeAdjYeme2 - 4.16*traceYuAdjYumu2 - 11.2*
      traceAdjYdYd*Sqr(MassB) - 14.400000000000002*traceAdjYeYe*Sqr(MassB) -
      20.8*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(-41.8154003415039*MassB*MassG -
      0.8533333333333334*mHd2 - 0.8533333333333334*mHu2 - 0.5688888888888889*
      tracemd2 - 1.7066666666666668*traceme2 - 0.8533333333333334*traceml2 -
      0.28444444444444444*tracemq2 - 2.2755555555555556*tracemu2 -
      62.723100512255854*Sqr(MassB) - 16.214366837418616*Sqr(MassG)) + Sqr(g2)*
      (-6.37154328659779*MassB*MassWB - 9.557314929896684*Sqr(MassB) -
      1.7457716432988948*Sqr(MassWB)))) + threeLoop*(144.*traceAdjTYdTYdAdjYdYd
      + 24.*traceAdjTYdTYdAdjYuYu + 48.*traceAdjTYeTYeAdjYeYe + 24.*
      traceAdjTYuTYuAdjYdYd + 144.*traceAdjYdTYdAdjTYdYd + 10.666666666666666*
      mHd2*Quad(g3) + 32.*MassG*traceAdjTYdYd*Sqr(g3) - 32.*MassG*traceAdjTYeYe
      *Sqr(g3) + Quad(g1)*(-22.946666666666665*mHd2 - 0.48*mHu2 - 134.8*Sqr(
      MassB)) + 64.*Quad(g3)*Sqr(MassG) + Sqr(g2)*(-54.*MassWB*traceAdjTYdYd -
      18.*MassWB*traceAdjTYeYe + Sqr(g3)*(-352.*MassG*MassWB - 176.*mHd2 - 352.
      *Sqr(MassG) - 352.*Sqr(MassWB))) + Sqr(g1)*(-14.*MassB*traceAdjTYdYd + 6.
      *MassB*traceAdjTYeYe + Sqr(g3)*(-19.2*MassB*MassG - 9.6*mHd2 - 19.2*Sqr(
      MassB) - 19.2*Sqr(MassG)) + Sqr(g2)*(-34.4*MassB*MassWB - 17.2*mHd2 -
      34.4*Sqr(MassB) - 34.4*Sqr(MassWB))) + Quad(g2)*(-99.*mHd2 - 12.*mHu2 -
      474.*Sqr(MassWB)))*(Yd*Yd.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_2 = ((threeLoop*(216.*mHd2*
      traceAdjYdYdAdjYdYd + 144.*traceAdjYdYdAdjYdYdmq2 + 24.*
      traceAdjYdYdAdjYuYumq2 - 72.*traceAdjYdYd*traceAdjYdYdmq2 + 48.*
      traceAdjYeTYeAdjTYeYe - 72.*mHd2*traceAdjYdYd*traceAdjYeYe - 24.*
      traceAdjYdYdmq2*traceAdjYeYe + 72.*mHd2*traceAdjYeYeAdjYeYe + 48.*
      traceAdjYeYeAdjYeYeml2 - 24.*traceAdjYdYd*traceAdjYeYeml2 - 8.*
      traceAdjYeYe*traceAdjYeYeml2 + 24.*traceAdjYuTYuAdjTYdYd + 48.*mHd2*
      traceAdjYuYuAdjYdYd + 24.*mHu2*traceAdjYuYuAdjYdYd + 24.*
      traceAdjYuYuAdjYdYdmq2 - 72.*traceAdjYdYd*traceTYdAdjTYd - 24.*
      traceAdjYeYe*traceTYdAdjTYd + 24.*traceTYdAdjTYuYuAdjYd - 72.*
      traceAdjTYdYd*traceTYdAdjYd - 24.*traceAdjTYeYe*traceTYdAdjYd - 24.*
      traceAdjYdYd*traceTYeAdjTYe - 8.*traceAdjYeYe*traceTYeAdjTYe - 24.*
      traceAdjTYdYd*traceTYeAdjYe - 8.*traceAdjTYeYe*traceTYeAdjYe - 72.*
      traceAdjYdYd*traceYdAdjYdmd2 - 24.*traceAdjYeYe*traceYdAdjYdmd2 + 144.*
      traceYdAdjYdYdAdjYdmd2 + 24.*traceYdAdjYuYuAdjYdmd2 - 24.*traceAdjYdYd*
      traceYeAdjYeme2 - 8.*traceAdjYeYe*traceYeAdjYeme2 + 48.*
      traceYeAdjYeYeAdjYeme2 + 24.*traceYuAdjYdYdAdjYumu2 + (-0.32*tracemd2 -
      0.96*traceme2 - 0.48*traceml2 - 0.16*tracemq2 - 1.28*tracemu2)*Quad(g1) -
      12.*traceml2*Quad(g2) - 36.*tracemq2*Quad(g2) + 108.*mHd2*traceAdjYdYd*
      Sqr(g2) + 54.*traceAdjYdYdmq2*Sqr(g2) + 36.*mHd2*traceAdjYeYe*Sqr(g2) +
      18.*traceAdjYeYeml2*Sqr(g2) + 54.*traceTYdAdjTYd*Sqr(g2) - 54.*MassWB*
      traceTYdAdjYd*Sqr(g2) + 18.*traceTYeAdjTYe*Sqr(g2) - 18.*MassWB*
      traceTYeAdjYe*Sqr(g2) + 54.*traceYdAdjYdmd2*Sqr(g2) + 18.*traceYeAdjYeme2
      *Sqr(g2) + Sqr(g1)*(28.*mHd2*traceAdjYdYd + 14.*traceAdjYdYdmq2 - 12.*
      mHd2*traceAdjYeYe - 6.*traceAdjYeYeml2 + 14.*traceTYdAdjTYd - 6.*
      traceTYeAdjTYe + MassB*(-14.*traceTYdAdjYd + 6.*traceTYeAdjYe) + 14.*
      traceYdAdjYdmd2 - 6.*traceYeAdjYeme2 + (28.*traceAdjYdYd - 12.*
      traceAdjYeYe)*Sqr(MassB)) + Sqr(g3)*(-64.*mHd2*traceAdjYdYd - 32.*
      traceAdjYdYdmq2 + 64.*mHd2*traceAdjYeYe + 32.*traceAdjYeYeml2 - 32.*
      traceTYdAdjTYd + 32.*MassG*traceTYdAdjYd + 32.*traceTYeAdjTYe - 32.*MassG
      *traceTYeAdjYe - 32.*traceYdAdjYdmd2 + 32.*traceYeAdjYeme2 - 64.*
      traceAdjYdYd*Sqr(MassG) + 64.*traceAdjYeYe*Sqr(MassG)) + 108.*
      traceAdjYdYd*Sqr(g2)*Sqr(MassWB) + 36.*traceAdjYeYe*Sqr(g2)*Sqr(MassWB) -
      108.*mHd2*Sqr(traceAdjYdYd) - 12.*mHd2*Sqr(traceAdjYeYe))*(Yd*Yd.adjoint
      ()) + threeLoop*(144.*traceAdjYdTYdAdjYdYd + 48.*traceAdjYeTYeAdjYeYe +
      24.*traceAdjYuTYuAdjYdYd - 72.*traceAdjYdYd*traceTYdAdjYd - 24.*
      traceAdjYeYe*traceTYdAdjYd + 44.93333333333333*MassB*Quad(g1) + 174.*
      MassWB*Quad(g2) - 21.333333333333332*MassG*Quad(g3) + 32.*MassG*
      traceAdjYdYd*Sqr(g3) - 32.*MassG*traceAdjYeYe*Sqr(g3) - 32.*traceTYdAdjYd
      *Sqr(g3) + Sqr(g1)*(-14.*MassB*traceAdjYdYd + 6.*MassB*traceAdjYeYe + 14.
      *traceTYdAdjYd + (17.2*MassB + 17.2*MassWB)*Sqr(g2) + (9.6*MassB + 9.6*
      MassG)*Sqr(g3)) + Sqr(g2)*(-54.*MassWB*traceAdjYdYd - 18.*MassWB*
      traceAdjYeYe + 54.*traceTYdAdjYd + (176.*MassG + 176.*MassWB)*Sqr(g3)))*(
      Yd*(TYd).adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_3 = ((threeLoop*(24.*
      traceTYdAdjYuYuAdjYd + traceTYeAdjYe*(-24.*traceAdjYdYd - 8.*traceAdjYeYe
      - 6.*Sqr(g1) + 18.*Sqr(g2) + 32.*Sqr(g3)))*(Yd*(TYd).adjoint()) +
      threeLoop*(24.*traceAdjTYuYuAdjYdYd - 72.*traceAdjTYdYd*traceAdjYdYd -
      24.*traceAdjTYeYe*traceAdjYdYd + 144.*traceAdjYdYdAdjTYdYd - 24.*
      traceAdjTYdYd*traceAdjYeYe - 8.*traceAdjTYeYe*traceAdjYeYe + 48.*
      traceAdjYeYeAdjTYeYe + 24.*traceAdjYuYuAdjTYdYd + 44.93333333333333*MassB
      *Quad(g1) + 174.*MassWB*Quad(g2) - 21.333333333333332*MassG*Quad(g3) -
      32.*traceAdjTYdYd*Sqr(g3) + 32.*traceAdjTYeYe*Sqr(g3) + 32.*MassG*
      traceAdjYdYd*Sqr(g3) - 32.*MassG*traceAdjYeYe*Sqr(g3) + Sqr(g1)*(14.*
      traceAdjTYdYd - 6.*traceAdjTYeYe - 14.*MassB*traceAdjYdYd + 6.*MassB*
      traceAdjYeYe + (17.2*MassB + 17.2*MassWB)*Sqr(g2) + (9.6*MassB + 9.6*
      MassG)*Sqr(g3)) + Sqr(g2)*(54.*traceAdjTYdYd + 18.*traceAdjTYeYe - 54.*
      MassWB*traceAdjYdYd - 18.*MassWB*traceAdjYeYe + (176.*MassG + 176.*MassWB
      )*Sqr(g3)))*(TYd*Yd.adjoint()) + threeLoop*(72.*traceAdjYdYdAdjYdYd - 24.
      *traceAdjYdYd*traceAdjYeYe + 24.*traceAdjYeYeAdjYeYe + 24.*
      traceAdjYuYuAdjYdYd - 22.466666666666665*Quad(g1) - 87.*Quad(g2) +
      10.666666666666666*Quad(g3) + Sqr(g2)*(54.*traceAdjYdYd + 18.*
      traceAdjYeYe - 176.*Sqr(g3)) + Sqr(g1)*(14.*traceAdjYdYd - 6.*
      traceAdjYeYe - 17.2*Sqr(g2) - 9.6*Sqr(g3)) - 32.*traceAdjYdYd*Sqr(g3) +
      32.*traceAdjYeYe*Sqr(g3) - 36.*Sqr(traceAdjYdYd) - 4.*Sqr(traceAdjYeYe))*
      (TYd*(TYd).adjoint()) + threeLoop*(36.*traceAdjYdYdAdjYdYd - 12.*
      traceAdjYdYd*traceAdjYeYe + 12.*traceAdjYeYeAdjYeYe + 12.*
      traceAdjYuYuAdjYdYd - 11.233333333333333*Quad(g1) - 43.5*Quad(g2) +
      5.333333333333333*Quad(g3) + Sqr(g2)*(27.*traceAdjYdYd + 9.*traceAdjYeYe
      - 88.*Sqr(g3)) + Sqr(g1)*(7.*traceAdjYdYd - 3.*traceAdjYeYe - 8.6*Sqr(g2)
      - 4.8*Sqr(g3)) - 16.*traceAdjYdYd*Sqr(g3) + 16.*traceAdjYeYe*Sqr(g3) -
      18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe))*(md2*Yd*Yd.adjoint()) +
      threeLoop*(72.*traceAdjYdYdAdjYdYd - 24.*traceAdjYdYd*traceAdjYeYe + 24.*
      traceAdjYeYeAdjYeYe + 24.*traceAdjYuYuAdjYdYd - 22.466666666666665*Quad(
      g1) - 87.*Quad(g2) + 10.666666666666666*Quad(g3) + Sqr(g2)*(54.*
      traceAdjYdYd + 18.*traceAdjYeYe - 176.*Sqr(g3)) + Sqr(g1)*(14.*
      traceAdjYdYd - 6.*traceAdjYeYe - 17.2*Sqr(g2) - 9.6*Sqr(g3)) - 32.*
      traceAdjYdYd*Sqr(g3) + 32.*traceAdjYeYe*Sqr(g3) - 36.*Sqr(traceAdjYdYd) -
      4.*Sqr(traceAdjYeYe))*(Yd*mq2*Yd.adjoint()) + threeLoop*(MassG*(384.*
      MassG + 384.*MassWB)*Sqr(g2)*Sqr(g3) - 1.12*Quad(g1)*Sqr(MassB) - 2176.*
      Quad(g3)*Sqr(MassG) - 108.*Quad(g2)*Sqr(MassWB) + Sqr(g1)*(Sqr(g3)*(
      42.666666666666664*MassB*MassG + 42.666666666666664*Sqr(MassB) +
      42.666666666666664*Sqr(MassG)) + Sqr(g2)*(33.6*MassB*MassWB + 33.6*Sqr(
      MassB) + 33.6*Sqr(MassWB))))*(Yd*Yd.adjoint()*1.2020569031595942))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_4 = ((threeLoop*(
      -0.18666666666666668*mHd2*Quad(g1) - 18.*mHd2*Quad(g2) + Sqr(g1)*(-24.*
      mHd2*traceAdjYdYd - 12.*traceAdjYdYdmq2 + 24.*mHd2*traceAdjYeYe + 12.*
      traceAdjYeYeml2 - 12.*traceTYdAdjTYd + 12.*traceTYeAdjTYe + MassB*(12.*
      traceAdjTYdYd - 12.*traceAdjTYeYe + 12.*traceTYdAdjYd - 12.*traceTYeAdjYe
      ) - 12.*traceYdAdjYdmd2 + 12.*traceYeAdjYeme2 + 21.333333333333332*mHd2*
      Sqr(g3) + (-24.*traceAdjYdYd + 24.*traceAdjYeYe)*Sqr(MassB)) + Sqr(g3)*(
      -192.*MassG*traceAdjTYdYd + 384.*mHd2*traceAdjYdYd + 192.*traceAdjYdYdmq2
      + 192.*traceTYdAdjTYd - 192.*MassG*traceTYdAdjYd + 192.*traceYdAdjYdmd2
      - 362.6666666666667*mHd2*Sqr(g3) + 384.*traceAdjYdYd*Sqr(MassG)) + Sqr(g2
      )*(108.*MassWB*traceAdjTYdYd + 36.*MassWB*traceAdjTYeYe - 216.*mHd2*
      traceAdjYdYd - 108.*traceAdjYdYdmq2 - 72.*mHd2*traceAdjYeYe - 36.*
      traceAdjYeYeml2 - 108.*traceTYdAdjTYd + 108.*MassWB*traceTYdAdjYd - 36.*
      traceTYeAdjTYe + 36.*MassWB*traceTYeAdjYe - 108.*traceYdAdjYdmd2 - 36.*
      traceYeAdjYeme2 + 16.8*mHd2*Sqr(g1) - 216.*traceAdjYdYd*Sqr(MassWB) - 72.
      *traceAdjYeYe*Sqr(MassWB) + Sqr(g3)*(192.*mHd2 + 384.*Sqr(MassWB))))*(Yd*
      Yd.adjoint()*1.2020569031595942) + threeLoop*(36.*traceAdjYdYdAdjYdYd -
      12.*traceAdjYdYd*traceAdjYeYe + 12.*traceAdjYeYeAdjYeYe + 12.*
      traceAdjYuYuAdjYdYd - 11.233333333333333*Quad(g1) - 43.5*Quad(g2) +
      5.333333333333333*Quad(g3) + Sqr(g2)*(27.*traceAdjYdYd + 9.*traceAdjYeYe
      - 88.*Sqr(g3)) + Sqr(g1)*(7.*traceAdjYdYd - 3.*traceAdjYeYe - 8.6*Sqr(g2)
      - 4.8*Sqr(g3)) - 16.*traceAdjYdYd*Sqr(g3) + 16.*traceAdjYeYe*Sqr(g3) -
      18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe))*(Yd*Yd.adjoint()*md2) +
      threeLoop*(0.37333333333333335*MassB*Quad(g1) + 36.*MassWB*Quad(g2) + Sqr
      (g1)*(12.*MassB*traceAdjYdYd - 12.*MassB*traceAdjYeYe - 12.*traceTYdAdjYd
      + 12.*traceTYeAdjYe + (-16.8*MassB - 16.8*MassWB)*Sqr(g2) + (
      -21.333333333333332*MassB - 21.333333333333332*MassG)*Sqr(g3)) + Sqr(g3)*
      (-192.*MassG*traceAdjYdYd + 192.*traceTYdAdjYd + 725.3333333333334*MassG*
      Sqr(g3)) + Sqr(g2)*(108.*MassWB*traceAdjYdYd + 36.*MassWB*traceAdjYeYe -
      108.*traceTYdAdjYd - 36.*traceTYeAdjYe + (-192.*MassG - 192.*MassWB)*Sqr(
      g3)))*(Yd*(TYd).adjoint()*1.2020569031595942) + threeLoop*(
      0.37333333333333335*MassB*Quad(g1) + 36.*MassWB*Quad(g2) + Sqr(g1)*(-12.*
      traceAdjTYdYd + 12.*traceAdjTYeYe + 12.*MassB*traceAdjYdYd - 12.*MassB*
      traceAdjYeYe + (-16.8*MassB - 16.8*MassWB)*Sqr(g2) + (-21.333333333333332
      *MassB - 21.333333333333332*MassG)*Sqr(g3)) + Sqr(g3)*(192.*traceAdjTYdYd
      - 192.*MassG*traceAdjYdYd + 725.3333333333334*MassG*Sqr(g3)) + Sqr(g2)*(
      -108.*traceAdjTYdYd - 36.*traceAdjTYeYe + 108.*MassWB*traceAdjYdYd + 36.*
      MassWB*traceAdjYeYe + (-192.*MassG - 192.*MassWB)*Sqr(g3)))*(TYd*
      Yd.adjoint()*1.2020569031595942) + threeLoop*(-0.18666666666666668*Quad(
      g1) + 16.8*Sqr(g1)*Sqr(g2))*(TYd*(TYd).adjoint()*1.2020569031595942))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_5 = ((threeLoop*(-18.*Quad(g2
      ) - 362.6666666666667*Quad(g3) + 192.*traceAdjYdYd*Sqr(g3) + Sqr(g1)*(
      -12.*traceAdjYdYd + 12.*traceAdjYeYe + 21.333333333333332*Sqr(g3)) + Sqr(
      g2)*(-108.*traceAdjYdYd - 36.*traceAdjYeYe + 192.*Sqr(g3)))*(TYd*(TYd)
      .adjoint()*1.2020569031595942) + threeLoop*(-0.09333333333333334*Quad(g1)
      - 9.*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*traceAdjYdYd*Sqr(g3) +
      Sqr(g1)*(-6.*traceAdjYdYd + 6.*traceAdjYeYe + 8.4*Sqr(g2) +
      10.666666666666666*Sqr(g3)) + Sqr(g2)*(-54.*traceAdjYdYd - 18.*
      traceAdjYeYe + 96.*Sqr(g3)))*(md2*Yd*Yd.adjoint()*1.2020569031595942) +
      threeLoop*(-0.18666666666666668*Quad(g1) - 18.*Quad(g2) -
      362.6666666666667*Quad(g3) + 192.*traceAdjYdYd*Sqr(g3) + Sqr(g1)*(-12.*
      traceAdjYdYd + 12.*traceAdjYeYe + 16.8*Sqr(g2) + 21.333333333333332*Sqr(
      g3)) + Sqr(g2)*(-108.*traceAdjYdYd - 36.*traceAdjYeYe + 192.*Sqr(g3)))*(
      Yd*mq2*Yd.adjoint()*1.2020569031595942) + threeLoop*(-0.09333333333333334
      *Quad(g1) - 9.*Quad(g2) - 181.33333333333334*Quad(g3) + 96.*traceAdjYdYd*
      Sqr(g3) + Sqr(g1)*(-6.*traceAdjYdYd + 6.*traceAdjYeYe + 8.4*Sqr(g2) +
      10.666666666666666*Sqr(g3)) + Sqr(g2)*(-54.*traceAdjYdYd - 18.*
      traceAdjYeYe + 96.*Sqr(g3)))*(Yd*Yd.adjoint()*md2*1.2020569031595942) +
      threeLoop*(36.*mHd2*traceAdjYdYd + 12.*traceAdjYdYdmq2 + 12.*mHd2*
      traceAdjYeYe + 4.*traceAdjYeYeml2 + 12.*traceTYdAdjTYd + 4.*
      traceTYeAdjTYe + 12.*traceYdAdjYdmd2 + 4.*traceYeAdjYeme2 + 36.*mHd2*Sqr(
      g2) + Sqr(g1)*(-1.3333333333333333*mHd2 - 1.3333333333333333*Sqr(MassB))
      + Sqr(g3)*(85.33333333333333*mHd2 + 85.33333333333333*Sqr(MassG)) + 36.*
      Sqr(g2)*Sqr(MassWB))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()) + threeLoop*(12.*
      traceTYdAdjYd + 4.*traceTYeAdjYe + 0.6666666666666666*MassB*Sqr(g1) - 18.
      *MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(Yd*Yd.adjoint()*Yd*(
      TYd).adjoint()) + threeLoop*(12.*traceAdjTYdYd + 4.*traceAdjTYeYe +
      0.6666666666666666*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yd*Yd.adjoint()*TYd*Yd.adjoint()) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe - 0.6666666666666666*Sqr(g1
      ) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yd*Yd.adjoint()*TYd*(TYd)
      .adjoint()) + threeLoop*(-24.*mHd2*traceAdjYdYd - 12.*mHu2*traceAdjYdYd -
      12.*traceAdjYdYdmq2 - 8.*mHd2*traceAdjYeYe - 4.*mHu2*traceAdjYeYe - 4.*
      traceAdjYeYeml2 + 24.*mHd2*traceAdjYuYu + 48.*mHu2*traceAdjYuYu + 24.*
      traceAdjYuYumq2 - 12.*traceTYdAdjTYd - 4.*traceTYeAdjTYe + 24.*
      traceTYuAdjTYu - 12.*traceYdAdjYdmd2 - 4.*traceYeAdjYeme2 + 24.*
      traceYuAdjYumu2 + 18.*mHd2*Sqr(g2) + 18.*mHu2*Sqr(g2) + Sqr(g1)*(
      -3.8666666666666663*mHd2 - 3.8666666666666663*mHu2 - 7.7333333333333325*
      Sqr(MassB)) + Sqr(g3)*(42.666666666666664*mHd2 + 42.666666666666664*mHu2
      + 85.33333333333333*Sqr(MassG)) + 36.*Sqr(g2)*Sqr(MassWB))*(Yd*Yu.adjoint
      ()*Yu*Yd.adjoint()) + threeLoop*(-12.*traceTYdAdjYd - 4.*traceTYeAdjYe +
      3.8666666666666663*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yd*Yu.adjoint()*Yu*(TYd).adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_6 = ((24.*threeLoop*
      traceTYuAdjYu*(Yd*Yu.adjoint()*Yu*(TYd).adjoint()) + threeLoop*(-12.*
      traceAdjTYdYd - 4.*traceAdjTYeYe + 24.*traceAdjTYuYu + 3.8666666666666663
      *MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(
      Yd*Yu.adjoint()*TYu*Yd.adjoint()) + threeLoop*(-12.*traceAdjYdYd - 4.*
      traceAdjYeYe + 24.*traceAdjYuYu - 3.8666666666666663*Sqr(g1) + 18.*Sqr(g2
      ) + 42.666666666666664*Sqr(g3))*(Yd*Yu.adjoint()*TYu*(TYd).adjoint()) +
      threeLoop*(12.*traceTYdAdjYd + 4.*traceTYeAdjYe + 0.6666666666666666*
      MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(
      Yd*(TYd).adjoint()*Yd*Yd.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yd*(TYd).adjoint()*TYd*Yd.adjoint()) +
      threeLoop*(-12.*traceTYdAdjYd - 4.*traceTYeAdjYe + 24.*traceTYuAdjYu +
      3.8666666666666663*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yd*(TYu).adjoint()*Yu*Yd.adjoint()) +
      threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe + 24.*traceAdjYuYu -
      3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yd*(TYu).adjoint()*TYu*Yd.adjoint()) + threeLoop*(12.*traceAdjTYdYd + 4.*
      traceAdjTYeYe + 0.6666666666666666*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(TYd*Yd.adjoint()*Yd*Yd.adjoint()) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe - 0.6666666666666666*Sqr(g1
      ) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(TYd*Yd.adjoint()*Yd*(TYd)
      .adjoint()) + threeLoop*(-12.*traceAdjTYdYd - 4.*traceAdjTYeYe + 24.*
      traceAdjTYuYu + 3.8666666666666663*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(TYd*Yu.adjoint()*Yu*Yd.adjoint()) +
      threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe + 24.*traceAdjYuYu -
      3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      TYd*Yu.adjoint()*Yu*(TYd).adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()) +
      threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe + 24.*traceAdjYuYu -
      3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      TYd*(TYu).adjoint()*Yu*Yd.adjoint()) + threeLoop*(6.*traceAdjYdYd + 2.*
      traceAdjYeYe - 0.3333333333333333*Sqr(g1) + 9.*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()) +
      threeLoop*(-6.*traceAdjYdYd - 2.*traceAdjYeYe + 12.*traceAdjYuYu -
      1.9333333333333331*Sqr(g1) + 9.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(
      md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()) +
      threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe + 24.*traceAdjYuYu -
      3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe - 0.6666666666666666*Sqr(g1
      ) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yd*Yd.adjoint()*Yd*mq2*
      Yd.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_7 = ((threeLoop*(Sqr(g1)*(4.8
      *mHd2 + 4.8*Sqr(MassB)) + Sqr(g2)*(-72.*mHd2 - 72.*Sqr(MassWB)))*(Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*1.2020569031595942) + threeLoop*(6.*
      traceAdjYdYd + 2.*traceAdjYeYe - 0.3333333333333333*Sqr(g1) + 9.*Sqr(g2)
      + 21.333333333333332*Sqr(g3))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2) +
      threeLoop*(-2.4*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(Yd*Yd.adjoint()*Yd*(
      TYd).adjoint()*1.2020569031595942) + threeLoop*(-2.4*MassB*Sqr(g1) + 36.*
      MassWB*Sqr(g2))*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*1.2020569031595942) +
      threeLoop*(2.4*Sqr(g1) - 36.*Sqr(g2))*(Yd*Yd.adjoint()*TYd*(TYd).adjoint(
      )*1.2020569031595942) + threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe +
      24.*traceAdjYuYu - 3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()) +
      threeLoop*(-12.*traceAdjYdYd - 4.*traceAdjYeYe + 24.*traceAdjYuYu -
      3.8666666666666663*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()) + threeLoop*(Sqr(g1)*(
      7.200000000000001*mHd2 + 7.200000000000001*mHu2 + 14.400000000000002*Sqr(
      MassB)) + Sqr(g2)*(-36.*mHd2 - 36.*mHu2 - 72.*Sqr(MassWB)))*(Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*1.2020569031595942) + threeLoop*(-6.*
      traceAdjYdYd - 2.*traceAdjYeYe + 12.*traceAdjYuYu - 1.9333333333333331*
      Sqr(g1) + 9.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(Yd*Yu.adjoint()*Yu*
      Yd.adjoint()*md2) + threeLoop*(-7.200000000000001*MassB*Sqr(g1) + 36.*
      MassWB*Sqr(g2))*(Yd*Yu.adjoint()*Yu*(TYd).adjoint()*1.2020569031595942) +
      threeLoop*(-7.200000000000001*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(Yd*
      Yu.adjoint()*TYu*Yd.adjoint()*1.2020569031595942) + threeLoop*(
      7.200000000000001*Sqr(g1) - 36.*Sqr(g2))*(Yd*Yu.adjoint()*TYu*(TYd)
      .adjoint()*1.2020569031595942) + threeLoop*(-2.4*MassB*Sqr(g1) + 36.*
      MassWB*Sqr(g2))*(Yd*(TYd).adjoint()*Yd*Yd.adjoint()*1.2020569031595942) +
      threeLoop*(2.4*Sqr(g1) - 36.*Sqr(g2))*(Yd*(TYd).adjoint()*TYd*Yd.adjoint
      ()*1.2020569031595942) + threeLoop*(-7.200000000000001*MassB*Sqr(g1) +
      36.*MassWB*Sqr(g2))*(Yd*(TYu).adjoint()*Yu*Yd.adjoint()*
      1.2020569031595942) + threeLoop*(7.200000000000001*Sqr(g1) - 36.*Sqr(g2))
      *(Yd*(TYu).adjoint()*TYu*Yd.adjoint()*1.2020569031595942) + threeLoop*(
      -2.4*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(TYd*Yd.adjoint()*Yd*Yd.adjoint(
      )*1.2020569031595942) + threeLoop*(2.4*Sqr(g1) - 36.*Sqr(g2))*(TYd*
      Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942) + threeLoop*(
      -7.200000000000001*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(TYd*Yu.adjoint()*
      Yu*Yd.adjoint()*1.2020569031595942) + threeLoop*(7.200000000000001*Sqr(g1
      ) - 36.*Sqr(g2))*(TYd*Yu.adjoint()*Yu*(TYd).adjoint()*1.2020569031595942)
      + threeLoop*(2.4*Sqr(g1) - 36.*Sqr(g2))*(TYd*(TYd).adjoint()*Yd*
      Yd.adjoint()*1.2020569031595942) + threeLoop*(7.200000000000001*Sqr(g1) -
      36.*Sqr(g2))*(TYd*(TYu).adjoint()*Yu*Yd.adjoint()*1.2020569031595942) +
      threeLoop*(1.2*Sqr(g1) - 18.*Sqr(g2))*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint(
      )*1.2020569031595942) + threeLoop*(3.6000000000000005*Sqr(g1) - 18.*Sqr(
      g2))*(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()*1.2020569031595942) + threeLoop
      *(2.4*Sqr(g1) - 36.*Sqr(g2))*(Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()*
      1.2020569031595942) + threeLoop*(7.200000000000001*Sqr(g1) - 36.*Sqr(g2))
      *(Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()*1.2020569031595942) + threeLoop*(
      2.4*Sqr(g1) - 36.*Sqr(g2))*(Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()*
      1.2020569031595942) + threeLoop*(2.4*Sqr(g1) - 36.*Sqr(g2))*(Yd*
      Yd.adjoint()*Yd*mq2*Yd.adjoint()*1.2020569031595942) + threeLoop*(1.2*Sqr
      (g1) - 18.*Sqr(g2))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*
      1.2020569031595942) + 36.*mHd2*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()
      *Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*(
      TYd).adjoint()) + (-8.*mHd2 - 4.*mHu2)*threeLoop*(Yd*Yd.adjoint()*Yd*
      Yu.adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*
      Yu.adjoint()*TYu*(TYd).adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*(
      TYd).adjoint()*TYd*Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*(TYu)
      .adjoint()*TYu*Yd.adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*TYd*
      Yd.adjoint()*Yd*(TYd).adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*TYd*
      Yu.adjoint()*Yu*(TYd).adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*TYd*(
      TYd).adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*TYd*(TYu)
      .adjoint()*Yu*Yd.adjoint()) + threeLoop*(7.200000000000001*Sqr(g1) - 36.*
      Sqr(g2))*(Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()*1.2020569031595942) +
      threeLoop*(7.200000000000001*Sqr(g1) - 36.*Sqr(g2))*(Yd*Yu.adjoint()*Yu*
      mq2*Yd.adjoint()*1.2020569031595942) + threeLoop*(3.6000000000000005*Sqr(
      g1) - 18.*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*md2*
      1.2020569031595942) + (-8.*mHd2 - 4.*mHu2)*threeLoop*(Yd*Yu.adjoint()*Yu*
      Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*Yu*
      Yd.adjoint()*TYd*(TYd).adjoint()) + 12.*mHd2*threeLoop*(Yd*Yu.adjoint()*
      Yu*Yu.adjoint()*Yu*Yd.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_8 = ((24.*mHu2*threeLoop*(Yd*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yu.adjoint()*Yu*Yu.adjoint()*TYu*(TYd).adjoint()) - 4.*threeLoop*(Yd*
      Yu.adjoint()*Yu*(TYd).adjoint()*TYd*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yu.adjoint()*Yu*(TYu).adjoint()*TYu*Yd.adjoint()) - 4.*threeLoop*(Yd*
      Yu.adjoint()*TYu*Yd.adjoint()*Yd*(TYd).adjoint()) + 12.*threeLoop*(Yd*
      Yu.adjoint()*TYu*Yu.adjoint()*Yu*(TYd).adjoint()) - 4.*threeLoop*(Yd*
      Yu.adjoint()*TYu*(TYd).adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yu.adjoint()*TYu*(TYu).adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*(
      TYd).adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYd)
      .adjoint()*Yd*Yu.adjoint()*TYu*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYd)
      .adjoint()*TYd*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYd)
      .adjoint()*TYd*Yu.adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYu)
      .adjoint()*Yu*Yd.adjoint()*TYd*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYu)
      .adjoint()*Yu*Yu.adjoint()*TYu*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYu)
      .adjoint()*TYu*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYu)
      .adjoint()*TYu*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(TYd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*(TYd).adjoint()) - 4.*threeLoop*(TYd*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*(TYd).adjoint()) + 12.*threeLoop*(TYd*
      Yd.adjoint()*Yd*(TYd).adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(TYd*
      Yd.adjoint()*Yd*(TYu).adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(TYd*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*(TYd).adjoint()) + 12.*threeLoop*(TYd*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYd).adjoint()) - 4.*threeLoop*(TYd*
      Yu.adjoint()*Yu*(TYd).adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(TYd*
      Yu.adjoint()*Yu*(TYu).adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(TYd*(
      TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(TYd*(TYd)
      .adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(TYd*(TYu)
      .adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(TYd*(TYu)
      .adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()) + 6.*threeLoop*(md2*Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 2.*threeLoop*(md2*Yd*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()) - 2.*threeLoop*(md2*Yd*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()) + 6.*threeLoop*(md2*Yd*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*mq2*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*mq2*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*mq2*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*mq2*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*
      Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*
      Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint()) + 72.*mHd2*threeLoop*(
      Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*1.2020569031595942) + 6.*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2) + 24.*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*(TYd).adjoint()*
      1.2020569031595942) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*mu2*
      Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*mq2*
      Yd.adjoint()) - 2.*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*
      Yd.adjoint()*md2) + 24.*threeLoop*(Yd*Yd.adjoint()*Yd*(TYd).adjoint()*TYd
      *Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yd*Yd.adjoint()*TYd*
      Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942) + 24.*threeLoop*(Yd*
      Yd.adjoint()*TYd*(TYd).adjoint()*Yd*Yd.adjoint()*1.2020569031595942) - 4.
      *threeLoop*(Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*
      threeLoop*(Yd*Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*Yd.adjoint()) - 4.*
      threeLoop*(Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*
      threeLoop*(Yd*Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*Yd.adjoint()) - 4.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*md2*Yd*Yd.adjoint()) - 4.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*mq2*Yd.adjoint()) - 2.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()*md2) + 12.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yd.adjoint()) + 12.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yd.adjoint()) + 6.*
      threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()*md2) + 24.*
      threeLoop*(Yd*(TYd).adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yd*(TYd).adjoint()*TYd*Yd.adjoint()*
      Yd*Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942) + 24.*threeLoop*(TYd*
      Yd.adjoint()*Yd*(TYd).adjoint()*Yd*Yd.adjoint()*1.2020569031595942) + 24.
      *threeLoop*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*
      1.2020569031595942) + 12.*threeLoop*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()*
      Yd*Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yd*mq2*Yd.adjoint()*
      Yd*Yd.adjoint()*Yd*Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yd*
      Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*
      Yd*Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*mq2*Yd.adjoint()*1.2020569031595942) + 12.*threeLoop*(Yd*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*1.2020569031595942))*
      UNITMATRIX(3)).real();

   beta_md2 = beta_md2_1 + beta_md2_2 + beta_md2_3 + beta_md2_4 +
      beta_md2_5 + beta_md2_6 + beta_md2_7 + beta_md2_8;


   return beta_md2;
}

} // namespace flexiblesusy
