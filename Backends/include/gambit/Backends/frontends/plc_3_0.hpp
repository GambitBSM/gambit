//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the plc backend.
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
///  \date 2019 Aug, Nov
///  \date 2020 Feb
///
///  *********************************************

#define BACKENDNAME plc
#define BACKENDLANG CC
#define VERSION 3.0
#define SAFE_VERSION 3_0
#define REFERENCE Planck:2015bpv,Planck:2019nip

LOAD_LIBRARY

// Internal function of plc (Not intended to be called directly)
BE_FUNCTION(initError, clik_error* , (),"initError","clik_initialize_error")
BE_FUNCTION(isError, int , (clik_error*),"_isError","clik_is_error")
BE_FUNCTION(stringError, void , (char*, clik_error*),"stringError","clik_string_error")
BE_FUNCTION(cleanupError, void , (clik_error**),"endError","clik_cleanup_error")
BE_FUNCTION(clik_init, clik_object*, (char*,clik_error**),"clik_init","clik_initialize")
BE_FUNCTION(clik_lensing_init, clik_lensing_object*, (char*,clik_error**),"clik_lensing_init","clik_lensing_initialize")
BE_FUNCTION(clik_get_lmax, void, (clik_object*, int*, clik_error**), "clik_get_lmax","clik_get_lmax")
BE_FUNCTION(clik_lensing_get_lmaxs, void, (clik_lensing_object*, int*, clik_error**), "clik_lensing_get_lmaxs","clik_lensing_get_lmaxs")
BE_FUNCTION(clik_compute, double, (clik_object*,double*,clik_error**), "clik_compute","clik_compute_loglike")
BE_FUNCTION(clik_lensing_compute, double, (clik_lensing_object*,double*,clik_error**), "clik_lensing_compute","clik_lensing_compute_loglike")
BE_FUNCTION(clik_cleanup, void, (clik_object**), "clik_cleanup","clik_cleanup")
BE_FUNCTION(clik_lensing_cleanup, void, (clik_lensing_object**), "clik_lensing_cleanup","clik_lensing_cleanup")

// All relevant data and variables will be kept within the fronted.
// Define convenience functions for the communication with the outside world
BE_CONV_FUNCTION(plc_required_Cl,void,(int&,bool&,bool&),"plc_required_Cl")

// (PR2 - 2015)
BE_CONV_FUNCTION(plc_loglike_highl_TTTEEE_2015,double,(double*),"plc_loglike_highl_TTTEEE_2015",(cosmo_nuisance_Planck_TTTEEE))
BE_CONV_FUNCTION(plc_loglike_highl_TT_2015,double,(double*),"plc_loglike_highl_TT_2015",(cosmo_nuisance_Planck_TT))
BE_CONV_FUNCTION(plc_loglike_highl_TTTEEE_lite_2015,double,(double*),"plc_loglike_highl_TTTEEE_lite_2015",(cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_highl_TT_lite_2015,double,(double*),"plc_loglike_highl_TT_lite_2015",(cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lowl_TEB_2015,double,(double*),"plc_loglike_lowl_TEB_2015",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lowl_TT_2015,double,(double*),"plc_loglike_lowl_TT_2015",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lensing_2015,double,(double*),"plc_loglike_lensing_2015",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT, cosmo_nuisance_Planck_lite))

// (PR3 - 2018)
BE_CONV_FUNCTION(plc_loglike_highl_TTTEEE_2018,double,(double*),"plc_loglike_highl_TTTEEE_2018",(cosmo_nuisance_Planck_TTTEEE))
BE_CONV_FUNCTION(plc_loglike_highl_TT_2018,double,(double*),"plc_loglike_highl_TT_2018",(cosmo_nuisance_Planck_TT))
BE_CONV_FUNCTION(plc_loglike_highl_TTTEEE_lite_2018,double,(double*),"plc_loglike_highl_TTTEEE_lite_2018",(cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_highl_TT_lite_2018,double,(double*),"plc_loglike_highl_TT_lite_2018",(cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lowl_TT_2018,double,(double*),"plc_loglike_lowl_TT_2018",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lowl_EE_2018,double,(double*),"plc_loglike_lowl_EE_2018",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT,cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lensing_2018,double,(double*),"plc_loglike_lensing_2018",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT, cosmo_nuisance_Planck_lite))
BE_CONV_FUNCTION(plc_loglike_lensing_marged_2018,double,(double*),"plc_loglike_lensing_marged_2018",(cosmo_nuisance_Planck_TTTEEE, cosmo_nuisance_Planck_TT, cosmo_nuisance_Planck_lite))

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
