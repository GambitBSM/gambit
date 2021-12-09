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

// File generated at Thu 10 Oct 2019 17:27:10

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

   beta_Ye = (oneOver16PiSqr*(-0.2*Ye*(-15*traceYdAdjYd - 5*traceYeAdjYe + 9*
      Sqr(g1) + 15*Sqr(g2)) + 3*(Ye*Ye.adjoint()*Ye))).real();


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

   beta_Ye = (twoLoop*(0.1*Ye*(-90*traceYdAdjYdYdAdjYd - 30*traceYdAdjYuYuAdjYd
       - 30*traceYeAdjYeYeAdjYe + 135*Quad(g1) + 75*Quad(g2) - 4*traceYdAdjYd*
      Sqr(g1) + 12*traceYeAdjYe*Sqr(g1) + 18*Sqr(g1)*Sqr(g2) + 160*traceYdAdjYd
      *Sqr(g3)) + 3*(-3*traceYdAdjYd - traceYeAdjYe + 2*Sqr(g2))*(Ye*Ye.adjoint
      ()*Ye) - 4*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye))).real();


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
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;


   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = (threeLoop*(0.0006666666666666666*Ye*(81000*traceAdjYdYd*
      traceAdjYdYdAdjYdYd + 4500*traceAdjYdYdAdjYdYdAdjYdYd + 27000*
      traceAdjYdYdAdjYdYd*traceAdjYeYe + 27000*traceAdjYdYd*traceAdjYeYeAdjYeYe
       + 9000*traceAdjYeYe*traceAdjYeYeAdjYeYe + 1500*
      traceAdjYeYeAdjYeYeAdjYeYe + 27000*traceAdjYuYu*traceAdjYuYuAdjYdYd +
      13500*traceAdjYuYuAdjYuYuAdjYdYd + 149958*Power6(g1) + 258750*Power6(g2)
      - 37625*traceAdjYdYd*Quad(g1) - 65475*traceAdjYeYe*Quad(g1) - 35100*
      traceAdjYuYu*Quad(g1) - 118125*traceAdjYdYd*Quad(g2) - 39375*traceAdjYeYe
      *Quad(g2) - 67500*traceAdjYuYu*Quad(g2) - 80000*traceAdjYdYd*Quad(g3) +
      4500*traceAdjYdYdAdjYdYd*Sqr(g1) + 13500*traceAdjYeYeAdjYeYe*Sqr(g1) -
      3600*traceAdjYuYuAdjYdYd*Sqr(g1) + 6750*Quad(g2)*Sqr(g1) + 13500*
      traceAdjYdYdAdjYdYd*Sqr(g2) + 4500*traceAdjYeYeAdjYeYe*Sqr(g2) + 27000*
      traceAdjYuYuAdjYdYd*Sqr(g2) + 25110*Quad(g1)*Sqr(g2) - 450*traceAdjYdYd*
      Sqr(g1)*Sqr(g2) - 12150*traceAdjYeYe*Sqr(g1)*Sqr(g2) + 108000*
      traceAdjYdYdAdjYdYd*Sqr(g3) + 36000*traceAdjYuYuAdjYdYd*Sqr(g3) + 118800*
      Quad(g1)*Sqr(g3) + 270000*Quad(g2)*Sqr(g3) - 28400*traceAdjYdYd*Sqr(g1)*
      Sqr(g3) - 198000*traceAdjYdYd*Sqr(g2)*Sqr(g3)) + 0.004*(4500*
      traceAdjYdYdAdjYdYdAdjYdYd + 1500*traceAdjYeYeAdjYeYeAdjYeYe - 10746*
      Power6(g1) + 78750*Power6(g2) - 385*traceAdjYdYd*Quad(g1) + 405*
      traceAdjYeYe*Quad(g1) - 23625*traceAdjYdYd*Quad(g2) - 7875*traceAdjYeYe*
      Quad(g2) - 4000*traceAdjYdYd*Quad(g3) + 2700*traceAdjYdYdAdjYdYd*Sqr(g1)
      - 2700*traceAdjYeYeAdjYeYe*Sqr(g1) + 2100*traceAdjYuYuAdjYdYd*Sqr(g1) -
      4050*Quad(g2)*Sqr(g1) + 13500*traceAdjYdYdAdjYdYd*Sqr(g2) + 4500*
      traceAdjYeYeAdjYeYe*Sqr(g2) - 7290*Quad(g1)*Sqr(g2) - 2250*traceAdjYdYd*
      Sqr(g1)*Sqr(g2) + 4050*traceAdjYeYe*Sqr(g1)*Sqr(g2) - 36000*
      traceAdjYdYdAdjYdYd*Sqr(g3) - 12000*traceAdjYuYuAdjYdYd*Sqr(g3) - 23760*
      Quad(g1)*Sqr(g3) - 54000*Quad(g2)*Sqr(g3) + 5600*traceAdjYdYd*Sqr(g1)*Sqr
      (g3) + 36000*traceAdjYdYd*Sqr(g2)*Sqr(g3))*(Ye*1.2020569031595942) - 0.03
      *(-1800*traceAdjYdYdAdjYdYd + 600*traceAdjYdYd*traceAdjYeYe - 600*
      traceAdjYeYeAdjYeYe - 600*traceAdjYuYuAdjYdYd + 1917*Quad(g1) + 1825*Quad
      (g2) - 980*traceAdjYdYd*Sqr(g1) - 60*traceAdjYeYe*Sqr(g1) - 1500*
      traceAdjYdYd*Sqr(g2) - 500*traceAdjYeYe*Sqr(g2) + 1170*Sqr(g1)*Sqr(g2) +
      3200*traceAdjYdYd*Sqr(g3) + 900*Sqr(traceAdjYdYd) + 100*Sqr(traceAdjYeYe)
      )*(Ye*Ye.adjoint()*Ye) - 0.18*(81*Quad(g1) + 225*Quad(g2) + 20*
      traceAdjYdYd*Sqr(g1) - 60*traceAdjYeYe*Sqr(g1) + 300*traceAdjYdYd*Sqr(g2)
      + 100*traceAdjYeYe*Sqr(g2) - 270*Sqr(g1)*Sqr(g2) - 800*traceAdjYdYd*Sqr(
      g3))*(Ye*Ye.adjoint()*Ye*1.2020569031595942) + 0.4*(30*traceAdjYdYd + 10*
      traceAdjYeYe + 27*Sqr(g1) + 15*Sqr(g2))*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*
      Ye) + 6*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 18*(Ye*Ye.
      adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942))).real()
      ;


   return beta_Ye;
}

/**
 * Calculates the 4-loop beta function of Ye.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Ye_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = ZEROMATRIX(3,3);


   return beta_Ye;
}

/**
 * Calculates the 5-loop beta function of Ye.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_susy_parameters::calc_beta_Ye_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Ye;

   beta_Ye = ZEROMATRIX(3,3);


   return beta_Ye;
}

} // namespace flexiblesusy
