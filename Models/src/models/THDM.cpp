//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDM model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDM          --> THDMatQ
///  THDM_higgs    --> THDM
///  THDM_physical --> THDM
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
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 Apr
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
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

// THDM --> THDMatQ
#define MODEL  THDM
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDM_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDM --> THDMatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin",Dep::SMINPUTS->mZ);
  add_Yukawas(0, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDM_higgs --> THDM
#define MODEL  THDM_higgs
#define PARENT THDM
void MODEL_NAMESPACE::THDM_higgs_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDM_higgs --> THDM.."<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(0, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDM_physical --> THDM
#define MODEL  THDM_physical
#define PARENT THDM
void MODEL_NAMESPACE::THDM_physical_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDM_physical --> THDM.."<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(0, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDM_hybrid_Higgs --> THDM (based on arXiv:1507.04281)
#define MODEL THDM_hybrid_Higgs
#define PARENT THDM
void MODEL_NAMESPACE::THDM_hybrid_Higgs_to_THDM(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDM_hybrid_Higgs --> THDM" << LogTags::info << EOM;
  hybrid_higgs_to_generic(true, *Dep::SMINPUTS, myP, targetP);
  add_Yukawas(0, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL
