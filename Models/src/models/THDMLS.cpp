//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDMLS model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDMLS    --> THDM
///  THDMLSatQ --> THDMatQ
///
///  THDMLS_higgs --> THDMLS
///  THDMLS_higgsatQ --> THDMLSatQ
///
///  THDMLS_physical --> THDMLS
///  THDMLS_physicalatQ --> THDMLSatQ
///
///  THDMLS_hybrid_lambda1 --> THDMLS
///  THDMLS_hybrid_lambda1atQ --> THDMLSatQ
///
///  THDMLS_hybrid_lambda2 --> THDMLS
///  THDMLS_hybrid_lambda2atQ --> THDMLSatQ
///
///  as well as the interpret-as-friend translation
///  functions for
///
///  THDMLS    --> THDMLSatQ
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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019
///  \date 2020 Jun
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  \date 2021 Mar
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDMLS.hpp"

#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

#define MODEL  THDMLS

// THDMLS --> THDMLSatQ
#define FRIEND THDMLSatQ
void MODEL_NAMESPACE::THDMLS_to_THDMLSatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS --> THDMLSatQ.."<<LogTags::info<<EOM;

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

}

#undef FRIEND

// THDMLS --> THDM
#define PARENT THDM
void MODEL_NAMESPACE::THDMLS_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS --> THDM.."<<LogTags::info<<EOM;

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
                                          "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_im_33",
                                          "yl2_re_11", "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_re_22", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_re_33", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
  targetP.setValue("yd2_re_11", sqrt(2)/v/sb * sminputs.mD);
  targetP.setValue("yd2_re_22", sqrt(2)/v/sb * sminputs.mS);
  targetP.setValue("yd2_re_33", sqrt(2)/v/sb * sminputs.mBmB);

}
#undef PARENT
#undef MODEL

// THDMLSatQ --> THDMatQ
#define MODEL THDMLSatQ
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDMLSatQ_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLSatQ --> THDMatQ.."<<LogTags::info<<EOM;

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
                                          "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_im_33",
                                          "yl2_re_11", "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_re_22", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_re_33", "yl2_im_33"};

  for (auto &yukawa_key : yukawa_keys) // access by reference to avoid copying
  {  
      targetP.setValue(yukawa_key, 0.0);
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
  targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
  targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
  targetP.setValue("yd2_re_11", sqrt(2)/v/sb * sminputs.mD);
  targetP.setValue("yd2_re_22", sqrt(2)/v/sb * sminputs.mS);
  targetP.setValue("yd2_re_33", sqrt(2)/v/sb * sminputs.mBmB);

}
#undef PARENT
#undef MODEL

//  THDMLS_higgs --> THDMLS
#define MODEL  THDMLS_higgs
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_higgs_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS_higgs --> THDMLS"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  // higgs basis
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = double tanb"];
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

//  THDMLS_higgsatQ --> THDMLSatQ
#define MODEL  THDMLS_higgsatQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_higgsatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDMLS_higgsatQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;

  // higgs basis
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  double tanb  = double tanb"];
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

//  THDMLS_physical --> THDMI
#define MODEL THDMLS_physical
#define PARENT THDMLS
void MODEL_NAMESPACE::TDHMI_physical_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMLS_physical ->> THDMLS"<<LogTags::info<<EOM;

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

//  THDMLS_physicalatQ --> THDMLSatQ
#define MODEL THDMLS_physicalatQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::TDHMI_physicalatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pope for "interpret as PARENT" function
  logger()<<"Running interpre_as_parent calculations for THDMLS_physicalatQ ->> THDMLSatQ"<<LogTags::info<<EOM;

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

//  THDMLS_hybrid_lambda1 --> THDMI
#define MODEL  THDMLS_hybrid_lambda1
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_hybrid_lambda1_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMLS_hybrid_lambda1 --> THDMLS"<<LogTags::info<<EOM;

  const SMInputs &sminputs = *Dep::SMINPUTS;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = sminputs.GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

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

//  THDMLS_hybrid_lambda1atQ --> THDMLSatQ
#define MODEL  THDMLS_hybrid_lambda1atQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_hybrid_lambda1atQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_PARENT calculations for THDMLS_hybrid_lambda1atQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

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

//  THDMLS_hybrid_lambda2 --> THDMI
#define MODEL  THDMLS_hybrid_lambda2
#define PARENT THDMLS
void MODEL_NAMESPACE::THDMLS_hybrid_lambda2_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT function
  logger()<<"Running interpret_as_PARENT calculations for THDMLS_hybrid_lambda2 --> THDMLS"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

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

//  THDMLS_hybrid_lambda2atQ --> THDMLSatQ
#define MODEL  THDMLS_hybrid_lambda2atQ
#define PARENT THDMLSatQ
void MODEL_NAMESPACE::THDMLS_hybrid_lambda2atQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT function
  logger()<<"Running interpret_as_PARENT calculations for THDMLS_hybrid_lambda2atQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

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
