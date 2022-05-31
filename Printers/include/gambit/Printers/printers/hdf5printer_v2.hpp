//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 printer version 2
///
///  This version of the HDF5 printer is a near
///  complete rewrite of the HDF5 printer, based
///  on a 'transaction' concept. Writes are
///  performed on a single output file in
///  'transactions', during which the file is
///  locked and cannot be accessed by other
///  processes. The idea is based on how the
///  SQLitePrinter works, though much more manual
///  work is required since HDF5 does not natively
///  work via transactions, unlike SQLite.
///
///  P.S. Also now supports dynamic changing of the
///  buffer size!
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jan
///
///  *********************************************


#ifndef __hdf5printer_v2_hpp__
#define __hdf5printer_v2_hpp__

#include <algorithm>
#include <set>
#include <iterator>
#include <string>

// BOOST_PP
#include <boost/preprocessor/seq/for_each_i.hpp>

// GAMBIT
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5types.hpp"
#include "gambit/Logs/logger.hpp"

// Activate extra debug logging (warning, LOTS of output)
//#define HDF5PRINTER2_DEBUG

namespace Gambit
{
  namespace Printers
  {

    typedef unsigned int uint;
    typedef unsigned long ulong;
    typedef long long longlong;
    typedef unsigned long long ulonglong;

    // DEBUG h5v2_BLOCK message counters
    //static int recv_counter;
    //static int send_counter;

    /// Length of chunks in chunked HDF5 dataset. Affects write/retrieval performance for blocks of data of various sizes.
    /// It is set to an "intermediate" sort of size since that seems to work well enough.
    static const std::size_t HDF5_CHUNKLENGTH = 100;

    /// Dimension of output dataset. We are only using 1D datasets for simplicity.
    static const std::size_t DSETRANK = 1;

    /// Largest allowed size of buffers. Size can be dynamically set from 1 to this number.
    static const std::size_t MAX_BUFFER_SIZE = 100000;

    /// MPI tags for HDF5 printer v2
    const int h5v2_bufname(10);
    const int h5v2_bufdata_points(11);
    const int h5v2_bufdata_ranks(12);
    const int h5v2_bufdata_valid(13);
    const int h5v2_bufdata_type(14);
    const int h5v2_bufdata_values(15);
    // Message block end tag:
    // 1 means "there is another block of messages to receive"
    // 0 means "there are no more blocks of messages to receive"
    const int h5v2_BLOCK(30);
    // "Begin sending data" tag
    const int h5v2_BEGIN(31);

    // The 'h5v2_bufdata_type' messages send an integer encoding
    // the datatype for the h5v2_bufdata_values messages
    // Need a unique integer for each type. We can encode these
    // with a template function:

    template<class T>
    std::set<T> set_diff(const std::set<T>& set1, const std::set<T>& set2)
    {
        std::set<T> result;
        std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
            std::inserter(result, result.end()));
        return result;
    }

    /// Base class for interfacing to a HDF5 dataset
    class HDF5DataSetBase
    {
      public:
         HDF5DataSetBase(const std::string& name, const hid_t hdftype_id);
         HDF5DataSetBase(const std::string& name);
         virtual ~HDF5DataSetBase();

         /// Open dataset on disk and obtain HDF5 handles
         void open_dataset(hid_t location_id);

         /// Close dataset on disk and release handles
         void close_dataset();

         /// Create a new dataset at the specified location
         /// (implemented in derived class since need to know the type)
         virtual void create_dataset(hid_t location_id) = 0;

         /// Retrieve the current size of the dataset on disk
         std::size_t get_dset_length() const;

         /// Check if our dataset exists on disk with the required name at the given location
         bool dataset_exists(const hid_t loc_id);

         /// Ensure that a correctly named dataset exists at the target location with the specified length
         void ensure_dataset_exists(const hid_t loc_id, const std::size_t length);

         /// Extend dataset to the specified size, filling it with default values
         void extend_dset_to(const std::size_t new_size);

         /// Retrieve name of the dataset we are supposed to access
         std::string myname() const;

         /// Retrieve the integer type ID for this dataset
         int get_type_id() const;

         /// Retrieve the HDF5 type ID for this dataset
         hid_t get_hdftype_id() const;

         /// Variable tracking whether the dataset is known to exist in the output file yet
         bool get_exists_on_disk() const;
         void set_exists_on_disk();

      private:

         // Dataset and chunk dimension specification arrays
         // We are only using 1D output datasets for simplicity.
         // Values are only valid if 'is_open==true'
         hsize_t  dims     [DSETRANK];
         hsize_t  maxdims  [DSETRANK];
         hsize_t  chunkdims[DSETRANK];
         //hsize_t  slicedims[DSETRANK];
         // Note, dims[0] is current size of dataset, so next unused index is equal to dims[0]

         /// Name of the dataset in the hdf5 file
         std::string _myname;

         /// Flag to let us known if the dataset is open
         bool is_open;

         /// Variable tracking whether the dataset is known to exist in the output file yet
         bool exists_on_disk;

      protected:

         /// HDF5 dataset identifer
         hid_t dset_id;

         /// Enforce that the dataset must be open for whatever follows (or else an error is thrown)
         void ensure_dataset_is_open() const;

         /// Retrieve the dataset ID for the currently open dataset
         hid_t get_dset_id() const;

         /// Set the variable that tracks the (virtual) dataset size on disk
         //void set_dset_length(const std::size_t newsize);

         /// Extend dataset by the specified amount
         void extend_dset_by(const std::size_t extend_by);

         /// Obtain memory and dataspace identifiers for writing to a hyperslab in the dataset
         std::pair<hid_t,hid_t> select_hyperslab(std::size_t offset, std::size_t length) const;

         /// HDF5 type ID for this dataset
         hid_t hdftype_id;

         /// Integer identifier for the template type of this dataset (determined by derived type)
         int type_id;
    };

    /// Constructable class for doing basic operations on a HDF5 dataset
    class HDF5DataSetBasic: public HDF5DataSetBase
    {
      public:
          HDF5DataSetBasic(const std::string& name);
          void create_dataset(hid_t location_id);
     };

    /// Class for interfacing to a HDF5 dataset of fixed type
    template<class T>
    class HDF5DataSet: public HDF5DataSetBase
    {
      public:

         /// Constructor
         HDF5DataSet(const std::string& name)
           : HDF5DataSetBase(name,get_hdf5_data_type<T>::type())
         {}

         /// Write a vector of data to disk at the target position
         std::size_t write_vector(const hid_t loc_id, const std::vector<T>& data, const std::size_t target_pos, const bool force=false)
         {
             open_dataset(loc_id);
             bool all_data_written=false;
             T buffer[MAX_BUFFER_SIZE];
             std::size_t i = 0;
             std::size_t offset = target_pos;
             //std::cout<<"Preparing to write "<<data.size()<<" elements to dataset "<<myname()<<" at position "<<target_pos<<std::endl;
             while(not all_data_written)
             {
                 std::size_t j;
                 // Copy data into buffer up to MAX_BUFFER_SIZE
                 for(j=0;
                     (j<MAX_BUFFER_SIZE) && (i<data.size());
                     ++j, ++i)
                 {
                     // DEBUG inspect buffer
                     //std::cout<< "   buffer["<<j<<"] = data.at("<<i<<") = "<<data.at(i)<<std::endl;
                     buffer[j] = data.at(i);
                 }
                 //std::cout<<"    i="<<i<<", j="<<j<<", data.size()="<<data.size()<<", MAX_BUFFER_SIZE="<<MAX_BUFFER_SIZE<<std::endl;
                 // Write buffer to disk
                 //std::cout<<"Writing "<<j<<" elements to dataset "<<myname()<<" at position "<<offset<<std::endl;
                 write_buffer(buffer,j,offset,force);
                 offset += j;
                 if(i==data.size()) all_data_written = true;
             }
             std::size_t new_dset_size = get_dset_length();
             close_dataset();

             // Report new size of the dataset so that we can check that all datasets are the same length
             return new_dset_size;
         }

