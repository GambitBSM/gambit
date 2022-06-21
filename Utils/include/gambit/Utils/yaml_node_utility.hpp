//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Wrapper functionality to get yaml nodes with
///  some extras.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2020 April
///
///  *********************************************


#ifndef __yaml_node_utility_hpp__
#define __yaml_node_utility_hpp__

#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstring>

#include "yaml-cpp/yaml.h"

#include "gambit/Utils/standalone_error_handlers.hpp"

namespace Gambit
{

  namespace NodeUtility
  {

      /// Wrapper for integer type casts from a double in string representation.
      /// It does first try to safely convert the string to a double and
      /// then performs checks before casting to an integer type.
      template<class TYPE>
      TYPE safeIntegerTypeCast(const std::string& s)
      {
        try
        {
          const double d = std::stod(s);
          if (d != std::floor(d))
          {
            std::ostringstream os;
            os << "Provided value " << d << " as option in the yaml file does not represent an integer.";
            utils_error().raise(LOCAL_INFO, os.str());
          }
          if (static_cast<double>(std::numeric_limits<TYPE>::max()) < d or static_cast<double>(std::numeric_limits<TYPE>::min()) > d)
          {
            std::ostringstream os;
            os << "Provided value " << d << " as option in the yaml file does not fit into the implemented integer type.";
            utils_error().raise(LOCAL_INFO, os.str());
          }
          return static_cast<TYPE>(d);
        }
        catch (const std::out_of_range& e)
        {
          std::ostringstream os;
          os << "Out of range error: " << e.what() << "\n";
          os << "Provided value " << s << " as option in the yaml file does not fit into double.";
          utils_error().raise(LOCAL_INFO, os.str());
        }
        catch (const std::invalid_argument& e)
        {
          std::ostringstream os;
          os << "Invalid argument: " << e.what() << "\n";
          os << "Provided value " << s << " as option in the yaml file can not be interpreted as double.";
          utils_error().raise(LOCAL_INFO, os.str());
        }
        throw std::runtime_error("Reached end of function safeIntegerTypeCast. This should not happen.");
      }

      /// Expand environment variables in the given string.
      void autoExpandEnvironmentVariables(std::string & text);

      /// Remove characters in the given string.
      void removeCharsFromString(std::string& text, const char* charsToRemove);

      /// Leave input alone and return new string, which has environment variables
      /// substituted and escpae characters removed.
      std::string expandEnvironmentVariables(const std::string& input);

      /// Wrapper for reading the node for a given type. Default case does nothing.
      /// However in some instances we want to catch the yamlcpp exception and try
      /// to interpret it, e.g. scientific notation numbers as integers.
      template<class TYPE>
      TYPE getNode(const YAML::Node node) { return node.as<TYPE>(); }

      /// Allows to read scientific notation integer numbers. If the number does not
      /// fit into the given type (here int) or is not an integer, this function will raise.
      /// This exception is then caught by getValue and handled.
      template<>
      inline int getNode<int>(const YAML::Node node)
      {
        try { return node.as<int>(); }
        catch (...) { return safeIntegerTypeCast<int>(node.as<std::string>()); }
      }

      /// See int specialization.
      template<>
      inline unsigned int getNode<unsigned int>(const YAML::Node node)
      {
        try { return node.as<unsigned int>(); }
        catch (...) { return safeIntegerTypeCast<unsigned int>(node.as<std::string>()); }
      }

      /// See int specialization.
      template<>
      inline long getNode<long>(const YAML::Node node)
      {
        try { return node.as<long>(); }
        catch (...) { return safeIntegerTypeCast<long>(node.as<std::string>()); }
      }

      /// See int specialization.
      template<>
      inline unsigned long getNode<unsigned long>(const YAML::Node node)
      {
        try { return node.as<unsigned long>(); }
        catch (...) { return safeIntegerTypeCast<unsigned long>(node.as<std::string>()); }
      }

      /// See int specialization.
      template<>
      inline long long getNode<long long>(const YAML::Node node)
      {
        try { return node.as<long long>(); }
        catch (...) { return safeIntegerTypeCast<long long>(node.as<std::string>()); }
      }

      /// See int specialization.
      template<>
      inline unsigned long long getNode<unsigned long long>(const YAML::Node node)
      {
        try { return node.as<unsigned long long>(); }
        catch (...) { return safeIntegerTypeCast<unsigned long long>(node.as<std::string>()); }
      }

      /// Read string and expand environment variables of the type ${MYVAR}.
      /// Expansion of environment variables is not performed if given as
      /// $MYVAR and \${MYVAR}.
      template<>
      inline std::string getNode<std::string>(const YAML::Node node)
      {
        return NodeUtility::expandEnvironmentVariables(node.as<std::string>());
      }

  }

}

#endif //__yaml_node_utility_hpp__
