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

#include "gambit/Models/models/THDM_III.hpp"
#include "gambit/Models/models/THDM_IIIatQ.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define SingletDM_DBUG

using namespace Gambit::Utils;

// Need to define MODEL and PARENT in order for helper macros to work correctly
#define MODEL  THDM_III
#define PARENT THDM_IIIatQ

// Translation function definition
void MODEL_NAMESPACE::THDM_III_to_THDM_IIIatQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for THDM_III --> THDM_IIIatQ.."<<LogTags::info<<EOM;

  targetP.setValue("Qin",80.39);
  targetP.setValue("QrunTo", 173.15);

  targetP.setValue("Lambda_1", myP.getValue("Lambda_1") );
  targetP.setValue("Lambda_2", myP.getValue("Lambda_2") );
  targetP.setValue("Lambda_3", myP.getValue("Lambda_3") );
  targetP.setValue("Lambda_4", myP.getValue("Lambda_4") );
  targetP.setValue("Lambda_5", myP.getValue("Lambda_5") );
  targetP.setValue("Lambda_7", myP.getValue("Lambda_7") );
  targetP.setValue("m22_2", myP.getValue("m22_2") );
  targetP.setValue("tanb", myP.getValue("tanb") );
  targetP.setValue("alpha", myP.getValue("alpha") );
  targetP.setValue("Y2ct_real", myP.getValue("Y2ct_real") );
  targetP.setValue("Y2tc_real", myP.getValue("Y2tc_real") );
  targetP.setValue("Y2tt_real", myP.getValue("Y2tt_real") );
  targetP.setValue("Y2ct_imag", myP.getValue("Y2ct_imag") );
  targetP.setValue("Y2tc_imag", myP.getValue("Y2tc_imag") );
  targetP.setValue("Y2tt_imag", myP.getValue("Y2tt_imag") );
  targetP.setValue("Y2sb_real", myP.getValue("Y2sb_real") );
  targetP.setValue("Y2bs_real", myP.getValue("Y2bs_real") );
  targetP.setValue("Y2bb_real", myP.getValue("Y2bb_real") );
  targetP.setValue("Y2sb_imag", myP.getValue("Y2sb_imag") );
  targetP.setValue("Y2bs_imag", myP.getValue("Y2bs_imag") );
  targetP.setValue("Y2bb_imag", myP.getValue("Y2bb_imag") );

   // Done! Check that everything is ok if desired.
   #ifdef THDM_DBUG
     std::cout << "THDM_III parameters:" << myP << std::endl;
     std::cout << "THDM_IIIatQ parameters   :" << targetP << std::endl;
   #endif
}

#undef PARENT
#undef MODEL
