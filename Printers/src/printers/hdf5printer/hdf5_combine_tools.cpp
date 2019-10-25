//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Greg's code for combining HDF5 output of
///  multiple MPI processes. Replaces the old
///  Python script
///
///  Ben: I have updated this to use my HDF5
///  wrappers (due to their error checking
///  functionality).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date ???
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2017 Jan
///
///  *********************************************

#include "gambit/Printers/printers/hdf5printer/hdf5_combine_tools.hpp"
#include "gambit/Printers/printers/hdf5printer/hdf5tools.hpp"
#include "gambit/Printers/printers/hdf5printer/DataSetInterfaceScalar.hpp"
#include "gambit/Utils/util_functions.hpp"

// flag to trigger debug output
//#define COMBINE_DEBUG

namespace Gambit
{
    namespace Printers
    {
        namespace HDF5
        {

            inline hsize_t getGroupNum(hid_t group_id)
            {
                H5G_info_t group_info;
                H5Gget_info(group_id, &group_info);
                return group_info.nlinks;
            }

            inline hid_t getType(hid_t dataset)
            {
                hid_t dtype = H5Dget_type(dataset);
                hid_t ret = H5Tget_native_type(dtype, H5T_DIR_DESCEND);
                H5Tclose(dtype);
                return ret;
            }

            // Get name of ith temp file
            std::string hdf5_stuff::get_fname(const size_t i)
            {
                std::stringstream ss;
                if(custom_mode)
                {
                    ss << file_names.at(i);
                }
                else
                {
                    ss << root_file_name << "_temp_" << i;
                }
                return ss.str();
            }

            // Function to discover names of datasets within a HDF5 group
            std::vector<std::string> get_dset_names(hid_t group_id)
            {
               std::vector<std::string> outnames;
               H5G_info_t group_info;
               H5Gget_info(group_id, &group_info );
               hsize_t nlinks = group_info.nlinks; // Number of objects in the group
               for(hsize_t i=0; i<nlinks; i++)
               {
                  int otype = H5Gget_objtype_by_idx(group_id, i);
                  switch (otype)
                  {
                      case H5G_DATASET:
                      {
                          char name_buffer[1000];
                          H5Gget_objname_by_idx(group_id, i, name_buffer, (size_t)1000);
                          std::string strname(name_buffer);
                          // std::cout << "Found "<<strname<<std::endl;
                          if (strname.find("_isvalid") == std::string::npos && strname != "RA_pointID" && strname != "RA_MPIrank")
                              outnames.push_back(strname);
                          break;
                      }
                      default:
                          break;
                  }
               }
               return outnames;
            }


            inline herr_t op_func (hid_t loc_id, const char *name_in, const H5L_info_t *,
                    void *operator_data)
            {
                //herr_t          status;
                herr_t          return_val = 0;
                H5O_info_t      infobuf;
                std::vector<std::string> &od = *static_cast<std::vector<std::string> *> (operator_data);
                std::string name(name_in);

                //status = H5Oget_info_by_name (loc_id, name.c_str(), &infobuf, H5P_DEFAULT);
                H5Oget_info_by_name (loc_id, name.c_str(), &infobuf, H5P_DEFAULT);

                switch (infobuf.type)
                {
                    case H5O_TYPE_GROUP:
                    {
                        //printf ("Group: %s {\n", name);
                        //od.push_back(name);
                        break;

                    }
                    case H5O_TYPE_DATASET:
                    {
                        //printf ("Dataset: %s\n", name);
                        std::string str(name);
                        if (name.find("_isvalid") == std::string::npos)
                            od.push_back(std::string(name));
                        break;
                    }
                    case H5O_TYPE_NAMED_DATATYPE:
                        //printf ("Datatype: %s\n", name);
                        break;
                    default:
                        break;
                        //printf ( "Unknown: %s\n", name);
                }

                return return_val;
            }

            inline herr_t op_func_aux (hid_t loc_id, const char *name_in, const H5L_info_t *,
                    void *operator_data)
            {
                //herr_t          status;
                herr_t          return_val = 0;
                H5O_info_t      infobuf;
                std::vector<std::string> &od = *static_cast<std::vector<std::string> *> (operator_data);
                std::string name(name_in);

                //status = H5Oget_info_by_name (loc_id, name.c_str(), &infobuf, H5P_DEFAULT);
                H5Oget_info_by_name (loc_id, name.c_str(), &infobuf, H5P_DEFAULT);

                switch (infobuf.type)
                {
                    case H5O_TYPE_GROUP:
                    {
                        //printf ("Group: %s {\n", name);
                        //od.push_back(name);
                        break;

                    }
                    case H5O_TYPE_DATASET:
                    {
                        //printf ("Dataset: %s\n", name);
                        std::string str(name);
                        if (name.find("_isvalid") == std::string::npos && name != "RA_pointID" && name != "RA_MPIrank")
                            od.push_back(std::string(name));
                        break;
                    }
                    case H5O_TYPE_NAMED_DATATYPE:
                        //printf ("Datatype: %s\n", name);
                        break;
                    default:
                        break;
                        //printf ( "Unknown: %s\n", name);
                }

                return return_val;
            }

