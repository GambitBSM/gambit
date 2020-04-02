///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDM_physical to THDM
///
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///  Cristian Sierra
///  cristian.sierra@monash.edu
///  Mar 2020
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDM_physical.hpp"


// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDM_physical
#define PARENT THDM

// Translation function definition
void MODEL_NAMESPACE::THDM_physical_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDM --> THDM_physical.."<<LogTags::info<<EOM;

      const SMInputs& sminputs = *Dep::SMINPUTS;
    std::map<std::string, double> basis = create_empty_THDM_basis();
    
   // physical basis
   basis["mh2"] = myP.getValue("mh_2")
   basis["mH2"] = myP.getValue("mH_2")
   basis["mA2"] = myP.getValue("mA_2")
   basis["mC2"] = myP.getValue("mC_2")
   basis["m12_2"] = myP.getValue("m12_2");
   basis["lambda6"] = myP.getValue("lambda_6");
   basis["lambda7"] = myP.getValue("lambda_7");
   basis["tanb"] = myP.getValue("tanb");
   basis["sba"] = myP.getValue("sba");
   
 
   //generic basis
   double mh2 =  myP.getValue("mh2"), mH2 =  myP.getValue("mH2"), mA2 =  myP.getValue("mA2"), mC2 =  myP.getValue("mC2");
   double alpha = beta - asin(input_basis["sba"]);
   double ca = cos(alpha), sa = sin(alpha);
   double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
   double tb  = myP.getValue("tanb");
   double ctb  = 1./tb;
   double beta = atan(tb);
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

    SpecBit::fill_generic_THDM_basis(basis, sminputs);

    targetP.setValue("lambda_1", basis["lambda1"] );
    targetP.setValue("lambda_2", basis["lambda2"] );
    targetP.setValue("lambda_3", basis["lambda3"] );
    targetP.setValue("lambda_4", basis["lambda4"] );
    targetP.setValue("lambda_5", basis["lambda5"] );
    targetP.setValue("lambda_6", basis["lambda6"] );
    targetP.setValue("lambda_7", basis["lambda7"] );
    targetP.setValue("m12_2", basis["m12_2"] );
    targetP.setValue("tanb", basis["tanb"] );
    targetP.setValue("alpha", basis["alpha"] );


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


}

#undef PARENT
#undef MODEL
