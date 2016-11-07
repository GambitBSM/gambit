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

// Boost
#include <boost/preprocessor/seq/for_each_i.hpp>

// Gambit
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/MPITagManager.hpp"
#include "gambit/Printers/VertexBufferBase.hpp"
#include "gambit/Printers/VertexBuffer_mpitags.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer/VertexBufferNumeric1D_HDF5.hpp"
#include "gambit/Printers/printers/hdf5printer/DataSetInterfaceScalar.hpp"
#include "gambit/Elements/printable_types.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/Logs/logger.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"

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
          errmsg << "Error! Supplied key for a VertexBuffer already exists in map (tag="<<tag<<")! This is a bug in the HDF5Printer class, please report it.";
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

      public:
        /// Constructor
        H5P_LocalBufferManager() 
          : printer(NULL) 
          , synchronised(true)
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

        /// Auxilliary mode constructor (for construction in scanner plugins) 
        // **deprecated**
        //HDF5Printer(const Options&, std::string&, bool synchronised);

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
        int getRank();
        void finalise(bool abnormal=false);

        ///@}
     
        /// @{ HDF5Printer-specific functions

        /// Retrieve pointer to HDF5 location to which datasets are added
        hid_t get_location();
        hid_t get_RA_location();

        /// Add a pointer to a new buffer to the global list
        void insert_buffer(VBIDpair& key, VertexBufferBase& newbuffer);

        /// Check if an output stream is already managed by some buffer in some printer
        bool is_stream_managed(VBIDpair& key);

        /// Add PPIDpair to global index list
        void add_PPID_to_list(const PPIDpair&);

        /// Completely reset the PPIDlists (e.g. used when printer is reset)
        void reset_PPID_lists();

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
        /// Reserved tags for MPI messages
        /// First reserved tag is for messages registering/requesting a new tag.
        // enum Tags { TAG_REQ=0; } //defined in hdf5tools.hpp

        /// Retrieve MPI communicator object used by this printer
        GMPI::Comm& get_Comm() { return myComm; }
        #endif  

        // Check if the buffers are full and waiting to be emptied
        // By default this only empties buffers if they are full. Use
        // flag to force the flush for the finalise buffer dumps.
        void empty_sync_buffers(bool force=false);

        /// Check whether printing to a new parameter space point is about to occur
        // and perform adjustments needed to prepare the printer.
        void check_for_new_point(const unsigned long, const unsigned int);
 
        /// Function used by print functions to retrieve their local buffer manager object
        template<class BuffType>
        H5P_LocalBufferManager<BuffType>& get_mybuffermanager(unsigned long pointID, unsigned int mpirank);

        /// Retrieve index from global lookup table, with error checking
        unsigned long get_global_index(const unsigned long pointID, const unsigned int mpirank);
 
        /// Get the name of this printer
        std::string get_printer_name() { return printer_name; }

        /// Get the number of RA write locations known to the primary printer
        /// NOTE: the meaning of this has changed slightly; it is the number of queued
        /// up RA write commands that should exist in the output datasets. The primary
        /// printer no longer tracks all of the IDs for every RA write command.
        unsigned long get_N_RApointIDs() { return primary_printer->reverse_global_index_lookup.size() + primary_printer->RA_dset_offset; }

        /// Get the number of pointIDs know to this printer
        /// (should correspond to the number of "appends" each active buffer has received)
        unsigned long get_sync_pos() { return sync_pos; }
        void increment_sync_pos() { sync_pos+=1; }

        /// Clear previous points list
        void clear_previous_points() { std::vector<PPIDpair>().swap(previous_points); } // This technique also shrinks the capacity of the vector, which 'clear' does not do.

        /// Scan for existing temporary files, in preparation for combining them
        /// Should only do this if scan is resuming, and if we are process rank 0.
        void prepare_and_combine_tmp_files();

        PPIDpair get_highest_PPID_from_HDF5(hid_t group_id);

        /// Search the output directory for temporary files (pre-combination)
        std::vector<std::string> find_temporary_files(const bool error_if_inconsistent=false);

        /// Combine temporary hdf5 output files from each process into a single coherent hdf5 file.
        void combine_output(const std::vector<std::string> tmp_files, const bool finalcombine);

        /// Retrieve a pointer to the primary printer object
        /// This is stored in the base class (BaseBasePrinter) as a pointer of type
        /// BaseBasePrinter, so we need to  



        /// Macro to help declare new buffer managers for various types
        #define NEW_BUFFMAN(BUFFTYPE,NAME)     \
          /* Note: NAME can be anything, but it needs to be unique since it §
             helps to name the buffer manager object */                        \
          H5P_LocalBufferManager<BUFFTYPE> CAT(hdf5_localbufferman_,NAME);     \

        /// Macro to help define the buffer manager getter functions
        // Need to use it outside the class body
        // 
        // The getter functions serve to both retrieve the buffer matching an
        // output stream, and to handle creation of those buffers.
        #define DEFINE_BUFFMAN_GETTER(BUFFTYPE,NAME)                               \
         template<>                                                                \
          inline H5P_LocalBufferManager<BUFFTYPE>&                                 \
           HDF5Printer::get_mybuffermanager<BUFFTYPE>(unsigned long pointID, unsigned int mpirank) \
          {                                                                        \
             /* If the buffermanger hasn't been initialised, do so now */          \
             if( not CAT(hdf5_localbufferman_,NAME).ready() )                      \
             {                                                                     \
                CAT(hdf5_localbufferman_,NAME).init(this,synchronised);            \
             }                                                                     \
                                                                                   \
             /* While we are at it, check if the buffers need to be                \
                synchronised to a new point. But only if this printer is running   \
                in "synchronised" mode. */                                         \
             if(synchronised)                                                      \
             {                                                                     \
               check_for_new_point(pointID, mpirank);                              \
             }                                                                     \
             return CAT(hdf5_localbufferman_,NAME);                                \
          }

        /// @}

        // PRINT FUNCTIONS
        //----------------------------
        // Need to define one of these for every type we want to print!
        // Could use macros again to generate identical print functions 
        // for all types that have a << operator already defined.

        // Types compatible with the template print function
        #define TEMPLATE_TYPES  \
         ALL_INT_TYPES \
         (float)\
         (double)\

        // Types for which custom print functions are defined
        typedef std::map<std::string,double> map_str_dbl; // can't have commas in macro input
        #define NON_TEMPLATE_TYPES \
          (std::vector<double>)    \
          (ModelParameters)        \
          (triplet<double>)        \
          (map_str_dbl)\
          (bool)
          /*(std::vector<bool>)        \
             (std::vector<int>)        */

        // All printable types
        #define HDF5_PRINTABLE_TYPES TEMPLATE_TYPES NON_TEMPLATE_TYPES

        #define DECLARE_PRINT(r,data,ELEM) \
          void _print(ELEM const& value, const std::string& label, const int IDcode, const unsigned int mpirank, const unsigned long pointID); \
                                                                              
        #define DECLARE_PRINT_FUNCTIONS(TYPES) BOOST_PP_SEQ_FOR_EACH(DECLARE_PRINT, _, TYPES)
        DECLARE_PRINT_FUNCTIONS(NON_TEMPLATE_TYPES)       

        /// Helper print functions
        // Used to reduce repetition in definitions of virtual function overloads 
        // (useful since there is no automatic type conversion possible)
        template<class T>
        void template_print(T const& value, const std::string& label, const int IDcode, const unsigned int mpirank, const unsigned long pointID)
        {
           // Define what output format will be used for this type (by choosing an appropriate buffer type)  
           typedef VertexBufferNumeric1D_HDF5<T,BUFFERLENGTH> BuffType;
          
           // Retrieve the buffer manager for buffers with this type
           typedef H5P_LocalBufferManager<BuffType> BuffMan;
           BuffMan& buffer_manager = get_mybuffermanager<BuffType>(pointID,mpirank);

           // Extract a buffer from the manager corresponding to this 
           BuffType& selected_buffer = buffer_manager.get_buffer(IDcode, 0, label); 

           // { debug
           //if(label=="pointID") std::cout << "rank "<<myRank<<", printer "<<this->get_printer_name()<<": printing "<<label<<" = "<<value<<std::endl;
           // }


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
 
        /// @{ Helper macros to write all the print functions which can use the "easy" template

        // The type of the template print function buffers
        #define TEMPLATE_BUFFTYPE(TYPE) VertexBufferNumeric1D_HDF5<TYPE,BUFFERLENGTH>

        #define TEMPLATE_PRINT(r,data,i,elem)                                   \
          NEW_BUFFMAN(TEMPLATE_BUFFTYPE(elem),CAT(template_,i))                 \
          void _print(elem const& value, const std::string& label, const int vID, \
                       const unsigned int mpirank, const unsigned long pointID) \
          {                                                                     \
            template_print(value,label,vID,mpirank,pointID);                    \
          }                                                          

        #define ADD_TEMPLATE_PRINTS                                             \
          BOOST_PP_SEQ_FOR_EACH_I(TEMPLATE_PRINT, _, TEMPLATE_TYPES)

        #define TEMPLATE_BUFFMAN(r,data,i,elem)                                 \
          DEFINE_BUFFMAN_GETTER(TEMPLATE_BUFFTYPE(elem),CAT(template_,i))                          
 
        #define DEFINE_TEMPLATE_BUFFMAN_GETTERS                                 \
          BOOST_PP_SEQ_FOR_EACH_I(TEMPLATE_BUFFMAN, _, TEMPLATE_TYPES)

        ADD_TEMPLATE_PRINTS
        /// @}

        // Add any extra buffermanger declarations here:
        // NEW_BUFFMAN(BUFFTYPE1,NAME1)
        // NEW_BUFFMAN(BUFFTYPE2,NAME2)
        // etc...

        /// Regular print functions
        // Now already declared in macro above
        //void _print(std::vector<double> const&, const std::string&, const int, const unsigned int, const unsigned long);
        //void _print(ModelParameters     const&, const std::string&, const int, const unsigned int, const unsigned long);
        //void _print(triplet<double> const&,     const std::string&, const int, const unsigned int, const unsigned long);

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

        /// Map containing pointers to all VertexBuffers contained in this printer
        // Note: Each buffer contains a bool to indicate whether it has done an "append" for the point "lastPointID"
        BaseBufferMap all_my_buffers;

        /// Map recording which model point this process is working on
        // Need this so that we can compute when (at least initial) writing to a model point has ceased
        // Key: rank; Value: last pointID sent by that rank.
        std::map<unsigned int,unsigned long> lastPointID;

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

    /// Macros which define the getter functions for the buffer managers
    //  Need one of these for every buffer type used by a print function
    //  However, some of them are automatically created by the 
    //  DEFINE_TEMPLATE_BUFFMAN_GETTERS macro, specifically buffer for
    //  the types listed
    //  in the TEMPLATE_TYPES list. It will be an error to define the
    //  getter twice for a buffer type, so check that any new buffer 
    //  types are not already covered.
    //  Note that the buffer type is different from the data type, e.g.
    //  the buffer for single doubles used in the template print function
    //  is:
    //
    //    typedef VertexBufferNumeric1D_HDF5<double,BUFFERLENGTH> BuffType;
    //
    //  Note also that new buffer types will need to have the buffer manager
    //  getter declared in the HDF5Printer class body, using the 
    //  NEW_BUFFMAN macro.
    //  If this is done correctly, you can then retrieve the buffermanager
    //  for your buffer type using:
    //
    //   typedef H5P_LocalBufferManager<BuffType> BuffMan;
    //   BuffMan& buffer_manager = get_mybuffermanager<BuffType>(pointID,mpirank);
    //

    // Define the buffermanager getter specialisations
    DEFINE_TEMPLATE_BUFFMAN_GETTERS
    // DEFINE_BUFFMAN_GETTER(BUFFTYPE1,NAME1)
    // DEFINE_BUFFMAN_GETTER(BUFFTYPE2,NAME2)
    // etc..

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(hdf5, HDF5Printer)
     
  } // end namespace Printers
} // end namespace Gambit

#undef DEBUG_MODE

#endif
