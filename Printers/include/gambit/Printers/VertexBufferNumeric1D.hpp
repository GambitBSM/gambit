//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration of VertexBufferNumeric1D class
///  This version of VertexBufferBase adds a
///  series of routines for managing a 1D data
///  buffer (i.e. a 1D array of scalars), and
///  for transmitting and receiving these buffers
///  via MPI. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 May
///
///  *********************************************
 
#ifndef __VertexBufferNumeric1D_hpp__
#define __VertexBufferNumeric1D_hpp__

#include <cstddef>
#include <sstream>
#include <iostream>

// HDF5 C bindings
#include <hdf5.h> 
 
// Gambit
#include "gambit/Printers/VertexBufferBase.hpp"
#include "gambit/Printers/VertexBuffer_mpitags.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"

//#define BUF_DEBUG /* Triggers debugging output */
//#define MONITOR_BUF "pointID" /* String ID of buffer to monitor. */

   
namespace Gambit {
  
  namespace Printers {

      /// Struct for a collection of MPI tags belonging to a single buffer
      struct BuffTags
      {
         int SYNC_data;   // message contains  T       buffer_entries[LENGTH]   
         int SYNC_valid;  //    "       "      bool    buffer_valid[LENGTH]   
         int RA_queue;    //    "       "      T       RA_write_queue[LENGTH]  
         int RA_loc;      //    "       "      hsize_t RA_write_locations[LENGTH] 
         int RA_length;   //    "       "      hsize_t RA_queue_length[LENGTH] //TODO err this is wrong 

         static const std::size_t NTAGS=5;
       
         bool valid;
 
         BuffTags()
            : SYNC_data (-1)
            , SYNC_valid(-1)
            , RA_queue  (-1)
            , RA_loc    (-1)
            , RA_length (-1)
            , valid(false)
         {}

         BuffTags(const int first_tag)
            : SYNC_data (first_tag)
            , SYNC_valid(first_tag+1)
            , RA_queue  (first_tag+2)
            , RA_loc    (first_tag+3)
            , RA_length (first_tag+4)
            , valid(true)
         {
           if(first_tag==-1) 
           {
             valid=false;
           }
           else if(first_tag<FIRST_EMPTY_TAG)
           {
              std::ostringstream errmsg;
              errmsg << "Error! Tried to create (valid) BuffTags from first_tag<FIRST_EMPTY_TAG ("<<first_tag<<"<"<<FIRST_EMPTY_TAG<<") (i.e. using reserved, or invalid, tag values)";
              printer_error().raise(LOCAL_INFO, errmsg.str());
           }
         }
      };
 
      /// VertexBuffer for simple numerical types
      template<class T, std::size_t LENGTH>
      class VertexBufferNumeric1D : public VertexBufferBase
      {
        protected:
          /// @{ Buffer variables for sequential writing
          // Using arrays as these are easier to write to hdf5
          bool  buffer_valid[LENGTH]; // Array telling us which buffer entries are properly filled
          T     buffer_entries[LENGTH];

          // DEPRECATED! No more MPI stuff needed.
          // /// Buffers to store data waiting to be sent via MPI
          // #ifdef WITH_MPI
          // BuffTags myTags; // Collection of MPI tags needed for passing messages
          // GMPI::Comm printerComm; // MPI communicator object from printer

          // int  send_buffer_valid[LENGTH];
          // T    send_buffer_entries[LENGTH];
          // bool send_buffer_ready = true; // flag to signal if send buffer can be filled with new data.

          // // Request handles for tracking status of a sent message
          // MPI_Request req_valid  =MPI_REQUEST_NULL;
          // MPI_Request req_entries=MPI_REQUEST_NULL;

          // // Status handles
          // MPI_Status stat_valid; 
          // MPI_Status stat_entries;
          // #endif
          // /// @}
 
          /// @{ Buffer variables for random access writing
          /// Queue for random access writes to dataset (independent of main buffer)
          T     RA_write_queue[LENGTH];
          /// Target pointIDs for RA writes.
          PPIDpair RA_write_locations[LENGTH];
          /// Current length of the RA write queue
          uint  RA_queue_length = 0;

          // DEPRECATED! No more MPI stuff needed
          // #ifdef WITH_MPI
          // /// MPI buffers, flags, and status+request handles for RA messages
          // T        send_buffer_RA_write_q[LENGTH];
          // PPIDpair send_buffer_RA_write_loc[LENGTH];
          // uint     send_buffer_RA_q_len;
          // uint     null_message;
          // bool     RA_send_buffer_ready = true; // flag to signal if send buffer can be filled with new data.

          // // Request handles for tracking status of a sent message
          // MPI_Request req_RA_write_q  =MPI_REQUEST_NULL;
          // MPI_Request req_RA_write_loc=MPI_REQUEST_NULL;
          // MPI_Request req_RA_q_len    =MPI_REQUEST_NULL;
          // MPI_Request req_RA_SENT     =MPI_REQUEST_NULL;

          // // Status handles
          // MPI_Status stat_RA_write_q;
          // MPI_Status stat_RA_write_loc;
          // MPI_Status stat_RA_q_len;
          // MPI_Status stat_RA_SENT;
          // #endif
          // /// @}
      
          /// MPI rank for this process
          uint myRank = 0;

        private:
          static const std::size_t bufferlength = LENGTH;

          /// Variable to check that "append" is not called twice in a row for the same scan point
          PPIDpair PPID_of_last_append;

          /// Special value for the above to use for skipping the double-append check (e.g. when receiving many points via MPI)
          static const PPIDpair null_PPID;

        public:
          /// Constructors
          VertexBufferNumeric1D()
            : VertexBufferBase()
            , buffer_valid()
            , buffer_entries()
            , PPID_of_last_append(null_PPID)
          {}

          // DEPRECATED! No more MPI needed
          // #ifdef WITH_MPI
          // VertexBufferNumeric1D(
          //       const std::string& label 
          //     , const int vID
          //     , const unsigned int i
          //     , const bool sync
          //     , const bool sil
          //     , const bool resume
          //     , const BuffTags& tags
          //     , const GMPI::Comm& pComm
          //  ): VertexBufferBase(label,vID,i,sync,sil,resume,true)
          //   , buffer_valid() 
          //   , buffer_entries()
          //   , myTags(tags)
          //   , printerComm(pComm)
          //   , PPID_of_last_append(null_PPID)
          // {
          //    myRank = pComm.Get_rank();

          //    //Debugging
          //    #ifdef BUF_DEBUG
          //    std::cout<<this->get_label()<<": My tags are: "
          //       <<tags.SYNC_data  <<", "
          //       <<tags.SYNC_valid <<", "
          //       <<tags.RA_queue   <<", "
          //       <<tags.RA_loc     <<", "
          //       <<tags.RA_length  <<", "
          //       <<std::endl; 
          //    #endif
          // }
          // #endif

          // No-MPI constructor. Can also be used with MPI, if output
          // is to be combined post-run.
          VertexBufferNumeric1D(
                const std::string& label 
              , const int vID
              , const unsigned int i
              , const bool sync
              , const bool sil
              , const bool resume
              , const char access
           ): VertexBufferBase(label,vID,i,sync,sil,resume,false,access)
            , buffer_valid() 
            , buffer_entries()
            // #ifdef WITH_MPI
            // , myTags()
            // , printerComm()
            // #endif
            , PPID_of_last_append(null_PPID)
          {
             // #ifdef WITH_MPI
             // myRank = printerComm.Get_rank();
             // #endif
          }


          /// Destructor
          ~VertexBufferNumeric1D()
          {} 

          /// Append a record to the buffer
          void append(const T& value, const PPIDpair pID = null_PPID);

          /// Virtual for debugging; find out what the absolute sync position is from the derived class.
          virtual unsigned long dset_head_pos() = 0;

          /// Virtual for debugging: Update the variables needed to track the currently target dset slot
          virtual void update_dset_head_pos() = 0;

          /// Queue up a desynchronised ("random access") dataset write to previous scan iteration
          void RA_write(const T& value, const PPIDpair pID, const std::map<PPIDpair, ulong>& PPID_to_dsetindex);

          /// No data to append this iteration; skip this slot
          virtual void skip_append();

          /// Skip several/many positions
          /// NOTE! This is meant for initialising new buffers to the correct
          /// position. If buffer overflows it may get cleared without data
          /// being written, so don't use this in other contexts.
          virtual void N_skip_append(ulong N);

          // Trigger MPI send of sync buffer to master node, or write to disk
          virtual void flush();

          // Trigger MPI send of random-access buffer to master node, or write to disk
          virtual void RA_flush(const std::map<PPIDpair, ulong>& PPID_to_dsetindex);

          // Perform write to disk of sync buffer 
          virtual void write_to_disk() = 0;            

          // Perform write to disk of random-access buffer
          virtual void RA_write_to_disk(const std::map<PPIDpair, ulong>& PPID_to_dsetindex) = 0;

          /// Write externally-supplied buffer to HDF5 dataset
          virtual void write_external_to_disk(const T (&values)[LENGTH], const bool (&isvalid)[LENGTH]) = 0;

          // #ifdef WITH_MPI
          // // Probe for a sync buffer MPI message from a process
          // virtual bool probe_sync_mpi_message(uint,int*);

          // // Probe for a RA buffer MPI message from a process
          // virtual bool probe_RA_mpi_message(uint);

          // // Retrieve sync buffer data from an MPI message from a known process rank
          // // Should only be triggered if a valid message is known to exist to be retrieved!
          // virtual void get_sync_mpi_message(uint,int);

          // // Retrieve RA buffer data from an MPI message from a known process rank
          // // Should only be triggered if a valid message is known to exist to be retrieved!
          // virtual void get_RA_mpi_message(uint, const std::map<PPIDpair, ulong>& PPID_to_dsetindex);

          // // Update myTags with valid values
          // virtual void update_myTags(uint);
          // #endif

          // Report queue length (e.g. for checking that it is empty during finalise)
          virtual uint get_RA_queue_length() { return RA_queue_length; }

          /// Extract (copy) a record
          T get_entry(const std::size_t i) const;
 
          /// Clear the buffer
          void clear();

      };

      /// @{ Static member definitions
  
      /// Use to skip the double-append check (for receiving many points via MPI)
      template<class T, std::size_t L>
      const PPIDpair VertexBufferNumeric1D<T,L>::null_PPID = PPIDpair(); // The default constructor for PPID includes a flag marking it as "invalid" 

      /// @}

      /// @{ VertexBufferNumeric1D function definitions

      /// Append a record to the buffer
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::append(const T& data, const PPIDpair pID)
      {
         if(not this->is_silenced())
         {
            //std::cout<<"rank "<<myRank<<": Buffer "<<this->get_label()<<", head_position ("<<this->get_head_position()<<"), pID ("<<pID.pointID<<","<<pID.rank<<"): running append()"<<std::endl;

            if(pID!=null_PPID and pID==PPID_of_last_append)
            {
               std::ostringstream errmsg;
               errmsg << "Error! Tried to append data to buffer "<<this->get_label()<<" (vID="<<this->get_vertexID()<<", index="<<this->get_index()<<") but supplied PPID matches PPID_of_last_append, i.e. the previous append was to the same point (rank="<<pID.rank<<", pointID="<<pID.pointID<<", [valid="<<PPID_of_last_append.valid<<"])! This indicates a bug in the buffer calling code.";
               printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            if(sync_buffer_is_full())
            {
               std::ostringstream errmsg;
               errmsg << "Error! Tried to append data to buffer "<<this->get_label()<<" (vID="<<this->get_vertexID()<<", index="<<this->get_index()<<") but the sync buffer is full! It should have been sent to the master node via MPI or written to disk before now.";
               printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            // Debug dump
            #ifdef BUF_DEBUG
            #ifdef MONITOR_BUF
            if(this->get_label()==MONITOR_BUF) {
            #endif
            std::cout<<"-------------------------------------"<<std::endl;
            std::cout<<"rank "<<myRank<<": Called 'VertexBufferNumeric1D<T,L>::append'"<<std::endl;
            std::cout<<"rank "<<myRank<<": Dump from buffer '"<<this->get_label()<<"'"<<std::endl;
            std::cout<<"rank "<<myRank<<": dset_head_pos()  = "<<dset_head_pos()<<std::endl;
            std::cout<<"rank "<<myRank<<": donepoint() = "<<this->donepoint()<<std::endl;
            std::cout<<"rank "<<myRank<<": After write, will increment head_position: "<<this->get_head_position()<<" --> "<<this->get_head_position()+1<<std::endl;
            #ifdef MONITOR_BUF
            }           
            #endif
            #endif

            error_if_done(); // make sure buffer hasn't written to the current point already
            buffer_entries[this->get_head_position()] = data;
            buffer_valid[this->get_head_position()] = true;
            this->move_head_to_next_slot();
            this->sync_buffer_empty = false;
            if(this->get_head_position()==bufferlength) 
            {
               #ifdef BUF_DEBUG
               #ifdef MONITOR_BUF
               if(this->get_label()==MONITOR_BUF) {
               #endif
               std::cout<<"rank "<<myRank<<": Buffer "<<this->get_label()<<": head_position ("<<this->get_head_position()<<") == bufferlength ("<<bufferlength<<"); setting sync_buffer_full=true."<<std::endl;
               #ifdef MONITOR_BUF
               }
               #endif
               #endif
               this->sync_buffer_full = true;
           }
           PPID_of_last_append = pID;
         }   
      }

      /// No data to append this iteration; skip this slot
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::skip_append()
      {
         if(not this->is_silenced()) {
            //std::cout<<"rank "<<myRank<<": Buffer "<<this->get_label()<<", head_position ("<<this->get_head_position()<<"): running skip_append()"<<std::endl;
            if(sync_buffer_is_full())
            {
               std::ostringstream errmsg;
               errmsg << "Error! Tried to skip_append (null-)data to buffer "<<this->get_label()<<" but the sync buffer is full! It should have been sent to the master node via MPI or written to disk before now.";
               printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            error_if_done(); // make sure buffer hasn't written to the current point already
            buffer_valid[this->get_head_position()] = false;
            this->move_head_to_next_slot();
            this->sync_buffer_empty = false;
            if(this->get_head_position()==bufferlength)
            {
               #ifdef BUF_DEBUG
               #ifdef MONITOR_BUF
               if(this->get_label()==MONITOR_BUF) {
               #endif
               std::cout<<"rank "<<myRank<<": Buffer "<<this->get_label()<<": head_position ("<<this->get_head_position()<<") == bufferlength ("<<bufferlength<<"); setting sync_buffer_full=true."<<std::endl;
               #ifdef MONITOR_BUF
               }
               #endif
               #endif
               this->sync_buffer_full = true;
            }
         }
      }

      /// Either send sync buffer data to master node via MPI, or trigger the write to disk
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::flush()
      {
         if(not this->is_silenced()) {
            // #ifdef WITH_MPI
            // // Prepate to send buffer data to master node
            // const int masterRank = 0;
            // if(this->MPI_mode()==true and myRank!=masterRank)
            // { // MPI-mode worker node instructions
            //    if(not send_buffer_ready)
            //    { 
            //       // Make sure previous messages are out of the send buffer before sending new ones.
            //       MPI_Wait(&req_valid, &stat_valid);
            //       MPI_Wait(&req_entries, &stat_entries);
            //       send_buffer_ready = true;
            //    }
            //    /// Compute how many points are to be sent to the master
            //    /// (should be a full buffers worth, except at the end of the
            //    /// run)
            //    std::size_t n_points_to_send = this->get_head_position(); //head should point to the index of the next empty buffer slot (or just past the end of the buffer), which is the number of slots preceding it, which are the ones we want to send. Should be equal to 'bufferlength' most of the time.

            //    /// Copy buffer data into the send buffer 
            //    for(uint i=0; i<n_points_to_send; i++)
            //    {
            //       send_buffer_valid[i]   = buffer_valid[i];
            //       send_buffer_entries[i] = buffer_entries[i];
            //    }

            //    /// Check that we actually have a set of valid tags 
            //    /// If we don't have them yet, throw an error. 
            //    /// Should be retrieved after
            //    /// one loop of the master, so if it is a whole buffer
            //    /// length behind then something is probably wrong.
            //    /// If we need to deal with this possibility (very slow
            //    /// loop on master) then some rethinking is needed here.
            //    if(not myTags.valid)
            //    {
            //       std::ostringstream errmsg;
            //       errmsg << "Error! Buffer "<<this->get_label()<<" (sync) is full, but MPI tags have not yet been received from the master process! These should have been sent one loop of the master after the creation of this buffer, and it is now one bufferlength since then, so it seems that the master is stuck relative to this process. This could potentially happen legitimately, but unfortunately the hdf5printer can't handle this corner case just yet.";
            //       printer_error().raise(LOCAL_INFO, errmsg.str());           
            //    }

            //    /// Perform non-blocking sends
            //    #ifdef MPI_DEBUG
            //    std::cout<<"rank "<<myRank<<"; buffer '"<<this->get_label()<<"': Isend-ing buffers to master"<<std::endl;
            //    #endif
            //    this->printerComm.Isend(send_buffer_valid,   n_points_to_send, masterRank, this->myTags.SYNC_valid, &req_valid);
            //    this->printerComm.Isend(send_buffer_entries, n_points_to_send, masterRank, this->myTags.SYNC_data,  &req_entries);
            //    send_buffer_ready = false;
            // }
            // else
            // {  // Master node instructions
            //    // (and worker node instructions in non-MPI mode)
            //    write_to_disk();
            // }
            // #else
            write_to_disk();
            // #endif
            clear();
         }
      } 

      /// Either send random-access buffer data to master node via MPI, or trigger the write to disk
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::RA_flush(const std::map<PPIDpair, ulong>& PPID_to_dsetindex)
      {
        if(this->is_synchronised())
        {
           std::ostringstream errmsg;
           errmsg << "rank "<<this->myRank<<": Error! Non-synchronised buffer attempted to perform RA_flush! Only non-synchronised buffers are permitted to do this. (buffer name = "<<this->get_label()<<")";
           printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }

        if(not this->is_silenced()) {
            // DEPRECATED! All processes now write their output independently, and we combine it at the end.
            // #ifdef WITH_MPI
            // // Prepate to send buffer data to master node
            // const int masterRank = 0;            
            // if(this->MPI_mode()==true and myRank!=masterRank and RA_queue_length!=0)
            // { // Worker node instructions
            //    if(not RA_send_buffer_ready)
            //    { 
            //       // Make sure previous messages are out of the send buffer before sending new ones.
            //       MPI_Wait(&req_RA_write_q,   &stat_RA_write_q);
            //       MPI_Wait(&req_RA_write_loc, &stat_RA_write_loc);
            //       MPI_Wait(&req_RA_q_len,     &stat_RA_q_len);
            //       MPI_Wait(&req_RA_SENT,      &stat_RA_SENT);
            //       RA_send_buffer_ready = true;
            //    }
            //    /// Copy buffer data into the send buffer 
            //    send_buffer_RA_q_len = RA_queue_length;
            //    for(uint i=0; i<RA_queue_length; i++)
            //    {
            //       send_buffer_RA_write_q[i]   = RA_write_queue[i];
            //       send_buffer_RA_write_loc[i] = RA_write_locations[i];
            //    }

            //    /// Check that we actually have a set of valid tags 
            //    /// If we don't have them yet, throw an error. 
            //    /// Should be retrieved after
            //    /// one loop of the master, so if it is a whole buffer
            //    /// length behind then something is probably wrong.
            //    /// If we need to deal with this possibility (very slow
            //    /// loop on master) then some rethinking is needed here.
            //    if(not myTags.valid)
            //    {
            //       std::ostringstream errmsg;
            //       errmsg << "Error! Buffer "<<this->get_label()<<" (RA) is full, but MPI tags have not yet been received from the master process! These should have been sent one loop of the master after the creation of this buffer, and it is now one bufferlength since then, so it seems that the master is stuck relative to this process. This could potentially happen legitimately, but unfortunately the hdf5printer can't handle this corner case just yet.";
            //       printer_error().raise(LOCAL_INFO, errmsg.str());           
            //    }

            //    /// Perform non-blocking sends
            //    #ifdef MPI_DEBUG
            //    std::cout<<"rank "<<myRank<<"; buffer '"<<this->get_label()<<"': Isend-ing RA buffers to master"<<std::endl;
            //    #endif
            //    this->printerComm.Isend(&send_buffer_RA_write_q,   bufferlength, masterRank, this->myTags.RA_queue, &req_RA_write_q);
            //    this->printerComm.Isend(&send_buffer_RA_write_loc, bufferlength, masterRank, this->myTags.RA_loc, &req_RA_write_loc);
            //    this->printerComm.Isend(&send_buffer_RA_q_len,     1,            masterRank, this->myTags.RA_length, &req_RA_q_len);
            //    this->printerComm.Isend(&null_message,             1,            masterRank, RA_BUFFERS_SENT, &req_RA_SENT);
            //    RA_send_buffer_ready = false;
            // }
            // else
            // { // Master node instructions
            //   // (and worker node instructions in non-MPI mode)
            //   RA_write_to_disk(PPID_to_dsetindex);
            // }
            // #else
            RA_write_to_disk(PPID_to_dsetindex);
            // #endif
            RA_queue_length = 0;
         }
      }


      /// Queue up a desynchronised ("random access") dataset write to previous scan iteration
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::RA_write(const T& value, const PPIDpair pID, const std::map<PPIDpair, ulong>& PPID_to_dsetindex)
      {
         uint i = RA_queue_length;
         if(i>L)
         {
            std::ostringstream errmsg;
            errmsg << "Error! Attempted to do RA_write beyond end of RA buffer ("<<i<<" > "<<L<<")! (buffer name="<<this->get_label()<<")";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         if(not this->is_silenced()) {
            RA_write_queue[i]     = value;
            RA_write_locations[i] = pID;
            RA_queue_length += 1;
            if(RA_queue_length==L)
            {
               RA_flush(PPID_to_dsetindex);
            }
         }
      }

      // DEPECATED! No longer passing data around via MPI. Each process just writes independently and we combine it at the end.
      // #ifdef WITH_MPI
      // // Probe for a sync buffer MPI message from a process
      // template<class T, std::size_t L>
      // bool VertexBufferNumeric1D<T,L>::probe_sync_mpi_message(uint source, int* msgsize)
      // {
      //    this->MPImode_only(LOCAL_INFO); // throws error if MPI_mode()==false
      //    if(not myTags.valid)
      //    {
      //       // Cannot probe for messages until we receive our MPI tags. Ignore them for now
      //       std::cout<<"Attempted to probe for sync MPI messages in buffer "<<this->get_label()<<", but skipping this attempt since MPI tags have not yet been delivered"<<std::endl;
      //       return false;
      //    }

      //    MPI_Status status;
      //    bool is_data_msg  = printerComm.Iprobe(source, myTags.SYNC_data, &status);
      //    int msgsize_data  = GMPI::Get_count<T>(&status);
      //    bool is_valid_msg = printerComm.Iprobe(source, myTags.SYNC_valid, &status);
      //    int msgsize_valid = GMPI::Get_count<int>(&status);
      // 
      //    if(msgsize_data != msgsize_valid)
      //    {
      //       std::ostringstream errmsg;
      //       errmsg << "Error in buffer "<<this->get_label()<<" during probe_sync_mpi_message! Length of 'data' message ("<<msgsize_data<<") does not match length of 'validity' message ("<<msgsize_valid<<").";
      //       printer_error().raise(LOCAL_INFO, errmsg.str());
      //    }
      //    *msgsize = msgsize_data;

      //    return (is_data_msg or is_valid_msg);
      // }

      // // Probe for a random-access buffer MPI message from a process
      // template<class T, std::size_t L>
      // bool VertexBufferNumeric1D<T,L>::probe_RA_mpi_message(uint source)
      // {
      //    this->MPImode_only(LOCAL_INFO); // throws error if MPI_mode()==false
      //    if(not myTags.valid)
      //    {
      //       // Cannot probe for messages until we receive our MPI tags. Ignore them for now
      //       std::cout<<"Attempted to probe for RA MPI messages in buffer "<<this->get_label()<<", but skipping this attempt since MPI tags have not yet been delivered"<<std::endl;
      //       return false;
      //    }
      //    bool is_q_msg   = printerComm.Iprobe(source, myTags.RA_queue);
      //    bool is_loc_msg = printerComm.Iprobe(source, myTags.RA_loc);
      //    bool is_len_msg = printerComm.Iprobe(source, myTags.RA_length);
      //    return (is_q_msg or is_loc_msg or is_len_msg);
      // }

      // // Retrieve sync buffer data from an MPI message
      // // Should only be triggered if a valid message is known to exist to be retrieved from the input source!
      // template<class T, std::size_t LENGTH>
      // void VertexBufferNumeric1D<T,LENGTH>::get_sync_mpi_message(uint source, int exp_length)
      // {
      //   this->MPImode_only(LOCAL_INFO); // throws error if MPI_mode()==false
      //   if(exp_length < 0)
      //   {
      //     std::ostringstream errmsg;
      //     errmsg << "Error retrieving sync message in buffer "<<this->get_label()<<"! Invalid expected message length supplied ("<<exp_length<<" < 0)";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }
      //   uint uexp_length = exp_length;

      //   if(uexp_length > LENGTH)
      //   {
      //     std::ostringstream errmsg;
      //     errmsg << "Error retrieving sync message in buffer "<<this->get_label()<<"! Expected message length ("<<uexp_length<<") is larger than the allocated buffer size (LENGTH="<<LENGTH<<")";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }

      //   // An MPI_Iprobe should have been done prior to calling this function, 
      //   // in order to trigger delivery of the message to the correct buffer. 
      //   // So now we trust that this buffer is indeed supposed to receive the 
      //   // message. We can also use a blocking receive since we know that a
      //   // message is already waiting to be sent.

      //   // Buffers to store received message
      //   int recv_buffer_valid[LENGTH];   // Would like to make this bool, but that requires MPI C++ bindings.
      //   T   recv_buffer_entries[LENGTH];

      //   //#ifdef MPI_DEBUG
      //   // Double check that a message is actually waiting to be sent
      //   // There is a code bug if this is not the case
      //   MPI_Status status;
      //   bool message_waiting1 = printerComm.Iprobe(source, myTags.SYNC_valid, &status);
      //   bool message_waiting2 = printerComm.Iprobe(source, myTags.SYNC_data,  &status);
      //   if(not message_waiting1 and not message_waiting2)
      //   {
      //     std::ostringstream errmsg;
      //     errmsg << "Error! get_sync_mpi_message called with source="<<source<<", but there is no appropriately tagged message waiting to be delivered from that process! This is a bug, please report it.";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }
      //   // Double check that the message has the expected number of elements
      //   // (this must match across all the buffers we are retrieving together)
      //   int msgsize = GMPI::Get_count<T>(&status);
      //   if(msgsize != exp_length)
      //   {
      //     std::ostringstream errmsg;
      //     errmsg << "Error retrieving sync message in buffer "<<this->get_label()<<"! Message length ("<<msgsize<<") does not match expected length ("<<exp_length<<").";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }
      //   //#endif
      //                    
      //   #ifdef MPI_DEBUG
      //   std::cout<<"rank "<<myRank<<": Collecting sync buffer ("<<this->get_label()<<") from process "<<source<<std::endl;
      //   #endif

      //   printerComm.Recv(&recv_buffer_valid, msgsize, source, myTags.SYNC_valid);
      //   printerComm.Recv(&recv_buffer_entries, msgsize, source, myTags.SYNC_data);
      //                    
      //   #ifdef MPI_DEBUG
      //   std::cout<<"rank "<<myRank<<"; buffer '"<<this->get_label()<<"': Received sync buffer from rank "<<source<<" (size="<<msgsize<<"). Appending received data to my sync buffers."<<std::endl;
      //   #endif

      //   // Write the buffers to disk
      //   // write_external_to_disk(recv_buffer_entries,recv_buffer_valid);

      //   // Rather than do external write, I think it is cleaner to just feed
      //   // everything through the normal "append" system.

      //   for(int i=0; i<msgsize; i++)
      //   {          
      //     // Push an element of the received data into the buffer
      //     if(recv_buffer_valid[i])
      //     {
      //       append(recv_buffer_entries[i]);
      //     }
      //     else 
      //     {
      //       skip_append();
      //     }         

      //     // Check if we need to do a write to disk 
      //     // Note; the buffer should have been emptied (if needed)
      //     // BEFORE get_sync_mpi_message() was called, so the if the 
      //     // first append in this loop fails due to the buffer
      //     // being full then this indicates that that was 
      //     // probably not done.
      //     if(sync_buffer_is_full())
      //     {
      //       #ifdef MPI_DEBUG
      //       std::cout<<"rank "<<myRank<<": During get_sync_mpi_message; Buffer "<<this->get_label()<<" full, emptying it..."<<std::endl;
      //       #endif
      //       flush();
      //     } 
      //   }
      // }

      // // Retrieve RA buffer data from an MPI message
      // // Should only be triggered if a valid message is known to exist to be retrieved from the input source!
      // template<class T, std::size_t LENGTH>
      // void VertexBufferNumeric1D<T,LENGTH>::get_RA_mpi_message(uint source, const std::map<PPIDpair, ulong>& PPID_to_dsetindex)
      // {
      //   this->MPImode_only(LOCAL_INFO); // throws error if MPI_mode()==false
      //   // An MPI_Iprobe should have been done prior to calling this function, 
      //   // in order to trigger delivery of the message to the correct buffer. 
      //   // So now we trust that this buffer is indeed supposed to receive the 
      //   // message. We can also use a blocking receive since we know that a
      //   // message is already waiting to be sent.

      //   // Buffers to store received messages
      //   T        recv_buffer_RA_write_q[LENGTH];
      //   PPIDpair recv_buffer_RA_write_loc[LENGTH];
      //   uint     recv_buffer_RA_q_len;

      //   #ifdef MPI_DEBUG
      //   // Double check that a message is actually waiting to be sent
      //   // There is a code bug if this is not the case
      //   MPI_Status status;
      //   bool message_waiting1 = printerComm.Iprobe(source, myTags.RA_queue,  &status);
      //   bool message_waiting2 = printerComm.Iprobe(source, myTags.RA_loc,    &status);
      //   bool message_waiting3 = printerComm.Iprobe(source, myTags.RA_length, &status);
      //   if(not message_waiting1 and not message_waiting2 and not message_waiting3) {
      //     std::ostringstream errmsg;
      //     errmsg << "Error! get_RA_mpi_message called with source="<<source<<", but there is no appropriately tagged message waiting to be delivered from that process! This is a bug, please report it.";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }
      //   #endif

      //   uint null_message;
      //   printerComm.Recv(&recv_buffer_RA_write_q,   LENGTH, source, myTags.RA_queue );
      //   printerComm.Recv(&recv_buffer_RA_write_loc, LENGTH, source, myTags.RA_loc   );
      //   printerComm.Recv(&recv_buffer_RA_q_len,     1,      source, myTags.RA_length);
      //   printerComm.Recv(&null_message,             1,      source, RA_BUFFERS_SENT); // absorbs one off the queue if there are several

      //   #ifdef MPI_DEBUG
      //   std::cout<<"rank "<<myRank<<"; buffer '"<<this->get_label()<<"': Received random-access buffer from rank "<<source<<". Sending write commands through my RA buffers."<<std::endl;
      //   #endif

      //   // feed all write commands through the master process RA_write commands
      //   for(uint i=0; i<recv_buffer_RA_q_len; i++)
      //   {
      //      RA_write(recv_buffer_RA_write_q[i], recv_buffer_RA_write_loc[i], PPID_to_dsetindex);
      //   }
      // }

      // // Update myTags with valid values
      // template<class T, std::size_t L>
      // void VertexBufferNumeric1D<T,L>::update_myTags(uint first_tag)
      // {
      //   this->MPImode_only(LOCAL_INFO); // throws error if MPI_mode()==false
      //   if(myTags.valid)
      //   {
      //     std::ostringstream errmsg;
      //     errmsg << "Error! Tried to update MPI tags for buffer "<<this->get_label()<<", but the current tags are already valid!";
      //     printer_error().raise(LOCAL_INFO, errmsg.str());
      //   }
      //   myTags = BuffTags(first_tag);
      //   return;
      // }

      // #endif

      /// Extract (copy) a record
      template<class T, std::size_t L>
      T VertexBufferNumeric1D<T,L>::get_entry(const std::size_t i) const
      {
         if(this->is_silenced()) {
           std::string errmsg = "Error! Attempted to retrieve data from a silenced buffer!";
           printer_error().raise(LOCAL_INFO, errmsg);
         }
         if(buffer_valid[i])
         {
           return buffer_entries[i];
         }
         else
         {
           std::string errmsg = "Error! Attempted to retrieve data from an invalidated VertexBufferNumeric1D entry!";
           printer_error().raise(LOCAL_INFO, errmsg);
         }
      }

      /// Clear the buffer
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::clear()
      {
         if(not this->is_silenced()) {
            #ifdef BUF_DEBUG
            #ifdef MONITOR_BUF
            if(this->get_label()==MONITOR_BUF) {
            #endif
            std::cout<<"rank "<<myRank<<": Buffer "<<this->get_label()<<": clear()"<<std::endl;
            #ifdef MONITOR_BUF
            }
            #endif
            #endif

            for(std::size_t i=0; i<bufferlength; i++)
            {
               buffer_valid[i] = false;
               buffer_entries[i] = 0;
            }
            this->reset_head(); 
            this->sync_buffer_full = false;
            this->sync_buffer_empty = true;
         }
      }

      /// TODO: Deprecated.
      /// Skip several/many positions
      /// NOTE! This is meant for initialising new buffers to the correct
      /// position. If buffer overflows it will be cleared without data
      /// being written, so don't use this in other contexts.
      template<class T, std::size_t L>
      void VertexBufferNumeric1D<T,L>::N_skip_append(ulong N)
      {
         //std::cout << "rank "<<myRank<<": Pushing forward (new?) buffer '"<<this->get_label()<<"' by "<<N<<" positions"<<std::endl; 
         for(ulong i=0; i<N; i++)
         {
            if(this->sync_buffer_is_full()) clear();
            skip_append();
         }
      }

      /// @}
  }
}
#endif
