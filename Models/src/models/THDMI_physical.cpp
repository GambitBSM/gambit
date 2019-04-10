///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDMI_physical to THDMI
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
#include "gambit/Models/models/THDMI_physical.hpp"
#include "gambit/Models/models/THDMI.hpp"
// #include "gambit/Models/models/THDMIatQ.hpp"
// #include "gambit/Elements/spectrum.hpp"

// #include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI_physical
#define PARENT THDM
#define FRIEND THDMI

// Translation function definition
void MODEL_NAMESPACE::THDMI_physical_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_physical --> THDMI"<<LogTags::info<<EOM;

  double m_h = myP.getValue("m_h");
  double m_H = myP.getValue("m_H");
  double m_A = myP.getValue("m_A");
  double m_Hp = myP.getValue("m_Hp");
  double m12_2 = myP.getValue("m12_2");
  double tanb = myP.getValue("tanb");
  double sba = myP.getValue("sba");

  double lambda6 = myP.getValue("lambda_6");
  double lambda7 = myP.getValue("lambda_7");

  // Problematic parameter choices
  if (m_h>m_H) {
    cerr << "WARNING: Cannot set physical masses such that m_H < m_h\n"; 
    // throw error
  }
  if ((tanb<=0)||(abs(sba)>1)||(m_h<0)||(m_H<0)||(m_A<0)||(m_Hp<0)) {
    cerr << "WARNING: Problematic input parameter choice.\n"; 
    // throw error
  }

  beta=atan(tan_beta);

  double sb	 = sin(beta);
  double sb2 = sb*sb;
  double cb	 = cos(beta);
  double cb2 = cb*cb;
  double tb	 = tan(beta);
  double ctb = 1./tb;

  double alpha = -asin(sba)+beta;
  double sa  = sin(alpha);
  double sa2 = sa*sa;
  double ca  = cos(alpha);
  double ca2 = ca*ca;

  double cba = sqrt(1.-sba*sba);
 
  double lambda1 = (m_H*m_H*ca2+m_h*m_h*sa2-m12_2*tb)/v2/cb2-1.5*lambda6*tb+0.5*lambda7*tb*tb*tb;
  double lambda2 = (m_H*m_H*sa2+m_h*m_h*ca2-m12_2*ctb)/v2/sb2+0.5*lambda6*ctb*ctb*ctb-1.5*lambda7*ctb;
  double lambda3 = ((m_H*m_H-m_h*m_h)*ca*sa+2.*m_Hp*m_Hp*sb*cb-m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
  double lambda4 = ((m_A*m_A-2.*m_Hp*m_Hp)*cb*sb+m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
  double lambda5 = (m12_2-m_A*m_A*sb*cb)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
  // m22_2 = -0.5/sb*(pow(m_h,2)*ca*sba+pow(m_H,2)*sa*cba)+m12_2*ctb;

  // ----

  targetP.setValue("lambda_1", lambda1 );
  targetP.setValue("lambda_2", lambda2 );
  targetP.setValue("lambda_3", lambda3 );
  targetP.setValue("lambda_4", lambda4 );
  targetP.setValue("lambda_5", lambda5 );
  targetP.setValue("lambda_6", lambda6 );
  targetP.setValue("lambda_7", lambda7 );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );


  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_physical parameters:" << myP << std::endl;
    std::cout << "THDMI parameters   :" << targetP << std::endl;
  #endif
}

// Translation function definition
void MODEL_NAMESPACE::THDMI_physical_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI --> THDMIatQ.."<<LogTags::info<<EOM;

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
    std::cout << "THDMI parameters:" << myP << std::endl;
    std::cout << "THDM parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef FRIEND
#undef MODEL