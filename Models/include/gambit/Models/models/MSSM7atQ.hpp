//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM7atQ model definition.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Sep
///
///  *********************************************

#ifndef __MSSM7atQ_hpp__
#define __MSSM7atQ_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM9atQ.hpp"

// Forward declaration of needed types
namespace Gambit
{
  struct SMInputs;
}

#define MODEL MSSM7atQ
#define PARENT MSSM9atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M2)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM7atQ_to_MSSM9atQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)

#undef PARENT
#undef MODEL

#endif
