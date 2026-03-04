//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Struct containing all functions required to be
///  written for a given module function, in order
///  to run an emulator on that function.
///
///  Add to this as required, also adding a corresponding
///  function declaration in the macro below.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2026 Jan
///
///  *********************************************


#ifndef __emulator_module_functions_hpp__
#define __emulator_module_functions_hpp__

#include <vector>
#include <string>

namespace Gambit
{

  /// Struct containing function pointers for emulator interface
  /// Here TYPE is the return type of the module function
  template <typename TYPE>
  struct emulator_required_function_ptrs
  {
    void (*TranslateInput)(std::vector<double> &);
    bool (*CheckThreshold)(std::string &, std::vector<double> &);
    // void (*Predict)(std::string &, std::vector<double> &, std::vector<double> &, std::vector<double> &);
    void (*TranslateTarget)(std::vector<double> &, TYPE &, std::vector<double> &);
    // void (*Train)(std::string &, std::vector<double> &, std::vector<double> &, std::vector<double> &);
    void (*TranslatePrediction)(std::vector<double> &, TYPE &);
  };

}

// Macro to declare all functions that emulators require to be written for a given module function
// This is then called inside module_macros_incore_defs.hpp, inside MAKE_FUNCTOR_MAIN
// Note: This macro must be defined outside of namespace Gambit since it uses CAT from cats.hpp
// which is included before this header in module_macros_incore_defs.hpp
#define DECLARE_EMULATOR_MODULE_FUNCTIONS(FUNCTION, TYPE)                                                                \
  void CAT(FUNCTION,_EmulatorTranslateInput)(std::vector<double> &);                                                     \
  bool CAT(FUNCTION,_EmulatorCheckThreshold)(str &, std::vector<double> &);                                              \
  void CAT(FUNCTION,_EmulatorTranslateTarget)(std::vector<double> &, TYPE &, std::vector<double> &);                     \
  void CAT(FUNCTION,_EmulatorTranslatePrediction)(std::vector<double> &, TYPE &);                                          \
                                                                                                                         \
  Gambit::emulator_required_function_ptrs<TYPE> CAT(FUNCTION,emu_ptrs) = {                                               \
    &CAT(FUNCTION,_EmulatorTranslateInput),                                                                              \
    &CAT(FUNCTION,_EmulatorCheckThreshold),                                                                              \
    &CAT(FUNCTION,_EmulatorTranslateTarget),                                                                             \
    &CAT(FUNCTION,_EmulatorTranslatePrediction)                                                                          \
  };

#endif //defined __emulator_module_functions_hpp__
