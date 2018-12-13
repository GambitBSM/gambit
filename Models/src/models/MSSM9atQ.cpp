//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM9atQ translation function definitions.
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

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/MSSM9atQ.hpp"


// Activate debug output
//#define MSSM9atQ_DBUG

#define MODEL MSSM9atQ

  void MODEL_NAMESPACE::MSSM9atQ_to_MSSM10atQ (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM10atQ."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Sfermion mass matrix entries.
     targetP.setValue("mq2", myP["mf2"]);
     targetP.setValue("ml2", myP["mf2"]);

     // Done
     #ifdef MSSM9atQ_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM10atQ parameters:" << targetP << std::endl;
     #endif
  }

  void MODEL_NAMESPACE::MSSM9atQ_to_MSSM10batQ (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> MSSM10batQ."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Charged slepton trilinear coupling
     targetP.setValue("Ae_3", 0.0);

     // Done
     #ifdef MSSM9atQ_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM10batQ parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
