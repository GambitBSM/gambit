//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type Y-Flipped, Generic Basis)
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///  
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2016 Aug
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __THDMflipped_hpp__
#define __THDMflipped_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMflipped
#define PARENT THDM
#define FRIEND THDMflippedatQ
  START_MODEL
  
  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)
  
  // Translation functions defined in THDMflipped.cpp
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMflipped_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
