//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Batch execution and merge helpers for ColliderBit Solo (CBS).
///
///  *********************************************

#pragma once

#include <map>
#include <string>
#include <vector>

#include <unistd.h>

#include "solo_input.hpp"
#include "solo_output.hpp"

#include "gambit/ColliderBit/ColliderBit_types.hpp"
#include "gambit/Utils/yaml_options.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace SoloBatch
    {
      /// Process-level event counts and suggested additional sampling.
      struct ProcessSamplingAdvice
      {
        std::string process_name;
        double cross_section_fb = 0.0;
        long long processed_events = 0;
        long long recommended_additional_events = 0;
      };

      /// Event budget and process allocation for one fractional MC uncertainty target.
      struct SamplingTargetAdvice
      {
        double target_fractional_uncert = 0.0;
        bool need_more_mc = false;
        double current_fractional_uncert = 0.0;
        double scale_factor = 1.0;
        long long current_total_events = 0;
        long long recommended_total_events = 0;
        long long recommended_additional_events = 0;
        std::vector<ProcessSamplingAdvice> process_recommendations;
      };

      /// Signal uncertainty and sampling targets for an analysis's selected signal region.
      struct AnalysisSamplingAdvice
      {
        std::string analysis_name;
        std::string sr_label;
        int sr_index = -1;
        double n_sig_scaled = 0.0;
        double n_sig_scaled_err = 0.0;
        double fractional_uncert = 0.0;
        double effective_events = 0.0;
        std::vector<SamplingTargetAdvice> targets;
      };

      /// Owned merged analysis data, non-owning pointers into analyses_storage,
      /// event totals and recalculated likelihoods. Keep storage alive with the pointers.
      /// Process event counts are indexed like PreparedInput::processes.
      struct MergedRunResult
      {
        int total_events = 0;
        long long total_process_events = 0;
        std::vector<long long> process_event_counts;
        std::map<std::string, long long> collider_event_counts;
        std::vector<AnalysisData> analyses_storage;
        AnalysisDataPointers analyses;
        map_str_AnalysisLogLikes analysis_loglikes;
        double combined_loglike = 0.0;
        double contur_loglike = 0.0;
        std::map<std::string, double> contur_pool_loglikes;
        std::map<std::string, std::string> contur_pool_info;
        std::vector<SoloOutput::InputFileSummaryEntry> input_files;
        std::vector<std::string> rivet_analyses;
        MCLoopInfo input_loop{};
      };

      /// One stored Rivet file and the mixture scale applied to a copy before merging.
      /// The checkpoint file itself stays at nominal weight.
      struct CheckpointYodaFile
      {
        std::string key;
        std::string collider;
        std::string process;
        std::string hepmc_file;
        std::string yoda_file;
        double scale = 1.0;
      };

      /// Holds the checkpoint lock until the combined JSON has been written.
      struct CheckpointLock
      {
        int fd = -1;
        CheckpointLock() = default;
        explicit CheckpointLock(int file_descriptor) : fd(file_descriptor) {}
        CheckpointLock(const CheckpointLock&) = delete;
        CheckpointLock& operator=(const CheckpointLock&) = delete;
        CheckpointLock(CheckpointLock&& other) noexcept : fd(other.fd) { other.fd = -1; }
        CheckpointLock& operator=(CheckpointLock&& other) noexcept
        {
          if (this != &other)
          {
            reset();
            fd = other.fd;
            other.fd = -1;
          }
          return *this;
        }
        ~CheckpointLock() { reset(); }
        void reset()
        {
          if (fd >= 0)
          {
            ::close(fd);
            fd = -1;
          }
        }
      };

      /// Merged searches plus the YODA files the caller scales and passes to Contur.
      struct CheckpointResult
      {
        MergedRunResult merged;
        std::string checkpoint_directory;
        std::vector<CheckpointYodaFile> yoda_files;
        CheckpointLock lock;
      };

      /// Run each unfinished HepMC file in its own CBS process and merge the stored results.
      /// A matching checkpoint file is kept. --fresh deletes that output's checkpoint first.
      CheckpointResult run_with_checkpoints(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        const std::string& output_file,
        bool screen_output,
        bool fresh,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      );

      /// Run files sequentially on the local machine and combine one parameter point.
      MergedRunResult run_and_merge(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      );

      /// Run one full measurement task per collider, then combine disjoint
      /// analysis/pool results without multiplying the same experimental data.
      MergedRunResult run_joint_colliders(
        const std::string& cbs_executable,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings,
        double (*marginaliser)(const int&, const double&, const double&, const double&),
        bool (*FullLikes_FileExists)(const str&),
        int (*FullLikes_ReadIn)(const str&, const str&, const str&),
        double (*FullLikes_Evaluate)(std::map<str,double>&, const str&)
      );

      /// Estimate extra events and process allocations for the selected SRs' MC errors.
      std::vector<AnalysisSamplingAdvice> build_sampling_advice(
        const MergedRunResult& merged,
        const SoloInput::PreparedInput& prepared_input,
        const Options& settings
      );
    } // namespace SoloBatch
  }   // namespace ColliderBit
} // namespace Gambit
