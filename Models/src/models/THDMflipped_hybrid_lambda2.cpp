///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation functions for THDMflipped_hybrid_lambda2
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
#include <math.h>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDMflipped_hybrid_lambda2.hpp"
#include "gambit/Models/models/THDMflipped.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_helper.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
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