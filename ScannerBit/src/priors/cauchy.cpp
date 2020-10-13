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
///  \author Gregory Martinez
///    (gregory.david.martinez@gmail.com)
///  \date 2013 July 2013 Feb 2014
///
///  \author Andrew Fowlie
///    (andrew.j.fowlie@qq.com)
///  \date August 2020
///
///  *********************************************

#include "gambit/ScannerBit/priors/cauchy.hpp"

namespace Gambit
{
  namespace Priors
  {
    Cauchy::Cauchy(const std::vector<std::string>& param, const Options& options) :
      BasePrior(param, param.size()), col(param.size())
    {

      std::vector<std::vector<double>> scale_matrix(param.size(), std::vector<double>(param.size(), 0.));

      if (options.hasKey("scale_matrix") && options.hasKey("gamma")) {
          std::stringstream err;
          err << "Cauchy prior: "
              << "define scale matrix by either 'scale_matrix' or 'gamma'"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }
      else if (options.hasKey("scale_matrix"))
      {
        scale_matrix = options.getValue<std::vector<std::vector<double>>>("scale_matrix");

        if (scale_matrix.size() != param.size())
        {
          std::stringstream err;
          err << "Cauchy prior: "
              << "'scale_matrix' is not the same dimension as the parameters"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }

        for (const auto& row : scale_matrix)
        {
          if (row.size() != scale_matrix.size())
          {
            std::stringstream err;
            err << "Cauchy prior: "
                << "'scale_matrix' is not square"
                << std::endl;
            Scanner::scan_error().raise(LOCAL_INFO, err.str());

          }
        }
      }
      else if (options.hasKey("gamma"))
      {
        const auto gamma = options.getVector<double>("gamma");
        if (gamma.size() != param.size())
        {
          std::stringstream err;
          err << "Cauchy prior: "
              << "'gamma' is not the same dimension as the parameters"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }
        else
        {
          for (int i = 0, end = gamma.size(); i < end; i++)
          {
            scale_matrix[i][i] = gamma[i] * gamma[i];
          }
        }
      }
     else
      {
        std::stringstream err;
        err << "Cauchy prior: "
            << "the scale matrix is not defined by either 'cov_matrix' or 'gamma'"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }

      if (options.hasKey("location"))
      {
        location = options.getVector<double>("location");
        if (location.size() != param.size())
        {
          std::stringstream err;
          err << "Cauchy prior: "
              << "'location' vector is not the same dimension as the parameters"
              << std::endl;
          Scanner::scan_error().raise(LOCAL_INFO, err.str());
        }
      }
      else
      {
        std::stringstream err;
        err << "Cauchy prior: "
            << "'location' vector is required"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }

      if (!col.EnterMat(scale_matrix))
      {
        std::stringstream err;
        err << "Cauchy prior: "
            << "the scale matrix is not positive-definite"
            << std::endl;
        Scanner::scan_error().raise(LOCAL_INFO, err.str());
      }
    }
  }  // namespace Priors
}  // namespace Gambit
