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
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMII.hpp"
#include "gambit/Models/models/THDMIIatQ.hpp"

#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

#define MODEL THDMII

// THDMII --> THDMIIatQ
#define FRIEND THDMIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMII_to_THDMIIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_FRIEND calculations for THDMII --> THDMIIatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("lambda1", myP.getValue("lambda1"));
  targetP.setValue("lambda2", myP.getValue("lambda2"));
  targetP.setValue("lambda3", myP.getValue("lambda3"));
  targetP.setValue("lambda4", myP.getValue("lambda4"));
  targetP.setValue("lambda5", myP.getValue("lambda5"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));


   // Done! Check that everything is ok if desired.
   #ifdef THDM_DBUG
     std::cout << "THDMII parameters:" << myP << std::endl;
     std::cout << "THDMIIatQ parameters   :" << targetP << std::endl;
   #endif
}

#undef FRIEND

// THDMII --> THDM
#define PARENT THDM

// Translation function definition
void MODEL_NAMESPACE::THDMII_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDM.."<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  targetP.setValue("lambda1", myP.getValue("lambda1"));
  targetP.setValue("lambda2", myP.getValue("lambda2"));
  targetP.setValue("lambda3", myP.getValue("lambda3"));
  targetP.setValue("lambda4", myP.getValue("lambda4"));
  targetP.setValue("lambda5", myP.getValue("lambda5"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));

  std::vector<std::string> yukawa_keys = {"yu2_im_11", "yu2_re_12", "yu2_im_12", "yu2_re_13", "yu2_im_13",
                                          "yu2_re_21", "yu2_im_21", "yu2_im_22", "yu2_re_23", "yu2_im_23",
                                          "yu2_re_31", "yu2_im_31", "yu2_re_32", "yu2_im_32", "yu2_im_33",
                                          "yd2_re_11", "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_re_22", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_re_33", "yd2_im_33",
                                          "yl2_re_11", "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_re_22", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_re_33", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb*sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb*sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb*sminputs.mT);

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL

// THDMIIatQ --> THDMatQ
#define MODEL THDMIIatQ
#define PARENT THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDMIIatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMIIatQ --> THDMatQ.."<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  targetP.setValue("lambda1", myP.getValue("lambda1"));
  targetP.setValue("lambda2", myP.getValue("lambda2"));
  targetP.setValue("lambda3", myP.getValue("lambda3"));
  targetP.setValue("lambda4", myP.getValue("lambda4"));
  targetP.setValue("lambda5", myP.getValue("lambda5"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));

  targetP.setValue("Qin", myP.getValue("Qin"));
  targetP.setValue("QrunTo", myP.getValue("QrunTo"));

  std::vector<std::string> yukawa_keys = {"yu2_im_11", "yu2_re_12", "yu2_im_12", "yu2_re_13", "yu2_im_13",
                                          "yu2_re_21", "yu2_im_21", "yu2_im_22", "yu2_re_23", "yu2_im_23",
                                          "yu2_re_31", "yu2_im_31", "yu2_re_32", "yu2_im_32", "yu2_im_33",
                                          "yd2_re_11", "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_re_22", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_re_33", "yd2_im_33",
                                          "yl2_re_11", "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_re_22", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_re_33", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb*sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb*sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb*sminputs.mT);

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMIIatQ parameters:" << myP << std::endl;
    std::cout << "THDMatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL
