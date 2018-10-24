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
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#define BACKENDNAME SARAHSPheno_NMSSMEFT
#define BACKENDLANG FORTRAN
#define VERSION 4.0.3
#define SARAH_VERSION 4.13.0
#define SAFE_VERSION 4_0_3

// Begin
LOAD_LIBRARY

// Allow for NMSSM EFT only
BE_ALLOW_MODELS(NMSSMEFTatQ)

// Functions
BE_FUNCTION(Set_All_Parameters_0, void, (), "__model_data_nmssmeft_MOD_set_all_parameters_0", "SARAHSARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(SetRenormalizationScale, Freal8, (Freal8&), "__loopfunctions_MOD_setrenormalizationscale", "SARAHSARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), "__loopfunctions_MOD_initializeloopfunctions", "SARAHSARAHPhenoNMSSMEFT_internal")
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
   "__standardmodel_MOD_calculaterunningmasses", "SARAHPhenoNMSSMEFT_internal")
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
        ), "__model_data_nmssmeft_MOD_setmatchingconditions", "SARAHSPheno_NMSSMEFT_internal")
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
        ), "__model_data_MOD_switch_from_superckm", "SARAHPhenoNMSSMEFT_internal")
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
        ), "__tadpoles_nmssmeft_MOD_solvetadpoleequations", "SARAHPhenoNMSSMEFT_internal")
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
        ), "__loopmasses_nmssmeft_MOD_oneloopmasses", "SARAHPhenoNMSSMEFT_internal")
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
  ), "calculatespectrum.2199", "SARAHPhenoNMSSMEFT_internal")
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
  ), "__model_data_nmssmeft_MOD_mass_uncertainty_q", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), "__loopfunctions_MOD_getrenormalizationscale", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), "__model_data_nmssmeft_MOD_setrgescale", "SARAHPhenoNMSSMEFT_internal")
/*BE_FUNCTION(SetHighScaleModel, Flogical, (Fstring<20>), "__sugraruns_MOD_sethighscalemodel", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(SetWriteMinBr, void, (Freal8&), "__inputoutput_MOD_setwriteminbr", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(SetWriteMinSig, void, (Freal8&), "__inputoutput_MOD_setwriteminsig", "SARAHPhenoNMSSMEFT_internal")*/
BE_FUNCTION(SetGUTScale, void, (Freal8&), "__model_data_nmssmeft_MOD_setgutscale", "SARAHSPheno_NMSSM_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), "__model_data_nmssmeft_MOD_setstrictunification", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), "__model_data_nmssmeft_MOD_setyukawascheme", "SARAHPhenoNMSSMEFT_internal")
/*BE_FUNCTION(Set_Use_bsstep_instead_of_rkqs, Flogical, (Flogical&), "__mathematics_MOD_set_use_bsstep_instead_of_rkqs", "SARAHPhenoNMSSMEFT_internal")
BE_FUNCTION(Set_Use_rzextr_instead_of_pzextr, Flogical, (Flogical&), "__mathematics_MOD_set_use_rzextr_instead_of_pzextr", "SARAHPhenoNMSSMEFT_internal")*/
BE_FUNCTION(Alpha_MSbar, Freal8, (Freal8&, Freal8&), "__loopcouplings_nmssmeft_MOD_alpha_msbar", "SARAHPhenoNMSSMEFT_internal")

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
   Freal8, // gTGlu
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
  ), "__branchingratios_nmssmeft_MOD_calculatebr", "SARAHPhenoNMSSMEFT_internal")