            inline void setup_hdf5_points(hid_t new_group, hid_t type, hid_t type2, unsigned long long size_tot, const std::string &name)
            {
                #ifdef COMBINE_DEBUG
                std::cerr << "  Creating dataset '"<<name<<"'" << std::endl;
                #endif

                hsize_t dimsf[1];
                dimsf[0] = size_tot;
                hid_t dataspace = H5Screate_simple(1, dimsf, NULL);
                if(dataspace < 0)
                {
                  std::ostringstream errmsg;
                  errmsg<<"Failed to set up HDF5 points for copying. H5Screate_simple failed for dataset ("<<name<<").";
                  printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                hid_t dataset_out = H5Dcreate2(new_group, name.c_str(), type, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                if(dataset_out < 0)
                {
                  std::ostringstream errmsg;
                  errmsg<<"Failed to set up HDF5 points for copying. H5Dcreate2 failed for dataset ("<<name<<").";
                  printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                hid_t dataspace2 = H5Screate_simple(1, dimsf, NULL);
                if(dataspace2 < 0)
                {
                  std::ostringstream errmsg;
                  errmsg<<"Failed to set up HDF5 points for copying. H5Screate_simple failed for dataset ("<<name<<"_isvalid).";
                  printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                hid_t dataset2_out = H5Dcreate2(new_group, (name + "_isvalid").c_str(), type2, dataspace2, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                if(dataset2_out < 0)
                {
                  std::ostringstream errmsg;
                  errmsg<<"Failed to set up HDF5 points for copying. H5Dcreate2 failed for dataset ("<<name<<"_isvalid).";
                  printer_error().raise(LOCAL_INFO, errmsg.str());
                }

                // We are just going to close the newly created datasets, and reopen them as needed.
                HDF5::closeSpace(dataspace);
                HDF5::closeSpace(dataspace2);
                HDF5::closeDataset(dataset_out);
                HDF5::closeDataset(dataset2_out);
            }

            inline std::vector<std::string> getGroups(std::string groups)
            {
                std::string::size_type pos = groups.find_first_of("/");
                while (pos != std::string::npos)
                {
                        groups[pos] = ' ';
                        pos = groups.find_first_of("/", pos + 1);
                }

                std::stringstream ss;
                ss << groups;
                std::vector<std::string> ret;
                std::string temp;
                while (ss >> temp) ret.push_back(temp);

                return ret;
            }

            hdf5_stuff::hdf5_stuff(const std::string &file_name, const std::string &output_file, const std::string &group_name, const size_t num, const bool cleanup, const bool skip, const std::vector<std::string>& file_names_in)
              : group_name(group_name)
              , cum_sizes(num, 0)
              , sizes(num, 0)
              , size_tot(0)
              , root_file_name(file_name)
              , do_cleanup(cleanup)
              , skip_unreadable(skip)
              , files(num,-1)
              , groups(num,-1)
              , aux_groups(num,-1)
              , file_names(file_names_in)
              , custom_mode(file_names.size()>0) // Running in mode which allows 'custom' filenames (for combining output from multiple runs)

           {
                if(custom_mode)
                {
                    if(num!=file_names.size())
                    {
                        std::ostringstream errmsg;
                        errmsg << "  Number of files to be combined (num="<<num<<") does not match length of file list supplied (file_names.size()="<<file_names.size()<<"). These should be the same!"<<std::endl;
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    if(num<2)
                    {
                        std::ostringstream errmsg;
                        errmsg << "  Number of files to be combined (num="<<num<<") is less than two! Therefore there is no combining to be done!"<<std::endl;
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    std::cout << "  Running combination routines in 'custom' mode. Primary datasets from all specified files (in the specified group) will be concatenated. Auxilliary (\"random access\") datasets will be IGNORED! If you need auxilliary datasets to be merged into the primary datasets then please merge them in 'normal' mode." << std::endl;
                    // TODO: It would actually be good to write out an extra dataset which records which points come from which files. Could just be an int, and could write out a txt file which gives the mapping from indices to input files. This is too much work for now though.
                }

                // Check which files are readable (lets us tell the user all at once if there is a bad batch)
                bool badfiles = false;
                std::vector<std::size_t> unreadable;
                std::cout << "  Checking readability of temp files...             "<<std::endl;
                for (size_t i = 0; i < num; i++)
                {
                    // Simple Progress monitor
                    std::string fname = get_fname(i);
                    if(not HDF5::checkFileReadable(fname))
                    {
                       badfiles = true;
                       unreadable.push_back(i);
                    }
                }
                if(badfiles)
                {
                    std::cerr << "  WARNING: Unreadable temporary HDF5 files detected! Indices were "<<unreadable<<std::endl;

                    if(not skip_unreadable and badfiles)
                    {
                        std::ostringstream errmsg;
                        errmsg << "  Unreadable temp files detected! Please set -f flag if you want to ignore them."<<std::endl;
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                }

                // Check readability of old combined file, if one is present
                if(Utils::file_exists(output_file))
                {
                   if(not HDF5::checkFileReadable(output_file))
                   {
                       std::ostringstream errmsg;
                       errmsg << "Error combining HDF5 temporary data! A previous combined output file was found ("<<output_file<<"), but it could not be successfully opened. It may be corrupted due to a bad shutdown. You could try deleting/moving the old combined data file and attempting the combination again, though of course the old combined data will be lost." << std::endl;
                       printer_error().raise(LOCAL_INFO, errmsg.str());
                   }
                }

                // Loop over the temporary files from each rank and perform some setup computations.
                for (size_t i = 0; i < num; i++)
                {
                    // Simple Progress monitor
                    std::cout << "  Scanning temp file "<<i<<" for datasets...             \r"<<std::flush;

                    std::string fname = get_fname(i);
                    hid_t file_id, group_id, aux_group_id;
                    hssize_t size = 0; // Length of datasets in this file (to be measured)
                    if(HDF5::checkFileReadable(fname))
                    {
                        file_id = HDF5::openFile(fname);
                        files[i] = file_id;
                        if(custom_mode) aux_group_id = -1; // Skip any aux stuff in custom mode.
                    }
                    else
                    {
                        //std::cout << "  Could not open file "<<i<<"                 "<<std::endl;
                        file_id = -1;
                        files[i] = file_id;
                        group_id = -1;
                        aux_group_id = -1;
                    }

                    if(file_id<0 and not skip)
                    {
                        // Can't read file, it is missing or corrupted, and not allowed to skip it, so error
                        std::ostringstream errmsg;
                        errmsg << "Error combining temporary HDF5 output! Failed to open expected temporary file '"<<fname<<"'.";
                        printer_error().raise(LOCAL_INFO, errmsg.str());
                    }


                    if(file_id >= 0 )
                    {
                        group_id = HDF5::openGroup(file_id, group_name, true); // final argument prevents group from being created

                        // Extract dataset names from the group
                        //std::vector<std::string> names;
                        //H5Literate (group_id, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, (void *) &names);

                        std::vector<std::string> names = get_dset_names(group_id);

                        // No special case needed
                        //if (i == 0)
                        //{
                        //    param_names = names;
                        //    param_set = std::unordered_set<std::string>(names.begin(), names.end());
                        //}
                        //else
                        //{
                            for (auto it = names.begin(), end = names.end(); it != end; ++it)
                            {
                                if (param_set.find(*it) == param_set.end())
                                {
                                    // New parameter name found; add it to the list to be processed.
                                    param_names.push_back(*it);
                                    param_set.insert(*it);
                                }
                            }
                        //}

                        if(not custom_mode)
                        {
                            // Get RA dataset names
                            aux_group_id = HDF5::openGroup(file_id, group_name+"/RA", true);
                            //std::vector<std::string> aux_names;
                            //H5Literate (aux_group_id, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func_aux, (void *) &aux_names);

                            std::vector<std::string> aux_names = get_dset_names(aux_group_id);

                            // Don't need this special case I think
                            //if (not found_valid_file) // These are the first of these names we have found
                            //{
                            //    aux_param_names = aux_names;
                            //    aux_param_set = std::unordered_set<std::string>(aux_names.begin(), aux_names.end());
                            //}
                            //else
                            //{
                                for (auto it = aux_names.begin(), end = aux_names.end(); it != end; ++it)
                                {
                                    if (aux_param_set.find(*it) == aux_param_set.end())
                                    {
                                        // New aux parameter name found; add it to the list to be processed.
                                        aux_param_names.push_back(*it);
                                        aux_param_set.insert(*it);
                                    }
                                }
                            //}
                        }

                        HDF5::errorsOff();
                        hid_t dataset  = HDF5::openDataset(group_id, "pointID", true); // Allow failure to open
                        hid_t dataset2 = HDF5::openDataset(group_id, "pointID_isvalid", true);
                        HDF5::errorsOn();
                        if(dataset<0 and dataset2<0)
                        {
                           // Probably the sync group is empty for this file, just skip it
                           size = 0;
                           // Just update? No reason to do only on last file I think
                           //if (i == num - 1) // Do we need this here?
                           //{
                               size_tot_l = size_tot + size; // Last?
                           //}
                        }
                        else if(dataset<0 or dataset2<0)
                        {
                           // Either primary or isvalid dataset missing (but not both). Error!
                           std::ostringstream errmsg;
                           errmsg << "Error combining temporary HDF5 output! One of the temporary files is missing either the 'pointID' or 'pointID_isvalid' dataset in the primary group (but not both, so the group is not empty!)";
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                        }
                        else
                        {
                           // Everything fine, measure the dataset sizes
                           hid_t dataspace = H5Dget_space(dataset);
                           hid_t dataspace2 = H5Dget_space(dataset2);
                           size           = H5Sget_simple_extent_npoints(dataspace); // Use variable declared outside the if block
                           hssize_t size2 = H5Sget_simple_extent_npoints(dataspace2);

                           std::vector<bool> valids;
                           Enter_HDF5<read_hdf5>(dataset2, valids);

                           // Don't seem to need this for anything?
                           //if (i == 0)
                           //{
                           //    std::vector<unsigned long long> pt_id;
                           //    Enter_HDF5<read_hdf5>(dataset2, pt_id);
                           //    pt_min = pt_id[0];
                           //}

                           if (size != size2)
                           {
                               std::ostringstream errmsg;
                               errmsg << "pointID and pointID_isvalid are not the same size.";
                               printer_error().raise(LOCAL_INFO, errmsg.str());
                           }

                           // Just update? No reason to do only on last file I think
                           //if (i == num - 1)
                           //{
                               size_tot_l = size_tot + size; // Last?
                           //}

                           for (auto it = valids.end()-1; size > 0; --it)
                           {
                               if (*it)
                                   break;
                               else
                                   --size;
                           }

                           HDF5::closeSpace(dataspace);
                           HDF5::closeSpace(dataspace2);
                           HDF5::closeDataset(dataset);
                           HDF5::closeDataset(dataset2);
                        }
                    }

                    for (int j = i+1, end = cum_sizes.size(); j < end; j++)
                    {
                        cum_sizes[j] += size;
                    }
                    sizes[i] = size;
                    size_tot += size;

                    //std::cout <<"size_tot="<<size_tot<<", (new contribution from file "<<i<<" is "<<size<<", file_id was "<<file_id<<")"<<std::endl;

                    // Record whether files/groups could be opened
                    files[i] = file_id;
                    groups[i] = group_id;
                    aux_groups[i] = aux_group_id;

                    // Close groups and tmp file
                    if(group_id>-1)     HDF5::closeGroup(group_id);
                    if(aux_group_id>-1) HDF5::closeGroup(aux_group_id);
                    if(file_id>-1)      HDF5::closeFile(file_id);
                }
                std::cout << "  Finished scanning temp files               "<<std::endl;
            }

            hdf5_stuff::~hdf5_stuff()
            {
                // Just in case they somehow weren't closed earlier
                // Hmm id doesn't change when they are closed so this doesn't work...
                //for(std::vector<hid_t>::iterator it=files.begin(); it!=files.end(); ++it)
                //{
                //   if(*it>-1) HDF5::closeFile(*it);
                //}
            }

            void hdf5_stuff::Enter_Aux_Parameters(const std::string &file, bool resume)
            {
                std::vector<std::vector<unsigned long long>> ranks, ptids;
                std::vector<unsigned long long> aux_sizes;

                hid_t old_file = -1;
                hid_t old_group = -1;
                //std::cout << "resume? " << resume <<std::endl;
                if (resume)
                {
                    // Check if 'file' exists?
                    if(Utils::file_exists(file))
                    {
                       std::string filebak = file + ".temp.bak";
                       std::system(("mv " + file + " " + filebak).c_str());
                       //old_file = H5Fopen((file + ".temp.bak").c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
                       old_file = HDF5::openFile(file + ".temp.bak", false, 'r');
                       if(old_file<0)
                       {
                           std::ostringstream errmsg;
                           errmsg << "Error combining HDF5 temporary data! A previous combined output file was found (now moved to "<<filebak<<"), but it could not be successfully opened. It may be corrupted due to a bad shutdown. You could try deleting/moving the old combined data file and resuming again, though of course the old combined data will be lost." << std::endl;
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                       }

                       old_group = H5Gopen2(old_file, group_name.c_str(), H5P_DEFAULT);
                       if(old_group<0)
                       {
                           std::ostringstream errmsg;
                           errmsg << "Error combining HDF5 temporary data! A previous combined output file was found (now moved to "<<filebak<<"), but the expected dataset location "<<group_name<<" could not be successfully opened. It may be missing or corrupted due to a bad shutdown. You could try deleting/moving the old combined data file and resuming again, though of course the old combined data will be lost." << std::endl;
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                       }

                       hid_t old_dataset = HDF5::openDataset(old_group, "pointID", true); // Allow fail, we will throw a customised error message
                       if(old_dataset<0)
                       {
                           std::ostringstream errmsg;
                           errmsg << "Error combining HDF5 temporary data! A previous combined output file was found (now moved to "<<filebak<<"), but the 'pointID' dataset was not found in the expected location ("<<group_name<<"). It may be missing or corrupted due to a bad shutdown. You could try deleting/moving the old combined data file and resuming again, though of course the old combined data will be lost." << std::endl;
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                       }
                       hid_t space = HDF5::getSpace(old_dataset);
                       hsize_t extra = HDF5::getSimpleExtentNpoints(space);
                       HDF5::closeSpace(space);
                       HDF5::closeDataset(old_dataset);
                       size_tot += extra;

                       // Check for parameters not found in the newer temporary files.
                       // (should not be any aux parameters in here, so don't check for them)
                       //std::vector<std::string> names;
                       //H5Literate (old_group, H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, (void *) &names);

                       std::vector<std::string> names = get_dset_names(old_group);

                       for (auto it = names.begin(), end = names.end(); it != end; ++it)
                       {
                           if (param_set.find(*it) == param_set.end())
                           {
                               // New parameter name found; add it to the list to be processed.
                               param_names.push_back(*it);
                               param_set.insert(*it);
                           }
                       }
                    }
                    else
                    {
                       // This is ok; on first resume no previous combined output exists.
                       old_file = -1;
                       old_group = -1;
                    }
                }

                if(size_tot==0 and aux_param_names.size()==0)
                {
                    // If size_tot==0 then there are no primary sync datapoints in any of the temp files (or previous combined output)
                    // If there are also no auxilliary datapoints found, then there is nothing to combine! Raise an error, because
                    // this is a weird situation, and the run would effectively be starting again anyway.
                    // TODO: Keep this? Someone could restart a run from old scanner data, but just have deleted all the old
                    // printer output. Not sure if we want to allow this or not.
                    std::ostringstream errmsg;
                    errmsg << "Error combining HDF5 temporary data! No previous combined output exists (this may be the first resume attempt), but there were also no primary sync datasets found in the temporary output. This means that if some RA data also exists then there are no points available to write it into! Something has therefore gone wrong during either printing or combining stages.";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                else if(size_tot==0 and aux_param_names.size()!=0)
                {
                    // Ok now size_tot==0 AND there are auxillary datapoints to be combined. Currently we require primary
                    // datapoints to exist in order to write auxilliary data to them.
                    std::ostringstream errmsg;
                    errmsg << "Error combining HDF5 temporary data! No model points in primary (synchronised) datasets were found in the existing temporary files, however auxilliary datasets WERE found. Currently auxilliary datasets cannot be 'combined' with nothing, i.e. they must have a corresponding model point in a 'primary' dataset to which they should be associated. It is possible to loosen this requirement, so if you have written a scanner or likelihood container which writes only to auxillary datasets then please report this error and request the print system be upgraded. Otherwise this error indicates a bug, please report it." << std::endl;
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                // else everything is cool

                //hid_t new_file = H5Fcreate(file.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
                hid_t new_file = HDF5::openFile(file,false,'w'); // No overwrite allowed, this file shouldn't exist
                if(new_file<0)
                {
                    std::ostringstream errmsg;
                    errmsg << "Failed to create output file '"<<file<<"'!";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }

                hid_t new_group = HDF5::openGroup(new_file, group_name); // Recursively creates required group structure

                if (aux_param_names.size() > 0) for (unsigned long i=0; i<aux_groups.size(); ++i)
                {
                     std::vector<unsigned long long> rank, ptid;

                    // Reopen temp files and reaquire group IDs
                    std::string fname = get_fname(i);
                    hid_t file_id = HDF5::openFile(fname);
                    files[i] = file_id; // keep file ID up to date
                    hid_t aux_group_id = HDF5::openGroup(file_id, group_name+"/RA", true); // final argument prevents group from being created
                    hid_t dataset;
                    if(aux_group_id < 0)
                    {
                       dataset = -1; // If group doesn't exist, dataset doesn't either
                    }
                    else
                    {
                       HDF5::errorsOff();
                       dataset = HDF5::openDataset(aux_group_id, "RA_MPIrank", true);
                       HDF5::errorsOn();
                    }

                    if(dataset < 0) // If key dataset doesn't exist, set aux size to zero for this rank
                    {
                       // Need to push back empty entries, because they need to remain synced with the datasets vectors
                       ranks.push_back(rank);
                       ptids.push_back(ptid);
                       aux_sizes.push_back(0);
                    }
                    else
                    {
                       hid_t dataset2 = HDF5::openDataset(aux_group_id, "RA_pointID");
                       hid_t dataset3 = HDF5::openDataset(aux_group_id, "RA_pointID_isvalid");

                       Enter_HDF5<read_hdf5>(dataset, rank);
                       Enter_HDF5<read_hdf5>(dataset2, ptid);
                       // Check that extracted rank/ptid vectors are the same length
                       if(rank.size() != ptid.size())
                       {
                           std::ostringstream errmsg;
                           errmsg << "Extracted RA_MPIrank and RA_pointID are not the same size! ("<<ranks.size()<<"!="<<ptid.size()<<")";
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                       }

                       hid_t dataspace = H5Dget_space(dataset2);
                       hid_t dataspace2 = H5Dget_space(dataset3);
                       hssize_t size = H5Sget_simple_extent_npoints(dataspace);
                       hssize_t size2 = H5Sget_simple_extent_npoints(dataspace2);

                       std::vector<bool> valids;
                       Enter_HDF5<read_hdf5>(dataset3, valids);

                       if (size != size2)
                       {
                           std::ostringstream errmsg;
                           errmsg << "RA_pointID and RA_pointID_isvalid are not the same size.";
                           printer_error().raise(LOCAL_INFO, errmsg.str());
                       }

                       // Make sure to only add the isvalid points!
                       std::vector<unsigned long long> valid_rank;
                       std::vector<unsigned long long> valid_ptid;
                       for(size_t vi=0; vi<valids.size(); vi++)
                       {
                          if(valids[vi])
                          {
                             valid_rank.push_back(rank[vi]);
                             valid_ptid.push_back(ptid[vi]);
                          }
                       }
                       ranks.push_back(valid_rank);
                       ptids.push_back(valid_ptid);

                       for (auto it = valids.end()-1; size > 0; --it)
                       {
                           if (*it)
                               break;
                           else
                               --size;
                       }
                       aux_sizes.push_back(size);

                       HDF5::closeSpace(dataspace);
                       HDF5::closeSpace(dataspace2);
                       HDF5::closeDataset(dataset);
                       HDF5::closeDataset(dataset2);
                       HDF5::closeDataset(dataset3);
                    }
                    // Close resources
                    HDF5::closeGroup(aux_group_id);
                    HDF5::closeFile(file_id);
                }

                // TODO: Ack, getting a "too many open files" error. I guess we need
                // to do this in batches, but that's quite a pain to arrange.
                const size_t BATCH_SIZE = 50;

                // Compute number of batches required
                size_t N_BATCHES = files.size() / BATCH_SIZE;
                size_t remainder = files.size() % BATCH_SIZE;
                if(remainder > 0)
                {
                   N_BATCHES += 1;
                }

                int counter = 1;
                for (auto it = param_names.begin(), end = param_names.end(); it != end; ++it, ++counter)
                {
                    // Simple Progress monitor
                    std::cout << "  Combining primary datasets... "<<int(100*counter/param_names.size())<<"%   (copied "<<counter<<" parameters of "<<param_names.size()<<")        \r"<<std::flush;

                    //std::vector<hid_t> file_ids(files.size(),-1);
                    //std::vector<hid_t> group_ids(files.size(),-1);
                    //std::vector<hid_t> datasets(files.size(),-1);
                    //std::vector<hid_t> datasets2(files.size(),-1);

                    size_t offset = 0; // where to begin writing the next batch in output datasets
                    for(size_t batch_i = 0, end = N_BATCHES; batch_i < end; batch_i++)
                    {
                        size_t pc_offset = 0; // possible extra offset due to previous combined datasets. Only batch 0 will use this.
                        long long valid_dset = -1; // index of a validly opened dataset (-1 if none)
                        size_t THIS_BATCH_SIZE = BATCH_SIZE;
                        std::vector<unsigned long long> batch_sizes(BATCH_SIZE,0);
                         // IDs for this batch
                        std::vector<hid_t> file_ids (THIS_BATCH_SIZE,-1);
                        std::vector<hid_t> group_ids(THIS_BATCH_SIZE,-1);
                        std::vector<hid_t> datasets (THIS_BATCH_SIZE,-1);
                        std::vector<hid_t> datasets2(THIS_BATCH_SIZE,-1);

                        // Collect all the HDF5 ids need to combine this parameter for this batch of files
                        if(remainder>0 and batch_i==N_BATCHES-1) THIS_BATCH_SIZE = remainder; // Last batch is incomplete
                        //std::cout << "   Processing temp files "<<batch_i*BATCH_SIZE<<" to "<<batch_i*BATCH_SIZE+THIS_BATCH_SIZE<<std::endl;
                        //std::cout << "BATCH "<< batch_i << std::endl;
                        for (size_t file_i = 0, end = THIS_BATCH_SIZE; file_i < end; file_i++)
                        {
                            size_t i = file_i + batch_i * BATCH_SIZE;

                            //std::cout << i << " ("<<(files[i]>=0)<<"), ";

                            hid_t file_id  = -1;
                            hid_t group_id = -1;
                            hid_t dataset = -1;
                            hid_t dataset2 = -1;
                            batch_sizes[file_i] = sizes[i]; // Collect pre-measured dataset sizes for this batch

                            // Skip this file if it wasn't successfully opened earlier
                            if(files[i]>=0)
                            {
                                // Reopen files
                                // NOTE: RAM problems largely solved, but footprint could be lowered even more if we only open one file at a time.
                                std::string fname = get_fname(i);
                                if(not HDF5::checkFileReadable(fname))
                                {
                                  std::cout <<"files["<<i<<"] = "<<files[i]<<std::endl;
                                  std::cerr<<"WARNING! "<<fname<<" was not readable! This should have been caught earlier!"<<std::endl;
                                }
                                file_id = HDF5::openFile(fname);
                                files[i] = file_id;
                                group_id = HDF5::openGroup(file_id, group_name, true); // final argument prevents group from being created
                                if(group_id>=0)
                                {
                                   HDF5::errorsOff();
                                   dataset  = HDF5::openDataset(group_id, *it, true); // Allow fail; not all parameters must exist in all temp files
                                   dataset2 = HDF5::openDataset(group_id, *it + "_isvalid", true);
                                   HDF5::errorsOn();
                                }

                                if(dataset>=0)
                                {
                                   if(dataset2>=0) valid_dset = file_i; // Use this one to determine dataset types for this batch (TODO: will be bad if it doesn't match other batches! could make this more robust)
                                   else
                                   {
                                      std::ostringstream errmsg;
                                      errmsg << "Error opening dataset '"<<*it<<"_isvalid' from temp file "<<i<<"! Main dataset was opened, but 'isvalid' dataset failed to open! It may be corrupted.";
                                      printer_error().raise(LOCAL_INFO, errmsg.str());
                                   }
                                }
                            }

                            datasets [file_i] = dataset;
                            datasets2[file_i] = dataset2;
                            file_ids [file_i] = file_id;
                            group_ids[file_i] = group_id;
                        }

                        // Get id for old combined output for this parameter
                        hid_t old_dataset = -1, old_dataset2 = -1;
                        if (resume and batch_i==0) // Only copy old dataset once, during first batch of files
                        {
                            //std::cout << "Opening previous combined dataset for parameter "<<*it<<std::endl;
                            HDF5::errorsOff();
                            old_dataset  = HDF5::openDataset(old_group, *it, true); // Allow fail; may be no previous combined output
                            old_dataset2 = HDF5::openDataset(old_group, *it + "_isvalid", true);
                            HDF5::errorsOn();
                            if(old_dataset<0) std::cout << "Failed to open previous combined dataset for parameter "<<*it<<std::endl; // debugging
                            if(old_dataset>0)
                            {
                                hid_t space = H5Dget_space(old_dataset);
                                hsize_t dim_t = H5Sget_simple_extent_npoints(space);
                                H5Sclose(space);
                                pc_offset = dim_t; // Record size of old combined dataset, needed to get correct offset for next batch
                            }
                        }

                        // With new batching system, could get a batch with no data for this parameter. This is ok,
                        // so we just skip it.
                        // TODO: Could put in a check to make sure that SOME batch copies data.
                        // This should happen though, since the parameter name must have been retrieved from *some*
                        // file or other, so it would just be double-checking that this worked correctly.
                        if(valid_dset>=0 or old_dataset>=0)
                        {
                            hid_t type, type2;
                            if(valid_dset<0)
                            {
                               // Parameter not in any of the new temp files, must only be in the old combined output, get type from there.
                               type  = H5Dget_type(old_dataset);
                               type2 = H5Dget_type(old_dataset2);
                            }
                            else
                            {
                               // Get the type from a validly opened dataset in temp file
                               type  = H5Dget_type(datasets[valid_dset]);
                               type2 = H5Dget_type(datasets2[valid_dset]);
                            }
                            if(type<0 or type2<0)
                            {
                               std::ostringstream errmsg;
                               errmsg << "Failed to detect type for dataset '"<<*it<<"'! The dataset is supposedly valid, so this does not make sense. It must be a bug, please report it. (valid_dset="<<valid_dset<<")";
                               printer_error().raise(LOCAL_INFO, errmsg.str());
                            }

                            if(batch_i==0) // Only want to create the output dataset once!
                            {
                               // Create datasets
                               //std::cout<<"Creating dataset '"<<*it<<"' in file:group "<<file<<":"<<group_name<<std::endl;
                               setup_hdf5_points(new_group, type, type2, size_tot, *it);
                            }

                            // Reopen dataset for writing
                            hid_t dataset_out   = HDF5::openDataset(new_group, *it);
                            hid_t dataset2_out  = HDF5::openDataset(new_group, (*it)+"_isvalid");
                            //std::cout << "Copying parameter "<<*it<<std::endl; // debug

                            // Measure total size of datasets for this batch of files
                            // (not counting previous combined output, which will be copied in batch 0)
                            unsigned long long batch_size_tot = 0;
                            for(auto it = batch_sizes.begin(); it != batch_sizes.end(); ++it)
                            {
                               batch_size_tot += *it;
                            }

                            //Enter_HDF5<copy_hdf5>(dataset_out, datasets, size_tot_l, sizes, old_dataset);
                            //Enter_HDF5<copy_hdf5>(dataset2_out, datasets2, size_tot_l, sizes, old_dataset2);

                            // Do the copy!!!
                            Enter_HDF5<copy_hdf5>(dataset_out, datasets, batch_size_tot, batch_sizes, old_dataset, offset);
                            Enter_HDF5<copy_hdf5>(dataset2_out, datasets2, batch_size_tot, batch_sizes, old_dataset2, offset);

                            // Close resources
                            HDF5::closeDataset(dataset_out);
                            HDF5::closeDataset(dataset2_out);

                            // Move offset so that next batch is written to correct place in output file
                            offset += batch_size_tot + pc_offset;
                        }
                        else
                        {
                            std::cout << "No datasets found for parameter "<<*it<<" in file batch "<<batch_i<<". Moving on to next batch since there seems to be nothing to copy in this one." << std::endl;
                        }

                        // Close files etc. associated with this batch
                        for (size_t file_i = 0, end = file_ids.size(); file_i < end; file_i++)
                        {
                            if(datasets[file_i]>=0)  HDF5::closeDataset(datasets[file_i]);
                            if(datasets2[file_i]>=0) HDF5::closeDataset(datasets2[file_i]);
                            if(group_ids[file_i]>=0) HDF5::closeGroup(group_ids[file_i]);
                            if(file_ids[file_i]>=0)  HDF5::closeFile(file_ids[file_i]);
                        }

                    } // end batch, begin processing next batch of files.
                }
                std::cout << "  Combining primary datasets... Done.                                 "<<std::endl;

                // Debug: early exit to check what primary combined output looks like
                // Flush and close output file
                // H5Fflush(new_file, H5F_SCOPE_GLOBAL);
                // HDF5::closeGroup(new_group);
                // HDF5::closeFile(new_file);
                // exit(0);

                // TODO! I have not yet implemented batch copying for the RA datasets!

                // Ben: NEW. Before copying RA points, we need to figure out a map between them
                // and their targets in the output dataset. That means we need to read through
                // the output dataset and read in all the pointID/MPI pairs.
                // We only need to do this once and create a big hash table to use while copying.
                // It would be better to do all the copying in chunks, and then we would also
                // only need chunks of this hash table at a time, but Greg didn't write this
                // code with chunked writing in mind. TODO: Should modify the code to do this.

                // We already know all the RA rank/ptID pairs, so just need to scan the output
                // datasets for the matching pairs, and record their indices.

                // Start with a list of ID pairs to be matched
                if(not custom_mode)
                {  // ranks and pointIDs not guaranteed to be unique in custom mode! RA datasets to be ignored, should be done prior to custom combining.
                   std::unordered_set<PPIDpair,PPIDHash,PPIDEqual> left_to_match;
                   for(std::size_t i=0; i<ranks.size(); ++i)
                   {
                      for(std::size_t j=0; j<ranks[i].size(); ++j)
                      {
                         //if(ranks[i][j]==0 and ptids[i][j]==0)
                         //{
                         //   std::cout<<"Added r="<<ranks[i][j]<<", p="<<ptids[i][j]<<" to hash search requests"<<std::endl;
                         //}
                         left_to_match.insert(PPIDpair(ptids[i][j],ranks[i][j]));
                      }
                   }

                   if(left_to_match.size()>0)
                   {
                      std::unordered_map<PPIDpair, unsigned long long, PPIDHash,PPIDEqual> RA_write_hash(get_RA_write_hash(new_group, left_to_match));

                      /// Now copy the RA datasets
                      counter = 1; //reset counter
                      for (auto it = aux_param_names.begin(), end = aux_param_names.end(); it != end; ++it, ++counter)
                      {
                          std::cout << "  Combining auxilliary datasets... "<<int(100*counter/aux_param_names.size())<<"%    (merged "<<counter<<" parameters of "<<aux_param_names.size()<<")         \r"<<std::flush;
                          std::vector<hid_t> file_ids, group_ids, datasets, datasets2;
                          int valid_dset  = -1; // index of a validly opened dataset (-1 if none)

                          #ifdef COMBINE_DEBUG
                          std::cerr << "  Preparing to copy dataset '"<<*it<<"'" << std::endl;
                          #endif

                          for (int i = 0, end = aux_groups.size(); i < end; i++)
                          {
                              hid_t file_id  = -1;
                              hid_t group_id = -1;
                              hid_t dataset = -1;
                              hid_t dataset2 = -1;

                              // Skip this file if it wasn't successfully opened earlier
                              if(files[i]>-1)
                              {
                                  // Reopen files
                                  std::string fname = get_fname(i);
                                  file_id = HDF5::openFile(fname);
                                  files[i] = file_id;
                                  group_id = HDF5::openGroup(file_id, group_name+"/RA", true); // final argument prevents group from being created

                                  // Dataset may not exist, and thus fail to open. We will check its status
                                  // later on and ignore it where needed.
                                  if(group_id>=0)
                                  {
                                     HDF5::errorsOff();
                                     dataset  = HDF5::openDataset(group_id, *it, true); // Allow fail; not all parameters must exist in all temp files
                                     dataset2 = HDF5::openDataset(group_id, *it + "_isvalid", true);
                                     HDF5::errorsOn();
                                  }

                                  if(dataset>=0)
                                  {
                                     if(dataset2>=0) valid_dset = i;
                                     else
                                     {
                                        std::ostringstream errmsg;
                                        errmsg << "Error opening dataset '"<<*it<<"_isvalid' from temp file "<<i<<"! Main dataset was opened, but 'isvalid' dataset failed to open! It may be corrupted.";
                                        printer_error().raise(LOCAL_INFO, errmsg.str());
                                     }
                                  }
                              }
                              datasets.push_back(dataset);
                              datasets2.push_back(dataset2);
                              file_ids.push_back(file_id);
                              group_ids.push_back(group_id);
                          }

                          hid_t old_dataset = -1, old_dataset2 = -1;
                          // Actually, I think there is now no need to copy the old data here. It should
                          // already be copied as part of the primary dataset copying.
                          // if (resume)
                          // {
                          //     // Dataset may not exist, and thus fail to open. We will check its status
                          //     // later on and ignore it where needed.
                          //     HDF5::errorsOff();
                          //     old_dataset  = HDF5::openDataset(old_group, *it, true);
                          //     old_dataset2 = HDF5::openDataset(old_group, *it + "_isvalid", true);
                          //     HDF5::errorsOn();
                          // }

                          // If the aux parameter was not also copied as a primary parameter then we need to create a new
                          // dataset for it here. Otherwise one should already exist.
                          if(param_set.find(*it) == param_set.end())
                          {
                             #ifdef COMBINE_DEBUG
                             std::cerr << "  No output dataset for '"<<*it<<"' found amongst those created during copying of primary parameters, preparing to create it." << std::endl;
                             #endif

                             hid_t type=-1, type2=-1;
                             if(valid_dset<0)
                             {
                                // No valid dset open, but we are supposed to copy something? Error.
                                std::ostringstream errmsg;
                                errmsg << "Error copying RA points for dataset '"<<*it<<"'. No valid datasets could be opened, though they were detected in the temp files. They may be corrupted.";
                                printer_error().raise(LOCAL_INFO, errmsg.str());
                             }
                             else
                             {
                                // Get the type from a validly opened dataset in temp file
                                type  = H5Dget_type(datasets[valid_dset]);
                                type2 = H5Dget_type(datasets2[valid_dset]);
                                if(type<0 or type2<0)
                                {
                                   std::ostringstream errmsg;
                                   errmsg << "Failed to detect type for RA dataset '"<<*it<<"'! The dataset is supposedly valid, so this does not make sense. It must be a bug, please report it.";
                                   printer_error().raise(LOCAL_INFO, errmsg.str());
                                }
                             }
                             // Create new dataset
                             setup_hdf5_points(new_group, type, type2, size_tot, *it);
                          }
                          // Reopen output datasets for copying
                          hid_t dataset_out  = HDF5::openDataset(new_group, *it);
                          hid_t dataset2_out = HDF5::openDataset(new_group, (*it)+"_isvalid");
                          Enter_HDF5<ra_copy_hdf5>(dataset_out, dataset2_out, datasets, datasets2, size_tot, RA_write_hash, ptids, ranks, aux_sizes, old_dataset, old_dataset2);

                          // Close resources
                          for (int i = 0, end = datasets.size(); i < end; i++)
                          {
                              // Some datasets may never have been opened, so check this before trying to close them.
                              if(datasets[i]>=0)  HDF5::closeDataset(datasets[i]);
                              if(datasets2[i]>=0) HDF5::closeDataset(datasets2[i]);
                              if(group_ids[i]>=0) HDF5::closeGroup(group_ids[i]);
                              if(file_ids[i]>=0)  HDF5::closeFile(file_ids[i]);
                          }
                      }
                      std::cout << "  Combining auxilliary datasets... Done.                 "<<std::endl;
                   }
                   else
                   {
                      std::cout << "  Combining auxilliary datasets... None found, skipping. "<<std::endl;
                   }
                }

                // Close the old combined file
                if(old_group>=0) HDF5::closeGroup(old_group);
                if(old_file>=0)  HDF5::closeFile(old_file);

                // Flush and close output file
                H5Fflush(new_file, H5F_SCOPE_GLOBAL);
                HDF5::closeGroup(new_group);
                HDF5::closeFile(new_file);

                if (do_cleanup and not custom_mode) // Cleanup disabled for custom mode. This is only for "routine" combination during scan resuming.
                {
                    if (resume)
                    {
                        std::system(("rm -f " + file + ".temp.bak").c_str());
                    }

                    for (int i = 0, end = files.size(); i < end; i++)
                    {
                        std::stringstream ss;
                        ss << i;
                        std::system(("rm -f " + root_file_name + "_temp_" + ss.str()).c_str());
                    }
                }
            }

            /// Helper function to create output hash map for RA points
            /// note: left_to_match points will be erased as we go, and are passed by reference, so will be erased in calling context also.
            std::unordered_map<PPIDpair, unsigned long long, PPIDHash,PPIDEqual> get_RA_write_hash(hid_t group_id, std::unordered_set<PPIDpair,PPIDHash,PPIDEqual>& left_to_match)
            {
               std::unordered_map<PPIDpair, unsigned long long, PPIDHash,PPIDEqual> output_hash;

               // Chunking variables
               static const std::size_t CHUNKLENGTH = 10000; // Should be a reasonable value

               // Interfaces for the datasets
               // Make sure the types used here don't get out of sync with the types used to write the original datasets
               // We open the datasets in "resume" mode to access existing dataset, and make "const" to disable writing of new data. i.e. "Read-only" mode.
               // TODO: this can probably be streamlined once I write the HDF5 reader, can consolidate some reading routines.
               const DataSetInterfaceScalar<unsigned long, CHUNKLENGTH> pointIDs(group_id, "pointID", true,'r');
               const DataSetInterfaceScalar<int, CHUNKLENGTH> pointIDs_isvalid  (group_id, "pointID_isvalid", true,'r');
               const DataSetInterfaceScalar<int, CHUNKLENGTH> mpiranks          (group_id, "MPIrank", true,'r');
               const DataSetInterfaceScalar<int, CHUNKLENGTH> mpiranks_isvalid  (group_id, "MPIrank_isvalid", true,'r');

               // Error check lengths. This should already have been done for all datasets in the group, but
               // we will double-check these four here.
               const std::size_t dset_length  = pointIDs.dset_length();
               const std::size_t dset_length2 = pointIDs_isvalid.dset_length();
               const std::size_t dset_length3 = mpiranks.dset_length();
               const std::size_t dset_length4 = mpiranks_isvalid.dset_length();
               if( (dset_length  != dset_length2)
                or (dset_length3 != dset_length4)
                or (dset_length  != dset_length3) )
               {
                 std::ostringstream errmsg;
                 errmsg << "Error scanning combined output for RA point locations! Unequal dataset lengths detected in pointID and MPIrank datasets:" <<std::endl;
                 errmsg << "  pointIDs.dset_length()         = " << dset_length << std::endl;
                 errmsg << "  pointIDs_isvalid.dset_length() = " << dset_length2 << std::endl;
                 errmsg << "  mpiranks.dset_length()         = " << dset_length3 << std::endl;
                 errmsg << "  mpiranks_isvalid.dset_length() = " << dset_length4 << std::endl;
                 errmsg << "This indicates either a bug in the HDF5 combine code, please report it.";
                 printer_error().raise(LOCAL_INFO, errmsg.str());
               }

               //std::cout<<"New combined output dataset length: "<<dset_length<<std::endl;

               // Compute number of chunks
               const std::size_t NCHUNKS = dset_length / CHUNKLENGTH; // Number of FULL chunks
               const std::size_t REMAINDER = dset_length - (NCHUNKS*CHUNKLENGTH); // leftover after last full chunk

               std::size_t NCHUNKIT; // Number of chunk iterations to perform
               if(REMAINDER==0) { NCHUNKIT = NCHUNKS; }
               else             { NCHUNKIT = NCHUNKS+1; } // Need an extra iteration to deal with incomplete chunk

               //std::cout<<"Will parse this output in "<<NCHUNKIT<<" chunks of size "<<CHUNKLENGTH<<std::endl;

               // Iterate through dataset in chunks
               for(std::size_t i=0; i<NCHUNKIT; ++i)
               {
                  std::size_t offset = i*CHUNKLENGTH;
                  std::size_t length;
                  if(i==NCHUNKS){ length = REMAINDER; }
                  else          { length = CHUNKLENGTH; }

                  //std::cout<<"  Offset for chunk "<<i<<" is "<<offset<<". Length is "<<length<<std::endl;

                  const std::vector<unsigned long> pID_chunk = pointIDs.get_chunk(offset,length);
                  const std::vector<int> pIDvalid_chunk  = pointIDs_isvalid.get_chunk(offset,length);
                  const std::vector<int> rank_chunk      =         mpiranks.get_chunk(offset,length);
                  const std::vector<int> rankvalid_chunk = mpiranks_isvalid.get_chunk(offset,length);

                  // Check that retrieved lengths make sense
                  if (pID_chunk.size() != CHUNKLENGTH)
                  {
                    if(not (i==NCHUNKS and pID_chunk.size()==REMAINDER) )
                    {
                      std::ostringstream errmsg;
                      errmsg << "Error scanning combined pointID and MPIrank datasets! Size of chunk vector retrieved from pointID dataset ("<<pID_chunk.size()<<") does not match CHUNKLENGTH ("<<CHUNKLENGTH<<"), nor the expected remainder for the last chunk ("<<REMAINDER<<"). This probably indicates a bug in the DataSetInterfaceScalar.get_chunk routine, please report it. Error occurred while reading chunk i="<<i<<std::endl;
                      printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                  }
                  if( (pID_chunk.size() != pIDvalid_chunk.size())
                   or (rank_chunk.size() != rankvalid_chunk.size())
                   or (pID_chunk.size() != rank_chunk.size()) )
                  {
                    std::ostringstream errmsg;
                    errmsg << "Error preparing to combine RA points into output dataset! Unequal chunk lengths retrieved while iterating through in pointID and MPIrank datasets:" <<std::endl;
                    errmsg << "  pID_chunk.size()      = " << pID_chunk.size() << std::endl;
                    errmsg << "  pIDvalid_chunk.size() = " << pIDvalid_chunk.size() << std::endl;
                    errmsg << "  rank_chunk.size()     = " << rank_chunk.size() << std::endl;
                    errmsg << "  rankvalid_chunk.size()= " << rankvalid_chunk.size() << std::endl;
                    errmsg << "  CHUNKLENGTH           = " << CHUNKLENGTH << std::endl;
                    errmsg << "This indicates a bug in the HDF5 combine code, please report it. Error occurred while reading chunk i="<<i<<std::endl;
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                  }

                  // Iterate within the chunk
                  for(std::size_t j=0; j<length; ++j)
                  {
                    //Check validity flags agree
                    if(pIDvalid_chunk[j] != rankvalid_chunk[j])
                    {
                      std::ostringstream errmsg;
                      errmsg << "Error! Incompatible validity flags detected in pointID_isvalid and MPIrank_isvalid datasets at position j="<<j<<" in chunk i="<<i<<"(with CHUNKLENGTH="<<CHUNKLENGTH<<"). Specifically:"<<std::endl;
                      errmsg << "  pIDvalid_chunk[j]  = " << pIDvalid_chunk[j] << std::endl;
                      errmsg << "  rankvalid_chunk[j] = " << rankvalid_chunk[j] << std::endl;
                      errmsg << "This most likely indicates a bug in the HDF5 combine code, please report it.";
                      printer_error().raise(LOCAL_INFO, errmsg.str());
                    }
                    // @{ Debugging: see what points exist in the output dataset (for rank 127)
                    //if(rank_chunk[j]==127)
                    //{
                    //    std::cout << "  Scanned point "<<pID_chunk[j]<<" (rank "<<rank_chunk[j]<<", valid="<<pIDvalid_chunk[j]<<") in combined output file"<<std::endl;
                    //}
                    // @}

                    // Check for hash match if entry is marked as "valid"
                    if(rankvalid_chunk[j])
                    {
                      // Check if this point is in our list of points to be matched
                      PPIDpair this_point(pID_chunk[j],rank_chunk[j]);
                      std::unordered_set<PPIDpair,PPIDHash,PPIDEqual>::iterator match = left_to_match.find(this_point);
                      if(match != left_to_match.end())
                      {
                         // Found a match! Add its index to the hash.
                         output_hash[*match] = offset + j;
                         // Delete it from the list of points that need to be matched (note, multiple entries in output file not allowed)
                         left_to_match.erase(match);
                      }
                    }
                    // else continue iteration
                  }
               }

               // Check that all the matches were found!
               if( left_to_match.size() > 0 )
               {
                   std::ostringstream errmsg;
                   errmsg << "Error generating hash map for Auxilliary parameter copy! Failed to find matches in primary datasets for all auxilliary data! There were "<<left_to_match.size()<<" unmatched auxilliary points. Unmatched points follow:" << std::endl;
                   for(auto it=left_to_match.begin(); it!=left_to_match.end(); ++it)
                   {
                      errmsg << "  rank: "<<it->rank<<", pointID: "<<it->pointID<< std::endl;
                   }
                   printer_error().raise(LOCAL_INFO, errmsg.str());
               }
               return output_hash;
            }

            std::pair<std::vector<std::string>,std::vector<size_t>> find_temporary_files(const std::string& finalfile)
            {
              size_t max_i = 0;
              return find_temporary_files(finalfile, max_i);
            }

            /// Search for temporary files to be combined
            std::pair<std::vector<std::string>,std::vector<size_t>> find_temporary_files(const std::string& finalfile, size_t& max_i)
            {
              // Autodetect temporary files from previous run.
              std::string output_dir = Utils::dir_name(finalfile);
              std::vector<std::string> files = Utils::ls_dir(output_dir);
              std::string tmp_base(Utils::base_name(finalfile) + "_temp_");
              std::vector<size_t> ranks;
              std::vector<std::string> result;

              //std::cout << "Matching against: " <<tmp_base<<std::endl;
              for(auto it=files.begin(); it!=files.end(); ++it)
              {
                //std::cout << (*it) << std::endl;
                //std::cout << it->substr(0,tmp_base.length()) << std::endl;
                if (it->compare(0, tmp_base.length(), tmp_base) == 0)
                {
                  // Matches format of temporary file! Extract the rank that produced it
                  std::stringstream ss;
                  ss << it->substr(tmp_base.length());
                  if(Utils::isInteger(ss.str())) // Only do this for files where the remainder of the string is just an integer (i.e. not the combined files etc.)
                  {
                    size_t rank;
                    ss >> rank;
                    if(rank>max_i) max_i = rank; // Look for highest rank output
                    //std::cout << "Match! "<< ss.str() << " : " << rank << std::endl;
                    // TODO: check for failed read
                    ranks.push_back(rank);
                    result.push_back(output_dir+"/"+*it);
                  }
                }
              }

              // Check if all temporary files found (i.e. if output from some rank is missing)
              std::vector<size_t> missing;
              for(size_t i=0; i<max_i; ++i)
              {
                if(std::find(ranks.begin(), ranks.end(), i) == ranks.end())
                { missing.push_back(i); }
              }

              // Return the list of missing tmp files, the caller can decide to throw an error if they like
              return std::make_pair(result,missing);
            }

        }
    }
}


