//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM9atQ_mA_lightgravitino model definition.
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

#ifndef __MSSM9atQ_mA_lightgravitino_hpp__
#define __MSSM9atQ_mA_lightgravitino_hpp__

// Parent and friend models must be declared first! Include them here to ensure that this happens.
#include "gambit/Models/models/MSSM10atQ_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM10batQ_mA_lightgravitino.hpp"

#define MODEL MSSM9atQ_mA_lightgravitino
#define PARENT MSSM10atQ_mA_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,
             mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9atQ_mA_lightgravitino_to_MSSM10atQ_mA_lightgravitino)
  INTERPRET_AS_X_FUNCTION(MSSM10batQ_mA_lightgravitino, MSSM9atQ_mA_lightgravitino_to_MSSM10batQ_mA_lightgravitino)

#undef PARENT
#undef MODEL

#endif
