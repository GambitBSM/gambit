///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDMLS_physical to THDMLS
///
///  *********************************************
///
///  Authors
///  =======
///
///  Filip Rajec (filip.rajec@adelaide.edu.au)
///  2019 
///
///  *********************************************
#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDM.hpp"
#include "gambit/Models/models/THDMLS_physical.hpp"
#include "gambit/Models/models/THDMLS.hpp"
// #include "gambit/Models/models/THDMLSatQ.hpp"
// #include "gambit/Elements/spectrum.hpp"

// #include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMLS_physical
#define PARENT THDM
#define FRIEND THDMLS

// Translation function definition
void MODEL_NAMESPACE::THDMLS_physical_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_physical --> THDMLS"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

  basis["m_h"] = myP.getValue("m_h");
  basis["m_H"] = myP.getValue("m_H");
  basis["m_A"]= myP.getValue("m_A");
  basis["m_Hp"]= myP.getValue("m_Hp");
  basis["m12_2"] = myP.getValue("m12_2");
  basis["tanb"] = myP.getValue("tanb");
  basis["sba"] = myP.getValue("sba");
  basis["lambda6"] = myP.getValue("lambda_6");
  basis["lambda7"] = myP.getValue("lambda_7");

  // Check for problematic parameter choices here

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

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_physical parameters:" << myP << std::endl;
    std::cout << "THDMLS parameters   :" << targetP << std::endl;
  #endif
}

// Translation function definition
void MODEL_NAMESPACE::THDMLS_physical_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS --> THDMLSatQ.."<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

  basis["m_h"] = myP.getValue("m_h");
  basis["m_H"] = myP.getValue("m_H");
  basis["m_A"]= myP.getValue("m_A");
  basis["m_Hp"]= myP.getValue("m_Hp");
  basis["m12_2"] = myP.getValue("m12_2");
  basis["tanb"] = myP.getValue("tanb");
  basis["sba"] = myP.getValue("sba");
  basis["lambda6"] = myP.getValue("lambda_6");
  basis["lambda7"] = myP.getValue("lambda_7");

  SpecBit::fill_generic_THDM_basis(basis, sminputs);
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
    std::cout << "THDMLS parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef FRIEND
#undef MODEL