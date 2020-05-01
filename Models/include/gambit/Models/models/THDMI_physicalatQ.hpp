//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Model Header
//  Two Higgs Doublet Model: Type I Physical Basis
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
//      Apr 2019
//
//  *********************************************

#ifndef __THDMI_physicalatQ_hpp__
#define __THDMI_physicalatQ_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMIatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI_physicalatQ
#define FRIEND THDMIatQ
  START_MODEL
  
  DEFINEPARS(m_h,m_H,m_A,m_Hp)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(Qin)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_physicalatQ_to_THDMIatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND ,SMINPUTS, SMInputs)
  // Translation functions defined in THDMI_physicalatQ.cpp
#undef FRIEND
#undef MODEL

#endif
