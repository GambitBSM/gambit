//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the DarkAges backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Oct
///
///  *********************************************


#define BACKENDNAME DarkAges
#define BACKENDLANG Python
#define VERSION 1.2.0
#define SAFE_VERSION 1_2_0

LOAD_LIBRARY

BE_ALLOW_MODELS(AnnihilatingDM_general, DecayingDM_general)

/* Syntax for BE_FUNCTION (same as for any other backend):
 * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]")
 */

/* --- NONE --- */

/* Syntax for BE_VARIABLE:
 * BE_VARIABLE([name], [type], "[exact symbol name]", "[choose capability name]")
 * */

 /* --- NONE --- */

/* We use BE_INI_DEPENDENCY, since DarkAges needs the spectra of injected electrons, positrons and photons
 * to calculate f(z)
 * */

#ifdef HAVE_PYBIND11

  BE_INI_DEPENDENCY(energy_injection_spectrum, DarkAges::Energy_injection_spectrum)

  /* Now register any convenience functions and wrap them in functors.
   *
   * Syntax for BE_CONV_FUNCTION:
   * BE_CONV_FUNCTION([function name], type, (arguments), "[choose capability name]") */

  BE_CONV_FUNCTION(get_energy_injection_efficiency_table, DarkAges::Energy_injection_efficiency_table, (), "get_energy_injection_efficiency_table")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
