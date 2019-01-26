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
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5types.hpp"
#include "gambit/Logs/logger.hpp"


namespace Gambit
{
  namespace Printers
  {

    typedef unsigned int uint;     
    typedef unsigned long ulong;    
    typedef long long longlong; 
    typedef unsigned long long ulonglong;

    /// Length of chunks in chunked HDF5 dataset. Affects write/retrieval performance for blocks of data of various sizes.
    /// It is set to an "intermediate" sort of size since that seems to work well enough. 
    static const std::size_t HDF5_CHUNKLENGTH = 100; 

    /// Dimension of output dataset. We are only using 1D datasets for simplicity.
    static const std::size_t DSETRANK = 1; 
 
    /// Largest allowed size of buffers. Size can be dynamically set from 1 to this number.
    static const std::size_t MAX_BUFFER_SIZE = 100000; 

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
          HDF5DataSetBase(const std::string& name);
         ~HDF5DataSetBase();
  
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

         /// Variable tracking size of dataset on disk
         std::size_t virtual_dset_length;

      protected:

         /// HDF5 dataset identifer
         hid_t dset_id;
 
         /// Retrieve name of the dataset we are supposed to access
         std::string myname() const;

         /// Enforce that the dataset must be open for whatever follows (or else an error is thrown)
         void ensure_dataset_is_open() const;

         /// Retrieve the dataset ID for the currently open dataset 
         hid_t get_dset_id() const;

         /// Set the variable that tracks the (virtual) dataset size on disk
         //void set_dset_length(const std::size_t newsize);
  
         /// Extend dataset by the specified amount
         void extend_dset_by(const std::size_t extend_by);
 
         /// Extend dataset to the specified size, filling it with default values
         void extend_dset_to(const std::size_t new_size);

         /// Obtain memory and dataspace identifiers for writing to a hyperslab in the dataset
         std::pair<hid_t,hid_t> select_hyperslab(std::size_t offset, std::size_t length) const;
 
    };
 
    /// Class for interfacing to a HDF5 dataset of fixed type
    template<class T>
    class HDF5DataSet: public HDF5DataSetBase
    {
      public:

