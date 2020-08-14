//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module TestFunctionBit
///
///  Put your functions in files like this
///  if you wish to add observables or likelihoods
///  to this module.
///
///  See https://en.wikipedia.org/wiki/Test_functions_for_optimization
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


#include <cmath>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/TestFunctionBit/TestFunctionBit_rollcall.hpp"


namespace Gambit
{
  namespace TestFunctionBit
  { 
    typedef Gambit::Models::safe_param_map<Gambit::safe_ptr<const double>> map;
    std::vector<double> get_arguments(map param)
    {
      std::vector<double> x;
      for (const auto& p : param)
      {
        x.push_back(*p.second);
      }
      return x;
    }

    void gaussian(double &loglike)
    {
      using namespace Pipes::gaussian;
      auto x = get_arguments(Param);

      const double mu = 0.5;
      const double sigma = 0.1;

      double chi_sq = 0.;
      for (const auto& e : x)
      {
        chi_sq += (e - mu) * (e - mu);
      }
      chi_sq /= sigma * sigma;

      static double norm = 0.5 * x.size() * std::log(2. * M_PI * sigma);
      loglike = -0.5 * chi_sq - norm;
    }

    double rosenbrock(double x, double y)
    {
      const double a = 1.;
      const double b = 100.;
      return (a - x) * (a - x) + b * (y - x * x) * (y - x * x);
    }

    double rosenbrock(std::vector<double> x)
    {
      const int d = x.size();
      double r = 0.;
      for (int i = 0; i < d - 1; i++)
      {
        r += rosenbrock(x[i], x[i + 1]);
      }
      return r;
    }

    void rosenbrock(double &loglike)
    {
      using namespace Pipes::rosenbrock;
      auto x = get_arguments(Param);
      loglike = - rosenbrock(x);
    }

    void himmelblau(double &loglike)
    {
      using namespace Pipes::himmelblau;
      auto x = get_arguments(Param);
      loglike = - (x[0] * x[0] + x[1] - 11.) * (x[0] * x[0] + x[1] - 11.)
                - (x[0] + x[1] * x[1] - 7.) * (x[0] + x[1] * x[1] - 7.);
    }

    void mccormick(double &loglike)
    {
      using namespace Pipes::mccormick;
      auto x = get_arguments(Param);
      loglike = - std::sin(x[0] + x[1]) 
                - (x[0] - x[1]) *  (x[0] - x[1])
                + 1.5 * x[0] - 2.5 * x[1] - 1.;
    }
  }  // namespace TestFunctionBit
}  // namespace Gambit
