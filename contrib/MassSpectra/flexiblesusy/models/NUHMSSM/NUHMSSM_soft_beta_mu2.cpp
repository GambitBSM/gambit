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

// File generated at Thu 10 May 2018 15:02:49

#include "NUHMSSM_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of mu2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> NUHMSSM_soft_parameters::calc_beta_mu2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = (oneOver16PiSqr*(4*mHu2*(Yu*Yu.adjoint()) + 4*(TYu*(TYu)
      .adjoint()) + 2*(mu2*Yu*Yu.adjoint()) + 4*(Yu*mq2*Yu.adjoint()) + 2*(Yu*
      Yu.adjoint()*mu2) - 0.26666666666666666*(3.872983346207417*g1*Tr11 + 8*
      AbsSqr(MassB)*Sqr(g1) + 40*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_mu2;
}

/**
 * Calculates the 2-loop beta function of mu2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> NUHMSSM_soft_parameters::calc_beta_mu2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceconjTYuTpYu = TRACE_STRUCT.traceconjTYuTpYu;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr23 = TRACE_STRUCT.Tr23;


   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = (twoLoop*(-0.8*(15*traceconjTYuTpTYu + 15*tracemq2AdjYuYu +
      15*tracemu2YuAdjYu + 30*mHu2*traceYuAdjYu + mHu2*Sqr(g1) + 2*AbsSqr(
      MassB)*Sqr(g1) - 15*mHu2*Sqr(g2) - 30*AbsSqr(MassWB)*Sqr(g2))*(Yu*
      Yu.adjoint()) + (0.8*MassB*Sqr(g1) - 12*(traceAdjYuTYu + MassWB*Sqr(g2)))
      *(Yu*(TYu).adjoint()) + (0.8*Conj(MassB)*Sqr(g1) - 12*(traceconjTYuTpYu +
      Conj(MassWB)*Sqr(g2)))*(TYu*Yu.adjoint()) - 0.8*(Sqr(g1) + 15*(
      traceYuAdjYu - Sqr(g2)))*(TYu*(TYu).adjoint()) + (-6*traceYuAdjYu - 0.4*
      Sqr(g1) + 6*Sqr(g2))*(mu2*Yu*Yu.adjoint()) - 0.8*(Sqr(g1) + 15*(
      traceYuAdjYu - Sqr(g2)))*(Yu*mq2*Yu.adjoint()) + (-6*traceYuAdjYu - 0.4*
      Sqr(g1) + 6*Sqr(g2))*(Yu*Yu.adjoint()*mu2) - 4*(mHd2 + mHu2)*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()) - 4*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()) -
      8*mHu2*(Yu*Yu.adjoint()*Yu*Yu.adjoint()) - 4*(Yu*Yu.adjoint()*TYu*(TYu)
      .adjoint()) - 4*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()) - 4*(Yu*(TYu)
      .adjoint()*TYu*Yu.adjoint()) - 4*(TYu*Yd.adjoint()*Yd*(TYu).adjoint()) -
      4*(TYu*Yu.adjoint()*Yu*(TYu).adjoint()) - 4*(TYu*(TYd).adjoint()*Yd*
      Yu.adjoint()) - 4*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()) - 2*(mu2*Yu*
      Yd.adjoint()*Yd*Yu.adjoint()) - 2*(mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()) -
      4*(Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()) - 4*(Yu*mq2*Yu.adjoint()*Yu*
      Yu.adjoint()) - 4*(Yu*Yd.adjoint()*md2*Yd*Yu.adjoint()) - 4*(Yu*
      Yd.adjoint()*Yd*mq2*Yu.adjoint()) - 2*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*
      mu2) - 4*(Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()) - 4*(Yu*Yu.adjoint()*Yu*
      mq2*Yu.adjoint()) - 2*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2) +
      0.07111111111111111*(2*Conj(MassB)*(321*MassB*Quad(g1) + 40*(2*MassB +
      MassG)*Sqr(g1)*Sqr(g3)) + 5*(-11.618950038622252*g1*Tr31 + 30*Tr23*Quad(
      g3) + 6*Tr2U111*Sqr(g1) + 8*Conj(MassG)*Sqr(g3)*(2*(MassB + 2*MassG)*Sqr(
      g1) - 15*MassG*Sqr(g3))))*UNITMATRIX(3))).real();


   return beta_mu2;
}

/**
 * Calculates the 3-loop beta function of mu2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> NUHMSSM_soft_parameters::calc_beta_mu2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjYuYuAdjTYuYu = TRACE_STRUCT.traceAdjYuYuAdjTYuYu;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceAdjYuTYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYu =
      TRACE_STRUCT.traceAdjYuTYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYu =
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceAdjTYuTYuAdjYuYu =
      TRACE_STRUCT.traceAdjTYuTYuAdjYuYu;
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
   const double traceAdjYuYuAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYuYumq2;


   Eigen::Matrix<double,3,3> beta_mu2;

   const Eigen::Matrix<double,3,3> beta_mu2_1 = ((threeLoop*(Power6(g1)*(
      -9.130666666666666*mHd2 - 9.130666666666666*mHu2 - 6.087111111111111*
      tracemd2 - 18.261333333333333*traceme2 - 9.130666666666666*traceml2 -
      3.0435555555555553*tracemq2 - 24.348444444444443*tracemu2 +
      401.01536764151473*Sqr(MassB)) + Quad(g3)*Sqr(g1)*(-199.82738974264868*
      MassB*MassG - 5.688888888888889*tracemd2 - 11.377777777777778*tracemq2 -
      5.688888888888889*tracemu2 - 88.180361537991*Sqr(MassB) -
      265.6077512806396*Sqr(MassG)) + Quad(g3)*(106.66666666666666*MassG*
      traceAdjTYdYd + 106.66666666666666*MassG*traceAdjTYuYu - 64.*mHd2*
      traceAdjYdYd - 64.*traceAdjYdYdmq2 - 64.*mHu2*traceAdjYuYu - 64.*
      traceAdjYuYumq2 - 64.*traceTYdAdjTYd + 106.66666666666666*MassG*
      traceTYdAdjYd - 64.*traceTYuAdjTYu + 106.66666666666666*MassG*
      traceTYuAdjYu - 64.*traceYdAdjYdmd2 - 64.*traceYuAdjYumu2 - 320.*
      traceAdjYdYd*Sqr(MassG) - 320.*traceAdjYuYu*Sqr(MassG) + Sqr(g3)*(
      35.55555555555556*tracemd2 + 71.11111111111111*tracemq2 +
      35.55555555555556*tracemu2 + 11510.908127376795*Sqr(MassG)) + Sqr(g2)*(
      -212.38477621992624*MassG*MassWB - 318.57716432988946*Sqr(MassG) -
      58.192388109963126*Sqr(MassWB))) + Quad(g1)*(14.933333333333334*MassB*
      traceAdjTYdYd + 19.2*MassB*traceAdjTYeYe + 27.733333333333334*MassB*
      traceAdjTYuYu - 8.96*mHd2*traceAdjYdYd - 8.96*traceAdjYdYdmq2 - 11.52*
      mHd2*traceAdjYeYe - 11.52*traceAdjYeYeml2 - 16.64*mHu2*traceAdjYuYu -
      16.64*traceAdjYuYumq2 - 8.96*traceTYdAdjTYd + 14.933333333333334*MassB*
      traceTYdAdjYd - 11.52*traceTYeAdjTYe + 19.2*MassB*traceTYeAdjYe - 16.64*
      traceTYuAdjTYu + 27.733333333333334*MassB*traceTYuAdjYu - 8.96*
      traceYdAdjYdmd2 - 11.52*traceYeAdjYeme2 - 16.64*traceYuAdjYumu2 - 44.8*
      traceAdjYdYd*Sqr(MassB) - 57.599999999999994*traceAdjYeYe*Sqr(MassB) -
      83.2*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(-194.56826803268228*MassB*MassG -
      3.4133333333333336*mHd2 - 3.4133333333333336*mHu2 - 2.2755555555555556*
      tracemd2 - 6.826666666666667*traceme2 - 3.4133333333333336*traceml2 -
      1.1377777777777778*tracemq2 - 9.102222222222222*tracemu2 -
      291.85240204902345*Sqr(MassB) - 78.5108006830078*Sqr(MassG)) + Sqr(g2)*(
      -25.48617314639116*MassB*MassWB - 38.229259719586736*Sqr(MassB) -
      6.983086573195578*Sqr(MassWB)))) + threeLoop*(24.*traceAdjTYdTYdAdjYuYu +
      24.*traceAdjTYuTYuAdjYdYd + 144.*traceAdjTYuTYuAdjYuYu + 24.*
      traceAdjYdYdAdjYuYumq2 + 24.*traceAdjYuTYuAdjTYdYd + 144.*
      traceAdjYuTYuAdjTYuYu + 10.666666666666666*mHu2*Quad(g3) + 32.*MassG*
      traceAdjTYuYu*Sqr(g3) + Quad(g1)*(0.48*mHd2 - 31.480000000000004*mHu2 -
      191.76*Sqr(MassB)) + 64.*Quad(g3)*Sqr(MassG) - 64.*traceAdjYuYu*Sqr(g3)*
      Sqr(MassG) + Sqr(g2)*(-53.99999999999999*MassWB*traceAdjTYuYu + Sqr(g3)*(
      -352.*MassG*MassWB - 176.*mHu2 - 352.*Sqr(MassG) - 352.*Sqr(MassWB))) +
      Sqr(g1)*(MassB*(-14.*traceAdjTYuYu + 28.*MassB*traceAdjYuYu) + Sqr(g3)*(
      -2.1333333333333333*MassB*MassG - 1.0666666666666667*mHu2 -
      2.1333333333333333*Sqr(MassB) - 2.1333333333333333*Sqr(MassG)) + Sqr(g2)*
      (-53.6*MassB*MassWB - 26.8*mHu2 - 53.6*Sqr(MassB) - 53.6*Sqr(MassWB))) +
      Quad(g2)*(-12.*mHd2 - 99.*mHu2 - 474.*Sqr(MassWB)))*(Yu*Yu.adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_2 = ((threeLoop*(24.*mHd2*
      traceAdjYuYuAdjYdYd + 48.*mHu2*traceAdjYuYuAdjYdYd + 24.*
      traceAdjYuYuAdjYdYdmq2 + 215.99999999999997*mHu2*traceAdjYuYuAdjYuYu +
      144.*traceAdjYuYuAdjYuYumq2 - 72.*traceAdjYuYu*traceAdjYuYumq2 + 24.*
      traceTYdAdjTYuYuAdjYd - 72.*traceAdjYuYu*traceTYuAdjTYu - 72.*
      traceAdjTYuYu*traceTYuAdjYu + 24.*traceYdAdjYuYuAdjYdmd2 + 24.*
      traceYuAdjYdYdAdjYumu2 - 72.*traceAdjYuYu*traceYuAdjYumu2 + 144.*
      traceYuAdjYuYuAdjYumu2 + (0.32*tracemd2 + 0.96*traceme2 + 0.48*traceml2 +
      0.16*tracemq2 + 1.28*tracemu2)*Quad(g1) + (-12.*traceml2 - 36.*tracemq2)
      *Quad(g2) + (28.*mHu2*traceAdjYuYu + 14.*traceAdjYuYumq2 + 14.*
      traceTYuAdjTYu - 14.*MassB*traceTYuAdjYu + 14.*traceYuAdjYumu2)*Sqr(g1) -
      64.*mHu2*traceAdjYuYu*Sqr(g3) - 32.*traceAdjYuYumq2*Sqr(g3) - 32.*
      traceTYuAdjTYu*Sqr(g3) + 32.*MassG*traceTYuAdjYu*Sqr(g3) - 32.*
      traceYuAdjYumu2*Sqr(g3) + Sqr(g2)*(107.99999999999999*mHu2*traceAdjYuYu +
      53.99999999999999*traceAdjYuYumq2 + 53.99999999999999*traceTYuAdjTYu -
      53.99999999999999*MassWB*traceTYuAdjYu + 53.99999999999999*
      traceYuAdjYumu2 + 107.99999999999999*traceAdjYuYu*Sqr(MassWB)) -
      107.99999999999999*mHu2*Sqr(traceAdjYuYu))*(Yu*Yu.adjoint()) + threeLoop*
      (24.*traceAdjYuTYuAdjYdYd + 144.*traceAdjYuTYuAdjYuYu + 24.*
      traceTYdAdjYuYuAdjYd - 72.*traceAdjYuYu*traceTYuAdjYu + 63.92*MassB*Quad(
      g1) + 174.*MassWB*Quad(g2) - 21.333333333333332*MassG*Quad(g3) + 32.*
      MassG*traceAdjYuYu*Sqr(g3) - 32.*traceTYuAdjYu*Sqr(g3) + Sqr(g1)*(-14.*
      MassB*traceAdjYuYu + 14.*traceTYuAdjYu + (26.8*MassB + 26.8*MassWB)*Sqr(
      g2) + (1.0666666666666667*MassB + 1.0666666666666667*MassG)*Sqr(g3)) +
      Sqr(g2)*(-53.99999999999999*MassWB*traceAdjYuYu + 53.99999999999999*
      traceTYuAdjYu + (176.*MassG + 176.*MassWB)*Sqr(g3)))*(Yu*(TYu).adjoint())
      + threeLoop*(24.*traceAdjTYuYuAdjYdYd - 72.*traceAdjTYuYu*traceAdjYuYu +
      24.*traceAdjYuYuAdjTYdYd + 144.*traceAdjYuYuAdjTYuYu + 63.92*MassB*Quad(
      g1) + 174.*MassWB*Quad(g2) - 21.333333333333332*MassG*Quad(g3) - 32.*
      traceAdjTYuYu*Sqr(g3) + 32.*MassG*traceAdjYuYu*Sqr(g3) + Sqr(g1)*(14.*
      traceAdjTYuYu - 14.*MassB*traceAdjYuYu + (26.8*MassB + 26.8*MassWB)*Sqr(
      g2) + (1.0666666666666667*MassB + 1.0666666666666667*MassG)*Sqr(g3)) +
      Sqr(g2)*(53.99999999999999*traceAdjTYuYu - 53.99999999999999*MassWB*
      traceAdjYuYu + (176.*MassG + 176.*MassWB)*Sqr(g3)))*(TYu*Yu.adjoint()) +
      threeLoop*(24.*traceAdjYuYuAdjYdYd + 72.*traceAdjYuYuAdjYuYu - 31.96*Quad
      (g1) - 87.*Quad(g2) + 10.666666666666666*Quad(g3) + Sqr(g2)*(
      53.99999999999999*traceAdjYuYu - 176.*Sqr(g3)) + Sqr(g1)*(14.*
      traceAdjYuYu - 26.8*Sqr(g2) - 1.0666666666666667*Sqr(g3)) - 32.*
      traceAdjYuYu*Sqr(g3) - 36.*Sqr(traceAdjYuYu))*(TYu*(TYu).adjoint()) +
      threeLoop*(12.*traceAdjYuYuAdjYdYd + 36.*traceAdjYuYuAdjYuYu - 15.98*Quad
      (g1) - 43.5*Quad(g2) + 5.333333333333333*Quad(g3) + Sqr(g2)*(
      26.999999999999996*traceAdjYuYu - 88.*Sqr(g3)) + Sqr(g1)*(7.*traceAdjYuYu
      - 13.4*Sqr(g2) - 0.5333333333333333*Sqr(g3)) - 16.*traceAdjYuYu*Sqr(g3)
      - 18.*Sqr(traceAdjYuYu))*(mu2*Yu*Yu.adjoint()) - 31.96*threeLoop*Quad(g1)
      *(Yu*mq2*Yu.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_3 = ((threeLoop*(24.*
      traceAdjYuYuAdjYdYd + 72.*traceAdjYuYuAdjYuYu - 87.*Quad(g2) +
      10.666666666666666*Quad(g3) + Sqr(g2)*(53.99999999999999*traceAdjYuYu -
      176.*Sqr(g3)) + Sqr(g1)*(14.*traceAdjYuYu - 26.8*Sqr(g2) -
      1.0666666666666667*Sqr(g3)) - 32.*traceAdjYuYu*Sqr(g3) - 36.*Sqr(
      traceAdjYuYu))*(Yu*mq2*Yu.adjoint()) + threeLoop*(Quad(g1)*(
      -6.586666666666667*mHu2 - 39.52*Sqr(MassB)) + Sqr(g3)*(-192.*MassG*
      traceAdjTYuYu + 384.*mHu2*traceAdjYuYu + 192.*traceAdjYuYumq2 + 192.*
      traceTYuAdjTYu - 192.*MassG*traceTYuAdjYu + 192.*traceYuAdjYumu2 + Sqr(g3
      )*(-362.6666666666667*mHu2 - 2176.*Sqr(MassG)) + 384.*traceAdjYuYu*Sqr(
      MassG)) + Quad(g2)*(-18.*mHu2 - 107.99999999999999*Sqr(MassWB)) + Sqr(g1)
      *(-16.8*MassB*traceAdjTYuYu + 33.6*mHu2*traceAdjYuYu + 16.8*
      traceAdjYuYumq2 + 16.8*traceTYuAdjTYu - 16.8*MassB*traceTYuAdjYu + 16.8*
      traceYuAdjYumu2 + 33.6*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(
      -59.733333333333334*MassB*MassG - 29.866666666666667*mHu2 -
      59.733333333333334*Sqr(MassB) - 59.733333333333334*Sqr(MassG)) + Sqr(g2)*
      (62.39999999999999*MassB*MassWB + 31.199999999999996*mHu2 +
      62.39999999999999*Sqr(MassB) + 62.39999999999999*Sqr(MassWB))) + Sqr(g2)*
      (107.99999999999999*MassWB*traceAdjTYuYu - 215.99999999999997*mHu2*
      traceAdjYuYu - 107.99999999999999*traceAdjYuYumq2 - 107.99999999999999*
      traceTYuAdjTYu + 107.99999999999999*MassWB*traceTYuAdjYu -
      107.99999999999999*traceYuAdjYumu2 - 215.99999999999997*traceAdjYuYu*Sqr(
      MassWB) + Sqr(g3)*(384.*MassG*MassWB + 192.*mHu2 + 384.*Sqr(MassG) + 384.
      *Sqr(MassWB))))*(Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(12.*
      traceAdjYuYuAdjYdYd + 36.*traceAdjYuYuAdjYuYu - 15.98*Quad(g1) - 43.5*
      Quad(g2) + 5.333333333333333*Quad(g3) + Sqr(g2)*(26.999999999999996*
      traceAdjYuYu - 88.*Sqr(g3)) + Sqr(g1)*(7.*traceAdjYuYu - 13.4*Sqr(g2) -
      0.5333333333333333*Sqr(g3)) - 16.*traceAdjYuYu*Sqr(g3) - 18.*Sqr(
      traceAdjYuYu))*(Yu*Yu.adjoint()*mu2) + threeLoop*(13.173333333333334*
      MassB*Quad(g1) + 36.*MassWB*Quad(g2) + Sqr(g3)*(-192.*MassG*traceAdjYuYu
      + 192.*traceTYuAdjYu + 725.3333333333334*MassG*Sqr(g3)) + Sqr(g1)*(-16.8*
      MassB*traceAdjYuYu + 16.8*traceTYuAdjYu + (-31.199999999999996*MassB -
      31.199999999999996*MassWB)*Sqr(g2) + (29.866666666666667*MassB +
      29.866666666666667*MassG)*Sqr(g3)) + Sqr(g2)*(107.99999999999999*MassWB*
      traceAdjYuYu - 107.99999999999999*traceTYuAdjYu + (-192.*MassG - 192.*
      MassWB)*Sqr(g3)))*(Yu*(TYu).adjoint()*1.2020569031595942) + threeLoop*(
      13.173333333333334*MassB*Quad(g1) + 36.*MassWB*Quad(g2) + Sqr(g3)*(192.*
      traceAdjTYuYu - 192.*MassG*traceAdjYuYu + 725.3333333333334*MassG*Sqr(g3)
      ) + Sqr(g1)*(16.8*traceAdjTYuYu - 16.8*MassB*traceAdjYuYu + (
      -31.199999999999996*MassB - 31.199999999999996*MassWB)*Sqr(g2) + (
      29.866666666666667*MassB + 29.866666666666667*MassG)*Sqr(g3)) + Sqr(g2)*(
      -107.99999999999999*traceAdjTYuYu + 107.99999999999999*MassWB*
      traceAdjYuYu + (-192.*MassG - 192.*MassWB)*Sqr(g3)))*(TYu*Yu.adjoint()*
      1.2020569031595942) + threeLoop*(-6.586666666666667*Quad(g1) - 18.*Quad(
      g2) - 362.6666666666667*Quad(g3) + Sqr(g1)*(16.8*traceAdjYuYu +
      31.199999999999996*Sqr(g2) - 29.866666666666667*Sqr(g3)) + Sqr(g2)*(
      -107.99999999999999*traceAdjYuYu + 192.*Sqr(g3)))*(TYu*(TYu).adjoint()*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_4 = ((192.*threeLoop*
      traceAdjYuYu*Sqr(g3)*(TYu*(TYu).adjoint()*1.2020569031595942) + threeLoop
      *(-3.2933333333333334*Quad(g1) - 9.*Quad(g2) - 181.33333333333334*Quad(g3
      ) + Sqr(g1)*(8.4*traceAdjYuYu + 15.599999999999998*Sqr(g2) -
      14.933333333333334*Sqr(g3)) + 96.*traceAdjYuYu*Sqr(g3) + Sqr(g2)*(
      -53.99999999999999*traceAdjYuYu + 96.*Sqr(g3)))*(mu2*Yu*Yu.adjoint()*
      1.2020569031595942) + threeLoop*(-6.586666666666667*Quad(g1) - 18.*Quad(
      g2) - 362.6666666666667*Quad(g3) + Sqr(g1)*(16.8*traceAdjYuYu +
      31.199999999999996*Sqr(g2) - 29.866666666666667*Sqr(g3)) + 192.*
      traceAdjYuYu*Sqr(g3) + Sqr(g2)*(-107.99999999999999*traceAdjYuYu + 192.*
      Sqr(g3)))*(Yu*mq2*Yu.adjoint()*1.2020569031595942) + threeLoop*(48.*mHd2*
      traceAdjYdYd + 24.*mHu2*traceAdjYdYd + 24.*traceAdjYdYdmq2 + 16.*mHd2*
      traceAdjYeYe + 8.*mHu2*traceAdjYeYe + 8.*traceAdjYeYeml2 - 12.*mHd2*
      traceAdjYuYu - 24.*mHu2*traceAdjYuYu - 12.*traceAdjYuYumq2 + 24.*
      traceTYdAdjTYd + 8.*traceTYeAdjTYe - 12.*traceTYuAdjTYu + 24.*
      traceYdAdjYdmd2 + 8.*traceYeAdjYeme2 - 12.*traceYuAdjYumu2 + 18.*mHd2*Sqr
      (g2) + 18.*mHu2*Sqr(g2) + Sqr(g1)*(2.533333333333333*mHd2 +
      2.533333333333333*mHu2 + 5.066666666666666*Sqr(MassB)) + Sqr(g3)*(
      42.666666666666664*mHd2 + 42.666666666666664*mHu2 + 85.33333333333333*Sqr
      (MassG)) + 36.*Sqr(g2)*Sqr(MassWB))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()) +
      threeLoop*(24.*traceTYdAdjYd + 8.*traceTYeAdjYe - 12.*traceTYuAdjYu -
      2.533333333333333*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664
      *MassG*Sqr(g3))*(Yu*Yd.adjoint()*Yd*(TYu).adjoint()) + threeLoop*(24.*
      traceAdjTYdYd + 8.*traceAdjTYeYe - 12.*traceAdjTYuYu - 2.533333333333333*
      MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(
      Yu*Yd.adjoint()*TYd*Yu.adjoint()) + threeLoop*(24.*traceAdjYdYd + 8.*
      traceAdjYeYe - 12.*traceAdjYuYu + 2.533333333333333*Sqr(g1) + 18.*Sqr(g2)
      + 42.666666666666664*Sqr(g3))*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()) +
      threeLoop*(-3.2933333333333334*Quad(g1) - 9.*Quad(g2) -
      181.33333333333334*Quad(g3) + Sqr(g1)*(8.4*traceAdjYuYu +
      15.599999999999998*Sqr(g2) - 14.933333333333334*Sqr(g3)) + 96.*
      traceAdjYuYu*Sqr(g3) + Sqr(g2)*(-53.99999999999999*traceAdjYuYu + 96.*Sqr
      (g3)))*(Yu*Yu.adjoint()*mu2*1.2020569031595942) + threeLoop*(36.*mHu2*
      traceAdjYuYu + 12.*traceAdjYuYumq2 + 12.*traceTYuAdjTYu + 12.*
      traceYuAdjYumu2 + 36.*mHu2*Sqr(g2) + Sqr(g1)*(-1.3333333333333333*mHu2 -
      1.3333333333333333*Sqr(MassB)) + Sqr(g3)*(85.33333333333333*mHu2 +
      85.33333333333333*Sqr(MassG)) + 36.*Sqr(g2)*Sqr(MassWB))*(Yu*Yu.adjoint()
      *Yu*Yu.adjoint()) + threeLoop*(12.*traceTYuAdjYu + 0.6666666666666666*
      MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(
      Yu*Yu.adjoint()*Yu*(TYu).adjoint()) + threeLoop*(12.*traceAdjTYuYu +
      0.6666666666666666*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yu*Yu.adjoint()*TYu*Yu.adjoint()) +
      threeLoop*(12.*traceAdjYuYu - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()) +
      threeLoop*(24.*traceTYdAdjYd + 8.*traceTYeAdjYe - 12.*traceTYuAdjYu -
      2.533333333333333*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664
      *MassG*Sqr(g3))*(Yu*(TYd).adjoint()*Yd*Yu.adjoint()) + threeLoop*(
      2.533333333333333*Sqr(g1) + 18.*Sqr(g2))*(Yu*(TYd).adjoint()*TYd*
      Yu.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_5 = ((threeLoop*(24.*
      traceAdjYdYd + 8.*traceAdjYeYe - 12.*traceAdjYuYu + 42.666666666666664*
      Sqr(g3))*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()) + threeLoop*(12.*
      traceTYuAdjYu + 0.6666666666666666*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) -
      42.666666666666664*MassG*Sqr(g3))*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()) +
      threeLoop*(12.*traceAdjYuYu - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()) +
      threeLoop*(24.*traceAdjTYdYd + 8.*traceAdjTYeYe - 12.*traceAdjTYuYu -
      2.533333333333333*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664
      *MassG*Sqr(g3))*(TYu*Yd.adjoint()*Yd*Yu.adjoint()) + threeLoop*(24.*
      traceAdjYdYd + 8.*traceAdjYeYe - 12.*traceAdjYuYu + 2.533333333333333*Sqr
      (g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(TYu*Yd.adjoint()*Yd*(
      TYu).adjoint()) + threeLoop*(12.*traceAdjTYuYu + 0.6666666666666666*MassB
      *Sqr(g1) - 18.*MassWB*Sqr(g2) - 42.666666666666664*MassG*Sqr(g3))*(TYu*
      Yu.adjoint()*Yu*Yu.adjoint()) + threeLoop*(12.*traceAdjYuYu -
      0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      TYu*Yu.adjoint()*Yu*(TYu).adjoint()) + threeLoop*(24.*traceAdjYdYd + 8.*
      traceAdjYeYe - 12.*traceAdjYuYu + 2.533333333333333*Sqr(g1) + 18.*Sqr(g2)
      + 42.666666666666664*Sqr(g3))*(TYu*(TYd).adjoint()*Yd*Yu.adjoint()) +
      threeLoop*(12.*traceAdjYuYu - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe - 6.*traceAdjYuYu +
      1.2666666666666666*Sqr(g1) + 9.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(
      mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()) + threeLoop*(6.*traceAdjYuYu -
      0.3333333333333333*Sqr(g1) + 9.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(
      mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()) + threeLoop*(24.*traceAdjYdYd + 8.*
      traceAdjYeYe - 12.*traceAdjYuYu + 2.533333333333333*Sqr(g1) + 18.*Sqr(g2)
      + 42.666666666666664*Sqr(g3))*(Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()) +
      threeLoop*(12.*traceAdjYuYu - 0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) +
      42.666666666666664*Sqr(g3))*(Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()) +
      threeLoop*(24.*traceAdjYdYd + 8.*traceAdjYeYe - 12.*traceAdjYuYu +
      2.533333333333333*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(Yu
      *Yd.adjoint()*md2*Yd*Yu.adjoint()) + threeLoop*(24.*traceAdjYdYd + 8.*
      traceAdjYeYe - 12.*traceAdjYuYu + 2.533333333333333*Sqr(g1) + 18.*Sqr(g2)
      + 42.666666666666664*Sqr(g3))*(Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()) +
      threeLoop*(Sqr(g1)*(7.199999999999999*mHd2 + 7.199999999999999*mHu2 +
      14.399999999999999*Sqr(MassB)) + Sqr(g2)*(-36.*mHd2 - 36.*mHu2 - 72.*Sqr(
      MassWB)))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*1.2020569031595942) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe - 6.*traceAdjYuYu +
      1.2666666666666666*Sqr(g1) + 9.*Sqr(g2) + 21.333333333333332*Sqr(g3))*(Yu
      *Yd.adjoint()*Yd*Yu.adjoint()*mu2) + threeLoop*(-7.199999999999999*MassB*
      Sqr(g1) + 36.*MassWB*Sqr(g2))*(Yu*Yd.adjoint()*Yd*(TYu).adjoint()*
      1.2020569031595942) + threeLoop*(-7.199999999999999*MassB*Sqr(g1) + 36.*
      MassWB*Sqr(g2))*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*1.2020569031595942) +
      threeLoop*(7.199999999999999*Sqr(g1) - 36.*Sqr(g2))*(Yu*Yd.adjoint()*TYd*
      (TYu).adjoint()*1.2020569031595942) + threeLoop*(12.*traceAdjYuYu -
      0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()) + threeLoop*(12.*traceAdjYuYu -
      0.6666666666666666*Sqr(g1) + 18.*Sqr(g2) + 42.666666666666664*Sqr(g3))*(
      Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_6 = ((threeLoop*(Sqr(g1)*(24.
      *mHu2 + 24.*Sqr(MassB)) + Sqr(g2)*(-72.*mHu2 - 72.*Sqr(MassWB)))*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(6.*
      traceAdjYuYu - 0.3333333333333333*Sqr(g1) + 9.*Sqr(g2) +
      21.333333333333332*Sqr(g3))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2) +
      threeLoop*(-12.*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(Yu*Yu.adjoint()*Yu*(
      TYu).adjoint()*1.2020569031595942) + threeLoop*(-12.*MassB*Sqr(g1) + 36.*
      MassWB*Sqr(g2))*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*1.2020569031595942) +
      threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*(Yu*Yu.adjoint()*TYu*(TYu).adjoint(
      )*1.2020569031595942) + threeLoop*(-7.199999999999999*MassB*Sqr(g1) + 36.
      *MassWB*Sqr(g2))*(Yu*(TYd).adjoint()*Yd*Yu.adjoint()*1.2020569031595942)
      + threeLoop*(7.199999999999999*Sqr(g1) - 36.*Sqr(g2))*(Yu*(TYd).adjoint()
      *TYd*Yu.adjoint()*1.2020569031595942) + threeLoop*(-12.*MassB*Sqr(g1) +
      36.*MassWB*Sqr(g2))*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()*
      1.2020569031595942) + threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*(Yu*(TYu)
      .adjoint()*TYu*Yu.adjoint()*1.2020569031595942) + threeLoop*(
      -7.199999999999999*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(TYu*Yd.adjoint()*
      Yd*Yu.adjoint()*1.2020569031595942) + threeLoop*(7.199999999999999*Sqr(g1
      ) - 36.*Sqr(g2))*(TYu*Yd.adjoint()*Yd*(TYu).adjoint()*1.2020569031595942)
      + threeLoop*(-12.*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(TYu*Yu.adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2
      ))*(TYu*Yu.adjoint()*Yu*(TYu).adjoint()*1.2020569031595942) + threeLoop*(
      7.199999999999999*Sqr(g1) - 36.*Sqr(g2))*(TYu*(TYd).adjoint()*Yd*
      Yu.adjoint()*1.2020569031595942) + threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*
      (TYu*(TYu).adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(
      3.5999999999999996*Sqr(g1) - 18.*Sqr(g2))*(mu2*Yu*Yd.adjoint()*Yd*
      Yu.adjoint()*1.2020569031595942) + threeLoop*(6.*Sqr(g1) - 18.*Sqr(g2))*(
      mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(
      7.199999999999999*Sqr(g1) - 36.*Sqr(g2))*(Yu*mq2*Yd.adjoint()*Yd*
      Yu.adjoint()*1.2020569031595942) + threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*
      (Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + threeLoop*(
      7.199999999999999*Sqr(g1) - 36.*Sqr(g2))*(Yu*Yd.adjoint()*md2*Yd*
      Yu.adjoint()*1.2020569031595942) + threeLoop*(7.199999999999999*Sqr(g1) -
      36.*Sqr(g2))*(Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()*1.2020569031595942) +
      (24.*mHd2 + 12.*mHu2)*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*(TYu)
      .adjoint()) + threeLoop*(3.5999999999999996*Sqr(g1) - 18.*Sqr(g2))*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*mu2*1.2020569031595942) + (-4.*mHd2 - 8.*
      mHu2)*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*
      threeLoop*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*TYu*(TYu).adjoint()) + 12.*
      threeLoop*(Yu*Yd.adjoint()*Yd*(TYd).adjoint()*TYd*Yu.adjoint()) - 4.*
      threeLoop*(Yu*Yd.adjoint()*Yd*(TYu).adjoint()*TYu*Yu.adjoint()) + 12.*
      threeLoop*(Yu*Yd.adjoint()*TYd*Yd.adjoint()*Yd*(TYu).adjoint()) - 4.*
      threeLoop*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*Yu*(TYu).adjoint()) + 12.*
      threeLoop*(Yu*Yd.adjoint()*TYd*(TYd).adjoint()*Yd*Yu.adjoint()) - 4.*
      threeLoop*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()*Yu*Yu.adjoint()) +
      threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*(Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint(
      )*1.2020569031595942) + threeLoop*(12.*Sqr(g1) - 36.*Sqr(g2))*(Yu*
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*1.2020569031595942) + (-4.*mHd2 - 8.*
      mHu2)*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*TYd*(TYu).adjoint()) +
      threeLoop*(6.*Sqr(g1) - 18.*Sqr(g2))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2
      *1.2020569031595942) + 36.*mHu2*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint(
      )*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*(
      TYu).adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*Yu*(TYd).adjoint()*TYd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*(TYu).adjoint()*TYu*
      Yu.adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*TYu*Yd.adjoint()*Yd*(TYu)
      .adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*(TYu)
      .adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*TYu*(TYd).adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()*Yu*
      Yu.adjoint()) + 12.*threeLoop*(Yu*(TYd).adjoint()*Yd*Yd.adjoint()*TYd*
      Yu.adjoint()) - 4.*threeLoop*(Yu*(TYd).adjoint()*Yd*Yu.adjoint()*TYu*
      Yu.adjoint()) + 12.*threeLoop*(Yu*(TYd).adjoint()*TYd*Yd.adjoint()*Yd*
      Yu.adjoint()) - 4.*threeLoop*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()*Yu*
      Yu.adjoint()) - 4.*threeLoop*(Yu*(TYu).adjoint()*Yu*Yd.adjoint()*TYd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()*TYu*
      Yu.adjoint()) - 4.*threeLoop*(Yu*(TYu).adjoint()*TYu*Yd.adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()*Yu*
      Yu.adjoint()) + 12.*threeLoop*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*(TYu)
      .adjoint()) - 4.*threeLoop*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*(TYu)
      .adjoint()) + 12.*threeLoop*(TYu*Yd.adjoint()*Yd*(TYd).adjoint()*Yd*
      Yu.adjoint()) - 4.*threeLoop*(TYu*Yd.adjoint()*Yd*(TYu).adjoint()*Yu*
      Yu.adjoint()) - 4.*threeLoop*(TYu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*(TYu)
      .adjoint()) + 12.*threeLoop*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYu)
      .adjoint()) - 4.*threeLoop*(TYu*Yu.adjoint()*Yu*(TYd).adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(TYu*Yu.adjoint()*Yu*(TYu).adjoint()*Yu*
      Yu.adjoint()) + 12.*threeLoop*(TYu*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*
      Yu.adjoint()) - 4.*threeLoop*(TYu*(TYd).adjoint()*Yd*Yu.adjoint()*Yu*
      Yu.adjoint()) - 4.*threeLoop*(TYu*(TYu).adjoint()*Yu*Yd.adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()*Yu*
      Yu.adjoint()) + 6.*threeLoop*(mu2*Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yu.adjoint()) - 2.*threeLoop*(mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*
      Yu.adjoint()) - 2.*threeLoop*(mu2*Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*
      Yu.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_7 = ((6.*threeLoop*(mu2*Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*mq2*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*mq2*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*mq2*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*mq2*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*Yu.adjoint()) + 6.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()*mu2) - 4.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*mu2*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*mq2*Yu.adjoint()) - 2.*threeLoop*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()*mu2) - 4.*threeLoop*(Yu*
      Yu.adjoint()*mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yu.adjoint()*Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yd.adjoint()*md2*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()) - 2.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*mu2) + 12.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()) + 72.*mHu2*threeLoop*(
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 6.*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2) + 24.*
      threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*(TYu).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*Yu*(TYu).adjoint()*
      TYu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*TYu
      *Yu.adjoint()*Yu*(TYu).adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*
      Yu.adjoint()*TYu*(TYu).adjoint()*Yu*Yu.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()*TYu*Yu.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*(TYu).adjoint()*1.2020569031595942) + 24.*threeLoop*(TYu*
      Yu.adjoint()*Yu*(TYu).adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 24.
      *threeLoop*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*
      1.2020569031595942) + 12.*threeLoop*(mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*mq2*Yu.adjoint()*
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*
      Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*1.2020569031595942) + 12.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2*1.2020569031595942))*
      UNITMATRIX(3)).real();

   beta_mu2 = beta_mu2_1 + beta_mu2_2 + beta_mu2_3 + beta_mu2_4 +
      beta_mu2_5 + beta_mu2_6 + beta_mu2_7;


   return beta_mu2;
}

} // namespace flexiblesusy
