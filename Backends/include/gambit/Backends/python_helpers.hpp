//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of helper functions for
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

#ifndef __python_helpers_hpp__
#define __python_helpers_hpp__

#include <pybind11/pybind11.h>

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

  namespace Backends
  {

    /// Helper functions to cast results of python functions to the right types for returning from the python_function object.
    /// @{
    template <typename T>
    T return_cast(pybind11::object o) { return o.cast<T>(); }
    template <>
    void return_cast<void>(pybind11::object o);
    /// @}

    /// Takes a function or variable name as a full path within a package, and returns the path to the containing submodule.
    /// Returns an empty string when the function or variable is not inside a submodule.
    sspair split_qualified_python_name(str, str);

  }

}

#endif // defined __python_helpers_hpp__