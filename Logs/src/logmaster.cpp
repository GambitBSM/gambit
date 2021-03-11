//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Member functions of logging classes
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
///  \date 2014 Mar, May
///
///  *********************************************


// Standard libraries
#include <set>
#include <fstream>
#include <cstdarg>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <chrono>
#include <omp.h>

// Gambit
#include "gambit/Logs/logmaster.hpp"
#include "gambit/Logs/logging.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/cmake/cmake_variables.hpp"

// Code!
namespace Gambit
{

  namespace Logging
  {
    using namespace LogTags;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    /// @{ Logger class member function definitions
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /// Logging "controller" object
    /// Keeps track of the individual logging objects.
    LogMaster::LogMaster()
      : loggers_readyQ (false)
      , silenced       (false)
      , separate_file_per_process(true)
      , log_debug_messages(false)
      , MPIrank        (0)
      , MPIsize        (1)
      , globlMaxThreads(omp_get_max_threads())
      , current_module (NULL)
      , current_backend(NULL)
      , stream         (NULL)
      , streamtags     (NULL)
      , backlog        (NULL)
    {
      // Note! MPIrank and MPIsize will not be correct until initialisation occurs!
    }

    /// Alternate constructor
    // Mainly for testing; lets you pass in pre-built loggers and their tags
    LogMaster::LogMaster(std::map<std::set<int>,BaseLogger*>& loggersIN)
      : loggers        (loggersIN)
      , loggers_readyQ (true)
      , silenced       (false)
      , separate_file_per_process(true)
      , log_debug_messages(false)
      , MPIrank        (0)
      , MPIsize        (1)
      , globlMaxThreads(omp_get_max_threads())
      , current_module (NULL)
      , current_backend(NULL)
      , stream         (NULL)
      , streamtags     (NULL)
      , backlog        (NULL)
    {
      // Note! MPIrank and MPIsize will not be correct until initialisation occurs!
    }

    // Initialise dynamic memory required for thread safety
    void LogMaster::init_memory()
    {
      int n = globlMaxThreads;
      // Reserve enough space to hold as many variables as there are slots (threads) allowed
      if(stream==NULL)
      {
        #pragma omp critical(logmaster_common_init_memory_stream)
        {
          if(stream==NULL) stream = new std::ostringstream[n];
        }
      }
      if(streamtags==NULL)
      {
        #pragma omp critical(logmaster_common_init_memory_streamtags)
        {
          if(streamtags==NULL) streamtags = new std::set<int>[n];
        }
      }
      if(backlog==NULL)
      {
        #pragma omp critical(logmaster_common_init_memory_backlog)
        {
          if(backlog==NULL) backlog = new std::deque<Message>[n];
        }
      }
      if(current_module==NULL)
      {
        #pragma omp critical(logmaster_common_init_memory_current_module)
        {
          if(current_module==NULL) current_module = new int[n];
          std::fill(current_module, current_module+n, -1);
        }
      }
      if(current_backend==NULL)
      {
        #pragma omp critical(logmaster_common_init_memory_current_backend)
        {
          if(current_backend==NULL) current_backend = new int[n];
          std::fill(current_backend, current_backend+n, -1);
        }
      }
    }

    // Print the backlogs to the default log file
    void LogMaster::emit_backlog(bool verbose)
    {
       if (backlog!=NULL)
       {
         bool backlog_empty = true;
         for(int i=0; i<globlMaxThreads; i++)
         {
            if(backlog[i].size()!=0) backlog_empty = false;
         }
         if (not backlog_empty)
         {
           if (verbose) *this<<"Logger backlog buffer not empty during LogMaster destruction; attempting to deliver unsent messages to the logs..."<<EOM;
           // If LogMaster was never initialised, create a default log file to which the messages can be dumped.
           if (not loggers_readyQ)
           {
             if (verbose) std::cout<<"Logger was never initialised! Creating default log messenger..."<<std::endl;
             StdLogger* deflogger = new StdLogger(Utils::runtime_scratch() + "default.log");
             std::set<int> deftag;
             deftag.insert(def);
             loggers[deftag] = deflogger;
             loggers_readyQ = true;
             if (verbose) std::cout<<"Log messages will be delivered to '" << Utils::runtime_scratch() << "default.log'"<<std::endl;
           }
           // Dump buffered messages
           empty_backlog();
         }
       }
    }

    // Destructor
    LogMaster::~LogMaster()
    {
       // See signal_handling.cpp for why we should not bail out in this situation
       // // LogMaster should not be destructed from within a parallel block. This check helps detect such a bug.
       // if(omp_get_level()!=0)
       // {
       //    // Raising an error from within the loggers within a parallel block probably will not end well, just use cout.
       //    #pragma omp critical(logmaster_destructor)
       //    {
       //      std::cout << "rank "<<MPIrank<<": "<< LOCAL_INFO << ": Tried to destruct LogMaster from inside an omp parallel block! This should not be allowed to happen, please file a bug report." << std::endl;
       //      exit(EXIT_FAILURE);
       //    }
       // }

       if(not silenced)
       {
         // Check if there is anything in the output stream that has not been sent, and send it if there is
         // (these messages will get backlogged because they are sent (ended) from a parallel block, but we are
         // about to empty the backlogs anyway so that is no problem).
         if (stream != NULL and streamtags!= NULL)
         {
           #pragma omp parallel
           {
              int i = omp_get_thread_num();
              if (not stream[i].str().empty() or not streamtags[i].empty())
              {
                *this <<"#### NO EOM RECEIVED FOR MESSAGE FROM THREAD ("<<i<<"): MESSAGE MAY BE INCOMPLETE ####"<<warn<<EOM;
              }
           }
         }

         // Output the message backlogs if needed
         emit_backlog(true);

       }

       // Delete logger objects
       for(std::map<std::set<int>,BaseLogger*>::iterator keyvalue = loggers.begin(); keyvalue != loggers.end(); ++keyvalue)
       {
         // Ensure their filestreams have been flushed before we delete them.
         // (not sure if this is really needed, I think the message is in the operating systems domain by this point)
         // Edit:  I think I have decided that this is unnecessary
         //(keyvalue->second)->flush();
         delete (keyvalue->second);
       }

       // Delete the thread variables
       if (stream != NULL)         delete [] stream;
       if (streamtags != NULL)     delete [] streamtags;
       if (backlog != NULL)        delete [] backlog;
       if (current_module !=NULL)  delete [] current_module;
       if (current_backend !=NULL) delete [] current_backend;
    }

    /// Function to construct loggers according to blueprint
    // This is the function that yaml_parser.hpp uses. You provide tags as a set of strings, and the filename as a string. We then construct the logger objects in here.
    void LogMaster::initialise(std::vector<std::pair< std::set<std::string>, std::string >>& loggerinfo)
    {
       // Fix up the MPI variables
       #ifdef WITH_MPI
       if(GMPI::Is_initialized())
       {
         GMPI::Comm COMM_WORLD;
         MPIsize = COMM_WORLD.Get_size();
         MPIrank = COMM_WORLD.Get_rank();
       }
       #endif

       // Check options and inform user what they are
       if (MPIrank == 0) std::cout << "Initialising logger...";
       // NOTE! Option to merge log files no longer exists. Concurrent write access is a nightmare. Log messages were
       // being lost due to different processes overwriting each others data, and using the FileLock system doesn't
       // help because the issue is the file pointer location. To fix that, files have to be closed and reopened
       // constantly, which creates a lot of overhead. On top of this, it is very hard to overwrite old log files at the
       // beginning of the run since we have to coordinate who creates the file at the beginning of the run, would have
       // to add a bunch of message passing. Overall it just isn't worth it.
       // #ifdef WITH_MPI
       // std::cout << std::endl << "  separate_file_per_process = ";
       // if(separate_file_per_process){ std::cout << "true; log messages will be stored in separate files for each MPI process (filename will be appended with underscore + MPI rank)"; }
       // else{ std::cout << "false; log messages from separate MPI processes will be merged into one file (orchestrated by the OS; some mangling of concurrently written log messages may occur. Set this separate_file_per_process to 'True' if this mangling is a problem for you)";}
       // #endif
       std::ostringstream logmsg;
       logmsg << "  log_debug_messages = ";
       if(log_debug_messages) logmsg << "true; log messages tagged as 'Debug' WILL be logged. " << endl << "WARNING: This may lead to very large log files!";
       else
       {
          // Add "Debug" tag to the global ignore list
          ignore.insert(LogTag::debug);
          logmsg << "false; log messages tagged as 'Debug' will NOT be logged";
       }

       if (MPIrank == 0) std::cout << logmsg.str() << std::endl;
       *this << LogTag::logs << LogTag::debug << logmsg.str() << EOM;

       // Iterate through map and build the logger objects
       for(std::vector<std::pair< std::set<std::string>, std::string >>::iterator infopair = loggerinfo.begin();
            infopair != loggerinfo.end(); ++infopair)
       {
          std::set<std::string> yamltags = infopair->first;
          std::string filename = infopair->second;
          std::set<int> tags;

          if(separate_file_per_process and MPIsize>1
             and filename!="stdout" and filename!="stderr")
          {
            std::ostringstream unique_filename;
            unique_filename << filename << "_" << MPIrank;
            filename = unique_filename.str();
          }

          // Log the loggers being created :)
          // (will be put into a preliminary buffer until loggers are all constructed)
          *this << LogTag::logs << LogTag::debug << std::endl << "Creating logger for tags [";

          // Iterate through string tags and convert them to the corresponding index
          for(std::set<std::string>::iterator stag = yamltags.begin();
                stag != yamltags.end(); ++stag)
          {
            // Finding the tag index from the tag string is kind of a drag, have to do a brute search
            int newtag = str2tag(*stag);
            // Check that valid tag was found (returns -1 if no tag found)
            if(newtag==-1)
            {
              // If we didn't find the tag, raise an exception (probably means there was an error in the yaml file)
              std::ostringstream errormsg;
              errormsg << "If you have an entry something like this:"<< endl
                       << "  Logger:" << endl
                       << "    redirection:" << endl
                       << "    [" << *stag << "] : \"blah.log\"" << endl
                       << "in your yaml file, then you probably should remove the last line.  The LogTag" << endl
                       << "\"" << *stag << "\" is not recognised by the logger system.  This commonly happens" << endl
                       << "if you try to redirect log output for a module that either doesn't exist, or was" << endl
                       << "ditched at cmake time." << endl;
              logging_error().raise(LOCAL_INFO,errormsg.str());
            }
            *this << *stag <<", ";
            tags.insert(newtag);
          }
          // Build the logger object
          StdLogger* newlogger;
          if(filename=="stdout")
          {
            newlogger = new StdLogger(std::cout);
          }
          else if(filename=="stderr")
          {
            newlogger = new StdLogger(std::cerr);
          }
          else
          {
            newlogger = new StdLogger(filename);
          }
          *this << "]; output is \"" << filename << "\"";
          loggers[tags] = newlogger;
       }
       *this << EOM; // End message about loggers.
       // Set logger objects ready for use and dump any buffered messages
       loggers_readyQ = true;
       empty_backlog();
    }

