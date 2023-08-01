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
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Core/yaml_parser.hpp"
#include "gambit/Core/error_handlers.hpp"

namespace Gambit
{

  namespace IniParser
  {

    // Implementations of main inifile class

    const str IniFile::filename() const { return _filename; }

    void IniFile::readFile(std::string name)
    {

      // Store filename internally
      _filename = name;

      // Perform the basic read and parse operations defined by the parent.
      YAML::Node root = filename_to_node(_filename);
      basicParse(root,_filename);

      // Get the observables and rules sections
      YAML::Node outputNode = root["ObsLikes"];
      YAML::Node rulesNode = root["Rules"];

      // Read likelihoods and observables
      for(YAML::const_iterator it=outputNode.begin(); it!=outputNode.end(); ++it)
      {
        observables.push_back((*it).as<DRes::Observable>());
      }

      // Read rules
      for(YAML::const_iterator it=rulesNode.begin(); it!=rulesNode.end(); ++it)
      {
        // Set up a string to store any reasons given as to why the rule as
        // posed in YAML cannot be interpreted as a module rule.
        str module_rule_conversion_error;

        // Try converting the YAML rule to a module rule.
        try
        {
          module_rules.push_back(it->as<DRes::ModuleRule>());
        }
        catch(const std::runtime_error& e)
        {
          module_rule_conversion_error = e.what();
        }

        // Try converting the YAML rule to a backend rule.
        try
        {
          backend_rules.push_back(it->as<DRes::BackendRule>());
        }
        catch(const std::runtime_error& e)
        {
          if (not module_rule_conversion_error.empty())
          // Failed to convert to either a module or a backend rule.  We got a problem.
          {
            std::stringstream errmsg;
            errmsg << "Invalid entry in Rules section. The yaml snippet "<< std::endl
                   << std::endl << *it << std::endl << std::endl;
            if (module_rule_conversion_error == e.what())
            {
              // Same error in both cases. This means that it fails the general requirements of a rule.
              errmsg << "does not form a valid rule. Reason: " << std::endl << std::endl << e.what() << std::endl;
            }
            else
            {
              // The two errors differ. This means that it fails the specific requirements of each type of rule.
              errmsg << "forms neither a valid rule for module functions," << std::endl
                     << "nor a valid rule for backend functions." << std::endl << std::endl
                     << "Reason for failing as a rule for module functions: " << std::endl
                     << module_rule_conversion_error << std::endl << std::endl
                     << "Reason for failing as a rule for backend functions: " << std::endl
                     << e.what() << std::endl;
            }
            DRes::dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
          }
        }
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
    const std::vector<DRes::Observable>& IniFile::getObservables() const { return observables; }
    const std::vector<DRes::ModuleRule>& IniFile::getModuleRules() const { return module_rules; }
    const std::vector<DRes::BackendRule>& IniFile::getBackendRules() const { return backend_rules; }
    /// @}

  }

}


// Methods for converting from inifile to observable or rule format
namespace YAML
{
  using namespace Gambit::DRes;

  /// Helper function for trying to convert a YAML snippet to a nested module rule
  void convert_to_module_rule(const YAML::detail::iterator_value y, std::vector<ModuleRule>& v)
  {
    try
    {
      v.push_back(y.as<ModuleRule>());
    }
    catch(const std::runtime_error& e)
    {
      std::stringstream errmsg;
      errmsg << "Invalid entry in nested module rule contained in dependencies section. The yaml snippet "<< std::endl
             << std::endl << y << std::endl << std::endl;
      errmsg << "does not form a valid module rule. Reason: " << std::endl << std::endl << e.what() << std::endl;
      Gambit::DRes::dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
    }
  }

  /// Helper function for trying to convert a YAML snippet to a nested backend rule
  void convert_to_backend_rule(const YAML::detail::iterator_value y, std::vector<BackendRule>& v)
  {
    try
    {
      v.push_back(y.as<BackendRule>());
    }
    catch(const std::runtime_error& e)
    {
      std::stringstream errmsg;
      errmsg << "Invalid entry in nested backend rule contained in backends section. The yaml snippet "<< std::endl
             << std::endl << y << std::endl << std::endl;
      errmsg << "does not form a valid backend rule. Reason: " << std::endl << std::endl << e.what() << std::endl;
      Gambit::DRes::dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
    }
  }

