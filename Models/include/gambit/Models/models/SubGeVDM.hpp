//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Header file for SubGeVDM models, includes
///  - SubGeVDM_fermion
///  - SubGeVDM_fermion_sigmae
///  - SubGeVMD_fermion_sigmaN
///  - SubGeV_fermion_RDprior
///  - Resonant_SubGeVDM_fermion
///  - Resonant_SubGeV_fermion_RDprior
///  - SubGeVDM_scalar
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 12:32PM on October 15, 2019
///
///  \author Felix Kahlhoefer
///         (kahlhoefer@kit.edu)
///  \date 2022 May
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2023 Dec
///
///  *********************************************

#ifndef __SubGeVDM_fermion_hpp__
#define __SubGeVDM_fermion_hpp__

// Make sure that AnnihilatingDM_general is declared first
#include "gambit/Models/models/CosmoEnergyInjection.hpp"

#define MODEL SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,mAp,gDM,kappa,etaDM)

  // In order to enable CMB constraints create a friendship relation
  // to the s-wave annihilation "marker" model AnnihilatingDM_general
  INTERPRET_AS_X_FUNCTION(AnnihilatingDM_general,SubGeVDM_fermion_to_AnnihilatingDM_general)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,mwimp,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,wimp_sc,bool)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,sigmav,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,ID_suppression,double)

#undef MODEL

#define MODEL SubGeVDM_fermion_sigmae
#define PARENT SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,mAp,sigmae,kappa,etaDM)

  // Translate to "SubGeVDM_fermion" (Mapping is defined in SubGeVDM.cpp)
  INTERPRET_AS_PARENT_FUNCTION(SubGeVDM_fermion_sigmae_to_SubGeVDM_fermion)
#undef PARENT
#undef MODEL

#define MODEL SubGeVDM_fermion_sigmaN
#define PARENT SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,mAp,sigmaN,kappa,etaDM)

  // Translate to "SubGeVDM_fermion" (Mapping is defined in SubGeVDM.cpp)
  INTERPRET_AS_PARENT_FUNCTION(SubGeVDM_fermion_sigmaN_to_SubGeVDM_fermion)
#undef PARENT
#undef MODEL


#define MODEL SubGeVDM_fermion_RDprior
#define PARENT SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,mAp,gDM,kappa,etaDM_mDM)

  INTERPRET_AS_PARENT_FUNCTION(SubGeVDM_fermion_RDprior_to_SubGeVDM_fermion)
#undef PARENT
#undef MODEL


#define MODEL Resonant_SubGeVDM_fermion
#define PARENT SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,epsR,gDM,kappa,etaDM)

  INTERPRET_AS_PARENT_FUNCTION(Resonant_SubGeVDM_fermion_to_SubGeVDM_fermion)
#undef PARENT
#undef MODEL

#define MODEL Resonant_SubGeVDM_fermion_RDprior
#define PARENT Resonant_SubGeVDM_fermion
  START_MODEL

  DEFINEPARS(mDM,epsR,gDM,kappa,etaDM_mDM)

  INTERPRET_AS_PARENT_FUNCTION(Resonant_SubGeVDM_fermion_RDprior_to_Resonant_SubGeVDM_fermion)
#undef PARENT
#undef MODEL


#define MODEL SubGeVDM_scalar
  START_MODEL

  DEFINEPARS(mDM,mAp,gDM,kappa,etaDM)

  // In order to enable CMB constraints create a friendship relation
  // to the s-wave annihilation "marker" model AnnihilatingDM_general
  INTERPRET_AS_X_FUNCTION(AnnihilatingDM_general,SubGeVDM_scalar_to_AnnihilatingDM_general)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,mwimp,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,wimp_sc,bool)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,sigmav,double)
  INTERPRET_AS_X_DEPENDENCY(AnnihilatingDM_general,ID_suppression,double)

#undef MODEL

#define MODEL SubGeVDM_scalar_RDprior
#define PARENT SubGeVDM_scalar
  START_MODEL

  DEFINEPARS(mDM,mAp,gDM,kappa,etaDM_mDM)

  INTERPRET_AS_PARENT_FUNCTION(SubGeVDM_scalar_RDprior_to_SubGeVDM_scalar)
#undef PARENT
#undef MODEL


#define MODEL Resonant_SubGeVDM_scalar
#define PARENT SubGeVDM_scalar
  START_MODEL

  DEFINEPARS(mDM,epsR,gDM,kappa,etaDM)

  INTERPRET_AS_PARENT_FUNCTION(Resonant_SubGeVDM_scalar_to_SubGeVDM_scalar)
#undef PARENT
#undef MODEL

#define MODEL Resonant_SubGeVDM_scalar_RDprior
#define PARENT Resonant_SubGeVDM_scalar
  START_MODEL

  DEFINEPARS(mDM,epsR,gDM,kappa,etaDM_mDM)

  INTERPRET_AS_PARENT_FUNCTION(Resonant_SubGeVDM_scalar_RDprior_to_Resonant_SubGeVDM_scalar)
#undef PARENT
#undef MODEL

#endif
