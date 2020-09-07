//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT signal handling functions
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 Oct - 2016 Jul
///
///  \author José Eliel Camargo-Molina
///         (Elielcamargomolina@gmail.com)
///   \date 2018 Aug
///  *********************************************

#include <iostream>
#include <signal.h>
#include <omp.h>
#include <time.h> // For nanosleep (posix only)
#include <cmath>
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Logs/logger.hpp"
#include "yaml-cpp/yaml.h"

//#define SIGNAL_DEBUG // comment out when not debugging.

namespace Gambit
{
   /// Translate signal codes to strings
   std::string signal_name(int sig)
   {
     std::string name;
     switch(sig){
         case SIGINT:  name="SIGINT";  break;
         case SIGTERM: name="SIGTERM"; break;
         case SIGUSR1: name="SIGUSR1"; break;
         case SIGUSR2: name="SIGUSR2"; break;
         default: name="<unlisted>";
     }
     return name;
   }

   #ifdef WITH_MPI
   /// Class for keeping track of shutdown message buffers and status for a certain shutdown code type
   ShutdownMsg::ShutdownMsg(const int code, const std::string& name)
    : mpisize(0)
    , myrank(0)
    , mycode(code)
    , name(name)
    , buffers()
    , buffer_status()
    , req()
    , comm(NULL)
   {}

   // Default constructor
   ShutdownMsg::ShutdownMsg()
    : mpisize(0)
    , myrank(0)
    , mycode(0)
    , name()
    , buffers()
    , buffer_status()
    , req()
    , comm(NULL)
   {}

   void ShutdownMsg::setComm(GMPI::Comm* const c)
   {
       comm = c;
       mpisize = comm->Get_size();
       myrank = comm->Get_rank();
       for(int i=0; i<mpisize; i++)
       {
           buffers.push_back(mycode);
           buffer_status.push_back(0);
           req.push_back(MPI_Request());
       }
   }

   // Send this code to all processes (non-blocking)
   void ShutdownMsg::ISendToAll()
   {
       for(int i=0; i<mpisize; i++)
       {
          if(i!=myrank)
          {
             if(buffer_status[i]!=0)
             {
                // Buffer already in use! Error!
                std::ostringstream errmsg;
                errmsg<<"Tried to broadcast code "<<name<<" to all processes, but the send buffer for process "<<i<<" was already in use! This is a bug in the message send logic of the code using this object, please file a bug report."<<std::endl;
                utils_error().raise(LOCAL_INFO, errmsg.str());
             }
             comm->Isend(&buffers[i], 1, i, comm->mytag, &req[i]);
             buffer_status[i] = 1;
          }
       }
   }

   // Ensure all processes have received this message (completes the send; must follow ISendToAll at some point)
   void ShutdownMsg::Wait()
   {
       for(int i=0; i<mpisize; i++)
       {
          if(i!=myrank and buffer_status[i]==1)
          {
              comm->Wait(&req[i]);
              buffer_status[i] = 0;
          }
       }
   }

   /// Translate shutdown codes to strings
   std::string SignalData::shutdown_name(int code)
   {
     std::string name;
     switch(code){
         case SOFT_SHUTDOWN:      name="SOFT_SHUTDOWN";      break;
         case EMERGENCY_SHUTDOWN: name="EMERGENCY_SHUTDOWN"; break;
         case NO_MORE_MESSAGES:   name="NO_MORE_MESSAGES"; break;
         default: name="<invalid shutdown code>"; break;
     }
     return name;
   }

   /// Shutdown code values. It is a stupid vagary of C++11 that these have external linkage.
   constexpr int SignalData::SOFT_SHUTDOWN;
   constexpr int SignalData::EMERGENCY_SHUTDOWN;
   constexpr int SignalData::NO_MORE_MESSAGES;

   #endif

   /// @{ SignalData member functions

