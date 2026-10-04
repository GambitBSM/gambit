//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HepMC event file reader module function
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2019 June
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 June
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 June
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Sep, Oct
///  \date 2020 Apr
///
///  \author Tomek Procter
///           (t.procter.1@research.gla.ac.uk)
///  \date 2019 October
///  \date 2021 November
///
///  \author Yang Zhang
///           (tsp116@ic.ac.uk)
///  \date 2020 June
///
///  *********************************************

#include "gambit/cmake/cmake_variables.hpp"

#ifndef EXCLUDE_HEPMC

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "HepMC3/ReaderAsciiHepMC2.h"
#include "gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/ReaderAscii.h"

#include <cmath>
#include <sstream>
#include <utility>
#include <vector>

#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "
//#define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    namespace
    {
      struct CBSBeamInfo
      {
        int pid_1 = 0;
        int pid_2 = 0;
        double energy_1_GeV = 0.0;
        double energy_2_GeV = 0.0;
        double collision_energy_TeV = 0.0;
      };

      std::pair<HepMC3::ConstGenParticlePtr, HepMC3::ConstGenParticlePtr>
      get_cbs_beam_particles(const HepMC3::GenEvent& event)
      {
        const std::vector<HepMC3::ConstGenParticlePtr> beams = event.beams();
        if (beams.size() >= 2 && beams[0] && beams[1])
        {
          return std::make_pair(beams[0], beams[1]);
        }

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
          "CBS HepMC run validation could not identify two beam particles."
        );
      }

      CBSBeamInfo inspect_cbs_beam_info(const HepMC3::GenEvent& event)
      {
        const std::pair<HepMC3::ConstGenParticlePtr, HepMC3::ConstGenParticlePtr> beams =
          get_cbs_beam_particles(event);
        const HepMC3::FourVector beam_sum = beams.first->momentum() + beams.second->momentum();
        const double s_GeV2 = beam_sum.m2();
        if (!std::isfinite(s_GeV2) || s_GeV2 <= 0.0)
        {
          throw std::runtime_error(
            "CBS HepMC run validation found a non-positive beam invariant mass squared."
          );
        }

        CBSBeamInfo result;
        result.pid_1 = beams.first->pid();
        result.pid_2 = beams.second->pid();
        result.energy_1_GeV = beams.first->momentum().e();
        result.energy_2_GeV = beams.second->momentum().e();
        result.collision_energy_TeV = std::sqrt(s_GeV2) / 1000.0;
        if (!std::isfinite(result.energy_1_GeV)
            || !std::isfinite(result.energy_2_GeV)
            || !std::isfinite(result.collision_energy_TeV)
            || result.energy_1_GeV <= 0.0
            || result.energy_2_GeV <= 0.0
            || result.collision_energy_TeV <= 0.0)
        {
          throw std::runtime_error("CBS HepMC run validation found invalid beam information.");
        }
        return result;
      }

      bool cbs_beam_ids_match(int lhs_1, int lhs_2, int rhs_1, int rhs_2)
      {
        return (lhs_1 == rhs_1 && lhs_2 == rhs_2)
               || (lhs_1 == rhs_2 && lhs_2 == rhs_1);
      }

      bool cbs_beam_energy_match(double lhs_GeV, double rhs_GeV,
                                 double absolute_tolerance_GeV,
                                 double relative_tolerance)
      {
        const double difference = std::abs(lhs_GeV - rhs_GeV);
        const double average = (std::abs(lhs_GeV) + std::abs(rhs_GeV)) / 2.0;
        return difference <= absolute_tolerance_GeV
               || difference <= relative_tolerance * average;
      }

      bool cbs_beam_energies_match(double lhs_1, double lhs_2,
                                   double rhs_1, double rhs_2,
                                   double absolute_tolerance_GeV,
                                   double relative_tolerance)
      {
        const bool direct = cbs_beam_energy_match(lhs_1, rhs_1, absolute_tolerance_GeV,
                                                   relative_tolerance)
                            && cbs_beam_energy_match(lhs_2, rhs_2, absolute_tolerance_GeV,
                                                     relative_tolerance);
        const bool swapped = cbs_beam_energy_match(lhs_1, rhs_2, absolute_tolerance_GeV,
                                                    relative_tolerance)
                             && cbs_beam_energy_match(lhs_2, rhs_1, absolute_tolerance_GeV,
                                                      relative_tolerance);
        return direct || swapped;
      }

      bool cbs_collision_energy_match(double lhs_TeV, double rhs_TeV,
                                      double tolerance_TeV)
      {
        return std::abs(lhs_TeV - rhs_TeV) <= tolerance_TeV;
      }

      void validate_cbs_event(const HepMC3::GenEvent& event, const Options& options)
      {
        if (!options.getValueOrDef<bool>(false, "cbs_check_hepmc_run")) return;

        const std::vector<int> reference_ids =
          options.getValueOrDef<std::vector<int>>({}, "cbs_reference_beam_ids");
        const std::vector<double> reference_energies =
          options.getValueOrDef<std::vector<double>>({}, "cbs_reference_beam_energies_GeV");
        if (reference_ids.size() != 2 || reference_energies.size() != 2)
        {
          throw std::runtime_error(
            "CBS HepMC run validation has incomplete first-event beam information."
          );
        }

        const CBSBeamInfo current = inspect_cbs_beam_info(event);
        const double collision_tolerance_TeV =
          options.getValueOrDef<double>(0.001, "cbs_collision_energy_tolerance_TeV");
        const double beam_absolute_tolerance_GeV =
          options.getValueOrDef<double>(1.0, "cbs_beam_energy_tolerance_GeV");
        const double beam_relative_tolerance =
          options.getValueOrDef<double>(1.0e-3, "cbs_beam_energy_relative_tolerance");
        const int reference_pid_1 = reference_ids[0];
        const int reference_pid_2 = reference_ids[1];
        const double reference_energy_1 = reference_energies[0];
        const double reference_energy_2 = reference_energies[1];
        const double reference_collision_energy =
          options.getValueOrDef<double>(0.0, "cbs_reference_collision_energy_TeV");

        const bool ids_match = cbs_beam_ids_match(current.pid_1, current.pid_2,
                                                   reference_pid_1, reference_pid_2);
        const bool energies_match = cbs_beam_energies_match(
          current.energy_1_GeV, current.energy_2_GeV,
          reference_energy_1, reference_energy_2,
          beam_absolute_tolerance_GeV, beam_relative_tolerance);
        const bool collision_energy_match = cbs_collision_energy_match(
          current.collision_energy_TeV, reference_collision_energy,
          collision_tolerance_TeV);

        if (!ids_match || !energies_match || !collision_energy_match)
        {
          std::ostringstream message;
          message << "CBS HepMC run conditions changed after the first event: current beams ("
                  << current.pid_1 << ", " << current.pid_2 << ") at "
                  << current.energy_1_GeV << ", " << current.energy_2_GeV
                  << " GeV, sqrt(s) = " << current.collision_energy_TeV
                  << " TeV; expected beams (" << reference_pid_1 << ", "
                  << reference_pid_2 << ") at " << reference_energy_1 << ", "
                  << reference_energy_2 << " GeV, sqrt(s) = "
                  << reference_collision_energy << " TeV.";
          throw std::runtime_error(message.str());
        }
      }
    }

    /// A nested function that reads in HepMC event files
    void readHepMCEvent(HepMC3::GenEvent& result, const str HepMC_filename,
                        const MCLoopInfo& RunMC, const int iteration,
                        void(*halt)())
    {
      result.clear();

      // Initialise the HepMC reader
      static int HepMC_file_version = -1;

      static bool first = true;
      if (first)
      {
        if (not Utils::file_exists(HepMC_filename)) throw std::runtime_error("HepMC event file "+HepMC_filename+" not found. Quitting...");

        // Figure out if the file is HepMC2 or HepMC3
        std::ifstream infile(HepMC_filename);
        if (infile.good())
        {
          std::string line;
          while(std::getline(infile, line))
          {
            // Skip blank lines
            if(line == "") continue;

            // We look for "HepMC::Version 2" or "HepMC::Version 3",
            // so we only need the first 16 characters of the line
            std::string short_line = line.substr(0,16);

            if (short_line == "HepMC::Version 2")
            {
              HepMC_file_version = 2;
              break;
            }
            else if (short_line == "HepMC::Version 3")
            {
              // Check the text format
              std::getline(infile, line);
              std::string text_format = line.substr(0,14);
              if (text_format == "HepMC::Asciiv3")
              {
                HepMC_file_version = 3;
                break;
              }
              else if (text_format == "HepMC::IO_GenE")
              {
                HepMC_file_version = 2;
                break;
              }
              else
              {
                std::stringstream msg;
                msg <<  "Could not determine HepMC version from the string '" << text_format << "' extracted from the line '" << line << "'. Quitting...";
                ColliderBit_error().raise(LOCAL_INFO, msg.str());
              }
            }
            else
            {
              std::stringstream msg;
              msg << "Could not determine HepMC version from the string '" << short_line << "' extracted from the line '" << line << "'. Quitting...";
              ColliderBit_error().raise(LOCAL_INFO, msg.str());
            }
          }
        }
        first = false;
      }

      if(HepMC_file_version != 2 and HepMC_file_version != 3)
      {
        std::stringstream msg;
        msg << "Failed to determine HepMC version for input file " << HepMC_filename << ". Quitting...";
        ColliderBit_error().raise(LOCAL_INFO, msg.str());
      }

      static HepMC3::Reader *HepMCio;

      // Initialize the reader on the first iteration
      if (iteration == BASE_INIT)
      {
        if (HepMC_file_version == 2)
        {
          HepMCio = new HepMC3::ReaderAsciiHepMC2(HepMC_filename);
        }
        else
        {
          HepMCio = new HepMC3::ReaderAscii(HepMC_filename);
        }
      }

      // Delete the reader in the last iteration
      if (iteration == BASE_FINALIZE)
        delete HepMCio;

      // Don't do anything else during special iterations
      if (iteration < 0) return;

      #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "Event number: " << iteration << endl;
      #endif

      // Attempt to read the next HepMC event. If there are no more events, wrap up the loop and skip the rest of this iteration.
      bool event_retrieved = true;
      #pragma omp critical (reading_HepMCEvent)
      {
        event_retrieved = HepMCio->read_event(result);

        // FIXME This is a temp solution to ensure that the event reading
        //       stops when there are no more events in the HepMC file.
        //       Remove this once bugfix is implemented in HepMC.
        if ((result.particles().size() == 0) && (result.vertices().size() == 0)) event_retrieved = false;
      }
      if (not event_retrieved)
      {
        // Tell the MCLoopInfo instance that we have reached the end of the file
        RunMC.report_end_of_event_file();
        halt();
      }
      if (not event_retrieved) halt();

   }
    /// A nested function that reads in HepMC event files
    void getHepMCEvent(HepMC3::GenEvent& result)
    {
      using namespace Pipes::getHepMCEvent;

      // Get yaml options
      const static str HepMC_filename = runOptions->getValueOrDef<str>("", "hepmc_filename");

      // Get the HepMC event
      readHepMCEvent(result, HepMC_filename, *Dep::RunMC, *Loop::iteration, Loop::halt);

      // CBS uses Rivet's run-boundary convention: normalise the first event
      // and validate every physical event against its run conditions.
      if (*Loop::iteration >= 0)
      {
        if (runOptions->getValueOrDef<bool>(false, "cbs_normalize_hepmc_units"))
        {
          result.set_units(HepMC3::Units::GEV, HepMC3::Units::MM);
        }
        validate_cbs_event(result, *runOptions);
      }

    }

    /// A nested function that reads in HepMC event files and converts them to HEPUtils::Event format
    void getHepMCEvent_HEPUtils(HEPUtils::Event &result)
    {
      using namespace Pipes::getHepMCEvent_HEPUtils;

      // Get yaml options
      const static str HepMC_filename = runOptions->getValueOrDef<str>("", "hepmc_filename");
      const static double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");
      const parsed_jet_collection_settings parsed_collections = read_jet_collection_settings_from_options(*runOptions);
      const std::vector<jet_collection_settings>& all_jet_collection_settings = parsed_collections.collections;
      const str& jetcollection_taus = parsed_collections.jetcollection_taus;

      // Get the HepMC event
      //HepMC3::GenEvent ge = *Dep::HardScatteringEvent;
      HepMC3::GenEvent ge;
      readHepMCEvent(ge, HepMC_filename, *Dep::RunMC, *Loop::iteration, Loop::halt);

      //We need to not do anything else on special iterations, where an event has not actually been extracted:
      if (*Loop::iteration < 0) return;

      //Set the weight
      result.set_weight(ge.weight());

      //Translate to HEPUtils event by calling the unified HEPMC/Pythia event converter:
      Gambit::ColliderBit::convertParticleEvent(ge.particles(), result, all_jet_collection_settings, jetcollection_taus, jet_pt_min);

    }

    void convertHepMCEvent_HEPUtils(HEPUtils::Event &result)
    {
      using namespace Pipes::convertHepMCEvent_HEPUtils;

      //Don't do anything on special iterations: you'll just end up dereferencing a nullptr
      if (*Loop::iteration < 0) return;

      //HepMC Event should just be sitting waiting for us.
      HepMC3::GenEvent ge = *Dep::HardScatteringEvent;

      //Get yaml options required for conversion
      const static double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");
      const parsed_jet_collection_settings parsed_collections = read_jet_collection_settings_from_options(*runOptions);
      const std::vector<jet_collection_settings>& all_jet_collection_settings = parsed_collections.collections;
      const str& jetcollection_taus = parsed_collections.jetcollection_taus;

      //Set the weight
      result.set_weight(ge.weight());

      //Translate to HEPUtils event by calling the unified HEPMC/Pythia event converter:
      Gambit::ColliderBit::convertParticleEvent(ge.particles(), result, all_jet_collection_settings, jetcollection_taus, jet_pt_min);
    }

  }
}

#endif
