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

#include "gambit/Utils/export_symbols.hpp"

namespace Gambit {

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

    // Delete all (copy + move) constructors and assignment operators
    ModelValidationHandler& operator=(const ModelValidationHandler&) = delete;
    ModelValidationHandler& operator=(ModelValidationHandler&&) = delete;
    ModelValidationHandler(const ModelValidationHandler&) = delete;
    ModelValidationHandler(ModelValidationHandler&&) = delete;

  private:
    ModelValidationHandling _model_validation_handling;

    ModelValidationHandler() : _model_validation_handling(ModelValidationHandling::pass) {}
  };

}

#endif // __model_validation_hpp__
