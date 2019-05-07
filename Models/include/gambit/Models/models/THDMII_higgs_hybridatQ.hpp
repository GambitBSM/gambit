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

#ifndef __THDMII_higgs_hybridatQ_hpp__
#define __THDMII_higgs_hybridatQ_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMIIatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMII_higgs_hybridatQ
#define FRIEND THDMIIatQ
  START_MODEL
  
  DEFINEPARS(m_h,m_H,Lambda_1,Lambda_2,Lambda_3,Lambda_4,Lambda_5,Lambda_7)
  DEFINEPARS(tanb, sba)

  DEFINEPARS(Qin,QrunTo)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMII_higgs_hybridatQ_to_THDMIIatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMII_higgs_hybridatQ.cpp
#undef FRIEND
#undef MODEL

#endif
