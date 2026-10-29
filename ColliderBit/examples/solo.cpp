//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  ColliderBit Solo: an event-based LHC recast
///  tool using the GAMBIT ColliderBit module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  (p.scott@imperial.ac.uk)
///  \date May 2019
///
///  \author Tomek Procter
///  (t.procter.1@research.gla.ac.uk)
///  \date November 2021
///
///  \author Pengxuan Zhu
///  (pengxuan.zhu@adelaide.edu.au)
///  \date Feburary 2025
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/analyses/AcceptedEvents.hpp"
#include "fastjet/ClusterSequence.hh"
#include "solo_batch.hpp"
#include "solo_cli.hpp"
#include "solo_input.hpp"
#include "solo_output.hpp"
// #include "gambit/Backends/backend_rollcall.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#define NULIKE_VERSION "1.0.9"
#define NULIKE_SAFE_VERSION 1_0_9

#define RIVET_VERSION "4.1.0"
#define RIVET_SAFE_VERSION 4_1_0
#define CONTUR_VERSION "3.0.0"
#define CONTUR_SAFE_VERSION 3_0_0

#define FULLLIKES_VERSION "1.0"
#define FULLLIKES_SAFE_VERSION 1_0

using namespace ColliderBit::Functown;
using namespace BackendIniBit::Functown;
using namespace CAT(Backends::nulike_,NULIKE_SAFE_VERSION)::Functown;
using namespace CAT(Backends::ATLAS_FullLikes_,FULLLIKES_SAFE_VERSION)::Functown;
using namespace CAT(Backends::Contur_,CONTUR_SAFE_VERSION)::Functown;
using namespace CAT(Backends::Rivet_,RIVET_SAFE_VERSION)::Functown;

namespace
{
  constexpr std::size_t cbs_screen_width = 80;

  class ScopedCoutSilencer
  {
    public:
      ScopedCoutSilencer()
        : saved_buffer(std::cout.rdbuf(discarded_output.rdbuf()))
      { }

      ~ScopedCoutSilencer()
      {
        std::cout.rdbuf(saved_buffer);
      }

      ScopedCoutSilencer(const ScopedCoutSilencer&) = delete;
      ScopedCoutSilencer& operator=(const ScopedCoutSilencer&) = delete;

    private:
      std::ostringstream discarded_output;
      std::streambuf* saved_buffer;
  };

  std::string format_analysis_list(const std::vector<std::string>& analyses)
  {
    if (analyses.empty()) return "(none)";

    std::ostringstream formatted;
    for (std::size_t index = 0; index < analyses.size(); ++index)
    {
      if (index != 0) formatted << ", ";
      formatted << analyses[index];
    }
    return formatted.str();
  }

  std::string format_cbs_startup_summary(
    const ColliderBit::SoloInput::PreparedInput& prepared_input,
    const std::vector<std::string>& enabled_analyses)
  {
    std::ostringstream summary;
    const std::size_t label_width = 20;

    summary << "\nCBS HepMC verification\n"
            << std::string(cbs_screen_width, '-') << '\n';

    std::map<std::string, std::string> file_colliders;
    for (const ColliderBit::SoloInput::ColliderInput& collider : prepared_input.colliders)
    {
      for (const std::string& filename : collider.hepmc_filenames) file_colliders[filename] = collider.name;
    }

    for (std::size_t index = 0; index < prepared_input.hepmc_filenames.size(); ++index)
    {
      const ColliderBit::SoloInput::HepMCRunInfo& run_info =
        prepared_input.hepmc_run_infos.at(index);
      std::ostringstream beams;
      beams << '(' << run_info.beam_pid_1 << ", " << run_info.beam_pid_2 << ')';
      summary << "  " << std::left << std::setw(label_width)
              << ("File " + std::to_string(index + 1) + "/"
                  + std::to_string(prepared_input.hepmc_filenames.size()))
              << ": " << prepared_input.hepmc_filenames.at(index) << '\n'
              << "  " << std::left << std::setw(label_width) << "Beam IDs"
              << ": " << beams.str() << '\n'
              << "  " << std::left << std::setw(label_width) << "Beam energies"
              << ": (" << ColliderBit::SoloOutput::format_screen_number(run_info.beam_energy_1_GeV)
              << ", "
              << ColliderBit::SoloOutput::format_screen_number(run_info.beam_energy_2_GeV)
              << ") GeV\n"
              << "  " << std::left << std::setw(label_width) << "sqrt(s)"
              << ": " << ColliderBit::SoloOutput::format_screen_number(run_info.collision_energy_TeV)
              << " TeV\n"
              << "  " << std::left << std::setw(label_width) << "Collider"
              << ": " << file_colliders[prepared_input.hepmc_filenames.at(index)] << '\n'
              << "  " << std::left << std::setw(label_width) << "Status"
              << ": verified\n";
      if (index + 1 != prepared_input.hepmc_filenames.size()) summary << '\n';
    }

    const std::size_t settings_indent_width = 2;
    std::size_t analysis_width = 25;
    const std::size_t status_width = 10;
    std::size_t reason_width = 39;
    const std::size_t settings_gap_width = 2;
    for (const auto& name : prepared_input.requested_analyses)
    {
      analysis_width = std::max(analysis_width, name.size());
      const auto collider = prepared_input.analysis_colliders.find(name);
      if (collider != prepared_input.analysis_colliders.end())
        reason_width = std::max(reason_width, collider->second.size());
      const auto reason = prepared_input.analysis_disable_reasons.find(name);
      if (reason != prepared_input.analysis_disable_reasons.end())
        reason_width = std::max(reason_width, reason->second.size());
    }
    const std::size_t settings_table_width = settings_indent_width + analysis_width
      + settings_gap_width + status_width + settings_gap_width + reason_width;

    summary << "\nCBS settings validation\n"
            << std::string(settings_table_width, '-') << '\n'
            << "  " << std::left << std::setw(label_width) << "Analyses"
            << ": " << prepared_input.requested_analyses.size() << " requested, "
            << enabled_analyses.size() << " enabled, "
            << prepared_input.requested_analyses.size() - enabled_analyses.size()
            << " disabled\n"
            << "  " << std::left << std::setw(analysis_width) << "Analysis"
            << std::string(settings_gap_width, ' ')
            << std::setw(status_width) << "Status"
            << std::string(settings_gap_width, ' ')
            << "Collider / reason\n"
            << "  " << std::string(analysis_width, '-')
            << std::string(settings_gap_width, ' ')
            << std::string(status_width, '-')
            << std::string(settings_gap_width, ' ')
            << std::string(reason_width, '-') << '\n';

    for (const std::string& requested_analysis : prepared_input.requested_analyses)
    {
      const bool enabled = std::find(
        enabled_analyses.begin(), enabled_analyses.end(), requested_analysis)
        != enabled_analyses.end();
      const auto reason_it = prepared_input.analysis_disable_reasons.find(requested_analysis);
      const std::string reason =
        (reason_it == prepared_input.analysis_disable_reasons.end())
          ? (enabled ? "-" : "reason unavailable")
          : reason_it->second;
      const auto collider_it = prepared_input.analysis_colliders.find(requested_analysis);
      const std::string collider =
        (collider_it == prepared_input.analysis_colliders.end()) ? "-" : collider_it->second;

      summary << "  " << std::left << std::setw(analysis_width)
              << requested_analysis
              << std::string(settings_gap_width, ' ')
              << std::setw(status_width) << (enabled ? "enabled" : "disabled")
              << std::string(settings_gap_width, ' ')
              << (enabled ? collider : reason) << '\n';
    }

    summary << std::string(settings_table_width, '-') << '\n';
    return summary.str();
  }

