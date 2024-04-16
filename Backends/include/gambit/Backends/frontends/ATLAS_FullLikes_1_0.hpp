//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example frontend header for the ATLAS_FullLikes 
///  backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///          (christopher.chang@uqconnect.edu.au)
///  \date 2021
///
///  *********************************************


#define BACKENDNAME ATLAS_FullLikes
#define BACKENDLANG Python3
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE ATL-PHYS-PUB-2019-029,pyhf,pyhf_joss


LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_FUNCTION(FullLikes_ReadIn, int, (const str&,const str&), "ReadIn", "FullLikes_ReadIn")
  BE_FUNCTION(FullLikes_FileExists,bool,(const str&),"FileExists","FullLikes_FileExists")
  BE_FUNCTION(FullLikes_Reset,int,(const str&),"Reset","FullLikes_Reset") //TODO: Chris Chang. This is currently not used.
  BE_FUNCTION(FullLikes_Evaluate_pydict, double, (PyDict&,const str&), "Evaluate", "FullLikes_Evaluate_pydict")

#endif

  BE_CONV_FUNCTION(FullLikes_Evaluate, double, (std::map<str,double>&, const str&), "FullLikes_Evaluate")

#include "gambit/Backends/backend_undefs.hpp"

