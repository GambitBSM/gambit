//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple container for storing and looking up
///  equivalent terms in an arbitrary number of
///  languages, using YAML.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Feb
///
///  *********************************************

#include <map>
#include <vector>

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  namespace Utils
  {

    class translator
    {

      private:

        /// Set of supported languages
        std::vector<str> languages;

        /// Actual database of terms
        std::map<str, std::vector<str>> rosetta;

      public:

        /// Constructor for translator
        translator(const str& filename_);

        /// Translate terms from one language to another.
        /// @{
        str operator()(const str& from, const str& to, const str& obs);
        str operator()(const str& from, const str& to, const str& obs, const str& suffix);
        std::vector<str> operator()(const str& from, const str& to, const std::vector<str>& obs);
        std::vector<str> operator()(const str& from, const str& to, const std::vector<str>& obs, const str& suffix);
        /// @}

    };


  }
}