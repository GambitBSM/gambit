//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Header file for DMEFT
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///
///  \author Sanjay Bloor
///         (sanjay.bloor12@imperial.ac.uk)
///  \date Oct 2019
///                                                
///  ********************************************* 

#ifndef __DMEFT_hpp__
#define __DMEFT_hpp__

// Make sure that AnnihilatingDM_general is declared first
#include "gambit/Models/models/CosmoEnergyInjection.hpp"

#define MODEL DMEFT
  START_MODEL

  DEFINEPARS(Lambda, C51, C52, C61, C62, C63, C64, C71, C72)
  DEFINEPARS(C73, C74, C75, C76, C77, C78, C79, C710, mchi)
  DEFINEPARS(mtrunIN)

  // In order to enable CMB constraints create a friendship relation
  // to the s-wave annihilation "marker" model AnnihilatingDM_general
  INTERPRET_AS_X_FUNCTION(AnnihilatingDM_general,DMEFT_to_AnnihilatingDM_general)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,WIMP_properties,WIMPprops)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,sigmav,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,RD_fraction,double)

  #define CAPABILITY WIMP_properties
  START_CAPABILITY
     #define FUNCTION DMEFT_WIMP_properties
     START_FUNCTION(WIMPprops)
     ALLOW_MODELS(DMEFT)
     #undef FUNCTION
  #undef CAPABILITY
  
  // Define the module functions
  namespace Gambit {
    namespace Models {
      namespace MODEL {
        void DMEFT_WIMP_properties(WIMPprops& result)
        {
            using namespace Pipes::DMEFT_WIMP_properties;
            result.mass   = *Param["mchi"];
            result.spinx2 = 1;
            result.sc     = false;
            result.name   = "chi";
        } 

        void DMEFT_to_AnnihilatingDM_general (const ModelParameters& /*myparams*/, ModelParameters &friendparams)
        {
          USE_MODEL_PIPE(AnnihilatingDM_general) // get pipe for "interpret as friend" function
          logger()<<"Running interpret_as_friend calculations for DMEFT -> AnnihilatingDM_general ..."<<EOM;

          const auto wimp_props = *Dep::WIMP_properties;
          const double k = (wimp_props.sc) ? 1. : 0.5;
          const double f = *Dep::RD_fraction;

          friendparams.setValue("mass", wimp_props.mass);
          // In AnnihilatingDM_general the parameter "sigmav" is assumed to already include
          // (RD_fraction)^2 and the factor k
          friendparams.setValue("sigmav", k*f*f*(*Dep::sigmav));
        }
      }
    }
  }

#undef MODEL

#endif
