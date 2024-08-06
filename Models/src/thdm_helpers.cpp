//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///
///  *********************************************

#include <string>
#include <vector>
#include <array>

#include "gambit/Models/thdm_helpers.hpp"
#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Elements/sminputs.hpp"

using namespace Gambit::Utils;

namespace Gambit
{

void add_Yukawas(const int type, const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  std::vector<std::string> yukawa_keys = {"yu2_re_11", "yu2_im_11", "yu2_re_12", "yu2_im_12", "yu2_re_13", "yu2_im_13",
                                          "yu2_re_21", "yu2_im_21", "yu2_re_22", "yu2_im_22", "yu2_re_23", "yu2_im_23",
                                          "yu2_re_31", "yu2_im_31", "yu2_re_32", "yu2_im_32", "yu2_re_33", "yu2_im_33",
                                          "yd2_re_11", "yd2_im_11", "yd2_re_12", "yd2_im_12", "yd2_re_13", "yd2_im_13",
                                          "yd2_re_21", "yd2_im_21", "yd2_re_22", "yd2_im_22", "yd2_re_23", "yd2_im_23",
                                          "yd2_re_31", "yd2_im_31", "yd2_re_32", "yd2_im_32", "yd2_re_33", "yd2_im_33",
                                          "yl2_re_11", "yl2_im_11", "yl2_re_12", "yl2_im_12", "yl2_re_13", "yl2_im_13",
                                          "yl2_re_21", "yl2_im_21", "yl2_re_22", "yl2_im_22", "yl2_re_23", "yl2_im_23",
                                          "yl2_re_31", "yl2_im_31", "yl2_re_32", "yl2_im_32", "yl2_re_33", "yl2_im_33"};
  if (type == 0)
  {
    for (auto &yukawa_key : yukawa_keys)
    {
        targetP.setValue(yukawa_key, myP.getValue(yukawa_key));
    }
  }
  else
  {
    for (auto &yukawa_key : yukawa_keys)
    {
        targetP.setValue(yukawa_key, 0.0);
    }
  }

  double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
  double sb = myP.getValue("tanb")/sqrt(1+pow(myP.getValue("tanb"),2));

  if (type == 1)
  {
    targetP.setValue("yu2_re_11", sqrt(2)/v/sb*sminputs.mU);
    targetP.setValue("yu2_re_22", sqrt(2)/v/sb*sminputs.mCmC);
    targetP.setValue("yu2_re_33", sqrt(2)/v/sb*sminputs.mT);
    targetP.setValue("yd2_re_11", sqrt(2)/v/sb*sminputs.mD);
    targetP.setValue("yd2_re_22", sqrt(2)/v/sb*sminputs.mS);
    targetP.setValue("yd2_re_33", sqrt(2)/v/sb*sminputs.mBmB);
    targetP.setValue("yl2_re_11", sqrt(2)/v/sb*sminputs.mE);
    targetP.setValue("yl2_re_22", sqrt(2)/v/sb*sminputs.mMu);
    targetP.setValue("yl2_re_33", sqrt(2)/v/sb*sminputs.mTau);
  }

  if (type == 2)
  {
    targetP.setValue("yu2_re_11", sqrt(2)/v/sb*sminputs.mU);
    targetP.setValue("yu2_re_22", sqrt(2)/v/sb*sminputs.mCmC);
    targetP.setValue("yu2_re_33", sqrt(2)/v/sb*sminputs.mT);
  }

  if (type == 3)
  {
    targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
    targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
    targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
    targetP.setValue("yd2_re_11", sqrt(2)/v/sb * sminputs.mD);
    targetP.setValue("yd2_re_22", sqrt(2)/v/sb * sminputs.mS);
    targetP.setValue("yd2_re_33", sqrt(2)/v/sb * sminputs.mBmB);
  }

  if (type == 4)
  {
    targetP.setValue("yu2_re_11", sqrt(2)/v/sb * sminputs.mU);
    targetP.setValue("yu2_re_22", sqrt(2)/v/sb * sminputs.mCmC);
    targetP.setValue("yu2_re_33", sqrt(2)/v/sb * sminputs.mT);
    targetP.setValue("yl2_re_11", sqrt(2)/v/sb * sminputs.mE);
    targetP.setValue("yl2_re_22", sqrt(2)/v/sb * sminputs.mMu);
    targetP.setValue("yl2_re_33", sqrt(2)/v/sb * sminputs.mTau);
  }
}

void generic_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  targetP.setValue("lambda1", myP.getValue("lambda1"));
  targetP.setValue("lambda2", myP.getValue("lambda2"));
  targetP.setValue("lambda3", myP.getValue("lambda3"));
  targetP.setValue("lambda4", myP.getValue("lambda4"));
  targetP.setValue("lambda5", myP.getValue("lambda5"));
  targetP.setValue("lambda6", myP.getValue("lambda6"));
  targetP.setValue("lambda7", myP.getValue("lambda7"));
  targetP.setValue("m12_2", myP.getValue("m12_2"));
  targetP.setValue("tanb", myP.getValue("tanb"));
}

