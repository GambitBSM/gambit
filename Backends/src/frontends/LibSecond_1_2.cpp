//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the LibSecond 1.2 backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Nov
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/LibSecond_1_2.hpp"

BE_INI_FUNCTION {}
END_BE_INI_FUNCTION

BE_NAMESPACE
{
  /* Convenience function implementation */
  double awesomenessNotByAnders(int a)
  {
    logger().send("Message from 'awesomenessNotByAnders' backend convenience function in LibSecond v1.2 wrapper",LogTags::info);
    initialize(a);
    someFunction();
    #ifdef HAVE_PYBIND11
      double i = pybind11::cast<double>(LibSecond.attr("hiddenFunction")(2.0));
      std::cout << "Result of hiddenFunction by direct access to LibSecond v1.2 python module (skipping frontend): " << i << std::endl;
    #endif
    return returnResult();
  }
}
END_BE_NAMESPACE
