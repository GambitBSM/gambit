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

// File generated at Wed 31 Oct 2018 19:30:32

#include "THDM_lepton_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Yu.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_lepton_susy_parameters::calc_beta_Yu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (oneOver16PiSqr*(Yu*(3*traceYdAdjYd + 3*traceYuAdjYu -
      1.4166666666666667*Sqr(g1) - 2.25*Sqr(g2) - 8*Sqr(g3)) - 1.5*(Yu*
      Yd.adjoint()*Yd) + 1.5*(Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 2-loop beta function of Yu.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_lepton_susy_parameters::calc_beta_Yu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = (twoLoop*(0.004629629629629629*Yu*(1267*Quad(g1) + Sqr(g1)*(
      225*traceYdAdjYd + 765*traceYuAdjYu - 162*Sqr(g2) + 456*Sqr(g3)) - 27*(42
      *Quad(g2) - 9*Sqr(g2)*(5*(traceYdAdjYd + traceYuAdjYu) + 8*Sqr(g3)) + 2*(
      -4*Lambda3*Lambda4 + 27*traceYdAdjYdYdAdjYd - 6*traceYdAdjYuYuAdjYd + 27*
      traceYuAdjYuYuAdjYu + 432*Quad(g3) - 80*(traceYdAdjYd + traceYuAdjYu)*Sqr
      (g3) - 6*Sqr(Lambda2) - 4*Sqr(Lambda3) - 4*Sqr(Lambda4) - 6*Sqr(Lambda5)
      - 6*Sqr(Lambda6) - 18*Sqr(Lambda7)))) + 0.020833333333333332*(-43*Sqr(g1)
      + 3*(60*traceYdAdjYd + 60*traceYuAdjYu + 9*Sqr(g2) - 256*Sqr(g3)))*(Yu*
      Yd.adjoint()*Yd) + 0.020833333333333332*(223*Sqr(g1) + 405*Sqr(g2) + 12*(
      -3*(8*Lambda2 + 9*(traceYdAdjYd + traceYuAdjYu)) + 64*Sqr(g3)))*(Yu*
      Yu.adjoint()*Yu) + 2.75*(Yu*Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 0.25*(Yu*
      Yd.adjoint()*Yd*Yu.adjoint()*Yu) - Yu*Yu.adjoint()*Yu*Yd.adjoint()*Yd +
      1.5*(Yu*Yu.adjoint()*Yu*Yu.adjoint()*Yu))).real();


   return beta_Yu;
}

/**
 * Calculates the 3-loop beta function of Yu.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> THDM_lepton_susy_parameters::calc_beta_Yu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_Yu;

   beta_Yu = ZEROMATRIX(3,3);


   return beta_Yu;
}

} // namespace flexiblesusy
