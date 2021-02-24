//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  List of headers that define classes, typedefs
///  and so forth needed for module, model and 
///  backend co-operation with the GAMBIT core. 
///  If you need to add a new type, how you do 
///  this depends on what the type is associated
///  with.  Guidelines are given below.
///
///  Bear in mind throughout that normal C/C++ rules
///  apply: if your new type is never going to be
///  used except as a local convenience in your new
///  module/backend/model, then there is no need to 
///  do anything more than put it in a header and 
///  \code #include \endcode that from wherever you
///  plan to use it, as per standard programming practice.
///  You should only have to bother with the 
///  instructions below if GAMBIT or its other 
///  modules/backends/models need to be aware of this
///  new type.  That would typically be the case when
///  your new type is to be used in more than one 
///  module/backend/model, or if it is to be used for 
///  passing things back and forth between modules,  
///  backends and/or models, e.g. if it is the result
///  or argument type of a backend function, module 
///  function or module dependency.
///  
///  Explicit instructions for adding new types:
///
///  MODELS
///  ------
///  To add a new type that will be used exclusively to 
///  communicate with some model X, declare it in a header
///   Models/include/gambit/Models/model_types/X_types.hpp,
///  and include that file from Models/include/gambit/Models/models/X.hpp.
///  X_types will be automatically included in 
///  Models/include/gambit/Models/model_types_rollcall.hpp by the GAMBIT
///  model harvester.
///
///  MODULES
///  -------
///  To add a new type that will be used exclusively to 
///  communicate with some module Y, declare it in a header
///   Y/include/gambit/Y/Y_types.hpp,
///  and include that file from Y/include/gambit/Y/Y_rollcall.hpp.
///  Y_types will be automatically included in 
///  Elements/include/gambit/Elements/module_types_rollcall.hpp
///  by the GAMBIT module harvester.
///
///  BACKENDS
///  --------
///  To add a new type that will be used to communicate
///  with a backend Z, declare it in a header
///   Backends/include/gambit/Backends/backend_types/Z_types.hpp
///  Z_types will be automatically included in 
///  Backends/include/gambit/Backends/backend_types_rollcall.hpp 
///  by the GAMBIT backend harvester.
///
///  MIXED-USE TYPES
///  --------------- 
///  If the type will be used by multiple modules, 
///  multiple models or multiple backends, or any 
///  mixture thereof, make some header 
///   Elements/include/gambit/Elements/__your_header_name__.hpp
///  that declares the type, and include
///  that header by hand from 
///   Elements/include/gambit/Elements/shared_types.hpp.
///  
///  PRINTING
///  --------
///  Remember also that if you want to be able to
///  spit instances of your new type out to a file 
///  or other output medium, you will need to add 
///  specialisations for it in the various printers
///  included in 
///   Utils/include/gambit/Utils/printers_rollcall.hpp.
///
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott  
///          (patscott@physics.mcgill.ca)
///  \date 2013 Oct
///  \date 2014 Mar, Nov
///
///  *********************************************

#ifndef __types_rollcall_hpp__
#define __types_rollcall_hpp__

#include "gambit/Elements/shared_types.hpp"          // All the shared types
#include "gambit/Elements/module_types_rollcall.hpp" // Module-specific types
#include "gambit/Models/model_types_rollcall.hpp"    // Model-specific types

#endif /* defined __types_rollcall_hpp__ */
