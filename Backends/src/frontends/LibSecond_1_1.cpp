//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the LibSecond 1.1 backend.
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
#include "gambit/Backends/frontends/LibSecond_1_1.hpp"

BE_INI_FUNCTION {}
END_BE_INI_FUNCTION

BE_NAMESPACE
{
  /* Convenience function implementation */
  double awesomenessNotByAnders(int a)
  {
    logger().send("Message from 'awesomenessNotByAnders' backend convenience function in LibSecond v1.1 wrapper",LogTags::info);
    initialize(a);
    someFunction();
    double i = pybind11::cast<double>(LibSecond.attr("hiddenFunction")(2.0));
    std::cout << "Result of hiddenFunction by direct access to LibSecond v1.1 python module (skipping frontend): " << i << std::endl;
    return returnResult();
  }
}
END_BE_NAMESPACE
