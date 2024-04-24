//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Translation function definitions for the
///  SMEFT model and its variations.
///
///  Contains the interpret-as translation
///  functions for:
///
///  SMEFT_FV  --> GWC
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Feb
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/WC.hpp"
#include "gambit/Models/models/SMEFT.hpp"

// SMEFT_FV --> GWC
#define PARENT GWC
#define MODEL SMEFT_FV
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

  USE_MODEL_PIPE(PARENT)

  // Set everything to zero first
  for(auto par : targetP.getKeys())
    targetP.setValue(par, 0.0);

  // Tree level value of sin2theta, from SMINPUTS
  double mz = Dep::SMINPUTS->mZ;
  double am1 = Dep::SMINPUTS->alphainv;
  double sin2thetaW_tree = 0.5 - sqrt(0.25 - pi / (root2*mz*mz*am1*Dep::SMINPUTS->GF));
  double zeta = 1. - 4.*sin2thetaW_tree;

  // Fill GWC parameters according to 1409.4557
  // TODO: This assumes that the WCS in SMEFT are flavour universal
  targetP.setValue("Re_DeltaC9_e", myP.getValue("Re_cqe") + myP.getValue("Re_cql1") + myP.getValue("Re_cql3") - zeta/2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC9_e", myP.getValue("Im_cqe") + myP.getValue("Im_cql1") + myP.getValue("Im_cql3") - zeta/2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));
  targetP.setValue("Re_DeltaC10_e", myP.getValue("Re_cqe") - myP.getValue("Re_cql1") - myP.getValue("Re_cql3") + 1./2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC10_e", myP.getValue("Im_cqe") - myP.getValue("Im_cql1") - myP.getValue("Im_cql3") + 1./2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));

  targetP.setValue("Re_DeltaC9_mu", myP.getValue("Re_cqe") + myP.getValue("Re_cql1") + myP.getValue("Re_cql3") - zeta/2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC9_mu", myP.getValue("Im_cqe") + myP.getValue("Im_cql1") + myP.getValue("Im_cql3") - zeta/2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));
  targetP.setValue("Re_DeltaC10_mu", myP.getValue("Re_cqe") - myP.getValue("Re_cql1") - myP.getValue("Re_cql3") + 1./2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC10_mu", myP.getValue("Im_cqe") - myP.getValue("Im_cql1") - myP.getValue("Im_cql3") + 1./2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));

  targetP.setValue("Re_DeltaC9_tau", myP.getValue("Re_cqe") + myP.getValue("Re_cql1") + myP.getValue("Re_cql3") - zeta/2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC9_tau", myP.getValue("Im_cqe") + myP.getValue("Im_cql1") + myP.getValue("Im_cql3") - zeta/2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));
  targetP.setValue("Re_DeltaC10_tau", myP.getValue("Re_cqe") - myP.getValue("Re_cql1") - myP.getValue("Re_cql3") + 1./2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaC10_tau", myP.getValue("Im_cqe") - myP.getValue("Im_cql1") - myP.getValue("Im_cql3") + 1./2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));

  targetP.setValue("Re_DeltaC9p_e", myP.getValue("Re_cde") + myP.getValue("Re_cdl") - zeta/2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC9p_e", myP.getValue("Im_cde") + myP.getValue("Im_cdl") - zeta/2*myP.getValue("Im_cHd"));
  targetP.setValue("Re_DeltaC10p_e", myP.getValue("Re_cde") - myP.getValue("Re_cdl") + 1./2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC10p_e", myP.getValue("Im_cde") - myP.getValue("Im_cdl") + 1./2*myP.getValue("Im_cHd"));

  targetP.setValue("Re_DeltaC9p_mu", myP.getValue("Re_cde") + myP.getValue("Re_cdl") - zeta/2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC9p_mu", myP.getValue("Im_cde") + myP.getValue("Im_cdl") - zeta/2*myP.getValue("Im_cHd"));
  targetP.setValue("Re_DeltaC10p_mu", myP.getValue("Re_cde") - myP.getValue("Re_cdl") + 1./2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC10p_mu", myP.getValue("Im_cde") - myP.getValue("Im_cdl") + 1./2*myP.getValue("Im_cHd"));

  targetP.setValue("Re_DeltaC9p_tau", myP.getValue("Re_cde") + myP.getValue("Re_cdl") - zeta/2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC9p_tau", myP.getValue("Im_cde") + myP.getValue("Im_cdl") - zeta/2*myP.getValue("Im_cHd"));
  targetP.setValue("Re_DeltaC10p_tau", myP.getValue("Re_cde") - myP.getValue("Re_cdl") + 1./2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaC10p_tau", myP.getValue("Im_cde") - myP.getValue("Im_cdl") + 1./2*myP.getValue("Im_cHd"));

  targetP.setValue("Re_DeltaCLL_V", myP.getValue("Re_cql1") - myP.getValue("Re_cql3") + 1./2*(myP.getValue("Re_cHq1") + myP.getValue("Re_cHq3")));
  targetP.setValue("Im_DeltaCLL_V", myP.getValue("Im_cql1") - myP.getValue("Im_cql3") + 1./2*(myP.getValue("Im_cHq1") + myP.getValue("Im_cHq3")));
  targetP.setValue("Re_DeltaCRR_V", myP.getValue("Re_cdl") + 1./2*myP.getValue("Re_cHd"));
  targetP.setValue("Im_DeltaCRR_V", myP.getValue("Im_cdl") + 1./2*myP.getValue("Im_cHd"));

}
#undef MODEL
