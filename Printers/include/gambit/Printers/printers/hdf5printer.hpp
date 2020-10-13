//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 interface printer class declaration
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


#ifndef __hdf5printer_hpp__
#define __hdf5printer_hpp__

// Standard libraries
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

// Gambit
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/VertexBufferBase.hpp"
#include "gambit/Printers/VertexBuffer_mpitags.hpp"
#include "gambit/Printers/printers/hdf5types.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer/VertexBufferNumeric1D_HDF5.hpp"
#include "gambit/Printers/printers/hdf5printer/DataSetInterfaceScalar.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/Logs/logger.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"

// BOOST_PP
#include <boost/preprocessor/seq/for_each_i.hpp>


//#define DEBUG_MODE
//#define HDEBUG_MODE // "High output" debug mode (info with every single print command)

// Code!
namespace Gambit
{
  namespace Printers
  {

    // Parameter controlling the length of all the standard buffers
    static const std::size_t BUFFERLENGTH = 100; // Change to 10000 or something. Currently cannot change this dynamically though, sorry.
    /// Max number of PPIDpairs to be tracked
    /// i.e. chunks of RA output longer than this can potentially contain multiple writes to the same point.
    /// It is up to the combine script to apply the last scheduled write preferentially.
    static const unsigned long MAX_PPIDPAIRS = 10*BUFFERLENGTH;

    /// @{ Helpful typedefs

    /// Type of the global buffer map
    typedef std::map<VBIDpair, VertexBufferBase*> BaseBufferMap;

    /// Helper function to check if a VertexBuffer key already exists in a map
    template<class T, class U>
    void error_if_key_exists(const std::map<T,U>& m, const T& key, const std::string& tag)
    {
       typename std::map<T,U>::const_iterator it = m.find(key);
       if ( it == m.end() ) {
          return;
       }
       else {
          std::ostringstream errmsg;
          errmsg << "Error! Supplied key for a VertexBuffer already exists in map (tag="<<tag<<")! This is a bug in the HDF5Printer (or Reader) class, please report it.";
          printer_error().raise(LOCAL_INFO, errmsg.str());
       }
    }

    // foward declaration
    class HDF5Printer;

    /// Keeps track of vertex buffers local to a print function
    template<class BuffType>
    class H5P_LocalBufferManager
    {
      private:
        // Buffers local to a print function. Access whichever ones match the IDcode.
        std::map<VBIDpair, BuffType> local_buffers;

        // Pointer to "parent" HDF5Printer object
        // Need to use two-stage initialisation because the automated
        // declaration of new buffer managers requires a default
        // constructor
        HDF5Printer* printer;

        /// Flag to check if a print function has been run before
        // (map is from IDcodes to flags)
        std::map<VBIDpair,bool> first_print;

        /// Flag to trigger treatment of buffers as synchronised or not
        /// i.e. couples buffers to the scanner iteration synchronisation.
        bool synchronised;

        /// Buffer access mode ('r'/'w')
        char access;

      public:
        /// Constructor
        H5P_LocalBufferManager()
          : printer(NULL)
          , synchronised(true)
          , access('w')
        {}

        /// Initialise the buffer (attach it to a printer and set its behaviour)
        void init(HDF5Printer* p, bool synchronised);

        /// Signal whether initialisation has occured
        bool ready() { if(printer==NULL){return false;}else{return true;} }

        /// Retrieve a buffer for an IDcode/auxilliary-index pair
        BuffType& get_buffer(const int vID, const unsigned int i, const std::string& label);

    };


    /// The main printer class for output to HDF5 format
    class HDF5Printer : public BasePrinter
    {
      public:
        /// Constructor (for construction via inifile options)
        HDF5Printer(const Options&, BasePrinter* const primary = NULL);

        /// Tasks common to the various constructors
        void common_constructor(const Options&);

        /// Destructor
        // Overload the base class virtual destructor
        ~HDF5Printer();

        /// Virtual function overloads:
        ///@{

        // Initialisation function
        // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
        void initialise(const std::vector<int>&);
        void flush();
        void reset(bool force=false);
        void finalise(bool abnormal=false);