  /// Convert yaml node to dependency resolver Observable type
  bool convert<Observable>::decode(const Node& node, Observable& rhs)
  {
    // Save the include_all tag if given
    if (node.Tag() == "!include_all") rhs.include_all = true;
    // Stop if any other tag has been given, as that isn't part of the current ObsLike spec.
    else if (node.Tag() != "?")
    {
      std::stringstream errmsg;
      errmsg << "The ObsLikes entry " << std::endl << node << std::endl
             << "is invalid, because it contains tag \"" << node.Tag() << "\"."
             << "The only tag permitted in ObsLikes entries is !include_all." << std::endl;
      dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
    }

    // Save the original node
    rhs.yaml = node;

    // Step through each of the entries in the node, making sure it is one of the permitted ones.
    for(auto& entry : node)
    {
      const std::string key = entry.first.as<std::string>(); 
      if      (key == "purpose")          rhs.purpose        = entry.second.as<std::string>();
      else if (key == "capability")       rhs.capability     = entry.second.as<std::string>();
      else if (key == "type")             rhs.type           = entry.second.as<std::string>();
      else if (key == "function")         rhs.function       = entry.second.as<std::string>();
      else if (key == "module")           rhs.module         = entry.second.as<std::string>();
      else if (key == "functionChain")    rhs.functionChain  = entry.second.as<std::vector<std::string>>();
      else if (key == "sub_capabilities") rhs.subcaps        = entry.second;
      else if (key == "printme")          rhs.printme        = entry.second.as<bool>();
      else if (key == "dependencies") for (auto& de : entry.second) convert_to_module_rule(de, rhs.dependencies);
      else if (key == "backends")     for (auto& be : entry.second) convert_to_backend_rule(be, rhs.backends);
      else
      {
        std::stringstream errmsg;
        errmsg << "The ObsLikes entry " << std::endl << node << std::endl
               << "is invalid, because it contains the invalid field " << entry.first << "." << std::endl;
        dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
      }
    }

    // Make sure that purpose is set
    if (rhs.purpose == "")
    {
      std::stringstream errmsg;
      errmsg << "The ObsLikes entry " << std::endl << node << std::endl
             << "is invalid, because it does not contain a \"purpose\" field." << std::endl;
      dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
    }

    // Make sure that capability, type, module or function is set. 
    if (rhs.capability == "" and rhs.type == "" and rhs.module == "" and rhs.function == "")
    {
      std::stringstream errmsg;
      errmsg << "The ObsLikes entry " << std::endl << node << std::endl
             << "is invalid, because it does not contain at least one of the" << std::endl
             << "fields \"capability\", \"type\", \"module\" or \"function\"." << std::endl;
      dependency_resolver_error().raise(LOCAL_INFO, errmsg.str());
    }

    // Strip leading "Gambit::" namespaces and whitespace, but preserve "const ".
    rhs.type = Gambit::Utils::fix_type(rhs.type);

    return true;
  }

  /// Throw an error if a yaml key is not one of those exclusively allowed in a module or backend rule.
  bool check_field_is_valid_in_derived_rule(const std::string& field)
  {
    if (not ModuleRule::permits_field(field) and not BackendRule::permits_field(field))
    {
      throw std::runtime_error(std::string("  The field \"" + field + "\" is not permitted in Rule specifications."));
    }
    return true;
  }

  /// Throw an error if a yaml key is one of those exclusively allowed in a backend rule.
  void throw_if_field_valid_only_in_backend_rule(const std::string& field)
  {
    if (BackendRule::permits_field(field))
    {
      throw std::runtime_error(std::string("  The field \"" + field + "\" is only permitted in rules for backend functions."));
    }
  }

  /// Throw an error if a yaml key is one of those exclusively allowed in a module rule.
  void throw_if_field_valid_only_in_module_rule(const std::string& field)
  {
    if (ModuleRule::permits_field(field))
    {
      throw std::runtime_error(std::string("  The field \"" + field + "\" is only permitted in rules for module functions."));
    }
  }

