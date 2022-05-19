///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Effective model of Flavour with WCs
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Marcin Chrzaszcz & Martin White
///  \date 2016 October
///
///  \author Jihyun Bhom
///  \date 2020 January
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 June
///
///  *********************************************

#ifndef __WC_hpp__   
#define __WC_hpp__   

// Most generic model, top of the hierarchy
#define MODEL GWC
   START_MODEL
   DEFINEPARS(Re_DeltaC2_tau, Im_DeltaC2_tau, Re_DeltaC7_tau, Im_DeltaC7_tau, Re_DeltaC8_tau, Im_DeltaC8_tau, Re_DeltaC9_tau, Im_DeltaC9_tau, Re_DeltaC10_tau, Im_DeltaC10_tau, Re_DeltaCQ1_tau, Im_DeltaCQ1_tau, Re_DeltaCQ2_tau, Im_DeltaCQ2_tau)
   DEFINEPARS(Re_DeltaC2_mu, Im_DeltaC2_mu, Re_DeltaC7_mu, Im_DeltaC7_mu, Re_DeltaC8_mu, Im_DeltaC8_mu, Re_DeltaC9_mu, Im_DeltaC9_mu, Re_DeltaC10_mu, Im_DeltaC10_mu, Re_DeltaCQ1_mu, Im_DeltaCQ1_mu, Re_DeltaCQ2_mu, Im_DeltaCQ2_mu)
   DEFINEPARS(Re_DeltaC2_e, Im_DeltaC2_e, Re_DeltaC7_e, Im_DeltaC7_e, Re_DeltaC8_e, Im_DeltaC8_e, Re_DeltaC9_e, Im_DeltaC9_e, Re_DeltaC10_e, Im_DeltaC10_e, Re_DeltaCQ1_e, Im_DeltaCQ1_e, Re_DeltaCQ2_e, Im_DeltaCQ2_e)
   DEFINEPARS(Re_DeltaC2_tau_Prime, Im_DeltaC2_tau_Prime, Re_DeltaC7_tau_Prime, Im_DeltaC7_tau_Prime, Re_DeltaC8_tau_Prime, Im_DeltaC8_tau_Prime, Re_DeltaC9_tau_Prime, Im_DeltaC9_tau_Prime, Re_DeltaC10_tau_Prime, Im_DeltaC10_tau_Prime, Re_DeltaCQ1_tau_Prime, Im_DeltaCQ1_tau_Prime, Re_DeltaCQ2_tau_Prime, Im_DeltaCQ2_tau_Prime)
   DEFINEPARS(Re_DeltaC2_mu_Prime, Im_DeltaC2_mu_Prime, Re_DeltaC7_mu_Prime, Im_DeltaC7_mu_Prime, Re_DeltaC8_mu_Prime, Im_DeltaC8_mu_Prime, Re_DeltaC9_mu_Prime, Im_DeltaC9_mu_Prime, Re_DeltaC10_mu_Prime, Im_DeltaC10_mu_Prime, Re_DeltaCQ1_mu_Prime, Im_DeltaCQ1_mu_Prime, Re_DeltaCQ2_mu_Prime, Im_DeltaCQ2_mu_Prime)
   DEFINEPARS(Re_DeltaC2_e_Prime, Im_DeltaC2_e_Prime, Re_DeltaC7_e_Prime, Im_DeltaC7_e_Prime, Re_DeltaC8_e_Prime, Im_DeltaC8_e_Prime, Re_DeltaC9_e_Prime, Im_DeltaC9_e_Prime, Re_DeltaC10_e_Prime, Im_DeltaC10_e_Prime, Re_DeltaCQ1_e_Prime, Im_DeltaCQ1_e_Prime, Re_DeltaCQ2_e_Prime, Im_DeltaCQ2_e_Prime)
#undef MODEL

// Simple WC model, only muon flavour
#define PARENT GWC
#define MODEL WC
   START_MODEL
   DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2)

  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_to_GWC)
#undef MODEL  
#undef PARENT

// WC model for lepton universality
#define PARENT GWC
#define MODEL WC_LUV
   START_MODEL
   DEFINEPARS(Re_DeltaC7_tau, Im_DeltaC7_tau, Re_DeltaC9_tau, Im_DeltaC9_tau, Re_DeltaC10_tau, Im_DeltaC10_tau, Re_DeltaCQ1_tau, Im_DeltaCQ1_tau, Re_DeltaCQ2_tau, Im_DeltaCQ2_tau)
   DEFINEPARS(Re_DeltaC7_mu, Im_DeltaC7_mu, Re_DeltaC9_mu, Im_DeltaC9_mu, Re_DeltaC10_mu, Im_DeltaC10_mu, Re_DeltaCQ1_mu, Im_DeltaCQ1_mu, Re_DeltaCQ2_mu, Im_DeltaCQ2_mu)
   DEFINEPARS(Re_DeltaC7_e, Im_DeltaC7_e, Re_DeltaC9_e, Im_DeltaC9_e, Re_DeltaC10_e, Im_DeltaC10_e, Re_DeltaCQ1_e, Im_DeltaCQ1_e, Re_DeltaCQ2_e, Im_DeltaCQ2_e)

  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_LUV_to_GWC)
#undef MODEL
#undef PARENT

// WC model with different chirality
#define PARENT GWC
#define MODEL WC_LR
   START_MODEL
   DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2)
   DEFINEPARS(Re_DeltaC7_Prime, Im_DeltaC7_Prime, Re_DeltaC9_Prime, Im_DeltaC9_Prime, Re_DeltaC10_Prime, Im_DeltaC10_Prime, Re_DeltaCQ1_Prime, Im_DeltaCQ1_Prime, Re_DeltaCQ2_Prime, Im_DeltaCQ2_Prime)

  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_LR_to_GWC)
#undef MODEL
#undef PARENT


#endif
