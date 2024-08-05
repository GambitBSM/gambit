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

  const SMInputs& sminputs = *Dep::SMINPUTS;

  //generic basis
  double mh2 =  myP.getValue("mh2"), mH2 =  myP.getValue("mH2"), mA2 =  myP.getValue("mA2"), mC2 =  myP.getValue("mC2");
  double tb  = myP.getValue("tanb");
  double beta = atan(tb);
  double alpha = beta - asin(myP.getValue("sba"));
  double ca = cos(alpha), sa = sin(alpha);
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double ctb  = 1./tb;
  double cb = cos(beta), sb = sin(beta);
  double lambda1 = (mH2*pow(ca,2)+mh2*pow(sa,2)-myP.getValue("m12_2")*tb)/v2/pow(cb,2)-1.5*myP.getValue("lambda6")*tb+0.5*myP.getValue("lambda7")*pow(tb,3);
  double lambda2 = (mH2*pow(sa,2)+mh2*pow(ca,2)-myP.getValue("m12_2")*ctb)/v2/pow(sb,2)+0.5*myP.getValue("lambda6")*pow(ctb,3)-1.5*myP.getValue("lambda7")*ctb;
  double lambda3 = ((mH2-mh2)*ca*sa+2.*mC2*sb*cb-myP.getValue("m12_2"))/v2/sb/cb-0.5*myP.getValue("lambda6")*ctb-0.5*myP.getValue("lambda7")*tb;
  double lambda4 = ((mA2-2.*mC2)*cb*sb+myP.getValue("m12_2"))/v2/sb/cb-0.5*myP.getValue("lambda6")*ctb-0.5*myP.getValue("lambda7")*tb;
  double lambda5 = (myP.getValue("m12_2")-mA2*sb*cb)/v2/sb/cb-0.5*myP.getValue("lambda6")*ctb-0.5*myP.getValue("lambda7")*tb;

  targetP.setValue("lambda1",lambda1);
  targetP.setValue("lambda2",lambda2);
  targetP.setValue("lambda3",lambda3);
  targetP.setValue("lambda4",lambda4);
  targetP.setValue("lambda5",lambda5);
  targetP.setValue("lambda6",myP.getValue("lambda6"));
  targetP.setValue("lambda7",myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));
  
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
