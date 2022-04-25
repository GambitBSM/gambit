//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Super Renormalizable Higgs Portal DM
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Iñigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///  \date 2019 December
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#ifndef __SuperRenormHP_hpp__
#define __SuperRenormHP_hpp__

#include "gambit/Models/models/ModifiedGravityYukawa.hpp"
#include "gambit/Models/models/CosmoEnergyInjection.hpp"

#define MODEL SuperRenormHP
  START_MODEL
  // Physical units : mass [GeV], theta [dimensionless]
  DEFINEPARS(mS) // mass of the DM scalar particle
  DEFINEPARS(theta) // mixing angle with the SM Higgs boson

  // Friendship with ModifiedGravityYukawa
  INTERPRET_AS_X_FUNCTION(ModifiedGravityYukawa, SuperRenormHP_to_ModifiedGravityYukawa)
  INTERPRET_AS_X_DEPENDENCY(ModifiedGravityYukawa, get_Higgs_Nucleon_coupling_fN, Higgs_Nucleon_coupling_fN)

  INTERPRET_AS_X_FUNCTION(DecayingDM_mixture, SuperRenormHP_to_DecayingDM_mixture)
  INTERPRET_AS_X_DEPENDENCY(DecayingDM_mixture, DM_lifetime, double)
  INTERPRET_AS_X_DEPENDENCY(DecayingDM_mixture, RD_fraction, double)
  INTERPRET_AS_X_DEPENDENCY(DecayingDM_mixture, DecDM_branching_ph, double)
  INTERPRET_AS_X_DEPENDENCY(DecayingDM_mixture, DecDM_branching_el, double)

  MAP_TO_CAPABILITY(mS, DM_mass)
#undef MODEL

#endif
*/
