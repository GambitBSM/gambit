//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type X-Lepton Specific)
///
///  Models included:
///    THDMLSatQ
///    THDMLS
///    THDMLS_higgs
///    THDMLS_higgsatQ
///    THDMLS_physical
///    THDMLS_physicalatQ
///    THDMLS_hybrid_lambda1
///    THDMLS_hybrid_lambda1atQ
///    THDMLS_hybrid_lambda2
///    THDMLS_hybrid_lambda2atQ
///
///  Translation functions defined in THDMLS.cpp
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
///  \date 2016 June, Aug
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  \date 2021 Mar
///
///  *********************************************

#ifndef __THDMLS_hpp__
#define __THDMLS_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Elements/sminputs.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMLSatQ
#define PARENT THDMatQ
  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  // Translation functions defined in THDMLS.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDMLSatQ_to_THDMatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS
#define PARENT THDM
#define FRIEND THDMLSatQ
  START_MODEL
  
  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)
  
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMLS_to_THDMLSatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMLS_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef FRIEND
#undef PARENT
#undef MODEL

#define MODEL THDMLS_higgs
#define PARENT THDMLS
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_higgs_to_THDMLS)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_higgsatQ
#define PARENT THDMLSatQ
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_higgsatQ_to_THDMLSatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_physical
#define PARENT THDMLS
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_physical_to_THDMLS)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_physicalatQ
#define PARENT THDMLSatQ
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_physicalatQ_to_THDMLSatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_hybrid_lambda1
#define PARENT THDMLS
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_hybrid_lambda1_to_THDMLS)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_hybrid_lambda1atQ
#define PARENT THDMLSatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda2,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_hybrid_lambda1atQ_to_THDMLSatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_hybrid_lambda2
#define PARENT THDMLS
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_hybrid_lambda2_to_THDMLS)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMLS_hybrid_lambda2atQ
#define PARENT THDMLSatQ
  START_MODEL

  DEFINEPARS(mh, sba)
  DEFINEPARS(lambda1,lambda3,lambda4,lambda5)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMLS_hybrid_lambda2atQ_to_THDMLSatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL


#endif
