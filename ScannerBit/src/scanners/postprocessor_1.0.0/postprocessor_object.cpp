//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Helper object for the postprocessor plugin,
///  plus some auxilliary functions
///
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2016 Mar, 2017 Jan, Feb, Mar
///
///  *********************************************

#include "gambit/ScannerBit/scanners/postprocessor_1.0.0/postprocessor.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/util_functions.hpp"

using Gambit::Printers::PPIDpair;

namespace Gambit
{
   namespace PostProcessor
   {

      /// @{ Helper functions for performing resume related tasks

      /// Answer queries as to whether a given dataset index has been postprocessed in a previous run or not
      bool point_done(const ChunkSet done_chunks, size_t index)
      {
        bool answer = false;
        for(ChunkSet::const_iterator it=done_chunks.begin();
             it!=done_chunks.end(); ++it)
        {
           if(it->iContain(index))
           {
              answer = true;
              break;
           }
        }
        return answer;
      }

      /// Get 'effective' start and end positions for a processing batch
      /// i.e. simply divides up an integer into the most even parts possible
      /// over a given number of processes
      Chunk get_effective_chunk(const std::size_t total_length, const unsigned int rank, const unsigned int numtasks)
      {
         // Compute which points this process is supposed to process. Divide total
         // by number of MPI tasks.
         unsigned long long my_length = total_length / numtasks;
         unsigned long long r = total_length % numtasks;
         // Offset from beginning for this task assuming equal lengths in each task
         unsigned long long start = my_length * rank;
         // Divide up the remainder amongst the tasks and adjust offsets to account for these
         if(rank<r)
         {
           my_length++;
           start+=rank;
         }
         else
         {
           start+=r;
         }
         unsigned long long end = start + my_length - 1; // Minus 1 for the zero indexing
         return Chunk(start,end);
      }

