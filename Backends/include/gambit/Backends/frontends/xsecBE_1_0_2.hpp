//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the xsecBE backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep
///  \date 2020 Dec
///
///  *********************************************


#define BACKENDNAME xsecBE
#define BACKENDLANG Python
#define VERSION 1.0.2
#define SAFE_VERSION 1_0_2

/* The following macro imports the modude in the Python interpreter
 * when this header file is included somewhere. */

LOAD_LIBRARY

/* Next we use macros BE_VARIABLE and BE_FUNCTION to extract pointers
 * to the variables and functions within the Python module.
 *
 * The macros create functors that wrap the library variables and functions.
 * These are used by the Core for dependency resolution and to set up a suitable
 * interface to the library functions/variables at module level. */

/* Syntax for BE_FUNCTION (same as for any other backend):
 * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]")
 */

BE_FUNCTION(import_slha_string, void, (std::string&), "import_slha_string", "xsecBE_import_slha_string")
BE_FUNCTION(set_parameters, void, (PyDict&), "set_parameters", "xsecBE_set_parameters")
BE_FUNCTION(get_xsection, PyDict, (iipair&), "get_xsection", "xsecBE_get_xsection")



/* At this point we have a minimal interface to the loaded library.
 * Any additional convenience functions could be constructed below
 * using the available pointers. All convenience functions must be
 * registred/wrapped via the macro BE_CONV_FUNCTION (see below). */

// BE_NAMESPACE
// {
  /* Convenience functions go here */
// }
// END_BE_NAMESPACE

/* Now register any convenience functions and wrap them in functors.
 *
 * Syntax for BE_CONV_FUNCTION:
 * BE_CONV_FUNCTION([function name], type, (arguments), "[choose capability name]") */

// BE_INI_FUNCTION {}
// END_BE_INI_FUNCTION

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

