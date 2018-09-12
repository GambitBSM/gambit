///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  THDM to THDMatQ
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
#include "gambit/Models/models/THDMatQ.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define SingletDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and PARENT in order for helper macros to work correctly
#define MODEL  THDM
#define PARENT THDMatQ

// Translation function definition
void MODEL_NAMESPACE::THDM_to_THDMatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for THDM --> THDMatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("lambda_1", myP.getValue("lambda_1") );
  targetP.setValue("lambda_2", myP.getValue("lambda_2") );
  targetP.setValue("lambda_3", myP.getValue("lambda_3") );
  targetP.setValue("lambda_4", myP.getValue("lambda_4") );
  targetP.setValue("lambda_5", myP.getValue("lambda_5") );
  targetP.setValue("lambda_6", myP.getValue("lambda_6") );
  targetP.setValue("lambda_7", myP.getValue("lambda_7") );
  targetP.setValue("m12_2", myP.getValue("m12_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );
  targetP.setValue("y_type", myP.getValue("y_type") );


   // Done! Check that everything is ok if desired.
   #ifdef THDM_DBUG
     std::cout << "THDM parameters:" << myP << std::endl;
     std::cout << "THDMatQ parameters   :" << targetP << std::endl;
   #endif
}

#undef PARENT
#undef MODEL
