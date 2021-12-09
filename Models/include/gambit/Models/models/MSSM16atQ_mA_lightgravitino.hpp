//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM16atQ_mA_lightgravitino model definition.
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

#ifndef __MSSM16atQ_mA_lightgravitino_hpp__
#define __MSSM16atQ_mA_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM19atQ_mA_lightgravitino.hpp"

#define MODEL MSSM16atQ_mA_lightgravitino
#define PARENT MSSM19atQ_mA_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,
             mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM16atQ_mA_lightgravitino_to_MSSM19atQ_mA_lightgravitino)

#undef PARENT
#undef MODEL

#endif
