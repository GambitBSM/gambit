//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the Pythia 8.312 backend.
///
///  Pythia needs no scan-level initialisation of its own (unlike Rivet,
///  which has to register its analysis library path) -- this file exists
///  only because LOAD_LIBRARY (in
///  Backends/include/gambit/Backends/frontends/Pythia_8_312.hpp) declares
///  a BackendIniBit::Pythia_8_312_init() function that something has to
///  define, win or lose.
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
#include "gambit/Backends/frontends/Pythia_8_312.hpp"

BE_INI_FUNCTION {}
END_BE_INI_FUNCTION
