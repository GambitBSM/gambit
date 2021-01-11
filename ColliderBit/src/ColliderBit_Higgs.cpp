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
///  \author Ankit Beniwal
///          (ankit.beniwal@uclouvain.be)
///  \date 2020 Jul
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
#include <complex>

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

        result.CS_lep_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_gg_hjZ_ratio[i] = 0.;
        result.CS_dd_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_uu_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_ss_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_cc_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_bb_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);

        result.CS_ud_hjWp_ratio[i] = pow(couplings.C_WW[i],2);
        result.CS_cs_hjWp_ratio[i] = pow(couplings.C_WW[i],2);
        result.CS_ud_hjWm_ratio[i] = pow(couplings.C_WW[i],2);
        result.CS_cs_hjWm_ratio[i] = pow(couplings.C_WW[i],2);

        result.CS_tev_vbf_ratio[i]  = pow(couplings.C_WW[i],2);
        result.CS_lhc7_vbf_ratio[i] = pow(couplings.C_WW[i],2);
        result.CS_lhc8_vbf_ratio[i] = pow(couplings.C_WW[i],2);

        result.CS_gg_hj_ratio[i] = couplings.C_gg2[i];

        result.CS_tev_tthj_ratio[i] = couplings.C_tt2[i];
        result.CS_lhc7_tthj_ratio[i] = couplings.C_tt2[i];
        result.CS_lhc8_tthj_ratio[i] = couplings.C_tt2[i];

        for(int j = 0; j < n_neutral_higgses; j++)
        {
          result.CS_lep_hjhi_ratio[i][j] = pow(couplings.C_hiZ[i][j],2);
        }
      }
    }

    /// Helper function to set HiggsBounds/Signals parameters cross-section ratios (HB 5 input) from a GAMBIT HiggsCouplingsTable
    void set_CS_neutral_effc(hb_neutral_ModelParameters_effc &result, const HiggsCouplingsTable& couplings, int n_neutral_higgses)
    {
      for(int i = 0; i < n_neutral_higgses; i++)
      {
          result.ghjss_s[i] = couplings.C_ss_s[i];
          result.ghjss_p[i] = couplings.C_ss_p[i];
  
          result.ghjbb_s[i] = couplings.C_bb_s[i];
          result.ghjbb_p[i] = couplings.C_bb_p[i];
  
          result.ghjcc_s[i] = couplings.C_cc_s[i];
          result.ghjcc_p[i] = couplings.C_cc_p[i];
 
          result.ghjtt_s[i] = couplings.C_tt_s[i];
          result.ghjtt_p[i] = couplings.C_tt_p[i];
 
          result.ghjmumu_s[i] = couplings.C_mumu_s[i];
          result.ghjmumu_p[i] = couplings.C_mumu_p[i];
   
          result.ghjtautau_s[i] = couplings.C_tautau_s[i];
          result.ghjtautau_p[i] = couplings.C_tautau_p[i];
         
          result.ghjZZ[i] = couplings.C_ZZ[i];    
   
          result.ghjWW[i] = couplings.C_WW[i];
  
          result.ghjgaga[i] = sqrt(couplings.C_gaga2[i]);
   
          result.ghjZga[i] = sqrt(couplings.C_Zga2[i]);

          result.ghjgg[i] = sqrt(couplings.C_gg2[i]);

          for(int j = 0; j < n_neutral_higgses; j++)
            result.ghjhiZ[i][j] = couplings.C_hiZ[i][j];
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

    /// MSSM Higgs neutral model parameters for HB 4
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

    // fills MSSM neutral model input for HB 5
    void MSSMHiggs_ModelParameters_effc(hb_neutral_ModelParameters_effc &result)
    {
        using namespace Pipes::MSSMHiggs_ModelParameters_effc;

        // Set up neutral Higgses
        static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

        // Set the CP of the Higgs states.
        for (int i = 0; i < 3; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

        // Retrieve higgs partial widths
        const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(3);

        // Retrieve masses
        const Spectrum& fullspectrum = *Dep::MSSM_spectrum;
        const SubSpectrum& he = fullspectrum.get_HE();

        // Neutral higgs masses and errors
        for(int i = 0; i < 3; i++)
        {
          result.Mh[i] = he.get(Par::Pole_Mass,sHneut[i]);
          bool has_high_err = he.has(Par::Pole_Mass_1srd_high,sHneut[i]);
          bool has_low_err = he.has(Par::Pole_Mass_1srd_low,sHneut[i]);
          if (has_high_err and has_low_err)
          {
            double upper = he.get(Par::Pole_Mass_1srd_high,sHneut[i]);
            double lower = he.get(Par::Pole_Mass_1srd_low,sHneut[i]);
            result.deltaMh[i] = result.Mh[i] * std::max(upper,lower);
          }
          else
          {
            result.deltaMh[i] = 0.;
          }
        }

        // fill neutral effective couplings
        set_CS_neutral_effc(result, *Dep::Higgs_Couplings, 3);
      
        for (int h=1;h<=3;h++) {
          // Total width
          result.hGammaTot[h-1] = h0_widths[h-1]->width_in_GeV;

          // Do decays to other neutral higgses
          for (int h2=1; h2<=3; h2++) {

            if (2.*result.Mh[h2-1] < result.Mh[h-1] and h0_widths[h-1]->has_channel(sHneut[h2-1],sHneut[h2-1]))
            {
              result.BR_hjhihi[h-1][h2-1] = h0_widths[h-1]->BF(sHneut[h2-1],sHneut[h2-1]);
            }
            else
            {
              result.BR_hjhihi[h-1][h2-1] = 0.;
            }

            #ifdef COLLIDERBIT_DEBUG
                std::cout << "Pole_Mass " << result.Mh[h-1]  << std::endl;
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
                printf("%2d %2d hihjZ %16.8E\n", h, h2, result.ghjhiZ[h-1][h2-1]);
                printf("%2d %2d hj->hihi %16.8E\n", h, h2, result.BR_hjhihi[h-1][h2-1]);
              #endif

          }
        }
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
      //TODO: The below needs to be replaced -- it does not exist in HiggsBounds 5.7.0
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




      // We should not have to explicitly declare the CP_value in the below function...
/*      BEreq::HiggsBounds_neutral_input_properties(&mH[0], &gamma[0], &CP_value[0]);

      BEreq::HiggsBounds_neutral_input_effC(&ghjss_s[1], &ghjss_p[0],
        &ghjcc_s[0], &ghjcc_p[0], &ghjbb_s[0],&ghjbb_p[0],
        &ghjtt_s[0], &ghjtt_p[0], &ghjmumu_s[0], &ghjmumu_p[0],
        &ghjtautau_s[0], &ghjtautau_p[0], &ghjWW[0], &ghjZZ[0],
        &ghjZga[0], &ghjgaga[0], &ghjgg[0], &ghjhiZ[0]);*/


    /// Get an LEP chisq from HiggsBounds for the CPVYukawas model using the
    /// effective coupling interface to HB/HS
    void calc_HB_LEP_LogLike_CPVYukawas(double &result)
    {
      using namespace Pipes::calc_HB_LEP_LogLike_CPVYukawas;

      int i, j, k;
      int Hneut = 1; //changed Backends/src/frontends/HiggsBounds_5_3_2beta.cpp so that only one neutral Higgs and no charged Higgs exist
      double mH[Hneut], gamma[Hneut], CP_value[Hneut];
      const HiggsCouplingsTable::h0_decay_array_type&
        h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(1);
      //double mH[1] = *Param["mH"];
      
      //HiggsBounds only returns chisq values for mH up to 120GeV seemingly no matter the couplings input
      mH[0] = 125.; // Higgs mass
      gamma[0] = h0_widths[0]->width_in_GeV;
//      cout << "gamma[0]: " << gamma[0] << endl;
      //gamma[0] = 0.1;
      CP_value[0] = 0.; // Mixed CP state

      double ghjss_s[Hneut], ghjss_p[Hneut], ghjcc_s[Hneut], ghjcc_p[Hneut],
        ghjbb_s[Hneut], ghjbb_p[Hneut], ghjtt_s[Hneut], ghjtt_p[Hneut],
        ghjmumu_s[Hneut], ghjmumu_p[Hneut], ghjtautau_s[Hneut], ghjtautau_p[Hneut],
        ghjWW[Hneut], ghjZZ[Hneut], ghjZga[Hneut], ghjgaga[Hneut], ghjgg[Hneut],
        ghjhiZ[Hneut];
      double BR_hjinvisible[Hneut], BR_hjemu[Hneut], BR_hjetau[Hneut],
        BR_hjmutau[Hneut], BR_hjHpiW[Hneut];
      Farray<double, 1,3, 1,3> BR_hjhiZ;
      Farray<double, 1,3, 1,3, 1,3> BR_hkhjhi;

      //chisq is very sensitve to ghjbb. When it goes slightly beyond 1 the maximum chisq value is reached. The others on the other hand have no apparent impact
      double kappaS = *Param["kappaS"];
      double kappaC = *Param["kappaC"];
      double kappaB = *Param["kappaB"];
      double kappaT = *Param["kappaT"];
      double kappaMu = *Param["kappaMu"];
      double kappaTau = *Param["kappaTau"];
      double sinPhiS = *Param["SinPhiS"];
      double sinPhiC = *Param["SinPhiC"];
      double sinPhiB = *Param["SinPhiB"];
      double sinPhiT = *Param["SinPhiT"];
      double sinPhiMu = *Param["SinPhiMu"];
      double sinPhiTau = *Param["SinPhiTau"];

      for(int i = 0; i<Hneut; i++){
      ghjss_p[i] = kappaS*sinPhiS;
      ghjss_s[i] = kappaS*sqrt(1. - pow(sinPhiS,2));
      ghjcc_p[i] = kappaC*sinPhiC;
      ghjcc_s[i] = kappaC*sqrt(1. - pow(sinPhiC,2));
      ghjbb_p[i] = kappaB*sinPhiB;
      ghjbb_s[i] = kappaB*sqrt(1. - pow(sinPhiB,2));
      ghjtt_p[i] = kappaT*sinPhiT;
      ghjtt_s[i] = kappaT*sqrt(1. - pow(sinPhiT,2));
      ghjmumu_p[i] = kappaMu*sinPhiMu;
      ghjmumu_s[i] = kappaMu*sqrt(1. - pow(sinPhiMu,2));
      ghjtautau_p[i] = kappaTau*sinPhiTau;
      ghjtautau_s[i] = kappaTau*sqrt(1. - pow(sinPhiTau,2));

      // hVV
      ghjWW[i]=0.;
      ghjZZ[i]=0.;
      ghjZga[i]=0.; // h-Z-photon (change?)
      ghjgaga[i]=0.; // h-photon-photon (change?)
      ghjgg[i]=0.; // h-gluon-gluon (change?)
      ghjhiZ[i]=0.; // h-h-Z - isn't it =1.?
      }
      cout << "couplings: bbp,bbs " << ghjbb_p[0] << " " << ghjbb_s[0] << endl;



/*	mH[i] = 112.0;
	gamma[i] = 2.988E-3; //directly used from hb532 with mH = 112
      CP_value[i] = 0.; // Mixed CP state
*/

      // All non-SM branchings are zero in this model

      for (i=0; i<=2; i++)
      {
        BR_hjinvisible[i] = BR_hjemu[i] = BR_hjetau[i] = 0.;
        BR_hjmutau[i] = BR_hjHpiW[i] = 0.;
        for (j=1; j<=3; j++)
        {
          BR_hjhiZ(i+1,j) = 0.;
          for (k=1; k<=3; k++)
          {
              BR_hkhjhi(i+1,j,k) = 0.;
          }
        }
      }

//      BEreq::HiggsBounds_neutral_input_properties(&mH[0], &gamma[0], &CP_value[0]);
//     cout << "mh" << mH[0] <<"gamma"<< gamma[0] <<"CP"<< CP_value[0] << endl;
//    cout << "hb_neutral_input_prop called";
      BEreq::HiggsBounds_neutral_input_properties(&mH[0], &gamma[0], &CP_value[0]);
//     cout << "hb_neutral_input_prop done";
      BEreq::HiggsBounds_neutral_input_effC(&ghjss_s[0], &ghjss_p[0],
        &ghjcc_s[0], &ghjcc_p[0], &ghjbb_s[0], &ghjbb_p[0],
        &ghjtt_s[0], &ghjtt_p[0], &ghjmumu_s[0], &ghjmumu_p[0],
        &ghjtautau_s[0], &ghjtautau_p[0], &ghjWW[0], &ghjZZ[0],
        &ghjZga[0], &ghjgaga[0], &ghjgg[0], &ghjhiZ[0]);


      BEreq::HiggsBounds_neutral_input_nonSMBR(&BR_hjinvisible[0],
        BR_hkhjhi, BR_hjhiZ, &BR_hjemu[0], &BR_hjetau[0], &BR_hjmutau[0],
        &BR_hjHpiW[0]);

      //BEreq::HiggsBounds_set_mass_uncertainties(&ModelParam.deltaMh[0],&ModelParam.deltaMHplus[0]);

      // run Higgs bounds 'classic'
      double obsratio;
      int HBresult, chan, ncombined;
//      cout << "run HB classic. HBresult, obsratio, chan, ncombined: " << HBresult << " " << obsratio << " " << chan << " " << ncombined << endl;
      BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);
//      cout << "finished HBclassic run. HBresult, obsratio, chan, ncombined: " << HBresult << " " << obsratio << " " << chan << " " << ncombined<< endl;
      // extract the LEP chisq
      double chisq_withouttheory=0.1,chisq_withtheory=0.1;
      int chan2;
//      cout << "chisq withouttheory before" << chisq_withouttheory << chisq_withtheory << endl;
      double theor_unc = 1.5; // theory uncertainty
      BEreq::HB_calc_stats(theor_unc,chisq_withouttheory,chisq_withtheory,chan2); 
//      cout << "chisq withouttheory after" << chisq_withouttheory << chisq_withtheory << endl;

      // Catch HiggsBound's error value, chisq = -999
      if( fabs(chisq_withouttheory - (-999.)) < 1e-6)
      {
        ColliderBit_warning().raise(LOCAL_INFO, "Got chisq=-999 from HB_calc_stats in HiggsBounds, indicating a cross-section outside tabulated range. Will use chisq=0.");
        chisq_withouttheory = 0.0;
      }

      result = -0.5*chisq_withouttheory;
    }

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


    //loop functions for effective hBB couplings for photon pair, gluon pair and photon-Z-Boson
    std::complex<double> Aloop(double tau){
	return 3.*tau/2. * (1.+(1-tau)*pow(atan(1./sqrt(std::complex<double>(tau-1))),2));
    }	   
    std::complex<double> Bloop(double tau){
	return (tau*pow(atan(1./sqrt(std::complex<double>(tau-1))),2));
    }	   
    static std::complex<double> weakLoopConstant;
    static std::complex<double> CPevenKapPreGam[9];
    static std::complex<double> CPoddKapPreGam[9];
    static std::complex<double> CPevenKapPreGlu[6];
    static std::complex<double> CPoddKapPreGlu[6];
    void initialize(){
	static bool first = true;
	if(first){
		double me = 0.0005109989461;
		double mmu = 0.1056583745;
		double mtau = 1.77686;
		double mu = 0.00138818972836;
		double md = 0.00300132208045;
		double ms = 0.0597702783098;
		double mc = 0.750440223951;
		double mb = 3.00584732405;
		double mt = 166.394;
		double fmasses[] = {me,mmu,mtau,mu,md,ms,mc,mb,mt}; //fermionmasses at Mz
		double fcharges[] = {-1.,-1.,-1.,2/3.,-1/3.,-1/3.,2/3.,-1/3.,2/3.}; //electrical charges
		double fNcs[] = {1.,1.,1.,3.,3.,3.,3.,3.,3.}; //number of colors
		double fisq[] = {0.,0.,0.,1.,1.,1.,1.,1.,1.}; //is fermion a quark?
		double Mh = 125.1;
		double Mz = 91.1876;
		double Mw = 80.379;
		double tauw = 4*pow(Mw/Mh,2);
		std::complex<double> AW = -1/8.*(2+3*tauw + 3*tauw*(2-tauw)*pow(atan(1./sqrt(tauw-1)),2));
		std::complex<double> dengam = AW;
		std::complex<double> denglu = 0.0;
		for(int i = 0; i<9; i++) { 
			dengam += 1/6.*pow(fcharges[i],2) * fNcs[i] * Aloop(pow(fmasses[i]/Mh,2)); 
			denglu += Aloop(pow(fmasses[i]/Mh,2))*fisq[i]; 
		}
		for(int i = 0; i<9; i++){
			CPevenKapPreGam[i] = 1./dengam * 1./6. * pow(fcharges[i],2) * fNcs[i] * Aloop(pow(fmasses[i]/Mh,2));
			CPoddKapPreGam[i] = 1./dengam * 1./4. * pow(fcharges[i],2) * fNcs[i] * Bloop(pow(fmasses[i]/Mh,2));
			CPevenKapPreGlu[i] = 1./denglu * fisq[i] * Aloop(pow(fmasses[i]/Mh,2));
			CPoddKapPreGlu[i] = 1./denglu * 3./2. *fisq[i] * Bloop(pow(fmasses[i]/Mh,2));
			cout << "Aloop " << Aloop(pow(fmasses[i]/Mh,2)) << endl;
			cout << "Bloop " << Bloop(pow(fmasses[i]/Mh,2)) << endl;
		}
		weakLoopConstant = AW/dengam;
		first = false;
	}
	return;
    }	 




    /// Get an LHC chisq from HiggsBounds for the CPVYukawas model using the
    /// effective coupling interface to HB/HS
    void calc_HS_LHC_LogLike_CPVYukawas(double &result)
    {
      using namespace Pipes::calc_HS_LHC_LogLike_CPVYukawas;

//      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
//      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      Farray<double, 1,3, 1,3> ghjhiZ;
      Farray<double, 1,3> BR_HpjhiW;
      for(int i = 0; i < 3; i++) 
      {
//        BR_HpjhiW(i+1) = ModelParam_charged.BR_HpjhiW[i];
        BR_HpjhiW(i+1) = 0.;
        for(int j = 0; j < 3; j++) {
          ghjhiZ(i+1,j+1) = 0;//ModelParam.ghjhiZ[i][j];
        }
      }
      int Hneut = 1;
      double Mh[Hneut];
      Mh[0] = 125.09;
      double GammaTot[Hneut];
      double CP[Hneut];
      CP[0] = 0.;
      //const HiggsCouplingsTable::h0_decay_array_type&  h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(1);
      GammaTot[0] = 4.08E-3; //taken from HS //h0_widths[0]->width_in_GeV;


      double ghjuu_s[Hneut], ghjuu_p[Hneut],ghjdd_s[Hneut], ghjdd_p[Hneut],ghjee_s[Hneut], ghjee_p[Hneut],
      	ghjss_s[Hneut], ghjss_p[Hneut], ghjcc_s[Hneut], ghjcc_p[Hneut],
        ghjbb_s[Hneut], ghjbb_p[Hneut], ghjtt_s[Hneut], ghjtt_p[Hneut],
        ghjmumu_s[Hneut], ghjmumu_p[Hneut], ghjtautau_s[Hneut], ghjtautau_p[Hneut],
        ghjWW[Hneut], ghjZZ[Hneut], ghjZga[Hneut], ghjgaga[Hneut], ghjgg[Hneut];

      double gf = Dep::SMINPUTS->GF;
      double vev = 1/sqrt(sqrt(2.)*gf);
      double Lambda = 1000.;
      double mu = Dep::SMINPUTS->mU;
      double md = Dep::SMINPUTS->mD;
      double ms = Dep::SMINPUTS->mS;
      double mc = Dep::SMINPUTS->mCmC;
      double mb = Dep::SMINPUTS->mBmB;
      double mt = Dep::SMINPUTS->mT;
      double me = Dep::SMINPUTS->mE;
      double mmu = Dep::SMINPUTS->mMu;
      double mtau = Dep::SMINPUTS->mTau;

      // The WCs are normalized to C*v^2/Lambda^2
      double sinThU = *Param["CuHm"]*vev/mu/2./sqrt(2.); //*vev*vev/Lambda/Lambda
      double sinThD = *Param["CdHm"]*vev/md/2./sqrt(2.);
      double sinThS = *Param["CsHm"]*vev/ms/2./sqrt(2.);
      double sinThC = *Param["CcHm"]*vev/mc/2./sqrt(2.);
      double sinThB = *Param["CbHm"]*vev/mb/2./sqrt(2.);
      double sinThT = *Param["CtHm"]*vev/mt/2./sqrt(2.);
      double sinThE = *Param["CeHm"]*vev/me/2./sqrt(2.);
      double sinThMu = *Param["CmuHm"]*vev/mmu/2./sqrt(2.);
      double sinThTau = *Param["CtauHm"]*vev/mtau/2./sqrt(2.);
 
      double cosThU = sqrt(1. - pow(sinThU,2));
      double cosThD = sqrt(1. - pow(sinThD,2));
      double cosThS = sqrt(1. - pow(sinThS,2));
      double cosThC = sqrt(1. - pow(sinThC,2));
      double cosThB = sqrt(1. - pow(sinThB,2));
      double cosThT = sqrt(1. - pow(sinThT,2));
      double cosThE = sqrt(1. - pow(sinThE,2));
      double cosThMu = sqrt(1. - pow(sinThMu,2));
      double cosThTau = sqrt(1. - pow(sinThTau,2));

      //kappa_gamma - W-boson loop

      initialize();

      for(int i = 0; i<Hneut; i++){
	      ghjuu_p[i] = -((*Param["CuHm"])*cosThU + (*Param["CuHp"])*sinThU)*vev/mu/2./sqrt(2.);//*vev*vev/Lambda/Lambda
	      ghjuu_s[i] = 1.+((*Param["CuHm"])*sinThU - (*Param["CuHp"])*cosThU)*vev/mu/2./sqrt(2.);
	      ghjdd_p[i] = -((*Param["CdHm"])*cosThD + (*Param["CdHp"])*sinThD)*vev/md/2./sqrt(2.);//*vev*vev/Lambda/Lambda
	      ghjdd_s[i] = 1.+((*Param["CdHm"])*sinThD - (*Param["CdHp"])*cosThD)*vev/md/2./sqrt(2.);
	      ghjee_p[i] = -((*Param["CeHm"])*cosThE + (*Param["CeHp"])*sinThE)*vev/me/2./sqrt(2.);//*vev*vev/Lambda/Lambda
	      ghjee_s[i] = 1.+((*Param["CeHm"])*sinThE - (*Param["CeHp"])*cosThE)*vev/me/2./sqrt(2.);
	
	      ghjss_p[i] = -((*Param["CsHm"])*cosThS + (*Param["CsHp"])*sinThS)*vev/ms/2./sqrt(2.);//*vev*vev/Lambda/Lambda
	      ghjss_s[i] = 1.+((*Param["CsHm"])*sinThS - (*Param["CsHp"])*cosThS)*vev/ms/2./sqrt(2.);
	      ghjcc_p[i] = -((*Param["CcHm"])*cosThC + (*Param["CcHp"])*sinThC)*vev/mc/2./sqrt(2.);
	      ghjcc_s[i] = 1.+((*Param["CcHm"])*sinThC - (*Param["CcHp"])*cosThC)*vev/mc/2./sqrt(2.);
	      ghjbb_p[i] = -((*Param["CbHm"])*cosThB + (*Param["CbHp"])*sinThB)*vev/mb/2./sqrt(2.);
	      ghjbb_s[i] = 1.+((*Param["CbHm"])*sinThB - (*Param["CbHp"])*cosThB)*vev/mb/2./sqrt(2.);
	      ghjtt_p[i] = -((*Param["CtHm"])*cosThT + (*Param["CtHp"])*sinThT)*vev/mt/2./sqrt(2.);
	      ghjtt_s[i] = 1.+((*Param["CtHm"])*sinThT - (*Param["CtHp"])*cosThT)*vev/mt/2./sqrt(2.);
	      ghjmumu_p[i] = -((*Param["CmuHm"])*cosThMu + (*Param["CmuHp"])*sinThMu)*vev/mmu/2./sqrt(2.);
	      ghjmumu_s[i] = 1.+((*Param["CmuHm"])*sinThMu - (*Param["CmuHp"])*cosThMu)*vev/mmu/2./sqrt(2.);
	      ghjtautau_p[i] = -((*Param["CtauHm"])*sinThTau + (*Param["CtauHp"])*cosThTau)*vev/mtau/2./sqrt(2.);
	      ghjtautau_s[i] = 1.+((*Param["CtauHm"])*cosThTau - (*Param["CtauHp"])*sinThTau)*vev/mtau/2./sqrt(2.);
	      double WCeven[9] = {ghjee_s[i], ghjmumu_s[i], ghjtautau_s[i], ghjuu_s[i], ghjdd_s[i], ghjss_s[i], ghjcc_s[i], ghjbb_s[i], ghjtt_s[i]};
	      double WCodd[9] = {ghjee_p[i], ghjmumu_p[i], ghjtautau_p[i], ghjuu_p[i], ghjdd_p[i], ghjss_p[i], ghjcc_p[i], ghjbb_p[i], ghjtt_p[i]};
	      ghjWW[i] = 1.;
	      ghjZZ[i] = 1.;
	      ghjZga[i] = 1.;
	      std::complex<double> kapgam = weakLoopConstant;
	      std::complex<double> kaptilgam = 0.0;
	      std::complex<double> kapglu = 0.0;
	      std::complex<double> kaptilglu = 0.0;
	      for(int j = 0; j<9; j++){
		      kapgam += CPevenKapPreGam[j]*WCeven[j];
		      kaptilgam += CPoddKapPreGam[j]*WCodd[j];
		      kapglu += CPevenKapPreGlu[j]*WCeven[j];
		      kaptilglu += CPoddKapPreGlu[j]*WCodd[j];
	      }	
	      cout << "kapgam " << kapgam << endl;
	      cout << "kapgam^2 " << std::real(std::conj(kapgam)*kapgam) << endl;
	      cout << "kaptilgam " << kaptilgam << endl;
	      cout << "kaptilgam^2 " << std::real(std::conj(kaptilgam)*kaptilgam) << endl;
	      ghjgaga[i] = 0;
	      ghjgg[i] = 0;
	      cout << "gaga part1 " <<std::real(kapgam*std::conj(kapgam)) << endl;
	      cout << "gaga part2 " <<std::real(kaptilgam*std::conj(kaptilgam)) << endl;
	      cout << "combined " <<std::real(kapgam*std::conj(kapgam))+std::real(kaptilgam*std::conj(kaptilgam)) << endl;
	      cout << "sqrt " <<sqrt(std::real(kapgam*std::conj(kapgam))+std::real(kaptilgam*std::conj(kaptilgam))) << endl;
	      ghjgaga[i] += sqrt(std::real(kapgam*std::conj(kapgam)) + std::real(kaptilgam*std::conj(kaptilgam))) ;
	      ghjgg[i] += sqrt(std::real(kapglu*std::conj(kapglu)) + std::real(kaptilglu*std::conj(kaptilglu))) ;
      }
      //taken from HS
	double SMBR_HWW =  0.20956600000000017;
	double SMBR_HZZ =  2.6439400000000023E-002;
	double SMBR_Hgg =  7.8108199999999989E-002;
	double SMBR_Htt =  0.0000000000000000;
	double SMBR_Hbb = 0.58950599999999986;
	double SMBR_Htautau =  6.3346999999999987E-002;
	double SMBR_Hss =  2.4636999999999993E-004;
	double SMBR_Hcc =  2.8827999999999993E-002;
	double SMBR_HZgam =  1.5473800000000008E-003;
	double SMBR_Hmumu =  2.2445999999999995E-004;
	double SMBR_Hgamgam =  2.3094600000000002E-003;


      for(int i = 0; i<Hneut; i++){
	     GammaTot[i] = GammaTot[i] * (1. 
			     + (pow(ghjss_p[i],2) + pow(ghjss_s[i],2) - 1.)*SMBR_Hss  //HiggsSignals: ghjff_p**2 -> ghjff_p**2 * 1./(1.-4*mf**2/mh**2)
			     + (pow(ghjcc_p[i],2) + pow(ghjcc_s[i],2) - 1.)*SMBR_Hcc
			     + (pow(ghjbb_p[i],2) + pow(ghjbb_s[i],2) - 1.)*SMBR_Hbb
			     + (pow(ghjmumu_p[i],2) + pow(ghjmumu_s[i],2) - 1.)*SMBR_Hmumu
			     + (pow(ghjtautau_p[i],2) + pow(ghjtautau_s[i],2) - 1.)*SMBR_Htautau
			     + (pow(ghjZZ[i],2) - 1.)*SMBR_HZZ
			     + (pow(ghjWW[i],2) - 1.)*SMBR_HWW
			     + (pow(ghjgaga[i],2) - 1.)*SMBR_Hgamgam
			     + (pow(ghjZga[i],2) - 1.)*SMBR_HZgam
			     + (pow(ghjgg[i],2)- 1.)*SMBR_Hgg
			     );
      }

      BEreq::HiggsBounds_neutral_input_properties_HS(&Mh[0], &GammaTot[0], &CP[0]);

      BEreq::HiggsBounds_neutral_input_effC_HS(&ghjss_s[0], &ghjss_p[0],
					    &ghjcc_s[0], &ghjcc_p[0],
                                            &ghjbb_s[0], &ghjbb_p[0],
                                            &ghjtt_s[0], &ghjtt_p[0],
                                            &ghjmumu_s[0], &ghjmumu_p[0],
                                            &ghjtautau_s[0], &ghjtautau_p[0],
                                            &ghjWW[0], &ghjZZ[0], &ghjZga[0],
                                            &ghjgaga[0], &ghjgg[0],
                                            ghjhiZ);

//      BEreq::HiggsBounds_charged_input_HS(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], 
//                                        &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
//                                        &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], 
//                                        &ModelParam_charged.BR_Hpjcs[0], &ModelParam_charged.BR_Hpjcb[0], 
//                                        &ModelParam_charged.BR_Hptaunu[0], &ModelParam_charged.BR_Hpjtb[0],
//                                        &ModelParam_charged.BR_HpjWZ[0], BR_HpjhiW);
//
//      BEreq::HiggsSignals_neutral_input_MassUncertainty(&ModelParam.deltaMh[0]);

      // add uncertainties to cross-sections and branching ratios
      // double dCS[5] = {0.,0.,0.,0.,0.};
      // double dBR[5] = {0.,0.,0.,0.,0.};
      // BEreq::setup_rate_uncertainties(dCS,dBR);



      cout << "gbbs: " << ghjbb_s[0] << " gbbp: " << ghjbb_p[0] << endl;
      for(int i = 0; i<9; i++){
      cout << i << "CPegam " << CPevenKapPreGam[i] << endl;
      cout << i <<"CPogam " << CPoddKapPreGam[i] << endl;
      cout << i <<"CPeglu " << CPevenKapPreGlu[i] << endl;
      cout << i <<"CPoglu " << CPoddKapPreGlu[i] << endl;
      }
      cout << "gaga " << ghjgaga[0] << endl;
      cout << "gg " << ghjgg[0] << endl;
      cout << "GammaTot: " << GammaTot[0] << endl;


            // run HiggsSignals
//      int mode = 1; // 1- peak-centered chi2 method (recommended) - not needed in HS-2.5.0 anymore
      double csqmu, csqmh, csqtot, Pvalue;
      double csqmu1, csqmh1, csqtot1, Pvalue1;
      double csqmu2, csqmh2, csqtot2, Pvalue2;
      int nobs, nobs1, nobs2;

      // Run the main subroutines
      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);
      BEreq::run_HiggsSignals_LHC_Run1_combination(csqmu1, csqmh1, csqtot1, nobs1, Pvalue1);
      BEreq::run_HiggsSignals_STXS(csqmu2, csqmh2, csqtot2, nobs2, Pvalue2);

      result = -0.5*(csqtot + csqtot1 + csqtot2);
      cout << "csqtot: " << csqtot << "csqtot1: " << csqtot1 <<"csqtot2: " << csqtot2 <<" result: " << result << endl;
    }
      //BEreq::HiggsSignals_neutral_input_MassUncertainty(&ModelParam.deltaMh[0]);
    
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
      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);//mode, 
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
  }
}


