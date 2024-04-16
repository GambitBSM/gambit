//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit (production) cross-section class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep
///
///  *********************************************

#include <algorithm>
#include <cassert>
#include <cmath>
#include <omp.h>
#include "gambit/ColliderBit/xsec.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

namespace Gambit
{
  namespace ColliderBit
  {


    /// 
    /// Definitions of xsec members
    ///

    /// Constructor
    xsec_container::xsec_container() : 
      _xsec(0),
      _xsecerr(0),
      _info_string(""),
      _trust_level(1)
    { }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void xsec_container::reset()
    {
      _xsec = 0;
      _xsecerr = 0;
      _info_string = "";
      _trust_level = 1;
    }

    /// Return the cross-section (in fb).
    double xsec_container::operator()() const { return _xsec; }
    double xsec_container::xsec() const { return _xsec; }

    /// Return the cross-section error (in fb).
    double xsec_container::xsec_err() const { return _xsecerr; }

    /// Return the cross-section relative error.
    double xsec_container::xsec_relerr() const { return _xsec > 0 ? _xsecerr/_xsec : 0; }

    /// Set the cross-section and its error (in fb).
    void xsec_container::set_xsec(double xs, double xserr) { _xsec = xs; _xsecerr = xserr; }

    /// Average cross-sections and combine errors.
    void xsec_container::average_xsec(double other_xsec, double other_xsecerr)
    {
      if (other_xsec > 0)
      {
        if (_xsec <= 0)
        {
          set_xsec(other_xsec, other_xsecerr);
        }
        else
        {
          double w = 1./(_xsecerr*_xsecerr);
          double other_w = 1./(other_xsecerr*other_xsecerr);
          _xsec = (w * _xsec + other_w * other_xsec) / (w + other_w);
          _xsecerr = 1./sqrt(w + other_w);
        }
      }
    }

    void xsec_container::average_xsec(const xsec_container& other)
    {
      average_xsec(other(), other.xsec_err());
    }

    /// Sum cross-sections and add errors in quadrature.
    void xsec_container::sum_xsecs(double other_xsec, double other_xsecerr)
    {
      if (other_xsec > 0)
      {
        if (_xsec <= 0)
        {
          set_xsec(other_xsec, other_xsecerr);
        }
        else
        {
          _xsec += other_xsec;
          _xsecerr = sqrt(_xsecerr * _xsecerr + other_xsecerr * other_xsecerr);
        }
      }
    }

    void xsec_container::sum_xsecs(const xsec_container& other)
    {
      sum_xsecs(other(), other.xsec_err());
    }

    /// Get content as a <string,double> map (for easy printing).
    std::map<std::string, double> xsec_container::get_content_as_map() const
    {
      std::map<std::string, double> content_map;

      std::string key;
      std::string base_key;
      if (_info_string != "") base_key = _info_string + "__";
      else base_key = "";

      key = base_key + "xsec_" + unit;
      content_map[key] = this->xsec();

      key = base_key + "xsec_err_" + unit;
      content_map[key] = this->xsec_err();

      key = base_key + "xsec_relerr";
      content_map[key] = this->xsec_relerr();

      content_map["trust_level"] = static_cast<double>(this->trust_level());  

      return content_map;
    }

    /// Set the info string
    void xsec_container::set_info_string(std::string info_string_in) { _info_string = info_string_in; }

    /// Get the info string
    std::string xsec_container::info_string() const { return _info_string; }

    /// Set the trust level
    void xsec_container::set_trust_level(int trust_level_in) { _trust_level = trust_level_in; }

    /// Get the info string
    int xsec_container::trust_level() const { return _trust_level; }

    /// Set the unit string
    const std::string xsec_container::unit = "fb";



    /// 
    /// Definitions of MC_xsec_container members
    ///

    /// Constructor
    MC_xsec_container::MC_xsec_container() : 
      xsec_container::xsec_container(),
      _ntot(0)
    { }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void MC_xsec_container::reset()
    {
      xsec_container::reset();
      _ntot = 0;

      // Add this instance to the instances map if it's not there already.
      int thread = omp_get_thread_num();
      if (instances_map.count(thread) == 0)
      {
        #pragma omp critical
        {
          instances_map[thread] = this;
        }
      }
    }

    /// Increment the number of events seen so far
    void MC_xsec_container::log_event() { _ntot += 1; }

    /// Return the total number of events seen so far.
    long long MC_xsec_container::num_events() const { return _ntot; }

    /// Return the cross-section per event seen (in fb).
    double MC_xsec_container::xsec_per_event() const { return (_xsec >= 0 && _ntot > 0) ? _xsec/_ntot : 0; }

    /// Set the total number of events seen so far.
    void MC_xsec_container::set_num_events(long long n) { _ntot = n; }

    /// Average cross-sections and combine errors.
    void MC_xsec_container::average_xsec(double other_xsec, double other_xsecerr, long long other_ntot)
    {
      // Run base class function
      xsec_container::average_xsec(other_xsec, other_xsecerr);

      // Update _ntot
      if (other_xsec > 0)
      {
        if (_xsec <= 0) set_num_events(other_ntot);
        else _ntot += other_ntot;
      }
    }

    void MC_xsec_container::average_xsec(const MC_xsec_container& other)
    {
      MC_xsec_container::average_xsec(other(), other.xsec_err(), other.num_events());
    }

    /// Sum cross-sections and add errors in quadrature.
    void MC_xsec_container::sum_xsecs(double other_xsec, double other_xsecerr, long long other_ntot)
    {
      // Run base class function
      xsec_container::sum_xsecs(other_xsec, other_xsecerr);

      // Update _ntot
      if (other_xsec > 0)
      {
        if (_xsec <= 0) set_num_events(other_ntot);
        else _ntot += other_ntot;
      }
    }

    void MC_xsec_container::sum_xsecs(const MC_xsec_container& other)
    {
      MC_xsec_container::sum_xsecs(other(), other.xsec_err(), other.num_events());
    }


    /// Collect xsec predictions from other threads and do a weighted combination.
    void MC_xsec_container::gather_xsecs()
    {
      int this_thread = omp_get_thread_num();
      for (auto& thread_xsec_pair : instances_map)
      {
        if (thread_xsec_pair.first == this_thread) continue;
        const MC_xsec_container& other = (*thread_xsec_pair.second);
        average_xsec(other(), other.xsec_err(), other.num_events());
      }
    }

    /// Collect total events seen on all threads.
    void MC_xsec_container::gather_num_events()
    {
      int this_thread = omp_get_thread_num();
      for (auto& thread_xsec_pair : instances_map)
      {
        if (thread_xsec_pair.first == this_thread) continue;
        const MC_xsec_container& other = (*thread_xsec_pair.second);
        _ntot += other.num_events();
      }
    }

    /// Get content as a <string,double> map (for easy printing).
    std::map<std::string, double> MC_xsec_container::get_content_as_map() const
    {
      // Get content from base class
      std::map<std::string, double> content_map = xsec_container::get_content_as_map();

      // Add content specific to this class
      std::string key;
      std::string base_key;
      if (_info_string != "") base_key = _info_string + "__";
      else base_key = "";

      key = base_key + "xsec_per_event_" + unit;
      content_map[key] = this->xsec_per_event();

      key = base_key + "logged_events_" + unit;
      content_map[key] = _ntot;

      return content_map;
    }

    /// A map with pointers to all instances of this class. The key is the thread number.
    std::map<int, const MC_xsec_container*> MC_xsec_container::instances_map;



    /// 
    /// Definitions of process_xsec_container members
    ///

    /// Constructor
    process_xsec_container::process_xsec_container() : 
      xsec_container::xsec_container(),
      _process_code(-1),
      _processes_sharing_xsec(std::vector<int>()),
      _related_pid_pairs(std::vector<PID_pair>())
    { }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void process_xsec_container::reset()
    {
      xsec_container::reset();
      _process_code = -1;
      _processes_sharing_xsec.clear();
      _related_pid_pairs.clear();
    }

    /// Average cross-sections and combine errors.
    void process_xsec_container::average_xsec(double other_xsec, double other_xsecerr)
    {
      // Run base class function
      xsec_container::average_xsec(other_xsec, other_xsecerr);
    }
    void process_xsec_container::average_xsec(const process_xsec_container& other)
    {
      // Check that the process code of this instance is set
      assert(_process_code > 0);
      // Check that we are working with the same process code
      assert(other.process_code() == _process_code);
      // @todo Should we also check the content of the vectors 
      //       _processes_sharing_xsec and _related_pid_pairs?
      process_xsec_container::average_xsec(other.xsec(), other.xsec_err());
    }

    /// Sum cross-sections and add errors in quadrature.
    void process_xsec_container::sum_xsecs(double other_xsec, double other_xsecerr)
    {
      // Run base class function
      xsec_container::sum_xsecs(other_xsec, other_xsecerr);
    }
    void process_xsec_container::sum_xsecs(const process_xsec_container& other)
    {
      // Check that the process code of this instance is set
      assert(_process_code > 0);
      // Check that we are working with the same process code
      assert(other.process_code() == _process_code);
      // @todo Should we also check the content of the vectors 
      //       _processes_sharing_xsec and _related_pid_pairs?
      process_xsec_container::sum_xsecs(other.xsec(), other.xsec_err());
    }


    /// Return the process code
    int process_xsec_container::process_code() const 
    { return _process_code; }

    /// Set the process code
    void process_xsec_container::set_process_code(int process_code_in) 
    { _process_code = process_code_in; } 

    /// Return the list of process codes that share this cross-section 
    /// (This is due to the many-to-many mapping between Pythia process 
    /// codes and the PID pairs we use as basis for external cross-section calculations)
    const std::vector<int>& process_xsec_container::processes_sharing_xsec() const 
    { return _processes_sharing_xsec; }

