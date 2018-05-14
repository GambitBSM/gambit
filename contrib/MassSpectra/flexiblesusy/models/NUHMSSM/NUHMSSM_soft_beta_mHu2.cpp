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

// File generated at Thu 10 May 2018 15:02:41

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
 * Calculates the 1-loop beta function of mHu2.
 *
 * @return 1-loop beta function
 */
double NUHMSSM_soft_parameters::calc_beta_mHu2_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double Tr11 = TRACE_STRUCT.Tr11;


   double beta_mHu2;

   beta_mHu2 = Re(oneOver16PiSqr*(0.7745966692414834*g1*Tr11 + 6*
      traceconjTYuTpTYu + 6*tracemq2AdjYuYu + 6*tracemu2YuAdjYu + 6*mHu2*
      traceYuAdjYu - 1.2*AbsSqr(MassB)*Sqr(g1) - 6*AbsSqr(MassWB)*Sqr(g2)));


   return beta_mHu2;
}

/**
 * Calculates the 2-loop beta function of mHu2.
 *
 * @return 2-loop beta function
 */
double NUHMSSM_soft_parameters::calc_beta_mHu2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceconjTYuTpYu = TRACE_STRUCT.traceconjTYuTpYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYuTYuAdjTYd =
      TRACE_STRUCT.traceYdAdjYuTYuAdjTYd;
   const double traceYdAdjTYuTYuAdjYd =
      TRACE_STRUCT.traceYdAdjTYuTYuAdjYd;
   const double traceYuAdjYdTYdAdjTYu =
      TRACE_STRUCT.traceYuAdjYdTYdAdjTYu;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYuAdjYuTYuAdjTYu =
      TRACE_STRUCT.traceYuAdjYuTYuAdjTYu;
   const double traceYuAdjTYdTYdAdjYu =
      TRACE_STRUCT.traceYuAdjTYdTYdAdjYu;
   const double traceYuAdjTYuTYuAdjYu =
      TRACE_STRUCT.traceYuAdjTYuTYuAdjYu;
   const double tracemd2YdAdjYuYuAdjYd =
      TRACE_STRUCT.tracemd2YdAdjYuYuAdjYd;
   const double tracemq2AdjYdYdAdjYuYu =
      TRACE_STRUCT.tracemq2AdjYdYdAdjYuYu;
   const double tracemq2AdjYuYuAdjYdYd =
      TRACE_STRUCT.tracemq2AdjYuYuAdjYdYd;
   const double tracemq2AdjYuYuAdjYuYu =
      TRACE_STRUCT.tracemq2AdjYuYuAdjYuYu;
   const double tracemu2YuAdjYdYdAdjYu =
      TRACE_STRUCT.tracemu2YuAdjYdYdAdjYu;
   const double tracemu2YuAdjYuYuAdjYu =
      TRACE_STRUCT.tracemu2YuAdjYuYuAdjYu;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr22 = TRACE_STRUCT.Tr22;


   double beta_mHu2;

   beta_mHu2 = Re(twoLoop*(3.0983866769659336*g1*Tr31 - 6*
      tracemd2YdAdjYuYuAdjYd - 6*tracemq2AdjYdYdAdjYuYu - 6*
      tracemq2AdjYuYuAdjYdYd - 36*tracemq2AdjYuYuAdjYuYu - 6*
      tracemu2YuAdjYdYdAdjYu - 36*tracemu2YuAdjYuYuAdjYu - 6*
      traceYdAdjTYuTYuAdjYd - 6*traceYdAdjYuTYuAdjTYd - 6*mHd2*
      traceYdAdjYuYuAdjYd - 6*mHu2*traceYdAdjYuYuAdjYd - 6*
      traceYuAdjTYdTYdAdjYu - 36*traceYuAdjTYuTYuAdjYu - 6*
      traceYuAdjYdTYdAdjTYu - 36*traceYuAdjYuTYuAdjTYu - 36*mHu2*
      traceYuAdjYuYuAdjYu + 6*Tr22*Quad(g2) + 33*AbsSqr(MassWB)*Quad(g2) + 1.2*
      Tr2U111*Sqr(g1) + 1.6*traceconjTYuTpTYu*Sqr(g1) - 1.6*MassB*
      traceconjTYuTpYu*Sqr(g1) + 1.6*tracemq2AdjYuYu*Sqr(g1) + 1.6*
      tracemu2YuAdjYu*Sqr(g1) + 1.6*mHu2*traceYuAdjYu*Sqr(g1) + 1.8*(MassB + 2*
      MassWB)*Conj(MassWB)*Sqr(g1)*Sqr(g2) + 0.04*Conj(MassB)*Sqr(g1)*(-40*(
      traceAdjYuTYu - 2*MassB*traceYuAdjYu) + 621*MassB*Sqr(g1) + 45*(2*MassB +
      MassWB)*Sqr(g2)) + 32*traceconjTYuTpTYu*Sqr(g3) - 32*MassG*
      traceconjTYuTpYu*Sqr(g3) + 32*tracemq2AdjYuYu*Sqr(g3) + 32*
      tracemu2YuAdjYu*Sqr(g3) + 32*mHu2*traceYuAdjYu*Sqr(g3) + 64*traceYuAdjYu*
      AbsSqr(MassG)*Sqr(g3) - 32*traceAdjYuTYu*Conj(MassG)*Sqr(g3)));


   return beta_mHu2;
}

/**
 * Calculates the 3-loop beta function of mHu2.
 *
 * @return 3-loop beta function
 */
double NUHMSSM_soft_parameters::calc_beta_mHu2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceml2 = TRACE_STRUCT.traceml2;
   const double tracemq2 = TRACE_STRUCT.tracemq2;
   const double tracemu2 = TRACE_STRUCT.tracemu2;
   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceme2 = TRACE_STRUCT.traceme2;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double tracemd2 = TRACE_STRUCT.tracemd2;
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
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYu =
      TRACE_STRUCT.traceAdjYuTYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYu =
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
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
   const double traceAdjYuYuAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYuYumq2;
   const double traceAdjYdYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYuTYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuTYuAdjTYdYd;
   const double traceAdjYdYdAdjTYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjTYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjTYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjYuYuAdjTYdYd;
   const double traceAdjYdTYdAdjTYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjTYuYuAdjYdYd;
   const double traceAdjYuYuAdjYdTYdAdjTYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYdTYdAdjTYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuTYuAdjTYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjTYuYu;
   const double traceAdjYuYuAdjTYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjTYdTYdAdjYdYd;
   const double traceAdjYuYuAdjTYuTYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjTYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjYdYdAdjTYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjYdYdAdjTYdYd;
   const double traceAdjYuTYuAdjYuYuAdjTYuYu =
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYuAdjYdYd;
   const double traceAdjTYuYuAdjYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjTYuYuAdjYdTYdAdjYdYd;
   const double traceYdAdjYdYdAdjYuYuAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYdmd2;
   const double traceYdAdjYuYuAdjYdYdAdjYdmd2 =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYdmd2;
   const double traceYuAdjYdYdAdjYdYdAdjYumu2 =
      TRACE_STRUCT.traceYuAdjYdYdAdjYdYdAdjYumu2;
   const double traceYuAdjYuYuAdjYuYuAdjYumu2 =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYumu2;
   const double traceAdjYdYdAdjYdYdAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYuYumq2;
   const double traceAdjYdYdAdjYuYuAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYdmq2;
   const double traceAdjYuYuAdjYdYdAdjYdYdmq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYdYdAdjYdYdmq2;
   const double traceAdjYuYuAdjYuYuAdjYuYumq2 =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYumq2;


   double beta_mHu2;

   const double beta_mHu2_1 = Re(threeLoop*(18.*
      traceAdjTYdTYdAdjYuYuAdjYdYd + 18.*traceAdjTYuYuAdjYdTYdAdjYdYd + 18.*
      traceAdjYdTYdAdjTYuYuAdjYdYd + 18.*traceAdjYdTYdAdjYuYuAdjTYdYd + 36.*
      traceAdjTYdTYdAdjYuYu*traceAdjYdYd + 36.*traceAdjTYuTYuAdjYdYd*
      traceAdjYdYd + 18.*traceAdjYdYdAdjTYuTYuAdjYdYd + 18.*
      traceAdjYdYdAdjYdYdAdjYuYumq2 + 18.*traceAdjYdYdAdjYuTYuAdjTYdYd + 36.*
      mHd2*traceAdjYdYdAdjYuYuAdjYdYd + 18.*mHu2*traceAdjYdYdAdjYuYuAdjYdYd +
      18.*traceAdjYdYdAdjYuYuAdjYdYdmq2 + 36.*traceAdjYdYd*
      traceAdjYdYdAdjYuYumq2 + 12.*traceAdjTYdTYdAdjYuYu*traceAdjYeYe + 12.*
      traceAdjTYuTYuAdjYdYd*traceAdjYeYe + 12.*traceAdjYdYdAdjYuYumq2*
      traceAdjYeYe + 36.*traceAdjYdYd*traceAdjYuTYuAdjTYdYd + 12.*traceAdjYeYe*
      traceAdjYuTYuAdjTYdYd + 36.*traceAdjTYdYd*traceAdjYuTYuAdjYdYd + 12.*
      traceAdjTYeYe*traceAdjYuTYuAdjYdYd + 18.*traceAdjYuTYuAdjYdYdAdjTYdYd +
      216.*traceAdjTYuYu*traceAdjYuTYuAdjYuYu + 147.82214554123618*
      traceAdjYuTYuAdjYuYuAdjTYuYu + 290.2649751355474*MassG*traceAdjTYuYu*Quad
      (g3) - 67.39746270332105*traceAdjTYdTYdAdjYuYu*Sqr(g3) -
      67.39746270332105*traceAdjTYuTYuAdjYdYd*Sqr(g3) - 404.38477621992627*
      traceAdjTYuTYuAdjYuYu*Sqr(g3) + 67.39746270332105*MassG*
      traceAdjTYuYuAdjYdYd*Sqr(g3) - 67.39746270332105*traceAdjYdYdAdjYuYumq2*
      Sqr(g3) - 67.39746270332105*traceAdjYuTYuAdjTYdYd*Sqr(g3) -
      404.38477621992627*traceAdjYuTYuAdjTYuYu*Sqr(g3) + 67.39746270332105*
      MassG*traceAdjYuTYuAdjYdYd*Sqr(g3) + 404.38477621992627*MassG*
      traceAdjYuTYuAdjYuYu*Sqr(g3) + Sqr(g2)*(36.*traceAdjTYdTYdAdjYuYu + 36.*
      traceAdjTYuTYuAdjYdYd + 295.64429108247236*traceAdjTYuTYuAdjYuYu - 36.*
      MassWB*traceAdjTYuYuAdjYdYd + 36.*traceAdjYdYdAdjYuYumq2 + 36.*
      traceAdjYuTYuAdjTYdYd + 295.64429108247236*traceAdjYuTYuAdjTYuYu - 36.*
      MassWB*traceAdjYuTYuAdjYdYd - 295.64429108247236*MassWB*
      traceAdjYuTYuAdjYuYu - 82.19238810996313*MassG*traceAdjTYuYu*Sqr(g3) -
      82.19238810996313*MassWB*traceAdjTYuYu*Sqr(g3)) + Power6(g1)*(-4.968*mHd2
      - 4.968*mHu2 + 239.45914429835202*Sqr(MassB)) + Sqr(g1)*(
      5.284936567583026*traceAdjTYdTYdAdjYuYu + 5.284936567583026*
      traceAdjTYuTYuAdjYdYd + 28.290380594501844*traceAdjTYuTYuAdjYuYu -
      5.284936567583026*MassB*traceAdjTYuYuAdjYdYd + 5.284936567583026*
      traceAdjYdYdAdjYuYumq2 + 5.284936567583026*traceAdjYuTYuAdjTYdYd +
      28.290380594501844*traceAdjYuTYuAdjTYuYu - 5.284936567583026*MassB*
      traceAdjYuTYuAdjYdYd - 28.290380594501844*MassB*traceAdjYuTYuAdjYuYu -
      17.34446767621158*MassB*traceAdjTYuYu*Sqr(g3) - 17.34446767621158*MassG*
      traceAdjTYuYu*Sqr(g3) + 34.68893535242316*traceAdjYuYu*Sqr(g3)*Sqr(MassB)
      + Sqr(g2)*(-18.89183395962177*MassB*traceAdjTYuYu - 18.89183395962177*
      MassWB*traceAdjTYuYu + 37.78366791924354*traceAdjYuYu*Sqr(MassB)) + Quad(
      g2)*(-59.893287324741706*MassB*MassWB - 1.8*mHd2 - 1.8*mHu2 -
      24.546643662370855*Sqr(MassB) - 82.63993098711256*Sqr(MassWB))) + Quad(g1
      )*(8.4*MassB*traceAdjTYdYd + 10.8*MassB*traceAdjTYeYe +
      147.78402922976323*MassB*traceAdjTYuYu - 5.04*mHd2*traceAdjYdYd - 5.04*
      traceAdjYdYdmq2 - 6.48*mHd2*traceAdjYeYe - 6.48*traceAdjYeYeml2 - 25.2*
      traceAdjYdYd*Sqr(MassB) - 32.4*traceAdjYeYe*Sqr(MassB) -
      443.3520876892897*traceAdjYuYu*Sqr(MassB) + Sqr(g3)*(-46.72465076838378*
      MassB*MassG - 70.08697615257569*Sqr(MassB) - 12.802325384191889*Sqr(MassG
      )) + Sqr(g2)*(-44.575972394845024*MassB*MassWB - 1.08*mHd2 - 1.08*mHu2 -
      66.86395859226754*Sqr(MassB) - 19.047986197422514*Sqr(MassWB))) + Power6(
      g2)*(-3.*mHd2 - 3.*mHu2 + 6700.775093943266*Sqr(MassWB)) + Quad(g2)*(
      MassWB*(90.*traceAdjTYdYd + 30.*traceAdjTYeYe + 679.3775093943266*
      traceAdjTYuYu) - 54.*mHd2*traceAdjYdYd - 54.*traceAdjYdYdmq2 - 18.*mHd2*
      traceAdjYeYe - 18.*traceAdjYeYeml2 + Sqr(g3)*(-318.57716432988946*MassG*
      MassWB - 87.28858216494473*Sqr(MassG) - 477.8657464948342*Sqr(MassWB)) +
      (-270.*traceAdjYdYd - 90.*traceAdjYeYe)*Sqr(MassWB))));
   const double beta_mHu2_2 = Re(threeLoop*(216.*traceAdjTYuTYuAdjYuYu*
      traceAdjYuYu + 216.*traceAdjYuTYuAdjTYuYu*traceAdjYuYu + 18.*
      traceAdjYuYuAdjTYdTYdAdjYdYd + 147.82214554123618*
      traceAdjYuYuAdjTYuTYuAdjYuYu + 18.*traceAdjYuYuAdjYdTYdAdjTYdYd + 72.*
      mHd2*traceAdjYdYd*traceAdjYuYuAdjYdYd + 36.*mHu2*traceAdjYdYd*
      traceAdjYuYuAdjYdYd + 36.*traceAdjYdYdmq2*traceAdjYuYuAdjYdYd + 24.*mHd2*
      traceAdjYeYe*traceAdjYuYuAdjYdYd + 12.*mHu2*traceAdjYeYe*
      traceAdjYuYuAdjYdYd + 12.*traceAdjYeYeml2*traceAdjYuYuAdjYdYd + 18.*
      traceAdjYuYuAdjYdYdAdjYdYdmq2 + 36.*traceAdjYdYd*traceAdjYuYuAdjYdYdmq2 +
      12.*traceAdjYeYe*traceAdjYuYuAdjYdYdmq2 + 147.82214554123618*
      traceAdjYuYuAdjYuTYuAdjTYuYu + 324.*mHu2*traceAdjYuYu*traceAdjYuYuAdjYuYu
      + 147.82214554123618*mHu2*traceAdjYuYuAdjYuYuAdjYuYu +
      147.82214554123618*traceAdjYuYuAdjYuYuAdjYuYumq2 + 216.*traceAdjYuYu*
      traceAdjYuYuAdjYuYumq2 + 108.*traceAdjYuYuAdjYuYu*traceAdjYuYumq2 + 36.*
      traceAdjYuYuAdjYdYd*traceTYdAdjTYd + 36.*traceAdjYdYd*
      traceTYdAdjTYuYuAdjYd + 12.*traceAdjYeYe*traceTYdAdjTYuYuAdjYd + (-3.312*
      tracemd2 - 9.936*traceme2 - 4.968*traceml2 - 1.656*tracemq2 - 13.248*
      tracemu2)*Power6(g1) + (-3.*traceml2 - 9.*tracemq2)*Power6(g2) -
      145.1324875677737*mHu2*traceAdjYuYu*Quad(g3) - 145.1324875677737*
      traceAdjYuYumq2*Quad(g3) - 31.999999999999996*traceAdjYuYu*tracemd2*Quad(
      g3) - 63.99999999999999*traceAdjYuYu*tracemq2*Quad(g3) -
      31.999999999999996*traceAdjYuYu*tracemu2*Quad(g3) + Quad(g1)*(
      -0.9599999999999999*mHd2*traceAdjYuYu - 76.41201461488161*mHu2*
      traceAdjYuYu - 75.45201461488162*traceAdjYuYumq2 - 0.64*traceAdjYuYu*
      tracemd2 - 1.9199999999999997*traceAdjYuYu*traceme2 - 0.9599999999999999*
      traceAdjYuYu*traceml2 - 0.32*traceAdjYuYu*tracemq2 - 2.56*traceAdjYuYu*
      tracemu2 - 5.04*traceTYdAdjTYd + 8.4*MassB*traceTYdAdjYd - 0.72*tracemd2*
      Sqr(g2) - 2.16*traceme2*Sqr(g2) - 1.08*traceml2*Sqr(g2) - 0.36*tracemq2*
      Sqr(g2) - 2.88*tracemu2*Sqr(g2)) + 67.39746270332105*MassG*
      traceAdjYuYuAdjTYdYd*Sqr(g3) + 404.38477621992627*MassG*
      traceAdjYuYuAdjTYuYu*Sqr(g3) - 67.39746270332105*mHd2*traceAdjYuYuAdjYdYd
      *Sqr(g3) - 67.39746270332105*mHu2*traceAdjYuYuAdjYdYd*Sqr(g3) -
      67.39746270332105*traceAdjYuYuAdjYdYdmq2*Sqr(g3) - 404.38477621992627*
      mHu2*traceAdjYuYuAdjYuYu*Sqr(g3) - 404.38477621992627*
      traceAdjYuYuAdjYuYumq2*Sqr(g3) - 67.39746270332105*traceTYdAdjTYuYuAdjYd*
      Sqr(g3) - 678.794925406642*traceAdjYuYu*Quad(g3)*Sqr(MassG) -
      134.7949254066421*traceAdjYuYuAdjYdYd*Sqr(g3)*Sqr(MassG) -
      404.38477621992627*traceAdjYuYuAdjYuYu*Sqr(g3)*Sqr(MassG) + Quad(g2)*(
      -348.6887546971633*mHu2*traceAdjYuYu - 348.6887546971633*traceAdjYuYumq2
      - 54.*traceTYdAdjTYd - 2038.13252818298*traceAdjYuYu*Sqr(MassWB)) + Sqr(
      g1)*(-5.284936567583026*MassB*traceAdjYuYuAdjTYdYd - 28.290380594501844*
      MassB*traceAdjYuYuAdjTYuYu + 5.284936567583026*mHd2*traceAdjYuYuAdjYdYd +
      5.284936567583026*mHu2*traceAdjYuYuAdjYdYd + 5.284936567583026*
      traceAdjYuYuAdjYdYdmq2 + 28.290380594501844*mHu2*traceAdjYuYuAdjYuYu +
      28.290380594501844*traceAdjYuYuAdjYuYumq2 + 5.284936567583026*
      traceTYdAdjTYuYuAdjYd + (-1.8*traceml2 - 5.4*tracemq2)*Quad(g2) +
      10.569873135166052*traceAdjYuYuAdjYdYd*Sqr(MassB) + 28.290380594501844*
      traceAdjYuYuAdjYuYu*Sqr(MassB) + Sqr(g3)*(34.68893535242316*MassB*MassG*
      traceAdjYuYu + 17.34446767621158*mHu2*traceAdjYuYu + 17.34446767621158*
      traceAdjYuYumq2 + 34.68893535242316*traceAdjYuYu*Sqr(MassG)) + Sqr(g2)*(
      37.78366791924354*MassB*MassWB*traceAdjYuYu + 18.89183395962177*mHu2*
      traceAdjYuYu + 18.89183395962177*traceAdjYuYumq2 + 37.78366791924354*
      traceAdjYuYu*Sqr(MassWB))) + Sqr(g2)*(MassWB*(-36.*traceAdjYuYuAdjTYdYd -
      295.64429108247236*traceAdjYuYuAdjTYuYu) + 36.*mHd2*traceAdjYuYuAdjYdYd
      + 36.*mHu2*traceAdjYuYuAdjYdYd + 36.*traceAdjYuYuAdjYdYdmq2 +
      295.64429108247236*mHu2*traceAdjYuYuAdjYuYu + 295.64429108247236*
      traceAdjYuYuAdjYuYumq2 + 36.*traceTYdAdjTYuYuAdjYd + (72.*
      traceAdjYuYuAdjYdYd + 295.64429108247236*traceAdjYuYuAdjYuYu)*Sqr(MassWB)
      + Sqr(g3)*(164.38477621992627*MassG*MassWB*traceAdjYuYu +
      82.19238810996313*mHu2*traceAdjYuYu + 82.19238810996313*traceAdjYuYumq2 +
      164.38477621992627*traceAdjYuYu*Sqr(MassG) + 164.38477621992627*
      traceAdjYuYu*Sqr(MassWB)))));
   const double beta_mHu2_3 = Re(threeLoop*(36.*traceAdjTYuYuAdjYdYd*
      traceTYdAdjYd + 36.*traceAdjYuYuAdjTYdYd*traceTYdAdjYd + 36.*
      traceAdjTYdYd*traceTYdAdjYuYuAdjYd + 12.*traceAdjTYeYe*
      traceTYdAdjYuYuAdjYd + 12.*traceAdjYuYuAdjYdYd*traceTYeAdjTYe + 12.*
      traceAdjTYuYuAdjYdYd*traceTYeAdjYe + 12.*traceAdjYuYuAdjTYdYd*
      traceTYeAdjYe + 108.*traceAdjYuYuAdjYuYu*traceTYuAdjTYu + 216.*
      traceAdjYuYuAdjTYuYu*traceTYuAdjYu + 36.*traceAdjYuYuAdjYdYd*
      traceYdAdjYdmd2 + 18.*traceYdAdjYdYdAdjYuYuAdjYdmd2 + 36.*traceAdjYdYd*
      traceYdAdjYuYuAdjYdmd2 + 12.*traceAdjYeYe*traceYdAdjYuYuAdjYdmd2 + 18.*
      traceYdAdjYuYuAdjYdYdAdjYdmd2 + 12.*traceAdjYuYuAdjYdYd*traceYeAdjYeme2 +
      18.*traceYuAdjYdYdAdjYdYdAdjYumu2 + 36.*traceAdjYdYd*
      traceYuAdjYdYdAdjYumu2 + 12.*traceAdjYeYe*traceYuAdjYdYdAdjYumu2 + 108.*
      traceAdjYuYuAdjYuYu*traceYuAdjYumu2 + 216.*traceAdjYuYu*
      traceYuAdjYuYuAdjYumu2 + 147.82214554123618*traceYuAdjYuYuAdjYuYuAdjYumu2
      - 6.48*traceTYeAdjTYe*Quad(g1) + 10.8*MassB*traceTYeAdjYe*Quad(g1) -
      75.45201461488162*traceTYuAdjTYu*Quad(g1) + 147.78402922976323*MassB*
      traceTYuAdjYu*Quad(g1) - 5.04*traceYdAdjYdmd2*Quad(g1) - 6.48*
      traceYeAdjYeme2*Quad(g1) - 75.45201461488162*traceYuAdjYumu2*Quad(g1) + (
      -18.*traceTYeAdjTYe - 348.6887546971633*traceTYuAdjTYu + MassWB*(90.*
      traceTYdAdjYd + 30.*traceTYeAdjYe + 679.3775093943266*traceTYuAdjYu) -
      54.*traceYdAdjYdmd2 - 18.*traceYeAdjYeme2 - 348.6887546971633*
      traceYuAdjYumu2)*Quad(g2) - 145.1324875677737*traceTYuAdjTYu*Quad(g3) +
      290.2649751355474*MassG*traceTYuAdjYu*Quad(g3) - 145.1324875677737*
      traceYuAdjYumu2*Quad(g3) - 5.284936567583026*MassB*traceTYdAdjYuYuAdjYd*
      Sqr(g1) + 5.284936567583026*traceYdAdjYuYuAdjYdmd2*Sqr(g1) +
      5.284936567583026*traceYuAdjYdYdAdjYumu2*Sqr(g1) + 28.290380594501844*
      traceYuAdjYuYuAdjYumu2*Sqr(g1) + 67.39746270332105*MassG*
      traceTYdAdjYuYuAdjYd*Sqr(g3) - 67.39746270332105*traceYdAdjYuYuAdjYdmd2*
      Sqr(g3) - 67.39746270332105*traceYuAdjYdYdAdjYumu2*Sqr(g3) -
      404.38477621992627*traceYuAdjYuYuAdjYumu2*Sqr(g3) + 17.34446767621158*
      traceTYuAdjTYu*Sqr(g1)*Sqr(g3) - 17.34446767621158*MassB*traceTYuAdjYu*
      Sqr(g1)*Sqr(g3) - 17.34446767621158*MassG*traceTYuAdjYu*Sqr(g1)*Sqr(g3) +
      17.34446767621158*traceYuAdjYumu2*Sqr(g1)*Sqr(g3) + Sqr(g2)*(36.*
      traceYdAdjYuYuAdjYdmd2 + 36.*traceYuAdjYdYdAdjYumu2 + 295.64429108247236*
      traceYuAdjYuYuAdjYumu2 + (18.89183395962177*traceTYuAdjTYu -
      18.89183395962177*MassB*traceTYuAdjYu + 18.89183395962177*traceYuAdjYumu2
      )*Sqr(g1) + 82.19238810996313*traceTYuAdjTYu*Sqr(g3) - 82.19238810996313*
      MassG*traceTYuAdjYu*Sqr(g3) + 82.19238810996313*traceYuAdjYumu2*Sqr(g3) +
      MassWB*(-36.*traceTYdAdjYuYuAdjYd - 18.89183395962177*traceTYuAdjYu*Sqr(
      g1) - 82.19238810996313*traceTYuAdjYu*Sqr(g3)))));

   beta_mHu2 = beta_mHu2_1 + beta_mHu2_2 + beta_mHu2_3;


   return beta_mHu2;
}

} // namespace flexiblesusy
