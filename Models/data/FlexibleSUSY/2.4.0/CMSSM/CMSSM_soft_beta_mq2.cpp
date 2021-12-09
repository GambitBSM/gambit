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

// File generated at Thu 10 Oct 2019 17:27:37

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
 * Calculates the 1-loop beta function of mq2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mq2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = (oneOver16PiSqr*(2*mHd2*(Yd.adjoint()*Yd) + 2*mHu2*(Yu.adjoint()*
      Yu) + 2*((TYd).adjoint()*TYd) + 2*((TYu).adjoint()*TYu) + mq2*Yd.adjoint(
      )*Yd + mq2*Yu.adjoint()*Yu + 2*(Yd.adjoint()*md2*Yd) + Yd.adjoint()*Yd*
      mq2 + 2*(Yu.adjoint()*mu2*Yu) + Yu.adjoint()*Yu*mq2 + 0.06666666666666667
      *(3.872983346207417*g1*Tr11 - 2*AbsSqr(MassB)*Sqr(g1) - 90*AbsSqr(MassWB)
      *Sqr(g2) - 160*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_mq2;
}

/**
 * Calculates the 2-loop beta function of mq2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mq2_2_loop(const Soft_traces& soft_traces) const
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

   beta_mq2 = (twoLoop*(0.4*(-15*traceconjTYdTpTYd - 5*traceconjTYeTpTYe - 15*
      tracemd2YdAdjYd - 5*traceme2YeAdjYe - 5*traceml2AdjYeYe - 15*
      tracemq2AdjYdYd - 30*mHd2*traceYdAdjYd - 10*mHd2*traceYeAdjYe + 2*mHd2*
      Sqr(g1) + 4*AbsSqr(MassB)*Sqr(g1))*(Yd.adjoint()*Yd) - 0.4*(15*
      traceconjTYdTpYd + 5*traceconjTYeTpYe + 2*Conj(MassB)*Sqr(g1))*(Yd.
      adjoint()*TYd) + 0.4*(-15*traceconjTYuTpTYu - 15*tracemq2AdjYuYu - 15*
      tracemu2YuAdjYu - 30*mHu2*traceYuAdjYu + 4*mHu2*Sqr(g1) + 8*AbsSqr(MassB)
      *Sqr(g1))*(Yu.adjoint()*Yu) - 0.4*(15*traceconjTYuTpYu + 4*Conj(MassB)*
      Sqr(g1))*(Yu.adjoint()*TYu) - 0.4*(15*traceAdjYdTYd + 5*traceAdjYeTYe + 2
      *MassB*Sqr(g1))*((TYd).adjoint()*Yd) + 0.4*(-15*traceYdAdjYd - 5*
      traceYeAdjYe + 2*Sqr(g1))*((TYd).adjoint()*TYd) - 0.4*(15*traceAdjYuTYu +
      4*MassB*Sqr(g1))*((TYu).adjoint()*Yu) + 0.4*(-15*traceYuAdjYu + 4*Sqr(g1)
      )*((TYu).adjoint()*TYu) + 0.2*(-15*traceYdAdjYd - 5*traceYeAdjYe + 2*Sqr(
      g1))*(mq2*Yd.adjoint()*Yd) + 0.2*(-15*traceYuAdjYu + 4*Sqr(g1))*(mq2*Yu.
      adjoint()*Yu) + 0.4*(-15*traceYdAdjYd - 5*traceYeAdjYe + 2*Sqr(g1))*(Yd.
      adjoint()*md2*Yd) + 0.2*(-15*traceYdAdjYd - 5*traceYeAdjYe + 2*Sqr(g1))*(
      Yd.adjoint()*Yd*mq2) + 0.4*(-15*traceYuAdjYu + 4*Sqr(g1))*(Yu.adjoint()*
      mu2*Yu) + 0.2*(-15*traceYuAdjYu + 4*Sqr(g1))*(Yu.adjoint()*Yu*mq2) - 8*
      mHd2*(Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 4*(Yd.adjoint()*Yd*(TYd).adjoint
      ()*TYd) - 4*(Yd.adjoint()*TYd*(TYd).adjoint()*Yd) - 8*mHu2*(Yu.adjoint()*
      Yu*Yu.adjoint()*Yu) - 4*(Yu.adjoint()*Yu*(TYu).adjoint()*TYu) - 4*(Yu.
      adjoint()*TYu*(TYu).adjoint()*Yu) - 4*((TYd).adjoint()*Yd*Yd.adjoint()*
      TYd) - 4*((TYd).adjoint()*TYd*Yd.adjoint()*Yd) - 4*((TYu).adjoint()*Yu*Yu
      .adjoint()*TYu) - 4*((TYu).adjoint()*TYu*Yu.adjoint()*Yu) - 2*(mq2*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd) - 2*(mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu) -
      4*(Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd) - 4*(Yd.adjoint()*Yd*mq2*Yd.
      adjoint()*Yd) - 4*(Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd) - 2*(Yd.adjoint()
      *Yd*Yd.adjoint()*Yd*mq2) - 4*(Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu) - 4*(
      Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu) - 4*(Yu.adjoint()*Yu*Yu.adjoint()*
      mu2*Yu) - 2*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2) + 0.0044444444444444444
      *(232.379000772445*g1*Tr31 + 597*AbsSqr(MassB)*Quad(g1) + 1350*Tr22*Quad(
      g2) + 7425*AbsSqr(MassWB)*Quad(g2) + 2400*Tr23*Quad(g3) - 9600*AbsSqr(
      MassG)*Quad(g3) + 30*Tr2U111*Sqr(g1) + 90*AbsSqr(MassB)*Sqr(g1)*Sqr(g2) +
      90*AbsSqr(MassWB)*Sqr(g1)*Sqr(g2) + 45*MassWB*Conj(MassB)*Sqr(g1)*Sqr(g2)
      + 45*MassB*Conj(MassWB)*Sqr(g1)*Sqr(g2) + 160*AbsSqr(MassB)*Sqr(g1)*Sqr(
      g3) + 160*AbsSqr(MassG)*Sqr(g1)*Sqr(g3) + 80*MassG*Conj(MassB)*Sqr(g1)*
      Sqr(g3) + 80*MassB*Conj(MassG)*Sqr(g1)*Sqr(g3) + 7200*AbsSqr(MassG)*Sqr(
      g2)*Sqr(g3) + 7200*AbsSqr(MassWB)*Sqr(g2)*Sqr(g3) + 3600*MassWB*Conj(
      MassG)*Sqr(g2)*Sqr(g3) + 3600*MassG*Conj(MassWB)*Sqr(g2)*Sqr(g3))*
      UNITMATRIX(3))).real();


   return beta_mq2;
}

/**
 * Calculates the 3-loop beta function of mq2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mq2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYdTYdAdjTYdYd = TRACE_STRUCT.traceAdjYdTYdAdjTYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjTYeYe = TRACE_STRUCT.traceAdjYeYeAdjTYeYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYeTYeAdjTYeYe = TRACE_STRUCT.traceAdjYeTYeAdjTYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjYuYuAdjTYuYu = TRACE_STRUCT.traceAdjYuYuAdjTYuYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjTYdYd = TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYu = TRACE_STRUCT.traceAdjYuTYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYdYd = TRACE_STRUCT.traceAdjTYdTYdAdjYdYd;
   const double traceAdjTYdTYdAdjYuYu = TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYeTYeAdjYeYe = TRACE_STRUCT.traceAdjTYeTYeAdjYeYe;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjTYuTYuAdjYdYd = TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceAdjTYuTYuAdjYuYu = TRACE_STRUCT.traceAdjTYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceTYdAdjTYuYuAdjYd = TRACE_STRUCT.traceTYdAdjTYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdmd2 = TRACE_STRUCT.traceYdAdjYdYdAdjYdmd2;
   const double traceYdAdjYuYuAdjYdmd2 = TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2;
   const double traceYeAdjYeYeAdjYeme2 = TRACE_STRUCT.traceYeAdjYeYeAdjYeme2;
   const double traceYuAdjYdYdAdjYumu2 = TRACE_STRUCT.traceYuAdjYdYdAdjYumu2;
   const double traceYuAdjYuYuAdjYumu2 = TRACE_STRUCT.traceYuAdjYuYuAdjYumu2;
   const double traceAdjYdYdAdjYdYdmq2 = TRACE_STRUCT.traceAdjYdYdAdjYdYdmq2;
   const double traceAdjYdYdAdjYuYumq2 = TRACE_STRUCT.traceAdjYdYdAdjYuYumq2;
   const double traceAdjYeYeAdjYeYeml2 = TRACE_STRUCT.traceAdjYeYeAdjYeYeml2;
   const double traceAdjYuYuAdjYdYdmq2 = TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2;
   const double traceAdjYuYuAdjYuYumq2 = TRACE_STRUCT.traceAdjYuYuAdjYuYumq2;


   Eigen::Matrix<double,3,3> beta_mq2;

   const Eigen::Matrix<double,3,3> beta_mq2_1 = (28.156793810928004*threeLoop*(
      -0.01884684279858271*mHd2*Power6(g1) - 0.01884684279858271*mHu2*Power6(g1
      ) - 0.012564561865721807*tracemd2*Power6(g1) - 0.03769368559716542*
      traceme2*Power6(g1) - 0.01884684279858271*traceml2*Power6(g1) -
      0.0062822809328609034*tracemq2*Power6(g1) - 0.05025824746288723*tracemu2*
      Power6(g1) - 0.10654622185128416*mHd2*Power6(g2) - 0.10654622185128416*
      mHu2*Power6(g2) - 0.10654622185128416*traceml2*Power6(g2) -
      0.3196386655538525*tracemq2*Power6(g2) + 1.2627700367559604*tracemd2*
      Power6(g3) + 2.525540073511921*tracemq2*Power6(g3) + 0.033147713464843964
      *MassB*traceAdjTYdYd*Quad(g1) + 0.04261848874051366*MassB*traceAdjTYeYe*
      Quad(g1) + 0.06156003929185307*MassB*traceAdjTYuYu*Quad(g1) -
      0.01988862807890638*mHd2*traceAdjYdYd*Quad(g1) - 0.01988862807890638*
      traceAdjYdYdmq2*Quad(g1) - 0.0255710932443082*mHd2*traceAdjYeYe*Quad(g1)
      - 0.0255710932443082*traceAdjYeYeml2*Quad(g1) - 0.036936023575111845*mHu2
      *traceAdjYuYu*Quad(g1) - 0.036936023575111845*traceAdjYuYumq2*Quad(g1) +
      3.1963866555385247*MassWB*traceAdjTYdYd*Quad(g2) + 1.0654622185128417*
      MassWB*traceAdjTYeYe*Quad(g2) + 3.1963866555385247*MassWB*traceAdjTYuYu*
      Quad(g2) - 1.917831993323115*mHd2*traceAdjYdYd*Quad(g2) -
      1.917831993323115*traceAdjYdYdmq2*Quad(g2) - 0.639277331107705*mHd2*
      traceAdjYeYe*Quad(g2) - 0.639277331107705*traceAdjYeYeml2*Quad(g2) -
      1.917831993323115*mHu2*traceAdjYuYu*Quad(g2) - 1.917831993323115*
      traceAdjYuYumq2*Quad(g2) + 3.7883101102678816*MassG*traceAdjTYdYd*Quad(g3
      ) + 3.7883101102678816*MassG*traceAdjTYuYu*Quad(g3) - 2.272986066160729*
      mHd2*traceAdjYdYd*Quad(g3) - 2.272986066160729*traceAdjYdYdmq2*Quad(g3) -
      2.272986066160729*mHu2*traceAdjYuYu*Quad(g3) - 2.272986066160729*
      traceAdjYuYumq2*Quad(g3) - 0.9906414598211808*MassB*MassWB*Quad(g2)*Sqr(
      g1) - 0.007103081456752278*mHd2*Quad(g2)*Sqr(g1) - 0.007103081456752278*
      mHu2*Quad(g2)*Sqr(g1) - 0.007103081456752278*traceml2*Quad(g2)*Sqr(g1) -
      0.02130924437025683*tracemq2*Quad(g2)*Sqr(g1) - 2.1721479898128444*MassB*
      MassG*Quad(g3)*Sqr(g1) - 0.012627700367559605*tracemd2*Quad(g3)*Sqr(g1) -
      0.02525540073511921*tracemq2*Quad(g3)*Sqr(g1) - 0.012627700367559605*
      tracemu2*Quad(g3)*Sqr(g1) - 0.15317389652424002*MassB*MassWB*Quad(g1)*Sqr
      (g2) - 0.004261848874051366*mHd2*Quad(g1)*Sqr(g2) - 0.004261848874051366*
      mHu2*Quad(g1)*Sqr(g2) - 0.002841232582700911*tracemd2*Quad(g1)*Sqr(g2) -
      0.008523697748102733*traceme2*Quad(g1)*Sqr(g2) - 0.004261848874051366*
      traceml2*Quad(g1)*Sqr(g2) - 0.0014206162913504555*tracemq2*Quad(g1)*Sqr(
      g2) - 0.011364930330803644*tracemu2*Quad(g1)*Sqr(g2) - 22.31734125836594*
      MassG*MassWB*Quad(g3)*Sqr(g2) - 0.5682465165401822*tracemd2*Quad(g3)*Sqr(
      g2) - 1.1364930330803644*tracemq2*Quad(g3)*Sqr(g2) - 0.5682465165401822*
      tracemu2*Quad(g3)*Sqr(g2) - 0.35611950302443995*MassB*MassG*Quad(g1)*Sqr(
      g3) - 0.007576620220535763*mHd2*Quad(g1)*Sqr(g3) - 0.007576620220535763*
      mHu2*Quad(g1)*Sqr(g3) - 0.005051080147023842*tracemd2*Quad(g1)*Sqr(g3) -
      0.015153240441071527*traceme2*Quad(g1)*Sqr(g3) - 0.007576620220535763*
      traceml2*Quad(g1)*Sqr(g3) - 0.002525540073511921*tracemq2*Quad(g1)*Sqr(g3
      ) - 0.02020432058809537*tracemu2*Quad(g1)*Sqr(g3) - 22.679328073285447*
      MassG*MassWB*Quad(g2)*Sqr(g3) - 0.5682465165401822*mHd2*Quad(g2)*Sqr(g3)
      - 0.5682465165401822*mHu2*Quad(g2)*Sqr(g3) - 0.5682465165401822*traceml2*
      Quad(g2)*Sqr(g3) - 1.7047395496205466*tracemq2*Quad(g2)*Sqr(g3) -
      0.2272986066160729*MassB*MassG*Sqr(g1)*Sqr(g2)*Sqr(g3) -
      0.2272986066160729*MassB*MassWB*Sqr(g1)*Sqr(g2)*Sqr(g3) -
      0.2272986066160729*MassG*MassWB*Sqr(g1)*Sqr(g2)*Sqr(g3) + 1.*Power6(g1)*
      Sqr(MassB) - 0.09944314039453188*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.127855466221541*traceAdjYeYe*Quad(g1)*Sqr(MassB) - 0.1846801178755592*
      traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.3035375305782789*Quad(g2)*Sqr(g1)*
      Sqr(MassB) - 0.6693598827769556*Quad(g3)*Sqr(g1)*Sqr(MassB) -
      0.22976084478636*Quad(g1)*Sqr(g2)*Sqr(MassB) - 0.53417925453666*Quad(g1)*
      Sqr(g3)*Sqr(MassB) - 0.2272986066160729*Sqr(g1)*Sqr(g2)*Sqr(g3)*Sqr(MassB
      ) + 408.81459034974597*Power6(g3)*Sqr(MassG) - 11.364930330803643*
      traceAdjYdYd*Quad(g3)*Sqr(MassG) - 11.364930330803643*traceAdjYuYu*Quad(
      g3)*Sqr(MassG) - 3.1824557825139066*Quad(g3)*Sqr(g1)*Sqr(MassG) -
      30.066532788307818*Quad(g3)*Sqr(g2)*Sqr(MassG) - 0.1363883402992733*Quad(
      g1)*Sqr(g3)*Sqr(MassG) - 8.782554712211905*Quad(g2)*Sqr(g3)*Sqr(MassG) -
      0.2272986066160729*Sqr(g1)*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      237.98075657827957*Power6(g2)*Sqr(MassWB) - 9.589159966615574*
      traceAdjYdYd*Quad(g2)*Sqr(MassWB) - 3.1963866555385247*traceAdjYeYe*Quad(
      g2)*Sqr(MassWB) - 9.589159966615574*traceAdjYuYu*Quad(g2)*Sqr(MassWB) -
      1.4575498639047624*Quad(g2)*Sqr(g1)*Sqr(MassWB) - 0.06380140163996591*
      Quad(g1)*Sqr(g2)*Sqr(MassWB) - 9.453931079562423*Quad(g3)*Sqr(g2)*Sqr(
      MassWB) - 31.746006043767444*Quad(g2)*Sqr(g3)*Sqr(MassWB) -
      0.2272986066160729*Sqr(g1)*Sqr(g2)*Sqr(g3)*Sqr(MassWB))*UNITMATRIX(3)).
      real();
   const Eigen::Matrix<double,3,3> beta_mq2_2 = ((35.55555555555556*threeLoop*(
      1.*tracemu2*Power6(g3) - 0.01575*traceTYdAdjTYd*Quad(g1) + 0.02625*MassB*
      traceTYdAdjYd*Quad(g1) - 0.020249999999999997*traceTYeAdjTYe*Quad(g1) +
      0.033749999999999995*MassB*traceTYeAdjYe*Quad(g1) - 0.029249999999999998*
      traceTYuAdjTYu*Quad(g1) + 0.04875*MassB*traceTYuAdjYu*Quad(g1) - 0.01575*
      traceYdAdjYdmd2*Quad(g1) - 0.020249999999999997*traceYeAdjYeme2*Quad(g1)
      - 0.029249999999999998*traceYuAdjYumu2*Quad(g1) - 1.5187499999999998*
      traceTYdAdjTYd*Quad(g2) + 2.53125*MassWB*traceTYdAdjYd*Quad(g2) - 0.50625
      *traceTYeAdjTYe*Quad(g2) + 0.8437500000000001*MassWB*traceTYeAdjYe*Quad(
      g2) - 1.5187499999999998*traceTYuAdjTYu*Quad(g2) + 2.53125*MassWB*
      traceTYuAdjYu*Quad(g2) - 1.5187499999999998*traceYdAdjYdmd2*Quad(g2) -
      0.50625*traceYeAdjYeme2*Quad(g2) - 1.5187499999999998*traceYuAdjYumu2*
      Quad(g2) - 1.7999999999999998*traceTYdAdjTYd*Quad(g3) + 3.*MassG*
      traceTYdAdjYd*Quad(g3) - 1.7999999999999998*traceTYuAdjTYu*Quad(g3) + 3.*
      MassG*traceTYuAdjYu*Quad(g3) - 1.7999999999999998*traceYdAdjYdmd2*Quad(g3
      ) - 1.7999999999999998*traceYuAdjYumu2*Quad(g3)) - 75.96*threeLoop*(-
      0.9478672985781992*traceAdjTYdTYdAdjYdYd - 0.1579778830963665*
      traceAdjTYdTYdAdjYuYu - 0.315955766192733*traceAdjTYeTYeAdjYeYe -
      0.1579778830963665*traceAdjTYuTYuAdjYdYd - 0.9478672985781992*
      traceAdjYdTYdAdjTYdYd - 1.4218009478672986*mHd2*traceAdjYdYdAdjYdYd -
      0.9478672985781992*traceAdjYdYdAdjYdYdmq2 - 0.1579778830963665*
      traceAdjYdYdAdjYuYumq2 + 0.4739336492890996*traceAdjYdYd*traceAdjYdYdmq2
      - 0.315955766192733*traceAdjYeTYeAdjTYeYe + 0.4739336492890996*mHd2*
      traceAdjYdYd*traceAdjYeYe + 0.1579778830963665*traceAdjYdYdmq2*
      traceAdjYeYe - 0.4739336492890996*mHd2*traceAdjYeYeAdjYeYe -
      0.315955766192733*traceAdjYeYeAdjYeYeml2 + 0.1579778830963665*
      traceAdjYdYd*traceAdjYeYeml2 + 0.05265929436545551*traceAdjYeYe*
      traceAdjYeYeml2 - 0.1579778830963665*traceAdjYuTYuAdjTYdYd -
      0.315955766192733*mHd2*traceAdjYuYuAdjYdYd - 0.1579778830963665*mHu2*
      traceAdjYuYuAdjYdYd - 0.1579778830963665*traceAdjYuYuAdjYdYdmq2 +
      0.4739336492890996*traceAdjYdYd*traceTYdAdjTYd + 0.1579778830963665*
      traceAdjYeYe*traceTYdAdjTYd + 0.17298578199052134*mHd2*Quad(g1) +
      0.00631911532385466*mHu2*Quad(g1) + 0.004212743549236441*tracemd2*Quad(g1
      ) + 0.01263823064770932*traceme2*Quad(g1) + 0.00631911532385466*traceml2*
      Quad(g1) + 0.0021063717746182204*tracemq2*Quad(g1) + 0.016850974196945763
      *tracemu2*Quad(g1) + 0.2962085308056872*mHd2*Quad(g2) -
      0.07021239248727401*mHd2*Quad(g3) + 0.08425487098472882*MassB*
      traceAdjTYdYd*Sqr(g1) - 0.04212743549236441*MassB*traceAdjTYeYe*Sqr(g1) -
      0.16850974196945764*mHd2*traceAdjYdYd*Sqr(g1) - 0.08425487098472882*
      traceAdjYdYdmq2*Sqr(g1) + 0.08425487098472882*mHd2*traceAdjYeYe*Sqr(g1) +
      0.04212743549236441*traceAdjYeYeml2*Sqr(g1) - 0.08425487098472882*
      traceTYdAdjTYd*Sqr(g1) + 0.4739336492890996*MassWB*traceAdjTYdYd*Sqr(g2)
      + 0.1579778830963665*MassWB*traceAdjTYeYe*Sqr(g2) - 0.9478672985781992*
      mHd2*traceAdjYdYd*Sqr(g2) - 0.4739336492890996*traceAdjYdYdmq2*Sqr(g2) -
      0.315955766192733*mHd2*traceAdjYeYe*Sqr(g2) - 0.1579778830963665*
      traceAdjYeYeml2*Sqr(g2) - 0.4739336492890996*traceTYdAdjTYd*Sqr(g2) +
      0.21590310689836756*MassB*MassWB*Sqr(g1)*Sqr(g2) + 0.10795155344918378*
      mHd2*Sqr(g1)*Sqr(g2) - 0.21063717746182203*MassG*traceAdjTYdYd*Sqr(g3) +
      0.21063717746182203*MassG*traceAdjTYeYe*Sqr(g3) + 0.42127435492364407*
      mHd2*traceAdjYdYd*Sqr(g3) + 0.21063717746182203*traceAdjYdYdmq2*Sqr(g3) -
      0.42127435492364407*mHd2*traceAdjYeYe*Sqr(g3) - 0.21063717746182203*
      traceAdjYeYeml2*Sqr(g3) + 0.21063717746182203*traceTYdAdjTYd*Sqr(g3) +
      0.2668070914516412*MassB*MassG*Sqr(g1)*Sqr(g3) + 0.1334035457258206*mHd2*
      Sqr(g1)*Sqr(g3) + 0.21063717746182203*MassG*MassWB*Sqr(g2)*Sqr(g3) +
      0.10531858873091102*mHd2*Sqr(g2)*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) -
      0.16850974196945764*traceAdjYdYd*Sqr(g1)*Sqr(MassB) + 0.08425487098472882
      *traceAdjYeYe*Sqr(g1)*Sqr(MassB) + 0.21590310689836756*Sqr(g1)*Sqr(g2)*
      Sqr(MassB) + 0.2668070914516412*Sqr(g1)*Sqr(g3)*Sqr(MassB) -
      0.42127435492364407*Quad(g3)*Sqr(MassG) + 0.42127435492364407*
      traceAdjYdYd*Sqr(g3)*Sqr(MassG) - 0.42127435492364407*traceAdjYeYe*Sqr(g3
      )*Sqr(MassG) + 0.2668070914516412*Sqr(g1)*Sqr(g3)*Sqr(MassG) +
      0.21063717746182203*Sqr(g2)*Sqr(g3)*Sqr(MassG) + 1.7772511848341235*Quad(
      g2)*Sqr(MassWB) - 0.9478672985781992*traceAdjYdYd*Sqr(g2)*Sqr(MassWB) -
      0.315955766192733*traceAdjYeYe*Sqr(g2)*Sqr(MassWB) + 0.21590310689836756*
      Sqr(g1)*Sqr(g2)*Sqr(MassWB) + 0.21063717746182203*Sqr(g2)*Sqr(g3)*Sqr(
      MassWB) + 0.7109004739336493*mHd2*Sqr(traceAdjYdYd) + 0.07898894154818326
      *mHd2*Sqr(traceAdjYeYe))*(Yd.adjoint()*Yd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_3 = ((12.*threeLoop*(1.*
      traceTYdAdjTYuYuAdjYd - 3.*traceAdjTYdYd*traceTYdAdjYd - 1.*traceAdjTYeYe
      *traceTYdAdjYd - 1.*traceAdjYdYd*traceTYeAdjTYe - 0.3333333333333333*
      traceAdjYeYe*traceTYeAdjTYe - 1.*traceAdjTYdYd*traceTYeAdjYe -
      0.3333333333333333*traceAdjTYeYe*traceTYeAdjYe - 3.*traceAdjYdYd*
      traceYdAdjYdmd2 - 1.*traceAdjYeYe*traceYdAdjYdmd2 + 6.*
      traceYdAdjYdYdAdjYdmd2 + 1.*traceYdAdjYuYuAdjYdmd2 - 1.*traceAdjYdYd*
      traceYeAdjYeme2 - 0.3333333333333333*traceAdjYeYe*traceYeAdjYeme2 + 2.*
      traceYeAdjYeYeAdjYeme2 + 1.*traceYuAdjYdYdAdjYumu2 - 0.5333333333333333*
      MassB*traceTYdAdjYd*Sqr(g1) - 0.26666666666666666*traceTYeAdjTYe*Sqr(g1)
      + 0.26666666666666666*MassB*traceTYeAdjYe*Sqr(g1) + 0.5333333333333333*
      traceYdAdjYdmd2*Sqr(g1) - 0.26666666666666666*traceYeAdjYeme2*Sqr(g1) -
      3.*MassWB*traceTYdAdjYd*Sqr(g2) + 1.*traceTYeAdjTYe*Sqr(g2) - 1.*MassWB*
      traceTYeAdjYe*Sqr(g2) + 3.*traceYdAdjYdmd2*Sqr(g2) + 1.*traceYeAdjYeme2*
      Sqr(g2) + 1.3333333333333333*MassG*traceTYdAdjYd*Sqr(g3) +
      1.3333333333333333*traceTYeAdjTYe*Sqr(g3) - 1.3333333333333333*MassG*
      traceTYeAdjYe*Sqr(g3) - 1.3333333333333333*traceYdAdjYdmd2*Sqr(g3) +
      1.3333333333333333*traceYeAdjYeme2*Sqr(g3))*(Yd.adjoint()*Yd) + 25.32*
      threeLoop*(0.47393364928909953*traceAdjTYuYuAdjYdYd - 1.4218009478672986*
      traceAdjTYdYd*traceAdjYdYd - 0.47393364928909953*traceAdjTYeYe*
      traceAdjYdYd + 2.843601895734597*traceAdjYdYdAdjTYdYd -
      0.47393364928909953*traceAdjTYdYd*traceAdjYeYe - 0.1579778830963665*
      traceAdjTYeYe*traceAdjYeYe + 0.9478672985781991*traceAdjYeYeAdjTYeYe +
      0.47393364928909953*traceAdjYuYuAdjTYdYd + 1.*MassB*Quad(g1) +
      1.7772511848341233*MassWB*Quad(g2) - 0.421274354923644*MassG*Quad(g3) +
      0.25276461295418645*traceAdjTYdYd*Sqr(g1) - 0.12638230647709323*
      traceAdjTYeYe*Sqr(g1) - 0.25276461295418645*MassB*traceAdjYdYd*Sqr(g1) +
      0.12638230647709323*MassB*traceAdjYeYe*Sqr(g1) + 1.4218009478672986*
      traceAdjTYdYd*Sqr(g2) + 0.47393364928909953*traceAdjTYeYe*Sqr(g2) -
      1.4218009478672986*MassWB*traceAdjYdYd*Sqr(g2) - 0.47393364928909953*
      MassWB*traceAdjYeYe*Sqr(g2) + 0.32385466034755134*MassB*Sqr(g1)*Sqr(g2) +
      0.32385466034755134*MassWB*Sqr(g1)*Sqr(g2) - 0.631911532385466*
      traceAdjTYdYd*Sqr(g3) + 0.631911532385466*traceAdjTYeYe*Sqr(g3) +
      0.631911532385466*MassG*traceAdjYdYd*Sqr(g3) - 0.631911532385466*MassG*
      traceAdjYeYe*Sqr(g3) + 0.4002106371774618*MassB*Sqr(g1)*Sqr(g3) +
      0.4002106371774618*MassG*Sqr(g1)*Sqr(g3) + 0.315955766192733*MassG*Sqr(g2
      )*Sqr(g3) + 0.315955766192733*MassWB*Sqr(g2)*Sqr(g3))*(Yd.adjoint()*TYd)
      - 150.68*threeLoop*(-0.07963897000265463*traceAdjTYdTYdAdjYuYu -
      0.07963897000265463*traceAdjTYuTYuAdjYdYd - 0.4778338200159278*
      traceAdjTYuTYuAdjYuYu - 0.07963897000265463*traceAdjYdYdAdjYuYumq2 -
      0.07963897000265463*traceAdjYuTYuAdjTYdYd - 0.4778338200159278*
      traceAdjYuTYuAdjTYuYu - 0.07963897000265463*mHd2*traceAdjYuYuAdjYdYd -
      0.15927794000530926*mHu2*traceAdjYuYuAdjYdYd - 0.07963897000265463*
      traceAdjYuYuAdjYdYdmq2 - 0.7167507300238917*mHu2*traceAdjYuYuAdjYuYu -
      0.4778338200159278*traceAdjYuYuAdjYuYumq2 + 0.00637111760021237*mHd2*Quad
      (g1) + 0.17303778426687905*mHu2*Quad(g1) + 0.14932306875497742*mHu2*Quad(
      g2) - 0.035395097778957614*mHu2*Quad(g3) + 0.02654632333421821*MassB*
      traceAdjTYuYu*Sqr(g1) - 0.05309264666843642*mHu2*traceAdjYuYu*Sqr(g1) -
      0.02654632333421821*traceAdjYuYumq2*Sqr(g1) + 0.2389169100079639*MassWB*
      traceAdjTYuYu*Sqr(g2) - 0.4778338200159278*mHu2*traceAdjYuYu*Sqr(g2) +
      0.15662330767188745*MassB*MassWB*Sqr(g1)*Sqr(g2) + 0.07831165383594373*
      mHu2*Sqr(g1)*Sqr(g2) - 0.10618529333687284*MassG*traceAdjTYuYu*Sqr(g3) +
      0.21237058667374567*mHu2*traceAdjYuYu*Sqr(g3) + 0.3610299973453676*MassB*
      MassG*Sqr(g1)*Sqr(g3) + 0.1805149986726838*mHu2*Sqr(g1)*Sqr(g3) +
      0.10618529333687284*MassG*MassWB*Sqr(g2)*Sqr(g3) + 0.05309264666843642*
      mHu2*Sqr(g2)*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) - 0.05309264666843642*
      traceAdjYuYu*Sqr(g1)*Sqr(MassB) + 0.15662330767188745*Sqr(g1)*Sqr(g2)*Sqr
      (MassB) + 0.3610299973453676*Sqr(g1)*Sqr(g3)*Sqr(MassB) -
      0.21237058667374567*Quad(g3)*Sqr(MassG) + 0.21237058667374567*
      traceAdjYuYu*Sqr(g3)*Sqr(MassG) + 0.3610299973453676*Sqr(g1)*Sqr(g3)*Sqr(
      MassG) + 0.10618529333687284*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      0.8959384125298646*Quad(g2)*Sqr(MassWB) - 0.4778338200159278*traceAdjYuYu
      *Sqr(g2)*Sqr(MassWB) + 0.15662330767188745*Sqr(g1)*Sqr(g2)*Sqr(MassWB) +
      0.10618529333687284*Sqr(g2)*Sqr(g3)*Sqr(MassWB) + 0.35837536501194583*
      mHu2*Sqr(traceAdjYuYu))*(Yu.adjoint()*Yu))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_4 = ((36.*threeLoop*(-1.*
      traceAdjYuYu*traceAdjYuYumq2 + 0.3333333333333333*traceTYdAdjTYuYuAdjYd -
      1.*traceAdjYuYu*traceTYuAdjTYu - 1.*traceAdjTYuYu*traceTYuAdjYu +
      0.3333333333333333*traceYdAdjYuYuAdjYdmd2 + 0.3333333333333333*
      traceYuAdjYdYdAdjYumu2 - 1.*traceAdjYuYu*traceYuAdjYumu2 + 2.*
      traceYuAdjYuYuAdjYumu2 - 0.01777777777777778*tracemd2*Quad(g1) -
      0.05333333333333333*traceme2*Quad(g1) - 0.026666666666666665*traceml2*
      Quad(g1) - 0.00888888888888889*tracemq2*Quad(g1) - 0.07111111111111112*
      tracemu2*Quad(g1) + 0.1111111111111111*traceTYuAdjTYu*Sqr(g1) -
      0.1111111111111111*MassB*traceTYuAdjYu*Sqr(g1) + 0.1111111111111111*
      traceYuAdjYumu2*Sqr(g1) + 1.*traceAdjYuYumq2*Sqr(g2) + 1.*traceTYuAdjTYu*
      Sqr(g2) - 1.*MassWB*traceTYuAdjYu*Sqr(g2) + 1.*traceYuAdjYumu2*Sqr(g2) -
      0.4444444444444444*traceAdjYuYumq2*Sqr(g3) - 0.4444444444444444*
      traceTYuAdjTYu*Sqr(g3) + 0.4444444444444444*MassG*traceTYuAdjYu*Sqr(g3) -
      0.4444444444444444*traceYuAdjYumu2*Sqr(g3))*(Yu.adjoint()*Yu) +
      50.22666666666667*threeLoop*(0.2389169100079639*traceAdjTYuYuAdjYdYd -
      0.7167507300238917*traceAdjTYuYu*traceAdjYuYu + 0.2389169100079639*
      traceAdjYuYuAdjTYdYd + 1.4335014600477833*traceAdjYuYuAdjTYuYu + 1.*MassB
      *Quad(g1) + 0.8959384125298646*MassWB*Quad(g2) - 0.21237058667374567*
      MassG*Quad(g3) + 0.07963897000265463*traceAdjTYuYu*Sqr(g1) -
      0.07963897000265463*MassB*traceAdjYuYu*Sqr(g1) + 0.7167507300238917*
      traceAdjTYuYu*Sqr(g2) - 0.7167507300238917*MassWB*traceAdjYuYu*Sqr(g2) +
      0.2349349615078312*MassB*Sqr(g1)*Sqr(g2) + 0.2349349615078312*MassWB*Sqr(
      g1)*Sqr(g2) - 0.3185558800106185*traceAdjTYuYu*Sqr(g3) +
      0.3185558800106185*MassG*traceAdjYuYu*Sqr(g3) + 0.5415449960180515*MassB*
      Sqr(g1)*Sqr(g3) + 0.5415449960180515*MassG*Sqr(g1)*Sqr(g3) +
      0.15927794000530926*MassG*Sqr(g2)*Sqr(g3) + 0.15927794000530926*MassWB*
      Sqr(g2)*Sqr(g3))*(Yu.adjoint()*TYu) + 25.32*threeLoop*(2.843601895734597*
      traceAdjYdTYdAdjYdYd + 0.9478672985781991*traceAdjYeTYeAdjYeYe +
      0.47393364928909953*traceAdjYuTYuAdjYdYd - 1.4218009478672986*
      traceAdjYdYd*traceTYdAdjYd - 0.47393364928909953*traceAdjYeYe*
      traceTYdAdjYd + 0.47393364928909953*traceTYdAdjYuYuAdjYd -
      0.47393364928909953*traceAdjYdYd*traceTYeAdjYe - 0.1579778830963665*
      traceAdjYeYe*traceTYeAdjYe + 1.*MassB*Quad(g1) + 1.7772511848341233*
      MassWB*Quad(g2) - 0.421274354923644*MassG*Quad(g3) - 0.25276461295418645*
      MassB*traceAdjYdYd*Sqr(g1) + 0.12638230647709323*MassB*traceAdjYeYe*Sqr(
      g1) + 0.25276461295418645*traceTYdAdjYd*Sqr(g1) - 0.12638230647709323*
      traceTYeAdjYe*Sqr(g1) - 1.4218009478672986*MassWB*traceAdjYdYd*Sqr(g2) -
      0.47393364928909953*MassWB*traceAdjYeYe*Sqr(g2) + 1.4218009478672986*
      traceTYdAdjYd*Sqr(g2) + 0.47393364928909953*traceTYeAdjYe*Sqr(g2) +
      0.32385466034755134*MassB*Sqr(g1)*Sqr(g2) + 0.32385466034755134*MassWB*
      Sqr(g1)*Sqr(g2) + 0.631911532385466*MassG*traceAdjYdYd*Sqr(g3) -
      0.631911532385466*MassG*traceAdjYeYe*Sqr(g3) - 0.631911532385466*
      traceTYdAdjYd*Sqr(g3) + 0.631911532385466*traceTYeAdjYe*Sqr(g3) +
      0.4002106371774618*MassB*Sqr(g1)*Sqr(g3) + 0.4002106371774618*MassG*Sqr(
      g1)*Sqr(g3) + 0.315955766192733*MassG*Sqr(g2)*Sqr(g3) + 0.315955766192733
      *MassWB*Sqr(g2)*Sqr(g3))*((TYd).adjoint()*Yd) - 12.66*threeLoop*(-
      2.843601895734597*traceAdjYdYdAdjYdYd + 0.9478672985781991*traceAdjYdYd*
      traceAdjYeYe - 0.9478672985781991*traceAdjYeYeAdjYeYe -
      0.9478672985781991*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.7772511848341233
      *Quad(g2) - 0.421274354923644*Quad(g3) - 0.5055292259083729*traceAdjYdYd*
      Sqr(g1) + 0.25276461295418645*traceAdjYeYe*Sqr(g1) - 2.843601895734597*
      traceAdjYdYd*Sqr(g2) - 0.9478672985781991*traceAdjYeYe*Sqr(g2) +
      0.6477093206951027*Sqr(g1)*Sqr(g2) + 1.263823064770932*traceAdjYdYd*Sqr(
      g3) - 1.263823064770932*traceAdjYeYe*Sqr(g3) + 0.8004212743549236*Sqr(g1)
      *Sqr(g3) + 0.631911532385466*Sqr(g2)*Sqr(g3) + 1.4218009478672986*Sqr(
      traceAdjYdYd) + 0.1579778830963665*Sqr(traceAdjYeYe))*((TYd).adjoint()*
      TYd) + 50.22666666666667*threeLoop*(0.2389169100079639*
      traceAdjYuTYuAdjYdYd + 1.*MassB*Quad(g1) + 0.8959384125298646*MassWB*Quad
      (g2) - 0.21237058667374567*MassG*Quad(g3) + 0.2349349615078312*MassB*Sqr(
      g1)*Sqr(g2) + 0.2349349615078312*MassWB*Sqr(g1)*Sqr(g2) +
      0.5415449960180515*MassB*Sqr(g1)*Sqr(g3) + 0.5415449960180515*MassG*Sqr(
      g1)*Sqr(g3) + 0.15927794000530926*MassG*Sqr(g2)*Sqr(g3) +
      0.15927794000530926*MassWB*Sqr(g2)*Sqr(g3))*((TYu).adjoint()*Yu))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_5 = ((72.*threeLoop*(1.*
      traceAdjYuTYuAdjYuYu + 0.16666666666666666*traceTYdAdjYuYuAdjYd - 0.5*
      traceAdjYuYu*traceTYuAdjYu - 0.05555555555555555*MassB*traceAdjYuYu*Sqr(
      g1) + 0.05555555555555555*traceTYuAdjYu*Sqr(g1) - 0.5*MassWB*traceAdjYuYu
      *Sqr(g2) + 0.5*traceTYuAdjYu*Sqr(g2) + 0.2222222222222222*MassG*
      traceAdjYuYu*Sqr(g3) - 0.2222222222222222*traceTYuAdjYu*Sqr(g3))*((TYu).
      adjoint()*Yu) - 25.11333333333333*threeLoop*(-0.47783382001592783*
      traceAdjYuYuAdjYdYd - 1.4335014600477836*traceAdjYuYuAdjYuYu + 1.*Quad(g1
      ) + 0.8959384125298647*Quad(g2) - 0.2123705866737457*Quad(g3) -
      0.1592779400053093*traceAdjYuYu*Sqr(g1) - 1.4335014600477836*traceAdjYuYu
      *Sqr(g2) + 0.46986992301566244*Sqr(g1)*Sqr(g2) + 0.6371117600212372*
      traceAdjYuYu*Sqr(g3) + 1.0830899920361032*Sqr(g1)*Sqr(g3) +
      0.3185558800106186*Sqr(g2)*Sqr(g3) + 0.7167507300238918*Sqr(traceAdjYuYu)
      )*((TYu).adjoint()*TYu) - 6.33*threeLoop*(-2.843601895734597*
      traceAdjYdYdAdjYdYd + 0.9478672985781991*traceAdjYdYd*traceAdjYeYe -
      0.9478672985781991*traceAdjYeYeAdjYeYe - 0.9478672985781991*
      traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.7772511848341233*Quad(g2) -
      0.421274354923644*Quad(g3) - 0.5055292259083729*traceAdjYdYd*Sqr(g1) +
      0.25276461295418645*traceAdjYeYe*Sqr(g1) - 2.843601895734597*traceAdjYdYd
      *Sqr(g2) - 0.9478672985781991*traceAdjYeYe*Sqr(g2) + 0.6477093206951027*
      Sqr(g1)*Sqr(g2) + 1.263823064770932*traceAdjYdYd*Sqr(g3) -
      1.263823064770932*traceAdjYeYe*Sqr(g3) + 0.8004212743549236*Sqr(g1)*Sqr(
      g3) + 0.631911532385466*Sqr(g2)*Sqr(g3) + 1.4218009478672986*Sqr(
      traceAdjYdYd) + 0.1579778830963665*Sqr(traceAdjYeYe))*(mq2*Yd.adjoint()*
      Yd) - 12.556666666666665*threeLoop*(-0.47783382001592783*
      traceAdjYuYuAdjYdYd - 1.4335014600477836*traceAdjYuYuAdjYuYu + 1.*Quad(g1
      ) + 0.8959384125298647*Quad(g2) - 0.2123705866737457*Quad(g3) -
      0.1592779400053093*traceAdjYuYu*Sqr(g1) - 1.4335014600477836*traceAdjYuYu
      *Sqr(g2) + 0.46986992301566244*Sqr(g1)*Sqr(g2) + 0.6371117600212372*
      traceAdjYuYu*Sqr(g3) + 1.0830899920361032*Sqr(g1)*Sqr(g3) +
      0.3185558800106186*Sqr(g2)*Sqr(g3) + 0.7167507300238918*Sqr(traceAdjYuYu)
      )*(mq2*Yu.adjoint()*Yu) - 12.66*threeLoop*(-2.843601895734597*
      traceAdjYdYdAdjYdYd + 0.9478672985781991*traceAdjYdYd*traceAdjYeYe -
      0.9478672985781991*traceAdjYeYeAdjYeYe - 0.9478672985781991*
      traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.7772511848341233*Quad(g2) -
      0.421274354923644*Quad(g3) - 0.5055292259083729*traceAdjYdYd*Sqr(g1) +
      0.25276461295418645*traceAdjYeYe*Sqr(g1) - 2.843601895734597*traceAdjYdYd
      *Sqr(g2) - 0.9478672985781991*traceAdjYeYe*Sqr(g2) + 0.6477093206951027*
      Sqr(g1)*Sqr(g2) + 1.263823064770932*traceAdjYdYd*Sqr(g3) -
      1.263823064770932*traceAdjYeYe*Sqr(g3) + 0.8004212743549236*Sqr(g1)*Sqr(
      g3) + 0.631911532385466*Sqr(g2)*Sqr(g3) + 1.4218009478672986*Sqr(
      traceAdjYdYd) + 0.1579778830963665*Sqr(traceAdjYeYe))*(Yd.adjoint()*md2*
      Yd) + 2.8*threeLoop*(0.16666666666666669*mHd2*Quad(g1) - 22.5*mHd2*Quad(
      g2) - 64.76190476190477*mHd2*Quad(g3) + 3.428571428571429*MassB*
      traceAdjTYdYd*Sqr(g1) - 1.7142857142857144*MassB*traceAdjTYeYe*Sqr(g1) -
      6.857142857142858*mHd2*traceAdjYdYd*Sqr(g1) - 3.428571428571429*
      traceAdjYdYdmq2*Sqr(g1) + 3.428571428571429*mHd2*traceAdjYeYe*Sqr(g1) +
      1.7142857142857144*traceAdjYeYeml2*Sqr(g1) - 3.428571428571429*
      traceTYdAdjTYd*Sqr(g1) + 3.428571428571429*MassB*traceTYdAdjYd*Sqr(g1) +
      1.7142857142857144*traceTYeAdjTYe*Sqr(g1) + 2.571428571428572*MassB*
      MassWB*Sqr(g1)*Sqr(g2) + 1.285714285714286*mHd2*Sqr(g1)*Sqr(g2) -
      34.28571428571428*MassG*traceAdjTYdYd*Sqr(g3) + 68.57142857142856*mHd2*
      traceAdjYdYd*Sqr(g3) + 34.28571428571428*traceAdjYdYdmq2*Sqr(g3) +
      34.28571428571428*traceTYdAdjTYd*Sqr(g3) - 34.28571428571428*MassG*
      traceTYdAdjYd*Sqr(g3) + 12.190476190476192*MassB*MassG*Sqr(g1)*Sqr(g3) +
      6.095238095238096*mHd2*Sqr(g1)*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) -
      6.857142857142858*traceAdjYdYd*Sqr(g1)*Sqr(MassB) + 3.428571428571429*
      traceAdjYeYe*Sqr(g1)*Sqr(MassB) + 2.571428571428572*Sqr(g1)*Sqr(g2)*Sqr(
      MassB) + 12.190476190476192*Sqr(g1)*Sqr(g3)*Sqr(MassB) -
      388.5714285714286*Quad(g3)*Sqr(MassG) + 68.57142857142856*traceAdjYdYd*
      Sqr(g3)*Sqr(MassG) + 12.190476190476192*Sqr(g1)*Sqr(g3)*Sqr(MassG) - 135.
      *Quad(g2)*Sqr(MassWB) + 2.571428571428572*Sqr(g1)*Sqr(g2)*Sqr(MassWB))*(
      Yd.adjoint()*Yd*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_6 = ((-4.8*threeLoop*(1.*MassB*
      traceTYeAdjYe*Sqr(g1) + 2.*traceYdAdjYdmd2*Sqr(g1) - 1.*traceYeAdjYeme2*
      Sqr(g1) - 19.999999999999996*traceYdAdjYdmd2*Sqr(g3))*(Yd.adjoint()*Yd*
      1.2020569031595942) - 6.33*threeLoop*(-2.843601895734597*
      traceAdjYdYdAdjYdYd + 0.9478672985781991*traceAdjYdYd*traceAdjYeYe -
      0.9478672985781991*traceAdjYeYeAdjYeYe - 0.9478672985781991*
      traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.7772511848341233*Quad(g2) -
      0.421274354923644*Quad(g3) - 0.5055292259083729*traceAdjYdYd*Sqr(g1) +
      0.25276461295418645*traceAdjYeYe*Sqr(g1) - 2.843601895734597*traceAdjYdYd
      *Sqr(g2) - 0.9478672985781991*traceAdjYeYe*Sqr(g2) + 0.6477093206951027*
      Sqr(g1)*Sqr(g2) + 1.263823064770932*traceAdjYdYd*Sqr(g3) -
      1.263823064770932*traceAdjYeYe*Sqr(g3) + 0.8004212743549236*Sqr(g1)*Sqr(
      g3) + 0.631911532385466*Sqr(g2)*Sqr(g3) + 1.4218009478672986*Sqr(
      traceAdjYdYd) + 0.1579778830963665*Sqr(traceAdjYeYe))*(Yd.adjoint()*Yd*
      mq2) - 0.9333333333333332*threeLoop*(1.*MassB*Quad(g1) -
      134.99999999999997*MassWB*Quad(g2) - 388.5714285714286*MassG*Quad(g3) +
      10.285714285714286*traceAdjTYdYd*Sqr(g1) - 5.142857142857143*
      traceAdjTYeYe*Sqr(g1) - 10.285714285714286*MassB*traceAdjYdYd*Sqr(g1) +
      5.142857142857143*MassB*traceAdjYeYe*Sqr(g1) + 3.857142857142858*MassB*
      Sqr(g1)*Sqr(g2) + 3.857142857142858*MassWB*Sqr(g1)*Sqr(g2) -
      102.85714285714286*traceAdjTYdYd*Sqr(g3) + 102.85714285714286*MassG*
      traceAdjYdYd*Sqr(g3) + 18.28571428571429*MassB*Sqr(g1)*Sqr(g3) +
      18.28571428571429*MassG*Sqr(g1)*Sqr(g3))*(Yd.adjoint()*TYd*
      1.2020569031595942) - 25.11333333333333*threeLoop*(-0.47783382001592783*
      traceAdjYuYuAdjYdYd - 1.4335014600477836*traceAdjYuYuAdjYuYu + 1.*Quad(g1
      ) + 0.8959384125298647*Quad(g2) - 0.2123705866737457*Quad(g3) -
      0.1592779400053093*traceAdjYuYu*Sqr(g1) - 1.4335014600477836*traceAdjYuYu
      *Sqr(g2) + 0.4698699230156625*Sqr(g1)*Sqr(g2) + 0.6371117600212372*
      traceAdjYuYu*Sqr(g3) + 1.083089992036103*Sqr(g1)*Sqr(g3) +
      0.3185558800106186*Sqr(g2)*Sqr(g3) + 0.7167507300238918*Sqr(traceAdjYuYu)
      )*(Yu.adjoint()*mu2*Yu) + 11.44*threeLoop*(0.16666666666666669*mHu2*Quad(
      g1) - 5.506993006993007*mHu2*Quad(g2) - 15.850815850815852*mHu2*Quad(g3)
      + 0.8391608391608392*MassB*traceAdjTYuYu*Sqr(g1) - 1.6783216783216783*
      mHu2*traceAdjYuYu*Sqr(g1) - 0.8391608391608392*traceAdjYuYumq2*Sqr(g1) -
      0.8391608391608392*traceTYuAdjTYu*Sqr(g1) + 0.8391608391608392*MassB*
      traceTYuAdjYu*Sqr(g1) - 0.8391608391608392*traceYuAdjYumu2*Sqr(g1) +
      3.146853146853147*MassB*MassWB*Sqr(g1)*Sqr(g2) + 1.5734265734265735*mHu2*
      Sqr(g1)*Sqr(g2) - 8.391608391608392*MassG*traceAdjTYuYu*Sqr(g3) +
      16.783216783216783*mHu2*traceAdjYuYu*Sqr(g3) + 8.391608391608392*
      traceAdjYuYumq2*Sqr(g3) + 8.391608391608392*traceTYuAdjTYu*Sqr(g3) -
      8.391608391608392*MassG*traceTYuAdjYu*Sqr(g3) + 8.391608391608392*
      traceYuAdjYumu2*Sqr(g3) + 2.983682983682984*MassB*MassG*Sqr(g1)*Sqr(g3) +
      1.491841491841492*mHu2*Sqr(g1)*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) -
      1.6783216783216783*traceAdjYuYu*Sqr(g1)*Sqr(MassB) + 3.146853146853147*
      Sqr(g1)*Sqr(g2)*Sqr(MassB) + 2.983682983682984*Sqr(g1)*Sqr(g3)*Sqr(MassB)
      - 95.1048951048951*Quad(g3)*Sqr(MassG) + 16.783216783216783*traceAdjYuYu*
      Sqr(g3)*Sqr(MassG) + 2.983682983682984*Sqr(g1)*Sqr(g3)*Sqr(MassG) -
      33.04195804195804*Quad(g2)*Sqr(MassWB) + 3.146853146853147*Sqr(g1)*Sqr(g2
      )*Sqr(MassWB))*(Yu.adjoint()*Yu*1.2020569031595942) - 12.556666666666665*
      threeLoop*(-0.47783382001592783*traceAdjYuYuAdjYdYd - 1.4335014600477836*
      traceAdjYuYuAdjYuYu + 1.*Quad(g1) + 0.8959384125298647*Quad(g2) -
      0.2123705866737457*Quad(g3) - 0.1592779400053093*traceAdjYuYu*Sqr(g1) -
      1.4335014600477836*traceAdjYuYu*Sqr(g2) + 0.4698699230156625*Sqr(g1)*Sqr(
      g2) + 0.6371117600212372*traceAdjYuYu*Sqr(g3) + 1.083089992036103*Sqr(g1)
      *Sqr(g3) + 0.3185558800106186*Sqr(g2)*Sqr(g3) + 0.7167507300238918*Sqr(
      traceAdjYuYu))*(Yu.adjoint()*Yu*mq2) - 3.8133333333333335*threeLoop*(1.*
      MassB*Quad(g1) - 33.04195804195804*MassWB*Quad(g2) - 95.1048951048951*
      MassG*Quad(g3) + 2.5174825174825175*traceAdjTYuYu*Sqr(g1) -
      2.5174825174825175*MassB*traceAdjYuYu*Sqr(g1) + 4.72027972027972*MassB*
      Sqr(g1)*Sqr(g2) + 4.72027972027972*MassWB*Sqr(g1)*Sqr(g2) -
      25.174825174825173*traceAdjTYuYu*Sqr(g3) + 25.174825174825173*MassG*
      traceAdjYuYu*Sqr(g3) + 4.475524475524475*MassB*Sqr(g1)*Sqr(g3) +
      4.475524475524475*MassG*Sqr(g1)*Sqr(g3))*(Yu.adjoint()*TYu*
      1.2020569031595942) - 0.9333333333333332*Sqr(g1)*(1.*MassB*threeLoop*Sqr(
      g1) + 3.857142857142858*MassB*threeLoop*Sqr(g2))*((TYd).adjoint()*Yd*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_7 = ((-17.066666666666666*threeLoop
      *(-7.382812499999999*MassWB*Quad(g2) - 21.25*MassG*Quad(g3) - 0.5625*
      MassB*traceAdjYdYd*Sqr(g1) + 0.28125*MassB*traceAdjYeYe*Sqr(g1) + 0.5625*
      traceTYdAdjYd*Sqr(g1) - 0.28125*traceTYeAdjYe*Sqr(g1) +
      0.21093750000000003*MassWB*Sqr(g1)*Sqr(g2) + 5.625*MassG*traceAdjYdYd*Sqr
      (g3) - 5.625*traceTYdAdjYd*Sqr(g3) + 1.*MassB*Sqr(g1)*Sqr(g3) + 1.*MassG*
      Sqr(g1)*Sqr(g3))*((TYd).adjoint()*Yd*1.2020569031595942) +
      0.4666666666666667*threeLoop*(1.*Quad(g1) - 134.99999999999997*Quad(g2) -
      388.5714285714286*Quad(g3) - 20.57142857142857*traceAdjYdYd*Sqr(g1) +
      10.285714285714285*traceAdjYeYe*Sqr(g1) + 7.714285714285715*Sqr(g1)*Sqr(
      g2) + 205.71428571428572*traceAdjYdYd*Sqr(g3) + 36.57142857142857*Sqr(g1)
      *Sqr(g3))*((TYd).adjoint()*TYd*1.2020569031595942) - 3.813333333333334*
      threeLoop*(1.*MassB*Quad(g1) - 33.04195804195803*MassWB*Quad(g2) -
      95.10489510489509*MassG*Quad(g3) - 2.517482517482517*MassB*traceAdjYuYu*
      Sqr(g1) + 2.517482517482517*traceTYuAdjYu*Sqr(g1) + 4.72027972027972*
      MassB*Sqr(g1)*Sqr(g2) + 4.72027972027972*MassWB*Sqr(g1)*Sqr(g2) +
      25.17482517482517*MassG*traceAdjYuYu*Sqr(g3) - 25.17482517482517*
      traceTYuAdjYu*Sqr(g3) + 4.475524475524475*MassB*Sqr(g1)*Sqr(g3) +
      4.475524475524475*MassG*Sqr(g1)*Sqr(g3))*((TYu).adjoint()*Yu*
      1.2020569031595942) + 1.906666666666667*threeLoop*(1.*Quad(g1) -
      33.04195804195803*Quad(g2) - 95.10489510489509*Quad(g3) -
      5.034965034965034*traceAdjYuYu*Sqr(g1) + 9.44055944055944*Sqr(g1)*Sqr(g2)
      + 50.34965034965034*traceAdjYuYu*Sqr(g3) + 8.95104895104895*Sqr(g1)*Sqr(
      g3))*((TYu).adjoint()*TYu*1.2020569031595942) + 0.23333333333333334*
      threeLoop*(1.*Quad(g1) - 134.99999999999997*Quad(g2) - 388.5714285714286*
      Quad(g3) - 20.57142857142857*traceAdjYdYd*Sqr(g1) + 10.285714285714285*
      traceAdjYeYe*Sqr(g1) + 7.714285714285715*Sqr(g1)*Sqr(g2) +
      205.71428571428572*traceAdjYdYd*Sqr(g3) + 36.57142857142857*Sqr(g1)*Sqr(
      g3))*(mq2*Yd.adjoint()*Yd*1.2020569031595942) + 0.9533333333333335*
      threeLoop*(1.*Quad(g1) - 33.04195804195803*Quad(g2) - 95.10489510489509*
      Quad(g3) - 5.034965034965034*traceAdjYuYu*Sqr(g1) + 9.44055944055944*Sqr(
      g1)*Sqr(g2) + 50.34965034965034*traceAdjYuYu*Sqr(g3) + 8.95104895104895*
      Sqr(g1)*Sqr(g3))*(mq2*Yu.adjoint()*Yu*1.2020569031595942) +
      0.4666666666666667*threeLoop*(1.*Quad(g1) - 134.99999999999997*Quad(g2) -
      388.5714285714286*Quad(g3) - 20.57142857142857*traceAdjYdYd*Sqr(g1) +
      10.285714285714285*traceAdjYeYe*Sqr(g1) + 7.714285714285715*Sqr(g1)*Sqr(
      g2) + 205.71428571428572*traceAdjYdYd*Sqr(g3) + 36.57142857142857*Sqr(g1)
      *Sqr(g3))*(Yd.adjoint()*md2*Yd*1.2020569031595942) + 0.23333333333333334*
      threeLoop*(1.*Quad(g1) - 134.99999999999997*Quad(g2) - 388.5714285714286*
      Quad(g3) - 20.57142857142857*traceAdjYdYd*Sqr(g1) + 10.285714285714285*
      traceAdjYeYe*Sqr(g1) + 7.714285714285715*Sqr(g1)*Sqr(g2) +
      205.71428571428572*traceAdjYdYd*Sqr(g3) + 36.57142857142857*Sqr(g1)*Sqr(
      g3))*(Yd.adjoint()*Yd*mq2*1.2020569031595942) + 1.8666666666666667*
      threeLoop*(19.285714285714285*mHd2*traceAdjYdYd + 6.428571428571429*
      traceAdjYdYdmq2 + 6.428571428571429*mHd2*traceAdjYeYe + 2.142857142857143
      *traceAdjYeYeml2 + 6.428571428571429*traceTYdAdjTYd + 2.142857142857143*
      traceTYeAdjTYe + 6.428571428571429*traceYdAdjYdmd2 + 2.142857142857143*
      traceYeAdjYeme2 + 1.*mHd2*Sqr(g1) - 6.428571428571429*mHd2*Sqr(g2) +
      45.71428571428571*mHd2*Sqr(g3) + 1.*Sqr(g1)*Sqr(MassB) +
      45.71428571428571*Sqr(g3)*Sqr(MassG) - 6.428571428571429*Sqr(g2)*Sqr(
      MassWB))*(Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.9333333333333333*threeLoop
      *(-12.857142857142858*traceAdjTYdYd - 4.285714285714286*traceAdjTYeYe +
      1.*MassB*Sqr(g1) - 6.428571428571429*MassWB*Sqr(g2) + 45.71428571428571*
      MassG*Sqr(g3))*(Yd.adjoint()*Yd*Yd.adjoint()*TYd) - 0.9333333333333333*
      threeLoop*(-12.857142857142858*traceTYdAdjYd - 4.285714285714286*
      traceTYeAdjYe + 1.*MassB*Sqr(g1) - 6.428571428571429*MassWB*Sqr(g2) +
      45.71428571428571*MassG*Sqr(g3))*(Yd.adjoint()*Yd*(TYd).adjoint()*Yd) +
      0.9333333333333333*threeLoop*(12.857142857142858*traceAdjYdYd +
      4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) - 6.428571428571429*Sqr(g2) +
      45.71428571428571*Sqr(g3))*(Yd.adjoint()*Yd*(TYd).adjoint()*TYd) -
      0.9333333333333333*(1.*MassB*threeLoop*Sqr(g1) - 6.428571428571429*MassWB
      *threeLoop*Sqr(g2) + 45.71428571428571*MassG*threeLoop*Sqr(g3))*(Yd.
      adjoint()*TYd*Yd.adjoint()*Yd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_8 = ((12.*threeLoop*(1.*
      traceAdjTYdYd + 0.3333333333333333*traceAdjTYeYe)*(Yd.adjoint()*TYd*Yd.
      adjoint()*Yd) + 0.9333333333333333*threeLoop*(12.857142857142858*
      traceAdjYdYd + 4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) -
      6.428571428571429*Sqr(g2) + 45.71428571428571*Sqr(g3))*(Yd.adjoint()*TYd*
      (TYd).adjoint()*Yd) + 1.906666666666667*threeLoop*(1.*Quad(g1) -
      33.04195804195803*Quad(g2) - 95.10489510489509*Quad(g3) -
      5.034965034965034*traceAdjYuYu*Sqr(g1) + 9.44055944055944*Sqr(g1)*Sqr(g2)
      + 50.34965034965034*traceAdjYuYu*Sqr(g3) + 8.95104895104895*Sqr(g1)*Sqr(
      g3))*(Yu.adjoint()*mu2*Yu*1.2020569031595942) + 0.9533333333333335*
      threeLoop*(1.*Quad(g1) - 33.04195804195803*Quad(g2) - 95.10489510489509*
      Quad(g3) - 5.034965034965034*traceAdjYuYu*Sqr(g1) + 9.44055944055944*Sqr(
      g1)*Sqr(g2) + 50.34965034965034*traceAdjYuYu*Sqr(g3) + 8.95104895104895*
      Sqr(g1)*Sqr(g3))*(Yu.adjoint()*Yu*mq2*1.2020569031595942) +
      14.666666666666664*threeLoop*(2.454545454545455*mHu2*traceAdjYuYu +
      0.8181818181818183*traceAdjYuYumq2 + 0.8181818181818183*traceTYuAdjTYu +
      0.8181818181818183*traceYuAdjYumu2 + 1.*mHu2*Sqr(g1) - 0.8181818181818183
      *mHu2*Sqr(g2) + 5.818181818181819*mHu2*Sqr(g3) + 1.*Sqr(g1)*Sqr(MassB) +
      5.818181818181819*Sqr(g3)*Sqr(MassG) - 0.8181818181818183*Sqr(g2)*Sqr(
      MassWB))*(Yu.adjoint()*Yu*Yu.adjoint()*Yu) - 7.333333333333332*threeLoop*
      (-1.6363636363636367*traceAdjTYuYu + 1.*MassB*Sqr(g1) -
      0.8181818181818183*MassWB*Sqr(g2) + 5.818181818181819*MassG*Sqr(g3))*(Yu.
      adjoint()*Yu*Yu.adjoint()*TYu) - 7.333333333333332*threeLoop*(-
      1.6363636363636367*traceTYuAdjYu + 1.*MassB*Sqr(g1) - 0.8181818181818183*
      MassWB*Sqr(g2) + 5.818181818181819*MassG*Sqr(g3))*(Yu.adjoint()*Yu*(TYu).
      adjoint()*Yu) + 7.333333333333332*threeLoop*(1.6363636363636367*
      traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(g2) +
      5.818181818181819*Sqr(g3))*(Yu.adjoint()*Yu*(TYu).adjoint()*TYu) -
      7.333333333333332*threeLoop*(-1.6363636363636367*traceAdjTYuYu + 1.*MassB
      *Sqr(g1) - 0.8181818181818183*MassWB*Sqr(g2) + 5.818181818181819*MassG*
      Sqr(g3))*(Yu.adjoint()*TYu*Yu.adjoint()*Yu) + 7.333333333333332*threeLoop
      *(1.6363636363636367*traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(
      g2) + 5.818181818181819*Sqr(g3))*(Yu.adjoint()*TYu*(TYu).adjoint()*Yu) -
      0.9333333333333333*threeLoop*(-12.857142857142858*traceTYdAdjYd -
      4.285714285714286*traceTYeAdjYe + 1.*MassB*Sqr(g1) - 6.428571428571429*
      MassWB*Sqr(g2) + 45.71428571428571*MassG*Sqr(g3))*((TYd).adjoint()*Yd*Yd.
      adjoint()*Yd) + 0.9333333333333333*threeLoop*(12.857142857142858*
      traceAdjYdYd + 4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) -
      6.428571428571429*Sqr(g2) + 45.71428571428571*Sqr(g3))*((TYd).adjoint()*
      Yd*Yd.adjoint()*TYd) + 0.9333333333333333*threeLoop*(12.857142857142858*
      traceAdjYdYd + 4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) -
      6.428571428571429*Sqr(g2) + 45.71428571428571*Sqr(g3))*((TYd).adjoint()*
      TYd*Yd.adjoint()*Yd) - 7.333333333333332*threeLoop*(-1.6363636363636367*
      traceTYuAdjYu + 1.*MassB*Sqr(g1) - 0.8181818181818183*MassWB*Sqr(g2) +
      5.818181818181819*MassG*Sqr(g3))*((TYu).adjoint()*Yu*Yu.adjoint()*Yu) +
      7.333333333333332*threeLoop*(1.6363636363636367*traceAdjYuYu + 1.*Sqr(g1)
      - 0.8181818181818183*Sqr(g2) + 5.818181818181819*Sqr(g3))*((TYu).adjoint(
      )*Yu*Yu.adjoint()*TYu) + 7.333333333333332*threeLoop*(1.6363636363636367*
      traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(g2) +
      5.818181818181819*Sqr(g3))*((TYu).adjoint()*TYu*Yu.adjoint()*Yu) +
      0.4666666666666667*threeLoop*(12.857142857142858*traceAdjYdYd +
      4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) - 6.428571428571429*Sqr(g2) +
      45.71428571428571*Sqr(g3))*(mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd) +
      3.666666666666666*threeLoop*(1.6363636363636367*traceAdjYuYu + 1.*Sqr(g1)
      - 0.8181818181818183*Sqr(g2) + 5.818181818181819*Sqr(g3))*(mq2*Yu.adjoint
      ()*Yu*Yu.adjoint()*Yu) + 0.9333333333333333*threeLoop*(12.857142857142858
      *traceAdjYdYd + 4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) -
      6.428571428571429*Sqr(g2) + 45.71428571428571*Sqr(g3))*(Yd.adjoint()*md2*
      Yd*Yd.adjoint()*Yd) + 0.9333333333333333*threeLoop*(12.857142857142858*
      traceAdjYdYd + 4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) -
      6.428571428571429*Sqr(g2) + 45.71428571428571*Sqr(g3))*(Yd.adjoint()*Yd*
      mq2*Yd.adjoint()*Yd) + 0.9333333333333333*(1.*threeLoop*Sqr(g1) -
      6.428571428571429*threeLoop*Sqr(g2) + 45.71428571428571*threeLoop*Sqr(g3)
      )*(Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_9 = ((12.*threeLoop*(1.*
      traceAdjYdYd + 0.3333333333333333*traceAdjYeYe)*(Yd.adjoint()*Yd*Yd.
      adjoint()*md2*Yd) - 4.8*(1.*mHd2*threeLoop*Sqr(g1) - 15.*mHd2*threeLoop*
      Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(MassB) - 15.*threeLoop*Sqr(g2)*Sqr(
      MassWB))*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      0.4666666666666667*threeLoop*(12.857142857142858*traceAdjYdYd +
      4.285714285714286*traceAdjYeYe + 1.*Sqr(g1) - 6.428571428571429*Sqr(g2) +
      45.71428571428571*Sqr(g3))*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2) + 2.4*(
      1.*MassB*threeLoop*Sqr(g1) - 15.*MassWB*threeLoop*Sqr(g2))*(Yd.adjoint()*
      Yd*Yd.adjoint()*TYd*1.2020569031595942) + 2.4*(1.*MassB*threeLoop*Sqr(g1)
      - 15.*MassWB*threeLoop*Sqr(g2))*(Yd.adjoint()*Yd*(TYd).adjoint()*Yd*
      1.2020569031595942) - 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*
      (Yd.adjoint()*Yd*(TYd).adjoint()*TYd*1.2020569031595942) + 2.4*(1.*MassB*
      threeLoop*Sqr(g1) - 15.*MassWB*threeLoop*Sqr(g2))*(Yd.adjoint()*TYd*Yd.
      adjoint()*Yd*1.2020569031595942) - 2.4*(1.*threeLoop*Sqr(g1) - 15.*
      threeLoop*Sqr(g2))*(Yd.adjoint()*TYd*(TYd).adjoint()*Yd*
      1.2020569031595942) + 7.333333333333332*threeLoop*(1.6363636363636367*
      traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(g2) +
      5.818181818181819*Sqr(g3))*(Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu) +
      7.333333333333332*threeLoop*(1.6363636363636367*traceAdjYuYu + 1.*Sqr(g1)
      - 0.8181818181818183*Sqr(g2) + 5.818181818181819*Sqr(g3))*(Yu.adjoint()*
      Yu*mq2*Yu.adjoint()*Yu) + 7.333333333333332*threeLoop*(1.6363636363636367
      *traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(g2) +
      5.818181818181819*Sqr(g3))*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu) - 24.*(
      1.*mHu2*threeLoop*Sqr(g1) - 3.*mHu2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(
      g1)*Sqr(MassB) - 3.*threeLoop*Sqr(g2)*Sqr(MassWB))*(Yu.adjoint()*Yu*Yu.
      adjoint()*Yu*1.2020569031595942) + 3.666666666666666*threeLoop*(
      1.6363636363636367*traceAdjYuYu + 1.*Sqr(g1) - 0.8181818181818183*Sqr(g2)
      + 5.818181818181819*Sqr(g3))*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2) + 12.*
      (1.*MassB*threeLoop*Sqr(g1) - 3.*MassWB*threeLoop*Sqr(g2))*(Yu.adjoint()*
      Yu*Yu.adjoint()*TYu*1.2020569031595942) + 12.*(1.*MassB*threeLoop*Sqr(g1)
      - 3.*MassWB*threeLoop*Sqr(g2))*(Yu.adjoint()*Yu*(TYu).adjoint()*Yu*
      1.2020569031595942) - 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(
      Yu.adjoint()*Yu*(TYu).adjoint()*TYu*1.2020569031595942) + 12.*(1.*MassB*
      threeLoop*Sqr(g1) - 3.*MassWB*threeLoop*Sqr(g2))*(Yu.adjoint()*TYu*Yu.
      adjoint()*Yu*1.2020569031595942) - 12.*(1.*threeLoop*Sqr(g1) - 3.*
      threeLoop*Sqr(g2))*(Yu.adjoint()*TYu*(TYu).adjoint()*Yu*
      1.2020569031595942) + 2.4*(1.*MassB*threeLoop*Sqr(g1) - 15.*MassWB*
      threeLoop*Sqr(g2))*((TYd).adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942
      ) - 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*((TYd).adjoint()*
      Yd*Yd.adjoint()*TYd*1.2020569031595942) - 2.4*(1.*threeLoop*Sqr(g1) - 15.
      *threeLoop*Sqr(g2))*((TYd).adjoint()*TYd*Yd.adjoint()*Yd*
      1.2020569031595942) + 12.*(1.*MassB*threeLoop*Sqr(g1) - 3.*MassWB*
      threeLoop*Sqr(g2))*((TYu).adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942
      ) - 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*((TYu).adjoint()*Yu
      *Yu.adjoint()*TYu*1.2020569031595942) - 12.*(1.*threeLoop*Sqr(g1) - 3.*
      threeLoop*Sqr(g2))*((TYu).adjoint()*TYu*Yu.adjoint()*Yu*
      1.2020569031595942) - 1.2*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*
      (mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) - 6.*(1.*
      threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(mq2*Yu.adjoint()*Yu*Yu.adjoint
      ()*Yu*1.2020569031595942) - 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr
      (g2))*(Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*1.2020569031595942) - 2.4*(1.*
      threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*(Yd.adjoint()*Yd*mq2*Yd.
      adjoint()*Yd*1.2020569031595942) - 2.4*(1.*threeLoop*Sqr(g1) - 15.*
      threeLoop*Sqr(g2))*(Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*
      1.2020569031595942) - 1.2*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*
      (Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*1.2020569031595942) + 16.*(1.*mHd2*
      threeLoop + 0.5*mHu2*threeLoop)*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*(TYd).
      adjoint()*TYd) + 8.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*TYu*(TYd).
      adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*(TYu).adjoint()*Yu*Yd.
      adjoint()*TYd) + 8.*threeLoop*(Yd.adjoint()*Yd*(TYu).adjoint()*TYu*Yd.
      adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*TYd*Yu.adjoint()*Yu*(TYd).
      adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*TYd*(TYu).adjoint()*Yu*Yd.
      adjoint()*Yd) - 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(Yu.
      adjoint()*mu2*Yu*Yu.adjoint()*Yu*1.2020569031595942) - 12.*(1.*threeLoop*
      Sqr(g1) - 3.*threeLoop*Sqr(g2))*(Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*
      1.2020569031595942) + 8.*(1.*mHd2*threeLoop + 2.*mHu2*threeLoop)*(Yu.
      adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.adjoint(
      )*Yu*Yd.adjoint()*Yd*(TYu).adjoint()*TYu) + 8.*threeLoop*(Yu.adjoint()*Yu
      *Yd.adjoint()*TYd*(TYu).adjoint()*Yu) - 12.*(1.*threeLoop*Sqr(g1) - 3.*
      threeLoop*Sqr(g2))*(Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*
      1.2020569031595942) - 6.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*1.2020569031595942) + 8.*threeLoop*(
      Yu.adjoint()*Yu*(TYd).adjoint()*Yd*Yu.adjoint()*TYu) + 8.*threeLoop*(Yu.
      adjoint()*Yu*(TYd).adjoint()*TYd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yu.
      adjoint()*TYu*Yd.adjoint()*Yd*(TYu).adjoint()*Yu) + 8.*threeLoop*(Yu.
      adjoint()*TYu*(TYd).adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*((TYd).
      adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*TYd))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mq2_10 = ((8.*threeLoop*((TYd).adjoint(
      )*Yd*Yu.adjoint()*TYu*Yd.adjoint()*Yd) + 8.*threeLoop*((TYd).adjoint()*
      TYd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 8.*threeLoop*((TYu).adjoint()*Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*TYu) + 8.*threeLoop*((TYu).adjoint()*Yu*Yd.
      adjoint()*TYd*Yu.adjoint()*Yu) + 8.*threeLoop*((TYu).adjoint()*TYu*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu) + 4.*threeLoop*(mq2*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu*Yd.adjoint()*Yd) + 4.*threeLoop*(mq2*Yu.adjoint()*Yu*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu) + 8.*threeLoop*(Yd.adjoint()*md2*Yd*Yu.
      adjoint()*Yu*Yd.adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*mq2*Yu.
      adjoint()*Yu*Yd.adjoint()*Yd) + 36.*mHd2*threeLoop*(Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*(TYd).adjoint()*TYd*1.2020569031595942) +
      12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*TYd*(TYd).adjoint()*Yd*
      1.2020569031595942) + 8.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*mu2*Yu*
      Yd.adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*mq2*Yd.
      adjoint()*Yd) + 8.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint(
      )*md2*Yd) + 4.*threeLoop*(Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd
      *mq2) + 12.*threeLoop*(Yd.adjoint()*Yd*(TYd).adjoint()*Yd*Yd.adjoint()*
      TYd*1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*(TYd).adjoint()*
      TYd*Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*TYd
      *Yd.adjoint()*Yd*(TYd).adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(
      Yd.adjoint()*TYd*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      8.*threeLoop*(Yu.adjoint()*mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu) + 8.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*mu2*Yu) + 4.*
      threeLoop*(Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*mq2) + 36.*
      mHu2*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYu
      ).adjoint()*TYu*1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*Yu.
      adjoint()*TYu*(TYu).adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yu.
      adjoint()*Yu*(TYu).adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) +
      12.*threeLoop*(Yu.adjoint()*Yu*(TYu).adjoint()*TYu*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*TYu*Yu.adjoint()*Yu*(
      TYu).adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*TYu*(
      TYu).adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*((
      TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*1.2020569031595942) +
      12.*threeLoop*((TYd).adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*
      1.2020569031595942) + 12.*threeLoop*((TYd).adjoint()*TYd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*((TYu).adjoint()*Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*TYu*1.2020569031595942) + 12.*threeLoop*((
      TYu).adjoint()*Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*1.2020569031595942) +
      12.*threeLoop*((TYu).adjoint()*TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      1.2020569031595942) + 6.*threeLoop*(mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 6.*threeLoop*(mq2*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yd.
      adjoint()*md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*1.2020569031595942) +
      12.*threeLoop*(Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*
      Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*mq2*Yd.adjoint()*Yd*1.2020569031595942) + 12.*threeLoop*(Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*1.2020569031595942) + 6.
      *threeLoop*(Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*mq2*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu*1.2020569031595942) + 12.*threeLoop*(Yu.
      adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()*Yu*1.2020569031595942) +
      12.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()*Yu*
      1.2020569031595942) + 12.*threeLoop*(Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*mu2*Yu*1.2020569031595942) + 6.*threeLoop*(Yu.adjoint()*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*mq2*1.2020569031595942))*UNITMATRIX(3)).real
      ();

   beta_mq2 = beta_mq2_1 + beta_mq2_2 + beta_mq2_3 + beta_mq2_4 + beta_mq2_5 +
      beta_mq2_6 + beta_mq2_7 + beta_mq2_8 + beta_mq2_9 + beta_mq2_10;


   return beta_mq2;
}

/**
 * Calculates the 4-loop beta function of mq2.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mq2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = ZEROMATRIX(3,3);


   return beta_mq2;
}

/**
 * Calculates the 5-loop beta function of mq2.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mq2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = ZEROMATRIX(3,3);


   return beta_mq2;
}

} // namespace flexiblesusy
