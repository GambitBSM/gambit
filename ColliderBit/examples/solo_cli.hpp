//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Command-line parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <iosfwd>
#include <string>

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloCLI
    {
      enum class CommandLineStatus
      {
        run,
        help,
        error
      };

      struct CommandLineOptions
      {
        std::string filename;
      };

      /// Print CBS command-line usage information.
      void print_usage(std::ostream& output, const std::string& program_name);

      /// Parse CBS command-line arguments.
      CommandLineStatus parse_command_line(
        int argc,
        char* argv[],
        CommandLineOptions& options
      );
    }
  }
}
