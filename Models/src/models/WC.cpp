//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Translation function definitions for the
///  WC model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  WC      --> GWC
///  WC_LUV  --> GWC
///  WC_LR   --> GWC
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Tomas Gonzalo  
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 June
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/WC.hpp"

// WC --> GWC
#define MODEL  WC
#define PARENT GWC
void MODEL_NAMESPACE::WC_to_GWC (const ModelParameters &myP, ModelParameters &targetP)
{

   logger()<<"Running interpret_as_parent calculations for WC --> GWC."<<LogTags::info<<EOM;
     
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

}
#undef PARENT
#undef MODEL

// WC_LUV --> GWC
#define MODEL  WC_LUV
#define PARENT GWC
void MODEL_NAMESPACE::WC_LUV_to_GWC (const ModelParameters &myP, ModelParameters &targetP)
{

   logger()<<"Running interpret_as_parent calculations for WC_LUV --> GWC."<<LogTags::info<<EOM;
     
   // Set everything to zero first
   for(auto par : targetP.getKeys())
     targetP.setValue(par, 0.0);

   // Now send all parameter values upstream to those matching parameters in parent.
   targetP.setValues(myP,false);

}
#undef PARENT
#undef MODEL

// WC_LR --> GWC
#define MODEL  WC_LR
#define PARENT GWC
void MODEL_NAMESPACE::WC_LR_to_GWC (const ModelParameters &myP, ModelParameters &targetP)
{

   logger()<<"Running interpret_as_parent calculations for WC_LR --> GWC."<<LogTags::info<<EOM;
     
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

   targetP.setValue("Re_DeltaC7_e_Prime",myP.getValue("Re_DeltaC7_Prime"));
   targetP.setValue("Im_DeltaC7_e_Prime",myP.getValue("Im_DeltaC7_Prime"));
   targetP.setValue("Re_DeltaC9_e_Prime",myP.getValue("Re_DeltaC9_Prime"));
   targetP.setValue("Im_DeltaC9_e_Prime",myP.getValue("Im_DeltaC9_Prime"));
   targetP.setValue("Re_DeltaC10_e_Prime",myP.getValue("Re_DeltaC10_Prime"));
   targetP.setValue("Im_DeltaC10_e_Prime",myP.getValue("Im_DeltaC10_Prime"));
   targetP.setValue("Re_DeltaCQ1_e_Prime",myP.getValue("Re_DeltaCQ1_Prime"));
   targetP.setValue("Im_DeltaCQ1_e_Prime",myP.getValue("Im_DeltaCQ1_Prime"));
   targetP.setValue("Re_DeltaCQ2_e_Prime",myP.getValue("Re_DeltaCQ2_Prime"));
   targetP.setValue("Im_DeltaCQ2_e_Prime",myP.getValue("Im_DeltaCQ2_Prime"));

   targetP.setValue("Re_DeltaC7_mu_Prime",myP.getValue("Re_DeltaC7_Prime"));
   targetP.setValue("Im_DeltaC7_mu_Prime",myP.getValue("Im_DeltaC7_Prime"));
   targetP.setValue("Re_DeltaC9_mu_Prime",myP.getValue("Re_DeltaC9_Prime"));
   targetP.setValue("Im_DeltaC9_mu_Prime",myP.getValue("Im_DeltaC9_Prime"));
   targetP.setValue("Re_DeltaC10_mu_Prime",myP.getValue("Re_DeltaC10_Prime"));
   targetP.setValue("Im_DeltaC10_mu_Prime",myP.getValue("Im_DeltaC10_Prime"));
   targetP.setValue("Re_DeltaCQ1_mu_Prime",myP.getValue("Re_DeltaCQ1_Prime"));
   targetP.setValue("Im_DeltaCQ1_mu_Prime",myP.getValue("Im_DeltaCQ1_Prime"));
   targetP.setValue("Re_DeltaCQ2_mu_Prime",myP.getValue("Re_DeltaCQ2_Prime"));
   targetP.setValue("Im_DeltaCQ2_mu_Prime",myP.getValue("Im_DeltaCQ2_Prime"));

   targetP.setValue("Re_DeltaC7_tau_Prime",myP.getValue("Re_DeltaC7_Prime"));
   targetP.setValue("Im_DeltaC7_tau_Prime",myP.getValue("Im_DeltaC7_Prime"));
   targetP.setValue("Re_DeltaC9_tau_Prime",myP.getValue("Re_DeltaC9_Prime"));
   targetP.setValue("Im_DeltaC9_tau_Prime",myP.getValue("Im_DeltaC9_Prime"));
   targetP.setValue("Re_DeltaC10_tau_Prime",myP.getValue("Re_DeltaC10_Prime"));
   targetP.setValue("Im_DeltaC10_tau_Prime",myP.getValue("Im_DeltaC10_Prime"));
   targetP.setValue("Re_DeltaCQ1_tau_Prime",myP.getValue("Re_DeltaCQ1_Prime"));
   targetP.setValue("Im_DeltaCQ1_tau_Prime",myP.getValue("Im_DeltaCQ1_Prime"));
   targetP.setValue("Re_DeltaCQ2_tau_Prime",myP.getValue("Re_DeltaCQ2_Prime"));
   targetP.setValue("Im_DeltaCQ2_tau_Prime",myP.getValue("Im_DeltaCQ2_Prime"));

}
#undef PARENT
#undef MODEL
