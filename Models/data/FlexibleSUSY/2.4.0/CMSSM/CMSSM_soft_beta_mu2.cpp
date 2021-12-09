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

// File generated at Thu 10 Oct 2019 17:27:49

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
 * Calculates the 1-loop beta function of mu2.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mu2_1_loop(const Soft_traces& soft_traces) const
{
   const double Tr11 = TRACE_STRUCT.Tr11;


   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = (oneOver16PiSqr*(4*mHu2*(Yu*Yu.adjoint()) + 4*(TYu*(TYu).adjoint(
      )) + 2*(mu2*Yu*Yu.adjoint()) + 4*(Yu*mq2*Yu.adjoint()) + 2*(Yu*Yu.adjoint
      ()*mu2) - 0.26666666666666666*(3.872983346207417*g1*Tr11 + 8*AbsSqr(MassB
      )*Sqr(g1) + 40*AbsSqr(MassG)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_mu2;
}

/**
 * Calculates the 2-loop beta function of mu2.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mu2_2_loop(const Soft_traces& soft_traces) const
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

   beta_mu2 = (twoLoop*(-0.8*(15*traceconjTYuTpTYu + 15*tracemq2AdjYuYu + 15*
      tracemu2YuAdjYu + 30*mHu2*traceYuAdjYu + mHu2*Sqr(g1) + 2*AbsSqr(MassB)*
      Sqr(g1) - 15*mHu2*Sqr(g2) - 30*AbsSqr(MassWB)*Sqr(g2))*(Yu*Yu.adjoint())
      + 0.8*(-15*traceAdjYuTYu + MassB*Sqr(g1) - 15*MassWB*Sqr(g2))*(Yu*(TYu).
      adjoint()) - 0.8*(15*traceconjTYuTpYu - Conj(MassB)*Sqr(g1) + 15*Conj(
      MassWB)*Sqr(g2))*(TYu*Yu.adjoint()) - 0.8*(15*traceYuAdjYu + Sqr(g1) - 15
      *Sqr(g2))*(TYu*(TYu).adjoint()) - 0.4*(15*traceYuAdjYu + Sqr(g1) - 15*Sqr
      (g2))*(mu2*Yu*Yu.adjoint()) - 0.8*(15*traceYuAdjYu + Sqr(g1) - 15*Sqr(g2)
      )*(Yu*mq2*Yu.adjoint()) - 0.4*(15*traceYuAdjYu + Sqr(g1) - 15*Sqr(g2))*(
      Yu*Yu.adjoint()*mu2) - 4*(mHd2 + mHu2)*(Yu*Yd.adjoint()*Yd*Yu.adjoint())
      - 4*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()) - 8*mHu2*(Yu*Yu.adjoint()*Yu*Yu
      .adjoint()) - 4*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()) - 4*(Yu*(TYd).
      adjoint()*TYd*Yu.adjoint()) - 4*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()) - 4
      *(TYu*Yd.adjoint()*Yd*(TYu).adjoint()) - 4*(TYu*Yu.adjoint()*Yu*(TYu).
      adjoint()) - 4*(TYu*(TYd).adjoint()*Yd*Yu.adjoint()) - 4*(TYu*(TYu).
      adjoint()*Yu*Yu.adjoint()) - 2*(mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()) - 2*
      (mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint()) - 4*(Yu*mq2*Yd.adjoint()*Yd*Yu.
      adjoint()) - 4*(Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()) - 4*(Yu*Yd.adjoint()
      *md2*Yd*Yu.adjoint()) - 4*(Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()) - 2*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*mu2) - 4*(Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint(
      )) - 4*(Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()) - 2*(Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*mu2) + 0.07111111111111111*(-58.09475019311125*g1*Tr31 + 642*
      AbsSqr(MassB)*Quad(g1) + 150*Tr23*Quad(g3) - 600*AbsSqr(MassG)*Quad(g3) +
      30*Tr2U111*Sqr(g1) + 160*AbsSqr(MassB)*Sqr(g1)*Sqr(g3) + 160*AbsSqr(MassG
      )*Sqr(g1)*Sqr(g3) + 80*MassG*Conj(MassB)*Sqr(g1)*Sqr(g3) + 80*MassB*Conj(
      MassG)*Sqr(g1)*Sqr(g3))*UNITMATRIX(3))).real();


   return beta_mu2;
}

/**
 * Calculates the 3-loop beta function of mu2.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mu2_3_loop(const Soft_traces& soft_traces) const
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


   Eigen::Matrix<double,3,3> beta_mu2;

   const Eigen::Matrix<double,3,3> beta_mu2_1 = ((401.01536764151473*threeLoop*
      (-0.02276886973276538*mHd2*Power6(g1) - 0.02276886973276538*mHu2*Power6(
      g1) - 0.015179246488510253*tracemd2*Power6(g1) - 0.04553773946553076*
      traceme2*Power6(g1) - 0.02276886973276538*traceml2*Power6(g1) -
      0.007589623244255127*tracemq2*Power6(g1) - 0.060716985954041014*tracemu2*
      Power6(g1) + 0.0886638229469057*tracemd2*Power6(g3) + 0.1773276458938114*
      tracemq2*Power6(g3) + 0.0886638229469057*tracemu2*Power6(g3) +
      0.03723880563770039*MassB*traceAdjTYdYd*Quad(g1) + 0.04787846439132907*
      MassB*traceAdjTYeYe*Quad(g1) + 0.06915778189858644*MassB*traceAdjTYuYu*
      Quad(g1) - 0.022343283382620236*mHd2*traceAdjYdYd*Quad(g1) -
      0.022343283382620236*traceAdjYdYdmq2*Quad(g1) - 0.028727078634797443*mHd2
      *traceAdjYeYe*Quad(g1) - 0.028727078634797443*traceAdjYeYeml2*Quad(g1) -
      0.04149466913915186*mHu2*traceAdjYuYu*Quad(g1) - 0.04149466913915186*
      traceAdjYuYumq2*Quad(g1) - 0.022343283382620236*traceTYdAdjTYd*Quad(g1) +
      0.03723880563770039*MassB*traceTYdAdjYd*Quad(g1) - 0.028727078634797443*
      traceTYeAdjTYe*Quad(g1) + 0.04787846439132907*MassB*traceTYeAdjYe*Quad(g1
      ) - 0.04149466913915186*traceTYuAdjTYu*Quad(g1) + 0.06915778189858644*
      MassB*traceTYuAdjYu*Quad(g1) - 0.022343283382620236*traceYdAdjYdmd2*Quad(
      g1) - 0.028727078634797443*traceYeAdjYeme2*Quad(g1) - 0.04149466913915186
      *traceYuAdjYumu2*Quad(g1) + 0.26599146884071706*MassG*traceAdjTYdYd*Quad(
      g3) + 0.26599146884071706*MassG*traceAdjTYuYu*Quad(g3) -
      0.15959488130443025*mHd2*traceAdjYdYd*Quad(g3) - 0.15959488130443025*
      traceAdjYdYdmq2*Quad(g3) - 0.15959488130443025*mHu2*traceAdjYuYu*Quad(g3)
      - 0.15959488130443025*traceAdjYuYumq2*Quad(g3) - 0.15959488130443025*
      traceTYdAdjTYd*Quad(g3) + 0.26599146884071706*MassG*traceTYdAdjYd*Quad(g3
      ) - 0.15959488130443025*traceTYuAdjTYu*Quad(g3) + 0.26599146884071706*
      MassG*traceTYuAdjYu*Quad(g3) - 0.15959488130443025*traceYdAdjYdmd2*Quad(
      g3) - 0.15959488130443025*traceYuAdjYumu2*Quad(g3) - 0.49830357105237716*
      MassB*MassG*Quad(g3)*Sqr(g1) - 0.014186211671504911*tracemd2*Quad(g3)*Sqr
      (g1) - 0.028372423343009823*tracemq2*Quad(g3)*Sqr(g1) -
      0.014186211671504911*tracemu2*Quad(g3)*Sqr(g1) - 0.06355410590941335*
      MassB*MassWB*Quad(g1)*Sqr(g2) - 0.5296175492451111*MassG*MassWB*Quad(g3)*
      Sqr(g2) - 0.4851890569106953*MassB*MassG*Quad(g1)*Sqr(g3) -
      0.008511727002902947*mHd2*Quad(g1)*Sqr(g3) - 0.008511727002902947*mHu2*
      Quad(g1)*Sqr(g3) - 0.005674484668601964*tracemd2*Quad(g1)*Sqr(g3) -
      0.017023454005805894*traceme2*Quad(g1)*Sqr(g3) - 0.008511727002902947*
      traceml2*Quad(g1)*Sqr(g3) - 0.002837242334300982*tracemq2*Quad(g1)*Sqr(g3
      ) - 0.022697938674407857*tracemu2*Quad(g1)*Sqr(g3) + 1.*Power6(g1)*Sqr(
      MassB) - 0.11171641691310116*traceAdjYdYd*Quad(g1)*Sqr(MassB) -
      0.1436353931739872*traceAdjYeYe*Quad(g1)*Sqr(MassB) - 0.20747334569575931
      *traceAdjYuYu*Quad(g1)*Sqr(MassB) - 0.21989272395370968*Quad(g3)*Sqr(g1)*
      Sqr(MassB) - 0.09533115886412002*Quad(g1)*Sqr(g2)*Sqr(MassB) -
      0.727783585366043*Quad(g1)*Sqr(g3)*Sqr(MassB) + 28.704406504607828*Power6
      (g3)*Sqr(MassG) - 0.7979744065221512*traceAdjYdYd*Quad(g3)*Sqr(MassG) -
      0.7979744065221512*traceAdjYuYu*Quad(g3)*Sqr(MassG) - 0.6623380865495361*
      Quad(g3)*Sqr(g1)*Sqr(MassG) - 0.7944263238676669*Quad(g3)*Sqr(g2)*Sqr(
      MassG) - 0.19578002993938143*Quad(g1)*Sqr(g3)*Sqr(MassG) -
      0.01741351363730795*Quad(g1)*Sqr(g2)*Sqr(MassWB) - 0.14511261364423286*
      Quad(g3)*Sqr(g2)*Sqr(MassWB)) - 191.76*threeLoop*(-0.1251564455569462*
      traceAdjTYdTYdAdjYuYu - 0.1251564455569462*traceAdjTYuTYuAdjYdYd -
      0.7509386733416771*traceAdjTYuTYuAdjYuYu - 0.1251564455569462*
      traceAdjYdYdAdjYuYumq2 - 0.1251564455569462*traceAdjYuTYuAdjTYdYd -
      0.7509386733416771*traceAdjYuTYuAdjTYuYu - 0.0025031289111389237*mHd2*
      Quad(g1) + 0.16416353775552778*mHu2*Quad(g1) + 0.0625782227784731*mHd2*
      Quad(g2) + 0.5162703379224031*mHu2*Quad(g2) - 0.055625086914198305*mHu2*
      Quad(g3) + 0.07300792657488528*MassB*traceAdjTYuYu*Sqr(g1) +
      0.2816020025031289*MassWB*traceAdjTYuYu*Sqr(g2) + 0.2795160617438465*
      MassB*MassWB*Sqr(g1)*Sqr(g2) + 0.13975803087192326*mHu2*Sqr(g1)*Sqr(g2) -
      0.16687526074259493*MassG*traceAdjTYuYu*Sqr(g3) + 0.01112501738283966*
      MassB*MassG*Sqr(g1)*Sqr(g3) + 0.00556250869141983*mHu2*Sqr(g1)*Sqr(g3) +
      1.835627868168544*MassG*MassWB*Sqr(g2)*Sqr(g3) + 0.917813934084272*mHu2*
      Sqr(g2)*Sqr(g3) + 1.*Quad(g1)*Sqr(MassB) - 0.14601585314977056*
      traceAdjYuYu*Sqr(g1)*Sqr(MassB) + 0.2795160617438465*Sqr(g1)*Sqr(g2)*Sqr(
      MassB) + 0.01112501738283966*Sqr(g1)*Sqr(g3)*Sqr(MassB) -
      0.33375052148518985*Quad(g3)*Sqr(MassG) + 0.33375052148518985*
      traceAdjYuYu*Sqr(g3)*Sqr(MassG) + 0.01112501738283966*Sqr(g1)*Sqr(g3)*Sqr
      (MassG) + 1.835627868168544*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      2.471839799749687*Quad(g2)*Sqr(MassWB) + 0.2795160617438465*Sqr(g1)*Sqr(
      g2)*Sqr(MassWB) + 1.835627868168544*Sqr(g2)*Sqr(g3)*Sqr(MassWB))*(Yu*Yu.
      adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_2 = ((-12.*threeLoop*(-2.*mHd2*
      traceAdjYuYuAdjYdYd - 4.*mHu2*traceAdjYuYuAdjYdYd - 2.*
      traceAdjYuYuAdjYdYdmq2 - 17.999999999999996*mHu2*traceAdjYuYuAdjYuYu -
      12.*traceAdjYuYuAdjYuYumq2 + 6.*traceAdjYuYu*traceAdjYuYumq2 - 2.*
      traceTYdAdjTYuYuAdjYd + 6.*traceAdjYuYu*traceTYuAdjTYu + 6.*traceAdjTYuYu
      *traceTYuAdjYu - 2.*traceYdAdjYuYuAdjYdmd2 - 2.*traceYuAdjYdYdAdjYumu2 +
      6.*traceAdjYuYu*traceYuAdjYumu2 - 12.*traceYuAdjYuYuAdjYumu2 -
      0.02666666666666667*tracemd2*Quad(g1) - 0.08*traceme2*Quad(g1) - 0.04*
      traceml2*Quad(g1) - 0.013333333333333334*tracemq2*Quad(g1) -
      0.10666666666666667*tracemu2*Quad(g1) + 1.*traceml2*Quad(g2) + 3.*
      tracemq2*Quad(g2) - 2.3333333333333335*mHu2*traceAdjYuYu*Sqr(g1) -
      1.1666666666666667*traceAdjYuYumq2*Sqr(g1) - 1.1666666666666667*
      traceTYuAdjTYu*Sqr(g1) + 1.1666666666666667*MassB*traceTYuAdjYu*Sqr(g1) -
      1.1666666666666667*traceYuAdjYumu2*Sqr(g1) - 8.999999999999998*mHu2*
      traceAdjYuYu*Sqr(g2) - 4.499999999999999*traceAdjYuYumq2*Sqr(g2) -
      4.499999999999999*traceTYuAdjTYu*Sqr(g2) + 4.499999999999999*MassWB*
      traceTYuAdjYu*Sqr(g2) - 4.499999999999999*traceYuAdjYumu2*Sqr(g2) +
      5.333333333333333*mHu2*traceAdjYuYu*Sqr(g3) + 2.6666666666666665*
      traceAdjYuYumq2*Sqr(g3) + 2.6666666666666665*traceTYuAdjTYu*Sqr(g3) -
      2.6666666666666665*MassG*traceTYuAdjYu*Sqr(g3) + 2.6666666666666665*
      traceYuAdjYumu2*Sqr(g3) - 8.999999999999998*traceAdjYuYu*Sqr(g2)*Sqr(
      MassWB) + 8.999999999999998*mHu2*Sqr(traceAdjYuYu))*(Yu*Yu.adjoint()) +
      63.92*threeLoop*(0.37546933667083854*traceAdjYuTYuAdjYdYd +
      2.252816020025031*traceAdjYuTYuAdjYuYu + 0.37546933667083854*
      traceTYdAdjYuYuAdjYd - 1.1264080100125156*traceAdjYuYu*traceTYuAdjYu + 1.
      *MassB*Quad(g1) + 2.7221526908635796*MassWB*Quad(g2) - 0.3337505214851898
      *MassG*Quad(g3) - 0.2190237797246558*MassB*traceAdjYuYu*Sqr(g1) +
      0.2190237797246558*traceTYuAdjYu*Sqr(g1) - 0.8448060075093866*MassWB*
      traceAdjYuYu*Sqr(g2) + 0.8448060075093866*traceTYuAdjYu*Sqr(g2) +
      0.4192740926157697*MassB*Sqr(g1)*Sqr(g2) + 0.4192740926157697*MassWB*Sqr(
      g1)*Sqr(g2) + 0.5006257822277848*MassG*traceAdjYuYu*Sqr(g3) -
      0.5006257822277848*traceTYuAdjYu*Sqr(g3) + 0.016687526074259492*MassB*Sqr
      (g1)*Sqr(g3) + 0.016687526074259492*MassG*Sqr(g1)*Sqr(g3) +
      2.753441802252816*MassG*Sqr(g2)*Sqr(g3) + 2.753441802252816*MassWB*Sqr(g2
      )*Sqr(g3))*(Yu*(TYu).adjoint()) + 63.92*threeLoop*(0.37546933667083854*
      traceAdjTYuYuAdjYdYd - 1.1264080100125156*traceAdjTYuYu*traceAdjYuYu +
      0.37546933667083854*traceAdjYuYuAdjTYdYd + 2.252816020025031*
      traceAdjYuYuAdjTYuYu + 1.*MassB*Quad(g1) + 2.7221526908635796*MassWB*Quad
      (g2) - 0.3337505214851898*MassG*Quad(g3) + 0.2190237797246558*
      traceAdjTYuYu*Sqr(g1) - 0.2190237797246558*MassB*traceAdjYuYu*Sqr(g1) +
      0.8448060075093866*traceAdjTYuYu*Sqr(g2) - 0.8448060075093866*MassWB*
      traceAdjYuYu*Sqr(g2) + 0.4192740926157697*MassB*Sqr(g1)*Sqr(g2) +
      0.4192740926157697*MassWB*Sqr(g1)*Sqr(g2) - 0.5006257822277848*
      traceAdjTYuYu*Sqr(g3) + 0.5006257822277848*MassG*traceAdjYuYu*Sqr(g3) +
      0.016687526074259492*MassB*Sqr(g1)*Sqr(g3) + 0.016687526074259492*MassG*
      Sqr(g1)*Sqr(g3) + 2.753441802252816*MassG*Sqr(g2)*Sqr(g3) +
      2.753441802252816*MassWB*Sqr(g2)*Sqr(g3))*(TYu*Yu.adjoint()) - 31.96*
      threeLoop*(-0.7509386733416771*traceAdjYuYuAdjYdYd - 2.252816020025031*
      traceAdjYuYuAdjYuYu + 1.*Quad(g1) + 2.7221526908635796*Quad(g2) -
      0.3337505214851898*Quad(g3) - 0.4380475594493116*traceAdjYuYu*Sqr(g1) -
      1.6896120150187732*traceAdjYuYu*Sqr(g2) + 0.8385481852315394*Sqr(g1)*Sqr(
      g2) + 1.0012515644555695*traceAdjYuYu*Sqr(g3) + 0.033375052148518984*Sqr(
      g1)*Sqr(g3) + 5.506883604505632*Sqr(g2)*Sqr(g3) + 1.1264080100125156*Sqr(
      traceAdjYuYu))*(TYu*(TYu).adjoint()) - 15.98*threeLoop*(-
      0.7509386733416771*traceAdjYuYuAdjYdYd - 2.252816020025031*
      traceAdjYuYuAdjYuYu + 1.*Quad(g1) + 2.7221526908635796*Quad(g2) -
      0.3337505214851898*Quad(g3) - 0.4380475594493116*traceAdjYuYu*Sqr(g1) -
      1.6896120150187732*traceAdjYuYu*Sqr(g2) + 0.8385481852315394*Sqr(g1)*Sqr(
      g2) + 1.0012515644555695*traceAdjYuYu*Sqr(g3) + 0.033375052148518984*Sqr(
      g1)*Sqr(g3) + 5.506883604505632*Sqr(g2)*Sqr(g3) + 1.1264080100125156*Sqr(
      traceAdjYuYu))*(mu2*Yu*Yu.adjoint()) - 31.96*threeLoop*Quad(g1)*(Yu*mq2*
      Yu.adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_3 = ((-26.800000000000004*threeLoop
      *(-0.8955223880597013*traceAdjYuYuAdjYdYd - 2.6865671641791042*
      traceAdjYuYuAdjYuYu + 3.2462686567164174*Quad(g2) - 0.3980099502487561*
      Quad(g3) - 0.5223880597014925*traceAdjYuYu*Sqr(g1) - 2.0149253731343277*
      traceAdjYuYu*Sqr(g2) + 1.*Sqr(g1)*Sqr(g2) + 1.1940298507462686*
      traceAdjYuYu*Sqr(g3) + 0.039800995024875614*Sqr(g1)*Sqr(g3) +
      6.567164179104476*Sqr(g2)*Sqr(g3) + 1.3432835820895521*Sqr(traceAdjYuYu))
      *(Yu*mq2*Yu.adjoint()) - 39.52*threeLoop*(0.16666666666666666*mHu2*Quad(
      g1) + 0.4554655870445344*mHu2*Quad(g2) + 9.176788124156545*mHu2*Quad(g3)
      + 0.42510121457489874*MassB*traceAdjTYuYu*Sqr(g1) - 0.8502024291497975*
      mHu2*traceAdjYuYu*Sqr(g1) - 0.42510121457489874*traceAdjYuYumq2*Sqr(g1) -
      0.42510121457489874*traceTYuAdjTYu*Sqr(g1) + 0.42510121457489874*MassB*
      traceTYuAdjYu*Sqr(g1) - 0.42510121457489874*traceYuAdjYumu2*Sqr(g1) -
      2.732793522267206*MassWB*traceAdjTYuYu*Sqr(g2) + 5.465587044534412*mHu2*
      traceAdjYuYu*Sqr(g2) + 2.732793522267206*traceAdjYuYumq2*Sqr(g2) +
      2.732793522267206*traceTYuAdjTYu*Sqr(g2) - 2.732793522267206*MassWB*
      traceTYuAdjYu*Sqr(g2) + 2.732793522267206*traceYuAdjYumu2*Sqr(g2) -
      1.5789473684210522*MassB*MassWB*Sqr(g1)*Sqr(g2) - 0.7894736842105261*mHu2
      *Sqr(g1)*Sqr(g2) + 4.8582995951417*MassG*traceAdjTYuYu*Sqr(g3) -
      9.7165991902834*mHu2*traceAdjYuYu*Sqr(g3) - 4.8582995951417*
      traceAdjYuYumq2*Sqr(g3) - 4.8582995951417*traceTYuAdjTYu*Sqr(g3) +
      4.8582995951417*MassG*traceTYuAdjYu*Sqr(g3) - 4.8582995951417*
      traceYuAdjYumu2*Sqr(g3) + 1.5114709851551955*MassB*MassG*Sqr(g1)*Sqr(g3)
      + 0.7557354925775978*mHu2*Sqr(g1)*Sqr(g3) - 9.7165991902834*MassG*MassWB*
      Sqr(g2)*Sqr(g3) - 4.8582995951417*mHu2*Sqr(g2)*Sqr(g3) + 1.*Quad(g1)*Sqr(
      MassB) - 0.8502024291497975*traceAdjYuYu*Sqr(g1)*Sqr(MassB) -
      1.5789473684210522*Sqr(g1)*Sqr(g2)*Sqr(MassB) + 1.5114709851551955*Sqr(g1
      )*Sqr(g3)*Sqr(MassB) + 55.06072874493927*Quad(g3)*Sqr(MassG) -
      9.7165991902834*traceAdjYuYu*Sqr(g3)*Sqr(MassG) + 1.5114709851551955*Sqr(
      g1)*Sqr(g3)*Sqr(MassG) - 9.7165991902834*Sqr(g2)*Sqr(g3)*Sqr(MassG) +
      2.732793522267206*Quad(g2)*Sqr(MassWB) + 5.465587044534412*traceAdjYuYu*
      Sqr(g2)*Sqr(MassWB) - 1.5789473684210522*Sqr(g1)*Sqr(g2)*Sqr(MassWB) -
      9.7165991902834*Sqr(g2)*Sqr(g3)*Sqr(MassWB))*(Yu*Yu.adjoint()*
      1.2020569031595942) - 15.98*threeLoop*(-0.7509386733416771*
      traceAdjYuYuAdjYdYd - 2.252816020025031*traceAdjYuYuAdjYuYu + 1.*Quad(g1)
      + 2.7221526908635796*Quad(g2) - 0.33375052148518974*Quad(g3) -
      0.4380475594493116*traceAdjYuYu*Sqr(g1) - 1.6896120150187732*traceAdjYuYu
      *Sqr(g2) + 0.8385481852315395*Sqr(g1)*Sqr(g2) + 1.0012515644555695*
      traceAdjYuYu*Sqr(g3) + 0.033375052148518984*Sqr(g1)*Sqr(g3) +
      5.5068836045056315*Sqr(g2)*Sqr(g3) + 1.1264080100125156*Sqr(traceAdjYuYu)
      )*(Yu*Yu.adjoint()*mu2) + 13.173333333333334*threeLoop*(1.*MassB*Quad(g1)
      + 2.7327935222672064*MassWB*Quad(g2) + 55.060728744939276*MassG*Quad(g3)
      - 1.2753036437246963*MassB*traceAdjYuYu*Sqr(g1) + 1.2753036437246963*
      traceTYuAdjYu*Sqr(g1) + 8.198380566801617*MassWB*traceAdjYuYu*Sqr(g2) -
      8.198380566801617*traceTYuAdjYu*Sqr(g2) - 2.3684210526315788*MassB*Sqr(g1
      )*Sqr(g2) - 2.3684210526315788*MassWB*Sqr(g1)*Sqr(g2) - 14.5748987854251*
      MassG*traceAdjYuYu*Sqr(g3) + 14.5748987854251*traceTYuAdjYu*Sqr(g3) +
      2.2672064777327936*MassB*Sqr(g1)*Sqr(g3) + 2.2672064777327936*MassG*Sqr(
      g1)*Sqr(g3) - 14.5748987854251*MassG*Sqr(g2)*Sqr(g3) - 14.5748987854251*
      MassWB*Sqr(g2)*Sqr(g3))*(Yu*(TYu).adjoint()*1.2020569031595942) +
      13.173333333333334*threeLoop*(1.*MassB*Quad(g1) + 2.7327935222672064*
      MassWB*Quad(g2) + 55.060728744939276*MassG*Quad(g3) + 1.2753036437246963*
      traceAdjTYuYu*Sqr(g1) - 1.2753036437246963*MassB*traceAdjYuYu*Sqr(g1) -
      8.198380566801617*traceAdjTYuYu*Sqr(g2) + 8.198380566801617*MassWB*
      traceAdjYuYu*Sqr(g2) - 2.3684210526315788*MassB*Sqr(g1)*Sqr(g2) -
      2.3684210526315788*MassWB*Sqr(g1)*Sqr(g2) + 14.5748987854251*
      traceAdjTYuYu*Sqr(g3) - 14.5748987854251*MassG*traceAdjYuYu*Sqr(g3) +
      2.2672064777327936*MassB*Sqr(g1)*Sqr(g3) + 2.2672064777327936*MassG*Sqr(
      g1)*Sqr(g3) - 14.5748987854251*MassG*Sqr(g2)*Sqr(g3) - 14.5748987854251*
      MassWB*Sqr(g2)*Sqr(g3))*(TYu*Yu.adjoint()*1.2020569031595942) -
      6.586666666666667*threeLoop*(1.*Quad(g1) + 2.7327935222672064*Quad(g2) +
      55.060728744939276*Quad(g3) - 2.5506072874493926*traceAdjYuYu*Sqr(g1) +
      16.396761133603235*traceAdjYuYu*Sqr(g2) - 4.7368421052631575*Sqr(g1)*Sqr(
      g2) + 4.534412955465587*Sqr(g1)*Sqr(g3) - 29.1497975708502*Sqr(g2)*Sqr(g3
      ))*(TYu*(TYu).adjoint()*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_4 = ((192.*threeLoop*traceAdjYuYu*
      Sqr(g3)*(TYu*(TYu).adjoint()*1.2020569031595942) - 3.2933333333333334*
      threeLoop*(1.*Quad(g1) + 2.7327935222672064*Quad(g2) + 55.060728744939276
      *Quad(g3) - 2.5506072874493926*traceAdjYuYu*Sqr(g1) + 16.39676113360323*
      traceAdjYuYu*Sqr(g2) - 4.736842105263158*Sqr(g1)*Sqr(g2) -
      29.1497975708502*traceAdjYuYu*Sqr(g3) + 4.534412955465587*Sqr(g1)*Sqr(g3)
      - 29.1497975708502*Sqr(g2)*Sqr(g3))*(mu2*Yu*Yu.adjoint()*
      1.2020569031595942) - 6.586666666666667*threeLoop*(1.*Quad(g1) +
      2.7327935222672064*Quad(g2) + 55.060728744939276*Quad(g3) -
      2.5506072874493926*traceAdjYuYu*Sqr(g1) + 16.39676113360323*traceAdjYuYu*
      Sqr(g2) - 4.736842105263158*Sqr(g1)*Sqr(g2) - 29.1497975708502*
      traceAdjYuYu*Sqr(g3) + 4.534412955465587*Sqr(g1)*Sqr(g3) -
      29.1497975708502*Sqr(g2)*Sqr(g3))*(Yu*mq2*Yu.adjoint()*1.2020569031595942
      ) + 5.066666666666666*threeLoop*(9.473684210526317*mHd2*traceAdjYdYd +
      4.736842105263158*mHu2*traceAdjYdYd + 4.736842105263158*traceAdjYdYdmq2 +
      3.1578947368421053*mHd2*traceAdjYeYe + 1.5789473684210527*mHu2*
      traceAdjYeYe + 1.5789473684210527*traceAdjYeYeml2 - 2.368421052631579*
      mHd2*traceAdjYuYu - 4.736842105263158*mHu2*traceAdjYuYu -
      2.368421052631579*traceAdjYuYumq2 + 4.736842105263158*traceTYdAdjTYd +
      1.5789473684210527*traceTYeAdjTYe - 2.368421052631579*traceTYuAdjTYu +
      4.736842105263158*traceYdAdjYdmd2 + 1.5789473684210527*traceYeAdjYeme2 -
      2.368421052631579*traceYuAdjYumu2 + 0.5*mHd2*Sqr(g1) + 0.5*mHu2*Sqr(g1) +
      3.5526315789473686*mHd2*Sqr(g2) + 3.5526315789473686*mHu2*Sqr(g2) +
      8.421052631578947*mHd2*Sqr(g3) + 8.421052631578947*mHu2*Sqr(g3) + 1.*Sqr(
      g1)*Sqr(MassB) + 16.842105263157894*Sqr(g3)*Sqr(MassG) +
      7.105263157894737*Sqr(g2)*Sqr(MassWB))*(Yu*Yd.adjoint()*Yd*Yu.adjoint())
      - 2.533333333333333*threeLoop*(-9.473684210526317*traceTYdAdjYd -
      3.1578947368421053*traceTYeAdjYe + 4.736842105263158*traceTYuAdjYu + 1.*
      MassB*Sqr(g1) + 7.105263157894737*MassWB*Sqr(g2) + 16.842105263157894*
      MassG*Sqr(g3))*(Yu*Yd.adjoint()*Yd*(TYu).adjoint()) - 2.533333333333333*
      threeLoop*(-9.473684210526317*traceAdjTYdYd - 3.1578947368421053*
      traceAdjTYeYe + 4.736842105263158*traceAdjTYuYu + 1.*MassB*Sqr(g1) +
      7.105263157894737*MassWB*Sqr(g2) + 16.842105263157894*MassG*Sqr(g3))*(Yu*
      Yd.adjoint()*TYd*Yu.adjoint()) + 2.533333333333333*threeLoop*(
      9.473684210526317*traceAdjYdYd + 3.1578947368421053*traceAdjYeYe -
      4.736842105263158*traceAdjYuYu + 1.*Sqr(g1) + 7.105263157894737*Sqr(g2) +
      16.842105263157894*Sqr(g3))*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()) -
      3.2933333333333334*threeLoop*(1.*Quad(g1) + 2.7327935222672064*Quad(g2) +
      55.060728744939276*Quad(g3) - 2.5506072874493926*traceAdjYuYu*Sqr(g1) +
      16.39676113360323*traceAdjYuYu*Sqr(g2) - 4.736842105263158*Sqr(g1)*Sqr(g2
      ) - 29.1497975708502*traceAdjYuYu*Sqr(g3) + 4.534412955465587*Sqr(g1)*Sqr
      (g3) - 29.1497975708502*Sqr(g2)*Sqr(g3))*(Yu*Yu.adjoint()*mu2*
      1.2020569031595942) - 1.3333333333333333*threeLoop*(-27.*mHu2*
      traceAdjYuYu - 9.*traceAdjYuYumq2 - 9.*traceTYuAdjTYu - 9.*
      traceYuAdjYumu2 + 1.*mHu2*Sqr(g1) - 27.*mHu2*Sqr(g2) - 64.*mHu2*Sqr(g3) +
      1.*Sqr(g1)*Sqr(MassB) - 64.*Sqr(g3)*Sqr(MassG) - 27.*Sqr(g2)*Sqr(MassWB))
      *(Yu*Yu.adjoint()*Yu*Yu.adjoint()) + 0.6666666666666666*threeLoop*(18.*
      traceTYuAdjYu + 1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr(g3)
      )*(Yu*Yu.adjoint()*Yu*(TYu).adjoint()) + 0.6666666666666666*threeLoop*(
      18.*traceAdjTYuYu + 1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr
      (g3))*(Yu*Yu.adjoint()*TYu*Yu.adjoint()) - 0.6666666666666666*threeLoop*(
      -18.*traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yu*Yu.
      adjoint()*TYu*(TYu).adjoint()) - 2.533333333333333*threeLoop*(-
      9.473684210526317*traceTYdAdjYd - 3.1578947368421053*traceTYeAdjYe +
      4.736842105263158*traceTYuAdjYu + 1.*MassB*Sqr(g1) + 7.105263157894737*
      MassWB*Sqr(g2) + 16.842105263157894*MassG*Sqr(g3))*(Yu*(TYd).adjoint()*Yd
      *Yu.adjoint()) + 2.533333333333333*(1.*threeLoop*Sqr(g1) +
      7.105263157894737*threeLoop*Sqr(g2))*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()
      ))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_5 = ((42.666666666666664*threeLoop*
      (0.5625*traceAdjYdYd + 0.1875*traceAdjYeYe - 0.28125*traceAdjYuYu + 1.*
      Sqr(g3))*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()) + 0.6666666666666666*
      threeLoop*(18.*traceTYuAdjYu + 1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) -
      64.*MassG*Sqr(g3))*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()) -
      0.6666666666666666*threeLoop*(-18.*traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2
      ) - 64.*Sqr(g3))*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()) -
      2.533333333333333*threeLoop*(-9.473684210526317*traceAdjTYdYd -
      3.1578947368421053*traceAdjTYeYe + 4.736842105263158*traceAdjTYuYu + 1.*
      MassB*Sqr(g1) + 7.105263157894737*MassWB*Sqr(g2) + 16.842105263157894*
      MassG*Sqr(g3))*(TYu*Yd.adjoint()*Yd*Yu.adjoint()) + 2.533333333333333*
      threeLoop*(9.473684210526317*traceAdjYdYd + 3.1578947368421053*
      traceAdjYeYe - 4.736842105263158*traceAdjYuYu + 1.*Sqr(g1) +
      7.105263157894737*Sqr(g2) + 16.842105263157894*Sqr(g3))*(TYu*Yd.adjoint()
      *Yd*(TYu).adjoint()) + 0.6666666666666666*threeLoop*(18.*traceAdjTYuYu +
      1.*MassB*Sqr(g1) - 27.*MassWB*Sqr(g2) - 64.*MassG*Sqr(g3))*(TYu*Yu.
      adjoint()*Yu*Yu.adjoint()) - 0.6666666666666666*threeLoop*(-18.*
      traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(TYu*Yu.adjoint()*
      Yu*(TYu).adjoint()) + 2.533333333333333*threeLoop*(9.473684210526317*
      traceAdjYdYd + 3.1578947368421053*traceAdjYeYe - 4.736842105263158*
      traceAdjYuYu + 1.*Sqr(g1) + 7.105263157894737*Sqr(g2) +
      16.842105263157894*Sqr(g3))*(TYu*(TYd).adjoint()*Yd*Yu.adjoint()) -
      0.6666666666666666*threeLoop*(-18.*traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2
      ) - 64.*Sqr(g3))*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()) +
      1.2666666666666666*threeLoop*(9.473684210526317*traceAdjYdYd +
      3.1578947368421053*traceAdjYeYe - 4.736842105263158*traceAdjYuYu + 1.*Sqr
      (g1) + 7.105263157894737*Sqr(g2) + 16.842105263157894*Sqr(g3))*(mu2*Yu*Yd
      .adjoint()*Yd*Yu.adjoint()) - 0.3333333333333333*threeLoop*(-18.*
      traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(mu2*Yu*Yu.adjoint
      ()*Yu*Yu.adjoint()) + 2.533333333333333*threeLoop*(9.473684210526317*
      traceAdjYdYd + 3.1578947368421053*traceAdjYeYe - 4.736842105263158*
      traceAdjYuYu + 1.*Sqr(g1) + 7.105263157894737*Sqr(g2) +
      16.842105263157894*Sqr(g3))*(Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()) -
      0.6666666666666666*threeLoop*(-18.*traceAdjYuYu + 1.*Sqr(g1) - 27.*Sqr(g2
      ) - 64.*Sqr(g3))*(Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()) +
      2.533333333333333*threeLoop*(9.473684210526317*traceAdjYdYd +
      3.1578947368421053*traceAdjYeYe - 4.736842105263158*traceAdjYuYu + 1.*Sqr
      (g1) + 7.105263157894737*Sqr(g2) + 16.842105263157894*Sqr(g3))*(Yu*Yd.
      adjoint()*md2*Yd*Yu.adjoint()) + 2.533333333333333*threeLoop*(
      9.473684210526317*traceAdjYdYd + 3.1578947368421053*traceAdjYeYe -
      4.736842105263158*traceAdjYuYu + 1.*Sqr(g1) + 7.105263157894737*Sqr(g2) +
      16.842105263157894*Sqr(g3))*(Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()) +
      14.399999999999999*(0.5*mHd2*threeLoop*Sqr(g1) + 0.5*mHu2*threeLoop*Sqr(
      g1) - 2.5000000000000004*mHd2*threeLoop*Sqr(g2) - 2.5000000000000004*mHu2
      *threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(MassB) - 5.000000000000001*
      threeLoop*Sqr(g2)*Sqr(MassWB))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*
      1.2020569031595942) + 1.2666666666666666*threeLoop*(9.473684210526317*
      traceAdjYdYd + 3.1578947368421053*traceAdjYeYe - 4.736842105263158*
      traceAdjYuYu + 1.*Sqr(g1) + 7.105263157894737*Sqr(g2) +
      16.842105263157894*Sqr(g3))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*mu2) -
      7.199999999999999*(1.*MassB*threeLoop*Sqr(g1) - 5.000000000000001*MassWB*
      threeLoop*Sqr(g2))*(Yu*Yd.adjoint()*Yd*(TYu).adjoint()*1.2020569031595942
      ) - 7.199999999999999*(1.*MassB*threeLoop*Sqr(g1) - 5.000000000000001*
      MassWB*threeLoop*Sqr(g2))*(Yu*Yd.adjoint()*TYd*Yu.adjoint()*
      1.2020569031595942) + 7.199999999999999*(1.*threeLoop*Sqr(g1) -
      5.000000000000001*threeLoop*Sqr(g2))*(Yu*Yd.adjoint()*TYd*(TYu).adjoint()
      *1.2020569031595942) - 0.6666666666666666*threeLoop*(-18.*traceAdjYuYu +
      1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yu*Yu.adjoint()*mu2*Yu*Yu.
      adjoint()) - 0.6666666666666666*threeLoop*(-18.*traceAdjYuYu + 1.*Sqr(g1)
      - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()))*
      UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_6 = ((24.*(1.*mHu2*threeLoop*Sqr(g1
      ) - 3.*mHu2*threeLoop*Sqr(g2) + 1.*threeLoop*Sqr(g1)*Sqr(MassB) - 3.*
      threeLoop*Sqr(g2)*Sqr(MassWB))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*
      1.2020569031595942) - 0.3333333333333333*threeLoop*(-18.*traceAdjYuYu +
      1.*Sqr(g1) - 27.*Sqr(g2) - 64.*Sqr(g3))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*
      mu2) - 12.*(1.*MassB*threeLoop*Sqr(g1) - 3.*MassWB*threeLoop*Sqr(g2))*(Yu
      *Yu.adjoint()*Yu*(TYu).adjoint()*1.2020569031595942) - 12.*(1.*MassB*
      threeLoop*Sqr(g1) - 3.*MassWB*threeLoop*Sqr(g2))*(Yu*Yu.adjoint()*TYu*Yu.
      adjoint()*1.2020569031595942) + 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*
      Sqr(g2))*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()*1.2020569031595942) -
      7.199999999999999*(1.*MassB*threeLoop*Sqr(g1) - 5.000000000000001*MassWB*
      threeLoop*Sqr(g2))*(Yu*(TYd).adjoint()*Yd*Yu.adjoint()*1.2020569031595942
      ) + 7.199999999999999*(1.*threeLoop*Sqr(g1) - 5.000000000000001*threeLoop
      *Sqr(g2))*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()*1.2020569031595942) - 12.*
      (1.*MassB*threeLoop*Sqr(g1) - 3.*MassWB*threeLoop*Sqr(g2))*(Yu*(TYu).
      adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 12.*(1.*threeLoop*Sqr(g1)
      - 3.*threeLoop*Sqr(g2))*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()*
      1.2020569031595942) - 7.199999999999999*(1.*MassB*threeLoop*Sqr(g1) -
      5.000000000000001*MassWB*threeLoop*Sqr(g2))*(TYu*Yd.adjoint()*Yd*Yu.
      adjoint()*1.2020569031595942) + 7.199999999999999*(1.*threeLoop*Sqr(g1) -
      5.000000000000001*threeLoop*Sqr(g2))*(TYu*Yd.adjoint()*Yd*(TYu).adjoint()
      *1.2020569031595942) - 12.*(1.*MassB*threeLoop*Sqr(g1) - 3.*MassWB*
      threeLoop*Sqr(g2))*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942)
      + 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(TYu*Yu.adjoint()*Yu*
      (TYu).adjoint()*1.2020569031595942) + 7.199999999999999*(1.*threeLoop*Sqr
      (g1) - 5.000000000000001*threeLoop*Sqr(g2))*(TYu*(TYd).adjoint()*Yd*Yu.
      adjoint()*1.2020569031595942) + 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*
      Sqr(g2))*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()*1.2020569031595942) +
      3.5999999999999996*(1.*threeLoop*Sqr(g1) - 5.000000000000001*threeLoop*
      Sqr(g2))*(mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()*1.2020569031595942) + 6.*(
      1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(mu2*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*1.2020569031595942) + 7.199999999999999*(1.*threeLoop*Sqr(g1) -
      5.000000000000001*threeLoop*Sqr(g2))*(Yu*mq2*Yd.adjoint()*Yd*Yu.adjoint()
      *1.2020569031595942) + 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*
      (Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) +
      7.199999999999999*(1.*threeLoop*Sqr(g1) - 5.000000000000001*threeLoop*Sqr
      (g2))*(Yu*Yd.adjoint()*md2*Yd*Yu.adjoint()*1.2020569031595942) +
      7.199999999999999*(1.*threeLoop*Sqr(g1) - 5.000000000000001*threeLoop*Sqr
      (g2))*(Yu*Yd.adjoint()*Yd*mq2*Yu.adjoint()*1.2020569031595942) + 24.*(1.*
      mHd2*threeLoop + 0.5*mHu2*threeLoop)*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*
      Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*TYd*(TYu).
      adjoint()) + 3.5999999999999996*(1.*threeLoop*Sqr(g1) - 5.000000000000001
      *threeLoop*Sqr(g2))*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*mu2*
      1.2020569031595942) - 4.*(1.*mHd2*threeLoop + 2.*mHu2*threeLoop)*(Yu*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint(
      )*Yd*Yu.adjoint()*TYu*(TYu).adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*
      Yd*(TYd).adjoint()*TYd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*Yd*(
      TYu).adjoint()*TYu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*TYd*Yd.
      adjoint()*Yd*(TYu).adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*TYd*Yu.
      adjoint()*Yu*(TYu).adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*TYd*(TYd).
      adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*TYd*(TYu).
      adjoint()*Yu*Yu.adjoint()) + 12.*(1.*threeLoop*Sqr(g1) - 3.*threeLoop*Sqr
      (g2))*(Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()*1.2020569031595942) + 12.*(1.*
      threeLoop*Sqr(g1) - 3.*threeLoop*Sqr(g2))*(Yu*Yu.adjoint()*Yu*mq2*Yu.
      adjoint()*1.2020569031595942) - 4.*(1.*mHd2*threeLoop + 2.*mHu2*threeLoop
      )*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yu
      .adjoint()*Yu*Yd.adjoint()*TYd*(TYu).adjoint()) + 6.*(1.*threeLoop*Sqr(g1
      ) - 3.*threeLoop*Sqr(g2))*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2*
      1.2020569031595942) + 36.*mHu2*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()
      *Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*TYu*(
      TYu).adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*Yu*(TYd).adjoint()*TYd*Yu
      .adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*(TYu).adjoint()*TYu*Yu.
      adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*TYu*Yd.adjoint()*Yd*(TYu).
      adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*(TYu).
      adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*TYu*(TYd).adjoint()*Yd*Yu.
      adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()*Yu*Yu.
      adjoint()) + 12.*threeLoop*(Yu*(TYd).adjoint()*Yd*Yd.adjoint()*TYd*Yu.
      adjoint()) - 4.*threeLoop*(Yu*(TYd).adjoint()*Yd*Yu.adjoint()*TYu*Yu.
      adjoint()) + 12.*threeLoop*(Yu*(TYd).adjoint()*TYd*Yd.adjoint()*Yd*Yu.
      adjoint()) - 4.*threeLoop*(Yu*(TYd).adjoint()*TYd*Yu.adjoint()*Yu*Yu.
      adjoint()) - 4.*threeLoop*(Yu*(TYu).adjoint()*Yu*Yd.adjoint()*TYd*Yu.
      adjoint()) + 12.*threeLoop*(Yu*(TYu).adjoint()*Yu*Yu.adjoint()*TYu*Yu.
      adjoint()) - 4.*threeLoop*(Yu*(TYu).adjoint()*TYu*Yd.adjoint()*Yd*Yu.
      adjoint()) + 12.*threeLoop*(Yu*(TYu).adjoint()*TYu*Yu.adjoint()*Yu*Yu.
      adjoint()) + 12.*threeLoop*(TYu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*(TYu).
      adjoint()) - 4.*threeLoop*(TYu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*(TYu).
      adjoint()) + 12.*threeLoop*(TYu*Yd.adjoint()*Yd*(TYd).adjoint()*Yd*Yu.
      adjoint()) - 4.*threeLoop*(TYu*Yd.adjoint()*Yd*(TYu).adjoint()*Yu*Yu.
      adjoint()) - 4.*threeLoop*(TYu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*(TYu).
      adjoint()) + 12.*threeLoop*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYu).
      adjoint()) - 4.*threeLoop*(TYu*Yu.adjoint()*Yu*(TYd).adjoint()*Yd*Yu.
      adjoint()) + 12.*threeLoop*(TYu*Yu.adjoint()*Yu*(TYu).adjoint()*Yu*Yu.
      adjoint()) + 12.*threeLoop*(TYu*(TYd).adjoint()*Yd*Yd.adjoint()*Yd*Yu.
      adjoint()) - 4.*threeLoop*(TYu*(TYd).adjoint()*Yd*Yu.adjoint()*Yu*Yu.
      adjoint()) - 4.*threeLoop*(TYu*(TYu).adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()) + 12.*threeLoop*(TYu*(TYu).adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()) + 6.*threeLoop*(mu2*Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd*Yu.
      adjoint()) - 2.*threeLoop*(mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu*Yu.
      adjoint()) - 2.*threeLoop*(mu2*Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_mu2_7 = ((6.*threeLoop*(mu2*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*mq2*Yd.
      adjoint()*Yd*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*mq2*Yd.
      adjoint()*Yd*Yu.adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*mq2*Yu.
      adjoint()*Yu*Yd.adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*mq2*Yu.
      adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint
      ()*md2*Yd*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*
      md2*Yd*Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*Yd*
      mq2*Yd.adjoint()*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*Yd*mq2*
      Yu.adjoint()*Yu*Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*md2*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*mq2*Yu.adjoint()) + 6.*threeLoop*(Yu*Yd.adjoint()*Yd*Yd.
      adjoint()*Yd*Yu.adjoint()*mu2) - 4.*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*mu2*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu*mq2*Yu.adjoint()) - 2.*threeLoop*(Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*Yu*Yu.adjoint()*mu2) - 4.*threeLoop*(Yu*Yu.adjoint()*mu2*Yu*Yd.
      adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*mu2*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*Yu*mq2*Yd.
      adjoint()*Yd*Yu.adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*mq2*Yu.
      adjoint()*Yu*Yu.adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint(
      )*md2*Yd*Yu.adjoint()) - 4.*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd
      *mq2*Yu.adjoint()) - 2.*threeLoop*(Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd*Yu.
      adjoint()*mu2) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yu
      .adjoint()) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yu.
      adjoint()) + 72.*mHu2*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*1.2020569031595942) + 6.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*Yu*Yu.adjoint()*mu2) + 24.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.
      adjoint()*TYu*(TYu).adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*Yu.
      adjoint()*Yu*(TYu).adjoint()*TYu*Yu.adjoint()*1.2020569031595942) + 24.*
      threeLoop*(Yu*Yu.adjoint()*TYu*Yu.adjoint()*Yu*(TYu).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*TYu*(TYu).adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*(TYu).adjoint()*
      Yu*Yu.adjoint()*TYu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*
      (TYu).adjoint()*TYu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) +
      24.*threeLoop*(TYu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*(TYu).adjoint()*
      1.2020569031595942) + 24.*threeLoop*(TYu*Yu.adjoint()*Yu*(TYu).adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(TYu*(TYu).adjoint()*
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 12.*threeLoop*(mu2*
      Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 24.
      *threeLoop*(Yu*mq2*Yu.adjoint()*Yu*Yu.adjoint()*Yu*Yu.adjoint()*
      1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()*
      Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*Yu.adjoint()*Yu*
      mq2*Yu.adjoint()*Yu*Yu.adjoint()*1.2020569031595942) + 24.*threeLoop*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*mu2*Yu*Yu.adjoint()*1.2020569031595942) +
      24.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*mq2*Yu.adjoint()*
      1.2020569031595942) + 12.*threeLoop*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*mu2*1.2020569031595942))*UNITMATRIX(3)).real();

   beta_mu2 = beta_mu2_1 + beta_mu2_2 + beta_mu2_3 + beta_mu2_4 + beta_mu2_5 +
      beta_mu2_6 + beta_mu2_7;


   return beta_mu2;
}

/**
 * Calculates the 4-loop beta function of mu2.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mu2_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = ZEROMATRIX(3,3);


   return beta_mu2;
}

/**
 * Calculates the 5-loop beta function of mu2.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_mu2_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_mu2;

   beta_mu2 = ZEROMATRIX(3,3);


   return beta_mu2;
}

} // namespace flexiblesusy
