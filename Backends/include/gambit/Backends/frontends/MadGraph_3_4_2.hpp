//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example frontend header for the MadGraph  
///  backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2021
///
///  *********************************************


#define BACKENDNAME MadGraph
#define BACKENDLANG Python3
#define VERSION 3.4.2
#define SAFE_VERSION 3_4_2
#define REFERENCE Stelzer:1994ta,Maltoni:2002qb,Alwall:2007st,Alwall:2011uj

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_FUNCTION(MG_RunEvents_pydict, int, (str&, str&, std::vector<str>&, PyDict&, int&), "MG_RunEvents", "MG_RunEvents_pydict")

#endif

  BE_CONV_FUNCTION(MG_RunEvents, int, (str&, str&, std::vector<str>&, std::map<str, double>&, int&), "MG_RunEvents")

#include "gambit/Backends/backend_undefs.hpp"

