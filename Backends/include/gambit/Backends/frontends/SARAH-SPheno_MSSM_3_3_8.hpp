//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Backend macros for SPheno (SARAH version) for the MSSM
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Dec
///
///  *********************************************

#define BACKENDNAME SARAH-SPheno_MSSM
#define BACKENDLANG FORTRAN
#define VERSION 3.3.8
#define SARAH_VERSION 4.8.1
#define SAFE_VERSION 3_3_8

// Begin
LOAD_LIBRARY

// Allow for CMSSM, MSSM63atMGUT and MSSM63atQ
BE_ALLOW_MODELS(CMSSM)

// Functions
BE_FUNCTION(Set_All_Parameters_0, void, (), "__model_data_mssm_MOD_set_all_parameters_0", "SPhenoMSSM_internal")
BE_FUNCTION(SetRenormalizationScale, Freal8, (Freal8&), "__loopfunctions_MOD_setrenormalizationscale", "SPhenoMSSM_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), "__loopfunctions_MOD_initializeloopfunctions", "SPhenoMSSM_internal")
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
	 "__standardmodel_MOD_calculaterunningmasses", "SPhenoMSSM_internal")
BE_FUNCTION(CalculateSpectrum, void,
	(Finteger&, // n_run
	 Freal8&, // delta
	 Flogical&, // WriteOut
	 Finteger&, // kont
         Farray_Freal8_1_2&, // MAh
         Farray_Freal8_1_2&, // MAh2
         Farray_Freal8_1_2&, // MCha
         Farray_Freal8_1_2&, // MCha2
         Farray_Freal8_1_4&, // MChi
         Farray_Freal8_1_4&, // MChi2
         Farray_Freal8_1_3&, // MFd
         Farray_Freal8_1_3&, // MFd2
         Farray_Freal8_1_3&, // MFe
         Farray_Freal8_1_3&, // MFe2
         Farray_Freal8_1_3&, // MFu
         Farray_Freal8_1_3&, // MFu2
         Freal8&, // MGlu
         Freal8&, // MGlu2
         Farray_Freal8_1_2&, // Mhh
         Farray_Freal8_1_2&, // Mhh2
         Farray_Freal8_1_2&, // MHpm
         Farray_Freal8_1_2&, // MHpm2
         Farray_Freal8_1_6&, // MSd
         Farray_Freal8_1_6&, // MSd2
         Farray_Freal8_1_6&, // MSe
         Farray_Freal8_1_6&, // MSe2
         Farray_Freal8_1_6&, // MSu
         Farray_Freal8_1_6&, // MSu2
         Farray_Freal8_1_3&, // MSv
         Farray_Freal8_1_3&, // MSv2
         Freal8&, // MVWm
         Freal8&, // MVWm2
         Freal8&, // MVZ
         Freal8&, // MVZ2
         Fcomplex16&, // pG
         Freal8&, // TW
         Farray_Fcomplex16_1_2_1_2&, // UM
         Farray_Fcomplex16_1_2_1_2&, // UP
         Freal8&, // v
         Farray_Freal8_1_2_1_2&, // ZA
         Farray_Fcomplex16_1_6_1_6&, // ZD
         Farray_Fcomplex16_1_3_1_3&, // ZDL
         Farray_Fcomplex16_1_3_1_3&, // ZDR
         Farray_Fcomplex16_1_6_1_6&, // ZE
         Farray_Fcomplex16_1_3_1_3&, // ZEL
         Farray_Fcomplex16_1_3_1_3&, // ZER
         Farray_Freal8_1_2_1_2&, // ZH
         Farray_Fcomplex16_1_4_1_4&, // ZN
         Farray_Freal8_1_2_1_2&, // ZP
         Farray_Fcomplex16_1_6_1_6&, // ZU
         Farray_Fcomplex16_1_3_1_3&, // ZUL
         Farray_Fcomplex16_1_3_1_3&, // ZUR
         Farray_Fcomplex16_1_3_1_3&, // ZV
         Farray_Fcomplex16_1_2_1_2&, // ZW
         Farray_Freal8_1_2_1_2&, // ZZ
         Freal8&, // alphaH
         Freal8&, // betaH
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Fcomplex16&, // Mu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Fcomplex16&, // Bmu
         Farray_Fcomplex16_1_3_1_3& , // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, //M3
         Freal8& //  m_GUT
	), "__sphenomssm_MOD_calculatespectrum", "SPhenoMSSM_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), "__loopfunctions_MOD_getrenormalizationscale", "SPhenoMSSM_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), "__model_data_mssm_MOD_setrgescale", "SPhenoMSSM_internal")
