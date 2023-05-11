//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Frontend header for SARAH-SPheno 4.0.3 backend,
/// for the gumTHDMII model.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:42PM on September 21, 2022
///                                                
///  ********************************************* 

#define BACKENDNAME SARAHSPheno_gumTHDMII
#define BACKENDLANG FORTRAN
#define VERSION 4.0.3
#define SARAH_VERSION 4.14.0
#define SAFE_VERSION 4_0_3
#define REFERENCE Porod:2003um,Porod:2011nf
// Begin
LOAD_LIBRARY

// Allow for gumTHDMII only
BE_ALLOW_MODELS(gumTHDMII)

BE_FUNCTION(CoupHiggsToPhoton, void, (Freal8&, // mHiggs
                                      Finteger&, // inG
                                      Farray_Fcomplex16_1_3&, // ratFd
                                      Farray_Fcomplex16_1_3&, // ratFe
                                      Farray_Fcomplex16_1_3&, // ratFu
                                      Farray_Fcomplex16_1_2&, // ratHm
                                      Fcomplex16&, // ratVWm
                                      Farray_Freal8_1_3&, // MFd
                                      Farray_Freal8_1_3&, // MFe
                                      Farray_Freal8_1_3&, // MFu
                                      Farray_Freal8_1_2&, // MHm
                                      Freal8&, // MVWm
                                      Freal8&, // gNLO
                                      Fcomplex16& // coup
                                      ), ("__loopcouplings_gumthdmii_MOD_couphiggstophoton","loopcouplings_gumthdmii_mp_couphiggstophoton"), "CoupHiggsToPhoton")

BE_FUNCTION(CoupPseudoHiggsToPhoton, void, (Freal8&, // mHiggs
                                      Finteger&, // inG
                                      Farray_Fcomplex16_1_3&, // ratFd
                                      Farray_Fcomplex16_1_3&, // ratFe
                                      Farray_Fcomplex16_1_3&, // ratFu
                                      Farray_Fcomplex16_1_2&, // ratHm
                                      Fcomplex16&, // ratVWm
                                      Farray_Freal8_1_3&, // MFd
                                      Farray_Freal8_1_3&, // MFe
                                      Farray_Freal8_1_3&, // MFu
                                      Farray_Freal8_1_2&, // MHm
                                      Freal8&, // MVWm
                                      Freal8&, // gNLO
                                      Fcomplex16& // coup
                                      ), ("__loopcouplings_gumthdmii_MOD_couppseudohiggstophoton","loopcouplings_gumthdmii_mp_couppseudohiggstophoton"), "CoupPseudoHiggsToPhoton")

BE_FUNCTION(CoupHiggsToGluon, void, (Freal8&, // mHiggs
                                      Finteger&, // inG
                                      Farray_Fcomplex16_1_3&, // ratFd
                                      Farray_Fcomplex16_1_3&, // ratFu
                                      Farray_Freal8_1_3&, // MFd
                                      Farray_Freal8_1_3&, // MFu
                                      Freal8&, // gNLO
                                      Fcomplex16& // coup
                                      ), ("__loopcouplings_gumthdmii_MOD_couphiggstogluon","loopcouplings_gumthdmii_mp_couphiggstogluon"), "CoupHiggsToGluon")

BE_FUNCTION(CoupHiggsToPhotonSM, void, (Freal8&, // mHiggs
                                      Farray_Freal8_1_3&, // MFd
                                      Farray_Freal8_1_3&, // MFe
                                      Farray_Freal8_1_3&, // MFu
                                      Farray_Freal8_1_2&, // MHm
                                      Freal8&, // MVWm
                                      Freal8&, // gNLO
                                      Fcomplex16& // coup
                                      ), ("__loopcouplings_gumthdmii_MOD_couphiggstophotonsm","loopcouplings_gumthdmii_mp_couphiggstophotonsm"), "CoupHiggsToPhotonSM")

BE_FUNCTION(CoupHiggsToGluonSM, void, (Freal8&, // mHiggs
                                      Farray_Freal8_1_3&, // MFd
                                      Farray_Freal8_1_3&, // MFu
                                      Freal8&, // gNLO
                                      Fcomplex16& // coup
                                      ), ("__loopcouplings_gumthdmii_MOD_couphiggstogluonsm","loopcouplings_gumthdmii_mp_couphiggstogluonsm"), "CoupHiggsToGluonSM")

// Freal8
// Fcomplex16
// Finteger
// Farray_Freal8_1_3
// Farray_Fcomplex16_1_3

//<name>, <ret>, (<args>), (__<module>_MOD_<function> , <module>_mp_<function>), <capability?

// BE_FUNCTION(SPheno_Main, void, (), ("__sphenogumthdmii_MOD_spheno_main", "sphenogumthdmii_mp_spheno_main_"), "SARAHSPheno_gumTHDMII_internal")
// BE_VARIABLE(CalculateLowEnergy, Flogical, ("__settings_MOD_calculatelowenergy", "settings_mp_calculatelowenergy_"), "SARAHSPheno_gumTHDMII_internal")

