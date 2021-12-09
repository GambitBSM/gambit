///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation function definitions for all
///  'mA' versions of 63 parameter MSSM, back to
///  the corresponding mhu2 mhd2 parameterisations
///
///  Contains translation functions for:
///   MSSM63atQ_mA_lightgravitino     --> MSSM63atQ_lightgravitino
///   MSSM63atMGUT_mA_lightgravitino  --> MSSM63atMGUT_lightgravitino
///   MSSM63atMSUSY_mA_lightgravitino --> MSSM63atMSUSY_lightgravitino
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Aug
///  \date 2018 Oct
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2017 Sep, Oct
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MSSM63atQ_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM63atMSUSY_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM63atMGUT_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define MSSM63_mA_lightgravitino_DBUG

#define MODEL  MSSM63atQ_mA_lightgravitino
#define PARENT MSSM63atQ_lightgravitino
void MODEL_NAMESPACE::MSSM63atQ_mA_lightgravitino_to_MSSM63atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atQ_mA_lightgravitino --> MSSM63atQ_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL

#define MODEL  MSSM63atMSUSY_mA_lightgravitino
#define PARENT MSSM63atMSUSY_lightgravitino
void MODEL_NAMESPACE::MSSM63atMSUSY_mA_lightgravitino_to_MSSM63atMSUSY_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atMSUSY_mA_lightgravitino --> MSSM63atMSUSY_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL

#define MODEL  MSSM63atMGUT_mA_lightgravitino
#define PARENT MSSM63atMGUT_lightgravitino
void MODEL_NAMESPACE::MSSM63atMGUT_mA_lightgravitino_to_MSSM63atMGUT_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atMGUT_mA_lightgravitino --> MSSM63atMGUT_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL
