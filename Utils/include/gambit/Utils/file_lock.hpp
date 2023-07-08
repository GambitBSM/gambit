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
///  \date 2016 Feb
///
///  *********************************************

#ifndef __file_lock_hpp__
#define __file_lock_hpp__

#include <string>

namespace Gambit
{
   namespace Utils
   {

      /// Class to manage a file lock
      /// Lock will be automatically released if this object is destructed
      class FileLock
      {
        private:

          /// Name for the managed lock file
          const std::string my_lock_fname;

          /// C file descriptor for the lock file
          const int fd;

          /// Bool to indicate if we already have the lock
          bool have_lock;

          /// Bool to indicate that hard errors should be thrown rather than gambit errors (e.g. for use in loggers)
          bool hard_errors;

          /// Bool to indicate if the file has the ability to be exhaustible
          bool exhaustible;

          /// Bool to indicate whether the lock has been exhausted or not
          bool exhausted_lock;

        public:
          /// Constructor
          FileLock(const std::string& fname, const bool is_exhaustible=false, const bool harderrs=false);

          /// Destructor
          /// Closing the file descriptor will automatically release any lock we might have
          ~FileLock();

          /// Obtain lock (or wait if lock cannot be obtained, and then obtain lock)
          void get_lock();

          /// Release a lock (error if no lock held)
          void release_lock();

          /// Getter for lockfile name
          const std::string& get_filename() const;

          /// Check if lock is exhausted
          bool exhausted();
      };


      /// Class to manage a process lock, using a file
      class ProcessLock : public FileLock
      {
        private:
          /// Static variable for the lock-file prefix path, i.e. where to store the lock file
          static const std::string lock_prefix;

          /// Static variable for the lock-file extension
          static const std::string lock_suffix;

        public:
          /// Constructor
          ProcessLock(const std::string& fname, const bool is_exhaustible=true, const bool harderrs=false);

          /// Clean up existing process locks
          static void clean_locks();
      };

   }
}

#endif