/*BE_FUNCTION(SetHighScaleModel, Flogical, (Fstring<20>), "__sugraruns_MOD_sethighscalemodel", "SPhenoMSSM_internal")
BE_FUNCTION(SetWriteMinBr, void, (Freal8&), "__inputoutput_MOD_setwriteminbr", "SPhenoMSSM_internal")
BE_FUNCTION(SetWriteMinSig, void, (Freal8&), "__inputoutput_MOD_setwriteminsig", "SPhenoMSSM_internal")*/
BE_FUNCTION(SetGUTScale, void, (Freal8&), "__model_data_mssm__MOD_setgutscale", "SPhenoMSSM_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), "__model_data_mssm_MOD_setstrictunification", "SPhenoMSSM_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), "__model_data_mssm_MOD_setyukawascheme", "SPhenoMSSM_internal")
/*BE_FUNCTION(Set_Use_bsstep_instead_of_rkqs, Flogical, (Flogical&), "__mathematics_MOD_set_use_bsstep_instead_of_rkqs", "SPhenoMSSM_internal")
BE_FUNCTION(Set_Use_rzextr_instead_of_pzextr, Flogical, (Flogical&), "__mathematics_MOD_set_use_rzextr_instead_of_pzextr", "SPhenoMSSM_internal")*/
BE_FUNCTION(Alpha_MSbar, Freal8, (Freal8&, Freal8&), "__loopcouplings_mssm_MOD_alpha_msbar", "SPhenoMSSM_internal")
/*BE_FUNCTION(Low_Energy_Constraints_MSSM, void,
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
       ), "__lowenergy_MOD_low_energy_constraints_mssm", "SPhenoMSSM_internal")

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
        ), "__branchingratios_MOD_calculatebr_mssm", "SPhenoMSSM_internal")
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
       ), "__epluseminusproduction_MOD_calculatecrosssectionsmssm", "SPhenoMSSM_internal")
*/
// Variables
// MODSEL Variables
BE_VARIABLE(HighScaleModel, Fstring<15>, "__model_data_mssm_MOD_highscalemodel", "SPhenoMSSM_internal")
BE_VARIABLE(BoundaryCondition, Finteger, "__model_data_mssm_MOD_boundarycondition", "SPhenoMSSM_internal")
// SPHENOINPUT Variables
BE_VARIABLE(ErrorLevel, Finteger, "__control_MOD_errorlevel", "SPhenoMSSM_internal")
BE_VARIABLE(SPA_convention, Flogical, "__model_data_mssm_MOD_spa_convention", "SPhenoMSSM_internal")
BE_VARIABLE(External_Spectrum, Flogical, "__control_MOD_external_spectrum", "SPhenoMSSM_internal")
BE_VARIABLE(External_Higgs, Flogical, "__control_MOD_external_higgs", "SPhenoMSSM_internal")
BE_VARIABLE(Use_Flavour_States, Flogical, "__inputoutput_MOD_use_flavour_states", "SPhenoMSSM_internal")
BE_VARIABLE(FermionMassResummation, Flogical, "__control_MOD_fermionmassresummation", "SPhenoMSSM_internal")
BE_VARIABLE(RXiNew, Freal8, "__model_data_mssm_MOD_rxinew", "SPhenoMSSM_internal")
BE_VARIABLE(CalculateTwoLoopHiggsMasses, Flogical, "__model_data_mssm_MOD_calculatetwoloophiggsmasses", "SPhenoMSSM_internal")
BE_VARIABLE(PurelyNumericalEffPot, Flogical, "__model_data_mssm_MOD_purelynumericaleffpot", "SPhenoMSSM_internal")
BE_VARIABLE(CalculateMSSM2Loop, Flogical, "__model_data_mssm_MOD_calculatemssm2loop", "SPhenoMSSM_internal")
BE_VARIABLE(TwoLoopMethod, Finteger, "__model_data_mssm_MOD_twoloopmethod", "SPhenoMSSM_internal")
BE_VARIABLE(GaugelessLimit, Flogical, "__model_data_mssm_MOD_gaugelesslimit", "SPhenoMSSM_internal")
BE_VARIABLE(TwoLoopSafeMode, Flogical, "__model_data_mssm_MOD_twoloopsafemode", "SPhenoMSSM_internal")
BE_VARIABLE(L_BR, Flogical, "__control_MOD_l_br", "SPhenoMSSM_internal")
BE_VARIABLE(L_CS, Flogical, "__control_MOD_l_cs", "SPhenoMSSM_internal")
BE_VARIABLE(delta_mass, Freal8, "__control_MOD_delta_mass", "SPhenoMSSM_internal")
BE_VARIABLE(n_run, Finteger, "__control_MOD_n_run", "SPhenoMSSM_internal")
BE_VARIABLE(MinimalNumberIterations, Finteger, "__model_data_mssm_MOD_minimalnumberiterations", "SPhenoMSSM_internal")
BE_VARIABLE(WriteOut, Flogical, "__control_MOD_writeout", "SPhenoMSSM_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, "__model_data_mssm_MOD_twolooprge", "SPhenoMSSM_internal")
BE_VARIABLE(WriteSLHA1, Flogical, "__model_data_mssm_MOD_writeslha1", "SPhenoMSSM_internal")
BE_VARIABLE(RotateNegativeFermionMasses, Flogical, "__model_data_mssm_MOD_rotatenegativefermionmasses", "SPhenoMSSM_internal")
BE_VARIABLE(SwitchToSCKM, Flogical, "__model_data_mssm_MOD_switchtosckm", "SPhenoMSSM_internal")
BE_VARIABLE(IgnoreNegativeMasses, Flogical, "__model_data_mssm_MOD_ignorenegativemasses", "SPhenoMSSM_internal")
BE_VARIABLE(IgnoreNegativeMassesMZ, Flogical, "__model_data_mssm_MOD_ignorenegativemassesmz", "SPhenoMSSM_internal")
BE_VARIABLE(WriteOutputForNonConvergence, Flogical, "__model_data_mssm_MOD_writeoutputfornonconvergence", "SPhenoMSSM_internal")
BE_VARIABLE(CalculateOneLoopMasses, Flogical, "__model_data_mssm_MOD_calculateoneloopmasses", "SPhenoMSSM_internal")
BE_VARIABLE(CalculateLowEnergy, Flogical, "__model_data_mssm_MOD_calculatelowenergy", "SPhenoMSSM_internal")
BE_VARIABLE(IncludeDeltaVB, Flogical, "__model_data_mssm_MOD_includedeltavb", "SPhenoMSSM_internal")
BE_VARIABLE(IncludeBSMdeltaVB, Flogical, "__model_data_mssm_MOD_includebsmdeltavb", "SPhenoMSSM_internal")
BE_VARIABLE(KineticMixing, Flogical, "__model_data_mssm_MOD_kineticmixing", "SPhenoMSSM_internal")
BE_VARIABLE(SMrunningLowScaleInput, Flogical, "__model_data_mssm_MOD_smrunninglowscaleinput", "SPhenoMSSM_internal")
BE_VARIABLE(RunningSUSYparametersLowEnergy, Flogical, "__model_data_mssm_MOD_runningsusyparameterslowenergy", "SPhenoMSSM_internal")
BE_VARIABLE(RunningSMparametersLowEnergy, Flogical, "__model_data_mssm_MOD_runningsmparameterslowenergy", "SPhenoMSSM_internal")
BE_VARIABLE(WriteParametersAtQ, Flogical, "__model_data_mssm_MOD_writeparametersatq", "SPhenoMSSM_internal")
BE_VARIABLE(SolutionTadpoleNr, Finteger, "__model_data_mssm_MOD_solutiontadpolenr", "SPhenoMSSM_internal")
BE_VARIABLE(SUSYrunningFromMZ, Flogical, "__model_data_mssm_MOD_susyrunningfrommz", "SPhenoMSSM_internal")
BE_VARIABLE(Write_WHIZARD, Flogical, "__model_data_mssm_MOD_write_whizard", "SPhenoMSSM_internal")
BE_VARIABLE(Write_HiggsBounds, Flogical, "__inputoutput_mssm_MOD_write_higgsbounds", "SPhenoMSSM_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, "__control_MOD_non_zero_exit", "SPhenoMSSM_internal")
BE_VARIABLE(WidthToBeInvisible, Freal8, "__model_data_mssm_MOD_widthtobeinvisible", "SPhenoMSSM_internal")
BE_VARIABLE(MaxMassLoop, Freal8, "__model_data_mssm_MOD_maxmassloop", "SPhenoMSSM_internal")
BE_VARIABLE(MaxMassNumericalZero, Freal8, "__model_data_mssm_MOD_maxmassnumericalzero", "SPhenoMSSM_internal")
BE_VARIABLE(ForceRealMatrices, Flogical, "__model_data_mssm_MOD_forcerealmatrices", "SPhenoMSSM_internal")
BE_VARIABLE(WriteTreeLevelTadpoleSolutions, Flogical, "__model_data_mssm_MOD_writetreeleveltadpolesolutions", "SPhenoMSSM_internal")
BE_VARIABLE(WriteGUTvalues, Flogical, "__model_data_mssm_MOD_writegutvalues", "SPhenoMSSM_internal")
BE_VARIABLE(WriteEffHiggsCouplingRatios, Flogical, "__model_data_mssm_MOD_writeeffhiggscouplingratios", "SPhenoMSSM_internal")
BE_VARIABLE(HigherOrderDiboson, Flogical, "__model_data_mssm_MOD_higherorderdiboson", "SPhenoMSSM_internal")
BE_VARIABLE(WriteHiggsDiphotonLoopContributions, Flogical, "__model_data_mssm_MOD_writehiggsdiphotonloopcontributions", "SPhenoMSSM_internal")
BE_VARIABLE(WriteTreeLevelTadpoleParameters, Flogical, "__model_data_mssm_MOD_writetreeleveltadpoleparameters", "SPhenoMSSM_internal")
BE_VARIABLE(CalcFT, Flogical, "__model_data_mssm_MOD_calcft", "SPhenoMSSM_internal")
BE_VARIABLE(OneLoopFT, Flogical, "__model_data_mssm_MOD_oneloopft" , "SPhenoMSSM_internal")
BE_VARIABLE(MakeQTEST, Flogical, "__model_data_mssm_MOD_makeqtest", "SPhenoMSSM_internal")
BE_VARIABLE(PrintDebugInformation, Flogical, "__model_data_mssm_MOD_printdebuginformation", "SPhenoMSSM_internal")
// MINPAR Variables
BE_VARIABLE(m0, Freal8, "__model_data_mssm_MOD_m0", "SPhenoMSSM_internal")
BE_VARIABLE(m12, Fcomplex16, "__model_data_mssm_MOD_m12", "SPhenoMSSM_internal")
BE_VARIABLE(TanBeta, Freal8, "__model_data_mssm_MOD_tanbeta", "SPhenoMSSM_internal")
BE_VARIABLE(SignumMu, Fcomplex16, "__model_data_mssm_MOD_signummu", "SPhenoMSSM_internal")
BE_VARIABLE(Azero, Fcomplex16, "__model_data_mssm_MOD_azero", "SPhenoMSSM_internal")
// EXTPAR Variables
BE_VARIABLE(M1input, Fcomplex16, "__model_data_mssm_MOD_m1input", "SPhenoMSSM_internal")
BE_VARIABLE(M2input, Fcomplex16, "__model_data_mssm_MOD_m2input", "SPhenoMSSM_internal")
BE_VARIABLE(M3input, Fcomplex16, "__model_data_mssm_MOD_m3input", "SPhenoMSSM_internal")
// TDIN, TUIN, TEIN
BE_VARIABLE(InputValueforTd, Flogical, "__model_data_mssm_MOD_inputvaluefortd", "SPhenoMSSM_internal")
BE_VARIABLE(TdIN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_tdin", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueforTu, Flogical, "__model_data_mssm_MOD_inputvaluefortu", "SPhenoMSSM_internal")
BE_VARIABLE(TuIN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_tuin", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueforTe, Flogical, "__model_data_mssm_MOD_inputvalueforte", "SPhenoMSSM_internal")
BE_VARIABLE(TeIN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_tein", "SPhenoMSSM_internal")
// MSL2, MSE2 ,MSQ2, MSU2, MSD2
BE_VARIABLE(InputValueforml2, Flogical, "__model_data_mssm_MOD_inputvalueforml2", "SPhenoMSSM_internal")
BE_VARIABLE(ml2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_ml2in", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueforme2, Flogical, "__model_data_mssm_MOD_inputvalueforme2", "SPhenoMSSM_internal")
BE_VARIABLE(me2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_me2in", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueformq2, Flogical, "__model_data_mssm_MOD_inputvalueformq2", "SPhenoMSSM_internal")
BE_VARIABLE(mq2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_mq2in", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueformu2, Flogical, "__model_data_mssm_MOD_inputvalueformu2", "SPhenoMSSM_internal")
BE_VARIABLE(mu2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_mu2in", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueformd2, Flogical, "__model_data_mssm_MOD_inputvalueformd2", "SPhenoMSSM_internal")
BE_VARIABLE(md2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_md2in", "SPhenoMSSM_internal")
// MSOFTIN Variables
BE_VARIABLE(InputValueformHd2, Flogical, "__model_data_mssm_MOD_inputvalueformhd2", "SPhenoMSSM_internal")
BE_VARIABLE(mHd2IN, Freal8, "__model_data_mssm_MOD_mhd2in", "SPhenoMSSM_internal")
BE_VARIABLE(InputValueformHu2, Flogical, "__model_data_mssm_MOD_inputvalueformhu2", "SPhenoMSSM_internal")
BE_VARIABLE(mHu2IN, Freal8, "__model_data_mssm_MOD_mhu2in", "SPhenoMSSM_internal")
// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, "__standardmodel_MOD_mz", "SPhenoMSSM_internal")
BE_VARIABLE(mZ2, Freal8,  "__standardmodel_MOD_mz2", "SPhenoMSSM_internal")
BE_VARIABLE(gamZ, Freal8, "__standardmodel_MOD_gamz", "SPhenoMSSM_internal")
BE_VARIABLE(gamZ2, Freal8, "__standardmodel_MOD_gamz2", "SPhenoMSSM_internal")
BE_VARIABLE(gmZ, Freal8, "__standardmodel_MOD_gmz", "SPhenoMSSM_internal")
BE_VARIABLE(gmZ2, Freal8, "__standardmodel_MOD_gmz2", "SPhenoMSSM_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, "__standardmodel_MOD_brzqq", "SPhenoMSSM_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, "__standardmodel_MOD_brzll", "SPhenoMSSM_internal")
BE_VARIABLE(BrZinv, Freal8, "__standardmodel_MOD_brzinv", "SPhenoMSSM_internal")
BE_VARIABLE(mW, Freal8, "__standardmodel_MOD_mw", "SPhenoMSSM_internal")
BE_VARIABLE(mW_SM, Freal8, "__model_data_mssm_MOD_mw_sm", "SPhenoMSSM_internal")
BE_VARIABLE(mW2, Freal8, "__standardmodel_MOD_mw2", "SPhenoMSSM_internal")
BE_VARIABLE(gamW, Freal8, "__standardmodel_MOD_gamw", "SPhenoMSSM_internal")
BE_VARIABLE(gamW2, Freal8, "__standardmodel_MOD_gamw2", "SPhenoMSSM_internal")
BE_VARIABLE(gmW, Freal8, "__standardmodel_MOD_gmw", "SPhenoMSSM_internal")
BE_VARIABLE(gmW2, Freal8, "__standardmodel_MOD_gmw2", "SPhenoMSSM_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, "__standardmodel_MOD_brwqq", "SPhenoMSSM_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, "__standardmodel_MOD_brwln", "SPhenoMSSM_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l", "SPhenoMSSM_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l_mz", "SPhenoMSSM_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, "__standardmodel_MOD_mf_nu", "SPhenoMSSM_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u", "SPhenoMSSM_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u_mz", "SPhenoMSSM_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d", "SPhenoMSSM_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d_mz", "SPhenoMSSM_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l2", "SPhenoMSSM_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u2", "SPhenoMSSM_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d2", "SPhenoMSSM_internal")
BE_VARIABLE(MNuR, Freal8, "__model_data_MOD_mnur", "SPhenoMSSM_internal")
BE_VARIABLE(Q_light_quarks, Freal8, "__standardmodel_MOD_q_light_quarks", "SPhenoMSSM_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, "__standardmodel_MOD_delta_alpha_lepton", "SPhenoMSSM_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, "__standardmodel_MOD_delta_alpha_hadron", "SPhenoMSSM_internal")
BE_VARIABLE(Alpha, Freal8, "__standardmodel_MOD_alpha", "SPhenoMSSM_internal")
BE_VARIABLE(Alpha_mZ, Freal8, "__standardmodel_MOD_alpha_mz", "SPhenoMSSM_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, "__standardmodel_MOD_alpha_mz_ms", "SPhenoMSSM_internal")
BE_VARIABLE(MZ_input, Flogical, "__model_data_mssm_MOD_mz_input", "SPhenoMSSM_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, "__standardmodel_MOD_alphas_mz", "SPhenoMSSM_internal")
BE_VARIABLE(G_F, Freal8, "__standardmodel_MOD_g_f", "SPhenoMSSM_internal")
BE_VARIABLE(KFactorLee, Freal8, "__standardmodel_MOD_kfactorlee", "SPhenoMSSM_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, "__standardmodel_MOD_ckm", "SPhenoMSSM_internal")
BE_VARIABLE(lam_wolf, Freal8, "__standardmodel_MOD_lam_wolf", "SPhenoMSSM_internal")
BE_VARIABLE(A_wolf, Freal8, "__standardmodel_MOD_a_wolf", "SPhenoMSSM_internal")
BE_VARIABLE(rho_wolf, Freal8, "__standardmodel_MOD_rho_wolf", "SPhenoMSSM_internal")
BE_VARIABLE(eta_wolf, Freal8, "__standardmodel_MOD_eta_wolf", "SPhenoMSSM_internal")
// MASS and output Variables
BE_VARIABLE(MAh, Farray_Freal8_1_2, "__model_data_mssm_MOD_mah", "SPhenoMSSM_internal")
BE_VARIABLE(MAh2, Farray_Freal8_1_2, "__model_data_mssm_MOD_mah2", "SPhenoMSSM_internal")
BE_VARIABLE(MCha, Farray_Freal8_1_2, "__model_data_mssm_MOD_mcha", "SPhenoMSSM_internal")
BE_VARIABLE(MCha2, Farray_Freal8_1_2, "__model_data_mssm_MOD_mcha2", "SPhenoMSSM_internal")
BE_VARIABLE(MChi, Farray_Freal8_1_4, "__model_data_mssm_MOD_mchi", "SPhenoMSSM_internal")
BE_VARIABLE(MChi2, Farray_Freal8_1_4, "__model_data_mssm_MOD_mchi2", "SPhenoMSSM_internal")
BE_VARIABLE(MFd, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfd", "SPhenoMSSM_internal")
BE_VARIABLE(MFd2, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfd2", "SPhenoMSSM_internal")
BE_VARIABLE(MFe, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfe", "SPhenoMSSM_internal")
BE_VARIABLE(MFe2, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfe2", "SPhenoMSSM_internal")
BE_VARIABLE(MFu, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfu", "SPhenoMSSM_internal")
BE_VARIABLE(MFu2, Farray_Freal8_1_3, "__model_data_mssm_MOD_mfu2", "SPhenoMSSM_internal")
BE_VARIABLE(MGlu, Freal8, "__model_data_mssm_MOD_mglu", "SPhenoMSSM_internal")
BE_VARIABLE(MGlu2, Freal8, "__model_data_mssm_MOD_mglu2", "SPhenoMSSM_internal")
BE_VARIABLE(Mhh, Farray_Freal8_1_2, "__model_data_mssm_MOD_mhh", "SPhenoMSSM_internal")
BE_VARIABLE(Mhh2, Farray_Freal8_1_2, "__model_data_mssm_MOD_mhh2", "SPhenoMSSM_internal")
BE_VARIABLE(MHpm, Farray_Freal8_1_2, "__model_data_mssm_MOD_mhpm", "SPhenoMSSM_internal")
BE_VARIABLE(MHpm2, Farray_Freal8_1_2, "__model_data_mssm_MOD_mhpm2", "SPhenoMSSM_internal")
BE_VARIABLE(MSd, Farray_Freal8_1_6, "__model_data_mssm_MOD_msd", "SPhenoMSSM_internal")
BE_VARIABLE(MSd2, Farray_Freal8_1_6, "__model_data_mssm_MOD_msd2", "SPhenoMSSM_internal")
BE_VARIABLE(MSe, Farray_Freal8_1_6, "__model_data_mssm_MOD_mse", "SPhenoMSSM_internal")
BE_VARIABLE(MSe2, Farray_Freal8_1_6, "__model_data_mssm_MOD_mse2", "SPhenoMSSM_internal")
BE_VARIABLE(MSu, Farray_Freal8_1_6, "__model_data_mssm_MOD_msu", "SPhenoMSSM_internal")
BE_VARIABLE(MSu2, Farray_Freal8_1_6, "__model_data_mssm_MOD_msu2", "SPhenoMSSM_internal")
BE_VARIABLE(MSv, Farray_Freal8_1_3, "__model_data_mssm_MOD_msv", "SPhenoMSSM_internal")
BE_VARIABLE(MSv2, Farray_Freal8_1_3, "__model_data_mssm_MOD_msv2", "SPhenoMSSM_internal")
BE_VARIABLE(MVWm, Freal8, "__model_data_mssm_MOD_mvwm", "SPhenoMSSM_internal")
BE_VARIABLE(MVWm2, Freal8, "__model_data_mssm_MOD_mvwm2", "SPhenoMSSM_internal")
BE_VARIABLE(MVZ, Freal8, "__model_data_mssm_MOD_mvz", "SPhenoMSSM_internal")
BE_VARIABLE(MVZ2, Freal8, "__model_data_mssm_MOD_mvz2", "SPhenoMSSM_internal")
BE_VARIABLE(pG, Fcomplex16, "__model_data_mssm_MOD_pg", "SPhenoMSSM_internal")
BE_VARIABLE(TW, Freal8, "__model_data_mssm_MOD_tw", "SPhenoMSSM_internal")
BE_VARIABLE(UM, Farray_Fcomplex16_1_2_1_2, "__model_data_mssm_MOD_um", "SPhenoMSSM_internal")
BE_VARIABLE(UP, Farray_Fcomplex16_1_2_1_2, "__model_data_mssm_MOD_up" ,"SPhenoMSSM_internal")
BE_VARIABLE(v, Freal8, "__model_data_mssm_MOD_v", "SPhenoMSSM_internal")
BE_VARIABLE(ZA, Farray_Freal8_1_2_1_2, "__model_data_mssm_MOD_za", "SPhenoMSSM_internal")
BE_VARIABLE(ZD, Farray_Fcomplex16_1_6_1_6, "__model_data_mssm_MOD_zd" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZDL, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zdl", "SPhenoMSSM_internal")
BE_VARIABLE(ZDR, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zdr", "SPhenoMSSM_internal")
BE_VARIABLE(ZE, Farray_Fcomplex16_1_6_1_6, "__model_data_mssm_MOD_ze", "SPhenoMSSM_internal")
BE_VARIABLE(ZEL, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zel" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZER, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zer", "SPhenoMSSM_internal")
BE_VARIABLE(ZH, Farray_Freal8_1_2_1_2, "__model_data_mssm_MOD_zh", "SPhenoMSSM_internal")
BE_VARIABLE(ZN, Farray_Fcomplex16_1_4_1_4, "__model_data_mssm_MOD_zn" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZP, Farray_Freal8_1_2_1_2, "__model_data_mssm_MOD_zp" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZU, Farray_Fcomplex16_1_6_1_6, "__model_data_mssm_MOD_zu" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZUL, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zul", "SPhenoMSSM_internal")
BE_VARIABLE(ZUR, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zur" ,"SPhenoMSSM_internal")
BE_VARIABLE(ZV, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_zv", "SPhenoMSSM_internal")
BE_VARIABLE(ZW, Farray_Fcomplex16_1_2_1_2, "__model_data_mssm_MOD_zw", "SPhenoMSSM_internal")
BE_VARIABLE(ZZ, Farray_Freal8_1_2_1_2, "__model_data_mssm_MOD_zz", "SPhenoMSSM_internal")
BE_VARIABLE(alphaH, Freal8, "__model_data_mssm_MOD_alphah", "SPhenoMSSM_internal")
BE_VARIABLE(betaH, Freal8, "__model_data_mssm_MOD_betah", "SPhenoMSSM_internal")
BE_VARIABLE(vd, Freal8, "__model_data_mssm_MOD_vd", "SPhenoMSSM_internal")
BE_VARIABLE(vu, Freal8, "__model_data_mssm_MOD_vu", "SPhenoMSSM_internal")
BE_VARIABLE(g1, Freal8, "__model_data_mssm_MOD_g1", "SPhenoMSSM_internal")
BE_VARIABLE(g2, Freal8, "__model_data_mssm_MOD_g2", "SPhenoMSSM_internal")
BE_VARIABLE(g3, Freal8, "__model_data_mssm_MOD_g3", "SPhenoMSSM_internal")
BE_VARIABLE(g1GUT, Freal8, "__model_data_mssm_MOD_g1gut", "SPhenoMSSM_internal")
BE_VARIABLE(g2GUT, Freal8, "__model_data_mssm_MOD_g2gut", "SPhenoMSSM_internal")
BE_VARIABLE(g3GUT, Freal8, "__model_data_mssm_MOD_g3gut", "SPhenoMSSM_internal")
BE_VARIABLE(Yd, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_yd", "SPhenoMSSM_internal")
BE_VARIABLE(Ye, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_ye", "SPhenoMSSM_internal")
BE_VARIABLE(Yu, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_yu", "SPhenoMSSM_internal")
BE_VARIABLE(Mu, Fcomplex16, "__model_data_mssm_MOD_mu", "SPhenoMSSM_internal")
BE_VARIABLE(Td, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_td", "SPhenoMSSM_internal")
BE_VARIABLE(Te, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_te", "SPhenoMSSM_internal")
BE_VARIABLE(Tu, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_tu", "SPhenoMSSM_internal")
BE_VARIABLE(Bmu, Fcomplex16, "__model_data_mssm_MOD_bmu", "SPhenoMSSM_internal")
BE_VARIABLE(mq2, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_mq2", "SPhenoMSSM_internal")
BE_VARIABLE(ml2, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_ml2", "SPhenoMSSM_internal")
BE_VARIABLE(mHd2, Freal8, "__model_data_mssm_MOD_mhd2", "SPhenoMSSM_internal")
BE_VARIABLE(mHu2, Freal8, "__model_data_mssm_MOD_mhu2", "SPhenoMSSM_internal")
BE_VARIABLE(md2, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_md2", "SPhenoMSSM_internal")
BE_VARIABLE(mu2, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_mu2", "SPhenoMSSM_internal")
BE_VARIABLE(me2, Farray_Fcomplex16_1_3_1_3, "__model_data_mssm_MOD_me2", "SPhenoMSSM_internal")
BE_VARIABLE(M1, Fcomplex16, "__model_data_mssm_MOD_m1", "SPhenoMSSM_internal")
BE_VARIABLE(M2, Fcomplex16, "__model_data_mssm_MOD_m2", "SPhenoMSSM_internal")
BE_VARIABLE(M3, Fcomplex16, "__model_data_mssm_MOD_m3", "SPhenoMSSM_internal")
// Control Variables
BE_VARIABLE(kont, Finteger, "__sphenomssm_MOD_kont", "SPhenoMSSM_internal")
BE_VARIABLE(mGUT, Freal8, "__sphenomssm_MOD_mgut", "SPhenoMSSM_internal")
BE_VARIABLE(ErrCan, Finteger, "__control_MOD_errcan", "SPhenoMSSM_internal")
BE_VARIABLE(GenerationMixing, Flogical, "__control_MOD_generationmixing", "SPhenoMSSM_internal")
BE_VARIABLE(FoundIterativeSolution, Flogical, "__model_data_mssm_MOD_founditerativesolution", "SPhenoMSSM_internal")
// Other variables
BE_VARIABLE(Qin, Freal8, "__sphenomssm_MOD_qin", "SPhenoMSSM_internal")
BE_VARIABLE(ratioWoM, Freal8, "__sphenomssm_MOD_ratiowom","SPhenoMSSM_internal")
BE_VARIABLE(CalcTBD, Flogical, "__sphenomssm_MOD_calctbd","SPhenoMSSM_internal")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SPhenoMSSM_MSSMspectrum")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const std::map<str, safe_ptr<double> >&), "SPhenoMSSM_internal")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SPhenoMSSM_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SPhenoMSSM_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SPhenoMSSM_internal")

// Initialisation functions (dependencies)


// End
#include "gambit/Backends/backend_undefs.hpp"
