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

#ifndef PRIOR_CAUCHY_HPP
#define PRIOR_CAUCHY_HPP
//#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include "gambit/ScannerBit/cholesky.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/priors.hpp"

namespace Gambit
{
        namespace Priors
        {       
                /// 2D Gaussian prior. Takes covariance matrix as arguments
                class Cauchy : public BasePrior
                {
                private:
                        std::vector <double> mean;
                        mutable Cholesky col;
                        
                public: 
                        // Constructor defined in cauchy.cpp
                        Cauchy(const std::vector<std::string>& param, const Options& options);
                        
                        // Transformation from unit interval to the Gaussian
                        void transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &outputMap) const
                        {
                                std::vector<double> vec(unitpars.size());
                                
                                auto v_it = vec.begin();
                                for (auto elem_it = unitpars.begin(), elem_end = unitpars.end(); elem_it != elem_end; elem_it++, v_it++)
                                {
                                        *v_it = std::tan(M_PI*(*elem_it - 0.5));      
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
                                static double norm = std::log(Gambit::Scanner::pi()*col.DetSqrt());
                                return -log(1.0 + col.Square(vec, mean)) - norm;
                        }
                };
        
                LOAD_PRIOR(cauchy, Cauchy)
        }
}

#endif
