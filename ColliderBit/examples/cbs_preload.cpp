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

// RestFrames prints from a shared-library constructor, before CBS main().
// This constructor is linked before RestFrames for the CBS target.
__attribute__((constructor))
static void configure_cbs_preload()
{
  setenv("RESTFRAMES_QUIET", "1", 1);
}
