//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Flavour EFTs
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Marcin Chrzaszcz & Martin White
//  2016 October
//
//  Jihyun Bhom
//  2020 January
//
//  Pat Scott
//  2022 May
//
//  *********************************************

#ifndef __WC_hpp__
#define __WC_hpp__


#define MODEL WC_LUV
  START_MODEL
  DEFINEPARS(Re_DeltaC7_tau, Im_DeltaC7_tau, Re_DeltaC9_tau, Im_DeltaC9_tau, Re_DeltaC10_tau, Im_DeltaC10_tau, Re_DeltaCQ1_tau, Im_DeltaCQ1_tau, Re_DeltaCQ2_tau, Im_DeltaCQ2_tau,
             Re_DeltaC7_mu, Im_DeltaC7_mu, Re_DeltaC9_mu, Im_DeltaC9_mu, Re_DeltaC10_mu, Im_DeltaC10_mu, Re_DeltaCQ1_mu, Im_DeltaCQ1_mu, Re_DeltaCQ2_mu, Im_DeltaCQ2_mu,
             Re_DeltaC7_e, Im_DeltaC7_e, Re_DeltaC9_e, Im_DeltaC9_e, Re_DeltaC10_e, Im_DeltaC10_e, Re_DeltaCQ1_e, Im_DeltaCQ1_e, Re_DeltaCQ2_e, Im_DeltaCQ2_e)
#undef MODEL


#define MODEL WC_LR
  START_MODEL
  DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2,
             Re_DeltaC7_Prime, Im_DeltaC7_Prime, Re_DeltaC9_Prime, Im_DeltaC9_Prime, Re_DeltaC10_Prime, Im_DeltaC10_Prime, Re_DeltaCQ1_Prime, Im_DeltaCQ1_Prime, Re_DeltaCQ2_Prime, Im_DeltaCQ2_Prime)
#undef MODEL


#define MODEL WC
  #define PARENT WC_LUV
    START_MODEL
    DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2)
    INTERPRET_AS_PARENT_FUNCTION(WC_to_WC_LUV)
    INTERPRET_AS_X_FUNCTION(WC_LR,WC_to_WC_LR)
  #undef PARENT
#undef MODEL


#endif
