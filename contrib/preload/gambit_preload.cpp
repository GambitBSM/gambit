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
///  \author Pengxuan Zhu
///          pengxuan.zhu@adelaide.edu.au
///  \date 2026 Aug
///
///  *********************************************

#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef __APPLE__
  #include <crt_externs.h>
#endif

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Core/cli_help_text.hpp"
#include "gambit/Utils/stringify.hpp"


// Classify the current invocation from argv.
//
// Used by the constructor below to short-circuit trivial GAMBIT flag-only
// invocations (--help, -h, --version, no-args) before the main binary's C++
// static initialisers run, saving several seconds of startup on e.g.
// `./gambit --help`.
//
// CBS has its own CLI. Its -h/--help/-l/--list-analyses paths must reach
// main() (not the GAMBIT help text) but should skip "Initialising GAMBIT..."
// and silence RestFrames' load-time banner.
typedef enum
{
  GAMBIT_INVOCATION_NORMAL  = 0,
  GAMBIT_INVOCATION_HELP    = 1,  // GAMBIT --help, -h, or no arguments
  GAMBIT_INVOCATION_VERSION = 2,  // --version
  GAMBIT_INVOCATION_LIGHT   = 3   // CBS help/list: continue to main(), quietly
} gambit_invocation_kind;

static const char* gambit_basename(const char* path)
{
  const char* base = path;
  if (path == NULL) return "";
  for (const char* p = path; *p != '\0'; ++p)
  {
    if (*p == '/') base = p + 1;
  }
  return base;
}

static int gambit_is_cbs(const char* argv0)
{
  return strcmp(gambit_basename(argv0), "CBS") == 0;
}

static gambit_invocation_kind gambit_classify_from_args(int argc, char** argv)
{
  if (argc < 1 || argv == NULL || argv[0] == NULL) return GAMBIT_INVOCATION_NORMAL;

  const int cbs = gambit_is_cbs(argv[0]);
  if (argc == 1)
  {
    return cbs ? GAMBIT_INVOCATION_LIGHT : GAMBIT_INVOCATION_HELP;
  }

  for (int i = 1; i < argc; ++i)
  {
    const char* arg = argv[i];
    if (arg == NULL) continue;
    if (cbs)
    {
      if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0 ||
          strcmp(arg, "-l") == 0 || strcmp(arg, "--list-analyses") == 0)
      {
        return GAMBIT_INVOCATION_LIGHT;
      }
    }
    else
    {
      if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0)
        return GAMBIT_INVOCATION_HELP;
      if (strcmp(arg, "--version") == 0)
        return GAMBIT_INVOCATION_VERSION;
    }
  }
  return GAMBIT_INVOCATION_NORMAL;
}

static gambit_invocation_kind gambit_classify_invocation()
{
#ifdef __APPLE__
  return gambit_classify_from_args(*_NSGetArgc(), *_NSGetArgv());
#elif defined(__linux__)
  static char buf[4096];
  static char* argv[256];
  FILE* f = fopen("/proc/self/cmdline", "r");
  if (f == NULL) return GAMBIT_INVOCATION_NORMAL;
  size_t n = fread(buf, 1, sizeof(buf) - 1, f);
  fclose(f);
  if (n == 0) return GAMBIT_INVOCATION_NORMAL;
  buf[n] = '\0';
  int argc = 0;
  size_t i = 0;
  while (i < n && argc < 255)
  {
    argv[argc++] = &buf[i];
    while (i < n && buf[i] != '\0') ++i;
    ++i;
  }
  argv[argc] = NULL;
  return gambit_classify_from_args(argc, argv);
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

  // Trivial GAMBIT flag-only invocations (--help, -h, --version, no-args)
  // don't need anything else GAMBIT does at startup, so print the
  // appropriate output and exit *here*, before the dynamic loader
  // hands control to the executable's .init_array.
  //
  // argv is read from /proc/self/cmdline on Linux and from _NSGetArgv on
  // Darwin. The fast-paths in main() and run_diagnostic remain as a
  // safety net on other systems.
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
    if (kind == GAMBIT_INVOCATION_LIGHT)
    {
      // CBS --help / --list-analyses: RestFrames is linked, but its constructor
      // banner is not useful for these paths. libRestFrames depends on this
      // preload, so this setenv runs first.
      setenv("RESTFRAMES_QUIET", "1", 1);
    }
    else if (kind == GAMBIT_INVOCATION_NORMAL)
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
