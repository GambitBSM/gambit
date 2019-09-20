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

#include "gambit/Models/models/MSSM63atQ.hpp" // Contains declaration of MSSM_mA_to_MSSM_mhud and MSSMatX_to_MSSMatQ functions
#include "gambit/Models/models/MSSM30atQ.hpp"
#include "gambit/Models/models/MSSM30atQ_mA.hpp"
#include "gambit/Models/models/MSSM30atMGUT.hpp"
#include "gambit/Models/models/MSSM30atMGUT_mA.hpp"
#include "gambit/Models/models/MSSM30atMSUSY.hpp"
#include "gambit/Models/models/MSSM30atMSUSY_mA.hpp"

#include "gambit/Elements/spectrum.hpp"

using namespace Gambit::Utils;

// General helper translation function definition
namespace Gambit { 
  void MSSM30atX_to_MSSM63atX(const ModelParameters &myP, ModelParameters &targetP)
  {

     // Copy all common parameters of MSSM30atX into MSSM63atX
     targetP.setValues(myP,false);
    
     // Manually set parameters that differ

     // RH squark soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("mq2_11",  myP["mq2_1"] );
     targetP.setValue("mq2_12",  0. );
     targetP.setValue("mq2_13",  0. );

     //targetP.setValue("mq2_21",  0. );
     targetP.setValue("mq2_22",  myP["mq2_2"] );
     targetP.setValue("mq2_23",  0. );

     //targetP.setValue("mq2_31",  0. );
     //targetP.setValue("mq2_32",  0. );
     targetP.setValue("mq2_33",  myP["mq2_3"] );

     // RH slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("ml2_11",  myP["ml2_1"] );
     targetP.setValue("ml2_12",  0. );
     targetP.setValue("ml2_13",  0. );

     //targetP.setValue("ml2_21",  0. );
     targetP.setValue("ml2_22",  myP["ml2_2"] );
     targetP.setValue("ml2_23",  0. );

     //targetP.setValue("ml2_31",  0. );
     //targetP.setValue("ml2_32",  0. );
     targetP.setValue("ml2_33",  myP["ml2_3"] );

     // LH down-type slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("md2_11",  myP["md2_1"] );
     targetP.setValue("md2_12",  0. );
     targetP.setValue("md2_13",  0. );

     //targetP.setValue("md2_21",  0. );
     targetP.setValue("md2_22",  myP["md2_2"] );
     targetP.setValue("md2_23",  0. );

     //targetP.setValue("md2_31",  0. );
     //targetP.setValue("md2_32",  0. );
     targetP.setValue("md2_33",  myP["md2_3"] );

     // LH up-type slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("mu2_11",  myP["mu2_1"] );
     targetP.setValue("mu2_12",  0. );
     targetP.setValue("mu2_13",  0. );

     //targetP.setValue("mu2_21",  0. );
     targetP.setValue("mu2_22",  myP["mu2_2"] );
     targetP.setValue("mu2_23",  0. );

     //targetP.setValue("mu2_31",  0. );
     //targetP.setValue("mu2_32",  0. );
     targetP.setValue("mu2_33",  myP["mu2_3"] );

     // LH charged slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("me2_11",  myP["me2_1"] );
     targetP.setValue("me2_12",  0. );
     targetP.setValue("me2_13",  0. );

     //targetP.setValue("me2_21",  0. );
     targetP.setValue("me2_22",  myP["me2_2"] );
     targetP.setValue("me2_23",  0. );

     //targetP.setValue("me2_31",  0. );
     //targetP.setValue("me2_32",  0. );
     targetP.setValue("me2_33",  myP["me2_3"] );

     // slepton trilinear couplings
     // Off-diagonal elements set to zero
     targetP.setValue("Ae_11",  myP["Ae_1"] );
     targetP.setValue("Ae_12",  0. );
     targetP.setValue("Ae_13",  0. );

     targetP.setValue("Ae_21",  0. );
     targetP.setValue("Ae_22",  myP["Ae_2"] );
     targetP.setValue("Ae_23",  0. );

     targetP.setValue("Ae_31",  0. );
     targetP.setValue("Ae_32",  0. );
     targetP.setValue("Ae_33",  myP["Ae_3"] );

     // down-type trilinear couplings
     // Off-diagonal elements set to zero
     // First and second generation to zero
     targetP.setValue("Ad_11",  myP["Ad_1"] );
     targetP.setValue("Ad_12",  0. );
     targetP.setValue("Ad_13",  0. );

     targetP.setValue("Ad_21",  0. );
     targetP.setValue("Ad_22",  myP["Ad_2"] );
     targetP.setValue("Ad_23",  0. );

     targetP.setValue("Ad_31",  0. );
     targetP.setValue("Ad_32",  0. );
     targetP.setValue("Ad_33",  myP["Ad_3"] );

     // up-type trilinear couplings
     // Off-diagonal elements set to zero
     // First and second generation set to zero
     targetP.setValue("Au_11",  myP["Au_1"] );
     targetP.setValue("Au_12",  0. );
     targetP.setValue("Au_13",  0. );

     targetP.setValue("Au_21",  0. );
     targetP.setValue("Au_22",  myP["Au_2"] );
     targetP.setValue("Au_23",  0. );

     targetP.setValue("Au_31",  0. );
     targetP.setValue("Au_32",  0. );
     targetP.setValue("Au_33",  myP["Au_3"] );

     // Done!
  }
}

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
   const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
   MSSM_mA_to_MSSM_mhud(myP, targetP, HE);
}
#undef MODEL

#define MODEL MSSM30atMGUT_mA
void MODEL_NAMESPACE::MSSM30atMGUT_mA_to_MSSM30atMGUT(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT_mA --> MSSM30atMGUT."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMGUT) // Need the pipe for the TARGET model
   const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
   MSSM_mA_to_MSSM_mhud(myP, targetP, HE);
}
#undef MODEL

#define MODEL MSSM30atMSUSY_mA
void MODEL_NAMESPACE::MSSM30atMSUSY_mA_to_MSSM30atMSUSY(const ModelParameters &myP, ModelParameters &targetP)
{
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY_mA --> MSSM30atMSUSY."<<LogTags::info<<EOM;
   USE_MODEL_PIPE(MSSM30atMSUSY) // Need the pipe for the TARGET model
   const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
   MSSM_mA_to_MSSM_mhud(myP, targetP, HE);
}
#undef MODEL
/// @}

/// @{ Interpret-as-friend (MGUT and MSUSY to Q, in primary parameterisation only)
#define MODEL MSSM30atMGUT
void MODEL_NAMESPACE::MSSM30atMGUT_to_MSSM30atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMGUT --> MSSM30atQ..."<<LogTags::info<<EOM;
   const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
   MSSMatX_to_MSSMatQ(myP, targetP, HE);
}
#undef MODEL

#define MODEL MSSM30atMSUSY
void MODEL_NAMESPACE::MSSM30atMSUSY_to_MSSM30atQ (const ModelParameters &myP, ModelParameters &targetP)
{
   USE_MODEL_PIPE(MSSM30atQ) // Need pipe for TARGET model
   logger()<<"Running interpret_as_X calculations for MSSM30atMSUSY --> MSSM30atQ..."<<LogTags::info<<EOM;
   const SubSpectrum& HE = Dep::unimproved_MSSM_spectrum->get_HE();
   MSSMatX_to_MSSMatQ(myP, targetP, HE);
}
#undef MODEL

/// @}
