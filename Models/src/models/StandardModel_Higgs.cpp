///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  StandardModel_Higgs to StandardModel_Higgs_running
///  translation function definitions.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 Aug
///
///  \author Pat Scott
///          (ben.farmer@gmail.com)
///  \date 2018 Sep
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/StandardModel_Higgs.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/Models/models/StandardModel_Higgs_running.hpp"

// Activate debug output
//#define SMHIGGS_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and PARENT in order for helper macros to work correctly
#define MODEL  StandardModel_Higgs
#define PARENT StandardModel_Higgs_running

// Translation function definition
void MODEL_NAMESPACE::StandardModel_Higgs_to_StandardModel_Higgs_running (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for SM_Higgs --> SM_Higgs_.."<<LogTags::info<<EOM;

  targetP.setValue("mH", myP.getValue("mH"));
  targetP.setValue("Qin", 91.1876);  // default value Z boson mass scale
  targetP.setValue("QEWSB", 173.34); // default value top mass scale

   // Done! Check that everything is ok if desired.
   #ifdef SMHIGGS_DBUG
     std::cout << "SM_Higgs parameters:" << myP << std::endl;
     std::cout << "SM_Higgs_running parameters   :" << targetP << std::endl;
   #endif
}

#undef PARENT
#undef MODEL

