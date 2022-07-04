//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A fortran backend-frontend example.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Anders Kvellestad
///
///  *****************************************


#define BACKENDNAME LibFortran
#define BACKENDLANG FORTRAN
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE GAMBIT:2017yxo

LOAD_LIBRARY

BE_FUNCTION(runMe, void, ( double (*)(int&), int&), "runme_", "runMe")
BE_FUNCTION(externalFunction, double, (int&), "externalfunction_", "externalFunction")
BE_FUNCTION(externalFunction2, double, (int&, const double&), "externalfunction2_", "externalComplicatedFunction")

// Tests for Torsten
BE_FUNCTION(average, double, (double(*)(double&), int&), "average_", "average")
BE_FUNCTION(funcGauss, double, (double&), "funcgauss_", "funcGauss")
BE_FUNCTION(funcBE, double, (double&), "funcbe_", "funcBE")

//Notes: fortran arguments must always be TYPE& for passing by reference , const TYPE& for
//passing by value, except for function pointers, which go directly by value.  The arguments
//of the functions to which pointers are being sent must be passed by reference in order
//for fortran to be able to use them.  It apparently makes no difference whether they are
//passed as const or not.

namespace Gambit
{
  namespace Backends
  {
    namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
    {

      /* Convenience functions go here */

    } /* end namespace BACKENDNAME_SAFE_VERSION */
  } /* end namespace Backends */
} /* end namespace Gambit */

BE_INI_FUNCTION{}
END_BE_INI_FUNCTION

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

