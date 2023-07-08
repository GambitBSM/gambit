//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Multivariate Cauchy prior
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///    (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///    (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  \author Andrew Fowlie
///    (andrew.j.fowlie@qq.com)
///  \date August 2020
///
///  *********************************************

#ifndef __PRIOR_CAUCHY_HPP__
#define __PRIOR_CAUCHY_HPP__

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

#include "gambit/ScannerBit/cholesky.hpp"
#include "gambit/ScannerBit/priors.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"

namespace Gambit {
  namespace Priors {
    /**
     * @brief  Multi-dimensional Cauchy prior
     *
     * This is a [multivariate \f$t\f$-distribution](https://en.wikipedia.org/wiki/Multivariate_t-distribution)
     * with \f$\nu = 1\f$ degree of freedom. 
     *
     * Defined by a scale matrix, \f$\Sigma\f$, and a location vector.
     *
     * If the scale matrix is diagonal,it may instead be specified by the square-roots of its 
     * diagonal entries, denoted \f$\gamma\f$.
     */
    class Cauchy : public BasePrior
    {
     private:
      std::vector<double> location;
      mutable Cholesky col;

     public:
      // Constructor defined in cauchy.cpp
      Cauchy(const std::vector<std::string>& param, const Options& options);

      /** @brief Transformation from unit interval to the Cauchy */
      void transform(const std::vector<double>& unitpars, std::unordered_map<std::string, double>& outputMap) const override
      {
        std::vector<double> vec(unitpars.size());

        auto v_it = vec.begin();
        for (auto elem_it = unitpars.begin(), elem_end = unitpars.end(); elem_it != elem_end; elem_it++, v_it++)
        {
          *v_it = std::tan(M_PI * (*elem_it - 0.5));
        }

        col.ElMult(vec);

        v_it = vec.begin();
        auto m_it = location.begin();
        for (auto str_it = param_names.begin(), str_end = param_names.end(); str_it != str_end; str_it++)
        {
          outputMap[*str_it] = *(v_it++) + *(m_it++);
        }
      }

      std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &physical) const override
      {
        // subtract location
        std::vector<double> central;
        for (int i = 0, n = this->size(); i < n; i++)
        {
          central.push_back(physical.at(param_names[i]) - location[i]);
        }

        // invert rotation by Cholesky matrix
        std::vector<double> rotated = col.invElMult(central);

        // now diagonal; invert Cauchy CDF
        std::vector<double> u;
        for (const auto& v : rotated)
        {
          u.push_back(std::atan(v) / M_PI + 0.5);
        }
        return u;
      }

      double operator()(const std::vector<double>& vec) const override
      {
        static double norm = std::log(M_PI * col.DetSqrt());
        return -std::log1p(col.Square(vec, location)) - norm;
      }
    };

    LOAD_PRIOR(cauchy, Cauchy)

  }  // namespace Priors
}  // namespace Gambit

#endif  // __PRIOR_CAUCHY_HPP__
