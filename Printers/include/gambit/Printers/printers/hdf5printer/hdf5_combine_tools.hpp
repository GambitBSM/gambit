//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Greg's code for combining HDF5 output of
///  multiple MPI processes. Replaces the old
///  Python script
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date ???
///
///
///  *********************************************
 
#ifndef __hdf5_combine_tools_hpp__
#define __hdf5_combine_tools_hpp__

#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map> 
#include <hdf5.h>

#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Utils/new_mpi_datatypes.hpp"

namespace Gambit
{
    namespace Printers
    {
        namespace HDF5 
        {
            template <typename T>
            inline T type_ret(){return T();}

            template <class U, typename... T>
            void Enter_HDF5(hid_t dataset, T&... params);

            /// Select a chunk of a 1D HDF5 dataset
            std::pair<hid_t,hid_t> select_chunk(hid_t dset_id, std::size_t offset, std::size_t length);

            struct read_hdf5
            {
                template <typename U, typename T>
                static void run(U, hid_t &dataset, std::vector <T> &vec)
                {
                    hid_t dataspace = H5Dget_space(dataset);
                    hssize_t dim_t = H5Sget_simple_extent_npoints(dataspace);
                    std::vector<U> data(dim_t);
                    H5Dread( dataset, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                    vec = std::vector<T>(data.begin(), data.end());
                    H5Sclose(dataspace);
                }
            };

