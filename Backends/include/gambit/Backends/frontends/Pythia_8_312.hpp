//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for GAMBIT backend Pythia 8.312.
///
///  The backend library is a plugin, libpythia_plugin.so, built from
///  Backends/src/frontends/plugins/pythia_plugin.cpp as part of the Pythia
///  build. It implements ColliderBit's BaseCollider interface
///  (ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp) on
///  top of Pythia, and exports the two functions declared below. See
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

#ifndef EXCLUDE_HEPMC

#include "gambit/Backends/backend_types/Pythia_8_312/identification.hpp"

LOAD_LIBRARY

#include "gambit/ColliderBit/colliders/BaseCollider.hpp"

/// Version of the BaseCollider interface the plugin was built against; checked at scan start.
BE_FUNCTION(collider_interface_version, int, (), "gambit_collider_interface_version", "collider_interface_version")

/// Create a Pythia-based collider. GAMBIT keeps the instance for the rest of the run.
BE_FUNCTION(create_collider, Gambit::ColliderBit::BaseCollider*, (), "gambit_create_collider", "create_collider")

// End
#include "gambit/Backends/backend_undefs.hpp"

#endif // EXCLUDE_HEPMC
