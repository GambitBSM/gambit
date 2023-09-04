//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Observable class for holding ObsLike entries.
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

#include "gambit/Core/rule.hpp"

#include "yaml-cpp/yaml.h"


namespace Gambit
{

  /// Forward declaration of functor class
  class functor;

  namespace DRes
  {

    struct Observable
    {
      /// The original YAML (if any) from which this observable was derived.
      YAML::Node yaml;
 
      /// Designated purpose of the observable (LogLike, etc).
      std::string purpose;

      /// Capability field targeted by the ObsLike entry.
      std::string capability;

      /// Type field targeted by the ObsLike entry.
      std::string type;

      /// Function field targeted by the ObsLike entry.
      std::string function;

      /// Module targeted by the ObsLike entry.
      std::string module;

      /// Subjugate dependency rules to be assigned to the observable.
      std::vector<ModuleRule> dependencies;

      /// Subjugate backend rules to be assigned to the observable.
      std::vector<BackendRule> backends;

      /// Function chain to be assigned to the observable.
      std::vector<std::string> functionChain;

      /// Sub-capabilities to be assigned to the observable.
      YAML::Node subcaps;

      /// Instruction to printer as to whether to write result to disk.
      bool printme;

      /// Whether or not to log matches to the observable with functors.
      bool log_matches;

      /// Whether to return multiple functor matches.
      bool include_all;

      /// True if and only if the passed functor matches all matchable non-empty fields of the observable (i.e. everything except purpose, dependencies, backend_reqs, functionChain and subcaps).
      bool matches(functor*, const Utils::type_equivalency&) const;

      /// Whether the set of dependency rules subjugate to this observable allow a given module functor or not. 
      /// Must be true for the passed module functor to be used to resolve a dependency of the module functor that provides this observable (the dependee).
      /// Does not test if the dependee actually matches the observable, so should typically only be used after confirming this first.
      bool dependencies_allow(functor*, const Utils::type_equivalency&, bool ignore_if_weak = true) const;

      /// Whether the functionChain of this observable allows a given module functor to be used to resolve the dependency of another. 
      /// Does not test if the dependent functor actually matches the observable, so should typically only be used after confirming this first.
      bool function_chain_allows(functor*, functor*, const Utils::type_equivalency&) const;

      /// Whether the set of backend rules subjugate to this observable allow a given backend functor or not. 
      /// Must be true for the passed backend functor to be used to resolve a backend requirement of the module functor that matches this observable (the requiree).
      /// Does not test if the requiree actually matches the observable, so should typically only be used after confirming this first.
      bool backend_reqs_allow(functor*, const Utils::type_equivalency&, const str&, bool ignore_if_weak = true) const;

      ///Default constructor. Sets all fields empty.
      Observable():
        purpose(),
        capability(),
        type(),
        function(),
        module(),
        dependencies(),
        backends(),
        functionChain(),
        subcaps(),
        printme(true),
        log_matches(true),
        include_all(false)
      {}
    };

  }

}
