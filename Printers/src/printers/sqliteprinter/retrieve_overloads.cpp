//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite interface reaader class retrieve function
///  overloads.  Add a new overload of the _retrieve
///  function in this file if you want to be able
///  to read a new type for postprocessing.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Dec
///
///  *********************************************

#include "gambit/Printers/printers/sqlitereader.hpp"

namespace Gambit
{
  namespace Printers
  {

     /// @{ Retrieve functions

     // Retrieve functions for int-like data
     #define RETRIEVE_INT(TYPE) _retrieve(TYPE& out, const std::string& l, const uint r, const ulong p) \
     {\
        long long int buffer;\
        bool valid(false);\
        valid = _retrieve_template(buffer,l,0,r,p);\
        out = buffer;\
        return valid;\
     }\

     // Retrieve functions for float data
     #define RETRIEVE_REAL(TYPE) _retrieve(TYPE& out, const std::string& l, const uint r, const ulong p) \
     {\
        double buffer;\
        bool valid(false);\
        valid = _retrieve_template(buffer,l,0,r,p);\
        out = buffer;\
        return valid;\
     }\

     /// Templatable retrieve functions
     bool SQLiteReader::RETRIEVE_INT(bool     )
     bool SQLiteReader::RETRIEVE_INT(int      )
     bool SQLiteReader::RETRIEVE_INT(uint     )
     bool SQLiteReader::RETRIEVE_INT(long     )
     bool SQLiteReader::RETRIEVE_INT(ulong    )
     bool SQLiteReader::RETRIEVE_INT(longlong )
     bool SQLiteReader::RETRIEVE_INT(ulonglong)
     bool SQLiteReader::RETRIEVE_REAL(float   )
     bool SQLiteReader::RETRIEVE_REAL(double  )
     #undef RETRIEVE_INT
     #undef RETRIEVE_REAL

     bool SQLiteReader::_retrieve(ModelParameters& out, const std::string& modelname, const uint rank, const ulong pointID)
     {
        bool is_valid = true;
        /// Work out all the output labels which correspond to the input modelname
        bool found_at_least_one(false);

        //std::cout << "Searching for ModelParameters of model '"<<modelname<<"'"<<std::endl;
        // Iterate through names in the SQLite table
        for(auto it = column_map.begin(); it!= column_map.end(); ++it)
        {
          std::string candidate = it->first;
          //std::cout << "Candidate: " <<*it<<std::endl;
          std::string param_name; // *output* of parsing function, parameter name
          std::string label_root; // *output* of parsing function, label minus parameter name
          if(parse_label_for_ModelParameters(candidate, modelname, param_name, label_root, false))
          {
            // Add the found parameter name to the ModelParameters object
            out._definePar(param_name);
            if(found_at_least_one)
            {
              if(out.getOutputName()!=label_root)
              {
                std::ostringstream err;
                err << "Error! SQLiteReader could not retrieve ModelParameters matching the model name '"
                    <<modelname<<"' in the SQLite database file '"<<get_database_file()<<"', table '"<<get_table_name()
                    <<"' (while calling 'retrieve'). Candidate parameters WERE found, however their "
                    <<"labels indicate the presence of an inconsistency or ambiguity in the output. For "
                    <<"example, we just tried to retrive a model parameter from the dataset:\n  "<<candidate
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
            tmp_is_valid = _retrieve(value, candidate, rank, pointID);
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
           err << "Error! SQLiteReader could not retrieve ModelParameters matching the model name '"
               <<modelname<<"' in the SQLite database file '"<<get_database_file()<<"', table '"<<get_table_name()
               <<"' (while calling 'retrieve'). Please check that model name and input file/table are correct.";
           printer_error().raise(LOCAL_INFO,err.str());
        }
        /// done!
        return is_valid;
     }

     bool SQLiteReader::_retrieve(std::vector<double>& /*out*/,  const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool SQLiteReader::_retrieve(map_str_dbl& /*out*/,          const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool SQLiteReader::_retrieve(triplet<double>& /*out*/,      const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
     bool SQLiteReader::_retrieve(map_intpair_dbl& /*out*/,      const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
     { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

    #ifndef SCANNER_STANDALONE // All the types inside SQLITE_MODULE_BACKEND_TYPES need to go inside this def guard.

       bool SQLiteReader::_retrieve(DM_nucleon_couplings& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
       bool SQLiteReader::_retrieve(DM_nucleon_couplings_fermionic_HP& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
       bool SQLiteReader::_retrieve(Flav_KstarMuMu_obs& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
       { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

     #endif

     /// @}

  }
}
