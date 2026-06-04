//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Input parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_input.hpp"

#include <cmath>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloInput
    {
      namespace
      {
        struct CrossSectionInput
        {
          double xsec_fb = 0.0;
          double xsec_uncert_fb = 0.0;
        };

        bool is_supported_hepmc_file(const str& filename)
        {
          return Gambit::Utils::endsWith(filename, ".hepmc")
                 || Gambit::Utils::endsWith(filename, ".hepmc2")
                 || Gambit::Utils::endsWith(filename, ".hepmc3");
        }

        std::string dirname(const std::string& path)
        {
          const std::size_t slash = path.find_last_of("/\\");
          if (slash == std::string::npos) return ".";
          if (slash == 0) return path.substr(0, 1);
          return path.substr(0, slash);
        }

        std::string source_root_from_this_file()
        {
          const std::string file = __FILE__;
          const std::string marker = "ColliderBit/examples/solo_input.cpp";
          const std::size_t pos = file.rfind(marker);
          if (pos == std::string::npos) return ".";

          std::string root = file.substr(0, pos);
          if (!root.empty() && (root.back() == '/' || root.back() == '\\'))
          {
            root.pop_back();
          }
          return root.empty() ? "." : root;
        }

        YAML::Node merge_yaml_nodes(const YAML::Node& defaults, const YAML::Node& overrides)
        {
          if (!defaults) return YAML::Clone(overrides);
          if (!overrides) return YAML::Clone(defaults);

          if (defaults.IsMap() && overrides.IsMap())
          {
            YAML::Node result = YAML::Clone(defaults);
            for (YAML::const_iterator it = overrides.begin(); it != overrides.end(); ++it)
            {
              const std::string key = it->first.as<std::string>();
              result[key] = merge_yaml_nodes(result[key], it->second);
            }
            return result;
          }

          // Scalars and sequences are replaced as a whole by the user value.
          return YAML::Clone(overrides);
        }

        std::string find_default_settings_file(
          const std::string& input_filename,
          const YAML::Node& user_settings,
          bool& explicit_default_file)
        {
          explicit_default_file = false;

          if (user_settings && user_settings["cbs_defaults_file"])
          {
            explicit_default_file = true;
            return user_settings["cbs_defaults_file"].as<std::string>();
          }

          const char* env_default_file = std::getenv("CBS_DEFAULTS_FILE");
          if (env_default_file != nullptr && std::string(env_default_file).size() > 0)
          {
            explicit_default_file = true;
            return std::string(env_default_file);
          }

          std::vector<std::string> candidates;
          candidates.push_back(dirname(input_filename) + "/CBS_defaults.yaml");
          candidates.push_back(source_root_from_this_file() + "/CBS_yaml/CBS_defaults.yaml");
          candidates.push_back("CBS_yaml/CBS_defaults.yaml");

          for (const std::string& candidate : candidates)
          {
            if (Gambit::Utils::file_exists(candidate)) return candidate;
          }

          return "";
        }

        YAML::Node apply_default_settings(
          const std::string& filename_in,
          const std::vector<str>& analyses,
          const YAML::Node& user_settings)
        {
          if (user_settings && user_settings["use_cbs_defaults"] &&
              !user_settings["use_cbs_defaults"].as<bool>())
          {
            return YAML::Clone(user_settings);
          }

          bool explicit_default_file = false;
          const std::string defaults_file =
            find_default_settings_file(filename_in, user_settings, explicit_default_file);

          if (defaults_file.empty())
          {
            return YAML::Clone(user_settings);
          }

          if (!Gambit::Utils::file_exists(defaults_file))
          {
            if (explicit_default_file)
            {
              throw std::runtime_error("CBS defaults file " + defaults_file + " not found.");
            }
            return YAML::Clone(user_settings);
          }

          YAML::Node defaults_root;
          try
          {
            defaults_root = YAML::LoadFile(defaults_file);
          }
          catch (YAML::Exception& e)
          {
            throw std::runtime_error(
              "YAML error in CBS defaults file " + defaults_file +
              ".\n(yaml-cpp error: " + std::string(e.what()) + " )");
          }

          YAML::Node merged_settings;
          if (defaults_root["settings"])
          {
            merged_settings = merge_yaml_nodes(merged_settings, defaults_root["settings"]);
          }

          if (defaults_root["analysis_defaults"])
          {
            const YAML::Node analysis_defaults = defaults_root["analysis_defaults"];
            for (const str& analysis : analyses)
            {
              if (!analysis_defaults[analysis]) continue;

              const YAML::Node analysis_node = analysis_defaults[analysis];
              const YAML::Node settings_node =
                analysis_node["settings"] ? analysis_node["settings"] : analysis_node;
              merged_settings = merge_yaml_nodes(merged_settings, settings_node);
            }
          }

          return merge_yaml_nodes(merged_settings, user_settings);
        }

        CrossSectionInput parse_cross_section_fb(const Options& opts, const std::string& context)
        {
          const bool has_fb = opts.hasKey("cross_section_fb");
          const bool has_pb = opts.hasKey("cross_section_pb");
          const bool has_unc_fb = opts.hasKey("cross_section_uncert_fb");
          const bool has_unc_pb = opts.hasKey("cross_section_uncert_pb");
          const bool has_frac_unc = opts.hasKey("cross_section_fractional_uncert");

          const int n_xsec_keys = static_cast<int>(has_fb) + static_cast<int>(has_pb);
          const int n_uncert_keys = static_cast<int>(has_unc_fb) + static_cast<int>(has_unc_pb) + static_cast<int>(has_frac_unc);

          if (n_xsec_keys != 1 || n_uncert_keys != 1)
          {
            std::stringstream msg;
            msg << "Invalid cross-section specification in " << context << ".\n"
                << "Expected one of:\n"
                << "  cross_section_fb + cross_section_uncert_fb\n"
                << "  cross_section_fb + cross_section_fractional_uncert\n"
                << "  cross_section_pb + cross_section_uncert_pb\n"
                << "  cross_section_pb + cross_section_fractional_uncert";
            throw std::runtime_error(msg.str());
          }

          CrossSectionInput result;
          if (has_fb)
          {
            result.xsec_fb = opts.getValue<double>("cross_section_fb");

            if (has_unc_fb)
            {
              result.xsec_uncert_fb = opts.getValue<double>("cross_section_uncert_fb");
            }
            else if (has_frac_unc)
            {
              const double frac = opts.getValue<double>("cross_section_fractional_uncert");
              if (frac < 0.0)
              {
                throw std::runtime_error("cross_section_fractional_uncert must be >= 0 in " + context + ".");
              }
              result.xsec_uncert_fb = frac * result.xsec_fb;
            }
            else
            {
              throw std::runtime_error("cross_section_uncert_pb cannot be combined with cross_section_fb in " + context + ".");
            }
          }
          else
          {
            result.xsec_fb = 1000.0 * opts.getValue<double>("cross_section_pb");

            if (has_unc_pb)
            {
              result.xsec_uncert_fb = 1000.0 * opts.getValue<double>("cross_section_uncert_pb");
            }
            else if (has_frac_unc)
            {
              const double frac = opts.getValue<double>("cross_section_fractional_uncert");
              if (frac < 0.0)
              {
                throw std::runtime_error("cross_section_fractional_uncert must be >= 0 in " + context + ".");
              }
              result.xsec_uncert_fb = frac * result.xsec_fb;
            }
            else
            {
              throw std::runtime_error("cross_section_uncert_fb cannot be combined with cross_section_pb in " + context + ".");
            }
          }

          if (result.xsec_fb < 0.0 || result.xsec_uncert_fb < 0.0)
          {
            throw std::runtime_error("Cross sections and uncertainties must be >= 0 in " + context + ".");
          }

          return result;
        }

        HepMCFileInput parse_hepmc_file_input(const YAML::Node& file_node, const std::string& context)
        {
          HepMCFileInput file_input;

          if (file_node.IsScalar())
          {
            file_input.filename = file_node.as<str>();
          }
          else if (file_node.IsMap())
          {
            if (file_node["file"])
            {
              file_input.filename = file_node["file"].as<str>();
            }
            else if (file_node["filename"])
            {
              file_input.filename = file_node["filename"].as<str>();
            }
            else
            {
              throw std::runtime_error("Missing file/filename key in " + context + ".");
            }

            // CBS now always derives file statistics from the HepMC file itself.
            // Keep YAML strict to avoid stale/manual event counts.
            if (file_node["generated_events"])
            {
              throw std::runtime_error(
                "The generated_events option is no longer supported in " + context +
                ". Please remove it; CBS will count events directly from the HepMC file."
              );
            }
          }
          else
          {
            throw std::runtime_error("Invalid file entry in " + context + ". Expected string or mapping.");
          }

          if (file_input.filename.empty())
          {
            throw std::runtime_error("Empty HepMC filename in " + context + ".");
          }
          if (!is_supported_hepmc_file(file_input.filename))
          {
            throw std::runtime_error("Unrecognised event file format in " + file_input.filename + "; must be .hepmc/.hepmc2/.hepmc3.");
          }
          if (!Gambit::Utils::file_exists(file_input.filename))
          {
            throw std::runtime_error("HepMC event file " + file_input.filename + " not found.");
          }

          return file_input;
        }
      } // namespace

      PreparedInput parse_and_prepare_input(const std::string& filename_in)
      {
        PreparedInput prepared;

        try
        {
          prepared.infile = YAML::LoadFile(filename_in);
        }
        catch (YAML::Exception& e)
        {
          throw std::runtime_error("YAML error in " + filename_in + ".\n(yaml-cpp error: " + std::string(e.what()) + " )");
        }

        if (prepared.infile["analyses"])
        {
          prepared.analyses = prepared.infile["analyses"].as<std::vector<str>>();
        }
        else
        {
          throw std::runtime_error("Analyses list not found in " + filename_in + ". Quitting...");
        }

        if (prepared.infile["settings"])
        {
          prepared.infile["settings"] =
            apply_default_settings(filename_in, prepared.analyses, prepared.infile["settings"]);
          prepared.settings = Options(prepared.infile["settings"]);
        }
        else
        {
          throw std::runtime_error("Settings section not found in " + filename_in + ". Quitting...");
        }

        const bool has_processes = prepared.settings.hasKey("processes");
        const bool has_event_file = prepared.settings.hasKey("event_file");

        if (has_processes && has_event_file)
        {
          throw std::runtime_error("Please use exactly one input mode: either settings.processes or settings.event_file.");
        }

        if (has_processes)
        {
          if (prepared.settings.hasKey("cross_section_fb")
              || prepared.settings.hasKey("cross_section_pb")
              || prepared.settings.hasKey("cross_section_uncert_fb")
              || prepared.settings.hasKey("cross_section_uncert_pb")
              || prepared.settings.hasKey("cross_section_fractional_uncert"))
          {
            throw std::runtime_error("Top-level cross_section_* settings are not allowed when using settings.processes.");
          }

          YAML::Node processes_node = prepared.settings.getValue<YAML::Node>("processes");
          if (!processes_node.IsSequence() || processes_node.size() == 0)
          {
            throw std::runtime_error("settings.processes must be a non-empty sequence.");
          }

          double total_uncert_sq = 0.0;

          for (std::size_t ip = 0; ip < processes_node.size(); ++ip)
          {
            YAML::Node process_node = processes_node[ip];
            if (!process_node.IsMap())
            {
              throw std::runtime_error("Each entry in settings.processes must be a mapping.");
            }

            Options process_opts(process_node);
            ProcessInput process_input;
            process_input.name = process_opts.getValueOrDef<str>("process_" + std::to_string(ip), "name");

            const std::string process_context = "settings.processes[" + std::to_string(ip) + "]";
            const CrossSectionInput xs = parse_cross_section_fb(process_opts, process_context);
            process_input.cross_section_fb = xs.xsec_fb;
            process_input.cross_section_uncert_fb = xs.xsec_uncert_fb;

            if (!process_opts.hasKey("files"))
            {
              throw std::runtime_error("Missing files list in " + process_context + ".");
            }

            YAML::Node files_node = process_opts.getValue<YAML::Node>("files");
            if (!files_node.IsSequence() || files_node.size() == 0)
            {
              throw std::runtime_error("files must be a non-empty sequence in " + process_context + ".");
            }

            for (std::size_t jf = 0; jf < files_node.size(); ++jf)
            {
              const std::string file_context = process_context + ".files[" + std::to_string(jf) + "]";
              HepMCFileInput file_input = parse_hepmc_file_input(files_node[jf], file_context);
              process_input.files.push_back(file_input);
            }

            prepared.processes.push_back(process_input);
            prepared.total_cross_section_fb += process_input.cross_section_fb;
            total_uncert_sq += process_input.cross_section_uncert_fb * process_input.cross_section_uncert_fb;
          }

          if (prepared.total_cross_section_fb <= 0.0)
          {
            throw std::runtime_error("Total cross section from settings.processes must be > 0.");
          }
          prepared.total_cross_section_uncert_fb = std::sqrt(total_uncert_sq);

          for (const ProcessInput& process : prepared.processes)
          {
            for (const HepMCFileInput& file : process.files)
            {
              prepared.hepmc_filenames.push_back(file.filename);
            }
          }
        }
        else
        {
          if (!has_event_file)
          {
            throw std::runtime_error("Missing settings.event_file (legacy mode) or settings.processes (multi-process mode).");
          }

          const str event_filename = prepared.settings.getValue<str>("event_file");
          if (!is_supported_hepmc_file(event_filename))
          {
            throw std::runtime_error("Unrecognised event file format in " + event_filename + "; must be .hepmc/.hepmc2/.hepmc3.");
          }
          if (!Gambit::Utils::file_exists(event_filename))
          {
            throw std::runtime_error("HepMC event file " + event_filename + " not found.");
          }

          const CrossSectionInput xs = parse_cross_section_fb(prepared.settings, "settings");
          prepared.total_cross_section_fb = xs.xsec_fb;
          prepared.total_cross_section_uncert_fb = xs.xsec_uncert_fb;

          prepared.hepmc_filenames.push_back(event_filename);
        }

        if (prepared.hepmc_filenames.empty())
        {
          throw std::runtime_error("No HepMC files were prepared from input YAML.");
        }

        return prepared;
      }
    } // namespace SoloInput
  }   // namespace ColliderBit
} // namespace Gambit
