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


  namespace slhahelp
  {

    /// map from gauge eigenstate strings to string, index pairs
    std::map<str, p_int_string> init_gauge_label_to_index_type()
    {
       std::map<str, p_int_string> gauge_label_to_index_type;

       gauge_label_to_index_type["~e_L"]      = std::make_pair(1,"~e-");
       gauge_label_to_index_type["~mu_L"]     = std::make_pair(2,"~e-");
       gauge_label_to_index_type["~tau_L"]    = std::make_pair(3,"~e-");
       gauge_label_to_index_type["~e_R"]      = std::make_pair(4,"~e-");
       gauge_label_to_index_type["~mu_R"]     = std::make_pair(5,"~e-");
       gauge_label_to_index_type["~tau_R"]    = std::make_pair(6,"~e-");

       gauge_label_to_index_type["~d_L"]      = std::make_pair(1,"~d");
       gauge_label_to_index_type["~s_L"]      = std::make_pair(2,"~d");
       gauge_label_to_index_type["~b_L"]      = std::make_pair(3,"~d");
       gauge_label_to_index_type["~d_R"]      = std::make_pair(4,"~d");
       gauge_label_to_index_type["~s_R"]      = std::make_pair(5,"~d");
       gauge_label_to_index_type["~b_R"]      = std::make_pair(6,"~d");

       gauge_label_to_index_type["~u_L"]      = std::make_pair(1,"~u");
       gauge_label_to_index_type["~c_L"]      = std::make_pair(2,"~u");
       gauge_label_to_index_type["~t_L"]      = std::make_pair(3,"~u");
       gauge_label_to_index_type["~u_R"]      = std::make_pair(4,"~u");
       gauge_label_to_index_type["~c_R"]      = std::make_pair(5,"~u");
       gauge_label_to_index_type["~t_R"]      = std::make_pair(6,"~u");

       gauge_label_to_index_type["~nu_e_L"]   = std::make_pair(1,"~nu");
       gauge_label_to_index_type["~nu_mu_L"]  = std::make_pair(2,"~nu");
       gauge_label_to_index_type["~nu_tau_L"] = std::make_pair(3,"~nu");

       return gauge_label_to_index_type;
    }

    /// map from mass eigenstate strings to string, index pairs
    std::map<str, p_int_string> init_mass_label_to_index_type()
    {
       std::map<str, p_int_string> mass_label_to_index_type;
       mass_label_to_index_type["~e-_1"] = std::make_pair(1,"~e-");
       mass_label_to_index_type["~e-_2"] = std::make_pair(2,"~e-");
       mass_label_to_index_type["~e-_3"] = std::make_pair(3,"~e-");
       mass_label_to_index_type["~e-_4"] = std::make_pair(4,"~e-");
       mass_label_to_index_type["~e-_5"] = std::make_pair(5,"~e-");
       mass_label_to_index_type["~e-_6"] = std::make_pair(6,"~e-");

       mass_label_to_index_type["~d_1"]  = std::make_pair(1,"~d");
       mass_label_to_index_type["~d_2"]  = std::make_pair(2,"~d");
       mass_label_to_index_type["~d_3"]  = std::make_pair(3,"~d");
       mass_label_to_index_type["~d_4"]  = std::make_pair(4,"~d");
       mass_label_to_index_type["~d_5"]  = std::make_pair(5,"~d");
       mass_label_to_index_type["~d_6"]  = std::make_pair(6,"~d");

       mass_label_to_index_type["~u_1"]  = std::make_pair(1,"~u");
       mass_label_to_index_type["~u_2"]  = std::make_pair(2,"~u");
       mass_label_to_index_type["~u_3"]  = std::make_pair(3,"~u");
       mass_label_to_index_type["~u_4"]  = std::make_pair(4,"~u");
       mass_label_to_index_type["~u_5"]  = std::make_pair(5,"~u");
       mass_label_to_index_type["~u_6"]  = std::make_pair(6,"~u");

       mass_label_to_index_type["~nu_1"] = std::make_pair(1,"~nu");
       mass_label_to_index_type["~nu_2"] = std::make_pair(2,"~nu");
       mass_label_to_index_type["~nu_3"] = std::make_pair(3,"~nu");

       return  mass_label_to_index_type;
    }

    /// map to extract info from family state
    std::map<str, pair_string_ints> init_familystate_label()
    {
       std::map<str, pair_string_ints> familystate_label;

       //pairs labeling family, mass
       pair_ints const three_one(3,1);
       pair_ints const three_two(3,2);
       pair_ints const two_one(3,1);
       pair_ints const two_two(3,2);
       pair_ints const one_one(3,1);
       pair_ints const one_two(3,2);

       //triplet labelling type, generation and mass order of family states
       pair_string_ints const stop1("~u",three_one);
       pair_string_ints const stop2("~u",three_two);
       pair_string_ints const sbot1("~d",three_one);
       pair_string_ints const sbot2("~d",three_two);
       pair_string_ints const stau1("~e-",three_one);
       pair_string_ints const stau2("~e-",three_two);
       pair_string_ints const scharm1("~u",two_one);
       pair_string_ints const scharm2("~u",two_two);
       pair_string_ints const sstrange1("~d",two_one);
       pair_string_ints const sstrange2("~d",two_two);
       pair_string_ints const smuon1("~e-",two_one);
       pair_string_ints const smuon2("~e-",two_two);
       pair_string_ints const sup1("~u",one_one);
       pair_string_ints const sup2("~u",one_two);
       pair_string_ints const sdown1("~d",one_one);
       pair_string_ints const sdown2("~d",one_two);
       pair_string_ints const selectron1("~e-",one_one);
       pair_string_ints const selectron2("~e-",one_two);

       // only have left handed sneutrinos in MSSM
       pair_string_ints const snue1("~nu",three_one);
       pair_string_ints const snumu1("~nu",two_one);
       pair_string_ints const snutau1("~nu",one_one);

       familystate_label["~t_1"]    =  stop1;
       familystate_label["~t_2"]    = stop2;
       familystate_label["~b_1"]    = sbot1;
       familystate_label["~b_2"]    = sbot2;
       familystate_label["~tau_1"]  = stau1;
       familystate_label["~tau_2"]  = stau2;

       familystate_label["~c_1"]    = scharm1;
       familystate_label["~c_2"]    = scharm2;
       familystate_label["~s_1"]    = sstrange1;
       familystate_label["~s_2"]    = sstrange2;
       familystate_label["~muon_1"] = smuon1;
       familystate_label["~muon_2"] = smuon2;

       //  maybe we shouldn't do first gen it's confusing
       familystate_label["~u_1"]    = sup1;
       familystate_label["~u_2"]    = sup2;
       familystate_label["~d_1"]    = sdown1;
       familystate_label["~d_2"]    = sdown2;
       familystate_label["~e-_1"]   = selectron1;
       familystate_label["~e-_2"]   = selectron2;

       // these are even less needed since no l-r mixing without r state
       familystate_label["~nu_1"]   = snue1;
       familystate_label["~nu_2"]   = snumu1;
       familystate_label["~nu_3"]   = snutau1;

       return familystate_label;

    }

    ///map to obtain left_right gauge_pairs from state info
    /// helps us reuse other routiones with string arguments
    std::map<p_int_string, std::vector<str> >  init_type_family_to_gauge_states()
    {
       std::map<p_int_string, std::vector<str> > type_family_to_gauge_states;

       type_family_to_gauge_states[std::make_pair(3,"~u")] = initVector<str>("~t_L","~t_R");
       type_family_to_gauge_states[std::make_pair(3,"~d")] = initVector<str>("~b_L","~b_R");
       type_family_to_gauge_states[std::make_pair(3,"~e-")]= initVector<str>("~tau_L","~tau_R");
       type_family_to_gauge_states[std::make_pair(2,"~u")] = initVector<str>("~c_L","~c_R");
       type_family_to_gauge_states[std::make_pair(2,"~d")] = initVector<str>("~s_L","~s_R");
       type_family_to_gauge_states[std::make_pair(2,"~e-")]= initVector<str>("~mu_L","~mu_R");
       type_family_to_gauge_states[std::make_pair(1,"~u")] = initVector<str>("~u_L","~u_R");
       type_family_to_gauge_states[std::make_pair(1,"~d")] = initVector<str>("~d_L","~d_R");
       type_family_to_gauge_states[std::make_pair(1,"~e-")]= initVector<str>("~e_L","~e_R");
       //no sneutrino gauges pairs as no right sneutrino

       return type_family_to_gauge_states;
    }

    /// maps directly from family string to left_right gauge_pairs
    /// helps us reuse other routines that take string arguments
    std::map<str, std::vector<str> > init_family_state_to_gauge_state()
    {
       std::map<str, std::vector<str> > family_state_to_gauge_state;

       family_state_to_gauge_state["~t_1"]    = initVector<str>("~t_L","~t_R");
       family_state_to_gauge_state["~t_2"]    = initVector<str>("~t_L","~t_R");
       family_state_to_gauge_state["~b_1"]    = initVector<str>("~b_L","~b_R");
       family_state_to_gauge_state["~b_2"]    = initVector<str>("~b_L","~b_R");
       family_state_to_gauge_state["~tau_1"]  = initVector<str>("~tau_L","~tau_R");
       family_state_to_gauge_state["~tau_2"]  = initVector<str>("~tau_L","~tau_R");

       family_state_to_gauge_state["~c_1"]    = initVector<str>("~c_L","~c_R");
       family_state_to_gauge_state["~c_2"]    = initVector<str>("~c_L","~c_R");
       family_state_to_gauge_state["~s_1"]    = initVector<str>("~s_L","~s_R");
       family_state_to_gauge_state["~s_2"]    = initVector<str>("~s_L","~s_R");
       family_state_to_gauge_state["~muon_1"] = initVector<str>("~mu_L","~mu_R");
       family_state_to_gauge_state["~muon_2"] = initVector<str>("~mu_L","~mu_R");

       family_state_to_gauge_state["~u_1"]    = initVector<str>("~u_L","~u_R");
       family_state_to_gauge_state["~u_2"]    = initVector<str>("~u_L","~u_R");
       family_state_to_gauge_state["~d_1"]    = initVector<str>("~d_L","~d_R");
       family_state_to_gauge_state["~d_2"]    = initVector<str>("~d_L","~d_R");
       family_state_to_gauge_state["~e-_1"]   = initVector<str>("~e_L","~e_R");
       family_state_to_gauge_state["~e-_2"]   = initVector<str>("~e_L","~e_R");

       return family_state_to_gauge_state;
    }

    ///maps directly from gauge_es string to familystates
    /// helps us reuse other routines that take string arguments
    std::map<str, std::vector<str> >  init_gauge_es_to_family_states()
    {
       std::map<str, std::vector<str> >  gauge_es_to_family_states;

       gauge_es_to_family_states["~t_L"]   = initVector<str>("~t_1","~t_2");
       gauge_es_to_family_states["~t_R"]   = initVector<str>("~t_1","~t_2");
       gauge_es_to_family_states["~b_L"]   = initVector<str>("~b_1","~b_2");
       gauge_es_to_family_states["~b_R"]   = initVector<str>("~b_1","~b_2");
       gauge_es_to_family_states["~tau_L"] = initVector<str>("~tau_1","~tau_2");
       gauge_es_to_family_states["~tau_R"] = initVector<str>("~tau_1","~tau_2");
       gauge_es_to_family_states["~c_L"]   = initVector<str>("~c_1","~c_2");
       gauge_es_to_family_states["~c_R"]   = initVector<str>("~c_1","~c_2");
       gauge_es_to_family_states["~s_L"]   = initVector<str>("~s_1","~s_2");
       gauge_es_to_family_states["~s_R"]   = initVector<str>("~s_1","~s_2");
       gauge_es_to_family_states["~mu_L"]  = initVector<str>("~mu_1","~mu_2");
       gauge_es_to_family_states["~mu_R"]  = initVector<str>("~mu_1","~mu_2");

       gauge_es_to_family_states["~u_L"]   = initVector<str>("~u_1","~u_2");
       gauge_es_to_family_states["~u_R"]   = initVector<str>("~u_1","~u_2");
       gauge_es_to_family_states["~d_L"]   = initVector<str>("~d_1","~d_2");
       gauge_es_to_family_states["~d_R"]   = initVector<str>("~d_1","~d_2");
       gauge_es_to_family_states["~e_L"]   = initVector<str>("~e-_1","~e-_2");
       gauge_es_to_family_states["~e_R"]   = initVector<str>("~e-_1","~e-_2");

       return gauge_es_to_family_states;
    }

    /// map from string representing type (ie up-squarks, down-squarks or
    /// charged sleptons) to appropriate set of mass eigenstates
    std::map<str,std::vector<str> > init_type_to_vec_of_mass_es()
    {
       std::map<str,std::vector<str> > type_to_vec_of_mass_es;

       type_to_vec_of_mass_es["~u"]  = initVector<str>("~u_1", "~u_2", "~u_3", "~u_4", "~u_5", "~u_6");
       type_to_vec_of_mass_es["~d"]  = initVector<str>("~d_1", "~d_2", "~d_3", "~d_4", "~d_5", "~d_6");
       type_to_vec_of_mass_es["~e-"] = initVector<str>("~e-_1", "~e-_2", "~e-_3", "~e-_4", "~e-_5", "~e-_6");
       type_to_vec_of_mass_es["~nu"] = initVector<str>("~nu_1", "~nu_2", "~nu_3");

       return type_to_vec_of_mass_es;
    }

    /// map from string representing type (ie up-squarks, down-squarks or
    /// charged sleptons) to appropriate set of gauge eigenstates
    std::map<str,std::vector<str> > init_type_to_vec_of_gauge_es()
    {
       std::map<str,std::vector<str> > type_to_vec_of_gauge_es;

       type_to_vec_of_gauge_es["~u"]  = initVector<str>("~u_L", "~c_L", "~t_L", "~u_R", "~c_R", "~t_R");
       type_to_vec_of_gauge_es["~d"]  = initVector<str>("~d_L", "~s_L", "~b_L", "~d_R", "~s_R", "~b_R");
       type_to_vec_of_gauge_es["~e-"] = initVector<str>("~e_L", "~mu_L", "~tau_L", "~e_R", "~mu_R", "~tau_R");
       type_to_vec_of_gauge_es["~nu"] = initVector<str>("~nu_e_L", "~nu_mu_L", "~nu_tau_L");

       return type_to_vec_of_gauge_es;
    }

  }

}