    // Overload for initialise to allow input of logging instructions via maps
    void LogMaster::initialise(std::map<std::set<std::string>, std::string>& loggerinfo)
    {
       std::vector<std::pair< std::set<std::string>, std::string >> loggerinfo_vec;
       // Iterate through map and convert it to a vector of pairs
       for(std::map<std::set<std::string>, std::string>::iterator infopair = loggerinfo.begin();
            infopair != loggerinfo.end(); ++infopair)
       {
          loggerinfo_vec.push_back(std::make_pair(infopair->first,infopair->second));
       }
       // Run the 'normal' initialise function
       initialise(loggerinfo_vec);
    }

    // Overload for initialise, to make it easier to manually initialise the logger in standalone modules
    void LogMaster::initialise(std::map<std::string, std::string>& loggerinfo)
    {
      std::map<std::set<std::string>, std::string> loggerinfo_set;
      // Translate the string containing the tags into (map of) a set of tags
      for(std::map<std::string, std::string>::iterator infopair = loggerinfo.begin();
            infopair != loggerinfo.end(); ++infopair)
      {
        std::vector<std::string> tags_vec(Utils::delimiterSplit(infopair->first, ","));
        std::set<std::string> tags_set(tags_vec.begin(), tags_vec.end());
        loggerinfo_set[tags_set] = infopair->second;
      }
      // Run the 'normal' initialise function
      initialise(loggerinfo_set);
    }

    // Function to completely silence all log messages
    void LogMaster::disable()
    {
       loggers_readyQ = true;
       silenced = true;
    }

    // Turn logs back on
    void LogMaster::enable()
    {
       silenced = false;
    }

    // Function to check if all log messages are silenced
    bool LogMaster::disabled()
    {
       return silenced;
    }

    // Dump the backlog buffer to the 'finalsend' function
    void LogMaster::empty_backlog()
    {
       // See signal_handling.cpp for why we should not bail out in this situation
       //if(omp_get_level()!=0)
       //{
       //   // Raising an error from within the loggers within a parallel block probably will not end well, just use cout.
       //   #pragma omp critical(logmaster_empty_backlog)
       //   {
       //     std::cout << LOCAL_INFO << ": (rank "<<MPIrank<<") Tried to run empty_backlog() (in LogMaster) from inside an omp parallel block! This should not be possible, please file a bug report." << std::endl;
       //     exit(EXIT_FAILURE);
       //   }
       //}

       for(int i=0; i<globlMaxThreads; i++)
       {
         for(size_t j=0; j<backlog[i].size(); j++)
         {
            finalsend(backlog[i].front());
            backlog[i].pop_front();
         }
       }
    }

