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

// File generated at Tue 31 Jul 2018 21:11:42

#include "THDM_II_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yd.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yd_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (oneOver16PiSqr*(Yd*(3*traceYdAdjYd + traceYeAdjYe + 3*
      traceYuAdjYu - 0.4166666666666667*Sqr(g1) - 2.25*Sqr(g2) - 8*Sqr(g3)) +
      1.5*(Yd*Yd.adjoint()*Yd) - 1.5*(Yd*Yu.adjoint()*Yu))).real();


   return beta_Yd;
}

/**
 * Calculates the 2-loop beta function of Yd.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yd_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (twoLoop*(-0.004629629629629629*Yd*(113*Quad(g1) + 3*Sqr(g1)
      *(-15*(5*traceYdAdjYd + 15*traceYeAdjYe + 17*traceYuAdjYu) + 162*Sqr(g2)
      - 248*Sqr(g3)) + 27*(42*Quad(g2) - 3*Sqr(g2)*(5*(3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu) + 24*Sqr(g3)) + 2*(-4*Lambda3*Lambda4 + 27
      *traceYdAdjYdYdAdjYd - 6*traceYdAdjYuYuAdjYd + 9*traceYeAdjYeYeAdjYe + 27
      *traceYuAdjYuYuAdjYu + 432*Quad(g3) - 80*(traceYdAdjYd + traceYuAdjYu)*
      Sqr(g3) - 6*Sqr(Lambda2) - 4*Sqr(Lambda3) - 4*Sqr(Lambda4) - 6*Sqr(
      Lambda5) - 6*Sqr(Lambda6) - 18*Sqr(Lambda7)))) + 0.020833333333333332*(
      187*Sqr(g1) + 3*(135*Sqr(g2) + 4*(-3*(8*Lambda2 + 9*traceYdAdjYd + 3*
      traceYeAdjYe + 9*traceYuAdjYu) + 64*Sqr(g3))))*(Yd*Yd.adjoint()*Yd) +
      0.020833333333333332*(-79*Sqr(g1) + 3*(60*traceYdAdjYd + 20*traceYeAdjYe
      + 60*traceYuAdjYu + 9*Sqr(g2) - 256*Sqr(g3)))*(Yd*Yu.adjoint()*Yu) + 1.5*
      (Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - Yd*Yd.adjoint()*Yd*Yu.adjoint()*Yu
      - 0.25*(Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) + 2.75*(Yd*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu))).real();


   return beta_Yd;
}

/**
 * Calculates the 3-loop beta function of Yd.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yd_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = ZEROMATRIX(3,3);


   return beta_Yd;
}

} // namespace flexiblesusy