   /// Constructor (initialise member variables)
   SignalData::SignalData()
     : jumppoint_set(false)
     , havejumped(1) // set to zero after jump point set
     , cleanup_function_set(false)
     , rank(-1)
     , shutdownBegun(0)
     , emergency(0)
     , POSIX_signal_noticed(false)
     , shutdown_due_to_MPI_message(false)
     , shutdown_attempts(0)
     , attempts_since_ff(0)
     , ff_loop_count(0)
     , ff_on(false)
     , ff_count(0)
     , inside_omp_block(false)
     , N_signals(0)
     #ifdef WITH_MPI
     , MPIsize(1)
     , _comm_rdy(false)
     , shutdown_broadcast_done(false)
     , looptimes(1000)
     , timeout(500)
     , msgs()
     #endif
   {
     #ifdef WITH_MPI
     msgs[SOFT_SHUTDOWN]      = ShutdownMsg(SOFT_SHUTDOWN,shutdown_name(SOFT_SHUTDOWN));
     msgs[EMERGENCY_SHUTDOWN] = ShutdownMsg(EMERGENCY_SHUTDOWN,shutdown_name(EMERGENCY_SHUTDOWN));
     msgs[NO_MORE_MESSAGES]   = ShutdownMsg(NO_MORE_MESSAGES,shutdown_name(NO_MORE_MESSAGES));
     #endif
   }

   /// Retrieve MPI rank as a string (for log messages etc.)
   std::string SignalData::myrank()
   {
     std::ostringstream tmp;
     #ifdef WITH_MPI
     if(rank==-1) { tmp << "UNKNOWN"; }
     else         { tmp << rank; }
     #else
     tmp << "(MPI DISABLED)";
     #endif
     return tmp.str();
   }

   /// Set jump point;
   void SignalData::setjump()
   {
      havejumped = setjmp(env);
      jumppoint_set = true;
   }

   /// Set cleanup function
   void SignalData::set_cleanup(void_func f)
   {
      cleanup = f;
      cleanup_function_set = true;
   }

   /// Call cleanup function
   void SignalData::call_cleanup()
   {
      if(cleanup_function_set) cleanup();
      // Do nothing if no function has been set;
   }

   /// Add signal to record
   void SignalData::add_signal(int sig)
   {
     //std::cerr << " Adding signal " << sig << std::endl; // debugging
     if(N_signals<MAX_SIGNALS) {
        received_signals[N_signals] = sig;
        N_signals+=1;
     }
     else
     {
        // no more space to record signals.
        N_signals+=1;
     }
   }

   /// Print to string a list of the signals received so far by this process
   std::string SignalData::display_received_signals()
   {
     std::ostringstream myout;
     if(N_signals > 0 )
     {
       myout << "Caught the following signals (in order):" << std::endl;
       for(int i=0; i<N_signals; i++)
       {
         if(i<MAX_SIGNALS)
         {
           myout <<"#"<<i+1<<": Signal "<<received_signals[i]<<" ("<<signal_name(received_signals[i])<<")"<<std::endl;
         }
       }
       if( (N_signals - MAX_SIGNALS) > 0)
       {
         myout << "Another " << (N_signals - MAX_SIGNALS) <<" signals were caught but their values were not recorded (buffer exceeded)"<<std::endl;
       }
     }
     return myout.str();
   }

   /// Register that shutdown has begun
   void SignalData::set_shutdown_begun(const sig_atomic_t emergnc)
   {
     shutdownBegun = 1;
     emergency = emergnc;
     // // if(ignore_signals_during_shutdown)
     // {
     //    /// Redirect all future signals (except of course kill etc.) to the null handlers
     //    signal(SIGTERM, sighandler_null);
     //    signal(SIGINT,  sighandler_null);
     //    signal(SIGUSR1, sighandler_null);
     //    signal(SIGUSR2, sighandler_null);
     // }
   }

   /// Check if shutdown is in progress
   bool SignalData::shutdown_begun() { return shutdownBegun; }
   //bool SignalData::emergency_shutdown_begun() { return shutdownBegun & emergency; }

   /// Attempt to synchronise all processes, but abort if it takes too long
   bool SignalData::all_processes_ready()
   {
     #ifdef WITH_MPI
       logger() << "Waiting up to "<<timeout/1000<<" seconds for all processes to sync..." << EOM;
       // sleep setup
       bool timedout = false;
       std::chrono::milliseconds bar_timeout(std::lround(timeout));
       if( signalComm->BarrierWithTimeout(bar_timeout, 9999) )
       {
         timedout = true; // Barrier timed out waiting for some process to enter
       }
       // else the barrier succeed in synchronising all processes
       logger() << "Synchronised? " << !timedout << EOM;
       return !timedout;
     #else
       return true; // Always ready if no MPI
     #endif
   }

   void SignalData::attempt_soft_shutdown()
   {
     const int max_attempts=-1; // Number of extra likelihood evaluations allowed for sync attempts before we declare failure. -1 means "unlimited"
     const int attempts_before_ff=10; // Number of times to attempt synchronisation before entering a "fast forward" period
     const int ff_loops=1000; // Number of "fast-forward" loops to perform in a fast-forward period

     /// Start counting...
     static std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());

     if(shutdown_attempts==0)
     {
        /// First time we see the shutdown signal, we will allow control to return to the scanner at least once,
        /// so that it can get its own affairs in order.
        logger() << "Beginning GAMBIT soft shutdown procedure. Control will be returned to the scanner plugin so "
                 << "that it can get its affairs in order in preparation for shutdown (it may cease iterating if "
                 << "it has that capability), and next iteration we will attempt to synchronise all processes and "
                 << "shut them down. If sync fails, we will loop up to "<<max_attempts<<" times (-1 means infinite), attempting to "
                 << "synchronise each time. If sync fails, an emergency shutdown will be attempted." << EOM;
        ++shutdown_attempts;
     }
     else if(ff_on)
     {
        logger() << "Fast-forward active (loop "<<ff_loop_count<<"); no synchronisation attempted." << EOM;
        // Fast-forward active; just increment counters and return
        ++ff_loop_count;
        if(ff_loop_count>=ff_loops)
        {
          logger() << "Fast-forward period finished (performed "<<ff_loop_count<<" fast loops)." << EOM;
          ff_on = false;
          ff_loop_count=0;
        }
     }
     else if(attempts_since_ff>=attempts_before_ff)
     {
        // Enter "fast-forward" period
        ff_on = true;
        ++ff_count;
        std::ostringstream msg;
        msg << "rank "<<myrank()<<": Tried to synchronise for shutdown (attempt "<<shutdown_attempts<<") but failed. Will now fast-forward through "<<ff_loops<<" iterations in an attempt to 'unlock' possible MPI deadlocks with the scanner.";
        std::cerr << msg.str() << std::endl;
        logger() << msg.str() << EOM;
        // Reset counters
        attempts_since_ff=0;
     }
     else
     {
        // Normal sync attempt (no fast forward)
        if(shutdown_attempts==1)
        {
           logger() << "Scanner did not shut down when given the chance; we will therefore assume responsibility for terminating the scan." << EOM;
        }
        logger() << "Attempting to synchronise for soft shutdown (attempt "<<shutdown_attempts<<")" << EOM;
        if (all_processes_ready())
        {
          logger() << "Calling cleanup routines" << EOM;
          call_cleanup();
          std::ostringstream msg;
          logger() << "Throwing soft shutdown exception" << EOM;
          throw SoftShutdownException(msg.str());
        }

        // Compute elapsed time since shutdown began
        std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
        std::chrono::duration<double> time_waited = current - start;

        if(max_attempts!=-1 and shutdown_attempts>=max_attempts)
        {
          logger() << "Failed to synchronise for soft shutdown! Attempting cleanup anyway, but cannot guarantee safety of the scan output." << EOM;
          call_cleanup();
          std::ostringstream msg;
          #ifdef WITH_MPI
          msg << "rank "<<myrank()<<": ";
          #endif
          msg << "Soft shutdown failed, emergency shutdown performed instead! (could not synchronise all processes after "<<shutdown_attempts
              <<" attempts, and after waiting "<<std::chrono::duration_cast<std::chrono::seconds>(time_waited).count()
              <<" seconds; fast-forward periods of "<<ff_loops<<" iterations were performed "<<ff_count
              <<" times). Data handled by external scanner codes may have been left in an inconsistent state." << std::endl;
          throw HardShutdownException(msg.str());
        }
        else
        {
          logger() << "Attempt to sync for soft shutdown failed (this was attempt "<<shutdown_attempts<<" of "<<max_attempts<<" (-1 means infinite)); "
                   <<std::chrono::duration_cast<std::chrono::seconds>(time_waited).count() <<" seconds have elapsed since "
                   <<"shutdown attempts began). Will allow evaluation to continue and attempt to sync again next iteration." << EOM;
        }
        ++shutdown_attempts;
        ++attempts_since_ff;
     }
   }

   /// Check for signals that early shutdown is required
   /// If an MPI message telling us to perform an emergency shutdown is received
   /// (which should only happen in the case of an error on some other process) then
   /// a shutdown exception is raised. Otherwise, we just return a bool indicating
   /// the shutdown status
   bool SignalData::check_if_shutdown_begun()
   {
     if(not shutdown_begun())
     {
        // If shutdown is not known to be in progress, check for MPI messages telling us to initiate shutdown
        #ifdef WITH_MPI
        /// Check for shutdown signals from other processes
        #ifdef SIGNAL_DEBUG
        logger() << LogTags::core << LogTags::info << "Doing Iprobe to check for shutdown messages from other processes (with MPI tag "<<signalComm->mytag<<")" << EOM;
        #endif
        if(signalComm->Iprobe(MPI_ANY_SOURCE, signalComm->mytag))
        {
          #ifdef SIGNAL_DEBUG
          logger() << LogTags::core << LogTags::info << "Shutdown message detected; doing Recv" << EOM;
          #endif
          int code;
          MPI_Status msg_status;
          signalComm->Recv(&code, 1, MPI_ANY_SOURCE, signalComm->mytag, &msg_status);

          // Check what code was received and use it to determined what kind of shutdown to do
          if(code==SOFT_SHUTDOWN)
          {
            set_shutdown_begun();
            logger() << LogTags::core << LogTags::info << "Received SOFT shutdown message from process with rank " << msg_status.MPI_SOURCE << EOM;
          }
          else if(code==EMERGENCY_SHUTDOWN)
          {
            set_shutdown_begun(1); // '1' argument means emergency set also.
            logger() << LogTags::core << LogTags::info << "Received EMERGENCY shutdown message from process with rank " << msg_status.MPI_SOURCE << EOM;
          }
          else
          {
            std::ostringstream ss;
            ss << "Received UNRECOGNISED shutdown message from process with rank " << msg_status.MPI_SOURCE<<". Performing emergency shutdown, but please note that this indicates a ***BUG*** somewhere in the signal handling code!!!";
            std::cout << ss.str() << std::endl;
            logger() << LogTags::core << LogTags::info << ss.str() << EOM;
            set_shutdown_begun(1); // '1' argument means emergency set also.
          }

          shutdown_due_to_MPI_message = true;
        }
        #ifdef SIGNAL_DEBUG
        else
        {
           logger() << LogTags::core << LogTags::info << "No shutdown message detected; continuing as normal" << EOM;
        }
        #endif
        #endif
     }

     // Check shutdown status again (might have changed due to MPI message receipt)
     if(shutdown_begun())
     {
       if(not POSIX_signal_noticed and not shutdown_due_to_MPI_message)
       {
         std::ostringstream ss;
         ss << "Process "<<rank<<": Shutdown signal detected!"<< std::endl;
         // std::cerr << ss.str();
         logger() << ss.str() << display_received_signals() << EOM;
         POSIX_signal_noticed = true;
       }

       std::ostringstream ss;
       static int loopi(0);
       logger() << "Shutdown is in progress; emergency="<< emergency <<" (loop="<<loopi<<")"<< EOM;
       ++loopi;
       logger() << ss.str() << EOM;

       #ifdef WITH_MPI
       if(not shutdown_due_to_MPI_message) // Don't broadcast another shutdown message if we are shutting down due to an MPI message we received. Assume that all processes will get the first message (otherwise for 1000 process job we will end up with 1000*1000 shutdown messages clogging up the network)
       {
         // Broadcast shutdown message to all processes
         int shutdown_code;
         if(emergency)
         {
           shutdown_code = EMERGENCY_SHUTDOWN;
         }
         else
         {
           shutdown_code = SOFT_SHUTDOWN;
         }
         broadcast_shutdown_signal(shutdown_code);
       }
       else if(emergency)
       {
         throw MPIShutdownException("Received emergency shutdown command via MPI! Terminating run.");
       }
       #endif

     }
     return shutdown_begun();
   }


   /// Add a new loop time to internal array used to decide barrier timeout
   void SignalData::update_looptime(double /*newtime*/)
   {
     // Leave this as 1 second now that likelihood calculation is disabled during shutdown
   }

   /// Absorb any extra shutdown messages that may be unreceived
   /// (since every process broadcasts to every other process that it should shut down,
   /// so with lots of processess there will be lots of unreceived messages floating
   /// around)
   #ifdef WITH_MPI
   void SignalData::discard_excess_shutdown_messages()
   {
     /// Check for shutdown signals from other processes
     #ifdef SIGNAL_DEBUG
     logger() << LogTags::core << LogTags::info << "Doing Iprobe to check for shutdown signals from other processes (with MPI tag "
              <<signalComm->mytag<<"). These will be discarded (since we are inside the 'discard_excess_shutdown_messages' routine)" << EOM;
     #endif
     int max_loops = 2*signalComm->Get_size(); // At most should be one message from every process (minus one), so we will check twice as many times as this before deciding that something has gone horribly wrong.

     int code;
     signalComm->Recv_all(&code, 1, MPI_ANY_SOURCE, signalComm->mytag, max_loops);
   }

   /// This function makes absolutely sure that there are no more shutdown messages
   /// to recv from any processes. It does this by making sure that every process
   /// has sent a message to confirm that it isn't going to send any more shutdown
   /// messages
   void SignalData::ensure_no_more_shutdown_messages()
   {
     int mpiSize = signalComm->Get_size();
     int myRank = signalComm->Get_rank();

     // Recv all shutdown messages from other processes
     logger() << LogTags::core << LogTags::debug << "Receiving all shutdown messages" << EOM;
     for(int rank=0; rank<mpiSize; rank++)
     {
        if(rank!=myRank)
        {
           //std::cerr<<"Rank "<<myRank<<" attempting to cleanup shutdown messages from rank "<<rank<<std::endl;
           int loop = 0;
           bool more_messages = true;
           while(more_messages)
           {
              int code;
              //std::cerr<<"Rank "<<myRank<<": Messages waiting from rank "<<rank<<"? "<<signalComm->Iprobe(rank, signalComm->mytag)<<std::endl;
              signalComm->Recv(&code, 1, rank, signalComm->mytag);
              //std::cerr<<"Rank "<<myRank<<": received code "<<shutdown_name(code)<<" from rank "<<rank<<std::endl;
              if(code==NO_MORE_MESSAGES) more_messages = false;
              loop++;
              if(loop>2*mpiSize)
              {
                 // I think there should only be one shutdown message from each process, so this
                 // condition is extreme and definitely indicates a problem.
                 std::ostringstream errmsg;
                 errmsg<<"ensure_no_more_shutdown_messages function has been looping on rank "<<myRank<<" for "<<loop<<" iterations (receiving messages from rank "<<rank<<" process), but there are only "<<mpiSize<<" processes in this job. There should not be anywhere near this many shutdown messages to receive, so something has gone horribly wrong. Please report this as a bug.";
                 utils_error().raise(LOCAL_INFO, errmsg.str());
              }
           }
        }
     }

     // Ensure all shutdown messages from this process have been fully sent
     // (not necessary for the corresponding Recv's to complete, so no deadlock problem,
     // but needed to confirm that the messages were sent and allow MPI to clean them up
     // properly).
     logger()<<LogTags::core << LogTags::info<<"Cleaning up shutdown message send buffers"<<EOM;
     for(auto it=msgs.begin(); it!=msgs.end(); ++it)
     {
        it->second.Wait();
     }
   }
   #endif

   /// @{ TODO: Thread checking routines are no longer needed due to simplified shutdown method. Can be deleted when functors are updated to no longer call these routines.

   /// Switch to threadsafe signal handling mode
   void SignalData::entering_multithreaded_region()
   {
      inside_omp_block = 1;
      // Debugging
      //std::cerr << "rank " << rank <<": ENTERING_MULTITHREADED_REGION" << std::endl;
      //std::cerr << "rank " << rank <<": signaldata().inside_omp_block=1 " << std::endl;
   }

   /// Exit threadsafe signal handling mode
   void SignalData::leaving_multithreaded_region()
   {
      inside_omp_block = 0;
      // Debugging
      //std::cerr << "rank " << rank <<": LEAVING_MULTITHREADED_REGION" << std::endl;
      //std::cerr << "rank " << rank <<": signaldata().inside_omp_block=0 " << std::endl;
   }

   /// Report 'true' if inside a multithreaded region (according to our own flag)
   bool SignalData::inside_multithreaded_region()
   {
      return inside_omp_block;
   }

   /// @}

   #ifdef WITH_MPI
   /// Report if MPI communicator object is prepared
   bool SignalData::comm_ready() { return (GMPI::Is_initialized() and _comm_rdy); }

   /// Set the MPI communicator object for the session
   /// Can be run multiple times, but I would not advise doing that.
   void SignalData::set_MPI_comm(GMPI::Comm* comm)
   {
       signalComm = comm;
       _comm_rdy = true;
       rank = comm->Get_rank();
       MPIsize = comm->Get_size();
       // Set communicator for shutdown message objects
       for(auto it=msgs.begin(); it!=msgs.end(); ++it)
       {
          it->second.setComm(comm);
       }
   }

   /// Broadcast signal to shutdown all processes
   void SignalData::broadcast_shutdown_signal(int shutdown_code)
   {
     if(MPIsize>1)
     {
       if(shutdown_code==NO_MORE_MESSAGES or not shutdown_broadcast_done)
       {
         if(comm_ready())
         {
           // Broadcast signal to all processes (might not work if something errornous is occuring)
           #ifdef SIGNAL_DEBUG
           logger() << LogTags::core << LogTags::info << "Broadcasting shutcode code " <<shutdown_name(shutdown_code)<< " with MPI tag "<<signalComm->mytag<< EOM;
           #endif
           msgs[shutdown_code].ISendToAll();
           logger() << LogTags::core << LogTags::info << shutdown_name(shutdown_code) <<" code broadcast to all processes" << EOM;
          }
         else
         {
           /// Should not be broadcasting
           std::ostringstream errmsg;
           errmsg << "Tried to broadcast_shutdown_signal ("<<shutdown_name(shutdown_code)<<"), but MPI communicator is not ready! (either MPI is uninitialised or a communicator has not been set). This is a bug, please report it.";
           utils_error().raise(LOCAL_INFO, errmsg.str());
         }
         shutdown_broadcast_done = true;
       } // Don't need to broadcast twice (NOTE: might need to trigger change from soft to emergency shutdown?)
       #ifdef SIGNAL_DEBUG
       else
       {
         logger() << LogTags::core << LogTags::info << "Received instruction to broadcast code " <<shutdown_name(shutdown_code)
                  <<", however shutdown_broadcast_done=true is already set, so skipping the broadcast!"<< EOM;
       }
       #endif
     }
   }
   #endif

   /// @}

   /// Retrieve global instance of signal handler options struct
   SignalData& signaldata()
   {
     static SignalData data;
     #ifdef WITH_MPI
     // If we are using MPI, it is required that the signaldata object be initialised with a communicator object
     // This 'ifdef' block ensures that this happens, or else throws an error.
     static int access_count = 0;
     if(access_count==0){ access_count += 1; }
     else if(access_count==1)
     {
       // Check that communicator object has been initialised
       if(not data.comm_ready())
       {
          std::ostringstream errmsg;
          errmsg << "Error retrieving global SignalData object! An MPI communicator has not been provided to this object! Please provide one via the 'set_MPI_comm' the first time that 'signaldata()' is called.";
          utils_error().raise(LOCAL_INFO, errmsg.str());
       }
     }
     #endif
     return data;
   }

   /// ========================================================================
   /// ========================================================================

   /// @{ Signal handler functions

   /// We used to have more of these, but now we only use the "soft shutdown" signal handler.

   /// Sets a "shutdown_begun" flag, which is checked each likelihood loop,
   /// after which MPI synchronisation followed by clean shutdown is attempted.
   void sighandler_soft(int sig)
   {
     // We will avoid touching streams in this "clean" shutdown mode since technically it is undefined behaviour, so no messages here.
     signaldata().set_shutdown_begun();
     signaldata().add_signal(sig); // I think this should be ok... but can delete it if there are any problems
   }

   /// @}

   /// TODO: Mostly obsolete
   /// Choose signal handler for a given signal via yaml file option
   void set_signal_handler(const YAML::Node& keyvalnode, const int sig, const std::string& def_mode)
   {
       std::string shutdown_mode;
       if(keyvalnode["signal_handling"]) {
          YAML::Node signal_options = keyvalnode["signal_handling"];
          if(signal_options[signal_name(sig)]) {
             shutdown_mode = signal_options[signal_name(sig)].as<std::string>();
          }else{
             shutdown_mode = def_mode;
          }
       }else{
          shutdown_mode = def_mode;
       }
       logger()<< "Setting action on "<<signal_name(sig)<<" to '"<<shutdown_mode<<"'"<<EOM;
       // if      (shutdown_mode=="hard_shutdown"){      signal(sig, sighandler_hard);      }
       // else if (shutdown_mode=="emergency_shutdown"){ signal(sig, sighandler_emergency); }
       // else if (shutdown_mode=="emergency_shutdown_longjmp"){ signal(sig, sighandler_emergency_longjmp); }
       //else
       if (shutdown_mode=="soft_shutdown"){      signal(sig, sighandler_soft);      }
       //else if (shutdown_mode=="null"){               signal(sig, sighandler_null);      }
       else {
           std::ostringstream msg;
           msg << "Invalid shutdown mode requested for signal "<<signal_name(sig)<<" ("<<sig<<")"<<" (via YAML file option '"<<signal_name(sig)<<"' in KeyValue section under 'signal_handling'). Value received was '"<<shutdown_mode<<"'. Valid shutdown modes are:" <<std::endl;
           msg << "   'hard_shutdown'              -- Exit immediately." <<std::endl;
           msg << "   'emergency_shutdown'         -- Attempt to save printer/resume data and then immediately exit." <<std::endl;
           msg << "   'emergency_shutdown_longjmp' -- Longjmp to outside of likelihood loop, then attempt to save printer/resume data and exit"<<std::endl;
           msg << "   'soft_shutdown'              -- Safest: attempt to synchronise processes at safe location, then save printer/resume data and exit." <<std::endl;
           msg << "   'null'                       -- Ignore signal. Use at own risk!" <<std::endl;
           msg << "The default shutdown mode on signal "<<signal_name(sig)<<" is '"<<def_mode<<"'." <<std::endl;
           std::cerr << msg.str();
           std::cerr << std::endl;
           exit(EXIT_FAILURE);
       }
   }

}


