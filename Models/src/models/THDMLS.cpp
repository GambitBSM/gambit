//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDMLS model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMLS    --> THDM
///  THDMLSatQ --> THDMatQ
///
///  THDMLS_higgs --> THDMLS
///  THDMLS_higgsatQ --> THDMLSatQ
///
///  THDMLS_physical --> THDMLS
///  THDMLS_physicalatQ --> THDMLSatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMLS    --> THDMLSatQ
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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019
///  \date 2020 Jun
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  \date 2021 Mar
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/thdm_helpers.hpp"
#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Models/models/THDMLS.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

#define MODEL  THDMLS

// THDMLS --> THDMLSatQ
#define FRIEND THDMLSatQ
void MODEL_NAMESPACE::THDMLS_to_THDMLSatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS --> THDMLSatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin",Dep::SMINPUTS->mZ);
}
#undef FRIEND

// THDMLS --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMLS_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS --> THDM.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(3, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDMLSatQ --> THDMatQ
#define MODEL THDMLSatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMLSatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLSatQ --> THDMatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
  add_Yukawas(3, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMLS_higgs --> THDMLS
#define MODEL  THDMLS_higgs
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_higgs_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS_higgs --> THDMLS"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMLS_higgsatQ --> THDMLSatQ
#define MODEL  THDMLS_higgsatQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_higgsatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS_higgsatQ --> THDMLSatQ"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin") );
}
#undef PARENT
#undef MODEL

//  THDMLS_physical --> THDMLS
#define MODEL THDMLS_physical
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_physical_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMLS_physical --> THDMLS"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMLS_physicalatQ --> THDMLSatQ
#define MODEL THDMLS_physicalatQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_physicalatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMLS_physicalatQ --> THDMLSatQ"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs --> THDMI (based on arXiv:1507.04281)
#define MODEL THDMLS_hybrid_Higgs
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_hybrid_Higgs_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMLS_hybrid_Higgs --> THDMLS" << LogTags::info << EOM;
  hybrid_higgs_to_generic(true, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMLS_hybrid_HiggsatQ --> THDMLSatQ (based on arXiv:1507.04281)
#define MODEL THDMLS_hybrid_HiggsatQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_hybrid_HiggsatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMLS_hybrid_HiggsatQ --> THDMLSatQ" << LogTags::info << EOM;
  hybrid_higgs_to_generic(false, *Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs --> THDMI (based on arXiv:1507.04281)
#define MODEL THDMLS_hybrid_Higgs2
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_hybrid_Higgs2_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMLS_hybrid_Higgs2 --> THDMLS" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMLS_hybrid_Higgs2atQ --> THDMLSatQ (based on arXiv:1507.04281)
#define MODEL THDMLS_hybrid_Higgs2atQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_hybrid_Higgs2atQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMLS_hybrid_Higgs2atQ --> THDMLSatQ" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL
