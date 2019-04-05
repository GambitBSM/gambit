///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  ScalarSingletDM_Z* to ScalarSingletDM_Z*_running translation function definitions
///  We take mS to be the tree-level MSbar mass rather than the pole mass, and use
///  the tree-level relation to determine mS^2, setting lambda_S to zero.
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
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///   \date 2015 Dec
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///   \date 2018 Sep
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/ScalarSingletDM_Z2.hpp"
#include "gambit/Models/models/ScalarSingletDM_Z2_running.hpp"
#include "gambit/Models/models/ScalarSingletDM_Z3.hpp"
#include "gambit/Models/models/ScalarSingletDM_Z3_running.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define SingletDM_DBUG

using namespace Gambit::Utils;


/////////////// Z2 Model ///////////////////////////

#define MODEL  ScalarSingletDM_Z2
#define PARENT ScalarSingletDM_Z2_running

// Translation function definition
void MODEL_NAMESPACE::ScalarSingletDM_Z2_to_ScalarSingletDM_Z2_running (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for ScalarSingletDM_Z2 --> ScalarSingletDM_Z2_running..."<<LogTags::info<<EOM;

  targetP.setValue("mS", myP.getValue("mS") );
  targetP.setValue("lambda_hS",myP.getValue("lambda_hS"));
  targetP.setValue("lambda_S", 0 );

  // Done! Check that everything is ok if desired.
  #ifdef SingletDM_DBUG
    std::cout << "ScalarSingletDM_Z2 parameters:" << myP << std::endl;
    std::cout << "ScalarSingletDM_Z2_running parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL


/////////////// Z3 Model ///////////////////////////

#define MODEL  ScalarSingletDM_Z3
#define PARENT ScalarSingletDM_Z3_running

// Translation function definition
void MODEL_NAMESPACE::ScalarSingletDM_Z3_to_ScalarSingletDM_Z3_running (const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
  logger()<<"Running interpret_as_parent calculations for ScalarSingletDM_Z2 --> ScalarSingletDM_Z2_running..."<<LogTags::info<<EOM;

  targetP.setValue("mS", myP.getValue("mS") );
  targetP.setValue("lambda_hS",myP.getValue("lambda_hS"));
  targetP.setValue("mu3",myP.getValue("mu3"));
  targetP.setValue("lambda_S", 0 );

  // Done! Check that everything is ok if desired.
  #ifdef SingletDM_DBUG
    std::cout << "ScalarSingletDM_Z3 parameters:" << myP << std::endl;
    std::cout << "ScalarSingletDM_Z3_running parameters   :" << targetP << std::endl;
  #endif
}

#undef PARENT
#undef MODEL