      /// Compute start/end indices for a given rank process, given previous "done_chunk" data.
      Chunk get_my_chunk(const std::size_t dset_length, const ChunkSet& done_chunks, const int rank, const int numtasks)
      {
        /// First compute number of points left to process
        std::size_t left_to_process = 0;
        std::size_t prev_chunk_end = 0;
        bool first_chunk = true;
        for(ChunkSet::const_iterator it=done_chunks.begin();
             it!=done_chunks.end(); ++it)
        {
          // total_done_length += it->length();
          // Whoops, cannot just add lengths, because done_chunks can overlap. Need to add up the actual gaps
          // between them
           long long int gap_size = it->start;  // e.g. done_chunk starts at say '5';
           if(not first_chunk) gap_size -= (prev_chunk_end+1); // e.g. previous chunk finished at '1'; then gap_size is len(2,3,4) = 3 = 5 - 2. Unless no previous chunk, then gap_size is len(0,1,2,3,4) = 5.
           // std::cout << "Rank "<<rank<<": "<<"examining done_chunk ["<<it->start<<","<<it->end<<"]"<<std::endl;
           // std::cout << "Rank "<<rank<<": "<<"first? "<<first_chunk<<", prev_chunk_end = "<<prev_chunk_end<<std::endl;
           // std::cout << "Rank "<<rank<<": "<<"gap_size = " << gap_size <<std::endl;
           if(gap_size>0)
           {
              left_to_process += gap_size;
           }
           // Else the new done_chunk started before the previous done_chunk finished,
           // (they are ordered only based on the start index)
           // so we can skip it, or rather "merge" their lengths by just updating the
           // prev_chunk_end location if it has increased.
           if(first_chunk or it->end > prev_chunk_end)
           {
             first_chunk = false;
             prev_chunk_end = it->end;
           }
           //std::cout << "Rank "<<rank<<": "<<"left_to_process = " << left_to_process <<std::endl;
        }
        // ...and add gap from last done_chunk to the end of the dataset
        long long int last_gap_size = dset_length;
        if(not first_chunk) last_gap_size -= (prev_chunk_end+1); // e.g. dataset ends at 9 (length 10); previous chunk finished at 6; last_gap_size = len(7,8,9) = 3 = 10 - (6+1)
        //std::cout << "Rank "<<rank<<": "<<"dset_length = " << dset_length <<std::endl;
        //std::cout << "Rank "<<rank<<": "<<"last_gap_size = " << last_gap_size <<std::endl;
        if(last_gap_size>0)
        {
           left_to_process += last_gap_size;
        }
        //std::cout << "Rank "<<rank<<": "<<"left_to_process = " << left_to_process <<std::endl;
        // Done! Sanity check.
        if(left_to_process > dset_length)
        {
           std::ostringstream err;
           err << "Rank "<<rank<<" chunk calculation encountered nonsense! Computed number of points left to process ("<<left_to_process<<") is greater than the actual dataset length ("<<dset_length<<")! This is a bug in the postprocessor, please report it." <<std::endl;
           Scanner::scan_error().raise(LOCAL_INFO,err.str());
        }
        // if(rank==0) std::cout << "left_to_process = " << left_to_process;
        // Get 'effective' start/end positions for this rank; i.e. what the start index would be if the 'done' points were removed.
        Chunk eff_chunk = get_effective_chunk(left_to_process, rank, numtasks);

        // Convert effective chunk to real dataset indices (i.e. add in the 'skipped' indices)
        std::size_t count = 0;
        Chunk realchunk;
        realchunk.eff_length = eff_chunk.length(); // Record real number of points that will be processed from this chunk
        //std::cout << "Rank "<<rank<<": Converting to real dataset indices..." <<std::endl;
        prev_chunk_end = 0; // Reset
        first_chunk = true; // Reset
        bool found_start = false;
        bool found_end = false;
        //std::cout << "Rank "<<rank<<": "<<"Computing real dataset indices..." <<std::endl;
        for(ChunkSet::const_iterator it=done_chunks.begin();
             it!=done_chunks.end(); ++it)
        {
           // Need to add up the size of the gaps between chunks until we exceed the "effective" start/end positions,
           // then get the real indices by measuring back from the start of the done_chunk we are up to.
           //std::cout << "Rank "<<rank<<": Getting next done_chunk ["<<it->start<<","<<it->end<<"]"<<std::endl;
           long long int gap_size = it->start;  // e.g. done_chunk starts at say '5';
           if(not first_chunk) gap_size -= (prev_chunk_end+1); // e.g. previous chunk finished at '1'; then gap_size is len(2,3,4) = 3 = 5 - 2. Unless no previous chunk, then gap_size is len(0,1,2,3,4) = 5.
           //std::cout << "Rank "<<rank<<": "<<"examining done_chunk ["<<it->start<<","<<it->end<<"]"<<std::endl;
           //std::cout << "Rank "<<rank<<": "<<"first? "<<first_chunk<<", prev_chunk_end = "<<prev_chunk_end<<std::endl;
           //std::cout << "Rank "<<rank<<": "<<"gap_size = " << gap_size <<std::endl;
           if(gap_size>0)
           {
              count += gap_size;
              //std::cout << "Rank "<<rank<<": count = "<<count<<" (added gap of size "<<gap_size<<"; done_chunk.start="<<it->start<<" - prev_chunk_end="<<prev_chunk_end<<")"<<std::endl;
              //std::cout << "Rank "<<rank<<": "<<"count = " << count <<std::endl;
              //std::cout << "Rank "<<rank<<": "<<"eff_chunk.start = " << eff_chunk.start <<std::endl;
              if(not found_start and count > eff_chunk.start)
              {
                 std::size_t overshoot = count - eff_chunk.start; // If count is 3 and our chunk is supposed to start at the first 'not done' point (index 0), we have overshot by 3 - 0 = 3 positions.
                 realchunk.start = it->start - overshoot; // So our start point is 5 - 3 = 2
                 //std::cout << "Rank "<<rank<<": "<<"start overshoot = " << overshoot <<std::endl;
                 //std::cout << "Rank "<<rank<<": "<<"realchunk.start = " << realchunk.start <<std::endl;
                 //std::cout << "Rank "<<rank<<": found start of chunk! realchunk.start = "<<realchunk.start<<", eff_chunk.start = "<<eff_chunk.start<<", overshoot = "<<overshoot<<std::endl;
                 found_start = true;
              }
              if(not found_end and count > eff_chunk.end)
              {
                 std::size_t overshoot = count - eff_chunk.end; // Suppose our chunk should also end on the first 'not done' point (i.e. we have only one point assigned). Then we have the same calculation as above for the end.
                 realchunk.end = it->start - overshoot;
                 //std::cout << "Rank "<<rank<<": "<<"end overshoot = " << overshoot <<std::endl;
                 //std::cout << "Rank "<<rank<<": "<<"realchunk.end = " << realchunk.end <<std::endl;
                 found_end = true;
                 //std::cout << "Rank "<<rank<<": found end of chunk! realchunk.end = "<<realchunk.end<<", eff_chunk.end = "<<eff_chunk.end<<", overshoot = "<<overshoot<<std::endl;
                 break;
              }
           }
           // Else the new done_chunk started before the previous done_chunk finished,
           // (they are ordered only based on the start index)
           // so we can skip it, or rather "merge" their lengths by just updating the
           // prev_chunk_end location if it has increased.
           if(first_chunk or it->end > prev_chunk_end)
           {
             first_chunk = false;
             prev_chunk_end = it->end;
           }

           //std::cout << "Rank "<<rank<<": set prev_chunk_end to "<<prev_chunk_end<<std::endl;
        }
        // If the chunk we need to process starts or finishes after the last done chunk,
        // then we won't have found the index yet. Need to measure from the end of the
        // dataset.
        if(not found_start or not found_end)
        {
           long long int last_gap_size = dset_length;
           if(not first_chunk) last_gap_size -= (prev_chunk_end+1); // e.g. dataset ends at 9 (length 10); previous chunk finished at 6; last_gap_size = len(7,8,9) = 3 = 10 - (6+1)
           if(last_gap_size<0)
           {
              std::ostringstream err;
              err << "Rank "<<rank<<" chunk calculation encountered nonsense! Size of gap between last 'done_chunk' and the end of the dataset was computed as less than zero! ("<<last_gap_size<<" = dset_length("<<dset_length<<") - prev_chunk_end("<<prev_chunk_end<<")). This is a bug in the postprocessor, please report it." <<std::endl;
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
           }
           count += last_gap_size;
           //std::cout << "Rank "<<rank<<": count = "<<count<<" (added LAST gap of size "<<last_gap_size<<"; dset_length="<<dset_length<<" - prev_chunk_end="<<prev_chunk_end<<")"<<std::endl;
           if(not found_start)
           {
              std::size_t overshoot = count - eff_chunk.start; // ok so from above count=3, say. Suppose eff_chunk.start=0. overshoot=3
              realchunk.start = dset_length - overshoot; // Then we want to start at index 7 = 10 - 3
              //std::cout << "Rank "<<rank<<": "<<"final start overshoot = " << overshoot <<std::endl;
              //std::cout << "Rank "<<rank<<": "<<"realchunk.start = " << realchunk.start <<std::endl;
              found_start = true;
           }
           if(not found_end)
           {
              std::size_t overshoot = count - eff_chunk.end;
              realchunk.end = dset_length - overshoot;
              found_end = true;
              //std::cout << "Rank "<<rank<<": "<<"final end overshoot = " << overshoot <<std::endl;
              //std::cout << "Rank "<<rank<<": "<<"realchunk.end = " << realchunk.end <<std::endl;
           }
        }
        // Basic sanity checks
        if(realchunk.start >= dset_length)
        {
           std::ostringstream err;
           err << "Rank "<<rank<<" chunk calculation returned nonsense! Assigned start of chunk ("<<realchunk.start<<") exceeds length of dataset ("<<dset_length<<") (end of chunk was "<<realchunk.end<<"). This is a bug in the postprocessor, please report it." <<std::endl;
           Scanner::scan_error().raise(LOCAL_INFO,err.str());
        }
        if(realchunk.end >= dset_length)
        {
           std::ostringstream err;
           err << "Rank "<<rank<<" chunk calculation returned nonsense! Assigned end of chunk ("<<realchunk.end<<") exceeds length of dataset ("<<dset_length<<") (start of chunk was "<<realchunk.start<<"). This is a bug in the postprocessor, please report it." <<std::endl;
           Scanner::scan_error().raise(LOCAL_INFO,err.str());
        }
        // Final sanity checks
        // Make sure the new chunk of assigned points doesn't start or end on a "done" point!
        // Comment out for speed once debugging done
        for(ChunkSet::const_iterator it=done_chunks.begin();
             it!=done_chunks.end(); ++it)
        {
           if(   it->end==realchunk.start
              or it->end==realchunk.end
              or it->start==realchunk.start
              or it->start==realchunk.end)
           {
              std::ostringstream err;
              err << "Rank "<<rank<<" chunk calculation returned nonsense! The assigned chunk start or end point is already listed as 'done'! This is a bug in the postprocessor, please report it. Debug output:" <<std::endl;
              err << "Assigned chunk: ["<<realchunk.start << ", " <<realchunk.end<<"]"<<std::endl;
              err << "Conflicting done_chunk: ["<<it->start << ", " <<it->end<<"]"<<std::endl;
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
           }
        }
        return realchunk;
      }

