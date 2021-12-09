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

// File generated at Thu 10 Oct 2019 17:27:42

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
 * Calculates the 1-loop beta function of mHd2.
 *
 * @return 1-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHd2_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceconjTYdTpTYd = TRACE_STRUCT.traceconjTYdTpTYd;
   const double traceconjTYeTpTYe = TRACE_STRUCT.traceconjTYeTpTYe;
   const double tracemd2YdAdjYd = TRACE_STRUCT.tracemd2YdAdjYd;
   const double traceme2YeAdjYe = TRACE_STRUCT.traceme2YeAdjYe;
   const double traceml2AdjYeYe = TRACE_STRUCT.traceml2AdjYeYe;
   const double tracemq2AdjYdYd = TRACE_STRUCT.tracemq2AdjYdYd;
   const double Tr11 = TRACE_STRUCT.Tr11;


   double beta_mHd2;

   beta_mHd2 = Re(0.2*oneOver16PiSqr*(-3.872983346207417*g1*Tr11 + 30*
      traceconjTYdTpTYd + 10*traceconjTYeTpTYe + 30*tracemd2YdAdjYd + 10*
      traceme2YeAdjYe + 10*traceml2AdjYeYe + 30*tracemq2AdjYdYd + 30*mHd2*
      traceYdAdjYd + 10*mHd2*traceYeAdjYe - 6*AbsSqr(MassB)*Sqr(g1) - 30*AbsSqr
      (MassWB)*Sqr(g2)));


   return beta_mHd2;
}

/**
 * Calculates the 2-loop beta function of mHd2.
 *
 * @return 2-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHd2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceconjTYdTpYd = TRACE_STRUCT.traceconjTYdTpYd;
   const double traceconjTYdTpTYd = TRACE_STRUCT.traceconjTYdTpTYd;
   const double traceconjTYeTpYe = TRACE_STRUCT.traceconjTYeTpYe;
   const double traceconjTYeTpTYe = TRACE_STRUCT.traceconjTYeTpTYe;
   const double tracemd2YdAdjYd = TRACE_STRUCT.tracemd2YdAdjYd;
   const double traceme2YeAdjYe = TRACE_STRUCT.traceme2YeAdjYe;
   const double traceml2AdjYeYe = TRACE_STRUCT.traceml2AdjYeYe;
   const double tracemq2AdjYdYd = TRACE_STRUCT.tracemq2AdjYdYd;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYdTYdAdjTYd = TRACE_STRUCT.traceYdAdjYdTYdAdjTYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYuTYuAdjTYd = TRACE_STRUCT.traceYdAdjYuTYuAdjTYd;
   const double traceYdAdjTYdTYdAdjYd = TRACE_STRUCT.traceYdAdjTYdTYdAdjYd;
   const double traceYdAdjTYuTYuAdjYd = TRACE_STRUCT.traceYdAdjTYuTYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYeAdjYeTYeAdjTYe = TRACE_STRUCT.traceYeAdjYeTYeAdjTYe;
   const double traceYeAdjTYeTYeAdjYe = TRACE_STRUCT.traceYeAdjTYeTYeAdjYe;
   const double traceYuAdjYdTYdAdjTYu = TRACE_STRUCT.traceYuAdjYdTYdAdjTYu;
   const double traceYuAdjTYdTYdAdjYu = TRACE_STRUCT.traceYuAdjTYdTYdAdjYu;
   const double tracemd2YdAdjYdYdAdjYd = TRACE_STRUCT.tracemd2YdAdjYdYdAdjYd;
   const double tracemd2YdAdjYuYuAdjYd = TRACE_STRUCT.tracemd2YdAdjYuYuAdjYd;
   const double traceme2YeAdjYeYeAdjYe = TRACE_STRUCT.traceme2YeAdjYeYeAdjYe;
   const double traceml2AdjYeYeAdjYeYe = TRACE_STRUCT.traceml2AdjYeYeAdjYeYe;
   const double tracemq2AdjYdYdAdjYdYd = TRACE_STRUCT.tracemq2AdjYdYdAdjYdYd;
   const double tracemq2AdjYdYdAdjYuYu = TRACE_STRUCT.tracemq2AdjYdYdAdjYuYu;
   const double tracemq2AdjYuYuAdjYdYd = TRACE_STRUCT.tracemq2AdjYuYuAdjYdYd;
   const double tracemu2YuAdjYdYdAdjYu = TRACE_STRUCT.tracemu2YuAdjYdYdAdjYu;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr22 = TRACE_STRUCT.Tr22;


   double beta_mHd2;

   beta_mHd2 = Re(0.04*twoLoop*(-77.45966692414834*g1*Tr31 - 900*
      tracemd2YdAdjYdYdAdjYd - 150*tracemd2YdAdjYuYuAdjYd - 300*
      traceme2YeAdjYeYeAdjYe - 300*traceml2AdjYeYeAdjYeYe - 900*
      tracemq2AdjYdYdAdjYdYd - 150*tracemq2AdjYdYdAdjYuYu - 150*
      tracemq2AdjYuYuAdjYdYd - 150*tracemu2YuAdjYdYdAdjYu - 900*
      traceYdAdjTYdTYdAdjYd - 150*traceYdAdjTYuTYuAdjYd - 900*
      traceYdAdjYdTYdAdjTYd - 900*mHd2*traceYdAdjYdYdAdjYd - 150*
      traceYdAdjYuTYuAdjTYd - 150*mHd2*traceYdAdjYuYuAdjYd - 150*mHu2*
      traceYdAdjYuYuAdjYd - 300*traceYeAdjTYeTYeAdjYe - 300*
      traceYeAdjYeTYeAdjTYe - 300*mHd2*traceYeAdjYeYeAdjYe - 150*
      traceYuAdjTYdTYdAdjYu - 150*traceYuAdjYdTYdAdjTYu + 621*AbsSqr(MassB)*
      Quad(g1) + 150*Tr22*Quad(g2) + 825*AbsSqr(MassWB)*Quad(g2) + 30*Tr2U111*
      Sqr(g1) - 20*traceconjTYdTpTYd*Sqr(g1) + 20*MassB*traceconjTYdTpYd*Sqr(g1
      ) + 60*traceconjTYeTpTYe*Sqr(g1) - 60*MassB*traceconjTYeTpYe*Sqr(g1) - 20
      *tracemd2YdAdjYd*Sqr(g1) + 60*traceme2YeAdjYe*Sqr(g1) + 60*
      traceml2AdjYeYe*Sqr(g1) - 20*tracemq2AdjYdYd*Sqr(g1) - 20*mHd2*
      traceYdAdjYd*Sqr(g1) + 60*mHd2*traceYeAdjYe*Sqr(g1) - 40*traceYdAdjYd*
      AbsSqr(MassB)*Sqr(g1) + 120*traceYeAdjYe*AbsSqr(MassB)*Sqr(g1) + 20*
      traceAdjYdTYd*Conj(MassB)*Sqr(g1) - 60*traceAdjYeTYe*Conj(MassB)*Sqr(g1)
      + 90*AbsSqr(MassB)*Sqr(g1)*Sqr(g2) + 90*AbsSqr(MassWB)*Sqr(g1)*Sqr(g2) +
      45*MassWB*Conj(MassB)*Sqr(g1)*Sqr(g2) + 45*MassB*Conj(MassWB)*Sqr(g1)*Sqr
      (g2) + 800*traceconjTYdTpTYd*Sqr(g3) - 800*MassG*traceconjTYdTpYd*Sqr(g3)
      + 800*tracemd2YdAdjYd*Sqr(g3) + 800*tracemq2AdjYdYd*Sqr(g3) + 800*mHd2*
      traceYdAdjYd*Sqr(g3) + 1600*traceYdAdjYd*AbsSqr(MassG)*Sqr(g3) - 800*
      traceAdjYdTYd*Conj(MassG)*Sqr(g3)));


   return beta_mHd2;
}

/**
 * Calculates the 3-loop beta function of mHd2.
 *
 * @return 3-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHd2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdTYdAdjTYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdTYdAdjTYdYd;
   const double traceAdjYdYdAdjTYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjTYdTYdAdjYdYd;
   const double traceAdjYdTYdAdjYdYdAdjTYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjYdYdAdjTYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeTYeAdjTYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeTYeAdjTYeYe;
   const double traceAdjYeYeAdjTYeTYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjTYeTYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYeAdjTYeYe = TRACE_STRUCT.
      traceAdjYeTYeAdjYeYeAdjTYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjTYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjTYdYd;
   const double traceAdjYuYuAdjTYdTYdAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjTYdTYdAdjYuYu;
   const double traceAdjYuYuAdjTYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjTYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjTYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjTYuYuAdjYdYd;
   const double traceAdjTYuYuAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjTYuYuAdjYuTYuAdjYdYd;
   const double traceAdjTYuTYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjTYuTYuAdjYuYuAdjYdYd;
   const double traceTYdAdjYuYuAdjTYuYuAdjYd = TRACE_STRUCT.
      traceTYdAdjYuYuAdjTYuYuAdjYd;
   const double traceTYdAdjTYuYuAdjYuYuAdjYd = TRACE_STRUCT.
      traceTYdAdjTYuYuAdjYuYuAdjYd;
   const double traceYdAdjYdYdAdjYdYdAdjYdmd2 = TRACE_STRUCT.
      traceYdAdjYdYdAdjYdYdAdjYdmd2;
   const double traceYdAdjYuYuAdjYuYuAdjYdmd2 = TRACE_STRUCT.
      traceYdAdjYuYuAdjYuYuAdjYdmd2;
   const double traceYeAdjYeYeAdjYeYeAdjYeme2 = TRACE_STRUCT.
      traceYeAdjYeYeAdjYeYeAdjYeme2;
   const double traceYuAdjYdYdAdjYuYuAdjYumu2 = TRACE_STRUCT.
      traceYuAdjYdYdAdjYuYuAdjYumu2;
   const double traceYuAdjYuYuAdjYdYdAdjYumu2 = TRACE_STRUCT.
      traceYuAdjYuYuAdjYdYdAdjYumu2;
   const double traceAdjYdYdAdjYdYdAdjYdYdmq2 = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYdmq2;
   const double traceAdjYdYdAdjYuYuAdjYuYumq2 = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYuYumq2;
   const double traceAdjYeYeAdjYeYeAdjYeYeml2 = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYeml2;
   const double traceAdjYuYuAdjYdYdAdjYuYumq2 = TRACE_STRUCT.
      traceAdjYuYuAdjYdYdAdjYuYumq2;
   const double traceAdjYuYuAdjYuYuAdjYdYdmq2 = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYdmq2;


   double beta_mHd2;

   const double beta_mHd2_1 = Re(239.45914429835202*threeLoop*(
      0.07516939915885217*traceAdjTYuTYuAdjYuYuAdjYdYd + 0.07516939915885217*
      traceAdjTYuYuAdjYuTYuAdjYdYd + 0.9020327899062259*traceAdjTYdYd*
      traceAdjYdTYdAdjYdYd + 0.30067759663540866*traceAdjTYeYe*
      traceAdjYdTYdAdjYdYd + 0.6173167701503955*traceAdjYdTYdAdjYdYdAdjTYdYd +
      0.9020327899062259*traceAdjTYdTYdAdjYdYd*traceAdjYdYd +
      0.30067759663540866*traceAdjTYeTYeAdjYeYe*traceAdjYdYd +
      0.9020327899062259*traceAdjYdTYdAdjTYdYd*traceAdjYdYd +
      0.6173167701503955*traceAdjYdYdAdjTYdTYdAdjYdYd + 0.6173167701503955*
      traceAdjYdYdAdjYdTYdAdjTYdYd + 1.353049184859339*mHd2*traceAdjYdYd*
      traceAdjYdYdAdjYdYd + 0.6173167701503955*mHd2*traceAdjYdYdAdjYdYdAdjYdYd
      + 0.6173167701503955*traceAdjYdYdAdjYdYdAdjYdYdmq2 - 0.020746754167843197
      *mHd2*Power6(g1) - 0.020746754167843197*mHu2*Power6(g1) -
      0.012528233193142026*mHd2*Power6(g2) - 0.012528233193142026*mHu2*Power6(
      g2) + 0.2745270139898719*MassB*traceAdjTYdYd*Quad(g1) +
      0.47110613210481683*MassB*traceAdjTYeYe*Quad(g1) + 0.06514681260433854*
      MassB*traceAdjTYuYu*Quad(g1) - 0.13876689497811298*mHd2*traceAdjYdYd*Quad
      (g1) + 0.002004517310902724*mHu2*traceAdjYdYd*Quad(g1) +
      2.837133287956054*MassWB*traceAdjTYdYd*Quad(g2) + 0.9457110959853513*
      MassWB*traceAdjTYeYe*Quad(g2) + 0.3758469957942608*MassWB*traceAdjTYuYu*
      Quad(g2) - 1.456151343557453*mHd2*traceAdjYdYd*Quad(g2) +
      1.2121690987665699*MassG*traceAdjTYdYd*Quad(g3) - 0.6060845493832849*mHd2
      *traceAdjYdYd*Quad(g3) + 0.26697188116918547*traceAdjTYdTYdAdjYdYd*Sqr(g1
      ) + 0.06428886237854617*traceAdjTYdTYdAdjYuYu*Sqr(g1) -
      0.06652015007891307*traceAdjTYeTYeAdjYeYe*Sqr(g1) + 0.06428886237854617*
      traceAdjTYuTYuAdjYdYd*Sqr(g1) - 0.06428886237854617*MassB*
      traceAdjTYuYuAdjYdYd*Sqr(g1) + 0.26697188116918547*traceAdjYdTYdAdjTYdYd*
      Sqr(g1) - 0.26697188116918547*MassB*traceAdjYdTYdAdjYdYd*Sqr(g1) -
      0.26697188116918547*MassB*traceAdjYdYdAdjTYdYd*Sqr(g1) +
      0.26697188116918547*mHd2*traceAdjYdYdAdjYdYd*Sqr(g1) +
      0.26697188116918547*traceAdjYdYdAdjYdYdmq2*Sqr(g1) - 0.2501190234360739*
      MassB*MassWB*Quad(g2)*Sqr(g1) - 0.007516939915885216*mHd2*Quad(g2)*Sqr(g1
      ) - 0.007516939915885216*mHu2*Quad(g2)*Sqr(g1) + 1.234633540300791*
      traceAdjTYdTYdAdjYdYd*Sqr(g2) + 0.15033879831770433*traceAdjTYdTYdAdjYuYu
      *Sqr(g2) + 0.41154451343359705*traceAdjTYeTYeAdjYeYe*Sqr(g2) +
      0.15033879831770433*traceAdjTYuTYuAdjYdYd*Sqr(g2) - 0.15033879831770433*
      MassWB*traceAdjTYuYuAdjYdYd*Sqr(g2) + 1.234633540300791*
      traceAdjYdTYdAdjTYdYd*Sqr(g2) - 1.234633540300791*MassWB*
      traceAdjYdTYdAdjYdYd*Sqr(g2) - 1.234633540300791*MassWB*
      traceAdjYdYdAdjTYdYd*Sqr(g2) + 1.234633540300791*mHd2*traceAdjYdYdAdjYdYd
      *Sqr(g2) + 1.234633540300791*traceAdjYdYdAdjYdYdmq2*Sqr(g2) -
      0.18615272565789337*MassB*MassWB*Quad(g1)*Sqr(g2) - 0.00451016394953113*
      mHd2*Quad(g1)*Sqr(g2) - 0.00451016394953113*mHu2*Quad(g1)*Sqr(g2) +
      0.09286354180388565*MassB*traceAdjTYdYd*Sqr(g1)*Sqr(g2) +
      0.09286354180388565*MassWB*traceAdjTYdYd*Sqr(g1)*Sqr(g2) -
      0.09499175205449609*MassB*traceAdjTYeYe*Sqr(g1)*Sqr(g2) -
      0.09499175205449609*MassWB*traceAdjTYeYe*Sqr(g1)*Sqr(g2) -
      0.1857270836077713*MassB*MassWB*traceAdjYdYd*Sqr(g1)*Sqr(g2) -
      0.09286354180388565*mHd2*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 1.688742258746597
      *traceAdjTYdTYdAdjYdYd*Sqr(g3) - 0.28145704312443287*
      traceAdjTYdTYdAdjYuYu*Sqr(g3) - 0.28145704312443287*traceAdjTYuTYuAdjYdYd
      *Sqr(g3) + 0.28145704312443287*MassG*traceAdjTYuYuAdjYdYd*Sqr(g3) -
      1.688742258746597*traceAdjYdTYdAdjTYdYd*Sqr(g3) + 1.688742258746597*MassG
      *traceAdjYdTYdAdjYdYd*Sqr(g3) + 1.688742258746597*MassG*
      traceAdjYdYdAdjTYdYd*Sqr(g3) - 1.688742258746597*mHd2*traceAdjYdYdAdjYdYd
      *Sqr(g3) - 0.1951257735648116*MassB*MassG*Quad(g1)*Sqr(g3) -
      1.330403001578261*MassG*MassWB*Quad(g2)*Sqr(g3) - 0.0667566178845364*
      MassB*traceAdjTYdYd*Sqr(g1)*Sqr(g3) - 0.0667566178845364*MassG*
      traceAdjTYdYd*Sqr(g1)*Sqr(g3) + 0.1335132357690728*MassB*MassG*
      traceAdjYdYd*Sqr(g1)*Sqr(g3) + 0.0667566178845364*mHd2*traceAdjYdYd*Sqr(
      g1)*Sqr(g3) - 0.3432418016476174*MassG*traceAdjTYdYd*Sqr(g2)*Sqr(g3) -
      0.3432418016476174*MassWB*traceAdjTYdYd*Sqr(g2)*Sqr(g3) +
      0.6864836032952348*MassG*MassWB*traceAdjYdYd*Sqr(g2)*Sqr(g3) +
      0.3432418016476174*mHd2*traceAdjYdYd*Sqr(g2)*Sqr(g3) + 1.*Power6(g1)*Sqr(
      MassB) - 0.8235810419696156*traceAdjYdYd*Quad(g1)*Sqr(MassB) +
      0.26697188116918547*traceAdjYdYdAdjYdYd*Sqr(g1)*Sqr(MassB) -
      0.1025086919703813*Quad(g2)*Sqr(g1)*Sqr(MassB) - 0.2792290884868401*Quad(
      g1)*Sqr(g2)*Sqr(MassB) - 0.1857270836077713*traceAdjYdYd*Sqr(g1)*Sqr(g2)*
      Sqr(MassB) - 0.29268866034721747*Quad(g1)*Sqr(g3)*Sqr(MassB) +
      0.1335132357690728*traceAdjYdYd*Sqr(g1)*Sqr(g3)*Sqr(MassB) -
      2.8347003719386197*traceAdjYdYd*Quad(g3)*Sqr(MassG) - 1.688742258746597*
      traceAdjYdYdAdjYdYd*Sqr(g3)*Sqr(MassG) - 0.053463505942545855*Quad(g1)*
      Sqr(g3)*Sqr(MassG) - 0.3645239041537219*Quad(g2)*Sqr(g3)*Sqr(MassG) +
      0.1335132357690728*traceAdjYdYd*Sqr(g1)*Sqr(g3)*Sqr(MassG) +
      0.6864836032952348*traceAdjYdYd*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      27.982957650573137*Power6(g2)*Sqr(MassWB) - 8.511399863868162*
      traceAdjYdYd*Quad(g2)*Sqr(MassWB) - 0.34511077549057*Quad(g2)*Sqr(g1)*Sqr
      (MassWB) + 1.234633540300791*traceAdjYdYdAdjYdYd*Sqr(g2)*Sqr(MassWB) -
      0.0795458709803533*Quad(g1)*Sqr(g2)*Sqr(MassWB) - 0.1857270836077713*
      traceAdjYdYd*Sqr(g1)*Sqr(g2)*Sqr(MassWB) - 1.9956045023673916*Quad(g2)*
      Sqr(g3)*Sqr(MassWB) + 0.6864836032952348*traceAdjYdYd*Sqr(g2)*Sqr(g3)*Sqr
      (MassWB)));
   const double beta_mHd2_2 = Re(-145.1324875677737*threeLoop*(-
      1.488295306032929*traceAdjYdYd*traceAdjYdYdAdjYdYdmq2 -
      0.12402460883607741*traceAdjYdYdAdjYuYuAdjYuYumq2 - 0.7441476530164645*
      traceAdjYdYdAdjYdYd*traceAdjYdYdmq2 - 0.49609843534430964*traceAdjYdYd*
      traceAdjYeTYeAdjTYeYe - 0.49609843534430964*traceAdjTYdYd*
      traceAdjYeTYeAdjYeYe - 0.16536614511476988*traceAdjTYeYe*
      traceAdjYeTYeAdjYeYe - 0.33951081070484296*traceAdjYeTYeAdjYeYeAdjTYeYe -
      0.49609843534430964*traceAdjTYdTYdAdjYdYd*traceAdjYeYe -
      0.16536614511476988*traceAdjTYeTYeAdjYeYe*traceAdjYeYe -
      0.49609843534430964*traceAdjYdTYdAdjTYdYd*traceAdjYeYe -
      0.7441476530164645*mHd2*traceAdjYdYdAdjYdYd*traceAdjYeYe -
      0.49609843534430964*traceAdjYdYdAdjYdYdmq2*traceAdjYeYe -
      0.16536614511476988*traceAdjYeTYeAdjTYeYe*traceAdjYeYe -
      0.33951081070484296*traceAdjYeYeAdjTYeTYeAdjYeYe - 0.33951081070484296*
      traceAdjYeYeAdjYeTYeAdjTYeYe - 0.7441476530164645*mHd2*traceAdjYdYd*
      traceAdjYeYeAdjYeYe - 0.24804921767215482*traceAdjYdYdmq2*
      traceAdjYeYeAdjYeYe - 0.24804921767215482*mHd2*traceAdjYeYe*
      traceAdjYeYeAdjYeYe - 0.33951081070484296*mHd2*traceAdjYeYeAdjYeYeAdjYeYe
       - 0.33951081070484296*traceAdjYeYeAdjYeYeAdjYeYeml2 -
      0.49609843534430964*traceAdjYdYd*traceAdjYeYeAdjYeYeml2 -
      0.16536614511476988*traceAdjYeYe*traceAdjYeYeAdjYeYeml2 -
      0.24804921767215482*traceAdjYdYdAdjYdYd*traceAdjYeYeml2 -
      0.08268307255738494*traceAdjYeYeAdjYeYe*traceAdjYeYeml2 -
      0.12402460883607741*traceAdjYuTYuAdjTYuYuAdjYdYd - 0.24804921767215482*
      traceAdjTYuYu*traceAdjYuTYuAdjYdYd - 0.12402460883607741*
      traceAdjYuTYuAdjYuYuAdjTYdYd - 0.24804921767215482*traceAdjTYdTYdAdjYuYu*
      traceAdjYuYu - 0.24804921767215482*traceAdjTYuTYuAdjYdYd*traceAdjYuYu -
      0.24804921767215482*traceAdjYdYdAdjYuYumq2*traceAdjYuYu -
      0.24804921767215482*traceAdjYuTYuAdjTYdYd*traceAdjYuYu -
      0.12402460883607741*traceAdjYuYuAdjTYdTYdAdjYuYu - 0.12402460883607741*
      traceAdjYuYuAdjTYuTYuAdjYdYd - 0.24804921767215482*mHd2*traceAdjYuYu*
      traceAdjYuYuAdjYdYd - 0.49609843534430964*mHu2*traceAdjYuYu*
      traceAdjYuYuAdjYdYd - 0.12402460883607741*traceAdjYuYuAdjYdYdAdjYuYumq2 -
      0.24804921767215482*traceAdjYuYu*traceAdjYuYuAdjYdYdmq2 -
      0.12402460883607741*traceAdjYuYuAdjYuTYuAdjTYdYd - 0.12402460883607741*
      mHd2*traceAdjYuYuAdjYuYuAdjYdYd - 0.24804921767215482*mHu2*
      traceAdjYuYuAdjYuYuAdjYdYd - 0.12402460883607741*
      traceAdjYuYuAdjYuYuAdjYdYdmq2 + 0.23226365435689822*traceAdjYdYdmq2*Quad(
      g1) + 0.4060106501395566*mHd2*traceAdjYeYe*Quad(g1) +
      0.009921968706886192*mHu2*traceAdjYeYe*Quad(g1) + 0.3960886814326704*
      traceAdjYeYeml2*Quad(g1) + 0.06449279659476025*mHu2*traceAdjYuYu*Quad(g1)
      + 2.4025548003808126*traceAdjYdYdmq2*Quad(g2) + 0.8008516001269376*mHd2*
      traceAdjYeYe*Quad(g2) + 0.8008516001269376*traceAdjYeYeml2*Quad(g2) +
      0.37207382650823223*mHu2*traceAdjYuYu*Quad(g2) + 1.*traceAdjYdYdmq2*Quad(
      g3) - 0.10607243237591625*traceAdjYdYdAdjYuYumq2*Sqr(g1) +
      0.10975391163922585*traceAdjYeTYeAdjTYeYe*Sqr(g1) - 0.10975391163922585*
      MassB*traceAdjYeTYeAdjYeYe*Sqr(g1) - 0.10975391163922585*MassB*
      traceAdjYeYeAdjTYeYe*Sqr(g1) + 0.10975391163922585*mHd2*
      traceAdjYeYeAdjYeYe*Sqr(g1) + 0.10975391163922585*traceAdjYeYeAdjYeYeml2*
      Sqr(g1) - 0.10607243237591625*traceAdjYuTYuAdjTYdYd*Sqr(g1) +
      0.10607243237591625*MassB*traceAdjYuTYuAdjYdYd*Sqr(g1) +
      0.10607243237591625*MassB*traceAdjYuYuAdjTYdYd*Sqr(g1) -
      0.10607243237591625*mHd2*traceAdjYuYuAdjYdYd*Sqr(g1) -
      0.10607243237591625*mHu2*traceAdjYuYuAdjYdYd*Sqr(g1) -
      0.10607243237591625*traceAdjYuYuAdjYdYdmq2*Sqr(g1) - 0.24804921767215482*
      traceAdjYdYdAdjYuYumq2*Sqr(g2) - 0.6790216214096859*traceAdjYeTYeAdjTYeYe
      *Sqr(g2) + 0.6790216214096859*MassWB*traceAdjYeTYeAdjYeYe*Sqr(g2) +
      0.6790216214096859*MassWB*traceAdjYeYeAdjTYeYe*Sqr(g2) -
      0.6790216214096859*mHd2*traceAdjYeYeAdjYeYe*Sqr(g2) - 0.6790216214096859*
      traceAdjYeYeAdjYeYeml2*Sqr(g2) - 0.24804921767215482*
      traceAdjYuTYuAdjTYdYd*Sqr(g2) + 0.24804921767215482*MassWB*
      traceAdjYuTYuAdjYdYd*Sqr(g2) + 0.24804921767215482*MassWB*
      traceAdjYuYuAdjTYdYd*Sqr(g2) - 0.24804921767215482*mHd2*
      traceAdjYuYuAdjYdYd*Sqr(g2) - 0.24804921767215482*mHu2*
      traceAdjYuYuAdjYdYd*Sqr(g2) - 0.24804921767215482*traceAdjYuYuAdjYdYdmq2*
      Sqr(g2) + 0.1532187908409445*traceAdjYdYdmq2*Sqr(g1)*Sqr(g2) -
      0.3134603980621316*MassB*MassWB*traceAdjYeYe*Sqr(g1)*Sqr(g2) -
      0.1567301990310658*mHd2*traceAdjYeYe*Sqr(g1)*Sqr(g2) - 0.1567301990310658
      *traceAdjYeYeml2*Sqr(g1)*Sqr(g2) + 2.7863146494411697*
      traceAdjYdYdAdjYdYdmq2*Sqr(g3) + 0.46438577490686167*
      traceAdjYdYdAdjYuYumq2*Sqr(g3) + 0.46438577490686167*
      traceAdjYuTYuAdjTYdYd*Sqr(g3) - 0.46438577490686167*MassG*
      traceAdjYuTYuAdjYdYd*Sqr(g3) - 0.46438577490686167*MassG*
      traceAdjYuYuAdjTYdYd*Sqr(g3) + 0.46438577490686167*mHd2*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 0.46438577490686167*mHu2*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 0.46438577490686167*traceAdjYuYuAdjYdYdmq2*
      Sqr(g3) - 0.1101440681047948*traceAdjYdYdmq2*Sqr(g1)*Sqr(g3) -
      0.5663265991467354*traceAdjYdYdmq2*Sqr(g2)*Sqr(g3) + 2.331883229415035*
      traceAdjYeYe*Quad(g1)*Sqr(MassB) + 0.32246398297380124*traceAdjYuYu*Quad(
      g1)*Sqr(MassB) + 0.10975391163922585*traceAdjYeYeAdjYeYe*Sqr(g1)*Sqr(
      MassB) - 0.2121448647518325*traceAdjYuYuAdjYdYd*Sqr(g1)*Sqr(MassB) -
      0.3134603980621316*traceAdjYeYe*Sqr(g1)*Sqr(g2)*Sqr(MassB) +
      0.9287715498137233*traceAdjYuYuAdjYdYd*Sqr(g3)*Sqr(MassG) +
      4.681084991925548*traceAdjYeYe*Quad(g2)*Sqr(MassWB) + 1.860369132541161*
      traceAdjYuYu*Quad(g2)*Sqr(MassWB) - 0.6790216214096859*
      traceAdjYeYeAdjYeYe*Sqr(g2)*Sqr(MassWB) - 0.49609843534430964*
      traceAdjYuYuAdjYdYd*Sqr(g2)*Sqr(MassWB) - 0.3134603980621316*traceAdjYeYe
      *Sqr(g1)*Sqr(g2)*Sqr(MassWB)));
   const double beta_mHd2_3 = Re(-3.312*threeLoop*(-10.869565217391305*
      traceAdjYuYuAdjYdYd*traceAdjYuYumq2 - 32.608695652173914*
      traceAdjYdYdAdjYdYd*traceTYdAdjTYd - 10.869565217391305*
      traceAdjYeYeAdjYeYe*traceTYdAdjTYd - 10.869565217391305*traceAdjYuYu*
      traceTYdAdjTYuYuAdjYd - 5.434782608695652*traceTYdAdjTYuYuAdjYuYuAdjYd -
      65.21739130434783*traceAdjYdYdAdjTYdYd*traceTYdAdjYd - 21.73913043478261*
      traceAdjYeYeAdjTYeYe*traceTYdAdjYd - 5.434782608695652*
      traceTYdAdjYuYuAdjTYuYuAdjYd - 10.869565217391305*traceAdjTYuYu*
      traceTYdAdjYuYuAdjYd - 10.869565217391305*traceAdjYdYdAdjYdYd*
      traceTYeAdjTYe - 3.6231884057971016*traceAdjYeYeAdjYeYe*traceTYeAdjTYe -
      21.73913043478261*traceAdjYdYdAdjTYdYd*traceTYeAdjYe - 7.246376811594203*
      traceAdjYeYeAdjTYeYe*traceTYeAdjYe - 10.869565217391305*
      traceAdjYuYuAdjYdYd*traceTYuAdjTYu - 10.869565217391305*
      traceAdjTYuYuAdjYdYd*traceTYuAdjYu - 10.869565217391305*
      traceAdjYuYuAdjTYdYd*traceTYuAdjYu - 32.608695652173914*
      traceAdjYdYdAdjYdYd*traceYdAdjYdmd2 - 10.869565217391305*
      traceAdjYeYeAdjYeYe*traceYdAdjYdmd2 - 65.21739130434783*traceAdjYdYd*
      traceYdAdjYdYdAdjYdmd2 - 21.73913043478261*traceAdjYeYe*
      traceYdAdjYdYdAdjYdmd2 - 44.63229032042155*traceYdAdjYdYdAdjYdYdAdjYdmd2
      - 10.869565217391305*traceAdjYuYu*traceYdAdjYuYuAdjYdmd2 -
      5.434782608695652*traceYdAdjYuYuAdjYuYuAdjYdmd2 - 10.869565217391305*
      traceAdjYdYdAdjYdYd*traceYeAdjYeme2 + 1.*tracemd2*Power6(g1) + 3.*
      traceme2*Power6(g1) + 1.5*traceml2*Power6(g1) + 0.5*tracemq2*Power6(g1) +
      4.*tracemu2*Power6(g1) + 0.9057971014492754*traceml2*Power6(g2) +
      2.717391304347826*tracemq2*Power6(g2) + 2.8260869565217392*
      traceAdjYuYumq2*Quad(g1) - 0.09661835748792272*traceAdjYdYd*tracemd2*Quad
      (g1) + 0.28985507246376807*traceAdjYeYe*tracemd2*Quad(g1) -
      0.28985507246376807*traceAdjYdYd*traceme2*Quad(g1) + 0.8695652173913043*
      traceAdjYeYe*traceme2*Quad(g1) - 0.14492753623188404*traceAdjYdYd*
      traceml2*Quad(g1) + 0.43478260869565216*traceAdjYeYe*traceml2*Quad(g1) -
      0.04830917874396136*traceAdjYdYd*tracemq2*Quad(g1) + 0.14492753623188404*
      traceAdjYeYe*tracemq2*Quad(g1) - 0.38647342995169087*traceAdjYdYd*
      tracemu2*Quad(g1) + 1.1594202898550723*traceAdjYeYe*tracemu2*Quad(g1) +
      10.177838746497047*traceTYdAdjTYd*Quad(g1) - 19.8484311161825*MassB*
      traceTYdAdjYd*Quad(g1) + 17.3566834643004*traceTYeAdjTYe*Quad(g1) -
      34.061193015557315*MassB*traceTYeAdjYe*Quad(g1) + 2.8260869565217392*
      traceTYuAdjTYu*Quad(g1) - 4.710144927536232*MassB*traceTYuAdjYu*Quad(g1)
      + 10.177838746497047*traceYdAdjYdmd2*Quad(g1) + 17.3566834643004*
      traceYeAdjYeme2*Quad(g1) + 16.304347826086957*traceAdjYuYumq2*Quad(g2) +
      105.28042110421597*traceTYdAdjTYd*Quad(g2) - 205.1260595997363*MassWB*
      traceTYdAdjYd*Quad(g2) + 35.09347370140532*traceTYeAdjTYe*Quad(g2) -
      68.3753531999121*MassWB*traceTYeAdjYe*Quad(g2) + 16.304347826086957*
      traceTYuAdjTYu*Quad(g2) - 27.17391304347826*MassWB*traceTYuAdjYu*Quad(g2)
      + 105.28042110421597*traceYdAdjYdmd2*Quad(g2) + 35.09347370140532*
      traceYeAdjYeme2*Quad(g2) + 9.66183574879227*traceAdjYdYd*tracemd2*Quad(g3
      ) + 19.32367149758454*traceAdjYdYd*tracemq2*Quad(g3) + 9.66183574879227*
      traceAdjYdYd*tracemu2*Quad(g3) + 43.820195521670804*traceTYdAdjTYd*Quad(
      g3) - 87.64039104334161*MassG*traceTYdAdjYd*Quad(g3) + 43.820195521670804
      *traceYdAdjYdmd2*Quad(g3) - 4.648114726171854*traceTYdAdjTYuYuAdjYd*Sqr(
      g1) + 4.648114726171854*MassB*traceTYdAdjYuYuAdjYd*Sqr(g1) -
      19.302191490487463*traceYdAdjYdYdAdjYdmd2*Sqr(g1) - 4.648114726171854*
      traceYdAdjYuYuAdjYdmd2*Sqr(g1) + 0.5434782608695653*traceml2*Quad(g2)*Sqr
      (g1) + 1.6304347826086958*tracemq2*Quad(g2)*Sqr(g1) - 10.869565217391305*
      traceTYdAdjTYuYuAdjYd*Sqr(g2) + 10.869565217391305*MassWB*
      traceTYdAdjYuYuAdjYd*Sqr(g2) - 89.2645806408431*traceYdAdjYdYdAdjYdmd2*
      Sqr(g2) - 10.869565217391305*traceYdAdjYuYuAdjYdmd2*Sqr(g2) +
      0.21739130434782608*tracemd2*Quad(g1)*Sqr(g2) + 0.6521739130434784*
      traceme2*Quad(g1)*Sqr(g2) + 0.3260869565217392*traceml2*Quad(g1)*Sqr(g2)
      + 0.10869565217391304*tracemq2*Quad(g1)*Sqr(g2) + 0.8695652173913043*
      tracemu2*Quad(g1)*Sqr(g2) + 6.714077372244172*traceTYdAdjTYd*Sqr(g1)*Sqr(
      g2) - 6.714077372244172*MassB*traceTYdAdjYd*Sqr(g1)*Sqr(g2) -
      6.714077372244172*MassWB*traceTYdAdjYd*Sqr(g1)*Sqr(g2) -
      6.867947965691683*traceTYeAdjTYe*Sqr(g1)*Sqr(g2) + 6.867947965691683*
      MassB*traceTYeAdjYe*Sqr(g1)*Sqr(g2) + 6.867947965691683*MassWB*
      traceTYeAdjYe*Sqr(g1)*Sqr(g2) + 6.714077372244172*traceYdAdjYdmd2*Sqr(g1)
      *Sqr(g2) - 6.867947965691683*traceYeAdjYeme2*Sqr(g1)*Sqr(g2) +
      20.349475453901285*traceTYdAdjTYuYuAdjYd*Sqr(g3) - 20.349475453901285*
      MassG*traceTYdAdjYuYuAdjYd*Sqr(g3) + 122.0968527234077*
      traceYdAdjYdYdAdjYdmd2*Sqr(g3) + 20.349475453901285*
      traceYdAdjYuYuAdjYdmd2*Sqr(g3) - 4.826534599904333*traceTYdAdjTYd*Sqr(g1)
      *Sqr(g3) + 4.826534599904333*MassB*traceTYdAdjYd*Sqr(g1)*Sqr(g3) +
      4.826534599904333*MassG*traceTYdAdjYd*Sqr(g1)*Sqr(g3) - 4.826534599904333
      *traceYdAdjYdmd2*Sqr(g1)*Sqr(g3) - 24.81654230373283*traceTYdAdjTYd*Sqr(
      g2)*Sqr(g3) + 24.81654230373283*MassG*traceTYdAdjYd*Sqr(g2)*Sqr(g3) +
      24.81654230373283*MassWB*traceTYdAdjYd*Sqr(g2)*Sqr(g3) -
      24.81654230373283*traceYdAdjYdmd2*Sqr(g2)*Sqr(g3)));
   const double beta_mHd2_4 = Re(12.*threeLoop*(1.*traceAdjYeYeAdjYeYe*
      traceYeAdjYeme2 + 6.*traceAdjYdYd*traceYeAdjYeYeAdjYeme2 + 2.*
      traceAdjYeYe*traceYeAdjYeYeAdjYeme2 + 4.106170709478783*
      traceYeAdjYeYeAdjYeYeAdjYeme2 + 3.*traceAdjYuYu*traceYuAdjYdYdAdjYumu2 +
      1.5*traceYuAdjYdYdAdjYuYuAdjYumu2 + 3.*traceAdjYuYuAdjYdYd*
      traceYuAdjYumu2 + 1.5*traceYuAdjYuYuAdjYdYdAdjYumu2 - 0.7799999999999999*
      traceYuAdjYumu2*Quad(g1) - 4.5*traceYuAdjYumu2*Quad(g2) -
      1.3274048513745398*traceYeAdjYeYeAdjYeme2*Sqr(g1) + 1.2828796644234317*
      traceYuAdjYdYdAdjYumu2*Sqr(g1) + 8.212341418957566*traceYeAdjYeYeAdjYeme2
      *Sqr(g2) + 3.*traceYuAdjYdYdAdjYumu2*Sqr(g2) - 5.616455225276755*
      traceYuAdjYdYdAdjYumu2*Sqr(g3)));

   beta_mHd2 = beta_mHd2_1 + beta_mHd2_2 + beta_mHd2_3 + beta_mHd2_4;


   return beta_mHd2;
}

/**
 * Calculates the 4-loop beta function of mHd2.
 *
 * @return 4-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHd2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_mHd2;

   beta_mHd2 = 0;


   return beta_mHd2;
}

/**
 * Calculates the 5-loop beta function of mHd2.
 *
 * @return 5-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHd2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_mHd2;

   beta_mHd2 = 0;


   return beta_mHd2;
}

} // namespace flexiblesusy
