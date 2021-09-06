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

#include <cstring>
#include <regex>

#include "gambit/Utils/yaml_node_utility.hpp"
#include <cstring>

namespace Gambit
{

    //bodge by Andy to enable compilation on CentOS systems, applied by Tomek Procter  
    void NodeUtility::autoExpandEnvironmentVariables(std::string &text) {
      static std::regex env( "\\$\\{([^}]+)\\}" );
      std::smatch match;
      while ( std::regex_search( text, match, env ) ) {
      const char * s = getenv( match[1].str().c_str() );
      const std::string var( s == NULL ? "" : s );              
      text.replace( match[0].first - std::cbegin(text), match[0].str().size(), var );
      }
    }

    /// Remove characters in the given string.
    void NodeUtility::removeCharsFromString(std::string& text, const char* charsToRemove)
    {
       for (unsigned int i = 0; i < std::strlen(charsToRemove); ++i)
       {
          text.erase(std::remove(text.begin(), text.end(), charsToRemove[i]), text.end());
       }
    }

    /// Leave input alone and return new string, which has environment variables
    /// substituted and escpae characters removed.
    std::string NodeUtility::expandEnvironmentVariables(const std::string& input)
    {
      static const char* escape_character = "\\";
      std::string text = input;
      NodeUtility::autoExpandEnvironmentVariables(text);
      NodeUtility::removeCharsFromString(text, escape_character);
      return text;
    }

}
