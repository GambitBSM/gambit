//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit LHC signal and likelihood functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Andy Buckley
///
///  \author Chris Rogan
///          (crogan@cern.ch)
///  \date 2014 Aug
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2018 Jan
///  \date 2019 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date   2017 March
///  \date   2018 Jan
///  \date   2018 May
///
///  *********************************************

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/statistics.hpp" 
#include "gambit/Utils/util_macros.hpp"
#include "gambit/ColliderBit/Utils.hpp"

#include "multimin/multimin.hpp"

#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include "Eigen/Eigenvalues"
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <gsl/gsl_sf_gamma.h>

//#define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {


    /// Loop over all analyses and fill a map of predicted counts
    void calc_LHC_signals(map_str_dbl& result)
    {
      using namespace Pipes::calc_LHC_signals;

      // Clear the result map
      result.clear();

      std::stringstream summary_line;
      summary_line << "LHC signals per SR: ";

      // Loop over analyses and collect the predicted events into the map
      for (size_t analysis = 0; analysis < Dep::AllAnalysisNumbers->size(); ++analysis)
      {
        // AnalysisData for this analysis
        const AnalysisData& adata = *(Dep::AllAnalysisNumbers->at(analysis));

        summary_line << adata.analysis_name << ": ";

        // Loop over the signal regions inside the analysis, and save the predicted number of events for each.
        for (size_t SR = 0; SR < adata.size(); ++SR)
        {
          // Save SR numbers and absolute uncertainties
          const SignalRegionData srData = adata[SR];
          const str key = adata.analysis_name + "__" + srData.sr_label + "__i" + std::to_string(SR) + "__signal";
          result[key] = srData.n_sig_scaled;
          const double n_sig_scaled_err = srData.calc_n_sig_scaled_err();
          result[key + "_uncert"] = n_sig_scaled_err;

          summary_line << srData.sr_label + "__i" + std::to_string(SR) << ":" << srData.n_sig_scaled << "+-" << n_sig_scaled_err << ", ";
        }
      }
      logger() << LogTags::debug << summary_line.str() << EOM;
    }




    /// Loglike objective-function wrapper to provide the signature for GSL multimin
    ///
    /// @note Doesn't return a full log-like: the factorial term is missing since it's expensive, fixed and cancels in DLLs
    void _gsl_calc_Analysis_MinusLogLike(const size_t n, const double* unit_nuisances_dbl,
                                         void* fixedparamspack, double* fval)
    {
      // Convert the array of doubles into an "Eigen view" of the nuisance params
      Eigen::Map<const Eigen::ArrayXd> unit_nuisances(&unit_nuisances_dbl[0], n);

      // Convert the linearised array of doubles into "Eigen views" of the fixed params
      double *fixedparamspack_dbl = (double*) fixedparamspack;
      Eigen::Map<const Eigen::VectorXd> n_preds_nominal(&fixedparamspack_dbl[0], n);
      Eigen::Map<const Eigen::ArrayXd> n_obss(&fixedparamspack_dbl[n], n);
      Eigen::Map<const Eigen::ArrayXd> sqrtevals(&fixedparamspack_dbl[2*n], n);
      Eigen::Map<const Eigen::MatrixXd> evecs(&fixedparamspack_dbl[3*n], n, n);

      // Rotate rate deltas into the SR basis and shift by SR mean rates
      const Eigen::VectorXd n_preds = n_preds_nominal + evecs*(sqrtevals*unit_nuisances).matrix();

      // Calculate each SR's Poisson likelihood and add to composite likelihood calculation
      double loglike_tot = n * log(1/sqrt(2*M_PI)); //< could also drop this, but it costs ~nothing
      for (size_t j = 0; j < n; ++j)
      {
        // First the multivariate Gaussian bit (j = nuisance)
        const double pnorm_j = -pow(unit_nuisances(j), 2)/2.;
        loglike_tot += pnorm_j;

        // Then the Poisson bit (j = SR)
        /// @note We've dropped the log(n_obs!) terms, since they're expensive and cancel in computing DLL
        const double lambda_j = std::max(n_preds(j), 1e-3); //< manually avoid <= 0 rates
        const double logfact_n_obs = 0; // gsl_sf_lngamma(n_obss(j) + 1); //< skipping log(n_obs!) computation
        const double loglike_j = n_obss(j)*log(lambda_j) - lambda_j - logfact_n_obs;

        loglike_tot += loglike_j;
      }

      // Output via argument (times -1 to return -LL for minimisation)
      *fval = -loglike_tot;
    }


    /// Loglike gradient-function wrapper to provide the signature for GSL multimin
    void _gsl_calc_Analysis_MinusLogLikeGrad(const size_t n, const double* unit_nuisances_dbl,
                                             void* fixedparamspack, double* fgrad)
    {
      // Convert the array of doubles into an "Eigen view" of the nuisance params
      Eigen::Map<const Eigen::ArrayXd> unit_nuisances(&unit_nuisances_dbl[0], n);

      // Convert the linearised array of doubles into "Eigen views" of the fixed params
      double *fixedparamspack_dbl = (double*) fixedparamspack;
      Eigen::Map<const Eigen::VectorXd> n_preds_nominal(&fixedparamspack_dbl[0], n);
      Eigen::Map<const Eigen::ArrayXd> n_obss(&fixedparamspack_dbl[n], n);
      Eigen::Map<const Eigen::ArrayXd> sqrtevals(&fixedparamspack_dbl[2*n], n);
      Eigen::Map<const Eigen::MatrixXd> evecs(&fixedparamspack_dbl[3*n], n, n);

      // Rotate rate deltas into the SR basis and shift by SR mean rates
      const Eigen::VectorXd n_preds = n_preds_nominal + evecs*(sqrtevals*unit_nuisances).matrix();

      // Compute gradient elements
      for (int j = 0; j < unit_nuisances.size(); ++j)
      {
        double llgrad = 0;
        for (int k = 0; k < unit_nuisances.size(); ++k)
        {
          llgrad += (n_obss(k)/n_preds(k) - 1) * evecs(k,j);
        }
        llgrad = llgrad * sqrtevals(j) - unit_nuisances(j);
        // Output via argument (times -1 to return -dLL for minimisation)
        fgrad[j] = -llgrad;
      }
    }


    void _gsl_calc_Analysis_MinusLogLikeAndGrad(const size_t n, const double* unit_nuisances_dbl,
                                                void* fixedparamspack,
                                                double* fval, double* fgrad)
    {
      _gsl_calc_Analysis_MinusLogLike(n, unit_nuisances_dbl, fixedparamspack, fval);
      _gsl_calc_Analysis_MinusLogLikeGrad(n, unit_nuisances_dbl, fixedparamspack, fgrad);
    }


    std::vector<double> _gsl_mkpackedarray(const Eigen::ArrayXd& n_preds,
                                           const Eigen::ArrayXd& n_obss,
                                           const Eigen::ArrayXd& sqrtevals,
                                           const Eigen::MatrixXd& evecs)
    {
      const size_t nSR = n_obss.size();
      std::vector<double> fixeds(3*nSR + 2*nSR*nSR, 0.0);
      for (size_t i = 0; i < nSR; ++i)
      {
        fixeds[0+i] = n_preds(i);
        fixeds[nSR+i] = n_obss(i);
        fixeds[2*nSR+i] = sqrtevals(i);
        for (size_t j = 0; j < nSR; ++j)
        {
          fixeds[3*nSR+i*nSR+j] = evecs(j,i);
        }
      }

      return fixeds;
    }


    /// Return the best log likelihood
    /// @note Return value is missing the log(n_obs!) terms (n_SR of them) which cancel in LLR calculation
    /// @todo Pass in the cov, and compute the fixed evals, evecs, and corr matrix as fixed params in here? Via a helper function to reduce duplication
    double profile_loglike_cov(const Eigen::ArrayXd& n_preds,
                               const Eigen::ArrayXd& n_obss,
                               const Eigen::ArrayXd& sqrtevals,
                               const Eigen::MatrixXd& evecs)
    {
      // Number of signal regions
      const size_t nSR = n_obss.size();

      // Set initial guess for nuisances to zero
      std::vector<double> nuisances(nSR, 0.0);

      // // Set nuisances to an informed starting position
      // const Eigen::ArrayXd& err_n_preds = (evecs*sqrtevals.matrix()).array(); //< @todo CHECK
      // std::vector<double> nuisances(nSR, 0.0);
      // for (size_t j = 0; j < nSR; ++j) 
      // {
      //   // Calculate the max-L starting position, ignoring correlations
      //   const double obs = n_obss(j);
      //   const double rate = n_preds(j);
      //   const double delta = err_n_preds(j);
      //   const double a = delta;
      //   const double b = rate + delta*delta;
      //   const double c = delta * (rate - obs);
      //   const double d = b*b - 4*a*c;
      //   const double sqrtd = (d < 0) ? 0 : sqrt(d);
      //   if (sqrtd == 0)
      //   {
      //     nuisances[j] = -b / (2*a);
      //   }
      //   else
      //   {
      //     const double th0_a = (-b + sqrtd) / (2*a);
      //     const double th0_b = (-b - sqrtd) / (2*a);
      //     nuisances[j] = (fabs(th0_a) < fabs(th0_b)) ? th0_a : th0_b;
      //   }
      // }


      // Optimiser parameters
      // Params: step1size, tol, maxiter, epsabs, simplex maxsize, method, verbosity
      // Methods:
      //  0: Fletcher-Reeves conjugate gradient
      //  1: Polak-Ribiere conjugate gradient
      //  2: Vector Broyden-Fletcher-Goldfarb-Shanno method
      //  3: Steepest descent algorithm
      //  4: Nelder-Mead simplex
      //  5: Vector Broyden-Fletcher-Goldfarb-Shanno method ver. 2
      //  6: Simplex algorithm of Nelder and Mead ver. 2
      //  7: Simplex algorithm of Nelder and Mead: random initialization
      using namespace Pipes::calc_LHC_LogLikes;
      static const double INITIAL_STEP = runOptions->getValueOrDef<double>(0.1, "nuisance_prof_initstep");
      static const double CONV_TOL = runOptions->getValueOrDef<double>(0.01, "nuisance_prof_convtol");
      static const unsigned MAXSTEPS = runOptions->getValueOrDef<unsigned>(10000, "nuisance_prof_maxsteps");
      static const double CONV_ACC = runOptions->getValueOrDef<double>(0.01, "nuisance_prof_convacc");
      static const double SIMPLEX_SIZE = runOptions->getValueOrDef<double>(1e-5, "nuisance_prof_simplexsize");
      static const unsigned METHOD = runOptions->getValueOrDef<unsigned>(6, "nuisance_prof_method");
      static const unsigned VERBOSITY = runOptions->getValueOrDef<unsigned>(0, "nuisance_prof_verbosity");
      static const struct multimin::multimin_params oparams = {INITIAL_STEP, CONV_TOL, MAXSTEPS, CONV_ACC, SIMPLEX_SIZE, METHOD, VERBOSITY};

      // Convert the linearised array of doubles into "Eigen views" of the fixed params
      std::vector<double> fixeds = _gsl_mkpackedarray(n_preds, n_obss, sqrtevals, evecs);

      // Pass to the minimiser
      double minusbestll = 999;

      // Call minimizer with stderr temporarily silenced (due to gsl output)?
      static bool silence_multimin = runOptions->getValueOrDef<bool>(true, "silence_multimin");

      // Call the minimizer
      if (silence_multimin)
      {
        CALL_WITH_SILENCED_STDERR(
          multimin::multimin(nSR, &nuisances[0], &minusbestll,
                   nullptr, nullptr, nullptr,
                   _gsl_calc_Analysis_MinusLogLike,
                   _gsl_calc_Analysis_MinusLogLikeGrad,
                   _gsl_calc_Analysis_MinusLogLikeAndGrad,
                   &fixeds[0], oparams) 
        )
      }
      else
      {
        multimin::multimin(nSR, &nuisances[0], &minusbestll,
                 nullptr, nullptr, nullptr,
                 _gsl_calc_Analysis_MinusLogLike,
                 _gsl_calc_Analysis_MinusLogLikeGrad,
                 _gsl_calc_Analysis_MinusLogLikeAndGrad,
                 &fixeds[0], oparams);
      }

      return -minusbestll;
    }


    double marg_loglike_nulike1sr(const Eigen::ArrayXd& n_preds,
                                  const Eigen::ArrayXd& n_obss,
                                  const Eigen::ArrayXd& sqrtevals)
    {
      assert(n_preds.size() == 1);
      assert(n_obss.size() == 1);
      assert(sqrtevals.size() == 1);

      using namespace Pipes::calc_LHC_LogLikes;
      auto marginaliser = (*BEgroup::lnlike_marg_poisson == "lnlike_marg_poisson_lognormal_error")
        ? BEreq::lnlike_marg_poisson_lognormal_error : BEreq::lnlike_marg_poisson_gaussian_error;

      // Setting bkg above zero to avoid nulike special cases
      const double sr_margll = marginaliser((int) n_obss(0), 0.001, n_preds(0), sqrtevals(0)/n_preds(0));
      return sr_margll;
    }


    double marg_loglike_cov(const Eigen::ArrayXd& n_preds,
                            const Eigen::ArrayXd& n_obss,
                            const Eigen::ArrayXd& sqrtevals,
                            const Eigen::MatrixXd& evecs)
    {
      // Number of signal regions
      const size_t nSR = n_obss.size();

      // Sample correlated SR rates from a rotated Gaussian defined by the covariance matrix and offset by the mean rates
      using namespace Pipes::calc_LHC_LogLikes;
      static const double CONVERGENCE_TOLERANCE_ABS = runOptions->getValueOrDef<double>(0.05, "nuisance_marg_convthres_abs");
      static const double CONVERGENCE_TOLERANCE_REL = runOptions->getValueOrDef<double>(0.05, "nuisance_marg_convthres_rel");
      static const size_t NSAMPLE_INPUT = runOptions->getValueOrDef<size_t>(100000, "nuisance_marg_nsamples_start");
      static const bool   NULIKE1SR = runOptions->getValueOrDef<bool>(false, "nuisance_marg_nulike1sr");

      // Optionally use nulike's more careful 1D marginalisation for one-SR cases
      if (NULIKE1SR && nSR == 1) return marg_loglike_nulike1sr(n_preds, n_obss, sqrtevals);

      // Dynamic convergence control & test variables
      size_t nsample = NSAMPLE_INPUT;
      bool first_iteration = true;
      double diff_abs = 9999;
      double diff_rel = 1;

      // Likelihood variables (note use of long double to guard against blow-up of L as opposed to log(L1/L0))
      long double ana_like_prev = 1;
      long double ana_like = 1;
      long double lsum_prev = 0;

      // Sampler for unit-normal nuisances
      std::normal_distribution<double> unitnormdbn(0,1);

      // Log factorial of observed number of events.
      // Currently use the ln(Gamma(x)) function gsl_sf_lngamma from GSL. (Need continuous function.)
      // We may want to switch to using Stirling's approximation: ln(n!) ~ n*ln(n) - n
      Eigen::ArrayXd logfact_n_obss(nSR);
      for (size_t j = 0; j < nSR; ++j)
        logfact_n_obss(j) = gsl_sf_lngamma(n_obss(j) + 1);

      // Check absolute difference between independent estimates
      /// @todo Should also implement a check of relative difference
      while ((diff_abs > CONVERGENCE_TOLERANCE_ABS && diff_rel > CONVERGENCE_TOLERANCE_REL) || 1.0/sqrt(nsample) > CONVERGENCE_TOLERANCE_ABS)
      {
        long double lsum = 0;

        /// @note How to correct negative rates? Discard (scales badly), set to
        /// epsilon (= discontinuous & unphysical pdf), transform to log-space
        /// (distorts the pdf quite badly), or something else (skew term)?
        /// We're using the "set to epsilon" version for now.
        /// Ben: I would vote for 'discard'. It can't be that inefficient, surely?
        /// Andy: For a lot of signal regions, the probability of none having a negative sample is Prod_SR p(non-negative)_SR... which *can* get bad.

        #pragma omp parallel
        {
          // Sample correlated SR rates from a rotated Gaussian defined by the covariance matrix and offset by the mean rates
          double lsum_private  = 0;
          #pragma omp for nowait
          for (size_t i = 0; i < nsample; ++i)
          {
            Eigen::VectorXd norm_samples(nSR);
            for (size_t j = 0; j < nSR; ++j)
              norm_samples(j) = sqrtevals(j) * unitnormdbn(Random::rng());

            // Rotate rate deltas into the SR basis and shift by SR mean rates
            const Eigen::VectorXd n_pred_samples  = n_preds + (evecs*norm_samples).array();

            // Calculate Poisson likelihood and add to composite likelihood calculation
            double combined_loglike = 0;
            for (size_t j = 0; j < nSR; ++j)
            {
              const double lambda_j = std::max(n_pred_samples(j), 1e-3); //< manually avoid <= 0 rates
              const double loglike_j  = n_obss(j)*log(lambda_j) - lambda_j - logfact_n_obss(j);
              combined_loglike += loglike_j;
            }
            // Add combined likelihood to running sums (to later calculate averages)
            lsum_private += exp(combined_loglike);
          }

          #pragma omp critical
          {
            lsum  += lsum_private;
          }
        } // End omp parallel

        // Compare convergence to previous independent batch
        if (first_iteration)  // The first round must be generated twice
        {
          lsum_prev = lsum;
          first_iteration = false;
        }
        else
        {
          ana_like_prev = lsum_prev / (double)nsample;
          ana_like = lsum / (double)nsample;
          diff_abs = fabs(ana_like_prev - ana_like);
          diff_rel = diff_abs/ana_like;

          // Update variables
          lsum_prev += lsum;  // Aggregate result. This doubles the effective batch size for lsum_prev.
          nsample *=2;  // This ensures that the next batch for lsum is as big as the current batch size for lsum_prev, so they can be compared directly.
        }

        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX
             << "diff_rel: " << diff_rel << endl
             << "   diff_abs: " << diff_abs << endl
             << "   logl: " << log(ana_like) << endl;
        cout << DEBUG_PREFIX << "nsample for the next iteration is: " << nsample << endl;
        cout << DEBUG_PREFIX << endl;
        #endif
      }
      // End convergence while-loop

      // Combine the independent estimates ana_like and ana_like_prev.
      // Use equal weights since the estimates are based on equal batch sizes.
      ana_like = 0.5*(ana_like + ana_like_prev);
      const double ana_margll = log(ana_like);
      #ifdef COLLIDERBIT_DEBUG
      cout << DEBUG_PREFIX << "Combined estimate: ana_loglike: " << ana_margll << "   (based on 2*nsample=" << 2*nsample << " samples)" << endl;
      #endif

      return ana_margll;
    }


    /// For a given analysis, calculate per-SR loglikes and the overall analysis loglike.
    /// Return the results as an AnalysLogLikes object.
    AnalysisLogLikes calc_loglikes_for_analysis(const AnalysisData& adata, bool USE_COVAR, bool USE_MARG,
                                                bool combine_nocovar_SRs, bool set_zero_loglike=false)
    {
      AnalysisLogLikes result;

      // Fix the profiling/marginalising function according to the option
      auto marg_prof_fn = USE_MARG ? marg_loglike_cov : profile_loglike_cov;

      // Extract analysis info from the AnalysisData instance
      const std::string ananame = adata.analysis_name;
      const size_t nSR = adata.size();
      const bool has_covar = adata.srcov.rows() > 0;


      // Shortcut #1: 
      // We've been told to set all SR loglikes to zero for this analysis
      if (set_zero_loglike)
      {
        // If this is an analysis with covariance info, only add a single 0-entry in the map
        if (USE_COVAR && has_covar)
        {
          result.combination_sr_label = "none";
          result.combination_sr_index = -1;
          result.combination_loglike = 0.0;
        }
        // If this is an analysis without covariance info, add 0-entries for all SRs plus
        // one for the combined LogLike
        else
        {
          for (size_t SR = 0; SR < adata.size(); ++SR)
          {
            result.sr_indices[adata[SR].sr_label] = SR;
            result.sr_loglikes[adata[SR].sr_label] = 0.0;
          }
          result.combination_sr_label = "none";
          result.combination_sr_index = -1;
          result.combination_loglike = 0.0;
        }

        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: " << ananame << "_LogLike : " << 0.0 << " (due to set_zero_loglike = true)" << endl;
        #endif

        return result;
      }


      // Shortcut #2
      // If all SRs have 0 signal prediction, we know the delta log-likelihood is 0.
      bool all_zero_signal = true;
      for (size_t SR = 0; SR < nSR; ++SR)
      {
        if (adata[SR].n_sig_MC != 0)
        {
          all_zero_signal = false;
          break;
        }
      }
      if (all_zero_signal)
      {
        // Store result
        if (!(USE_COVAR && has_covar))
        {
          for (size_t SR = 0; SR < adata.size(); ++SR)
          {
            result.sr_indices[adata[SR].sr_label] = SR;
            result.sr_loglikes[adata[SR].sr_label] = 0.0;
          }
        }
        result.combination_sr_label = "any";
        result.combination_sr_index = -1;
        result.combination_loglike = 0.0;

        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: " << ananame << "_LogLike : " << 0.0 << " (No signal predicted. Skipped full calculation.)" << endl;
        #endif

        // Continue to next analysis
        return result;
      }


      // Work out the total (delta) log likelihood for this analysis, with correlations as available/instructed
      double ana_dll = NAN;
      if (USE_COVAR && has_covar)
      {
        /// If (simplified) SR-correlation info is available, so use the
        /// covariance matrix to construct composite marginalised likelihood
        /// Despite initial thoughts, we can't just do independent LL
        /// calculations in a rotated basis, but have to sample from the
        /// covariance matrix.
        ///
        /// @note This means we can't use the nulike LL functions, which
        /// operate in 1D only.  Also, log-normal sampling in the diagonal
        /// basis is not helpful, since the rotation will re-generate negative
        /// rates.
        ///
        /// @todo Support NSL, i.e. skewness correction
        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: Analysis " << analysis << " has a covariance matrix: computing composite loglike." << endl;
        #endif


        // Construct vectors of SR numbers
        /// @todo Unify this for both cov and no-cov, feeding in one-element Eigen blocks as Ref<>s for the latter?
        Eigen::ArrayXd n_obs(nSR); // logfact_n_obs(nSR);
        Eigen::ArrayXd n_pred_b(nSR), n_pred_sb(nSR), abs_unc_s(nSR);
        for (size_t SR = 0; SR < nSR; ++SR)
        {
          const SignalRegionData& srData = adata[SR];

          // Actual observed number of events
          n_obs(SR) = srData.n_obs;

          // Log factorial of observed number of events.
          // Currently use the ln(Gamma(x)) function gsl_sf_lngamma from GSL. (Need continuous function.)
          // We may want to switch to using Stirling's approximation: ln(n!) ~ n*ln(n) - n
          //logfact_n_obs(SR) = gsl_sf_lngamma(n_obs(SR) + 1.);

          // A contribution to the predicted number of events that is not known exactly
          n_pred_b(SR) = std::max(srData.n_bkg, 0.001); // <-- Avoid trouble with b==0
          n_pred_sb(SR) = srData.n_sig_scaled + srData.n_bkg;

          // Absolute errors for n_predicted_uncertain_*
          abs_unc_s(SR) = srData.calc_n_sig_scaled_err();
        }

        // Diagonalise the background-only covariance matrix, extracting the correlation and rotation matrices
        /// @todo Compute the background-only covariance decomposition and likelihood only once
        const Eigen::MatrixXd& srcov_b = adata.srcov;
        Eigen::MatrixXd srcorr_b = srcov_b; // start with cov, then make corr
        for (size_t SR = 0; SR < nSR; ++SR)
        {
          const double diagsd = sqrt(srcov_b(SR,SR));
          srcorr_b.row(SR) /= diagsd;
          srcorr_b.col(SR) /= diagsd;
        }
        const Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig_b(adata.srcov);
        const Eigen::ArrayXd Eb = eig_b.eigenvalues();
        const Eigen::ArrayXd sqrtEb = Eb.sqrt();
        const Eigen::MatrixXd Vb = eig_b.eigenvectors();

        // Construct and diagonalise the s+b covariance matrix, adding the diagonal signal uncertainties in quadrature
        const Eigen::MatrixXd srcov_s = abs_unc_s.array().square().matrix().asDiagonal();
        const Eigen::MatrixXd srcov_sb = srcov_b + srcov_s;
        Eigen::MatrixXd srcorr_sb = srcov_sb;
        for (size_t SR = 0; SR < nSR; ++SR)
        {
          const double diagsd = sqrt(srcov_sb(SR,SR));
          srcorr_sb.row(SR) /= diagsd;
          srcorr_sb.col(SR) /= diagsd;
        }
        const Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig_sb(srcov_sb);
        const Eigen::ArrayXd Esb = eig_sb.eigenvalues();
        const Eigen::ArrayXd sqrtEsb = Esb.sqrt();
        const Eigen::MatrixXd Vsb = eig_sb.eigenvectors();

        // cout << "B: " << srcorr_b << " " << srcov_b << endl;
        // cout << "SB: " << srcorr_sb << " " << srcov_sb << endl;

        // Compute the single, correlated analysis-level DLL as the difference of s+b and b (partial) LLs
        /// @todo Only compute this once per run
        const double ll_b = marg_prof_fn(n_pred_b, n_obs, sqrtEb, Vb);
        const double ll_sb = marg_prof_fn(n_pred_sb, n_obs, sqrtEsb, Vsb);
        const double dll = ll_sb - ll_b;

        // Store result
        ana_dll = dll;
        result.combination_sr_label = "all";
        result.combination_sr_index = -1;
        result.combination_loglike = ana_dll;

        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: " << ananame << "_LogLike : " << ana_dll << endl;
        #endif


      }
      else
      { // NO SR-CORRELATION INFO, OR USER CHOSE NOT TO USE IT:


        // We either take the result from the SR *expected* to be most
        // constraining under the s=0 assumption (default), or naively combine
        // the loglikes for all SRs (if combine_SRs_without_covariances=true).
        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: Analysis " << analysis << " has no covariance matrix: computing single best-expected loglike." << endl;
        #endif

        double bestexp_dll_exp = 0, bestexp_dll_obs = NAN;
        str bestexp_sr_label;
        int bestexp_sr_index;
        double nocovar_srsum_dll_obs = 0;

        for (size_t SR = 0; SR < nSR; ++SR)
        {
          const SignalRegionData& srData = adata[SR];

          // Shortcut: If n_sig_MC == 0, we know the delta log-likelihood is 0.
          if(srData.n_sig_MC == 0)
          {
            // Store (obs) result for this SR
            result.sr_indices[srData.sr_label] = SR;
            result.sr_loglikes[srData.sr_label] = 0.0;

            // Update the running best-expected-exclusion detail
            if (0.0 < bestexp_dll_exp || SR == 0)
            {
              bestexp_dll_exp = 0.0;
              bestexp_dll_obs = 0.0;
              bestexp_sr_label = srData.sr_label;
              bestexp_sr_index = SR;
            }

            // Skip to next SR
            continue;
          }

          // A contribution to the predicted number of events that is not known exactly
          const double n_pred_b = std::max(srData.n_bkg, 0.001); // <-- Avoid trouble with b==0
          const double n_pred_sb = n_pred_b + srData.n_sig_scaled;

          // Actual observed number of events and predicted background, as integers cf. Poisson stats
          const double n_obs = round(srData.n_obs);
          const double n_pred_b_int = round(n_pred_b);

          // Absolute errors for n_predicted_uncertain_*
          const double abs_uncertainty_b = std::max(srData.n_bkg_err, 0.001); // <-- Avoid trouble with b_err==0
          const double abs_uncertainty_sb = std::max(srData.calc_n_sigbkg_err(), 0.001); // <-- Avoid trouble with sb_err==0
 

          // Construct dummy 1-element Eigen objects for passing to the general likelihood calculator
          /// @todo Use newer (?) one-step Eigen constructors for (const) single-element arrays
          Eigen::ArrayXd n_obss(1);        n_obss(0) = n_obs;
          Eigen::ArrayXd n_preds_b_int(1); n_preds_b_int(0) = n_pred_b_int;
          Eigen::ArrayXd n_preds_b(1);     n_preds_b(0) = n_pred_b;
          Eigen::ArrayXd n_preds_sb(1);    n_preds_sb(0) = n_pred_sb;
          Eigen::ArrayXd sqrtevals_b(1);   sqrtevals_b(0) = abs_uncertainty_b;
          Eigen::ArrayXd sqrtevals_sb(1);  sqrtevals_sb(0) = abs_uncertainty_sb;
          Eigen::MatrixXd dummy(1,1); dummy(0,0) = 1.0;


          // Compute this SR's DLLs as the differences of s+b and b (partial) LLs
          /// @todo Or compute all the exp DLLs first, then only the best-expected SR's obs DLL?
          /// @todo Only compute this once per run
          const double ll_b_exp = marg_prof_fn(n_preds_b, n_preds_b_int, sqrtevals_b, dummy);
          /// @todo Only compute this once per run
          const double ll_b_obs = marg_prof_fn(n_preds_b, n_obss, sqrtevals_b, dummy);
          const double ll_sb_exp = marg_prof_fn(n_preds_sb, n_preds_b_int, sqrtevals_sb, dummy);
          const double ll_sb_obs = marg_prof_fn(n_preds_sb, n_obss, sqrtevals_sb, dummy);
          const double dll_exp = ll_sb_exp - ll_b_exp;
          const double dll_obs = ll_sb_obs - ll_b_obs;

          // Check for problems
          if (Utils::isnan(ll_b_exp))
          {
            std::stringstream msg;
            msg << "Computation of ll_b_exp for signal region " << srData.sr_label << " in analysis " << ananame << " returned NaN" << endl;
            invalid_point().raise(msg.str());
          }
          if (Utils::isnan(ll_b_obs))
          {
            std::stringstream msg;
            msg << "Computation of ll_b_obs for signal region " << srData.sr_label << " in analysis " << ananame << " returned NaN" << endl;
            invalid_point().raise(msg.str());
          }
          if (Utils::isnan(ll_sb_exp))
          {
            std::stringstream msg;
            msg << "Computation of ll_sb_exp for signal region " << srData.sr_label << " in analysis " << ananame << " returned NaN" << endl;
            invalid_point().raise(msg.str());
          }
          if (Utils::isnan(ll_sb_obs))
          {
            std::stringstream msg;
            msg << "Computation of ll_sb_obs for signal region " << srData.sr_label << " in analysis " << ananame << " returned NaN" << endl;
            invalid_point().raise(msg.str());
          }

          // Update the running best-expected-exclusion detail
          if (dll_exp < bestexp_dll_exp || SR == 0)
          {
            bestexp_dll_exp = dll_exp;
            bestexp_dll_obs = dll_obs;
            bestexp_sr_label = srData.sr_label;
            bestexp_sr_index = SR;
            #ifdef COLLIDERBIT_DEBUG
            cout << DEBUG_PREFIX << "Setting bestexp_sr_label to: " << bestexp_sr_label << ", LogL_exp = " << bestexp_dll_exp << ", LogL_obs = " << bestexp_dll_obs << endl;
            #endif
          }

          // Store (obs) result for this SR
          result.sr_indices[srData.sr_label] = SR;
          result.sr_loglikes[srData.sr_label] = dll_obs;
          // Also add the obs loglike to the no-correlations sum over SRs
          nocovar_srsum_dll_obs += dll_obs;

          #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << ananame << ", " << srData.sr_label << ",  llsb_exp-llb_exp = " << dll_exp << ",  llsb_obs-llb_obs= " << dll_obs << endl;
          #endif

        }

        // Set this analysis' total obs DLL to that from the best-expected SR
        ana_dll = bestexp_dll_obs;
        result.combination_sr_label = bestexp_sr_label;
        result.combination_sr_index = bestexp_sr_index;
        result.combination_loglike = ana_dll;

        // Or should we use the naive sum of SR loglikes (without correlations) instead?
        if (combine_nocovar_SRs)
        {
          result.combination_loglike = nocovar_srsum_dll_obs;
        }

        #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: " << ananame << "_" << bestexp_sr_label << "_LogLike : " << ana_dll << endl;
        #endif

      } // end cov/no-cov


      // Check for problems with the result
      for(auto& s_d_pair : result.sr_loglikes)
      {
        if (Utils::isnan(s_d_pair.second))
        {
          std::stringstream msg;
          msg << "Computation of loglike for signal region " << s_d_pair.first << " in analysis " << ananame << " returned NaN" << endl;
          msg << "Will now print the signal region data for this analysis:" << endl;
          for (size_t SR = 0; SR < nSR; ++SR)
          {
            const SignalRegionData& srData = adata[SR];
            msg << srData.sr_label
                << ",  n_bkg = " << srData.n_bkg
                << ",  n_bkg_err = " << srData.n_bkg_err
                << ",  n_obs = " << srData.n_obs
                << ",  n_sig_scaled = " << srData.n_sig_scaled
                << ",  n_sig_MC = " << srData.n_sig_MC
                << ",  n_sig_MC_sys = " << srData.n_sig_MC_sys
                << endl;
          }
          invalid_point().raise(msg.str());
        }
      }

      return result;
    }


    /// Loop over all analyses and fill a map of AnalysisLogLikes objects
    void calc_LHC_LogLikes(map_str_AnalysisLogLikes& result)
    {
      // Read options
      using namespace Pipes::calc_LHC_LogLikes;
      // Use covariance matrices if available?
      static const bool USE_COVAR = runOptions->getValueOrDef<bool>(true, "use_covariances");
      // Use marginalisation rather than profiling (probably less stable)?
      static const bool USE_MARG = runOptions->getValueOrDef<bool>(false, "use_marginalising");
      // Use the naive sum of SR loglikes for analyses without known correlations?
      static const bool combine_nocovar_SRs = runOptions->getValueOrDef<bool>(false, "combine_SRs_without_covariances");

      // Clear the result map
      result.clear();

      // Loop over analyses in Dep::AllAnalysisNumbers
      // Main loop over all analyses to compute DLL = LL_sb - LL_b
      for (size_t analysis = 0; analysis < Dep::AllAnalysisNumbers->size(); ++analysis)
      {
        // AnalysisData for this analysis
        const AnalysisData& adata = *(Dep::AllAnalysisNumbers->at(analysis));
        const std::string ananame = adata.analysis_name;

        #ifdef COLLIDERBIT_DEBUG
        std::streamsize stream_precision = cout.precision();  // get current precision
        cout.precision(2);  // set precision
        cout << DEBUG_PREFIX << "calc_LHC_LogLikes: " << "Will print content of " << ananame << " signal regions:" << endl;
        for (size_t SR = 0; SR < adata.size(); ++SR)
        {
          const SignalRegionData& srData = adata[SR];
          cout << std::fixed << DEBUG_PREFIX
                                 << "calc_LHC_LogLikes: " << ananame
                                 << ", " << srData.sr_label
                                 << ",  n_b = " << srData.n_bkg << " +/- " << srData.n_bkg_err
                                 << ",  n_obs = " << srData.n_obs
                                 << ",  excess = " << srData.n_obs - srData.n_bkg << " +/- " << srData.n_bkg_err
                                 << ",  n_s = " << srData.n_sig_scaled
                                 << ",  (excess-n_s) = " << (srData.n_obs-srData.n_bkg) - srData.n_sig_scaled << " +/- " << srData.n_bkg_err
                                 << ",  n_s_MC = " << srData.n_sig_MC
                                 << endl;
        }
        cout.precision(stream_precision); // restore previous precision
        #endif

        bool set_zero_loglike = false;
        if (not Dep::RunMC->event_gen_BYPASS && (not Dep::RunMC->event_generation_began || Dep::RunMC->exceeded_maxFailedEvents) )
        {
          set_zero_loglike = true;
        }

        // Get loglike(s) for the current analysis
        AnalysisLogLikes aloglikes = calc_loglikes_for_analysis(adata, USE_COVAR, USE_MARG, combine_nocovar_SRs, set_zero_loglike);
        
        // Save to results map
        result[ananame] = aloglikes;

      } // end analysis loop

    }




    /// Extract the combined log likelihood for each analysis
    void get_LHC_LogLike_per_analysis(map_str_dbl& result)
    {
      using namespace Pipes::get_LHC_LogLike_per_analysis;

      std::stringstream summary_line;
      summary_line << "LHC loglikes per analysis: ";

      for (const std::pair<str,AnalysisLogLikes> pair : *Dep::LHC_LogLikes)
      {
        const str& analysis_name = pair.first;
        const AnalysisLogLikes& analysis_loglikes = pair.second;

        result[analysis_name] = analysis_loglikes.combination_loglike;

        summary_line << analysis_name << ":" << analysis_loglikes.combination_loglike << ", ";
      }
      logger() << LogTags::debug << summary_line.str() << EOM;
    }


    /// Extract the log likelihood for each SR
    void get_LHC_LogLike_per_SR(map_str_dbl& result)
    {
      using namespace Pipes::get_LHC_LogLike_per_SR;

      std::stringstream summary_line;
      summary_line << "LHC loglikes per SR: ";

      for (const std::pair<str,AnalysisLogLikes> pair_i : *Dep::LHC_LogLikes)
      {
        const str& analysis_name = pair_i.first;
        const AnalysisLogLikes& analysis_loglikes = pair_i.second;

        summary_line << analysis_name << ": ";

        for (const std::pair<str,double> pair_j : analysis_loglikes.sr_loglikes)
        {
          const str& sr_label = pair_j.first;
          const double& sr_loglike = pair_j.second;
          const int sr_index = analysis_loglikes.sr_indices.at(sr_label);

          const str key = analysis_name + "__" + sr_label + "__i" + std::to_string(sr_index) + "__LogLike";
          result[key] = sr_loglike;

          summary_line << sr_label + "__i" + std::to_string(sr_index) << ":" << sr_loglike << ", ";
        }

        result[analysis_name + "__combined_LogLike"] = analysis_loglikes.combination_loglike;

        summary_line << "combined_LogLike:" << analysis_loglikes.combination_loglike << ", ";
      }
      logger() << LogTags::debug << summary_line.str() << EOM;
    }


    /// Extract the labels for the SRs used in the analysis loglikes
    void get_LHC_LogLike_SR_labels(map_str_str& result)
    {
      using namespace Pipes::get_LHC_LogLike_per_SR;
      for (const std::pair<str,AnalysisLogLikes> pair_i : *Dep::LHC_LogLikes)
      {
        const str& analysis_name = pair_i.first;
        const AnalysisLogLikes& analysis_loglikes = pair_i.second;

        result[analysis_name] = analysis_loglikes.combination_sr_label;
      }
    }


    /// Extract the indices for the SRs used in the analysis loglikes
    /// @todo Switch result type to map_str_int once we have implemented a printer for this type
    void get_LHC_LogLike_SR_indices(map_str_dbl& result)
    {
      using namespace Pipes::get_LHC_LogLike_per_SR;

      std::stringstream summary_line;
      summary_line << "LHC loglike SR indices: ";

      // Loop over analyses
      for (const std::pair<str,AnalysisLogLikes> pair_i : *Dep::LHC_LogLikes)
      {
        const str& analysis_name = pair_i.first;
        const AnalysisLogLikes& analysis_loglikes = pair_i.second;

        result[analysis_name] = (double) analysis_loglikes.combination_sr_index;

        summary_line << analysis_name << ":" << analysis_loglikes.combination_sr_index << ", ";
      }
      logger() << LogTags::debug << summary_line.str() << EOM;
    }


    /// Compute the total likelihood combining all analyses
    void calc_combined_LHC_LogLike(double& result)
    {
      using namespace Pipes::calc_combined_LHC_LogLike;
      result = 0.0;

      static const bool write_summary_to_log = runOptions->getValueOrDef<bool>(false, "write_summary_to_log");

      std::stringstream summary_line_combined_loglike; 
      summary_line_combined_loglike << "calc_combined_LHC_LogLike: combined LogLike: ";
      std::stringstream summary_line_skipped_analyses;
      summary_line_skipped_analyses << "calc_combined_LHC_LogLike: skipped analyses: ";
      std::stringstream summary_line_included_analyses;
      summary_line_included_analyses << "calc_combined_LHC_LogLike: included analyses: ";

      // Read analysis names from the yaml file
      std::vector<str> default_skip_analyses;  // The default is empty lists of analyses to skip
      static const std::vector<str> skip_analyses = runOptions->getValueOrDef<std::vector<str> >(default_skip_analyses, "skip_analyses");

      // If too many events have failed, do the conservative thing and return delta log-likelihood = 0
      if (Dep::RunMC->exceeded_maxFailedEvents)
      {
        #ifdef COLLIDERBIT_DEBUG
          cout << DEBUG_PREFIX << "calc_combined_LHC_LogLike: Too many failed events. Will be conservative and return a delta log-likelihood of 0." << endl;
        #endif
        return;
      }

      // Loop over analyses and calculate the total observed dLL
      for (auto const& analysis_loglike_pair : *Dep::LHC_LogLike_per_analysis)
      {
        const str& analysis_name = analysis_loglike_pair.first;
        const double& analysis_loglike = analysis_loglike_pair.second;

        // If the analysis name is in skip_analyses, don't add its loglike to the total loglike.
        if (std::find(skip_analyses.begin(), skip_analyses.end(), analysis_name) != skip_analyses.end())
        {
          #ifdef COLLIDERBIT_DEBUG
            cout.precision(5);
            cout << DEBUG_PREFIX << "calc_combined_LHC_LogLike: Leaving out analysis " << analysis_name << " with LogL = " << analysis_loglike << endl;
          #endif

          // Add to log summary
          if(write_summary_to_log)
          {
            summary_line_skipped_analyses << analysis_name << "__LogLike:" << analysis_loglike << ", ";
          }

          continue;
        }

        // Add analysis loglike.
        // If using capped likelihood for each individual analysis, set analysis_loglike = min(analysis_loglike,0)
        static const bool use_cap_loglike_individual = runOptions->getValueOrDef<bool>(false, "cap_loglike_individual_analyses");
        if (use_cap_loglike_individual)
        {
          result += std::min(analysis_loglike, 0.0);
        }
        else
        {
          result += analysis_loglike;
        }

        // Add to log summary
        if(write_summary_to_log)
        {
          summary_line_included_analyses << analysis_name << "__LogLike:" << analysis_loglike << ", ";
        }

        #ifdef COLLIDERBIT_DEBUG
          cout.precision(5);
          cout << DEBUG_PREFIX << "calc_combined_LHC_LogLike: Analysis " << analysis_name << " contributes with a LogL = " << analysis_loglike << endl;
        #endif
      }

      #ifdef COLLIDERBIT_DEBUG
        cout << DEBUG_PREFIX << "calc_combined_LHC_LogLike: LHC_Combined_LogLike = " << result << endl;
      #endif

      // If using a "global" capped likelihood, set result = min(result,0)
      static const bool use_cap_loglike = runOptions->getValueOrDef<bool>(false, "cap_loglike");
      if (use_cap_loglike)
      {
        result = std::min(result, 0.0);
      }

      // Write log summary
      if(write_summary_to_log)
      {
        summary_line_combined_loglike << result;

        logger() << summary_line_combined_loglike.str() << EOM;
        logger() << summary_line_included_analyses.str() << EOM;
        logger() << summary_line_skipped_analyses.str() << EOM;
      }  
    }


    /// A dummy log-likelihood that helps the scanner track a given 
    /// range of collider log-likelihood values
    void calc_LHC_LogLike_scan_guide(double& result)
    {
      using namespace Pipes::calc_LHC_LogLike_scan_guide;
      result = 0.0;

      static const bool write_summary_to_log = runOptions->getValueOrDef<bool>(false, "write_summary_to_log");
      static const double target_LHC_loglike = runOptions->getValue<double>("target_LHC_loglike");
      static const double target_width = runOptions->getValue<double>("width_LHC_loglike");

      // Get the combined LHC loglike
      double LHC_loglike = *Dep::LHC_Combined_LogLike;

      // Calculate the dummy scan guide loglike using a gaussian centered on the target LHC loglike value
      result = Stats::gaussian_loglikelihood(LHC_loglike, target_LHC_loglike, 0.0, target_width, false);

      // Write log summary
      if(write_summary_to_log)
      {
        std::stringstream summary_line; 
        summary_line << "LHC_LogLike_scan_guide: " << result;
        logger() << summary_line.str() << EOM;
      }  
    }

  }
}
