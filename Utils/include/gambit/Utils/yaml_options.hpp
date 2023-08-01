//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations for the YAML options class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 June 2013
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2014 Feb
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2020 April
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 June
///
///  *********************************************

#ifndef __yaml_options_hpp__
#define __yaml_options_hpp__

#include <vector>
#include <sstream>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/yaml_variadic_functions.hpp"
#include "gambit/Utils/yaml_node_utility.hpp"

namespace Gambit
{

  ///  A small wrapper object for 'options' nodes.
  ///  These can be extracted from the prior, observable/likelihood and rules sections of the
  ///  inifile, or set by hand in module standalone mode.
  class Options
  {

    public:

      /// Default constructor
      Options() {}

      /// Copy constructor
      Options(const YAML::Node &options) : options(options) {}

      /// Move constructor
      Options(YAML::Node &&options) : options(std::move(options)) {}

      /// Getters for key/value pairs (which is all the options node should contain)
      /// @{
      template <typename... args>
      bool hasKey(const args&... keys) const
      {
        return getVariadicNode(options, keys...);
      }

      template<typename TYPE, typename... args>
      TYPE getValue(const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(options, keys...);
        TYPE result;
        if (not node)
        {
          std::ostringstream os;
          os << "No options entry for [" << stringifyVariadic(keys...) << "]\n Node contents:  " << options;
          utils_error().raise(LOCAL_INFO,os.str());
          result = TYPE();
        }
        else
        {
          try
          {
            result = NodeUtility::getNode<TYPE>(node);
          }
          catch(YAML::Exception& e)
          {
            std::string nodestr;
            try
            {
              nodestr = node.as<std::string>();
            }
            catch(YAML::Exception& e)
            {
              nodestr = "<Couldn't even convert to string!>";
            }
            std::ostringstream os;
            os << "Error retrieving options entry for [" << stringifyVariadic(keys...)
               << "] as type " << typeid(TYPE).name() << " (template parameter: see below). String form of node value was: "
               << nodestr << std::endl
               << "YAML message follows: " << std::endl
               << e.what();
            utils_error().raise(LOCAL_INFO,os.str());
            result = TYPE();
          }
        }
        return result;
      }

      template<typename TYPE, typename... args>
      TYPE getValueOrDef(TYPE def, const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(options, keys...);
        TYPE result;
        if (not node)
        {
          result = def;
        }
        else
        {
          result = getValue<TYPE>(keys...);
        }
        return result;
      }
      /// @}


      /// Basic setter, for adding extra options
      /// @{
      template<typename KEYTYPE, typename VALTYPE>
      void setValue(const KEYTYPE &key, const VALTYPE &val)
      {
         options[key] = val;
         return;
      }
      /// @}

      /**
       * @brief Get a `std::vector` of a particular type
       *
       * If the entry is a scalar rather than a vector, try to convert it to a size one
       * `std::vector`
       */
      template<typename TYPE>
      std::vector<TYPE> getVector(std::string key) const
      {
        if (getNode(key).IsScalar())
        {
          return {getValue<TYPE>(key)};
        }
        else
        {
          return getValue<std::vector<TYPE>>(key);
        }
      }

      /// Retrieve values from key-value pairs in options node.
      /// Works for an arbitrary set of input keys (of any type), and returns
      /// all values as strings.
      template<typename... args>
      const std::vector<str> getNames(const args&... keys) const
      {
        std::vector<str> result;
        const YAML::Node node = getVariadicNode(options, keys...);

        if (node.IsMap())
        {
          for (auto it = node.begin(), end = node.end(); it != end; ++it)
          {
            result.push_back( it->first.as<str>() );
          }
        }

        return result;
      }

      /// Retrieve values from all key-value pairs in options node.
      /// Returns all keys as strings.
      const std::vector<str> getNames() const
      {
        std::vector<str> result;

        for (auto it = options.begin(), end = options.end(); it != end; ++it)
        {
          result.push_back( it->first.as<str>() );
        }

        return result;
      }

