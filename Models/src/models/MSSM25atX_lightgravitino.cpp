///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  MSSM25 translation function definitions
///
///  Contains translation functions for
///  MSSM25atQ_lightgravitino        --> MSSM30atQ_lightgravitino
///  MSSM25atQ_mA_lightgravitino     --> MSSM30atQ_mA_lightgravitino
///  MSSM25atMGUT_lightgravitino     --> MSSM30atMGUT_lightgravitino
///  MSSM25atMGUT_mA_lightgravitino  --> MSSM30atMGUT_mA_lightgravitino
///  MSSM25atMSUSY_lightgravitino    --> MSSM30atMSUSY_lightgravitino
///  MSSM25atMSUSY_mA_lightgravitino --> MSSM30atMSUSY_mA_lightgravitino
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

#include "gambit/Models/models/MSSM25atQ_lightgravitino.hpp"
#include "gambit/Models/models/MSSM25atQ_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM25atMGUT_lightgravitino.hpp"
#include "gambit/Models/models/MSSM25atMGUT_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM25atMSUSY_lightgravitino.hpp"
#include "gambit/Models/models/MSSM25atMSUSY_mA_lightgravitino.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"


#define DEFINE_IAPFUNC(PARENT) \
void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP) \
{ \
   logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "..."<<LogTags::info<<EOM; \
   MSSM25atX_to_MSSM30atX(myP, targetP); \
} \

#define MODEL MSSM25atQ_lightgravitino
DEFINE_IAPFUNC(MSSM30atQ_lightgravitino)
#undef MODEL
#define MODEL MSSM25atQ_mA_lightgravitino
DEFINE_IAPFUNC(MSSM30atQ_mA_lightgravitino)
#undef MODEL
#define MODEL MSSM25atMGUT_lightgravitino
DEFINE_IAPFUNC(MSSM30atMGUT_lightgravitino)
#undef MODEL
#define MODEL MSSM25atMGUT_mA_lightgravitino
DEFINE_IAPFUNC(MSSM30atMGUT_mA_lightgravitino)
#undef MODEL
#define MODEL MSSM25atMSUSY_lightgravitino
DEFINE_IAPFUNC(MSSM30atMSUSY_lightgravitino)
#undef MODEL
#define MODEL MSSM25atMSUSY_mA_lightgravitino
DEFINE_IAPFUNC(MSSM30atMSUSY_mA_lightgravitino)
#undef MODEL

