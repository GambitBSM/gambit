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

// File generated at Thu 10 May 2018 14:35:48

#include "MSSMatMGUTEFTHiggs_soft_parameters.hpp"
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
Eigen::Matrix<double,3,3> MSSMatMGUTEFTHiggs_soft_parameters::calc_beta_mu2_1_loop(const Soft_traces& soft_traces) const
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
Eigen::Matrix<double,3,3> MSSMatMGUTEFTHiggs_soft_parameters::calc_beta_mu2_2_loop(const Soft_traces& soft_traces) const
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
Eigen::Matrix<double,3,3> MSSMatMGUTEFTHiggs_soft_parameters::calc_beta_mu2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = ZEROMATRIX(3,3);


   return beta_mu2;
}

} // namespace flexiblesusy
