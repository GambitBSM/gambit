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

#ifndef __THDMI_hybrid_lambda1_hpp__
#define __THDMI_hybrid_lambda1_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI_hybrid_lambda1
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(m_h, sba)
  DEFINEPARS(lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_hybrid_lambda1_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMI_hybrid_lambda1.cpp
#undef FRIEND
#undef MODEL

#endif
