//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for GAMBIT backend Rivet 4.1.0.
///
///  The backend library is a plugin, librivet_plugin.so, built from
///  Backends/src/frontends/plugins/rivet_plugin.cpp as part of the Rivet
///  build. It implements ColliderBit's AnalysisHandler interface
///  (ColliderBit/include/gambit/ColliderBit/AnalysisHandler.hpp) on top of
///  Rivet, and exports the three functions declared below. See
///  Backends/src/frontends/plugins/README.md.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#ifndef EXCLUDE_YODA
#ifndef EXCLUDE_HEPMC

#include "gambit/Backends/backend_types/Rivet_4_1_0/identification.hpp"

LOAD_LIBRARY

#include "gambit/ColliderBit/AnalysisHandler.hpp"

/// Version of the AnalysisHandler interface the plugin was built against; checked at scan start.
BE_FUNCTION(analysis_handler_interface_version, int, (), "gambit_analysis_handler_interface_version", "analysis_handler_interface_version")

/// Create a Rivet analysis handler. The caller owns the instance.
BE_FUNCTION(create_analysis_handler, Gambit::ColliderBit::AnalysisHandler*, (), "gambit_create_analysis_handler", "create_analysis_handler")

/// Add a directory to Rivet's search path for analysis plugins (returns 0 on success).
BE_FUNCTION(add_analysis_lib_path, int, (const char*), "gambit_add_analysis_lib_path", "add_analysis_lib_path")

// End
#include "gambit/Backends/backend_undefs.hpp"

#endif // EXCLUDE_HEPMC
#endif // EXCLUDE_YODA
