//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  LCDM model and data dependent nuisance parameter declarations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@imperial.ac.uk)
///  \date 2016 Oct
///  \date 2017 Jan
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Feb, July
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///  \date 2019 June
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///   \date 2019 Nov
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///   \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sep
///
///  *********************************************

#pragma once

// Vanilla ΛCDM.
// This model would usually be scanned alongside an inflationary model and a neutrino model
#define MODEL LCDM
  START_MODEL
  DEFINEPARS(T_cmb,omega_b,omega_cdm,H0,tau_reio)
  MAP_TO_CAPABILITY(T_cmb,T_cmb)
  MAP_TO_CAPABILITY(H0, H0)
#undef MODEL

// Vanilla ΛCDM.
// This model would usually be scanned alongside an inflationary model and a neutrino model
// As LCDM but with 100theta_s, acoustic angular scale of first CMB peak x 100, as
// model parameter instead of H0.
#define MODEL LCDM_theta
  START_MODEL
  DEFINEPARS(T_cmb,omega_b,omega_cdm,100theta_s,tau_reio)
  MAP_TO_CAPABILITY(T_cmb,T_cmb)
#undef MODEL

/* CMB + BBN */

// η (baryon-to-photon ratio) defined at BBN.
// r_CMB(BBN): Ratio of temperatures in non-cold DM compared to the SM with 3 massive neutrinos:
// r_CMB = T_v(BSM)/T_v(SM) at CMB (BBN)
// dNurCMB(_BBN): ΔN_effective defined at CMB(BBN) from additional radiation.
#define MODEL etaBBN_rBBN_rCMB_dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(eta_BBN)
  DEFINEPARS(r_BBN,r_CMB)
  DEFINEPARS(dNur_BBN,dNur_CMB)
#undef MODEL

// No additional radiation or changes to the neutrino temperature.
// Just the baryon-to-photon ratio η at BBN.
#define MODEL etaBBN
 #define PARENT etaBBN_rBBN_rCMB_dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(eta_BBN)
  INTERPRET_AS_PARENT_FUNCTION(etaBBN_to_etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
 #undef PARENT
#undef MODEL

// As etaBBN_rBBN_rCMB_dNurBBN_dNurCMB, but with the
// baryon-to-photon ratio η at BBN set equal to η today.
#define MODEL rBBN_rCMB_dNurBBN_dNurCMB
 #define PARENT etaBBN_rBBN_rCMB_dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(r_BBN,r_CMB)
  DEFINEPARS(dNur_BBN,dNur_CMB)
  INTERPRET_AS_PARENT_FUNCTION(rBBN_rCMB_dNurBBN_dNurCMB_to_etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
  INTERPRET_AS_PARENT_DEPENDENCY(eta0, double)
 #undef PARENT
#undef MODEL

// As above, but with no additional radiation.
#define MODEL rBBN_rCMB
 #define PARENT rBBN_rCMB_dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(r_BBN,r_CMB)
  INTERPRET_AS_PARENT_FUNCTION(rBBN_rCMB_to_rBBN_rCMB_dNurBBN_dNurCMB)
 #undef PARENT
#undef MODEL

// As above, but with neutrino temperature at BBN the same as at recombination.
#define MODEL rCMB
 #define PARENT rBBN_rCMB
  START_MODEL
  DEFINEPARS(r_CMB)
  INTERPRET_AS_PARENT_FUNCTION(rCMB_to_rBBN_rCMB)
 #undef PARENT
#undef MODEL

// As rBBN_rCMB_dNurBBN_dNurCMB, but with no changes to the neutrino temperature.
#define MODEL dNurBBN_dNurCMB
 #define PARENT rBBN_rCMB_dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(dNur_BBN,dNur_CMB)
  INTERPRET_AS_PARENT_FUNCTION(dNurBBN_dNurCMB_to_rBBN_rCMB_dNurBBN_dNurCMB)
 #undef PARENT
#undef MODEL

// As above, but with additional radiation the same at BBN as at recombination.
#define MODEL dNurCMB
 #define PARENT dNurBBN_dNurCMB
  START_MODEL
  DEFINEPARS(dNur_CMB)
  INTERPRET_AS_PARENT_FUNCTION(dNurCMB_to_dNurBBN_dNurCMB)
 #undef PARENT
#undef MODEL


/* INFLATION */

// Inflationary models -- if one of these is in use, you would usually need to use a cosmological model
// to scan over the four standard cosmological parameters (H0 or theta, omega_b, omega_cdm, tau_reio).
// The shape of the (either parameterised or full) primordial power spectrum will be determined by
// the inflation model in use.

// Simple, parameterised, purely phenomenological, scale-free power spectrum
#define MODEL PowerLaw_ps
  START_MODEL
  DEFINEPARS(ln10A_s,n_s,r,N_pivot)
#undef MODEL

// Even simpler, parameterised, purely phenomenological, scale-free power spectrum
#define MODEL Minimal_PowerLaw_ps
 #define PARENT PowerLaw_ps
  START_MODEL
  DEFINEPARS(ln10A_s,n_s)
  INTERPRET_AS_PARENT_FUNCTION(Minimal_PowerLaw_ps_to_PowerLaw_ps)
 #undef PARENT
#undef MODEL

// Single field, monomial inflation with exponent 2/3 (assuming instant reheating)
// Potential: V(phi) = 1.5 lambda M_P^(10/3) phi^(2/3)
#define MODEL Inflation_InstReh_1mono23
  START_MODEL
  DEFINEPARS(lambda)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL

// Single field, linear inflation (assuming instant reheating)
// Potential: V(phi) = lambda M_P^3 phi
#define MODEL Inflation_InstReh_1linear
  START_MODEL
  DEFINEPARS(lambda)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL

// Single field, quadratic inflation (assuming instant reheating)
// Potential: V(phi) = 0.5 m^2 phi^2 = 0.5 m_phi^2 M_P^2 phi^2
#define MODEL Inflation_InstReh_1quadratic
  START_MODEL
  DEFINEPARS(m_phi)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL

// Single field, quartic inflation (assuming instant reheating)
// Potential: V(phi) = 0.25 lambda phi^4
#define MODEL Inflation_InstReh_1quartic
  START_MODEL
  DEFINEPARS(lambda)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL

// Single field, natural inflation (assuming instant reheating)
// Potential: V(phi) = Lambda^4 [ 1 + cos(phi/f) ] = (lambda M_P)^4 [ 1 + cos(phi/[f_phi M_P]) ]
#define MODEL Inflation_InstReh_1natural
  START_MODEL
  DEFINEPARS(lambda, f_phi)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL

// Single field, Starobinsky - aka R^2 - inflation (assuming instant reheating)
// Potential: V(phi) = Lambda^4 [1-exp(-sqrt(2/3)phi/M_P)]^2 = (lambda M_P)^4 [1-exp(-sqrt(2/3)phi/M_P)]^2
#define MODEL Inflation_InstReh_1Starobinsky
  START_MODEL
  DEFINEPARS(lambda)
  INTERPRET_AS_X_FUNCTION(PowerLaw_ps, as_PowerLaw)
  INTERPRET_AS_X_DEPENDENCY(PowerLaw_ps, PowerLaw_ps_parameters, ModelParameters)
#undef MODEL
