//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM20atQ_lightgravitino model definition.
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

#ifndef __MSSM20atQ_lightgravitino_hpp__
#define __MSSM20atQ_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM25atQ_lightgravitino.hpp"

#define MODEL MSSM20atQ_lightgravitino
#define PARENT MSSM25atQ_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM20atQ_lightgravitino_to_MSSM25atQ_lightgravitino)

#undef PARENT
#undef MODEL

#endif
