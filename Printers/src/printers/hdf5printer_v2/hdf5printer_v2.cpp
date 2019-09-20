//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 printer version 2 function defintions
//
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jan
///
///  *********************************************
//
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer_v2.hpp"

namespace Gambit
{
  namespace Printers
  {
 
    /// @{ HDF5DataSetBase member functions

    /// Constructor
    HDF5DataSetBase::HDF5DataSetBase(const std::string& name)
      : _myname(name)
      , is_open(false)
      , virtual_dset_length(0)
      , dset_id(-1)
    {}

    /// Destructor
    HDF5DataSetBase::~HDF5DataSetBase()
    {
        if(is_open)
        {
            if(dset_id<0)
            {
                std::stringstream errmsg;
                errmsg<<"Error closing dataset in destructor for HDF5DataSetBase! Dataset is marked 'open' but dset_id<0! This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());     
            } 
            close_dataset();
        }
    }
  
    /// Retrieve name of the dataset we are supposed to access
    std::string HDF5DataSetBase::myname() const { return _myname; }

    /// Retrieve the dataset ID for the currently open dataset 
    hid_t HDF5DataSetBase::get_dset_id() const
    {
        ensure_dataset_is_open();
        return dset_id;
    }

    /// Check if our dataset exists on disk with the required name at the given location
    bool HDF5DataSetBase::dataset_exists(const hid_t loc_id)
    {
        bool exists(false);
        htri_t r = H5Lexists(loc_id, myname().c_str(), H5P_DEFAULT);
        if(r>0) exists=true;
        else if(r==0) exists=false;
        else
        {
            // Something else went wrong; error
            std::ostringstream errmsg;
            errmsg<<"HDF5 error encountered while checking if dataset named '"<<myname()<<"' exists!";
            printer_error().raise(LOCAL_INFO, errmsg.str());     
        }
        return exists;
    }

    /// Ensure that the dataset exists with the specified length
    void HDF5DataSetBase::ensure_dataset_exists(const hid_t loc_id, const std::size_t length)
    {
        if(not dataset_exists(loc_id))
        {
            // Dataset doesn't exist; create it
            create_dataset(loc_id);
        }

        // Make sure length is correct (add fill values as needed);
        open_dataset(loc_id);
        if(get_dset_length()<length)
        {
            extend_dset_to(length);
        }
        close_dataset();
    }

    /// Retrieve the current size of the dataset on disk
    std::size_t HDF5DataSetBase::get_dset_length() const
    {
        ensure_dataset_is_open();
        return dims[0];
        //return virtual_dset_length;
    }

    /// Set the variable that tracks the (used) dataset size on disk
    //void HDF5DataSetBase::set_dset_length(const std::size_t newsize)
    //{
    //    virtual_dset_length = newsize;
    //}

