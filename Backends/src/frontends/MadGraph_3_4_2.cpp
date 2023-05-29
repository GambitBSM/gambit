//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the MadGraph v3.4.2 
///  backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2021
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MadGraph_3_4_2.hpp"

BE_INI_FUNCTION {}
END_BE_INI_FUNCTION

BE_NAMESPACE
{

#ifdef HAVE_PYBIND11
  // Convert the maps to PyDicts before passing them to MadGraph
  int MG_RunEvents(str& mg5_dir, str& script_name, std::vector<str>& commands, std::map<str, double>& PassParamsToMG)
  {
    // Convert the std::map to a PyDict
    pybind11::dict MGParams;
    
    for (auto mydict : PassParamsToMG)
    {
      pybind11::str Param = mydict.first;
      MGParams[Param] = mydict.second;
    }
    
    // Run the MadGraph Event Generation
    int success = MG_RunEvents_pydict(mg5_dir, script_name, commands, MGParams);
    
    return success;
  }
#else
  int MG_RunEvents(str& mg5_dir, str& script_name, std::vector<str>& commands, std::map<str, double>& PassMassParamsToMG)
  {
    backend_error().raise(LOCAL_INFO, "pybind11 has been excluded, but is required for the MadGraph backend.\n");
    return 0; // Just returning a number to be consistent with types
  }
#endif

}
END_BE_NAMESPACE