      /// Read through resume data files and reconstruct which chunks of points have already been processed
      ChunkSet get_done_points(const std::string& filebase)
      {
        ChunkSet done_chunks;

        // First read collated chunk data from past resumes, and the number of processes used in the last run
        std::string inprev = filebase+"_prev.dat";

        // Check if it exists (it will not exist on the first resume)
        if(Utils::file_exists(inprev))
        {
           std::ifstream finprev(inprev);
           if(finprev)
           {
              unsigned int prev_size;
              finprev >> prev_size;
              Chunk nextchunk;
              while( finprev >> nextchunk.start >> nextchunk.end )
              {
                done_chunks.insert(nextchunk);
              }

              // Now read each of the chunk files left by each process during previous run
              for(unsigned int i=0; i<prev_size; ++i)
              {
                std::ostringstream inname;
                inname << filebase << "_" << i << ".dat";
                std::string in = inname.str();
                if(Utils::file_exists(in))
                {
                  std::ifstream fin(in);
                  if(fin)
                  {
                    fin >> nextchunk.start >> nextchunk.end;
                    done_chunks.insert(nextchunk);
                  }
                  else
                  {
                    std::ostringstream err;
                    err << "Tried to read postprocessor resume data from "<<in<<" but encountered a read error of some kind (the file seems to exist but appears to be unreadable";
                    Scanner::scan_error().raise(LOCAL_INFO,err.str());
                  }
                }
                else
                {
                  std::ostringstream err;
                  err << "Tried to read postprocessor resume data from "<<in<<" but the file does not exist or is unreadable. We require this file because according to "<<inprev<<" there were "<<prev_size<<" processes in use during the last run, and we require the resume data from all of them";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
                }
              }
           }
           else
           {
              std::ostringstream err;
              err << "Tried to read postprocessor resume data from "<<inprev<<" but encountered a read error of some kind (the file seems to exist but appears to be unreadable";
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
           }
        }
        // Else there is no resume data, assume that this is a new run started without the --restart flag.
        return merge_chunks(done_chunks); // Simplify the chunks and return them
      }

      /// Simplify a ChunkSet by merging chunks which overlap.
      ChunkSet merge_chunks(const ChunkSet& input_chunks)
      {
        ChunkSet merged_chunks;
        if(input_chunks.size()>0)
        {
           Chunk new_chunk;
           std::size_t prev_chunk_end = 0;
           new_chunk.start = input_chunks.begin()->start; // Start of first chunk
           for(ChunkSet::const_iterator it=input_chunks.begin();
                it!=input_chunks.end(); ++it)
           {
              if(prev_chunk_end!=0 and it->start > prev_chunk_end)
              {
                 // Gap detected; close the existing chunk and start a new one.
                 new_chunk.end = prev_chunk_end;
                 merged_chunks.insert(new_chunk);
                 new_chunk.start = it->start;
              }

              if(it->end > prev_chunk_end)
              {
                prev_chunk_end = it->end;
              }
           }
           // No more chunks, close the last open chunk
           new_chunk.end = prev_chunk_end;
           merged_chunks.insert(new_chunk);
           // Sanity check; Starts and ends of merged chunks should match some start/end in the input chunks
           for(ChunkSet::const_iterator it=merged_chunks.begin();
                it!=merged_chunks.end(); ++it)
           {
              bool found_start = false;
              bool found_end = false;
              for(ChunkSet::const_iterator jt=input_chunks.begin();
                   jt!=input_chunks.end(); ++jt)
              {
                if(it->start==jt->start) found_start = true;
                if(it->end==jt->end) found_end = true;
              }
              if(not found_start or not found_end)
              {
                 std::ostringstream err;
                 err << "Error, merged 'done_chunks' are not consistent with the originally input done_chunks! This indicates a bug in the merge_chunks routine of the postprocessor, please report it. Debug output:" << endl;
                 err << "Problem merged chunk was ["<<it->start<<","<<it->end<<"]"<<endl;
                 Scanner::scan_error().raise(LOCAL_INFO,err.str());
              }
              // else fine, move to next merged chunk
           }
        }
        // else there are no input chunks, just return an empty ChunkSet
        return merged_chunks;
      }

