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

#include <vector>
#include <map>
#include <string>
#include "gambit/Utils/PID_pair.hpp"


#pragma once

namespace Gambit
{

  namespace ColliderBit
  {


    /// A base class for holding cross-section info within ColliderBit.
    class xsec_container
    {
      public:

        xsec_container();
        virtual ~xsec_container() { }

        /// Reset this instance for reuse.
        void reset();

        /// Return the full cross-section (in fb).
        double operator()() const;
        double xsec() const;

        /// Return the cross-section error (in fb).
        double xsec_err() const;

        /// Return the cross-section relative error.
        double xsec_relerr() const;

        /// Set the cross-section and its error (in fb).
        void set_xsec(double, double);

        /// Average cross-sections and combine errors.
        void average_xsec(double, double);
        void average_xsec(const xsec_container&);

        /// Sum cross-sections and add errors in quadrature.
        void sum_xsecs(double, double);
        void sum_xsecs(const xsec_container&);

        /// Get content as map <string,double> map (for easy printing).
        std::map<std::string, double> get_content_as_map() const;

        /// Set the info string
        void set_info_string(std::string);

        /// Get the info string
        std::string info_string() const;

        /// Set the trust level
        void set_trust_level(int);

        /// Get the trust level
        int trust_level() const;

        /// String Let's make it clear that we work with fb as unit
        static const std::string unit;

      protected:

        double _xsec;
        double _xsecerr;
        std::string _info_string;
        int _trust_level;
    };


    /// A class for holding a total cross-section calculated via MC across multiple threads
    class MC_xsec_container : public xsec_container
    {

      public:

        MC_xsec_container();
        virtual ~MC_xsec_container() { }

        /// Reset this instance for reuse.
        void reset();

        /// Tell the xsec object that there has been a new event.
        void log_event();

        /// Return the total number of events seen so far.
        long long num_events() const;

        /// Return the cross-section per event seen (in fb).
        double xsec_per_event() const;

        /// Set the total number of events seen so far.
        void set_num_events(long long);


        /// Average cross-sections and combine errors.
        void average_xsec(double, double, long long);
        void average_xsec(const MC_xsec_container&);

        /// Sum cross-sections and add errors in quadrature.
        void sum_xsecs(double, double, long long);
        void sum_xsecs(const MC_xsec_container&);

        /// Collect xsec predictions from other threads and do a weighted combination.
        void gather_xsecs();

        /// Collect total events seen on all threads.
        void gather_num_events();

        /// Get content as map <string,double> map (for easy printing).
        std::map<std::string, double> get_content_as_map() const;

      private:

        long long _ntot;

        /// A map with pointers to all instances of this class. The key is the OMP thread number.
        static std::map<int, const MC_xsec_container*> instances_map;
    };



    /// A class for holding the cross-section of a single Pythia process (identified by the Pythia process code)
    class process_xsec_container : public xsec_container
    {

      public:
        process_xsec_container();
        virtual ~process_xsec_container() { }

        /// Reset this instance for reuse.
        void reset();

        /// Average cross-sections and combine errors.
        void average_xsec(double, double);
        void average_xsec(const process_xsec_container&);

        /// Sum cross-sections and add errors in quadrature.
        void sum_xsecs(double, double);
        void sum_xsecs(const process_xsec_container&);

        /// Return the process code
        int process_code() const;

        /// Set the process code
        void set_process_code(int);

        /// Return the list of process codes that share this cross-section 
        /// (This is due to the many-to-many mapping between Pythia process 
        /// codes and the PID pairs we use as basis for external cross-section calculations)
        const std::vector<int>& processes_sharing_xsec() const;

        /// Add a process code to the list of processes sharing this cross-section 
        void register_process_sharing_xsec(int);

        /// Return the list of PID pairs related to this cross-section
        const std::vector<PID_pair>& related_pid_pairs() const; 

        /// Add a PID pair to the list of processes related to this cross-section
        void register_related_pid_pair(PID_pair); 

      private:
        int _process_code;
        std::vector<int> _processes_sharing_xsec;
        std::vector<PID_pair> _related_pid_pairs;
    };



    /// A class for holding the production cross-section for final state identified by the pair of PID codes
    class PID_pair_xsec_container : public xsec_container
    {

      public:
        PID_pair_xsec_container();
        virtual ~PID_pair_xsec_container() { }

        /// Reset this instance for reuse.
        void reset();

        /// Average cross-sections and combine errors.
        void average_xsec(double, double);
        void average_xsec(const PID_pair_xsec_container&);

        /// Sum cross-sections and add errors in quadrature.
        void sum_xsecs(double, double);
        void sum_xsecs(const PID_pair_xsec_container&);

        /// Return the PID pair
        const PID_pair& pid_pair() const;

        /// Set the PID pair
        void set_pid_pair(const PID_pair&);

        /// Return the list of PID pairs that share this cross-section 
        /// (This is due to the many-to-many mapping between Pythia process 
        /// codes and the PID pairs we use as basis for external cross-section calculations)
        const std::vector<PID_pair>& pid_pairs_sharing_xsec() const;

        /// Add a PID pair to the list of PID pairs sharing this cross-section 
        void register_pid_pair_sharing_xsec(PID_pair);

        /// Return the list of process codes related to this cross-section
        const std::vector<int>& related_processes() const; 

        /// Add a process code to the list of processes related to this cross-section
        void register_related_process(int); 

      private:
        PID_pair _pid_pair;
        std::vector<PID_pair> _pid_pairs_sharing_xsec;
        std::vector<int> _related_processes;
    };

  }
}
