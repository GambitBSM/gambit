//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior function that implements a discrete
///  distribution from a user-provided histogram.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sebastian Hoof
///          (s.hoof.physics@gmail.com)
///  \date 2021 Mar
///        2024 Feb
///
///  *********************************************

#ifndef PRIOR_DISCRETE_HPP
#define PRIOR_DISCRETE_HPP

#include "gambit/ScannerBit/priors.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"

#include <vector>

namespace Gambit
{
  namespace Priors
  {
    /// Discrete prior for a discrete set of values.
    /// Takes the arguments: [hist_data : hist_file]
    class Discrete : public BasePrior
    {
    private:
      /// Name of the parameter that this prior is supposed to transform
      const std::string &myparameter;
      /// Save the values of the unique parameter, PMF, and CMF
      std::vector<double> unique_params;
      std::vector<double> pmf_values;
      std::vector<double> cmf_values;

    public:
      /// Constructor
      Discrete(const std::vector<std::string>& param, const Options&);

      /// Transformation from unit interval to the parameter values (inverse CDF)
      void transform(hyper_cube_ref<double> unitpars, std::unordered_map<std::string, double> &physicalpars) const override;

      /// Transformation from the parameter values to the unit interval (CDF)
      void inverse_transform(const std::unordered_map<std::string, double> &physicalpars, hyper_cube_ref<double> unitpars) const override;

      /// Probability mass function
      double log_prior_density(const std::unordered_map<std::string, double> &physicalpars) const override;
    };

    LOAD_PRIOR(discrete, Discrete)

  } // namespace Priors
} // namespace Gambit

#endif
