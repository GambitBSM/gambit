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

#include "solo_cli.hpp"

#include "gambit/cmake/cmake_variables.hpp"

#include "yaml-cpp/yaml.h"

#include <getopt.h>

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloCLI
    {
      namespace
      {
        const char* analysis_info_dir()
        {
          return GAMBIT_DIR "/ColliderBit/src/analyses";
        }

        std::string to_lower(std::string value)
        {
          std::transform(value.begin(), value.end(), value.begin(),
                         [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
          return value;
        }

        std::string analysis_name_from_info_path(const fs::path& path)
        {
          std::string stem = path.stem().string();
          const std::string prefix = "Analysis_";
          if (stem.compare(0, prefix.size(), prefix) == 0)
          {
            stem.erase(0, prefix.size());
          }
          return stem;
        }

        std::string format_yaml_value(const YAML::Node& node)
        {
          if (!node || node.IsNull()) return {};
          if (node.IsScalar()) return node.Scalar();
          if (node.IsSequence())
          {
            std::ostringstream joined;
            bool first = true;
            for (const auto& item : node)
            {
              if (!item || !item.IsScalar()) continue;
              if (!first) joined << "; ";
              first = false;
              joined << item.Scalar();
            }
            return joined.str();
          }
          return {};
        }

        struct AnalysisRecord
        {
          std::string name;
          std::string path;
          std::map<std::string, std::string> fields;
        };

        std::string field(const AnalysisRecord& record, const char* key)
        {
          const auto it = record.fields.find(key);
          if (it == record.fields.end()) return {};
          return it->second;
        }

        bool passes_validation_policy(const AnalysisRecord& record)
        {
          const std::string validation = field(record, "Validation");
          return validation.empty() || to_lower(validation) == "passed";
        }

        bool matches_query(const std::string& query, const AnalysisRecord& record)
        {
          if (query.empty()) return true;
          const std::string needle = to_lower(query);
          auto contains = [&needle](const std::string& haystack) {
            return to_lower(haystack).find(needle) != std::string::npos;
          };
          if (contains(record.name)) return true;
          static const char* searchable[] = {
            "Summary", "OldName", "ExptRun", "Keywords", "Signatures",
            "Authors", "Note", "Validation", "InspireID"
          };
          for (const char* key : searchable)
          {
            if (contains(field(record, key))) return true;
          }
          return false;
        }

        bool load_analysis_records(std::vector<AnalysisRecord>& records, std::ostream& errors)
        {
          const fs::path info_dir(analysis_info_dir());
          if (!fs::exists(info_dir) || !fs::is_directory(info_dir))
          {
            errors << "CBS analysis metadata directory was not found:\n  "
                   << info_dir.string() << std::endl;
            return false;
          }

          for (const auto& entry : fs::directory_iterator(info_dir))
          {
            if (!fs::is_regular_file(entry.path())) continue;
            if (entry.path().extension() != ".info") continue;

            AnalysisRecord record;
            record.path = entry.path().string();
            record.name = analysis_name_from_info_path(entry.path());
            try
            {
              // Copy-initialise. yaml-cpp 0.6.2 Node assignment merges
              // documents, so a stored Node plus std::sort/swap scrambles
              // metadata across analyses.
              const YAML::Node root = YAML::LoadFile(record.path);
              if (root && root.IsMap())
              {
                for (const auto& kv : root)
                {
                  if (!kv.first.IsScalar()) continue;
                  record.fields[kv.first.Scalar()] = format_yaml_value(kv.second);
                }
              }
            }
            catch (const YAML::Exception& e)
            {
              errors << "Skipping unreadable analysis metadata " << record.path
                     << " (yaml-cpp error: " << e.what() << ")\n";
              continue;
            }
            records.push_back(std::move(record));
          }

          std::sort(records.begin(), records.end(),
                    [](const AnalysisRecord& a, const AnalysisRecord& b) {
                      return a.name < b.name;
                    });
          return true;
        }

        void print_compact_table(std::ostream& output, const std::vector<AnalysisRecord>& records)
        {
          output << std::left
                 << std::setw(36) << "Name"
                 << std::setw(12) << "ExptRun"
                 << std::setw(10) << "Ecm_TeV"
                 << std::setw(10) << "Lumi_ifb"
                 << std::setw(12) << "InspireID"
                 << "Summary\n";
          output << std::string(110, '-') << '\n';
          for (const AnalysisRecord& record : records)
          {
            std::string summary = field(record, "Summary");
            if (summary.size() > 70) summary = summary.substr(0, 67) + "...";
            output << std::left
                   << std::setw(36) << record.name
                   << std::setw(12) << field(record, "ExptRun")
                   << std::setw(10) << field(record, "Ecm_TeV")
                   << std::setw(10) << field(record, "Lumi_ifb")
                   << std::setw(12) << field(record, "InspireID")
                   << summary << '\n';
          }
        }

        void print_full_record(std::ostream& output, const AnalysisRecord& record)
        {
          output << record.name << '\n';
          static const char* ordered_keys[] = {
            "Summary", "InspireID", "ExptRun", "Ecm_TeV", "Lumi_ifb",
            "Signatures", "Keywords", "Authors", "OldName", "Note", "Validation"
          };

          auto print_key = [&](const std::string& key, const std::string& value) {
            if (value.empty()) return;
            output << "  " << std::left << std::setw(12) << key << ": " << value << '\n';
          };

          std::vector<std::string> seen;
          for (const char* key : ordered_keys)
          {
            print_key(key, field(record, key));
            seen.emplace_back(key);
          }
          for (const auto& kv : record.fields)
          {
            if (std::find(seen.begin(), seen.end(), kv.first) != seen.end()) continue;
            print_key(kv.first, kv.second);
          }
          output << "  " << std::left << std::setw(12) << "File" << ": " << record.path << '\n';
        }
      }

      void print_usage(std::ostream& output, const std::string& program_name)
      {
        output
          << "\nUsage: " << program_name << " [options] <CBS YAML file>\n"
          << "       " << program_name << " --list-analyses [query]\n"
          << "\nOptions:\n"
          << "  -h, --help                   Display this usage information\n"
          << "  -l, --list-analyses [query]  List validation-approved ColliderBit analyses from .info metadata\n"
          << std::endl;
      }

      bool print_analysis_list(std::ostream& output, std::ostream& errors, const std::string& query)
      {
        std::vector<AnalysisRecord> records;
        if (!load_analysis_records(records, errors)) return false;

        std::vector<AnalysisRecord> matched;
        matched.reserve(records.size());
        for (AnalysisRecord& record : records)
        {
          if (passes_validation_policy(record) && matches_query(query, record))
          {
            matched.push_back(std::move(record));
          }
        }

        if (matched.empty())
        {
          if (query.empty())
          {
            output << "No ColliderBit analyses pass the validation policy.\n";
            return true;
          }
          errors << "No validation-approved ColliderBit analyses matched";
          if (!query.empty()) errors << " '" << query << "'";
          errors << ".\n";
          return false;
        }

        output << "CBS analyses: " << matched.size();
        if (!query.empty()) output << " matching '" << query << "'";
        output << " (from " << analysis_info_dir() << ")\n\n";

        if (query.empty())
        {
          print_compact_table(output, matched);
          output << "\nUse --list-analyses <name> for full .info metadata.\n";
        }
        else
        {
          for (std::size_t i = 0; i < matched.size(); ++i)
          {
            if (i != 0) output << '\n';
            print_full_record(output, matched[i]);
          }
        }
        return true;
      }

      CommandLineStatus parse_command_line(
        int argc,
        char* argv[],
        CommandLineOptions& options
      )
      {
        const struct option command_line_options[] = {
          {"help", no_argument, 0, 'h'},
          {"list-analyses", no_argument, 0, 'l'},
          {0, 0, 0, 0}
        };

        // CBS is currently the only parser in this process. Reset getopt's
        // state explicitly so the helper remains safe to call more than once.
        optind = 1;
        opterr = 0;

        int option_index = 0;
        int option = 0;
        bool list_analyses = false;
        while ((option = getopt_long(argc, argv, "hl", command_line_options, &option_index)) != -1)
        {
          switch (option)
          {
            case 'h':
              print_usage(std::cout, argv[0]);
              return CommandLineStatus::help;

            case 'l':
              list_analyses = true;
              break;

            case '?':
            default:
              std::cerr << "Unknown or malformed CBS command-line option.\n";
              print_usage(std::cerr, argv[0]);
              return CommandLineStatus::error;
          }
        }

        if (list_analyses)
        {
          if (argc - optind > 1)
          {
            std::cerr << "Expected at most one analysis query with --list-analyses.\n";
            print_usage(std::cerr, argv[0]);
            return CommandLineStatus::error;
          }
          if (optind < argc) options.analysis_query = argv[optind];
          return CommandLineStatus::list_analyses;
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
