///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation function definitions for
///  63 parameter MSSM variants back to the
///  'master' MSSM63atQ generic model
///
///  Contains interpret-as-parent definitions for
///   MSSM63atMGUT
///   MSSM63atMSUSY
///  back to their common parent:
///   MSSM63atQ
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Aug, 2017 Oct
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MSSM63atMGUT.hpp"
#include "gambit/Models/models/MSSM63atMSUSY.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"
#include "gambit/Elements/spectrum.hpp"

using namespace Gambit::Utils;

#define PARENT MSSM63atQ
#define MODEL  MSSM63atMGUT
void MODEL_NAMESPACE::MSSM63atMGUT_to_MSSM63atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for MSSM63atMGUT --> MSSM63atQ..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

#define MODEL  MSSM63atMSUSY
void MODEL_NAMESPACE::MSSM63atMSUSY_to_MSSM63atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for MSSM63atMSUSY --> MSSM63atQ..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL
#undef PARENT
