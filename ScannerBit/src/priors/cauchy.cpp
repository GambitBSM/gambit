//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Scanner inifile interface implementations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 July 2013 Feb 2014
///
///  *********************************************

#include "gambit/ScannerBit/priors/cauchy.hpp"

namespace Gambit
{
        namespace Priors
        {
                Cauchy::Cauchy(const std::vector<std::string>& param, const Options& options) : BasePrior(param, param.size()), mean(param.size(), 0.0), col(param.size())
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
                                        err << "Cauchy (prior):  Covariance matrix is not the same dimension has the parameters." << std::endl;
                                }
                                
                                for (std::vector<std::vector<double>>::iterator it = cov.begin(); it != cov.end(); it++)
                                {
                                        if (it->size() != cov.size())
                                        {
                                                good = false;
                                                err << "Cauchy (prior):  Covariance matrix is not square." << std::endl;
                                        }
                                }
                        }
                        else if (options.hasKey("sigs"))
                        {
                                std::vector <double> sigs = options.getValue <std::vector <double>> ("sigs");
                                if (sigs.size() != param.size())
                                {
                                        good = false;
                                        err << "Cauchy (prior):  Sigma vector is not the same dimension has the parameters." << std::endl;
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
                                err << "Cauchy (prior):  Covariance matrix is not defined in inifile." << std::endl;
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
                                        err << "Cauchy (prior):  Mean vector is not the same dimension has the parameters." << std::endl;
                                }
                        }
                        
                        if (good)
                        {
                                if (!col.EnterMat(cov))
                                {
                                        err << "Cauchy (prior):  Covariance matrix is not postive definite." << std::endl;
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
