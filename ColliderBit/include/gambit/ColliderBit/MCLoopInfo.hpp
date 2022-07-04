//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type for holding event loop information.
///
///  *********************************************
///
///  Authors (add name if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Jan
///
///  *********************************************


#pragma once

#include <vector>
#include "gambit/Utils/util_types.hpp"
#include "gambit/ColliderBit/MC_convergence.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    /// @brief Container for event loop status data and settings
    struct MCLoopInfo
    {
     
      // Event genration has been bypassed: Default = false
      bool event_gen_BYPASS = false;

      /// Event generation has started
      bool event_generation_began;

      /// Maximum allowed number of failed events has been reached
      mutable bool exceeded_maxFailedEvents;

      /// Maximum allowed number of failed events has been reached and MC loop terminated
      mutable bool end_of_event_file;

      /// The names of all colliders
      std::vector<str> collider_names;

      /// Maximum allowable number of failed events before MC loop is terminated for each collider
      std::map<str,int> maxFailedEvents;

      /// Invalidate points where number of failed events > maxFailedEvents? One bool for each collider
      std::map<str,bool> invalidate_failed_points;

      /// Number of events generated for each collider
      mutable std::map<str,int> event_count;

      /// Convergence options for each collider
      std::map<str,convergence_settings> convergence_options;

      /// Analysis list for each collider
      std::map<str,std::vector<str>> analyses;

      /// Analysis list for each detector of each collider
      std::map<str,std::map<str,std::vector<str>>> detector_analyses;

      /// Set the current collider
      void set_current_collider(str&);

      /// Get the current collider
      const str& current_collider() const;

      /// Get maximum allowable number of failed events before MC loop is terminated for the current collider
      const int& current_maxFailedEvents() const;
      /// Get/set maximum allowable number of failed events before MC loop is terminated for the current collider
      int& current_maxFailedEvents();

      /// Get invalidate_failed_points bool for the current collider
      const bool& current_invalidate_failed_points() const;
      /// Get/set invalidate_failed_points for the current collider
      bool& current_invalidate_failed_points();

      /// Get the number of events generated for the current collider
      const int& current_event_count() const;
      /// Get/set the number of events generated for the current collider
      int& current_event_count();

      /// Get the set of convergence options for the current collider
      const convergence_settings& current_convergence_options() const;
      /// Get/set the set of convergence options for the current collider
      convergence_settings& current_convergence_options();

      /// Get the set of analyses for the current collider
      const std::vector<str>& current_analyses() const;
      /// Get/set the set of analyses for the current collider
      std::vector<str>& current_analyses();

      /// Get the set of analyses for the current collider and a given detector
      const std::vector<str>& current_analyses_for(const str&) const;
      /// Get/set the set of analyses for the current collider and a given detector
      std::vector<str>& current_analyses_for(const str&);

      /// Query whether any analyses exist for a given detector for the current collider
      bool current_analyses_exist_for(const str&) const;

      /// Set exceeded_maxFailedEvents = true and decrement event counter by 1
      void report_exceeded_maxFailedEvents() const;

      /// Set end_of_event_file = true and decrement event counter by 1
      void report_end_of_event_file() const;

      /// Reset flags
      void reset_flags();

      private:

        /// The name of the current collider
        str _current_collider;

        /// Iterator to the current maxFailedEvents
        std::map<str,int>::iterator _current_maxFailedEvents_it;

        /// Iterator to the current invalidate_failed_points
        std::map<str,bool>::iterator _current_invalidate_failed_points_it;

        /// Iterator to the current event count
        std::map<str,int>::iterator _current_event_count_it;

        /// Iterator to the current set of convergence options
        std::map<str,convergence_settings>::iterator _current_convergence_options_it;

        /// Iterator to the current set of analyses
        std::map<str,std::vector<str>>::iterator _current_analyses_it;

        /// Iterator to the current set of analyses sorted by detector
        std::map<str,std::map<str,std::vector<str>>>::iterator _current_detector_analyses_it;

    };

  }
}