         /// Write a block of data to disk at the end of the dataset
         /// This is the lower-level function. There is a fixed-size
         /// buffer that cannot be exceeded. If more data than
         /// MAX_BUFFER_SIZE is to be written then the 'write_vector'
         /// function will split it up and write it in pieces.
         /// If force=true then target_pos can be used to overwrite data
         void write_buffer(const T (&buffer)[MAX_BUFFER_SIZE], const std::size_t length, const std::size_t target_pos, const bool force=false)
         {
             if(length>MAX_BUFFER_SIZE)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Received buffer with length ("<<length<<") greater than MAX_BUFFER_SIZE ("<<MAX_BUFFER_SIZE<<") while tring to perform block write for dataset (name="<<myname()<<"). The input to this function is therefore invalid.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }
             if(length==0)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Received buffer of length zero! This will cause an error when trying to select element for writing, and there is no point calling this function with no points to write anyway. Please review the input to this function (error occurred while tring to perform block write for dataset (name="<<myname()<<"))";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             // DEBUG dump whole buffer up to length to check it
             //for(std::size_t i=0;i<length;++i)
             //{
             //    std::cout<<"    buffer["<<i<<"] = "<<buffer[i]<<std::endl;
             //}

             ensure_dataset_is_open();

             // Get the C interface identifier for the type of the output dataset
             hid_t expected_dtype = get_hdftype_id();
             hid_t dtype = H5Dget_type(get_dset_id()); // type with which the dset was created
             if(not H5Tequal(dtype, expected_dtype))
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Tried to write to dataset (name="<<myname()<<") with type id "<<dtype<<" but expected it to have type id "<<expected_dtype<<". This is a bug, please report it.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             std::size_t required_size = target_pos+length;
             // Check that target position is allowed
             if(target_pos < get_dset_length())
             {
                 if(force)
                 {
                     if(required_size > get_dset_length())
                     {
                         // Some overlap into unused space, partial dataset extension required.
                         extend_dset_to(required_size);
                     }
                     // Else whole target block is inside current dataset size. No extension required.
                 }
                 else
                 {
                     std::ostringstream errmsg;
                     errmsg << "Error! Tried to write block to dataset (name="<<myname()<<"), but target index ("<<target_pos<<") is inside the current dataset extents (dset size="<<get_dset_length()<<"), i.e. some of the target slots are already used! This is a bug, please report it.";
                     printer_error().raise(LOCAL_INFO, errmsg.str());
                 }
             }
             else
             {
                 // Target block fully outside current dataset extents. Extend to fit.
                 extend_dset_to(required_size);
             }

             // Select output hyperslab
             // (this also determines what data will be read out of the buffer)
             std::pair<hid_t,hid_t> selection_ids = select_hyperslab(target_pos,length);
             hid_t memspace_id = selection_ids.first;
             hid_t dspace_id   = selection_ids.second;

             // Write the data to the hyperslab.
             herr_t status = H5Dwrite(get_dset_id(), get_hdftype_id(), memspace_id, dspace_id, H5P_DEFAULT, buffer);
             if(status<0)
             {
                std::ostringstream errmsg;
                errmsg << "Error writing new chunk to dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dwrite failed." << std::endl;
                printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             // Release the hyperslab IDs
             H5Sclose(dspace_id);
             H5Sclose(memspace_id);

             //std::cout<<"write_buffer finished; new dataset size is: "<<get_dset_length()<<std::endl;
         }

         /// Write data to disk at specified positions
         void write_random(const hid_t loc_id, const std::map<std::size_t,T>& data)
         {
             open_dataset(loc_id);
             bool all_data_written=false;
             T       buffer[MAX_BUFFER_SIZE];
             hsize_t coords[MAX_BUFFER_SIZE];
             auto it = data.begin();
             while(not all_data_written)
             {
                 // Copy data into buffer up to MAX_BUFFER_SIZE
                 std::size_t j;
                 for(j=0;
                     (j<MAX_BUFFER_SIZE) && (it!=data.end());
                     ++j, ++it)
                 {
                     buffer[j] = it->second;
                     coords[j] = it->first;
                 }
                 // Write buffer to disk
                 if(j>0) write_RA_buffer(buffer,coords,j);
                 if(it==data.end()) all_data_written = true;
             }
             close_dataset();
         }

         /// Write a buffer of data to disk at the specified positions (must be within current dataset extents)
         void write_RA_buffer(const T (&buffer)[MAX_BUFFER_SIZE], const hsize_t (&coords)[MAX_BUFFER_SIZE], std::size_t npoints)
         {
             if(npoints>MAX_BUFFER_SIZE)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Received npoints ("<<npoints<<") greater than MAX_BUFFER_SIZE ("<<MAX_BUFFER_SIZE<<") while tring to perform RA write for dataset (name="<<myname()<<"). The input to this function is therefore invalid.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }
             if(npoints==0)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Received npoints=0! This will cause an error when trying to select element for writing, and there is no point calling this function with no points to write anyway. Please review the input to this function (error occurred while tring to perform RA write for dataset (name="<<myname()<<"))";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             ensure_dataset_is_open();

             bool error_occurred = false; // simple error flag

             // DEBUG: check coords array
             //for(std::size_t i=0; i<npoints; i++) std::cout<<"coords["<<i<<"] = "<<coords[i]<<std::endl;

             // Check that no data is to be written outside the current dataset extents. This
             // function is only for writing back to points that already exist!
             std::size_t max_coord = *std::max_element(coords,coords+npoints);
             if(max_coord > get_dset_length())
             {
                 std::ostringstream errmsg;
                 errmsg<<"Attempted to perform RA write to a point outside the current dataset extents (max_coord="<<max_coord<<", dset_length="<<get_dset_length()<<")! The dataset should be resized prior to calling this function, so this is a bug, please report it.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             // Dataset size in memory
             static const std::size_t MDIM_RANK = 1;
             hsize_t mdim[] = {npoints};

             // Dataspace for the output values
             hid_t dspace = H5Screate_simple(MDIM_RANK, mdim, NULL);
             if(dspace<0) error_occurred = true;

             // Get the C interface identifier for a copy of the dataspace
             // of the dataset
             hid_t dspace_id = H5Dget_space(get_dset_id());
             if(dspace_id<0) error_occurred = true;

             // Select the target write points in the file dataspace
             hid_t errflag = H5Sselect_elements(dspace_id, H5S_SELECT_SET, npoints, coords);
             if(errflag<0) error_occurred = true;

             // Get the C interface identifier for the type of the output dataset
             hid_t expected_dtype = get_hdftype_id();
             hid_t dtype = H5Dget_type(get_dset_id()); // type with which the dset was created
             if(not H5Tequal(dtype, expected_dtype))
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Tried to write to dataset (name="<<myname()<<") with type id "<<dtype<<" but expected it to have type id "<<expected_dtype<<". This is a bug, please report it.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             // Write data to selected points
             // (H5P_DEFAULT specifies some transfer properties for the I/O
             //  operation. These are the default values, probably are ok.)
             hid_t errflag2 = H5Dwrite(get_dset_id(), dtype, dspace, dspace_id, H5P_DEFAULT, buffer);

             if(errflag2<0) error_occurred = true;

             if(error_occurred)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error! Failed to write desynchronised buffer data to file! (dataset name="<<myname()<<")"<<std::endl
                        << "Error flags were:" << std::endl
                        << "  dspace   : " << dspace << std::endl
                        << "  dspace_id: " << dspace_id << std::endl
                        << "  errflag  : " << errflag << std::endl
                        << "  errflag2 : " << errflag2 << std::endl
                        << "Variables:" << std::endl
                        << "  dtype = " << dtype;
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             H5Tclose(dtype);
             H5Sclose(dspace_id);
             H5Sclose(dspace);
         }

         /// Extract a data slice from the linked dataset
         std::vector<T> get_chunk(std::size_t offset, std::size_t length) const
         {
             // Buffer to receive data (and return from function)
             std::vector<T> chunkdata(length);

             // Select hyperslab
             std::pair<hid_t,hid_t> selection_ids = select_hyperslab(offset,length);
             hid_t memspace_id = selection_ids.first;
             hid_t dspace_id   = selection_ids.second;

             // Buffer to receive data
             void* buffer = &chunkdata[0]; // pointer to contiguous memory within the buffer vector

             // Get the data from the hyperslab.
             herr_t err_read = H5Dread(get_dset_id(), get_hdftype_id(), memspace_id, dspace_id, H5P_DEFAULT, buffer);

             if(err_read<0)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error retrieving chunk (offset="<<offset<<", length="<<length<<") from dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dread failed." << std::endl;
                 errmsg << "  offset+length = "<< offset+length << std::endl;
                 errmsg << "  dset_length() = "<< get_dset_length() << std::endl;
                 printer_error().raise(LOCAL_INFO, errmsg.str());
             }

             H5Sclose(dspace_id);
             H5Sclose(memspace_id);

             return chunkdata;
         }

         /// Clear all data on disk for this dataset
         /// Note; this just sets all values to defaults,
         /// it doesn't delete or resize the dataset
         void reset(hid_t loc_id)
         {
             if(dataset_exists(loc_id))
             {
                 open_dataset(loc_id);
                 std::size_t remaining_length = get_dset_length();
                 close_dataset();
                 std::size_t target_pos = 0;
                 while(remaining_length>0)
                 {
                     std::vector<T> zero_buffer;
                     if(remaining_length>=MAX_BUFFER_SIZE)
                     {
                         zero_buffer = std::vector<T>(MAX_BUFFER_SIZE);
                         remaining_length -= MAX_BUFFER_SIZE;
                     }
                     else
                     {
                         zero_buffer = std::vector<T>(remaining_length);
                         remaining_length = 0;
                     }
                     write_vector(loc_id, zero_buffer, target_pos, true);
                     target_pos += MAX_BUFFER_SIZE;
                 }
             }
             // else the dataset doesn't even exist yet (no buffer flushes have occurred yet),
             // so don't need to reset anything.
         }

         /// Create a new dataset at the specified location
         void create_dataset(hid_t location_id);

    };

    /// Create a (chunked) dataset
    template<class T>
    void HDF5DataSet<T>::create_dataset(hid_t location_id)
    {
        hsize_t  dims     [DSETRANK];
        hsize_t  maxdims  [DSETRANK];
        hsize_t  chunkdims[DSETRANK];
        //hsize_t  slicedims[DSETRANK];

        // Compute initial dataspace and chunk dimensions
        dims[0] = 0; // Empty to start
        maxdims[0] = H5S_UNLIMITED; // No upper limit on number of records allowed in dataset
        chunkdims[0] = HDF5_CHUNKLENGTH;
        //slicedims[0] = 1; // Dimensions of a single record in the data space

        // Create the data space
        hid_t dspace_id = H5Screate_simple(DSETRANK, dims, maxdims);
        if(dspace_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Screate_simple failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Object containing dataset creation parameters
        hid_t cparms_id = H5Pcreate(H5P_DATASET_CREATE);
        if(cparms_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Pcreate failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        herr_t status = H5Pset_chunk(cparms_id, DSETRANK, chunkdims);
        if(status<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Pset_chunk failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Check if location id is invalid
        if(location_id==-1)
        {
            std::ostringstream errmsg;
            errmsg << "Error! Tried to create hdf5 dataset (with name=\""<<myname()<<"\") at undefined location (location_id was -1). Please check that calling code supplied a valid location handle. This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Create the dataset
        hid_t dset_id = H5Dcreate2(location_id, myname().c_str(), get_hdftype_id(), dspace_id, H5P_DEFAULT, cparms_id, H5P_DEFAULT);
        if(dset_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name=\""<<myname()<<"\") in HDF5 file. Dataset with same name may already exist";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Release the dataspace IDs
        H5Sclose(dspace_id);
        H5Pclose(cparms_id);
        H5Dclose(dset_id);

        // Register that the dataset now exists on disk
        set_exists_on_disk();
    }


    /// Base class for buffers
    class HDF5BufferBase
    {
      public:

        /// Constructor
        HDF5BufferBase(const std::string& name, const bool sync);

        /// Destructor
        virtual ~HDF5BufferBase() {}

        /// Report name of dataset for which we are the buffer
        std::string dset_name() const;

        /// Report whether the dataset for which we are the buffer is known to exist on disk yet
        virtual bool exists_on_disk() const = 0;

        /// Make sure buffer includes the input point (data will be set as 'invalid' unless given elsewhere)
        virtual void update(const PPIDpair& ppid) = 0;

        /// Empty buffer to disk as a block
        virtual void block_flush(const hid_t loc_id, const std::vector<PPIDpair>& order, const std::size_t target_pos) = 0;

        /// Empty buffer to disk as arbitrarily positioned data
        virtual void random_flush(const hid_t loc_id, const std::map<PPIDpair,std::size_t>& position_map) = 0;

        // Retrieve buffer data in specified order (leaving it empty!) along with type ID in
        // As a double.
        virtual std::pair<std::vector<double>,std::vector<int>> flush_to_vector_dbl(const std::vector<PPIDpair>& order) = 0;
        // int version
        virtual std::pair<std::vector<long>,std::vector<int>> flush_to_vector_int(const std::vector<PPIDpair>& order) = 0;

#ifdef WITH_MPI
        /// Send buffer contents to another process
        virtual void MPI_flush_to_rank(const unsigned int r) = 0;

#endif

        /// Make sure datasets exist on disk with the correct name and size
        virtual void ensure_dataset_exists(const hid_t loc_id, const std::size_t length) = 0;

        /// Clear all data in memory ***and on disk*** for this buffer
        virtual void reset(hid_t loc_id) = 0;

        // Report whether this buffer is synchronised
        bool is_synchronised() const;

        // Report the number of items currently in the buffer;
        virtual std::size_t N_items_in_buffer() = 0;

        /// Report all the points in this buffer
        std::set<PPIDpair> get_points_set() const;

        /// Retrieve the integer type ID for this dataset
        virtual int get_type_id() const = 0;

      private:

        /// Name of dataset for which this object is the buffer
        std::string _dset_name;

        /// Flag to tell us whether this buffer should perform block writes
        /// to the output dataset, or look up and overwrite existing points.
        bool synchronised;

      protected:

        /// Set detailing what points are in the buffer
        std::set<PPIDpair> buffer_set;

        /// Buffer specifying whether the data in the primary buffer is "valid".
        std::map<PPIDpair,int> buffer_valid;
    };

    /// Class to manage buffer for a single output label
    template<class T>
    class HDF5Buffer: public HDF5BufferBase
    {
      public:

        /// Constructor
        HDF5Buffer(const std::string& name, const bool sync, const std::vector<PPIDpair>& buffered_points
#ifdef WITH_MPI
          // Gambit MPI communicator context for use within the hdf5 printer system
        , GMPI::Comm& comm
#endif
        )
          : HDF5BufferBase(name,sync)
          , my_dataset(name)
          , my_dataset_valid(name+"_isvalid")
#ifdef WITH_MPI
          , myComm(comm)
#endif
        {
           // Add points known to other buffers (as 'invalid' data, for synchronisation purposes)
           for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it)
           {
              update(*it);
           }
        }

        /// Make sure buffer includes the specified point (data will be set as 'invalid' unless given elsewhere)
        void update(const PPIDpair& ppid)
        {
            buffer[ppid]; // Create point with default value if it doesn't exist
            buffer_set.insert(ppid);
            auto it = buffer_valid.find(ppid);
            // If point not already in the buffer, set it as invalid
            if(it==buffer_valid.end())
            {
                buffer_valid[ppid] = 0;
                // DEBUG
                //std::cout<<"Set point "<<ppid<<" to 'invalid' for buffer "<<dset_name()<<std::endl;
            }
        }

        /// Insert data to print buffer at the specified point (overwrite if it already exists in the buffer)
        void append(T const& value, const PPIDpair& ppid)
        {
            buffer      [ppid] = value;
            buffer_valid[ppid] = 1;
            buffer_set.insert(ppid);
            //logger()<<" ***Added valid data "<<value<<" to point "<<ppid<<" in buffer "<<dset_name()<<std::endl;
        }

        /// Empty the buffer to disk as block with the specified order into the target position
        /// (only allowed if target_pos is beyond the current end of the dataset!)
        void block_flush(const hid_t loc_id, const std::vector<PPIDpair>& order, const std::size_t target_pos)
        {
            // Make sure output order is same size as the buffer to be output
            if(order.size() != buffer.size())
            {
                std::ostringstream errmsg;
                errmsg << "Supplied buffer ordering vector is not the same size as the buffer (buffer.size()="<<buffer.size()<<", order.size()="<<order.size()<<"; dset_name()="<<dset_name()<<"). This is a bug, please report it." <<std::endl;
                errmsg << "Extra debug information:" << std::endl;
                errmsg << "  buffer.size()       = "<<buffer.size()<<std::endl;
                errmsg << "  buffer_valid.size() = "<<buffer_valid.size()<<std::endl;
                errmsg << "  buffer_set.size() = "<<buffer_set.size()<<std::endl;
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            // Need to keep track of whether buffer points have been added to the ordered output
            std::set<PPIDpair> done;

            // Create a vector version of the buffer in the specified order
            std::vector<T> ordered_buffer;
            std::vector<int> ordered_buffer_valid;
            for(auto ppid_it=order.begin(); ppid_it!=order.end(); ++ppid_it)
            {
                if(done.count(*ppid_it)!=0)
                {
                    std::ostringstream errmsg;
                    errmsg << "Supplied buffer ordering vector contains a duplicate PPIDpair! This is a bug, please report it.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                ordered_buffer      .push_back(buffer      .at(*ppid_it));
                ordered_buffer_valid.push_back(buffer_valid.at(*ppid_it));
                done.insert(*ppid_it);
            }

            // Check if any points were not added to the ordered buffer
            std::set<PPIDpair> not_done = set_diff(buffer_set,done);

            if(not_done.size()>0)
            {
                std::ostringstream errmsg;
                errmsg << "Supplied buffer ordering vector does not specify order positions for all points in the buffer! This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            if(ordered_buffer.size() != buffer.size())
            {
                std::ostringstream errmsg;
                errmsg << "The ordered buffer we just constructed is not the same size as the original buffer! This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            // Perform dataset writes
        #ifdef HDF5PRINTER2_DEBUG
            logger()<<LogTags::printers<<LogTags::debug;
            logger()<<"Writing block of data to disk for dataset "<<dset_name()<<std::endl;
            logger()<<" Data to write (to target_pos="<<target_pos<<"):"<<std::endl;
            for(auto it=ordered_buffer.begin(); it!=ordered_buffer.end(); ++it)
            {
                logger()<<"   "<<*it<<std::endl;
            }
            logger()<<EOM;
            #endif

            std::size_t newsize   = my_dataset      .write_vector(loc_id,ordered_buffer      ,target_pos);
            std::size_t newsize_v = my_dataset_valid.write_vector(loc_id,ordered_buffer_valid,target_pos);
            if(newsize!=newsize_v)
            {
                std::ostringstream errmsg;
                errmsg<<"Inconsistent dataset sizes detected after buffer flush! (newsize="<<newsize<<", newsize_v="<<newsize_v<<")";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }

            // Clear buffer variables
            buffer      .clear();
            buffer_valid.clear();
            buffer_set.clear();
        }

        /// Empty the buffer to disk as "random access" data at pre-existing positions matching the point IDs
        /// May not completely empty the buffer; points will be removed from the buffer if they are included
        /// in the supplied position map.
        void random_flush(const hid_t loc_id, const std::map<PPIDpair,std::size_t>& position_map)
        {
            std::map<std::size_t,T> pos_buffer;
            std::map<std::size_t,int> pos_buffer_valid;

            // DEBUG inspect buffer
            //for(auto it=buffer.begin(); it!=buffer.end(); ++it)
            //{
            //    std::cout<<"buffer["<<it->first<<"] = "<<it->second<<std::endl;
            //}

            for(auto it=position_map.begin(); it!=position_map.end(); ++it)
            {
                const PPIDpair& ppid = it->first;
                const std::size_t& position = it->second;
                auto bit = buffer      .find(ppid);
                auto vit = buffer_valid.find(ppid);
                if(bit==buffer.end() or vit==buffer_valid.end())
                {
                    std::ostringstream errmsg;
                    errmsg<<"Could not find point "<<ppid<<" in buffer! This is a bug, please report it."<<std::endl;
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                if(vit->second) // I think there is no reason to write the RA data to disk if it is invalid. Buffers should have been reset if need to clear points.
                {
                    pos_buffer      [position] = bit->second;
                    pos_buffer_valid[position] = vit->second;
                }
                // Erase point from buffer
                buffer      .erase(bit);
                buffer_valid.erase(vit);
                buffer_set.erase(ppid);
            }
            // Perform dataset writes
            my_dataset      .write_random(loc_id, pos_buffer      );
            my_dataset_valid.write_random(loc_id, pos_buffer_valid);
        }

        /// Clear all data in the buffer ***and on disk***
        /// Only allowed for "random access" buffers
        void reset(hid_t loc_id)
        {
            if(not is_synchronised())
            {
                // Only need to clear the "validity" dataset
                // Doesn't matter what values are in the main datasets
                // once they are marked as 'invalid'.
                buffer      .clear();
                buffer_valid.clear();
                buffer_set.clear();
                //my_dataset      .reset(loc_id);
                my_dataset_valid.reset(loc_id);
            }
            else
            {
                std::ostringstream errmsg;
                errmsg<<"Reset called on buffer for data label "<<dset_name()<<", however this output stream is marked as 'synchronised'. It therefore cannot be reset! This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }

        /// Make sure datasets exist on disk with the correct name and size
        void ensure_dataset_exists(const hid_t loc_id, const std::size_t length)
        {
            my_dataset      .ensure_dataset_exists(loc_id,length);
            my_dataset_valid.ensure_dataset_exists(loc_id,length);
        }

        /// Report whether the dataset for which we are the buffer exists on disk yet
        bool exists_on_disk() const
        {
            return my_dataset.get_exists_on_disk();
            // TODO: Should make sure that 'valid' dataset also exists on disk
        }

        // Report the number of items currently in the buffer;
        std::size_t N_items_in_buffer()
        {
            /// Might as well check the internal consistency of this buffer while we are at it
            if( buffer.size()!=buffer_set.size()
             or buffer.size()!=buffer_valid.size())
            {
                std::ostringstream errmsg;
                errmsg<<"Internal inconsistency detected in buffer for dataset "<<dset_name()<<"; the following variables should all be the same size, but are not:"<<std::endl;
                errmsg<<"  buffer      .size() = "<<buffer      .size()<<std::endl;
                errmsg<<"  buffer_valid.size() = "<<buffer_valid.size()<<std::endl;
                errmsg<<"  buffer_set  .size() = "<<buffer_set  .size()<<std::endl;
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            return buffer.size();
        }

#ifdef WITH_MPI
        // Send buffer contents to a different process
        void MPI_flush_to_rank(const unsigned int r)
        {
            if(buffer.size()>0)
            {
                // Get name of the dataset this buffer is associated with
                std::string namebuf = dset_name();
                // Copy point data and values into MPI send buffer
                std::vector<unsigned long> pointIDs;
                std::vector<unsigned int> ranks; // Will assume all PPIDpairs are valid. I think this is fine to do...
                std::vector<int> valid; // We have to send the invalid points too, to maintain buffer synchronicity
                std::vector<T> values;
                int type(h5v2_type<T>()); // Get integer identifying the type of the data values
                int more_buffers = 1; // Flag indicating that there is a block of data to receive
                for(auto it=buffer.begin(); it!=buffer.end(); ++it)
                {
                    pointIDs.push_back(it->first.pointID);
                    ranks   .push_back(it->first.rank);
                    valid   .push_back(buffer_valid.at(it->first));
                    values  .push_back(it->second);
                }

                // Debug info
        #ifdef HDF5PRINTER2_DEBUG
                logger()<<LogTags::printers<<LogTags::debug<<"Sending points for buffer "<<dset_name()<<std::endl
                                                           <<" (more_buffers: "<<more_buffers<<")"<<std::endl;
                for(std::size_t i=0; i<buffer.size(); ++i)
                {
                    logger()<<"   Sending point ("<<ranks.at(i)<<", "<<pointIDs.at(i)<<")="<<values.at(i)<<" (valid="<<valid.at(i)<<")"<<std::endl;
                }
                logger()<<EOM;
                #endif

                // Send the buffers
                std::size_t Npoints = values.size();
                myComm.Send(&more_buffers, 1, r, h5v2_BLOCK);
                //std::cerr<<myComm.Get_rank()<<": sent "<<more_buffers<<std::endl;
                //send_counter+=1;
                myComm.Send(&namebuf[0] , namebuf.size(), MPI_CHAR, r, h5v2_bufname);
                myComm.Send(&type       , 1      , r, h5v2_bufdata_type);
                myComm.Send(&values[0]  , Npoints, r, h5v2_bufdata_values);
                myComm.Send(&pointIDs[0], Npoints, r, h5v2_bufdata_points);
                myComm.Send(&ranks[0]   , Npoints, r, h5v2_bufdata_ranks);
                myComm.Send(&valid[0]   , Npoints, r, h5v2_bufdata_valid);

                // Clear buffer variables
                buffer      .clear();
                buffer_valid.clear();
                buffer_set  .clear();
            }
        }

        // Receive buffer contents from a different process
        // (MasterBuffer should have received the name, type, and size of the
        // buffer data, and used this to construct/retrieve this buffer.
        // We then collect the buffer data messages)
        void MPI_recv_from_rank(unsigned int r, std::size_t Npoints)
        {
            /// MPI buffers
            std::vector<unsigned long> pointIDs(Npoints);
            std::vector<unsigned int> ranks(Npoints);
            std::vector<int> valid(Npoints);
            std::vector<T> values(Npoints);

            // Receive buffer data
            myComm.Recv(&values[0]  , Npoints, r, h5v2_bufdata_values);
            myComm.Recv(&pointIDs[0], Npoints, r, h5v2_bufdata_points);
            myComm.Recv(&ranks[0]   , Npoints, r, h5v2_bufdata_ranks);
            myComm.Recv(&valid[0]   , Npoints, r, h5v2_bufdata_valid);

            // Pack it into this buffer
        #ifdef HDF5PRINTER2_DEBUG
            logger()<<LogTags::printers<<LogTags::debug<<"Adding points to buffer "<<dset_name()<<std::endl;
            for(std::size_t i=0; i<Npoints; ++i)
            {
                // Extra Debug
                logger()<<"   Adding received point ("<<ranks.at(i)<<", "<<pointIDs.at(i)<<")="<<values.at(i)<<" (valid="<<valid.at(i)<<")"<<std::endl;
                PPIDpair ppid(pointIDs.at(i), ranks.at(i));
                if(valid.at(i))
                {
                    append(values.at(i), ppid);
                }
                else
                {
                    update(ppid);
                }
            }
            logger()<<EOM;
            #endif

            // Debug info:
            //std::cout<<"(rank "<<myComm.Get_rank()<<") Final buffer size: "<<N_items_in_buffer()<<" (Npoints was: "<<Npoints<<"), dset="<<dset_name()<<std::endl;
        }
#endif

        void add_float_block(const HDF5bufferchunk& chunk, const std::size_t buf)
        {
            // Pack it into this buffer
      #ifdef HDF5PRINTER2_DEBUG
            logger()<<LogTags::printers<<LogTags::debug<<"Adding 'float type' points to buffer "<<dset_name()<<std::endl;
            #endif
            for(std::size_t i=0; i<chunk.used_size; ++i)
            {
                bool valid = chunk.valid[buf][i];
                PPIDpair ppid(chunk.pointIDs[i], chunk.ranks[i]);
                if(valid)
                {
                    T value = static_cast<T>(chunk.values[buf][i]);
            #ifdef HDF5PRINTER2_DEBUG
                    logger()<<"   Adding valid point (rank="<<chunk.ranks[i]<<", pointID="<<chunk.pointIDs[i]<<", value="<<value<<")"<<std::endl;
                    #endif
                    append(value, ppid);
                }
                else
                {
            #ifdef HDF5PRINTER2_DEBUG
                    logger()<<"   Updating with invalid point (rank="<<chunk.ranks[i]<<", pointID="<<chunk.pointIDs[i]<<")"<<std::endl;
                    #endif
                    update(ppid);
                }
            }
      #ifdef HDF5PRINTER2_DEBUG
            logger()<<EOM;
            #endif
        }

        void add_int_block(const HDF5bufferchunk& chunk, const std::size_t buf)
        {
            // Pack it into this buffer
      #ifdef HDF5PRINTER2_DEBUG
            logger()<<LogTags::printers<<LogTags::debug<<"Adding 'int type' points (from chunk["<<buf<<"] with name ID "<<chunk.name_id[buf]<<") to buffer "<<dset_name()<<std::endl;
            #endif
            for(std::size_t i=0; i<chunk.used_size; ++i)
            {
                bool valid = chunk.valid[buf][i];
                PPIDpair ppid(chunk.pointIDs[i], chunk.ranks[i]);
                if(valid)
                {
                    T value = static_cast<T>(chunk.values_int[buf][i]);
            #ifdef HDF5PRINTER2_DEBUG
                    logger()<<"   Adding valid point (rank="<<chunk.ranks[i]<<", pointID="<<chunk.pointIDs[i]<<", value="<<value<<")"<<std::endl;
                    #endif
                    append(value, ppid);
                }
                else
                {
            #ifdef HDF5PRINTER2_DEBUG
                    logger()<<"   Updating with invalid point (rank="<<chunk.ranks[i]<<", pointID="<<chunk.pointIDs[i]<<")"<<std::endl;
                    #endif
                    update(ppid);
                }
            }
      #ifdef HDF5PRINTER2_DEBUG
            logger()<<EOM;
            #endif

            // // Super debug; check entire buffer contents
            // logger()<<LogTags::printers<<LogTags::debug;
            // logger()<<"Checking buffer contents for dataset "<<dset_name()<<std::endl;
            // for(auto it=buffer.begin(); it!=buffer.end(); ++it)
            // {
            //     logger()<<"   "<<it->first<<", "<<it->second<<std::endl;
            // }
            // logger()<<EOM;

        }

        // Retrieve buffer data in specified order (removing the points specified in 'order' from the buffer)
        // Points not in the buffer are returned as "invalid"
        // As a double.
        std::pair<std::vector<double>,std::vector<int>> flush_to_vector_dbl(const std::vector<PPIDpair>& order)
        {
            std::vector<double> out_values;
            std::vector<int> out_valid;
            for(auto it=order.begin(); it!=order.end(); ++it)
            {
                if(buffer_set.find(*it)!=buffer_set.end())
                {
                    // Add to output vector
                    out_values.push_back((double)buffer.at(*it));
                    out_valid .push_back(buffer_valid.at(*it));
                    // Remove from buffer
                    buffer_set  .erase(*it);
                    buffer      .erase(*it);
                    buffer_valid.erase(*it);
                }
                else
                {
                    out_values.push_back(0);
                    out_valid .push_back(0);
                }
            }
            return std::make_pair(out_values,out_valid);
        }

        // int version
        std::pair<std::vector<long>,std::vector<int>> flush_to_vector_int(const std::vector<PPIDpair>& order)
        {
            std::vector<long> out_values;
            std::vector<int> out_valid;
            for(auto it=order.begin(); it!=order.end(); ++it)
            {
                if(buffer_set.find(*it)!=buffer_set.end())
                {
                    // Add to output vector
                    out_values.push_back((long)buffer.at(*it));
                    out_valid .push_back(buffer_valid.at(*it));
                    // Remove from buffer
                    buffer_set  .erase(*it);
                    buffer      .erase(*it);
                    buffer_valid.erase(*it);
                }
                else
                {
                    out_values.push_back(0);
                    out_valid .push_back(0);
                }
            }
            return std::make_pair(out_values,out_valid);
        }

        /// Retrieve the integer type ID for the buffered dataset
        int get_type_id() const
        {
            return my_dataset.get_type_id();
        }

      private:

        /// Object that provides an interface to the output HDF5 dataset matching this buffer
        HDF5DataSet<T> my_dataset;
        HDF5DataSet<int> my_dataset_valid;

        /// Buffer containing points to be written to disk upon "flush"
        std::map<PPIDpair,T> buffer;

#ifdef WITH_MPI
        // Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm& myComm;
#endif
    };

    /// Class to manage a set of buffers for a single output type
    template<class T>
    class HDF5MasterBufferT
    {
      public:

        /// Constructor
        HDF5MasterBufferT(bool sync
#ifdef WITH_MPI
          , GMPI::Comm& comm
#endif
          ) : synchronised(sync)
#ifdef WITH_MPI
            , myComm(comm)
#endif
        {}

        /// Retrieve buffer of our type for a given label
        // Currently buffered points need to be supplied in case we have to create and fill a new buffer
        HDF5Buffer<T>& get_buffer(const std::string& label, const std::vector<PPIDpair>& buffered_points)
        {
            auto it=my_buffers.find(label);
            if(it==my_buffers.end())
            {
                // No buffer with this name. Need to create one!
                my_buffers.emplace(label,HDF5Buffer<T>(label,synchronised,buffered_points
#ifdef WITH_MPI
                 , myComm
#endif
                ));
                it=my_buffers.find(label);
            }
            return it->second;
        }

      private:

        std::map<std::string,HDF5Buffer<T>> my_buffers;
        bool synchronised;
#ifdef WITH_MPI
        // Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm& myComm;
#endif
    };

    /// Class to manage all buffers for a given printer object
    /// Also handles the file locking/access to the output file
    class HDF5MasterBuffer
    {

      public:

        /// Constructor
        HDF5MasterBuffer(const std::string& filename, const std::string& groupname, const bool sync, const std::size_t buffer_length
#ifdef WITH_MPI
          , GMPI::Comm& comm
#endif
        );

        /// Destructor
        ~HDF5MasterBuffer();

        /// Queue up data to be written to disk when buffers are full
        template<class T>
        void schedule_print(T const& value, const std::string& label, const unsigned int mpirank, const unsigned long pointID)
        {
            /// Check if the point is known to be in the buffers already
            PPIDpair thispoint(pointID,mpirank);
            auto it = buffered_points_set.find(thispoint);
            if(it==buffered_points_set.end())
            {
                /// While we are here, check that buffered_points and buffered_points_set are the same size
                if(buffered_points.size() != buffered_points_set.size())
                {
                    std::stringstream msg;
                    msg<<"Inconsistency detected between buffered_points and buffered_points_set sizes ("<<buffered_points.size()<<" vs "<<buffered_points_set.size()<<")! This is a bug, please report it."<<std::endl;
                    printer_error().raise(LOCAL_INFO,msg.str());
                }

                /// This is a new point! See if buffers are full and need to be flushed
                if(is_synchronised() and buffered_points.size()>get_buffer_length())
                {
                    /// Sync buffers exceeded the allowed size somehow
                    std::stringstream msg;
                    msg<<"The allowed sync buffer size has somehow been exceeded! Buffers should have been flushed when they were full. This is a bug, please report it.";
                    printer_error().raise(LOCAL_INFO,msg.str());
                }
                else if(buffered_points.size()==get_buffer_length())
                {
                    // Buffer full, flush it out
                    flush();
                }
                else if(not is_synchronised() and buffered_points.size()>get_buffer_length())
                {
                    /// RA buffers may not have been able to fully flush, so check their length and report if it is getting big.

                    /// Attempt to flush again every 1000 points beyond buffer limits
                    if((buffered_points.size()%1000)==0)
                    {
                        flush();

                        std::stringstream msg;
                        msg<<"The number of unflushable points in the non-synchronised print buffers is getting large (current buffer length is "<<buffered_points.size()<<"; soft max limit was "<<get_buffer_length()<<"). This may indicate that some process has not been properly printing the synchronised points that it is computing. If nothing changes this process may run out of RAM for the printer buffers and crash.";
                        printer_warning().raise(LOCAL_INFO,msg.str());
                    }
                }

                // Inform all buffers of this new point
                update_all_buffers(thispoint);
                // DEBUG
                //std::cout<<"Adding point to buffered_points list: "<<thispoint<<std::endl;
                buffered_points.push_back(thispoint);
                buffered_points_set.insert(thispoint);
            }

            // Add the new data to the buffer
            get_buffer<T>(label,buffered_points).append(value,thispoint);
        }

        /// Empty all buffers to disk
        void flush();

        #ifdef WITH_MPI
        /// Gather all buffer data on a certain rank process
        /// (only gathers data from buffers known to that process)
        void MPI_flush_to_rank(const unsigned int rank);

        /// Give process 'rank' permission to begin sending its buffer data
        void MPI_request_buffer_data(const unsigned int rank);

        /// Receive buffer data from a specified process until a STOP message is received
        void MPI_recv_all_buffers(const unsigned int rank);

        /// Receive buffer data of a known type for a known dataset
        /// Requires status message resulting from a probe for the message to be received
        template<class T>
        int MPI_recv_buffer(const unsigned int r, const std::string& dset_name)
        {
            // Get number of points to be received
            MPI_Status status;
            myComm.Probe(r, h5v2_bufdata_values, &status);
            int Npoints;
            int err = MPI_Get_count(&status, GMPI::get_mpi_data_type<T>::type(), &Npoints);
            if(err<0)
            {
                std::stringstream msg;
                msg<<"Error from MPI_Get_count while attempting to receive buffer data from rank "<<r<<" for dataset "<<dset_name<<"!";
                printer_error().raise(LOCAL_INFO,msg.str());
            }
            HDF5Buffer<T>& buffer = get_buffer<T>(dset_name, buffered_points);
            //std::cout<<"(rank "<<myComm.Get_rank()<<") Npoints: "<<Npoints<<std::endl;
            buffer.MPI_recv_from_rank(r, Npoints);
            logger()<< LogTags::printers << LogTags::debug << "Received "<<Npoints<<" points from rank "<<r<<"'s buffers (for dataset: "<<dset_name<<")"<<EOM;
            //std::cout<<"(rank "<<myComm.Get_rank()<<") Received "<<Npoints<<" from rank "<<r<<". New buffer size is "<<buffer.N_items_in_buffer()<<" (name="<<buffer.dset_name()<<")"<<std::endl;
            return Npoints;
        }

        /// Copy an MPI-transmitted block of buffer data into our buffer
        template<class T>
        void MPI_add_int_block_to_buffer(const HDF5bufferchunk& chunk, const std::string& dset_name, const std::size_t dset_index)
        {
            HDF5Buffer<T>& buffer = get_buffer<T>(dset_name, buffered_points);
            buffer.add_int_block(chunk,dset_index);
        }

        template<class T>
        void MPI_add_float_block_to_buffer(const HDF5bufferchunk& chunk, const std::string& dset_name, const std::size_t dset_index)
        {
            HDF5Buffer<T>& buffer = get_buffer<T>(dset_name, buffered_points);
            buffer.add_float_block(chunk,dset_index);
        }

        // Add a vector of buffer chunk data to the buffers managed by this object
        void add_to_buffers(const std::vector<HDF5bufferchunk>& blocks, const std::vector<std::pair<std::string,int>>& buf_types);

        #endif

        /// Clear all data in buffers ***and on disk*** for this printer
        void reset();

        /// Make sure all buffers know about all points in all buffers
        void resynchronise();

        /// Report whether all the buffers are empty
        bool all_buffers_empty();

        /// Report what sort of buffers we are managing
        bool is_synchronised();

        /// Report status of non-empty buffers (as a string message)
        std::string buffer_status();

        /// Report what output file we are targeting
        std::string get_file();

        /// Report which group in the output file we are targeting
        std::string get_group();

        /// Report length of buffer for HDF5 output
        std::size_t get_buffer_length();

        /// Report number of points currently in the buffer
        std::size_t get_Npoints();

        /// Extend all datasets to the specified size;
        void extend_all_datasets_to(const std::size_t length);

        /// Search the existing output and find the highest used pointIDs for each rank
        std::map<ulong, ulong> get_highest_PPIDs(const int mpisize);

        /// Open (and lock) output HDF5 file and obtain HDF5 handles
        void lock_and_open_file(const char access_type='w'); // read/write allowed by default

        /// Close (and unlock) output HDF5 file and release HDF5 handles
        void close_and_unlock_file();

        /// Retrieve the location_id specifying where output should be created in the HDF5 file
        hid_t get_location_id();

        /// Get next available position in the synchronised output datasets
        std::size_t get_next_free_position();

        /// Report number of buffers that we are managing
        std::size_t get_Nbuffers();

        /// Report upper limit estimate of size of all buffer data in MB
        double get_sizeMB();

        /// Get names and types of all datasets in the group that we are pointed at
        std::vector<std::pair<std::string,int>> get_all_dset_names_on_disk();

        /// Retrieve a map containing pointers to all buffers managed by this object
        const std::map<std::string,HDF5BufferBase*>& get_all_buffers();

        /// Retrieve set containing all points currently known to be in these buffers
        const std::set<PPIDpair>& get_all_points();

        /// Remove points from buffer tracking
        // (only intended to be used when points have been removed from buffers by e.g. MPI-related
        // routines like flush_to_vector)
        void untrack_points(const std::set<PPIDpair>& removed_points);

      private:

        /// Map containing pointers to all buffers managed by this object;
        std::map<std::string,HDF5BufferBase*> all_buffers;

        /// Vector of PPIDpairs that are currently stored in the printer buffers
        /// This also defines the order in which points should ultimately be
        /// written to disk (we will tell the buffers what order to print stuff,
        /// they don't track the ordering themselves).
        std::vector<PPIDpair> buffered_points;

        /// We also need a set of the buffered points, so we can do fast lookup of
        /// whether a point is in the buffer or not.
        std::set<PPIDpair> buffered_points_set;

        /// Flag to specify what sort of buffer this manager is supposed to be managing
        bool synchronised;

        /// Max allowed size of buffer
        std::size_t buffer_length;

        /// Retrieve the buffer for a given output label (and type)
        template<class T>
        HDF5Buffer<T>& get_buffer(const std::string& label, const std::vector<PPIDpair>& buffered_points);

        /// Add base class pointer for a buffer to master buffer map
        void update_buffer_map(const std::string& label, HDF5BufferBase& buff);

        /// Inform all buffers that data has been written to certain mpirank/pointID pair
        /// They will make sure that they have an output slot for this pair, so that all the
        /// buffers for this printer stay "synchronised".
        void update_all_buffers(const PPIDpair& ppid);

        /// Obtain positions in output datasets for a buffer of points
        std::map<PPIDpair,std::size_t> get_position_map(const std::vector<PPIDpair>& buffer) const;

        /// Output file variales
        std::string file;  // Output HDF5 file
        std::string group; // HDF5 group location to store datasets

        // Handles for HDF5 files and groups containing the datasets
        hid_t file_id;
        hid_t group_id;

        // Handle to a location in a HDF5 to which the datasets will be written
        // i.e. a file or a group.
        hid_t location_id;

        /// File locking object for the output hdf5 file
        Utils::FileLock hdf5out;

        // Flag to register whether HDF5 file is open
        bool file_open;

        // Flag to register whether HDF5 file is locked for us to use
        bool have_lock;

        /// Ensure HDF5 file is open (and locked for us to use)
        void ensure_file_is_open() const;

        /// Buffer manager objects
        //  Need a map for every directly printable type, and a specialisation
        //  of 'get_buffer' to access it.
        HDF5MasterBufferT<int      > hdf5_buffers_int;
        HDF5MasterBufferT<uint     > hdf5_buffers_uint;
        HDF5MasterBufferT<long     > hdf5_buffers_long;
        HDF5MasterBufferT<ulong    > hdf5_buffers_ulong;
        //HDF5MasterBufferT<longlong > hdf5_buffers_longlong;
        //HDF5MasterBufferT<ulonglong> hdf5_buffers_ulonglong;
        HDF5MasterBufferT<float    > hdf5_buffers_float;
        HDF5MasterBufferT<double   > hdf5_buffers_double;

#ifdef WITH_MPI
        // Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm& myComm;
#endif

    };

    /// Specialisation declarations for 'get_buffer' function for each buffer type
    template<> HDF5Buffer<int      >& HDF5MasterBuffer::get_buffer<int      >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<uint     >& HDF5MasterBuffer::get_buffer<uint     >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<long     >& HDF5MasterBuffer::get_buffer<long     >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<ulong    >& HDF5MasterBuffer::get_buffer<ulong    >(const std::string& label, const std::vector<PPIDpair>&);
    //template<> HDF5Buffer<longlong >& HDF5MasterBuffer::get_buffer<longlong >(const std::string& label, const std::vector<PPIDpair>&);
    //template<> HDF5Buffer<ulonglong>& HDF5MasterBuffer::get_buffer<ulonglong>(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<float    >& HDF5MasterBuffer::get_buffer<float    >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<double   >& HDF5MasterBuffer::get_buffer<double   >(const std::string& label, const std::vector<PPIDpair>&);

    /// The main printer class for output to HDF5 format
    class HDF5Printer2: public BasePrinter
    {
      public:
        /// Constructor (for construction via inifile options)
        HDF5Printer2(const Options& options, BasePrinter* const primary = NULL);

        /// Destructor
        ~HDF5Printer2();

        /// Report name (inc. path) of output file
        std::string get_filename();

        /// Report group in output HDF5 file of output datasets
        std::string get_groupname();

        /// Report length of buffer for HDF5 output
        std::size_t get_buffer_length();

        /// Base class virtual function overloads
        /// (the public virtual interface)
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

        /// Add buffer to the primary printers records
        void add_aux_buffer(HDF5MasterBuffer& aux_buffermaster);

        /// Get pointer to primary printer of this class type
        /// (get_primary_printer returns a pointer-to-base)
        HDF5Printer2* get_HDF5_primary_printer();

#ifdef WITH_MPI
        /// Get reference to Comm object
        GMPI::Comm& get_Comm();
#endif

      private:

        /// Convert pointer-to-base for primary printer into derived type
        HDF5Printer2* link_primary_printer(BasePrinter* const primary);

        /// Pointer to primary printer object
        HDF5Printer2* primary_printer;

        std::size_t myRank;
        std::size_t mpiSize;

#ifdef WITH_MPI
        /// Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm myComm; // initially attaches to MPI_COMM_WORLD

        /// Determine ID codes to use for buffer transmission
        std::pair<std::map<std::string,int>,std::vector<std::pair<std::string,int>>> get_buffer_idcodes(const std::vector<HDF5MasterBuffer*>& masterbuffers);

        /// Gather buffer data from all processes via MPI and print it on rank 0
        void gather_and_print(HDF5MasterBuffer& out_printbuffer, const std::vector<HDF5MasterBuffer*>& masterbuffers, bool sync);

       // Gather (via MPI) all HDF5 buffer chunk data from a set of managed buffers
       std::vector<HDF5bufferchunk> gather_all(GMPI::Comm& comm, const std::vector<HDF5MasterBuffer*>& masterbuffers, const std::map<std::string,int>& buf_ids);

        static constexpr double RAMlimit = 500; // MB; dump data if buffer size exceeds this
        static constexpr std::size_t MAXrecv = 100; // Maximum number of processes to send buffer data at one time

#endif

        /// Object interfacing to HDF5 file and all datasets
        HDF5MasterBuffer buffermaster;

        /// Vector of pointers to master buffer objects for auxilliary printers
        /// Only the primary printer will have anything in this.
        std::vector<HDF5MasterBuffer*> aux_buffers;

        /// Determine filename from options
        std::string get_filename(const Options& options);

        /// Determine target group in output HDF5 file from options
        std::string get_groupname(const Options& options);

        /// Get length of buffer from options (or primary printer)
        std::size_t get_buffer_length(const Options& options);

        /// Search the existing output and find the highest used pointIDs for each rank
        std::map<ulong, ulong> get_highest_PPIDs_from_HDF5();

        /// Check all datasets in a group for length inconsistencies
        /// and correct them if possible
        void check_consistency(bool attempt_repair);

        /// Report whether this printer prints in synchronised or 'random' mode
        bool get_sync(const Options& options);

        /// Helper print functions
        /// Used to reduce repetition in definitions of virtual function overloads
        /// (useful since there is no automatic type conversion possible)
        /// @{

        template<class T>
        void basic_print(T const& value, const std::string& label, const unsigned int mpirank, const unsigned long pointID)
        {
            // Forward the print information on to the master buffer manager object
            buffermaster.schedule_print<T>(value,label,mpirank,pointID);
        }

        template<typename T>
        void print_map_str_dbl(const T& map, const std::string& label, const unsigned int mpirank, const unsigned long pointID)
        {
          for (typename T::const_iterator it = map.begin(); it != map.end(); it++)
          {
            std::stringstream ss;
            ss<<label<<"::"<<it->first;
            basic_print(it->second,ss.str(),mpirank,pointID);
          }
        }

        template<typename T>
        void print_map_str_map_str_dbl(const T& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
        {
          for (typename T::const_iterator it = map.begin(); it != map.end(); it++)
          {
            std::stringstream ss;
            ss<<label<<"::"<<it->first;
            _print(it->second,ss.str(),vID,mpirank,pointID);
          }
        }

        /// @}

    };

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(hdf5, HDF5Printer2)

  }
}

#endif
