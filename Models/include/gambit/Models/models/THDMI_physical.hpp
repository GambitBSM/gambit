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

#ifndef __THDMI_physical_hpp__
#define __THDMI_physical_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Models/models/THDM.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI_physical
#define PARENT THDM
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(m_h,m_H,m_A,m_Hp)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(sba,tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_physical_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND ,SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMI_physical_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMI_physical.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
