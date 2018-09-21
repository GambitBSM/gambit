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

// File generated at Thu 10 May 2018 14:33:29

#include "MSSM_mAmu_mass_eigenstates.hpp"
#include "MSSM_mAmu_weinberg_angle.hpp"
#include "MSSM_mAmu_info.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "numerics2.hpp"
#include "config.h"
#include "numerics.h"
#include "error.hpp"
#include "pv.hpp"

#include <limits>
#include <cmath>

namespace flexiblesusy {

#define CLASSNAME MSSM_mAmu_weinberg_angle

#define MODEL model
#define MODELPARAMETER(p) model->get_##p()
#define INPUTPARAMETER(p) model->get_input().p
#define DERIVEDPARAMETER(p) model->p()
#define PHASE(p) model->get_##p()
#define SINTHETAW sinThetaW
#define RHOHATRATIO rhohat_ratio
#define GFERMI gfermi
#define MW mw
#define MZ mz
#define MT mt
#define ALPHAS alphaS
#define RHO2 rho_2
#define DELTARHAT1LOOP deltaRHat1Loop
#define PIZZTMZ pizzt_MZ

namespace {
const double ROOT2 = Sqrt(2.0);
} // anonymous namespace

/**
 * Sets the maximum number of iterations to 20, the number of loops to 2,
 * the precision goal to 1.0e-8, and the model pointer as well as the
 * SM parameter struct to the ones which are handed over as parameters. 
 *
 * @param model_ pointer to the model for which the calculation shall be done
 * @param sm_parameters_ struct containing the required SM parameters
 */
CLASSNAME::MSSM_mAmu_weinberg_angle(
   const MSSM_mAmu_mass_eigenstates* model_,
   const Sm_parameters& sm_parameters_)
   : model(model_)
   , sm_parameters(sm_parameters_)
{
}

void CLASSNAME::set_number_of_iterations(int n)
{
   number_of_iterations = n;
}

void CLASSNAME::set_number_of_loops(int n)
{
   number_of_loops = n;
}

void CLASSNAME::set_precision_goal(double p)
{
   precision_goal = p;
}

void CLASSNAME::enable_dvb_bsm()
{
   include_dvb_bsm = true;
}

void CLASSNAME::disable_dvb_bsm()
{
   include_dvb_bsm = false;
}

void CLASSNAME::set_model(const MSSM_mAmu_mass_eigenstates* model_)
{
   model = model_;
}

void CLASSNAME::set_sm_parameters(const Sm_parameters& sm_parameters_)
{
   sm_parameters = sm_parameters_;
}

/**
 * Calculates the DR-bar weak mixing angle \f$\sin\hat{\theta}_W\f$ as
 * defined in Eq. (C.3) from hep-ph/9606211 given the Fermi constant,
 * the Z-boson pole mass and the DR-bar electromagnetic coupling as input
 * and taking the tree-level value of the \f$\hat{\rho}\f$ parameter into account.
 * Furthermore the W boson pole mass is determined from the final result.
 *
 * The function throws an exception of type NoSinThetaWConvergenceError if the
 * iterative procedure to determine the weak mixing angle does not converge.
 *
 * @param sinThetaW_start initial guess for the sine of the weak mixing angle
 *
 * @return sine of the DR-bar weak mixing angle (#1) and W pole mass (#2)
 */
std::pair<double,double> CLASSNAME::calculate(double sinThetaW_start)
{
   const double gY = MODEL->get_g1() * MSSM_mAmu_info::normalization_g1;
   const double g2 = MODEL->get_g2() * MSSM_mAmu_info::normalization_g2;
   const double eDRbar     = gY * g2 / Sqrt(Sqr(gY) + Sqr(g2));
   const double alphaDRbar = Sqr(eDRbar) / (4.0 * Pi);
   const double mw         = sm_parameters.mw_pole;
   const double mz         = sm_parameters.mz_pole;
   const double gfermi     = sm_parameters.fermi_constant;

   pizzt_MZ = calculate_self_energy_VZ(mz);
   piwwt_MW = calculate_self_energy_VWm(mw);
   piwwt_0  = calculate_self_energy_VWm(0.);

   double rhohat_tree = calculate_rho_hat_tree();

   if (!std::isfinite(rhohat_tree)) {
#if defined(ENABLE_VERBOSE) || defined(ENABLE_DEBUG)
      WARNING("rhohat_tree non-finite");
#endif
      rhohat_tree = 1.;
   }

   int iteration = 0;
   bool not_converged = true;
   bool fudged = false;
   double sinThetaW_old = sinThetaW_start;
   double sinThetaW_new = sinThetaW_start;

   while (not_converged && iteration < number_of_iterations) {
      fudged = false;

      double deltaRhoHat = calculate_delta_rho_hat(sinThetaW_old);

      if (!std::isfinite(deltaRhoHat) || Abs(deltaRhoHat) >= 1.0) {
         fudged = true;
         deltaRhoHat = 0.;
      }

      const double rhohat_ratio = 1.0 / (1.0 - deltaRhoHat);

      double deltaRHat = calculate_delta_r_hat(rhohat_ratio, sinThetaW_old);

      if (!std::isfinite(deltaRHat) || Abs(deltaRHat) >= 1.0) {
         fudged = true;
         deltaRHat = 0.;
      }

      double sin2thetasqO4 = Pi * alphaDRbar /
         (ROOT2 * Sqr(mz) * gfermi * (1.0 - deltaRHat) * rhohat_tree);

      if (sin2thetasqO4 >= 0.25) {
         fudged = true;
         sin2thetasqO4 = 0.25;
      }

      if (sin2thetasqO4 < 0.0) {
         fudged = true;
         sin2thetasqO4 = 0.0;
      }

      const double sin2theta = Sqrt(4.0 * sin2thetasqO4);
      const double theta = 0.5 * ArcSin(sin2theta);

      sinThetaW_new = Sin(theta);

      const double precision = Abs(sinThetaW_old / sinThetaW_new - 1.0);

      VERBOSE_MSG("\t\tIteration step " << iteration
                  << ": prec=" << precision
                  << " dRhoHat=" << deltaRhoHat
                  << " rhohat_ratio=" << rhohat_ratio
                  << " dRHat=" << deltaRHat
                  << " sinThetaW_new=" << sinThetaW_new
                  << " fudged = " << fudged);

      not_converged = precision >= precision_goal;

      sinThetaW_old = sinThetaW_new;
      iteration++;
   }

   if (fudged)
      throw NonPerturbativeSinThetaW();

   if (not_converged)
      throw NoSinThetaWConvergenceError(number_of_iterations, sinThetaW_new);

   const double deltaRhoHat = calculate_delta_rho_hat(sinThetaW_new);

   if (Abs(deltaRhoHat) >= 1.0)
      throw NonPerturbativeSinThetaW();

   const double rhohat_ratio_final =
      1.0 / (1.0 - deltaRhoHat);
   const double mw_pole =
      Sqrt(Sqr(mz) * rhohat_tree * rhohat_ratio_final * (1 - Sqr(sinThetaW_new)));

   return std::make_pair(sinThetaW_new, mw_pole);
}

/**
 * Calculates the tree-level value of \f$\hat{\rho}\f$ taking contributions
 * from higher Higgs multiplets and possible \f$Z\f$-\f$Z^{\prime}\f$-mixing
 * into account.
 *
 * @return tree-level value of \f$\hat{\rho}\f$
 */
double CLASSNAME::calculate_rho_hat_tree() const
{
   double rhohat_tree = 1.;
   rhohat_tree = 1;

   return rhohat_tree;
}

/**
 * Calculates the \f$\Delta\hat{\rho}\f$ corrections as defined in
 * Eqs. (C.4), (C.6) from hep-ph/9606211 but with the dependency on 
 * rhohat eliminated.
 *
 * @param sinThetaW sin(theta_W)
 *
 * @return \f$\Delta\hat{\rho}\f$ as defined in (C.4) and (C.6) from hep-ph/9606211
 */
double CLASSNAME::calculate_delta_rho_hat(double sinThetaW) const
{
   const double gfermi = sm_parameters.fermi_constant;
   const double mw = sm_parameters.mw_pole;
   const double mz = sm_parameters.mz_pole;
   const double mt = sm_parameters.mt_pole;
   const double alphaS = sm_parameters.alpha_s;

   const double deltaRhoHat1Loop = number_of_loops > 0 ?
      1 - (1 + piwwt_MW / Sqr(mw)) / (1 + pizzt_MZ / Sqr(mz)) : 0.;

   std::complex<double> deltaRhoHat2LoopSM(0., 0.);

   if (number_of_loops > 1) {
      if (Abs(1. - model->get_scale() / mz) > 0.1) {
#if defined(ENABLE_VERBOSE) || defined(ENABLE_DEBUG)
         WARNING("scale deviates from value mz_pole assumed in deltaRhoHat2LoopSM");
#endif
      }

      const auto g1 = MODELPARAMETER(g1);
      const auto g2 = MODELPARAMETER(g2);
      const auto vd = MODELPARAMETER(vd);
      const auto vu = MODELPARAMETER(vu);
      const auto Yu = MODELPARAMETER(Yu);
      const auto ZUL = MODELPARAMETER(ZUL);
      const auto ZUR = MODELPARAMETER(ZUR);
      const auto ZA = MODELPARAMETER(ZA);
      const auto ZH = MODELPARAMETER(ZH);
      const auto MAh = MODELPARAMETER(MAh);
      const auto Mhh = MODELPARAMETER(Mhh);

      deltaRhoHat2LoopSM = (6.015223977354103e-6*((64*ALPHAS*Pi*Sqr(g1)*Sqr(g2)*(
         -2.24 + 1.262*Log(MT/MZ) - (2.145*Sqr(MT))/Sqr(MW) - (0.85*Sqr(MZ))/Sqr(MT))
         )/((0.6*Sqr(g1) + Sqr(g2))*Sqr(SINTHETAW)) + 5*Sqr(GFERMI)*Sqr(MT)*(Sqr(vd)
         + Sqr(vu))*(RHO2(MAh(1)/MT)*(Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2,
         Conj(ZUR(2,j1))*Yu(j1,j2))) - SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1
         ))*ZUL(2,j2)))*ZA(1,1))) - Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2,
         Conj(ZUR(2,j1))*Yu(j1,j2))) + SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1
         ))*ZUL(2,j2)))*ZA(1,1)))) - RHO2(Mhh(0)/MT)*(Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,
         j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) - SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(
         j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(0,1))) - Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2
         ))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) + SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1
         ,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(0,1)))) - RHO2(Mhh(1)/MT)*(Sqr(Abs((SUM(j2,0
         ,2,Conj(ZUL(2,j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) - SUM(j2,0,2,SUM(
         j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(1,1))) - Sqr(Abs((SUM(j2,0,
         2,Conj(ZUL(2,j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) + SUM(j2,0,2,SUM(j1
         ,0,2,Conj(Yu(j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(1,1)))))))/(1 + PIZZTMZ/Sqr(
         MZ));
   }

   const double deltaRhoHat2LoopSMreal = std::real(deltaRhoHat2LoopSM);

   const double deltaRhoHat = deltaRhoHat1Loop + deltaRhoHat2LoopSMreal;

   return deltaRhoHat;
}

/**
 * Calculates the \f$\Delta\hat{r}\f$ corrections as defined in
 * Eqs. (C.3), (C.5) from hep-ph/9606211 taking the tree-level
 * value of the rhohat parameter into account.
 *
 * @param rhohat_ratio = rhohat / rhohat_tree
 * @param sinThetaW sin(theta_W)
 *
 * @return \f$\Delta\hat{r}\f$ as defined in (C.3) and (C.5) from hep-ph/9606211
 */
double CLASSNAME::calculate_delta_r_hat(double rhohat_ratio, double sinThetaW) const
{
   const double gfermi = sm_parameters.fermi_constant;
   const double mw = sm_parameters.mw_pole;
   const double mz = sm_parameters.mz_pole;
   const double mt = sm_parameters.mt_pole;
   const double alphaS = sm_parameters.alpha_s;

   const double dvb = number_of_loops > 0 ?
      calculate_delta_vb(rhohat_ratio, sinThetaW) : 0.;

   const double deltaRHat1Loop = number_of_loops > 0 ?
      rhohat_ratio * piwwt_0 / Sqr(mw) - pizzt_MZ / Sqr(mz) + dvb : 0.;

   std::complex<double> deltaRHat2LoopSM(0., 0.);

   if (number_of_loops > 1) {
      if (Abs(1. - model->get_scale() / mz) > 0.1) {
#if defined(ENABLE_VERBOSE) || defined(ENABLE_DEBUG)
         WARNING("scale deviates from value mz_pole assumed in deltaRHat2LoopSM");
#endif
      }

      const auto g1 = MODELPARAMETER(g1);
      const auto g2 = MODELPARAMETER(g2);
      const auto vd = MODELPARAMETER(vd);
      const auto vu = MODELPARAMETER(vu);
      const auto Yu = MODELPARAMETER(Yu);
      const auto ZUL = MODELPARAMETER(ZUL);
      const auto ZUR = MODELPARAMETER(ZUR);
      const auto ZA = MODELPARAMETER(ZA);
      const auto ZH = MODELPARAMETER(ZH);
      const auto MAh = MODELPARAMETER(MAh);
      const auto Mhh = MODELPARAMETER(Mhh);

      deltaRHat2LoopSM = 6.015223977354103e-6*((64*ALPHAS*Pi*Sqr(g1)*Sqr(g2)*(
         -0.224 + 0.575*Log(MT/MZ) + (2.145*Sqr(MT))/Sqr(MZ) - (0.144*Sqr(MZ))/Sqr(MT
         )))/((0.6*Sqr(g1) + Sqr(g2))*(1 - Sqr(SINTHETAW))*Sqr(SINTHETAW)) - 5*(1 -
         DELTARHAT1LOOP)*RHOHATRATIO*Sqr(GFERMI)*Sqr(MT)*(Sqr(vd) + Sqr(vu))*(RHO2(
         MAh(1)/MT)*(Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*
         Yu(j1,j2))) - SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*
         ZA(1,1))) - Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*
         Yu(j1,j2))) + SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*
         ZA(1,1)))) - RHO2(Mhh(0)/MT)*(Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2
         ,Conj(ZUR(2,j1))*Yu(j1,j2))) - SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,
         j1))*ZUL(2,j2)))*ZH(0,1))) - Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2))*SUM(j1,0,2,
         Conj(ZUR(2,j1))*Yu(j1,j2))) + SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1,j2))*ZUR(2,j1
         ))*ZUL(2,j2)))*ZH(0,1)))) - RHO2(Mhh(1)/MT)*(Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,
         j2))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) - SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(
         j1,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(1,1))) - Sqr(Abs((SUM(j2,0,2,Conj(ZUL(2,j2
         ))*SUM(j1,0,2,Conj(ZUR(2,j1))*Yu(j1,j2))) + SUM(j2,0,2,SUM(j1,0,2,Conj(Yu(j1
         ,j2))*ZUR(2,j1))*ZUL(2,j2)))*ZH(1,1))))));
   }

   const double deltaRHat2LoopSMreal = std::real(deltaRHat2LoopSM);

   const double deltaRHat = deltaRHat1Loop + deltaRHat2LoopSMreal;

   return deltaRHat;
}

