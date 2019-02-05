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
//   \date 2015 November
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDMLS.hpp"
#include "gambit/Models/models/THDMLSatQ.hpp"
// #include "gambit/Elements/spectrum.hpp"

// #include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
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

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  double lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7;
  double tanb, m12_2;

  // to be implemented as a capability in SpecBit 
  // **

  // const SMInputs& SM = *Dep::SMINPUTS;
  double GF = Dep::SMINPUTS->GF;

  double v2 = 1./(sqrt(2)*GF);
  // double v2 = 247.0*247.0;

  double sba = myP.getValue("sba");
  tanb = myP.getValue("tanb");

  double b = atan(tanb);
  double beta = - b; //for all equations needed when converting to coupling basis
  double sb=sin(beta);
  double s2b=sin(2.*beta);
  double s3b=sin(3.*beta);
  double s2b2=s2b*s2b;
  double sb2=sb*sb;
  double sb4=sb2*sb2;
  double cb=cos(beta);
  double c2b=cos(2.*beta);
  double c3b=cos(3.*beta);
  double cb2=cb*cb;
  double cb4=cb2*cb2;

  double cba = sqrt(1-sba*sba); //should always be the positive value
  double s2ba = 2*sba*cba;
  double c2ba = sqrt(1-s2ba*s2ba);
  double t2ba = s2ba/c2ba;

  double Lambda1 = myP.getValue("Lambda1");
  double Lambda2 = myP.getValue("Lambda2");
  double Lambda3 = myP.getValue("Lambda3");
  double Lambda4 = myP.getValue("Lambda4");
  double Lambda5 = myP.getValue("Lambda5");
  double Lambda7 = myP.getValue("Lambda7");
  double M22_2 = myP.getValue("M22_2");

  double m_Hp2 = M22_2 + 0.5*v2*Lambda3;
  double mA2 = m_Hp2 - 0.5*v2*(Lambda5-Lambda4);

  double Lambda6 = t2ba/(2*v2) * (mA2 + v2*(Lambda5-Lambda1));
  if (sba<0.0) Lambda6 = -Lambda6;

  m12_2 = -0.5*Lambda6*v2;

  double lambda345=Lambda3+Lambda4+Lambda5;
  // See hep-ph/0504050
  lambda1 =  Lambda1*cb4+Lambda2*sb4+0.5*lambda345*s2b2+2.*s2b*(cb2*Lambda6+sb2*Lambda7);
  lambda2 =  Lambda1*sb4+Lambda2*cb4+0.5*lambda345*s2b2-2.*s2b*(sb2*Lambda6+cb2*Lambda7);
  lambda3 =  0.25*s2b2*(Lambda1+Lambda2-2*lambda345)+Lambda3-s2b*c2b*(Lambda6-Lambda7);
  lambda4 =  0.25*s2b2*(Lambda1+Lambda2-2*lambda345)+Lambda4-s2b*c2b*(Lambda6-Lambda7);
  lambda5 =  0.25*s2b2*(Lambda1+Lambda2-2*lambda345)+Lambda5-s2b*c2b*(Lambda6-Lambda7);
  lambda6 = -0.5*s2b*(Lambda1*cb2-Lambda2*sb2-lambda345*c2b)+cb*c3b*Lambda6+sb*s3b*Lambda7;
  lambda7 = -0.5*s2b*(Lambda1*sb2-Lambda2*cb2+lambda345*c2b)+sb*s3b*Lambda6+cb*c3b*Lambda7;

  // **

  targetP.setValue("lambda_1", lambda1 );
  targetP.setValue("lambda_2", lambda2 );
  targetP.setValue("lambda_3", lambda3 );
  targetP.setValue("lambda_4", lambda4 );
  targetP.setValue("lambda_5", lambda5 );
  targetP.setValue("lambda_6", lambda6 );
  targetP.setValue("lambda_7", lambda7 );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

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