    /// Add a process code to the list of processes sharing this cross-section, 
    void process_xsec_container::register_process_sharing_xsec(int process_code_in) 
    { 
      if(std::find(_processes_sharing_xsec.begin(), _processes_sharing_xsec.end(), process_code_in) == _processes_sharing_xsec.end())
      {
        _processes_sharing_xsec.push_back(process_code_in); 
      }
    }

    /// Return the list of PID pairs related to this cross-section
    const std::vector<PID_pair>& process_xsec_container::related_pid_pairs() const 
    { return _related_pid_pairs; } 

    /// Add a PID pair to the list of PID pairs related to this cross-section
    void process_xsec_container::register_related_pid_pair(PID_pair pid_pair_in) 
    { 
      if(std::find(_related_pid_pairs.begin(), _related_pid_pairs.end(), pid_pair_in) == _related_pid_pairs.end())
      {
        _related_pid_pairs.push_back(pid_pair_in); 
      }
    }  



    /// 
    /// Definitions of PID_pair_xsec_container members
    ///

    /// Constructor
    PID_pair_xsec_container::PID_pair_xsec_container() : 
      xsec_container::xsec_container(),
      _pid_pair(PID_pair()),
      _pid_pairs_sharing_xsec(std::vector<PID_pair>()),
      _related_processes(std::vector<int>())
    { }

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void PID_pair_xsec_container::reset()
    {
      xsec_container::reset();
      _pid_pair = PID_pair();
      _pid_pairs_sharing_xsec.clear();
      _related_processes.clear();
    }

    /// Average cross-sections and combine errors.
    void PID_pair_xsec_container::average_xsec(double other_xsec, double other_xsecerr)
    {
      // Run base class function
      xsec_container::average_xsec(other_xsec, other_xsecerr);
    }
    void PID_pair_xsec_container::average_xsec(const PID_pair_xsec_container& other)
    {
      // Check that the PID pair of this instance is set
      assert((_pid_pair.pid1() != 0) && (_pid_pair.pid2() != 0));
      // Check that we are working with the same PID pair
      assert(other.pid_pair() == _pid_pair);
      // @todo Should we also check the content of the vectors 
      //       _pid_pairs_sharing_xsec and _related_processes?
      PID_pair_xsec_container::average_xsec(other.xsec(), other.xsec_err());
    }

    /// Sum cross-sections and add errors in quadrature.
    void PID_pair_xsec_container::sum_xsecs(double other_xsec, double other_xsecerr)
    {
      // Run base class function
      xsec_container::sum_xsecs(other_xsec, other_xsecerr);
    }
    void PID_pair_xsec_container::sum_xsecs(const PID_pair_xsec_container& other)
    {
      // Check that the PID pair of this instance is set
      assert((_pid_pair.pid1() != 0) && (_pid_pair.pid2() != 0));
      // Check that we are working with the same PID pair
      assert(other.pid_pair() == _pid_pair);
      // @todo Should we also check the content of the vectors 
      //       _pid_pairs_sharing_xsec and _related_processes?
      PID_pair_xsec_container::sum_xsecs(other.xsec(), other.xsec_err());
    }

    /// Return the PID pair
    const PID_pair& PID_pair_xsec_container::pid_pair() const 
    { return _pid_pair; }

    /// Set the PID pair
    void PID_pair_xsec_container::set_pid_pair(const PID_pair& pid_pair_in) 
    { _pid_pair = pid_pair_in; } 

    /// Return the list of PID pairs that share this cross-section 
    /// (This is due to the many-to-many mapping between Pythia process 
    /// codes and the PID pairs we use as basis for external cross-section calculations)
    const std::vector<PID_pair>& PID_pair_xsec_container::pid_pairs_sharing_xsec() const 
    { return _pid_pairs_sharing_xsec; }

    /// Add a PID pair to the list of PID pairs sharing this cross-section 
    void PID_pair_xsec_container::register_pid_pair_sharing_xsec(PID_pair pid_pair_in) 
    { 
      if(std::find(_pid_pairs_sharing_xsec.begin(), _pid_pairs_sharing_xsec.end(), pid_pair_in) == _pid_pairs_sharing_xsec.end())
      {
        _pid_pairs_sharing_xsec.push_back(pid_pair_in); 
      }
    }

    /// Return the list of process codes related to this cross-section
    const std::vector<int>& PID_pair_xsec_container::related_processes() const 
    { return _related_processes; } 

    /// Add a process code to the list of processes related to this cross-section
    void PID_pair_xsec_container::register_related_process(int process_code_in) 
    { 
      if(std::find(_related_processes.begin(), _related_processes.end(), process_code_in) == _related_processes.end())
      {
        _related_processes.push_back(process_code_in); 
      }
    }  


  }
}
