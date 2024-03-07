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
  typedef std::map<std::string, double> flav_observable_map;
  typedef std::map<std::string, std::map<std::string, double>> flav_covariance_map;

  /// Flavour observables structure holding central values and covariances.
  struct flav_prediction
  {
    flav_observable_map central_values;
    flav_covariance_map covariance;

    // Empty constructor
    flav_prediction()
    {}

    // Constructor with both central values and covariance
    flav_prediction(flav_observable_map cv, flav_covariance_map cov) : central_values(cv), covariance(cov)
    {}

    // Constructor only with central values
    flav_prediction(flav_observable_map cv) : central_values(cv)
    {
      for(auto &val1 : central_values)
        for(auto &val2 : central_values)
          covariance[val1.first][val2.first] = 0.0;
    }

    // Constructor with a single observable and value pair
    flav_prediction(str obs, double val)
    {
      central_values[obs] = val;
      for(auto &val1 : central_values)
        for(auto &val2 : central_values)
          covariance[val1.first][val2.first] = 0.0;
    }

    // Sum two different contribution as flav_predictions
    flav_prediction &operator+=(flav_prediction fp)
    {
      for(auto &cv : fp.central_values)
      {
        if(central_values.find(cv.first) != central_values.end())
        {
          central_values[cv.first] += cv.second;
          for(auto &cv2 : fp.central_values)
            covariance[cv.first][cv2.first] += fp.covariance[cv.first][cv2.first];
        }
        else
        {
          central_values[cv.first] = cv.second;
          covariance[cv.first] = {{cv.first, fp.covariance[cv.first][cv.first]}};
          for(auto &cv2 : central_values)
          {
            if(fp.covariance.find(cv2.first) != fp.covariance.end())
              covariance[cv2.first][cv.first] = fp.covariance[cv2.first][cv.first];
            else
              covariance[cv2.first][cv.first] = 0.0;
            covariance[cv.first][cv2.first] = covariance[cv2.first][cv.first];
          }

        }
      }
      return *this;
    }
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
