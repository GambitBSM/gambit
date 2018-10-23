//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Backend macros for SPheno (SARAH version) for the NMSSM
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2018 Sep
///
///  *********************************************

#define BACKENDNAME SARAHSPheno_NMSSM
#define BACKENDLANG FORTRAN
#define VERSION 4.0.3
#define SARAH_VERSION 4.13.0
#define SAFE_VERSION 4_0_3

// Begin
LOAD_LIBRARY

// Allow for NMSSM only
BE_ALLOW_MODELS(NMSSM66atQ)

// Functions
BE_FUNCTION(Set_All_Parameters_0, void, (), "__model_data_nmssm_MOD_set_all_parameters_0", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetRenormalizationScale, Freal8, (Freal8&), "__loopfunctions_MOD_setrenormalizationscale", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), "__loopfunctions_MOD_initializeloopfunctions", "SARAHSPheno_NMSSM_internal")
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
	 "__standardmodel_MOD_calculaterunningmasses", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetMatchingConditions, void,
        (Freal8&, // g1SM
         Freal8&, // g2SM
         Freal8&, // g3SM
         Farray_Fcomplex16_1_3_1_3&, // YuSM
         Farray_Fcomplex16_1_3_1_3&, // YdSM
         Farray_Fcomplex16_1_3_1_3&, // YeSM
         Freal8&, // vSM
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // vS
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3&, // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, // M3
         Flogical& // MZsuffix
        ), "__model_data_nmssm_MOD_setmatchingconditions", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(Switch_from_superCKM, void,
        (Farray_Fcomplex16_1_3_1_3&, // Yd_ckm
         Farray_Fcomplex16_1_3_1_3&, // Yu_ckm
         Farray_Fcomplex16_1_3_1_3&, // Td_ckm
         Farray_Fcomplex16_1_3_1_3&, // Tu_ckm
         Farray_Fcomplex16_1_3_1_3&, // md2_ckm
         Farray_Fcomplex16_1_3_1_3&, // mq2_ckm
         Farray_Fcomplex16_1_3_1_3&, // mu2_ckm
         Farray_Fcomplex16_1_3_1_3&, // Td_out
         Farray_Fcomplex16_1_3_1_3&, // Tu_out
         Farray_Fcomplex16_1_3_1_3&, // md2_out
         Farray_Fcomplex16_1_3_1_3&, // mq2_out
         Farray_Fcomplex16_1_3_1_3&, // mu2_out
         Flogical& // Tranposed
        ), "__sphenonmssm_MOD_switch_from_superckm", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SolveTadpoleEquations, void,
        (Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3&, // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, // M3
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, //vS
         Farray_Fcomplex16_1_3& // Tad1Loop
        ), "__tadpoles_nmssm_MOD_solvetadpoleequations", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(OneLoopMasses, void,
        (Farray_Freal8_1_3&, // MAh
         Farray_Freal8_1_3&, // MAh2
         Farray_Freal8_1_2&, // MCha
         Farray_Freal8_1_2&, // MCha2
         Farray_Freal8_1_5&, // MChi
         Farray_Freal8_1_5&, // MChi2
         Farray_Freal8_1_3&, // MFd
         Farray_Freal8_1_3&, // MFd2
         Farray_Freal8_1_3&, // MFe
         Farray_Freal8_1_3&, // MFe2
         Farray_Freal8_1_3&, // MFu
         Farray_Freal8_1_3&, // MFu2
         Freal8&, // MGlu
         Freal8&, // MGlu2
         Farray_Freal8_1_3&, // Mhh
         Farray_Freal8_1_3&, // Mhh2
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
         Farray_Freal8_1_3_1_3&, // ZA
         Farray_Fcomplex16_1_6_1_6&, // ZD
         Farray_Fcomplex16_1_3_1_3&, // ZDL
         Farray_Fcomplex16_1_3_1_3&, // ZDR
         Farray_Fcomplex16_1_6_1_6&, // ZE
         Farray_Fcomplex16_1_3_1_3&, // ZEL
         Farray_Fcomplex16_1_3_1_3&, // ZER
         Farray_Freal8_1_3_1_3&, // ZH
         Farray_Fcomplex16_1_5_1_5&, // ZN
         Farray_Freal8_1_2_1_2&, // ZP
         Farray_Fcomplex16_1_6_1_6&, // ZU
         Farray_Fcomplex16_1_3_1_3&, // ZUL
         Farray_Fcomplex16_1_3_1_3&, // ZUR
         Farray_Fcomplex16_1_3_1_3&, // ZV
         Farray_Fcomplex16_1_2_1_2&, // ZW
         Farray_Freal8_1_2_1_2&, // ZZ
         Freal8&, // betaH
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // vS
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3& , // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, //M3
         Finteger& //  kont
        ), "__loopmasses_nmssm_MOD_oneloopmasses", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(CalculateSpectrum, void,
	(Finteger&, // n_run
	 Freal8&, // delta_mass
	 Flogical&, // WriteOut
	 Finteger&, // kont
         Farray_Freal8_1_3&, // MAh
         Farray_Freal8_1_3&, // MAh2
         Farray_Freal8_1_2&, // MCha
         Farray_Freal8_1_2&, // MCha2
         Farray_Freal8_1_5&, // MChi
         Farray_Freal8_1_5&, // MChi2
         Farray_Freal8_1_3&, // MFd
         Farray_Freal8_1_3&, // MFd2
         Farray_Freal8_1_3&, // MFe
         Farray_Freal8_1_3&, // MFe2
         Farray_Freal8_1_3&, // MFu
         Farray_Freal8_1_3&, // MFu2
         Freal8&, // MGlu
         Freal8&, // MGlu2
         Farray_Freal8_1_3&, // Mhh
         Farray_Freal8_1_3&, // Mhh2
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
         Farray_Freal8_1_3_1_3&, // ZA
         Farray_Fcomplex16_1_6_1_6&, // ZD
         Farray_Fcomplex16_1_3_1_3&, // ZDL
         Farray_Fcomplex16_1_3_1_3&, // ZDR
         Farray_Fcomplex16_1_6_1_6&, // ZE
         Farray_Fcomplex16_1_3_1_3&, // ZEL
         Farray_Fcomplex16_1_3_1_3&, // ZER
         Farray_Freal8_1_3_1_3&, // ZH
         Farray_Fcomplex16_1_5_1_5&, // ZN
         Farray_Freal8_1_2_1_2&, // ZP
         Farray_Fcomplex16_1_6_1_6&, // ZU
         Farray_Fcomplex16_1_3_1_3&, // ZUL
         Farray_Fcomplex16_1_3_1_3&, // ZUR
         Farray_Fcomplex16_1_3_1_3&, // ZV
         Farray_Fcomplex16_1_2_1_2&, // ZW
         Farray_Freal8_1_2_1_2&, // ZZ
         Freal8&, // betaH
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // vS
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3& , // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, // M3
         Freal8& //  m_GUT
	), "__sphenonmssm_MOD_calculatespectrum", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(GetScaleUncertainty, void,
	(Freal8&, // delta_mass
	 Flogical&, // WriteOut
	 Finteger&, // kont
         Farray_Freal8_1_3&, // MAh
         Farray_Freal8_1_3&, // MAh2
         Farray_Freal8_1_2&, // MCha
         Farray_Freal8_1_2&, // MCha2
         Farray_Freal8_1_5&, // MChi
         Farray_Freal8_1_5&, // MChi2
         Farray_Freal8_1_3&, // MFd
         Farray_Freal8_1_3&, // MFd2
         Farray_Freal8_1_3&, // MFe
         Farray_Freal8_1_3&, // MFe2
         Farray_Freal8_1_3&, // MFu
         Farray_Freal8_1_3&, // MFu2
         Freal8&, // MGlu
         Freal8&, // MGlu2
         Farray_Freal8_1_3&, // Mhh
         Farray_Freal8_1_3&, // Mhh2
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
         Farray_Freal8_1_3_1_3&, // ZA
         Farray_Fcomplex16_1_6_1_6&, // ZD
         Farray_Fcomplex16_1_3_1_3&, // ZDL
         Farray_Fcomplex16_1_3_1_3&, // ZDR
         Farray_Fcomplex16_1_6_1_6&, // ZE
         Farray_Fcomplex16_1_3_1_3&, // ZEL
         Farray_Fcomplex16_1_3_1_3&, // ZER
         Farray_Freal8_1_3_1_3&, // ZH
         Farray_Fcomplex16_1_5_1_5&, // ZN
         Farray_Freal8_1_2_1_2&, // ZP
         Farray_Fcomplex16_1_6_1_6&, // ZU
         Farray_Fcomplex16_1_3_1_3&, // ZUL
         Farray_Fcomplex16_1_3_1_3&, // ZUR
         Farray_Fcomplex16_1_3_1_3&, // ZV
         Farray_Fcomplex16_1_2_1_2&, // ZW
         Farray_Freal8_1_2_1_2&, // ZZ
         Freal8&, // betaH
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // vS
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3& , // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, // M3
         Farray_Freal8_1_46&// mass_uncertainty_Q
        ), "__model_data_nmssm_MOD_mass_uncertainty_q", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), "__loopfunctions_MOD_getrenormalizationscale", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), "__model_data_nmssm_MOD_setrgescale", "SARAHSPheno_NMSSM_internal")
/*BE_FUNCTION(SetHighScaleModel, Flogical, (Fstring<20>), "__sugraruns_MOD_sethighscalemodel", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetWriteMinBr, void, (Freal8&), "__inputoutput_MOD_setwriteminbr", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetWriteMinSig, void, (Freal8&), "__inputoutput_MOD_setwriteminsig", "SARAHSPheno_NMSSM_internal")*/
BE_FUNCTION(SetGUTScale, void, (Freal8&), "__model_data_nmssm__MOD_setgutscale", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), "__model_data_nmssm_MOD_setstrictunification", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), "__model_data_nmssm_MOD_setyukawascheme", "SARAHSPheno_NMSSM_internal")
/*BE_FUNCTION(Set_Use_bsstep_instead_of_rkqs, Flogical, (Flogical&), "__mathematics_MOD_set_use_bsstep_instead_of_rkqs", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(Set_Use_rzextr_instead_of_pzextr, Flogical, (Flogical&), "__mathematics_MOD_set_use_rzextr_instead_of_pzextr", "SARAHSPheno_NMSSM_internal")*/
BE_FUNCTION(Alpha_MSbar, Freal8, (Freal8&, Freal8&), "__loopcouplings_nmssm_MOD_alpha_msbar", "SARAHSPheno_NMSSM_internal")

