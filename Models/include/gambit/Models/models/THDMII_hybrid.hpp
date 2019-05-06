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
  
  DEFINEPARS(m_h,m_H,Lambda_1,Lambda_2,Lambda_3,Lambda_4,Lambda_5,Lambda_7)
  DEFINEPARS(tanb, sba)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMII_hybrid_to_THDMII)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMII_hybrid.cpp
#undef FRIEND
#undef MODEL

#endif
