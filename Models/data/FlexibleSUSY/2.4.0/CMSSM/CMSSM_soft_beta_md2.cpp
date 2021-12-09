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

// File generated at Thu 10 Oct 2019 17:27:46

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
 * Calculates the 1-loop beta function of md2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_md2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_md2;

   beta_md2 = (oneOver16PiSqr*(4*mHd2*(Yd*Yd.adjoint()) + 4*(TYd*(TYd).adjoint(
      )) + 2*(md2*Yd*Yd.adjoint()) + 4*(Yd*mq2*Yd.adjoint()) + 2*(Yd*Yd.adjoint
      ()*md2) + 0.13333333333333333*(3.872983346207417*g1*Tr11 - 4*AbsSqr(MassB
      )*Sqr(g1) - 80*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_md2;
}

/**
 * Calculates the 2-loop beta function of md2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_md2_2_loop(const Soft_traces& soft_traces) const
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

   beta_md2 = (twoLoop*(0.8*(-15*traceconjTYdTpTYd - 5*traceconjTYeTpTYe - 15*
      tracemd2YdAdjYd - 5*traceme2YeAdjYe - 5*traceml2AdjYeYe - 15*
      tracemq2AdjYdYd - 30*mHd2*traceYdAdjYd - 10*mHd2*traceYeAdjYe + mHd2*Sqr(
      g1) + 2*AbsSqr(MassB)*Sqr(g1) + 15*mHd2*Sqr(g2) + 30*AbsSqr(MassWB)*Sqr(
      g2))*(Yd*Yd.adjoint()) - 0.8*(15*traceAdjYdTYd + 5*traceAdjYeTYe + MassB*
      Sqr(g1) + 15*MassWB*Sqr(g2))*(Yd*(TYd).adjoint()) - 0.8*(15*
      traceconjTYdTpYd + 5*traceconjTYeTpYe + Conj(MassB)*Sqr(g1) + 15*Conj(
      MassWB)*Sqr(g2))*(TYd*Yd.adjoint()) + 0.8*(-15*traceYdAdjYd - 5*
      traceYeAdjYe + Sqr(g1) + 15*Sqr(g2))*(TYd*(TYd).adjoint()) + 0.4*(-15*
      traceYdAdjYd - 5*traceYeAdjYe + Sqr(g1) + 15*Sqr(g2))*(md2*Yd*Yd.adjoint(
      )) + 0.8*(-15*traceYdAdjYd - 5*traceYeAdjYe + Sqr(g1) + 15*Sqr(g2))*(Yd*
      mq2*Yd.adjoint()) + 0.4*(-15*traceYdAdjYd - 5*traceYeAdjYe + Sqr(g1) + 15
      *Sqr(g2))*(Yd*Yd.adjoint()*md2) - 8*mHd2*(Yd*Yd.adjoint()*Yd*Yd.adjoint()
      ) - 4*(Yd*Yd.adjoint()*TYd*(TYd).adjoint()) - 4*(mHd2 + mHu2)*(Yd*Yu.
      adjoint()*Yu*Yd.adjoint()) - 4*(Yd*Yu.adjoint()*TYu*(TYd).adjoint()) - 4*
      (Yd*(TYd).adjoint()*TYd*Yd.adjoint()) - 4*(Yd*(TYu).adjoint()*TYu*Yd.
      adjoint()) - 4*(TYd*Yd.adjoint()*Yd*(TYd).adjoint()) - 4*(TYd*Yu.adjoint(
      )*Yu*(TYd).adjoint()) - 4*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()) - 4*(TYd*
      (TYu).adjoint()*Yu*Yd.adjoint()) - 2*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()
      ) - 2*(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()) - 4*(Yd*mq2*Yd.adjoint()*Yd*
      Yd.adjoint()) - 4*(Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()) - 4*(Yd*Yd.
      adjoint()*md2*Yd*Yd.adjoint()) - 4*(Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint())
      - 2*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2) - 4*(Yd*Yu.adjoint()*mu2*Yu*Yd.
      adjoint()) - 4*(Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()) - 2*(Yd*Yu.adjoint()
      *Yu*Yd.adjoint()*md2) + 0.035555555555555556*(58.09475019311125*g1*Tr31 +
      303*AbsSqr(MassB)*Quad(g1) + 300*Tr23*Quad(g3) - 1200*AbsSqr(MassG)*Quad(
      g3) + 15*Tr2U111*Sqr(g1) + 80*AbsSqr(MassB)*Sqr(g1)*Sqr(g3) + 80*AbsSqr(
      MassG)*Sqr(g1)*Sqr(g3) + 40*MassG*Conj(MassB)*Sqr(g1)*Sqr(g3) + 40*MassB*
      Conj(MassG)*Sqr(g1)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_md2;
}

/**
 * Calculates the 3-loop beta function of md2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_md2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjTYdYd = TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjTYdTYdAdjYdYd = TRACE_STRUCT.traceAdjTYdTYdAdjYdYd;
   const double traceAdjTYdTYdAdjYuYu = TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYeTYeAdjYeYe = TRACE_STRUCT.traceAdjTYeTYeAdjYeYe;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjTYuTYuAdjYdYd = TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceTYdAdjTYuYuAdjYd = TRACE_STRUCT.traceTYdAdjTYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdmd2 = TRACE_STRUCT.traceYdAdjYdYdAdjYdmd2;
   const double traceYdAdjYuYuAdjYdmd2 = TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2;
   const double traceYeAdjYeYeAdjYeme2 = TRACE_STRUCT.traceYeAdjYeYeAdjYeme2;
   const double traceYuAdjYdYdAdjYumu2 = TRACE_STRUCT.traceYuAdjYdYdAdjYumu2;
   const double traceAdjYdYdAdjYdYdmq2 = TRACE_STRUCT.traceAdjYdYdAdjYdYdmq2;
   const double traceAdjYdYdAdjYuYumq2 = TRACE_STRUCT.traceAdjYdYdAdjYuYumq2;
   const double traceAdjYeYeAdjYeYeml2 = TRACE_STRUCT.traceAdjYeYeAdjYeYeml2;
   const double traceAdjYuYuAdjYdYdmq2 = TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2;


   Eigen::Matrix<double,3,3> beta_md2;

   const Eigen::Matrix<double,3,3> beta_md2_1 = ((110.40850857704534*threeLoop*
      (-0.019515404151692672*mHd2*Power6(g1) - 0.019515404151692672*mHu2*Power6
      (g1) - 0.013010269434461782*tracemd2*Power6(g1) - 0.039030808303385345*
      traceme2*Power6(g1) - 0.019515404151692672*traceml2*Power6(g1) -
      0.006505134717230891*tracemq2*Power6(g1) - 0.05204107773784713*tracemu2*
      Power6(g1) + 0.32203637214014313*tracemd2*Power6(g3) + 0.6440727442802863
      *tracemq2*Power6(g3) + 0.32203637214014313*tracemu2*Power6(g3) +
      0.03381381907471503*MassB*traceAdjTYdYd*Quad(g1) + 0.04347491023891932*
      MassB*traceAdjTYeYe*Quad(g1) + 0.0627970925673279*MassB*traceAdjTYuYu*
      Quad(g1) - 0.020288291444829017*mHd2*traceAdjYdYd*Quad(g1) -
      0.020288291444829017*traceAdjYdYdmq2*Quad(g1) - 0.026084946143351592*mHd2
      *traceAdjYeYe*Quad(g1) - 0.026084946143351592*traceAdjYeYeml2*Quad(g1) -
      0.03767825554039675*mHu2*traceAdjYuYu*Quad(g1) - 0.03767825554039675*
      traceAdjYuYumq2*Quad(g1) - 0.020288291444829017*traceTYdAdjTYd*Quad(g1) +
      0.03381381907471503*MassB*traceTYdAdjYd*Quad(g1) - 0.026084946143351592*
      traceTYeAdjTYe*Quad(g1) + 0.04347491023891932*MassB*traceTYeAdjYe*Quad(g1
      ) - 0.03767825554039675*traceTYuAdjTYu*Quad(g1) + 0.0627970925673279*
      MassB*traceTYuAdjYu*Quad(g1) - 0.020288291444829017*traceYdAdjYdmd2*Quad(
      g1) - 0.026084946143351592*traceYeAdjYeme2*Quad(g1) - 0.03767825554039675
      *traceYuAdjYumu2*Quad(g1) + 0.9661091164204294*MassG*traceAdjTYdYd*Quad(
      g3) + 0.9661091164204294*MassG*traceAdjTYuYu*Quad(g3) -
      0.5796654698522576*mHd2*traceAdjYdYd*Quad(g3) - 0.5796654698522576*
      traceAdjYdYdmq2*Quad(g3) - 0.5796654698522576*mHu2*traceAdjYuYu*Quad(g3)
      - 0.5796654698522576*traceAdjYuYumq2*Quad(g3) - 0.5796654698522576*
      traceTYdAdjTYd*Quad(g3) + 0.9661091164204294*MassG*traceTYdAdjYd*Quad(g3)
      - 0.5796654698522576*traceTYuAdjTYu*Quad(g3) + 0.9661091164204294*MassG*
      traceTYuAdjYu*Quad(g3) - 0.5796654698522576*traceYdAdjYdmd2*Quad(g3) -
      0.5796654698522576*traceYuAdjYumu2*Quad(g3) - 0.8051377339934198*MassB*
      MassG*Quad(g3)*Sqr(g1) - 0.012881454885605725*tracemd2*Quad(g3)*Sqr(g1) -
      0.02576290977121145*tracemq2*Quad(g3)*Sqr(g1) - 0.012881454885605725*
      tracemu2*Quad(g3)*Sqr(g1) - 0.05770880676421415*MassB*MassWB*Quad(g1)*Sqr
      (g2) - 1.9236268921404711*MassG*MassWB*Quad(g3)*Sqr(g2) -
      0.37873349509403303*MassB*MassG*Quad(g1)*Sqr(g3) - 0.0077288729313634355*
      mHd2*Quad(g1)*Sqr(g3) - 0.0077288729313634355*mHu2*Quad(g1)*Sqr(g3) -
      0.00515258195424229*tracemd2*Quad(g1)*Sqr(g3) - 0.015457745862726871*
      traceme2*Quad(g1)*Sqr(g3) - 0.0077288729313634355*traceml2*Quad(g1)*Sqr(
      g3) - 0.002576290977121145*tracemq2*Quad(g1)*Sqr(g3) -
      0.02061032781696916*tracemu2*Quad(g1)*Sqr(g3) + 1.*Power6(g1)*Sqr(MassB)
      - 0.10144145722414508*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.13042473071675798*traceAdjYeYe*Quad(g1)*Sqr(MassB) -
      0.18839127770198372*traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.2962968641904627
      *Quad(g3)*Sqr(g1)*Sqr(MassB) - 0.08656321014632122*Quad(g1)*Sqr(g2)*Sqr(
      MassB) - 0.5681002426410495*Quad(g1)*Sqr(g3)*Sqr(MassB) +
      104.25743700128189*Power6(g3)*Sqr(MassG) - 2.898327349261288*traceAdjYdYd
      *Quad(g3)*Sqr(MassG) - 2.898327349261288*traceAdjYuYu*Quad(g3)*Sqr(MassG)
      - 1.1304178716764948*Quad(g3)*Sqr(g1)*Sqr(MassG) - 2.885440338210707*Quad
      (g3)*Sqr(g2)*Sqr(MassG) - 0.1468579464245176*Quad(g1)*Sqr(g3)*Sqr(MassG)
      - 0.015811930310431276*Quad(g1)*Sqr(g2)*Sqr(MassWB) - 0.5270643436810423*
      Quad(g3)*Sqr(g2)*Sqr(MassWB)) - 134.8*threeLoop*(-1.0682492581602372*
      traceAdjTYdTYdAdjYdYd - 0.17804154302670622*traceAdjTYdTYdAdjYuYu -
      0.35608308605341243*traceAdjTYeTYeAdjYeYe - 0.17804154302670622*
      traceAdjTYuTYuAdjYdYd - 1.0682492581602372*traceAdjYdTYdAdjTYdYd +
      0.17022749752720076*mHd2*Quad(g1) + 0.003560830860534124*mHu2*Quad(g1) +
      0.7344213649851632*mHd2*Quad(g2) + 0.08902077151335311*mHu2*Quad(g2) -
      0.0791295746785361*mHd2*Quad(g3) + 0.10385756676557863*MassB*
      traceAdjTYdYd*Sqr(g1) - 0.044510385756676554*MassB*traceAdjTYeYe*Sqr(g1)
      + 0.400593471810089*MassWB*traceAdjTYdYd*Sqr(g2) + 0.13353115727002965*
      MassWB*traceAdjTYeYe*Sqr(g2) + 0.2551928783382789*MassB*MassWB*Sqr(g1)*
      Sqr(g2) + 0.12759643916913946*mHd2*Sqr(g1)*Sqr(g2) - 0.2373887240356083*
      MassG*traceAdjTYdYd*Sqr(g3) + 0.2373887240356083*MassG*traceAdjTYeYe*Sqr(
      g3) + 0.14243323442136496*MassB*MassG*Sqr(g1)*Sqr(g3) +
      0.07121661721068248*mHd2*Sqr(g1)*Sqr(g3) + 2.611275964391691*MassG*MassWB
      *Sqr(g2)*Sqr(g3) + 1.3056379821958455*mHd2*Sqr(g2)*Sqr(g3) + 1.*Quad(g1)*
      Sqr(MassB) + 0.2551928783382789*Sqr(g1)*Sqr(g2)*Sqr(MassB) +
      0.14243323442136496*Sqr(g1)*Sqr(g3)*Sqr(MassB) - 0.4747774480712166*Quad(
      g3)*Sqr(MassG) + 0.14243323442136496*Sqr(g1)*Sqr(g3)*Sqr(MassG) +
      2.611275964391691*Sqr(g2)*Sqr(g3)*Sqr(MassG) + 3.516320474777448*Quad(g2)
      *Sqr(MassWB) + 0.2551928783382789*Sqr(g1)*Sqr(g2)*Sqr(MassWB) +
      2.611275964391691*Sqr(g2)*Sqr(g3)*Sqr(MassWB))*(Yd*Yd.adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_2 = ((-0.32*threeLoop*(-675.*mHd2*
      traceAdjYdYdAdjYdYd - 449.9999999999999*traceAdjYdYdAdjYdYdmq2 - 75.*
      traceAdjYdYdAdjYuYumq2 + 224.99999999999994*traceAdjYdYd*traceAdjYdYdmq2
      - 150.*traceAdjYeTYeAdjTYeYe + 224.99999999999994*mHd2*traceAdjYdYd*
      traceAdjYeYe + 75.*traceAdjYdYdmq2*traceAdjYeYe - 224.99999999999994*mHd2
      *traceAdjYeYeAdjYeYe - 150.*traceAdjYeYeAdjYeYeml2 + 75.*traceAdjYdYd*
      traceAdjYeYeml2 + 25.*traceAdjYeYe*traceAdjYeYeml2 - 75.*
      traceAdjYuTYuAdjTYdYd - 150.*mHd2*traceAdjYuYuAdjYdYd - 75.*mHu2*
      traceAdjYuYuAdjYdYd - 75.*traceAdjYuYuAdjYdYdmq2 + 224.99999999999994*
      traceAdjYdYd*traceTYdAdjTYd + 75.*traceAdjYeYe*traceTYdAdjTYd - 75.*
      traceTYdAdjTYuYuAdjYd + 224.99999999999994*traceAdjTYdYd*traceTYdAdjYd +
      75.*traceAdjTYeYe*traceTYdAdjYd + 75.*traceAdjYdYd*traceTYeAdjTYe + 25.*
      traceAdjYeYe*traceTYeAdjTYe + 75.*traceAdjTYdYd*traceTYeAdjYe + 25.*
      traceAdjTYeYe*traceTYeAdjYe + 224.99999999999994*traceAdjYdYd*
      traceYdAdjYdmd2 + 75.*traceAdjYeYe*traceYdAdjYdmd2 - 449.9999999999999*
      traceYdAdjYdYdAdjYdmd2 - 75.*traceYdAdjYuYuAdjYdmd2 + 75.*traceAdjYdYd*
      traceYeAdjYeme2 + 25.*traceAdjYeYe*traceYeAdjYeme2 - 150.*
      traceYeAdjYeYeAdjYeme2 - 75.*traceYuAdjYdYdAdjYumu2 + 1.*tracemd2*Quad(g1
      ) + 3.*traceme2*Quad(g1) + 1.5*traceml2*Quad(g1) + 0.5*tracemq2*Quad(g1)
      + 4.*tracemu2*Quad(g1) + 37.5*traceml2*Quad(g2) + 112.49999999999997*
      tracemq2*Quad(g2) - 87.50000000000001*mHd2*traceAdjYdYd*Sqr(g1) -
      43.75000000000001*traceAdjYdYdmq2*Sqr(g1) + 37.5*mHd2*traceAdjYeYe*Sqr(g1
      ) + 18.75*traceAdjYeYeml2*Sqr(g1) - 43.75000000000001*traceTYdAdjTYd*Sqr(
      g1) + 43.75000000000001*MassB*traceTYdAdjYd*Sqr(g1) + 18.75*
      traceTYeAdjTYe*Sqr(g1) - 18.75*MassB*traceTYeAdjYe*Sqr(g1) -
      43.75000000000001*traceYdAdjYdmd2*Sqr(g1) + 18.75*traceYeAdjYeme2*Sqr(g1)
      - 337.5*mHd2*traceAdjYdYd*Sqr(g2) - 168.75*traceAdjYdYdmq2*Sqr(g2) -
      112.49999999999997*mHd2*traceAdjYeYe*Sqr(g2) - 56.249999999999986*
      traceAdjYeYeml2*Sqr(g2) - 168.75*traceTYdAdjTYd*Sqr(g2) + 168.75*MassWB*
      traceTYdAdjYd*Sqr(g2) - 56.249999999999986*traceTYeAdjTYe*Sqr(g2) +
      56.249999999999986*MassWB*traceTYeAdjYe*Sqr(g2) - 168.75*traceYdAdjYdmd2*
      Sqr(g2) - 56.249999999999986*traceYeAdjYeme2*Sqr(g2) + 200.*mHd2*
      traceAdjYdYd*Sqr(g3) + 100.*traceAdjYdYdmq2*Sqr(g3) - 200.*mHd2*
      traceAdjYeYe*Sqr(g3) - 100.*traceAdjYeYeml2*Sqr(g3) + 100.*traceTYdAdjTYd
      *Sqr(g3) - 100.*MassG*traceTYdAdjYd*Sqr(g3) - 100.*traceTYeAdjTYe*Sqr(g3)
      + 100.*MassG*traceTYeAdjYe*Sqr(g3) + 100.*traceYdAdjYdmd2*Sqr(g3) - 100.*
      traceYeAdjYeme2*Sqr(g3) - 87.50000000000001*traceAdjYdYd*Sqr(g1)*Sqr(
      MassB) + 37.5*traceAdjYeYe*Sqr(g1)*Sqr(MassB) + 200.*traceAdjYdYd*Sqr(g3)
      *Sqr(MassG) - 200.*traceAdjYeYe*Sqr(g3)*Sqr(MassG) - 337.5*traceAdjYdYd*
      Sqr(g2)*Sqr(MassWB) - 112.49999999999997*traceAdjYeYe*Sqr(g2)*Sqr(MassWB)
      + 337.5*mHd2*Sqr(traceAdjYdYd) + 37.5*mHd2*Sqr(traceAdjYeYe))*(Yd*Yd.
      adjoint()) + 44.93333333333333*threeLoop*(3.2047477744807122*
      traceAdjYdTYdAdjYdYd + 1.0682492581602374*traceAdjYeTYeAdjYeYe +
      0.5341246290801187*traceAdjYuTYuAdjYdYd - 1.6023738872403561*traceAdjYdYd
      *traceTYdAdjYd - 0.5341246290801187*traceAdjYeYe*traceTYdAdjYd + 1.*MassB
      *Quad(g1) + 3.8724035608308607*MassWB*Quad(g2) - 0.47477744807121663*
      MassG*Quad(g3) - 0.31157270029673595*MassB*traceAdjYdYd*Sqr(g1) +
      0.13353115727002968*MassB*traceAdjYeYe*Sqr(g1) + 0.31157270029673595*
      traceTYdAdjYd*Sqr(g1) - 1.2017804154302671*MassWB*traceAdjYdYd*Sqr(g2) -
      0.40059347181008903*MassWB*traceAdjYeYe*Sqr(g2) + 1.2017804154302671*
      traceTYdAdjYd*Sqr(g2) + 0.3827893175074184*MassB*Sqr(g1)*Sqr(g2) +
      0.3827893175074184*MassWB*Sqr(g1)*Sqr(g2) + 0.712166172106825*MassG*
      traceAdjYdYd*Sqr(g3) - 0.712166172106825*MassG*traceAdjYeYe*Sqr(g3) -
      0.712166172106825*traceTYdAdjYd*Sqr(g3) + 0.2136498516320475*MassB*Sqr(g1
      )*Sqr(g3) + 0.2136498516320475*MassG*Sqr(g1)*Sqr(g3) + 3.9169139465875373
      *MassG*Sqr(g2)*Sqr(g3) + 3.9169139465875373*MassWB*Sqr(g2)*Sqr(g3))*(Yd*(
      TYd).adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_3 = ((24.*threeLoop*(1.*
      traceTYdAdjYuYuAdjYd - 1.*traceAdjYdYd*traceTYeAdjYe - 0.3333333333333333
      *traceAdjYeYe*traceTYeAdjYe - 0.25*traceTYeAdjYe*Sqr(g1) + 0.75*
      traceTYeAdjYe*Sqr(g2) + 1.3333333333333333*traceTYeAdjYe*Sqr(g3))*(Yd*(
      TYd).adjoint()) + 44.93333333333333*threeLoop*(0.5341246290801187*
      traceAdjTYuYuAdjYdYd - 1.6023738872403561*traceAdjTYdYd*traceAdjYdYd -
      0.5341246290801187*traceAdjTYeYe*traceAdjYdYd + 3.2047477744807122*
      traceAdjYdYdAdjTYdYd - 0.5341246290801187*traceAdjTYdYd*traceAdjYeYe -
      0.17804154302670624*traceAdjTYeYe*traceAdjYeYe + 1.0682492581602374*
      traceAdjYeYeAdjTYeYe + 0.5341246290801187*traceAdjYuYuAdjTYdYd + 1.*MassB
      *Quad(g1) + 3.8724035608308607*MassWB*Quad(g2) - 0.47477744807121663*
      MassG*Quad(g3) + 0.31157270029673595*traceAdjTYdYd*Sqr(g1) -
      0.13353115727002968*traceAdjTYeYe*Sqr(g1) - 0.31157270029673595*MassB*
      traceAdjYdYd*Sqr(g1) + 0.13353115727002968*MassB*traceAdjYeYe*Sqr(g1) +
      1.2017804154302671*traceAdjTYdYd*Sqr(g2) + 0.40059347181008903*
      traceAdjTYeYe*Sqr(g2) - 1.2017804154302671*MassWB*traceAdjYdYd*Sqr(g2) -
      0.40059347181008903*MassWB*traceAdjYeYe*Sqr(g2) + 0.3827893175074184*
      MassB*Sqr(g1)*Sqr(g2) + 0.3827893175074184*MassWB*Sqr(g1)*Sqr(g2) -
      0.712166172106825*traceAdjTYdYd*Sqr(g3) + 0.712166172106825*traceAdjTYeYe
      *Sqr(g3) + 0.712166172106825*MassG*traceAdjYdYd*Sqr(g3) -
      0.712166172106825*MassG*traceAdjYeYe*Sqr(g3) + 0.2136498516320475*MassB*
      Sqr(g1)*Sqr(g3) + 0.2136498516320475*MassG*Sqr(g1)*Sqr(g3) +
      3.9169139465875373*MassG*Sqr(g2)*Sqr(g3) + 3.9169139465875373*MassWB*Sqr(
      g2)*Sqr(g3))*(TYd*Yd.adjoint()) - 22.466666666666665*threeLoop*(-
      3.2047477744807122*traceAdjYdYdAdjYdYd + 1.0682492581602374*traceAdjYdYd*
      traceAdjYeYe - 1.0682492581602374*traceAdjYeYeAdjYeYe -
      1.0682492581602374*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 3.8724035608308607
      *Quad(g2) - 0.47477744807121663*Quad(g3) - 0.6231454005934719*
      traceAdjYdYd*Sqr(g1) + 0.26706231454005935*traceAdjYeYe*Sqr(g1) -
      2.4035608308605343*traceAdjYdYd*Sqr(g2) - 0.8011869436201781*traceAdjYeYe
      *Sqr(g2) + 0.7655786350148368*Sqr(g1)*Sqr(g2) + 1.42433234421365*
      traceAdjYdYd*Sqr(g3) - 1.42433234421365*traceAdjYeYe*Sqr(g3) +
      0.427299703264095*Sqr(g1)*Sqr(g3) + 7.833827893175075*Sqr(g2)*Sqr(g3) +
      1.6023738872403561*Sqr(traceAdjYdYd) + 0.17804154302670624*Sqr(
      traceAdjYeYe))*(TYd*(TYd).adjoint()) - 11.233333333333333*threeLoop*(-
      3.2047477744807122*traceAdjYdYdAdjYdYd + 1.0682492581602374*traceAdjYdYd*
      traceAdjYeYe - 1.0682492581602374*traceAdjYeYeAdjYeYe -
      1.0682492581602374*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 3.8724035608308607
      *Quad(g2) - 0.47477744807121663*Quad(g3) - 0.6231454005934719*
      traceAdjYdYd*Sqr(g1) + 0.26706231454005935*traceAdjYeYe*Sqr(g1) -
      2.4035608308605343*traceAdjYdYd*Sqr(g2) - 0.8011869436201781*traceAdjYeYe
      *Sqr(g2) + 0.7655786350148368*Sqr(g1)*Sqr(g2) + 1.42433234421365*
      traceAdjYdYd*Sqr(g3) - 1.42433234421365*traceAdjYeYe*Sqr(g3) +
      0.427299703264095*Sqr(g1)*Sqr(g3) + 7.833827893175075*Sqr(g2)*Sqr(g3) +
      1.6023738872403561*Sqr(traceAdjYdYd) + 0.17804154302670624*Sqr(
      traceAdjYeYe))*(md2*Yd*Yd.adjoint()) - 22.466666666666665*threeLoop*(-
      3.2047477744807122*traceAdjYdYdAdjYdYd + 1.0682492581602374*traceAdjYdYd*
      traceAdjYeYe - 1.0682492581602374*traceAdjYeYeAdjYeYe -
      1.0682492581602374*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 3.8724035608308607
      *Quad(g2) - 0.47477744807121663*Quad(g3) - 0.6231454005934719*
      traceAdjYdYd*Sqr(g1) + 0.26706231454005935*traceAdjYeYe*Sqr(g1) -
      2.4035608308605343*traceAdjYdYd*Sqr(g2) - 0.8011869436201781*traceAdjYeYe
      *Sqr(g2) + 0.7655786350148368*Sqr(g1)*Sqr(g2) + 1.42433234421365*
      traceAdjYdYd*Sqr(g3) - 1.42433234421365*traceAdjYeYe*Sqr(g3) +
      0.427299703264095*Sqr(g1)*Sqr(g3) + 7.833827893175075*Sqr(g2)*Sqr(g3) +
      1.6023738872403561*Sqr(traceAdjYdYd) + 0.17804154302670624*Sqr(
      traceAdjYeYe))*(Yd*mq2*Yd.adjoint()) - 1.12*(-30.*MassB*MassWB*threeLoop*
      Sqr(g1)*Sqr(g2) - 38.09523809523809*MassB*MassG*threeLoop*Sqr(g1)*Sqr(g3)
      - 342.85714285714283*MassG*MassWB*threeLoop*Sqr(g2)*Sqr(g3) + 1.*
      threeLoop*Quad(g1)*Sqr(MassB) - 30.*threeLoop*Sqr(g1)*Sqr(g2)*Sqr(MassB)
      - 38.09523809523809*threeLoop*Sqr(g1)*Sqr(g3)*Sqr(MassB) +
      1942.8571428571427*threeLoop*Quad(g3)*Sqr(MassG) - 38.09523809523809*
      threeLoop*Sqr(g1)*Sqr(g3)*Sqr(MassG) - 342.85714285714283*threeLoop*Sqr(
      g2)*Sqr(g3)*Sqr(MassG) + 96.42857142857142*threeLoop*Quad(g2)*Sqr(MassWB)
      - 30.*threeLoop*Sqr(g1)*Sqr(g2)*Sqr(MassWB))*(Yd*Yd.adjoint()*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_4 = ((-18.*threeLoop*(
      0.01037037037037037*mHd2*Quad(g1) + 1.*mHd2*Quad(g2) + 20.14814814814815*
      mHd2*Quad(g3) - 0.6666666666666666*MassB*traceAdjTYdYd*Sqr(g1) +
      0.6666666666666666*MassB*traceAdjTYeYe*Sqr(g1) + 1.3333333333333333*mHd2*
      traceAdjYdYd*Sqr(g1) + 0.6666666666666666*traceAdjYdYdmq2*Sqr(g1) -
      1.3333333333333333*mHd2*traceAdjYeYe*Sqr(g1) - 0.6666666666666666*
      traceAdjYeYeml2*Sqr(g1) + 0.6666666666666666*traceTYdAdjTYd*Sqr(g1) -
      0.6666666666666666*MassB*traceTYdAdjYd*Sqr(g1) - 0.6666666666666666*
      traceTYeAdjTYe*Sqr(g1) + 0.6666666666666666*MassB*traceTYeAdjYe*Sqr(g1) +
      0.6666666666666666*traceYdAdjYdmd2*Sqr(g1) - 0.6666666666666666*
      traceYeAdjYeme2*Sqr(g1) - 6.*MassWB*traceAdjTYdYd*Sqr(g2) - 2.*MassWB*
      traceAdjTYeYe*Sqr(g2) + 12.*mHd2*traceAdjYdYd*Sqr(g2) + 6.*
      traceAdjYdYdmq2*Sqr(g2) + 4.*mHd2*traceAdjYeYe*Sqr(g2) + 2.*
      traceAdjYeYeml2*Sqr(g2) + 6.*traceTYdAdjTYd*Sqr(g2) - 6.*MassWB*
      traceTYdAdjYd*Sqr(g2) + 2.*traceTYeAdjTYe*Sqr(g2) - 2.*MassWB*
      traceTYeAdjYe*Sqr(g2) + 6.*traceYdAdjYdmd2*Sqr(g2) + 2.*traceYeAdjYeme2*
      Sqr(g2) - 0.9333333333333333*mHd2*Sqr(g1)*Sqr(g2) + 10.666666666666666*
      MassG*traceAdjTYdYd*Sqr(g3) - 21.333333333333332*mHd2*traceAdjYdYd*Sqr(g3
      ) - 10.666666666666666*traceAdjYdYdmq2*Sqr(g3) - 10.666666666666666*
      traceTYdAdjTYd*Sqr(g3) + 10.666666666666666*MassG*traceTYdAdjYd*Sqr(g3) -
      10.666666666666666*traceYdAdjYdmd2*Sqr(g3) - 1.1851851851851851*mHd2*Sqr(
      g1)*Sqr(g3) - 10.666666666666666*mHd2*Sqr(g2)*Sqr(g3) +
      1.3333333333333333*traceAdjYdYd*Sqr(g1)*Sqr(MassB) - 1.3333333333333333*
      traceAdjYeYe*Sqr(g1)*Sqr(MassB) - 21.333333333333332*traceAdjYdYd*Sqr(g3)
      *Sqr(MassG) + 12.*traceAdjYdYd*Sqr(g2)*Sqr(MassWB) + 4.*traceAdjYeYe*Sqr(
      g2)*Sqr(MassWB) - 21.333333333333332*Sqr(g2)*Sqr(g3)*Sqr(MassWB))*(Yd*Yd.
      adjoint()*1.2020569031595942) - 11.233333333333333*threeLoop*(-
      3.2047477744807122*traceAdjYdYdAdjYdYd + 1.0682492581602374*traceAdjYdYd*
      traceAdjYeYe - 1.0682492581602374*traceAdjYeYeAdjYeYe -
      1.0682492581602374*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 3.8724035608308607
      *Quad(g2) - 0.47477744807121663*Quad(g3) - 0.6231454005934719*
      traceAdjYdYd*Sqr(g1) + 0.26706231454005935*traceAdjYeYe*Sqr(g1) -
      2.4035608308605343*traceAdjYdYd*Sqr(g2) - 0.8011869436201781*traceAdjYeYe
      *Sqr(g2) + 0.7655786350148368*Sqr(g1)*Sqr(g2) + 1.42433234421365*
      traceAdjYdYd*Sqr(g3) - 1.42433234421365*traceAdjYeYe*Sqr(g3) +
      0.427299703264095*Sqr(g1)*Sqr(g3) + 7.833827893175075*Sqr(g2)*Sqr(g3) +
      1.6023738872403561*Sqr(traceAdjYdYd) + 0.17804154302670624*Sqr(
      traceAdjYeYe))*(Yd*Yd.adjoint()*md2) + 0.3733333333333333*threeLoop*(1.*
      MassB*Quad(g1) + 96.42857142857144*MassWB*Quad(g2) + 1942.8571428571431*
      MassG*Quad(g3) + 32.14285714285714*MassB*traceAdjYdYd*Sqr(g1) -
      32.14285714285714*MassB*traceAdjYeYe*Sqr(g1) - 32.14285714285714*
      traceTYdAdjYd*Sqr(g1) + 32.14285714285714*traceTYeAdjYe*Sqr(g1) +
      289.28571428571433*MassWB*traceAdjYdYd*Sqr(g2) + 96.42857142857144*MassWB
      *traceAdjYeYe*Sqr(g2) - 289.28571428571433*traceTYdAdjYd*Sqr(g2) -
      96.42857142857144*traceTYeAdjYe*Sqr(g2) - 45.00000000000001*MassB*Sqr(g1)
      *Sqr(g2) - 45.00000000000001*MassWB*Sqr(g1)*Sqr(g2) - 514.2857142857142*
      MassG*traceAdjYdYd*Sqr(g3) + 514.2857142857142*traceTYdAdjYd*Sqr(g3) -
      57.142857142857146*MassB*Sqr(g1)*Sqr(g3) - 57.142857142857146*MassG*Sqr(
      g1)*Sqr(g3) - 514.2857142857142*MassG*Sqr(g2)*Sqr(g3) - 514.2857142857142
      *MassWB*Sqr(g2)*Sqr(g3))*(Yd*(TYd).adjoint()*1.2020569031595942) +
      0.3733333333333333*threeLoop*(1.*MassB*Quad(g1) + 96.42857142857144*
      MassWB*Quad(g2) + 1942.8571428571431*MassG*Quad(g3) - 32.14285714285714*
      traceAdjTYdYd*Sqr(g1) + 32.14285714285714*traceAdjTYeYe*Sqr(g1) +
      32.14285714285714*MassB*traceAdjYdYd*Sqr(g1) - 32.14285714285714*MassB*
      traceAdjYeYe*Sqr(g1) - 289.28571428571433*traceAdjTYdYd*Sqr(g2) -
      96.42857142857144*traceAdjTYeYe*Sqr(g2) + 289.28571428571433*MassWB*
      traceAdjYdYd*Sqr(g2) + 96.42857142857144*MassWB*traceAdjYeYe*Sqr(g2) -
      45.00000000000001*MassB*Sqr(g1)*Sqr(g2) - 45.00000000000001*MassWB*Sqr(g1
      )*Sqr(g2) + 514.2857142857142*traceAdjTYdYd*Sqr(g3) - 514.2857142857142*
      MassG*traceAdjYdYd*Sqr(g3) - 57.142857142857146*MassB*Sqr(g1)*Sqr(g3) -
      57.142857142857146*MassG*Sqr(g1)*Sqr(g3) - 514.2857142857142*MassG*Sqr(g2
      )*Sqr(g3) - 514.2857142857142*MassWB*Sqr(g2)*Sqr(g3))*(TYd*Yd.adjoint()*
      1.2020569031595942) - 0.18666666666666665*Sqr(g1)*(1.*threeLoop*Sqr(g1) -
      90.00000000000001*threeLoop*Sqr(g2))*(TYd*(TYd).adjoint()*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_5 = ((-18.*threeLoop*(1.*Quad(g2) +
      20.14814814814815*Quad(g3) + 0.6666666666666665*traceAdjYdYd*Sqr(g1) -
      0.6666666666666665*traceAdjYeYe*Sqr(g1) + 6.*traceAdjYdYd*Sqr(g2) + 2.*
      traceAdjYeYe*Sqr(g2) - 10.666666666666664*traceAdjYdYd*Sqr(g3) -
      1.1851851851851851*Sqr(g1)*Sqr(g3) - 10.666666666666664*Sqr(g2)*Sqr(g3))*
      (TYd*(TYd).adjoint()*1.2020569031595942) - 0.09333333333333332*threeLoop*
      (1.*Quad(g1) + 96.42857142857144*Quad(g2) + 1942.8571428571431*Quad(g3) +
      64.28571428571428*traceAdjYdYd*Sqr(g1) - 64.28571428571428*traceAdjYeYe*
      Sqr(g1) + 578.5714285714287*traceAdjYdYd*Sqr(g2) + 192.8571428571429*
      traceAdjYeYe*Sqr(g2) - 90.00000000000001*Sqr(g1)*Sqr(g2) -
      1028.5714285714284*traceAdjYdYd*Sqr(g3) - 114.28571428571429*Sqr(g1)*Sqr(
      g3) - 1028.5714285714284*Sqr(g2)*Sqr(g3))*(md2*Yd*Yd.adjoint()*
      1.2020569031595942) - 0.18666666666666665*threeLoop*(1.*Quad(g1) +
      96.42857142857144*Quad(g2) + 1942.8571428571431*Quad(g3) +
      64.28571428571428*traceAdjYdYd*Sqr(g1) - 64.28571428571428*traceAdjYeYe*
      Sqr(g1) + 578.5714285714287*traceAdjYdYd*Sqr(g2) + 192.8571428571429*
      traceAdjYeYe*Sqr(g2) - 90.00000000000001*Sqr(g1)*Sqr(g2) -
      1028.5714285714284*traceAdjYdYd*Sqr(g3) - 114.28571428571429*Sqr(g1)*Sqr(
      g3) - 1028.5714285714284*Sqr(g2)*Sqr(g3))*(Yd*mq2*Yd.adjoint()*
      1.2020569031595942) - 0.09333333333333332*threeLoop*(1.*Quad(g1) +
      96.42857142857144*Quad(g2) + 1942.8571428571431*Quad(g3) +
      64.28571428571428*traceAdjYdYd*Sqr(g1) - 64.28571428571428*traceAdjYeYe*
      Sqr(g1) + 578.5714285714287*traceAdjYdYd*Sqr(g2) + 192.8571428571429*
      traceAdjYeYe*Sqr(g2) - 90.00000000000001*Sqr(g1)*Sqr(g2) -
      1028.5714285714284*traceAdjYdYd*Sqr(g3) - 114.28571428571429*Sqr(g1)*Sqr(
      g3) - 1028.5714285714284*Sqr(g2)*Sqr(g3))*(Yd*Yd.adjoint()*md2*
      1.2020569031595942) - 1.3333333333333333*threeLoop*(-27.*mHd2*
      traceAdjYdYd - 9.*traceAdjYdYdmq2 - 9.*mHd2*traceAdjYeYe - 3.*
      traceAdjYeYeml2 - 9.*traceTYdAdjTYd - 3.*traceTYeAdjTYe - 9.*
      traceYdAdjYdmd2 - 3.*traceYeAdjYeme2 + 1.*mHd2*Sqr(g1) - 27.*mHd2*Sqr(g2)
      - 64.*mHd2*Sqr(g3) + 1.*Sqr(g1)*Sqr(MassB) - 64.*Sqr(g3)*Sqr(MassG) - 27.
      *Sqr(g2)*Sqr(MassWB))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()) +
      0.6666666666666666*threeLoop*(18.*traceTYdAdjYd + 6.*traceTYeAdjYe + 1.*
      MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr(g3))*(Yd*Yd.adjoint()*
      Yd*(TYd).adjoint()) + 0.6666666666666666*threeLoop*(18.*traceAdjTYdYd +
      6.*traceAdjTYeYe + 1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr(
      g3))*(Yd*Yd.adjoint()*TYd*Yd.adjoint()) - 0.6666666666666666*threeLoop*(-
      18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(
      g3))*(Yd*Yd.adjoint()*TYd*(TYd).adjoint()) - 7.7333333333333325*threeLoop
      *(3.1034482758620694*mHd2*traceAdjYdYd + 1.5517241379310347*mHu2*
      traceAdjYdYd + 1.5517241379310347*traceAdjYdYdmq2 + 1.0344827586206897*
      mHd2*traceAdjYeYe + 0.5172413793103449*mHu2*traceAdjYeYe +
      0.5172413793103449*traceAdjYeYeml2 - 3.1034482758620694*mHd2*traceAdjYuYu
       - 6.206896551724139*mHu2*traceAdjYuYu - 3.1034482758620694*
      traceAdjYuYumq2 + 1.5517241379310347*traceTYdAdjTYd + 0.5172413793103449*
      traceTYeAdjTYe - 3.1034482758620694*traceTYuAdjTYu + 1.5517241379310347*
      traceYdAdjYdmd2 + 0.5172413793103449*traceYeAdjYeme2 - 3.1034482758620694
      *traceYuAdjYumu2 + 0.5*mHd2*Sqr(g1) + 0.5*mHu2*Sqr(g1) -
      2.327586206896552*mHd2*Sqr(g2) - 2.327586206896552*mHu2*Sqr(g2) -
      5.517241379310345*mHd2*Sqr(g3) - 5.517241379310345*mHu2*Sqr(g3) + 1.*Sqr(
      g1)*Sqr(MassB) - 11.03448275862069*Sqr(g3)*Sqr(MassG) - 4.655172413793104
      *Sqr(g2)*Sqr(MassWB))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()) +
      3.8666666666666663*threeLoop*(-3.1034482758620694*traceTYdAdjYd -
      1.0344827586206897*traceTYeAdjYe + 1.*MassB*Sqr(g1) - 4.655172413793104*
      MassWB*Sqr(g2) - 11.03448275862069*MassG*Sqr(g3))*(Yd*Yu.adjoint()*Yu*(
      TYd).adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_6 = ((24.*threeLoop*traceTYuAdjYu*(
      Yd*Yu.adjoint()*Yu*(TYd).adjoint()) + 3.8666666666666663*threeLoop*(-
      3.1034482758620694*traceAdjTYdYd - 1.0344827586206897*traceAdjTYeYe +
      6.206896551724139*traceAdjTYuYu + 1.*MassB*Sqr(g1) - 4.655172413793104*
      MassWB*Sqr(g2) - 11.03448275862069*MassG*Sqr(g3))*(Yd*Yu.adjoint()*TYu*Yd
      .adjoint()) - 3.8666666666666663*threeLoop*(3.1034482758620694*
      traceAdjYdYd + 1.0344827586206897*traceAdjYeYe - 6.206896551724139*
      traceAdjYuYu + 1.*Sqr(g1) - 4.655172413793104*Sqr(g2) - 11.03448275862069
      *Sqr(g3))*(Yd*Yu.adjoint()*TYu*(TYd).adjoint()) + 0.6666666666666666*
      threeLoop*(18.*traceTYdAdjYd + 6.*traceTYeAdjYe + 1.*MassB*Sqr(g1) - 27.*
      MassWB*Sqr(g2) - 64.*MassG*Sqr(g3))*(Yd*(TYd).adjoint()*Yd*Yd.adjoint())
      - 0.6666666666666666*threeLoop*(-18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*
      Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yd*(TYd).adjoint()*TYd*Yd.adjoint()
      ) + 3.8666666666666663*threeLoop*(-3.1034482758620694*traceTYdAdjYd -
      1.0344827586206897*traceTYeAdjYe + 6.206896551724139*traceTYuAdjYu + 1.*
      MassB*Sqr(g1) - 4.655172413793104*MassWB*Sqr(g2) - 11.03448275862069*
      MassG*Sqr(g3))*(Yd*(TYu).adjoint()*Yu*Yd.adjoint()) - 3.8666666666666663*
      threeLoop*(3.1034482758620694*traceAdjYdYd + 1.0344827586206897*
      traceAdjYeYe - 6.206896551724139*traceAdjYuYu + 1.*Sqr(g1) -
      4.655172413793104*Sqr(g2) - 11.03448275862069*Sqr(g3))*(Yd*(TYu).adjoint(
      )*TYu*Yd.adjoint()) + 0.6666666666666666*threeLoop*(18.*traceAdjTYdYd +
      6.*traceAdjTYeYe + 1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr(
      g3))*(TYd*Yd.adjoint()*Yd*Yd.adjoint()) - 0.6666666666666666*threeLoop*(-
      18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(
      g3))*(TYd*Yd.adjoint()*Yd*(TYd).adjoint()) + 3.8666666666666663*threeLoop
      *(-3.1034482758620694*traceAdjTYdYd - 1.0344827586206897*traceAdjTYeYe +
      6.206896551724139*traceAdjTYuYu + 1.*MassB*Sqr(g1) - 4.655172413793104*
      MassWB*Sqr(g2) - 11.03448275862069*MassG*Sqr(g3))*(TYd*Yu.adjoint()*Yu*Yd
      .adjoint()) - 3.8666666666666663*threeLoop*(3.1034482758620694*
      traceAdjYdYd + 1.0344827586206897*traceAdjYeYe - 6.206896551724139*
      traceAdjYuYu + 1.*Sqr(g1) - 4.655172413793104*Sqr(g2) - 11.03448275862069
      *Sqr(g3))*(TYd*Yu.adjoint()*Yu*(TYd).adjoint()) - 0.6666666666666666*
      threeLoop*(-18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2)
      - 64.*Sqr(g3))*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()) - 3.8666666666666663
      *threeLoop*(3.1034482758620694*traceAdjYdYd + 1.0344827586206897*
      traceAdjYeYe - 6.206896551724139*traceAdjYuYu + 1.*Sqr(g1) -
      4.655172413793104*Sqr(g2) - 11.03448275862069*Sqr(g3))*(TYd*(TYu).adjoint
      ()*Yu*Yd.adjoint()) - 0.3333333333333333*threeLoop*(-18.*traceAdjYdYd -
      6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(md2*Yd*Yd.
      adjoint()*Yd*Yd.adjoint()) - 1.9333333333333331*threeLoop*(
      3.1034482758620694*traceAdjYdYd + 1.0344827586206897*traceAdjYeYe -
      6.206896551724139*traceAdjYuYu + 1.*Sqr(g1) - 4.655172413793104*Sqr(g2) -
      11.03448275862069*Sqr(g3))*(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()) -
      0.6666666666666666*threeLoop*(-18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*
      Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()
      ) - 3.8666666666666663*threeLoop*(3.1034482758620694*traceAdjYdYd +
      1.0344827586206897*traceAdjYeYe - 6.206896551724139*traceAdjYuYu + 1.*Sqr
      (g1) - 4.655172413793104*Sqr(g2) - 11.03448275862069*Sqr(g3))*(Yd*mq2*Yu.
      adjoint()*Yu*Yd.adjoint()) - 0.6666666666666666*threeLoop*(-18.*
      traceAdjYdYd - 6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*
      (Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()) - 0.6666666666666666*threeLoop*(-
      18.*traceAdjYdYd - 6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(
      g3))*(Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_7 = ((4.8*(1.*mHd2*threeLoop*Sqr(g1
      ) - 15.*mHd2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(MassB) - 15.*
      threeLoop*Sqr(g2)*Sqr(MassWB))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*
      1.2020569031595942) - 0.3333333333333333*threeLoop*(-18.*traceAdjYdYd -
      6.*traceAdjYeYe + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yd*Yd.adjoint(
      )*Yd*Yd.adjoint()*md2) - 2.4*(1.*MassB*threeLoop*Sqr(g1) - 15.*MassWB*
      threeLoop*Sqr(g2))*(Yd*Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942
      ) - 2.4*(1.*MassB*threeLoop*Sqr(g1) - 15.*MassWB*threeLoop*Sqr(g2))*(Yd*
      Yd.adjoint()*TYd*Yd.adjoint()*1.2020569031595942) + 2.4*(1.*threeLoop*Sqr
      (g1) - 15.*threeLoop*Sqr(g2))*(Yd*Yd.adjoint()*TYd*(TYd).adjoint()*
      1.2020569031595942) - 3.8666666666666663*threeLoop*(3.1034482758620694*
      traceAdjYdYd + 1.0344827586206897*traceAdjYeYe - 6.206896551724139*
      traceAdjYuYu + 1.*Sqr(g1) - 4.655172413793104*Sqr(g2) - 11.03448275862069
      *Sqr(g3))*(Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()) - 3.8666666666666663*
      threeLoop*(3.1034482758620694*traceAdjYdYd + 1.0344827586206897*
      traceAdjYeYe - 6.206896551724139*traceAdjYuYu + 1.*Sqr(g1) -
      4.655172413793104*Sqr(g2) - 11.03448275862069*Sqr(g3))*(Yd*Yu.adjoint()*
      Yu*mq2*Yd.adjoint()) + 14.400000000000002*(0.5*mHd2*threeLoop*Sqr(g1) +
      0.5*mHu2*threeLoop*Sqr(g1) - 2.4999999999999996*mHd2*threeLoop*Sqr(g2) -
      2.4999999999999996*mHu2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(
      MassB) - 4.999999999999999*threeLoop*Sqr(g2)*Sqr(MassWB))*(Yd*Yu.adjoint(
      )*Yu*Yd.adjoint()*1.2020569031595942) - 1.9333333333333331*threeLoop*(
      3.1034482758620694*traceAdjYdYd + 1.0344827586206897*traceAdjYeYe -
      6.206896551724139*traceAdjYuYu + 1.*Sqr(g1) - 4.655172413793104*Sqr(g2) -
      11.03448275862069*Sqr(g3))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*md2) -
      7.200000000000001*(1.*MassB*threeLoop*Sqr(g1) - 4.999999999999999*MassWB*
      threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*Yu*(TYd).adjoint()*1.2020569031595942
      ) - 7.200000000000001*(1.*MassB*threeLoop*Sqr(g1) - 4.999999999999999*
      MassWB*threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*TYu*Yd.adjoint()*
      1.2020569031595942) + 7.200000000000001*(1.*threeLoop*Sqr(g1) -
      4.999999999999999*threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*TYu*(TYd).adjoint()
      *1.2020569031595942) - 2.4*(1.*MassB*threeLoop*Sqr(g1) - 15.*MassWB*
      threeLoop*Sqr(g2))*(Yd*(TYd).adjoint()*Yd*Yd.adjoint()*1.2020569031595942
      ) + 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*(Yd*(TYd).adjoint(
      )*TYd*Yd.adjoint()*1.2020569031595942) - 7.200000000000001*(1.*MassB*
      threeLoop*Sqr(g1) - 4.999999999999999*MassWB*threeLoop*Sqr(g2))*(Yd*(TYu)
      .adjoint()*Yu*Yd.adjoint()*1.2020569031595942) + 7.200000000000001*(1.*
      threeLoop*Sqr(g1) - 4.999999999999999*threeLoop*Sqr(g2))*(Yd*(TYu).
      adjoint()*TYu*Yd.adjoint()*1.2020569031595942) - 2.4*(1.*MassB*threeLoop*
      Sqr(g1) - 15.*MassWB*threeLoop*Sqr(g2))*(TYd*Yd.adjoint()*Yd*Yd.adjoint()
      *1.2020569031595942) + 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))
      *(TYd*Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942) -
      7.200000000000001*(1.*MassB*threeLoop*Sqr(g1) - 4.999999999999999*MassWB*
      threeLoop*Sqr(g2))*(TYd*Yu.adjoint()*Yu*Yd.adjoint()*1.2020569031595942)
      + 7.200000000000001*(1.*threeLoop*Sqr(g1) - 4.999999999999999*threeLoop*
      Sqr(g2))*(TYd*Yu.adjoint()*Yu*(TYd).adjoint()*1.2020569031595942) + 2.4*(
      1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*(TYd*(TYd).adjoint()*Yd*Yd.
      adjoint()*1.2020569031595942) + 7.200000000000001*(1.*threeLoop*Sqr(g1) -
      4.999999999999999*threeLoop*Sqr(g2))*(TYd*(TYu).adjoint()*Yu*Yd.adjoint()
      *1.2020569031595942) + 1.2*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))
      *(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()*1.2020569031595942) +
      3.6000000000000005*(1.*threeLoop*Sqr(g1) - 4.999999999999999*threeLoop*
      Sqr(g2))*(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()*1.2020569031595942) + 2.4*(
      1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*(Yd*mq2*Yd.adjoint()*Yd*Yd.
      adjoint()*1.2020569031595942) + 7.200000000000001*(1.*threeLoop*Sqr(g1) -
      4.999999999999999*threeLoop*Sqr(g2))*(Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()
      *1.2020569031595942) + 2.4*(1.*threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))
      *(Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()*1.2020569031595942) + 2.4*(1.*
      threeLoop*Sqr(g1) - 15.*threeLoop*Sqr(g2))*(Yd*Yd.adjoint()*Yd*mq2*Yd.
      adjoint()*1.2020569031595942) + 1.2*(1.*threeLoop*Sqr(g1) - 15.*threeLoop
      *Sqr(g2))*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*1.2020569031595942) + 36.*
      mHd2*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*
      threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*TYd*(TYd).adjoint()) - 8.*(1.*
      mHd2*threeLoop + 0.5*mHu2*threeLoop)*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*
      Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*Yu.adjoint()*TYu*(TYd).
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*(TYd).adjoint()*TYd*Yd.
      adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*(TYu).adjoint()*TYu*Yd.
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*(TYd).
      adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*TYd*Yu.adjoint()*Yu*(TYd).
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*TYd*(TYd).adjoint()*Yd*Yd.
      adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*TYd*(TYu).adjoint()*Yu*Yd.
      adjoint()) + 7.200000000000001*(1.*threeLoop*Sqr(g1) - 4.999999999999999*
      threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()*
      1.2020569031595942) + 7.200000000000001*(1.*threeLoop*Sqr(g1) -
      4.999999999999999*threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()
      *1.2020569031595942) + 3.6000000000000005*(1.*threeLoop*Sqr(g1) -
      4.999999999999999*threeLoop*Sqr(g2))*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*md2
      *1.2020569031595942) - 8.*(1.*mHd2*threeLoop + 0.5*mHu2*threeLoop)*(Yd*Yu
      .adjoint()*Yu*Yd.adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint
      ()*Yu*Yd.adjoint()*TYd*(TYd).adjoint()) + 12.*mHd2*threeLoop*(Yd*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_md2_8 = ((24.*mHu2*threeLoop*(Yd*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint
      ()*Yu*Yu.adjoint()*TYu*(TYd).adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*
      Yu*(TYd).adjoint()*TYd*Yd.adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*Yu*
      (TYu).adjoint()*TYu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*TYu*Yd.
      adjoint()*Yd*(TYd).adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*TYu*Yu.
      adjoint()*Yu*(TYd).adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*TYu*(TYd).
      adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*TYu*(TYu).
      adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYd).adjoint()*Yd*Yd.
      adjoint()*TYd*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYd).adjoint()*Yd*Yu.
      adjoint()*TYu*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYd).adjoint()*TYd*Yd.
      adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYd).adjoint()*TYd*Yu.
      adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYu).adjoint()*Yu*Yd.
      adjoint()*TYd*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYu).adjoint()*Yu*Yu.
      adjoint()*TYu*Yd.adjoint()) - 4.*threeLoop*(Yd*(TYu).adjoint()*TYu*Yd.
      adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*(TYu).adjoint()*TYu*Yu.
      adjoint()*Yu*Yd.adjoint()) + 12.*threeLoop*(TYd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*(TYd).adjoint()) - 4.*threeLoop*(TYd*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu*(TYd).adjoint()) + 12.*threeLoop*(TYd*Yd.adjoint()*Yd*(TYd).
      adjoint()*Yd*Yd.adjoint()) - 4.*threeLoop*(TYd*Yd.adjoint()*Yd*(TYu).
      adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(TYd*Yu.adjoint()*Yu*Yd.adjoint
      ()*Yd*(TYd).adjoint()) + 12.*threeLoop*(TYd*Yu.adjoint()*Yu*Yu.adjoint()*
      Yu*(TYd).adjoint()) - 4.*threeLoop*(TYd*Yu.adjoint()*Yu*(TYd).adjoint()*
      Yd*Yd.adjoint()) + 12.*threeLoop*(TYd*Yu.adjoint()*Yu*(TYu).adjoint()*Yu*
      Yd.adjoint()) + 12.*threeLoop*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()) - 4.*threeLoop*(TYd*(TYd).adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()) - 4.*threeLoop*(TYd*(TYu).adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()) + 12.*threeLoop*(TYd*(TYu).adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()) + 6.*threeLoop*(md2*Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()) - 2.*threeLoop*(md2*Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()) - 2.*threeLoop*(md2*Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()) + 6.*threeLoop*(md2*Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()) + 12.*threeLoop*(Yd*mq2*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()) - 4.*threeLoop*(Yd*mq2*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()) - 4.*threeLoop*(Yd*mq2*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()) + 12.*threeLoop*(Yd*mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*md2*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*md2*Yd*Yu.adjoint()*Yu*Yd.
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*mq2*Yd.adjoint()*Yd*Yd.
      adjoint()) - 4.*threeLoop*(Yd*Yd.adjoint()*Yd*mq2*Yu.adjoint()*Yu*Yd.
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*md2*Yd*Yd.
      adjoint()) + 12.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*mq2*Yd.
      adjoint()) + 72.*mHd2*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*1.2020569031595942) + 6.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*Yd.adjoint()*md2) + 24.*threeLoop*(Yd*Yd.adjoint()*Yd*Yd.
      adjoint()*TYd*(TYd).adjoint()*1.2020569031595942) - 4.*threeLoop*(Yd*Yd.
      adjoint()*Yd*Yu.adjoint()*mu2*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu*mq2*Yd.adjoint()) - 2.*threeLoop*(Yd*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu*Yd.adjoint()*md2) + 24.*threeLoop*(Yd*Yd.
      adjoint()*Yd*(TYd).adjoint()*TYd*Yd.adjoint()*1.2020569031595942) + 24.*
      threeLoop*(Yd*Yd.adjoint()*TYd*Yd.adjoint()*Yd*(TYd).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yd*Yd.adjoint()*TYd*(TYd).adjoint()*
      Yd*Yd.adjoint()*1.2020569031595942) - 4.*threeLoop*(Yd*Yu.adjoint()*mu2*
      Yu*Yd.adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*mu2*Yu*
      Yu.adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*Yu*mq2*Yd.
      adjoint()*Yd*Yd.adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*Yu*mq2*Yu.
      adjoint()*Yu*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint(
      )*md2*Yd*Yd.adjoint()) - 4.*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd
      *mq2*Yd.adjoint()) - 2.*threeLoop*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*md2) + 12.*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yd
      .adjoint()) + 12.*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yd.
      adjoint()) + 6.*threeLoop*(Yd*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yd.adjoint(
      )*md2) + 24.*threeLoop*(Yd*(TYd).adjoint()*Yd*Yd.adjoint()*TYd*Yd.adjoint
      ()*1.2020569031595942) + 24.*threeLoop*(Yd*(TYd).adjoint()*TYd*Yd.adjoint
      ()*Yd*Yd.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYd*Yd.adjoint()*
      Yd*Yd.adjoint()*Yd*(TYd).adjoint()*1.2020569031595942) + 24.*threeLoop*(
      TYd*Yd.adjoint()*Yd*(TYd).adjoint()*Yd*Yd.adjoint()*1.2020569031595942) +
      24.*threeLoop*(TYd*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yd.adjoint()*
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

   beta_md2 = beta_md2_1 + beta_md2_2 + beta_md2_3 + beta_md2_4 + beta_md2_5 +
      beta_md2_6 + beta_md2_7 + beta_md2_8;


   return beta_md2;
}

/**
 * Calculates the 4-loop beta function of md2.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_md2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_md2;

   beta_md2 = ZEROMATRIX(3,3);


   return beta_md2;
}

/**
 * Calculates the 5-loop beta function of md2.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_md2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_md2;

   beta_md2 = ZEROMATRIX(3,3);


   return beta_md2;
}

} // namespace flexiblesusy
