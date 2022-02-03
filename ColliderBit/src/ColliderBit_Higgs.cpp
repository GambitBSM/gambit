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

#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpecSM.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"
#include "gambit/Core/point_counter.hpp"


// #define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {


    // --------------------------------------------------
    // declarations for convenience
    enum yukawa_type
    {
      type_I = 1,
      type_II,
      lepton_specific,
      flipped,
      type_III
    };
    enum particle_type
    {
      h0 = 1,
      H0,
      A0,
      G0,
      Hp,
      Hm,
      Gp,
      Gm
    };
    struct physical_basis_input
    {
      double mh, mH, mC, mA, mG, mGC, beta, lambda6, lambda7, m122, alpha;
    };

    // model lookup map -> useful for looking up model info
    // the keys correspond to model names which may be matched using the ModelInUse GAMBIT function
    struct model_param
    {
      bool is_model_at_Q;
      yukawa_type model_y_type;
      // constructor
      model_param(bool is_model_at_Q_in, yukawa_type model_y_type_in) : is_model_at_Q(is_model_at_Q_in), model_y_type(model_y_type_in) {}
    };

    std::map<std::string, model_param> THDM_model_lookup_map = {
        {"THDMatQ", model_param(true, type_III)},
        {"THDM", model_param(false, type_III)},
        {"THDMIatQ", model_param(true, type_I)},
        {"THDMI", model_param(false, type_I)},
        {"THDMIIatQ", model_param(true, type_II)},
        {"THDMII", model_param(false, type_II)},
        {"THDMLSatQ", model_param(true, lepton_specific)},
        {"THDMLS", model_param(false, lepton_specific)},
        {"THDMflippedatQ", model_param(true, flipped)},
        {"THDMflipped", model_param(false, flipped)}};
    // --------------------------------------------------


    

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

          // Total width 
          const DecayTable::Entry& decays = Dep::Higgs_Couplings->get_neutral_decays(i);
          result.hGammaTot[i] = decays.width_in_GeV;

          const bool calc_width_using_HB = false;
          if (calc_width_using_HB) {
            // get HB to calculate total width internally (this is only valid for scalar masses up to 1 TeV)
            result.hGammaTot[i] = -1.;
          }
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
    
    // ~~ 24 ~~ (fill THDM model params for HB)
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

          // Total width 
          const DecayTable::Entry& decays = Dep::Higgs_Couplings->get_neutral_decays(i);
          result.hGammaTot[i] = decays.width_in_GeV;

          const bool calc_width_using_HB = false;
          if (calc_width_using_HB) {
            // get HB to calculate total width internally (this is only valid for scalar masses up to 1 TeV)
            result.hGammaTot[i] = -1.;
          }
          
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
    
    // ~~ 25 ~~ (fill in charged model in put for HB)
    // fills THDM charged model input for HB 4/5
    void THDM_ModelParameters_charged(hb_charged_ModelParameters &result) {
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
    
    struct HS_Test_Results
    {
      double HS_Channel_h_to_gaga_LogLike { 0.0 };
      double HS_Channel_h_to_ZZ_LogLike { 0.0 };
      double HS_Channel_h_to_WW_LogLike { 0.0 };
      double HS_Channel_h_to_tautau_LogLike { 0.0 };
      double HS_Channel_h_to_bb_LogLike { 0.0 };
      double HS_Channel_h_to_mumu_LogLike { 0.0 };
      double HS_Channel_h_to_all_LogLike { 0.0 };
    };

    static HS_Test_Results* hs_results { nullptr };

    enum DecayChannels
    {
      gaga,   // (loop) h -> (3 diagrams) -> gamma+gamma
      ZZ,     // h -> ZZ
      WW,     // h -> WW
      tautau, // h -> tau+tau
      bb,     // h -> bb -> ?
      mumu,   // h -> mu+mu
      // missing (loop) h -> .. -> Z+gamma
      nDecayChannels
    };

    enum ProductionChannels
    {
      ggF, // (loop) gluon-gluon fusion ( gg -> fff* -> h )
      VBF, // vector boson fusion ( qq -> qqVV* -> qqh )
      Wh,  // Associated production / Higgsstrahlung ( qq -> W* -> Wh )
      Zh,  // Associated production / Higgsstrahlung ( qq -> W* -> Zh )
      // missing: (tree) gg -> ... -> hZ
      tth, // qq -> (3 diagrams) -> tth, gg -> (3 diagrams) -> tth
      // missing: (tree) qq -> ... -> bbh
      // missing: (tree) gg -> ... -> bbh
      // pp,  // ??
      // missing: (tree) qq -> ... -> thb
      // missing: (tree) bq -> ... -> thq
      // missing: (tree) bq -> (2 diagrams) -> thW
      nProductionChannels
    };

    double sq(const double x) 
    {
      return x*x;
    }
  

    // calculates the higgs signal strengths
    // for comparison with HiggsSignals backend
    void HiggsSignalsTest(double &result)
    {
      // get deps

      using namespace Pipes::HiggsSignalsTest;

      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }

      // give higgs indicies names
      enum neutral_higgs_indicies {
          light_higgs, heavy_higgs, CP_odd_higgs, NUMBER_OF_NEUTRAL_HIGGS
      };

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;
      const HiggsCouplingsTable::hp_decay_array_type& hp_widths = Dep::Higgs_Couplings->get_charged_decays_array(1);
      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(3);
      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
      const SubSpectrum &spec = fullspectrum.get_HE();
      THDM_spectrum_container container;
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      const SubSpectrum& he = fullspectrum.get_HE();


      // extract 2HDM parameters
      double alpha = container.he->get(Par::dimensionless, "alpha");
      double beta  = container.he->get(Par::dimensionless, "beta");
      double m122  = container.he->get(Par::mass1, "m12_2");
      double mHp2  = sq(container.he->get(Par::Pole_Mass, "H+"));
      double mh2   = sq(container.he->get(Par::Pole_Mass, "h0_1"));
      double mH2   = sq(container.he->get(Par::Pole_Mass, "h0_2"));
      double mA2   = sq(container.he->get(Par::Pole_Mass, "A0"));
      // double C_gSM = 0.0;

      // SM branching ratios

      double BR_hbb_sm = 0.575;
      double BR_hWW_sm = 0.216;
      double BR_hgg_sm = 0.0856;
      double BR_htautau_sm = 0.0630;
      double BR_hcc_sm = 0.0290;
      double BR_hZZ_sm = 0.0267;
      double BR_hgaga_sm = 0.00228;
      double BR_hZga_sm = 0.00155;
      double BR_hmumu_sm = 0.00022;
      double Gamma_total_sm = 4.1e-3; // GeV

      // sm production cross sections (for sqrt(s) = 13 TeV)

      double CS_ggF_sm = 48.517; // pb
      double CS_VBF_sm = 3.779;
      double CS_WH_sm = 1.369;
      double CS_ZH_sm = 0.8824;
      double CS_ttH_sm = 0.5065;
      double CS_bbH_sm = 0.4863;
      double CS_total_sm = 22.3;

      // extract relevant branching ratios

      double BR_hbb = h0_widths[light_higgs]->BF("b","bbar");
      double BR_hWW = h0_widths[light_higgs]->BF("W+","W-");
      double BR_hgg = h0_widths[light_higgs]->BF("g","g");
      double BR_htautau = h0_widths[light_higgs]->BF("tau+","tau-");
      double BR_hcc = h0_widths[light_higgs]->BF("c","cbar");
      double BR_hZZ = h0_widths[light_higgs]->BF("Z0","Z0");
      double BR_hgaga = h0_widths[light_higgs]->BF("gamma","gamma");
      double BR_hZga = h0_widths[light_higgs]->BF("Z0","gamma");
      double BR_hmumu = h0_widths[light_higgs]->BF("mu+","mu-");
      double Gamma_total = h0_widths[light_higgs]->width_in_GeV; // GeV

      // extract relevant cross-sections

      // extract relevant couplings

      // number of decay channels
      int nDecay = DecayChannels::nDecayChannels; 

      // number of production channels
      int nProd = ProductionChannels::nProductionChannels;

      // the higgs signals to be calculated
      std::vector<std::vector<double>> HS ( nDecay, std::vector<double>(nProd, 0.0) );
      std::vector<double> HS_total (nDecay, 0.0 );

      // the SM branching ratios for each decay mode
      std::vector<double> BR_SM ( nDecay, 0.0 );

      // the 2HDM scaling factors
      std::vector<double> kappa ( nDecay+nProd, 0.0 );

      // fill in the scalaing factors (tree-level relations) Type-I only
      // defined as the relevant decay rate/cross-section normalized to the SM value
      // we are assuming mh = 125.09 GeV, sqrt(s) = 8 TeV
      // to leading order these are given by the ratio of the relevant couplings (or effective couplings)

      double k_huu = cos(alpha) / sin(beta);
      double k_hdd = cos(alpha) / sin(beta);
      double k_hee = cos(alpha) / sin(beta);
      double k_hvv = cos(alpha) / sin(beta);
      double k_hWW = sin(beta-alpha);
      double k_hZZ = sin(beta-alpha);

      double a1 = m122/(sin(beta)*cos(beta)*mHp2);
      double a2 = mh2/mHp2;

      double k_hgg = sqrt((BR_hgg*Gamma_total)/(BR_hgg_sm*Gamma_total_sm)); // from P.181(Corre)
      double k_hgaga = sqrt((BR_hgaga*Gamma_total)/(BR_hgaga_sm*Gamma_total_sm)); // from P.181(Corre)

      double k_hgaga_wei = 1+((-1.0/3.0) * (1-a1)-(1/90)*(23-8*a1)*a2-(1/1440)*(73-9*a1)*a2*a2) * (1/6.53); // Wei's paper
      // double k_hgg = sqrt(1.06*sq(k_huu) + 0.01*sq(k_hdd) - 0.07*k_huu*k_hdd + 0.74*sq(k_hWW) + 0.26*sq(k_hZZ)); // effective coupling from Higgs paper
      // double k_hgaga = sqrt(1.59*sq(k_hWW) + 0.07*sq(k_huu) - 0.66*k_hWW*k_huu); // effective coupling from Higgs paper

      // Resolved scaling factors

      double sigma_ggF = k_hgg;
      double sigma_VBF = 0.74*sq(k_hWW) + 0.26*sq(k_hZZ);
      double sigma_WH = sq(k_hWW);
      double sigma_qqZH = sq(k_hZZ);
      double sigma_ggZH = 2.27*sq(k_hZZ) + 0.37*sq(k_huu) - 1.64*k_huu*k_hZZ;
      double sigma_ttH = sq(k_huu);
      double sigma_tHW = 0.;
      double sigma_tHq = 0.;
      double sigma_bbH = sq(k_hdd);

      double Gamma_ZZ = sq(k_hZZ);
      double Gamma_WW = sq(k_hWW);
      double Gamma_gaga = sq(k_hgaga);
      double Gamma_tautau = sq(k_hee);
      double Gamma_bb = sq(k_hdd);
      double Gamma_mumu = sq(k_hee);


      // calculate the signal strengths (\mu_i == ( \sigma_i * \Gamma_i)^2HDM / ( \sigma_i * \Gamma_i)^SM)
      // here we implicitly assume we can use the NWA (narrow width approximation)
      // Higgs-signal-strength[Decay][Production]

      HS[gaga][ggF]   = sq(k_hgg)*BR_hgaga/BR_hgaga_sm;
      HS[ZZ][ggF]     = sq(k_hgg)*BR_hZZ/BR_hZZ_sm;
      HS[WW][ggF]     = sq(k_hgg)*BR_hWW/BR_hWW_sm;
      HS[tautau][ggF] = sq(k_hgg)*BR_htautau/BR_htautau_sm;
      HS[bb][ggF]     = sq(k_hgg)*BR_hbb/BR_hbb_sm;
      HS[mumu][ggF]   = sq(k_hgg)*BR_hmumu/BR_hmumu_sm;

      HS[gaga][VBF]   = sq(k_hWW)*BR_hgaga/BR_hgaga_sm;
      HS[ZZ][VBF]     = sq(k_hWW)*BR_hZZ/BR_hZZ_sm;
      HS[WW][VBF]     = sq(k_hWW)*BR_hWW/BR_hWW_sm;
      HS[tautau][VBF] = sq(k_hWW)*BR_htautau/BR_htautau_sm;
      HS[bb][VBF]     = sq(k_hWW)*BR_hbb/BR_hbb_sm;
      HS[mumu][VBF]   = sq(k_hWW)*BR_hmumu/BR_hmumu_sm;

      for (const auto& hs : HS[gaga]) HS_total[gaga] += hs;
      for (const auto& hs : HS[ZZ]) HS_total[ZZ] += hs;
      for (const auto& hs : HS[WW]) HS_total[WW] += hs;
      for (const auto& hs : HS[tautau]) HS_total[tautau] += hs;
      for (const auto& hs : HS[bb]) HS_total[bb] += hs;
      for (const auto& hs : HS[mumu]) HS_total[mumu] += hs;

      // calculate the likelihood components

      std::vector<std::vector<double>> HS_exp ( nDecay , std::vector<double>(nProd, 1.0) );
      std::vector<double> HS_exp_total ( nDecay, 1.0 );

      std::vector<std::vector<double>> HS_exp_corr ( nDecay , std::vector<double>(nProd, 10.0) );
      std::vector<double> HS_exp_total_corr ( nDecay, 10.0 );

      // HS_exp_total[gaga]   = 1.14;
      // HS_exp_total[ZZ]     = 1.29;
      // HS_exp_total[WW]     = 0.0;
      // HS_exp_total[tautau] = 0.79;
      // HS_exp_total[bb]     = 2.3;
      // HS_exp_total[mumu]   = 0.0;

      // HS_exp_total_corr[gaga]   = 0.0;
      // HS_exp_total_corr[ZZ]     = 0.0;
      // HS_exp_total_corr[WW]     = 0.0;
      // HS_exp_total_corr[tautau] = 0.0;
      // HS_exp_total_corr[bb]     = 0.0;
      // HS_exp_total_corr[mumu]   = 0.0;
      
      HS_exp[gaga][ggF] = 1.10;
      HS_exp[gaga][VBF] = 1.30;
      HS_exp[gaga][Wh]  = 0.50;
      HS_exp[gaga][Zh]  = 0.50;
      HS_exp[gaga][tth] = 2.20;
      
      HS_exp[ZZ][ggF] = 1.13;
      HS_exp[ZZ][VBF] = 0.10;
      // HS_exp[ZZ][Wh]  = 1.0;
      // HS_exp[ZZ][Zh]  = 1.0;
      HS_exp[ZZ][tth] = 1.15;
      
      HS_exp[WW][ggF] = 0.84;
      HS_exp[WW][VBF] = 1.20;
      HS_exp[WW][Wh]  = 1.60;
      HS_exp[WW][Zh]  = 5.90;
      HS_exp[WW][tth] = 5.00;
      
      HS_exp[tautau][ggF] = 1.00;
      HS_exp[tautau][VBF] = 1.30;
      HS_exp[tautau][Wh]  = -1.40;
      HS_exp[tautau][Zh]  = 2.20;
      HS_exp[tautau][tth] = -1.90;
      
      // HS_exp[bb][ggF] = 1.0;
      // HS_exp[bb][VBF] = 1.0;
      HS_exp[bb][Wh]  = 1.00;
      HS_exp[bb][Zh]  = 0.40;
      // HS_exp[bb][tth] = 1.0;
      
      // HS_exp[mumu][ggF] = 1.0;
      // HS_exp[mumu][VBF] = 1.0;
      // HS_exp[mumu][Wh]  = 1.0;
      // HS_exp[mumu][Zh]  = 1.0;
      // HS_exp[mumu][tth] = 1.0;





      HS_exp_corr[gaga][ggF] = 0.23;
      HS_exp_corr[gaga][VBF] = 0.50;
      HS_exp_corr[gaga][Wh]  = 1.30;
      HS_exp_corr[gaga][Zh]  = 3.00;
      HS_exp_corr[gaga][tth] = 1.60;
      
      HS_exp_corr[ZZ][ggF] = 0.34;
      HS_exp_corr[ZZ][VBF] = 1.10;
      // HS_exp_corr[ZZ][Wh]  = 1.0;
      // HS_exp_corr[ZZ][Zh]  = 1.0;
      HS_exp_corr[ZZ][tth] = 0.99;
      
      HS_exp_corr[WW][ggF] = 0.17;
      HS_exp_corr[WW][VBF] = 0.40;
      HS_exp_corr[WW][Wh]  = 1.20;
      HS_exp_corr[WW][Zh]  = 2.60;
      HS_exp_corr[WW][tth] = 1.80;
      
      HS_exp_corr[tautau][ggF] = 0.60;
      HS_exp_corr[tautau][VBF] = 0.40;
      HS_exp_corr[tautau][Wh]  = 1.40;
      HS_exp_corr[tautau][Zh]  = 2.20;
      HS_exp_corr[tautau][tth] = 3.70;
      
      // HS_exp_corr[bb][ggF] = 1.0;
      // HS_exp_corr[bb][VBF] = 1.0;
      HS_exp_corr[bb][Wh]  = 0.50;
      HS_exp_corr[bb][Zh]  = 0.40;
      // HS_exp_corr[bb][tth] = 1.0;
      
      // HS_exp_corr[mumu][ggF] = 1.0;
      // HS_exp_corr[mumu][VBF] = 1.0;
      // HS_exp_corr[mumu][Wh]  = 1.0;
      // HS_exp_corr[mumu][Zh]  = 1.0;
      // HS_exp_corr[mumu][tth] = 1.0;


      std::vector<std::vector<double>> HS_LogLike ( nDecay , std::vector<double>(nProd, 0.0) );

      for (size_t d=0; d<HS_LogLike.size(); ++d)
      {
        for (size_t p=0; p<HS_LogLike[0].size(); ++p)
        {
          // skip if some entries are missing

          if (!(p == ggF || p == VBF)) continue;
          if (d == mumu) continue;
          if (p == ZZ && d == Wh) continue;
          if (p == ZZ && d == Zh) continue;
          if (p == bb && d == ggF) continue;
          if (p == bb && d == VBF) continue;
          if (p == bb && d == tth) continue;

          HS_LogLike[d][p] = -0.5 * sq((HS[d][p] - HS_exp[d][p]) / HS_exp_corr[d][p]);
        }
      }

      // fill in the results struct

      if (hs_results == nullptr)
        hs_results = new HS_Test_Results;

      hs_results->HS_Channel_h_to_gaga_LogLike = 0.0;
      hs_results->HS_Channel_h_to_ZZ_LogLike = 0.0;
      hs_results->HS_Channel_h_to_WW_LogLike = 0.0;
      hs_results->HS_Channel_h_to_tautau_LogLike = 0.0;
      hs_results->HS_Channel_h_to_bb_LogLike = 0.0;
      hs_results->HS_Channel_h_to_mumu_LogLike = 0.0;
      hs_results->HS_Channel_h_to_all_LogLike = 0.0;

      for (auto& hs : HS_LogLike[gaga]) hs_results->HS_Channel_h_to_gaga_LogLike += hs;
      for (auto& hs : HS_LogLike[ZZ]) hs_results->HS_Channel_h_to_ZZ_LogLike += hs;
      for (auto& hs : HS_LogLike[WW]) hs_results->HS_Channel_h_to_WW_LogLike += hs;
      for (auto& hs : HS_LogLike[tautau]) hs_results->HS_Channel_h_to_tautau_LogLike += hs;
      for (auto& hs : HS_LogLike[bb]) hs_results->HS_Channel_h_to_bb_LogLike += hs;
      for (auto& hs : HS_LogLike[mumu]) hs_results->HS_Channel_h_to_mumu_LogLike += hs;
      for (auto& d : HS_LogLike) 
        for (auto& hs : d) 
          hs_results->HS_Channel_h_to_all_LogLike += hs;

      result = 1.0;

    }
    
    void calc_HS_TEST_CHANNEL_h_to_gaga(double& result)
    {
      result = hs_results->HS_Channel_h_to_gaga_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_ZZ(double& result)
    {
      result = hs_results->HS_Channel_h_to_ZZ_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_WW(double& result)
    {
      result = hs_results->HS_Channel_h_to_WW_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_tautau(double& result)
    {
      result = hs_results->HS_Channel_h_to_tautau_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_mumu(double& result)
    {
      result = hs_results->HS_Channel_h_to_mumu_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_bb(double& result)
    {
      result = hs_results->HS_Channel_h_to_bb_LogLike;
    }
    
    void calc_HS_TEST_CHANNEL_h_to_all(double& result)
    {
      result = hs_results->HS_Channel_h_to_all_LogLike;
    }

    // ~~ 26 ~~ (get HiggsSignals LL)
    /// Get an LHC chisq from HiggsSignals (v2 beta)
    void calc_HS_2_LHC_LogLike(double &result)
    {
      // result = 1.0;
      // return; // !!!!!!


      static point_counter count("HiggsSignals LL"); count.count();
      static point_counter count2("HiggsSignals NaN/inf"); count2.count();

      using namespace Pipes::calc_HS_2_LHC_LogLike;
      const bool SMHiggsMassOnly = runOptions->getValueOrDef<bool>(false, "sm_higgs_mass_only");

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      hb_charged_ModelParameters ModelParam_charged = *Dep::HB_ModelParameters_charged;

      const int nNeutral = 3; // !!!!

      // - put Higgs branching ratios into a Fortran array

      Farray<double, 1,nNeutral> BR_HpjhiW, BR_hjHpiW;
      Farray<double, 1,nNeutral, 1,nNeutral> ghjhiZ, BR_hjhiZ;
      Farray<double, 1,nNeutral, 1,nNeutral, 1,nNeutral> BR_hkhjhi;

      for(int j = 0; j < nNeutral; j++) {
        BR_HpjhiW(j+1) = ModelParam_charged.BR_HpjhiW[j];
        BR_hjHpiW(j+1) = ModelParam.BR_hjHpiW[j][0];

        for(int i = 0; i < nNeutral; i++) {
          ghjhiZ(j+1,i+1) = ModelParam.ghjhiZ[j][i];
          BR_hjhiZ(j+1,i+1) = ModelParam.BR_hjhiZ[j][i];
          
          for(int k = 0; k < nNeutral; k++) {
            BR_hkhjhi(k+1, j+1, i+1) = ModelParam.BR_hkhjhi[k][j][i];
          }
        }
      }

      // - give our couplings / branching ratios to HiggsBounds/HiggsSignals

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

      // std::cout << "mh2" << ModelParam.Mh[1] << std::endl;
      // std::cout << "mh3" << ModelParam.Mh[2] << std::endl;

      // add uncertainties to cross-sections and branching ratios
      // double dCS[5] = {0.,0.,0.,0.,0.};
      // double dBR[5] = {0.,0.,0.,0.,0.};
      // BEreq::setup_rate_uncertainties(dCS,dBR);

      // - run HiggsSignals
      // int mode = 1; // 1- peak-centered chi2 method (recommended)
      double csqmu, csqmh, csqtot, Pvalue;
      double csqmu1, csqmh1, csqtot1, Pvalue1;
      double csqmu2, csqmh2, csqtot2, Pvalue2;
      int nobs, nobs1, nobs2;

      // Run the main subroutines
      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);
      BEreq::run_HiggsSignals_LHC_Run1_combination(csqmu1, csqmh1, csqtot1, nobs1, Pvalue1);
      BEreq::run_HiggsSignals_STXS(csqmu2, csqmh2, csqtot2, nobs2, Pvalue2);

      // std::cout << " " << csqmu << " " << csqmu1 << " " << csqmu2 << " " << csqmh << " " << csqmh1 << " " << csqmh2 << std::endl;


      // // std::cout << "csqmu " << csqmu << std::endl;
      // // std::cout << "csqmh " << csqmh << std::endl;
      // // std::cout << "csqmu1 " << csqmu1 << std::endl;
      // // std::cout << "csqmh1 " << csqmh1 << std::endl;
      // // std::cout << "csqmu2 " << csqmu2 << std::endl;
      // // std::cout << "csqmh2 " << csqmh2 << std::endl;

      // result = -0.5*(csqmu1+csqmu);

      // if (SMHiggsMassOnly) 
      //   result = -0.5*(csqmh + csqmh1 + csqmh2);
      // else
        result = -0.5*(csqtot + csqtot1 + csqtot2);

      // std::cout << "mh1  " << ModelParam.Mh[0] << "  | massLL:  " <<  -0.5*(csqmh + csqmh1 + csqmh2) << "  | muLL:  " <<  -0.5*(csqmu + csqmu1 + csqmu2) << std::endl;

      // std::cout << "csqmh: " << csqmh << '\n';
      // std::cout << "csqmh1: " << csqmh1 << '\n';
      // std::cout << "csqmh2: " << csqmh2 << '\n';
      // std::cout << "csqmu: " << csqmu << '\n';
      // std::cout << "csqmu1: " << csqmu1 << '\n';
      // std::cout << "csqmu2: " << csqmu2 << '\n';

      // result = csqmh1; // !!!!!
      if (csqmu > 45 || csqmu1 > 100 || csqmu2 > 300)
      {
        count.count_invalid();
      }


      if (std::isnan(result) || std::isinf(result))
      {
        count2.count_invalid();
        invalid_point().raise("NaN or infinite HS likelihood, point invalidated!");
      }

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

     /// Get an LHC chisq from HiggsSignals
    void calc_SM_Higgs_Mass_LogLike(double &result)
    {
      using namespace Pipes::calc_SM_Higgs_Mass_LogLike;

      hb_neutral_ModelParameters_effc ModelParam = *Dep::HB_ModelParameters_neutral;
      const double mh = ModelParam.Mh[0];
      const double mh_obs = 124.97;
      const double error = 0.24;

      result = -0.5 * pow(((mh - mh_obs) / error), 2);

    }
  }
}
