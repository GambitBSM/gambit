//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Command-line parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pengxuan Zhu
///          (pengxuan.zhu@adelaide.edu.au)
///  \date 2026 Aug
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
        list_analyses,
        error
      };

      struct CommandLineOptions
      {
        std::string filename;
        std::string analysis_query;
      };

      /// Print CBS command-line usage information.
      void print_usage(std::ostream& output, const std::string& program_name);

      /// Print ColliderBit analysis metadata from .info files.
      bool print_analysis_list(std::ostream& output, std::ostream& errors, const std::string& query);

      /// Parse CBS command-line arguments.
      CommandLineStatus parse_command_line(
        int argc,
        char* argv[],
        CommandLineOptions& options
      );
    }
  }
}
