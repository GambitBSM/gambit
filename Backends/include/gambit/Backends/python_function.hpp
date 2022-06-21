//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Templated class for holding and executing
///  pointers to Python backends.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************

#ifndef __python_function_hpp__
#define __python_function_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/ini_catch.hpp"
#include "gambit/Backends/python_helpers.hpp"
#include "gambit/Backends/backend_singleton.hpp"


namespace Gambit
{
  namespace Backends
  {

    /// Holds the info about a python backend function, and defines conversion functions.
    template <typename TYPE, typename... ARGS>
    class python_function
    {

      private:

        #ifdef HAVE_PYBIND11

          /// Wrapper to the function
          pybind11::object func;

          /// Indication of whether or not the function has been successfully loaded
          bool handle_works;

        #endif

      public:

        /// Constructor
        #ifndef HAVE_PYBIND11
          python_function(const str&, const str&, const str&) {}
        #else
          python_function(const str& be, const str& ver, const str& symbol) : handle_works(false)
          {
            try
            {
              // Extract the backend module pointer from the backendInfo object
              pybind11::object* mod;
              if (backendInfo().works.at(be+ver))
              {
                mod = backendInfo().loaded_python_backends.at(be+ver);
              }
              else
              {
                mod = (pybind11::module*)0;
                return;
              }

              // Work out if this is a function in the main part of the package, or in a sub-module
              sspair module_and_name = split_qualified_python_name(symbol, backendInfo().lib_name(be, ver));

              // Extract the function from the module
              try
              {
                if (module_and_name.first.empty())
                {
                  func = mod->attr(symbol.c_str());
                }
                else
                {
                  pybind11::module sub_module = pybind11::module::import(module_and_name.first.c_str());
                  func = sub_module.attr(module_and_name.second.c_str());
                }
                handle_works = true;
              }
              catch (std::exception& e)
              {
                std::ostringstream err;
                err << "Failed to retrieve handle to function " << symbol << " from Python module for " << be+ver << endl
                    << "The backend function from this symbol will be disabled (i.e. get status = -2)." << endl
                    << "Python error was: " << e.what() << endl;
                backend_warning().raise(LOCAL_INFO, err.str());
                backendInfo().dlerrors[be+ver] = symbol;
              }
            }
            catch (std::exception& e) { ini_catch(e); }
          }
        #endif

        /// Operation (execute function and return value)
        #ifdef HAVE_PYBIND11
          TYPE operator()(ARGS&&... args)
          {
            if (not handle_works) backend_error().raise(LOCAL_INFO, "Attempted to call a Python backend function that was not successfully loaded.");
            pybind11::object result = func(std::forward<ARGS>(args)...);
            return return_cast<TYPE>(result);
          }
        #else
          TYPE operator()(ARGS&&...)
          {
            backend_error().raise(LOCAL_INFO, "Attempted to call a python function from C++ without pybind11.");
            return TYPE();
          }
        #endif

    };

  }

}

#endif /* __python_function_hpp__ */
