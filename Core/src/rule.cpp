//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function implementations for rule classes.
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

#include "gambit/Core/rule.hpp"
#include "gambit/Core/error_handlers.hpp"
#include "gambit/Core/resolution_utilities.hpp"
#include "gambit/Elements/functors.hpp"

namespace Gambit
{

  namespace DRes
  {

    /// True if and only if the passed functor matches the base part of an 'if' part of a rule 
    bool Rule::base_antecedent_matches(functor* f, const Utils::type_equivalency& te) const
    {
      bool match = true;
      if (match and if_capability) match = stringComp(capability, f->capability()   ); 
      if (match and if_type)       match = typeComp  (type,       f->type(),      te); 
      if (match and if_function)   match = stringComp(function,   f->name()         ); 
      return match;
    }

    /// True if and only if the passed functor matches the base part of a 'then' part of a rule 
    bool Rule::base_consequent_matches(functor* f, const Utils::type_equivalency& te) const
    {
      bool match = true;
      if (match and then_capability) match = stringComp(capability, f->capability()   ); 
      if (match and then_type)       match = typeComp  (type,       f->type(),      te); 
      if (match and then_function)   match = stringComp(function,   f->name()         ); 
      return match;
    }

    /// Check if a given string is a permitted field of the BackendRule class
    bool BackendRule::permits_field(const str& field)
    {
      static const std::set<str> fields =
      {
        "version",
        "backend",
        "group"
      };
      return (fields.find(field) != fields.end());
    }

    /// True if and only if the passed backend functor matches the 'if' part of a rule
    bool BackendRule::antecedent_matches(functor* f, const Utils::type_equivalency& te, const str& group_being_resolved) const
    {
      // Allow matching only if the antecedent has been properly specified.
      bool match = if_capability or if_type or if_function or if_version or if_backend or if_group;
      // Check if the base class part of the antecedent was matched.
      match = match and base_antecedent_matches(f, te);
      // Check if the derived class part of the antecedent was matched.
      if (match and if_version) match = stringComp(version, f->version()); 
      if (match and if_backend) match = stringComp(backend, f->origin()); 
      if (match and if_group)   match = stringComp(group, group_being_resolved); 
      return match;
    }

    /// True if and only if the passed backend functor matches the 'then' part of a rule
    bool BackendRule::consequent_matches(functor* f, const Utils::type_equivalency& te) const
    {
      // Allow matching only if the consequent has been properly specified.
      bool match = then_capability or then_type or then_function or then_version or then_backend;
      // Check if the base class part of the consequent was matched.
      match = match and base_consequent_matches(f, te);
      // Check if the derived class part of the consequent was matched.
      if (match and then_version) match = stringComp(version, f->version()); 
      if (match and then_backend) match = stringComp(backend, f->origin()); 
      // Log match
      if (match and log_matches) f->addMatchedBackendRule(this);
      return match;
    }

    /// Whether a backend rule allows a given backend functor or not.  
    /// Must be true for a backend functor to be used to resolve a backend requirement.   
    /// True unless the functor passes the antecedent ('if' part of the rule) but fails the consequent ('then' part of the rule). 
    bool BackendRule::allows(functor* f, const Utils::type_equivalency& te, const str& group_being_resolved, bool ignore_if_weak) const
    {
      if (ignore_if_weak and weakrule) return true;
      if (not antecedent_matches(f, te, group_being_resolved)) return true;
      bool result = consequent_matches(f, te);
      return result;
    }

    /// Check if a given string is a permitted field of the ModuleRule class
    bool ModuleRule::permits_field(const str& field)
    {
      static const std::set<str> fields =
      {
        "module",
        "options",
        "dependencies",
        "backends",
        "functionChain"
      };
      return (fields.find(field) != fields.end());
    }

    /// True if and only if the passed module functor matches the 'if' part of a rule
    bool ModuleRule::antecedent_matches(functor* f, const Utils::type_equivalency& te) const
    {
      // Allow matching only if the antecedent has been properly specified.
      bool match = if_capability or if_type or if_function or if_module;
      // Check if the base class part of the antecedent was matched.
      match = match and base_antecedent_matches(f, te);
      // Check if the derived class part of the antecedent was matched.
      if (match and if_module) match = stringComp(module, f->origin()); 
      return match;
    }

    /// True if and only if the passed module functor matches the 'then' part of a rule
    bool ModuleRule::consequent_matches(functor* f, const Utils::type_equivalency& te) const
    {
      // Allow matching only if the consequent has been properly specified.
      bool match = then_capability or then_type or then_function or then_module or
                   then_options or then_dependencies or then_backends or then_functionChain;
      // Check if the base class part of the consequent was matched.
      match = match and base_consequent_matches(f, te);
      // Check if the derived class part of the consequent was matched.
      if (match and then_module) match = stringComp(module, f->origin()); 
      // Log match
      if (match and log_matches) f->addMatchedModuleRule(this);
      return match;
    }

    /// Whether a module rule allows a given module functor or not.  
    /// Must be true for a module functor to be used to resolve a dependency.   
    /// True unless the functor passes the antecedent ('if' part of the rule) but fails the consequent ('then' part of the rule). 
    bool ModuleRule::allows(functor* f, const Utils::type_equivalency& te, bool ignore_if_weak) const
    {
      if (ignore_if_weak and weakrule) return true;
      if (not antecedent_matches(f, te)) return true;
      bool result = consequent_matches(f, te);
      return result;
    }

    /// Whether the set of dependency rules subjugate to this rule allow a given module functor or not. 
    bool ModuleRule::dependencies_allow(functor* f, const Utils::type_equivalency& te, bool ignore_if_weak) const
    {
      if (ignore_if_weak and weakrule) return true;
      bool allow = true;
      for (const ModuleRule& rule : dependencies) allow = allow and rule.allows(f, te, ignore_if_weak);
      return allow;      
    }

    /// Whether the functionChain of this rule allows a given module functor to be used to resolve the dependency of another. 
    bool ModuleRule::function_chain_allows(functor* candidate, functor* dependee, const Utils::type_equivalency& te, bool ignore_if_weak) const
    {
      // Scenarios in which the functionChain is irrelevent.
      if (ignore_if_weak and weakrule) return true;
      if (not then_functionChain) return true;
      if (not stringComp(capability, candidate->capability()) and not typeComp(type, candidate->type(), te)) return true;
      // If the dependee matches the rule, then the candidate is allowed only if it appears at the start of the function chain.
      if (antecedent_matches(dependee, te) and consequent_matches(dependee, te)) return (*functionChain.begin() == candidate->name());
      // Iterate over the entries in the functionChain
      for (auto it = functionChain.begin(); it != functionChain.end() - 1; ++it)
      {
        // Function is allowed if somewhere in the chain it is directly preceeded by the dependent function.
        if ((*it) == dependee->name()) return (*(it+1) == candidate->name());
      }
      return true;
    }

    /// Whether the set of backend rules subjugate to this rule allow a given backend functor or not. 
    bool ModuleRule::backend_reqs_allow(functor* f, const Utils::type_equivalency& te, const str& group_being_resolved, bool ignore_if_weak) const
    {
      if (ignore_if_weak and weakrule) return true;
      bool allow = true;
      for (const BackendRule& rule : backends) allow = allow and rule.allows(f, te, group_being_resolved, ignore_if_weak);
      return allow;      
    }

  }

}
