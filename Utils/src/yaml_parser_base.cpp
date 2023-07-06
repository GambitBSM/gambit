//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base class for ini-file parsers using yaml-cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 May, June, July
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 June
///
///  *********************************************

#include <iostream>

#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Logs/logmaster.hpp"

#ifdef GAMBIT_LIGHT
#include <regex>
#endif

namespace Gambit
{

  namespace IniParser
  {

    /// Recursive import
    int importRound(YAML::Node node, const std::string& filename)
    {
      int counter = 0;
      if (node.IsScalar())
      {
        if ( node.Tag() == "!import" )
        {
          #ifdef WITH_MPI
            int rank = GMPI::Comm().Get_rank();
          #else
            int rank = 0;
          #endif
          YAML::Node import;
          std::string new_filename = node.as<std::string>();
          if (rank == 0) std::cout << "Importing: " << new_filename << std::endl;
          try
          {
            // We want to do the import relative to the path in which the YAML file
            // sits, unless it has a forward slash at the beginning (in which case we
            // will interpret it as an absolute path)
            std::string file_location = Utils::dir_name(filename); // "outer" file location
            if(new_filename.at(0)=='/') // POSIX
            {
               // Use the absolute path as given
               import = YAML::LoadFile(new_filename);        
            }
            else
            {
               // Append the path of the outer file
               new_filename = file_location+"/"+new_filename;
               import = YAML::LoadFile(new_filename);        
            }
          }
          catch (YAML::Exception &e)
          {
            std::ostringstream msg;
            msg << "Error importing \""<<new_filename<<"\"! ";
            msg << "Please check that file exists! Error occurred during parsing of YAML file '"<<filename<<"'" << endl;
            msg << "(yaml-cpp error: "<<e.what()<<" )";
            inifile_error().raise(LOCAL_INFO,msg.str());
          }
          node = import;
          return 1;
        }
        return 0;
      }
      if (node.IsSequence())
      {
        for (unsigned int i = 0; i<node.size(); ++i)
        {
          counter += importRound(node[i],filename);
        }
        return counter;
      }
      if (node.IsMap())
      {
        for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
        {
          counter += importRound(it->second,filename);  // Only values are processed
        }
        return counter;
      }
      return 0;
    }

    void recursiveImport(const YAML::Node& node, const std::string& filename)
    {
      int last_import_counter = 0;
      for ( int i = 0; i < 10; ++i)
      {
        last_import_counter = importRound(node,filename);
      }
      if (last_import_counter > 0)
      {
        #ifdef WITH_MPI
          int rank = GMPI::Comm().Get_rank();
        #else
          int rank = 0;
        #endif
        if (rank == 0)
        {
          std::cout << last_import_counter << std::endl;
          std::cout << "WARNING: YAML imports were truncated after 10 recursions." << std::endl;
        }
      }
    }


    // Implementations of main inifile class

    void Parser::readFile(std::string filename)
    {
      YAML::Node root = filename_to_node(filename);
      basicParse(root,filename);
    }

    YAML::Node Parser::filename_to_node(std::string filename)
    {
      YAML::Node root;
      // Read inifile file
      try
      {
        root = YAML::LoadFile(filename);
      }
      catch (YAML::Exception &e)
      {
        std::ostringstream msg;
        msg << "Error reading Inifile \""<<filename<<"\"! ";
        msg << "Please check that file exist!" << endl;
        msg << "(yaml-cpp error: "<<e.what()<<" )";
        inifile_error().raise(LOCAL_INFO,msg.str());
      }
      return root;
    }

    void Parser::basicParse(YAML::Node root, std::string filename)
    {
      recursiveImport(root,filename);
      YAMLNode = root;
      parametersNode = root["Parameters"];
      priorsNode = root["Priors"];
      printerNode = root["Printer"];
      scannerNode = root["Scanner"];
      logNode = root["Logger"];
      keyValuePairNode = root["KeyValues"];

      // Special treatment for GAMBIT-light
      #ifdef GAMBIT_LIGHT
        userModelNode = root["UserModel"];
        userLogLikesNode = root["UserLogLikes"];

        bool has_UserPrior_node = root["UserPrior"].IsDefined();
        if (has_UserPrior_node)
        {
          userPriorNode = root["UserPrior"];
        }

        std::map<std::pair<int,int>,YAML::Node> par_range_nodes;
        std::map<std::pair<int,int>,std::string> par_range_names;

        const std::regex full_par_name_regex("^UserModel::p[0-9]+$");
        const std::regex par_name_regex("^p[0-9]+$");
        const std::regex par_name_range_regex("^p([0-9]+)-p([0-9]+)$");
        std::smatch full_par_name_match;
        std::smatch par_name_match;
        std::smatch par_name_range_match;

        for(YAML::iterator it = userModelNode.begin(); it != userModelNode.end(); ++it)
        {
          std::string par_name = it->first.as<std::string>();
          YAML::Node& par_node = it->second;
  
          // If a parameter node in "UserModel" is a Scalar/Sequence, 
          // convert to a Map by adding the "fixed_value" key.
          if (par_node.IsScalar() or par_node.IsSequence()) 
          {
            YAML::Node new_node;
            new_node["fixed_value"] = par_node;
            par_node = new_node;
          }

          // Check that all nodes in "UserModel" have names that match a parameter
          // name (e.g. "p13") or a range of parameter names (e.g. "p5-p10").
          bool par_name_matched = std::regex_match(par_name, par_name_match, par_name_regex);
          bool par_name_range_matched = std::regex_match(par_name, par_name_range_match, par_name_range_regex);

          if (!par_name_matched && !par_name_range_matched)
          {
            inifile_error().raise(LOCAL_INFO, 
              "Error while parsing the UserModel settings: The name '" + par_name + "' "
              "is not a valid UserModel parameter entry. Either use a valid parameter name "
              "('p0', 'p1', 'p2', ...) or specify a range of parameters (e.g. 'p1-p8')."
            );
          }

          // If a range of parameters was specified, save the parameter indices and 
          // the YAML node so we can add individual parameter nodes later
          if (par_name_range_matched)
          {
            int par_index_min = std::stoi(par_name_range_match[1].str());
            int par_index_max = std::stoi(par_name_range_match[2].str());
            if (par_index_min >= par_index_max)
            {
              inifile_error().raise(LOCAL_INFO, 
                "Error while parsing the UserModel settings: The parameter range '"
                 + par_name_range_match[0].str() + "' has non-increasing indices."
              );
            }
            std::pair<int,int> par_index_pair(par_index_min, par_index_max);
            par_range_nodes[par_index_pair] = YAML::Clone(par_node);
            par_range_names[par_index_pair] = par_name;
          }
        }

        // For each parameter range entry (e.g. 'p1-p8'), construct individual parameter 
        // nodes for all parameters included in the range, and then delete the node
        // with the parameter range entry.
        for (const auto& pair_ii_node : par_range_nodes)
        {
          std::string par_range_name = par_range_names[pair_ii_node.first];
          int min_index = pair_ii_node.first.first;
          int max_index = pair_ii_node.first.second;

          const YAML::Node& par_range_node = pair_ii_node.second;

          bool has_name_option = par_range_node["name"].IsDefined();
          std::string user_name;
          if (has_name_option)
          {
            user_name = par_range_node["name"].as<std::string>();
          }

          for (int index = min_index; index <= max_index; ++index)
          {
            std::string par_name = "p" + std::to_string(index);
            if (userModelNode[par_name].IsDefined())
            {
              inifile_error().raise(LOCAL_INFO, 
                "Error while parsing the UserModel settings: Multiple entries "
                "for the parameter '" + par_name + "', which is part of "
                "the range entry '" + par_range_name + "'."
              );
            }
            userModelNode[par_name] = YAML::Clone(par_range_node);
            if (has_name_option)
            {
              userModelNode[par_name]["name"] = user_name + std::to_string(index);
            }
          }
          userModelNode.remove(par_range_name);
        }

        // For each parameter, check the 'same_as' option if present. 
        // If an entry like "same_as: p3" is found, automatically 
        // translate it to the complete form "same_as: UserModel::p3" 
        // expected by GAMBIT.
        for(YAML::iterator it = userModelNode.begin(); it != userModelNode.end(); ++it)
        {
          std::string par_name = it->first.as<std::string>();
          YAML::Node& par_node = it->second;
          if (par_node["same_as"].IsDefined())
          {
            std::string same_as_par_name = par_node["same_as"].as<std::string>();

            bool full_par_name_matched = std::regex_match(same_as_par_name, full_par_name_match, full_par_name_regex);
            bool par_name_matched = std::regex_match(same_as_par_name, par_name_match, par_name_regex);

            if (par_name_matched)
            {
              par_node["same_as"] = "UserModel::" + same_as_par_name;
            }

            if (!full_par_name_matched && !par_name_matched)
            {
              inifile_error().raise(LOCAL_INFO, 
                "Error while parsing the UserModel settings: Unrecognised parameter "
                "'" + same_as_par_name + "' in the 'same_as' option for parameter "
                "'" + par_name + "'. Expected a parmater name of the form 'p1', 'p2', etc."
              );
            }
          }
        }

        // Override the parametersNode variable with a node we construct 
        // from the "UserModel" node. We construct a new parameters node 
        // (newParametersNode), add an entry "UserModel" (which corresponds 
        // to a model name) and fill it with the content from root["UserModel"].
        YAML::Node newParametersNode;
        newParametersNode["UserModel"] = userModelNode;
        // Now override the existing parametersNode variable
        parametersNode = newParametersNode;


        // If there is a "UserPrior" node, use this to construct a new
        // "Priors" node that overrides the old priorsNode variable
        if (has_UserPrior_node)
        {
          // Check that the required entries are present
          if (userPriorNode.size() != 3 
              || !userPriorNode["lang"].IsDefined()
              || !userPriorNode["user_lib"].IsDefined()
              || !userPriorNode["func_name"].IsDefined())
          {
            inifile_error().raise(LOCAL_INFO, 
              "Error while parsing the UserPrior settings: The UserPrior section must contain "
              "exactly the three entries 'lang', 'user_lib' and 'func_name'. (Multiple instances " 
              "are not allowed.)"
            );
          }
          
          YAML::Node newPriorsNode;
          newPriorsNode["gambit_light_prior"] = userPriorNode;
          userPriorNode["prior_type"] = "userprior";
          for(YAML::iterator it = userModelNode.begin(); it != userModelNode.end(); ++it)
          {
            std::string par_name = it->first.as<std::string>();
            userPriorNode["parameters"].push_back("UserModel::" + par_name);
          }
          priorsNode = newPriorsNode;
        }


        // Force the "like: LogLike" option for all listed scanner plugins,
        // to match the "purpose: LogLike" in the pre-defined ObsLikes section 
        // for GAMBIT-light.
        YAML::Node listed_scanner_plugins = scannerNode["scanners"];
        for(YAML::const_iterator it = listed_scanner_plugins.begin(); it != listed_scanner_plugins.end(); ++it)
        {
          str plugin_name = it->first.as<str>();
          scannerNode["scanners"][plugin_name]["like"] = "LogLike";
        }
      #endif  // End #ifdef GAMBIT_LIGHT

      // Set default output path
      std::string defpath;
      if(hasKey("default_output_path"))
      {
         defpath = getValue<std::string>("default_output_path");
      }
      else
      {
         // Assign a default default (;)) path based on the yaml file name
         // Ridiculously we have to parse manually in C++ since no
         // standard library tools for doing this exist...
         // Assumes that file extension has only one dot, or that
         // there is no file extension. Should work anyway if more
         // dots, will just get a directory name with a dot in it.
         size_t fname_start = filename.find_last_of("/\\");
         size_t fname_end   = filename.find_last_of(".");
         str fname = filename.substr(fname_start+1,fname_end);
         defpath = "runs/" + fname + "/";
      }
      scannerNode["default_output_path"] = Utils::ensure_path_exists(defpath+"/scanner_plugins/");
      logNode    ["default_output_path"] = Utils::ensure_path_exists(defpath+"/logs/");
      printerNode["options"]["default_output_path"] = Utils::ensure_path_exists(defpath+"/samples/");

      // Make a copy of yaml file in output dir
      str new_filename = defpath+'/'+Utils::base_name(filename);
      bool replace_yaml_file = getValueOrDef<bool>(true, "replace_yaml_file");
      printNode(root,new_filename,replace_yaml_file);

      // Postprocessor is currently incompatible with 'print_timing_data', so need to pass this option on for checking
      scannerNode["print_timing_data"] = getValueOrDef<bool>(false,"print_timing_data");

      // Pass on minimum recognised lnlike and offset to Scanner
      scannerNode["model_invalid_for_lnlike_below"] = getValueOrDef<double>(0.9*std::numeric_limits<double>::lowest(), "likelihood", "model_invalid_for_lnlike_below");
      if (hasKey("likelihood", "lnlike_offset"))
        scannerNode["lnlike_offset"] = getValue<double>("likelihood", "lnlike_offset");

      // Set fatality of exceptions
      if (hasKey("exceptions"))
      {
        // Iterate over the map of all recognised exception objects
        std::map<const char*,exception*>::const_iterator iter;
        for (iter = exception::all_exceptions().begin(); iter != exception::all_exceptions().end(); ++iter)
        {
          // Check if the exception has an entry in the YAML file
          if (hasKey("exceptions",iter->first))
          {
            // Retrieve the entry and set the exception's 'fatal' flag accordingly.
            str value = getValue<str>("exceptions",iter->first);
            if (value == "fatal")
            {
              iter->second->set_fatal(true);
            }
            else if (value == "non-fatal")
            {
              iter->second->set_fatal(false);
            }
            else
            {
              str error_msg = "Unrecognised entry \"" + value + "\" for exceptions key \"" + iter->first + "\" in input file.";
              inifile_error().raise(LOCAL_INFO,error_msg);
            }
          }
        }
      }

      // Parse the logging setup node, and initialise the LogMaster object
      std::string prefix;
      if(logNode["prefix"])
      {
         prefix = logNode["prefix"].as<std::string>();
      }
      else
      {
         prefix = logNode["default_output_path"].as<std::string>()+"/";
      }

      // map storing info used to set up logger objects
      std::map<std::set<std::string>,std::string> loggerinfo;
      if(logNode["redirection"])
      {
         YAML::Node redir = logNode["redirection"];
         for(YAML::const_iterator it=redir.begin(); it!=redir.end(); ++it)
         {
             std::set<std::string> tags;
             std::string filename;
             // Iterate through tags and add them to the set
             YAML::Node yamltags = it->first;
             for(YAML::const_iterator it2=yamltags.begin();it2!=yamltags.end();++it2)
             {
               tags.insert( it2->as<std::string>() );
             }
             filename = (it->second).as<std::string>();

             // Add entry to the loggerinfo map
             if((filename=="stdout") or (filename=="stderr"))
             {
               // Special cases to trigger redirection to standard output streams
               loggerinfo[tags] = filename;
             }
             else
             {
               // The logger won't be able to create the log files if the prefix
               // directory doesn't exist, so let us now make sure that it does
               loggerinfo[tags] = Utils::ensure_path_exists(prefix + filename);
             }
         }
      }
      else
      {
         // Use default log file only
         std::set<std::string> tags;
         std::string filename;
         tags.insert("Default");
         filename = "default.log";
         loggerinfo[tags] = Utils::ensure_path_exists(prefix + filename);
     }
      // Initialise global LogMaster object
      bool master_debug = (keyValuePairNode["debug"]) ? keyValuePairNode["debug"].as<bool>() : false;
      bool logger_debug = (logNode["debug"])          ? logNode["debug"].as<bool>()          : false;
      logger().set_log_debug_messages(master_debug or logger_debug);
      logger().initialise(loggerinfo);

      // Parse the Parameters node and expand out some shorthand syntax
      // e.g.
      //  model1
      //    param1: 5.678
      // expands to
      //  model1
      //    param1:
      //      fixed_value: 5.678
      // Parameter must have no entries besides the value for this syntax to be valid
    }

