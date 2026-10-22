//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration of VertexBufferNumeric1D_HDF5 
///  class. 
///  This version of VertexBufferNumeric1D adds
///  routines for sending the Numeric1D buffers
///  to a DataSetInterface object, which in turn
///  handles the output to a HDF5 file.
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
 
#ifndef __VertexBufferNumeric1D_HDF5_hpp__
#define __VertexBufferNumeric1D_HDF5_hpp__

#include <cstddef>
#include <sstream>

// HDF5 C bindings
#include <hdf5.h> 
 
// Gambit
#include "gambit/Printers/VertexBufferNumeric1D.hpp"
#include "gambit/Printers/printers/hdf5printer/DataSetInterfaceScalar.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Logs/logger.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"

//#define HDF5_BUF_DEBUG /* Triggers debugging output */
//#define MONITOR_BUF "pointID" /* String ID of buffer to monitor. */
 
namespace Gambit {
  
  namespace Printers {
 
      /// VertexBuffer for simple numerical types - derived version that handles output to hdf5
      template<class T, std::size_t CHUNKLENGTH>
      class VertexBufferNumeric1D_HDF5 : public VertexBufferNumeric1D<T,CHUNKLENGTH> 
      {
         private:
           /// Interfaces to HDF5 datasets
           DataSetInterfaceScalar<bool,CHUNKLENGTH> _dsetvalid; // validity bools
           DataSetInterfaceScalar<T,CHUNKLENGTH>    _dsetdata;  // actual data 

           /// Getters for HDF5 dataset interfaces (extra error checking)
           DataSetInterfaceScalar<bool,CHUNKLENGTH>& dsetvalid(); // validity bools
           DataSetInterfaceScalar<T,CHUNKLENGTH>&    dsetdata();  // actual data             

           /// Extendible backup buffers for RA writes that need to be
           /// postponed due to the original sync writes not having been
           /// performed yet.
           std::vector<std::pair<T,PPIDpair>> postpone_write_queue_and_locs;             

           /// Dimension-0 index of the next empty hyperslab in the output datasets
           unsigned long nextemptyslab = 0;

           /// Variable obtained from somewhere external to the buffer,
           /// used to track the synchronisation position with other buffers
           /// Currently only used to ensure the RA buffers end up the same
           /// size as the sync buffers.
           unsigned long target_sync_pos = 0;

         public:
           /// Constructors
           VertexBufferNumeric1D_HDF5();
           #ifdef WITH_MPI
           VertexBufferNumeric1D_HDF5
             ( hid_t location_id
             , const std::string& name
             , const int vID
             , const unsigned int i
             , const bool sync
             , const bool silence
             , const bool resume
             , const BuffTags& tags
             , const GMPI::Comm& pComm
             );
           #endif
 
           // No MPI constructor
           VertexBufferNumeric1D_HDF5
             ( hid_t location_id
             , const std::string& name
             , const int vID
             , const unsigned int i
             , const bool sync
             , const bool silence
             , const bool resume
             , const char access
             );
     
           /// Destructor
           /// Make sure buffer contents are written to file when buffer object is destroyed
           ~VertexBufferNumeric1D_HDF5();

           /// (virtual for debugging purposes)
           /// Current absolute "write head" position for synchronised buffers
           virtual unsigned long dset_head_pos() { return nextemptyslab + this->get_head_position(); }

           // Print to std::cout a report on the sync status of this buffer
           virtual void sync_report();

           /// Write sync buffer to HDF5 dataset
           virtual void write_to_disk();

           /// Write externally-supplied buffer to HDF5 dataset
           virtual void write_external_to_disk(const T (&values)[CHUNKLENGTH], const bool (&isvalid)[CHUNKLENGTH]);

           /// Reset the output (non-synchronised datasets only, unless force=true)
           virtual void reset(bool force=false);

           // Finalise writing to underlying output. Do not do any more writing after this!
           virtual void finalise();

           /// Send random access write queue to dataset interfaces for writing
           virtual void RA_write_to_disk(const std::map<PPIDpair, ulong>& PPID_to_dsetindex);

