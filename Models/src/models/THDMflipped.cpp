//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDMflipped model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMflipped    --> THDM
///  THDMflippedatQ --> THDMatQ
///
///  THDMflipped_higgs --> THDMflipped
///  THDMflipped_higgsatQ --> THDMflippedatQ
///
///  THDMflipped_physical --> THDMflipped
///  THDMflipped_physicalatQ --> THDMflippedatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMflipped    --> THDMflippedatQ
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
#include "gambit/Models/models/THDMflipped.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

#define MODEL  THDMflipped

// THDMflipped --> THDMflippedatQ
#define FRIEND THDMflippedatQ
void MODEL_NAMESPACE::THDMflipped_to_THDMflippedatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped --> THDMflippedatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin",Dep::SMINPUTS->mZ);
}
#undef FRIEND

// THDMflipped --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMflipped_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflipped --> THDM.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(4, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDMflippedatQ --> THDMatQ
#define MODEL  THDMflippedatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMflippedatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflippedatQ --> THDMatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
  add_Yukawas(4, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMflipped_higgs --> THDMflipped
#define MODEL  THDMflipped_higgs
#define PARENT THDMflipped
void MODEL_NAMESPACE::THDMflipped_higgs_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflipped_higgs --> THDMflipped"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMflipped_higgsatQ --> THDMflippedatQ
#define MODEL  THDMflipped_higgsatQ
#define PARENT THDMflippedatQ
void MODEL_NAMESPACE::THDMflipped_higgsatQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflipped_higgsatQ --> THDMflippedatQ"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin") );
}
#undef PARENT
#undef MODEL

//  THDMflipped_physical --> THDMflipped
#define MODEL THDMflipped_physical
#define PARENT THDMflipped
void MODEL_NAMESPACE::THDMflipped_physical_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMflipped_physical --> THDMflipped"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMflipped_physicalatQ --> THDMflippedatQ
#define MODEL THDMflipped_physicalatQ
#define PARENT THDMflippedatQ
void MODEL_NAMESPACE::THDMflipped_physicalatQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMflipped_physicalatQ --> THDMflippedatQ"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMflipped_hybrid_Higgs --> THDMflipped (based on arXiv:1507.04281)
#define MODEL THDMflipped_hybrid_Higgs
#define PARENT THDMflipped
void MODEL_NAMESPACE::THDMflipped_hybrid_Higgs_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMflipped_hybrid_Higgs --> THDMflipped" << LogTags::info << EOM;
  hybrid_higgs_to_generic(true, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMflipped_hybrid_HiggsatQ --> THDMflippedatQ (based on arXiv:1507.04281)
#define MODEL THDMflipped_hybrid_HiggsatQ
#define PARENT THDMflippedatQ
void MODEL_NAMESPACE::THDMflipped_hybrid_HiggsatQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMflipped_hybrid_HiggsatQ --> THDMflippedatQ" << LogTags::info << EOM;
  hybrid_higgs_to_generic(false, *Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMflipped_hybrid_Higgs2 --> THDMflipped (based on arXiv:1507.04281)
#define MODEL THDMflipped_hybrid_Higgs2
#define PARENT THDMflipped
void MODEL_NAMESPACE::THDMflipped_hybrid_Higgs2_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMflipped_hybrid_Higgs2 --> THDMflipped" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMflipped_hybrid_Higgs2atQ --> THDMflippedatQ (based on arXiv:1507.04281)
#define MODEL THDMflipped_hybrid_Higgs2atQ
#define PARENT THDMflippedatQ
void MODEL_NAMESPACE::THDMflipped_hybrid_Higgs2atQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger() << "Running interpret_as_PARENT calculations for THDMflipped_hybrid_Higgs2atQ --> THDMflippedatQ" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL
