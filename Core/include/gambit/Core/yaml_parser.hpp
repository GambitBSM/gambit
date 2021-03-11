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

        /// Read in the YAML file
        virtual void readFile(str filename);

        /// Getters for private observable and rules entries
        /// @{
        const ObservablesType & getObservables() const;
        const ObservablesType & getRules() const;
        /// @}

      private:
        ObservablesType observables;
        ObservablesType rules;

    };


  }

}


// Rules for inifile --> Structs mapping
namespace YAML
{
 
  using namespace Gambit::IniParser::Types;
  
  template<> struct convert<Observable>
  {
    static bool decode(const Node& node, Observable& rhs)
    {
      #define READ(NAME) \
      if (node[#NAME].IsDefined()) \
        rhs.NAME = node[#NAME].as<std::string>();

      READ(purpose)
      READ(capability)
      READ(type)
      READ(function)
      READ(module)
      READ(backend)
      READ(version)

      if (node.Tag() == "!weak" or node.Tag() == "!weakrule") 
        rhs.weakrule = true;
      else 
        rhs.weakrule = false;

      // Strip leading "Gambit::" namespaces and whitespace, but preserve
      // "const ".
      rhs.type = Gambit::Utils::fix_type(rhs.type);
      
      if (node["printme"].IsDefined())
          rhs.printme = node["printme"].as<bool>();

      if (node["options"].IsDefined())
          rhs.options = Gambit::Options(node["options"]);
      #undef READ
      if (node["functionChain"].IsDefined())
          rhs.functionChain = node["functionChain"].as<std::vector<std::string>>();
      for(YAML::const_iterator it=node["dependencies"].begin();
          it!=node["dependencies"].end(); ++it)
      {
        rhs.dependencies.push_back((*it).as<Observable>());
      }
      for(YAML::const_iterator it=node["backends"].begin();
          it!=node["backends"].end(); ++it)
      {
        rhs.backends.push_back((*it).as<Observable>());
      }
      return true;
    }
  };

}


#endif /* defined(__yaml_parser_hpp__) */
