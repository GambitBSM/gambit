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
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 May, June
///
///  *********************************************

#define BACKENDNAME SPheno
#define BACKENDLANG FORTRAN
#define VERSION 3.3.8
#define SAFE_VERSION 3_3_8

// Begin
LOAD_LIBRARY

// Allow for CMSSM, MSSM63atMGUT and MSSM63atQ
BE_ALLOW_MODELS(CMSSM,MSSM63atMGUT,MSSM63atQ)

// Functions
BE_FUNCTION(Set_All_Parameters_0, void, (), "__model_data_MOD_set_all_parameters_0", "SPheno_internal")
BE_FUNCTION(Initialize_MSSM, void, (Flogical&, // GenerationMixing
				Finteger&, // id_gl
				Finteger&, // id_ph
				Finteger&, // id_Z
				Finteger&, // id_W
				Farray_Finteger_1_3&, // id_nu
				Farray_Finteger_1_3&, // id_l
				Farray_Finteger_1_3&, // id_d
				Farray_Finteger_1_3&, // id_u
				Finteger&), // id_grav
	"__mssm_data_MOD_initialize_mssm", "SPheno_internal") 
BE_FUNCTION(InitializeLoopFunctions, void, (), "__loopfunctions_MOD_initializeloopfunctions", "SPheno_internal")
BE_FUNCTION(CalculateRunningMasses, void, (Farray_Freal8_1_3&, //mf_l_in
					Farray_Freal8_1_3&, // mf_d_in
					Farray_Freal8_1_3&, // mf_u_in
					Freal8&, // Qlow
                                        Freal8&, // Alpha
                                        Freal8&, // AlphaS
                                        Freal8&, // Qhigh
                                        Farray_Freal8_1_3&, // mf_l_out
                                        Farray_Freal8_1_3&, // mf_d_out
                                        Farray_Freal8_1_3&, // mf_u_out 
                                        Finteger&), //kont))
	 "__standardmodel_MOD_calculaterunningmasses", "SPheno_internal")
BE_FUNCTION(CalculateSpectrum, void, 
	(Finteger&, // n_run
	 Freal8&, // delta
	 Flogical&, // WriteOut
	 Finteger&, // kont
	 Freal8&, // tanb
	 Farray_Freal8_1_2&, // vevSM
	 Farray_Freal8_1_2&, // mC
	 Farray_Fcomplex16_1_2_1_2&, // U
	 Farray_Fcomplex16_1_2_1_2&, // V
	 Farray_Freal8_1_4&, // mN
	 Farray_Fcomplex16_1_4_1_4&, // N
	 Farray_Freal8_1_2&, // mS0
	 Farray_Freal8_1_2&, // mS02
	 Farray_Freal8_1_2_1_2&, // RS0
	 Farray_Freal8_1_2&, // mP0
	 Farray_Freal8_1_2&, // mP02
	 Farray_Freal8_1_2_1_2&, // RP0
	 Farray_Freal8_1_2&, // mSpm
	 Farray_Freal8_1_2&, // mSpm2
	 Farray_Fcomplex16_1_2_1_2&, // RSpm
	 Farray_Freal8_1_6&, //mSdown
	 Farray_Freal8_1_6&, // mSdown2
	 Farray_Fcomplex16_1_6_1_6&, // RSdown
	 Farray_Freal8_1_6&, // mSup
	 Farray_Freal8_1_6&, // mSup2
	 Farray_Fcomplex16_1_6_1_6&, // RSup
	 Farray_Freal8_1_6&, // mSlepton
	 Farray_Freal8_1_6&, // mSlepton2
	 Farray_Fcomplex16_1_6_1_6&, // RSlepton
	 Farray_Freal8_1_3&, // mSneut
	 Farray_Freal8_1_3&, // mSneut2
	 Farray_Fcomplex16_1_3_1_3&, // RSneut
	 Freal8&, // mGlu
	 Fcomplex16&, // PhaseGlu
	 Farray_Freal8_1_3&, // gauge
	 Farray_Fcomplex16_1_3_1_3&, // uL_L
 	 Farray_Fcomplex16_1_3_1_3&, // uL_R
	 Farray_Fcomplex16_1_3_1_3&, // uD_L
	 Farray_Fcomplex16_1_3_1_3&, // uD_R
	 Farray_Fcomplex16_1_3_1_3&, // uU_L
	 Farray_Fcomplex16_1_3_1_3&, // uU_R
	 Farray_Fcomplex16_1_3_1_3&, // Y_l
	 Farray_Fcomplex16_1_3_1_3&, // Y_d
	 Farray_Fcomplex16_1_3_1_3&, // Y_u
	 Farray_Fcomplex16_1_3&, // Mi
	 Farray_Fcomplex16_1_3_1_3&, // A_l
	 Farray_Fcomplex16_1_3_1_3&, // A_d
	 Farray_Fcomplex16_1_3_1_3&, // A_u
	 Farray_Fcomplex16_1_3_1_3&, // M2_E
	 Farray_Fcomplex16_1_3_1_3&, // M2_L
	 Farray_Fcomplex16_1_3_1_3&, // M2_D
	 Farray_Fcomplex16_1_3_1_3&, // M2_Q
	 Farray_Fcomplex16_1_3_1_3&, // M2_U
	 Farray_Freal8_1_2&, // M2_H
	 Fcomplex16&, // mu
	 Fcomplex16&, // B
	 Freal8& //  m_GUT
	), "__spheno_MOD_calculatespectrum", "SPheno_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), "__loopfunctions_MOD_getrenormalizationscale", "SPheno_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), "__sugraruns_MOD_setrgescale", "SPheno_internal")
