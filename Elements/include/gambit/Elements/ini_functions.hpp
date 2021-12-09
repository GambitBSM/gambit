//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions for triggering initialisation code.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Feb
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2015
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Sep
///
///  *********************************************

#ifndef __ini_functions_hpp__
#define __ini_functions_hpp__

#include <vector>

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  /// Forward declarations
  class module_functor_common;
  class model_functor;
  class Options;

  /// Helper function for adding a type equivalency at initialisation
  int add_equivrelation(str, str);

  /// Helper function for passing default backend information at initialisation
  int pass_default_to_backendinfo(str, str);

  /// Runtime addition of model to GAMBIT model database
  int add_model(str, str);

  /// Add a new parameter to a primary model functor
  int add_parameter(model_functor&, str);

  /// Set the model name in a primary model functor
  int set_model_name(model_functor&, str);

  /// Tell a model functor to take its parameter definition from another model functor.
  int copy_parameters(model_functor&, model_functor&, bool, str="", str="");

  /// Register a model functor.
  int register_model_functor(std::map<str, bool(*)()>, std::map<str, str>, bool(*)(), const str&, const str&);

  /// Create a log tag for a new module.
  int register_module_with_log(str);

  /// Register a function with a module.
  int register_function(module_functor_common&, bool, safe_ptr<bool>*, safe_ptr<Options>&,
                        safe_ptr<std::set<sspair>>&, safe_ptr<Options>&);

  /// Register the fact that a module function needs to run nested
  int register_function_nesting(module_functor_common&, omp_safe_ptr<long long>&, const str&, const str&);

  /// Register that a module function is compatible with a single model
  int register_model_singly(module_functor_common&, const str&);

  /// Register a model group with a functor
  int register_model_group(module_functor_common&, const str&, const str&);

  /// Register a backend requirement for a module function
  int register_backend_requirement(module_functor_common&, const str&, const str&,
   const str&, bool, const str&, const str&, void(*)(functor*));

  /// Register a combination of models as allowed with a functor
  int register_model_combination(module_functor_common&, const str&);

  /// Register a dependency of a module function
  int register_dependency(module_functor_common&, const str&, const str&,
   void(*)(functor*, module_functor_common*));

  /// Register a conditional dependency of a module function
  int register_conditional_dependency(module_functor_common&, const str&, const str&);

  /// Register a model parameters dependency of a module function
  int register_model_parameter_dependency(module_functor_common&, const str&, const str&,
   void(*resolver)(functor*, module_functor_common*));

  /// Register a model-conditional dependency of a module function
  int register_model_conditional_dependency(module_functor_common&, const str&,
   const str&, void(*)(functor*, module_functor_common*));

  /// Register a backend-conditional dependency of a module function
  int register_backend_conditional_dependency(module_functor_common&, const str&, const str&,
   const str&, const str&, void(*)(functor*, module_functor_common*));

  /// Apply a backend-matching rule
  int apply_backend_matching_rule(module_functor_common&, const str&);

  /// Apply a backend option rule
  int apply_backend_option_rule(module_functor_common&, const str&, const str&);


}

#endif // #defined __ini_functions_hpp__
