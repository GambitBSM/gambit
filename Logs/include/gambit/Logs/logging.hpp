//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Header for logging classes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2014 Mar
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __logging_hpp__
#define __logging_hpp__

// Standard libraries
#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <fstream>
#include <chrono> 
#include <omp.h>

// Gambit
#include "gambit/Logs/logger.hpp" // Minimal declarations needed to use logger -- most code should only need to include this.
#include "gambit/Logs/log_tags.hpp"
#include "gambit/Utils/file_lock.hpp"
//#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
  // Forward declarations from Utils. Saves including the entire header for a trivial thing
  namespace Utils
  {
    typedef std::chrono::time_point<std::chrono::system_clock> time_point;
    /// Get clock time
    time_point get_clock_now();
  }

  namespace Logging
  {

    // Global reference start time. Can only be used in this compile unit.
    static const Utils::time_point start_time(Utils::get_clock_now());

    // Function to retrieve the 'msgtypes' set
    const std::set<LogTag>& msgtypes();

    // Function to retrieve the 'flags' set
    const std::set<LogTag>& flags();
 
    // Function to retrieve the 'echoes' set
    const std::set<LogTag>& echoes();

    // Function to return the next unused tag index
    // (needed by module and backend macros so they can determine what tag they are allowed to use)
    int getfreetag();

    /// Function to inspect tags and their associated strings. For testing purposes only.
    void checktags();

    /// structure for storing log messages and metadata
    struct Message
    {
        std::string message;
        std::set<int> tags;
        Utils::time_point received_at;
        /// Constructor
        Message(const std::string& msgIN, 
                const std::set<int>& tagsIN)
          : message(msgIN), 
            tags(tagsIN), 
            received_at(Utils::get_clock_now())
        {}
    };

    /// structure for storing log messages and metadata after tags are sorted
    struct SortedMessage
    {
        const std::string& message; //lives on in original Message object, so can be a reference safely I think
        const Utils::time_point& received_at; //ditto
        // couldn't figure out how to nicely initialise these in the constructor list, so not const
        // now happens in body of constructor
        std::set<LogTag> type_tags;      //message types
        std::set<int> component_tags;    //gambit components, modules, and backends
        std::set<LogTag> flag_tags;      //extra message flags      
        std::set<LogTag> echo_tags;      //message echo flags      
        // Constructor (does the sorting of the tags)
        SortedMessage(const Message& mail);
    };


    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% Logger class declarations                           %
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
    /// Logger virtual base class
    class BaseLogger
    {
      public:
        /// Virtual destructor so we can delete the loggers by pointer to base
        virtual ~BaseLogger();

        /// Write message
        virtual void write(const SortedMessage&) = 0;

        /// Flush stream buffer;
        virtual void flush() = 0;
    };

    /// Logger for 'standard' messages
    class StdLogger : public BaseLogger
    {
      public:
        /// Constructor
        // Attach logger object to an existing stream
        StdLogger(std::ostream&);
    
        /// Alternate constructor
        // Opens a file and takes care of the stream itself
        StdLogger(const std::string&);
  
        /// Destructor
        virtual ~StdLogger();

        /// Write message
        virtual void write(const SortedMessage&);
        
        /// Flush stream buffer
        virtual void flush();
 
        /// Look up names corresponding to tags and write them out to the stream
        void writetags(const std::set<LogTag>&);   
        void writetags(const std::set<int>&);   
 
      private:
        std::ofstream my_own_fstream; //Don't use this except in constructor
        std::ostream& my_stream;
 
        /// MPI variables
        int MPIrank;
        int MPIsize;
    };

  } //end namespace Logging

} // end namespace Gambit

#endif
