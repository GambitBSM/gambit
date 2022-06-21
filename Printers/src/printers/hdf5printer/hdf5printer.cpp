//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 interface printer class member function definitions
///
///
///  Design strategy:
///
///  Gambit operates in an iterative fashion, collecting likelihood samples in a
///  multidimensional space. Along with the likelihoods, we also want to store
///  other information collected at each parameter space point. Naively the results
///  of this search could be stored in a record array, however Gambit operates at
///  too high a level to determine the type information necessary to define the
///  type of the record we want to store in any given scan.
///
///  To solve this problem, while maintaining the ability to store a wide variety
///  of types, the Gambit HDF5 interface is implemented with the following strategy:
///
///   - Every vertex ID becomes associated with its own, independent, HDF5 dataset,
///     whose type is suited to that vertex (i.e. Gambit functor). This also means
///     that vertices are permitted to have variable-length arrays as their record
///     type (useful for perhaps storing event data of some kind). It is better
///     for later analysis to store the data this way anyway, since one almost
///     always wants one or two or several "columns" of data at a time, rather than
///     every column (complete record) for several parameter points. We effectively
///     store each "column" separately, which makes retrieval of just one "column"
///     very fast.
///
///   - Each dataset contains a boolean field which indicates whether a record has
///     been filled or not (some points fail to produce results in all functors).
///
///   - When the scanner moves to a new point, all the datasets have an entry added
///     (via their individual buffers). The boolean flag is set to zero
///     (indicating no result) if no result was provided before this. This keeps
///     all the datasets synchronised, so that e.g. record 5 in all datasets refers
///     to the same parameter space point.
///
///   - The rank 0 process handles all dataset access, which allows it to keep the
///     datasets synchronised even when point information is coming in from several
///     points at once.
///
///   -- To elaborate on the above two points further:
///      - the MPI handling is a little tricky here. Every type needs to know how to
///        serialise itself for transmission to the rank 0 process. Each process can
///        keep a series of buffers (instead of the actual datasets) synchronised
///        by the above method, and when they are full this can trigger the MPI send.
///      - The MPI receive must happen when the rank 0 process knows that it has
///        completed one of its own points, so that a clean write to all the datasets
///        can occur.
///
///  In order to handle the auxilliary printers, i.e. the case where extra information
///  about points is added after the scan has moved on, the following strategy is used:
///
///   - The auxilliary printers communicate with the main printer, to let it know what
///     information will appear in the future. The main printer then creates datasets
///     for this future information, and keeps them (and their boolean flags) in
///     lockstep with all the other datasets.
///
///   - When the auxilliary printer decides that it wants to print its information, a
///     lookup is done in the datasets containing the pointID and rank information, to
///     figure out which absolute index the auxilliary data belongs to. The pre-existing
///     dataset created by the main printer is then updated accordingly. It might not
///     be possible to allow variable length arrays for this auxilliary data.
///
///   - It may occur that the above lookup fails, because the auxilliary data has been
///     computed for a point which hasn't yet been delivered to the rank 0 process (i.e.
///     the main printer data is still in the buffer of another process). In this case
///     the auxilliary data will remain in a buffer (with its associated pointID and rank)
///     and the lookup will be attempted again at a later stage (unless the auxilliary
///     printer signals that the auxilliary data is going to be completely overwritten, in
///     which case the buffer is simply erased).
///
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


// Standard libraries
#include <map>
#include <vector>
#include <algorithm>
#include <ios>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> // For popen in finalise()
#include <chrono>

// Gambit
#include "gambit/Printers/printers/hdf5printer.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5_combine_tools.hpp"
#include "gambit/Printers/printer_id_tools.hpp"

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Logs/logger.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"

// Switch for debugging output (manual at the moment)

#ifdef DEBUG_MODE
#define DBUG(x) x
#else
#define DBUG(x)
#endif

//#define CHECK_SYNC

// Debugging for 'finalise' routine
#define FINAL_CHECK_SYNC
#define FINAL_DEBUG_MODE

// Code!
namespace Gambit
{
  namespace Printers
  {

    // Locally defined helper struct
    struct DSetData
    {
      // Input data for HDF5 helper functions
      int rank;

      // Dataset metadata
      std::vector<std::string> names;
      std::vector<unsigned long> lengths;

      /// Need to analyse this in a more "streaming" way, otherwise too big and slow
      // // Contents of pointID and mpirank datasets
      // std::vector<unsigned long> pointIDs;
      // std::vector<int> pointIDs_isvalid;
      // std::vector<unsigned int> mpiranks;
      // std::vector<int> mpiranks_isvalid;

      // Report error
      std::string local_info;
      std::string errmsg;

      DSetData(int r) : rank(r) {}
    };

    // Helper function to check for GAMBIT shutdown messages due to errors in other processes
    void check_for_error_messages()
    {
      signaldata().check_if_shutdown_begun(); // Will throw a shutdown exception if an emergency shutdown command is received via MPI
    }

    // Helper function for examining existing HDF5 file during verification stage
    // Finds the highest PPID for our rank
    // (separate function checks datasets for consistent lengths; that should run first)

