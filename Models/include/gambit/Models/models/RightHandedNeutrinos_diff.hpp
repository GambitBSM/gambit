// GAMBIT: Global and Modular BSM Inference Tool
//
// *********************************************
//
// RH Neutrino Model with differential masses
//
// *********************************************
//
// Authors
// =======
//
// (add name and date if you modify)
//
// \author Tomas Gonzalo
//         (t.e.gonzalo@fys.uio.no)
// \date 2017 December
//
// *********************************************

#ifndef __RightHandedNeutrinos_diff_hpp__
#define __RightHandedNeutrinos_diff_hpp__

#include "gambit/Models/models/RightHandedNeutrinos.hpp"

#define MODEL RightHandedNeutrinos_diff
#define PARENT RightHandedNeutrinos
  START_MODEL
  DEFINEPARS(M_1, delta_M21, M_3, ReOm23, ImOm23, ReOm13, ImOm13, ReOm12, ImOm12, Rorder)
  INTERPRET_AS_PARENT_FUNCTION(RightHandedNeutrinos_diff_to_RightHandedNeutrinos)
#undef PARENT
#undef MODEL

#endif
