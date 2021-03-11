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

#include "gambit/ScannerBit/priors/gaussian.hpp"

namespace Gambit
{
        namespace Priors
        {
                Gaussian::Gaussian(const std::vector<std::string>& param, const Options& options) : BasePrior(param, param.size()), mean(param.size(), 0.0), col(param.size())
                { 
                        std::vector<std::vector<double>> cov(param.size(), std::vector<double>(param.size(), 0.0));
                        
                        bool good = true;
                        std::stringstream err;
                        if (options.hasKey("cov"))
                        {
                                cov = options.getValue< std::vector<std::vector<double>> >("cov");
                                
                                if (cov.size() != param.size())
                                {
                                        good = false;
                                        err << "Gaussian (prior):  Covariance matrix is not the same dimension has the parameters." << std::endl;
                                }
                                
                                for (std::vector<std::vector<double>>::iterator it = cov.begin(); it != cov.end(); it++)
                                {
                                        if (it->size() != cov.size())
                                        {
                                                good = false;
                                                err << "Gaussian (prior):  Covariance matrix is not square." << std::endl;
                                        }
                                }
                        }
                        else if (options.hasKey("sigs"))
                        {
                                std::vector <double> sigs = options.getValue <std::vector <double>> ("sigs");
                                if (sigs.size() != param.size())
                                {
                                        good = false;
                                        err << "Gaussian (prior):  Sigma vector is not the same dimension has the parameters." << std::endl;
                                }
                                else
                                {
                                        for (int i = 0, end = sigs.size(); i < end; i++)
                                        {
                                                cov[i][i] = sigs[i]*sigs[i];
                                        }
                                }
                        }
                        else
                        {
                                good = false;
                                err << "Gaussian (prior):  Covariance matrix is not defined in inifile." << std::endl;
                        }
                        
                        if (options.hasKey("mean"))
                        {
                                std::vector <double> temp = options.getValue <std::vector <double>> ("mean");
                                if (temp.size() == mean.size())
                                {
                                        mean = temp;
                                }
                                else
                                {
                                        good = false;
                                        err << "Gaussian (prior):  Mean vector is not the same dimension has the parameters." << std::endl;
                                }
                        }
                        
                        if (good)
                        {
                                if (!col.EnterMat(cov))
                                {
                                        err << "Gaussian (prior):  Covariance matrix is not postive definite." << std::endl;
                                        Scanner::scan_error().raise(LOCAL_INFO, err.str());
                                }
                        }
                        else
                        {
                                Scanner::scan_error().raise(LOCAL_INFO, err.str());
                        }
                }
        }
}
