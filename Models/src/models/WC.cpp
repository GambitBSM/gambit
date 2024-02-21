//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Translation function definitions for the
///  WC model and its variations.
///
///  Contains the interpret-as translation
///  functions for:
///
///  WC_LUV  --> GWC
///  WC_LR   --> GWC
///  WC_nu   --> GWC
///  WC      --> WC_LUV, WC_LR
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2022 May, June
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 June
///  \date 2024 Feb
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/WC.hpp"

// Models inheriting from GWC
#define PARENT GWC

// WC_LUV --> GWC
#define MODEL  WC_LUV
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

  // Set everything to zero first
  for(auto par : targetP.getKeys())
    targetP.setValue(par, 0.0);

  // Now send all parameter values upstream to those matching parameters in parent.
  targetP.setValues(myP,false);

}
#undef MODEL

// WC_LR --> GWC
#define MODEL WC_LR
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

  // Set everything to zero first
  for(auto par : targetP.getKeys())
    targetP.setValue(par, 0.0);

  // Now send all parameter values upstream to those matching parameters in parent.
  targetP.setValue("Re_DeltaC7_e",myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_e",myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_e",myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_e",myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_e",myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_e",myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_e",myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_e",myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_e",myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_e",myP.getValue("Im_DeltaCQ2"));

  targetP.setValue("Re_DeltaC7_mu",myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_mu",myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_mu",myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_mu",myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_mu",myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_mu",myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_mu",myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_mu",myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_mu",myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_mu",myP.getValue("Im_DeltaCQ2"));

  targetP.setValue("Re_DeltaC7_tau",myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7_tau",myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9_tau",myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9_tau",myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10_tau",myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10_tau",myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1_tau",myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1_tau",myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2_tau",myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2_tau",myP.getValue("Im_DeltaCQ2"));

  targetP.setValue("Re_DeltaC7_ep",myP.getValue("Re_DeltaC7p"));
  targetP.setValue("Im_DeltaC7_ep",myP.getValue("Im_DeltaC7p"));
  targetP.setValue("Re_DeltaC9_ep",myP.getValue("Re_DeltaC9p"));
  targetP.setValue("Im_DeltaC9_ep",myP.getValue("Im_DeltaC9p"));
  targetP.setValue("Re_DeltaC10_ep",myP.getValue("Re_DeltaC10p"));
  targetP.setValue("Im_DeltaC10_ep",myP.getValue("Im_DeltaC10p"));
  targetP.setValue("Re_DeltaCQ1_ep",myP.getValue("Re_DeltaCQ1p"));
  targetP.setValue("Im_DeltaCQ1_ep",myP.getValue("Im_DeltaCQ1p"));
  targetP.setValue("Re_DeltaCQ2_ep",myP.getValue("Re_DeltaCQ2p"));
  targetP.setValue("Im_DeltaCQ2_ep",myP.getValue("Im_DeltaCQ2p"));

  targetP.setValue("Re_DeltaC7_mup",myP.getValue("Re_DeltaC7p"));
  targetP.setValue("Im_DeltaC7_mup",myP.getValue("Im_DeltaC7p"));
  targetP.setValue("Re_DeltaC9_mup",myP.getValue("Re_DeltaC9p"));
  targetP.setValue("Im_DeltaC9_mup",myP.getValue("Im_DeltaC9p"));
  targetP.setValue("Re_DeltaC10_mup",myP.getValue("Re_DeltaC10p"));
  targetP.setValue("Im_DeltaC10_mup",myP.getValue("Im_DeltaC10p"));
  targetP.setValue("Re_DeltaCQ1_mup",myP.getValue("Re_DeltaCQ1p"));
  targetP.setValue("Im_DeltaCQ1_mup",myP.getValue("Im_DeltaCQ1p"));
  targetP.setValue("Re_DeltaCQ2_mup",myP.getValue("Re_DeltaCQ2p"));
  targetP.setValue("Im_DeltaCQ2_mup",myP.getValue("Im_DeltaCQ2p"));

  targetP.setValue("Re_DeltaC7_taup",myP.getValue("Re_DeltaC7p"));
  targetP.setValue("Im_DeltaC7_taup",myP.getValue("Im_DeltaC7p"));
  targetP.setValue("Re_DeltaC9_taup",myP.getValue("Re_DeltaC9p"));
  targetP.setValue("Im_DeltaC9_taup",myP.getValue("Im_DeltaC9p"));
  targetP.setValue("Re_DeltaC10_taup",myP.getValue("Re_DeltaC10p"));
  targetP.setValue("Im_DeltaC10_taup",myP.getValue("Im_DeltaC10p"));
  targetP.setValue("Re_DeltaCQ1_taup",myP.getValue("Re_DeltaCQ1p"));
  targetP.setValue("Im_DeltaCQ1_taup",myP.getValue("Im_DeltaCQ1p"));
  targetP.setValue("Re_DeltaCQ2_taup",myP.getValue("Re_DeltaCQ2p"));
  targetP.setValue("Im_DeltaCQ2_taup",myP.getValue("Im_DeltaCQ2p"));

}
#undef MODEL

// WC_nu --> GWC
#define MODEL WC_nu
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

  // Set everything to zero first
  for(auto par : targetP.getKeys())
    targetP.setValue(par, 0.0);

  targetP.setValue("Re_DeltaCLL_V", myP.getValue("Re_DeltaCL"));
  targetP.setValue("Im_DeltaCLL_V", myP.getValue("Im_DeltaCL"));
  targetP.setValue("Re_DeltaCRR_V", myP.getValue("Re_DeltaCR"));
  targetP.setValue("Im_DeltaCRR_V", myP.getValue("Im_DeltaCR"));

}
#undef MODEL

#undef PARENT

// WC --> WC_LUV
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

// WC --> WC_LR
void MODEL_NAMESPACE::WC_to_WC_LR (const ModelParameters& myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_friend calculations for WC -> WC_LR..."<<LogTags::info<<EOM;

  // Send all parameter values upstream to matching parameters in friend.
  targetP.setValues(myP);

  targetP.setValue("Re_DeltaC7p", myP.getValue("Re_DeltaC7"));
  targetP.setValue("Im_DeltaC7p", myP.getValue("Im_DeltaC7"));
  targetP.setValue("Re_DeltaC9p", myP.getValue("Re_DeltaC9"));
  targetP.setValue("Im_DeltaC9p", myP.getValue("Im_DeltaC9"));
  targetP.setValue("Re_DeltaC10p", myP.getValue("Re_DeltaC10"));
  targetP.setValue("Im_DeltaC10p", myP.getValue("Im_DeltaC10"));
  targetP.setValue("Re_DeltaCQ1p", myP.getValue("Re_DeltaCQ1"));
  targetP.setValue("Im_DeltaCQ1p", myP.getValue("Im_DeltaCQ1"));
  targetP.setValue("Re_DeltaCQ2p", myP.getValue("Re_DeltaCQ2"));
  targetP.setValue("Im_DeltaCQ2p", myP.getValue("Im_DeltaCQ2"));
}
#undef MODEL

