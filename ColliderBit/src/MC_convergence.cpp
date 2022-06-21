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
///  \date 2019 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2018 May
///
///  *********************************************

#include <omp.h>
#include "gambit/ColliderBit/MC_convergence.hpp"
#include "gambit/ColliderBit/analyses/AnalysisContainer.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

// #define COLLIDERBIT_DEBUG

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
    void MC_convergence_checker::init(const convergence_settings& settings)
    {
      clear();
      set_settings(settings);
    }

    /// Provide a pointer to the convergence settings
    void MC_convergence_checker::set_settings(const convergence_settings& settings)
    {
      if (omp_get_thread_num() > 0) utils_error().raise(LOCAL_INFO, "Cannot call this function from inside an OpenMP block.");
      _settings = &settings;
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
    void MC_convergence_checker::update(const AnalysisContainer& ac)
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
          n_signals[my_thread].push_back(sr.n_sig_MC);
        }
      }
    }


    /// Check if convergence has been achieved across threads, and across all instances of this class
    bool MC_convergence_checker::achieved(const AnalysisContainer& ac)
    {
      if (not converged)
      {

        int SR_index = -1;
        // Loop over all analyses
        bool analysis_converged;
        bool all_analyses_converged = true; // Will be set to false if any analysis is not converged
        for (auto& analysis_pointer_pair : ac.get_current_analyses_map())
        {

          analysis_converged = false;

          // Loop over all the signal regions in this analysis
          bool SR_converged;
          bool all_SR_converged = true;  // Will be set to false if any SR is not converged
          for (auto& sr : analysis_pointer_pair.second->get_results())
          {
            SR_converged = false;
            SR_index += 1;

            // Sum signal count across threads
            int total_counts = 0;
            for (int j = 0; j != n_threads; j++)
            {
              // Tally up the counts across all threads
              total_counts += n_signals[j][SR_index];
            }

            double fractional_stat_uncert = (total_counts == 0 ? 1.0 : 1.0/sqrt(total_counts));
            double absolute_stat_uncert = total_counts * fractional_stat_uncert;
            SR_converged = (_settings->stop_at_sys and total_counts > 0 and absolute_stat_uncert <= sr.n_sig_MC_sys) or
                   (fractional_stat_uncert <= _settings->target_stat);

            if (not SR_converged) all_SR_converged = false;

            #ifdef COLLIDERBIT_DEBUG
              cerr << endl;
              cerr << "DEBUG: SIGNAL REGION " << SR_index << " of " << n_signals[0].size() << endl;
              cerr << "DEBUG: SR label: " << sr.sr_label << " in analysis " << analysis_pointer_pair.first << endl;
              cerr << "DEBUG: absolute_stat_uncert vs sys: " << absolute_stat_uncert << " vs " << sr.n_sig_MC_sys << endl;
              cerr << "DEBUG: fractional_stat_uncert vs target: " << fractional_stat_uncert << " vs " << _settings->target_stat << endl;
              cerr << "DEBUG: Is this SR done? " << SR_converged << endl;
            #endif

            if (SR_converged)
            {
              // Shortcut
              if (not _settings->all_analyses_must_converge and not _settings->all_SR_must_converge)
              {
                converged = true;
                convergence_map[this] = true;
                return true;
              }

              if (not _settings->all_SR_must_converge)
              {
                analysis_converged = true;
                break; // break signal region loop
              }
            }
            else  // SR not converged
            {
              // Shortcut
              if (_settings->all_analyses_must_converge and _settings->all_SR_must_converge)
              {
                return false;
              }
            }
          } // End loop over SRs

          if (_settings->all_SR_must_converge) analysis_converged = all_SR_converged;

          #ifdef COLLIDERBIT_DEBUG
            cerr << endl;
            cerr << "DEBUG: Done looping over SRs for analysis " << analysis_pointer_pair.first << endl;
            cerr << "DEBUG: analysis_converged =  " << analysis_converged << endl;
          #endif

          if (not analysis_converged) all_analyses_converged = false;

          // Shortcut
          if (analysis_converged and not _settings->all_analyses_must_converge)
          {
            converged = true;
            convergence_map[this] = true;
            return true;
          }
          else if (not analysis_converged and _settings->all_analyses_must_converge)
          {
            return false;
          }

        } // End loop over analyses

        #ifdef COLLIDERBIT_DEBUG
          cerr << endl;
          cerr << "DEBUG: Done looping over analyses in this container" << endl;
          cerr << "DEBUG: Current variable values:" << endl;
          cerr << "DEBUG: analysis_converged = " << analysis_converged << endl;
          cerr << "DEBUG: all-analysis_converged = " << all_analyses_converged << endl;
        #endif

        if (not all_analyses_converged) return false;
        converged = true;
        convergence_map[this] = true;
      } // end: if (not converged

      // Now check if all instances of this class have also set their entry in the convergence map to true,
      // implying that all analyses in all containers have reached convergence.
      if (_settings->all_analyses_must_converge)
      {
        for (auto& it : convergence_map)
        {
          if (not it.second) return false;
        }
        return true;
      }
      return true;
    }

  }
}
