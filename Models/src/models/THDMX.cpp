///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///  \file
///
///  THDMX
///  -> 
///  THDMX 
///  (translation functions)
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Jun
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
#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Models/models/THDMIatQ.hpp"
#include "gambit/Models/models/THDMII.hpp"
#include "gambit/Models/models/THDMIIatQ.hpp"
#include "gambit/Models/models/THDMLS.hpp"
#include "gambit/Models/models/THDMLSatQ.hpp"
#include "gambit/Models/models/THDMflipped.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

std::map<std::string, double> THDM_create_empty_THDM_basis(){
    const double EMPTY = -1E10;
    std::map<std::string, double> basis;
    // create a complete list of keys for basis
    const std::vector<std::string> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7", "m12_2", "m11_2", "m22_2", \
                                        "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                        "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
    // fill entries in basis
    for(const auto& each_basis_key : basis_keys){
      basis.insert(std::make_pair(each_basis_key, EMPTY));
    }
    return basis;
}

void THDM_general_to_higgs(std::map<std::string, double>& input_basis, const Gambit::SMInputs& sminputs) {
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = input_basis["tanb"];
  double beta = atan(tanb);
  double sb = sin(beta), cb = cos(beta), tb = tan(beta);
  double ctb = 1./tb;
  double s2b = sin(2.*beta), c2b = cos(2.*beta);
  // initially try to fill from scalar basis
  // get values from coupling basis
  double lam1 = input_basis["lambda1"], lam2 = input_basis["lambda2"], lam3 = input_basis["lambda3"], lam4 = input_basis["lambda4"], lam5 = input_basis["lambda5"];
  double lam6 = input_basis["lambda6"], lam7 = input_basis["lambda7"], m12_2 = input_basis["m12_2"];
  double lam345 = lam3 + lam4 + lam5;
  // (also fill these in case they haven't been calculated)
  double m11_2 = m12_2*tb - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb); input_basis["m11_2"] = m11_2;
  double m22_2 = m12_2*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb); input_basis["m22_2"] = m22_2;
  input_basis["M12_2"] = (m11_2-m22_2)*s2b + m12_2*c2b;
  input_basis["M11_2"] = m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
  input_basis["M22_2"] = m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
  // do the basis conversion here
  input_basis["Lambda1"] = lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
  input_basis["Lambda2"] = lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
  input_basis["Lambda3"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
  input_basis["Lambda4"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
  input_basis["Lambda5"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
  input_basis["Lambda6"] = -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*beta)*lam6 + sb*sin(3.*beta)*lam7;
  input_basis["Lambda7"] = -0.5*s2b*(lam1*pow(sb,2)-lam2*pow(cb,2)+lam345*c2b) + sb*sin(3.*beta)*lam6 + cb*cos(3.*beta)*lam7;
}

#define MODEL  THDM
#define FRIEND THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDM_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_friend calculations for THDM --> THDMatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("Lambda_1", myP.getValue("Lambda_1") );
  targetP.setValue("Lambda_2", myP.getValue("Lambda_2") );
  targetP.setValue("Lambda_3", myP.getValue("Lambda_3") );
  targetP.setValue("Lambda_4", myP.getValue("Lambda_4") );
  targetP.setValue("Lambda_5", myP.getValue("Lambda_5") );
  targetP.setValue("Lambda_7", myP.getValue("Lambda_7") );
  targetP.setValue("m22_2", myP.getValue("m22_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );
  targetP.setValue("alpha", myP.getValue("alpha") );

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
    std::map<std::string, double> basis = THDM_create_empty_THDM_basis();

    basis["lambda1"] = myP.getValue("lambda_1");
    basis["lambda2"] = myP.getValue("lambda_2");
    basis["lambda3"]= myP.getValue("lambda_3");
    basis["lambda4"]= myP.getValue("lambda_4");
    basis["lambda5"] = myP.getValue("lambda_5");
    basis["lambda6"] = myP.getValue("lambda_6");
    basis["lambda7"] = myP.getValue("lambda_7");
    basis["m12_2"] = myP.getValue("m12_2");
    basis["tanb"] = myP.getValue("tanb");

    THDM_general_to_higgs(basis, sminputs);

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


#define MODEL  THDMII
#define PARENT THDM
#define FRIEND THDMIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMII_to_THDMIIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_FRIEND calculations for THDMII --> THDMIIatQ.."<<LogTags::info<<EOM;

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
     std::cout << "THDMII parameters:" << myP << std::endl;
     std::cout << "THDMIIatQ parameters   :" << targetP << std::endl;
   #endif
}


// Translation function definition
void MODEL_NAMESPACE::THDMII_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDMIatQ.."<<LogTags::info<<EOM;

      const SMInputs& sminputs = *Dep::SMINPUTS;
    std::map<std::string, double> basis = THDM_create_empty_THDM_basis();

    basis["lambda1"] = myP.getValue("lambda_1");
    basis["lambda2"] = myP.getValue("lambda_2");
    basis["lambda3"]= myP.getValue("lambda_3");
    basis["lambda4"]= myP.getValue("lambda_4");
    basis["lambda5"] = myP.getValue("lambda_5");
    basis["lambda6"] = myP.getValue("lambda_6");
    basis["lambda7"] = myP.getValue("lambda_7");
    basis["m12_2"] = myP.getValue("m12_2");
    basis["tanb"] = myP.getValue("tanb");

    THDM_general_to_higgs(basis, sminputs);

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
    std::cout << "THDMII parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef PARENT
#undef MODEL


#define MODEL  THDMIIatQ
#define PARENT THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDMIIatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMII --> THDMIIatQ.."<<LogTags::info<<EOM;

  targetP.setValue("lambda_1", myP.getValue("lambda_1") );
  targetP.setValue("lambda_2", myP.getValue("lambda_2") );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", myP.getValue("m12_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );
  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

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
    std::cout << "THDMIIatQ parameters:" << myP << std::endl;
    std::cout << "THDMatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL


#define MODEL  THDMLS
#define PARENT THDM
#define FRIEND THDMLSatQ

// Translation function definition
void MODEL_NAMESPACE::THDMLS_to_THDMLSatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_FRIEND calculations for THDMLS --> THDMLSatQ.."<<LogTags::info<<EOM;

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
     std::cout << "THDMLS parameters:" << myP << std::endl;
     std::cout << "THDMLSatQ parameters   :" << targetP << std::endl;
   #endif
}


