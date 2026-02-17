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
#include <cstdio>
#include <cstring>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/stringify.hpp"


namespace
{
  bool env_flag_enabled(const char* value)
  {
    if (value == NULL) return false;
    if (strcmp(value, "1") == 0) return true;
    if (strcmp(value, "true") == 0) return true;
    if (strcmp(value, "TRUE") == 0) return true;
    if (strcmp(value, "yes") == 0) return true;
    if (strcmp(value, "YES") == 0) return true;
    if (strcmp(value, "on") == 0) return true;
    if (strcmp(value, "ON") == 0) return true;
    return false;
  }
}

// Initializer; runs as soon as this library is loaded.
__attribute__((constructor))
static void initializer()
{
  const bool suppress_banner = env_flag_enabled(getenv("GAMBIT_SUPPRESS_BANNER"));
  if (!suppress_banner)
  {
    printf("%s", "\n\x1b[1;33mGAMBIT " STRINGIFY(GAMBIT_VERSION_MAJOR) "." STRINGIFY(GAMBIT_VERSION_MINOR) "." STRINGIFY(GAMBIT_VERSION_REVISION));
    if (strcmp(GAMBIT_VERSION_PATCH, "") != 0) printf("%s", "-" GAMBIT_VERSION_PATCH);
    printf("\nhttp://gambitbsm.org\n\n\x1b[0m");
  }
  #ifndef EXCLUDE_RESTFRAMES
  {
    const char* oldenv = getenv("CPLUS_INCLUDE_PATH");
    const char* addition = (oldenv == NULL ? RESTFRAMES_INCLUDE : ":" RESTFRAMES_INCLUDE);
    if (oldenv != NULL)
    {
      char* newenv = (char*) malloc((strlen(oldenv) + strlen(addition) + 1) * sizeof(char));
      strcpy(newenv, oldenv);
      strcat(newenv, addition);
      setenv("CPLUS_INCLUDE_PATH", newenv, 1);
      free(newenv);
    }
    else setenv("CPLUS_INCLUDE_PATH", addition, 1);
  }
  #endif

}