std::array<double,6> physical_to_generic_helper(double mh2, double mH2, double mA2, double mC2, double m122, 
                                                double tb, double alpha, double v2, double lam6, double lam7)
{
  double ctb  = 1./tb;
  double beta = atan(tb);

  double cb = cos(beta), sb = sin(beta);
  double ca = cos(alpha), sa = sin(alpha);
  double ca2 = sqr(ca), sa2 = sqr(sa), cb2 = sqr(cb), sb2 = sqr(sb);

  // https://arxiv.org/pdf/hep-ph/0207010 page 40
  std::array<double,6> lambda;
  lambda[1] = (mH2*ca2 + mh2*sa2 - m122*tb)/v2/cb2 - 1.5*lam6*tb + 0.5*lam7*pow(tb,3);
  lambda[2] = (mH2*sa2 + mh2*ca2 - m122*ctb)/v2/sb2 + 0.5*lam6*pow(ctb,3) - 1.5*lam7*ctb;
  lambda[3] = ((mH2 - mh2)*ca*sa + 2.*mC2*sb*cb - m122)/v2/sb/cb - 0.5*lam6*ctb - 0.5*lam7*tb;
  lambda[4] = ((mA2 - 2.*mC2)*cb*sb + m122)/v2/sb/cb - 0.5*lam6*ctb - 0.5*lam7*tb;
  lambda[5] = (m122 - mA2*sb*cb)/v2/sb/cb - 0.5*lam6*ctb - 0.5*lam7*tb;
  return lambda;
}

void physical_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  // get parameters
  double mh  =  myP.getValue("mh");
  double mH  =  myP.getValue("mH");
  double mA  =  myP.getValue("mA");
  double mHp =  myP.getValue("mHp");
  double tb  = myP.getValue("tanb");
  double m122 = myP.getValue("m12_2");
  double lam6 = myP.getValue("lambda6");
  double lam7 = myP.getValue("lambda7");

  // calcs
  double mh2 = mh*mh, mH2 = mH*mH, mA2 = mA*mA, mC2 = mHp*mHp;
  double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
  
  // conventions for alpha
  double alpha = atan(tb) - asin(myP.getValue("sba"));

  auto lambda = physical_to_generic_helper(mh2, mH2, mA2, mC2, m122, tb, alpha, v2, lam6, lam7);

  // set parameters
  targetP.setValue("lambda1",lambda[1]);
  targetP.setValue("lambda2",lambda[2]);
  targetP.setValue("lambda3",lambda[3]);
  targetP.setValue("lambda4",lambda[4]);
  targetP.setValue("lambda5",lambda[5]);
  targetP.setValue("lambda6",lam6);
  targetP.setValue("lambda7",lam7);
  targetP.setValue("m12_2", m122);
  targetP.setValue("tanb", tb);
}

// Reference
// ...

void higgs_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
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

void hybrid_lam1_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
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

