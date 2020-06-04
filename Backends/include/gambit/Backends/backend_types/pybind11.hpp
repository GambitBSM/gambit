//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Wrappers of pybind11 types
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  
/// \author Tomas Gonzalo
///         (tomas.gonzalo@monash.edu)
/// \date 2020 June
///
///  *********************************************

#include "gambit/Utils/util_types.hpp"
#include "gambit/cmake/cmake_variables.hpp"

#ifdef HAVE_PYBIND11
  #include <pybind11/pybind11.h>
#endif

#ifndef __pybind11_types_hpp__
#define __pybind11_types_hpp__

namespace Gambit
{

  /// Types used for Python backends
  // TODO: This might be temporary as the harvesting scripts should make this unneccesary
  #ifdef HAVE_PYBIND11
    typedef pybind11::dict PyDict;
  #else
    typedef char PyDict;
  #endif

}

#endif // defined __pybind11_types_hpp__
