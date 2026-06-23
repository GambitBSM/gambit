//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the simplexs backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Chang
///          (christopher.chang@uqconnect.edu.au)
///  \date 2020 Feb
///
///  *********************************************


#define BACKENDNAME simple_xs
#define BACKENDLANG Python
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE Bozzi:2007qr,Fuks:2013vua,Fuks:2013lya,Fiaschi:2019zgh,Debove:2010kf,Fuks:2012qx,Fiaschi:2018hgm,Beenakker:2016lwe


LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_FUNCTION(init, void, (PyDict&), "init", "simplexs_init")
  BE_FUNCTION(get_xsection, PyDict, (PyDict&, PyDict&), "get_xsection", "simplexs_get_xsection")
  
#endif

#include "gambit/Backends/backend_undefs.hpp"

















