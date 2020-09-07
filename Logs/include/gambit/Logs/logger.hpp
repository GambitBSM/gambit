//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Logging access header for GAMBIT. Declares
///  the minimal amount needed for standard
///  use of the logger.
///  For more advanced use, include 'logmaster.hpp'
///  as well (provides the full declaration of the
///  LogMaster class).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2014 Mar, 2016 Jan
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __logger_hpp__
#define __logger_hpp__

#include <sstream>
#include <string>
#include <map>
#include <set>
#include "gambit/Logs/log_tags.hpp"
#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{
  /// Forward declare minimial logging components needed to use logger
  namespace Logging
  {
     class LogMaster;
     /// Special (empty) struct for signalling end of message to LogMaster stream
     struct endofmessage {};

     // Function to do the reverse search of tag map (brute force)
     int str2tag(const std::string&);

     // Function to retrieve the 'tag2str' map outside of this compilation unit
     // (needed by module and backend macros so they can add to it)
     std::map<int,std::string>& tag2str();

     // Function to retrieve the 'components' set (needed by module and backend macros so they can add to it)
     std::set<int>& components();

     // Typedefs for standard stream manpulators. We need stream operator overloads for all of them.
     typedef std::ostream& (*manip1)( std::ostream& );
     typedef std::basic_ios< std::ostream::char_type, std::ostream::traits_type > ios_type;
     typedef ios_type& (*manip2)( ios_type& );
     typedef std::ios_base& (*manip3)( std::ios_base& );

     /// @{ Stream functions for use with LogMaster
     LogMaster& operator<<(LogMaster&, const std::string&);
     LogMaster& operator<<(LogMaster&, const LogTag&);
     LogMaster& operator<<(LogMaster&, const endofmessage&);
     // Overloads for stream manipulators (typedefs above)
     LogMaster& operator<<(LogMaster&, const manip1);
     LogMaster& operator<<(LogMaster&, const manip2);
     LogMaster& operator<<(LogMaster&, const manip3);

     // Stream function to convert everything else to strings before
     // feeding into LogMaster (this way no-one needs to have the full
     // declaration of the LogMaster class; I think the overhead
     // should be negligible and is worth the segregation).
     // Use 'ostringstream' so that any type with an ostream operator defined
     // will be able to stream into the loggers.
     template <typename TYPE>
     LogMaster& operator << (LogMaster& logobj, const TYPE& input)
     {
       using ::Gambit::operator<<; // Unhide operator overloads in Gambit scope
       std::stringstream ss;
       ss << input;
       logobj << ss.str();
       return logobj;
     }
     // Non-const copy
     template <typename TYPE>
     LogMaster& operator << (LogMaster& logobj, TYPE& input)
     {
       using ::Gambit::operator<<; // Unhide operator overloads in Gambit scope
       std::stringstream ss;
       ss << input;
       logobj << ss.str();
       return logobj;
     }
     /// @}
  }

  /// Explicit const instance of the end of message struct in Gambit namespace
  const Logging::endofmessage EOM = Logging::endofmessage();

  /// Function to retrieve a reference to the Gambit global log object.
  Logging::LogMaster& logger();

}

#endif /* defined(__logger_hpp__) */
