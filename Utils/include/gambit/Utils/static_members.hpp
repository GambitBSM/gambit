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

namespace Gambit
{

  /// Pointer to chosen random number generation engine
  Utils::threadsafe_rng* Random::local_rng = NULL;

  /// Shared string indicating the current values of the paramters.
  str exception::parameters = "";

}

#endif //#ifndef __static_members_hpp__