  /// Throw an error if a field appears in both an if and a then block
  void forbid_both_true(const std::string& field, bool is_in_one_block, bool is_in_other_block)
  {
    if (not (is_in_one_block and is_in_other_block)) return;
    throw std::runtime_error(std::string("  The field \"" + field + "\" appears in both the \"if\" and \"then\" blocks."));
  }

  /// Build the base-class parts of a rule from a yaml node
  void build_rule(const Node& node, Rule& rhs)
  {
    // Save the original node
    rhs.yaml = node;

    // Register whether rule is weak or strong
    if (node.Tag() == "!weak")
    {
      rhs.weakrule = true;
    }
    else
    {
      rhs.weakrule = false;
      // Stop if any other tag has been given, as that isn't part of the Rules spec.
      if (node.Tag() != "?")
      {
        std::stringstream errmsg;
        errmsg << "  The Rules entry " << node << "contains tag \"" << node.Tag() << "\"." << std::endl
               << "  The only tag permitted in rules is \"!weak\".";
        throw std::runtime_error(errmsg.str());
      }
    }

    // A variable for keeping track of whether there have been non-base direct fields given.
    bool contains_other_direct_fields = false;

    // Step through each of the entries in the node, making sure it is one of the permitted ones.
    for(auto& entry : node)
    {
      const std::string key = entry.first.as<std::string>(); 
      if      (key == "capability"){rhs.capability = entry.second.as<std::string>(); rhs.if_capability = true;}
      else if (key == "type")      {rhs.type = entry.second.as<std::string>(); rhs.if_type = true;}
      else if (key == "function")  {rhs.function = entry.second.as<std::string>(); rhs.then_function = true;}
      else if (key == "if")        rhs.has_if = true;
      else if (key == "then")      rhs.has_then = true;
      else contains_other_direct_fields = check_field_is_valid_in_derived_rule(key);
    }

    // Make sure that if and then either appear together or not at all
    if ((rhs.has_if and not rhs.has_then) or (rhs.has_then and not rhs.has_if))
    {
      std::string first = (rhs.has_if ? "if" : "then");
      std::string second = (rhs.has_if ? "then" : "if");
      throw std::runtime_error(std::string("  The rule contains \"" + first + "\" without \"" + second + "\"."));
    }

    // Validate if-then blocks
    if (rhs.has_if)
    {
      // Make sure that if an if-then clause is present, no other entries are.
      if (contains_other_direct_fields or not (rhs.capability.empty() and
                                               rhs.type.empty() and
                                               rhs.function.empty()))
      {
        std::stringstream errmsg;
        errmsg << "  The rule contains regular fields *and* an if-then clause. If a rule" << std::endl
               << "  contains an if-then clause, all fields of the rule must be within that clause.";
        throw std::runtime_error(errmsg.str());
      }

      // Make sure that if and then blocks are not empty
      if (node["if"].size() == 0) throw std::runtime_error(std::string("  The rule contains an empty 'if' block."));
      if (node["then"].size() == 0) throw std::runtime_error(std::string("  The rule contains an empty 'then' block."));

      // Step through each of the entries in the if node, making sure it is one of the permitted ones.
      for(auto& entry : node["if"])
      {
        const std::string key = entry.first.as<std::string>(); 
        if      (key == "capability") {rhs.capability = entry.second.as<std::string>(); rhs.if_capability = true;}
        else if (key == "type")       {rhs.type = entry.second.as<std::string>();       rhs.if_type = true;}
        else if (key == "function")   {rhs.function = entry.second.as<std::string>();   rhs.if_function = true;}
        else check_field_is_valid_in_derived_rule(key);
      }

      // Step through each of the entries in the then node, making sure it is one of the permitted ones.
      for(auto& entry : node["then"])
      {
        const std::string key = entry.first.as<std::string>(); 
        if      (key == "capability") {rhs.capability = entry.second.as<std::string>(); rhs.then_capability = true;}
        else if (key == "type")       {rhs.type = entry.second.as<std::string>();       rhs.then_type = true;}
        else if (key == "function")   {rhs.function = entry.second.as<std::string>();   rhs.then_function = true;}
        else check_field_is_valid_in_derived_rule(key);
      }

      // Make sure there are no fields common to the if and then blocks.
      forbid_both_true("capability", rhs.if_capability, rhs.then_capability);
      forbid_both_true("type", rhs.if_type, rhs.then_type);
      forbid_both_true("function", rhs.if_function, rhs.then_function);
    }

    // Strip leading "Gambit::" namespaces and whitespace, but preserve "const ".
    rhs.type = Gambit::Utils::fix_type(rhs.type);
  }

  /// Set fields exclusive to module rules that can only appear as 'then' parts of a condition
  void set_other_module_rule_fields(const YAML::detail::iterator_value& entry, ModuleRule& rhs)
  {
    const std::string key = entry.first.as<std::string>(); 
    if (key == "options")
    {
      YAML::Node node = entry.second.as<YAML::Node>();
      if (node.IsNull()) throw std::runtime_error(std::string("  The options node is empty."));
      rhs.options = node;
      rhs.then_options = true;
    }
    else if (key == "functionChain")
    {
      rhs.functionChain = entry.second.as<std::vector<std::string>>();
      rhs.then_functionChain = true;
    }
    else if (key == "dependencies")
    {
      for (auto& dependencies_entry : entry.second)
      {
        // Try converting the entry to a module rule.
        convert_to_module_rule(dependencies_entry, rhs.dependencies);
        rhs.then_dependencies = true;
      }
    }
    else if (key == "backends")
    {
      for (auto& backends_entry : entry.second)
      {
        // Try converting the entry to a backend rule.
        convert_to_backend_rule(backends_entry, rhs.backends);
        rhs.then_backends = true;
      }
    }
    else throw_if_field_valid_only_in_backend_rule(key);
  }

  /// Convert yaml node to dependency resolver ModuleRule type
  bool convert<ModuleRule>::decode(const Node& node, ModuleRule& rhs)
  {
    // Build the generic base-class parts of the rule
    build_rule(node, rhs);

    // Step through each of the entries in the node, making sure it is one of the permitted ones.
    for(auto& entry : node)
    {
      const std::string key = entry.first.as<std::string>(); 
      if (key == "module")
      {
        rhs.module = entry.second.as<std::string>(); 
        rhs.then_module = true;
      }
      else set_other_module_rule_fields(entry, rhs);
    }

    // Validate if-then blocks
    if (rhs.has_if)
    {
      // Step through each of the entries in the if node, making sure it is one of the permitted ones.
      for(auto& entry : node["if"])
      {
        const std::string key = entry.first.as<std::string>();
        if (key == "module")
        {
          rhs.module = entry.second.as<std::string>();
          rhs.if_module = true;
        }
        else if (key == "functionChain" or
                 key == "options"       or
                 key == "dependencies"  or
                 key == "backends")
        {
          throw std::runtime_error(std::string("  The field \"" + key + "\" cannot appear in an \"if\" block."));
        }
        else throw_if_field_valid_only_in_backend_rule(key);
      }

      // Step through each of the entries in the then node, making sure it is one of the permitted ones.
      for(auto& entry : node["then"])
      {
        if (entry.first.as<std::string>() == "module")
        {
          rhs.module = entry.second.as<std::string>(); 
          rhs.then_module = true;
        }
        else set_other_module_rule_fields(entry, rhs);
      }

      // Make sure that module does not appear in both if and then blocks.
      forbid_both_true("module", rhs.if_module, rhs.then_module);
    }
    // If there is no explicit if-then, make sure the default 'if' and 'then' conditions are actually implemented
    else
    {
      if (not (rhs.if_capability or rhs.if_type))
      {
        std::stringstream errmsg;
        errmsg << "  The rule contains neither an if-then block nor any capability or" << std::endl
               << "  type entry able to be interpreted as an implicit if condition.";
        throw std::runtime_error(errmsg.str());
      }
      if (not (rhs.then_function or
               rhs.then_module or
               rhs.then_options or
               rhs.then_functionChain or
               rhs.then_dependencies or
               rhs.then_backends))
      {
        std::stringstream errmsg;
        errmsg << "  The rule contains neither an if-then block nor an entry" << std::endl
               << "  able to be interpreted as an implicit then condition.";
        throw std::runtime_error(errmsg.str());
      }
    }

    return true;
  }

