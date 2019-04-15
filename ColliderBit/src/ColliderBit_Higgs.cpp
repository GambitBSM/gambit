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

#define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// Helper function to set HiggsBounds/Signals parameters cross-section ratios from a GAMBIT HiggsCouplingsTable
    void set_CS(hb_ModelParameters &result, const HiggsCouplingsTable& couplings, int n_neutral_higgses)
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
      // LEP H+ H- x-section ratio
      result.CS_lep_HpjHmi_ratio[0] = 1.;
    }

    /// Helper function for populating a HiggsBounds/Signals ModelParameters object for SM-like Higgs.
    void set_SMLikeHiggs_ModelParameters(const SubSpectrum& spec, const HiggsCouplingsTable& couplings, hb_ModelParameters &result)
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
      set_CS(result, couplings, 1);

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
    void SMHiggs_ModelParameters(hb_ModelParameters &result)
    {
      using namespace Pipes::SMHiggs_ModelParameters;
      set_SMLikeHiggs_ModelParameters(Dep::SM_spectrum->get_HE(), *Dep::Higgs_Couplings, result);
    }

    /// SM-like (SM + possible invisibles) Higgs model parameters for HiggsBounds/Signals
    void SMLikeHiggs_ModelParameters(hb_ModelParameters &result)
    {
      using namespace Pipes::SMLikeHiggs_ModelParameters;
      dep_bucket<Spectrum>* spectrum_dependency;
      if (ModelInUse("ScalarSingletDM_Z2") or ModelInUse("ScalarSingletDM_Z2_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z2_spectrum;
      else if (ModelInUse("ScalarSingletDM_Z3") or ModelInUse("ScalarSingletDM_Z3_running")) spectrum_dependency = &Dep::ScalarSingletDM_Z3_spectrum;
      else ColliderBit_error().raise(LOCAL_INFO, "No valid model for SMLikeHiggs_ModelParameters.");
      const SubSpectrum& spec = (*spectrum_dependency)->get_HE();
      set_SMLikeHiggs_ModelParameters(spec, *Dep::Higgs_Couplings, result);
    }

    /// MSSM Higgs model parameters
    void MSSMHiggs_ModelParameters(hb_ModelParameters &result)
    {
      using namespace Pipes::MSSMHiggs_ModelParameters;

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Set the CP of the Higgs states.
      for (int i = 0; i < 3; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

      // Retrieve higgs partial widths
      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(3);
      const DecayTable::Entry& H_plus_widths = Dep::Higgs_Couplings->get_charged_decays(0);
      const DecayTable::Entry& t_widths = Dep::Higgs_Couplings->get_t_decays();

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

      // Retrieve cross-section ratios from the HiggsCouplingsTable
      set_CS(result, *Dep::Higgs_Couplings, 3);
    }


    /// Get a LEP chisq from HiggsBounds
    void calc_HB_LEP_LogLike(double &result)
    {
      using namespace Pipes::calc_HB_LEP_LogLike;

      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;

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

      BEreq::HiggsBounds_charged_input(&ModelParam.MHplus[0], &ModelParam.HpGammaTot[0], &ModelParam.CS_lep_HpjHmi_ratio[0],
               &ModelParam.BR_tWpb, &ModelParam.BR_tHpjb[0], &ModelParam.BR_Hpjcs[0],
               &ModelParam.BR_Hpjcb[0], &ModelParam.BR_Hptaunu[0]);

      BEreq::HiggsBounds_set_mass_uncertainties(&ModelParam.deltaMh[0],&ModelParam.deltaMHplus[0]);

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

      // run Higgs bounds 'classic'
       double obsratio;
       int HBresult, chan, ncombined;

      BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);
      
      // previous routine to find likelihood
      /*
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
      */

      #ifdef COLLIDERBIT_DEBUG
        std::cout << "HB output: " << std::endl << \
        "hbres: " << HBresult << std::endl << \
        "hbchan: "<< chan << std::endl << \
        "hbobs: " << obsratio << std::endl << \
        "hbcomb: " << ncombined << std::endl;
      #endif

      if (HBresult != -1) {
      		// if (obsratio<1.0) result = 0.0;
      		// else result = -pow((obsratio - 1.0),2);
          result = -pow((obsratio),2);
      }
      else {
        std::ostringstream err;
        err << "HB_LEP_Likelihood is invalid." << std::endl;
        invalid_point().raise(err.str());
      }
      
    }

    /// Get an LHC chisq from HiggsSignals
    void calc_HS_LHC_LogLike(double &result)
    {
      using namespace Pipes::calc_HS_LHC_LogLike;

      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;

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

      BEreq::HiggsBounds_charged_input_HS(&ModelParam.MHplus[0], &ModelParam.HpGammaTot[0], &ModelParam.CS_lep_HpjHmi_ratio[0],
            &ModelParam.BR_tWpb, &ModelParam.BR_tHpjb[0], &ModelParam.BR_Hpjcs[0],
            &ModelParam.BR_Hpjcb[0], &ModelParam.BR_Hptaunu[0]);

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
         ModelParam.MHplus[0] << " " <<
         ModelParam.HpGammaTot[0] << " " <<
         ModelParam.CS_lep_HpjHmi_ratio[0] << " " <<
         ModelParam.BR_Hpjcs[0] << " " <<
         ModelParam.BR_Hpjcb[0] << " " <<
         ModelParam.BR_Hptaunu[0] << " " <<
         ModelParam.BR_tWpb << " " <<
         ModelParam.BR_tHpjb[0] << "\n";
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
         ModelParam.MHplus[0] << std::setw(w) <<
         ModelParam.HpGammaTot[0] << std::setw(w) <<
         ModelParam.CS_lep_HpjHmi_ratio[0] << std::setw(w) <<
         ModelParam.BR_Hpjcs[0] << std::setw(w) <<
         ModelParam.BR_Hpjcb[0] << std::setw(w) <<
         ModelParam.BR_Hptaunu[0] << std::setw(w) <<
         ModelParam.BR_tWpb << std::setw(w) <<
         ModelParam.BR_tHpjb[0];
        f.close();
      #endif

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
    // * is this required?
    // void THDMHiggs_gambit_ModelParameters(Higgs_ModelParameters &result)
    // {
    //   using namespace Pipes::THDMHiggs_gambit_ModelParameters;
    //   Spectrum fullspectrum = *Dep::THDM_spectrum;
    //   const SubSpectrum& he = fullspectrum.get_HE();
    //   result.reset();
    //   result.nh = 3;
    //   result.add_higgs(he.get(Par::mass1,"mh0"),0.0,1);
    //   result.add_higgs(he.get(Par::mass1,"mH0"),0.0,1);
    //   result.add_higgs(he.get(Par::mass1,"mA"),0.0,-1);
    //   result.add_charged_higgs(he.get(Par::mass1,"mC"),0.0);
    // }

    void fill_THDM_HiggsBounds_model_parameters(hb_ModelParameters &result)
    {
      using namespace Pipes::fill_THDM_HiggsBounds_model_parameters;
      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      // unpack THDM Couplings
      const thdmc_couplings THDM_couplings = *Dep::THDM_couplings;
      const std::vector<thdmc_couplings> THDM_couplings_SM_like = *Dep::THDM_couplings_SM_like_model;
      const thdmc_decay_widths THDM_decay_widths = *Dep::THDM_decay_widths;
      const std::vector<thdmc_decay_widths> THDM_decay_widths_SM_like = *Dep::THDM_decay_widths_SM_like_model;
      const thdmc_total_widths THDM_total_widths = *Dep::THDM_total_widths;

      const SubSpectrum& he = fullspectrum.get_HE();
      const SubSpectrum& SM = fullspectrum.get_LE();
      const SMInputs& sminputs = fullspectrum.get_SMInputs();

      // ---
      // adapted from 2HDMC code - Constraints.cpp
      double RWW=0.77; 
      double RZZ=1.0-RWW;

      double MZ = SM.get(Par::Pole_Mass,"Z0"), MW = SM.get(Par::Pole_Mass,"W+");

      double GF = sminputs.GF;
      double v = 1./sqrt(sqrt(2)*GF);
      double g = 2.*MW/v;

      double sintw = sqrt(1.-MW*MW/(MZ*MZ));
      double costw = sqrt(1.-sintw*sintw);

      complex <double> c,cs,cp,cs_sm,cp_sm,cst,cpt,cst_sm,cpt_sm;

      result.Mh[0] = he.get(Par::Pole_Mass, "h0", 1);
      result.Mh[1] = he.get(Par::Pole_Mass, "h0", 2);
      result.Mh[2] = he.get(Par::Pole_Mass,"A0");
      result.MHplus[0] = he.get(Par::Pole_Mass,"H+");

      bool has_high_err = he.has(Par::Pole_Mass_1srd_high, 25, 0);
      bool has_low_err = he.has(Par::Pole_Mass_1srd_low, 25, 0);
      if (has_high_err and has_low_err)
      {
        double upper = he.get(Par::Pole_Mass_1srd_high, 25, 0);
        double lower = he.get(Par::Pole_Mass_1srd_low, 25, 0);
        result.deltaMh[0] = result.Mh[0] * std::max(upper,lower);
      }
      else
      {
        result.deltaMh[0] = 0.;
      }

      result.deltaMh[1] = 0.0;
      result.deltaMh[2] = 0.0;

      result.deltaMHplus[0] = 0.0;

      result.CP[0] = 1;
      result.CP[1] = 1;
      result.CP[2] = -1;

      for (int h=0; h<3; h++) {

        result.hGammaTot[h] = THDM_total_widths.gamma_tot_h[h+1];

        result.BR_hjss[h] = THDM_decay_widths.gamma_hdd[h+1][2][2]/result.hGammaTot[h];
        result.BR_hjcc[h] = THDM_decay_widths.gamma_huu[h+1][2][2]/result.hGammaTot[h];
        result.BR_hjbb[h] = THDM_decay_widths.gamma_hdd[h+1][3][3]/result.hGammaTot[h];
        result.BR_hjtautau[h] = THDM_decay_widths.gamma_hll[h+1][3][3]/result.hGammaTot[h];
        result.BR_hjmumu[h] = THDM_decay_widths.gamma_hll[h+1][2][2]/result.hGammaTot[h];
        result.BR_hjWW[h] = THDM_decay_widths.gamma_hvv[h+1][3]/result.hGammaTot[h];
        result.BR_hjZZ[h] = THDM_decay_widths.gamma_hvv[h+1][2]/result.hGammaTot[h];
        result.BR_hjZga[h] = THDM_decay_widths.gamma_hZga[h+1]/result.hGammaTot[h];
        result.BR_hjgg[h] = THDM_decay_widths.gamma_hgg[h+1]/result.hGammaTot[h];
        result.BR_hjgaga[h] = THDM_decay_widths.gamma_hgaga[h+1]/result.hGammaTot[h];


        for (int h2=0; h2<3; h2++) {

          result.BR_hjhihi[h2][h] = THDM_decay_widths.gamma_hhh[h+1][h2+1][h2+1]/result.hGammaTot[h];

          if(result.hGammaTot[h2+1]==0)
          {
            result.BR_hjinvisible[h] = result.BR_hjhihi[h2][h];
          }
          else{ result.BR_hjinvisible[h] = 0; }

          c = THDM_couplings.vhh[2][h2+1][h+1];
          result.CS_lep_hjhi_ratio[h][h2] = pow(abs(c)/(g/2./costw),2);
        }

        c = THDM_couplings.vvh[2][2][h+1];
        result.CS_lep_hjZ_ratio[h]=pow(abs(c)/(g/costw*MZ),2);
        result.CS_dd_hjZ_ratio[h] = result.CS_lep_hjZ_ratio[h];
        result.CS_uu_hjZ_ratio[h] = result.CS_lep_hjZ_ratio[h];
        result.CS_ss_hjZ_ratio[h] = result.CS_lep_hjZ_ratio[h];
        result.CS_cc_hjZ_ratio[h] = result.CS_lep_hjZ_ratio[h];
        result.CS_bb_hjZ_ratio[h] = result.CS_lep_hjZ_ratio[h];

        result.CS_gg_hjZ_ratio[h]=0.;

        c = THDM_couplings.vvh[3][3][h+1];
        result.CS_ud_hjWp_ratio[h] = pow(abs(c)/(g*MW),2);
        result.CS_ud_hjWm_ratio[h] = result.CS_ud_hjWp_ratio[h];
        result.CS_cs_hjWp_ratio[h] = result.CS_ud_hjWp_ratio[h];
        result.CS_cs_hjWm_ratio[h] = result.CS_ud_hjWp_ratio[h];

        result.CS_tev_vbf_ratio[h] = RWW*result.CS_ud_hjWp_ratio[h]+RZZ*result.CS_dd_hjZ_ratio[h];

        result.CS_gg_hj_ratio[h] = THDM_decay_widths.gamma_hgg[h+1]/THDM_decay_widths_SM_like[h].gamma_hgg[1];

        cs = THDM_couplings.hdd_cs[h+1][3][3];
        cp = THDM_couplings.hdd_cp[h+1][3][3];
        cs_sm = THDM_couplings_SM_like[h].hdd_cs[1][3][3];
        cp_sm = THDM_couplings_SM_like[h].hdd_cp[1][3][3];

        result.CS_bb_hj_ratio[h]=pow(abs(cs/cs_sm),2)+pow(abs(cp/cs_sm),2);
        result.CS_bg_hjb_ratio[h]=result.CS_bb_hj_ratio[h];
        result.CS_lep_bbhj_ratio[h] = result.CS_bb_hj_ratio[h];

        result.CS_lep_tautauhj_ratio[h] = THDM_decay_widths.gamma_hll[h+1][3][3]/THDM_decay_widths_SM_like[h].gamma_hll[1][3][3];

        cst = THDM_couplings.huu_cs[h+1][3][3];
        cpt = THDM_couplings.huu_cp[h+1][3][3];
        cst_sm = THDM_couplings_SM_like[h].huu_cs[1][3][3];
        cpt_sm = THDM_couplings_SM_like[h].huu_cp[1][3][3];

        // std::cout << "ColliderBit_Higgs.cpp higgsbounds filling: " << " " << cst << " " << cst_sm << " " << cpt << std::endl;

        result.CS_tev_tthj_ratio[h] = pow(abs(cst/cst_sm),2)+pow(abs(cpt/cst_sm),2);

        result.CS_lhc7_vbf_ratio[h] = result.CS_tev_vbf_ratio[h];
        result.CS_lhc8_vbf_ratio[h] = result.CS_tev_vbf_ratio[h];
        result.CS_lhc7_tthj_ratio[h] = result.CS_tev_tthj_ratio[h];
        result.CS_lhc8_tthj_ratio[h] = result.CS_tev_tthj_ratio[h];

      }

      result.HpGammaTot[0] = THDM_total_widths.gamma_tot_h[4];

      result.CS_lep_HpjHmi_ratio[0] = 1.;

      result.BR_tWpb = THDM_total_widths.gamma_tot_t_SM_contrib/THDM_total_widths.gamma_tot_t;
      result.BR_tHpjb[0]= THDM_decay_widths.gamma_uhd[3][4][3]/THDM_total_widths.gamma_tot_t;
      result.BR_Hpjcs[0] = THDM_decay_widths.gamma_hdu[4][2][2]/THDM_total_widths.gamma_tot_h[4];
      result.BR_Hpjcb[0] = THDM_decay_widths.gamma_hdu[4][3][2]/THDM_total_widths.gamma_tot_h[4];
      result.BR_Hptaunu[0] = THDM_decay_widths.gamma_hln[4][3][3]/THDM_total_widths.gamma_tot_h[4];
      // ---
    }


    void SM_higgs_mass_likelihood(double &result) {
      using namespace Pipes::SM_higgs_mass_likelihood;
      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      const double mh = fullspectrum.get(Par::mass1, "h0", 1); // Higgs boson mass - GeV
      const double mh_pole = fullspectrum.get(Par::Pole_Mass, "h0", 1); // Higgs boson mass - GeV
      double massSMHiggs = 125.09;
      double h_sigma = 0.32;

      #ifdef COLLIDERBIT_DEBUG
        std::cout << "SM higgs mass likelihood debug output" << std::endl \
        << "mh= " << fullspectrum.get(Par::mass1, "h0", 1) << std::endl \
        << "Lam1= " << fullspectrum.get(Par::mass1, "Lambda_1") << std::endl \
        << "Lam2= " << fullspectrum.get(Par::mass1, "Lambda_2") << std::endl \
        << "Lam3= " << fullspectrum.get(Par::mass1, "Lambda_3") << std::endl \
        << "Lam4= " << fullspectrum.get(Par::mass1, "Lambda_4") << std::endl \
        << "Lam5= " << fullspectrum.get(Par::mass1, "Lambda_5") << std::endl \
        << "Lam6= " << fullspectrum.get(Par::mass1, "Lambda_6") << std::endl \
        << "Lam7= " << fullspectrum.get(Par::mass1, "Lambda_7") << std::endl \
        << "mHp= " << fullspectrum.get(Par::mass1, "H+") << std::endl \
        << "alpha= " << fullspectrum.get(Par::dimensionless, "alpha") << std::endl; \
        std::cout << "mass1: " << mh << " Pole_mass: " << mh_pole << std::endl;
        std::unique_ptr<SubSpectrum> he = fullspectrum.clone_HE();
        he -> RunToScale(750.0);
        std::cout << "SM higgs mass likelihood debug output" << std::endl \
        << "mh= " << he->get(Par::mass1, "h0", 1) << std::endl \
        << "Lam1= " << he->get(Par::mass1, "Lambda_1") << std::endl \
        << "Lam2= " << he->get(Par::mass1, "Lambda_2") << std::endl \
        << "Lam3= " << he->get(Par::mass1, "Lambda_3") << std::endl \
        << "Lam4= " << he->get(Par::mass1, "Lambda_4") << std::endl \
        << "Lam5= " << he->get(Par::mass1, "Lambda_5") << std::endl \
        << "Lam6= " << he->get(Par::mass1, "Lambda_6") << std::endl \
        << "Lam7= " << he->get(Par::mass1, "Lambda_7") << std::endl \
        << "mHp= " << he->get(Par::mass1, "H+") << std::endl \
        << "alpha= " << he->get(Par::dimensionless, "alpha") << std::endl; \
        std::cout << "mass1: " << he->get(Par::mass1, "h0", 1) << " Pole_mass: " << he->get(Par::Pole_Mass, "h0", 1) << std::endl;

      #endif

      

      result = - pow( (mh - massSMHiggs) / h_sigma,2);
    } 

    // ---------------
    // HS debug likelihood
    // original author Miguel Nebot
    // used here only to debug code
    // NB: not to be included in release

    typedef double obs; // Standard observable/other quantity
    typedef complex<double> obs_c; // Complex observable/other quantity

    obs_c f_triangle(double x)
    {
      std::complex<double> i(0,1);
      if (x>=1.0)
        {return pow(asin(1.0/sqrt(x)),2);}
      else
        {obs_c temp; temp=log((1.0+sqrt(1.0-x))/(1.0-sqrt(1.0-x))) - i*M_PI; return -0.25*temp*temp;}
    }

    // --------------------------------------------------
    obs_c AF(double x)
    {
      return -2.0*x*(1.0+(1.0-x)*f_triangle(x));
    }
    // --------------------------------------------------

    // --------------------------------------------------
    obs_c AFhat(double x)
    {
      return -2.0*x*f_triangle(x);
    }
    // --------------------------------------------------

    // --------------------------------------------------
    obs_c AV(double x)
    {
      return 2.0+3.0*x+3.0*x*(2.0-x)*f_triangle(x);
    }
    // --------------------------------------------------

    // --------------------------------------------------
    obs_c AS(double x)
    {
      return x*(1.0-x*f_triangle(x));
    }


    void HS_debug_likelihood(double &result)
    {
      using namespace Pipes::HS_debug_likelihood;
      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      // unpack THDM Couplings
      const thdmc_couplings THDM_couplings = *Dep::THDM_couplings;
      const std::vector<thdmc_couplings> THDM_couplings_SM_like = *Dep::THDM_couplings_SM_like_model;
      const thdmc_decay_widths THDM_decay_widths = *Dep::THDM_decay_widths;
      const std::vector<thdmc_decay_widths> THDM_decay_widths_SM_like = *Dep::THDM_decay_widths_SM_like_model;
      const thdmc_total_widths THDM_total_widths = *Dep::THDM_total_widths;

      const SubSpectrum& he = fullspectrum.get_HE();
      const SubSpectrum& SM = fullspectrum.get_LE();
      const SMInputs& sminputs = fullspectrum.get_SMInputs();

      // returns a vector of likelihoods grouped by decay channels.
      // Unpacking THDM Parameters & SM Oject
      // double mh, mH, mA, mC, sba, labmbda6, lambda7, m122, tan_beta;
      // THDMObject.get_param_phys(mh, mH, mA, mC, sba, lambda6, lambda7, m122,tan_beta);

      double RWW=0.77; 
      double RZZ=1.0-RWW;
      double GF = sminputs.GF;
      vector<double> likelihoods;

      // --------------------------------------------------
      // Pieces of code for Higgs signals
      // --------------------------------------------------
      // 1- Declarations: constants, experimental constraints, variables
      // 2- Loop functions for h->gg,GG: definition
      // 3- Computation of SM factors for Higgs decays, only once
      // 4- Computations in fit/MCMC
      // --------------------------------------------------

      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // BEGIN: Declarations: constants, experimental constraints, variables
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // N.B. 'obs' and 'obs_c' are just 'double' and 'double complex':
      // typedef double obs; // Standard observable/other quantity
      // typedef complex<double> obs_c; // Complex observable/other quantity

      // Constants
      obs const VEV = 1./sqrt(sqrt(2)*GF); //v^2 Higgs VEV GeV
      obs const M_w = SM.get(Par::Pole_Mass,"W+"); // W boson mass - GeV
      obs const M_z = SM.get(Par::Pole_Mass,"Z0"); //Z boson mass - GeV

      obs const Mz2 = pow(M_z,2), Mw2 = pow(M_w,2);
      obs const m_h = he.get(Par::Pole_Mass, "h0", 1); // Higgs boson mass - GeV
      obs const mh2_VEV2 = pow(m_h/VEV,2); // (Higgs boson mass/VEV)^2
      obs const mh2 = pow(m_h,2);
      obs const xh = mh2/Mw2, yh = mh2/Mz2;

      double mu = SM.get(Par::mass1, "u_1");
      double mc = SM.get(Par::mass1, "u_2");
      double mt = SM.get(Par::mass1, "u_3");

      double md = SM.get(Par::mass1, "d_1");
      double ms = SM.get(Par::mass1, "d_2");
      double mb = SM.get(Par::mass1, "d_3");

      // Quark masses, running Mz (GeV)
      obs const m_qu = mu;
      obs const m_qc = mc;
      obs const m_qt = mt;
      obs const m_qd = md;
      obs const m_qs = ms;
      obs const m_qb = mb;
      obs const x_qu = pow(m_qu/M_w,2), y_qu = pow(m_qu/M_z,2), xh_qu = pow(2.0*m_qu/m_h,2);
      obs const x_qc = pow(m_qc/M_w,2), y_qc = pow(m_qc/M_z,2), xh_qc = pow(2.0*m_qc/m_h,2);
      obs const x_qt = pow(m_qt/M_w,2), y_qt = pow(m_qt/M_z,2), xh_qt = pow(2.0*m_qt/m_h,2);
      obs const x_qd = pow(m_qd/M_w,2), y_qd = pow(m_qd/M_z,2), xh_qd = pow(2.0*m_qd/m_h,2);
      obs const x_qs = pow(m_qs/M_w,2), y_qs = pow(m_qs/M_z,2), xh_qs = pow(2.0*m_qs/m_h,2);
      obs const x_qb = pow(m_qb/M_w,2), y_qb = pow(m_qb/M_z,2), xh_qb = pow(2.0*m_qb/m_h,2);

      // Lepton masses
      obs const m_le = SM.get(Par::Pole_Mass, "e-_1");
      obs const m_lm = SM.get(Par::Pole_Mass, "e-_2");
      obs const m_lt = SM.get(Par::Pole_Mass, "e-_3");
      obs const x_le = pow(m_le/M_w,2), y_le = pow(m_le/M_z,2), xh_le = pow(2.0*m_le/m_h,2);
      obs const x_lm = pow(m_lm/M_w,2), y_lm = pow(m_lm/M_z,2), xh_lm = pow(2.0*m_lm/m_h,2);
      obs const x_lt = pow(m_lt/M_w,2), y_lt = pow(m_lt/M_z,2), xh_lt = pow(2.0*m_lt/m_h,2);

      // Higgs decay widths
      obs G_h_qd_gFC, BR_h_qd_gFC;
      obs G_h_qs_gFC, BR_h_qs_gFC, SM_factor_G_h_qs;
      obs G_h_qb_gFC, BR_h_qb_gFC, SM_factor_G_h_qb;
      obs G_h_qu_gFC, BR_h_qu_gFC;
      obs G_h_qc_gFC, BR_h_qc_gFC, SM_factor_G_h_qc;
      obs G_h_le_gFC, BR_h_le_gFC;
      obs G_h_lm_gFC, BR_h_lm_gFC, SM_factor_G_h_lm;
      obs G_h_lt_gFC, BR_h_lt_gFC, SM_factor_G_h_lt;
      obs G_h_GG_gFC, BR_h_GG_gFC, SM_factor_G_h_GG, factor_G_h_GG;
      obs G_h_WW_gFC, BR_h_WW_gFC;
      obs G_h_ZZ_gFC, BR_h_ZZ_gFC;
      obs factor_h_VV;
      obs G_h_gg_gFC, BR_h_gg_gFC, SM_factor_G_h_gg, factor_G_h_gg;
      //obs BR_h_gZ, BR_h_gZ_gFC;
      // Full width
      obs G_h_gFC;

      // h->ff constant
      obs const C_hff = m_h / 8.0 / M_PI;

      // Production K-factors
      obs K_prod_ggF, K_prod_VBF, K_prod_WH, K_prod_ZH, K_prod_ttH;
      // Decay K-factors
      obs K_decay_gg, K_decay_ZZ, K_decay_WW, K_decay_lt, K_decay_qb;
      // Higgs signals
      obs HiggsSignals_Run1_production[5];
      obs HiggsSignals_Run1_decay[5];
      obs HiggsSignals_Run1[5][5];

      // Loop functions for h->gg,GG
      obs_c AF_qu, AF_qc, AF_qt, AF_qd, AF_qs, AF_qb, AF_le, AF_lm, AF_lt;
      obs_c AFhat_qu, AFhat_qc, AFhat_qt, AFhat_qd, AFhat_qs, AFhat_qb, AFhat_le, AFhat_lm, AFhat_lt;
      // obs_c AF_qt;
      // obs_c AFhat_qt
      obs_c AV_W;

      // Fermion scalar and pseudoscalar couplings
      obs a_qu, b_qu;
      obs a_qc, b_qc;
      obs a_qt, b_qt;
      obs a_qd, b_qd;
      obs a_qs, b_qs;
      obs a_qb, b_qb;
      obs a_le, b_le;
      obs a_lm, b_lm;
      obs a_lt, b_lt;

      // Auxiliary/temp
      obs_c aux_c;
      double temp;

      // Higgs production mechanisms, cross sections from 1307.1347 for mH=125.0 GeV
      // cross sections in pb
      // xs_ggH: gluon-gluon fusion
      // xs_VBF: vector boson fusion
      // xs_WH & xs_ZH: bremstrahlung
      // xs_ttH: top anti-top associated
      // xs_bbH: b anti-b associated
      obs const xs_8_ggH_SM = 19.27;
      obs const xs_8_VBF_SM = 1.578;
      obs const xs_8_WH_SM = 0.7046;
      obs const xs_8_ZH_SM = 0.4153;
      obs const xs_8_ttH_SM = 0.1293;
      obs const xs_8_bbH_SM = 0.2035;
      obs const xs_13_ggH_SM = 43.92;
      obs const xs_13_VBF_SM = 3.748;
      obs const xs_13_WH_SM = 1.380;
      obs const xs_13_ZH_SM = 0.8696;
      obs const xs_13_ttH_SM = 0.5085;
      obs const xs_13_bbH_SM = 0.5116;
      obs const xs_14_ggH_SM = 49.47;
      obs const xs_14_VBF_SM = 4.233;
      obs const xs_14_WH_SM = 1.522;
      obs const xs_14_ZH_SM = 0.969;
      obs const xs_14_ttH_SM = 0.6113;
      obs const xs_14_bbH_SM = 0.5805;

      // Higgs decays, branching ratios
      // from 1307.1347 for mH=125.0 GeV
      obs const BR_h_qs_SM = 0.000246;
      obs const BR_h_qc_SM = 0.0291;
      obs const BR_h_lm_SM = 0.000219;
      obs const BR_h_GG_SM = 0.0857;
      obs const BR_h_gZ_SM = 0.00154;
      // for mH=125.1 GeV
      obs const BR_h_WW_SM = 0.216;
      obs const BR_h_ZZ_SM = 0.0267;
      obs const BR_h_gg_SM = 0.00228;
      obs const BR_h_qb_SM = 0.575;
      obs const BR_h_lt_SM = 0.0630;
      obs const G_h_SM = 0.00408; // Higgs width (GeV)

      // Higgs Signal Strengths Run 1
      // ATLAS+CMS combination, arXiv:1606.02266, Table 8

      // For quantities not measured
      double const No_EXP_VAL = 1.0;
      double const No_EXP_VAL_UNC = 1.0e8;
      // --------------------------------------------------
      double HiggsSignals_EXP_VAL[5][5] = {{1.1, 1.3, 0.5, 0.5, 2.2}, {1.13, 0.1, No_EXP_VAL, No_EXP_VAL, No_EXP_VAL}, {0.84, 1.2, 1.6, 5.9, 5.0}, {1.0, 1.3, -1.4, 2.2, -1.9}, {No_EXP_VAL, No_EXP_VAL, 1.0, 0.4, 1.1}};
      // -------------------------
      double HiggsSignals_EXP_UNC_sup[5][5] = {{0.23, 0.5, 1.3, 3.0, 1.6}, {0.34, 1.1, No_EXP_VAL_UNC, No_EXP_VAL_UNC, No_EXP_VAL_UNC}, {0.17, 0.4, 1.2, 2.6, 1.8}, {0.6, 0.4, 1.4, 2.2, 3.7}, {No_EXP_VAL, No_EXP_VAL, 0.5, 0.4, 1.0}};
      // -------------------------
      double HiggsSignals_EXP_UNC_inf[5][5] = {{0.22, 0.5, 1.2, 2.5, 1.3}, {0.31, 0.6, No_EXP_VAL_UNC, No_EXP_VAL_UNC, No_EXP_VAL_UNC}, {0.17, 0.4, 1.0, 2.2, 1.7}, {0.6, 0.4, 1.4, 1.8, 3.3}, {No_EXP_VAL, No_EXP_VAL, 0.5, 0.4, 1.0}};
      // --------------------------------------------------
      // In all, ordering is:
      // Arrays (decays): {gamma-gamma, ZZ, WW, tau-tau, bb}
      // Elements in sub-array (production): {ggF, VBF, WH, ZH, ttH}
      // i.e. Table 8 from reference but transposed
      // --------------------------------------------------

      // Additional Higgs constraints

      // // Full width bound from 1605.02329
      // obs G_h_bound_VAL = 0.015, G_h_bound_UNC = 0.001; // (GeV)
      // H->mu+mu- width bound from
      obs BR_h_mm_bound_VAL = 3.0, BR_h_mm_bound_UNC = 0.2;
      // H->e+e- width bound from
      // Same as muons
      // obs BR_h_ee_bound_VAL = , BR_h_ee_bound_UNC = ;

      // h->bb
      // 1709.07497 CMS
      double mu_hbb_VH_CMS_VAL = 1.2, mu_hbb_VH_CMS_UNC = 0.4; // coincides with ATLAS
      // 1708.03299 ATLAS
      double mu_hbb_VH_ATLAS_VAL = 1.2, mu_hbb_VH_ATLAS_UNC = 0.4;

      // h->tautau
      // 1708.00373, Fig.21
      double mu_htt_VBF_CMS_VAL = 1.11, mu_htt_VBF_CMS_UNC = 0.34;
      double mu_htt_ggF_CMS_VAL = 0.84, mu_htt_ggF_CMS_UNC = 0.89;

      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // END: Declarations: constants, experimental constraints, variables
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------


      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // BEGIN: Computation of SM factors for Higgs decays, only once
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
        // temp auxiliary complex double
        obs_c aux_c_0 = (0,0);
        // aux_c_0.real() = 0.0; aux_c_0.imag() = 0.0;

        // Decays
        SM_factor_G_h_qc = (1.0-xh_qc) * pow(m_qc/VEV,2);
        SM_factor_G_h_qs = (1.0-xh_qs) * pow(m_qs/VEV,2);
        SM_factor_G_h_qb = (1.0-xh_qb) * pow(m_qb/VEV,2);
        SM_factor_G_h_lm = (1.0-xh_lm) * pow(m_lm/VEV,2);
        SM_factor_G_h_lt = (1.0-xh_lt) * pow(m_lt/VEV,2);

        // Loop functions for h->gg,GG
        // Including v/m prefactor for fermions
        AF_qu = VEV/m_qu*AF(xh_qu); AFhat_qu = VEV/m_qu*AFhat(xh_qu);
        AF_qc = VEV/m_qc*AF(xh_qc); AFhat_qc = VEV/m_qc*AFhat(xh_qc);
        AF_qt = VEV/m_qt*AF(xh_qt); AFhat_qt = VEV/m_qt*AFhat(xh_qt);
        AF_qd = VEV/m_qd*AF(xh_qd); AFhat_qd = VEV/m_qd*AFhat(xh_qd);
        AF_qs = VEV/m_qs*AF(xh_qs); AFhat_qs = VEV/m_qs*AFhat(xh_qs);
        AF_qb = VEV/m_qb*AF(xh_qb); AFhat_qb = VEV/m_qb*AFhat(xh_qb);
        AF_le = VEV/m_le*AF(xh_le); AFhat_le = VEV/m_le*AFhat(xh_le);
        AF_lm = VEV/m_lm*AF(xh_lm); AFhat_lm = VEV/m_lm*AFhat(xh_lm);
        AF_lt = VEV/m_lt*AF(xh_lt); AFhat_lt = VEV/m_lt*AFhat(xh_lt);
        AV_W = AV(4.0*Mw2/mh2);

        // h->gamma+gamma
        aux_c = 4.0/3.0 * m_qt/VEV * AF_qt;
        aux_c += AV_W;
        //  aux_c += 4.0/3.0 * m_qu/VEV * AF_qu;
        //  aux_c += 4.0/3.0 * m_qc/VEV * AF_qc;
        //  aux_c += 1.0 / 3.0 * m_qd/VEV * AF_qd;
        //  aux_c += 1.0 / 3.0 * m_qs/VEV * AF_qs;
        //  aux_c += 1.0 / 3.0 * m_qb/VEV * AF_qb;
        //  aux_c += m_le/VEV * AF_le;
        //  aux_c += m_lm/VEV * AF_lm;
        //  aux_c += m_lt/V;EV * AF_lt;
        SM_factor_G_h_gg = pow(abs(aux_c),2);

        // h->gluon+gluon
        aux_c = m_qt/VEV * AF_qt;
        //  aux_c += m_qu/VEV * AF_qu;
        //  aux_c += m_qc/VEV * AF_qc;
        //  aux_c += m_qd/VEV * AF_qd;
        //  aux_c += m_qs/VEV * AF_qs;
        //  aux_c += m_qb/VEV * AF_qb;
        SM_factor_G_h_GG = pow(abs(aux_c),2);
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // END: Computation of SM factors for Higgs decays, only once
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------



      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // BEGIN: Computations in fit/MCMC
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
        double sab = sin(atan(he.get(Par::dimensionless, "tanb"))-he.get(Par::dimensionless, "alpha"));
        double cab = sqrt(1-sab*sab);

        // no diagonal contributions here
        // no extra contributions in this 
        // complex<double> n_qu = (0,0);//convertYukawaNotation(THDMObject, Cube, yuu);
        // complex<double> n_qc = (0,0); //convertYukawaNotation(THDMObject, Cube, ycc);
        // complex<double> n_qt = (0,0); //convertYukawaNotation(THDMObject, Cube, ytt);
        // complex<double> n_qd = (0,0); //convertYukawaNotation(THDMObject, Cube, ydd);
        // complex<double> n_qs = (0,0); //convertYukawaNotation(THDMObject, Cube, yss);
        // complex<double> n_qb = (0,0); //convertYukawaNotation(THDMObject, Cube, ybb);
        // complex<double> n_le = (0,0);
        // complex<double> n_lm = (0,0);
        // complex<double> n_lt = (0,0);

        // complex<double> n_qbs = convertYukawaNotation(THDMObject, Cube, ybs);
        // complex<double> n_qsb = convertYukawaNotation(THDMObject, Cube, ysb);


        // n couplings below are the diagonal elements of the combination of Yukawa matrices that couples to H_2 with <H_2>=0 in the Higgs basis
        // Fermion scalar-pseudoscalar couplings
        a_qu = he.get(Par::dimensionless, "Yu",1,1);
        a_qc = he.get(Par::dimensionless, "Yu",2,2);
        a_qt = he.get(Par::dimensionless, "Yu",3,3);
        a_qd = he.get(Par::dimensionless, "Yd",1,1);
        a_qs = he.get(Par::dimensionless, "Yd",2,2);
        a_qb = he.get(Par::dimensionless, "Yu",3,3);
        a_le = he.get(Par::dimensionless, "Ye",1,1);
        a_lm = he.get(Par::dimensionless, "Ye",2,2);
        a_lt = he.get(Par::dimensionless, "Ye",3,3);

        // Vector boson couplings
        factor_h_VV = sab;

        // Decay widths
        G_h_WW_gFC = THDM_decay_widths.gamma_hvv[1][3];
        //G_h_SM * BR_h_WW_SM * pow(factor_h_VV,2);
        G_h_ZZ_gFC = THDM_decay_widths.gamma_hvv[1][2];
        //G_h_SM * BR_h_ZZ_SM * pow(factor_h_VV,2);

        G_h_qs_gFC = THDM_decay_widths.gamma_hdd[1][2][2];
        //( (1.0-xh_qs) * pow(a_qs,2) + pow(b_qs,2) ) / SM_factor_G_h_qs * G_h_SM * BR_h_qs_SM;
        G_h_qb_gFC = THDM_decay_widths.gamma_hdd[1][3][3];
        //( (1.0-xh_qb) * pow(a_qb,2) + pow(b_qb,2) ) / SM_factor_G_h_qb * G_h_SM * BR_h_qb_SM;
        G_h_qc_gFC = THDM_decay_widths.gamma_huu[1][2][2];
        //( (1.0-xh_qc) * pow(a_qc,2) + pow(b_qc,2) ) / SM_factor_G_h_qc * G_h_SM * BR_h_qc_SM;

        G_h_lt_gFC = THDM_decay_widths.gamma_hll[1][3][3];
        //( (1.0-xh_lt) * pow(a_lt,2) + pow(b_lt,2) ) / SM_factor_G_h_lt * G_h_SM * BR_h_lt_SM;
        G_h_lm_gFC = THDM_decay_widths.gamma_hll[1][2][2];
        //( (1.0-xh_lm) * pow(a_lm,2) + pow(b_lm,2) ) / SM_factor_G_h_lm * G_h_SM * BR_h_lm_SM;

        G_h_qu_gFC = THDM_decay_widths.gamma_huu[1][1][1];
        //3.0 * C_hff * sqrt(1.0-xh_qu) * ( (1.0-xh_qu) * pow(a_qu,2) + pow(b_qu,2) );
        G_h_qd_gFC = THDM_decay_widths.gamma_hdd[1][1][1];
        //3.0 * C_hff * sqrt(1.0-xh_qd) * ( (1.0-xh_qd) * pow(a_qd,2) + pow(b_qd,2) );
        G_h_le_gFC = THDM_decay_widths.gamma_hll[1][1][1];
        //C_hff * sqrt(1.0-xh_le) * ( (1.0-xh_le) * pow(a_le,2) + pow(b_le,2) );

        // h->gamma+gamma
        // scalar
        // aux_c = 4.0/3.0 * a_qu * AF_qu;
        // aux_c += 4.0/3.0 * a_qc * AF_qc;
        // aux_c += 4.0/3.0 * a_qt * AF_qt;
        // aux_c += 1.0 / 3.0 * a_qd * AF_qd;
        // aux_c += 1.0 / 3.0 * a_qs * AF_qs;
        // aux_c += 1.0 / 3.0 * a_qb * AF_qb;
        // aux_c += a_le * AF_le;
        // aux_c += a_lm * AF_lm;
        // aux_c += a_lt * AF_lt;
        // aux_c += factor_h_VV * AV_W;
        // factor_G_h_gg = pow(abs(aux_c),2);
        // // pseudoscalar
        // aux_c = 4.0/3.0 * b_qu * AFhat_qu;
        // aux_c += 4.0/3.0 * b_qc * AFhat_qc;
        // aux_c += 4.0/3.0 * b_qt * AFhat_qt;
        // aux_c += 1.0 / 3.0 * b_qd * AFhat_qd;
        // aux_c += 1.0 / 3.0 * b_qs * AFhat_qs;
        // aux_c += 1.0 / 3.0 * b_qb * AFhat_qb;
        // aux_c += b_le * AFhat_le;
        // aux_c += b_lm * AFhat_lm;
        // aux_c += b_lt * AFhat_lt;
        // factor_G_h_gg += pow(abs(aux_c),2);
        // factor_G_h_gg *= 1.0 / SM_factor_G_h_gg;
        // width
        G_h_gg_gFC = THDM_decay_widths.gamma_hvv[1][1];
        // factor_G_h_gg * G_h_SM * BR_h_gg_SM;

        // h->gluon+gluon
      aux_c = a_qt * AF_qt;
      //  aux_c += a_qu * AF_qu;
      //  aux_c += a_qc * AF_qc;
      //  aux_c += a_qd * AF_qd;
      //  aux_c += a_qs * AF_qs;
      //  aux_c += a_qb * AF_qb;
      factor_G_h_GG = pow(abs(aux_c),2);
      aux_c = b_qt * AFhat_qt;
      //  aux_c += b_qu * AFhat_qu;
      //  aux_c += b_qc * AFhat_qc;
      //  aux_c += b_qd * AFhat_qd;
      //  aux_c += b_qs * AFhat_qs;
      //  aux_c += b_qb * AFhat_qb;
      factor_G_h_GG += pow(abs(aux_c),2);
      factor_G_h_GG *= 1.0 / SM_factor_G_h_GG;
        // width
        G_h_GG_gFC = THDM_decay_widths.gamma_hgg[1];
        // factor_G_h_GG * G_h_SM * BR_h_GG_SM;

        // total width
        G_h_gFC = THDM_total_widths.gamma_tot_h[1];
        // G_h_WW_gFC + G_h_ZZ_gFC + G_h_qu_gFC + G_h_qc_gFC + G_h_qd_gFC + G_h_qs_gFC + G_h_qb_gFC + G_h_le_gFC + G_h_lm_gFC + G_h_lt_gFC + G_h_GG_gFC + G_h_gg_gFC;

        // BRs
        BR_h_qd_gFC = G_h_qd_gFC/ G_h_gFC;
        BR_h_qs_gFC = G_h_qs_gFC/ G_h_gFC;
        BR_h_qb_gFC = G_h_qb_gFC/ G_h_gFC;
        BR_h_qu_gFC = G_h_qu_gFC/ G_h_gFC;
        BR_h_qc_gFC = G_h_qc_gFC/ G_h_gFC;
        BR_h_le_gFC = G_h_le_gFC/ G_h_gFC;
        BR_h_lm_gFC = G_h_lm_gFC/ G_h_gFC;
        BR_h_lt_gFC = G_h_lt_gFC/ G_h_gFC;
        BR_h_GG_gFC = G_h_GG_gFC/ G_h_gFC;
        BR_h_WW_gFC = G_h_WW_gFC/ G_h_gFC;
        BR_h_ZZ_gFC = G_h_ZZ_gFC/ G_h_gFC;
        BR_h_gg_gFC = G_h_gg_gFC/ G_h_gFC;

        double BR_h_bb = BR_h_qb_gFC;
        double BR_h_gg = BR_h_gg_gFC;
        double BR_h_WW = BR_h_WW_gFC;
        double BR_h_ZZ = BR_h_ZZ_gFC;
        double BR_h_tt = BR_h_lt_gFC;

        // production K-factors
        K_prod_ggF = factor_G_h_GG;
        K_prod_VBF = pow(factor_h_VV,2);
        K_prod_WH = pow(factor_h_VV,2);
        K_prod_ZH = pow(factor_h_VV,2);
        K_prod_ttH = pow(VEV/m_qt,2)*( pow((a_qt),2) + pow(abs(b_qt),2) );
        HiggsSignals_Run1_production[0] = K_prod_ggF;
        HiggsSignals_Run1_production[1] = K_prod_VBF;
        HiggsSignals_Run1_production[2] = K_prod_WH;
        HiggsSignals_Run1_production[3] = K_prod_ZH;
        HiggsSignals_Run1_production[4] = K_prod_ttH;

        double ggF = factor_G_h_GG;
        double VBF = K_prod_VBF;
        double ttH = K_prod_ttH;

        // decay K-factors
        K_decay_gg = BR_h_gg_gFC / BR_h_gg_SM;
        // cout << "K factor h->gg: " << BR_h_gg_gFC << " / " << BR_h_gg_SM;
        K_decay_ZZ = BR_h_ZZ_gFC / BR_h_ZZ_SM;
        K_decay_WW = BR_h_WW_gFC / BR_h_WW_SM;
        K_decay_lt = BR_h_lt_gFC / BR_h_lt_SM;
        K_decay_qb = BR_h_qb_gFC / BR_h_qb_SM;
        HiggsSignals_Run1_decay[0] = K_decay_gg;
        HiggsSignals_Run1_decay[1] = K_decay_ZZ;
        HiggsSignals_Run1_decay[2] = K_decay_WW;
        HiggsSignals_Run1_decay[3] = K_decay_lt;
        HiggsSignals_Run1_decay[4] = K_decay_qb;

        // Higgs signals
        for (int i_decay=0; i_decay<5; i_decay++)
          {
            for (int i_prod=0; i_prod<5; i_prod++)
        {
          HiggsSignals_Run1[i_decay][i_prod] = HiggsSignals_Run1_decay[i_decay]*HiggsSignals_Run1_production[i_prod];
        }
          }


        // --------------------------------------------------
        // CHI^2
        // --------------------------------------------------
        double chi2 = 0.0;

        // Higgs signals
        // cycle thtough decay channels
        for(int i_decay=0; i_decay<5; i_decay++)
        {
          // cycle through production channels
          for(int i_prod=0; i_prod<5; i_prod++)
          {
            if ( HiggsSignals_Run1[i_decay][i_prod] > HiggsSignals_EXP_VAL[i_decay][i_prod] )
              {
                chi2 += pow( (HiggsSignals_Run1[i_decay][i_prod] - HiggsSignals_EXP_VAL[i_decay][i_prod]) / HiggsSignals_EXP_UNC_sup[i_decay][i_prod], 2);
              }
            else
              {
                chi2 += pow( (HiggsSignals_EXP_VAL[i_decay][i_prod] - HiggsSignals_Run1[i_decay][i_prod]) / HiggsSignals_EXP_UNC_inf[i_decay][i_prod], 2);
              }
            }
            likelihoods.push_back(chi2);
            chi2 = 0.0;
        }

        // Run II bb,tautau
        chi2 = 0.0;
        // bb CMS
        chi2 += pow( ( K_prod_VBF*K_decay_qb - mu_hbb_VH_CMS_VAL) / mu_hbb_VH_CMS_UNC,2);
        // bb ATLAS
        chi2 += pow( ( K_prod_VBF*K_decay_qb - mu_hbb_VH_ATLAS_VAL) / mu_hbb_VH_ATLAS_UNC,2);
        // lt CMS (prod vbf)
        chi2 += pow( ( K_prod_VBF*K_decay_lt - mu_htt_VBF_CMS_VAL) / mu_htt_VBF_CMS_UNC,2);
        // lt CMS (prod gluon)
        chi2 += pow( ( factor_G_h_GG*K_decay_lt - mu_htt_ggF_CMS_VAL) / mu_htt_ggF_CMS_UNC,2);
        likelihoods.push_back(chi2);
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------
      // END: Computations in fit/MCMC
      // ---------------------------------------------------------------------------
      // ---------------------------------------------------------------------------

      double chi2_tot = 0.0;

      // add likelihoods
      for (auto& n : likelihoods){
        chi2_tot += n;
        // std::cout << n << std::endl;
      }

      // width likelihood
      // Full width bound from 1605.02329
      double G_h_bound_VAL = 0.015, G_h_bound_UNC = 0.001; // (GeV)

      // Total width
        if ( G_h_gFC > G_h_bound_VAL )
        {
          chi2_tot += pow( (G_h_gFC - G_h_bound_VAL) / G_h_bound_UNC,2);
          // std::cout << "width h like (before sqrd): " << (G_h_gFC - G_h_bound_VAL) / G_h_bound_UNC << std::endl;
          // std::cout << "width h like (sqrd): " << pow( (G_h_gFC - G_h_bound_VAL) / G_h_bound_UNC,2) << std::endl;
        }

        // mass likelihood
        double massSMHiggs = 125.09; //pm 0.32
        double h_sigma = 0.32;

        chi2_tot += pow( (m_h - massSMHiggs) / h_sigma,2);
        // std::cout << "mass h like (before sqrd): " << (m_h - massSMHiggs) / h_sigma << std::endl;
        // std::cout << "mass h like (sqrd): " << pow( (m_h - massSMHiggs) / h_sigma,2) << std::endl;

      result = -0.5*chi2_tot;

    }

  }
}
