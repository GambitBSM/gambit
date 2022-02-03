///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///  \file
///
///  THDMhybridX_higgsX 
///  -> 
///  THDMX 
///  (translation functions)
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
/// \author A.S. Woodcock
///         (alex.woodcock@outlook.com)
/// \date   Feb 2022
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

#include "gambit/Models/models/THDMI_hybrid_lambda1.hpp"
#include "gambit/Models/models/THDMI_hybrid_lambda2.hpp"
#include "gambit/Models/models/THDMI_hybrid_lambda1atQ.hpp"
#include "gambit/Models/models/THDMI_hybrid_lambda2atQ.hpp"

#include "gambit/Models/models/THDMII_hybrid_lambda1.hpp"
#include "gambit/Models/models/THDMII_hybrid_lambda2.hpp"
#include "gambit/Models/models/THDMII_hybrid_lambda1atQ.hpp"
#include "gambit/Models/models/THDMII_hybrid_lambda2atQ.hpp"

#include "gambit/Models/models/THDMLS_hybrid_lambda1.hpp"
#include "gambit/Models/models/THDMLS_hybrid_lambda2.hpp"
#include "gambit/Models/models/THDMLS_hybrid_lambda1atQ.hpp"
#include "gambit/Models/models/THDMLS_hybrid_lambda2atQ.hpp"

#include "gambit/Models/models/THDMflipped_hybrid_lambda1.hpp"
#include "gambit/Models/models/THDMflipped_hybrid_lambda2.hpp"
#include "gambit/Models/models/THDMflipped_hybrid_lambda1atQ.hpp"
#include "gambit/Models/models/THDMflipped_hybrid_lambda2atQ.hpp"

#include "gambit/Models/models/THDMI_smartBasis.hpp"
#include "gambit/Models/models/THDMIatQ_smartBasis.hpp"

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

// -- smart basis translations --

inline double sq(double v)
{
  return v*v;
}

inline double cube(double v)
{
  return v*v*v;
}

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI_smartBasis
#define FRIEND THDMI

// Translation function definition
void MODEL_NAMESPACE::THDMI_smartBasis_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_smartBasis --> THDMI"<<LogTags::info<<EOM;

  // - calculate cosba

  // the distorted cosba
  double x = myP.getValue("cosba_distorted");
  // // spline input points
  // static const std::vector<double> xj = { -1.0, -0.66, -0.33, 0.0, 0.33, 0.66, 1.0 };
  // // spline output points
  // static const std::vector<double> fj = { -1.0, -0.1, -0.01, 0.0, 0.01, 0.1, 1.0 };
  // // splie coeffs
  // static const std::vector<double> cj = { 0, -4.5657, 2.4648, -2.7352, 0, 2.7352, -2.4648 };
  // // calc cubic spline
  // double cosba = cj[0] + cj[1]*x;
  // for (size_t i = 2; i<cj.size(); ++i) cosba += cube(abs(x - xj[i-1])) * cj[i];
  // cosba = std::min(1.0,cosba);
  // cosba = std::max(-1.0,cosba);

  double cosba = x; // !!!!!!!

  // - calculate m122

  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);
  double lam1 = myP.getValue("lambda_1");
  double lam2 = myP.getValue("lambda_2");
  double lam3 = myP.getValue("lambda_3");
  double lam4 = myP.getValue("lambda_4");
  double lam5 = myP.getValue("lambda_5");
  double lam6 = myP.getValue("lambda_6");
  double lam7 = myP.getValue("lambda_7");
  double tanb = myP.getValue("tanb");

  double beta = atan(tanb);
  double alpha = beta - acos(cosba);
  double cosb2 = sq(cos(beta));
  double sinb2 = sq(sin(beta));
  double sin2b = sin(2*beta);
  double cot2b = 1.0/tan(2*beta);
  double tan2a = tan(2*alpha);

  double m12_2 = v2 * ( (lam1*cosb2 - lam2*sinb2)*tan2a - (lam3+lam4+lam5)*sin2b ) / (2*tan2a*cot2b - 2);

  // std::cout << "m12_2: " << m12_2 << std::endl;
  // std::cout << "cosba: " << cosba << std::endl;
  // std::cout << "cosba_d: " << x << std::endl;


  // - set generic basis

  targetP.setValue("lambda_1", lam1 );
  targetP.setValue("lambda_2", lam2 );
  targetP.setValue("lambda_3", lam3 );
  targetP.setValue("lambda_4", lam4 );
  targetP.setValue("lambda_5", lam5 );
  targetP.setValue("lambda_6", lam6 );
  targetP.setValue("lambda_7", lam7 );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_smartBasis parameters:" << myP << std::endl;
    std::cout << "THDMI parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL

#define MODEL  THDMIatQ_smartBasis
#define FRIEND THDMIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMIatQ_smartBasis_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMIatQ_smartBasis --> THDMIatQ"<<LogTags::info<<EOM;

    // - calculate cosba

  // the distorted cosba
  double x = myP.getValue("cosba_distorted");
  // spline input points
  static const std::vector<double> xj = { -1.0, -0.66, -0.33, 0.0, 0.33, 0.66, 1.0 };
  // spline output points
  static const std::vector<double> fj = { -1.0, -0.1, -0.01, 0.0, 0.01, 0.1, 1.0 };
  // splie coeffs
  static const std::vector<double> cj = { 0, -4.5657, 2.4648, -2.7352, 0, 2.7352, -2.4648 };
  // calc cubic spline
  double cosba = cj[0] + cj[1]*x;
  for (size_t i = 2; i<cj.size(); ++i) cosba += cube(abs(x - xj[i-1])) * cj[i];
  cosba = std::min(1.0,cosba);
  cosba = std::max(-1.0,cosba);

  // - calculate m122

  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);
  double lam1 = myP.getValue("lambda_1");
  double lam2 = myP.getValue("lambda_2");
  double lam3 = myP.getValue("lambda_3");
  double lam4 = myP.getValue("lambda_4");
  double lam5 = myP.getValue("lambda_5");
  double lam6 = myP.getValue("lambda_6");
  double lam7 = myP.getValue("lambda_7");
  double tanb = myP.getValue("tanb");

  double beta = atan(tanb);
  double alpha = beta - acos(cosba);
  double cosb2 = sq(cos(beta));
  double sinb2 = sq(sin(beta));
  double sin2b = sin(2*beta);
  double cot2b = 1.0/tan(2*beta);
  double tan2a = tan(2*alpha);

  double m12_2 = v2 * ( (lam1*cosb2 - lam2*sinb2)*tan2a - (lam3+lam4+lam5)*sin2b ) / (2*tan2a*cot2b - 2);

  // - set generic basis

  targetP.setValue("lambda_1", lam1 );
  targetP.setValue("lambda_2", lam2 );
  targetP.setValue("lambda_3", lam3 );
  targetP.setValue("lambda_4", lam4 );
  targetP.setValue("lambda_5", lam5 );
  targetP.setValue("lambda_6", lam6 );
  targetP.setValue("lambda_7", lam7 );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );


  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMIatQ_smartBasis parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMI_hybrid_lambda1
#define FRIEND THDMI

// Translation function definition
void MODEL_NAMESPACE::THDMI_hybrid_lambda1_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_hybrid_lambda1 --> THDMI"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_hybrid_lambda1 parameters:" << myP << std::endl;
    std::cout << "THDMI parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL

#define MODEL  THDMI_hybrid_lambda1atQ
#define FRIEND THDMIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMI_hybrid_lambda1atQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_hybrid_lambda1atQ --> THDMIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_hybrid_lambda1atQ parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL

#define MODEL  THDMI_hybrid_lambda2
#define FRIEND THDMI

