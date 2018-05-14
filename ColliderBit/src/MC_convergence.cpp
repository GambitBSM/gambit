//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit Monte Carlo convergence routines.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Jan
///
///  *********************************************

#include <omp.h>
#include "gambit/ColliderBit/MC_convergence.hpp"
#include "gambit/ColliderBit/analyses/AnalysisData.hpp"
#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

//#define COLLIDERBIT_DEBUG

namespace Gambit
{
  namespace ColliderBit
  {

    /// A map containing pointers to all instances of this class
    std::map<const MC_convergence_checker* const, bool> MC_convergence_checker::convergence_map;

    /// Constructor
    MC_convergence_checker::MC_convergence_checker() : n_threads(omp_get_max_threads()), converged(false)
    {
      n_signals = new std::vector<int>[n_threads];
      convergence_map[this] = false;
    }

    /// Deconstructor
    MC_convergence_checker::~MC_convergence_checker()
    {
      delete[] n_signals;
    }

    /// Initialise (or re-initialise) the object
    void MC_convergence_checker::init(int collider, const convergence_settings& settings)
    {
      clear();
      set_collider(collider);
      set_settings(settings);
    }

    /// Provide a pointer to the convergence settings
    void MC_convergence_checker::set_settings(const convergence_settings& settings)
    {
      if (omp_get_thread_num() > 0) utils_error().raise(LOCAL_INFO, "Cannot call this function from inside an OpenMP block.");
      _settings = &settings;
    }

    /// Indicate precisely which of the convergence settings to actually use
    void MC_convergence_checker::set_collider(int collider)
    {
      if (omp_get_thread_num() > 0) utils_error().raise(LOCAL_INFO, "Cannot call this function from inside an OpenMP block.");
      _collider = collider;
    }

    /// Clear all convergence data (for all threads)
    void MC_convergence_checker::clear()
    {
      if (omp_get_thread_num() > 0) utils_error().raise(LOCAL_INFO, "Cannot call this function from inside an OpenMP block.");
      converged = false;
      convergence_map[this] = false;
      for (int i = 0; i != n_threads; ++i)
      {
        n_signals[i].clear();
      }
    }


    /// Update the convergence data.  This is the only routine meant to be called in parallel.
    void MC_convergence_checker::update(const HEPUtilsAnalysisContainer& ac)
    {
      // Abort if the analysis container tracked by this object is already fully converged
      if (converged) return;

      // Work out the thread number.
      int my_thread = omp_get_thread_num();

      // Loop over all the analyses and populate their current signal predictions
      n_signals[my_thread].clear();
      for (auto& analysis_pointer_pair : ac.get_current_analyses_map())
      {
        // Loop over all the signal regions in this analysis
        for (auto& sr : analysis_pointer_pair.second->get_results())
        {
          // Update the number of accepted events in this signal region
          n_signals[my_thread].push_back(sr.n_signal);
        }
      }
    }


    /// Check if convergence has been achieved across threads, and across all instances of this class
    bool MC_convergence_checker::achieved(const HEPUtilsAnalysisContainer& ac)
    {
      // Loop over all the analyses and get their systematic errors
      std::vector<int> n_signals_sys;
      for (auto& analysis_pointer_pair : ac.get_current_analyses_map())
      {
        // Loop over all the signal regions in this analysis and get their systematics
        for (auto& sr : analysis_pointer_pair.second->get_results()) n_signals_sys.push_back(sr.signal_sys);
      }

      // Work through the results for all the signal regions in all analyses, combining them
      // across threads and checking if the totals get the statistical error below the target.
      bool done;
      for (unsigned int i = 0; i != n_signals[0].size(); ++i)
      {
        int total_counts = 0;
        for (int j = 0; j != n_threads; j++)
        {
          // Tally up the counts across all threads
          total_counts += n_signals[j][i];
        }
        double fractional_stat_uncert = (total_counts == 0 ? 1.0 : 1.0/sqrt(total_counts));
        double absolute_stat_uncert = total_counts * fractional_stat_uncert;
        done = (_settings->stop_at_sys and total_counts > 0 and absolute_stat_uncert <= n_signals_sys[i]) or
               (fractional_stat_uncert <= _settings->target_stat[_collider]);
        #ifdef COLLIDERBIT_DEBUG
          cerr << endl << "SIGNAL REGION " << i << " of " << n_signals[0].size() << endl;
          cerr << "absolute_stat_uncert vs sys: " << absolute_stat_uncert << " vs " << n_signals_sys[i] << endl;
          cerr << "fractional_stat_uncert vs target: " << fractional_stat_uncert << " vs " << _settings->target_stat[_collider] << endl;
          cerr << "Is this SR done? " << done << endl;
        #endif
        if (_settings->all_SR_must_converge)
        {
          if (not done) return false;
        }
        else
        {
          if (done) break;
        }
      }
      if (not done) return false;
      converged = true;
      convergence_map[this] = true;

      // Now check if all instances of this class have also set their entry in the convergence map to true,
      // implying that all analyses in all containers have reached convergence.
      for (auto& it : convergence_map)
      {
        if (not it.second) return false;
      }
      return true;
    }


  }
}