  /// Summarise a prepared collider, and the events analysed for it, for CBS output.
  ColliderBit::SoloOutput::ColliderSummaryEntry summarise_collider(
    const ColliderBit::SoloInput::ColliderInput& collider, long long n_events)
  {
    ColliderBit::SoloOutput::ColliderSummaryEntry entry;
    entry.name = collider.name;
    entry.beam_pid_1 = collider.run_info.beam_pid_1;
    entry.beam_pid_2 = collider.run_info.beam_pid_2;
    entry.beam_energy_1_GeV = collider.run_info.beam_energy_1_GeV;
    entry.beam_energy_2_GeV = collider.run_info.beam_energy_2_GeV;
    entry.collision_energy_TeV = collider.run_info.collision_energy_TeV;
    entry.n_files = collider.hepmc_filenames.size();
    entry.n_events = n_events;
    entry.cross_section_fb = collider.cross_section_fb;
    entry.cross_section_uncert_fb = collider.cross_section_uncert_fb;
    entry.analyses = collider.analyses;
    return entry;
  }

  /// Build the cross_sections option table read by the CBS cross-section functions.
  YAML::Node cbs_cross_section_table(const ColliderBit::SoloInput::ColliderInput& collider)
  {
    YAML::Node table;
    table[collider.name]["cross_section_fb"] = collider.cross_section_fb;
    table[collider.name]["cross_section_uncert_fb"] = collider.cross_section_uncert_fb;
    return table;
  }
  std::vector<ColliderBit::SoloOutput::SamplingAdviceEntry> make_sampling_advice(
    const ColliderBit::SoloBatch::MergedRunResult& merged,
    const ColliderBit::SoloInput::PreparedInput& prepared_input, const Options& settings)
  {
    const std::vector<ColliderBit::SoloBatch::AnalysisSamplingAdvice> batch_sampling_advice =
      ColliderBit::SoloBatch::build_sampling_advice(merged, prepared_input, settings);

    std::vector<ColliderBit::SoloOutput::SamplingAdviceEntry> output_sampling_advice;
    output_sampling_advice.reserve(batch_sampling_advice.size());
    for (const ColliderBit::SoloBatch::AnalysisSamplingAdvice& in_analysis : batch_sampling_advice)
    {
      ColliderBit::SoloOutput::SamplingAdviceEntry out_analysis;
      out_analysis.analysis_name = in_analysis.analysis_name;
      out_analysis.sr_label = in_analysis.sr_label;
      out_analysis.sr_index = in_analysis.sr_index;
      out_analysis.n_sig_scaled = in_analysis.n_sig_scaled;
      out_analysis.n_sig_scaled_err = in_analysis.n_sig_scaled_err;
      out_analysis.fractional_uncert = in_analysis.fractional_uncert;
      out_analysis.effective_events = in_analysis.effective_events;
      out_analysis.targets.reserve(in_analysis.targets.size());

      for (const ColliderBit::SoloBatch::SamplingTargetAdvice& in_target : in_analysis.targets)
      {
        ColliderBit::SoloOutput::SamplingAdviceTargetEntry out_target;
        out_target.target_fractional_uncert = in_target.target_fractional_uncert;
        out_target.need_more_mc = in_target.need_more_mc;
        out_target.current_fractional_uncert = in_target.current_fractional_uncert;
        out_target.scale_factor = in_target.scale_factor;
        out_target.current_total_events = in_target.current_total_events;
        out_target.recommended_total_events = in_target.recommended_total_events;
        out_target.recommended_additional_events = in_target.recommended_additional_events;
        out_target.process_recommendations.reserve(in_target.process_recommendations.size());

        for (const ColliderBit::SoloBatch::ProcessSamplingAdvice& in_process :
             in_target.process_recommendations)
        {
          ColliderBit::SoloOutput::SamplingAdviceProcessEntry out_process;
          out_process.process_name = in_process.process_name;
          out_process.cross_section_fb = in_process.cross_section_fb;
          out_process.processed_events = in_process.processed_events;
          out_process.recommended_additional_events = in_process.recommended_additional_events;
          out_target.process_recommendations.push_back(std::move(out_process));
        }

        out_analysis.targets.push_back(std::move(out_target));
      }

      output_sampling_advice.push_back(std::move(out_analysis));
    }
    return output_sampling_advice;
  }

  // contur-settings stores flags without the leading dashes.
  // convert_yaml_options_for_contur adds them before Contur parses argv.
  bool contur_names_its_log(const std::vector<std::string>& options)
  {
    for (const std::string& option : options)
    {
      std::string name = option;
      if (name.rfind("--", 0) == 0) name.erase(0, 2);
      else if (!name.empty() && name.front() == '-') name.erase(0, 1);
      const std::size_t equals = name.find('=');
      if (equals != std::string::npos) name.resize(equals);
      if (name == "log" || name == "l") return true;
    }
    return false;
  }

  // A single collider keeps Contur's usual contur.log name. Each collider in a
  // joint run, and each batch child, gets its own file so siblings do not clobber it.
  std::string contur_log_filename(const std::string& collider_name, bool per_collider)
  {
    if (!per_collider) return "contur.log";
    return "contur_" + collider_name + ".log";
  }

  // Must stay the name written by Rivet_measurements.
  std::string yoda_filename(const std::string& collider_name)
  {
    return "GAMBIT_collider_measurements_" + collider_name + ".yoda";
  }

  std::string path_in_directory(const std::string& directory, const std::string& name)
  {
    return (std::filesystem::path(directory) / name).lexically_normal().string();
  }

