//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function implementations for observable class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2022 Dec
///
///  *********************************************

#include "gambit/Core/observable.hpp"
#include "gambit/Core/resolution_utilities.hpp"
#include "gambit/Elements/functors.hpp"
#include "gambit/Elements/type_equivalency.hpp"

namespace Gambit
{

  namespace DRes
  {

    /// True if and only if the passed functor matches all matchable non-empty fields of the observable (i.e. everything except purpose, dependencies, backend_reqs, functionChain and subcaps).
    bool Observable::matches(functor* f, const Utils::type_equivalency& te) const
    {
      bool m = stringComp ( capability, f->capability()     ) and
               typeComp   ( type,       f->type()      , te ) and
               stringComp ( function,   f->name()           ) and
               stringComp ( module,     f->origin()         );
      if (m and log_matches) f->addMatchedObservable(this);
      return m;
    }

    /// Whether the set of dependency rules subjugate to this observable allow a given module functor or not. 
    bool Observable::dependencies_allow(functor* f, const Utils::type_equivalency& te, bool ignore_if_weak) const
    {
      bool allow = true;
      for (const ModuleRule& rule : dependencies) allow = allow and rule.allows(f, te, ignore_if_weak);
      return allow;      
    }

    /// Whether the functionChain of this observable allows a given module functor to be used to resolve the dependency of another. 
    bool Observable::function_chain_allows(functor* candidate, functor* dependee, const Utils::type_equivalency& te) const
    {
      // If the functionChain is empty, the candidate is allowed
      if (functionChain.empty()) return true;
      // If the candidate functor doesn't also match the capability and type of the observable, then the functionChain is not relevant.
      if (not stringComp(capability, candidate->capability()) or 
          not typeComp(type, candidate->type(), te)) return true;
      // If the dependee matches the observable, then the candidate is allowed only if it appears at the start of the function chain.
      if (matches(dependee, te)) return (*functionChain.begin() == candidate->name());
      // Iterate over the entries in the functionChain
      for (auto it = functionChain.begin(); it != functionChain.end() - 1; ++it)
      {
        // Function is allowed if somewhere in the chain it is directly preceded by the dependent function.
        if ((*it) == dependee->name()) return (*(it+1) == candidate->name());
      }
      return true;
    }

    /// Whether the set of backend rules subjugate to this observable allow a given backend functor or not. 
    bool Observable::backend_reqs_allow(functor* f, const Utils::type_equivalency& te, const str& group_being_resolved, bool ignore_if_weak) const
    {
      bool allow = true;
      for (const BackendRule& rule : backends) allow = allow and rule.allows(f, te, group_being_resolved, ignore_if_weak);
      return allow;      
    }

  }

}
