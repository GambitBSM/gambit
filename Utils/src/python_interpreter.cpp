//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementations of python_interpreter class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2023 Jun
///
///  *********************************************

#include "gambit/Utils/python_interpreter.hpp"

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/embed.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"
  #include "gambit/Logs/logger.hpp"
  
  
  namespace Gambit
  {
  
    namespace Utils
    {
  
      /// Singleton accessor function 
      python_interpreter& python_interpreter::get()
      {
        // This is guaranteed to be threadsafe by C++11
        static python_interpreter s;
        return s;
      }
  
      /// Regular constructor. No access as it is private.
      python_interpreter::python_interpreter()
      {
        // Start the interpreter
        iptr = new pybind11::scoped_interpreter;
        // Import the sys module, and save a wrapper to it for later.
        static pybind11::module local_sys = pybind11::module::import("sys");
        sys = &local_sys;
        // Import the os module, and save a wrapper to it for later.
        static pybind11::module local_os = pybind11::module::import("os");
        os = &local_os; 
        logger() << LogTags::utils << LogTags::debug << "Python interpreter successfully started." << EOM;                  
      }
      
      /// Regular destructor. No access as it is private.
      python_interpreter::~python_interpreter()
      {
        // This still causes a segfault :(
        // delete iptr;
      }
  
      /// Interpreter guard constructor
      python_interpreter_guard::python_interpreter_guard() { python_interpreter::get(); }
      
    }
  
  }

#endif
