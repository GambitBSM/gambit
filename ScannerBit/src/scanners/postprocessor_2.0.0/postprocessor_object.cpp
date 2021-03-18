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
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Logs/logger.hpp"
#include "gambit/ScannerBit/scanners/postprocessor_2.0.0/postprocessor.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/util_functions.hpp"

// Need this to allow Master process to manually check for shutdown signals without calling the likelihood container
#include "gambit/Utils/signal_handling.hpp"

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

      /// Read through any pre-existing output and reconstruct which chunks of points have already been processed
      ChunkSet get_done_points(Gambit::Printers::BaseBaseReader& resume_reader)
      {
         ChunkSet done_chunks;

         // Need to iterate through the pre-existing output and figure out what points it
         // has processed. We cannot tell what points were purposefully skipped (if the user
         // chose not to copy them into the output), but that shouldn't be a big deal since deciding
         // to skip a point doesn't cost much CPU, so we can just do it again.

         // We build up the set of "done" points as chunks.

         std::size_t previous_index = 0;
         bool building_chunk = false;
         std::size_t chunk_start;
         std::size_t chunk_end;
         while(not resume_reader.eoi()) // while not end of input
         {
            std::size_t input_index;
            bool is_valid = resume_reader.retrieve(input_index, "input_dataset_index");

            if(is_valid)
            {
               if(not building_chunk)
               {
                  // Not building a chunk, and this point is valid, so start new (will be the first) chunk
                  building_chunk = true;
                  chunk_start = input_index;
               }
               else if(input_index==(previous_index+1))
               {
                  // Point is just an increment by one, so still part of this chunk
                  // Do nothing.
               }
               else if(input_index==previous_index)
               {
                  // Reader didn't progress, error.
                  std::ostringstream err;
                  err << "'resume_reader' object returned the same value for 'input_dataset_index' twice ('"<<input_index<<"')! This means that it either didn't increment properly during this postprocessor run, or the input dataset contains the same point twice! Either case indicates a bug in the postprocessor, please report it.";
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }
               else
               {
                  // Non-incremental change in input_index! Could be higher or lower, either way, we
                  // close the previous chunk and start a new one.
                  chunk_end = previous_index;
                  done_chunks.insert(Chunk(chunk_start,chunk_end));
                  chunk_start = input_index;
               }

               previous_index = input_index;
            }

            resume_reader.get_next_point(); // Move reader to next previously processed point
         }
         // Need to close off last chunk
         if(building_chunk)
         {
            chunk_end = previous_index;
            done_chunks.insert(Chunk(chunk_start,chunk_end));
         }

         return merge_chunks(done_chunks); // Simplify the chunks and return them
      }

      /// Simplify a ChunkSet by merging chunks which overlap (or are directly adjacent).
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
              if(prev_chunk_end!=0 and it->start > prev_chunk_end+1)
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
        , total_length()
        , next_point(0)
        , chunksize()
        , done_chunks()
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
        , rank()
        #ifdef WITH_MPI
        , comm(NULL)
        #endif
        , verbose(false)
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
        , total_length(getReader().get_dataset_length())
        , next_point(0)
        , chunksize(o.chunksize)
        , done_chunks()
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
        , rank                       (o.rank                       )
        #ifdef WITH_MPI
        , comm                       (o.comm                       )
        #endif
        , verbose                    (o.verbose                    )
    {
         // Retrieve "visibile" parameter and model names
         // This will ignore parameters with fixed values in the yaml file,
         // allowing those to be input or overridden manually
         std::vector<std::string> keys = getLogLike()->getPrior().getShownParameters();

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
      int PPDriver::run_main_loop(const Chunk& mychunk)
      {
         bool quit = false; // Flag to abort 'scan' early.
         std::size_t loopi = getReader().get_current_index(); // track true index of input file
         std::size_t ppi = 0; // track number of points actually processed
         std::size_t n_passed = 0; // Number which have passed any user-specified cuts.
         bool found_chunk_start = false; // Make sure we start processing from the correct place

         //std::cout << "Chunk to process: "<<mychunk.start<<" -> "<<mychunk.end<<std::endl;

         if(mychunk.eff_length==0)
         {
            // Don't bother doing any processing for zero length chunks
            // Just check whether the calling code wants us to shut down early
            // NOTE: A trick here is that the Master process never runs the likelihood container
            // in this Master/Slave setup. So we have to manually check for the signal,
            // which is a little clumsy because I ideally wanted to leave this up to the
            // likelihood container. But doing this locks the postprocessor into using
            // the GAMBIT signal handling methods. TODO: is there another way?

            //if(verbose) logger() << LogTags::debug << LogTags::scanner << "Chunk to process has length zero! Will check for shutdown signals and then exit chunk process loop" << EOM;

            quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();
            if(not quit)
            {
               // Inelegant bit @{
               if(signaldata().check_if_shutdown_begun())
               {
                  Gambit::Scanner::Plugins::plugin_info.set_early_shutdown_in_progress();
                  quit = true;
               }
               // @}
            }

            loopi=mychunk.end; // Set loop counter to end of batch to satisfy checks at end of this function
         }
         else
         {
            PPIDpair current_point = getReader().get_current_point();
            loopi = getReader().get_current_index();

            //iif(verbose) logger() << LogTags::debug << LogTags::scanner << "Starting loop over old points ("<<total_length<<" in total)" << std::endl;
            //std::cout << "This task (rank "<<rank<<" of "<<numtasks<<"), will process iterations "<<mychunk.start<<" through to "<<mychunk.end<<", excluding any points that may have already been processed as recorded by resume data. This leaves "<<mychunk.eff_length<<" points for this rank to process."<<std::endl;

            // Disable auto-incrementing of pointID's in the likelihood container. We will set these manually.
            Gambit::Printers::auto_increment() = false;

            bool stop_loop = false;

            if(getReader().eoi())
            {
               std::cout << "Postprocessor (rank "<<rank<<") immediately reached end of input file! Skipping execution of main loop, ..."<<std::endl;
               // We should exit with the "unexpected finish" error code if this has happened.
            }

            if(verbose) logger() << LogTags::debug << LogTags::scanner << "Searching dataset for chunk ["<<mychunk.start<<" -> "<<mychunk.end<<"] (effective length "<<mychunk.eff_length<<")"<<EOM;
            ChunkSet::iterator current_done_chunk=done_chunks.begin(); // Used to skip past points that are already done
            while(not stop_loop) // while not end of input
            {
               // std::cout << "Current index: "<<getReader().get_current_index()<<std::endl;
               // std::cout << "Current loopi: "<<loopi<<std::endl;
               // std::cout << "Current printer pointID: "<<Gambit::Printers::get_point_id()<<std::endl;
               // std::cout << "eoi?: "<<getReader().eoi()<<std::endl;

               // Cancel processing of iterations beyond our assigned range
               if(loopi>mychunk.end)
               {
                  if(verbose) logger() << LogTags::debug << LogTags::scanner << "Reached the end of our batch, stopping iteration. (loopi:"<<loopi<<", mychunk.end:"<<mychunk.end<<")" << EOM;
                  loopi--; // Return counter to the last index that we actually processed.
                  break; // Exit the loop
               }

               // Send early quit signal if we unexpectedly hit the end of the input file
               if(getReader().eoi())
               {
                  if(verbose) logger() << LogTags::debug << LogTags::scanner << "Unexpectedly hit end of input file!" <<EOM;
                  quit = true;
               }

               // Inelegant signal checking. TODO: Think about how this can be shifted over to ScannerBit
               if(not quit)
               {
                  quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();
               }

               if(not quit)
               {
                  // Inelegant bit @{
                  if(signaldata().check_if_shutdown_begun())
                  {
                     Gambit::Scanner::Plugins::plugin_info.set_early_shutdown_in_progress();
                     quit = true;
                  }
                  // @}
               }

               if(not quit)
               {
                  unsigned int       MPIrank = current_point.rank;
                  unsigned long long pointID = current_point.pointID;

                  if(verbose) logger() << LogTags::debug << LogTags::scanner
                     << "Current point: "<<MPIrank<<", "<<pointID<<std::endl
                     << "Current index: "<<getReader().get_current_index()<<std::endl
                     << "Current loopi: "<<loopi<<EOM;

                  // Make sure we didn't somehow get desynchronised from the reader's internal index
                  if(loopi!=getReader().get_current_index())
                  {
                     std::ostringstream err;
                     err << "The postprocessor has become desynchronised with its assigned reader object! The postprocessor index is "<<loopi<<" but the reader index is "<<getReader().get_current_index()<<"! This indicates a bug in either the postprocessor or the reader, please report it";
                     Scanner::scan_error().raise(LOCAL_INFO,err.str());
                  }

                  // Check whether the calling code wants us to shut down early
                  quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();
                  if(quit)
                  {
                     // Need to save data about which points have been processed, so we
                     // can resume processing from here.
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Postprocessor (rank "<<rank<<") received quit signal! Aborting run." << EOM;
                     stop_loop = true;
                  }

                  // If we have moved past the end of the currently selected batch of "done"
                  // points, then select the next batch (if there are any left)
                  // if(current_done_chunk!=done_chunks.end()) std::cout << "Rank "<<rank<<": loopi="<<loopi<<", current_done_chunk=["<<current_done_chunk->start<<","<<current_done_chunk->end<<"]"<<std::endl;
                  while(current_done_chunk!=done_chunks.end() and loopi > current_done_chunk->end)
                  {
                     //std::cout<<"Rank "<<rank<<": loopi > current_done_chunk->end ("<<loopi<<" > "<<current_done_chunk->end<<"). Moving to next done chunk..."<<std::endl;
                     ++current_done_chunk;
                     //std::cout<<"Rank "<<rank<<": ...which is ["<<current_done_chunk->start<<","<<current_done_chunk->end<<"]"<<std::endl;
                  }

                  // Skip loop ahead to the batch of points we are assigned to process,
                  // and skip any points that are already processed;
                  if(loopi<mychunk.start or (current_done_chunk!=done_chunks.end() and current_done_chunk->iContain(loopi)))
                  {
                     //std::cout<<"Skipping point (not in our batch)"<<std::endl;
                     //std::cout<<"(loopi=="<<loopi<<", mychunk.start="<<mychunk.start<<", current_done_chunk.start="<<current_done_chunk->start<<", current_done_chunk.end="<<current_done_chunk->end<<")"<<std::endl;
                     current_point = getReader().get_next_point();
                     loopi++;
                     continue;
                  }

                  // Make sure that the first point we *don't* skip is the correct starting point
                  if(not found_chunk_start)
                  {
                     if(loopi==mychunk.start)
                     {
                        found_chunk_start=true;
                     }
                     else
                     {
                        std::ostringstream err;
                        err<<"The first point in this batch to be processed does not have the correct index! (mychunk.start="<<mychunk.start<<", but loopi="<<loopi<<"). This is a bug, please report it.";
                        Scanner::scan_error().raise(LOCAL_INFO,err.str());
                     }
                  }

                  if((ppi % update_interval) == 0 and ppi!=0)
                  {
                     // Progress report
                     std::cout << "Rank "<<rank<<" has processed "<<ppi<<" of "<<mychunk.eff_length<<" points ("<<100*ppi/mychunk.eff_length<<"%, with "<<100*n_passed/ppi<<"% passing all cuts)"<<std::endl;
                  }
                  ppi++; // Processing is go, update counter.

                  if(verbose) logger() << LogTags::debug << LogTags::scanner << "Found candidate point for postprocessing:"<<std::endl
                      << "  loopi = "<<loopi<<", point = ("<<current_point.rank<<", "<<current_point.pointID<<")"<<EOM;

                  // Data about current point in input file
                  if(current_point == Printers::nullpoint)
                  {
                     // No valid data here, go to next point
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Skipping point (no valid data here)"<<EOM;
                     current_point = getReader().get_next_point();
                     loopi++;
                     continue;
                  }
                  //std::cout << "Rank: "<<rank<<", Ready to process! current iteration: "<<loopi<<", current point:" << MPIrank << ", " << pointID << std::endl;

                  /// @{ Retrieve the old parameter values from previous output

                  // Storage for retrieved parameters
                  std::unordered_map<std::string, double> outputMap;

                  // Extract the model parameters
                  bool valid_modelparams = get_ModelParameters(outputMap);

                  // Check if valid model parameters were extracted. If not, something may be wrong with the input file, or we could just be at the end of a buffer (e.g. in HDF5 case). Can't tell the difference, so just skip the point and continue.
                  if(not valid_modelparams)
                  {
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Skipping point as it has no valid ModelParameters" <<EOM;
                     current_point = getReader().get_next_point();
                     loopi++;
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
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Point passed all cuts, beginning new observable/likelihood calculations"<<EOM;
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

                     // Print the index of the point in the input dataset, so that we can easily figure out later which ones
                     // were postprocessed
                     //std::cout<<"Rank "<<rank<<": Printing new data for point ("<<MPIrank<<", "<<pointID<<")"<<std::endl;
                     getPrinter().print(loopi, "input_dataset_index", MPIrank, pointID);

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
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Point outside cuts, but discard_points_outside_cuts is false, so we will copy the old data for this point. But no new calculations will be done."<<EOM;

                     /// No postprocessing to be done, but we still should copy across the modelparameters
                     /// and point ID data, since the copying routines below assume that these were taken
                     /// care of by the likelihood routine, which we never ran.
                     //std::cout<<"Rank "<<rank<<": Copying existing data for point ("<<MPIrank<<", "<<pointID<<")"<<std::endl;
                     getPrinter().print(MPIrank, "MPIrank", MPIrank, pointID);
                     getPrinter().print(pointID, "pointID", MPIrank, pointID);

                     // Print the index of the point in the input dataset, so that we can easily figure out later which ones
                     // were postprocessed
                     getPrinter().print(loopi, "input_dataset_index", MPIrank, pointID);

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
                  else
                  {
                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Skipping point (outside cuts, no data to be copied)"<<EOM;
                  }

                  /// Copy selected data from input file
                  if(not cuts_passed and discard_points_outside_cuts)
                  {
                     // Don't copy in this case, just discard the old data.
                     //std::cout<<"Rank "<<rank<<": Discarding old data for point ("<<MPIrank<<", "<<pointID<<") (didn't pass the cuts)"<<std::endl;
                  }
                  else
                  {

                     if(verbose) logger() << LogTags::debug << LogTags::scanner << "Copying old data for this point to new output file" << EOM;

                     //std::cout<<"Rank "<<rank<<": Copying existing data for point ("<<MPIrank<<", "<<pointID<<")"<<std::endl;

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

                  /// Go to next point
                  if(not stop_loop)
                  {
                     current_point = getReader().get_next_point();
                     loopi++;
                  }
               }
               else
               {
                  stop_loop = true;
               }
            }
         }

         // Check if we finished because of reaching the end of the input
         if(getReader().eoi() and loopi!=mychunk.end)
         {
            if(verbose) logger() << LogTags::debug << LogTags::scanner << "Postprocessor (rank "<<rank<<") reached the end of the input file! (debug: was this the end of our batch? (loopi="<<loopi<<", mychunk.end="<<mychunk.end<<", total_length = "<<total_length<<")"<<EOM;

            //std::cout << "Postprocessor (rank "<<rank<<") reached the end of the input file! (debug: was this the end of our batch? (loopi="<<loopi<<", mychunk.end="<<mychunk.end<<", total_length = "<<total_length<<")"<<std::endl;

         }

         // We now set the return code to inform the calling code of why we stopped.
         // 0 - Finished processing all the points we were assigned
         // 1 - Saw quit flag and so stopped prematurely
         // 2 - Encountered end of input file unexpectedly
         int exit_code = 0;
         if(quit)
         {
           exit_code = 1;
           if(verbose) logger() << LogTags::debug << LogTags::scanner << "Postprocessor (rank "<<rank<<") received quit signal! Aborting run." << EOM;
         }
         else if(getReader().eoi() and loopi!=mychunk.end)
         {
           exit_code = 2;
         }
         if(exit_code==0)
         {
            // Make sure the exit state makes sense
            if(loopi!=mychunk.end)
            {
               std::ostringstream err;
               err<<"According to the exit code, out batch is supposedly finished correctly, however the loopi counter is not equal to the proper end of our batch (loopi="<<loopi<<", mychunk.end="<<mychunk.end<<")";
               Scanner::scan_error().raise(LOCAL_INFO,err.str());
            }
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

      // Define the set of points that can be auto-skipped
      void PPDriver::set_done_chunks(const ChunkSet& in_done_chunks)
      {
         done_chunks = in_done_chunks;
      }

      /// Compute start/end indices for a given rank process, given previous "done_chunk" data.
      Chunk PPDriver::get_new_chunk()
      {
         std::size_t chunk_start = next_point;
         std::size_t chunk_end   = next_point;
         std::size_t chunk_length = 0;
         bool stop = false;
         bool found_start = false;

         if(next_point > total_length)
         {
            // Do nothing, no points left to process. Return special stop-signal chunk.
            chunk_start = 0;
            chunk_end   = 0;
         }
         else
         {
            // Build chunk to pre-set size. We select a new chunk by moving forward
            // through the dataset, but skipping points that have already been processed.
            while(not stop)
            {
               bool point_is_done = false;
               for(ChunkSet::const_iterator donechunk=done_chunks.begin();
                    donechunk!=done_chunks.end(); ++donechunk)
               {
                  // Check if the next scheduled point has been processed previously
                  if(donechunk->iContain(next_point)) point_is_done = true;
               }

               if(not point_is_done)
               {
                  chunk_length++; // Point needs to be processed, count it towards total processing length
                  if(not found_start)
                  {
                     chunk_start = next_point; // Marking the starting point if this is the first unprocessed point to be found
                     found_start = true;
                  }
               }

               if(next_point == total_length)
               {
                  // Stop early because we hit the end of the dataset
                  chunk_end = total_length;
                  stop = true;
               }
               else if(chunk_length == chunksize)
               {
                  // Chunk contains enough unprocessed points; stop adding more.
                  chunk_end = next_point;
                  stop = true;
               }
               else if(next_point > total_length)
               {
                  std::ostringstream err;
                  err << "Error generating chunk to be processed; next_point exceeds total length of dataset. Something has gone wrong for this to happen, please report this as a postprocessor bug." << std::endl;
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }
               else if(chunk_length > chunksize)
               {
                  std::ostringstream err;
                  err << "Error generating chunk to be processed; length of generated chunk exceeds allocated size. Something has gone wrong for this to happen, please report this as a postprocessor bug." << std::endl;
                  Scanner::scan_error().raise(LOCAL_INFO,err.str());
               }

               next_point++;
            }
         }

         // Return to the chunk to be processed
         //std::cout<<"chunk_start :"<<chunk_start<<std::endl;
         //std::cout<<"chunk_end   :"<<chunk_end<<std::endl;
         //std::cout<<"chunk_length:"<<chunk_length<<std::endl;
         return Chunk(chunk_start,chunk_end,chunk_length);
      }

      /// Return index of next point to be distributed for processing (mainly to track progress)
      unsigned long long PPDriver::next_point_index()
      {
         return next_point;
      }

      /// Return total length of input dataset (mainly to track progress)
      unsigned long long PPDriver::get_total_length()
      {
         return total_length;
      }


      /// @}
   }
}
