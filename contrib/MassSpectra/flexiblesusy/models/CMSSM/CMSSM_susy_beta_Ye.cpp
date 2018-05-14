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

// File generated at Thu 10 May 2018 15:11:07

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Ye.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Ye_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (oneOver16PiSqr*(Ye*(3*traceYdAdjYd + traceYeAdjYe - 1.8*Sqr
      (g1) - 3*Sqr(g2)) + 3*(Ye*Ye.adjoint()*Ye))).real();


   return beta_Ye;
}

/**
 * Calculates the 2-loop beta function of Ye.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Ye_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (twoLoop*(0.1*Ye*(-30*(3*traceYdAdjYdYdAdjYd +
      traceYdAdjYuYuAdjYd + traceYeAdjYeYeAdjYe) + 135*Quad(g1) + 75*Quad(g2) +
      2*Sqr(g1)*(-2*traceYdAdjYd + 6*traceYeAdjYe + 9*Sqr(g2)) + 160*
      traceYdAdjYd*Sqr(g3)) + (-3*(3*traceYdAdjYd + traceYeAdjYe) + 6*Sqr(g2))*
      (Ye*Ye.adjoint()*Ye) - 4*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye))).real();


   return beta_Ye;
}

/**
 * Calculates the 3-loop beta function of Ye.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Ye_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYdYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYd;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (threeLoop*(0.0006666666666666666*Ye*(149958*Power6(g1) + 5*
      Quad(g1)*(-7525*traceAdjYdYd - 13095*traceAdjYeYe - 7020*traceAdjYuYu +
      5022*Sqr(g2) + 23760*Sqr(g3)) + 50*Sqr(g1)*(90*traceAdjYdYdAdjYdYd + 270*
      traceAdjYeYeAdjYeYe - 72*traceAdjYuYuAdjYdYd + 135*Quad(g2) - 9*(
      traceAdjYdYd + 27*traceAdjYeYe)*Sqr(g2) - 568*traceAdjYdYd*Sqr(g3)) + 125
      *(12*(3*traceAdjYdYdAdjYdYdAdjYdYd + 18*traceAdjYdYdAdjYdYd*traceAdjYeYe
      + 6*traceAdjYeYe*traceAdjYeYeAdjYeYe + 18*traceAdjYdYd*(3*
      traceAdjYdYdAdjYdYd + traceAdjYeYeAdjYeYe) + traceAdjYeYeAdjYeYeAdjYeYe +
      18*traceAdjYuYu*traceAdjYuYuAdjYdYd + 9*traceAdjYuYuAdjYuYuAdjYdYd) +
      2070*Power6(g2) - 640*traceAdjYdYd*Quad(g3) + 288*(3*traceAdjYdYdAdjYdYd
      + traceAdjYuYuAdjYdYd)*Sqr(g3) + 45*Quad(g2)*(-21*traceAdjYdYd - 7*
      traceAdjYeYe - 12*traceAdjYuYu + 48*Sqr(g3)) - 36*Sqr(g2)*(-3*
      traceAdjYdYdAdjYdYd - traceAdjYeYeAdjYeYe - 6*traceAdjYuYuAdjYdYd + 44*
      traceAdjYdYd*Sqr(g3)))) + 0.004*(-10746*Power6(g1) - 5*Quad(g1)*(77*
      traceAdjYdYd - 81*traceAdjYeYe + 1458*Sqr(g2) + 4752*Sqr(g3)) - 50*Sqr(g1
      )*(-6*(9*traceAdjYdYdAdjYdYd - 9*traceAdjYeYeAdjYeYe + 7*
      traceAdjYuYuAdjYdYd) + 81*Quad(g2) + 9*(5*traceAdjYdYd - 9*traceAdjYeYe)*
      Sqr(g2) - 112*traceAdjYdYd*Sqr(g3)) + 125*(630*Power6(g2) - 9*Quad(g2)*(7
      *(3*traceAdjYdYd + traceAdjYeYe) + 48*Sqr(g3)) + 36*Sqr(g2)*(3*
      traceAdjYdYdAdjYdYd + traceAdjYeYeAdjYeYe + 8*traceAdjYdYd*Sqr(g3)) - 4*(
      -3*(3*traceAdjYdYdAdjYdYdAdjYdYd + traceAdjYeYeAdjYeYeAdjYeYe) + 8*
      traceAdjYdYd*Quad(g3) + 24*(3*traceAdjYdYdAdjYdYd + traceAdjYuYuAdjYdYd)*
      Sqr(g3))))*(Ye*1.2020569031595942) - 0.03*(1917*Quad(g1) + 10*Sqr(g1)*(
      -98*traceAdjYdYd - 6*traceAdjYeYe + 117*Sqr(g2)) + 25*(73*Quad(g2) - 20*(
      3*traceAdjYdYd + traceAdjYeYe)*Sqr(g2) + 4*(-18*traceAdjYdYdAdjYdYd + 6*
      traceAdjYdYd*traceAdjYeYe - 6*traceAdjYeYeAdjYeYe - 6*traceAdjYuYuAdjYdYd
      + 32*traceAdjYdYd*Sqr(g3) + 9*Sqr(traceAdjYdYd) + Sqr(traceAdjYeYe))))*(
      Ye*Ye.adjoint()*Ye) - 0.18*(81*Quad(g1) - 10*Sqr(g1)*(-2*traceAdjYdYd + 6
      *traceAdjYeYe + 27*Sqr(g2)) + 25*(9*Quad(g2) + 4*(3*traceAdjYdYd +
      traceAdjYeYe)*Sqr(g2) - 32*traceAdjYdYd*Sqr(g3)))*(Ye*Ye.adjoint()*Ye*
      1.2020569031595942) + (4*(3*traceAdjYdYd + traceAdjYeYe) + 10.8*Sqr(g1) +
      6*Sqr(g2))*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 6*(Ye*Ye.adjoint()*Ye*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 18*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye
      *Ye.adjoint()*Ye*1.2020569031595942))).real();


   return beta_Ye;
}

} // namespace flexiblesusy
