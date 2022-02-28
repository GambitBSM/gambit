//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Backend macros for SPheno (not SARAH's version)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2016 May, June
///  \date 2020 Apr
///
///  *********************************************

#define BACKENDNAME SPheno
#define BACKENDLANG FORTRAN
#define VERSION 3.3.8
#define SAFE_VERSION 3_3_8
#define REFERENCE Porod:2003um,Porod:2011nf

// Begin
LOAD_LIBRARY

// Allow for CMSSM, MSSM63atMGUT and MSSM63atQ
BE_ALLOW_MODELS(CMSSM,MSSM63atMGUT,MSSM63atQ)

// Functions
BE_FUNCTION(Set_All_Parameters_0, void, (), ("__model_data_MOD_set_all_parameters_0", "__model_data_mp_set_all_parameters_0_"), "SPheno_internal")
BE_FUNCTION(SPheno_Main, void, (), ("__spheno_MOD_spheno_main", "spheno_mp_spheno_main_"), "SPheno_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), ("__loopfunctions_MOD_initializeloopfunctions", "loopfunctions_mp_initializeloopfunctions_"), "SPheno_internal")
BE_FUNCTION(CalculateRunningMasses, void, (
  Farray_Freal8_1_3&, //mf_l_in
  Farray_Freal8_1_3&, // mf_d_in
  Farray_Freal8_1_3&, // mf_u_in
  Freal8&, // Qlow
  Freal8&, // Alpha
  Freal8&, // AlphaS
  Freal8&, // Qhigh
  Farray_Freal8_1_3&, // mf_l_out
  Farray_Freal8_1_3&, // mf_d_out
  Farray_Freal8_1_3&, // mf_u_out
  Finteger& //kont))
  ), ("__standardmodel_MOD_calculaterunningmasses", "standardmodel_mp_calculaterunningmasses_"), "SPheno_internal")
BE_FUNCTION(Switch_to_superCKM, void, (
  Farray_Fcomplex16_1_3_1_3&, // Yd
  Farray_Fcomplex16_1_3_1_3&, // Yu
  Farray_Fcomplex16_1_3_1_3&, // Ad
  Farray_Fcomplex16_1_3_1_3&, // Au
  Farray_Fcomplex16_1_3_1_3&, // md2
  Farray_Fcomplex16_1_3_1_3&, // mq2
  Farray_Fcomplex16_1_3_1_3&, // mu2
  Farray_Fcomplex16_1_3_1_3&, // Ad_ckm
  Farray_Fcomplex16_1_3_1_3&, // Au_ckm
  Farray_Fcomplex16_1_3_1_3&, // md2_ckm
  Farray_Fcomplex16_1_3_1_3&, // mq2_ckm
  Farray_Fcomplex16_1_3_1_3&, // mu2_ckm
  Flogical&, // Tranposed
  Farray_Fcomplex16_1_6_1_6&, // RSd
  Farray_Fcomplex16_1_6_1_6&, // RSu
  Farray_Fcomplex16_1_6_1_6&, // RSd_ckm
  Farray_Fcomplex16_1_6_1_6&, // RSu_ckm
  Farray_Fcomplex16_1_3_1_3&, // CKM_Q
  Farray_Freal8_1_3&, // Yd_ckm
  Farray_Freal8_1_3&  // Yu_ckm
  ), ("__model_data_MOD_switch_to_superckm", "model_data_mp_switch_to_superckm_"), "SPheno_internal")
BE_FUNCTION(Switch_to_superPMNS, void, (
  Farray_Fcomplex16_1_3_1_3&, // Yl
  Farray_Fcomplex16_1_3_1_3&, // id3C
  Farray_Fcomplex16_1_3_1_3&, // Al
  Farray_Fcomplex16_1_3_1_3&, // me2
  Farray_Fcomplex16_1_3_1_3&, // ml2
  Farray_Fcomplex16_1_3_1_3&, // Al_pmns
  Farray_Fcomplex16_1_3_1_3&, // me2_pmns
  Farray_Fcomplex16_1_3_1_3&, // ml2_pmns
  Flogical&, // Tranposed
  Farray_Fcomplex16_1_6_1_6&, // RSl
  Farray_Fcomplex16_1_3_1_3&, // Rsn
  Farray_Fcomplex16_1_6_1_6&, // RSl_pmns
  Farray_Fcomplex16_1_3_1_3&, // RSn_pmns
  Farray_Fcomplex16_1_3_1_3&, // PMNS_Q
  Farray_Freal8_1_3&  // Yl_pmns
  ), ("__model_data_MOD_switch_to_superckm", "model_data_mp_switch_to_superckm_"), "SPheno_internal")

BE_FUNCTION(GetRenormalizationScale, Freal8, (), ("__loopfunctions_MOD_getrenormalizationscale", "loopfunctions_mp_getrenormalizationscale_"), "SPheno_internal")
BE_FUNCTION(SetHighScaleModel, Flogical, (Fstring20), ("__sugraruns_MOD_sethighscalemodel", "sugraruns_mp_sethighscalemodel_"), "SPheno_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), ("__sugraruns_MOD_setrgescale", "sugraruns_mp_setrgescale_"), "SPheno_internal")
BE_FUNCTION(SetGUTScale, void, (Freal8&), ("__sugraruns_MOD_setgutscale", "sugraruns_mp_setgutscale_"), "SPheno_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), ("__sugraruns_MOD_setstrictunification", "sugraruns_mp_setstrictunification_"), "SPheno_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), ("__sugraruns_MOD_setyukawascheme", "sugraruns_mp_setyukawascheme_"), "SPheno_internal")
BE_FUNCTION(Set_Use_bsstep_instead_of_rkqs, Flogical, (Flogical&), ("__mathematics_MOD_set_use_bsstep_instead_of_rkqs", "mathematics_mp_set_use_bsstep_instead_of_rkqs_"), "SPheno_internal")
BE_FUNCTION(Set_Use_rzextr_instead_of_pzextr, Flogical, (Flogical&), ("__mathematics_MOD_set_use_rzextr_instead_of_pzextr", "mathematics_mp_set_use_rzextr_instead_of_pzextr_"), "SPheno_internal")
BE_FUNCTION(Alpha_MSbar, Freal8, (Freal8&, Freal8&), ("__loopcouplings_MOD_alpha_msbar", "loopcouplings_mp_alpha_msbar_"), "SPheno_internal")

// Variables
// MODSEL Variables
BE_VARIABLE(HighScaleModel, Fstring<15>, ("__inputoutput_MOD_highscalemodel", "inputoutput_mp_highscalemodel_"), "SPheno_internal")
// SPHENOINPUT Variables
BE_VARIABLE(ErrorLevel, Finteger, ("__control_MOD_errorlevel", "control_mp_errorlevel_"), "SPheno_internal")
BE_VARIABLE(SPA_convention, Flogical, ("__loopmasses_MOD_spa_convention", "loopmasses_mp_spa_convention_"), "SPheno_internal")
BE_VARIABLE(External_Spectrum, Flogical, ("__control_MOD_external_spectrum", "control_mp_external_spectrum_"), "SPheno_internal")
BE_VARIABLE(External_Higgs, Flogical, ("__control_MOD_external_higgs", "control_mp_external_higgs_"), "SPheno_internal")
BE_VARIABLE(FermionMassResummation, Flogical, ("__control_MOD_fermionmassresummation", "control_mp_fermionmassresummation_"), "SPheno_internal")
BE_VARIABLE(Ynu_at_MR3, Flogical, ("__sugraruns_MOD_ynu_at_mr3", "sugraruns_mp_ynu_at_mr3_"), "SPheno_internal")
BE_VARIABLE(Fixed_Nu_Yukawas, Flogical, ("__sugraruns_MOD_fixed_nu_yukawas", "sugraruns_mp_fixed_nu_yukawas_"), "SPheno_internal")
BE_VARIABLE(Only_1loop_Higgsmass, Flogical, ("__loopmasses_MOD_only_1loop_higgsmass", "loopmasses_mp_only_1loop_higgsmass_"), "SPheno_internal")
BE_VARIABLE(Calc_Mass, Flogical, ("__inputoutput_MOD_calc_mass", "inputoutput_mp_calc_mass_"), "SPheno_internal")
BE_VARIABLE(UseNewBoundaryEW, Flogical, ("__control_MOD_usenewboundaryew", "control_mp_usenewboundaryew_"), "SPheno_internal")
BE_VARIABLE(UseNewScale, Flogical, ("__control_MOD_usenewscale", "control_mp_usenewscale_"), "SPheno_internal")
BE_VARIABLE(L_BR, Flogical, ("__control_MOD_l_br", "control_mp_l_br_"), "SPheno_internal")
BE_VARIABLE(L_CS, Flogical, ("__control_MOD_l_cs", "control_mp_l_cs_"), "SPheno_internal")
BE_VARIABLE(delta_mass, Freal8, ("__control_MOD_delta_mass", "control_mp_delta_mass_"), "SPheno_internal")
BE_VARIABLE(n_run, Finteger, ("__control_MOD_n_run", "control_mp_n_run_"), "SPheno_internal")
BE_VARIABLE(WriteOut, Flogical, ("__control_MOD_writeout", "control_mp_writeout_"), "SPheno_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, ("__rges_MOD_twolooprge", "rges_mp_twolooprge_"), "SPheno_internal")
BE_VARIABLE(Write_SLHA1, Flogical, ("__inputoutput_MOD_write_slha1", "inputoutput_mp_write_slha1_"), "SPheno_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, ("__control_MOD_non_zero_exit", "control_mp_non_zero_exit_"), "SPheno_internal")
BE_VARIABLE(Model_Suchita, Flogical, ("__sugraruns_MOD_model_suchita", "sugraruns_mp_model_suchita_"), "SPheno_internal")
BE_VARIABLE(Add_RParity, Flogical, ("__inputoutput_MOD_add_rparity", "inputoutput_mp_add_rparity_"), "SPheno_internal")
BE_VARIABLE(L_Fit_RP_Parameters, Flogical, ("__control_MOD_l_fit_rp_parameters", "control_mp_l_fit_rp_parameters_"), "SPheno_internal")
BE_VARIABLE(L_CSrp, Flogical, ("__control_MOD_l_csrp", "control_mp_l_csrp_"), "SPheno_internal")
// MINPAR Variables
BE_VARIABLE(tanb, Freal8, ("__model_data_MOD_tanb", "model_data_mp_tanb_"), "SPheno_internal")
BE_VARIABLE(Mi_0, Farray_Fcomplex16_1_3, ("__model_data_MOD_mi_0", "model_data_mp_mi_0_"), "SPheno_internal")
BE_VARIABLE(M2Q_0_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2q_0_sckm", "model_data_mp_m2q_0_sckm_"), "SPheno_internal")
BE_VARIABLE(M2D_0_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2d_0_sckm", "model_data_mp_m2d_0_sckm_"), "SPheno_internal")
BE_VARIABLE(M2U_0_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2u_0_sckm", "model_data_mp_m2u_0_sckm_"), "SPheno_internal")
BE_VARIABLE(M2L_0_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2l_0_pmns", "model_data_mp_m2l_0_pmns_"), "SPheno_internal")
BE_VARIABLE(M2E_0_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2e_0_pmns", "model_data_mp_m2e_0_pmns_"), "SPheno_internal")
BE_VARIABLE(M2_R_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_r_0", "model_data_mp_m2_r_0_"), "SPheno_internal")
BE_VARIABLE(M2_H_0, Farray_Freal8_1_2, ("__model_data_MOD_m2_h_0", "model_data_mp_m2_h_0_"), "SPheno_internal")
BE_VARIABLE(M2_T_0, Farray_Freal8_1_2, ("__model_data_MOD_m2_t_0", "model_data_mp_m2_t_0_"), "SPheno_internal")
BE_VARIABLE(phase_mu, Fcomplex16, ("__model_data_MOD_phase_mu", "model_data_mp_phase_mu_"), "SPheno_internal")
BE_VARIABLE(AoY_l_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_l_0", "model_data_mp_aoy_l_0_"), "SPheno_internal")
BE_VARIABLE(AoY_nu_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_nu_0", "model_data_mp_aoy_nu_0_"), "SPheno_internal")
BE_VARIABLE(AoY_d_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_d_0", "model_data_mp_aoy_d_0_"), "SPheno_internal")
BE_VARIABLE(AoY_u_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_u_0", "model_data_mp_aoy_u_0_"), "SPheno_internal")
BE_VARIABLE(AoT_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aot_0", "model_data_mp_aot_0_"), "SPheno_internal")
BE_VARIABLE(Aolam12_0, Farray_Fcomplex16_1_2, ("__model_data_MOD_alam12_0", "model_data_mp_alam12_0_"), "SPheno_internal")
// EXTPAR Variables
BE_VARIABLE(tanb_Q, Freal8, ("__loopmasses_MOD_tanb_q", "loopmasses_mp_tanb_q_"), "SPheno_internal")
BE_VARIABLE(tanb_in_at_Q, Flogical, ("__model_data_MOD_tanb_in_at_q", "model_data_mp_tanb_in_at_q_"), "SPheno_internal")
BE_VARIABLE(Mi, Farray_Fcomplex16_1_3, ("__model_data_MOD_mi", "model_data_mp_mi_"), "SPheno_internal")
BE_VARIABLE(M2Q_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2q_sckm", "model_data_mp_m2q_sckm_"), "SPheno_internal")
BE_VARIABLE(M2D_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2d_sckm", "model_data_mp_m2d_sckm_"), "SPheno_internal")
BE_VARIABLE(M2U_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2u_sckm", "model_data_mp_m2u_sckm_"), "SPheno_internal")
BE_VARIABLE(M2L_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2l_pmns", "model_data_mp_m2l_pmns_"), "SPheno_internal")
BE_VARIABLE(M2E_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2e_pmns", "model_data_mp_m2e_pmns_"), "SPheno_internal")
BE_VARIABLE(AoY_l, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_l", "model_data_mp_aoy_l_"), "SPheno_internal")
BE_VARIABLE(AoY_nu, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_nu", "model_data_mp_aoy_nu_"), "SPheno_internal")
BE_VARIABLE(AoY_d, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_d", "model_data_mp_aoy_d_"), "SPheno_internal")
BE_VARIABLE(AoY_u, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_aoy_u", "model_data_mp_aoy_u_"), "SPheno_internal")
BE_VARIABLE(At_save, Fcomplex16, ("__model_data_MOD_at_save", "model_data_mp_at_save_"), "SPheno_internal")
BE_VARIABLE(Ab_save, Fcomplex16, ("__model_data_MOD_ab_save", "model_data_mp_ab_save_"), "SPheno_internal")
BE_VARIABLE(Atau_save, Fcomplex16, ("__model_data_MOD_ab_save", "model_data_mp_ab_save_"), "SPheno_internal")
//BE_VARIABLE(Q_in, Freal8, ("__spheno_MOD_q_in", "spheno_mp_q_in_"), "SPheno_internal")*/
BE_VARIABLE(M2_H, Farray_Freal8_1_2, ("__model_data_MOD_m2_h", "model_data_mp_m2_h_"), "SPheno_internal")
BE_VARIABLE(Au_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_au_sckm", "model_data_mp_au_sckm_"), "SPheno_internal")
BE_VARIABLE(Ad_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_ad_sckm", "model_data_mp_ad_sckm_"), "SPheno_internal")
BE_VARIABLE(Al_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_al_pmns", "model_data_mp_al_pmns_"), "SPheno_internal")
BE_VARIABLE(Au_0_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_au_0_sckm", "model_data_mp_au_0_sckm_"), "SPheno_internal")
BE_VARIABLE(Ad_0_sckm, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_ad_0_sckm", "model_data_mp_ad_0_sckm_"), "SPheno_internal")
BE_VARIABLE(Al_0_pmns, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_al_0_pmns", "model_data_mp_al_0_pmns_"), "SPheno_internal")
// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, ("__standardmodel_MOD_mz", "standardmodel_mp_mz_"), "SPheno_internal")
BE_VARIABLE(mZ2, Freal8,  ("__standardmodel_MOD_mz2", "standardmodel_mp_mz2_"), "SPheno_internal")
BE_VARIABLE(gamZ, Freal8, ("__standardmodel_MOD_gamz", "standardmodel_mp_gamz_"), "SPheno_internal")
BE_VARIABLE(gamZ2, Freal8, ("__standardmodel_MOD_gamz2", "standardmodel_mp_gamz2_"), "SPheno_internal")
BE_VARIABLE(gmZ, Freal8, ("__standardmodel_MOD_gmz", "standardmodel_mp_gmz_"), "SPheno_internal")
BE_VARIABLE(gmZ2, Freal8, ("__standardmodel_MOD_gmz2", "standardmodel_mp_gmz2_"), "SPheno_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, ("__standardmodel_MOD_brzqq", "standardmodel_mp_brzqq_"), "SPheno_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, ("__standardmodel_MOD_brzll", "standardmodel_mp_brzll_"), "SPheno_internal")
BE_VARIABLE(BrZinv, Freal8, ("__standardmodel_MOD_brzinv", "standardmodel_mp_brzinv_"), "SPheno_internal")
BE_VARIABLE(mW, Freal8, ("__standardmodel_MOD_mw", "standardmodel_mp_mw_"), "SPheno_internal")
BE_VARIABLE(mW2, Freal8, ("__standardmodel_MOD_mw2", "standardmodel_mp_mw2_"), "SPheno_internal")
BE_VARIABLE(gamW, Freal8, ("__standardmodel_MOD_gamw", "standardmodel_mp_gamw_"), "SPheno_internal")
BE_VARIABLE(gamW2, Freal8, ("__standardmodel_MOD_gamw2", "standardmodel_mp_gamw2_"), "SPheno_internal")
BE_VARIABLE(gmW, Freal8, ("__standardmodel_MOD_gmw", "standardmodel_mp_gmw_"), "SPheno_internal")
BE_VARIABLE(gmW2, Freal8, ("__standardmodel_MOD_gmw2", "standardmodel_mp_gmw2_"), "SPheno_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, ("__standardmodel_MOD_brwqq", "standardmodel_mp_brwqq_"), "SPheno_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, ("__standardmodel_MOD_brwln", "standardmodel_mp_brwln_"), "SPheno_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l", "standardmodel_mp_mf_l_"), "SPheno_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l_mz", "standardmodel_mp_mf_l_mz_"), "SPheno_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_nu", "standardmodel_mp_mf_nu_"), "SPheno_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u", "standardmodel_mp_mf_u_"), "SPheno_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u_mz", "standardmodel_mp_mf_u_mz_"), "SPheno_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d", "standardmodel_mp_mf_d_"), "SPheno_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d_mz", "standardmodel_mp_mf_d_mz_"), "SPheno_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l2", "standardmodel_mp_mf_l2_"), "SPheno_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u2", "standardmodel_mp_mf_u2_"), "SPheno_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d2", "standardmodel_mp_mf_d2_"), "SPheno_internal")
BE_VARIABLE(MNuR, Freal8, ("__model_data_MOD_mnur", "model_data_mp_mnur_"), "SPheno_internal")
BE_VARIABLE(Q_light_quarks, Freal8, ("__standardmodel_MOD_q_light_quarks", "standardmodel_mp_q_light_quarks_"), "SPheno_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, ("__standardmodel_MOD_delta_alpha_lepton", "standardmodel_mp_delta_alpha_lepton_"), "SPheno_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, ("__standardmodel_MOD_delta_alpha_hadron", "standardmodel_mp_delta_alpha_hadron_"), "SPheno_internal")
BE_VARIABLE(Alpha, Freal8, ("__standardmodel_MOD_alpha", "standardmodel_mp_alpha_"), "SPheno_internal")
BE_VARIABLE(Alpha_mZ, Freal8, ("__standardmodel_MOD_alpha_mz", "standardmodel_mp_alpha_mz_"), "SPheno_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, ("__standardmodel_MOD_alpha_mz_ms", "standardmodel_mp_alpha_mz_ms_"), "SPheno_internal")
BE_VARIABLE(MZ_input, Flogical, ("__loopcouplings_MOD_mz_input", "loopcouplings_mp_mz_input_"), "SPheno_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, ("__standardmodel_MOD_alphas_mz", "standardmodel_mp_alphas_mz_"), "SPheno_internal")
BE_VARIABLE(G_F, Freal8, ("__standardmodel_MOD_g_f", "standardmodel_mp_g_f_"), "SPheno_internal")
BE_VARIABLE(KFactorLee, Freal8, ("__standardmodel_MOD_kfactorlee", "standardmodel_mp_kfactorlee_"), "SPheno_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, ("__standardmodel_MOD_ckm", "standardmodel_mp_ckm_"), "SPheno_internal")
BE_VARIABLE(Unu, Farray_Fcomplex16_1_3_1_3, ("__standardmodel_MOD_unu", "standardmodel_mp_unu_"), "SPheno_internal")
BE_VARIABLE(lam_wolf, Freal8, ("__standardmodel_MOD_lam_wolf", "standardmodel_mp_lam_wolf_"), "SPheno_internal")
BE_VARIABLE(A_wolf, Freal8, ("__standardmodel_MOD_a_wolf", "standardmodel_mp_a_wolf_"), "SPheno_internal")
BE_VARIABLE(rho_wolf, Freal8, ("__standardmodel_MOD_rho_wolf", "standardmodel_mp_rho_wolf_"), "SPheno_internal")
BE_VARIABLE(eta_wolf, Freal8, ("__standardmodel_MOD_eta_wolf", "standardmodel_mp_eta_wolf_"), "SPheno_internal")
BE_VARIABLE(theta_12, Freal8, ("__standardmodel_MOD_theta_12", "standardmodel_mp_theta_12_"), "SPheno_internal")
BE_VARIABLE(theta_23, Freal8, ("__standardmodel_MOD_theta_23", "standardmodel_mp_theta_23_"), "SPheno_internal")
BE_VARIABLE(theta_13, Freal8, ("__standardmodel_MOD_theta_13", "standardmodel_mp_theta_13_"), "SPheno_internal")
BE_VARIABLE(delta_nu, Freal8, ("__standardmodel_MOD_delta_nu", "standardmodel_mp_delta_nu_"), "SPheno_internal")
BE_VARIABLE(alpha_nu1, Freal8, ("__standardmodel_MOD_alpha_nu1", "standardmodel_mp_alpha_nu1_"), "SPheno_internal")
BE_VARIABLE(alpha_nu2, Freal8, ("__standardmodel_MOD_alpha_nu2", "standardmodel_mp_alpha_nu2_"), "SPheno_internal")
// EWSB Variables
BE_VARIABLE(mu, Fcomplex16, ("__model_data_MOD_mu", "model_data_mp_mu_"), "SPheno_internal")
BE_VARIABLE(B, Fcomplex16, ("__model_data_MOD_b", "model_data_mp_b_"), "SPheno_internal")
// MASS and output Variables
BE_VARIABLE(ChiPm, Farray_particle23_1_2, ("__mssm_data_MOD_chipm", "mssm_data_mp_chipm_"), "SPheno_internal")
BE_VARIABLE(U, Farray_Fcomplex16_1_2_1_2, ("__model_data_MOD_u", "model_data_mp_u_"), "SPheno_internal")
BE_VARIABLE(V, Farray_Fcomplex16_1_2_1_2, ("__model_data_MOD_v", "model_data_mp_v_"), "SPheno_internal")
BE_VARIABLE(Chi0, Farray_particle23_1_4, ("__mssm_data_MOD_chi0", "mssm_data_mp_chi0_"), "SPheno_internal")
BE_VARIABLE(N, Farray_Fcomplex16_1_4_1_4, ("__model_data_MOD_n", "model_data_mp_n_"), "SPheno_internal")
BE_VARIABLE(S0, Farray_particle23_1_2, ("__mssm_data_MOD_s0", "mssm_data_mp_s0_"), "SPheno_internal")
BE_VARIABLE(RS0, Farray_Freal8_1_2_1_2, ("__mssm_data_MOD_rs0", "mssm_data_mp_rs0_"), "SPheno_internal")
BE_VARIABLE(P0, Farray_particle2_1_2, ("__mssm_data_MOD_p0", "mssm_data_mp_p0_"), "SPheno_internal")
BE_VARIABLE(RP0, Farray_Freal8_1_2_1_2, ("__model_data_MOD_rp0", "model_data_mp_rp0_"), "SPheno_internal")
BE_VARIABLE(Spm, Farray_particle2_1_2, ("__mssm_data_MOD_spm", "mssm_data_mp_spm_"), "SPheno_internal")
BE_VARIABLE(RSpm, Farray_Fcomplex16_1_2_1_2, ("__model_data_MOD_rspm", "model_data_mp_rspm_"), "SPheno_internal")
BE_VARIABLE(Sdown, Farray_particle2_1_6, ("__mssm_data_MOD_sdown", "mssm_data_mp_sdown_"), "SPheno_internal")
BE_VARIABLE(RSdown, Farray_Fcomplex16_1_6_1_6, ("__model_data_MOD_rsdown", "model_data_mp_rsdown_"), "SPheno_internal")
BE_VARIABLE(Sup, Farray_particle23_1_6, ("__mssm_data_MOD_sup", "mssm_data_mp_sup_"), "SPheno_internal")
BE_VARIABLE(RSup, Farray_Fcomplex16_1_6_1_6, ("__model_data_MOD_rsup", "model_data_mp_rsup_"), "SPheno_internal")
BE_VARIABLE(Slepton, Farray_particle23_1_6, ("__mssm_data_MOD_slepton", "mssm_data_mp_slepton_"), "SPheno_internal")
BE_VARIABLE(RSlepton, Farray_Fcomplex16_1_6_1_6, "__model_data_MOD_rslepton",  "SPheno_internal")
BE_VARIABLE(Sneut, Farray_particle23_1_3, ("__mssm_data_MOD_sneut", "mssm_data_mp_sneut_"), "SPheno_internal")
BE_VARIABLE(RSneut, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_rsneut", "model_data_mp_rsneut_"), "SPheno_internal")
BE_VARIABLE(Glu, particle23, ("__mssm_data_MOD_glu", "mssm_data_mp_glu_"), "SPheno_internal")
BE_VARIABLE(gauge, Farray_Freal8_1_3, ("__model_data_MOD_gauge", "model_data_mp_gauge_"), "SPheno_internal")
BE_VARIABLE(gauge_0, Farray_Freal8_1_3, ("__model_data_MOD_gauge_0", "model_data_mp_gauge_0_"), "SPheno_internal")
BE_VARIABLE(Y_l, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_l", "model_data_mp_y_l_"), "SPheno_internal")
BE_VARIABLE(Y_d, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_d", "model_data_mp_y_d_"), "SPheno_internal")
BE_VARIABLE(Y_u, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_u", "model_data_mp_y_u_"), "SPheno_internal")
BE_VARIABLE(Y_u_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_u_0", "model_data_mp_y_u_0_"), "SPheno_internal")
BE_VARIABLE(Y_d_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_d_0", "model_data_mp_y_d_0_"), "SPheno_internal")
BE_VARIABLE(Y_l_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_y_l_0", "model_data_mp_y_l_0_"), "SPheno_internal")
BE_VARIABLE(A_l, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_a_l", "model_data_mp_a_l_"), "SPheno_internal")
BE_VARIABLE(A_d, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_a_d", "model_data_mp_a_d_"), "SPheno_internal")
BE_VARIABLE(A_u, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_a_u", "model_data_mp_a_u_"), "SPheno_internal")
BE_VARIABLE(A_d_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_a_d_0", "model_data_mp_a_d_0_"), "SPheno_internal")
BE_VARIABLE(A_u_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_a_u_0", "model_data_mp_a_u_0_"), "SPheno_internal")
BE_VARIABLE(M2_E, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_e", "model_data_mp_m2_e_"), "SPheno_internal")
BE_VARIABLE(M2_L, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_l", "model_data_mp_m2_l_"), "SPheno_internal")
BE_VARIABLE(M2_D, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_d", "model_data_mp_m2_d_"), "SPheno_internal")
BE_VARIABLE(M2_Q, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_q", "model_data_mp_m2_q_"), "SPheno_internal")
BE_VARIABLE(M2_U, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_u", "model_data_mp_m2_u_"), "SPheno_internal")
BE_VARIABLE(M2_D_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_d_0", "model_data_mp_m2_d_0_"), "SPheno_internal")
BE_VARIABLE(M2_Q_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_q_0", "model_data_mp_m2_q_0_"), "SPheno_internal")
BE_VARIABLE(M2_U_0, Farray_Fcomplex16_1_3_1_3, ("__model_data_MOD_m2_u_0", "model_data_mp_m2_u_0_"), "SPheno_internal")
BE_VARIABLE(vev_Q, Freal8, ("__loopmasses_MOD_vev_q", "loopmasses_mp_vev_q_"), "SPheno_internal")
BE_VARIABLE(mA2_Q, Freal8, ("__loopmasses_MOD_ma2_q", "loopmasses_mp_ma2_q_"), "SPheno_internal")
// Control Variables
BE_VARIABLE(GenerationMixing, Flogical, ("__control_MOD_generationmixing", "control_mp_generationmixing_"), "SPheno_internal")
BE_VARIABLE(epsI, Freal8, ("__spheno_MOD_epsi", "spheno_mp_epsi_"), "SPheno_internal")
BE_VARIABLE(deltaM, Freal8, ("__spheno_MOD_deltam", "spheno_mp_deltam_"), "SPheno_internal")
BE_VARIABLE(kont, Finteger, ("__spheno_MOD_kont", "spheno_mp_kont_"), "SPheno_internal")
BE_VARIABLE(ErrCan, Finteger, ("__control_MOD_errcan", "control_mp_errcan_"), "SPheno_internal")
BE_VARIABLE(ErrorHandler_cptr, fptr_void, ("__control_MOD_errorhandler_cptr", "control_mp_errorhandler_cptr_"), "SPheno_internal")
BE_VARIABLE(SilenceOutput, Flogical, ("__control_MOD_silenceoutput", "control_mp_silenceoutput"), "SPheno_internal")
BE_VARIABLE(Math_Error, Farray_Fstring60_1_31, ("__control_MOD_math_error", "control_mp_math_error"), "SPheno_internal")
BE_VARIABLE(SM_Error, Farray_Fstring60_1_2, ("__control_MOD_sm_error", "control_mp_sm_error"), "SPheno_internal")
BE_VARIABLE(SusyM_Error, Farray_Fstring60_1_33, ("__control_MOD_susym_error", "control_mp_susym_error"), "SPheno_internal")
BE_VARIABLE(InOut_Error, Farray_Fstring60_1_15, ("__control_MOD_inout_error", "control_mp_inout_error"), "SPheno_internal")
BE_VARIABLE(Sugra_Error, Farray_Fstring60_1_22, ("__control_MOD_sugra_error", "control_mp_sugra_error"), "SPheno_internal")
BE_VARIABLE(LoopMass_Error, Farray_Fstring60_1_25, ("__control_MOD_loopmass_error", "control_mp_loopmass_error"), "SPheno_internal")
BE_VARIABLE(TwoLoopHiggs_Error, Farray_Fstring60_1_9, ("__control_MOD_twoloophiggs_error", "control_mp_twoloophiggs_error"), "SPheno_internal")
BE_VARIABLE(MathQP_Error, Farray_Fstring60_1_10, ("__control_MOD_mathqp_error", "control_mp_mathqp_error"), "SPheno_internal")
BE_VARIABLE(YukScen, Flogical, ("__sugraruns_MOD_yukscen", "sugraruns_MOD_yukscen"), "SPheno_internal")
// Other variables
BE_VARIABLE(vevSM, Farray_Freal8_1_2, ("__model_data_MOD_vevsm", "model_data_mp_vevsm_"), "SPheno_internal")
BE_VARIABLE(m_GUT, Freal8, ("__spheno_MOD_m_gut", "spheno_mp_m_gut_"), "SPheno_internal")
BE_VARIABLE(ratioWoM, Freal8, ("__spheno_MOD_ratiowom", "spheno_mp_ratiowom_"),  "SPheno_internal")
BE_VARIABLE(CalcTBD, Flogical, ("__spheno_MOD_calctbd", "spheno_mp_calctbd_"), "SPheno_internal")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SPheno_MSSMspectrum")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const Finputs&), "SPheno_internal")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SPheno_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SPheno_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SPheno_internal")

// Initialisation functions (dependencies)


// End
#include "gambit/Backends/backend_undefs.hpp"
