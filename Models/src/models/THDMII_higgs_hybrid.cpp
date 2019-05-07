///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation functions for THDMII_higgs_hybrid
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

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/THDMII_higgs_hybrid.hpp"
#include "gambit/Models/models/THDMII.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMII_higgs_hybrid
#define FRIEND THDMII

// Translation function definition
void MODEL_NAMESPACE::THDMII_higgs_hybrid_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_higgs_hybrid --> THDMII"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

  const double m_h = myP.getValue("m_h"), m_H = myP.getValue("m_H"), sba = myP.getValue("sba");
  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["tanb"] = myP.getValue("tanb");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda7"] = myP.getValue("Lambda_7");

  const double ba = asin(sba);
  // check that beta-alpha is in the required quadrant
  if (ba < -PI/2) ba + PI/2;
  if (ba > PI/2) ba - PI/2;
  const double cba = cos(ba);
  const double s2ba = 2.0*sba*cba;
  const double GF = Dep::SMINPUTS->GF;
  const double v2 = 1./(sqrt(2)*GF);
  const double Lambda_6 = s2ba*( pow(m_H,2) - pow(m_h,2) )/(2.0*v2);

  basis["Lambda6"] = Lambda_6;
  basis["M12_2"] = 0.5*Lambda_6*v2;

  SpecBit::fill_generic_THDM_basis(basis, sminputs);

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
    std::cout << "THDMII_higgs_hybrid parameters:" << myP << std::endl;
    std::cout << "THDMII parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL