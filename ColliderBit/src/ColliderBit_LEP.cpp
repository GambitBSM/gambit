//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit LEP likelihoods.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///  \author Anders Kvellestad
///          (anders.kvellestad@nordita.org)
///
///  \author Are Raklev
///          (ahye@fys.uio.no)
///  \date   2018 Feb
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date   2018 Feb
///
///  *********************************************

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/ColliderBit/lep_mssm_xsecs.hpp"
#include "gambit/ColliderBit/limits/ImageLimit.hpp"

//#define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// A simple struct and helper function to determine if the LSP is
    /// the lightest neutralino or the gravitino.
    struct LSP
    {
      int pdg;
      str name;
      double mass;
    };

    LSP get_LSP_for_LEP_limits(const Spectrum& spec)
    {
      LSP lsp;

      // Start by assuming the neutralino_1 is LSP
      lsp.pdg = 1000022;
      lsp.name = "~chi0_1";
      lsp.mass = std::abs(spec.get(Par::Pole_Mass, 1000022, 0));

      // Check if gravitino is LSP
      if (spec.has(Par::Pole_Mass, 1000039, 0))
      {
        double m = spec.get(Par::Pole_Mass, 1000039, 0);
        if (m < lsp.mass)
        {
          lsp.pdg = 1000039;
          lsp.name = "~G";
          lsp.mass = m;
        }
      }

      return lsp;
    }



    // *** Limits from e+e- colliders ***



    /// LEP limit likelihood function
    double limit_LLike(double x, double x95, double sigma) {
      /**
         @brief Incorporate theoretical uncertainty in a 95% limit
         @param x Predicted cross section
         @param x95 Experimental 95% upper limit on cross section
         @param sigma Theoretical uncertainty on predicted cross section
         @returns Log-likelihood
      */
      static double p95 = 1.;
      using std::erf;
      using std::sqrt;

      if (p95 < 1.01)
      {
        for (int i=0; i<20000; i++)
        {
          static double step = 0.1;
          if (0.5 * (1 - erf(p95 + step)) > 0.05) p95 += step;
          else step /= 10.;
        }
      }

      double result = 0.5 * (1.0 - erf(p95 + (x - x95) / sigma / sqrt(2.)));

      if (result < 0.0 or Utils::isnan(result))
      {
        cout << "result: " << result << endl;
        cout << "x: " << x << endl;
        cout << "x95: " << x95 << endl;
        cout << "sigma: " << sigma << endl;
        cout << "p95: " << p95 << endl;
        cout << "(x - x95) / sigma / sqrt(2.): " << (x - x95) / sigma / sqrt(2.) << endl;
        cout << "erf(p95 + (x - x95) / sigma / sqrt(2.)): " << erf(p95 + (x - x95) / sigma / sqrt(2.)) << endl;
        ColliderBit_error().raise(LOCAL_INFO, "Suspicious results in limit_LLike!");
      }

      return (result == 0.0 ? -1e10 : log(result));
    }


        /// LEP limit debugging function
    bool is_xsec_sane(const triplet<double>& xsecWithError)
    {
      double xsec = xsecWithError.central;
      double dxsec_upper = xsecWithError.upper - xsecWithError.central;
      double dxsec_lower = xsecWithError.central - xsecWithError.lower;
      if (xsec < 0.0 or dxsec_upper < 0.0 or dxsec_lower < 0.0
          or Utils::isnan(xsec) or Utils::isnan(dxsec_upper) or Utils::isnan(dxsec_lower))
      {
        cout << "xsec: " << xsec << endl;
        cout << "dxsec_upper: " << dxsec_upper << endl;
        cout << "dxsec_lower: " << dxsec_lower << endl;
        return false;
      }
      return true;
    }



    /// ee --> selectron pair production cross-sections at 208 GeV
    /// @{
    void LEP208_SLHA1_convention_xsec_selselbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_selselbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_selserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_selserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_serserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_serserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_serselbar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_serselbar::Dep::LEP208_xsec_selserbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_se1se1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_se1se1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_se1se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_se1se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_se2se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_se2se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 1, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_se2se1bar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_se2se1bar::Dep::LEP208_xsec_se1se2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> smuon pair production cross-sections at 208 GeV
    /// @{
    void LEP208_SLHA1_convention_xsec_smulsmulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smulsmulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smulsmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smulsmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smursmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smursmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smursmulbar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_smursmulbar::Dep::LEP208_xsec_smulsmurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smu1smu1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smu1smu1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smu1smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smu1smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smu2smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_smu2smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 2, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_smu2smu1bar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_smu2smu1bar::Dep::LEP208_xsec_smu1smu2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> stau pair production cross-sections at 208 GeV
    /// @{
    void LEP208_SLHA1_convention_xsec_staulstaulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_staulstaulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_staulstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_staulstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_staurstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_staurstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_staurstaulbar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_staurstaulbar::Dep::LEP208_xsec_staulstaurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_stau1stau1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_stau1stau1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_stau1stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_stau1stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_stau2stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_stau2stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 208.0, 3, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_stau2stau1bar(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_stau2stau1bar::Dep::LEP208_xsec_stau1stau2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    // @brief \f[ee \to \chi_1\chi_1\f] pair production cross-section at 207 GeV
    void LEP207_SLHA1_convention_xsec_chi00_11(triplet<double>& result) {
      using namespace Pipes::LEP207_SLHA1_convention_xsec_chi00_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 207.0, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result)) {
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
      }
    }

    /// ee --> neutralino pair production cross-sections at 208 GeV
    /// @{
    void LEP208_SLHA1_convention_xsec_chi00_11(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_12(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_13(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_13;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 1, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_14(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_14;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 1, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_22(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_23(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_23;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 2, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_24(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_24;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 2, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_33(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_33;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 3, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_34(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_34;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 3, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chi00_44(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chi00_44;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 208.0, 4, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> chargino pair production cross-sections at 208 GeV
    /// @{
    void LEP208_SLHA1_convention_xsec_chipm_11(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chipm_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 208.0, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chipm_12(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chipm_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 208.0, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chipm_22(triplet<double>& result)
    {
      using namespace Pipes::LEP208_SLHA1_convention_xsec_chipm_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 208.0, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP208_SLHA1_convention_xsec_chipm_21(triplet<double>& result)
    {
      result = *Pipes::LEP208_SLHA1_convention_xsec_chipm_21::Dep::LEP208_xsec_chipm_12;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> selectron pair production cross-sections at 205 GeV
    /// @{
    void LEP205_SLHA1_convention_xsec_selselbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_selselbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_selserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_selserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_serserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_serserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_serselbar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_serselbar::Dep::LEP205_xsec_selserbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_se1se1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_se1se1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_se1se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_se1se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_se2se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_se2se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 1, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_se2se1bar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_se2se1bar::Dep::LEP205_xsec_se1se2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> smuon pair production cross-sections at 205 GeV
    /// @{
    void LEP205_SLHA1_convention_xsec_smulsmulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smulsmulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smulsmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smulsmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smursmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smursmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smursmulbar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_smursmulbar::Dep::LEP205_xsec_smulsmurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smu1smu1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smu1smu1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smu1smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smu1smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smu2smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_smu2smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 2, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_smu2smu1bar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_smu2smu1bar::Dep::LEP205_xsec_smu1smu2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> stau pair production cross-sections at 205 GeV
    /// @{
    void LEP205_SLHA1_convention_xsec_staulstaulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_staulstaulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_staulstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_staulstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_staurstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_staurstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_staurstaulbar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_staurstaulbar::Dep::LEP205_xsec_staulstaurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_stau1stau1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_stau1stau1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_stau1stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_stau1stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_stau2stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_stau2stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 205.0, 3, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_stau2stau1bar(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_stau2stau1bar::Dep::LEP205_xsec_stau1stau2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> neutralino pair production cross-sections at 205 GeV
    /// @{
    void LEP205_SLHA1_convention_xsec_chi00_11(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_12(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_13(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_13;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 1, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_14(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_14;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 1, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_22(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_23(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_23;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 2, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_24(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_24;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 2, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_33(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_33;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 3, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_34(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_34;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 3, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chi00_44(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chi00_44;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 205.0, 4, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> chargino pair production cross-sections at 205 GeV
    /// @{
    void LEP205_SLHA1_convention_xsec_chipm_11(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chipm_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 205.0, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chipm_12(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chipm_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 205.0, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chipm_22(triplet<double>& result)
    {
      using namespace Pipes::LEP205_SLHA1_convention_xsec_chipm_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 205.0, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP205_SLHA1_convention_xsec_chipm_21(triplet<double>& result)
    {
      result = *Pipes::LEP205_SLHA1_convention_xsec_chipm_21::Dep::LEP205_xsec_chipm_12;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }

    /// ee --> selectron pair production cross-sections at 188.6 GeV
    /// @{
    void LEP188_SLHA1_convention_xsec_selselbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_selselbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_selserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_selserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_serserbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_serserbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_serselbar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_serselbar::Dep::LEP188_xsec_selserbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_se1se1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_se1se1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_se1se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_se1se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_se2se2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_se2se2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 1, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_se2se1bar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_se2se1bar::Dep::LEP188_xsec_se1se2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> smuon pair production cross-sections at 188.6 GeV
    /// @{
    void LEP188_SLHA1_convention_xsec_smulsmulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smulsmulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smulsmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smulsmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smursmurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smursmurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smursmulbar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_smursmulbar::Dep::LEP188_xsec_smulsmurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smu1smu1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smu1smu1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smu1smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smu1smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smu2smu2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_smu2smu2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 2, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_smu2smu1bar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_smu2smu1bar::Dep::LEP188_xsec_smu1smu2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}

    /// ee --> stau pair production cross-sections at 188.6 GeV
    /// @{
    void LEP188_SLHA1_convention_xsec_staulstaulbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_staulstaulbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 1, 1, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_staulstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_staulstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 1, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_staurstaurbar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_staurstaurbar;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 2, 2, tol, tol, pt_error, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, true);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_staurstaulbar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_staurstaulbar::Dep::LEP188_xsec_staulstaurbar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_stau1stau1bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_stau1stau1bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 1, 1, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_stau1stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_stau1stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 1, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_stau2stau2bar(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_stau2stau2bar;
      const static double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_ll(result, 188.6, 3, 2, 2, gtol, ftol, gpt_error, fpt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV, false);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_stau2stau1bar(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_stau2stau1bar::Dep::LEP188_xsec_stau1stau2bar;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> neutralino pair production cross-sections at 188.6 GeV
    /// @{
    void LEP188_SLHA1_convention_xsec_chi00_11(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_12(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_13(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_13;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 1, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_14(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_14;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 1, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_22(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_23(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_23;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 2, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_24(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_24;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 2, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_33(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_33;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 3, 3, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_34(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_34;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 3, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chi00_44(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chi00_44;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chi00(result, 188.6, 4, 4, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// ee --> chargino pair production cross-sections at 188.6 GeV
    /// @{
    void LEP188_SLHA1_convention_xsec_chipm_11(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chipm_11;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 188.6, 1, 1, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chipm_12(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chipm_12;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 188.6, 1, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chipm_22(triplet<double>& result)
    {
      using namespace Pipes::LEP188_SLHA1_convention_xsec_chipm_22;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      get_sigma_ee_chipm(result, 188.6, 2, 2, tol, pt_error, *Dep::MSSM_spectrum, Dep::Z_decay_rates->width_in_GeV);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    void LEP188_SLHA1_convention_xsec_chipm_21(triplet<double>& result)
    {
      result = *Pipes::LEP188_SLHA1_convention_xsec_chipm_21::Dep::LEP188_xsec_chipm_12;
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
    }
    /// @}


    /// LEP Slepton Log-Likelihoods
    /// @{
    void ALEPH_Selectron_Conservative_LLike(double& result)
    {
      using namespace Pipes::ALEPH_Selectron_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      double max_mixing;
      const SubSpectrum& mssm = spec.get_HE();
      str sel_string = slhahelp::mass_es_from_gauge_es("~e_L", max_mixing, mssm);
      str ser_string = slhahelp::mass_es_from_gauge_es("~e_R", max_mixing, mssm);
      const double mass_seL=spec.get(Par::Pole_Mass,sel_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_seR = spec.get(Par::Pole_Mass,ser_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const ALEPHSelectronLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //static bool dumped=false;
      //if(!dumped)
      //{
      //  limitContainer.dumpPlotData(45., 115., 0., 100., mZ, "lepLimitPlanev2/ALEPHSelectronLimitAt208GeV.dump");
      //  dumped=true;
      //}
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // se_L, se_L
      xsecLimit = limitContainer.limitAverage(mass_seL, mass_neut1, mZ);
      xsecWithError = *Dep::LEP208_xsec_selselbar;
      xsecWithError.upper *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.central *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.lower *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // se_R, se_R
      xsecLimit = limitContainer.limitAverage(mass_seR, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_serserbar;
      xsecWithError.upper *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.central *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.lower *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void ALEPH_Smuon_Conservative_LLike(double& result)
    {
      using namespace Pipes::ALEPH_Smuon_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      double max_mixing;
      const SubSpectrum& mssm = spec.get_HE();
      str smul_string = slhahelp::mass_es_from_gauge_es("~mu_L", max_mixing, mssm);
      str smur_string = slhahelp::mass_es_from_gauge_es("~mu_R", max_mixing, mssm);
      const double mass_smuL=spec.get(Par::Pole_Mass,smul_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_smuR = spec.get(Par::Pole_Mass,smur_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const ALEPHSmuonLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45., 115., 0., 100., mZ, "lepLimitPlanev2/ALEPHSmuonLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // smu_L, smu_L
      xsecLimit = limitContainer.limitAverage(mass_smuL, mass_neut1, mZ);
      xsecWithError = *Dep::LEP208_xsec_smulsmulbar;
      xsecWithError.upper *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.central *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.lower *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // smu_R, smu_R
      xsecLimit = limitContainer.limitAverage(mass_smuR, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_smursmurbar;
      xsecWithError.upper *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.central *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.lower *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void ALEPH_Stau_Conservative_LLike(double& result)
    {
      using namespace Pipes::ALEPH_Stau_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      const SubSpectrum& mssm = spec.get_HE();
      static const double tol = runOptions->getValueOrDef<double>(1e-5, "family_mixing_tolerance");
      static const bool pterror = runOptions->getValueOrDef<bool>(false, "family_mixing_tolerance_invalidates_point_only");
      str stau1_string = slhahelp::mass_es_closest_to_family("~tau_1", mssm,tol,LOCAL_INFO,pterror);
      str stau2_string = slhahelp::mass_es_closest_to_family("~tau_2", mssm,tol,LOCAL_INFO,pterror);
      const double mass_stau1=spec.get(Par::Pole_Mass,stau1_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_stau2 = spec.get(Par::Pole_Mass,stau2_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const ALEPHStauLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45., 115., 0., 100., mZ, "lepLimitPlanev2/ALEPHStauLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // stau_1, stau_1
      xsecLimit = limitContainer.limitAverage(mass_stau1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_stau1stau1bar;
      xsecWithError.upper *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // stau_2, stau_2
      xsecLimit = limitContainer.limitAverage(mass_stau2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_stau2stau2bar;
      xsecWithError.upper *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Selectron_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Selectron_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      double max_mixing;
      const SubSpectrum& mssm = spec.get_HE();
      str sel_string = slhahelp::mass_es_from_gauge_es("~e_L", max_mixing, mssm);
      str ser_string = slhahelp::mass_es_from_gauge_es("~e_R", max_mixing, mssm);
      const double mass_seL=spec.get(Par::Pole_Mass,sel_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_seR = spec.get(Par::Pole_Mass,ser_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const L3SelectronLimitAt205GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
         static bool dumped=false;
         if(!dumped)
         {
           limitContainer.dumpPlotData(45., 104., 0., 100., mZ, "lepLimitPlanev2/L3SelectronLimitAt205GeV.dump",200);
           dumped=true;
         }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // se_L, se_L
      xsecLimit = limitContainer.limitAverage(mass_seL, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_selselbar;
      xsecWithError.upper *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.central *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.lower *= pow(Dep::selectron_l_decay_rates->BF("~chi0_1", "e-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // se_R, se_R
      xsecLimit = limitContainer.limitAverage(mass_seR, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_serserbar;
      xsecWithError.upper *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.central *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);
      xsecWithError.lower *= pow(Dep::selectron_r_decay_rates->BF("~chi0_1", "e-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Smuon_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Smuon_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      double max_mixing;
      const SubSpectrum& mssm = spec.get_HE();
      str smul_string = slhahelp::mass_es_from_gauge_es("~mu_L", max_mixing, mssm);
      str smur_string = slhahelp::mass_es_from_gauge_es("~mu_R", max_mixing, mssm);
      const double mass_smuL=spec.get(Par::Pole_Mass,smul_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_smuR = spec.get(Par::Pole_Mass,smur_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const L3SmuonLimitAt205GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      // static bool dumped=false;
      // if(!dumped)
      // {
      //   limitContainer.dumpPlotData(45., 115., 0., 100., mZ, "lepLimitPlanev2/L3SmuonLimitAt205GeV.dump");
      //   dumped=true;
      // }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // smu_L, smu_L
      xsecLimit = limitContainer.limitAverage(mass_smuL, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_smulsmulbar;
      xsecWithError.upper *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.central *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.lower *= pow(Dep::smuon_l_decay_rates->BF("~chi0_1", "mu-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // smu_R, smu_R
      xsecLimit = limitContainer.limitAverage(mass_smuR, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_smursmurbar;
      xsecWithError.upper *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.central *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);
      xsecWithError.lower *= pow(Dep::smuon_r_decay_rates->BF("~chi0_1", "mu-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Stau_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Stau_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      const SubSpectrum& mssm = spec.get_HE();
      static const double tol = runOptions->getValueOrDef<double>(1e-5, "family_mixing_tolerance");
      static const bool pterror = runOptions->getValueOrDef<bool>(false, "family_mixing_tolerance_invalidates_point_only");
      str stau1_string = slhahelp::mass_es_closest_to_family("~tau_1", mssm,tol,LOCAL_INFO,pterror);
      str stau2_string = slhahelp::mass_es_closest_to_family("~tau_2", mssm,tol,LOCAL_INFO,pterror);
      const double mass_stau1=spec.get(Par::Pole_Mass,stau1_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_stau2 = spec.get(Par::Pole_Mass,stau2_string);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const L3StauLimitAt205GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45., 115., 0., 100., mZ, "lepLimitPlanev2/L3StauLimitAt205GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // stau_1, stau_1
      xsecLimit = limitContainer.limitAverage(mass_stau1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_stau1stau1bar;
      xsecWithError.upper *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower *= pow(Dep::stau_1_decay_rates->BF("~chi0_1", "tau-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // stau_2, stau_2
      xsecLimit = limitContainer.limitAverage(mass_stau2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP205_xsec_stau2stau2bar;
      xsecWithError.upper *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower *= pow(Dep::stau_2_decay_rates->BF("~chi0_1", "tau-"), 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }
    /// @}

    /// LEP Gaugino Log-Likelihoods
    /// @{
    void L3_Neutralino_All_Channels_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Neutralino_All_Channels_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      const DecayTable& decays = *Dep::decay_rates;
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const L3NeutralinoAllChannelsLimitAt188pt6GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(0., 200., 0., 100., mZ, "lepLimitPlanev2/L3NeutralinoAllChannelsLimitAt188pt6GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // neut2, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_12;
      // Total up all channels which look like Z* decays
      totalBR = 0;
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "Z0");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "bbar", "b");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "tau+", "tau-");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "nubar_e", "nu_e");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "nubar_mu", "nu_mu");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "nubar_tau", "nu_tau");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut3, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut3, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_13;
      // Total up all channels which look like Z* decays
      totalBR = 0;
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "Z0");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "bbar", "b");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "tau+", "tau-");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "nubar_e", "nu_e");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "nubar_mu", "nu_mu");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "nubar_tau", "nu_tau");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut4, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut4, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_14;
      // Total up all channels which look like Z* decays
      totalBR = 0;
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "Z0");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "bbar", "b");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "tau+", "tau-");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "nubar_e", "nu_e");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "nubar_mu", "nu_mu");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "nubar_tau", "nu_tau");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Neutralino_Leptonic_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Neutralino_Leptonic_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      const DecayTable& decays = *Dep::decay_rates;
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const L3NeutralinoLeptonicLimitAt188pt6GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      // static bool dumped=false;
      // if(!dumped)
      // {
      //   limitContainer.dumpPlotData(0., 200., 0., 100., mZ, "lepLimitPlanev2/L3NeutralinoLeptonicLimitAt188pt6GeV.dump");
      //   dumped=true;
      // }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // neut2, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_12;
      // Total up all channels which look like leptonic Z* decays
      // Total up the leptonic Z decays first...
      totalBR = 0;
      totalBR += decays.at("Z0").BF("e+", "e-");
      totalBR += decays.at("Z0").BF("mu+", "mu-");
      totalBR += decays.at("Z0").BF("tau+", "tau-");
      totalBR = decays.at("~chi0_2").BF("~chi0_1", "Z0") * totalBR;

      totalBR += decays.at("~chi0_2").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "tau+", "tau-");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut3, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut3, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_13;
      // Total up all channels which look like leptonic Z* decays
      // Total up the leptonic Z decays first...
      totalBR = 0;
      totalBR += decays.at("Z0").BF("e+", "e-");
      totalBR += decays.at("Z0").BF("mu+", "mu-");
      totalBR += decays.at("Z0").BF("tau+", "tau-");
      totalBR = decays.at("~chi0_3").BF("~chi0_1", "Z0") * totalBR;

      totalBR += decays.at("~chi0_3").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "tau+", "tau-");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut4, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut4, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chi00_14;
      // Total up all channels which look like leptonic Z* decays
      // Total up the leptonic Z decays first...
      totalBR = 0;
      totalBR += decays.at("Z0").BF("e+", "e-");
      totalBR += decays.at("Z0").BF("mu+", "mu-");
      totalBR += decays.at("Z0").BF("tau+", "tau-");
      totalBR = decays.at("~chi0_4").BF("~chi0_1", "Z0") * totalBR;

      totalBR += decays.at("~chi0_4").BF("~chi0_1", "e+", "e-");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "mu+", "mu-");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "tau+", "tau-");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Chargino_All_Channels_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Chargino_All_Channels_Conservative_LLike;
      using std::pow;
      using std::log;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const SubSpectrum& mssm = spec.get_HE();
      const DecayTable& decays = *Dep::decay_rates;

      const double mass_neut1 = lsp.mass;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const L3CharginoAllChannelsLimitAt188pt6GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45., 100., 0., 100., mZ, "lepLimitPlanev2/L3CharginoAllChannelsLimitAt188pt6GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chipm_11;
      // Total up all channels which look like W* decays
      totalBR = 0;
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "W+");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "u", "dbar");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "c", "sbar");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "e+", "nu_e");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "mu+", "nu_mu");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "tau+", "nu_tau");
      totalBR += decays.at("~chi+_1").BF(snue, "e+")
               * decays.at(snue).BF("~chi0_1", "nu_e");
      totalBR += decays.at("~chi+_1").BF(snumu, "mu+")
               * decays.at(snumu).BF("~chi0_1", "nu_mu");
      totalBR += decays.at("~chi+_1").BF(snutau, "tau+")
               * decays.at(snutau).BF("~chi0_1", "nu_tau");
      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chipm_22;
      // Total up all channels which look like W* decays
      totalBR = 0;
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "W+");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "u", "dbar");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "c", "sbar");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "e+", "nu_e");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "mu+", "nu_mu");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "tau+", "nu_tau");
      totalBR += decays.at("~chi+_2").BF(snue, "e+")
               * decays.at(snue).BF("~chi0_1", "nu_e");
      totalBR += decays.at("~chi+_2").BF(snumu, "mu+")
               * decays.at(snumu).BF("~chi0_1", "nu_mu");
      totalBR += decays.at("~chi+_2").BF(snutau, "tau+")
               * decays.at(snutau).BF("~chi0_1", "nu_tau");
      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void L3_Chargino_Leptonic_Conservative_LLike(double& result)
    {
      using namespace Pipes::L3_Chargino_Leptonic_Conservative_LLike;
      using std::pow;
      using std::log;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const SubSpectrum& mssm = spec.get_HE();
      const DecayTable& decays = *Dep::decay_rates;

      const double mass_neut1 = lsp.mass;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const L3CharginoLeptonicLimitAt188pt6GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45., 100., 0., 100., mZ, "lepLimitPlanev2/L3CharginoLeptonicLimitAt188pt6GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chipm_11;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_1").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_1").BF("~chi0_1", "e+", "nu_e");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "mu+", "nu_mu");
      totalBR += decays.at("~chi+_1").BF("~chi0_1", "tau+", "nu_tau");

      totalBR += decays.at("~chi+_1").BF(snue, "e+")
               * decays.at(snue).BF("~chi0_1", "nu_e");
      totalBR += decays.at("~chi+_1").BF(snumu, "mu+")
               * decays.at(snumu).BF("~chi0_1", "nu_mu");
      totalBR += decays.at("~chi+_1").BF(snutau, "tau+")
               * decays.at(snutau).BF("~chi0_1", "nu_tau");

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP188_xsec_chipm_22;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_2").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_2").BF("~chi0_1", "e+", "nu_e");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "mu+", "nu_mu");
      totalBR += decays.at("~chi+_2").BF("~chi0_1", "tau+", "nu_tau");

      totalBR += decays.at("~chi+_2").BF(snue, "e+")
               * decays.at(snue).BF("~chi0_1", "nu_e");
      totalBR += decays.at("~chi+_2").BF(snumu, "mu+")
               * decays.at(snumu).BF("~chi0_1", "nu_mu");
      totalBR += decays.at("~chi+_2").BF(snutau, "tau+")
               * decays.at(snutau).BF("~chi0_1", "nu_tau");

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void OPAL_Chargino_Hadronic_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Chargino_Hadronic_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const DecayTable& decays = *Dep::decay_rates;
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const OPALCharginoHadronicLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(75., 105., 0., 105., mZ, "lepLimitPlanev2/OPALCharginoHadronicLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_11;
      // Total up all channels which look like hadronic W* decays
      // Total up the hadronic W decays first...
      totalBR = decays.at("W+").BF("hadron", "hadron");
      totalBR = decays.at("~chi+_1").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_1").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "c", "sbar");
      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_22;
      // Total up all channels which look like hadronic W* decays
      // Total up the hadronic W decays first...
      totalBR = decays.at("W+").BF("hadron", "hadron");
      totalBR = decays.at("~chi+_2").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_2").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "c", "sbar");
      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void OPAL_Chargino_SemiLeptonic_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Chargino_SemiLeptonic_Conservative_LLike;
      using std::pow;
      using std::log;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const SubSpectrum& mssm = spec.get_HE();
      const DecayTable& decays = *Dep::decay_rates;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const OPALCharginoSemiLeptonicLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(75., 105., 0., 105., mZ, "lepLimitPlanev2/OPALCharginoSemiLeptonicLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_11;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_1").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_1").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_1").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_1").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_1").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      // ALSO, total up all channels which look like hadronic W* decays
      // Total up the hadronic W decays first...
      totalBR = decays.at("W+").BF("hadron", "hadron");
      totalBR = decays.at("~chi+_1").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_1").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "c", "sbar");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_22;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_2").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_2").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_2").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_2").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_2").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      // ALSO, total up all channels which look like hadronic W* decays
      // Total up the hadronic W decays first...
      totalBR = decays.at("W+").BF("hadron", "hadron");
      totalBR = decays.at("~chi+_2").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_2").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "c", "sbar");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void OPAL_Chargino_Leptonic_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Chargino_Leptonic_Conservative_LLike;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const SubSpectrum& mssm = spec.get_HE();
      const DecayTable& decays = *Dep::decay_rates;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const OPALCharginoLeptonicLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(75., 105., 0., 105., mZ, "lepLimitPlanev2/OPALCharginoLeptonicLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_11;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_1").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_1").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_1").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_1").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_1").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_22;
      // Total up all channels which look like leptonic W* decays
      // Total up the leptonic W decays first...
      totalBR = 0;
      totalBR += decays.at("W+").BF("e+", "nu_e");
      totalBR += decays.at("W+").BF("mu+", "nu_mu");
      totalBR += decays.at("W+").BF("tau+", "nu_tau");
      totalBR = decays.at("~chi+_2").BF(lsp.name, "W+") * totalBR;

      totalBR += decays.at("~chi+_2").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_2").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_2").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_2").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    // OPAL limit on degenerate chargino--neutralino scenario at 208 GeV
    // Sensitive to mass differences between 320 MeV and 5 GeV
    // Based on hep-ex/0210043
    void OPAL_Degenerate_Chargino_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Degenerate_Chargino_Conservative_LLike;

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;

      static const OPALDegenerateCharginoLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(45.0, 95., 0.320, 5., mZ, "lepLimitPlanev2/OPALDegenerateCharginoLimitAt208GeV.dump");
      //
      //     dumped=true;
      //   }
      // #endif

      result = 0;

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_char1-abs(mass_neut1), mZ);
      xsecWithError = *Dep::LEP208_xsec_chipm_11;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }


    void OPAL_Chargino_All_Channels_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Chargino_All_Channels_Conservative_LLike;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const LSP lsp = get_LSP_for_LEP_limits(spec);

      const SubSpectrum& mssm = spec.get_HE();
      const DecayTable& decays = *Dep::decay_rates;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const OPALCharginoAllChannelsLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(75., 105., 0., 105., mZ, "lepLimitPlanev2/OPALCharginoAllChannelsLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_11;
      // Total up all channels which look like W* decays
      totalBR = 0;
      totalBR += decays.at("~chi+_1").BF(lsp.name, "W+");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "c", "sbar");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_1").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_1").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_1").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_1").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // char2, neut1
      xsecLimit = limitContainer.limitAverage(mass_char2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chipm_22;
      // Total up all channels which look like W* decays
      totalBR = 0;
      totalBR += decays.at("~chi+_2").BF(lsp.name, "W+");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "u", "dbar");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "c", "sbar");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "e+", "nu_e");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "mu+", "nu_mu");
      totalBR += decays.at("~chi+_2").BF(lsp.name, "tau+", "nu_tau");

      // We don't have sneutrino --> gravitino + neutrino decays
      if (lsp.pdg != 1000039)
      {
        totalBR += decays.at("~chi+_2").BF(snue, "e+")
                 * decays.at(snue).BF(lsp.name, "nu_e");
        totalBR += decays.at("~chi+_2").BF(snumu, "mu+")
                 * decays.at(snumu).BF(lsp.name, "nu_mu");
        totalBR += decays.at("~chi+_2").BF(snutau, "tau+")
                 * decays.at(snutau).BF(lsp.name, "nu_tau");
      }

      xsecWithError.upper *= pow(totalBR, 2);
      xsecWithError.central *= pow(totalBR, 2);
      xsecWithError.lower *= pow(totalBR, 2);

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    void OPAL_Neutralino_Hadronic_Conservative_LLike(double& result)
    {
      using namespace Pipes::OPAL_Neutralino_Hadronic_Conservative_LLike;
      using std::pow;
      using std::log;

      const Spectrum& spec = *Dep::MSSM_spectrum;

      const DecayTable& decays = *Dep::decay_rates;
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;

      static const OPALNeutralinoHadronicLimitAt208GeV limitContainer;
      // #ifdef COLLIDERBIT_DEBUG
      //   static bool dumped=false;
      //   if(!dumped)
      //   {
      //     limitContainer.dumpPlotData(0., 200., 0., 100., mZ, "lepLimitPlanev2/OPALNeutralinoHadronicLimitAt208GeV.dump");
      //     dumped=true;
      //   }
      // #endif

      result = 0;
      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:

      // neut2, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut2, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chi00_12;
      // Total up all channels which look like Z* decays
      totalBR = decays.at("Z0").BF("hadron", "hadron");
      totalBR = decays.at("~chi0_2").BF("~chi0_1", "Z0") * totalBR;
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_2").BF("~chi0_1", "bbar", "b");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut3, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut3, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chi00_13;
      // Total up all channels which look like Z* decays
      totalBR = decays.at("Z0").BF("hadron", "hadron");
      totalBR = decays.at("~chi0_3").BF("~chi0_1", "Z0") * totalBR;
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_3").BF("~chi0_1", "bbar", "b");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      // neut4, neut1
      xsecLimit = limitContainer.limitAverage(mass_neut4, mass_neut1, mZ);

      xsecWithError = *Dep::LEP208_xsec_chi00_14;
      // Total up all channels which look like Z* decays
      totalBR = decays.at("Z0").BF("hadron", "hadron");
      totalBR = decays.at("~chi0_4").BF("~chi0_1", "Z0") * totalBR;
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "ubar", "u");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "dbar", "d");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "cbar", "c");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "sbar", "s");
      totalBR += decays.at("~chi0_4").BF("~chi0_1", "bbar", "b");
      xsecWithError.upper *= totalBR;
      xsecWithError.central *= totalBR;
      xsecWithError.lower *= totalBR;

      if (xsecWithError.central < xsecLimit)
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      }
      else
      {
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

    }

    /// @}

    void L3_Gravitino_LLike(double& result) {
      /**
         @brief L3 search for gravitinos at 207 GeV

         We use a limit from Fig. 6c of
         https://doi.org/10.1016/j.physletb.2004.01.010.

         We use the 95% upper limit on
         \f[
         \sigma(ee \to \chi^0_1\chi^0_1) \textrm{BR}(\chi^0_1 \to \tilde{G}\gamma)^2
         \f]
      */

      // Unpack neutralino & gravitino mass
      using namespace Pipes::L3_Gravitino_LLike;
      const Spectrum& spectrum = *Dep::MSSM_spectrum;
      const double m_chi = spectrum.get(Par::Pole_Mass, 1000022, 0);
      const double m_gravitino = spectrum.get(Par::Pole_Mass, 1000039, 0);

      // Calculate relevant branching ratio
      const DecayTable& decay_rates = *Dep::decay_rates;
      const auto BF = decay_rates.at("~chi0_1").BF("gamma", "~G");

      // Production cross section of two lightest neutralinos at 207 GeV
      const auto production_xsec = *Dep::LEP207_xsec_chi00_11;

      // Make product of cross section and branching ratio squared
      triplet<double> xsec;
      xsec.upper = production_xsec.upper * pow(BF, 2);
      xsec.central = production_xsec.central * pow(BF, 2);
      xsec.lower = production_xsec.lower * pow(BF, 2);

      // Construct object for fetching limit (do this once only, hence static)
      const std::string fig6c = GAMBIT_DIR "/ColliderBit/data/scraped_fig6c.dat";
      static auto L3Gravitino = ImageLimit(fig6c, 0., 103., 0., 103.);
      const double limit = L3Gravitino.get_limit(m_chi, m_gravitino);

      // Resulting log-likelihood, taking into account theoretical uncertainty
      result = limit_LLike(xsec.central, limit, xsec.upper - xsec.central);
    }

  }  // namespace ColliderBit
}  // namespace Gambit
