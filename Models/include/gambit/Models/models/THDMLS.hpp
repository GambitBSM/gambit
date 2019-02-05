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

#ifndef __THDMLS_hpp__
#define __THDMLS_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMLSatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMLS
#define PARENT THDM
#define FRIEND THDMLSatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMLS_to_THDMLSatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDMLS_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMLS.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
