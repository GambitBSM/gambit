///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Nuclear parameters model definitions
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Jonathan Cornell
///  \date 2015 March
///
///  \author Janina Renk
///  \date 2020 May
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sep
///
///  *********************************************

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


// model for neutron lifetime
#define MODEL nuclear_params_neutron_lifetime
  START_MODEL
  DEFINEPARS(neutron_lifetime)
#undef MODEL

#endif /* __nuclear_params_hpp__ */