      /// Recursive options retrieval
      template<typename... args>
      const Options getOptions(const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(options, keys...);
        if (node["options"])
        {
          return Options(node["options"]);
        }
        else
        {
          return Options(node);
        }
      }

      /// Retrieve raw YAML node
      template<typename... args>
      YAML::Node getNode(const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(options, keys...);
        if (not node)
        {
          std::ostringstream os;
          os << "No options entry for [" << stringifyVariadic(keys...) << "]\n Node contents:  " << options;
          utils_error().raise(LOCAL_INFO,os.str());
        }
        return node;
      }

      /// Get YAML node from file
      template<typename... args>
      YAML::Node loadFromFile(const args&... keys) const
      {
        const YAML::Node node = getVariadicNode(options, keys...);
        if (not node)
        {
          std::ostringstream os;
          os << "No options entry for [" << stringifyVariadic(keys...) << "]\n Node contents:  " << options;
          utils_error().raise(LOCAL_INFO,os.str());
        }
        return YAML::LoadFile(node.as<std::string>().c_str());
      }

      /// Return begin and end of options
      YAML::const_iterator begin() const { return options.begin(); }
      YAML::const_iterator end() const { return options.end(); }

      /// Convert to string with some indentation
      std::string toString(size_t level) const
      {
        std::stringstream ss;
        for (YAML::const_iterator it = begin(); it != end(); it++)
        {
          for(size_t i=0; i<level; i++) ss << "  ";
          ss << it->first.as<std::string>() << " : ";
          if(it->second.IsScalar())
            ss << it->second << endl;
          else if(it->second.IsMap())
            ss << endl << Options(it->second).toString(level+1);
          else if(it->second.IsSequence())
          {
            ss << endl;
            for (unsigned int j = 0; j<it->second.size(); ++j)
            {
              for(size_t i=0; i<level+1; i++) ss << "  ";
              ss << "- " << it->second[j] << endl;
            }
          }
          else
          {
            std::ostringstream os;
            os << "Couldn't convert options to string. YAML type unknown. ";
            utils_error().raise(LOCAL_INFO,os.str());
          }
        }
        return ss.str();
      }

      /// Convert the options node a map
      void toMap(map_str_str& map, str header = "") const
      {
        str head = header;
        if(not head.empty()) head += "::";

        for(auto node: *this)
        {
          str key;
          if(node.first.IsScalar())
            key = node.first.as<str>();
          else if(node.first.IsSequence())
          {
            key = "[";
            for(size_t j=0; j<node.first.size()-1; ++j)
              key += node.first[j].as<str>() + ",";
            key += node.first[node.first.size()-1].as<str>() + "]";
          }
          if(node.second.IsScalar())
            map[head + key] = node.second.as<str>();
          else if(node.second.IsMap())
            Options(node.second).toMap(map, head + key);
          else if(node.second.IsSequence())
          {
            str val = "[";
            for(size_t j=0; j<node.second.size(); ++j)
            {
              if(node.second[j].IsScalar() and j < node.second.size()-1)
                val += node.second[j].as<str>() + ", ";
              else if(node.second[j].IsSequence())
              {
                val += "[";
                for(size_t k=0; k<node.second[j].size()-1; ++k)
                {
                  if(node.second[j][k].IsScalar())
                    val += node.second[j][k].as<str>() + ",";
                  else
                    utils_error().raise(LOCAL_INFO, "Options node only allows 2D matrices");
                }
                val += node.second[j][node.second[j].size()-1].as<str>() + "]";
                if(j < node.second.size()-1) val += ",";
              }
            }
            if(node.second[node.second.size()-1].IsScalar())
              val += node.second[node.second.size()-1].as<str>();
            val += "]";
            map[head + key] = val;
          }
          else
          {
            std::ostringstream os;
            os << "Couldn't convert options to map. YAML type unknown. ";
            utils_error().raise(LOCAL_INFO,os.str());
          }
        }

      }

    private:

      YAML::Node options;
  };


}

#endif //#ifndef __yaml_options_hpp__
