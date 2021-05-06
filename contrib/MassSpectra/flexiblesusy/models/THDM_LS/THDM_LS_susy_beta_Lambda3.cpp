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

// File generated at Tue 7 Apr 2020 14:55:41

#include "THDM_LS_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambda3.
 *
 * @return 1-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda3_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Lambda3;

   beta_Lambda3 = Re(oneOver16PiSqr*(6*Lambda1*Lambda3 + 6*Lambda2*
      Lambda3 + 2*Lambda1*Lambda4 + 2*Lambda2*Lambda4 + 6*Lambda3*traceYdAdjYd
      + 2*Lambda3*traceYeAdjYe + 6*Lambda3*traceYuAdjYu + 2*AbsSqr(Lambda5) + 4
      *AbsSqr(Lambda7) + 4*(Lambda6 + 2*Lambda7)*Conj(Lambda6) + 8*Lambda6*Conj
      (Lambda7) + 0.75*Quad(g1) + 2.25*Quad(g2) - 3*Lambda3*Sqr(g1) - 9*Lambda3
      *Sqr(g2) - 1.5*Sqr(g1)*Sqr(g2) + 4*Sqr(Lambda3) + 2*Sqr(Lambda4)));


   return beta_Lambda3;
}

/**
 * Calculates the 2-loop beta function of Lambda3.
 *
 * @return 2-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda3_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambda3;

   const double beta_Lambda3_1 = Re(-0.041666666666666664*twoLoop*(384*
      Lambda1*Lambda3*Lambda4 + 384*Lambda2*Lambda3*Lambda4 + 864*Lambda5*
      Lambda6*Lambda7 + 864*Lambda2*Lambda3*traceYdAdjYd + 288*Lambda2*Lambda4*
      traceYdAdjYd + 324*Lambda3*traceYdAdjYdYdAdjYd + 504*Lambda3*
      traceYdAdjYuYuAdjYd + 576*Lambda4*traceYdAdjYuYuAdjYd + 288*Lambda1*
      Lambda3*traceYeAdjYe + 96*Lambda1*Lambda4*traceYeAdjYe + 108*Lambda3*
      traceYeAdjYeYeAdjYe + 864*Lambda2*Lambda3*traceYuAdjYu + 288*Lambda2*
      Lambda4*traceYuAdjYu + 324*Lambda3*traceYuAdjYuYuAdjYu + 288*Cube(Lambda3
      ) + 288*Cube(Lambda4) + 393*Power6(g1) - 873*Power6(g2) - 90*Lambda1*Quad
      (g1) - 90*Lambda2*Quad(g1) - 591*Lambda3*Quad(g1) - 60*Lambda4*Quad(g1) -
      30*traceYdAdjYd*Quad(g1) + 150*traceYeAdjYe*Quad(g1) + 114*traceYuAdjYu*
      Quad(g1) - 270*Lambda1*Quad(g2) - 270*Lambda2*Quad(g2) + 333*Lambda3*Quad
      (g2) - 180*Lambda4*Quad(g2) + 54*traceYdAdjYd*Quad(g2) + 18*traceYeAdjYe*
      Quad(g2) + 54*traceYuAdjYu*Quad(g2) - 288*Lambda1*Lambda3*Sqr(g1) - 288*
      Lambda2*Lambda3*Sqr(g1) - 96*Lambda1*Lambda4*Sqr(g1) - 96*Lambda2*Lambda4
      *Sqr(g1) - 50*Lambda3*traceYdAdjYd*Sqr(g1) - 150*Lambda3*traceYeAdjYe*Sqr
      (g1) - 170*Lambda3*traceYuAdjYu*Sqr(g1) - 33*Quad(g2)*Sqr(g1) - 48*AbsSqr
      (Lambda5)*(-9*Lambda1 - 9*Lambda2 - 9*Lambda3 - 22*Lambda4 - 3*
      traceYdAdjYd - traceYeAdjYe - 3*traceYuAdjYu + 2*Sqr(g1)) - 864*Lambda1*
      Lambda3*Sqr(g2) - 864*Lambda2*Lambda3*Sqr(g2) - 432*Lambda1*Lambda4*Sqr(
      g2) - 432*Lambda2*Lambda4*Sqr(g2) + 288*Lambda3*Lambda4*Sqr(g2) - 270*
      Lambda3*traceYdAdjYd*Sqr(g2) - 90*Lambda3*traceYeAdjYe*Sqr(g2) - 270*
      Lambda3*traceYuAdjYu*Sqr(g2) - 303*Quad(g1)*Sqr(g2) + 60*Lambda1*Sqr(g1)*
      Sqr(g2) + 60*Lambda2*Sqr(g1)*Sqr(g2) - 66*Lambda3*Sqr(g1)*Sqr(g2) + 72*
      Lambda4*Sqr(g1)*Sqr(g2) + 108*traceYdAdjYd*Sqr(g1)*Sqr(g2) + 132*
      traceYeAdjYe*Sqr(g1)*Sqr(g2) + 252*traceYuAdjYu*Sqr(g1)*Sqr(g2) + 48*Conj
      (Lambda6)*(31*Lambda1*Lambda6 + 11*Lambda2*Lambda6 + 30*Lambda3*Lambda6 +
      34*Lambda4*Lambda6 + 11*Lambda1*Lambda7 + 11*Lambda2*Lambda7 + 44*
      Lambda3*Lambda7 + 22*Lambda4*Lambda7 + 12*Lambda7*traceYdAdjYd - (Lambda6
      + 8*Lambda7)*Sqr(g1) - 27*Lambda7*Sqr(g2)) - 960*Lambda3*traceYdAdjYd*
      Sqr(g3) - 960*Lambda3*traceYuAdjYu*Sqr(g3) + 360*Lambda3*Sqr(Lambda1) +
      96*Lambda4*Sqr(Lambda1) + 360*Lambda3*Sqr(Lambda2) + 96*Lambda4*Sqr(
      Lambda2) + 864*Lambda1*Sqr(Lambda3) + 864*Lambda2*Sqr(Lambda3) + 96*
      Lambda4*Sqr(Lambda3) + 288*traceYdAdjYd*Sqr(Lambda3) + 96*traceYeAdjYe*
      Sqr(Lambda3) + 288*traceYuAdjYu*Sqr(Lambda3) - 48*Sqr(g1)*Sqr(Lambda3) -
      144*Sqr(g2)*Sqr(Lambda3) + 336*Lambda1*Sqr(Lambda4) + 336*Lambda2*Sqr(
      Lambda4) + 384*Lambda3*Sqr(Lambda4) + 144*traceYdAdjYd*Sqr(Lambda4) + 48*
      traceYeAdjYe*Sqr(Lambda4) + 144*traceYuAdjYu*Sqr(Lambda4) + 48*Sqr(g1)*
      Sqr(Lambda4) - 144*Sqr(g2)*Sqr(Lambda4) + 816*Lambda5*Sqr(Lambda6) + 816*
      Lambda5*Sqr(Lambda7)));
   const double beta_Lambda3_2 = Re(-2*twoLoop*(2*Conj(Lambda6)*(2*
      Lambda6*traceYeAdjYe + 2*Lambda7*traceYeAdjYe + 6*Lambda7*traceYuAdjYu +
      9*Conj(Lambda5)*Conj(Lambda7)) + Conj(Lambda7)*(11*Lambda1*Lambda6 + 11*
      Lambda2*Lambda6 + 44*Lambda3*Lambda6 + 22*Lambda4*Lambda6 + 11*Lambda1*
      Lambda7 + 31*Lambda2*Lambda7 + 30*Lambda3*Lambda7 + 34*Lambda4*Lambda7 +
      12*Lambda6*traceYdAdjYd + 12*Lambda7*traceYdAdjYd + 4*Lambda6*
      traceYeAdjYe + 12*Lambda6*traceYuAdjYu + 12*Lambda7*traceYuAdjYu + 17*
      Conj(Lambda5)*Conj(Lambda7) - (8*Lambda6 + Lambda7)*Sqr(g1) - 27*Lambda6*
      Sqr(g2)) + 17*Conj(Lambda5)*Sqr(Conj(Lambda6))));

   beta_Lambda3 = beta_Lambda3_1 + beta_Lambda3_2;


   return beta_Lambda3;
}

/**
 * Calculates the 3-loop beta function of Lambda3.
 *
 * @return 3-loop beta function
 */
double THDM_LS_susy_parameters::calc_beta_Lambda3_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambda3;

   beta_Lambda3 = 0;


   return beta_Lambda3;
}

} // namespace flexiblesusy
