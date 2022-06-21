//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module ObjectivesBit
///
///  Put your functions in files like this
///  if you wish to add observables or likelihoods
///  to this module.
///
///  See https://en.wikipedia.org/wiki/Test_functions_for_optimization
///  https://arxiv.org/abs/2101.04525
///  and https://arxiv.org/abs/1306.2144
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@qq.com)
///  \date 2021 January
///
///  *********************************************


#include <cmath>
#include <limits>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ObjectivesBit/ObjectivesBit_rollcall.hpp"


namespace Gambit
{
  namespace ObjectivesBit
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

    /** @brief See https://en.wikipedia.org/wiki/Rosenbrock_function */
    void rosenbrock(double &loglike)
    {
      using namespace Pipes::rosenbrock;
      auto x = get_arguments(Param);
      loglike = - rosenbrock(x);
    }

    /** @brief See https://en.wikipedia.org/wiki/Himmelblau%27s_function */
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

    /** @brief See https://en.wikipedia.org/wiki/Ackley_function */
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

    /** @brief Test problem 2 from https://arxiv.org/abs/1306.2144 */
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

    /** @brief See https://en.wikipedia.org/wiki/Rastrigin_function */
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

    /** @brief Test problem 1 from https://arxiv.org/abs/1306.2144 */
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

    void styblinski_tang(double &loglike)
    {
      using namespace Pipes::styblinski_tang;
      auto x = get_arguments(Param);

      loglike = 0.;

      for (const auto& p : x)
      {
        double p2 = p * p;
        loglike -= 0.5 * (p2 * p2 - 16. * p2 + 5. * p);
      }
    }

    void easom(double &loglike)
    {
      using namespace Pipes::easom;
      auto x = get_arguments(Param);
      loglike = std::cos(x[0]) * std::cos(x[1]) *
                std::exp(- (x[0] - M_PI) * (x[0] - M_PI) - (x[1] - M_PI) * (x[1] - M_PI));
    }

    /** @brief Analytic function 1 from https://arxiv.org/abs/2101.04525 */
    void tf1(double &loglike)
    {
      using namespace Pipes::tf1;
      auto x = get_arguments(Param);

      const double location = 2.;
      static const double scale = std::pow(15., 6);

      double sum_x2 = 0.;
      double sum_x6 = 0.;
      double prod_c2 = 1.;
      for (auto p : x)
      {
        p -= location;
        double x2 = p * p;
        sum_x2 += x2;
        sum_x6 += x2 * x2 * x2;
        double c = std::cos(p);
        prod_c2 *= c * c;
      }

      loglike = - std::exp(-sum_x6 / scale) + 2. * std::exp(-sum_x2) * prod_c2;
    }

    /** @brief Analytic function 2 from https://arxiv.org/abs/2101.04525 */
    void tf2(double &loglike)
    {
      using namespace Pipes::tf2;
      auto x = get_arguments(Param);

      const double location = -0.23;

      loglike = 0.;
      for (auto p : x)
      {
        p -= location;
        loglike -= p * p - 10. * std::cos(2. * M_PI * p) + 10.;
      }
    }

    /** @brief Analytic function 3 from https://arxiv.org/abs/2101.04525 */
    void tf3(double &loglike)
    {
      using namespace Pipes::tf3;
      auto x = get_arguments(Param);

      const int n = x.size();

      double sum_s6 = 0.;
      for (const auto& p : x)
      {
        double s = std::sin(5. * M_PI * (std::pow(p, 0.75) - 0.05));
        sum_s6 += std::pow(s, 6);
      }

      loglike = 1. / n * sum_s6;
    }

    /** @brief Analytic function 4 from https://arxiv.org/abs/2101.04525 */
    void tf4(double &loglike)
    {
      using namespace Pipes::tf4;
      auto x = get_arguments(Param);

      const int n = x.size();

      double sum = 0.;
      for (const auto& p : x)
      {
        sum += p * std::sin(std::sqrt(std::abs(p)));
      }

      loglike = -418.982887 * n + sum;
    }

  }  // namespace ObjectivesBit
}  // namespace Gambit
