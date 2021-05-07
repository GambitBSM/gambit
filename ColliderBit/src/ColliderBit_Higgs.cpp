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
    void set_CS_neutral(hb_neutral_ModelParameters_part &result, const HiggsCouplingsTable& couplings, int nNeutral)
    {
      for(int i = 0; i < nNeutral; i++)
      {
        result.CS_bg_hjb_ratio[i] = couplings.C_bb2[i];
        result.CS_bb_hj_ratio[i]  = couplings.C_bb2[i];
        result.CS_lep_bbhj_ratio[i] = couplings.C_bb2[i];

        result.CS_lep_tautauhj_ratio[i] = couplings.C_tautau2[i];

        result.CS_lep_hjZ_ratio[i] = pow(couplings.C_ZZ[i],2);
        result.CS_gg_hjZ_ratio[i] = 0.; //TODO
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

        for(int j = 0; j < nNeutral; j++)
        {
          result.CS_lep_hjhi_ratio[i][j] = pow(couplings.C_hiZ[i][j],2);
        }
      }
    }

    /// Helper function to set HiggsBounds/Signals parameters cross-section ratios (HB 5 input) from a GAMBIT HiggsCouplingsTable
    void set_CS_neutral_effc(hb_neutral_ModelParameters_effc &result, const HiggsCouplingsTable& couplings, int nNeutral)
    {
      for(int i = 0; i < nNeutral; i++)
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

          for(int j = 0; j < nNeutral; j++)
            result.ghjhiZ[i][j] = couplings.C_hiZ[i][j];
      }
    }

    /// Helper function to set HiggsBounds/Signals non SM branchings (v5) from a GAMBIT HiggsCouplingsTable
    template <class T>
    void set_nonSMBR(T &result, const HiggsCouplingsTable& Higgs_Couplings, int nNeutral)
    {
      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Higgs_Couplings.get_neutral_decays_array(3);
      const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      // Loop over Higgs & fill
      for (int j = 1; j <= nNeutral; j++) {
        for (int i = 1; i <= nNeutral; i++) {
          for (int k = 1; k <= nNeutral; k++) {
              // h -> h,h
              if (result.Mh[k-1] > (result.Mh[j-1]+result.Mh[i-1]) and h0_widths[k-1]->has_channel(sHneut[j-1],sHneut[i-1])) {
                result.BR_hkhjhi[k-1][j-1][i-1] = h0_widths[k-1]->BF(sHneut[j-1],sHneut[i-1]);
              }
              else {
                result.BR_hkhjhi[k-1][j-1][i-1] = 0.;
              }
              #ifdef COLLIDERBIT_DEBUG
                std::cout << "h->hh ("<< k << ", " << j << ", " << i << "): " << result.BR_hkhjhi[k - 1][j - 1][i - 1] << std::endl;
              #endif
            }
            result.BR_hjhiZ[j-1][i-1] = h0_widths[j-1]->has_channel("Z0",sHneut[i-1]) ? h0_widths[j-1]->BF("Z0",sHneut[i-1]) : 0.; 
            #ifdef COLLIDERBIT_DEBUG
              std::cout << "h->hZ ("<< j << ", " << i << "): " << result.BR_hjhiZ[j - 1][i - 1] << std::endl;
            #endif
          }
        // invisibles
        result.BR_hjinvisible[j-1] = 0.;
        for (auto it = Higgs_Couplings.invisibles.begin(); it != Higgs_Couplings.invisibles.end(); ++it) {
          result.BR_hjinvisible[j-1] += h0_widths[j-1]->BF(*it, *it);
        }
        // other
        result.BR_hjemu[j-1] = h0_widths[j-1]->has_channel("e+","mu-") ? h0_widths[j-1]->BF("e+","mu-") : 0.; 
        result.BR_hjetau[j-1] = h0_widths[j-1]->has_channel("e+","tau-") ? h0_widths[j-1]->BF("e+","tau-") : 0.;  
        result.BR_hjmutau[j-1] = h0_widths[j-1]->has_channel("mu+","tau-") ? h0_widths[j-1]->BF("mu+","tau-") : 0.; 
        result.BR_hjHpiW[j-1][0] = h0_widths[j-1]->has_channel("H+","W-") ? h0_widths[j-1]->BF("H+","W-") : 0.; 
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
      // Cross section 
      set_CS_charged(result); // Moved this to end, so CS_lep_HpjHmi_ratio is set. Is that OK?
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

        // Retrieve masses
        const Spectrum& fullspectrum = *Dep::MSSM_spectrum;
        const SubSpectrum& he = fullspectrum.get_HE();

        // Neutral higgs masses, widths and errors
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

          // Total width - get HB to calculate this 
          result.hGammaTot[i] = -1.;
          // Total width - use calculated
          // result.hGammaTot[i] = decays.width_in_GeV;
        }

        // fill neutral effective couplings
        set_CS_neutral_effc(result, *Dep::Higgs_Couplings, 3);
        // fill non SM BRs
        set_nonSMBR(result, *Dep::Higgs_Couplings, 3);
      
        #ifdef COLLIDERBIT_DEBUG
          for (int h=1;h<=3;h++) {
            for (int h2=1; h2<=3; h2++) {
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
            }
          }
        #endif
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

      // Cross section
      set_CS_charged(result);

      // Set charged Higgs branching fractions and total width.
      result.HpGammaTot[0] = H_plus_widths.width_in_GeV;
      result.BR_Hpjcs[0]   = H_plus_widths.has_channel("c", "sbar") ? H_plus_widths.BF("c", "sbar") : 0.; 
      result.BR_Hpjcb[0]   = H_plus_widths.has_channel("c", "bbar") ? H_plus_widths.BF("c", "bbar") : 0.; 
      result.BR_Hptaunu[0] = H_plus_widths.has_channel("tau+", "nu_tau") ? H_plus_widths.BF("tau+", "nu_tau") : 0.; 

      // Set top branching fractions
      result.BR_tWpb       = t_widths.has_channel("W+", "b") ? t_widths.BF("W+", "b") : 0.; 
      result.BR_tHpjb[0]   = t_widths.has_channel("H+", "b") ? t_widths.BF("H+", "b") : 0.0;

      // extra HB v5 beta input
      result.BR_Hpjtb[0] = H_plus_widths.has_channel("t", "bbar") ? H_plus_widths.BF("t", "bbar"): 0.;
      result.BR_HpjWZ[0] = H_plus_widths.has_channel("W+","Z0") ? H_plus_widths.BF("W+","Z0") : 0.; 

      // Set up neutral Higgses (keys)
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      
      for (int h=1;h<=3;h++) {
        result.BR_HpjhiW[h-1] = H_plus_widths.has_channel("W+",sHneut[h-1]) ? H_plus_widths.BF("W+",sHneut[h-1]): 0.;
      }
     
    }

    // fills THDM neutral model input for HB 5
    void THDM_ModelParameters_effc(hb_neutral_ModelParameters_effc &result)
    {
        using namespace Pipes::THDM_ModelParameters_effc;

        // Set up neutral Higgses
        static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

        // Set the CP of the Higgs states.
        for (int i = 0; i < 3; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

        // Retrieve masses
        const Spectrum& fullspectrum = *Dep::THDM_spectrum;
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

          const DecayTable::Entry& decays = Dep::Higgs_Couplings->get_neutral_decays(i);

          // Total width - get HB to calculate this 
          result.hGammaTot[i] = -1.;
          // Total width - use calculated
          // result.hGammaTot[i] = decays.width_in_GeV;
        }

        // fill neutral effective couplings
        set_CS_neutral_effc(result, *Dep::Higgs_Couplings, 3);
         // fill non SM BRs
        set_nonSMBR(result, *Dep::Higgs_Couplings, 3);
        
        #ifdef COLLIDERBIT_DEBUG
          for (int h=1;h<=3;h++) {
            for (int h2=1; h2<=3; h2++) {
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
            }
          }
        #endif
    }

    // fills THDM charged model input for HB 4/5
    void THDM_ModelParameters_charged(hb_charged_ModelParameters &result)
    {
        using namespace Pipes::THDM_ModelParameters_charged;

        // Retrieve higgs partial widths
        const DecayTable::Entry& H_plus_widths = Dep::Higgs_Couplings->get_charged_decays(0);
        const DecayTable::Entry& t_widths = Dep::Higgs_Couplings->get_t_decays();

        // Retrieve masses
        const Spectrum& fullspectrum = *Dep::THDM_spectrum;
        const SubSpectrum& spec = fullspectrum.get_HE();

        // Charged higgs masses and errors
        result.MHplus[0] = spec.get(Par::Pole_Mass,"H+");
        bool has_high_err = spec.has(Par::Pole_Mass_1srd_high,"H+");
        bool has_low_err = spec.has(Par::Pole_Mass_1srd_low,"H+");
        if (has_high_err and has_low_err)
        {
          double upper = spec.get(Par::Pole_Mass_1srd_high,"H+");
          double lower = spec.get(Par::Pole_Mass_1srd_low,"H+");
          result.deltaMHplus[0] = result.MHplus[0] * std::max(upper,lower);
        }
        else
        {
          result.deltaMHplus[0] = 0.;
        }

        // fill charged effective couplings
        set_CS_charged(result);

        // Set charged Higgs branching fractions and total width.
        result.HpGammaTot[0] = H_plus_widths.width_in_GeV;
        result.BR_Hpjcs[0]   = H_plus_widths.has_channel("c", "sbar") ? H_plus_widths.BF("c", "sbar") : 0.; 
        result.BR_Hpjcb[0]   = H_plus_widths.has_channel("c", "bbar") ? H_plus_widths.BF("c", "bbar") : 0.; 
        result.BR_Hptaunu[0] = H_plus_widths.has_channel("tau+", "nu_tau") ? H_plus_widths.BF("tau+", "nu_tau") : 0.; 

        // Set top branching fractions
        result.BR_tWpb       = t_widths.has_channel("W+", "b") ? t_widths.BF("W+", "b") : 0.; 
        result.BR_tHpjb[0]   = t_widths.has_channel("H+", "b") ? t_widths.BF("H+", "b") : 0.0;

        // extra HB v5 beta input
        result.BR_Hpjtb[0] = H_plus_widths.has_channel("t", "bbar") ? H_plus_widths.BF("t", "bbar"): 0.;
        result.BR_HpjWZ[0] = H_plus_widths.has_channel("W+","Z0") ? H_plus_widths.BF("W+","Z0") : 0.; 

        // Set up neutral Higgses (keys)
        static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
        
         for (int h=1;h<=3;h++) {
          result.BR_HpjhiW[h-1] = H_plus_widths.has_channel("W+",sHneut[h-1]) ? H_plus_widths.BF("W+",sHneut[h-1]): 0.;
         }

        #ifdef COLLIDERBIT_DEBUG
        std::cout << "Pole_Mass " << result.MHplus[0] << std::endl;
        std::cout << "Width " << result.HpGammaTot[0] << std::endl;
          printf("4 %5s %16.8E\n", "tW", result.BR_tWpb);
          printf("4 %5s %16.8E\n", "tHpj", result.BR_tHpjb[0]);
          printf("4 %5s %16.8E\n", "Hpjcs", result.BR_Hpjcs[0]);
          printf("4 %5s %16.8E\n", "Hpjcb", result.BR_Hpjcb[0]);
          printf("4 %5s %16.8E\n", "BR_Hptaunu", result.BR_Hptaunu[0]);
          printf("4 %5s %16.8E\n", "BR_Hpjtb", result.BR_Hpjtb[0]);
          printf("4 %5s %16.8E\n", "BR_HpjhiW", result.BR_HpjhiW[0]);
        #endif
 
    }

    // fills THDM neutral model input for HB 4 
    void THDM_ModelParameters(hb_neutral_ModelParameters_part &result)
    {
      using namespace Pipes::THDM_ModelParameters;

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Set the CP of the Higgs states.
      for (int i = 0; i < 3; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

      // Retrieve higgs partial widths
      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(3);

      // Retrieve masses
      const Spectrum& fullspectrum = *Dep::THDM_spectrum;
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

      set_CS_neutral(result, *Dep::Higgs_Couplings, 3);

      // cycle over neutral scalars & fill HB input
      for (int h=0; h<3; h++) {
        result.hGammaTot[h] = h0_widths[h]->width_in_GeV;
        result.BR_hjss[h] = h0_widths[h]->BF("s", "sbar");
        result.BR_hjcc[h] = h0_widths[h]->BF("c", "cbar");
        result.BR_hjbb[h] = h0_widths[h]->BF("b", "bbar");
        result.BR_hjmumu[h] = h0_widths[h]->BF("mu+", "mu-");
        result.BR_hjtautau[h] = h0_widths[h]->BF("tau+", "tau-");
        result.BR_hjWW[h] = h0_widths[h]->BF("W+", "W-");
        result.BR_hjZZ[h] = h0_widths[h]->BF("Z0", "Z0");
        result.BR_hjZga[h] = h0_widths[h]->BF("gamma", "Z0");
        result.BR_hjgaga[h] = h0_widths[h]->BF("gamma", "gamma");
        result.BR_hjgg[h] = h0_widths[h]->BF("g", "g");

        // Do decays to invisibles
        result.BR_hjinvisible[h] = 0.;
        for (auto it = Dep::Higgs_Couplings->invisibles.begin(); it != Dep::Higgs_Couplings->invisibles.end(); ++it)
        {
          result.BR_hjinvisible[h] += h0_widths[h]->BF(*it, *it);
        }

        // Do decays to other neutral higgses
        for (int h2=0; h2<3; h2++) {

          if (2.*result.Mh[h2] < result.Mh[h] and h0_widths[h]->has_channel(sHneut[h2],sHneut[h2]))
          {
            result.BR_hjhihi[h][h2] = h0_widths[h]->BF(sHneut[h2],sHneut[h2]);
          }
          else
          {
            result.BR_hjhihi[h][h2] = 0.;
          }
        }
      }
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

      const int nNeutral = 3;

      Farray<double, 1,nNeutral> BR_HpjhiW, BR_hjHpiW;
      Farray<double, 1,nNeutral, 1,nNeutral> ghjhiZ, BR_hjhiZ;
      Farray<double, 1,nNeutral, 1,nNeutral, 1,nNeutral> BR_hkhjhi;

      for(int j = 0; j < nNeutral; j++) {
        BR_HpjhiW(j+1) = ModelParam_charged.BR_HpjhiW[j];
        BR_hjHpiW(j+1) = ModelParam.BR_hjHpiW[j][0];
        //
        for(int i = 0; i < nNeutral; i++) {
          ghjhiZ(j+1,i+1) = ModelParam.ghjhiZ[j][i];
          BR_hjhiZ(j+1,i+1) = ModelParam.BR_hjhiZ[j][i];
          
          //
          for(int k = 0; k < nNeutral; k++) {
            BR_hkhjhi(k+1, j+1, i+1) = ModelParam.BR_hkhjhi[k][j][i];
          }
          //
        }
        //
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

      BEreq::HiggsBounds_neutral_input_nonSMBR(
        &ModelParam.BR_hjinvisible[0], BR_hkhjhi,
        BR_hjhiZ, &ModelParam.BR_hjemu[0],
        &ModelParam.BR_hjetau[0], &ModelParam.BR_hjmutau[0],
        BR_hjHpiW);

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
      BEreq::HiggsBounds_get_LEPChisq(theor_unc,chisq_withouttheory,chisq_withtheory,chan2);

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

    /// Get an LHC chisq from HiggsSignals (v2 beta)
    void calc_HS_2_LHC_LogLike(double &result)
    {
      using namespace Pipes::calc_HS_2_LHC_LogLike;

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      const int nNeutral = 3;

      Farray<double, 1,nNeutral> BR_HpjhiW, BR_hjHpiW;
      Farray<double, 1,nNeutral, 1,nNeutral> ghjhiZ, BR_hjhiZ;
      Farray<double, 1,nNeutral, 1,nNeutral, 1,nNeutral> BR_hkhjhi;

      for(int j = 0; j < nNeutral; j++) {
        BR_HpjhiW(j+1) = ModelParam_charged.BR_HpjhiW[j];
        BR_hjHpiW(j+1) = ModelParam.BR_hjHpiW[j][0];
        //
        for(int i = 0; i < nNeutral; i++) {
          ghjhiZ(j+1,i+1) = ModelParam.ghjhiZ[j][i];
          BR_hjhiZ(j+1,i+1) = ModelParam.BR_hjhiZ[j][i];
          
          //
          for(int k = 0; k < nNeutral; k++) {
            BR_hkhjhi(k+1, j+1, i+1) = ModelParam.BR_hkhjhi[k][j][i];
          }
          //
        }
        //
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

      BEreq::HiggsBounds_neutral_input_nonSMBR_HS(&ModelParam.BR_hjinvisible[0], BR_hkhjhi,
                                                  BR_hjhiZ, &ModelParam.BR_hjemu[0],
                                                  &ModelParam.BR_hjetau[0], &ModelParam.BR_hjmutau[0],
                                                  BR_hjHpiW);

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
      // int mode = 1; // 1- peak-centered chi2 method (recommended)
      double csqmu, csqmh, csqtot, Pvalue;
      double csqmu1, csqmh1, csqtot1, Pvalue1;
      double csqmu2, csqmh2, csqtot2, Pvalue2;
      int nobs, nobs1, nobs2;

      // Run the main subroutines
      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);
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
