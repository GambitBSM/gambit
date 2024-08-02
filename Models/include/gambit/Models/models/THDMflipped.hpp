//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type Y-Flipped)
///
///  Models included:
///    THDMflippedatQ
///    THDMflipped
///    THDMflipped_higgs
///    THDMflipped_higgsatQ
///    THDMflipped_physical
///    THDMflipped_physicalatQ
///
///  Translation functions defined in THDMflipped.cpp
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
///  \date 2016 Aug
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 November
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  /date 2021 Mar
///
///  *********************************************

#ifndef __THDMflipped_hpp__
#define __THDMflipped_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Elements/sminputs.hpp"

// Forward declaration of needed types
namespace Gambit
{
  struct SMInputs;
}

#define MODEL  THDMflippedatQ
#define PARENT THDMatQ
  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin)

  // Translation functions defined in THDMflipped.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDMflippedatQ_to_THDMatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped
#define PARENT THDM
#define FRIEND THDMflippedatQ
  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  // Translation functions defined in THDMflipped.cpp
  INTERPRET_AS_X_FUNCTION(FRIEND, THDMflipped_to_THDMflippedatQ)
  INTERPRET_AS_X_DEPENDENCY(FRIEND, SMINPUTS, SMInputs)
  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef FRIEND
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_higgs
#define PARENT THDMflipped
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_higgs_to_THDMflipped)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_higgsatQ
#define PARENT THDMflippedatQ
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda6,Lambda7)
  DEFINEPARS(tanb, M12_2)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_higgsatQ_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_physical
#define PARENT THDMflipped
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_physical_to_THDMflipped)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_physicalatQ
#define PARENT THDMflippedatQ
  START_MODEL

  DEFINEPARS(mh,mH,mA,mHp)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_physicalatQ_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_hybrid_Higgs
#define PARENT THDMflipped
  START_MODEL

  DEFINEPARS(mh, mH, cba, tanb, Lambda4, Lambda5, Lambda7, lambda6, lambda7)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_hybrid_Higgs_to_THDMflipped)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_hybrid_HiggsatQ
#define PARENT THDMflippedatQ
  START_MODEL

  DEFINEPARS(mh, mH, cba, tanb, Lambda4, Lambda5, Lambda7, lambda6, lambda7)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_hybrid_HiggsatQ_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_hybrid_Higgs2
#define PARENT THDMflipped
  START_MODEL

  DEFINEPARS(mh, mHp, cba, tanb, Lambda4, Lambda5, Lambda7, lambda6, lambda7)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_hybrid_Higgs2_to_THDMflipped)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDMflipped_hybrid_Higgs2atQ
#define PARENT THDMflippedatQ
  START_MODEL

  DEFINEPARS(mh, mHp, cba, tanb, Lambda4, Lambda5, Lambda7, lambda6, lambda7)

  DEFINEPARS(Qin)

  INTERPRET_AS_PARENT_FUNCTION(THDMflipped_hybrid_Higgs2atQ_to_THDMflippedatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
