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
///  \date 2026 Apr
///
///  *********************************************

#include <sstream>

#include "gambit/Utils/model_validation.hpp"
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

  void ModelValidationHandler::handleInvalidModel(const std::string& model_name) const
  {
    if (_model_validation_handling == ModelValidationHandling::pass) {
      return;
    }

    if (_model_validation_handling == ModelValidationHandling::invalidate)
    {
      std::stringstream ss;
      ss << "Parameters of model " << model_name << " are invalid. Invalidate this point";
      invalid_point().raise(ss.str());
    }

    if (_model_validation_handling == ModelValidationHandling::raise)
    {
      std::stringstream ss;
      ss << "Parameters of model " << model_name << " are invalid. Stop the scan";
      model_error().raise(LOCAL_INFO, ss.str());
    }
  }
} // namespace Gambit