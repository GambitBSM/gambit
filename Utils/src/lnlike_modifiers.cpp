//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Modifier functions for the total scan lnlike
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Feb, Oct
///
///  *********************************************

#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include "gambit/Utils/lnlike_modifiers.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/local_info.hpp"

namespace Gambit
{
  namespace Utils
  {
    /// Interface function that calls the correct modifier function based on the name in lnlike_modifier_name
    double run_lnlike_modifier(double lnlike, const str& lnlike_modifier_name, const Options& lnlike_modifier_options)
    {
      // Just as a reminder to the user, print a warning if any non-default modifier function is activated.
      static bool first = true;
      if (first)
      {
        if (lnlike_modifier_name != "identity")
        {
          std::ostringstream msg;
          msg << "The option 'use_lnlike_modifier: " << lnlike_modifier_name << "' is activated. ";
          msg << "This will modify the total log-likelihood function as seen by the scanner.";
          // Warning to screen
          std::cout << "WARNING: " << msg.str() << std::endl;
          // Warning to logs
          utils_warning().raise(LOCAL_INFO, msg.str());
        }
        first = false;
      }

      double modified_lnlike;

      if (lnlike_modifier_name == "identity")
      {
        modified_lnlike = lnlike;
      }
      else if (lnlike_modifier_name == "gaussian")
      {
        modified_lnlike = lnlike_modifier_gaussian(lnlike, lnlike_modifier_options);
      }
      else if (lnlike_modifier_name == "gaussian_plateau")
      {
        modified_lnlike = lnlike_modifier_gaussian_plateau(lnlike, lnlike_modifier_options);
      }
      else
      {
        utils_error().raise(LOCAL_INFO, "Unknown lnlike modifier: " + lnlike_modifier_name);
      }

      return modified_lnlike;
    }

    /// lnlike modifier: gaussian
    double lnlike_modifier_gaussian(double lnlike, const Options& lnlike_modifier_options)
    {
      static const double mu = lnlike_modifier_options.getValue<double>("mu");
      static const double sigma = lnlike_modifier_options.getValue<double>("sigma");
      static const str use_limit = lnlike_modifier_options.getValueOrDef<str>("none", "use_limit");
      static const bool use_delta_lnlike = lnlike_modifier_options.getValueOrDef<bool>(false, "use_delta_lnlike");
      static const double sigma_sq = sigma * sigma;

      static double currentbest = lnlike;

      double x = lnlike;

      if (use_delta_lnlike)
      {
        if (lnlike > currentbest)
        {
          currentbest = lnlike;        
        }
        x = lnlike - currentbest;
      }

      if (use_limit == "upper" && x < mu)
      {
        return 0.;
      }
      else if (use_limit == "lower" && x > mu)
      {
        return 0.;
      }
      return -0.5 * pow(x - mu, 2) / sigma_sq;
    }

    /// lnlike modifier: gaussian_plateau
    double lnlike_modifier_gaussian_plateau(double lnlike, const Options& lnlike_modifier_options)
    {
      static const double mu_dn = lnlike_modifier_options.getValue<double>("mu_dn");
      static const double sigma_dn = lnlike_modifier_options.getValue<double>("sigma_dn");
      static const double mu_up = lnlike_modifier_options.getValue<double>("mu_up");
      static const double sigma_up = lnlike_modifier_options.getValue<double>("sigma_up");
      static const bool use_delta_lnlike = lnlike_modifier_options.getValueOrDef<bool>(false, "use_delta_lnlike");
      static const double sigma_dn_sq = sigma_dn * sigma_dn;
      static const double sigma_up_sq = sigma_up * sigma_up;

      static double currentbest = lnlike;

      double x = lnlike;

      if (use_delta_lnlike)
      {
        if (lnlike > currentbest)
        {
          currentbest = lnlike;        
        }
        x = lnlike - currentbest;
      }

      if (x < mu_dn)
      {
        return -0.5 * pow(x - mu_dn, 2) / sigma_dn_sq;
      }
      else if (x > mu_up)
      {
        return -0.5 * pow(x - mu_up, 2) / sigma_up_sq;
      }
      return 0.;
    }

  }
}