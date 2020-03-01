///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDMI to THDMIatQ
///
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
//   \date 2015 November
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Models/models/THDMIatQ.hpp"
// #include "gambit/Elements/spectrum.hpp"

// #include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_helper.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI
#define PARENT THDM
#define FRIEND THDMIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMI_to_THDMIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI --> THDMIatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("lambda_1", myP.getValue("lambda_1") );
  targetP.setValue("lambda_2", myP.getValue("lambda_2") );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", myP.getValue("m12_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );


  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}

// Translation function definition
void MODEL_NAMESPACE::THDMI_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI --> THDMIatQ.."<<LogTags::info<<EOM;

    const SMInputs& sminputs = *Dep::SMINPUTS;
    std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

    basis["lambda1"] = myP.getValue("lambda_1");
    basis["lambda2"] = myP.getValue("lambda_2");
    basis["lambda3"]= myP.getValue("lambda_3");
    basis["lambda4"]= myP.getValue("lambda_4");
    basis["lambda5"] = myP.getValue("lambda_5");
    basis["lambda6"] = myP.getValue("lambda_6");
    basis["lambda7"] = myP.getValue("lambda_7");
    basis["m12_2"] = myP.getValue("m12_2");
    basis["tanb"] = myP.getValue("tanb");

    SpecBit::fill_higgs_THDM_basis(basis, sminputs);

    targetP.setValue("Lambda_1", basis["Lambda1"] );
    targetP.setValue("Lambda_2", basis["Lambda2"] );
    targetP.setValue("Lambda_3", basis["Lambda3"] );
    targetP.setValue("Lambda_4", basis["Lambda4"] );
    targetP.setValue("Lambda_5", basis["Lambda5"] );
    targetP.setValue("Lambda_7", basis["Lambda7"] );
    targetP.setValue("m22_2", basis["M22_2"] );
    targetP.setValue("tanb", basis["tanb"] );

    std::vector<std::string> yukawa_keys = {"yu2_re_11", "yu2_im_11", "yu2_re_12", "yu2_im_12", "yu2_re_13", "yu2_im_13",
                                            "yu2_re_21", "yu2_im_21", "yu2_re_22", "yu2_im_22", "yu2_re_23", "yu2_im_23",
                                            "yu2_re_31", "yu2_im_31", "yu2_re_32", "yu2_im_32", "yu2_re_33", "yu2_im_33",
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

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef FRIEND
#undef MODEL