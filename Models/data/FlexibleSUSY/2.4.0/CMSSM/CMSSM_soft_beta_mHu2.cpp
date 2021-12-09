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

// File generated at Thu 10 Oct 2019 17:27:44

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
 * Calculates the 1-loop beta function of mHu2.
 *
 * @return 1-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHu2_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double Tr11 = TRACE_STRUCT.Tr11;


   double beta_mHu2;

   beta_mHu2 = Re(0.2*oneOver16PiSqr*(3.872983346207417*g1*Tr11 + 30*
      traceconjTYuTpTYu + 30*tracemq2AdjYuYu + 30*tracemu2YuAdjYu + 30*mHu2*
      traceYuAdjYu - 6*AbsSqr(MassB)*Sqr(g1) - 30*AbsSqr(MassWB)*Sqr(g2)));


   return beta_mHu2;
}

/**
 * Calculates the 2-loop beta function of mHu2.
 *
 * @return 2-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHu2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceconjTYuTpYu = TRACE_STRUCT.traceconjTYuTpYu;
   const double traceconjTYuTpTYu = TRACE_STRUCT.traceconjTYuTpTYu;
   const double tracemq2AdjYuYu = TRACE_STRUCT.tracemq2AdjYuYu;
   const double tracemu2YuAdjYu = TRACE_STRUCT.tracemu2YuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYuTYuAdjTYd = TRACE_STRUCT.traceYdAdjYuTYuAdjTYd;
   const double traceYdAdjTYuTYuAdjYd = TRACE_STRUCT.traceYdAdjTYuTYuAdjYd;
   const double traceYuAdjYdTYdAdjTYu = TRACE_STRUCT.traceYuAdjYdTYdAdjTYu;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYuAdjYuTYuAdjTYu = TRACE_STRUCT.traceYuAdjYuTYuAdjTYu;
   const double traceYuAdjTYdTYdAdjYu = TRACE_STRUCT.traceYuAdjTYdTYdAdjYu;
   const double traceYuAdjTYuTYuAdjYu = TRACE_STRUCT.traceYuAdjTYuTYuAdjYu;
   const double tracemd2YdAdjYuYuAdjYd = TRACE_STRUCT.tracemd2YdAdjYuYuAdjYd;
   const double tracemq2AdjYdYdAdjYuYu = TRACE_STRUCT.tracemq2AdjYdYdAdjYuYu;
   const double tracemq2AdjYuYuAdjYdYd = TRACE_STRUCT.tracemq2AdjYuYuAdjYdYd;
   const double tracemq2AdjYuYuAdjYuYu = TRACE_STRUCT.tracemq2AdjYuYuAdjYuYu;
   const double tracemu2YuAdjYdYdAdjYu = TRACE_STRUCT.tracemu2YuAdjYdYdAdjYu;
   const double tracemu2YuAdjYuYuAdjYu = TRACE_STRUCT.tracemu2YuAdjYuYuAdjYu;
   const double Tr2U111 = TRACE_STRUCT.Tr2U111;
   const double Tr31 = TRACE_STRUCT.Tr31;
   const double Tr22 = TRACE_STRUCT.Tr22;


   double beta_mHu2;

   beta_mHu2 = Re(0.04*twoLoop*(77.45966692414834*g1*Tr31 - 150*
      tracemd2YdAdjYuYuAdjYd - 150*tracemq2AdjYdYdAdjYuYu - 150*
      tracemq2AdjYuYuAdjYdYd - 900*tracemq2AdjYuYuAdjYuYu - 150*
      tracemu2YuAdjYdYdAdjYu - 900*tracemu2YuAdjYuYuAdjYu - 150*
      traceYdAdjTYuTYuAdjYd - 150*traceYdAdjYuTYuAdjTYd - 150*mHd2*
      traceYdAdjYuYuAdjYd - 150*mHu2*traceYdAdjYuYuAdjYd - 150*
      traceYuAdjTYdTYdAdjYu - 900*traceYuAdjTYuTYuAdjYu - 150*
      traceYuAdjYdTYdAdjTYu - 900*traceYuAdjYuTYuAdjTYu - 900*mHu2*
      traceYuAdjYuYuAdjYu + 621*AbsSqr(MassB)*Quad(g1) + 150*Tr22*Quad(g2) +
      825*AbsSqr(MassWB)*Quad(g2) + 30*Tr2U111*Sqr(g1) + 40*traceconjTYuTpTYu*
      Sqr(g1) - 40*MassB*traceconjTYuTpYu*Sqr(g1) + 40*tracemq2AdjYuYu*Sqr(g1)
      + 40*tracemu2YuAdjYu*Sqr(g1) + 40*mHu2*traceYuAdjYu*Sqr(g1) + 80*
      traceYuAdjYu*AbsSqr(MassB)*Sqr(g1) - 40*traceAdjYuTYu*Conj(MassB)*Sqr(g1)
      + 90*AbsSqr(MassB)*Sqr(g1)*Sqr(g2) + 90*AbsSqr(MassWB)*Sqr(g1)*Sqr(g2) +
      45*MassWB*Conj(MassB)*Sqr(g1)*Sqr(g2) + 45*MassB*Conj(MassWB)*Sqr(g1)*Sqr
      (g2) + 800*traceconjTYuTpTYu*Sqr(g3) - 800*MassG*traceconjTYuTpYu*Sqr(g3)
      + 800*tracemq2AdjYuYu*Sqr(g3) + 800*tracemu2YuAdjYu*Sqr(g3) + 800*mHu2*
      traceYuAdjYu*Sqr(g3) + 1600*traceYuAdjYu*AbsSqr(MassG)*Sqr(g3) - 800*
      traceAdjYuTYu*Conj(MassG)*Sqr(g3)));


   return beta_mHu2;
}

/**
 * Calculates the 3-loop beta function of mHu2.
 *
 * @return 3-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHu2_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjTYdYd = TRACE_STRUCT.traceAdjYuTYuAdjTYdYd;
   const double traceAdjYuTYuAdjTYuYu = TRACE_STRUCT.traceAdjYuTYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYu = TRACE_STRUCT.traceAdjTYdTYdAdjYuYu;
   const double traceAdjTYuYuAdjYdYd = TRACE_STRUCT.traceAdjTYuYuAdjYdYd;
   const double traceAdjTYuTYuAdjYdYd = TRACE_STRUCT.traceAdjTYuTYuAdjYdYd;
   const double traceAdjTYuTYuAdjYuYu = TRACE_STRUCT.traceAdjTYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceTYdAdjTYuYuAdjYd = TRACE_STRUCT.traceTYdAdjTYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdmd2 = TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2;
   const double traceYuAdjYdYdAdjYumu2 = TRACE_STRUCT.traceYuAdjYdYdAdjYumu2;
   const double traceYuAdjYuYuAdjYumu2 = TRACE_STRUCT.traceYuAdjYuYuAdjYumu2;
   const double traceAdjYdYdAdjYuYumq2 = TRACE_STRUCT.traceAdjYdYdAdjYuYumq2;
   const double traceAdjYuYuAdjYdYdmq2 = TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2;
   const double traceAdjYuYuAdjYuYumq2 = TRACE_STRUCT.traceAdjYuYuAdjYuYumq2;
   const double traceAdjYdYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYuTYuAdjTYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuTYuAdjTYdYd;
   const double traceAdjYdYdAdjTYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjTYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjTYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjYuYuAdjTYdYd;
   const double traceAdjYdTYdAdjTYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjTYuYuAdjYdYd;
   const double traceAdjYuYuAdjYdTYdAdjTYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYdTYdAdjTYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuTYuAdjTYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjTYuYu;
   const double traceAdjYuYuAdjTYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjTYdTYdAdjYdYd;
   const double traceAdjYuYuAdjTYuTYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjTYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjYdYdAdjTYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjYdYdAdjTYdYd;
   const double traceAdjYuTYuAdjYuYuAdjTYuYu = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjTYuYu;
   const double traceAdjTYdTYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjTYdTYdAdjYuYuAdjYdYd;
   const double traceAdjTYuYuAdjYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjTYuYuAdjYdTYdAdjYdYd;
   const double traceYdAdjYdYdAdjYuYuAdjYdmd2 = TRACE_STRUCT.
      traceYdAdjYdYdAdjYuYuAdjYdmd2;
   const double traceYdAdjYuYuAdjYdYdAdjYdmd2 = TRACE_STRUCT.
      traceYdAdjYuYuAdjYdYdAdjYdmd2;
   const double traceYuAdjYdYdAdjYdYdAdjYumu2 = TRACE_STRUCT.
      traceYuAdjYdYdAdjYdYdAdjYumu2;
   const double traceYuAdjYuYuAdjYuYuAdjYumu2 = TRACE_STRUCT.
      traceYuAdjYuYuAdjYuYuAdjYumu2;
   const double traceAdjYdYdAdjYdYdAdjYuYumq2 = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYuYumq2;
   const double traceAdjYdYdAdjYuYuAdjYdYdmq2 = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYdmq2;
   const double traceAdjYuYuAdjYdYdAdjYdYdmq2 = TRACE_STRUCT.
      traceAdjYuYuAdjYdYdAdjYdYdmq2;
   const double traceAdjYuYuAdjYuYuAdjYuYumq2 = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYumq2;


   double beta_mHu2;

   const double beta_mHu2_1 = Re(239.45914429835202*threeLoop*(
      0.07516939915885217*traceAdjTYdTYdAdjYuYuAdjYdYd + 0.07516939915885217*
      traceAdjTYuYuAdjYdTYdAdjYdYd + 0.07516939915885217*
      traceAdjYdTYdAdjTYuYuAdjYdYd + 0.07516939915885217*
      traceAdjYdTYdAdjYuYuAdjTYdYd + 0.15033879831770433*traceAdjTYdTYdAdjYuYu*
      traceAdjYdYd + 0.15033879831770433*traceAdjTYuTYuAdjYdYd*traceAdjYdYd +
      0.07516939915885217*traceAdjYdYdAdjTYuTYuAdjYdYd + 0.07516939915885217*
      traceAdjYdYdAdjYdYdAdjYuYumq2 + 0.07516939915885217*
      traceAdjYdYdAdjYuTYuAdjTYdYd + 0.15033879831770433*mHd2*
      traceAdjYdYdAdjYuYuAdjYdYd + 0.07516939915885217*mHu2*
      traceAdjYdYdAdjYuYuAdjYdYd + 0.07516939915885217*
      traceAdjYdYdAdjYuYuAdjYdYdmq2 + 0.15033879831770433*traceAdjYdYd*
      traceAdjYdYdAdjYuYumq2 + 0.050112932772568106*traceAdjTYdTYdAdjYuYu*
      traceAdjYeYe + 0.050112932772568106*traceAdjTYuTYuAdjYdYd*traceAdjYeYe +
      0.050112932772568106*traceAdjYdYdAdjYuYumq2*traceAdjYeYe +
      0.15033879831770433*traceAdjYdYd*traceAdjYuTYuAdjTYdYd +
      0.050112932772568106*traceAdjYeYe*traceAdjYuTYuAdjTYdYd +
      0.15033879831770433*traceAdjTYdYd*traceAdjYuTYuAdjYdYd +
      0.050112932772568106*traceAdjTYeYe*traceAdjYuTYuAdjYdYd +
      0.07516939915885217*traceAdjYuTYuAdjYdYdAdjTYdYd + 0.9020327899062259*
      traceAdjTYuYu*traceAdjYuTYuAdjYuYu + 0.6173167701503955*
      traceAdjYuTYuAdjYuYuAdjTYuYu - 0.020746754167843197*mHd2*Power6(g1) -
      0.020746754167843197*mHu2*Power6(g1) - 0.012528233193142026*mHd2*Power6(
      g2) - 0.012528233193142026*mHu2*Power6(g2) + 0.035079052940797675*MassB*
      traceAdjTYdYd*Quad(g1) + 0.0451016394953113*MassB*traceAdjTYeYe*Quad(g1)
      + 0.6171575934708637*MassB*traceAdjTYuYu*Quad(g1) - 0.021047431764478604*
      mHd2*traceAdjYdYd*Quad(g1) - 0.021047431764478604*traceAdjYdYdmq2*Quad(g1
      ) - 0.02706098369718678*mHd2*traceAdjYeYe*Quad(g1) - 0.02706098369718678*
      traceAdjYeYeml2*Quad(g1) + 0.3758469957942608*MassWB*traceAdjTYdYd*Quad(
      g2) + 0.12528233193142027*MassWB*traceAdjTYeYe*Quad(g2) +
      2.837133287956054*MassWB*traceAdjTYuYu*Quad(g2) - 0.22550819747655648*
      mHd2*traceAdjYdYd*Quad(g2) - 0.22550819747655648*traceAdjYdYdmq2*Quad(g2)
      - 0.07516939915885217*mHd2*traceAdjYeYe*Quad(g2) - 0.07516939915885217*
      traceAdjYeYeml2*Quad(g2) + 1.2121690987665699*MassG*traceAdjTYuYu*Quad(g3
      ) + 0.022070305909881252*traceAdjTYdTYdAdjYuYu*Sqr(g1) +
      0.022070305909881252*traceAdjTYuTYuAdjYdYd*Sqr(g1) + 0.11814282840355302*
      traceAdjTYuTYuAdjYuYu*Sqr(g1) - 0.022070305909881252*MassB*
      traceAdjTYuYuAdjYdYd*Sqr(g1) + 0.022070305909881252*
      traceAdjYdYdAdjYuYumq2*Sqr(g1) + 0.022070305909881252*
      traceAdjYuTYuAdjTYdYd*Sqr(g1) + 0.11814282840355302*traceAdjYuTYuAdjTYuYu
      *Sqr(g1) - 0.022070305909881252*MassB*traceAdjYuTYuAdjYdYd*Sqr(g1) -
      0.11814282840355302*MassB*traceAdjYuTYuAdjYuYu*Sqr(g1) -
      0.2501190234360739*MassB*MassWB*Quad(g2)*Sqr(g1) - 0.007516939915885216*
      mHd2*Quad(g2)*Sqr(g1) - 0.007516939915885216*mHu2*Quad(g2)*Sqr(g1) +
      0.15033879831770433*traceAdjTYdTYdAdjYuYu*Sqr(g2) + 0.15033879831770433*
      traceAdjTYuTYuAdjYdYd*Sqr(g2) + 1.234633540300791*traceAdjTYuTYuAdjYuYu*
      Sqr(g2) - 0.15033879831770433*MassWB*traceAdjTYuYuAdjYdYd*Sqr(g2) +
      0.15033879831770433*traceAdjYdYdAdjYuYumq2*Sqr(g2) + 0.15033879831770433*
      traceAdjYuTYuAdjTYdYd*Sqr(g2) + 1.234633540300791*traceAdjYuTYuAdjTYuYu*
      Sqr(g2) - 0.15033879831770433*MassWB*traceAdjYuTYuAdjYdYd*Sqr(g2) -
      1.234633540300791*MassWB*traceAdjYuTYuAdjYuYu*Sqr(g2) -
      0.18615272565789337*MassB*MassWB*Quad(g1)*Sqr(g2) - 0.00451016394953113*
      mHd2*Quad(g1)*Sqr(g2) - 0.00451016394953113*mHu2*Quad(g1)*Sqr(g2) -
      0.07889376709742041*MassB*traceAdjTYuYu*Sqr(g1)*Sqr(g2) -
      0.07889376709742041*MassWB*traceAdjTYuYu*Sqr(g1)*Sqr(g2) -
      0.28145704312443287*traceAdjTYdTYdAdjYuYu*Sqr(g3) - 0.28145704312443287*
      traceAdjTYuTYuAdjYdYd*Sqr(g3) - 1.688742258746597*traceAdjTYuTYuAdjYuYu*
      Sqr(g3) + 0.28145704312443287*MassG*traceAdjTYuYuAdjYdYd*Sqr(g3) -
      0.28145704312443287*traceAdjYdYdAdjYuYumq2*Sqr(g3) - 0.28145704312443287*
      traceAdjYuTYuAdjTYdYd*Sqr(g3) - 1.688742258746597*traceAdjYuTYuAdjTYuYu*
      Sqr(g3) + 0.28145704312443287*MassG*traceAdjYuTYuAdjYdYd*Sqr(g3) +
      1.688742258746597*MassG*traceAdjYuTYuAdjYuYu*Sqr(g3) - 0.1951257735648116
      *MassB*MassG*Quad(g1)*Sqr(g3) - 1.330403001578261*MassG*MassWB*Quad(g2)*
      Sqr(g3) - 0.07243184521949762*MassB*traceAdjTYuYu*Sqr(g1)*Sqr(g3) -
      0.07243184521949762*MassG*traceAdjTYuYu*Sqr(g1)*Sqr(g3) -
      0.3432418016476174*MassG*traceAdjTYuYu*Sqr(g2)*Sqr(g3) -
      0.3432418016476174*MassWB*traceAdjTYuYu*Sqr(g2)*Sqr(g3) + 1.*Power6(g1)*
      Sqr(MassB) - 0.10523715882239303*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.13530491848593387*traceAdjYeYe*Quad(g1)*Sqr(MassB) - 1.8514727804125912
      *traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.1025086919703813*Quad(g2)*Sqr(g1)*
      Sqr(MassB) - 0.2792290884868401*Quad(g1)*Sqr(g2)*Sqr(MassB) +
      0.15778753419484082*traceAdjYuYu*Sqr(g1)*Sqr(g2)*Sqr(MassB) -
      0.29268866034721747*Quad(g1)*Sqr(g3)*Sqr(MassB) + 0.14486369043899525*
      traceAdjYuYu*Sqr(g1)*Sqr(g3)*Sqr(MassB) - 0.053463505942545855*Quad(g1)*
      Sqr(g3)*Sqr(MassG) - 0.3645239041537219*Quad(g2)*Sqr(g3)*Sqr(MassG) +
      27.982957650573137*Power6(g2)*Sqr(MassWB) - 1.1275409873827824*
      traceAdjYdYd*Quad(g2)*Sqr(MassWB) - 0.3758469957942608*traceAdjYeYe*Quad(
      g2)*Sqr(MassWB) - 0.34511077549057*Quad(g2)*Sqr(g1)*Sqr(MassWB) -
      0.0795458709803533*Quad(g1)*Sqr(g2)*Sqr(MassWB) - 1.9956045023673916*Quad
      (g2)*Sqr(g3)*Sqr(MassWB)));
   const double beta_mHu2_2 = Re(-3.312*threeLoop*(-65.21739130434783*
      traceAdjTYuTYuAdjYuYu*traceAdjYuYu - 65.21739130434783*
      traceAdjYuTYuAdjTYuYu*traceAdjYuYu - 5.434782608695652*
      traceAdjYuYuAdjTYdTYdAdjYdYd - 44.63229032042155*
      traceAdjYuYuAdjTYuTYuAdjYuYu - 5.434782608695652*
      traceAdjYuYuAdjYdTYdAdjTYdYd - 21.73913043478261*mHd2*traceAdjYdYd*
      traceAdjYuYuAdjYdYd - 10.869565217391305*mHu2*traceAdjYdYd*
      traceAdjYuYuAdjYdYd - 10.869565217391305*traceAdjYdYdmq2*
      traceAdjYuYuAdjYdYd - 7.246376811594203*mHd2*traceAdjYeYe*
      traceAdjYuYuAdjYdYd - 3.6231884057971016*mHu2*traceAdjYeYe*
      traceAdjYuYuAdjYdYd - 3.6231884057971016*traceAdjYeYeml2*
      traceAdjYuYuAdjYdYd - 5.434782608695652*traceAdjYuYuAdjYdYdAdjYdYdmq2 -
      10.869565217391305*traceAdjYdYd*traceAdjYuYuAdjYdYdmq2 -
      3.6231884057971016*traceAdjYeYe*traceAdjYuYuAdjYdYdmq2 -
      44.63229032042155*traceAdjYuYuAdjYuTYuAdjTYuYu - 97.82608695652175*mHu2*
      traceAdjYuYu*traceAdjYuYuAdjYuYu - 44.63229032042155*mHu2*
      traceAdjYuYuAdjYuYuAdjYuYu - 44.63229032042155*
      traceAdjYuYuAdjYuYuAdjYuYumq2 - 65.21739130434783*traceAdjYuYu*
      traceAdjYuYuAdjYuYumq2 - 32.608695652173914*traceAdjYuYuAdjYuYu*
      traceAdjYuYumq2 - 10.869565217391305*traceAdjYuYuAdjYdYd*traceTYdAdjTYd -
      10.869565217391305*traceAdjYdYd*traceTYdAdjTYuYuAdjYd -
      3.6231884057971016*traceAdjYeYe*traceTYdAdjTYuYuAdjYd + 1.*tracemd2*
      Power6(g1) + 3.*traceme2*Power6(g1) + 1.5*traceml2*Power6(g1) + 0.5*
      tracemq2*Power6(g1) + 4.*tracemu2*Power6(g1) + 0.9057971014492754*
      traceml2*Power6(g2) + 2.717391304347826*tracemq2*Power6(g2) +
      0.28985507246376807*mHd2*traceAdjYuYu*Quad(g1) + 23.071260451353144*mHu2*
      traceAdjYuYu*Quad(g1) + 22.781405378889378*traceAdjYuYumq2*Quad(g1) +
      0.19323671497584544*traceAdjYuYu*tracemd2*Quad(g1) + 0.5797101449275361*
      traceAdjYuYu*traceme2*Quad(g1) + 0.28985507246376807*traceAdjYuYu*
      traceml2*Quad(g1) + 0.09661835748792272*traceAdjYuYu*tracemq2*Quad(g1) +
      0.7729468599033817*traceAdjYuYu*tracemu2*Quad(g1) + 1.5217391304347827*
      traceTYdAdjTYd*Quad(g1) - 2.536231884057971*MassB*traceTYdAdjYd*Quad(g1)
      + 105.28042110421597*mHu2*traceAdjYuYu*Quad(g2) + 105.28042110421597*
      traceAdjYuYumq2*Quad(g2) + 16.304347826086957*traceTYdAdjTYd*Quad(g2) +
      43.820195521670804*mHu2*traceAdjYuYu*Quad(g3) + 43.820195521670804*
      traceAdjYuYumq2*Quad(g3) + 9.66183574879227*traceAdjYuYu*tracemd2*Quad(g3
      ) + 19.32367149758454*traceAdjYuYu*tracemq2*Quad(g3) + 9.66183574879227*
      traceAdjYuYu*tracemu2*Quad(g3) + 1.5956934080866625*MassB*
      traceAdjYuYuAdjTYdYd*Sqr(g1) + 8.541781580465534*MassB*
      traceAdjYuYuAdjTYuYu*Sqr(g1) - 1.5956934080866625*mHd2*
      traceAdjYuYuAdjYdYd*Sqr(g1) - 1.5956934080866625*mHu2*traceAdjYuYuAdjYdYd
      *Sqr(g1) - 1.5956934080866625*traceAdjYuYuAdjYdYdmq2*Sqr(g1) -
      8.541781580465534*mHu2*traceAdjYuYuAdjYuYu*Sqr(g1) - 8.541781580465534*
      traceAdjYuYuAdjYuYumq2*Sqr(g1) - 1.5956934080866625*traceTYdAdjTYuYuAdjYd
      *Sqr(g1) + 0.5434782608695653*traceml2*Quad(g2)*Sqr(g1) +
      1.6304347826086958*tracemq2*Quad(g2)*Sqr(g1) + 10.869565217391305*MassWB*
      traceAdjYuYuAdjTYdYd*Sqr(g2) + 89.2645806408431*MassWB*
      traceAdjYuYuAdjTYuYu*Sqr(g2) - 10.869565217391305*mHd2*
      traceAdjYuYuAdjYdYd*Sqr(g2) - 10.869565217391305*mHu2*traceAdjYuYuAdjYdYd
      *Sqr(g2) - 10.869565217391305*traceAdjYuYuAdjYdYdmq2*Sqr(g2) -
      89.2645806408431*mHu2*traceAdjYuYuAdjYuYu*Sqr(g2) - 89.2645806408431*
      traceAdjYuYuAdjYuYumq2*Sqr(g2) - 10.869565217391305*traceTYdAdjTYuYuAdjYd
      *Sqr(g2) + 0.21739130434782608*tracemd2*Quad(g1)*Sqr(g2) +
      0.6521739130434784*traceme2*Quad(g1)*Sqr(g2) + 0.3260869565217392*
      traceml2*Quad(g1)*Sqr(g2) + 0.10869565217391304*tracemq2*Quad(g1)*Sqr(g2)
      + 0.8695652173913043*tracemu2*Quad(g1)*Sqr(g2) - 11.408112294457592*MassB
      *MassWB*traceAdjYuYu*Sqr(g1)*Sqr(g2) - 5.704056147228796*mHu2*
      traceAdjYuYu*Sqr(g1)*Sqr(g2) - 5.704056147228796*traceAdjYuYumq2*Sqr(g1)*
      Sqr(g2) - 20.349475453901285*MassG*traceAdjYuYuAdjTYdYd*Sqr(g3) -
      122.0968527234077*MassG*traceAdjYuYuAdjTYuYu*Sqr(g3) + 20.349475453901285
      *mHd2*traceAdjYuYuAdjYdYd*Sqr(g3) + 20.349475453901285*mHu2*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 20.349475453901285*traceAdjYuYuAdjYdYdmq2*
      Sqr(g3) + 122.0968527234077*mHu2*traceAdjYuYuAdjYuYu*Sqr(g3) +
      122.0968527234077*traceAdjYuYuAdjYuYumq2*Sqr(g3) + 20.349475453901285*
      traceTYdAdjTYuYuAdjYd*Sqr(g3) - 10.473712364862065*MassB*MassG*
      traceAdjYuYu*Sqr(g1)*Sqr(g3) - 5.2368561824310325*mHu2*traceAdjYuYu*Sqr(
      g1)*Sqr(g3) - 5.2368561824310325*traceAdjYuYumq2*Sqr(g1)*Sqr(g3) -
      49.63308460746566*MassG*MassWB*traceAdjYuYu*Sqr(g2)*Sqr(g3) -
      24.81654230373283*mHu2*traceAdjYuYu*Sqr(g2)*Sqr(g3) - 24.81654230373283*
      traceAdjYuYumq2*Sqr(g2)*Sqr(g3) - 3.191386816173325*traceAdjYuYuAdjYdYd*
      Sqr(g1)*Sqr(MassB) - 8.541781580465534*traceAdjYuYuAdjYuYu*Sqr(g1)*Sqr(
      MassB) + 204.95015863727116*traceAdjYuYu*Quad(g3)*Sqr(MassG) +
      40.69895090780257*traceAdjYuYuAdjYdYd*Sqr(g3)*Sqr(MassG) +
      122.0968527234077*traceAdjYuYuAdjYuYu*Sqr(g3)*Sqr(MassG) -
      10.473712364862065*traceAdjYuYu*Sqr(g1)*Sqr(g3)*Sqr(MassG) -
      49.63308460746566*traceAdjYuYu*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      615.378178799209*traceAdjYuYu*Quad(g2)*Sqr(MassWB) - 21.73913043478261*
      traceAdjYuYuAdjYdYd*Sqr(g2)*Sqr(MassWB) - 89.2645806408431*
      traceAdjYuYuAdjYuYu*Sqr(g2)*Sqr(MassWB) - 11.408112294457592*traceAdjYuYu
      *Sqr(g1)*Sqr(g2)*Sqr(MassWB) - 49.63308460746566*traceAdjYuYu*Sqr(g2)*Sqr
      (g3)*Sqr(MassWB)));
   const double beta_mHu2_3 = Re(90.*threeLoop*(0.4*traceAdjTYuYuAdjYdYd*
      traceTYdAdjYd + 0.4*traceAdjYuYuAdjTYdYd*traceTYdAdjYd + 0.4*
      traceAdjTYdYd*traceTYdAdjYuYuAdjYd + 0.13333333333333333*traceAdjTYeYe*
      traceTYdAdjYuYuAdjYd + 0.13333333333333333*traceAdjYuYuAdjYdYd*
      traceTYeAdjTYe + 0.13333333333333333*traceAdjTYuYuAdjYdYd*traceTYeAdjYe +
      0.13333333333333333*traceAdjYuYuAdjTYdYd*traceTYeAdjYe + 1.2*
      traceAdjYuYuAdjYuYu*traceTYuAdjTYu + 2.4*traceAdjYuYuAdjTYuYu*
      traceTYuAdjYu + 0.4*traceAdjYuYuAdjYdYd*traceYdAdjYdmd2 + 0.2*
      traceYdAdjYdYdAdjYuYuAdjYdmd2 + 0.4*traceAdjYdYd*traceYdAdjYuYuAdjYdmd2 +
      0.13333333333333333*traceAdjYeYe*traceYdAdjYuYuAdjYdmd2 + 0.2*
      traceYdAdjYuYuAdjYdYdAdjYdmd2 + 0.13333333333333333*traceAdjYuYuAdjYdYd*
      traceYeAdjYeme2 + 0.2*traceYuAdjYdYdAdjYdYdAdjYumu2 + 0.4*traceAdjYdYd*
      traceYuAdjYdYdAdjYumu2 + 0.13333333333333333*traceAdjYeYe*
      traceYuAdjYdYdAdjYumu2 + 1.2*traceAdjYuYuAdjYuYu*traceYuAdjYumu2 + 2.4*
      traceAdjYuYu*traceYuAdjYuYuAdjYumu2 + 1.6424682837915132*
      traceYuAdjYuYuAdjYuYuAdjYumu2 - 0.07200000000000001*traceTYeAdjTYe*Quad(
      g1) + 0.12000000000000001*MassB*traceTYeAdjYe*Quad(g1) -
      0.8383557179431291*traceTYuAdjTYu*Quad(g1) + 1.6420447692195914*MassB*
      traceTYuAdjYu*Quad(g1) - 0.056*traceYdAdjYdmd2*Quad(g1) -
      0.07200000000000001*traceYeAdjYeme2*Quad(g1) - 0.8383557179431291*
      traceYuAdjYumu2*Quad(g1) + 1.*MassWB*traceTYdAdjYd*Quad(g2) - 0.2*
      traceTYeAdjTYe*Quad(g2) + 0.3333333333333333*MassWB*traceTYeAdjYe*Quad(g2
      ) - 3.8743194966351475*traceTYuAdjTYu*Quad(g2) + 7.548638993270296*MassWB
      *traceTYuAdjYu*Quad(g2) - 0.6*traceYdAdjYdmd2*Quad(g2) - 0.2*
      traceYeAdjYeme2*Quad(g2) - 3.8743194966351475*traceYuAdjYumu2*Quad(g2) -
      1.6125831951974854*traceTYuAdjTYu*Quad(g3) + 3.2251663903949708*MassG*
      traceTYuAdjYu*Quad(g3) - 1.6125831951974854*traceYuAdjYumu2*Quad(g3) -
      0.05872151741758918*MassB*traceTYdAdjYuYuAdjYd*Sqr(g1) +
      0.05872151741758918*traceYdAdjYuYuAdjYdmd2*Sqr(g1) + 0.05872151741758918*
      traceYuAdjYdYdAdjYumu2*Sqr(g1) + 0.3143375621611316*
      traceYuAdjYuYuAdjYumu2*Sqr(g1) - 0.4*MassWB*traceTYdAdjYuYuAdjYd*Sqr(g2)
      + 0.4*traceYdAdjYuYuAdjYdmd2*Sqr(g2) + 0.4*traceYuAdjYdYdAdjYumu2*Sqr(g2)
      + 3.2849365675830264*traceYuAdjYuYuAdjYumu2*Sqr(g2) + 0.20990926621801967
      *traceTYuAdjTYu*Sqr(g1)*Sqr(g2) - 0.20990926621801967*MassB*traceTYuAdjYu
      *Sqr(g1)*Sqr(g2) - 0.20990926621801967*MassWB*traceTYuAdjYu*Sqr(g1)*Sqr(
      g2) + 0.20990926621801967*traceYuAdjYumu2*Sqr(g1)*Sqr(g2) +
      0.7488606967035673*MassG*traceTYdAdjYuYuAdjYd*Sqr(g3) -
      0.7488606967035673*traceYdAdjYuYuAdjYdmd2*Sqr(g3) - 0.7488606967035673*
      traceYuAdjYdYdAdjYumu2*Sqr(g3) - 4.493164180221403*traceYuAdjYuYuAdjYumu2
      *Sqr(g3) + 0.192716307513462*traceTYuAdjTYu*Sqr(g1)*Sqr(g3) -
      0.192716307513462*MassB*traceTYuAdjYu*Sqr(g1)*Sqr(g3) - 0.192716307513462
      *MassG*traceTYuAdjYu*Sqr(g1)*Sqr(g3) + 0.192716307513462*traceYuAdjYumu2*
      Sqr(g1)*Sqr(g3) + 0.9132487567773682*traceTYuAdjTYu*Sqr(g2)*Sqr(g3) -
      0.9132487567773682*MassG*traceTYuAdjYu*Sqr(g2)*Sqr(g3) -
      0.9132487567773682*MassWB*traceTYuAdjYu*Sqr(g2)*Sqr(g3) +
      0.9132487567773682*traceYuAdjYumu2*Sqr(g2)*Sqr(g3)));

   beta_mHu2 = beta_mHu2_1 + beta_mHu2_2 + beta_mHu2_3;


   return beta_mHu2;
}

/**
 * Calculates the 4-loop beta function of mHu2.
 *
 * @return 4-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHu2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_mHu2;

   beta_mHu2 = 0;


   return beta_mHu2;
}

/**
 * Calculates the 5-loop beta function of mHu2.
 *
 * @return 5-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_mHu2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_mHu2;

   beta_mHu2 = 0;


   return beta_mHu2;
}

} // namespace flexiblesusy
