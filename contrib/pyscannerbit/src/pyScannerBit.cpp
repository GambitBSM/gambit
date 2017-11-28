//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Python interface for ScannerBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2017 Nov
///
///  *********************************************

#include <iostream>
#include <pybind11/pybind11.h>
#include "gambit/ScannerBit/ScannerBit_CAPI.h"

namespace py = pybind11;

void py_hello_world()
{
   // Call library function
   hello_world();
} 

py::object user_pyfunc; // Global variable defining the users chosen Python likelihood function

/// Wrapper for user-supplied likelihood function from Python
double wrapper_func(const std::unordered_map<std::string, double>& pars) 
{
   // Move the input parameters into a Python dictionary for access in the user's Python function
   //std::cout << "Parameter values:" << std::endl;
   py::dict params; 
   for (std::unordered_map<std::string, double>::const_iterator it = pars.begin(); it != pars.end(); ++it)
   {
     params[py::cast(it->first)] = py::cast(it->second);
   }
 
   // Call user-defined Python likelihood function and convert result to a double
   py::object pyr = user_pyfunc(params);
   double r = pyr.cast<double>();
   //std::cout << "result: " << r << std::endl;

   return r; // Rubbish for now, just see if it works 
}

void py_run_scan(const char yaml_file[], const py::object& f)
{
   // Set user-defined Python function for callbacks
   user_pyfunc = f;   

   // Call library function
   run_scan_from_file(yaml_file,&wrapper_func);
}

PYBIND11_PLUGIN(pyscannerbit)
{
    py::module m("pyscannerbit");
    m.def("hello", &py_hello_world);
    m.def("run_scan", &py_run_scan);
    return m.ptr();
}
