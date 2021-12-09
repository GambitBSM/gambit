//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM19atQ_mA_lightgravitino translation function definitions.
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

#include "gambit/Models/models/MSSM19atQ_mA_lightgravitino.hpp"


// Activate debug output
//#define MSSM19atQ_mA_lightgravitino_DBUG

#define MODEL MSSM19atQ_mA_lightgravitino

  void MODEL_NAMESPACE::MSSM19atQ_mA_lightgravitino_to_MSSM24atQ_mA_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> MSSM24atQ_mA_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // RH squark soft masses, gen 1 and 2
     targetP.setValue("mq2_1",  myP["mq2_12"] ); // mq2_11 in MSSM63
     targetP.setValue("mq2_2",  myP["mq2_12"] ); // mq2_22   " "
     // RH slepton soft masses, gen 1 and 2
     targetP.setValue("ml2_1",  myP["ml2_12"] ); // ml2_11 in MSSM63
     targetP.setValue("ml2_2",  myP["ml2_12"] ); // ml2_22   " "
     // LH down-type squark soft masses
     targetP.setValue("md2_1",  myP["md2_12"] ); // ml2_11 in MSSM63
     targetP.setValue("md2_2",  myP["md2_12"] ); // ml2_22   " "
     // LH up-type squark soft masses
     targetP.setValue("mu2_1",  myP["mu2_12"] ); // mu2_11 in MSSM63
     targetP.setValue("mu2_2",  myP["mu2_12"] ); // mu2_22   " "
     // LH charged slepton soft masses
     targetP.setValue("me2_1",  myP["me2_12"] ); // me2_11 in MSSM63
     targetP.setValue("me2_2",  myP["me2_12"] ); // me2_22   " "

     // Done
     #ifdef MSSM19atQ_mA_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM24atQ_mA_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

  void MODEL_NAMESPACE::MSSM19atQ_mA_lightgravitino_to_MSSM20atQ_mA_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> MSSM20atQ_mA_lightgravitino."<<LogTags::info<<EOM;

     // Send all parameter values upstream to matching parameters in the friend model.
     targetP.setValues(myP);
     // Set 20th parameter (1st/2nd gen trilinear) in friend to zero.
     targetP.setValue("Ae_12",  0.0 );

     // Done
     #ifdef MSSM19atQ_mA_lightgravitino_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << "MSSM20atQ_mA_lightgravitino parameters:" << targetP << std::endl;
     #endif
  }

#undef MODEL
