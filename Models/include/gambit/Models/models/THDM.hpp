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

#ifndef __THDM_hpp__
#define __THDM_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMatQ.hpp"

#define MODEL THDM
#define PARENT THDMatQ
  START_MODEL
  
  DEFINEPARS(mh0,mH0,mA,mC)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(alpha,tanb)
  
  INTERPRET_AS_PARENT_FUNCTION(THDM_to_THDMatQ)
  // Translation functions defined in THDM.cpp
#undef PARENT
#undef MODEL

#endif
