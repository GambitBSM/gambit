//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Model Header
//  Two Higgs Doublet Model: Type I
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//    Filip Rajec 
//      filip.rajec@adelaide.edu.au
//      Feb 2019
//
//  *********************************************

#ifndef __THDMI_hpp__
#define __THDMI_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMIatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI
#define PARENT THDM
#define FRIEND THDMIatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_to_THDMIatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDMI_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMI.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
