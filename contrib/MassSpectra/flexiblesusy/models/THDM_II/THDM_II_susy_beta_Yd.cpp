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

// File generated at Thu 2 Aug 2018 15:04:47

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


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (oneOver16PiSqr*(Yd*(3*traceYdAdjYd + traceYeAdjYe -
      0.4166666666666667*Sqr(g1) - 2.25*Sqr(g2) - 8*Sqr(g3)) + 1.5*(Yd*
      Yd.adjoint()*Yd) + 0.5*(Yd*Yu.adjoint()*Yu))).real();


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
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (twoLoop*(-0.004629629629629629*Yd*(113*Quad(g1) + 3*Sqr(g1)
      *(-75*(traceYdAdjYd + 3*traceYeAdjYe) + 162*Sqr(g2) - 248*Sqr(g3)) + 27*(
      42*Quad(g2) - 3*Sqr(g2)*(5*(3*traceYdAdjYd + traceYeAdjYe) + 24*Sqr(g3))
      + 2*(-4*Lambda3*Lambda4 + 27*traceYdAdjYdYdAdjYd + 9*traceYdAdjYuYuAdjYd
      + 9*traceYeAdjYeYeAdjYe + 432*Quad(g3) - 80*traceYdAdjYd*Sqr(g3) - 6*Sqr(
      Lambda1) - 4*Sqr(Lambda3) - 4*Sqr(Lambda4) - 6*Sqr(Lambda5) - 18*Sqr(
      Lambda6) - 6*Sqr(Lambda7)))) + (-6*Lambda1 - 6.75*traceYdAdjYd - 2.25*
      traceYeAdjYe + 3.8958333333333335*Sqr(g1) + 8.4375*Sqr(g2) + 16*Sqr(g3))*
      (Yd*Yd.adjoint()*Yd) + (-2*Lambda3 + 2*Lambda4 - 2.25*traceYuAdjYu -
      0.3680555555555556*Sqr(g1) + 2.0625*Sqr(g2) + 5.333333333333333*Sqr(g3))*
      (Yd*Yu.adjoint()*Yu) + 1.5*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.25*(
      Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 0.25*(Yd*Yu.adjoint()*Yu*Yu.adjoint
      ()*Yu))).real();


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
