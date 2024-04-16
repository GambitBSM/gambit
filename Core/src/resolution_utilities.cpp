//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utilities useful during dependency resolution.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2022 Nov
///
///  *********************************************

#include "gambit/Core/resolution_utilities.hpp"
#include "gambit/Core/error_handlers.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Utils/util_functions.hpp"

#include <iostream>
#include <regex>

namespace Gambit
{

  namespace DRes
  {

    /// Check whether s1 (wildcard + regex allowed) matches s2
    bool stringComp(const str & s1, const str & s2)
    {
      if ( s1 == s2 ) return true;
      if ( s1 == "" ) return true;
      if ( s1 == "*" ) return true;
      if ( s1 == "any" ) return true;
      if ( s2 == "any" ) return true;
      try
      {
        if (std::regex_match(s2, std::regex(s1))) return true;
      }
      catch (std::regex_error & err)
      {
        std::ostringstream errmsg;
        errmsg << "ERROR during regex string comparison." << std::endl;
        errmsg << "  Comparing regular expression: " << s1 << std::endl;
        errmsg << "  with test string: " << s2 << std::endl;
        dependency_resolver_error().raise(LOCAL_INFO,errmsg.str());
      }
      return false;
    }

    /// Check whether type 1 (wildcard + regex allowed) matches type 2, taking into account equivalence classes.
    bool typeComp(str s1, str s2, const Utils::type_equivalency & eq)
    {
      bool match1, match2;
      // Loop over all the default versions of BOSSed backends and replace any corresponding *_default leading namespace with the explicit version.
      if ((s1.find("_default") != std::string::npos) || (s2.find("_default") != std::string::npos))
      {
        for (auto it = Backends::backendInfo().default_safe_versions.begin(); it != Backends::backendInfo().default_safe_versions.end(); ++it)
        {
          s1 = Utils::replace_leading_namespace(s1, it->first+"_default", it->first+"_"+it->second);
          s2 = Utils::replace_leading_namespace(s2, it->first+"_default", it->first+"_"+it->second);
        }
      }
      // Does it just match?
      if (stringComp(s1, s2)) return true;
      // Otherwise loop over equivalence classes.
      for (auto it1 = eq.equivalency_classes.begin(); it1 != eq.equivalency_classes.end(); it1++)
      {
        match1 = match2 = false;
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++)
        {
          // Here we use stringComp for s1 but not s2, as only s1 is allowed to have regex + wildcards.
          if (s2 == *it2) match1 = true;
          if (stringComp(s1, *it2)) match2 = true;
        }
        if (match1 and match2) return true;
      }
      return false;
    }

  }

}
