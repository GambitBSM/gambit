//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration for class DataSetInterfaceBase
///
///  This class and its daughters are the main
///  tools used by the hdf5 printer for actually
///  performing the output writes to hdf5 files.
///  This base class deals with creating the
///  hdf5 file and basic buffer constructs, but
///  not the actual writing to file (this is
///  dependent on the dimensionality of the
///  buffer).
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

#ifndef __DataSetInterfaceBase_hpp__
#define __DataSetInterfaceBase_hpp__

// HDF5 C bindings
#include <hdf5.h>

// Gambit
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Logs/logger.hpp"

namespace Gambit {

  namespace Printers {

      /// Wrapper object to manage a single dataset
      // Mostly just creates the dataset and holds metadata about it
      // Would be nice to extend to handle writing as well, but currently
      // I have to do it differently depending on the RANK.
      template<class T, std::size_t RECORDRANK, std::size_t CHUNKLENGTH>
      class DataSetInterfaceBase
      {
        private:
         static const std::size_t DSETRANK = RECORDRANK+1; // Rank of the dataset array
         hid_t mylocation_id; // handle for where this datasets is located in the hdf5 file
         std::string myname; // name of the dataset in the hdf5 file

         // Dimension sizes for each record.
         // This only needs to be RECORDRANK long, however zero-size arrays are not
         // standard compliant so we will use arrays one larger than we need and
         // just ignore the last entry.
         std::size_t record_dims[DSETRANK];

         // Dataset and chunk dimensions
         hsize_t  dims[DSETRANK];
         hsize_t  maxdims[DSETRANK];
         hsize_t  chunkdims[DSETRANK];
         hsize_t  slicedims[DSETRANK];

         // flag to specify whether we should try to access an existing dataset or create a new one
         bool resume;

         // flag to record access mode for the dataset
         char access;

        protected:
         // Derived classes need full access to these

         // HDF5 type handle for datasets
         static const hid_t hdftype_id;

         // Handle for wrapped dataset
         hid_t dset_id;

         // Safe(r) getter for dataset handle
         hid_t get_dset_id() const
         {
           if(this->dset_id<0)
           {
              std::ostringstream errmsg;
              errmsg << "Error getting handle for dataset with name: \""<<get_myname()<<"\". Handle id is invalid. Dataset wrapping has failed to occur correctly, and problems should have been detected before this, so this is a bug; please fix.";
              printer_error().raise(LOCAL_INFO, errmsg.str());
           }
           return this->dset_id;
         }

         // index of the beginning of the next empty slot in the output array
         // i.e. the offset in dimension 0 of the dataset needed to select the
         // next output hyperslab.
         unsigned long dsetnextemptyslab;

         // currently targeted index in output dataset
         // "Virtual" because write will not directly go to this position, it
         // will go into the buffer, but this is where the append should end
         // up after the buffer is written to file.
         unsigned long virtualwriteposition;

        public:
         // Const public data accessors
         std::string get_myname() const      { return myname; }
         std::size_t get_dsetrank() const    { return DSETRANK; }
         std::size_t get_chunklength() const { return CHUNKLENGTH; }
         const hsize_t* get_maxdsetdims() const    { return maxdims; }
         const hsize_t* get_chunkdims() const      { return chunkdims; }
         const hsize_t* get_slicedims() const      { return slicedims; }
         unsigned long get_nextemptyslab() const     { return dsetnextemptyslab; }
         unsigned long dset_length() const            { return dims[0]; }
         char access_mode() const            { return access; }

         // To point "next write" cursor back at the beginning of a dataset, for overwriting everything
         void reset_nextemptyslab() { dsetnextemptyslab = 0; }

         // Full accessor needed for dataset dimensions
         // so that they can be updated when chunks are added
         hsize_t* dsetdims() { return dims; }

