//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Frontend header for SARAH-SPheno 4.0.3 backend,
/// for the Inert model.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#define BACKENDNAME SARAHSPheno_Inert
#define BACKENDLANG FORTRAN
#define VERSION 4.0.3
#define SARAH_VERSION 4.14.0
#define SAFE_VERSION 4_0_3
#define REFERENCE Porod:2003um,Porod:2011nf
// Begin
LOAD_LIBRARY

// Allow for Inert only
BE_ALLOW_MODELS(Inert)

// Functions
BE_FUNCTION(SPheno_Main, void, (), ("__sphenoinert_MOD_spheno_main", "sphenoinert_mp_spheno_main_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(Set_All_Parameters_0, void, (), ("__model_data_inert_MOD_set_all_parameters_0", "model_data_inert_mp_set_all_parameters_0_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(SetRenormalizationScale, Freal8, (Freal8&), ("__loopfunctions_MOD_setrenormalizationscale", "loopfunctions_mp_setrenormalizationscale_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), ("__loopfunctions_MOD_initializeloopfunctions", "loopfunctions_mp_initializeloopfunctions_"), "SARAHSPheno_Inert_internal")
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
     ("__standardmodel_MOD_calculaterunningmasses", "standardmodel_mp_calculaterunningmasses_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), ("__loopfunctions_MOD_getrenormalizationscale", "loopfunctions_mp_getrenormalizationscale_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), ("__model_data_inert_MOD_setrgescale", "model_data_inert_mp_setrgescale_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(SetGUTScale, void, (Freal8&), ("__model_data_inert_MOD_setgutscale", "model_data_inert_mp_setgutscale_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), ("__model_data_inert_MOD_setstrictunification", "model_data_inert_mp_setstrictunification_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), ("__model_data_inert_MOD_setyukawascheme", "model_data_inert_mp_setyukawascheme_"), "SARAHSPheno_Inert_internal")

// Model-dependent arguments auto-scraped by GUM
BE_FUNCTION(CalculateBR_2, void,
  (Flogical&, // CTBD
   Freal8&, // fac3
   Freal8&, // epsI
   Freal8&, // deltaM
   Finteger&, // kont
   Freal8&, // MA0
   Freal8&, // MA02
   Farray_Freal8_1_3&, // MFd
   Farray_Freal8_1_3&, // MFd2
   Farray_Freal8_1_3&, // MFe
   Farray_Freal8_1_3&, // MFe2
   Farray_Freal8_1_3&, // MFu
   Farray_Freal8_1_3&, // MFu2
   Freal8&, // MG0
   Freal8&, // MG02
   Freal8&, // MH0
   Freal8&, // MH02
   Freal8&, // Mhh
   Freal8&, // Mhh2
   Farray_Freal8_1_2&, // MHp
   Farray_Freal8_1_2&, // MHp2
   Freal8&, // MVWp
   Freal8&, // MVWp2
   Freal8&, // MVZ
   Freal8&, // MVZ2
   Freal8&, // TW
   Farray_Fcomplex16_1_3_1_3&, // ZDL
   Farray_Fcomplex16_1_3_1_3&, // ZDR
   Farray_Fcomplex16_1_3_1_3&, // ZEL
   Farray_Fcomplex16_1_3_1_3&, // ZER
   Farray_Freal8_1_2_1_2&, // ZP
   Farray_Fcomplex16_1_3_1_3&, // ZUL
   Farray_Fcomplex16_1_3_1_3&, // ZUR
   Farray_Fcomplex16_1_2_1_2&, // ZW
   Farray_Freal8_1_2_1_2&, // ZZ
   Freal8&, // betaH
   Freal8&, // v
   Freal8&, // g1
   Freal8&, // g2
   Freal8&, // g3
   Fcomplex16&, // Lam5
   Fcomplex16&, // Lam1
   Fcomplex16&, // Lam4
   Fcomplex16&, // Lam3
   Fcomplex16&, // Lam2
   Farray_Fcomplex16_1_3_1_3&, // Ye
   Farray_Fcomplex16_1_3_1_3&, // Yd
   Farray_Fcomplex16_1_3_1_3&, // Yu
   Freal8&, // mHd2
   Freal8&, // mHu2
   Farray_Freal8_1_3_1_159&, // gPFu
   Farray_Freal8_1_3&, // gTFu
   Farray_Freal8_1_3_1_159&, // BRFu
   Farray_Freal8_1_3_1_156&, // gPFe
   Farray_Freal8_1_3&, // gTFe
   Farray_Freal8_1_3_1_156&, // BRFe
   Farray_Freal8_1_3_1_159&, // gPFd
   Farray_Freal8_1_3&, // gTFd
   Farray_Freal8_1_3_1_159&, // BRFd
   Farray_Freal8_1_1_1_59&, // gPhh
   Freal8&, // gThh
   Farray_Freal8_1_1_1_59&, // BRhh
   Farray_Freal8_1_1_1_54&, // gPH0
   Freal8&, // gTH0
   Farray_Freal8_1_1_1_54&, // BRH0
   Farray_Freal8_1_1_1_54&, // gPA0
   Freal8&, // gTA0
   Farray_Freal8_1_1_1_54&, // BRA0
   Farray_Freal8_1_2_1_28&, // gPHp
   Farray_Freal8_1_2&, // gTHp
   Farray_Freal8_1_2_1_28& // BRHp
), ("__branchingratios_inert_MOD_calculatebr_2", "branchingratios_inert_mp_calculatebr_2_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(Switch_to_superCKM, void,
  (Farray_Fcomplex16_1_3_1_3&, // Y_d
   Farray_Fcomplex16_1_3_1_3&, // Y_u
   Farray_Fcomplex16_1_3_1_3&, // Ad_in
   Farray_Fcomplex16_1_3_1_3&, // Au_in
   Farray_Fcomplex16_1_3_1_3&, // MD_in
   Farray_Fcomplex16_1_3_1_3&, // MQ_in
   Farray_Fcomplex16_1_3_1_3&, // MU_in
   Farray_Fcomplex16_1_3_1_3&, // Ad_out
   Farray_Fcomplex16_1_3_1_3&, // Au_out
   Farray_Fcomplex16_1_3_1_3&, // MD_out
   Farray_Fcomplex16_1_3_1_3&, // MQ_out
   Farray_Fcomplex16_1_3_1_3&, // MU_out
   Flogical&, // tr
   Farray_Fcomplex16_1_6_1_6&, // RSd_in
   Farray_Fcomplex16_1_6_1_6&, // RSu_in
   Farray_Fcomplex16_1_6_1_6&, // RSd_out
   Farray_Fcomplex16_1_6_1_6&, // RSu_out
   Farray_Fcomplex16_1_3_1_3&, // CKM_out
   Farray_Fcomplex16_1_3_1_3&, // Yd_out
   Farray_Fcomplex16_1_3_1_3& // Yu_out
), ("__inputoutput_inert_MOD_switch_to_superckm", "inputoutput_inert_mp_switch_to_superckm_"), "SARAHSPheno_Inert_internal")
BE_FUNCTION(Switch_to_superPMNS, void,
  (Farray_Fcomplex16_1_3_1_3&, // Y_l
   Farray_Fcomplex16_1_3_1_3&, // uN_L
   Farray_Fcomplex16_1_3_1_3&, // Al_in
   Farray_Fcomplex16_1_3_1_3&, // ME_in
   Farray_Fcomplex16_1_3_1_3&, // ML_in
   Farray_Fcomplex16_1_3_1_3&, // Al_out
   Farray_Fcomplex16_1_3_1_3&, // ME_out
   Farray_Fcomplex16_1_3_1_3&, // ML_out
   Flogical&, // tr
   Farray_Fcomplex16_1_6_1_6&, // RSl_in
   Farray_Fcomplex16_1_3_1_3&, // RSn_in
   Farray_Fcomplex16_1_6_1_6&, // RSl_out
   Farray_Fcomplex16_1_3_1_3&, // RSn_out
   Farray_Fcomplex16_1_3_1_3&, // PMNS_out
   Farray_Fcomplex16_1_3_1_3& // Yl
), ("__inputoutput_inert_MOD_switch_to_superpmns", "inputoutput_inert_mp_switch_to_superpmns_"), "SARAHSPheno_Inert_internal")

// Model-dependent variables
BE_VARIABLE(BoundaryCondition, Finteger, ("__model_data_inert_MOD_boundarycondition", "model_data_inert_mp_boundarycondition_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CS_Higgs_LHC, Farray_Freal8_1_5_1_1_1_5, ("__model_data_inert_MOD_cs_higgs_lhc", "model_data_inert_mp_cs_higgs_lhc_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcFT, Flogical, ("__model_data_inert_MOD_calcft", "model_data_inert_mp_calcft_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CheckSugraDetails, Farray_Flogical_1_10, ("__model_data_inert_MOD_checksugradetails", "model_data_inert_mp_checksugradetails_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CoupAGG, Fcomplex16, ("__model_data_inert_MOD_coupagg", "model_data_inert_mp_coupagg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CoupAPP, Fcomplex16, ("__model_data_inert_MOD_coupapp", "model_data_inert_mp_coupapp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CoupHGG, Fcomplex16, ("__model_data_inert_MOD_couphgg", "model_data_inert_mp_couphgg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CoupHPP, Fcomplex16, ("__model_data_inert_MOD_couphpp", "model_data_inert_mp_couphpp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(FineTuningResults, void, ("__model_data_inert_MOD_finetuningresults", "model_data_inert_mp_finetuningresults_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(FineTuningResultsAllVEVs, void, ("__model_data_inert_MOD_finetuningresultsallvevs", "model_data_inert_mp_finetuningresultsallvevs_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(GUT_scale, Freal8, ("__model_data_inert_MOD_gut_scale", "model_data_inert_mp_gut_scale_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(GetMassUncertainty, Flogical, ("__model_data_inert_MOD_getmassuncertainty", "model_data_inert_mp_getmassuncertainty_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(GuessTwoLoopMatchingBSM, Flogical, ("__model_data_inert_MOD_guesstwoloopmatchingbsm", "model_data_inert_mp_guesstwoloopmatchingbsm_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HPPloopFd, Farray_Freal8_1_3, ("__model_data_inert_MOD_hpploopfd", "model_data_inert_mp_hpploopfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HPPloopFe, Farray_Freal8_1_3, ("__model_data_inert_MOD_hpploopfe", "model_data_inert_mp_hpploopfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HPPloopFu, Farray_Freal8_1_3, ("__model_data_inert_MOD_hpploopfu", "model_data_inert_mp_hpploopfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HPPloopHp, Farray_Freal8_1_2, ("__model_data_inert_MOD_hpploophp", "model_data_inert_mp_hpploophp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HPPloopVWp, Freal8, ("__model_data_inert_MOD_hpploopvwp", "model_data_inert_mp_hpploopvwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(IgnoreMuSignFlip, Flogical, ("__model_data_inert_MOD_ignoremusignflip", "model_data_inert_mp_ignoremusignflip_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(IgnoreNegativeMasses, Flogical, ("__model_data_inert_MOD_ignorenegativemasses", "model_data_inert_mp_ignorenegativemasses_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(IgnoreNegativeMassesMZ, Flogical, ("__model_data_inert_MOD_ignorenegativemassesmz", "model_data_inert_mp_ignorenegativemassesmz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforLam1, Flogical, ("__model_data_inert_MOD_inputvalueforlam1", "model_data_inert_mp_inputvalueforlam1_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforLam2, Flogical, ("__model_data_inert_MOD_inputvalueforlam2", "model_data_inert_mp_inputvalueforlam2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforLam3, Flogical, ("__model_data_inert_MOD_inputvalueforlam3", "model_data_inert_mp_inputvalueforlam3_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforLam4, Flogical, ("__model_data_inert_MOD_inputvalueforlam4", "model_data_inert_mp_inputvalueforlam4_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforLam5, Flogical, ("__model_data_inert_MOD_inputvalueforlam5", "model_data_inert_mp_inputvalueforlam5_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforYd, Flogical, ("__model_data_inert_MOD_inputvalueforyd", "model_data_inert_mp_inputvalueforyd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforYe, Flogical, ("__model_data_inert_MOD_inputvalueforye", "model_data_inert_mp_inputvalueforye_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforYu, Flogical, ("__model_data_inert_MOD_inputvalueforyu", "model_data_inert_mp_inputvalueforyu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforg1, Flogical, ("__model_data_inert_MOD_inputvalueforg1", "model_data_inert_mp_inputvalueforg1_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforg2, Flogical, ("__model_data_inert_MOD_inputvalueforg2", "model_data_inert_mp_inputvalueforg2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueforg3, Flogical, ("__model_data_inert_MOD_inputvalueforg3", "model_data_inert_mp_inputvalueforg3_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueformHd2, Flogical, ("__model_data_inert_MOD_inputvalueformhd2", "model_data_inert_mp_inputvalueformhd2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(InputValueformHu2, Flogical, ("__model_data_inert_MOD_inputvalueformhu2", "model_data_inert_mp_inputvalueformhu2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(KineticMixing, Flogical, ("__model_data_inert_MOD_kineticmixing", "model_data_inert_mp_kineticmixing_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(KineticMixingSave, Flogical, ("__model_data_inert_MOD_kineticmixingsave", "model_data_inert_mp_kineticmixingsave_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam1, Fcomplex16, ("__model_data_inert_MOD_lam1", "model_data_inert_mp_lam1_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam1GUT, Fcomplex16, ("__model_data_inert_MOD_lam1gut", "model_data_inert_mp_lam1gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam1IN, Fcomplex16, ("__model_data_inert_MOD_lam1in", "model_data_inert_mp_lam1in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam1MZ, Fcomplex16, ("__model_data_inert_MOD_lam1mz", "model_data_inert_mp_lam1mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam2, Fcomplex16, ("__model_data_inert_MOD_lam2", "model_data_inert_mp_lam2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam2GUT, Fcomplex16, ("__model_data_inert_MOD_lam2gut", "model_data_inert_mp_lam2gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam2IN, Fcomplex16, ("__model_data_inert_MOD_lam2in", "model_data_inert_mp_lam2in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam2MZ, Fcomplex16, ("__model_data_inert_MOD_lam2mz", "model_data_inert_mp_lam2mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam3, Fcomplex16, ("__model_data_inert_MOD_lam3", "model_data_inert_mp_lam3_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam3GUT, Fcomplex16, ("__model_data_inert_MOD_lam3gut", "model_data_inert_mp_lam3gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam3IN, Fcomplex16, ("__model_data_inert_MOD_lam3in", "model_data_inert_mp_lam3in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam3MZ, Fcomplex16, ("__model_data_inert_MOD_lam3mz", "model_data_inert_mp_lam3mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam4, Fcomplex16, ("__model_data_inert_MOD_lam4", "model_data_inert_mp_lam4_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam4GUT, Fcomplex16, ("__model_data_inert_MOD_lam4gut", "model_data_inert_mp_lam4gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam4IN, Fcomplex16, ("__model_data_inert_MOD_lam4in", "model_data_inert_mp_lam4in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam4MZ, Fcomplex16, ("__model_data_inert_MOD_lam4mz", "model_data_inert_mp_lam4mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam5, Fcomplex16, ("__model_data_inert_MOD_lam5", "model_data_inert_mp_lam5_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam5GUT, Fcomplex16, ("__model_data_inert_MOD_lam5gut", "model_data_inert_mp_lam5gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam5IN, Fcomplex16, ("__model_data_inert_MOD_lam5in", "model_data_inert_mp_lam5in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lam5MZ, Fcomplex16, ("__model_data_inert_MOD_lam5mz", "model_data_inert_mp_lam5mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lambda1IN, Fcomplex16, ("__model_data_inert_MOD_lambda1in", "model_data_inert_mp_lambda1in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lambda2IN, Fcomplex16, ("__model_data_inert_MOD_lambda2in", "model_data_inert_mp_lambda2in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lambda3IN, Fcomplex16, ("__model_data_inert_MOD_lambda3in", "model_data_inert_mp_lambda3in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lambda4IN, Fcomplex16, ("__model_data_inert_MOD_lambda4in", "model_data_inert_mp_lambda4in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Lambda5IN, Fcomplex16, ("__model_data_inert_MOD_lambda5in", "model_data_inert_mp_lambda5in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MA0, Freal8, ("__model_data_inert_MOD_ma0", "model_data_inert_mp_ma0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MA02, Freal8, ("__model_data_inert_MOD_ma02", "model_data_inert_mp_ma02_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MAh2L, Freal8, ("__model_data_inert_MOD_mah2l", "model_data_inert_mp_mah2l_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MAh2_s, Freal8, ("__model_data_inert_MOD_mah2_s", "model_data_inert_mp_mah2_s_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MAhL, Freal8, ("__model_data_inert_MOD_mahl", "model_data_inert_mp_mahl_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MAh_s, Freal8, ("__model_data_inert_MOD_mah_s", "model_data_inert_mp_mah_s_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFd, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfd", "model_data_inert_mp_mfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFd2, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfd2", "model_data_inert_mp_mfd2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFe, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfe", "model_data_inert_mp_mfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFe2, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfe2", "model_data_inert_mp_mfe2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFu, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfu", "model_data_inert_mp_mfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MFu2, Farray_Freal8_1_3, ("__model_data_inert_MOD_mfu2", "model_data_inert_mp_mfu2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MG0, Freal8, ("__model_data_inert_MOD_mg0", "model_data_inert_mp_mg0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MG02, Freal8, ("__model_data_inert_MOD_mg02", "model_data_inert_mp_mg02_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MH0, Freal8, ("__model_data_inert_MOD_mh0", "model_data_inert_mp_mh0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MH02, Freal8, ("__model_data_inert_MOD_mh02", "model_data_inert_mp_mh02_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MHp, Farray_Freal8_1_2, ("__model_data_inert_MOD_mhp", "model_data_inert_mp_mhp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MHp2, Farray_Freal8_1_2, ("__model_data_inert_MOD_mhp2", "model_data_inert_mp_mhp2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MVWp, Freal8, ("__model_data_inert_MOD_mvwp", "model_data_inert_mp_mvwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MVWp2, Freal8, ("__model_data_inert_MOD_mvwp2", "model_data_inert_mp_mvwp2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MVZ, Freal8, ("__model_data_inert_MOD_mvz", "model_data_inert_mp_mvz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MVZ2, Freal8, ("__model_data_inert_MOD_mvz2", "model_data_inert_mp_mvz2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Mhh, Freal8, ("__model_data_inert_MOD_mhh", "model_data_inert_mp_mhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Mhh2, Freal8, ("__model_data_inert_MOD_mhh2", "model_data_inert_mp_mhh2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Mhh2L, Freal8, ("__model_data_inert_MOD_mhh2l", "model_data_inert_mp_mhh2l_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Mhh2_s, Freal8, ("__model_data_inert_MOD_mhh2_s", "model_data_inert_mp_mhh2_s_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(MhhL, Freal8, ("__model_data_inert_MOD_mhhl", "model_data_inert_mp_mhhl_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Mhh_s, Freal8, ("__model_data_inert_MOD_mhh_s", "model_data_inert_mp_mhh_s_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(OneLoopFT, Flogical, ("__model_data_inert_MOD_oneloopft", "model_data_inert_mp_oneloopft_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(OneLoopMatching, Flogical, ("__model_data_inert_MOD_oneloopmatching", "model_data_inert_mp_oneloopmatching_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RXiG, Freal8, ("__model_data_inert_MOD_rxig", "model_data_inert_mp_rxig_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RXiP, Freal8, ("__model_data_inert_MOD_rxip", "model_data_inert_mp_rxip_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RXiWp, Freal8, ("__model_data_inert_MOD_rxiwp", "model_data_inert_mp_rxiwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RXiZ, Freal8, ("__model_data_inert_MOD_rxiz", "model_data_inert_mp_rxiz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RotateNegativeFermionMasses, Flogical, ("__model_data_inert_MOD_rotatenegativefermionmasses", "model_data_inert_mp_rotatenegativefermionmasses_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(RunRGEs_unitarity, Flogical, ("__model_data_inert_MOD_runrges_unitarity", "model_data_inert_mp_runrges_unitarity_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(SolutionTadpoleNr, Finteger, ("__model_data_inert_MOD_solutiontadpolenr", "model_data_inert_mp_solutiontadpolenr_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(StrictUnification, Flogical, ("__model_data_inert_MOD_strictunification", "model_data_inert_mp_strictunification_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(SugraErrors, Farray_Flogical_1_10, ("__model_data_inert_MOD_sugraerrors", "model_data_inert_mp_sugraerrors_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TUcutLevel, Finteger, ("__model_data_inert_MOD_tucutlevel", "model_data_inert_mp_tucutlevel_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TW, Freal8, ("__model_data_inert_MOD_tw", "model_data_inert_mp_tw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TransposedYukawa, Flogical, ("__model_data_inert_MOD_transposedyukawa", "model_data_inert_mp_transposedyukawa_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TreeLevelUnitarityLimits, Flogical, ("__model_data_inert_MOD_treelevelunitaritylimits", "model_data_inert_mp_treelevelunitaritylimits_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TrilinearUnitarity, Flogical, ("__model_data_inert_MOD_trilinearunitarity", "model_data_inert_mp_trilinearunitarity_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopMatching, Flogical, ("__model_data_inert_MOD_twoloopmatching", "model_data_inert_mp_twoloopmatching_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(UseFixedGUTScale, Flogical, ("__model_data_inert_MOD_usefixedgutscale", "model_data_inert_mp_usefixedgutscale_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(UseFixedScale, Flogical, ("__model_data_inert_MOD_usefixedscale", "model_data_inert_mp_usefixedscale_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteEffHiggsCouplingRatios, Flogical, ("__model_data_inert_MOD_writeeffhiggscouplingratios", "model_data_inert_mp_writeeffhiggscouplingratios_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteHiggsDiphotonLoopContributions, Flogical, ("__model_data_inert_MOD_writehiggsdiphotonloopcontributions", "model_data_inert_mp_writehiggsdiphotonloopcontributions_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteTreeLevelTadpoleSolutions, Flogical, ("__model_data_inert_MOD_writetreeleveltadpolesolutions", "model_data_inert_mp_writetreeleveltadpolesolutions_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Write_WHIZARD, Flogical, ("__model_data_inert_MOD_write_whizard", "model_data_inert_mp_write_whizard_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_d, Fcomplex16, ("__model_data_inert_MOD_y_d", "model_data_inert_mp_y_d_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_d_0, Fcomplex16, ("__model_data_inert_MOD_y_d_0", "model_data_inert_mp_y_d_0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_d_mZ, Fcomplex16, ("__model_data_inert_MOD_y_d_mz", "model_data_inert_mp_y_d_mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_l, Fcomplex16, ("__model_data_inert_MOD_y_l", "model_data_inert_mp_y_l_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_l_0, Fcomplex16, ("__model_data_inert_MOD_y_l_0", "model_data_inert_mp_y_l_0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_l_mZ, Fcomplex16, ("__model_data_inert_MOD_y_l_mz", "model_data_inert_mp_y_l_mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_u, Fcomplex16, ("__model_data_inert_MOD_y_u", "model_data_inert_mp_y_u_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_u_0, Fcomplex16, ("__model_data_inert_MOD_y_u_0", "model_data_inert_mp_y_u_0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Y_u_mZ , Fcomplex16, ("__model_data_inert_MOD_y_u_mz ", "model_data_inert_mp_y_u_mz _"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Yd, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yd", "model_data_inert_mp_yd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YdGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_ydgut", "model_data_inert_mp_ydgut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YdIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_ydin", "model_data_inert_mp_ydin_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YdMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_ydmz", "model_data_inert_mp_ydmz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Yd_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yd_saveep", "model_data_inert_mp_yd_saveep_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Ye, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_ye", "model_data_inert_mp_ye_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YeGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yegut", "model_data_inert_mp_yegut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YeIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yein", "model_data_inert_mp_yein_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YeMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yemz", "model_data_inert_mp_yemz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Ye_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_ye_saveep", "model_data_inert_mp_ye_saveep_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Yu, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yu", "model_data_inert_mp_yu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YuGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yugut", "model_data_inert_mp_yugut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YuIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yuin", "model_data_inert_mp_yuin_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YuMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yumz", "model_data_inert_mp_yumz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(Yu_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_yu_saveep", "model_data_inert_mp_yu_saveep_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(YukawaScheme, Finteger, ("__model_data_inert_MOD_yukawascheme", "model_data_inert_mp_yukawascheme_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZDL, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zdl", "model_data_inert_mp_zdl_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZDR, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zdr", "model_data_inert_mp_zdr_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZEL, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zel", "model_data_inert_mp_zel_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZER, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zer", "model_data_inert_mp_zer_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZP, Farray_Freal8_1_2_1_2, ("__model_data_inert_MOD_zp", "model_data_inert_mp_zp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZUL, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zul", "model_data_inert_mp_zul_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZUR, Farray_Fcomplex16_1_3_1_3, ("__model_data_inert_MOD_zur", "model_data_inert_mp_zur_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZW, Farray_Fcomplex16_1_2_1_2, ("__model_data_inert_MOD_zw", "model_data_inert_mp_zw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ZZ, Farray_Freal8_1_2_1_2, ("__model_data_inert_MOD_zz", "model_data_inert_mp_zz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(betaH, Freal8, ("__model_data_inert_MOD_betah", "model_data_inert_mp_betah_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g1, Freal8, ("__model_data_inert_MOD_g1", "model_data_inert_mp_g1_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g1GUT, Freal8, ("__model_data_inert_MOD_g1gut", "model_data_inert_mp_g1gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g1IN, Freal8, ("__model_data_inert_MOD_g1in", "model_data_inert_mp_g1in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g1MZ, Freal8, ("__model_data_inert_MOD_g1mz", "model_data_inert_mp_g1mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g1_saveEP, Freal8, ("__model_data_inert_MOD_g1_saveep", "model_data_inert_mp_g1_saveep_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g2, Freal8, ("__model_data_inert_MOD_g2", "model_data_inert_mp_g2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g2GUT, Freal8, ("__model_data_inert_MOD_g2gut", "model_data_inert_mp_g2gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g2IN, Freal8, ("__model_data_inert_MOD_g2in", "model_data_inert_mp_g2in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g2MZ, Freal8, ("__model_data_inert_MOD_g2mz", "model_data_inert_mp_g2mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g2_saveEP, Freal8, ("__model_data_inert_MOD_g2_saveep", "model_data_inert_mp_g2_saveep_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g3, Freal8, ("__model_data_inert_MOD_g3", "model_data_inert_mp_g3_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g3GUT, Freal8, ("__model_data_inert_MOD_g3gut", "model_data_inert_mp_g3gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g3IN, Freal8, ("__model_data_inert_MOD_g3in", "model_data_inert_mp_g3in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g3MZ, Freal8, ("__model_data_inert_MOD_g3mz", "model_data_inert_mp_g3mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g3running, Freal8, ("__model_data_inert_MOD_g3running", "model_data_inert_mp_g3running_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gForTadpoles, Farray_Freal8_1_70, ("__model_data_inert_MOD_gfortadpoles", "model_data_inert_mp_gfortadpoles_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LA0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_gp1la0", "model_data_inert_mp_gp1la0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LFd, Farray_Freal8_1_3_1_24, ("__model_data_inert_MOD_gp1lfd", "model_data_inert_mp_gp1lfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LFe, Farray_Freal8_1_3_1_21, ("__model_data_inert_MOD_gp1lfe", "model_data_inert_mp_gp1lfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LFu, Farray_Freal8_1_3_1_24, ("__model_data_inert_MOD_gp1lfu", "model_data_inert_mp_gp1lfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LH0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_gp1lh0", "model_data_inert_mp_gp1lh0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1LHp, Farray_Freal8_1_2_1_28, ("__model_data_inert_MOD_gp1lhp", "model_data_inert_mp_gp1lhp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gP1Lhh, Farray_Freal8_1_1_1_59, ("__model_data_inert_MOD_gp1lhh", "model_data_inert_mp_gp1lhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPA0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_gpa0", "model_data_inert_mp_gpa0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPFd, Farray_Freal8_1_3_1_159, ("__model_data_inert_MOD_gpfd", "model_data_inert_mp_gpfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPFe, Farray_Freal8_1_3_1_156, ("__model_data_inert_MOD_gpfe", "model_data_inert_mp_gpfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPFu, Farray_Freal8_1_3_1_159, ("__model_data_inert_MOD_gpfu", "model_data_inert_mp_gpfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPH0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_gph0", "model_data_inert_mp_gph0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPHp, Farray_Freal8_1_2_1_28, ("__model_data_inert_MOD_gphp", "model_data_inert_mp_gphp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gPhh, Farray_Freal8_1_1_1_59, ("__model_data_inert_MOD_gphh", "model_data_inert_mp_gphh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(g_SM_save, Farray_Freal8_1_62, ("__model_data_inert_MOD_g_sm_save", "model_data_inert_mp_g_sm_save_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gauge, Freal8, ("__model_data_inert_MOD_gauge", "model_data_inert_mp_gauge_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gauge_0, Freal8, ("__model_data_inert_MOD_gauge_0", "model_data_inert_mp_gauge_0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gauge_mZ, Freal8, ("__model_data_inert_MOD_gauge_mz", "model_data_inert_mp_gauge_mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(m32, Freal8, ("__model_data_inert_MOD_m32", "model_data_inert_mp_m32_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHd2, Freal8, ("__model_data_inert_MOD_mhd2", "model_data_inert_mp_mhd2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHd2GUT, Freal8, ("__model_data_inert_MOD_mhd2gut", "model_data_inert_mp_mhd2gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHd2IN, Freal8, ("__model_data_inert_MOD_mhd2in", "model_data_inert_mp_mhd2in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHd2MZ, Freal8, ("__model_data_inert_MOD_mhd2mz", "model_data_inert_mp_mhd2mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHu2, Freal8, ("__model_data_inert_MOD_mhu2", "model_data_inert_mp_mhu2_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHu2GUT, Freal8, ("__model_data_inert_MOD_mhu2gut", "model_data_inert_mp_mhu2gut_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHu2IN, Freal8, ("__model_data_inert_MOD_mhu2in", "model_data_inert_mp_mhu2in_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mHu2MZ, Freal8, ("__model_data_inert_MOD_mhu2mz", "model_data_inert_mp_mhu2mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mass_uncertainty_Q, Farray_Freal8_1_15, ("__model_data_inert_MOD_mass_uncertainty_q", "model_data_inert_mp_mass_uncertainty_q_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(mass_uncertainty_Yt, Farray_Freal8_1_15, ("__model_data_inert_MOD_mass_uncertainty_yt", "model_data_inert_mp_mass_uncertainty_yt_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioFd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiofd", "model_data_inert_mp_ratiofd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioFe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiofe", "model_data_inert_mp_ratiofe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioFu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiofu", "model_data_inert_mp_ratiofu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioHp, Farray_Freal8_1_1_1_2, ("__model_data_inert_MOD_ratiohp", "model_data_inert_mp_ratiohp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioVWp, Freal8, ("__model_data_inert_MOD_ratiovwp", "model_data_inert_mp_ratiovwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(tForTadpoles, Farray_Fcomplex16_1_2, ("__model_data_inert_MOD_tfortadpoles", "model_data_inert_mp_tfortadpoles_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(tanb, Freal8, ("__model_data_inert_MOD_tanb", "model_data_inert_mp_tanb_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(tanb_mZ, Freal8, ("__model_data_inert_MOD_tanb_mz", "model_data_inert_mp_tanb_mz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(tanbetaMZ, Freal8, ("__model_data_inert_MOD_tanbetamz", "model_data_inert_mp_tanbetamz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(temporaryValue, Fcomplex16, ("__model_data_inert_MOD_temporaryvalue", "model_data_inert_mp_temporaryvalue_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(unitarity_s_best, Freal8, ("__model_data_inert_MOD_unitarity_s_best", "model_data_inert_mp_unitarity_s_best_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(unitarity_s_max, Freal8, ("__model_data_inert_MOD_unitarity_s_max", "model_data_inert_mp_unitarity_s_max_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(unitarity_s_min, Freal8, ("__model_data_inert_MOD_unitarity_s_min", "model_data_inert_mp_unitarity_s_min_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(unitarity_steps, Finteger, ("__model_data_inert_MOD_unitarity_steps", "model_data_inert_mp_unitarity_steps_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(v, Freal8, ("__model_data_inert_MOD_v", "model_data_inert_mp_v_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vFix, Freal8, ("__model_data_inert_MOD_vfix", "model_data_inert_mp_vfix_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vIN, Freal8, ("__model_data_inert_MOD_vin", "model_data_inert_mp_vin_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vMZ, Freal8, ("__model_data_inert_MOD_vmz", "model_data_inert_mp_vmz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vSM_Q, Freal8, ("__model_data_inert_MOD_vsm_q", "model_data_inert_mp_vsm_q_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vSUSY, Freal8, ("__model_data_inert_MOD_vsusy", "model_data_inert_mp_vsusy_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(vevSM, Farray_Freal8_1_2, ("__model_data_inert_MOD_vevsm", "model_data_inert_mp_vevsm_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(HighScaleModel, Fstring<15>, ("__settings_MOD_highscalemodel", "settings_mp_highscalemodel_"), "SARAHSPheno_Inert_internal")

// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, ("__standardmodel_MOD_mz", "standardmodel_mp_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mZ2, Freal8,  ("__standardmodel_MOD_mz2", "standardmodel_mp_mz2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gamZ, Freal8, ("__standardmodel_MOD_gamz", "standardmodel_mp_gamz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gamZ2, Freal8, ("__standardmodel_MOD_gamz2", "standardmodel_mp_gamz2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gmZ, Freal8, ("__standardmodel_MOD_gmz", "standardmodel_mp_gmz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gmZ2, Freal8, ("__standardmodel_MOD_gmz2", "standardmodel_mp_gmz2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, ("__standardmodel_MOD_brzqq", "standardmodel_mp_brzqq_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, ("__standardmodel_MOD_brzll", "standardmodel_mp_brzll_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BrZinv, Freal8, ("__standardmodel_MOD_brzinv", "standardmodel_mp_brzinv_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mW, Freal8, ("__standardmodel_MOD_mw", "standardmodel_mp_mw_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mW_SM, Freal8, ("__model_data_inert_MOD_mw_sm", "model_data_inert_mp_mw_sm_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mW2, Freal8, ("__standardmodel_MOD_mw2", "standardmodel_mp_mw2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gamW, Freal8, ("__standardmodel_MOD_gamw", "standardmodel_mp_gamw_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gamW2, Freal8, ("__standardmodel_MOD_gamw2", "standardmodel_mp_gamw2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gmW, Freal8, ("__standardmodel_MOD_gmw", "standardmodel_mp_gmw_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(gmW2, Freal8, ("__standardmodel_MOD_gmw2", "standardmodel_mp_gmw2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, ("__standardmodel_MOD_brwqq", "standardmodel_mp_brwqq_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, ("__standardmodel_MOD_brwln", "standardmodel_mp_brwln_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l", "standardmodel_mp_mf_l_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l_mz", "standardmodel_mp_mf_l_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_nu", "standardmodel_mp_mf_nu_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u", "standardmodel_mp_mf_u_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u_mz", "standardmodel_mp_mf_u_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d", "standardmodel_mp_mf_d_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d_mz", "standardmodel_mp_mf_d_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l2", "standardmodel_mp_mf_l2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u2", "standardmodel_mp_mf_u2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d2", "standardmodel_mp_mf_d2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(sinW2, Freal8, ("__sphenoinert_MOD_sinw2", "sphenoinert_mp_sinw2_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MNuR, Freal8, ("__model_data_MOD_mnur", "model_data_mp_mnur_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Q_light_quarks, Freal8, ("__standardmodel_MOD_q_light_quarks", "standardmodel_mp_q_light_quarks_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, ("__standardmodel_MOD_delta_alpha_lepton", "standardmodel_mp_delta_alpha_lepton_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, ("__standardmodel_MOD_delta_alpha_hadron", "standardmodel_mp_delta_alpha_hadron_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Alpha, Freal8, ("__standardmodel_MOD_alpha", "standardmodel_mp_alpha_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Alpha_mZ, Freal8, ("__standardmodel_MOD_alpha_mz", "standardmodel_mp_alpha_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, ("__standardmodel_MOD_alpha_mz_ms", "standardmodel_mp_alpha_mz_ms_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MZ_input, Flogical, ("__model_data_inert_MOD_mz_input", "model_data_inert_mp_mz_input_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, ("__standardmodel_MOD_alphas_mz", "standardmodel_mp_alphas_mz_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(G_F, Freal8, ("__standardmodel_MOD_g_f", "standardmodel_mp_g_f_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(KFactorLee, Freal8, ("__standardmodel_MOD_kfactorlee", "standardmodel_mp_kfactorlee_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, ("__standardmodel_MOD_ckm", "standardmodel_mp_ckm_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(lam_wolf, Freal8, ("__standardmodel_MOD_lam_wolf", "standardmodel_mp_lam_wolf_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(A_wolf, Freal8, ("__standardmodel_MOD_a_wolf", "standardmodel_mp_a_wolf_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(rho_wolf, Freal8, ("__standardmodel_MOD_rho_wolf", "standardmodel_mp_rho_wolf_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(eta_wolf, Freal8, ("__standardmodel_MOD_eta_wolf", "standardmodel_mp_eta_wolf_"), "SARAHSPheno_Inert_internal")

// Control Variables
BE_VARIABLE(CTBD, Flogical, ("__sphenoinert_MOD_calctbd", "sphenoinert_mp_calctbd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(epsI, Freal8, ("__sphenoinert_MOD_epsi", "sphenoinert_mp_epsi_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(deltaM, Freal8, ("__sphenoinert_MOD_deltam", "sphenoinert_mp_deltam_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(kont, Finteger, ("__sphenoinert_MOD_kont", "sphenoinert_mp_kont_"), "SARAHSPheno_Inert_internal")

// Settings
BE_VARIABLE(Calculate_mh_within_SM, Flogical, ("__settings_MOD_calculate_mh_within_sm", "settings_mp_calculate_mh_within_sm_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalculateLowEnergy, Flogical, ("__settings_MOD_calculatelowenergy", "settings_mp_calculatelowenergy_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalculateMSSM2Loop, Flogical, ("__settings_MOD_calculatemssm2loop", "settings_mp_calculatemssm2loop_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalculateOneLoopMasses, Flogical, ("__settings_MOD_calculateoneloopmasses", "settings_mp_calculateoneloopmasses_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalculateTwoLoopHiggsMasses, Flogical, ("__settings_MOD_calculatetwoloophiggsmasses", "settings_mp_calculatetwoloophiggsmasses_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(DecoupleAtRenScale, Flogical, ("__settings_MOD_decoupleatrenscale", "settings_mp_decoupleatrenscale_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(delta_mass, Freal8, ("__control_MOD_delta_mass", "control_mp_delta_mass_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ErrCan, Finteger, ("__control_MOD_errcan", "control_mp_errcan_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ErrorLevel, Finteger, ("__control_MOD_errorlevel", "control_mp_errorlevel_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(External_Higgs, Flogical, ("__control_MOD_external_higgs", "control_mp_external_higgs_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(External_Spectrum, Flogical, ("__control_MOD_external_spectrum", "control_mp_external_spectrum_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(FermionMassResummation, Flogical, ("__control_MOD_fermionmassresummation", "control_mp_fermionmassresummation_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Force_mh_within_SM, Flogical, ("__settings_MOD_force_mh_within_sm", "settings_mp_force_mh_within_sm_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ForceRealMatrices, Flogical, ("__settings_MOD_forcerealmatrices", "settings_mp_forcerealmatrices_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(FoundIterativeSolution, Flogical, ("__settings_MOD_founditerativesolution", "settings_mp_founditerativesolution_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(GaugelessLimit, Finteger, ("__settings_MOD_gaugelesslimit", "settings_mp_gaugelesslimit_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(GenerationMixing, Flogical, ("__control_MOD_generationmixing", "control_mp_generationmixing_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(HigherOrderDiboson, Flogical, ("__settings_MOD_higherorderdiboson", "settings_mp_higherorderdiboson_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(hstep_pn, Freal8, ("__settings_MOD_hstep_pn", "settings_mp_hstep_pn_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(hstep_sa, Freal8, ("__settings_MOD_hstep_sa", "settings_mp_hstep_sa_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Iname, Finteger, ("__control_MOD_iname", "control_mp_iname_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(include1l2lshift, Flogical, ("__settings_MOD_include1l2lshift", "settings_mp_include1l2lshift_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(IncludeBSMdeltaVB, Flogical, ("__settings_MOD_includebsmdeltavb", "settings_mp_includebsmdeltavb_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(IncludeDeltaVB, Flogical, ("__settings_MOD_includedeltavb", "settings_mp_includedeltavb_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(InOut_Error, Farray_Fstring60_1_15, ("__control_MOD_inout_error", "control_mp_inout_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(L_CS, Flogical, ("__control_MOD_l_cs", "control_mp_l_cs_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(LoopMass_Error, Farray_Fstring60_1_25, ("__control_MOD_loopmass_error", "control_mp_loopmass_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MatchingOrder, Finteger, ("__settings_MOD_matchingorder", "settings_mp_matchingorder_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MatchZWpoleMasses, Flogical, ("__settings_MOD_matchzwpolemasses", "settings_mp_matchzwpolemasses_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Math_Error, Farray_Fstring60_1_31, ("__control_MOD_math_error", "control_mp_math_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MathQP_Error, Farray_Fstring60_1_10, ("__control_MOD_mathqp_error", "control_mp_mathqp_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MaxMassLoop, Freal8, ("__settings_MOD_maxmassloop", "settings_mp_maxmassloop_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MaxMassNumericalZero, Freal8, ("__settings_MOD_maxmassnumericalzero", "settings_mp_maxmassnumericalzero_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(mGUT, Freal8, ("__sphenoinert_MOD_mgut", "sphenoinert_mp_mgut_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MinimalNumberIterations, Finteger, ("__settings_MOD_minimalnumberiterations", "settings_mp_minimalnumberiterations_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(n_run, Finteger, ("__control_MOD_n_run", "control_mp_n_run_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(NewGBC, Flogical, ("__settings_MOD_newgbc", "settings_mp_newgbc_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, ("__control_MOD_non_zero_exit", "control_mp_non_zero_exit_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(OutputForMG, Flogical, ("__settings_MOD_outputformg", "settings_mp_outputformg_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(OutputForMO, Flogical, ("__settings_MOD_outputformo", "settings_mp_outputformo_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(PoleMassesInLoops, Flogical, ("__settings_MOD_polemassesinloops", "settings_mp_polemassesinloops_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(PrintDebugInformation, Flogical, ("__settings_MOD_printdebuginformation", "settings_mp_printdebuginformation_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(PurelyNumericalEffPot, Flogical, ("__settings_MOD_purelynumericaleffpot", "settings_mp_purelynumericaleffpot_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(RunningSMparametersLowEnergy, Flogical, ("__settings_MOD_runningsmparameterslowenergy", "settings_mp_runningsmparameterslowenergy_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(RunningSUSYparametersLowEnergy, Flogical, ("__settings_MOD_runningsusyparameterslowenergy", "settings_mp_runningsusyparameterslowenergy_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(RXiNew, Freal8, ("__settings_MOD_rxinew", "settings_mp_rxinew_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SilenceOutput, Flogical, ("__control_MOD_silenceoutput", "control_mp_silenceoutput_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SM_Error, Farray_Fstring60_1_2, ("__control_MOD_sm_error", "control_mp_sm_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SPA_convention, Finteger, ("__settings_MOD_spa_convention", "settings_mp_spa_convention_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Sugra_Error, Farray_Fstring60_1_22, ("__control_MOD_sugra_error", "control_mp_sugra_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SusyM_Error, Farray_Fstring60_1_33, ("__control_MOD_susym_error", "control_mp_susym_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SwitchToSCKM, Flogical, ("__settings_MOD_switchtosckm", "settings_mp_switchtosckm_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopHiggs_Error, Farray_Fstring60_1_9, ("__control_MOD_twoloophiggs_error", "control_mp_twoloophiggs_error_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopMethod, Finteger, ("__settings_MOD_twoloopmethod", "settings_mp_twoloopmethod_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopRegulatorMass, Freal8, ("__settings_MOD_twoloopregulatormass", "settings_mp_twoloopregulatormass_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, ("__settings_MOD_twolooprge", "settings_mp_twolooprge_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(TwoLoopSafeMode, Flogical, ("__settings_MOD_twoloopsafemode", "settings_mp_twoloopsafemode_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WidthToBeInvisible, Freal8, ("__settings_MOD_widthtobeinvisible", "settings_mp_widthtobeinvisible_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Write_HiggsBounds, Flogical, ("__inputoutput_inert_MOD_write_higgsbounds", "inputoutput_inert_mp_write_higgsbounds_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Write_WCXF, Flogical, ("__settings_MOD_write_wcxf", "settings_mp_write_wcxf_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteGUTvalues, Flogical, ("__settings_MOD_writegutvalues", "settings_mp_writegutvalues_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteOut, Flogical, ("__control_MOD_writeout", "control_mp_writeout_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteOutputForNonConvergence, Flogical, ("__settings_MOD_writeoutputfornonconvergence", "settings_mp_writeoutputfornonconvergence_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteParametersAtQ, Flogical, ("__settings_MOD_writeparametersatq", "settings_mp_writeparametersatq_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteSLHA1, Flogical, ("__settings_MOD_writeslha1", "settings_mp_writeslha1_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(WriteTreeLevelTadpoleParameters, Flogical, ("__settings_MOD_writetreeleveltadpoleparameters", "settings_mp_writetreeleveltadpoleparameters_"), "SARAHSPheno_Inert_internal")


// Other variables
BE_VARIABLE(Qin, Freal8, ("__sphenoinert_MOD_qin", "sphenoinert_mp_qin_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioWoM, Freal8, ("__sphenoinert_MOD_ratiowom", "sphenoinert_mp_ratiowom_"),"SARAHSPheno_Inert_internal")

// Branching Ratio variables
BE_VARIABLE(L_BR, Flogical, ("__control_MOD_l_br", "control_mp_l_br_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Enable3BDecaysF, Flogical, ("__settings_MOD_enable3bdecaysf", "settings_mp_enable3bdecaysf_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Enable3BDecaysS, Flogical, ("__settings_MOD_enable3bdecayss", "settings_mp_enable3bdecayss_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(RunningCouplingsDecays, Flogical, ("__settings_MOD_runningcouplingsdecays", "settings_mp_runningcouplingsdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(MinWidth, Freal8, ("__settings_MOD_minwidth", "settings_mp_minwidth_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(OneLoopDecays, Flogical, ("__settings_MOD_oneloopdecays", "settings_mp_oneloopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LA0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_br1la0", "model_data_inert_mp_br1la0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LFd, Farray_Freal8_1_3_1_24, ("__model_data_inert_MOD_br1lfd", "model_data_inert_mp_br1lfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LFe, Farray_Freal8_1_3_1_21, ("__model_data_inert_MOD_br1lfe", "model_data_inert_mp_br1lfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LFu, Farray_Freal8_1_3_1_24, ("__model_data_inert_MOD_br1lfu", "model_data_inert_mp_br1lfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LH0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_br1lh0", "model_data_inert_mp_br1lh0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1LHp, Farray_Freal8_1_2_1_28, ("__model_data_inert_MOD_br1lhp", "model_data_inert_mp_br1lhp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR1Lhh, Farray_Freal8_1_1_1_59, ("__model_data_inert_MOD_br1lhh", "model_data_inert_mp_br1lhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRA0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_bra0", "model_data_inert_mp_bra0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAAA, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_braaa", "model_data_inert_mp_braaa_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAAAijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_braaaijk", "model_data_inert_mp_braaaijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAAZ, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_braaz", "model_data_inert_mp_braaz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAHAijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_brahaijk", "model_data_inert_mp_brahaijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAHH, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brahh", "model_data_inert_mp_brahh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAHHijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_brahhijk", "model_data_inert_mp_brahhijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAHZ, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brahz", "model_data_inert_mp_brahz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAHpW, Farray_Freal8_1_1_1_2, ("__model_data_inert_MOD_brahpw", "model_data_inert_mp_brahpw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRAll, Farray_Freal8_1_1_1_3_1_3, ("__model_data_inert_MOD_brall", "model_data_inert_mp_brall_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRFd, Farray_Freal8_1_3_1_159, ("__model_data_inert_MOD_brfd", "model_data_inert_mp_brfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRFe, Farray_Freal8_1_3_1_156, ("__model_data_inert_MOD_brfe", "model_data_inert_mp_brfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRFu, Farray_Freal8_1_3_1_159, ("__model_data_inert_MOD_brfu", "model_data_inert_mp_brfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRH0, Farray_Freal8_1_1_1_54, ("__model_data_inert_MOD_brh0", "model_data_inert_mp_brh0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHAA, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brhaa", "model_data_inert_mp_brhaa_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHAAijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_brhaaijk", "model_data_inert_mp_brhaaijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHAZ, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brhaz", "model_data_inert_mp_brhaz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHHAijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_brhhaijk", "model_data_inert_mp_brhhaijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHHH, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brhhh", "model_data_inert_mp_brhhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHHHijk, Farray_Freal8_1_1_1_1_1_1, ("__model_data_inert_MOD_brhhhijk", "model_data_inert_mp_brhhhijk_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHHZ, Farray_Freal8_1_1_1_1, ("__model_data_inert_MOD_brhhz", "model_data_inert_mp_brhhz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHhpW, Farray_Freal8_1_1_1_2, ("__model_data_inert_MOD_brhhpw", "model_data_inert_mp_brhhpw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHll, Farray_Freal8_1_1_1_3_1_3, ("__model_data_inert_MOD_brhll", "model_data_inert_mp_brhll_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRHp, Farray_Freal8_1_2_1_28, ("__model_data_inert_MOD_brhp", "model_data_inert_mp_brhp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRhh, Farray_Freal8_1_1_1_59, ("__model_data_inert_MOD_brhh", "model_data_inert_mp_brhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRinvA, Farray_Freal8_1_1, ("__model_data_inert_MOD_brinva", "model_data_inert_mp_brinva_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BRinvH, Farray_Freal8_1_1, ("__model_data_inert_MOD_brinvh", "model_data_inert_mp_brinvh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LA0, Freal8, ("__model_data_inert_MOD_gt1la0", "model_data_inert_mp_gt1la0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LFd, Farray_Freal8_1_3, ("__model_data_inert_MOD_gt1lfd", "model_data_inert_mp_gt1lfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LFe, Farray_Freal8_1_3, ("__model_data_inert_MOD_gt1lfe", "model_data_inert_mp_gt1lfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LFu, Farray_Freal8_1_3, ("__model_data_inert_MOD_gt1lfu", "model_data_inert_mp_gt1lfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LH0, Freal8, ("__model_data_inert_MOD_gt1lh0", "model_data_inert_mp_gt1lh0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1LHp, Farray_Freal8_1_2, ("__model_data_inert_MOD_gt1lhp", "model_data_inert_mp_gt1lhp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gT1Lhh, Freal8, ("__model_data_inert_MOD_gt1lhh", "model_data_inert_mp_gt1lhh_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTA0, Freal8, ("__model_data_inert_MOD_gta0", "model_data_inert_mp_gta0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTFd, Farray_Freal8_1_3, ("__model_data_inert_MOD_gtfd", "model_data_inert_mp_gtfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTFe, Farray_Freal8_1_3, ("__model_data_inert_MOD_gtfe", "model_data_inert_mp_gtfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTFu, Farray_Freal8_1_3, ("__model_data_inert_MOD_gtfu", "model_data_inert_mp_gtfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTH0, Freal8, ("__model_data_inert_MOD_gth0", "model_data_inert_mp_gth0_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gTHp, Farray_Freal8_1_2, ("__model_data_inert_MOD_gthp", "model_data_inert_mp_gthp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(gThh, Freal8, ("__model_data_inert_MOD_gthh", "model_data_inert_mp_gthh_"),"SARAHSPheno_Inert_internal")

// Decay options
BE_VARIABLE(divonly_save, Finteger, ("__settings_MOD_divonly_save", "settings_mp_divonly_save_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(divergence_save, Freal8, ("__settings_MOD_divergence_save", "settings_mp_divergence_save_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(SimplisticLoopDecays, Flogical, ("__settings_MOD_simplisticloopdecays", "settings_mp_simplisticloopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ShiftIRdiv, Flogical, ("__settings_MOD_shiftirdiv", "settings_mp_shiftirdiv_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(DebugLoopDecays, Flogical, ("__settings_MOD_debugloopdecays", "settings_mp_debugloopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(OnlyTreeLevelContributions, Flogical, ("__settings_MOD_onlytreelevelcontributions", "settings_mp_onlytreelevelcontributions_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ExternalZfactors, Flogical, ("__settings_MOD_externalzfactors", "settings_mp_externalzfactors_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(UseZeroRotationMatrices, Flogical, ("__settings_MOD_usezerorotationmatrices", "settings_mp_usezerorotationmatrices_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(UseP2Matrices, Flogical, ("__settings_MOD_usep2matrices", "settings_mp_usep2matrices_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(OSkinematics, Flogical, ("__settings_MOD_oskinematics", "settings_mp_oskinematics_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(ewOSinDecays, Flogical, ("__settings_MOD_ewosindecays", "settings_mp_ewosindecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(yukOSinDecays, Flogical, ("__settings_MOD_yukosindecays", "settings_mp_yukosindecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CTinLoopDecays, Flogical, ("__settings_MOD_ctinloopdecays", "settings_mp_ctinloopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(LoopInducedDecaysOS, Flogical, ("__settings_MOD_loopinduceddecaysos", "settings_mp_loopinduceddecaysos_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Mass_Regulator_PhotonGluon, Freal8, ("__settings_MOD_mass_regulator_photongluon", "settings_mp_mass_regulator_photongluon_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Extra_Scale_LoopDecays, Flogical, ("__settings_MOD_extra_scale_loopdecays", "settings_mp_extra_scale_loopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Scale_LoopDecays, Freal8, ("__settings_MOD_scale_loopdecays", "settings_mp_scale_loopdecays_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Calc3BodyDecay_Fd, Flogical, ("__model_data_inert_MOD_calc3bodydecay_fd", "model_data_inert_mp_calc3bodydecay_fd_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Calc3BodyDecay_Fe, Flogical, ("__model_data_inert_MOD_calc3bodydecay_fe", "model_data_inert_mp_calc3bodydecay_fe_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(Calc3BodyDecay_Fu, Flogical, ("__model_data_inert_MOD_calc3bodydecay_fu", "model_data_inert_mp_calc3bodydecay_fu_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_A0, Flogical, ("__model_data_inert_MOD_calcloopdecay_a0", "model_data_inert_mp_calcloopdecay_a0_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_Fd, Flogical, ("__model_data_inert_MOD_calcloopdecay_fd", "model_data_inert_mp_calcloopdecay_fd_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_Fe, Flogical, ("__model_data_inert_MOD_calcloopdecay_fe", "model_data_inert_mp_calcloopdecay_fe_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_H0, Flogical, ("__model_data_inert_MOD_calcloopdecay_h0", "model_data_inert_mp_calcloopdecay_h0_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_Hp, Flogical, ("__model_data_inert_MOD_calcloopdecay_hp", "model_data_inert_mp_calcloopdecay_hp_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_LoopInducedOnly, Flogical, ("__model_data_inert_MOD_calcloopdecay_loopinducedonly", "model_data_inert_mp_calcloopdecay_loopinducedonly_"), "SARAHSPheno_Inert_internal")
BE_VARIABLE(CalcLoopDecay_hh, Flogical, ("__model_data_inert_MOD_calcloopdecay_hh", "model_data_inert_mp_calcloopdecay_hh_"), "SARAHSPheno_Inert_internal")

// HiggsBounds variables
BE_VARIABLE(BR_Hcb, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_hcb", "model_data_inert_mp_br_hcb_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_Hcs, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_hcs", "model_data_inert_mp_br_hcs_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_HpAW, Farray_Freal8_1_2_1_1, ("__model_data_inert_MOD_br_hpaw", "model_data_inert_mp_br_hpaw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_HpHW, Farray_Freal8_1_2_1_1, ("__model_data_inert_MOD_br_hphw", "model_data_inert_mp_br_hphw_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_HpTB, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_hptb", "model_data_inert_mp_br_hptb_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_HpWZ, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_hpwz", "model_data_inert_mp_br_hpwz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_Htaunu, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_htaunu", "model_data_inert_mp_br_htaunu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_tHb, Farray_Freal8_1_2, ("__model_data_inert_MOD_br_thb", "model_data_inert_mp_br_thb_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(BR_tWb, Freal8, ("__model_data_inert_MOD_br_twb", "model_data_inert_mp_br_twb_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CPL_A_A_Z, Farray_Fcomplex16_1_1_1_1, ("__model_data_inert_MOD_cpl_a_a_z", "model_data_inert_mp_cpl_a_a_z_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CPL_A_H_Z, Fcomplex16, ("__model_data_inert_MOD_cpl_a_h_z", "model_data_inert_mp_cpl_a_h_z_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(CPL_H_H_Z, Farray_Fcomplex16_1_1_1_1, ("__model_data_inert_MOD_cpl_h_h_z", "model_data_inert_mp_cpl_h_h_z_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_P_Fd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_p_fd", "model_data_inert_mp_rhb_p_p_fd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_P_Fe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_p_fe", "model_data_inert_mp_rhb_p_p_fe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_P_Fu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_p_fu", "model_data_inert_mp_rhb_p_p_fu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_P_Fv, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_p_fv", "model_data_inert_mp_rhb_p_p_fv_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_S_Fd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_s_fd", "model_data_inert_mp_rhb_p_s_fd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_S_Fe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_s_fe", "model_data_inert_mp_rhb_p_s_fe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_S_Fu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_p_s_fu", "model_data_inert_mp_rhb_p_s_fu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_S_Fv, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_s_fv", "model_data_inert_mp_rhb_p_s_fv_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_VG, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_vg", "model_data_inert_mp_rhb_p_vg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_VP, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_vp", "model_data_inert_mp_rhb_p_vp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_VWp, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_vwp", "model_data_inert_mp_rhb_p_vwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_P_VZ, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_p_vz", "model_data_inert_mp_rhb_p_vz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_P_Fd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_p_fd", "model_data_inert_mp_rhb_s_p_fd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_P_Fe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_p_fe", "model_data_inert_mp_rhb_s_p_fe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_P_Fu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_p_fu", "model_data_inert_mp_rhb_s_p_fu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_P_Fv, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_p_fv", "model_data_inert_mp_rhb_s_p_fv_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_S_Fd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_s_fd", "model_data_inert_mp_rhb_s_s_fd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_S_Fe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_s_fe", "model_data_inert_mp_rhb_s_s_fe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_S_Fu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_rhb_s_s_fu", "model_data_inert_mp_rhb_s_s_fu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_S_Fv, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_s_fv", "model_data_inert_mp_rhb_s_s_fv_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_VG, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_vg", "model_data_inert_mp_rhb_s_vg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_VP, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_vp", "model_data_inert_mp_rhb_s_vp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_VWp, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_vwp", "model_data_inert_mp_rhb_s_vwp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(rHB_S_VZ, Farray_Freal8_1_1, ("__model_data_inert_MOD_rhb_s_vz", "model_data_inert_mp_rhb_s_vz_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioGG, Fcomplex16, ("__model_data_inert_MOD_ratiogg", "model_data_inert_mp_ratiogg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPFd, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiopfd", "model_data_inert_mp_ratiopfd_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPFe, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiopfe", "model_data_inert_mp_ratiopfe_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPFu, Farray_Freal8_1_1_1_3, ("__model_data_inert_MOD_ratiopfu", "model_data_inert_mp_ratiopfu_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPGG, Fcomplex16, ("__model_data_inert_MOD_ratiopgg", "model_data_inert_mp_ratiopgg_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPHp, Farray_Freal8_1_1_1_2, ("__model_data_inert_MOD_ratiophp", "model_data_inert_mp_ratiophp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPP, Fcomplex16, ("__model_data_inert_MOD_ratiopp", "model_data_inert_mp_ratiopp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPPP, Fcomplex16, ("__model_data_inert_MOD_ratioppp", "model_data_inert_mp_ratioppp_"),"SARAHSPheno_Inert_internal")
BE_VARIABLE(ratioPVWp, Freal8, ("__model_data_inert_MOD_ratiopvwp", "model_data_inert_mp_ratiopvwp_"),"SARAHSPheno_Inert_internal")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SARAHSPheno_Inert_spectrum")
BE_CONV_FUNCTION(run_SPheno_decays, int, (const Spectrum &, DecayTable &, const Finputs&), "SARAHSPheno_Inert_decays")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const Finputs&), "SARAHSPheno_Inert_internal")
BE_CONV_FUNCTION(get_HiggsCouplingsTable, int, (const Spectrum&, HiggsCouplingsTable&, const Finputs&), "SARAHSPheno_Inert_HiggsCouplingsTable")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SARAHSPheno_Inert_internal")
BE_CONV_FUNCTION(ReadingData_decays, void, (const Finputs&), "SARAHSPheno_Inert_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SARAHSPheno_Inert_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SARAHSPheno_Inert_internal")

// Initialisation functions (dependencies)

// Function pointer variable for error handling
BE_VARIABLE(ErrorHandler_cptr, fptr_void, ("__control_MOD_errorhandler_cptr", "control_mp_errorhandler_cptr_"), "SARAHSPheno_Inert_internal")

// End
#include "gambit/Backends/backend_undefs.hpp"
