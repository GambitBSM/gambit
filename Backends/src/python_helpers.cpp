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


namespace Gambit
{

  namespace Backends
  {

    /// Helper functions to cast void result of python functions to voids for returning from the python_function object.
    template <>
    void return_cast<void>(pybind11::object o) { return static_cast<void>(o); }

  }

}

#endif