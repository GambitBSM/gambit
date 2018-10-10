//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NUGM model declaration. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Tomas Gonzalo  
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  *********************************************

#ifndef __NUGM_hpp__
#define __NUGM_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/MSSM20atMGUT.hpp" 

#define MODEL NUGM
#define PARENT MSSM20atMGUT
  START_MODEL
  DEFINEPARS(M0,M1,M2,M3,A0,TanBeta,SignMu)
  INTERPRET_AS_PARENT_FUNCTION(NUGM_to_MSSM20atMGUT)
#undef PARENT
#undef MODEL


#endif
