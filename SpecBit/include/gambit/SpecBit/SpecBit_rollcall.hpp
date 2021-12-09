//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module SpecBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///    \date 2019 Oct
///
///  *********************************************

//TODO: This is manual now, we'll automate this with a harvester in the future

#ifndef __SpecBit_rollcall_hpp__
#define __SpecBit_rollcall_hpp__

#include "gambit/SpecBit/SpecBit_types.hpp"

#define MODULE SpecBit
#define REFERENCE GAMBITModelsWorkgroup:2017ilg
START_MODULE

  // Predefine capabilities that appear in more than one model, to avoid ordering problems
  #define CAPABILITY Higgs_Couplings
  START_CAPABILITY
  #undef CAPABILITY

  #define CAPABILITY scale_of_nonperturbativity
  START_CAPABILITY
  #undef CAPABILITY

  /// Module function declarations for model SM
  #include "gambit/SpecBit/models/SM.hpp"

  /// Module function declarations for model MSSM
  #include "gambit/SpecBit/models/MSSM.hpp"

  /// Module function declarations for model ScalarSingletDM
  #include "gambit/SpecBit/models/ScalarSingletDM.hpp"

  /// Module function declarations for model VectorSingletDM
  #include "gambit/SpecBit/models/VectorSingletDM.hpp"

  /// Module function declarations for model MajoranaSingletDM
  #include "gambit/SpecBit/models/MajoranaSingletDM.hpp"

  /// Module function declarations for model DiracSingletDM
  #include "gambit/SpecBit/models/DiracSingletDM.hpp"

  /// Module function declarations for model MDM
  #include "gambit/SpecBit/models/MDM.hpp"

  /// Module function declarations for model DMEFT
  #include "gambit/SpecBit/models/DMEFT.hpp"
  
  // TODO: Still to fix
  #include "gambit/SpecBit/SpecBit_VS_rollcall.hpp"

#undef REFERENCE
#undef MODULE

#endif /* defined(__SpecBit_rollcall_hpp__) */



