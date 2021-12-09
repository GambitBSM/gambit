//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10catQ_lightgravitino model definition.
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

#ifndef __MSSM10catQ_lightgravitino_hpp__
#define __MSSM10catQ_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM15atQ_lightgravitino.hpp"

#define MODEL MSSM10catQ_lightgravitino
#define PARENT MSSM15atQ_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2)

  DEFINEPARS(A0)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10catQ_lightgravitino_to_MSSM15atQ_lightgravitino)

#undef PARENT
#undef MODEL

#endif
