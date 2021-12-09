///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  MSSM25 translation function definitions
///
///  Contains translation functions for
///  MSSM25atQ        --> MSSM30atQ
///  MSSM25atQ_mA     --> MSSM30atQ_mA
///  MSSM25atMGUT     --> MSSM30atMGUT
///  MSSM25atMGUT_mA  --> MSSM30atMGUT_mA
///  MSSM25atMSUSY    --> MSSM30atMSUSY
///  MSSM25atMSUSY_mA --> MSSM30atMSUSY_mA
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  Ben Farmer
///  2017 Oct
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MSSM25atQ.hpp"
#include "gambit/Models/models/MSSM25atQ_mA.hpp"
#include "gambit/Models/models/MSSM25atMGUT.hpp"
#include "gambit/Models/models/MSSM25atMGUT_mA.hpp"
#include "gambit/Models/models/MSSM25atMSUSY.hpp"
#include "gambit/Models/models/MSSM25atMSUSY_mA.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"


/// @{ Interpret-as-parent function definitions
/// These are particularly repetitive so let's define them with the help of a macro
#define DEFINE_IAPFUNC(PARENT) \
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP) \
{ \
   logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "..."<<LogTags::info<<EOM; \
   MSSM25atX_to_MSSM30atX(myP, targetP); \
} \

#define MODEL MSSM25atQ
DEFINE_IAPFUNC(MSSM30atQ)
#undef MODEL
#define MODEL MSSM25atQ_mA
DEFINE_IAPFUNC(MSSM30atQ_mA)
#undef MODEL
#define MODEL MSSM25atMGUT
DEFINE_IAPFUNC(MSSM30atMGUT)
#undef MODEL
#define MODEL MSSM25atMGUT_mA
DEFINE_IAPFUNC(MSSM30atMGUT_mA)
#undef MODEL
#define MODEL MSSM25atMSUSY
DEFINE_IAPFUNC(MSSM30atMSUSY)
#undef MODEL
#define MODEL MSSM25atMSUSY_mA
DEFINE_IAPFUNC(MSSM30atMSUSY_mA)
#undef MODEL
/// @}

