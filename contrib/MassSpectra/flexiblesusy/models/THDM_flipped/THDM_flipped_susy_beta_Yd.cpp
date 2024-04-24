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

// File generated at Tue 7 Apr 2020 14:54:55

#include "THDM_flipped_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yd.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_flipped_susy_parameters::calc_beta_Yd_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (oneOver16PiSqr*(-0.08333333333333333*Yd*(-36*traceYdAdjYd +
      5*Sqr(g1) + 27*Sqr(g2) + 96*Sqr(g3)) + 1.5*(Yd*Yd.adjoint()*Yd) + 0.5*(
      Yd*Yu.adjoint()*Yu))).real();


   return beta_Yd;
}

/**
 * Calculates the 2-loop beta function of Yd.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_flipped_susy_parameters::calc_beta_Yd_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = (twoLoop*(Yd*(Lambda3*Lambda4 - 6.75*traceYdAdjYdYdAdjYd -
      2.25*traceYdAdjYuYuAdjYd + 1.5*AbsSqr(Lambda5) + 4.5*AbsSqr(Lambda6) +
      1.5*AbsSqr(Lambda7) - 0.5231481481481481*Quad(g1) - 5.25*Quad(g2) - 108*
      Quad(g3) + 1.0416666666666667*traceYdAdjYd*Sqr(g1) + 5.625*traceYdAdjYd*
      Sqr(g2) - 2.25*Sqr(g1)*Sqr(g2) + 20*traceYdAdjYd*Sqr(g3) +
      3.4444444444444446*Sqr(g1)*Sqr(g3) + 9*Sqr(g2)*Sqr(g3) + 1.5*Sqr(Lambda1)
      + Sqr(Lambda3) + Sqr(Lambda4)) + (-6*Lambda1 - 6.75*traceYdAdjYd +
      3.8958333333333335*Sqr(g1) + 8.4375*Sqr(g2) + 16*Sqr(g3))*(Yd*Yd.adjoint(
      )*Yd) + (-2*Lambda3 + 2*Lambda4 - 0.75*traceYeAdjYe - 2.25*traceYuAdjYu -
      0.3680555555555556*Sqr(g1) + 2.0625*Sqr(g2) + 5.333333333333333*Sqr(g3))
      *(Yd*Yu.adjoint()*Yu) + 1.5*(Yd*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.25*(
      Yd*Yu.adjoint()*Yu*Yd.adjoint()*Yd) - 0.25*(Yd*Yu.adjoint()*Yu*Yu.adjoint
      ()*Yu))).real();


   return beta_Yd;
}

/**
 * Calculates the 3-loop beta function of Yd.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_flipped_susy_parameters::calc_beta_Yd_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yd;

   beta_Yd = ZEROMATRIX(3,3);


   return beta_Yd;
}

} // namespace flexiblesusy
