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

#ifndef __THDMI_higgs_hpp__
#define __THDMI_higgs_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI_higgs
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(Lambda_1,Lambda_2,Lambda_3,Lambda_4,Lambda_5,Lambda6,Lambda_7)
  DEFINEPARS(tanb, M12_2)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_higgs_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMI_higgs.cpp
#undef FRIEND
#undef MODEL

#endif
