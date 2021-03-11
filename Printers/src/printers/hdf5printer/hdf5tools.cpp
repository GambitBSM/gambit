//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A collection of tools for interacting with
///  HDF5 databases.
///
///  Currently I am using the C++ bindings for
///  HDF5, however they are a bit crap and it may
///  be better to just write our own.
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

#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Logs/logger.hpp"

#include <stdio.h>
#include <string.h>
#include <iostream>

// Boost
#include <boost/preprocessor/seq/for_each.hpp>

namespace Gambit {
  namespace Printers {

    namespace HDF5 {

      /// GAMBIT default file access property list
      //  Sets some HDF5 properties to associate with open objects
      //  Here we set objects to be 'evicted' from the metadata cache
      //  when they are closed, which apparantly is not the default
      //  which leads to massive RAM usage if we don't set this.
      hid_t create_GAMBIT_fapl()
      {
         hid_t fapl(H5Pcreate(H5P_FILE_ACCESS)); // Copy defaults
         //std::cout<<"HDF5 version:"<<H5_VERS_MAJOR<<"."<<H5_VERS_MINOR<<"."<<H5_VERS_RELEASE<<std::endl;
         #if (H5_VERS_MAJOR > 1) || \
             (H5_VERS_MAJOR == 1) && H5_VERS_MINOR > 10 || \
             (H5_VERS_MAJOR == 1) && H5_VERS_MINOR == 10 && H5_VERS_RELEASE >= 1
         hbool_t value = 1; // true?
         // This function does not appear before v 1.10.1, however it is
         // pretty crucial, at least in my version of HDF5, for keeping the
         // metadata cache from consuming all my RAM. However, Anders commented
         // it out with his older HDF5 version and still had no RAM problem.
         // So it might be ok to just remove it for older versions.
         // However, if you see RAM blowouts and your HDF5 version is old,
         // then this is probably the reason.
         H5Pset_evict_on_close(fapl, value); // Set evict_on_close = true
         //std::cout <<"GAMBIT fapl used!"<<std::endl; // Check that this code is built...
         #endif

        return fapl;
      }

      /// Const global for the GAMBIT fapl
      const hid_t H5P_GAMBIT(create_GAMBIT_fapl());

      /// Macro to define simple wrappers with error checking for basic HDF5 tasks
      #define SIMPLE_CALL(IDTYPE_OUT, FNAME, IDTYPE_IN, H5FUNCTION, VERB, OUTPUTNAME, INPUTNAME) \
      IDTYPE_OUT FNAME(IDTYPE_IN id) \
      { \
         if(id < 0) \
         { \
            std::ostringstream errmsg; \
            errmsg << "Failed to "<<VERB<<" "<<OUTPUTNAME<<" for HDF5 dataset! The supplied id does not point to a successfully opened "<<INPUTNAME<<"!"; \
            printer_error().raise(LOCAL_INFO, errmsg.str()); \
         } \
         IDTYPE_OUT out_id = H5FUNCTION(id); \
         if(out_id < 0) \
         { \
            std::ostringstream errmsg; \
            errmsg << "Failed to "<<VERB<<" "<<OUTPUTNAME<<" for HDF5 dataset! See HDF5 error output for more details."; \
            printer_error().raise(LOCAL_INFO, errmsg.str()); \
         } \
         return out_id; \
      }

