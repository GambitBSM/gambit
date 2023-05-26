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

  BE_FUNCTION(MG_RunEvents, int, (str&, str&, std::vector<str>&), "MG_RunEvents", "MG_RunEvents")

#endif

#include "gambit/Backends/backend_undefs.hpp"

