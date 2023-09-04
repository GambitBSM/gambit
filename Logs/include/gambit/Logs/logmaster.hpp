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

#ifndef __logmaster_hpp__
#define __logmaster_hpp__

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
#include "gambit/Logs/logger.hpp"
#include "gambit/Logs/log_tags.hpp"

namespace Gambit
{

  namespace Logging
  {
    /// Forward declarations
    struct Message;
    class BaseLogger;

    /// Logging "controller" object
    /// Keeps track of the various "Logger" objects
    class LogMaster
    {
       public:
        /// Default constructor
        LogMaster();

        /// Alternate constructor
        /// Mainly for testing; lets you pass in pre-built loggers and their tags
        LogMaster(std::map<std::set<int>,BaseLogger*>&);

        /// Destructor
        /// If errors happen before the inifile is loaded, we need to dump the log messages
        /// (that have been buffered) into a default log file. These will be log messages coming from initialisation code and so on.
        ~LogMaster();

        /// Initialise dynamic memory required for thread safety
        void init_memory();

        /// Function to construct loggers according to blueprint
        // This is the function that yaml_parser.hpp uses. You provide tags as a set of strings, and the filename as a string. We then construct the logger objects in here.
        // This needs to be a vector of pairs rather than a map in case people want duplicate output streams of certain logs. In this case there will be duplicate keys, which a map cannot allow.
        void initialise(std::vector<std::pair< std::set<std::string>, std::string>>&);

        // Overload to allow using maps as input
        void initialise(std::map<std::set<std::string>, std::string>&);

        // Overload of initialise function to allow easier manual initialisation in standalone modules
        void initialise(std::map<std::string, std::string>&);

        // Function to silence all log messages
        void disable();
        // Function to check if all log messages are silenced
        bool disabled();
        // Turn logs back on
        void enable();

        /// Print the backlogs to the default log file
        void emit_backlog(bool verbose);

        /// Functions for stream input (actual stream operators which use these are defined in logger.cpp)
        void input(const std::string&);
        void input(const LogTag&);
        void input(const endofmessage&);
        // Overloads for stream manipulators (typedefs in logger.hpp)
        void input(const manip1);
        void input(const manip2);
        void input(const manip3);

        /// Main logging function (user-friendly overloaded version)
        // Need a bunch of overloads of this to deal with
        void send(const std::string&);
        void send(const std::string&,LogTag);
        void send(const std::string&,LogTag,LogTag);
        void send(const std::string&,LogTag,LogTag,LogTag);
        void send(const std::string&,LogTag,LogTag,LogTag,LogTag);
        void send(const std::string&,LogTag,LogTag,LogTag,LogTag,LogTag);
        //...add more as needed

        // stringstream versions of the above
        void send(const std::ostringstream&);
        void send(const std::ostringstream&,LogTag);
        void send(const std::ostringstream&,LogTag,LogTag);
        void send(const std::ostringstream&,LogTag,LogTag,LogTag);
        void send(const std::ostringstream&,LogTag,LogTag,LogTag,LogTag);
        void send(const std::ostringstream&,LogTag,LogTag,LogTag,LogTag,LogTag);
        //...add more as needed

        /// Internal version of main logging function
        void send(const std::string&, std::set<LogTag>&);
        void send(const std::string&, std::set<int>&);
        void finalsend(const Message&);

        // stringstream versions...
        void send(const std::ostringstream&, std::set<LogTag>&);
        void send(const std::ostringstream&, std::set<int>&);

        /// Set the internal variables tracking which module and/or backend is currently running
        void entering_module(int);
        void leaving_module();
        void entering_backend(int);
        void leaving_backend();

        /// @{ Setters for behaviour options
        /// Must be used before "initialise" in order to have any effect
        /// Choose whether a separate log file for each MPI process is used
        /// NOW FORBIDDEN! Always must be true to avoid concurrent write access issues
        ///void set_separate_file_per_process(bool flag) {separate_file_per_process=flag;}

        /// Choose whether "Debug" tagged log messages will be ignored (i.e. not logged)
        void set_log_debug_messages(bool flag) {log_debug_messages=flag;}

        /// @}

      private:
        /// Empty the backlog buffer to the 'send' function
        void empty_backlog();

        /// Map to identify loggers
        std::map<std::set<int>,BaseLogger*> loggers;

        /// Global ignore set; if these tags/integers are seen, ignore messages containing them.
        std::set<int> ignore;

        /// Flag to set whether loggers have been initialised not
        bool loggers_readyQ;

        /// Flag to silence logger
        bool silenced;

        /// Flag to store log messages for different processes in separate files
        bool separate_file_per_process;

        /// Flag to ignore Debug tagged messages
        bool log_debug_messages;

        /// MPI variables
        int MPIrank;
        int MPIsize;

        /// Max number of threads that could potentially be running
        int globlMaxThreads;

        /// @{ Variables that need to be threadsafe

        /// int current_function; Can generalise to this if we discover that we really want to...
        int* current_module;  // index -1 means "not in any module"
        int* current_backend; // index -1 means "not in any backend"

        /// Buffer variables needed for stream logging
        std::ostringstream* stream;
        std::set<int>* streamtags;

        /// Messages sent before logger objects are created will be buffered
        /// Same for messages sent while inside omp parallel blocks
        std::deque<Message>* backlog;

        /// @}
    };

  } //end namespace Logging

} // end namespace Gambit

#endif
