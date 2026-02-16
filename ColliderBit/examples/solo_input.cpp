//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Input parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_input.hpp"

#include <cmath>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "HepMC3/GenEvent.h"
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"

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

        int determine_hepmc_file_version(const str& hepmc_filename)
        {
          std::ifstream infile(hepmc_filename);
          if (!infile.good())
          {
            throw std::runtime_error("HepMC event file " + hepmc_filename + " not found.");
          }

          std::string line;
          while (std::getline(infile, line))
          {
            if (line.empty()) continue;

            const std::string short_line = line.substr(0, 16);
            if (short_line == "HepMC::Version 2")
            {
              return 2;
            }
            else if (short_line == "HepMC::Version 3")
            {
              if (!std::getline(infile, line))
              {
                throw std::runtime_error("Failed to determine HepMC format in file " + hepmc_filename + ".");
              }

              const std::string text_format = line.substr(0, 14);
              if (text_format == "HepMC::Asciiv3")
              {
                return 3;
              }
              else if (text_format == "HepMC::IO_GenE")
              {
                return 2;
              }

              std::stringstream msg;
              msg << "Could not determine HepMC version for file " << hepmc_filename
                  << " from line: " << line;
              throw std::runtime_error(msg.str());
            }
            else
            {
              std::stringstream msg;
              msg << "Could not determine HepMC version for file " << hepmc_filename
                  << " from line: " << line;
              throw std::runtime_error(msg.str());
            }
          }

          throw std::runtime_error("Failed to determine HepMC version for input file " + hepmc_filename + ".");
        }

        std::unique_ptr<HepMC3::Reader> make_hepmc_reader(const str& hepmc_filename, int hepmc_version)
        {
          if (hepmc_version == 2)
          {
            return std::unique_ptr<HepMC3::Reader>(new HepMC3::ReaderAsciiHepMC2(hepmc_filename));
          }
          if (hepmc_version == 3)
          {
            return std::unique_ptr<HepMC3::Reader>(new HepMC3::ReaderAscii(hepmc_filename));
          }

          throw std::runtime_error("Unsupported HepMC version for file " + hepmc_filename + ".");
        }

        long long count_hepmc_events(const str& hepmc_filename)
        {
          const int hepmc_version = determine_hepmc_file_version(hepmc_filename);
          std::unique_ptr<HepMC3::Reader> reader = make_hepmc_reader(hepmc_filename, hepmc_version);

          HepMC3::GenEvent event;
          long long event_count = 0;
          while (true)
          {
            event.clear();
            const bool event_retrieved = reader->read_event(event);
            if (!event_retrieved) break;

            // Workaround for empty events when reader reached EOF.
            if (event.particles().empty() && event.vertices().empty()) break;

            ++event_count;
          }

          return event_count;
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

            if (file_node["generated_events"])
            {
              file_input.generated_events = file_node["generated_events"].as<long long>();
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
          if (file_input.generated_events == 0)
          {
            throw std::runtime_error("generated_events must be > 0 in " + context + ".");
          }
          if (file_input.generated_events < -1)
          {
            throw std::runtime_error("generated_events must be positive when specified in " + context + ".");
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

          std::vector<long long> process_generated_events;
          process_generated_events.reserve(processes_node.size());

          long long total_generated_events = 0;
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

            long long this_process_generated_events = 0;
            for (std::size_t jf = 0; jf < files_node.size(); ++jf)
            {
              const std::string file_context = process_context + ".files[" + std::to_string(jf) + "]";
              HepMCFileInput file_input = parse_hepmc_file_input(files_node[jf], file_context);

              if (file_input.generated_events < 0)
              {
                file_input.generated_events = count_hepmc_events(file_input.filename);
              }
              if (file_input.generated_events <= 0)
              {
                throw std::runtime_error("No events found in " + file_input.filename + ".");
              }

              this_process_generated_events += file_input.generated_events;
              process_input.files.push_back(file_input);
            }

            if (this_process_generated_events <= 0)
            {
              throw std::runtime_error("Total generated events must be > 0 for " + process_context + ".");
            }

            prepared.processes.push_back(process_input);
            process_generated_events.push_back(this_process_generated_events);

            total_generated_events += this_process_generated_events;
            prepared.total_cross_section_fb += process_input.cross_section_fb;
            total_uncert_sq += process_input.cross_section_uncert_fb * process_input.cross_section_uncert_fb;
          }

          if (prepared.total_cross_section_fb <= 0.0)
          {
            throw std::runtime_error("Total cross section from settings.processes must be > 0.");
          }
          if (total_generated_events <= 0)
          {
            throw std::runtime_error("Total generated events from settings.processes must be > 0.");
          }

          prepared.total_cross_section_uncert_fb = std::sqrt(total_uncert_sq);

          for (std::size_t ip = 0; ip < prepared.processes.size(); ++ip)
          {
            const ProcessInput& process = prepared.processes[ip];
            const long long process_events = process_generated_events[ip];

            const double process_weight =
              (process.cross_section_fb / prepared.total_cross_section_fb)
              * (static_cast<double>(total_generated_events) / static_cast<double>(process_events));

            for (const HepMCFileInput& file : process.files)
            {
              prepared.hepmc_filenames.push_back(file.filename);
              prepared.hepmc_file_weights.push_back(process_weight);
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
          prepared.hepmc_file_weights.push_back(1.0);
        }

        if (prepared.hepmc_filenames.empty())
        {
          throw std::runtime_error("No HepMC files were prepared from input YAML.");
        }
        if (prepared.hepmc_filenames.size() != prepared.hepmc_file_weights.size())
        {
          throw std::runtime_error("Internal error: mismatch between HepMC filenames and weights.");
        }

        return prepared;
      }
    } // namespace SoloInput
  }   // namespace ColliderBit
} // namespace Gambit
