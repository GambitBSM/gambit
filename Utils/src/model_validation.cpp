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

  const ModelValidationHandling &ModelValidationHandler::getModelValidationHandling() const
  {
    return _model_validation_handling;
  }

} // namespace Gambit