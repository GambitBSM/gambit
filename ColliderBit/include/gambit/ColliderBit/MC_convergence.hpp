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

#ifndef __MC_convergence_hpp__
#define __MC_convergence_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Forward declaration
    class AnalysisContainer;

    /// Type for holding Monte Carlo convergence settings
    struct convergence_settings
    {
      double target_stat;
      bool stop_at_sys;
      bool all_analyses_must_converge;
      bool all_SR_must_converge;
    };

    /// Helper class for testing for convergence of analyses
    class MC_convergence_checker
    {
      private:

        /// A pointer to the convergence settings to use
        const convergence_settings* _settings;

        /// Pointer to an array holding the signal counts on each thread
        std::vector<int>* n_signals;

        /// Total number of threads that the checker is configured to deal with
        int n_threads;

        /// Flag indicating if everything tracked by this instance is converged
        bool converged;

        /// A map containing pointers to all instances of this class
        static std::map<const MC_convergence_checker* const, bool> convergence_map;

      public:

        /// Constructor
        MC_convergence_checker();

        /// Destructor
        ~MC_convergence_checker();

        /// Initialise (or re-initialise) the object
        void init(const convergence_settings&);

        /// Provide a pointer to the convergence settings
        void set_settings(const convergence_settings&);

        /// Clear all convergence data (for all threads)
        void clear();

        /// Update the convergence data.  This is the only routine meant to be called in parallel.
        void update(const AnalysisContainer&);

        /// Check if convergence has been achieved across threads, and across all instances of this class
        bool achieved(const AnalysisContainer& ac);
    };


  }
}

#endif