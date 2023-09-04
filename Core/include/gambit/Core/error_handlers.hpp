//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Exception object declarations.
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

#ifndef __error_handlers_hpp__
#define __error_handlers_hpp__

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/local_info.hpp"

namespace Gambit
{

  /// Core errors
  error& core_error();
  /// Core warnings
  warning& core_warning();

  namespace DRes
  {
    /// Dependency resolver errors
    error& dependency_resolver_error();
    /// Dependency resolver warnings
    warning& dependency_resolver_warning();
  }
    
}

#endif //#ifndef error_handlers_hpp

