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
// \author A.S. Woodcock
//         (alex.woodcock@outlook.com)
// \date   Feb 2022
//
//  *********************************************

#ifndef __THDMI_smartBasis_hpp__
#define __THDMI_smartBasis_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMI_smartBasis
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,cosba_distorted)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_smartBasis_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)

#undef FRIEND
#undef MODEL

#endif

