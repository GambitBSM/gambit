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

#pragma once

#include <string>
#include "HEPUtils/Event.h"
#include "gambit/ColliderBit/analyses/AnalysisData.hpp"

namespace Gambit
{
  typedef std::string str;

  namespace ColliderBit
  {

    /// A class for collider analyses within ColliderBit.
    class Analysis
    {

      public:

        /// Construction
        Analysis();
        /// Destruction
        virtual ~Analysis() { }

        /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
        void reset();

        /// @name Event analysis, event number, and cross section functions:
        ///@{
        /// Analyze the event (accessed by reference).
        void analyze(const HEPUtils::Event&);
        /// Analyze the event (accessed by pointer).
        void analyze(const HEPUtils::Event*);
        /// @}

        /// Return the integrated luminosity.
        double luminosity() const;
        /// Set the integrated luminosity.
        void set_luminosity(double);
        /// Set the analysis name
        void set_analysis_name(str);
        /// Get the analysis name
        str analysis_name();

        /// Get the collection of SignalRegionData for likelihood computation.
        const AnalysisData& get_results();
        /// An overload of get_results() with some additional consistency checks.
        const AnalysisData& get_results(str&);
        /// Get a (non-const!) pointer to _results.
        AnalysisData* get_results_ptr();
        /// An overload of get_results_ptr() with some additional consistency checks.
        AnalysisData* get_results_ptr(str&);
        ///@}

        /// Scale by xsec per event.
        void scale(double);

        /// @name Analysis combination operations
        ///@{
        /// Add the results of another analysis to this one. Argument is not const, because the other needs to be able to gather its results if necessary.
        void add(Analysis* other);
        /// Add the analysis-specific variables of another analysis to this one.
        virtual void combine(const Analysis* other) = 0;
        ///@}

      protected:

        /// Reset the analysis-specific variables.
        virtual void analysis_specific_reset() = 0;

        /// @name Collection functions
        ///@{
        /// Run the analysis.
        virtual void run(const HEPUtils::Event*) = 0;
        /// Add the given result to the internal results list.
        void add_result(const SignalRegionData& sr);
        /// Set the covariance matrix, expressing SR correlations
        void set_covariance(const Eigen::MatrixXd& srcov);
        /// A convenience function for setting the SR covariance from a nested vector/initialiser list
        void set_covariance(const std::vector<std::vector<double>>&);
        /// A convenience function for setting the path to the ATLAS FullLikes BKG Json file
        void set_bkgjson(const std::string& bkgpath);
        /// Gather together the info for likelihood calculation.
        virtual void collect_results() = 0;
        ///@}

      private:

        double _luminosity;
        bool _luminosity_is_set;
        bool _is_scaled;
        bool _needs_collection;
        AnalysisData _results;
        std::string _analysis_name;

    };


    /// For analysis factory function definition
    #define DEFINE_ANALYSIS_FACTORY(ANAME)                                     \
      Analysis* create_Analysis_ ## ANAME()                                    \
      {                                                                        \
        return new Analysis_ ## ANAME();                                       \
      }                                                                        \
      std::string getDetector_ ## ANAME()                                      \
      {                                                                        \
        return std::string(Analysis_ ## ANAME::detector);                      \
      }


  }
}
