//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT file locking functions
///  Use these to block access to sensitive parts
///  of the code by other processes when we are
///  using them. For example, some backends
///  do stupid things like initialise themselves
///  by writing and reading files; use these
///  routines to force only one process at a time
///  to perform these routines.
///
///  Can also be used to literally lock access to
///  a particular file, e.g. HDF5Printer2 output
///  uses these to serialise write access to the
///  hdf5 output file.
///
///  Usage:
///
///   {
///     Utils::FileLock mylock("some_unique_name");
///     mylock.get_lock();
///     /* Do sensitive stuff. No other process will
///        be allowed into this code region while we
///        are here. */
///     mylock.release_lock();
///   }
///   /* If not already done, lock is automatically
///      released when 'mylock' is destructed */
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2016 Feb, 2019 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016, 2019 Sep
///
///  *********************************************

#include <cstdio>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h> // I think this should work on osx as well...
#include <string>

#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/cmake/cmake_variables.hpp"

//#define FILE_LOCK_DEBUG

#ifdef FILE_LOCK_DEBUG
  #include <sys/time.h>
  #include "gambit/Utils/mpiwrapper.hpp"
#endif


namespace Gambit
{
   namespace Utils
   {

      /// @{ Members of FileLock class

      const std::string hardmsg("Now calling abort (will produce a core file for analysis if this is enabled on your system; if so please include this with the bug report)");

      /// Constructor
      FileLock::FileLock(const std::string& fname, const bool harderrs)
       : my_lock_fname(ensure_path_exists(fname))
       , fd(open(my_lock_fname.c_str(), O_RDWR | O_CREAT, 0666)) // last argument is permissions, in case file has to be created.
       , have_lock(false)
       , hard_errors(harderrs)
      {
        /// Should check for errors opening the file. List of error codes is kind of long though, let people look it up themselves for now...
        if(fd<0)
        {
          /// Error opening file!
          std::ostringstream msg;
          msg << "Error getting file descriptor for lock file '"<<my_lock_fname<<"'! Error was: "<< std::strerror(errno);
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }
      }

      /// Destructor
      /// Closing the file descriptor will automatically release any lock we might have
      FileLock::~FileLock()
      {
        int return_code = close(fd);

        if(return_code!=0)
        {
          /// Error closing file!
          std::ostringstream msg;
          msg << "Error closing file descriptor for lock file '"<<my_lock_fname<<"'! Error was: "<< std::strerror(errno);
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }
      }

      /// Obtain lock (or wait if lock cannot be obtained, and then obtain lock)
      void FileLock::get_lock()
      {
        if(have_lock)
        {
          /// Already have the lock!
          std::ostringstream msg;
          msg << "Tried to obtain lock for file '"<<my_lock_fname<<"', but we already have it! This indicates a logic error in whatever code tried to obtain the lock, please file a bug report.";
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }

        #ifdef FILE_LOCK_DEBUG
          int rank;
          struct timeval tv;
          struct timezone tz;
          MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        #endif
        // Attempt to gain the lock. If the lock cannot be obtained, will block until it can.
        // This operation is atomic and so should be safe.
        int return_code = lockf(fd, F_LOCK, 0);
        #ifdef FILE_LOCK_DEBUG
          gettimeofday(&tv, &tz);
          cout << "[" << tv.tv_sec << "." << tv.tv_usec << "] Got lock " << my_lock_fname << " in rank " << rank << endl;
        #endif

        /// Ok it seems there are some errors that we should handle, and then just try again to obtain the lock.
        if(return_code!=0 && errno==EINTR)
        {
          // This happens if the system call is interrupted by a signal. This
          // happens when we tell GAMBIT to stop via a signal! But it is no
          // big deal, we just need to attempt the lock again. We should log
          // that this happened, in case we need to debug some bizarre problem.
          logger() << LogTags::utils << "Attempt to get lock "<< my_lock_fname <<" failed due to interruption by system call! But this was probably just the GAMBIT shutdown signal, so we will just keep trying to get the lock until the error changes or goes away..." << EOM;
          while(return_code!=0 && errno==EINTR)
          {
            return_code = lockf(fd, F_LOCK, 0);
          }
        }

        if(return_code!=0)
        {
          // Uh oh, error occurred. Return error message
          std::ostringstream msg;
          msg << "Error obtaining lock on \""<<my_lock_fname<<"\"! Error was: "<< std::strerror(errno) << " (errno="<<errno<<")";
          //msg << " (DEBUG! EINTR="<<EINTR<<")";
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }
        // Else the lock is ours!
        have_lock = true;
      }

      /// Release a lock (error if no lock held)
      void FileLock::release_lock()
      {
        if(not have_lock)
        {
          /// Don't have the lock!
          std::ostringstream msg;
          msg << "Tried to release lock for file '"<<my_lock_fname<<"', but it is not ours to release (i.e. get_lock() was not called, or the lock has already been released)! This indicates a logic error in whatever code tried to obtain the lock, please file a bug report.";
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }

        #ifdef FILE_LOCK_DEBUG
          int rank;
          MPI_Comm_rank(MPI_COMM_WORLD,&rank);
          struct timeval tv;
          struct timezone tz;
          gettimeofday(&tv, &tz);
          cout << "[" << tv.tv_sec << "." << tv.tv_usec << "] Releasing lock " << my_lock_fname << " in rank " << rank << endl;
        #endif
        /// Release the lock
        int return_code = lockf(fd, F_ULOCK, 0);

        if(return_code!=0)
        {
          // Uh oh, error occurred. Return error message
          std::ostringstream msg;
          msg << "Error releasing lock on \""<<my_lock_fname<<"\"! Error was: "<< std::strerror(errno);
          if(hard_errors) { std::cerr<<"Error! ("<<LOCAL_INFO<<"): "<<msg.str()<<hardmsg<<std::endl; std::cerr.flush(); abort(); }
          else { utils_error().raise(LOCAL_INFO,msg.str()); }
        }
        have_lock = false;
      }

      /// Getter for lockfile name
      const std::string& FileLock::get_filename() const { return my_lock_fname; }

      /// @}


      /// @{ Members of ProcessLock class

      /// Initialise prefix path name to lock files, and extension
      const std::string ProcessLock::lock_prefix(GAMBIT_DIR "/scratch/run_time/process_locks/");
      const std::string ProcessLock::lock_suffix(".lock");

      /// Constructor
      ProcessLock::ProcessLock(const std::string& fname, const bool harderrs)
       : FileLock(lock_prefix + fname + lock_suffix, harderrs)
      {}

      /// @}

   }
}
