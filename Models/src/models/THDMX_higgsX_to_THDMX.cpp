///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///  \file
///
///  THDMX_higgsX 
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
#include <math.h>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDMI_higgs.hpp"
#include "gambit/Models/models/THDMI_higgsatQ.hpp"
#include "gambit/Models/models/THDMII_higgs.hpp"
#include "gambit/Models/models/THDMII_higgsatQ.hpp"
#include "gambit/Models/models/THDMLS_higgs.hpp"
#include "gambit/Models/models/THDMLS_higgsatQ.hpp"
#include "gambit/Models/models/THDMflipped_higgs.hpp"
#include "gambit/Models/models/THDMflipped_higgsatQ.hpp"

#include "gambit/Models/models/THDMI.hpp"
#include "gambit/Models/models/THDMIatQ.hpp"
#include "gambit/Models/models/THDMII.hpp"
#include "gambit/Models/models/THDMIIatQ.hpp"
#include "gambit/Models/models/THDMLS.hpp"
#include "gambit/Models/models/THDMLSatQ.hpp"
#include "gambit/Models/models/THDMflipped.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

std::map<std::string, double> higgs_create_empty_THDM_basis(){
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

// Shared basis transformation function
void higgs_THDM_higgs_to_general(std::map<std::string, double>& input_basis, const Gambit::SMInputs& sminputs) {
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = input_basis["tanb"];
  double beta = atan(tanb);
  double sb = sin(beta), cb = cos(beta), tb = tan(beta);
  double ctb = 1./tb;
  double s2b = sin(2.*beta), c2b = cos(2.*beta);
  // get values from higgs basis
  double Lambda1 = input_basis["Lambda1"], Lambda2 = input_basis["Lambda2"], Lambda3 = input_basis["Lambda3"], Lambda4 = input_basis["Lambda4"], Lambda5 = input_basis["Lambda5"];
  double Lambda6 = input_basis["Lambda6"], Lambda7 = input_basis["Lambda7"], M12_2 = input_basis["M12_2"];
  // set values of coupling basis
  double Lam345 = Lambda3 + Lambda4 + Lambda5;
  double M11_2 = M12_2*tb - 0.5*v2 * (Lambda1*cb*cb + Lam345*sb*sb + 3.0*Lambda6*sb*cb + Lambda7*sb*sb*tb); 
  double M22_2 = M12_2*ctb - 0.5*v2 * (Lambda2*sb*sb + Lam345*cb*cb + Lambda6*cb*cb*ctb + 3.0*Lambda7*sb*cb);
  input_basis["m12_2"] = (M11_2-M22_2)*s2b + M12_2*c2b;
  // do the basis conversion here
  input_basis["lambda1"] = Lambda1*pow(cb,4) + Lambda2*pow(sb,4) + 0.5*Lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*Lambda6+pow(sb,2)*Lambda7);
  input_basis["lambda2"] = Lambda1*pow(sb,4) + Lambda2*pow(cb,4) + 0.5*Lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*Lambda6+pow(cb,2)*Lambda7);
  input_basis["lambda3"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda3 - s2b*c2b*(Lambda6-Lambda7);
  input_basis["lambda4"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda4 - s2b*c2b*(Lambda6-Lambda7);
  input_basis["lambda5"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda5 - s2b*c2b*(Lambda6-Lambda7);
  input_basis["lambda6"] = -0.5*s2b*(Lambda1*pow(cb,2)-Lambda2*pow(sb,2)-Lam345*c2b) + cb*cos(3.*beta)*Lambda6 + sb*sin(3.*beta)*Lambda7;
  input_basis["lambda7"] = -0.5*s2b*(Lambda1*pow(sb,2)-Lambda2*pow(cb,2)+Lam345*c2b) + sb*sin(3.*beta)*Lambda6 + cb*cos(3.*beta)*Lambda7;
  // fill extra inputs
  input_basis["m11_2"] = M11_2*pow(cb,2) + M22_2*pow(sb,2) - M12_2*s2b;
  input_basis["m22_2"] = M11_2*pow(sb,2) + M22_2*pow(cb,2) + M12_2*s2b;
}

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI_higgs
#define FRIEND THDMI

// Translation function definition
void MODEL_NAMESPACE::THDMI_higgs_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_higgs --> THDMI"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

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
    std::cout << "THDMI_higgs parameters:" << myP << std::endl;
    std::cout << "THDMI parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMI_higgsatQ
#define FRIEND THDMIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMI_higgsatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_higgsatQ --> THDMIatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

  targetP.setValue("lambda_1", basis["lambda1"] );
  targetP.setValue("lambda_2", basis["lambda2"] );
  targetP.setValue("lambda_3", basis["lambda3"] );
  targetP.setValue("lambda_4", basis["lambda4"] );
  targetP.setValue("lambda_5", basis["lambda5"] );
  targetP.setValue("lambda_6", basis["lambda6"] );
  targetP.setValue("lambda_7", basis["lambda7"] );
  targetP.setValue("m12_2", basis["m12_2"] );
  targetP.setValue("tanb", basis["tanb"] );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_higgsatQ parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMII_higgs
#define FRIEND THDMII

// Translation function definition
void MODEL_NAMESPACE::THDMII_higgs_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_higgs --> THDMII"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

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
    std::cout << "THDMII_higgs parameters:" << myP << std::endl;
    std::cout << "THDMII parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMII_higgsatQ
#define FRIEND THDMIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMII_higgsatQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_higgsatQ --> THDMIIatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

  targetP.setValue("lambda_1", basis["lambda1"] );
  targetP.setValue("lambda_2", basis["lambda2"] );
  targetP.setValue("lambda_3", basis["lambda3"] );
  targetP.setValue("lambda_4", basis["lambda4"] );
  targetP.setValue("lambda_5", basis["lambda5"] );
  targetP.setValue("lambda_6", basis["lambda6"] );
  targetP.setValue("lambda_7", basis["lambda7"] );
  targetP.setValue("m12_2", basis["m12_2"] );
  targetP.setValue("tanb", basis["tanb"] );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_higgsatQ parameters:" << myP << std::endl;
    std::cout << "THDMIIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_higgs
#define FRIEND THDMLS

// Translation function definition
void MODEL_NAMESPACE::THDMLS_higgs_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_higgs --> THDMLS"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

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
    std::cout << "THDMLS_higgs parameters:" << myP << std::endl;
    std::cout << "THDMLS parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_higgsatQ
#define FRIEND THDMLSatQ

// Translation function definition
void MODEL_NAMESPACE::THDMLS_higgsatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_higgsatQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

  targetP.setValue("lambda_1", basis["lambda1"] );
  targetP.setValue("lambda_2", basis["lambda2"] );
  targetP.setValue("lambda_3", basis["lambda3"] );
  targetP.setValue("lambda_4", basis["lambda4"] );
  targetP.setValue("lambda_5", basis["lambda5"] );
  targetP.setValue("lambda_6", basis["lambda6"] );
  targetP.setValue("lambda_7", basis["lambda7"] );
  targetP.setValue("m12_2", basis["m12_2"] );
  targetP.setValue("tanb", basis["tanb"] );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_higgsatQ parameters:" << myP << std::endl;
    std::cout << "THDMLSatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_higgs
#define FRIEND THDMflipped

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_higgs_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_higgs --> THDMflipped"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

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
    std::cout << "THDMflipped_higgs parameters:" << myP << std::endl;
    std::cout << "THDMflipped parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_higgsatQ
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_higgsatQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_higgsatQ --> THDMflippedatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = higgs_create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

  higgs_THDM_higgs_to_general(basis, sminputs);

  targetP.setValue("lambda_1", basis["lambda1"] );
  targetP.setValue("lambda_2", basis["lambda2"] );
  targetP.setValue("lambda_3", basis["lambda3"] );
  targetP.setValue("lambda_4", basis["lambda4"] );
  targetP.setValue("lambda_5", basis["lambda5"] );
  targetP.setValue("lambda_6", basis["lambda6"] );
  targetP.setValue("lambda_7", basis["lambda7"] );
  targetP.setValue("m12_2", basis["m12_2"] );
  targetP.setValue("tanb", basis["tanb"] );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_higgsatQ parameters:" << myP << std::endl;
    std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL