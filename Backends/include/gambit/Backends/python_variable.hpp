//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class python_variable, needed to overload
///  constructor and assignment operators to send
///  messages through pybind11.
///
///  ***********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  ***********************************************

#ifndef __python_variable_hpp__
#define __python_variable_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/ini_catch.hpp"
#include "gambit/Backends/python_helpers.hpp"
#include "gambit/Backends/backend_singleton.hpp"


namespace Gambit
{

  /// Holds the info about a python backend variable, and defines conversion functions.
  template <typename TYPE>
  class python_variable
  {

    private:

      #ifdef HAVE_PYBIND11

        /// Wrapper for the Python dictionary of internal module variables
        pybind11::dict _dict;

        /// Name of the variable inside the Python module
        str _symbol;

        /// Indication of whether or not the function has been successfully loaded
        bool handle_works;

      #endif

    public:

      /// Constructor
      #ifndef HAVE_PYBIND11
        python_variable(const str&, const str&, const str&) {}
      #else
        python_variable(const str& be, const str& ver, const str& symbol) : handle_works(false)
        {
          using namespace Backends;
          try
          {
            // Extract the backend module pointer from the backendInfo object
            pybind11::module* mod;
            if (backendInfo().works.at(be+ver))
            {
              mod = backendInfo().loaded_python_backends.at(be+ver);
            }
            else
            {
              mod = (pybind11::module*)0;
              return;
            }

            // Work out if this is a variable in the main part of the package, or in a sub-module
            sspair module_and_name = split_qualified_python_name(symbol, backendInfo().lib_name(be, ver));
            _symbol = module_and_name.second;

            // Extract the wrapper to the module's internal dictionary
            try
            {
              if (module_and_name.first.empty())
              {
                _dict = mod->attr("__dict__");
              }
              else
              {
                pybind11::module sub_module = pybind11::module::import(module_and_name.first.c_str());
                _dict = sub_module.attr("__dict__");
              }
              handle_works = true;
            }
            catch (std::exception& e)
            {
              std::ostringstream err;
              err << "Failed to retrieve handle to dictionary (containing variable " << _symbol << ") from Python module for " << be+ver << endl
                  << "The backend variable associated with this symbol will be disabled (i.e. get status = -2)." << endl
                  << "Python error was: " << e.what() << endl;
              backend_warning().raise(LOCAL_INFO, err.str());
              backendInfo().dlerrors[be+ver] = _symbol;
            }
          }
          catch (std::exception& e) { ini_catch(e); }
        }
      #endif

      /// Assignment operator for python_variable from equivalent C++ type
      #ifdef HAVE_PYBIND11
        python_variable& operator=(const TYPE& val)
        {
          if (not handle_works) backend_error().raise(LOCAL_INFO, "Attempted to use a Python backend variable that was not successfully loaded.");
          _dict[_symbol.c_str()] = val;
          return *this;
        }
      #else
        python_variable& operator=(const TYPE&)
        {
          backend_error().raise(LOCAL_INFO, "Attempted to assign a C++ type to a python_variable without pybind11.");
          return *this;
        }
      #endif

      /// Cast operator from python_variable to equivalent C++ type
      operator TYPE const()
      {
        #ifdef HAVE_PYBIND11
          if (not handle_works) backend_error().raise(LOCAL_INFO, "Attempted to use a Python backend variable that was not successfully loaded.");
          pybind11::object result = _dict[_symbol.c_str()];
          return result.cast<TYPE>();
        #else
          backend_error().raise(LOCAL_INFO, "Attempted to cast a python_variable to a C++ type without pybind11.");
          return TYPE();
        #endif
      }

  };

}

#endif /* __python_variable_hpp__ */