/**
 * Calculates the vertex, box and external wave-function renormalization
 * corrections \f$\delta_{\text{VB}}\f$ for the specific model as e.g.
 * given in Eqs. (C.11)-(C.16), (C.20) from hep-ph/9606211 for the MSSM.
 *
 * @param rhohat_ratio = rhohat / rhohat_tree
 * @param sinThetaW sin(theta_W)
 *
 * @return \f$\delta_{\text{VB}}\f$
 */
double CLASSNAME::calculate_delta_vb(double rhohat_ratio, double sinThetaW) const
{
   const double deltaVbSM = calculate_delta_vb_sm(sinThetaW);

   const double deltaVbBSM = include_dvb_bsm ?
      calculate_delta_vb_bsm(sinThetaW) : 0.;

   const double deltaVb = rhohat_ratio * (deltaVbSM + deltaVbBSM);

   return deltaVb;
}

/**
 * Calculates the Standard Model vertex and box corrections
 * \f$\delta_{\text{VB}}^{\text{SM}}\f$ as given in Eq. (C.12) from
 * hep-ph/9606211 taking the tree-level value of the rhohat parameter
 * into account.
 *
 * @param sinThetaW sin(theta_W)
 *
 * @return \f$\delta_{\text{VB}}^{\text{SM}}\f$ as defined in (C.12)
 * from hep-ph/9606211
 */
