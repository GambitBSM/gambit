//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM15atQ_mA_lightgravitino model definition.
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

#ifndef __MSSM15atQ_mA_lightgravitino_hpp__
#define __MSSM15atQ_mA_lightgravitino_hpp__

// Parent model must be declared first! Include it here to ensure that this happens.
#include "gambit/Models/models/MSSM16atQ_mA_lightgravitino.hpp"

#define MODEL MSSM15atQ_mA_lightgravitino
#define PARENT MSSM16atQ_mA_lightgravitino
  START_MODEL

  DEFINEPARS(Qin,TanBeta,
             mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(A0, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM15atQ_mA_lightgravitino_to_MSSM16atQ_mA_lightgravitino)

#undef PARENT
#undef MODEL

#endif