// Translation function definition
void MODEL_NAMESPACE::THDMLS_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS --> THDMIatQ.."<<LogTags::info<<EOM;

      const SMInputs& sminputs = *Dep::SMINPUTS;
    std::map<std::string, double> basis = THDM_create_empty_THDM_basis();

    basis["lambda1"] = myP.getValue("lambda_1");
    basis["lambda2"] = myP.getValue("lambda_2");
    basis["lambda3"]= myP.getValue("lambda_3");
    basis["lambda4"]= myP.getValue("lambda_4");
    basis["lambda5"] = myP.getValue("lambda_5");
    basis["lambda6"] = myP.getValue("lambda_6");
    basis["lambda7"] = myP.getValue("lambda_7");
    basis["m12_2"] = myP.getValue("m12_2");
    basis["tanb"] = myP.getValue("tanb");

    THDM_general_to_higgs(basis, sminputs);

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

#undef FRIEND
#undef PARENT
#undef MODEL



#define MODEL  THDMflipped
#define PARENT THDM
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_to_THDMflippedatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
   logger()<<"Running interpret_as_FRIEND calculations for THDMflipped --> THDMflippedatQ.."<<LogTags::info<<EOM;

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
     std::cout << "THDMflipped parameters:" << myP << std::endl;
     std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
   #endif
}


// Translation function definition
void MODEL_NAMESPACE::THDMflipped_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMflipped --> THDMIatQ.."<<LogTags::info<<EOM;

    const SMInputs& sminputs = *Dep::SMINPUTS;
    std::map<std::string, double> basis = THDM_create_empty_THDM_basis();

    basis["lambda1"] = myP.getValue("lambda_1");
    basis["lambda2"] = myP.getValue("lambda_2");
    basis["lambda3"]= myP.getValue("lambda_3");
    basis["lambda4"]= myP.getValue("lambda_4");
    basis["lambda5"] = myP.getValue("lambda_5");
    basis["lambda6"] = myP.getValue("lambda_6");
    basis["lambda7"] = myP.getValue("lambda_7");
    basis["m12_2"] = myP.getValue("m12_2");
    basis["tanb"] = myP.getValue("tanb");

    THDM_general_to_higgs(basis, sminputs);

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
    std::cout << "THDMflipped parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef PARENT
#undef MODEL
