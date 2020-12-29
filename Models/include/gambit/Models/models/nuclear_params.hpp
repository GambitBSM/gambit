//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Nuclear parameters model definitions
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Jonathan Cornell
//  2015 March, 2019 Feb
//
//  Dimitrios Skodras
//  2019 Mar
//
//  *********************************************

#ifndef __nuclear_params_hpp__
#define __nuclear_params_hpp__

// Forward declaration of needed types
namespace Gambit
{
  struct SMInputs;
}

// Explicitly defined hadronic matrix elements. deltaq are the
// spin content of the proton.
#define MODEL nuclear_params_fnq
  START_MODEL
  DEFINEPARS(fpd, fpu, fps, fnd, fnu, fns)
  DEFINEPARS(deltad, deltau, deltas)
#undef MODEL

// sigma0 and sigmal used to calculate hadronic matrix elements
#define MODEL nuclear_params_sigma0_sigmal
#define PARENT nuclear_params_fnq
  START_MODEL
  DEFINEPARS(sigma0, sigmal)
  DEFINEPARS(deltad, deltau, deltas)
  INTERPRET_AS_PARENT_FUNCTION(sigma0_sigmal_to_fnq)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

// sigmas and sigmal used to calculate hadronic matrix elements
#define MODEL nuclear_params_sigmas_sigmal
#define PARENT nuclear_params_sigma0_sigmal
  START_MODEL
  DEFINEPARS(sigmas, sigmal)
  DEFINEPARS(deltad, deltau, deltas)
  INTERPRET_AS_PARENT_FUNCTION(sigmas_to_sigma0)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

// Neutron EDM matrix elements
#define MODEL nEDMme
  START_MODEL
  // EDM matrix elements (MSbar at 2 GeV)
  DEFINEPARS(gTu, gTd, gTs)
  // chromoEDM matrix elements
  DEFINEPARS(rhoU, rhoD)
#undef MODEL

// diamagnetic EDM matrix elements
#define MODEL diaEDMme
  START_MODEL
  // Schiff moment parameters a_i, b and Schiff constant for several diamagnetic systems
  DEFINEPARS(a0_Hg,a1_Hg,b_Hg,CSchiff_Hg,ae_Hg)
  DEFINEPARS(a0_Ra,a1_Ra,b_Ra,CSchiff_Ra,ae_Ra)
  DEFINEPARS(a0_Rn,a1_Rn,b_Rn,CSchiff_Rn,ae_Rn)
  DEFINEPARS(a0_Xe,a1_Xe,b_Xe,CSchiff_Xe,ae_Xe)
#undef MODEL

#define MODEL TESTMODel
	START_MODEL
	DEFINEPARS(a0)
#undef MODEL

#endif /* __nuclear_params_hpp__ */
