//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of how to use the macros in
///  'backend_macros.hpp' to set up a frontend for
///  a specific library.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///  \date 2013 Mar, Apr
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr
///  \date 2014 May
///
///  *********************************************

#define BACKENDNAME LibFirst
#define BACKENDLANG CXX
#define VERSION 1.1
#define SAFE_VERSION 1_1

// Begin
LOAD_LIBRARY

// Set models that this backend can be used with.  If absent, all models are allowed.
BE_ALLOW_MODELS(NUHM1,ScalarSingletDM_Z3,WC)

// Functions
BE_FUNCTION(initialize, void, (int), "_Z10initializei", "initialize_capability")
BE_FUNCTION(someFunction, void, (), "_Z12someFunctionv", "someFunction", (NUHM1,WC))
BE_FUNCTION(returnResult, double, (), "_Z12returnResultv","returnResult_capability")
BE_FUNCTION(byRefExample, double, (double&), "_Z12byRefExampleRd", "refex")
BE_FUNCTION(byRefExample2, void, (double&, double), "_Z13byRefExample2Rdd", "refex2")
BE_FUNCTION(nastyExample, double, (int, etc), "_Z12nastyExampleiz", "varex")
BE_FUNCTION(arrayarg_1D, double, (double*), "_Z11arrayarg_1DPd", "example_be_array_1D")
BE_FUNCTION(arrayarg_2D, double, (double(*)[10]), "_Z11arrayarg_2DPA10_d", "example_be_array_2D")
BE_FUNCTION(arrayarg_3D, double, (double(*)[10][10]), "_Z11arrayarg_3DPA10_A10_d", "example_be_array_3D")

// Variables
BE_VARIABLE(SomeInt, int, "someInt", "SomeInt", (NUHM1))
BE_VARIABLE(SomeDouble, double, "someDouble", "SomeDouble")
BE_VARIABLE(SomeArray, dblarr, "someArray", "SomeArray")
BE_VARIABLE(SomeVector, std::vector<double>, "someVector", "test_vector")

// Initialisation function (dependencies)
BE_INI_DEPENDENCY(nevents, int)

// Convenience functions (registration)
BE_CONV_FUNCTION(awesomenessByAnders, double, (int), "awesomeness", (NUHM1,ScalarSingletDM_Z3))
BE_CONV_FUNCTION(variadicConvenience, double, (int, etc), "varex2")

// Initialisation function (definition)
BE_INI_FUNCTION
{
  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {
    logger() << "Initialising backend LibFirst, v1.1.  My .so file is in " << backendDir << ".";
    logger() << (*InUse::awesomenessByAnders ? "Ready to bust out some awesomeness." : "No awesomeness shall be forthcoming.") << EOM;
  }
  scan_level = false;

  // Point-level initialisation
  if (*InUse::SomeDouble)
  {
    *SomeDouble = 2.1;
    logger() << "Initialised someDouble to " << *SomeDouble << EOM;
  }
  logger() << "M0 in libfirst v1.1 initialisation function: " << *Param["M0"] << EOM;
  awesomenessByAnders(*Dep::nevents);
}
END_BE_INI_FUNCTION

// Convenience functions (definitions)
BE_NAMESPACE
{
  #include <cstdarg>

  double awesomenessByAnders(int a)
  {
    logger().send("Message from 'awesomenessByAnders' backend convenience function in LibFirst v1.1 wrapper",LogTags::info);
    initialize(a);
    someFunction();
    return returnResult();
  }

  double variadicConvenience(int count, ...)
  {
    double result = *SomeDouble;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
      result += va_arg(args, double);
    }
    va_end(args);
    return result;
  }

}
END_BE_NAMESPACE

// End
#include "gambit/Backends/backend_undefs.hpp"

