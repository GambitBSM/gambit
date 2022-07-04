//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Modifier functions for the total scan lnlike
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Feb
///
///  *********************************************

#ifndef __lnlike_modifiers_hpp__
#define __lnlike_modifiers_hpp__

#include "gambit/Utils/util_types.hpp" 
#include "gambit/Utils/yaml_options.hpp" 

namespace Gambit
{
  namespace Utils
  {

    /// Interface function that calls the correct modifier function based on the name in lnlike_modifier_name
    double run_lnlike_modifier(double lnlike, const str& lnlike_modifier_name, const Options& lnlike_modifier_options);

    /// lnlike modifier: gaussian
    double lnlike_modifier_gaussian(double lnlike, const Options& lnlike_modifier_options);

    /// lnlike modifier: gaussian_plateau
    double lnlike_modifier_gaussian_plateau(double lnlike, const Options& lnlike_modifier_options);

  }
}

#endif //defined __lnlike_modifiers_hpp__
