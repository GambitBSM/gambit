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

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/minuit2/minuit2.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"


scanner_plugin(minuit2, version(6, 23, 01))
{
  reqd_libraries("Minuit2", "Minuit2Math");
  reqd_headers("Minuit2/Minuit2Minimizer.h", "Math/Functor.h");

  typedef std::unordered_map<std::string, double> param_map;

  int plugin_main(void)
  {
    // retrieve the dimensionality of the scan
    const int dim = get_dimension();

    // retrive the model - contains loglike etc
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
    const auto strategy{get_inifile_value<int>("strategy", 1)};

    // get starting point (optional). Default is center of hypercube for each parameter
    std::vector<double> start(dim, 0.5);
    param_map start_map = model.transform(start);
    auto start_node = get_inifile_node("physical_start");

    if (start_node) 
    {
      for (const auto &s : start_map)
      {
         if (start_node[s.first])
         {
            start_map.at(s.first) = start_node[s.first].as<double>();
         }
      }    
    } 

    const std::vector<double> hypercube_start = model.inverse_transform(start_map);

    // check it

    for (const auto &p : hypercube_start)
    {
      if (p > 1. || p < 0.)
      {
        throw std::runtime_error("Minuit2: start outside prior ranges");
      }
    }

    const param_map round_trip = model.transform(hypercube_start);
    for (const auto &s : start_map) 
    {
      if (s.second != round_trip.at(s.first))
      {
        throw std::runtime_error("Minuit2: could not convert physical parameters to hypercube");
      }
    }

    // get hypercube step (optional). Default is same for each parameter
    const double default_step = 0.01;
    auto step_node = get_inifile_node("unit_hypercube_step");
    std::vector<double> hypercube_step;

    for (const auto &s : start_map)
    {
       if (step_node && step_node[s.first])
       {
          hypercube_step.push_back(step_node[s.first].as<double>());
       }  
       else
       {
          hypercube_step.push_back(default_step);
       }
    }    

    // select algorithm

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
      throw std::runtime_error("Minuit2: Unknown algorithm: " + algorithm);
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
    
    auto names = model.get_names();
    for (int i = 0; i < dim; i++)
    {
      min->SetLimitedVariable(i, names[i], hypercube_start[i], hypercube_step[i], 0., 1.);
      std::cout << names[i] << ". hypercube = " << hypercube_start[i]
                << " +/- " << hypercube_step[i]
                << ". physical = " << start_map.at(names[i]) << std::endl;
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
        throw std::runtime_error("Minuit2: Unknown error: " + std::to_string(status));
     }

    // manually delete the pointer
    delete min;

    // success if reached end
    return 0;
  }
}

