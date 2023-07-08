#define BACKENDNAME pbarlike
#define BACKENDLANG Python
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE DarkRayNet:2021

LOAD_LIBRARY

#ifdef HAVE_PYBIND11
    BE_CONV_FUNCTION(c_pbarlike_initialization,pybind11::list,(const bool& ,const std::string& ,const mat_dbl& ), "pbarlike_initialization")
    BE_CONV_FUNCTION(c_pbar_logLikes,map_str_dbl,(double&,  map_str_dbl&, double& ), "drn_pbar_logLikes")
#endif

#include "gambit/Backends/backend_undefs.hpp"
