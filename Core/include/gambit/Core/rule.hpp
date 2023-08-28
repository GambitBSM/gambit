//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class for holding a rule to be applied during
///  dependency resolution.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2022 Nov
///
///  *********************************************

#pragma once

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Elements/type_equivalency.hpp"


namespace Gambit
{

  /// Forward declaration of functor class
  class functor;

  namespace DRes
  {

    /// Base rule for resolution of dependencies and backend requirements.
    struct Rule
    {

      /// Rule has an antecedent ('if' clause)
      bool has_if;
      /// Rule has a consequent ('then' clause)
      bool has_then;

      /// The original YAML (if any) from which this rule was derived.
      YAML::Node yaml;

      /// Capability field targeted by the rule.
      std::string capability;
      /// Capability field appears in 'if' clause.
      bool if_capability;
      /// Capability field appears in 'then' clause.
      bool then_capability;

      /// Type field targeted by the rule.
      std::string type;
      /// Type field appears in 'if' clause.
      bool if_type;
      /// Type field appears in 'then' clause.
      bool then_type;

      /// Function field targeted by the rule.
      std::string function;
      /// Function field appears in 'if' clause.
      bool if_function;
      /// Function field appears in 'then' clause.
      bool then_function;

      /// Indicates that rule can be broken
      bool weakrule;
      
      /// Whether or not to log matches to the rule with functors
      bool log_matches;

      /// True if and only if the passed functor matches the 'if' part of a rule
      bool base_antecedent_matches(functor*, const Utils::type_equivalency&) const;

      /// True if and only if the passed functor matches the 'then' part of a rule
      bool base_consequent_matches(functor*, const Utils::type_equivalency&) const;

      ///Default constructor. Sets all fields empty.
      Rule():
        has_if(false),
        has_then(false),
        capability(),
        if_capability(false),
        then_capability(false),
        type(),
        if_type(false),
        then_type(false),
        function(),
        if_function(false),
        then_function(false),
        weakrule(false),
        log_matches(true)
      {}

    };

    /// Derived class rule for resolution of backend requirements.
    struct BackendRule : public Rule
    {

      /// Version field targeted by the rule.
      std::string version;
      /// Version field appears in 'if' clause.
      bool if_version;
      /// Version field appears in 'then' clause.
      bool then_version;

      /// Backend field targeted by the rule.
      std::string backend;
      /// Backend field appears in 'if' clause.
      bool if_backend;
      /// Backend field appears in 'then' clause.
      bool then_backend;

      /// Backend group referenced by the rule.
      std::string group;
      /// Group field appears in 'if' clause.
      bool if_group;

      /// True if and only if the passed backend functor matches the 'if' part of a rule
      bool antecedent_matches(functor*, const Utils::type_equivalency&, const str&) const;

      /// True if and only if the passed backend functor matches the 'then' part of a rule
      bool consequent_matches(functor*, const Utils::type_equivalency&) const;

      /// Whether a backend rule allows a given backend functor or not.  
      /// Must be true for a backend functor to be used to resolve a backend requirement.   
      /// True unless the functor passes the antecedent ('if' part of the rule) but fails the consequent ('then' part of the rule). 
      bool allows(functor*, const Utils::type_equivalency&, const str&, bool ignore_if_weak = true) const;
      
      ///Default constructor. Sets all fields empty.
      BackendRule():
        Rule(),
        version(),
        if_version(false),
        then_version(false),
        backend(),
        if_backend(false),
        then_backend(false),
        group(),
        if_group(false)
      {}

      /// Check if a given string is a permitted field of this class
      static bool permits_field(const str&);

    };

    /// Derived class rule for resolution of dependencies.
    struct ModuleRule : public Rule
    {

      /// Module field targeted by the rule.
      std::string module;
      /// Module field appears in 'if' clause.
      bool if_module;
      /// Module field appears in 'then' clause.
      bool then_module;

      /// Options provided by the rule.
      Options options;
      /// Options appear in 'then' clause.
      bool then_options;

      /// Subjugate dependency rules provided by the rule.
      std::vector<ModuleRule> dependencies;
      /// Subjugate dependency rules appear in 'then' clause.
      bool then_dependencies;

      /// Subjugate backend rules provided by the rule.
      std::vector<BackendRule> backends;
      /// Subjugate backend rules appear in 'then' clause.
      bool then_backends;

      /// Function chain provided by the rule.
      std::vector<std::string> functionChain;
      /// Function chain appears in the 'then' clause.
      bool then_functionChain;

      /// True if and only if the passed module functor matches the 'if' part of a rule
      bool antecedent_matches(functor*, const Utils::type_equivalency&) const;

      /// True if and only if the passed module functor matches the 'then' part of a rule
      bool consequent_matches(functor*, const Utils::type_equivalency&) const;

      /// Whether a module rule allows a given module functor or not.  
      /// Must be true for a module functor to be used to resolve a dependency.   
      /// True unless the functor passes the antecedent ('if' part of the rule) but fails the consequent ('then' part of the rule). 
      bool allows(functor*, const Utils::type_equivalency&, bool ignore_if_weak = true) const;

      /// Whether the set of dependency rules subjugate to this rule allow a given module functor or not. 
      /// Must be true for the passed module functor to be used to resolve a dependency of another module functor that matches this rule (the dependee).
      /// Does not test if the dependee actually matches the rule, so should typically only be used after confirming this first.
      bool dependencies_allow(functor*, const Utils::type_equivalency&, bool ignore_if_weak = true) const;

      /// Whether the functionChain of this rule allow a given module functor to be used to resolve the dependency of another. 
      /// Does not test if the dependent functor actually matches the rule, so should typically only be used after confirming this first.
      bool function_chain_allows(functor*, functor*, const Utils::type_equivalency&, bool ignore_if_weak = true) const;

      /// Whether the set of backend rules subjugate to this rule allow a given backend functor or not. 
      /// Must be true for the passed backend functor to be used to resolve a backend requirement of another module functor that matches this rule (the requiree).
      /// Does not test if the requiree actually matches the rule, so should typically only be used after confirming this first.
      bool backend_reqs_allow(functor*, const Utils::type_equivalency&, const str&, bool ignore_if_weak = true) const;

      ///Default constructor. Sets all fields empty.
      ModuleRule():
        Rule(),
        module(),
        if_module(false),
        then_module(false),
        options(),
        then_options(false),
        dependencies(),
        then_dependencies(false),
        backends(),
        then_backends(false),
        functionChain(),
        then_functionChain(false)
      {}

      /// Check if a given string is a permitted field of this class
      static bool permits_field(const str&);

    };

  }
}
