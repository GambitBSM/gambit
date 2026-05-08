//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit that deal exclusively with Higgs physics.
///  Some functions were originally in ColliderBit.cpp.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Rogan
///          (crogan@cern.ch)
///  \date 2014 Aug
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2016 Sep
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Sep
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2020 Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Mar
///
///  *********************************************

#include <cmath>
#include <string>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"


namespace Gambit
{

  namespace ColliderBit
  {

    /// Resize all per-particle vectors in a HiggsTools_input to the given sizes
    /// and zero them.  Two-index containers are sized as n_neutral x n_neutral.
    static void resize_HiggsTools_input(HiggsTools_input& d, int n_neutral, int n_charged)
    {
      d.n_neutral = n_neutral;
      d.n_charged = n_charged;

      auto resize_n = [&](std::vector<double>& v) { v.assign(n_neutral, 0.0); };
      resize_n(d.Mh);
      resize_n(d.deltaMh);
      resize_n(d.hGammaTot);
      resize_n(d.CP);
      resize_n(d.BR_hjss);
      resize_n(d.BR_hjcc);
      resize_n(d.BR_hjbb);
      resize_n(d.BR_hjmumu);
      resize_n(d.BR_hjtautau);
      resize_n(d.BR_hjWW);
      resize_n(d.BR_hjZZ);
      resize_n(d.BR_hjZga);
      resize_n(d.BR_hjgaga);
      resize_n(d.BR_hjgg);
      resize_n(d.BR_hjinvisible);
      resize_n(d.g2hjss);
      resize_n(d.g2hjcc);
      resize_n(d.g2hjbb);
      resize_n(d.g2hjtt);
      resize_n(d.g2hjmumu);
      resize_n(d.g2hjtautau);
      resize_n(d.g2hjWW);
      resize_n(d.g2hjZZ);
      resize_n(d.g2hjgaga);
      resize_n(d.g2hjZga);
      resize_n(d.g2hjgg);
      d.BR_hjhihi.assign(n_neutral, std::vector<double>(n_neutral, 0.0));

      auto resize_c = [&](std::vector<double>& v) { v.assign(n_charged, 0.0); };
      resize_c(d.MHplus);
      resize_c(d.deltaMHplus);
      resize_c(d.HpGammaTot);
      resize_c(d.BR_Hpjcs);
      resize_c(d.BR_Hpjcb);
      resize_c(d.BR_Hptaunu);
      resize_c(d.BR_tHpjb);
      d.BR_tWpb = 0.0;
    }

    /// Copy effective couplings squared from a HiggsCouplingsTable into the
    /// input DTO for the requested neutral Higgs index.
    static void set_eff_couplings(HiggsTools_input& d, int i, const HiggsCouplingsTable& c)
    {
      d.g2hjWW[i]      = c.C_WW2[i];
      d.g2hjZZ[i]      = c.C_ZZ2[i];
      d.g2hjtt[i]      = c.C_tt2[i];
      d.g2hjbb[i]      = c.C_bb2[i];
      d.g2hjcc[i]      = c.C_cc2[i];
      d.g2hjss[i]      = c.C_ss2[i];
      d.g2hjtautau[i]  = c.C_tautau2[i];
      d.g2hjmumu[i]    = c.C_mumu2[i];
      d.g2hjgaga[i]    = c.C_gaga2[i];
      d.g2hjZga[i]     = c.C_Zga2[i];
      d.g2hjgg[i]      = c.C_gg2[i];
    }

