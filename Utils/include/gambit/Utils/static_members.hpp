//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Initialisation of static member variables in 
///  utility classes.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott 
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __static_members_hpp__
#define __static_members_hpp__

#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/Utils/exceptions.hpp"

// This header *defines* static members, so it must contribute them from exactly
// one translation unit per executable (the main program TU).  Translation units
// that need the in-core rollcall macros but must not define the static members
// (e.g. the per-Bit link-time registration TUs, which link alongside the main
// gambit TU) define GAMBIT_NO_STATIC_MEMBER_DEFINITIONS before including this.
#ifndef GAMBIT_NO_STATIC_MEMBER_DEFINITIONS

namespace Gambit
{

  /// Pointer to chosen random number generation engine
  Utils::threadsafe_rng* Random::local_rng = NULL;

  /// Shared string indicating the current values of the paramters.
  str exception::parameters = "";

}

#endif //#ifndef GAMBIT_NO_STATIC_MEMBER_DEFINITIONS

#endif //#ifndef __static_members_hpp__

