//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NUHM1 model definition.
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

#ifndef __NUHM1_hpp__
#define __NUHM1_hpp__

// Must include models that are targets of translation functions
#include "gambit/Models/models/NUHM2.hpp"

#define MODEL NUHM1
#define PARENT NUHM2
  START_MODEL
  DEFINEPARS(M0,M12,mH,A0,TanBeta,SignMu)
  INTERPRET_AS_PARENT_FUNCTION(NUHM1_to_NUHM2)
  // Translation functions defined in NUHM1.cpp
#undef PARENT
#undef MODEL


#endif
