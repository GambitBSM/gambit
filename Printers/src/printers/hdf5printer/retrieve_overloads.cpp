//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 interface reaader class retrieve function
///  overloads.  Add a new overload of the _retrieve
///  function in this file if you want to be able
///  to read a new type for postprocessing.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2017 Jan
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 March
///
///  *********************************************

#include "gambit/Printers/printers/hdf5reader.hpp"
#include "gambit/Printers/printers/hdf5printer.hpp"

namespace Gambit
{
  namespace Printers
  {

     /// @{ Retrieve functions

     /// Templatable retrieve functions
     #define RETRIEVE(TYPE) _retrieve(TYPE& out, const std::string& l, const uint r, const ulong p) \
        { return  _retrieve_template(out,l,0,r,p); }
     bool HDF5Reader::RETRIEVE(int      )
     bool HDF5Reader::RETRIEVE(uint     )
     bool HDF5Reader::RETRIEVE(long     )
     bool HDF5Reader::RETRIEVE(ulong    )
     bool HDF5Reader::RETRIEVE(float    )
     bool HDF5Reader::RETRIEVE(double   )
     #undef RETRIEVE

     #define RETRIEVEFROM(INTYPE,OUTTYPE) _retrieve(INTYPE& out, const std::string& l, const uint r, const ulong p) \
        { \
           OUTTYPE outtmp; \
           bool valid = _retrieve_template(outtmp,l,0,r,p); \
           out = (INTYPE)outtmp; \
           return valid; \
        }
     bool HDF5Reader::RETRIEVEFROM(longlong, long)
     bool HDF5Reader::RETRIEVEFROM(ulonglong, ulong)
     #undef RETRIEVEFROM

     // Bools can't quite use the template function directly, since there
     // are some issues with bools and MPI/HDF5 types. Easier to just convert
     // the bool to an int first (this is how they are printed in the first place anyway).
     bool HDF5Reader::_retrieve(bool& out, const std::string& l, const uint rank, const ulong pID)
     {
       uint tmp_out;
       bool tmp_ret;
       tmp_ret = _retrieve_template(tmp_out,l,0,rank,pID);
       out = tmp_out;
       return tmp_ret;
     }

     bool HDF5Reader::_retrieve(ModelParameters& out, const std::string& modelname, const uint rank, const ulong pointID)
     {
        bool is_valid = true;
        /// Work out all the output labels which correspond to the input modelname
        bool found_at_least_one(false);

        //std::cout << "Searching for ModelParameters of model '"<<modelname<<"'"<<std::endl;
        // Iterate through names in HDF5 group
        for(std::vector<std::string>::const_iterator
            it = all_datasets.begin();
            it!= all_datasets.end(); ++it)
        {
          //std::cout << "Candidate: " <<*it<<std::endl;
          std::string param_name; // *output* of parsing function, parameter name
          std::string label_root; // *output* of parsing function, label minus parameter name
          if(parse_label_for_ModelParameters(*it, modelname, param_name, label_root))
          {
            // Add the found parameter name to the ModelParameters object
            out._definePar(param_name);
            if(found_at_least_one)
            {
              if(out.getOutputName()!=label_root)
              {
                std::ostringstream err;
                err << "Error! HDF5Reader could not retrieve ModelParameters matching the model name '"
                    <<modelname<<"' in the HDF5 file:group "<<file<<":"<<group
                    <<"' (while calling 'retrieve'). Candidate parameters WERE found, however their dataset "
                    <<"labels indicate the presence of an inconsistency or ambiguity in the output. For "
                    <<"example, we just tried to retrive a model parameter from the dataset:\n  "<<*it
                    <<"\nand successfully found the parameter "<<param_name
                    <<", however the root of the label, that is,\n  "<<label_root
                    <<"\ndoes not match the root expected based upon previous parameter retrievals for this "
                    <<"model, which was\n  "<<out.getOutputName()<<"\nThis may indicate that multiple sets "
                    <<"of model parameters are present in the output file for the same model! This is not "
                    <<"allowed, please report this bug against whatever master YAML file (or external code?) "
                    <<"produced the output file you are trying to read.";
                printer_error().raise(LOCAL_INFO,err.str());
              }
            }
            else
            {
              out.setOutputName(label_root);
            }
            // Get the corresponding value out of the data file
            double value; // *output* of retrieve function
            bool tmp_is_valid;
            tmp_is_valid = _retrieve(value, *it, rank, pointID);
            found_at_least_one = true;
            if(tmp_is_valid)
            {
               out.setValue(param_name, value);
            }
            else
            {
               // If one parameter value is 'invalid' then we cannot reconstruct
               // the ModelParameters object, so we mark the whole thing invalid.
               out.setValue(param_name, 0);
               is_valid = false;
            }
          }
        }

        if(not found_at_least_one)
        {
          // Didn't find any matches!
           std::ostringstream err;
           err << "Error! HDF5Reader failed to find any ModelParameters matching the model name '"<<modelname<<"' in the HDF5 file:group "<<file<<":"<<group<<"' (while calling 'retrieve'). Please check that model name and input file/group are correct.";
           printer_error().raise(LOCAL_INFO,err.str());
        }
        /// done!
        return is_valid;
     }

     bool HDF5Reader::_retrieve(std::vector<double>& /*out*/,  const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool HDF5Reader::_retrieve(map_str_dbl& /*out*/,          const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool HDF5Reader::_retrieve(triplet<double>& /*out*/,      const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool HDF5Reader::_retrieve(map_intpair_dbl& /*out*/,      const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

     #ifndef SCANNER_STANDALONE // All the types inside HDF5_BACKEND_TYPES need to go inside this def guard.

       bool HDF5Reader::_retrieve(DM_nucleon_couplings& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
       bool HDF5Reader::_retrieve(DM_nucleon_couplings_fermionic_HP& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
       bool HDF5Reader::_retrieve(Flav_KstarMuMu_obs& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
       bool HDF5Reader::_retrieve(BBN_container& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

     #endif

     /// @}

  }
}
