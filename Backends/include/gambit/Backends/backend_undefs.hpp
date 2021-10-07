//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Undef backend identification things to prevent
///  clashes with other backends.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Sep
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Sep
///
///  *********************************************

#ifndef BACKEND_SPECIFIC_COMPILE_UNIT
  #undef BACKENDNAME
  #undef BACKENDLANG
  #undef VERSION
  #undef SAFE_VERSION
  #undef REFERENCE
  #undef DO_CLASSLOADING
  #define DO_CLASSLOADING 0
#endif
