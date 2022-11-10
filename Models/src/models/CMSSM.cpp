// Maiken - this file should not be synced


//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CMSSM model definitions. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer 
///  \date 2015 Jan
///   
///  \author Pat Scott  
///          (p.scott@imperial.ac.uk)
///  \date 2015 Sep
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/CMSSM.hpp"


#define MODEL CMSSM 
  void MODEL_NAMESPACE::CMSSM_to_NUHM1 (const ModelParameters &myP, ModelParameters &targetP)
  {

     logger()<<"Running interpret_as_parent calculations for CMSSM --> NUHM1."<<LogTags::info<<EOM;
     
     // Send all parameter values upstream to matching parameters in parent.
     targetP.setValues(myP);

     // MH2
     targetP.setValue("mH", myP["M0"]);

  }

#undef MODEL


