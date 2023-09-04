//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Version command
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Apr
///
///  *********************************************

#include "gambit/Utils/version.hpp"

namespace Gambit
{

  /// Construct a string containing the full GAMBIT version information.
  str get_gambit_version()
  {
    std::ostringstream ss;
    ss << gambit_version_major << "." << gambit_version_minor << "." << gambit_version_revision;
    if (!gambit_version_patch.empty()) ss << "-" << gambit_version_patch;
    return ss.str();
  }

  /// Statically construct a string containing the full GAMBIT version information and return a reference to it.
  str& gambit_version()
  {
    static str local = get_gambit_version();
    return local;
  }

}

