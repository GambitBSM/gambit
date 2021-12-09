//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10atQ_mA_lightgravitino model definition.
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

#ifndef __MSSM10atQ_mA_lightgravitino_hpp__
#define __MSSM10atQ_mA_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM11atQ_mA_lightgravitino.hpp"

#define MODEL MSSM10atQ_mA_lightgravitino
#define PARENT MSSM11atQ_mA_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,
             mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2)

  DEFINEPARS(ml2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10atQ_mA_lightgravitino_to_MSSM11atQ_mA_lightgravitino)

#undef PARENT
#undef MODEL

#endif
