//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Input parsing helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#include "solo_input.hpp"

#include "gambit/ColliderBit/analyses/AnalysisContainer.hpp"
#include "gambit/cmake/cmake_variables.hpp"

#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

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

        struct HepMCFileInspection
        {
          str filename;
          HepMCRunInfo run_info;
        };

        struct AnalysisRequirements
        {
          bool has_collision_energy = false;
          double collision_energy_TeV = 0.0;
          std::vector<std::pair<int, int>> beam_ids;
          std::vector<std::pair<double, double>> beam_energies_GeV;
        };

        enum class HepMCFileFormat
        {
          HepMC2,
          HepMC3
        };

        bool is_supported_hepmc_file(const str& filename)
        {
          return Gambit::Utils::endsWith(filename, ".hepmc")
                 || Gambit::Utils::endsWith(filename, ".hepmc2")
                 || Gambit::Utils::endsWith(filename, ".hepmc3");
        }

        std::string to_lower(std::string value)
        {
          std::transform(value.begin(), value.end(), value.begin(),
                         [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
          return value;
        }

        std::string analysis_info_file(const str& analysis)
        {
          return std::string(GAMBIT_DIR) + "/ColliderBit/src/analyses/Analysis_" + analysis + ".info";
        }

        std::string format_energy_TeV(double energy_TeV)
        {
          std::ostringstream formatted;
          formatted << std::fixed << std::setprecision(6) << energy_TeV << " TeV";
          return formatted.str();
        }

        std::string format_beam_pair(int beam_pid_1, int beam_pid_2)
        {
          return "(" + std::to_string(beam_pid_1) + ", "
                 + std::to_string(beam_pid_2) + ")";
        }

        std::string format_run_conditions(const HepMCRunInfo& run_info)
        {
          std::ostringstream formatted;
          formatted << "beams "
                    << format_beam_pair(run_info.beam_pid_1, run_info.beam_pid_2)
                    << " at (" << run_info.beam_energy_1_GeV << ", "
                    << run_info.beam_energy_2_GeV << ") GeV, sqrt(s) = "
                    << format_energy_TeV(run_info.collision_energy_TeV);
          return formatted.str();
        }

        bool is_lhc_recast_metadata(const YAML::Node& metadata)
        {
          const YAML::Node expt_run = metadata["ExptRun"];
          if (!expt_run || !expt_run.IsScalar()) return false;

          const std::string run = to_lower(expt_run.as<std::string>());
          return run.find("atlas-") == 0 || run.find("cms-") == 0;
        }

        HepMCFileFormat get_hepmc_file_format(const str& filename)
        {
          std::ifstream infile(filename);
          if (!infile)
          {
            throw std::runtime_error("Could not open HepMC event file " + filename + " for collision-energy inspection.");
          }

          std::string line;
          while (std::getline(infile, line))
          {
            if (line.empty()) continue;

            const std::string short_line = line.substr(0, 16);
            if (short_line == "HepMC::Version 2")
            {
              return HepMCFileFormat::HepMC2;
            }
            if (short_line == "HepMC::Version 3")
            {
              if (!std::getline(infile, line))
              {
                throw std::runtime_error("Could not determine HepMC text format in " + filename + ".");
              }

              const std::string text_format = line.substr(0, 14);
              if (text_format == "HepMC::Asciiv3")
              {
                return HepMCFileFormat::HepMC3;
              }
              if (text_format == "HepMC::IO_GenE")
              {
                return HepMCFileFormat::HepMC2;
              }

              throw std::runtime_error(
                "Could not determine HepMC text format from '" + text_format
                + "' in " + filename + "."
              );
            }

            throw std::runtime_error(
              "Could not determine HepMC version from '" + short_line
              + "' in " + filename + "."
            );
          }

          throw std::runtime_error("HepMC event file " + filename + " is empty.");
        }

        std::pair<HepMC3::ConstGenParticlePtr, HepMC3::ConstGenParticlePtr>
        get_beam_particles(const HepMC3::GenEvent& event, const str& filename)
        {
          const std::vector<HepMC3::ConstGenParticlePtr> beams = event.beams();
          if (beams.size() >= 2 && beams[0] && beams[1])
          {
            return std::make_pair(beams[0], beams[1]);
          }

          // Match Rivet's fallback for HepMC files without explicit beam links.
          std::vector<HepMC3::ConstGenParticlePtr> status_four_beams;
          for (const HepMC3::ConstGenParticlePtr& particle : event.particles())
          {
            if (particle && particle->status() == 4) status_four_beams.push_back(particle);
          }
          if (status_four_beams.size() >= 2)
          {
            return std::make_pair(status_four_beams[0], status_four_beams[1]);
          }

          throw std::runtime_error(
            "HepMC event file " + filename
            + " does not provide two identifiable beam particles in its first event; "
              "CBS cannot determine the run conditions."
          );
        }

        HepMCRunInfo inspect_run_info(const HepMC3::GenEvent& event, const str& filename)
        {
          const std::pair<HepMC3::ConstGenParticlePtr, HepMC3::ConstGenParticlePtr> beams =
            get_beam_particles(event, filename);

          HepMC3::FourVector beam_sum = beams.first->momentum() + beams.second->momentum();
          if (event.momentum_unit() == HepMC3::Units::MEV)
          {
            beam_sum *= 0.001;
          }

          const double s_GeV2 = beam_sum.m2();
          if (!std::isfinite(s_GeV2) || s_GeV2 <= 0.0)
          {
            throw std::runtime_error(
              "HepMC event file " + filename
              + " has a non-positive beam invariant mass squared; CBS cannot determine the collision energy."
            );
          }

          HepMCRunInfo result;
          result.beam_pid_1 = beams.first->pid();
          result.beam_pid_2 = beams.second->pid();
          result.beam_energy_1_GeV = beams.first->momentum().e();
          result.beam_energy_2_GeV = beams.second->momentum().e();
          if (event.momentum_unit() == HepMC3::Units::MEV)
          {
            result.beam_energy_1_GeV *= 0.001;
            result.beam_energy_2_GeV *= 0.001;
          }
          result.collision_energy_TeV = std::sqrt(s_GeV2) / 1000.0;

          if (!std::isfinite(result.beam_energy_1_GeV)
              || !std::isfinite(result.beam_energy_2_GeV)
              || result.beam_energy_1_GeV <= 0.0
              || result.beam_energy_2_GeV <= 0.0
              || !std::isfinite(result.collision_energy_TeV)
              || result.collision_energy_TeV <= 0.0)
          {
            throw std::runtime_error(
              "HepMC event file " + filename
              + " has invalid beam energies or collision energy."
            );
          }
          return result;
        }

        HepMCFileInspection inspect_hepmc_file(const str& filename)
        {
          HepMC3::GenEvent event;
          bool event_retrieved = false;

          switch (get_hepmc_file_format(filename))
          {
            case HepMCFileFormat::HepMC2:
            {
              HepMC3::ReaderAsciiHepMC2 reader(filename);
              event_retrieved = reader.read_event(event);
              break;
            }
            case HepMCFileFormat::HepMC3:
            {
              HepMC3::ReaderAscii reader(filename);
              event_retrieved = reader.read_event(event);
              break;
            }
          }

          if (!event_retrieved || (event.particles().empty() && event.vertices().empty()))
          {
            throw std::runtime_error(
              "Could not read a physical first event from HepMC event file " + filename
              + " while determining its collision energy."
            );
          }

          HepMCFileInspection inspection;
          inspection.filename = filename;
          inspection.run_info = inspect_run_info(event, filename);
          return inspection;
        }

        double get_collision_energy_tolerance_TeV(const Options& settings)
        {
          const double tolerance_GeV =
            settings.getValueOrDef<double>(1.0, "collision_energy_tolerance_GeV");
          if (!std::isfinite(tolerance_GeV) || tolerance_GeV < 0.0)
          {
            throw std::runtime_error("collision_energy_tolerance_GeV must be finite and >= 0.");
          }
          return tolerance_GeV / 1000.0;
        }

        bool collision_energies_match(double lhs_TeV, double rhs_TeV, double tolerance_TeV)
        {
          return std::abs(lhs_TeV - rhs_TeV) <= tolerance_TeV;
        }

        double get_beam_energy_tolerance_GeV(const Options& settings)
        {
          const double tolerance_GeV =
            settings.getValueOrDef<double>(1.0, "beam_energy_tolerance_GeV");
          if (!std::isfinite(tolerance_GeV) || tolerance_GeV < 0.0)
          {
            throw std::runtime_error("beam_energy_tolerance_GeV must be finite and >= 0.");
          }
          return tolerance_GeV;
        }

        double get_beam_energy_relative_tolerance(const Options& settings)
        {
          const double tolerance =
            settings.getValueOrDef<double>(1.0e-3, "beam_energy_relative_tolerance");
          if (!std::isfinite(tolerance) || tolerance < 0.0)
          {
            throw std::runtime_error("beam_energy_relative_tolerance must be finite and >= 0.");
          }
          return tolerance;
        }

        bool beam_energy_match(double lhs_GeV, double rhs_GeV,
                               double absolute_tolerance_GeV,
                               double relative_tolerance)
        {
          const double difference = std::abs(lhs_GeV - rhs_GeV);
          const double average = (std::abs(lhs_GeV) + std::abs(rhs_GeV)) / 2.0;
          return difference <= absolute_tolerance_GeV
                 || difference <= relative_tolerance * average;
        }

        bool beam_ids_match(int lhs_1, int lhs_2, int rhs_1, int rhs_2)
        {
          return (lhs_1 == rhs_1 && lhs_2 == rhs_2)
                 || (lhs_1 == rhs_2 && lhs_2 == rhs_1);
        }

        bool beam_energies_match(double lhs_1, double lhs_2, double rhs_1, double rhs_2,
                                 double absolute_tolerance_GeV,
                                 double relative_tolerance)
        {
          const bool direct = beam_energy_match(lhs_1, rhs_1, absolute_tolerance_GeV,
                                                 relative_tolerance)
                              && beam_energy_match(lhs_2, rhs_2, absolute_tolerance_GeV,
                                                   relative_tolerance);
          const bool swapped = beam_energy_match(lhs_1, rhs_2, absolute_tolerance_GeV,
                                                  relative_tolerance)
                               && beam_energy_match(lhs_2, rhs_1, absolute_tolerance_GeV,
                                                    relative_tolerance);
          return direct || swapped;
        }

        bool run_infos_match(const HepMCRunInfo& lhs, const HepMCRunInfo& rhs,
                             double collision_energy_tolerance_TeV,
                             double beam_energy_tolerance_GeV,
                             double beam_energy_relative_tolerance)
        {
          return beam_ids_match(lhs.beam_pid_1, lhs.beam_pid_2,
                                rhs.beam_pid_1, rhs.beam_pid_2)
                 && beam_energies_match(lhs.beam_energy_1_GeV, lhs.beam_energy_2_GeV,
                                        rhs.beam_energy_1_GeV, rhs.beam_energy_2_GeV,
                                        beam_energy_tolerance_GeV,
                                        beam_energy_relative_tolerance)
                 && collision_energies_match(lhs.collision_energy_TeV,
                                              rhs.collision_energy_TeV,
                                              collision_energy_tolerance_TeV);
        }

        int parse_beam_pid(const YAML::Node& node, const str& analysis)
        {
          if (!node || !node.IsScalar())
          {
            throw std::runtime_error("analysis '" + analysis + "' has a non-scalar beam ID");
          }

          const std::string name = to_lower(node.as<std::string>());
          if (name == "p+" || name == "p" || name == "proton") return 2212;
          if (name == "p-" || name == "pbar" || name == "antiproton") return -2212;
          if (name == "e-") return 11;
          if (name == "e+") return -11;
          if (name == "mu-") return 13;
          if (name == "mu+") return -13;

          try
          {
            std::size_t consumed = 0;
            const int pid = std::stoi(name, &consumed);
            if (consumed == name.size()) return pid;
          }
          catch (const std::exception&)
          {
            // Convert the parse failure into a useful metadata diagnostic below.
          }

          throw std::runtime_error(
            "analysis '" + analysis + "' has unsupported beam ID '"
            + node.as<std::string>() + "'"
          );
        }

        std::vector<std::pair<int, int>> parse_beam_requirements(
          const YAML::Node& node, const str& analysis)
        {
          std::vector<std::pair<int, int>> result;
          if (!node) return result;
          if (!node.IsSequence())
          {
            throw std::runtime_error("analysis '" + analysis + "' has invalid Beams metadata");
          }

          if (node.size() == 2 && node[0].IsScalar() && node[1].IsScalar())
          {
            result.emplace_back(parse_beam_pid(node[0], analysis),
                                parse_beam_pid(node[1], analysis));
            return result;
          }

          for (const YAML::Node& pair : node)
          {
            if (!pair.IsSequence() || pair.size() != 2
                || !pair[0].IsScalar() || !pair[1].IsScalar())
            {
              throw std::runtime_error(
                "analysis '" + analysis + "' has invalid Beams metadata; expected pairs"
              );
            }
            result.emplace_back(parse_beam_pid(pair[0], analysis),
                                parse_beam_pid(pair[1], analysis));
          }
          return result;
        }

        std::vector<std::pair<double, double>> parse_beam_energy_requirements(
          const YAML::Node& node, const str& analysis)
        {
          std::vector<std::pair<double, double>> result;
          if (!node) return result;
          if (!node.IsSequence())
          {
            throw std::runtime_error("analysis '" + analysis + "' has invalid Energies metadata");
          }

          for (const YAML::Node& entry : node)
          {
            std::pair<double, double> energies;
            if (entry.IsScalar())
            {
              const double collision_energy_GeV = entry.as<double>();
              energies = std::make_pair(collision_energy_GeV / 2.0,
                                         collision_energy_GeV / 2.0);
            }
            else if (entry.IsSequence() && entry.size() == 2)
            {
              energies = std::make_pair(entry[0].as<double>(), entry[1].as<double>());
            }
            else
            {
              throw std::runtime_error(
                "analysis '" + analysis + "' has invalid Energies metadata"
              );
            }

            if (!std::isfinite(energies.first) || !std::isfinite(energies.second)
                || energies.first <= 0.0 || energies.second <= 0.0)
            {
              throw std::runtime_error(
                "analysis '" + analysis + "' has non-positive beam energy metadata"
              );
            }
            result.push_back(energies);
          }
          return result;
        }

        bool get_analysis_requirements(const str& analysis,
                                       AnalysisRequirements& result,
                                       str& reason)
        {
          const std::string info_file = analysis_info_file(analysis);
          if (!Gambit::Utils::file_exists(info_file))
          {
            reason = "its .info metadata file is missing";
            return false;
          }

          try
          {
            const YAML::Node metadata = YAML::LoadFile(info_file);
            const YAML::Node energy = metadata["Ecm_TeV"];
            if (energy)
            {
              if (!energy.IsScalar())
              {
                reason = "its .info metadata has a non-scalar Ecm_TeV";
                return false;
              }
              result.collision_energy_TeV = energy.as<double>();
              if (!std::isfinite(result.collision_energy_TeV)
                  || result.collision_energy_TeV <= 0.0)
              {
                reason = "its .info metadata has an invalid Ecm_TeV";
                return false;
              }
              result.has_collision_energy = true;
            }

            result.beam_ids = parse_beam_requirements(metadata["Beams"], analysis);
            result.beam_energies_GeV =
              parse_beam_energy_requirements(metadata["Energies"], analysis);

            // Current CBS analyses are ATLAS/CMS LHC recasts.  Their existing
            // metadata predates Beams/Energies, so derive the same p+p,
            // symmetric-beam requirement from Ecm_TeV unless it is explicit.
            if (is_lhc_recast_metadata(metadata) && result.has_collision_energy)
            {
              if (result.beam_ids.empty()) result.beam_ids.emplace_back(2212, 2212);
              if (result.beam_energies_GeV.empty())
              {
                const double beam_energy_GeV = 500.0 * result.collision_energy_TeV;
                result.beam_energies_GeV.emplace_back(beam_energy_GeV, beam_energy_GeV);
              }
            }

            if (!result.has_collision_energy && result.beam_energies_GeV.empty())
            {
              reason = "its .info metadata has neither Ecm_TeV nor Energies";
              return false;
            }
          }
          catch (const std::exception& e)
          {
            reason = "its .info metadata could not be read (" + std::string(e.what()) + ")";
            return false;
          }

          return true;
        }

        bool analysis_matches_run(const AnalysisRequirements& requirements,
                                  const HepMCRunInfo& run_info,
                                  double collision_energy_tolerance_TeV,
                                  double beam_energy_tolerance_GeV,
                                  double beam_energy_relative_tolerance,
                                  str& reason)
        {
          if (requirements.has_collision_energy
              && !collision_energies_match(run_info.collision_energy_TeV,
                                            requirements.collision_energy_TeV,
                                            collision_energy_tolerance_TeV))
          {
            reason = "its Ecm_TeV is " + format_energy_TeV(requirements.collision_energy_TeV)
                     + " but the HepMC input is "
                     + format_energy_TeV(run_info.collision_energy_TeV);
            return false;
          }

          if (!requirements.beam_ids.empty())
          {
            bool matched = false;
            for (const std::pair<int, int>& required : requirements.beam_ids)
            {
              if (beam_ids_match(run_info.beam_pid_1, run_info.beam_pid_2,
                                 required.first, required.second))
              {
                matched = true;
                break;
              }
            }
            if (!matched)
            {
              reason = "its beam IDs do not match the HepMC input beams "
                       + format_beam_pair(run_info.beam_pid_1, run_info.beam_pid_2);
              return false;
            }
          }

          if (!requirements.beam_energies_GeV.empty())
          {
            bool matched = false;
            for (const std::pair<double, double>& required : requirements.beam_energies_GeV)
            {
              if (beam_energies_match(run_info.beam_energy_1_GeV,
                                      run_info.beam_energy_2_GeV,
                                      required.first,
                                      required.second,
                                      beam_energy_tolerance_GeV,
                                      beam_energy_relative_tolerance))
              {
                matched = true;
                break;
              }
            }
            if (!matched)
            {
              reason = "its beam energies do not match the HepMC input beam energies";
              return false;
            }
          }

          return true;
        }

        void retain_run_matched_analyses(PreparedInput& prepared,
                                         const std::vector<HepMCFileInspection>& inputs,
                                         double collision_energy_tolerance_TeV,
                                         double beam_energy_tolerance_GeV,
                                         double beam_energy_relative_tolerance)
        {
          std::vector<str> retained_analyses;
          retained_analyses.reserve(prepared.analyses.size());

          for (const str& analysis : prepared.analyses)
          {
            AnalysisRequirements requirements;
            str reason;
            if (!get_analysis_requirements(analysis, requirements, reason))
            {
              prepared.analysis_warnings.push_back(
                "CBS input: ignoring analysis '" + analysis
                + "' because CBS cannot verify its beam/run requirements; " + reason + "."
              );
              continue;
            }

            bool matches_all_inputs = true;
            for (const HepMCFileInspection& input : inputs)
            {
              reason.clear();
              if (!analysis_matches_run(requirements,
                                        input.run_info,
                                        collision_energy_tolerance_TeV,
                                        beam_energy_tolerance_GeV,
                                        beam_energy_relative_tolerance,
                                        reason))
              {
                prepared.analysis_warnings.push_back(
                  "CBS input: ignoring analysis '" + analysis
                  + "' because its beam/run requirements do not match HepMC file "
                  + input.filename + "; " + reason + "."
                );
                matches_all_inputs = false;
                break;
              }
            }

            if (matches_all_inputs) retained_analyses.push_back(analysis);
          }

          prepared.analyses.swap(retained_analyses);
        }

        void validate_hepmc_run_conditions(PreparedInput& prepared)
        {
          const double collision_energy_tolerance_TeV =
            get_collision_energy_tolerance_TeV(prepared.settings);
          const double beam_energy_tolerance_GeV =
            get_beam_energy_tolerance_GeV(prepared.settings);
          const double beam_energy_relative_tolerance =
            get_beam_energy_relative_tolerance(prepared.settings);
          std::vector<HepMCFileInspection> inputs;
          inputs.reserve(prepared.hepmc_filenames.size());
          for (const str& filename : prepared.hepmc_filenames)
          {
            inputs.push_back(inspect_hepmc_file(filename));
          }

          const HepMCFileInspection& reference = inputs.front();
          prepared.run_info = reference.run_info;
          prepared.collision_energy_TeV = reference.run_info.collision_energy_TeV;
          prepared.hepmc_run_infos.clear();
          prepared.hepmc_run_infos.reserve(inputs.size());
          for (const HepMCFileInspection& input : inputs)
          {
            prepared.hepmc_run_infos.push_back(input.run_info);
          }

          for (std::size_t index = 1; index < inputs.size(); ++index)
          {
            const HepMCFileInspection& inspected = inputs[index];
            if (!run_infos_match(reference.run_info,
                                 inspected.run_info,
                                 collision_energy_tolerance_TeV,
                                 beam_energy_tolerance_GeV,
                                 beam_energy_relative_tolerance))
            {
              throw std::runtime_error(
                "CBS input mixes HepMC run conditions: " + reference.filename + " has "
                + format_run_conditions(reference.run_info) + ", while " + inspected.filename
                + " has " + format_run_conditions(inspected.run_info) + "."
              );
            }
          }

          retain_run_matched_analyses(prepared,
                                      inputs,
                                      collision_energy_tolerance_TeV,
                                      beam_energy_tolerance_GeV,
                                      beam_energy_relative_tolerance);
          prepared.infile["analyses"] = prepared.analyses;
        }

        bool passes_validation_policy(const str& analysis, str& reason)
        {
          const std::string info_file = analysis_info_file(analysis);
          if (!Gambit::Utils::file_exists(info_file))
          {
            return true;
          }

          try
          {
            const YAML::Node metadata = YAML::LoadFile(info_file);
            const YAML::Node validation = metadata["Validation"];
            if (!validation || !validation.IsScalar())
            {
              return true;
            }
            if (to_lower(validation.Scalar()) != "passed")
            {
              reason = "its Validation metadata is '" + validation.Scalar() + "'";
              return false;
            }
          }
          catch (const YAML::Exception& e)
          {
            reason = "its .info metadata could not be read (yaml-cpp error: "
                     + std::string(e.what()) + ")";
            return false;
          }

          return true;
        }

        void retain_validated_analyses(PreparedInput& prepared, bool debug_mode)
        {
          std::vector<str> retained_analyses;
          retained_analyses.reserve(prepared.analyses.size());

          for (const str& analysis : prepared.analyses)
          {
            if (!isAnalysisRegistered(analysis))
            {
              prepared.analysis_warnings.push_back(
                "CBS input: ignoring analysis '" + analysis
                + "' because it is not registered in this CBS build.");
              continue;
            }

            str reason;
            if (!passes_validation_policy(analysis, reason))
            {
              if (debug_mode)
              {
                prepared.analysis_warnings.push_back(
                  "CBS input: retaining analysis '" + analysis
                  + "' despite validation status because settings.debug is true; " + reason + ".");
              }
              else
              {
                prepared.analysis_warnings.push_back(
                  "CBS input: ignoring analysis '" + analysis
                  + "' because Validation: passed is required; " + reason + ".");
                continue;
              }
            }

            retained_analyses.push_back(analysis);
          }

          prepared.analyses.swap(retained_analyses);
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

        if (!prepared.infile["settings"])
        {
          throw std::runtime_error("Settings section not found in " + filename_in + ". Quitting...");
        }

        const YAML::Node settings_for_validation = apply_default_settings(
          filename_in, std::vector<str>(), prepared.infile["settings"]);
        const bool debug_mode =
          settings_for_validation["debug"]
            ? settings_for_validation["debug"].as<bool>()
            : false;

        if (prepared.infile["analyses"])
        {
          prepared.requested_analyses = prepared.infile["analyses"].as<std::vector<str>>();
          prepared.analyses = prepared.requested_analyses;
          retain_validated_analyses(prepared, debug_mode);
          prepared.infile["analyses"] = prepared.analyses;
        }
        else
        {
          throw std::runtime_error("Analyses list not found in " + filename_in + ". Quitting...");
        }

        prepared.infile["settings"] =
          apply_default_settings(filename_in, prepared.analyses, prepared.infile["settings"]);
        prepared.settings = Options(prepared.infile["settings"]);

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

        validate_hepmc_run_conditions(prepared);

        return prepared;
      }
    } // namespace SoloInput
  }   // namespace ColliderBit
} // namespace Gambit
