///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  MSSM30atX translation function definitions
///
///  Specialisations of MSSM63atQ with all
///  off-diagonal m and A terms set to zero.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  MSSM30atQ        --> MSSM63atQ
///  MSSM30atQ_mA     --> MSSM63atQ_mA
///  MSSM30atMGUT     --> MSSM63atMGUT
///  MSSM30atMGUT_mA  --> MSSM63atMGUT_mA
///  MSSM30atMSUSY    --> MSSM63atMSUSY
///  MSSM30atMSUSY_mA --> MSSM63atMSUSY_mA
///
///  As well as the interpret-as-friend translation
///  functions for:
///
///  MSSM30atQ_mA     --> MSSM30atQ
///  MSSM30atMGUT_mA  --> MSSM30atMGUT
///  MSSM30atMSUSY_mA --> MSSM30atMSUSY
///
///  and
///
///  MSSM30atMGUT  --> MSSM30atQ
///  MSSM30atMSUSY --> MSSM30atQ
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
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MSSM63atQ.hpp"
#include "gambit/Models/models/MSSM30atQ.hpp"
#include "gambit/Models/models/MSSM30atQ_mA.hpp"
#include "gambit/Models/models/MSSM30atMGUT.hpp"
#include "gambit/Models/models/MSSM30atMGUT_mA.hpp"
#include "gambit/Models/models/MSSM30atMSUSY.hpp"
#include "gambit/Models/models/MSSM30atMSUSY_mA.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"

#include "gambit/Elements/spectrum.hpp"

using namespace Gambit::Utils;

/// @{ Interpret-as-parent function definitions
/// These are particularly repetitive so let's define them with the help of a macro
#define DEFINE_IAPFUNC(PARENT) \
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP) \
{ \
   logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "..."<<LogTags::info<<EOM; \
   MSSM30atX_to_MSSM63atX(myP, targetP); \
} \

#define MODEL MSSM30atQ
DEFINE_IAPFUNC(MSSM63atQ)
#undef MODEL
#define MODEL MSSM30atQ_mA
DEFINE_IAPFUNC(MSSM63atQ_mA)
#undef MODEL
#define MODEL MSSM30atMGUT
DEFINE_IAPFUNC(MSSM63atMGUT)
#undef MODEL
#define MODEL MSSM30atMGUT_mA
DEFINE_IAPFUNC(MSSM63atMGUT_mA)
#undef MODEL
#define MODEL MSSM30atMSUSY
DEFINE_IAPFUNC(MSSM63atMSUSY)
#undef MODEL
#define MODEL MSSM30atMSUSY_mA
DEFINE_IAPFUNC(MSSM63atMSUSY_mA)
#undef MODEL
/// @}

/// @{ Interpret-as-friend (mA parameterisations to primary parameterisations)
#define MODEL MSSM30atQ_mA
void MODEL_NAMESPACE::MSSM30atQ_mA_to_MSSM30atQ(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atQ_mA --> MSSM30atQ."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atQ) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMGUT_mA
void MODEL_NAMESPACE::MSSM30atMGUT_mA_to_MSSM30atMGUT(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT_mA --> MSSM30atMGUT."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMGUT) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMSUSY_mA
void MODEL_NAMESPACE::MSSM30atMSUSY_mA_to_MSSM30atMSUSY(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY_mA --> MSSM30atMSUSY."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMSUSY) // Need the pipe for the TARGET model
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSM_mA_to_MSSM_mhud(myP, targetP, spec);
}
#undef MODEL
/// @}

/// @{ Interpret-as-friend (MGUT and MSUSY to Q, in primary parameterisation only)
#define MODEL MSSM30atMGUT
void MODEL_NAMESPACE::MSSM30atMGUT_to_MSSM30atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT --> MSSM30atQ..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

#define MODEL MSSM30atMSUSY
void MODEL_NAMESPACE::MSSM30atMSUSY_to_MSSM30atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY --> MSSM30atQ..."<<LogTags::info<<EOM;
   const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
   MSSMatX_to_MSSMatQ(myP, targetP, spec);
}
#undef MODEL

/// @}
