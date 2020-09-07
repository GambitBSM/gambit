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
///        2016 Aug
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
#include "gambit/Logs/logger.hpp"
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

    const bool verbose = false;

    // If you add to the following message tags, make sure to update the enum in log_tags.hpp that tracks the number of them!

    // Function to retrieve the 'msgtypes' set of tags
    const std::set<LogTag>& msgtypes()
    {
      static LogTag msg_a[] = {debug, info, warn, err};
      static const std::set<LogTag> msgtypes_set(msg_a, msg_a+sizeof(msg_a)/sizeof(msg_a[0]));
      return msgtypes_set;
    }

    // Function to retrieve the 'flags' set of tags
    const std::set<LogTag>& flags()
    {
      static LogTag flags_a[] = {fatal, nonfatal};
      static const std::set<LogTag> flags_set(flags_a, flags_a+sizeof(flags_a)/sizeof(flags_a[0]));
      return flags_set;
    }

    // Function to retrieve the 'echoes' set of tags
    const std::set<LogTag>& echoes()
    {
      static LogTag echoes_a[] = {repeat_to_cout, repeat_to_cerr};
      static const std::set<LogTag> echoes_set(echoes_a, echoes_a+sizeof(echoes_a)/sizeof(echoes_a[0]));
      return echoes_set;
    }

    // Function to retrieve the 'components' set of tags (needed by module and backend macros so they can add to it)
    std::set<int>& components()
    {
      // We add the core components here, but the module and backend numbers are added later, so the set cannot be const.
      static LogTag core_a[] = {def, core, logs, models, dependency_resolver, scanner, inifile, printers, utils, backends};
      static std::set<int> components_set(core_a, core_a+sizeof(core_a)/sizeof(core_a[0]));
      return components_set;
    }

    // String names for enums
    static std::map<int,std::string> create_tag_names()
    {
       std::map<int,std::string> m;
       m[debug]   = "Debug";
       m[info]    = "Info";
       m[warn]    = "Warning";
       m[err]     = "Error";
       /* Flags */
       m[fatal]   = "Fatal";
       m[nonfatal]= "Non-fatal";
       /* Repeaters */
       m[repeat_to_cout]   = "Echo > stout";
       m[repeat_to_cerr]= "Echo > sterr";
       /* Component tags */
       m[def]     = "Default";
       m[core]    = "Core";
       m[logs] = "Logger";
       m[models]  = "Models";
       m[dependency_resolver]  = "Dependency Resolver";
       m[scanner]    = "Scanner";
       m[inifile] = "IniFile";
       m[printers]= "Printers";
       m[utils]   = "Utilities";
       m[backends]= "Backends";

       // Test numbers:
       if (verbose)
       {
         std::cout<<"Checking LogTag numbers..."<<std::endl;
         for(std::map<int,std::string>::iterator tag = m.begin(); tag != m.end(); ++tag)
         {
           std::cout<<"  "<<tag->first<<" : "<<tag->second<<std::endl;
         }
       }

       return m;
    }

    // Function to retrieve the 'tag2str' map outside of this compilation unit
    // (needed by module and backend macros so they can add to it)
    std::map<int,std::string>& tag2str()
    {
      // Can't be const because we will add to it from the module/backend macros
      static std::map<int,std::string> tag2str_map = create_tag_names();
      return tag2str_map;
    }

    // Function to return the next unused tag index
    int getfreetag()
    {
      for(int i=0; i<std::numeric_limits<int>::max(); ++i)
      {
        if( tag2str().count(i) == 0 ) { return i; }
      }
      // Uh oh, seems like we ran out of integers. If this happens you are screwed, and we have to rewrite the code to use long ints instead, or you have to unhook some modules.
      // Cannot log this because we are outside the LogMaster class code.
      std::ostringstream ss;
      ss << "Error in logger.cpp! It seems that you have so many logging tags that you have exceeded the maximum allowed integer. There is no way you can fix this except to have fewer modules hooked up to gambit all at once. Otherwise we have to rewrite the logger to work with long ints or some such" << std::endl;
      throw std::overflow_error( ss.str() );
    }

    // Function to do the reverse search (brute force)
    int str2tag(const std::string& tagname)
    {
       for(std::map<int,std::string>::iterator tag = tag2str().begin(); tag != tag2str().end(); ++tag)
       {
         if (tag->second == tagname) { return tag->first; }
       }
       // Uh oh, no match found. Return fail code and let caller deal with it
       return -1;
    }

    /// Function to inspect tags and their associated strings. For testing purposes only
    void checktags()
    {
       std::cout<<"Checking message type LogTags..."<<std::endl;
       for(std::set<LogTag>::iterator tag = msgtypes().begin(); tag != msgtypes().end(); ++tag)
       {
         std::cout<<"  "<<*tag<<" : "<<tag2str()[*tag]<<std::endl;
       }
       std::cout<<"Checking message flag LogTags..."<<std::endl;
       for(std::set<LogTag>::iterator tag = flags().begin(); tag != flags().end(); ++tag)
       {
         std::cout<<"  "<<*tag<<" : "<<tag2str()[*tag]<<std::endl;
       }
       std::cout<<"Checking message echo LogTags..."<<std::endl;
       for(std::set<LogTag>::iterator tag = echoes().begin(); tag != echoes().end(); ++tag)
       {
         std::cout<<"  "<<*tag<<" : "<<tag2str()[*tag]<<std::endl;
       }
       std::cout<<"Checking Gambit component LogTags..."<<std::endl;
       for(std::set<int>::iterator tag = components().begin(); tag != components().end(); ++tag)
       {
         std::cout<<"  "<<*tag<<" : "<<tag2str()[*tag]<<std::endl;
       }
       std::cout<<"LogTag check finished."<<std::endl;
    }


    /// Constructor for SortedMessage struct
    SortedMessage::SortedMessage(const Message& mail)
      : message(mail.message), received_at(mail.received_at)
    {
       // First task is to scan through the tags and figure out where the message is supposed to go
       //std::cout<<"Sorting tags..."<<std::endl;
       for(std::set<int>::iterator tag = mail.tags.begin(); tag != mail.tags.end(); ++tag)
       {
         // Debugging crap... to be deleted.
         // std::cout<<"Sorting tag "<<tag2str()[*tag]<<std::endl;
         // std::cout<<"empty?"<<components().empty()<<std::endl;
         // for(std::set<int>::iterator tag2 = components().begin(); tag2 != components().end(); ++tag2)
         // {
         //    std::cout<<"componentI: "<<*tag2<<std::endl;
         //    std::cout<<"component:  "<<tag2str()[*tag2]<<std::endl;
         // }
         // for(std::set<LogTag>::iterator tag3 = msgtypes().begin(); tag3 != msgtypes().end(); ++tag3)
         // {
         //    std::cout<<"msgtypeI: "<<*tag3<<std::endl;
         //    std::cout<<"msgtype:  "<<tag2str()[*tag3]<<std::endl;
         // }
         // std::cout<<"core:"<<*(components().find(core))<<std::endl;
         // std::cout<<"t1 "<<*(components().find(*tag))<<std::endl;
         // std::cout<<"t2 "<<*(components().end())<<std::endl;
         // std::cout<<"tag "<<*tag<<std::endl;
         // std::cout<<"tag "<<static_cast<LogTag>(*tag)<<std::endl;
         // std::cout<<"mt1 "<<*(msgtypes().find(static_cast<LogTag>(*tag)))<<std::endl;
         // std::cout<<"mt2 "<<*(msgtypes().end())<<std::endl;
         if ( msgtypes().find(static_cast<LogTag>(*tag)) != msgtypes().end() )
         {
           // If tag is a message type, add it to the type_tags set
           //std::cout<<"Identified tag '"<<tag2str()[*tag]<<"' as message type"<<std::endl;
           type_tags.insert(static_cast<LogTag>(*tag));
         }
         else if ( components().find(*tag) != components().end() )
         {
           // std::cout<<"Adding tag "<<tag2str()[*tag]<<std::endl;
           // If tag names a gambit core component, add it to the component_tags set
           //std::cout<<"Identified tag '"<<tag2str()[*tag]<<"' as Gambit component"<<std::endl;
           component_tags.insert(*tag);
         }
         else if ( flags().find(static_cast<LogTag>(*tag)) != flags().end() )
         {
           // If tag is an auxiliary message flag, add it to the flag_tags set
           //std::cout<<"Identified tag '"<<tag2str()[*tag]<<"' as message flag"<<std::endl;
           flag_tags.insert(static_cast<LogTag>(*tag));
         }
         else if ( echoes().find(static_cast<LogTag>(*tag)) != echoes().end() )
         {
           // If tag is a message echo flag, add it to the echo_tags set
           //std::cout<<"Identified tag '"<<tag2str()[*tag]<<"' as message echo flag"<<std::endl;
           echo_tags.insert(static_cast<LogTag>(*tag));
         }
         else
         {
           // If tag was not in of those categories, it shouldn't have been a valid LogTag, and so there should have been a compiler error before now. Since there wasn't, there is something wrong with the LogTag definitions, the tag categories, or this function.
           // TODO: Gambit error! Really bad one that can't be logged.
           // I think we are converging on the idea that this type of error should just throw an ordinary exception.
           std::ostringstream ss;
           ss << "Error in SortedMessage constructor! One of the tags received could not be found in any of the const LogTag sets. This is supposed to be impossible. Please check that all tags in the LogTags enum (in logger.hpp) are also listed in one (and only one) of the (const) category sets (also in logger.hpp). If this seems fine the problem may be in the code which generates the integer codes for the modules and backends (not yet written...). Tag was number: "<< *tag<<"; name: "<< tag2str()[*tag];
           throw std::logic_error( ss.str() );
         }
       } //end tag sorting
    } // end SortedMessage constructor

    /// %%%% Logger classes %%%

    // Apparantly this cannot be virtual, so provide an implementation for it
    BaseLogger::~BaseLogger() {}

    /// "Standard" logger class

    /// Constructor
    /// Attach logger object to an existing stream
    StdLogger::StdLogger(std::ostream& logstream) 
      : my_stream(logstream)
      , MPIrank(0)
      , MPIsize(1)
    {
      #ifdef WITH_MPI
      if(GMPI::Is_initialized())
      {
        GMPI::Comm COMM_WORLD;
        MPIsize = COMM_WORLD.Get_size();
        MPIrank = COMM_WORLD.Get_rank();
      }
      #endif
      // Check error bits on stream and throw exception in anything is bad
      if( my_stream.fail() | my_stream.bad() )
      {
        std::ostringstream ss;
        ss << "IO error while constructing StdLogger! Error bit on in supplied ostream.";
        throw std::runtime_error( ss.str() );
      }
    }

    /// Open new file stream and manage it internally
    StdLogger::StdLogger(const std::string& filename)
      : my_own_fstream(filename, std::ofstream::out)
      , my_stream(my_own_fstream)
      , MPIrank(0)
      , MPIsize(1)
    {
      #ifdef WITH_MPI
      if(GMPI::Is_initialized() && !GMPI::Is_finalized())
      {
        GMPI::Comm COMM_WORLD;
        MPIsize = COMM_WORLD.Get_size();
        MPIrank = COMM_WORLD.Get_rank();
      }
      #endif
      // Check error bits on stream and throw exception in anything is bad
      if( my_stream.fail() | my_stream.bad() )
      {
         std::ostringstream ss;
         #ifdef WITH_MPI
         ss << "rank "<<MPIrank<<": ";
         #endif
         ss << "IO error while constructing StdLogger! Tried to open ofstream to file \""<<filename<<"\", but encountered error bit in the created ostream.";
         throw std::runtime_error( ss.str() );
      }
    }

    StdLogger::~StdLogger() {}

    /// Write message to log file
    void StdLogger::write(const SortedMessage& mail)
    {
      // Message reception time (UTC)
      my_stream<<"("<<Utils::return_time_and_date(mail.received_at)<<")";
      // Seconds elapsed since start_time
      std::chrono::duration<double> diff = mail.received_at - start_time;
      my_stream<<"("<<diff.count()<<" [s])";
      // MPI rank
      // Might as well add this even if different ranks output to different
      // files, since people might like to cat together the different files
      // later on or something.
      if(MPIsize>1) my_stream << "(Rank " << MPIrank << ")";

      // Message tags
      writetags(mail.component_tags);
      writetags(mail.type_tags);
      writetags(mail.flag_tags);
      my_stream<<":"<<std::endl;
      // Message proper
      my_stream<<mail.message<<std::endl;
      my_stream<<"--<>--<>--<>--<>--<>--<>--<>--"<<std::endl;
      // (I picked a weird end of message boundary so that it would be easily distinguished from formatting that may appear in the message body)
    }

    void StdLogger::writetags(const std::set<LogTag>& tags)
    {
      // If we can figure out how to cast set<LogTag> to set<int> then we can do this better
      std::set<int> int_tags;
      for(std::set<LogTag>::iterator tag = tags.begin(); tag != tags.end(); ++tag)
      {
        int_tags.insert(*tag); //static_cast<int>(*tag);
      }
      writetags(int_tags);
    }

    void StdLogger::writetags(const std::set<int>& tags)
    {
      std::set<int>::iterator it;

      if( not tags.empty() )
      {
        my_stream<<"[";
        bool firstloop = true;
        for (it = tags.begin(); it != tags.end(); ++it)
        {
          if (not firstloop) { my_stream<<","; }
          //std::cout<<"test: "<<*it<<std::endl;
          //std::cout<<"test2:"<<tag2str().at(*it)<<std::endl;
          my_stream << tag2str().at(*it); // replace with a lookup of the correct string
          firstloop = false;
        }
        my_stream<<"]";
      }
    }

    /// Flush stream buffer
    // Possibly unnecessary...
    void StdLogger::flush()
    {
      my_stream.flush();
    }

    /// Destructor
    /// Ensure cached messages are dumped
    // (do we need a cache? linux filesystem probably does this for us...)
    // ~StdLogger::StdLogger()


  } //end namespace Logging
} // end namespace Gambit