BE_FUNCTION(CalculateBR, void,
	(Flogical&, // CalcTBD
         Freal8&, // ratioWoM
         Freal8&, // epsI
         Freal8&, // delta_mass
	 Finteger&, // kont
         Farray_Freal8_1_3&, // MAh
         Farray_Freal8_1_3&, // MAh2
         Farray_Freal8_1_2&, // MCha
         Farray_Freal8_1_2&, // MCha2
         Farray_Freal8_1_5&, // MChi
         Farray_Freal8_1_5&, // MChi2
         Farray_Freal8_1_3&, // MFd
         Farray_Freal8_1_3&, // MFd2
         Farray_Freal8_1_3&, // MFe
         Farray_Freal8_1_3&, // MFe2
         Farray_Freal8_1_3&, // MFu
         Farray_Freal8_1_3&, // MFu2
         Freal8&, // MGlu
         Freal8&, // MGlu2
         Farray_Freal8_1_3&, // Mhh
         Farray_Freal8_1_3&, // Mhh2
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
         Farray_Freal8_1_3_1_3&, // ZA
         Farray_Fcomplex16_1_6_1_6&, // ZD
         Farray_Fcomplex16_1_3_1_3&, // ZDL
         Farray_Fcomplex16_1_3_1_3&, // ZDR
         Farray_Fcomplex16_1_6_1_6&, // ZE
         Farray_Fcomplex16_1_3_1_3&, // ZEL
         Farray_Fcomplex16_1_3_1_3&, // ZER
         Farray_Freal8_1_3_1_3&, // ZH
         Farray_Fcomplex16_1_5_1_5&, // ZN
         Farray_Freal8_1_2_1_2&, // ZP
         Farray_Fcomplex16_1_6_1_6&, // ZU
         Farray_Fcomplex16_1_3_1_3&, // ZUL
         Farray_Fcomplex16_1_3_1_3&, // ZUR
         Farray_Fcomplex16_1_3_1_3&, // ZV
         Farray_Fcomplex16_1_2_1_2&, // ZW
         Farray_Freal8_1_2_1_2&, // ZZ
         Freal8&, // betaH
         Freal8&, // vd
         Freal8&, // vu
         Freal8&, // vS
         Freal8&, // g1
         Freal8&, // g2
         Freal8&, // g3
         Farray_Fcomplex16_1_3_1_3&, // Yd
         Farray_Fcomplex16_1_3_1_3&, // Ye
         Fcomplex16&, // lam
         Fcomplex16&, // kap
         Farray_Fcomplex16_1_3_1_3&, // Yu
         Farray_Fcomplex16_1_3_1_3&, // Td
         Farray_Fcomplex16_1_3_1_3&, // Te
         Fcomplex16&, // Tlam
         Fcomplex16&, // Tk
         Farray_Fcomplex16_1_3_1_3&, // Tu
         Farray_Fcomplex16_1_3_1_3& , // mq2
         Farray_Fcomplex16_1_3_1_3&, // ml2
         Freal8&, // mHd2
         Freal8&, // mHu2
         Farray_Fcomplex16_1_3_1_3&, // md2
         Farray_Fcomplex16_1_3_1_3&, // mu2
         Farray_Fcomplex16_1_3_1_3&, // me2
         Freal8&, // ms2
         Fcomplex16&, // M1
         Fcomplex16&, // M2
         Fcomplex16&, // M3
         Farray_Freal8_1_6_1_1245&, // gPSd
         Farray_Freal8_1_6&, // gTSd
         Farray_Freal8_1_6_1_1245&, // BRSd
         Farray_Freal8_1_6_1_1245&, // gPSu
         Farray_Freal8_1_6&, // gTSu
         Farray_Freal8_1_6_1_1245&, // BRSu
         Farray_Freal8_1_6_1_1128&, // gPSe
         Farray_Freal8_1_6&, // gTSe
         Farray_Freal8_1_6_1_1128&, // BRSe
         Farray_Freal8_1_3_1_1002&, // gPSv
         Farray_Freal8_1_3&, // gTSv
         Farray_Freal8_1_3_1_1002&, // BRSv
         Farray_Freal8_1_3_1_209&, // gPhh
         Farray_Freal8_1_3&, // gThh
         Farray_Freal8_1_3_1_209&, // BRhh
         Farray_Freal8_1_3_1_207&, // gPAh
         Farray_Freal8_1_3&, // gTAh
         Farray_Freal8_1_3_1_207&, // BRAh
         Farray_Freal8_1_2_1_96&, // gPHpm
         Farray_Freal8_1_2&, // gTHpm
         Farray_Freal8_1_2_1_96&, // BRHpm
         Farray_Freal8_1_1_1_157&, // gPGlu
         Freal8&, // gTGlu
         Farray_Freal8_1_1_1_157&, // BRGlu
         Farray_Freal8_1_5_1_482&, // gPChi
         Farray_Freal8_1_5&, // gTChi
         Farray_Freal8_1_5_1_482&, // BRChi
         Farray_Freal8_1_2_1_316&, // gPCha
         Farray_Freal8_1_2&, // gTCha
         Farray_Freal8_1_2_1_316&, // BRCha
         Farray_Freal8_1_3_1_78&, // gPFu
         Farray_Freal8_1_3&, // gTFu
         Farray_Freal8_1_3_1_78& // BRFu
        ), "__branchingratios_nmssm_MOD_calculatebr_2", "SARAHSPheno_NMSSM_internal")

