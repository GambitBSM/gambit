//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for LowEBit.
///
///  Compile-time registration of available
///  observables and likelihoods for (mostly
///  electroweak) precision observables.
///
///  Don't put typedefs or other type definitions
///  in this file; see
///  Core/include/types_rollcall.hpp for further
///  instructions on how to add new types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jonathan.cornell@uc.edu)
///  \date 2019 Jan
///
///  *********************************************

#ifndef __LowEBit_rollcall_hpp__
#define __LowEBit_rollcall_hpp__

#include "gambit/LowEBit/LowEBit_types.hpp"

#define MODULE LowEBit
START_MODULE

// Wilson Coefficients for CPV violating operators as defined
// in 1811.05480 (at mu_had)
#define CAPABILITY CPV_Wilson_Coeff_q
START_CAPABILITY
	// Simple calculation 3.4-3.6 of 1811.05480, ignoring
    // uncertainties
   #define FUNCTION CPV_Wilson_q_Simple
   START_FUNCTION(CPV_WC_q)
   ALLOW_MODELS(CPVYukawas)
   #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY EDM_q
START_CAPABILITY
   #define FUNCTION EDM_q_Wilson
   // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
   START_FUNCTION(dq)
   DEPENDENCY(CPV_Wilson_Coeff_q, CPV_WC_q)
   DEPENDENCY(SMINPUTS, SMInputs)
   #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY CEDM_q
START_CAPABILITY
   #define FUNCTION CEDM_q_Wilson
   // Calculation of quark chromoEDMs (at mu_had) from Wilson Coefficients in cm
   START_FUNCTION(dq)
   DEPENDENCY(CPV_Wilson_Coeff_q, CPV_WC_q)
   DEPENDENCY(SMINPUTS, SMInputs)
   #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY EDM_n // The EDM of the neutron
START_CAPABILITY
   #define FUNCTION EDM_n_quark
   // Calculation of neutron EDM from quark EDMs and CEDMs in e cm
   START_FUNCTION(double)
   DEPENDENCY(SMINPUTS, SMInputs)
   DEPENDENCY(EDM_q, dq)
   DEPENDENCY(CEDM_q, dq)
   ALLOW_MODELS(nEDMme)
   #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY lnL_EDM_n
START_CAPABILITY
   #define FUNCTION lnL_EDM_n_step
   // Step function likelihood for neutron EDM (TODO: improve this!!!!!)
   START_FUNCTION(double)
   DEPENDENCY(EDM_n, double)
   #undef FUNCTION
#undef CAPABILITY

#undef MODULE

#endif