         /// Constructors
         DataSetInterfaceBase();
         DataSetInterfaceBase(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK], const bool resume, const char access);
         virtual ~DataSetInterfaceBase();

         /// Create a (chunked) dataset
         hid_t createDataSet(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK]);

         /// Open an existing dataset
         hid_t openDataSet(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK]);

         /// Close an open dataset
         void closeDataSet();

         /// Extend dataset to nearest multiple of CHUNKLENGTH above supplied length
         void extend_dset(const unsigned long i);

      };


      /// @{ DataSetInterfaceBase class member definitions

      // Define some static members
      template<class T, std::size_t RR, std::size_t CL>
      const hid_t DataSetInterfaceBase<T,RR,CL>::hdftype_id = get_hdf5_data_type<T>::type();

      /// Constructors
      template<class T, std::size_t RR, std::size_t CL>
      DataSetInterfaceBase<T,RR,CL>::DataSetInterfaceBase()
        : mylocation_id(-1)
        , myname()
        , record_dims()
        , resume(false)
        , access('r')
	, dset_id(-1)
        , dsetnextemptyslab(0)
      {}

      template<class T, std::size_t RR, std::size_t CL>
      DataSetInterfaceBase<T,RR,CL>::DataSetInterfaceBase(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK], const bool r, const char a)
        : mylocation_id(location_id)
        , myname(name)
        , record_dims() /* doh have to copy array element by element */
        , resume(r)
        , access(a)
        , dset_id(-1)
        , dsetnextemptyslab(0)
      {
        if(resume)
        {
           dset_id = openDataSet(location_id,name,rdims);
        }
        else
        {
           dset_id = createDataSet(location_id,name,rdims);
        }
        if(dset_id<0)
        {
           std::ostringstream errmsg;
           errmsg << "Error! Failed to attach interface to dataset '"<<this->get_myname()<<"', and problem was not caught during open or create routine! This is a bug, please fix.";
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        // copy rdims to record_dims
        for(std::size_t i=0; i<DSETRANK; i++) { record_dims[i] = rdims[i]; }
      }

      /// Do cleanup (close dataset)
      template<class T, std::size_t RR, std::size_t CL>
      DataSetInterfaceBase<T,RR,CL>::~DataSetInterfaceBase()
      {
         // TODO: Having problems with copied objects sharing dataset identifiers, and closing datasets prematurely on each other.
         // To fix, will probably need to have a fancy copy constructor or something. Or wrap datasets in an
         // object which itself has a fancy copy constructor. For now, just leave dataset resources lying around,
         // probably won't cause any issues.
         // Or could explicity tell interface to close datasets before the objects are destroyed.
         //if(this->dset_id>=0)
         //{
         //  herr_t status = H5Dclose(this->dset_id);
         //  if(status<0)
         //  {
         //     logger() << LogTags::printers << LogTags::err <<LogTags::repeat_to_cerr<< LOCAL_INFO << ": Error destructing DataSetInterfaceBase! Failed to close wrapped dataset! (H5Dclose failed). No exception thrown because this will behave badly when throw from a destructor. (dataset name: "<<myname<<")"<<EOM;
         //  }
         //}
      }

      /// Release resources associated with the underlying dataset
      template<class T, std::size_t RR, std::size_t CL>
      void DataSetInterfaceBase<T,RR,CL>::closeDataSet()
      {
         if(this->dset_id>=0)
         {
           herr_t status = H5Dclose(this->dset_id);
           if(status<0)
           {
            std::ostringstream errmsg;
            errmsg << "Error closing dataset (with name: \""<<this->get_myname()<<"\") in HDF5 file. H5Dclose failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
           }
         }
      }

      /// Create a (chunked) dataset
      template<class T, std::size_t RECORDRANK, std::size_t CHUNKLENGTH>
      hid_t DataSetInterfaceBase<T,RECORDRANK,CHUNKLENGTH>::createDataSet(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK])
      {
         // I'd like to declare rdims as rdims[RECORDRANK], but apparantly zero length arrays are not allowed,
         // so this would not compile in the RECORDRANK=0 case, which I need. Irritating.

         // Compute initial dataspace and chunk dimensions
         dims[0] = 0; //1*CHUNKLENGTH; // Start off with space for 1 chunk
         maxdims[0] = H5S_UNLIMITED; // No upper limit on number of records allowed in dataset
         chunkdims[0] = CHUNKLENGTH;
         slicedims[0] = 1; // Dimensions of a single record in the data space
         std::size_t loopsize = RECORDRANK; // Just tricking the compiler so it doesn't complain in the RECORDRANK=0 case.
         for(std::size_t i=0; i<loopsize; i++)
         {
            // Set other dimensions to match record size
            dims[i+1]      = rdims[i];
            maxdims[i+1]   = rdims[i];
            chunkdims[i+1] = rdims[i];
            slicedims[i+1] = rdims[i];
         }

         // Create the data space
         //H5::DataSpace dspace(DSETRANK, dims, maxdims);
         hid_t dspace_id = H5Screate_simple(DSETRANK, dims, maxdims);
         if(dspace_id<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<name<<"\") in HDF5 file. H5Screate_simple failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Object containing dataset creation parameters
         //H5::DSetCreatPropList cparms;
         //cparms.setChunk(DSETRANK, chunkdims);
         hid_t cparms_id = H5Pcreate(H5P_DATASET_CREATE);
         if(cparms_id<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<name<<"\") in HDF5 file. H5Pcreate failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         herr_t status = H5Pset_chunk(cparms_id, DSETRANK, chunkdims);
         if(status<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error creating dataset (with name: \""<<name<<"\") in HDF5 file. H5Pset_chunk failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Check if location id is invalid
         if(location_id==-1)
         {
            std::ostringstream errmsg;
            errmsg << "Error! Tried to create hdf5 dataset (with name: \""<<myname<<"\") at undefined location (location_id was -1). Please check that calling code supplied a valid location handle. This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Create the dataset
         hid_t output_dset_id;
         output_dset_id = H5Dcreate2(location_id, name.c_str(), hdftype_id, dspace_id, H5P_DEFAULT, cparms_id, H5P_DEFAULT);
         //output = location->createDataSet( name.c_str(), hdf_dtype.type(), dspace, cparms);
         if(output_dset_id<0)
         {
               std::ostringstream errmsg;
               errmsg << "Error creating dataset (with name: \""<<myname<<"\") in HDF5 file. Dataset with same name may already exist";
               printer_error().raise(LOCAL_INFO, errmsg.str());
         }
         return output_dset_id;
      }

      /// Open an existing dataset
      /// It is assumed that we are resuming a run and therefore know what format this dataset should have
      template<class T, std::size_t RECORDRANK, std::size_t CHUNKLENGTH>
      hid_t DataSetInterfaceBase<T,RECORDRANK,CHUNKLENGTH>::openDataSet(hid_t location_id, const std::string& name, const std::size_t rdims[DSETRANK])
      {
         // Open the dataset
         hid_t out_dset_id = H5Dopen2(location_id, name.c_str(), H5P_DEFAULT);
         if(out_dset_id<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<name<<"\") in HDF5 file. H5Dopen2 failed." << std::endl
                   << "You may have a corrupt hdf5 file from a previous run. Try using -r, or deleting the old output.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Get dataspace of the dataset.
         //H5::DataSpace dataspace = dataset.getSpace();
         hid_t dspace_id = H5Dget_space(out_dset_id);
         if(dspace_id<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<name<<"\") in HDF5 file. H5Dget_space failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Get the number of dimensions in the dataspace.
         //int rank = dataspace.getSimpleExtentNdims();
         int rank = H5Sget_simple_extent_ndims(dspace_id);
         if(rank<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error opening existing dataset (with name: \""<<name<<"\") in HDF5 file. H5Sget_simple_extent_ndims failed.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }
         if(rank!=DSETRANK)
         {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name: \""<<myname<<"\") in HDF5 file. Rank of dataset ("<<rank<<") does not match the expected rank ("<<DSETRANK<<").";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Get the dimension size of each dimension in the dataspace
         // now that we know ndims matches DSETRANK.
         hsize_t dims_out[DSETRANK];
         //int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
         int ndims = H5Sget_simple_extent_dims(dspace_id, dims_out, NULL);
         if(ndims<0)
         {
            std::ostringstream errmsg;
            errmsg << "Error while accessing existing dataset (with name: \""<<myname<<"\") in HDF5 file. Failed to retrieve dataset extents (H5Sget_simple_extent_dims failed).";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // Update parameters to match dataset contents
         // Compute initial dataspace and chunk dimensions
         dims[0] = dims_out[0]; // Set to match existing data
         maxdims[0] = H5S_UNLIMITED; // No upper limit on number of records allowed in dataset
         chunkdims[0] = CHUNKLENGTH;
         slicedims[0] = 1; // Dimensions of a single record in the data space
         std::size_t loopsize = RECORDRANK; // Just tricking the compiler so it doesn't complain in the RECORDRANK=0 case.
         for(std::size_t i=0; i<loopsize; i++)
         {
            // Set other dimensions to match record size
            dims[i+1]      = rdims[i];
            maxdims[i+1]   = rdims[i];
            chunkdims[i+1] = rdims[i];
            slicedims[i+1] = rdims[i];

            // Check that record size matches the existing dataset
            if(dims[i+1] != dims_out[i+1])
            {
               std::ostringstream errmsg;
               errmsg << "Error while accessing existing dataset (with name: \""<<myname<<"\") in HDF5 file. Size of dimension "<<i+1<<" ("<<dims_out[i+1]<<") does not match the expected size ("<<dims[i+1]<<")";
               printer_error().raise(LOCAL_INFO, errmsg.str());
            }
         }

         // Update the variables which control where the next write will occur
         // Index of first element in next target hyperslab (assumes that
         // existing dataset has been written up to a complete chunk)
         dsetnextemptyslab = dims[0];

         return out_dset_id;
      }


      /// Extend dataset to nearest multiple of CHUNKLENGTH above supplied length
      template<class T, std::size_t RR, std::size_t CHUNKLENGTH>
      void DataSetInterfaceBase<T,RR,CHUNKLENGTH>::extend_dset(const unsigned long min_length)
      {
         std::size_t current_length = this->dsetdims()[0];
         if( min_length > current_length )
         {
            // Extend the dataset to the nearest multiple of CHUNKLENGTH above min_length,
            // unless min_length is itself a multiple of CHUNKLENGTH.
            std::size_t remainder = min_length % CHUNKLENGTH;
            std::size_t newlength;
            if(remainder==0) { newlength = min_length; }
            else             { newlength = min_length - remainder + CHUNKLENGTH; }
            #ifdef HDF5_DEBUG
            std::cout << "Requested min_length ("<<min_length<<") larger than current dataset length ("<<current_length<<") (dset name="<<this->get_myname()<<")" << std::endl
                      << "Extending dataset to newlength="<<newlength<<std::endl;
            #endif
            this->dsetdims()[0] = newlength;
            //this->my_dataset.extend( this->dsetdims() );
            herr_t status = H5Dset_extent( this->get_dset_id(), this->dsetdims());
            if(status<0)
            {
               std::cout<<this->get_dset_id()<<std::endl;
               std::ostringstream errmsg;
               errmsg << "Failed to extend dataset (with name: \""<<myname<<"\") from length "<<current_length<<" to length "<<newlength<<"!";
               printer_error().raise(LOCAL_INFO, errmsg.str());
            }
         }
      }
      /// @}

  }
}
#endif

