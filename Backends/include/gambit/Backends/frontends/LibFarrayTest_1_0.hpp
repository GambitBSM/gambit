//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A fortran backend-frontend example, showing
///  how to use the special GAMBIT fortran variable
///  types, in particular fortran arrays.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Lars A. Dal
///
///  *****************************************


#define BACKENDNAME LibFarrayTest
#define BACKENDLANG FORTRAN
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE GAMBIT:2017yxo

LOAD_LIBRARY

BE_VARIABLE(commonBlock, libFarrayTest_CB_type, "commonblock_", "libFarrayTestCommonBlock")
BE_VARIABLE(commonBlock2, libFarrayTest_CB2_type, "commonblock2_", "libFarrayTestCommonBlock2")
BE_VARIABLE(commonBlock3, libFarrayTest_CB3_type, "commonblock3_", "libFarrayTestCommonBlock3")

BE_FUNCTION(printStuff, void, (), "printstuff_", "libFarrayTest_printStuff")

BE_FUNCTION(fillArrays, void, (), "fillarrays_", "libFarrayTest_fillArrays")

BE_FUNCTION(fptrRoutine, void, (Farray< Fdouble,1,3>&, Finteger&, Fdouble(*)(Farray< Fdouble,1,3>&) ), "fptrroutine_", "libFarrayTest_fptrRoutine")

BE_FUNCTION(doubleFuncArray, Fdouble, (Farray< Fdouble,1,3>&), "doublefuncarray_", "libFarrayTest_doubleFuncArray")

// The doubleFuncArray2 function is identical to doubleFuncArray.
// This is an alternative way to declare and use the function (see ExampleBit A).
// This version should only be used in very special cases, where you need to pass arrays with different index ranges than those specified in the function.
// (But you should know what you are doing!)
BE_FUNCTION(doubleFuncArray2, Fdouble, (Fdouble*), "doublefuncarray2_", "libFarrayTest_doubleFuncArray2")

BE_FUNCTION(doubleFuncArray3, Fdouble, (Farray<Fdouble, 1,2, 2,3>&), "doublefuncarray3_", "libFarrayTest_doubleFuncArray3")

BE_FUNCTION(testcomplex, void, (Fcomplex16&, Freal8&, Freal8&), "testcomplex_", "libFarrayTest_testcomplex")

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

