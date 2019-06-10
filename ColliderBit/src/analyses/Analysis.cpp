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
///  *********************************************

#include <vector>
#include "HEPUtils/Event.h"
#include "gambit/ColliderBit/analyses/Analysis.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    Analysis::Analysis() : _luminosity(0)
                         , _luminosity_is_set(false)
                         , _is_scaled(false)
                         , _needs_collection(true)
                         { }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void Analysis::reset()
    {
      _is_scaled = false;
      _needs_collection = true;
      _results.clear();
      analysis_specific_reset();
    }

    /// Analyze the event (accessed by reference).
    void Analysis::analyze(const HEPUtils::Event& e) { analyze(&e); }

    /// Analyze the event (accessed by pointer).
    void Analysis::analyze(const HEPUtils::Event* e)
    {
      _needs_collection = true;
      run(e);
    }

    /// Return the integrated luminosity (in inverse pb).
    double Analysis::luminosity() const { return _luminosity; }

    /// Set the integrated luminosity (in inverse pb).
    void Analysis::set_luminosity(double lumi) { _luminosity_is_set = true; _luminosity = lumi; }

    /// Set the analysis name
    void Analysis::set_analysis_name(str aname)
    {
      _analysis_name = aname;
      _results.analysis_name = _analysis_name;
    }

    /// Get the analysis name
    str Analysis::analysis_name() { return _analysis_name; }

    /// Get the collection of SignalRegionData for likelihood computation.
    const AnalysisData& Analysis::get_results()
    {
      if (_needs_collection)
      {
        collect_results();
        _needs_collection = false;
      }
      return _results;
    }

    /// An overload of get_results() with some additional consistency checks.
    const AnalysisData& Analysis::get_results(str& warning)
    {
      warning = "";
      if (not _luminosity_is_set)
        warning += "Luminosity has not been set for analysis " + _analysis_name + ".";
      if (not _is_scaled)
        warning += "Results have not been scaled for analysis " + _analysis_name + ".";

      return get_results();
    }

    /// Get a pointer to _results.
    const AnalysisData* Analysis::get_results_ptr()
    {
      return &get_results();
    }

    /// Get a pointer to _results.
    const AnalysisData* Analysis::get_results_ptr(str& warning)
    {
      return &get_results(warning);
    }

    /// Add the given result to the internal results list.
    void Analysis::add_result(const SignalRegionData& sr) { _results.add(sr); }

    /// Set the covariance matrix, expressing SR correlations
    void Analysis::set_covariance(const Eigen::MatrixXd& srcov) { _results.srcov = srcov; }

    /// A convenience function for setting the SR covariance from a nested vector/initialiser list
    void Analysis::set_covariance(const std::vector<std::vector<double>>& srcov)
    {
      Eigen::MatrixXd cov(srcov.size(), srcov.front().size());
      for (size_t i = 0; i < srcov.size(); ++i)
      {
        for (size_t j = 0; j < srcov.front().size(); ++j)
        {
          cov(i,j) = srcov[i][j];
        }
      }
      set_covariance(cov);
    }

    /// Scale by xsec per event.
    void Analysis::scale(double xsec_per_event)
    {
      double factor = luminosity() * xsec_per_event;
      assert(factor >= 0);
      for (SignalRegionData& sr : _results)
      {
        sr.n_signal_at_lumi = factor * sr.n_signal;
      }
      _is_scaled = true;
    }

    /// Add the results of another analysis to this one. Argument is not const, because the other needs to be able to gather its results if necessary.
    void Analysis::add(Analysis* other)
    {
      if (_results.empty()) collect_results();
      const AnalysisData otherResults = other->get_results();
      /// @todo Access by name, including merging disjoint region sets?
      assert(otherResults.size() == _results.size());
      for (size_t i = 0; i < _results.size(); ++i)
      {
        _results[i].n_signal += otherResults[i].n_signal;
      }
      combine(other);
    }

  }
}
