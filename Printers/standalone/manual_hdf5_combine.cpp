//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  This is code for a stand-alone binary which
///  performs the end-of-run combination of
///  temporary HDF5 files from a GAMBIT scan.
///
///  It is essentially the same code that GAMBIT
///  runs automatically in the HDF5 printer, just
///  moved into a stand-alone tool so that the
///  combination can be done "manually" if needed.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Mar
///
///  *********************************************

#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <sstream>
#include <utility>
#include <string>
#include <sys/stat.h>
#include <chrono>

// GAMBIT headers
#include "gambit/Printers/printers/hdf5printer/hdf5_combine_tools.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_functions.hpp"

// Annoying other things we need due to mostly unwanted dependencies
#include "gambit/Utils/static_members.hpp"

using namespace Gambit;
using namespace Printers;

void usage()
{
    std::cout << "\nusage: hdf5combine <filename> <group> [options] "
          "\n "
          "\n  filename - Base name of the temporary files to be combined" 
          "\n               e.g. /path/to/my/hdf5file.hdf5 "
          "\n  group    - location inside the HDF5 files which contains the datasets to be combined"
          "\n"
          "\nOptions:"
          "\n   -h/--help             Display this usage information"
          "\n   -f/--force            Attempt combination while ignoring missing temporary files"
          "\n   -c/--cleanup          Delete temporary files after successful combination"
          "\n   -o/--out <path>       Set output folder (default is same folder as temp files)"
          "\n                         (note, this first creates the output in the default place,"
          "\n                         and then just moves it)"
          "\n   -i/--in <file_with_list>"
          "\n                         Uses named files as input instead of automatically inferring"
          "\n                         them from <filename>. Filenames are to be supplied in a single"
          "\n                         ascii file, on separate lines."
          "\n                         In this mode <filename> will only be used for naming the output"
          "\n                         file (Note: WITHOUT the usual addition of '_temp_combined'!!!)."
          "\n                         All files must have the same <group>."
          "\n                         Note: Auxilliary ('RA') datasets will be IGNORED! These should"
          "\n                         be combined during 'normal' combination of results from a single"
          "\n                         run. This 'custom' mode is intended for combining results from"
          "\n                         DIFFERENT runs."
          "\n\n";
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
   // Process command line options
   // Must at least have two arguments.
   if (argc < 3)
   {
      usage();
   }

   // First, the required options (folder and temporary file base name)
   std::string finalfile  = argv[1];
   std::string group      = argv[2];
   std::string outpath;

   const struct option primary_options[] =
   {
     {"force", no_argument, 0, 'f'},
     {"help",  no_argument, 0, 'h'},
     {"cleanup", no_argument, 0 , 'c'},
     {"in", required_argument, 0, 'i'},
     {"out", required_argument, 0, 'o'},
     {0,0,0,0},
   };

   int index;
   int iarg=0;
   std::string filename;
   std::vector<std::string> input_files;
   bool custom_mode = false;
   std::string tmp_comb_file;
   bool error_if_inconsistent = true;
   bool do_cleanup = false;
   bool move_output = false;
   size_t num;
   bool combined_file_exists;

   while(iarg != -1)
   {
     iarg = getopt_long(argc, argv, "fhcoi:", primary_options, &index);
     switch (iarg)
     {
       case 'h':
         // Display usage information and exit
         usage();
         break;
       case 'f':
         // Ignore missing temporary files
         error_if_inconsistent = false;
         break;
       case 'c':
         do_cleanup = true;
         break;
       case 'o':
         outpath = optarg; 
         move_output = true;
         break;
       case 'i':
         {
            std::ifstream file_list(optarg);
            std::string line; 
            while(std::getline(file_list, line))
            {
               input_files.push_back(line);
            }
         }
         custom_mode = true;
         combined_file_exists = false;
         num = input_files.size();
         break;
       case '?':
         // display usage message and quit (also happens on unrecognised options)
         usage();
         break;
     }
   }
 
   // Begining timing of operation
   std::chrono::time_point<std::chrono::system_clock> startT = std::chrono::system_clock::now();

   if(custom_mode)
   {
      // Custom specification of input files
      std::cout <<"  Running combine code in custom filename mode" <<std::endl;
      std::cout <<"  "<<num<<" files to be combined:"<<std::endl;
      for(std::vector<std::string>::iterator it=input_files.begin(); it!=input_files.end(); ++it)
      {
        std::cout << "    " << *it << std::endl;
      }
      if(num<2)
      {
        std::ostringstream errmsg;
        errmsg << "  ERROR! Less than two files parsed from '--in' argument! At least two files are required for combination to do anything!";
        std::cerr << errmsg.str() << std::endl;
        exit(EXIT_FAILURE); 
      }
      HDF5::combine_hdf5_files(finalfile, "", group, num, false, false, true, input_files);
   }
   else
   {
      // Report what we are going to do
      std::cout <<"  Searching for temporary files to combine" <<std::endl;
      std::cout <<"     with base filename: "<<finalfile<<std::endl;

      // Search for the temporary files to be combined
      size_t max_i = 0;
      std::pair<std::vector<std::string>,std::vector<size_t>> out = HDF5::find_temporary_files(finalfile, max_i);
      std::vector<std::string> tmp_files = out.first;
      std::vector<size_t> missing = out.second;

      std::cout <<"  Found "<<tmp_files.size()<<" temporary files to be combined"<<std::endl;
      // Check if all temporary files found (i.e. check if output from some rank is missing)
      if(missing.size()>0)
      {
        std::cout <<"  WARNING! Temporary files missing from the following ranks: "<<missing<<std::endl; 
        if(error_if_inconsistent)
        {
          std::ostringstream errmsg;
          errmsg << "  Could not locate all the expected temporary output files (found "<<tmp_files.size()<<" temporary files, but are missing the files from the ranks reported above)! If you want to attempt the combination anyway, please add the -f flag to the command line invocation.";
          std::cerr << errmsg.str() << std::endl;
          exit(EXIT_FAILURE); 
        }
      }

      // Name of temporary combined file, if one exists
      std::ostringstream name;
      name << finalfile << "_temp_combined";
      tmp_comb_file = name.str();

      combined_file_exists = Utils::file_exists(tmp_comb_file);
      if(combined_file_exists)
      {
         std::cout<<"  Found pre-existing (temporary) combined file"<<std::endl;
      } 
      else 
      {
         std::cout<<"  No pre-existing (temporary) combined file found"<<std::endl;  
      }

      num = tmp_files.size() + missing.size();
      // We don't actually use their names here, Greg's code assumes that they
      // follow a fixed format. Previous all files had to exist in increasing
      // numerical order, however now, if you use the -f flag, it is allowed
      // for some to just be missing. These will just be ignored if they fail
      // to open.
 
      HDF5::combine_hdf5_files(tmp_comb_file, finalfile, group, num, combined_file_exists, do_cleanup, !error_if_inconsistent);
   }

   std::cout<<"  Combination finished successfully!"<<std::endl;
   if(move_output)
   {
      std::string fname(Utils::base_name(tmp_comb_file));
      std::string outname(outpath+"/"+fname);
      std::cout<<"  Moving output from "<<std::endl
               <<"  "<<tmp_comb_file<<std::endl
               <<"  to"<<std::endl
               <<"  "<<outname<<std::endl;
      int status = std::system(("mv " + tmp_comb_file+ " " + outname).c_str());
      if(WEXITSTATUS(status)!=0)
      {
         std::cerr << "  FAILED to move output to requested directory!! It should still be located at"<<std::endl
                   << "    "<<tmp_comb_file<<std::endl;
      }
   }

   // End timing of operation
   std::chrono::time_point<std::chrono::system_clock> endT = std::chrono::system_clock::now();
   std::chrono::duration<double> interval = endT - startT;
   long runtime = std::chrono::duration_cast<std::chrono::seconds>(interval).count(); 
   long mins = runtime / 60;
   long secs = runtime % 60;
   std::cout<<"  Operation took "<<mins<<" minutes and "<<secs<<" seconds."<<std::endl;

   // Finished!
   exit(EXIT_SUCCESS);   
}

