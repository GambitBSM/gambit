//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Small wrapper object for parsing and emitting
///  capability/model etc. database information
///  using yaml-cpp
///
///  Also in this file are the definitions of
///  structs for carrying around capability/model
///  information, as well as YAML emitters/decoders
///  for these structs.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2014 Aug,Sep
///
///  *********************************************

#include <yaml-cpp/yaml.h>
#include <vector>
#include <sstream>
#include <utility>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/variadic_functions.hpp"
#include "gambit/Utils/yaml_variadic_functions.hpp"

#ifndef __yaml_description_database_hpp__
#define __yaml_description_database_hpp__

namespace Gambit
{
  /// Helper struct to carry around capability information
  struct capability_info
  {
     /// Capability name
     str name;
     /// Set of modules and module functions in which capability is used, along with corresponding result types
     std::map<str, std::set<std::pair<str,str> > > modset;
     /// Set of backends and backend functions in which capability is used, along with corresponding type signatures
     std::map<str, std::set<std::pair<str,str> > > beset;
     /// Full description of capability
     str description;
     /// Flag to check if description is missing
     bool has_description;
  };

  /// Helper struct to carry around model information
  struct model_info
  {
     /// Model name
     str name; 
     /// Parameter names
     std::vector<str> parameters; 
     /// Number of parameters ( parameters.size() )
     int nparams;
     /// Parent model name
     str parent; 
     /// Parent and all ancestor models
     std::vector<str> lineage;     
     /// All children and later descendants
     std::vector<str> descendants;
     /// Full description of capability 
     str description;
     /// Flag to check if description is missing
     bool has_description;
  };

  /// Emitter for the capability_info struct
  YAML::Emitter& operator << (YAML::Emitter&, const capability_info&);
  
  /// Emitter for the model_info struct
  YAML::Emitter& operator << (YAML::Emitter&, const model_info&);
 
  ///  A small wrapper object for 'description database' nodes.
  ///  The descriptions are extracted from, e.g., capabilities.dat
  class DescriptionDatabase 
  {

    public:

      /// Default constructor
      DescriptionDatabase();

      /// Construct from file
      DescriptionDatabase(const str& filename);

      /// Copy constructor
      DescriptionDatabase(const YAML::Node &descriptions);
      
      /// Move constructor
      DescriptionDatabase(YAML::Node &&descriptions);

      /// Getters for key/value pairs (which is all the options node should contain)
      /// @{
      template <typename... args>
      bool hasKey(const args&... keys) const
      {
        return bool(getVariadicNode(descriptions, keys...));
      }

      template<typename TYPE, typename... args>
      TYPE getValue(const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(descriptions, keys...);
        if (not node)
        {
          std::ostringstream os;
          os << "No entry for [" << stringifyVariadic(keys...) << "]\n Node contents:  " << descriptions;
          utils_error().raise(LOCAL_INFO,os.str());
        }
        return node.as<TYPE>();
      }
      /// @}
     
      
      /// Load descriptions from file
      template<typename... args>
      void loadFile(const str& filename)
      {
        try { 
          descriptions = YAML::LoadFile(filename);
        } 
        catch (YAML::Exception &e) {
          std::ostringstream msg;
          msg << "Error reading descriptions file \""<<filename<<"\"! ";
          msg << "Please check that file exists!" << endl;
          msg << "(yaml-cpp error: "<<e.what()<<" )";
          utils_error().raise(LOCAL_INFO,msg.str());
        }
      }

      /// Check 'descriptions' for duplicate keys
      std::map<str,int> check_for_duplicates();
          
      /// Return vector of descriptions matching key (for retrieving values with non-unique keys)
      std::vector<str> get_all_values(str key);
     
    private:

      YAML::Node descriptions;

  };

} // end Gambit namespace


#endif //defined __yaml_description_database_hpp__
