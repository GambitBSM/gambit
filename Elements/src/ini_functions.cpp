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
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2016 Feb
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Sep
///
///  *********************************************

#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Elements/ini_catch.hpp"
#include "gambit/Elements/functors.hpp"
#include "gambit/Elements/equivalency_singleton.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Models/claw_singleton.hpp"
#include "gambit/Logs/logging.hpp"

namespace Gambit
{

  /// Helper function for adding a type equivalency at initialisation
  int add_equivrelation(str s1, str s2)
  {
    try
    {
      Utils::typeEquivalencies().add(s1,s2);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Helper function for passing default backend information at initialisation
  int pass_default_to_backendinfo(str be, str def)
  {
    try
    {
      Backends::backendInfo().default_safe_versions[be] = def;
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Runtime addition of model to GAMBIT model database
  int add_model(str model, str parent)
  {
    try
    {
      Models::ModelDB().declare_model(model, parent);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Add a new parameter to a primary model functor
  int add_parameter(model_functor& primary_parameters, str param)
  {
    try
    {
      primary_parameters.addParameter(param);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Set model name string in a primary model functor
  int set_model_name(model_functor& primary_parameters, str model_name)
  {
    try
    {
      primary_parameters.setModelName(model_name);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Tell a model functor to take its parameter definition from another model functor.
  int copy_parameters(model_functor& donor, model_functor& donee, bool add_friend, str model, str model_x)
  {
    try
    {
      donor.donateParameters(donee);
      if (add_friend) Models::ModelDB().add_friend(model, model_x);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Create a log tag for a new module.
  int register_module_with_log(str module)
  {
    int mytag;
    try
    {
      mytag = Logging::getfreetag();
      Logging::tag2str()[mytag] = module;
      Logging::components().insert(mytag);
    }
    catch (std::exception& e) { ini_catch(e); }
    return mytag;
  }

  /// Register a function with a module.
  int register_function(module_functor_common& f, bool can_manage, safe_ptr<bool>* done,
   safe_ptr<Options>& opts, safe_ptr<std::set<sspair>>& dependees, safe_ptr<Options>& subcaps)
  {
    try
    {
      if (can_manage)
      {
        f.setCanBeLoopManager(true);
        *done = f.loopIsDone();
      }
      opts = f.getOptions();
      dependees = f.getDependees();
      subcaps = f.getSubCaps();
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register the fact that a module function needs to run nested
  int register_function_nesting(module_functor_common& f, omp_safe_ptr<long long>& iteration,
   const str& loopmanager_capability, const str& loopmanager_type)
  {
    try
    {
      f.setLoopManagerCapType(loopmanager_capability, loopmanager_type);
      iteration = f.iterationPtr();
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register that a module function is compatible with a single model
  int register_model_singly(module_functor_common& f, const str& model)
  {
    try
    {
      f.setAllowedModel(model);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a backend requirement for a module function
  int register_backend_requirement(module_functor_common& f, const str& group,
   const str& req, const str& tags, bool is_variable, const str& req_type1,
   const str& req_type2, void(*resolver)(functor*))
  {
    try
    {
      str signature = req_type1 + (is_variable ? "*" : req_type2);
      f.setBackendReq(group, req, tags, signature, resolver);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a dependency of a module function
  int register_dependency(module_functor_common& f, const str& dep, const str& dep_type,
   void(*resolver)(functor*, module_functor_common*))
  {
    try
    {
      f.setDependency(dep, dep_type, resolver);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a conditional dependency of a module function
  int register_conditional_dependency(module_functor_common& f, const str& dep, const str& dep_type)
  {
    try
    {
      f.setConditionalDependency(dep, dep_type);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a model parameters dependency of a module function
  int register_model_parameter_dependency(module_functor_common& f, const str& model,
   const str& dep, void(*resolver)(functor*, module_functor_common*))
  {
    int i = register_conditional_dependency(f, dep, "ModelParameters");
    return i + register_model_conditional_dependency(f, model, dep, resolver);
  }

  /// Register a model-conditional dependency of a module function
  int register_model_conditional_dependency(module_functor_common& f, const str& model,
   const str& dep, void(*resolver)(functor*, module_functor_common*))
  {
    try
    {
      f.setModelConditionalDependency(model, dep, resolver);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a backend-conditional dependency of a module function
  int register_backend_conditional_dependency(module_functor_common& f, const str& req, const str& be,
   const str& versions, const str& dep, void(*resolver)(functor*, module_functor_common*))
  {
    try
    {
      f.setBackendConditionalDependency(req, be, versions, dep, resolver);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a model group with a functor
  int register_model_group(module_functor_common& f, const str& group_name, const str& group)
  {
    try
    {
      f.setModelGroup(group_name,group);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a combination of models as allowed with a functor
  int register_model_combination(module_functor_common& f, const str& combo)
  {
    try
    {
      f.setAllowedModelGroupCombo(combo);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Apply a backend-matching rule
  int apply_backend_matching_rule(module_functor_common& f, const str& rule)
  {
    try
    {
      f.makeBackendMatchingRule(rule);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Apply a backend option rule
  int apply_backend_option_rule(module_functor_common& f, const str& be_and_ver, const str& tags)
  {
    try
    {
      f.makeBackendOptionRule(be_and_ver, tags);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

}
