//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base class for ini-file parsers using yaml-cpp
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 June 2013
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
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2020 May
///
///  *********************************************

#ifndef __yaml_parser_base_hpp__
#define __yaml_parser_base_hpp__

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include "yaml-cpp/yaml.h"
#include <limits>


namespace Gambit
{

  namespace IniParser
  {

    /// Inifile parser base class
    class Parser
    {

      public:

        /// Read in the YAML file
        virtual void readFile(str filename);

        /// Getters for key/value section
        /// @{
        YAML::Node getParametersNode() const;
        YAML::Node getPriorsNode() const;
        YAML::Node getPrinterNode() const;
        YAML::Node getScannerNode() const;
        YAML::Node getLoggerNode() const;
        YAML::Node getKeyValuePairNode() const;
        
        template <typename... args>
        bool hasKey(args... keys) const
        {
          return getVariadicNode(keyValuePairNode, keys...);
        }

        template<typename TYPE, typename... args> TYPE getValue(args... keys) const
        {
          const YAML::Node node = getVariadicNode(keyValuePairNode, keys...);
          if (not node) inifile_error().raise(LOCAL_INFO,"No inifile entry for [" + stringifyVariadic(keys...) + "]");
          return NodeUtility::getNode<TYPE>(node);
        }

        template<typename TYPE, typename... args> TYPE getValueOrDef(TYPE def, const args&... keys) const
        {
          const YAML::Node node = getVariadicNode(keyValuePairNode, keys...);
          if (not node)
          {
              return def;
          }
          return NodeUtility::getNode<TYPE>(node);
        }
        /// @}

        /// Getters for model/parameter section
        /// @{
        template<typename TYPE> TYPE getModelParameterEntry(str model, str param, str key) const
        {
          if (not parametersNode[model][param][key]) inifile_error().raise(LOCAL_INFO,model + "." + param + "." + key + "not found in inifile.");
          return parametersNode[model][param][key].as<TYPE>();
        }
        bool hasModelParameterEntry(str model, str param, str key) const;
        /// Return list of model names (without "adhoc" model!)
        const std::set<str> getModelNames() const;
        const std::vector<str> getModelParameters(str model) const;
        /// @}

        /// Getter for options
        const Options getOptions(str key) const;

     protected:

        /// Read in the actual YAML file
        YAML::Node filename_to_node(str);
        
        /// Do the basic parsing of the YAML file
        void basicParse(YAML::Node,str);
         
      private:     

        YAML::Node keyValuePairNode;
        YAML::Node parametersNode;
        YAML::Node priorsNode;
        YAML::Node printerNode;
        YAML::Node scannerNode;
        YAML::Node logNode;
    };


  }

}

#endif /* defined(__yaml_parser_base_hpp__) */
