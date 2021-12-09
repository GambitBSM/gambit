//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10atQ_lightgravitino translation function definitions.
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

#include "gambit/Models/models/MSSM10atQ_lightgravitino.hpp"


// Activate debug output
//#define MSSM10atQ_lightgravitino_DBUG

#define MODEL MSSM10atQ_lightgravitino

  void MODEL_NAMESPACE::MSSM10atQ_lightgravitino_to_MSSM11atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM11atQ_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     targetP.setValues(myP);

     // Charged slepton trilinear coupling
     targetP.setValue("Ae_3", 0.0);

     // Done
     #ifdef MSSM11atQ_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM16atQ_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
