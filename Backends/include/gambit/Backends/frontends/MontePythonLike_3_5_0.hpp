//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the MontePython backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 June, 2020 May
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************

#define BACKENDNAME MontePythonLike
#define BACKENDLANG Python
#define VERSION 3.5.0
#define SAFE_VERSION 3_5_0
#define REFERENCE Audren:2012wb,Brinckmann:2018cvx

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_CONV_FUNCTION(get_MP_available_likelihoods,  std::vector<str>, (), "get_MP_available_likelihoods")
  BE_CONV_FUNCTION(check_likelihood_classy_combi,  void, (str&,str&), "check_likelihood_classy_combi")
  BE_CONV_FUNCTION(check_likelihood_support,  void, (str&), "check_likelihood_support")
  BE_CONV_FUNCTION(get_MP_loglike, double, (const MPLike_data_container&, pybind11::object&, std::string&), "get_MP_loglike")
  BE_CONV_FUNCTION(create_MP_data_object, pybind11::object, (map_str_str&), "create_MP_data_object")
  BE_CONV_FUNCTION(create_MP_likelihood_objects,  map_str_pyobj, (pybind11::object&, map_str_str&), "create_MP_likelihood_objects")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