           /// Attempt to write any postponed RA_write attempts to disk
           void attempt_postponed_RA_write_to_disk(const std::map<PPIDpair, ulong>& PPID_to_dsetindex);

           /// Update the variables needed to tracks the currently target dset slot
           /// (really just updates the nextemptyslab variable)
           virtual void update_dset_head_pos()
           {
              if(this->myRank==0 or not this->MPI_mode()) // Only the master process has access to this information, unless we are in non-MPI mode
              {
                if(dsetvalid().get_nextemptyslab() != dsetdata().get_nextemptyslab())
                {
                  // The two datasets controlled by this buffer should always remain synchronised!
                  std::ostringstream errmsg;
                  errmsg << "rank "<<this->myRank<<": Error! Validity and Data datasets have gone out of sync in buffer with label '"<<this->get_label()<<"'! This is a bug in the VertexBufferNumeric1D_HDF5 class. Please report it.";
                  printer_error().raise(LOCAL_INFO, errmsg.str()); 
                }
                nextemptyslab = dsetvalid().get_nextemptyslab();
              }
           }

           /// Ensure dataset "write head" (i.e. next append) is prepared to
           /// write to the supplied absolute dataset index (e.g. by inserting
           /// blank entries if need)
           void synchronise_output_to_position(const ulong i);
        
           /// Check how many RA writes are waiting in the postpone queue
           /// (mostly for debugging purposes)
           std::size_t postponed_RA_queue_length() { return postpone_write_queue_and_locs.size(); }

           // Needed for checking that dataset sizes on disk are consistent
           ulong get_dataset_length();

      };
 


      /// @{ VertexBufferNumeric1D_HDF5 member function definitions
 
      /// Constructors
      template<class T, std::size_t CHUNKLENGTH>
      VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::VertexBufferNumeric1D_HDF5()
        : VertexBufferNumeric1D<T,CHUNKLENGTH>()
        , _dsetvalid()
        , _dsetdata()
        , postpone_write_queue_and_locs()
      {}

      #ifdef WITH_MPI
      template<class T, std::size_t CHUNKLENGTH>
      VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::VertexBufferNumeric1D_HDF5(
          hid_t location_id
        , const std::string& name
        , const int vID
        , const unsigned int i
        , const bool sync
        , const bool silence
        , const bool resume
        , const BuffTags& tags
        , const GMPI::Comm& pComm
        )
        : VertexBufferNumeric1D<T,CHUNKLENGTH>(
            name
          , vID
          , i
          , sync
          , silence
          , resume
          , tags
          , pComm
          )
        , _dsetvalid()
        , _dsetdata()
        , postpone_write_queue_and_locs()
      {
        if(this->MPI_mode() and location_id==-1 and this->myRank==0)
        {
           std::ostringstream errmsg;
           errmsg << "rank "<<this->myRank<<": Error! Tried to create buffer '"<<this->get_label()<<"', but supplied HDF5 location pointer was -1 (and we are the rank 0 process, who needs this pointer)";
           printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }
        else if(not silence)
        {
          if(resume) 
          { 
             logger()<<LogTags::printers<<"Attempting to resume writing to dataset '"<<name<<"_isvalid'...";
          }
          else
          {
             logger()<<LogTags::printers<<"Creating new dataset '"<<name<<"_isvalid'...";
          }
          _dsetvalid = DataSetInterfaceScalar<bool,CHUNKLENGTH>(location_id, name+"_isvalid", resume);

          if(resume) 
          { 
             logger()<<std::endl<<LogTags::printers<<"Attempting to resume writing to dataset '"<<name<<"'...";
          }
          else
          {
             logger()<<std::endl<<LogTags::printers<<"Creating new dataset '"<<name<<"'...";
          }
          _dsetdata  = DataSetInterfaceScalar<T,CHUNKLENGTH>(location_id, name, resume);

          logger()<<EOM; // Leave this to calling function
        }
      }
      #endif     
 
