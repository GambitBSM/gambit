//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10batQ_lightgravitino translation function definitions.
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

#include "gambit/Models/models/MSSM10batQ_lightgravitino.hpp"


// Activate debug output
//#define MSSM10batQ_lightgravitino_DBUG

#define MODEL MSSM10batQ_lightgravitino

  void MODEL_NAMESPACE::MSSM10batQ_lightgravitino_to_MSSM11atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM11atQ_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Sfermion mass matrix entries.
     targetP.setValue("mq2", myP["mf2"]);
     targetP.setValue("ml2", myP["mf2"]);

     // Done
     #ifdef MSSM10batQ_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM11atQ_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
