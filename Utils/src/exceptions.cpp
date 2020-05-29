//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Threadsafe exception class definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  Distantly inspired by SUFIT classes of the
///  same name by Johan Lundberg, Aug 2011.
///
///  *********************************************

#include <string>
#include <iostream>
#include <algorithm>
#include <omp.h>

#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Utils/exceptions.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Logs/logger.hpp"

namespace Gambit
{
    using namespace std;
    using namespace LogTags;
    typedef std::string str;

    // Public members of GAMBIT exception base class.

    /// Constructor without log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      exception_map()[inikey] = this;
    }

    /// Constructor with 1 log tag
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      exception_map()[inikey] = this;
    }

    /// Constructor with 2 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      exception_map()[inikey] = this;
    }

    /// Constructor with 3 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2, LogTag t3) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      myLogTags.insert(t3);
      exception_map()[inikey] = this;
    }

    /// Constructor with 4 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2, LogTag t3, LogTag t4) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      myLogTags.insert(t3);
      myLogTags.insert(t4);
      exception_map()[inikey] = this;
    }

    /// Constructor with 5 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      myLogTags.insert(t3);
      myLogTags.insert(t4);
      myLogTags.insert(t5);
      exception_map()[inikey] = this;
    }

    /// Constructor with 6 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5, LogTag t6) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      myLogTags.insert(t3);
      myLogTags.insert(t4);
      myLogTags.insert(t5);
      myLogTags.insert(t6);
      exception_map()[inikey] = this;
    }

    /// Constructor with 7 log tags
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal,
     LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5, LogTag t6, LogTag t7) :
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      myLogTags.insert(t1);
      myLogTags.insert(t2);
      myLogTags.insert(t3);
      myLogTags.insert(t4);
      myLogTags.insert(t5);
      myLogTags.insert(t6);
      myLogTags.insert(t7);
      exception_map()[inikey] = this;
    }

    /// Constructor with log tags as a set
    exception::exception(const char* kind, const char* what, const char* message, const char* inikey, bool fatal, std::set<LogTag> tags) :
     myLogTags             (tags),
     myKind                (kind),
     myWhat                (what),
     myShortWhat           (what),
     myMessage             (message),
     isFatal               (fatal)
    {
      exception_map()[inikey] = this;
    }

    /// Setter for the fatal flag.
    void exception::set_fatal(bool fatal)
    {
      #pragma omp critical (GAMBIT_exception)
      {
        isFatal = fatal;
      }
    }

    /// Retrieve the identity of the exception.
    const char* exception::what() const throw()
    {
      return myWhat.c_str();
    }

    /// Raise the exception.
    /// Log the exception and, if it is considered fatal, actually throw it.
    /// This is the regular way to trigger a GAMBIT error or warning.
    void exception::raise(const std::string& origin, const std::string& specific_message)
    {
      str full_message = isFatal ? specific_message+parameters : specific_message;
      #pragma omp critical (GAMBIT_exception)
      {
        log_exception(origin, full_message);
      }
      if (isFatal) throw_iff_outside_parallel();
    }

    /// Log the exception and throw it regardless of whether is is fatal or not.
    void exception::forced_throw(const std::string& origin, const std::string& specific_message)
    {
      #pragma omp critical (GAMBIT_exception)
      {
        log_exception(origin, specific_message+parameters);
      }
      throw(*this);
    }

    /// As per forced_throw but without logging.
    void exception::silent_forced_throw()
    {
      throw(*this);
    }

    /// Get a read-only map of pointers to all instances of this class.
    const std::map<const char*,exception*>& exception::all_exceptions()
    {
      return exception_map();
    }

    /// Set the parameter point string to append if a fatal exception is thrown
    void exception::set_parameters(str params)
    {
      parameters = params;
    }

  // Private members of GAMBIT exception base class.

    /// Get a map of pointers to all instances of this class.
    std::map<const char*,exception*>& exception::exception_map()
    {
      static std::map<const char*,exception*> local_map;
      return local_map;
    }

    /// Log the details of the exception
    void exception::log_exception(const std::string& origin, const std::string& specific_message)
    {
      std::ostringstream msg;
      msg << myKind << ": " << myMessage << std::endl
          << specific_message << std::endl
          << "Raised at: " << origin << ".";
      if (isFatal)
      {
        logger() << fatal;
        std::ostringstream myLongWhat;
        myLongWhat << myShortWhat << std::endl << msg.str();
        myWhat = myLongWhat.str();
      }
      else
      {
        logger() << nonfatal;
        myWhat = myShortWhat;
      }
      for (std::set<LogTag>::iterator it = myLogTags.begin(); it != myLogTags.end(); ++it) { logger() << *it; }
      logger() << msg.str() << EOM;
    }

    /// Throw the exception onward if running serially, abort if not.
    void exception::throw_iff_outside_parallel()
    {
      if (omp_get_level()==0) // If not in an OpenMP parallel block, throw onwards
      {
        throw(*this);
      }
      else
      {
        abort_here_and_now(); // If in an OpenMP parallel block, just abort immediately.
      }
    }

    /// Cause the code to print the exception and abort.
    void exception::abort_here_and_now()
    {
      #pragma omp critical (GAMBIT_exception)
      {
        cerr << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl
             << "GAMBIT has exited with fatal exception: " << what() << endl
             << "Please note: this error occurred inside an OpenMP parallel " << endl
             << "region and so caused a hard stop. If you are running in MPI " << endl
             << "mode, other processes were not informed of this error and " << endl
             << "may have to be killed manually (though your MPI implementation " << endl
             << "may automatically kill them).  For more 'gentle' handling of " << endl
             << "errors in OpenMP loops, please raise errors using the Piped_exceptions system." << endl;
        #ifdef WITH_MPI
          GMPI::Comm().Abort();
        #else
          abort();
        #endif
      }
    }


  /// GAMBIT error class constructors

    /// Constructor without log tags
    error::error(const char* message, const char* inikey) :
     exception("ERROR", "GAMBIT error", message, inikey, true, err) {}
    /// Constructor with 1 log tag
    error::error(const char* message, const char* inikey, LogTag t1)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1) {}
    /// Constructor with 2 log tags
    error::error(const char* message, const char* inikey, LogTag t1, LogTag t2)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1, t2) {}
    /// Constructor with 3 log tags
    error::error(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1, t2, t3) {}
    /// Constructor with 4 log tags
    error::error(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1, t2, t3, t4) {}
    /// Constructor with 5 log tags
    error::error(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1, t2, t3, t4, t5) {}
    /// Constructor with 6 log tags
    error::error(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5, LogTag t6)
     : exception("ERROR", "GAMBIT error", message, inikey, true, err, t1, t2, t3, t4, t5, t6) {}
    /// Constructor with log tags as a set
    error::error(const char* message, const char* inikey, std::set<LogTag> tags) :
     exception("ERROR", "GAMBIT error", message, inikey, true)
    {
      myLogTags = tags;
      myLogTags.insert(err);
    }

  /// GAMBIT warning class constructors

    /// Constructor without log tags
    warning::warning(const char* message, const char* inikey) :
     exception("WARNING", "GAMBIT warning", message, inikey, false, warn) {}
    /// Constructor with 1 log tag
    warning::warning(const char* message, const char* inikey, LogTag t1)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1) {}
    /// Constructor with 2 log tags
    warning::warning(const char* message, const char* inikey, LogTag t1, LogTag t2)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1, t2) {}
    /// Constructor with 3 log tags
    warning::warning(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1, t2, t3) {}
    /// Constructor with 4 log tags
    warning::warning(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1, t2, t3, t4) {}
    /// Constructor with 5 log tags
    warning::warning(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1, t2, t3, t4, t5) {}
    /// Constructor with 6 log tags
    warning::warning(const char* message, const char* inikey, LogTag t1, LogTag t2, LogTag t3, LogTag t4, LogTag t5, LogTag t6)
     : exception("WARNING", "GAMBIT warning", message, inikey, false, warn, t1, t2, t3, t4, t5, t6) {}
    /// Constructor with log tags as a set
    warning::warning(const char* message, const char* inikey, std::set<LogTag> tags) :
     exception("WARNING", "GAMBIT warning", message, inikey, false)
    {
      myLogTags = tags;
      myLogTags.insert(warn);
    }


  /// GAMBIT special exception class methods.

    /// Constructor
    special_exception::special_exception(const char* what) : myWhat(what), myMessage("") {}

    /// Retrieve the identity of the exception.
    const char* special_exception::what() const throw()
    {
      const char* temp;
      temp = myWhat;
      return temp;
    }

    /// Retrieve the message that this exception was raised with.
    std::string special_exception::message()
    {
      std::string temp;
      #pragma omp critical (GAMBIT_exception)
      {
        temp = myMessage;
      }
      return temp;
    }

    /// Raise the exception, i.e. throw it with a message.
    void special_exception::raise(const std::string& msg)
    {
      #pragma omp critical (GAMBIT_exception)
      {
        myMessage = msg;
      }
      throw(*this);
    }


  /// Gambit invalid point exception class methods.

    /// Constructor
    invalid_point_exception::invalid_point_exception() : special_exception("GAMBIT invalid point."), myThrower(NULL) {}

    /// Set the pointer to the functor that threw the invalid point exception.
    void invalid_point_exception::set_thrower(functor* thrown_from)
    {
      #pragma omp critical (myThrower)
      {
        myThrower = thrown_from;
      }
    }

    /// Retrieve pointer to the functor that threw the invalid point exception.
    functor* invalid_point_exception::thrower()
    {
      functor* temp;
      #pragma omp critical (myThrower)
      {
        temp = myThrower;
      }
      if (temp == NULL) utils_error().raise(LOCAL_INFO, "No throwing functor in invalid_point_exception.");
      return temp;
    }

    /// Raise the exception, i.e. throw it with a message.
    void invalid_point_exception::raise(const std::string& msg)
    {
      if (omp_get_level()==0) // If not in an OpenMP parallel block, throw onwards
      {
        #pragma omp critical (GAMBIT_exception)
        {
          myMessage = msg;
        }
        throw(*this);
      }
      else
      {
        std::ostringstream full_msg;
        full_msg << "Sorry, you cannot raise an invalid point exception inside an OpenMP block." << endl
                 << "Please use piped_invalid_point.request() in your block, then check it with " << endl
                 << "piped_invalid_point.check() to raise the exception outside the block." << endl
                << "Message: " << msg;
        #pragma omp critical (GAMBIT_exception)
        {
          myMessage = full_msg.str();
        }
        abort_here_and_now(); // If in an OpenMP parallel block, just abort immediately.
      }
    }

    /// Cause the code to print the exception and abort.
    void invalid_point_exception::abort_here_and_now()
    {
      #pragma omp critical (GAMBIT_invalid_pt_exception)
      {
        cerr << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl;
        cerr << "An invalid_point exception is fatal inside an OpenMP block. " << endl << what() << endl << message() << endl;
        #ifdef WITH_MPI
          GMPI::Comm().Abort();
        #else
          abort();
        #endif
      }
    }

    /// Request a piped invalid point exception.
    void Piped_invalid_point::request(std::string message)
    {
      #pragma omp critical (GAMBIT_piped_invalid_point)
      {
        this->message = message;
        this->flag = true;
      }
    }

    /// Check whether a piped invalid point exception was requested, and throw if necessary.
    void Piped_invalid_point::check()
    {
      if (omp_get_level()==0) // If not in an OpenMP parallel block, throw onwards
      {
        if (this->flag)
        {
          this->flag = false;  // Reset...
          invalid_point().raise(this->message);  // ...and throw.
        }
      }
      else
      {
        #pragma omp critical (GAMBIT_invalid_point)
        {
          cerr << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl;
          cerr << "GAMBIT has exited with fatal exception: Piped_invalid_point::check() called inside an OpenMP block." << endl
              << "Piped exceptions may be requested inside OpenMP blocks, but should only be checked outside the block." << endl;
          if (this->flag)
            cerr << "Invalid point message requested: " << endl << this->message;
          else cerr << "No invalid point requested." << endl;
          #ifdef WITH_MPI
            GMPI::Comm().Abort();
          #else
            abort();
          #endif
        }
      }
    }

  /// Gambit halt loop exception class methods.

    /// Constructor
    halt_loop_exception::halt_loop_exception() : special_exception("Immediate halt of GAMBIT loop requested.") {}


  /// Gambit invalid loop iteration exception class methods.

    /// Constructor
    invalid_loop_iteration_exception::invalid_loop_iteration_exception() : special_exception("GAMBIT invalid loop iteration.") {}


    /// @{ SilentShutdownException member functions
    SilentShutdownException::SilentShutdownException() {}
    SilentShutdownException::SilentShutdownException(const std::string& message) : myWhat(message) {}
    const char* SilentShutdownException::what() const throw() { return myWhat.c_str(); }
    /// @}

    /// @{ SoftShutdownException member functions
    SoftShutdownException::SoftShutdownException(const std::string& message) : myWhat(message) {}
    const char* SoftShutdownException::what() const throw() { return myWhat.c_str(); }
    /// @}

    /// @{ HardShutdownException member functions
    HardShutdownException::HardShutdownException(const std::string& message) : myWhat(message) {}
    const char* HardShutdownException::what() const throw() { return myWhat.c_str(); }
    /// @}

    /// @{ MPIShutdownException member functions
    MPIShutdownException::MPIShutdownException(const std::string& message) : myWhat(message) {}
    const char* MPIShutdownException::what() const throw() { return myWhat.c_str(); }
    /// @}

    /// Global instance of piped invalid point class.
    Piped_invalid_point piped_invalid_point;

    /// Request a piped exception.
    void Piped_exceptions::request(std::string origin, std::string message)
    {
      #pragma omp critical (GAMBIT_piped_exception)
      {
        if(exceptions.size() < maxExceptions)
          this->exceptions.push_back(description(origin,message));
        this->flag = true;
      }
    }

    /// Request a piped exception.
    void Piped_exceptions::request(description desc)
    {
      this->request(desc.first, desc.second);
    }

    /// Check whether any exceptions were requested, and raise them.
    void Piped_exceptions::check(exception &excep)
    {
      if (omp_get_level()==0) // If not in an OpenMP parallel block, throw onwards
      {
        if (this->flag)
        {
          // Raise all exceptions (only the first if they are fatal)
          for(size_t i= 0; i < std::min(exceptions.size(),maxExceptions); i++)
          {
            excep.raise(exceptions.at(i).first, exceptions.at(i).second);
          }
          // Reset
          this->flag = false;
          exceptions.clear();
        }
      }
      else
      {
        #pragma omp critical (GAMBIT_exception)
        {
          cerr << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl;
          cerr << "GAMBIT has exited with fatal exception: Piped_exceptions::check() called inside an OpenMP block." << endl
              << "Piped exceptions may be requested inside OpenMP blocks, but should only be checked outside the block." << endl;
          if (this->flag)
          {
            cerr << "Exceptions stored: " << endl << endl;
            for(size_t i= 0; i < std::min(exceptions.size(),maxExceptions); i++)
            {
              cerr << exceptions.at(i).second << endl
                   << "\nRaised at: " << exceptions.at(i).first << "." << endl << endl;
            }
          }
          else cerr << "No exceptions stored." << endl;
          #ifdef WITH_MPI
            GMPI::Comm().Abort();
          #else
            abort();
          #endif
        }
      }
    }

    /// Check whether any exceptions were requested without handling them.
    bool Piped_exceptions::inquire()
    {
      return this->flag;
    }

    /// Check whether any exceptions with a specific message were requested, without handling them.
    bool Piped_exceptions::inquire(std::string message)
    {
      if (not this->flag) return false;
      auto it = std::find_if(exceptions.cbegin(), exceptions.cend(),
       [&message](std::pair<std::string,std::string> const &e){ return e.second == message; });
      return it != exceptions.cend();
    }

    /// Global instance of Piped_exceptions class for errors.
    Piped_exceptions piped_errors(1000);

    /// Global instance of Piped_exceptions class for warnings.
    Piped_exceptions piped_warnings(1000);
}


