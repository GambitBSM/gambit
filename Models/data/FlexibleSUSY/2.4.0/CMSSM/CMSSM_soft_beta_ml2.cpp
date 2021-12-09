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

// File generated at Thu 10 Oct 2019 17:27:39

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
 * Calculates the 1-loop beta function of ml2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_ml2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_ml2;

   beta_ml2 = (oneOver16PiSqr*(2*mHd2*(Ye.adjoint()*Ye) + 2*((TYe).adjoint()*
      TYe) + ml2*Ye.adjoint()*Ye + 2*(Ye.adjoint()*me2*Ye) + Ye.adjoint()*Ye*
      ml2 - 0.2*(3.872983346207417*g1*Tr11 + 6*AbsSqr(MassB)*Sqr(g1) + 30*
      AbsSqr(MassWB)*Sqr(g2))*UNITMATRIX(3))).real();


   return beta_ml2;
}

/**
 * Calculates the 2-loop beta function of ml2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_ml2_2_loop(const Soft_traces& soft_traces) const
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

   beta_ml2 = (twoLoop*(0.4*(-15*traceconjTYdTpTYd - 5*traceconjTYeTpTYe - 15*
      tracemd2YdAdjYd - 5*traceme2YeAdjYe - 5*traceml2AdjYeYe - 15*
      tracemq2AdjYdYd - 30*mHd2*traceYdAdjYd - 10*mHd2*traceYeAdjYe + 6*mHd2*
      Sqr(g1) + 12*AbsSqr(MassB)*Sqr(g1))*(Ye.adjoint()*Ye) - 0.4*(15*
      traceconjTYdTpYd + 5*traceconjTYeTpYe + 6*Conj(MassB)*Sqr(g1))*(Ye.
      adjoint()*TYe) - 0.4*(15*traceAdjYdTYd + 5*traceAdjYeTYe + 6*MassB*Sqr(g1
      ))*((TYe).adjoint()*Ye) + 0.4*(-15*traceYdAdjYd - 5*traceYeAdjYe + 6*Sqr(
      g1))*((TYe).adjoint()*TYe) + 0.2*(-15*traceYdAdjYd - 5*traceYeAdjYe + 6*
      Sqr(g1))*(ml2*Ye.adjoint()*Ye) + 0.4*(-15*traceYdAdjYd - 5*traceYeAdjYe +
      6*Sqr(g1))*(Ye.adjoint()*me2*Ye) + 0.2*(-15*traceYdAdjYd - 5*traceYeAdjYe
       + 6*Sqr(g1))*(Ye.adjoint()*Ye*ml2) - 8*mHd2*(Ye.adjoint()*Ye*Ye.adjoint(
      )*Ye) - 4*(Ye.adjoint()*Ye*(TYe).adjoint()*TYe) - 4*(Ye.adjoint()*TYe*(
      TYe).adjoint()*Ye) - 4*((TYe).adjoint()*Ye*Ye.adjoint()*TYe) - 4*((TYe).
      adjoint()*TYe*Ye.adjoint()*Ye) - 2*(ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye)
      - 4*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye) - 4*(Ye.adjoint()*Ye*ml2*Ye.
      adjoint()*Ye) - 4*(Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye) - 2*(Ye.adjoint()
      *Ye*Ye.adjoint()*Ye*ml2) + 0.04*(-77.45966692414834*g1*Tr31 + 621*AbsSqr(
      MassB)*Quad(g1) + 150*Tr22*Quad(g2) + 825*AbsSqr(MassWB)*Quad(g2) + 30*
      Tr2U111*Sqr(g1) + 90*AbsSqr(MassB)*Sqr(g1)*Sqr(g2) + 90*AbsSqr(MassWB)*
      Sqr(g1)*Sqr(g2) + 45*MassWB*Conj(MassB)*Sqr(g1)*Sqr(g2) + 45*MassB*Conj(
      MassWB)*Sqr(g1)*Sqr(g2))*UNITMATRIX(3))).real();


   return beta_ml2;
}

/**
 * Calculates the 3-loop beta function of ml2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_ml2_3_loop(const Soft_traces& soft_traces) const
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


   Eigen::Matrix<double,3,3> beta_ml2;

   const Eigen::Matrix<double,3,3> beta_ml2_1 = ((239.45914429835202*threeLoop*
      (-0.020746754167843197*mHd2*Power6(g1) - 0.020746754167843197*mHu2*Power6
      (g1) - 0.013831169445228797*tracemd2*Power6(g1) - 0.041493508335686394*
      traceme2*Power6(g1) - 0.020746754167843197*traceml2*Power6(g1) -
      0.006915584722614399*tracemq2*Power6(g1) - 0.05532467778091519*tracemu2*
      Power6(g1) - 0.012528233193142026*mHd2*Power6(g2) - 0.012528233193142026*
      mHu2*Power6(g2) - 0.012528233193142026*traceml2*Power6(g2) -
      0.03758469957942608*tracemq2*Power6(g2) + 0.035079052940797675*MassB*
      traceAdjTYdYd*Quad(g1) + 0.0451016394953113*MassB*traceAdjTYeYe*Quad(g1)
      + 0.06514681260433854*MassB*traceAdjTYuYu*Quad(g1) - 0.021047431764478604
      *mHd2*traceAdjYdYd*Quad(g1) - 0.021047431764478604*traceAdjYdYdmq2*Quad(
      g1) - 0.02706098369718678*mHd2*traceAdjYeYe*Quad(g1) -
      0.02706098369718678*traceAdjYeYeml2*Quad(g1) - 0.03908808756260312*mHu2*
      traceAdjYuYu*Quad(g1) - 0.03908808756260312*traceAdjYuYumq2*Quad(g1) -
      0.021047431764478604*traceTYdAdjTYd*Quad(g1) + 0.035079052940797675*MassB
      *traceTYdAdjYd*Quad(g1) - 0.02706098369718678*traceTYeAdjTYe*Quad(g1) +
      0.0451016394953113*MassB*traceTYeAdjYe*Quad(g1) - 0.03908808756260312*
      traceTYuAdjTYu*Quad(g1) + 0.06514681260433854*MassB*traceTYuAdjYu*Quad(g1
      ) - 0.021047431764478604*traceYdAdjYdmd2*Quad(g1) - 0.02706098369718678*
      traceYeAdjYeme2*Quad(g1) - 0.03908808756260312*traceYuAdjYumu2*Quad(g1) +
      0.3758469957942608*MassWB*traceAdjTYdYd*Quad(g2) + 0.12528233193142027*
      MassWB*traceAdjTYeYe*Quad(g2) + 0.3758469957942608*MassWB*traceAdjTYuYu*
      Quad(g2) - 0.22550819747655648*mHd2*traceAdjYdYd*Quad(g2) -
      0.22550819747655648*traceAdjYdYdmq2*Quad(g2) - 0.07516939915885217*mHd2*
      traceAdjYeYe*Quad(g2) - 0.07516939915885217*traceAdjYeYeml2*Quad(g2) -
      0.22550819747655648*mHu2*traceAdjYuYu*Quad(g2) - 0.22550819747655648*
      traceAdjYuYumq2*Quad(g2) - 0.22550819747655648*traceTYdAdjTYd*Quad(g2) +
      0.3758469957942608*MassWB*traceTYdAdjYd*Quad(g2) - 0.07516939915885217*
      traceTYeAdjTYe*Quad(g2) + 0.12528233193142027*MassWB*traceTYeAdjYe*Quad(
      g2) - 0.22550819747655648*traceTYuAdjTYu*Quad(g2) + 0.3758469957942608*
      MassWB*traceTYuAdjYu*Quad(g2) - 0.22550819747655648*traceYdAdjYdmd2*Quad(
      g2) - 0.07516939915885217*traceYeAdjYeme2*Quad(g2) - 0.22550819747655648*
      traceYuAdjYumu2*Quad(g2) - 0.2501190234360739*MassB*MassWB*Quad(g2)*Sqr(
      g1) - 0.007516939915885216*mHd2*Quad(g2)*Sqr(g1) - 0.007516939915885216*
      mHu2*Quad(g2)*Sqr(g1) - 0.007516939915885216*traceml2*Quad(g2)*Sqr(g1) -
      0.02255081974765565*tracemq2*Quad(g2)*Sqr(g1) - 0.18615272565789337*MassB
      *MassWB*Quad(g1)*Sqr(g2) - 0.00451016394953113*mHd2*Quad(g1)*Sqr(g2) -
      0.00451016394953113*mHu2*Quad(g1)*Sqr(g2) - 0.0030067759663540863*
      tracemd2*Quad(g1)*Sqr(g2) - 0.00902032789906226*traceme2*Quad(g1)*Sqr(g2)
      - 0.00451016394953113*traceml2*Quad(g1)*Sqr(g2) - 0.0015033879831770432*
      tracemq2*Quad(g1)*Sqr(g2) - 0.012027103865416345*tracemu2*Quad(g1)*Sqr(g2
      ) - 0.1951257735648116*MassB*MassG*Quad(g1)*Sqr(g3) - 1.330403001578261*
      MassG*MassWB*Quad(g2)*Sqr(g3) + 1.*Power6(g1)*Sqr(MassB) -
      0.10523715882239303*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.13530491848593387*traceAdjYeYe*Quad(g1)*Sqr(MassB) - 0.1954404378130156
      *traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.1025086919703813*Quad(g2)*Sqr(g1)*
      Sqr(MassB) - 0.2792290884868401*Quad(g1)*Sqr(g2)*Sqr(MassB) -
      0.29268866034721747*Quad(g1)*Sqr(g3)*Sqr(MassB) - 0.053463505942545855*
      Quad(g1)*Sqr(g3)*Sqr(MassG) - 0.3645239041537219*Quad(g2)*Sqr(g3)*Sqr(
      MassG) + 27.982957650573137*Power6(g2)*Sqr(MassWB) - 1.1275409873827824*
      traceAdjYdYd*Quad(g2)*Sqr(MassWB) - 0.3758469957942608*traceAdjYeYe*Quad(
      g2)*Sqr(MassWB) - 1.1275409873827824*traceAdjYuYu*Quad(g2)*Sqr(MassWB) -
      0.34511077549057*Quad(g2)*Sqr(g1)*Sqr(MassWB) - 0.0795458709803533*Quad(
      g1)*Sqr(g2)*Sqr(MassWB) - 1.9956045023673916*Quad(g2)*Sqr(g3)*Sqr(MassWB)
      ) - 329.4*threeLoop*(-0.21857923497267762*traceAdjTYdTYdAdjYdYd -
      0.03642987249544627*traceAdjTYdTYdAdjYuYu - 0.07285974499089254*
      traceAdjTYeTYeAdjYeYe - 0.03642987249544627*traceAdjTYuTYuAdjYdYd -
      0.21857923497267762*traceAdjYdTYdAdjTYdYd + 0.17103825136612025*mHd2*Quad
      (g1) + 0.004371584699453552*mHu2*Quad(g1) + 0.06830601092896176*mHd2*Quad
      (g2) + 0.048573163327261686*MassB*traceAdjTYdYd*Sqr(g1) -
      0.09714632665452337*mHd2*traceAdjYdYd*Sqr(g1) + 0.10928961748633881*
      MassWB*traceAdjTYdYd*Sqr(g2) + 0.03642987249544627*MassWB*traceAdjTYeYe*
      Sqr(g2) + 0.09836065573770492*MassB*MassWB*Sqr(g1)*Sqr(g2) +
      0.04918032786885246*mHd2*Sqr(g1)*Sqr(g2) - 0.19429265330904674*MassG*
      traceAdjTYdYd*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) - 0.09714632665452337*
      traceAdjYdYd*Sqr(g1)*Sqr(MassB) + 0.09836065573770492*Sqr(g1)*Sqr(g2)*Sqr
      (MassB) + 0.3885853066180935*traceAdjYdYd*Sqr(g3)*Sqr(MassG) +
      0.4098360655737705*Quad(g2)*Sqr(MassWB) - 0.21857923497267762*
      traceAdjYdYd*Sqr(g2)*Sqr(MassWB) + 0.09836065573770492*Sqr(g1)*Sqr(g2)*
      Sqr(MassWB))*(Ye.adjoint()*Ye))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_2 = ((72.*threeLoop*(1.5*mHd2*
      traceAdjYdYdAdjYdYd + 1.*traceAdjYdYdAdjYdYdmq2 + 0.16666666666666666*
      traceAdjYdYdAdjYuYumq2 - 0.5*traceAdjYdYd*traceAdjYdYdmq2 +
      0.3333333333333333*traceAdjYeTYeAdjTYeYe - 0.5*mHd2*traceAdjYdYd*
      traceAdjYeYe - 0.16666666666666666*traceAdjYdYdmq2*traceAdjYeYe + 0.5*
      mHd2*traceAdjYeYeAdjYeYe + 0.3333333333333333*traceAdjYeYeAdjYeYeml2 -
      0.16666666666666666*traceAdjYdYd*traceAdjYeYeml2 - 0.05555555555555555*
      traceAdjYeYe*traceAdjYeYeml2 + 0.16666666666666666*traceAdjYuTYuAdjTYdYd
      + 0.3333333333333333*mHd2*traceAdjYuYuAdjYdYd + 0.16666666666666666*mHu2*
      traceAdjYuYuAdjYdYd + 0.16666666666666666*traceAdjYuYuAdjYdYdmq2 - 0.5*
      traceAdjYdYd*traceTYdAdjTYd - 0.16666666666666666*traceAdjYeYe*
      traceTYdAdjTYd + 0.16666666666666666*traceTYdAdjTYuYuAdjYd - 0.5*
      traceAdjTYdYd*traceTYdAdjYd - 0.16666666666666666*traceAdjTYeYe*
      traceTYdAdjYd - 0.16666666666666666*traceAdjYdYd*traceTYeAdjTYe -
      0.05555555555555555*traceAdjYeYe*traceTYeAdjTYe - 0.16666666666666666*
      traceAdjTYdYd*traceTYeAdjYe - 0.05555555555555555*traceAdjTYeYe*
      traceTYeAdjYe - 0.5*traceAdjYdYd*traceYdAdjYdmd2 - 0.16666666666666666*
      traceAdjYeYe*traceYdAdjYdmd2 + 1.*traceYdAdjYdYdAdjYdmd2 +
      0.16666666666666666*traceYdAdjYuYuAdjYdmd2 - 0.16666666666666666*
      traceAdjYdYd*traceYeAdjYeme2 - 0.05555555555555555*traceAdjYeYe*
      traceYeAdjYeme2 + 0.3333333333333333*traceYeAdjYeYeAdjYeme2 +
      0.16666666666666666*traceYuAdjYdYdAdjYumu2 - 0.01333333333333333*tracemd2
      *Quad(g1) - 0.04*traceme2*Quad(g1) - 0.02*traceml2*Quad(g1) -
      0.006666666666666665*tracemq2*Quad(g1) - 0.05333333333333332*tracemu2*
      Quad(g1) + 0.2222222222222222*traceAdjYdYdmq2*Sqr(g1) +
      0.2222222222222222*traceTYdAdjTYd*Sqr(g1) - 0.2222222222222222*MassB*
      traceTYdAdjYd*Sqr(g1) + 0.2222222222222222*traceYdAdjYdmd2*Sqr(g1) + 1.*
      mHd2*traceAdjYdYd*Sqr(g2) + 0.5*traceAdjYdYdmq2*Sqr(g2) +
      0.3333333333333333*mHd2*traceAdjYeYe*Sqr(g2) + 0.16666666666666666*
      traceAdjYeYeml2*Sqr(g2) + 0.5*traceTYdAdjTYd*Sqr(g2) - 0.5*MassWB*
      traceTYdAdjYd*Sqr(g2) + 0.16666666666666666*traceTYeAdjTYe*Sqr(g2) -
      0.16666666666666666*MassWB*traceTYeAdjYe*Sqr(g2) + 0.5*traceYdAdjYdmd2*
      Sqr(g2) + 0.16666666666666666*traceYeAdjYeme2*Sqr(g2) -
      1.7777777777777777*mHd2*traceAdjYdYd*Sqr(g3) - 0.8888888888888888*
      traceAdjYdYdmq2*Sqr(g3) - 0.8888888888888888*traceTYdAdjTYd*Sqr(g3) +
      0.8888888888888888*MassG*traceTYdAdjYd*Sqr(g3) - 0.8888888888888888*
      traceYdAdjYdmd2*Sqr(g3) + 0.3333333333333333*traceAdjYeYe*Sqr(g2)*Sqr(
      MassWB) - 0.75*mHd2*Sqr(traceAdjYdYd) - 0.08333333333333333*mHd2*Sqr(
      traceAdjYeYe))*(Ye.adjoint()*Ye) + 109.8*threeLoop*(0.1092896174863388*
      traceAdjTYuYuAdjYdYd - 0.3278688524590164*traceAdjTYdYd*traceAdjYdYd -
      0.1092896174863388*traceAdjTYeYe*traceAdjYdYd + 0.6557377049180328*
      traceAdjYdYdAdjTYdYd - 0.1092896174863388*traceAdjTYdYd*traceAdjYeYe -
      0.03642987249544626*traceAdjTYeYe*traceAdjYeYe + 0.2185792349726776*
      traceAdjYeYeAdjTYeYe + 0.1092896174863388*traceAdjYuYuAdjTYdYd + 1.*MassB
      *Quad(g1) + 0.4098360655737705*MassWB*Quad(g2) + 0.14571948998178505*
      traceAdjTYdYd*Sqr(g1) - 0.14571948998178505*MassB*traceAdjYdYd*Sqr(g1) +
      0.3278688524590164*traceAdjTYdYd*Sqr(g2) + 0.1092896174863388*
      traceAdjTYeYe*Sqr(g2) - 0.3278688524590164*MassWB*traceAdjYdYd*Sqr(g2) -
      0.1092896174863388*MassWB*traceAdjYeYe*Sqr(g2) + 0.14754098360655737*
      MassB*Sqr(g1)*Sqr(g2) + 0.14754098360655737*MassWB*Sqr(g1)*Sqr(g2) -
      0.5828779599271402*traceAdjTYdYd*Sqr(g3) + 0.5828779599271402*MassG*
      traceAdjYdYd*Sqr(g3))*(Ye.adjoint()*TYe) + 109.8*threeLoop*(
      0.6557377049180328*traceAdjYdTYdAdjYdYd + 0.2185792349726776*
      traceAdjYeTYeAdjYeYe + 0.1092896174863388*traceAdjYuTYuAdjYdYd -
      0.3278688524590164*traceAdjYdYd*traceTYdAdjYd - 0.1092896174863388*
      traceAdjYeYe*traceTYdAdjYd + 0.1092896174863388*traceTYdAdjYuYuAdjYd -
      0.1092896174863388*traceAdjYdYd*traceTYeAdjYe - 0.03642987249544626*
      traceAdjYeYe*traceTYeAdjYe + 1.*MassB*Quad(g1) + 0.4098360655737705*
      MassWB*Quad(g2) - 0.14571948998178505*MassB*traceAdjYdYd*Sqr(g1) +
      0.14571948998178505*traceTYdAdjYd*Sqr(g1) - 0.3278688524590164*MassWB*
      traceAdjYdYd*Sqr(g2) - 0.1092896174863388*MassWB*traceAdjYeYe*Sqr(g2) +
      0.3278688524590164*traceTYdAdjYd*Sqr(g2) + 0.1092896174863388*
      traceTYeAdjYe*Sqr(g2) + 0.14754098360655737*MassB*Sqr(g1)*Sqr(g2) +
      0.14754098360655737*MassWB*Sqr(g1)*Sqr(g2) + 0.5828779599271402*MassG*
      traceAdjYdYd*Sqr(g3) - 0.5828779599271402*traceTYdAdjYd*Sqr(g3))*((TYe).
      adjoint()*Ye) - 54.9*threeLoop*Quad(g1)*((TYe).adjoint()*TYe))*UNITMATRIX
      (3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_3 = ((-16.2*threeLoop*(-
      2.2222222222222223*traceAdjYdYdAdjYdYd + 0.7407407407407408*traceAdjYdYd*
      traceAdjYeYe - 0.7407407407407408*traceAdjYeYeAdjYeYe -
      0.7407407407407408*traceAdjYuYuAdjYdYd + 1.3888888888888888*Quad(g2) -
      0.9876543209876543*traceAdjYdYd*Sqr(g1) - 2.2222222222222223*traceAdjYdYd
      *Sqr(g2) - 0.7407407407407408*traceAdjYeYe*Sqr(g2) + 1.*Sqr(g1)*Sqr(g2) +
      3.950617283950617*traceAdjYdYd*Sqr(g3) + 1.1111111111111112*Sqr(
      traceAdjYdYd) + 0.12345679012345678*Sqr(traceAdjYeYe))*((TYe).adjoint()*
      TYe) - 27.45*threeLoop*(-0.6557377049180328*traceAdjYdYdAdjYdYd +
      0.2185792349726776*traceAdjYdYd*traceAdjYeYe - 0.2185792349726776*
      traceAdjYeYeAdjYeYe - 0.2185792349726776*traceAdjYuYuAdjYdYd + 1.*Quad(g1
      ) + 0.4098360655737705*Quad(g2) - 0.2914389799635701*traceAdjYdYd*Sqr(g1)
      - 0.6557377049180328*traceAdjYdYd*Sqr(g2) - 0.2185792349726776*
      traceAdjYeYe*Sqr(g2) + 0.29508196721311475*Sqr(g1)*Sqr(g2) +
      1.1657559198542804*traceAdjYdYd*Sqr(g3) + 0.3278688524590164*Sqr(
      traceAdjYdYd) + 0.03642987249544626*Sqr(traceAdjYeYe))*(ml2*Ye.adjoint()*
      Ye) - 54.9*threeLoop*(-0.6557377049180328*traceAdjYdYdAdjYdYd +
      0.2185792349726776*traceAdjYdYd*traceAdjYeYe - 0.2185792349726776*
      traceAdjYeYeAdjYeYe - 0.2185792349726776*traceAdjYuYuAdjYdYd + 1.*Quad(g1
      ) + 0.4098360655737705*Quad(g2) - 0.2914389799635701*traceAdjYdYd*Sqr(g1)
      - 0.6557377049180328*traceAdjYdYd*Sqr(g2) - 0.2185792349726776*
      traceAdjYeYe*Sqr(g2) + 0.29508196721311475*Sqr(g1)*Sqr(g2) +
      1.1657559198542804*traceAdjYdYd*Sqr(g3) + 0.3278688524590164*Sqr(
      traceAdjYdYd) + 0.03642987249544626*Sqr(traceAdjYeYe))*(Ye.adjoint()*me2*
      Ye) + 19.44*threeLoop*(0.16666666666666666*mHd2*Quad(g1) -
      3.24074074074074*mHd2*Quad(g2) + 1.2345679012345678*MassB*traceAdjTYdYd*
      Sqr(g1) - 2.4691358024691357*mHd2*traceAdjYdYd*Sqr(g1) -
      1.2345679012345678*traceAdjYdYdmq2*Sqr(g1) - 1.2345679012345678*
      traceTYdAdjTYd*Sqr(g1) + 1.2345679012345678*MassB*traceTYdAdjYd*Sqr(g1) -
      1.2345679012345678*traceYdAdjYdmd2*Sqr(g1) + 3.333333333333333*MassB*
      MassWB*Sqr(g1)*Sqr(g2) + 1.6666666666666665*mHd2*Sqr(g1)*Sqr(g2) -
      4.938271604938271*MassG*traceAdjTYdYd*Sqr(g3) + 9.876543209876543*mHd2*
      traceAdjYdYd*Sqr(g3) + 4.938271604938271*traceAdjYdYdmq2*Sqr(g3) +
      4.938271604938271*traceTYdAdjTYd*Sqr(g3) - 4.938271604938271*MassG*
      traceTYdAdjYd*Sqr(g3) + 4.938271604938271*traceYdAdjYdmd2*Sqr(g3) + 1.*
      Quad(g1)*Sqr(MassB) - 2.4691358024691357*traceAdjYdYd*Sqr(g1)*Sqr(MassB)
      + 3.333333333333333*Sqr(g1)*Sqr(g2)*Sqr(MassB) + 9.876543209876543*
      traceAdjYdYd*Sqr(g3)*Sqr(MassG) - 19.444444444444443*Quad(g2)*Sqr(MassWB)
      + 3.333333333333333*Sqr(g1)*Sqr(g2)*Sqr(MassWB))*(Ye.adjoint()*Ye*
      1.2020569031595942) - 27.45*threeLoop*(-0.6557377049180328*
      traceAdjYdYdAdjYdYd + 0.2185792349726776*traceAdjYdYd*traceAdjYeYe -
      0.2185792349726776*traceAdjYeYeAdjYeYe - 0.2185792349726776*
      traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 0.4098360655737705*Quad(g2) -
      0.2914389799635701*traceAdjYdYd*Sqr(g1) - 0.6557377049180328*traceAdjYdYd
      *Sqr(g2) - 0.2185792349726776*traceAdjYeYe*Sqr(g2) + 0.29508196721311475*
      Sqr(g1)*Sqr(g2) + 1.1657559198542804*traceAdjYdYd*Sqr(g3) +
      0.3278688524590164*Sqr(traceAdjYdYd) + 0.03642987249544626*Sqr(
      traceAdjYeYe))*(Ye.adjoint()*Ye*ml2) - 6.48*threeLoop*(1.*MassB*Quad(g1)
      - 19.44444444444444*MassWB*Quad(g2) + 3.7037037037037033*traceAdjTYdYd*
      Sqr(g1) - 3.7037037037037033*MassB*traceAdjYdYd*Sqr(g1) +
      4.999999999999999*MassB*Sqr(g1)*Sqr(g2) + 4.999999999999999*MassWB*Sqr(g1
      )*Sqr(g2) - 14.814814814814813*traceAdjTYdYd*Sqr(g3) + 14.814814814814813
      *MassG*traceAdjYdYd*Sqr(g3))*(Ye.adjoint()*TYe*1.2020569031595942) - 6.48
      *threeLoop*(1.*MassB*Quad(g1) - 19.44444444444444*MassWB*Quad(g2) -
      3.7037037037037033*MassB*traceAdjYdYd*Sqr(g1) + 3.7037037037037033*
      traceTYdAdjYd*Sqr(g1) + 4.999999999999999*MassB*Sqr(g1)*Sqr(g2) +
      4.999999999999999*MassWB*Sqr(g1)*Sqr(g2) + 14.814814814814813*MassG*
      traceAdjYdYd*Sqr(g3) - 14.814814814814813*traceTYdAdjYd*Sqr(g3))*((TYe).
      adjoint()*Ye*1.2020569031595942) + 3.24*threeLoop*(1.*Quad(g1) -
      19.44444444444444*Quad(g2) - 7.4074074074074066*traceAdjYdYd*Sqr(g1) +
      9.999999999999998*Sqr(g1)*Sqr(g2) + 29.629629629629626*traceAdjYdYd*Sqr(
      g3))*((TYe).adjoint()*TYe*1.2020569031595942) + 1.62*threeLoop*(1.*Quad(
      g1) - 19.44444444444444*Quad(g2) - 7.4074074074074066*traceAdjYdYd*Sqr(g1
      ) + 9.999999999999998*Sqr(g1)*Sqr(g2) + 29.629629629629626*traceAdjYdYd*
      Sqr(g3))*(ml2*Ye.adjoint()*Ye*1.2020569031595942) + 3.24*threeLoop*Quad(
      g1)*(Ye.adjoint()*me2*Ye*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_4 = ((32.4*threeLoop*(-
      1.9444444444444442*Quad(g2) - 0.7407407407407408*traceAdjYdYd*Sqr(g1) +
      1.*Sqr(g1)*Sqr(g2) + 2.9629629629629632*traceAdjYdYd*Sqr(g3))*(Ye.adjoint
      ()*me2*Ye*1.2020569031595942) + 1.62*threeLoop*(1.*Quad(g1) -
      19.44444444444444*Quad(g2) - 7.4074074074074066*traceAdjYdYd*Sqr(g1) +
      9.999999999999998*Sqr(g1)*Sqr(g2) + 29.629629629629626*traceAdjYdYd*Sqr(
      g3))*(Ye.adjoint()*Ye*ml2*1.2020569031595942) + 36.*threeLoop*(1.*mHd2*
      traceAdjYdYd + 0.3333333333333333*traceAdjYdYdmq2 + 0.3333333333333333*
      mHd2*traceAdjYeYe + 0.1111111111111111*traceAdjYeYeml2 +
      0.3333333333333333*traceTYdAdjTYd + 0.1111111111111111*traceTYeAdjTYe +
      0.3333333333333333*traceYdAdjYdmd2 + 0.1111111111111111*traceYeAdjYeme2 +
      1.*mHd2*Sqr(g1) - 0.3333333333333333*mHd2*Sqr(g2) + 1.*Sqr(g1)*Sqr(MassB)
      - 0.3333333333333333*Sqr(g2)*Sqr(MassWB))*(Ye.adjoint()*Ye*Ye.adjoint()*
      Ye) - 18.*threeLoop*(-0.6666666666666666*traceAdjTYdYd -
      0.2222222222222222*traceAdjTYeYe + 1.*MassB*Sqr(g1) - 0.3333333333333333*
      MassWB*Sqr(g2))*(Ye.adjoint()*Ye*Ye.adjoint()*TYe) - 18.*threeLoop*(-
      0.6666666666666666*traceTYdAdjYd - 0.2222222222222222*traceTYeAdjYe + 1.*
      MassB*Sqr(g1) - 0.3333333333333333*MassWB*Sqr(g2))*(Ye.adjoint()*Ye*(TYe)
      .adjoint()*Ye) + 18.*threeLoop*(0.6666666666666666*traceAdjYdYd +
      0.2222222222222222*traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2)
      )*(Ye.adjoint()*Ye*(TYe).adjoint()*TYe) - 18.*threeLoop*(-
      0.6666666666666666*traceAdjTYdYd - 0.2222222222222222*traceAdjTYeYe + 1.*
      MassB*Sqr(g1) - 0.3333333333333333*MassWB*Sqr(g2))*(Ye.adjoint()*TYe*Ye.
      adjoint()*Ye) + 18.*threeLoop*(0.6666666666666666*traceAdjYdYd +
      0.2222222222222222*traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2)
      )*(Ye.adjoint()*TYe*(TYe).adjoint()*Ye) - 18.*threeLoop*(-
      0.6666666666666666*traceTYdAdjYd - 0.2222222222222222*traceTYeAdjYe + 1.*
      MassB*Sqr(g1) - 0.3333333333333333*MassWB*Sqr(g2))*((TYe).adjoint()*Ye*Ye
      .adjoint()*Ye) + 18.*threeLoop*(0.6666666666666666*traceAdjYdYd +
      0.2222222222222222*traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2)
      )*((TYe).adjoint()*Ye*Ye.adjoint()*TYe) + 18.*threeLoop*(
      0.6666666666666666*traceAdjYdYd + 0.2222222222222222*traceAdjYeYe + 1.*
      Sqr(g1) - 0.3333333333333333*Sqr(g2))*((TYe).adjoint()*TYe*Ye.adjoint()*
      Ye) + 9.*threeLoop*(0.6666666666666666*traceAdjYdYd + 0.2222222222222222*
      traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2))*(ml2*Ye.adjoint()
      *Ye*Ye.adjoint()*Ye) + 18.*threeLoop*(0.6666666666666666*traceAdjYdYd +
      0.2222222222222222*traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2)
      )*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye) + 18.*threeLoop*(
      0.6666666666666666*traceAdjYdYd + 0.2222222222222222*traceAdjYeYe + 1.*
      Sqr(g1) - 0.3333333333333333*Sqr(g2))*(Ye.adjoint()*Ye*ml2*Ye.adjoint()*
      Ye) + 18.*threeLoop*(0.6666666666666666*traceAdjYdYd + 0.2222222222222222
      *traceAdjYeYe + 1.*Sqr(g1) - 0.3333333333333333*Sqr(g2))*(Ye.adjoint()*Ye
      *Ye.adjoint()*me2*Ye) - 43.2*(1.*mHd2*threeLoop*Sqr(g1) -
      1.6666666666666665*mHd2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(
      MassB) - 1.6666666666666665*threeLoop*Sqr(g2)*Sqr(MassWB))*(Ye.adjoint()*
      Ye*Ye.adjoint()*Ye*1.2020569031595942) + 9.*threeLoop*(0.6666666666666666
      *traceAdjYdYd + 0.2222222222222222*traceAdjYeYe + 1.*Sqr(g1) -
      0.3333333333333333*Sqr(g2))*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2) + 21.6*
      (1.*MassB*threeLoop*Sqr(g1) - 1.6666666666666665*MassWB*threeLoop*Sqr(g2)
      )*(Ye.adjoint()*Ye*Ye.adjoint()*TYe*1.2020569031595942) + 21.6*(1.*MassB*
      threeLoop*Sqr(g1) - 1.6666666666666665*MassWB*threeLoop*Sqr(g2))*(Ye.
      adjoint()*Ye*(TYe).adjoint()*Ye*1.2020569031595942) - 21.6*(1.*threeLoop*
      Sqr(g1) - 1.6666666666666665*threeLoop*Sqr(g2))*(Ye.adjoint()*Ye*(TYe).
      adjoint()*TYe*1.2020569031595942) + 21.6*(1.*MassB*threeLoop*Sqr(g1) -
      1.6666666666666665*MassWB*threeLoop*Sqr(g2))*(Ye.adjoint()*TYe*Ye.adjoint
      ()*Ye*1.2020569031595942) - 21.6*(1.*threeLoop*Sqr(g1) -
      1.6666666666666665*threeLoop*Sqr(g2))*(Ye.adjoint()*TYe*(TYe).adjoint()*
      Ye*1.2020569031595942) + 21.6*(1.*MassB*threeLoop*Sqr(g1) -
      1.6666666666666665*MassWB*threeLoop*Sqr(g2))*((TYe).adjoint()*Ye*Ye.
      adjoint()*Ye*1.2020569031595942) - 21.6*(1.*threeLoop*Sqr(g1) -
      1.6666666666666665*threeLoop*Sqr(g2))*((TYe).adjoint()*Ye*Ye.adjoint()*
      TYe*1.2020569031595942) - 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665
      *threeLoop*Sqr(g2))*((TYe).adjoint()*TYe*Ye.adjoint()*Ye*
      1.2020569031595942) - 10.8*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) - 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) - 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*
      1.2020569031595942) - 21.6*threeLoop*Sqr(g1)*(Ye.adjoint()*Ye*Ye.adjoint(
      )*me2*Ye*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_ml2_5 = ((36.*threeLoop*Sqr(g2)*(Ye.
      adjoint()*Ye*Ye.adjoint()*me2*Ye*1.2020569031595942) - 10.8*(1.*threeLoop
      *Sqr(g1) - 1.6666666666666665*threeLoop*Sqr(g2))*(Ye.adjoint()*Ye*Ye.
      adjoint()*Ye*ml2*1.2020569031595942) + 36.*mHd2*threeLoop*(Ye.adjoint()*
      Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*(TYe).adjoint()*TYe*1.2020569031595942) +
      12.*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*TYe*(TYe).adjoint()*Ye*
      1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*(TYe).adjoint()*Ye*
      Ye.adjoint()*TYe*1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*(
      TYe).adjoint()*TYe*Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(
      Ye.adjoint()*TYe*Ye.adjoint()*Ye*(TYe).adjoint()*Ye*1.2020569031595942) +
      12.*threeLoop*(Ye.adjoint()*TYe*(TYe).adjoint()*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + 12.*threeLoop*((TYe).adjoint()*Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*TYe*1.2020569031595942) + 12.*threeLoop*((TYe).adjoint()*Ye*
      Ye.adjoint()*TYe*Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*((
      TYe).adjoint()*TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) +
      6.*threeLoop*(ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*ml2*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 12.*threeLoop*(Ye.
      adjoint()*Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*1.2020569031595942) +
      12.*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*
      1.2020569031595942) + 12.*threeLoop*(Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()*me2*Ye*1.2020569031595942) + 6.*threeLoop*(Ye.adjoint()*Ye*Ye.
      adjoint()*Ye*Ye.adjoint()*Ye*ml2*1.2020569031595942))*UNITMATRIX(3)).real
      ();

   beta_ml2 = beta_ml2_1 + beta_ml2_2 + beta_ml2_3 + beta_ml2_4 + beta_ml2_5;


   return beta_ml2;
}

/**
 * Calculates the 4-loop beta function of ml2.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_ml2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_ml2;

   beta_ml2 = ZEROMATRIX(3,3);


   return beta_ml2;
}

/**
 * Calculates the 5-loop beta function of ml2.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_ml2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_ml2;

   beta_ml2 = ZEROMATRIX(3,3);


   return beta_ml2;
}

} // namespace flexiblesusy