  /// Convert yaml node to dependency resolver BackendRule type
  bool convert<BackendRule>::decode(const Node& node, BackendRule& rhs)
  {
    // Build the generic base-class parts of the rule
    build_rule(node, rhs);

    // Step through each of the entries in the node, making sure it is one of the permitted ones.
    for(auto& entry : node)
    {
      const std::string key = entry.first.as<std::string>();
      if (key == "version")
      {
        rhs.version = entry.second.as<std::string>(); 
        rhs.then_version = true;
      }
      else if (key == "backend")
      {
        rhs.backend = entry.second.as<std::string>(); 
        rhs.then_backend = true;
      }
      else if (key == "group")
      {
        rhs.group = entry.second.as<std::string>(); 
        rhs.if_group = true;
        // Given that there is a group keyword, re-interpret capability (if it is outside an if block) as a then condition. 
        if (not rhs.has_if and rhs.if_capability)
        {
          rhs.if_capability = false;
          rhs.then_capability = true;
        }
      } 
      else throw_if_field_valid_only_in_module_rule(key);
    }

    // Validate if-then blocks
    if (rhs.has_if)
    {
      // Step through each of the entries in the if node, making sure it is one of the permitted ones.
      for(auto& entry : node["if"])
      {
        const std::string key = entry.first.as<std::string>();
        if (key == "version")
        {
          rhs.version = entry.second.as<std::string>(); 
          rhs.if_version = true;
        }
        else if (key == "backend")
        {
          rhs.backend = entry.second.as<std::string>(); 
          rhs.if_backend = true;
        }
        else if (key == "group")
        {
          rhs.group = entry.second.as<std::string>(); 
          rhs.if_group = true;
        }
        else throw_if_field_valid_only_in_module_rule(key);
      }

      // Step through each of the entries in the then node, making sure it is one of the permitted ones.
      for(auto& entry : node["then"])
      {
        const std::string key = entry.first.as<std::string>();
        if (key == "version")
        {
          rhs.version = entry.second.as<std::string>(); 
          rhs.then_version = true;
        }
        else if (key == "backend")
        {
          rhs.backend = entry.second.as<std::string>(); 
          rhs.then_backend = true;
        }
        else if (key == "group")
        {
          throw std::runtime_error(std::string("  The field \"" + key + "\" cannot appear in a \"then\" block."));
        }
        else throw_if_field_valid_only_in_module_rule(key);
      }

      // Make sure that version and backend do not appear in both if and then blocks.
      forbid_both_true("version", rhs.if_version, rhs.then_version);
      forbid_both_true("backend", rhs.if_backend, rhs.then_backend);
    }
    // If there is no explicit if-then, make sure the default 'then' condition is actually implemented
    else
    {
      if (not (rhs.if_capability or rhs.if_type or rhs.if_group))
      {
        std::stringstream errmsg;
        errmsg << "  The rule contains neither an if-then block nor any capability entry" << std::endl
               << "  able to be interpreted as an implicit if condition.";
        throw std::runtime_error(errmsg.str());
      }
      if (not (rhs.then_function or rhs.then_version or rhs.then_backend or rhs.then_capability))
      {
        std::stringstream errmsg;
        errmsg << "  The rule contains neither an if-then block, nor an entry able to be" << std::endl
               << "  interpreted as an implicit then condition." << std::endl;
        if (rhs.if_capability)
        {
          errmsg << std::endl
                 << "  Note that \"capability\" has already been implicitly interpreted as an if" << std::endl
                 << "  condition.  Interpreting it as a then condition requires the presence of the" << std::endl
                 << "  \"group\" keyword, which implicitly takes over the role of the if condition." << std::endl;
        }
        throw std::runtime_error(errmsg.str());
      }
    }

    return true;
  }


}
