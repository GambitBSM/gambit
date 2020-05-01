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

#include "gambit/Models/models/THDMflipped.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

#define MODEL  THDMflipped

// THDMflipped --> THDMflippedatQ
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_to_THDMflippedatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped --> THDMflippedatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",Dep::SMINPUTS->mZ);

  targetP.setValue("lambda1", myP.getValue("lambda1") );
  targetP.setValue("lambda2", myP.getValue("lambda2") );
  targetP.setValue("lambda3", myP.getValue("lambda3") );
  targetP.setValue("lambda4", myP.getValue("lambda4") );
  targetP.setValue("lambda5", myP.getValue("lambda5") );
  targetP.setValue("lambda6", myP.getValue("lambda6") );
  targetP.setValue("lambda7", myP.getValue("lambda7") );
  targetP.setValue("m12_2", myP.getValue("m12_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );


   // Done! Check that everything is ok if desired.
   #ifdef THDM_DBUG
     std::cout << "THDMflipped parameters:" << myP << std::endl;
     std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
   #endif
}

#undef FRIEND

// THDMflipped --> THDM
#define PARENT THDM

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflipped --> THDM.."<<LogTags::info<<EOM;

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
                                          "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
  targetP.setValue("yl2_re_11", sqrt(2)/v/sb * sminputs.mE);
  targetP.setValue("yl2_re_22", sqrt(2)/v/sb * sminputs.mMu);
  targetP.setValue("yl2_re_33", sqrt(2)/v/sb * sminputs.mTau);


  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL

// THDMflippedatQ --> THDMatQ
#define MODEL  THDMflippedatQ
#define PARENT THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflippedatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflippedatQ --> THDMatQ.."<<LogTags::info<<EOM;

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

  std::vector<std::string> yukawa_keys = {"yu2_im_11", "yu2_re_12", "yu2_im_12", "yu2_re_13", "yu2_im_13",
                                          "yu2_re_21", "yu2_im_21", "yu2_im_22", "yu2_re_23", "yu2_im_23",
                                          "yu2_re_31", "yu2_im_31", "yu2_re_32", "yu2_im_32", "yu2_im_33",
                                          "yd2_re_11", "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_re_22", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_re_33", "yd2_im_33",
                                          "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
  targetP.setValue("yl2_re_11", sqrt(2)/v/sb * sminputs.mE);
  targetP.setValue("yl2_re_22", sqrt(2)/v/sb * sminputs.mMu);
  targetP.setValue("yl2_re_33", sqrt(2)/v/sb * sminputs.mTau);


  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflippedatQ parameters:" << myP << std::endl;
    std::cout << "THDMatQ parameters:" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL
