//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Top-level CLI usage text for the gambit executable.
///
///  Defined once here and consumed both by Gambit::gambit_core::bail()
///  in Core/src/core.cpp and by the preload library's
///  __attribute__((constructor)) in contrib/preload/gambit_preload.cpp,
///  which intercepts trivial flag-only invocations (--help, -h,
///  --version, no args) and exits before the main binary's C++ static
///  initialisers run.
///
///  *********************************************

#ifndef __gambit_cli_help_text_hpp__
#define __gambit_cli_help_text_hpp__

namespace Gambit
{

  inline constexpr const char* cli_help_text =
      "\nusage: gambit [options] [<command>]                                        "
      "\n                                                                           "
      "\nRun scan:                                                                  "
      "\n   gambit -f <inifile>   Start a scan using instructions from inifile      "
      "\n                           e.g.: gambit -f gambit.yaml                     "
      "\n                                                                           "
      "\nAvailable commands:                                                        "
      "\n   modules               List registered modules                           "
      "\n   backends              List registered backends and their status         "
      "\n   models                List registered models and output model graph     "
      "\n   capabilities          List all registered function capabilities         "
      "\n   scanners              List registered scanners                          "
      "\n   test-functions        List registered scanner test objective functions  "
      "\n   <name>                Give info on a specific module, module function,  "
      "\n                           backend, backend function, model, capability,   "
      "\n                           scanner or scanner test objective function      "
      "\n                           e.g.: gambit DarkBit                            "
      "\n                                 gambit GA_SimYieldTable_DarkSUSY          "
      "\n                                 gambit Pythia                             "
      "\n                                 gambit get_abund_map_AlterBBN             "
      "\n                                 gambit MSSM                               "
      "\n                                 gambit IC79WL_loglike                     "
      "\n                                 gambit MultiNest                          "
      "\n                                                                           "
      "\nBasic options:                                                             "
      "\n   --version             Display GAMBIT version information                "
      "\n   -h/--help             Display this usage information                    "
      "\n   -f <inifile>          Start scan using <inifile>                        "
      "\n   -v/--verbose          Turn on verbose mode                              "
      "\n   -d/--dryrun           List the function evaluation order computed based "
      "\n                           on inifile                                      "
      "\n   -b/--backends         List the backends required to fulfil dependencies "
      "\n                           based on inifile                                "
      "\n   -r/--restart          Restart the scan defined by <inifile>. Existing   "
      "\n                         output files for the run will be overwritten.     "
      "\n                         Default behaviour in the absence of this option is"
      "\n                         to attempt to resume the scan from any existing   "
      "\n                         output.                                           "
      "\n\n\n";

}

#endif // defined __gambit_cli_help_text_hpp__