//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT routines that must run before
///  anything else.  Beware that these may even
///  run before static object initialisation!
///
///  *********************************************
///
///  Authors:
///
///  \author Pat Scott
///          p.scott@imperial.ac.uk
///  \date 2019 June, July
///
///  \author Anders Kvellestad
///          anders.kvellestad@fys.uio.no
///  \date 2023 Oct
///
///  *********************************************

#include <cstdlib>
#include <string>
#include <iostream>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/stringify.hpp"

// Initializer; runs as soon as this library is loaded.
__attribute__((constructor))
static void initializer()
{
  std::cout << "\n\x1b[1;33mGAMBIT " << STRINGIFY(GAMBIT_VERSION_MAJOR) << "." << STRINGIFY(GAMBIT_VERSION_MINOR) << "." << STRINGIFY(GAMBIT_VERSION_REVISION);
  if (std::string(GAMBIT_VERSION_PATCH) != "") std::cout << "-" << GAMBIT_VERSION_PATCH;
  std::cout << "\nhttp://gambitbsm.org\n\n\x1b[0m";

  #ifndef EXCLUDE_RESTFRAMES
  {
    const char* oldenv = getenv("CPLUS_INCLUDE_PATH");
    std::string newenv;
    if (oldenv != NULL)
    {
      newenv = std::string(oldenv);
      newenv += ":";
    }
    newenv += RESTFRAMES_INCLUDE;
    setenv("CPLUS_INCLUDE_PATH", newenv.c_str(), 1);
  }
  #endif
}
