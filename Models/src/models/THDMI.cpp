//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the THDMI
///  model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMI    --> THDM
///  THDMIatQ --> THDMatQ
///
///  THDMI_higgs --> THDMI
///  THDMI_higgsatQ --> THDMIatQ
///
///  THDMI_physical --> THDMI
///  THDMI_physicalatQ --> THDMIatQ
///
///  THDMI_hybrid_lambda1 --> THDMI
///  THDMI_hybrid_lambda1atQ --> THDMIatQ
///
///  THDMI_hybrid_lambda2 --> THDMI
///  THDMI_hybrid_lambda2atQ --> THDMIatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMI    --> THDMIatQ
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
#include "gambit/Models/models/THDMI.hpp"

#include "gambit/Elements/sminputs.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL, PARENT and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI

// THDMI --> THDMIatQ
#define FRIEND THDMIatQ
void MODEL_NAMESPACE::THDMI_to_THDMIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI --> THDMIatQ.."<<LogTags::info<<EOM;

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
    std::cout << "THDMI parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}
#undef FRIEND

// THDMI --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMI_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI --> THDM.."<<LogTags::info<<EOM;

  targetP.setValue("lambda1", myP.getValue("lambda1"));
  targetP.setValue("lambda2", myP.getValue("lambda2"));
  targetP.setValue("lambda3", myP.getValue("lambda3"));
  targetP.setValue("lambda4", myP.getValue("lambda4"));
  targetP.setValue("lambda5", myP.getValue("lambda5"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));

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
    std::cout << "THDM parameters:" << targetP << std::endl;
  #endif
}
#undef PARENT
#undef MODEL

// THDMIatQ --> THDMatQ
#define MODEL  THDMIatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMIatQ_to_THDMatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMIatQ --> THDMatQ.."<<LogTags::info<<EOM;

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

//  THDMI_higgs --> THDMI
#define MODEL  THDMI_higgs
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_higgs_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI_higgs --> THDMI"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  // higgs basis
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = myP.getValue("tanb");
  double beta = atan(tanb);
  double sb = sin(beta), cb = cos(beta), tb = tan(beta);
  double ctb = 1./tb;
  double s2b = sin(2.*beta), c2b = cos(2.*beta);
  double Lambda1 = myP.getValue("Lambda1"), Lambda2 = myP.getValue("Lambda2"), Lambda3 = myP.getValue("Lambda3"), Lambda4 = myP.getValue("Lambda4"), Lambda5 = myP.getValue("Lambda5");
  double Lambda6 = myP.getValue("Lambda6"), Lambda7 = myP.getValue("Lambda7"), M12_2 = myP.getValue("M12_2");
  double Lam345 = Lambda3 + Lambda4 + Lambda5;
  double M11_2 = M12_2*tb - 0.5*v2 * (Lambda1*cb*cb + Lam345*sb*sb + 3.0*Lambda6*sb*cb + Lambda7*sb*sb*tb);
  double M22_2 = M12_2*ctb - 0.5*v2 * (Lambda2*sb*sb + Lam345*cb*cb + Lambda6*cb*cb*ctb + 3.0*Lambda7*sb*cb);

  // generic basis
  double m12_2 = (M11_2-M22_2)*s2b + M12_2*c2b;
  double lambda1 = Lambda1*pow(cb,4) + Lambda2*pow(sb,4) + 0.5*Lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*Lambda6+pow(sb,2)*Lambda7);
  double lambda2 = Lambda1*pow(sb,4) + Lambda2*pow(cb,4) + 0.5*Lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*Lambda6+pow(cb,2)*Lambda7);
  double lambda3 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda3 - s2b*c2b*(Lambda6-Lambda7);
  double lambda4 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda4 - s2b*c2b*(Lambda6-Lambda7);
  double lambda5 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda5 - s2b*c2b*(Lambda6-Lambda7);
  double lambda6 = -0.5*s2b*(Lambda1*pow(cb,2)-Lambda2*pow(sb,2)-Lam345*c2b) + cb*cos(3.*beta)*Lambda6 + sb*sin(3.*beta)*Lambda7;
  double lambda7 = -0.5*s2b*(Lambda1*pow(sb,2)-Lambda2*pow(cb,2)+Lam345*c2b) + sb*sin(3.*beta)*Lambda6 + cb*cos(3.*beta)*Lambda7;

  targetP.setValue("lambda1",lambda1);
  targetP.setValue("lambda2",lambda2);
  targetP.setValue("lambda3",lambda3);
  targetP.setValue("lambda4",lambda4);
  targetP.setValue("lambda5",lambda5);
  targetP.setValue("lambda6",lambda6);
  targetP.setValue("lambda7",lambda7);
  targetP.setValue("m12_2", m12_2);
  targetP.setValue("tanb", myP.getValue("tanb"));

}
#undef PARENT
#undef MODEL