    /// Helper function for populating a HiggsTools_input for SM-like Higgs.
    void set_SMLikeHiggs_ModelParameters(const SubSpectrum& spec, const HiggsCouplingsTable& couplings, HiggsTools_input& result)
    {
      resize_HiggsTools_input(result, 1, 0);

      const DecayTable::Entry& decays = couplings.get_neutral_decays(0);

      result.CP[0] = couplings.CP[0];
      result.Mh[0] = spec.get(Par::Pole_Mass, 25, 0);
      const bool has_high_err = spec.has(Par::Pole_Mass_1srd_high, 25, 0);
      const bool has_low_err  = spec.has(Par::Pole_Mass_1srd_low, 25, 0);
      if (has_high_err and has_low_err)
      {
        const double upper = spec.get(Par::Pole_Mass_1srd_high, 25, 0);
        const double lower = spec.get(Par::Pole_Mass_1srd_low, 25, 0);
        result.deltaMh[0] = result.Mh[0] * std::max(upper, lower);
      }

      result.hGammaTot[0]    = decays.width_in_GeV;
      result.BR_hjss[0]      = decays.BF("s", "sbar");
      result.BR_hjcc[0]      = decays.BF("c", "cbar");
      result.BR_hjbb[0]      = decays.BF("b", "bbar");
      result.BR_hjmumu[0]    = decays.BF("mu+", "mu-");
      result.BR_hjtautau[0]  = decays.BF("tau+", "tau-");
      result.BR_hjWW[0]      = decays.BF("W+", "W-");
      result.BR_hjZZ[0]      = decays.BF("Z0", "Z0");
      result.BR_hjZga[0]     = decays.BF("gamma", "Z0");
      result.BR_hjgaga[0]    = decays.BF("gamma", "gamma");
      result.BR_hjgg[0]      = decays.BF("g", "g");

      result.BR_hjinvisible[0] = 0.0;
      for (auto it = couplings.invisibles.begin(); it != couplings.invisibles.end(); ++it)
      {
        result.BR_hjinvisible[0] += decays.BF(it->first, it->second);
      }

      set_eff_couplings(result, 0, couplings);
    }

