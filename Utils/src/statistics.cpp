//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of statistical utilities.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Aug
///  \author Jonathan Cornell
///          (cornellj@physics.mcgill.ca)
///  \date 2016 Feb
///
///  *********************************************

#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>

#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/local_info.hpp"

namespace Gambit
{

  namespace Stats
  {

    /// Minimum finite result returnable from log(double x);
    const double logmin = log(std::numeric_limits<double>::min());

    /// A simple tester routine for the likelihood functions
    void test_likelihoods()
    {
      const int npts = 1001;
      const int n_theory_errs = 5;
      const double obs = 10;
      const double obserr = 1.0;
      const double base_theory_err = 0.25;
      const double obsrelerr = obserr/obs;
      const double pred_min = 0;
      const double pred_max = 20;
      double theory_err[n_theory_errs] = {0, 1, 2, 4, 8};
      double theory_relerr[n_theory_errs];
      for (int j = 0; j < n_theory_errs; ++j)
      {
        theory_err[j] *= base_theory_err;
        theory_relerr[j] = theory_err[j]/obs;
      }

      std::ofstream myfile;
      myfile.open ("stats_tests.txt");
      myfile << "# Theory errors:";
      for (int j = 0; j < n_theory_errs; ++j) myfile << " " << theory_err[j];
      myfile << endl << "# Fractional (relative) theory errors:";
      for (int j = 0; j < n_theory_errs; ++j) myfile << " " << theory_relerr[j];
      myfile << endl << "# mu           ";
      for (int j = 0; j < n_theory_errs; ++j)
      {
        myfile << "ln_Gprof[" << j << "]     "
               << "ln_Gmarg[" << j << "]     "
               << "ln_Gupprof[" << j << "]   "
               << "ln_Gupmarg[" << j << "]   "
               << "ln_Gdownprof[" << j << "] "
               << "ln_Gdownmarg[" << j << "] "
               << "ln_LNprof[" << j << "]    "
               << "ln_LNmarg[" << j << "]    "
               << "ln_LNprof_rel[" << j << "]"
               << "ln_LNmarg_rel[" << j << "]"
               << "Gprof[" << j << "]        "
               << "Gmarg[" << j << "]        "
               << "Gupprof[" << j << "]      "
               << "Gupmarg[" << j << "]      "
               << "Gdownprof[" << j << "]    "
               << "Gdownmarg[" << j << "]    "
               << "LNprof[" << j << "]       "
               << "LNmarg[" << j << "]       "
               << "LNprof_rel[" << j << "]   "
               << "LNmarg_rel[" << j << "]   ";
      }
      myfile << endl << std::setprecision(8) << std::scientific;
      for (int i = 0; i < npts; ++i)
      {
        double pred = pred_min + double(i)/double(npts-1)*(pred_max - pred_min);
        myfile << pred << " ";
        for (int j = 0; j < n_theory_errs; ++j)
        {
          double Gprof =      gaussian_loglikelihood(pred, obs, theory_err[j], obserr, true);
          double Gmarg =      gaussian_loglikelihood(pred, obs, theory_err[j], obserr, false);
          double Gupprof =    gaussian_upper_limit(pred, obs, theory_err[j], obserr, true);
          double Gupmarg =    gaussian_upper_limit(pred, obs, theory_err[j], obserr, false);
          double Gdownprof =  gaussian_lower_limit(pred, obs, theory_err[j], obserr, true);
          double Gdownmarg =  gaussian_lower_limit(pred, obs, theory_err[j], obserr, false);
          double LNprof =     lognormal_loglikelihood(pred, obs, theory_err[j], obserr, true);
          double LNmarg =     lognormal_loglikelihood(pred, obs, theory_err[j], obserr, false);
          double LNprof_rel = lognormal_loglikelihood_relerror(pred, obs, theory_relerr[j], obsrelerr, true);
          double LNmarg_rel = lognormal_loglikelihood_relerror(pred, obs, theory_relerr[j], obsrelerr, false);
          myfile << Gprof << " "
                 << Gmarg << " "
                 << Gupprof << " "
                 << Gupmarg << " "
                 << Gdownprof << " "
                 << Gdownmarg << " "
                 << LNprof << " "
                 << LNmarg << " "
                 << LNprof_rel << " "
                 << LNmarg_rel << " "
                 << exp(Gprof) << " "
                 << exp(Gmarg) << " "
                 << exp(Gupprof) << " "
                 << exp(Gupmarg) << " "
                 << exp(Gdownprof) << " "
                 << exp(Gdownmarg) << " "
                 << exp(LNprof) << " "
                 << exp(LNmarg) << " "
                 << exp(LNprof_rel) << " "
                 << exp(LNmarg_rel) << " ";
        }
        myfile << endl;
      }
      myfile.close();
      exit(1);
    }

