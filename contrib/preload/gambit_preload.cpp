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
///  \date 2026 May
///
///  *********************************************

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Core/cli_help_text.hpp"
#include "gambit/Utils/stringify.hpp"


// Classify the current gambit invocation by inspecting /proc/self/cmdline.
// Used by the constructor below to short-circuit trivial flag-only invocations
// (--help, -h, --version, no-args) before the main binary's C++ static
// initialisers run, saving several seconds of startup on e.g. `./gambit --help`.
//
// Detection is Linux-only (/proc/self/cmdline). On other systems this returns
// "normal" and the existing fast-paths in main()/run_diagnostic still cover
// the trivial invocations, just a bit slower.
typedef enum
{
  GAMBIT_INVOCATION_NORMAL  = 0,
  GAMBIT_INVOCATION_HELP    = 1,  // --help, -h, or no arguments at all
  GAMBIT_INVOCATION_VERSION = 2,  // --version
} gambit_invocation_kind;

static gambit_invocation_kind gambit_classify_invocation()
{
#ifdef __linux__
  FILE* f = fopen("/proc/self/cmdline", "r");
  if (f == NULL) return GAMBIT_INVOCATION_NORMAL;
  char buf[4096];
  size_t n = fread(buf, 1, sizeof(buf) - 1, f);
  fclose(f);
  if (n == 0) return GAMBIT_INVOCATION_NORMAL;
  buf[n] = '\0';
  // Step past argv[0] (the executable path).
  size_t i = 0;
  while (i < n && buf[i] != '\0') ++i;
  ++i;
  // No further arguments: print usage like `./gambit --help` does.
  if (i >= n) return GAMBIT_INVOCATION_HELP;
  // Walk argv looking for the first matching trivial flag, mirroring
  // getopt's left-to-right parse order.
  while (i < n)
  {
    const char* arg = &buf[i];
    if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0)
      return GAMBIT_INVOCATION_HELP;
    if (strcmp(arg, "--version") == 0)
      return GAMBIT_INVOCATION_VERSION;
    while (i < n && buf[i] != '\0') ++i;
    ++i;
  }
  return GAMBIT_INVOCATION_NORMAL;
#else
  return GAMBIT_INVOCATION_NORMAL;
#endif
}


// Initializer; runs as soon as this library is loaded.
__attribute__((constructor))
static void initializer()
{
  // Print GAMBIT startup message
  printf("%s", "\n\x1b[1;33mGAMBIT " STRINGIFY(GAMBIT_VERSION_MAJOR) "." STRINGIFY(GAMBIT_VERSION_MINOR) "." STRINGIFY(GAMBIT_VERSION_REVISION));
  if (strcmp(GAMBIT_VERSION_PATCH, "") != 0) printf("%s", "-" GAMBIT_VERSION_PATCH);
  printf("\nhttp://gambitbsm.org\n\n\x1b[0m");

  // Trivial flag-only invocations (--help, -h, --version, no-args) 
  // don't need anything else GAMBIT does at startup, so print the 
  // appropriate output and exit *here*, before the dynamic loader 
  // hands control to the executable's .init_array. 
  //
  // The fast-paths in main() and run_diagnostic remain in place
  // as a safety net for non-Linux systems where /proc/self/cmdline
  // isn't available.
  {
    const gambit_invocation_kind kind = gambit_classify_invocation();
    if (kind == GAMBIT_INVOCATION_HELP)
    {
      fputs(Gambit::cli_help_text, stdout);
      exit(0);
    }
    if (kind == GAMBIT_INVOCATION_VERSION)
    {
      // The banner above is the version output; no further text needed.
      exit(0);
    }
    if (kind == GAMBIT_INVOCATION_NORMAL)
    {
      // Normal GAMBIT invocation usually takes a few seconds of startup
      // time, so let's inform the user that we are working on it.
      printf("Initialising GAMBIT...\n");
    }
  }


  // Set environment variable for RestFrames
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

  // Set environment variable for HDF5
  setenv("HDF5_USE_FILE_LOCKING", "FALSE", 1);
}
