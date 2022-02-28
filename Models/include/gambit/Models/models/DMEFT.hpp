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
///  \date 2019 Oct
///
///  \author Patrick Stöcker
///          (patrick.stoecker@kit.edu)
///  \date 2021 Mar, Sep
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
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
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,mwimp,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,wimp_sc,bool)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,sigmav,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,RD_fraction,double)

#undef MODEL

#endif
