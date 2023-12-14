//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Defines the python module to be used in the
///  python plugins.
///
///  *********************************************
///
///  Authors:
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2023 Dec
///
///  *********************************************

#pragma once

#include "gambit/cmake/cmake_variables.hpp"

#ifdef HAVE_PYBIND11

#include <unordered_map>
#include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include <pybind11/embed.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "gambit/Utils/end_ignore_warnings.hpp"

#include "gambit/ScannerBit/factory_defs.hpp"
#include "gambit/ScannerBit/plugin_defs.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/python_utils.hpp"

namespace py = pybind11;

#include "gambit/ScannerBit/py_module_scanbit.hpp"
#include "gambit/ScannerBit/py_module_scan.hpp"
#include "gambit/ScannerBit/py_module_obj.hpp"

#endif  // HAVE_PYBIND11