         /// Constructor
         HDF5DataSet(const std::string& name)
           : HDF5DataSetBase(name)
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
             hid_t expected_dtype = hdftype_id;
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
             herr_t status = H5Dwrite(get_dset_id(), hdftype_id, memspace_id, dspace_id, H5P_DEFAULT, buffer);
             if(status<0)
             {
                std::ostringstream errmsg;
                errmsg << "Error writing new chunk to dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dwrite failed." << std::endl;
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
             hid_t expected_dtype = hdftype_id;
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
             herr_t err_read = H5Dread(get_dset_id(), hdftype_id, memspace_id, dspace_id, H5P_DEFAULT, buffer);

             if(err_read<0)
             {
                 std::ostringstream errmsg;
                 errmsg << "Error retrieving chunk (offset="<<offset<<", length="<<length<<") from dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dread failed." << std::endl;
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

      private:

         /// HDF5 identifier for the template type of this dataset
         static const hid_t hdftype_id;

    };

    /// HDF5 identifier for the template type of this dataset
    template<class T>
    const hid_t HDF5DataSet<T>::hdftype_id = get_hdf5_data_type<T>::type();
 
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
            errmsg << "Error creating dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Screate_simple failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Object containing dataset creation parameters
        hid_t cparms_id = H5Pcreate(H5P_DATASET_CREATE);
        if(cparms_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Pcreate failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        herr_t status = H5Pset_chunk(cparms_id, DSETRANK, chunkdims);
        if(status<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Pset_chunk failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Check if location id is invalid
        if(location_id==-1)
        {
            std::ostringstream errmsg;
            errmsg << "Error! Tried to create hdf5 dataset (with name: \""<<myname()<<"\") at undefined location (location_id was -1). Please check that calling code supplied a valid location handle. This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Create the dataset
        hid_t dset_id = H5Dcreate2(location_id, myname().c_str(), hdftype_id, dspace_id, H5P_DEFAULT, cparms_id, H5P_DEFAULT);
        if(dset_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<myname()<<"\") in HDF5 file. Dataset with same name may already exist";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
    
        // Release the dataspace IDs
        H5Sclose(dspace_id);
        H5Pclose(cparms_id);
        H5Dclose(dset_id);
    }


    /// Base class for buffers
    class HDF5BufferBase
    {
      public:

        /// Constructor
        HDF5BufferBase(const std::string& name, const bool sync);
          
        /// Report name of dataset for which we are the buffer
        std::string dset_name();

        /// Make sure buffer includes the input point (data will be set as 'invalid' unless given elsewhere)
        virtual void update(const PPIDpair& ppid) = 0;
 
        /// Empty buffer to disk as a block
        virtual void block_flush(const hid_t loc_id, const std::vector<PPIDpair>& order, const std::size_t target_pos) = 0;

        /// Empty buffer to disk as arbitrarily positioned data
        virtual void random_flush(const hid_t loc_id, const std::map<PPIDpair,std::size_t>& position_map) = 0;

        /// Make sure datasets exist on disk with the correct name and size
        virtual void ensure_dataset_exists(const hid_t loc_id, const std::size_t length) = 0;

        /// Clear all data in memory ***and on disk*** for this buffer
        virtual void reset(hid_t loc_id) = 0;

        // Report whether this buffer is synchronised
        bool is_synchronised();

        // Report the number of items currently in the buffer;
        virtual std::size_t N_items_in_buffer() = 0;

      private:

        /// Name of dataset for which this object is the buffer
        std::string _dset_name;

        /// Flag to tell us whether this buffer should perform block writes
        /// to the output dataset, or look up and overwrite existing points.
        bool synchronised;

    };

    /// Class to manage buffer for a single output label
    template<class T>
    class HDF5Buffer: public HDF5BufferBase
    {
      public:

        /// Constructor
        HDF5Buffer(const std::string& name, const bool sync, const std::vector<PPIDpair>& buffered_points)
          : HDF5BufferBase(name,sync)
          , my_dataset(name)
          , my_dataset_valid(name+"_isvalid")
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
            //std::cout<<"Added valid data to point "<<ppid<<" in buffer "<<dset_name()<<std::endl;
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
                pos_buffer      [position] = bit->second;  
                pos_buffer_valid[position] = vit->second;
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

      private:

        /// Object that provides an interface to the output HDF5 dataset matching this buffer
        HDF5DataSet<T> my_dataset;
        HDF5DataSet<int> my_dataset_valid;

        /// Buffer containing points to be written to disk upon "flush"
        std::map<PPIDpair,T> buffer;

        /// Set detailing what points are in the buffer
        std::set<PPIDpair> buffer_set; 

        /// Buffer specifying whether the data in the primary buffer is "valid".
        std::map<PPIDpair,int> buffer_valid;

    };

    /// Class to manage a set of buffers for a single output type
    template<class T>
    class HDF5MasterBufferT
    {
      public:
 
        /// Constructor
        HDF5MasterBufferT(bool sync)
          : synchronised(sync)
        {}

        /// Retrieve buffer of our type for a given label
        // Currently buffered points need to be supplied in case we have to create and fill a new buffer
        HDF5Buffer<T>& get_buffer(const std::string& label, const std::vector<PPIDpair>& buffered_points)
        {
            auto it=my_buffers.find(label);
            if(it==my_buffers.end())
            {
                // No buffer with this name. Need to create one!
                my_buffers.emplace(label,HDF5Buffer<T>(label,synchronised,buffered_points));
                it=my_buffers.find(label);
            }
            return it->second;
        }

      private:
 
        std::map<std::string,HDF5Buffer<T>> my_buffers;
        bool synchronised;
    };

    /// Class to manage all buffers for a given printer object
    /// Also handles the file locking/access to the output file
    class HDF5MasterBuffer
    {

      public:

        /// Constructor  
        HDF5MasterBuffer(const std::string& filename, const std::string& groupname, const bool sync, const std::size_t buffer_length);

        /// Destructor
        ~HDF5MasterBuffer();
 
        /// Queue up data to be written to disk when buffers are full
        template<class T>
        void schedule_print(T const& value, const std::string& label, const unsigned int mpirank, const unsigned long pointID)
        {
            /// Check if the point is known to be in the buffers already
            PPIDpair thispoint(mpirank,pointID);
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
 
        /// Clear all data in buffers ***and on disk*** for this printer
        void reset();

        /// Report whether all the buffers are empty
        bool all_buffers_empty();

        /// Report what sort of buffers we are managing
        bool is_synchronised();

        /// Report what output file we are targeting
        std::string get_file(); 

        /// Report which group in the output file we are targeting
        std::string get_group();

        /// Report length of buffer for HDF5 output
        std::size_t get_buffer_length();
 
        /// Extend all datasets to the specified size;
        void extend_all_datasets_to(const std::size_t length);

        /// Search the existing output and find the highest used pointIDs for each rank
        std::map<ulong, ulonglong> get_highest_PPIDs(const int mpisize);
 
        /// Open (and lock) output HDF5 file and obtain HDF5 handles
        void lock_and_open_file();

        /// Close (and unlock) output HDF5 file and release HDF5 handles
        void close_and_unlock_file();

        /// Retrieve the location_id specifying where output should be created in the HDF5 file
        hid_t get_location_id();
 
        /// Get next available position in the synchronised output datasets
        std::size_t get_next_free_position();

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

        /// Add base class point for a buffer to master buffer map  
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
        HDF5MasterBufferT<longlong > hdf5_buffers_longlong;
        HDF5MasterBufferT<ulonglong> hdf5_buffers_ulonglong;
        HDF5MasterBufferT<float    > hdf5_buffers_float;
        HDF5MasterBufferT<double   > hdf5_buffers_double;

    };
   
    /// Specialisation declarations for 'get_buffer' function for each buffer type
    template<> HDF5Buffer<int      >& HDF5MasterBuffer::get_buffer<int      >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<uint     >& HDF5MasterBuffer::get_buffer<uint     >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<long     >& HDF5MasterBuffer::get_buffer<long     >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<ulong    >& HDF5MasterBuffer::get_buffer<ulong    >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<longlong >& HDF5MasterBuffer::get_buffer<longlong >(const std::string& label, const std::vector<PPIDpair>&);
    template<> HDF5Buffer<ulonglong>& HDF5MasterBuffer::get_buffer<ulonglong>(const std::string& label, const std::vector<PPIDpair>&);
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
          BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , HDF5_MODULE_BACKEND_TYPES)
        #endif
        #undef DECLARE_PRINT
        ///@}

        /// Add buffer to the primary printers records
        void add_aux_buffer(HDF5MasterBuffer& aux_buffermaster);
          
        /// Get pointer to primary printer of this class type
        /// (get_primary_printer returns a pointer-to-base)
        HDF5Printer2* get_HDF5_primary_printer();
            
      private:
    
        /// Convert pointer-to-base for primary printer into derived type  
        HDF5Printer2* link_primary_printer(BasePrinter* const primary);
  
        /// Pointer to primary printer object
        HDF5Printer2* primary_printer;

        /// Object interfacing to HDF5 file and all datasets
        HDF5MasterBuffer buffermaster;
       
        /// Vector of pointers to master buffer objects for auxilliary printers
        /// Only the primary printer will have anything in this.
        std::vector<HDF5MasterBuffer*> aux_buffers;

        std::size_t myRank;
        std::size_t mpiSize;
#ifdef WITH_MPI
        // Gambit MPI communicator context for use within the hdf5 printer system
        GMPI::Comm myComm; // initially attaches to MPI_COMM_WORLD
#endif
        /// Determine filename from options 
        std::string get_filename(const Options& options);
                
        /// Determine target group in output HDF5 file from options
        std::string get_groupname(const Options& options);

        /// Get length of buffer from options (or primary printer)
        std::size_t get_buffer_length(const Options& options);
 
        /// Search the existing output and find the highest used pointIDs for each rank
        std::map<ulong, ulonglong> get_highest_PPIDs_from_HDF5();
 
        /// Report whether this printer prints in synchronised or 'random' mode
        bool get_sync(const Options& options);

        /// Helper print function
        // Used to reduce repetition in definitions of virtual function overloads
        // (useful since there is no automatic type conversion possible)
        template<class T>
        void basic_print(T const& value, const std::string& label, const unsigned int mpirank, const unsigned long pointID)
        {
            // Forward the print information on to the master buffer manager object
            buffermaster.schedule_print<T>(value,label,mpirank,pointID);
        }

    };

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(hdf5, HDF5Printer2)

  }
}

#endif