        // Get options required to construct a reader object that can read
        // the previous output of this printer.
        Options resume_reader_options();

        ///@}

        ///@{ Print functions
        using BasePrinter::_print; // Tell compiler we are using some of the base class overloads of this on purpose.
        #define DECLARE_PRINT(r,data,i,elem) void _print(elem const&, const std::string&, const int, const uint, const ulong);
        BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , HDF5_TYPES)
        #ifndef SCANNER_STANDALONE
          BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , HDF5_BACKEND_TYPES)
        #endif
        #undef DECLARE_PRINT
        ///@}

        /// @{ HDF5Printer-specific functions

        /// Check if an output stream is already managed by some buffer in some printer
        bool is_stream_managed(VBIDpair& key) const;

        /// Retrieve pointer to HDF5 location to which datasets are added
        hid_t get_location() const;
        hid_t get_RA_location() const;

        /// Add a pointer to a new buffer to the global list
        void insert_buffer(VBIDpair& key, VertexBufferBase& newbuffer);

        /// Get the number of pointIDs know to this printer
        /// (should correspond to the number of "appends" each active buffer has received)
        unsigned long get_sync_pos() const { return sync_pos; }

     private:

        /// Buffer manager objects
        //  Need one for every directly retrievable type, and a specialisation
        //  of 'get_mybuffermanager' to access it. But the latter have to be
        //  defined outside the class declaration, so they can be found below.
        //  Could create all these with a macro, but I am sick of macros so
        //  will just do it the "old-fashioned" way.
        #define BT(TYPE) VertexBufferNumeric1D_HDF5<TYPE,BUFFERLENGTH>
        H5P_LocalBufferManager<BT(int      )> hdf5_localbufferman_int;
        H5P_LocalBufferManager<BT(uint     )> hdf5_localbufferman_uint;
        H5P_LocalBufferManager<BT(long     )> hdf5_localbufferman_long;
        H5P_LocalBufferManager<BT(ulong    )> hdf5_localbufferman_ulong;
        H5P_LocalBufferManager<BT(longlong )> hdf5_localbufferman_longlong;
        H5P_LocalBufferManager<BT(ulonglong)> hdf5_localbufferman_ulonglong;
        H5P_LocalBufferManager<BT(float    )> hdf5_localbufferman_float;
        H5P_LocalBufferManager<BT(double   )> hdf5_localbufferman_double;

        /// Function used by print functions to retrieve their local buffer manager object
        template<class T>
        H5P_LocalBufferManager<BT(T)>& get_mybuffermanager(ulong, uint);
        #undef BT

        /// Add PPIDpair to global index list
        void add_PPID_to_list(const PPIDpair&);

        /// Completely reset the PPIDlists (e.g. used when printer is reset)
        void reset_PPID_lists();

        /// Ask the printer for the highest ID number known for a given rank
        /// process (needed for resuming, so the scanner can resume assigning
        /// point ID from this value.
        // TODO: DEPRECATED
        //unsigned long getHighestPointID(const int rank);

        /// Check if PPIDpair exists in global index list
        bool seen_PPID_before(const PPIDpair& ppid);

        /// Function to ensure buffers are all synchronised to the same absolute position
        void synchronise_buffers();

        /// For debugging: check that buffers are synced correctly
        /// Flag sets whether "perfect" sync is required, or whether
        /// some buffers can be ahead by one slot (due to having
        /// performed prints that other buffers have not yet done)
        void check_sync(const std::string& label, const int sync_type, bool checkall);

        #ifdef WITH_MPI

        /// Retrieve MPI communicator object used by this printer
        GMPI::Comm& get_Comm() { return myComm; }
        #endif

        /// Check if the buffers are full and waiting to be emptied
        /// By default this only empties buffers if they are full. Use
        /// flag to force the flush for the finalise buffer dumps.
        void empty_sync_buffers(bool force=false);

        /// Check whether printing to a new parameter space point is about to occur
        /// and perform adjustments needed to prepare the printer.
        void check_for_new_point(const PPIDpair&);

