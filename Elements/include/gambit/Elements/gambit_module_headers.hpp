//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Header file that includes all GAMBIT
///  headers required for a module source file.
///  This is the only GAMBIT header you should 
///  ever need to include explicitly
///  in your module source file, apart from 
///  a) the rollcall header for your module
///  b) any new headers that you have created 
///     yourself for your module.  
///  These should typically reside in 
///    <your_module's_name>/include/
///    gambit/<your_module's_name>.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott 
///          (patscott@physics.mcgill.ca)
///  \date 2013 Aug, Oct
///
///  *********************************************

#ifndef __gambit_module_headers_hpp__
#define __gambit_module_headers_hpp__

#ifdef __module_macros_incore_hpp__
  FAIL("You cannot include gambit_module_headers.hpp from a rollcall header, only from module source files.")
#endif
#ifdef __module_rollcall_hpp__
  FAIL("You cannot include gambit_module_headers.hpp from a rollcall header, only from module source files.")
#endif

#include "gambit/Elements/module_macros_inmodule.hpp"
#include "gambit/Elements/shared_types.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Backends/backend_singleton.hpp"

#endif /* defined(__gambit_module_headers_hpp__) */