      // No MPI constructor
      template<class T, std::size_t CHUNKLENGTH>
      VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::VertexBufferNumeric1D_HDF5(
          hid_t location_id
        , const std::string& name
        , const int vID
        , const unsigned int i
        , const bool sync
        , const bool silence
        , const bool resume
        , char access
        )
        : VertexBufferNumeric1D<T,CHUNKLENGTH>(
            name
          , vID
          , i
          , sync
          , silence
          , resume
          , access
          )
        , _dsetvalid()
        , _dsetdata()
        , postpone_write_queue_and_locs()
      {
        if(this->MPI_mode() and location_id==-1 and this->myRank==0)
        {
           std::ostringstream errmsg;
           errmsg << "rank "<<this->myRank<<": Error! Tried to create buffer '"<<this->get_label()<<"', but supplied HDF5 location pointer was NULL (and we are the rank 0 process, who needs this pointer)";
           printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }
        else if(not silence)
        {
          if(resume) 
          { 
             logger()<<LogTags::printers<<"Attempting to resume writing to dataset '"<<name<<"_isvalid'...";
          }
          else
          {
             logger()<<LogTags::printers<<"Creating new dataset '"<<name<<"_isvalid'...";
          }
          _dsetvalid = DataSetInterfaceScalar<bool,CHUNKLENGTH>(location_id, name+"_isvalid", resume, this->access_mode());

          if(resume) 
          { 
             logger()<<std::endl<<LogTags::printers<<"Attempting to resume writing to dataset '"<<name<<"'...";
          }
          else
          {
             logger()<<std::endl<<LogTags::printers<<"Creating new dataset '"<<name<<"'...";
          }
          _dsetdata  = DataSetInterfaceScalar<T,CHUNKLENGTH>(location_id, name, resume, this->access_mode());

          logger()<<EOM; // Leave this to calling function
        }
      }
 
      /// Destructor.
      /// Deliberately does NOT flush the buffer to disk.
      ///
      /// Buffer objects of this type are stored by value (in the
      /// std::map<VBIDpair, BuffType> inside H5P_LocalBufferManager) and
      /// are populated via the assign-from-temporary pattern at
      /// H5P_LocalBufferManager::get_buffer, so each buffer object's
      /// destructor runs at least once on a temporary that shares state
      /// (HDF5 dataset handles, sync counters) with the surviving
      /// container slot. Triggering write_to_disk() / RA_write_to_disk()
      /// here would therefore either double-write or write through stale
      /// state, depending on which copy is being destroyed. End-of-scan
      /// flushing is handled deterministically by HDF5Printer::flush()
      /// and HDF5Printer::finalise() instead, which iterate over the
      /// surviving buffers in the printer's all_buffers map.
      template<class T, std::size_t L>
      VertexBufferNumeric1D_HDF5<T,L>::~VertexBufferNumeric1D_HDF5()
      {
      }

      // Print out report on buffer sync status       
      template<class T, std::size_t L>
      void VertexBufferNumeric1D_HDF5<T,L>::sync_report()
      {
         std::cout<<"rank "<<this->myRank<<":-----------------------------------------"<<std::endl;
         std::cout<<"rank "<<this->myRank<<": Begin sync report for buffer "<<this->get_label()<<std::endl;
         std::cout<<"rank "<<this->myRank<<": Synchronised? = "<<this->is_synchronised()<<std::endl;
         std::cout<<"rank "<<this->myRank<<": nextemptyslab = "<<nextemptyslab<<std::endl;
         std::cout<<"rank "<<this->myRank<<": head_position = "<<this->get_head_position()<<std::endl;
         std::cout<<"rank "<<this->myRank<<": dset_head_pos = "<<this->dset_head_pos()<<std::endl;
         std::cout<<"rank "<<this->myRank<<": donepoint()   = "<<this->donepoint()<<std::endl;
         std::cout<<"rank "<<this->myRank<<": sync_buffer_full() = "<<this->sync_buffer_full<<std::endl;
         std::cout<<"rank "<<this->myRank<<": End sync report for buffer "<<this->get_label()<<std::endl;
         std::cout<<"rank "<<this->myRank<<":-----------------------------------------"<<std::endl;

      }
    
      /// @{ Safe dataset getters
      template<class T, std::size_t L>
      DataSetInterfaceScalar<bool,L>& VertexBufferNumeric1D_HDF5<T,L>::dsetvalid()
      {
        #ifdef WITH_MPI
        if(this->MPI_mode() and this->myRank!=0)
        {
            std::ostringstream errmsg;
            errmsg << "rank "<<this->myRank<<": Error! VertexBuffer (HDF5 type) in non-master process tried to access dsetvalid! This doesn't exist except on the master process (buffer is "<<this->get_label()<<")";
            printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }
        #endif 
        return _dsetvalid;
      }

      template<class T, std::size_t L>
      DataSetInterfaceScalar<T,L>& VertexBufferNumeric1D_HDF5<T,L>::dsetdata()
      {
        #ifdef WITH_MPI
        if(this->MPI_mode() and this->myRank!=0)
        {
            std::ostringstream errmsg;
            errmsg << "rank "<<this->myRank<<"Error! VertexBuffer (HDF5 type) in non-master process tried to access dsetdata! This doesn't exist except on the master process (buffer is "<<this->get_label()<<")";
            printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }
        #endif 
        return _dsetdata;
      }
      /// @}

      /// Override of buffer dump function to handle HDF5 output
      template<class T, std::size_t L>
      void VertexBufferNumeric1D_HDF5<T,L>::write_to_disk()
      {
         if(this->is_synchronised()) {
           // Check if buffer is empty, and whether we really want to write an
           // empty buffer to disk.
           if( not this->sync_buffer_is_empty() or
               this->dset_head_pos() >= dsetvalid().dset_length()
             ) // Should only have to check one of the datasets... perhaps add error checking for this.
           {
             dsetvalid().writenewchunk(this->buffer_valid); 
             dsetdata().writenewchunk(this->buffer_entries);
             // Update the head tracking variables to reflect the new dset chunk
             update_dset_head_pos();
           }
         }
         else {
            std::ostringstream errmsg;
            errmsg << "rank "<<this->myRank<<": Error! Tried to write_to_disk() synchronised write buffer of buffer with name "<<this->get_label()<<", but buffer is not flagged as running in synchronised mode! Please report this bug.";
            printer_error().raise(LOCAL_INFO, errmsg.str()); 
         }
      }

      /// Manual command to send an arbitrary buffer to be written to disk
      template<class T, std::size_t CHUNKLENGTH>
      void VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::write_external_to_disk(const T (&values)[CHUNKLENGTH], const bool (&isvalid)[CHUNKLENGTH])
      {
         if(not this->is_silenced()) {
           dsetvalid().writenewchunk(isvalid); 
           dsetdata().writenewchunk(values);
           // Update sync information to reflect the presence of the new chunk
           update_dset_head_pos();
         }
      }

      /// Reset the output (non-synchronised datasets only)
      template<class T, std::size_t L>
      void VertexBufferNumeric1D_HDF5<T,L>::reset(bool force) 
      { 
         if(not force and this->is_synchronised())
         {
            std::ostringstream errmsg;
            errmsg << "rank "<<this->myRank<<": Error! Tried to reset() a synchronised buffer! This is forbidden unless force=true. (buffer name = "<<this->get_label()<<")";
            printer_error().raise(LOCAL_INFO, errmsg.str()); 
         }

         // Clear the sync buffers
         this->clear();

         /// Empty the queue of postponed writes, because it would now
         /// be erased had we gotten around to writing it.
         postpone_write_queue_and_locs.clear();

         if(this->myRank==0 or not this->MPI_mode()) // Can only touch datasets on master process (unless we are in non-MPI mode)
         {
            /// Invalidate the contents of the linked datasets
            /// This can be done by simply resetting the all validity bools to "false"
            dsetvalid().zero();
            //dsetdata().zero(); // Should work fine, but should be unneccesary.

            // Point the write head (or "cursor") back at the beginning of the output datasets.
            dsetvalid().reset_nextemptyslab();
            dsetdata().reset_nextemptyslab();
         }
      }

      /// Attempt to write postponed RA entries to disk 
      template<class T, std::size_t CHUNKLENGTH>
      void VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::attempt_postponed_RA_write_to_disk(const std::map<PPIDpair, ulong>& PPID_to_dsetindex)
      {
         /// Use the provided PPIDpair-->dset_location map to locate the target
         /// parameter points in the output dataset. 
         /// (Temp RA buffers for immediate writes)
         bool valid[CHUNKLENGTH]; 
         T        now_write_queue[CHUNKLENGTH];             
         hsize_t  now_abs_write_locations[CHUNKLENGTH];
         uint     now_i=0; // queue_length

         /// Postponed entries which still cannot be written will be added here.
         std::vector<std::pair<T,PPIDpair>> failed;
         
         /// Need to go through the postponed entries one CHUNKLENGTH at a time
         typedef typename std::vector<std::pair<T,PPIDpair>>::iterator it_type;
         it_type itpp = postpone_write_queue_and_locs.begin();
         while(itpp != postpone_write_queue_and_locs.end())
         {
            T&        val = itpp->first;
            PPIDpair& loc = itpp->second;

            // Convert loc to abs dataset index (if possible)
            std::map<PPIDpair, ulong>::const_iterator it 
                = PPID_to_dsetindex.find(loc);

            if(it==PPID_to_dsetindex.end())
            {
               // No PPID found
               failed.push_back(*itpp);
            }
            else
            {
               // PPID found; convert to absolute dataset index and add to "now" queue
               now_write_queue[now_i]         = val;
               now_abs_write_locations[now_i] = it->second;
               now_i++;
            }

            // Increment iterator (need to do this before 'if' statement around RA_write call)
            ++itpp; 

            // Write "now" buffers to disk, if they aren't empty
            if(now_i != 0)
            {
               if(now_i>CHUNKLENGTH)
               {
                  std::ostringstream errmsg;
                  errmsg << "rank "<<this->myRank<<": Error! now_i has exceeded CHUNKLENGTH (now_i=="<<now_i<<") during attempt to perform postponed RA_writes. (buffer name = "<<this->get_label()<<")";
                  printer_error().raise(LOCAL_INFO, errmsg.str()); 
               }

               // Do the write only if buffer is full or postpone queue is finished and we
               // are about to finish looping.
               if(now_i==CHUNKLENGTH or itpp == postpone_write_queue_and_locs.end())
               {
                  std::fill(valid, valid+CHUNKLENGTH, false); 
                  std::fill(valid, valid+now_i, true); 
                  dsetvalid().RA_write(valid,           now_abs_write_locations, now_i); 
                  dsetdata().RA_write (now_write_queue, now_abs_write_locations, now_i);
                  //std::cout<<"Wrote "<<now_i<<" postponed RA items to disk"<<std::endl;
                  now_i = 0; // Reset buffer
               }
            }
         }
         // put failed write attempts back into the postpone queue
         postpone_write_queue_and_locs = failed;
      }