//  THDMI_higgsatQ --> THDMIatQ
#define MODEL  THDMI_higgsatQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_higgsatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMI_higgsatQ --> THDMIatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  // higgs basis
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = myP.getValue("tanb");
  double beta = atan(tanb);
  double sb = sin(beta), cb = cos(beta), tb = tan(beta);
  double ctb = 1./tb;
  double s2b = sin(2.*beta), c2b = cos(2.*beta);
  double Lambda1 = myP.getValue("Lambda1"), Lambda2 = myP.getValue("Lambda2"), Lambda3 = myP.getValue("Lambda3"), Lambda4 = myP.getValue("Lambda4"), Lambda5 = myP.getValue("Lambda5");
  double Lambda6 = myP.getValue("Lambda6"), Lambda7 = myP.getValue("Lambda7"), M12_2 = myP.getValue("M12_2");
  double Lam345 = Lambda3 + Lambda4 + Lambda5;
  double M11_2 = M12_2*tb - 0.5*v2 * (Lambda1*cb*cb + Lam345*sb*sb + 3.0*Lambda6*sb*cb + Lambda7*sb*sb*tb);
  double M22_2 = M12_2*ctb - 0.5*v2 * (Lambda2*sb*sb + Lam345*cb*cb + Lambda6*cb*cb*ctb + 3.0*Lambda7*sb*cb);

  // generic basis
  double m12_2 = (M11_2-M22_2)*s2b + M12_2*c2b;
  double lambda1 = Lambda1*pow(cb,4) + Lambda2*pow(sb,4) + 0.5*Lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*Lambda6+pow(sb,2)*Lambda7);
  double lambda2 = Lambda1*pow(sb,4) + Lambda2*pow(cb,4) + 0.5*Lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*Lambda6+pow(cb,2)*Lambda7);
  double lambda3 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda3 - s2b*c2b*(Lambda6-Lambda7);
  double lambda4 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda4 - s2b*c2b*(Lambda6-Lambda7);
  double lambda5 = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda5 - s2b*c2b*(Lambda6-Lambda7);
  double lambda6 = -0.5*s2b*(Lambda1*pow(cb,2)-Lambda2*pow(sb,2)-Lam345*c2b) + cb*cos(3.*beta)*Lambda6 + sb*sin(3.*beta)*Lambda7;
  double lambda7 = -0.5*s2b*(Lambda1*pow(sb,2)-Lambda2*pow(cb,2)+Lam345*c2b) + sb*sin(3.*beta)*Lambda6 + cb*cos(3.*beta)*Lambda7;

  targetP.setValue("lambda1",lambda1);
  targetP.setValue("lambda2",lambda2);
  targetP.setValue("lambda3",lambda3);
  targetP.setValue("lambda4",lambda4);
  targetP.setValue("lambda5",lambda5);
  targetP.setValue("lambda6",lambda6);
  targetP.setValue("lambda7",lambda7);
  targetP.setValue("m12_2", m12_2);
  targetP.setValue("tanb", myP.getValue("tanb"));
  targetP.setValue("Qin", myP.getValue("Qin") );

}
#undef PARENT
#undef MODEL

//  THDMI_physical --> THDMI
#define MODEL THDMI_physical
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_physical_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMI_physical --> THDMI"<<LogTags::info<<EOM;

  const SMInputs &sminputs = *Dep::SMINPUTS;

  //generic basis
  double mh =  myP.getValue("m_h"), mH =  myP.getValue("m_H"), mA =  myP.getValue("m_A"), mHp =  myP.getValue("m_Hp");
  double mh2 = mh*mh, mH2 = mH*mH, mA2 = mA*mA, mC2 = mHp*mHp;
  double tb  = myP.getValue("tanb");
  double beta = atan(tb);
  double alpha = beta - asin(myP.getValue("sba"));
  double ca = cos(alpha), sa = sin(alpha);
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double ctb  = 1./tb;
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

}
#undef PARENT
#undef MODEL