    /// Main logging function (user-friendly overloaded version)
    // Need a bunch of overloads of this to deal with
    void LogMaster::send(const std::string& message)
    {
      std::set<LogTag> tags;
      send(message,tags);
    }

    void LogMaster::send(const std::string& message, LogTag tag1)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      send(message,tags);
    }

    void LogMaster::send(const std::string& message, LogTag tag1, LogTag tag2)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      send(message,tags);
    }

    void LogMaster::send(const std::string& message, LogTag tag1, LogTag tag2, LogTag tag3)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      send(message,tags);
    }

    void LogMaster::send(const std::string& message, LogTag tag1, LogTag tag2, LogTag tag3, LogTag tag4)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      tags.insert(tag4);
      send(message,tags);
    }

    void LogMaster::send(const std::string& message, LogTag tag1, LogTag tag2, LogTag tag3, LogTag tag4, LogTag tag5)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      tags.insert(tag4);
      tags.insert(tag5);
      send(message,tags);
    }

    //...add more as needed

    /// stringstream versions....
    void LogMaster::send(const std::ostringstream& message)
    {
      std::set<LogTag> tags;
      send(message.str(),tags);
    }

    void LogMaster::send(const std::ostringstream& message, LogTag tag1)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      send(message.str(),tags);
    }

    void LogMaster::send(const std::ostringstream& message, LogTag tag1, LogTag tag2)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      send(message.str(),tags);
    }

    void LogMaster::send(const std::ostringstream& message, LogTag tag1, LogTag tag2, LogTag tag3)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      send(message.str(),tags);
    }

    void LogMaster::send(const std::ostringstream& message, LogTag tag1, LogTag tag2, LogTag tag3, LogTag tag4)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      tags.insert(tag4);
      send(message.str(),tags);
    }

    void LogMaster::send(const std::ostringstream& message, LogTag tag1, LogTag tag2, LogTag tag3, LogTag tag4, LogTag tag5)
    {
      std::set<LogTag> tags;
      tags.insert(tag1);
      tags.insert(tag2);
      tags.insert(tag3);
      tags.insert(tag4);
      tags.insert(tag5);
      send(message.str(),tags);
    }

    //...add more as needed


    // Overload to allow tags to be cast to ints, for delivery to the "full" send function
    void LogMaster::send(const std::string& message, std::set<LogTag>& tags)
    {
      //std::set<int>& int_tags = static_cast< std::set<int> >(tags);
      // I cannot seem to get the static cast to work, so just copying for now:
      //std::set<int> int_tags(tags);
      // Gah that seems not to work for the same reason, do one by one:
      std::set<int> int_tags;
      for(std::set<LogTag>::iterator tag = tags.begin(); tag != tags.end(); ++tag)
      {
        int_tags.insert(*tag); //static_cast<int>(*tag));
      }
      send(message, int_tags);
    }

    /// Serious version of main logging function
    // Ok this is the function that actual does things; the above are all just "syntatic sugar", as the cool kids say.
    // In the end, this function should construct all the Message structs.
    void LogMaster::send(const std::string& message, std::set<int>& tags)
    {
       // LogMaster keeps an internal map of all the logging objects, where the keys are sets of 'LogTag's, constructed according to the inifile. So to figure out where the message has to go, we just compare the "tags" to these keys; if any of these keys are a subset of our tags, then we send the message to that LogHub.
       // Well almost. We have to seperate out the components first, because we can "send" a message to multiple components at once, but a direction command will never include two component tags (it is an error if it does).

       // Testing...
       //std::cout<<"msg: "<<message<<std::endl;

       // Preliminary stuff

       // Get thread number
       int i = omp_get_thread_num();

       // Automatically add the "def" (Default) tag so that the message definitely tries to go somewhere
       tags.insert(def);

       // Automatically add the tags for the "current" module and backend to the tags list
       if (current_module[i] != -1)
       {
         //std::cout<<"current_module="<<current_module<<"; adding tag "<<tag2str()[current_module]<<std::endl;
         tags.insert(current_module[i]);
       }
       if (current_backend[i] != -1)
       {
         //std::cout<<"current_backend="<<current_backend<<"; adding tag "<<tag2str()[current_backend]<<std::endl;
         tags.insert(current_backend[i]);
       }

       // If the loggers have not yet been initialised, buffer the message
       if(omp_get_level()!=0 or not loggers_readyQ)
       {
         backlog[i].emplace_back(message,tags); //time stamp automatically added NOW
       }
       else
       {
         if(omp_get_level()==0) empty_backlog();
         finalsend(Message(message,tags)); //time stamp automatically added NOW
       }
    } // end LogHub::send

    /// Version of send function used by buffer dump; skips all the tag modification stuff
    void LogMaster::finalsend(const Message& mail)
    {
       // Check the 'ignore' set; if any of the specified tags are in this set, then do nothing more, i.e. ignore the message.
       // (need to add extra stuff to ignore modules and backends, since these cannot be normal tags)
       // Also ignore the message if logs have been 'silenced'.
       if( silenced or not Utils::is_disjoint(mail.tags, ignore) )
       {
         //std::cout<<"Ignoring message..."<<std::endl;
         return;
       }

       // If the "cout" tag is seen, repeat the message to stdout
       if(mail.tags.find(repeat_to_cout) != mail.tags.end()) std::cout << mail.message << std::endl;

       // If the "cerr" tag is seen, repeat the message to sterr
       if(mail.tags.find(repeat_to_cerr) != mail.tags.end()) std::cerr << mail.message << std::endl;

       // Sort the tags
       const SortedMessage sortedmsg(mail);

       // Main loop for message distribution

       // Loop through the map of loggers and see if any of them match subsets of 'key'.
       for(std::map<std::set<int>,BaseLogger*>::iterator keyvalue = loggers.begin(); keyvalue != loggers.end(); ++keyvalue)
       {
         // if set1 includes set2
         if( std::includes(mail.tags.begin(), mail.tags.end(),
                           (keyvalue->first).begin(), (keyvalue->first).end()) )
         {
           // Matching logger object found! Send it the sorted message object
           (keyvalue->second)->write(sortedmsg);
         }
       } //end loop over loggers
    } // end LogMaster::finalsend

    /// stringstream overloads...
    void LogMaster::send(const std::ostringstream& message, std::set<LogTag>& tags)
    {
      send(message.str(), tags);
    }

    void LogMaster::send(const std::ostringstream& message, std::set<int>& tags)
    {
      send(message.str(), tags);
    }

    void LogMaster::entering_module(int i)
    {
       init_memory();
       current_module[omp_get_thread_num()] = i;
    }

    void LogMaster::leaving_module()
    {
       init_memory();
       current_module[omp_get_thread_num()] = -1;
       leaving_backend();
    }

    void LogMaster::entering_backend(int i)
    {
       init_memory();
       current_backend[omp_get_thread_num()] = i;
       *this<<"Setting current_backend="<<i;
       *this<<logs<<debug<<EOM;
    }
    void LogMaster::leaving_backend()
    {
       init_memory();
       int cb_test;
       cb_test = current_backend[omp_get_thread_num()];
       if (cb_test == -1) return;
       current_backend[omp_get_thread_num()] = -1;
       *this<<"Restoring current_backend="<<-1;
       *this<<logs<<debug<<EOM;
    }

    /// Handle LogTag input
    void LogMaster::input(const LogTag& tag)
    {
       init_memory();
       streamtags[omp_get_thread_num()].insert(tag);
    }

    /// Handle end of message character
    void LogMaster::input(const endofmessage&)
    {
       init_memory();
       size_t i = omp_get_thread_num();
       // Collect the stream and tags, then send the message
       send(stream[i].str(), streamtags[i]);
       // Clear stream and tags for next message;
       stream[i].str(std::string()); //TODO: check that this works properly on all compilers...
       streamtags[i].clear();
    }

    /// Handle strings
    void LogMaster::input(const std::string& in)
    {
       init_memory();
       stream[omp_get_thread_num()] << in;
    }

    /// Handle various stream manipulators
    void LogMaster::input(const manip1 fp)
    {
       init_memory();
       stream[omp_get_thread_num()] << fp;
    }

    void LogMaster::input(const manip2 fp)
    {
       init_memory();
       stream[omp_get_thread_num()] << fp;
    }

    void LogMaster::input(const manip3 fp)
    {
       init_memory();
       stream[omp_get_thread_num()] << fp;
    }

    /// @}

  } //end namespace Logging
} // end namespace Gambit
