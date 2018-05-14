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

// File generated at Thu 10 May 2018 14:26:40

#include "MSSMatMSUSY_mAmu_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of me2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_soft_parameters::calc_beta_me2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_me2;

   beta_me2 = (oneOver16PiSqr*(4*mHd2*(Ye*Ye.adjoint()) + 4*(TYe*(TYe)
      .adjoint()) + 2*(me2*Ye*Ye.adjoint()) + 4*(Ye*ml2*Ye.adjoint()) + 2*(Ye*
      Ye.adjoint()*me2) + 0.4*g1*(3.872983346207417*Tr11 - 12*g1*AbsSqr(MassB))
      *UNITMATRIX(3))).real();


   return beta_me2;
}

/**
 * Calculates the 2-loop beta function of me2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_soft_parameters::calc_beta_me2_2_loop(const Soft_traces& soft_traces) const
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


   Eigen::Matrix<double,3,3> beta_me2;

   beta_me2 = (twoLoop*(-0.8*(15*traceconjTYdTpTYd + 5*traceconjTYeTpTYe
      + 15*tracemd2YdAdjYd + 5*traceme2YeAdjYe + 5*traceml2AdjYeYe + 15*
      tracemq2AdjYdYd + 30*mHd2*traceYdAdjYd + 10*mHd2*traceYeAdjYe + 3*mHd2*
      Sqr(g1) + 6*AbsSqr(MassB)*Sqr(g1) - 15*mHd2*Sqr(g2) - 30*AbsSqr(MassWB)*
      Sqr(g2))*(Ye*Ye.adjoint()) + (2.4*MassB*Sqr(g1) - 4*(3*traceAdjYdTYd +
      traceAdjYeTYe + 3*MassWB*Sqr(g2)))*(Ye*(TYe).adjoint()) + (2.4*Conj(MassB
      )*Sqr(g1) - 4*(3*traceconjTYdTpYd + traceconjTYeTpYe + 3*Conj(MassWB)*Sqr
      (g2)))*(TYe*Ye.adjoint()) - 0.8*(3*Sqr(g1) + 5*(3*traceYdAdjYd +
      traceYeAdjYe - 3*Sqr(g2)))*(TYe*(TYe).adjoint()) + (-2*(3*traceYdAdjYd +
      traceYeAdjYe) - 1.2*Sqr(g1) + 6*Sqr(g2))*(me2*Ye*Ye.adjoint()) - 0.8*(3*
      Sqr(g1) + 5*(3*traceYdAdjYd + traceYeAdjYe - 3*Sqr(g2)))*(Ye*ml2*
      Ye.adjoint()) + (-2*(3*traceYdAdjYd + traceYeAdjYe) - 1.2*Sqr(g1) + 6*Sqr
      (g2))*(Ye*Ye.adjoint()*me2) - 8*mHd2*(Ye*Ye.adjoint()*Ye*Ye.adjoint()) -
      4*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()) - 4*(Ye*(TYe).adjoint()*TYe*
      Ye.adjoint()) - 4*(TYe*Ye.adjoint()*Ye*(TYe).adjoint()) - 4*(TYe*(TYe)
      .adjoint()*Ye*Ye.adjoint()) - 2*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()) - 4
      *(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()) - 4*(Ye*Ye.adjoint()*me2*Ye*
      Ye.adjoint()) - 4*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()) - 2*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*me2) + 0.32*g1*(15*g1*Tr2U111 +
      19.364916731037084*Tr31 + 351*AbsSqr(MassB)*Cube(g1))*UNITMATRIX(3)))
      .real();


   return beta_me2;
}

/**
 * Calculates the 3-loop beta function of me2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> MSSMatMSUSY_mAmu_soft_parameters::calc_beta_me2_3_loop(const Soft_traces& soft_traces) const
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


   Eigen::Matrix<double,3,3> beta_me2;

   const Eigen::Matrix<double,3,3> beta_me2_1 = ((threeLoop*Quad(g1)*(
      33.6*MassB*traceAdjTYdYd + 43.2*MassB*traceAdjTYeYe + 62.39999999999999*
      MassB*traceAdjTYuYu - 20.16*mHd2*traceAdjYdYd - 20.16*traceAdjYdYdmq2 -
      25.92*mHd2*traceAdjYeYe - 25.92*traceAdjYeYeml2 - 37.44*mHu2*traceAdjYuYu
      - 37.44*traceAdjYuYumq2 - 20.16*traceTYdAdjTYd + 33.6*MassB*
      traceTYdAdjYd - 25.92*traceTYeAdjTYe + 43.2*MassB*traceTYeAdjYe - 37.44*
      traceTYuAdjTYu + 62.39999999999999*MassB*traceTYuAdjYu - 20.16*
      traceYdAdjYdmd2 - 25.92*traceYeAdjYeme2 - 37.44*traceYuAdjYumu2 -
      186.89860307353513*MassB*MassG*Sqr(g3) - 100.8*traceAdjYdYd*Sqr(MassB) -
      129.6*traceAdjYeYe*Sqr(MassB) - 187.2*traceAdjYuYu*Sqr(MassB) -
      280.34790461030275*Sqr(g3)*Sqr(MassB) + Sqr(g1)*(-22.464*mHd2 - 22.464*
      mHu2 - 14.976*tracemd2 - 44.928*traceme2 - 22.464*traceml2 - 7.488*
      tracemq2 - 59.904*tracemu2 + 709.004577193408*Sqr(MassB)) -
      51.209301536767555*Sqr(g3)*Sqr(MassG) + Sqr(g2)*(-57.34388957938012*MassB
      *MassWB - 86.01583436907012*Sqr(MassB) - 15.711944789690051*Sqr(MassWB)))
      + threeLoop*(144.*traceAdjTYdTYdAdjYdYd + 24.*traceAdjTYdTYdAdjYuYu +
      48.*traceAdjTYeTYeAdjYeYe + 24.*traceAdjTYuTYuAdjYdYd + 144.*
      traceAdjYdTYdAdjTYdYd + 216.*mHd2*traceAdjYdYdAdjYdYd + 144.*
      traceAdjYdYdAdjYdYdmq2 + 24.*traceAdjYdYdAdjYuYumq2 - 72.*traceAdjYdYd*
      traceAdjYdYdmq2 + 48.*traceAdjYeTYeAdjTYeYe - 72.*mHd2*traceAdjYdYd*
      traceAdjYeYe - 24.*traceAdjYdYdmq2*traceAdjYeYe + 72.*mHd2*
      traceAdjYeYeAdjYeYe + 48.*traceAdjYeYeAdjYeYeml2 - 24.*traceAdjYdYd*
      traceAdjYeYeml2 - 8.*traceAdjYeYe*traceAdjYeYeml2 + 24.*
      traceAdjYuTYuAdjTYdYd + 48.*mHd2*traceAdjYuYuAdjYdYd + 24.*mHu2*
      traceAdjYuYuAdjYdYd + 24.*traceAdjYuYuAdjYdYdmq2 - 72.*traceAdjYdYd*
      traceTYdAdjTYd - 24.*traceAdjYeYe*traceTYdAdjTYd + 24.*
      traceTYdAdjTYuYuAdjYd + 128.*MassG*traceAdjTYdYd*Sqr(g3) - 256.*mHd2*
      traceAdjYdYd*Sqr(g3) - 128.*traceAdjYdYdmq2*Sqr(g3) - 128.*traceTYdAdjTYd
      *Sqr(g3) + Quad(g1)*(-58.68*mHd2 + 1.44*mHu2 + 0.96*tracemd2 + 2.88*
      traceme2 + 1.44*traceml2 + 0.48*tracemq2 + 3.84*tracemu2 -
      360.7200000000001*Sqr(MassB)) - 256.*traceAdjYdYd*Sqr(g3)*Sqr(MassG) +
      Sqr(g1)*(-42.8*MassB*traceAdjTYdYd - 3.6*MassB*traceAdjTYeYe + 85.6*mHd2*
      traceAdjYdYd + 42.8*traceAdjYdYdmq2 + 7.2*mHd2*traceAdjYeYe + 3.6*
      traceAdjYeYeml2 + 42.8*traceTYdAdjTYd + 85.6*traceAdjYdYd*Sqr(MassB) +
      7.2*traceAdjYeYe*Sqr(MassB) + Sqr(g2)*(-108.*MassB*MassWB - 54.*mHd2 -
      108.*Sqr(MassB) - 108.*Sqr(MassWB))) + Quad(g2)*(-99.*mHd2 - 12.*mHu2 -
      12.*traceml2 - 36.*tracemq2 - 474.00000000000006*Sqr(MassWB)) + Sqr(g2)*(
      -54.*MassWB*traceAdjTYdYd - 18.*MassWB*traceAdjTYeYe + 108.*mHd2*
      traceAdjYdYd + 54.*traceAdjYdYdmq2 + 36.*mHd2*traceAdjYeYe + 18.*
      traceAdjYeYeml2 + 54.*traceTYdAdjTYd + 108.*traceAdjYdYd*Sqr(MassWB) +
      36.*traceAdjYeYe*Sqr(MassWB)) - 108.*mHd2*Sqr(traceAdjYdYd) - 12.*mHd2*
      Sqr(traceAdjYeYe))*(Ye*Ye.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_2 = ((threeLoop*(-72.*
      traceAdjTYdYd*traceTYdAdjYd - 24.*traceAdjTYeYe*traceTYdAdjYd - 24.*
      traceAdjYdYd*traceTYeAdjTYe - 8.*traceAdjYeYe*traceTYeAdjTYe - 24.*
      traceAdjTYdYd*traceTYeAdjYe - 8.*traceAdjTYeYe*traceTYeAdjYe - 72.*
      traceAdjYdYd*traceYdAdjYdmd2 - 24.*traceAdjYeYe*traceYdAdjYdmd2 + 144.*
      traceYdAdjYdYdAdjYdmd2 + 24.*traceYdAdjYuYuAdjYdmd2 - 24.*traceAdjYdYd*
      traceYeAdjYeme2 - 8.*traceAdjYeYe*traceYeAdjYeme2 + 48.*
      traceYeAdjYeYeAdjYeme2 + 24.*traceYuAdjYdYdAdjYumu2 + (-42.8*MassB*
      traceTYdAdjYd + 3.6*traceTYeAdjTYe - 3.6*MassB*traceTYeAdjYe + 42.8*
      traceYdAdjYdmd2 + 3.6*traceYeAdjYeme2)*Sqr(g1) - 54.*MassWB*traceTYdAdjYd
      *Sqr(g2) + 18.*traceTYeAdjTYe*Sqr(g2) - 18.*MassWB*traceTYeAdjYe*Sqr(g2)
      + 54.*traceYdAdjYdmd2*Sqr(g2) + 18.*traceYeAdjYeme2*Sqr(g2) + (128.*MassG
      *traceTYdAdjYd - 128.*traceYdAdjYdmd2)*Sqr(g3))*(Ye*Ye.adjoint()) +
      threeLoop*(144.*traceAdjYdTYdAdjYdYd + 48.*traceAdjYeTYeAdjYeYe + 24.*
      traceAdjYuTYuAdjYdYd - 72.*traceAdjYdYd*traceTYdAdjYd - 24.*traceAdjYeYe*
      traceTYdAdjYd + 24.*traceTYdAdjYuYuAdjYd - 24.*traceAdjYdYd*traceTYeAdjYe
      - 8.*traceAdjYeYe*traceTYeAdjYe + 120.24*MassB*Quad(g1) + 174.*MassWB*
      Quad(g2) + (-54.*MassWB*traceAdjYdYd - 18.*MassWB*traceAdjYeYe + 54.*
      traceTYdAdjYd + 18.*traceTYeAdjYe)*Sqr(g2) + Sqr(g1)*(-42.8*MassB*
      traceAdjYdYd - 3.6*MassB*traceAdjYeYe + 42.8*traceTYdAdjYd + 3.6*
      traceTYeAdjYe + (54.*MassB + 54.*MassWB)*Sqr(g2)) + 128.*MassG*
      traceAdjYdYd*Sqr(g3) - 128.*traceTYdAdjYd*Sqr(g3))*(Ye*(TYe).adjoint()) +
      threeLoop*(24.*traceAdjTYuYuAdjYdYd - 72.*traceAdjTYdYd*traceAdjYdYd -
      24.*traceAdjTYeYe*traceAdjYdYd + 144.*traceAdjYdYdAdjTYdYd - 24.*
      traceAdjTYdYd*traceAdjYeYe - 8.*traceAdjTYeYe*traceAdjYeYe + 48.*
      traceAdjYeYeAdjTYeYe + 24.*traceAdjYuYuAdjTYdYd + 120.24*MassB*Quad(g1) +
      174.*MassWB*Quad(g2) + (54.*traceAdjTYdYd + 18.*traceAdjTYeYe - 54.*
      MassWB*traceAdjYdYd - 18.*MassWB*traceAdjYeYe)*Sqr(g2) + Sqr(g1)*(42.8*
      traceAdjTYdYd + 3.6*traceAdjTYeYe - 42.8*MassB*traceAdjYdYd - 3.6*MassB*
      traceAdjYeYe + (54.*MassB + 54.*MassWB)*Sqr(g2)) - 128.*traceAdjTYdYd*Sqr
      (g3) + 128.*MassG*traceAdjYdYd*Sqr(g3))*(TYe*Ye.adjoint()) + threeLoop*(
      72.*traceAdjYdYdAdjYdYd - 24.*traceAdjYdYd*traceAdjYeYe + 24.*
      traceAdjYeYeAdjYeYe + 24.*traceAdjYuYuAdjYdYd - 60.12*Quad(g1) - 87.*Quad
      (g2) + Sqr(g1)*(42.8*traceAdjYdYd + 3.6*traceAdjYeYe - 54.*Sqr(g2)) + (
      54.*traceAdjYdYd + 18.*traceAdjYeYe)*Sqr(g2) - 128.*traceAdjYdYd*Sqr(g3)
      - 36.*Sqr(traceAdjYdYd) - 4.*Sqr(traceAdjYeYe))*(TYe*(TYe).adjoint()) +
      threeLoop*(36.*traceAdjYdYdAdjYdYd - 12.*traceAdjYdYd*traceAdjYeYe + 12.*
      traceAdjYeYeAdjYeYe + 12.*traceAdjYuYuAdjYdYd - 30.06*Quad(g1) - 43.5*
      Quad(g2) + Sqr(g1)*(21.4*traceAdjYdYd + 1.8*traceAdjYeYe - 27.*Sqr(g2)) +
      (27.*traceAdjYdYd + 9.*traceAdjYeYe)*Sqr(g2) - 64.*traceAdjYdYd*Sqr(g3)
      - 18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe))*(me2*Ye*Ye.adjoint()) +
      threeLoop*(-60.12*Quad(g1) - 54.*Sqr(g1)*Sqr(g2))*(Ye*ml2*Ye.adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_3 = ((threeLoop*(72.*
      traceAdjYdYdAdjYdYd - 24.*traceAdjYdYd*traceAdjYeYe + 24.*
      traceAdjYeYeAdjYeYe + 24.*traceAdjYuYuAdjYdYd - 87.*Quad(g2) + (42.8*
      traceAdjYdYd + 3.6*traceAdjYeYe)*Sqr(g1) + (54.*traceAdjYdYd + 18.*
      traceAdjYeYe)*Sqr(g2) - 128.*traceAdjYdYd*Sqr(g3) - 36.*Sqr(traceAdjYdYd)
      - 4.*Sqr(traceAdjYeYe))*(Ye*ml2*Ye.adjoint()) + threeLoop*(Quad(g1)*(
      -32.4*mHd2 - 194.39999999999998*Sqr(MassB)) + Sqr(g3)*(-192.*MassG*
      traceAdjTYdYd + 384.*mHd2*traceAdjYdYd + 192.*traceAdjYdYdmq2 + 192.*
      traceTYdAdjTYd - 192.*MassG*traceTYdAdjYd + 192.*traceYdAdjYdmd2 + 384.*
      traceAdjYdYd*Sqr(MassG)) + Quad(g2)*(-18.*mHd2 - 108.*Sqr(MassWB)) + Sqr(
      g2)*(-216.*mHd2*traceAdjYdYd - 108.*traceAdjYdYdmq2 - 72.*mHd2*
      traceAdjYeYe - 36.*traceAdjYeYeml2 - 108.*traceTYdAdjTYd - 36.*
      traceTYeAdjTYe + MassWB*(108.*traceAdjTYdYd + 36.*traceAdjTYeYe + 108.*
      traceTYdAdjYd + 36.*traceTYeAdjYe) - 108.*traceYdAdjYdmd2 - 36.*
      traceYeAdjYeme2 + (-216.*traceAdjYdYd - 72.*traceAdjYeYe)*Sqr(MassWB)) +
      Sqr(g1)*(33.6*mHd2*traceAdjYdYd + 16.8*traceAdjYdYdmq2 + 43.2*mHd2*
      traceAdjYeYe + 21.6*traceAdjYeYeml2 + 16.8*traceTYdAdjTYd + 21.6*
      traceTYeAdjTYe + MassB*(-16.8*traceAdjTYdYd - 21.6*traceAdjTYeYe - 16.8*
      traceTYdAdjYd - 21.6*traceTYeAdjYe) + 16.8*traceYdAdjYdmd2 + 21.6*
      traceYeAdjYeme2 + (33.6*traceAdjYdYd + 43.2*traceAdjYeYe)*Sqr(MassB) +
      Sqr(g2)*(129.6*MassB*MassWB + 64.8*mHd2 + 129.6*Sqr(MassB) + 129.6*Sqr(
      MassWB))))*(Ye*Ye.adjoint()*1.2020569031595942) + threeLoop*(36.*
      traceAdjYdYdAdjYdYd - 12.*traceAdjYdYd*traceAdjYeYe + 12.*
      traceAdjYeYeAdjYeYe + 12.*traceAdjYuYuAdjYdYd - 30.06*Quad(g1) - 43.5*
      Quad(g2) + Sqr(g1)*(21.4*traceAdjYdYd + 1.8*traceAdjYeYe - 27.*Sqr(g2)) +
      (27.*traceAdjYdYd + 9.*traceAdjYeYe)*Sqr(g2) - 64.*traceAdjYdYd*Sqr(g3)
      - 18.*Sqr(traceAdjYdYd) - 2.*Sqr(traceAdjYeYe))*(Ye*Ye.adjoint()*me2) +
      threeLoop*(64.8*MassB*Quad(g1) + 36.*MassWB*Quad(g2) + (108.*MassWB*
      traceAdjYdYd + 36.*MassWB*traceAdjYeYe - 108.*traceTYdAdjYd - 36.*
      traceTYeAdjYe)*Sqr(g2) + Sqr(g1)*(-16.8*MassB*traceAdjYdYd - 21.6*MassB*
      traceAdjYeYe + 16.8*traceTYdAdjYd + 21.6*traceTYeAdjYe + (-64.8*MassB -
      64.8*MassWB)*Sqr(g2)) + (-192.*MassG*traceAdjYdYd + 192.*traceTYdAdjYd)*
      Sqr(g3))*(Ye*(TYe).adjoint()*1.2020569031595942) + threeLoop*(64.8*MassB*
      Quad(g1) + 36.*MassWB*Quad(g2) + (-108.*traceAdjTYdYd - 36.*traceAdjTYeYe
      + 108.*MassWB*traceAdjYdYd + 36.*MassWB*traceAdjYeYe)*Sqr(g2) + Sqr(g1)*
      (16.8*traceAdjTYdYd + 21.6*traceAdjTYeYe - 16.8*MassB*traceAdjYdYd - 21.6
      *MassB*traceAdjYeYe + (-64.8*MassB - 64.8*MassWB)*Sqr(g2)) + (192.*
      traceAdjTYdYd - 192.*MassG*traceAdjYdYd)*Sqr(g3))*(TYe*Ye.adjoint()*
      1.2020569031595942) + threeLoop*(-32.4*Quad(g1) - 18.*Quad(g2) + 64.8*Sqr
      (g1)*Sqr(g2))*(TYe*(TYe).adjoint()*1.2020569031595942))*UNITMATRIX(3))
      .real();
   const Eigen::Matrix<double,3,3> beta_me2_4 = ((threeLoop*((16.8*
      traceAdjYdYd + 21.6*traceAdjYeYe)*Sqr(g1) + (-108.*traceAdjYdYd - 36.*
      traceAdjYeYe)*Sqr(g2) + 192.*traceAdjYdYd*Sqr(g3))*(TYe*(TYe).adjoint()*
      1.2020569031595942) + threeLoop*(-16.2*Quad(g1) - 9.*Quad(g2) + (-54.*
      traceAdjYdYd - 18.*traceAdjYeYe)*Sqr(g2) + Sqr(g1)*(8.4*traceAdjYdYd +
      10.8*traceAdjYeYe + 32.4*Sqr(g2)) + 96.*traceAdjYdYd*Sqr(g3))*(me2*Ye*
      Ye.adjoint()*1.2020569031595942) + threeLoop*(-32.4*Quad(g1) - 18.*Quad(
      g2) + (-108.*traceAdjYdYd - 36.*traceAdjYeYe)*Sqr(g2) + Sqr(g1)*(16.8*
      traceAdjYdYd + 21.6*traceAdjYeYe + 64.8*Sqr(g2)) + 192.*traceAdjYdYd*Sqr(
      g3))*(Ye*ml2*Ye.adjoint()*1.2020569031595942) + threeLoop*(-16.2*Quad(g1)
      - 9.*Quad(g2) + (-54.*traceAdjYdYd - 18.*traceAdjYeYe)*Sqr(g2) + Sqr(g1)
      *(8.4*traceAdjYdYd + 10.8*traceAdjYeYe + 32.4*Sqr(g2)) + 96.*traceAdjYdYd
      *Sqr(g3))*(Ye*Ye.adjoint()*me2*1.2020569031595942) + threeLoop*(36.*mHd2*
      traceAdjYdYd + 12.*traceAdjYdYdmq2 + 12.*mHd2*traceAdjYeYe + 4.*
      traceAdjYeYeml2 + 12.*traceTYdAdjTYd + 4.*traceTYeAdjTYe + 12.*
      traceYdAdjYdmd2 + 4.*traceYeAdjYeme2 + Sqr(g1)*(7.2*mHd2 + 7.2*Sqr(MassB)
      ) + Sqr(g2)*(36.*mHd2 + 36.*Sqr(MassWB)))*(Ye*Ye.adjoint()*Ye*Ye.adjoint(
      )) + threeLoop*(12.*traceTYdAdjYd + 4.*traceTYeAdjYe - 3.6*MassB*Sqr(g1)
      - 18.*MassWB*Sqr(g2))*(Ye*Ye.adjoint()*Ye*(TYe).adjoint()) + threeLoop*(
      12.*traceAdjTYdYd + 4.*traceAdjTYeYe - 3.6*MassB*Sqr(g1) - 18.*MassWB*Sqr
      (g2))*(Ye*Ye.adjoint()*TYe*Ye.adjoint()) + threeLoop*(12.*traceAdjYdYd +
      4.*traceAdjYeYe + 3.6*Sqr(g1) + 18.*Sqr(g2))*(Ye*Ye.adjoint()*TYe*(TYe)
      .adjoint()) + threeLoop*(12.*traceTYdAdjYd + 4.*traceTYeAdjYe - 3.6*MassB
      *Sqr(g1) - 18.*MassWB*Sqr(g2))*(Ye*(TYe).adjoint()*Ye*Ye.adjoint()) +
      threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 3.6*Sqr(g1) + 18.*Sqr(g2)
      )*(Ye*(TYe).adjoint()*TYe*Ye.adjoint()) + threeLoop*(12.*traceAdjTYdYd +
      4.*traceAdjTYeYe - 3.6*MassB*Sqr(g1) - 18.*MassWB*Sqr(g2))*(TYe*
      Ye.adjoint()*Ye*Ye.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe + 3.6*Sqr(g1) + 18.*Sqr(g2))*(TYe*Ye.adjoint()*Ye*(TYe)
      .adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 3.6*Sqr(g1)
      + 18.*Sqr(g2))*(TYe*(TYe).adjoint()*Ye*Ye.adjoint()) + threeLoop*(6.*
      traceAdjYdYd + 2.*traceAdjYeYe + 1.8*Sqr(g1) + 9.*Sqr(g2))*(me2*Ye*
      Ye.adjoint()*Ye*Ye.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*
      traceAdjYeYe + 3.6*Sqr(g1) + 18.*Sqr(g2))*(Ye*ml2*Ye.adjoint()*Ye*
      Ye.adjoint()) + threeLoop*(12.*traceAdjYdYd + 4.*traceAdjYeYe + 3.6*Sqr(
      g1) + 18.*Sqr(g2))*(Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()) + threeLoop*(12.
      *traceAdjYdYd + 4.*traceAdjYeYe + 3.6*Sqr(g1) + 18.*Sqr(g2))*(Ye*
      Ye.adjoint()*Ye*ml2*Ye.adjoint()) + threeLoop*(Sqr(g1)*(43.2*mHd2 + 43.2*
      Sqr(MassB)) + Sqr(g2)*(-72.*mHd2 - 72.*Sqr(MassWB)))*(Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*1.2020569031595942) + threeLoop*(6.*traceAdjYdYd + 2.*
      traceAdjYeYe + 1.8*Sqr(g1) + 9.*Sqr(g2))*(Ye*Ye.adjoint()*Ye*Ye.adjoint()
      *me2) + threeLoop*(-21.6*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2))*(Ye*
      Ye.adjoint()*Ye*(TYe).adjoint()*1.2020569031595942) - 21.6*MassB*
      threeLoop*Sqr(g1)*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*1.2020569031595942))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_5 = ((36.*MassWB*threeLoop*
      Sqr(g2)*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*1.2020569031595942) + threeLoop
      *(21.6*Sqr(g1) - 36.*Sqr(g2))*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()*
      1.2020569031595942) + threeLoop*(-21.6*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2)
      )*(Ye*(TYe).adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + threeLoop*(
      21.6*Sqr(g1) - 36.*Sqr(g2))*(Ye*(TYe).adjoint()*TYe*Ye.adjoint()*
      1.2020569031595942) + threeLoop*(-21.6*MassB*Sqr(g1) + 36.*MassWB*Sqr(g2)
      )*(TYe*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + threeLoop*(21.6
      *Sqr(g1) - 36.*Sqr(g2))*(TYe*Ye.adjoint()*Ye*(TYe).adjoint()*
      1.2020569031595942) + threeLoop*(21.6*Sqr(g1) - 36.*Sqr(g2))*(TYe*(TYe)
      .adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + threeLoop*(10.8*Sqr(g1)
      - 18.*Sqr(g2))*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) +
      threeLoop*(21.6*Sqr(g1) - 36.*Sqr(g2))*(Ye*ml2*Ye.adjoint()*Ye*
      Ye.adjoint()*1.2020569031595942) + threeLoop*(21.6*Sqr(g1) - 36.*Sqr(g2))
      *(Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*1.2020569031595942) + threeLoop*(
      21.6*Sqr(g1) - 36.*Sqr(g2))*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*
      1.2020569031595942) + threeLoop*(10.8*Sqr(g1) - 18.*Sqr(g2))*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*me2*1.2020569031595942) + 36.*mHd2*threeLoop
      *(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*TYe*(TYe).adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*(TYe).adjoint()*TYe*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*TYe*Ye.adjoint()*Ye*(TYe).adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*TYe*(TYe).adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*(
      TYe).adjoint()*Ye*Ye.adjoint()*TYe*Ye.adjoint()) + 12.*threeLoop*(Ye*(TYe
      ).adjoint()*TYe*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(TYe*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*(TYe).adjoint()) + 12.*threeLoop*(TYe*
      Ye.adjoint()*Ye*(TYe).adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(TYe*(
      TYe).adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 6.*threeLoop*(me2*Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*ml2*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()) + 72.*mHd2*threeLoop*(
      Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 6.*
      threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2) + 24.*
      threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*(TYe).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*Ye*(TYe).adjoint()*
      TYe*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*TYe
      *Ye.adjoint()*Ye*(TYe).adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*
      Ye.adjoint()*TYe*(TYe).adjoint()*Ye*Ye.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Ye*(TYe).adjoint()*Ye*Ye.adjoint()*TYe*Ye.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Ye*(TYe).adjoint()*TYe*Ye.adjoint()*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYe*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*(TYe).adjoint()*1.2020569031595942) + 24.*threeLoop*(TYe*
      Ye.adjoint()*Ye*(TYe).adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 24.
      *threeLoop*(TYe*(TYe).adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 12.*threeLoop*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*ml2*Ye.adjoint()*
      Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*
      Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*ml2*Ye.adjoint()*1.2020569031595942) + 12.*threeLoop*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2*1.2020569031595942))*
      UNITMATRIX(3)).real();

   beta_me2 = beta_me2_1 + beta_me2_2 + beta_me2_3 + beta_me2_4 +
      beta_me2_5;


   return beta_me2;
}

} // namespace flexiblesusy
