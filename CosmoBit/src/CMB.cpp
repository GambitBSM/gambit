//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to the CMB.
///
///  Routines include extracting CMB spectra and 
///  computing effects of energy injections.
///
///  Does *not* contain the Planck likelihoods; 
///  these live in CosmoBit/src/Planck.cpp.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///  \date 2018 May
///  \date 2018 Aug - Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan - May
///  \date 2019 Jan, Feb, June, Nov
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 June
///  \date 2019 Mar,June
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2018 Mar
///  \date 2019 Jul
///  \date 2020 Apr
///
///  *********************************************

#include <gsl/gsl_spline.h>

#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"

#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    /**********/
    /* Classy */
    /**********/

    /// Getter functions for CL spectra from classy.

    /* UNLENSED SPECTRA */

    /// Temperature autocorrelation 
    void class_get_unlensed_Cl_TT(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_TT;
      result = BEreq::class_get_unlensed_cl("tt");

      // Loop through the TT spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the TT spectrum.");
        }
      }
    }

    /// Temperature & E-mode cross-correlation
    void class_get_unlensed_Cl_TE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_TE;
      result = BEreq::class_get_unlensed_cl("te");
    }

    /// E-mode autocorrelation 
    void class_get_unlensed_Cl_EE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_EE;
      result = BEreq::class_get_unlensed_cl("ee");

      // Loop through the EE spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the EE spectrum.");
        }
      }
    }

    /// B-mode autocorrelation 
    void class_get_unlensed_Cl_BB(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_BB;
      result = BEreq::class_get_unlensed_cl("bb");

      // Loop through the BB spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the BB spectrum.");
        }
      }
    }

    /// Lensing (Phi) autocorrelation
    void class_get_unlensed_Cl_PhiPhi(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_PhiPhi;
      result = BEreq::class_get_unlensed_cl("pp");

      // Loop through the PhiPhi spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the PhiPhi spectrum.");
        }
      }
    }

    /* LENSED SPECTRA */

    /// Temperature autocorrelation
    void class_get_lensed_Cl_TT(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_TT;
      result = BEreq::class_get_lensed_cl("tt");

      // Loop through the TT spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the TT spectrum.");
        }
      }
    }

    /// Temperature & E-mode cross-correlation
    void class_get_lensed_Cl_TE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_TE;
      result = BEreq::class_get_lensed_cl("te");
    }

    /// E-mode autocorrelation
    void class_get_lensed_Cl_EE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_EE;
      result = BEreq::class_get_lensed_cl("ee");

      // Loop through the EE spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the EE spectrum.");
        }
      }
    }

    /// B-mode autocorrelation
    void class_get_lensed_Cl_BB(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_BB;
      result = BEreq::class_get_lensed_cl("bb");

      // Loop through the BB spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the BB spectrum.");
        }
      }
    }

    /// Lensing (Phi) autocorrelation
    void class_get_lensed_Cl_PhiPhi(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_PhiPhi;
      result = BEreq::class_get_lensed_cl("pp");

      // Loop through the PhiPhi spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the PhiPhi spectrum.");
        }
      }
    }

    ////////////////
    /// DarkAges ///
    ////////////////

    /// Get the energy injection efficiency table from DarkAges.
    void energy_injection_efficiency_func(DarkAges::Energy_injection_efficiency_table& result)
    {
      using namespace Pipes::energy_injection_efficiency_func;
      result = BEreq::get_energy_injection_efficiency_table();
    }

    /// Calculate the effective energy injection efficiency by convulution
    /// of f_eff(z) with a weighting function W(z) that takes the sensitivity
    /// of the CMB for energy injection as a function of redshift into account.
    /// [cf. https://arxiv.org/abs/1506.03811]
    void f_eff_weighted(double& result)
    {
      using namespace Pipes::f_eff_weighted;

      // Read in the table with the weighting function
      static ASCIItableReader W_table;
      static bool first = true;
      if (first)
      {
        W_table = std::move( ASCIItableReader(GAMBIT_DIR "/CosmoBit/data/EnergyInjection/f_eff_weighting_function.txt") );
        W_table.setcolnames({"z+1","W(z)"});
        first = false;
      }

      static const std::vector<double>& zp1 = W_table["z+1"];
      static const std::vector<double>& Wz = W_table["W(z)"];
      static double zp1_min = zp1[0];
      static double zp1_max = zp1[zp1.size()-1];

      // Retrieve the Energy_injection_efficiency_table.
      static DarkAges::Energy_injection_efficiency_table fz_cached;
      DarkAges::Energy_injection_efficiency_table fz = *Dep::energy_injection_efficiency;

      const std::vector<double>& z = fz.redshift;
      const std::vector<double>& f_eff = fz.f_eff;

      // Ensure that the redshift range required by the W(z) table is covered by fz
      if (zp1_min-1 < z[0] || zp1_max-1 > z[z.size()-1])
      {
        std::ostringstream ss;
        ss << "The redshift range of the energy injection efficiency table "
           << "[" << fz.redshift[0] << ", " << fz.redshift[fz.redshift.size()-1] << "] must cover "
           << "the redshift range required by the W(z) table [" << zp1_min-1 << ", " << zp1_max-1 << "].\n\n";
        CosmoBit_error().raise(LOCAL_INFO, ss.str());
      }

      // Sample the energy injection efficiency table at the redshift coordinates of the W(z) table
      // (only if fz_cached != fz)
      if (fz_cached != fz)
      {
        std::vector<double> sampled_fz;
        sampled_fz.reserve(zp1.size());

        gsl_interp_accel *gsl_accel_ptr = gsl_interp_accel_alloc();
        gsl_spline *spline_ptr = gsl_spline_alloc(gsl_interp_linear, z.size());

        gsl_spline_init(spline_ptr, z.data(), f_eff.data(), z.size());
        for (const auto& it: zp1)
        {
          sampled_fz.emplace_back(gsl_spline_eval(spline_ptr, it-1, gsl_accel_ptr));
        }

        gsl_spline_free(spline_ptr);
        gsl_interp_accel_free(gsl_accel_ptr);

        // Perform the discretised integral
        // 1) Perform the inner product
        result = std::inner_product(Wz.begin(), Wz.end(), sampled_fz.begin(), 0.0);
        // 2) Normalise by the integral over W(z)
        static double Wz_norm = std::accumulate(Wz.begin(),Wz.end(),0.0);
        result /= Wz_norm;

        // Update the cached table
        fz_cached = fz;
      }
    }

    /// Calculate the effective energy injection efficiency by taking the
    /// value of f_eff(z) at given z.
    void f_eff_at_z(double& result)
    {
      using namespace Pipes::f_eff_at_z;

      // Get the redshift at which f_eff should be evaluated
      // The default depends on the scenario in question
      static double z_eff = 0.01;
      static bool first = true;
      if (first)
      {
        if(ModelInUse("DecayingDM_general"))
        {
          z_eff = runOptions->getValueOrDef<double>(300.,"z_eff");
        }
        else if (ModelInUse("AnnihilatingDM_general"))
        {
          z_eff = runOptions->getValueOrDef<double>(600.,"z_eff");
        }

        first = false;
      }

      // Retrieve the Energy_injection_efficiency_table.
      static DarkAges::Energy_injection_efficiency_table fz_cached;
      DarkAges::Energy_injection_efficiency_table fz = *Dep::energy_injection_efficiency;

      if (fz_cached != fz)
      {
        const std::vector<double>& z = fz.redshift;
        const std::vector<double>& f_eff = fz.f_eff;
        const size_t npts = z.size();

        /// Set-up, do the interpolation, and claen-up
        gsl_interp_accel *gsl_accel_ptr = gsl_interp_accel_alloc();
        gsl_spline *spline_ptr = gsl_spline_alloc(gsl_interp_cspline, npts);
        gsl_spline_init(spline_ptr, z.data(), f_eff.data(), npts);

        result = gsl_spline_eval(spline_ptr, z_eff, gsl_accel_ptr);

        gsl_spline_free(spline_ptr);
        gsl_interp_accel_free(gsl_accel_ptr);

        // Update the cached table
        fz_cached = fz;
      }
    }

    /// Manually set the effective energy injection efficiency.
    void f_eff_constant(double& result)
    {
      result = Pipes::f_eff_constant::runOptions->getValueOrDef<double>(1.0,"f_eff");
    }

    /// Calculate the annihilation rate p_ann = f_eff * f^2 * <sv>/m
    /// (Unit of result is: cm^3 s^-1 GeV^-1)
    void p_ann(double& result)
    {
      using namespace Pipes::p_ann;

      double m = *Param["mass"];
      double f2_sv = *Param["sigmav"]; // Note: The factor f^2 is already included in the parameter sigmav
      double f_eff = *Dep::f_eff;

      result = f_eff * f2_sv / m;
    }

    // Profiled likelihood on p_ann.
    // Used Datasets:
    //  - P18 highl TT+TE+EE (lite)
    //  - P18 lowl TT+EE
    //  - P18 lensing
    //  - BAO ("smallz 2014" + BOSS DR12)
    void lnL_p_ann_P18_TTTEEE_lowE_lensing_BAO(double& result)
    {
      using namespace Pipes::lnL_p_ann_P18_TTTEEE_lowE_lensing_BAO;

      const double p_ann28 = (*Dep::p_ann)*1e28;

      // The likelihood is given by a Gaussian in p_ann28
      // centered around -0.48 with a width of 2.48/sqrt(2)
      result = Stats::gaussian_loglikelihood(p_ann28, -0.48, 0.0, 2.48/sqrt(2.), true);
    }

    /// The energy injection spectrum from the AnnihilatingDM model hierarchy.
    void energy_injection_spectrum_AnnihilatingDM_mixture(DarkAges::Energy_injection_spectrum& spectrum)
    {
      using namespace Pipes::energy_injection_spectrum_AnnihilatingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR_el"];
      double BR_ph = *Param["BR_ph"];

      logger() << LogTags::debug << "Creating \'energy_injection_spectrum\' for \'AnnihilatingDM_mixture\'\n\n";
      logger() << "- Branching fraction into e+/e-: " << BR_el;
      logger() << "\n- Branching fraction into photons: " << BR_ph;
      logger() << "\n- Branching fraction into inefficient final state: " << 1 - BR_ph - BR_el << "\n" << EOM;

      if (BR_el + BR_ph > 1.0)
      {
        std::ostringstream err;
        err << "The sum of the branching fractions into electrons and photons (BR_el and BR_ph) must not exceed 1.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the annihilating dark matter candidate is below the electron mass.";
        err << " No production of e+/e- is possible.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      spectrum.E_el.clear();
      spectrum.E_ph.clear();
      spectrum.spec_el.clear();
      spectrum.spec_ph.clear();

      spectrum.E_el.resize(1,std::max(m-m_electron, std::numeric_limits<double>::min()));
      spectrum.E_ph.resize(1,m);
      spectrum.spec_el.resize(1,BR_el*2e9);
      spectrum.spec_ph.resize(1,BR_ph*2e9);
    }

    /// The energy injection spectrum from the DecayingDM model hierarchy.
    void energy_injection_spectrum_DecayingDM_mixture(DarkAges::Energy_injection_spectrum& spectrum)
    {
      using namespace Pipes::energy_injection_spectrum_DecayingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR_el"];
      double BR_ph = *Param["BR_ph"];

      logger() << LogTags::debug << "Creating \'energy_injection_spectrum\' for \'DecayingDM_mixture\'\n\n";
      logger() << "- Branching fraction into e+/e-: " << BR_el;
      logger() << "\n- Branching fraction into photons: " << BR_ph;
      logger() << "\n- Branching fraction into inefficient final state: " << 1 - BR_ph - BR_el << "\n" << EOM;

      if (BR_el + BR_ph > 1.0)
      {
        std::ostringstream err;
        err << "The sum of the branching fractions into electrons and photons (BR_el and BR_ph) must not exceed 1.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= 2*m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the decaying dark matter candidate is below twice the electron mass.";
        err << " No production of e+/e- is possible.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      spectrum.E_el.clear();
      spectrum.E_ph.clear();
      spectrum.spec_el.clear();
      spectrum.spec_ph.clear();

      spectrum.E_el.resize(1,std::max(m*0.5-m_electron, std::numeric_limits<double>::min()));
      spectrum.E_ph.resize(1,m*0.5);
      spectrum.spec_el.resize(1,BR_el*2e9);
      spectrum.spec_ph.resize(1,BR_ph*2e9);
    }

  } // namespace CosmoBit

} // namespace Gambit
