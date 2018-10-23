//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NMSSMEFTatQ_mA translation function definitions.
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
#include "gambit/Models/models/NMSSMEFTatQ_mA.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Logs/logger.hpp"

// Activate debug output
//#define NMSSMEFTatQ_DBUG

#define MODEL NMSSMEFTatQ_mA
#define PARENT NMSSMEFTatQ

  void MODEL_NAMESPACE::NMSSMEFTatQ_mA_to_NMSSMEFTatQ (const ModelParameters &myP, ModelParameters &targetP)
  {
     USE_MODEL_PIPE(PARENT)

     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) << LogTags::info <<EOM;

     // Send all commmon parameter values upstream to matching parameters in parent.
     targetP.setValues(myP,false);

     // Translate mu to vev of S and mA to Alambda
     double mu = myP["mu"];
     double lambda = myP["lambda"];
     double tanbeta = myP["tanbeta"];
     double mA = myP["mA"];
     targetP.setValue("vS", mu / lambda * root2);
     targetP.setValue("Alambda", mA*mA*tanbeta/(mu*(1+tanbeta*tanbeta)) - myP["kappa"]*mu/lambda);

     // Done
     #ifdef NMSSMEFTatQ_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }

#undef PARENT
#undef MODEL
