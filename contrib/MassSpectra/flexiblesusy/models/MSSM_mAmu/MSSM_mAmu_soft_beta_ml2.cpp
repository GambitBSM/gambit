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

// File generated at Thu 10 May 2018 14:32:38

#include "MSSM_mAmu_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of ml2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_mAmu_soft_parameters::calc_beta_ml2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_ml2;

   beta_ml2 = (oneOver16PiSqr*(2*mHd2*(Ye.adjoint()*Ye) + 2*((TYe)
      .adjoint()*TYe) + ml2*Ye.adjoint()*Ye + 2*(Ye.adjoint()*me2*Ye) +
      Ye.adjoint()*Ye*ml2 - 0.2*(3.872983346207417*g1*Tr11 + 6*AbsSqr(MassB)*
      Sqr(g1) + 30*AbsSqr(MassWB)*Sqr(g2))*UNITMATRIX(3))).real();


   return beta_ml2;
}

/**
 * Calculates the 2-loop beta function of ml2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_mAmu_soft_parameters::calc_beta_ml2_2_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr22 = TRACE_STRUCT.Tr22;


   Eigen::Matrix<double,3,3> beta_ml2;

   beta_ml2 = (twoLoop*(0.4*(-5*(3*traceconjTYdTpTYd + traceconjTYeTpTYe
      + 3*tracemd2YdAdjYd + traceme2YeAdjYe + traceml2AdjYeYe + 3*
      tracemq2AdjYdYd + 6*mHd2*traceYdAdjYd + 2*mHd2*traceYeAdjYe) + 6*mHd2*Sqr
      (g1) + 12*AbsSqr(MassB)*Sqr(g1))*(Ye.adjoint()*Ye) - 0.4*(5*(3*
      traceconjTYdTpYd + traceconjTYeTpYe) + 6*Conj(MassB)*Sqr(g1))*(Ye.adjoint
      ()*TYe) - 0.4*(5*(3*traceAdjYdTYd + traceAdjYeTYe) + 6*MassB*Sqr(g1))*((
      TYe).adjoint()*Ye) + (-2*(3*traceYdAdjYd + traceYeAdjYe) + 2.4*Sqr(g1))*(
      (TYe).adjoint()*TYe) + (-3*traceYdAdjYd - traceYeAdjYe + 1.2*Sqr(g1))*(
      ml2*Ye.adjoint()*Ye) + (-2*(3*traceYdAdjYd + traceYeAdjYe) + 2.4*Sqr(g1))
      *(Ye.adjoint()*me2*Ye) + (-3*traceYdAdjYd - traceYeAdjYe + 1.2*Sqr(g1))*(
      Ye.adjoint()*Ye*ml2) - 8*mHd2*(Ye.adjoint()*Ye*Ye.adjoint()*Ye) - 4*(
      Ye.adjoint()*Ye*(TYe).adjoint()*TYe) - 4*(Ye.adjoint()*TYe*(TYe).adjoint(
      )*Ye) - 4*((TYe).adjoint()*Ye*Ye.adjoint()*TYe) - 4*((TYe).adjoint()*TYe*
      Ye.adjoint()*Ye) - 2*(ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye) - 4*(
      Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye) - 4*(Ye.adjoint()*Ye*ml2*Ye.adjoint(
      )*Ye) - 4*(Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye) - 2*(Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*ml2) + 0.04*(9*Conj(MassB)*(69*MassB*Quad(g1) + 5*(2*
      MassB + MassWB)*Sqr(g1)*Sqr(g2)) + 5*(-15.491933384829668*g1*Tr31 + 30*
      Tr22*Quad(g2) + 6*Tr2U111*Sqr(g1) + 3*Conj(MassWB)*Sqr(g2)*(3*(MassB + 2*
      MassWB)*Sqr(g1) + 55*MassWB*Sqr(g2))))*UNITMATRIX(3))).real();


   return beta_ml2;
}

/**
 * Calculates the 3-loop beta function of ml2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSM_mAmu_soft_parameters::calc_beta_ml2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYdYdAdjTYdYd = TRACE_STRUCT.traceAdjYdYdAdjTYdYd;
   const double traceAdjYeYeAdjTYeYe = TRACE_STRUCT.traceAdjYeYeAdjTYeYe;
   const double traceAdjYuYuAdjTYdYd = TRACE_STRUCT.traceAdjYuYuAdjTYdYd;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
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


   Eigen::Matrix<double,3,3> beta_ml2;

   const Eigen::Matrix<double,3,3> beta_ml2_1 = ((threeLoop*(Power6(g1)*(
      -4.968*mHd2 - 4.968*mHu2 - 3.312*tracemd2 - 9.936*traceme2 - 4.968*
      traceml2 - 1.656*tracemq2 - 13.248*tracemu2 + 239.45914429835202*Sqr(
      MassB)) + Quad(g1)*(8.4*MassB*traceAdjTYdYd + 10.8*MassB*traceAdjTYeYe +
      15.6*MassB*traceAdjTYuYu - 5.04*mHd2*traceAdjYdYd - 5.04*traceAdjYdYdmq2
      - 6.48*mHd2*traceAdjYeYe - 6.48*traceAdjYeYeml2 - 9.36*mHu2*traceAdjYuYu
      - 9.36*traceAdjYuYumq2 - 5.04*traceTYdAdjTYd + 8.4*MassB*traceTYdAdjYd -
      6.48*traceTYeAdjTYe + 10.8*MassB*traceTYeAdjYe - 9.36*traceTYuAdjTYu +
      15.6*MassB*traceTYuAdjYu - 5.04*traceYdAdjYdmd2 - 6.48*traceYeAdjYeme2 -
      9.36*traceYuAdjYumu2 - 25.2*traceAdjYdYd*Sqr(MassB) - 32.4*traceAdjYeYe*
      Sqr(MassB) - 46.8*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(-46.72465076838378*
      MassB*MassG - 70.08697615257569*Sqr(MassB) - 12.802325384191889*Sqr(MassG
      )) + Sqr(g2)*(-44.575972394845024*MassB*MassWB - 1.08*mHd2 - 1.08*mHu2 -
      0.72*tracemd2 - 2.16*traceme2 - 1.08*traceml2 - 0.36*tracemq2 - 2.88*
      tracemu2 - 66.86395859226754*Sqr(MassB) - 19.047986197422514*Sqr(MassWB))
      ) + Quad(g2)*Sqr(g1)*(-59.893287324741706*MassB*MassWB - 1.8*mHd2 - 1.8*
      mHu2 - 1.8*traceml2 - 5.4*tracemq2 - 24.546643662370855*Sqr(MassB) -
      82.63993098711256*Sqr(MassWB)) + Quad(g2)*(90.*MassWB*traceAdjTYdYd + 30.
      *MassWB*traceAdjTYeYe + 90.*MassWB*traceAdjTYuYu - 54.*mHd2*traceAdjYdYd
      - 54.*traceAdjYdYdmq2 - 18.*mHd2*traceAdjYeYe - 18.*traceAdjYeYeml2 - 54.
      *mHu2*traceAdjYuYu - 54.*traceAdjYuYumq2 - 54.*traceTYdAdjTYd + 90.*
      MassWB*traceTYdAdjYd - 18.*traceTYeAdjTYe + 30.*MassWB*traceTYeAdjYe -
      54.*traceTYuAdjTYu + 90.*MassWB*traceTYuAdjYu - 54.*traceYdAdjYdmd2 - 18.
      *traceYeAdjYeme2 - 54.*traceYuAdjYumu2 + Sqr(g3)*(-318.57716432988946*
      MassG*MassWB - 87.28858216494473*Sqr(MassG) - 477.8657464948342*Sqr(
      MassWB)) - 270.*traceAdjYdYd*Sqr(MassWB) - 90.*traceAdjYeYe*Sqr(MassWB) -
      270.*traceAdjYuYu*Sqr(MassWB) + Sqr(g2)*(-3.*mHd2 - 3.*mHu2 - 3.*
      traceml2 - 9.*tracemq2 + 6700.775093943266*Sqr(MassWB)))) + threeLoop*(
      72.*traceAdjTYdTYdAdjYdYd + 12.*traceAdjTYdTYdAdjYuYu + 24.*
      traceAdjTYeTYeAdjYeYe + 12.*traceAdjTYuTYuAdjYdYd + 72.*
      traceAdjYdTYdAdjTYdYd + MassWB*(-36.*traceAdjTYdYd - 12.*traceAdjTYeYe +
      72.*MassWB*traceAdjYdYd)*Sqr(g2) + 63.99999999999999*MassG*traceAdjTYdYd*
      Sqr(g3) + Quad(g1)*(-56.34*mHd2 - 1.44*mHu2 - 329.4*Sqr(MassB)) -
      127.99999999999999*traceAdjYdYd*Sqr(g3)*Sqr(MassG) + Sqr(g1)*(
      -15.999999999999998*MassB*traceAdjTYdYd + 31.999999999999996*mHd2*
      traceAdjYdYd + 31.999999999999996*traceAdjYdYd*Sqr(MassB) + Sqr(g2)*(
      -32.4*MassB*MassWB - 16.2*mHd2 - 32.4*Sqr(MassB) - 32.4*Sqr(MassWB))) +
      Quad(g2)*(-22.5*mHd2 - 135.*Sqr(MassWB)))*(Ye.adjoint()*Ye))*UNITMATRIX(3
      )).real();
   const Eigen::Matrix<double,3,3> beta_ml2_2 = ((threeLoop*(108.*mHd2*
      traceAdjYdYdAdjYdYd + 72.*traceAdjYdYdAdjYdYdmq2 + 12.*
      traceAdjYdYdAdjYuYumq2 - 36.*traceAdjYdYd*traceAdjYdYdmq2 + 24.*
      traceAdjYeTYeAdjTYeYe - 36.*mHd2*traceAdjYdYd*traceAdjYeYe - 12.*
      traceAdjYdYdmq2*traceAdjYeYe + 36.*mHd2*traceAdjYeYeAdjYeYe + 24.*
      traceAdjYeYeAdjYeYeml2 - 12.*traceAdjYdYd*traceAdjYeYeml2 -
      3.9999999999999996*traceAdjYeYe*traceAdjYeYeml2 + 12.*
      traceAdjYuTYuAdjTYdYd + 24.*mHd2*traceAdjYuYuAdjYdYd + 12.*mHu2*
      traceAdjYuYuAdjYdYd + 12.*traceAdjYuYuAdjYdYdmq2 - 36.*traceAdjYdYd*
      traceTYdAdjTYd - 12.*traceAdjYeYe*traceTYdAdjTYd + 12.*
      traceTYdAdjTYuYuAdjYd - 36.*traceAdjTYdYd*traceTYdAdjYd - 12.*
      traceAdjTYeYe*traceTYdAdjYd - 12.*traceAdjYdYd*traceTYeAdjTYe -
      3.9999999999999996*traceAdjYeYe*traceTYeAdjTYe - 12.*traceAdjTYdYd*
      traceTYeAdjYe - 3.9999999999999996*traceAdjTYeYe*traceTYeAdjYe - 36.*
      traceAdjYdYd*traceYdAdjYdmd2 - 12.*traceAdjYeYe*traceYdAdjYdmd2 + 72.*
      traceYdAdjYdYdAdjYdmd2 + 12.*traceYdAdjYuYuAdjYdmd2 - 12.*traceAdjYdYd*
      traceYeAdjYeme2 - 3.9999999999999996*traceAdjYeYe*traceYeAdjYeme2 + 24.*
      traceYeAdjYeYeAdjYeme2 + 12.*traceYuAdjYdYdAdjYumu2 - 0.9599999999999999*
      tracemd2*Quad(g1) - 2.88*traceme2*Quad(g1) - 1.44*traceml2*Quad(g1) -
      0.4799999999999999*tracemq2*Quad(g1) - 3.8399999999999994*tracemu2*Quad(
      g1) + 15.999999999999998*traceAdjYdYdmq2*Sqr(g1) + 15.999999999999998*
      traceTYdAdjTYd*Sqr(g1) - 15.999999999999998*MassB*traceTYdAdjYd*Sqr(g1) +
      15.999999999999998*traceYdAdjYdmd2*Sqr(g1) + (-127.99999999999999*mHd2*
      traceAdjYdYd - 63.99999999999999*traceAdjYdYdmq2 - 63.99999999999999*
      traceTYdAdjTYd + 63.99999999999999*MassG*traceTYdAdjYd -
      63.99999999999999*traceYdAdjYdmd2)*Sqr(g3) + Sqr(g2)*(72.*mHd2*
      traceAdjYdYd + 36.*traceAdjYdYdmq2 + 24.*mHd2*traceAdjYeYe + 12.*
      traceAdjYeYeml2 + 36.*traceTYdAdjTYd - 36.*MassWB*traceTYdAdjYd + 12.*
      traceTYeAdjTYe - 12.*MassWB*traceTYeAdjYe + 36.*traceYdAdjYdmd2 + 12.*
      traceYeAdjYeme2 + 24.*traceAdjYeYe*Sqr(MassWB)) - 54.*mHd2*Sqr(
      traceAdjYdYd) - 6.*mHd2*Sqr(traceAdjYeYe))*(Ye.adjoint()*Ye) + threeLoop*
      (12.*traceAdjTYuYuAdjYdYd - 36.*traceAdjTYdYd*traceAdjYdYd - 12.*
      traceAdjTYeYe*traceAdjYdYd + 72.*traceAdjYdYdAdjTYdYd - 12.*traceAdjTYdYd
      *traceAdjYeYe - 3.9999999999999996*traceAdjTYeYe*traceAdjYeYe + 24.*
      traceAdjYeYeAdjTYeYe + 12.*traceAdjYuYuAdjTYdYd + 109.8*MassB*Quad(g1) +
      45.*MassWB*Quad(g2) + (36.*traceAdjTYdYd + 12.*traceAdjTYeYe - 36.*MassWB
      *traceAdjYdYd - 12.*MassWB*traceAdjYeYe)*Sqr(g2) + Sqr(g1)*(
      15.999999999999998*traceAdjTYdYd - 15.999999999999998*MassB*traceAdjYdYd
      + (16.2*MassB + 16.2*MassWB)*Sqr(g2)) - 63.99999999999999*traceAdjTYdYd*
      Sqr(g3) + 63.99999999999999*MassG*traceAdjYdYd*Sqr(g3))*(Ye.adjoint()*TYe
      ) + threeLoop*(72.*traceAdjYdTYdAdjYdYd + 24.*traceAdjYeTYeAdjYeYe + 12.*
      traceAdjYuTYuAdjYdYd - 36.*traceAdjYdYd*traceTYdAdjYd - 12.*traceAdjYeYe*
      traceTYdAdjYd + 12.*traceTYdAdjYuYuAdjYd - 12.*traceAdjYdYd*traceTYeAdjYe
      - 3.9999999999999996*traceAdjYeYe*traceTYeAdjYe + 109.8*MassB*Quad(g1) +
      45.*MassWB*Quad(g2) + (-36.*MassWB*traceAdjYdYd - 12.*MassWB*
      traceAdjYeYe + 36.*traceTYdAdjYd + 12.*traceTYeAdjYe)*Sqr(g2) + Sqr(g1)*(
      -15.999999999999998*MassB*traceAdjYdYd + 15.999999999999998*traceTYdAdjYd
      + (16.2*MassB + 16.2*MassWB)*Sqr(g2)) + 63.99999999999999*MassG*
      traceAdjYdYd*Sqr(g3) - 63.99999999999999*traceTYdAdjYd*Sqr(g3))*((TYe)
      .adjoint()*Ye) - 54.9*threeLoop*Quad(g1)*((TYe).adjoint()*TYe))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_3 = ((threeLoop*(36.*
      traceAdjYdYdAdjYdYd - 12.*traceAdjYdYd*traceAdjYeYe + 12.*
      traceAdjYeYeAdjYeYe + 12.*traceAdjYuYuAdjYdYd - 22.5*Quad(g2) + Sqr(g1)*(
      15.999999999999998*traceAdjYdYd - 16.2*Sqr(g2)) + (36.*traceAdjYdYd + 12.
      *traceAdjYeYe)*Sqr(g2) - 63.99999999999999*traceAdjYdYd*Sqr(g3) - 18.*Sqr
      (traceAdjYdYd) - 1.9999999999999998*Sqr(traceAdjYeYe))*((TYe).adjoint()*
      TYe) + threeLoop*(18.*traceAdjYdYdAdjYdYd - 6.*traceAdjYdYd*traceAdjYeYe
      + 6.*traceAdjYeYeAdjYeYe + 6.*traceAdjYuYuAdjYdYd - 27.45*Quad(g1) -
      11.25*Quad(g2) + Sqr(g1)*(7.999999999999999*traceAdjYdYd - 8.1*Sqr(g2)) +
      (18.*traceAdjYdYd + 6.*traceAdjYeYe)*Sqr(g2) - 31.999999999999996*
      traceAdjYdYd*Sqr(g3) - 9.*Sqr(traceAdjYdYd) - 0.9999999999999999*Sqr(
      traceAdjYeYe))*(ml2*Ye.adjoint()*Ye) + threeLoop*(36.*traceAdjYdYdAdjYdYd
      - 12.*traceAdjYdYd*traceAdjYeYe + 12.*traceAdjYeYeAdjYeYe + 12.*
      traceAdjYuYuAdjYdYd - 54.9*Quad(g1) - 22.5*Quad(g2) + Sqr(g1)*(
      15.999999999999998*traceAdjYdYd - 16.2*Sqr(g2)) + (36.*traceAdjYdYd + 12.
      *traceAdjYeYe)*Sqr(g2) - 63.99999999999999*traceAdjYdYd*Sqr(g3) - 18.*Sqr
      (traceAdjYdYd) - 1.9999999999999998*Sqr(traceAdjYeYe))*(Ye.adjoint()*me2*
      Ye) + threeLoop*(Quad(g1)*(3.24*mHd2 + 19.44*Sqr(MassB)) + Sqr(g3)*(-96.*
      MassG*traceAdjTYdYd + 192.*mHd2*traceAdjYdYd + 96.*traceAdjYdYdmq2 + 96.*
      traceTYdAdjTYd - 96.*MassG*traceTYdAdjYd + 96.*traceYdAdjYdmd2 + 192.*
      traceAdjYdYd*Sqr(MassG)) + Quad(g2)*(-62.99999999999999*mHd2 - 378.*Sqr(
      MassWB)) + Sqr(g1)*(24.*MassB*traceAdjTYdYd - 48.*mHd2*traceAdjYdYd - 24.
      *traceAdjYdYdmq2 - 24.*traceTYdAdjTYd + 24.*MassB*traceTYdAdjYd - 24.*
      traceYdAdjYdmd2 - 48.*traceAdjYdYd*Sqr(MassB) + Sqr(g2)*(64.8*MassB*
      MassWB + 32.4*mHd2 + 64.8*Sqr(MassB) + 64.8*Sqr(MassWB))))*(Ye.adjoint()*
      Ye*1.2020569031595942) + threeLoop*(18.*traceAdjYdYdAdjYdYd - 6.*
      traceAdjYdYd*traceAdjYeYe + 6.*traceAdjYeYeAdjYeYe + 6.*
      traceAdjYuYuAdjYdYd - 27.45*Quad(g1) - 11.25*Quad(g2) + Sqr(g1)*(
      7.999999999999999*traceAdjYdYd - 8.1*Sqr(g2)) + (18.*traceAdjYdYd + 6.*
      traceAdjYeYe)*Sqr(g2) - 31.999999999999996*traceAdjYdYd*Sqr(g3) - 9.*Sqr(
      traceAdjYdYd) - 0.9999999999999999*Sqr(traceAdjYeYe))*(Ye.adjoint()*Ye*
      ml2) + threeLoop*(-6.48*MassB*Quad(g1) + 125.99999999999999*MassWB*Quad(
      g2) + Sqr(g1)*(-24.*traceAdjTYdYd + 24.*MassB*traceAdjYdYd + (-32.4*MassB
      - 32.4*MassWB)*Sqr(g2)) + (96.*traceAdjTYdYd - 96.*MassG*traceAdjYdYd)*
      Sqr(g3))*(Ye.adjoint()*TYe*1.2020569031595942) + threeLoop*(-6.48*MassB*
      Quad(g1) + 125.99999999999999*MassWB*Quad(g2) + Sqr(g1)*(24.*MassB*
      traceAdjYdYd - 24.*traceTYdAdjYd + (-32.4*MassB - 32.4*MassWB)*Sqr(g2)) +
      (-96.*MassG*traceAdjYdYd + 96.*traceTYdAdjYd)*Sqr(g3))*((TYe).adjoint()*
      Ye*1.2020569031595942) + threeLoop*(3.24*Quad(g1) - 62.99999999999999*
      Quad(g2) + Sqr(g1)*(-24.*traceAdjYdYd + 32.4*Sqr(g2)) + 96.*traceAdjYdYd*
      Sqr(g3))*((TYe).adjoint()*TYe*1.2020569031595942) + threeLoop*(1.62*Quad(
      g1) - 31.499999999999996*Quad(g2) + Sqr(g1)*(-12.*traceAdjYdYd + 16.2*Sqr
      (g2)) + 48.*traceAdjYdYd*Sqr(g3))*(ml2*Ye.adjoint()*Ye*1.2020569031595942
      ) + 3.24*threeLoop*Quad(g1)*(Ye.adjoint()*me2*Ye*1.2020569031595942))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_4 = ((threeLoop*(
      -62.99999999999999*Quad(g2) + Sqr(g1)*(-24.*traceAdjYdYd + 32.4*Sqr(g2))
      + 96.*traceAdjYdYd*Sqr(g3))*(Ye.adjoint()*me2*Ye*1.2020569031595942) +
      threeLoop*(1.62*Quad(g1) - 31.499999999999996*Quad(g2) + Sqr(g1)*(-12.*
      traceAdjYdYd + 16.2*Sqr(g2)) + 48.*traceAdjYdYd*Sqr(g3))*(Ye.adjoint()*Ye
      *ml2*1.2020569031595942) + threeLoop*(36.*mHd2*traceAdjYdYd + 12.*
      traceAdjYdYdmq2 + 12.*mHd2*traceAdjYeYe + 3.9999999999999996*
      traceAdjYeYeml2 + 12.*traceTYdAdjTYd + 3.9999999999999996*traceTYeAdjTYe
      + 12.*traceYdAdjYdmd2 + 3.9999999999999996*traceYeAdjYeme2 + Sqr(g1)*(36.
      *mHd2 + 36.*Sqr(MassB)) + Sqr(g2)*(-12.*mHd2 - 12.*Sqr(MassWB)))*(
      Ye.adjoint()*Ye*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjTYdYd +
      3.9999999999999996*traceAdjTYeYe - 18.*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2))
      *(Ye.adjoint()*Ye*Ye.adjoint()*TYe) + threeLoop*(12.*traceTYdAdjYd +
      3.9999999999999996*traceTYeAdjYe - 18.*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2))
      *(Ye.adjoint()*Ye*(TYe).adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*(Ye.adjoint()
      *Ye*(TYe).adjoint()*TYe) + threeLoop*(12.*traceAdjTYdYd +
      3.9999999999999996*traceAdjTYeYe - 18.*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2))
      *(Ye.adjoint()*TYe*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*(Ye.adjoint()
      *TYe*(TYe).adjoint()*Ye) + threeLoop*(12.*traceTYdAdjYd +
      3.9999999999999996*traceTYeAdjYe - 18.*MassB*Sqr(g1) + 6.*MassWB*Sqr(g2))
      *((TYe).adjoint()*Ye*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*((TYe)
      .adjoint()*Ye*Ye.adjoint()*TYe) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*((TYe)
      .adjoint()*TYe*Ye.adjoint()*Ye) + threeLoop*(6.*traceAdjYdYd +
      1.9999999999999998*traceAdjYeYe + 9.*Sqr(g1) - 3.*Sqr(g2))*(ml2*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*(Ye.adjoint()
      *me2*Ye*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*(Ye.adjoint()
      *Ye*ml2*Ye.adjoint()*Ye) + threeLoop*(12.*traceAdjYdYd +
      3.9999999999999996*traceAdjYeYe + 18.*Sqr(g1) - 6.*Sqr(g2))*(Ye.adjoint()
      *Ye*Ye.adjoint()*me2*Ye) + threeLoop*(Sqr(g1)*(-43.2*mHd2 - 43.2*Sqr(
      MassB)) + Sqr(g2)*(72.*mHd2 + 72.*Sqr(MassWB)))*(Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*1.2020569031595942) + threeLoop*(6.*traceAdjYdYd +
      1.9999999999999998*traceAdjYeYe + 9.*Sqr(g1) - 3.*Sqr(g2))*(Ye.adjoint()*
      Ye*Ye.adjoint()*Ye*ml2) + threeLoop*(21.6*MassB*Sqr(g1) - 36.*MassWB*Sqr(
      g2))*(Ye.adjoint()*Ye*Ye.adjoint()*TYe*1.2020569031595942) + threeLoop*(
      21.6*MassB*Sqr(g1) - 36.*MassWB*Sqr(g2))*(Ye.adjoint()*Ye*(TYe).adjoint()
      *Ye*1.2020569031595942) + threeLoop*(-21.6*Sqr(g1) + 36.*Sqr(g2))*(
      Ye.adjoint()*Ye*(TYe).adjoint()*TYe*1.2020569031595942) + threeLoop*(21.6
      *MassB*Sqr(g1) - 36.*MassWB*Sqr(g2))*(Ye.adjoint()*TYe*Ye.adjoint()*Ye*
      1.2020569031595942) + threeLoop*(-21.6*Sqr(g1) + 36.*Sqr(g2))*(Ye.adjoint
      ()*TYe*(TYe).adjoint()*Ye*1.2020569031595942) + threeLoop*(21.6*MassB*Sqr
      (g1) - 36.*MassWB*Sqr(g2))*((TYe).adjoint()*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + threeLoop*(-21.6*Sqr(g1) + 36.*Sqr(g2))*((TYe)
      .adjoint()*Ye*Ye.adjoint()*TYe*1.2020569031595942) + threeLoop*(-21.6*Sqr
      (g1) + 36.*Sqr(g2))*((TYe).adjoint()*TYe*Ye.adjoint()*Ye*
      1.2020569031595942) + threeLoop*(-10.8*Sqr(g1) + 18.*Sqr(g2))*(ml2*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + threeLoop*(-21.6*
      Sqr(g1) + 36.*Sqr(g2))*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + threeLoop*(-21.6*Sqr(g1) + 36.*Sqr(g2))*(Ye.adjoint
      ()*Ye*ml2*Ye.adjoint()*Ye*1.2020569031595942) - 21.6*threeLoop*Sqr(g1)*(
      Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*1.2020569031595942))*UNITMATRIX(3))
      .real();
   const Eigen::Matrix<double,3,3> beta_ml2_5 = ((36.*threeLoop*Sqr(g2)*(
      Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*1.2020569031595942) + threeLoop*(
      -10.8*Sqr(g1) + 18.*Sqr(g2))*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*
      1.2020569031595942) + 36.*mHd2*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*Ye
      *Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*(TYe).adjoint()*TYe*1.2020569031595942) + 12.*threeLoop*(
      Ye.adjoint()*Ye*Ye.adjoint()*TYe*(TYe).adjoint()*Ye*1.2020569031595942) +
      12.*threeLoop*(Ye.adjoint()*Ye*(TYe).adjoint()*Ye*Ye.adjoint()*TYe*
      1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*(TYe).adjoint()*TYe*
      Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*TYe*
      Ye.adjoint()*Ye*(TYe).adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(
      Ye.adjoint()*TYe*(TYe).adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) +
      12.*threeLoop*((TYe).adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*
      1.2020569031595942) + 12.*threeLoop*((TYe).adjoint()*Ye*Ye.adjoint()*TYe*
      Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*((TYe).adjoint()*TYe*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 6.*threeLoop*(ml2*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 12.
      *threeLoop*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*
      Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*1.2020569031595942) +
      12.*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*
      1.2020569031595942) + 6.*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*ml2*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_ml2 = beta_ml2_1 + beta_ml2_2 + beta_ml2_3 + beta_ml2_4 +
      beta_ml2_5;


   return beta_ml2;
}

} // namespace flexiblesusy
