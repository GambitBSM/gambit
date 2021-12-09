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

// File generated at Thu 10 Oct 2019 17:27:11

#include "CMSSM_susy_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces

/**
 * Calculates the 1-loop beta function of Mu.
 *
 * @return 1-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_Mu_1_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_Mu;

   beta_Mu = Re(-0.2*oneOver16PiSqr*Mu*(-15*traceYdAdjYd - 5*traceYeAdjYe - 15*
      traceYuAdjYu + 3*Sqr(g1) + 15*Sqr(g2)));


   return beta_Mu;
}

/**
 * Calculates the 2-loop beta function of Mu.
 *
 * @return 2-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_Mu_2_loop(const Susy_traces& susy_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_Mu;

   beta_Mu = Re(0.02*twoLoop*Mu*(-450*traceYdAdjYdYdAdjYd - 300*
      traceYdAdjYuYuAdjYd - 150*traceYeAdjYeYeAdjYe - 450*traceYuAdjYuYuAdjYu +
      207*Quad(g1) + 375*Quad(g2) - 20*traceYdAdjYd*Sqr(g1) + 60*traceYeAdjYe*
      Sqr(g1) + 40*traceYuAdjYu*Sqr(g1) + 90*Sqr(g1)*Sqr(g2) + 800*traceYdAdjYd
      *Sqr(g3) + 800*traceYuAdjYu*Sqr(g3)));


   return beta_Mu;
}

/**
 * Calculates the 3-loop beta function of Mu.
 *
 * @return 3-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_Mu_3_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYu;


   double beta_Mu;

   beta_Mu = Re(19.556928691529336*threeLoop*(2.761169754808634*traceAdjYdYd*
      traceAdjYdYdAdjYdYd*Mu + 1.2597593745659919*traceAdjYdYdAdjYdYdAdjYdYd*Mu
       + 0.4601949591347724*traceAdjYdYdAdjYuYuAdjYdYd*Mu + 0.9203899182695447*
      traceAdjYdYdAdjYdYd*traceAdjYeYe*Mu + 0.9203899182695447*traceAdjYdYd*
      traceAdjYeYeAdjYeYe*Mu + 0.3067966394231816*traceAdjYeYe*
      traceAdjYeYeAdjYeYe*Mu + 0.41991979152199727*traceAdjYeYeAdjYeYeAdjYeYe*
      Mu + 0.9203899182695447*traceAdjYdYd*traceAdjYuYuAdjYdYd*Mu +
      0.3067966394231816*traceAdjYeYe*traceAdjYuYuAdjYdYd*Mu +
      0.9203899182695447*traceAdjYuYu*traceAdjYuYuAdjYdYd*Mu +
      2.761169754808634*traceAdjYuYu*traceAdjYuYuAdjYuYu*Mu +
      0.4601949591347724*traceAdjYuYuAdjYuYuAdjYdYd*Mu + 1.2597593745659919*
      traceAdjYuYuAdjYuYuAdjYuYu*Mu + 1.*Mu*Power6(g1) + 28.181721843368493*Mu*
      Power6(g2) - 0.9477204348670009*traceAdjYdYd*Mu*Quad(g1) -
      1.5801391059050232*traceAdjYeYe*Mu*Quad(g1) - 2.0885696292962597*
      traceAdjYuYu*Mu*Quad(g1) - 9.835101430414863*traceAdjYdYd*Mu*Quad(g2) -
      3.278367143471621*traceAdjYeYe*Mu*Quad(g2) - 9.835101430414863*
      traceAdjYuYu*Mu*Quad(g2) - 3.7105132880766374*traceAdjYdYd*Mu*Quad(g3) -
      3.7105132880766374*traceAdjYuYu*Mu*Quad(g3) + 0.8172149526242314*
      traceAdjYdYdAdjYdYd*Mu*Sqr(g1) - 0.20362167377786827*traceAdjYeYeAdjYeYe*
      Mu*Sqr(g1) + 0.5286999013710443*traceAdjYuYuAdjYdYd*Mu*Sqr(g1) +
      0.3616414039331648*traceAdjYuYuAdjYuYu*Mu*Sqr(g1) - 0.7656274698015747*Mu
      *Quad(g2)*Sqr(g1) + 3.7792781236979756*traceAdjYdYdAdjYdYd*Mu*Sqr(g2) +
      1.2597593745659919*traceAdjYeYeAdjYeYe*Mu*Sqr(g2) + 1.8407798365390895*
      traceAdjYuYuAdjYdYd*Mu*Sqr(g2) + 3.7792781236979756*traceAdjYuYuAdjYuYu*
      Mu*Sqr(g2) - 0.5698232720732902*Mu*Quad(g1)*Sqr(g2) - 0.5685203593983595*
      traceAdjYdYd*Mu*Sqr(g1)*Sqr(g2) + 0.5815494861476658*traceAdjYeYe*Mu*Sqr(
      g1)*Sqr(g2) + 0.4829959309460581*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g2) -
      5.169328765757029*traceAdjYdYdAdjYdYd*Mu*Sqr(g3) - 3.446219177171353*
      traceAdjYuYuAdjYdYd*Mu*Sqr(g3) - 5.169328765757029*traceAdjYuYuAdjYuYu*Mu
      *Sqr(g3) - 0.5972902430817468*Mu*Quad(g1)*Sqr(g3) - 4.072433475557365*Mu*
      Quad(g2)*Sqr(g3) + 0.4086910283056593*traceAdjYdYd*Mu*Sqr(g1)*Sqr(g3) +
      0.4434353663038093*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g3) + 2.101362371525213*
      traceAdjYdYd*Mu*Sqr(g2)*Sqr(g3) + 2.101362371525213*traceAdjYuYu*Mu*Sqr(
      g2)*Sqr(g3)));


   return beta_Mu;
}

/**
 * Calculates the 4-loop beta function of Mu.
 *
 * @return 4-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_Mu_4_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Mu;

   beta_Mu = 0;


   return beta_Mu;
}

/**
 * Calculates the 5-loop beta function of Mu.
 *
 * @return 5-loop beta function
 */
double CMSSM_susy_parameters::calc_beta_Mu_5_loop(const Susy_traces& susy_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_Mu;

   beta_Mu = 0;


   return beta_Mu;
}

} // namespace flexiblesusy
