//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ASCII reader retrieve function overloads.
///  Add a new overload of the _retrieve function
///  in this file if you want to be able to read
///  a new type during postprocessing.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2016 Jan
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 March
///
///  *********************************************

#include "gambit/Printers/printers/asciireader.hpp"
#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{

  namespace Printers
  {

    /// @{ Retrieval functions

    /// Everything is a string in the output file, so use this as the 'master' retrieve function, and the others
    /// just wrap it in various ways
    bool asciiReader::_retrieve(std::string& out, const std::string& label, const uint rank, const ulong pointID)
    {
      // return value
      bool is_valid = true;

      /// Advance read-head position until the target point is found (or throw an error if it cannot be found)
      /// Will be fastest if we are already at the right position or only have to go forward a small number of slots
      /// Going backwards will involve traversing the whole file forwards and looping back around from the start!
      advance_to_point(PPIDpair(pointID,rank));

      /// Check which column is supposed to correspond with 'label'
      uint target_col = 0;
      std::map<std::string,uint>::const_iterator it = column_map.find(label);
      if(it != column_map.end())
      {
        target_col = it->second;
      }
      else
      {
        std::ostringstream err;
        err << "Error! asciiReader could not retrieve requested output entry '"
            <<label<<"'. This label does not match any column described in the loaded 'info' file '"
            <<infoFile_name<<"'.";
        printer_error().raise(LOCAL_INFO,err.str());
      }

      /// Parse the line and extract the entry
      std::istringstream iss(current_line);
      unsigned int i=0;
      std::string garbage;
      while(i<target_col)
      {
        iss >> garbage;
        if(!iss)
        {
           std::ostringstream err;
           err << "Error! asciiReader failed to read line '"<<current_row+1<<"', column '"<<i+1
               <<"' from the wrapped output file '"<<dataFile_name
               <<"'! The file may be corrupt, or may contain fewer columns than expected (was planning to iterate up to column '"
               <<target_col<<"').";
           printer_error().raise(LOCAL_INFO,err.str());
        }
        i++;
      }
      iss >> out;
      if(!iss)
      {
         std::ostringstream err;
         err << "Error! asciiReader failed to read line '"<<current_row+1<<"', column '"<<i+1
             <<"' from the wrapped output file '"<<dataFile_name
             <<"'! The file may be corrupt, or may contain fewer columns than expected (was planning to iterate up to column '"
             <<target_col<<"').";
         printer_error().raise(LOCAL_INFO,err.str());
      }
      if(out=="none")
      {
         // Valid data was not recorded for this quantity at this pointID.
         is_valid = false;
      }
      /// done!
      return is_valid;
    }

    bool asciiReader::_retrieve(double& out, const std::string& label, const uint rank, const ulong pointID)
    {
      /// Get requested quantity as a string, then convert it to a double
      std::string temp_out;
      bool is_valid;
      is_valid = _retrieve(temp_out, label, rank, pointID);
      if(is_valid)
      {
        std::istringstream iss(temp_out);
        iss >> out;
        if(!iss)
        {
           std::ostringstream err;
           err << "Error! asciiReader retrieved an element of '"<<label<<"' from the data file '"
               <<dataFile_name<<"', which is not marked as 'invalid', but failed to convert it to type 'double'."
               <<" The data file may be corrupted, or you may have tried to use an inappropriate 'retrieve' type "
               <<" for this data. Error occurred while reading from row '"<<current_row
               <<"'. Retrieved string value was '"<<temp_out<<"'.";
           printer_error().raise(LOCAL_INFO,err.str());
        }
      }
      else
      {
        out = 0; // but also marked invalid, so default number is unimportant.
      }
      /// done!
      return is_valid;
    }

    /// This one is fancy, gets ALL the ModelParameters matching a certain model name
    /// So say the labels for two parameters are:
    ///
    ///#NormalDist_parameters @NormalDist::primary_parameters::mu
    ///#NormalDist_parameters @NormalDist::primary_parameters::sigma
    ///
    /// Then to get a ModelParameters object containing "mu" and "sigma" you should enter
    /// 'NormalDist' as the label.
    ///
    ///Note:
    ///label=("#"+func_capability+" @"+origin_name+"::"+func_name)
    ///
    bool asciiReader::_retrieve(ModelParameters& out, const std::string& modelname, const uint rank, const ulong pointID)
    {
      bool is_valid = true;

      /// Work out all the output labels that correspond to the input modelname
      bool found_at_least_one(false);
      for(const std::pair<std::string,uint>& kv : column_map)
      {
        std::string param_name; // *output* of parsing function, parameter name
        std::string label_root; // *output* of parsing function, label minus parameter name
        if(parse_label_for_ModelParameters(kv.first, modelname, param_name, label_root))
        {
          // Add the found parameter name to the ModelParameters object
          out._definePar(param_name);
          if(found_at_least_one)
          {
            if(out.getOutputName()!=label_root)
            {
               std::ostringstream err;
               err << "Error! ASCIIReader could not retrieve ModelParameters matching the model name '"<<modelname
                   <<"' in the ascii file '"<<dataFile_name<<"' (while calling 'retrieve'). Candidate parameters WERE "
                   <<"found, however their dataset labels indicate the presence of an inconsistency or ambiguity in "
                   <<"the output. For example, we just tried to retrive a model parameter from the dataset:\n" << kv
                   // <<"[" << kv.first << "->" << kv.second << "]"
                   <<"\nand successfully found the parameter "<<param_name<<", however the root of the label, that is,\n"
                   <<label_root<<"\ndoes not match the root expected based upon previous parameter retrievals for this model, which was\n  "
                   <<out.getOutputName()<<"\nThis may indicate that multiple sets of model parameters are present in the "
                   <<"output file for the same model! This is not allowed, please report this bug against whatever master "
                   <<"YAML file (or external code?) produced the output file you are trying to read.";
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
          tmp_is_valid = _retrieve(value, kv.first, rank, pointID);
          found_at_least_one = true;
          if(tmp_is_valid)
          {
             out.setValue(param_name, value);
             //std::cout<<"Extracted parameter "<<param_name<<", value="<<value<<std::endl;
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
         err << "Error! asciiReader failed to find any ModelParameters matching the model name '"<<modelname
             <<"' in the info file '"<<infoFile_name<<"' (while calling 'retrieve'). Please check that model name and info file name are correct.";
         printer_error().raise(LOCAL_INFO,err.str());
      }
      /// done!
      return is_valid;
    }

    bool asciiReader::_retrieve(bool& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(int& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(unsigned int& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(short& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(unsigned short& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(long& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(unsigned long& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(long long& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(unsigned long long& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(float& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<bool>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<int>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<unsigned int>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<short>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<unsigned short>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<long>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<unsigned long>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<long long>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<unsigned long long>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<float>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(std::vector<double>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(map_str_dbl& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(triplet<double>& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
    bool asciiReader::_retrieve(map_intpair_dbl& /*out*/,const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

    #ifndef SCANNER_STANDALONE // All the types inside ASCII_MODULE_BACKEND_TYPES need to go inside this def guard.

      bool asciiReader::_retrieve(DM_nucleon_couplings& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
      { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
      bool asciiReader::_retrieve(DM_nucleon_couplings_fermionic_HP& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
      { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }
      bool asciiReader::_retrieve(Flav_KstarMuMu_obs& /*out*/, const std::string& /*label*/, const uint /*rank*/, const ulong /*pointID*/)
      { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

    #endif

    /// @}

  }
}
