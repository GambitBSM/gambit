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

// File generated at Fri 11 May 2018 14:06:40

#include "THDM_II_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(-0.08333333333333333*Yu*(-36*traceYuAdjYu +
      17*Sqr(g1) + 27*Sqr(g2) + 96*Sqr(g3)) + 0.5*(Yu*Yd.adjoint()*Yd) + 1.5*(
      Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(0.004629629629629629*Yu*(1267*Quad(g1) + Sqr(g1)*(
      765*traceYuAdjYu - 162*Sqr(g2) + 456*Sqr(g3)) - 27*(42*Quad(g2) - 9*Sqr(
      g2)*(5*traceYuAdjYu + 8*Sqr(g3)) + 2*(-4*Lambda3*Lambda4 + 9*
      traceYdAdjYuYuAdjYd + 27*traceYuAdjYuYuAdjYu + 432*Quad(g3) - 80*
      traceYuAdjYu*Sqr(g3) - 6*Sqr(Lambda2) - 4*Sqr(Lambda3) - 4*Sqr(Lambda4) -
      6*Sqr(Lambda5) - 6*Sqr(Lambda6) - 18*Sqr(Lambda7)))) + (-2*Lambda3 + 2*
      Lambda4 - 2.25*traceYdAdjYd - 0.75*traceYeAdjYe - 0.2847222222222222*Sqr(
      g1) + 2.0625*Sqr(g2) + 5.333333333333333*Sqr(g3))*(Yu*Yd.adjoint()*Yd) +
      (-6*Lambda2 - 6.75*traceYuAdjYu + 4.645833333333333*Sqr(g1) + 8.4375*Sqr(
      g2) + 16*Sqr(g3))*(Yu*Yu.adjoint()*Yu) - 0.25*(Yu*Yd.adjoint()*Yd*
      Yd.adjoint()*Yd) - 0.25*(Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu) + 1.5*(Yu*
      Yu.adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

/**
 * Calculates the 4-loop beta function of Yu.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

} // namespace flexiblesusy