BE_FUNCTION(SetHighScaleModel, Flogical, (Fstring<20>), "__sugraruns_MOD_sethighscalemodel", "SPheno_internal")
BE_FUNCTION(SetWriteMinBr, void, (Freal8&), "__inputoutput_MOD_setwriteminbr", "SPheno_internal")
BE_FUNCTION(SetWriteMinSig, void, (Freal8&), "__inputoutput_MOD_setwriteminsig", "SPheno_internal")
BE_FUNCTION(SetGUTScale, void, (Freal8&), "__sugraruns_MOD_setgutscale", "SPheno_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), "__sugraruns_MOD_setstrictunification", "SPheno_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), "__sugraruns_MOD_setyukawascheme", "SPheno_internal")
BE_FUNCTION(Set_Use_bsstep_instead_of_rkqs, Flogical, (Flogical&), "__mathematics_MOD_set_use_bsstep_instead_of_rkqs", "SPheno_internal")
BE_FUNCTION(Set_Use_rzextr_instead_of_pzextr, Flogical, (Flogical&), "__mathematics_MOD_set_use_rzextr_instead_of_pzextr", "SPheno_internal")
BE_FUNCTION(Alpha_MSbar, Freal8, (Freal8&, Freal8&), "__loopcouplings_MOD_alpha_msbar", "SPheno_internal")
BE_FUNCTION(Low_Energy_Constraints_MSSM, void,
        (Freal8&, // Q_in
         Farray_Freal8_1_3&, // gauge
         Farray_Fcomplex16_1_3_1_3&, // Y_l
         Farray_Fcomplex16_1_3_1_3&, // Y_d
         Farray_Fcomplex16_1_3_1_3&, // Y_u
         Farray_Fcomplex16_1_3_1_3&, // A_l 
         Farray_Fcomplex16_1_3_1_3&, // A_d
         Farray_Fcomplex16_1_3_1_3&, // A_u
         Farray_Fcomplex16_1_3&, // Mi
         Fcomplex16&, // mu
         Farray_Fcomplex16_1_3_1_3&, // M2_E
         Farray_Fcomplex16_1_3_1_3&, // M2_L
         Farray_Fcomplex16_1_3_1_3&, // M2_D
         Farray_Fcomplex16_1_3_1_3&, // M2_Q
         Farray_Fcomplex16_1_3_1_3&, // M2_U
         Farray_Freal8_1_2&, // M2_H
         Fcomplex16&, // B
         Freal8&, // tanb_Q
         Farray_Freal8_1_2&, // mP02
         Farray_Freal8_1_2&, // mS02
         Farray_Freal8_1_2&, // mSpm2
         Farray_Fcomplex16_1_3_1_3&, // CKM
         Finteger&, // kont
         Flogical&, // GenerationMixing
         Freal8&, // rho_parameter
         Fcomplex16&, //DeltaMBd
         Freal8&, // BRBtosgamma
         Farray_Freal8_1_3&, // Bs_ll
         Farray_Freal8_1_3&, // Bd_ll
         Freal8&, // BrBToSLL
         Freal8&, // BtoSNuNu
         Freal8&, // BR_Bu_TauNu
         Freal8&, // R_Bu_TauNu
         Freal8&, // epsK
         Freal8&, // DeltaMK2
         Freal8&, // K0toPi0NuNu
         Freal8&, // KptoPipNuNu
         Freal8&, // a_e
         Freal8&, // a_mu
         Freal8&, // a_tau
         Freal8&, // d_e
         Freal8&, // d_mu
         Freal8&, // d_tau
         Freal8&, // BrMutoEGamma
         Freal8&, // BrTautoEGamma
         Freal8&, // BrTautoMuGamma
         Freal8&, // BrMu3e
         Freal8&, // BrTau3e
         Freal8&, // BrTau3Mu
         Freal8&, // BR_Z_e_mu
         Freal8&, // BR_Z_e_tau 
         Freal8& // BR_Z_mu_tau
       ), "__lowenergy_MOD_low_energy_constraints_mssm", "SPheno_internal")    

