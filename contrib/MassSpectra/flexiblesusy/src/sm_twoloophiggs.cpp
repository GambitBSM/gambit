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

#include "sm_twoloophiggs.hpp"
#include "wrappers.hpp"
#include "pv.hpp"

#include <cmath>

namespace flexiblesusy {
namespace sm_twoloophiggs {

/**
 * Standard Model Higgs 1-loop contribution (Landau gauge).
 * Taken from arxiv:1205.6497, Eq. (16).
 *
 * @note The result contains the 1-loop tadpole diagrams.  It is
 * therefore not 1-particle irreducible (1PI).
 *
 * @note The sign of the result is opposite to arxiv:1205.6497,
 * Eq. (16).
 *
 * @warning The result is in Landau gauge (\f$\xi = 0\f$).
 *
 * @warning In the diagram that has a Higgs loop, the momentum has
 * been set to the tree-level Higgs mass, \f$p^2 = 2\lambda v^2\f$.
 *
 * @param p momentum
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 * @param v MS-bar VEV
 * @param gY MS-bar hypercharge gauge coupling
 * @param g2 MS-bar SU(2)_L gauge coupling
 * @param lambda MS-bar 4-Higgs coupling
 *
 * @return real part of 1-loop self-energy
 */
double delta_mh_1loop_sm(
   double p, double scale, double mt, double yt,
   double v, double gY, double g2, double lambda)
{
   using namespace passarino_veltman;

   const double yt2 = Sqr(yt);
   const double mt2 = Sqr(mt);
   const double p2 = Sqr(p);
   const double Q2 = Sqr(scale);
   const double lambda2 = Sqr(lambda);
   const double v2 = Sqr(v);
   const double g22 = Sqr(g2);
   const double g24 = Sqr(g22);
   const double gp2 = Sqr(gY);
   const double G2 = g22 + gp2;
   const double G4 = Sqr(G2);
   const double mW2 = g22 * v2/4.;
   const double mZ2 = G2 * v2/4.;
   const double mH2 = 2*lambda*v2;
   const double LogW = FiniteLog(mW2 / Q2);
   const double LogZ = FiniteLog(mZ2 / Q2);
   const double LogH = FiniteLog(mH2 / Q2);

   const double result =
      (+3*yt2*(4*mt2 - p2)*ReB0(p2,mt2,mt2,Q2)
       +6*lambda2*v2*(3*LogH-6+Pi*Sqrt(3))
       -v2/4.*(3*g24-8*lambda*g22+16*lambda2)*ReB0(p2,mW2,mW2,Q2)
       -v2/8.*(3*G4-8*lambda*G2+16*lambda2)*ReB0(p2,mZ2,mZ2,Q2)
       +2*mW2*(g22-2*lambda*(LogW-1))
       +mZ2*(G2-2*lambda*(LogZ-1))
      );

   return - result * oneOver16PiSqr;
}

/**
 * Standard Model Higgs 1-loop contribution, \f$O(\alpha_t)\f$.
 * Taken from arxiv:1205.6497, Eq. (16).
 *
 * @note The result contains the 1-loop top quark tadpole diagram.  It
 * is therefore not 1-particle irreducible (1PI).
 *
 * @note The sign of the result is opposite to arxiv:1205.6497,
 * Eq. (16).
 *
 * @param p momentum
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 *
 * @return real part of 1-loop self-energy O(alpha_t)
 */
double delta_mh_1loop_at_sm(
   double p, double scale, double mt, double yt)
{
   using namespace passarino_veltman;

   const double yt2 = Sqr(yt);
   const double mt2 = Sqr(mt);
   const double p2 = Sqr(p);
   const double Q2 = Sqr(scale);

   const double result =
      3*yt2*(4.*mt2 - p2)*ReB0(p2,mt2,mt2,Q2);

   return - result * oneOver16PiSqr;
}

/**
 * Standard Model Higgs self-energy 2-loop, \f$O(\alpha_t
 * \alpha_s)\f$, including momentum dependence.
 *
 * @warning The result is in Landau gauge (\f$\xi = 0\f$).
 *
 * @param p2    squared momentum
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 * @param g3 MS-bar strong gauge coupling
 *
 * @return real part of 2-loop self-energy \f$O(\alpha_t \alpha_s)\f$
 */
double self_energy_higgs_2loop_at_as_sm(
   double p2, double scale, double mt, double yt, double g3)
{
   const double yt2 = Sqr(yt);
   const double g32 = Sqr(g3);
   const double t = Sqr(mt);
   const double s = p2;
   const double q = Sqr(scale);
   const double lnt = std::log(t/q);

   const double result =
      1./135. * g32 * yt2 * (-10800*t - 1665*p2 + (122*Sqr(p2))/t +
                             540*(12*t + 5*p2) * lnt -
                             1620*(12*t - p2) * Sqr(lnt));

   return result * twoLoop;
}

/**
 * Standard Model Higgs tadpole 2-loop, \f$O(\alpha_t \alpha_s)\f$.
 *
 * @warning The result is in Landau gauge (\f$\xi = 0\f$).
 *
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 * @param g3 MS-bar strong gauge coupling
 *
 * @return real part of 2-loop self-energy \f$O(\alpha_t \alpha_s)\f$
 */
double tadpole_higgs_2loop_at_as_sm(
   double scale, double mt, double yt, double g3)
{
   const double yt2 = Sqr(yt);
   const double g32 = Sqr(g3);
   const double t = Sqr(mt);
   const double q = Sqr(scale);
   const double lnt = std::log(t/q);

   const double result =
      -16 * g32 * t * yt2 * (5 - 5*lnt + 3*Sqr(lnt));

   return result * twoLoop;
}

double delta_mh_2loop_at_as_sm(
   double p2, double scale, double mt, double yt, double g3)
{
   return - self_energy_higgs_2loop_at_as_sm(p2, scale, mt, yt, g3)
      + tadpole_higgs_2loop_at_as_sm(scale, mt, yt, g3);
}

/**
 * Standard Model Higgs self-energy 2-loop, \f$O(\alpha_t^2)\f$.
 *
 * @param p2    squared momentum (not used so far)
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 *
 * @return real part of 2-loop self-energy \f$O(\alpha_t^2) \f$
 */
double self_energy_higgs_2loop_at_at_sm(
   double /* p2 */, double scale, double mt, double yt)
{
   const double yt4 = Power4(yt);
   const double mt2 = Sqr(mt);
   const double Q2 = Sqr(scale);
   const double LogT = FiniteLog(mt2 / Q2);
   const double LogT2 = Sqr(LogT);

   const double result =
      3*mt2 * yt4 * (19 + Sqr(Pi) - 27 * LogT + 9 * LogT2);

   return result * twoLoop;
}

/**
 * Standard Model Higgs tadpole 2-loop, \f$O(\alpha_t^2)\f$.
 *
 * @param scale renormalization scale
 * @param mt MS-bar top mass
 * @param yt MS-bar Yukawa coupling
 *
 * @return real part of 2-loop self-energy \f$O(\alpha_t^2) \f$
 */
double tadpole_higgs_2loop_at_at_sm(
   double scale, double mt, double yt)
{
   const double yt4 = Power4(yt);
   const double mt2 = Sqr(mt);
   const double Q2 = Sqr(scale);
   const double LogT = FiniteLog(mt2 / Q2);
   const double LogT2 = Sqr(LogT);

   const double result =
      mt2 * yt4 * (45 + Sqr(Pi) - 39*LogT + 9*LogT2);

   return result * twoLoop;
}

double delta_mh_2loop_at_at_sm(
   double p2, double scale, double mt, double yt)
{
   return - self_energy_higgs_2loop_at_at_sm(p2, scale, mt, yt)
      + tadpole_higgs_2loop_at_at_sm(scale, mt, yt);
}

namespace {

double QA0(double m, double Q) {
   using namespace flexiblesusy::passarino_veltman;
   return ReA0(m*m, Q*Q);
}

double QB0(double p, double m1, double m2, double Q) {
   using namespace flexiblesusy::passarino_veltman;
   return ReB0(p*p, m1*m1, m2*m2, Q*Q);
}

} // anonymous namespace

/**
 * Standard Model Higgs 1-loop contribution as used in SUSYHD 1.0.2.
 *
 * @note The result contains the 1-loop tadpole diagrams.  It is
 * therefore not 1-particle irreducible (1PI).
 *
 * @param vev Higgs Vacuum expectation value (~ 246 GeV)
 * @param Mt top quark pole mass
 * @param mh MS-bar Higgs mass
 * @param MW W pole mass
 * @param MZ Z pole mass
 * @param Q renormalization scale
 *
 * @return real part of 1-loop self-energy
 */
double delta_mh_1loop_sm_SUSYHD(
   double vev, double Mt, double mh, double MW, double MZ, double Q)
{
   using namespace std;

   const double Pi = M_PI;

   const double delta_lambda =
      ((pow(mh,4) + pow(mh,2)*
         (-6*pow(Mt,2) + 2*pow(MW,2) + pow(MZ,2)) -
        8*(2*pow(MW,4) + pow(MZ,4)))/4. -
     (3*pow(mh,2)*pow(MW,2)*QA0(mh,Q))/
      (2.*(pow(mh,2) - pow(MW,2))) + 3*pow(mh,2)*QA0(Mt,Q) +
     (pow(mh,2)*(-11 + (3*pow(mh,2))/
           (pow(mh,2) - pow(MW,2)) -
          (3*pow(MW,2))/(-pow(MW,2) + pow(MZ,2)))*QA0(MW,Q))/
      2. + (pow(mh,2)*(7*pow(MW,2) - 4*pow(MZ,2))*QA0(MZ,Q))/
      (2.*(-pow(MW,2) + pow(MZ,2))) +
     (9*pow(mh,4)*QB0(mh,mh,mh,Q))/4. +
     3*pow(Mt,2)*(pow(mh,2) - 4*pow(Mt,2))*QB0(mh,Mt,Mt,Q) +
     ((pow(mh,4) - 4*pow(mh,2)*pow(MW,2) + 12*pow(MW,4))*
        QB0(mh,MW,MW,Q))/2. +
     ((pow(mh,4) - 4*pow(mh,2)*pow(MZ,2) + 12*pow(MZ,4))*
      QB0(mh,MZ,MZ,Q))/4.)/(16.*pow(Pi,2)*pow(vev,4));

   const double sigma = 2 * delta_lambda * vev * vev;

   return sigma;
}

/**
 * Standard Model Higgs 2-loop contribution as used in SUSYHD 1.0.2.
 *
 * @note The result contains the 2-loop tadpole diagrams.  It is
 * therefore not 1-particle irreducible (1PI).
 *
 * @param vev Higgs Vacuum expectation value (~ 246 GeV)
 * @param Mt top quark pole mass
 * @param Mh Higgs pole mass
 * @param g3 strong gauge coupling at the top quark pole mass scale
 *    \f$Q = M_t\f$
 *
 * @return real part of 2-loop self-energy
 */
double delta_mh_2loop_sm_SUSYHD(
   double vev, double Mt, double Mh, double g3)
{
   using namespace std;

   const double Pi = M_PI;

   const double delta_lambda_QCD = pow(g3,2)*(
      -23.88 + 0.12*(-125 + Mh) - 0.64*(-173 + Mt))/(256.*pow(Pi,4));
   const double delta_lambda_EW =
      (-9.45 - 0.12*(-125 + Mh) - 0.21*(-173 + Mt))/(256.*pow(Pi,4));
   const double delta_lambda = delta_lambda_QCD + delta_lambda_EW;

   const double sigma = 2 * delta_lambda * vev * vev;

   return sigma;
}

} // namespace sm_twoloophiggs
} // namespace flexiblesusy
