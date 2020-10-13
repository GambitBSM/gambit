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

#include "gambit/ScannerBit/priors/gaussian.hpp"

namespace Gambit
{
  namespace Priors
  {
    Gaussian::Gaussian(const std::vector<std::string>& param, const Options& options) :
      BasePrior(param, param.size()), col(param.size())
    {
      std::vector<std::vector<double>> cov_matrix(param.size(), std::vector<double>(param.size(), 0.));

      if (options.hasKey("sigma") && options.hasKey("cov_matrix")) {
          std::stringstream err;
          err << "Gaussian prior: "
              << "define covariance matrix by either 'cov_matrix' or 'sigma'"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }
      else if (options.hasKey("cov_matrix"))
      {
        cov_matrix = options.getValue<std::vector<std::vector<double>>>("cov_matrix");

        if (cov_matrix.size() != param.size())
        {
          std::stringstream err;
          err << "Gaussian prior: "
              << "'cov_matrix' is not the same dimension as the parameters"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }

        for (const auto& row : cov_matrix)
        {
          if (row.size() != cov_matrix.size())
          {
            std::stringstream err;
            err << "Gaussian prior: "
                << "'cov_matrix' is not square"
                << std::endl;
            Scanner::scan_error().raise(LOCAL_INFO, err.str());
          }
        }
      }
      else if (options.hasKey("sigma"))
      {
        std::vector<double> sigma = options.getVector<double>("sigma");
        if (sigma.size() != param.size())
        {
            std::stringstream err;
            err << "Gaussian prior: "
                << "'sigma' is not the same dimension as the parameters"
                << std::endl;
            Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }
        else
        {
          for (int i = 0, end = sigma.size(); i < end; i++)
          {
            cov_matrix[i][i] = sigma[i] * sigma[i];
          }
        }
      }
      else
      {
        std::stringstream err;
        err << "Gaussian prior: "
            << "the covariance matrix is not defined by either 'cov_matrix' or 'sigma'"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }

      if (options.hasKey("mu"))
      {
        mu = options.getVector<double>("mu");
        if (mu.size() != param.size())
        {
          std::stringstream err;
          err << "Gaussian prior: "
              << "'mu' vector is not the same dimension as the parameters"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }
      }
      else
      {
        std::stringstream err;
        err << "Gaussian prior: "
            << "'mu' vector is required"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }

      if (!col.EnterMat(cov_matrix))
      {
        std::stringstream err;
        err << "Gaussian prior: "
            << "covariance matrix is not positive-definite"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }
    }

  }  // namespace Priors
}  // namespace Gambit
