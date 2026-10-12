//  *********************************************
//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions for model validation classes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2026 Oct
///
///  *********************************************

#include <iostream>
#include <sstream>

#include "gambit/Utils/model_validation.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

namespace Gambit
{

  ModelValidationHandler& ModelValidationHandler::getInstance()
  {
    static ModelValidationHandler instance;
    return instance;
  }

  void ModelValidationHandler::setModelValidationHandling(const ModelValidationHandling &h)
  {
    _model_validation_handling = h;
  }

  const ModelValidationHandling &ModelValidationHandler::getModelValidationHandling() const
  {
    return _model_validation_handling;
  }

  void ModelValidationHandler::activate()
  {
    _model_validation_active = true;
  }

  void ModelValidationHandler::deactivate()
  {
    _model_validation_active = false;
  }

  void ModelValidationHandler::registerModelValidator(const std::string& model_name, modelValidator f)
  {
    if (_model_validators.find(model_name) != _model_validators.end())
    {
      model_error().raise(LOCAL_INFO, "Attempt to register model validation function for model " + model_name + " failed. A model validation function has already been registered.");
    }
    _model_validators[model_name] = std::move(f);
  }

  bool ModelValidationHandler::hasModelValidator(const std::string& model_name) const
  {
    return _model_validators.find(model_name) != _model_validators.end();
  }

  bool ModelValidationHandler::validateModel(const ModelParameters& model_parameters) const
  {
    auto it = _model_validators.find(model_parameters.getModelName());
    if (it == _model_validators.end() || !it->second)
    {
      return true;
    }
    return it->second(model_parameters);
  }

  void ModelValidationHandler::runModelValidation(const ModelParameters &model_parameters) const
  {
    // Model validation short circuits, if:
    // - model validation is not activated
    // - model validation handling is 'pass'
    // - model parameters are valid
    if (!_model_validation_active || _model_validation_handling == ModelValidationHandling::pass || validateModel(model_parameters))
    {
      return;
    }

    // If this point is reached, model validation is active, model parameters are invalid and the model validation handling is not pass.
    std::stringstream ss;
    ss << "Parameters of model " << model_parameters.getModelName() << " are invalid.";

    if (_model_validation_handling == ModelValidationHandling::invalidate)
    {
      invalid_point().raise(ss.str());
    }
    else if (_model_validation_handling == ModelValidationHandling::raise)
    {
      model_error().raise(LOCAL_INFO, ss.str());
    }
    else
    {
      // This should be unreachable
      utils_error().raise(LOCAL_INFO, "Reached unreachable code in ModelValidationHandler::runModelValidation. This is a bug.");
    }
  }

  int register_model_validation_function(const std::string& model, modelValidator f)
  {
    try
    {
      ModelValidationHandler::getInstance().registerModelValidator(model, std::move(f));
    }
    catch (std::exception& e)
    {
      std::cout << "Error registering model validation function for model " << model << ": " << e.what() << std::endl;
    }
    return 0;
  }

} // namespace Gambit