    // Note; resumed runs may use different numbers of processes to the initial run.
    // But this should be no problem; if there are new processes added, the highest
    // previous PPID number for those ranks is just zero. If there are fewer, then
    // there will be still be matching old-process ranks for all of the new ranks.
    //PPIDpair
    std::map<unsigned long, unsigned long long int> HDF5Printer::get_highest_PPID_from_HDF5(hid_t group_id)
    {
       //unsigned long long int highest_pointID = 0; // Highest ID found so far
       std::map<unsigned long, unsigned long long int> highest_pointIDs;

       // Chunking variables
       static const std::size_t CHUNKLENGTH = 1000; // Should be a reasonable value

       // Interfaces for the datasets
       // Make sure the types used here don't get out of sync with the types used to write the original datasets
       // We open the datasets in "resume" mode to access existing dataset, and make "const" to disable writing of new data. i.e. "Read-only" mode.
       const DataSetInterfaceScalar<unsigned long long, CHUNKLENGTH> pointIDs(group_id, "pointID", true, 'r');
       const DataSetInterfaceScalar<int, CHUNKLENGTH> pointIDs_isvalid  (group_id, "pointID_isvalid", true, 'r');
       const DataSetInterfaceScalar<int, CHUNKLENGTH> mpiranks          (group_id, "MPIrank", true, 'r');
       const DataSetInterfaceScalar<int, CHUNKLENGTH> mpiranks_isvalid  (group_id, "MPIrank_isvalid", true, 'r');

       // Error check lengths. This should already have been done for all datasets in the group, but
       // we will double-check these four here.
       const std::size_t dset_length  = pointIDs.dset_length();
       const std::size_t dset_length2 = pointIDs_isvalid.dset_length();
       const std::size_t dset_length3 = mpiranks.dset_length();
       const std::size_t dset_length4 = mpiranks_isvalid.dset_length();
       if( (dset_length  != dset_length2)
        or (dset_length3 != dset_length4)
        or (dset_length  != dset_length3) )
       {
         std::ostringstream errmsg;
         errmsg << "Error retrieving highest PPID from previous dataset! Unequal dataset lengths detected in pointID and MPIrank datasets:" <<std::endl;
         errmsg << "  pointIDs.dset_length()         = " << dset_length << std::endl;
         errmsg << "  pointIDs_isvalid.dset_length() = " << dset_length2 << std::endl;
         errmsg << "  mpiranks.dset_length()         = " << dset_length3 << std::endl;
         errmsg << "  mpiranks_isvalid.dset_length() = " << dset_length4 << std::endl;
         errmsg << "This indicates either a bug in the HDF5printer or corruption of the datasets (possibly due to unsafe shutdown).";
         printer_error().raise(LOCAL_INFO, errmsg.str());
       }

       // Compute number of chunks
       const std::size_t NCHUNKS = dset_length / CHUNKLENGTH; // Number of FULL chunks
       const std::size_t REMAINDER = dset_length - (NCHUNKS*CHUNKLENGTH); // leftover after last full chunk

       std::size_t NCHUNKIT; // Number of chunk iterations to perform
       if(REMAINDER==0) { NCHUNKIT = NCHUNKS; }
       else             { NCHUNKIT = NCHUNKS+1; } // Need an extra iteration to deal with incomplete chunk

       logger()<<"Begining iteration through existing HDF5 output for rank "<<getRank()<<", searching for previous highest pointID."<<EOM;

       // Iterate through dataset in chunks
       for(std::size_t i=0; i<NCHUNKIT; ++i)
       {
          std::size_t offset = i*CHUNKLENGTH;
          std::size_t length;

          if(i==NCHUNKS){ length = REMAINDER; }
          else          { length = CHUNKLENGTH; }

          logger()<<"rank "<<getRank()<<": chunk "<<i<<": reading entries "<<offset<<" to "<<offset+length<<"."<<EOM;

          const std::vector<unsigned long long> pID_chunk = pointIDs.get_chunk(offset,length);
          const std::vector<int> pIDvalid_chunk  = pointIDs_isvalid.get_chunk(offset,length);
          const std::vector<int> rank_chunk      =         mpiranks.get_chunk(offset,length);
          const std::vector<int> rankvalid_chunk = mpiranks_isvalid.get_chunk(offset,length);

          // Check that retrieved lengths make sense
          if (pID_chunk.size() != CHUNKLENGTH)
          {
            if(not (i==NCHUNKS and pID_chunk.size()==REMAINDER) )
            {
              std::ostringstream errmsg;
              errmsg << "Error retrieving highest PPID from previous dataset! Size of chunk vector retrieved from pointID dataset ("<<pID_chunk.size()<<") does not match CHUNKLENGTH ("<<CHUNKLENGTH<<"), nor the expected remainder for the last chunk ("<<REMAINDER<<"). This probably indicates a bug in the DataSetInterfaceScalar.get_chunk routine, please report it. Error occurred while reading chunk i="<<i<<std::endl;
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
          if( (pID_chunk.size() != pIDvalid_chunk.size())
           or (rank_chunk.size() != rankvalid_chunk.size())
           or (pID_chunk.size() != rank_chunk.size()) )
          {
            std::ostringstream errmsg;
            errmsg << "Error retrieving highest PPID from previous dataset! Unequal chunk lengths retrieved while iterating through in pointID and MPIrank datasets:" <<std::endl;
            errmsg << "  pID_chunk.size()      = " << pID_chunk.size() << std::endl;
            errmsg << "  pIDvalid_chunk.size() = " << pIDvalid_chunk.size() << std::endl;
            errmsg << "  rank_chunk.size()     = " << rank_chunk.size() << std::endl;
            errmsg << "  rankvalid_chunk.size()= " << rankvalid_chunk.size() << std::endl;
            errmsg << "  CHUNKLENGTH           = " << CHUNKLENGTH << std::endl;
            errmsg << "This indicates either a bug in the HDF5printer or corruption of the datasets (possibly due to unsafe shutdown). Error occurred while reading chunk i="<<i<<std::endl;
            printer_error().raise(LOCAL_INFO, errmsg.str());
          }

          // Iterate within the chunk
          for(std::size_t j=0; j<length; ++j)
          {
            //Check validity flags agree
            if(pIDvalid_chunk[j] != rankvalid_chunk[j])
            {
              std::ostringstream errmsg;
              errmsg << "Error retrieving highest PPID from previous dataset! Incompatible validity flags detected in pointID_isvalid and MPIrank_isvalid datasets at position j="<<j<<" in chunk i="<<i<<"(with CHUNKLENGTH="<<CHUNKLENGTH<<"). Specifically:"<<std::endl;
              errmsg << "  pIDvalid_chunk[j]  = " << pIDvalid_chunk[j] << std::endl;
              errmsg << "  rankvalid_chunk[j] = " << rankvalid_chunk[j] << std::endl;
              errmsg << "This most likely indicates a bug in the HDF5printer, but could indicate corruption of the datasets (possibly due to unsafe shutdown). Please report it.";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            //std::cerr<<"rank "<<getRank()<<":    Entry (valid="<<pIDvalid_chunk[j]<<"): rank="<<rank_chunk[j]<<" , pointID="<<pID_chunk[j]<<std::endl;

            // Continue only if entry is marked as "valid" and corresponds to our rank
            if(rankvalid_chunk[j])// and rank_chunk[j]==getRank())
            {
              // Test the pointID for this point to see if it is the highest so far.
              if(pID_chunk[j] > highest_pointIDs[rank_chunk[j]])
              {
                highest_pointIDs[rank_chunk[j]] = pID_chunk[j];
                //std::cerr<<"rank "<<getRank()<<": new highest pointID found = "<<highest_pointID<<std::endl;
              }
            }
            // else continue iteration
          }
       }

       // Return the highest ID found (-1 if none)
       return highest_pointIDs; //PPIDpair(highest_pointID,getRank());
    }

    // We are going to have to combine this data with information from the
    // scanners (using the auxilliary printers). In order to do this efficiently,
    // we will store the pointIDs and ranks in a dataset seperate from the
    // bulk of the data (but correlated with it) so that we can quickly search
    // for records by their pointID and rank, and then write new data to them.
    //
    // NOTE: will have to change the auxilliary printers a bit, so that they
    // communicate what they intend to write back to the main printer... or something.


    /// @{ HDF5Printer member functions

    // Constructor
    HDF5Printer::HDF5Printer(const Options& options, BasePrinter* const primary)
    : BasePrinter(primary,options.getValueOrDef<bool>(false,"auxilliary"))
    , lastPointID(nullpoint)
    , printer_name("Primary printer")
    , myRank(0)
    , mpiSize(1)
#ifdef WITH_MPI
    , myComm() // initially attaches to MPI_COMM_WORLD
#endif
    {
      common_constructor(options);
    }

    // Get options required to construct a reader object that can read
    // the previous output of this printer.
    Options HDF5Printer::resume_reader_options()
    {
      Options options;
      // Set options that we need later to construct a reader object for
      // previous output, if required.
      options.setValue("type", "hdf5");
      options.setValue("file", tmp_comb_file);
      options.setValue("group", group);
      return options;
    }

    void HDF5Printer::common_constructor(const Options& options)
    {
#ifdef WITH_MPI
      // Note; here 'myRank' is the REAL mpi rank. Used
      // for process-specific actions.
      // the inherited 'getRank' function should be used for
      // printing "as if" this process is from that rank,
      // i.e. mostly just for setting point ID codes.
      // 'myRank' will not change, but getRank() may be
      // changed by the scanner (e.g. postprocessor).
      myRank = myComm.Get_rank();
      this->setRank(myRank);
#endif

      // Disable output combination routines?
      disable_combine_routines = options.getValueOrDef<bool>(false,"disable_combine_routines");

      if(not this->is_auxilliary_printer())
      {
        // Set up this printer in primary mode
        DBUG( std::cout << "Constructing Primary HDF5Printer object..." << std::endl; )
        is_primary_printer = true;

        set_resume(options.getValue<bool>("resume"));

        // Set up communicator context for HDF5 printer system
#ifdef WITH_MPI
        myComm.dup(MPI_COMM_WORLD,"HDF5printerComm"); // duplicates MPI_COMM_WORLD
        mpiSize = myComm.Get_size();
#endif

        std::ostringstream ss;
        ss << "Primary printer for rank " << myRank;
        printer_name = ss.str();

        // Name of file where results should ultimately end up
        std::ostringstream ff;
        if(options.hasKey("output_path"))
        {
          ff << options.getValue<std::string>("output_path") << "/";
        }
        else
        {
          ff << options.getValue<std::string>("default_output_path") << "/";
        }
        if(options.hasKey("output_file"))
        {
          ff << options.getValue<std::string>("output_file");
        }
        else
        {
          printer_error().raise(LOCAL_INFO, "No 'output_file' entry specified in the options section of the Printer category of the input YAML file. Please add a name there for the output hdf5 file of the scan.");
        }
        finalfile = ff.str();

        // Name of file where combined results from previous (unfinished) runs end up
        std::ostringstream rename;
        rename << finalfile << "_temp_combined";
        tmp_comb_file = rename.str();

        // HDF5 group (virtual "folder") inside output file in which to store datasets
        group = options.getValueOrDef<std::string>("/","group");

        // Delete final target file (or group) if one with same name already exists? (and if we are restarting the run)
        // This is just for convenience during testing; by default datasets will simply be replaced in/added to
        // existing target HDF5 files. This lets one combine data from many scans into one file if desired.
        bool overwrite_file  = options.getValueOrDef<bool>(false,"delete_file_on_restart");

        std::vector<unsigned long long int> highests(mpiSize);

        if(myRank==0)
        {
          // Check whether a readable output file exists with the name that we want to use.
          std::string msg_finalfile;
          #ifdef DEBUG_MODE
            std::cout << "File readable: " << finalfile << " : " << HDF5::checkFileReadable(finalfile, msg_finalfile) <<std::endl;
          #endif
          if(HDF5::checkFileReadable(finalfile, msg_finalfile))
          {
            if(overwrite_file and not get_resume())
            {
              // Note: "not resume" means "start or restart"
              // Delete existing output file
              std::ostringstream command;
              command << "rm -f "<<finalfile;
              logger() << LogTags::printers << LogTags::info << "Running shell command: " << command.str() << EOM;
              FILE* fp = popen(command.str().c_str(), "r");
              if(fp==NULL)
              {
                // Error running popen
                std::ostringstream errmsg;
                errmsg << "rank "<<myRank<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<finalfile<<")! popen failed to run the command (command was '"<<command.str()<<"')";
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }
              else if(pclose(fp)!=0)
              {
                // Command returned exit code!=0, or pclose failed
                std::ostringstream errmsg;
                errmsg << "rank "<<myRank<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<finalfile<<")! Shell command failed to executed successfully, see stderr (command was '"<<command.str()<<"').";
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }
            }
            else
            {
              // File exists, so check if 'group' is readable, and throw error if it exists
              file_id = HDF5::openFile(finalfile);
              std::string msg_group;
              std::cout << "Group readable: " << finalfile << " , " << group << " : " << HDF5::checkGroupReadable(file_id, group, msg_group) << std::endl;
              if(HDF5::checkGroupReadable(file_id, group, msg_group))
              {
                // Group already exists, error!
                std::ostringstream errmsg;
                errmsg << "Error preparing pre-existing output file '"<<finalfile<<"' for writing via hdf5printer! The requested output group '"<<group<<" already exists in this file! Please take one of the following actions:"<<std::endl;
                errmsg << "  1. Choose a new group via the 'group' option in the Printer section of your input YAML file;"<<std::endl;
                errmsg << "  2. Delete the existing group from '"<<finalfile<<"';"<<std::endl;
                errmsg << "  3. Delete the existing output file, or set 'delete_file_on_restart: true' in your input YAML file to give GAMBIT permission to automatically delete it (applies when -r/--restart flag used);"<<std::endl;
                errmsg << std::endl;
                errmsg << "*** Note: This error most commonly occurs when you try to resume a scan that has already finished! ***" <<std::endl;
                errmsg << std::endl;
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }
              HDF5::closeFile(file_id);
              exit(1);
            }
          }

          // Deal with temporary files from previous runs
          if(get_resume()) // If in resume mode, need to combine any existing process-level temporary files
          {
            logger() << LogTags::info << "Checking if temporary files from a previous scan exist" << EOM;
            std::vector<std::string> tmp_files = find_temporary_files(true); //error if they are inconsistent
            if(tmp_files.size()!=0)
            {
              logger() << LogTags::info << "Found "<<tmp_files.size()<<" temporary files from previous scan; preparing to combine them" << EOM;

              // This might take a while; for debugging purposes we will time it.
              std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());
              prepare_and_combine_tmp_files();
              std::chrono::time_point<std::chrono::system_clock> end(std::chrono::system_clock::now());
              std::chrono::duration<double> time_taken = end - start;
              logger() << LogTags::info << "HDF5 files from previous scan combined successfully. Operation took "<<std::chrono::duration_cast<std::chrono::seconds>(time_taken).count()<<" seconds." << EOM;
            }
            else
            {
              logger() << LogTags::info << "No process-level temporary files found; skipping combination step." << EOM;
              if(not HDF5::checkFileReadable(tmp_comb_file))
              {
                // There is no combined output either, so disable resume mode
                std::ostringstream msg;
                msg<<"No temporary output from a previous scan found (or it is unreadable); this will be treated as a NEW scan";
                std::cout<<msg.str()<<std::endl;
                logger() << LogTags::info << msg.str();
                set_resume(false);
              }
            }
          }
          else // If we are not in resume mode, need to delete any temporary files left lying around in our target directory from previous incomplete runs
          {
            // If everything is ok, delete any existing temporary files, including temporary combined files
            std::vector<std::string> tmp_files = find_temporary_files();
            tmp_files.push_back(tmp_comb_file); // Adds temporary combined file to deletion list
            for(auto it=tmp_files.begin(); it!=tmp_files.end(); ++it)
            {
              std::ostringstream command;
              command << "rm -f "<<*it;
              logger() << LogTags::printers << LogTags::info << "Running shell command: " << command.str() << EOM;
              FILE* fp = popen(command.str().c_str(), "r");
              if(fp==NULL)
              {
                // Error running popen
                std::ostringstream errmsg;
                errmsg << "rank "<<myRank<<": Error deleting old temporary output file (attempting to do this because '--restart' flag was detected. Target for deletion was "<<*it<<")! popen failed to run the command (command was '"<<command.str()<<"')";
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }
              else if(pclose(fp)!=0)
              {
                // Command returned exit code!=0, or pclose failed
                std::ostringstream errmsg;
                errmsg << "rank "<<myRank<<": Error deleting old temporary output file (attempting to do this because '--restart' flag was detected. Target for deletion was "<<*it<<")! Shell command failed to execute successfully, please check stderr (command was '"<<command.str()<<"').";
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }
            }
          } // end if(resume)

          std::cout <<"Rank "<<myRank<<" resume flag? "<<get_resume()<<std::endl;
          if(get_resume())
          {
            //long highest = 0;
            /// Check if combined output file exists
            std::cout <<"Rank "<<myRank<<": tmp_comb_file readable? "<<HDF5::checkFileReadable(tmp_comb_file)<<"(filename: "<<tmp_comb_file<<")"<<std::endl;
            if( HDF5::checkFileReadable(tmp_comb_file) )
            {
              logger() << LogTags::info << "Scanning existing temporary combined output file, to prepare for adding new data" << EOM;
            // Open HDF5 file
              file_id = HDF5::openFile(tmp_comb_file);

              // Check that group is readable
              std::string msg2;
              if(not HDF5::checkGroupReadable(file_id, group, msg2))
              {
                // We are supposed to be resuming, but specified group was not readable in the output file, so we can't.
                std::ostringstream errmsg;
                errmsg << "Error! GAMBIT is in resume mode, however the chosen output system (HDF5Printer) was unable to open the specified group ("<<group<<") within the existing output file ("<<tmp_comb_file<<"). Resuming is therefore not possible; aborting run... (see below for IO error message)";
                errmsg << std::endl << "(Strictly speaking we could allow the run to continue (if the scanner can find its necessary output files from the last run), however the printer output from that run is gone, so most likely the scan needs to start again).";
                errmsg << std::endl << "IO error message: " << msg2;
                printer_error().raise(LOCAL_INFO, errmsg.str());
              }

              // Open requested group (creating it plus parents if needed)
              group_id = HDF5::openGroup(file_id,group);

              // Get previous highest pointID for our rank from the existing output file
              // Might take a while, so time it.
              std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());
              //PPIDpair highest_PPID
              std::map<unsigned long, unsigned long long int> highest_PPIDs = get_highest_PPID_from_HDF5(group_id);
              std::chrono::time_point<std::chrono::system_clock> end(std::chrono::system_clock::now());
              std::chrono::duration<double> time_taken = end - start;

              for (size_t rank = 0; rank < mpiSize; rank++ )
              {
                  auto it = highest_PPIDs.find(rank);
                  if (it != highest_PPIDs.end())
                      highests[rank] = it->second;
                  else
                      highests[rank] = 0;
              }
              //highest = highest_PPID.pointID;

              logger() << LogTags::info << "Extracted highest pointID calculated on rank "<<myRank<<" process during previous scan (it was "<< highests <<") from combined output. Operation took "<<std::chrono::duration_cast<std::chrono::seconds>(time_taken).count()<<" seconds." << EOM;

              // Cleanup
              HDF5::closeGroup(group_id);
              HDF5::closeFile(file_id);
            }
            else
            {
              logger() << LogTags::info << "No temporary combined output file found; therefore no previous MPIrank/pointID pairs to parse. Will assume that this is a new run (since -r/--restart flag was not used)." << EOM;
            }

            // Use global function get_point_id to fast-forward ScannerBit to the
            // next unused pointID for this rank (actually we give it the highest known, it will iterate itself)
            //get_point_id() = highest;
          }
        }

#ifdef WITH_MPI
        std::vector<int> resume_int_buf(1);
        resume_int_buf[0] = get_resume();
        myComm.Barrier();
        myComm.Bcast(resume_int_buf, 1, 0);
        set_resume(resume_int_buf.at(0));

        if (get_resume())
        {
            unsigned long long int highest;
            myComm.Barrier();
            myComm.Scatter(highests, highest, 0);
            get_point_id() = highest;
        }
#else
        if (get_resume())
        {
            get_point_id() = highests[0];
        }
#endif

        /*if(myRank==0)
        {
#ifdef WITH_MPI
          // Everyone wait until the master finishes pre-processing of existing files
          // Calls 'check_for_error_messages' function while waiting, in case master fails to process the files.
          myComm.allWaitForMasterWithFunc(PPFILES_PASS, check_for_error_messages);
#endif
        }*/

        // Specify temporary output file name to use for this process
        // Will combine with data from other processes when run is finished,
        // or when resuming a run.
        // TODO: Currently we have to do this even if no MPI is being used. Might just leave this for simplicity.
        std::ostringstream rename2;
        rename2 << finalfile << "_temp_" << myRank;
        tmpfile = rename2.str();

        // Open requested file
        bool oldfile;
        Utils::ensure_path_exists(tmpfile);
        file_id = HDF5::openFile(tmpfile,false,oldfile,'w'); // Don't overwrite existing file; we will check here if it exists (via oldfile) and throw an error if it does.
        if(oldfile)
        {
          std::ostringstream errmsg;
          errmsg << "Error! HDF5Printer attempted to open a temporary file for storing output data ("<<tmpfile<<"), however it found an existing file of the same name! This is a bug; pre-existing temporary files should already have been analysed and deleted before this point in the code.";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Open requested group (creating it plus parents if needed)
        group_id = HDF5::openGroup(file_id,group);

        // Open sub-group for RA datasets
        RA_group_id = HDF5::openGroup(file_id,group+"/RA");

        // Set the target dataset write location to the chosen group
        location_id = group_id;
        RA_location_id = RA_group_id;

      }
      else
      {
        // Set up this printer in auxilliary mode
        std::ostringstream ss;
        ss << options.getValue<std::string>("name");
#ifdef WITH_MPI
        ss << " for rank " << myRank;
#endif
        printer_name = ss.str();
        synchronised = options.getValueOrDef<bool>(true,"synchronised");
        DBUG( std::cout << "Constructing Auxilliary HDF5Printer object (with name=\""<<printer_name<<"\" synchronised="<<synchronised<<")..." << std::endl; )

        primary_printer = dynamic_cast<HDF5Printer*>(this->get_primary_printer());

        // Set resume flag to match primary printer
        set_resume(primary_printer->get_resume());

        // Fix up mpi communicator (need to copy the one created by the
        // primary printer)
#ifdef WITH_MPI
        myComm = primary_printer->get_Comm();
#endif

        // Retrieve the target location for adding new datasets from the primary
        // printer
        location_id = primary_printer->get_location();
        RA_location_id = primary_printer->get_RA_location();
        //startpos = primary_printer->get_startpos(); // OBSOLETE
      }
      // Now that communicator is set up, get its properties.
#ifdef WITH_MPI
      myRank = myComm.Get_rank();
      this->setRank(myRank);
      mpiSize = myComm.Get_size();
#endif
    }

    /// Search the output directory for temporary files (pre-combination)
    std::vector<std::string> HDF5Printer::find_temporary_files(const bool error_if_inconsistent)
    {
      /// Already have a routine to do the work
      std::pair<std::vector<std::string>,std::vector<size_t>> out = HDF5::find_temporary_files(finalfile);
      std::vector<std::string> result = out.first;
      std::vector<size_t> missing = out.second;

      // Check if all temporary files found (i.e. if output from some rank is missing)
      if(error_if_inconsistent)
      {
        if( missing.size()>0 )
        {
          std::ostringstream errmsg;
          errmsg << "HDF5Printer is attempting to resume from a previous run, but could not locate all the expected temporary output files (found "<<result.size()<<" temporary files, but are missing the files from the following ranks: "<<missing<<")! Resuming is therefore not possible; aborting run...";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
      }
      return result;
    }

    /// Scan for existing temporary files, in preparation for combining them
    /// Should only do this if scan is resuming, and if we are process rank 0.
    void HDF5Printer::prepare_and_combine_tmp_files()
    {
      // Need to do combination before trying to get previous points.
      // Make sure a barrier or similar exists outside this function to make
      // sure master node does combination before workers try to retrieve
      // previous points
      if(not get_resume() or not (myRank==0))
      {
        std::ostringstream errmsg;
        errmsg << "HDF5Printer: Tried to run function 'prepare_and_combined_tmp_files', however GAMBIT is not in 'resume' mode, and this is not the process with rank 0, so this is forbidden. This indicates a bug in the HDF5Printer logic, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      /// Check if temporary combined hdf5 file exists (from previous resume!) and can be opened in read/write mode
      logger() << LogTags::repeat_to_cout << LogTags::info
               << "HDF5Printer is preparing any existing output files from a previous run for resuming..."
               << EOM;
      bool combined_file_readable=false;
      std::string msg;
      if( HDF5::checkFileReadable(tmp_comb_file, msg) )
      {
        logger() << LogTags::repeat_to_cout << LogTags::info << "...Existing temporary combined output file was found and is readable" << EOM;
        combined_file_readable=true;
      }
      else
      {
        logger() << LogTags::repeat_to_cout << LogTags::info << "...No readable pre-existing temporary combined output file found" << EOM;
      }
      // Autodetect temporary files from previous run.
      logger() << LogTags::info << " Autodetecting temporary files from previous run..." << EOM;
      std::vector<std::string> tmp_files = find_temporary_files(true);

      if(tmp_files.size()==0)
      {
        logger() << LogTags::repeat_to_cout << LogTags::info << "...No process-level temporary files found. No combination to perform." << EOM;
        // No temporary files exist
        // This is ok, could just be starting a new run
        // But we could also have just finished a run and accidentally tried to continue
        // it -- the responsibility for checking this is left to the calling code, because
        // we could also be trying to store the output of this run in a pre-existing hdf5
        // file, so we cannot assume that a pre-existing file is a problem.
      }
      else
      {
        logger() << LogTags::repeat_to_cout << LogTags::info << "...Found "<<tmp_files.size()<<" process-level temporary files from a previous run. " << EOM;

        // Check if we are allowed to run the combine routines
        if(not disable_combine_routines)
        {
           logger() << LogTags::info << " Will now check to see if they are readable." << EOM;
           // Check if temporary files from previous run are readable.
           for(auto it=tmp_files.begin(); it!=tmp_files.end(); ++it)
           {
             std::string msg2;
             if(not HDF5::checkFileReadable(*it, msg2))
             {
               // We are supposed to be resuming, but no readable output file was found, so we can't.
               std::ostringstream errmsg;
               errmsg << "Error! GAMBIT is in resume mode, however the chosen output system (HDF5Printer) could not locate/read all the required temporary files from the previous run (possibly there is no unfinished run to continue from). Resuming is therefore not possible; aborting run... (see below for IO error messages)";
               errmsg << std::endl << "IO message for temporary combined output file read attempt: ";
               errmsg << std::endl << "    " << msg;
               errmsg << std::endl << "IO message for temporary uncombined output file read attempt: ";
               errmsg << std::endl << "    " << msg2;
               printer_error().raise(LOCAL_INFO, errmsg.str());
             }
           }
           // Ok all the temporary files exist: combine them
           // (but do it in non-resume mode, since any potentially existing output file is unreadable anyway)
           std::ostringstream logmsg;
           if(combined_file_readable)
           {
             logmsg << " Temporary combined output file detected" << std::endl;
             logmsg << "  (found "<<tmp_comb_file<<")"<<std::endl;
             logmsg << "  Will merge temporary files from last run into this file"<<std::endl;
             logmsg << "  If run completes, results will be moved to "<<finalfile<<std::endl;
           }
           else
           {
             logmsg << " No temporary combined output file detected" << std::endl;
             logmsg << "  (searched for "<<tmp_comb_file<<")"<<std::endl;
             logmsg << "  Will attempt to create it from temporary files from last run"<<std::endl;
             logmsg << "  If run completes, results will be moved to "<<finalfile<<std::endl;
           }
           logmsg << " Detected the following temporary files: " << std::endl;
           for(auto it=tmp_files.begin(); it!=tmp_files.end(); ++it)
           {
             logmsg << "   " << *it << std::endl;
           }
           logmsg << " Attempting combination into: "<< std::endl;
           logmsg << "   " << tmp_comb_file;
           logger() << LogTags::printers << LogTags::info << logmsg.str() << EOM;
           combine_output(tmp_files,false);
           logger() << LogTags::repeat_to_cout << LogTags::printers << LogTags::info << "...Combination complete!" << EOM;
        }
        else
        {
           std::ostringstream errmsg;
           errmsg << " Process level temporary HDF5 output was detected, however the 'disable_combine_routines' option is set for the HDF5 printer plugin. The combine code is therefore not permitted to run, so this job cannot proceed. Please either manually combine the output files, restart the scan, or set this option to 'false'" << std::endl;
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }
      }
    }

    /// Initialisation function
    // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
    void HDF5Printer::initialise(const std::vector<int>& /*printmevec*/)
    {
      // Nothing to be done
    }

    /// Destructor
    // Overload the base class virtual destructor
    HDF5Printer::~HDF5Printer()
    {
      DBUG( std::cout << "Destructing HDF5Printer object (with name=\""<<printer_name<<"\")..." << std::endl; )
    }

    /// Perform final cleanup and write tasks
    void HDF5Printer::finalise(bool abnormal)
    {
      // Only the primary_printer should have to do anything here, since it
      // has access to all the buffers.
      if(is_primary_printer)
      {
        std::cout << "Running finalise() routine for HDF5Printer (with name=\""<<printer_name<<"\", early="<<abnormal<<")"<<std::endl;
        logger() << LogTags::printers << "Running finalise() routine for HDF5Printer (with name=\""<<printer_name<<"\")..." << EOM;

        // Make sure all the buffers are caught up to the final point.
        synchronise_buffers();
        logger() << LogTags::printers << "Print buffers synchronised; flushing them to disk" << EOM;
        flush();
        logger() << LogTags::printers << "Final buffer flush done ("<<printer_name<<")"<<EOM;

        // close HDF5 datasets, groups, and file

        for(BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
        {
          // Tell the buffers that they are done; they should then close the HDF5 datasets that they own.
          it->second->finalise();
        }
        HDF5::closeGroup(group_id);
        HDF5::closeGroup(RA_group_id);
        HDF5::closeFile(file_id);

        // Check that sync buffers have a consistent length, and that RA buffers have a consistent length
        // (though each group can have different lengths)
        unsigned long dset_length = 0;
        unsigned long RA_dset_length = 0;
        logger() << LogTags::printers << "Checking for any leftover RA write attempts" << EOM;

        for(BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
        {
          //std::cout << it->second->get_label() <<": "<< it->second->postponed_RA_queue_length() <<std::endl;
          std::size_t remaining_msgs = it->second->postponed_RA_queue_length();
          if(remaining_msgs!=0)
          {
            std::ostringstream errmsg;
            errmsg << "Error! There are (N="<<remaining_msgs<<") postponed random-access writes still left unwritten to disk in buffer "<<it->second->get_label()<<" at end of run! This may mean that some sync buffer data was not properly delivered from another process.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
          }

          // Debug: check final lengths
#ifdef FINAL_MPI_DEBUG
          std::cout << "dset: " << it->second->get_label() << ", length:" << it->second->get_dataset_length() << std::endl;
#endif

          if(it->second->is_synchronised())
          {
            if(dset_length==0) { dset_length = it->second->get_dataset_length(); }
            else if(dset_length != it->second->get_dataset_length())
            {
              std::ostringstream errmsg;
              errmsg << "Error! Inconsistency detected in output dataset lengths during hdf5printer::finalise(). Datasets from buffer "<<it->second->get_label()<<" have length "<<it->second->get_dataset_length()<<", but previous sync datasets had length "<<dset_length<<".";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
          else // not synchronised
          {
            if(RA_dset_length==0) { RA_dset_length = it->second->get_dataset_length(); }
            else if(RA_dset_length != it->second->get_dataset_length())
            {
              std::ostringstream errmsg;
              errmsg << "Error! Inconsistency detected in output dataset lengths during hdf5printer::finalise(). Datasets from buffer "<<it->second->get_label()<<" have length "<<it->second->get_dataset_length()<<", but previous RA datasets had length "<<RA_dset_length<<".";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
        }

        /// Double-check that all the buffers are empty.
        logger() << LogTags::printers << "Double-checking that all print buffers are empty" << EOM;
        for(BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
        {
          if(it->second->is_synchronised())
          {
            if(it->second->sync_buffer_is_full()==true)
            {
              std::ostringstream errmsg;
              errmsg << "rank "<<myRank<<": Error! Buffer "<<it->second->get_label()<<" reports sync_buffer_is_full()=true after finalise operations should be complete!";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            if(it->second->sync_buffer_is_empty()==false)
            {
              std::ostringstream errmsg;
              errmsg << "rank "<<myRank<<": Error! Buffer "<<it->second->get_label()<<" reports sync_buffer_is_empty()=false after finalise operations should be complete!";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
          else
          {
            if(it->second->postponed_RA_queue_length()!=0)
            {
              std::ostringstream errmsg;
              errmsg << "rank "<<myRank<<": Error! Buffer "<<it->second->get_label()<<" reports postponed_RA_queue_length!=0 (length is "<<it->second->postponed_RA_queue_length()<<") after finalise operations should be complete!";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            if(it->second->get_RA_queue_length()!=0)
            {
              std::ostringstream errmsg;
              errmsg << "rank "<<myRank<<": Error! Buffer "<<it->second->get_label()<<" reports get_RA_queue_length()!=0 (length is "<<it->second->get_RA_queue_length()<<") after finalise operations should be complete!";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
        }

        /// BEGIN DATA COMBINATION
        //  We now need to combine the data from all the different processes
        //  that were creating output during this run. First, make sure all
        //  processess are finished
        //  TODO: This requires that the scanner code did not shut down MPI
        //  already! In principle we could do this another way, e.g. by
        //  getting all processes to write a dummy file that signals that
        //  they are done, but for now let us just use this:
        //  TODO: In principle we shouldn't have to do this combination if
        //  either MPI is not used at all, or if mpiSize==1, however currently
        //  we still have to do it due to the way the RA writes are just
        //  "queued up" in the temporary HDF5 file, rather than actually
        //  written to the correct place. But should make it do the latter
        //  in these special cases.
        if(not abnormal) // Don't do the combination in case of abnormal termination, since we cannot reliably wait for all the other processes to finish
        {
#ifdef WITH_MPI
          logger() << LogTags::printers << "We are in normal shutdown mode, meaning that the run has finished and output files should be combined. However, the master process must wait for all workers to write their output to disk before attempting the combination. We are now entering this barrier; if we are master we will wait here; all other processes will just register entry and then continue." << EOM;
          myComm.masterWaitForAll(FINAL_SYNC);
          // TODO! What if the master finishes before other processes? Then it will sit here. But what then if an abnormal shutdown signal is received?? Then the other processes will not enter the barrier! This is bad.
          // To avoid the problem we'd have to make the wait able to monitor for termination signals.
          // Also could just turn off the auto-combination and make the user "continue" the scan one final time to trigger the combination?
#endif

          logger() << LogTags::printers << "Passed FINAL_SYNC point in HDF5Printer finalise() routine" << EOM;

          if(myRank==0)
          {
            // Make sure all datasets etc are closed before doing this or else errors may occur.

            if(not disable_combine_routines)
            {
               logger() << LogTags::printers << "We are the master process: beginning combination of output files." << EOM;
               combine_output(find_temporary_files(true),true);
            }
            else
            {
               logger() << LogTags::printers << "We are the master process: but 'disable_combine_routines' is set to true. SKIPPING combination of output files." << EOM;
            }
          }
        }
        else
        {
          logger() << LogTags::printers << "rank "<<myRank<<": HDF5Printer is terminating abnormally (usually if some signal, e.g. CTRL-C detected); temporary hdf5 files NOT combined! Combination will be attempted upon resuming the run." << EOM;
        }
        logger() << LogTags::printers << "rank "<<myRank<<": HDF5Printer finalise() completed successfully." << EOM;
      } //end if(is_primary_printer)
    }

    /// Combine temporary hdf5 output files from each process into a single coherent hdf5 file
    /// This version operates via the python script 'combine_hdf5.py'
    void HDF5Printer::combine_output_py(const std::vector<std::string> tmp_files, const bool finalcombine)
    {
      std::ostringstream command;
      std::ostringstream tmp_file_list;
      for(auto it=tmp_files.begin(); it!=tmp_files.end(); ++it)
      {
        tmp_file_list << *it << " ";
      }
      command << "python "<< GAMBIT_DIR <<"/Printers/scripts/combine_hdf5.py --delete_tmp "<<tmp_comb_file<<"  "<<group<<" "<<tmp_file_list.str()<<" 2>&1";
      logger() << LogTags::printers << "Running HDF5 data combination script..." << std::endl;
      logger() << "> " << command.str() << std::endl;
      logger() << EOM;
      FILE* fp = popen(command.str().c_str(), "r");
      if(fp==NULL)
      {
        // Error running popen
        std::ostringstream errmsg;
        errmsg << "rank "<<myRank<<": Error running HDF5 data combination script during HDF5Printer finalise()! popen failed to run the specified command (command was '"<<command.str()<<"')";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      // Something ran at least; get the stdout (plus redirected stderr)
      char buffer[2048];
      // read output into a c++ stream via buffer
      std::ostringstream output;
      while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        output << buffer;
      }
      int rc = pclose(fp);
      logger() << LogTags::printers << LogTags::info;
      logger() << "Stdout/stderr captured from HDF5printer combination script" << std::endl;
      logger() << "--------------------" << std::endl;
      logger() << output.str() << std::endl;
      logger() << "--------------------" << std::endl;
      logger() << "end HDF5 combination script output" << EOM;
      if(rc!=0)
      {
        // Python error occurred
        std::ostringstream errmsg;
        errmsg << "rank "<<myRank<<": Error running HDF5 data combination script during HDF5Printer finalise()! Script ran, but return code != 0 was encountered; stdout and stderr from the system call can be found in the log files.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      // Otherwise everything should be ok!
      if(finalcombine)
      {
        // This happens only at the end of the run; copy data to user-requested filename
        // TODO! This does not permit adding different runs into the same hdf5 file
        // Need to make sure Greg's combine code can do this.
        std::ostringstream command2;
        command2 <<"cp "<<tmp_comb_file<<" "<<finalfile<<" && rm "<<tmp_comb_file; // Note, deletes old file if successful
        logger() << LogTags::printers << LogTags::info << "Running shell command: " << command2.str() << EOM;
        FILE* fp = popen(command2.str().c_str(), "r");
        if(fp==NULL)
        {
          // Error running popen
          std::ostringstream errmsg;
          errmsg << "rank "<<myRank<<": Error copying combined HDF5 data to final location during HDF5Printer finalise()! popen failed to run the specified copy (and delete) command (command was '"<<command2.str()<<"')";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        else if(pclose(fp)!=0)
        {
          // Command returned exit code!=0, or pclose failed
          std::ostringstream errmsg;
          errmsg << "rank "<<myRank<<": Error copying combined HDF5 data to final location during HDF5Printer finalise()! Shell command failed to execute successfully, please check stderr (command was '"<<command2.str()<<"').";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        // Success!
      }
    }

    /// Combine temporary hdf5 output files from each process into a single coherent hdf5 file
    /// This version operates via Greg's C++ routines.
    void HDF5Printer::combine_output(const std::vector<std::string> tmp_files, const bool finalcombine)
    {
      logger() << LogTags::printers << "Running HDF5 data combination..." << EOM;
      // Do combination
      int num = tmp_files.size(); // We don't actually use their names here, Greg's code assumes that they
                                  // follow a fixed format and they all exist. We check for this before
                                  // running this function, so this should be fine.

      // If we set the second last flag 'true' then Greg's code will assume that a '_temp_combined' output file
      // exists, and it will crash if it doesn't. So we need to first check if such a file exists.
      bool combined_file_exists = Utils::file_exists(tmp_comb_file); // We already check this externally; pass in as flag?
      std::cout<<"combined_file_exists? "<<combined_file_exists<<std::endl;
      // Second last bool just tells the routine to delete the temporary files when it is done
      // Last flag, if false, tells routines to throw an error if any expected temporary file cannot be opened for any reason
      HDF5::combine_hdf5_files(tmp_comb_file, finalfile, group, num, combined_file_exists, true, false);

      // This is just left the same as the combine_output_py version!
      if(finalcombine)
      {
        // This happens only at the end of the run; copy data to user-requested filename
        // TODO! This does not permit adding different runs into the same hdf5 file
        // Need to make sure Greg's combine code can do this.
        std::ostringstream command2;
        command2 <<"cp "<<tmp_comb_file<<" "<<finalfile<<" && rm "<<tmp_comb_file; // Note, deletes old file if successful
        logger() << LogTags::printers << LogTags::info << "Running shell command: " << command2.str() << EOM;
        FILE* fp = popen(command2.str().c_str(), "r");
        if(fp==NULL)
        {
          // Error running popen
          std::ostringstream errmsg;
          errmsg << "rank "<<myRank<<": Error copying combined HDF5 data to final location during HDF5Printer finalise()! popen failed to run the specified copy (and delete) command (command was '"<<command2.str()<<"')";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        else if(pclose(fp)!=0)
        {
          // Command returned exit code!=0, or pclose failed
          std::ostringstream errmsg;
          errmsg << "rank "<<myRank<<": Error copying combined HDF5 data to final location during HDF5Printer finalise()! Shell command failed to execute successfully, please check stderr (command was '"<<command2.str()<<"').";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        // Success!
      }

    }


    /// Retrieve pointer to HDF5 location to which datasets are added
    hid_t HDF5Printer::get_location() const
    {
      if(location_id==-1)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to retrieve 'location_id' handle from HDF5Printer, but it is -1! This means the printer has not been set up correctly. This is a bug, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      return location_id;
    }

    hid_t HDF5Printer::get_RA_location() const
    {
      if(RA_location_id==-1)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to retrieve 'RA_location' pointer from HDF5Printer, but it is -1! This means the printer has not been set up correctly. This is a bug, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      return RA_location_id;
    }

    /// Add a pointer to a new buffer to the global list for this printer
    /// and also register it with the list global to all printers.
    void HDF5Printer::insert_buffer(VBIDpair& key, VertexBufferBase& newbuffer)
    {
      error_if_key_exists(all_my_buffers, key, "all_my_buffers");
      all_my_buffers[key] = &newbuffer;

      error_if_key_exists(all_buffers, key, "all_buffers");
      primary_printer->all_buffers[key] = &newbuffer;
    }

    /// Check if an output stream is already managed by some buffer in any printer.
    bool HDF5Printer::is_stream_managed(VBIDpair& key) const
    {
      bool answer = true;
      if( primary_printer->all_buffers.find(key)
         == primary_printer->all_buffers.end() )
      {
        answer = false;
      }
      return answer;
    }

    /// Add PPIDpair to global index list
    /// In this version of the HDF5Printer, this list applies only to RA points.
    /// Synchronised writes are not tracked.
    /// UPDATE! Due to memory issues with tracking many RA points, we now only track
    /// the last 10*BUFFERLENGTH points. When the PPID list gets "full" we do a flush,
    /// and then start tracking again, with the new list getting assigned only indices
    /// above the highest in the previous list. This means that the output will
    /// potentially have duplicate RA write commands, so the post-processing should be
    /// sure to preferrentially take the latest commands over earlier ones.
    void HDF5Printer::add_PPID_to_list(const PPIDpair& ppid)
    {
      // Check if it is in the lookup map already
      std::map<PPIDpair, unsigned long>& lookup = primary_printer->global_index_lookup;
      std::vector<PPIDpair>& reverse_lookup = primary_printer->reverse_global_index_lookup;
      std::map<PPIDpair, unsigned long>::const_iterator it = lookup.find(ppid);
      if ( it != lookup.end() ) {
        std::ostringstream errmsg;
        errmsg << "Error! Supplied PPID already exists in global_index_lookup map! It should only be added once, so there is a bug in HDF5Printer. Please report this error.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      // If the list has reached its max allowed length, flush any queued RA
      // writes, clear the list, and increment RA_dset_offset.
      if(reverse_lookup.size()==MAX_PPIDPAIRS)
      {
        for (BaseBufferMap::iterator it = primary_printer->all_buffers.begin(); it != primary_printer->all_buffers.end(); it++)
        {
          if(it->second->is_synchronised())
          { /*do nothing, these are the sync buffers*/ }
          else
          {
            it->second->RA_flush(primary_printer->global_index_lookup);
          }
        }
        lookup.clear();
        reverse_lookup.clear();
        primary_printer->RA_dset_offset += MAX_PPIDPAIRS;
      }

      // Ok, now safe to add new stuff
      lookup[ppid] = reverse_lookup.size() + primary_printer->RA_dset_offset;
      reverse_lookup.push_back(ppid);

      // Need to make sure the pointID and MPIrank are stashed at this location in the RA output
      // (this should only occur from within a non-synchronised printer, so these should be
      //  interpreted as RA writes)
      unsigned long pointID = ppid.pointID; // unsigned versions were coming out gibberish in python...
      unsigned int mpirank = ppid.rank;
      //std::cout << "rank "<<myRank<<": adding new RA PPID to list: (" << pointID << "," << mpirank << ")" << std::endl;

      // The ID numbers will be obtained via the 'aux' parameter system, but I think that is fine.
      // The call is a little bizarre because these are template functions from the base class, which
      // require this weird notation to resolve a compiler abiguity.
      this->print(pointID, "RA_pointID", mpirank, pointID);
      this->print(mpirank, "RA_MPIrank", mpirank, pointID);
    }

    /// Completely reset the PPIDlists
    void HDF5Printer::reset_PPID_lists()
    {
      primary_printer->global_index_lookup.clear();
      primary_printer->reverse_global_index_lookup.clear();
      primary_printer->RA_dset_offset = 0;
    }

    /// Check if PPIDpair exists in global index list
    bool HDF5Printer::seen_PPID_before(const PPIDpair& ppid)
    {
      bool result = false;
      std::map<PPIDpair, unsigned long>& lookup = primary_printer->global_index_lookup;
      if ( lookup.find(ppid) != lookup.end() ) result = true;
      return result;
    }

    /// Retrieve index from global lookup table, with error checking
    unsigned long HDF5Printer::get_global_index(const unsigned long pointID, const unsigned int mpirank)
    {
      std::map<PPIDpair, unsigned long>::iterator it;
      std::map<PPIDpair, unsigned long>& lookup = primary_printer->global_index_lookup;
      it = lookup.find(PPIDpair(pointID,mpirank));
      if ( it == lookup.end() )
      {
#ifdef DEBUG_MODE
        std::cout<<"Contents of global_index_lookup map:"<<std::endl;
        for(it = lookup.begin(); it != lookup.end(); it++) {
          std::cout<<"[pointID="<<it->first.first<<", mpirank="<<it->first.second<<"] : index="<<it->second<<std::endl;
        }
#endif
        std::ostringstream errmsg;
        errmsg << "Error retrieving global index for pointID="<<pointID<<", mpirank="<<mpirank<<"; no corresponding global index found. This means this point has not yet passed through the primary printer. This function is called in preparation for writing to data files via random access, so possibly something has gone wrong there.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      return it->second;
    }

    /// Function to ensure buffers are all synchronised to the same absolute position
    // Will move the "write heads" of all buffers to "current_dset_position"
    // This should only required one "skip_append" command at most to each buffer; something
    // went wrong if more are required.
    void HDF5Printer::synchronise_buffers()
    {
      if(is_auxilliary_printer())
      {
        std::ostringstream errmsg;
        errmsg << "Error! synchronise_buffer() called by auxilliary hdf5 printer (name="<<printer_name<<")! Only the primary hdf5 printer is allowed to do this. This is a bug in the HDF5Printer class, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      // Determine the desired sync position
      const unsigned long sync_pos = get_sync_pos()-1;

      // Cycle through all buffers and tell them to ensure they are at the right position
      // The buffers should throw an error if we are accidentally telling them to go backwards
      // or skip too many points or anything they can't do.
      // Here though we should only be moving them forward by one position.
#ifdef DEBUG_MODE
      std::cout<<"rank "<<myRank<<": Synchronising buffers to position "<<sync_pos<<" (message from printer: "<<printer_name<<", is_auxilliary: "<<is_auxilliary_printer()<<", synchronised: "<<synchronised<<")"<<std::endl;
#endif

      // Do the sync buffers first:
      for (BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
      {
        if(it->second->is_synchronised()) it->second->synchronise_output_to_position(sync_pos);
      }

      // Now the RA buffers; they don't have to be the same size as the sync buffers, but it
      // is useful if we keep them all the same length. Need two loops; one to find the current
      // max length of an RA buffer, and the next to tell them all to adjust themselves to
      // that length (which won't actually happen until the next time they need to write their
      // data to disk).
      // TODO: may not need this, can possible just set them to match "get_N_RApointIDs()".
      // These are all the possible RA write position anyway...
      unsigned long maxRAlength = get_N_RApointIDs();
      //for (BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
      //{
      //  if(not it->second->is_synchronised())
      //  {
      //     unsigned long length = it->second->get_dataset_length();
      //     if(length>maxRAlength) maxRAlength = length;
      //  }
      //}
      for (BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
      {
        if(not it->second->is_synchronised()) it->second->synchronise_output_to_position(maxRAlength);
      }
    }

    // (this will trigger MPI sends if needed)
    // Note that if one sync buffer is full, they should all be full!
    // By default this only empties buffers if they are full. Use
    // flag to force the flush for the finalise buffer dumps.
    void HDF5Printer::empty_sync_buffers(bool force)
    {
#ifdef DEBUG_MODE
      std::cout<<"rank "<<myRank<<": Emptying sync buffers (if full)..."<<std::endl;
#endif
      unsigned int N_sync_buffers = 0;
      unsigned int N_were_full = 0;
      for (BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
      {
        if(it->second->is_synchronised())
        {
          N_sync_buffers += 1;
          if(it->second->sync_buffer_is_full() or force)
          {
#ifdef DEBUG_MODE
            std::cout<<"rank "<<myRank<<": Emptying sync buffer "<<it->second->get_label()<<std::endl;
#endif
            N_were_full += 1; // Can get flushed if not full only if force=true
            it->second->flush();
          }
        }
      }

      // Make sure that all the buffers were full and have now been cleared!
      if(N_were_full != 0 and N_were_full != N_sync_buffers)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to empty all synchronised buffers, but some of them were not full! (N_were_full ("<<N_were_full<<") != N_sync_buffers ("<<N_sync_buffers<<"). This indicates that a loss of synchronisation has occurred, which is a bug in the hdf5printer system. Please report it. (Note: rank="<<myRank<<", printer_name="<<printer_name<<")";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      // Tell the HDF5 library to flush everything to disk
      herr_t err = H5Fflush(file_id, H5F_SCOPE_GLOBAL);
      if(err<0)
      {
        std::ostringstream errmsg;
        errmsg << "Error in HDF5Printer while trying to empty all synchronised buffers. Buffers were emptied to the HDF5 backend (seemingly) successfully, however H5Fflush returned an error value ("<<err<<"). That is, an error occurred while the HDF5 system attempted to flush its internally buffered data to disk. (Note: rank="<<myRank<<", printer_name="<<printer_name<<")";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
    }

    /// Empty all the buffers to disk
    /// Note: Empty sync buffers will not get flushed, to avoid writing extra
    /// buffer-lengths at the end of scan.
    void HDF5Printer::flush()
    {
      empty_sync_buffers(true); // NOTE: forces flush even if buffers not full

      // Need to do all the sync buffers before the RA buffers, so that at the end of the
      // run the sync buffers all get written to disk first, and no RA writes get left
      // in the postpone queue due to missing targets.
      for (BaseBufferMap::iterator it = all_buffers.begin(); it != all_buffers.end(); it++)
      {
        if(it->second->is_synchronised())
        { // do nothing, these are the sync buffers
          //if(not it->second->sync_buffer_is_empty()) {}
        }
        else
        {
          it->second->RA_flush(primary_printer->global_index_lookup);
          //std::cout<<"rank "<<myRank<<": flushing RA buffer of "<<it->second->get_label()<<std::endl;
        }
      }

      // Make sure RA datasets are the same length


    }

    /// Invalidate all data on disk which has been printed by this printer so far,
    /// and reset all the buffers to write back to the first data slots.
    /// This is only allowed if this is an auxilliary printer with global=true, or
    /// if "force=true" is specified.
    void HDF5Printer::reset(bool force)
    {
      //#ifdef DEBUG_MODE
      std::cout<<"resetting..."<<std::endl;
      std::cout<<"is_auxilliary_printer() = "<<is_auxilliary_printer()<<std::endl;
      std::cout<<"synchronised            = "<<synchronised<<std::endl;
      std::cout<<"printer_name            = "<<printer_name<<std::endl;
      //#endif
      if(not force and not this->is_auxilliary_printer())
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to call reset() on the primary HDF5Printer (printer_name = "<<printer_name<<")! This would delete all the data from the scan and is not currently allowed! Probably this was called accidentally due to a bug.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      else if(not force and synchronised)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to call reset() on an auxilliary HDF5Printer (printer_name = "<<printer_name<<") which is synchronised with the primary printer! This would delete all the point-level data written by this printer during the scan and is not currently allowed! Probably this was called accidentally due to a bug.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      else
      {
        // Ok safe to do the resets.
        for (BaseBufferMap::iterator it = all_my_buffers.begin(); it != all_my_buffers.end(); it++)
        {
          // SPECIAL CASES!
          // We rely on the special RA buffers 'RA_MPIrank' and 'RA_pointID'
          // to keep track of which RA entries correspond to which
          // sync buffer points. Once written once, we preserve which slots
          // in the RA datasets correspond to a particular sync point, even
          // after resetting them, because multiple RA streams are all
          // writing data into the same hdf5 group. So if we invalidate the
          // RA_MPIrank and RA_pointID ranks, then we screw up the matching
          // between RA output streams (i.e. non-sync printers).
          // Could perhaps use a different groups for each aux printer
          // (i.e. stream). each with its own MPIrank and pointID datasets.
          // For now though, we will simply not invalidate these datasets.
          const std::string& name = it->second->get_label();
          if(name!="RA_MPIrank" and name!="RA_pointID")
          {
            // Reset the rest
            it->second->reset(force);
          }
        }
        // Also need to reset the PPID lists
        // TODO: The HDF5Printer currently assumes that ALL the auxilliary printers are
        // reset together. This is not really what we want, but to deal with it I would
        // need to make e.g. a separate "RA" group in the hdf5 output for every aux
        // stream, and then get the combine script to combine them all.
        reset_PPID_lists();
      }
    }

    /// For debugging: check that buffers are synced correctly
    /// Flag sets whether "perfect" sync is required, or whether
    /// some buffers can be ahead by one slot (due to having
    /// performed prints that other buffers have not yet done)
    /// If checkall=true, then all_buffers is checked, not just
    /// all_my_buffers. Only primary printer can do this.
    void HDF5Printer::check_sync(const std::string& label, const int sync_type, bool checkall=false)
    {
      BaseBufferMap* map_to_check=NULL;
      if(checkall)
      {
        if(not is_primary_printer)
        {
          std::ostringstream errmsg;
          errmsg << "Error running 'check_sync'; flag 'checkall' set to true, but this is not the primary printer (it is "<<this->get_printer_name()<<") This is not allowed and is a bug, please fix it.";
          printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        else
        {
          map_to_check=&all_buffers;
        }
      }
      else
      {
        map_to_check=&all_my_buffers;
      }

      // Explicitly check up on the synchronisation of all the buffers and their
      // associated datasets
      std::string sync_type_name = "non-perfect";
      long int diff; // required difference (dset_head_pos - sync_pos)
      if     (sync_type==0) {
        sync_type_name = "pre-resync (non-perfect)";
      }
      else if(sync_type==1) {
        diff = 1;
        sync_type_name = "post-resync   (perfect)";
      }
      else if(sync_type==2) {
        diff = 0;
        sync_type_name = "post-newpoint (perfect)";
      }

      std::cout<<"rank "<<myRank<<": Sync check (type: "<<sync_type_name<<"); "<<label<<std::endl;

#define ERR_MSG \
std::ostringstream errmsg; \
errmsg << "rank "<<myRank<<": Error! ("<<label<<"; ("<<sync_type_name<<") sync check) Buffers have gone out of sync in printer '"<<printer_name<<"'!"<<std::endl; \
errmsg << "   head_pos = " << head_pos << "; name = " << name << std::endl; \
errmsg << "   sync_pos = " << sync_pos_plus1-1 << std::endl;

      for(BaseBufferMap::iterator it = map_to_check->begin(); it != map_to_check->end(); it++)
      {
        if(it->second->is_synchronised())
        {
          long head_pos = it->second->dset_head_pos();
          std::string name = it->second->get_label();
          long sync_pos_plus1 = get_sync_pos();

          if(sync_type==0) {
            if(head_pos+1 < sync_pos_plus1)
            {
              ERR_MSG
              errmsg << " (head_pos < syncpos) " << std::endl;
              printer_error().raise(LOCAL_INFO, errmsg.str());
            } else if (head_pos > sync_pos_plus1)
            {
              ERR_MSG
              errmsg << " (head_pos > syncpos + 1) " << std::endl;
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }  // else ok.
          }
          else if(sync_type==1 or sync_type==2)
          {
            if(head_pos != sync_pos_plus1-1 + diff)
            {
              ERR_MSG
              errmsg << " (head_pos != syncpos + "<<diff<<") " << std::endl;
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }

          std::cout << "   head_pos = " << head_pos << "; name = " << name << std::endl;
          std::cout << "   sync_pos = " << sync_pos_plus1-1 << std::endl;
          //it->second->sync_report();
        }
      }
    }


    /// Check whether printing to a new parameter space point is about to occur
    // and perform adjustments needed to prepare the printer.
    void HDF5Printer::check_for_new_point(const PPIDpair& candidate_newpoint)
    {
      if(is_auxilliary_printer())
      {
        // Redirect task to primary printer
        primary_printer->check_for_new_point(candidate_newpoint);
      }

      // Check if we have changed target PointIDs since the last print call
      if(candidate_newpoint!=lastPointID)
      {

#ifdef MPI_DEBUG
        std::cout<<"rank "<<myRank<<": New point detected (lastPointID="<<lastPointID<<", candidate_newpoint="<<candidate_newpoint<<")"<<std::endl;
        std::cout<<"rank "<<myRank<<": sync_pos="<<get_sync_pos()<<std::endl;
#endif

        // Explicitly check up on the synchronisation of all the buffers and their
        // associated datasets

        // When a new point is detected, the "sync position" should be the
        // largest index which has a pointID assigned, which will match the
        // head_pos of any buffers which didn't write to that point.
        // The other buffers are allowed to be AT MOST one slot ahead of this,
        // having done a write for the last point and moved ahead one slot.
        //
        // At the end of this routine, all the buffers should once again
        // have their write heads pointing to both the same buffer index, and
        // the same output dataset index, and this index should be equal to
        // the number of pointIDs collected so far, minus 1 for the zero indexing
        // (with the last ID being the point from which the next print statements
        // will arrive).
        //
        // So, in the end, with sync_pos = reverse_global_index_lookup.size() - 1 = get_N_pointIDs() - 1
        // we require
        //   dset_head_pos() == sync_pos
        // for every buffer.
        // However, at the beginning, we may have
        //   dset_head_pos() == sync_pos + 1
        // for some buffers, which, after sync_pos is incremented with the new
        // pointID, will match the new sync_pos, and the other buffers will need
        // to be caught up. Any other state is an error.
        // So, in debug mode, we will check this first.

#ifdef CHECK_SYNC
        check_sync("Prelim check (in check_for_new_point)", 0);
#endif

        // Make sure all the buffers are caught up at the old position.
        synchronise_buffers();

#ifdef CHECK_SYNC
        check_sync("Post-resync check (in check_for_new_point)", 1);
#endif

        // Yep the scanner has moved on, at least as far as the current process sees
        lastPointID = candidate_newpoint;

        // Check if the buffers are full and waiting to be emptied
        // (this will trigger MPI sends if needed)
        empty_sync_buffers();

#ifdef CHECK_SYNC
        check_sync("Post-buffer-empty check (in check_for_new_point)", 1);
#endif

        // Move forward buffer synchronisation counter by one slot
        increment_sync_pos();

        // Now the buffers should all be synchronised; check this in debug mode.
#ifdef CHECK_SYNC
        check_sync("Post-newpoint check (in check_for_new_point)", 2);
#endif

        // Debugging only! check if buffers are somehow still full...
#ifdef MPI_DEBUG
        for (BaseBufferMap::iterator it = all_my_buffers.begin(); it != all_my_buffers.end(); it++)
        {
          if(it->second->is_synchronised())
          {
            if(it->second->sync_buffer_is_full())
            {
              std::ostringstream errmsg;
              errmsg << "rank "<<myRank<<": Error! sync buffer with label "<<it->second->get_label()<<" is full! Should not be full at this point (printer="<<printer_name<<")";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
          }
        }
#endif

        // For resuming, we need to be able to retrieve the pointID and
        // MPIrank for every output point. So we need to make sure this
        // information is always output, and not rely on the scanner to
        // do it. Scanners can output it as well, since not all printers
        // may do it automatically (although it would be good if they
        // did), but in that case they should use the special ID codes
        // below to avoid duplication.
        // EDIT: Ok need to do these in the constructor also, since otherwise
        // the very first point gets missed.
        /// TODO: Ok currently cannot both print them here and in the scanner plugins.
        /// Need to deal with duplicate print attempts better.
        //_print(candidate_newpoint, "pointID", -1000, myRank, candidate_newpoint);
        //_print(myRank,             "MPIrank", -1001, myRank, candidate_newpoint);
      }
      else
      {
        // no action required
      }
    }

    /// @}

  } // end namespace printers
} // end namespace Gambit

#undef DBUG
#undef DEBUG_MODE
