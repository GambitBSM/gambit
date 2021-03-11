//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple struct for triggering initialisation
///  code.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott 
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************


#ifndef __ini_code_struct_hpp__
#define __ini_code_struct_hpp__

#include <exception>
#include <string>

#include "gambit/Elements/terminator.hpp"

namespace Gambit
{

  /// A container for a function that needs to be constructed at compile
  /// and executed as initialisation code at startup.
  struct ini_code
  {

    ini_code(std::string location, void (*unroll)())
    {
      std::set_terminate(terminator);
      try
      {
        (*unroll)();
      }
      catch (const std::exception& e)
      {
        std::cout << "GAMBIT has failed to initialise due to fatal exception: " << e.what() << std::endl;
        std::cout << "raised from ini_code_struct declared at: " << location << std::endl;
        throw(e);
      }
    }

    ini_code(void (*unroll)())
    {
      std::set_terminate(terminator);
      try
      {
        (*unroll)();
      }
      catch (const std::exception& e)
      {
        std::cout << "GAMBIT has failed to initialise due to fatal exception: " << e.what() << std::endl;
        throw(e);
      }
    }

  };
  
}

#endif //#ifndef__ini_code_struct_hpp__