// Variables
// MODSEL Variables
BE_VARIABLE(HighScaleModel, Fstring<15>, "__model_data_nmssm_MOD_highscalemodel", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BoundaryCondition, Finteger, "__model_data_nmssm_MOD_boundarycondition", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(GenerationMixing, Flogical, "__control_MOD_generationmixing", "SARAHSPheno_NMSSM_internal")
// SPHENOINPUT Variables
BE_VARIABLE(ErrorLevel, Finteger, "__control_MOD_errorlevel", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(SPA_convention, Flogical, "__settings_MOD_spa_convention", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(External_Spectrum, Flogical, "__control_MOD_external_spectrum", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(External_Higgs, Flogical, "__control_MOD_external_higgs", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(FermionMassResummation, Flogical, "__control_MOD_fermionmassresummation", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(RXiNew, Freal8, "__settings_MOD_rxinew", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalculateTwoLoopHiggsMasses, Flogical, "__settings_MOD_calculatetwoloophiggsmasses", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(PurelyNumericalEffPot, Flogical, "__settings_MOD_purelynumericaleffpot", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalculateMSSM2Loop, Flogical, "__settings_MOD_calculatemssm2loop", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TwoLoopMethod, Finteger, "__settings_MOD_twoloopmethod", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(GaugelessLimit, Flogical, "__settings_MOD_gaugelesslimit", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(hstep_pn, Freal8, "__settings_MOD_hstep_pn", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(hstep_sa, Freal8, "__settings_MOD_hstep_sa", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TwoLoopRegulatorMass, Freal8, "__settings_MOD_twoloopregulatormass", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TwoLoopSafeMode, Flogical, "__settings_MOD_twoloopsafemode", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(L_BR, Flogical, "__control_MOD_l_br", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(L_CS, Flogical, "__control_MOD_l_cs", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MatchingOrder, Finteger, "__settings_MOD_matchingorder", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(GetMassUncertainty, Flogical, "__model_data_nmssm_MOD_getmassuncertainty","SARAHSPheno_NMSSM_internal")
BE_VARIABLE(delta_mass, Freal8, "__control_MOD_delta_mass", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(n_run, Finteger, "__control_MOD_n_run", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MinimalNumberIterations, Finteger, "__settings_MOD_minimalnumberiterations", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, "__settings_MOD_twolooprge", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteSLHA1, Flogical, "__settings_MOD_writeslha1", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(RotateNegativeFermionMasses, Flogical, "__model_data_nmssm_MOD_rotatenegativefermionmasses", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(SwitchToSCKM, Flogical, "__settings_MOD_switchtosckm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(IgnoreNegativeMasses, Flogical, "__model_data_nmssm_MOD_ignorenegativemasses", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(IgnoreNegativeMassesMZ, Flogical, "__model_data_nmssm_MOD_ignorenegativemassesmz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteOutputForNonConvergence, Flogical, "__settings_MOD_writeoutputfornonconvergence", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalculateOneLoopMasses, Flogical, "__settings_MOD_calculateoneloopmasses", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalculateLowEnergy, Flogical, "__settings_MOD_calculatelowenergy", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(IncludeDeltaVB, Flogical, "__settings_MOD_includedeltavb", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(IncludeBSMdeltaVB, Flogical, "__settings_MOD_includebsmdeltavb", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(KineticMixing, Flogical, "__model_data_nmssm_MOD_kineticmixing", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(RunningSUSYparametersLowEnergy, Flogical, "__settings_MOD_runningsusyparameterslowenergy", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(RunningSMparametersLowEnergy, Flogical, "__settings_MOD_runningsmparameterslowenergy", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteParametersAtQ, Flogical, "__settings_MOD_writeparametersatq", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(SolutionTadpoleNr, Finteger, "__model_data_nmssm_MOD_solutiontadpolenr", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(DecoupleAtRenScale, Flogical, "__settings_MOD_decoupleatrenscale", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Calculate_mh_within_SM, Flogical, "__settings_MOD_calculate_mh_within_sm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Force_mh_within_SM, Flogical, "__settings_MOD_force_mh_within_sm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MatchZWpoleMasses, Flogical, "__settings_MOD_matchzwpolemasses", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Write_WHIZARD, Flogical, "__model_data_nmssm_MOD_write_whizard", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Write_HiggsBounds, Flogical, "__inputoutput_nmssm_MOD_write_higgsbounds", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(OutputForMO, Flogical, "__settings_MOD_outputformo", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(OutputForMG, Flogical, "__settings_MOD_outputformg", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Write_WCXF, Flogical, "__settings_MOD_write_wcxf", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, "__control_MOD_non_zero_exit", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WidthToBeInvisible, Freal8, "__settings_MOD_widthtobeinvisible", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MaxMassLoop, Freal8, "__settings_MOD_maxmassloop", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MaxMassNumericalZero, Freal8, "__settings_MOD_maxmassnumericalzero", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ForceRealMatrices, Flogical, "__settings_MOD_forcerealmatrices", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(include1l2lshift, Flogical, "__settings_MOD_include1l2lshift", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(NewGBC, Flogical,"__settings_MOD_newgbc", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TreeLevelUnitarityLimits, Flogical, "__model_data_nmssm_MOD_treelevelunitaritylimits", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TrilinearUnitarity, Flogical, "__model_data_nmssm_MOD_trilinearunitarity", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(unitarity_s_min, Freal8, "__model_data_nmssm_MOD_unitarity_s_min", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(unitarity_s_max, Freal8, "__model_data_nmssm_MOD_unitarity_s_max", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(unitarity_steps, Finteger, "__model_data_nmssm_MOD_unitarity_steps", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(RunRGEs_unitarity, Flogical, "__model_data_nmssm_MOD_runrges_unitarity", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TUcutLevel, Finteger, "__model_data_nmssm_MOD_tucutlevel", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteTreeLevelTadpoleSolutions, Flogical, "__model_data_nmssm_MOD_writetreeleveltadpolesolutions", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteGUTvalues, Flogical, "__settings_MOD_writegutvalues", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteEffHiggsCouplingRatios, Flogical, "__model_data_nmssm_MOD_writeeffhiggscouplingratios", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(HigherOrderDiboson, Flogical, "__settings_MOD_higherorderdiboson", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(PoleMassesInLoops, Flogical, "__settings_MOD_polemassesinloops", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteHiggsDiphotonLoopContributions, Flogical, "__model_data_nmssm_MOD_writehiggsdiphotonloopcontributions", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteTreeLevelTadpoleParameters, Flogical, "__settings_MOD_writetreeleveltadpoleparameters", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalcFT, Flogical, "__model_data_nmssm_MOD_calcft", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(OneLoopFT, Flogical, "__model_data_nmssm_MOD_oneloopft" , "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MakeQTEST, Flogical, "__settings_MOD_makeqtest", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(PrintDebugInformation, Flogical, "__settings_MOD_printdebuginformation", "SARAHSPheno_NMSSM_internal")
// MINPAR Variables
BE_VARIABLE(m0, Freal8, "__model_data_nmssm_MOD_m0", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(m12, Fcomplex16, "__model_data_nmssm_MOD_m12", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TanBeta, Freal8, "__model_data_nmssm_MOD_tanbeta", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Azero, Fcomplex16, "__model_data_nmssm_MOD_azero", "SARAHSPheno_NMSSM_internal")
// EXTPAR Variables
//BE_VARIABLE(M1input, Fcomplex16, "__model_data_nmssm_MOD_m1input", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(M2input, Fcomplex16, "__model_data_nmssm_MOD_m2input", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(M3input, Fcomplex16, "__model_data_nmssm_MOD_m3input", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(LambdaInput, Fcomplex16, "__model_data_nmssm_MOD_lambdainput", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(KappaInput, Fcomplex16, "__model_data_nmssm_MOD_kappainput", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ALambdaInput, Fcomplex16, "__model_data_nmssm_MOD_alambdainput", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(AKappaInput, Fcomplex16, "__model_data_nmssm_MOD_akappainput", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MuEffinput, Fcomplex16, "__model_data_nmssm_MOD_mueffinput", "SARAHSPheno_NMSSM_internal")
// TDIN, TUIN, TEIN
BE_VARIABLE(InputValueforTd, Flogical, "__model_data_nmssm_MOD_inputvaluefortd", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TdIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_tdin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforTu, Flogical, "__model_data_nmssm_MOD_inputvaluefortu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TuIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_tuin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforTe, Flogical, "__model_data_nmssm_MOD_inputvalueforte", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TeIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_tein", "SARAHSPheno_NMSSM_internal")
// MSL2, MSE2 ,MSQ2, MSU2, MSD2
BE_VARIABLE(InputValueforml2, Flogical, "__model_data_nmssm_MOD_inputvalueforml2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ml2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_ml2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforme2, Flogical, "__model_data_nmssm_MOD_inputvalueforme2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(me2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_me2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueformq2, Flogical, "__model_data_nmssm_MOD_inputvalueformq2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mq2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_mq2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueformu2, Flogical, "__model_data_nmssm_MOD_inputvalueformu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mu2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_mu2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueformd2, Flogical, "__model_data_nmssm_MOD_inputvalueformd2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(md2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_md2in", "SARAHSPheno_NMSSM_internal")
// MSOFTIN Variables
BE_VARIABLE(InputValueformHd2, Flogical, "__model_data_nmssm_MOD_inputvalueformhd2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mHd2IN, Freal8, "__model_data_nmssm_MOD_mhd2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueformHu2, Flogical, "__model_data_nmssm_MOD_inputvalueformhu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mHu2IN, Freal8, "__model_data_nmssm_MOD_mhu2in", "SARAHSPheno_NMSSM_internal")
// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, "__standardmodel_MOD_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mZ2, Freal8,  "__standardmodel_MOD_mz2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gamZ, Freal8, "__standardmodel_MOD_gamz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gamZ2, Freal8, "__standardmodel_MOD_gamz2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gmZ, Freal8, "__standardmodel_MOD_gmz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gmZ2, Freal8, "__standardmodel_MOD_gmz2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, "__standardmodel_MOD_brzqq", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, "__standardmodel_MOD_brzll", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BrZinv, Freal8, "__standardmodel_MOD_brzinv", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mW, Freal8, "__standardmodel_MOD_mw", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mW_SM, Freal8, "__model_data_nmssm_MOD_mw_sm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mW2, Freal8, "__standardmodel_MOD_mw2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gamW, Freal8, "__standardmodel_MOD_gamw", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gamW2, Freal8, "__standardmodel_MOD_gamw2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gmW, Freal8, "__standardmodel_MOD_gmw", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(gmW2, Freal8, "__standardmodel_MOD_gmw2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, "__standardmodel_MOD_brwqq", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, "__standardmodel_MOD_brwln", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, "__standardmodel_MOD_mf_nu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MNuR, Freal8, "__model_data_MOD_mnur", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Q_light_quarks, Freal8, "__standardmodel_MOD_q_light_quarks", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, "__standardmodel_MOD_delta_alpha_lepton", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, "__standardmodel_MOD_delta_alpha_hadron", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Alpha, Freal8, "__standardmodel_MOD_alpha", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Alpha_mZ, Freal8, "__standardmodel_MOD_alpha_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, "__standardmodel_MOD_alpha_mz_ms", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MZ_input, Flogical, "__model_data_nmssm_MOD_mz_input", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, "__standardmodel_MOD_alphas_mz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(G_F, Freal8, "__standardmodel_MOD_g_f", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(KFactorLee, Freal8, "__standardmodel_MOD_kfactorlee", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, "__standardmodel_MOD_ckm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(lam_wolf, Freal8, "__standardmodel_MOD_lam_wolf", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(A_wolf, Freal8, "__standardmodel_MOD_a_wolf", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(rho_wolf, Freal8, "__standardmodel_MOD_rho_wolf", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(eta_wolf, Freal8, "__standardmodel_MOD_eta_wolf", "SARAHSPheno_NMSSM_internal")
// MASS and output Variables
BE_VARIABLE(MAh, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mah", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MAh2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mah2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MCha, Farray_Freal8_1_2, "__model_data_nmssm_MOD_mcha", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MCha2, Farray_Freal8_1_2, "__model_data_nmssm_MOD_mcha2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MChi, Farray_Freal8_1_5, "__model_data_nmssm_MOD_mchi", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MChi2, Farray_Freal8_1_5, "__model_data_nmssm_MOD_mchi2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFd, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfd", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFd2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfd2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFe, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfe", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFe2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfe2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFu, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MFu2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mfu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MGlu, Freal8, "__model_data_nmssm_MOD_mglu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MGlu2, Freal8, "__model_data_nmssm_MOD_mglu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Mhh, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mhh", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Mhh2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_mhh2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MHpm, Farray_Freal8_1_2, "__model_data_nmssm_MOD_mhpm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MHpm2, Farray_Freal8_1_2, "__model_data_nmssm_MOD_mhpm2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSd, Farray_Freal8_1_6, "__model_data_nmssm_MOD_msd", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSd2, Farray_Freal8_1_6, "__model_data_nmssm_MOD_msd2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSe, Farray_Freal8_1_6, "__model_data_nmssm_MOD_mse", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSe2, Farray_Freal8_1_6, "__model_data_nmssm_MOD_mse2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSu, Farray_Freal8_1_6, "__model_data_nmssm_MOD_msu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSu2, Farray_Freal8_1_6, "__model_data_nmssm_MOD_msu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSv, Farray_Freal8_1_3, "__model_data_nmssm_MOD_msv", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MSv2, Farray_Freal8_1_3, "__model_data_nmssm_MOD_msv2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MVWm, Freal8, "__model_data_nmssm_MOD_mvwm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MVWm2, Freal8, "__model_data_nmssm_MOD_mvwm2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MVZ, Freal8, "__model_data_nmssm_MOD_mvz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(MVZ2, Freal8, "__model_data_nmssm_MOD_mvz2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(pG, Fcomplex16, "__model_data_nmssm_MOD_pg", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TW, Freal8, "__model_data_nmssm_MOD_tw", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(UM, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssm_MOD_um", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(UP, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssm_MOD_up" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(v, Freal8, "__model_data_nmssm_MOD_v", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZA, Farray_Freal8_1_3_1_3, "__model_data_nmssm_MOD_za", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZD, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssm_MOD_zd" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZDL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zdl", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZDR, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zdr", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZE, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssm_MOD_ze", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZEL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zel" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZER, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zer", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZH, Farray_Freal8_1_3_1_3, "__model_data_nmssm_MOD_zh", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZN, Farray_Fcomplex16_1_5_1_5, "__model_data_nmssm_MOD_zn" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZP, Farray_Freal8_1_2_1_2, "__model_data_nmssm_MOD_zp" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZU, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssm_MOD_zu" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZUL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zul", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZUR, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zur" ,"SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZV, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_zv", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZW, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssm_MOD_zw", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ZZ, Farray_Freal8_1_2_1_2, "__model_data_nmssm_MOD_zz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(betaH, Freal8, "__model_data_nmssm_MOD_betah", "SARAHSPheno_NMSSM_internal")
// Model data
BE_VARIABLE(TanBetaMZ, Freal8, "__model_data_nmssm_MOD_tanbetamz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vd, Freal8, "__model_data_nmssm_MOD_vd", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vdIN, Freal8, "__model_data_nmssm_MOD_vdin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vu, Freal8, "__model_data_nmssm_MOD_vu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vuIN, Freal8, "__model_data_nmssm_MOD_vuin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vS, Freal8, "__model_data_nmssm_MOD_vs", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vSIN, Freal8, "__model_data_nmssm_MOD_vsin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g1, Freal8, "__model_data_nmssm_MOD_g1", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g1IN, Freal8, "__model_data_nmssm_MOD_g1in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g2, Freal8, "__model_data_nmssm_MOD_g2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g2IN, Freal8, "__model_data_nmssm_MOD_g2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g3, Freal8, "__model_data_nmssm_MOD_g3", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g3IN, Freal8, "__model_data_nmssm_MOD_g3in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Yd, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_yd", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(YdIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_ydin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Ye, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_ye", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(YeIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_yein", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Yu, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_yu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(YuIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_yuin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(lam, Fcomplex16, "__model_data_nmssm_MOD_lam", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(lamIN, Fcomplex16, "__model_data_nmssm_MOD_lamin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(kap, Fcomplex16, "__model_data_nmssm_MOD_kap", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(kapIN, Fcomplex16, "__model_data_nmssm_MOD_kapin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Td, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_td", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Te, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_te", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Tu, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_tu", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Tlam, Fcomplex16, "__model_data_nmssm_MOD_tlam", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TlamIN, Fcomplex16, "__model_data_nmssm_MOD_tlamin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(Tk, Fcomplex16, "__model_data_nmssm_MOD_tk", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TkIN, Fcomplex16, "__model_data_nmssm_MOD_tkin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mq2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_mq2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ml2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_ml2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mHd2, Freal8, "__model_data_nmssm_MOD_mhd2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mHu2, Freal8, "__model_data_nmssm_MOD_mhu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(md2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_md2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mu2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_mu2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(me2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssm_MOD_me2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ms2, Freal8, "__model_data_nmssm_MOD_ms2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ms2IN, Freal8, "__model_data_nmssm_MOD_ms2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M1, Fcomplex16, "__model_data_nmssm_MOD_m1", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M1IN, Fcomplex16, "__model_data_nmssm_MOD_m1in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforM1, Flogical,"__model_data_nmssm_MOD_inputvalueform1", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M2, Fcomplex16, "__model_data_nmssm_MOD_m2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M2IN, Fcomplex16, "__model_data_nmssm_MOD_m2in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforM2, Flogical,"__model_data_nmssm_MOD_inputvalueform2", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M3, Fcomplex16, "__model_data_nmssm_MOD_m3", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(M3IN, Fcomplex16, "__model_data_nmssm_MOD_m3in", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(InputValueforM3, Flogical, "__model_data_nmssm_MOD_inputvalueform3", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vdMZ, Freal8, "__model_data_nmssm_MOD_vdmz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vuMZ, Freal8, "__model_data_nmssm_MOD_vumz", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(vSMZ, Freal8, "__model_data_nmssm_MOD_vsmz", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(vSM, Freal8, "__sphenonmssm_MOD_vsm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(g1SM, Freal8, "__sphenonmssm_MOD_g1sm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(g2SM, Freal8, "__sphenonmssm_MOD_g2sm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(g3SM, Freal8, "__sphenonmssm_MOD_g3sm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g1GUT, Freal8, "__model_data_nmssm_MOD_g1gut", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g2GUT, Freal8, "__model_data_nmssm_MOD_g2gut", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(g3GUT, Freal8, "__model_data_nmssm_MOD_g3gut", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(YuSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yusm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(YdSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_ydsm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(YeSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yesm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Yd_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yd_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Yu_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yu_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Td_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_td_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Tu_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_tu_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(mq2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mq2_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(md2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_md2_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(mu2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mu2_ckm", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Td_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_td_out", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(Tu_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_tu_out", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(mq2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mq2_out", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(md2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_md2_out", "SARAHSPheno_NMSSM_internal")
//BE_VARIABLE(mu2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mu2_out", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(OneLoopMatching, Flogical, "__model_data_nmssm_MOD_oneloopmatching", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(TwoLoopMatching, Flogical, "__model_data_nmssm_MOD_twoloopmatching", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(GuessTwoLoopMatchingBSM, Flogical, "__model_data_nmssm_MOD_guesstwoloopmatchingbsm", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mass_uncertainty_Yt, Farray_Freal8_1_46, "__model_data_nmssm_MOD_mass_uncertainty_yt", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mass_uncertainty_Q, Farray_Freal8_1_46, "__model_data_nmssm_MOD_mass_uncertainty_q", "SARAHSPheno_NMSSM_internal")
// Control Variables
BE_VARIABLE(kont, Finteger, "__sphenonmssm_MOD_kont", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(WriteOut, Flogical, "__control_MOD_writeout", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(epsI, Freal8, "__sphenonmssm_MOD_epsi", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(deltaM, Freal8, "__sphenonmssm_MOD_deltam", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(mGUT, Freal8, "__sphenonmssm_MOD_mgut", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ErrCan, Finteger, "__control_MOD_errcan", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(FoundIterativeSolution, Flogical, "__settings_MOD_founditerativesolution", "SARAHSPheno_NMSSM_internal")
// Other variables
BE_VARIABLE(Qin, Freal8, "__sphenonmssm_MOD_qin", "SARAHSPheno_NMSSM_internal")
BE_VARIABLE(ratioWoM, Freal8, "__sphenonmssm_MOD_ratiowom","SARAHSPheno_NMSSM_internal")
BE_VARIABLE(CalcTBD, Flogical, "__sphenonmssm_MOD_calctbd","SARAHSPheno_NMSSM_internal")
// Branching Ratio variables
/*BE_VARIABLE(gPSd, 
BE_VARIABLE(gTSd
BE_VARIABLE(BRSd
BE_VARIABLE(gPSu
BE_VARIABLE(gTSu
BE_VARIABLE(BRSu
BE_VARIABLE(gPSe
BE_VARIABLE(gTSe
BE_VARIABLE(BRSe
BE_VARIABLE(gPSv
BE_VARIABLE(gTSv
BE_VARIABLE(BRSv
BE_VARIABLE(gPhh
BE_VARIABLE(gThh
BE_VARIABLE(BRhh
BE_VARIABLE(gPAh
BE_VARIABLE(gTAh
BE_VARIABLE(BRAh
BE_VARIABLE(gPHpm
BE_VARIABLE(gTHpm
BE_VARIABLE(BRHpm
BE_VARIABLE(gPGlu
BE_VARIABLE(gTGlu
BE_VARIABLE(BRGlu
BE_VARIABLE(gPChi
BE_VARIABLE(gTChi
BE_VARIABLE(BRChi
BE_VARIABLE(gPCha
BE_VARIABLE(gTCha
BE_VARIABLE(BRCha
BE_VARIABLE(gPFu
BE_VARIABLE(gTFu
BE_VARIABLE(BRFu
*/
// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SARAHSPheno_NMSSM_spectrum")
BE_CONV_FUNCTION(run_SPheno_decays, int, (const Spectrum &, DecayTable &), "SARAHSPheno_NMSSM_decays")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const std::map<str, safe_ptr<double> >&), "SARAHSPheno_NMSSM_internal")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SARAHSPheno_NMSSM_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SARAHSPheno_NMSSM_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SARAHSPheno_NMSSM_internal")

// Initialisation functions (dependencies)


// End
#include "gambit/Backends/backend_undefs.hpp"