//  THDMI_physicalatQ --> THDMIatQ
#define MODEL THDMI_physicalatQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_physicalatQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMI_physicalatQ --> THDMIatQ"<<LogTags::info<<EOM;

  const SMInputs &sminputs = *Dep::SMINPUTS;

  //generic basis
  double mh =  myP.getValue("mh"), mH =  myP.getValue("mH"), mA =  myP.getValue("mA"), mHp =  myP.getValue("mHp");
  double mh2 = mh*mh, mH2 = mH*mH, mA2 = mA*mA, mC2 = mHp*mHp;
  double tb  = myP.getValue("tanb");
  double beta = atan(tb);
  double alpha = beta - asin(myP.getValue("sba"));
  double ca = cos(alpha), sa = sin(alpha);
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double ctb  = 1./tb;
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
  targetP.setValue("Qin", myP.getValue("Qin"));

}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_lambda1 --> THDMI
#define MODEL  THDMI_hybrid_lambda1
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_hybrid_lambda1_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_lambda1 --> THDMI"<<LogTags::info<<EOM;

  const SMInputs &sminputs = *Dep::SMINPUTS;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda2 = myP.getValue("lambda2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = sminputs.GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda1", lambda1 );
  targetP.setValue("lambda2", lambda2 );
  targetP.setValue("lambda3", myP.getValue("lambda3") );
  targetP.setValue("lambda4", myP.getValue("lambda4") );
  targetP.setValue("lambda5", myP.getValue("lambda5") );
  targetP.setValue("lambda6", myP.getValue("lambda6") );
  targetP.setValue("lambda7", myP.getValue("lambda7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_lambda1atQ --> THDMIatQ
#define MODEL  THDMI_hybrid_lambda1atQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_hybrid_lambda1atQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_lambda1atQ --> THDMIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda2 = myP.getValue("lambda2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda1", lambda1 );
  targetP.setValue("lambda2", lambda2 );
  targetP.setValue("lambda3", myP.getValue("lambda3") );
  targetP.setValue("lambda4", myP.getValue("lambda4") );
  targetP.setValue("lambda5", myP.getValue("lambda5") );
  targetP.setValue("lambda6", myP.getValue("lambda6") );
  targetP.setValue("lambda7", myP.getValue("lambda7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  targetP.setValue("Qin", myP.getValue("Qin"));

}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_lambda2 --> THDMI
#define MODEL  THDMI_hybrid_lambda2
#define PARENT THDMI
void MODEL_NAMESPACE::THDMI_hybrid_lambda2_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_lambda2 --> THDMI"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda1 = myP.getValue("lambda1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda1", lambda1 );
  targetP.setValue("lambda2", lambda2 );
  targetP.setValue("lambda3", myP.getValue("lambda3") );
  targetP.setValue("lambda4", myP.getValue("lambda4") );
  targetP.setValue("lambda5", myP.getValue("lambda5") );
  targetP.setValue("lambda6", myP.getValue("lambda6") );
  targetP.setValue("lambda7", myP.getValue("lambda7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

}
#undef PARENT
#undef MODEL

//  THDMI_hybrid_lambda2atQ --> THDMIatQ
#define MODEL  THDMI_hybrid_lambda2atQ
#define PARENT THDMIatQ
void MODEL_NAMESPACE::THDMI_hybrid_lambda2atQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT function
  logger()<<"Running interpret_as_PARENT calculations for THDMI_hybrid_lambda2atQ --> THDMIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda1 = myP.getValue("lambda1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda1", lambda1 );
  targetP.setValue("lambda2", lambda2 );
  targetP.setValue("lambda3", myP.getValue("lambda3") );
  targetP.setValue("lambda4", myP.getValue("lambda4") );
  targetP.setValue("lambda5", myP.getValue("lambda5") );
  targetP.setValue("lambda6", myP.getValue("lambda6") );
  targetP.setValue("lambda7", myP.getValue("lambda7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  targetP.setValue("Qin", myP.getValue("Qin"));

}
#undef PARENT
#undef MODEL
