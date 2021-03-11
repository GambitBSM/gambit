//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior object construction routines
///  
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  *********************************************

#ifndef PRIOR_GAUSSIAN_HPP
#define PRIOR_GAUSSIAN_HPP

#include <vector>
#include <cmath>

#include "gambit/ScannerBit/cholesky.hpp"
#include "gambit/ScannerBit/priors.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include <boost/math/special_functions/erf.hpp>
   
namespace Gambit
{
    namespace Priors
    {
        // Gaussian prior. Takes covariance matrix as arguments
        class Gaussian : public BasePrior
        {
        private:
            std::vector <double> mean;
            mutable Cholesky col;
                
        public: 
            // Constructor defined in gaussian.cpp
            Gaussian(const std::vector<std::string>&, const Options&);
            
            // Transformation from unit interval to the Gaussian
            void transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &outputMap) const
            {
                std::vector<double> vec(unitpars.size());
                
                auto v_it = vec.begin();
                for (auto elem_it = unitpars.begin(), elem_end = unitpars.end(); elem_it != elem_end; elem_it++, v_it++)
                {
                    *v_it = M_SQRT2*boost::math::erf_inv(2.0*(*elem_it) - 1.0); 
                }
                
                col.ElMult(vec);
                
                v_it = vec.begin();
                auto m_it = mean.begin();
                for (auto str_it = param_names.begin(), str_end = param_names.end(); str_it != str_end; str_it++)
                {
                    outputMap[*str_it] = *(v_it++) + *(m_it++);
                }
            }
            
            double operator()(const std::vector<double> &vec) const
            {
                    static double norm = std::log(2.0*Gambit::Scanner::pi()*Gambit::Scanner::pow<2>(col.DetSqrt()))/2.0;
                    return -col.Square(vec, mean)/2.0 - norm;
            }
        };

        LOAD_PRIOR(gaussian, Gaussian)
    }
}

#endif