            struct copy_hdf5
            {
                template <typename U>
                static void run(U, hid_t &dataset_out, std::vector<hid_t> &datasets, unsigned long long &size_tot, std::vector<unsigned long long> &sizes, hid_t &old_dataset)
                {
                    std::vector<U> data(size_tot);
                    unsigned long long j = 0;
                    
                    if (old_dataset >= 0)
                    {
                        hid_t space = H5Dget_space(old_dataset);
                        hsize_t dim_t = H5Sget_simple_extent_npoints(space);
                        //data.resize(dim_t + size_tot); // This should be unnecessary; size_tot should include the old 
                        //dataset points already.
                        //But let's make sure there is space.
                        if( dim_t > size_tot)
                        {
                           // The old dataset is larger than the total size allocated for all data! size_tot must have been
                           // measured wrong!
                           std::ostringstream errmsg;
                           errmsg << "Error copying parameter "". Buffer overrun while reading dataset from the old combined file. (Dataset in file had size "<<dim_t<<", but there was only size "<<data.size()<<" allocated to the read buffer; data.size()="<<data.size()<<")"<<std::endl;
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                        }

                        // Read in the old dataset for this parameter
                        herr_t err_read = H5Dread(old_dataset, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                        if(err_read<0)
                        {
                           std::ostringstream errmsg;
                           errmsg << "Error copying parameter "". An error was reported during the H5Dread operation (while reading in old combined data from previous run). This is probably a bug in the HDF5Printer, please report it."<<std::endl;
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                        j = dim_t; // Set next free position to after old data
                        H5Sclose(space);
                    }
                    
                    for (int i = 0, end = datasets.size(); i < end; i++)
                    {
                        hsize_t dim_t;
                        if(datasets[i] >= 0)
                        {                           
                           // Check that the buffer is the right size to fit the dataset!
                           if( (data.size() - j)<sizes[i])
                           {
                              // Data has some other unexpected size, error!
                              std::ostringstream errmsg;
                              errmsg << "Error copying parameter "". Buffer overrun while reading dataset from input file " << i << ". (Dataset in file had size "<<dim_t<<", but there was only size "<<data.size()-j<<" left in the buffer; buffer.size()="<<data.size()<<", current pos.="<<j<<")"<<std::endl;
                              printer_error().raise(LOCAL_INFO, errmsg.str());
 
                           }

                           // Get the hyperslab selection (i.e. the dataset minus invalid points padding out the end)
                           std::pair<hid_t,hid_t> selection_ids = select_chunk(datasets[i], 0, sizes[i]);
                           hid_t memspace_id = selection_ids.first;
                           hid_t dspace_id   = selection_ids.second;

                           // Check sizes of what we are about to copy, and the buffer size
                           //hsize_t dim_check = H5Sget_select_npoints(dspace_id);
                           //std::cout << "Copying data of size "<<dim_check<<" into buffer of size "<<data.size()<<" at position "<<j<<" (so "<<data.size()-j<<" slots available. Note; requested "<<sizes[i]<<" slots)"<<std::endl;

                           // Get the data from the hyperslab.
                           herr_t err_read = H5Dread(datasets[i], get_hdf5_data_type<U>::type(), memspace_id, dspace_id, H5P_DEFAULT, (void *)&data[j]);
                  
                           if(err_read<0)
                           {
                              std::ostringstream errmsg;
                              errmsg << "Error copying parameter "". An error was reported during the H5Dread operation. This is probably a bug in the HDF5Printer, please report it."<<std::endl;
                              printer_error().raise(LOCAL_INFO, errmsg.str());
                           }
                  
                           H5Sclose(dspace_id);
                           H5Sclose(memspace_id);
                        }
                        else
                        {
                           // dataset didn't exist for this file, skip it.
                           dim_t = 0;
                        }
                       
                        // Check size consistency
                        if (dim_t >= sizes[i])
                        {
                            // Data had expected size, no problem
                            // NOTE: dim_t can be larger than expected due to possible padding at end of dataset
                            j += sizes[i];
                        }
                        else if(dim_t==0)
                        {
                            // Data was missing, but also probably fine, just skip it
                            j += sizes[i];
                        }
                        else
                        {
                            // Data has some other unexpected size, error!
                            std::ostringstream errmsg;
                            errmsg << "Error copying parameter "".  Dataset in input file " << i << " did not have the expected size" <<std::endl;
                            errmsg << "(sizes["<<i<<"] = "<<sizes[i]<<" was less than dim_t = "<<dim_t<<")";
                            printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                    }

                    if( dataset_out<0 )
                    {
                        std::ostringstream errmsg;
                        errmsg << "Error copying parameter "".  Output dataset file failed to open for some reason. It is possible that the target file or group does not exist. This should not happen so it is a bug, please report it." <<std::endl;
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    H5Dwrite( dataset_out, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                    // just an extra statement to make line numbers more clear
                    // Check dataset size
                    //hid_t space2 = H5Dget_space(dataset_out);
                    //hsize_t dim_t2 = H5Sget_simple_extent_npoints(space2);
                    //H5Sclose(space2);
                    //std::cout << "Copied "<<size_tot<<" into dataset_out (size="<<dim_t2<<") from vector of size "<<data.size()<<std::endl;
                    //std::cout << "exiting copy_hdf5::run" << std::endl;
                }
            };

            struct ra_copy_hdf5
            {
                template <typename U>
                static void run (U, hid_t &dataset_out, hid_t &dataset2_out, std::vector<hid_t> &datasets, std::vector<hid_t> &datasets2, const unsigned long long size, const std::unordered_map<PPIDpair, unsigned long long, PPIDHash, PPIDEqual>& RA_write_hash, const std::vector<std::vector <unsigned long long> > &pointid, const std::vector<std::vector <unsigned long long> > &rank, const std::vector<unsigned long long> &aux_sizes, hid_t &/*old_dataset*/, hid_t &/*old_dataset2*/)
                {
                    std::vector<U> output(size, 0);
                    std::vector<int> valids(size, 0);

                    // Read in the recently-copied primary points. We will replace
                    // entries as-needed with those from the RA datasets.
                    // (TODO: would use much less memory if we just write individual replacements
                    // straight to disk. But that requires some fancy HDF5 selections, this
                    // method is much more straightforward)
                    if (dataset_out >= 0 && dataset2_out >= 0)
                    {
                        hid_t space  = HDF5::getSpace(dataset_out);
                        hid_t space2 = HDF5::getSpace(dataset2_out);
                        hsize_t out_size  = HDF5::getSimpleExtentNpoints(space);
                        hsize_t out_size2 = HDF5::getSimpleExtentNpoints(space2);
                        HDF5::closeSpace(space);
                        HDF5::closeSpace(space2);
                        if(out_size > size or out_size2 > size)
                        {
                           std::ostringstream errmsg;
                           errmsg << "Error copying dataset into buffer for RA replacements! The dataset has a larger size than has been allocated for new data! (out_size="<<out_size<<", out_size2="<<out_size2<<", expected_size="<<size<<")";
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                        // We should be able to read the whole thing in this time,
                        // unlike in the primary point case, because the combined
                        // dataset should have been created with the correct
                        // length, which we check above. So it should not overflow
                        // the buffers we have allocated.
                        H5Dread(dataset_out,  get_hdf5_data_type<U>::type(),   H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&output[0]);
                        H5Dread(dataset2_out, get_hdf5_data_type<int>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&valids[0]);
                    }
                    else
                    {
                        std::ostringstream errmsg;
                        errmsg << "Error copying datasets into buffer for RA replacements! Could not open datasets (were they created properly during 'copy_hdf5' operation?).";
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    } 

                    // Check that all the input given is consistent in length
                    size_t ndsets = datasets.size();
                    #define DSET_SIZE_CHECK(VEC) \
                    if(VEC.size()!=ndsets) \
                    { \
                       std::ostringstream errmsg; \
                       errmsg << STRINGIFY(VEC) << " vector has inconsistent size! ("<<VEC.size()<<", should be "<<ndsets<<"). This is a bug, please report it."; \
                       printer_error().raise(LOCAL_INFO, errmsg.str()); \
                    }
                    DSET_SIZE_CHECK(datasets2)
                    DSET_SIZE_CHECK(aux_sizes)
                    DSET_SIZE_CHECK(pointid)
                    DSET_SIZE_CHECK(rank)
                    #undef DSET_SIZE_CHECK
 
                    // Additional iterators to be iterated in sync with dataset iteration
                    // We are actually only copying over one 'parameter' in this function,
                    // but are looping over matching datasets from the temp files from
                    // each rank. So each iteration goes to the next file, but remains
                    // targeting the same parameter.
                    auto st = aux_sizes.begin();
                    auto pt = pointid.begin(); 
                    auto ra = rank.begin();
                    auto itv = datasets2.begin();
                    for (auto it = datasets.begin(); it != datasets.end(); 
                         ++it, ++itv, ++pt, ++ra, ++st)
                    {
                       if(*it < 0)
                       {
                          // Dataset wasn't opened, probably some RA parameter just happened to not 
                          // exist in a certain temporary file. Skip this dataset. Though check that
                          // Dataset2 also wasn't opened.
                          if(*itv >= 0)
                          {
                              std::ostringstream errmsg;
                              errmsg << "dataset2 iterator ('isvalid') points to an open dataset, while dataset iterator (main dataset) does not. This is inconsistent and indicates either a bug in this combine code, or in the code which generated the datasets, please report it.";
                              printer_error().raise(LOCAL_INFO, errmsg.str());
                          }
                       }
                       else
                       {
                          hid_t space = H5Dget_space(*it);
                          hssize_t dim_t = H5Sget_simple_extent_npoints(space);
                          std::vector<U> data(dim_t);
                          std::vector<bool> valid; // don't need to declare length because the Enter_HDF5 will take care of it 
                          Enter_HDF5<read_hdf5> (*itv, valid);
                          H5Dread(*it, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                          
                          if((unsigned long long)dim_t < *st)
                          {
                              std::ostringstream errmsg;
                              errmsg << "Error copying aux parameter.  Input file smaller than required.";
                              printer_error().raise(LOCAL_INFO, errmsg.str());
                          }

                          for (int i = 0, end = *st; i < end; i++)
                          {
                              if (valid[i])
                              {
                                  // Look up target for write in hash map
                                  std::unordered_map<PPIDpair, unsigned long long, PPIDHash, PPIDEqual>::const_iterator ihash = RA_write_hash.find(PPIDpair((*pt)[i],(*ra)[i]));
                                  if(ihash != RA_write_hash.end())
                                  {
                                      // found hash key, copy data
                                      unsigned long long temp = ihash->second;
                                      if(temp > size)
                                      {
                                          std::ostringstream errmsg;
                                          errmsg << "Error copying random access parameter. The hash entry for "
                                          << "pt number " << (*pt)[i] << " of rank " << (*ra)[i]  
                                          << " targets the point outside the size of the output dataset ("<<temp<<" > "<<size<<")." 
                                          << "This indicates"
                                          << " a bug in the hash generation, please report it."; 
                                          printer_error().raise(LOCAL_INFO, errmsg.str());
                                      }
                                      output[temp] = data[i];
                                      valids[temp] = 1;
                                  }
                                  else
                                  {
                                     std::ostringstream errmsg;
                                     errmsg << "Error copying random access parameter. Could not find "
                                     << "pt number " << (*pt)[i] << " of rank " << (*ra)[i]  
                                     << " in the output dataset (hash entry was not found).";
                                     printer_error().raise(LOCAL_INFO, errmsg.str());
                                  }
                              }
                          }
                       } // end if
                    }
                    
                    H5Dwrite( dataset_out, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&output[0]);
                    H5Dwrite( dataset2_out, get_hdf5_data_type<int>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&valids[0]);
                }
            };

            template <class U, typename... T>
            inline void Enter_HDF5(hid_t dataset, T&... params)
            {
                if(dataset<0)
                {
                   std::ostringstream errmsg;
                   errmsg << "Invalid dataset supplied to Enter_HDF5 routine!";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
                }

                hid_t dtype = H5Dget_type(dataset);
                if(dtype<0)
                {
                   std::ostringstream errmsg;
                   errmsg << "Failed to detect type for dataset provides as argument for Enter_HDF5 routine!";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
                }

                //H5T_class_t cl = H5Tget_class(dtype);
                hid_t type = H5Tget_native_type(dtype, H5T_DIR_DESCEND);
                if(type<0)
                {
                   std::ostringstream errmsg;
                   errmsg << "Failed to detect native type for dataset provides as argument for Enter_HDF5 routine!";
                   printer_error().raise(LOCAL_INFO, errmsg.str());
                }

                if (H5Tequal(type, get_hdf5_data_type<float>::type()))
                {
                    U::run(float(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<double>::type()))
                {
                    U::run(double(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<long double>::type()))
                {
                    U::run(type_ret<long double>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<char>::type()))
                {
                    U::run(char(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<short>::type()))
                {
                    U::run(short(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<int>::type()))
                {
                    U::run(int(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<long>::type()))
                {
                    U::run(long(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<long long>::type()))
                {
                    U::run(type_ret<long long>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<unsigned char>::type()))
                {
                    U::run(type_ret<unsigned char>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<unsigned short>::type()))
                {
                    U::run(type_ret<unsigned short>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<unsigned int>::type()))
                {
                    U::run(type_ret<unsigned int>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<unsigned long>::type()))
                {
                    U::run(type_ret<unsigned long>(), dataset, params...);
                }
                else if (H5Tequal(type, get_hdf5_data_type<unsigned long long>::type()))
                {
                    U::run(type_ret<unsigned long long>(), dataset, params...);
                }
                else
                {
                    std::ostringstream errmsg;
                    errmsg << "Could not deduce input hdf5 parameter type.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                
                H5Tclose(dtype);
            }

            class hdf5_stuff
            {
            private:
                std::string group_name;
                std::vector<std::string> param_names, aux_param_names;
                std::unordered_set<std::string> param_set, aux_param_set; // for easier finding
                std::vector<hid_t> files;
                std::vector<hid_t> groups;
                std::vector<hid_t> aux_groups;
                std::vector<unsigned long long> cum_sizes;
                std::vector<unsigned long long> sizes;
                unsigned long long size_tot;
                std::string root_file_name;
                unsigned long long pt_min;
                
            public:
                hdf5_stuff(const std::string &file_name, const std::string &group_name, int num);
                ~hdf5_stuff(); // close files on destruction                
                void Enter_Aux_Paramters(const std::string &file, bool resume = false);
            };

            inline void combine_hdf5_files(const std::string file_output, const std::string &file, const std::string &group, int num, bool resume)
            {
                hdf5_stuff stuff(file, group, num);
                
                stuff.Enter_Aux_Paramters(file_output, resume);
            }
  
            // Helper function to compute target point hash for RA combination
            std::unordered_map<PPIDpair, unsigned long long, PPIDHash, PPIDEqual> get_RA_write_hash(hid_t, std::unordered_set<PPIDpair,PPIDHash,PPIDEqual>&);

        }
    }
}

#endif

