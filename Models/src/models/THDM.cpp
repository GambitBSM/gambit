//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  THDM model and its variations.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  THDM          --> THDMatQ
///  THDM_higgs    --> THDM
///  THDM_physical --> THDM
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
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 Apr
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

#include "gambit/Models/models/THDM.hpp"

#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

// THDM --> THDMatQ
#define MODEL  THDM
#define PARENT THDMatQ
void MODEL_NAMESPACE::THDM_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for THDM --> THDMatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",Dep::SMINPUTS->mZ);

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

}
#undef PARENT
#undef MODEL

// THDM_higgs --> THDM
#define MODEL  THDM_higgs
#define PARENT THDM
void MODEL_NAMESPACE::THDM_higgs_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
    USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
    logger()<<"Running interpret_as_parent calculations for THDM_higgs --> THDM.."<<LogTags::info<<EOM;

    const SMInputs& sminputs = *Dep::SMINPUTS;

    // higgs basis
    double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
    double tb  = myP.getValue("tanb");
    double beta = -atan(tb);//Inverse transformation from higgs to generic basis adds the minus sign
    double cb = cos(beta),sb = sin(beta), c2b = cos(2.*beta),s2b = sin(2.*beta);
    double alpha = myP.getValue("alpha");
    double mC2 = myP.getValue("M22_2")+0.5*v2*myP.getValue("Lambda3");
    double mA2 = mC2-0.5*v2*(myP.getValue("Lambda5")-myP.getValue("Lambda4"));
    double Lambda6 = (tan(2.*(beta-alpha))/(2.*v2))*(mA2+v2*(myP.getValue("Lambda5")-myP.getValue("Lambda1")));
    double Lam345 = myP.getValue("Lambda3")+ myP.getValue("Lambda4") + myP.getValue("Lambda5");
    double M11_2 = -0.5*v2*myP.getValue("Lambda1");
    double M12_2 = 0.5*v2*Lambda6;

    //generic basis
    double lambda1 = myP.getValue("Lambda1")*pow(cb,4) + myP.getValue("Lambda2")*pow(sb,4) + 0.5*Lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*Lambda6+pow(sb,2)*myP.getValue("Lambda7"));
    double lambda2 = myP.getValue("Lambda1")*pow(sb,4) + myP.getValue("Lambda2")*pow(cb,4) + 0.5*Lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*Lambda6+pow(cb,2)*myP.getValue("Lambda7"));
    double lambda3 = 0.25*pow(s2b,2)*(myP.getValue("Lambda1")+myP.getValue("Lambda2")-2.*Lam345) + myP.getValue("Lambda3") - s2b*c2b*(Lambda6-myP.getValue("Lambda7"));
    double lambda4 = 0.25*pow(s2b,2)*(myP.getValue("Lambda1")+myP.getValue("Lambda2")-2.*Lam345) + myP.getValue("Lambda4") - s2b*c2b*(Lambda6-myP.getValue("Lambda7"));
    double lambda5 = 0.25*pow(s2b,2)*(myP.getValue("Lambda1")+myP.getValue("Lambda2")-2.*Lam345) + myP.getValue("Lambda5") - s2b*c2b*(Lambda6-myP.getValue("Lambda7"));
    double lambda6 = -0.5*s2b*(myP.getValue("Lambda1")*pow(cb,2)-myP.getValue("Lambda2")*pow(sb,2)-Lam345*c2b) + cb*cos(3.*beta)*Lambda6 + sb*sin(3.*beta)*myP.getValue("Lambda7");
    double lambda7 = -0.5*s2b*(myP.getValue("Lambda1")*pow(sb,2)-myP.getValue("Lambda2")*pow(cb,2)+Lam345*c2b) + sb*sin(3.*beta)*Lambda6 + cb*cos(3.*beta)*myP.getValue("Lambda7");
    double m12_2 = 0.5*(M11_2-myP.getValue("M22_2"))*s2b + M12_2*c2b;

    targetP.setValue("lambda1",lambda1);
    targetP.setValue("lambda2",lambda2);
    targetP.setValue("lambda3",lambda3);
    targetP.setValue("lambda4",lambda4);
    targetP.setValue("lambda5",lambda5);
    targetP.setValue("lambda6",lambda6);
    targetP.setValue("lambda7",lambda7);
    targetP.setValue("m12_2", m12_2);
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
    targetP.setValue(yukawa_key, myP.getValue(yukawa_key));
  }


}
#undef PARENT
#undef MODEL

// THDM_physical --> THDM
#define MODEL  THDM_physical
#define PARENT THDM
void MODEL_NAMESPACE::THDM_physical_to_THDM (const ModelParameters &myP, ModelParameters &targetP)
{
    USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
    logger()<<"Running interpret_as_parent calculations for THDM_physical --> THDM.."<<LogTags::info<<EOM;

    const SMInputs& sminputs = *Dep::SMINPUTS;

    //generic basis
    double mh2 =  myP.getValue("mh2"), mH2 =  myP.getValue("mH2"), mA2 =  myP.getValue("mA2"), mC2 =  myP.getValue("mC2");
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


}
#undef PARENT
#undef MODEL
