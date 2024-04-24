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

#include "gambit/Core/yaml_description_database.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/variadic_functions.hpp"

namespace Gambit
{
  /// Emitter for the capability_info struct
  YAML::Emitter& operator << (YAML::Emitter& out, const capability_info& info)
  {
    std::vector< std::pair<str, std::map<str, std::set<std::pair<str,str> > > > > origins;
    origins.push_back(std::pair<str, std::map<str, std::set<std::pair<str,str> > > >("modules", info.modset));
    origins.push_back(std::pair<str, std::map<str, std::set<std::pair<str,str> > > >("backends", info.beset));
    out << YAML::BeginMap;
    out << YAML::Key << "name" << YAML::Value << info.name;
    out << YAML::Key << "description";
    out << YAML::Literal << info.description; // Long string format
    for (std::vector< std::pair<str, std::map<str, std::set<std::pair<str,str> > > > >::const_iterator it = origins.begin(); it != origins.end(); ++it)
    {
      out << YAML::Key << it->first << YAML::Value << YAML::BeginSeq;
      for (std::map<str, std::set<std::pair<str,str> > >::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
      {
        out << YAML::BeginMap << YAML::Key << jt->first << YAML::Value << YAML::BeginSeq;
        for (std::set<std::pair<str,str> >::const_iterator kt = jt->second.begin(); kt != jt->second.end(); ++kt)
        {
          out << YAML::BeginMap << YAML::Key << kt->first << YAML::Value << kt->second << YAML::EndMap; 
        }
        out << YAML::EndSeq << YAML::EndMap;
      }
      out << YAML::EndSeq;
    }
    out << YAML::EndMap;  
    out << YAML::Newline;
    return out;
  }
  
  /// Emitter for the model_info struct
  YAML::Emitter& operator << (YAML::Emitter& out, const model_info& info)
  {
    out << YAML::BeginMap;
    out << YAML::Key << "name" << YAML::Value << info.name;
    out << YAML::Key << "nparams" << YAML::Value << info.nparams;
    out << YAML::Key << "parameters"<< YAML::Value << YAML::BeginSeq;
    for (std::vector<std::string>::const_iterator jt = info.parameters.begin(); jt != info.parameters.end(); ++jt)
    {
     out << *jt;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "parent" << YAML::Value << info.parent;
    out << YAML::Key << "lineage" << YAML::Value << YAML::BeginSeq;
    for (std::vector<std::string>::const_iterator jt = info.lineage.begin(); jt !=info.lineage.end(); ++jt)
    {
     out << *jt;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "descendants" << YAML::Value << YAML::BeginSeq;
    for (std::vector<std::string>::const_iterator jt = info.descendants.begin(); jt !=info.descendants.end(); ++jt)
    {
     out << *jt;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "description";
    out << YAML::Literal << info.description; // Long string format
    out << YAML::EndMap;  
    out << YAML::Newline;
    return out;
  }

  /// Member functions for DescriptionDatabase class

  /// Default constructor
  DescriptionDatabase::DescriptionDatabase() {}

  /// Construct from file
  DescriptionDatabase::DescriptionDatabase(const str& filename)
  {
     loadFile(filename);
  }

  /// Copy constructor
  DescriptionDatabase::DescriptionDatabase(const YAML::Node &desc) : descriptions(desc) {}
  
  /// Move constructor
  DescriptionDatabase::DescriptionDatabase(YAML::Node &&desc) : descriptions(std::move(desc)) {}

  /// Check 'descriptions' for duplicate keys
  std::map<str,int> DescriptionDatabase::check_for_duplicates()
  {
    std::set<str> found; //found keys
    std::map<str,int> duplicates; //name and number of duplicates
    for(YAML::const_iterator it=descriptions.begin();it!=descriptions.end();++it) 
    {
      str name = it->first.as<str>();
      if(found.find(name)==found.end())
      {
        found.insert(name);
        duplicates[name] = 0;
      }
      else
      {
        duplicates[name] = duplicates[name] + 1;   
      }         
    }
    return duplicates;
  }
  
  /// Return vector of descriptions matching key (for retrieving values with non-unique keys)
  std::vector<str> DescriptionDatabase::get_all_values(str key)
  {
    std::vector<str> values;
    for(YAML::const_iterator it=descriptions.begin();it!=descriptions.end();++it) 
    {
      if(key==it->first.as<str>())
      {
        values.push_back(it->second.as<str>());
      }
    }
    return values;
  } 

} // end Gambit namespace

