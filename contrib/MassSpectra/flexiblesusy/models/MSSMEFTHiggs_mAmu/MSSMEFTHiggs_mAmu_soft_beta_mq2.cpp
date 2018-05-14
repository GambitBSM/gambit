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

// File generated at Thu 10 May 2018 14:40:00

#include "MSSMEFTHiggs_mAmu_soft_parameters.hpp"
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
Eigen::Matrix<double,3,3> MSSMEFTHiggs_mAmu_soft_parameters::calc_beta_mq2_1_loop(const Soft_traces& soft_traces) const
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
Eigen::Matrix<double,3,3> MSSMEFTHiggs_mAmu_soft_parameters::calc_beta_mq2_2_loop(const Soft_traces& soft_traces) const
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
Eigen::Matrix<double,3,3> MSSMEFTHiggs_mAmu_soft_parameters::calc_beta_mq2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mq2;

   beta_mq2 = ZEROMATRIX(3,3);


   return beta_mq2;
}

} // namespace flexiblesusy
