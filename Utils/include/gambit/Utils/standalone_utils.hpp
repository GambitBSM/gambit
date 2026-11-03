//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utilities needed to use a GAMBIT
///  module as a standalone analysis code.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott  
///          (patscott@physics.mcgill.ca)
///  \date 2014 Feb
///
///  \author Chris Chang
///  \date 2023 Dec
///
///  *********************************************

#ifndef __standalone_utils_hpp__
#define __standalone_utils_hpp__

#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/yaml_node_utility.hpp"

namespace Gambit
{

  /// Logger setup standalone utility function
  void initialise_standalone_logs(str);

  /// Initialise the printers (required for suspicious point raises)
  YAML::Node get_standalone_printer(str, str, str);

}


#endif //__standalone_utils_hpp__

