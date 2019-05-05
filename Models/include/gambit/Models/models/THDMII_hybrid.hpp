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

#ifndef __THDMII_hybrid_hpp__
#define __THDMII_hybrid_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMII.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMII_hybrid
#define FRIEND THDMII
  START_MODEL
  
  DEFINEPARS(m_h,lambda2,lambda3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMII_hybrid_to_THDMII)
  // INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMII_hybrid.cpp
#undef FRIEND
#undef MODEL

#endif
