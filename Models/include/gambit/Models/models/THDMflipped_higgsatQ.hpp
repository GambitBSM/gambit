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

#ifndef __THDMflipped_higgsatQ_hpp__
#define __THDMflipped_higgsatQ_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMflippedatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMflipped_higgsatQ
#define FRIEND THDMflippedatQ
  START_MODEL
  
  DEFINEPARS(Lambda_1,Lambda_2,Lambda_3,Lambda_4,Lambda_5,Lambda6,Lambda_7)
  DEFINEPARS(tanb, M12_2)

  DEFINEPARS(Qin)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMflipped_higgsatQ_to_THDMflippedatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMflipped_higgsatQ.cpp
#undef FRIEND
#undef MODEL

#endif
