//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM10catQ_lightgravitino translation function definitions.
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

#include "gambit/Models/models/MSSM10catQ_lightgravitino.hpp"


// Activate debug output
//#define MSSM10catQ_lightgravitino_DBUG

#define MODEL MSSM10catQ_lightgravitino

  void MODEL_NAMESPACE::MSSM10catQ_lightgravitino_to_MSSM15atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM15atQ_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // Sfermion masses
     set_many_to_one(targetP, initVector<str>("mu2_3", "md2_3"), myP["mq2_3"]);
     set_many_to_one(targetP, initVector<str>("ml2_12", "ml2_3", "me2_3"), myP["ml2"]);

     // 3rd gen up-type trilinear coupling.
     targetP.setValue("Au_3", myP["A0"]);

     // Done
     #ifdef MSSM15atQ_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM15atQ_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
