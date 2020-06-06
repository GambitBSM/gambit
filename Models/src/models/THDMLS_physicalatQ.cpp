///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDMLS_physicalatQ to THDMIatQ
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

#include "gambit/Models/models/THDMLS_physicalatQ.hpp"
#include "gambit/Models/models/THDMLSatQ.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"

// Activate debug output
// #define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMLS_physicalatQ
#define FRIEND THDMLSatQ

// Translation function definition
void MODEL_NAMESPACE::THDMLS_physicalatQ_to_THDMLSatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMLS_physicalatQ --> THDM:SatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

  basis["m_h"] = myP.getValue("m_h");
  basis["m_H"] = myP.getValue("m_H");
  basis["m_A"]= myP.getValue("m_A");
  basis["m_Hp"]= myP.getValue("m_Hp");
  basis["m12_2"] = myP.getValue("m12_2");
  basis["tanb"] = myP.getValue("tanb");
  basis["sba"] = myP.getValue("sba");
  basis["lambda6"] = myP.getValue("lambda_6");
  basis["lambda7"] = myP.getValue("lambda_7");

  // Check for problematic parameter choices here

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
  targetP.setValue("Qin", myP.getValue("Qin") );
  targetP.setValue("QrunTo", myP.getValue("QrunTo") );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMLS_physicalatQ parameters:" << myP << std::endl;
    std::cout << "THDMLSatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL