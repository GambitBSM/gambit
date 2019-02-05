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
//  Filip Rajec
//  Aug 2016
//
//  *********************************************

#ifndef __THDMflipped_hpp__
#define __THDMflipped_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMflipped
#define PARENT THDM
#define FRIEND THDMflippedatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMflipped_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
  // Translation functions defined in THDMflipped.cpp
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
