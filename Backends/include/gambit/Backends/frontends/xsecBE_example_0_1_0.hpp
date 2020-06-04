//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example frontend header for a cross-section 
///  tool written in Python
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep
///
///  *********************************************


#define BACKENDNAME xsecBE_example
#define BACKENDLANG Python3
#define VERSION 0.1.0
#define SAFE_VERSION 0_1_0

/* The following macro imports the module in the Python interpreter
 * when this header file is included somewhere. */

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  /* Next we use macros BE_VARIABLE and BE_FUNCTION to extract pointers
   * to the variables and functions within the Python module.
   *
   * The macros create functors that wrap the library variables and functions.
   * These are used by the Core for dependency resolution and to set up a suitable
   * interface to the library functions/variables at module level. */

  /* Syntax for BE_FUNCTION (same as for any other backend):
   * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]")
   */

  BE_FUNCTION(set_parameters, void, (PyDict&), "set_parameters", "xsecBE_example_set_parameters")
  BE_FUNCTION(set_flags, void, (PyDict&), "set_flags", "xsecBE_example_set_flags")

  BE_FUNCTION(xsec_fb, double, (iipair&, PyDict&, PyDict&), "xsec_fb", "xsecBE_example_xsec_fb")
  BE_FUNCTION(xsec_err_fb, ddpair, (iipair&, PyDict&, PyDict&), "xsec_err_fb", "xsecBE_example_xsec_err_fb")


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

#endif

// BE_INI_FUNCTION {}
// END_BE_INI_FUNCTION

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

