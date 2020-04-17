//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module FlavBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with FlavBit.
///
///  Add to this if you want to define a new type
///  for the functions in FlavBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Marcin Chrzaszcz
///          (mchrzasz@cern.ch)
///  \date 2015 July
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 July
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2019 Nov
///        2020 Feb
///
///  *********************************************

#ifndef __FlavBit_types_hpp__
#define __FlavBit_types_hpp__

#include <string>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>


namespace Gambit
{

  namespace FlavBit
  {

    namespace ublas = boost::numeric::ublas;

    /// Simple structure for holding a correlation value and name of the correlated observable
    struct Correlation
    {
      double corr_val;
      std::string corr_name;
    };

    /// Representation of a single entry in the FlavBit YAML database
    struct Measurement
    {
      bool is_limit;
      bool exp_one_sided;
      double exp_value;
      double exp_stat_error;
      double exp_sys_error;
      double exp_error;
      double exp_90_CL;
      double exp_95_CL;
      double th_error;
      std::string name;
      std::string exp_source;
      std::string th_error_source;
      std::string th_error_type;
      std::vector<Correlation> corr;
    };

    /// Structure for holding predicted and observed values of multiple observables,
    /// and experimental and theoretical covariance matrices for their uncertainties.
    struct predictions_measurements_covariances
    {
      std::string LL_name;
      boost::numeric::ublas::matrix<double> value_exp;
      boost::numeric::ublas::matrix<double> cov_exp;
      boost::numeric::ublas::matrix<double> value_th;
      boost::numeric::ublas::matrix<double> cov_th;
      std::vector<double> diff;
      int dim;
    };

    /// Maps for holding SI observables and covariance matrix.
    typedef std::map<const std::string, double> flav_observable_map;
    typedef std::map<const std::string, std::map<const std::string, double>> flav_covariance_map;

    /// Flavour observables structure holding central values and covariances.
    struct flav_prediction
    {
      flav_observable_map central_values;
      flav_covariance_map covariance;
    };

  }
}


#endif
