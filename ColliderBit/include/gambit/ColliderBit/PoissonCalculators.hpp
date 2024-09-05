#ifndef LHC_LIKELIHOODS_HPP_
#define LHC_LIKELIHOODS_HPP_

/**
Unbiased likelihood estimator
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>


namespace Gambit
{
  namespace ColliderBit
  {
    namespace ideal
    {

      double log_factorial(double k);
      double beta(double x, double y);
      double binom(double n, double k);

      template <typename engine_type>
      int umvue_draw_n_mc(double n_mc, engine_type engine);

      int umvue_draw_n_mc(double n_mc);

      double umvue_poisson_like(int k, double b, int o, int n_mc, double n_exp);

      double mle_poisson_like(int sb, int o);

    }  // end namespace ideal
  }  // end namespace ColliderBit
}  // end namespace Gambit

#endif  // LHC_LIKELIHOODS_HPP_
