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


#include "gambit/ColliderBit/MCLoopInfo.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"


namespace Gambit
{

  namespace ColliderBit
  {

    /// Set exceeded_maxFailedEvents = true and decrement event counter by 1
    void MCLoopInfo::report_exceeded_maxFailedEvents() const
    {
      #pragma omp critical
      {
        exceeded_maxFailedEvents = true;
        // Decrement event counter
        _current_event_count_it->second--;        
      }
    }

    /// Set end_of_event_file = true and decrement event counter by 1
    void MCLoopInfo::report_end_of_event_file() const
    {
      #pragma omp critical
      {
        end_of_event_file = true;
        // Decrement event counter
        _current_event_count_it->second--;        
      }
    }

    /// Reset flags
    void MCLoopInfo::reset_flags()
    {
      end_of_event_file = false;
      event_generation_began = false;
      exceeded_maxFailedEvents = false;
    }

    /// Set the current collider
    void MCLoopInfo::set_current_collider(str& col)
    {
      // Save the current collider
      _current_collider = col;

      // Save an iterator to the current maxFailedEvents
      auto it = maxFailedEvents.find(_current_collider);
      if (it == maxFailedEvents.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::maxFailedEvents map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_maxFailedEvents_it = it;

      // Save an iterator to the number of events generated for the current collider
      it = event_count.find(_current_collider);
      if (it == event_count.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::event_count map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_event_count_it = it;

      // Save an iterator to the the list of analyses for the current collider
      auto jt = convergence_options.find(_current_collider);
      if (jt == convergence_options.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::convergence_options map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_convergence_options_it = jt;

      // Save an iterator to the the list of analyses for the current collider
      auto kt = analyses.find(_current_collider);
      if (kt == analyses.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::analyses map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_analyses_it = kt;

      // Save an iterator to the the list of analyses for the current collider, sorted by detector
      auto lt = detector_analyses.find(_current_collider);
      if (lt == detector_analyses.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::detector_analyses map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_detector_analyses_it = lt;

      // Save an iterator to the current invalidate_failed_points
      auto mt = invalidate_failed_points.find(_current_collider);
      if (mt == invalidate_failed_points.end())
      {
        str msg = "Current collider \"" + _current_collider + "\" not found in MCLoopInfo::invalidate_failed_points map.";
        utils_error().raise(LOCAL_INFO, msg);
      }
      _current_invalidate_failed_points_it = mt;

    }

    bool MCLoopInfo::current_analyses_exist_for(const str& detname) const
    {
      auto current_analyses_by_detector = _current_detector_analyses_it->second;
      auto it = current_analyses_by_detector.find(detname);
      return not (it == current_analyses_by_detector.end());
    }

    const str& MCLoopInfo::current_collider() const { return _current_collider; }

    const int& MCLoopInfo::current_maxFailedEvents() const { return _current_maxFailedEvents_it->second; }
    int& MCLoopInfo::current_maxFailedEvents() { return _current_maxFailedEvents_it->second; }

    const bool& MCLoopInfo::current_invalidate_failed_points() const { return _current_invalidate_failed_points_it->second; }
    bool& MCLoopInfo::current_invalidate_failed_points() { return _current_invalidate_failed_points_it->second; }

    const int& MCLoopInfo::current_event_count() const { return _current_event_count_it->second; }
    int& MCLoopInfo::current_event_count() { return _current_event_count_it->second; }

    const convergence_settings& MCLoopInfo::current_convergence_options() const { return _current_convergence_options_it->second; }
    convergence_settings& MCLoopInfo::current_convergence_options() { return _current_convergence_options_it->second; }

    const std::vector<str>& MCLoopInfo::current_analyses() const { return _current_analyses_it->second; }
    std::vector<str>& MCLoopInfo::current_analyses() { return _current_analyses_it->second; }

    const std::vector<str>& MCLoopInfo::current_analyses_for(const str& detname) const
    {
      if (not current_analyses_exist_for(detname)) utils_error().raise(LOCAL_INFO, "Detector "+detname);
      return _current_detector_analyses_it->second.at(detname);
    }
    std::vector<str>& MCLoopInfo::current_analyses_for(const str& detname)
    {
      if (not current_analyses_exist_for(detname)) utils_error().raise(LOCAL_INFO, "Detector "+detname);
      return _current_detector_analyses_it->second.at(detname);
    }

  }

}
