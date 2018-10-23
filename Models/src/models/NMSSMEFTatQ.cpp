//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NMSSMEFTatQ translation function definitions.
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
#include "gambit/Models/models/NMSSMEFTatQ.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Logs/logger.hpp"

// Activate debug output
//#define NMSSMEFTatQ_DBUG

#define MODEL NMSSMEFTatQ
#define PARENT NMSSM66atQ

  void MODEL_NAMESPACE::NMSSMEFTatQ_to_NMSSM66atQ (const ModelParameters &myP, ModelParameters &targetP)
  {
     USE_MODEL_PIPE(PARENT)

     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) << LogTags::info <<EOM;

     // Send all commmon parameter values upstream to matching parameters in parent.
     targetP.setValues(myP,false);

     // Set mass and dimenionful coupling parameters for particles decoupled ("deleted" in SARAH model) to 100 TeV.
     const static std::vector<str> deleted_parameters = initVector<str>("M3",
      "mq2_11", "mq2_12", "mq2_13", "mq2_22", "mq2_23", "mq2_33",
      "ml2_11", "ml2_12", "ml2_13", "ml2_22", "ml2_23", "ml2_33",
      "md2_11", "md2_12", "md2_13", "md2_22", "md2_23", "md2_33",
      "mu2_11", "mu2_12", "mu2_13", "mu2_22", "mu2_23", "mu2_33",
      "me2_11", "me2_12", "me2_13", "me2_22", "me2_23", "me2_33",
       "Ae_11",  "Ae_12",  "Ae_13",  "Ae_21",  "Ae_22",  "Ae_23",
       "Ae_31",  "Ae_32",  "Ae_33",  "Ad_11",  "Ad_12",  "Ad_13",
       "Ad_21",  "Ad_22",  "Ad_23",  "Ad_31",  "Ad_32",  "Ad_33",
       "Au_11",  "Au_12",  "Au_13",  "Au_21",  "Au_22",  "Au_23",
       "Au_31",  "Au_32",  "Au_33");
     set_many_to_one(targetP, deleted_parameters, 1e5);

     // Translate vev of S to effective mu parameter
     targetP.setValue("mueff", myP["lambda"]*myP["vS"]/root2);

     // Done
     #ifdef NMSSMEFTatQ_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }

#undef PARENT
#undef MODEL
