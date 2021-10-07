//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of how to use the macros in
///  'backend_macros.hpp' to set up a frontend for
///  a Python library.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************


#define BACKENDNAME LibSecond
#define BACKENDLANG Python
#define VERSION 1.2
#define SAFE_VERSION 1_2
#define REFERENCE GAMBIT:2017yxo

/* The following macro imports the module in the Python interpreter
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

BE_FUNCTION(initialize, void, (int), "initialize", "initialize_capability")
BE_FUNCTION(someFunction, void, (), "someFunction", "someFunction")
BE_FUNCTION(returnResult, double, (), "returnResult","returnResult_capability")

/* We have now created the following:
 *
 * - Function pointers
 * Gambit::Backends::LibSecond::initialize       type: void (*)(int)
 * Gambit::Backends::LibSecond::someFunction     type: void (*)()
 * Gambit::Backends::LibSecond::returnResult     type: double (*)()
 *
 * - Functors
 * Gambit::Backends::LibSecond::Functown::initialize       type: Gambit::backend_functor<void,int>
 * Gambit::Backends::LibSecond::Functown::someFunction     type: Gambit::backend_functor<void>
 * Gambit::Backends::LibSecond::Functown::returnResult     type: Gambit::backend_functor<double>  */


/* Syntax for BE_VARIABLE:
 * BE_VARIABLE([name], [type], "[exact symbol name]", "[choose capability name]")
 * */

BE_VARIABLE(SomeInt, int, "someInt", "SomeInt")
BE_VARIABLE(SomeDouble, double, "someDouble", "SomeDouble")

/* We have now created the following:
 *
 * - Pointers
 * Gambit::Backends::LibFirst::SomeInt      type: int*
 * Gambit::Backends::LibFirst::SomeDouble   type: double*
 *
 * - Functors
 * Gambit::Backends::LibFirst::Functown::SomeInt      type: Gambit::backend_functor<int>
 * Gambit::Backends::LibFirst::Functown::SomeDouble   type: Gambit::backend_functor<double> */


/* At this point we have a minimal interface to the loaded library.
 * Any additional convenience functions could be constructed below
 * using the available pointers. All convenience functions must be
 * registred/wrapped via the macro BE_CONV_FUNCTION. Implementation
 * of convenience functions can be found in LibSecond_1.1.cpp. */

/* Now register any convenience functions and wrap them in functors.
 *
 * Syntax for BE_CONV_FUNCTION:
 * BE_CONV_FUNCTION([function name], type, (arguments), "[choose capability name]") */

BE_CONV_FUNCTION(awesomenessNotByAnders, double, (int), "awesomeness")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

