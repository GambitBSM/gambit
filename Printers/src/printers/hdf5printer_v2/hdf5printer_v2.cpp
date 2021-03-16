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
#include <math.h>
#include <limits>
#include <iterator>
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer_v2.hpp"
#include "gambit/Utils/util_functions.hpp"

// Helper to check next item in iteration
//template <typename Iter>
//Iter next(Iter iter)
//{
//        return ++iter;
//}

namespace Gambit
{
  namespace Printers
  {
    /// @{ HDF5DataSetBase member functions

    /// Constructor
    HDF5DataSetBase::HDF5DataSetBase(const std::string& name, const hid_t tid)
      : _myname(name)
      , is_open(false)
      , exists_on_disk(false)
      , dset_id(-1)
      , hdftype_id(tid)
      , type_id(HDF5::inttype_from_h5type(tid))
    {}

    /// Version where type is not provided; set to default of -1
    HDF5DataSetBase::HDF5DataSetBase(const std::string& name)
      : _myname(name)
      , is_open(false)
      , exists_on_disk(false)
      , dset_id(-1)
      , hdftype_id(-1)
      , type_id(-1)
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

    /// Access variables that track whether the dataset exists on disk yet 
    bool HDF5DataSetBase::get_exists_on_disk() const { return exists_on_disk; }
    void HDF5DataSetBase::set_exists_on_disk() { exists_on_disk = true; }

    /// Retrieve the dataset ID for the currently open dataset 
    hid_t HDF5DataSetBase::get_dset_id() const
    {
        ensure_dataset_is_open();
        return dset_id;
    }

    /// Retrieve the integer type ID for this dataset 
    int HDF5DataSetBase::get_type_id() const { return type_id; }

    /// Retrieve the HDF5 type ID for this dataset 
    hid_t HDF5DataSetBase::get_hdftype_id() const { return hdftype_id; }

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
        if(exists) set_exists_on_disk();
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
            errmsg << "Failed to extend dataset (with name=\""<<myname()<<"\") from length "<<current_length<<" to length "<<newlength<<"! The new length is short than the existing length! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        dims[0] = newlength; 
        herr_t status = H5Dset_extent(get_dset_id(), dims);
        if(status<0)
        {
            std::ostringstream errmsg;
            errmsg << "Failed to extend dataset (with name=\""<<myname()<<"\") from length "<<current_length<<" to length "<<newlength<<"!";
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
            errmsg << "Error! Dataset (with name=\""<<myname()<<"\") is not open! Code following this check is not permitted to run. This is a bug in HDF5Printer2, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());     
        }
    }

