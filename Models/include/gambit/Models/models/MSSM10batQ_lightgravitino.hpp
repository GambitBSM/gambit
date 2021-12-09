//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10batQ_lightgravitino model definition.
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

#ifndef __MSSM10batQ_lightgravitino_hpp__
#define __MSSM10batQ_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM11atQ_lightgravitino.hpp"

#define MODEL MSSM10batQ_lightgravitino
#define PARENT MSSM11atQ_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10batQ_lightgravitino_to_MSSM11atQ_lightgravitino)

#undef PARENT
#undef MODEL

#endif
