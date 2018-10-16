//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the LibThird 1.0 backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/LibThird_1_0.hpp"

BE_INI_FUNCTION {}
END_BE_INI_FUNCTION

BE_NAMESPACE
{
  /* Convenience function implementation */
  double awesomenessNotByAnders(int a)
  {
    logger().send("Message from 'awesomenessNotByAnders' backend convenience function in LibThird v1.0 wrapper",LogTags::info);
    initialize(a);
    someFunction();
    // An example of how to use sub-module variables and functions when they have been declared in
    // advance to GAMBIT (i.e. in a frontend header).
    *SomeOtherInt = a;
    cout << "someOtherInt in LibThird 1.0: " << *SomeOtherInt << endl;
    double result = someOtherFunction(*SomeOtherInt);
    cout << "someOtherFunction(someOtherInt) in LibThird 1.0: " << result << endl;
    return result;
  }
}
END_BE_NAMESPACE
