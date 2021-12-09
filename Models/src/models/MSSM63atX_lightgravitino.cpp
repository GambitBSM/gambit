///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation function definitions for
///  63 parameter MSSM variants back to the
///  'master' MSSM63atQ_lightgravitino generic model
///
///  Contains interpret-as-parent definitions for
///   MSSM63atMGUT_lightgravitino
///   MSSM63atMSUSY_lightgravitino
///  back to their common parent:
///   MSSM63atQ_lightgravitino
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

#include "gambit/Models/models/MSSM63atMGUT_lightgravitino.hpp"
#include "gambit/Models/models/MSSM63atMSUSY_lightgravitino.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"
#include "gambit/Elements/spectrum.hpp"

using namespace Gambit::Utils;

#define PARENT MSSM63atQ_lightgravitino
#define MODEL  MSSM63atMGUT_lightgravitino
void MODEL_NAMESPACE::MSSM63atMGUT_lightgravitino_to_MSSM63atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for MSSM63atMGUT_lightgravitino --> MSSM63atQ_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

#define MODEL  MSSM63atMSUSY_lightgravitino
void MODEL_NAMESPACE::MSSM63atMSUSY_lightgravitino_to_MSSM63atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
   logger()<<"Running interpret_as_parent calculations for MSSM63atMSUSY_lightgravitino --> MSSM63atQ_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL
#undef PARENT
