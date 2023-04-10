//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  MSSM models with boundary conditions at
///  scale MSUSY and with A pole mass and mu
///  as explicit input parameters instead of mHu2 and mHd2.
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  MSSM63atMSUSY_mA  --> MSSM63atMSUSY
///  MSSM30atMSUSY_mA  --> MSSM63atMSUSY_mA
///  MSSM25atMSUSY_mA  --> MSSM30atMSUSY_mA
///  MSSM20atMSUSY_mA  --> MSSM25atMSUSY_mA
///
///  As well as the interpret-as-friend translation
///  functions for:
///
///  MSSM30atMSUSY_mA  --> MSSM30atMSUSY
///  MSSM20atMSUSY_mA  --> MSSM20atMSUSY
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
///  \date 2015 Sep
///  \date 2017 Aug
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2017 Sep, Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Sept
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/Models/models/MSSMatMSUSY_mA.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"

// Activate debug output
//#define MSSMatMSUSY_mA_DBUG

// MSSM63atMSUSY_mA --> MSSM63atMSUSYA
#define MODEL MSSM63atMSUSY_mA
#define PARENT MSSM63atMSUSY
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(PARENT)
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSM_mA_to_MSSM_mhud(myP, targetP, HE);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT
#undef MODEL

// MSSM30atMSUSY_mA --> MSSM63atMSUSY_mA
#define MODEL MSSM30atMSUSY_mA
#define PARENT MSSM63atMSUSY_mA
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM30atX_to_MSSM63atX(myP, targetP);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT

// MSSM30atMSUSY_mA --> MSSM30atMSUSY
#define FRIEND MSSM30atMSUSY
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,FRIEND) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(FRIEND) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(FRIEND) // Need the pipe for the TARGET model
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSM_mA_to_MSSM_mhud(myP, targetP, HE);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(FRIEND) " parameters:" << targetP << std::endl;
     #endif
  }
#undef FRIEND
#undef MODEL

// MSSM25atMSUSY_mA --> MSSM30atMSUSY_mA
#define MODEL MSSM25atMSUSY_mA
#define PARENT MSSM30atMSUSY_mA
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM25atX_to_MSSM30atX(myP, targetP);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT
#undef MODEL

// MSSM20atMSUSY_mA --> MSSM25atMSUSY_mA
#define MODEL MSSM20atMSUSY_mA
#define PARENT MSSM25atMSUSY_mA
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM20atX_to_MSSM25atX(myP, targetP);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT

// MSSM20atMSUSY_mA --> MSSM20atMSUSY
#define FRIEND MSSM20atMSUSY
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,FRIEND) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(FRIEND) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(FRIEND) // Need the pipe for the TARGET model
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSM_mA_to_MSSM_mhud(myP, targetP, HE);

     // Done
     #ifdef MSSMatMSUSY_mA_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(FRIEND) " parameters:" << targetP << std::endl;
     #endif
  }
#undef FRIEND
#undef MODEL