double CLASSNAME::calculate_delta_vb_sm(double sinThetaW) const
{
   const double mz  = sm_parameters.mz_pole;
   const double mw  = sm_parameters.mw_pole;
   const double cw2 = Sqr(mw / mz);
   const double sw2 = 1.0 - cw2;
   const double sinThetaW2 = Sqr(sinThetaW);
   const double outcos2    = 1.0 - sinThetaW2;
   const double q   = model->get_scale();

   const double gY = MODEL->get_g1() * MSSM_mAmu_info::normalization_g1;
   const double g2 = MODEL->get_g2() * MSSM_mAmu_info::normalization_g2;
   const double eDRbar     = gY * g2 / Sqrt(Sqr(gY) + Sqr(g2));
   const double alphaDRbar = Sqr(eDRbar) / (4.0 * Pi);

   const double deltaVbSM = alphaDRbar / (4.0 * Pi * sinThetaW2) *
      (6.0 + log(cw2) / sw2 *
       (3.5 - 2.5 * sw2 - sinThetaW2 * (5.0 - 1.5 * cw2 / outcos2))
       - 4. * Log(Sqr(mz/q)));

   return deltaVbSM;
}

/**
 * Calculates the BSM vertex, box and external wave-function renormalization
 * corrections \f$\delta_{\text{VB}}^{\text{BSM}}\f$ for the specific model
 * as e.g. given in Eqs. (C.13)-(C.16), (C.20) from hep-ph/9606211 for the MSSM.
 *
 * @param sinThetaW sin(theta_W)
 *
 * @return \f$\delta_{\text{VB}}^{\text{BSM}}\f$
 */
