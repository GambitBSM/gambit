//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Multivariate Gaussian prior
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///  (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///  (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  \author Andrew Fowlie
///    (andrew.j.fowlie@qq.com)
///  \date August 2020
///
///  *********************************************

#ifndef __PRIOR_GAUSSIAN_HPP__
#define __PRIOR_GAUSSIAN_HPP__

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>

#include "gambit/ScannerBit/cholesky.hpp"
#include "gambit/ScannerBit/priors.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include <boost/math/special_functions/erf.hpp>

namespace Gambit
{
  namespace Priors
  {
    /**
     * @brief  Multi-dimensional Gaussian prior
     *
     * Defined by a covariance matrix and mean.
     *
     * If the covariance matrix is diagonal, it may instead be specified by the square-roots of its 
     * diagonal entries, denoted \f$\sigma\f$.
     */
    class Gaussian : public BasePrior
    {
     private:
      std::vector <double> mu;
      mutable Cholesky col;

     public:
      // Constructor defined in gaussian.cpp
      Gaussian(const std::vector<std::string>&, const Options&);

      /** @brief Transformation from unit interval to the Gaussian */
      void transform(const std::vector <double> &unitpars, std::unordered_map<std::string, double> &outputMap) const override
      {
        std::vector<double> vec(unitpars.size());

        auto v_it = vec.begin();
        for (auto elem_it = unitpars.begin(), elem_end = unitpars.end(); elem_it != elem_end; elem_it++, v_it++)
        {
          *v_it = M_SQRT2 * boost::math::erf_inv(2. * (*elem_it) - 1.);
        }

        col.ElMult(vec);

        v_it = vec.begin();
        auto m_it = mu.begin();
        for (auto str_it = param_names.begin(), str_end = param_names.end(); str_it != str_end; str_it++)
        {
          outputMap[*str_it] = *(v_it++) + *(m_it++);
        }
      }

      std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &physical) const override
      {
        // subtract mean
        std::vector<double> central;
        for (int i = 0, n = this->size(); i < n; i++)
        {
          central.push_back(physical.at(param_names[i]) - mu[i]);
        }

        // invert rotation by Cholesky matrix
        std::vector<double> rotated = col.invElMult(central);

        // now diagonal; invert Gaussian CDF
        std::vector<double> u;
        for (const auto& v : rotated)
        {
          u.push_back(0.5 * (boost::math::erf(v / M_SQRT2) + 1.));
        }
        return u;
      }

      double operator()(const std::vector<double> &vec) const override
      {
        static double norm = 0.5 * std::log(2. * M_PI * std::pow(col.DetSqrt(), 2));
        return -0.5 * col.Square(vec, mu) - norm;
      }
    };

    LOAD_PRIOR(gaussian, Gaussian)

  }  // namespace Priors
}  // namespace Gambit

#endif  // __PRIOR_GAUSSIAN_HPP__
