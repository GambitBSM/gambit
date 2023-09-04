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

#include "gambit/Models/models/RightHandedNeutrinos_diff.hpp"


#define MODEL RightHandedNeutrinos_diff 
  void MODEL_NAMESPACE::RightHandedNeutrinos_diff_to_RightHandedNeutrinos (const ModelParameters &myP, ModelParameters &targetP)
  {

     logger()<<"Running interpret_as_parent calculations for RightHandedNeutrinos_diff --> RightHandedNeutrinos."<<LogTags::info<<EOM;
     
     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, as these are set below.
     targetP.setValues(myP,false);

     // M2
     targetP.setValue("M_2", myP["M_1"]+myP["delta_M21"]);
  }

#undef MODEL


