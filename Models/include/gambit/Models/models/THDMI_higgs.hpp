//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type I, Higgs Basis)
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///  \author Filip Rajec 
///          (filip.rajec@adelaide.edu.au)
///  \date Feb 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date Apr 2020
///
///  *********************************************

#ifndef __THDMI_higgs_hpp__
#define __THDMI_higgs_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMI_higgs
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)
  
  // Translation functions defined in THDMI_higgs.cpp
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_higgs_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
#undef FRIEND
#undef MODEL

#endif
