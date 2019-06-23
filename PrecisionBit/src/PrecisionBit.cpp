//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions of PrecisionBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Nov
///
///  \author Chris Rogan
///          (crogan@cern.ch)
///  \date 2014 Aug
///
///  \author Ankit Beniwal
///         (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Oct
///
///  *********************************************

#include <algorithm>

// GSL headers
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_permute.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>

// intorduce FlavBit helper routines for likelihood calculations
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/FlavBit/flav_utils.hpp"

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/PrecisionBit/PrecisionBit_rollcall.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/util_functions.hpp"

//#define PRECISIONBIT_DEBUG

/// EWPO theoretical uncertainties on FeynHiggs calculations; based on hep-ph/0412214 Eq 3.1.
/// @{
const double abserr_mw = 1e-2; //10 MeV
const double abserr_sinW2eff = 12e-5;
/// @}

namespace Gambit
{

  namespace PrecisionBit
  {

    using namespace LogTags;

    // Module functions

    void FH_PrecisionObs(fh_PrecisionObs &result)
    {
      using namespace Pipes::FH_PrecisionObs;

      fh_real gm2;        // g_{mu}-2
      fh_real Deltarho;   // deltaRho
      fh_real MWMSSM;     // W pole mass in MSSM
      fh_real MWSM;       // W pole mass in SM
      fh_real SW2MSSM;    // sin^2theta_W^leptonic_effective in MSSM
      fh_real SW2SM;      // sin^2theta_W^leptonic_effective in SM
      fh_real edmeTh;     // electron EDM (experimental)
      fh_real edmn;       // neutron EDM (experimental)
      fh_real edmHg;      // mercury EDM (experimental)
      int ccb;            // model corresponds to charge or colour-breaking minimum (experimental)

      int error = 1;
      BEreq::FHConstraints(error, gm2, Deltarho,
         MWMSSM, MWSM, SW2MSSM, SW2SM,
         edmeTh, edmn, edmHg, ccb);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHConstraints raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      // Just scrub this point now if it's more than 7 sigma off in mW,
      // as extreme values of mW can cause instability in other routines.
      const double obserrsq = mw_err_observed*mw_err_observed;
      const double theoryerrsq = abserr_mw*abserr_mw;
      if (std::abs(mw_central_observed - MWMSSM) > 7.0*sqrt(obserrsq + theoryerrsq))
      {
        std::ostringstream err;
        err << "W mass too extreme. More than 7 sigma off observed value. " << endl
            << "Deviation from observed value: " << std::abs(mw_central_observed - MWMSSM) << "." << endl
            << "1 sigma uncertainty on observed value: " << sqrt(obserrsq + theoryerrsq) << "." << endl
            << "Invalidating immediately to prevent downstream instability.";
        invalid_point().raise(err.str());
        //PrecisionBit_error().raise(LOCAL_INFO, err.str());
      }

      // Just scrub this point now if sinW2 is negative in the MSSM,
      // as negative sinW2 can cause instability in other routines
      // (and this point should be excluded because this is waaay off
      // the observed value).
      if (SW2MSSM <= 0.0)
      {
        std::ostringstream err;
        err << "Sin^2 thetaW_effective is less than zero." << endl
            << "Value computed by FeynHiggs: " << SW2MSSM << endl
            << "Invalidating immediately to prevent downstream instability.";
        invalid_point().raise(err.str());
        //PrecisionBit_error().raise(LOCAL_INFO, err.str());
      }

      #ifdef PRECISIONBIT_DEBUG
        // Just die if any of the other observables look really suspicious.
        str nans;
        if (Utils::isnan(gm2)) nans += "g-2 | ";
        if (Utils::isnan(Deltarho)) nans += "Delta rho | ";
        if (Utils::isnan(MWMSSM)) nans += "MW in MSSM | ";
        if (Utils::isnan(MWSM)) nans += "MW in SM | ";
        if (Utils::isnan(SW2MSSM)) nans += "sin^2 thetaW_effective in MSSM | ";
        if (Utils::isnan(SW2SM)) nans += "sin^2 thetaW_effective in SM | ";
        if (Utils::isnan(edmeTh)) nans += "e EDM | ";
        if (Utils::isnan(edmn)) nans += "n EDM | ";
        if (Utils::isnan(edmHg)) nans += "Hg EDM | ";
        if (not nans.empty()) PrecisionBit_error().raise(LOCAL_INFO, nans+"returned as NaN from FeynHiggs!");
      #endif

      fh_PrecisionObs PrecisionObs;
      PrecisionObs.gmu2 = gm2;
      PrecisionObs.deltaRho = Deltarho;
      PrecisionObs.MW_MSSM = MWMSSM;
      PrecisionObs.MW_SM = MWSM;
      PrecisionObs.sinW2_MSSM = SW2MSSM;
      PrecisionObs.sinW2_SM = SW2SM;
      PrecisionObs.edm_ele = edmeTh;
      PrecisionObs.edm_neu = edmn;
      PrecisionObs.edm_Hg = edmHg;
      PrecisionObs.ccb = ccb;

      result = PrecisionObs;
    }

    /// FeynHiggs precision extractors
    /// @{
    void FH_precision_edm_e   (double &result) { result = Pipes::FH_precision_edm_e::Dep::FH_Precision->edm_ele;     }
    void FH_precision_edm_n   (double &result) { result = Pipes::FH_precision_edm_n::Dep::FH_Precision->edm_neu;     }
    void FH_precision_edm_hg  (double &result) { result = Pipes::FH_precision_edm_hg::Dep::FH_Precision->edm_Hg;     }
    void FH_precision_gm2(triplet<double> &result)
    {
      result.central = Pipes::FH_precision_gm2::Dep::FH_Precision->gmu2;
      result.upper = std::max(std::abs(result.central)*0.3, 6e-10); //Based on hep-ph/0609168v1 eqs 84 & 85
      result.lower = result.upper;
    }
    void FH_precision_deltarho(triplet<double> &result)
    {
      double mw = Pipes::FH_precision_deltarho::Dep::FH_Precision->MW_MSSM;
      double sintw2eff = Pipes::FH_precision_sinW2::Dep::FH_Precision->sinW2_MSSM;
      result.central = Pipes::FH_precision_deltarho::Dep::FH_Precision->deltaRho;
      //Follows approximately from tree level relations, where delta{M_W, sintthetaW^2} go as deltarho
      result.upper = std::max(abserr_mw/mw, abserr_sinW2eff/sintw2eff);
      result.lower = result.upper;
    }
    void FH_precision_mw(triplet<double> &result)
    {
      result.central = Pipes::FH_precision_mw::Dep::FH_Precision->MW_MSSM;
      result.upper = abserr_mw;
      result.lower = result.upper;
    }
    void FH_precision_sinW2   (triplet<double> &result)
    {
      result.central = Pipes::FH_precision_sinW2::Dep::FH_Precision->sinW2_MSSM;
      result.upper = abserr_sinW2eff;
      result.lower = result.upper;
    }
    /// @}

    /// Helper function to set W masses
    void update_W_masses(SubSpectrum& HE, SubSpectrum& LE, const triplet<double>& prec_mw, bool allow_fallback)
    {
      if (prec_mw.central <= 0.0 or Utils::isnan(prec_mw.central))
      {
        if (allow_fallback) return;
        invalid_point().raise("Precison W mass NaN or <= 0.  To allow fallback to the unimproved value, "
                              "set option allow_fallback_to_unimproved_masses=true in your YAML file.");
      }
      HE.set_override(Par::Pole_Mass, prec_mw.central, "W+", true); // "true" flag causes overrides to be written even if no native quantity exists to override.
      HE.set_override(Par::Pole_Mass_1srd_high, prec_mw.upper/prec_mw.central, "W+", true);
      HE.set_override(Par::Pole_Mass_1srd_low, prec_mw.lower/prec_mw.central, "W+", true);
      LE.set_override(Par::Pole_Mass, prec_mw.central, "W+");  // No flag; W mass should definitely already exist in the LE spectrum.
      LE.set_override(Par::Pole_Mass_1srd_high, prec_mw.upper/prec_mw.central, "W+", true);
      LE.set_override(Par::Pole_Mass_1srd_low, prec_mw.lower/prec_mw.central, "W+", true);
    }

