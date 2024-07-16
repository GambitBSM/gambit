//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDMII model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMII    --> THDM
///  THDMIIatQ --> THDMatQ
///
///  THDMII_higgs --> THDMII
///  THDMII_higgsatQ --> THDMIIatQ
///
///  THDMII_physical --> THDMII
///  THDMII_physicalatQ --> THDMIIatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMII    --> THDMIIatQ
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
#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMII.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

#define MODEL THDMII

// THDMII --> THDMIIatQ
#define FRIEND THDMIIatQ
void MODEL_NAMESPACE::THDMII_to_THDMIIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII --> THDMIIatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin",Dep::SMINPUTS->mZ);
}
#undef FRIEND

// THDMII --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMII_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDM.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  add_Yukawas(2, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

// THDMII_physical2 --> THDMII_physical
#define MODEL THDMII_physical2
#define PARENT THDMII_physical
void MODEL_NAMESPACE::THDMII_physical2_to_THDMII_physical (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDM.."<<LogTags::info<<EOM;

  targetP.setValue("mh", myP.getValue("mh"));
  targetP.setValue("mH", myP.getValue("mH"));
  targetP.setValue("mA", myP.getValue("mA"));
  targetP.setValue("mHp", myP.getValue("mHp"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("sba", sin(myP.getValue("ba")));
  targetP.setValue("tanb", myP.getValue("tanb"));
}
#undef PARENT
#undef MODEL

// THDMII_physical2atQ --> THDMII_physicalatQ
#define MODEL THDMII_physical2atQ
#define PARENT THDMII_physicalatQ
void MODEL_NAMESPACE::THDMII_physical2atQ_to_THDMII_physicalatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDM.."<<LogTags::info<<EOM;

  targetP.setValue("mh", myP.getValue("mh"));
  targetP.setValue("mH", myP.getValue("mH"));
  targetP.setValue("mA", myP.getValue("mA"));
  targetP.setValue("mHp", myP.getValue("mHp"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("sba", sin(myP.getValue("ba")));
  targetP.setValue("tanb", myP.getValue("tanb"));
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

// THDMIIatQ --> THDMatQ
#define MODEL THDMIIatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMIIatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMIIatQ --> THDMatQ.."<<LogTags::info<<EOM;
  generic_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
  add_Yukawas(2, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMII_higgs --> THDMII
#define MODEL  THDMII_higgs
#define PARENT THDMII
void MODEL_NAMESPACE::THDMII_higgs_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMII_higgs --> THDMII"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMII_higgsatQ --> THDMIIatQ
#define MODEL  THDMII_higgsatQ
#define PARENT THDMIIatQ
void MODEL_NAMESPACE::THDMII_higgsatQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpret_as_parent calculations for THDMII_higgsatQ --> THDMIIatQ"<<LogTags::info<<EOM;
  higgs_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin") );
}
#undef PARENT
#undef MODEL

//  THDMII_physical --> THDMII
#define MODEL THDMII_physical
#define PARENT THDMII
void MODEL_NAMESPACE::THDMII_physical_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger()<<"Running interpre_as_parent calculations for THDMII_physical --> THDMII"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMII_physicalatQ --> THDMIIatQ
#define MODEL THDMII_physicalatQ
#define PARENT THDMIIatQ
void MODEL_NAMESPACE::THDMII_physicalatQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMII_physicalatQ --> THDMIIatQ"<<LogTags::info<<EOM;
  physical_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs --> THDMI (based on arXiv:1507.04281)
#define MODEL THDMII_hybrid_Higgs
#define PARENT THDMII
void MODEL_NAMESPACE::THDMII_hybrid_Higgs_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger() << "Running interpret_as_PARENT calculations for THDMII_hybrid_Higgs --> THDMII" << LogTags::info << EOM;
  hybrid_higgs_to_generic(true, *Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMII_hybrid_HiggsatQ --> THDMIIatQ (based on arXiv:1507.04281)
#define MODEL THDMII_hybrid_HiggsatQ
#define PARENT THDMIIatQ
void MODEL_NAMESPACE::THDMII_hybrid_HiggsatQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger() << "Running interpret_as_PARENT calculations for THDMII_hybrid_HiggsatQ --> THDMIIatQ" << LogTags::info << EOM;
  hybrid_higgs_to_generic(false, *Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_Higgs2 --> THDMI (based on arXiv:1507.04281)
#define MODEL THDMII_hybrid_Higgs2
#define PARENT THDMII
void MODEL_NAMESPACE::THDMII_hybrid_Higgs2_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger() << "Running interpret_as_PARENT calculations for THDMII_hybrid_Higgs2 --> THDMII" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
}
#undef PARENT
#undef MODEL

//  THDMII_hybrid_Higgs2atQ --> THDMIIatQ (based on arXiv:1507.04281)
#define MODEL THDMII_hybrid_Higgs2atQ
#define PARENT THDMIIatQ
void MODEL_NAMESPACE::THDMII_hybrid_Higgs2atQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT)
  logger() << "Running interpret_as_PARENT calculations for THDMII_hybrid_Higgs2atQ --> THDMIIatQ" << LogTags::info << EOM;
  hybrid_higgs2_to_generic(*Dep::SMINPUTS, myP, targetP);
  targetP.setValue("Qin", myP.getValue("Qin"));
}
#undef PARENT
#undef MODEL