      /// Send random access write queue to dataset interfaces for writing
      template<class T, std::size_t CHUNKLENGTH>
      void VertexBufferNumeric1D_HDF5<T,CHUNKLENGTH>::RA_write_to_disk(const std::map<PPIDpair, ulong>& PPID_to_dsetindex)
      {
        if(this->is_synchronised())
        {
           std::ostringstream errmsg;
           errmsg << "rank "<<this->myRank<<": Error! Non-synchronised buffer attempted to perform RA_write_to_disk! Only non-synchronised buffers are permitted to do this. (buffer name = "<<this->get_label()<<")";
           printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }

        if(not this->is_silenced()) 
         {
            dsetvalid().extend_dset(target_sync_pos);
            dsetdata().extend_dset(target_sync_pos);

            #ifdef DEBUG_MODE
            std::cout<<"rank "<<this->myRank<<": Extended RA dset '"<<this->get_label()<<"' to at least size "<<target_sync_pos<<std::endl; 
            #endif

            if (this->RA_queue_length!=0 or postpone_write_queue_and_locs.size()!=0) 
            {
               #ifdef DEBUG_MODE
               std::cout<<"rank "<<this->myRank<<": Doing RA_write_to_disk for buffer '"<<this->get_label()<<"' (note: target_sync_pos="<<target_sync_pos<<", dset_head_pos()="<<this->dset_head_pos()<<")"<<std::endl;
               #endif 

               // Attempt to write any existing postponed RA write attempts to disk (again)
               attempt_postponed_RA_write_to_disk(PPID_to_dsetindex);

               //std::cout<<"rank "<<this->myRank<<": Number of items remaining in postpone queue after write attempt = "<<postpone_write_queue_and_locs.size()<<"); buffer is '"<<this->get_label()<<"'"<<std::endl;

               /// Use the provided PPIDpair-->dset_location map to locate the target
               /// parameter points in the output dataset. 
               /// (Temp RA buffers for immediate writes)
               bool valid[CHUNKLENGTH]; 
               T        now_write_queue[CHUNKLENGTH];             
               hsize_t  now_abs_write_locations[CHUNKLENGTH];
               uint     now_i=0; // queue_length

               // Now go through the current RA_queue and try to write them to disk
               for(ulong i=0; i<this->RA_queue_length; i++)
               {
                 // Some write locations may not be known yet due to the original
                 // data not yet having been written to disk from its sync buffer.
                 // We will have to postpone writing these until the next RA_write
                 // attempt.
                 std::map<PPIDpair, ulong>::const_iterator it 
                     = PPID_to_dsetindex.find(this->RA_write_locations[i]);
                 if(it==PPID_to_dsetindex.end())
                 {
                    // No PPID found; add to "postpone" queue
                    postpone_write_queue_and_locs.push_back(
                                  std::make_pair(this->RA_write_queue[i],
                                                 this->RA_write_locations[i])
                                  );
                 }
                 else
                 {
                    // PPID found; convert to absolute dataset index and add to "now" queue
                    now_write_queue[now_i]         = this->RA_write_queue[i];
                    now_abs_write_locations[now_i] = it->second;
                    now_i++;
                 }
               }               

               // Write "now" buffers to disk, if they aren't empty
               if(now_i != 0)
               {
                  if(now_i>CHUNKLENGTH)
                  {
                     std::ostringstream errmsg;
                     errmsg << "rank "<<this->myRank<<": Error! now_i has exceeded CHUNKLENGTH (now_i=="<<now_i<<"). (buffer name = "<<this->get_label()<<")";
                     printer_error().raise(LOCAL_INFO, errmsg.str()); 
                  }
                  std::fill(valid, valid+CHUNKLENGTH, false); 
                  std::fill(valid, valid+now_i, true); 
                  #ifdef DEBUG_MODE
                  std::cout<<"rank "<<this->myRank<<": writing buffer for "<<this->get_label()<<" to disk; now_i="<<now_i<<std::endl;
                  #endif
                  dsetvalid().RA_write(valid,           now_abs_write_locations, now_i); 
                  dsetdata().RA_write (now_write_queue, now_abs_write_locations, now_i);
               }

            }
         }
      }

