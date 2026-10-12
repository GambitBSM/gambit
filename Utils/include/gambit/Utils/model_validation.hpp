//  *********************************************
//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Classes and enum model validation handling
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

#ifndef __model_validation_hpp__
#define __model_validation_hpp__

#include <functional>
#include <map>
#include <string>

#include "gambit/Utils/export_symbols.hpp"

namespace Gambit {

  class ModelParameters;

  /// Model validation functor type
  typedef std::function<bool(const ModelParameters&)> modelValidator;

  /// Enumeration for model validation handling strategies.
  /// - pass: No model validation is performed.
  /// - invalidate: The current parameter point will be deemed invalid
  /// - raise: A model validation error will be raised
  enum class ModelValidationHandling
  {
    pass,
    invalidate,
    raise
  };

  /// Class for handling model validation logic.
  /// This is implemented as a singleton to ensure globally consistent model validation handling.
  class EXPORT_SYMBOLS ModelValidationHandler
  {
  public:
    /// Get the singleton instance of the handler
    static ModelValidationHandler& getInstance();

    /// Set the handling strategy for model validation (pass, warning, or error)
    void setModelValidationHandling(const ModelValidationHandling& h);

    /// Get the current handling strategy for model validation
    [[nodiscard]] const ModelValidationHandling& getModelValidationHandling() const;

    /// Activate the model validation handler
    void activate();

    /// Deactivate the model validation handler
    void deactivate();

    /// Register a model validation function for a specific model
    void registerModelValidator(const std::string& model_name, modelValidator f);

    /// Check if a model validation function has been registered for a specific model
    [[nodiscard]] bool hasModelValidator(const std::string& model_name) const;

    /// Validate the parameters of a model
    [[nodiscard]] bool validateModel(const ModelParameters& model_parameters) const;

    /// Run model validation
    void runModelValidation(const ModelParameters& model_parameters) const;

    // Delete all (copy + move) constructors and assignment operators
    ModelValidationHandler& operator=(const ModelValidationHandler&) = delete;
    ModelValidationHandler& operator=(ModelValidationHandler&&) = delete;
    ModelValidationHandler(const ModelValidationHandler&) = delete;
    ModelValidationHandler(ModelValidationHandler&&) = delete;

  private:
    ModelValidationHandling _model_validation_handling;
    bool _model_validation_active;
    std::map<std::string, modelValidator> _model_validators;

    ModelValidationHandler() : _model_validation_handling(ModelValidationHandling::pass), _model_validation_active(false) {}
  };

  /// Helper function for registering a model validation function at static initialization
  int register_model_validation_function(const std::string& model, modelValidator f);

}

#endif // __model_validation_hpp__
