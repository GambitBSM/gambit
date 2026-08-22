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


// Classify the current GAMBIT invocation from argv. This library is also
// linked into contributed-package test programs, so CLI handling must run only
// for the actual GAMBIT executable.
typedef enum
{
  GAMBIT_INVOCATION_NORMAL  = 0,
  GAMBIT_INVOCATION_HELP    = 1,  // GAMBIT --help, -h, or no arguments
  GAMBIT_INVOCATION_VERSION = 2,  // --version
  GAMBIT_INVOCATION_EXTERNAL = 3  // A non-GAMBIT process linked to this library
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

static int gambit_is_main_executable(const char* argv0)
{
  return strcmp(gambit_basename(argv0), GAMBIT_EXECUTABLE) == 0;
}

static gambit_invocation_kind gambit_classify_from_args(int argc, char** argv)
{
  if (argc < 1 || argv == NULL || argv[0] == NULL) return GAMBIT_INVOCATION_EXTERNAL;
  if (!gambit_is_main_executable(argv[0])) return GAMBIT_INVOCATION_EXTERNAL;
  if (argc == 1) return GAMBIT_INVOCATION_HELP;

  for (int i = 1; i < argc; ++i)
  {
    const char* arg = argv[i];
    if (arg == NULL) continue;
    if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0)
      return GAMBIT_INVOCATION_HELP;
    if (strcmp(arg, "--version") == 0)
      return GAMBIT_INVOCATION_VERSION;
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
  if (f == NULL) return GAMBIT_INVOCATION_EXTERNAL;
  size_t n = fread(buf, 1, sizeof(buf) - 1, f);
  fclose(f);
  if (n == 0) return GAMBIT_INVOCATION_EXTERNAL;
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
  // The normal GAMBIT main() path remains available on platforms where this
  // preload cannot inspect argv.  Do not apply GAMBIT CLI behaviour to every
  // executable that happens to link this library.
  return GAMBIT_INVOCATION_EXTERNAL;
#endif
}


// Initializer; runs as soon as this library is loaded.
__attribute__((constructor))
static void initializer()
{
  const gambit_invocation_kind kind = gambit_classify_invocation();
  if (kind != GAMBIT_INVOCATION_EXTERNAL)
  {
    // Print GAMBIT startup message only for GAMBIT itself.
    printf("%s", "\n\x1b[1;33mGAMBIT " STRINGIFY(GAMBIT_VERSION_MAJOR) "." STRINGIFY(GAMBIT_VERSION_MINOR) "." STRINGIFY(GAMBIT_VERSION_REVISION));
    if (strcmp(GAMBIT_VERSION_PATCH, "") != 0) printf("%s", "-" GAMBIT_VERSION_PATCH);
    printf("\nhttp://gambitbsm.org\n\n\x1b[0m");

    // Trivial GAMBIT flag-only invocations (--help, -h, --version, no-args)
    // don't need anything else GAMBIT does at startup, so print the
    // appropriate output and exit *here*, before the dynamic loader
    // hands control to the executable's .init_array.
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
