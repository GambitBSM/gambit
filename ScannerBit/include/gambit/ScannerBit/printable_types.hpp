//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Preprocessor sequence of functor types that
///  should be allowed to print when using
///  ScannerBit in standalone mode.  Add to
///  this as necessary.
///
///  *********************************************
///
///  Authors:
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jun
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Feb
///
///  *********************************************

#pragma once

#include <string>
#include <map>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/model_parameters.hpp"


namespace Gambit
{
  // Types that scanner plugins are allowed to print.
  // Covers just basic types, vectors of those types, and
  // a couple of extras needed by scanners.

  // Bool has weird behaviour in vectors, so need a version without bool.
  #define SCANNER_SIMPLE_TYPES_NOBOOL \
    (int)                             \
    (unsigned int)                    \
    (short int)                       \
    (unsigned short int)              \
    (long)                            \
    (unsigned long)                   \
    (long long)                       \
    (unsigned long long)              \
    (float)                           \
    (double)                          \

  #define SCANNER_SIMPLE_TYPES        \
    SCANNER_SIMPLE_TYPES_NOBOOL       \
    (bool)                            \

  #define SCANNER_VECTOR_TYPES        \
    (std::vector<bool>)               \
    (std::vector<int>)                \
    (std::vector<unsigned int>)       \
    (std::vector<short int>)          \
    (std::vector<unsigned short int>) \
    (std::vector<long>)               \
    (std::vector<unsigned long>)      \
    (std::vector<long long>)          \
    (std::vector<unsigned long long>) \
    (std::vector<float>)              \
    (std::vector<double>)

  #define SCANNER_PRINTABLE_TYPES \
    SCANNER_SIMPLE_TYPES          \
    SCANNER_VECTOR_TYPES          \
    (map_str_dbl)                 \
    (map_str_str)                 \
    (Gambit::ModelParameters)     \

  #define SCANNER_RETRIEVABLE_TYPES   \
    SCANNER_SIMPLE_TYPES              \
    (std::string)                     \
    (std::vector<double>)             \
    (map_str_dbl)                     \
    (Gambit::ModelParameters)
}
