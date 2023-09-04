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
///  \date 2022 Nov
///
///  *********************************************

#pragma once

#include "gambit/Core/observable.hpp"
#include "gambit/Core/rule.hpp"
#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "yaml-cpp/yaml.h"


namespace Gambit
{

  namespace IniParser
  {

    /// Main inifile class
    class IniFile : public Parser
    {

      public:

        /// Return the filename
        const str filename() const;

        /// Read in the YAML file
        virtual void readFile(str);

        /// Getters for private observable and rules entries
        /// @{
        const std::vector<DRes::Observable>& getObservables() const;
        const std::vector<DRes::ModuleRule>& getModuleRules() const;
        const std::vector<DRes::BackendRule>& getBackendRules() const;
        /// @}

      private:

        str _filename;
        std::vector<DRes::Observable> observables;
        std::vector<DRes::ModuleRule> module_rules;
        std::vector<DRes::BackendRule> backend_rules;

    };

  }

}


namespace YAML
{

  /// Rules for inifile --> observable/rule mapping
  /// @{

  template<>
  struct convert<Gambit::DRes::Observable>
  {
    static bool decode(const Node&, Gambit::DRes::Observable&);
  };

  template<>
  struct convert<Gambit::DRes::ModuleRule>
  {
    static bool decode(const Node&, Gambit::DRes::ModuleRule&);
  };

  template<>
  struct convert<Gambit::DRes::BackendRule>
  {
    static bool decode(const Node&, Gambit::DRes::BackendRule&);
  };

  /// @}

}