      /// Ensure dataset "write head" (i.e. next append) is prepared to
      /// write to the supplied absolute dataset index (e.g. by inserting
      /// blank entries if need)
      ///
      /// NEW MEANING:
      /// Ensure that the supplied index has been written to, and that the
      /// next append will happen to the next index above it.
      template<class T, std::size_t L>
      void VertexBufferNumeric1D_HDF5<T,L>::synchronise_output_to_position(const ulong sync_pos)
      {
         if(not this->is_silenced()) 
         {
            // Make sure the correct dset_head_pos() is known
            update_dset_head_pos();

            // Update the variable which tracks the current sync position.
            // (do this regardless of whether this is a sync buffer or not)
            target_sync_pos = sync_pos;

            #ifdef HDF5_BUF_DEBUG
            std::cout<<"rank "<<this->myRank<<": Updated target_sync_pos to '"<<target_sync_pos<<" in buffer "<<this->get_label()<<std::endl; 
            #endif

            if(this->is_synchronised()) 
            {
               #ifdef HDF5_BUF_DEBUG
               #ifdef MONITOR_BUF
               if(this->get_label()==MONITOR_BUF) {
               #endif
               std::cout<<"rank "<<this->myRank<<": Synchronising buffer '"<<this->get_label()<<"' to position "<<sync_pos<<" (current dset_head_pos() = "<<this->dset_head_pos()<<")"<<std::endl;
               #ifdef MONITOR_BUF
               }
               #endif
               #endif 

               // Compare target position to current sync position and see what we need to do
               // The plus one is because the head_pos should be one larger than the sync_pos
               // for buffers who already did an append to the sync_pos; these buffers therefore
               // do not need to move.
               //
               const long movediff = sync_pos+1 - this->dset_head_pos();
               if(movediff==1)             
               {
                   // Set the current point as having no valid data and move to the next
                   this->skip_append();    
               } 
               else if(movediff<0)
               {
                   std::ostringstream errmsg;
                   errmsg << "rank "<<this->myRank<<": Error! Attempted to move HDF5 write position backwards in buffer with label '"<<this->get_label()<<"'! (movediff ("<<movediff<<") = sync_pos ("<<sync_pos<<")+1 - dset_head_pos() ("<<this->dset_head_pos()<<")) This is a bug in the VertexBufferNumeric1D_HDF5 class or in a class which uses it (probably HDF5Printer). Please report it. (Note, writing to old points can be done but requires using special write functions).";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
               } 
               else if (movediff==0)
               {
                 if(this->donepoint())
                 {
                   std::ostringstream errmsg;
                   errmsg << "rank "<<this->myRank<<": Error! Attempted to move HDF5 write position by 0 slots in buffer with label '"<<this->get_label()<<"' (movediff ("<<movediff<<") = sync_pos ("<<sync_pos<<")+1 - dset_head_pos ("<<this->dset_head_pos()<<")); this part is fine, however the buffer indicates that this position has already received a write (donepoint()==true) so it should have moved forward! This is a bug in the VertexBufferNumeric1D_HDF5 class or in a class which uses it (probably HDF5Printer). Please report it.";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
                 }
                 // otherwise no problem; carry on.
               }
               else if (movediff>1) // and movediff!=CHUNKLENGTH+1) 
               {
                   std::ostringstream errmsg;
                   errmsg << "rank "<<this->myRank<<": Error! Attempted to move HDF5 write position by >1 slots ("<<movediff<<") in buffer with label '"<<this->get_label()<<"' (movediff ("<<movediff<<") = sync_pos ("<<sync_pos<<")+1 - dset_head_pos() ("<<this->dset_head_pos()<<")). Buffer synchronisation should only happen one slot at a time. This is a bug in the VertexBufferNumeric1D_HDF5 class or in a class which uses it (probably HDF5Printer). Please report it.";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
               }

               #ifdef HDF5_BUF_DEBUG
               #ifdef MONITOR_BUF
               if(this->get_label()==MONITOR_BUF) {
               #endif
               long slots_left = L;
               slots_left -= this->get_head_position() - this->donepoint();
               std::cout<<"rank "<<this->myRank<<": Moved "<<movediff<<" slot(s). # unwritten slots left in buffer = "<<slots_left<<". buffer_is_full = "<<this->sync_buffer_is_full()<<std::endl;         
               std::cout<<"rank "<<this->myRank<<":   Buffer length:"<<L<<std::endl;
               std::cout<<"rank "<<this->myRank<<":   head_position:"<<this->get_head_position()<<std::endl;	 
               std::cout<<"rank "<<this->myRank<<":   donepoint()  :"<<this->donepoint()<<std::endl;		
	
               #ifdef MONITOR_BUF
               }
               #endif
               #endif 
            }
         }
      }
 
      template<class T, std::size_t L>
      ulong VertexBufferNumeric1D_HDF5<T,L>::get_dataset_length()
      {
         if(dsetvalid().dset_length() != dsetdata().dset_length())
         {
            std::ostringstream errmsg;
            errmsg << "rank "<<this->myRank<<": Error! Lengths of 'data' and 'valid' datasets for buffer "<<this->get_label()<<" are different ("<<dsetdata().dset_length()<<" and "<<dsetvalid().dset_length()<<" respectively). This should never happen.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }
         return dsetdata().dset_length();
      }

      // Finalise writing to underlying output. Do not do any more writing after this!
      template<class T, std::size_t L>
      void VertexBufferNumeric1D_HDF5<T,L>::finalise()
      {
         dsetdata().closeDataSet();
         dsetvalid().closeDataSet();
      }
      /// @} 
  }
}

#endif

