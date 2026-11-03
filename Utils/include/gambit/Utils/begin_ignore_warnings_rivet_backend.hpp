//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Pragma directives to suppress compiler warnings
///  from headers included via the Rivet backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2023 Feb
///
///  *********************************************


#include "gambit/cmake/cmake_variables.hpp"

#ifdef SUPPRESS_LIBRARY_WARNINGS

  // GCC:
  // clang also depfines __GNUC__ so make sure it is only GCC
  #if defined(__GNUC__) && !defined(__clang__)
    // Save diagnostic state
    #pragma GCC diagnostic push 
    // Don't care if an old compiler version doesn't recognize all the pragmas
    #pragma GCC diagnostic ignored "-Wpragmas"
    // Turn off some warnings
    #pragma GCC diagnostic ignored "-Wdeprecated-copy"
    #pragma GCC diagnostic ignored "-Wignored-qualifiers"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
  #endif

  // Clang:
  // icpc apparently also defines __clang__ 
  #if defined(__clang__) && !defined(__ICC)
    // Save diagnostic state
    #pragma clang diagnostic push 
    // Don't care if an old compiler version doesn't recognize all the pragmas
    #pragma clang diagnostic ignored "-Wpragmas"
    // Turn off some warnings
    #pragma clang diagnostic ignored "-Wdeprecated-copy"
    #pragma clang diagnostic ignored "-Wignored-qualifiers"
    #pragma clang diagnostic ignored "-Wunused-parameter"
  #endif

#endif
