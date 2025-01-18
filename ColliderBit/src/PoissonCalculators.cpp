//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions for working with an unbiased 
///  Poisson likelihood estimator.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date   2024 Oct
///
///  \author Andrew Fowlie
///  \date   2024 Oct
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ColliderBit/PoissonCalculators.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    namespace PoissonCalculators
    {


      double log_factorial(double k)
      {
        return std::lgamma(k + 1);
      }

      double beta(double x, double y)
      {
        return std::tgamma(x) * std::tgamma(y) / std::tgamma(x + y);
      }

      double binom(double n, double k)
      {
        if (n < k) { return 0.;}
        return 1. / ((n + 1.) * beta(n - k + 1., k + 1.));
      }

      /**
      Unbiased likelihood estimator
      */

      template <typename engine_type>
      int umvue_draw_n_mc(double n_mc, engine_type engine)
      {
        std::poisson_distribution<> poisson(n_mc);
        return poisson(engine);
      }

      int umvue_draw_n_mc(double n_mc)
      {
        std::random_device rd;
        std::mt19937 engine(rd());
        return umvue_draw_n_mc(n_mc, engine);
      }
      
      int umvue_draw_n_mc_threadsafe(double n_mc)
      {
        std::poisson_distribution<> poisson(n_mc);
        return poisson(Random::rng());
      }
      
      double umvue_poisson_like(int k, double b, int o, int n_mc, double n_exp)
      {

        if ((n_mc <= 0) || (n_exp <= 0))
        {
          ColliderBit_error().raise(LOCAL_INFO, "umvue_poisson_like: n_mc <= 0 || n_exp <= 0");
        }

        const double f = n_exp / n_mc;

        const double eps = 1.0e-9;

        // special case b = 0 and maybe f = 1
        if (std::fabs(b - 0.) < eps)
        {
          if (std::fabs(f - 1.) < eps)
          {
            return k == o ? 1. : 0.;
          }
          return binom(k, o) * std::pow(f, k) * std::pow(1. - f, k - o);
        }

        // special case b !=0 but f = 1
        if (std::fabs(f - 1.) < eps)
        {
          if (k > o) {return 0.;}

          const double ln_like = -b + (o - k) * std::log(b) -log_factorial(o - k);
          return std::exp(ln_like);
        }

        // general cases
        double sum = 0.;
        double term = 1.;
        const double r = f / (1. - f) / b;

        for (int i = 0; i <= std::min(k, o); i++)
        {
          sum += term;
          term *= r * (k - i) * (o - i) / (i + 1);
        }

        const double ln_norm = o * std::log(b) - b - log_factorial(o);
        const double norm = std::exp(ln_norm);
        
        return norm * std::pow(1. - f, k) * sum;
      }

      /**
      Regular likelihood estimator
      */
      double mle_poisson_loglike(double s, double b, int o)
      {
        double sb = s + b;
        return o*log(sb) - sb - log_factorial(o);
      }

    }  // end namespace PoissonCalculators
  }  // end namespace ColliderBit
}  // end namespace Gambit