// Functions
BE_FUNCTION(SPheno_Main, void, (), ("__sphenogumthdmii_MOD_spheno_main", "sphenogumthdmii_mp_spheno_main_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(Set_All_Parameters_0, void, (), ("__model_data_gumthdmii_MOD_set_all_parameters_0", "model_data_gumthdmii_mp_set_all_parameters_0_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(SetRenormalizationScale, Freal8, (Freal8&), ("__loopfunctions_MOD_setrenormalizationscale", "loopfunctions_mp_setrenormalizationscale_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(InitializeLoopFunctions, void, (), ("__loopfunctions_MOD_initializeloopfunctions", "loopfunctions_mp_initializeloopfunctions_"), "SARAHSPheno_gumTHDMII_internal")
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
     ("__standardmodel_MOD_calculaterunningmasses", "standardmodel_mp_calculaterunningmasses_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(GetRenormalizationScale, Freal8, (), ("__loopfunctions_MOD_getrenormalizationscale", "loopfunctions_mp_getrenormalizationscale_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(SetRGEScale, void, (Freal8&), ("__model_data_gumthdmii_MOD_setrgescale", "model_data_gumthdmii_mp_setrgescale_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(SetGUTScale, void, (Freal8&), ("__model_data_gumthdmii_MOD_setgutscale", "model_data_gumthdmii_mp_setgutscale_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(SetStrictUnification, Flogical, (Flogical&), ("__model_data_gumthdmii_MOD_setstrictunification", "model_data_gumthdmii_mp_setstrictunification_"), "SARAHSPheno_gumTHDMII_internal")
BE_FUNCTION(SetYukawaScheme, Finteger, (Finteger&), ("__model_data_gumthdmii_MOD_setyukawascheme", "model_data_gumthdmii_mp_setyukawascheme_"), "SARAHSPheno_gumTHDMII_internal")

// Model-dependent arguments auto-scraped by GUM
BE_FUNCTION(CalculateBR_2, void,
  (Flogical&, // CTBD
   Freal8&, // fac3
   Freal8&, // epsI
   Freal8&, // deltaM
   Finteger&, // kont
   Farray_Freal8_1_2&, // MAh
   Farray_Freal8_1_2&, // MAh2
   Farray_Freal8_1_3&, // MFd
   Farray_Freal8_1_3&, // MFd2
   Farray_Freal8_1_3&, // MFe
   Farray_Freal8_1_3&, // MFe2
   Farray_Freal8_1_3&, // MFu
   Farray_Freal8_1_3&, // MFu2
   Farray_Freal8_1_2&, // Mhh
   Farray_Freal8_1_2&, // Mhh2
   Farray_Freal8_1_2&, // MHm
   Farray_Freal8_1_2&, // MHm2
   Freal8&, // MVWm
   Freal8&, // MVWm2
   Freal8&, // MVZ
   Freal8&, // MVZ2
   Freal8&, // TW
   Farray_Fcomplex16_1_3_1_3&, // ZDR
   Farray_Fcomplex16_1_3_1_3&, // ZER
   Farray_Fcomplex16_1_3_1_3&, // ZUR
   Freal8&, // v
   Farray_Fcomplex16_1_3_1_3&, // ZDL
   Farray_Fcomplex16_1_3_1_3&, // ZEL
   Farray_Fcomplex16_1_3_1_3&, // ZUL
   Farray_Freal8_1_2_1_2&, // ZA
   Farray_Freal8_1_2_1_2&, // ZH
   Farray_Freal8_1_2_1_2&, // ZP
   Farray_Fcomplex16_1_2_1_2&, // ZW
   Farray_Freal8_1_2_1_2&, // ZZ
   Freal8&, // alphaH
   Freal8&, // betaH
   Freal8&, // vd
   Freal8&, // vu
   Freal8&, // g1
   Freal8&, // g2
   Freal8&, // g3
   Fcomplex16&, // lam5
   Fcomplex16&, // lam1
   Fcomplex16&, // lam4
   Fcomplex16&, // lam3
   Fcomplex16&, // lam2
   Farray_Fcomplex16_1_3_1_3&, // Yu
   Farray_Fcomplex16_1_3_1_3&, // Yd
   Farray_Fcomplex16_1_3_1_3&, // Ye
   Fcomplex16&, // m122
   Fcomplex16&, // m112
   Fcomplex16&, // m222
   Farray_Freal8_1_3_1_159&, // gPFu
   Farray_Freal8_1_3&, // gTFu
   Farray_Freal8_1_3_1_159&, // BRFu
   Farray_Freal8_1_3_1_156&, // gPFe
   Farray_Freal8_1_3&, // gTFe
   Farray_Freal8_1_3_1_156&, // BRFe
   Farray_Freal8_1_3_1_159&, // gPFd
   Farray_Freal8_1_3&, // gTFd
   Farray_Freal8_1_3_1_159&, // BRFd
   Farray_Freal8_1_2_1_59&, // gPhh
   Farray_Freal8_1_2&, // gThh
   Farray_Freal8_1_2_1_59&, // BRhh
   Farray_Freal8_1_2_1_57&, // gPAh
   Farray_Freal8_1_2&, // gTAh
   Farray_Freal8_1_2_1_57&, // BRAh
   Farray_Freal8_1_2_1_28&, // gPHm
   Farray_Freal8_1_2&, // gTHm
   Farray_Freal8_1_2_1_28& // BRHm
), ("__branchingratios_gumthdmii_MOD_calculatebr_2", "branchingratios_gumthdmii_mp_calculatebr_2_"), "SARAHSPheno_gumTHDMII_internal")
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
), ("__inputoutput_gumthdmii_MOD_switch_to_superckm", "inputoutput_gumthdmii_mp_switch_to_superckm_"), "SARAHSPheno_gumTHDMII_internal")
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
), ("__inputoutput_gumthdmii_MOD_switch_to_superpmns", "inputoutput_gumthdmii_mp_switch_to_superpmns_"), "SARAHSPheno_gumTHDMII_internal")

// Model-dependent variables
BE_VARIABLE(BoundaryCondition, Finteger, ("__model_data_gumthdmii_MOD_boundarycondition", "model_data_gumthdmii_mp_boundarycondition_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CS_Higgs_LHC, Farray_Freal8_1_5_1_2_1_5, ("__model_data_gumthdmii_MOD_cs_higgs_lhc", "model_data_gumthdmii_mp_cs_higgs_lhc_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CS_PHiggs_LHC, Farray_Freal8_1_5_1_2_1_5, ("__model_data_gumthdmii_MOD_cs_phiggs_lhc", "model_data_gumthdmii_mp_cs_phiggs_lhc_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcFT, Flogical, ("__model_data_gumthdmii_MOD_calcft", "model_data_gumthdmii_mp_calcft_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CheckSugraDetails, Farray_Flogical_1_10, ("__model_data_gumthdmii_MOD_checksugradetails", "model_data_gumthdmii_mp_checksugradetails_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CoupAGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_coupagg", "model_data_gumthdmii_mp_coupagg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CoupAPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_coupapp", "model_data_gumthdmii_mp_coupapp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CoupHGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_couphgg", "model_data_gumthdmii_mp_couphgg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CoupHPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_couphpp", "model_data_gumthdmii_mp_couphpp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(FineTuningResults, void, ("__model_data_gumthdmii_MOD_finetuningresults", "model_data_gumthdmii_mp_finetuningresults_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(FineTuningResultsAllVEVs, void, ("__model_data_gumthdmii_MOD_finetuningresultsallvevs", "model_data_gumthdmii_mp_finetuningresultsallvevs_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(GUT_scale, Freal8, ("__model_data_gumthdmii_MOD_gut_scale", "model_data_gumthdmii_mp_gut_scale_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(GetMassUncertainty, Flogical, ("__model_data_gumthdmii_MOD_getmassuncertainty", "model_data_gumthdmii_mp_getmassuncertainty_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(GuessTwoLoopMatchingBSM, Flogical, ("__model_data_gumthdmii_MOD_guesstwoloopmatchingbsm", "model_data_gumthdmii_mp_guesstwoloopmatchingbsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HPPloopFd, Farray_Freal8_1_3_1_2, ("__model_data_gumthdmii_MOD_hpploopfd", "model_data_gumthdmii_mp_hpploopfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HPPloopFe, Farray_Freal8_1_3_1_2, ("__model_data_gumthdmii_MOD_hpploopfe", "model_data_gumthdmii_mp_hpploopfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HPPloopFu, Farray_Freal8_1_3_1_2, ("__model_data_gumthdmii_MOD_hpploopfu", "model_data_gumthdmii_mp_hpploopfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HPPloopHm, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_hpploophm", "model_data_gumthdmii_mp_hpploophm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HPPloopVWm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_hpploopvwm", "model_data_gumthdmii_mp_hpploopvwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(IgnoreMuSignFlip, Flogical, ("__model_data_gumthdmii_MOD_ignoremusignflip", "model_data_gumthdmii_mp_ignoremusignflip_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(IgnoreNegativeMasses, Flogical, ("__model_data_gumthdmii_MOD_ignorenegativemasses", "model_data_gumthdmii_mp_ignorenegativemasses_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(IgnoreNegativeMassesMZ, Flogical, ("__model_data_gumthdmii_MOD_ignorenegativemassesmz", "model_data_gumthdmii_mp_ignorenegativemassesmz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforYd, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforyd", "model_data_gumthdmii_mp_inputvalueforyd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforYe, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforye", "model_data_gumthdmii_mp_inputvalueforye_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforYu, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforyu", "model_data_gumthdmii_mp_inputvalueforyu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforg1, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforg1", "model_data_gumthdmii_mp_inputvalueforg1_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforg2, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforg2", "model_data_gumthdmii_mp_inputvalueforg2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforg3, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforg3", "model_data_gumthdmii_mp_inputvalueforg3_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforlam1, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforlam1", "model_data_gumthdmii_mp_inputvalueforlam1_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforlam2, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforlam2", "model_data_gumthdmii_mp_inputvalueforlam2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforlam3, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforlam3", "model_data_gumthdmii_mp_inputvalueforlam3_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforlam4, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforlam4", "model_data_gumthdmii_mp_inputvalueforlam4_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueforlam5, Flogical, ("__model_data_gumthdmii_MOD_inputvalueforlam5", "model_data_gumthdmii_mp_inputvalueforlam5_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueform112, Flogical, ("__model_data_gumthdmii_MOD_inputvalueform112", "model_data_gumthdmii_mp_inputvalueform112_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueform122, Flogical, ("__model_data_gumthdmii_MOD_inputvalueform122", "model_data_gumthdmii_mp_inputvalueform122_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InputValueform222, Flogical, ("__model_data_gumthdmii_MOD_inputvalueform222", "model_data_gumthdmii_mp_inputvalueform222_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(KineticMixing, Flogical, ("__model_data_gumthdmii_MOD_kineticmixing", "model_data_gumthdmii_mp_kineticmixing_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(KineticMixingSave, Flogical, ("__model_data_gumthdmii_MOD_kineticmixingsave", "model_data_gumthdmii_mp_kineticmixingsave_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Lambda1Input, Fcomplex16, ("__model_data_gumthdmii_MOD_lambda1input", "model_data_gumthdmii_mp_lambda1input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Lambda2Input, Fcomplex16, ("__model_data_gumthdmii_MOD_lambda2input", "model_data_gumthdmii_mp_lambda2input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Lambda3Input, Fcomplex16, ("__model_data_gumthdmii_MOD_lambda3input", "model_data_gumthdmii_mp_lambda3input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Lambda4Input, Fcomplex16, ("__model_data_gumthdmii_MOD_lambda4input", "model_data_gumthdmii_mp_lambda4input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Lambda5Input, Fcomplex16, ("__model_data_gumthdmii_MOD_lambda5input", "model_data_gumthdmii_mp_lambda5input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(M122input, Fcomplex16, ("__model_data_gumthdmii_MOD_m122input", "model_data_gumthdmii_mp_m122input_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mah", "model_data_gumthdmii_mp_mah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAh2, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mah2", "model_data_gumthdmii_mp_mah2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAh2L, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mah2l", "model_data_gumthdmii_mp_mah2l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAh2_s, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mah2_s", "model_data_gumthdmii_mp_mah2_s_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAhL, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mahl", "model_data_gumthdmii_mp_mahl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MAh_s, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mah_s", "model_data_gumthdmii_mp_mah_s_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFd, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfd", "model_data_gumthdmii_mp_mfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFd2, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfd2", "model_data_gumthdmii_mp_mfd2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFe, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfe", "model_data_gumthdmii_mp_mfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFe2, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfe2", "model_data_gumthdmii_mp_mfe2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFu, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfu", "model_data_gumthdmii_mp_mfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MFu2, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_mfu2", "model_data_gumthdmii_mp_mfu2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MHm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhm", "model_data_gumthdmii_mp_mhm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MHm2, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhm2", "model_data_gumthdmii_mp_mhm2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MVWm, Freal8, ("__model_data_gumthdmii_MOD_mvwm", "model_data_gumthdmii_mp_mvwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MVWm2, Freal8, ("__model_data_gumthdmii_MOD_mvwm2", "model_data_gumthdmii_mp_mvwm2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MVZ, Freal8, ("__model_data_gumthdmii_MOD_mvz", "model_data_gumthdmii_mp_mvz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MVZ2, Freal8, ("__model_data_gumthdmii_MOD_mvz2", "model_data_gumthdmii_mp_mvz2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mhh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhh", "model_data_gumthdmii_mp_mhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mhh2, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhh2", "model_data_gumthdmii_mp_mhh2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mhh2L, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhh2l", "model_data_gumthdmii_mp_mhh2l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mhh2_s, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhh2_s", "model_data_gumthdmii_mp_mhh2_s_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MhhL, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhhl", "model_data_gumthdmii_mp_mhhl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mhh_s, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_mhh_s", "model_data_gumthdmii_mp_mhh_s_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OneLoopFT, Flogical, ("__model_data_gumthdmii_MOD_oneloopft", "model_data_gumthdmii_mp_oneloopft_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OneLoopMatching, Flogical, ("__model_data_gumthdmii_MOD_oneloopmatching", "model_data_gumthdmii_mp_oneloopmatching_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RXiG, Freal8, ("__model_data_gumthdmii_MOD_rxig", "model_data_gumthdmii_mp_rxig_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RXiP, Freal8, ("__model_data_gumthdmii_MOD_rxip", "model_data_gumthdmii_mp_rxip_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RXiWm, Freal8, ("__model_data_gumthdmii_MOD_rxiwm", "model_data_gumthdmii_mp_rxiwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RXiZ, Freal8, ("__model_data_gumthdmii_MOD_rxiz", "model_data_gumthdmii_mp_rxiz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RotateNegativeFermionMasses, Flogical, ("__model_data_gumthdmii_MOD_rotatenegativefermionmasses", "model_data_gumthdmii_mp_rotatenegativefermionmasses_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RunRGEs_unitarity, Flogical, ("__model_data_gumthdmii_MOD_runrges_unitarity", "model_data_gumthdmii_mp_runrges_unitarity_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SolutionTadpoleNr, Finteger, ("__model_data_gumthdmii_MOD_solutiontadpolenr", "model_data_gumthdmii_mp_solutiontadpolenr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(StrictUnification, Flogical, ("__model_data_gumthdmii_MOD_strictunification", "model_data_gumthdmii_mp_strictunification_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SugraErrors, Farray_Flogical_1_10, ("__model_data_gumthdmii_MOD_sugraerrors", "model_data_gumthdmii_mp_sugraerrors_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TUcutLevel, Finteger, ("__model_data_gumthdmii_MOD_tucutlevel", "model_data_gumthdmii_mp_tucutlevel_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TW, Freal8, ("__model_data_gumthdmii_MOD_tw", "model_data_gumthdmii_mp_tw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TanBeta, Freal8, ("__model_data_gumthdmii_MOD_tanbeta", "model_data_gumthdmii_mp_tanbeta_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TanBetaQ, Freal8, ("__model_data_gumthdmii_MOD_tanbetaq", "model_data_gumthdmii_mp_tanbetaq_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TransposedYukawa, Flogical, ("__model_data_gumthdmii_MOD_transposedyukawa", "model_data_gumthdmii_mp_transposedyukawa_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TreeLevelUnitarityLimits, Flogical, ("__model_data_gumthdmii_MOD_treelevelunitaritylimits", "model_data_gumthdmii_mp_treelevelunitaritylimits_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TrilinearUnitarity, Flogical, ("__model_data_gumthdmii_MOD_trilinearunitarity", "model_data_gumthdmii_mp_trilinearunitarity_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopMatching, Flogical, ("__model_data_gumthdmii_MOD_twoloopmatching", "model_data_gumthdmii_mp_twoloopmatching_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(UseFixedGUTScale, Flogical, ("__model_data_gumthdmii_MOD_usefixedgutscale", "model_data_gumthdmii_mp_usefixedgutscale_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(UseFixedScale, Flogical, ("__model_data_gumthdmii_MOD_usefixedscale", "model_data_gumthdmii_mp_usefixedscale_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteEffHiggsCouplingRatios, Flogical, ("__model_data_gumthdmii_MOD_writeeffhiggscouplingratios", "model_data_gumthdmii_mp_writeeffhiggscouplingratios_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteHiggsDiphotonLoopContributions, Flogical, ("__model_data_gumthdmii_MOD_writehiggsdiphotonloopcontributions", "model_data_gumthdmii_mp_writehiggsdiphotonloopcontributions_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteTreeLevelTadpoleSolutions, Flogical, ("__model_data_gumthdmii_MOD_writetreeleveltadpolesolutions", "model_data_gumthdmii_mp_writetreeleveltadpolesolutions_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Write_WHIZARD, Flogical, ("__model_data_gumthdmii_MOD_write_whizard", "model_data_gumthdmii_mp_write_whizard_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_d, Fcomplex16, ("__model_data_gumthdmii_MOD_y_d", "model_data_gumthdmii_mp_y_d_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_d_0, Fcomplex16, ("__model_data_gumthdmii_MOD_y_d_0", "model_data_gumthdmii_mp_y_d_0_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_d_mZ, Fcomplex16, ("__model_data_gumthdmii_MOD_y_d_mz", "model_data_gumthdmii_mp_y_d_mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_l, Fcomplex16, ("__model_data_gumthdmii_MOD_y_l", "model_data_gumthdmii_mp_y_l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_l_0, Fcomplex16, ("__model_data_gumthdmii_MOD_y_l_0", "model_data_gumthdmii_mp_y_l_0_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_l_mZ, Fcomplex16, ("__model_data_gumthdmii_MOD_y_l_mz", "model_data_gumthdmii_mp_y_l_mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_u, Fcomplex16, ("__model_data_gumthdmii_MOD_y_u", "model_data_gumthdmii_mp_y_u_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_u_0, Fcomplex16, ("__model_data_gumthdmii_MOD_y_u_0", "model_data_gumthdmii_mp_y_u_0_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Y_u_mZ , Fcomplex16, ("__model_data_gumthdmii_MOD_y_u_mz ", "model_data_gumthdmii_mp_y_u_mz _"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Yd, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yd", "model_data_gumthdmii_mp_yd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YdGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_ydgut", "model_data_gumthdmii_mp_ydgut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YdIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_ydin", "model_data_gumthdmii_mp_ydin_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YdMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_ydmz", "model_data_gumthdmii_mp_ydmz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Yd_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yd_saveep", "model_data_gumthdmii_mp_yd_saveep_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Ye, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_ye", "model_data_gumthdmii_mp_ye_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YeGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yegut", "model_data_gumthdmii_mp_yegut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YeIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yein", "model_data_gumthdmii_mp_yein_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YeMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yemz", "model_data_gumthdmii_mp_yemz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Ye_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_ye_saveep", "model_data_gumthdmii_mp_ye_saveep_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Yu, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yu", "model_data_gumthdmii_mp_yu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YuGUT, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yugut", "model_data_gumthdmii_mp_yugut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YuIN, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yuin", "model_data_gumthdmii_mp_yuin_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YuMZ, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yumz", "model_data_gumthdmii_mp_yumz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Yu_saveEP, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_yu_saveep", "model_data_gumthdmii_mp_yu_saveep_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(YukawaScheme, Finteger, ("__model_data_gumthdmii_MOD_yukawascheme", "model_data_gumthdmii_mp_yukawascheme_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZA, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_za", "model_data_gumthdmii_mp_za_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZDL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zdl", "model_data_gumthdmii_mp_zdl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZDR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zdr", "model_data_gumthdmii_mp_zdr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZEL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zel", "model_data_gumthdmii_mp_zel_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZER, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zer", "model_data_gumthdmii_mp_zer_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZH, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_zh", "model_data_gumthdmii_mp_zh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZP, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_zp", "model_data_gumthdmii_mp_zp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZUL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zul", "model_data_gumthdmii_mp_zul_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZUR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_zur", "model_data_gumthdmii_mp_zur_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZW, Farray_Fcomplex16_1_2_1_2, ("__model_data_gumthdmii_MOD_zw", "model_data_gumthdmii_mp_zw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ZZ, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_zz", "model_data_gumthdmii_mp_zz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(alphaH, Freal8, ("__model_data_gumthdmii_MOD_alphah", "model_data_gumthdmii_mp_alphah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(betaH, Freal8, ("__model_data_gumthdmii_MOD_betah", "model_data_gumthdmii_mp_betah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g1, Freal8, ("__model_data_gumthdmii_MOD_g1", "model_data_gumthdmii_mp_g1_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g1GUT, Freal8, ("__model_data_gumthdmii_MOD_g1gut", "model_data_gumthdmii_mp_g1gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g1IN, Freal8, ("__model_data_gumthdmii_MOD_g1in", "model_data_gumthdmii_mp_g1in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g1MZ, Freal8, ("__model_data_gumthdmii_MOD_g1mz", "model_data_gumthdmii_mp_g1mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g1_saveEP, Freal8, ("__model_data_gumthdmii_MOD_g1_saveep", "model_data_gumthdmii_mp_g1_saveep_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g2, Freal8, ("__model_data_gumthdmii_MOD_g2", "model_data_gumthdmii_mp_g2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g2GUT, Freal8, ("__model_data_gumthdmii_MOD_g2gut", "model_data_gumthdmii_mp_g2gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g2IN, Freal8, ("__model_data_gumthdmii_MOD_g2in", "model_data_gumthdmii_mp_g2in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g2MZ, Freal8, ("__model_data_gumthdmii_MOD_g2mz", "model_data_gumthdmii_mp_g2mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g2_saveEP, Freal8, ("__model_data_gumthdmii_MOD_g2_saveep", "model_data_gumthdmii_mp_g2_saveep_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g3, Freal8, ("__model_data_gumthdmii_MOD_g3", "model_data_gumthdmii_mp_g3_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g3GUT, Freal8, ("__model_data_gumthdmii_MOD_g3gut", "model_data_gumthdmii_mp_g3gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g3IN, Freal8, ("__model_data_gumthdmii_MOD_g3in", "model_data_gumthdmii_mp_g3in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g3MZ, Freal8, ("__model_data_gumthdmii_MOD_g3mz", "model_data_gumthdmii_mp_g3mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g3running, Freal8, ("__model_data_gumthdmii_MOD_g3running", "model_data_gumthdmii_mp_g3running_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gForTadpoles, Farray_Freal8_1_75, ("__model_data_gumthdmii_MOD_gfortadpoles", "model_data_gumthdmii_mp_gfortadpoles_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1LAh, Farray_Freal8_1_2_1_57, ("__model_data_gumthdmii_MOD_gp1lah", "model_data_gumthdmii_mp_gp1lah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1LFd, Farray_Freal8_1_3_1_24, ("__model_data_gumthdmii_MOD_gp1lfd", "model_data_gumthdmii_mp_gp1lfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1LFe, Farray_Freal8_1_3_1_21, ("__model_data_gumthdmii_MOD_gp1lfe", "model_data_gumthdmii_mp_gp1lfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1LFu, Farray_Freal8_1_3_1_24, ("__model_data_gumthdmii_MOD_gp1lfu", "model_data_gumthdmii_mp_gp1lfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1LHm, Farray_Freal8_1_2_1_28, ("__model_data_gumthdmii_MOD_gp1lhm", "model_data_gumthdmii_mp_gp1lhm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gP1Lhh, Farray_Freal8_1_2_1_59, ("__model_data_gumthdmii_MOD_gp1lhh", "model_data_gumthdmii_mp_gp1lhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPAh, Farray_Freal8_1_2_1_57, ("__model_data_gumthdmii_MOD_gpah", "model_data_gumthdmii_mp_gpah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPFd, Farray_Freal8_1_3_1_159, ("__model_data_gumthdmii_MOD_gpfd", "model_data_gumthdmii_mp_gpfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPFe, Farray_Freal8_1_3_1_156, ("__model_data_gumthdmii_MOD_gpfe", "model_data_gumthdmii_mp_gpfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPFu, Farray_Freal8_1_3_1_159, ("__model_data_gumthdmii_MOD_gpfu", "model_data_gumthdmii_mp_gpfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPHm, Farray_Freal8_1_2_1_28, ("__model_data_gumthdmii_MOD_gphm", "model_data_gumthdmii_mp_gphm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gPhh, Farray_Freal8_1_2_1_59, ("__model_data_gumthdmii_MOD_gphh", "model_data_gumthdmii_mp_gphh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(g_SM_save, Farray_Freal8_1_62, ("__model_data_gumthdmii_MOD_g_sm_save", "model_data_gumthdmii_mp_g_sm_save_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gauge, Freal8, ("__model_data_gumthdmii_MOD_gauge", "model_data_gumthdmii_mp_gauge_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gauge_0, Freal8, ("__model_data_gumthdmii_MOD_gauge_0", "model_data_gumthdmii_mp_gauge_0_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gauge_mZ, Freal8, ("__model_data_gumthdmii_MOD_gauge_mz", "model_data_gumthdmii_mp_gauge_mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRmuTo3e, Freal8, ("__model_data_gumthdmii_MOD_global_brmuto3e", "model_data_gumthdmii_mp_global_brmuto3e_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauTo3e, Freal8, ("__model_data_gumthdmii_MOD_global_brtauto3e", "model_data_gumthdmii_mp_global_brtauto3e_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauTo3mu, Freal8, ("__model_data_gumthdmii_MOD_global_brtauto3mu", "model_data_gumthdmii_mp_global_brtauto3mu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauToemumu, Freal8, ("__model_data_gumthdmii_MOD_global_brtautoemumu", "model_data_gumthdmii_mp_global_brtautoemumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauToemumu2, Freal8, ("__model_data_gumthdmii_MOD_global_brtautoemumu2", "model_data_gumthdmii_mp_global_brtautoemumu2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauTomuee, Freal8, ("__model_data_gumthdmii_MOD_global_brtautomuee", "model_data_gumthdmii_mp_global_brtautomuee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BRtauTomuee2, Freal8, ("__model_data_gumthdmii_MOD_global_brtautomuee2", "model_data_gumthdmii_mp_global_brtautomuee2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0dEE, Freal8, ("__model_data_gumthdmii_MOD_global_brb0dee", "model_data_gumthdmii_mp_global_brb0dee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0dMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_brb0dmumu", "model_data_gumthdmii_mp_global_brb0dmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0dTauTau, Freal8, ("__model_data_gumthdmii_MOD_global_brb0dtautau", "model_data_gumthdmii_mp_global_brb0dtautau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0sEE, Freal8, ("__model_data_gumthdmii_MOD_global_brb0see", "model_data_gumthdmii_mp_global_brb0see_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0sMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_brb0smumu", "model_data_gumthdmii_mp_global_brb0smumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrB0sTauTau, Freal8, ("__model_data_gumthdmii_MOD_global_brb0stautau", "model_data_gumthdmii_mp_global_brb0stautau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBmunu, Freal8, ("__model_data_gumthdmii_MOD_global_brbmunu", "model_data_gumthdmii_mp_global_brbmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBsGamma, Freal8, ("__model_data_gumthdmii_MOD_global_brbsgamma", "model_data_gumthdmii_mp_global_brbsgamma_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtaunu, Freal8, ("__model_data_gumthdmii_MOD_global_brbtaunu", "model_data_gumthdmii_mp_global_brbtaunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoDnunu, Freal8, ("__model_data_gumthdmii_MOD_global_brbtodnunu", "model_data_gumthdmii_mp_global_brbtodnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoKee, Freal8, ("__model_data_gumthdmii_MOD_global_brbtokee", "model_data_gumthdmii_mp_global_brbtokee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoKmumu, Freal8, ("__model_data_gumthdmii_MOD_global_brbtokmumu", "model_data_gumthdmii_mp_global_brbtokmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoSEE, Freal8, ("__model_data_gumthdmii_MOD_global_brbtosee", "model_data_gumthdmii_mp_global_brbtosee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoSMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_brbtosmumu", "model_data_gumthdmii_mp_global_brbtosmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrBtoSnunu, Freal8, ("__model_data_gumthdmii_MOD_global_brbtosnunu", "model_data_gumthdmii_mp_global_brbtosnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrDmunu, Freal8, ("__model_data_gumthdmii_MOD_global_brdmunu", "model_data_gumthdmii_mp_global_brdmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrDsmunu, Freal8, ("__model_data_gumthdmii_MOD_global_brdsmunu", "model_data_gumthdmii_mp_global_brdsmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrDstaunu, Freal8, ("__model_data_gumthdmii_MOD_global_brdstaunu", "model_data_gumthdmii_mp_global_brdstaunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrK0eMu, Freal8, ("__model_data_gumthdmii_MOD_global_brk0emu", "model_data_gumthdmii_mp_global_brk0emu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrKltoPinunu, Freal8, ("__model_data_gumthdmii_MOD_global_brkltopinunu", "model_data_gumthdmii_mp_global_brkltopinunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrKmunu, Freal8, ("__model_data_gumthdmii_MOD_global_brkmunu", "model_data_gumthdmii_mp_global_brkmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrKptoPipnunu, Freal8, ("__model_data_gumthdmii_MOD_global_brkptopipnunu", "model_data_gumthdmii_mp_global_brkptopipnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoEEta, Freal8, ("__model_data_gumthdmii_MOD_global_brtautoeeta", "model_data_gumthdmii_mp_global_brtautoeeta_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoEEtap, Freal8, ("__model_data_gumthdmii_MOD_global_brtautoeetap", "model_data_gumthdmii_mp_global_brtautoeetap_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoEPi, Freal8, ("__model_data_gumthdmii_MOD_global_brtautoepi", "model_data_gumthdmii_mp_global_brtautoepi_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoMuEta, Freal8, ("__model_data_gumthdmii_MOD_global_brtautomueta", "model_data_gumthdmii_mp_global_brtautomueta_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoMuEtap, Freal8, ("__model_data_gumthdmii_MOD_global_brtautomuetap", "model_data_gumthdmii_mp_global_brtautomuetap_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrTautoMuPi, Freal8, ("__model_data_gumthdmii_MOD_global_brtautomupi", "model_data_gumthdmii_mp_global_brtautomupi_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrZtoMuE, Freal8, ("__model_data_gumthdmii_MOD_global_brztomue", "model_data_gumthdmii_mp_global_brztomue_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrZtoTauE, Freal8, ("__model_data_gumthdmii_MOD_global_brztotaue", "model_data_gumthdmii_mp_global_brztotaue_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrZtoTauMu, Freal8, ("__model_data_gumthdmii_MOD_global_brztotaumu", "model_data_gumthdmii_mp_global_brztotaumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrhtoMuE, Freal8, ("__model_data_gumthdmii_MOD_global_brhtomue", "model_data_gumthdmii_mp_global_brhtomue_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrhtoTauE, Freal8, ("__model_data_gumthdmii_MOD_global_brhtotaue", "model_data_gumthdmii_mp_global_brhtotaue_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_BrhtoTauMu, Freal8, ("__model_data_gumthdmii_MOD_global_brhtotaumu", "model_data_gumthdmii_mp_global_brhtotaumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC7, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc7", "model_data_gumthdmii_mp_global_cc7_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC7SM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc7sm", "model_data_gumthdmii_mp_global_cc7sm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC7p, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc7p", "model_data_gumthdmii_mp_global_cc7p_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC7pSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc7psm", "model_data_gumthdmii_mp_global_cc7psm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC8, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc8", "model_data_gumthdmii_mp_global_cc8_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC8SM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc8sm", "model_data_gumthdmii_mp_global_cc8sm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC8p, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc8p", "model_data_gumthdmii_mp_global_cc8p_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CC8pSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_cc8psm", "model_data_gumthdmii_mp_global_cc8psm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuEAl, Freal8, ("__model_data_gumthdmii_MOD_global_crmueal", "model_data_gumthdmii_mp_global_crmueal_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuEAu, Freal8, ("__model_data_gumthdmii_MOD_global_crmueau", "model_data_gumthdmii_mp_global_crmueau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuEPb, Freal8, ("__model_data_gumthdmii_MOD_global_crmuepb", "model_data_gumthdmii_mp_global_crmuepb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuESb, Freal8, ("__model_data_gumthdmii_MOD_global_crmuesb", "model_data_gumthdmii_mp_global_crmuesb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuESr, Freal8, ("__model_data_gumthdmii_MOD_global_crmuesr", "model_data_gumthdmii_mp_global_crmuesr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_CRmuETi, Freal8, ("__model_data_gumthdmii_MOD_global_crmueti", "model_data_gumthdmii_mp_global_crmueti_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_DelMK, Freal8, ("__model_data_gumthdmii_MOD_global_delmk", "model_data_gumthdmii_mp_global_delmk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_DeltaMBq, Freal8, ("__model_data_gumthdmii_MOD_global_deltambq", "model_data_gumthdmii_mp_global_deltambq_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_DeltaMBs, Freal8, ("__model_data_gumthdmii_MOD_global_deltambs", "model_data_gumthdmii_mp_global_deltambs_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_EDMe, Freal8, ("__model_data_gumthdmii_MOD_global_edme", "model_data_gumthdmii_mp_global_edme_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_EDMmu, Freal8, ("__model_data_gumthdmii_MOD_global_edmmu", "model_data_gumthdmii_mp_global_edmmu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_EDMtau, Freal8, ("__model_data_gumthdmii_MOD_global_edmtau", "model_data_gumthdmii_mp_global_edmtau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_K1L, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_k1l", "model_data_gumthdmii_mp_global_k1l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_K1R, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_k1r", "model_data_gumthdmii_mp_global_k1r_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_K2L, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_k2l", "model_data_gumthdmii_mp_global_k2l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_K2R, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_k2r", "model_data_gumthdmii_mp_global_k2r_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsll", "model_data_gumthdmii_mp_global_o4dsll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsllsm", "model_data_gumthdmii_mp_global_o4dsllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dslr", "model_data_gumthdmii_mp_global_o4dslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dslrsm", "model_data_gumthdmii_mp_global_o4dslrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsrl", "model_data_gumthdmii_mp_global_o4dsrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsrlsm", "model_data_gumthdmii_mp_global_o4dsrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsrr", "model_data_gumthdmii_mp_global_o4dsrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dSRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dsrrsm", "model_data_gumthdmii_mp_global_o4dsrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtll", "model_data_gumthdmii_mp_global_o4dtll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtllsm", "model_data_gumthdmii_mp_global_o4dtllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtlr", "model_data_gumthdmii_mp_global_o4dtlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtlrsm", "model_data_gumthdmii_mp_global_o4dtlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtrl", "model_data_gumthdmii_mp_global_o4dtrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtrlsm", "model_data_gumthdmii_mp_global_o4dtrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtrr", "model_data_gumthdmii_mp_global_o4dtrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dTRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dtrrsm", "model_data_gumthdmii_mp_global_o4dtrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvll", "model_data_gumthdmii_mp_global_o4dvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvllsm", "model_data_gumthdmii_mp_global_o4dvllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvlr", "model_data_gumthdmii_mp_global_o4dvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvlrsm", "model_data_gumthdmii_mp_global_o4dvlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvrl", "model_data_gumthdmii_mp_global_o4dvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvrlsm", "model_data_gumthdmii_mp_global_o4dvrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvrr", "model_data_gumthdmii_mp_global_o4dvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4dVRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4dvrrsm", "model_data_gumthdmii_mp_global_o4dvrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsll", "model_data_gumthdmii_mp_global_o4lsll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSLLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsllcross", "model_data_gumthdmii_mp_global_o4lsllcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lslr", "model_data_gumthdmii_mp_global_o4lslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSLRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lslrcross", "model_data_gumthdmii_mp_global_o4lslrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsrl", "model_data_gumthdmii_mp_global_o4lsrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSRLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsrlcross", "model_data_gumthdmii_mp_global_o4lsrlcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsrr", "model_data_gumthdmii_mp_global_o4lsrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lSRRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lsrrcross", "model_data_gumthdmii_mp_global_o4lsrrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltll", "model_data_gumthdmii_mp_global_o4ltll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTLLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltllcross", "model_data_gumthdmii_mp_global_o4ltllcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltlr", "model_data_gumthdmii_mp_global_o4ltlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTLRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltlrcross", "model_data_gumthdmii_mp_global_o4ltlrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltrl", "model_data_gumthdmii_mp_global_o4ltrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTRLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltrlcross", "model_data_gumthdmii_mp_global_o4ltrlcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltrr", "model_data_gumthdmii_mp_global_o4ltrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lTRRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4ltrrcross", "model_data_gumthdmii_mp_global_o4ltrrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvll", "model_data_gumthdmii_mp_global_o4lvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVLLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvllcross", "model_data_gumthdmii_mp_global_o4lvllcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvlr", "model_data_gumthdmii_mp_global_o4lvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVLRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvlrcross", "model_data_gumthdmii_mp_global_o4lvlrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvrl", "model_data_gumthdmii_mp_global_o4lvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVRLcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvrlcross", "model_data_gumthdmii_mp_global_o4lvrlcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvrr", "model_data_gumthdmii_mp_global_o4lvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_O4lVRRcross, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_o4lvrrcross", "model_data_gumthdmii_mp_global_o4lvrrcross_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA1L, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa1l", "model_data_gumthdmii_mp_global_oa1l_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA1R, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa1r", "model_data_gumthdmii_mp_global_oa1r_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2lSL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2lsl", "model_data_gumthdmii_mp_global_oa2lsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2lSR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2lsr", "model_data_gumthdmii_mp_global_oa2lsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qSL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qsl", "model_data_gumthdmii_mp_global_oa2qsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qSLSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qslsm", "model_data_gumthdmii_mp_global_oa2qslsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qSR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qsr", "model_data_gumthdmii_mp_global_oa2qsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qSRSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qsrsm", "model_data_gumthdmii_mp_global_oa2qsrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qVL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qvl", "model_data_gumthdmii_mp_global_oa2qvl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qVLSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qvlsm", "model_data_gumthdmii_mp_global_oa2qvlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qVR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qvr", "model_data_gumthdmii_mp_global_oa2qvr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OA2qVRSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oa2qvrsm", "model_data_gumthdmii_mp_global_oa2qvrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OAh2qSL, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oah2qsl", "model_data_gumthdmii_mp_global_oah2qsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OAh2qSLSM, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oah2qslsm", "model_data_gumthdmii_mp_global_oah2qslsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OAh2qSR, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oah2qsr", "model_data_gumthdmii_mp_global_oah2qsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OAh2qSRSM, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oah2qsrsm", "model_data_gumthdmii_mp_global_oah2qsrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OG2qSL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_og2qsl", "model_data_gumthdmii_mp_global_og2qsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OG2qSLSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_og2qslsm", "model_data_gumthdmii_mp_global_og2qslsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OG2qSR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_og2qsr", "model_data_gumthdmii_mp_global_og2qsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OG2qSRSM, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_og2qsrsm", "model_data_gumthdmii_mp_global_og2qsrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2lSL, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2lsl", "model_data_gumthdmii_mp_global_oh2lsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2lSR, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2lsr", "model_data_gumthdmii_mp_global_oh2lsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2qSL, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2qsl", "model_data_gumthdmii_mp_global_oh2qsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2qSLSM, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2qslsm", "model_data_gumthdmii_mp_global_oh2qslsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2qSR, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2qsr", "model_data_gumthdmii_mp_global_oh2qsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OH2qSRSM, Farray_Fcomplex16_1_3_1_3_1_2, ("__model_data_gumthdmii_MOD_global_oh2qsrsm", "model_data_gumthdmii_mp_global_oh2qsrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OZ2lSL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oz2lsl", "model_data_gumthdmii_mp_global_oz2lsl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OZ2lSR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oz2lsr", "model_data_gumthdmii_mp_global_oz2lsr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OZ2lVL, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oz2lvl", "model_data_gumthdmii_mp_global_oz2lvl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OZ2lVR, Farray_Fcomplex16_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oz2lvr", "model_data_gumthdmii_mp_global_oz2lvr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsll", "model_data_gumthdmii_mp_global_oddllsll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsllsm", "model_data_gumthdmii_mp_global_oddllsllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllslr", "model_data_gumthdmii_mp_global_oddllslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllslrsm", "model_data_gumthdmii_mp_global_oddllslrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsrl", "model_data_gumthdmii_mp_global_oddllsrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsrlsm", "model_data_gumthdmii_mp_global_oddllsrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsrr", "model_data_gumthdmii_mp_global_oddllsrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllSRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllsrrsm", "model_data_gumthdmii_mp_global_oddllsrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltll", "model_data_gumthdmii_mp_global_oddlltll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltllsm", "model_data_gumthdmii_mp_global_oddlltllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltlr", "model_data_gumthdmii_mp_global_oddlltlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltlrsm", "model_data_gumthdmii_mp_global_oddlltlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltrl", "model_data_gumthdmii_mp_global_oddlltrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltrlsm", "model_data_gumthdmii_mp_global_oddlltrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltrr", "model_data_gumthdmii_mp_global_oddlltrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllTRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddlltrrsm", "model_data_gumthdmii_mp_global_oddlltrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvll", "model_data_gumthdmii_mp_global_oddllvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvllsm", "model_data_gumthdmii_mp_global_oddllvllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvlr", "model_data_gumthdmii_mp_global_oddllvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvlrsm", "model_data_gumthdmii_mp_global_oddllvlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvrl", "model_data_gumthdmii_mp_global_oddllvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvrlsm", "model_data_gumthdmii_mp_global_oddllvrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvrr", "model_data_gumthdmii_mp_global_oddllvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddllVRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddllvrrsm", "model_data_gumthdmii_mp_global_oddllvrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvll", "model_data_gumthdmii_mp_global_oddvvvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvllsm", "model_data_gumthdmii_mp_global_oddvvvllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvlr", "model_data_gumthdmii_mp_global_oddvvvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvlrsm", "model_data_gumthdmii_mp_global_oddvvvlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvrl", "model_data_gumthdmii_mp_global_oddvvvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvrlsm", "model_data_gumthdmii_mp_global_oddvvvrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvrr", "model_data_gumthdmii_mp_global_oddvvvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OddvvVRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_oddvvvrrsm", "model_data_gumthdmii_mp_global_oddvvvrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsll", "model_data_gumthdmii_mp_global_odulvsll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsllsm", "model_data_gumthdmii_mp_global_odulvsllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvslr", "model_data_gumthdmii_mp_global_odulvslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvslrsm", "model_data_gumthdmii_mp_global_odulvslrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsrl", "model_data_gumthdmii_mp_global_odulvsrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsrlsm", "model_data_gumthdmii_mp_global_odulvsrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsrr", "model_data_gumthdmii_mp_global_odulvsrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvSRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvsrrsm", "model_data_gumthdmii_mp_global_odulvsrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvll", "model_data_gumthdmii_mp_global_odulvvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVLLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvllsm", "model_data_gumthdmii_mp_global_odulvvllsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvlr", "model_data_gumthdmii_mp_global_odulvvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVLRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvlrsm", "model_data_gumthdmii_mp_global_odulvvlrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvrl", "model_data_gumthdmii_mp_global_odulvvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVRLSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvrlsm", "model_data_gumthdmii_mp_global_odulvvrlsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvrr", "model_data_gumthdmii_mp_global_odulvvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OdulvVRRSM, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_odulvvrrsm", "model_data_gumthdmii_mp_global_odulvvrrsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddsll", "model_data_gumthdmii_mp_global_ollddsll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddslr", "model_data_gumthdmii_mp_global_ollddslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddsrl", "model_data_gumthdmii_mp_global_ollddsrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddsrr", "model_data_gumthdmii_mp_global_ollddsrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddTLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddtll", "model_data_gumthdmii_mp_global_ollddtll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddTLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddtlr", "model_data_gumthdmii_mp_global_ollddtlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddTRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddtrl", "model_data_gumthdmii_mp_global_ollddtrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddTRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddtrr", "model_data_gumthdmii_mp_global_ollddtrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddvll", "model_data_gumthdmii_mp_global_ollddvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddvlr", "model_data_gumthdmii_mp_global_ollddvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddvrl", "model_data_gumthdmii_mp_global_ollddvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OllddVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_ollddvrr", "model_data_gumthdmii_mp_global_ollddvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuSLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluusll", "model_data_gumthdmii_mp_global_olluusll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuSLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluuslr", "model_data_gumthdmii_mp_global_olluuslr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuSRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluusrl", "model_data_gumthdmii_mp_global_olluusrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuSRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluusrr", "model_data_gumthdmii_mp_global_olluusrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuTLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluutll", "model_data_gumthdmii_mp_global_olluutll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuTLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluutlr", "model_data_gumthdmii_mp_global_olluutlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuTRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluutrl", "model_data_gumthdmii_mp_global_olluutrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuTRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluutrr", "model_data_gumthdmii_mp_global_olluutrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuVLL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluuvll", "model_data_gumthdmii_mp_global_olluuvll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuVLR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluuvlr", "model_data_gumthdmii_mp_global_olluuvlr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuVRL, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluuvrl", "model_data_gumthdmii_mp_global_olluuvrl_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_OlluuVRR, Farray_Fcomplex16_1_3_1_3_1_3_1_3, ("__model_data_gumthdmii_MOD_global_olluuvrr", "model_data_gumthdmii_mp_global_olluuvrr_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_RK, Freal8, ("__model_data_gumthdmii_MOD_global_rk", "model_data_gumthdmii_mp_global_rk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_RKSM, Freal8, ("__model_data_gumthdmii_MOD_global_rksm", "model_data_gumthdmii_mp_global_rksm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_Spar, Freal8, ("__model_data_gumthdmii_MOD_global_spar", "model_data_gumthdmii_mp_global_spar_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_Tpar, Freal8, ("__model_data_gumthdmii_MOD_global_tpar", "model_data_gumthdmii_mp_global_tpar_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_Upar, Freal8, ("__model_data_gumthdmii_MOD_global_upar", "model_data_gumthdmii_mp_global_upar_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ae, Freal8, ("__model_data_gumthdmii_MOD_global_ae", "model_data_gumthdmii_mp_global_ae_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_amu, Freal8, ("__model_data_gumthdmii_MOD_global_amu", "model_data_gumthdmii_mp_global_amu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_atau, Freal8, ("__model_data_gumthdmii_MOD_global_atau", "model_data_gumthdmii_mp_global_atau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_cplHiggsGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_global_cplhiggsgg", "model_data_gumthdmii_mp_global_cplhiggsgg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_cplHiggsPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_global_cplhiggspp", "model_data_gumthdmii_mp_global_cplhiggspp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_cplPseudoHiggsGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_global_cplpseudohiggsgg", "model_data_gumthdmii_mp_global_cplpseudohiggsgg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_cplPseudoHiggsPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_global_cplpseudohiggspp", "model_data_gumthdmii_mp_global_cplpseudohiggspp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_dRho, Freal8, ("__model_data_gumthdmii_MOD_global_drho", "model_data_gumthdmii_mp_global_drho_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_epsK, Freal8, ("__model_data_gumthdmii_MOD_global_epsk", "model_data_gumthdmii_mp_global_epsk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_muEgamma, Freal8, ("__model_data_gumthdmii_MOD_global_muegamma", "model_data_gumthdmii_mp_global_muegamma_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0dEE, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0dee", "model_data_gumthdmii_mp_global_ratiob0dee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0dMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0dmumu", "model_data_gumthdmii_mp_global_ratiob0dmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0dTauTau, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0dtautau", "model_data_gumthdmii_mp_global_ratiob0dtautau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0sEE, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0see", "model_data_gumthdmii_mp_global_ratiob0see_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0sMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0smumu", "model_data_gumthdmii_mp_global_ratiob0smumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioB0sTauTau, Freal8, ("__model_data_gumthdmii_MOD_global_ratiob0stautau", "model_data_gumthdmii_mp_global_ratiob0stautau_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBmunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobmunu", "model_data_gumthdmii_mp_global_ratiobmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBsGamma, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobsgamma", "model_data_gumthdmii_mp_global_ratiobsgamma_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtaunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtaunu", "model_data_gumthdmii_mp_global_ratiobtaunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoDnunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtodnunu", "model_data_gumthdmii_mp_global_ratiobtodnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoKee, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtokee", "model_data_gumthdmii_mp_global_ratiobtokee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoKmumu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtokmumu", "model_data_gumthdmii_mp_global_ratiobtokmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoSEE, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtosee", "model_data_gumthdmii_mp_global_ratiobtosee_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoSMuMu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtosmumu", "model_data_gumthdmii_mp_global_ratiobtosmumu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioBtoSnunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiobtosnunu", "model_data_gumthdmii_mp_global_ratiobtosnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDelMK, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodelmk", "model_data_gumthdmii_mp_global_ratiodelmk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDeltaMBq, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodeltambq", "model_data_gumthdmii_mp_global_ratiodeltambq_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDeltaMBs, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodeltambs", "model_data_gumthdmii_mp_global_ratiodeltambs_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDmunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodmunu", "model_data_gumthdmii_mp_global_ratiodmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDsmunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodsmunu", "model_data_gumthdmii_mp_global_ratiodsmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioDstaunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiodstaunu", "model_data_gumthdmii_mp_global_ratiodstaunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioK0eMu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiok0emu", "model_data_gumthdmii_mp_global_ratiok0emu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioKltoPinunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiokltopinunu", "model_data_gumthdmii_mp_global_ratiokltopinunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioKmunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiokmunu", "model_data_gumthdmii_mp_global_ratiokmunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioKptoPipnunu, Freal8, ("__model_data_gumthdmii_MOD_global_ratiokptopipnunu", "model_data_gumthdmii_mp_global_ratiokptopipnunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_ratioepsK, Freal8, ("__model_data_gumthdmii_MOD_global_ratioepsk", "model_data_gumthdmii_mp_global_ratioepsk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_tauEgamma, Freal8, ("__model_data_gumthdmii_MOD_global_tauegamma", "model_data_gumthdmii_mp_global_tauegamma_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(global_tauMuGamma, Freal8, ("__model_data_gumthdmii_MOD_global_taumugamma", "model_data_gumthdmii_mp_global_taumugamma_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam1, Fcomplex16, ("__model_data_gumthdmii_MOD_lam1", "model_data_gumthdmii_mp_lam1_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam1GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_lam1gut", "model_data_gumthdmii_mp_lam1gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam1IN, Fcomplex16, ("__model_data_gumthdmii_MOD_lam1in", "model_data_gumthdmii_mp_lam1in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam1MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_lam1mz", "model_data_gumthdmii_mp_lam1mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam2, Fcomplex16, ("__model_data_gumthdmii_MOD_lam2", "model_data_gumthdmii_mp_lam2_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam2GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_lam2gut", "model_data_gumthdmii_mp_lam2gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam2IN, Fcomplex16, ("__model_data_gumthdmii_MOD_lam2in", "model_data_gumthdmii_mp_lam2in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam2MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_lam2mz", "model_data_gumthdmii_mp_lam2mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam3, Fcomplex16, ("__model_data_gumthdmii_MOD_lam3", "model_data_gumthdmii_mp_lam3_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam3GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_lam3gut", "model_data_gumthdmii_mp_lam3gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam3IN, Fcomplex16, ("__model_data_gumthdmii_MOD_lam3in", "model_data_gumthdmii_mp_lam3in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam3MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_lam3mz", "model_data_gumthdmii_mp_lam3mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam4, Fcomplex16, ("__model_data_gumthdmii_MOD_lam4", "model_data_gumthdmii_mp_lam4_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam4GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_lam4gut", "model_data_gumthdmii_mp_lam4gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam4IN, Fcomplex16, ("__model_data_gumthdmii_MOD_lam4in", "model_data_gumthdmii_mp_lam4in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam4MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_lam4mz", "model_data_gumthdmii_mp_lam4mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam5, Fcomplex16, ("__model_data_gumthdmii_MOD_lam5", "model_data_gumthdmii_mp_lam5_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam5GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_lam5gut", "model_data_gumthdmii_mp_lam5gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam5IN, Fcomplex16, ("__model_data_gumthdmii_MOD_lam5in", "model_data_gumthdmii_mp_lam5in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam5MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_lam5mz", "model_data_gumthdmii_mp_lam5mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m112, Fcomplex16, ("__model_data_gumthdmii_MOD_m112", "model_data_gumthdmii_mp_m112_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m112GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_m112gut", "model_data_gumthdmii_mp_m112gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m112IN, Fcomplex16, ("__model_data_gumthdmii_MOD_m112in", "model_data_gumthdmii_mp_m112in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m112MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_m112mz", "model_data_gumthdmii_mp_m112mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m122, Fcomplex16, ("__model_data_gumthdmii_MOD_m122", "model_data_gumthdmii_mp_m122_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m122GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_m122gut", "model_data_gumthdmii_mp_m122gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m122IN, Fcomplex16, ("__model_data_gumthdmii_MOD_m122in", "model_data_gumthdmii_mp_m122in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m122MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_m122mz", "model_data_gumthdmii_mp_m122mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m222, Fcomplex16, ("__model_data_gumthdmii_MOD_m222", "model_data_gumthdmii_mp_m222_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m222GUT, Fcomplex16, ("__model_data_gumthdmii_MOD_m222gut", "model_data_gumthdmii_mp_m222gut_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m222IN, Fcomplex16, ("__model_data_gumthdmii_MOD_m222in", "model_data_gumthdmii_mp_m222in_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m222MZ, Fcomplex16, ("__model_data_gumthdmii_MOD_m222mz", "model_data_gumthdmii_mp_m222mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(m32, Freal8, ("__model_data_gumthdmii_MOD_m32", "model_data_gumthdmii_mp_m32_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mass_uncertainty_Q, Farray_Freal8_1_15, ("__model_data_gumthdmii_MOD_mass_uncertainty_q", "model_data_gumthdmii_mp_mass_uncertainty_q_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mass_uncertainty_Yt, Farray_Freal8_1_15, ("__model_data_gumthdmii_MOD_mass_uncertainty_yt", "model_data_gumthdmii_mp_mass_uncertainty_yt_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioFd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiofd", "model_data_gumthdmii_mp_ratiofd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioFe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiofe", "model_data_gumthdmii_mp_ratiofe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioFu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiofu", "model_data_gumthdmii_mp_ratiofu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioHm, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_ratiohm", "model_data_gumthdmii_mp_ratiohm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioVWm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_ratiovwm", "model_data_gumthdmii_mp_ratiovwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(tForTadpoles, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_tfortadpoles", "model_data_gumthdmii_mp_tfortadpoles_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(tanb, Freal8, ("__model_data_gumthdmii_MOD_tanb", "model_data_gumthdmii_mp_tanb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(tanb_mZ, Freal8, ("__model_data_gumthdmii_MOD_tanb_mz", "model_data_gumthdmii_mp_tanb_mz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(tanbetaMZ, Freal8, ("__model_data_gumthdmii_MOD_tanbetamz", "model_data_gumthdmii_mp_tanbetamz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(temporaryValue, Fcomplex16, ("__model_data_gumthdmii_MOD_temporaryvalue", "model_data_gumthdmii_mp_temporaryvalue_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(unitarity_s_best, Freal8, ("__model_data_gumthdmii_MOD_unitarity_s_best", "model_data_gumthdmii_mp_unitarity_s_best_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(unitarity_s_max, Freal8, ("__model_data_gumthdmii_MOD_unitarity_s_max", "model_data_gumthdmii_mp_unitarity_s_max_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(unitarity_s_min, Freal8, ("__model_data_gumthdmii_MOD_unitarity_s_min", "model_data_gumthdmii_mp_unitarity_s_min_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(unitarity_steps, Finteger, ("__model_data_gumthdmii_MOD_unitarity_steps", "model_data_gumthdmii_mp_unitarity_steps_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(v, Freal8, ("__model_data_gumthdmii_MOD_v", "model_data_gumthdmii_mp_v_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vSM_Q, Freal8, ("__model_data_gumthdmii_MOD_vsm_q", "model_data_gumthdmii_mp_vsm_q_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vd, Freal8, ("__model_data_gumthdmii_MOD_vd", "model_data_gumthdmii_mp_vd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vdFix, Freal8, ("__model_data_gumthdmii_MOD_vdfix", "model_data_gumthdmii_mp_vdfix_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vdIN, Freal8, ("__model_data_gumthdmii_MOD_vdin", "model_data_gumthdmii_mp_vdin_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vdMZ, Freal8, ("__model_data_gumthdmii_MOD_vdmz", "model_data_gumthdmii_mp_vdmz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vdSUSY, Freal8, ("__model_data_gumthdmii_MOD_vdsusy", "model_data_gumthdmii_mp_vdsusy_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vevSM, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_vevsm", "model_data_gumthdmii_mp_vevsm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vu, Freal8, ("__model_data_gumthdmii_MOD_vu", "model_data_gumthdmii_mp_vu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vuFix, Freal8, ("__model_data_gumthdmii_MOD_vufix", "model_data_gumthdmii_mp_vufix_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vuIN, Freal8, ("__model_data_gumthdmii_MOD_vuin", "model_data_gumthdmii_mp_vuin_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vuMZ, Freal8, ("__model_data_gumthdmii_MOD_vumz", "model_data_gumthdmii_mp_vumz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(vuSUSY, Freal8, ("__model_data_gumthdmii_MOD_vususy", "model_data_gumthdmii_mp_vususy_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HighScaleModel, Fstring<15>, ("__settings_MOD_highscalemodel", "settings_mp_highscalemodel_"), "SARAHSPheno_gumTHDMII_internal")

// SMINPUT Variables
BE_VARIABLE(mZ, Freal8, ("__standardmodel_MOD_mz", "standardmodel_mp_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mZ2, Freal8,  ("__standardmodel_MOD_mz2", "standardmodel_mp_mz2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gamZ, Freal8, ("__standardmodel_MOD_gamz", "standardmodel_mp_gamz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gamZ2, Freal8, ("__standardmodel_MOD_gamz2", "standardmodel_mp_gamz2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gmZ, Freal8, ("__standardmodel_MOD_gmz", "standardmodel_mp_gmz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gmZ2, Freal8, ("__standardmodel_MOD_gmz2", "standardmodel_mp_gmz2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BrZqq, Farray_Freal8_1_5, ("__standardmodel_MOD_brzqq", "standardmodel_mp_brzqq_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BrZll, Farray_Freal8_1_3, ("__standardmodel_MOD_brzll", "standardmodel_mp_brzll_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BrZinv, Freal8, ("__standardmodel_MOD_brzinv", "standardmodel_mp_brzinv_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mW, Freal8, ("__standardmodel_MOD_mw", "standardmodel_mp_mw_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mW_SM, Freal8, ("__model_data_gumthdmii_MOD_mw_sm", "model_data_gumthdmii_mp_mw_sm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mW2, Freal8, ("__standardmodel_MOD_mw2", "standardmodel_mp_mw2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gamW, Freal8, ("__standardmodel_MOD_gamw", "standardmodel_mp_gamw_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gamW2, Freal8, ("__standardmodel_MOD_gamw2", "standardmodel_mp_gamw2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gmW, Freal8, ("__standardmodel_MOD_gmw", "standardmodel_mp_gmw_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gmW2, Freal8, ("__standardmodel_MOD_gmw2", "standardmodel_mp_gmw2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BrWqq, Farray_Freal8_1_2, ("__standardmodel_MOD_brwqq", "standardmodel_mp_brwqq_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BrWln, Farray_Freal8_1_3, ("__standardmodel_MOD_brwln", "standardmodel_mp_brwln_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_l, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l", "standardmodel_mp_mf_l_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_l_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l_mz", "standardmodel_mp_mf_l_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_nu, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_nu", "standardmodel_mp_mf_nu_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_u, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u", "standardmodel_mp_mf_u_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_u_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u_mz", "standardmodel_mp_mf_u_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_d, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d", "standardmodel_mp_mf_d_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_d_mZ, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d_mz", "standardmodel_mp_mf_d_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_l2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_l2", "standardmodel_mp_mf_l2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_u2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_u2", "standardmodel_mp_mf_u2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mf_d2, Farray_Freal8_1_3, ("__standardmodel_MOD_mf_d2", "standardmodel_mp_mf_d2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(sinW2, Freal8, ("__sphenogumthdmii_MOD_sinw2", "sphenogumthdmii_mp_sinw2_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MNuR, Freal8, ("__model_data_MOD_mnur", "model_data_mp_mnur_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Q_light_quarks, Freal8, ("__standardmodel_MOD_q_light_quarks", "standardmodel_mp_q_light_quarks_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Delta_Alpha_Lepton, Freal8, ("__standardmodel_MOD_delta_alpha_lepton", "standardmodel_mp_delta_alpha_lepton_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Delta_Alpha_Hadron, Freal8, ("__standardmodel_MOD_delta_alpha_hadron", "standardmodel_mp_delta_alpha_hadron_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Alpha, Freal8, ("__standardmodel_MOD_alpha", "standardmodel_mp_alpha_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Alpha_mZ, Freal8, ("__standardmodel_MOD_alpha_mz", "standardmodel_mp_alpha_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Alpha_mZ_MS, Freal8, ("__standardmodel_MOD_alpha_mz_ms", "standardmodel_mp_alpha_mz_ms_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MZ_input, Flogical, ("__model_data_gumthdmii_MOD_mz_input", "model_data_gumthdmii_mp_mz_input_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(AlphaS_mZ, Freal8, ("__standardmodel_MOD_alphas_mz", "standardmodel_mp_alphas_mz_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(G_F, Freal8, ("__standardmodel_MOD_g_f", "standardmodel_mp_g_f_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(KFactorLee, Freal8, ("__standardmodel_MOD_kfactorlee", "standardmodel_mp_kfactorlee_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CKM, Farray_Fcomplex16_1_3_1_3, ("__standardmodel_MOD_ckm", "standardmodel_mp_ckm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(lam_wolf, Freal8, ("__standardmodel_MOD_lam_wolf", "standardmodel_mp_lam_wolf_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(A_wolf, Freal8, ("__standardmodel_MOD_a_wolf", "standardmodel_mp_a_wolf_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rho_wolf, Freal8, ("__standardmodel_MOD_rho_wolf", "standardmodel_mp_rho_wolf_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(eta_wolf, Freal8, ("__standardmodel_MOD_eta_wolf", "standardmodel_mp_eta_wolf_"), "SARAHSPheno_gumTHDMII_internal")

// Control Variables
BE_VARIABLE(CTBD, Flogical, ("__sphenogumthdmii_MOD_calctbd", "sphenogumthdmii_mp_calctbd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(epsI, Freal8, ("__sphenogumthdmii_MOD_epsi", "sphenogumthdmii_mp_epsi_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(deltaM, Freal8, ("__sphenogumthdmii_MOD_deltam", "sphenogumthdmii_mp_deltam_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(kont, Finteger, ("__sphenogumthdmii_MOD_kont", "sphenogumthdmii_mp_kont_"), "SARAHSPheno_gumTHDMII_internal")

// Settings
BE_VARIABLE(Calculate_mh_within_SM, Flogical, ("__settings_MOD_calculate_mh_within_sm", "settings_mp_calculate_mh_within_sm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalculateLowEnergy, Flogical, ("__settings_MOD_calculatelowenergy", "settings_mp_calculatelowenergy_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalculateMSSM2Loop, Flogical, ("__settings_MOD_calculatemssm2loop", "settings_mp_calculatemssm2loop_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalculateOneLoopMasses, Flogical, ("__settings_MOD_calculateoneloopmasses", "settings_mp_calculateoneloopmasses_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalculateTwoLoopHiggsMasses, Flogical, ("__settings_MOD_calculatetwoloophiggsmasses", "settings_mp_calculatetwoloophiggsmasses_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(DecoupleAtRenScale, Flogical, ("__settings_MOD_decoupleatrenscale", "settings_mp_decoupleatrenscale_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(delta_mass, Freal8, ("__control_MOD_delta_mass", "control_mp_delta_mass_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ErrCan, Finteger, ("__control_MOD_errcan", "control_mp_errcan_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ErrorLevel, Finteger, ("__control_MOD_errorlevel", "control_mp_errorlevel_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(External_Higgs, Flogical, ("__control_MOD_external_higgs", "control_mp_external_higgs_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(External_Spectrum, Flogical, ("__control_MOD_external_spectrum", "control_mp_external_spectrum_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(FermionMassResummation, Flogical, ("__control_MOD_fermionmassresummation", "control_mp_fermionmassresummation_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Force_mh_within_SM, Flogical, ("__settings_MOD_force_mh_within_sm", "settings_mp_force_mh_within_sm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ForceRealMatrices, Flogical, ("__settings_MOD_forcerealmatrices", "settings_mp_forcerealmatrices_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(FoundIterativeSolution, Flogical, ("__settings_MOD_founditerativesolution", "settings_mp_founditerativesolution_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(GaugelessLimit, Finteger, ("__settings_MOD_gaugelesslimit", "settings_mp_gaugelesslimit_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(GenerationMixing, Flogical, ("__control_MOD_generationmixing", "control_mp_generationmixing_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(HigherOrderDiboson, Flogical, ("__settings_MOD_higherorderdiboson", "settings_mp_higherorderdiboson_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(hstep_pn, Freal8, ("__settings_MOD_hstep_pn", "settings_mp_hstep_pn_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(hstep_sa, Freal8, ("__settings_MOD_hstep_sa", "settings_mp_hstep_sa_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Iname, Finteger, ("__control_MOD_iname", "control_mp_iname_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(include1l2lshift, Flogical, ("__settings_MOD_include1l2lshift", "settings_mp_include1l2lshift_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(IncludeBSMdeltaVB, Flogical, ("__settings_MOD_includebsmdeltavb", "settings_mp_includebsmdeltavb_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(IncludeDeltaVB, Flogical, ("__settings_MOD_includedeltavb", "settings_mp_includedeltavb_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(InOut_Error, Farray_Fstring60_1_15, ("__control_MOD_inout_error", "control_mp_inout_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(L_CS, Flogical, ("__control_MOD_l_cs", "control_mp_l_cs_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(LoopMass_Error, Farray_Fstring60_1_25, ("__control_MOD_loopmass_error", "control_mp_loopmass_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MatchingOrder, Finteger, ("__settings_MOD_matchingorder", "settings_mp_matchingorder_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MatchZWpoleMasses, Flogical, ("__settings_MOD_matchzwpolemasses", "settings_mp_matchzwpolemasses_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Math_Error, Farray_Fstring60_1_31, ("__control_MOD_math_error", "control_mp_math_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MathQP_Error, Farray_Fstring60_1_10, ("__control_MOD_mathqp_error", "control_mp_mathqp_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MaxMassLoop, Freal8, ("__settings_MOD_maxmassloop", "settings_mp_maxmassloop_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MaxMassNumericalZero, Freal8, ("__settings_MOD_maxmassnumericalzero", "settings_mp_maxmassnumericalzero_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(mGUT, Freal8, ("__sphenogumthdmii_MOD_mgut", "sphenogumthdmii_mp_mgut_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MinimalNumberIterations, Finteger, ("__settings_MOD_minimalnumberiterations", "settings_mp_minimalnumberiterations_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(n_run, Finteger, ("__control_MOD_n_run", "control_mp_n_run_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(NewGBC, Flogical, ("__settings_MOD_newgbc", "settings_mp_newgbc_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Non_Zero_Exit, Flogical, ("__control_MOD_non_zero_exit", "control_mp_non_zero_exit_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OutputForMG, Flogical, ("__settings_MOD_outputformg", "settings_mp_outputformg_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OutputForMO, Flogical, ("__settings_MOD_outputformo", "settings_mp_outputformo_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(PoleMassesInLoops, Flogical, ("__settings_MOD_polemassesinloops", "settings_mp_polemassesinloops_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(PrintDebugInformation, Flogical, ("__settings_MOD_printdebuginformation", "settings_mp_printdebuginformation_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(PurelyNumericalEffPot, Flogical, ("__settings_MOD_purelynumericaleffpot", "settings_mp_purelynumericaleffpot_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RunningSMparametersLowEnergy, Flogical, ("__settings_MOD_runningsmparameterslowenergy", "settings_mp_runningsmparameterslowenergy_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RunningSUSYparametersLowEnergy, Flogical, ("__settings_MOD_runningsusyparameterslowenergy", "settings_mp_runningsusyparameterslowenergy_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RXiNew, Freal8, ("__settings_MOD_rxinew", "settings_mp_rxinew_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SilenceOutput, Flogical, ("__control_MOD_silenceoutput", "control_mp_silenceoutput_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SM_Error, Farray_Fstring60_1_2, ("__control_MOD_sm_error", "control_mp_sm_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SPA_convention, Finteger, ("__settings_MOD_spa_convention", "settings_mp_spa_convention_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Sugra_Error, Farray_Fstring60_1_22, ("__control_MOD_sugra_error", "control_mp_sugra_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SusyM_Error, Farray_Fstring60_1_33, ("__control_MOD_susym_error", "control_mp_susym_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SwitchToSCKM, Flogical, ("__settings_MOD_switchtosckm", "settings_mp_switchtosckm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopHiggs_Error, Farray_Fstring60_1_9, ("__control_MOD_twoloophiggs_error", "control_mp_twoloophiggs_error_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopMethod, Finteger, ("__settings_MOD_twoloopmethod", "settings_mp_twoloopmethod_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopRegulatorMass, Freal8, ("__settings_MOD_twoloopregulatormass", "settings_mp_twoloopregulatormass_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopRGE, Flogical, ("__settings_MOD_twolooprge", "settings_mp_twolooprge_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(TwoLoopSafeMode, Flogical, ("__settings_MOD_twoloopsafemode", "settings_mp_twoloopsafemode_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WidthToBeInvisible, Freal8, ("__settings_MOD_widthtobeinvisible", "settings_mp_widthtobeinvisible_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Write_HiggsBounds, Flogical, ("__inputoutput_gumthdmii_MOD_write_higgsbounds", "inputoutput_gumthdmii_mp_write_higgsbounds_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Write_WCXF, Flogical, ("__settings_MOD_write_wcxf", "settings_mp_write_wcxf_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteGUTvalues, Flogical, ("__settings_MOD_writegutvalues", "settings_mp_writegutvalues_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteOut, Flogical, ("__control_MOD_writeout", "control_mp_writeout_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteOutputForNonConvergence, Flogical, ("__settings_MOD_writeoutputfornonconvergence", "settings_mp_writeoutputfornonconvergence_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteParametersAtQ, Flogical, ("__settings_MOD_writeparametersatq", "settings_mp_writeparametersatq_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteSLHA1, Flogical, ("__settings_MOD_writeslha1", "settings_mp_writeslha1_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(WriteTreeLevelTadpoleParameters, Flogical, ("__settings_MOD_writetreeleveltadpoleparameters", "settings_mp_writetreeleveltadpoleparameters_"), "SARAHSPheno_gumTHDMII_internal")


// Other variables
BE_VARIABLE(Qin, Freal8, ("__sphenogumthdmii_MOD_qin", "sphenogumthdmii_mp_qin_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioWoM, Freal8, ("__sphenogumthdmii_MOD_ratiowom", "sphenogumthdmii_mp_ratiowom_"),"SARAHSPheno_gumTHDMII_internal")

// Branching Ratio variables
BE_VARIABLE(L_BR, Flogical, ("__control_MOD_l_br", "control_mp_l_br_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Enable3BDecaysF, Flogical, ("__settings_MOD_enable3bdecaysf", "settings_mp_enable3bdecaysf_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Enable3BDecaysS, Flogical, ("__settings_MOD_enable3bdecayss", "settings_mp_enable3bdecayss_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(RunningCouplingsDecays, Flogical, ("__settings_MOD_runningcouplingsdecays", "settings_mp_runningcouplingsdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(MinWidth, Freal8, ("__settings_MOD_minwidth", "settings_mp_minwidth_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OneLoopDecays, Flogical, ("__settings_MOD_oneloopdecays", "settings_mp_oneloopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1LAh, Farray_Freal8_1_2_1_57, ("__model_data_gumthdmii_MOD_br1lah", "model_data_gumthdmii_mp_br1lah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1LFd, Farray_Freal8_1_3_1_24, ("__model_data_gumthdmii_MOD_br1lfd", "model_data_gumthdmii_mp_br1lfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1LFe, Farray_Freal8_1_3_1_21, ("__model_data_gumthdmii_MOD_br1lfe", "model_data_gumthdmii_mp_br1lfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1LFu, Farray_Freal8_1_3_1_24, ("__model_data_gumthdmii_MOD_br1lfu", "model_data_gumthdmii_mp_br1lfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1LHm, Farray_Freal8_1_2_1_28, ("__model_data_gumthdmii_MOD_br1lhm", "model_data_gumthdmii_mp_br1lhm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR1Lhh, Farray_Freal8_1_2_1_59, ("__model_data_gumthdmii_MOD_br1lhh", "model_data_gumthdmii_mp_br1lhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAAA, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_braaa", "model_data_gumthdmii_mp_braaa_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAAAijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_braaaijk", "model_data_gumthdmii_mp_braaaijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAAZ, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_braaz", "model_data_gumthdmii_mp_braaz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAHAijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_brahaijk", "model_data_gumthdmii_mp_brahaijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAHH, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brahh", "model_data_gumthdmii_mp_brahh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAHHijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_brahhijk", "model_data_gumthdmii_mp_brahhijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAHZ, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brahz", "model_data_gumthdmii_mp_brahz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAHpW, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brahpw", "model_data_gumthdmii_mp_brahpw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAh, Farray_Freal8_1_2_1_57, ("__model_data_gumthdmii_MOD_brah", "model_data_gumthdmii_mp_brah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRAll, Farray_Freal8_1_2_1_3_1_3, ("__model_data_gumthdmii_MOD_brall", "model_data_gumthdmii_mp_brall_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRFd, Farray_Freal8_1_3_1_159, ("__model_data_gumthdmii_MOD_brfd", "model_data_gumthdmii_mp_brfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRFe, Farray_Freal8_1_3_1_156, ("__model_data_gumthdmii_MOD_brfe", "model_data_gumthdmii_mp_brfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRFu, Farray_Freal8_1_3_1_159, ("__model_data_gumthdmii_MOD_brfu", "model_data_gumthdmii_mp_brfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHAA, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brhaa", "model_data_gumthdmii_mp_brhaa_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHAAijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_brhaaijk", "model_data_gumthdmii_mp_brhaaijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHAZ, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brhaz", "model_data_gumthdmii_mp_brhaz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHHAijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_brhhaijk", "model_data_gumthdmii_mp_brhhaijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHHH, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brhhh", "model_data_gumthdmii_mp_brhhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHHHijk, Farray_Freal8_1_2_1_2_1_2, ("__model_data_gumthdmii_MOD_brhhhijk", "model_data_gumthdmii_mp_brhhhijk_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHHZ, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brhhz", "model_data_gumthdmii_mp_brhhz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHhpW, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_brhhpw", "model_data_gumthdmii_mp_brhhpw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHll, Farray_Freal8_1_2_1_3_1_3, ("__model_data_gumthdmii_MOD_brhll", "model_data_gumthdmii_mp_brhll_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRHm, Farray_Freal8_1_2_1_28, ("__model_data_gumthdmii_MOD_brhm", "model_data_gumthdmii_mp_brhm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRhh, Farray_Freal8_1_2_1_59, ("__model_data_gumthdmii_MOD_brhh", "model_data_gumthdmii_mp_brhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRinvA, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_brinva", "model_data_gumthdmii_mp_brinva_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BRinvH, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_brinvh", "model_data_gumthdmii_mp_brinvh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1LAh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gt1lah", "model_data_gumthdmii_mp_gt1lah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1LFd, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gt1lfd", "model_data_gumthdmii_mp_gt1lfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1LFe, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gt1lfe", "model_data_gumthdmii_mp_gt1lfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1LFu, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gt1lfu", "model_data_gumthdmii_mp_gt1lfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1LHm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gt1lhm", "model_data_gumthdmii_mp_gt1lhm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gT1Lhh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gt1lhh", "model_data_gumthdmii_mp_gt1lhh_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gTAh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gtah", "model_data_gumthdmii_mp_gtah_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gTFd, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gtfd", "model_data_gumthdmii_mp_gtfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gTFe, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gtfe", "model_data_gumthdmii_mp_gtfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gTFu, Farray_Freal8_1_3, ("__model_data_gumthdmii_MOD_gtfu", "model_data_gumthdmii_mp_gtfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gTHm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gthm", "model_data_gumthdmii_mp_gthm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(gThh, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_gthh", "model_data_gumthdmii_mp_gthh_"),"SARAHSPheno_gumTHDMII_internal")

// Decay options
BE_VARIABLE(divonly_save, Finteger, ("__settings_MOD_divonly_save", "settings_mp_divonly_save_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(divergence_save, Freal8, ("__settings_MOD_divergence_save", "settings_mp_divergence_save_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(SimplisticLoopDecays, Flogical, ("__settings_MOD_simplisticloopdecays", "settings_mp_simplisticloopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ShiftIRdiv, Flogical, ("__settings_MOD_shiftirdiv", "settings_mp_shiftirdiv_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(DebugLoopDecays, Flogical, ("__settings_MOD_debugloopdecays", "settings_mp_debugloopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OnlyTreeLevelContributions, Flogical, ("__settings_MOD_onlytreelevelcontributions", "settings_mp_onlytreelevelcontributions_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ExternalZfactors, Flogical, ("__settings_MOD_externalzfactors", "settings_mp_externalzfactors_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(UseZeroRotationMatrices, Flogical, ("__settings_MOD_usezerorotationmatrices", "settings_mp_usezerorotationmatrices_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(UseP2Matrices, Flogical, ("__settings_MOD_usep2matrices", "settings_mp_usep2matrices_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(OSkinematics, Flogical, ("__settings_MOD_oskinematics", "settings_mp_oskinematics_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ewOSinDecays, Flogical, ("__settings_MOD_ewosindecays", "settings_mp_ewosindecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(yukOSinDecays, Flogical, ("__settings_MOD_yukosindecays", "settings_mp_yukosindecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CTinLoopDecays, Flogical, ("__settings_MOD_ctinloopdecays", "settings_mp_ctinloopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(LoopInducedDecaysOS, Flogical, ("__settings_MOD_loopinduceddecaysos", "settings_mp_loopinduceddecaysos_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Mass_Regulator_PhotonGluon, Freal8, ("__settings_MOD_mass_regulator_photongluon", "settings_mp_mass_regulator_photongluon_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Extra_Scale_LoopDecays, Flogical, ("__settings_MOD_extra_scale_loopdecays", "settings_mp_extra_scale_loopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Scale_LoopDecays, Freal8, ("__settings_MOD_scale_loopdecays", "settings_mp_scale_loopdecays_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Calc3BodyDecay_Fd, Flogical, ("__model_data_gumthdmii_MOD_calc3bodydecay_fd", "model_data_gumthdmii_mp_calc3bodydecay_fd_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Calc3BodyDecay_Fe, Flogical, ("__model_data_gumthdmii_MOD_calc3bodydecay_fe", "model_data_gumthdmii_mp_calc3bodydecay_fe_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(Calc3BodyDecay_Fu, Flogical, ("__model_data_gumthdmii_MOD_calc3bodydecay_fu", "model_data_gumthdmii_mp_calc3bodydecay_fu_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_Ah, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_ah", "model_data_gumthdmii_mp_calcloopdecay_ah_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_Fd, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_fd", "model_data_gumthdmii_mp_calcloopdecay_fd_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_Fe, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_fe", "model_data_gumthdmii_mp_calcloopdecay_fe_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_Hm, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_hm", "model_data_gumthdmii_mp_calcloopdecay_hm_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_LoopInducedOnly, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_loopinducedonly", "model_data_gumthdmii_mp_calcloopdecay_loopinducedonly_"), "SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CalcLoopDecay_hh, Flogical, ("__model_data_gumthdmii_MOD_calcloopdecay_hh", "model_data_gumthdmii_mp_calcloopdecay_hh_"), "SARAHSPheno_gumTHDMII_internal")

// HiggsBounds variables
BE_VARIABLE(BR_Hcb, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_hcb", "model_data_gumthdmii_mp_br_hcb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_Hcs, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_hcs", "model_data_gumthdmii_mp_br_hcs_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_HpAW, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_br_hpaw", "model_data_gumthdmii_mp_br_hpaw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_HpHW, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_br_hphw", "model_data_gumthdmii_mp_br_hphw_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_HpTB, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_hptb", "model_data_gumthdmii_mp_br_hptb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_HpWZ, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_hpwz", "model_data_gumthdmii_mp_br_hpwz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_Htaunu, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_htaunu", "model_data_gumthdmii_mp_br_htaunu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_tHb, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_br_thb", "model_data_gumthdmii_mp_br_thb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(BR_tWb, Freal8, ("__model_data_gumthdmii_MOD_br_twb", "model_data_gumthdmii_mp_br_twb_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CPL_A_A_Z, Farray_Fcomplex16_1_2_1_2, ("__model_data_gumthdmii_MOD_cpl_a_a_z", "model_data_gumthdmii_mp_cpl_a_a_z_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CPL_A_H_Z, Farray_Fcomplex16_1_2_1_2, ("__model_data_gumthdmii_MOD_cpl_a_h_z", "model_data_gumthdmii_mp_cpl_a_h_z_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(CPL_H_H_Z, Farray_Fcomplex16_1_2_1_2, ("__model_data_gumthdmii_MOD_cpl_h_h_z", "model_data_gumthdmii_mp_cpl_h_h_z_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_P_Fd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_p_fd", "model_data_gumthdmii_mp_rhb_p_p_fd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_P_Fe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_p_fe", "model_data_gumthdmii_mp_rhb_p_p_fe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_P_Fu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_p_fu", "model_data_gumthdmii_mp_rhb_p_p_fu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_P_Fv, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_p_fv", "model_data_gumthdmii_mp_rhb_p_p_fv_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_S_Fd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_s_fd", "model_data_gumthdmii_mp_rhb_p_s_fd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_S_Fe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_s_fe", "model_data_gumthdmii_mp_rhb_p_s_fe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_S_Fu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_p_s_fu", "model_data_gumthdmii_mp_rhb_p_s_fu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_S_Fv, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_s_fv", "model_data_gumthdmii_mp_rhb_p_s_fv_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_VG, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_vg", "model_data_gumthdmii_mp_rhb_p_vg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_VP, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_vp", "model_data_gumthdmii_mp_rhb_p_vp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_VWm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_vwm", "model_data_gumthdmii_mp_rhb_p_vwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_P_VZ, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_p_vz", "model_data_gumthdmii_mp_rhb_p_vz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_P_Fd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_p_fd", "model_data_gumthdmii_mp_rhb_s_p_fd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_P_Fe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_p_fe", "model_data_gumthdmii_mp_rhb_s_p_fe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_P_Fu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_p_fu", "model_data_gumthdmii_mp_rhb_s_p_fu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_P_Fv, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_p_fv", "model_data_gumthdmii_mp_rhb_s_p_fv_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_S_Fd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_s_fd", "model_data_gumthdmii_mp_rhb_s_s_fd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_S_Fe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_s_fe", "model_data_gumthdmii_mp_rhb_s_s_fe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_S_Fu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_rhb_s_s_fu", "model_data_gumthdmii_mp_rhb_s_s_fu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_S_Fv, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_s_fv", "model_data_gumthdmii_mp_rhb_s_s_fv_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_VG, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_vg", "model_data_gumthdmii_mp_rhb_s_vg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_VP, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_vp", "model_data_gumthdmii_mp_rhb_s_vp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_VWm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_vwm", "model_data_gumthdmii_mp_rhb_s_vwm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(rHB_S_VZ, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_rhb_s_vz", "model_data_gumthdmii_mp_rhb_s_vz_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_ratiogg", "model_data_gumthdmii_mp_ratiogg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPFd, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiopfd", "model_data_gumthdmii_mp_ratiopfd_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPFe, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiopfe", "model_data_gumthdmii_mp_ratiopfe_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPFu, Farray_Freal8_1_2_1_3, ("__model_data_gumthdmii_MOD_ratiopfu", "model_data_gumthdmii_mp_ratiopfu_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPGG, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_ratiopgg", "model_data_gumthdmii_mp_ratiopgg_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPHm, Farray_Freal8_1_2_1_2, ("__model_data_gumthdmii_MOD_ratiophm", "model_data_gumthdmii_mp_ratiophm_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_ratiopp", "model_data_gumthdmii_mp_ratiopp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPPP, Farray_Fcomplex16_1_2, ("__model_data_gumthdmii_MOD_ratioppp", "model_data_gumthdmii_mp_ratioppp_"),"SARAHSPheno_gumTHDMII_internal")
BE_VARIABLE(ratioPVWm, Farray_Freal8_1_2, ("__model_data_gumthdmii_MOD_ratiopvwm", "model_data_gumthdmii_mp_ratiopvwm_"),"SARAHSPheno_gumTHDMII_internal")

BE_CONV_FUNCTION(conv_Tpar, double, (), "SARAHSPheno_gumTHDMII_conv_Tpar")
BE_CONV_FUNCTION(conv_Spar, double, (), "SARAHSPheno_gumTHDMII_conv_Spar")
BE_CONV_FUNCTION(conv_Upar, double, (), "SARAHSPheno_gumTHDMII_conv_Upar")
BE_CONV_FUNCTION(conv_ae, double, (), "SARAHSPheno_gumTHDMII_conv_ae")
BE_CONV_FUNCTION(conv_amu, double, (), "SARAHSPheno_gumTHDMII_conv_amu")
BE_CONV_FUNCTION(conv_atau, double, (), "SARAHSPheno_gumTHDMII_conv_atau")
BE_CONV_FUNCTION(conv_EDMe, double, (), "SARAHSPheno_gumTHDMII_conv_EDMe")
BE_CONV_FUNCTION(conv_EDMmu, double, (), "SARAHSPheno_gumTHDMII_conv_EDMmu")
BE_CONV_FUNCTION(conv_EDMtau, double, (), "SARAHSPheno_gumTHDMII_conv_EDMtau")
BE_CONV_FUNCTION(conv_dRho, double, (), "SARAHSPheno_gumTHDMII_conv_dRho")

BE_CONV_FUNCTION(conv_BrBsGamma, double, (), "SARAHSPheno_gumTHDMII_conv_BrBsGamma")
BE_CONV_FUNCTION(conv_ratioBsGamma, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBsGamma")
BE_CONV_FUNCTION(conv_BrDmunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrDmunu")
BE_CONV_FUNCTION(conv_ratioDmunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDmunu")
BE_CONV_FUNCTION(conv_BrDsmunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrDsmunu")
BE_CONV_FUNCTION(conv_ratioDsmunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDsmunu")
BE_CONV_FUNCTION(conv_BrDstaunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrDstaunu")
BE_CONV_FUNCTION(conv_ratioDstaunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDstaunu")
BE_CONV_FUNCTION(conv_BrBmunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBmunu")
BE_CONV_FUNCTION(conv_ratioBmunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBmunu")
BE_CONV_FUNCTION(conv_BrBtaunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtaunu")
BE_CONV_FUNCTION(conv_ratioBtaunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtaunu")
BE_CONV_FUNCTION(conv_BrKmunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrKmunu")
BE_CONV_FUNCTION(conv_ratioKmunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioKmunu")
BE_CONV_FUNCTION(conv_RK, double, (), "SARAHSPheno_gumTHDMII_conv_RK")
BE_CONV_FUNCTION(conv_RKSM, double, (), "SARAHSPheno_gumTHDMII_conv_RKSM")
BE_CONV_FUNCTION(conv_muEgamma, double, (), "SARAHSPheno_gumTHDMII_conv_muEgamma")
BE_CONV_FUNCTION(conv_tauEgamma, double, (), "SARAHSPheno_gumTHDMII_conv_tauEgamma")
BE_CONV_FUNCTION(conv_tauMuGamma, double, (), "SARAHSPheno_gumTHDMII_conv_tauMuGamma")
BE_CONV_FUNCTION(conv_CRmuEAl, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuEAl")
BE_CONV_FUNCTION(conv_CRmuETi, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuETi")
BE_CONV_FUNCTION(conv_CRmuESr, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuESr")
BE_CONV_FUNCTION(conv_CRmuESb, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuESb")
BE_CONV_FUNCTION(conv_CRmuEAu, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuEAu")
BE_CONV_FUNCTION(conv_CRmuEPb, double, (), "SARAHSPheno_gumTHDMII_conv_CRmuEPb")
BE_CONV_FUNCTION(conv_BRmuTo3e, double, (), "SARAHSPheno_gumTHDMII_conv_BRmuTo3e")
BE_CONV_FUNCTION(conv_BRtauTo3e, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauTo3e")
BE_CONV_FUNCTION(conv_BRtauTo3mu, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauTo3mu")
BE_CONV_FUNCTION(conv_BRtauToemumu, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauToemumu")
BE_CONV_FUNCTION(conv_BRtauTomuee, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauTomuee")
BE_CONV_FUNCTION(conv_BRtauToemumu2, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauToemumu2")
BE_CONV_FUNCTION(conv_BRtauTomuee2, double, (), "SARAHSPheno_gumTHDMII_conv_BRtauTomuee2")
BE_CONV_FUNCTION(conv_BrZtoMuE, double, (), "SARAHSPheno_gumTHDMII_conv_BrZtoMuE")
BE_CONV_FUNCTION(conv_BrZtoTauE, double, (), "SARAHSPheno_gumTHDMII_conv_BrZtoTauE")
BE_CONV_FUNCTION(conv_BrZtoTauMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrZtoTauMu")
BE_CONV_FUNCTION(conv_BrhtoMuE, double, (), "SARAHSPheno_gumTHDMII_conv_BrhtoMuE")
BE_CONV_FUNCTION(conv_BrhtoTauE, double, (), "SARAHSPheno_gumTHDMII_conv_BrhtoTauE")
BE_CONV_FUNCTION(conv_BrhtoTauMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrhtoTauMu")
BE_CONV_FUNCTION(conv_DeltaMBs, double, (), "SARAHSPheno_gumTHDMII_conv_DeltaMBs")
BE_CONV_FUNCTION(conv_ratioDeltaMBs, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDeltaMBs")
BE_CONV_FUNCTION(conv_DeltaMBq, double, (), "SARAHSPheno_gumTHDMII_conv_DeltaMBq")
BE_CONV_FUNCTION(conv_ratioDeltaMBq, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDeltaMBq")
BE_CONV_FUNCTION(conv_BrTautoEPi, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoEPi")
BE_CONV_FUNCTION(conv_BrTautoEEta, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoEEta")
BE_CONV_FUNCTION(conv_BrTautoEEtap, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoEEtap")
BE_CONV_FUNCTION(conv_BrTautoMuPi, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoMuPi")
BE_CONV_FUNCTION(conv_BrTautoMuEta, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoMuEta")
BE_CONV_FUNCTION(conv_BrTautoMuEtap, double, (), "SARAHSPheno_gumTHDMII_conv_BrTautoMuEtap")
BE_CONV_FUNCTION(conv_BrB0dEE, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0dEE")
BE_CONV_FUNCTION(conv_ratioB0dEE, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0dEE")
BE_CONV_FUNCTION(conv_BrB0sEE, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0sEE")
BE_CONV_FUNCTION(conv_ratioB0sEE, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0sEE")
BE_CONV_FUNCTION(conv_BrB0dMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0dMuMu")
BE_CONV_FUNCTION(conv_ratioB0dMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0dMuMu")
BE_CONV_FUNCTION(conv_BrB0sMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0sMuMu")
BE_CONV_FUNCTION(conv_ratioB0sMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0sMuMu")
BE_CONV_FUNCTION(conv_BrB0dTauTau, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0dTauTau")
BE_CONV_FUNCTION(conv_ratioB0dTauTau, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0dTauTau")
BE_CONV_FUNCTION(conv_BrB0sTauTau, double, (), "SARAHSPheno_gumTHDMII_conv_BrB0sTauTau")
BE_CONV_FUNCTION(conv_ratioB0sTauTau, double, (), "SARAHSPheno_gumTHDMII_conv_ratioB0sTauTau")
BE_CONV_FUNCTION(conv_BrBtoSEE, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoSEE")
BE_CONV_FUNCTION(conv_ratioBtoSEE, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoSEE")
BE_CONV_FUNCTION(conv_BrBtoSMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoSMuMu")
BE_CONV_FUNCTION(conv_ratioBtoSMuMu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoSMuMu")
BE_CONV_FUNCTION(conv_BrBtoKee, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoKee")
BE_CONV_FUNCTION(conv_ratioBtoKee, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoKee")
BE_CONV_FUNCTION(conv_BrBtoKmumu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoKmumu")
BE_CONV_FUNCTION(conv_ratioBtoKmumu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoKmumu")
BE_CONV_FUNCTION(conv_BrBtoSnunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoSnunu")
BE_CONV_FUNCTION(conv_ratioBtoSnunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoSnunu")
BE_CONV_FUNCTION(conv_BrBtoDnunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrBtoDnunu")
BE_CONV_FUNCTION(conv_ratioBtoDnunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioBtoDnunu")
BE_CONV_FUNCTION(conv_BrKptoPipnunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrKptoPipnunu")
BE_CONV_FUNCTION(conv_ratioKptoPipnunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioKptoPipnunu")
BE_CONV_FUNCTION(conv_BrKltoPinunu, double, (), "SARAHSPheno_gumTHDMII_conv_BrKltoPinunu")
BE_CONV_FUNCTION(conv_ratioKltoPinunu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioKltoPinunu")
BE_CONV_FUNCTION(conv_BrK0eMu, double, (), "SARAHSPheno_gumTHDMII_conv_BrK0eMu")
BE_CONV_FUNCTION(conv_ratioK0eMu, double, (), "SARAHSPheno_gumTHDMII_conv_ratioK0eMu")
BE_CONV_FUNCTION(conv_DelMK, double, (), "SARAHSPheno_gumTHDMII_conv_DelMK")
BE_CONV_FUNCTION(conv_ratioDelMK, double, (), "SARAHSPheno_gumTHDMII_conv_ratioDelMK")
BE_CONV_FUNCTION(conv_epsK, double, (), "SARAHSPheno_gumTHDMII_conv_epsK")
BE_CONV_FUNCTION(conv_ratioepsK, double, (), "SARAHSPheno_gumTHDMII_conv_ratioepsK")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_SPheno, int, (Spectrum&, const Finputs&), "SARAHSPheno_gumTHDMII_spectrum")
BE_CONV_FUNCTION(run_SPheno_decays, int, (const Spectrum &, DecayTable &, const Finputs&), "SARAHSPheno_gumTHDMII_decays")
BE_CONV_FUNCTION(Spectrum_Out, Spectrum, (const Finputs&), "SARAHSPheno_gumTHDMII_internal")
BE_CONV_FUNCTION(get_HiggsCouplingsTable, int, (const Spectrum&, HiggsCouplingsTable&, const Finputs&), "SARAHSPheno_gumTHDMII_HiggsCouplingsTable")
BE_CONV_FUNCTION(ReadingData, void, (const Finputs&), "SARAHSPheno_gumTHDMII_internal")
BE_CONV_FUNCTION(ReadingData_decays, void, (const Finputs&), "SARAHSPheno_gumTHDMII_internal")
BE_CONV_FUNCTION(InitializeStandardModel, void, (const SMInputs&), "SARAHSPheno_gumTHDMII_internal")
BE_CONV_FUNCTION(ErrorHandling, void, (const int&), "SARAHSPheno_gumTHDMII_internal")

BE_CONV_FUNCTION(conv_get_effective_couplings, void, (const Spectrum&, map_str_dbl&), "SARAHSPheno_gumTHDMII_conv_get_effective_couplings")

// Initialisation functions (dependencies)

// Function pointer variable for error handling
BE_VARIABLE(ErrorHandler_cptr, fptr_void, ("__control_MOD_errorhandler_cptr", "control_mp_errorhandler_cptr_"), "SARAHSPheno_gumTHDMII_internal")

// End
#include "gambit/Backends/backend_undefs.hpp"
