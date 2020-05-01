///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation functions for THDMflipped_higgsatQ
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

#include "gambit/Models/models/THDMflipped_higgsatQ.hpp"
#include "gambit/Models/models/THDMflippedatQ.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/SpecBit/THDMSpec_helper.hpp"

// Activate debug output
//#define THDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and FRIEND in order for helper macros to work correctly
#define MODEL  THDMflipped_higgsatQ
#define FRIEND THDMflippedatQ

// Translation function definition
void MODEL_NAMESPACE::THDMflipped_higgsatQ_to_THDMflippedatQ(const ModelParameters &myP, ModelParameters &targetP)
{
  USE_MODEL_PIPE(FRIEND) // get pipe for "interpret as FRIEND" function
  logger()<<"Running interpret_as_FRIEND calculations for THDMflipped_higgsatQ --> THDMflippedatQ"<<LogTags::info<<EOM;

  const SMInputs& sminputs = *Dep::SMINPUTS;
  std::map<std::string, double> basis = SpecBit::create_empty_THDM_basis();

  basis["Lambda1"]= myP.getValue("Lambda_1");
  basis["Lambda2"]= myP.getValue("Lambda_2");
  basis["Lambda3"]= myP.getValue("Lambda_3");
  basis["Lambda4"]= myP.getValue("Lambda_4");
  basis["Lambda5"] = myP.getValue("Lambda_5");
  basis["Lambda6"] = myP.getValue("Lambda_6");
  basis["Lambda7"] = myP.getValue("Lambda_7");
  basis["M12_2"] = myP.getValue("M12_2");
  basis["tanb"] = myP.getValue("tanb");

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

  // Done! Check that everything is ok if desired.
  #ifdef THDM_DBUG
    std::cout << "THDMflipped_higgsatQ parameters:" << myP << std::endl;
    std::cout << "THDMflippedatQ parameters   :" << targetP << std::endl;
  #endif
}

#undef FRIEND
#undef MODEL
