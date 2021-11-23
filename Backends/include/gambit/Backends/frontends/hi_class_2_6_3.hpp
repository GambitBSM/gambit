//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the classy backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Chang
///          (christopher.chang@uqconnect.edu.au)
///  \date 2021 November
///
///  *********************************************

#define BACKENDNAME classy //hi_class
#define BACKENDLANG Python
#define VERSION hiclass_2.6.3
#define SAFE_VERSION hiclass_2_6_3

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_CONV_FUNCTION(get_classy_cosmo_object, pybind11::object, (), "get_classy_cosmo_object")
  BE_CONV_FUNCTION(get_classy_backendDir, std::string, (), "get_classy_backendDir")

  BE_CONV_FUNCTION(class_get_rs,        double, (), "class_get_rs")
  BE_CONV_FUNCTION(class_get_tau_reio,  double, (), "class_get_tau_reio")
  BE_CONV_FUNCTION(class_get_z_reio,    double, (), "class_get_z_reio")
  BE_CONV_FUNCTION(class_get_Neff,      double, (), "class_get_Neff")
  BE_CONV_FUNCTION(class_get_sigma8,      double, (), "class_get_sigma8")
  BE_CONV_FUNCTION(class_get_Omega0_r,    double, (), "class_get_Omega0_r")
  BE_CONV_FUNCTION(class_get_Omega0_ur,     double, (), "class_get_Omega0_ur")
  BE_CONV_FUNCTION(class_get_Omega0_m,    double, (), "class_get_Omega0_m")
  BE_CONV_FUNCTION(class_get_Omega0_ncdm_tot, double, (), "class_get_Omega0_ncdm_tot")
  BE_CONV_FUNCTION(class_get_Omega0_Lambda,   double, (), "class_get_Omega0_Lambda")
  BE_CONV_FUNCTION(class_get_H0,              double, (), "class_get_H0")
  BE_CONV_FUNCTION(class_get_Da, double, (double), "class_get_Da")
  BE_CONV_FUNCTION(class_get_Dl, double, (double), "class_get_Dl")
  BE_CONV_FUNCTION(class_get_Hz, double, (double), "class_get_Hz")

  BE_CONV_FUNCTION(class_get_lensed_cl, std::vector<double>, (str), "class_get_lensed_cl")
  BE_CONV_FUNCTION(class_get_unlensed_cl, std::vector<double>, (str), "class_get_unlensed_cl")
  BE_CONV_FUNCTION(class_get_scale_independent_growth_factor,   double, (double), "class_get_scale_independent_growth_factor")
  BE_CONV_FUNCTION(class_get_scale_independent_growth_factor_f, double, (double), "class_get_scale_independent_growth_factor_f")
  
  BE_INI_DEPENDENCY(classy_input_params, Classy_input)
  
  /**

  BE_CONV_FUNCTION(get_hi_class_cosmo_object, pybind11::object, (), "get_classy_cosmo_object")
  BE_CONV_FUNCTION(get_hi_class_backendDir, std::string, (), "get_classy_backendDir")

  BE_CONV_FUNCTION(hi_class_get_rs,        double, (), "class_get_rs")
  BE_CONV_FUNCTION(hi_class_get_tau_reio,  double, (), "class_get_tau_reio")
  BE_CONV_FUNCTION(hi_class_get_z_reio,    double, (), "class_get_z_reio")
  BE_CONV_FUNCTION(hi_class_get_Neff,      double, (), "class_get_Neff")
  BE_CONV_FUNCTION(hi_class_get_sigma8,      double, (), "class_get_sigma8")
  BE_CONV_FUNCTION(hi_class_get_Omega0_r,    double, (), "class_get_Omega0_r")
  BE_CONV_FUNCTION(hi_class_get_Omega0_ur,     double, (), "class_get_Omega0_ur")
  BE_CONV_FUNCTION(hi_class_get_Omega0_m,    double, (), "class_get_Omega0_m")
  BE_CONV_FUNCTION(hi_class_get_Omega0_ncdm_tot, double, (), "class_get_Omega0_ncdm_tot")
  BE_CONV_FUNCTION(hi_class_get_Omega0_Lambda,   double, (), "class_get_Omega0_Lambda")
  BE_CONV_FUNCTION(hi_class_get_H0,              double, (), "class_get_H0")
  BE_CONV_FUNCTION(hi_class_get_Da, double, (double), "class_get_Da")
  BE_CONV_FUNCTION(hi_class_get_Dl, double, (double), "class_get_Dl")
  BE_CONV_FUNCTION(hi_class_get_Hz, double, (double), "class_get_Hz")

  BE_CONV_FUNCTION(hi_class_get_lensed_cl, std::vector<double>, (str), "class_get_lensed_cl")
  BE_CONV_FUNCTION(hi_class_get_unlensed_cl, std::vector<double>, (str), "class_get_unlensed_cl")
  BE_CONV_FUNCTION(hi_class_get_scale_independent_growth_factor,   double, (double), "class_get_scale_independent_growth_factor")
  BE_CONV_FUNCTION(hi_class_get_scale_independent_growth_factor_f, double, (double), "class_get_scale_independent_growth_factor_f")

  BE_INI_DEPENDENCY(hi_class_input_params, Classy_input)

  **/

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
