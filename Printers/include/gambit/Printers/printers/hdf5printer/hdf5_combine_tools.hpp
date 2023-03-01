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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 May
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

            struct read_hdf5
            {
                template <typename U, typename T>
                static void run(U, hid_t &dataset, std::vector <T> &vec)
                {
                    hid_t dataspace = H5Dget_space(dataset);
                    hssize_t dim_t = H5Sget_simple_extent_npoints(dataspace);
                    vec.resize(dim_t);
                    H5Dread( dataset, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)vec.data());
                    H5Sclose(dataspace);
                }

                template <typename U>
                static void run(U, hid_t &dataset, std::vector <bool> &vec)
                {
                    hid_t dataspace = H5Dget_space(dataset);
                    hssize_t dim_t = H5Sget_simple_extent_npoints(dataspace);
                    std::vector<U> data(dim_t);
                    H5Dread( dataset, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                    vec = std::vector<bool>(data.begin(), data.end());
                    H5Sclose(dataspace);
                }

                static void run(std::string, hid_t &, std::vector <bool> &)
                { }


            };

            struct copy_hdf5
            {
                template <typename U>
                static void run(U, hid_t &dataset_out, std::vector<hid_t> &datasets, unsigned long long &size_tot, std::vector<unsigned long long> &sizes, hid_t &old_dataset, size_t offset)
                {
                    std::vector<U> data(size_tot);
                    unsigned long long j = 0;
                    
                    if (old_dataset >= 0)
                    {
                        hid_t space = H5Dget_space(old_dataset);
                        hsize_t dim_t = H5Sget_simple_extent_npoints(space);
                        H5Sclose(space);
                        data.resize(dim_t + size_tot);
                        H5Dread(old_dataset, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                        j = dim_t;
                        //std::cout <<"Read "<<dim_t<<" points from old dataset (into position 0)!"<<std::endl;
                        //for(unsigned long long i=0; i<dim_t; i++) // debug
                        //{
                        //   std::cout<<"  "<<data[i]<<std::endl;
                        //}
                    }
                    else
                    {
                        //std::cout << "No old dataset found!" << std::endl;
                    }
                    
                    for (int i = 0, end = datasets.size(); i < end; i++)
                    {
                        hsize_t dim_t;
                        if(datasets[i] >= 0)
                        {
                           // Check that we allocated enough space for this dataset!
                           hid_t space = H5Dget_space(datasets[i]);
                           dim_t = H5Sget_simple_extent_npoints(space);
                           H5Sclose(space);
                           if(j+dim_t > data.size())
                           {
                              if( (data.size() - j) < sizes[i]) // was !=, but I think it is fine so long as there isn't too *little* space. TODO: might be an odds measuring bug though since I think these should indeed be == if everything has happened correctly.
                              {
                                 // This is how much space we expect to have left in the buffer
                                 // at the end. If not, something bad has happened!
                                 std::ostringstream errmsg;
                                 errmsg << "Error copying parameter.  Dataset in input file " << i 
                                     << " was larger than previously measured and doesn't fit in the allocated buffer! " 
                                     << "This is a bug in the combination tools, please report it." <<std::endl;
                                 errmsg << "(j="<<j<<", dim_t="<<dim_t<<", data.size()="<<data.size()<<", sizes["<<i<<"]="<<sizes[i]<<")"<<std::endl;
                                 printer_error().raise(LOCAL_INFO, errmsg.str()); 
                              }
                              // Just some junk buffer points at the end of the last data set.
                              // Need to do a more careful dataset selection to chop these out so
                              // that the data fits in our buffer (and in the space already allocated
                              // in the output file)
                              hid_t memspace_id, dspace_id; 
                              std::pair<hid_t,hid_t> chunk_ids = HDF5::selectChunk(datasets[i], 0, sizes[i]);
                              memspace_id = chunk_ids.first;
                              dspace_id = chunk_ids.second;
   
                              H5Dread(datasets[i], get_hdf5_data_type<U>::type(), memspace_id, dspace_id, H5P_DEFAULT, (void *)&data[j]);                           
                              H5Sclose(memspace_id);
                              H5Sclose(dspace_id);
                              //std::cout <<"Read "<<sizes[i]<<" points from dataset "<<i<<" into position "<<j<<std::endl;
                              //std::ostringstream errmsg;
                              //errmsg << "Error copying parameter.  Dataset in input file " << i 
                              //    << " was larger than previously measured and doesn't fit in the allocated buffer! " 
                              //    << "This is a bug in the combination tools, please report it." <<std::endl;
                              //errmsg << "(j="<<j<<", dim_t="<<dim_t<<", data.size()="<<data.size()<<")"<<std::endl;
                              //printer_error().raise(LOCAL_INFO, errmsg.str()); 
                           }
                           else
                           { 
                              // Read the whole dataset in to buffer (faster than selecting, I should think)
                              H5Dread(datasets[i], get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[j]);                           
                              //std::cout <<"Read "<<dim_t<<" points from dataset "<<i<<" into position "<<j<<std::endl;
                              //for(unsigned long long k=j; k<j+dim_t; k++) // debug
                              //{
                              //   std::cout<<"  "<<data[k]<<std::endl;
                              //}
                            }
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
                            // NOTE: Why can dim_t be larger than expected? Possible padding at end or something?
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
                    // Select dataspace for writing in the output file. Partial write now possible, so we
                    // have to select the hyperslab that we want to write into
                    hid_t memspace_id, dspace_id; 
                    std::pair<hid_t,hid_t> chunk_ids = HDF5::selectChunk(dataset_out, offset, data.size());
                    memspace_id = chunk_ids.first;
                    dspace_id = chunk_ids.second;
                    herr_t err = H5Dwrite( dataset_out, get_hdf5_data_type<U>::type(), memspace_id, dspace_id, H5P_DEFAULT, (void *)&data[0]);
                    if(err<0)
                    {
                        std::ostringstream errmsg;
                        errmsg << "Error copying parameter. HD5write failed." <<std::endl;  
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    //std::cout<<"Wrote "<<data.size()<<" points into output dataset at position "<<offset<<std::endl;
                    H5Sclose(memspace_id);
                    H5Sclose(dspace_id);
 
                    // Was:
                    //H5Dwrite( dataset_out, get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&data[0]);
                }
            };

            struct ra_copy_hdf5
            {
                template <typename U>
                static void run (U, hid_t &dataset_out, hid_t &dataset2_out, std::vector<hid_t> &datasets, std::vector<hid_t> &datasets2, const unsigned long long size, const std::unordered_map<PPIDpair, unsigned long long, PPIDHash, PPIDEqual>& RA_write_hash, const std::vector<std::vector <unsigned long long> > &pointid, const std::vector<std::vector <unsigned long long> > &rank, const std::vector<unsigned long long> &aux_sizes, hid_t &/*old_dataset*/, hid_t &/*old_dataset2*/)
                {
                    std::vector<U> output(size, 0);
                    std::vector<int> valids(size, 0);

                    // Should no longer need the old datasets, they should have already been copied during "copy_hdf5"
                    // if (old_dataset >= 0 && old_dataset2 >= 0)
                    // {
                    //     hid_t space  = HDF5::getSpace(old_dataset);
                    //     hid_t space2 = HDF5::getSpace(old_dataset2);
                    //     hsize_t old_size  = H5Sget_simple_extent_npoints(space);
                    //     hsize_t old_size2 = H5Sget_simple_extent_npoints(space2);
                    //     HDF5::closeSpace(space);
                    //     HDF5::closeSpace(space2);
                    //     if(old_size > size or old_size2 > size)
                    //     {
                    //        std::ostringstream errmsg;
                    //        errmsg << "Error copying old dataset into buffer! The old dataset has a larger size than has been allocated for new data! (old_size="<<old_size<<", old_size2="<<old_size2<<", new_size="<<size<<")";
                    //        printer_error().raise(LOCAL_INFO, errmsg.str());
                    //     }
                    //     H5Dread(old_dataset,  get_hdf5_data_type<U>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&output[0]);
                    //     H5Dread(old_dataset2, get_hdf5_data_type<int>::type(), H5S_ALL, H5S_ALL, H5P_DEFAULT, (void *)&valids[0]);
                    // }

                    // Instead we just need to read in the recently-copied primary points and replace
                    // entries as needed (TODO: would use much less memory if we just write individual replacements
                    // straight to disk)
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
                          std::vector<bool> valid;
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
                else if (H5Tequal(type, get_hdf5_data_type<std::string>::type()))
                {
                    U::run(type_ret<std::string>(), dataset, params...);
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
                std::string metadata_group_name;
                std::vector<std::string> param_names, metadata_names, aux_param_names;
                std::unordered_set<std::string> param_set, metadata_set, aux_param_set; // for easier finding
                std::vector<std::string> metadata_dates;
                std::vector<unsigned long long> cum_sizes;
                std::vector<unsigned long long> sizes;
                std::vector<unsigned long long> metadata_sizes;
                unsigned long long size_tot;
                unsigned long long size_tot_l;
                std::string root_file_name;
                bool do_cleanup; // If true, delete old temporary files after successful combination
                std::string get_fname(const size_t); // get name of ith temp file
                bool skip_unreadable; // If true, ignores temp files that fail to open
                std::vector<hid_t> files;
                std::vector<hid_t> groups;
                std::vector<hid_t> metadata_groups;
                std::vector<hid_t> aux_groups;
                std::vector<std::string> file_names; // Names of temp files to combine
                bool custom_mode; // Running in mode which allows 'custom' filenames (for combining output from multiple runs)

            public:
                hdf5_stuff(const std::string &base_file_name, const std::string &output_file, const std::string &group_name, const std::string &metadata_group_name, const size_t num, const bool cleanup, const bool skip, const std::vector<std::string>& input_files);
                ~hdf5_stuff(); // close files on destruction                
                void Enter_Aux_Parameters(const std::string &output_file, bool resume = false);
            };

            inline void combine_hdf5_files(const std::string output_file, const std::string &base_file_name, const std::string &group, const std::string &metadata_group, const size_t num, const bool resume, const bool cleanup, const bool skip, const std::vector<std::string> input_files = std::vector<std::string>())
            {
                hdf5_stuff stuff(base_file_name, output_file, group, metadata_group, num, cleanup, skip, input_files);
                
                stuff.Enter_Aux_Parameters(output_file, resume);
            }
  
            // Helper function to compute target point hash for RA combination
            std::unordered_map<PPIDpair, unsigned long long, PPIDHash, PPIDEqual> get_RA_write_hash(hid_t, std::unordered_set<PPIDpair,PPIDHash,PPIDEqual>&);

            /// Search for temporary files to be combined
            std::pair<std::vector<std::string>,std::vector<size_t>> find_temporary_files(const std::string& finalfile);
            std::pair<std::vector<std::string>,std::vector<size_t>> find_temporary_files(const std::string& finalfile, size_t& max_i);
  
        }
    }
}

#endif

