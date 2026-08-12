//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Command-line parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_cli.hpp"

#include <getopt.h>

#include <iostream>

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloCLI
    {
      void print_usage(std::ostream& output, const std::string& program_name)
      {
        output
          << "\nUsage: " << program_name << " [options] <CBS YAML file>\n"
          << "\nOptions:\n"
          << "  -h, --help    Display this usage information\n"
          << std::endl;
      }

      CommandLineStatus parse_command_line(
        int argc,
        char* argv[],
        CommandLineOptions& options
      )
      {
        const struct option command_line_options[] = {
          {"help", no_argument, 0, 'h'},
          {0, 0, 0, 0}
        };

        // CBS is currently the only parser in this process. Reset getopt's
        // state explicitly so the helper remains safe to call more than once.
        optind = 1;
        opterr = 0;

        int option_index = 0;
        int option = 0;
        while ((option = getopt_long(argc, argv, "h", command_line_options, &option_index)) != -1)
        {
          switch (option)
          {
            case 'h':
              print_usage(std::cout, argv[0]);
              return CommandLineStatus::help;

            case '?':
            default:
              std::cerr << "Unknown or malformed CBS command-line option.\n";
              print_usage(std::cerr, argv[0]);
              return CommandLineStatus::error;
          }
        }

        if (optind >= argc)
        {
          std::cerr << "Missing CBS YAML file.\n";
          print_usage(std::cerr, argv[0]);
          return CommandLineStatus::error;
        }

        if (argc - optind != 1)
        {
          std::cerr << "Expected exactly one CBS YAML file.\n";
          print_usage(std::cerr, argv[0]);
          return CommandLineStatus::error;
        }

        options.filename = argv[optind];
        return CommandLineStatus::run;
      }
    }
  }
}