BE_FUNCTION(CalculateBR_MSSM, void, 
	(Finteger&, // n_nu
         Farray_Finteger_1_3&, // id_nu
         Finteger&, // n_l
         Farray_Finteger_1_3&, // id_l
         Finteger&, // n_d
         Farray_Finteger_1_3&, // id_d
         Finteger&, // n_u
         Farray_Finteger_1_3&, // id_u
         Finteger&, // n_Z
         Finteger&, // id_Z
         Finteger&, // n_W
         Finteger&, // id_W
         Finteger&, // n_Snu
         Finteger&, // n_Sle
         Finteger&, // n_Sd
         Finteger&, // n_Su
         Finteger&, // n_N
         Finteger&, // n_C
         Finteger&, // n_g
         Finteger&, // n_S0
         Finteger&, // n_P0
         Finteger&, // n_Spm
         Finteger&, // id_grav
         Finteger&, // id_gl
         Finteger&, // id_ph
         Farray_Freal8_1_3&, //gauge
         particle23&, // Glu
         Fcomplex16&, // PhaseGlu
         Farray_particle23_1_2&, // ChiPm
         Farray_Fcomplex16_1_2_1_2&, // U
         Farray_Fcomplex16_1_2_1_2&, // V
         Farray_particle23_1_4&, // Chi0
         Farray_Fcomplex16_1_4_1_4&, // N
         Farray_particle23_1_3&, // Sneut
         Farray_Fcomplex16_1_3_1_3&, // RSneut
         Farray_particle23_1_6&, // Slepton
         Farray_Fcomplex16_1_6_1_6&, // RSlepton
         Farray_particle23_1_6&, // Sup
         Farray_Fcomplex16_1_6_1_6&, // RSup
         Farray_particle2_1_6&, // Sdown
         Farray_Fcomplex16_1_6_1_6&, // RSdown
         Farray_Fcomplex16_1_3_1_3&, // uL_L
         Farray_Fcomplex16_1_3_1_3&, // uL_R
         Farray_Fcomplex16_1_3_1_3&, // uD_L
         Farray_Fcomplex16_1_3_1_3&, // uD_R
         Farray_Fcomplex16_1_3_1_3&, // uU_L
         Farray_Fcomplex16_1_3_1_3&, // uU_R
         Farray_particle23_1_2&, // S0
         Farray_Freal8_1_2_1_2&, // RS0
         Farray_particle2_1_2&, // P0
         Farray_Freal8_1_2_1_2&, // RP0
         Farray_particle2_1_2&, // Spm
         Farray_Fcomplex16_1_2_1_2&, // RSpm
         Freal8&, // epsI
         Freal8&, // deltaM
         Flogical&, // CalcTBD
         Freal8&, // rationWoM
         Farray_Fcomplex16_1_3_1_3&, // Y_d
         Farray_Fcomplex16_1_3_1_3&, // A_d
         Farray_Fcomplex16_1_3_1_3&, // Y_l
         Farray_Fcomplex16_1_3_1_3&, // A_l
         Farray_Fcomplex16_1_3_1_3&, // Y_u
         Farray_Fcomplex16_1_3_1_3&, // A_u
         Fcomplex16&, // mu
         Farray_Freal8_1_2&, // vevSM
         Freal8&, // F_Gmsb
         Freal8&, // m32
         Freal8& // grav_fac
        ), "__branchingratios_MOD_calculatebr_mssm", "SPheno_internal")
BE_FUNCTION(CalculateCrossSectionsMSSM, void,
        (Freal8&, // Ecms
         Freal8&, // Pm
         Freal8&, // Pp
         Flogical&, // ISR
         Flogical&, // Beam
         Fstring<20>&, // "Tesla800"
         Farray_Freal8_1_6&, //  mSup
         Farray_Fcomplex16_1_6_1_6&, // RSup
         Farray_Freal8_1_3&, // mf_u 
         Farray_Freal8_1_6&, // mSdown
         Farray_Fcomplex16_1_6_1_6&, // RSdown
         Farray_Freal8_1_3&, // mf_d
         Freal8&, // mGlu
         Farray_Freal8_1_6_1_6&, // SigSup
         Farray_Freal8_1_6_1_6&, // SigSdown
         Farray_Freal8_1_6&, // mSlepton
         Farray_Fcomplex16_1_6_1_6&, // RSlepton
         Farray_Fcomplex16_1_3_1_3&, // Ylp
         Farray_Freal8_1_3&, // mSneut
         Farray_Fcomplex16_1_3_1_3&, // RSneut
         Farray_Freal8_1_6_1_6&, // SigSle
         Farray_Freal8_1_3_1_3&, // SigSn
         Farray_Freal8_1_2&, // mChiPm
         Farray_Fcomplex16_1_2_1_2&, // U
         Farray_Fcomplex16_1_2_1_2&, // V
         Farray_Freal8_1_4&, // mChi0
         Farray_Fcomplex16_1_4_1_4&, // N 
         Farray_Freal8_1_2_1_2&, // SigC
         Farray_Freal8_1_4_1_4&, // SigChi0
         Farray_Freal8_1_2&, // mS0
         Farray_Freal8_1_2_1_2&, // RS0
         Farray_Freal8_1_2&, // vevSM
         Farray_Freal8_1_2&, // mP0
         Farray_Freal8_1_2_1_2&, // RP0
         Farray_Freal8_1_2&, // mSpm
         Farray_Fcomplex16_1_2_1_2&, // RSpm
         Farray_Freal8_1_2&, // SigS0
         Farray_Freal8_1_2&, // SigSP
         Freal8& // SigHp
       ), "__epluseminusproduction_MOD_calculatecrosssectionsmssm", "SPheno_internal")

