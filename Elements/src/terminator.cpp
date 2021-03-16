//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Garbage collection of last resort.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  \date 2014 Apr
//
///  \author Christoph Weniger
///  \date 2016 Feb
///
///  *********************************************

#include "gambit/Elements/terminator.hpp"

void Gambit::terminator()
{
  std::cout << std::endl << "Gambit has encountered an uncaught error during initialisation." << std::endl;
  std::cout << std::endl << "Check the output logs for details.";
  std::cout << std::endl << "(Unless you see one or more uninitialised logger messages above, these will be in the location specified in your yaml file.)" << std::endl << std::endl;

  std::exception_ptr eptr = std::current_exception();
  try
  {
    std::rethrow_exception(eptr);
  }
  catch (const std::exception &e)
  {
    std::cout << "what(): " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Exception not derived from std::exception." << std::endl;
  }
  exit(1);
}

