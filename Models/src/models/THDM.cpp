///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDM to THDMatQ
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
///   \date 2015 November
///
///  Cristian Sierra
///  cristian.sierra@monash.edu
///  Apr 2020
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMatQ.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDM
#define FRIEND THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDM_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_friend calculations for THDM --> THDMatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("lambda1",myP.getValue("lambda1"));
  targetP.setValue("lambda2",myP.getValue("lambda2"));
  targetP.setValue("lambda3",myP.getValue("lambda3"));
  targetP.setValue("lambda4",myP.getValue("lambda4"));
  targetP.setValue("lambda5",myP.getValue("lambda5"));
  targetP.setValue("lambda6",myP.getValue("lambda6"));
  targetP.setValue("lambda7",myP.getValue("lambda7"));
  targetP.setValue("m12_2",myP.getValue("m12_2"));
  targetP.setValue("tanb",myP.getValue("tanb"));

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
      targetP.setValue(yukawa_key, myP.getValue(yukawa_key));
  }

   // Done! Check that everything is ok if desired.
   #ifdef THDM_DBUG
     std::cout << "THDM parameters:" << myP << std::endl;
     std::cout << "THDMatQ parameters   :" << targetP << std::endl;
   #endif
}

#undef FRIEND
#undef MODEL
