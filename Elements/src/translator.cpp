//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementations for translator class, a simple
///  container for storing and looking up equivalent
///  terms in an arbitrary number of languages
///  using YAML.
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

#include <algorithm>

#include "yaml-cpp/yaml.h"

#include "gambit/Elements/translator.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

namespace Gambit
{
  namespace Utils
  {

    /// Constructor for translator
    translator::translator(const str& filename)
    {
      // Read yaml configuration file
      std::vector<YAML::Node> yaml_entries;
      try
      {
        yaml_entries = YAML::LoadAllFromFile(filename);
      }
      catch (YAML::Exception &e)
      {
        std::ostringstream msg;
        msg << "Could not read translation file \""<<filename<<"\"!" << endl;
        msg << "Please check that file exists and contains valid YAML." << endl;
        msg << "("<<e.what()<<")";
        utils_error().raise(LOCAL_INFO, msg.str());
      }

      // Save the languages
      languages = yaml_entries.begin()->as<std::vector<str>>();

      // Create vector for each language
      for (auto lang : languages) rosetta[lang] = std::vector<str>();

      // Iterate over the entries in the translation file and add them to the set of equivalency classes
      for (auto it = yaml_entries.begin() + 1; it != yaml_entries.end(); ++it)
      {
        std::vector<str> row = it->as<std::vector<str>>();
        if (row.size() != languages.size())
        {
          std::ostringstream msg;
          msg << "Row in \""<<filename<<"\" has " << (row.size() < languages.size() ? "less" : "more") << " entries than there are column headings." << endl;
          msg << "Please fix the file." << endl;
          utils_error().raise(LOCAL_INFO,msg.str());
        }
        for (unsigned int i = 0; i != row.size(); i++)
        {
          rosetta.at(languages[i]).push_back(row[i]);
        }

      }
    }

    /// Translate terms from one language to another.
    str translator::operator()(const str& from, const str& to, const str& obs)
    {
      auto from_lang = rosetta.find(from);
      auto to_lang = rosetta.find(to);
      if (from_lang == rosetta.end()) utils_error().raise(LOCAL_INFO, from + str(" not a language recognised by translator."));
      if (to_lang == rosetta.end()) utils_error().raise(LOCAL_INFO, to + str(" not a language recognised by translator."));
      auto it = std::find(from_lang->second.begin(), from_lang->second.end(), obs);
      if (it == from_lang->second.end()) utils_error().raise(LOCAL_INFO, obs + str(" not found by translator in language " + from));
      return to_lang->second.at(it - from_lang->second.begin());
    }

    /// Translate terms from one language to another and add a suffix
    str translator::operator()(const str& from, const str& to, const str& obs, const str& suffix) { return operator()(from, to, obs) + suffix; }

    /// Translate terms from one language to another.
    std::vector<str> translator::operator()(const str& from, const str& to, const std::vector<str>& obs) { return operator()(from, to, obs, ""); }

    /// Translate terms from one language to another and add a suffix
    std::vector<str> translator::operator()(const str& from, const str& to, const std::vector<str>& obs, const str& suffix)
    {
      std::vector<str> result;
      for (auto o : obs) result.push_back(operator()(from, to, o, suffix));
      return result;
    }

  }
}