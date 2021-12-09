//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM9batQ_lightgravitino model definition.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2015 Sep
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#ifndef __MSSM9batQ_lightgravitino_hpp__
#define __MSSM9batQ_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM15atQ_lightgravitino.hpp"

#define MODEL MSSM9batQ_lightgravitino
#define PARENT MSSM15atQ_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,
             mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_3)

  DEFINEPARS(msf2)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9batQ_lightgravitino_to_MSSM15atQ_lightgravitino)

#undef PARENT
#undef MODEL

#endif
