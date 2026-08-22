//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CBS-only load-time setup.  This is deliberately separate from
///  contrib/preload/gambit_preload.cpp: CBS has its own command-line
///  interface and must not change GAMBIT's process-wide CLI behaviour.
///
///  *********************************************
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

namespace
{
  const char* basename(const char* path)
  {
    const char* base = path;
    if (path == nullptr) return "";
    for (const char* p = path; *p != '\0'; ++p)
    {
      if (*p == '/') base = p + 1;
    }
    return base;
  }

  bool is_quiet_cbs_invocation(int argc, char* const* argv)
  {
    if (argc < 1 || argv == nullptr || argv[0] == nullptr) return false;
    if (std::strcmp(basename(argv[0]), "CBS") != 0) return false;
    if (argc == 1) return true;

    for (int i = 1; i < argc; ++i)
    {
      const char* arg = argv[i];
      if (arg == nullptr) continue;
      if (std::strcmp(arg, "-h") == 0 ||
          std::strcmp(arg, "--help") == 0 ||
          std::strcmp(arg, "-l") == 0 ||
          std::strcmp(arg, "--list-analyses") == 0)
      {
        return true;
      }
    }
    return false;
  }

  bool is_quiet_cbs_invocation()
  {
#ifdef __APPLE__
    return is_quiet_cbs_invocation(*_NSGetArgc(), *_NSGetArgv());
#elif defined(__linux__)
    char buffer[4096];
    char* argv[256];
    FILE* cmdline = std::fopen("/proc/self/cmdline", "r");
    if (cmdline == nullptr) return false;
    const size_t size = std::fread(buffer, 1, sizeof(buffer) - 1, cmdline);
    std::fclose(cmdline);
    if (size == 0) return false;
    buffer[size] = '\0';

    int argc = 0;
    size_t position = 0;
    while (position < size && argc < 255)
    {
      argv[argc++] = &buffer[position];
      while (position < size && buffer[position] != '\0') ++position;
      if (position < size) ++position;
    }
    argv[argc] = nullptr;
    return is_quiet_cbs_invocation(argc, argv);
#else
    return false;
#endif
  }
}

// RestFrames prints from a shared-library constructor, before CBS main().
// This constructor is linked before RestFrames for the CBS target.
__attribute__((constructor))
static void configure_cbs_preload()
{
  if (is_quiet_cbs_invocation()) setenv("RESTFRAMES_QUIET", "1", 1);
}
