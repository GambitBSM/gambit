//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions specifically for triggering
///  backend initialisation code.
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

#ifndef __ini_functions_backends_hpp__
#define __ini_functions_backends_hpp__

#include <vector>
#include <exception>
#include <dlfcn.h>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Elements/ini_catch.hpp"

/// Define the separator to use instead of "::" when macros get gnarly.
#define NS_SEP ___no_apologies_for_rocking_macros___


namespace Gambit
{
  // Forward declarations
  class functor;
  class module_functor_common;

  /// Get back the "::" from things that use NS_SEP instead
  str fixns(str);

  /// Call push back on a vector of strings
  int vectorstr_push_back(std::vector<str>&, str);

  /// Notify a backend functor of which models it can be used with
  int set_allowed_models(functor&, std::vector<str>&, str);

  /// Register a backend with the logging system
  int register_backend_with_log(str);

  /// Register a BOSSed type with the rollcall system
  int register_type(str bever, str classname);

  /// Disable a backend functor if its library is missing or the symbol cannot be found.
  int set_backend_functor_status(functor&, const std::vector<str>&);

  /// Disable a backend initialisation function if the backend is missing.
  int set_BackendIniBit_functor_status(functor&, str, str);

  /// Get the status of a factory pointer to a BOSSed type's wrapper constructor.
  int get_ctor_status(str, str, str, str, str, const std::vector<str>&);

  /// Set a backend rule for one or more models.
  int set_backend_rule_for_model(module_functor_common&, str, str);

  /// Set the classloading requirements of a given functor.
  int set_classload_requirements(module_functor_common&, str, str, str);

  namespace Backends
  {

    /// Simplify pointers to void functions
    typedef void(*voidFptr)();

    /// Hack to suppress warnings about casting between void pointers and function pointers.
    /// "Necessary" as long as dlsym has no separate functionality for retrieving function pointers.
    union void_voidFptr
    {
      void *ptr;      // Use this for objects
      voidFptr fptr;  // Use this for functions
    };

    /// Get the pointer to the backend function.
    template <typename T>
    T load_backend_symbol(const std::vector<str>& symbol_names, str be, str ver)
    {
      T result = nullptr;
      try
      {
        // Get the pointer to the backend
        bool works = backendInfo().works.at(be+ver);
        void* pHandle = works ? backendInfo().loaded_C_CXX_Fortran_backends.at(be+ver) : NULL ;
        // Clear error code by calling dlerror()
        dlerror();
        // Attempt to obtain a void pointer (pSym) to one of the library symbols.
        void_voidFptr pSym;
        for (auto& name : symbol_names)
        {
          pSym.ptr = dlsym(pHandle, name.c_str());
          if (pSym.ptr != NULL) break;
        }
        // If using backwards systems missing dlinfo(), like OSX, determine the path to the library with dladdr()
        #ifndef HAVE_LINK_H
          // Don't bother trying if the symbol wasn't found in the library anyway.
          if (pSym.ptr != NULL)
          {
            Dl_info info;
            int dladdr_result = dladdr(pSym.ptr, &info);
            // Try overriding the path to the library if dladdr seemed to return OK.
            if (dladdr_result) backendInfo().attempt_backend_path_override(be, ver, info.dli_fname);
          }
        #else
          // Do something inconsequential with the last two args to skip compiler warnings.
          (void)be;
          (void)ver;
        #endif
        // Hand over the pointer
        result = reinterpret_cast<T>(pSym.fptr);
      }
      catch (std::exception& e) { ini_catch(e); }
      return result;
    }

    /// Provide the factory pointer to a BOSSed type's wrapper constructor.
    template <typename T>
    T handover_factory_pointer(str be, str ver, str name, str barename,
                               str args, const std::vector<str>& symbol_names, T factory,
                               T missing_backend, T missing_factory)
    {
      try
      {
        int status = get_ctor_status(be, ver, name, barename, args, symbol_names);
        switch(status)
        {
          case  0: return factory;
          case -1: return missing_backend;
          case -2: return missing_factory;
        }
      }
      catch (std::exception& e) { ini_catch(e); }
      return missing_factory;
    }

  }

}

#endif // #defined __ini_functions_backends_hpp__