double CLASSNAME::calculate_delta_vb_bsm(double sinThetaW) const
{
   const double mz = sm_parameters.mz_pole;
   const double gY = MODEL->get_g1() * MSSM_mAmu_info::normalization_g1;
   const double g2 = MODEL->get_g2() * MSSM_mAmu_info::normalization_g2;
   const double sinThetaW2 = Sqr(sinThetaW);
   const double outcos2    = 1.0 - sinThetaW2;

   const double eDRbar     = gY * g2 / Sqrt(Sqr(gY) + Sqr(g2));
   const double alphaDRbar = Sqr(eDRbar) / (4.0 * Pi);

   const std::complex<double> a1 = delta_vb_box(1, 1, 0, 0);
   const std::complex<double> deltaV =
      delta_vb_vertex(0, 0) + delta_vb_vertex(1, 1);
   const std::complex<double> deltaZ =
      delta_vb_wave_Fv(0) + delta_vb_wave_Fv(1) + delta_vb_wave_Fe(0) + delta_vb_wave_Fe(1);

   const double deltaVbBSM = oneOver16PiSqr *
      (- sinThetaW2 * outcos2 / (2.0 * Pi * alphaDRbar) * Sqr(mz) * a1.real() +
       deltaV.real() + 0.5 * deltaZ.real());

   return deltaVbBSM;
}

/**
 * Routines for computation of couplings and terms included in
 * \f$\delta_{\text{VB}}^{\text{BSM}}\f$
 */