    /// Helper function to set arbitrary number of H masses
    void update_H_masses(SubSpectrum& HE, int n_higgs, const str* higgses, int central, int error, std::vector<triplet<double> >& MH, bool allow_fallback)
    {

      for (int i = 0; i < n_higgs; ++i)
      {
        if (MH[i].central <= 0.0 or Utils::isnan(MH[i].central))
        {
          if (allow_fallback) return;
          invalid_point().raise("Precison "+higgses[i]+" mass NaN or <= 0.  To allow fallback to the unimproved value, "
                                "set option allow_fallback_to_unimproved_masses=true in your YAML file.");
        }
      }

      // Central value:
      //  1 = from precision calculator
      //  2 = from spectrum calculator
      //  3 = mean of precision mass and mass from spectrum calculator
      std::vector<double> mh_s;
      for (int i = 0; i < n_higgs; ++i) mh_s.push_back(HE.get(Par::Pole_Mass, higgses[i]));
      double mh[n_higgs];

      #ifdef PRECISIONBIT_DEBUG
        for (int i = 0; i < n_higgs; i++) cout << "h masses, spectrum generator: "<< mh_s[i] << endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, spectrum generator error low: "<< HE.get(Par::Pole_Mass_1srd_low, higgses[i])*mh_s[i] << endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, spectrum generator error high: "<< HE.get(Par::Pole_Mass_1srd_high, higgses[i])*mh_s[i] << endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, precision calculation: "<< MH[i].central << endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, precision calculation error low: "<< MH[i].lower << endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, precision calculation error high: "<< MH[i].upper << endl;
      #endif

      if (central == 1)
      {
        for (int i = 0; i < n_higgs; i++) mh[i] = MH[i].central;
      }
      else if (central == 2)
      {
        for (int i = 0; i < n_higgs; i++) mh[i] = mh_s[i];
      }
      else if (central == 3)
      {
        for (int i = 0; i < n_higgs; i++) mh[i] = 0.5*(MH[i].central + mh_s[i]);
      }
      else
      {
        std::stringstream msg;
        msg << "Unrecognised Higgs_predictions_source option specified for making MSSM precision spectrum: " << central;
        PrecisionBit_error().raise(LOCAL_INFO,msg.str());
      }
      if (central != 2)
      {
        for (int i = 0; i < n_higgs; i++) HE.set_override(Par::Pole_Mass, mh[i], higgses[i]);
      }

      // Uncertainties:
      //  Definitions: D_s = error on mass from spectrum calculator
      //               D_p = error on mass from precision calculator
      //               D_g = difference between central values from spectrum generator and precision calculator
      //  1 = sum in quadrature of D_s, D_p and D_g
      //  2 = range around chosen central (RACC), with D_s and D_p taken at their respective edges.
      //  3 = RACC, with 1/2 * D_g taken at both edges.
      //  4 = RACC, with 1/2 * D_g taken at the spectrum-generator edge, D_p taken at the other edge.
      //  5 = RACC, with 1/2 * D_g taken at the precision-calculator edge, D_s taken at the other edge.
      std::vector<double> D_g;
      for (int i = 0; i < n_higgs; ++i) D_g.push_back(MH[i].central - mh_s[i]);
      double mh_low[n_higgs], mh_high[n_higgs];

      //  1 = sum in quadrature of D_s, D_p and D_g
      if (error == 1)
      {
        for (int i = 0; i < n_higgs; i++)
        {
          double D_s_low = HE.get(Par::Pole_Mass_1srd_low, higgses[i])*mh_s[i];
          double D_s_high = HE.get(Par::Pole_Mass_1srd_high, higgses[i])*mh_s[i];
          double D_p_low = MH[i].lower;
          double D_p_high = MH[i].upper;
          mh_low[i] = sqrt(D_s_low*D_s_low + D_p_low*D_p_low + D_g[i]*D_g[i]);
          mh_high[i] = sqrt(D_s_high*D_s_high + D_p_high*D_p_high + D_g[i]*D_g[i]);
        }
      }

      //  2 = range around chosen central (RACC), with D_s and D_p taken at their respective edges.
      else if (error == 2)
      {
        for (int i = 0; i < n_higgs; i++)
        {
          double D_s_low = mh_s[i]*HE.get(Par::Pole_Mass_1srd_low, higgses[i]);
          double D_s_high = mh_s[i]*HE.get(Par::Pole_Mass_1srd_high, higgses[i]);
          double D_p_low = MH[i].lower;
          double D_p_high = MH[i].upper;
          if (central == 1) // Using precision calculator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = D_g[i] + D_s_low;
              mh_high[i] = D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low;
              mh_high[i] = D_s_high-D_g[i];
            }
          }
          else if (central == 2) // Using spectrum generator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = D_s_low;
              mh_high[i] = D_g[i] + D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low-D_g[i];
              mh_high[i] = D_s_high;
            }
          }
          else  // Using mean of spectrum gen and precision calc as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 0.5*D_g[i] + D_s_low;
              mh_high[i] = 0.5*D_g[i] + D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low - 0.5*D_g[i];
              mh_high[i] = D_s_high - 0.5*D_g[i];
            }
          }
        }
      }

      //  3 = RACC, with 1/2 * D_g taken at both edges.
      else if (error == 3)
      {
        for (int i = 0; i < n_higgs; i++)
        {
          if (central == 1) // Using precision calculator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 1.5*D_g[i];
              mh_high[i] = 0.5*D_g[i];
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = -0.5*D_g[i];
              mh_high[i] = -1.5*D_g[i];
            }
          }
          else if (central == 2) // Using spectrum generator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 0.5*D_g[i];
              mh_high[i] = 1.5*D_g[i];
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = -1.5*D_g[i];
              mh_high[i] = -0.5*D_g[i];
            }
          }
          else  // Using mean of spectrum gen and precision calc as central value
          {
            mh_low[i] = fabs(D_g[i]);
            mh_high[i] = mh_low[i];
          }
        }
      }

      //  4 = RACC, with 1/2 * D_g taken at the spectrum-generator edge, D_p taken at the other edge.
      else if (error == 4)
      {
        for (int i = 0; i < n_higgs; i++)
        {
          double D_p_low = MH[i].lower;
          double D_p_high = MH[i].upper;
          if (central == 1) // Using precision calculator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 1.5*D_g[i];
              mh_high[i] = D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low;
              mh_high[i] = -1.5*D_g[i];
            }
          }
          else if (central == 2) // Using spectrum generator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 0.5*D_g[i];
              mh_high[i] = D_g[i] + D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low-D_g[i];
              mh_high[i] = -0.5*D_g[i];
            }
          }
          else  // Using mean of spectrum gen and precision calc as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = D_g[i];
              mh_high[i] = 0.5*D_g[i] + D_p_high;
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = D_p_low - 0.5*D_g[i];
              mh_high[i] = -D_g[i];
            }
          }
        }
      }

      //  5 = RACC, with 1/2 * D_g taken at the precision-calculator edge, D_s taken at the other edge.
      else if (error == 5)
      {
        for (int i = 0; i < n_higgs; i++)
        {
          double D_s_low = mh_s[i]*HE.get(Par::Pole_Mass_1srd_low, higgses[i]);
          double D_s_high = mh_s[i]*HE.get(Par::Pole_Mass_1srd_high, higgses[i]);
          if (central == 1) // Using precision calculator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = D_g[i] + D_s_low;
              mh_high[i] = 0.5*D_g[i];
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = -0.5*D_g[i];
              mh_high[i] = D_s_high-D_g[i];
            }
          }
          else if (central == 2) // Using spectrum generator mass as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = D_s_low;
              mh_high[i] = 1.5*D_g[i];
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = -1.5*D_g[i];
              mh_high[i] = D_s_high;
            }
          }
          else  // Using mean of spectrum gen and precision calc as central value
          {
            if (D_g[i] >= 0) // Precision calculator mass is higher than spectrum generator mass
            {
              mh_low[i] = 0.5*D_g[i] + D_s_low;
              mh_high[i] = D_g[i];
            }
            else // Precision calculator mass is lower than spectrum generator mass
            {
              mh_low[i] = -D_g[i];
              mh_high[i] = D_s_high - 0.5*D_g[i];
            }
          }
        }
      }

      //  >5 = failure
      else
      {
        std::stringstream msg;
        msg << "Unrecognised Higgs_predictions_error_method specified for make_MSSM_precision_spectrum: " << central;
        PrecisionBit_error().raise(LOCAL_INFO,msg.str());
      }

      // Finally, set the errors.
      for (int i = 0; i < n_higgs; i++) HE.set_override(Par::Pole_Mass_1srd_low, mh_low[i]/mh[i], higgses[i], true);
      for (int i = 0; i < n_higgs; i++) HE.set_override(Par::Pole_Mass_1srd_high, mh_high[i]/mh[i], higgses[i], true);

      #ifdef PRECISIONBIT_DEBUG
        for (int i = 0; i < n_higgs; i++) cout << "h masses, central: "<< HE.get(Par::Pole_Mass, higgses[i])<< endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, fractional low: "<< HE.get(Par::Pole_Mass_1srd_low, higgses[i])<< endl;
        for (int i = 0; i < n_higgs; i++) cout << "h masses, fractional high: " << HE.get(Par::Pole_Mass_1srd_high, higgses[i])<<endl;
      #endif
    }

    /// Precision MSSM spectrum manufacturer that does nothing but relabel the unimproved spectrum
    void make_MSSM_precision_spectrum_none(Spectrum& improved_spec /*(result)*/)
    {
      using namespace Pipes::make_MSSM_precision_spectrum_none;
      improved_spec = *Dep::unimproved_MSSM_spectrum; // Does copy
      improved_spec.drop_SLHAs_if_requested(runOptions, "GAMBIT_spectrum");
    }

    /// Precision MSSM spectrum manufacturer with precision W mass only
    void make_MSSM_precision_spectrum_W(Spectrum& improved_spec /*(result)*/)
    {
      using namespace Pipes::make_MSSM_precision_spectrum_W;
      improved_spec = *Dep::unimproved_MSSM_spectrum; // Does copy
      static bool allow_fallback = runOptions->getValueOrDef<bool>(false, "allow_fallback_to_unimproved_masses");
      update_W_masses(improved_spec.get_HE(), improved_spec.get_LE(), *Dep::prec_mw, allow_fallback);
      improved_spec.drop_SLHAs_if_requested(runOptions, "GAMBIT_spectrum");
    }

    /// Precision MSSM spectrum manufacturer with precision SM-like Higgs mass
    void make_MSSM_precision_spectrum_H(Spectrum& improved_spec /*(result)*/)
    {
      using namespace Pipes::make_MSSM_precision_spectrum_H;
      improved_spec = *Dep::unimproved_MSSM_spectrum; // Does copy
      SubSpectrum& HE = improved_spec.get_HE();
      static bool allow_fallback = runOptions->getValueOrDef<bool>(false, "allow_fallback_to_unimproved_masses");

      // Higgs masses
      // FIXME switch to this once the setters take pdg pairs
      //const std::pair<int,int> higgses[4] = {std::pair<int,int>(25,0),
      //                                 std::pair<int,int>(35,0),
      //                                 std::pair<int,int>(36,0),
      //                                 std::pair<int,int>(37,0)};
      str higgses[1];
      std::vector< triplet<double> > MH = {*Dep::prec_mh};
      int smlike_pdg = SMlike_higgs_PDG_code(HE);
      if (smlike_pdg == 25) higgses[0] = "h0_1";
      else if (smlike_pdg == 35) higgses[0] = "h0_2";
      else PrecisionBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      static int central = runOptions->getValueOrDef<int>(1, "Higgs_predictions_source");
      static int error = runOptions->getValueOrDef<int>(2, "Higgs_predictions_error_method");
      update_H_masses(HE, 1, higgses, central, error, MH, allow_fallback);

      // Save the identity/identities of the calculator(s) used for the central value.
      const str& p_calc = Dep::prec_mh.name();
      const str& p_orig = Dep::prec_mh.origin();
      const str& s_calc = Dep::unimproved_MSSM_spectrum.name();
      const str& s_orig = Dep::unimproved_MSSM_spectrum.origin();
      if (central == 1) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p_orig+"::"+p_calc, true);
      if (central == 2) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+s_orig+"::"+s_calc, true);
      if (central == 3) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p_orig+"::"+p_calc+", "+s_orig+"::"+s_calc, true);

      // Check if an SLHA file needs to be excreted.
      improved_spec.drop_SLHAs_if_requested(runOptions, "GAMBIT_spectrum");

    }

    /// Precision MSSM spectrum manufacturer with precision W and SM-like Higgs masses
    void make_MSSM_precision_spectrum_H_W(Spectrum& improved_spec /*(result)*/)
    {
      using namespace Pipes::make_MSSM_precision_spectrum_H_W;
      improved_spec = *Dep::unimproved_MSSM_spectrum; // Does copy
      SubSpectrum& HE = improved_spec.get_HE();
      SubSpectrum& LE = improved_spec.get_LE();
      static bool allow_fallback = runOptions->getValueOrDef<bool>(false, "allow_fallback_to_unimproved_masses");

      // W mass
      update_W_masses(HE, LE, *Dep::prec_mw, allow_fallback);

      // Higgs masses
      // FIXME switch to this once the setters take pdg pairs
      //const std::pair<int,int> higgses[4] = {std::pair<int,int>(25,0),
      //                                 std::pair<int,int>(35,0),
      //                                 std::pair<int,int>(36,0),
      //                                 std::pair<int,int>(37,0)};
      str higgses[1];
      std::vector< triplet<double> > MH = {*Dep::prec_mh};
      int smlike_pdg = SMlike_higgs_PDG_code(HE);
      if (smlike_pdg == 25) higgses[0] = "h0_1";
      else if (smlike_pdg == 35) higgses[0] = "h0_2";
      else PrecisionBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      static int central = runOptions->getValueOrDef<int>(1, "Higgs_predictions_source");
      static int error = runOptions->getValueOrDef<int>(2, "Higgs_predictions_error_method");
      update_H_masses(HE, 1, higgses, central, error, MH, allow_fallback);

      // Save the identity/identities of the calculator(s) used for the central value.
      const str& p_calc = Dep::prec_mh.name();
      const str& p_orig = Dep::prec_mh.origin();
      const str& s_calc = Dep::unimproved_MSSM_spectrum.name();
      const str& s_orig = Dep::unimproved_MSSM_spectrum.origin();
      if (central == 1) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p_orig+"::"+p_calc, true);
      if (central == 2) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+s_orig+"::"+s_calc, true);
      if (central == 3) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p_orig+"::"+p_calc+", "+s_orig+"::"+s_calc, true);

      // Check if an SLHA file needs to be excreted.
      improved_spec.drop_SLHAs_if_requested(runOptions, "GAMBIT_spectrum");

    }

    /// Precision MSSM spectrum manufacturer with precision W and 2HDM (4x) Higgs masses
    void make_MSSM_precision_spectrum_4H_W(Spectrum& improved_spec /*(result)*/)
    {
      using namespace Pipes::make_MSSM_precision_spectrum_4H_W;
      improved_spec = *Dep::unimproved_MSSM_spectrum; // Does copy
      SubSpectrum& HE = improved_spec.get_HE();
      SubSpectrum& LE = improved_spec.get_LE();
      static bool allow_fallback = runOptions->getValueOrDef<bool>(false, "allow_fallback_to_unimproved_masses");

      // W mass
      update_W_masses(HE, LE, *Dep::prec_mw, allow_fallback);

      // Higgs masses
      // FIXME switch to this once the setters take pdg pairs
      //const std::pair<int,int> higgses[4] = {std::pair<int,int>(25,0),
      //                                 std::pair<int,int>(35,0),
      //                                 std::pair<int,int>(36,0),
      //                                 std::pair<int,int>(37,0)};
      const str higgses[4] = {"h0_1", "h0_2", "A0", "H+"};
      std::vector< triplet<double> > MH;
      int smlike_pdg = SMlike_higgs_PDG_code(HE);
      if (smlike_pdg == 25)
      { //h0_1
        MH.push_back(*Dep::prec_mh);
        MH.push_back(Dep::prec_HeavyHiggsMasses->at(35));
      }
      else if (smlike_pdg == 35)
      { //h0_2
        MH.push_back(Dep::prec_HeavyHiggsMasses->at(25));
        MH.push_back(*Dep::prec_mh);
      }
      else PrecisionBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      MH.push_back(Dep::prec_HeavyHiggsMasses->at(36)); //A_0
      MH.push_back(Dep::prec_HeavyHiggsMasses->at(37)); //H+

      static int central = runOptions->getValueOrDef<int>(1, "Higgs_predictions_source");
      static int error = runOptions->getValueOrDef<int>(2, "Higgs_predictions_error_method");
      update_H_masses(HE, 4, higgses, central, error, MH, allow_fallback);

      // Save the identity/identities of the calculator(s) used for the central value.
      const str& p1_calc = Dep::prec_mh.name();
      const str& p1_orig = Dep::prec_mh.origin();
      const str& p2_calc = Dep::prec_HeavyHiggsMasses.name();
      const str& p2_orig = Dep::prec_HeavyHiggsMasses.origin();
      const str& s_calc = Dep::unimproved_MSSM_spectrum.name();
      const str& s_orig = Dep::unimproved_MSSM_spectrum.origin();
      if (central == 1) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p1_orig+"::"+p1_calc+", "+p2_orig+"::"+p2_calc, true);
      if (central == 2) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+s_orig+"::"+s_calc, true);
      if (central == 3) HE.set_override(Par::dimensionless, 1.0, "h mass from: "+p1_orig+"::"+p1_calc+", "+p2_orig+"::"+p2_calc+", "+s_orig+"::"+s_calc, true);

      // Check if an SLHA file needs to be excreted.
      improved_spec.drop_SLHAs_if_requested(runOptions, "GAMBIT_spectrum");

    }


    /// Basic mass extractors for different types of spectra, for use with precision likelihoods and other things not needing a whole spectrum object.
    /// @{
    void mw_from_SM_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_SM_spectrum;
      const SubSpectrum& LE = Dep::SM_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");;
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mw_from_ScalarSingletDM_Z2_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_ScalarSingletDM_Z2_spectrum;
      const SubSpectrum& LE = Dep::ScalarSingletDM_Z2_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");;
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mw_from_ScalarSingletDM_Z3_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_ScalarSingletDM_Z3_spectrum;
      const SubSpectrum& LE = Dep::ScalarSingletDM_Z3_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");;
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mw_from_VectorSingletDM_Z2_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_VectorSingletDM_Z2_spectrum;
      const SubSpectrum& LE = Dep::VectorSingletDM_Z2_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mw_from_MajoranaSingletDM_Z2_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_MajoranaSingletDM_Z2_spectrum;
      const SubSpectrum& LE = Dep::MajoranaSingletDM_Z2_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
      void mw_from_DiracSingletDM_Z2_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_DiracSingletDM_Z2_spectrum;
      const SubSpectrum& LE = Dep::DiracSingletDM_Z2_spectrum->get_LE();
      result.central = LE.get(Par::Pole_Mass, "W+");
      result.upper = result.central * LE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * LE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mw_from_MSSM_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mw_from_MSSM_spectrum;
      const SubSpectrum& HE = Dep::MSSM_spectrum->get_HE();
      result.central = HE.get(Par::Pole_Mass, "W+");
      result.upper = result.central * HE.get(Par::Pole_Mass_1srd_high, "W+");
      result.lower = result.central * HE.get(Par::Pole_Mass_1srd_low, "W+");
    }
    void mh_from_SM_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mh_from_SM_spectrum;
      const SubSpectrum& HE = Dep::SM_spectrum->get_HE();
      result.central = HE.get(Par::Pole_Mass, 25, 0);
      result.upper = result.central * HE.get(Par::Pole_Mass_1srd_high, 25, 0);
      result.lower = result.central * HE.get(Par::Pole_Mass_1srd_low, 25, 0);
    }
    void mh_from_ScalarSingletDM_Z2_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mh_from_ScalarSingletDM_Z2_spectrum;
      const SubSpectrum& HE = Dep::ScalarSingletDM_Z2_spectrum->get_HE();
      result.central = HE.get(Par::Pole_Mass, 25, 0);
      result.upper = result.central * HE.get(Par::Pole_Mass_1srd_high, 25, 0);
      result.lower = result.central * HE.get(Par::Pole_Mass_1srd_low, 25, 0);
    }
    void mh_from_ScalarSingletDM_Z3_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mh_from_ScalarSingletDM_Z3_spectrum;
      const SubSpectrum& HE = Dep::ScalarSingletDM_Z3_spectrum->get_HE();
      result.central = HE.get(Par::Pole_Mass, 25, 0);
      result.upper = result.central * HE.get(Par::Pole_Mass_1srd_high, 25, 0);
      result.lower = result.central * HE.get(Par::Pole_Mass_1srd_low, 25, 0);
    }
    void mh_from_MSSM_spectrum(triplet<double> &result)
    {
      using namespace Pipes::mh_from_MSSM_spectrum;
      const SubSpectrum& HE = Dep::MSSM_spectrum->get_HE();
      int smlike_pdg = SMlike_higgs_PDG_code(HE);
      result.central = HE.get(Par::Pole_Mass, smlike_pdg, 0);
      result.upper = result.central * HE.get(Par::Pole_Mass_1srd_high, smlike_pdg, 0);
      result.lower = result.central * HE.get(Par::Pole_Mass_1srd_low, smlike_pdg, 0);
    }
    /// @}

    /// Z boson mass likelihood
    /// M_Z (Breit-Wigner mass parameter ~ pole) = 91.1876 +/- 0.0021 GeV (1 sigma), Gaussian.
    /// Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_Z_mass_chi2(double &result)
    {
      using namespace Pipes::lnL_Z_mass_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->mZ, 91.1876, 0.0, 0.0021, profile);
    }

    /// t quark mass likelihood
    /// m_t (pole) = 173.34 +/- 0.76 GeV (1 sigma), Gaussian.
    /// Reference: http://arxiv.org/abs/1403.4427
    void lnL_t_mass_chi2(double &result)
    {
      using namespace Pipes::lnL_t_mass_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->mT, 173.34, 0.0, 0.76, profile);
    }

    /// b quark mass likelihood
    /// m_b (mb)^MSbar = 4.18 +/- 0.03 GeV (1 sigma), Gaussian.
    /// Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_mbmb_chi2(double &result)
    {
      using namespace Pipes::lnL_mbmb_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->mBmB, 4.18, 0.0, 0.03, profile);
    }

    /// c quark mass likelihood
    /// m_c (mc)^MSbar = 1.28 +/- 0.03 GeV (1 sigma), Gaussian.
    ///  Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_mcmc_chi2(double &result)
    {
      using namespace Pipes::lnL_mcmc_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->mCmC, 1.28, 0.0, 0.03, profile);
    }

    /// \brief Likelihoods for light quark mass ratios. At the moment, all are just gaussians.
    /// Default data from PDG http://PDG.LBL.GOV 26/06/2017.
    /// Likelihoods apply to MSbar masses at the scale mu = 2 GeV.
    /// m_u/m_d = 0.38-0.58
    /// m_s / ((m_u + m_d)/2) = 27.3 +/- 0.7
    /// m_s = (96 +/- 4) MeV
    void lnL_light_quark_masses_chi2 (double &result)
    {
        using namespace Pipes::lnL_light_quark_masses_chi2;
        const SMInputs& SM = *Dep::SMINPUTS;

        double mud_obs = runOptions->getValueOrDef<double>(0.48, "mud_obs");
        double mud_obserror = runOptions->getValueOrDef<double>(0.10, "mud_obserr");
        double msud_obs = runOptions->getValueOrDef<double>(27.3, "msud_obs");
        double msud_obserror = runOptions->getValueOrDef<double>(0.7, "msud_obserr");
        double ms_obs = runOptions->getValueOrDef<double>(96.E-03, "ms_obs");
        double ms_obserror = runOptions->getValueOrDef<double>(4.E-03, "ms_obserr");

        /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
        bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

        result = Stats::gaussian_loglikelihood(SM.mU/SM.mD, mud_obs, 0., mud_obserror, profile)
            + Stats::gaussian_loglikelihood((2*SM.mS)/(SM.mU + SM.mD), msud_obs, 0., msud_obserror, profile)
            + Stats::gaussian_loglikelihood(SM.mS, ms_obs, 0., ms_obserror, profile);
        logger() << LogTags::debug << "Combined lnL for light quark mass ratios and s-quark mass is " << result << EOM;
    }

    /// alpha^{-1}(mZ)^MSbar likelihood
    /// alpha^{-1}(mZ)^MSbar = 127.950 +/- 0.017 (1 sigma), Gaussian.  (PDG global SM fit)
    /// Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-standard-model.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_alpha_em_chi2(double &result)
    {
      using namespace Pipes::lnL_alpha_em_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->alphainv, 127.950, 0.0, 0.017, profile);
    }

    /// alpha_s(mZ)^MSbar likelihood
    /// alpha_s(mZ)^MSbar = 0.1181 +/- 0.0011 (1 sigma), Gaussian.
    /// Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_alpha_s_chi2(double &result)
    {
      using namespace Pipes::lnL_alpha_s_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->alphaS, 0.1181, 0.0, 0.0011, profile);
    }

    /// G_Fermi likelihood
    /// G_Fermi = (1.1663787 +/- 0.0000006) * 10^-5 GeV^-2 (1 sigma), Gaussian.
    ///  Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_GF_chi2(double &result)
    {
      using namespace Pipes::lnL_GF_chi2;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::SMINPUTS->GF, 1.1663787E-05, 0.0, 0.0000006E-05, profile);
    }

    /// W boson mass likelihood
    void lnL_W_mass_chi2(double &result)
    {
      using namespace Pipes::lnL_W_mass_chi2;
      double theory_uncert = std::max(Dep::mw->upper, Dep::mw->lower);
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::mw->central, mw_central_observed, theory_uncert, mw_err_observed, profile);
    }

    /// Simple, naive h boson mass likelihood
    /// Reference: D. Aad et al arxiv:1503.07589, Phys.Rev.Lett. 114 (2015) 191803 (ATLAS + CMS combination)
    /// Also used dierctly in http://pdg.lbl.gov/2016/tables/rpp2016-sum-gauge-higgs-bosons.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_h_mass_chi2(double &result)
    {
      using namespace Pipes::lnL_h_mass_chi2;
      double theory_uncert = std::max(Dep::mh->upper, Dep::mh->lower);
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::mh->central, 125.09, theory_uncert, 0.24, profile);
    }

    /// Effective leptonic sin^2(theta_W) likelihood
    /// sin^2theta_W^leptonic_effective~ sin^2theta_W(mZ)^MSbar + 0.00029 = 0.23155 +/- 0.00005    (1 sigma), Gaussian.  (PDG global SM fit)
   ///  Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_sinW2_eff_chi2(double &result)
    {
      using namespace Pipes::lnL_sinW2_eff_chi2;
      double theory_uncert = std::max(Dep::prec_sinW2_eff->upper, Dep::prec_sinW2_eff->lower);
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::prec_sinW2_eff->central, 0.23155, theory_uncert, 0.00005, profile);
    }

    /// Delta rho likelihood
    /// Delta rho = 0.00037 +/- 0.00023 (1 sigma), Gaussian.  (PDG global SM fit)
    ///  Reference: http://pdg.lbl.gov/2016/reviews/rpp2016-rev-qcd.pdf = C. Patrignani et al. (Particle Data Group), Chin. Phys. C, 40, 100001 (2016).
    void lnL_deltarho_chi2(double &result)
    {
      using namespace Pipes::lnL_deltarho_chi2;
      double theory_uncert = std::max(Dep::deltarho->upper, Dep::deltarho->lower);
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(Dep::deltarho->central, 0.00037, theory_uncert, 0.00023, profile);
    }


    /// g-2 in SM from e+e- data
    void gm2_SM_ee(triplet<double> &result)
    {
      /// Values taken from prediction in arXiv:1010.4180 (Eq 22)
      result.central = 2.0 * 11659180.2e-10;
      result.upper = 2.0 * 4.9e-10;
      result.lower = result.upper;
    }

    /// g-2 in SM from tau+tau- data
    void gm2_SM_tautau(triplet<double> &result)
    {
      /// Values taken from prediction in arXiv:1010.4180, based on tau data
      result.central = 2.0 * 11659189.4e-10;
      result.upper = 2.0 * 5.4e-10;
      result.lower = result.upper;
    }

    /// g-2 likelihood
    void lnL_gm2_chi2(double &result)
    {
      using namespace Pipes::lnL_gm2_chi2;
      double amu_sm  = 0.5*Dep::muon_gm2_SM->central;
      double amu_sm_error = 0.5*std::max(Dep::muon_gm2_SM->upper, Dep::muon_gm2_SM->lower);
      double amu_bsm = 0.5*Dep::muon_gm2->central;
      double amu_bsm_error = 0.5*std::max(Dep::muon_gm2->upper, Dep::muon_gm2->lower);
      double amu_theory = amu_sm + amu_bsm;
      double amu_theory_err = sqrt(Gambit::Utils::sqr(amu_sm_error) + Gambit::Utils::sqr(amu_bsm_error));
      // From hep-ex/0602035, as updated in PDG 2016 (C. Patrignani et al, Chin. Phys. C, 40, 100001 (2016). ). Error combines statistical (5.4) and systematic (3.3) uncertainties in quadrature.
      double amu_exp = 11659209.1e-10;
      double amu_exp_error = 6.3e-10;
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      result = Stats::gaussian_loglikelihood(amu_theory, amu_exp, amu_theory_err, amu_exp_error, profile);
    }

    /// Calculate a_mu_SUSY using the gm2calc backend.
    void GM2C_SUSY(triplet<double> &result)
    {
      using namespace Pipes::GM2C_SUSY;
      const SubSpectrum& mssm = Dep::MSSM_spectrum->get_HE();

      gm2calc::MSSMNoFV_onshell model;

      try
      {
        /// fill pole masses.
        /// note: that the indices start from 0 in gm2calc,
        /// gambit indices start from 1, hence the offsets here
        model.get_physical().MSvmL = mssm.get(Par::Pole_Mass, "~nu", 2); // 1L
        str msm1, msm2;
        // PA: todo: I think we shouldn't be too sensitive to mixing in this case.
        // If we get a successful convergence to the pole mass scheme in the end it's OK
        const static double tol = runOptions->getValueOrDef<double>(1e-1, "family_mixing_tolerance");
        const static bool pt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
        slhahelp::family_state_mix_matrix("~e-", 2, msm1, msm2, mssm, tol, LOCAL_INFO, pt_error);
        model.get_physical().MSm(0)  =  mssm.get(Par::Pole_Mass, msm1); // 1L
        model.get_physical().MSm(1)  =  mssm.get(Par::Pole_Mass, msm2); // 1L

        model.get_physical().MChi(0) = mssm.get(Par::Pole_Mass, "~chi0", 1); // 1L
        model.get_physical().MChi(1) =  mssm.get(Par::Pole_Mass, "~chi0", 2); // 1L
        model.get_physical().MChi(2) = mssm.get(Par::Pole_Mass, "~chi0", 3); // 1L
        model.get_physical().MChi(3) = mssm.get(Par::Pole_Mass, "~chi0", 4); // 1L

        model.get_physical().MCha(0) =  mssm.get(Par::Pole_Mass, "~chi+", 1); // 1L
        model.get_physical().MCha(1) =  mssm.get(Par::Pole_Mass, "~chi+", 2); // 1L
        model.get_physical().MAh(1)  = mssm.get(Par::Pole_Mass, "A0"); // 2L

        model.set_TB(mssm.get(Par::dimensionless,"tanbeta"));
        model.set_Mu(mssm.get(Par::mass1, "Mu"));
        model.set_MassB(mssm.get(Par::mass1, "M1"));
        model.set_MassWB(mssm.get(Par::mass1, "M2"));
        model.set_MassG(mssm.get(Par::mass1, "M3"));
        for(int i = 1; i<=3; i++)
        {
          for(int j = 1; j<=3; j++)
          {
            model.set_mq2(i-1,j-1, mssm.get(Par::mass2, "mq2", i, j));
            model.set_ml2(i-1,j-1, mssm.get(Par::mass2, "ml2", i, j));
            model.set_md2(i-1,j-1, mssm.get(Par::mass2, "md2", i, j));
            model.set_mu2(i-1,j-1, mssm.get(Par::mass2, "mu2", i, j));
            model.set_me2(i-1,j-1, mssm.get(Par::mass2, "me2", i, j));
            double Au = 0.0, Ad = 0.0, Ae = 0.0;
            if(mssm.get(Par::dimensionless, "Yu", i, j) > 1e-14){
              Au = mssm.get(Par::mass1, "TYu", i, j)
              / mssm.get(Par::dimensionless, "Yu", i, j);
            }
            if(mssm.get(Par::dimensionless, "Ye", i, j) > 1e-14){
              Ae = mssm.get(Par::mass1, "TYe", i, j)
              / mssm.get(Par::dimensionless, "Ye", i, j);
            }
            if(mssm.get(Par::dimensionless, "Yd", i, j) > 1e-14){
              Ad = mssm.get(Par::mass1, "TYd", i, j)
              / mssm.get(Par::dimensionless, "Yd", i, j);
            }

            model.set_Au(i-1, j-1, Au);
            model.set_Ad(i-1, j-1, Ad);
            model.set_Ae(i-1, j-1, Ae);
          }
        }

        const SMInputs& smin = Dep::MSSM_spectrum->get_SMInputs();

        model.get_physical().MVZ =smin.mZ;
        model.get_physical().MFb =smin.mBmB;
        model.get_physical().MFt =smin.mT;
        model.get_physical().MFtau =smin.mTau;
        model.get_physical().MVWm =mssm.get(Par::Pole_Mass, "W+");  //GAMBIT can get the pole mas but it may have been improved by FeynHiggs calcualtion
        model.get_physical().MFm =smin.mMu;
        //use SM alphaS(MZ) instead of MSSM g3(MSUSY) -- appears at two-loop so difference should be three-loop
        // (it is used for correctuions to yb and DRbar --> MS bar conversion)
        model.set_g3(std::sqrt(4*M_PI*smin.alphaS));
        // these are not currently used but may be in future updates so set them anyway
        model.get_physical().MFe =smin.mE;
        model.get_physical().MFd =smin.mD; //MSbar
        model.get_physical().MFs =smin.mS; //MSbar
        model.get_physical().MFu =smin.mU; //MSbar
        model.get_physical().MFc =smin.mCmC; // MSbar

        /// alpha_MZ := alpha(0) (1 - \Delta^{OS}(M_Z) ) where
        /// \Delta^{OS}(M_Z) = quark and lepton contributions to
        // on-shell renormalized photon vacuum polarization
        // default value recommended by GM2calc from arxiv:1105.3149
        const double alpha_MZ = runOptions->getValueOrDef
        <double>(alpha_e_OS_MZ, "GM2Calc_extra_alpha_e_MZ");
        const double alpha_thomson = runOptions->getValueOrDef
        <double>(alpha_e_OS_thomson_limit, "GM2Calc_extra_alpha_e_thomson_limit");

        if (alpha_MZ > std::numeric_limits<double>::epsilon())
          model.set_alpha_MZ(alpha_MZ);

        if (alpha_thomson > std::numeric_limits<double>::epsilon())
          model.set_alpha_thompson(alpha_thomson);

        model.set_scale(mssm.GetScale());                   // 2L

        /// convert DR-bar parameters to on-shell
        model.convert_to_onshell();

        /// need to hook up errors properly
        /// check for problems
        if( model.get_problems().have_problem() == true) {
          std::ostringstream err;
          err << "gm2calc routine convert_to_onshell raised error: "
              << model.get_problems().get_problems() << ".";
          invalid_point().raise(err.str());
        }
        /// check for warnings
        if( model.get_problems().have_warning() == true) {
          std::ostringstream err;
          err << "gm2calc routine convert_to_onshell raised warning: "
              << model.get_problems().get_warnings() << ".";
          // Maybe you would argue that we want to invalidate such points, but the DRbar-->OS
          // conversion seems to fail to converge extremely often for general weak-scale SUSY models.
          PrecisionBit_warning().raise(LOCAL_INFO, err.str());
        }

      }
      catch (const gm2calc_1_2_0::gm2calc::Abstract_Error& e)
      {
        std::ostringstream err;
        err << "gm2calc 1.2.0 routine convert_to_onshell raised error: "
        << e.what() << ".";
        invalid_point().raise(err.str());
      }
      catch (const gm2calc_1_3_0::gm2calc::Abstract_Error& e)
      {
        std::ostringstream err;
        err << "gm2calc 1.3.0 routine convert_to_onshell raised error: "
        << e.what() << ".";
        invalid_point().raise(err.str());
      }

      const double error = BEreq::calculate_uncertainty_amu_2loop(model);

      const double amumssm = BEreq::calculate_amu_1loop(model)
         + BEreq::calculate_amu_2loop(model);

      // Convert from a_mu to g-2
      result.central = 2.0*amumssm;
      result.upper = 2.0*error;
      result.lower = 2.0*error;

      return;
    }


    /// Calculation of g-2 with SuperIso
    void SI_muon_gm2(triplet<double> &result)
    {
      using namespace Pipes::SI_muon_gm2;

      #ifdef PRECISIONBIT_DEBUG
        cout<<"Starting SI_muon_gm2"<<endl;
      #endif

      struct parameters param = *Dep::SuperIso_modelinfo;

      if (param.model < 0)
      {
        result.central = 0.0;
        result.upper   = 0.0;
        result.upper   = 0.0;
      }
      else
      {
        result.central = BEreq::muon_gm2(&param);
        result.upper = std::max(std::abs(result.central)*0.3, 6e-10); //Based on hep-ph/0609168v1 eqs 84 & 85
        result.lower = result.upper;
      }

      #ifdef PRECISIONBIT_DEBUG
        printf("(g-2)_mu=%.3e\n",result.central);
        cout<<"Finished SI_muon_gm2"<<endl;
      #endif
    }


    /// Precision observables from SUSY-POPE
    /// This function is unfinished because SUSY-POPE is buggy.
    void SP_PrecisionObs(double &result)
    {
      using namespace Pipes::SP_PrecisionObs;
      int error = 0;
      Farray<Fdouble,1,35> SM_Obs;
      Farray<Fdouble,1,35> MSSM_Obs;

      BEreq::CalcObs_SUSYPOPE(error, SM_Obs, MSSM_Obs);
      if(error != 0)
      {
        std::cout << "something went wrong" << std::endl;
      }
      else
      {
        std::cout << " MW in SM = " << SM_Obs(1) << std::endl;
        std::cout << " MW in MSSM = " << MSSM_Obs(1) << std::endl;
      }
      result = 0.1;
      return;

    }

    // THDM requirements
    // {
   // functions to create and distribute THDM container
   // the THDM container combines the Spectrum and THDMC objects to optimise code efficiency

    void set_SM(const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_7_0::THDM* THDM_object){
      THDMC_1_7_0::SM* SM_object = THDM_object->get_SM_pointer();
      SM_object->set_alpha(1/(sminputs.alphainv));
      SM_object->set_alpha_s(sminputs.alphaS);
      SM_object->set_GF(sminputs.GF);
      SM_object->set_MZ(SM->get(Par::Pole_Mass,"Z0"));
      SM_object->set_MW(SM->get(Par::Pole_Mass,"W+"));
      SM_object->set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
      SM_object->set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
      SM_object->set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));
      SM_object->set_qmass_msbar(1,SM->get(Par::mass1,"d_1")); //d
      SM_object->set_qmass_msbar(2,SM->get(Par::mass1,"u_1")); //u
      SM_object->set_qmass_msbar(3,SM->get(Par::mass1,"d_2")); //s
      SM_object->set_qmass_msbar(4,sminputs.mCmC); //c
      SM_object->set_qmass_msbar(5,SM->get(Par::mass1,"d_3")); //u
      SM_object->set_qmass_msbar(6,SM->get(Par::mass1,"u_3")); //s
    }

    void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, const int yukawa_type, THDMC_1_7_0::THDM* THDM_object) {
      //Takes in the spectrum and fills a THDM object which is defined
      //in 2HDMC. Any 2HDMC functions can then be called on this object.
      double lambda_1 = he->get(Par::mass1,"lambda_1");
      double lambda_2 = he->get(Par::mass1,"lambda_2");
      double lambda_3 = he->get(Par::mass1, "lambda_3");
      double lambda_4 = he->get(Par::mass1, "lambda_4");
      double lambda_5 = he->get(Par::mass1, "lambda_5");
      double tan_beta = he->get(Par::dimensionless, "tanb");
      double lambda_6 = he->get(Par::mass1, "lambda_6");
      double lambda_7 = he->get(Par::mass1, "lambda_7");
      double m12_2 = he->get(Par::mass1,"m12_2");
      double mh = he->get(Par::Pole_Mass, "h0", 1);
      double mH = he->get(Par::Pole_Mass, "h0", 2);
      double mA = he->get(Par::Pole_Mass, "A0");
      double mC = he->get(Par::Pole_Mass, "H+");
      double alpha = he->get(Par::dimensionless, "alpha");
      double sba = sin(atan(tan_beta) - alpha);
      set_SM(SM,sminputs,THDM_object);
      THDM_object->set_param_full(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, \
                                  m12_2, tan_beta, mh, mH, mA, mC, sba);
      THDM_object->set_yukawas_type(yukawa_type);
    }

    struct thdm_params { double lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7, tanb, alpha, m11_2, m22_2, m12_2, mh, mH, mC, mA, mh_run, mH_run, mC_run, mA_run, Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7, M11_2, M22_2, M12_2, yukawa_type; };
    void init_THDM_pars(const std::unique_ptr<SubSpectrum>& he, const int yukawa_type, thdm_params& thdm_pars) {
        thdm_pars.lambda1 = he->get(Par::mass1,"lambda_1");
        thdm_pars.lambda2 = he->get(Par::mass1,"lambda_2");
        thdm_pars.lambda3 = he->get(Par::mass1, "lambda_3");
        thdm_pars.lambda4 = he->get(Par::mass1, "lambda_4");
        thdm_pars.lambda5 = he->get(Par::mass1, "lambda_5");
        thdm_pars.lambda6 = he->get(Par::mass1, "lambda_6");
        thdm_pars.lambda7 = he->get(Par::mass1, "lambda_7");
        thdm_pars.tanb = he->get(Par::dimensionless, "tanb");
        thdm_pars.alpha = he->get(Par::dimensionless,"alpha");
        thdm_pars.m11_2 = he->get(Par::mass1,"m11_2");
        thdm_pars.m22_2 = he->get(Par::mass1,"m22_2");
        thdm_pars.m12_2 = he->get(Par::mass1,"m12_2");
        thdm_pars.mh = he->get(Par::Pole_Mass, "h0", 1);
        thdm_pars.mH = he->get(Par::Pole_Mass, "h0", 2);
        thdm_pars.mC = he->get(Par::Pole_Mass, "H+");
        thdm_pars.mA = he->get(Par::Pole_Mass, "A0");
        thdm_pars.mh_run = he->get(Par::mass1, "h0", 1);
        thdm_pars.mH_run = he->get(Par::mass1, "h0", 2);
        thdm_pars.mC_run = he->get(Par::mass1, "H+");
        thdm_pars.mA_run = he->get(Par::mass1, "A0");
        thdm_pars.Lambda1 = he->get(Par::mass1,"Lambda_1");
        thdm_pars.Lambda2 = he->get(Par::mass1,"Lambda_2");
        thdm_pars.Lambda3 = he->get(Par::mass1,"Lambda_3");
        thdm_pars.Lambda4 = he->get(Par::mass1,"Lambda_4");
        thdm_pars.Lambda5 = he->get(Par::mass1,"Lambda_5");
        thdm_pars.Lambda6 = he->get(Par::mass1,"Lambda_6");
        thdm_pars.Lambda7 = he->get(Par::mass1,"Lambda_7");
        thdm_pars.M11_2 = he->get(Par::mass1,"M11_2");
        thdm_pars.M22_2 = he->get(Par::mass1,"M22_2");
        thdm_pars.M12_2 = he->get(Par::mass1,"M12_2");
        thdm_pars.yukawa_type = he->get(Par::dimensionless,"yukawaCoupling");
    }

    void init_THDM_object_SM_like(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, const int yukawa_type, THDMC_1_7_0::THDM* THDM_object, const int higgs_number) {
      double mh = he->get(Par::Pole_Mass,"h0",1);
      if (higgs_number > 0 && higgs_number < 3) mh = he->get(Par::Pole_Mass,"h0", higgs_number);
      if (higgs_number == 3) mh = he->get(Par::Pole_Mass,"A0");
      set_SM(SM,sminputs,THDM_object);
      // tree level conversion will be used for any basis changes
      THDM_object->set_param_phys(mh, mh*100.0, mh*100.0, mh*100.0, 1.0, 0.0, 0.0, 0.0, 1.0);
      THDM_object->set_yukawas_type(yukawa_type);
    }

    struct THDM_spectrum_container {
      std::unique_ptr<SubSpectrum> he;
      std::unique_ptr<SubSpectrum> SM;
      SMInputs sminputs;
      THDMC_1_7_0::THDM* THDM_object;
      thdm_params thdm_pars;
      int yukawa_type;
    };

    void init_THDM_spectrum_container(THDM_spectrum_container& container, const Spectrum& spec, const int yukawa_type, const double scale=0.0) {
      container.he = spec.clone_HE(); // Copy "high-energy" SubSpectrum
      if(scale>0.0) container.he->RunToScale(scale);
      container.SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
      container.sminputs = spec.get_SMInputs();   
      container.yukawa_type = yukawa_type;
      container.THDM_object = new THDMC_1_7_0::THDM();
      init_THDM_pars(container.he, container.yukawa_type, container.thdm_pars);
      init_THDM_object(container.he, container.SM, container.sminputs, container.yukawa_type, container.THDM_object);
    }

    enum yukawa_type {type_I = 1, type_II, lepton_specific, flipped, type_III};
    enum particle_type {h0=1, H0, A0, G0, Hp, Hm, Gp, Gm};

    const std::vector<std::string> THDM_model_keys = {"THDMatQ", "THDM", "THDMIatQ", "THDMI", "THDMIIatQ", "THDMII", "THDMLSatQ", "THDMLS", "THDMflippedatQ", "THDMflipped"};
    const std::vector<bool> THDM_model_at_Q = {true, false, true, false, true, false, true, false, true, false};
    const std::vector<yukawa_type> THDM_model_y_type = {type_III, type_III, type_I, type_I, type_II, type_II, lepton_specific, lepton_specific, flipped, flipped};

    double oblique_parameters_likelihood_THDM(THDM_spectrum_container& container);

    void get_oblique_parameters_likelihood_THDM(double& result) {
      using namespace Pipes::get_oblique_parameters_likelihood_THDM;
      // set THDM model type
      int y_type = -1; bool is_at_Q = false; double scale = 0.0;
      for (int i=0; unsigned(i) < THDM_model_keys.size(); i++) {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model_keys[i])) {is_at_Q = THDM_model_at_Q[i]; y_type = THDM_model_y_type[i]; break;}
      }
      THDM_spectrum_container container;
      init_THDM_spectrum_container(container, *Dep::THDM_spectrum, y_type);
      result = oblique_parameters_likelihood_THDM(container);
      delete container.THDM_object; // must be deleted upon the of container usage or memory will overflow
    }

    std::vector<double> get_lambdas_from_spectrum(THDM_spectrum_container& container) {
      std::vector<double> Lambda(8);
      Lambda[1] = container.he->get(Par::mass1, "lambda_1");
      Lambda[2] = container.he->get(Par::mass1, "lambda_2");
      Lambda[3] = container.he->get(Par::mass1, "lambda_3");
      Lambda[4] = container.he->get(Par::mass1, "lambda_4");
      Lambda[5] = container.he->get(Par::mass1, "lambda_5");
      Lambda[6] = container.he->get(Par::mass1, "lambda_6");
      Lambda[7] = container.he->get(Par::mass1, "lambda_7");
      return Lambda;
    }

    double oblique_parameters_likelihood_THDM(THDM_spectrum_container& container) { 
      THDMC_1_7_0::Constraints constraints_object(*(container.THDM_object));

      const double mh_ref = 125.0; //container.he->get(Par::Pole_Mass,"h0",1);
      double S, T, U, V, W, X;
      constraints_object.oblique_param(mh_ref, S, T, U, V, W, X);

      // nan debug currently reuqired
      const bool nan_debug = true;
      std::vector<double> nan_debug_vals;

      // add oblique params to nan debug output
      if (nan_debug) {
        nan_debug_vals.push_back(S);
        nan_debug_vals.push_back(T);
        nan_debug_vals.push_back(U);
        nan_debug_vals.push_back(V);
        nan_debug_vals.push_back(W);
        nan_debug_vals.push_back(X);
      }
    
      // if new physics in the low energy scale 
      // move to basis as introduced in arxiv:9407203
      const bool use_low_energy = true;
      if (use_low_energy) {
        const double sinW2 = container.he->get(Par::dimensionless, "sinW2");
        const double cosW2 = 1. - sinW2;
        S = S + 4.*sinW2*cosW2*V + 4.*(cosW2-sinW2)*X;
        T = T + V;
        U = U - 4.*sinW2*cosW2*V + 8.*sinW2*X;
      }

      //calculating a diff
      std::vector<double> value_exp = {S,T,U};
      std::vector<double> value_th = {0.014, 0.03, 0.06};
      std::vector<double> error;
      const int dim = value_exp.size();

      for (int i=0;i<dim;++i) {
        error.push_back(value_exp[i] - value_th[i]);
      }

      // calculating the covariance matrix
      boost::numeric::ublas::matrix<double> cov(dim,dim), cov_inv(dim, dim), corr(dim, dim);
      std::vector<double> sigma = {0.10, 0.11, 0.10};

      // fill with zeros
      for (int i=0; i< dim; i++) {
        for (int j=0; j<dim; j++) corr(i,j) = 0.0;
      }

      corr(0,0) = 1.0; corr(0,1) = 0.9; corr(0,2) = -0.59;
      corr(1,0) = 0.9; corr(1,1) = 1.0; corr(1,2) = -0.83; 
      corr(2,0) = -0.59; corr(2,1) = -0.83; corr(2,2) = 1.0;

      for (int i=0; i< dim; i++) {
        for (int j=0; j<dim; j++) cov(i,j) = sigma[i] * sigma[j] * corr(i,j);
      }

      // add cov to nan debug output
      if (nan_debug) {
        for (int i=0; i < dim; ++i) {
          for (int j=0; j< dim; ++j) nan_debug_vals.push_back(cov(i,j));
        }
      }

      // calculating the chi2
      double chi2=0;
      FlavBit::InvertMatrix(cov, cov_inv);
      for (int i=0; i < dim; ++i) {
        for (int j=0; j< dim; ++j) chi2 += error[i] * cov_inv(i,j)* error[j];
      }

      // add cov_inv to nan debug output
      if (nan_debug) {
        for (int i=0; i < dim; ++i) {
          for (int j=0; j< dim; ++j) nan_debug_vals.push_back(cov_inv(i,j));
        }
        // PURELY FOR DEBUG
        chi2 = NAN;
        // is chi2 NaN? If so continue print debug & invalidate point
        if (isnan(chi2)) {
          // save point
          std::ofstream debug_stream;
          debug_stream.open ("oblique_nan_debug.txt", std::ofstream::out | std::ofstream::app);
          debug_stream << "*****";
          for (int k=0; k< nan_debug_vals.size(); k++) debug_stream << nan_debug_vals[k] << std::endl;
          std::vector<double> Lambdas = get_lambdas_from_spectrum(container);
          for(int k=0; k< Lambdas.size(); k++) debug_stream << Lambdas[k] << std::endl;
          debug_stream << container.he->get(Par::mass1, "m12_2") << std::endl;
          debug_stream << container.he->get(Par::dimensionless, "sba") << std::endl;
          debug_stream << container.he->get(Par::dimensionless, "tanb") << std::endl;
          debug_stream << container.he->get(Par::dimensionless, "alpha") << std::endl;
          debug_stream << "*****" << std::endl;
          debug_stream.close();

          std::ostringstream err;
          err << "Oblique parameters likelihood THDM returned NaN. Problemetic output saved to debug_oblique.txt. Point invalidated.";
          invalid_point().raise(err.str());
        }
      }
        
      return -0.5*chi2;
    }
    // end of THDM container functions
    // }

  }
}
