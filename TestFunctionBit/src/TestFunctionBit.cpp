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
#include <limits>
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
      for (int i = 0, n = param.size(); i < n; i++)
      {
        std::string name = "x" + std::to_string(i + 1);
        x.push_back(*param.at(name));
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

      static double norm = 0.5 * x.size() * std::log(2. * M_PI * sigma * sigma);
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

    void ackley(double &loglike)
    {
      using namespace Pipes::ackley;
      auto x = get_arguments(Param);
      double r2 = 0.;
      double c = 0.;
      for (const auto& p : x)
      {
        r2 += p * p;
        c += std::cos(2. * M_PI * p);
      }
      loglike = 20. * std::exp(-0.2 * std::sqrt(r2 / x.size()))
                + std::exp(c / x.size())
                - M_E - 20.;
    }

    void eggbox(double &loglike)
    {
      using namespace Pipes::eggbox;
      auto x = get_arguments(Param);
      double prod = 1.;
      for (const auto& p : x)
      {
        prod *= std::cos(p * 5. * M_PI);
      }
      loglike = std::pow(prod + 2., 5.);
    }

    void rastrigin(double &loglike)
    {
      using namespace Pipes::rastrigin;
      auto x = get_arguments(Param);
      double r2 = 0.;
      double c = 0.;
      for (const auto& p : x)
      {
        r2 += p * p;
        c += std::cos(2. * M_PI * p);
      }
      loglike = x.size() * 10. + r2 - 10. * c;
    }

    void beale(double &loglike)
    {
      using namespace Pipes::beale;
      auto x = get_arguments(Param);
      loglike = - std::pow(1.5 - x[0] - x[1] * x[0], 2)
                - std::pow(2.25 - x[0] - x[1] * x[1] * x[0], 2)
                - std::pow(2.625 - x[0] - x[1] * x[1] * x[1] * x[0], 2);
    }

    double logaddexp(double x, double y)
    {
      return std::max(x, y) + std::log1p(std::exp(-std::abs(x - y)));
    }

    void shells(double &loglike)
    {
      using namespace Pipes::shells;
      auto x = get_arguments(Param);

      const double radius = 0.1;
      const double width = 2.;
      const std::vector<double> center = {-3.5, 3.5};
      static double norm = - 0.5 * std::log(2. * M_PI * width * width);

      loglike = std::numeric_limits<double>::lowest();
      for (const auto& c : center)
      {
        double r2 = 0.;
        for (const auto& p : x)
        {
          r2 += (c - p) * (c - p);
        }
        double d = (std::sqrt(r2) - radius) * (std::sqrt(r2) - radius);
        double delta = -d / (2. * width * width) - norm;
        loglike = logaddexp(loglike, delta);
      }
    }

  }  // namespace TestFunctionBit
}  // namespace Gambit
