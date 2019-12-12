//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 printer retriever class definitions
///  This is a class accompanying the HDF5Printer
///  which takes care of *reading* from output
///  created by the HDF5Printer.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2017 Jan
///
///  *********************************************

#include "gambit/Printers/printers/hdf5reader.hpp"
#include "gambit/Printers/printers/hdf5printer.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Logs/logger.hpp"

namespace Gambit
{
  namespace Printers
  {

     // It's a little clumsy, but need to declare these type checking functions as extern templates here
     #define externGETTYPEID(r,data,i,elem) extern template std::size_t getTypeID<elem>();
     BOOST_PP_SEQ_FOR_EACH_I(externGETTYPEID, _, PRINTABLE_TYPES)
     #undef externGETTYPEID

     hid_t openfile_read(std::string file)
     {
        hid_t file_id = HDF5::openFile(file);
        if(file_id<0)
        {
            std::ostringstream errmsg;
            errmsg << "Error opening HDF5 file '"<<file<<"' for reading! See HDF5 error (stderr) for further details.";
            printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        return file_id;
     }

     // Post-process output of lsGroup to remove "_isvalid" datasets
     std::vector<std::string> lsGroup_process(hid_t location_id)
     {
        std::vector<std::string> ls_out;
        std::vector<std::string> ls_all = HDF5::lsGroup(location_id);
        for(std::vector<std::string>::iterator it = ls_all.begin();
            it != ls_all.end(); ++it)
        {
           if(not Utils::endsWith(*it,"_isvalid")) ls_out.push_back(*it);
        }
        return ls_out;
     }

     HDF5File::HDF5File(const std::string& file, const std::string& group)
      : file_id(openfile_read(file))
      , location_id(HDF5::openGroup(file_id, group, true))
     {}

     HDF5File::~HDF5File()
     {
        HDF5::closeGroup(location_id);
        HDF5::closeFile(file_id);
     }

     HDF5Reader::HDF5Reader(const Options& options)
      : file( options.getValue<std::string>("file"))
      , group( options.getValue<std::string>("group") )
      , H5file(file,group)
      , all_datasets(lsGroup_process(H5file.location_id))
      , pointIDs        (H5file.location_id, "pointID", true, 'r')
      , pointIDs_isvalid(H5file.location_id, "pointID_isvalid", true, 'r')
      , mpiranks        (H5file.location_id, "MPIrank", true, 'r')
      , mpiranks_isvalid(H5file.location_id, "MPIrank_isvalid", true, 'r')
      , current_dataset_index(0)
      , current_point(nullpoint)
     {
       if(all_datasets.size()<2)
       {
         std::ostringstream errmsg;
         errmsg << "Error opening HDF5 datasets for reading (file="<<file<<", group="<<group<<"). Less than two datasets detected in specified group (number found = "<<all_datasets.size()<<"). Please check that the input file and group are correct." <<std::endl;
         printer_error().raise(LOCAL_INFO, errmsg.str());
       }

       const std::size_t dset_length  = pointIDs.dset_length();
       const std::size_t dset_length2 = pointIDs_isvalid.dset_length();
       const std::size_t dset_length3 = mpiranks.dset_length();
       const std::size_t dset_length4 = mpiranks_isvalid.dset_length();
       if( (dset_length  != dset_length2)
        or (dset_length3 != dset_length4)
        or (dset_length  != dset_length3) )
       {
         std::ostringstream errmsg;
         errmsg << "Error opening HDF5 datasets for reading (file="<<file<<", group="<<group<<"). Unequal dataset lengths detected in pointID and MPIrank datasets:" <<std::endl;
         errmsg << "  pointIDs.dset_length()         = " << dset_length << std::endl;
         errmsg << "  pointIDs_isvalid.dset_length() = " << dset_length2 << std::endl;
         errmsg << "  mpiranks.dset_length()         = " << dset_length3 << std::endl;
         errmsg << "  mpiranks_isvalid.dset_length() = " << dset_length4 << std::endl;
         errmsg << "This most likely indicates corruption of the datasets (possibly due to unsafe shutdown).";
         printer_error().raise(LOCAL_INFO, errmsg.str());
       }
       //std::cout<<"Created HDF5 reader object for file "<<file<<std::endl;
     }

     HDF5Reader::~HDF5Reader()
     {
        // Need to close the datasets that aren't managed by a buffermanager object
        pointIDs.closeDataSet();
        mpiranks.closeDataSet();
        pointIDs_isvalid.closeDataSet();
        mpiranks_isvalid.closeDataSet();
        //std::cout<<"Deleted HDF5 reader object for file "<<file<<std::endl;
     }

     /// @{ Base class virtual interface functions

     /// Reset 'read head' position to first entry
     void HDF5Reader::reset()
     {
        current_dataset_index = 0;
        current_point = nullpoint;
     }

     /// Get length of input dataset
     ulong HDF5Reader::get_dataset_length()
     {
        return pointIDs.dset_length();
     }

     /// Get next rank/ptID pair in data file
     PPIDpair HDF5Reader::get_next_point()
     {
        // New method; just move dataset index and then try to retrieve the point
        ++current_dataset_index;
        current_point = get_current_point();
        return current_point;
     }

     /// Get current rank/ptID pair in data file
     PPIDpair HDF5Reader::get_current_point()
     {
        if(eoi())
        {
          // End of data, return nullpoint;
          current_point = nullpoint;
        }
        else
        {
          bool pvalid = pointIDs_isvalid.get_entry(current_dataset_index);
          bool mvalid = mpiranks_isvalid.get_entry(current_dataset_index);
          if(pvalid and mvalid)
          {
            unsigned long pid = pointIDs.get_entry(current_dataset_index);
            int mpirank       = mpiranks.get_entry(current_dataset_index);
            current_point = PPIDpair(pid,mpirank);
          }
          else
          {
            // No valid data here! Up to user to check.
            current_point = nullpoint;
          }
        }
        return current_point;
     }

     // Get a linear index which corresponds to the current rank/ptID pair in the iterative sense
     ulong HDF5Reader::get_current_index()
     {
       return current_dataset_index;
     }

     /// Check if 'current point' is past the end of the datasets (and thus invalid!)
     bool HDF5Reader::eoi()
     {
        bool result = current_dataset_index >= get_dataset_length();
        //if(result) std::cout <<"eoi? index="<<current_dataset_index<<", length="<<get_dataset_length()<<std::endl;
        return result;
     }

     /// Get type information for a data entry, i.e. defines the C++ type which this should be
     /// retrieved as, not what it is necessarily literally stored as in the output.
     std::size_t HDF5Reader::get_type(const std::string& label)
     {
        hid_t datatype_id = HDF5::getH5DatasetType(H5file.location_id, label);
        // Need to match HDF5 datatype to a printer type ID code.
        // In principle we may like to retrieve a certain type of data in a fancy way,
        // as with ModelParameters or vectors, however we can't really do that in an
        // automated way because this higher-level information is lost during output.
        // So the type matching has to be of a basic sort, i.e. individual ModelParameters
        // elements will be identified as 'double' and so on. But if they are stored that
        // way in the output, then we should be able to copy them that way too (which is
        // the main usage of this get_type function), so this should be ok to do.
        // Currently we only store data in basic types, so those are all that this
        // function needs to retrieve.

        // DEBUG
        // std::cout << "Retrieved H5 type for '"<<label<<"': "<<datatype_id<<std::endl;
        // printAllTypeIDs();
        // printAllH5Types();
        // END DEBUG

        // Matching of HDF5 datatypes to Printer type IDs
        // Need to use H5Tequal to check if the HDF5 type IDs are equal
        std::size_t typeID=0;
        #define GET_TYPE_CASES(r,data,elem)                          \
        if( H5Tequal(datatype_id, get_hdf5_data_type<elem>::type()) )\
        {                                                            \
            typeID = getTypeID<elem>();                              \
        }                                                            \
        else
        BOOST_PP_SEQ_FOR_EACH(GET_TYPE_CASES, , H5_OUTPUT_TYPES)
        #undef GET_TYPE_CASES
        {
          std::ostringstream err;
          err << "Did not recognise retrieved HDF5 type for data label '"<<label<<"'! This may indicate a bug in the Reader class you are using, please report it.";
          printer_error().raise(LOCAL_INFO,err.str());
        }
        if(typeID==0)
        {
          std::ostringstream err;
          err << "Did not recognise retrieved Printer type for data label '"<<label<<"'! This may indicate a bug in the Printer system, please report it.";
          printer_error().raise(LOCAL_INFO,err.str());
        }
        /// Release HDF5 type ID number
        HDF5::closeType(datatype_id);
        return typeID;
     }

     /// Get labels of all datasets in the linked group
     std::set<std::string> HDF5Reader::get_all_labels()
     {
        std::set<std::string> out(all_datasets.begin(), all_datasets.end());
        return out;
     }

     /// @}

     /// @{ Private functions

     /// Search for the PPID supplied in the input data and return the index of the first match
     ulong HDF5Reader::get_index_from_PPID(const PPIDpair ppid)
     {
        ulong out_index=0;
        if(ppid == current_point)
        {
           // Matches current point; send it out
           out_index = current_dataset_index;
        }
        else if(ppid == mem_point)
        {
           // Matches stored point; send it out
           out_index = mem_index;
        }
        else
        {
           // Gotta search for it.
           std::ostringstream errmsg;
           errmsg << "Arbitrary point access has not yet been implemented for the HDF5Reader! Currently only iterated access through a dataset works.";
           printer_error().raise(LOCAL_INFO, errmsg.str());
        }
        mem_point = ppid;
        mem_index = out_index;
        return out_index;
     }

     /// @}

  }
}
