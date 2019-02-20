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
   START_FUNCTION(dq)
   DEPENDENCY(CPV_Wilson_Coeff_q, CPV_WC_q)
   DEPENDENCY(SMINPUTS, SMInputs)
   #undef FUNCTION
#undef CAPABILITY

#define CAPABILITY CEDM_q
START_CAPABILITY
   #define FUNCTION CEDM_q_Wilson
   START_FUNCTION(dq)
   DEPENDENCY(CPV_Wilson_Coeff_q, CPV_WC_q)
   DEPENDENCY(SMINPUTS, SMInputs)
   #undef FUNCTION
#undef CAPABILITY

#undef MODULE

#endif
