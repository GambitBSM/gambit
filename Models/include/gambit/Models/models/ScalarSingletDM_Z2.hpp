//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  Singlet DM
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Christoph Weniger
///  \date 2014 January
///
///  \author James McKay
///  \date 2015 September
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#ifndef __ScalarSingletDM_Z2_hpp__
#define __ScalarSingletDM_Z2_hpp__

// Must include models that are targets of translation functions
#include "gambit/Models/models/ScalarSingletDM_Z2_running.hpp"

#define MODEL ScalarSingletDM_Z2
#define PARENT ScalarSingletDM_Z2_running
  START_MODEL
  DEFINEPARS(mS, lambda_hS)
  // Translate this model into ScalarSingletDM_Z2_running
  INTERPRET_AS_PARENT_FUNCTION(ScalarSingletDM_Z2_to_ScalarSingletDM_Z2_running)
#undef PARENT
#undef MODEL

#endif
