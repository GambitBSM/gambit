//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the Acropolis backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2021 Oct
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Oct
///
///  *********************************************

#define BACKENDNAME Acropolis
#define BACKENDLANG Python3
#define VERSION 1.2.1
#define SAFE_VERSION 1_2_1
#define REFERENCE Depta:2020mhj,Depta:2020zbh,Hufnagel:2018bjp

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_CONV_FUNCTION(set_input_params, void, (bool,int,int,double), "set_input_params")
  BE_CONV_FUNCTION(abundance_photodisintegration_decay, void,(double*,double*,double*,double*,double,double,double,double,double,int), "abundance_photodisintegration_decay")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
