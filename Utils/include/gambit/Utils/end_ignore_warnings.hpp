//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple header file for turning compiler 
///  warnings back on after having included
///  one of the begin_ignore_warnings_*.hpp files.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Jul
///
///  *********************************************


// SUPPRESS_LIBRARY_WARNINGS is defined by gambit/cmake/cmake_variables.hpp
// which will have been included by the begin_ignore_warnings_*.hpp file.
#ifdef SUPPRESS_LIBRARY_WARNINGS

  // GCC:
  #ifdef __GNUC__
    // Turn warnings back on
    #pragma GCC diagnostic pop
  #endif

  // Clang:
  #ifdef __clang__
    #ifndef __ICC
      // Turn warnings back on
      #pragma clang diagnostic pop
    #endif
  #endif
  
#endif
