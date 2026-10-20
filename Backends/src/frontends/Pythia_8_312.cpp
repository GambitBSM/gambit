//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the Pythia 8.312 backend.
///
///  Pythia needs no point-level initialisation. The scan-level
///  initialisation checks that the plugin library GAMBIT loaded was built
///  against the same version of ColliderBit's BaseCollider interface as
///  GAMBIT itself. A mismatch would otherwise surface as a crash, or as
///  silently wrong behaviour, the first time a method is called.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"

#ifndef EXCLUDE_HEPMC

#include "gambit/Backends/frontends/Pythia_8_312.hpp"

#include <sstream>

BE_INI_FUNCTION
{
  static bool scan_level = true;
  if (scan_level)
  {
    scan_level = false;

    if (create_collider == nullptr || collider_interface_version == nullptr)
    {
      backend_error().raise(LOCAL_INFO, "The Pythia plugin library (libpythia_plugin.so) does not export the functions "
       "gambit_create_collider and gambit_collider_interface_version. It is probably stale; rebuild it with 'make pythia'.");
    }

    const int plugin_version = collider_interface_version();
    if (plugin_version != COLLIDERBIT_COLLIDER_INTERFACE_VERSION)
    {
      std::ostringstream msg;
      msg << "The Pythia plugin library (libpythia_plugin.so) was built against version " << plugin_version
          << " of ColliderBit's BaseCollider interface (ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp), "
          << "but GAMBIT was compiled with version " << COLLIDERBIT_COLLIDER_INTERFACE_VERSION
          << ". Rebuild the plugin with 'make pythia'.";
      backend_error().raise(LOCAL_INFO, msg.str());
    }
  }
}
END_BE_INI_FUNCTION

#endif // EXCLUDE_HEPMC
