//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Header file for SubGeVDM_fermion
///
///  Authors (add name and date if you modify):    
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///
///  \author Felix Kahlhoefer
///         (kahlhoefer@kit.edu)
///  \date 202 May
///
///  ********************************************* 

#ifndef __SubGeVDM_fermion_hpp__
#define __SubGeVDM_fermion_hpp__

// Make sure that AnnihilatingDM_general is declared first
#include "gambit/Models/models/CosmoEnergyInjection.hpp"

#define MODEL SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,mAp,gDM,kappa,etaDM,smooth)

  // In order to enable CMB constraints create a friendship relation
  // to the s-wave annihilation "marker" model AnnihilatingDM_general
  INTERPRET_AS_X_FUNCTION(AnnihilatingDM_general,SubGeVDM_fermion_to_AnnihilatingDM_general)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,mwimp,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,wimp_sc,bool)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,sigmav,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,RD_fraction,double)

#undef MODEL

#endif
