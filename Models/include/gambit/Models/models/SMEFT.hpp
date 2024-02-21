///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Standard Model Effective Field Theory
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Feb
///
///  *********************************************


#ifndef __SMEFT_hpp__
#define __SMEFT_hpp__

#include "gambit/Models/models/WC.hpp"

// Most generic model, top of the hierarchy
#define MODEL SMEFT
   START_MODEL
   // TODO: There are O(1000) possible WCs here, so maybe there is no point in adding a full SMEFT model, but I keep this one here as placeholder in case we do
#undef MODEL


// Simplified SMEFT Model that cares about flavour violating interactions
// Uses tilde coefficients from 1409.4557 c_k~ = (ck)_23/Lambda^2 pi/(sqrt(2)*GF*alpha*Vtb*conj(Vts))
// Inherits from GWC for now, in the future in may inherit from SMEFT and friend to GWC
// TODO: This is missing dipole and scalar operators
#define PARENT GWC
#define MODEL SMEFT_FV
  START_MODEL
  DEFINEPARS(Re_cql1,Im_cql1,Re_cql3,Im_cql3,Re_cdl,Im_cdl,Re_cqe,Im_cqe,Re_cde,Im_cde)
  DEFINEPARS(Re_cHq1,Im_cHq1,Re_cHq3,Im_cHq3,Re_cHd,Im_cHd)
  // Translation functions defined in SMEFT.cpp
  INTERPRET_AS_PARENT_FUNCTION(SMEFT_FV_to_GWC)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef MODEL
#undef PARENT

#endif
