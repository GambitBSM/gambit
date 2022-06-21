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

#include "gambit/Elements/gambit_module_headers.hpp"
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
        model_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the annihilating dark matter candidate is below the electron mass.";
        err << " No production of e+/e- is possible.";
        model_error().raise(LOCAL_INFO,err.str());
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
        model_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= 2*m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the decaying dark matter candidate is below twice the electron mass.";
        err << " No production of e+/e- is possible.";
        model_error().raise(LOCAL_INFO,err.str());
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
