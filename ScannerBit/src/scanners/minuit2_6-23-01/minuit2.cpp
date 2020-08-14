//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Minuit2
///
///  Header file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@qq.com)
///  \date 2020 August
///
///  *********************************************

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>  // For debugging only

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/minuit2/minuit2.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "Math/IFunction.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"
#include "Math/MinimizerOptions.h"

scanner_plugin(minuit2, version(6, 23, 01))
{
   reqd_libraries("Minuit2", "Minuit2Math");
   reqd_headers("Math/IFunction.h", "Minuit2/Minuit2Minimizer.h", "Math/Functor.h", "Math/MinimizerOptions.h");

   int plugin_main(void)
   {
      // Retrieve the dimensionality of the scan
      const int dim = get_dimension();

      Gambit::Scanner::like_ptr model = get_purpose(get_inifile_value<std::string>("like"));

      double offset = get_inifile_value<double>("likelihood: lnlike_offset", 0.);
      model->setPurposeOffset(offset);
  
      // minuit2 algorithm options
      const auto algorithm{get_inifile_value<std::string>("algorithm", "minimize")};
      const auto max_loglike_calls{get_inifile_value<int>("max_loglike_calls", 100000)};   
      const auto max_iterations{get_inifile_value<int>("max_iterations", 100000)};
      const auto tolerance{get_inifile_value<double>("tolerace", 0.0001)};
      const auto precision{get_inifile_value<double>("precision", 0.0001)};   
      const auto print_level{get_inifile_value<int>("print_level", 1)};   
      const auto start{get_inifile_value<double>("unit_hypercube_start", 0.5)}; 
      const auto step{get_inifile_value<double>("unit_hypercube_step", 0.01)};
      const auto strategy{get_inifile_value<int>("strategy", 1)};

      ROOT::Minuit2::EMinimizerType kalgorithm;
      if (algorithm == "simplex")
      {
        kalgorithm = ROOT::Minuit2::kSimplex;
      }
      else if (algorithm == "minimize")
      {
        kalgorithm = ROOT::Minuit2::kCombined;
      }
      else if (algorithm == "scan")
      {
        kalgorithm = ROOT::Minuit2::kScan;
      }
      else if (algorithm == "fumili")
      {
        kalgorithm = ROOT::Minuit2::kFumili;
      }
      else if (algorithm == "bfgs")
      { 
        kalgorithm = ROOT::Minuit2::kMigradBFGS;
      }
      else if (algorithm == "migrad")
      { 
        kalgorithm = ROOT::Minuit2::kMigrad;
      }
      else 
      {
        throw std::runtime_error("Unknown minuit2 algorithm: " + algorithm);
      }

      ROOT::Math::Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer(kalgorithm);
      min->SetStrategy(strategy);
      min->SetMaxFunctionCalls(max_loglike_calls);
      min->SetMaxIterations(max_iterations);
      min->SetTolerance(tolerance);
      min->SetPrintLevel(print_level);
      min->SetPrecision(precision);
      
      auto chi_squared = [&model, dim] (const double* x)
      {
        std::vector<double> v;
        for (int i = 0; i < dim; i++)
        {
          v.push_back(x[i]);
        }
        return -2. * model(v);
      };

      ROOT::Math::Functor f(chi_squared, dim);
      min->SetFunction(f);

      // set the free variables to be minimized
      for (int i = 0; i < dim; i++)
      {
        std::string name = "x_" + std::to_string(i);
        min->SetLimitedVariable(i, name, start, step, 0., 1.);
      }

      // do the minimization
      min->Minimize();
  
      std::cout << "minimum chi-squared = " << min->MinValue() << std::endl;

      const double *best_fit_hypercube = min->X();
      for (int i = 0; i < dim; i++)
      {
        std::cout << "best-fit hypercube " << i << " = "
                  << best_fit_hypercube[i] << std::endl;
      }

      // convert result to physical parameters
      std::vector<double> v;
      for (int i = 0; i < dim; i++)
      {
        v.push_back(best_fit_hypercube[i]);
      }  
      auto best_fit_physical = model.transform(v);    
      std::cout << "best-fit physical = " << best_fit_physical << std::endl;

      // whether succssful
      const int status = min->Status();
      switch (status) {
        case 0:
          break; 
        case 5:
          throw std::runtime_error("Minuit2: Covar is not pos def");
        case 1:
          throw std::runtime_error("Minuit2: Covar was made pos def");
        case 2:
          throw std::runtime_error("Minuit2: Hesse is not valid");
        case 3:
          throw std::runtime_error("Minuit2: Edm is above max");
        case 4:
          throw std::runtime_error("Minuit2: Reached call limit");
        default:
          throw std::runtime_error("Unknown minuit2 error: " + std::to_string(status));
       }

      // manually delete the pointer
      delete min;

      // success if reached end
      return 0;
   }
}

