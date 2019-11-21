//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions for Gambit MPI C++ bindings.
///
///  NOTE! I just learned something unfortunate,
///  which is that all Isend's are supposed to be
///  matched by MPI_Wait calls at some point, to
///  ensure the operation is complete.
///  We are not doing this. Things seem to work
///  anyway, but it may explain some of the hangs
///  on MPI_Finalize.
///  I will fix the worst offenders of this asap,
///  but the rest may take longer.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2015 - 2019
///
///  *********************************************

#ifdef WITH_MPI // Contents of this file ignored if MPI not enabled

#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h> // For nanosleep (posix only)
#include <sys/types.h>
#include <chrono>

#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"

//#define MPI_DEBUG_OUTPUT // Turn on debugging messages


namespace Gambit
{

   namespace GMPI
   {

      /// @{ Main "Communicator" class

      long int Comm::pid = getpid();

      /// @{ Constructors
      /// Default (attaches to MPI_COMM_WORLD):
      Comm::Comm() : boundcomm(MPI_COMM_WORLD), myname("COMM_WORLD")
      {
         if(not Is_initialized())
         {
            utils_error().raise(LOCAL_INFO, "Error creating Comm object (wrapper for MPI communicator)! MPI has not been initialised!");
         }
      }

      /// Copy existing communicator
      Comm::Comm(const MPI_Comm& comm, const std::string& name) : boundcomm(comm), myname(name)
      {
         if(not Is_initialized())
         {
            utils_error().raise(LOCAL_INFO, "Error creating Comm object (wrapper for MPI communicator)! MPI has not been initialised!");
         }
      }

      /// Create a new communicator group from WORLD for the specified processes
      Comm::Comm(std::vector<int> processes, const std::string& name)
         : boundcomm(), myname(name)
      {
         // Create group
         MPI_Group group_world, new_group;
         MPI_Comm_group(MPI_COMM_WORLD, &group_world);
         MPI_Group_incl(group_world, processes.size(), &processes[0], &new_group);

         // Create new communicator
         int errflag = MPI_Comm_create(MPI_COMM_WORLD, new_group, &boundcomm);

         //std::cerr<<"boundcomm="<<boundcomm<<", MPI_COMM_NULL="<<MPI_COMM_NULL<<std::endl;

         // Check for error
         if(errflag!=0)
         {
           std::ostringstream errmsg;
           errmsg << "Error performing MPI_Comm_create while attempting to create a new communicator group! Received error flag: "<<errflag;
           utils_error().raise(LOCAL_INFO, errmsg.str());
         }
      }

      /// Duplicate input communicator into boundcomm
      /// (creates new context)
      /// NOTE! MPI_Comm_dup is a COLLECTIVE call, so all processes
      /// must call it! Beware deadlocks. May sometimes be better to duplicate
      /// first and then wrap in a communicator.
      void Comm::dup(const MPI_Comm& comm, const std::string& name)
      {
         int errflag = MPI_Comm_dup(comm, &boundcomm);
         if(errflag!=0) {
           std::ostringstream errmsg;
           errmsg << "Error performing MPI_Comm_dup! Received error flag: "<<errflag;
           utils_error().raise(LOCAL_INFO, errmsg.str());
         }
         // Change bound name
         myname = name;
      }

      /// Destructor
      ///́ Warn if any undelivered messages exist
      Comm::~Comm() { check_for_undelivered_messages(); }
      /// @}

      /// Check for undelivered messages (unless finalize has already been called)
      void Comm::check_for_undelivered_messages()
      {
        if(not Is_finalized() and boundcomm!=MPI_COMM_NULL)
        {
          std::ostringstream errmsg;
          // Warn if any unreceived messages exist
          MPI_Status status;
          bool message_waiting = Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, &status);
          if(message_waiting)
          {
            int source = status.MPI_SOURCE;
            int tag = status.MPI_TAG;
            LOGGER << "rank " << Get_rank() << ": WARNING! Unreceived MPI message detected (source="<<source<<", tag="<<tag<<", communicator group="<<Get_name()<<"). This may cause problems when MPI_Finalize is run." << EOM;
          }
        }
      }

      /// Get total number of MPI tasks in this communicator group
      int Comm::Get_size() const
      {
        int size;
        MPI_Comm_size(boundcomm,&size);
        return size;
      }

      /// Get "rank" (ID number) of current task in this communicator group
      int Comm::Get_rank() const
      {
        int rank;
        MPI_Comm_rank(boundcomm,&rank);
        return rank;
      }

