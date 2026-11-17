//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Access to the run's default_output_path (from the yaml file) for code
///  that has no access to the inifile, e.g. backend frontends.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ida-Marie Fauske Johansson
///  \date 2026 Nov
///
///  *********************************************

#ifndef __output_path_hpp__
#define __output_path_hpp__

#include <string>

namespace Gambit
{
  namespace Utils
  {
    /// Set by the yaml parser. Includes a trailing slash. Empty if never set.
    const std::string& default_output_path();
    void set_default_output_path(const std::string&);
  }
}

#endif