    /// Use a detection to compute a simple chi-square-like log likelihood, for the case when obs is Gaussian distributed.
    double gaussian_loglikelihood(double theory, double obs, double theoryerr, double obserr, bool profile_systematics)
    {
      //Debug code (used to produce plots as per Section 8 of the main GAMBIT paper).
      //static bool first = true;
      //if (first) {first = false; test_likelihoods();}

      if (theoryerr < 0) utils_error().raise(LOCAL_INFO, "Theory uncertainty cannot be negative.");
      if (obserr <= 0) utils_error().raise(LOCAL_INFO, "Observational uncertainty must be non-zero and positive.");

      // If no theory error is given, go back to the standard chi^2 without systematics.
      if (theoryerr == 0) profile_systematics = false;

      double errsq = theoryerr*theoryerr + obserr*obserr;
      double chi2 = -0.5*pow(theory-obs,2)/errsq;
      double norm = profile_systematics ? log(2.0*pi*obserr*theoryerr) : 0.5*log(2.0*pi*errsq);

      std::cout << "(gaussian_loglikelihood debug) " << chi2 - norm <<" | errsq: " <<  errsq << " | chi2: " << chi2 << " | norm: " << norm << std::endl;

      return chi2 - norm;
    }

    /// Use a detection to compute a simple chi-square-like log likelihood, for the case when obs is log-normal distributed.
    /// Version that takes absolute errors.
    double lognormal_loglikelihood(double theory, double obs, double theoryerr, double obserr, bool profile_systematics)
    {
      return lognormal_loglikelihood_relerror(theory, obs, theoryerr/theory, obserr/obs, profile_systematics);
    }

    /// Use a detection to compute a simple chi-square-like log likelihood, for the case when obs is log-normal distributed.
    /// Version that takes fractional (relative) errors.
    double lognormal_loglikelihood_relerror(double theory, double obs, double reltheoryerr, double relobserr, bool profile_systematics)
    {
      if (reltheoryerr < 0) utils_error().raise(LOCAL_INFO, "Theory uncertainty cannot be negative.");
      if (relobserr <= 0) utils_error().raise(LOCAL_INFO, "Observational uncertainty must be non-zero and positive.");

      // Don't allow observed or predicted values of less than or equal to 0
      if (obs <= 1e2*std::numeric_limits<double>::min()) return std::numeric_limits<double>::lowest();
      if (theory <= 1e2*std::numeric_limits<double>::min()) return std::numeric_limits<double>::lowest();

      // If no theory error is given, go back to the standard log-normal likelihood without systematics.
      if (reltheoryerr == 0) profile_systematics = false;

      double log_obs_on_theory = log(obs / theory);
      double obserr_prime = log1p(relobserr);
      double theoryerr_prime = log1p(reltheoryerr);
      double errsq = obserr_prime*obserr_prime + theoryerr_prime*theoryerr_prime;
      double chi2 = -log(obs) - 0.5*pow(log_obs_on_theory,2)/errsq;
      double norm = profile_systematics ? log(2.0*pi*obserr_prime*theoryerr_prime) : 0.5*log(2.0*pi*errsq);
      double extra = profile_systematics ? theoryerr_prime*theoryerr_prime*(0.5*obserr_prime*obserr_prime - log_obs_on_theory)/errsq : 0.0;
      return chi2 + extra - norm;
    }

    /// Use a detection to compute a gaussian log-likelihood for an upper limit
    double gaussian_upper_limit(double theory, double obs, double theoryerr, double obserr, bool profile_systematics)
    {
      if (theoryerr < 0) utils_error().raise(LOCAL_INFO, "Theory uncertainty cannot be negative.");
      if (obserr <= 0) utils_error().raise(LOCAL_INFO, "Observational uncertainty must be non-zero and positive.");

      double loglike;
      double errsq = theoryerr*theoryerr + obserr*obserr;

      // Deal with the special case that no theory error has actually been given.  Revert to basic limit likelihood.
      if (theoryerr == 0)
      {
        double prefactor = -0.5*log(2.0*pi*errsq);
        return prefactor - (theory > obs ? 0.5*pow(theory-obs,2)/errsq : 0.0);
      }

      // Switch according to whether or not we are profiling.
      if (profile_systematics)
      {
        double prefactor = -log(2.0*pi*theoryerr*obserr);
        loglike = prefactor - (theory > obs? 0.5*pow(theory-obs,2)/errsq : 0.0);
      }
      else
      {
        double prefactor = -0.5*log(8.0*pi);
        double diff = obs - theory;
        double like = exp(-0.5*pow(diff,2)/errsq)/sqrt(errsq);
        like *= erfc(obserr * diff / (theoryerr * sqrt(2.0*errsq)));
        like += erfc(-diff/(sqrt(2.0)*theoryerr))/obserr;
        if (like < 0) utils_error().raise(LOCAL_INFO, "Marginalised Gaussian limit likelihood went negative!");
        loglike = prefactor + (like == 0 ? logmin : log(like));
      }

      return loglike;

    }

    /// Use a detection to compute a gaussian log-likelihood for a lower limit
    double gaussian_lower_limit(double theory, double obs, double theoryerr, double obserr, bool profile_systematics)
    {
      return gaussian_upper_limit(-theory, -obs, theoryerr, obserr, profile_systematics);
    }

  }

}
