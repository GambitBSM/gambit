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

#ifndef __THDMflipped_hybrid_lambda2atQ_hpp__
#define __THDMflipped_hybrid_lambda2atQ_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMflippedatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMflipped_hybrid_lambda2atQ
#define FRIEND THDMflippedatQ
  START_MODEL
  
  DEFINEPARS(m_h, sba)
  DEFINEPARS(lambda_1,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin,QrunTo)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMflipped_hybrid_lambda2atQ_to_THDMflippedatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  // Translation functions defined in THDMflipped_hybrid_lambda2atQ.cpp
#undef FRIEND
#undef MODEL

#endif
