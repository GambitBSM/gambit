///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  MSSM30atX_lightgravitino translation function definitions
///
///  Specialisations of MSSM63atQ_lightgravitino with all
///  off-diagonal m and A terms set to zero.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  MSSM30atQ_lightgravitino        --> MSSM63atQ_lightgravitino
///  MSSM30atQ_mA_lightgravitino     --> MSSM63atQ_mA_lightgravitino
///  MSSM30atMGUT_lightgravitino     --> MSSM63atMGUT_lightgravitino
///  MSSM30atMGUT_mA_lightgravitino  --> MSSM63atMGUT_mA_lightgravitino
///  MSSM30atMSUSY_lightgravitino    --> MSSM63atMSUSY_lightgravitino
///  MSSM30atMSUSY_mA_lightgravitino --> MSSM63atMSUSY_mA_lightgravitino
///
///  As well as the interpret-as-friend translation
///  functions for:
///
///  MSSM30atQ_mA_lightgravitino     --> MSSM30atQ_lightgravitino
///  MSSM30atMGUT_mA_lightgravitino  --> MSSM30atMGUT_lightgravitino
///  MSSM30atMSUSY_mA_lightgravitino --> MSSM30atMSUSY_lightgravitino
///
///  and
///
///  MSSM30atMGUT_lightgravitino  --> MSSM30atQ_lightgravitino
///  MSSM30atMSUSY_lightgravitino --> MSSM30atQ_lightgravitino
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
///  \date 2017 Oct
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

#include "gambit/Models/models/MSSM63atQ_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atQ_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atQ_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atMGUT_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atMGUT_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atMSUSY_lightgravitino.hpp"
#include "gambit/Models/models/MSSM30atMSUSY_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"

#include "gambit/Elements/spectrum.hpp"

/// @{ Interpret-as-parent function definitions
/// These are particularly repetitive so let's define them with the help of a macro
#define DEFINE_IAPFUNC(PARENT) \
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP) \
{ \
   logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "..."<<LogTags::info<<EOM; \
   MSSM30atX_to_MSSM63atX(myP, targetP); \
} \

#define MODEL MSSM30atQ_lightgravitino
DEFINE_IAPFUNC(MSSM63atQ_lightgravitino)
#undef MODEL
#define MODEL MSSM30atQ_mA_lightgravitino
DEFINE_IAPFUNC(MSSM63atQ_mA_lightgravitino)
#undef MODEL
#define MODEL MSSM30atMGUT_lightgravitino
DEFINE_IAPFUNC(MSSM63atMGUT_lightgravitino)
#undef MODEL
#define MODEL MSSM30atMGUT_mA_lightgravitino
DEFINE_IAPFUNC(MSSM63atMGUT_mA_lightgravitino)
#undef MODEL
#define MODEL MSSM30atMSUSY_lightgravitino
DEFINE_IAPFUNC(MSSM63atMSUSY_lightgravitino)
#undef MODEL
#define MODEL MSSM30atMSUSY_mA_lightgravitino
DEFINE_IAPFUNC(MSSM63atMSUSY_mA_lightgravitino)
#undef MODEL
/// @}

/// @{ Interpret-as-friend (mA parameterisations to primary parameterisations)
#define MODEL MSSM30atQ_mA_lightgravitino
void MODEL_NAMESPACE::MSSM30atQ_mA_lightgravitino_to_MSSM30atQ_lightgravitino(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atQ_mA_lightgravitino --> MSSM30atQ_lightgravitino."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atQ_lightgravitino) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMGUT_mA_lightgravitino
void MODEL_NAMESPACE::MSSM30atMGUT_mA_lightgravitino_to_MSSM30atMGUT_lightgravitino(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT_mA_lightgravitino --> MSSM30atMGUT_lightgravitino."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMGUT_lightgravitino) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMSUSY_mA_lightgravitino
void MODEL_NAMESPACE::MSSM30atMSUSY_mA_lightgravitino_to_MSSM30atMSUSY_lightgravitino(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY_mA_lightgravitino --> MSSM30atMSUSY_lightgravitino."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMSUSY_lightgravitino) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL
/// @}

/// @{ Interpret-as-friend (MGUT and MSUSY to Q, in primary parameterisation only)
#define MODEL MSSM30atMGUT_lightgravitino
void MODEL_NAMESPACE::MSSM30atMGUT_lightgravitino_to_MSSM30atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ_lightgravitino) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT_lightgravitino --> MSSM30atQ_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMSUSY_lightgravitino
void MODEL_NAMESPACE::MSSM30atMSUSY_lightgravitino_to_MSSM30atQ_lightgravitino (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ_lightgravitino) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY_lightgravitino --> MSSM30atQ_lightgravitino..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

/// @}
