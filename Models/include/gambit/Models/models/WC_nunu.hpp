//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Flavour EFT for B->Knunu and B->K*nunu transitions
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Martin White
//  2023 March
//
//  *********************************************

#ifndef __WC_nunu_hpp__
#define __WC_nunu_hpp__

// Wilson coefficients inspired by page 4 of https://arxiv.org/pdf/2107.01080.pdf
// We only have one number per matrix
// Assume that off diagonal elements are zero
// All diagonal elements are set to the number below (i.e. gives factor of 3 when summing over flavours)
// (assume different neutrinos are phenomenologically indistinguishable)
#define MODEL WC_nunu
  START_MODEL
  DEFINEPARS(Re_DeltaCLL_V, Im_DeltaCLL_V, Re_DeltaCRL_V, Im_DeltaCRL_V, Re_DeltaCLR_V, Im_DeltaCLR_V, Re_DeltaCRR_V, Im_DeltaCRR_V,
	     Re_DeltaCLL_S, Im_DeltaCLL_S, Re_DeltaCRL_S, Im_DeltaCRL_S, Re_DeltaCLR_S, Im_DeltaCLR_S, Re_DeltaCRR_S, Im_DeltaCRR_S,
	     Re_DeltaCLL_T, Im_DeltaCLL_T, Re_DeltaCRR_T, Im_DeltaCRR_T)
#undef MODEL

#endif