//    void calc_HS_LHC_LogLike_CPVYukawas(double &result)
//    {
//      using namespace Pipes::calc_HS_LHC_LogLike_CPVYukawas;
//
//    // TODO: JC: Delete this?
////      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;
//      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
//      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;
//
//
//      Farray<double, 1,3, 1,3> BR_hjhiZ;
//      Farray<double, 1,3, 1,3, 1,3> BR_hkhjhi;
//
//      int i,j,k;
//
//     //TODO: JC: Delete this? These are not used anywhere.
////      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
////      Farray<double, 1,3, 1,3> BR_hjhihi;
//      
//      int Hneut = 1;
//      double Mh[Hneut];
//      Mh[0] = 125.09;
//      double GammaTotal[Hneut];
//      double CP[Hneut];
//      CP[0] = 0.;
//      //const HiggsCouplingsTable::h0_decay_array_type&  h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(1);
//      GammaTotal[0] = 4.08E-3; //taken from HS //h0_widths[0]->width_in_GeV;
//
//      double ghjss_s[Hneut], ghjss_p[Hneut], ghjcc_s[Hneut], ghjcc_p[Hneut],
//        ghjbb_s[Hneut], ghjbb_p[Hneut], ghjtt_s[Hneut], ghjtt_p[Hneut],
//        ghjmumu_s[Hneut], ghjmumu_p[Hneut], ghjtautau_s[Hneut], ghjtautau_p[Hneut],
//        ghjWW[Hneut], ghjZZ[Hneut], ghjZga[Hneut], ghjgaga[Hneut], ghjgg[Hneut];
//
//      Farray<double, 1,3, 1,3> ghjhiZ;
//      double BR_hjinvisible[Hneut], BR_hjemu[Hneut], BR_hjetau[Hneut],
//        BR_hjmutau[Hneut], BR_hjHpiW[Hneut];
//
//      // TODO: JC: Delete this? These are not used anywhere
////      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
////      {
////        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
////        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
////      }
//
//      //the following two functions are already called in Backends/src/frontends/HiggsSignals_2_2_3beta.cpp with nHneut = 1, nHplus = 0, pdf = 2 (Gaussian)
//      //initialize_HiggsSignals_LHC13(nHneut,nHplus
//      //setup_pdf(pdf=2)
//      //
//      //setup_output_level(0) only gives debug information - not called
//      //setup_Nparam(number of free model parameters = 12) not called - even though might be needed but is not listed in Backends/include/gambit/Backends/frontends/HiggsSignals_2_2_3beta.hpp
//      double gf = Dep::SMINPUTS->GF;
//      double vev = 1/sqrt(sqrt(2.)*gf);
//      double Lambda = 1000.;
//      double mu = Dep::SMINPUTS->mU;
//      double md = Dep::SMINPUTS->mD;
//      double ms = Dep::SMINPUTS->mS;
//      double mc = Dep::SMINPUTS->mCmC;
//      double mb = Dep::SMINPUTS->mBmB;
//      double mt = Dep::SMINPUTS->mT;
//      double mmu = Dep::SMINPUTS->mMu;
//      double mtau = Dep::SMINPUTS->mTau;
//
//      double sinThU = *Param["CuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mu;
//      double sinThD = *Param["CdHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/md;
//      double sinThS = *Param["CsHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/ms;
//      double sinThC = *Param["CcHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mc;
//      double sinThB = *Param["CbHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mb;
//      double sinThT = *Param["CtHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mt;
//      double sinThMu = *Param["CmuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mmu;
//      double sinThTau = *Param["CtauHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mtau;
// 
//      double cosThU = sqrt(1. - pow(sinThU,2));
//      double cosThD = sqrt(1. - pow(sinThD,2));
//      double cosThS = sqrt(1. - pow(sinThS,2));
//      double cosThC = sqrt(1. - pow(sinThC,2));
//      double cosThB = sqrt(1. - pow(sinThB,2));
//      double cosThT = sqrt(1. - pow(sinThT,2));
//      double cosThMu = sqrt(1. - pow(sinThMu,2));
//      double cosThTau = sqrt(1. - pow(sinThTau,2));
//
//
//      for(int i = 0; i<Hneut; i++){
//      ghjss_p[i] = (*Param["CsHm"])*cosThS + (*Param["CsHp"])*sinThS;
//      ghjss_s[i] = (*Param["CsHm"])*sinThS + (*Param["CsHp"])*cosThS;
//      ghjcc_p[i] = (*Param["CcHm"])*cosThC + (*Param["CcHp"])*sinThC;
//      ghjcc_s[i] = (*Param["CcHm"])*sinThC + (*Param["CcHp"])*cosThC;
//      ghjbb_p[i] = (*Param["CbHm"])*cosThB + (*Param["CbHp"])*sinThB;
//      ghjbb_s[i] = (*Param["CbHm"])*sinThB + (*Param["CbHp"])*cosThB;
//      ghjtt_p[i] = (*Param["CtHm"])*cosThT + (*Param["CtHp"])*sinThT;
//      ghjtt_s[i] = (*Param["CtHm"])*sinThT + (*Param["CtHp"])*cosThT;
//      ghjmumu_p[i] = (*Param["CmuHm"])*cosThMu + (*Param["CmuHp"])*sinThMu;
//      ghjmumu_s[i] = (*Param["CmuHm"])*sinThMu + (*Param["CmuHp"])*cosThMu;
//      ghjtautau_p[i] = (*Param["CtauHm"])*sinThTau + (*Param["CtauHp"])*cosThTau;
//      ghjtautau_s[i] = (*Param["CtauHm"])*cosThTau + (*Param["CtauHp"])*sinThTau;
//
//      // hVV
//      ghjWW[i]=1.;
//      ghjZZ[i]=1.;
//      ghjZga[i]=1.; // h-Z-photon (change?)
//      //the following numeric values are with a SM-Higgs mass. Formulae found in 1310.1385. Results than multiplied with complex conjugate.
//      ghjgaga[i] = -1.04129 
//	      /*+ 0.0000369539 *pow(kappaB,2) + 0.0000147277 *pow(kappaC,2) + 1.97566E-9 *pow(kappaMu,2) + 1.55315E-10 *pow(kappaS,2) 
//	+ 0.0782548 *pow(kappaT,2) + 0.0000237393 *pow(kappaTau,2) + 3.53719E-6 *pow(kappaB *sinPhiB,2) + 0.00931582 *kappaB *cosPhiB 
//	+ 0.0000494538 *kappaB *kappaC *sinPhiB *sinPhiC + 1.03101E-6 *pow(kappaC *sinPhiC,2) + 0.00753304 *kappaC *cosPhiC 
//	+ 0.000045367 *kappaB *kappaC *cosPhiB *cosPhiC + 5.23318E-7 *kappaB *kappaMu *sinPhiB *sinPhiMu 
//	+ 3.50135E-7 *kappaC *kappaMu *sinPhiC *sinPhiMu + 6.96949E-11 *pow(kappaMu *sinPhiMu,2) + 0.000101872 *kappaMu *cosPhiMu 
//	+ 4.79805E-7 *kappaB *kappaMu *cosPhiB *cosPhiMu + 3.31189E-7 *kappaC *kappaMu *cosPhiC *cosPhiMu 
//	+ 1.4627E-7 *kappaB *kappaS *sinPhiB *sinPhiS + 9.7998E-8 *kappaC *kappaS *sinPhiC *sinPhiS + 1.14647E-9 *kappaMu *kappaS *sinPhiMu *sinPhiS 
//	+ 5.34611E-12 *pow(kappaS *sinPhiS,2) 
//	+ 0.0000286471 *kappaS *cosPhiS + 1.34093E-7 *kappaB *kappaS *cosPhiB *cosPhiS + 9.27152E-8 *kappaC *kappaS *cosPhiC *cosPhiS 
//	+ 1.10786E-9 *kappaMu *kappaS *cosPhiMu *cosPhiS - 0.00350944 *kappaB *kappaT *sinPhiB *sinPhiT 
//	- 0.00266921 *kappaC *kappaT *sinPhiC *sinPhiT 
//	- 0.0000348837 *kappaMu *kappaT *sinPhiMu *sinPhiT - 9.80344E-6 *kappaS *kappaT *sinPhiS *sinPhiT + 0.102849 *pow(kappaT *sinPhiT,2) 
//	- 0.710205 *kappaT *cosPhiT 
//	- 0.00205295 *kappaB *kappaT *cosPhiB *cosPhiT - 0.00166008 *kappaC *kappaT *cosPhiC *cosPhiT 
//	- 0.0000224498 *kappaMu *kappaT *cosPhiMu *cosPhiT - 6.31304E-6 *kappaS *kappaT *cosPhiS *cosPhiT 
//	+ 0.0000635451 *kappaB *kappaTau *sinPhiB *sinPhiTau 
//	+ 0.000040101 *kappaC *kappaTau *sinPhiC *sinPhiTau + 4.40694E-7 *kappaMu *kappaTau *sinPhiMu *sinPhiTau 
//	+ 1.23307E-7 *kappaS *kappaTau *sinPhiS *sinPhiTau - 0.00327124 *kappaT *kappaTau *sinPhiT *sinPhiTau 
//	+ 1.82919E-6 *pow(kappaTau *sinPhiTau,2) + 0.00913359 *kappaTau *cosPhiTau + 0.0000582519 *kappaB *kappaTau *cosPhiB *cosPhiTau 
//	+ 0.0000373436 *kappaC *kappaTau *cosPhiC *cosPhiTau + 4.14361E-7 *kappaMu *kappaTau *cosPhiMu *cosPhiTau 
//	+ 1.15958E-7 *kappaS *kappaTau *cosPhiS *cosPhiTau - 0.00201279 *kappaT *kappaTau *cosPhiT *cosPhiTau*/;
//      ghjgaga[i] = sqrt(ghjgaga[i]);
//
//      ghjgg[i] =0.006290625010238506*pow((*Param["CtHm"]),2) + 0.9990252202861851*pow((*Param["CtHp"]),2) - \
//		0.000027089997790387234*(*Param["CbHm"])*(*Param["CtHm"])*cosThB + \
//		0.000891735387584407*(*Param["CbHp"])*(*Param["CtHp"])*cosThB + \
//		2.916514571639365*pow(10,-8)*pow((*Param["CbHm"]),2)*pow(cosThB,2) + \
//		1.9899197370675947*pow(10,-7)*pow((*Param["CbHp"]),2)*pow(cosThB,2) - \
//		2.4942655686159687*pow(10,-6)*(*Param["CcHm"])*(*Param["CtHm"])*cosThC + \
//		0.00008236361851064285*(*Param["CcHp"])*(*Param["CtHp"])*cosThC + \
//		5.370662583802915*pow(10,-9)*(*Param["CbHm"])*(*Param["CcHm"])*cosThB*cosThC + \
//		3.675910867115173*pow(10,-8)*(*Param["CbHp"])*(*Param["CcHp"])*cosThB*cosThC + \
//		2.4724732107927947*pow(10,-10)*pow((*Param["CcHm"]),2)*pow(cosThC,2) + \
//		1.6975961958756663*pow(10,-9)*pow((*Param["CcHp"]),2)*pow(cosThC,2) - \
//		3.371748438675548*pow(10,-11)*(*Param["CdHm"])*(*Param["CtHm"])*cosThD + \
//		1.1137469628321865*pow(10,-9)*(*Param["CdHp"])*(*Param["CtHp"])*cosThD + \
//		7.260062204057451*pow(10,-14)*(*Param["CbHm"])*(*Param["CdHm"])*cosThB*cosThD + \
//		4.970683219026287*pow(10,-13)*(*Param["CbHp"])*(*Param["CdHp"])*cosThB*cosThD + \
//		6.6845790544938286*pow(10,-15)*(*Param["CcHm"])*(*Param["CdHm"])*cosThC*cosThD + \
//		4.591086796478438*pow(10,-14)*(*Param["CcHp"])*(*Param["CdHp"])*cosThC*cosThD + \
//		4.518107308577258*pow(10,-20)*pow((*Param["CdHm"]),2)*pow(cosThD,2) + \
//		3.104106563152081*pow(10,-19)*pow((*Param["CdHp"]),2)*pow(cosThD,2) - \
//		1.3371739579187153*pow(10,-8)*(*Param["CsHm"])*(*Param["CtHm"])*cosThS + \
//		4.4169098581825755*pow(10,-7)*(*Param["CsHp"])*(*Param["CtHp"])*cosThS + \
//		2.8792083065215112*pow(10,-11)*(*Param["CbHm"])*(*Param["CsHm"])*cosThB*cosThS + \
//		1.9712789749109267*pow(10,-10)*(*Param["CbHp"])*(*Param["CsHp"])*cosThB*cosThS + \
//		2.6509821814670007*pow(10,-12)*(*Param["CcHm"])*(*Param["CsHm"])*cosThC*cosThS + \
//		1.8207382114489247*pow(10,-11)*(*Param["CcHp"])*(*Param["CsHp"])*cosThC*cosThS + \
//		3.583597971196735*pow(10,-17)*(*Param["CdHm"])*(*Param["CsHm"])*cosThD*cosThS + \
//		2.4620599359069126*pow(10,-16)*(*Param["CdHp"])*(*Param["CsHp"])*cosThD*cosThS + \
//		7.105948100649103*pow(10,-15)*pow((*Param["CsHm"]),2)*pow(cosThS,2) + \
//		4.882032079661053*pow(10,-14)*pow((*Param["CsHp"]),2)*pow(cosThS,2) - \
//		7.21321546325541*pow(10,-12)*(*Param["CtHm"])*(*Param["CuHm"])*cosThU + \
//		2.3826501258395936*pow(10,-10)*(*Param["CtHp"])*(*Param["CuHp"])*cosThU + \
//		1.553152434322002*pow(10,-14)*(*Param["CbHm"])*(*Param["CuHm"])*cosThB*cosThU + \
//		1.0633832811723*pow(10,-13)*(*Param["CbHp"])*(*Param["CuHp"])*cosThB*cosThU + \
//		1.4300387433461167*pow(10,-15)*(*Param["CcHm"])*(*Param["CuHm"])*cosThC*cosThU + \
//		9.82175835124416*pow(10,-15)*(*Param["CcHp"])*(*Param["CuHp"])*cosThC*cosThU + \
//		1.9331265125863557*pow(10,-20)*(*Param["CdHm"])*(*Param["CuHm"])*cosThD*cosThU + \
//		1.3281293040757236*pow(10,-19)*(*Param["CdHp"])*(*Param["CuHp"])*cosThD*cosThU + \
//		7.666427306208178*pow(10,-18)*(*Param["CsHm"])*(*Param["CuHm"])*cosThS*cosThU + \
//		5.267109686383153*pow(10,-17)*(*Param["CsHp"])*(*Param["CuHp"])*cosThS*cosThU + \
//		2.06777852894836*pow(10,-21)*pow((*Param["CuHm"]),2)*pow(cosThU,2) + \
//		1.420640216804829*pow(10,-20)*pow((*Param["CuHp"]),2)*pow(cosThU,2) - \
//		0.000027089997790387234*(*Param["CbHp"])*(*Param["CtHm"])*sinThB + \
//		0.000891735387584407*(*Param["CbHm"])*(*Param["CtHp"])*sinThB + \
//		4.5631423884630625*pow(10,-7)*(*Param["CbHm"])*(*Param["CbHp"])*cosThB*sinThB + \
//		5.370662583802915*pow(10,-9)*(*Param["CbHp"])*(*Param["CcHm"])*cosThC*sinThB + \
//		3.675910867115173*pow(10,-8)*(*Param["CbHm"])*(*Param["CcHp"])*cosThC*sinThB + \
//		7.260062204057451*pow(10,-14)*(*Param["CbHp"])*(*Param["CdHm"])*cosThD*sinThB + \
//		4.970683219026287*pow(10,-13)*(*Param["CbHm"])*(*Param["CdHp"])*cosThD*sinThB + \
//		2.8792083065215112*pow(10,-11)*(*Param["CbHp"])*(*Param["CsHm"])*cosThS*sinThB + \
//		1.9712789749109267*pow(10,-10)*(*Param["CbHm"])*(*Param["CsHp"])*cosThS*sinThB + \
//		1.553152434322002*pow(10,-14)*(*Param["CbHp"])*(*Param["CuHm"])*cosThU*sinThB + \
//		1.0633832811723*pow(10,-13)*(*Param["CbHm"])*(*Param["CuHp"])*cosThU*sinThB + \
//		1.9899197370675947*pow(10,-7)*pow((*Param["CbHm"]),2)*pow(sinThB,2) + \
//		2.916514571639365*pow(10,-8)*pow((*Param["CbHp"]),2)*pow(sinThB,2) - \
//		2.4942655686159687*pow(10,-6)*(*Param["CcHp"])*(*Param["CtHm"])*sinThC + \
//		0.00008236361851064285*(*Param["CcHm"])*(*Param["CtHp"])*sinThC + \
//		3.675910867115173*pow(10,-8)*(*Param["CbHp"])*(*Param["CcHm"])*cosThB*sinThC + \
//		5.370662583802915*pow(10,-9)*(*Param["CbHm"])*(*Param["CcHp"])*cosThB*sinThC + \
//		3.889687033909892*pow(10,-9)*(*Param["CcHm"])*(*Param["CcHp"])*cosThC*sinThC + \
//		6.6845790544938286*pow(10,-15)*(*Param["CcHp"])*(*Param["CdHm"])*cosThD*sinThC + \
//		4.591086796478438*pow(10,-14)*(*Param["CcHm"])*(*Param["CdHp"])*cosThD*sinThC + \
//		2.6509821814670007*pow(10,-12)*(*Param["CcHp"])*(*Param["CsHm"])*cosThS*sinThC + \
//		1.8207382114489247*pow(10,-11)*(*Param["CcHm"])*(*Param["CsHp"])*cosThS*sinThC + \
//		1.4300387433461167*pow(10,-15)*(*Param["CcHp"])*(*Param["CuHm"])*cosThU*sinThC + \
//		9.82175835124416*pow(10,-15)*(*Param["CcHm"])*(*Param["CuHp"])*cosThU*sinThC + \
//		3.675910867115173*pow(10,-8)*(*Param["CbHm"])*(*Param["CcHm"])*sinThB*sinThC + \
//		5.370662583802915*pow(10,-9)*(*Param["CbHp"])*(*Param["CcHp"])*sinThB*sinThC + \
//		1.6975961958756663*pow(10,-9)*pow((*Param["CcHm"]),2)*pow(sinThC,2) + \
//		2.4724732107927947*pow(10,-10)*pow((*Param["CcHp"]),2)*pow(sinThC,2) - \
//		3.371748438675548*pow(10,-11)*(*Param["CdHp"])*(*Param["CtHm"])*sinThD + \
//		1.1137469628321865*pow(10,-9)*(*Param["CdHm"])*(*Param["CtHp"])*sinThD + \
//		4.970683219026287*pow(10,-13)*(*Param["CbHp"])*(*Param["CdHm"])*cosThB*sinThD + \
//		7.260062204057451*pow(10,-14)*(*Param["CbHm"])*(*Param["CdHp"])*cosThB*sinThD + \
//		4.591086796478438*pow(10,-14)*(*Param["CcHp"])*(*Param["CdHm"])*cosThC*sinThD + \
//		6.6845790544938286*pow(10,-15)*(*Param["CcHm"])*(*Param["CdHp"])*cosThC*sinThD + \
//		7.111834588019614*pow(10,-19)*(*Param["CdHm"])*(*Param["CdHp"])*cosThD*sinThD + \
//		3.583597971196735*pow(10,-17)*(*Param["CdHp"])*(*Param["CsHm"])*cosThS*sinThD + \
//		2.4620599359069126*pow(10,-16)*(*Param["CdHm"])*(*Param["CsHp"])*cosThS*sinThD + \
//		1.9331265125863557*pow(10,-20)*(*Param["CdHp"])*(*Param["CuHm"])*cosThU*sinThD + \
//		1.3281293040757236*pow(10,-19)*(*Param["CdHm"])*(*Param["CuHp"])*cosThU*sinThD + \
//		4.970683219026287*pow(10,-13)*(*Param["CbHm"])*(*Param["CdHm"])*sinThB*sinThD + \
//		7.260062204057451*pow(10,-14)*(*Param["CbHp"])*(*Param["CdHp"])*sinThB*sinThD + \
//		4.591086796478438*pow(10,-14)*(*Param["CcHm"])*(*Param["CdHm"])*sinThC*sinThD + \
//		6.6845790544938286*pow(10,-15)*(*Param["CcHp"])*(*Param["CdHp"])*sinThC*sinThD + \
//		3.104106563152081*pow(10,-19)*pow((*Param["CdHm"]),2)*pow(sinThD,2) + \
//		4.518107308577258*pow(10,-20)*pow((*Param["CdHp"]),2)*pow(sinThD,2) - \
//		1.3371739579187153*pow(10,-8)*(*Param["CsHp"])*(*Param["CtHm"])*sinThS + \
//		4.4169098581825755*pow(10,-7)*(*Param["CsHm"])*(*Param["CtHp"])*sinThS + \
//		1.9712789749109267*pow(10,-10)*(*Param["CbHp"])*(*Param["CsHm"])*cosThB*sinThS + \
//		2.8792083065215112*pow(10,-11)*(*Param["CbHm"])*(*Param["CsHp"])*cosThB*sinThS + \
//		1.8207382114489247*pow(10,-11)*(*Param["CcHp"])*(*Param["CsHm"])*cosThC*sinThS + \
//		2.6509821814670007*pow(10,-12)*(*Param["CcHm"])*(*Param["CsHp"])*cosThC*sinThS + \
//		2.4620599359069126*pow(10,-16)*(*Param["CdHp"])*(*Param["CsHm"])*cosThD*sinThS + \
//		3.583597971196735*pow(10,-17)*(*Param["CdHm"])*(*Param["CsHp"])*cosThD*sinThS + \
//		1.1185253779451926*pow(10,-13)*(*Param["CsHm"])*(*Param["CsHp"])*cosThS*sinThS + \
//		7.666427306208178*pow(10,-18)*(*Param["CsHp"])*(*Param["CuHm"])*cosThU*sinThS + \
//		5.267109686383153*pow(10,-17)*(*Param["CsHm"])*(*Param["CuHp"])*cosThU*sinThS + \
//		1.9712789749109267*pow(10,-10)*(*Param["CbHm"])*(*Param["CsHm"])*sinThB*sinThS + \
//		2.8792083065215112*pow(10,-11)*(*Param["CbHp"])*(*Param["CsHp"])*sinThB*sinThS + \
//		1.8207382114489247*pow(10,-11)*(*Param["CcHm"])*(*Param["CsHm"])*sinThC*sinThS + \
//		2.6509821814670007*pow(10,-12)*(*Param["CcHp"])*(*Param["CsHp"])*sinThC*sinThS + \
//		2.4620599359069126*pow(10,-16)*(*Param["CdHm"])*(*Param["CsHm"])*sinThD*sinThS + \
//		3.583597971196735*pow(10,-17)*(*Param["CdHp"])*(*Param["CsHp"])*sinThD*sinThS + \
//		4.882032079661053*pow(10,-14)*pow((*Param["CsHm"]),2)*pow(sinThS,2) + \
//		7.105948100649103*pow(10,-15)*pow((*Param["CsHp"]),2)*pow(sinThS,2) + \
//		2.3826501258395936*pow(10,-10)*(*Param["CtHp"])*(*Param["CuHm"])*sinThU - \
//		7.21321546325541*pow(10,-12)*(*Param["CtHm"])*(*Param["CuHp"])*sinThU + \
//		1.0633832811723*pow(10,-13)*(*Param["CbHp"])*(*Param["CuHm"])*cosThB*sinThU + \
//		1.553152434322002*pow(10,-14)*(*Param["CbHm"])*(*Param["CuHp"])*cosThB*sinThU + \
//		9.82175835124416*pow(10,-15)*(*Param["CcHp"])*(*Param["CuHm"])*cosThC*sinThU + \
//		1.4300387433461167*pow(10,-15)*(*Param["CcHm"])*(*Param["CuHp"])*cosThC*sinThU + \
//		1.3281293040757236*pow(10,-19)*(*Param["CdHp"])*(*Param["CuHm"])*cosThD*sinThU + \
//		1.9331265125863557*pow(10,-20)*(*Param["CdHm"])*(*Param["CuHp"])*cosThD*sinThU + \
//		5.267109686383153*pow(10,-17)*(*Param["CsHp"])*(*Param["CuHm"])*cosThS*sinThU + \
//		7.666427306208178*pow(10,-18)*(*Param["CsHm"])*(*Param["CuHp"])*cosThS*sinThU + \
//		3.25483613939933*pow(10,-20)*(*Param["CuHm"])*(*Param["CuHp"])*cosThU*sinThU + \
//		1.0633832811723*pow(10,-13)*(*Param["CbHm"])*(*Param["CuHm"])*sinThB*sinThU + \
//		1.553152434322002*pow(10,-14)*(*Param["CbHp"])*(*Param["CuHp"])*sinThB*sinThU + \
//		9.82175835124416*pow(10,-15)*(*Param["CcHm"])*(*Param["CuHm"])*sinThC*sinThU + \
//		1.4300387433461167*pow(10,-15)*(*Param["CcHp"])*(*Param["CuHp"])*sinThC*sinThU + \
//		1.3281293040757236*pow(10,-19)*(*Param["CdHm"])*(*Param["CuHm"])*sinThD*sinThU + \
//		1.9331265125863557*pow(10,-20)*(*Param["CdHp"])*(*Param["CuHp"])*sinThD*sinThU + \
//		5.267109686383153*pow(10,-17)*(*Param["CsHm"])*(*Param["CuHm"])*sinThS*sinThU + \
//		7.666427306208178*pow(10,-18)*(*Param["CsHp"])*(*Param["CuHp"])*sinThS*sinThU + \
//		1.420640216804829*pow(10,-20)*pow((*Param["CuHm"]),2)*pow(sinThU,2) + \
//		2.06777852894836*pow(10,-21)*pow((*Param["CuHp"]),2)*pow(sinThU,2);
//
//      // h-gluon-gluon (change?)
//      ghjgg[i]=sqrt(ghjgg[i]); // h-gluon-gluon (change?)
//      ghjhiZ=0.; // h-h-Z 
//
//      cout << "gammaTotal before: " <<  GammaTotal[i] << endl;
//      GammaTotal[i] = 4.08E-3; //taken from HS //h0_widths[0]->width_in_GeV;
//      GammaTotal[i] = GammaTotal[i]* ( 1
//		/*	+ (pow(kappaS,2)-1)*2.4637E-4 +(pow(kappaC,2)-1)*2.8828E-2 +(pow(kappaB,2)-1)*5.895E-1 +(pow(kappaT,2)-1)*0E0 
//			+ (pow(kappaMu,2)-1)*2.2446E-4 +(pow(kappaTau,2)-1)*6.3347E-2 +(pow(ghjgaga[i],2)-1)*2.30946E-3 
//			+ (pow(ghjgg[i],2)-1)*7.81082E-2 + (pow(ghjWW[i],2)-1)*2.09566E-1 + (pow(ghjZZ[i],2)-1)*2.64394E-2*/
//	      	      );
//	      //how does the decay rate change in the model
//      cout << "gammaTotal after: " <<  GammaTotal[i] << endl;
//
//      }
//      for (i=0; i<=2; i++)
//      {
//        BR_hjinvisible[i] = BR_hjemu[i] = BR_hjetau[i] = 0.;
//        BR_hjmutau[i] = BR_hjHpiW[i] = 0.;
//        for (j=1; j<=3; j++)
//        {
//          BR_hjhiZ(i+1,j) = 0.;
//          for (k=1; k<=3; k++)
//          {
//              BR_hkhjhi(i+1,j,k) = 0.;
//          }
//        }
//      }
//      cout << "hgaga: " << ghjgaga[0] << endl;
//      cout << "hgg: " << ghjgg[0] << endl;
//     
//      BEreq::HiggsBounds_neutral_input_properties_HS(&Mh[0],&GammaTotal[0],&CP[0]);
//
//      BEreq::HiggsBounds_neutral_input_effC_HS(
//		      &ghjss_s[0], &ghjss_p[0], &ghjcc_s[0],   &ghjcc_p[0],   &ghjbb_s[0],     &ghjbb_p[0],
//		      &ghjtt_s[0], &ghjtt_p[0], &ghjmumu_s[0], &ghjmumu_p[0], &ghjtautau_s[0], &ghjtautau_p[0], 
//		      &ghjWW[0],   &ghjZZ[0],   &ghjZga[0],    &ghjgaga[0],   &ghjgg[0],       ghjhiZ);
//
////      BEreq::HiggsBounds_charged_input_HS(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], 
////		      			&ModelParam_charged.CS_lep_HpjHmi_ratio[0],
////				       	&ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], 
////					&ModelParam_charged.BR_Hpjcs[0], &ModelParam_charged.BR_Hpjcb[0], 
////					&ModelParam_charged.BR_Hptaunu[0]);
//      BEreq::HiggsBounds_charged_input_HS(&ModelParam_charged.MHplus[0], &ModelParam_charged.HpGammaTot[0], 
//                                        &ModelParam_charged.CS_lep_HpjHmi_ratio[0],
//                                        &ModelParam_charged.BR_tWpb, &ModelParam_charged.BR_tHpjb[0], 
//                                        &ModelParam_charged.BR_Hpjcs[0], &ModelParam_charged.BR_Hpjcb[0], 
//                                        &ModelParam_charged.BR_Hptaunu[0], &ModelParam_charged.BR_Hpjtb[0],
//                                        &ModelParam_charged.BR_HpjWZ[0], BR_HpjhiW);
//
//
//      // run HiggsSignals
//      //TODO: Mode option removed in HiggsSignals 2.4.0. Check to make sure that we don't set it somewhere else...
//      //int mode = 1; // 1- peak-centered chi2 method (recommended)
//      double csqmu, csqmh, csqtot, Pvalue;
//      int nobs;
//      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);
//      //TODO: Also calculate STXS chi-square
//
//      result = -0.5*csqtot;
//
//      // Add one-sided Gaussian drop in loglike when the lightest Higgs
//      // mass is > 150 GeV. This avoids a completely flat loglike 
//      // from HS in parameter regions with far too high Higgs mass.
//      if (Mh[0] > 150.)
//      {
//        result -= 0.5 * pow(Mh[0] - 150., 2) / pow(10., 2);
//      }
//      
//      #ifdef COLLIDERBIT_DEBUG
//        std::ofstream f;
//        f.open ("HB_ModelParameters_contents.dat");
//        f<<"LHC log-likleihood";
//        for (int i = 0; i < 3; i++) f<<
//         "             higgs index"      <<
//         "                    "<<i<<":CP"<<
//         "                    "<<i<<":Mh"<<
//         "             "<<i<<":hGammaTot"<<
//         "      "<<i<<":CS_lep_hjZ_ratio"<<
//         "      "<<i<<":CS_tev_vbf_ratio"<<
//         "     "<<i<<":CS_lep_bbhj_ratio"<<
//         " "<<i<<":CS_lep_tautauhj_ratio"<<
//         "        "<<i<<":CS_gg_hj_ratio"<<
//         "     "<<i<<":CS_tev_tthj_ratio"<<
//         "    "<<i<<":CS_lhc7_tthj_ratio"<<
//         "    "<<i<<":CS_lhc8_tthj_ratio"<<
//         "  "<<i<<":CS_lep_hjhi_ratio[0]"<<
//         "  "<<i<<":CS_lep_hjhi_ratio[1]"<<
//         "  "<<i<<":CS_lep_hjhi_ratio[2]"<<
//         "                 "<<i<<":BR_ss"<<
//         "                 "<<i<<":BR_cc"<<
//         "                 "<<i<<":BR_bb"<<
//         "               "<<i<<":BR_mumu"<<
//         "             "<<i<<":BR_tautau"<<
//         "                 "<<i<<":BR_WW"<<
//         "                 "<<i<<":BR_ZZ"<<
//         "                "<<i<<":BR_Zga"<<
//         "             "<<i<<":BR_gamgam"<<
//         "                 "<<i<<":BR_gg"<<
//         "          "<<i<<":BR_invisible"<<
//         "            "<<i<<":BR_hihi[0]"<<
//         "            "<<i<<":BR_hihi[1]"<<
//         "            "<<i<<":BR_hihi[2]";
//        f<<
//         "             higgs index"      <<
//         "                 "<<4<<"MHplus"<<
//         "            "<<4<<":HpGammaTot"<<
//         "   "<<4<<":CS_lep_HpjHmi_ratio"<<
//         "             "<<4<<":BR_H+->cs"<<
//         "             "<<4<<":BR_H+->cb"<<
//         "          "<<4<<":BR_H+->taunu"<<
//         "             "<<4<<":BR_t->W+b"<<
//         "             "<<4<<":BR_t->H+b";
//        f << endl << std::setw(18) << result;
//        const int w = 24;
//        for (int i = 0; i < 3; i++)
//        {
//          f << std::setw(w) << i << std::setw(w) <<
//           ModelParam.CP[i] << std::setw(w) <<
//           ModelParam.Mh[i] << std::setw(w) <<
//           ModelParam.hGammaTot[i] << std::setw(w) <<
//           ModelParam.CS_lep_hjZ_ratio[i] << std::setw(w) <<
//           ModelParam.CS_tev_vbf_ratio[i] << std::setw(w) <<
//           ModelParam.CS_lep_bbhj_ratio[i] << std::setw(w) <<
//           ModelParam.CS_lep_tautauhj_ratio[i] << std::setw(w) <<
//           ModelParam.CS_gg_hj_ratio[i] << std::setw(w) <<
//           ModelParam.CS_tev_tthj_ratio[i] << std::setw(w) <<
//           ModelParam.CS_lhc7_tthj_ratio[i] << std::setw(w) <<
//           ModelParam.CS_lhc8_tthj_ratio[i];
//          for (int j = 0; j < 3; j++) f << std::setw(w) << ModelParam.CS_lep_hjhi_ratio[i][j];
//          f << std::setw(w) <<
//           ModelParam.BR_hjss[i] << std::setw(w) <<
//           ModelParam.BR_hjcc[i] << std::setw(w) <<
//           ModelParam.BR_hjbb[i] << std::setw(w) <<
//           ModelParam.BR_hjmumu[i] << std::setw(w) <<
//           ModelParam.BR_hjtautau[i] << std::setw(w) <<
//           ModelParam.BR_hjWW[i] << std::setw(w) <<
//           ModelParam.BR_hjZZ[i] << std::setw(w) <<
//           ModelParam.BR_hjZga[i] << std::setw(w) <<
//           ModelParam.BR_hjgaga[i] << std::setw(w) <<
//           ModelParam.BR_hjgg[i] << std::setw(w) <<
//           ModelParam.BR_hjinvisible[i];
//          for (int j = 0; j < 3; j++) f << std::setw(w) << ModelParam.BR_hjhihi[i][j];
//        }
//        f << std::setw(w) << 4 << std::setw(w) <<
//         ModelParam.MHplus[0] << std::setw(w) <<
//         ModelParam.HpGammaTot[0] << std::setw(w) <<
//         ModelParam.CS_lep_HpjHmi_ratio[0] << std::setw(w) <<
//         ModelParam.BR_Hpjcs[0] << std::setw(w) <<
//         ModelParam.BR_Hpjcb[0] << std::setw(w) <<
//         ModelParam.BR_Hptaunu[0] << std::setw(w) <<
//         ModelParam.BR_tWpb << std::setw(w) <<
//         ModelParam.BR_tHpjb[0];
//        f.close();
//      #endif
//
//    }