std::complex<double> CLASSNAME::CpAhHpmconjVWm(int gI2, int gI1) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZA = MODELPARAMETER(ZA);
   const auto ZP = MODELPARAMETER(ZP);

   const std::complex<double> result = std::complex<double>(0,0.5)*g2*(ZA(gI2,0
      )*ZP(gI1,0) + ZA(gI2,1)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CphhHpmconjVWm(int gI2, int gI1) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZH = MODELPARAMETER(ZH);
   const auto ZP = MODELPARAMETER(ZP);

   const std::complex<double> result = -0.5*g2*(ZH(gI2,0)*ZP(gI1,0) - ZH(gI2,1)
      *ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFvFeconjVWmPL(int gI1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZEL = MODELPARAMETER(ZEL);

   const std::complex<double> result = IF(gI1 < 3,-0.7071067811865475*g2*Conj(
      ZEL(gI2,gI1)),0);

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSvconjVWm(int gI2, int gI1) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZE = MODELPARAMETER(ZE);
   const auto ZV = MODELPARAMETER(ZV);

   const std::complex<double> result = 0.7071067811865475*g2*SUM(j1,0,2,Conj(ZE
      (gI2,j1))*ZV(gI1,j1));

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjVWmPL(int gI1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto UM = MODELPARAMETER(UM);
   const auto ZN = MODELPARAMETER(ZN);

   const std::complex<double> result = -0.5*g2*(2*Conj(UM(gI2,0))*ZN(gI1,1) +
      1.4142135623730951*Conj(UM(gI2,1))*ZN(gI1,2));

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjVWmPR(int gI1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZN = MODELPARAMETER(ZN);
   const auto UP = MODELPARAMETER(UP);

   const std::complex<double> result = -(g2*Conj(ZN(gI1,1))*UP(gI2,0)) +
      0.7071067811865475*g2*Conj(ZN(gI1,3))*UP(gI2,1);

   return result;
}

double CLASSNAME::CpbarFvFeconjHpmPL(int , int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvFeconjHpmPR(int gO1, int gI2, int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZP = MODELPARAMETER(ZP);

   const std::complex<double> result = SUM(j1,0,2,Conj(Ye(j1,gO1))*ZER(gI2,j1))
      *ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarChabarFvSePR(int gI1, int gO1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZE = MODELPARAMETER(ZE);
   const auto UM = MODELPARAMETER(UM);

   const std::complex<double> result = IF(gO1 < 3,-(g2*Conj(ZE(gI2,gO1))*UM(gI1
      ,0)),0) + SUM(j1,0,2,Conj(Ye(j1,gO1))*Conj(ZE(gI2,3 + j1)))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFvChiSvPR(int gO1, int gI2, int gI1) const
{
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto ZV = MODELPARAMETER(ZV);
   const auto ZN = MODELPARAMETER(ZN);

   const std::complex<double> result = IF(gO1 < 3,0.5477225575051661*g1*Conj(ZV
      (gI1,gO1))*ZN(gI2,0),0) + IF(gO1 < 3,-0.7071067811865475*g2*Conj(ZV(gI1,gO1)
      )*ZN(gI2,1),0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFehhPL(int gO2, int gI2, int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZH = MODELPARAMETER(ZH);

   const std::complex<double> result = -0.7071067811865475*SUM(j2,0,2,Conj(ZEL(
      gI2,j2))*SUM(j1,0,2,Conj(ZER(gO2,j1))*Ye(j1,j2)))*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFehhPR(int gO1, int gI2, int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZH = MODELPARAMETER(ZH);

   const std::complex<double> result = -0.7071067811865475*SUM(j2,0,2,SUM(j1,0,
      2,Conj(Ye(j1,j2))*ZER(gI2,j1))*ZEL(gO1,j2))*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFvHpmPL(int gO2, int gI2, int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZP = MODELPARAMETER(ZP);

   const std::complex<double> result = SUM(j1,0,2,Conj(ZER(gO2,j1))*Ye(j1,gI2))
      *ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFeFvHpmPR(int , int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChaSvPR(int gO1, int gI2, int gI1) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto ZV = MODELPARAMETER(ZV);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto UP = MODELPARAMETER(UP);

   const std::complex<double> result = -(g2*SUM(j1,0,2,Conj(ZV(gI1,j1))*ZEL(gO1
      ,j1))*UP(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeAhPL(int gO2, int gI1, int gI2) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZA = MODELPARAMETER(ZA);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*SUM(j2,0,2,Conj(ZEL(gI1,j2))*SUM(j1,0,2,Conj(ZER(gO2,j1
      ))*Ye(j1,j2)))*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeAhPR(int gO1, int gI1, int gI2) const
{
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZER = MODELPARAMETER(ZER);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZA = MODELPARAMETER(ZA);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*SUM(j2,0,2,SUM(j1,0,2,Conj(Ye(j1,j2))*ZER(gI1,j1))*ZEL(
      gO1,j2))*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChiSePR(int gO1, int gI2, int gI1) const
{
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZE = MODELPARAMETER(ZE);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZN = MODELPARAMETER(ZN);

   const std::complex<double> result = 0.7071067811865475*SUM(j1,0,2,Conj(ZE(
      gI1,j1))*ZEL(gO1,j1))*(0.7745966692414834*g1*ZN(gI2,0) + g2*ZN(gI2,1)) - SUM
      (j2,0,2,SUM(j1,0,2,Conj(Ye(j1,j2))*Conj(ZE(gI1,3 + j1)))*ZEL(gO1,j2))*ZN(gI2
      ,2);

   return result;
}

std::complex<double> CLASSNAME::CpChaFvconjSePL(int gI1, int gO1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto Ye = MODELPARAMETER(Ye);
   const auto UM = MODELPARAMETER(UM);
   const auto ZE = MODELPARAMETER(ZE);

   const std::complex<double> result = IF(gO1 < 3,-(g2*Conj(UM(gI1,0))*ZE(gI2,
      gO1)),0) + Conj(UM(gI1,1))*SUM(j1,0,2,Ye(j1,gO1)*ZE(gI2,3 + j1));

   return result;
}

std::complex<double> CLASSNAME::CpChiFvconjSvPL(int gI1, int gO1, int gI2) const
{
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto ZN = MODELPARAMETER(ZN);
   const auto ZV = MODELPARAMETER(ZV);

   const std::complex<double> result = IF(gO1 < 3,0.5477225575051661*g1*Conj(ZN
      (gI1,0))*ZV(gI2,gO1),0) + IF(gO1 < 3,-0.7071067811865475*g2*Conj(ZN(gI1,1))*
      ZV(gI2,gO1),0);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFeconjSvPL(int gI1, int gO1, int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto UP = MODELPARAMETER(UP);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZV = MODELPARAMETER(ZV);

   const std::complex<double> result = -(g2*Conj(UP(gI1,0))*SUM(j1,0,2,Conj(ZEL
      (gO1,j1))*ZV(gI2,j1)));

   return result;
}

std::complex<double> CLASSNAME::CpChiFeconjSePL(int gI1, int gO1, int gI2) const
{
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto Ye = MODELPARAMETER(Ye);
   const auto ZN = MODELPARAMETER(ZN);
   const auto ZEL = MODELPARAMETER(ZEL);
   const auto ZE = MODELPARAMETER(ZE);

   const std::complex<double> result = 0.5477225575051661*g1*Conj(ZN(gI1,0))*
      SUM(j1,0,2,Conj(ZEL(gO1,j1))*ZE(gI2,j1)) + 0.7071067811865475*g2*Conj(ZN(gI1
      ,1))*SUM(j1,0,2,Conj(ZEL(gO1,j1))*ZE(gI2,j1)) - Conj(ZN(gI1,2))*SUM(j2,0,2,
      Conj(ZEL(gO1,j2))*SUM(j1,0,2,Ye(j1,j2)*ZE(gI2,3 + j1)));

   return result;
}


std::complex<double> CLASSNAME::delta_vb_wave_Fv(int gO1) const
{
   const auto MCha = MODELPARAMETER(MCha);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MChi = MODELPARAMETER(MChi);
   const auto MSv = MODELPARAMETER(MSv);
   const auto MFe = MODELPARAMETER(MFe);
   const auto MHpm = MODELPARAMETER(MHpm);

   const std::complex<double> result = SUM(gI1,0,1,SUM(gI2,0,5,-(AbsSqr(
      CpChaFvconjSePL(gI1,gO1,gI2))*B1(0,Sqr(MCha(gI1)),Sqr(MSe(gI2)))))) + SUM(
      gI1,0,3,SUM(gI2,0,2,-(AbsSqr(CpChiFvconjSvPL(gI1,gO1,gI2))*B1(0,Sqr(MChi(gI1
      )),Sqr(MSv(gI2)))))) + SUM(gI1,1,1,SUM(gI2,0,2,-(AbsSqr(CpbarFeFvHpmPL(gI2,
      gO1,gI1))*B1(0,Sqr(MFe(gI2)),Sqr(MHpm(gI1))))));

   return result;
}

std::complex<double> CLASSNAME::delta_vb_wave_Fe(int gO1) const
{
   const auto MCha = MODELPARAMETER(MCha);
   const auto MSv = MODELPARAMETER(MSv);
   const auto MFe = MODELPARAMETER(MFe);
   const auto Mhh = MODELPARAMETER(Mhh);
   const auto MFv = MODELPARAMETER(MFv);
   const auto MHpm = MODELPARAMETER(MHpm);
   const auto MChi = MODELPARAMETER(MChi);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MAh = MODELPARAMETER(MAh);

   const std::complex<double> result = SUM(gI1,0,1,SUM(gI2,0,2,-(AbsSqr(
      CpbarChaFeconjSvPL(gI1,gO1,gI2))*B1(0,Sqr(MCha(gI1)),Sqr(MSv(gI2)))))) + SUM
      (gI1,0,1,SUM(gI2,0,2,-(AbsSqr(CpbarFeFehhPL(gI2,gO1,gI1))*B1(0,Sqr(MFe(gI2))
      ,Sqr(Mhh(gI1)))))) + SUM(gI1,0,2,SUM(gI2,1,1,-(AbsSqr(CpbarFvFeconjHpmPL(gI1
      ,gO1,gI2))*B1(0,Sqr(MFv(gI1)),Sqr(MHpm(gI2)))))) + SUM(gI1,0,3,SUM(gI2,0,5,-
      (AbsSqr(CpChiFeconjSePL(gI1,gO1,gI2))*B1(0,Sqr(MChi(gI1)),Sqr(MSe(gI2))))))
      + SUM(gI1,1,1,SUM(gI2,0,2,-(AbsSqr(CpbarFeFeAhPL(gI2,gO1,gI1))*B1(0,Sqr(MFe(
      gI2)),Sqr(MAh(gI1))))));

   return result;
}

std::complex<double> CLASSNAME::delta_vb_vertex(int gO1, int gO2) const
{
   const auto MCha = MODELPARAMETER(MCha);
   const auto MChi = MODELPARAMETER(MChi);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MSv = MODELPARAMETER(MSv);
   const auto MHpm = MODELPARAMETER(MHpm);
   const auto Mhh = MODELPARAMETER(Mhh);
   const auto MFe = MODELPARAMETER(MFe);
   const auto MAh = MODELPARAMETER(MAh);

   const std::complex<double> result = (SUM(gI1,0,1,SUM(gI2,0,3,SUM(gI3,0,5,
      CpbarChabarFvSePR(gI1,gO2,gI3)*CpChiFeconjSePL(gI2,gO1,gI3)*(C0(Sqr(MSe(gI3)
      ),Sqr(MCha(gI1)),Sqr(MChi(gI2)))*CpChiChaconjVWmPR(gI2,gI1)*MCha(gI1)*MChi(
      gI2) - 0.5*CpChiChaconjVWmPL(gI2,gI1)*(-0.5 + B0(0,Sqr(MCha(gI1)),Sqr(MChi(
      gI2))) + C0(Sqr(MSe(gI3)),Sqr(MCha(gI1)),Sqr(MChi(gI2)))*Sqr(MSe(gI3)))))))
      + SUM(gI1,0,2,SUM(gI2,0,5,SUM(gI3,0,3,-0.5*CpbarFvChiSvPR(gO2,gI3,gI1)*
      CpChiFeconjSePL(gI3,gO1,gI2)*CpSeconjSvconjVWm(gI2,gI1)*(0.5 + B0(0,Sqr(MSv(
      gI1)),Sqr(MSe(gI2))) + C0(Sqr(MChi(gI3)),Sqr(MSv(gI1)),Sqr(MSe(gI2)))*Sqr(
      MChi(gI3)))))) + SUM(gI1,0,3,SUM(gI2,0,1,SUM(gI3,0,2,CpbarChaFeconjSvPL(gI2,
      gO1,gI3)*CpbarFvChiSvPR(gO2,gI1,gI3)*(-(C0(Sqr(MSv(gI3)),Sqr(MChi(gI1)),Sqr(
      MCha(gI2)))*CpChiChaconjVWmPL(gI1,gI2)*MCha(gI2)*MChi(gI1)) + 0.5*
      CpChiChaconjVWmPR(gI1,gI2)*(-0.5 + B0(0,Sqr(MChi(gI1)),Sqr(MCha(gI2))) + C0(
      Sqr(MSv(gI3)),Sqr(MChi(gI1)),Sqr(MCha(gI2)))*Sqr(MSv(gI3))))))) + SUM(gI1,1,
      1,SUM(gI2,0,1,SUM(gI3,0,2,-0.5*CpbarFeFehhPL(gI3,gO1,gI2)*CpbarFvFeconjHpmPR
      (gO2,gI3,gI1)*CphhHpmconjVWm(gI2,gI1)*(0.5 + B0(0,Sqr(MHpm(gI1)),Sqr(Mhh(gI2
      ))) + C0(Sqr(MFe(gI3)),Sqr(MHpm(gI1)),Sqr(Mhh(gI2)))*Sqr(MFe(gI3)))))) + SUM
      (gI1,1,1,SUM(gI2,1,1,SUM(gI3,0,2,-0.5*CpAhHpmconjVWm(gI2,gI1)*CpbarFeFeAhPL(
      gI3,gO1,gI2)*CpbarFvFeconjHpmPR(gO2,gI3,gI1)*(0.5 + B0(0,Sqr(MHpm(gI1)),Sqr(
      MAh(gI2))) + C0(Sqr(MFe(gI3)),Sqr(MHpm(gI1)),Sqr(MAh(gI2)))*Sqr(MFe(gI3)))))
      ))/CpbarFvFeconjVWmPL(gO2,gO1);

   return result;
}

std::complex<double> CLASSNAME::delta_vb_box(int gO1, int gO2, int gO3, int gO4) const
{
   const auto MCha = MODELPARAMETER(MCha);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MSv = MODELPARAMETER(MSv);
   const auto MChi = MODELPARAMETER(MChi);
   const auto MFe = MODELPARAMETER(MFe);
   const auto MHpm = MODELPARAMETER(MHpm);
   const auto Mhh = MODELPARAMETER(Mhh);
   const auto MAh = MODELPARAMETER(MAh);
   const auto MFv = MODELPARAMETER(MFv);

   const std::complex<double> result = SUM(gI1,0,1,SUM(gI2,0,5,SUM(gI3,0,1,SUM(
      gI4,0,2,0.5*CpbarChabarFvSePR(gI3,gO2,gI2)*CpbarChaFeconjSvPL(gI1,gO1,gI4)*
      CpbarFeChaSvPR(gO4,gI3,gI4)*CpChaFvconjSePL(gI1,gO3,gI2)*D0(Sqr(MCha(gI1)),
      Sqr(MSe(gI2)),Sqr(MCha(gI3)),Sqr(MSv(gI4)))*MCha(gI1)*MCha(gI3))))) + SUM(
      gI1,0,2,SUM(gI2,0,3,SUM(gI3,0,2,SUM(gI4,0,1,CpbarChaFeconjSvPL(gI4,gO1,gI1)*
      CpbarFeChaSvPR(gO4,gI4,gI3)*CpbarFvChiSvPR(gO2,gI2,gI1)*CpChiFvconjSvPL(gI2,
      gO3,gI3)*D27(Sqr(MSv(gI1)),Sqr(MChi(gI2)),Sqr(MSv(gI3)),Sqr(MCha(gI4)))))))
      + SUM(gI1,0,2,SUM(gI2,0,3,SUM(gI3,0,5,SUM(gI4,0,1,0.5*CpbarChaFeconjSvPL(gI4
      ,gO1,gI1)*CpbarFeChiSePR(gO4,gI2,gI3)*CpbarFvChiSvPR(gO2,gI2,gI1)*
      CpChaFvconjSePL(gI4,gO3,gI3)*D0(Sqr(MSv(gI1)),Sqr(MChi(gI2)),Sqr(MSe(gI3)),
      Sqr(MCha(gI4)))*MCha(gI4)*MChi(gI2))))) + SUM(gI1,0,2,SUM(gI2,1,1,SUM(gI3,0,
      2,SUM(gI4,0,1,CpbarFeFehhPL(gI1,gO1,gI4)*CpbarFeFehhPR(gO4,gI3,gI4)*
      CpbarFeFvHpmPL(gI3,gO3,gI2)*CpbarFvFeconjHpmPR(gO2,gI1,gI2)*D27(Sqr(MFe(gI1)
      ),Sqr(MHpm(gI2)),Sqr(MFe(gI3)),Sqr(Mhh(gI4))))))) + SUM(gI1,0,2,SUM(gI2,1,1,
      SUM(gI3,0,2,SUM(gI4,1,1,CpbarFeFeAhPL(gI1,gO1,gI4)*CpbarFeFeAhPR(gO4,gI3,gI4
      )*CpbarFeFvHpmPL(gI3,gO3,gI2)*CpbarFvFeconjHpmPR(gO2,gI1,gI2)*D27(Sqr(MFe(
      gI1)),Sqr(MHpm(gI2)),Sqr(MFe(gI3)),Sqr(MAh(gI4))))))) + SUM(gI1,0,3,SUM(gI2,
      0,2,SUM(gI3,0,3,SUM(gI4,0,5,CpbarFeChiSePR(gO4,gI3,gI4)*CpbarFvChiSvPR(gO2,
      gI1,gI2)*CpChiFeconjSePL(gI1,gO1,gI4)*CpChiFvconjSvPL(gI3,gO3,gI2)*D27(Sqr(
      MChi(gI1)),Sqr(MSv(gI2)),Sqr(MChi(gI3)),Sqr(MSe(gI4))))))) + SUM(gI1,0,3,SUM
      (gI2,0,2,SUM(gI3,0,3,SUM(gI4,0,5,0.5*CpbarFeChiSePR(gO4,gI3,gI4)*
      CpbarFvChiSvPR(gO2,gI3,gI2)*CpChiFeconjSePL(gI1,gO1,gI4)*CpChiFvconjSvPL(gI1
      ,gO3,gI2)*D0(Sqr(MChi(gI1)),Sqr(MSv(gI2)),Sqr(MChi(gI3)),Sqr(MSe(gI4)))*MChi
      (gI1)*MChi(gI3))))) + SUM(gI1,0,5,SUM(gI2,0,1,SUM(gI3,0,2,SUM(gI4,0,3,0.5*
      CpbarChabarFvSePR(gI2,gO2,gI1)*CpbarFeChaSvPR(gO4,gI2,gI3)*CpChiFeconjSePL(
      gI4,gO1,gI1)*CpChiFvconjSvPL(gI4,gO3,gI3)*D0(Sqr(MSe(gI1)),Sqr(MCha(gI2)),
      Sqr(MSv(gI3)),Sqr(MChi(gI4)))*MCha(gI2)*MChi(gI4))))) + SUM(gI1,0,5,SUM(gI2,
      0,1,SUM(gI3,0,5,SUM(gI4,0,3,CpbarChabarFvSePR(gI2,gO2,gI1)*CpbarFeChiSePR(
      gO4,gI4,gI3)*CpChaFvconjSePL(gI2,gO3,gI3)*CpChiFeconjSePL(gI4,gO1,gI1)*D27(
      Sqr(MSe(gI1)),Sqr(MCha(gI2)),Sqr(MSe(gI3)),Sqr(MChi(gI4))))))) + SUM(gI1,1,1
      ,SUM(gI2,0,2,SUM(gI3,1,1,SUM(gI4,0,2,-(CpbarFeFvHpmPL(gI2,gO3,gI1)*
      CpbarFeFvHpmPR(gO4,gI4,gI3)*CpbarFvFeconjHpmPL(gI4,gO1,gI1)*
      CpbarFvFeconjHpmPR(gO2,gI2,gI3)*D27(Sqr(MHpm(gI1)),Sqr(MFe(gI2)),Sqr(MHpm(
      gI3)),Sqr(MFv(gI4))))))));

   return result;
}


/**
 * Wrapper routines for Passarino-Veltman loop functions
 */

double CLASSNAME::B0(double p2, double m12, double m22) const noexcept
{
   return passarino_veltman::ReB0(p2, m12, m22, Sqr(model->get_scale()));
}

double CLASSNAME::B1(double p2, double m12, double m22) const noexcept
{
   return -1. * passarino_veltman::ReB1(p2, m12, m22, Sqr(model->get_scale()));
}

double CLASSNAME::C0(double m12, double m22, double m32) const noexcept
{
   return softsusy::c0(std::sqrt(m12), std::sqrt(m22), std::sqrt(m32));
}

double CLASSNAME::D0(double m12, double m22, double m32, double m42) const noexcept
{
   return softsusy::d0(std::sqrt(m12), std::sqrt(m22), std::sqrt(m32), std::sqrt(m42));
}

double CLASSNAME::D27(double m12, double m22, double m32, double m42) const noexcept
{
   return softsusy::d27(std::sqrt(m12), std::sqrt(m22), std::sqrt(m32), std::sqrt(m42));
}

/**
 * Calculates \f$\rho^{(2)}(r)\f$ as given in Eqs. (C.7)-(C.8) from
 * hep-ph/9606211.
 *
 * @param r ratio of Higgs mass over top quark mass
 *
 * @return \f$\rho^{(2)}(r)\f$
 */
double CLASSNAME::rho_2(double r)
{
   const double Pi2 = Pi * Pi;
   const double logr = Log(r);

   if (r <= std::numeric_limits<double>::epsilon()) {
#if defined(ENABLE_VERBOSE) || defined(ENABLE_DEBUG)
      WARNING("rho_2: value of r is invalid: r = " << r);
      WARNING("-> setting 2-loop corrections ~ xt^2 to 0");
#endif
      return 0.;
   }

   if (r <= 1.9) {
      const double r2 = Sqr(r);
      return 19.0 - 16.5 * r + 43.0 / 12.0 * r2 + 7.0 / 120.0 * r2 * r -
         Pi * Sqrt(r) * (4.0 - 1.5 * r + 3.0 / 32.0 * r2 + r2 * r / 256.0) -
         Pi2 * (2.0 - 2.0 * r + 0.5 * r2) - logr * (3.0 * r - 0.5 * r2);
   } else {
      const double rm1 = 1.0 / r, rm2 = Sqr(rm1), rm3 = rm2 * rm1,
         rm4 = rm3 * rm1, rm5 = rm4 * rm1;
      return Sqr(logr) * (1.5 - 9.0 * rm1 - 15.0 * rm2 - 48.0 * rm3 -
                            168.0 * rm4 - 612.0 * rm5) -
         logr * (13.5 + 4.0 * rm1 - 125.0 / 4.0 * rm2 - 558.0 / 5.0 * rm3 -
                   8307.0 / 20.0 * rm4 - 109321.0 / 70.0 * rm5) +
         Pi2 * (1.0 - 4.0 * rm1 - 5.0 * rm2 - 16.0 * rm3 -
                56.0 * rm4 - 204.0 * rm5) +
         49.0 / 4.0 + 2.0 / 3.0 * rm1 + 1613.0 / 48.0 * rm2 + 87.57 * rm3 +
         341959.0 / 1200.0 * rm4 + 9737663.0 / 9800.0 * rm5;
   }
}

/**
 * Calculates 1-loop transverse Z boson self-energy
 * including the correction from usage of pole instead of DRbar top-quark mass.
 *
 * @param p momentum
 *
 * @return 1-loop transverse Z boson self-energy
 */
double CLASSNAME::calculate_self_energy_VZ(double p) const
{
   const double mt      = sm_parameters.mt_pole;
   const double mtDRbar = MODEL->get_MFu(2);
   const double pizzt   = Re(model->self_energy_VZ_1loop(p));

   double pizzt_corrected = pizzt;

   if (model->get_thresholds() > 1) {
      pizzt_corrected =
         pizzt - calculate_self_energy_VZ_top(p, mtDRbar)
               + calculate_self_energy_VZ_top(p, mt);
   }

   return pizzt_corrected;
}

/**
 * Calculates 1-loop transverse W boson self-energy
 * including the correction from usage of pole instead of DRbar top-quark mass.
 *
 * @param p momentum
 *
 * @return 1-loop transverse W boson self-energy
 */
double CLASSNAME::calculate_self_energy_VWm(double p) const
{
   const double mt      = sm_parameters.mt_pole;
   const double mtDRbar = MODEL->get_MFu(2);
   const double piwwt   = Re(model->self_energy_VWm_1loop(p));

   double piwwt_corrected = piwwt;

   if (model->get_thresholds() > 1) {
      piwwt_corrected =
         piwwt - calculate_self_energy_VWm_top(p, mtDRbar)
               + calculate_self_energy_VWm_top(p, mt);
   }

   return piwwt_corrected;
}

/**
 * Calculates 1-loop top-quark contribution to Z boson self-energy.
 *
 * @param p momentum
 * @param mt top-quark mass
 *
 * @return 1-loop top-quark contribution to Z boson self-energy
 */
double CLASSNAME::calculate_self_energy_VZ_top(double p, double mt) const
{
   const double q  = model->get_scale();
   const double Nc = 3.0;
   const double gY = MODEL->get_g1() * MSSM_mAmu_info::normalization_g1;
   const double g2 = MODEL->get_g2() * MSSM_mAmu_info::normalization_g2;
   const double gY2 = Sqr(gY);
   const double g22 = Sqr(g2);
   const double sw2 = gY2 / (gY2 + g22);
   const double cw2 = 1.0 - sw2;
   const double guL = 0.5 - 2.0 * sw2 / 3.0;
   const double guR = 2.0 * sw2 / 3.0;

   const double self_energy_z_top =
      Nc * Sqr(g2) / cw2 * oneOver16PiSqr *
      (softsusy::hfn(p, mt, mt, q) * (Sqr(guL) + Sqr(guR)) -
       4.0 * guL * guR * Sqr(mt) * softsusy::b0(p, mt, mt, q));

   return self_energy_z_top;
}

/**
 * Calculates 1-loop top-quark contribution to W boson self-energy.
 *
 * @param p momentum
 * @param mt top-quark mass
 *
 * @return 1-loop top-quark contribution to W boson self-energy
 */
double CLASSNAME::calculate_self_energy_VWm_top(double p, double mt) const
{
   const double q  = model->get_scale();
   const double mb = MODEL->get_MFd(2);
   const double Nc = 3.0;
   const double g2 = MODEL->get_g2() * MSSM_mAmu_info::normalization_g2;

   const double self_energy_w_top =
      0.5 * Nc * softsusy::hfn(p, mt, mb, q) * Sqr(g2) * oneOver16PiSqr;

   return self_energy_w_top;
}

} // namespace flexiblesusy
