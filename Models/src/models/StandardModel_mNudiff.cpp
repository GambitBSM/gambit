//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  RH Neutrino Model with differential masses
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Tomas Gonzao  
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 December
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/StandardModel_mNudiff.hpp"

#define MODEL StandardModel_mNudiff
  void MODEL_NAMESPACE::StandardModel_mNudiff_to_StandardModel_SLHA2 (const ModelParameters &myP, ModelParameters &targetP)
  {

     logger()<<"Running interpret_as_parent calculations for StandardModel_mNudiff --> StandardModel_SLHA2."<<LogTags::info<<EOM;
     
     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     if (myP["dmNu3l"] > 0.)  // normal hierarchy, l = 1
     {
       targetP.setValue("mNu1", myP["mNu_light"]*1e-9);
       targetP.setValue("mNu2",
           pow(myP["mNu_light"]*myP["mNu_light"]+myP["dmNu21"], 0.5)*1e-9);
       targetP.setValue("mNu3",
           pow(myP["mNu_light"]*myP["mNu_light"]+myP["dmNu3l"], 0.5)*1e-9);
     }
     else // inverted hierarchy, l = 2
     {
       targetP.setValue("mNu3", myP["mNu_light"]*1e-9);
       targetP.setValue("mNu2",
           pow(myP["mNu_light"]*myP["mNu_light"]-myP["dmNu3l"], 0.5)*1e-9);
       targetP.setValue("mNu1",
           pow(myP["mNu_light"]*myP["mNu_light"]-myP["dmNu3l"]-myP["dmNu21"], 0.5)*1e-9);
     }
  }

#undef MODEL
