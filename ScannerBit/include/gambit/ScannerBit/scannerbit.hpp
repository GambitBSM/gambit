//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit executable-level header file.
///  Include this in your main program that calls
///  ScannerBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __ScannerBit_hpp__
#define __ScannerBit_hpp__

#include "gambit/ScannerBit/scan.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/Utils/static_members.hpp"

namespace Gambit
{

  namespace Scanner
  {

    int register_ScannerBit_handlers()
    {
      try
      {
        error e = scan_error();
        warning w = scan_warning();
      }
      catch (std::exception& e)
      {
        std::cout << "ScannerBit has failed to initialise due to a fatal exception: " << e.what() << std::endl;
        throw(e);
      }
      return 0;
    }

    int ScannerBit_handlers = register_ScannerBit_handlers();

  }

}

#endif //#ifndef __ScannerBit_hpp__
