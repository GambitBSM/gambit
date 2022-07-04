//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Ini-file parser based on yaml-cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 June
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2014 Feb
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///  \date 2015 Mar
///  \date 2020 Apr
///
///  *********************************************

#ifndef __yaml_parser_hpp__
#define __yaml_parser_hpp__

#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Elements/type_equivalency.hpp"

#include "yaml-cpp/yaml.h"


namespace Gambit
{

  namespace IniParser
  {

    namespace Types
    {

      // Dependency and Observable have the same type (and purpose entry is
      // irrelevant for dependencies)
      struct Observable
      {
        std::string purpose;
        std::string capability;
        std::string type;
        std::string function;
        std::string module;
        std::string backend;
        std::string version;
        bool printme; // Instruction to printer as to whether to write result to disk
        bool weakrule;  // Indicates that rule can be broken
        Options options;
        YAML::Node subcaps;
        std::vector<Observable> dependencies;
        std::vector<Observable> backends;
        std::vector<std::string> functionChain;

        ///Default constructor, to ensure the default values are not gibberish
        Observable():
          purpose(),
          capability(),
          type(),
          function(),
          module(),
          backend(),
          version(),
          printme(true),
          options(),
          subcaps(),
          dependencies(),
          backends(),
          functionChain()
        {}
      };

    }

    typedef Types::Observable ObservableType;
    typedef std::vector<ObservableType> ObservablesType;

    /// Main inifile class
    class IniFile : public Parser
    {

      public:

        // Return the filename
        const str filename() const;

        /// Read in the YAML file
        virtual void readFile(str);

        /// Getters for private observable and rules entries
        /// @{
        const ObservablesType & getObservables() const;
        const ObservablesType & getRules() const;
        /// @}

      private:

        str _filename;

        ObservablesType observables;
        ObservablesType rules;

    };


  }

}


// Rules for inifile --> Observable mapping
namespace YAML
{
  template<>
  struct convert<Gambit::IniParser::Types::Observable>
  {
    static bool decode(const Node&, Gambit::IniParser::Types::Observable&);
  };
}


#endif /* defined(__yaml_parser_hpp__) */
