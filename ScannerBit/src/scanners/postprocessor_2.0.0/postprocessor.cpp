//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  "Postprocessing" scanner plugin. Reads points
///  from old scan output and re-runs a likelihood
///  containing plugin for those same point.
///  Can perform some simple addition/subtraction
///  operations of likelihood components from
///  the new plugin output.
///
///  This is version 2 of the postproccessor; it
///  distributes the postprocessing workload by
///  a completely different algorithm to version 1.
///  This version employs a master/worker model,
///  with the master processes distributing points
///  in batches to the worker processes on request.
///  Batch size can be set via options (use batch
///  size of 1 for very slow likelihoods, use
///  large batch size for very fast likelihoods).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018, Sep
///
///  *********************************************

// STL
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

// GAMBIT
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"
#include "gambit/ScannerBit/scanners/postprocessor_2.0.0/postprocessor.hpp"
#include "gambit/ScannerBit/objective_plugin.hpp"
#include "gambit/ScannerBit/scanner_plugin.hpp"

using namespace Gambit;
using namespace Gambit::PostProcessor;


// The reweighter Scanner plugin
scanner_plugin(postprocessor, version(2, 0, 0))
{
  reqd_inifile_entries("like","reader");

  /// The likelihood container plugin
  like_ptr LogLike;

  /// MPI data
  int numtasks;
  int rank;

  #ifdef WITH_MPI
    /// Tag for messages
    const int request_work_tag=10;
  #endif

  /// The reader object in use for the scan
  Gambit::Printers::BaseBaseReader* reader;

  /// The main postprocessing driver object
  PPDriver driver;

  /// Options for PPDriver;
  PPOptions settings;

  /// Allow extra log output for this process (need to restrict master process since it loops a lot)
  bool this_rank_verbose;
  
  // Retrieve an integer from an environment variable
  int getintenv(const std::string& name)
  {
     int x = 0;
     if(const char* env_p = std::getenv(name.c_str()))
     {
       std::stringstream env_s(env_p);
       env_s >> x;
       if (!env_s)
       {
          std::ostringstream err;
          err << "Tried to retrieve value of environment variable "<<name<<" as an integer, but conversion failed! String retrieved was '"<<env_s.str()<<"'";
          scan_error().raise(LOCAL_INFO,err.str());
       }
     }
     else
     {
       std::ostringstream err;
       err << "Tried to retrieve value of environment variable "<<name<<" as an integer, but it does not seem to be defined!";
       scan_error().raise(LOCAL_INFO,err.str());
     }
     return x;
  }

  /// The constructor to run when the plugin is loaded.
  plugin_constructor
  {
    int s_numtasks;
    int s_rank;

    // Get MPI data. No communication is needed, we just need to know how to
    // split up the workload. Just a straight division among all processes is
    // used, nothing fancy.
    #ifdef WITH_MPI
      MPI_Comm_size(MPI_COMM_WORLD, &s_numtasks); // MPI requires unsigned ints here, so we'll just convert afterwards
      MPI_Comm_rank(MPI_COMM_WORLD, &s_rank);
    #else
      s_numtasks = 1;
      s_rank = 0;
    #endif
      numtasks = s_numtasks;
    rank = s_rank;

    if(rank==0) std::cout << "Initialising 'postprocessor' plugin for ScannerBit..." << std::endl;

    // Get options for setting up the reader (these live in the inifile under:
    // Scanners:
    //  scanners:
    //    scannername:
    //      reader
    Gambit::Options reader_options = get_inifile_node("reader");

    // Initialise reader object
    get_printer().new_reader("old_points",reader_options);

    // Retrieve the reader object
    reader = get_printer().get_reader("old_points");

    // Get names of all the output data labels
    settings.data_labels = reader->get_all_labels();

    // Set up other options for the plugin
    settings.verbose = get_inifile_value<bool>("verbose_logging", true); // They are all marked as 'debug', so need debug: true in the yaml file. But can turn them off by setting verbose_logging: false.
    settings.update_interval = get_inifile_value<std::size_t>("update_interval", 1000);
    settings.add_to_logl = get_inifile_value<std::vector<std::string>>("add_to_like", std::vector<std::string>());
    settings.subtract_from_logl = get_inifile_value<std::vector<std::string>>("subtract_from_like", std::vector<std::string>());
    settings.reweighted_loglike_name = get_inifile_value<std::string>("reweighted_like");

    settings.renaming_scheme = get_inifile_value<std::map<std::string,std::string>>("rename",
                          std::map<std::string,std::string>());

    settings.cut_less_than = get_inifile_value<std::map<std::string,double>>("cut_less_than",
                          std::map<std::string,double>());

    settings.cut_greater_than = get_inifile_value<std::map<std::string,double>>("cut_greater_than",
                          std::map<std::string,double>());

    settings.discard_points_outside_cuts = get_inifile_value<bool>("discard_points_outside_cuts", false);

    // Use virtual rank system?
    if(get_inifile_value<bool>("use_virtual_rank",false))
    {
        #ifdef WITH_MPI
          if(numtasks>1)
          {
            std::ostringstream err;
            err << "You have set the 'use_virtual_rank' option for the postprocessor scanner plugin to 'true', which will allow the plugin to act as if it is part of an MPI ensemble when it really isn't, however you are also running this task in an MPI batch with size > 1! You cannot use the virtual rank system at the same time as running a real MPI job! Please choose one configuration or the other and rerun the job.";
            scan_error().raise(LOCAL_INFO,err.str());
          }
        #endif
        rank     = getintenv("RANK");
        numtasks = getintenv("SIZE");
        if(rank>=numtasks)
        {
          std::ostringstream err;
          err << "Environment variable RANK was larger than permitted by SIZE ("<<numtasks<<">="<<rank<<") while running postprocessor scanner plugin with 'use_virtual_rank=true' option. This is not a valid MPI configuration, so it is an illegal choice of virtual configuration.";
          scan_error().raise(LOCAL_INFO,err.str());
        }
    }
    // Transfer MPI variables to PPOptions
    settings.rank = rank;
    settings.numtasks = numtasks;

    // Set rank-specific verbosity
    if(((rank==0 and numtasks==1) or (rank!=0 and numtasks>1)) and settings.verbose) this_rank_verbose=true;

    // Size of chunks to be distributed to worker processes
    settings.chunksize = get_inifile_value<std::size_t>("batch_size",1);

    // Finally, there is the 'Purpose' value of the likelihood container. This may well clash
    // with the old name used in the input file, so better check for this and make the user
    // change their choice if so.
    settings.logl_purpose_name = get_inifile_value<std::string>("like");
    settings.discard_old_logl = get_inifile_value<bool>("permit_discard_old_likes",false);

    // Retrieve the external likelihood calculator
    LogLike = get_purpose(settings.logl_purpose_name);

    // Do not allow GAMBIT's own likelihood calculator to directly shut down the scan.
    // This scanner plugin will assume responsibility for this process, triggered externally by
    // the 'plugin_info.early_shutdown_in_progress()' function.
    LogLike->disable_external_shutdown();

    // Do not allow recording of timing information
    // Currently we cannot tell what the names will be for this, and they may
    // collide with previous timing data in a way that we cannot presently
    // predict. So for now it is just not allowed to record timing data whilst
    // using the postprocessor
    if(get_inifile_value<bool>("print_timing_data"))
    {
        std::ostringstream err;
        err<<"Detected 'print_timing_data: true' in master YAML file. At present this option is not compatible with\
 the postprocessor, sorry! Please set 'print_timing_data: false' and try again"<<std::endl;
        Scanner::scan_error().raise(LOCAL_INFO,err.str());
    }

  }

  /// Main run function
  int plugin_main()
  {
    if(rank==0) std::cout << "Running 'postprocessor' plugin for ScannerBit." << std::endl;

    // Set up our MPI communicator
    #ifdef WITH_MPI
    GMPI::Comm ppComm;
    ppComm.dup(MPI_COMM_WORLD,"PostprocessorComm"); // duplicates MPI_COMM_WORLD
    // Message tag definitons in PPDriver class:
    #endif

    /// Determine what data needs to be copied from the input file to the new output dataset
    // Get labels of functors listed for printing from the primary printer.
    settings.all_params = get_printer().get_stream()->getPrintList();
    // There are some extra items that will also be automatically printed in all scans,
    // so we need to avoid copying those:
    settings.all_params.insert("unitCubeParameters"); // It would be better to keep the originals here, but currently cannot turn off the printing from within like_ptr.
    settings.all_params.insert("MPIrank"); // These should be re-printed the same as they were anyway
    settings.all_params.insert("pointID");
    settings.all_params.insert(settings.logl_purpose_name); // If there is a name clash and the run was not aborted, we are to discard the old data under this name.
    settings.all_params.insert("Modified" + settings.logl_purpose_name);
    settings.all_params.insert(settings.reweighted_loglike_name); //   "  "
    #ifdef WITH_MPI
    settings.comm = &ppComm;
    #endif

    // Construct the main driver object
    driver = PPDriver(reader,get_printer().get_stream(),LogLike,settings);

    // Check that the supplied settings make sense
    driver.check_settings();

    // Points which have already been processed in a previous (aborted) run
    ChunkSet done_chunks; // Empty by default

    // Ask the printer if this is a resumed run or not
    bool resume = get_printer().resume_mode();

    // Vector to record which processes have been told by the master to stop.
    // Master cannot stop until all other processes have stopped.
    std::vector<bool> process_has_stopped(numtasks); // For end of run

    // Rank 0 needs to figure out which points are already processesed (if resuming)
    std::cout << "PP resume flag? "<<resume<<std::endl;
    if(resume)
    {
        if(rank==0)
        {
            std::stringstream ss;
            ss << "Analysing previous output to determine remaining postprocessing work (may take a little time for large datasets)...";
            std::cout << ss.str() << std::endl;
            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << ss.str() << EOM; 

           
            // Set up reader object for temporary output file, if one exists

            //Gambit::Options resume_reader_options = get_inifile_node("resume_reader");
            //get_printer().new_reader("done_points",resume_reader_options);

            // Create reader object for previous output, if it exists.
            // There is a special function for this
            // Resume reader is always called "resume".
            get_printer().create_resume_reader();
            Gambit::Printers::BaseBaseReader* resume_reader = get_printer().get_reader("resume");
            done_chunks = get_done_points(*resume_reader);

            // Delete the reader object
            get_printer().delete_reader("resume"); 
            ss.clear();
            ss << "Distributing information about remaining work to all processes..."; 
            std::cout << ss.str() << std::endl;;
            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << ss.str() << EOM; 
        }

        #ifdef WITH_MPI
        if(numtasks>1)
        {
            // Need to distribute these to all processes
            // It is a bit hard to distribute them in one message, so we will do it
            // one chunk at a time. Hopefully this isn't a big deal in terms of the
            // delivery times. TODO: review this if startup is too slow.

            // First tell all processes how many chunks to expect
            std::vector<std::size_t> num_chunks_buf(1);
            if(rank==0) num_chunks_buf.push_back(done_chunks.size());
            ppComm.Bcast(num_chunks_buf, 1, 0); // Broadcast to all workers from master
            std::size_t num_chunks = num_chunks_buf.at(0);

            ChunkSet::iterator chunk=done_chunks.begin();
            for(std::size_t i=0; i<num_chunks; i++)
            {
                std::vector<std::size_t> chunkdata(3); // Raw form of chunk information
                if(rank==0)
                {
                   if(chunk!=done_chunks.end())
                   {
                      chunkdata[0] = chunk->start;
                      chunkdata[1] = chunk->end;
                      chunkdata[2] = chunk->eff_length;
                      chunk++;
                   }
                   else
                   {
                      std::ostringstream err;
                      err << "Iterated past end of done_chunks!";
                      scan_error().raise(LOCAL_INFO,err.str());
                   }
                }

                ppComm.Bcast(chunkdata, 3, 0); // Broadcast to all workers from master

                if(rank!=0)
                {
                   Chunk newchunk;
                   newchunk.start      = chunkdata[0];
                   newchunk.end        = chunkdata[1];
                   newchunk.eff_length = chunkdata[2];
                   done_chunks.insert(newchunk);
                }
            }
        }
        #endif

        // I think the above broadcast should be blocking, but lets do a barrier here to make sure no strange writing occurs before
        // this resume analysis is complete
        #ifdef WITH_MPI
        ppComm.Barrier();
        #endif

        if(rank==0)
        {
            std::stringstream ss;
            ss << "Postprocessing resume analysis completed.";
            std::cout << ss.str() << std::endl;
            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << ss.str() << EOM; 
        }

        if(settings.verbose) 
        {
            logger() << LogTags::debug << LogTags::scanner << "Rank "<<rank<<" believes that the following chunks have already been processed:"<<std::endl;
            for(auto chunk=done_chunks.begin(); chunk!=done_chunks.end(); ++chunk)
            {
               logger() << "   "<<chunk->start<<" -> "<<chunk->end<<std::endl;
            }
            logger() << EOM; 
        }
        // DEBUG
        //std::cout << "Rank "<<rank<<" believes that the following chunks have already been processed:"<<std::endl;
        //for(auto chunk=done_chunks.begin(); chunk!=done_chunks.end(); ++chunk)
        //{
        //   std::cout << "   "<<chunk->start<<" -> "<<chunk->end<<std::endl;
        //}
    }

    // Tell the driver routine what points it can automatically skip
    driver.set_done_chunks(done_chunks);

    //MAIN LOOP HERE
    bool continue_processing = true;
    bool quit_flag_seen = false;
    unsigned long long ri = 0; // Counter for reporting intervals

    while(continue_processing)
    {
       Chunk mychunk; // Work to be performed this loop

       //Too verbose; removing messages that would totally spam logs
       if(this_rank_verbose) logger() << LogTags::debug << LogTags::scanner << "In main postprocessor chunk processing loop. Chunk to process is ["<<mychunk.start<<" -> "<<mychunk.end<<"]." << EOM;  

       #ifdef WITH_MPI
         if(rank==0 and numtasks==1)
         {
            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Rank zero task is only task; retrieving new chunk for ourselves to process" << EOM;
            // Compute new work for this one process.
            mychunk = driver.get_new_chunk();
         }
         else if(rank==0)
         { 
            //if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Master process checking for work requests from other processes..." << EOM;
            // Master checks for work requests from other processes
            for(int worker=1; worker<numtasks; worker++)
            {
               bool needs_work = ppComm.Iprobe(worker, request_work_tag);
               if(needs_work)
               {
                  // Receive the work request message (no information, just cleaning up)
                  int quit_flag = 0; // The message itself propagates quit flags, if seen by workers
                  if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Worker on rank "<<worker<<" has no more work. Receiving message to determined whether to send more work or quit." << EOM;
 
                  ppComm.Recv(&quit_flag,1,worker,request_work_tag);

                  if(quit_flag==1)
                  {
                     quit_flag_seen = true;
                  }

                  Chunk newchunk;
                  if(quit_flag_seen)
                  {
                     // Send stop signal to worker
                     newchunk = stopchunk;
                     if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Worked on rank "<<worker<<" sent us the quit signal! Assigning it a stopchunk to trigger shutdown." << EOM;  
                  }
                  else
                  {
                     // Compute new work assignment
                     newchunk = driver.get_new_chunk();
                  }

                  if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Sending chunk ["<<newchunk.start<<"->"<<newchunk.end<<"] (effective length "<<newchunk.eff_length<<") to task "<<worker<<" for processing." << EOM;  
 
                  // Send work assignment
                  std::size_t chunkdata[3]; // Raw form of chunk information
                  chunkdata[0] = newchunk.start;
                  chunkdata[1] = newchunk.end;
                  chunkdata[2] = newchunk.eff_length;
                  ppComm.Send(&chunkdata, 3, worker, request_work_tag);

                  // Check if we just sent the 'stop' signal.
                  if(newchunk==stopchunk)
                  {
                     process_has_stopped[worker] = true;
                     if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Stop signal sent to worker "<<worker<< EOM;   
                  }
               }
            }

            // Set zero-length chunk for master
            bool any_still_running=false;
            //if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Checking if worker processes are still running:"<<std::endl;  
            for(int i=1; i<numtasks; i++)
            {
               if(process_has_stopped[i]==false) 
               {
                  any_still_running=true;
                  //logger() << LogTags::debug << LogTags::scanner << "   Worker "<<i<<" is still running"<<std::endl;
               }
               else
               {
                  //logger() << LogTags::debug << LogTags::scanner << "   Worker "<<i<<" has stopped"<<std::endl;
               }
            }

            if(any_still_running)
            {
               mychunk = Chunk(1,1,0); // Zero-length chunk; master doesn't process anything, but need to continue looping
               //if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Some workers are still running, so master needs to continue looping." << EOM;  
            }
            else
            {
               // Everyone has been told to stop! So now master should stop too.
               mychunk = stopchunk;
               if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "All processes have been told to stop. Triggering shutdown of master process." << EOM;  
            }
         }
         else
         {
            // Worker processes request more work from master
            int quit_flag = 0; // Use this message to propagate quit flag, if it has been seen
            if(quit_flag_seen) quit_flag = 1;

            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Worker "<<rank<<" is sending a work request message to master process (quit_flag="<<quit_flag<<")"<< EOM;  
 
            ppComm.Send(&quit_flag,1,0,request_work_tag);

            // Receive the work assignment
            std::size_t chunkdata[3]; // Raw form of chunk information
            ppComm.Recv(&chunkdata,3,0,request_work_tag);

            // Check if any work in the work assignment
            // If start and end are both zero then take this as the signal that
            // we are finished
            mychunk.start      = chunkdata[0];
            mychunk.end        = chunkdata[1];
            mychunk.eff_length = chunkdata[2];

            if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Received new work from master: ["<<mychunk.start<<" -> "<<mychunk.end<<"] (effective size = "<<mychunk.eff_length<<")"<<EOM; 
         }
       #else
       // Compute new work for this one process.
       if(quit_flag_seen)
       {
          // Send stop signal
          mychunk = stopchunk;
       }
       else
       {
          mychunk = driver.get_new_chunk();
       }
       #endif


       if(this_rank_verbose) logger() << LogTags::debug << LogTags::scanner << "Rank "<<rank<<": Chunk to process is ["<<mychunk.start<<", "<<mychunk.end<<"; eff_len="<<mychunk.eff_length<<"]"<<EOM;

       if((rank==0 and numtasks==1) or (rank!=0 and numtasks>1))
       {
          //std::cout << "Rank "<<rank<<": Chunk to process is ["<<mychunk.start<<", "<<mychunk.end<<"; eff_len="<<mychunk.eff_length<<"]"<<std::endl;
       }


       // Progress report
       unsigned long long npi = driver.next_point_index();
       unsigned long long this_ri = npi / settings.update_interval;
       if(this_ri > ri)
       {
          // Issue progress report if we have crossed into a new reporting interval
          std::stringstream ss;
          ss << npi <<" of "<<driver.get_total_length()<<" points ("
                    <<100*npi/driver.get_total_length()<<"%) have been distributed for processing";
          std::cout<<ss.str()<<std::endl;
          if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << ss.str() << EOM;
          ri = this_ri;
       }

       if(mychunk==stopchunk)
       {
          // Finished! (or was told to stop via quit flag)
          continue_processing = false;
       }

       if(mychunk.start > mychunk.end)
       {
          // End after start, error!
          std::ostringstream err;
          err << "Work assignment for rank "<<rank
              <<" process is invalid! Chunk end ("<<mychunk.end
              <<") is before the chunk start ("<<mychunk.start
              <<")! ended due to encountering the end of the input file."
              <<" This indicates a bug in the postprocessor (or some "
              <<"bizarre corruption of the MPI message). Please report"
              <<"this.";
          std::cerr << err.str() << std::endl;
          scan_error().raise(LOCAL_INFO,err.str());
       }

       int exit_code;
       if(continue_processing)
       {
          // 0 - Finished processing all the points we were assigned
          // 1 - Saw quit flag and so stopped prematurely
          // 2 - Encountered end of input file unexpectedly
          exit_code = driver.run_main_loop(mychunk);
          if(this_rank_verbose) logger() << LogTags::debug << LogTags::scanner << "Rank "<<rank<<": exited loop with code "<<exit_code<<EOM;
       }
       else
       {
          if(quit_flag_seen)
          {
             exit_code=1;
          }
          else
          {
             // No points assigned, in shutdown mode
             exit_code=0;
          }
       }

       if(exit_code==0)
       {
          if(this_rank_verbose) logger() << LogTags::debug << LogTags::scanner << "Rank "<<rank<<" has finished processing its batch." << EOM;
       }
       else if(exit_code==1)
       {
          // Saw quit flag. Should be stopping, but we need to continue
          // until the master process explicitly tells us to stop.
          // So do nothing until "continue_processing" flag gets set to false.
          quit_flag_seen = true;
          if(settings.verbose) logger() << LogTags::debug << LogTags::scanner << "Quit flag seen, but haven't yet been told by master process to stop. Will continue processing loop." << EOM;  
          if(rank==0 and numtasks==1)
          {
             // If we are the only process then just stop.
             continue_processing = false;
          }
       }
       else if(exit_code==2)
       {
          // That shouldn't happen; warning
          std::ostringstream err;
          err << "Postprocessing on "<<rank<<" ended due to encountering the end of the input file. This indicates that it was told to process more points than existed in the input file, which indicates a bug in the postprocessor. Your output may still be fine, but please report this bug.";
          std::cerr << err.str() << std::endl;
          scan_error().raise(LOCAL_INFO,err.str());
       }
       else
       {
          std::ostringstream err;
          err << "Postprocessing on "<<rank<<" terminated with an unrecognised return code ("<<exit_code<<"). This indicates a bug in the postprocessor, please report it.";
          scan_error().raise(LOCAL_INFO,err.str());
       }

    }
    std::cout << "Rank "<< rank<< ": Done!" << std::endl;

    // Test barrier to see if everyone made it
    #ifdef WITH_MPI
    ppComm.Barrier();
    if(rank==0) std::cout << "Passed final PP barrier" << std::endl;
    #endif
    return 0;
  }
}