    /// Open an existing dataset
    void HDF5DataSetBase::open_dataset(hid_t location_id)
    {
        if(is_open)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening dataset (with name=\""<<myname()<<"\") in HDF5 file. The dataset is already open! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Open the dataset
        dset_id = H5Dopen2(location_id, myname().c_str(), H5P_DEFAULT);
        if(dset_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dopen2 failed." << std::endl
                   << "You may have a corrupt hdf5 file from a previous run. Try using -r, or deleting the old output.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get dataspace of the dataset.
        hid_t dspace_id = H5Dget_space(dset_id);
        if(dspace_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dget_space failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get the number of dimensions in the dataspace.
        int rank = H5Sget_simple_extent_ndims(dspace_id);
        if(rank<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Sget_simple_extent_ndims failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        if(rank!=DSETRANK)
        {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name=\""<<myname()<<"\") in HDF5 file. Rank of dataset ("<<rank<<") does not match the expected rank ("<<DSETRANK<<").";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }

        // Get the dimension size of each dimension in the dataspace
        // now that we know ndims matches DSETRANK.
        hsize_t dims_out[DSETRANK];
        int ndims = H5Sget_simple_extent_dims(dspace_id, dims_out, NULL);
        if(ndims<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name=\""<<myname()<<"\") in HDF5 file. Failed to retrieve dataset extents (H5Sget_simple_extent_dims failed).";
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
                    errmsg << "Error closing dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dclose failed.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
            }
            else
            {
                std::ostringstream errmsg;
                errmsg << "Error closing dataset (with name=\""<<myname()<<"\") in HDF5 file. Dataset ID is negative. This would usually indicate that the dataset is not open, however the 'is_open' flag is 'true'. This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }
        else
        {
            std::ostringstream errmsg;
            errmsg << "Error closing dataset (with name=\""<<myname()<<"\") in HDF5 file. The dataset is not open! This is a bug, please report it.";
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
           errmsg << "Error selecting chunk from dataset (with name=\""<<myname()<<") in HDF5 file. Tried to select a hyperslab which extends beyond the dataset extents:" << std::endl;
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
           errmsg << "Error selecting chunk from dataset (with name=\""<<myname()<<"\") in HDF5 file. H5Dget_space failed." << std::endl;
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
           errmsg << "Error selecting chunk from dataset (with name=\""<<myname()<<"\", offset="<<offset<<", length="<<selection_dims[0]<<") in HDF5 file. H5Sselect_hyperslab failed." << std::endl;
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
   
    /// @{ HDF5DataSetBasic member functions
 
    HDF5DataSetBasic::HDF5DataSetBasic(const std::string& name)
     : HDF5DataSetBase(name)
    {}

    void HDF5DataSetBasic::create_dataset(hid_t /*location_id*/)
    {
        std::ostringstream errmsg;
        errmsg<<"Tried to use create_dataset function in a HDF5DataSetBasic object! This is not allowed. This object is only able to perform basic operations on existing datasets, like resizings them. For full dataset access a HDF5DataSet<T> object is required, where the type T of the dataset must be known.";
        printer_error().raise(LOCAL_INFO, errmsg.str());
    }
    
    /// @}

    /// @{ HDF5BufferBase member functions
    
    /// Constructor
    HDF5BufferBase::HDF5BufferBase(const std::string& name, const bool sync)
      : _dset_name(name)
      , synchronised(sync)
    {}
 
    /// Report name of dataset for which we are the buffer
    std::string HDF5BufferBase::dset_name() const
    {
        return _dset_name;
    }

    /// Report whether this buffer is synchronised
    bool HDF5BufferBase::is_synchronised() const
    {
        return synchronised;
    }

    /// Report all the points in this buffer
    std::set<PPIDpair> HDF5BufferBase::get_points_set() const
    { 
        return buffer_set; 
    }

    /// @}


    /// @{ Member functions of HDF5MasterBuffer

    HDF5MasterBuffer::HDF5MasterBuffer(const std::string& filename, const std::string& groupname, const bool sync, const std::size_t buflen
#ifdef WITH_MPI
        , GMPI::Comm& comm
#endif
        )
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
#ifdef WITH_MPI
        , hdf5_buffers_int(sync,comm)
        , hdf5_buffers_uint(sync,comm)
        , hdf5_buffers_long(sync,comm)
        , hdf5_buffers_ulong(sync,comm)
        //, hdf5_buffers_longlong(sync,comm)
        //, hdf5_buffers_ulonglong(sync,comm)
        , hdf5_buffers_float(sync,comm)
        , hdf5_buffers_double(sync,comm)
        , myComm(comm)
#else
        , hdf5_buffers_int(sync)
        , hdf5_buffers_uint(sync)
        , hdf5_buffers_long(sync)
        , hdf5_buffers_ulong(sync)
        //, hdf5_buffers_longlong(sync)
        //, hdf5_buffers_ulonglong(sync)
        , hdf5_buffers_float(sync)
        , hdf5_buffers_double(sync)
#endif
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

    /// Report number of points currently in the buffer
    std::size_t HDF5MasterBuffer::get_Npoints()
    {
        return buffered_points.size();
    }

    /// Empty all buffers to disk
    /// (or as much of them as is currently possible in RA case)
    void HDF5MasterBuffer::flush()
    {
        if(get_Npoints()>0) // No point trying to flush an already empty buffer
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
				#ifdef HDF5PRINTER2_DEBUG     
                logger()<<LogTags::printers<<LogTags::debug;
                logger()<<"Preparing to flush "<<buffered_points.size()<<" points to target position "<<target_pos<<std::endl;
                std::size_t i=0;
                for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it, ++i)
                {
                    logger()<<"   buffered_point "<<i<<": "<<(*it)<<std::endl;
                }
                logger()<<EOM;
                #endif
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
    }

    /// Get names of all datasets in the group that we are pointed at
    std::vector<std::pair<std::string,int>> HDF5MasterBuffer::get_all_dset_names_on_disk()
    {
         lock_and_open_file();

         // Get all object names in the group 
         std::vector<std::string> names = HDF5::lsGroup(group_id);
         std::vector<std::pair<std::string,int>> dset_names_and_types;

         // Determine which objects are datasets
         for(auto it = names.begin(); it!=names.end(); ++it)
         {
             if(HDF5::isDataSet(group_id, *it) and not Utils::endsWith(*it,"_isvalid"))
             {
                 // Figure out the type
                 hid_t h5type = HDF5::getH5DatasetType(group_id, *it);
                 int type = HDF5::inttype_from_h5type(h5type);
                 dset_names_and_types.push_back(std::make_pair(*it,type));
             }
         }

         close_and_unlock_file();

         return dset_names_and_types;
    }

    #ifdef WITH_MPI
    /// Send buffer data to a specified process  
    void HDF5MasterBuffer::MPI_flush_to_rank(const unsigned int r)
    {
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            it->second->MPI_flush_to_rank(r);
        }
        buffered_points.clear();
        buffered_points_set.clear();
    }

    /// Give process r permission to begin sending its buffer data
    // Don't do this for all processes at once, as MPI can run out of 
    // Recv request IDs behind the scenes if thousands of processes are
    // trying to send it lots of stuff at once. But it is good to let
    // many processes start sending data before we need it, so that the
    // Recv goes quickly (and is effectively already done in the background)
    // when we get to it. 
    void HDF5MasterBuffer::MPI_request_buffer_data(const unsigned int r)
    {
        logger()<< LogTags::printers << LogTags::info << "Asking process "<<r<<" to begin sending buffer data"<<EOM;
        // Send a message to the process to trigger it to begin sending buffer data (if any exists)
        int begin_sending = 1;
        myComm.Send(&begin_sending, 1, r, h5v2_BEGIN);
    }

    /// Receive buffer data from a specified process until a STOP message is received
    void HDF5MasterBuffer::MPI_recv_all_buffers(const unsigned int r)
    {
        // MAKE SURE MPI_request_buffer_data(r) HAS BEEN CALLED BEFORE THIS FUNCTION!
        // Otherwise a deadlock will occur because we will wait forever for buffer data
        // that will never be sent.
        
        int more_buffers = 1;
        int max_Npoints = 0; // Track largest buffer sent, for reporting general number of points recv'd
        int Nbuffers = 0; // Number of buffers recv'd        
        while(more_buffers)
        {
            // Check "more buffers" message  
            myComm.Recv(&more_buffers, 1, r, h5v2_BLOCK);
            //recv_counter+=1;
            logger()<<LogTags::printers<<LogTags::debug<<"More buffers to receive from process "<<r<<"? "<<more_buffers<<EOM;
            if(more_buffers)
            {
                Nbuffers+=1;
                // Retrieve the name of the dataset for the buffer data
                MPI_Status status;
                myComm.Probe(r, h5v2_bufname, &status);
                int name_size;
                int err = MPI_Get_count(&status, MPI_CHAR, &name_size);
                if(err<0)
                { 
                    std::ostringstream errmsg;
                    errmsg<<"MPI_Get_count failed while trying to get name of dataset to receive!";
                    printer_error().raise(LOCAL_INFO, errmsg.str());       
                }
                std::string dset_name(name_size, 'x'); // Initialise string to correct size, but filled with x's
                myComm.Recv(&dset_name[0], name_size, MPI_CHAR, r, h5v2_bufname);

                logger()<<LogTags::printers<<LogTags::debug<<"Preparing to receive buffer data from process "<<r<<" for buffer "<<dset_name<<EOM;
   
                // Get datatype of buffer data, and call matching receive function for that type
                int buftype;
                myComm.Recv(&buftype, 1, r, h5v2_bufdata_type);
                int Npoints = 0;
                switch(buftype) 
                {
                    case h5v2_type<int      >(): Npoints = MPI_recv_buffer<int      >(r, dset_name); break;      
                    case h5v2_type<uint     >(): Npoints = MPI_recv_buffer<uint     >(r, dset_name); break;      
                    case h5v2_type<long     >(): Npoints = MPI_recv_buffer<long     >(r, dset_name); break;      
                    case h5v2_type<ulong    >(): Npoints = MPI_recv_buffer<ulong    >(r, dset_name); break;      
                    //case h5v2_type<longlong >(): Npoints = MPI_recv_buffer<longlong >(r, dset_name); break;      
                    //case h5v2_type<ulonglong>(): Npoints = MPI_recv_buffer<ulonglong>(r, dset_name); break;      
                    case h5v2_type<float    >(): Npoints = MPI_recv_buffer<float    >(r, dset_name); break;      
                    case h5v2_type<double   >(): Npoints = MPI_recv_buffer<double   >(r, dset_name); break;      
                    default:
                       std::ostringstream errmsg;
                       errmsg<<"Unrecognised datatype integer (value = "<<buftype<<") received in buffer type message from rank "<<r<<" for dataset "<<dset_name<<"!";
                       printer_error().raise(LOCAL_INFO, errmsg.str());       
                }
                if(Npoints>max_Npoints) max_Npoints = Npoints;
            }
        }

        logger()<<LogTags::printers<<LogTags::info;
        if(max_Npoints==0)
        {
           logger()<<"No print buffer data recv'd from rank "<<r<<" process"<<std::endl;
        }
        else
        {
           logger()<<"Recv'd "<<Nbuffers<<" dataset buffers from rank "<<r<<"; the largest one contained "<<max_Npoints<<" points"<<std::endl; 
        }
        // Debug
        //for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        //{
        //    std::cout<<"New buffer length is "<<it->second->N_items_in_buffer()<<" (name="<<it->second->dset_name()<<")"<<std::endl;
        //}

        logger()<<"Finished checking for buffer data messages from process "<<r<<EOM;
    }
  
    // Add a vector of buffer chunk data to the buffers managed by this object 
    void HDF5MasterBuffer::add_to_buffers(const std::vector<HDF5bufferchunk>& blocks, const std::vector<std::pair<std::string,int>>& buf_types)
    {
        for(auto it=blocks.begin(); it!=blocks.end(); ++it)
        {
            const HDF5bufferchunk& block(*it);
            if(block.used_size>HDF5bufferchunk::SIZE)
            {
                std::ostringstream errmsg;
                errmsg<<"Invalid block detected! used_size exceeds max SIZE ("<<block.used_size<<">"<<HDF5bufferchunk::SIZE<<"). This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            if(block.used_nbuffers>HDF5bufferchunk::NBUFFERS)
            {
                std::ostringstream errmsg;
                errmsg<<"Invalid block detected! used_nbuffers exceeds max NBUFFERS ("<<block.used_nbuffers<<">"<<HDF5bufferchunk::NBUFFERS<<"). This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
         
            for(std::size_t j=0; j<block.used_nbuffers; j++)
            {
                // Work out dataset name and whether we want the int or float values for this buffer
                std::string name = buf_types.at(block.name_id[j]).first;
                int type = buf_types.at(block.name_id[j]).second;
				#ifdef HDF5PRINTER2_DEBUG     
                logger()<<LogTags::printers<<LogTags::debug;
                logger()<<"Adding block["<<j<<"] with type ID "<<type<<" and name ID "<<block.name_id[j]<<" to dataset named "<<name<<EOM;
                #endif 
                switch(type) 
                {
                    case h5v2_type<int      >(): MPI_add_int_block_to_buffer<int      >(block, name, j); break;
                    case h5v2_type<uint     >(): MPI_add_int_block_to_buffer<uint     >(block, name, j); break;       
                    case h5v2_type<long     >(): MPI_add_int_block_to_buffer<long     >(block, name, j); break;       
                    case h5v2_type<ulong    >(): MPI_add_int_block_to_buffer<ulong    >(block, name, j); break;       
                    //case h5v2_type<longlong >(): MPI_add_int_block_to_buffer<longlong >(block, name, j); break;       
                    //case h5v2_type<ulonglong>(): MPI_add_int_block_to_buffer<ulonglong>(block, name, j); break;       
                    case h5v2_type<float    >(): MPI_add_float_block_to_buffer<float  >(block, name, j); break;       
                    case h5v2_type<double   >(): MPI_add_float_block_to_buffer<double >(block, name, j); break;       
                    default:
                       std::ostringstream errmsg;
                       errmsg<<"Unrecognised datatype integer (value = "<<type<<") received in a buffer block for dataset "<<name<<"!";
                       printer_error().raise(LOCAL_INFO, errmsg.str());       
                }
            }
        }
    }

    #endif 

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
    void HDF5MasterBuffer::lock_and_open_file(const char access_type)
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
        file_id  = HDF5::openFile(file,false,access_type);
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
        else if(&buff!=it->second) // if candidate buffer not the same as the one already in the map
        {
            if(buff.get_type_id() != it->second->get_type_id())
            {
                // Make sure that we haven't accidentally duplicated a buffer due to type confusion!
                std::stringstream err;
                err<<"Tried to add a buffer with label "<<label<<" to a MasterBuffer, but a non-identical buffer with the same name and different type already exists! This is a bug, please report it. Types were (existing:"<<it->second->get_type_id()<<", new:"<<buff.get_type_id()<<")";
                printer_error().raise(LOCAL_INFO, err.str());
            }
            else
            {
                // Make sure that we haven't accidentally duplicated a buffer some other bizarre way
                std::stringstream err;
                err<<"Tried to add a buffer with label "<<label<<" to a MasterBuffer, but a non-identical buffer with the same name and same type already exists (type="<<buff.get_type_id()<<")! This shouldn't be possible and is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, err.str());
            }
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

    /// Report number of buffers that we are managing
    std::size_t HDF5MasterBuffer::get_Nbuffers()
    {
        return all_buffers.size();
    }

    /// Report upper limit estimate of size of all buffer data in MB
    // Used to trigger dump to disk if buffer is using too much RAM
    // All datasets treated as doubles for simplicity
    double HDF5MasterBuffer::get_sizeMB()
    {
        double Nbytes = (8.+4.) * (double)get_Nbuffers() * (double)get_Npoints();
        return pow(2,-20) * Nbytes; // bytes -> MB (base 2) 
    }


    /// Determine the next free index in the output datasets
    std::size_t HDF5MasterBuffer::get_next_free_position()
    {
        ensure_file_is_open(); 

        HDF5DataSet<int>       mpiranks      ("MPIrank"); // Will need some constructor arguments
        HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid"); // Will need some constructor arguments
        HDF5DataSet<ulong>     pointids      ("pointID");
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
        HDF5DataSet<ulong>     pointids      ("pointID");
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
            std::vector<ulong>     p_chunk  = pointids      .get_chunk(offset,length);  
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
                    PPIDpair candidate(*pt,*rt);
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
    std::map<ulong, ulong> HDF5MasterBuffer::get_highest_PPIDs(const int mpisize)
    {
        lock_and_open_file('r');

        std::map<ulong, ulong> highests;
        for(int i=0; i<mpisize; ++i)
        {
            highests[i] = 0;
        }

        HDF5DataSet<int>       mpiranks      ("MPIrank");
        HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid");
        HDF5DataSet<ulong>     pointids      ("pointID");
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
            std::vector<ulong>     p_chunk  = pointids      .get_chunk(offset,length);  
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

    /// Report status of non-empty buffers
    std::string HDF5MasterBuffer::buffer_status()
    {
        std::stringstream ss;
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            if(it->second->N_items_in_buffer()!=0)
            {
                ss << "   Buffer "<<it->first<<" contains "<<it->second->N_items_in_buffer()<<" unwritten items (synchronised="<<it->second->is_synchronised()<<")"<<std::endl;
                // VERBOSE DEBUG OUTPUT
                ss << "   Unwritten points are:" << std::endl;
                auto point_set = it->second->get_points_set();
                for(auto jt = point_set.begin(); jt!=point_set.end(); ++jt)
                {
                   ss << "   rank="<<jt->rank<<", pointID="<<jt->pointID<<std::endl;
                } 
            }
        } 
        return ss.str();
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

    /// Retrieve a map containing pointers to all buffers managed by this object
    const std::map<std::string,HDF5BufferBase*>& HDF5MasterBuffer::get_all_buffers() { return all_buffers; }
 
    /// Retrieve set containing all points currently known to be in these buffers
    const std::set<PPIDpair>& HDF5MasterBuffer::get_all_points() { return buffered_points_set; } 

    /// Make sure all buffers know about all points in all buffers
    /// Should not generally be necessary if points are added in the
    /// "normal" way. Only needed in special circumstances (e.g. when
    /// receiving points from another process).
    void HDF5MasterBuffer::resynchronise()
    {
        logger()<<LogTags::printers<<LogTags::info<<"Resynchronising print buffers:" << std::endl;
 
        // Determine all known points in all buffers
        std::set<PPIDpair> initial_buffer_points = buffered_points_set;
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            logger()<<"   Buffer contains "<<it->second->N_items_in_buffer()<<" items (name="<<it->second->dset_name()<<")"<<std::endl;
            std::set<PPIDpair> this_buffer_points = it->second->get_points_set();
            buffered_points_set.insert(this_buffer_points.begin(), this_buffer_points.end());
        }

        // Update all buffers with these points
        for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
        {
            for(auto jt=buffered_points_set.begin(); jt!=buffered_points_set.end(); ++jt)
            {
                it->second->update(*jt);
            }
        }

        // Determine which points were not already in the buffers
        std::set<PPIDpair> new_points;
        std::set_difference(buffered_points_set.begin(), buffered_points_set.end(), 
                            initial_buffer_points.begin(), initial_buffer_points.end(),
                            std::inserter(new_points, new_points.end())); 

        // Debug info:
        logger() << std::endl
                 << "  Initial N points   : "<<initial_buffer_points.size()<<std::endl
                 << "  Final N points     : "<<buffered_points_set.size()<<std::endl
                 << "  Difference N points: "<<new_points.size()<<std::endl;

        // Update the buffer variables with the new points
        for(auto jt=new_points.begin(); jt!=new_points.end(); ++jt)
        {
            // Update all buffers with these points
            for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
            {
                it->second->update(*jt);
            }
            // Update MasterBuffer variables
            buffered_points.push_back(*jt);
        }

        logger() << std::endl
                 << "Print buffer now contains "<<get_Npoints()<<" items."
                 << EOM;
    }

    /// Remove points from buffer tracking
    // (only intended to be used when points have been removed from buffers by e.g. MPI-related
    // routines like flush_to_vector)
    void HDF5MasterBuffer::untrack_points(const std::set<PPIDpair>& removed_points) 
    {
        for(auto pt=removed_points.begin(); pt!=removed_points.end(); ++pt)
        {
            auto it = buffered_points_set.find(*pt);
            if(it!=buffered_points_set.end())
            {
                buffered_points_set.erase(it);
                auto jt = std::find(buffered_points.begin(),buffered_points.end(),*pt);
                if(jt!=buffered_points.end())
                {
                    buffered_points.erase(jt);
                }
                else
                {
                    std::ostringstream errmsg;
                    errmsg<<"Error untracking point (rank="<<pt->rank<<", pointID="<<pt->pointID<<")! Point was found in tracked set, but not in ordering vector! This is a bug, please report it.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
            }
            else
            {
                std::ostringstream errmsg;
                errmsg<<"Could not untrack point (rank="<<pt->rank<<", pointID="<<pt->pointID<<")! Point was not being tracked! This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }
    }

    /// Specialisation declarations for 'get_buffer' function for each buffer type
    #define DEFINE_GET_BUFFER(TYPE)\
    template<>\
    HDF5Buffer<TYPE>& HDF5MasterBuffer::get_buffer<TYPE>(const std::string& label, const std::vector<PPIDpair>& buffered_points)\
    {\
        HDF5Buffer<TYPE>& out_buffer = CAT(hdf5_buffers_,TYPE).get_buffer(label,buffered_points);\
        /*logger()<<"Updating buffer map with buffer "<<label<<", C++ type="<<typeid(TYPE).name()<<", type ID="<<out_buffer.get_type_id()<<EOM;*/\
        update_buffer_map(label,out_buffer);\
        return out_buffer;\
    }
    DEFINE_GET_BUFFER(int      )
    DEFINE_GET_BUFFER(uint     )
    DEFINE_GET_BUFFER(long     )
    DEFINE_GET_BUFFER(ulong    )
    //DEFINE_GET_BUFFER(longlong ) // Some type ambiguities here between C++ and HDF5, seems like ulong and ulonglong map to same HDF5 type. So ditch ulonglong for now.
    //DEFINE_GET_BUFFER(ulonglong)
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
      , myRank(0)
      , mpiSize(1)
#ifdef WITH_MPI
      , myComm() // initially attaches to MPI_COMM_WORLD
#endif
      , buffermaster(get_filename(options),get_groupname(options),get_sync(options),get_buffer_length(options)
#ifdef WITH_MPI
        , myComm
#endif  
        )
    {
#ifdef WITH_MPI
        myRank  = myComm.Get_rank();
        mpiSize = myComm.Get_size(); 
        this->setRank(myRank); // Tell BasePrinter what rank this process is (for error messages)
        define_mpiHDF5bufferchunk();
#endif
        // Set resume flag to match primary printer, and give primary printer a pointer to our buffer master object.
        if(this->is_auxilliary_printer())
        {
            set_resume(get_HDF5_primary_printer()->get_resume());
            get_HDF5_primary_printer()->add_aux_buffer(buffermaster);
            #ifdef WITH_MPI
            myComm = get_HDF5_primary_printer()->get_Comm();
            #endif
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

            // Attempt repairs on existing HDF5 output if inconsistencies detected
            bool attempt_repair = !options.getValueOrDef<bool>(false,"disable_autorepair");

            std::vector<ulong> highests(mpiSize);
            
            std::string file  = get_filename();
            std::string group = get_groupname(); 

            if(myRank==0)
            {
                // Warn about excessive buffer length times mpiSize
                if(get_buffer_length() * mpiSize > 1e7)
                {
                    std::ostringstream warn;
                    warn<<"Warning from HDF5Printer2! Your chosen printer buffer length ("<<get_buffer_length()<<"), multiplied by the number of processes in your job ("<<mpiSize<<"), is very large. During job shutdown the master process receives all remaining print buffer data via MPI, from ALL processes, for efficient writing to disk. This needs to be able to fit into the available RAM. If you are sure that you have enough RAM for this then there is no problem. But please do check, and if needed, reduce the buffer length for this job using the 'buffer_length' option for the printer.";
                    printer_warning().raise(LOCAL_INFO, warn.str());
                }
 
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

                        // Check output for signs of corruption, and fix them
                        // For example if a previous hard shutdown occurred, but the file is not corrupted, 
                        // we might nevertheless still be missing data in some datasets.
                        // We need to look for this and at least make sure the datasets are all sized correctly.
                        check_consistency(attempt_repair);

                        // Output seems to be readable. 
                        // Get previous highest pointID for our rank from the existing output file
                        // Might take a while, so time it.
                        std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());
                        //PPIDpair highest_PPID
                        std::map<ulong, ulong> highest_PPIDs = get_highest_PPIDs_from_HDF5();
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
                HDF5DataSet<ulong>     pointids      ("pointID");
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
            std::vector<int> resume_int_buf(1);
            resume_int_buf[0] = get_resume();
            myComm.Barrier();
            myComm.Bcast(resume_int_buf, 1, 0);
            set_resume(resume_int_buf.at(0));

            if(get_resume())
            {
                unsigned long highest;
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

    /// Check all datasets in a group for length inconsistencies
    /// and correct them if possible
    void HDF5Printer2::check_consistency(bool attempt_repair)
    {
         hid_t fid = HDF5::openFile(get_filename(), false, 'r');
         hid_t gid = HDF5::openGroup(fid, get_groupname(), true);
        
         // Get all object names in the group 
         std::vector<std::string> names = HDF5::lsGroup(gid);
         std::vector<std::string> dset_names;

         // Check if all datasets have the same length
         bool first=true;
         bool problem=false;
         std::size_t dset_length = 0;
         std::size_t max_dset_length = 0;
         std::size_t min_dset_length = 0;
         for(auto it = names.begin(); it!=names.end(); ++it)
         {
             // Check if object is a dataset (could be another group)
             if(HDF5::isDataSet(gid, *it))
             {
                 dset_names.push_back(*it);
                 HDF5DataSetBasic dset(*it);
                 dset.open_dataset(gid);
                 std::size_t this_dset_length = dset.get_dset_length();
                 if(first)
                 {
                     min_dset_length = this_dset_length; 
                     first = false;
                 }
                 else if(dset_length!=this_dset_length)
                 {
                     problem = true;
                 }
                 if(this_dset_length>max_dset_length) max_dset_length = this_dset_length;
                 if(this_dset_length<min_dset_length) min_dset_length = this_dset_length;
                 dset_length = this_dset_length;
                 dset.close_dataset();
             }
         }

         if(problem)
         {
             // Length inconsistency detected. Need to try and fix it.
             // First, need to know "nominal" length. This is the *shortest*
             // of the mpiranks/pointids datasets. We will invalidate data
             // in any datasets beyond this length.
             // Then we need to know the longest actual length of any dataset.
             // We will extend all datasets to this size, and set data as invalid
             // beyond the nominal length. Shortening datasets doesn't work well
             // in HDF5, so it is better to just leave a chunk of invalid data.

             std::ostringstream warn;
             warn << "An inconsistency has been detected in the existing HDF5 output! Not all datasets are the same length. This can happen if your previous run was not shut down safely. We will now check all datasets for corruption (this involves reading the whole HDF5 file so may take some time if it is a large file)"<<std::endl;
             warn << "Note: longest  dataset: "<<max_dset_length<<std::endl;
             warn << "      shortest dataset: "<<min_dset_length<<std::endl;
             std::cerr << warn.str();
             printer_warning().raise(LOCAL_INFO, warn.str());

             bool unfixable_problem=false;
             std::string unfixable_report;
             std::size_t highest_common_readable_index = 0;

             // We already measured the longest dataset length. So now we want to extend all datasets to this length
             std::cerr<<std::endl;
             for(auto it = dset_names.begin(); it!=dset_names.end(); ++it)
             {
                 std::cerr<<"\rScanning dataset for problems: "<<*it<<"                                                                    ";
                 HDF5DataSetBasic dset(*it);
                 dset.open_dataset(gid);
                 std::size_t this_dset_length = dset.get_dset_length();

                 // Check that the dataset is fully readable
                 // Also finds highest readable index if dataset is partially readable
                 std::pair<bool,std::size_t> readable_info = HDF5::checkDatasetReadable(gid, *it);
                 if(not readable_info.first)
                 {
                     std::ostringstream msg;
                     msg << "   Corrupted dataset detected! Highest readable index was "<<readable_info.second<<" (dataset name = "<<*it<<")"<<std::endl;
                     unfixable_report += msg.str();
                     if(not unfixable_problem)
                     {
                         highest_common_readable_index = readable_info.second;
                         unfixable_problem = true;
                     }
                     else if(readable_info.second < highest_common_readable_index)
                     {
                         highest_common_readable_index = readable_info.second;
                     }
                 }
                 dset.close_dataset();

                 // Also need to shorten this highest_common_readable_index in case some non-corrupt datasets happen to be shorter
                 if(this_dset_length < highest_common_readable_index) highest_common_readable_index = this_dset_length;

             }
             std::cerr<<"\rScan of datasets complete!                                                                                      "<<std::endl;

             if(unfixable_problem)
             {
                 // Dataset corruption detected! Need to abort, but we can tell the user some facts about the problem.
                 std::ostringstream err;
                 err<<"Corruption detected in existing datasets! You cannot resume writing to the existing HDF5 file. You may be able to recover from this by copying all readable data from these datasets into a new HDF5 file. We have checked the readability of all datasets and determined that the highest index readable in all datasets is:"<<std::endl;
                 err<<"   "<<highest_common_readable_index<<std::endl;
                 err<<" A full report on the readability of corrupted datasets is given below:"<<std::endl;
                 err<<unfixable_report;
                 printer_error().raise(LOCAL_INFO, err.str());
             }

             if(attempt_repair)
             {
                 std::ostringstream warn;
                 warn << "Attempting to automatically repair datasets. Lost data will not be recovered, but file will be restored to a condition such that further data can be added. A report on dataset modifications will be issued below. If you want to disable auto-repair (and get an error message instead) then please set disable_autorepair=true in the YAML options for this printer."<<std::endl; 
                 std::cerr << warn.str();
                 printer_warning().raise(LOCAL_INFO, warn.str());
  
                 std::ostringstream repair_report;
      
                 // Reopen file in write mode
                 HDF5::closeGroup(gid);
                 HDF5::closeFile(fid);
                 fid = HDF5::openFile(get_filename(), false, 'w');
                 gid = HDF5::openGroup(fid, get_groupname(), true);
 
                 HDF5DataSet<int>       mpiranks      ("MPIrank");
                 HDF5DataSet<int>       mpiranks_valid("MPIrank_isvalid");
                 HDF5DataSet<ulong>     pointids      ("pointID");
                 HDF5DataSet<int>       pointids_valid("pointID_isvalid");

                 mpiranks      .open_dataset(gid);     
                 mpiranks_valid.open_dataset(gid);
                 pointids      .open_dataset(gid);
                 pointids_valid.open_dataset(gid);

                 std::size_t nominal_dset_length = mpiranks.get_dset_length();
                 if(mpiranks_valid.get_dset_length() < nominal_dset_length) nominal_dset_length = mpiranks_valid.get_dset_length();
                 if(pointids      .get_dset_length() < nominal_dset_length) nominal_dset_length = pointids      .get_dset_length();
                 if(pointids_valid.get_dset_length() < nominal_dset_length) nominal_dset_length = pointids_valid.get_dset_length();
                
                 mpiranks      .close_dataset();     
                 mpiranks_valid.close_dataset();
                 pointids      .close_dataset();
                 pointids_valid.close_dataset();

                 repair_report << "   Nominal dataset length identified as: "<<nominal_dset_length<<std::endl;
                 repair_report << "   Maximum dataset length identified as: "<<max_dset_length<<std::endl;

                 // We already measured the longest dataset length. So now we want to extend all datasets to this length
                 for(auto it = dset_names.begin(); it!=dset_names.end(); ++it)
                 {
                     HDF5DataSetBasic dset(*it);
                     dset.open_dataset(gid);
                     std::size_t this_dset_length = dset.get_dset_length();
                     if(max_dset_length > this_dset_length)
                     {
                         dset.extend_dset_to(max_dset_length);
                         repair_report << "   Extended dataset from "<<this_dset_length<<" to "<<max_dset_length<<"   (name = "<<*it<<")"<<std::endl;
                     }
                     dset.close_dataset();
                 }

                 // Next we want to open all the 'isvalid' datasets, and set their entries as 'invalid' between nominal and max lengths.
                 // Could be that the nominal length is the max length though; in which case no further action is required. That just
                 // means some datasets were too short. They will automatically be set as invalid in the extended sections.
                 if(max_dset_length > nominal_dset_length)
                 {
                     for(auto it = dset_names.begin(); it!=dset_names.end(); ++it)
                     {
                         if(Utils::endsWith(*it,"_isvalid"))
                         {
                             HDF5DataSet<int> dset(*it);
                             std::vector<int> zeros(max_dset_length-nominal_dset_length,0);
                             dset.write_vector(gid, zeros, nominal_dset_length, true);
                             repair_report << "   Set data as 'invalid' from "<<nominal_dset_length<<" to "<<max_dset_length<<"   (name = "<<*it<<")"<<std::endl; 
                         }
                     }
                 }
                 repair_report << "   Repairs complete."<<std::endl;
                 std::cerr << repair_report.str();
                 printer_warning().raise(LOCAL_INFO, repair_report.str());
             }
             else
             {
                 std::ostringstream err;
                 err << "Automatic dataset repair has been disabled, and a problem with your HDF5 file was detected, so this run must stop. Please manually repair your HDF5 file, or set disable_autorepair=false in the YAML options for this printer, and then try again."; 
                 printer_error().raise(LOCAL_INFO, err.str());
             }
         }
 
         HDF5::closeGroup(gid);
         HDF5::closeFile(fid);
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
        // DEBUG h5v2_BLOCK message counter
        //recv_counter = 0;
        //send_counter = 0;

        // The primary printer will take care of finalising all output.
        if(not is_auxilliary_printer())
        {
            // On HPC systems we are likely to be using hundreds or thousands of processes,
            // over a networked filesystem. If each process tries to write to the
            // output file all at once, it will create an enormous bottleneck and be very
            // slow.
            // We thus need to send ALL the buffer data to the master process via MPI,
            // and have the master process write everything to disk. Fortunately all the
            // processes can be synced here, so we can do some big collective
            // operations to send everything.

            #ifdef WITH_MPI
            // Gather and print the sync buffer data
            // Sort all buffers into sync/non-sync
            std::vector<HDF5MasterBuffer*> sync_buffers;
            std::vector<HDF5MasterBuffer*> RA_buffers;
            sync_buffers.push_back(&buffermaster);
            for(auto it=aux_buffers.begin(); it!=aux_buffers.end(); ++it)
            {
                if((*it)->is_synchronised())
                {
                    sync_buffers.push_back(*it);
                }
                else
                {
                    RA_buffers.push_back(*it);
                }
            }
            #ifdef HDF5PRINTER2_DEBUG 
            logger()<<LogTags::printers<<LogTags::debug;
            logger()<<"# sync printer streams: "<<sync_buffers.size()<<std::endl;
            logger()<<"# RA printer streams  : "<<RA_buffers.size()<<EOM;
            #endif
            logger()<<LogTags::printers<<LogTags::info<<"Gathering sync buffer data from all processes to rank 0 process..."<<EOM;
            gather_and_print(buffermaster,sync_buffers,true);
            #endif

            // Flush remaining buffer data
            /// Need to finalise output of the sync buffers for
            /// all printers before we do the RA buffers.
            if(myRank==0)
            {
                buffermaster.flush(); // Flush the primary printer
                for(auto it=aux_buffers.begin(); it!=aux_buffers.end(); ++it)
                {
                    if((*it)->is_synchronised())
                    {
                        (*it)->flush();
                    } 
                }
            }

            // Flush master process RA print buffers

            std::ostringstream buffer_nonempty_report;
            bool buffer_nonempty_warn(false);
            std::size_t final_size;
            if(myRank==0)
            {
                /// Need to know final nominal dataset size to ensure unsynchronised datasets match synchronised ones.
                buffermaster.lock_and_open_file();
                final_size = buffermaster.get_next_free_position();
                buffermaster.close_and_unlock_file();
                std::cout<<"Final dataset size is "<<final_size<<std::endl;
                logger()<< LogTags::printers << LogTags::info << "Final dataset size is "<<final_size<<EOM;
            }

            #ifdef WITH_MPI
            // Gather RA print buffer data from all other processes

            // Create a dedicate unsynchronised 'aux' buffer handler to receive data from other processes (and also this one!)
            HDF5MasterBuffer RAbuffer(get_filename(),get_groupname(),false,get_buffer_length(),myComm);
 
            // Add it to RA_buffers in case there are none, to satisfy various collective operation requirements
            RA_buffers.push_back(&RAbuffer);
 
            // Gather RA print buffer data from all other processes
            logger()<< LogTags::printers << LogTags::info << "Gathering random-access print buffer data from all process to rank 0 process..."<<EOM;
            if(myRank==0 and mpiSize>1)
            {
                // Do the gather
                gather_and_print(RAbuffer,RA_buffers,false); 
            }
            else if(myRank>0)
            {
                // Do the gather
                // Note: first argument is the target output buffermanger, but is unused except on rank 0
                // So just stick any buffermanager object as the argument to satisfy the function signature requirements.
                gather_and_print(buffermaster,RA_buffers,false); 
            }

            // Try to flush everything left to disk
            add_aux_buffer(RAbuffer); // Make sure to include 'gathered' RA data, if there is any.
            #endif
            for(auto it=aux_buffers.begin(); it!=aux_buffers.end(); ++it)
            {
                if(not (*it)->is_synchronised())
                {
                    (*it)->flush();
                    // Check if everything managed to flush!
                    if(not (*it)->all_buffers_empty())
                    {
                        buffer_nonempty_report<<(*it)->buffer_status();
                        buffer_nonempty_warn = true;
                    }
                    // Make sure final dataset size is correct for the unsynchronised buffers
                    (*it)->extend_all_datasets_to(final_size);
                } 
            }

            if(myRank==0 and buffer_nonempty_warn)
            {
                std::ostringstream errmsg;
                errmsg<<"\nWarning! Not all 'random access' buffers were successfully flushed to disk! This most often occurs when you resume scanning from a run that did not shut down cleanly (at some point in its history). Hard shutdowns can cause loss of samples, and cause subsequent attempts to write data to the missing points to fail, triggering this warning."<<std::endl;
                errmsg<<"A report on the data that could not be written to disk is given below. Please consider the impact of this on the integrity of your results:"<<std::endl;
                errmsg<<buffer_nonempty_report.str();
                std::cout<<errmsg.str();
                printer_warning().raise(LOCAL_INFO, errmsg.str());
            }

            logger()<< LogTags::printers << LogTags::info << "HDF5Printer2 output finalisation complete."<<EOM;

            // DEBUG
            //logger()<<LogTags::printers<<LogTags::debug<<"h5v2_BLOCK send count: "<<send_counter<<std::endl
            //                                           <<"h5v2_BLOCK recv count: "<<recv_counter<<EOM;
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
    std::map<ulong, ulong> HDF5Printer2::get_highest_PPIDs_from_HDF5()
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

#ifdef WITH_MPI
    /// Get reference to Comm object
    GMPI::Comm& HDF5Printer2::get_Comm() {return myComm;}

    // Determine ID codes to use for buffer transmission for all buffers across a collection of buffer managers
    std::pair<std::map<std::string,int>,std::vector<std::pair<std::string,int>>> HDF5Printer2::get_buffer_idcodes(const std::vector<HDF5MasterBuffer*>& masterbuffers)
    {
        logger()<<LogTags::printers<<LogTags::debug<<"Determining ID codes for HDF5 buffers for MPI transmission..."<<EOM;
        int rank = myComm.Get_rank();
        // Gather information on buffers to be gathered from
        // all processes
        std::stringstream buffernames;
        std::string delim = "`~`";

        // We will pack all the buffer names into one big string, and separate them
        // again on each process.
        // NOTE! This would be a lot of data to transmit, but actually we only need
        // to transmit buffer names that don't already exist in the output file!
        std::set<std::pair<std::string,int>> bufdefs;
        for(auto bt=masterbuffers.begin(); bt!=masterbuffers.end(); ++bt)
        {
            std::map<std::string,HDF5BufferBase*> all_buffers = (*bt)->get_all_buffers();
            for(auto it=all_buffers.begin(); it!=all_buffers.end(); ++it)
            {
                if(not it->second->exists_on_disk())
                {
                    bufdefs.insert(std::make_pair(it->first,it->second->get_type_id()));
                }
            }
        }
 
        // Set made sure name/types were unique, now convert to a big string for transmission
        logger()<<LogTags::printers<<LogTags::debug<<"Converting buffer names and types to string for transmission..."<<std::endl;
        for(auto it=bufdefs.begin(); it!=bufdefs.end(); ++it)
        {
            buffernames<<it->first<<delim;
            buffernames<<it->second<<delim;
            logger()<<"   type: "<<it->second<<"; name: "<<it->first<<std::endl;
        }
        std::string namestr = buffernames.str();
        #ifdef HDF5PRINTER2_DEBUG
        logger()<<"Full string to transmit:"<<std::endl;
        #endif
        logger()<<namestr<<EOM;

        // First gather lengths of strings to receive from all processes
        std::vector<int> totallen;
        totallen.push_back(namestr.length());
        std::vector<int> alllens(myComm.Get_size());
        logger()<<LogTags::printers<<LogTags::debug<<"Gathering lengths of string messages..."<<std::endl;
        #ifdef HDF5PRINTER2_DEBUG
        logger()<<"Initial state: "<<alllens;
        #endif
        logger()<<EOM;
        myComm.Gather(totallen, alllens, 0);
        #ifdef HDF5PRINTER2_DEBUG 
        logger()<<LogTags::printers<<LogTags::debug<<"Final state  : "<<alllens<<EOM;
        #endif 

        std::size_t totalstrsize = 0;
        for(auto it=alllens.begin(); it!=alllens.end(); ++it)
        {
            // Check validity
            if(*it<0)
            {
                std::ostringstream errmsg;
                errmsg<<"Received a negative value for the total length of new buffer names from a process! The value might have overflowed! In any case it makes no sense, something bad has happened.";
                printer_error().raise(LOCAL_INFO, errmsg.str());       
            }
            totalstrsize += *it;
        }

        // Check for int overflow (max single message size)
        std::size_t maxint = std::numeric_limits<int>::max(); 
        if(totalstrsize > maxint)
        {
            std::ostringstream errmsg;
            errmsg<<"Complete buffer name message is larger than MPI limits for a single message! (Required size: "<<totalstrsize<<", max size on this system (largest int): "<<maxint<<")";
            printer_error().raise(LOCAL_INFO, errmsg.str());        
        }

        // Now gather all the strings
        std::vector<char> sendnames(namestr.begin(), namestr.end());
        std::vector<char> recvnames(totalstrsize);
        logger()<<LogTags::printers<<LogTags::debug<<"Gathering all buffer name strings..."<<std::endl;
        #ifdef HDF5PRINTER2_DEBUG 
        logger()<<"sendnames:"<<sendnames;
        #endif
        logger()<<EOM;
        myComm.Gatherv(sendnames, recvnames, alllens, 0);
        #ifdef HDF5PRINTER2_DEBUG 
        logger()<<LogTags::printers<<LogTags::debug<<"recvnames:"<<recvnames<<EOM;
        #endif

        // Process names and assign IDs
        std::stringstream sendbufs;
        std::vector<std::pair<std::string,int>> ordered_bufs; // Will only be filled on rank 0
        if(rank==0)
        {
            // Split them back into their individual buffer names and types
            std::string recvnames_str(recvnames.begin(), recvnames.end());
            std::vector<std::string> all_buf_names_and_types = Utils::split(recvnames_str,delim);
            if(!all_buf_names_and_types.empty()) 
            {
                all_buf_names_and_types.pop_back(); // Remove trailing empty element
                // Make sure result is of even length (always need name + type)
                if(all_buf_names_and_types.size() % 2 != 0)
                {
                    std::ostringstream errmsg;
                    errmsg<<"all_buf_names_and_types vector doesn't have an even number of elements! This is a bug, please report it.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());       
                }
            }

            std::set<std::pair<std::string,int>> all_buf_pairs; // Remove duplicates via set
            logger()<<LogTags::printers<<LogTags::debug<<"Splitting received buffer name string..."<<std::endl;
            #ifdef HDF5PRINTER2_DEBUG
            logger()<<"Input: "<<recvnames_str<<std::endl;
            logger()<<"All size: "<<all_buf_names_and_types.size()<<std::endl;
            logger()<<"All: "<<all_buf_names_and_types<<std::endl;
            #endif
            for(auto it=all_buf_names_and_types.begin(); it!=all_buf_names_and_types.end(); ++it)
            {
                if(*it!="")
                {
                    std::string name(*it);
                    ++it;
                    if(it!=all_buf_names_and_types.end())
                    {
                       int type(std::stoi(*it));
                       all_buf_pairs.insert(std::make_pair(name,type));
                       logger()<<"   Inserted: type:"<<type<<"; name:"<<name<<std::endl;
                    }
                    else
                    {
                       std::ostringstream errmsg;
                       errmsg<<"Iterated past end of all_buf_names_and_types! This is a bug, please report it.";
                       printer_error().raise(LOCAL_INFO, errmsg.str());       
                    }
                }
            }
            logger()<<EOM;

            // Add the buffers that are already on disk
            // (do this via any of the buffer managers; they should all be managing buffers in the same
            //  HDF5 group or else none of this will work anyway)
            std::vector<std::pair<std::string,int>> existing_bufs = masterbuffers.at(0)->get_all_dset_names_on_disk();
            logger()<<LogTags::printers<<LogTags::debug<<"Adding buffer names already on disk:"<<std::endl;
            for(auto it=existing_bufs.begin(); it!=existing_bufs.end(); ++it)
            {
                all_buf_pairs.insert(*it);
                logger()<<"   Added: type:"<<it->second<<"; name:"<<it->first<<std::endl;
            }
            logger()<<EOM;

            // Figure out ID codes for all the buffers based on their order
            // in the unique set. Should end up the same on all processes.
            ordered_bufs = std::vector<std::pair<std::string,int>>(all_buf_pairs.begin(),all_buf_pairs.end()); 

            // Prepare buffers for sending. Don't need the types this time.
            for(auto it=ordered_bufs.begin(); it!=ordered_bufs.end(); ++it)
            {
                sendbufs<<it->first<<delim;
            }
        }
        namestr = sendbufs.str(); // might as well re-use these variables
        sendnames = std::vector<char>(namestr.begin(), namestr.end());
        std::vector<int> size(1);
        size[0] = sendnames.size();
        logger()<<LogTags::printers<<LogTags::debug<<"Broadcasting size of composited buffer name string"<<std::endl;
        #ifdef HDF5PRINTER2_DEBUG
        logger()<<"   namestr:"<<namestr<<std::endl;
        logger()<<"   namestr.size():"<<size.at(0);
        #endif
        logger()<<EOM; 
        // Broadcast the required recv buffer size
        myComm.Bcast(size, 1, 0);
        logger()<<LogTags::printers<<LogTags::debug<<"Received size for composited buffer name string:"<<size<<EOM;
       
        if(rank!=0) sendnames = std::vector<char>(size.at(0));

        // Broadcast the buffer names in the order defining their ID codes
        logger()<<LogTags::printers<<LogTags::debug<<"Broadcasting composited buffer name string"<<std::endl;
        #ifdef HDF5PRINTER2_DEBUG
        logger()<<"   sendnames:"<<sendnames;
        #endif
        logger()<<EOM;
        myComm.Bcast(sendnames, size.at(0), 0);
        #ifdef HDF5PRINTER2_DEBUG
        logger()<<LogTags::printers<<LogTags::debug<<"Received:"<<sendnames<<EOM;
        #endif
        // Split them back into their individual buffer names
        std::string allnames_str(sendnames.begin(), sendnames.end());
        std::vector<std::string> buf_order = Utils::split(allnames_str,delim);
 
        // Compute map of ID codes
        std::map<std::string,int> idcodes;
        logger()<<LogTags::printers<<LogTags::debug<<"Computing buffer ID codes:"<<std::endl;
        if(buf_order.size()>0)
        { 
           for(std::size_t i=0; i<buf_order.size()-1; i++)
           {
              idcodes[buf_order.at(i)] = i;
              logger()<<"   "<<i<<": "<<buf_order.at(i)<<std::endl;
           }
           logger()<<EOM;
        }
        return std::make_pair(idcodes,ordered_bufs); // Note: ordered_bufs only filled on rank 0!
    }

    // Gather buffer data from all processes via MPI and print it on rank 0
    void HDF5Printer2::gather_and_print(HDF5MasterBuffer& out_printbuffer, const std::vector<HDF5MasterBuffer*>& masterbuffers, bool sync)
    {
        // First need to gatherv information on buffer sizes to be sent
        std::vector<unsigned long> pointsbuffers(2);
        std::vector<unsigned long> pointsbuffersperprocess(mpiSize*2); // number of points and buffers to be recv'd for each process
        std::vector<unsigned long> pointsperprocess(mpiSize);
        std::vector<unsigned long> buffersperprocess(mpiSize);

        // Count points and buffers across all buffer manager objects
        auto it=masterbuffers.begin();
        if(it==masterbuffers.end())
        {
            std::ostringstream errmsg;
            errmsg<<"No buffers supplied for gathering!";
            printer_error().raise(LOCAL_INFO, errmsg.str());       
        }
        pointsbuffers[0] = (*it)->get_Npoints();
        pointsbuffers[1] = (*it)->get_Nbuffers();
        ++it;
        for(;it!=masterbuffers.end(); ++it)
        {
           // In sync case points are shared across all buffer manager objects
           // In aux case, points may or may not be shared. For the size
           // computations we'll just have to assume they are not shared.
           if(not sync) pointsbuffers[0] += (*it)->get_Npoints(); 
           pointsbuffers[1] += (*it)->get_Nbuffers();          
        }

        logger()<<LogTags::printers<<LogTags::info;
        logger()<<"Gathering data on number of points and buffers to be transmitted"<<std::endl;
        logger()<<"Number of points to send from this process: "<<pointsbuffers.at(0)<<std::endl;
        logger()<<"Number of buffers to send from this process: "<<pointsbuffers.at(1)<<std::endl;
        logger()<<EOM;

        // Need to do AllGather because all processes need to be able to do the size
        // computation to figure out if the main Gatherv operation needs to be split
        // into pieces.
        myComm.AllGather(pointsbuffers, pointsbuffersperprocess);
        for(std::size_t i=0; i<mpiSize; i++)
        {
           std::size_t j = 2*i;
           std::size_t k = 2*i+1;
           pointsperprocess[i]  = pointsbuffersperprocess.at(j);
           buffersperprocess[i] = pointsbuffersperprocess.at(k);
        }
        logger()<<LogTags::printers<<LogTags::info;
        logger()<<"Gathered data:"<<std::endl;
        logger()<<"Number of points to recv from each process: "<<pointsperprocess<<std::endl;
        logger()<<"Number of buffers to recv from each process: "<<buffersperprocess<<std::endl;
        logger()<<EOM; 

        // Now we know how many points we need to recv per process, can figure out
        // how many we can recv at once.
        // Need to compute approximate MB of storage required by each process
        std::vector<std::vector<int>> groups;
        groups.push_back(std::vector<int>());
        double running_tot_MB = 0;
        for(std::size_t i=0; i<mpiSize; i++)
        {
           double N_MB = pow(2,-20) * (8.+4.) * (double)buffersperprocess.at(i) * (double)pointsperprocess.at(i);
           running_tot_MB += N_MB;
           if((running_tot_MB > RAMlimit) and (groups.back().size()>1))
           {
              // Make a new group each time we go over the RAM limit, so long as the previous group wasn't empty (aside from rank 0 process)
              groups.push_back(std::vector<int>());
              groups.back().push_back(0); // Always need process 0 in there    
           }
           groups.back().push_back(i);
        }
        logger()<<LogTags::printers<<LogTags::debug;
        logger()<<"Number of <500MB Gathers to perform: "<<groups.size()<<std::endl;
        logger()<<"Assigned communicator groups are:"<<std::endl;
        for(auto it=groups.begin(); it!=groups.end(); ++it)
        {
           logger()<<"  "<<(*it)<<std::endl;
        }
        logger()<<EOM;

        // Get ID codes for the buffers (requires collective operations)
        std::pair<std::map<std::string,int>,std::vector<std::pair<std::string,int>>> ids_and_types = get_buffer_idcodes(masterbuffers); 
        std::map<std::string,int> buf_ids = ids_and_types.first;
        std::vector<std::pair<std::string,int>> buf_types = ids_and_types.second;

        for(std::size_t i=0; i<groups.size(); i++)
        {
            // Create new communicator group for the Gather
            std::stringstream ss;
            ss<<"Gather group "<<i;
            GMPI::Comm subComm(groups.at(i),ss.str());

            // Gather the buffer data from this group of processes to rank 0

            logger()<<LogTags::printers<<LogTags::info;
            logger()<<"Gathering buffer data for processes "<<groups.at(i)<<EOM;
            
            // Are we in this group? Communicator is null if not.
            if(*(subComm.get_boundcomm())!=MPI_COMM_NULL)
            {
               //std::cerr<<"rank "<<myRank<<" calling gather_all..."<<std::endl;
               std::vector<HDF5bufferchunk> data = gather_all(subComm, masterbuffers, buf_ids);
               // Add the data to the output buffermanager on rank 0
               if(myRank==0) 
               {
                   out_printbuffer.add_to_buffers(data,buf_types);
                   out_printbuffer.resynchronise();
                   out_printbuffer.flush();
               }
            }
        }
    }

    // Gather (via MPI) all HDF5 buffer chunk data from a set of managed buffers
    std::vector<HDF5bufferchunk> HDF5Printer2::gather_all(GMPI::Comm& comm, const std::vector<HDF5MasterBuffer*>& masterbuffers, const std::map<std::string,int>& buf_ids)
    {
        if(*(comm.get_boundcomm())==MPI_COMM_NULL)
        {
            std::ostringstream errmsg;
            errmsg<<"Attempted to call gather_all with an invalid communicator! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());        
        }

        // Build blocks to be transmitted
        std::vector<HDF5bufferchunk> bufchunks;
        std::vector<PPIDpair> sub_order;
        std::size_t i=0; // point counter
        HDF5bufferchunk newchunk;

        // First need to determine all points known to all buffers
        // For sync buffers should be the same for all buffer managers,
        // but may not be for aux buffers.
        std::set<PPIDpair> buffered_points;
        for(auto bt=masterbuffers.begin(); bt!=masterbuffers.end(); ++bt)
        {
            const std::set<PPIDpair>& all_points = (*bt)->get_all_points();
            for(auto ct=all_points.begin(); ct!=all_points.end(); ++ct)
            {
                buffered_points.insert(*ct);
            }
        }

        logger()<<LogTags::printers<<LogTags::debug<<"Building buffer chunks for MPI transmission"<<EOM;
        for(auto it=buffered_points.begin(); it!=buffered_points.end(); ++it)
        {
            sub_order.push_back(*it);
            newchunk.pointIDs[i] = it->pointID;
            newchunk.ranks[i] = it->rank;
            i++;
            // Collected enough points to fill a chunk yet? If so, create a chunk.
            if(sub_order.size()==HDF5bufferchunk::SIZE or std::next(it)==buffered_points.end())
            {
                #ifdef HDF5PRINTER2_DEBUG
                logger()<<"Obtained points for new chunk "<<std::endl;
                if(sub_order.size()==HDF5bufferchunk::SIZE)
                {
                    logger()<<"(chunk full):"<<std::endl;
                }
                else
                {
                    logger()<<"(chunk not full, but no more points to add):"<<std::endl;
                }
                for(auto ct=sub_order.begin(); ct!=sub_order.end(); ++ct)
                {
                    logger()<<"   (rank="<<ct->rank<<", pointID="<<ct->pointID<<")"<<std::endl;
                }
                #endif
                
                // Go through all the buffers and add their values for these points
                std::size_t j=0; // buffer selection index
                for(auto bt=masterbuffers.begin(); bt!=masterbuffers.end(); ++bt)
                {
                    // Check that at least some of the selected points are stored in this set of buffers
                    const std::set<PPIDpair>& points_in_these_bufs = (*bt)->get_all_points();
                    std::set<PPIDpair> intersec;
                    std::set_intersection(sub_order.begin(),sub_order.end(),points_in_these_bufs.begin(),points_in_these_bufs.end(),
                                          std::inserter(intersec,intersec.begin()));
                    if(intersec.size()>0)
                    {
                        std::map<std::string,HDF5BufferBase*> all_buffers = (*bt)->get_all_buffers();
                        for(auto jt=all_buffers.begin(); jt!=all_buffers.end(); ++jt)
                        {
                            bool last_buffer = (std::next(jt)==all_buffers.end() and std::next(bt)==masterbuffers.end());
                            #ifdef HDF5PRINTER2_DEBUG
                            logger()<<LogTags::printers<<LogTags::debug;
                            #endif 
                            if(HDF5::is_float_type(jt->second->get_type_id()))
                            {
                                std::pair<std::vector<double>,std::vector<int>> buffer;
                                buffer = jt->second->flush_to_vector_dbl(sub_order);
                                std::vector<double> values = buffer.first;
                                std::vector<int> valid = buffer.second;
                                // Check that at least some of this data is valid before wasting a chunk slot on it
                                auto kt = std::find(valid.begin(), valid.end(), 1); 
                                if(kt!=valid.end())
                                {
                                    #ifdef HDF5PRINTER2_DEBUG
                                    logger()<<"Adding float values for buffer "<<jt->first<<std::endl;
                                    #endif
                                    newchunk.name_id[j] = buf_ids.at(jt->first);
                                    for(std::size_t i2=0; i2<sub_order.size(); i2++)
                                    {
                                        #ifdef HDF5PRINTER2_DEBUG
                                        logger()<<"    value="<<values.at(i2)<<", valid="<<valid.at(i2)<<std::endl;
                                        #endif
                                        newchunk.values[j][i2] = values.at(i2);
                                        newchunk.valid[j][i2] = valid.at(i2);
                                    }
                                    j++; // Move to next buffer slot
                                }
                            }
                            else // int version
                            {
                                std::pair<std::vector<long>,std::vector<int>> buffer;
                                buffer = jt->second->flush_to_vector_int(sub_order);
                                std::vector<long> values = buffer.first;
                                std::vector<int> valid = buffer.second;
                                // Check that at least some of this data is valid before wasting a chunk slot on it
                                auto kt = std::find(valid.begin(), valid.end(), 1); 
                                if(kt!=valid.end())
                                {
                                    #ifdef HDF5PRINTER2_DEBUG
                                    logger()<<"Adding int values for buffer "<<jt->first<<std::endl;
                                    #endif
                                    newchunk.name_id[j] = buf_ids.at(jt->first);
                                    for(std::size_t i2=0; i2<sub_order.size(); i2++)
                                    {
                                        #ifdef HDF5PRINTER2_DEBUG
                                        logger()<<"    value="<<values.at(i2)<<", valid="<<valid.at(i2)<<std::endl;
                                        #endif
                                        newchunk.values_int[j][i2] = values.at(i2);
                                        newchunk.valid[j][i2] = valid.at(i2);
                                    }
                                    j++; // Move to next buffer slot
                                }
                            }
                            if(j==HDF5bufferchunk::NBUFFERS or last_buffer)
                            {
                                // Chunk full, begin another.
                                if(i>HDF5bufferchunk::SIZE)
                                {
                                    std::ostringstream errmsg;
                                    errmsg<<"Point counter exceeded allowed chunk size somehow (i>SIZE;"<<i<<">"<<HDF5bufferchunk::SIZE<<"). This is a bug, please report it.";
                                    printer_error().raise(LOCAL_INFO, errmsg.str());
                                }
                                if(j>HDF5bufferchunk::NBUFFERS)
                                {
                                    std::ostringstream errmsg;
                                    errmsg<<"Buffer counter exceeded allowed chunk size somehow (j>NBUFFERS;"<<j<<">"<<HDF5bufferchunk::NBUFFERS<<"). This is a bug, please report it.";
                                    printer_error().raise(LOCAL_INFO, errmsg.str());
                                }
                                newchunk.used_size = i;
                                newchunk.used_nbuffers = j;                    
                                bufchunks.push_back(newchunk);
                                #ifdef HDF5PRINTER2_DEBUG
                                if(last_buffer)
                                { 
                                    logger()<<"Chunk finished (no more buffer data for these points) (used_size="<<i<<", used_nbuffers="<<j<<")"<<EOM;
                                }
                                else
                                {
                                    logger()<<"Chunk finished (no space for more buffers) (used_size="<<i<<", used_nbuffers="<<j<<")"<<EOM;
                                    logger()<<LogTags::printers<<LogTags::debug;
                                    logger()<<"Beginning new chunk with same points as last"<<std::endl;
                                }
                                #endif
                                // Reset chunk (can leave the data, will be ignored so long as these counters are reset)
                                newchunk.used_size = 0;
                                newchunk.used_nbuffers = 0;
                                j=0;
                            }
                        }
                        // Inform master buffer that we have removed some points from it
                        (*bt)->untrack_points(intersec);
                    }   
                    else if(j!=0)
                    {
                        // else skip these buffers; the current point isn't in them (must have come from one of the other sets of buffers).
                        // But if this was the last buffer manager then need to close off the chunk.
                        if(i>HDF5bufferchunk::SIZE)
                        {
                            std::ostringstream errmsg;
                            errmsg<<"Point counter exceeded allowed chunk size somehow (i>SIZE;"<<i<<">"<<HDF5bufferchunk::SIZE<<"). This is a bug, please report it.";
                            printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                        if(j>HDF5bufferchunk::NBUFFERS)
                        {
                            std::ostringstream errmsg;
                            errmsg<<"Buffer counter exceeded allowed chunk size somehow (j>NBUFFERS;"<<j<<">"<<HDF5bufferchunk::NBUFFERS<<"). This is a bug, please report it.";
                            printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                        newchunk.used_size = i;
                        newchunk.used_nbuffers = j;
                        bufchunks.push_back(newchunk); 
                        #ifdef HDF5PRINTER2_DEBUG 
                        logger()<<"Chunk finished (no more buffer data for these points; skipped last masterbuffer) (used_size="<<i<<", used_nbuffers="<<j<<")"<<EOM;
                        #endif
                        // Reset chunk (can leave the data, will be ignored so long as these counters are reset)
                        newchunk.used_size = 0;
                        newchunk.used_nbuffers = 0;
                    }
                    else
                    {
                        // Skipped last buffer, but was left with an empty chunk. No big deal, just note it in the logs
                        #ifdef HDF5PRINTER2_DEBUG
                        logger()<<"Chunk finished (no more buffer data for these points; skipped last masterbuffer; chunk remains empty, discarding it."<<EOM;
                        #endif
                        newchunk.used_size = 0;
                        newchunk.used_nbuffers = 0;
                    }
                }
                i=0;
                sub_order.clear();
            }
        }

        // Transmit information about number of blocks to transmit
        std::vector<int> nblocks;
        std::vector<int> all_nblocks(comm.Get_size());
        nblocks.push_back(bufchunks.size());
        logger()<<LogTags::printers<<LogTags::info;
        logger()<<"Gathering buffer block size data (number of buffer blocks to transmit from this process: "<<nblocks.at(0)<<")"<<EOM;
        comm.Gather(nblocks, all_nblocks, 0);

        // Transmit blocks
        std::size_t total_nblocks = 0;
        if(comm.Get_rank()==0)
        {
            logger()<<LogTags::printers<<LogTags::debug; 
            logger()<<"Number of blocks to recv from each process: "<<all_nblocks<<std::endl;
            for(auto it=all_nblocks.begin(); it!=all_nblocks.end(); ++it)
            {
                total_nblocks += *it;
            }
            logger()<<"Total: "<<total_nblocks<<std::endl;
            logger()<<EOM;
        }
        std::vector<HDF5bufferchunk> all_bufblocks(total_nblocks);
        logger()<<LogTags::printers<<LogTags::info;
        logger()<<"Performing Gatherv of buffer data blocks..."<<EOM;
        comm.Gatherv(bufchunks, all_bufblocks, all_nblocks, 0); // (sendbuf, recvbuf, recvcounts, root)

        #ifdef HDF5PRINTER2_DEBUG 
        if(comm.Get_rank()==0)
        {
            // Check that received data makes sense.
            logger()<<LogTags::printers<<LogTags::debug<<"Checking received data..."<<std::endl;
            int i = 0;
            int globi = 0;
            int rrank = 0;
            for(auto it=all_bufblocks.begin(); it!=all_bufblocks.end(); ++it)
            {
                if(i==all_nblocks.at(rrank)) { rrank++; i=0; }
                logger()<<" block "<<globi<<" ("<<i<<"), received from rank "<<rrank<<", used_size="<<it->used_size<<std::endl;
                for(int j=0; j<it->used_size; j++)
                {
                   logger()<<"    ranks["<<j<<"]="<<it->ranks[j]<<", pointIDs["<<j<<"]="<<it->pointIDs[j]<<std::endl;
                }
                i++; globi++;
            }
        }
        #endif

        return all_bufblocks;
    }
#endif         

    /// @}
   
  }
}