      /// Write resume data files
      /// These specify which chunks of points have been processed during this run
      void record_done_points(const ChunkSet& done_chunks, const Chunk& mydone, const std::string& filebase, unsigned int rank, unsigned int size)
      {
        if(rank == 0)
        {
          // If we are rank 0, output any old chunks from previous resumes to a special file
          // (deleting it first)
          std::string outprev = filebase+"_prev.dat";
          if( Gambit::Utils::file_exists(outprev) )
          {
            if( remove(outprev.c_str()) != 0 )
            {
              perror( ("Error deleting file "+outprev).c_str() );
              std::ostringstream err;
              err << "Unknown error removing old resume data file '"<<outprev<<"'!";
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
          }
          // else was deleted no problem
          std::ofstream foutprev(outprev);
          foutprev << size << std::endl;
          for(ChunkSet::const_iterator it=done_chunks.begin();
               it!=done_chunks.end(); ++it)
          {
            foutprev << it->start << " " << it->end << std::endl;
          }
          // check that the write succeeded
          foutprev.close();
          if (!foutprev)
          {
              std::ostringstream err;
              err << "Unknown IO error while writing resume data file '"<<outprev<<"'!";
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
          }
        }
        // Now output what we have done (could overlap with old chunks, but that doesn't really matter)
        std::ostringstream outname;
        outname << filebase << "_" << rank <<".dat";
        std::string out = outname.str();
        if( Gambit::Utils::file_exists(out) )
        {
          if( remove(out.c_str()) != 0 )
          {
            perror( ("Error deleting file "+out).c_str() );
            std::ostringstream err;
            err << "Unknown error removing old resume data file '"<<out<<"'!";
            Scanner::scan_error().raise(LOCAL_INFO,err.str());
          }
        }
        // else was deleted no problem, write new file
        std::ofstream fout(out);
        fout << mydone.start << " " << mydone.end << std::endl;
        // let's just make sure the files had no errors while closing because they are important.
        fout.close();
        if (!fout)
        {
            std::ostringstream err;
            err << "Unknown IO error while writing resume data file '"<<out<<"'!";
            Scanner::scan_error().raise(LOCAL_INFO,err.str());
        }
        // Gah, data could apparantly still be buffered by the OS and not yet written to disk
        // Apparantly on POSIX fsync can be used to ensure this happens, but I am not
        // sure if the following works. This answer on StackOverflow seems to say it doesn't?
        // http://stackoverflow.com/questions/676787/how-to-do-fsync-on-an-ofstream
        //int fd = open(filename, O_APPEND);
        //fsync(fd);
        //close(fd);
        // I may need to convert all these operations to old-school C operations
      }

      // Gather a bunch of ints from all processes (COLLECTIVE OPERATION)
      #ifdef WITH_MPI
      std::vector<int> allgather_int(int myval, GMPI::Comm& comm)
      {
          const MPI_Datatype datatype = GMPI::get_mpi_data_type<int>::type(); // datatype for ints
          int sendbuf = myval;
          std::vector<int> all_vals(comm.Get_size(),0);
          MPI_Allgather(
             &sendbuf, /* send buffer */
             1, /* send count */
             datatype, /* send datatype */
             &all_vals[0], /* recv buffer */
             1, /* recv count */
             datatype, /* recv datatype */
             *(comm.get_boundcomm()) /* communicator */
          );
          return all_vals;
      }
      #endif
      /// @}

      /// @{ PPDriver member function definitions

      /// Default constructor
      PPDriver::PPDriver()
        : reader(NULL)
        , printer(NULL)
        , LogLike()
        , new_params()
        , req_models()
        , longname()
        , all_params()
        , data_labels()
        , data_labels_copy()
        , add_to_logl()
        , subtract_from_logl()
        , renaming_scheme()
        , cut_less_than()
        , cut_greater_than()
        , discard_points_outside_cuts()
        , update_interval()
        , discard_old_logl()
        , logl_purpose_name()
        , reweighted_loglike_name()
        , root()
        , numtasks()
        , rank()
        #ifdef WITH_MPI
        , comm(NULL)
        #endif
      {}

      /// Real constructor
      PPDriver::PPDriver(
           Printers::BaseBaseReader* const r
         , Printers::BaseBasePrinter* const p
         , Scanner::like_ptr const l
         , const PPOptions& o
        )
        : reader(r)
        , printer(p)
        , LogLike(l)
        , new_params()
        , req_models()
        , longname()
        , all_params                 (o.all_params                 )
        , data_labels                (o.data_labels                )
        , data_labels_copy           (o.data_labels_copy           )
        , add_to_logl                (o.add_to_logl                )
        , subtract_from_logl         (o.subtract_from_logl         )
        , renaming_scheme            (o.renaming_scheme            )
        , cut_less_than              (o.cut_less_than              )
        , cut_greater_than           (o.cut_greater_than           )
        , discard_points_outside_cuts(o.discard_points_outside_cuts)
        , update_interval            (o.update_interval            )
        , discard_old_logl           (o.discard_old_logl           )
        , logl_purpose_name          (o.logl_purpose_name          )
        , reweighted_loglike_name    (o.reweighted_loglike_name    )
        , root                       (o.root                       )
        , numtasks                   (o.numtasks                   )
        , rank                       (o.rank                       )
        #ifdef WITH_MPI
        , comm                       (o.comm                       )
        #endif
    {
         // Retrieve parameter and model names
         std::vector<std::string> keys = getLogLike()->getPrior().getParameters(); // use to use get_keys() in the objective (prior) plugin;

         // Pull the keys apart into model-name, parameter-name pairs
         if(rank==0) std::cout << "Number of model parameters to be retrieved from previous output: "<< keys.size() <<std::endl;
         for(auto it=keys.begin(); it!=keys.end(); ++it)
         {
            if(rank==0) std::cout << "   " << *it << std::endl;
            std::vector<std::string> splitkey = Utils::delimiterSplit(*it, "::");
            std::string model = splitkey[0];
            std::string par   = splitkey[1];
            req_models[model].push_back(par);
            longname[model][par] = *it;
         }
         #ifdef WITH_MPI
         if(comm==NULL)
         {
             std::ostringstream err;
             err << "No MPI communicator supplied to postprocessor driver object! This is a bug in the postprocessor scanner plugin, please report it.";
             Scanner::scan_error().raise(LOCAL_INFO,err.str());
         }
         #endif
      }

      /// @{ Safe(-ish) accessors for pointer data
      Printers::BaseBaseReader& PPDriver::getReader()
      {
         if(reader==NULL)
         {
             std::ostringstream err;
             err << "Postprocessor tried to access reader object, but found only a NULL pointer! The postprocessor has therefore not been set up correctly, please report this bug.";
             Scanner::scan_error().raise(LOCAL_INFO,err.str());
         }
         return *reader;
      }

      Printers::BaseBasePrinter& PPDriver::getPrinter()
      {
         if(printer==NULL)
         {
             std::ostringstream err;
             err << "Postprocessor tried to access printer object, but found only a NULL pointer! The postprocessor has therefore not been set up correctly, please report this bug.";
             Scanner::scan_error().raise(LOCAL_INFO,err.str());
         }
         return *printer;
      }

      Scanner::like_ptr PPDriver::getLogLike()
      {
         // Actually it is a strange Greg-pointer, can't set it to NULL it seems.
         // if(LogLike==NULL)
         // {
         //     std::ostringstream err;
         //     err << "Postprocessor tried to access LogLike object, but found only a NULL pointer! The postprocessor has therefore not been set up correctly, please report this bug.";
         //     Scanner::scan_error().raise(LOCAL_INFO,err.str());
         // }
         return LogLike;
      }
      /// @}

      bool PPDriver::check_for_redistribution_request()
      {
         bool request_seen = false;
         #ifdef WITH_MPI
         request_seen = comm->Iprobe(MPI_ANY_SOURCE, REDIST_REQ);
         #endif
         return request_seen;
      }

      void PPDriver::send_redistribution_request()
      {
         // Inform all processes of the resynchronisation request
         #ifdef WITH_MPI
         int nullbuf = 0;
         comm->IsendToAll(&nullbuf, 0, REDIST_REQ);
         #endif
      }

      void PPDriver::clear_redistribution_requests()
      {
         // Ensure all redistribution request messages are recv'd
         #ifdef WITH_MPI
         while(check_for_redistribution_request())
         {
           int nullbuf;
           comm->Recv(&nullbuf, 1, MPI_ANY_SOURCE, REDIST_REQ);
         }
         #endif
      }

      /// Check postprocessor settings for consistency and general validity
      void PPDriver::check_settings()
      {
         new_params = all_params; // Parameters not present in the input file; to be deduced here. Start from everything and cut out those in the input file.

         if(not discard_old_logl)
         {
            if(std::find(data_labels.begin(), data_labels.end(), logl_purpose_name)
                 != data_labels.end())
            {
               std::ostringstream err;
               err << "Error starting postprocessing run! The 'purpose' name selected for the likelihood to be computed ('"<<logl_purpose_name<<"') collides with an entry in the chosen input data. Please either change the name given in the scanner option 'like', or set 'permit_discard_old_likes' to 'true' to allow the old data to be replaced in the new output.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
            if(std::find(data_labels.begin(), data_labels.end(), reweighted_loglike_name)
                 != data_labels.end())
            {
               std::ostringstream err;
               err << "Error starting postprocessing run! The label name selected for the result of likelihood weighting ('"<<reweighted_loglike_name<<"') collides with an entry in the chosen input data. Please either change the name given in the scanner option 'reweighted_like', or set 'permit_discard_old_likes' to 'true' to allow the old data to be replaced in the new output.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
         }

         /// Check if any of the output names selected in the renaming scheme are already claimed by functor output etc.
         /// Also check if the requested input label actually exists in the input dataset
         /// And check if the selected output name clashes with another input name that isn't selected for renaming
         for(std::map<std::string,std::string>::iterator it = renaming_scheme.begin(); it!=renaming_scheme.end(); ++it)
         {
            std::string in_label = it->first;
            std::string out_label = it->second;

            // Make sure input label actually exists
            if(std::find(data_labels.begin(), data_labels.end(), in_label)
                == data_labels.end())
            {
               //Whoops, could not find this label in the input data
               std::ostringstream err;
               err << "Could not find data labelled '"<<in_label<<"' in the input dataset for postprocessing! In your master YAML file you have requested this data to be relabelled to '"<<out_label<<"', however it could not be found under the specified input label.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }

            // Make sure chosen output name is not already claimed by the printer
            if(std::find(all_params.begin(), all_params.end(), out_label)
                != all_params.end())
            {
               //Whoops, name already in use by something else!
               std::ostringstream err;
               err << "Cannot rename dataset '"<<in_label<<"' to '"<<out_label<<"'! The requested output label has already been claimed by some other component in the scan. Please choose a different output label for this dataset in the master YAML file, or remove it from the 'rename' options for the postprocessor scanner plugin";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }

            // Make sure chosen output name doesn't clash with an un-renamed item to be copied
            std::set<std::string>::iterator jt = std::find(data_labels.begin(), data_labels.end(), out_label);
            if(jt != data_labels.end())
            {
               // Potential clash; check if the name is going to be changed
               std::map<std::string,std::string>::iterator kt = renaming_scheme.find(*jt);
               if(kt == renaming_scheme.end())
               {
                  // Not getting renamed! Error
                  std::ostringstream err;
                  err << "Cannot rename dataset '"<<in_label<<"' to '"<<out_label<<"'! The requested output label clashes with an item in the input dataset (which isn't getting renamed). Please choose a different output label for this dataset in the master YAML file, remove it from the 'rename' options for the postprocessor scanner plugin, or request for the conflicting input label to be renamed.";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }
               // Could still be a problem if the renamed name clashes, but we will check for that separately
            }

            // Make sure chosen output name doesn't clash with another renamed name
            for(std::map<std::string,std::string>::iterator jt = renaming_scheme.begin();
                   jt!=renaming_scheme.end(); ++jt)
            {
               if((jt->second==it->second) and (jt->first!=it->first))
               {
                  // If the out_labels match (and we aren't just clashing with ourselves)
                  // Then this is forbidden
                  std::ostringstream err;
                  err << "Cannot rename dataset '"<<in_label<<"' to '"<<out_label<<"'! The requested output label has already been claimed by some another item in the renaming scheme (you requested '"<<jt->first<<"' to also be renamed to '"<<jt->second<<"'). Please choose a different output label for one of these datasets in the master YAML file, or remove one of them from the 'rename' options for the postprocessor scanner plugin";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }
            }

            // Make sure the user isn't trying to rename a protected name (MPIrank, pointID)
            if(in_label=="MPIrank" or in_label=="pointID")
            {
               std::ostringstream err;
                  err << "Cannot rename dataset '"<<in_label<<"' to '"<<out_label<<"'! The input dataset has a special purpose so renaming it is forbidden. Please remove it from the 'rename' options for the postprocessor scanner plugin in your master YAML file.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
         }

         // Check that the cut maps refer to input datasets that actually exist
         for(std::map<std::string,double>::iterator it = cut_less_than.begin(); it!=cut_less_than.end(); ++it)
         {
            std::string in_label = it->first;
            double cut_value = it->second;

            // Make sure input label actually exists
            if(std::find(data_labels.begin(), data_labels.end(), in_label)
                == data_labels.end())
            {
               //Whoops, could not find this label in the input data
               std::ostringstream err;
               err << "Could not find data labelled '"<<in_label<<"' in the input dataset for postprocessing! In your master YAML file you have requested to only postprocess points satisfying the criteria '"<<in_label<<"' <= "<<cut_value<<", however the requested dataset for cutting could not be found under the specified input label. Please fix the label or remove this entry from the 'cut_less_than' list.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }

            // Make sure it has type 'double'
            if(getReader().get_type(in_label) != Printers::getTypeID<double>())
            {
               std::ostringstream err;
               err << "Type of input dataset '"<<in_label<<"' is not 'double'! In your master YAML file you have requested to only postprocess points satisfying the criteria '"<<in_label<<"' <= "<<cut_value<<", however the requested dataset for cutting cannot be retrieved as type 'double'. Currently cuts can only be applied to datasets stored as doubles, sorry! Please remove this entry from the 'cut_less_than' list.";
               // DEBUG
               err << std::endl << "input type ID:" << getReader().get_type(in_label) << std::endl;
               err              << "double type ID:" << Printers::getTypeID<double>() << std::endl;
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
         }
         for(std::map<std::string,double>::iterator it = cut_greater_than.begin(); it!=cut_greater_than.end(); ++it)
         {
            std::string in_label = it->first;
            double cut_value = it->second;

            // Make sure input label actually exists
            if(std::find(data_labels.begin(), data_labels.end(), in_label)
                == data_labels.end())
            {
               //Whoops, could not find this label in the input data
               std::ostringstream err;
               err << "Could not find data labelled '"<<in_label<<"' in the input dataset for postprocessing! In your master YAML file you have requested to only postprocess points satisfying the criteria '"<<in_label<<"' >= "<<cut_value<<", however the requested dataset for cutting could not be found under the specified input label. Please fix the label or remove this entry from the 'cut_greater_than' list.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }

            // Make sure it has type 'double'
            if(getReader().get_type(in_label) != Printers::getTypeID<double>())
            {
               std::ostringstream err;
               err << "Type of input dataset '"<<in_label<<"' is not 'double'! In your master YAML file you have requested to only postprocess points satisfying the criteria '"<<in_label<<"' <= "<<cut_value<<", however the requested dataset for cutting cannot be retrieved as type 'double'. Currently cuts can only be applied to datasets stored as doubles, sorry! Please remove this entry from the 'cut_greater_than' list.";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
   }


         // Check what data is to be copied and what is to be recomputed
         if(rank==0) std::cout << "Determining which data is to be copied from input file to new output file, and which will be recomputed..." <<std::endl;
         if(rank==0) std::cout << " Datasets found in input file: " << std::endl;
         for(auto it = data_labels.begin(); it!=data_labels.end(); ++it)
         {
            // Check if any parameters we plan to copy have already been registered by the
            // printer system.
            // This is actually a little tricky, since names of parameters can be modified
            // in the output depending on what printer was used. So far we have kept a certain
            // consistency that can be exploited, but it isn't enforced. Should note this somewhere
            // in the printer documentation.
            // For example, when printing ModelParameters, they have their actual parameter names
            // appended and they are output as separate datasets/columns. Likewise for vector
            // components. But this appending rule is so far consistent, so I think we can just
            // check that no prefix substring of the proposed copy has already been registered.
            // Not sure if this has a danger of observable names just by accident being prefixes of
            // some other name?
            bool is_new = true;
            for(auto jt = all_params.begin(); jt!=all_params.end(); ++jt)
            {
               if( ( (*it)==(*jt) )
                   or Gambit::Utils::startsWith(*it,(*jt)+":")
                   or Gambit::Utils::startsWith(*it,(*jt)+"[")
                   or Gambit::Utils::startsWith(*it,(*jt)+"{")
                   or Gambit::Utils::startsWith(*it,(*jt)+"%")
                   or Gambit::Utils::startsWith(*it,(*jt)+"#")
                 ) // if not [input data label] starts with [existing parameter] (plus append seperator character, for extra info like parameter name or index)
               {
                  // Then it is not new. Not allowed to copy this, the likelihood container is already printing it anew.
                  new_params.erase(*jt);
                  is_new = false;
                  break;
               }
            }

            if(is_new)
            {
               data_labels_copy.insert(*it); // Not otherwise printed; schedule for copying
               if(rank==0) std::cout << "   copy     : "<< (*it) <<std::endl;
               // Check if it is getting relabelled
               std::map<std::string,std::string>::iterator jt = renaming_scheme.find(*it);
               if(jt != renaming_scheme.end())
               {
                  // Yep, getting relabelled
                  if(rank==0) std::cout << "     to --> : "<< jt->second <<std::endl;
               }
            }
            else
            {
               if(rank==0) std::cout << "   recompute: "<< (*it) <<std::endl;
               // Check if it is getting relabelled
               std::map<std::string,std::string>::iterator jt = renaming_scheme.find(*it);
               if(jt != renaming_scheme.end())
               {
                  // Yep, getting relabelled
                  data_labels_copy.insert(*it); // Allowed to copy this after all since the name will be changed
                  if(rank==0)
                  {
                     std::cout << "     with old data copied"<<std::endl;
                     std::cout << "     to --> : "<< jt->second <<std::endl;
                  }
               }
            }
            // Check if a cut is being applied on this input dataset
            if(rank==0)
            {
               std::map<std::string,double>::iterator jt = cut_less_than.find(*it);
               if(jt != cut_less_than.end())
               {
                     std::cout << "     with cut <= "<< jt->second <<std::endl;
               }
               std::map<std::string,double>::iterator kt = cut_greater_than.find(*it);
               if(kt != cut_greater_than.end())
               {
                     std::cout << "     with cut >= "<< kt->second <<std::endl;
               }
            }
         }
         // Might as well also list what new stuff is listed for creation
         if(rank==0)
         {
           std::cout << " New datasets to be added: " << std::endl;
           for(auto it = new_params.begin(); it!=new_params.end(); ++it)
           {
              std::cout << "   " << *it << std::endl;
           }
         }
         if(rank==0) std::cout << "Copy analysis complete." <<std::endl;
         /// @}


         /// Check that we aren't accidentally throwing away any old likelihood components that we might want to keep.
         if(not discard_old_logl)
         {
            // Check if any of the likelihood components being added or subtracted from the likelihood
            // are going to be replaced in the new output. User must set 'permit_discard_old_likes" to explictly allow this.
            for(auto it=add_to_logl.begin(); it!=add_to_logl.end(); ++it)
            {
               if(std::find(all_params.begin(), all_params.end(), *it)
                    != all_params.end())
               {
                  std::ostringstream err;
                  err << "Error starting postprocessing run! One of the data entries listed in the option 'add_to_like' is scheduled to be recalculated during postprocessing ("<<*it<<"). This is permitted; the old value will be added to 'like' and then discarded and replaced by the new value, however you must explicitly permit this to occur by setting 'permit_discard_old_likes' to 'true'.";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }
            }

            for(auto it=subtract_from_logl.begin(); it!=subtract_from_logl.end(); ++it)
            {
               if(std::find(all_params.begin(), all_params.end(), *it)
                    != all_params.end())
               {
                  std::ostringstream err;
                  err << "Error starting postprocessing run! One of the data entries listed in the option 'subtract_from_like' is scheduled to be recalculated during postprocessing ("<<*it<<"). This is permitted; the old value will be subtracted from 'like' and then discarded and replaced by the new value, however you must explicitly permit this to occur by setting 'permit_discard_old_likes' to 'true'.";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }

            }
         }

      }

      /// The main run loop
      int PPDriver::run_main_loop(const ChunkSet& done_chunks)
      {
         // Compute which points this process is supposed to process. Divide up
         // by number of MPI tasks.
         if(rank==0) std::cout<<"Computing work assignments (may take a little time for very large datasets)"<<std::endl;
         unsigned long long total_length = getReader().get_dataset_length();
         Chunk mychunk = get_my_chunk(total_length, done_chunks, rank, numtasks);

         // Loop over the old points
         getReader().reset(); // Make sure we start from the beginning of the file upon redistributing work
         PPIDpair current_point = getReader().get_next_point(); // Get first point
         std::size_t loopi = 0; // track true index of input file
         std::size_t ppi = 0; // track number of points actually processed
         if(rank==0) std::cout << "Starting loop over old points ("<<total_length<<" in total)" << std::endl;
         std::cout << "This task (rank "<<rank<<" of "<<numtasks<<"), will process iterations "<<mychunk.start<<" through to "<<mychunk.end<<", excluding any points that may have already been processed as recorded by resume data. This leaves "<<mychunk.eff_length<<" points for this rank to process."<<std::endl;

         std::size_t n_passed = 0; // Number which have passed any user-specified cuts.

         // Disable auto-incrementing of pointID's in the likelihood container. We will set these manually.
         Gambit::Printers::auto_increment() = false;

         bool quit = false; // Flag to abort 'scan' early.
         bool redistribution_requested = false; // Flag to temporarily stop to redistribute remaining workload amongst MPI processes
         bool redistribution_request_ignored = false;
         bool stop_loop = false;

         if(getReader().eoi())
         {
            std::cout << "Postprocessor (rank "<<rank<<") immediately reached end of input file! Skipping execution of main loop, ..."<<std::endl;
            // We should exit with the "unexpected finish" error code if this has happened.
         }

         ChunkSet::iterator current_done_chunk=done_chunks.begin(); // Used to skip past points that are already done
         while(not getReader().eoi() and not stop_loop) // while not end of input
         {
           loopi++;
           // Make sure we didn't somehow get desynchronised from the reader's internal index
           if(loopi!=getReader().get_current_index())
           {
              std::ostringstream err;
              err << "The postprocessor has become desynchronised with its assigned reader object! The postprocessor index is "<<loopi<<" but the reader index is "<<getReader().get_current_index()<<"! This indicates a bug in either the postprocessor or the reader, please report it";
              Scanner::scan_error().raise(LOCAL_INFO,err.str());
           }

           // Cancel processing of iterations beyoud our assigned range
           if(loopi>mychunk.end)
           {
              std::cout << "Rank "<<rank<<" has reached the end of its batch, stopping iteration." << std::endl;
              loopi--; // Return counter to the last index that we actually processed.
              break;
           }

           // If we have moved past the end of the currently selected batch of "done"
           // points, then select the next batch (if there are any left)
           //if(current_done_chunk!=done_chunks.end()) std::cout << "Rank "<<rank<<": loopi="<<loopi<<", current_done_chunk=["<<current_done_chunk->start<<","<<current_done_chunk->end<<"]"<<std::endl;
           if(current_done_chunk!=done_chunks.end() and loopi > current_done_chunk->end)
           {
              ++current_done_chunk;
           }

           // Skip loop ahead to the batch of points we are assigned to process,
           // and skip any points that are already processed;
           if(loopi<mychunk.start or (current_done_chunk!=done_chunks.end() and current_done_chunk->iContain(loopi)))
           {
              current_point = getReader().get_next_point();
              continue;
           }

           if((ppi % update_interval) == 0 and ppi!=0)
           {
              // Progress report
              std::cout << "Rank "<<rank<<" has processed "<<ppi<<" of "<<mychunk.eff_length<<" points ("<<100*ppi/mychunk.eff_length<<"%, with "<<100*n_passed/ppi<<"% passing all cuts)"<<std::endl;
           }
           ppi++; // Processing is go, update counter.

           // Data about current point in input file
           if(current_point == Printers::nullpoint)
           {
              // No valid data here, go to next point
              current_point = getReader().get_next_point();
              continue;
           }
           unsigned int       MPIrank = current_point.rank;
           unsigned long long pointID = current_point.pointID;
           //std::cout << "Rank: "<<rank<<", current iteration: "<<loopi<<", current point:" << MPIrank << ", " << pointID << std::endl;

           /// @{ Retrieve the old parameter values from previous output

           // Storage for retrieved parameters
           std::unordered_map<std::string, double> outputMap;

           // Extract the model parameters
           bool valid_modelparams = get_ModelParameters(outputMap);

           // Check if valid model parameters were extracted. If not, something may be wrong with the input file, or we could just be at the end of a buffer (e.g. in HDF5 case). Can't tell the difference, so just skip the point and continue.
           if(not valid_modelparams)
           {
              std::cout << "Skipping point "<<loopi<<" as it has no valid ModelParameters" <<std::endl;
              current_point = getReader().get_next_point();
              continue;
           }

           /// @}

           // Determine if model point passes the user-requested cuts
           // This is a little tricky because we don't know the type of the input dataset.
           // For now we will restrict the system so that it only works for datasets with
           // type 'double' (which is most stuff). We check for this earlier, so here we
           // can just assume that the requested datasets have the correct type.

           bool cuts_passed = true; // Will be set to false if any cut is failed, or a required entry is invalid
           for(std::map<std::string,double>::iterator it = cut_less_than.begin();
                it!=cut_less_than.end(); ++it)
           {
             if(cuts_passed)
             {
               std::string in_label = it->first;
               double cut_value = it->second;
               double buffer;
               bool valid = getReader().retrieve(buffer, in_label);
               if(valid)
               {
                  cuts_passed = (buffer <= cut_value);
               }
               else
               {
                  cuts_passed = false;
               }
             }
           }

           for(std::map<std::string,double>::iterator it = cut_greater_than.begin();
                it!=cut_greater_than.end(); ++it)
           {
             if(cuts_passed)
             {
               std::string in_label = it->first;
               double cut_value = it->second;
               double buffer;
               bool valid = getReader().retrieve(buffer, in_label);
               if(valid)
               {
                  cuts_passed = (buffer >= cut_value);
               }
               else
               {
                  cuts_passed = false;
               }
             }
           }

           if(cuts_passed) // Else skip new calculations and go straight to copying old results
           {
              n_passed += 1; // Counter for number of points which have passed all the cuts.
              // Before calling the likelihood function, we need to set up the printer to
              // output correctly. The auto-incrementing of pointID's cannot be used,
              // because we need to match the old scan results. So we must set it manually.
              // This is currently a little clunky but it works. Make sure to have turned
              // off auto incrementing (see above).
              // The printer should still print to files split according to the actual rank, this
              // should only change the assigned pointID pair tag. Which should already be
              // properly unambiguous if the original scan was done properly.
              // Note: This might fail for merged datasets from separate runs. Not sure what the solution
              // for that is.
              getLogLike()->setRank(MPIrank); // For purposes of printing only
              getLogLike()->setPtID(pointID);


              // We feed the unit hypercube and/or transformed parameter map into the likelihood container. ScannerBit
              // interprets the map values as post-transformation and not apply a prior to those, and ensures that the
              // length of the cube plus number of transformed parameters adds up to the total number of parameter.
              double new_logL = getLogLike()(outputMap); // Here we supply *only* the map; no parameters to transform.

              // Add old likelihood components as requested in the inifile
              if (not add_to_logl.empty() or not subtract_from_logl.empty())
              {

                double combined_logL = new_logL;
                bool is_valid(true);

                for(auto it=add_to_logl.begin(); it!=add_to_logl.end(); ++it)
                {
                    std::string old_logl = *it;
                    if(std::find(data_labels.begin(), data_labels.end(), old_logl)
                        == data_labels.end())
                    {
                       std::ostringstream err;
                       err << "In the input YAML file, you requested to 'add_to_like' the component '"<<old_logl<<"' from your input data file, however this does not match any of the data labels retrieved from the input data file you specified. Please check the spelling, path, etc. and try again.";
                       Scanner::scan_error().raise(LOCAL_INFO,err.str());
                    }
                    if(getReader().get_type(*it) != Gambit::Printers::getTypeID<double>())
                    {
                       std::ostringstream err;
                       err << "In the input YAML file, you requested 'add_to_like' component '"<<old_logl<<"' from your input data file, however this data cannot be retrieved as type 'double', therefore it cannot be used as a likelihood component. Please enter a different data label and try again.";
                       Scanner::scan_error().raise(LOCAL_INFO,err.str());
                    }

                    double old_logl_value;
                    is_valid = is_valid and getReader().retrieve(old_logl_value, old_logl);
                    if(is_valid)
                    {
                       // Combine with the new logL component
                       combined_logL += old_logl_value;
                    }
                    // Else old likelihood value didn't exist for this point; cannot combine with non-existent likelihood, so don't print the reweighted value.
                }

                // Now do the same thing for the components we want to subtract.
                for(auto it=subtract_from_logl.begin(); it!=subtract_from_logl.end(); ++it)
                {
                    std::string old_logl = *it;
                    if(std::find(data_labels.begin(), data_labels.end(), old_logl)
                        == data_labels.end())
                    {
                       std::ostringstream err;
                       err << "In the input YAML file, you requested to 'subtract_from_like' the component '"<<old_logl<<"' from your input data file, however this does not match any of the data labels retrieved from the input data file you specified. Please check the spelling, path, etc. and try again.";
                       Scanner::scan_error().raise(LOCAL_INFO,err.str());
                    }
                    if(getReader().get_type(*it) != Gambit::Printers::getTypeID<double>())
                    {
                       std::ostringstream err;
                       err << "In the input YAML file, you requested 'subtract_from_like' component '"<<old_logl<<"' from your input data file, however this data cannot be retrieved as type 'double', therefore it cannot be used as a likelihood component. Please enter a different data label and try again.";
                       Scanner::scan_error().raise(LOCAL_INFO,err.str());
                    }

                    double old_logl_value;
                    is_valid = is_valid and getReader().retrieve(old_logl_value, old_logl);
                    if(is_valid)
                    {
                       // Combine with the new logL component, subtracting this time
                       combined_logL -= old_logl_value;
                    }
                    // Else old likelihood value didn't exist for this point; cannot combine with non-existent likelihood, so don't print the reweighted value.
                }

                // Output the new reweighted likelihood (if all components were valid)
                if(is_valid) getPrinter().print(combined_logL, reweighted_loglike_name, MPIrank, pointID);

              }

              ///  In the future would be nice if observables could be reconstructed from the
              ///  output file, but that is a big job, need to automatically create functors
              ///  for them which provide the capabilities they are supposed to correspond to,
              ///  which is possible since this information is stored in the labels, but
              ///  would take quite a bit of setting up I think...
              ///  Would need the reader to provide virtual functions for retrieving all the
              ///  observable metadata from the output files.
              ///
              ///  UPDATE: TODO: What happens in case of invalid point? Does this copying etc. just get skipped?
              ///  Or do I need to check that the output LogL was valid somehow?
              ///  Answer: Loglike function just returns a default low value in that case, scanner plugins do
              ///  not see the invalid point exceptions, they are caught inside the likelihood container.
           }
           else if(not discard_points_outside_cuts)
           {
              /// No postprocessing to be done, but we still should copy across the modelparameters
              /// and point ID data, since the copying routines below assume that these were taken
              /// care of by the likelihood routine, which we never ran.
              getPrinter().print(MPIrank, "MPIrank", MPIrank, pointID);
              getPrinter().print(pointID, "pointID", MPIrank, pointID);
              // Now the modelparameters
              for(auto it=req_models.begin(); it!=req_models.end(); ++it)
              {
                ModelParameters modelparameters;
                std::string model = it->first;
                bool is_valid = getReader().retrieve(modelparameters, model);
                if(is_valid)
                {
                   // Use the OutputName set by the reader to preserve the original naming of the modelparameters.
                   getPrinter().print(modelparameters, modelparameters.getOutputName(), MPIrank, pointID);
                }
              }
           }

           /// Copy selected data from input file
           if(not cuts_passed and discard_points_outside_cuts)
           {
              // Don't copy in this case, just discard the old data.
           }
           else
           {
              for(std::set<std::string>::iterator it = data_labels_copy.begin(); it!=data_labels_copy.end(); ++it)
              {
                 // Check if this input label has been mapped to a different output label.
                 std::string in_label = *it;
                 std::map<std::string,std::string>::iterator jt = renaming_scheme.find(in_label);
                 if(jt != renaming_scheme.end())
                 {
                    // Found match! Do the renaming
                    std::string out_label = jt->second;
                    //std::cout << "Copying data from "<<in_label<<", to output name "<<out_label<<", for point ("<<MPIrank<<", "<<pointID<<")" <<std::endl;
                    getReader().retrieve_and_print(in_label,out_label,getPrinter(), MPIrank, pointID);
                 }
                 else
                 {
                    // No match, keep the old name
                    //std::cout << "Copying data from "<<in_label<<" for point ("<<MPIrank<<", "<<pointID<<")" <<std::endl;
                    getReader().retrieve_and_print(in_label,getPrinter(), MPIrank, pointID);
                 }
              }
           }

           // Check whether the calling code wants us to shut down early
           quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();

           // Check whether some other process wants us to stop and redistribute the
           // processing workload
           if(not redistribution_request_ignored)
           {
             redistribution_requested = check_for_redistribution_request();
             //if(not redistribution_requested) std::cout << "Rank "<<rank<<": Still looping, no redistribution request seen." << std::endl;
           }

           if(quit)
           {
              // Need to save data about which points have been processed, so we
              // can resume processing from here.
              //std::cout << "Postprocessor (rank "<<rank<<") received quit signal! Aborting run." << std::endl;
              stop_loop = true;
           }
           else if(redistribution_requested)
           {
              //std::cout << "Postprocessor (rank "<<rank<<") received redistribution request!" << std::endl;
              // Decide if we are going to stop for the redistribution. Don't bother if we
              // only have a small number of points left to process.
              std::size_t points_left = mychunk.eff_length - ppi;

              // How many points should we use as a threshold? It depends on how long they
              // take to evaluate and how many cpus are available. For now we will pick something
              // fairly simply. If there are less than 10 points left, or if there were less than
              // 100 points to start with, then we won't bother redistributing
              if(points_left > 10 and mychunk.eff_length > 100) // Make an option to vary this?
              {
                 stop_loop = true;
              }
              else
              {
                 // Just ignore the request and finish our batch normally.
                 //std::cout << "Postprocessor (rank "<<rank<<") ...but we have less than 10 points left so we will finish them first." << std::endl;
                 redistribution_requested = false;
                 redistribution_request_ignored = true; // deactivate the request.
              }
           }

           /// Go to next point
           if(not stop_loop) current_point = getReader().get_next_point();
         }

         // Check if we finished because of reaching the end of the input
         if(getReader().eoi() and loopi!=mychunk.end)
         {
            std::cout << "Postprocessor (rank "<<rank<<") reached the end of the input file! (debug: was this the end of our batch? (loopi="<<loopi<<", mychunk.end="<<mychunk.end<<", dset_length = "<<getReader().get_dataset_length()<<")"<<std::endl;
         }

         // Write resume data (even if we finished; other processes might not have)
         //std::cout<<"Writing resume data (rank "<<rank<<")...."<< std::endl;
         Chunk mydonechunk(mychunk.start,loopi);
         record_done_points(done_chunks, mydonechunk, root, rank, numtasks);

         // We now set the return code to inform the calling code of why we stopped.
         // 0 - Finished processing all the points we were assigned
         // 1 - Saw quit flag and so stopped prematurely
         // 2 - Was told to stop by some other process for redistribution of postprocessing work
         // 3 - Encountered end of input file unexpectedly
         int exit_code = 0;
         if(quit)
         {
           exit_code = 1;
         }
         else if(redistribution_requested) // and if we obeyed it; if we ignored it then some other exit code is returned
         {
           exit_code = 2;
         }
         else if(getReader().eoi() and loopi!=mychunk.end)
         {
           exit_code = 3;
         }
         return exit_code;
      }

      // Extract model parameters from the reader
      bool PPDriver::get_ModelParameters(std::unordered_map<std::string, double>& outputMap)
      {
         bool valid_modelparams = true;
         for(auto it=req_models.begin(); it!=req_models.end(); ++it)
         {

           ModelParameters modelparameters;
           std::string model = it->first;
           bool is_valid = getReader().retrieve(modelparameters, model);
           if(not is_valid)
           {
              valid_modelparams = false;
              //std::cout << "ModelParameters marked 'invalid' for model "<<model<<"; point will be skipped." << std::endl;
           }
           /// @{ Debugging; show what was actually retrieved from the output file
           //std::cout << "Retrieved parameters for model '"<<model<<"' at point:" << std::endl;
           //std::cout << " ("<<MPIrank<<", "<<pointID<<")  (rank,pointID)" << std::endl;
           //const std::vector<std::string> names = modelparameters.getKeys();
           //for(std::vector<std::string>::const_iterator
           //    kt = names.begin();
           //    kt!= names.end(); ++kt)
           //{
           //  std::cout << "    " << *kt << " : " << modelparameters[*kt] << std::endl;
           //}
           /// @}

           // Check that all the required parameters were retrieved
           // Could actually do this in the constructor for the scanner plugin, would be better, but a little more complicated. TODO: do this later.
           std::vector<std::string> req_pars = it->second;
           std::vector<std::string> retrieved_pars = modelparameters.getKeys();
           for(auto jt = req_pars.begin(); jt != req_pars.end(); ++jt)
           {
             std::string par = *jt;
             if(std::find(retrieved_pars.begin(), retrieved_pars.end(), par)
                 == retrieved_pars.end())
             {
                std::ostringstream err;
                err << "Error! Reader could not retrieve the required paramater '"<<par<<"' for the model '"<<model<<"' from the supplied data file! Please check that this parameter indeed exists in that file." << std::endl;
                Scanner::scan_error().raise(LOCAL_INFO,err.str());
             }

             // If it was found, add it to the return map
             outputMap[ longname[model][par] ] = modelparameters[par];
           }
         }
         return valid_modelparams;
      }

      /// @}
   }
}
