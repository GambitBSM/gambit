//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM24atQ_mA_lightgravitino translation function definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MSSM24atQ_mA_lightgravitino.hpp"


// Activate debug output
//#define MSSM24atQ_mA_lightgravitino_DBUG

#define MODEL MSSM24atQ_mA_lightgravitino

  void MODEL_NAMESPACE::MSSM24atQ_mA_lightgravitino_to_MSSM25atQ_mA_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM25atQ_mA_lightgravitino."<<LogTags::info<<EOM;
     // Send all parameter values upstream to matching parameters in parent.
     targetP.setValues(myP);
     // Set 25th parameter (1st/2nd gen trilinear) in parent to zero.
     targetP.setValue("Ae_12",  0.0 );
     // Done
     #ifdef MSSM24atQ_mA_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM25atQ_mA_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
