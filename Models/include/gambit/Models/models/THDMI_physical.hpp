//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type I, Physicalc Basis)
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Filip Rajec 
///          (filip.rajec@adelaide.edu.au)
///  \date Apr 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date Apr 2020
///
///  *********************************************

#ifndef __THDMI_physical_hpp__
#define __THDMI_physical_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Models/models/THDM.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMI_physical
#define PARENT THDM
#define FRIEND THDMI
  START_MODEL
  
  DEFINEPARS(m_h,m_H,m_A,m_Hp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)
  
  // Translation functions defined in THDMI_physical.cpp
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_physical_to_THDMI)
  INTERPRET_AS_X_DEPENDENCY(FRIEND ,SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMI_physical_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef FRIEND
#undef PARENT
#undef MODEL

#endif
