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
//      Feb 2019
//
//  *********************************************

#ifndef __THDMLS_physical_hpp__
#define __THDMLS_physical_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMLS.hpp"
#include "gambit/Models/models/THDM.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMLS_physical
#define PARENT THDM
#define FRIEND THDMLS
  START_MODEL
  
  DEFINEPARS(m_h,m_H,m_A,m_Hp)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(sba,tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMLS_physical_to_THDMLS)
  INTERPRET_AS_X_DEPENDENCY(FRIEND ,SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMLS_physical_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMLS_physical.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
