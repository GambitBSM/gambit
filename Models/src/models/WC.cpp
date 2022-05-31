///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Model translation functions for the flavour EFT models
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2022 May
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/WC.hpp"

#define MODEL WC

void MODEL_NAMESPACE::WC_to_WC_LUV (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for WC --> WC_LUV."<<LogTags::info<<EOM;

  targetP.setValue("Re_DeltaC7_tau", myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_tau", myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_tau", myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_tau", myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_tau", myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_tau", myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_tau", myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_tau", myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_tau", myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_tau", myP.getValue("Im_DeltaCQ2"));

  targetP.setValue("Re_DeltaC7_mu", myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_mu", myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_mu", myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_mu", myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_mu", myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_mu", myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_mu", myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_mu", myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_mu", myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_mu", myP.getValue("Im_DeltaCQ2"));

  targetP.setValue("Re_DeltaC7_e", myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_e", myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_e", myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_e", myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_e", myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_e", myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_e", myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_e", myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_e", myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_e", myP.getValue("Im_DeltaCQ2"));
}

void MODEL_NAMESPACE::WC_to_WC_LR (const ModelParameters& myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_friend calculations for WC -> WC_LR..."<<LogTags::info<<EOM;

  // Send all parameter values upstream to matching parameters in friend.
  targetP.setValues(myP);

  targetP.setValue("Re_DeltaC7_Prime", myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_Prime", myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_Prime", myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_Prime", myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_Prime", myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_Prime", myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_Prime", myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_Prime", myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_Prime", myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_Prime", myP.getValue("Im_DeltaCQ2"));
}

#undef MODEL
