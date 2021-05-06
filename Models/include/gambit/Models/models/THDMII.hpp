//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type II)
///
///  Models included:
///    THDMIIatQ
///    THDMII
///    THDMII_higgs
///    THDMII_higgsatQ
///    THDMII_physical
///    THDMII_physicalatQ
///    THDMII_hybrid_lambda1
///    THDMII_hybrid_lambda1atQ
///    THDMII_hybrid_lambda2
///    THDMII_hybrid_lambda2atQ
///
///  Translation functions defined in THDMII.cpp
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
///  \date 2016 June
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __THDMII_hpp__
#define __THDMII_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Elements/sminputs.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMIIatQ
#define PARENT THDMatQ
  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMIIatQ_to_THDMatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII
#define PARENT THDM
#define FRIEND THDMIIatQ
  START_MODEL
  
  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMII_to_THDMIIatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMII_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef FRIEND
#undef PARENT
#undef MODEL

#define MODEL THDMII_higgs
#define PARENT THDMII
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_higgs_to_THDMII)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_higgsatQ
#define PARENT THDMIIatQ
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_higgsatQ_to_THDMIIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_physical
#define PARENT THDMII
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_physical_to_THDMII)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_physicalatQ
#define PARENT THDMIIatQ
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_physicalatQ_to_THDMIIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_hybrid_lambda1
#define PARENT THDMII
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_hybrid_lambda1_to_THDMII)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_hybrid_lambda1atQ
#define PARENT THDMIIatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_hybrid_lambda1atQ_to_THDMIIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_hybrid_lambda2
#define PARENT THDMII
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_hybrid_lambda2_to_THDMII)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMII_hybrid_lambda2atQ
#define PARENT THDMIIatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMII_hybrid_lambda2atQ_to_THDMIIatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
