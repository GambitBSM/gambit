//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Two Higgs Doublet Model
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//  Filip Rajec
//  Aug 2016
//
//  *********************************************

#ifndef __THDM_III_hpp__
#define __THDM_III_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM_IIIatQ.hpp"

#define MODEL THDM_III
#define PARENT THDM_IIIatQ
  START_MODEL

  DEFINEPARS(Lambda_1,Lambda_2,Lambda_3,Lambda_4,Lambda_5,Lambda_7)
  DEFINEPARS(m22_2)
  DEFINEPARS(alpha,tanb)
  
  DEFINEPARS(Y2ct_real,Y2tc_real,Y2tt_real)
  DEFINEPARS(Y2ct_imag,Y2tc_imag,Y2tt_imag)
  DEFINEPARS(Y2sb_real,Y2bs_real,Y2bb_real)
  DEFINEPARS(Y2sb_imag,Y2bs_imag,Y2bb_imag)

  INTERPRET_AS_PARENT_FUNCTION(THDM_III_to_THDM_IIIatQ)
  // Translation functions defined in THDM.cpp
#undef PARENT
#undef MODEL

#endif