void hybrid_lam2_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  const double m_h = myP.getValue("mh"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda1 = myP.getValue("lambda1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = sminputs.GF;
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

void hybrid_higgs_to_generic(bool tree, const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  // extract params
  double mh2 = sqr(myP.getValue("mh"));
  double mH2 = sqr(myP.getValue("mH"));
  double cba = myP.getValue("cba");
  double tanb = myP.getValue("tanb");
  double L4 = myP.getValue("Lambda4");
  double L5 = myP.getValue("Lambda5");
  double L7 = myP.getValue("Lambda7");
  double lambda6 = myP.getValue("lambda6");
  double lambda7 = myP.getValue("lambda7");
  double v2 = 1. / (sqrt(2) * sminputs.GF);

  // Note: maximum absolute values of Lam1, Lam6 set by theory constraints
  // (the more conservative perturbativity limit is 4*pi)
  
  double Lam6_max = 0.8;
  double Lam1_max = 0.6;
  if (tree)
  {
    Lam6_max = 6.0;
    Lam1_max = 4.0;
  }

  // --- alternative A (rescale cosba)

  const double delta = 1.0;
  if (mH2 > Lam1_max*v2 + delta)
  {
    // maximum possible value of |cos(b-a)|
    // https://arxiv.org/pdf/1507.04281 page 8
    // N.B. mh2 <= Z1.v2 <= mH2
    double cosba_max = std::min(1.0, Lam6_max*v2/sqrt((mH2-mh2)*(mH2-Lam1_max*v2)));
    // rescale cosba so that we dont waste time with non-perturbative values
    cba *= cosba_max;
  }

  // --- alternative B (rescale mH2)

  // const double mH_lim = 1e5; // from yaml file
  // double mH_max = sqrt((Lam1_max*v2+mh2)/sqr(cba));
  
  // if (mH_max < mH_lim)
  //   mH2 *= sqr(mH_max / mH_lim);

  // calc angles
  double beta = std::atan(tanb);
  double alpha = beta - std::acos(cba);
  double sba = sin(beta - alpha);

  // calc masses
  // https://arxiv.org/pdf/1507.04281 page 14 (67)
  double mA2 = mH2 * sqr(sba) + mh2 * sqr(cba) - L5 * v2;
  https://arxiv.org/pdf/1507.04281 page 14 (68)
  double mHp2 = mA2 - 0.5 * v2 * (L4 - L5);
  // https://arxiv.org/pdf/1507.04281 page 14 (64)
  double L6 = (mh2 - mH2) * sba * cba / v2;
  // https://arxiv.org/pdf/1507.04281 page 14 (69)
  double m_bar = mH2 * sqr(sba) + mh2 * sqr(cba) + 0.5 * v2 * tan(2 * beta) * (L6 - L7);
  // https://arxiv.org/pdf/1507.04281 page 10 (56)
  double m122 = 0.5 * m_bar * sin(2 * beta);

  auto lambda = physical_to_generic_helper(mh2, mH2, mA2, mHp2, m122, tanb, alpha, v2, lambda6, lambda7);

  // set params
  targetP.setValue("lambda1", lambda[1]);
  targetP.setValue("lambda2", lambda[2]);
  targetP.setValue("lambda3", lambda[3]);
  targetP.setValue("lambda4", lambda[4]);
  targetP.setValue("lambda5", lambda[5]);
  targetP.setValue("lambda6", lambda6);
  targetP.setValue("lambda7", lambda7);
  targetP.setValue("m12_2", m122);
  targetP.setValue("tanb", tanb);
}

void hybrid_higgs2_to_generic(const SMInputs &sminputs, const ModelParameters &myP, ModelParameters &targetP)
{
  // extract params
  double mh2 = sqr(myP.getValue("mh"));
  double mHp2 = sqr(myP.getValue("mHp"));
  double cba = myP.getValue("cba");
  double tanb = myP.getValue("tanb");
  double L4 = myP.getValue("Lambda4");
  double L5 = myP.getValue("Lambda5");
  double L7 = myP.getValue("Lambda7");
  double lambda6 = myP.getValue("lambda6");
  double lambda7 = myP.getValue("lambda7");
  double v2 = 1. / (sqrt(2) * sminputs.GF);

  // calc angles
  double beta = std::atan(tanb);
  double alpha = beta - std::acos(cba);
  double sba = sin(beta - alpha);

  // calc masses

  // WARNING: may come out mH<mh for some points leading to HHS
  // https://arxiv.org/pdf/1507.04281 page 14 (67+68)
  double mH2 = (mHp2+0.5*v2*(L4+L5)-mh2*sqr(cba))/sqr(sba);
  double mA2 = mH2 * sqr(sba) + mh2 * sqr(cba) - L5 * v2; // same
  double L6 = (mh2 - mH2) * sba * cba / v2; // same
  double m_bar = mH2 * sqr(sba) + mh2 * sqr(cba) + 0.5 * v2 * tan(2 * beta) * (L6 - L7); // same
  double m122 = 0.5 * m_bar * sin(2 * beta); // same

  auto lambda = physical_to_generic_helper(mh2, mH2, mA2, mHp2, m122, tanb, alpha, v2, lambda6, lambda7);

  // set params
  targetP.setValue("lambda1", lambda[1]);
  targetP.setValue("lambda2", lambda[2]);
  targetP.setValue("lambda3", lambda[3]);
  targetP.setValue("lambda4", lambda[4]);
  targetP.setValue("lambda5", lambda[5]);
  targetP.setValue("lambda6", lambda6);
  targetP.setValue("lambda7", lambda7);
  targetP.setValue("m12_2", m122);
  targetP.setValue("tanb", tanb);
}

} // namespace Gambit
