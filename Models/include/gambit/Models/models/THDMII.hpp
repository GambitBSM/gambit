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
//    Filip Rajec 
//      filip.rajec@adelaide.edu.au
//    Feb 2019
//
//  *********************************************

#ifndef __THDMII_hpp__
#define __THDMII_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMIIatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMII
#define PARENT THDM
#define FRIEND THDMIIatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMII_to_THDMIIatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDMII_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMII.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
