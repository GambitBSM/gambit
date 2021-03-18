//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple class for holding a sorted pair
///  of particle ID (PID) codes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2019 Sep
///  \date 2019 Nov
///
///  *********************************************

#include <utility>
#include <string>

#pragma once

namespace Gambit
{

  /// Simple class for holding a sorted pair of particle ID (PID) codes.
  /// This is essentially just a wrapper around a std::pair<int,int>, 
  /// with forced ordering (first element <= second element) and some 
  /// extra bells and whistles.
  class PID_pair
  {

    public:

      typedef std::pair<int,int> iipair;

      /// Constructors
      PID_pair() : 
        _pids(iipair({0, 0}))
      {}

      PID_pair(int pid1_in, int pid2_in)
      {
        // Use this function to ensure correct sorting
        set_pids(pid1_in, pid2_in);
      }

      PID_pair(const iipair& PIDs_in)
      {
        // Use this function to ensure correct sorting
        set_pids(PIDs_in);
      }

      /// Detstructor
      virtual ~PID_pair() { }


      /// Set PIDs, with sorting
      void set_pids(int pid1_in, int pid2_in)
      {
        if (pid1_in <= pid2_in)
        {
          _pids = iipair({pid1_in, pid2_in});
        }
        else
        {
          _pids = iipair({pid2_in, pid1_in});
        }
      }

      void set_pids(const iipair& PIDs_in)
      {
        set_pids(PIDs_in.first, PIDs_in.second);
      }


      /// Get PIDs
      const iipair& PIDs() const
      {
        return _pids;
      }

      int pid1() const
      {
        return _pids.first;
      }

      int pid2() const
      {
        return _pids.second;
      }

      /// Get the charge-conjugated PID pair
      PID_pair cc_pid_pair() const
      {
        return PID_pair(-_pids.second, -_pids.first);
      }

      /// Check if |pid1| == |pid2|
      bool is_antiparticle_pair() const
      {
        return (_pids.first == -_pids.second);
      }

      /// Relational operators, simply using the relational 
      /// operators for the underlying pair<int,int>
      bool operator== (const PID_pair& rhs) const
      { return this->_pids.first == rhs._pids.first && this->_pids.second == rhs._pids.second; }

      bool operator!= (const PID_pair& rhs) const
      { return !(*this == rhs); }

      bool operator<  (const PID_pair& rhs) const
      { return this->_pids.first < rhs._pids.first || (!(rhs._pids.first < this->_pids.first) && this->_pids.second < rhs._pids.second); }

      bool operator<= (const PID_pair& rhs) const
      { return !(rhs < *this); }

      bool operator>  (const PID_pair& rhs) const
      { return rhs < *this; }

      bool operator>= (const PID_pair& rhs) const
      { return !(*this < rhs); }


      /// Reset the PIDs
      void reset()
      {
        _pids = iipair({0,0});
      }


      /// Get the PID pair as a string: "<pid1>_<pid2>"
      std::string str() const
      {
        std::string pids_str = std::to_string(_pids.first) + "_" + std::to_string(_pids.second);
        return pids_str;
      }


    private:

      iipair _pids;
  };

}
