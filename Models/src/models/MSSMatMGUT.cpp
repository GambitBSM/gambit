//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Translation function definitions for the
///  MSSM models with boundary conditions at
///  scale MGUT
///
///  Contains the interpret-as-parent translation
///  functions for:
///
///  MSSM63atMGUT  --> MSSM63atQ
///  MSSM30atMGUT  --> MSSM63atMGUT
///  MSSM25atMGUT  --> MSSM30atMGUT
///  MSSM20atMGUT  --> MSSM25atMGUT
///
///  As well as the interpret-as-friend translation
///  functions for:
///
///  MSSM30atMGUT  --> MSSM30atQ
///  MSSM20atMGUT  --> MSSM20atQ
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
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Aug
///  \date 2017 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Sept
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/Models/models/MSSMatMGUT.hpp"
#include "gambit/Models/models/MSSMatQ.hpp"
#include "gambit/Models/models/MSSM_translation_helpers.hpp"

// Activate debug output
//#define MSSMatMGUT_DBUG

// MSSM63atMGUT --> MSSM63atQ
#define MODEL MSSM63atMGUT
#define PARENT MSSM63atQ
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(PARENT) // get pipe for "interpret as PARENT" function
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSMatX_to_MSSMatQ(myP, targetP, HE);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT
#undef MODEL

// MSSM30atMGUT --> MSSM63atMGUT
#define MODEL MSSM30atMGUT
#define PARENT MSSM63atMGUT
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM30atX_to_MSSM63atX(myP, targetP);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT

// MSSM30atMGUT --> MSSM30atQ
#define FRIEND MSSM30atQ
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,FRIEND) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(FRIEND) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(FRIEND) // Need the pipe for the TARGET model
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSMatX_to_MSSMatQ(myP, targetP, HE);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(FRIEND) " parameters:" << targetP << std::endl;
     #endif
  }
#undef FRIEND
#undef MODEL

// MSSM25atMGUT --> MSSM30atMGUT
#define MODEL MSSM25atMGUT
#define PARENT MSSM30atMGUT
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM25atX_to_MSSM30atX(myP, targetP);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT
#undef MODEL

// MSSM20atMGUT --> MSSM25atMGUT
#define MODEL MSSM20atMGUT
#define PARENT MSSM25atMGUT
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,PARENT) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_parent calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(PARENT) "."<<LogTags::info<<EOM;

     MSSM20atX_to_MSSM25atX(myP, targetP);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(PARENT) " parameters:" << targetP << std::endl;
     #endif
  }
#undef PARENT

// MSSM20atMGUT --> MSSM20atQ
#define FRIEND MSSM20atQ
  void MODEL_NAMESPACE::CAT_3(MODEL,_to_,FRIEND) (const ModelParameters &myP, ModelParameters &targetP)
  {
     logger()<<"Running interpret_as_X calculations for " STRINGIFY(MODEL) " --> " STRINGIFY(FRIEND) "."<<LogTags::info<<EOM;

     USE_MODEL_PIPE(FRIEND) // Need the pipe for the TARGET model
     const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
     MSSMatX_to_MSSMatQ(myP, targetP, HE);

     // Done
     #ifdef MSSMatMGUT_DBUG
       std::cout << STRINGIFY(MODEL) " parameters:" << myP << std::endl;
       std::cout << STRINGIFY(FRIEND) " parameters:" << targetP << std::endl;
     #endif
  }
#undef FRIEND
#undef MODEL


