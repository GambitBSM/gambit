//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for the CosmoBit module.
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@imperial.ac.uk)
///  \date 2017 Jul
///  \date 2017 Nov
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan,Feb, Mar
///  \date 2019 Jan, Feb, June
///  \date 2020 Nov
///  \date 2021 Jan, Mar, Apr, Sep
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Jun
///  \date 2019 Mar
///  \date 2020 Jun
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  \author Will Handley
///          (wh260@cam.ac.uk)
///  \date 2020 Mar
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2018 Mar
///  \date 2019 Jul
///  \date 2020 Apr
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sep
///
///  \author Anna Liang
///          (a.liang1@uqconnect.edu.au)
///  \date 2021 Aug
///
///  *********************************************

#ifndef __CosmoBit_rollcall_hpp__
#define __CosmoBit_rollcall_hpp__

#include "gambit/CosmoBit/CosmoBit_types.hpp"


#define MODULE CosmoBit
#define REFERENCE GAMBITCosmologyWorkgroup:2020htv
START_MODULE

  /// fraction of the abundance of the dark matter candidate in question
  /// (mostly a decaying component) contributing to the total DM abundance.
  #define CAPABILITY DM_fraction
  START_CAPABILITY
    #define FUNCTION DM_fraction_ALP
    START_FUNCTION(double)
    DEPENDENCY(minimum_fraction,double)
    DEPENDENCY(lifetime,double)
    DEPENDENCY(RD_oh2, double)
    ALLOW_MODEL_DEPENDENCE(LCDM, LCDM_theta, LCDM_zreio, GeneralCosmoALP)
    MODEL_GROUP(lcdm_model, (LCDM, LCDM_theta, LCDM_zreio))
    MODEL_GROUP(alp_model, (GeneralCosmoALP))
    ALLOW_MODEL_COMBINATION(lcdm_model, alp_model)
    #undef FUNCTION
  #undef CAPABILITY

  /// total abundance of axion-like particles, produced either by misalignment or freeze-in
  #define CAPABILITY total_DM_abundance
  START_CAPABILITY
    #define FUNCTION total_DM_abundance_ALP
    START_FUNCTION(double)
    DEPENDENCY(DM_fraction,double)
    ALLOW_MODEL_DEPENDENCE(LCDM, LCDM_theta, LCDM_zreio, GeneralCosmoALP)
    MODEL_GROUP(lcdm_model, (LCDM, LCDM_theta, LCDM_zreio))
    MODEL_GROUP(alp_model, (GeneralCosmoALP))
    ALLOW_MODEL_COMBINATION(lcdm_model, alp_model)
    #undef FUNCTION
  #undef CAPABILITY

  /// lifetime of the decaying dark matter component (in s)
  #define CAPABILITY lifetime
  START_CAPABILITY
    #define FUNCTION lifetime_ALP_agg
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  /// minimal Freeze-in abundance of axion-like particles, produced via Primakoff processes
  #define CAPABILITY minimum_abundance
  START_CAPABILITY
    #define FUNCTION minimum_abundance_ALP_analytical
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    #undef FUNCTION

    #define FUNCTION minimum_abundance_ALP_numerical
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  /// the fraction of the minimal freeze-in abundance of axion-like particles,
  /// produced via Primakoff processes, to the total abundance of dark matter
  #define CAPABILITY minimum_fraction
  START_CAPABILITY
    #define FUNCTION minimum_fraction_ALP
    START_FUNCTION(double)
    DEPENDENCY(minimum_abundance,double)
    ALLOW_MODEL_DEPENDENCE(LCDM, LCDM_theta, LCDM_zreio, GeneralCosmoALP)
    MODEL_GROUP(lcdm_model, (LCDM, LCDM_theta, LCDM_zreio))
    MODEL_GROUP(alp_model, (GeneralCosmoALP))
    ALLOW_MODEL_COMBINATION(lcdm_model, alp_model)
    #undef FUNCTION
  #undef CAPABILITY

  /// compute the values for etaBBN_rBBN_rCMB_dNurBBN_dNurCMB
  /// for non standard models (e.g. GeneralCosmoALP)
  #define CAPABILITY external_dNeff_etaBBN
  START_CAPABILITY
    #define FUNCTION compute_dNeff_etaBBN_ALP
    START_FUNCTION(map_str_dbl)
    ALLOW_JOINT_MODEL(GeneralCosmoALP,rBBN_dNurBBN)
    DEPENDENCY(total_DM_abundance, double)
    DEPENDENCY(lifetime, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY eta_ratio
  START_CAPABILITY
    #define FUNCTION eta_ratio_ALP
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    DEPENDENCY(external_dNeff_etaBBN, map_str_dbl)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Neff_evolution
  START_CAPABILITY
    #define FUNCTION Neff_evolution_ALP
    START_FUNCTION(map_str_dbl)
    ALLOW_MODELS(GeneralCosmoALP)
    DEPENDENCY(external_dNeff_etaBBN, map_str_dbl)
    #undef FUNCTION
  #undef CAPABILITY

  /// get the energy injection efficiency tables
  #define CAPABILITY energy_injection_efficiency
  START_CAPABILITY
    #define FUNCTION energy_injection_efficiency_func
    START_FUNCTION(DarkAges::Energy_injection_efficiency_table)
    ALLOW_MODELS(AnnihilatingDM_general,DecayingDM_general)
    BACKEND_REQ(get_energy_injection_efficiency_table, (), DarkAges::Energy_injection_efficiency_table,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY energy_injection_spectrum
  START_CAPABILITY
    #define FUNCTION energy_injection_spectrum_AnnihilatingDM_mixture
    START_FUNCTION(DarkAges::Energy_injection_spectrum)
    ALLOW_MODELS(AnnihilatingDM_mixture)
    #undef FUNCTION

    #define FUNCTION energy_injection_spectrum_DecayingDM_mixture
    START_FUNCTION(DarkAges::Energy_injection_spectrum)
    ALLOW_MODELS(DecayingDM_mixture)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY f_eff
  START_CAPABILITY
    // Calculate f_eff by convolution with weighting functions
    #define FUNCTION f_eff_weighted
    START_FUNCTION(double)
    ALLOW_MODELS(AnnihilatingDM_general) // Weighting function only known for s-wave annihilation
    DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
    #undef FUNCTION

    // Calculate f_eff by taking f_eff(z) at given z
    #define FUNCTION f_eff_at_z
    START_FUNCTION(double)
    ALLOW_MODELS(AnnihilatingDM_general,DecayingDM_general)
    DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
    #undef FUNCTION

    // Set f_eff to a constant that the user can choose
    #define FUNCTION f_eff_constant
    START_FUNCTION(double)
    ALLOW_MODELS(AnnihilatingDM_general,DecayingDM_general)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY p_ann
  START_CAPABILITY
    #define FUNCTION p_ann
    START_FUNCTION(double)
    ALLOW_MODELS(AnnihilatingDM_general)
    DEPENDENCY(f_eff, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Profiled likelihood on p_ann = f_eff * f^2 * <sv> / m
  #define CAPABILITY lnL_p_ann
  START_CAPABILITY
    #define FUNCTION lnL_p_ann_P18_TTTEEE_lowE_lensing_BAO
    START_FUNCTION(double)
    DEPENDENCY(p_ann, double)
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  // capabilities related to setting neutrino masses,
  // temperature, ncdm components & number of ultra-relativistic species Nur

  // total mass of neutrinos (in eV)
  #define CAPABILITY mNu_tot
  START_CAPABILITY
    #define FUNCTION get_mNu_tot
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  // SM value of N_eff in the early Universe (3 + corrections from precise decoupling)
  // calculations)
  #define CAPABILITY Neff_SM
  START_CAPABILITY
    #define FUNCTION get_Neff_SM
    START_FUNCTION(double)
    #undef FUNCTION
  #undef CAPABILITY

  // value of N_ur (today) (aka. contribution of massive neutrinos which are still relativistic)
  #define CAPABILITY N_ur
  START_CAPABILITY
    #define FUNCTION get_N_ur
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    ALLOW_MODEL_DEPENDENCE(etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    MODEL_GROUP(group1, StandardModel_SLHA2)
    MODEL_GROUP(group2, etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    ALLOW_MODEL_COMBINATION(group1, group2)
    DEPENDENCY(Neff_SM, double)
    #undef FUNCTION
  #undef CAPABILITY

  // ------------------------

  // Pivot scale (in Mpc^-1)
  #define CAPABILITY k_pivot
  START_CAPABILITY
    #define FUNCTION set_k_pivot
    START_FUNCTION(double)
    #undef FUNCTION
  #undef CAPABILITY

  // ------------------------

  #ifdef HAVE_PYBIND11

    // capabilities related to setting input options for CLASS
    // (cosmo parameters, temperature and number of ultra-relativistic species Nur)

    /// gather all CLASS input parameters, i.e.
    /// - cosmological parameters (H0, Omega_b, Omega_cmd, tau_reio)
    /// - primordial parameters (YHe, primordial power spectrum) from classy_primordial_input
    /// - neutrino mass, ultra-relativistic species and ncdm related parameters from classy_NuMasses_Nur_input
    /// - energy injection related parameters (if needed) from classy_parameters_EnergyInjection
    /// - CLASS settings from MontePython likelihoods from classy_MPLike_input
    /// - CLASS settings passed as yaml file options to the capability classy_input_params
    /// consistency checks when combining all these different inputs are performed.
    #define CAPABILITY classy_input_params
    START_CAPABILITY
      #define FUNCTION set_classy_input_params
      START_FUNCTION(Classy_input)
      ALLOW_MODELS(LCDM,LCDM_theta,LCDM_zreio)
      DEPENDENCY(classy_MPLike_input, pybind11::dict)
      DEPENDENCY(classy_NuMasses_Nur_input, pybind11::dict)
      DEPENDENCY(classy_primordial_input, pybind11::dict)
      MODEL_CONDITIONAL_DEPENDENCY(classy_parameters_EnergyInjection, pybind11::dict, AnnihilatingDM_general, DecayingDM_general)
      MODEL_CONDITIONAL_DEPENDENCY(classy_PlanckLike_input, pybind11::dict, cosmo_nuisance_Planck_lite,cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT)
      #undef FUNCTION
    #undef CAPABILITY

    // initialise CLASS either with the run options needed by
    // MontePython Likelihoods (t modes, Pk at specific z,..), or not.
    #define CAPABILITY classy_MPLike_input
    START_CAPABILITY
      #define FUNCTION set_classy_input_with_MPLike
      START_FUNCTION(pybind11::dict)
      DEPENDENCY(MP_objects, MPLike_objects_container)
      #undef FUNCTION

      #define FUNCTION set_classy_input_no_MPLike
      START_FUNCTION(pybind11::dict)
      #undef FUNCTION
    #undef CAPABILITY

    // set primordial CLASS input parameters
    #define CAPABILITY classy_primordial_input
    START_CAPABILITY
      // primordial helium abundance,YHe & *external* full shape of primordial power spectrum
      // (array with scalar & tensor perturb as function of k + pivot scale)
      #define FUNCTION set_classy_parameters_primordial_ps
      START_FUNCTION(pybind11::dict)
      DEPENDENCY(primordial_power_spectrum, Primordial_ps)
      DEPENDENCY(helium_abundance, double)
      DEPENDENCY(k_pivot, double)
      #undef FUNCTION

      // primordial helium abundance,YHe & *parametrised* primordial power spectrum
      // parameters (A_s,n_s,r + pivot scale)
      #define FUNCTION set_classy_parameters_parametrised_ps
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(PowerLaw_ps)
      DEPENDENCY(helium_abundance, double)
      DEPENDENCY(k_pivot, double)
      #undef FUNCTION
    #undef CAPABILITY

    /// set extra CLASS parameters for energy injection -- different functions for
    /// decaying and annihilating DM models
    #define CAPABILITY classy_parameters_EnergyInjection
    START_CAPABILITY
      #define FUNCTION set_classy_parameters_EnergyInjection_AnnihilatingDM
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(AnnihilatingDM_general)
      DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
      #undef FUNCTION

      #define FUNCTION set_classy_parameters_EnergyInjection_AnnihilatingDM_onSpot
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(AnnihilatingDM_general)
      DEPENDENCY(f_eff, double)
      #undef FUNCTION

      #define FUNCTION set_classy_parameters_EnergyInjection_DecayingDM
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(DecayingDM_general)
      DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
      #undef FUNCTION

      #define FUNCTION set_classy_parameters_EnergyInjection_DecayingDM_onSpot
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(DecayingDM_general)
      DEPENDENCY(f_eff, double)
      #undef FUNCTION
    #undef CAPABILITY

    // set extra parameters for CLASS run if Planck CMB likelihoods are included
    #define CAPABILITY classy_PlanckLike_input
    START_CAPABILITY
      #define FUNCTION set_classy_PlanckLike_input
      START_FUNCTION(pybind11::dict)
      BACKEND_REQ(plc_required_Cl,(),void,(int&,bool&,bool&))
      #undef FUNCTION
    #undef CAPABILITY

    /// set neutrino mass related CLASS input -- m_ncdm, T_ncdm, N_ur, N_ncdm
    #define CAPABILITY classy_NuMasses_Nur_input
    START_CAPABILITY
      #define FUNCTION set_classy_NuMasses_Nur_input
      START_FUNCTION(pybind11::dict)
      ALLOW_MODEL(StandardModel_SLHA2)
      DEPENDENCY(T_ncdm, double)
      DEPENDENCY(N_ur, double)
      #undef FUNCTION
    #undef CAPABILITY

  #endif

  // -----------

  // Primodial power spectra (MultiModeCode)

  /// initialise settings for MultiModeCode
  #define CAPABILITY multimode_input_parameters
  START_CAPABILITY
    #define FUNCTION set_multimode_inputs
    START_FUNCTION(Multimode_inputs)
    DEPENDENCY(k_pivot, double)
    ALLOW_MODELS(Inflation_InstReh_1mono23, Inflation_InstReh_1linear, Inflation_InstReh_1quadratic, Inflation_InstReh_1quartic, Inflation_InstReh_1natural, Inflation_InstReh_1Starobinsky)
    #undef FUNCTION
  #undef CAPABILITY

  /// use MultiModeCode to compute a non-parametric primordial power spectrum
  #define CAPABILITY primordial_power_spectrum
  START_CAPABILITY
    #define FUNCTION get_multimode_primordial_ps
    START_FUNCTION(Primordial_ps)
    DEPENDENCY(multimode_input_parameters, Multimode_inputs)
    BACKEND_REQ(multimodecode_primordial_ps, (), gambit_inflation_observables,
     (int&,int&,int&,int&,double*,double*,double*,double&,double&,double&,int&,double&,double&,int&,int&,int&,int&,int&))
    #undef FUNCTION
  #undef CAPABILITY

  /// use MultiModeCode to compute a parameterised primordial power spectrum
  #define CAPABILITY PowerLaw_ps_parameters
  START_CAPABILITY
    #define FUNCTION get_multimode_parametrised_ps
    START_FUNCTION(ModelParameters)
    DEPENDENCY(multimode_input_parameters, Multimode_inputs)
    BACKEND_REQ(multimodecode_parametrised_ps, (), gambit_inflation_observables,
     (int&,int&,int&,int&,double*,double*,double*,double&,double&,double&,int&,int&,int&,int&,int&))
    #undef FUNCTION
  #undef CAPABILITY

  // -----------

  // CMB (CLASS / Planck)

  /// get unlensed CMB TT spectrum
  #define CAPABILITY unlensed_Cl_TT
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_TT
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get lensed CMB TT spectrum
  #define CAPABILITY lensed_Cl_TT
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_TT
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get unlensed CMB Temperature-E mode cross-correlation spectrum
  #define CAPABILITY unlensed_Cl_TE
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_TE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get lensed CMB Temperature-E mode cross-correlation spectrum
  #define CAPABILITY lensed_Cl_TE
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_TE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get unlensed CMB E mode spectrum
  #define CAPABILITY unlensed_Cl_EE
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_EE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get lensed CMB E mode spectrum
  #define CAPABILITY lensed_Cl_EE
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_EE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get unlensed CMB B mode spectrum
  #define CAPABILITY unlensed_Cl_BB
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_BB
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get lensed CMB B mode spectrum
  #define CAPABILITY lensed_Cl_BB
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_BB
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get unlensed CMB lensing spectrum (Cell_phiphi)
  #define CAPABILITY unlensed_Cl_PhiPhi
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_PhiPhi
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// get lensed CMB lensing spectrum (Cell_phiphi)
  #define CAPABILITY lensed_Cl_PhiPhi
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_PhiPhi
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(),std::vector<double>, (str))
    #undef FUNCTION
  #undef CAPABILITY

  /// compute CMB low ell likelihood from Planck data
  /// functions to use
  /// - TT or TEB or EE or TTEE
  /// - 2018 or 2015 DR
  #define CAPABILITY Planck_lowl_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_lowl_TT_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TEB_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_BB,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TEB_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TT_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_EE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_EE_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TTEE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2018,(plc_tag),double,(double*))
    BACKEND_REQ(plc_loglike_lowl_EE_2018,(plc_tag),double,(double*))
    FORCE_SAME_BACKEND(plc_tag)
    #undef FUNCTION
  #undef CAPABILITY

  /// compute CMB high ell likelihood from Planck data
  /// functions to use
  /// - TT or TTTEEE
  /// - 2018 or 2015 DR and
  /// - full (16 for TT 34 for TTTEEE nuisance params) or lite (1 nuisance param)
  #define CAPABILITY Planck_highl_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_highl_TT_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT)
    BACKEND_REQ(plc_loglike_highl_TT_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_lite_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TT_lite_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_lite_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_lite_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT)
    BACKEND_REQ(plc_loglike_highl_TT_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_lite_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TT_lite_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_lite_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_lite_2018,(),double,(double*))
    #undef FUNCTION
  #undef CAPABILITY

  /// compute CMB lensing likelihood from Planck data
  /// function for 2018 and 2015 DR available
  #define CAPABILITY Planck_lensing_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_lensing_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_PhiPhi,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lensing_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lensing_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_PhiPhi,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lensing_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lensing_marged_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_PhiPhi,std::vector<double>)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lensing_marged_2018,(),double,(double*))
    #undef FUNCTION
  #undef CAPABILITY

  /// Gaussian priors on the nuisance parameters of the Planck likelihoods
  #define CAPABILITY Planck_nuisance_prior_loglike
  START_CAPABILITY
    #define FUNCTION compute_Planck_nuisance_prior_loglike
    START_FUNCTION(double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_TTTEEE)
    #undef FUNCTION
  #undef CAPABILITY

  /// priors on the tSZ and kSZ amplitudes based on based on SPT and ACT data
  /// cf. Eq. (32) of Aghanim et al. 2015 (arXiv 1507.02704)
  #define CAPABILITY Planck_sz_prior_loglike
  START_CAPABILITY
    #define FUNCTION compute_Planck_sz_prior
    START_FUNCTION(double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_TTTEEE)
    #undef FUNCTION
  #undef CAPABILITY

 /// temperature of non-cold DM components

  #define CAPABILITY T_ncdm
  START_CAPABILITY

    // needed in addition to T_ncdm, as T_ncdm of non-SM models
    // assume a fiducial value to base calculation on
    #define FUNCTION T_ncdm_SM
    START_FUNCTION(double)
    #undef FUNCTION

    #define FUNCTION T_ncdm
    START_FUNCTION(double)
    ALLOW_MODEL(etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    #undef FUNCTION

  #undef CAPABILITY

  /// extract H0 from a classy run if it is not a fundamental parameter
  /// (i.e. for LCDM_theta), as it now becomes derived
  #define CAPABILITY H0
  START_CAPABILITY
    #define FUNCTION get_H0_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_H0,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// Get Hubble rate at z in km/s/Mpc
  #define CAPABILITY H_at_z
  START_CAPABILITY
    #define FUNCTION get_H_at_z_classy
    START_FUNCTION(daFunk::Funk)
    BACKEND_REQ(class_get_Hz,(),double,(double))
    #undef FUNCTION
  #undef CAPABILITY

  /// Get time since big bang at z in s
  #define CAPABILITY time_at_z
  START_CAPABILITY
    #define FUNCTION get_time_at_z_classy
    START_FUNCTION(daFunk::Funk)
    BACKEND_REQ(class_get_tz,(),double,(double))
    #undef FUNCTION
  #undef CAPABILITY

  /// Get t(z=0) in s
  #define CAPABILITY age_universe
  START_CAPABILITY
    #define FUNCTION get_age_universe_from_time_at_z
    START_FUNCTION(double)
    DEPENDENCY(time_at_z,daFunk::Funk)
    #undef FUNCTION
  #undef CAPABILITY

  /// number density of photons today
  #define CAPABILITY n0_g
  START_CAPABILITY
    #define FUNCTION compute_n0_g
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio)
    #undef FUNCTION
  #undef CAPABILITY

// TODO: Temporarily disabled until project is ready
/*
  /// energy density of dark energy today
  #define CAPABILITY Omega0_Lambda
    START_CAPABILITY
    #define FUNCTION get_Omega0_Lambda_classy
      START_FUNCTION(double)
      BACKEND_REQ(class_get_Omega0_Lambda,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY
*/

  /// energy density of all matter components today
  #define CAPABILITY Omega0_m
  START_CAPABILITY
    #define FUNCTION get_Omega0_m_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_m,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density in baryons today
  #define CAPABILITY Omega0_b
  START_CAPABILITY
    #define FUNCTION compute_Omega0_b
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density of CDM component today
  #define CAPABILITY Omega0_cdm
  START_CAPABILITY
    #define FUNCTION compute_Omega0_cdm
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density in radiation today
  #define CAPABILITY Omega0_r
  START_CAPABILITY
    #define FUNCTION get_Omega0_r_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_r,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density in photons today
  #define CAPABILITY Omega0_g
  START_CAPABILITY
    #define FUNCTION compute_Omega0_g
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density in ultra-relativistic species today
  #define CAPABILITY Omega0_ur
  START_CAPABILITY
    #define FUNCTION compute_Omega0_ur
    START_FUNCTION(double)
    DEPENDENCY(Omega0_g, double)
    DEPENDENCY(N_ur, double)
    #undef FUNCTION

    #define FUNCTION get_Omega0_ur_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_ur,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// energy density of non-cold DM components today
  #define CAPABILITY Omega0_ncdm
  START_CAPABILITY
    #define FUNCTION get_Omega0_ncdm_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_ncdm_tot,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// baryon-to-photon ratio today
  #define CAPABILITY eta0
  START_CAPABILITY
    // calculate eta0 (today) from omega_b and T_cmb
    #define FUNCTION eta0_LCDM
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio)
    #undef FUNCTION
  #undef CAPABILITY

  // sound horizon at baryon drag
  #define CAPABILITY rs_drag
  START_CAPABILITY
    #define FUNCTION get_rs_drag_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_rs,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // optical depth at reionisation
  #define CAPABILITY tau_reio
  START_CAPABILITY
    #define FUNCTION get_tau_reio_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_tau_reio,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // redshift of reionisation
  #define CAPABILITY z_reio
  START_CAPABILITY
    #define FUNCTION get_z_reio_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_z_reio,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// get the value of Neff in the early Universe from CLASS backend
  #define CAPABILITY Neff
  START_CAPABILITY
    #define FUNCTION get_Neff_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Neff,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  /// returns S8 = sigma8 (Omega0_m/0.3)^0.5
  /// (sigma8:root mean square fluctuations density fluctuations within
  /// spheres of radius 8/h Mpc)
  #define CAPABILITY S8_cosmo
  START_CAPABILITY
    #define FUNCTION get_S8_classy
    START_FUNCTION(double)
    DEPENDENCY(Omega0_m, double)
    BACKEND_REQ(class_get_sigma8,(),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  // AlterBBN

  /// collect all input options for AlterBBN in form of a string to double map
  #define CAPABILITY AlterBBN_Input
  START_CAPABILITY
    #define FUNCTION AlterBBN_Input
    START_FUNCTION(map_str_dbl)
    ALLOW_MODELS(LCDM, LCDM_theta, LCDM_zreio, etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    ALLOW_MODEL_DEPENDENCE(nuclear_params_neutron_lifetime)
    MODEL_GROUP(cosmo,(LCDM, LCDM_theta, LCDM_zreio, etaBBN_rBBN_rCMB_dNurBBN_dNurCMB))
    MODEL_GROUP(neutron,(nuclear_params_neutron_lifetime))
    ALLOW_MODEL_COMBINATION(cosmo,neutron)
    DEPENDENCY(Neff_SM, double)
    MODEL_CONDITIONAL_DEPENDENCY(eta0,double,LCDM,LCDM_theta,LCDM_zreio)
    #undef FUNCTION
  #undef CAPABILITY

  /// compute primordial element abundances (and theoretical errors &
  /// covariances if requested) as predicted from BBN
  #define CAPABILITY primordial_abundances_BBN
  START_CAPABILITY
    #define FUNCTION compute_primordial_abundances_BBN
    START_FUNCTION(BBN_container)
    DEPENDENCY(AlterBBN_Input, map_str_dbl)
    BACKEND_REQ(call_nucl_err, (alterbbn_tag), int, (map_str_dbl&,double*,double*))
    BACKEND_REQ(call_nucl, (alterbbn_tag), int, (map_str_dbl&,double*))
    BACKEND_REQ(get_NNUC, (alterbbn_tag), size_t, ())
    BACKEND_REQ(get_abund_map_AlterBBN, (alterbbn_tag), map_str_int, ())
    FORCE_SAME_BACKEND(alterbbn_tag)
    #undef FUNCTION
  #undef CAPABILITY

  /// Compute the primordial abundances today
  /// These contain effects from photodisintegration if relevant
  #define CAPABILITY primordial_abundances
  START_CAPABILITY

    #define FUNCTION primordial_abundances
    START_FUNCTION(BBN_container)
    DEPENDENCY(primordial_abundances_BBN, BBN_container)
    #undef FUNCTION

    #define FUNCTION primordial_abundances_decayingDM
    START_FUNCTION(BBN_container)
    ALLOW_MODEL_DEPENDENCE(LCDM, LCDM_theta, LCDM_zreio)
    ALLOW_MODEL_DEPENDENCE(DecayingDM_mixture)
    MODEL_GROUP(cosmo,(LCDM, LCDM_theta, LCDM_zreio))
    MODEL_GROUP(decay,(DecayingDM_mixture))
    ALLOW_MODEL_COMBINATION(cosmo,decay)
    DEPENDENCY(primordial_abundances_BBN, BBN_container)
    BACKEND_REQ(set_input_params, (), void, (bool,int,int,double))
    BACKEND_REQ(abundance_photodisintegration_decay, (), void, (double*,double*,double*,double*,double,double,double,double,double,int))
    #undef FUNCTION
  #undef CAPABILITY

  /// compute primordial helium abundance
  #define CAPABILITY helium_abundance
  START_CAPABILITY
    #define FUNCTION extract_helium_abundance
    START_FUNCTION(double)
    DEPENDENCY(primordial_abundances, BBN_container)
    #undef FUNCTION
  #undef CAPABILITY

  /// compute BBN likelihood for chosen isotopes
  /// depending on yaml file settings, theoretical
  /// errors and cross-correlations are included
  #define CAPABILITY BBN_LogLike
  START_CAPABILITY
    #define FUNCTION compute_BBN_LogLike
    START_FUNCTION(double)
    DEPENDENCY(primordial_abundances, BBN_container)
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  #ifdef HAVE_PYBIND11

    // MontePython

    /// pass current values of nuisance parameters to MP
    #define CAPABILITY parameter_dict_for_MPLike
    START_CAPABILITY
      // allow all possible nuisance parameter models here
      #define FUNCTION set_parameter_dict_for_MPLike
      START_FUNCTION(pybind11::dict)
      ALLOW_MODELS(cosmo_nuisance_acbar,cosmo_nuisance_spt,cosmo_nuisance_Lya_abg)
      ALLOW_MODELS(cosmo_nuisance_JLA,cosmo_nuisance_Pantheon,cosmo_nuisance_BK15,cosmo_nuisance_BK14,cosmo_nuisance_BK14priors)
      ALLOW_MODELS(cosmo_nuisance_CFHTLens_correlation,cosmo_nuisance_euclid_lensing,cosmo_nuisance_euclid_pk,cosmo_nuisance_euclid_pk_noShot)
      ALLOW_MODELS(cosmo_nuisance_kids450_qe_likelihood_public,cosmo_nuisance_wmap,cosmo_nuisance_ISW)
      ALLOW_MODELS(cosmo_nuisance_ska1,cosmo_nuisance_ska1_IM_band,cosmo_nuisance_ska1_IM_band_noHI,cosmo_nuisance_ska_lensing)
      ALLOW_MODELS(cosmo_nuisance_ska1_pk,cosmo_nuisance_ska2_pk)
      ALLOW_MODELS(cosmo_nuisance_SpectralDistortions)
      // if you implement new MontePython likelihoods with new nuisance parameters add the name of your new
      // nuisance parameter model (to be defined in Models/include/gambit/Models/models/CosmoNuisanceModels.hpp)
      ALLOW_MODELS(cosmo_nuisance_dummy)
      #undef FUNCTION

      // pass an empty dictionary if no likelihood with nuisance parameters
      // is in use
      #define FUNCTION pass_empty_parameter_dict_for_MPLike
      START_FUNCTION(pybind11::dict)
      #undef FUNCTION
    #undef CAPABILITY

    /// creates the MontePython data and likelihood objects, determining which experiments
    /// are in use in the process
    #define CAPABILITY MP_objects
    START_CAPABILITY
      #define FUNCTION create_MP_objects
      START_FUNCTION(MPLike_objects_container)
      DEPENDENCY(parameter_dict_for_MPLike, pybind11::dict)
      BACKEND_REQ(create_MP_data_object,        (mplike_tag), pybind11::object, (map_str_str&))
      BACKEND_REQ(get_MP_available_likelihoods, (mplike_tag), std::vector<str>, ())
      BACKEND_REQ(create_MP_likelihood_objects, (mplike_tag), map_str_pyobj,    (pybind11::object&, map_str_str&))
      FORCE_SAME_BACKEND(mplike_tag)
      #undef FUNCTION
    #undef CAPABILITY

    /// calculates lnL for individual experiments using MontePython
    #define CAPABILITY MP_LogLikes
    START_CAPABILITY
      #define FUNCTION compute_MP_LogLikes
      START_FUNCTION(map_str_dbl)
      DEPENDENCY(parameter_dict_for_MPLike, pybind11::dict)
      DEPENDENCY(MP_objects, MPLike_objects_container)
      BACKEND_REQ(check_likelihood_classy_combi,(mplike_tag), void,             (str&, str&))
      BACKEND_REQ(get_MP_loglike,               (mplike_tag), double,           (const MPLike_data_container&, pybind11::object&, std::string&))
      BACKEND_REQ(get_classy_backendDir,        (class_tag),  std::string,      ())
      BACKEND_REQ(get_classy_cosmo_object,      (class_tag),  pybind11::object, ())
      FORCE_SAME_BACKEND(mplike_tag)
      FORCE_SAME_BACKEND(class_tag)
      #undef FUNCTION
    #undef CAPABILITY

    /// calculates the total lnL from MontePython
    #define CAPABILITY MP_Combined_LogLike
      START_CAPABILITY
      #define FUNCTION compute_MP_combined_LogLike
      START_FUNCTION(double)
      DEPENDENCY(MP_LogLikes, map_str_dbl)
      #undef FUNCTION
    #undef CAPABILITY

    /// retrieves the correlation coefficients and the LogLike not taking
    /// bao correlations into account from the MP likelihood "bao_correlations"
    #define CAPABILITY bao_like_correlation
      START_CAPABILITY
      #define FUNCTION get_bao_like_correlation
      START_FUNCTION(map_str_dbl)
      DEPENDENCY(MP_LogLikes, map_str_dbl)
      DEPENDENCY(MP_objects, MPLike_objects_container)
      #undef FUNCTION
    #undef CAPABILITY

  #endif

  // --------------------
  // Modified gravity models - symmetron
  // TODO: Temporarily disabled until project is ready
/*
  // Obtain a value for phi(0) given mass and mu
  #define CAPABILITY phi0_interpolation
  START_CAPABILITY
    #define FUNCTION interp_phi0
    START_FUNCTION(double)
    ALLOW_MODELS(symmetron)
    #undef FUNCTION
  #undef CAPABILITY

  // Calculate BD param omega gievn phi(0), mass and v
  #define CAPABILITY omega_bdparam
  START_CAPABILITY
    #define FUNCTION compute_omega
    START_FUNCTION(double)
    ALLOW_MODELS(symmetron)
    DEPENDENCY(phi0_interpolation, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Calculate |gamma-1| given BD param omega
  #define CAPABILITY gammaminus1_bdparam
  START_CAPABILITY
    #define FUNCTION compute_gammaminus1
    START_FUNCTION(double)
    DEPENDENCY(omega_bdparam, double)
    #undef FUNCTION
  #undef CAPABILITY

    // A likelihood function for |gamma-1| using cassini value
  #define CAPABILITY gamma_loglike
  START_CAPABILITY
    #define FUNCTION lnL_gamma
    START_FUNCTION(double)
    DEPENDENCY(gammaminus1_bdparam, double)
    #undef FUNCTION
  #undef CAPABILITY

  // calculate |beta-1| given BD param omega
  #define CAPABILITY betaminus1_bdparam
  START_CAPABILITY
    #define FUNCTION compute_betaminus1
    START_FUNCTION(double)
    ALLOW_MODELS(symmetron)
    DEPENDENCY(omega_bdparam, double)
    DEPENDENCY(phi0_interpolation, double)
    #undef FUNCTION
  #undef CAPABILITY

  // A likelihood function for eta using mars perihelion value
  #define CAPABILITY eta_loglike
  START_CAPABILITY
    #define FUNCTION lnL_eta
    START_FUNCTION(double)
    DEPENDENCY(gammaminus1_bdparam, double)
    DEPENDENCY(betaminus1_bdparam, double)
    #undef FUNCTION
  #undef CAPABILITY

  // A likelihood function vmax
  #define CAPABILITY vmin_loglike
  START_CAPABILITY
    #define FUNCTION lnL_vmin
    START_FUNCTION(double)
    ALLOW_MODELS(symmetron)
    #undef FUNCTION
  #undef CAPABILITY
*/

#undef REFERENCE
#undef MODULE
#endif /* defined __CosmoBit_rollcall_hpp__ */