  void note_run_artifacts(
    ColliderBit::SoloOutput::OutputConfig& config,
    const std::string& collider_name,
    bool per_collider_log,
    bool redirect_contur_log)
  {
    if (config.run_directory.empty()) return;
    if (redirect_contur_log)
    {
      config.contur_logs.push_back(path_in_directory(
        config.run_directory, contur_log_filename(collider_name, per_collider_log)));
    }
    if (config.write_yoda_file)
    {
      config.yoda_files.push_back(path_in_directory(
        config.run_directory, yoda_filename(collider_name)));
    }
  }

}

// Helper function to check if setting in CBS yaml and then set it
template <typename Tsetting, typename Tresult>
bool apply_setting_if_present(const std::string &setting, Options& settings, Gambit::module_functor<Tresult> &the_functor)
{
  if (settings.hasKey(setting))
  {
    the_functor.template setOption<Tsetting>(setting, settings.getValue<Tsetting>(setting));
    return true;
  }
  return false;
}
/// ColliderBit Solo main program
int main(int argc, char* argv[])
{
  bool cbs_logs_initialised = false;
  try
  {
    ColliderBit::SoloCLI::CommandLineOptions command_line_options;
    const ColliderBit::SoloCLI::CommandLineStatus command_line_status =
      ColliderBit::SoloCLI::parse_command_line(argc, argv, command_line_options);

    if (command_line_status == ColliderBit::SoloCLI::CommandLineStatus::help)
    {
      logger().disable();
      return 0;
    }
    if (command_line_status == ColliderBit::SoloCLI::CommandLineStatus::list_analyses)
    {
      logger().disable();
      return ColliderBit::SoloCLI::print_analysis_list(
               std::cout, std::cerr, command_line_options.analysis_query) ? 0 : 1;
    }
    if (command_line_status == ColliderBit::SoloCLI::CommandLineStatus::error)
    {
      logger().disable();
      return 1;
    }

    const auto env_flag_enabled = [](const char* value) -> bool
    {
      if (value == nullptr) return false;
      if (std::strcmp(value, "1") == 0) return true;
      if (std::strcmp(value, "true") == 0) return true;
      if (std::strcmp(value, "TRUE") == 0) return true;
      if (std::strcmp(value, "yes") == 0) return true;
      if (std::strcmp(value, "YES") == 0) return true;
      if (std::strcmp(value, "on") == 0) return true;
      if (std::strcmp(value, "ON") == 0) return true;
      return false;
    };

    // Initialise required backends (static loadLibrary calls may be optimised
    // away at -O2, so we must trigger loading via the init functors explicitly).
    CAT_3(nulike_,NULIKE_SAFE_VERSION,_init).reset_and_calculate();

    // Make sure that nulike is present.
    if (not Backends::backendInfo().works[str("nulike")+NULIKE_VERSION]) backend_error().raise(LOCAL_INFO, str("nulike ")+NULIKE_VERSION+" is missing!");

    // Check if Rivet and Contur are there: permit runs without that don't ask for them:
    bool conturWorks = true;
    bool rivetWorks = true;
    if (not Backends::backendInfo().works[str("Contur")+CONTUR_VERSION]) { conturWorks = false;}
    if (not Backends::backendInfo().works[str("Rivet")+RIVET_VERSION]) { rivetWorks = false;}

    // Print the CBS startup banner once, unless suppressed for subprocess runs.
    const bool suppress_startup_banner = env_flag_enabled(std::getenv("CBS_SUPPRESS_BANNER"));
    if (!suppress_startup_banner)
    {
      cout << endl;
      cout << "==================================" << endl;
      cout << "||                              ||" << endl;
      cout << "||    CBS: ColliderBit Solo     ||" << endl;
      cout << "||  GAMBIT Collider Workgroup   ||" << endl;
      cout << "||                              ||" << endl;
      cout << "==================================" << endl;
      cout << endl;
    }

    // Read input file name
    const std::string& filename_in = command_line_options.filename;

    // Input preparation reads the first HepMC event, so initialise logs before
    // it in order to retain any run-condition failure in CBS_logs.
    // GAMBIT's generic logger prints an implementation-status line directly
    // to stdout.  CBS reports its own structured run summary below instead.
    {
      ScopedCoutSilencer silence_logger_initialisation;
      initialise_standalone_logs("CBS_logs/");
    }
    cbs_logs_initialised = true;

    // Read and prepare the settings in the input file
    ColliderBit::SoloInput::PreparedInput prepared_input;
    prepared_input = ColliderBit::SoloInput::parse_and_prepare_input(filename_in);

    YAML::Node infile;
    std::vector<str> analyses;
    Options settings;
    infile = prepared_input.infile;
    analyses = prepared_input.analyses;
    settings = prepared_input.settings;


    // Translate relevant settings into appropriate variables
    bool debug = settings.getValueOrDef<bool>(false, "debug");

    // Initialise logs before reporting input validation results.  This is also
    // before batch-mode dispatch, so both CBS execution paths report them.
    logger().set_log_debug_messages(debug);
    logger()<<"Running CBS"<<LogTags::info<<EOM;
    for (std::size_t index = 0; index < prepared_input.hepmc_filenames.size(); ++index)
    {
      const ColliderBit::SoloInput::HepMCRunInfo& run_info =
        prepared_input.hepmc_run_infos.at(index);
      std::ostringstream message;
      message<<"CBS HepMC file "<<(index + 1)<<"/"<<prepared_input.hepmc_filenames.size()
             <<": "<<prepared_input.hepmc_filenames[index]
             <<"; beams ("<<run_info.beam_pid_1<<", "<<run_info.beam_pid_2<<") at ("
             <<ColliderBit::SoloOutput::format_screen_number(run_info.beam_energy_1_GeV)<<", "
             <<ColliderBit::SoloOutput::format_screen_number(run_info.beam_energy_2_GeV)
             <<") GeV; sqrt(s) = "
             <<ColliderBit::SoloOutput::format_screen_number(run_info.collision_energy_TeV)
             <<" TeV; verified.";
      logger()<<LogTags::info<<message.str()<<EOM;
    }
    logger()<<LogTags::info<<"CBS run-condition tolerances: sqrt(s) "
            <<ColliderBit::SoloOutput::format_screen_number(
                settings.getValueOrDef<double>(1.0, "collision_energy_tolerance_GeV"))
            <<" GeV; beam energies "
            <<ColliderBit::SoloOutput::format_screen_number(
                settings.getValueOrDef<double>(1.0, "beam_energy_tolerance_GeV"))
            <<" GeV or "
            <<ColliderBit::SoloOutput::format_screen_number(
                settings.getValueOrDef<double>(1.0e-3, "beam_energy_relative_tolerance"))
            <<" relative."<<EOM;
    for (const ColliderBit::SoloInput::ColliderInput& collider : prepared_input.colliders)
    {
      logger()<<LogTags::info<<"CBS collider "<<collider.name<<": sqrt(s) = "
              <<ColliderBit::SoloOutput::format_screen_number(collider.run_info.collision_energy_TeV)
              <<" TeV; "<<collider.hepmc_filenames.size()
              <<" HepMC file(s); cross section "
              <<ColliderBit::SoloOutput::format_screen_number(collider.cross_section_fb)<<" +/- "
              <<ColliderBit::SoloOutput::format_screen_number(collider.cross_section_uncert_fb)
              <<" fb; analyses ("<<collider.analyses.size()<<"): "
              <<format_analysis_list(collider.analyses)<<EOM;
    }
    logger()<<LogTags::info<<"CBS native analyses requested ("
            <<prepared_input.requested_analyses.size()<<"): "
            <<format_analysis_list(prepared_input.requested_analyses)<<EOM;
    logger()<<LogTags::info<<"CBS native analyses enabled after run-condition matching ("
            <<analyses.size()<<"): "<<format_analysis_list(analyses)<<EOM;
    if (!suppress_startup_banner)
    {
      logger()<<LogTags::repeat_to_cout<<LogTags::info
              <<format_cbs_startup_summary(
                  prepared_input,
                  analyses)
              <<EOM;
    }
    for (const str& warning : prepared_input.analysis_warnings)
    {
      if (!suppress_startup_banner)
      {
        logger()<<LogTags::repeat_to_cerr<<LogTags::warn<<warning<<EOM;
      }
      else
      {
        logger()<<LogTags::warn<<warning<<EOM;
      }
    }
    if (analyses.empty())
    {
      throw std::runtime_error(
        "No requested analyses remain after CBS validation and run-condition filtering. "
        "Select analyses marked Validation: passed whose beam/run metadata matches the HepMC input.");
    }

    // CBS provides its own concise startup output.
    fastjet::ClusterSequence::set_fastjet_banner_stream(nullptr);
    bool use_FullLikes = settings.getValueOrDef<bool>(false, "use_FullLikes");
    module_functor<ColliderBit::map_str_AnalysisLogLikes>* calcLogLikes =
      use_FullLikes ? &calc_LHC_LogLikes_full : &calc_LHC_LogLikes;
    if (use_FullLikes)
    {
      CAT_3(ATLAS_FullLikes_,FULLLIKES_SAFE_VERSION,_init).reset_and_calculate();
      if (not Backends::backendInfo().works[str("ATLAS_FullLikes") + FULLLIKES_VERSION]) backend_error().raise(LOCAL_INFO, str("ATLAS_FullLikes ")+FULLLIKES_VERSION" is missing!");
    }

    bool use_lnpiln = settings.getValueOrDef<bool>(false, "use_lognormal_distribution_for_1d_systematic");
    // Single runtime cutflow switch for CBS. Cutflow filling relies on extra
    // per-event bookkeeping compiled only when CMake CUTFLOW is enabled.
    const bool requested_check_cutflow = settings.getValueOrDef<bool>(false, "check_cutflow");
#ifdef CHECK_CUTFLOW
    const bool check_cutflow = requested_check_cutflow;
#else
    const bool check_cutflow = false;
    if (requested_check_cutflow)
    {
      std::cerr
        << "WARNING: check_cutflow was requested, but this CBS binary was built "
        << "without CUTFLOW support. Reconfigure with -DCUTFLOW=ON to enable it."
        << std::endl;
    }
#endif
    ColliderBit::Cutflow::set_check_cutflow(check_cutflow);

    // Runtime histogram switch for CBS.
    const bool check_histogram = settings.getValueOrDef<bool>(false, "check_histogram");
    ColliderBit::Histogram1D::set_check_histogram(check_histogram);
    double jet_pt_min = settings.getValueOrDef<double>(10.0, "jet_pt_min");

    // Extract the jet collections yaml node
    YAML::Node jet_collections = settings.getValue<YAML::Node>("jet_collections");
    std::string jet_collection_taus = settings.getValueOrDef<std::string>("antikt_R04", "jet_collection_taus");

    // Check if Rivet & Contur requested and/or enabled then extract options from yaml
    bool withRivet;
    bool withContur;
    Options rivet_settings;
    std::vector<std::string> contur_options;
    try
    {
      if (infile["rivet-settings"])
      {
        withRivet = true;
        rivet_settings = Options(infile["rivet-settings"]);
      } else {withRivet = false;}
      // TODO: Should we just assume contur with no options if rivet settings are specified and Contur not?
      if (infile["contur-settings"])
      {
        withContur = true;
        contur_options = infile["contur-settings"].as<std::vector<std::string>>();
      }
      else
      {
        withContur = false;
      }
      // Throw out cases where things won't work, with informative errors:
      if (withContur && !withRivet)
      {
        throw std::runtime_error("Can't run contur without rivet. Try adding a rivet-settings section to your yaml-file. Quitting...");
      }
      else if (!withContur && withRivet)
      {
        throw std::runtime_error("Can't run rivet without contur. Try adding a contur-settings section to your yaml-file. Quitting...");
      }
      else if (withContur && !conturWorks)
      {
        backend_error().raise(LOCAL_INFO, str("yaml file requests contur, but Contur ")+CONTUR_VERSION+" is missing!");
      }
      else if (withRivet && !rivetWorks)
      {
        backend_error().raise(LOCAL_INFO, str("yaml file requests rivet, but Rivet ")+RIVET_VERSION+" is missing!");
      }
      else if (withContur && withRivet)
      {
        // Ok, we're good to go with Rivet and Contur,
        // TODO: Proper citation message?
        std::cout << "\nUsing RIVET " << RIVET_VERSION << " and CONTUR " <<
          CONTUR_VERSION << " on this run.\n";
      }
    }
    catch (YAML::Exception &e)
    {
      throw std::runtime_error("YAML error in "+filename_in+".\n(yaml-cpp error: "+std::string(e.what())+" )");
    }

    if (withRivet)
    {
      const std::vector<std::string> rivet_analyses =
        rivet_settings.getValue<std::vector<std::string>>("analyses");
      logger()<<LogTags::info<<"CBS Rivet analyses requested ("<<rivet_analyses.size()<<"): "
              <<format_analysis_list(rivet_analyses)<<EOM;
      if (!suppress_startup_banner)
      {
        logger()<<LogTags::repeat_to_cout<<LogTags::info
                <<"CBS Rivet: "<<rivet_analyses.size()
                <<" requested analyses; Rivet will apply first-event beam matching."
                <<EOM;
      }
    }

    ColliderBit::SoloOutput::OutputConfig output_config;
    output_config.screen_output = settings.getValueOrDef<bool>(true, "screen_output");
    std::string report_value = settings.getValueOrDef<std::string>("summary", "report");
    if (command_line_options.has_report)
    {
      if (settings.hasKey("report"))
      {
        const std::string yaml_report = settings.getValue<std::string>("report");
        if (yaml_report != command_line_options.report)
        {
          std::cerr << "CBS: --report=" << command_line_options.report
                    << " overrides settings.report=" << yaml_report << std::endl;
        }
      }
      report_value = command_line_options.report;
    }
    output_config.screen_report = ColliderBit::SoloOutput::screen_report_from_string(report_value);
    output_config.write_file = settings.hasKey("output");
    if (output_config.write_file)
    {
      output_config.output_file = settings.getValueOrDef<std::string>("CBS_output.json", "output");
    }
    ColliderBit::SoloOutput::validate_output_config(output_config);

    // Group the JSON, Contur log and optional YODA beside settings.output.
    // A batch child receives that directory as artifact_directory and must not
    // treat its temporary JSON path as the run directory.
    const bool batch_child = settings.hasKey("cbs_collider_name");
    if (batch_child) output_config.announce_outputs = false;
    if (settings.hasKey("artifact_directory"))
    {
      output_config.run_directory = settings.getValue<std::string>("artifact_directory");
    }
    else if (!batch_child && output_config.write_file)
    {
      output_config.run_directory =
        ColliderBit::SoloOutput::prepare_output_directory(output_config.output_file);
    }
    if (withRivet)
    {
      if (rivet_settings.hasKey("write_YODA_file"))
      {
        output_config.write_yoda_file = rivet_settings.getValue<bool>("write_YODA_file");
      }
      else if (rivet_settings.hasKey("drop_YODA_file"))
      {
        output_config.write_yoda_file = rivet_settings.getValue<bool>("drop_YODA_file");
        if (!batch_child)
        {
          std::cerr << "CBS: rivet-settings.drop_YODA_file is accepted as write_YODA_file "
                    << "(true writes the YODA file)." << std::endl;
        }
      }
    }
    const bool per_collider_contur_log =
      batch_child || prepared_input.colliders.size() > 1;
    const bool redirect_contur_log = withContur
      && !output_config.run_directory.empty()
      && !contur_names_its_log(contur_options);

    // Isolate colliders in fresh child tasks; within a collider all files and
    // processes share one normalised event loop, with or without measurements.
    const bool joint_measurements = withRivet && withContur;
    if (!prepared_input.processes.empty() && prepared_input.colliders.size() > 1)
    {

      double (*marginaliser)(const int&, const double&, const double&, const double&) =
        use_lnpiln
          ? nulike_lnpiln.handoutFunctionPointer()
          : nulike_lnpin.handoutFunctionPointer();

      bool (*fullLikesFileExists)(const str&) =
        use_FullLikes ? FullLikes_FileExists.handoutFunctionPointer() : nullptr;
      int (*fullLikesReadIn)(const str&, const str&, const str&) =
        use_FullLikes ? FullLikes_ReadIn.handoutFunctionPointer() : nullptr;
      double (*fullLikesEvaluate)(std::map<str,double>&, const str&) =
        use_FullLikes ? FullLikes_Evaluate.handoutFunctionPointer() : nullptr;

      ColliderBit::SoloBatch::MergedRunResult merged =
        ColliderBit::SoloBatch::run_joint_colliders(
        argv[0],
        prepared_input,
        settings,
        marginaliser,
        fullLikesFileExists,
        fullLikesReadIn,
        fullLikesEvaluate
      );

      const auto output_sampling_advice = make_sampling_advice(merged, prepared_input, settings);

      for (const ColliderBit::SoloInput::ColliderInput& collider_input : prepared_input.colliders)
      {
        note_run_artifacts(
          output_config, collider_input.name, per_collider_contur_log, redirect_contur_log);
      }

      std::vector<ColliderBit::SoloOutput::ColliderSummaryEntry> collider_summaries;
      for (const ColliderBit::SoloInput::ColliderInput& collider : prepared_input.colliders)
      {
        const auto events_it = merged.collider_event_counts.find(collider.name);
        collider_summaries.push_back(summarise_collider(
          collider, events_it == merged.collider_event_counts.end() ? 0 : events_it->second));
      }

      ColliderBit::SoloOutput::emit_outputs(
        output_config,
        merged.total_events,
        collider_summaries,
        merged.combined_loglike,
        merged.analyses,
        merged.analysis_loglikes,
        joint_measurements,
        merged.contur_loglike,
        merged.contur_pool_loglikes,
        merged.contur_pool_info,
        output_sampling_advice,
        merged.input_files,
        &merged.input_loop,
        merged.rivet_analyses
      );
      return 0;
    }

    // One logical collider may contain multiple processes and source files.
    // Other colliders are isolated in fresh child tasks to keep functor state local.
    if (prepared_input.colliders.size() != 1)
    {
      throw std::runtime_error("A CBS event_file run must define exactly one collider.");
    }
    const ColliderBit::SoloInput::ColliderInput& collider = prepared_input.colliders.front();

    auto& getEvent = getHepMCEvent;
    auto& convertEvent = convertHepMCEvent_HEPUtils;
    auto& AnalysisNumbers = CollectAnalyses;
    AnalysisNumbers.setOption<bool>("check_cutflow", check_cutflow);
    // CBS renders the retained cutflows once, as part of its final formatted
    // summary.  Keep collection enabled above, but suppress the raw eventloop
    // copy (and therefore every batch subprocess copy).
    AnalysisNumbers.setOption<bool>("print_cutflows", false);
    AnalysisNumbers.setOption<bool>("normalized_cutflows", false);

    // Record and export the same acceptance matrix as full ColliderBit.
    // Batch children inherit this setting and append their completed-event rows.
    const bool drop_accepted_events_file = settings.getValueOrDef<bool>(false, "drop_accepted_events_file");
    const bool record_event_ids = drop_accepted_events_file || settings.getValueOrDef<bool>(false, "trace_input_events");
    getATLASAnalysisContainer.setOption<bool>("drop_accepted_events_file", record_event_ids);
    getCMSAnalysisContainer.setOption<bool>("drop_accepted_events_file", record_event_ids);
    getIdentityAnalysisContainer.setOption<bool>("drop_accepted_events_file", record_event_ids);

    // Initialise settings for printer (required)
    YAML::Node printerNode = get_standalone_printer("cout", "CBS_logs/", "");
    Printers::PrinterManager printerManager(printerNode, false);
    set_global_printer_manager(&printerManager);

    // Initialise the random number generator, using a hardware seed if no seed is given in the input file.
    int seed = settings.getValueOrDef<int>(-1, "seed");
    Random::create_rng_engine("default", seed);

    long long expected_events = 0;
    for (const auto& file : collider.hepmc_filenames)
      expected_events += prepared_input.input_statistics.at(file).n_events;
    if (expected_events <= 0 || expected_events > std::numeric_limits<int>::max())
      throw std::runtime_error("CBS input event count is outside the supported integer range.");
    if (joint_measurements && collider.cross_section_fb <= 0.0)
      throw std::runtime_error("Rivet/Contur requires a positive process mixture cross section.");
    YAML::Node input_files(YAML::NodeType::Sequence);
    std::vector<ColliderBit::SoloOutput::InputFileSummaryEntry> input_summaries;
    for (const auto& file : collider.hepmc_filenames)
    {
      const auto& statistics = prepared_input.input_statistics.at(file);
      double process_sigma = collider.cross_section_fb;
      double process_uncert = collider.cross_section_uncert_fb;
      double denominator = statistics.sum_weights;
      str process_name = "event_file";
      for (const auto& process : prepared_input.processes)
        for (const auto& source : process.files)
          if (source.filename == file)
          {
            process_name = process.name;
            process_sigma = process.cross_section_fb;
            process_uncert = process.cross_section_uncert_fb;
            denominator = 0.0;
            for (const auto& sibling : process.files)
              denominator += prepared_input.input_statistics.at(sibling.filename).sum_weights;
          }
      if (!(denominator > 0.0) || !std::isfinite(denominator))
        throw std::runtime_error("Invalid total nominal weight for process " + process_name);
      const double scale = collider.cross_section_fb > 0.0
        ? (expected_events / denominator) * (process_sigma / collider.cross_section_fb)
        : expected_events / denominator;
      if (!std::isfinite(scale) || scale < 0.0 || (process_sigma > 0.0 && scale == 0.0))
        throw std::runtime_error("Invalid nominal-weight normalization for process " + process_name);
      YAML::Node source;
      source["file"] = file;
      source["n_events"] = statistics.n_events;
      source["weight_scale"] = scale;
      input_files.push_back(source);
      input_summaries.push_back({file, process_name, collider.name, statistics.n_events,
                                statistics.sum_weights, statistics.sum_weights2,
                                statistics.nominal_name, statistics.nominal_index, scale, process_sigma, process_uncert});
    }
    getEvent.setOption<YAML::Node>("cbs_inputs", input_files);
    getEvent.setOption<str>("nominal_weight_name", settings.getValueOrDef<str>("", "nominal_weight_name"));
    getEvent.setOption<bool>("trace_input_events", settings.getValueOrDef<bool>(false, "trace_input_events"));
    getEvent.setOption<double>("cbs_cross_section_pb", collider.cross_section_fb / 1000.0);
    getEvent.setOption<double>("cbs_cross_section_uncert_pb", collider.cross_section_uncert_fb / 1000.0);

    // Input preflight fixes the exact logical count. No intermediate EOF is
    // submitted as an analysis iteration and source boundaries need no barrier:
    // every event already has the same nominal convention and physical xsec.
    YAML::Node CBS(infile["settings"]);
    CBS["analyses"] = collider.analyses;
    CBS["min_nEvents"] = expected_events;
    CBS["max_nEvents"] = expected_events;
    // CBS policy: always process all events provided by the user (no convergence-based early stop).
    CBS["run_convergence_checks"] = false;
    // Emit a compact progress indicator after each completed event block.
    // The event loop itself remains quiet; this is the only intentional live output.
    CBS["show_event_progress"] = settings.getValueOrDef<bool>(
      output_config.screen_output, "hepmc_progress"
    );
    const std::string default_event_progress_label =
      "CBS HepMC (" + std::to_string(prepared_input.hepmc_filenames.size()) + " input files)";
    CBS["event_progress_label"] = settings.getValueOrDef<std::string>(
      default_event_progress_label, "event_progress_label");
    operateLHCLoop.setOption<YAML::Node>(collider.name, CBS);
    operateLHCLoop.setOption<bool>("silenceLoop", not debug);
    operateLHCLoop.setOption<std::vector<std::string>>("use_colliders", {collider.name});

    // Pass the event filename and the jet pt cutoff to the HepMC reader/HEPUtils converter function
    getEvent.setOption<str>("hepmc_filename", prepared_input.hepmc_filenames.front());
    convertEvent.setOption<double>("jet_pt_min", jet_pt_min);

    // CBS follows Rivet's run-condition convention: the first physical event
    // defines the run, and every later event must keep the same beams and sqrt(s).
    getEvent.setOption<bool>("cbs_normalize_hepmc_units", true);
    getEvent.setOption<bool>("cbs_check_hepmc_run", true);
    getEvent.setOption<std::vector<int>>(
      "cbs_reference_beam_ids",
      {collider.run_info.beam_pid_1, collider.run_info.beam_pid_2}
    );
    getEvent.setOption<std::vector<double>>(
      "cbs_reference_beam_energies_GeV",
      {collider.run_info.beam_energy_1_GeV, collider.run_info.beam_energy_2_GeV}
    );
    getEvent.setOption<double>("cbs_reference_collision_energy_TeV",
                               collider.run_info.collision_energy_TeV);
    getEvent.setOption<double>(
      "cbs_collision_energy_tolerance_TeV",
      settings.getValueOrDef<double>(1.0, "collision_energy_tolerance_GeV") / 1000.0
    );
    getEvent.setOption<double>(
      "cbs_beam_energy_tolerance_GeV",
      settings.getValueOrDef<double>(1.0, "beam_energy_tolerance_GeV")
    );
    getEvent.setOption<double>(
      "cbs_beam_energy_relative_tolerance",
      settings.getValueOrDef<double>(1.0e-3, "beam_energy_relative_tolerance")
    );

    // Pass the jet collections yaml node to the hepMC reader/HEPUtils converter function
    getEvent.setOption<std::string>("jet_collection_taus", jet_collection_taus);
    getEvent.setOption<YAML::Node>("jet_collections", jet_collections);
    convertEvent.setOption<std::string>("jet_collection_taus", jet_collection_taus);
    convertEvent.setOption<YAML::Node>("jet_collections", jet_collections);

    // Pass the collider's total cross-section to the CBS cross-section functions
    InitialTotalCrossSection_CBS.setOption<YAML::Node>("cross_sections", cbs_cross_section_table(collider));
    TotalCrossSection_CBS.setOption<YAML::Node>("cross_sections", cbs_cross_section_table(collider));

    // Pass options to the likelihood function
    // TODO: I'm not specifying the defaults here. I'll add the argument only if the user supplies it.
    // ColliderBit can then fall back to its defaults if nothing is supplied.
    apply_setting_if_present<bool>("use_covariances", settings, *calcLogLikes);//Default true
    apply_setting_if_present<bool>("use_marginalising", settings, *calcLogLikes);//Default False
    apply_setting_if_present<bool>("combine_SRs_without_covariances", settings, *calcLogLikes);//Default False

    apply_setting_if_present<double>("nuisance_prof_initstep", settings, *calcLogLikes);//Default 0.1
    apply_setting_if_present<double>("nuisance_prof_convtol", settings, *calcLogLikes);//Default 0.01
    apply_setting_if_present<int>("nuisance_prof_maxsteps", settings, *calcLogLikes);//Default 10000
    apply_setting_if_present<double>("nuisance_prof_convacc", settings, *calcLogLikes);//Default 0.01
    apply_setting_if_present<double>("nuisance_prof_simplexsize", settings, *calcLogLikes);//Default 1e-5
    apply_setting_if_present<int>("nuisance_prof_method", settings, *calcLogLikes);//Default 6

    apply_setting_if_present<double>("nuisance_marg_convthres_abs", settings, *calcLogLikes);//Default 0.05
    apply_setting_if_present<double>("nuisance_marg_convthres_rel", settings, *calcLogLikes);//Default 0.05
    apply_setting_if_present<long>("nuisance_marg_nsamples_start", settings, *calcLogLikes);//Default 1000000
    apply_setting_if_present<bool>("nuisance_marg_nulike1sr", settings, *calcLogLikes);//Default true

    apply_setting_if_present<bool>("calc_noerr_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_expected_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_expected_noerr_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<bool>("calc_scaledsignal_loglikes", settings, *calcLogLikes);//Default false
    apply_setting_if_present<double>("signal_scalefactor", settings, *calcLogLikes);//Default 1.0

    apply_setting_if_present<str>("alt_loglike", settings, calc_combined_LHC_LogLike);
    apply_setting_if_present<bool>("cap_loglike", settings, calc_combined_LHC_LogLike);
    apply_setting_if_present<bool>("cap_loglike_individual_analyses", settings, calc_combined_LHC_LogLike);
    calc_combined_LHC_LogLike.setSubCap<std::vector<str>>("skip_analyses",
      settings.getValueOrDef<std::vector<str>>({}, "skip_analyses"));

    // If Rivet/Contur, set Rivet/Contur options
    if (withRivet)
    {
      Rivet_measurements.setOption<bool>("write_YODA_file", output_config.write_yoda_file);
      if (!output_config.run_directory.empty())
      {
        Rivet_measurements.setOption<std::string>(
          "YODA_output_directory", output_config.run_directory);
      }
      Rivet_measurements.setOption<bool>("runningStandalone", true);
      Rivet_measurements.setOption<double>("cbs_cross_section_pb", collider.cross_section_fb / 1000.0);
      Rivet_measurements.setOption<double>("cbs_cross_section_uncert_pb", collider.cross_section_uncert_fb / 1000.0);
      Rivet_measurements.setOption<std::vector<std::string>>("analyses",
                                                rivet_settings.getValue<std::vector<std::string>>("analyses"));
      Rivet_measurements.setOption<std::vector<std::string>>("exclude_analyses",
                                                rivet_settings.getValueOrDef<std::vector<std::string>>({},"exclude_analyses"));
      note_run_artifacts(
        output_config, collider.name, per_collider_contur_log, redirect_contur_log);
      if (redirect_contur_log)
        contur_options.push_back("log=" + output_config.contur_logs.back());
      Contur_LHC_measurements_from_stream.setOption("contur_options", contur_options);
    }


    // Resolve ColliderBit dependencies and backend requirements
    convertEvent.resolveDependency(&getEvent);
    calc_combined_LHC_LogLike.resolveDependency(calcLogLikes);
    calc_combined_LHC_LogLike.resolveDependency(&operateLHCLoop);
    get_LHC_LogLike_per_analysis.resolveDependency(calcLogLikes);
    calcLogLikes->resolveDependency(&CollectAnalyses);
    calcLogLikes->resolveDependency(&operateLHCLoop);
    calcLogLikes->resolveDependency(&InitialTotalCrossSection_CBS);
    operateLHCLoop.resolveDependency(&InitialTotalCrossSection_CBS);
    calcLogLikes->resolveBackendReq(use_lnpiln ? &nulike_lnpiln : &nulike_lnpin);
    if (use_FullLikes)
    {
      calcLogLikes->resolveBackendReq(&FullLikes_FileExists);
      calcLogLikes->resolveBackendReq(&FullLikes_ReadIn);
      calcLogLikes->resolveBackendReq(&FullLikes_Evaluate);
    }
    CollectAnalyses.resolveDependency(&runATLASAnalyses);
    CollectAnalyses.resolveDependency(&runCMSAnalyses);
    CollectAnalyses.resolveDependency(&runIdentityAnalyses);
    CollectAnalyses.resolveDependency(&TotalCrossSection_CBS);
    runATLASAnalyses.resolveDependency(&getATLASAnalysisContainer);
    runATLASAnalyses.resolveDependency(&smearEventATLAS);
    runCMSAnalyses.resolveDependency(&getCMSAnalysisContainer);
    runCMSAnalyses.resolveDependency(&smearEventCMS);
    runIdentityAnalyses.resolveDependency(&getIdentityAnalysisContainer);
    runIdentityAnalyses.resolveDependency(&copyEvent);
    getATLASAnalysisContainer.resolveDependency(&TotalCrossSection_CBS);
    getCMSAnalysisContainer.resolveDependency(&TotalCrossSection_CBS);
    getIdentityAnalysisContainer.resolveDependency(&TotalCrossSection_CBS);
    smearEventATLAS.resolveDependency(&getBuckFastATLAS);
    smearEventATLAS.resolveDependency(&convertEvent);
    smearEventCMS.resolveDependency(&getBuckFastCMS);
    smearEventCMS.resolveDependency(&convertEvent);
    copyEvent.resolveDependency(&getBuckFastIdentity);
    copyEvent.resolveDependency(&convertEvent);
    // If using Rivet/Contur, resolve Rivet/Contur dependencies:
    if (withRivet)
    {
      Rivet_measurements.resolveDependency(&getEvent);
      Rivet_measurements.resolveBackendReq(&Contur_get_analyses_from_beam);

      Contur_LHC_measurements_from_stream.resolveDependency(&Rivet_measurements);
      Contur_LHC_measurements_from_stream.resolveBackendReq(&Contur_LogLike_from_stream);
      Contur_LHC_measurements_LogLike.resolveDependency(&Contur_LHC_measurements_from_stream);
      Contur_LHC_measurements_LogLike_perPool.resolveDependency(&Contur_LHC_measurements_from_stream);
      Contur_LHC_measurements_histotags_perPool.resolveDependency(&Contur_LHC_measurements_from_stream);
    }

    // Resolve loop manager for ColliderBit event loop
    getEvent.resolveLoopManager(&operateLHCLoop);
    convertEvent.resolveLoopManager(&operateLHCLoop);
    getBuckFastATLAS.resolveLoopManager(&operateLHCLoop);
    getBuckFastCMS.resolveLoopManager(&operateLHCLoop);
    getBuckFastIdentity.resolveLoopManager(&operateLHCLoop);
    TotalCrossSection_CBS.resolveLoopManager(&operateLHCLoop);
    getATLASAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getCMSAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getIdentityAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    smearEventATLAS.resolveLoopManager(&operateLHCLoop);
    smearEventCMS.resolveLoopManager(&operateLHCLoop);
    copyEvent.resolveLoopManager(&operateLHCLoop);
    runATLASAnalyses.resolveLoopManager(&operateLHCLoop);
    runCMSAnalyses.resolveLoopManager(&operateLHCLoop);
    runIdentityAnalyses.resolveLoopManager(&operateLHCLoop);
    std::vector<functor*> nested_functions = initVector<functor*>(&getEvent,
                                                                  &convertEvent,
                                                                  &getBuckFastATLAS,
                                                                  &getBuckFastCMS,
                                                                  &getBuckFastIdentity,
                                                                  &TotalCrossSection_CBS,
                                                                  &getATLASAnalysisContainer,
                                                                  &getCMSAnalysisContainer,
                                                                  &getIdentityAnalysisContainer,
                                                                  &smearEventATLAS,
                                                                  &smearEventCMS,
                                                                  &copyEvent,
                                                                  &runATLASAnalyses,
                                                                  &runCMSAnalyses,
                                                                  &runIdentityAnalyses);
    // If using contur and rivet:
    if (withRivet)
    {
      Rivet_measurements.resolveLoopManager(&operateLHCLoop);
      Contur_LHC_measurements_from_stream.resolveLoopManager(&operateLHCLoop);

      nested_functions.push_back(&Rivet_measurements);
      nested_functions.push_back(&Contur_LHC_measurements_from_stream);
    }

    operateLHCLoop.setNestedList(nested_functions);

    // Call the initialisation function for remaining backends
    // (nulike and optional ATLAS_FullLikes are already initialised before the works[] checks above)
    if (withRivet)
    {
      CAT_3(Rivet_, RIVET_SAFE_VERSION,_init).reset_and_calculate();
      CAT_3(Contur_, CONTUR_SAFE_VERSION,_init).reset_and_calculate();
    }

    // Run the detector sim and selected analyses on all the events read in.
    InitialTotalCrossSection_CBS.reset_and_calculate();
    operateLHCLoop.reset_and_calculate();
    CollectAnalyses.reset_and_calculate();
    if (drop_accepted_events_file)
      ColliderBit::export_accepted_events(CollectAnalyses(0), operateLHCLoop(0).completed_event_ids);
    calcLogLikes->reset_and_calculate();
    get_LHC_LogLike_per_analysis.reset_and_calculate();
    calc_combined_LHC_LogLike.reset_and_calculate();
    if (withContur)
    {
      Contur_LHC_measurements_LogLike.reset_and_calculate();
      Contur_LHC_measurements_LogLike_perPool.reset_and_calculate();
      Contur_LHC_measurements_histotags_perPool.reset_and_calculate();
    }

    const int n_events = operateLHCLoop(0).event_count.at(collider.name);
    if (n_events != expected_events)
      throw std::runtime_error("CBS did not complete every validated input event; no partial result is written.");
    for (const auto& file : collider.hepmc_filenames)
    {
      const auto& observed = operateLHCLoop(0).input_file_statistics.at(file);
      const auto& expected = prepared_input.input_statistics.at(file);
      if (std::filesystem::file_size(file) != expected.size_bytes
          || std::filesystem::last_write_time(file).time_since_epoch().count() != expected.modified_ticks
          || observed.n_events != expected.n_events
          || std::abs(observed.sum_weights - expected.sum_weights) > 1e-10 * expected.sum_weights
          || std::abs(observed.sum_weights2 - expected.sum_weights2) > 1e-10 * expected.sum_weights2)
        throw std::runtime_error("HepMC input changed after validation: " + file);
    }
    const double loglike = calc_combined_LHC_LogLike(0);

    std::map<std::string, double> contur_pool_loglikes;
    std::map<std::string, std::string> contur_pool_info;
    double contur_total_loglike = 0.0;
    if (withContur)
    {
      contur_total_loglike = Contur_LHC_measurements_LogLike(0);
      contur_pool_loglikes = Contur_LHC_measurements_LogLike_perPool(0);
      contur_pool_info = Contur_LHC_measurements_histotags_perPool(0);
    }

    const auto& analysis_results = CollectAnalyses(0);
    const auto& analysis_loglikes = (*calcLogLikes)(0);

    ColliderBit::SoloBatch::MergedRunResult sampling;
    sampling.total_events = n_events;
    sampling.total_process_events = n_events;
    sampling.analyses = analysis_results;
    sampling.analysis_loglikes = analysis_loglikes;
    sampling.collider_event_counts[collider.name] = n_events;
    sampling.process_event_counts.resize(prepared_input.processes.size(), 0);
    for (std::size_t i = 0; i < prepared_input.processes.size(); ++i)
      for (const auto& file : prepared_input.processes[i].files)
        sampling.process_event_counts[i] += prepared_input.input_statistics.at(file.filename).n_events;
    const auto sampling_advice = make_sampling_advice(sampling, prepared_input, settings);

    ColliderBit::SoloOutput::emit_outputs(
      output_config,
      n_events,
      {summarise_collider(collider, n_events)},
      loglike,
      analysis_results,
      analysis_loglikes,
      withContur,
      contur_total_loglike,
      contur_pool_loglikes,
      contur_pool_info,
      sampling_advice, input_summaries, &operateLHCLoop(0), operateLHCLoop(0).rivet_analyses
    );

    // No more to see here folks, go home.
    return 0;
  }

  catch (std::exception& e)
  {
    if (cbs_logs_initialised)
    {
      logger()<<LogTags::repeat_to_cerr<<LogTags::err
              <<"CBS has exited with fatal exception: "<<e.what()<<EOM;
    }
    else
    {
      cerr << "CBS has exited with fatal exception: " << e.what() << endl;
    }
  }

  // Finished, but an exception was raised.
  return 1;

}