      /// Get name of communicator group (for error messages)
      std::string Comm::Get_name() const
      {
        return myname;
      }

      /// Null buffer for use in master_wait_for_tag
      int null_send_buffer = 0;
      MPI_Request req_null = MPI_REQUEST_NULL;

      /// Tells master to wait until all other processes pass this function, with the specified MPI tag
      /// Could be modified to take a function pointer to loop over,
      void Comm::masterWaitForAll(int tag)
      {
         std::size_t mpiSize = Get_size();
         std::size_t myRank  = Get_rank();
         if(mpiSize>1)
         {
            if(myRank==0)
            {
               for(std::size_t sender=1; sender<mpiSize; sender++)
               {
                  // Do a blocking wait for each worker, until all messages received
                  int recv_buffer = 0; // To receive the null message
                  //std::cerr<<"rank "<<myRank<<": Waiting for tag "<<tag<<" from process "<<sender<<std::endl;
                  Recv(&recv_buffer, 1, sender, tag);
                  //std::cerr<<"rank "<<myRank<<": Received tag "<<tag<<" from process "<<sender<<std::endl;
               }
            }
            else
            {
               // Other processes simply signal that they have passed this point.
               //std::cerr<<"rank "<<myRank<<": Sending tag "<<tag<<" to process "<<0<<std::endl;
               Isend(&null_send_buffer, 1, 0 /*master*/, tag, &req_null);
            }
         }
         //std::cerr<<"rank "<<myRank<<": Passed masterWaitForAll with tag "<<tag<<std::endl;
      }

      /// Tells all processes to wait until master passes this point before proceeding, with the specified MPI tag
      void Comm::allWaitForMaster(int tag)
      {
         std::size_t mpiSize = Get_size();
         std::size_t myRank  = Get_rank();
         if(mpiSize>1)
         {
            if(myRank==0)
            {
               // Send to everyone that we have passed the checkpoint
               for(std::size_t dest=1; dest<mpiSize; dest++)
               {
                  //std::cerr<<"rank "<<myRank<<": Sending tag "<<tag<<" to process "<<dest<<std::endl;
                  Isend(&null_send_buffer, 1, dest, tag, &req_null);
               }
            }
            else
            {
               // Keep this simple for now, and just block until message received.
               // Like above, could modify so that work could be done while waiting.
               int recv_buffer = 0; // To receive the null message
               //std::cerr<<"rank "<<myRank<<": Waiting for tag "<<tag<<" from process "<<0<<std::endl;
               Recv(&recv_buffer, 1, 0 /*source*/, tag);
               //std::cerr<<"rank "<<myRank<<": Received tag "<<tag<<" from process "<<0<<std::endl;
            }
         }
         //std::cerr<<"rank "<<myRank<<": Passed allWaitForMaster with tag "<<tag<<std::endl;
      }

      /// Tells all processes to wait until master passes this point before proceeding, with the specified MPI tag
      /// Calls "func" periodically while waiting (can be used to e.g. check for error messages from other processes)
      void Comm::allWaitForMasterWithFunc(int tag, void (*func)())
      {
         std::size_t mpiSize = Get_size();
         std::size_t myRank  = Get_rank();
         if(mpiSize>1)
         {
            if(myRank==0)
            {
               // Send to everyone that we have passed the checkpoint
               for(std::size_t dest=1; dest<mpiSize; dest++)
               {
                  //std::cerr<<"rank "<<myRank<<": Sending tag "<<tag<<" to process "<<dest<<std::endl;
                  Isend(&null_send_buffer, 1, dest, tag, &req_null);
               }
            }
            else
            {
               bool message_received = false;
               struct timespec sleeptime;
               sleeptime.tv_sec = 0;
               sleeptime.tv_nsec = 100*1e6; // 100 millisecond wait time between loops should be reasonable
               MPI_Status status;

               // Now, loop and wait for all other processes to send their own entering signals
               while(not message_received)
               {
                  if( Iprobe(0 /*source*/, tag, &status) )
                  {
                    int recv_buffer = 0; // To receive the null message
                    Recv(&recv_buffer, 1, 0 /*source*/, tag);
                    message_received = true;
                  }

                  if(not message_received)
                  {
                    // sleep (is a busy sleep, but at least will avoid slamming MPI with constant Iprobes)
                    (*func)(); // Call the user-supplied function
                    nanosleep(&sleeptime,NULL);
                  }
               }
            }
         }
         //std::cerr<<"rank "<<myRank<<": Passed allWaitForMaster with tag "<<tag<<std::endl;
      }

      int BARRIER_ENTERED = 1; // Storage for barrier entry send message. Don't change this! (can't make it const due to signature of MPI functions)
      int BARRIER_LEFT = 0;  // Storage for barrier exit send message.  "          "           "

      bool Comm::BarrierWithTimeout(const std::chrono::duration<double> timeout, const int tag)
      {
         std::size_t mpiSize = Get_size();
         std::size_t myRank  = Get_rank();
         bool timedout = false;
         double total_timeout = std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count();

         std::vector<bool> entered(mpiSize); // should init to "false"
         entered[myRank] = true; // we know that we have entered the barrier
         LOGGER<<"rank "<<myRank<<": Entered BarrierWithTimeout (with tag "<<tag<<")"<<EOM;
         if(mpiSize>1)
         {
            int recv_buffer = 0; // To receive the null messages
            MPI_Status status;

            // First, tell all other processes that we have entered the barrier.
            IsendToAll(&BARRIER_ENTERED, 1, tag, &req_null);

            // Setup timeout interval and sleep time
            unsigned int Nchecks = 100; // Check for messages 100 times evenly spaced over the timeout interval
            std::chrono::time_point<std::chrono::system_clock> truestart = std::chrono::system_clock::now();
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

            struct timespec sleeptime;
            sleeptime.tv_sec = 0;
            sleeptime.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timeout).count() / Nchecks;

            // Now, loop and wait for all other processes to send their own entering signals
            while( not timedout and std::find(entered.begin(), entered.end(), false) != entered.end() ) // Pass when 'false' cannot be found
            {
               // Check whether other processes have entered the barrier
               for(std::size_t source=0;source<mpiSize;source++)
               {
                  //std::cerr<<"rank "<<myRank<<": has process "<<source<<" entered BarrierWithTimeout? "<<entered[source]<<std::endl;
                  if( Iprobe(source, tag, &status) )
                  {
                     start = std::chrono::system_clock::now();
                     // Clear out any other barrier entry messages that this process may have sent in previous loops
                     // (for example if it has already timed out waiting for us in this barrier for several attempts)
                     int max_loops = 10000; // Just hardcoded; if more messages than this are waiting then something crazy has happened.
                     Recv_all(&recv_buffer, 1, source, tag, max_loops);
                     // The last message will indicate whether the sender process is waiting in their barrier, or has left it already
                     if(recv_buffer==BARRIER_ENTERED)
                     {
                       // Ok the source is (probably) waiting at this barrier (modulo message delays)
                       entered[source] = true;
                       LOGGER << "rank " << myRank <<": Process "<<source<<" has entered BarrierWithTimeout (with tag "<<tag<<"). Resetting timeout."<<EOM;
                     }
                     else if(recv_buffer==BARRIER_LEFT)
                     {
                       if(not entered[source])
                       {
                         LOGGER << "rank " << myRank <<": Last message from process "<<source<<" indicates that it has LEFT BarrierWithTimeout (with tag "<<tag<<"). We did not see it enter this barrier. We will continue waiting in the hope that it will re-enter the barrier soon."<<EOM;
                       }
                       else
                       {
                          LOGGER << "rank " << myRank <<": Process "<<source<<" has LEFT BarrierWithTimeout (with tag "<<tag<<"). We will therefore abandon the barrier as well."<<EOM;                                 timedout = true;
                       }
                     }
                     else
                     {
                       std::ostringstream errmsg;
                       errmsg << "Error in BarrierWithTimeout! Unrecognised barrier entry/exit message received from process "<<source<<" (value was "<<recv_buffer<<").";
                       utils_error().raise(LOCAL_INFO, errmsg.str());
                     }
                  }
               }

               // While waiting, could do work here.

               LOGGER << "rank " << myRank <<": sleeping... (total timeout = "<<total_timeout<<"ms; sleeptime = "<<sleeptime.tv_nsec*1e-6<<"ms)"<< EOM;
               // sleep (is a busy sleep, but at least will avoid slamming MPI with constant Iprobes)
               nanosleep(&sleeptime,NULL);

               // Check if timeout interval has been exceeded
               std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
               std::chrono::duration<double> time_waited = current - start;
               std::chrono::duration<double> true_time_waited = current - truestart;
               double time_waited_d = std::chrono::duration_cast<std::chrono::milliseconds>(time_waited).count();
               double true_time_waited_d = std::chrono::duration_cast<std::chrono::milliseconds>(true_time_waited).count();

               double fraction = time_waited_d/total_timeout;
               LOGGER << "rank " << myRank <<": time_waited = "<<time_waited_d<<"ms ("<<fraction*100<<"%% of time allowed). True time waited is "<<true_time_waited_d<<"ms."<< EOM;

               if(not timedout)
               {
                 if(time_waited >= timeout) timedout = true;
               }
               else
               {
                 LOGGER << "rank " << myRank <<":'timedout' flag has been manually set, so we will abandon the barrier."<< EOM;
               }
            }
         }

         // if we timed out, spit out some errors
         if(timedout)
         {
            LOGGER << "rank " << myRank << ": timed out in BarrierWithTimeout (tag="<<tag<<") waiting for the following process(es): ";
            for(std::size_t source=0;source<mpiSize;source++)
            {
               if(not entered[source]) LOGGER << source << ", ";
            }
            LOGGER << EOM;
            // Tell all other processes that we are leaving the barrier.
            IsendToAll(&BARRIER_LEFT, 1, tag, &req_null);
         }
         else
         {
            // Do a barrier to sync the processes
            //LOGGER << "rank " << myRank << ": Entering final sync Barrier in BarrierWithTimeout (tag="<<tag<<")!" << EOM;
            //Barrier(); // For some reason this did not work as expected... some processed stopped by it and others were not? One process even exited, without the others! Wtf.
            LOGGER << "rank " << myRank << ": Synchronisation succeeded in BarrierWithTimeout (tag="<<tag<<")!" << EOM;
         }

         if(mpiSize>1)
         {
            int recv_buffer = 0; // To receive the null messages
            // Clean out any remaining Barrier entry messages before we try to sync again next loop
            int max_loops = 10000; // Just hardcoded; if more messages than this are waiting then something crazy has happened.
            Recv_all(&recv_buffer, 1, MPI_ANY_SOURCE, tag, max_loops);
         }
         return timedout;
      }

      /// This is a fancy barrier that waits a certain amount of time after the FIRST process
      /// enters before unlocking (so that other action can be taken). This means that all the
      /// processes that enter the barrier *do* get synchronised, even if the barrier unlocks.
      /// This helps the synchronisation to be achieved next time.
      /// NOTE! Don't use this! It is still experimental. It works, but can leave some messages
      /// lying around which can screw up MPI_Finalize. Stick to plain BarrierWithTimeout for now.
      bool Comm::BarrierWithCommonTimeout(std::chrono::duration<double> timeout,
                                          const int tag_entered,
                                          const int tag_timeleft)
      {
         std::size_t mpiSize = Get_size();
         std::size_t myRank  = Get_rank();
         bool timedout = false;

         std::vector<bool> entered(mpiSize,false); // should init to "false"
         entered[myRank] = true; // we know that we have entered the barrier
         LOGGER << "Entered BarrierWithCommonTimeout; timeout="<<std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count()<<" ms; tag_entered="<<tag_entered<<"; tag_timeleft="<<tag_timeleft<<EOM;
         if(mpiSize>1)
         {
            int null_recv_buffer = 0; // To receive the null messages
            MPI_Status status;

            // First, tell all other processes that we have entered the barrier
            IsendToAll(&null_send_buffer, 1, tag_entered, &req_null);

            // Setup timeout interval and sleep time
            unsigned int Nchecks = 10; // Check for messages 10 times evenly spaced over the timeout interval
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

            struct timespec sleeptime;
            sleeptime.tv_sec = 0;
            sleeptime.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timeout).count() / Nchecks;

            // Vector to keep track of processes from which we have received "time remaining" counts.
            std::vector<bool>  received_timeleft(mpiSize,false);
            received_timeleft[myRank] = true; // Don't need to message ourselves

            // Vector to keep track of processes to which we have sent *our* "time remaining" counts.
            std::vector<bool>  sent_timeleft(mpiSize,false);
            sent_timeleft[myRank] = true; // Don't need to message ourselves

            // Counter for extra loops used to clean up timing messages
            unsigned int overtime_loop = 0;
            unsigned int max_overtime_loops = 10; // Should really only need 1 on average
            bool overtime_exceeded = true; // No overtime used by default, only turned on if extra message cleanup needed

            // Now, loop and wait for all other processes to send their own entering signals
            while( (not (timedout and overtime_exceeded)) // Exit if both timeout and overtime loops are elapsed.
               and std::find(entered.begin(), entered.end(), false) != entered.end() ) // Pass when 'false' cannot be found
            {
               // Check which other processes have entered the barrier
               for(std::size_t source=0;source<mpiSize;source++)
               {
                  //std::cerr<<"rank "<<myRank<<": has process "<<source<<" entered BarrierWithTimeout? "<<entered[source]<<std::endl;
                  if(not entered[source] and Iprobe(source, tag_entered, &status) )
                  {
                     // Ok the source has now reached this barrier.
                     entered[source] = true;
                     Recv(&null_recv_buffer, 1, source, tag_entered);
                     LOGGER << myRank <<": "<<"Process "<<source<<" entered BarrierWithCommonTimeout."<< EOM;

                     // Clear out any other barrier entry messages that this process may have sent in previous loops
                     // (for example if it has already timed out waiting for us in this barrier for several attempts)
                     int max_loops = 10000; // Just hardcoded; if more messages than this are waiting then something crazy has happened.
                     Recv_all(&null_recv_buffer, 1, source, tag_entered, max_loops);
                  }
               }

               // Send our "timeleft" data to all processes waiting in this loop (that we know about), if we haven't already done so
               // Some processes might be in the loop but we haven't gotten the message yet; they will have to wait until at least
               // the next loop iteration before getting our timing data.
               for(std::size_t source=0;source<mpiSize;source++)
               {
                  if(entered[source] and not sent_timeleft[source])
                  {
                     unsigned long buf_timeleft;
                     std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
                     std::chrono::duration<double> our_timeleft = timeout - (current - start);
                     buf_timeleft = std::chrono::duration_cast<std::chrono::milliseconds>(our_timeleft).count();
                     Isend(&buf_timeleft, 1, source, tag_timeleft, &req_null);
                     sent_timeleft[source] = true;
                     LOGGER << myRank <<": "<< "Sent our_timeleft ("<<buf_timeleft<<" ms) to process "<<source<< EOM;
                  }
               }

               // From processes that we know are waiting in this loop, check for messages from them with their time_left data
               for(std::size_t source=0;source<mpiSize;source++)
               {
                  if(entered[source] and not received_timeleft[source] and Iprobe(source, tag_timeleft, &status)) // wait to receive regardless of whether they have sent the message yet.
                  {
                     // Ok the source is trying to tell us how much time they have left in their Barrier, record this.
                     received_timeleft[source] = true;
                     unsigned long buf_timeleft;
                     LOGGER << myRank <<": "<< "Attempting to receive their_timeleft from process "<<source<<EOM;
                     int max_loops = 10000; // This is pretty extreme, if this many old timing messages have piled up then something has gone terribly wrong.
                     Recv_all(&buf_timeleft, 1, source, tag_timeleft, max_loops); // Recv all timing messages that may have piled up
                     LOGGER << myRank <<": "<< "Received their_timeleft ("<<buf_timeleft<<" ms) from process "<<source<<EOM;
                     //Update our own timeleft to reflect this
                     //i.e. subtract difference between our timeleft and theirs from total timeout time.
                     std::chrono::milliseconds their_timeleft(buf_timeleft);
                     std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
                     std::chrono::duration<double> our_timeleft = timeout - (current - start);
                     std::chrono::duration<double> diff = our_timeleft - their_timeleft;
                     if(diff>std::chrono::milliseconds(10)) // We have more time left than them, need to correct. But ignore discrepances of less than 100 ms.
                     {
                        timeout = timeout - diff;
                        // Debug
                        LOGGER << myRank <<": "<< "Adjusting timeout; process "<<source<<" reports that it has "<<std::chrono::duration_cast<std::chrono::milliseconds>(their_timeleft).count()<<" ms until timeout, but we have "<<std::chrono::duration_cast<std::chrono::milliseconds>(our_timeleft).count()<<" ms left. Our remaining time is longer than theirs, so we will subtract "<<std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()<<" ms to improve synchronisation." << EOM;
                     } else {
                        LOGGER << myRank <<": "<< "Difference between their_timeleft and our_timeleft is less than 10ms; will not bother to adjust." << EOM;
                     }
                  }
               }

               // While waiting, could do work here.
               LOGGER << myRank <<": "<< "sleeping... (total timeout = "<<std::chrono::duration_cast<std::chrono::seconds>(timeout).count()<<"; sleeptime = "<<sleeptime.tv_nsec*1e-9<<")"<< std::endl << std::flush << EOM; // Seem to need to flush before the nanosleep for some reason, or else the message vanishes (if output to std::cerr).
               // sleep (is a busy sleep, but at least will avoid slamming MPI with constant Iprobes)
               nanosleep(&sleeptime,NULL);

               // Check if timeout interval has been exceeded
               std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
               std::chrono::duration<double> time_waited = current - start;
               //std::cerr << "rank " << myRank <<": time_waited = "<<std::chrono::duration_cast<std::chrono::seconds>(time_waited).count() << std::endl;

               if(time_waited >= timeout) timedout = true;

               if(timedout)
               {
                  // Check if we have received all the timing messages that we were supposed to.
                  // (i.e. make sure that we received timing messages from everyone who was supposed to have entered the barrier)
                  // If we have not, then we enter overtime loops to try and collect them.
                  overtime_exceeded = true; // If no problems, will not perform overtime loop
                  for(std::size_t source=0;source<mpiSize;source++)
                  {
                     if(entered[source] and not received_timeleft[source])
                     {
                        // Doh, missing a message (they may not have realised we are in the loop yet, and so have been delayed in sending us their timing data. We will do some extra loops to try and collect it)
                        if(overtime_loop < max_overtime_loops)
                        {
                          // We are allowed to keep looping, and have a reason to do so. Activate overtime loops.
                          overtime_exceeded = false;
                          LOGGER << "BarrierWithCommonTimeout has timed out, but we have not received 'their_timeleft' from process "<<source<<" despite it having been detected as having entered the barrier. We will do an overtime loop to try to Recv this message. (overtime_loop="<<overtime_loop<<" of max "<<max_overtime_loops<<")"<<EOM;
                        } else {
                          LOGGER << "BarrierWithCommonTimeout has timed out, but we have not received 'their_timeleft' from process "<<source<<" despite it having been detected as having entered the barrier. No more overtime loops are permitted, so that message will be abandoned!"<<EOM;
                        }
                     }
                  }
                  ++overtime_loop;
               }

               LOGGER << myRank <<": "<< "End of wait loop; time left to timeout: "<<std::chrono::duration_cast<std::chrono::milliseconds>(timeout - time_waited).count()<<" ms"<<EOM;
            }


            // Check that we didn't screw up the logic and leave some message unreceived somehow
            for(std::size_t source=0;source<mpiSize;source++)
            {
               if((not timedout) and not entered[source])
               {
                 // Supposedly the synchronisation succeeded, but process 'source' is not recorded as having entered the barrier!
                 LOGGER << "Error! Exiting BarrierWithCommonTimeout, but inconsistency in final state detected. Synchronisation registered as successful, but process "<<source<<" was not detected as having entered the barrier!"<<EOM;
               }

               if(entered[source])
               {
                 if(not sent_timeleft[source])
                 {
                    LOGGER << "WARNING! Exiting BarrierWithCommonTimeout, but inconsistency in final state detected. Process "<<source<<" was detected as having entered the barrier, however we (process "<<myRank<<") did not send 'our_timeleft' to that process"<<EOM;
                 }

                 // From processes that we know are waiting in this loop, check for messages from them with their time_left data
                 if(not received_timeleft[source])
                 {
                    LOGGER << "WARNING! Exiting BarrierWithCommonTimeout, but inconsistency in final state detected. Process "<<source<<" was detected as having entered the barrier, however we (process "<<myRank<<") did not received 'their_timeleft' from that process"<<EOM;
                 }
               }
            }

         }

         // if we timed out, spit out some errors
         if(timedout)
         {
            LOGGER << "rank " << myRank << ": timed out in BarrierWithCommonTimeout (tag_entered="<<tag_entered<<") waiting for the following process(es): ";
            for(std::size_t source=0;source<mpiSize;source++)
            {
               if(not entered[source]) LOGGER << source << ", ";
            }
            LOGGER << std::endl;
         }
         LOGGER << "Leaving BarrierWithCommonTimeout (tag_entered="<<tag_entered<<")"<<EOM;
         return timedout;
      }

      /// This routine exists for MPI debugging purposes, to help make sure that
      /// all MPI messages are received before MPI_Finalize is called.
      /// It doesn't fix any problems, it just lets us notice if they exist.
      void Comm::check_for_unreceived_messages(int timeout)
      {
        int mpiSize = Get_size();
        int myRank  = Get_rank();

        // Wait 'timeout' seconds before checking for messages, to make sure
        // that other processes don't send more after we check.
        struct timespec sleeptime;
        sleeptime.tv_sec = timeout;
        sleeptime.tv_nsec = 0;
        logger() << LogTags::core << LogTags::info << "Waiting "<<timeout<<" seconds for any pending MPI communication to be transmitted, then we will check for unreceived messages from all processes (in communicator group "<<Get_name()<<")"<<EOM;
        nanosleep(&sleeptime,NULL);

        logger() << LogTags::core << LogTags::info << "Unreceived message report for communicator group "<<Get_name()<<":"<<std::endl;
        bool unreceived_messages_detected(false);
        for(int rank=0; rank<mpiSize; rank++)
        {
           if(rank!=myRank)
           {
              MPI_Status status;
              if(Iprobe(rank, MPI_ANY_TAG, &status))
              {
                 unreceived_messages_detected = true;
                 logger() << "  Unreceived messages detected from rank "<<rank<<" with tag "<<status.MPI_TAG<<std::endl;
              }
           }
        }
        if(not unreceived_messages_detected)
        {
           logger() << "  No unreceived messages detected!";
        }
        logger()<<EOM;
      }


      /// Get the process ID of the master process (rank 0)
      long int Comm::MasterPID()
      {
        if (not Is_initialized())
        {
          utils_error().raise(LOCAL_INFO, "Error retrieving process ID for rank0; MPI has not been initialised!");
        }
        return pid;
      }

      /// Get the process ID of the master process (rank 0)
      void Comm::set_MasterPID(long int p) { pid = p; }

      /// @}

      /// Check if MPI_Init has been called (it is an error to call it twice)
      bool Is_initialized()
      {
        int flag;
        MPI_Initialized(&flag);
        return (flag!=0);
      }

      /// Check if MPI_Finalize has been called (it is an error to do anything else after this)
      bool Is_finalized()
      {
        int flag;
        MPI_Finalized(&flag);
        return (flag!=0);
      }

      /// @{ Helpers for registration of compound datatypes
      // DEPRECATED! No longer sending compound datatypes via MPI. Leaving this here in case we need to do it in the future.
      //
      // /// Get vector storing functions to be run when MPI initialises.
      // std::vector<MpiIniFunc>& get_mpi_ini_functions()
      // {
      //    static std::vector<MpiIniFunc> mpi_ini_functions;
      //    return mpi_ini_functions;
      // }

      // /// Constructor for AddMpiInitFunc
      // ///
      // /// AddMpiInitFunc will add functions to the map when it is constructed. Works
      // /// on the same idea as the "ini_code" struct, except it doesn't
      // /// cause the functions to be run, just "queues them up" so to speak.
      // AddMpiIniFunc::AddMpiIniFunc(const std::string& local_info, const std::string& name, void(*func)())
      // {
      //    get_mpi_ini_functions().push_back(MpiIniFunc(local_info,name,func));
      // }

      /// @}

      /// Initialise MPI
      void Init()
      {
        // Dummies; can't rely on being able to use these seriously as the MPI standard doesn't mandate it.
        int argc = 0;
        char** argv = NULL;

        // Run any functions needed to queue up MPI datatype definition functions
        // (still a little hacky, but works)
        // DEPRECATED! No longer adding any new MPI datatypes, for now anyway
        // Printers::queue_mpidefs();

        // Do basic interrogation
        #ifdef MPI_DEBUG_OUTPUT
        std::cerr << "Hooking up to MPI..." << std::endl;
        #endif
        if(Is_initialized())
        {
           std::ostringstream errmsg;
           errmsg << "Error initialising MPI! It is already initialised!";
           utils_error().raise(LOCAL_INFO, errmsg.str());
        }
        else
        {
           int errflag;
           errflag = MPI_Init(&argc,&argv);

           // // Test case for thread-safe MPI. Probably not going to use this though.
           // int provided; // output; level of thread support provided (may not meet the requested level)
           // errflag = MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided);
           // if(provided<MPI_THREAD_MULTIPLE)
           // {
           //    std::ostringstream errmsg;
           //    errmsg << "Error initialising MPI with thread support level MPI_THREAD_FUNNELED. The implementation did not provide the requested level of thread support; the best it could do was ";
           //    switch(provided)
           //    {
           //       case MPI_THREAD_SINGLE:     errmsg<<"MPI_THREAD_SINGLE"; break;
           //       case MPI_THREAD_FUNNELED:   errmsg<<"MPI_THREAD_FUNNELED"; break;
           //       case MPI_THREAD_SERIALIZED: errmsg<<"MPI_THREAD_SERIALIZED"; break;
           //       case MPI_THREAD_MULTIPLE:   errmsg<<"MPI_THREAD_MULTIPLE"; break;
           //       default: errmsg<<"[UNRECOGNISED CODE!!!]"; break;
           //    }
           //    utils_error().raise(LOCAL_INFO, errmsg.str());
           // }

           if(errflag!=0) {
              std::ostringstream errmsg;
              errmsg << "Error initialising MPI! Received error flag: "<<errflag;
              utils_error().raise(LOCAL_INFO, errmsg.str());
           }
        }

        // Create communicator and check out basic info
        Comm COMM_WORLD;

        // Get the local process ID
        long int pid = getpid();
        std::vector<long int> pid_vec;
        pid_vec.push_back(pid);

        #ifdef MPI_DEBUG_OUTPUT
        std::cerr << "  Process pool size: " << COMM_WORLD.Get_size() << std::endl;
        std::cerr << "  I am process number " << COMM_WORLD.Get_rank() << ", with PID " << pid << std::endl;
        #endif

        // Distribute and save the process ID of the master process
        COMM_WORLD.Bcast(pid_vec, 1, 0);
        COMM_WORLD.set_MasterPID(pid_vec.at(0));

        #ifdef MPI_DEBUG_OUTPUT
        std::cerr << "  Master process PID " << COMM_WORLD.MasterPID() << std::endl;
        #endif

        // Run externally defined initialisation functions
        // DEPRECATED! No longer adding new MPI datatypes, at least for now
        // std::cerr << "  Running MPI initialisation functions..." << std::endl;
        // for (std::vector<MpiIniFunc>::iterator it=get_mpi_ini_functions().begin();
        //       it != get_mpi_ini_functions().end(); it++)
        // {
        //  #ifdef MPI_DEBUG_OUTPUT
        //  std::cerr << "    - Running function '"<<it->myname()<<"'" << std::endl;
        //  #endif
        //   try
        //   {
        //      it->runme(); // Run function.
        //   }
        //   catch (const std::exception& e)
        //   {
        //      std::cerr << "Gambit has failed to initialise MPI due to fatal exception: " << e.what() << std::endl;
        //      std::cerr << "raised from an mpi_ini_function (with label="<<it->myname()<<") declared at: " << it->mylocation() << std::endl;
        //      throw(e);
        //   }
        // }
        #ifdef MPI_DEBUG_OUTPUT
        std::cerr << "  MPI initialisation complete." << std::endl;
        #endif
      }

      // Finalize MPI, also check for pending messages as these could cause MPI_Finalize() to hang
      void Finalize()
      {
        if(not Is_finalized() and Is_initialized())
        {
          {
            Comm COMM_WORLD;
            #ifdef MPI_DEBUG_OUTPUT
            std::cerr << "rank " << COMM_WORLD.Get_rank() << ": Shutting down MPI..." << std::endl;
            #endif
          // Warn if any unreceived messages exist from WORLD (when it is destructed). Undelivered messages from other communicators are checked when their wrappers are destructed, so try to make sure this happens before finalize is called, otherwise the warnings will not occur.
          }
          MPI_Finalize();
        }
      }

      // Prepare to finalise MPI by checking for pending messages, as these could cause MPI_Finalize() to hang,
      // but call MPI_abort and exit if timeout is exceeded
      bool PrepareForFinalizeWithTimeout(bool use_mpi_abort)
      {
        bool synced_ok(false);
        if(not Is_finalized() and Is_initialized())
        {
          Comm COMM_WORLD;
          std::chrono::seconds timeout(10); // TODO: Perhaps make longer
          synced_ok = !COMM_WORLD.BarrierWithTimeout(timeout, 6666);  // TODO: decide on tag in a safer way
          if (!synced_ok)
          {
            // Doh timed out
            if(use_mpi_abort)
            {
              //#ifdef MPI_DEBUG_OUTPUT
              std::cerr << "rank " << COMM_WORLD.Get_rank() << ": FinalizeWithTimeout failed to sync for clean MPI shutdown, calling MPI_Abort..." << std::endl;
              //#endif
              COMM_WORLD.Abort();
            }
          }
        }
        return synced_ok;
      }

   }
}


#endif
