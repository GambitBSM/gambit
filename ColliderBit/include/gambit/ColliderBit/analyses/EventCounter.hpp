//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  EventCounter class
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2019 Nov
///
///  *********************************************

#pragma once

#include <string>
#include "HEPUtils/Event.h"

namespace Gambit {
  namespace ColliderBit {

    /// A simple class for counting events of type HEPUtils::Event
    class EventCounter
    {

    private:

      std::string _name;
      int _sum;
      double _weight_sum;
      double _weight_sum_err;
      std::vector<unsigned int> _event_acceptance_record;
      bool _store_accepted_event_IDs; 

    public:


      // Constructors
      EventCounter() :
        _name(""),
        _sum(0),
        _weight_sum(0.0),
        _weight_sum_err(0.0),
        _store_accepted_event_IDs(false)
      { }

      EventCounter(const std::string name) :
        _name(name),
        _sum(0),
        _weight_sum(0.0),
        _weight_sum_err(0.0),
        _store_accepted_event_IDs(false)
      { }


      // Initialize
      void init(const std::string name)
      {
        _name = name;
        _sum = 0;
        _weight_sum = 0;
        _weight_sum_err = 0;        
      }

      // Reset
      void reset() 
      { 
        _sum = 0;
        _weight_sum = 0;
        _weight_sum_err = 0;
      }

      // Set name
      void set_name(const std::string name) { _name = name; }
      // Get name
      std::string name() const { return _name; }

      // Set sum
      void set_sum(int sum) { _sum = sum; }
      // Get sum
      int sum() const { return _sum; }

      // Set weight sum
      void set_weight_sum(double weight_sum) { _weight_sum = weight_sum; }
      // Get weight sum
      double weight_sum() const { return _weight_sum; }

      // Set weight sum error
      void set_weight_sum_err(double weight_sum_err) { _weight_sum_err = weight_sum_err; }
      // Get weight sum error
      double weight_sum_err() const { return _weight_sum_err; }


      // Increment event count directly, with optional weights arguments
      void add_event(unsigned int event_id, double w = 1.0, double werr = 0.0)
      {
        _sum++;
        _weight_sum += w;
        _weight_sum_err = sqrt((_weight_sum_err * _weight_sum_err) + (werr * werr));
        // _Anders
        if (_store_accepted_event_IDs)
        {
          _event_acceptance_record.push_back(event_id);
          std::cerr << "Thread: " << omp_get_thread_num() << "   SR: " << _name << "   Accepted event ID: " << event_id << std::endl;          
        }
      }

      // Increment event count with weigths from an HEPUtils::Event
      void add_event(const HEPUtils::Event& event)
      {
        add_event(event.id(), event.weight(), event.weight_err());
      }

      void add_event(const HEPUtils::Event* event_ptr) 
      { 
        add_event(*event_ptr); 
      }

      // Increment event count with the operator+= and HEPUtils::Event input
      EventCounter& operator+=(const HEPUtils::Event& event)
      {
        add_event(event);
        return *this;
      }

      // Increment event count with the operator+= and EventCounter input
      EventCounter& operator+=(const EventCounter& rhs)
      {
        _sum += rhs.sum();
        _weight_sum += rhs.weight_sum();
        _weight_sum_err = sqrt( (_weight_sum_err * _weight_sum_err) + (rhs.weight_sum_err() * rhs.weight_sum_err()) );
        // _Anders
        if (_store_accepted_event_IDs)
        {
          _event_acceptance_record.insert( _event_acceptance_record.end(), rhs._event_acceptance_record.begin(), rhs._event_acceptance_record.end() );
        }
        return *this;
      }

      // Add the content of another EventCounter to this one
      EventCounter& combine(const EventCounter& other)
      {
        _sum += other.sum();
        _weight_sum += other.weight_sum();

        double other_weight_sum_err = other.weight_sum_err();
        _weight_sum_err = sqrt((_weight_sum_err * _weight_sum_err) + (other_weight_sum_err * other_weight_sum_err));

        // _Anders
        if (_store_accepted_event_IDs)
        {
          _event_acceptance_record.insert( _event_acceptance_record.end(), other._event_acceptance_record.begin(), other._event_acceptance_record.end() );
        }
        return *this;
      }

      // _Anders
      void set_store_accepted_event_IDs(bool setting)
      { 
        _store_accepted_event_IDs = setting;
      }

      std::vector<unsigned int> get_event_acceptance_record() const
      {
        return _event_acceptance_record;
      }

    };

  }
}