// Variables
// MODSEL Variables
BE_VARIABLE(HighScaleModel, Fstring<15>, "__inputoutput_MOD_highscalemodel", "SPheno_internal")
// SPHENOINPUT Variables
BE_VARIABLE(ErrorLevel, Finteger, "__control_MOD_errorlevel", "SPheno_internal")
BE_VARIABLE(SPA_convention, Flogical, "__loopmasses_MOD_spa_convention", "SPheno_internal")
BE_VARIABLE(External_Spectrum, Flogical, "__control_MOD_external_spectrum", "SPheno_internal")
BE_VARIABLE(External_Higgs, Flogical, "__control_MOD_external_higgs", "SPheno_internal")
BE_VARIABLE(Use_Flavour_States, Flogical, "__inputoutput_MOD_use_flavour_states", "SPheno_internal")
BE_VARIABLE(FermionMassResummation, Flogical, "__control_MOD_fermionmassresummation", "SPheno_internal")
BE_VARIABLE(Ynu_at_MR3, Flogical, "__sugraruns_MOD_ynu_at_mr3", "SPheno_internal")
BE_VARIABLE(Fixed_Nu_Yukawas, Flogical, "__sugraruns_MOD_fixed_nu_yukawas", "SPheno_internal")
BE_VARIABLE(Only_1loop_Higgsmass, Flogical, "__loopmasses_MOD_only_1loop_higgsmass", "SPheno_internal")
BE_VARIABLE(Calc_Mass, Flogical, "__inputoutput_MOD_calc_mass", "SPheno_internal")
BE_VARIABLE(UseNewBoundaryEW, Flogical, "__control_MOD_usenewboundaryew", "SPheno_internal")
BE_VARIABLE(UseNewScale, Flogical, "__control_MOD_usenewscale", "SPheno_internal")
BE_VARIABLE(L_BR, Flogical, "__control_MOD_l_br", "SPheno_internal")
BE_VARIABLE(BR_Higgs_with_offshell_V, Flogical, "__inputoutput_MOD_br_higgs_with_offshell_v", "SPheno_internal")
BE_VARIABLE(L_CS, Flogical, "__control_MOD_l_cs", "SPheno_internal")
BE_VARIABLE(delta_mass, Freal8, "__control_MOD_delta_mass", "SPheno_internal")
BE_VARIABLE(n_run, Finteger, "__control_MOD_n_run", "SPheno_internal")
BE_VARIABLE(WriteOut, Flogical, "__control_MOD_writeout", "SPheno_internal") 
BE_VARIABLE(TwoLoopRGE, Flogical, "__rges_MOD_twolooprge", "SPheno_internal")
BE_VARIABLE(Write_SLHA1, Flogical, "__inputoutput_MOD_write_slha1", "SPheno_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, "__control_MOD_non_zero_exit", "SPheno_internal")
BE_VARIABLE(Model_Suchita, Flogical, "__sugraruns_MOD_model_suchita", "SPheno_internal")
BE_VARIABLE(Add_RParity, Flogical, "__inputoutput_MOD_add_rparity", "SPheno_internal")
BE_VARIABLE(L_Fit_RP_Parameters, Flogical, "__control_MOD_l_fit_rp_parameters", "SPheno_internal")
BE_VARIABLE(L_RP_Pythia, Flogical, "__inputoutput_MOD_l_rp_pythia", "SPheno_internal")
BE_VARIABLE(L_CSrp, Flogical, "__control_MOD_l_csrp", "SPheno_internal")
BE_VARIABLE(io_RP, Finteger, "__inputoutput_MOD_io_rp", "SPheno_internal")
BE_VARIABLE(MADGraph_style, Flogical, "__inputoutput_MOD_madgraph_sytle", "SPheno_internal")
BE_VARIABLE(LWrite_LHC_Observables, Flogical, "__inputoutput_MOD_lwrite_lhc_observables", "SPheno_internal")
// MINPAR Variables
BE_VARIABLE(tanb, Freal8, "__model_data_MOD_tanb", "SPheno_internal")

BE_VARIABLE(Mi_0, Farray_Fcomplex16_1_3, "__model_data_MOD_mi_0", "SPheno_internal")
BE_VARIABLE(M2Q_0_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2q_0_sckm", "SPheno_internal")
BE_VARIABLE(M2D_0_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2d_0_sckm", "SPheno_internal")
BE_VARIABLE(M2U_0_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2u_0_sckm", "SPheno_internal")
BE_VARIABLE(M2L_0_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2l_0_pmns", "SPheno_internal")
BE_VARIABLE(M2E_0_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2e_0_pmns", "SPheno_internal")
BE_VARIABLE(M2_R_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_r_0", "SPheno_internal")
BE_VARIABLE(M2_H_0, Farray_Freal8_1_2, "__model_data_MOD_m2_h_0", "SPheno_internal")
BE_VARIABLE(M2_T_0, Farray_Freal8_1_2, "__model_data_MOD_m2_t_0", "SPheno_internal")
BE_VARIABLE(phase_mu, Fcomplex16, "__model_data_MOD_phase_mu", "SPheno_internal")
BE_VARIABLE(AoY_l_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_l_0", "SPheno_internal")
BE_VARIABLE(AoY_nu_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_nu_0", "SPheno_internal")
BE_VARIABLE(AoY_d_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_d_0", "SPheno_internal")
BE_VARIABLE(AoY_u_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_u_0", "SPheno_internal")
BE_VARIABLE(AoT_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aot_0", "SPheno_internal")
BE_VARIABLE(Aolam12_0, Farray_Fcomplex16_1_2, "__model_data_MOD_alam12_0", "SPheno_internal")
// GMSB Variables
BE_VARIABLE(F_GMSB, Freal8, "__sugraruns_MOD_f_gmsb", "SPheno_internal")
BE_VARIABLE(m32, Freal8, "__sugraruns_MOD_m32", "SPheno_internal")
BE_VARIABLE(grav_fac, Freal8, "__inputoutput_MOD_grav_fac", "SPheno_internal")
BE_VARIABLE(Lambda, Freal8, "__sugraruns_MOD_lambda", "SPheno_internal")
BE_VARIABLE(MLambdaS, Freal8, "__sugraruns_MOD_mlambdas", "SPheno_internal")
BE_VARIABLE(n5plets, Freal8, "__sugraruns_MOD_n5plets", "SPheno_internal")
BE_VARIABLE(n10plets, Finteger, "__sugraruns_MOD_n10plets", "SPheno_internal")
// AMSB Variables
BE_VARIABLE(M0_amsb, Freal8, "__sugraruns_MOD_m0_amsb", "SPheno_internal")
BE_VARIABLE(M_32, Freal8, "__sugraruns_MOD_m_32", "SPheno_internal")
// EXTPAR Variables
BE_VARIABLE(tanb_Q, Freal8, "__loopmasses_MOD_tanb_q", "SPheno_internal")
BE_VARIABLE(tanb_in_at_Q, Flogical, "__model_data_MOD_tanb_in_at_q", "SPheno_internal")
BE_VARIABLE(Mi, Farray_Fcomplex16_1_3, "__model_data_MOD_mi", "SPheno_internal")
BE_VARIABLE(M2Q_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2q_sckm", "SPheno_internal")
BE_VARIABLE(M2D_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2d_sckm", "SPheno_internal")
BE_VARIABLE(M2U_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2u_sckm", "SPheno_internal")
BE_VARIABLE(M2L_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2l_pmns", "SPheno_internal")
BE_VARIABLE(M2E_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2e_pmns", "SPheno_internal")
BE_VARIABLE(AoY_l, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_l", "SPheno_internal")
BE_VARIABLE(AoY_nu, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_nu", "SPheno_internal")
BE_VARIABLE(AoY_d, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_d", "SPheno_internal")
BE_VARIABLE(AoY_u, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_aoy_u", "SPheno_internal")
BE_VARIABLE(At_save, Fcomplex16, "__model_data_MOD_at_save", "SPheno_internal")
BE_VARIABLE(Ab_save, Fcomplex16, "__model_data_MOD_ab_save", "SPheno_internal")
BE_VARIABLE(Atau_save, Fcomplex16, "__model_data_MOD_ab_save", "SPheno_internal")
BE_VARIABLE(Q_in, Freal8, "__spheno_MOD_q_in", "SPheno_internal")
BE_VARIABLE(M2_H, Farray_Freal8_1_2, "__model_data_MOD_m2_h", "SPheno_internal")
BE_VARIABLE(Au_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_au_sckm", "SPheno_internal")
BE_VARIABLE(Ad_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ad_sckm", "SPheno_internal")
BE_VARIABLE(Al_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_al_pmns", "SPheno_internal")
BE_VARIABLE(Au_0_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_au_0_sckm", "SPheno_internal")
BE_VARIABLE(Ad_0_sckm, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ad_0_sckm", "SPheno_internal")
BE_VARIABLE(Al_0_pmns, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_al_0_pmns", "SPheno_internal")
// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, "__standardmodel_MOD_mz", "SPheno_internal")
BE_VARIABLE(mZ2, Freal8,  "__standardmodel_MOD_mz2", "SPheno_internal")
BE_VARIABLE(gamZ, Freal8, "__standardmodel_MOD_gamz", "SPheno_internal")
BE_VARIABLE(gamZ2, Freal8, "__standardmodel_MOD_gamz2", "SPheno_internal")
BE_VARIABLE(gmZ, Freal8, "__standardmodel_MOD_gmz", "SPheno_internal")
BE_VARIABLE(gmZ2, Freal8, "__standardmodel_MOD_gmz2", "SPheno_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, "__standardmodel_MOD_brzqq", "SPheno_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, "__standardmodel_MOD_brzll", "SPheno_internal")
BE_VARIABLE(BrZinv, Freal8, "__standardmodel_MOD_brzinv", "SPheno_internal")
BE_VARIABLE(mW, Freal8, "__standardmodel_MOD_mw", "SPheno_internal")
BE_VARIABLE(mW2, Freal8, "__standardmodel_MOD_mw2", "SPheno_internal")
BE_VARIABLE(gamW, Freal8, "__standardmodel_MOD_gamw", "SPheno_internal")
BE_VARIABLE(gamW2, Freal8, "__standardmodel_MOD_gamw2", "SPheno_internal")
BE_VARIABLE(gmW, Freal8, "__standardmodel_MOD_gmw", "SPheno_internal")
BE_VARIABLE(gmW2, Freal8, "__standardmodel_MOD_gmw2", "SPheno_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, "__standardmodel_MOD_brwqq", "SPheno_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, "__standardmodel_MOD_brwln", "SPheno_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l", "SPheno_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l_mz", "SPheno_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, "__standardmodel_MOD_mf_nu", "SPheno_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u", "SPheno_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u_mz", "SPheno_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d", "SPheno_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d_mz", "SPheno_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l2", "SPheno_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u2", "SPheno_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d2", "SPheno_internal")
BE_VARIABLE(MNuR, Freal8, "__model_data_MOD_mnur", "SPheno_internal")
BE_VARIABLE(Q_light_quarks, Freal8, "__standardmodel_MOD_q_light_quarks", "SPheno_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, "__standardmodel_MOD_delta_alpha_lepton", "SPheno_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, "__standardmodel_MOD_delta_alpha_hadron", "SPheno_internal")
BE_VARIABLE(Alpha, Freal8, "__standardmodel_MOD_alpha", "SPheno_internal")
BE_VARIABLE(Alpha_mZ, Freal8, "__standardmodel_MOD_alpha_mz", "SPheno_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, "__standardmodel_MOD_alpha_mz_ms", "SPheno_internal")
BE_VARIABLE(MZ_input, Flogical, "__loopcouplings_MOD_mz_input", "SPheno_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, "__standardmodel_MOD_alphas_mz", "SPheno_internal")
BE_VARIABLE(G_F, Freal8, "__standardmodel_MOD_g_f", "SPheno_internal")
BE_VARIABLE(KFactorLee, Freal8, "__standardmodel_MOD_kfactorlee", "SPheno_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, "__standardmodel_MOD_ckm", "SPheno_internal")
BE_VARIABLE(lam_wolf, Freal8, "__standardmodel_MOD_lam_wolf", "SPheno_internal")
BE_VARIABLE(A_wolf, Freal8, "__standardmodel_MOD_a_wolf", "SPheno_internal")
BE_VARIABLE(rho_wolf, Freal8, "__standardmodel_MOD_rho_wolf", "SPheno_internal")
BE_VARIABLE(eta_wolf, Freal8, "__standardmodel_MOD_eta_wolf", "SPheno_internal")
// EWSB Variables
BE_VARIABLE(mu, Fcomplex16, "__model_data_MOD_mu", "SPheno_internal")
BE_VARIABLE(B, Fcomplex16, "__model_data_MOD_b", "SPheno_internal")
// MASS and output Variables
BE_VARIABLE(ChiPm, Farray_particle23_1_2, "__mssm_data_MOD_chipm", "SPheno_internal")
BE_VARIABLE(U, Farray_Fcomplex16_1_2_1_2, "__model_data_MOD_u", "SPheno_internal")
BE_VARIABLE(V, Farray_Fcomplex16_1_2_1_2, "__model_data_MOD_v", "SPheno_internal")
BE_VARIABLE(Chi0, Farray_particle23_1_4, "__mssm_data_MOD_chi0", "SPheno_internal")
BE_VARIABLE(N, Farray_Fcomplex16_1_4_1_4, "__model_data_MOD_n", "SPheno_internal")
BE_VARIABLE(S0, Farray_particle23_1_2, "__mssm_data_MOD_s0", "SPheno_internal")
BE_VARIABLE(RS0, Farray_Freal8_1_2_1_2, "__mssm_data_MOD_rs0", "SPheno_internal")
BE_VARIABLE(P0, Farray_particle2_1_2, "__mssm_data_MOD_p0", "SPheno_internal")
BE_VARIABLE(mP0, Farray_Freal8_1_2, "__model_data_MOD_mp0", "SPheno_internal")
BE_VARIABLE(mP02, Farray_Freal8_1_2, "__model_data_MOD_mp02", "SPheno_internal")
BE_VARIABLE(RP0, Farray_Freal8_1_2_1_2, "__model_data_MOD_rp0", "SPheno_internal")
BE_VARIABLE(Spm, Farray_particle2_1_2, "__mssm_data_MOD_spm", "SPheno_internal")
BE_VARIABLE(RSpm, Farray_Fcomplex16_1_2_1_2, "__model_data_MOD_rspm", "SPheno_internal")
BE_VARIABLE(Sdown, Farray_particle2_1_6, "__mssm_data_MOD_sdown", "SPheno_internal")
BE_VARIABLE(RSdown, Farray_Fcomplex16_1_6_1_6, "__model_data_MOD_rsdown", "SPheno_internal")
BE_VARIABLE(Sup, Farray_particle23_1_6, "__mssm_data_MOD_sup", "SPheno_internal")
BE_VARIABLE(RSup, Farray_Fcomplex16_1_6_1_6, "__model_data_MOD_rsup", "SPheno_internal")
BE_VARIABLE(Slepton, Farray_particle23_1_6, "__mssm_data_MOD_slepton", "SPheno_internal")
BE_VARIABLE(RSlepton, Farray_Fcomplex16_1_6_1_6, "__model_data_MOD_rslepton",  "SPheno_internal")
BE_VARIABLE(Sneut, Farray_particle23_1_3, "__mssm_data_MOD_sneut", "SPheno_internal")
BE_VARIABLE(RSneut, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_rsneut", "SPheno_internal")
BE_VARIABLE(Glu, particle23, "__mssm_data_MOD_glu", "SPheno_internal")
BE_VARIABLE(PhaseGlu, Fcomplex16, "__model_data_MOD_phaseglu", "SPheno_internal")
BE_VARIABLE(gauge, Farray_Freal8_1_3, "__model_data_MOD_gauge", "SPheno_internal")
BE_VARIABLE(YukScen, Flogical, "__sugraruns_MOD_yukscen", "SPheno_internal")
BE_VARIABLE(gauge_0, Farray_Freal8_1_3, "__model_data_MOD_gauge_0", "SPheno_internal")
BE_VARIABLE(uL_L, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ul_l", "SPheno_internal")
BE_VARIABLE(uL_R, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ul_r", "SPheno_internal")
BE_VARIABLE(uD_L, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ud_l", "SPheno_internal")
BE_VARIABLE(uD_R, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_ud_r", "SPheno_internal")
BE_VARIABLE(uU_L, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_uu_l", "SPheno_internal")
BE_VARIABLE(uU_R, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_uu_r", "SPheno_internal")
BE_VARIABLE(Y_l, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_l", "SPheno_internal")
BE_VARIABLE(Y_d, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_d", "SPheno_internal")
BE_VARIABLE(Y_u, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_u", "SPheno_internal")
BE_VARIABLE(Y_u_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_u_0", "SPheno_internal")
BE_VARIABLE(Y_d_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_d_0", "SPheno_internal")
BE_VARIABLE(Y_l_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_y_l_0", "SPheno_internal")
BE_VARIABLE(A_l, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_l", "SPheno_internal")
BE_VARIABLE(A_d, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_d", "SPheno_internal")
BE_VARIABLE(A_u, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_u", "SPheno_internal")
BE_VARIABLE(A_l_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_l_0", "SPheno_internal")
BE_VARIABLE(A_d_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_d_0", "SPheno_internal")
BE_VARIABLE(A_u_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_a_u_0", "SPheno_internal")
BE_VARIABLE(M2_E, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_e", "SPheno_internal")
BE_VARIABLE(M2_L, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_l", "SPheno_internal")
BE_VARIABLE(M2_D, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_d", "SPheno_internal")
BE_VARIABLE(M2_Q, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_q", "SPheno_internal")
BE_VARIABLE(M2_U, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_u", "SPheno_internal")
BE_VARIABLE(M2_E_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_e_0", "SPheno_internal")
BE_VARIABLE(M2_L_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_l_0", "SPheno_internal")
BE_VARIABLE(M2_D_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_d_0", "SPheno_internal")
BE_VARIABLE(M2_Q_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_q_0", "SPheno_internal")
BE_VARIABLE(M2_U_0, Farray_Fcomplex16_1_3_1_3, "__model_data_MOD_m2_u_0", "SPheno_internal")
BE_VARIABLE(vev_Q, Freal8, "__loopmasses_MOD_vev_q", "SPheno_internal")
BE_VARIABLE(mA2_Q, Freal8, "__loopmasses_MOD_ma2_q", "SPheno_internal")
// InitializeMSSM variables
BE_VARIABLE(GenerationMixing, Flogical, "__control_MOD_generationmixing", "SPheno_internal")
BE_VARIABLE(id_gl, Finteger, "__spheno_MOD_id_gl","SPheno_internal")
BE_VARIABLE(id_ph, Finteger, "__spheno_MOD_id_ph","SPheno_internal")
BE_VARIABLE(id_grav, Finteger, "__spheno_MOD_id_grav","SPheno_internal")
BE_VARIABLE(id_Z, Finteger, "__spheno_MOD_id_z","SPheno_internal")
BE_VARIABLE(id_W, Finteger, "__spheno_MOD_id_w","SPheno_internal")
BE_VARIABLE(id_nu, Farray_Finteger_1_3, "__spheno_MOD_id_nu","SPheno_internal")
BE_VARIABLE(id_l, Farray_Finteger_1_3, "__spheno_MOD_id_l","SPheno_internal")
BE_VARIABLE(id_d, Farray_Finteger_1_3, "__spheno_MOD_id_d","SPheno_internal")
BE_VARIABLE(id_u, Farray_Finteger_1_3, "__spheno_MOD_id_u", "SPheno_internal")
// Low energy observables variables
BE_VARIABLE(rho_parameter, Freal8, "__standardmodel_MOD_rho_parameter", "SPheno_internal") 
BE_VARIABLE(DeltaMBd, Fcomplex16, "__spheno_MOD_deltambd", "SPheno_internal")
BE_VARIABLE(DeltaMBs, Fcomplex16, "__spheno_MOD_deltambs", "SPheno_internal")
BE_VARIABLE(BRBtosgamma, Freal8, "__spheno_MOD_brbtosgamma", "SPheno_internal")
BE_VARIABLE(Bs_ll, Farray_Freal8_1_3, "__spheno_MOD_bs_ll", "SPheno_internal")
BE_VARIABLE(Bd_ll, Farray_Freal8_1_3, "__spheno_MOD_bd_ll", "SPheno_internal")
BE_VARIABLE(BrBToSLL, Freal8, "__spheno_MOD_brbtosll", "SPheno_internal")
BE_VARIABLE(BtoSNuNu, Freal8, "__spheno_MOD_btosnunu", "SPheno_internal")
BE_VARIABLE(BR_Bu_TauNu, Freal8, "__spheno_MOD_br_bu_taunu", "SPheno_internal")
BE_VARIABLE(R_Bu_TauNu, Freal8, "__spheno_MOD_r_bu_taunu", "SPheno_internal")
BE_VARIABLE(epsK, Freal8, "__spheno_MOD_epsk", "SPheno_internal")
BE_VARIABLE(DeltaMK2, Freal8, "__spheno_MOD_deltamk2", "SPheno_internal")
BE_VARIABLE(K0toPi0NuNu, Freal8, "__spheno_MOD_k0topi0nunu", "SPheno_internal")
BE_VARIABLE(KptoPipNuNu, Freal8, "__spheno_MOD_kptopipnunu", "SPheno_internal")
BE_VARIABLE(a_e, Freal8, "__spheno_MOD_a_e", "SPheno_internal")
BE_VARIABLE(a_mu, Freal8, "__spheno_MOD_a_mu", "SPheno_internal")
BE_VARIABLE(a_tau, Freal8, "__spheno_MOD_a_tau", "SPheno_internal")
BE_VARIABLE(d_e, Freal8, "__spheno_MOD_d_e", "SPheno_internal")
BE_VARIABLE(d_mu, Freal8, "__spheno_MOD_d_mu", "SPheno_internal")
BE_VARIABLE(d_tau, Freal8, "__spheno_MOD_d_tau", "SPheno_internal")
BE_VARIABLE(BrMutoEGamma, Freal8, "__spheno_MOD_brmutoegamma", "SPheno_internal")
BE_VARIABLE(BrTautoEGamma, Freal8, "__spheno_MOD_brtautoegamma", "SPheno_internal")
BE_VARIABLE(BrTautoMuGamma, Freal8, "__spheno_MOD_brtautomugamma", "SPheno_internal")
BE_VARIABLE(BrMu3e, Freal8, "__spheno_MOD_brmu3e", "SPheno_internal")
BE_VARIABLE(BrTau3e, Freal8, "__spheno_MOD_brtau3e", "SPheno_internal")
BE_VARIABLE(BrTau3Mu, Freal8, "__spheno_MOD_brtau3mu", "SPheno_internal")
BE_VARIABLE(BR_Z_e_mu, Freal8, "__spheno_MOD_br_z_e_mu", "SPheno_internal")
BE_VARIABLE(BR_Z_e_tau, Freal8, "__spheno_MOD_br_z_e_tau", "SPheno_internal")
BE_VARIABLE(BR_Z_mu_tau, Freal8, "__spheno_MOD_br_z_mu_tau", "SPheno_internal")
// Branching Ratio Variables
BE_VARIABLE(epsI, Freal8, "__spheno_MOD_epsi","SPheno_internal")
BE_VARIABLE(deltaM, Freal8, "__spheno_MOD_deltam","SPheno_internal")
BE_VARIABLE(n_nu, Finteger, "__mssm_data_MOD_n_nu", "SPheno_internal")
BE_VARIABLE(n_l, Finteger, "__mssm_data_MOD_n_l", "SPheno_internal")
BE_VARIABLE(n_d, Finteger, "__mssm_data_MOD_n_d", "SPheno_internal")
BE_VARIABLE(n_u, Finteger, "__mssm_data_MOD_n_u", "SPheno_internal")
BE_VARIABLE(n_Z, Finteger, "__mssm_data_MOD_n_z", "SPheno_internal")
BE_VARIABLE(n_W, Finteger, "__mssm_data_MOD_n_w", "SPheno_internal")
BE_VARIABLE(n_Snu, Finteger, "__mssm_data_MOD_n_snu", "SPheno_internal")
BE_VARIABLE(n_Sle, Finteger, "__mssm_data_MOD_n_sle", "SPheno_internal")
BE_VARIABLE(n_Sd, Finteger, "__mssm_data_MOD_n_sd", "SPheno_internal")
BE_VARIABLE(n_Su, Finteger, "__mssm_data_MOD_n_su", "SPheno_internal")
BE_VARIABLE(n_N, Finteger, "__mssm_data_MOD_n_n", "SPheno_internal")
BE_VARIABLE(n_C, Finteger, "__mssm_data_MOD_n_c", "SPheno_internal")
BE_VARIABLE(n_g, Finteger, "__mssm_data_MOD_n_g", "SPheno_internal")
BE_VARIABLE(n_S0, Finteger, "__mssm_data_MOD_n_s0", "SPheno_internal")
BE_VARIABLE(n_P0, Finteger, "__mssm_data_MOD_n_p0", "SPheno_internal")
BE_VARIABLE(n_Spm, Finteger, "__mssm_data_MOD_n_spm", "SPheno_internal")
// Cross section variables
BE_VARIABLE(Ecms, Farray_Freal8_1_100, "__spheno_MOD_ecms", "SPheno_internal")
BE_VARIABLE(Pm, Farray_Freal8_1_100, "__spheno_MOD_pm", "SPheno_internal")
BE_VARIABLE(Pp, Farray_Freal8_1_100, "__spheno_MOD_pp", "SPheno_internal")
BE_VARIABLE(ISR, Farray_Flogical_1_100, "__spheno_MOD_isr", "SPheno_internal")
BE_VARIABLE(Beam, Farray_Flogical_1_100, "__spheno_MOD_beam", "SPheno_internal")
BE_VARIABLE(SigSup, Farray_Freal8_1_100_1_6_1_6, "__spheno_MOD_sigsup", "SPheno_internal")
BE_VARIABLE(SigSdown, Farray_Freal8_1_100_1_6_1_6, "__spheno_MOD_sigsdown", "SPheno_internal")
BE_VARIABLE(SigSle, Farray_Freal8_1_100_1_6_1_6, "__spheno_MOD_sigsle", "SPheno_internal")
BE_VARIABLE(SigSn, Farray_Freal8_1_100_1_3_1_3, "__spheno_MOD_sigsn", "SPheno_internal")
BE_VARIABLE(SigC, Farray_Freal8_1_100_1_5_1_5, "__spheno_MOD_sigc", "SPheno_internal")
BE_VARIABLE(SigChi0, Farray_Freal8_1_100_1_7_1_7, "__spheno_MOD_sigchi0", "SPheno_internal")
BE_VARIABLE(SigS0, Farray_Freal8_1_100_1_5, "__spheno_MOD_sigs0", "SPheno_internal")
BE_VARIABLE(SigSP, Farray_Freal8_1_100_1_5_1_4, "__spheno_MOD_sigsp", "SPheno_internal")
BE_VARIABLE(SigHp, Farray_Freal8_1_100_1_7_1_7, "__spheno_MOD_sighp", "SPheno_internal")
// Control Variables
BE_VARIABLE(kont, Finteger, "__spheno_MOD_kont", "SPheno_internal")
BE_VARIABLE(ErrCan, Finteger, "__control_MOD_errcan", "SPheno_internal")
// Other variabls
BE_VARIABLE(vevSM, Farray_Freal8_1_2, "__model_data_MOD_vevsm", "SPheno_internal")
BE_VARIABLE(m_GUT, Freal8, "__spheno_MOD_m_gut", "SPheno_internal")
BE_VARIABLE(Ylp, Farray_Fcomplex16_1_3_1_3, "__spheno_MOD_ylp", "SPheno_internal")
BE_VARIABLE(ratioWoM, Freal8, "__spheno_MOD_ratiowom","SPheno_internal")
BE_VARIABLE(CalcTBD,Flogical, "__spheno_MOD_calctbd","SPheno_internal")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SPheno_MSSMspectrum")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const std::map<str, safe_ptr<const double> >&), "SPheno_internal")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SPheno_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SPheno_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SPheno_internal")

// Initialisation functions (dependencies)


// End
#include "gambit/Backends/backend_undefs.hpp"