    /// Extend dataset to the specified size
    void HDF5DataSetBase::extend_dset_to(const std::size_t newlength)
    {
        ensure_dataset_is_open();
        std::size_t current_length = dims[0];
        if(newlength<current_length)
        {
            std::ostringstream errmsg;
            errmsg << "Failed to extend dataset (with name: \""<<myname()<<"\") from length "<<current_length<<" to length "<<newlength<<"! The new length is short than the existing length! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        dims[0] = newlength; 
        herr_t status = H5Dset_extent(get_dset_id(), dims);
        if(status<0)
        {
            std::ostringstream errmsg;
            errmsg << "Failed to extend dataset (with name: \""<<myname()<<"\") from length "<<current_length<<" to length "<<newlength<<"!";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Record the new dataset length
        //set_dset_length(newlength);
    }

    /// Extend dataset by the specified amount
    void HDF5DataSetBase::extend_dset_by(const std::size_t extend_by)
    {
       ensure_dataset_is_open();
       std::size_t current_length = get_dset_length();
       std::size_t newlength = current_length + extend_by;
       extend_dset_to(newlength);
    }

    /// Enforce that the dataset must be open for whatever follows (or else an error is thrown)
    void HDF5DataSetBase::ensure_dataset_is_open() const
    {
        if(not is_open)
        {
            std::ostringstream errmsg;
            errmsg << "Error! Dataset (with name: \""<<myname()<<"\") is not open! Code following this check is not permitted to run. This is a bug in HDF5Printer2, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());     
        }
    }

    /// Open an existing dataset
    void HDF5DataSetBase::open_dataset(hid_t location_id)
    {
        if(is_open)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening dataset (with name: \""<<myname()<<"\") in HDF5 file. The dataset is already open! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Open the dataset
        dset_id = H5Dopen2(location_id, myname().c_str(), H5P_DEFAULT);
        if(dset_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dopen2 failed." << std::endl
                   << "You may have a corrupt hdf5 file from a previous run. Try using -r, or deleting the old output.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get dataspace of the dataset.
        hid_t dspace_id = H5Dget_space(dset_id);
        if(dspace_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dget_space failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get the number of dimensions in the dataspace.
        int rank = H5Sget_simple_extent_ndims(dspace_id);
        if(rank<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Sget_simple_extent_ndims failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        if(rank!=DSETRANK)
        {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name: \""<<myname()<<"\") in HDF5 file. Rank of dataset ("<<rank<<") does not match the expected rank ("<<DSETRANK<<").";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get the dimension size of each dimension in the dataspace
        // now that we know ndims matches DSETRANK.
        hsize_t dims_out[DSETRANK];
        int ndims = H5Sget_simple_extent_dims(dspace_id, dims_out, NULL);
        if(ndims<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name: \""<<myname()<<"\") in HDF5 file. Failed to retrieve dataset extents (H5Sget_simple_extent_dims failed).";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Update parameters to match dataset contents
        // Compute initial dataspace and chunk dimensions
        dims[0] = dims_out[0]; // Set to match existing data
        maxdims[0] = H5S_UNLIMITED; // No upper limit on number of records allowed in dataset
        chunkdims[0] = HDF5_CHUNKLENGTH;
        //slicedims[0] = 1; // Dimensions of a single record in the data space

        // Release dataspace handle
        H5Sclose(dspace_id);
    
        // Register that we have opened the dataset
        is_open = true;
    }

    /// Close a dataset
    void HDF5DataSetBase::close_dataset()
    {
        if(is_open)
        {
            if(dset_id>=0)
            {
                herr_t status = H5Dclose(dset_id);
                if(status<0)
                {
                    std::ostringstream errmsg;
                    errmsg << "Error closing dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dclose failed.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
            }
            else
            {
                std::ostringstream errmsg;
                errmsg << "Error closing dataset (with name: \""<<myname()<<"\") in HDF5 file. Dataset ID is negative. This would usually indicate that the dataset is not open, however the 'is_open' flag is 'true'. This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }
        else
        {
            std::ostringstream errmsg;
            errmsg << "Error closing dataset (with name: \""<<myname()<<"\") in HDF5 file. The dataset is not open! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str()); 
        }
        is_open = false;
    }

    /// Obtain memory and dataspace identifiers for writing to a hyperslab in the dataset
    std::pair<hid_t,hid_t> HDF5DataSetBase::select_hyperslab(std::size_t offset, std::size_t length) const
    {
        // Make sure that this chunk lies within the dataset extents
        if(offset + length > get_dset_length())
        {
           std::ostringstream errmsg;
           errmsg << "Error selecting chunk from dataset (with name: \""<<myname()<<") in HDF5 file. Tried to select a hyperslab which extends beyond the dataset extents:" << std::endl;
           errmsg << "  offset = " << offset << std::endl;
           errmsg << "  offset+length = " << offset+length << std::endl;
           errmsg << "  dset_length = "<< get_dset_length() << std::endl;
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Select a hyperslab.
        hid_t dspace_id = H5Dget_space(get_dset_id());
        if(dspace_id<0) 
        {
           std::ostringstream errmsg;
           errmsg << "Error selecting chunk from dataset (with name: \""<<myname()<<"\") in HDF5 file. H5Dget_space failed." << std::endl;
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        hsize_t offsets[DSETRANK];
        offsets[0] = offset;

        hsize_t selection_dims[DSETRANK]; // Set same as output chunks, but may have a different length
        selection_dims[0] = length; // Adjust chunk length to input specification

        herr_t err_hs = H5Sselect_hyperslab(dspace_id, H5S_SELECT_SET, offsets, NULL, selection_dims, NULL);        

        if(err_hs<0) 
        {
           std::ostringstream errmsg;
           errmsg << "Error selecting chunk from dataset (with name: \""<<myname()<<"\", offset="<<offset<<", length="<<selection_dims[0]<<") in HDF5 file. H5Sselect_hyperslab failed." << std::endl;
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Define memory space
        //H5::DataSpace memspace( DSETRANK, this->get_chunkdims() );
        hid_t memspace_id = H5Screate_simple(DSETRANK, selection_dims, NULL);         

        #ifdef HDF5_DEBUG 
        std::cout << "Debug variables:" << std::endl
                  << "  dset_length       = " << get_dset_length() << std::endl
                  << "  offsets[0]        = " << offsets[0] << std::endl
                  << "  selection_dims[0] = " << selection_dims[0] << std::endl;
        #endif

        return std::make_pair(memspace_id, dspace_id); // Be sure to close these identifiers after using them!
    }

    /// @}
    
    /// @{ HDF5BufferBase member functions
    
    /// Constructor
    HDF5BufferBase::HDF5BufferBase(const std::string& name, const bool sync)
      : _dset_name(name)
      , synchronised(sync)
    {}
 
    /// Report name of dataset for which we are the buffer
    std::string HDF5BufferBase::dset_name()
    {
        return _dset_name;
    }

    /// Report whether this buffer is synchronised
    bool HDF5BufferBase::is_synchronised()
    {
        return synchronised;
    }

    /// @}


    /// @{ Member functions of HDF5MasterBuffer

    HDF5MasterBuffer::HDF5MasterBuffer(const std::string& filename, const std::string& groupname, const bool sync, const std::size_t buflen)
        : synchronised(sync)
        , buffer_length(sync ? buflen : MAX_BUFFER_SIZE) // Use buflen for the bufferlength if this is a sync buffer, otherwise use MAX_BUFFER_SIZE
        , file(filename)
        , group(groupname)
        , file_id(-1)
        , group_id(-1)
        , location_id(-1)
        , hdf5out(file,false)
        , file_open(false)
        , have_lock(false)
        , hdf5_buffers_int(sync)
        , hdf5_buffers_uint(sync)
        , hdf5_buffers_long(sync)
        , hdf5_buffers_ulong(sync)
        , hdf5_buffers_longlong(sync)
        , hdf5_buffers_ulonglong(sync)
        , hdf5_buffers_float(sync)
        , hdf5_buffers_double(sync)
    {
        //std::cout<<"Constructed MasterBuffer to attach to file/group:"<<std::endl;
        //std::cout<<"file : "<<file<<std::endl;
        //std::cout<<"group: "<<group<<std::endl;
    }

    HDF5MasterBuffer::~HDF5MasterBuffer()
    {
        if(file_open) close_and_unlock_file();
    }

    bool HDF5MasterBuffer::is_synchronised()
    {
        return synchronised;
    }

    /// Report length of buffer for HDF5 output
    std::size_t HDF5MasterBuffer::get_buffer_length()
    {
        return buffer_length;
    }

    /// Report what output file we are targeting
    std::string HDF5MasterBuffer::get_file()  { return file; }

    /// Report which group in the output file we are targeting
    std::string HDF5MasterBuffer::get_group() { 
        //std::cout<<"Accessing variable 'group'"<<std::endl;
        //std::cout<<"group = "<<group<<std::endl;
        return group; 
    }

    /// Empty all buffers to disk
    /// (or as much of them as is currently possible in RA case)
    void HDF5MasterBuffer::flush()
    {
        // Obtain lock on the output file
        lock_and_open_file();

        // Determine next available output slot (i.e. current nominal dataset length)
        std::size_t target_pos = get_next_free_position();

        // Behaviour is different depending on whether this buffer manager
        // manages synchronised or RA buffers
        if(is_synchronised())
        {
            // DEBUG
            //std::cout<<"Preparing to flush "<<buffered_points.size()<<" points to target position "<<target_pos<<std::endl;
            //std::size_t i=0;
            //for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it, ++i)
            //{
            //    std::cout<<"   buffered_point "<<i<<": "<<(*it)<<std::endl;
            //}

            for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
            {
                // Extend the output datasets to the next free position (in case some have been left behind)
                it->second->ensure_dataset_exists(location_id, target_pos);

                // For synchronised writes we have to tell the buffers what order to write their output,
                // and where. 'target_pos' should usually be the end of their dataset, unless data for
                // a certain dataset was not written for some buffer dump.
                it->second->block_flush(location_id,buffered_points,target_pos);
            }
            buffered_points.clear();
            buffered_points_set.clear();
        } 
        else
        {     
            //std::cout<<"Preparing to flush "<<buffered_points.size()<<" random-access points to datasets with length "<<target_pos<<std::endl;

            // DEBUG inspect buffered points
            //std::size_t i=0;
            //for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it, ++i)
            //{
            //    std::cout<<"buffered_points["<<i<<"] = "<<(*it)<<std::endl;
            //}

            // For RA writes we need to first locate the positions on disk of all
            // the points to be written
            // We will do this in (large) chunks.
            bool done = false;
            auto it = buffered_points.begin();
            std::set<PPIDpair> done_points;
            while(not done)
            {
                std::vector<PPIDpair> sub_buffer;
                sub_buffer.clear();
                for(std::size_t j=0; (j<1000000) && (it!=buffered_points.end()); ++j, ++it)
                {
                    sub_buffer.push_back(*it);
                }
                if(it==buffered_points.end()) done=true;
                //std::cout<<"Getting dataset positions for "<<sub_buffer.size()<<" points"<<std::endl;
                //std::cout<<"("<<buffered_points.size()-sub_buffer.size()<<" points remaining)"<<std::endl;
                 
                // Obtain locations on disk of all points in sub_buffer
                const std::map<PPIDpair,std::size_t> position_map(get_position_map(sub_buffer));

                // Record which points were found (the ones that were not found need to be left in the buffer)
                for(auto jt = position_map.begin(); jt!=position_map.end(); ++jt)
                {
                    //std::cout<<"position_map["<<jt->first<<"] = "<<jt->second<<std::endl;
                    if(jt->second > target_pos)
                    {
                        std::ostringstream errmsg;
                        errmsg<<"A target position for a RA write is beyond the current nominal dataset size! This doesn't make sense because we should not have retrieved such positions. This is a bug, please report it.";
                        printer_error().raise(LOCAL_INFO, errmsg.str());     
                    }
                    done_points.insert(jt->first);
                }

                // Tell all buffers to write their points to disk according to the position map
                for(auto jt = all_buffers.begin(); jt!=all_buffers.end(); ++jt)
                {
                    // Extend datasets to current nominal size and flush RA data
                    jt->second->ensure_dataset_exists(location_id, target_pos);
                    jt->second->random_flush(location_id, position_map);
                }
            }


            // Remove flushed points from the buffered points record
            std::vector<PPIDpair> remaining_buffered_points;
            for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it)
            {
                if(done_points.count(*it)==0)
                {
                    // This point couldn't be flushed (wasn't found on disk (yet))
                    //DEBUG
                    //std::cout<<"Could not flush point "<<(*it)<<", leaving it in the buffer."<<std::endl;
                    remaining_buffered_points.push_back(*it);
                }
            }
            buffered_points = remaining_buffered_points;
            buffered_points_set = set_diff(buffered_points_set, done_points);
            /// While we are here, check that buffered_points and buffered_points_set are the same size
            if(buffered_points.size() != buffered_points_set.size())
            {
                std::stringstream msg;
                msg<<"Inconsistency detected between buffered_points and buffered_points_set sizes after subtracting done_points ("<<buffered_points.size()<<" vs "<<buffered_points_set.size()<<")! This is a bug, please report it."<<std::endl;
                printer_error().raise(LOCAL_INFO,msg.str());  
            }
            //std::cout<<buffered_points.size()<<" points failed to flush from random-access buffer."<<std::endl;
        }

        // Release lock on output file
        close_and_unlock_file();
    }
    
    /// Ensure HDF5 file is open (and locked for us to use)
    void HDF5MasterBuffer::ensure_file_is_open() const 
    {
        if(not (file_open and have_lock))
        {
            std::ostringstream errmsg;
            errmsg << "Error! Output HDF5 file '"<<file<<"' is not open and locked! Code following this check is not permitted to run. This is a bug in HDF5Printer2, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());     
        }
    }

    /// Open (and lock) output HDF5 file and obtain HDF5 handles
    void HDF5MasterBuffer::lock_and_open_file()
    {
        if(have_lock)
        {
            std::stringstream err;
            err<<"HDF5MasterBuffer attempted to obtain a lock on the output hdf5 file, but it already has the lock! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        if(file_open)
        {
            std::stringstream err;
            err<<"HDF5Printer2 attempted to open the output hdf5 file, but it is already open! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        // Obtain the lock
        hdf5out.get_lock();

        // Open the file and target groups
        file_id  = HDF5::openFile(file,false,'w');
        group_id = HDF5::openGroup(file_id,group);

        // Set the target dataset write location to the chosen group
        location_id = group_id;

        file_open=true;
        have_lock=true;
    }

    /// Close (and unlock) output HDF5 file and release HDF5 handles
    void HDF5MasterBuffer::close_and_unlock_file()
    {
        if(not have_lock)
        {
            std::stringstream err;
            err<<"HDF5Printer2 attempted to release a lock on the output hdf5 file, but it doesn't currently have the lock! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        if(not file_open)
        {
            std::stringstream err;
            err<<"HDF5Printer2 attempted to close the output hdf5 file, but it is not currently open! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        if(group_id<0)
        {
            // This especially shouldn't happen because the 'file_open' flag should not be 'true' if the group has been closed.
            std::stringstream err;
            err<<"HDF5Printer2 attempted to close the output hdf5 file, but group_id<0 indicating that that output group is already closed (or was never opened)! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        if(file_id<0)
        {
            // This especially shouldn't happen because the 'file_open' flag should not be 'true' if the group has been closed.
            std::stringstream err;
            err<<"HDF5Printer2 attempted to close the output hdf5 file, but file_id<0 indicating that that output file is already closed (or was never opened)! This is a bug, please report it."<<std::endl;
            printer_error().raise(LOCAL_INFO, err.str());
        }

        // Close groups and file
        HDF5::closeGroup(group_id);
        HDF5::closeFile(file_id);

        // Release the lock
        hdf5out.release_lock();

        file_open=false;
        have_lock=false;
    }

    /// Clear all data in buffers ***and on disk*** for this printer
    void HDF5MasterBuffer::reset()
    {
        lock_and_open_file();
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            it->second->reset(location_id);
        }
        close_and_unlock_file();
        buffered_points.clear();
        buffered_points_set.clear();
    }

    /// Add base class point for a buffer to master buffer map  
    void HDF5MasterBuffer::update_buffer_map(const std::string& label, HDF5BufferBase& buff)
    {
        auto it=all_buffers.find(label);
        if(it==all_buffers.end())
        {
            /// Not already in the map; add it
            all_buffers.emplace(label,&buff);
        }
    }

    /// Inform all buffers that data has been written to certain mpirank/pointID pair
    /// They will make sure that they have an output slot for this pair, so that all the
    /// buffers for this printer stay "synchronised".
    void HDF5MasterBuffer::update_all_buffers(const PPIDpair& ppid)
    {
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            it->second->update(ppid);
        }
    }

    /// Determine the next free index in the output datasets
    std::size_t HDF5MasterBuffer::get_next_free_position()
    {
        ensure_file_is_open(); 

        HDF5DataSet<int>       mpiranks      ("MPIrank"); // Will need some constructor arguments
        HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid"); // Will need some constructor arguments
        HDF5DataSet<ulonglong> pointids      ("pointID");
        HDF5DataSet<int>       pointids_valid("pointID_isvalid");

        // Open all datasets that we need
        mpiranks      .open_dataset(location_id);
        mpiranks_valid.open_dataset(location_id);
        pointids      .open_dataset(location_id);
        pointids_valid.open_dataset(location_id);

        std::size_t r_size  = mpiranks      .get_dset_length();
        std::size_t rv_size = mpiranks_valid.get_dset_length();
        std::size_t p_size  = pointids      .get_dset_length();
        std::size_t pv_size = pointids_valid.get_dset_length();

        //std::cout<<"mpiranks dataset length: "<<r_size<<std::endl;

        if( (r_size!=rv_size)
         || (r_size!=p_size)
         || (r_size!=pv_size) )
        {
            std::ostringstream errmsg;
            errmsg<<"Inconsistency in dataset sizes detected! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Close datasets
        mpiranks      .close_dataset();
        mpiranks_valid.close_dataset();
        pointids      .close_dataset();
        pointids_valid.close_dataset();

        return r_size;
    }

    /// Obtain positions in output datasets for a buffer of points
    std::map<PPIDpair,std::size_t> HDF5MasterBuffer::get_position_map(const std::vector<PPIDpair>& buffer) const
    {
        ensure_file_is_open(); 

        std::map<PPIDpair,std::size_t> position_map_out;

        HDF5DataSet<int>       mpiranks      ("MPIrank"); // Will need some constructor arguments
        HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid"); // Will need some constructor arguments
        HDF5DataSet<ulonglong> pointids      ("pointID");
        HDF5DataSet<int>       pointids_valid("pointID_isvalid");

        // Copy point buffer into a set for faster lookup
        const std::set<PPIDpair> buffer_set(buffer.begin(), buffer.end()); 

        // DEBUG check that copy was correct
        //for(auto it=buffer_set.begin(); it!=buffer_set.end(); ++it) std::cout<<" buffer_set item: "<<(*it)<<std::endl; 

        //std::cout<<"Obtaining position map for random access write"<<std::endl;

        // Open all datasets that we need
        mpiranks      .open_dataset(location_id);
        mpiranks_valid.open_dataset(location_id);
        pointids      .open_dataset(location_id);
        pointids_valid.open_dataset(location_id);

        std::size_t dset_length = mpiranks.get_dset_length();
        std::size_t Nchunks   = dset_length / HDF5_CHUNKLENGTH;
        std::size_t remainder = dset_length % HDF5_CHUNKLENGTH;
        if(remainder!=0) Nchunks+=1; 
        for(std::size_t i=0; i<Nchunks; i++)  
        {
            std::size_t offset = i * HDF5_CHUNKLENGTH;
            std::size_t length = HDF5_CHUNKLENGTH;
            if(remainder!=0 and (i+1)==Nchunks) length = remainder;
            //std::cout<<"Reading chunk "<<offset<<" to "<<offset+length<<"(chunk "<<i<<" of "<<Nchunks<<")"<<std::endl; 

            std::vector<int>       r_chunk  = mpiranks      .get_chunk(offset,length);
            std::vector<int>       rv_chunk = mpiranks_valid.get_chunk(offset,length);
            std::vector<ulonglong> p_chunk  = pointids      .get_chunk(offset,length);  
            std::vector<int>       pv_chunk = pointids_valid.get_chunk(offset,length);  
 
            std::size_t position = offset;

            auto rt =r_chunk .begin();
            auto rvt=rv_chunk.begin();
            auto pt =p_chunk .begin();
            auto pvt=pv_chunk.begin();
            for(; // Variables declared above due to different types
                (rt !=r_chunk.end() ) 
             && (rvt!=rv_chunk.end())
             && (pt !=p_chunk.end() )
             && (pvt!=pv_chunk.end());
                ++rt,++rvt,++pt,++pvt,++position)
            {
                //DEBUG Dump everything as we read it
                //std::cout<<"position: "<<position<<", point: ("<<(*rt)<<", "<<(*pt)<<"), valid: ("<<(*rvt)<<", "<<(*pvt)<<")"<<std::endl;

                // Check if point is valid
                if((*rvt) and (*pvt))
                {
                    // Check if this is one of the points we are looking for
                    PPIDpair candidate(*rt,*pt);
                    if(buffer_set.count(candidate)>0)
                    {
                        //std::cout<<"   Point "<<candidate<<" is a match at position "<<position<<std::endl;
                        position_map_out[candidate] = position;
                    }
                } 
                else if(not ((*rvt) and (*pvt)))
                {
                    // Point is not valid. Skip it.
                    continue;
                }
                else
                {
                    // Inconsistent validity flags.
                    std::ostringstream errmsg;
                    errmsg<<"Inconsistent validity flags detected whilst determining dataset locations for RA buffer data! This is a bug, please report it."; 
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
            }
        }

        // Close all datasets
        mpiranks      .close_dataset();
        mpiranks_valid.close_dataset();
        pointids      .close_dataset();
        pointids_valid.close_dataset();

        // DEBUG check result
        //for(auto it=position_map_out.begin(); it!=position_map_out.end(); ++it)
        //{
        //    std::cout<<"Point "<<it->first<<" found at index "<<it->second<<std::endl;
        //}

        return position_map_out; 
    }

    // Read through the output dataset and find the highest pointIDs for each rank (up to maxrank)
    // (assumes file is closed)
    std::map<ulong, ulonglong> HDF5MasterBuffer::get_highest_PPIDs(const int mpisize)
    {
        lock_and_open_file();

        std::map<ulong, ulonglong> highests;
        for(int i=0; i<mpisize; ++i)
        {
            highests[i] = 0;
        }

        HDF5DataSet<int>       mpiranks      ("MPIrank");
        HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid");
        HDF5DataSet<ulonglong> pointids      ("pointID");
        HDF5DataSet<int>       pointids_valid("pointID_isvalid");

        // Open all datasets that we need
        mpiranks      .open_dataset(location_id);
        mpiranks_valid.open_dataset(location_id);
        pointids      .open_dataset(location_id);
        pointids_valid.open_dataset(location_id);

        std::size_t dset_length = mpiranks.get_dset_length();
        std::size_t Nchunks   = dset_length / HDF5_CHUNKLENGTH;
        std::size_t remainder = dset_length % HDF5_CHUNKLENGTH;
        if(remainder!=0) Nchunks+=1; 
        for(std::size_t i=0; i<Nchunks; i++)  
        {
            std::size_t offset = i * HDF5_CHUNKLENGTH;
            std::size_t length = HDF5_CHUNKLENGTH;
            if(remainder!=0 and (i+1)==Nchunks) length = remainder;
             
            std::vector<int>       r_chunk  = mpiranks      .get_chunk(offset,length);
            std::vector<int>       rv_chunk = mpiranks_valid.get_chunk(offset,length);
            std::vector<ulonglong> p_chunk  = pointids      .get_chunk(offset,length);  
            std::vector<int>       pv_chunk = pointids_valid.get_chunk(offset,length);  
 
            std::size_t position = offset;

            auto rt =r_chunk .begin();
            auto rvt=rv_chunk.begin();
            auto pt =p_chunk .begin();
            auto pvt=pv_chunk.begin();
            for(; // Variables declared above due to different types
                (rt!=r_chunk.end()) 
             && (rvt!=rv_chunk.end())
             && (pt!=p_chunk.end())
             && (pvt!=pv_chunk.end());
                ++rt,++rvt,++pt,++pvt,++position)
            {
                 // Check if point is valid
                 if((*rvt) and (*pvt))
                 {
                      // Yep, valid, check if it has a higher pointID for this rank than previously seen
                      if( ((*rt)<mpisize) and ((*pt)>highests.at(*rt)) )
                      { 
                          highests.at(*rt) = *pt; 
                      }         
                 } 
                 else if(not ((*rvt) and (*pvt)))
                 {
                      // Point is not valid. Skip it.
                      continue;
                 }
                 else
                 {
                      // Inconsistent validity flags.
                      std::ostringstream errmsg;
                      errmsg<<"Inconsistent validity flags detected whilst finding highest pointIDs in existing output! This is a bug, please report it."; 
                      printer_error().raise(LOCAL_INFO, errmsg.str());
                 }
            }
        }

        // Close datasets
        mpiranks      .close_dataset();
        mpiranks_valid.close_dataset();
        pointids      .close_dataset();
        pointids_valid.close_dataset();

        close_and_unlock_file();

        return highests;
    }
 
    /// Report whether all the buffers are empty
    bool HDF5MasterBuffer::all_buffers_empty()
    {
        bool all_empty=true;
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            if(it->second->N_items_in_buffer()!=0) all_empty=false;
        } 
        return all_empty;
    }

    /// Retrieve the location_id specifying where output should be created in the HDF5 file
    hid_t HDF5MasterBuffer::get_location_id()
    {
        ensure_file_is_open();
        return location_id;
    }

    /// Extend all datasets to the specified size;
    void HDF5MasterBuffer::extend_all_datasets_to(const std::size_t length)
    {
        lock_and_open_file();
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            it->second->ensure_dataset_exists(location_id, length);
        } 
        close_and_unlock_file();
    }

    /// Specialisation declarations for 'get_buffer' function for each buffer type
    #define DEFINE_GET_BUFFER(TYPE)\
    template<>\
    HDF5Buffer<TYPE>& HDF5MasterBuffer::get_buffer<TYPE>(const std::string& label, const std::vector<PPIDpair>& buffered_points)\
    {\
        HDF5Buffer<TYPE>& out_buffer = CAT(hdf5_buffers_,TYPE).get_buffer(label,buffered_points);\
        update_buffer_map(label,out_buffer);\
        return out_buffer;\
    }
    DEFINE_GET_BUFFER(int      )
    DEFINE_GET_BUFFER(uint     )
    DEFINE_GET_BUFFER(long     )
    DEFINE_GET_BUFFER(ulong    )
    DEFINE_GET_BUFFER(longlong )
    DEFINE_GET_BUFFER(ulonglong)
    DEFINE_GET_BUFFER(float    )
    DEFINE_GET_BUFFER(double   )
    #undef DEFINE_GET_BUFFER

    /// @}

    /// @{ Member functions for HDF5Printer2
 
    /// Convert pointer-to-base for primary printer into derived type  
    HDF5Printer2* HDF5Printer2::link_primary_printer(BasePrinter* const primary)
    {
        HDF5Printer2* out(NULL);
        if(this->is_auxilliary_printer())
        {
            if(primary==NULL)
            {
                std::ostringstream errmsg;
                errmsg<<"Auxilliary printer was not constructed with a pointer to the primary printer! This is a bug, please report it";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            out = dynamic_cast<HDF5Printer2*>(primary);
        }
        return out; 
    }

    /// Constructor
    HDF5Printer2::HDF5Printer2(const Options& options, BasePrinter* const primary)
      : BasePrinter(primary,options.getValueOrDef<bool>(false,"auxilliary"))
      , primary_printer(link_primary_printer(primary))
      , buffermaster(get_filename(options),get_groupname(options),get_sync(options),get_buffer_length(options))
      , myRank(0)
      , mpiSize(1)
#ifdef WITH_MPI
      , myComm() // initially attaches to MPI_COMM_WORLD
    {
        myRank  = myComm.Get_rank();
        mpiSize = myComm.Get_size(); 
        this->setRank(myRank); // Tell BasePrinter what rank this process is (for error messages)
#else
    { //} This comment is here just to satisfy automatic parenthesis matching 
#endif
        // Set resume flag to match primary printer, and give primary printer a pointer to our buffer master object.
        if(this->is_auxilliary_printer())
        {
            set_resume(get_HDF5_primary_printer()->get_resume());
            get_HDF5_primary_printer()->add_aux_buffer(buffermaster);
        }
        else
        {
#ifdef WITH_MPI
            // Create a new MPI context for use by this printer
            myComm.dup(MPI_COMM_WORLD,"HDF5Printer2Comm"); // duplicates MPI_COMM_WORLD
#endif
            // This is the primary printer. Need to determine resume status
            set_resume(options.getValue<bool>("resume"));

            // Overwrite output file if one already exists with the same name?
            bool overwrite_file = options.getValueOrDef<bool>(false,"delete_file_on_restart");

            std::vector<ulonglong> highests(mpiSize);
            
            std::string file  = get_filename();
            std::string group = get_groupname(); 

            if(myRank==0)
            {
                // Check whether a readable output file exists with the name that we want to use.
                std::string msg_finalfile;
                if(HDF5::checkFileReadable(file, msg_finalfile))
                {
                    if(not get_resume())
                    {
                        // Note: "not resume" means "start or restart"
                        if(overwrite_file)
                        {
                            // Delete existing output file
                            std::ostringstream command;
                            command << "rm -f "<<file;
                            logger() << LogTags::printers << LogTags::info << "Running shell command: " << command.str() << EOM;
                            FILE* fp = popen(command.str().c_str(), "r");
                            if(fp==NULL)
                            {
                                // Error running popen
                                std::ostringstream errmsg;
                                errmsg << "rank "<<myRank<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<file<<")! popen failed to run the command (command was '"<<command.str()<<"')";
                                printer_error().raise(LOCAL_INFO, errmsg.str());
                            }
                            else if(pclose(fp)!=0)
                            {
                                // Command returned exit code!=0, or pclose failed
                                std::ostringstream errmsg;
                                errmsg << "rank "<<myRank<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<file<<")! Shell command failed to executed successfully, see stderr (command was '"<<command.str()<<"').";
                                printer_error().raise(LOCAL_INFO, errmsg.str());
                            }
                        }
                        else
                        {
                            // File exists, so check if 'group' is readable, and throw error if it exists
                            // (we are not resuming, so need an empty group to write into)
                            hid_t file_id = HDF5::openFile(file);
                            std::string msg_group;
                            std::cout << "Group readable: " << file << " , " << group << " : " << HDF5::checkGroupReadable(file_id, group, msg_group) << std::endl;
                            if(HDF5::checkGroupReadable(file_id, group, msg_group))
                            {
                                // Group already exists, error!
                                std::ostringstream errmsg;
                                errmsg << "Error preparing pre-existing output file '"<<file<<"' for writing via hdf5printer! The requested output group '"<<group<<" already exists in this file! Please take one of the following actions:"<<std::endl;
                                errmsg << "  1. Choose a new group via the 'group' option in the Printer section of your input YAML file;"<<std::endl;
                                errmsg << "  2. Delete the existing group from '"<<file<<"';"<<std::endl;
                                errmsg << "  3. Delete the existing output file, or set 'delete_file_on_restart: true' in your input YAML file to give GAMBIT permission to automatically delete it (applies when -r/--restart flag used);"<<std::endl;
                                errmsg << std::endl;
                                errmsg << "*** Note: This error most commonly occurs when you try to resume a scan that has already finished! ***" <<std::endl;
                                errmsg << std::endl;
                                printer_error().raise(LOCAL_INFO, errmsg.str());
                            }
                            HDF5::closeFile(file_id);
                        }
                    }
                }
                else
                {
                    // No readable output file exists, so there is nothing to resume from. Deactivate resuming.
                    set_resume(false);  //Tell ScannerBit that it shouldn't resume and do not find highest point.
                    logger() << LogTags::info << "No previous output file found, treating run as completely new." << EOM;
                }

                std::cout <<"Rank "<<myRank<<" resume flag? "<<get_resume()<<std::endl; 
                if(get_resume())
                {
                    /// Check if combined output file exists
                    std::cout <<"Rank "<<myRank<<": output file readable? "<<HDF5::checkFileReadable(file)<<"(filename: "<<file<<")"<<std::endl;
                    if( HDF5::checkFileReadable(file) )
                    {
                        logger() << LogTags::info << "Scanning existing output file, to prepare for adding new data" << EOM;
                
                        // Open HDF5 file
                        hid_t file_id = HDF5::openFile(file);

                        // Check that group is readable
                        std::string msg2;
                        if(not HDF5::checkGroupReadable(file_id, group, msg2))
                        {
                            // We are supposed to be resuming, but specified group was not readable in the output file, so we can't.
                            std::ostringstream errmsg;
                            errmsg << "Error! GAMBIT is in resume mode, however the chosen output system (HDF5Printer) was unable to open the specified group ("<<group<<") within the existing output file ("<<file<<"). Resuming is therefore not possible; aborting run... (see below for IO error message)";
                            errmsg << std::endl << "(Strictly speaking we could allow the run to continue (if the scanner can find its necessary output files from the last run), however the printer output from that run is gone, so most likely the scan needs to start again).";
                            errmsg << std::endl << "IO error message: " << msg2;
                            printer_error().raise(LOCAL_INFO, errmsg.str());
                        }

                        // Cleanup
                        HDF5::closeFile(file_id);

                        // Output seems to be readable. 
                        // Get previous highest pointID for our rank from the existing output file
                        // Might take a while, so time it.
                        std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());
                        //PPIDpair highest_PPID
                        std::map<ulong, ulonglong> highest_PPIDs = get_highest_PPIDs_from_HDF5();
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

                        logger() << LogTags::info << "Extracted highest pointID calculated on rank "<<myRank<<" process during previous scan (it was "<< highests <<") from combined output. Operation took "<<std::chrono::duration_cast<std::chrono::seconds>(time_taken).count()<<" seconds." << EOM;

                    }
                    else
                    {
                        logger() << LogTags::info << "No previous output file found; therefore no previous MPIrank/pointID pairs to parse. Will assume that this is a new run (-r/--restart flag was not explicitly given)." << EOM;
                    }

                }
            }
           
            if(myRank==0 and not get_resume())
            {
                // No previous output; need to create MPIrank and pointID datasets
                // so that they can be used to measure nominal dataset lengths
                // Need to make sure this is done before other processes try
                // to print anything.
                buffermaster.lock_and_open_file();

                HDF5DataSet<int>       mpiranks      ("MPIrank");
                HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid");
                HDF5DataSet<ulonglong> pointids      ("pointID");
                HDF5DataSet<int>       pointids_valid("pointID_isvalid");

                mpiranks      .create_dataset(buffermaster.get_location_id());
                mpiranks_valid.create_dataset(buffermaster.get_location_id());
                pointids      .create_dataset(buffermaster.get_location_id());
                pointids_valid.create_dataset(buffermaster.get_location_id());

                buffermaster.close_and_unlock_file();
            }

#ifdef WITH_MPI
            // Resume might have been deactivated due to lack of existing previous output
            // Need to broadcast this to all other processes.
            int resume_int = get_resume();
            myComm.Barrier();
            myComm.Bcast(resume_int, 1, 0);
            set_resume(resume_int);

            if(get_resume())
            {
                unsigned long long int highest;
                myComm.Barrier();
                myComm.Scatter(highests, highest, 0);
                get_point_id() = highest;
            }
#else
            if(get_resume())
            {
                get_point_id() = highests[0];
            }
#endif
        }
    }

    /// Destructor
    HDF5Printer2::~HDF5Printer2()
    {
        // Nothing special required
    }

    /// Add buffer to the primary printers records
    void HDF5Printer2::add_aux_buffer(HDF5MasterBuffer& aux_buffermaster)
    {
        if(is_auxilliary_printer())
        {
            std::ostringstream errmsg;
            errmsg<<"'add_aux_buffer' function called on auxilliary printer! Only the primary printer should be using this function! This is abug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        aux_buffers.push_back(&aux_buffermaster);
    }
   
    void HDF5Printer2::initialise(const std::vector<int>&)
    {
        // This printer doesn't need to do anything here
    }

    // Clear all data in buffers and on disk for this printer
    void HDF5Printer2::reset(bool /*force*/)
    {
        //TODO: force flag currently not used; do we need it?
        buffermaster.reset();
    }

    // Flush data in buffers to disk
    void HDF5Printer2::flush()
    {
        buffermaster.flush();
    }

    // Make sure printer output is fully on disk and safe
    // No distinction between final and early termination procedure for this printer.
    void HDF5Printer2::finalise(bool /*abnormal*/)
    {
        // The primary printer will take care of finalising all output.
        if(not is_auxilliary_printer())
        {
            /// Need to finalise output of the sync buffers for
            /// all printers before we do the RA buffers.
            buffermaster.flush(); // Flush the primary printer
            for(auto it=aux_buffers.begin(); it!=aux_buffers.end(); ++it)
            {
                if((*it)->is_synchronised())
                {
                    (*it)->flush();
                } 
            }
 
            /// Now we need to wait until all processes have done this, to make
            /// sure every single calculated point is on disk. This way the
            /// RA buffers should be able to fully empty themselves.
            logger()<<"Synchronised buffers flushed for rank "<<myRank<<" printers. Waiting for all processes to flush their sync data before we try to write the RA data."<<EOM;
#ifdef WITH_MPI
            myComm.Barrier();
#endif

            /// Need to know final nominal dataset size to ensure unsynchronised datasets match synchronised ones.
            buffermaster.lock_and_open_file();
            std::size_t final_size = buffermaster.get_next_free_position();
            buffermaster.close_and_unlock_file();

            if(myRank==0) std::cout<<"Final dataset size is "<<final_size<<std::endl;

            for(auto it=aux_buffers.begin(); it!=aux_buffers.end(); ++it)
            {
                if(not (*it)->is_synchronised())
                {
                    (*it)->flush();
                    // Check if everything managed to flush!
                    if(not (*it)->all_buffers_empty())
                    {
                        std::ostringstream errmsg;
                        errmsg<<"Not all 'random access' buffers were successfully flushed on rank "<<myRank<<" process! This is a bug, please report it."; 
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    // Make sure final dataset size is correct for the unsynchronised buffers
                    (*it)->extend_all_datasets_to(final_size);
                } 
            }
        }    
    }

    /// Get pointer to primary printer of this class type
    /// (get_primary_printer returns a pointer-to-base)
    HDF5Printer2* HDF5Printer2::get_HDF5_primary_printer()
    {
        if(not is_auxilliary_printer())
        {
            std::ostringstream errmsg;
            errmsg<<"Attempted to get a pointer of derived class type to primary printer, however this object IS the primary printer! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        else if(primary_printer==NULL)
        {
            std::ostringstream errmsg;
            errmsg<<"Attempted to get a pointer of derived class type to primary printer, but it was NULL! This means that this auxilliary printer has not been constructed correctly. This is a bug, please report it."; 
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        return primary_printer;
    }
  

    /// Search the existing output and find the highest used pointIDs for each rank
    std::map<ulong, ulonglong> HDF5Printer2::get_highest_PPIDs_from_HDF5()
    {
        return buffermaster.get_highest_PPIDs(mpiSize);
    }

    /// Report name (inc. path) of output file
    std::string HDF5Printer2::get_filename()
    {
        return buffermaster.get_file();
    }

    /// Report group in output HDF5 file of output datasets
    std::string HDF5Printer2::get_groupname()
    {
        return buffermaster.get_group();
    }

    /// Report length of buffer for HDF5 output
    std::size_t HDF5Printer2::get_buffer_length()
    {
        return buffermaster.get_buffer_length();
    }

    /// Determine filename from options 
    std::string HDF5Printer2::get_filename(const Options& options)
    {
        std::string filename;
        if(not this->is_auxilliary_printer())
        {
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
            filename = ff.str();
        }
        else
        {
            // Get filename from primary printer object
            filename = get_HDF5_primary_printer()->get_filename();
        }
        return filename;
    }

    /// Determine target group in output HDF5 file from options
    std::string HDF5Printer2::get_groupname(const Options& options)
    {
        std::string groupname;
        if(not is_auxilliary_printer())
        {
            groupname = options.getValueOrDef<std::string>("/","group");
        }
        else
        {
            // Get groupname from primary printer
            groupname = get_HDF5_primary_printer()->get_groupname();
        }
        return groupname;
    }

    /// Get length of buffer from options (or primary printer)
    std::size_t HDF5Printer2::get_buffer_length(const Options& options)
    {
        std::size_t buflen;
        if(not is_auxilliary_printer())
        {
            buflen = options.getValueOrDef<std::size_t>(1000,"buffer_length");
            if(buflen > MAX_BUFFER_SIZE)
            {
                std::ostringstream errmsg;
                errmsg<<"Requested buffer length is larger than maximum allowed (which is MAX_BUFFER_SIZE="<<MAX_BUFFER_SIZE<<"). Please specify a shorter buffer_length for the HDF5 printer.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }
        else
        {
            // Get buffer length from primary printer
            buflen = get_HDF5_primary_printer()->get_buffer_length();
        }
        return buflen;
    }

    bool HDF5Printer2::get_sync(const Options& options)
    {
        return options.getValueOrDef<bool>(true,"synchronised");
    }

    // Get options required to construct a reader object that can read
    // the previous output of this printer.
    Options HDF5Printer2::resume_reader_options()
    {
        Options options;
        // Set options that we need later to construct a reader object for
        // previous output, if required.
        options.setValue("type", "hdf5");
        options.setValue("file", buffermaster.get_file());
        options.setValue("group", buffermaster.get_group());
        return options;
    }


    /// @}
   
  }
}

