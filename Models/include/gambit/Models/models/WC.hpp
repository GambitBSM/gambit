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
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2022 May, June
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 June
///  \date 2024 Feb
///
///  \author Martin White
///          (martin.white@adelaide.edu.au)
///  \date 2023 March
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
   DEFINEPARS(Re_DeltaC2p_tau, Im_DeltaC2p_tau, Re_DeltaC7p_tau, Im_DeltaC7p_tau, Re_DeltaC8p_tau, Im_DeltaC8p_tau, Re_DeltaC9p_tau, Im_DeltaC9p_tau, Re_DeltaC10p_tau, Im_DeltaC10p_tau, Re_DeltaCQ1p_tau, Im_DeltaCQ1p_tau, Re_DeltaCQ2p_tau, Im_DeltaCQ2p_tau)
   DEFINEPARS(Re_DeltaC2p_mu, Im_DeltaC2p_mu, Re_DeltaC7p_mu, Im_DeltaC7p_mu, Re_DeltaC8p_mu, Im_DeltaC8p_mu, Re_DeltaC9p_mu, Im_DeltaC9p_mu, Re_DeltaC10p_mu, Im_DeltaC10p_mu, Re_DeltaCQ1p_mu, Im_DeltaCQ1p_mu, Re_DeltaCQ2p_mu, Im_DeltaCQ2p_mu)
   DEFINEPARS(Re_DeltaC2p_e, Im_DeltaC2p_e, Re_DeltaC7p_e, Im_DeltaC7p_e, Re_DeltaC8p_e, Im_DeltaC8p_e, Re_DeltaC9p_e, Im_DeltaC9p_e, Re_DeltaC10p_e, Im_DeltaC10p_e, Re_DeltaCQ1p_e, Im_DeltaCQ1p_e, Re_DeltaCQ2p_e, Im_DeltaCQ2p_e)

  // Wilson coefficients for neutral lepton interactions, inspired by page 4 of https://arxiv.org/pdf/2107.01080.pdf
  // Assume that off diagonal elements are zero
  // All diagonal elements are set to the number below (i.e. gives factor of 3 when summing over flavours)
  // This assumes flavour universality, i.e. different neutrinos are phenomenologically indistinguishable
  DEFINEPARS(Re_DeltaCLL_V, Im_DeltaCLL_V, Re_DeltaCRL_V, Im_DeltaCRL_V, Re_DeltaCLR_V, Im_DeltaCLR_V, Re_DeltaCRR_V, Im_DeltaCRR_V,
       Re_DeltaCLL_S, Im_DeltaCLL_S, Re_DeltaCRL_S, Im_DeltaCRL_S, Re_DeltaCLR_S, Im_DeltaCLR_S, Re_DeltaCRR_S, Im_DeltaCRR_S,
       Re_DeltaCLL_T, Im_DeltaCLL_T, Re_DeltaCRR_T, Im_DeltaCRR_T)

#undef MODEL

// WC model for lepton universality
#define PARENT GWC
#define MODEL WC_LUV
  START_MODEL
  DEFINEPARS(Re_DeltaC7_tau, Im_DeltaC7_tau, Re_DeltaC9_tau, Im_DeltaC9_tau, Re_DeltaC10_tau, Im_DeltaC10_tau, Re_DeltaCQ1_tau, Im_DeltaCQ1_tau, Re_DeltaCQ2_tau, Im_DeltaCQ2_tau,
             Re_DeltaC7_mu, Im_DeltaC7_mu, Re_DeltaC9_mu, Im_DeltaC9_mu, Re_DeltaC10_mu, Im_DeltaC10_mu, Re_DeltaCQ1_mu, Im_DeltaCQ1_mu, Re_DeltaCQ2_mu, Im_DeltaCQ2_mu,
             Re_DeltaC7_e, Im_DeltaC7_e, Re_DeltaC9_e, Im_DeltaC9_e, Re_DeltaC10_e, Im_DeltaC10_e, Re_DeltaCQ1_e, Im_DeltaCQ1_e, Re_DeltaCQ2_e, Im_DeltaCQ2_e)
  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_LUV_to_GWC)
#undef MODEL
#undef PARENT

// WC model with different chirality
#define PARENT GWC
#define MODEL WC_LR
  START_MODEL
  DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2,
             Re_DeltaC7p, Im_DeltaC7p, Re_DeltaC9p, Im_DeltaC9p, Re_DeltaC10p, Im_DeltaC10p, Re_DeltaCQ1p, Im_DeltaCQ1p, Re_DeltaCQ2p, Im_DeltaCQ2p)
  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_LR_to_GWC)
#undef MODEL
#undef PARENT

// Simple WC model, only muon flavour
#define PARENT WC_LUV
#define MODEL WC
  START_MODEL
  DEFINEPARS(Re_DeltaC7, Im_DeltaC7, Re_DeltaC9, Im_DeltaC9, Re_DeltaC10, Im_DeltaC10, Re_DeltaCQ1, Im_DeltaCQ1, Re_DeltaCQ2, Im_DeltaCQ2)
  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_to_WC_LUV)
  INTERPRET_AS_X_FUNCTION(WC_LR,WC_to_WC_LR)
#undef MODEL
#undef PARENT

// Simplified neutral lepton interaction model with just vector-like and no left-right interactions
#define PARENT GWC
#define MODEL WC_nu
  START_MODEL
  DEFINEPARS(Re_DeltaCL, Im_DeltaCL, Re_DeltaCR, Im_DeltaCR)
  // Translation functions defined in WC.cpp
  INTERPRET_AS_PARENT_FUNCTION(WC_nu_to_GWC)
#undef MODEL
#undef PARENT

#endif
