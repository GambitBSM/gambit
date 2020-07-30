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
                printf("%2d %5s %16.8E\n", h, "gg