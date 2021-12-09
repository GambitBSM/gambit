///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Translation function definitions for all
///  'mA' versions of 63 parameter MSSM, back to
///  the corresponding mhu2 mhd2 parameterisations
///
///  Contains translation functions for:
///   MSSM63atQ_mA     --> MSSM63atQ
///   MSSM63atMGUT_mA  --> MSSM63atMGUT
///   MSSM63atMSUSY_mA --> MSSM63atMSUSY
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

#include "gambit/Models/models/MSSM63atQ_mA.hpp"
#include "gambit/Models/models/MSSM63atMSUSY_mA.hpp"
#include "gambit/Models/models/MSSM63atMGUT_mA.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"
#include "gambit/Elements/spectrum.hpp"

// Activate debug output
//#define MSSM63_mA_DBUG

#define MODEL  MSSM63atQ_mA
#define PARENT MSSM63atQ
void MODEL_NAMESPACE::MSSM63atQ_mA_to_MSSM63atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atQ_mA --> MSSM63atQ..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL

#define MODEL  MSSM63atMSUSY_mA
#define PARENT MSSM63atMSUSY
void MODEL_NAMESPACE::MSSM63atMSUSY_mA_to_MSSM63atMSUSY (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atMSUSY_mA --> MSSM63atMSUSY..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL

#define MODEL  MSSM63atMGUT_mA
#define PARENT MSSM63atMGUT
void MODEL_NAMESPACE::MSSM63atMGUT_mA_to_MSSM63atMGUT (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(PARENT)
   logger()<<"Running interpret_as_parent calculations for MSSM63atMGUT_mA --> MSSM63atMGUT..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef PARENT
#undef MODEL
