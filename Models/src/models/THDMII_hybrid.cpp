///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation functions for THDMII_hybrid
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

#include "gambit/Models/models/THDMII_hybrid.hpp"
#include "gambit/Models/models/THDMII.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMII_hybrid
#define FRIEND THDMII

// Translation function definition
void MODEL_NAMESPACE::THDMII_hybrid_to_THDMII(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMII_hybrid --> THDMII"<<LogTags::info<<EOM;
  
  targetP.setValue("lambda_1", myP.getValue("m_h") );
  targetP.setValue("lambda_2", myP.getValue("lambda_2") );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", basis["m12_2"] );
  targetP.setValue("tanb", basis["tanb"] );

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMII_hybrid parameters:" << myP << std::endl;
    std::cout << "THDMII parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL