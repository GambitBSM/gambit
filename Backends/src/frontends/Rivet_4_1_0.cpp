//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the Rivet 4.1.0 backend.
///
///  Scan-level initialisation: checks that the plugin library GAMBIT
///  loaded was built against the same version of ColliderBit's
///  AnalysisHandler interface as GAMBIT itself, then registers the
///  directory of Rivet's analysis plugins.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomek Procter
///          (t.procter.1@research.gla.ac.uk)
///  \date 2021 July
///  \date 2023 April, May
///  \date 2024 October
///  \date 2025 March
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"

#ifndef EXCLUDE_YODA
#ifndef EXCLUDE_HEPMC

#include "gambit/Backends/frontends/Rivet_4_1_0.hpp"
#include "gambit/Utils/util_functions.hpp"

#include <sstream>

BE_INI_FUNCTION
{
  static bool scan_level = true;
  if (scan_level)
  {
    scan_level = false;

    if (create_analysis_handler == nullptr || analysis_handler_interface_version == nullptr || add_analysis_lib_path == nullptr)
    {
      backend_error().raise(LOCAL_INFO, "The Rivet plugin library (librivet_plugin.so) does not export the functions "
       "gambit_create_analysis_handler, gambit_analysis_handler_interface_version and gambit_add_analysis_lib_path. "
       "It is probably stale; rebuild it with 'make rivet'.");
    }

    const int plugin_version = analysis_handler_interface_version();
    if (plugin_version != COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION)
    {
      std::ostringstream msg;
      msg << "The Rivet plugin library (librivet_plugin.so) was built against version " << plugin_version
          << " of ColliderBit's AnalysisHandler interface (ColliderBit/include/gambit/ColliderBit/AnalysisHandler.hpp), "
          << "but GAMBIT was compiled with version " << COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION
          << ". Rebuild the plugin with 'make rivet'.";
      backend_error().raise(LOCAL_INFO, msg.str());
    }

    // Tell Rivet where its analysis plugins are. If the directory does not
    // exist, the Rivet installation is probably incomplete.
    const str rivet_analyses_dir = std::string(GAMBIT_DIR) + "/Backends/installed/rivet/4.1.0/analyses";
    if (!Utils::file_exists(rivet_analyses_dir))
    {
      backend_error().raise(LOCAL_INFO, "Rivet analysis directory does not exist: " + rivet_analyses_dir);
    }
    if (add_analysis_lib_path(rivet_analyses_dir.c_str()) != 0)
    {
      backend_error().raise(LOCAL_INFO, "Rivet could not register its analysis directory " + rivet_analyses_dir);
    }
  }
}
END_BE_INI_FUNCTION

#endif // EXCLUDE_HEPMC
#endif // EXCLUDE_YODA
