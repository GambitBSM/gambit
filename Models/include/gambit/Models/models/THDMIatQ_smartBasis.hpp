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
//
//  James McKay
//    November 2016
//
//  Filip Rajec 
//    filip.rajec@adelaide.edu.au
//    Feb 2019
//
//  *********************************************

#ifndef __THDMIatQ_smartBasis_hpp__
#define __THDMIatQ_smartBasis_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMIatQ.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL THDMIatQ_smartBasis
#define FRIEND THDMIatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,cosba_distorted)
  DEFINEPARS(tanb)
  DEFINEPARS(Qin,QrunTo)

  INTERPRET_AS_X_FUNCTION(FRIEND, THDMIatQ_smartBasis_to_THDMIatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)

#undef FRIEND
#undef MODEL

#endif
