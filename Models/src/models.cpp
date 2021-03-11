//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Library of Models methods.
///
///  Duties:
///  * Activate primary_model_functors according to
///    the model(s) being scanned
///  * Check whether all active primary_model_functors
///    are actually used
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 July 17
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Aug, Sep
///  \date 2014 Mar
///
///  *********************************************

#include <algorithm>
#include "gambit/Elements/functors.hpp"
#include "gambit/Models/models.hpp"

namespace Gambit
{

  namespace Models
  {

    typedef std::map<std::string, primary_model_functor *>::const_iterator activemodel_it;

    /// ModelFunctorClaw function definitions
    /// Models object the performs initialisation and checking operations
    /// on a primary_model_functor list.
    /// @{

    // Public functions and data members

    /// Model activation function
    /// Returns a vector of primary_model_functors to be activated, according to the model(s) being scanned
    primodel_vec ModelFunctorClaw::getPrimaryModelFunctorsToActivate (std::set<str> selectedmodels, const primodel_vec& primaryModelFunctors)
    {
      // Holder for result
      primodel_vec result;
      // Iterator to elements of 'selectedmodels'
      std::set<str>::iterator el;

      // Loop through functor list and activate functor if it matches a member of 'selectedmodels'.
      for (primodel_vec::const_iterator
          it  = primaryModelFunctors.begin();
          it != primaryModelFunctors.end();
          ++it)
      {
        // Check if this functor originates from one of the selected models
        el = std::find(selectedmodels.begin(), selectedmodels.end(), (*it)->origin());
        if(el != selectedmodels.end())
        {
          // If yes, activate this functor.  Default is inactivated.
          (*it)->setStatus(1);               // 1 means "available".
          (*it)->setPrintRequirement(true);  // Tell printer to output this functor
          // Initialise ModelParameters object it contains
          (*it)->calculate();
          // Add it to the vector of primary model functors to make active (to be returned)
          result.push_back(*it);
          // Add it to the internal list of active models
          activemodels.insert(*el);
          // Remove it from the input 'selectedmodels' list
          selectedmodels.erase(el);
        }
      }

      // Check that all requested models have been activated
      if( selectedmodels.size() != 0 )
      {
        // Report error
        str errmsg = "Error! Some of the requested models could not be activated for \n";
        errmsg    += "scanning! Probably they have not been defined, or you spelled  \n";
        errmsg    += "their name wrong in the ini file.                              \n";
        errmsg    += "Models that cannot be activated:                               \n";
        for (std::set<str>::iterator m = selectedmodels.begin(); m != selectedmodels.end(); ++m)
        {
          errmsg    += ("  " + *m + "\n");
        }
        model_error().raise(LOCAL_INFO,errmsg);
      }

      return result;

    }

    /// Searches primary model functor list for specificed model
    primary_model_functor* ModelFunctorClaw::getPrimaryModelFunctor(const std::string modelname, const primodel_vec& primaryModelFunctors) const
    {
      primary_model_functor* result;

      // Find primary model functor with matching name
      auto it = std::find_if(std::begin(primaryModelFunctors), std::end(primaryModelFunctors), 
                 [&] (primary_model_functor* f) {return f->getcontentsPtr()->getModelName() == modelname;});

      if(it != primaryModelFunctors.end())
      {
          result = *it;
      }
      else
      {
          std::stringstream err;
          err<<"No primary model functor with model name "<<modelname<<" was found! Please check the input name for typos!";
          model_error().raise(LOCAL_INFO,err.str());
      }
      return result;
    }

    /// Return set of all models recognised by GAMBIT
    const std::set<str>& ModelFunctorClaw::get_allmodels() const { return allmodelnames; }

    /// Retrieve the internally stored vector of activated models
    std::set<str> ModelFunctorClaw::get_activemodels() const { return activemodels; }

    /// Active model functor "usefulness" checker
    ///
    /// Checks that all the active primary model functors are actually used for
    /// something in the dependency tree. If not throws an error to warn the
    /// user.
    void ModelFunctorClaw::checkPrimaryModelFunctorUsage(const activemodel_map& activeModelFunctors) const
    {
      std::vector<std::string> unusedmodels;
      std::string modelname;
      primary_model_functor* functorPtr;
      // Loop through functor list and check that their statuses have all been
      // set to 2 ("active"). If not, it means that some of them were not
      // activated by the dependency resolver and thus are not used for
      // computing anything.
      for(activemodel_it it  = activeModelFunctors.begin();
                         it != activeModelFunctors.end(); it++)
      {
        modelname  = it->first;
        functorPtr = it->second;

        if ( functorPtr->status()!=2 )
        {
          unusedmodels.push_back( modelname );
        }
      }

      // If we found unused models throw an error
      if ( unusedmodels.size() > 0 )
      {
        str errmsg = "Some models selected for scanning are not required by any of\n";
        errmsg    += "the requested observables/likelihoods! Please switch these  \n";
        errmsg    += "off in the inifile or add a target that actually uses them. \n";
        errmsg    += "List of unused models:                                      \n";
        for (std::vector<std::string>::iterator it = unusedmodels.begin(); it != unusedmodels.end(); ++it)
        {
          errmsg  += (*it + "\n");
        }
        model_error().raise(LOCAL_INFO,errmsg);
      }

    }

    /// Add a new model to the model database.
    void ModelFunctorClaw::declare_model (const str &model, const str &parent)
    {
      // Register the new model.
      allmodelnames.insert(model);
      if (parent != "PARENT")
      {
        // If the parent actually doesn't exist yet, die.
        if (not model_exists(parent))
        {
          str errmsg = "Requested parent model \""+parent+ "\" for model \""+model;
          errmsg += "\nis not in the GAMBIT database. Recognised models are:\n" + list_models();
          model_error().raise(LOCAL_INFO,errmsg);
        }
        // Add the parent to the parents database.
        myParentsDB[model] = parent;
        // Inherit friends from the model's parent.
        myFriendsDB[model] = myFriendsDB[parent];
        // Inherit lineage from the model's parent.
        myLineageDB[model] = myLineageDB[parent];
      }
      else
      {
        // Seed empty friend sets and inheritance vector.
        myFriendsDB[model] = std::set<str>();
        myBestFriendsDB[model] = std::set<str>();
        myLineageDB[model] = std::vector<str>();
      }
      // Add the new model to its own lineage vector.
      myLineageDB[model].push_back(model);
      // Register the model in each of its parents' descendents vectors.
      for (std::set<str>::iterator parent = allmodelnames.begin(); parent != allmodelnames.end(); ++parent)
      {
        // If this model descends from parent, add it to the parent's descendents vector
        if (descended_from(model,*parent)) myDescendantsDB[*parent].push_back(model);
      }
    }

    /// Add a friend, and all its friends and ancestors, to a model's list of friends
    void ModelFunctorClaw::add_friend (const str &model, const str &newfriend)
    {
      // If the new friend actually doesn't exist yet, die.
      if (not model_exists(newfriend))
      {
        str errmsg = "Requested friend model \""+newfriend + "\" for model \""+model;
        errmsg += "\nis not in the GAMBIT database. Recognised models are:\n" + list_models();
        model_error().raise(LOCAL_INFO,errmsg);
      }
      // Add the new friend as a best friend.
      myBestFriendsDB[model].insert(newfriend);
      // Add the new friend's whole lineage vector as regular friends.
      std::set<str> temp1, temp2, lineage(myLineageDB[newfriend].begin(), myLineageDB[newfriend].end());
      set_union(myFriendsDB[model].begin(), myFriendsDB[model].end(), lineage.begin(), lineage.end(), inserter(temp1, temp1.begin()));
      // Also inherit the new friend's friends as regular friends.
      set_union(temp1.begin(), temp1.end(), myFriendsDB[newfriend].begin(), myFriendsDB[newfriend].end(), inserter(temp2, temp2.begin()));
      myFriendsDB[model] = temp2;
    }

    /// Indicate whether a model is recognised by GAMBIT or not
    bool ModelFunctorClaw::model_exists (const str &model) const
    {
      return allmodelnames.find(model) != allmodelnames.end();
    }

    /// List all the models recognised by GAMBIT
    str ModelFunctorClaw::list_models() const
    {
      str temp = "";
      for (std::set<str>::iterator it = allmodelnames.begin(); it != allmodelnames.end(); ++it)
      {
        temp += "\n" + *it;
      }
      return temp;
    }

    /// Verify that a string matches a model recognised by GAMBIT, crash otherwise
    void ModelFunctorClaw::verify_model(const str &model) const
    {
      if (not model_exists(model))
      {
        str errmsg = "Model \"";
        errmsg += model + "\" is not in the GAMBIT database.";
        errmsg += "\nRecognised models are:" + list_models();
        model_error().raise(LOCAL_INFO,errmsg);
      }
    }

    /// Retrieve the descendants for a given model
    std::vector<str> ModelFunctorClaw::get_descendants (const str &model) const
    {
      return myDescendantsDB.find(model) == myDescendantsDB.end() ? std::vector<str>() : myDescendantsDB.at(model);
    }

    /// Retrieve the parents for a given model
    str ModelFunctorClaw::get_parent (const str &model) const
    {
      return myParentsDB.find(model) == myParentsDB.end() ? "none" : myParentsDB.at(model);
    }

    /// Retrieve the lineage for a given model
    std::vector<str> ModelFunctorClaw::get_lineage (const str &model) const
    {
      return myLineageDB.find(model) == myLineageDB.end() ? std::vector<str>() : myLineageDB.at(model);
    }

    /// Retrieve the friends for a given model
    std::set<str> ModelFunctorClaw::get_friends (const str &model) const
    {
      return myFriendsDB.find(model) == myFriendsDB.end() ? std::set<str>() : myFriendsDB.at(model);
    }

    /// Retrieve the best friends for a given model
    std::set<str> ModelFunctorClaw::get_best_friends (const str &model) const
    {
      return myBestFriendsDB.find(model) == myBestFriendsDB.end() ? std::set<str>() : myBestFriendsDB.at(model);
    }

    /// Check if model 1 is descended from model 2
    bool ModelFunctorClaw::descended_from (const str &model1, const str &model2) const
    {
      verify_model(model1);
      auto lineage = myLineageDB.at(model1);
      for (std::vector<str>::const_iterator it = lineage.begin(); it != lineage.end(); ++it)
      {
        if (model2==*it) return true;
      }
      return false;
    }

    /// Check if model 1 is an ancestor of model 2
    bool ModelFunctorClaw::ancestor_of (const str &model1, const str &model2) const
    {
      return descended_from(model2, model1);
    }

    /// Check if model 1 exists somewhere downstream of (and can be therefore be interpreted as a) model 2
    bool ModelFunctorClaw::downstream_of (const str &model1, const str &model2) const
    {
      if (descended_from(model1, model2)) return true;
      if (myFriendsDB.find(model1) != myFriendsDB.end())
      {
        std::set<str> friends = myFriendsDB.at(model1);
        return friends.find(model2) != friends.end();
      }
      return false;
    }

    /// Check if model 1 exists somewhere upstream of model 2, allowing model 2 to be interpreted as model 1
    bool ModelFunctorClaw::upstream_of (const str &model1, const str &model2) const
    {
      return downstream_of(model2, model1);
    }

    /// @}

  }

}
