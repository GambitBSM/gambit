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

// File generated at Wed 29 Mar 2017 15:35:48

#include "THDM_II_two_scale_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the one-loop beta function of Yu.
 *
 * @return one-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_one_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (0.08333333333333333*oneOver16PiSqr*(-(Yu*(-36*traceYuAdjYu
      + 17*Sqr(g1) + 27*Sqr(g2) + 96*Sqr(g3))) + 6*(Yu*Yd.adjoint()*Yd + 3*(Yu*
      Yu.adjoint()*Yu)))).real();


   return beta_Yu;
}

/**
 * Calculates the two-loop beta function of Yu.
 *
 * @return two-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_two_loop(const Susy_traces& susy_traces) const
{
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(Yu*(5.8657407407407405*Power(g1,4) - 5.25*Power(g2
      ,4) - 108*Power(g3,4) + Lambda3*Lambda4 - 2.25*traceYdAdjYuYuAdjYd - 6.75
      *traceYuAdjYuYuAdjYu - 0.75*Sqr(g1)*Sqr(g2) + 2.111111111111111*Sqr(g1)*
      Sqr(g3) + 9*Sqr(g2)*Sqr(g3) + 0.20833333333333334*traceYuAdjYu*(17*Sqr(g1
      ) + 27*Sqr(g2) + 96*Sqr(g3)) + 1.5*Sqr(Lambda2) + Sqr(Lambda3) + Sqr(
      Lambda4) + 1.5*Sqr(Lambda5) + 1.5*Sqr(Lambda6) + 4.5*Sqr(Lambda7)) +
      0.006944444444444444*((-288*Lambda3 + 288*Lambda4 - 324*traceYdAdjYd -
      108*traceYeAdjYe - 41*Sqr(g1) + 297*Sqr(g2) + 768*Sqr(g3))*(Yu*Yd.adjoint
      ()*Yd) + 3*((-288*Lambda2 - 324*traceYuAdjYu + 223*Sqr(g1) + 405*Sqr(g2)
      + 768*Sqr(g3))*(Yu*Yu.adjoint()*Yu) - 12*(Yu*Yd.adjoint()*Yd*Yd.adjoint()
      *Yd + Yu*Yd.adjoint()*Yd*Yu.adjoint()*Yu - 6*(Yu*Yu.adjoint()*Yu*
      Yu.adjoint()*Yu)))))).real();


   return beta_Yu;
}

/**
 * Calculates the three-loop beta function of Yu.
 *
 * @return three-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_II_susy_parameters::calc_beta_Yu_three_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

} // namespace flexiblesusy
