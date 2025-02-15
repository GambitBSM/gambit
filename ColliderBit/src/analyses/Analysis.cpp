//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class for ColliderBit analyses.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Andy Buckley
///          (mostlikelytobefound@facebook.com)
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date often
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2023 Aug
///
///  *********************************************

#include <vector>
#include "HEPUtils/Event.h"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include <iostream>

namespace Gambit
{
  namespace ColliderBit
  {

    Analysis::Analysis() : _luminosity(0), _luminosity_is_set(false), _is_scaled(false), _needs_collection(true), _collider_name("")
    {
    }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void Analysis::reset()
    {
      _is_scaled = false;
      _needs_collection = true;
      _results.clear();
      analysis_specific_reset();
    }

    /// Analyze the event (accessed by reference).
    void Analysis::analyze(const HEPUtils::Event &e) { analyze(&e); }

    /// Analyze the event (accessed by pointer).
    void Analysis::analyze(const HEPUtils::Event *e)
    {
      _needs_collection = true;
      run(e);
      // log_progress(); // Add this line to log progress after processing the event
    }

    /// Return the integrated luminosity.
    double Analysis::luminosity() const { return _luminosity; }

    /// Set the integrated luminosity.
    void Analysis::set_luminosity(double lumi)
    {
      _luminosity_is_set = true;
      _luminosity = lumi;
      _results.luminosity = lumi;
    }

    /// Set the analysis name
    void Analysis::set_analysis_name(str aname)
    {
      _analysis_name = aname;
      _results.analysis_name = _analysis_name;
    }

    /// Get the analysis name
    str Analysis::analysis_name() { return _analysis_name; }

    /// Set the collider name
    void Analysis::set_collider_name(str collname)
    {
      _collider_name = collname;
      _results.collider_name = _collider_name;
    }

    /// Get the collider name
    str Analysis::collider_name() { return _collider_name; }

    /// Get the collection of SignalRegionData for likelihood computation.
    const AnalysisData &Analysis::get_results()
    {
      if (_needs_collection)
      {
        collect_results();
        _needs_collection = false;
      }

      return _results;
    }

    /// An overload of get_results() with some additional consistency checks.
    const AnalysisData &Analysis::get_results(str &warning)
    {
      warning = "";
      if (not _luminosity_is_set)
        warning += "Luminosity has not been set for analysis " + _analysis_name + ".";
      if (not _is_scaled)
        warning += "Results have not been scaled for analysis " + _analysis_name + ".";

      return get_results();
    }

    /// Get a (non-const!) pointer to _results.
    AnalysisData *Analysis::get_results_ptr()
    {
      // Call get_results() to make sure everything has been collected properly, but ignore the return value
      get_results();
      // Now provide pointer to _results directly
      return &_results;
    }

    /// An overload of get_results_ptr() with some additional consistency checks.
    AnalysisData *Analysis::get_results_ptr(str &warning)
    {
      // Call get_results() to make sure everything has been collected properly, but ignore the return value
      get_results(warning);
      // Now provide pointer to _results directly
      return &_results;
    }

    /// Add the given result to the internal results list.
    void Analysis::add_result(const SignalRegionData &sr) { _results.add(sr); }

    /// Get the cutflows
    const Cutflows &Analysis::get_cutflows()
    {
      return _results.cutflows;
    }

    /// Add cutflows to the internal results list
    void Analysis::add_cutflows(const Cutflows &cf)
    {
      _results.add_cutflows(cf);
    }

    /// Set the path to the FullLikes BKG file
    void Analysis::set_bkgjson(const std::string &bkgpath)
    {
      _results.bkgjson_path = bkgpath;
    }

    /// Set the covariance matrix, expressing SR correlations
    void Analysis::set_covariance(const Eigen::MatrixXd &srcov) { _results.srcov = srcov; }

    /// A convenience function for setting the SR covariance from a nested vector/initialiser list
    void Analysis::set_covariance(const std::vector<std::vector<double>> &srcov)
    {
      Eigen::MatrixXd cov(srcov.size(), srcov.front().size());
      for (size_t i = 0; i < srcov.size(); ++i)
      {
        for (size_t j = 0; j < srcov.front().size(); ++j)
        {
          cov(i, j) = srcov[i][j];
        }
      }
      set_covariance(cov);
    }

    /// Scale by xsec per event.
    void Analysis::scale(double xsec_per_event)
    {
      double factor = luminosity() * xsec_per_event;
      assert(factor >= 0);
      for (SignalRegionData &sr : _results)
      {
        sr.n_sig_scaled = factor * sr.n_sig_MC;
      }
      _is_scaled = true;
    }

    /// Add the results of another analysis to this one. Argument is not const, because the other needs to be able to gather its results if necessary.
    void Analysis::add(Analysis *other)
    {
      if (_results.empty())
        collect_results();
      if (this == other)
        return;
      const AnalysisData otherResults = other->get_results();
      /// @todo Access by name, including merging disjoint region sets?
      assert(otherResults.size() == _results.size());
      for (size_t i = 0; i < _results.size(); ++i)
      {
        _results[i].combine_SR_MC_signal(otherResults[i]);
      }
      for (auto &pair : _counters)
      {
        pair.second += other->_counters.at(pair.first);
      }
      _cutflows.combine(other->get_cutflows());
      _results.add_cutflows(_cutflows);
      std::cout << "Cutflow combined after this cout" << std::endl; 
    }

    // For printing progress

    // void Analysis::enable_progress_tracking(size_t interval)
    // {
    //   _progress_tracking_enabled = true;
    //   _progress_interval = interval;
    //   _start_time = std::chrono::steady_clock::now();
    // }

    // void Analysis::log_progress()
    // {
    //   if (!_progress_tracking_enabled)
    //     return;

    //   _processed_events++;
    //   if (_processed_events % _progress_interval == 0)
    //   {
    //     auto now = std::chrono::steady_clock::now();
    //     auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - _start_time).count();

    //     int minutes = elapsed_seconds / 60;
    //     int seconds = elapsed_seconds % 60;

    //     std::cout << "Processed " << _processed_events
    //               << " events (" << minutes << "m " << seconds << "s elapsed)"
    //               << std::endl;
    //   }
    // }

  }
}