      hid_t closeFile(hid_t id)
      {
         if(id < 0)
         {
            std::ostringstream errmsg;
            errmsg << "Failed to close HDF5 file with ID "<<id<<"! The supplied id does not point to a successfully opened file.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }
  
         // Check for any open objects! These should all be closed before the file is closed for maximum safety
         ssize_t count = H5Fget_obj_count(id, H5F_OBJ_ALL);
         if(count > 1)
         {
            logger()<<LogTags::warn<<LogTags::repeat_to_cerr;
            logger() << "Warning! "<<count<<" open objects detected when closing HDF5 file with ID "<<id<<"! Please check your code and ensure that all datasets, groups, selections, etc. are closed before closing the files they belong to."<<std::endl;
            logger() << "Beginning analysis of open objects..."<<std::endl;
            count = H5Fget_obj_count(id, H5F_OBJ_FILE);
            if(count>1) logger() << "   "<<count<<" H5F_OBJ_FILE detected (should only be 1, for the open file itself)"<<std::endl;
            count = H5Fget_obj_count(id, H5F_OBJ_GROUP);
            if(count>0) logger() << "   "<<count<<" H5F_OBJ_GROUP detected"<<std::endl;
            count = H5Fget_obj_count(id, H5F_OBJ_DATASET);
            if(count>0) logger() << "   "<<count<<" H5F_OBJ_DATASET detected"<<std::endl;
            count = H5Fget_obj_count(id, H5F_OBJ_DATATYPE);
            if(count>0) logger() << "   "<<count<<" H5F_OBJ_DATATYPE detected"<<std::endl;
            count = H5Fget_obj_count(id, H5F_OBJ_ATTR);
            if(count>0) logger() << "   "<<count<<" H5F_OBJ_ATTR detected"<<std::endl;
            logger()<<EOM;
         }

         hid_t out_id = H5Fclose(id);
         if(out_id < 0)
         {
            std::ostringstream errmsg;
            errmsg << "Failed to close HDF5 file with ID "<<id<<"! See HDF5 error output for more details.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }
         //std::cout<<"Called H5Fclose on file with ID "<<id<<std::endl;
         return out_id;
      }


      template<>
      std::vector<bool> getChunk(const hid_t dset_id, std::size_t offset, std::size_t length)
      {
          // Buffer to receive data (and return from function)
          std::vector<uint8_t> chunkdata(length);
 
          // Select hyperslab
          std::pair<hid_t,hid_t> selection_ids = selectChunk(dset_id,offset,length);
          hid_t memspace_id = selection_ids.first;
          hid_t dspace_id   = selection_ids.second;

          // Buffer to receive data
          void* buffer = chunkdata.data(); // pointer to contiguous memory within the buffer vector

          // Get the data from the hyperslab.
          hid_t hdftype_id = get_hdf5_data_type<bool>::type(); // It is assumed that you already know this is the right type for the dataset!
          herr_t err_read = H5Dread(dset_id, hdftype_id, memspace_id, dspace_id, H5P_DEFAULT, buffer);

          if(err_read<0)
          {
              std::ostringstream errmsg;
              errmsg << "Error retrieving chunk (offset="<<offset<<", length="<<length<<") from dataset in HDF5 file. H5Dread failed." << std::endl;
              errmsg << "  offset+length = "<< offset+length << std::endl;
              printer_error().raise(LOCAL_INFO, errmsg.str());
          }

          H5Sclose(dspace_id);
          H5Sclose(memspace_id);
 
          std::vector<bool> chunkdata_bool;
          for(auto it=chunkdata.begin(); it!=chunkdata.end(); ++it)
          {
              chunkdata_bool.push_back(*it);
          }

          return chunkdata_bool;
      }
 
      /// Create or open hdf5 file (ignoring feedback regarding whether file already existed)
      hid_t openFile(const std::string& fname, bool overwrite, const char access_type)
      {
         bool tmp;
         return openFile(fname,overwrite,tmp,access_type);
      }

      /// Create or open hdf5 file
      /// third argument "oldfile" is used to report whether an existing file was opened (true if yes)
      hid_t openFile(const std::string& fname, bool overwrite, bool& oldfile, const char access_type)
      {
          //Debug
          //std::cerr<<"Attempting to open file "<<fname<<" in mode "<<access_type<<" (overwrite="<<overwrite<<")"<<std::endl;

          hid_t file_id;  // file handle

          unsigned int atype=0;
          switch(access_type)
          {
            case 'r':
              atype = H5F_ACC_RDONLY;
              break;
            case 'w':
              // We let 'w' mean read/write here
              atype = H5F_ACC_RDWR;
              break;
            default:
              std::ostringstream errmsg;
              errmsg << "Unrecognised access mode requested while trying to open HDF5 file! Saw '"<<access_type<<"'; only 'r' (read-only) and 'w' (read/wrtie) are valid. File was ("<<fname<<")";
              printer_error().raise(LOCAL_INFO, errmsg.str());
              break;
          }

          if(overwrite)
          {
            // DANGER! Deletes existing file
            if( remove(fname.c_str()) != 0 )
            {
              // Error deleting file, but probably it just didn't exist to delete
              logger()<<LogTags::utils<<LogTags::warn<<"Failed to delete file '"<<fname<<"'! Maybe it didn't exist in the first place."<<EOM;
            }
            else// else deleted file with no problem
            {
              logger()<<LogTags::utils<<LogTags::info<<"Deleted pre-existing file "<<fname<<" (because overwrite=true)"<<EOM;
            }
          }

          errorsOff();
          file_id = H5Fopen(fname.c_str(), atype, H5P_GAMBIT);
          errorsOn();
          if(file_id < 0)
          {
             if(access_type=='w')
             {
                /* Ok maybe file doesn't exist yet, try creating it */
                errorsOff();
                file_id = H5Fcreate(fname.c_str(), H5F_ACC_EXCL, H5P_DEFAULT, H5P_GAMBIT);
                errorsOn();
                if(file_id < 0)
                {
                   /* Still no good; error */
                   std::ostringstream errmsg;
                   errmsg << "Failed to open existing HDF5 file, then failed to create new one! ("<<fname<<"). The file may exist but be unreadable. You can check this by trying to inspect it with the 'h5ls' command line tool.";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                else
                {
                   /* successfully created new file */
                   oldfile = false;
                }
             }
             else
             {
               // Doesn't make sense to create new file if we wanted read-only mode. Error.
               std::ostringstream errmsg;
               errmsg << "Failed to open existing HDF5 file, and did not create new one since read-only access was specified. ("<<fname<<")";
               printer_error().raise(LOCAL_INFO, errmsg.str());
             }
          }
          else
          {
             /* successfully opened existing file */
             oldfile = true;
          }

          // DEBUG
          //std::cout<<"Opened file "<<fname<<" in mode "<<access_type<<", and assigned it ID "<<file_id<<std::endl;

          /* Return the file handle */
          return file_id;
      }

      /// Check if hdf5 file exists and can be opened in read mode
      bool checkFileReadable(const std::string& fname, std::string& msg)
      {
          bool readable(false);

          errorsOff();
          hid_t file_id = H5Fopen(fname.c_str(), H5F_ACC_RDONLY, H5P_GAMBIT);
          errorsOn();
          if(file_id < 0)
          {
            readable=false;
            std::ostringstream errmsg;
            errmsg<<"H5Fopen failed (tried to open '"<<fname<<"')";
            msg = errmsg.str();
          }
          else
          {
            /* everything fine, close the file */
            herr_t status = H5Fclose(file_id);
            if(status<0)
            {
                std::ostringstream errmsg;
                errmsg << "Failed to properly close HDF5 file after successfully checking that it was readable! ("<<fname<<")";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            readable=true;
          }
          // DEBUG
          std::cout<<"Checked that file "<<fname<<" was readable (had RDONLY access and ID "<<file_id<<")"<<std::endl;
          return readable;
      }

      /// Check if a group exists and can be accessed
      bool checkGroupReadable(hid_t location, const std::string& groupname, std::string& msg)
      {
          hid_t group_id;
          bool readable(false);

          errorsOff();
          group_id = H5Gopen2(location, groupname.c_str(), H5P_DEFAULT);
          errorsOn();
          if(group_id < 0)
          {
            readable=false;
            std::ostringstream errmsg;
            errmsg<<"H5Gopen failed (tried to open '"<<groupname<<"' from location with id "<<location<<")";
            msg = errmsg.str();
          }
          else
          {
            /* everything fine, close the group */
            herr_t status = H5Gclose(group_id);
            if(status<0)
            {
                std::ostringstream errmsg;
                errmsg << "Failed to properly close HDF5 group after successfully checking that it was readable! ("<<groupname<<")";
                printer_error().raise(LOCAL_INFO, errmsg.str());
            }
            readable=true;
          }
          return readable;
      }

      template<class T>
      std::pair<bool,std::size_t> _checkDatasetReadable_helper(hid_t dset_id, const std::string dset_name)
      {
          static const std::size_t CHUNK(1000);
          std::vector<T> buffer(CHUNK);
          bool fully_readable(true);
          std::size_t largest_readable_index(0);

          // Get dataset length
          hid_t dspace_id = getSpace(dset_id);
          if(dspace_id<0)
          {
              fully_readable = false;
          }
          else
          {
              size_t dset_length(0);
              bool length_error(false);
              try
              {
                  dset_length = getSimpleExtentNpoints(dspace_id);
              }
              catch(const Gambit::exception& e)
              {
                  fully_readable = false;
                  length_error = true;
              }
              closeSpace(dspace_id);

              if(not length_error)
              {
                  // Begin trying to read data
                  std::size_t Nchunks   = dset_length / CHUNK;
                  std::size_t remainder = dset_length % CHUNK;
                  if(remainder!=0) Nchunks+=1;
                  std::size_t offset(0);
                  std::size_t length(0);
                  errorsOff();
                  for(std::size_t i=0; i<Nchunks; i++)  
                  {
                      offset = i * CHUNK;
                      length = CHUNK;
                      if(remainder!=0 and (i+1)==Nchunks) length = remainder;
                      try
                      {
                          errorsOff();
                          buffer = getChunk<T>(dset_id, offset, length);
                      }
                      catch(const Gambit::exception& e)
                      {
                          fully_readable = false;
                      }
                      if(not fully_readable) break;
                  }
                  errorsOn();

                  if(not fully_readable)
                  {
                      // Try to find highest readable index in the dataset
                      // We know it is somewhere in the last chunk we were reading.
                      // Could do a more efficient search, but we will just look
                      // sequentially from the beginning of the chunk

                      errorsOff();
                      for(std::size_t j=offset; j<offset+length; j++)
                      {
                          try
                          {
                              std::vector<T> jbuffer = getChunk<T>(dset_id, j, 1);
                              largest_readable_index = j;
                          }
                          catch(const Gambit::exception& e)
                          {
                              break;
                          }
                      }
                      errorsOn();

                      if(largest_readable_index==dset_length)
                      {
                          // Chunked read failed, but individual reads succeeded? Weird.
                          // Will have to abandon our efforts and make the user investigate
                          // manually
                          std::ostringstream err;
                          err<<"Dataset "<<dset_name<<" was determined to be partially unreadable (corrupted), however we were unable to determine the largest readable index. You will have to investigate the HDF5 file manually.";
                          printer_error().raise(LOCAL_INFO,err.str());
                      }
                  }
                  else
                  {
                      // Everything seems fine with this dataset
                      largest_readable_index = dset_length;
                  }
              }
          }
          return std::make_pair(fully_readable,largest_readable_index);
      }
 
      /// Check if a dataset exists and can be read from fully
      /// (Reads through entire dataset to make sure! May take some time)
      std::pair<bool,std::size_t> checkDatasetReadable(hid_t location, const std::string& dsetname)
      {
          std::pair<bool,std::size_t> readable_info(false,0);
          hid_t dataset_id = openDataset(location, dsetname);
          if(dataset_id<0)
          {
              //msg += "Failed to open dataset";
          }
          else
          {
              hid_t datatype_id = H5Dget_type(dataset_id);
              if(datatype_id<0)
              {
                  //msg += "Failed to obtain type of dataset";
              }
              else
              { 
                  // Need buffers of various types depending of type of dataset.
                  // Can achieve this with some macros and a templated helper function
                  #define RUN_TYPE_DEPENDENT_CHECK(r,data,elem) \
                  if( H5Tequal(datatype_id, get_hdf5_data_type<elem>::type()) )\
                  {\
                      readable_info = _checkDatasetReadable_helper<elem>(dataset_id,dsetname);\
                  }\
                  else
                  BOOST_PP_SEQ_FOR_EACH(RUN_TYPE_DEPENDENT_CHECK, _, H5_OUTPUT_TYPES)
                  #undef RUN_TYPE_DEPENDENT_CHECK
                  {
                      std::ostringstream err;
                      err << "Did not recognise retrieved HDF5 type for dataset '"<<dsetname<<"'! This may indicate a bug in the GAMBIT HDF5 tools library, please report it.";
                      printer_error().raise(LOCAL_INFO,err.str());
                  }
              }
          }
          closeDataset(dataset_id);
          return readable_info;
      }

      /// Create hdf5 file (always overwrite existing files)
      hid_t createFile(const std::string& fname)
      {
          hid_t file_id = H5Fcreate(fname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_GAMBIT);
          if(file_id < 0)
          {
             /* Still no good; error */
             std::ostringstream errmsg;
             errmsg << "Failed to create HDF5 file '"<<fname<<"'!";
             printer_error().raise(LOCAL_INFO, errmsg.str());
          }
          return file_id;
      }

      /// Create a group inside the specified location
      // Argument "location" can be a handle for either a file or another group
      hid_t createGroup(hid_t location, const std::string& name)
      {
          hid_t group_id;

          group_id = H5Gcreate2(location, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
          if(group_id<0)
          {
              std::ostringstream errmsg;
              errmsg << "Error creating HDF5 group '"<<name<<"'";
              printer_error().raise(LOCAL_INFO, errmsg.str());
          }
          return group_id;
      }

      // Modified minimally from https://github.com/gregreen/h5utils/blob/master/src/h5utils.cpp#L92
      // Credit: Gregory Green 2012
      /*
       * Opens a group, creating it if it does not exist. Nonexistent parent groups are also
       * created. This works similarly to the Unix/Linux command
       * mkdir -p /parent/subgroup/group
       * in that if /parent and /parent/subgroup do not exist, they will be created.
       *
       * If no accessmode has H5Utils::DONOTCREATE flag set, then returns NULL if group
       * does not yet exist.
       *
       */
      hid_t openGroup(hid_t file_id, const std::string& name, bool nocreate) //, int accessmode)
      {
         hid_t group_id;

         if(file_id < 0)
         {
            std::ostringstream errmsg;
            errmsg << "Error opening HDF5 group '"<<name<<"'. The supplied file_id does not point to a successfully opened file!";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         // User does not want to create group
         if(nocreate) //accessmode & H5Utils::DONOTCREATE)
         {
            group_id = H5Gopen2(file_id, name.c_str(), H5P_DEFAULT);
            if(group_id<0)
            {
              std::ostringstream errmsg;
              errmsg << "Error opening HDF5 group '"<<name<<"'. Group (probably) does not exist, and 'nocreate' flag is set to 'true', so we will not attempt to create one";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
         }
         else
         {
            // Possibly create group and parent groups
            std::stringstream ss(name);
            std::stringstream path;
            std::string gp_name;
            while(std::getline(ss, gp_name, '/'))
            {
               path << "/" << gp_name;
               errorsOff();
               group_id = H5Gopen2(file_id, path.str().c_str(), H5P_DEFAULT);
               errorsOn();
               if(group_id<0)
               {
                  /* doesn't exist; try to create it */
                  group_id = H5Gcreate2(file_id, path.str().c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                  if(group_id<0)
                  {
                    std::ostringstream errmsg;
                    errmsg << "Error while recursively creating/opening group '"<<name<<"'. Failed to create group '"<<path.str()<<"'";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                  }
               }
               herr_t err = H5Gclose(group_id);
               if(err<0)
               {
                  std::ostringstream errmsg;
                  errmsg << "Error closing group '"<<name<<"'!";
                  printer_error().raise(LOCAL_INFO, errmsg.str());
               }
            }
            // Should exist now; open the group and return the handle
            group_id = H5Gopen2(file_id, name.c_str(), H5P_DEFAULT);
            if(group_id<0)
            {
              std::ostringstream errmsg;
              errmsg << "Error opening HDF5 group '"<<name<<"' after recursive creation supposedly succeeded! There must be a bug in this routine, please fix.";
              printer_error().raise(LOCAL_INFO, errmsg.str());
            }
        }
        return group_id;
      }

      // Iterator function for listing datasets in a group
      herr_t group_ls(hid_t g_id, const char *name, const H5L_info_t* /*info*/, void *op_data)
      {
          //std::cout<<"group_ls: "<<name<<std::endl;
          //std::cout<<info->type<<" "<<H5G_DATASET<<std::endl;
          std::vector<std::string>* out = static_cast<std::vector<std::string>*>(op_data);
          // Only add names that correspond to datasets
          H5G_stat_t statbuf;
          H5Gget_objinfo(g_id, name, false, &statbuf);
          if(statbuf.type == H5G_DATASET) out->push_back(name);
          return 0;
      }

      /// List object names in a group
      std::vector<std::string> lsGroup(hid_t group_id)
      {
         if(group_id<0)
         {
           std::ostringstream errmsg;
           errmsg << "Error inspecting HDF5 group. The supplied group_id does not point to an open group object!";
           printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         std::vector<std::string> out;
         herr_t err = H5Literate(group_id, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, group_ls, &out);

         if(err<0)
         {
           std::ostringstream errmsg;
           errmsg << "Error encountering while iterating through HDF5 group! See HDF5 error for more details (stderr).";
           printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         return out;
      }

      /// Check if an object in a file or group is a dataset
      bool isDataSet(hid_t loc_id, const std::string& name)
      {
          H5O_info_t object_info;
          herr_t err = H5Oget_info_by_name(loc_id, name.c_str(), &object_info, H5P_DEFAULT);
          if(err<0)
          {
              std::ostringstream errmsg;
              errmsg << "Attempt to check if object named '"<<name<<"' is a dataset failed! See HDF5 error for more details (stderr).";
              printer_error().raise(LOCAL_INFO, errmsg.str()); 
          }
          return object_info.type == H5O_TYPE_DATASET;
      }

      /// Get type of a dataset in a group
      /// NOTE: Make sure to call closeType when the ID is no longer needed!
      hid_t getH5DatasetType(hid_t group_id, const std::string& dset_name)
      {
          hid_t dataset_id = openDataset(group_id, dset_name);
          if(dataset_id<0)
          {
            std::ostringstream errmsg;
            errmsg << "Failed to open dataset '"<<dset_name<<"' while attempting to check its HDF5 data type! See stderr output for more details.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
          }
          hid_t type_id = H5Dget_type(dataset_id);
          if(type_id<0)
          {
            std::ostringstream errmsg;
            errmsg << "Failed to get HDF5 type of dataset '"<<dset_name<<"'. See stderr output for more details.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
          }
          closeDataset(dataset_id);
          return type_id;
      }

      /// Close hdf5 type ID
      SIMPLE_CALL(hid_t, closeType,  hid_t, H5Tclose, "close", "type ID", "type ID")

      /// Close hdf5 group
      SIMPLE_CALL(hid_t, closeGroup,  hid_t, H5Gclose, "close", "group", "group")

      /// global error variables (handler)
      H5E_auto2_t old_func;
      void *old_client_data;

      // FIXME: This caused compile problems on LISA cluster (CW)
      /// Silence error report (e.g. while probing for file existence)
      /// Just silences default error stack, since we aren't using anything else
      /// TESTING! I changed from using
      ///   H5Eget_auto
      /// to
      ///   H5Eget_auto2
      /// If that still causes errors, try switching to
      ///   H5Eget_auto1
      /// and let me know if it works :)
      void errorsOff()
      {
         /* Save old error handler */
         H5Eget_auto2(H5E_DEFAULT, &old_func, &old_client_data);

         /* Turn off error handling */
         H5Eset_auto2(H5E_DEFAULT, NULL, NULL);
      }

      /// Restore error report
      void errorsOn()
      {
         /* Restore previous error handler */
         H5Eset_auto2(H5E_DEFAULT, old_func, old_client_data);
      }

      /// @{ Dataset manipulations

      /// Open dataset
      // Set error_off=true to manually check for successful dataset opening.
      hid_t openDataset(hid_t group_id, const std::string& name, bool error_off)
      {
         hid_t dset_id;

         if(group_id < 0)
         {
            std::ostringstream errmsg;
            errmsg << "Error opening HDF5 dataset '"<<name<<"'. The supplied group_id in which the dataset should be located does not point to a successfully opened group!";
            printer_error().raise(LOCAL_INFO, errmsg.str());
         }

         dset_id = H5Dopen2(group_id, name.c_str(), H5P_DEFAULT);
         if(dset_id<0 and not error_off)
         {
           std::ostringstream errmsg;
           errmsg << "Error opening HDF5 dataset '"<<name<<"'. Dataset may not exist at the specified location.";
           printer_error().raise(LOCAL_INFO, errmsg.str());
         }
         return dset_id;
      }

      /// Close dataset
      SIMPLE_CALL(hid_t, closeDataset,  hid_t, H5Dclose, "close", "dataset", "dataset")

      /// Open/close dataspace; input dataset, output dataspace
      SIMPLE_CALL(hid_t, getSpace,  hid_t, H5Dget_space, "get", "dataspace", "dataset")
      SIMPLE_CALL(hid_t, closeSpace, hid_t, H5Sclose, "close", "dataspace", "dataspace")

      /// Get simple dataspace extent (number of points); input dataspace, output data extent (size)
      SIMPLE_CALL(hssize_t, getSimpleExtentNpoints,  hid_t, H5Sget_simple_extent_npoints, "get", "simple_extent_npoints", "dataspace")

      /// Get dataset name
      std::string getName(hid_t dset_id)
      {
          size_t len = H5Iget_name(dset_id,NULL,0);
          char buffer[len];
          H5Iget_name(dset_id,buffer,len+1);
          std::string n = buffer;
          return n;
      }

      /// Select a simple hyperslab in a 1D dataset
      std::pair<hid_t,hid_t> selectChunk(const hid_t dset_id, std::size_t offset, std::size_t length)
      {
          // Open dataspace
          hid_t dspace_id = getSpace(dset_id);

          // Make sure that the requested chunk lies within the dataset extents
          size_t dset_length = getSimpleExtentNpoints(dspace_id);

          if(offset + length > dset_length)
          {
             std::ostringstream errmsg;
             errmsg << "Error selecting chunk from dataset in HDF5 file. Tried to select a hyperslab which extends beyond the dataset extents:" << std::endl;
             errmsg << "  offset = " << offset << std::endl;
             errmsg << "  offset+length = " << length << std::endl;
             errmsg << "  dset_length  = "<< dset_length << std::endl;
             printer_error().raise(LOCAL_INFO, errmsg.str());
          }

          // Select a hyperslab.
          static const size_t DSETRANK(1); // assuming 1D dataset
          hsize_t offsets[DSETRANK];
          offsets[0] = offset;
          hsize_t selection_dims[DSETRANK]; // Set same as output chunks, but may have a different length
          selection_dims[0] = length; // Adjust chunk length to input specification

          herr_t err_hs = H5Sselect_hyperslab(dspace_id, H5S_SELECT_SET, offsets, NULL, selection_dims, NULL);
          if(err_hs<0)
          {
             std::ostringstream errmsg;
             errmsg << "Error selecting chunk from dataset (offset="<<offset<<", length="<<selection_dims[0]<<") in HDF5 file. H5Sselect_hyperslab failed." << std::endl;
             printer_error().raise(LOCAL_INFO, errmsg.str());
          }

          // Define memory space
          hid_t memspace_id = H5Screate_simple(DSETRANK, selection_dims, NULL);

          #ifdef HDF5_DEBUG
          std::cout << "Debug variables:" << std::endl
                    << "  dsetdims()[0]      = " << this->dsetdims()[0] << std::endl
                    << "  offsets[0]         = " << offsets[0] << std::endl
                    << "  CHUNKLENGTH        = " << CHUNKLENGTH << std::endl
                    << "  selection_dims[0] = " << selection_dims[0] << std::endl;
          #endif

          return std::make_pair(memspace_id, dspace_id); // Be sure to close these identifiers after using them!
      }

      /// @}
 
      // Match fixed integers to HDF5 types
      int inttype_from_h5type(hid_t h5type)
      {
          #define ELSEIF(r,data,elem) \
            else if(H5Tequal(h5type,get_hdf5_data_type<elem>::type())) \
            { \
               out = h5v2_type<elem>(); \
            }

          int out;
          if(h5type==-1)
          {
              std::ostringstream errmsg;
              errmsg<<"No fixed ID assigned for this type! (h5type = "<<h5type<<")!";
              printer_error().raise(LOCAL_INFO, errmsg.str());        
          }
          BOOST_PP_SEQ_FOR_EACH(ELSEIF, _, H5_OUTPUT_TYPES)
          #undef ELSEIF
          else
          {
              std::ostringstream errmsg;
              errmsg<<"Unrecognised HDF5 type (h5type = "<<h5type<<")!";
              printer_error().raise(LOCAL_INFO, errmsg.str());       
          }
          return out;
      }

      // Query whether type integer indicates general 'float' or 'int'
      bool is_float_type(int inttype)
      {
          bool out(false);
          switch(inttype)
          {
              case h5v2_type<int               >():
              case h5v2_type<unsigned int      >():
              case h5v2_type<long              >():
              case h5v2_type<unsigned long     >():
              case h5v2_type<long long         >():
              case h5v2_type<unsigned long long>():
                  out = false;
                  break;
              case h5v2_type<float             >():
              case h5v2_type<double            >():
                  out = true;
                  break;
          }
          return out;
      }

    }

    /// DEBUG: print to stdout all HDF5 type IDs
    void printAllH5Types(void)
    {
       std::cout << "Types known to get_hdf5_data_type<T>::type() function:" << std::endl;
       #define PRINTTYPEID(r,data,elem) \
         std::cout << "  Type: " << STRINGIFY(elem) << ", H5 type code: " << get_hdf5_data_type<elem>::type() << std::endl;
       BOOST_PP_SEQ_FOR_EACH(PRINTTYPEID, _, H5_OUTPUT_TYPES)
       #undef PRINTTYPEID
    }

  }
}