        /// Retrieve index from global lookup table, with error checking
        unsigned long get_global_index(const ulong pointID, const uint mpirank);

        /// Get the name of this printer
        std::string get_printer_name() { return printer_name; }

        /// Get the number of RA write locations known to the primary printer
        /// NOTE: the meaning of this has changed slightly; it is the number of queued
        /// up RA write commands that should exist in the output datasets. The primary
        /// printer no longer tracks all of the IDs for every RA write command.
        unsigned long get_N_RApointIDs() { return primary_printer->reverse_global_index_lookup.size() + primary_printer->RA_dset_offset; }

        /// Move head dataset sync position
        void increment_sync_pos() { sync_pos+=1; }

        /// Clear previous points list
        void clear_previous_points() { std::vector<PPIDpair>().swap(previous_points); } // This technique also shrinks the capacity of the vector, which 'clear' does not do.

        /// Scan for existing temporary files, in preparation for combining them
        /// Should only do this if scan is resuming, and if we are process rank 0.
        void prepare_and_combine_tmp_files();

        //PPIDpair get_highest_PPID_from_HDF5(hid_t group_id);
        std::map<unsigned long, unsigned long long int> get_highest_PPID_from_HDF5(hid_t group_id);

        /// Search the output directory for temporary files (pre-combination)
        std::vector<std::string> find_temporary_files(const bool error_if_inconsistent=false);

        /// Combine temporary hdf5 output files from each process into a single coherent hdf5 file.
        void combine_output_py(const std::vector<std::string> tmp_files, const bool finalcombine); // Python version
        void combine_output(const std::vector<std::string> tmp_files, const bool finalcombine); // Greg version

        /// @}


        /// Helper print functions
        // Used to reduce repetition in definitions of virtual function overloads
        // (useful since there is no automatic type conversion possible)
        template<class T>
        void template_print(T const& value, const std::string& label, const int IDcode, const unsigned int mpirank, const unsigned long pointID)
        {
           // Retrieve the buffer manager for buffers with this type
           auto& buffer_manager = get_mybuffermanager<T>(pointID,mpirank);

           // Extract a buffer from the manager corresponding to this
           auto& selected_buffer = buffer_manager.get_buffer(IDcode, 0, label);

           #ifdef HDEBUG_MODE
             std::cout<<"rank "<<myRank<<", printer "<<this->get_printer_name()<<": printing "<<typeid(T).name()<<", "<<label<<" = "<<value<<std::endl;
             std::cout<<"rank "<<myRank<<", printer "<<this->get_printer_name()<<": pointID="<<pointID<<", mpirank="<<mpirank<<std::endl;
           #endif

           PPIDpair ppid(pointID,mpirank);
           if(synchronised)
           {
             // Write the data to the selected buffer ("just works" for simple numeric types)
             selected_buffer.append(value,ppid);
           }
           else
           {
             // Queue up a desynchronised ("random access") dataset write to previous scan iteration
             if(not seen_PPID_before(ppid))
             {
               add_PPID_to_list(ppid);
             }
             selected_buffer.RA_write(value,ppid,primary_printer->global_index_lookup);
           }
        }

      private:
        // String names for output file and group
        std::string tmp_comb_file; // temporary combined output filename
        std::string tmpfile;   // temporary filename (unique to each process)
        std::string finalfile; // Combined results moved here only upon successful scan completion
        std::string group;     // HDF5 group location to store datasets

        // Handles for HDF5 files and groups containing the datasets
        hid_t file_id;
        hid_t group_id;
        hid_t RA_group_id;

        // Handle to a location in a HDF5 to which the datasets will be written
        // i.e. a file or a group.
        hid_t location_id;
        hid_t RA_location_id;

        /// Pointer to the primary printer object
        // (if this is an auxilliary printer, else it is "this" //NULL)
        HDF5Printer* primary_printer = this; //NULL;

        /// Flag to specify if this is the primary printer or not
        bool is_primary_printer = false;

        /// Flag to disable combination of hdf5 output (user will have to run the combination routines manually)
        bool disable_combine_routines = false;

        /// Map containing pointers to all VertexBuffers contained in this printer
        // Note: Each buffer contains a bool to indicate whether it has done an "append" for the point "lastPointID"
        BaseBufferMap all_my_buffers;

        /// ID of the point that this printer is currently working on.
        // Need this so that we can compute when (at least initial) writing to a model point has ceased
        PPIDpair lastPointID;

        /// Current absolute dataset index
        // i.e. this location in the output dataset is currently the target of print functions
        unsigned long current_dset_position;

        /// Map from pointID,thread pairs to absolute dataset indices
        //  Needed for dataset writes which return to old points.
        std::map<PPIDpair, unsigned long> global_index_lookup;

        // Matching vector for the above, for reverse lookup
        std::vector<PPIDpair> reverse_global_index_lookup;

        /// Offset needed to be added to the reverse lookup in
        /// order for it to match the output dataset position correctly
        unsigned long RA_dset_offset = 0;

        /// Label for printer, mostly for more helpful error messages
        std::string printer_name;

        /// MPI rank and size
        unsigned int myRank;  // Needed even without MPI available, for some default behaviour.
        unsigned int mpiSize; //            "                           "
        #ifdef WITH_MPI
        // Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm myComm;
        #endif

        /// Flag to specify whether all buffers created by this printer
        /// should be synchronised and iterated along with the Gambit
        /// scanner iterations.
        bool synchronised = true;

        /// Flag to trigger "global" write mode for printer
        // i.e. print data will not be associated with parameter space points,
        // but will be "global" data about the whole scan (e.g. max log likelihood
        // found, scan statistics, etc.)
        bool global = false;

        /// Position to start writing new output. Should be zero unless we are in
        /// resume mode.
        //unsigned long startpos = 0; // OBSOLETE

        /// Write position to which output buffers should be synchronised
        unsigned long sync_pos = 0;

        /// In resume mode: storage for PPIDpairs harvested from previous scan data
        std::vector<PPIDpair> previous_points;

      protected:
        /// Things which other printers need access to

        /// Map containing pointers to all VertexBuffers, across all printers
        // Note: Each buffer contains a bool to indicate whether it has done an "append" for the point "lastPointID"
        BaseBufferMap all_buffers;

    };

    /// Macro to help define the buffer manager getter functions
    // Need to use it outside the class body, and be sure to typedef
    // types which can not form part of a valid variable name.
    #define DEFINE_BUFFMAN_GETTER(TYPE)                                        \
      template<>                                                               \
      inline H5P_LocalBufferManager<VertexBufferNumeric1D_HDF5<TYPE,BUFFERLENGTH>>& \
       HDF5Printer::get_mybuffermanager<TYPE>(ulong pointID, uint mpirank) \
      {                                                                        \
         /* If the buffermanger hasn't been initialised, do so now */          \
         if( not CAT(hdf5_localbufferman_,TYPE).ready() )                      \
         {                                                                     \
            CAT(hdf5_localbufferman_,TYPE).init(this,synchronised);            \
         }                                                                     \
                                                                               \
         /* While we are at it, check if the buffers need to be                \
            synchronised to a new point. But only if this printer is running   \
            in "synchronised" mode. */                                         \
         if(synchronised)                                                      \
         {                                                                     \
           check_for_new_point(PPIDpair(pointID, mpirank));                    \
         }                                                                     \
         return CAT(hdf5_localbufferman_,TYPE);                                \
      }

    DEFINE_BUFFMAN_GETTER(int      )
    DEFINE_BUFFMAN_GETTER(uint     )
    DEFINE_BUFFMAN_GETTER(long     )
    DEFINE_BUFFMAN_GETTER(ulong    )
    DEFINE_BUFFMAN_GETTER(longlong )
    DEFINE_BUFFMAN_GETTER(ulonglong)
    DEFINE_BUFFMAN_GETTER(float    )
    DEFINE_BUFFMAN_GETTER(double   )


    /// @{ Templated H5P_LocalBufferManager member functions

    template<class BuffType>
    void H5P_LocalBufferManager<BuffType>::init(HDF5Printer* p, bool sync)
    {
      /* Set global behaviour flag */
      synchronised = sync;

      /* Attempt to attach to printer */
      if(p==NULL)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to initialise a H5P_LocalBufferManager with a null pointer! Need an actual HDF5Printer object in order to work. This is a bug in the HDF5Printer class, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
      if(not ready()) {
        printer = p;
      } else {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to initialise a H5P_LocalBufferManager twice! This is a bug in the HDF5Printer class, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }
    }

    template<class BuffType>
    BuffType& H5P_LocalBufferManager<BuffType>::get_buffer(const int vertexID, const unsigned int aux_i, const std::string& label)
    {
      if(not ready()) {
        std::ostringstream errmsg;
        errmsg << "Error! Tried to retrieve a buffer from a buffer manager without first initialising it! This is a bug in the HDF5Printer class, please report it.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      VBIDpair key;
      key.vertexID = vertexID;
      key.index    = aux_i;

      typename std::map<VBIDpair, BuffType>::iterator it = local_buffers.find(key);

      if( it == local_buffers.end() )
      {
        error_if_key_exists(local_buffers, key, "local_buffers");
        // No local buffer exists for this output stream yet, so make one
        // But check first if another printer manager is already handling this
        // output stream. If so, we relinquish control over it and silence the
        // new output stream.
        bool silence = false;
        #ifdef DEBUG_MODE
          std::cout<<"Preparing to create new print output stream..."<<std::endl;
          std::cout<<"...label = "<<label<<std::endl;
          std::cout<<"...is stream already managed? "<<printer->is_stream_managed(key)<<std::endl;
          std::cout<<"...from printer with name = "<<printer->get_printer_name()<<std::endl;
          std::cout<<"...from printer with name = "<<printer->get_printer_name()<<std::endl;
        #endif
        if( printer->is_stream_managed(key) )
        {
          silence = true;
        }
        #ifdef DEBUG_MODE
          std::cout<<"...is silenced? "<<silence<<std::endl;
        #endif

        // Create the new buffer object
        hid_t loc(-1);
        if(synchronised)
        {
          loc = printer->get_location();
        }
        else // write to the RA group
        {
          loc = printer->get_RA_location();
        }

        local_buffers[key] = BuffType( loc
                                      , label/*deconstruct?*/
                                      , vertexID
                                      , aux_i
                                      , synchronised
                                      , silence
                                      , false /*printer->get_resume() -- In this new version of the HDF5Printer we write temporary files and then combine them at the end of the scan, so each individual buffer no longer needs to be in 'resume' mode, it can just start anew and be combined with the old data later on */
                                      , access /* r/w mode. Buffers can now be used for reading also. */
                                      );

        // Get the new (possibly silenced) buffer back out of the map
        it = local_buffers.find(key);

        // Add a pointer to the new buffer to the full list as well
        if(not silence) printer->insert_buffer( key, it->second );

        // Force increment the buffer to "catch it up" to the current sync
        // position, in case it has been created "late".
        // We subtract one because another increment will happen after
        // the print statement (that triggered the creation of the new
        // buffer) completes.
        if(synchronised) it->second.fast_forward(printer->get_sync_pos()-1);
      }

      if( it == local_buffers.end() )
      {
        std::ostringstream errmsg;
        errmsg << "Error! Failed to retrieve newly created buffer (label="<<label<<") from local_buffers map! Key was: ("<<vertexID<<","<<aux_i<<")"<<std::endl;
        printer_error().raise(LOCAL_INFO, errmsg.str());
      }

      return it->second;
    }

    /// @}


    // Avoid cluttering up "macro namespace"
    #undef DEFINE_BUFFMAN_GETTER
    #undef BT

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(hdf5_v1, HDF5Printer)

  } // end namespace Printers

} // end namespace Gambit

#ifdef DEBUG_MODE
  #undef DEBUG_MODE
#endif

#endif
