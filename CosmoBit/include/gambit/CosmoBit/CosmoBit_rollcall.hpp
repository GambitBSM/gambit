//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for the developement
///  version of the CosmoBit module.
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
///  *********************************************

#pragma once

#include "gambit/CosmoBit/CosmoBit_types.hpp"


#define MODULE CosmoBit
START_MODULE

  #define CAPABILITY DM_fraction
  START_CAPABILITY
    #define FUNCTION DM_fraction_ALP
    START_FUNCTION(double)
    DEPENDENCY(minimum_fraction,double)
    DEPENDENCY(lifetime,double)
    DEPENDENCY(RD_oh2, double)
    ALLOW_JOINT_MODEL(LCDM, GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY total_DM_abundance
  START_CAPABILITY
    #define FUNCTION total_DM_abundance_ALP
    START_FUNCTION(double)
    DEPENDENCY(DM_fraction,double)
    ALLOW_JOINT_MODEL(LCDM, GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lifetime
  START_CAPABILITY
    #define FUNCTION lifetime_ALP_agg
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY minimum_abundance
  START_CAPABILITY
    #define FUNCTION minimum_abundance_ALP
    START_FUNCTION(double)
    ALLOW_MODELS(GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY minimum_fraction
  START_CAPABILITY
    #define FUNCTION minimum_fraction_ALP
    START_FUNCTION(double)
    DEPENDENCY(minimum_abundance,double)
    ALLOW_JOINT_MODEL(LCDM,GeneralCosmoALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY energy_injection_efficiency
  START_CAPABILITY
    #define FUNCTION energy_injection_efficiency_func
    START_FUNCTION(DarkAges::Energy_injection_efficiency_table)
    ALLOW_MODELS(AnnihilatingDM_general,DecayingDM_general)
    BACKEND_REQ(get_energy_injection_efficiency_table, (DarkAges_tag), DarkAges::Energy_injection_efficiency_table,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Planck_nuisance_prior_loglike
  START_CAPABILITY
    #define FUNCTION compute_Planck_nuisance_prior_loglike
    START_FUNCTION(double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_TTTEEE)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Planck_sz_prior_loglike
  START_CAPABILITY
    #define FUNCTION compute_Planck_sz_prior
    START_FUNCTION(double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_TTTEEE)
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  // Capabilities related to setting neutrino masses,
  // temperature, ncdm components & number of ultra-relativistic species Nur

  // Total mass of neutrinos (in eV)
  #define CAPABILITY mNu_tot
  START_CAPABILITY
    #define FUNCTION get_mNu_tot
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  // SM value of N_eff in the early Universe (3 + corrections from precise decoupling
  // calculations)
  #define CAPABILITY Neff_SM
  START_CAPABILITY
    #define FUNCTION get_Neff_SM
    START_FUNCTION(double)
     #undef FUNCTION
  #undef CAPABILITY
  
  // Value of N_ur (today) (aka. contribution of massive neutrinos which are still relativistic)
  #define CAPABILITY N_ur
  START_CAPABILITY
    #define FUNCTION get_N_ur
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    DEPENDENCY(Neff_SM, double)
    MODEL_CONDITIONAL_DEPENDENCY(etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters,ModelParameters,etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
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

  // Capabilities related to setting input options for CLASS
  // (cosmo parameters, temperature and number of ultra-relativistic species Nur)

  #define CAPABILITY classy_input_params
  START_CAPABILITY
    #define FUNCTION set_classy_input_params
    START_FUNCTION(Classy_input)
    ALLOW_MODELS(LCDM,LCDM_theta)
    DEPENDENCY(classy_MPLike_input, pybind11::dict)
    DEPENDENCY(classy_NuMasses_Nur_input, pybind11::dict)
    DEPENDENCY(classy_primordial_input, pybind11::dict)
    //MODEL_CONDITIONAL_DEPENDENCY(classy_parameters_EnergyInjection, pybind11::dict, AnnihilatingDM_general, DecayingDM_general)
    MODEL_CONDITIONAL_DEPENDENCY(classy_PlanckLike_input, pybind11::dict, cosmo_nuisance_Planck_lite,cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,plik_dx11dr2_HM_v18_TT)
    #undef FUNCTION
  #undef CAPABILITY

  // Initialise CLASS either with the run options needed by
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

  // Set different CLASS input parameters
  #define CAPABILITY classy_primordial_input
  START_CAPABILITY
    // H0, tau_reio, Omega_m, Omega_b plus an external primordial power spectrum
    #define FUNCTION set_classy_parameters_primordial_ps
    START_FUNCTION(pybind11::dict)
    DEPENDENCY(primordial_power_spectrum, Primordial_ps)
    DEPENDENCY(helium_abundance, double)
    DEPENDENCY(k_pivot, double)
    #undef FUNCTION

    // H0, tau_reio, Omega_m, Omega_b plus an external *parametrised* primordial power spectrum
    #define FUNCTION set_classy_parameters_parametrised_ps
    START_FUNCTION(pybind11::dict)
    ALLOW_MODELS(PowerLaw_ps)
    DEPENDENCY(helium_abundance, double)
    DEPENDENCY(k_pivot, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Set extra CLASS parameters for energy injection
  #define CAPABILITY classy_parameters_EnergyInjection
  START_CAPABILITY
    #define FUNCTION set_classy_parameters_EnergyInjection_AnnihilatingDM
    START_FUNCTION(Classy_input)
    DEPENDENCY(classy_input_params,Classy_input)
    ALLOW_MODEL(AnnihilatingDM_general)
    DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
    #undef FUNCTION

    #define FUNCTION set_classy_parameters_EnergyInjection_DecayingDM
    START_FUNCTION(Classy_input)
    DEPENDENCY(classy_input_params,Classy_input)
    ALLOW_MODEL(DecayingDM_general)
    DEPENDENCY(energy_injection_efficiency, DarkAges::Energy_injection_efficiency_table)
    #undef FUNCTION

    #define FUNCTION set_classy_parameters_no_EnergyInjection
    START_FUNCTION(Classy_input)
    DEPENDENCY(classy_input_params,Classy_input)
    #undef FUNCTION
  #undef CAPABILITY

  // Set extra parameters for CLASS run if Planck CMB likelihoods are included
  #define CAPABILITY classy_PlanckLike_input
  START_CAPABILITY
    #define FUNCTION set_classy_PlanckLike_input
    START_FUNCTION(pybind11::dict)
    BACKEND_REQ(plc_required_Cl,(plc_tag),void,(int&,bool&,bool&))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY classy_NuMasses_Nur_input
  START_CAPABILITY
    #define FUNCTION set_classy_NuMasses_Nur_input
    START_FUNCTION(pybind11::dict)
    ALLOW_MODEL(StandardModel_SLHA2)
    DEPENDENCY(T_ncdm, double)
    DEPENDENCY(N_ur, double)
    #undef FUNCTION
  #undef CAPABILITY

  // -----------

  // Primodial power spectra (MultiModeCode)

  /// Initialise settings for MultiModeCode
  #define CAPABILITY multimode_input_parameters
  START_CAPABILITY
    #define FUNCTION set_multimode_inputs
    START_FUNCTION(Multimode_inputs)
    DEPENDENCY(k_pivot, double)
    ALLOW_MODELS(Inflation_InstReh_1mono23, Inflation_InstReh_1linear, Inflation_InstReh_1quadratic, Inflation_InstReh_1quartic, Inflation_InstReh_1natural, Inflation_InstReh_1Starobinsky)
    #undef FUNCTION
  #undef CAPABILITY

  /// Use MultiModeCode to compute a non-parametric primordial power spectrum
  #define CAPABILITY primordial_power_spectrum
  START_CAPABILITY
    #define FUNCTION get_multimode_primordial_ps
    START_FUNCTION(Primordial_ps)
    DEPENDENCY(multimode_input_parameters, Multimode_inputs)
    BACKEND_REQ(multimodecode_primordial_ps, (), gambit_inflation_observables,
     (int&,int&,int&,int&,double*,double*,double*,double&,double&,double&,int&,double&,double&,int&,int&,int&,int&,int&))
    #undef FUNCTION
  #undef CAPABILITY

  /// Use MultiModeCode to compute a parameterised primordial power spectrum
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

  #define CAPABILITY unlensed_Cl_TT
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_TT
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unlensed_Cl_TE
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_TE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unlensed_Cl_EE
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_EE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unlensed_Cl_BB
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_BB
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY unlensed_Cl_PhiPhi
  START_CAPABILITY
    #define FUNCTION class_get_unlensed_Cl_PhiPhi
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_unlensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lensed_Cl_TT
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_TT
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lensed_Cl_TE
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_TE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lensed_Cl_EE
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_EE
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lensed_Cl_BB
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_BB
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lensed_Cl_PhiPhi
  START_CAPABILITY
    #define FUNCTION class_get_lensed_Cl_PhiPhi
    START_FUNCTION(std::vector<double>)
    BACKEND_REQ(class_get_lensed_cl,(class_tag),std::vector<double>, (str))
    FORCE_SAME_BACKEND(class_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Planck_lowl_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_lowl_TT_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TEB_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_BB,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TEB_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TT_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_EE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_EE_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lowl_TTEE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lowl_TT_2018,(plc_tag),double,(double*))
    BACKEND_REQ(plc_loglike_lowl_EE_2018,(plc_tag),double,(double*))
    FORCE_SAME_BACKEND(plc_tag)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Planck_highl_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_highl_TT_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT)
    BACKEND_REQ(plc_loglike_highl_TT_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_lite_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TT_lite_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_lite_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_lite_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TT)
    BACKEND_REQ(plc_loglike_highl_TT_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TT_lite_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TT_lite_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_2018,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_highl_TTTEEE_lite_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_highl_TTTEEE_lite_2018,(),double,(double*))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Planck_lensing_loglike
  START_CAPABILITY
    #define FUNCTION function_Planck_lensing_2015_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_PhiPhi,std::vector<double>)
    DEPENDENCY(T_cmb,double)
    ALLOW_MODELS(cosmo_nuisance_Planck_TTTEEE,cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite)
    BACKEND_REQ(plc_loglike_lensing_2015,(),double,(double*))
    #undef FUNCTION

    #define FUNCTION function_Planck_lensing_2018_loglike
    START_FUNCTION(double)
    DEPENDENCY(lensed_Cl_TT,std::vector<double>)
    DEPENDENCY(lensed_Cl_TE,std::vector<double>)
    DEPENDENCY(lensed_Cl_EE,std::vector<double>)
    DEPENDENCY(lensed_Cl_PhiPhi,std::vector<double>)
    DEPENDENCY(T_cmb,double)
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

  // Needed in addition to T_ncdm, as T_ncdm of non-SM models
  // assume a fiducial value to base calculation on
  #define CAPABILITY T_ncdm_SM
  START_CAPABILITY
    #define FUNCTION T_ncdm_SM
    START_FUNCTION(double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY T_ncdm
  START_CAPABILITY
    #define FUNCTION T_ncdm
    START_FUNCTION(double)
    MODEL_CONDITIONAL_DEPENDENCY(etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters,ModelParameters,etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    DEPENDENCY(T_ncdm_SM,double)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract H0 from a classy run if it is not a fundamental parameter
  /// (i.e. for LCDM_theta), as it now becomes derived
  #define CAPABILITY H0
  START_CAPABILITY
    #define FUNCTION get_H0_classy
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM_theta)
    BACKEND_REQ(class_get_H0,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY n0_g
  START_CAPABILITY
    #define FUNCTION compute_n0_g
    START_FUNCTION(double)
    #undef FUNCTION

    //#define FUNCTION get_n0_g_classy
    //START_FUNCTION(double)
    //DEPENDENCY(get_Classy_cosmo_container, Classy_cosmo_container)
    //#undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_m
  START_CAPABILITY
    #define FUNCTION get_Omega0_m_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_m,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_b
  START_CAPABILITY
    #define FUNCTION compute_Omega0_b
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_cdm
  START_CAPABILITY
    #define FUNCTION compute_Omega0_cdm
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_r
  START_CAPABILITY
    #define FUNCTION get_Omega0_r_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_r,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_g
  START_CAPABILITY
    #define FUNCTION compute_Omega0_g
    START_FUNCTION(double)
    DEPENDENCY(H0, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_ur
  START_CAPABILITY
    #define FUNCTION compute_Omega0_ur
    START_FUNCTION(double)
    DEPENDENCY(Omega0_g, double)
    DEPENDENCY(N_ur, double)
    #undef FUNCTION

    #define FUNCTION get_Omega0_ur_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_ur,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Omega0_ncdm
  START_CAPABILITY
    #define FUNCTION get_Omega0_ncdm_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Omega0_ncdm_tot,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY eta0
  START_CAPABILITY
    // Calculate eta0 (today) from omega_b and T_cmb
    #define FUNCTION eta0_LCDM
    START_FUNCTION(double)
    ALLOW_MODELS(LCDM, LCDM_theta)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY etaBBN
  START_CAPABILITY
    // Fallback for etaBBN if 'etaBBN_rBBN_rCMB_dNurBBN_dNurCMB'
    // cannot be used to provide the capability
    #define FUNCTION etaBBN_SM
    START_FUNCTION(double)
    DEPENDENCY(eta0,double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY rs_drag
  START_CAPABILITY
    #define FUNCTION get_rs_drag_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_rs,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // Good for cross-checks, innit.
  #define CAPABILITY Neff
  START_CAPABILITY
    #define FUNCTION get_Neff_classy
    START_FUNCTION(double)
    BACKEND_REQ(class_get_Neff,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // Compute dNeff AND etaBBN for non-standard models
  #define CAPABILITY external_dNeff_etaBBN
  START_CAPABILITY
    #define FUNCTION compute_dNeff_etaBBN_ALP
    START_FUNCTION(map_str_dbl)
    ALLOW_MODELS(GeneralCosmoALP)
    DEPENDENCY(total_DM_abundance, double)
    DEPENDENCY(lifetime, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Sigma8
  START_CAPABILITY
    #define FUNCTION get_Sigma8_classy
    START_FUNCTION(double)
    DEPENDENCY(Omega0_m, double)
    BACKEND_REQ(class_get_sigma8,(class_tag),double,())
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  // AlterBBN

  #define CAPABILITY AlterBBN_Input
  START_CAPABILITY
    #define FUNCTION AlterBBN_Input
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(etaBBN, double)
    DEPENDENCY(Neff_SM, double)
    MODEL_CONDITIONAL_DEPENDENCY(nuclear_params_neutron_lifetime_parameters,ModelParameters,nuclear_params_neutron_lifetime)
    MODEL_CONDITIONAL_DEPENDENCY(etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters,ModelParameters,etaBBN_rBBN_rCMB_dNurBBN_dNurCMB)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BBN_abundances
  START_CAPABILITY
    #define FUNCTION compute_BBN_abundances
    START_FUNCTION(BBN_container)
    DEPENDENCY(AlterBBN_Input, map_str_dbl)
    BACKEND_REQ(call_nucl_err, (libbbn), int, (map_str_dbl&,double*,double*))
    BACKEND_REQ(get_NNUC, (libbbn), int, ())
    BACKEND_REQ(get_abund_map_AlterBBN, (libbbn), map_str_int, ())
    BACKEND_OPTION( (AlterBBN), (libbbn) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY helium_abundance
  START_CAPABILITY
    #define FUNCTION extract_helium_abundance
    START_FUNCTION(double)
    DEPENDENCY(BBN_abundances, BBN_container)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BBN_LogLike
  START_CAPABILITY
    #define FUNCTION compute_BBN_LogLike
    START_FUNCTION(double)
    DEPENDENCY(BBN_abundances, BBN_container)
    #undef FUNCTION
  #undef CAPABILITY

  // ----------------------

  // MontePython

  #define CAPABILITY parameter_dict_for_MPLike
  START_CAPABILITY
    #define FUNCTION set_parameter_dict_for_MPLike
    START_FUNCTION(pybind11::dict)
    ALLOW_MODELS(cosmo_nuisance_acbar,cosmo_nuisance_spt)
    ALLOW_MODELS(cosmo_nuisance_JLA,cosmo_nuisance_Pantheon,cosmo_nuisance_BK14,cosmo_nuisance_BK14priors)
    ALLOW_MODELS(cosmo_nuisance_CFHTLens_correlation,cosmo_nuisance_euclid_lensing,cosmo_nuisance_euclid_pk,cosmo_nuisance_ISW)
    ALLOW_MODELS(cosmo_nuisance_kids450_qe_likelihood_public,cosmo_nuisance_ska,cosmo_nuisance_wmap)
    // if you implement new MontePython likelihoods with new nuisance parameters add the name of your new
    // nuisance parameter model (to be defined in Models/include/gambit/Models/models/CosmoNuisanceModels.hpp)
    ALLOW_MODELS(cosmo_nuisance_dummy)
    #undef FUNCTION

    #define FUNCTION pass_empty_parameter_dict_for_MPLike
    START_FUNCTION(pybind11::dict)
    #undef FUNCTION
  #undef CAPABILITY

  // Creates the MontePython data and likelihood objects, determining which experiments are in use in the process
  #define CAPABILITY MP_objects
  START_CAPABILITY
    #define FUNCTION create_MP_objects
    START_FUNCTION(MPLike_objects_container)
    BACKEND_REQ(create_MP_data_object,        (libmontepythonlike), pybind11::object, (map_str_str&))
    BACKEND_REQ(get_MP_available_likelihoods, (libmontepythonlike), std::vector<str>, ())
    BACKEND_REQ(create_MP_likelihood_objects, (libmontepythonlike), map_str_pyobj,    (pybind11::object&, map_str_str&))
    DEPENDENCY(parameter_dict_for_MPLike, pybind11::dict)
    #undef FUNCTION
  #undef CAPABILITY

  // Calculates lnL for individual experiments using MontePython
  #define CAPABILITY MP_LogLikes
  START_CAPABILITY
    #define FUNCTION compute_MP_LogLikes
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(parameter_dict_for_MPLike, pybind11::dict)
    DEPENDENCY(MP_objects, MPLike_objects_container)
    BACKEND_REQ(get_classy_backendDir,        (class_tag),          std::string, ())
    BACKEND_REQ(get_classy_cosmo_object,      (class_tag),          pybind11::object, ())
    BACKEND_REQ(get_MP_loglike,               (libmontepythonlike), double,           (const MPLike_data_container&, pybind11::object&, std::string&))
    #undef FUNCTION
  #undef CAPABILITY

  // Calculates the total lnL from MontePython
  #define CAPABILITY MP_Combined_LogLike
    START_CAPABILITY
    #define FUNCTION compute_MP_combined_LogLike
    START_FUNCTION(double)
    DEPENDENCY(MP_LogLikes, map_str_dbl)
    #undef FUNCTION
  #undef CAPABILITY
 
  // Retrieves the correlation coefficients and the LogLike not taking 
  // bao correlations into account from the MP likelihood "bao_correlations"
  #define CAPABILITY bao_like_correlation
    START_CAPABILITY
    #define FUNCTION get_bao_like_correlation
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(MP_LogLikes, map_str_dbl)
    DEPENDENCY(MP_objects, MPLike_objects_container)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE
