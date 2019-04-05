//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementations of helper functions for
///  python_function and python_variable
///  classes.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************

#include "gambit/cmake/cmake_variables.hpp"

#ifdef HAVE_PYBIND11

#include "gambit/Backends/python_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{

  namespace Backends
  {

    /// Helper functions to cast void result of python functions to voids for returning from the python_function object.
    template <>
    void return_cast<void>(pybind11::object o) { return static_cast<void>(o); }

    /// Takes a function or variable name as a full path within a package, and returns the path to the containing submodule
    /// and the bare name of the function or variable.  Returns an empty string for the path when the function or variable
    /// is not inside a submodule.
    sspair split_qualified_python_name(str s, str m)
    {
      std::vector<str> split_s = Utils::delimiterSplit(s, ".");
      s = "";
      if (split_s.size() > 1)
      {
        s = m;
        for (auto it = split_s.begin(); it != split_s.end() - 1; ++it) s = s + "." + *it;
      }
      sspair test = sspair(s, *(split_s.end() - 1));
      return sspair(s, *(split_s.end() - 1));
    }

  }

}

#endif