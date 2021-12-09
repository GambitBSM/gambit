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

    /// Expand environment variables in the given string.
    void NodeUtility::autoExpandEnvironmentVariables(std::string & text)
    {
      // C++ regex does not support negative lookahead. So let us reverse the string.
      std::reverse(text.begin(), text.end());

      // Matches reverse ${MYVAR}, but not \${MYVAR} and $MYVAR
      const static std::regex env( "\\}([^{]+)\\{\\$(?!\\\\)" );

      std::smatch match;
      while (std::regex_search(text, match, env))
      {
          // Reverse the found match into a temporary variable, this is what we actually
          // want to look for, e.g. we found RAV, but we want to look for VAR.
          std::string tmp = match[1].str();
          std::reverse(tmp.begin(), tmp.end());

          // Look for VAR
          const char * s = std::getenv(tmp.c_str());

          std::string var(s == NULL ? "" : s);
          if (s == NULL)
          {
            std::cout << "Environment variable " << match.str() << " not set";
          }
          // Reverse the found environment variable...
          std::reverse(var.begin(), var.end());
          // and plug it into the text string.
          text.replace(match[0].first, match[0].second, var);
      }
      // Finally return the text string in the normal order.
      std::reverse(text.begin(), text.end());
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