// Variables
// MODSEL Variables
BE_VARIABLE(HighScaleModel, Fstring<15>, "__model_data_nmssmeft_MOD_highscalemodel", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BoundaryCondition, Finteger, "__model_data_nmssmeft_MOD_boundarycondition", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(GenerationMixing, Flogical, "__control_MOD_generationmixing", "SARAHPhenoNMSSMEFT_internal")
// SPHENOINPUT Variables
BE_VARIABLE(ErrorLevel, Finteger, "__control_MOD_errorlevel", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(SPA_convention, Flogical, "__settings_MOD_spa_convention", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(External_Spectrum, Flogical, "__control_MOD_external_spectrum", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(External_Higgs, Flogical, "__control_MOD_external_higgs", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(FermionMassResummation, Flogical, "__control_MOD_fermionmassresummation", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(RXiNew, Freal8, "__settings_MOD_rxinew", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalculateTwoLoopHiggsMasses, Flogical, "__settings_MOD_calculatetwoloophiggsmasses", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(PurelyNumericalEffPot, Flogical, "__settings_MOD_purelynumericaleffpot", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalculateMSSM2Loop, Flogical, "__settings_MOD_calculatemssm2loop", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TwoLoopMethod, Finteger, "__settings_MOD_twoloopmethod", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(GaugelessLimit, Flogical, "__settings_MOD_gaugelesslimit", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(hstep_pn, Freal8, "__settings_MOD_hstep_pn", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(hstep_sa, Freal8, "__settings_MOD_hstep_sa", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TwoLoopRegulatorMass, Freal8, "__settings_MOD_twoloopregulatormass", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TwoLoopSafeMode, Flogical, "__settings_MOD_twoloopsafemode", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(L_BR, Flogical, "__control_MOD_l_br", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(L_CS, Flogical, "__control_MOD_l_cs", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MatchingOrder, Finteger, "__settings_MOD_matchingorder", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(GetMassUncertainty, Flogical, "__model_data_nmssmeft_MOD_getmassuncertainty","SPhenoNMSSM_interal")
BE_VARIABLE(delta_mass, Freal8, "__control_MOD_delta_mass", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(n_run, Finteger, "__control_MOD_n_run", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MinimalNumberIterations, Finteger, "__settings_MOD_minimalnumberiterations", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, "__settings_MOD_twolooprge", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteSLHA1, Flogical, "__settings_MOD_writeslha1", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(RotateNegativeFermionMasses, Flogical, "__model_data_nmssmeft_MOD_rotatenegativefermionmasses", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(SwitchToSCKM, Flogical, "__settings_MOD_switchtosckm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(IgnoreNegativeMasses, Flogical, "__model_data_nmssmeft_MOD_ignorenegativemasses", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(IgnoreNegativeMassesMZ, Flogical, "__model_data_nmssmeft_MOD_ignorenegativemassesmz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteOutputForNonConvergence, Flogical, "__settings_MOD_writeoutputfornonconvergence", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalculateOneLoopMasses, Flogical, "__settings_MOD_calculateoneloopmasses", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalculateLowEnergy, Flogical, "__settings_MOD_calculatelowenergy", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(IncludeDeltaVB, Flogical, "__settings_MOD_includedeltavb", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(IncludeBSMdeltaVB, Flogical, "__settings_MOD_includebsmdeltavb", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(KineticMixing, Flogical, "__model_data_nmssmeft_MOD_kineticmixing", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(RunningSUSYparametersLowEnergy, Flogical, "__settings_MOD_runningsusyparameterslowenergy", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(RunningSMparametersLowEnergy, Flogical, "__settings_MOD_runningsmparameterslowenergy", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteParametersAtQ, Flogical, "__settings_MOD_writeparametersatq", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(SolutionTadpoleNr, Finteger, "__model_data_nmssmeft_MOD_solutiontadpolenr", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(DecoupleAtRenScale, Flogical, "__settings_MOD_decoupleatrenscale", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Calculate_mh_within_SM, Flogical, "__settings_MOD_calculate_mh_within_sm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Force_mh_within_SM, Flogical, "__settings_MOD_force_mh_within_sm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MatchZWpoleMasses, Flogical, "__settings_MOD_matchzwpolemasses", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Write_WHIZARD, Flogical, "__model_data_nmssmeft_MOD_write_whizard", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Write_HiggsBounds, Flogical, "__inputoutput_nmssmeft_MOD_write_higgsbounds", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(OutputForMO, Flogical, "__settings_MOD_outputformo", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(OutputForMG, Flogical, "__settings_MOD_outputformg", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Write_WCXF, Flogical, "__settings_MOD_write_wcxf", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, "__control_MOD_non_zero_exit", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WidthToBeInvisible, Freal8, "__settings_MOD_widthtobeinvisible", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MaxMassLoop, Freal8, "__settings_MOD_maxmassloop", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MaxMassNumericalZero, Freal8, "__settings_MOD_maxmassnumericalzero", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ForceRealMatrices, Flogical, "__settings_MOD_forcerealmatrices", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(include1l2lshift, Flogical, "__settings_MOD_include1l2lshift", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(NewGBC, Flogical,"__settings_MOD_newgbc", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TreeLevelUnitarityLimits, Flogical, "__model_data_nmssmeft_MOD_treelevelunitaritylimits", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TrilinearUnitarity, Flogical, "__model_data_nmssmeft_MOD_trilinearunitarity", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(unitarity_s_min, Freal8, "__model_data_nmssmeft_MOD_unitarity_s_min", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(unitarity_s_max, Freal8, "__model_data_nmssmeft_MOD_unitarity_s_max", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(unitarity_steps, Finteger, "__model_data_nmssmeft_MOD_unitarity_steps", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(RunRGEs_unitarity, Flogical, "__model_data_nmssmeft_MOD_runrges_unitarity", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TUcutLevel, Finteger, "__model_data_nmssmeft_MOD_tucutlevel", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteTreeLevelTadpoleSolutions, Flogical, "__model_data_nmssmeft_MOD_writetreeleveltadpolesolutions", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteGUTvalues, Flogical, "__settings_MOD_writegutvalues", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteEffHiggsCouplingRatios, Flogical, "__model_data_nmssmeft_MOD_writeeffhiggscouplingratios", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(HigherOrderDiboson, Flogical, "__settings_MOD_higherorderdiboson", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(PoleMassesInLoops, Flogical, "__settings_MOD_polemassesinloops", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteHiggsDiphotonLoopContributions, Flogical, "__model_data_nmssmeft_MOD_writehiggsdiphotonloopcontributions", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteTreeLevelTadpoleParameters, Flogical, "__settings_MOD_writetreeleveltadpoleparameters", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalcFT, Flogical, "__model_data_nmssmeft_MOD_calcft", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(OneLoopFT, Flogical, "__model_data_nmssmeft_MOD_oneloopft" , "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MakeQTEST, Flogical, "__settings_MOD_makeqtest", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(PrintDebugInformation, Flogical, "__settings_MOD_printdebuginformation", "SARAHPhenoNMSSMEFT_internal")
// MINPAR Variables
BE_VARIABLE(m0, Freal8, "__model_data_nmssmeft_MOD_m0", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(m12, Fcomplex16, "__model_data_nmssmeft_MOD_m12", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TanBeta, Freal8, "__model_data_nmssmeft_MOD_tanbeta", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Azero, Fcomplex16, "__model_data_nmssmeft_MOD_azero", "SARAHPhenoNMSSMEFT_internal")
// EXTPAR Variables
//BE_VARIABLE(M1input, Fcomplex16, "__model_data_nmssmeft_MOD_m1input", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(M2input, Fcomplex16, "__model_data_nmssmeft_MOD_m2input", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(M3input, Fcomplex16, "__model_data_nmssmeft_MOD_m3input", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(LambdaInput, Fcomplex16, "__model_data_nmssmeft_MOD_lambdainput", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(KappaInput, Fcomplex16, "__model_data_nmssmeft_MOD_kappainput", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ALambdaInput, Fcomplex16, "__model_data_nmssmeft_MOD_alambdainput", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(AKappaInput, Fcomplex16, "__model_data_nmssmeft_MOD_akappainput", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MuEffinput, Fcomplex16, "__model_data_nmssmeft_MOD_mueffinput", "SARAHPhenoNMSSMEFT_internal")
// TDIN, TUIN, TEIN
BE_VARIABLE(InputValueforTd, Flogical, "__model_data_nmssmeft_MOD_inputvaluefortd", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TdIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_tdin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforTu, Flogical, "__model_data_nmssmeft_MOD_inputvaluefortu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TuIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_tuin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforTe, Flogical, "__model_data_nmssmeft_MOD_inputvalueforte", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TeIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_tein", "SARAHPhenoNMSSMEFT_internal")
// MSL2, MSE2 ,MSQ2, MSU2, MSD2
BE_VARIABLE(InputValueforml2, Flogical, "__model_data_nmssmeft_MOD_inputvalueforml2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ml2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_ml2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforme2, Flogical, "__model_data_nmssmeft_MOD_inputvalueforme2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(me2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_me2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueformq2, Flogical, "__model_data_nmssmeft_MOD_inputvalueformq2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mq2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_mq2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueformu2, Flogical, "__model_data_nmssmeft_MOD_inputvalueformu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mu2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_mu2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueformd2, Flogical, "__model_data_nmssmeft_MOD_inputvalueformd2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(md2IN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_md2in", "SARAHPhenoNMSSMEFT_internal")
// MSOFTIN Variables
BE_VARIABLE(InputValueformHd2, Flogical, "__model_data_nmssmeft_MOD_inputvalueformhd2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mHd2IN, Freal8, "__model_data_nmssmeft_MOD_mhd2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueformHu2, Flogical, "__model_data_nmssmeft_MOD_inputvalueformhu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mHu2IN, Freal8, "__model_data_nmssmeft_MOD_mhu2in", "SARAHPhenoNMSSMEFT_internal")
// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, "__standardmodel_MOD_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mZ2, Freal8,  "__standardmodel_MOD_mz2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gamZ, Freal8, "__standardmodel_MOD_gamz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gamZ2, Freal8, "__standardmodel_MOD_gamz2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gmZ, Freal8, "__standardmodel_MOD_gmz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gmZ2, Freal8, "__standardmodel_MOD_gmz2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, "__standardmodel_MOD_brzqq", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, "__standardmodel_MOD_brzll", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BrZinv, Freal8, "__standardmodel_MOD_brzinv", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mW, Freal8, "__standardmodel_MOD_mw", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mW_SM, Freal8, "__model_data_nmssmeft_MOD_mw_sm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mW2, Freal8, "__standardmodel_MOD_mw2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gamW, Freal8, "__standardmodel_MOD_gamw", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gamW2, Freal8, "__standardmodel_MOD_gamw2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gmW, Freal8, "__standardmodel_MOD_gmw", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(gmW2, Freal8, "__standardmodel_MOD_gmw2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, "__standardmodel_MOD_brwqq", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, "__standardmodel_MOD_brwln", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, "__standardmodel_MOD_mf_nu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_l2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_u2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, "__standardmodel_MOD_mf_d2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Q_light_quarks, Freal8, "__standardmodel_MOD_q_light_quarks", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, "__standardmodel_MOD_delta_alpha_lepton", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, "__standardmodel_MOD_delta_alpha_hadron", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Alpha, Freal8, "__standardmodel_MOD_alpha", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Alpha_mZ, Freal8, "__standardmodel_MOD_alpha_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, "__standardmodel_MOD_alpha_mz_ms", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MZ_input, Flogical, "__model_data_nmssmeft_MOD_mz_input", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, "__standardmodel_MOD_alphas_mz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(G_F, Freal8, "__standardmodel_MOD_g_f", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(KFactorLee, Freal8, "__standardmodel_MOD_kfactorlee", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, "__standardmodel_MOD_ckm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(lam_wolf, Freal8, "__standardmodel_MOD_lam_wolf", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(A_wolf, Freal8, "__standardmodel_MOD_a_wolf", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(rho_wolf, Freal8, "__standardmodel_MOD_rho_wolf", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(eta_wolf, Freal8, "__standardmodel_MOD_eta_wolf", "SARAHPhenoNMSSMEFT_internal")
// MASS and output Variables
BE_VARIABLE(MAh, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mah", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MAh2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mah2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MCha, Farray_Freal8_1_2, "__model_data_nmssmeft_MOD_mcha", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MCha2, Farray_Freal8_1_2, "__model_data_nmssmeft_MOD_mcha2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MChi, Farray_Freal8_1_5, "__model_data_nmssmeft_MOD_mchi", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MChi2, Farray_Freal8_1_5, "__model_data_nmssmeft_MOD_mchi2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFd, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfd", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFd2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfd2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFe, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfe", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFe2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfe2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFu, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MFu2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mfu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MGlu, Freal8, "__model_data_nmssmeft_MOD_mglu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MGlu2, Freal8, "__model_data_nmssmeft_MOD_mglu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Mhh, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mhh", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Mhh2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_mhh2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MHpm, Farray_Freal8_1_2, "__model_data_nmssmeft_MOD_mhpm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MHpm2, Farray_Freal8_1_2, "__model_data_nmssmeft_MOD_mhpm2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSd, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_msd", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSd2, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_msd2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSe, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_mse", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSe2, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_mse2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSu, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_msu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSu2, Farray_Freal8_1_6, "__model_data_nmssmeft_MOD_msu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSv, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_msv", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MSv2, Farray_Freal8_1_3, "__model_data_nmssmeft_MOD_msv2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MVWm, Freal8, "__model_data_nmssmeft_MOD_mvwm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MVWm2, Freal8, "__model_data_nmssmeft_MOD_mvwm2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MVZ, Freal8, "__model_data_nmssmeft_MOD_mvz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(MVZ2, Freal8, "__model_data_nmssmeft_MOD_mvz2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(pG, Fcomplex16, "__model_data_nmssmeft_MOD_pg", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TW, Freal8, "__model_data_nmssmeft_MOD_tw", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(UM, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssmeft_MOD_um", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(UP, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssmeft_MOD_up" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(v, Freal8, "__model_data_nmssmeft_MOD_v", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZA, Farray_Freal8_1_3_1_3, "__model_data_nmssmeft_MOD_za", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZD, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssmeft_MOD_zd" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZDL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zdl", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZDR, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zdr", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZE, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssmeft_MOD_ze", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZEL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zel" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZER, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zer", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZH, Farray_Freal8_1_3_1_3, "__model_data_nmssmeft_MOD_zh", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZN, Farray_Fcomplex16_1_5_1_5, "__model_data_nmssmeft_MOD_zn" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZP, Farray_Freal8_1_2_1_2, "__model_data_nmssmeft_MOD_zp" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZU, Farray_Fcomplex16_1_6_1_6, "__model_data_nmssmeft_MOD_zu" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZUL, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zul", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZUR, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zur" ,"SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZV, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_zv", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZW, Farray_Fcomplex16_1_2_1_2, "__model_data_nmssmeft_MOD_zw", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ZZ, Farray_Freal8_1_2_1_2, "__model_data_nmssmeft_MOD_zz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(betaH, Freal8, "__model_data_nmssmeft_MOD_betah", "SARAHPhenoNMSSMEFT_internal")
// Model data
BE_VARIABLE(TanBetaMZ, Freal8, "__model_data_nmssmeft_MOD_tanbetamz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vd, Freal8, "__model_data_nmssmeft_MOD_vd", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vdIN, Freal8, "__model_data_nmssmeft_MOD_vdin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vu, Freal8, "__model_data_nmssmeft_MOD_vu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vuIN, Freal8, "__model_data_nmssmeft_MOD_vuin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vS, Freal8, "__model_data_nmssmeft_MOD_vs", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vSIN, Freal8, "__model_data_nmssmeft_MOD_vsin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g1, Freal8, "__model_data_nmssmeft_MOD_g1", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g1IN, Freal8, "__model_data_nmssmeft_MOD_g1in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g2, Freal8, "__model_data_nmssmeft_MOD_g2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g2IN, Freal8, "__model_data_nmssmeft_MOD_g2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g3, Freal8, "__model_data_nmssmeft_MOD_g3", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g3IN, Freal8, "__model_data_nmssmeft_MOD_g3in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Yd, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_yd", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(YdIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_ydin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Ye, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_ye", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(YeIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_yein", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Yu, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_yu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(YuIN, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_yuin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(lam, Fcomplex16, "__model_data_nmssmeft_MOD_lam", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(lamIN, Fcomplex16, "__model_data_nmssmeft_MOD_lamin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(kap, Fcomplex16, "__model_data_nmssmeft_MOD_kap", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(kapIN, Fcomplex16, "__model_data_nmssmeft_MOD_kapin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Td, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_td", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Te, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_te", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Tu, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_tu", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Tlam, Fcomplex16, "__model_data_nmssmeft_MOD_tlam", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TlamIN, Fcomplex16, "__model_data_nmssmeft_MOD_tlamin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(Tk, Fcomplex16, "__model_data_nmssmeft_MOD_tk", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TkIN, Fcomplex16, "__model_data_nmssmeft_MOD_tkin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mq2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_mq2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ml2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_ml2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mHd2, Freal8, "__model_data_nmssmeft_MOD_mhd2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mHu2, Freal8, "__model_data_nmssmeft_MOD_mhu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(md2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_md2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mu2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_mu2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(me2, Farray_Fcomplex16_1_3_1_3, "__model_data_nmssmeft_MOD_me2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ms2, Freal8, "__model_data_nmssmeft_MOD_ms2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ms2IN, Freal8, "__model_data_nmssmeft_MOD_ms2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M1, Fcomplex16, "__model_data_nmssmeft_MOD_m1", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M1IN, Fcomplex16, "__model_data_nmssmeft_MOD_m1in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforM1, Flogical,"__model_data_nmssmeft_MOD_inputvalueform1", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M2, Fcomplex16, "__model_data_nmssmeft_MOD_m2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M2IN, Fcomplex16, "__model_data_nmssmeft_MOD_m2in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforM2, Flogical,"__model_data_nmssmeft_MOD_inputvalueform2", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M3, Fcomplex16, "__model_data_nmssmeft_MOD_m3", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(M3IN, Fcomplex16, "__model_data_nmssmeft_MOD_m3in", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(InputValueforM3, Flogical, "__model_data_nmssmeft_MOD_inputvalueform3", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vdMZ, Freal8, "__model_data_nmssmeft_MOD_vdmz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vuMZ, Freal8, "__model_data_nmssmeft_MOD_vumz", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(vSMZ, Freal8, "__model_data_nmssmeft_MOD_vsmz", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(vSM, Freal8, "__sphenonmssm_MOD_vsm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(g1SM, Freal8, "__sphenonmssm_MOD_g1sm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(g2SM, Freal8, "__sphenonmssm_MOD_g2sm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(g3SM, Freal8, "__sphenonmssm_MOD_g3sm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g1GUT, Freal8, "__model_data_nmssmeft_MOD_g1gut", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g2GUT, Freal8, "__model_data_nmssmeft_MOD_g2gut", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(g3GUT, Freal8, "__model_data_nmssmeft_MOD_g3gut", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(YuSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yusm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(YdSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_ydsm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(YeSM, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yesm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Yd_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yd_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Yu_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_yu_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Td_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_td_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Tu_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_tu_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(mq2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mq2_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(md2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_md2_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(mu2_ckm, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mu2_ckm", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Td_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_td_out", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(Tu_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_tu_out", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(mq2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mq2_out", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(md2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_md2_out", "SARAHPhenoNMSSMEFT_internal")
//BE_VARIABLE(mu2_out, Farray_Fcomplex16_1_3_1_3, "__sphenonmssm_MOD_mu2_out", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(OneLoopMatching, Flogical, "__model_data_nmssmeft_MOD_oneloopmatching", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(TwoLoopMatching, Flogical, "__model_data_nmssmeft_MOD_twoloopmatching", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(GuessTwoLoopMatchingBSM, Flogical, "__model_data_nmssmeft_MOD_guesstwoloopmatchingbsm", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mass_uncertainty_Yt, Farray_Freal8_1_46, "__model_data_nmssmeft_MOD_mass_uncertainty_yt", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mass_uncertainty_Q, Farray_Freal8_1_46, "__model_data_nmssmeft_MOD_mass_uncertainty_q", "SARAHPhenoNMSSMEFT_internal")
// Control Variables
BE_VARIABLE(kont, Finteger, "__sphenonmssm_MOD_kont", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(WriteOut, Flogical, "__control_MOD_writeout", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(epsI, Freal8, "__sphenonmssm_MOD_epsi", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(deltaM, Freal8, "__sphenonmssm_MOD_deltam", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(mGUT, Freal8, "__sphenonmssm_MOD_mgut", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ErrCan, Finteger, "__control_MOD_errcan", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(FoundIterativeSolution, Flogical, "__settings_MOD_founditerativesolution", "SARAHPhenoNMSSMEFT_internal")
// Other variables
BE_VARIABLE(Qin, Freal8, "__sphenonmssm_MOD_qin", "SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(ratioWoM, Freal8, "__sphenonmssm_MOD_ratiowom","SARAHPhenoNMSSMEFT_internal")
BE_VARIABLE(CalcTBD, Flogical, "__sphenonmssm_MOD_calctbd","SARAHPhenoNMSSMEFT_internal")
// Branching Ratio variables


// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SARAHSPheno_NMSSMEFTspectrum")
BE_CONV_FUNCTION(run_SPheno_decays, int, (const Spectrum &, DecayTable &), "SARAHSPheno_NMSSMEFTdecays")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const std::map<str, safe_ptr<double> >&), "SARAHPhenoNMSSMEFT_internal")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SARAHPhenoNMSSMEFT_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SARAHPhenoNMSSMEFT_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SARAHPhenoNMSSMEFT_internal")

// Initialisation functions (dependencies)


// End
#include "gambit/Backends/backend_undefs.hpp"
