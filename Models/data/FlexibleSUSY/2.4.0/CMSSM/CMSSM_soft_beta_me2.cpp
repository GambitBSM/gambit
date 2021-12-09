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

// File generated at Thu 10 Oct 2019 17:27:51

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
 * Calculates the 1-loop beta function of me2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_me2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_me2;

   beta_me2 = (oneOver16PiSqr*(4*mHd2*(Ye*Ye.adjoint()) + 4*(TYe*(TYe).adjoint(
      )) + 2*(me2*Ye*Ye.adjoint()) + 4*(Ye*ml2*Ye.adjoint()) + 2*(Ye*Ye.adjoint
      ()*me2) + 0.4*g1*(3.872983346207417*Tr11 - 12*g1*AbsSqr(MassB))*
      UNITMATRIX(3))).real();


   return beta_me2;
}

/**
 * Calculates the 2-loop beta function of me2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_me2_2_loop(const Soft_traces& soft_traces) const
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

   beta_me2 = (twoLoop*(-0.8*(15*traceconjTYdTpTYd + 5*traceconjTYeTpTYe + 15*
      tracemd2YdAdjYd + 5*traceme2YeAdjYe + 5*traceml2AdjYeYe + 15*
      tracemq2AdjYdYd + 30*mHd2*traceYdAdjYd + 10*mHd2*traceYeAdjYe + 3*mHd2*
      Sqr(g1) + 6*AbsSqr(MassB)*Sqr(g1) - 15*mHd2*Sqr(g2) - 30*AbsSqr(MassWB)*
      Sqr(g2))*(Ye*Ye.adjoint()) + 0.8*(-15*traceAdjYdTYd - 5*traceAdjYeTYe + 3
      *MassB*Sqr(g1) - 15*MassWB*Sqr(g2))*(Ye*(TYe).adjoint()) - 0.8*(15*
      traceconjTYdTpYd + 5*traceconjTYeTpYe - 3*Conj(MassB)*Sqr(g1) + 15*Conj(
      MassWB)*Sqr(g2))*(TYe*Ye.adjoint()) - 0.8*(15*traceYdAdjYd + 5*
      traceYeAdjYe + 3*Sqr(g1) - 15*Sqr(g2))*(TYe*(TYe).adjoint()) - 0.4*(15*
      traceYdAdjYd + 5*traceYeAdjYe + 3*Sqr(g1) - 15*Sqr(g2))*(me2*Ye*Ye.
      adjoint()) - 0.8*(15*traceYdAdjYd + 5*traceYeAdjYe + 3*Sqr(g1) - 15*Sqr(
      g2))*(Ye*ml2*Ye.adjoint()) - 0.4*(15*traceYdAdjYd + 5*traceYeAdjYe + 3*
      Sqr(g1) - 15*Sqr(g2))*(Ye*Ye.adjoint()*me2) - 8*mHd2*(Ye*Ye.adjoint()*Ye*
      Ye.adjoint()) - 4*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()) - 4*(Ye*(TYe).
      adjoint()*TYe*Ye.adjoint()) - 4*(TYe*Ye.adjoint()*Ye*(TYe).adjoint()) - 4
      *(TYe*(TYe).adjoint()*Ye*Ye.adjoint()) - 2*(me2*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) - 4*(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()) - 4*(Ye*Ye.adjoint()
      *me2*Ye*Ye.adjoint()) - 4*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()) - 2*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*me2) + 0.32*g1*(15*g1*Tr2U111 +
      19.364916731037084*Tr31 + 351*AbsSqr(MassB)*Cube(g1))*UNITMATRIX(3))).
      real();


   return beta_me2;
}

/**
 * Calculates the 3-loop beta function of me2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_me2_3_loop(const Soft_traces& soft_traces) const
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


   Eigen::Matrix<double,3,3> beta_me2;

   const Eigen::Matrix<double,3,3> beta_me2_1 = ((709.004577193408*threeLoop*(-
      0.031683857513196405*mHd2*Power6(g1) - 0.031683857513196405*mHu2*Power6(
      g1) - 0.02112257167546427*tracemd2*Power6(g1) - 0.06336771502639281*
      traceme2*Power6(g1) - 0.031683857513196405*traceml2*Power6(g1) -
      0.010561285837732136*tracemq2*Power6(g1) - 0.08449028670185708*tracemu2*
      Power6(g1) + 0.047390385169310864*MassB*traceAdjTYdYd*Quad(g1) +
      0.0609304952176854*MassB*traceAdjTYeYe*Quad(g1) + 0.08801071531443445*
      MassB*traceAdjTYuYu*Quad(g1) - 0.028434231101586518*mHd2*traceAdjYdYd*
      Quad(g1) - 0.028434231101586518*traceAdjYdYdmq2*Quad(g1) -
      0.03655829713061124*mHd2*traceAdjYeYe*Quad(g1) - 0.03655829713061124*
      traceAdjYeYeml2*Quad(g1) - 0.05280642918866067*mHu2*traceAdjYuYu*Quad(g1)
      - 0.05280642918866067*traceAdjYuYumq2*Quad(g1) - 0.028434231101586518*
      traceTYdAdjTYd*Quad(g1) + 0.047390385169310864*MassB*traceTYdAdjYd*Quad(
      g1) - 0.03655829713061124*traceTYeAdjTYe*Quad(g1) + 0.0609304952176854*
      MassB*traceTYeAdjYe*Quad(g1) - 0.05280642918866067*traceTYuAdjTYu*Quad(g1
      ) + 0.08801071531443445*MassB*traceTYuAdjYu*Quad(g1) -
      0.028434231101586518*traceYdAdjYdmd2*Quad(g1) - 0.03655829713061124*
      traceYeAdjYeme2*Quad(g1) - 0.05280642918866067*traceYuAdjYumu2*Quad(g1) -
      0.08087943494860879*MassB*MassWB*Quad(g1)*Sqr(g2) - 0.26360704723991*
      MassB*MassG*Quad(g1)*Sqr(g3) + 1.*Power6(g1)*Sqr(MassB) -
      0.14217115550793258*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.18279148565305617*traceAdjYeYe*Quad(g1)*Sqr(MassB) - 0.2640321459433034
      *traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.1213191524229131*Quad(g1)*Sqr(g2)*
      Sqr(MassB) - 0.39541057085986514*Quad(g1)*Sqr(g3)*Sqr(MassB) -
      0.07222703940710706*Quad(g1)*Sqr(g3)*Sqr(MassG) - 0.022160568908998764*
      Quad(g1)*Sqr(g2)*Sqr(MassWB)) - 360.7200000000001*threeLoop*(-
      0.3992015968063871*traceAdjTYdTYdAdjYdYd - 0.06653359946773119*
      traceAdjTYdTYdAdjYuYu - 0.13306719893546237*traceAdjTYeTYeAdjYeYe -
      0.06653359946773119*traceAdjTYuTYuAdjYdYd - 0.3992015968063871*
      traceAdjYdTYdAdjTYdYd - 0.5988023952095807*mHd2*traceAdjYdYdAdjYdYd -
      0.3992015968063871*traceAdjYdYdAdjYdYdmq2 - 0.06653359946773119*
      traceAdjYdYdAdjYuYumq2 + 0.19960079840319356*traceAdjYdYd*traceAdjYdYdmq2
       - 0.13306719893546237*traceAdjYeTYeAdjTYeYe + 0.19960079840319356*mHd2*
      traceAdjYdYd*traceAdjYeYe + 0.06653359946773119*traceAdjYdYdmq2*
      traceAdjYeYe - 0.19960079840319356*mHd2*traceAdjYeYeAdjYeYe -
      0.13306719893546237*traceAdjYeYeAdjYeYeml2 + 0.06653359946773119*
      traceAdjYdYd*traceAdjYeYeml2 + 0.02217786648924373*traceAdjYeYe*
      traceAdjYeYeml2 - 0.06653359946773119*traceAdjYuTYuAdjTYdYd -
      0.13306719893546237*mHd2*traceAdjYuYuAdjYdYd - 0.06653359946773119*mHu2*
      traceAdjYuYuAdjYdYd - 0.06653359946773119*traceAdjYuYuAdjYdYdmq2 +
      0.19960079840319356*traceAdjYdYd*traceTYdAdjTYd + 0.06653359946773119*
      traceAdjYeYe*traceTYdAdjTYd - 0.06653359946773119*traceTYdAdjTYuYuAdjYd +
      0.16267465069860276*mHd2*Quad(g1) - 0.003992015968063871*mHu2*Quad(g1) -
      0.0026613439787092474*tracemd2*Quad(g1) - 0.007984031936127742*traceme2*
      Quad(g1) - 0.003992015968063871*traceml2*Quad(g1) - 0.0013306719893546237
      *tracemq2*Quad(g1) - 0.01064537591483699*tracemu2*Quad(g1) +
      0.27445109780439114*mHd2*Quad(g2) + 0.03326679973386559*mHu2*Quad(g2) +
      0.03326679973386559*traceml2*Quad(g2) + 0.09980039920159678*tracemq2*Quad
      (g2) + 0.11865158571745395*MassB*traceAdjTYdYd*Sqr(g1) +
      0.009980039920159679*MassB*traceAdjTYeYe*Sqr(g1) - 0.2373031714349079*
      mHd2*traceAdjYdYd*Sqr(g1) - 0.11865158571745395*traceAdjYdYdmq2*Sqr(g1) -
      0.019960079840319358*mHd2*traceAdjYeYe*Sqr(g1) - 0.009980039920159679*
      traceAdjYeYeml2*Sqr(g1) - 0.11865158571745395*traceTYdAdjTYd*Sqr(g1) +
      0.14970059880239517*MassWB*traceAdjTYdYd*Sqr(g2) + 0.04990019960079839*
      MassWB*traceAdjTYeYe*Sqr(g2) - 0.29940119760479034*mHd2*traceAdjYdYd*Sqr(
      g2) - 0.14970059880239517*traceAdjYdYdmq2*Sqr(g2) - 0.09980039920159678*
      mHd2*traceAdjYeYe*Sqr(g2) - 0.04990019960079839*traceAdjYeYeml2*Sqr(g2) -
      0.14970059880239517*traceTYdAdjTYd*Sqr(g2) + 0.29940119760479034*MassB*
      MassWB*Sqr(g1)*Sqr(g2) + 0.14970059880239517*mHd2*Sqr(g1)*Sqr(g2) -
      0.3548458638278997*MassG*traceAdjTYdYd*Sqr(g3) + 0.7096917276557994*mHd2*
      traceAdjYdYd*Sqr(g3) + 0.3548458638278997*traceAdjYdYdmq2*Sqr(g3) +
      0.3548458638278997*traceTYdAdjTYd*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) -
      0.2373031714349079*traceAdjYdYd*Sqr(g1)*Sqr(MassB) - 0.019960079840319358
      *traceAdjYeYe*Sqr(g1)*Sqr(MassB) + 0.29940119760479034*Sqr(g1)*Sqr(g2)*
      Sqr(MassB) + 0.7096917276557994*traceAdjYdYd*Sqr(g3)*Sqr(MassG) +
      1.3140385894876911*Quad(g2)*Sqr(MassWB) - 0.29940119760479034*
      traceAdjYdYd*Sqr(g2)*Sqr(MassWB) - 0.09980039920159678*traceAdjYeYe*Sqr(
      g2)*Sqr(MassWB) + 0.29940119760479034*Sqr(g1)*Sqr(g2)*Sqr(MassWB) +
      0.29940119760479034*mHd2*Sqr(traceAdjYdYd) + 0.03326679973386559*mHd2*Sqr
      (traceAdjYeYe))*(Ye*Ye.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_2 = ((-42.8*threeLoop*(
      1.6822429906542058*traceAdjTYdYd*traceTYdAdjYd + 0.5607476635514019*
      traceAdjTYeYe*traceTYdAdjYd + 0.5607476635514019*traceAdjYdYd*
      traceTYeAdjTYe + 0.1869158878504673*traceAdjYeYe*traceTYeAdjTYe +
      0.5607476635514019*traceAdjTYdYd*traceTYeAdjYe + 0.1869158878504673*
      traceAdjTYeYe*traceTYeAdjYe + 1.6822429906542058*traceAdjYdYd*
      traceYdAdjYdmd2 + 0.5607476635514019*traceAdjYeYe*traceYdAdjYdmd2 -
      3.3644859813084116*traceYdAdjYdYdAdjYdmd2 - 0.5607476635514019*
      traceYdAdjYuYuAdjYdmd2 + 0.5607476635514019*traceAdjYdYd*traceYeAdjYeme2
      + 0.1869158878504673*traceAdjYeYe*traceYeAdjYeme2 - 1.1214953271028039*
      traceYeAdjYeYeAdjYeme2 - 0.5607476635514019*traceYuAdjYdYdAdjYumu2 + 1.*
      MassB*traceTYdAdjYd*Sqr(g1) - 0.08411214953271029*traceTYeAdjTYe*Sqr(g1)
      + 0.08411214953271029*MassB*traceTYeAdjYe*Sqr(g1) - 1.*traceYdAdjYdmd2*
      Sqr(g1) - 0.08411214953271029*traceYeAdjYeme2*Sqr(g1) +
      1.2616822429906542*MassWB*traceTYdAdjYd*Sqr(g2) - 0.42056074766355145*
      traceTYeAdjTYe*Sqr(g2) + 0.42056074766355145*MassWB*traceTYeAdjYe*Sqr(g2)
      - 1.2616822429906542*traceYdAdjYdmd2*Sqr(g2) - 0.42056074766355145*
      traceYeAdjYeme2*Sqr(g2) - 2.990654205607477*MassG*traceTYdAdjYd*Sqr(g3) +
      2.990654205607477*traceYdAdjYdmd2*Sqr(g3))*(Ye*Ye.adjoint()) + 120.24*
      threeLoop*(1.1976047904191618*traceAdjYdTYdAdjYdYd + 0.3992015968063872*
      traceAdjYeTYeAdjYeYe + 0.1996007984031936*traceAdjYuTYuAdjYdYd -
      0.5988023952095809*traceAdjYdYd*traceTYdAdjYd - 0.1996007984031936*
      traceAdjYeYe*traceTYdAdjYd + 0.1996007984031936*traceTYdAdjYuYuAdjYd -
      0.1996007984031936*traceAdjYdYd*traceTYeAdjYe - 0.06653359946773121*
      traceAdjYeYe*traceTYeAdjYe + 1.*MassB*Quad(g1) + 1.4471057884231537*
      MassWB*Quad(g2) - 0.3559547571523619*MassB*traceAdjYdYd*Sqr(g1) -
      0.029940119760479045*MassB*traceAdjYeYe*Sqr(g1) + 0.3559547571523619*
      traceTYdAdjYd*Sqr(g1) + 0.029940119760479045*traceTYeAdjYe*Sqr(g1) -
      0.44910179640718567*MassWB*traceAdjYdYd*Sqr(g2) - 0.14970059880239522*
      MassWB*traceAdjYeYe*Sqr(g2) + 0.44910179640718567*traceTYdAdjYd*Sqr(g2) +
      0.14970059880239522*traceTYeAdjYe*Sqr(g2) + 0.44910179640718567*MassB*Sqr
      (g1)*Sqr(g2) + 0.44910179640718567*MassWB*Sqr(g1)*Sqr(g2) +
      1.0645375914836994*MassG*traceAdjYdYd*Sqr(g3) - 1.0645375914836994*
      traceTYdAdjYd*Sqr(g3))*(Ye*(TYe).adjoint()) + 120.24*threeLoop*(
      0.1996007984031936*traceAdjTYuYuAdjYdYd - 0.5988023952095809*
      traceAdjTYdYd*traceAdjYdYd - 0.1996007984031936*traceAdjTYeYe*
      traceAdjYdYd + 1.1976047904191618*traceAdjYdYdAdjTYdYd -
      0.1996007984031936*traceAdjTYdYd*traceAdjYeYe - 0.06653359946773121*
      traceAdjTYeYe*traceAdjYeYe + 0.3992015968063872*traceAdjYeYeAdjTYeYe +
      0.1996007984031936*traceAdjYuYuAdjTYdYd + 1.*MassB*Quad(g1) +
      1.4471057884231537*MassWB*Quad(g2) + 0.3559547571523619*traceAdjTYdYd*Sqr
      (g1) + 0.029940119760479045*traceAdjTYeYe*Sqr(g1) - 0.3559547571523619*
      MassB*traceAdjYdYd*Sqr(g1) - 0.029940119760479045*MassB*traceAdjYeYe*Sqr(
      g1) + 0.44910179640718567*traceAdjTYdYd*Sqr(g2) + 0.14970059880239522*
      traceAdjTYeYe*Sqr(g2) - 0.44910179640718567*MassWB*traceAdjYdYd*Sqr(g2) -
      0.14970059880239522*MassWB*traceAdjYeYe*Sqr(g2) + 0.44910179640718567*
      MassB*Sqr(g1)*Sqr(g2) + 0.44910179640718567*MassWB*Sqr(g1)*Sqr(g2) -
      1.0645375914836994*traceAdjTYdYd*Sqr(g3) + 1.0645375914836994*MassG*
      traceAdjYdYd*Sqr(g3))*(TYe*Ye.adjoint()) - 60.12*threeLoop*(-
      1.1976047904191618*traceAdjYdYdAdjYdYd + 0.3992015968063872*traceAdjYdYd*
      traceAdjYeYe - 0.3992015968063872*traceAdjYeYeAdjYeYe -
      0.3992015968063872*traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.4471057884231537
      *Quad(g2) - 0.7119095143047238*traceAdjYdYd*Sqr(g1) - 0.05988023952095809
      *traceAdjYeYe*Sqr(g1) - 0.8982035928143713*traceAdjYdYd*Sqr(g2) -
      0.29940119760479045*traceAdjYeYe*Sqr(g2) + 0.8982035928143713*Sqr(g1)*Sqr
      (g2) + 2.129075182967399*traceAdjYdYd*Sqr(g3) + 0.5988023952095809*Sqr(
      traceAdjYdYd) + 0.06653359946773121*Sqr(traceAdjYeYe))*(TYe*(TYe).adjoint
      ()) - 30.06*threeLoop*(-1.1976047904191618*traceAdjYdYdAdjYdYd +
      0.3992015968063872*traceAdjYdYd*traceAdjYeYe - 0.3992015968063872*
      traceAdjYeYeAdjYeYe - 0.3992015968063872*traceAdjYuYuAdjYdYd + 1.*Quad(g1
      ) + 1.4471057884231537*Quad(g2) - 0.7119095143047238*traceAdjYdYd*Sqr(g1)
      - 0.05988023952095809*traceAdjYeYe*Sqr(g1) - 0.8982035928143713*
      traceAdjYdYd*Sqr(g2) - 0.29940119760479045*traceAdjYeYe*Sqr(g2) +
      0.8982035928143713*Sqr(g1)*Sqr(g2) + 2.129075182967399*traceAdjYdYd*Sqr(
      g3) + 0.5988023952095809*Sqr(traceAdjYdYd) + 0.06653359946773121*Sqr(
      traceAdjYeYe))*(me2*Ye*Ye.adjoint()) - 60.12*Sqr(g1)*(1.*threeLoop*Sqr(g1
      ) + 0.8982035928143713*threeLoop*Sqr(g2))*(Ye*ml2*Ye.adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_3 = ((-87.*threeLoop*(-
      0.8275862068965517*traceAdjYdYdAdjYdYd + 0.27586206896551724*traceAdjYdYd
      *traceAdjYeYe - 0.27586206896551724*traceAdjYeYeAdjYeYe -
      0.27586206896551724*traceAdjYuYuAdjYdYd + 1.*Quad(g2) -
      0.4919540229885057*traceAdjYdYd*Sqr(g1) - 0.041379310344827586*
      traceAdjYeYe*Sqr(g1) - 0.6206896551724138*traceAdjYdYd*Sqr(g2) -
      0.20689655172413793*traceAdjYeYe*Sqr(g2) + 1.471264367816092*traceAdjYdYd
      *Sqr(g3) + 0.41379310344827586*Sqr(traceAdjYdYd) + 0.04597701149425287*
      Sqr(traceAdjYeYe))*(Ye*ml2*Ye.adjoint()) - 194.39999999999998*threeLoop*(
      0.16666666666666669*mHd2*Quad(g1) + 0.0925925925925926*mHd2*Quad(g2) +
      0.08641975308641976*MassB*traceAdjTYdYd*Sqr(g1) + 0.11111111111111113*
      MassB*traceAdjTYeYe*Sqr(g1) - 0.17283950617283952*mHd2*traceAdjYdYd*Sqr(
      g1) - 0.08641975308641976*traceAdjYdYdmq2*Sqr(g1) - 0.22222222222222227*
      mHd2*traceAdjYeYe*Sqr(g1) - 0.11111111111111113*traceAdjYeYeml2*Sqr(g1) -
      0.08641975308641976*traceTYdAdjTYd*Sqr(g1) + 0.08641975308641976*MassB*
      traceTYdAdjYd*Sqr(g1) - 0.11111111111111113*traceTYeAdjTYe*Sqr(g1) +
      0.11111111111111113*MassB*traceTYeAdjYe*Sqr(g1) - 0.08641975308641976*
      traceYdAdjYdmd2*Sqr(g1) - 0.11111111111111113*traceYeAdjYeme2*Sqr(g1) -
      0.5555555555555556*MassWB*traceAdjTYdYd*Sqr(g2) - 0.1851851851851852*
      MassWB*traceAdjTYeYe*Sqr(g2) + 1.1111111111111112*mHd2*traceAdjYdYd*Sqr(
      g2) + 0.5555555555555556*traceAdjYdYdmq2*Sqr(g2) + 0.3703703703703704*
      mHd2*traceAdjYeYe*Sqr(g2) + 0.1851851851851852*traceAdjYeYeml2*Sqr(g2) +
      0.5555555555555556*traceTYdAdjTYd*Sqr(g2) - 0.5555555555555556*MassWB*
      traceTYdAdjYd*Sqr(g2) + 0.1851851851851852*traceTYeAdjTYe*Sqr(g2) -
      0.1851851851851852*MassWB*traceTYeAdjYe*Sqr(g2) + 0.5555555555555556*
      traceYdAdjYdmd2*Sqr(g2) + 0.1851851851851852*traceYeAdjYeme2*Sqr(g2) -
      0.6666666666666667*MassB*MassWB*Sqr(g1)*Sqr(g2) - 0.33333333333333337*
      mHd2*Sqr(g1)*Sqr(g2) + 0.9876543209876545*MassG*traceAdjTYdYd*Sqr(g3) -
      1.975308641975309*mHd2*traceAdjYdYd*Sqr(g3) - 0.9876543209876545*
      traceAdjYdYdmq2*Sqr(g3) - 0.9876543209876545*traceTYdAdjTYd*Sqr(g3) +
      0.9876543209876545*MassG*traceTYdAdjYd*Sqr(g3) - 0.9876543209876545*
      traceYdAdjYdmd2*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) - 0.17283950617283952*
      traceAdjYdYd*Sqr(g1)*Sqr(MassB) - 0.22222222222222227*traceAdjYeYe*Sqr(g1
      )*Sqr(MassB) - 0.6666666666666667*Sqr(g1)*Sqr(g2)*Sqr(MassB) -
      1.975308641975309*traceAdjYdYd*Sqr(g3)*Sqr(MassG) + 0.5555555555555556*
      Quad(g2)*Sqr(MassWB) + 1.1111111111111112*traceAdjYdYd*Sqr(g2)*Sqr(MassWB
      ) + 0.3703703703703704*traceAdjYeYe*Sqr(g2)*Sqr(MassWB) -
      0.6666666666666667*Sqr(g1)*Sqr(g2)*Sqr(MassWB))*(Ye*Ye.adjoint()*
      1.2020569031595942) - 30.06*threeLoop*(-1.1976047904191618*
      traceAdjYdYdAdjYdYd + 0.3992015968063872*traceAdjYdYd*traceAdjYeYe -
      0.3992015968063872*traceAdjYeYeAdjYeYe - 0.3992015968063872*
      traceAdjYuYuAdjYdYd + 1.*Quad(g1) + 1.4471057884231537*Quad(g2) -
      0.7119095143047238*traceAdjYdYd*Sqr(g1) - 0.05988023952095809*
      traceAdjYeYe*Sqr(g1) - 0.8982035928143713*traceAdjYdYd*Sqr(g2) -
      0.29940119760479045*traceAdjYeYe*Sqr(g2) + 0.8982035928143713*Sqr(g1)*Sqr
      (g2) + 2.129075182967399*traceAdjYdYd*Sqr(g3) + 0.5988023952095809*Sqr(
      traceAdjYdYd) + 0.06653359946773121*Sqr(traceAdjYeYe))*(Ye*Ye.adjoint()*
      me2) + 64.8*threeLoop*(1.*MassB*Quad(g1) + 0.5555555555555556*MassWB*Quad
      (g2) - 0.2592592592592593*MassB*traceAdjYdYd*Sqr(g1) -
      0.33333333333333337*MassB*traceAdjYeYe*Sqr(g1) + 0.2592592592592593*
      traceTYdAdjYd*Sqr(g1) + 0.33333333333333337*traceTYeAdjYe*Sqr(g1) +
      1.6666666666666667*MassWB*traceAdjYdYd*Sqr(g2) + 0.5555555555555556*
      MassWB*traceAdjYeYe*Sqr(g2) - 1.6666666666666667*traceTYdAdjYd*Sqr(g2) -
      0.5555555555555556*traceTYeAdjYe*Sqr(g2) - 1.*MassB*Sqr(g1)*Sqr(g2) - 1.*
      MassWB*Sqr(g1)*Sqr(g2) - 2.9629629629629632*MassG*traceAdjYdYd*Sqr(g3) +
      2.9629629629629632*traceTYdAdjYd*Sqr(g3))*(Ye*(TYe).adjoint()*
      1.2020569031595942) + 64.8*threeLoop*(1.*MassB*Quad(g1) +
      0.5555555555555556*MassWB*Quad(g2) + 0.2592592592592593*traceAdjTYdYd*Sqr
      (g1) + 0.33333333333333337*traceAdjTYeYe*Sqr(g1) - 0.2592592592592593*
      MassB*traceAdjYdYd*Sqr(g1) - 0.33333333333333337*MassB*traceAdjYeYe*Sqr(
      g1) - 1.6666666666666667*traceAdjTYdYd*Sqr(g2) - 0.5555555555555556*
      traceAdjTYeYe*Sqr(g2) + 1.6666666666666667*MassWB*traceAdjYdYd*Sqr(g2) +
      0.5555555555555556*MassWB*traceAdjYeYe*Sqr(g2) - 1.*MassB*Sqr(g1)*Sqr(g2)
      - 1.*MassWB*Sqr(g1)*Sqr(g2) + 2.9629629629629632*traceAdjTYdYd*Sqr(g3) -
      2.9629629629629632*MassG*traceAdjYdYd*Sqr(g3))*(TYe*Ye.adjoint()*
      1.2020569031595942) - 32.4*(1.*threeLoop*Quad(g1) + 0.5555555555555556*
      threeLoop*Quad(g2) - 2.*threeLoop*Sqr(g1)*Sqr(g2))*(TYe*(TYe).adjoint()*
      1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_4 = ((16.8*threeLoop*(1.*
      traceAdjYdYd*Sqr(g1) + 1.2857142857142858*traceAdjYeYe*Sqr(g1) -
      6.428571428571428*traceAdjYdYd*Sqr(g2) - 2.142857142857143*traceAdjYeYe*
      Sqr(g2) + 11.428571428571429*traceAdjYdYd*Sqr(g3))*(TYe*(TYe).adjoint()*
      1.2020569031595942) - 16.2*threeLoop*(1.*Quad(g1) + 0.5555555555555556*
      Quad(g2) - 0.5185185185185186*traceAdjYdYd*Sqr(g1) - 0.6666666666666667*
      traceAdjYeYe*Sqr(g1) + 3.3333333333333335*traceAdjYdYd*Sqr(g2) +
      1.1111111111111112*traceAdjYeYe*Sqr(g2) - 2.*Sqr(g1)*Sqr(g2) -
      5.9259259259259265*traceAdjYdYd*Sqr(g3))*(me2*Ye*Ye.adjoint()*
      1.2020569031595942) - 32.4*threeLoop*(1.*Quad(g1) + 0.5555555555555556*
      Quad(g2) - 0.5185185185185186*traceAdjYdYd*Sqr(g1) - 0.6666666666666667*
      traceAdjYeYe*Sqr(g1) + 3.3333333333333335*traceAdjYdYd*Sqr(g2) +
      1.1111111111111112*traceAdjYeYe*Sqr(g2) - 2.*Sqr(g1)*Sqr(g2) -
      5.9259259259259265*traceAdjYdYd*Sqr(g3))*(Ye*ml2*Ye.adjoint()*
      1.2020569031595942) - 16.2*threeLoop*(1.*Quad(g1) + 0.5555555555555556*
      Quad(g2) - 0.5185185185185186*traceAdjYdYd*Sqr(g1) - 0.6666666666666667*
      traceAdjYeYe*Sqr(g1) + 3.3333333333333335*traceAdjYdYd*Sqr(g2) +
      1.1111111111111112*traceAdjYeYe*Sqr(g2) - 2.*Sqr(g1)*Sqr(g2) -
      5.9259259259259265*traceAdjYdYd*Sqr(g3))*(Ye*Ye.adjoint()*me2*
      1.2020569031595942) + 7.2*threeLoop*(5.*mHd2*traceAdjYdYd +
      1.6666666666666665*traceAdjYdYdmq2 + 1.6666666666666665*mHd2*traceAdjYeYe
       + 0.5555555555555556*traceAdjYeYeml2 + 1.6666666666666665*traceTYdAdjTYd
       + 0.5555555555555556*traceTYeAdjTYe + 1.6666666666666665*traceYdAdjYdmd2
       + 0.5555555555555556*traceYeAdjYeme2 + 1.*mHd2*Sqr(g1) + 5.*mHd2*Sqr(g2)
      + 1.*Sqr(g1)*Sqr(MassB) + 5.*Sqr(g2)*Sqr(MassWB))*(Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) - 3.6*threeLoop*(-3.333333333333333*traceTYdAdjYd -
      1.1111111111111112*traceTYeAdjYe + 1.*MassB*Sqr(g1) + 5.*MassWB*Sqr(g2))*
      (Ye*Ye.adjoint()*Ye*(TYe).adjoint()) - 3.6*threeLoop*(-3.333333333333333*
      traceAdjTYdYd - 1.1111111111111112*traceAdjTYeYe + 1.*MassB*Sqr(g1) + 5.*
      MassWB*Sqr(g2))*(Ye*Ye.adjoint()*TYe*Ye.adjoint()) + 3.6*threeLoop*(
      3.333333333333333*traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*Sqr
      (g1) + 5.*Sqr(g2))*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()) - 3.6*threeLoop*
      (-3.333333333333333*traceTYdAdjYd - 1.1111111111111112*traceTYeAdjYe + 1.
      *MassB*Sqr(g1) + 5.*MassWB*Sqr(g2))*(Ye*(TYe).adjoint()*Ye*Ye.adjoint())
      + 3.6*threeLoop*(3.333333333333333*traceAdjYdYd + 1.1111111111111112*
      traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2))*(Ye*(TYe).adjoint()*TYe*Ye.
      adjoint()) - 3.6*threeLoop*(-3.333333333333333*traceAdjTYdYd -
      1.1111111111111112*traceAdjTYeYe + 1.*MassB*Sqr(g1) + 5.*MassWB*Sqr(g2))*
      (TYe*Ye.adjoint()*Ye*Ye.adjoint()) + 3.6*threeLoop*(3.333333333333333*
      traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2))
      *(TYe*Ye.adjoint()*Ye*(TYe).adjoint()) + 3.6*threeLoop*(3.333333333333333
      *traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2)
      )*(TYe*(TYe).adjoint()*Ye*Ye.adjoint()) + 1.8*threeLoop*(
      3.333333333333333*traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*Sqr
      (g1) + 5.*Sqr(g2))*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()) + 3.6*threeLoop*
      (3.333333333333333*traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*
      Sqr(g1) + 5.*Sqr(g2))*(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()) + 3.6*
      threeLoop*(3.333333333333333*traceAdjYdYd + 1.1111111111111112*
      traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2))*(Ye*Ye.adjoint()*me2*Ye*Ye.
      adjoint()) + 3.6*threeLoop*(3.333333333333333*traceAdjYdYd +
      1.1111111111111112*traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2))*(Ye*Ye.adjoint
      ()*Ye*ml2*Ye.adjoint()) + 43.2*(1.*mHd2*threeLoop*Sqr(g1) -
      1.6666666666666665*mHd2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(
      MassB) - 1.6666666666666665*threeLoop*Sqr(g2)*Sqr(MassWB))*(Ye*Ye.adjoint
      ()*Ye*Ye.adjoint()*1.2020569031595942) + 1.8*threeLoop*(3.333333333333333
      *traceAdjYdYd + 1.1111111111111112*traceAdjYeYe + 1.*Sqr(g1) + 5.*Sqr(g2)
      )*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2) - 21.6*(1.*MassB*threeLoop*Sqr(g1
      ) - 1.6666666666666665*MassWB*threeLoop*Sqr(g2))*(Ye*Ye.adjoint()*Ye*(TYe
      ).adjoint()*1.2020569031595942) - 21.6*MassB*threeLoop*Sqr(g1)*(Ye*Ye.
      adjoint()*TYe*Ye.adjoint()*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_me2_5 = ((36.*MassWB*threeLoop*Sqr(g2)*
      (Ye*Ye.adjoint()*TYe*Ye.adjoint()*1.2020569031595942) + 21.6*(1.*
      threeLoop*Sqr(g1) - 1.6666666666666665*threeLoop*Sqr(g2))*(Ye*Ye.adjoint(
      )*TYe*(TYe).adjoint()*1.2020569031595942) - 21.6*(1.*MassB*threeLoop*Sqr(
      g1) - 1.6666666666666665*MassWB*threeLoop*Sqr(g2))*(Ye*(TYe).adjoint()*Ye
      *Ye.adjoint()*1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) -
      1.6666666666666665*threeLoop*Sqr(g2))*(Ye*(TYe).adjoint()*TYe*Ye.adjoint(
      )*1.2020569031595942) - 21.6*(1.*MassB*threeLoop*Sqr(g1) -
      1.6666666666666665*MassWB*threeLoop*Sqr(g2))*(TYe*Ye.adjoint()*Ye*Ye.
      adjoint()*1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) -
      1.6666666666666665*threeLoop*Sqr(g2))*(TYe*Ye.adjoint()*Ye*(TYe).adjoint(
      )*1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(TYe*(TYe).adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 10.8*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*
      1.2020569031595942) + 21.6*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*
      1.2020569031595942) + 10.8*(1.*threeLoop*Sqr(g1) - 1.6666666666666665*
      threeLoop*Sqr(g2))*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2*
      1.2020569031595942) + 36.*mHd2*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()
      *Ye*Ye.adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*(
      TYe).adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*(TYe).adjoint()*TYe*
      Ye.adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye*(TYe).
      adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*(TYe).adjoint()*Ye*Ye.adjoint()*TYe*Ye.
      adjoint()) + 12.*threeLoop*(Ye*(TYe).adjoint()*TYe*Ye.adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye*(TYe).
      adjoint()) + 12.*threeLoop*(TYe*Ye.adjoint()*Ye*(TYe).adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(TYe*(TYe).adjoint()*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) + 6.*threeLoop*(me2*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*Ye.
      adjoint()) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*Ye.
      adjoint()) + 72.*mHd2*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.
      adjoint()*1.2020569031595942) + 6.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.
      adjoint()*Ye*Ye.adjoint()*me2) + 24.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.
      adjoint()*TYe*(TYe).adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*Ye.
      adjoint()*Ye*(TYe).adjoint()*TYe*Ye.adjoint()*1.2020569031595942) + 24.*
      threeLoop*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye*(TYe).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*TYe*(TYe).adjoint()*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*(TYe).adjoint()*
      Ye*Ye.adjoint()*TYe*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*
      (TYe).adjoint()*TYe*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) +
      24.*threeLoop*(TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye*(TYe).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(TYe*Ye.adjoint()*Ye*(TYe).adjoint()*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYe*(TYe).adjoint()*
      Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 12.*threeLoop*(me2*
      Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 24.
      *threeLoop*(Ye*ml2*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*
      Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*Ye.adjoint()*Ye*
      ml2*Ye.adjoint()*Ye*Ye.adjoint()*1.2020569031595942) + 24.*threeLoop*(Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*me2*Ye*Ye.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*ml2*Ye.adjoint()*
      1.2020569031595942) + 12.*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*me2*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_me2 = beta_me2_1 + beta_me2_2 + beta_me2_3 + beta_me2_4 + beta_me2_5;


   return beta_me2;
}

/**
 * Calculates the 4-loop beta function of me2.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_me2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_me2;

   beta_me2 = ZEROMATRIX(3,3);


   return beta_me2;
}

/**
 * Calculates the 5-loop beta function of me2.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_me2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_me2;

   beta_me2 = ZEROMATRIX(3,3);


   return beta_me2;
}

} // namespace flexiblesusy