// Translation function definition
void MODEL_NAMESPACE::THDMI_hybrid_lambda2_to_THDMI(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_hybrid_lambda2 --> THDMI"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_hybrid_lambda2 parameters:" << myP << std::endl;
    std::cout << "THDMI parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMI_hybrid_lambda2atQ
#define FRIEND THDMIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMI_hybrid_lambda2atQ_to_THDMIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMI_hybrid_lambda2atQ --> THDMIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMI_hybrid_lambda2atQ parameters:" << myP << std::endl;
    std::cout << "THDMIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


// #define MODEL  THDMflipped_hybrid_lambda2atQ
// #define FRIEND THDMflippedatQ

// // Translation function definition
// void MODEL_NAMESPACE::THDMflipped_hybrid_lambda2atQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
// {
//   USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
//   logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_hybrid_lambda2atQ --> THDMflippedatQ"<<LogTags::info<<EOM;

//   const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
//       m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

//   const double beta = atan(tanb);
//   double ba = asin(sba);
//   const double alpha = beta - ba;
//   const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
//   const double GF = Dep::SMINPUTS->GF;
//   const double v2 = 1./(sqrt(2)*GF);

//   const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
//       ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

//   targetP.setValue("lambda_1", lambda_1 );
//   targetP.setValue("lambda_2", lambda_2 );
//   targetP.setValue("lambda_3", myP.getValue("lambda_3") );
//   targetP.setValue("lambda_4", myP.getValue("lambda_4") );
//   targetP.setValue("lambda_5", myP.getValue("lambda_5") );
//   targetP.setValue("lambda_6", myP.getValue("lambda_6") );
//   targetP.setValue("lambda_7", myP.getValue("lambda_7") );
//   targetP.setValue("m12_2", m12_2 );
//   targetP.setValue("tanb", tanb );

//   targetP.setValue("Qin", myP.getValue("Qin") );
//   targetP.setValue("QrunTo", myP.getValue("QrunTo") );

//   // Done! Check that everything is ok if desired.
//   #ifdef THDM_DBUG
//     std::cout << "THDMflipped_hybrid_lambda2atQ parameters:" << myP << std::endl;
//     std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
//   #endif
// }

// #undef FRIEND
// #undef MODEL


#define MODEL  THDMII_hybrid_lambda1
#define FRIEND THDMII

// Translation function definition
void MODEL_NAMESPACE::THDMII_hybrid_lambda1_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_hybrid_lambda1 --> THDMII"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_hybrid_lambda1 parameters:" << myP << std::endl;
    std::cout << "THDMII parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMII_hybrid_lambda1atQ
#define FRIEND THDMIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMII_hybrid_lambda1atQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_hybrid_lambda1atQ --> THDMIIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_hybrid_lambda1atQ parameters:" << myP << std::endl;
    std::cout << "THDMIIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMII_hybrid_lambda2
#define FRIEND THDMII

// Translation function definition
void MODEL_NAMESPACE::THDMII_hybrid_lambda2_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_hybrid_lambda2 --> THDMII"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_hybrid_lambda2 parameters:" << myP << std::endl;
    std::cout << "THDMII parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMII_hybrid_lambda2atQ
#define FRIEND THDMIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDMII_hybrid_lambda2atQ_to_THDMIIatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_hybrid_lambda2atQ --> THDMIIatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_hybrid_lambda2atQ parameters:" << myP << std::endl;
    std::cout << "THDMIIatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_hybrid_lambda1
#define FRIEND THDMLS

// Translation function definition
void MODEL_NAMESPACE::THDMLS_hybrid_lambda1_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_hybrid_lambda1 --> THDMLS"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_hybrid_lambda1 parameters:" << myP << std::endl;
    std::cout << "THDMLS parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_hybrid_lambda1atQ
#define FRIEND THDMLSatQ

// Translation function definition
void MODEL_NAMESPACE::THDMLS_hybrid_lambda1atQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_hybrid_lambda1atQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_hybrid_lambda1atQ parameters:" << myP << std::endl;
    std::cout << "THDMLSatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_hybrid_lambda2
#define FRIEND THDMLS

// Translation function definition
void MODEL_NAMESPACE::THDMLS_hybrid_lambda2_to_THDMLS(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_hybrid_lambda2 --> THDMLS"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_hybrid_lambda2 parameters:" << myP << std::endl;
    std::cout << "THDMLS parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMLS_hybrid_lambda2atQ
#define FRIEND THDMLSatQ

// Translation function definition
void MODEL_NAMESPACE::THDMLS_hybrid_lambda2atQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_hybrid_lambda2atQ --> THDMLSatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_hybrid_lambda2atQ parameters:" << myP << std::endl;
    std::cout << "THDMLSatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_hybrid_lambda1
#define FRIEND THDMflipped

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_hybrid_lambda1_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_hybrid_lambda1 --> THDMflipped"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_hybrid_lambda1 parameters:" << myP << std::endl;
    std::cout << "THDMflipped parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_hybrid_lambda1atQ
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_hybrid_lambda1atQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_hybrid_lambda1atQ --> THDMflippedatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
               m12_2 = myP.getValue("m12_2"), lambda_2 = myP.getValue("lambda_2");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_1 = 1.0/(v2*pow(cb,2)*pow(sa,2)) * \
      ( pow(m_h,2)*(pow(sa,4) - pow(ca,4)) + m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_2*v2*pow(sb,2)*pow(ca,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_hybrid_lambda1atQ parameters:" << myP << std::endl;
    std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_hybrid_lambda2
#define FRIEND THDMflipped

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_hybrid_lambda2_to_THDMflipped(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_hybrid_lambda2 --> THDMflipped"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );
  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_hybrid_lambda2 parameters:" << myP << std::endl;
    std::cout << "THDMflipped parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL


#define MODEL  THDMflipped_hybrid_lambda2atQ
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_hybrid_lambda2atQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_hybrid_lambda2atQ --> THDMflippedatQ"<<LogTags::info<<EOM;

  const double m_h = myP.getValue("m_h"), sba = myP.getValue("sba"), tanb = myP.getValue("tanb"), \
      m12_2 = myP.getValue("m12_2"), lambda_1 = myP.getValue("lambda_1");

  const double beta = atan(tanb);
  double ba = asin(sba);
  const double alpha = beta - ba;
  const double cb = cos(beta), sb = sin(beta), ca = cos(alpha), sa = sin(alpha), cotb = 1./tanb;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);

  const double lambda_2 = 1.0/(v2*pow(sb,2)*pow(ca,2)) * \
      ( -pow(m_h,2)*(pow(sa,4) - pow(ca,4)) - m12_2*(cotb*pow(ca,2) - tanb*pow(sa,2)) + lambda_1*v2*pow(cb,2)*pow(sa,2));

  targetP.setValue("lambda_1", lambda_1 );
  targetP.setValue("lambda_2", lambda_2 );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", m12_2 );
  targetP.setValue("tanb", tanb );

  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_hybrid_lambda2atQ parameters:" << myP << std::endl;
    std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL