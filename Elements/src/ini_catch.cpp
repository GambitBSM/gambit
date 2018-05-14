//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Micro function useful from all sorts of other
///  initialisation codes.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Feb
///
///  *********************************************

#include <iostream>

#include "gambit/Elements/ini_catch.hpp"

namespace Gambit
{

  /// Catch initialisation exceptions
  void ini_catch(std::exception& e)
  {
    std::cout << "GAMBIT has failed to initialise due to a fatal exception: " << e.what() << std::endl;
    throw(e);
  }

}