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
///  \author Chris Chang
///  \date   2026 Jun
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
    double limit_LLike(double x, double x95, double sigma)
    {
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


    // *** Limits from e+e- colliders ***


    // The LEP slepton and gaugino likelihoods are all computed by the single
    // module function calc_LEP_LogLikes (further below), which returns a map of
    // the individual per-analysis log-likelihoods. The cross sections needed by
    // the likelihoods are computed on the fly via the helpers below, rather than
    // being provided as separate capabilities.


    /// @name Thin wrappers around the LEP cross-section helpers in lep_mssm_xsecs.hpp.
    /// Each returns the cross section (with theory uncertainty) and raises an
    /// error if the result is non-physical.
    /// @{
    triplet<double> LEP_xsec_ll(double sqrts, int generation, int l_chirality, int lbar_chirality,
                                double gtol, double ftol, bool gpt_error, bool fpt_error,
                                const Spectrum& spec, double gammaZ, bool l_are_gauge_es)
    {
      triplet<double> result;
      get_sigma_ee_ll(result, sqrts, generation, l_chirality, lbar_chirality,
                      gtol, ftol, gpt_error, fpt_error, spec, gammaZ, l_are_gauge_es);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
      return result;
    }

    triplet<double> LEP_xsec_chi00(double sqrts, int chi_first, int chi_second,
                                   double tol, bool pt_error, const Spectrum& spec, double gammaZ)
    {
      triplet<double> result;
      get_sigma_ee_chi00(result, sqrts, chi_first, chi_second, tol, pt_error, spec, gammaZ);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
      return result;
    }

    triplet<double> LEP_xsec_chipm(double sqrts, int chi_plus, int chi_minus,
                                   double tol, bool pt_error, const Spectrum& spec, double gammaZ)
    {
      triplet<double> result;
      get_sigma_ee_chipm(result, sqrts, chi_plus, chi_minus, tol, pt_error, spec, gammaZ);
      if (!is_xsec_sane(result))
        ColliderBit_error().raise(LOCAL_INFO, "Non-physical LEP cross section!");
      return result;
    }
    /// @}


    /// @name Per-analysis LEP log-likelihood helpers.
    /// These are plain (non-module) functions, each computing the conservative
    /// log-likelihood for one LEP analysis. They are dispatched from
    /// calc_LEP_LogLikes. The cross sections are computed internally using the
    /// LEP_xsec_* wrappers above.
    /// @{

    /// Selectron/smuon pair production (two same-chirality processes).
    double LEP_slepton_pair_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                  const BaseLimitContainer& limitContainer, int generation,
                                  const str& gauge_es_L, const str& gauge_es_R,
                                  const DecayTable::Entry& decays_L, const DecayTable::Entry& decays_R,
                                  const str& lepton, double tol, bool pt_error)
    {
      using std::pow;

      double max_mixing;
      const SubSpectrum& mssm = spec.get_HE();
      const str sL_string = slhahelp::mass_es_from_gauge_es(gauge_es_L, max_mixing, mssm);
      const str sR_string = slhahelp::mass_es_from_gauge_es(gauge_es_R, max_mixing, mssm);
      const double mass_sL = spec.get(Par::Pole_Mass, sL_string);
      const double mass_sR = spec.get(Par::Pole_Mass, sR_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass, 1000022, 0);
      const double mZ = spec.get(Par::Pole_Mass, 23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;
      double result = 0;

      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // l_L, l_L
      xsecLimit = limitContainer.limitAverage(mass_sL, mass_neut1, mZ);
      xsecWithError = LEP_xsec_ll(sqrts, generation, 1, 1, tol, tol, pt_error, pt_error, spec, gammaZ, true);
      xsecWithError.upper   *= pow(decays_L.BF("~chi0_1", lepton), 2);
      xsecWithError.central *= pow(decays_L.BF("~chi0_1", lepton), 2);
      xsecWithError.lower   *= pow(decays_L.BF("~chi0_1", lepton), 2);
      if (xsecWithError.central < xsecLimit)
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      else
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);

      // l_R, l_R
      xsecLimit = limitContainer.limitAverage(mass_sR, mass_neut1, mZ);
      xsecWithError = LEP_xsec_ll(sqrts, generation, 2, 2, tol, tol, pt_error, pt_error, spec, gammaZ, true);
      xsecWithError.upper   *= pow(decays_R.BF("~chi0_1", lepton), 2);
      xsecWithError.central *= pow(decays_R.BF("~chi0_1", lepton), 2);
      xsecWithError.lower   *= pow(decays_R.BF("~chi0_1", lepton), 2);
      if (xsecWithError.central < xsecLimit)
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      else
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);

      return result;
    }

    /// Stau pair production (two mass-eigenstate processes).
    double LEP_stau_pair_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                               const BaseLimitContainer& limitContainer,
                               const DecayTable::Entry& decays_1, const DecayTable::Entry& decays_2,
                               double gtol, double ftol, bool gpt_error, bool fpt_error,
                               double id_tol, bool id_pterror)
    {
      using std::pow;

      const SubSpectrum& mssm = spec.get_HE();
      const str stau1_string = slhahelp::mass_es_closest_to_family("~tau_1", mssm, id_tol, LOCAL_INFO, id_pterror);
      const str stau2_string = slhahelp::mass_es_closest_to_family("~tau_2", mssm, id_tol, LOCAL_INFO, id_pterror);
      const double mass_stau1 = spec.get(Par::Pole_Mass, stau1_string);
      const double mass_stau2 = spec.get(Par::Pole_Mass, stau2_string);
      const double mass_neut1 = spec.get(Par::Pole_Mass, 1000022, 0);
      const double mZ = spec.get(Par::Pole_Mass, 23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;
      double result = 0;

      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these two processes individually:

      // stau_1, stau_1
      xsecLimit = limitContainer.limitAverage(mass_stau1, mass_neut1, mZ);
      xsecWithError = LEP_xsec_ll(sqrts, 3, 1, 1, gtol, ftol, gpt_error, fpt_error, spec, gammaZ, false);
      xsecWithError.upper   *= pow(decays_1.BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(decays_1.BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower   *= pow(decays_1.BF("~chi0_1", "tau-"), 2);
      if (xsecWithError.central < xsecLimit)
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      else
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);

      // stau_2, stau_2
      xsecLimit = limitContainer.limitAverage(mass_stau2, mass_neut1, mZ);
      xsecWithError = LEP_xsec_ll(sqrts, 3, 2, 2, gtol, ftol, gpt_error, fpt_error, spec, gammaZ, false);
      xsecWithError.upper   *= pow(decays_2.BF("~chi0_1", "tau-"), 2);
      xsecWithError.central *= pow(decays_2.BF("~chi0_1", "tau-"), 2);
      xsecWithError.lower   *= pow(decays_2.BF("~chi0_1", "tau-"), 2);
      if (xsecWithError.central < xsecLimit)
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      else
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);

      return result;
    }

    /// L3 neutralino search, summing over all Z*-like decay channels.
    double LEP_L3_Neutralino_All_Channels_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                                const BaseLimitContainer& limitContainer,
                                                const DecayTable& decays, double tol, bool pt_error)
    {
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str neut_name[3] = {"~chi0_2", "~chi0_3", "~chi0_4"};
      const double neut_mass[3] = {mass_neut2, mass_neut3, mass_neut4};

      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:
      for (int i = 0; i < 3; ++i)
      {
        xsecLimit = limitContainer.limitAverage(neut_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chi00(sqrts, 1, i+2, tol, pt_error, spec, gammaZ);
        // Total up all channels which look like Z* decays
        totalBR = 0;
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "Z0");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "ubar", "u");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "dbar", "d");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "cbar", "c");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "sbar", "s");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "bbar", "b");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "e+", "e-");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "mu+", "mu-");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "tau+", "tau-");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "nubar_e", "nu_e");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "nubar_mu", "nu_mu");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "nubar_tau", "nu_tau");
        xsecWithError.upper   *= totalBR;
        xsecWithError.central *= totalBR;
        xsecWithError.lower   *= totalBR;
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// L3 neutralino search, summing over leptonic Z*-like decay channels.
    double LEP_L3_Neutralino_Leptonic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                            const BaseLimitContainer& limitContainer,
                                            const DecayTable& decays, double tol, bool pt_error)
    {
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str neut_name[3] = {"~chi0_2", "~chi0_3", "~chi0_4"};
      const double neut_mass[3] = {mass_neut2, mass_neut3, mass_neut4};

      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:
      for (int i = 0; i < 3; ++i)
      {
        xsecLimit = limitContainer.limitAverage(neut_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chi00(sqrts, 1, i+2, tol, pt_error, spec, gammaZ);
        // Total up all channels which look like leptonic Z* decays
        // Total up the leptonic Z decays first...
        totalBR = 0;
        totalBR += decays.at("Z0").BF("e+", "e-");
        totalBR += decays.at("Z0").BF("mu+", "mu-");
        totalBR += decays.at("Z0").BF("tau+", "tau-");
        totalBR = decays.at(neut_name[i]).BF("~chi0_1", "Z0") * totalBR;

        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "e+", "e-");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "mu+", "mu-");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "tau+", "tau-");
        xsecWithError.upper   *= totalBR;
        xsecWithError.central *= totalBR;
        xsecWithError.lower   *= totalBR;
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL neutralino search, summing over hadronic Z*-like decay channels.
    double LEP_OPAL_Neutralino_Hadronic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                              const BaseLimitContainer& limitContainer,
                                              const DecayTable& decays, double tol, bool pt_error)
    {
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_neut2 = spec.get(Par::Pole_Mass,1000023, 0);
      const double mass_neut3 = spec.get(Par::Pole_Mass,1000025, 0);
      const double mass_neut4 = spec.get(Par::Pole_Mass,1000035, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str neut_name[3] = {"~chi0_2", "~chi0_3", "~chi0_4"};
      const double neut_mass[3] = {mass_neut2, mass_neut3, mass_neut4};

      // Due to the nature of the analysis details of the model independent limit in
      // the paper, the best we can do is to try these processes individually:
      for (int i = 0; i < 3; ++i)
      {
        xsecLimit = limitContainer.limitAverage(neut_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chi00(sqrts, 1, i+2, tol, pt_error, spec, gammaZ);
        // Total up all channels which look like Z* decays
        totalBR = decays.at("Z0").BF("hadron", "hadron");
        totalBR = decays.at(neut_name[i]).BF("~chi0_1", "Z0") * totalBR;
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "ubar", "u");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "dbar", "d");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "cbar", "c");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "sbar", "s");
        totalBR += decays.at(neut_name[i]).BF("~chi0_1", "bbar", "b");
        xsecWithError.upper   *= totalBR;
        xsecWithError.central *= totalBR;
        xsecWithError.lower   *= totalBR;
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// L3 chargino search, summing over all W*-like decay channels.
    double LEP_L3_Chargino_All_Channels_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                              const BaseLimitContainer& limitContainer,
                                              const DecayTable& decays, double tol, bool pt_error)
    {
      using std::pow;

      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const SubSpectrum& mssm = spec.get_HE();
      const double mass_neut1 = lsp.mass;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like W* decays
        totalBR = 0;
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "W+");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "u", "dbar");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "c", "sbar");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "e+", "nu_e");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "mu+", "nu_mu");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "tau+", "nu_tau");
        totalBR += decays.at(char_name[i]).BF(snue, "e+")
                 * decays.at(snue).BF("~chi0_1", "nu_e");
        totalBR += decays.at(char_name[i]).BF(snumu, "mu+")
                 * decays.at(snumu).BF("~chi0_1", "nu_mu");
        totalBR += decays.at(char_name[i]).BF(snutau, "tau+")
                 * decays.at(snutau).BF("~chi0_1", "nu_tau");
        xsecWithError.upper   *= pow(totalBR, 2);
        xsecWithError.central *= pow(totalBR, 2);
        xsecWithError.lower   *= pow(totalBR, 2);
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// L3 chargino search, summing over leptonic W*-like decay channels.
    double LEP_L3_Chargino_Leptonic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                          const BaseLimitContainer& limitContainer,
                                          const DecayTable& decays, double tol, bool pt_error)
    {
      using std::pow;

      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const SubSpectrum& mssm = spec.get_HE();
      const double mass_neut1 = lsp.mass;
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like leptonic W* decays
        // Total up the leptonic W decays first...
        totalBR = 0;
        totalBR += decays.at("W+").BF("e+", "nu_e");
        totalBR += decays.at("W+").BF("mu+", "nu_mu");
        totalBR += decays.at("W+").BF("tau+", "nu_tau");
        totalBR = decays.at(char_name[i]).BF(lsp.name, "W+") * totalBR;

        totalBR += decays.at(char_name[i]).BF("~chi0_1", "e+", "nu_e");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "mu+", "nu_mu");
        totalBR += decays.at(char_name[i]).BF("~chi0_1", "tau+", "nu_tau");

        totalBR += decays.at(char_name[i]).BF(snue, "e+")
                 * decays.at(snue).BF("~chi0_1", "nu_e");
        totalBR += decays.at(char_name[i]).BF(snumu, "mu+")
                 * decays.at(snumu).BF("~chi0_1", "nu_mu");
        totalBR += decays.at(char_name[i]).BF(snutau, "tau+")
                 * decays.at(snutau).BF("~chi0_1", "nu_tau");

        xsecWithError.upper   *= pow(totalBR, 2);
        xsecWithError.central *= pow(totalBR, 2);
        xsecWithError.lower   *= pow(totalBR, 2);
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL chargino search, hadronic channels.
    double LEP_OPAL_Chargino_Hadronic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                            const BaseLimitContainer& limitContainer,
                                            const DecayTable& decays, double tol, bool pt_error)
    {
      using std::pow;

      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like hadronic W* decays
        // Total up the hadronic W decays first...
        totalBR = decays.at("W+").BF("hadron", "hadron");
        totalBR = decays.at(char_name[i]).BF(lsp.name, "W+") * totalBR;

        totalBR += decays.at(char_name[i]).BF(lsp.name, "u", "dbar");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "c", "sbar");
        xsecWithError.upper   *= pow(totalBR, 2);
        xsecWithError.central *= pow(totalBR, 2);
        xsecWithError.lower   *= pow(totalBR, 2);
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL chargino search, semi-leptonic channels.
    double LEP_OPAL_Chargino_SemiLeptonic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                                const BaseLimitContainer& limitContainer,
                                                const DecayTable& decays, double tol, bool pt_error)
    {
      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const SubSpectrum& mssm = spec.get_HE();
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like leptonic W* decays
        // Total up the leptonic W decays first...
        totalBR = 0;
        totalBR += decays.at("W+").BF("e+", "nu_e");
        totalBR += decays.at("W+").BF("mu+", "nu_mu");
        totalBR += decays.at("W+").BF("tau+", "nu_tau");
        totalBR = decays.at(char_name[i]).BF(lsp.name, "W+") * totalBR;

        totalBR += decays.at(char_name[i]).BF(lsp.name, "e+", "nu_e");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "mu+", "nu_mu");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "tau+", "nu_tau");

        // We don't have sneutrino --> gravitino + neutrino decays
        if (lsp.pdg != 1000039)
        {
          totalBR += decays.at(char_name[i]).BF(snue, "e+")
                   * decays.at(snue).BF(lsp.name, "nu_e");
          totalBR += decays.at(char_name[i]).BF(snumu, "mu+")
                   * decays.at(snumu).BF(lsp.name, "nu_mu");
          totalBR += decays.at(char_name[i]).BF(snutau, "tau+")
                   * decays.at(snutau).BF(lsp.name, "nu_tau");
        }

        xsecWithError.upper   *= totalBR;
        xsecWithError.central *= totalBR;
        xsecWithError.lower   *= totalBR;

        // ALSO, total up all channels which look like hadronic W* decays
        // Total up the hadronic W decays first...
        totalBR = decays.at("W+").BF("hadron", "hadron");
        totalBR = decays.at(char_name[i]).BF(lsp.name, "W+") * totalBR;

        totalBR += decays.at(char_name[i]).BF(lsp.name, "u", "dbar");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "c", "sbar");
        xsecWithError.upper   *= totalBR;
        xsecWithError.central *= totalBR;
        xsecWithError.lower   *= totalBR;

        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL chargino search, leptonic channels.
    double LEP_OPAL_Chargino_Leptonic_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                            const BaseLimitContainer& limitContainer,
                                            const DecayTable& decays, double tol, bool pt_error)
    {
      using std::pow;

      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const SubSpectrum& mssm = spec.get_HE();
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like leptonic W* decays
        // Total up the leptonic W decays first...
        totalBR = 0;
        totalBR += decays.at("W+").BF("e+", "nu_e");
        totalBR += decays.at("W+").BF("mu+", "nu_mu");
        totalBR += decays.at("W+").BF("tau+", "nu_tau");
        totalBR = decays.at(char_name[i]).BF(lsp.name, "W+") * totalBR;

        totalBR += decays.at(char_name[i]).BF(lsp.name, "e+", "nu_e");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "mu+", "nu_mu");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "tau+", "nu_tau");

        // We don't have sneutrino --> gravitino + neutrino decays
        if (lsp.pdg != 1000039)
        {
          totalBR += decays.at(char_name[i]).BF(snue, "e+")
                   * decays.at(snue).BF(lsp.name, "nu_e");
          totalBR += decays.at(char_name[i]).BF(snumu, "mu+")
                   * decays.at(snumu).BF(lsp.name, "nu_mu");
          totalBR += decays.at(char_name[i]).BF(snutau, "tau+")
                   * decays.at(snutau).BF(lsp.name, "nu_tau");
        }

        xsecWithError.upper   *= pow(totalBR, 2);
        xsecWithError.central *= pow(totalBR, 2);
        xsecWithError.lower   *= pow(totalBR, 2);
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL chargino search, all channels.
    double LEP_OPAL_Chargino_All_Channels_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                                const BaseLimitContainer& limitContainer,
                                                const DecayTable& decays, double tol, bool pt_error)
    {
      using std::pow;

      const LSP lsp = get_LSP_for_LEP_limits(spec);
      const SubSpectrum& mssm = spec.get_HE();
      const str snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snumu = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol, LOCAL_INFO, pt_error);
      const str snutau = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol, LOCAL_INFO, pt_error);
      const double mass_neut1 = lsp.mass;
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mass_char2 = spec.get(Par::Pole_Mass,1000037, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit, totalBR;
      double result = 0;

      const str char_name[2] = {"~chi+_1", "~chi+_2"};
      const double char_mass[2] = {mass_char1, mass_char2};
      const int char_idx[2] = {1, 2};

      for (int i = 0; i < 2; ++i)
      {
        xsecLimit = limitContainer.limitAverage(char_mass[i], mass_neut1, mZ);
        xsecWithError = LEP_xsec_chipm(sqrts, char_idx[i], char_idx[i], tol, pt_error, spec, gammaZ);
        // Total up all channels which look like W* decays
        totalBR = 0;
        totalBR += decays.at(char_name[i]).BF(lsp.name, "W+");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "u", "dbar");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "c", "sbar");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "e+", "nu_e");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "mu+", "nu_mu");
        totalBR += decays.at(char_name[i]).BF(lsp.name, "tau+", "nu_tau");

        // We don't have sneutrino --> gravitino + neutrino decays
        if (lsp.pdg != 1000039)
        {
          totalBR += decays.at(char_name[i]).BF(snue, "e+")
                   * decays.at(snue).BF(lsp.name, "nu_e");
          totalBR += decays.at(char_name[i]).BF(snumu, "mu+")
                   * decays.at(snumu).BF(lsp.name, "nu_mu");
          totalBR += decays.at(char_name[i]).BF(snutau, "tau+")
                   * decays.at(snutau).BF(lsp.name, "nu_tau");
        }

        xsecWithError.upper   *= pow(totalBR, 2);
        xsecWithError.central *= pow(totalBR, 2);
        xsecWithError.lower   *= pow(totalBR, 2);
        if (xsecWithError.central < xsecLimit)
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
        else
          result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);
      }

      return result;
    }

    /// OPAL limit on degenerate chargino--neutralino scenario at 208 GeV.
    /// Sensitive to mass differences between 320 MeV and 5 GeV.
    /// Based on hep-ex/0210043.
    double LEP_OPAL_Degenerate_Chargino_LLike(const Spectrum& spec, double gammaZ, double sqrts,
                                              const BaseLimitContainer& limitContainer,
                                              double tol, bool pt_error)
    {
      const double mass_neut1 = spec.get(Par::Pole_Mass,1000022, 0);
      const double mass_char1 = spec.get(Par::Pole_Mass,1000024, 0);
      const double mZ = spec.get(Par::Pole_Mass,23, 0);
      triplet<double> xsecWithError;
      double xsecLimit;
      double result = 0;

      // char1, neut1
      xsecLimit = limitContainer.limitAverage(mass_char1, mass_char1-std::abs(mass_neut1), mZ);
      xsecWithError = LEP_xsec_chipm(sqrts, 1, 1, tol, pt_error, spec, gammaZ);

      if (xsecWithError.central < xsecLimit)
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.upper - xsecWithError.central);
      else
        result += limit_LLike(xsecWithError.central, xsecLimit, xsecWithError.central - xsecWithError.lower);

      return result;
    }
    /// @}


    /// Compute the individual LEP slepton and gaugino log-likelihoods, returning
    /// them as a map from analysis name to log-likelihood. The set of analyses
    /// to include is controlled by the "analyses" option (default: the standard
    /// non-overlapping set of LEP limits).
    void calc_LEP_LogLikes(map_str_dbl& result)
    {
      using namespace Pipes::calc_LEP_LogLikes;
      result.clear();

      // The standard non-overlapping set of LEP analyses.
      static const std::vector<str> default_analyses =
      {
        "ALEPH_Selectron", "ALEPH_Smuon", "ALEPH_Stau",
        "L3_Selectron", "L3_Smuon", "L3_Stau",
        "L3_Neutralino_Leptonic", "L3_Chargino_Leptonic",
        "OPAL_Chargino_Hadronic", "OPAL_Chargino_SemiLeptonic", "OPAL_Chargino_Leptonic",
        "OPAL_Neutralino_Hadronic"
      };
      const std::vector<str> analyses = runOptions->getValueOrDef<std::vector<str> >(default_analyses, "analyses");

      // Mixing tolerances and point-invalidation flags, with the same option
      // names and historical defaults as the original individual functions.
      const double gtol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const bool   gpt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      const double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const bool   fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      // The stau mass-eigenstate identification historically used different
      // defaults for the family-mixing tolerance and point-invalidation flag.
      const double stau_id_tol = runOptions->getValueOrDef<double>(1e-5, "family_mixing_tolerance");
      const bool   stau_id_pterror = runOptions->getValueOrDef<bool>(false, "family_mixing_tolerance_invalidates_point_only");

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const double gammaZ = Dep::Z_decay_rates->width_in_GeV;
      const DecayTable& decays = *Dep::decay_rates;
      const DecayTable::Entry& sel_l = *Dep::selectron_l_decay_rates;
      const DecayTable::Entry& sel_r = *Dep::selectron_r_decay_rates;
      const DecayTable::Entry& smu_l = *Dep::smuon_l_decay_rates;
      const DecayTable::Entry& smu_r = *Dep::smuon_r_decay_rates;
      const DecayTable::Entry& stau_1 = *Dep::stau_1_decay_rates;
      const DecayTable::Entry& stau_2 = *Dep::stau_2_decay_rates;

      std::stringstream summary_line;
      summary_line << "LEP loglikes per analysis: ";

      for (const str& analysis : analyses)
      {
        double llike;

        if (analysis == "ALEPH_Selectron")
        {
          static const ALEPHSelectronLimitAt208GeV lc;
          llike = LEP_slepton_pair_LLike(spec, gammaZ, 208.0, lc, 1, "~e_L", "~e_R", sel_l, sel_r, "e-", gtol, gpt_error);
        }
        else if (analysis == "ALEPH_Smuon")
        {
          static const ALEPHSmuonLimitAt208GeV lc;
          llike = LEP_slepton_pair_LLike(spec, gammaZ, 208.0, lc, 2, "~mu_L", "~mu_R", smu_l, smu_r, "mu-", gtol, gpt_error);
        }
        else if (analysis == "ALEPH_Stau")
        {
          static const ALEPHStauLimitAt208GeV lc;
          llike = LEP_stau_pair_LLike(spec, gammaZ, 208.0, lc, stau_1, stau_2, gtol, ftol, gpt_error, fpt_error, stau_id_tol, stau_id_pterror);
        }
        else if (analysis == "L3_Selectron")
        {
          static const L3SelectronLimitAt205GeV lc;
          llike = LEP_slepton_pair_LLike(spec, gammaZ, 205.0, lc, 1, "~e_L", "~e_R", sel_l, sel_r, "e-", gtol, gpt_error);
        }
        else if (analysis == "L3_Smuon")
        {
          static const L3SmuonLimitAt205GeV lc;
          llike = LEP_slepton_pair_LLike(spec, gammaZ, 205.0, lc, 2, "~mu_L", "~mu_R", smu_l, smu_r, "mu-", gtol, gpt_error);
        }
        else if (analysis == "L3_Stau")
        {
          static const L3StauLimitAt205GeV lc;
          llike = LEP_stau_pair_LLike(spec, gammaZ, 205.0, lc, stau_1, stau_2, gtol, ftol, gpt_error, fpt_error, stau_id_tol, stau_id_pterror);
        }
        else if (analysis == "L3_Neutralino_All_Channels")
        {
          static const L3NeutralinoAllChannelsLimitAt188pt6GeV lc;
          llike = LEP_L3_Neutralino_All_Channels_LLike(spec, gammaZ, 188.6, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "L3_Neutralino_Leptonic")
        {
          static const L3NeutralinoLeptonicLimitAt188pt6GeV lc;
          llike = LEP_L3_Neutralino_Leptonic_LLike(spec, gammaZ, 188.6, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "L3_Chargino_All_Channels")
        {
          static const L3CharginoAllChannelsLimitAt188pt6GeV lc;
          llike = LEP_L3_Chargino_All_Channels_LLike(spec, gammaZ, 188.6, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "L3_Chargino_Leptonic")
        {
          static const L3CharginoLeptonicLimitAt188pt6GeV lc;
          llike = LEP_L3_Chargino_Leptonic_LLike(spec, gammaZ, 188.6, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Chargino_Hadronic")
        {
          static const OPALCharginoHadronicLimitAt208GeV lc;
          llike = LEP_OPAL_Chargino_Hadronic_LLike(spec, gammaZ, 208.0, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Chargino_SemiLeptonic")
        {
          static const OPALCharginoSemiLeptonicLimitAt208GeV lc;
          llike = LEP_OPAL_Chargino_SemiLeptonic_LLike(spec, gammaZ, 208.0, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Chargino_Leptonic")
        {
          static const OPALCharginoLeptonicLimitAt208GeV lc;
          llike = LEP_OPAL_Chargino_Leptonic_LLike(spec, gammaZ, 208.0, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Chargino_All_Channels")
        {
          static const OPALCharginoAllChannelsLimitAt208GeV lc;
          llike = LEP_OPAL_Chargino_All_Channels_LLike(spec, gammaZ, 208.0, lc, decays, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Degenerate_Chargino")
        {
          static const OPALDegenerateCharginoLimitAt208GeV lc;
          llike = LEP_OPAL_Degenerate_Chargino_LLike(spec, gammaZ, 208.0, lc, gtol, gpt_error);
        }
        else if (analysis == "OPAL_Neutralino_Hadronic")
        {
          static const OPALNeutralinoHadronicLimitAt208GeV lc;
          llike = LEP_OPAL_Neutralino_Hadronic_LLike(spec, gammaZ, 208.0, lc, decays, gtol, gpt_error);
        }
        else
        {
          ColliderBit_error().raise(LOCAL_INFO, "Unknown LEP analysis '" + analysis
            + "' requested in the 'analyses' option of calc_LEP_LogLikes.");
          continue;
        }

        result[analysis] = llike;
        summary_line << analysis << ":" << llike << ", ";
      }

      logger() << LogTags::debug << summary_line.str() << EOM;
    }

    /// Combine the individual LEP log-likelihoods (LEP_LogLikes) into a single
    /// total LEP log-likelihood.
    void calc_LEP_Combined_LogLike(double& result)
    {
      using namespace Pipes::calc_LEP_Combined_LogLike;
      result = 0;
      for (const std::pair<const str, double>& pair : *Dep::LEP_LogLikes)
      {
        result += pair.second;
      }
    }

    void L3_Gravitino_LLike(double& result)
    {
      /**
         @brief L3 search for gravitinos at 207 GeV

         We use a limit from Fig. 6c of
         https://doi.org/10.1016/j.physletb.2004.01.010.

         We use the 95% upper limit on
         \f[
         \sigma(ee \to \chi^0_1\chi^0_1) \textrm{BR}(\chi^0_1 \to \tilde{G}\gamma)^2
         \f]
      */
      using namespace Pipes::L3_Gravitino_LLike;
      using std::pow;
      static const double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      static const bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");

      // Unpack neutralino & gravitino mass
      const Spectrum& spectrum = *Dep::MSSM_spectrum;
      const double m_chi = spectrum.get(Par::Pole_Mass, 1000022, 0);
      const double m_gravitino = spectrum.get(Par::Pole_Mass, 1000039, 0);

      // Calculate relevant branching ratio
      const DecayTable& decay_rates = *Dep::decay_rates;
      const auto BF = decay_rates.at("~chi0_1").BF("gamma", "~G");

      // Production cross section of two lightest neutralinos at 207 GeV
      const triplet<double> production_xsec = LEP_xsec_chi00(207.0, 1, 1, tol, pt_error, spectrum, Dep::Z_decay_rates->width_in_GeV);

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
