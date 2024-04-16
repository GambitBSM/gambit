//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  "Postprocessing" scanner plugin.
///  Header file
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

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/postprocessor_1.0.0/chunks.hpp"

#ifndef __postprocessor_1_0_0_hpp__
#define __postprocessor_1_0_0_hpp__

// Forward declare this template specialisation as extern so that we use the definition compiled into baseprinter.cpp
extern template std::size_t Gambit::Printers::getTypeID<double>();

namespace Gambit
{
  namespace PostProcessor
  {
      /// @{ Helper functions for performing resume related tasks

      /// Answer queries as to whether a given dataset index has been postprocessed in a previous run or not
      bool point_done(const ChunkSet done_chunks, size_t index);
      
      /// Get 'effective' start and end positions for a processing batch
      /// i.e. simply divides up an integer into the most even parts possible
      /// over a given number of processes
      Chunk get_effective_chunk(const std::size_t total_length, const unsigned int rank, const unsigned int numtasks);
      
      /// Compute start/end indices for a given rank process, given previous "done_chunk" data.
      Chunk get_my_chunk(const std::size_t dset_length, const ChunkSet& done_chunks, const int rank, const int numtasks);
      
      /// Read through resume data files and reconstruct which chunks of points have already been processed
      ChunkSet get_done_points(const std::string& filebase);
     
      /// Simplify a ChunkSet by merging chunks which overlap.
      ChunkSet merge_chunks(const ChunkSet&);
 
      /// Write resume data files
      /// These specify which chunks of points have been processed during this run
      void record_done_points(const ChunkSet& done_chunks, const Chunk& mydone, const std::string& filebase, unsigned int rank, unsigned int size);

      // Gather a bunch of ints from all processes (COLLECTIVE OPERATION)
      #ifdef WITH_MPI
      std::vector<int> allgather_int(int myval, GMPI::Comm& comm);
      #endif
      /// @}

      /// Options object for PPDriver
      /// See matching options in PPDriver class for description
      struct PPOptions
      {
         std::set<std::string> all_params;
         std::set<std::string> data_labels;
         std::set<std::string> data_labels_copy;
         std::vector<std::string> add_to_logl;
         std::vector<std::string> subtract_from_logl;
         std::map<std::string,std::string> renaming_scheme;
         std::map<std::string,double> cut_less_than;
         std::map<std::string,double> cut_greater_than;
         bool discard_points_outside_cuts;
         std::size_t update_interval;
         bool discard_old_logl;
         std::string logl_purpose_name;
         std::string reweighted_loglike_name;
         std::string root;
         unsigned int numtasks;
         unsigned int rank;
         #ifdef WITH_MPI
         GMPI::Comm* comm;
         PPOptions() : comm(NULL) {}
         #endif
      };
 
      /// Driver class to handle the actual postprocessing tasks
      class PPDriver
      {
         public:
            PPDriver();
            PPDriver(Printers::BaseBaseReader* const, Printers::BaseBasePrinter* const, Scanner::like_ptr const, const PPOptions&);
            void check_settings();
            int run_main_loop(const ChunkSet& done_chunks);
            bool get_ModelParameters(std::unordered_map<std::string, double>& outputMap);
            bool check_for_redistribution_request();
            void send_redistribution_request();
            void clear_redistribution_requests();

            // Message tags
            static const int REDIST_REQ = 0;

         private:
            /// Safe accessors for pointer data
            Printers::BaseBaseReader& getReader();
            Printers::BaseBasePrinter& getPrinter();
            Scanner::like_ptr getLogLike();

            /// The reader object in use for the scan
            Printers::BaseBaseReader* reader;

            /// The printer for the primary output stream of the scan
            Printers::BaseBasePrinter* printer;

            /// The likelihood container plugin
            Scanner::like_ptr LogLike;
            
            /// Names of new output to be printed, i.e. output labels not present in the input file.
            std::set<std::string> new_params;

            /// Models required by the scan
            std::map<std::string,std::vector<std::string>> req_models;

            /// Map to retrieve the "model::parameter" version of the parameter name
            std::map<std::string,std::map<std::string,std::string>> longname;

            /// Names of all output that the primary printer knows about at startup (things GAMBIT plans to print from the likelihood loop)
            std::set<std::string> all_params;

            /// Labels of all output datasets
            std::set<std::string> data_labels;

            /// Labels of output datasets to be copied
            std::set<std::string> data_labels_copy;

            /// List of likelihoods in old output to be added to the newly computed likelihood
            std::vector<std::string> add_to_logl;

            /// List of likelihoods in old output to be subtracted from the newly computed likelihood
            std::vector<std::string> subtract_from_logl;

            /// Map for renaming old datasets in the new output
            /// Keys are "in_label", values are "out_label"
            std::map<std::string,std::string> renaming_scheme;

            /// Cut maps, for selecting only points in the input
            /// datasets which pass certain criteria.
            /// Keys are "in_label", values are the cut boundaries.
            std::map<std::string,double> cut_less_than;
            std::map<std::string,double> cut_greater_than;

            /// Flag to throw away points that don't pass the cuts (rather than copying them un-processed)
            bool discard_points_outside_cuts;

            /// Number of iterations between progress reports. '0' means no updates
            std::size_t update_interval;
       
            /// Allow old likelihood components to be overwritten by newly calculated values?
            bool discard_old_logl;
 
            /// Label assigned to the output of the likelihood container
            std::string logl_purpose_name;

            /// The label to assign to the results of add_to_like and subtract_from_like operations.
            std::string reweighted_loglike_name;

            /// Path to save resume files
            std::string root;

            /// MPI variables (set manually rather than inferred, to allow for "virtual rank" settings
            unsigned int numtasks;
            unsigned int rank;
            #ifdef WITH_MPI
            GMPI::Comm* comm;
            #endif
      };

  }
}

#endif

//o.all_params
//o.data_labels
//o.data_labels_copy
//o.add_to_logl
//o.subtract_from_logl
//o.renaming_scheme
//o.cut_less_than
//o.cut_greater_than
//o.discard_points_outside_cuts
//o.update_interval
//o.numtasks
//o.rank
//




