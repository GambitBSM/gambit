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
#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ScannerBit/emulator_utils.hpp"
#include "gambit/Core/emu_map.hpp"
#include "gambit/Elements/emulator_functions.hpp"

//#define COLLIDERBIT_DEBUG


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
      for (std::vector<std::pair<str,str>>::const_iterator it = couplings.invisibles.begin(); it != couplings.invisibles.end(); ++it)
      {
        result.BR_hjinvisible[0] += decays.BF(it->first, it->second);
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

    /// SM-like (SM + possible invisibles) Higgs model parameters for HiggsBounds/Signals
    void SMLikeHiggs_ModelParameters(hb_ModelParameters &result)
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

    /// MSSM-like (MSSM + NMSSM + ...) Higgs model parameters for HiggsBounds/Signals
    void MSSMLikeHiggs_ModelParameters(hb_ModelParameters &result)
    {
      using namespace Pipes::MSSMLikeHiggs_ModelParameters;

      // Set up neutral Higgses
      int n_neutral_higgses = Dep::Higgs_Couplings->get_n_neutral_higgs();

      // Set the CP of the Higgs states.
      for (int i = 0; i < n_neutral_higgses; i++) result.CP[i] = Dep::Higgs_Couplings->CP[i];

      // Retrieve higgs partial widths
      const std::vector<const DecayTable::Entry*>& h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array();
      const DecayTable::Entry& H_plus_widths = Dep::Higgs_Couplings->get_charged_decays(0);
      const DecayTable::Entry& t_widths = Dep::Higgs_Couplings->get_t_decays();

      // Pick the correct spectrum and specify the Higgses
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

      // Neutral higgs masses and errors
      for(int i = 0; i < n_neutral_higgses; i++)
      {
        result.Mh[i] = spec.get(Par::Pole_Mass,sHneut[i]);
        double upper = spec.get(Par::Pole_Mass_1srd_high,sHneut[i]);
        double lower = spec.get(Par::Pole_Mass_1srd_low,sHneut[i]);
        result.deltaMh[i] = result.Mh[i] * std::max(upper,lower);
      }

      // Loop over all neutral Higgses, setting their branching fractions and total widths.
      for(int i = 0; i < n_neutral_higgses; i++)
      {
        result.hGammaTot[i] = h0_widths[i]->width_in_GeV;
        result.BR_hjss[i] = h0_widths[i]->BF("s", "sbar");
        result.BR_hjcc[i] = h0_widths[i]->BF("c", "cbar");
        result.BR_hjbb[i] = h0_widths[i]->BF("b", "bbar");
        result.BR_hjmumu[i] = h0_widths[i]->BF("mu+", "mu-");
        result.BR_hjtautau[i] = h0_widths[i]->BF("tau+", "tau-");
        result.BR_hjWW[i] = h0_widths[i]->has_channel("W+", "W-") ? h0_widths[i]->BF("W+", "W-") : 0.0;
        result.BR_hjZZ[i] = h0_widths[i]->has_channel("Z0", "Z0") ? h0_widths[i]->BF("Z0", "Z0") : 0.0;
        result.BR_hjZga[i] = h0_widths[i]->has_channel("gamma", "Z0") ? h0_widths[i]->BF("gamma", "Z0") : 0.0;
        result.BR_hjgaga[i] = h0_widths[i]->BF("gamma", "gamma");
        result.BR_hjgg[i] = h0_widths[i]->BF("g", "g");
        // Do decays to invisibles
        result.BR_hjinvisible[i] = 0.;
        for (std::vector<std::pair<str,str>>::const_iterator it = Dep::Higgs_Couplings->invisibles.begin(); it != Dep::Higgs_Couplings->invisibles.end(); ++it)
        {
          result.BR_hjinvisible[i] += h0_widths[i]->BF(it->first, it->second);
        }
        // Do decays to other neutral higgses
        for (int j = 0; j < n_neutral_higgses; j++)
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
      set_CS(result, *Dep::Higgs_Couplings, n_neutral_higgses);
    }

    /// Get a LEP chisq from HiggsBounds
    void calc_HB_LEP_LogLike(double &result)
    {
      using namespace Pipes::calc_HB_LEP_LogLike;

      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;

      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
      Farray<double, 1,3, 1,3> BR_hjhihi;
      // Transpose to get around Fortran matrix types
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        ModelParam.CS_lep_hjhi_ratio[j][i] = CS_lep_hjhi_ratio(i+1,j+1);
        ModelParam.BR_hjhihi[j][i] = BR_hjhihi(i+1,j+1);
      }


      BEreq::HiggsBounds_neutral_input_part(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0],
              &ModelParam.CS_lep_hjZ_ratio[0], &ModelParam.CS_lep_bbhj_ratio[0],
              &ModelParam.CS_lep_tautauhj_ratio[0], &ModelParam.CS_lep_hjhi_ratio[0][0],
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
              &ModelParam.BR_hjgg[0], &ModelParam.BR_hjinvisible[0], &ModelParam.BR_hjhihi[0][0]);

      // Transpose it back
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        ModelParam.CS_lep_hjhi_ratio[j][i] = CS_lep_hjhi_ratio(i+1,j+1);
        ModelParam.BR_hjhihi[j][i] = BR_hjhihi(i+1,j+1);
      }


      BEreq::HiggsBounds_charged_input(&ModelParam.MHplus[0], &ModelParam.HpGammaTot[0], &ModelParam.CS_lep_HpjHmi_ratio[0],
               &ModelParam.BR_tWpb, &ModelParam.BR_tHpjb[0], &ModelParam.BR_Hpjcs[0],
               &ModelParam.BR_Hpjcb[0], &ModelParam.BR_Hptaunu[0]);

      BEreq::HiggsBounds_set_mass_uncertainties(&ModelParam.deltaMh[0],&ModelParam.deltaMHplus[0]);

      // run Higgs bounds 'classic'
      double obsratio;
      int HBresult, chan, ncombined;
      BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);

      // extract the LEP chisq
      double chisq_withouttheory,chisq_withtheory;
      int chan2;
      double theor_unc = 1.5; // theory uncertainty
      BEreq::HB_calc_stats(theor_unc,chisq_withouttheory,chisq_withtheory,chan2);

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

      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;

      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
      Farray<double, 1,3, 1,3> BR_hjhihi;
      // Transpose to get around Fortran matrix types
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        ModelParam.CS_lep_hjhi_ratio[j][i] = CS_lep_hjhi_ratio(i+1,j+1);
        ModelParam.BR_hjhihi[j][i] = BR_hjhihi(i+1,j+1);
      }


      BEreq::HiggsBounds_neutral_input_part_HS(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0],
                 &ModelParam.CS_lep_hjZ_ratio[0], &ModelParam.CS_lep_bbhj_ratio[0],
                 &ModelParam.CS_lep_tautauhj_ratio[0], &ModelParam.CS_lep_hjhi_ratio[0][0],
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
                 &ModelParam.BR_hjgg[0], &ModelParam.BR_hjinvisible[0], &ModelParam.BR_hjhihi[0][0]);

      // Transpose it back
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      }
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      {
        ModelParam.CS_lep_hjhi_ratio[j][i] = CS_lep_hjhi_ratio(i+1,j+1);
        ModelParam.BR_hjhihi[j][i] = BR_hjhihi(i+1,j+1);
      }


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
    void FeynHiggs_HiggsProd(fh_HiggsProd_container &result)
    {
      using namespace Pipes::FeynHiggs_HiggsProd;

      Farray<fh_real, 1,52> prodxs;

      fh_HiggsProd_container HiggsProd;
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

    /// Emulator input: the MSSM parameters that actually drive the SusHi
    /// cross section (stop/sbottom sector controls the SUSY-QCD loop
    /// corrections, tanb/mu/At/Ab control bottom-Yukawa enhancement of bbh,
    /// mh sets the phase space / parton luminosities).
    void getSusHi_h_xsec_total_EmulatorTranslateInput(std::vector<double>& input)
    {
      const Spectrum& mySpec = *Pipes::getSusHi_h_xsec_total::Dep::MSSM_spectrum;
      double tanb    = mySpec.get(Par::dimensionless, "tanbeta");
      double mh      = mySpec.get(Par::Pole_Mass, "h0_1");
      double M3_val  = mySpec.get(Par::mass1, "M3");
      double mu_val  = mySpec.get(Par::mass1, "Mu");
      double Yu33    = mySpec.get(Par::dimensionless, "Yu", 3, 3);
      double TYu33   = mySpec.get(Par::mass1, "TYu", 3, 3);
      double Yd33    = mySpec.get(Par::dimensionless, "Yd", 3, 3);
      double TYd33   = mySpec.get(Par::mass1, "TYd", 3, 3);
      double At_val  = (Yu33 != 0.0) ? TYu33 / Yu33 : 0.0;
      double Ab_val  = (Yd33 != 0.0) ? TYd33 / Yd33 : 0.0;
      double mQ3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mq2", 3, 3)));
      double mU3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mu2", 3, 3)));
      double mD3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "md2", 3, 3)));

      input = {tanb, mh, M3_val, mu_val, mQ3_val, mU3_val, mD3_val, At_val, Ab_val};
      std::cout << "[Emulator: getSusHi_h_xsec_total] TranslateInput: tanb=" << tanb
                << " mh=" << mh << std::endl;
    }

    bool getSusHi_h_xsec_total_EmulatorCheckThreshold(str& name, std::vector<double>& uncertainty)
    {
      #ifdef WITH_MPI
      bool accept = checkThreshold(name, uncertainty);
      std::cout << "[Emulator: " << name << "] CheckThreshold: uncertainty = " << uncertainty[0]
                << " -> " << (accept ? "PREDICT" : "TRAIN") << std::endl;
      return accept;
      #else
      return false;
      #endif
    }

    void getSusHi_h_xsec_total_EmulatorTranslateTarget(std::vector<double>& target, double& result, std::vector<double>& uncertainty)
    {
      target = {result};
      // ~2% relative uncertainty, matching the reduced VEGAS call counts
      // configured in SusHi_run_point for emulator-training speed.
      uncertainty = {0.02 * result};
      std::cout << "[Emulator: getSusHi_h_xsec_total] TrainPoint: xsec_total = " << result << " pb" << std::endl;
    }

    void getSusHi_h_xsec_total_EmulatorTranslatePrediction(std::vector<double>& prediction, std::vector<double>& uncertainty, double& result)
    {
      result = prediction[0];
      std::cout << "[Emulator: getSusHi_h_xsec_total] Prediction: xsec_total = " << result << " pb" << std::endl;
    }

    /// Total (gg->h + bb->h) production cross section at NNLO [pb], LHC 13 TeV,
    /// for the lightest CP-even MSSM Higgs h, from SusHi.
    void getSusHi_h_xsec_total(double& result)
    {
      using namespace Pipes::getSusHi_h_xsec_total;
      double ggh = 0.0, bbh = 0.0;
      BEreq::SusHi_run_point(*Dep::MSSM_spectrum, ggh, bbh);
      result = ggh + bbh;
    }

    /// Signal strength mu_gammagamma = [sigma(pp->h) x BR(h->gammagamma)] / SM
    /// reference, for the MSSM lightest CP-even Higgs h as a candidate for
    /// the ~95 GeV diphoton excess.
    void getMu_gammagamma_h95(double& result)
    {
      using namespace Pipes::getMu_gammagamma_h95;

      double xsec_total = *Dep::SusHi_h_xsec_total_cap;                 // pb
      double BR_gaga = Dep::Higgs_decay_rates->BF("gamma", "gamma");
      double sigmaBR = xsec_total * BR_gaga;                            // pb

      // SM reference sigma(pp->H) x BR(H->gammagamma) at m_H = 95.4 GeV,
      // LHC 13 TeV, matching the normalization used in Biekotter, Heinemeyer,
      // Weiglein, "The 95.4 GeV di-photon excess at ATLAS and CMS"
      // (arXiv:2306.03889), which quotes sigma^SM(pp->H->gammagamma) = 126
      // [ref 30: LHC Higgs XS WG Handbook 4, arXiv:1610.07922] to compute
      // mu_gammagamma^ATLAS from ATLAS's raw cross-section limits.
      //
      // Units: the paper's "126" is in FEMTOBARN, not picobarn (verified by
      // cross-check against CMS's own HIG-20-002 PAS, which reports an
      // *observed* 95% CL upper limit on sigma x BR(gammagamma) of 73 fb at
      // m=95.4 GeV -- a "126 pb" SM reference would be ~1700x that observed
      // limit, making mu values of order 0.2-0.3 impossible; "126 fb"
      // (=0.126 pb) is consistent with it). Independently cross-checked
      // against a from-scratch SusHi SM-mode run (model=0) at 95.4 GeV,
      // 13 TeV, NNLO ggh+bbh: sigma_SM = 74.02 pb, times a representative
      // BR_SM(H->gammagamma)~1.3-1.8e-3 at that mass gives ~0.10-0.13 pb,
      // consistent with 0.126 pb. Override via a yaml runOption
      // ("SM_xsecBR_gammagamma_95GeV") without recompiling if a more precise
      // value becomes available.
      double SM_ref = runOptions->getValueOrDef<double>(0.126, "SM_xsecBR_gammagamma_95GeV");

      result = sigmaBR / SM_ref;
    }

    /// sigma(pp->h) x BR(h->tautau) [pb], for the MSSM lightest CP-even
    /// Higgs h. Compared directly against a raw observed rate (not a ratio
    /// to SM) in calc_Higgs95_LogLike, since that's the form CMS actually
    /// quoted their best-fit result in.
    void getSigmaBR_tautau_h95(double& result)
    {
      using namespace Pipes::getSigmaBR_tautau_h95;

      double xsec_total = *Dep::SusHi_h_xsec_total_cap;                 // pb
      double BR_tautau = Dep::Higgs_decay_rates->BF("tau+", "tau-");
      result = xsec_total * BR_tautau;                                  // pb
    }

    /// Combined chi^2-based log-likelihood for the ~95 GeV diphoton and
    /// ditau excesses reported by CMS/ATLAS. All target/reference values
    /// are read via runOptions, so they can be changed from the yaml
    /// (a "- function: calc_Higgs95_LogLike" Rules entry with an options:
    /// block) without recompiling gambit -- see the defaults and their
    /// sources below.
    void calc_Higgs95_LogLike(double& result)
    {
      using namespace Pipes::calc_Higgs95_LogLike;

      // ---- gamma-gamma channel ----
      // ATLAS+CMS combined signal strength at m=95.4 GeV, local significance
      // 3.1 sigma (CMS alone 2.9 sigma, ATLAS alone 1.7 sigma, both full
      // Run 2). Source: Biekotter, Heinemeyer, Weiglein, "The 95.4 GeV
      // di-photon excess at ATLAS and CMS", arXiv:2306.03889, which quotes
      // mu_gammagamma^(ATLAS+CMS) = 0.24 (+0.09/-0.08). We symmetrize the
      // asymmetric uncertainty here (0.085 = average of 0.09 and 0.08) for
      // a simple Gaussian chi^2; this supersedes the CMS-only 0.6 +/- 0.2
      // value quoted in the earlier arXiv:2203.13180 (Eq. 1).
      double mu_gg_obs    = runOptions->getValueOrDef<double>(0.24,  "mu_gammagamma_obs");
      double mu_gg_obserr = runOptions->getValueOrDef<double>(0.085, "mu_gammagamma_obserr");
      double mu_gg_pred = *Dep::mu_gammagamma_h95_cap;
      double chi2_gg = std::pow((mu_gg_pred - mu_gg_obs) / mu_gg_obserr, 2);

      // ---- tau-tau channel ----
      // CMS best-fit sigma(ggphi) x BR(phi->tautau) at m=95 GeV, full Run 2
      // gluon-fusion search. Verified directly against the primary CMS
      // paper (CMS-HIG-21-001, "Searches for additional Higgs bosons and for
      // vector leptoquarks in tautau final states", arXiv:2208.02717),
      // which states verbatim: "The local (global) significance for the
      // tautau search evaluated at m_phi = 95 GeV is 2.6 (2.3) s.d. and the
      // best fit value of the product of the cross section with the
      // branching fraction ... is sigma_ggphi x BR(phi->tautau) =
      // (7.8 +3.9/-3.1) pb." (Note: 7.8, not the 7.7 originally taken from
      // the secondary citation in Biekotter, Heinemeyer, Weiglein,
      // arXiv:2203.13180, Sect. 1 -- a small rounding/version discrepancy.)
      // We use the lower (more conservative) uncertainty symmetrically,
      // matching the convention that paper itself adopts in its Eq. (3)
      // footnote.
      double sigmaBR_tt_obs    = runOptions->getValueOrDef<double>(7.8, "sigmaBR_tautau_obs_pb");
      double sigmaBR_tt_obserr = runOptions->getValueOrDef<double>(3.1, "sigmaBR_tautau_obserr_pb");
      double sigmaBR_tt_pred = *Dep::sigmaBR_tautau_h95_cap;
      double chi2_tt = std::pow((sigmaBR_tt_pred - sigmaBR_tt_obs) / sigmaBR_tt_obserr, 2);

      double chi2_total = chi2_gg + chi2_tt;
      result = -0.5 * chi2_total;
    }

  }

}
