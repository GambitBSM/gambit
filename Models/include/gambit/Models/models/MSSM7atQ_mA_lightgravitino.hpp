//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM7atQ_mA_lightgravitino model definition.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#ifndef __MSSM7atQ_mA_lightgravitino_hpp__
#define __MSSM7atQ_mA_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM9atQ_mA_lightgravitino.hpp"

// Forward declaration of needed types
namespace Gambit {
  class SMInputs;
}

#define MODEL MSSM7atQ_mA_lightgravitino
#define PARENT MSSM9atQ_mA_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,
             mA,mu,M2,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM7atQ_mA_lightgravitino_to_MSSM9atQ_mA_lightgravitino)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)

#undef PARENT
#undef MODEL

#endif
