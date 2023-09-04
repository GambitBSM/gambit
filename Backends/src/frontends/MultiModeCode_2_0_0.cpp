//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the MultiModeCode backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Feb
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MultiModeCode_2_0_0.hpp"

// Callback function for error handling
BE_NAMESPACE
{
  // This function will be called from MultiModeCode. Needs C linkage, and thus also
  // a backend-specific name to guard against name clashes.
  extern "C"
  void CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler)()
  {
    throw std::runtime_error("MultiModeCode backend raised an exception.");
  }
}
END_BE_NAMESPACE


BE_INI_FUNCTION
{
  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {
    // Set the function pointer in MultiModeCode to our ErrorHandler callback function
    *ErrorHandler_cptr = & CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler);

    // Set the SilenceOutput variable
    *SilenceOutput = runOptions->getValueOrDef<bool>(true, "SilenceOutput");
  }
  scan_level = false;

}
END_BE_INI_FUNCTION
