//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Flavour prediction container type
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2019 Nov
///        2020 Feb
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2022 May
///
///  *********************************************

#pragma once

#include <string>
#include <map>


namespace Gambit
{

  /// Maps for holding observables and covariance matrix.
  typedef std::map<const std::string, double> flav_observable_map;
  typedef std::map<const std::string, std::map<const std::string, double>> flav_covariance_map;

  /// Flavour observables structure holding central values and covariances.
  struct flav_prediction
  {
    flav_observable_map central_values;
    flav_covariance_map covariance;
  };

}