    /// SM-like (SM + possible invisibles) Higgs model parameters.
    void SMLikeHiggs_ModelParameters(HiggsTools_input& result)
    {
      using namespace Pipes::SMLikeHiggs_ModelParameters;
      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
      if (ModelInUse("ScalarSingletDM_Z2") or ModelInUse("ScalarSingletDM_Z2_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z2_spectrum;
      else if (ModelInUse("ScalarSingletDM_Z3") or ModelInUse("ScalarSingletDM_Z3_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z3_spectrum;
      else if (ModelInUse("StandardModel_Higgs") or ModelInUse("StandardModel_Higgs_running")) spectrum_dependency = &Dep::SM_spectrum;
      else ColliderBit_error().raise(LOCAL_INFO, "No valid model for SMLikeHiggs_ModelParameters.");
      const SubSpectrum& spec = (*spectrum_dependency)->get_HE();
      set_SMLikeHiggs_ModelParameters(spec, *Dep::Higgs_Couplings, result);
    }

    /// MSSM-like (MSSM + NMSSM + ...) Higgs model parameters.
    void MSSMLikeHiggs_ModelParameters(HiggsTools_input& result)
    {
      using namespace Pipes::MSSMLikeHiggs_ModelParameters;

      const int n_neutral = Dep::Higgs_Couplings->get_n_neutral_higgs();
      const int n_charged = Dep::Higgs_Couplings->get_n_charged_higgs();
      resize_HiggsTools_input(result, n_neutral, n_charged);

      for (int i = 0; i < n_neutral; ++i) result.CP[i] = Dep::Higgs_Couplings->CP[i];

      const std::vector<const DecayTable::Entry*>& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array();
      const DecayTable::Entry& H_plus_widths = Dep::Higgs_Couplings->get_charged_decays(0);
      const DecayTable::Entry& t_widths = Dep::Higgs_Couplings->get_t_decays();

      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
      std::vector<str> Higgses;
      if (ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ"))
      {
        spectrum_dependency = &Dep::MSSM_spectrum;
        Higgses = initVector<str>("h0_1", "h0_2", "A0");
      }
      else ColliderBit_error().raise(LOCAL_INFO, "No valid model for MSSMLikeHiggs_ModelParameters.");

      const SubSpectrum& spec = (*spectrum_dependency)->get_HE();
      static const std::vector<str> sHneut(Higgses);

      for (int i = 0; i < n_neutral; ++i)
      {
        result.Mh[i] = spec.get(Par::Pole_Mass, sHneut[i]);
        const double upper = spec.get(Par::Pole_Mass_1srd_high, sHneut[i]);
        const double lower = spec.get(Par::Pole_Mass_1srd_low, sHneut[i]);
        result.deltaMh[i] = result.Mh[i] * std::max(upper, lower);
      }

      for (int i = 0; i < n_neutral; ++i)
      {
        const DecayTable::Entry& dec = *h0_widths[i];
        result.hGammaTot[i]   = dec.width_in_GeV;
        result.BR_hjss[i]     = dec.BF("s", "sbar");
        result.BR_hjcc[i]     = dec.BF("c", "cbar");
        result.BR_hjbb[i]     = dec.BF("b", "bbar");
        result.BR_hjmumu[i]   = dec.BF("mu+", "mu-");
        result.BR_hjtautau[i] = dec.BF("tau+", "tau-");
        result.BR_hjWW[i]     = dec.has_channel("W+", "W-") ? dec.BF("W+", "W-") : 0.0;
        result.BR_hjZZ[i]     = dec.has_channel("Z0", "Z0") ? dec.BF("Z0", "Z0") : 0.0;
        result.BR_hjZga[i]    = dec.has_channel("gamma", "Z0") ? dec.BF("gamma", "Z0") : 0.0;
        result.BR_hjgaga[i]   = dec.BF("gamma", "gamma");
        result.BR_hjgg[i]     = dec.BF("g", "g");

        result.BR_hjinvisible[i] = 0.0;
        for (auto it = Dep::Higgs_Couplings->invisibles.begin(); it != Dep::Higgs_Couplings->invisibles.end(); ++it)
        {
          result.BR_hjinvisible[i] += dec.BF(it->first, it->second);
        }
        for (int j = 0; j < n_neutral; ++j)
        {
          result.BR_hjhihi[i][j] = (2.0 * result.Mh[j] < result.Mh[i] and dec.has_channel(sHneut[j], sHneut[j]))
                                 ? dec.BF(sHneut[j], sHneut[j]) : 0.0;
        }

        set_eff_couplings(result, i, *Dep::Higgs_Couplings);
      }

      if (n_charged > 0)
      {
        result.MHplus[0] = spec.get(Par::Pole_Mass, "H+");
        const double upper = spec.get(Par::Pole_Mass_1srd_high, "H+");
        const double lower = spec.get(Par::Pole_Mass_1srd_low, "H+");
        result.deltaMHplus[0] = result.MHplus[0] * std::max(upper, lower);
        result.HpGammaTot[0]  = H_plus_widths.width_in_GeV;
        result.BR_Hpjcs[0]    = H_plus_widths.BF("c", "sbar");
        result.BR_Hpjcb[0]    = H_plus_widths.BF("c", "bbar");
        result.BR_Hptaunu[0]  = H_plus_widths.BF("tau+", "nu_tau");
        result.BR_tWpb        = t_widths.BF("W+", "b");
        result.BR_tHpjb[0]    = t_widths.has_channel("H+", "b") ? t_widths.BF("H+", "b") : 0.0;
      }
    }

    /// LHC Higgs chi^2 log-likelihood from HiggsTools (HiggsSignals).
    void calc_HiggsTools_LHC_LogLike(double& result)
    {
      using namespace Pipes::calc_HiggsTools_LHC_LogLike;
      result = BEreq::HiggsTools_LHC_LogLike(*Dep::HiggsTools_ModelParameters);
    }

    /// Higgs production cross-sections from FeynHiggs.
    void FeynHiggs_HiggsProd(fh_HiggsProd_container& result)
    {
      using namespace Pipes::FeynHiggs_HiggsProd;

      Farray<fh_real, 1, 52> prodxs;
      fh_HiggsProd_container HiggsProd;
      int error;
      fh_real sqrts;

      sqrts = 2.0;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for Tevatron: " << error << ".";
        invalid_point().raise(err.str());
      }
      for (int i = 0; i < 52; ++i) HiggsProd.prodxs_Tev[i] = prodxs(i + 1);

      sqrts = 7.0;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for LHC7: " << error << ".";
        invalid_point().raise(err.str());
      }
      for (int i = 0; i < 52; ++i) HiggsProd.prodxs_LHC7[i] = prodxs(i + 1);

      sqrts = 8.0;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for LHC8: " << error << ".";
        invalid_point().raise(err.str());
      }
      for (int i = 0; i < 52; ++i) HiggsProd.prodxs_LHC8[i] = prodxs(i + 1);

      result = HiggsProd;
    }

  }
}
