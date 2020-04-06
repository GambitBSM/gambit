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
      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
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

      // run Higgs bounds 'classic'
      double obsratio;
      int HBresult, chan, ncombined;
      BEreq::run_HiggsBounds_classic(HBresult,chan,obsratio,ncombined);

      // extract the LEP chisq
      double chisq_withouttheory,chisq_withtheory;
      int chan2;
      double theor_unc = 1.5; // theory uncertainty
      //TODO: The below needs to be replaced -- it does not exist in HiggsBounds 5.7.0
      BEreq::HB_calc_stats(theor_unc,chisq_withouttheory,chisq_withtheory,chan2);

      // Catch HiggsBound's error value, chisq = -999
      if( fabs(chisq_withouttheory - (-999.)) < 1e-6)
      {
        ColliderBit_warning().raise(LOCAL_INFO, "Got chisq=-999 from HB_calc_stats in HiggsBounds, indicating a cross-section outside tabulated range. Will use chisq=0.");
        chisq_withouttheory = 0.0;
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

      // Add one-sided Gaussian drop in loglike when the lightest Higgs
      // mass is > 150 GeV. This avoids a completely flat loglike 
      // from HS in parameter regions with far too high Higgs mass.
      if (ModelParam.Mh[0] > 150.)
      {
        result -= 0.5 * pow(ModelParam.Mh[0] - 150., 2) / pow(10., 2);
      }
      
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


    /// Get an LHC chisq from HiggsBounds for the CPVYukawas model using the
    /// effective coupling interface to HB/HS
    void calc_HS_LHC_LogLike_CPVYukawas(double &result)
    {
      using namespace Pipes::calc_HS_LHC_LogLike_CPVYukawas;

    // TODO: JC: Delete this?
//      hb_ModelParameters ModelParam = *Dep::HB_ModelParameters;

      Farray<double, 1,3, 1,3> BR_hjhiZ;
      Farray<double, 1,3, 1,3, 1,3> BR_hkhjhi;

      int i,j,k;

     //TODO: JC: Delete this? These are not used anywhere.
//      Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
//      Farray<double, 1,3, 1,3> BR_hjhihi;
      
      int Hneut = 1;
      double Mh[Hneut];
      Mh[0] = 125.09;
      double GammaTotal[Hneut];
      double CP[Hneut];
      CP[0] = 0.;
      //const HiggsCouplingsTable::h0_decay_array_type&  h0_widths = Dep::Higgs_Couplings->get_neutral_decays_array(1);
      GammaTotal[0] = 4.08E-3; //taken from HS //h0_widths[0]->width_in_GeV;

      double ghjss_s[Hneut], ghjss_p[Hneut], ghjcc_s[Hneut], ghjcc_p[Hneut],
        ghjbb_s[Hneut], ghjbb_p[Hneut], ghjtt_s[Hneut], ghjtt_p[Hneut],
        ghjmumu_s[Hneut], ghjmumu_p[Hneut], ghjtautau_s[Hneut], ghjtautau_p[Hneut],
        ghjWW[Hneut], ghjZZ[Hneut], ghjZga[Hneut], ghjgaga[Hneut], ghjgg[Hneut],
        ghjhiZ[Hneut];
      double BR_hjinvisible[Hneut], BR_hjemu[Hneut], BR_hjetau[Hneut],
        BR_hjmutau[Hneut], BR_hjHpiW[Hneut];

      // TODO: JC: Delete this? These are not used anywhere
//      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
//      {
//        CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
//        BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
//      }

      //the following two functions are already called in Backends/src/frontends/HiggsSignals_2_2_3beta.cpp with nHneut = 1, nHplus = 0, pdf = 2 (Gaussian)
      //initialize_HiggsSignals_LHC13(nHneut,nHplus
      //setup_pdf(pdf=2)
      //
      //setup_output_level(0) only gives debug information - not called
      //setup_Nparam(number of free model parameters = 12) not called - even though might be needed but is not listed in Backends/include/gambit/Backends/frontends/HiggsSignals_2_2_3beta.hpp


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
      double cosPhiS = sqrt(1. - pow(*Param["SinPhiS"],2));
      double cosPhiC = sqrt(1. - pow(*Param["SinPhiC"],2));
      double cosPhiB = sqrt(1. - pow(*Param["SinPhiB"],2));
      double cosPhiT = sqrt(1. - pow(*Param["SinPhiT"],2));
      double cosPhiMu = sqrt(1. - pow(*Param["SinPhiMu"],2));
      double cosPhiTau = sqrt(1. - pow(*Param["SinPhiTau"],2));


      for(int i = 0; i<Hneut; i++){
      ghjss_p[i] = kappaS*sinPhiS;
      ghjss_s[i] = kappaS*cosPhiS;
      ghjcc_p[i] = kappaC*sinPhiC;
      ghjcc_s[i] = kappaC*cosPhiC;
      ghjbb_p[i] = kappaB*sinPhiB;
      ghjbb_s[i] = kappaB*cosPhiB;
      ghjtt_p[i] = kappaT*sinPhiT;
      ghjtt_s[i] = kappaT*cosPhiT;
      ghjmumu_p[i] = kappaMu*sinPhiMu;
      ghjmumu_s[i] = kappaMu*cosPhiMu;
      ghjtautau_p[i] = kappaTau*sinPhiTau;
      ghjtautau_s[i] = kappaTau*cosPhiTau;

      // hVV
      ghjWW[i]=1.;
      ghjZZ[i]=1.;
      ghjZga[i]=1.; // h-Z-photon (change?)
      //the following numeric values are with a SM-Higgs mass. Formulae found in 1310.1385. Results than multiplied with complex conjugate.
      ghjgaga[i] = 1.61137 + 0.0000369539 *pow(kappaB,2) + 0.0000147277 *pow(kappaC,2) + 1.97566E-9 *pow(kappaMu,2) + 1.55315E-10 *pow(kappaS,2) 
	+ 0.0782548 *pow(kappaT,2) + 0.0000237393 *pow(kappaTau,2) + 3.53719E-6 *pow(kappaB *sinPhiB,2) + 0.00931582 *kappaB *cosPhiB 
	+ 0.0000494538 *kappaB *kappaC *sinPhiB *sinPhiC + 1.03101E-6 *pow(kappaC *sinPhiC,2) + 0.00753304 *kappaC *cosPhiC 
	+ 0.000045367 *kappaB *kappaC *cosPhiB *cosPhiC + 5.23318E-7 *kappaB *kappaMu *sinPhiB *sinPhiMu 
	+ 3.50135E-7 *kappaC *kappaMu *sinPhiC *sinPhiMu + 6.96949E-11 *pow(kappaMu *sinPhiMu,2) + 0.000101872 *kappaMu *cosPhiMu 
	+ 4.79805E-7 *kappaB *kappaMu *cosPhiB *cosPhiMu + 3.31189E-7 *kappaC *kappaMu *cosPhiC *cosPhiMu 
	+ 1.4627E-7 *kappaB *kappaS *sinPhiB *sinPhiS + 9.7998E-8 *kappaC *kappaS *sinPhiC *sinPhiS + 1.14647E-9 *kappaMu *kappaS *sinPhiMu *sinPhiS 
	+ 5.34611E-12 *pow(kappaS *sinPhiS,2) 
	+ 0.0000286471 *kappaS *cosPhiS + 1.34093E-7 *kappaB *kappaS *cosPhiB *cosPhiS + 9.27152E-8 *kappaC *kappaS *cosPhiC *cosPhiS 
	+ 1.10786E-9 *kappaMu *kappaS *cosPhiMu *cosPhiS - 0.00350944 *kappaB *kappaT *sinPhiB *sinPhiT 
	- 0.00266921 *kappaC *kappaT *sinPhiC *sinPhiT 
	- 0.0000348837 *kappaMu *kappaT *sinPhiMu *sinPhiT - 9.80344E-6 *kappaS *kappaT *sinPhiS *sinPhiT + 0.102849 *pow(kappaT *sinPhiT,2) 
	- 0.710205 *kappaT *cosPhiT 
	- 0.00205295 *kappaB *kappaT *cosPhiB *cosPhiT - 0.00166008 *kappaC *kappaT *cosPhiC *cosPhiT 
	- 0.0000224498 *kappaMu *kappaT *cosPhiMu *cosPhiT - 6.31304E-6 *kappaS *kappaT *cosPhiS *cosPhiT 
	+ 0.0000635451 *kappaB *kappaTau *sinPhiB *sinPhiTau 
	+ 0.000040101 *kappaC *kappaTau *sinPhiC *sinPhiTau + 4.40694E-7 *kappaMu *kappaTau *sinPhiMu *sinPhiTau 
	+ 1.23307E-7 *kappaS *kappaTau *sinPhiS *sinPhiTau - 0.00327124 *kappaT *kappaTau *sinPhiT *sinPhiTau 
	+ 1.82919E-6 *pow(kappaTau *sinPhiTau,2) + 0.00913359 *kappaTau *cosPhiTau + 0.0000582519 *kappaB *kappaTau *cosPhiB *cosPhiTau 
	+ 0.0000373436 *kappaC *kappaTau *cosPhiC *cosPhiTau + 4.14361E-7 *kappaMu *kappaTau *cosPhiMu *cosPhiTau 
	+ 1.15958E-7 *kappaS *kappaTau *cosPhiS *cosPhiTau - 0.00201279 *kappaT *kappaTau *cosPhiT *cosPhiTau;
      ghjgaga[i] = sqrt(ghjgaga[i]);
      ghjgg[i]=0.0119731 *pow(kappaB,2) + 0.000298235 *pow(kappaC,2) + 5.0322E-8 *pow(kappaS,2) 
	+ 1.58466 *pow(kappaT,2) + 0.00114605 *pow(kappaB* sinPhiB,2) + 0.00400575 *kappaB *kappaC* sinPhiB* sinPhiC 
	+ 0.0000208779 *pow(kappaC* sinPhiC,2) + 0.0000473915 *kappaB *kappaS* sinPhiB* sinPhiS 
	+ 7.93784E-6 *kappaC *kappaS* sinPhiC* sinPhiS + 1.73214E-9 *pow(kappaS* sinPhiS,2) 
	- 0.284265 *kappaB *kappaT* sinPhiB* sinPhiT - 0.0540516 *kappaC *kappaT* sinPhiC* sinPhiT - 0.000794079 *kappaS *kappaT* sinPhiS* sinPhiT 
	+ 2.08269 *pow(kappaT* sinPhiT,2) + 0.00367473 *kappaB *kappaC *cosPhiB *cosPhiC + 0.0000434461 *kappaB *kappaS *cosPhiB *cosPhiS 
	+ 7.50993E-6 *kappaC *kappaS *cosPhiC *cosPhiS - 0.166289 *kappaB *kappaT *cosPhiB *cosPhiT - 0.0336165 *kappaC *kappaT *cosPhiC *cosPhiT 
	- 0.000511357 *kappaS *kappaT *cosPhiS *cosPhiT; 
      // h-gluon-gluon (change?)
      ghjgg[i]=sqrt(ghjgg[i]); // h-gluon-gluon (change?)
      ghjhiZ[i]=0.; // h-h-Z 
 
      cout << "gammaTotal before: " <<  GammaTotal[i] << endl;
      GammaTotal[i] = 4.08E-3; //taken from HS //h0_widths[0]->width_in_GeV;
      GammaTotal[i] = GammaTotal[i]* ( 1
			+ (pow(kappaS,2)-1)*2.4637E-4 +(pow(kappaC,2)-1)*2.8828E-2 +(pow(kappaB,2)-1)*5.895E-1 +(pow(kappaT,2)-1)*0E0 
			+ (pow(kappaMu,2)-1)*2.2446E-4 +(pow(kappaTau,2)-1)*6.3347E-2 +(pow(ghjgaga[i],2)-1)*2.30946E-3 
			+ (pow(ghjgg[i],2)-1)*7.81082E-2 + (pow(ghjWW[i],2)-1)*2.09566E-1 + (pow(ghjZZ[i],2)-1)*2.64394E-2
	      	      );
	      //how does the decay rate change in the model
      cout << "gammaTotal after: " <<  GammaTotal[i] << endl;

      }
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
      cout << "hgaga: " << ghjgaga[0] << endl;
      cout << "hgg: " << ghjgg[0] << endl;
     
      BEreq::HiggsBounds_neutral_input_properties_HS(&Mh[0],&GammaTotal[0],&CP[0]);

      BEreq::HiggsBounds_neutral_input_effC_HS(
		      &ghjss_s[0], &ghjss_p[0], &ghjcc_s[0],   &ghjcc_p[0],   &ghjbb_s[0],     &ghjbb_p[0],
		      &ghjtt_s[0], &ghjtt_p[0], &ghjmumu_s[0], &ghjmumu_p[0], &ghjtautau_s[0], &ghjtautau_p[0], 
		      &ghjWW[0],   &ghjZZ[0],   &ghjZga[0],    &ghjgaga[0],   &ghjgg[0],       &ghjhiZ[0]);


      //BEreq::HiggsSignals_neutral_input_MassUncertainty(&ModelParam.deltaMh[0]);

      // add uncertainties to cross-sections and branching ratios
      // double dCS[5] = {0.,0.,0.,0.,0.};
      // double dBR[5] = {0.,0.,0.,0.,0.};
      // BEreq::setup_rate_uncertainties(dCS,dBR);

      // run HiggsSignals
      int mode = 1; // 1- peak-centered chi2 method (recommended)
      double csqmu, csqmh, csqtot, Pvalue;
      int nobs;
      BEreq::run_HiggsSignals(csqmu, csqmh, csqtot, nobs, Pvalue);
      //TODO: Also calculate STXS chi-square

      result = -0.5*csqtot;

      // Add one-sided Gaussian drop in loglike when the lightest Higgs
      // mass is > 150 GeV. This avoids a completely flat loglike 
      // from HS in parameter regions with far too high Higgs mass.
      if (Mh[0] > 150.)
      {
        result -= 0.5 * pow(Mh[0] - 150., 2) / pow(10., 2);
      }
      
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
