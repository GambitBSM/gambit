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
///  \date 2013 May, June, July
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///  \date 2015 Mar
///
///  *********************************************

#include "gambit/Core/yaml_parser.hpp"

namespace Gambit
{

  namespace IniParser
  {

    // Implementations of main inifile class

    void IniFile::readFile(std::string filename)
    {

      // Perform the basic read and parse operations defined by the parent.
      YAML::Node root = filename_to_node(filename);
      basicParse(root,filename);
      
      // Get the observables and rules sections
      YAML::Node outputNode = root["ObsLikes"];
      YAML::Node rulesNode = root["Rules"];

      // Read likelihood/observables
      for(YAML::const_iterator it=outputNode.begin(); it!=outputNode.end(); ++it)
      {
        observables.push_back((*it).as<Types::Observable>());
      }

      // Read rules
      for(YAML::const_iterator it=rulesNode.begin(); it!=rulesNode.end(); ++it)
      {
        rules.push_back((*it).as<Types::Observable>());
      }

      // Read KeyValue section, find the default path entry, and pass this on
      // to the Scanner, Logger, and Printer nodes
      YAML::Node keyvalue    = getKeyValuePairNode();
      YAML::Node scanNode    = getScannerNode();
      YAML::Node printerNode = getPrinterNode();
      YAML::Node logNode     = getLoggerNode();

    }

    /// Getters for private observable and rules entries
    /// @{
    const ObservablesType& IniFile::getObservables() const { return observables; }
    const ObservablesType& IniFile::getRules() const { return rules; }
    /// @}

  }

}
