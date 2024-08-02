//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the THDMI
///  model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMI    --> THDM
///  THDMIatQ --> THDMatQ
///
///  THDMI_higgs --> THDMI
///  THDMI_higgsatQ --> THDMIatQ
///
///  THDMI_physical --> THDMI
///  THDMI_physicalatQ --> THDMIatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMI    --> THDMIatQ
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2015 November
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Jun
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/thdm_helpers.hpp"
#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

// Need to define MODEL, PARENT and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI

// THDMI --> THDMIatQ
#define FRIEND THDMIatQ
void MODEL_NAMESPACE::THDMI_to_THDMIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI --> THDMIatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin",Dep::SMINPUTS->mZ);
}
#undef FRIEND

// THDMI --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMI_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI --> THDM.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(1, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDMIatQ --> THDMatQ
#define MODEL  THDMIatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMIatQ_to_THDMatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMIatQ --> THDMatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
  add_Yukawas(1, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMI_higgs --> THDMI
#define MODEL  THDMI_higgs
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_higgs_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI_higgs --> THDMI"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMI_higgsatQ --> THDMIatQ
#define MODEL  THDMI_higgsatQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_higgsatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI_higgsatQ --> THDMIatQ"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin") );
}
#undef PARENT
#undef MODEL

//  THDMI_physical --> THDMI
#define MODEL THDMI_physical
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_physical_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMI_physical --> THDMI"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMI_physicalatQ --> THDMIatQ
#define MODEL THDMI_physicalatQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_physicalatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMI_physicalatQ --> THDMIatQ"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs --> THDMI (based on arXiv:1507.04281)
#define MODEL  THDMI_hybrid_Higgs
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_hybrid_Higgs_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_Higgs --> THDMI"<<LogTags::info<<EOM;
  hybrid_higgs_to_generic(true, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_HiggsatQ --> THDMIatQ (based on arXiv:1507.04281)
#define MODEL  THDMI_hybrid_HiggsatQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_hybrid_HiggsatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_HiggsatQ --> THDMIatQ"<<LogTags::info<<EOM;
  hybrid_higgs_to_generic(false, *Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs2 --> THDMI (based on arXiv:1507.04281)
#define MODEL  THDMI_hybrid_Higgs2
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_hybrid_Higgs2_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_Higgs2 --> THDMI"<<LogTags::info<<EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs2atQ --> THDMIatQ (based on arXiv:1507.04281)
#define MODEL  THDMI_hybrid_Higgs2atQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_hybrid_Higgs2atQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_Higgs2atQ --> THDMIatQ"<<LogTags::info<<EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL
