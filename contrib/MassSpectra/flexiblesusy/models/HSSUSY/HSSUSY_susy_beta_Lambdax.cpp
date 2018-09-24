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

// File generated at Thu 10 May 2018 14:43:39

#include "HSSUSY_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Lambdax.
 *
 * @return 1-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_Lambdax_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Lambdax;

   beta_Lambdax = Re(oneOver16PiSqr*(0.27*Quad(g1) + 2.25*Quad(g2) - 9*
      Lambdax*Sqr(g2) + 0.9*Sqr(g1)*(-2*Lambdax + Sqr(g2)) + 4*(-3*
      traceYdAdjYdYdAdjYd - traceYeAdjYeYeAdjYe - 3*traceYuAdjYuYuAdjYu + 3*
      traceYdAdjYd*Lambdax + traceYeAdjYe*Lambdax + 3*traceYuAdjYu*Lambdax + 3*
      Sqr(Lambdax))));


   return beta_Lambdax;
}

/**
 * Calculates the 2-loop beta function of Lambdax.
 *
 * @return 2-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_Lambdax_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYdAdjYdYdAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYd;
   const double traceYdAdjYdYdAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYd;
   const double traceYdAdjYuYuAdjYdYdAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYuYuAdjYd =
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYeYeAdjYe =
      TRACE_STRUCT.traceYeAdjYeYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYuYuAdjYu =
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYu;


   double beta_Lambdax;

   beta_Lambdax = Re(twoLoop*(60*traceYdAdjYdYdAdjYdYdAdjYd - 24*
      traceYdAdjYdYdAdjYuYuAdjYd + 12*traceYdAdjYuYuAdjYdYdAdjYd - 12*
      traceYdAdjYuYuAdjYuYuAdjYd + 20*traceYeAdjYeYeAdjYeYeAdjYe + 60*
      traceYuAdjYuYuAdjYuYuAdjYu - 78*Cube(Lambdax) - 3*traceYdAdjYdYdAdjYd*
      Lambdax - 42*traceYdAdjYuYuAdjYd*Lambdax - traceYeAdjYeYeAdjYe*Lambdax -
      3*traceYuAdjYuYuAdjYu*Lambdax - 3.411*Power6(g1) + 38.125*Power6(g2) -
      0.125*(36*traceYdAdjYd + 12*traceYeAdjYe + 36*traceYuAdjYu + 73*Lambdax)*
      Quad(g2) + 1.5*Lambdax*(15*traceYdAdjYd + 5*traceYeAdjYe + 15*
      traceYuAdjYu + 36*Lambdax)*Sqr(g2) - 0.015*Quad(g1)*(-60*traceYdAdjYd +
      300*traceYeAdjYe + 228*traceYuAdjYu - 629*Lambdax + 559*Sqr(g2)) - 64*
      traceYdAdjYdYdAdjYd*Sqr(g3) - 64*traceYuAdjYuYuAdjYu*Sqr(g3) + 80*
      traceYdAdjYd*Lambdax*Sqr(g3) + 80*traceYuAdjYu*Lambdax*Sqr(g3) - 72*
      traceYdAdjYd*Sqr(Lambdax) - 24*traceYeAdjYe*Sqr(Lambdax) - 72*
      traceYuAdjYu*Sqr(Lambdax) - 0.025*Sqr(g1)*(289*Quad(g2) - 6*(36*
      traceYdAdjYd + 44*traceYeAdjYe + 84*traceYuAdjYu + 39*Lambdax)*Sqr(g2) -
      4*(16*traceYdAdjYdYdAdjYd - 48*traceYeAdjYeYeAdjYe - 32*
      traceYuAdjYuYuAdjYu + 25*traceYdAdjYd*Lambdax + 75*traceYeAdjYe*Lambdax +
      85*traceYuAdjYu*Lambdax + 108*Sqr(Lambdax)))));


   return beta_Lambdax;
}

/**
 * Calculates the 3-loop beta function of Lambdax.
 *
 * @return 3-loop beta function
 */
double HSSUSY_susy_parameters::calc_beta_Lambdax_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Lambdax;

   beta_Lambdax = Re(0.0001*threeLoop*(-60320*Power8(g1) - 4563640*Power8
      (g2) - 40*Power6(g1)*(-14084*Lambdax + 1543*Sqr(g2) - 663*Sqr(g3) - 11117
      *Sqr(Yu(2,2))) + 20*Power6(g2)*(865483*Lambdax + 15072*Sqr(g3) + 125000*
      Sqr(Yu(2,2))) + 2*Sqr(g2)*(-968630*Cube(Lambdax) + 1482760*Power6(Yu(2,2)
      ) - 54700*Lambdax*Quad(Yu(2,2)) + 266980*Quad(Yu(2,2))*Sqr(g3) + 151443*
      Lambdax*Sqr(g3)*Sqr(Yu(2,2)) - 1797695*Sqr(Lambdax)*Sqr(Yu(2,2))) + 80*
      Quad(g2)*(7942*Quad(Yu(2,2)) - 98785*Sqr(Lambdax) - 79916*Lambdax*Sqr(Yu(
      2,2)) + Sqr(g3)*(-14286*Lambdax + 8232*Sqr(Yu(2,2)))) + 2*Quad(g1)*(
      130000*Quad(g2) + 318960*Quad(Yu(2,2)) - 927660*Sqr(Lambdax) - 748599*
      Lambdax*Sqr(Yu(2,2)) + Sqr(g3)*(-83810*Lambdax + 20320*Sqr(Yu(2,2))) + 10
      *Sqr(g2)*(61753*Lambdax + 2210*Sqr(g3) + 21254*Sqr(Yu(2,2)))) - 10*Sqr(g1
      )*(38745*Cube(Lambdax) + 151556*Power6(g2) - 135720*Power6(Yu(2,2)) +
      42030*Lambdax*Quad(Yu(2,2)) + 63869*Sqr(Lambdax)*Sqr(Yu(2,2)) - 4*Quad(g2
      )*(39819*Lambdax + 1507*Sqr(g3) + 13041*Sqr(Yu(2,2))) - 4*Sqr(g3)*(17570*
      Quad(Yu(2,2)) + 8727*Lambdax*Sqr(Yu(2,2))) + 2*Sqr(g2)*(140712*Quad(Yu(2,
      2)) + 158320*Sqr(Lambdax) - 5615*Lambdax*Sqr(Yu(2,2)) - 22772*Sqr(g3)*Sqr
      (Yu(2,2)))) - 5*(893528*Lambdax*Power6(Yu(2,2)) + 1945192*Power8(Yu(2,2))
      - 3005675*Quad(Lambdax) - 3536520*Quad(Yu(2,2))*Sqr(Lambdax) - 873000*
      Cube(Lambdax)*Sqr(Yu(2,2)) + 8*Quad(g3)*(50201*Quad(Yu(2,2)) - 178484*
      Lambdax*Sqr(Yu(2,2))) - 4*Sqr(g3)*(500988*Power6(Yu(2,2)) - 662866*
      Lambdax*Quad(Yu(2,2)) + 80385*Sqr(Lambdax)*Sqr(Yu(2,2))))));


   return beta_Lambdax;
}

} // namespace flexiblesusy
