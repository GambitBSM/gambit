//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM9atQ_lightgravitino translation function definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Sep
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/MSSM9atQ_lightgravitino.hpp"


// Activate debug output
//#define MSSM9atQ_lightgravitino_DBUG

#define MODEL MSSM9atQ_lightgravitino

  void MODEL_NAMESPACE::MSSM9atQ_lightgravitino_to_MSSM10atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM10atQ_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Sfermion mass matrix entries.
     targetP.setValue("mq2", myP["mf2"]);
     targetP.setValue("ml2", myP["mf2"]);

     // Done
     #ifdef MSSM9atQ_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM10atQ_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

  void MODEL_NAMESPACE::MSSM9atQ_lightgravitino_to_MSSM10batQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM10batQ_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Charged slepton trilinear coupling
     targetP.setValue("Ae_3", 0.0);

     // Done
     #ifdef MSSM9atQ_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM10batQ_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
