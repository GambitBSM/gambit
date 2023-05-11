//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functor member function definitions for 
///  functions which are not needed in standlone
///  compile units, because they use the core
///  signal handling system.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2016 Mar
///
///  *********************************************

#include "gambit/Elements/functors.hpp"
#include "gambit/Utils/signal_handling.hpp" // Don't want this in standlone mode
#include "gambit/Logs/logger.hpp"

namespace Gambit
{

  /// @{ Definitions of friend functions from above

    /// @{ Some helper functions for interacting with signals in the calculate() routine
    ///    These don't exist in standalone compilations, are replaced with null functions
    namespace FunctorHelp {
       
       // Both OBSOLETE   
       // /// Thin wrapper to isolate signal handling from other components of the functors 
       // bool emergency_shutdown_begun()
       // {
       //   return signaldata().emergency_shutdown_begun();
       // }
       //      
       // /// Check if shutdown in progress and take appropriate action.
       // /// Now only cancels evaluations if it is an emergency shutdown; soft shutdown requires
       // /// valid likelihood calculation to continue until synchronisation can be achieved.
       // void check_for_shutdown_signal(module_functor_common& functor)
       // {
       //   /* Check if shutdown signal received, and either throw Shutdown exception or break out of loop */
       //   if(functor.emergency_shutdown_begun())
       //   {
       //     #pragma omp critical (module_functor_calculate)
       //     {
       //       std::ostringstream ss;
       //       ss << "Shutdown signal detected while computing functor "<<functor.myName<<"! (omp_get_level()==" << omp_get_level() << ", thread="<<omp_get_thread_num()<<")";
       //       std::cerr << ss.str() << std::endl;
       //       logger() << LogTags::core << LogTags::debug << ss.str() << EOM;
       //     }
       //     if(omp_get_level()==0)                               /* If shutdown signal received and we are not in an */
       //     {                                                    /* OpenMP parallel block, perform the shutdown.     */
       //       signaldata().check_for_emergency_shutdown_signal();/* (but only if it is an emergency) */
       //       // Throw error if we haven't jumped!
       //       std::cerr << "rank " << signaldata().myrank() <<": No emergency shutdown occurred, but according to previous logic the signal to do so must have already been received! Please file a bug report." << std::endl;
       //       exit(EXIT_FAILURE);
       //     } 
       //     else if(functor.iCanManageLoops)
       //     {
       //       functor.breakLoop();
       //       logger() << LogTags::core << LogTags::debug << "breakLoop triggered (iCanManageLoops==1) in functor " << functor.myName << EOM;
       //     }
       //     else /* Must be a managed functor (since type is not void, cannot be a loop manager) */
       //     {
       //       functor.breakLoopFromManagedFunctor();
       //       functor.breakLoop(); /* Set this as well anyway in case I didn't understand the logic correctly. */
       //       logger() << LogTags::core << LogTags::debug << "breakLoop triggered while computing functor "<<functor.myName<<" (thread="<<omp_get_thread_num()<<")" << EOM;
       //     }
       //   }
       // }

       void entering_multithreaded_region(module_functor_common& functor)
       {
         if(functor.iCanManageLoops and not signaldata().inside_multithreaded_region())
         {
            /* Debugging */
            if(omp_get_level()!=0)
            {
              std::cerr << "rank " << signaldata().myrank() <<": Tried to set signaldata().inside_omp_block=1 (in "<<functor.myName<<"), but we are already in a parellel region! Please file a bug report." << std::endl;
              exit(EXIT_FAILURE);
            } \
            /* end debugging */
            signaldata().entering_multithreaded_region(); /* Switch signal handler to threadsafe mode */
            functor.signal_mode_locked = false;                  /* We are allowed to switch off sighandler threadsafe mode */
         }
       }

       void leaving_multithreaded_region(module_functor_common& functor)
       {
         if(functor.iCanManageLoops and not functor.signal_mode_locked)
         {
            /* Debugging */
            if(omp_get_level()!=0)
            {
              std::cerr << "rank " << signaldata().myrank() <<": Tried to set signaldata().inside_omp_block=0 (in "<<functor.myName<<"), but we are still inside a parellel region! Please file a bug report." << std::endl;
              exit(EXIT_FAILURE);
            }
            /* end debugging */
            signaldata().leaving_multithreaded_region(); /* Switch signal handler back to normal mode */
         }
       }
     
     }
    /// @}

  /// @}

}
