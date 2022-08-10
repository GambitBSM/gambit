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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Aug
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

  /// Stream overload for flav_prediction
  inline std::ostream& operator << (std::ostream &os, const flav_prediction &prediction)
  {
    for(auto val : prediction.central_values)
    {
      os << " " << val.first << ": " << val.second << std::endl;
    }
    os << " Covariance:" << std::endl;
    for(auto cov : prediction.covariance)
    {
      std::stringstream row;
      for(auto cov2 : cov.second)
      {
        row << cov2.second << " ";
      }
      os << " " << row.str() << std::endl;
    }
    return os;
  }

  // Map from bin pair to flavour prediction
  typedef std::map<std::string,flav_prediction> flav_binned_prediction;

  // Stream overload for flav_binned_prediction
  inline std::ostream& operator << (std::ostream &os, const flav_binned_prediction &prediction)
  {
    for(auto bin : prediction)
    {
      os << "Bin:" << bin.first << std::endl << bin.second;
    }

    return os;
  }
}
