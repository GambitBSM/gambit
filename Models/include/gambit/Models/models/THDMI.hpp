//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type I)
///
///  Models included:
///    THDMIatQ
///    THDMI
///    THDMI_higgs
///    THDMI_higgsatQ
///    THDMI_physical
///    THDMI_physicalatQ
///    THDMI_hybrid_lambda1
///    THDMI_hybrid_lambda1atQ
///    THDMI_hybrid_lambda2
///    THDMI_hybrid_lambda2atQ
///
///  Translation functions defined in THDMI.cpp
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 November
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  \date 201 Mar
///
///  *********************************************

#ifndef __THDMI_hpp__
#define __THDMI_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Elements/sminputs.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMIatQ
#define PARENT THDMatQ

  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMIatQ_to_THDMatQ)
#undef PARENT
#undef MODEL

#define MODEL THDMI
#define PARENT THDM
#define FRIEND THDMIatQ
  START_MODEL
  
  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMI_to_THDMIatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMI_to_THDM)
#undef FRIEND
#undef PARENT
#undef MODEL

#define MODEL THDMI_higgs
#define PARENT THDMI
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_higgs_to_THDMI)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_higgsatQ
#define PARENT THDMIatQ
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_higgsatQ_to_THDMIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_physical
#define PARENT THDMI
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_physical_to_THDMI)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_physicalatQ
#define PARENT THDMIatQ
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_physicalatQ_to_THDMIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_hybrid_lambda1
#define PARENT THDMI
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_hybrid_lambda1_to_THDMI)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_hybrid_lambda1atQ
#define PARENT THDMIatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_hybrid_lambda1atQ_to_THDMIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_hybrid_lambda2
#define PARENT THDMI
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_hybrid_lambda2_to_THDMI)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMI_hybrid_lambda2atQ
#define PARENT THDMIatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMI_hybrid_lambda2atQ_to_THDMIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
