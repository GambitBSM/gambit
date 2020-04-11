//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit that deal exclusively with Higgs physics
///  some functions were originally in CollderBit.cpp
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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
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
#include "gambit/Utils/statistics.hpp"

// #define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// Helper function to set HiggsBounds/Signals parameters cross-section ratios from a GAMBIT HiggsCouplingsTable
    void set_CS_neutral(hb_neutral_ModelParameters_part &result, const HiggsCouplingsTable& couplings, int n_neutral_higgses)
    {
      for(int i = 0; i < n_neutral_higgses; i++)
      {
        result.CS_bg_hjb_ratio[i] = couplings.C_bb2[i];
        result.CS_bb_hj_ratio[i]  = couplings.C_bb2[i];
        result.CS_lep_bbhj_ratio[i] = couplings.C_bb2[i];

        result.CS_lep_tautauhj_ratio[i] = couplings.C_tautau2[i];

        result.CS_lep_hjZ_ratio[i] = couplings.C_ZZ2[i];
        result.CS_gg_hjZ_ratio[i] = 0.;
        result.CS_dd_hjZ_ratio[i] = couplings.C_ZZ2[i];
        result.CS_uu_hjZ_ratio[i] = couplings.C_ZZ2[i];
        result.CS_ss_hjZ_ratio[i] = couplings.C_ZZ2[i];
        result.CS_cc_hjZ_ratio[i] = couplings.C_ZZ2[i];
        result.CS_bb_hjZ_ratio[i] = couplings.C_ZZ2[i];

        result.CS_ud_hjWp_ratio[i] = couplings.C_WW2[i];
        result.CS_cs_hjWp_ratio[i] = couplings.C_WW2[i];
        result.CS_ud_hjWm_ratio[i] = couplings.C_WW2[i];
        result.CS_cs_hjWm_ratio[i] = couplings.C_WW2[i];

        result.CS_tev_vbf_ratio[i]  = couplings.C_WW2[i];
        result.CS_lhc7_vbf_ratio[i] = couplings.C_WW2[i];
        result.CS_lhc8_vbf_ratio[i] = couplings.C_WW2[i];

        result.CS_gg_hj_ratio[i] = couplings.C_gg2[i];

        result.CS_tev_tthj_ratio[i] = couplings.C_tt2[i];
        result.CS_lhc7_tthj_ratio[i] = couplings.C_tt2[i];
        result.CS_lhc8_tthj_ratio[i] = couplings.C_tt2[i];

        for(int j = 0; j < n_neutral_higgses; j++)
        {
          result.CS_lep_hjhi_ratio[i][j] = couplings.C_hiZ2[i][j];
        }
      }
    }

    void set_CS_charged(hb_charged_ModelParameters &result)
    {
      // LEP H+ H- x-section ratio
      result.CS_lep_HpjHmi_ratio[0] = 1.;
    }

    /// Helper function for populating a HiggsBounds/Signals ModelParameters object for SM-like Higgs.
    void set_SMLikeHiggs_ModelParameters(const SubSpectrum& spec, const HiggsCouplingsTable& couplings, hb_neutral_ModelParameters_part &result)
    {
      // Retrieve the decays
      const DecayTable::Entry& decays = couplings.get_neutral_decays(0);

      // Set the CP of the lone higgs
      result.CP[0] = couplings.CP[0];

      // Set h mass and uncertainty
      result.Mh[0] = spec.get(Par::Pole_Mass,25,0);
      bool has_high_err = spec.has(Par::Pole_Mass_1srd_high, 25, 0);
      bool has_low_err = spec.has(Par::Pole_Mass_1srd_low, 25, 0);
      if (has_high_err and has_low_err)
      {
        double upper = spec.get(Par::Pole_Mass_1srd_high, 25, 0);
        double lower = spec.get(Par::Pole_Mass_1srd_low, 25, 0);
        result.deltaMh[0] = result.Mh[0] * std::max(upper,lower);
      }
      else
      {
        result.deltaMh[0] = 0.;
      }

      // Set the total h width
      result.hGammaTot[0] = decays.width_in_GeV;

      // Set the branching fractions
      result.BR_hjss[0] = decays.BF("s", "sbar");
      result.BR_hjcc[0] = decays.BF("c", "cbar");
      result.BR_hjbb[0] = decays.BF("b", "bbar");
      result.BR_hjmumu[0] = decays.BF("mu+", "mu-");
      result.BR_hjtautau[0] = decays.BF("tau+", "tau-");
      result.BR_hjWW[0] = decays.BF("W+", "W-");
      result.BR_hjZZ[0] = decays.BF("Z0", "Z0");
      result.BR_hjZga[0] = decays.BF("gamma", "Z0");
      result.BR_hjgaga[0] = decays.BF("gamma", "gamma");
      result.BR_hjgg[0] = decays.BF("g", "g");

      // Add the invisibles
      result.BR_hjinvisible[0] = 0.;
      for (auto it = couplings.invisibles.begin(); it != couplings.invisibles.end(); ++it)
      {
        result.BR_hjinvisible[0] += decays.BF(*it, *it);
      }

      // Retrieve cross-section ratios from the HiggsCouplingsTable
      set_CS_neutral(result, couplings, 1);

      // Zero all heavy neutral higgs masses, widths and effective couplings
      for(int i = 1; i < 3; i++)
      {
        result.Mh[i] = 0.;
        result.deltaMh[i] = 0.;
        result.hGammaTot[i] = 0.;
        result.CP[i] = 0.;
        result.BR_hjss[i] = 0.;
        result.BR_hjcc[i] = 0.;
        result.BR_hjbb[i] = 0.;
        result.BR_hjmumu[i] = 0.;
        result.BR_hjtautau[i] = 0.;
        result.BR_hjWW[i] = 0.;
        result.BR_hjZZ[i] = 0.;
        result.BR_hjZga[i] = 0.;
        result.BR_hjgaga[i] = 0.;
        result.BR_hjgg[i] = 0.;
        result.BR_hjinvisible[i] = 0.;
        result.CS_lep_hjZ_ratio[i] = 0.;
        result.CS_lep_bbhj_ratio[i] = 0.;
        result.CS_lep_tautauhj_ratio[i] = 0.;
        result.CS_gg_hj_ratio[i] = 0.;
        result.CS_bb_hj_ratio[i] = 0.;
        result.CS_bg_hjb_ratio[i] = 0.;
        result.CS_ud_hjWp_ratio[i] = 0.;
        result.CS_cs_hjWp_ratio[i] = 0.;
        result.CS_ud_hjWm_ratio[i] = 0.;
        result.CS_cs_hjWm_ratio[i] = 0.;
        result.CS_gg_hjZ_ratio[i] = 0.;
        result.CS_dd_hjZ_ratio[i] = 0.;
        result.CS_uu_hjZ_ratio[i] = 0.;
        result.CS_ss_hjZ_ratio[i] = 0.;
        result.CS_cc_hjZ_ratio[i] = 0.;
        result.CS_bb_hjZ_ratio[i] = 0.;
        result.CS_tev_vbf_ratio[i] = 0.;
        result.CS_tev_tthj_ratio[i] = 0.;
        result.CS_lhc7_vbf_ratio[i] = 0.;
        result.CS_lhc7_tthj_ratio[i] = 0.;
        result.CS_lhc8_vbf_ratio[i] = 0.;
        result.CS_lhc8_tthj_ratio[i] = 0.;
        for(int j = 0; j < 3; j++) result.BR_hjhihi[i][j] = 0.;
        for(int j = 0; j < 3; j++) result.CS_lep_hjhi_ratio[i][j] = 0.;
      }
    }

    /// Helper function for populating a HiggsBounds/Signals ModelParameters object for SM-like Higgs (charged).
    void set_SMLikeHiggs_ModelParameters_charged(hb_charged_ModelParameters &result)
    {
      // Cross section 
      set_CS_charged(result); // zeroed later regardless? Is this necessary?
      // Zero all H+ masses, widths and effective couplings
      result.MHplus[0] = 0.;
      result.deltaMHplus[0] = 0.;
      result.HpGammaTot[0] = 0.;
      result.BR_tWpb = 0.;
      result.BR_tHpjb[0] = 0.;
      result.BR_Hpjcs[0] = 0.;
      result.BR_Hpjcb[0] = 0.;
      result.BR_Hptaunu[0] = 0.;
      result.CS_lep_HpjHmi_ratio[0] = 0.;
    }

    /// SM Higgs model parameters for HiggsBounds/Signals
    void SMHiggs_ModelParameters(hb_neutral_ModelParameters_part &result)
    {
      using namespace Pipes::SMHiggs_ModelParameters;
      set_SMLikeHiggs_ModelParameters(Dep::SM_spectrum->get_HE(), *Dep::Higgs_Couplings, result);
    }

        /// SM Higgs model parameters for HiggsBounds/Signals
    void SMHiggs_ModelParameters_charged(hb_charged_ModelParameters &result)
    {
      using namespace Pipes::SMHiggs_ModelParameters_charged;
      set_SMLikeHiggs_ModelParameters_charged(result);
    }

    /// SM-like (SM + possible invisibles) Higgs model parameters for HiggsBounds/Signals
    void SMLikeHiggs_ModelParameters(hb_neutral_ModelParameters_part &result)
    {
      using namespace Pipes::SMLikeHiggs_ModelParameters;
      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
      if (ModelInUse("ScalarSingletDM_Z2") or ModelInUse("ScalarSingletDM_Z2_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z2_spectrum;
      else if (ModelInUse("ScalarSingletDM_Z3") or ModelInUse("ScalarSingletDM_Z3_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z3_spectrum;
      else ColliderBit_error().raise(LOCAL_INFO, "No valid model for SMLikeHiggs_ModelParameters.");
      const SubSpectrum& spec = (*spectrum_dependency)->get_HE();
      set_SMLikeHiggs_ModelParameters(spec, *Dep::Higgs_Couplings, result);
    }

    /// SM-like (SM + possible invisibles) Higgs model parameters for HiggsBounds/Signals
    void SMLikeHiggs_ModelParameters_charged(hb_charged_ModelParameters &result)
    {
      using namespace Pipes::SMLikeHiggs_ModelParameters_charged;
      set_SMLikeHiggs_ModelParameters_charged(result);
    }

    /// MSSM Higgs model parameters
    void MSSMHiggs_ModelParameters(hb_neutral_ModelParameters_part &result)
    {
      using namespace Pipes::MSSMHiggs_ModelParameters;

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Set the CP of the Higgs states.
      for (int i = 0; i < 3; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

      // Retrieve higgs partial widths
      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(3);

      // Retrieve masses
      const Spectrum& fullspectrum = *Dep::MSSM_spectrum;
      const SubSpectrum& spec = fullspectrum.get_HE();

      // Neutral higgs masses and errors
      for(int i = 0; i < 3; i++)
      {
        result.Mh[i] = spec.get(Par::Pole_Mass,sHneut[i]);
        double upper = spec.get(Par::Pole_Mass_1srd_high,sHneut[i]);
        double lower = spec.get(Par::Pole_Mass_1srd_low,sHneut[i]);
        result.deltaMh[i] = result.Mh[i] * std::max(upper,lower);
      }

      // Loop over all neutral Higgses, setting their branching fractions and total widths.
      for(int i = 0; i < 3; i++)
      {
        result.hGammaTot[i] = h0_widths[i]->width_in_GeV;
        result.BR_hjss[i] = h0_widths[i]->BF("s", "sbar");
        result.BR_hjcc[i] = h0_widths[i]->BF("c", "cbar");
        result.BR_hjbb[i] = h0_widths[i]->BF("b", "bbar");
        result.BR_hjmumu[i] = h0_widths[i]->BF("mu+", "mu-");
        result.BR_hjtautau[i] = h0_widths[i]->BF("tau+", "tau-");
        result.BR_hjWW[i] = h0_widths[i]->BF("W+", "W-");
        result.BR_hjZZ[i] = h0_widths[i]->BF("Z0", "Z0");
        result.BR_hjZga[i] = h0_widths[i]->BF("gamma", "Z0");
        result.BR_hjgaga[i] = h0_widths[i]->BF("gamma", "gamma");
        result.BR_hjgg[i] = h0_widths[i]->BF("g", "g");
        // Do decays to invisibles
        result.BR_hjinvisible[i] = 0.;
        for (auto it = Dep::Higgs_Couplings->invisibles.begin(); it != Dep::Higgs_Couplings->invisibles.end(); ++it)
        {
          result.BR_hjinvisible[i] += h0_widths[i]->BF(*it, *it);
        }
        // Do decays to other neutral higgses
        for (int j = 0; j < 3; j++)
        {
          if (2.*result.Mh[j] < result.Mh[i] and h0_widths[i]->has_channel(sHneut[j],sHneut[j]))
          {
            result.BR_hjhihi[i][j] = h0_widths[i]->BF(sHneut[j],sHneut[j]);
          }
          else
          {
            result.BR_hjhihi[i][j] = 0.;
          }
        }
      }
      // Retrieve cross-section ratios from the HiggsCouplingsTable
      set_CS_neutral(result, *Dep::Higgs_Couplings, 3);
    }

     /// MSSM Higgs model parameters
    void MSSMHiggs_ModelParameters_charged(hb_charged_ModelParameters &result)
    {
      using namespace Pipes::MSSMHiggs_ModelParameters_charged;

      // Retrieve higgs partial widths
      const DecayTable::Entry& H_plus_widths = Dep::Higgs_Couplings->get_charged_decays(0);
      const DecayTable::Entry& t_widths = Dep::Higgs_Couplings->get_t_decays();

      // Retrieve masses
      const Spectrum& fullspectrum = *Dep::MSSM_spectrum;
      const SubSpectrum& spec = fullspectrum.get_HE();

      // Charged higgs masses and errors
      result.MHplus[0] = spec.get(Par::Pole_Mass,"H+");
      double upper = spec.get(Par::Pole_Mass_1srd_high,"H+");
      double lower = spec.get(Par::Pole_Mass_1srd_low,"H+");
      result.deltaMHplus[0] = result.MHplus[0] * std::max(upper,lower);

      // Set charged Higgs branching fractions and total width.
      result.HpGammaTot[0] = H_plus_widths.width_in_GeV;
      result.BR_Hpjcs[0]   = H_plus_widths.BF("c", "sbar");
      result.BR_Hpjcb[0]   = H_plus_widths.BF("c", "bbar");
      result.BR_Hptaunu[0] = H_plus_widths.BF("tau+", "nu_tau");

      // Set top branching fractions
      result.BR_tWpb       = t_widths.BF("W+", "b");
      result.BR_tHpjb[0]   = t_widths.has_channel("H+", "b") ? t_widths.BF("H+", "b") : 0.0;

      // Cross section
      set_CS_charged(result);
     
    }


    /// Get a LEP chisq from HiggsBounds
    void calc_HB_LEP_LogLike(double &result)
    {
      using namespace Pipes::calc_HB_LEP_LogLike;

      hb_neutral_ModelParameters_part ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
      Farray<double, 1,3, 1,3> BR_hjhihi;
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }

      BEreq::HiggsBounds_neutral_input_part(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0],
              &ModelParam.CS_lep_hjZ_ratio[0], &ModelParam.CS_lep_bbhj_ratio[0],
              &ModelParam.CS_lep_tautauhj_ratio[0], CS_lep_hjhi_ratio,
              &ModelParam.CS_gg_hj_ratio[0], &ModelParam.CS_bb_hj_ratio[0],
              &ModelParam.CS_bg_hjb_ratio[0], &ModelParam.CS_ud_hjWp_ratio[0],
              &ModelParam.CS_cs_hjWp_ratio[0], &ModelParam.CS_ud_hjWm_ratio[0],
              &ModelParam.CS_cs_hjWm_ratio[0], &ModelParam.CS_gg_hjZ_ratio[0],
              &ModelParam.CS_dd_hjZ_ratio[0], &ModelParam.CS_uu_hjZ_ratio[0],
              &ModelParam.CS_ss_hjZ_ratio[0], &ModelParam.CS_cc_hjZ_ratio[0],
              &ModelParam.CS_bb_hjZ_ratio[0], &ModelParam.CS_tev_vbf_ratio[0],
              &ModelParam.CS_tev_tthj_ratio[0], &ModelParam.CS_lhc7_vbf_ratio[0],
              &ModelParam.CS_lhc7_tthj_ratio[0], &ModelParam.CS_lhc8_vbf_ratio[0],
              &ModelParam.CS_lhc8_tthj_ratio[0], &ModelParam.BR_hjss[0],
              &ModelParam.BR_hjcc[0], &ModelParam.BR_hjbb[0],
              &ModelParam.BR_hjmumu[0], &ModelParam.BR_hjtautau[0],
              &ModelParam.BR_hjWW[0], &ModelParam.BR_hjZZ[0],
              &ModelParam.BR_hjZga[0], &ModelParam.BR_hjgaga[0],
              &ModelParam.BR_hjgg[0], &ModelParam.BR_hjinvisible[0], BR_hjhihi);

      BEreq::HiggsBounds_charged_input(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
               &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], &ModelParam_charged.BR_Hpjcs[0],
               &ModelParam_charged.BR_Hpjcb[0], &ModelParam_charged.BR_Hptaunu[0]);

      BEreq::HiggsBounds_set_mass_uncertainties(&ModelParam.deltaMh[0],&ModelParam_charged.deltaMHplus[0]);

      #ifdef COLLIDERBIT_DEBUG
        std::cout << "HB input: " << std::endl << \
        " Mh " << ModelParam.Mh[0] << " " << ModelParam.Mh[1] << std::endl << \
        " hGammaTot  " << ModelParam.hGammaTot[0] << std::endl << \
        " CP " << ModelParam.CP[0] << std::endl << \
        " CS_lep_hjZ_ratio " << ModelParam.CS_lep_hjZ_ratio[0] << std::endl << \
        " CS_lep_bbhj_ratio " << ModelParam.CS_lep_bbhj_ratio[0] << std::endl << \
        " CS_lep_tautauhj_ratio " << ModelParam.CS_lep_tautauhj_ratio[0] << std::endl << \
        " CS_gg_hj_ratio " <<  ModelParam.CS_gg_hj_ratio[0] << std::endl << \
        " CS_bb_hj_ratio " << ModelParam.CS_bb_hj_ratio[0] << std::endl << \
        " CS_bg_hjb_ratio " << ModelParam.CS_bg_hjb_ratio[0] << std::endl << \
        " CS_ud_hjWp_ratio " << ModelParam.CS_ud_hjWp_ratio[0] << std::endl << \
        " CS_cs_hjWp_ratio " << ModelParam.CS_cs_hjWp_ratio[0] << std::endl << \
        " CS_ud_hjWm_ratio " << ModelParam.CS_ud_hjWm_ratio[0] << std::endl << \
        " CS_cs_hjWm_ratio " << ModelParam.CS_cs_hjWm_ratio[0] << std::endl << \
        " CS_gg_hjZ_ratio " << ModelParam.CS_gg_hjZ_ratio[0] << std::endl << \
        " CS_dd_hjZ_ratio " << ModelParam.CS_dd_hjZ_ratio[0] << std::endl << \
        " CS_uu_hjZ_ratio " << ModelParam.CS_uu_hjZ_ratio[0] << std::endl << \
        " CS_ss_hjZ_ratio " << ModelParam.CS_ss_hjZ_ratio[0] << std::endl << \
        " CS_cc_hjZ_ratio " << ModelParam.CS_cc_hjZ_ratio[0] << std::endl << \
        " CS_bb_hjZ_ratio " << ModelParam.CS_bb_hjZ_ratio[0] << std::endl << \
        " CS_tev_vbf_ratio " << ModelParam.CS_tev_vbf_ratio[0] << std::endl << \
        " CS_tev_tthj_ratio " << ModelParam.CS_tev_tthj_ratio[0] << std::endl << \
        " CS_lhc7_vbf_ratio " << ModelParam.CS_lhc7_vbf_ratio[0] << std::endl << \
        " CS_lhc7_tthj_ratio " << ModelParam.CS_lhc7_tthj_ratio[0] << std::endl << \
        " CS_lhc8_vbf_ratio " << ModelParam.CS_lhc8_vbf_ratio[0] << std::endl << \
        " CS_lhc8_tthj_ratio " << ModelParam.CS_lhc8_tthj_ratio[0] << std::endl << \
        " BR_hjss " << ModelParam.BR_hjss[0] << std::endl << \
        " BR_hjcc " << ModelParam.BR_hjcc[0] << std::endl << \
        " BR_hjbb " << ModelParam.BR_hjbb[0] << std::endl << \
        " BR_hjmumu " << ModelParam.BR_hjmumu[0] << std::endl << \
        " BR_hjtautau " << ModelParam.BR_hjtautau[0] << std::endl << \
        " BR_hjWW " << ModelParam.BR_hjWW[0] << std::endl << \
        " BR_hjZZ " << ModelParam.BR_hjZZ[0] << std::endl << \
        " BR_hjZga " << ModelParam.BR_hjZga[0] << std::endl << \
        " BR_hjgaga " << ModelParam.BR_hjgaga[0] << std::endl << \
        " BR_hjgg " << ModelParam.BR_hjgg[0] << std::endl << \
        " BR_hjinvisible " << ModelParam.BR_hjinvisible[0] << std::endl;
      #endif

      bool use_classic = false;

      if (use_classic) {
        // run Higgs bounds 'classic'
        double obsratio;
        int HBresult, chan, ncombined;

        BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);

        #ifdef COLLIDERBIT_DEBUG
          std::cout << "HB output: " << std::endl << \
          "hbres: " << HBresult << std::endl << \
          "hbchan: "<< chan << std::endl << \
          "hbobs: " << obsratio << std::endl << \
          "hbcomb: " << ncombined << std::endl;
        #endif

        if (HBresult != -1) {
            if (obsratio < 1.0) result = 0.0;
            else result = Stats::gaussian_upper_limit((obsratio - 1.0),0.0,0.0,1.0,false);
        }
        else {
          std::ostringstream err;
          err << "HB_LEP_Likelihood is invalid." << std::endl;
          invalid_point().raise(err.str());
        }
      }
      else {
        // run Higgs bounds 'v4'
        double obsratio[6];
        int HBresult[6], chan[6], ncombined[6];

        BEreq::run_HiggsBounds_full(HBresult,chan,obsratio,ncombined);

        // extract the LEP chisq
        double chisq_withouttheory,chisq_withtheory;
        int chan2;
        double theor_unc = 1.5; // theory uncertainty
        BEreq::HB_calc_stats(theor_unc,chisq_withouttheory,chisq_withtheory,chan2);

        // Catch HiggsBound's error value, chisq = -999
        if( fabs(chisq_withouttheory - (-999.)) < 1e-6)
        {
          std::ostringstream err;
          err <<  "Got chisq=-999 from HB_calc_stats in HiggsBounds, indicating a cross-section outside tabulated range. Will use chisq=0." << std::endl;
          // ColliderBit_warning().raise(LOCAL_INFO,err.str());
          // chisq_withouttheory = 0.0;
          invalid_point().raise(err.str());
        } 
        result = -0.5*chisq_withouttheory;
      }
      
    }

    /// Get a LEP chisq from HiggsBounds (HB v5)
    void calc_HB_5_LEP_LogLike(double &result)
    {
      using namespace Pipes::calc_HB_5_LEP_LogLike;

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      Farray<double, 1,3, 1,3> ghjhiZ;
      Farray<double, 1,3> BR_HpjhiW;
      for(int i = 0; i < 3; i++) 
      {
        BR_HpjhiW(i+1) = ModelParam_charged.BR_HpjhiW[i];
        for(int j = 0; j < 3; j++) {
          ghjhiZ(i+1,j+1) = ModelParam.ghjhiZ[i][j];
        }
      }

      BEreq::HiggsBounds_neutral_input_properties(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0]);

      BEreq::HiggsBounds_neutral_input_effC(&ModelParam.ghjss_s[0], &ModelParam.ghjss_p[0],
						  						                  &ModelParam.ghjcc_s[0], &ModelParam.ghjcc_p[0],
                                            &ModelParam.ghjbb_s[0], &ModelParam.ghjbb_p[0],
                                            &ModelParam.ghjtt_s[0], &ModelParam.ghjtt_p[0],
                                            &ModelParam.ghjmumu_s[0], &ModelParam.ghjmumu_p[0],
                                            &ModelParam.ghjtautau_s[0], &ModelParam.ghjtautau_p[0],
                                            &ModelParam.ghjWW[0], &ModelParam.ghjZZ[0], &ModelParam.ghjZga[0],
                                            &ModelParam.ghjgaga[0], &ModelParam.ghjgg[0],
                                            ghjhiZ);

      BEreq::HiggsBounds_charged_input(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], 
                                        &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
                                        &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], 
                                        &ModelParam_charged.BR_Hpjcs[0], &ModelParam_charged.BR_Hpjcb[0], 
                                        &ModelParam_charged.BR_Hptaunu[0], &ModelParam_charged.BR_Hpjtb[0],
                                        &ModelParam_charged.BR_HpjWZ[0], BR_HpjhiW);

      BEreq::HiggsBounds_set_mass_uncertainties(&ModelParam.deltaMh[0],&ModelParam_charged.deltaMHplus[0]);

         // run Higgs bounds 'classic'
        double obsratio;
        int HBresult, chan, ncombined;

        BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);

        #ifdef COLLIDERBIT_DEBUG
          std::cout << "HB output: " << std::endl << \
          "hbres: " << HBresult << std::endl << \
          "hbchan: "<< chan << std::endl << \
          "hbobs: " << obsratio << std::endl << \
          "hbcomb: " << ncombined << std::endl;
        #endif

        // extract the LEP chisq
        double chisq_withouttheory,chisq_withtheory;
        int chan2;
        double theor_unc = 1.5; // theory uncertainty
        BEreq::HB_calc_stats(theor_unc,chisq_withouttheory,chisq_withtheory,chan2);

        // Catch HiggsBound's error value, chisq = -999
        if( fabs(chisq_withouttheory - (-999.)) < 1e-6)
        {
          std::ostringstream err;
          err <<  "Got chisq=-999 from HB_calc_stats in HiggsBounds, indicating a cross-section outside tabulated range. Will use chisq=0." << std::endl;
          // ColliderBit_warning().raise(LOCAL_INFO,err.str());
          // chisq_withouttheory = 0.0;
          invalid_point().raise(err.str());
        } 
        result = -0.5*chisq_withouttheory;
    }
    // ***

    /// Get an LHC chisq from HiggsSignals
    void calc_HS_LHC_LogLike(double &result)
    {
      using namespace Pipes::calc_HS_LHC_LogLike;

      hb_neutral_ModelParameters_part ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
      Farray<double, 1,3, 1,3> BR_hjhihi;
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }

      BEreq::HiggsBounds_neutral_input_part_HS(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0],
                 &ModelParam.CS_lep_hjZ_ratio[0], &ModelParam.CS_lep_bbhj_ratio[0],
                 &ModelParam.CS_lep_tautauhj_ratio[0], CS_lep_hjhi_ratio,
                 &ModelParam.CS_gg_hj_ratio[0], &ModelParam.CS_bb_hj_ratio[0],
                 &ModelParam.CS_bg_hjb_ratio[0], &ModelParam.CS_ud_hjWp_ratio[0],
                 &ModelParam.CS_cs_hjWp_ratio[0], &ModelParam.CS_ud_hjWm_ratio[0],
                 &ModelParam.CS_cs_hjWm_ratio[0], &ModelParam.CS_gg_hjZ_ratio[0],
                 &ModelParam.CS_dd_hjZ_ratio[0], &ModelParam.CS_uu_hjZ_ratio[0],
                 &ModelParam.CS_ss_hjZ_ratio[0], &ModelParam.CS_cc_hjZ_ratio[0],
                 &ModelParam.CS_bb_hjZ_ratio[0], &ModelParam.CS_tev_vbf_ratio[0],
                 &ModelParam.CS_tev_tthj_ratio[0], &ModelParam.CS_lhc7_vbf_ratio[0],
                 &ModelParam.CS_lhc7_tthj_ratio[0], &ModelParam.CS_lhc8_vbf_ratio[0],
                 &ModelParam.CS_lhc8_tthj_ratio[0], &ModelParam.BR_hjss[0],
                 &ModelParam.BR_hjcc[0], &ModelParam.BR_hjbb[0],
                 &ModelParam.BR_hjmumu[0], &ModelParam.BR_hjtautau[0],
                 &ModelParam.BR_hjWW[0], &ModelParam.BR_hjZZ[0],
                 &ModelParam.BR_hjZga[0], &ModelParam.BR_hjgaga[0],
                 &ModelParam.BR_hjgg[0], &ModelParam.BR_hjinvisible[0], BR_hjhihi);

      BEreq::HiggsBounds_charged_input_HS(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
            &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], &ModelParam_charged.BR_Hpjcs[0],
            &ModelParam_charged.BR_Hpjcb[0], &ModelParam_charged.BR_Hptaunu[0]);

      BEreq::HiggsSignals_neutral_input_MassUncertainty(&ModelParam.deltaMh[0]);

      // add uncertainties to cross-sections and branching ratios
      // double dCS[5] = {0.,0.,0.,0.,0.};
      // double dBR[5] = {0.,0.,0.,0.,0.};
      // BEreq::setup_rate_uncertainties(dCS,dBR);

     // run HiggsSignals
      int mode = 1; // 1- peak-centered chi2 method (recommended)
      double csqmu, csqmh, csqtot, Pvalue;
      int nobs;
      BEreq::run_HiggsSignals(mode, csqmu, csqmh, csqtot, nobs, Pvalue);

      result = -0.5*csqtot;

      // Add one-sided Gaussian drop in loglike when the lightest Higgs
      // mass is > 150 GeV. This avoids a completely flat loglike 
      // from HS in parameter regions with far too high Higgs mass.
      if (ModelParam.Mh[0] > 150.)
      {
        result -= 0.5 * pow(ModelParam.Mh[0] - 150., 2) / pow(10., 2);
      }
      
      #ifdef COLLIDERBIT_DEBUG
        // likelihood plots
        // csqmh
        ofstream csqmhdbg;
        csqmhdbg.open("HS_debug_csqmh.txt",std::ofstream::out | std::ofstream::app);
        csqmhdbg << csqmh << " " << ModelParam.Mh[0] << "\n";
        csqmhdbg.close();

        ofstream csqmudbg;
        csqmudbg.open("HS_debug_csqmu.txt",std::ofstream::out | std::ofstream::app);
        csqmudbg << csqmu;
        //
        for (int i = 0; i < 3; i++)
        {
           csqmudbg << " " << i << " " <<
           ModelParam.CP[i] << " " <<
           ModelParam.Mh[i] << " " <<
           ModelParam.hGammaTot[i] << " " <<
           ModelParam.CS_lep_hjZ_ratio[i] << " " <<
           ModelParam.CS_tev_vbf_ratio[i] << " " <<
           ModelParam.CS_lep_bbhj_ratio[i] << " " <<
           ModelParam.CS_lep_tautauhj_ratio[i] << " " <<
           ModelParam.CS_gg_hj_ratio[i] << " " <<
           ModelParam.CS_tev_tthj_ratio[i] << " " <<
           ModelParam.CS_lhc7_tthj_ratio[i] << " " <<
           ModelParam.CS_lhc8_tthj_ratio[i];
          for (int j = 0; j < 3; j++) csqmudbg << " " << ModelParam.CS_lep_hjhi_ratio[i][j];
          csqmudbg << " " <<
           ModelParam.BR_hjss[i] << " " <<
           ModelParam.BR_hjcc[i] << " " <<
           ModelParam.BR_hjbb[i] << " " <<
           ModelParam.BR_hjmumu[i] << " " <<
           ModelParam.BR_hjtautau[i] << " " <<
           ModelParam.BR_hjWW[i] << " " <<
           ModelParam.BR_hjZZ[i] << " " <<
           ModelParam.BR_hjZga[i] << " " <<
           ModelParam.BR_hjgaga[i] << " " <<
           ModelParam.BR_hjgg[i] << " " <<
           ModelParam.BR_hjinvisible[i];
          for (int j = 0; j < 3; j++) csqmudbg << " " << ModelParam.BR_hjhihi[i][j];
        }
        csqmudbg << " " << 4 << " " <<
         ModelParam_charged.MHplus[0] << " " <<
         ModelParam_charged.HpGammaTot[0] << " " <<
         ModelParam_charged.CS_lep_HpjHmi_ratio[0] << " " <<
         ModelParam_charged.BR_Hpjcs[0] << " " <<
         ModelParam_charged.BR_Hpjcb[0] << " " <<
         ModelParam_charged.BR_Hptaunu[0] << " " <<
         ModelParam_charged.BR_tWpb << " " <<
         ModelParam_charged.BR_tHpjb[0] << "\n";
        //
        csqmudbg.close();

        std::cout << "HS output: " << std::endl << \
        "csqmu: " << csqmu << std::endl << \
        "csqmh: "<< csqmh << std::endl << \
        "csqtot: " << csqtot << std::endl << \
        "nobs: " << nobs << std::endl << \
        "pval: " << Pvalue << std::endl << \
        "(using Higgs mass): " << ModelParam.Mh[0] << std::endl;
        //
        std::ofstream f;
        f.open ("HB_ModelParameters_contents.dat");
        f<<"LHC log-likleihood";
        for (int i = 0; i < 3; i++) f<<
         "             higgs index"      <<
         "                    "<<i<<":CP"<<
         "                    "<<i<<":Mh"<<
         "             "<<i<<":hGammaTot"<<
         "      "<<i<<":CS_lep_hjZ_ratio"<<
         "      "<<i<<":CS_tev_vbf_ratio"<<
         "     "<<i<<":CS_lep_bbhj_ratio"<<
         " "<<i<<":CS_lep_tautauhj_ratio"<<
         "        "<<i<<":CS_gg_hj_ratio"<<
         "     "<<i<<":CS_tev_tthj_ratio"<<
         "    "<<i<<":CS_lhc7_tthj_ratio"<<
         "    "<<i<<":CS_lhc8_tthj_ratio"<<
         "  "<<i<<":CS_lep_hjhi_ratio[0]"<<
         "  "<<i<<":CS_lep_hjhi_ratio[1]"<<
         "  "<<i<<":CS_lep_hjhi_ratio[2]"<<
         "                 "<<i<<":BR_ss"<<
         "                 "<<i<<":BR_cc"<<
         "                 "<<i<<":BR_bb"<<
         "               "<<i<<":BR_mumu"<<
         "             "<<i<<":BR_tautau"<<
         "                 "<<i<<":BR_WW"<<
         "                 "<<i<<":BR_ZZ"<<
         "                "<<i<<":BR_Zga"<<
         "             "<<i<<":BR_gamgam"<<
         "                 "<<i<<":BR_gg"<<
         "          "<<i<<":BR_invisible"<<
         "            "<<i<<":BR_hihi[0]"<<
         "            "<<i<<":BR_hihi[1]"<<
         "            "<<i<<":BR_hihi[2]";
        f<<
         "             higgs index"      <<
         "                 "<<4<<"MHplus"<<
         "            "<<4<<":HpGammaTot"<<
         "   "<<4<<":CS_lep_HpjHmi_ratio"<<
         "             "<<4<<":BR_H+->cs"<<
         "             "<<4<<":BR_H+->cb"<<
         "          "<<4<<":BR_H+->taunu"<<
         "             "<<4<<":BR_t->W+b"<<
         "             "<<4<<":BR_t->H+b";
        f << endl << std::setw(18) << result;
        const int w = 24;
        for (int i = 0; i < 3; i++)
        {
          f << std::setw(w) << i << std::setw(w) <<
           ModelParam.CP[i] << std::setw(w) <<
           ModelParam.Mh[i] << std::setw(w) <<
           ModelParam.hGammaTot[i] << std::setw(w) <<
           ModelParam.CS_lep_hjZ_ratio[i] << std::setw(w) <<
           ModelParam.CS_tev_vbf_ratio[i] << std::setw(w) <<
           ModelParam.CS_lep_bbhj_ratio[i] << std::setw(w) <<
           ModelParam.CS_lep_tautauhj_ratio[i] << std::setw(w) <<
           ModelParam.CS_gg_hj_ratio[i] << std::setw(w) <<
           ModelParam.CS_tev_tthj_ratio[i] << std::setw(w) <<
           ModelParam.CS_lhc7_tthj_ratio[i] << std::setw(w) <<
           ModelParam.CS_lhc8_tthj_ratio[i];
          for (int j = 0; j < 3; j++) f << std::setw(w) << ModelParam.CS_lep_hjhi_ratio[i][j];
          f << std::setw(w) <<
           ModelParam.BR_hjss[i] << std::setw(w) <<
           ModelParam.BR_hjcc[i] << std::setw(w) <<
           ModelParam.BR_hjbb[i] << std::setw(w) <<
           ModelParam.BR_hjmumu[i] << std::setw(w) <<
           ModelParam.BR_hjtautau[i] << std::setw(w) <<
           ModelParam.BR_hjWW[i] << std::setw(w) <<
           ModelParam.BR_hjZZ[i] << std::setw(w) <<
           ModelParam.BR_hjZga[i] << std::setw(w) <<
           ModelParam.BR_hjgaga[i] << std::setw(w) <<
           ModelParam.BR_hjgg[i] << std::setw(w) <<
           ModelParam.BR_hjinvisible[i];
          for (int j = 0; j < 3; j++) f << std::setw(w) << ModelParam.BR_hjhihi[i][j];
        }
        f << std::setw(w) << 4 << std::setw(w) <<
         ModelParam_charged.MHplus[0] << std::setw(w) <<
         ModelParam_charged.HpGammaTot[0] << std::setw(w) <<
         ModelParam_charged.CS_lep_HpjHmi_ratio[0] << std::setw(w) <<
         ModelParam_charged.BR_Hpjcs[0] << std::setw(w) <<
         ModelParam_charged.BR_Hpjcb[0] << std::setw(w) <<
         ModelParam_charged.BR_Hptaunu[0] << std::setw(w) <<
         ModelParam_charged.BR_tWpb << std::setw(w) <<
         ModelParam_charged.BR_tHpjb[0];
        f.close();
      #endif

    }

    /// Get an LHC chisq from HiggsSignals (v2 beta)
    void calc_HS_2_LHC_LogLike(double &result)
    {
      using namespace Pipes::calc_HS_2_LHC_LogLike;

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      Farray<double, 1,3, 1,3> ghjhiZ;
      Farray<double, 1,3> BR_HpjhiW;
      for(int i = 0; i < 3; i++) 
      {
        BR_HpjhiW(i+1) = ModelParam_charged.BR_HpjhiW[i];
        for(int j = 0; j < 3; j++) {
          ghjhiZ(i+1,j+1) = ModelParam.ghjhiZ[i][j];
        }
      }

      BEreq::HiggsBounds_neutral_input_properties_HS(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0]);

      BEreq::HiggsBounds_neutral_input_effC_HS(&ModelParam.ghjss_s[0], &ModelParam.ghjss_p[0],
						  						                  &ModelParam.ghjcc_s[0], &ModelParam.ghjcc_p[0],
                                            &ModelParam.ghjbb_s[0], &ModelParam.ghjbb_p[0],
                                            &ModelParam.ghjtt_s[0], &ModelParam.ghjtt_p[0],
                                            &ModelParam.ghjmumu_s[0], &ModelParam.ghjmumu_p[0],
                                            &ModelParam.ghjtautau_s[0], &ModelParam.ghjtautau_p[0],
                                            &ModelParam.ghjWW[0], &ModelParam.ghjZZ[0], &ModelParam.ghjZga[0],
                                            &ModelParam.ghjgaga[0], &ModelParam.ghjgg[0],
                                            ghjhiZ);

      BEreq::HiggsBounds_charged_input_HS(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], 
                                        &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
                                        &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], 
                                        &ModelParam_charged.BR_Hpjcs[0], &ModelParam_charged.BR_Hpjcb[0], 
                                        &ModelParam_charged.BR_Hptaunu[0], &ModelParam_charged.BR_Hpjtb[0],
                                        &ModelParam_charged.BR_HpjWZ[0], BR_HpjhiW);

      BEreq::HiggsSignals_neutral_input_MassUncertainty(&ModelParam.deltaMh[0]);

      // add uncertainties to cross-sections and branching ratios
      // double dCS[5] = {0.,0.,0.,0.,0.};
      // double dBR[5] = {0.,0.,0.,0.,0.};
      // BEreq::setup_rate_uncertainties(dCS,dBR);


            // run HiggsSignals
      int mode = 1; // 1- peak-centered chi2 method (recommended)
      double csqmu, csqmh, csqtot, Pvalue;
      double csqmu1, csqmh1, csqtot1, Pvalue1;
      double csqmu2, csqmh2, csqtot2, Pvalue2;
      int nobs, nobs1, nobs2;

      // Run the main subroutines
      BEreq::run_HiggsSignals(mode, csqmu, csqmh, csqtot, nobs, Pvalue);
      BEreq::run_HiggsSignals_LHC_Run1_combination(csqmu1, csqmh1, csqtot1, nobs1, Pvalue1);
      BEreq::run_HiggsSignals_STXS(csqmu2, csqmh2, csqtot2, nobs2, Pvalue2);

      result = -0.5*(csqtot + csqtot1 + csqtot2);
    }

    /// Higgs production cross-sections from FeynHiggs.
    void FH_HiggsProd(fh_HiggsProd &result)
    {
      using namespace Pipes::FH_HiggsProd;

      Farray<fh_real, 1,52> prodxs;

      fh_HiggsProd HiggsProd;
      int error;
      fh_real sqrts;

      // Tevatron
      sqrts = 2.;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for Tevatron: " << error << ".";
        invalid_point().raise(err.str());
      }
      for(int i = 0; i < 52; i++) HiggsProd.prodxs_Tev[i] = prodxs(i+1);
      // LHC7
      sqrts = 7.;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for LHC7: " << error << ".";
        invalid_point().raise(err.str());
      }
      for(int i = 0; i < 52; i++) HiggsProd.prodxs_LHC7[i] = prodxs(i+1);
      // LHC8
      sqrts = 8.;
      error = 1;
      BEreq::FHHiggsProd(error, sqrts, prodxs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsProd raised error flag for LHC8: " << error << ".";
        invalid_point().raise(err.str());
      }
      for(int i = 0; i < 52; i++) HiggsProd.prodxs_LHC8[i] = prodxs(i+1);

      // The ttbar production cross-sections for the (BSM,SM) model can be found at (prodxs_X[h+27], prodxs_X[h+30]),
      // where h is the higgs index (0 = h0_1, 1 = h0_2, 2 = A0) and X is one of Tev, LHC7 or LHC8.
      result = HiggsProd;

    }

    void THDM_ModelParameters_effc(hb_neutral_ModelParameters_effc &result)
    {
        using namespace Pipes::THDM_ModelParameters_effc;
        const Spectrum fullspectrum = *Dep::THDM_spectrum;
        
        const THDM_couplings couplings = *Dep::fill_THDM_couplings_HB_effc; // get THDM coupling struct
        const std::vector<THDM_couplings> couplings_SM_like = *Dep::fill_THDM_couplings_HB_effc_SM_like_model; // get vector of SM-like (multiple limits) THDM coupling structs
        const THDM_decay_widths decay_widths = *Dep::fill_THDM_decay_widths_HB_effc; // get THDM decay width struct
        const std::vector<THDM_decay_widths> decay_widths_SM_like = *Dep::fill_THDM_decay_widths_HB_effc_SM_like_model; // get vector of SM-like (multiple limits) THDM decay widths
        const THDM_total_widths total_widths = *Dep::fill_THDM_total_widths; // get total widths

        // extract spectrum object
        const SubSpectrum& he = fullspectrum.get_HE();
        const SubSpectrum& SM = fullspectrum.get_LE();
        const SMInputs& sminputs = fullspectrum.get_SMInputs();

        const double MZ = SM.get(Par::Pole_Mass,"Z0"), MW = SM.get(Par::Pole_Mass,"W+"), GF = sminputs.GF;
        const double v = 1./sqrt(sqrt(2)*GF);
        const double g = 2.*MW/v;
        const double sintw = sqrt(1.-MW*MW/(MZ*MZ));
        const double costw = sqrt(1.-sintw*sintw);

        std::complex<double> c,cs,cp,c_sm,cs_sm,cp_sm;

        result.Mh[0] = he.get(Par::Pole_Mass, "h0", 1);
        result.Mh[1] = he.get(Par::Pole_Mass, "h0", 2);
        result.Mh[2] = he.get(Par::Pole_Mass, "A0");

        // set error for mh
        const bool has_high_err = he.has(Par::Pole_Mass_1srd_high, 25, 0);
        const bool has_low_err = he.has(Par::Pole_Mass_1srd_low, 25, 0);
        if (has_high_err and has_low_err) {
          const double upper = he.get(Par::Pole_Mass_1srd_high, 25, 0);
          const double lower = he.get(Par::Pole_Mass_1srd_low, 25, 0);
          result.deltaMh[0] = result.Mh[0] * std::max(upper,lower);
        }
        else {
          result.deltaMh[0] = 0.;
        }

        // set all other scalar mass errors to zero
        result.deltaMh[1] = 0.0;
        result.deltaMh[2] = 0.0;
        // set CP of the scalars
        result.CP[0] = 1;
        result.CP[1] = 1;
        result.CP[2] = -1;

        for (int h=1;h<=3;h++) {
          // get the ratio of the THDM/SM couplings
          // ghjss
          cs = couplings.hdd_cs[h][2][2];
          cp = couplings.hdd_cp[h][2][2];
          cs_sm = couplings_SM_like[h-1].hdd_cs[1][2][2];
          result.ghjss_s[h-1] = abs(cs/cs_sm);
          result.ghjss_p[h-1] = abs(cp/cs_sm);
          //ghjbb
          cs = couplings.hdd_cs[h][3][3];
          cp = couplings.hdd_cp[h][3][3];
          cs_sm = couplings_SM_like[h-1].hdd_cs[1][3][3];
          result.ghjbb_s[h-1] = abs(cs/cs_sm);
          result.ghjbb_p[h-1] = abs(cp/cs_sm);
          //ghjcc
          cs = couplings.huu_cs[h][2][2];
          cp = couplings.huu_cp[h][2][2];
          cs_sm = couplings_SM_like[h-1].huu_cs[1][2][2];
          result.ghjcc_s[h-1] = abs(cs/cs_sm);
          result.ghjcc_p[h-1] = abs(cp/cs_sm);
          //ghjtt
          cs = couplings.huu_cs[h][3][3];
          cp = couplings.huu_cp[h][3][3];
          cs_sm = couplings_SM_like[h-1].huu_cs[1][3][3];
          result.ghjtt_s[h-1] = abs(cs/cs_sm);
          result.ghjtt_p[h-1] = abs(cp/cs_sm);
          //ghjmumu
          cs = couplings.hll_cs[h][2][2];
          cp = couplings.hll_cp[h][2][2];
          cs_sm = couplings_SM_like[h-1].hll_cs[1][2][2];
          result.ghjmumu_s[h-1] = abs(cs/cs_sm);
          result.ghjmumu_p[h-1] = abs(cp/cs_sm);
          //ghjtautau
          cs = couplings.hll_cs[h][3][3];
          cp = couplings.hll_cp[h][3][3];
          cs_sm = couplings_SM_like[h-1].hll_cs[1][3][3];
          result.ghjtautau_s[h-1] = abs(cs/cs_sm);
          result.ghjtautau_p[h-1] = abs(cp/cs_sm);  
          //ghjZZ
          c = couplings.vvh[2][2][h];
          c_sm = couplings_SM_like[h-1].vvh[2][2][1];
          result.ghjZZ[h-1] = abs(c/c_sm);    
          //ghjWW
          c = couplings.vvh[3][3][h];
          c_sm = couplings_SM_like[h-1].vvh[3][3][1];
          result.ghjWW[h-1] = abs(c/c_sm);
          //ghjgaga
          double hgaga = decay_widths.gamma_hgaga[h];
          double hgaga_sm = decay_widths_SM_like[h-1].gamma_hgaga[1];
          result.ghjgaga[h-1] = hgaga/hgaga_sm;
          //ghjZga
          double hZga = decay_widths.gamma_hZga[h];
          double hZga_sm = decay_widths_SM_like[h-1].gamma_hZga[1];
          result.ghjZga[h-1] = hZga/hZga_sm;
          //ghjhh
          double hgg = decay_widths.gamma_hgg[h];
          double hgg_sm = decay_widths_SM_like[h-1].gamma_hgg[1];
          result.ghjgg[h-1] = hgg/hgg_sm;
          result.ghjggZ[h-1] = 0.;
          // Total width
          result.hGammaTot[h-1] = total_widths.gamma_tot_h[h];
    
          #ifdef COLLIDERBIT_DEBUG
            printf("%2d %5s %16.8E %16.8E\n", h, "ss", result.ghjss_s[h-1], result.ghjss_p[h-1]);
            printf("%2d %5s %16.8E %16.8E\n", h, "bb", result.ghjbb_s[h-1], result.ghjbb_p[h-1]);
            printf("%2d %5s %16.8E %16.8E\n", h, "cc", result.ghjcc_s[h-1], result.ghjcc_p[h-1]);
            printf("%2d %5s %16.8E %16.8E\n", h, "tt", result.ghjtt_s[h-1], result.ghjtt_p[h-1]);
            printf("%2d %5s %16.8E %16.8E\n", h, "mumu", result.ghjmumu_s[h - 1], result.ghjmumu_p[h - 1]);
            printf("%2d %5s %16.8E %16.8E\n", h, "tata", result.ghjtautau_s[h-1], result.ghjtautau_p[h-1]);
            printf("%2d %5s %16.8E\n", h, "ZZ", result.ghjZZ[h-1]);
            printf("%2d %5s %16.8E\n", h, "WW", result.ghjWW[h-1]);
            printf("%2d %5s %16.8E\n", h, "gaga", result.ghjgaga[h-1]);
            printf("%2d %5s %16.8E\n", h, "Zga", result.ghjZga[h-1]);
            printf("%2d %5s %16.8E\n", h, "gg", result.ghjgg[h-1]);
          #endif
        }

        // ghjhiZ
        for (int j=1;j<=3;j++) {
          for (int i=1;i<=3;i++) {
            result.BR_hjhihi[i-1][j-1] = decay_widths.gamma_hhh[j][i][i]/result.hGammaTot[j-1];
            c = couplings.vhh[2][j][i];
            result.ghjhiZ[i-1][j-1] = abs(c)/(g/2./costw);
            #ifdef COLLIDERBIT_DEBUG
              printf("%2d %2d hihjZ %16.8E\n", j, i, result.ghjhiZ[i-1][j-1]);
              printf("%2d %2d hj->hihi %16.8E\n", j, i, result.BR_hjhihi[i-1][j-1]);
            #endif
          }
        }
    }

    void THDM_ModelParameters_charged(hb_charged_ModelParameters &result) {
        using namespace Pipes::THDM_ModelParameters_charged;
        const Spectrum fullspectrum = *Dep::THDM_spectrum;

        // extract spectrum object
        const SubSpectrum& he = fullspectrum.get_HE();

        const THDM_decay_widths decay_widths = *Dep::fill_THDM_decay_widths_HB; // get THDM decay width struct
        const THDM_total_widths total_widths = *Dep::fill_THDM_total_widths; // get total widths

        result.MHplus[0] = he.get(Par::Pole_Mass,"H+");
        result.deltaMHplus[0] = 0.0;

        result.CS_lep_HpjHmi_ratio[0] = 1.;
        const double gammatot_top = total_widths.gamma_tot_t;
        const double gammatot_top_SM = total_widths.gamma_tot_t_SM_contrib;
        const double gammatot_Hc = total_widths.gamma_tot_h[4];

        result.HpGammaTot[0] = gammatot_Hc;
        result.BR_tWpb = gammatot_top_SM/gammatot_top;
        result.BR_tHpjb[0] = decay_widths.gamma_uhd[3][4][3]/gammatot_top;
        result.BR_Hpjcs[0] = decay_widths.gamma_hdu[4][2][2]/gammatot_Hc;
        result.BR_Hpjcb[0] = decay_widths.gamma_hdu[4][3][2]/gammatot_Hc;
        result.BR_Hptaunu[0] = decay_widths.gamma_hln[4][3][3]/gammatot_Hc;

        #ifdef COLLIDERBIT_DEBUG
          printf("4 %5s %16.8E\n", "tW", result.BR_tWpb);
          printf("4 %5s %16.8E\n", "tHpj", result.BR_tHpjb[0]);
          printf("4 %5s %16.8E\n", "Hpjcs", result.BR_Hpjcs[0]);
          printf("4 %5s %16.8E\n", "Hpjcb", result.BR_Hpjcb[0]);
          printf("4 %5s %16.8E\n", "BR_Hptaunu", result.BR_Hptaunu[0]);
        #endif

        // extra HB v5 beta input
        result.BR_Hpjtb[0] = decay_widths.gamma_huu[4][3][3]/gammatot_Hc;
        result.BR_HpjWZ[0] = 0.0; // TODO

         for (int h=1;h<=3;h++) {
          result.BR_HpjhiW[h] = decay_widths.gamma_hvh[4][3][h]/gammatot_Hc;
         }
        
    }

    void THDM_ModelParameters(hb_neutral_ModelParameters_part &result)
    {
      using namespace Pipes::THDM_ModelParameters;
      const Spectrum fullspectrum = *Dep::THDM_spectrum;

      const THDM_couplings couplings = *Dep::fill_THDM_couplings_HB; // get THDM coupling struct
      const std::vector<THDM_couplings> couplings_SM_like = *Dep::fill_THDM_couplings_HB_SM_like_model; // get vector of SM-like (multiple limits) THDM coupling structs
      const THDM_decay_widths decay_widths = *Dep::fill_THDM_decay_widths_HB; // get THDM decay width struct
      const std::vector<THDM_decay_widths> decay_widths_SM_like = *Dep::fill_THDM_decay_widths_HB_SM_like_model; // get vector of SM-like (multiple limits) THDM decay widths
      const THDM_total_widths total_widths = *Dep::fill_THDM_total_widths; // get total widths

      // extract spectrum object
      const SubSpectrum& he = fullspectrum.get_HE();
      const SubSpectrum& SM = fullspectrum.get_LE();
      const SMInputs& sminputs = fullspectrum.get_SMInputs();

      const double RWW = 0.77; 
      const double RZZ = 1.0-RWW;
      const double MZ = SM.get(Par::Pole_Mass,"Z0"), MW = SM.get(Par::Pole_Mass,"W+"), GF = sminputs.GF;
      const double v = 1./sqrt(sqrt(2)*GF);
      const double g = 2.*MW/v;
      const double sintw = sqrt(1.-MW*MW/(MZ*MZ));
      const double costw = sqrt(1.-sintw*sintw);

      // declare couplings
      std::complex <double> c,cs,cp,cs_sm,cp_sm,cst,cpt,cst_sm,cpt_sm;

      // fill scalar masses (at Pole)
      result.Mh[0] = he.get(Par::Pole_Mass, "h0", 1);
      result.Mh[1] = he.get(Par::Pole_Mass, "h0", 2);
      result.Mh[2] = he.get(Par::Pole_Mass,"A0");

      // set error for mh
      const bool has_high_err = he.has(Par::Pole_Mass_1srd_high, 25, 0);
      const bool has_low_err = he.has(Par::Pole_Mass_1srd_low, 25, 0);
      if (has_high_err and has_low_err) {
        const double upper = he.get(Par::Pole_Mass_1srd_high, 25, 0);
        const double lower = he.get(Par::Pole_Mass_1srd_low, 25, 0);
        result.deltaMh[0] = result.Mh[0] * std::max(upper,lower);
      }
      else {
        result.deltaMh[0] = 0.;
      }

      // set all other scalar mass errors to zero
      result.deltaMh[1] = 0.0;
      result.deltaMh[2] = 0.0;

      // set CP of the scalars
      result.CP[0] = 1;
      result.CP[1] = 1;
      result.CP[2] = -1;

      // cycle over neutral scalars & fill HB input
      for (int h=0; h<3; h++) {
        const double gamma_h = total_widths.gamma_tot_h[h+1];
        result.hGammaTot[h] = gamma_h;
        result.BR_hjss[h] = decay_widths.gamma_hdd[h+1][2][2]/gamma_h;
        result.BR_hjcc[h] = decay_widths.gamma_huu[h+1][2][2]/gamma_h;
        result.BR_hjbb[h] = decay_widths.gamma_hdd[h+1][3][3]/gamma_h;
        result.BR_hjtautau[h] = decay_widths.gamma_hll[h+1][3][3]/gamma_h;
        result.BR_hjmumu[h] = decay_widths.gamma_hll[h+1][2][2]/gamma_h;
        result.BR_hjWW[h] = decay_widths.gamma_hvv[h+1][3]/gamma_h;
        result.BR_hjZZ[h] = decay_widths.gamma_hvv[h+1][2]/gamma_h;
        result.BR_hjZga[h] = decay_widths.gamma_hZga[h+1]/gamma_h;
        result.BR_hjgg[h] = decay_widths.gamma_hgg[h+1]/gamma_h;
        result.BR_hjgaga[h] = decay_widths.gamma_hgaga[h+1]/gamma_h;

        // multi higgs couplings
        for (int h2=0; h2<3; h2++) {

          result.BR_hjhihi[h2][h] = decay_widths.gamma_hhh[h+1][h2+1][h2+1]/gamma_h;

          // sets invisible branching 
          if(result.hGammaTot[h2+1]==0) {
            result.BR_hjinvisible[h] = result.BR_hjhihi[h2][h];
          }
          else{ 
            result.BR_hjinvisible[h] = 0; 
          }

          c = couplings.vhh[2][h2+1][h+1];
          result.CS_lep_hjhi_ratio[h][h2] = pow(abs(c)/(g/2./costw),2);
        }

        c = couplings.vvh[2][2][h+1];
        const double CS_lep_hjz_ratio = pow(abs(c)/(g/costw*MZ),2);
        result.CS_lep_hjZ_ratio[h]= CS_lep_hjz_ratio;
        result.CS_dd_hjZ_ratio[h] = CS_lep_hjz_ratio;
        result.CS_uu_hjZ_ratio[h] = CS_lep_hjz_ratio;
        result.CS_ss_hjZ_ratio[h] = CS_lep_hjz_ratio;
        result.CS_cc_hjZ_ratio[h] = CS_lep_hjz_ratio;
        result.CS_bb_hjZ_ratio[h] = CS_lep_hjz_ratio;
        result.CS_gg_hjZ_ratio[h] = 0.0;

        c = couplings.vvh[3][3][h+1];
        const double CS_ud_hjWp_ratio = pow(abs(c)/(g*MW),2);
        result.CS_ud_hjWp_ratio[h] = CS_ud_hjWp_ratio;
        result.CS_ud_hjWm_ratio[h] = CS_ud_hjWp_ratio;
        result.CS_cs_hjWp_ratio[h] = CS_ud_hjWp_ratio;
        result.CS_cs_hjWm_ratio[h] = CS_ud_hjWp_ratio;

        result.CS_gg_hj_ratio[h] = decay_widths.gamma_hgg[h+1]/decay_widths_SM_like[h].gamma_hgg[1];

        cs = couplings.hdd_cs[h+1][3][3];
        cp = couplings.hdd_cp[h+1][3][3];
        cs_sm = couplings_SM_like[h].hdd_cs[1][3][3];
        cp_sm = couplings_SM_like[h].hdd_cp[1][3][3];

        const double CS_bb_hj_ratio = pow(abs(cs/cs_sm),2) + pow(abs(cp/cs_sm),2);
        result.CS_bb_hj_ratio[h] = CS_bb_hj_ratio;
        result.CS_bg_hjb_ratio[h] = CS_bb_hj_ratio;
        result.CS_lep_bbhj_ratio[h] = CS_bb_hj_ratio;

        result.CS_lep_tautauhj_ratio[h] = decay_widths.gamma_hll[h+1][3][3]/decay_widths_SM_like[h].gamma_hll[1][3][3];

        cst = couplings.huu_cs[h+1][3][3];
        cpt = couplings.huu_cp[h+1][3][3];
        cst_sm = couplings_SM_like[h].huu_cs[1][3][3];
        cpt_sm = couplings_SM_like[h].huu_cp[1][3][3];

        const double CS_tev_vbf_ratio = RWW*CS_ud_hjWp_ratio + RZZ*CS_lep_hjz_ratio;
        result.CS_tev_vbf_ratio[h] = CS_tev_vbf_ratio;

        const double CS_tev_tthj_ratio = pow(abs(cst/cst_sm),2)+pow(abs(cpt/cst_sm),2);
        result.CS_tev_tthj_ratio[h] = CS_tev_tthj_ratio;

        result.CS_lhc7_vbf_ratio[h] = CS_tev_vbf_ratio;
        result.CS_lhc8_vbf_ratio[h] = CS_tev_vbf_ratio;
        result.CS_lhc7_tthj_ratio[h] = CS_tev_tthj_ratio;
        result.CS_lhc8_tthj_ratio[h] = CS_tev_tthj_ratio;
      }
    }

    // Higgs mass likelihood
    void SM_higgs_mass_likelihood(double &result) {
      using namespace Pipes::SM_higgs_mass_likelihood;
      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      const double mh_pole = fullspectrum.get(Par::Pole_Mass, "h0", 1); // Higgs boson mass - GeV
      const double massSMHiggs = 125.09, h_sigma = 0.32;
      // calculate the likelihood
      result = - pow( (mh_pole - massSMHiggs) / h_sigma,2);
    }

    // Higgs width likelihood
    void SM_higgs_width_likelihood(double &result) {
      using namespace Pipes::SM_higgs_width_likelihood;
      const THDM_total_widths total_widths = *Dep::fill_THDM_total_widths;
      const double gamma_h = total_widths.gamma_tot_h[1];
      // Full width bound from 1605.02329
      const double gamma_h_bound = 0.015, gamma_h_sigma = 0.001; // (GeV)
      // calculate the likelihood
      if ( gamma_h > gamma_h_bound ) result = - pow( (gamma_h - gamma_h_bound) / gamma_h_sigma,2);
      else result = 0.;
    }

  }
}