    /// Print a yaml node to file
    void Parser::printNode(YAML::Node node, str filename, bool replace_yaml_file)
    {
      #ifdef WITH_MPI
        int rank = GMPI::Comm().Get_rank();
      #else
        int rank = 0;
      #endif
      if (rank == 0) 
      {
        if(not Utils::file_exists(filename) or replace_yaml_file)
        {
          std::ofstream fout(filename); 
          fout << node;
        }
      }
    }

    /// Getter for the full YAML Node
    YAML::Node Parser::getYAMLNode()         const {return YAMLNode;}
    /// Getters for key/value section
    /// @{
    YAML::Node Parser::getParametersNode()   const {return parametersNode;}
    YAML::Node Parser::getPriorsNode()       const {return priorsNode;}
    YAML::Node Parser::getPrinterNode()      const {return printerNode;}
    YAML::Node Parser::getScannerNode()      const {return scannerNode;}
    YAML::Node Parser::getLoggerNode()       const {return logNode;}
    YAML::Node Parser::getKeyValuePairNode() const {return keyValuePairNode;}
    #ifdef GAMBIT_LIGHT
      YAML::Node Parser::getUserModelNode() const {return userModelNode;}
      YAML::Node Parser::getUserLogLikesNode() const {return userLogLikesNode;}
    #endif
    /// @}

    /// Getters for model/parameter section
    /// @{
    bool Parser::hasModelParameterEntry(std::string model, std::string param, std::string key) const
    {
      return parametersNode[model][param][key];
    }

    /// Return list of model names (without "adhoc" model!)
    const std::set<str> Parser::getModelNames() const
    {
      std::set<str> result;
      for (YAML::const_iterator it = parametersNode.begin(); it!=parametersNode.end(); ++it)
      {
        if (it->first.as<std::string>() != "adhoc")
          result.insert( it->first.as<std::string>() );
      }
      return result;
    }

    const std::vector<std::string> Parser::getModelParameters(std::string model) const
    {
      std::vector<std::string> result;
      if (parametersNode[model])
      {
        for (YAML::const_iterator it = parametersNode[model].begin(); it!=parametersNode[model].end(); ++it)
        {
          result.push_back( it->first.as<std::string>() );
        }
      }
      return result;
    }

    /// Getter for options
    const Options Parser::getOptions(std::string key) const
    {
      if (hasKey(key, "options"))
      {
        return Options(keyValuePairNode[key]["options"]);
      }
      else
      {
        return Options(keyValuePairNode[key]);
      }
    }

    /// @}


  }
}
