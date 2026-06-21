///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.au)
///  \date 2025 Oct
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2019-04/
//  - https://cds.cern.ch/record/2858670
//  - https://inspirehep.net/literature/2686498
//  - https://arxiv.org/abs/2308.02595

// Search for the single vector-like B (B -> b+H( -> bb)) in pp collisions at s√= 13 TeV

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"

// Similar to ATLAS_13_TeV_3b_NN_139invfb (define structure copied from heputils/FastJet.h)
#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/tools/Filter.hh"
#else
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

using namespace std;

// #define CHECK_CUTFLOW

namespace Gambit
{
  namespace ColliderBit
  {
    class Analysis_ATLAS_EXOT_2019_04 : public Analysis
    {
    private:
      /* data */
    public:
      #ifdef CHECK_CUTFLOW
            Cutflows _cutflows;
            int Nevent = 0;
      #endif

      static constexpr const char *detector = "ATLAS";
      Analysis_ATLAS_EXOT_2019_04()
      {
        DEFINE_SIGNAL_REGION("SR");

        // Histograms for kinematic distributions (filled when check_histogram is enabled)
        // DEFINE_HISTOGRAM_1D_UNIFORM("m_VLB", 25, 500.0, 3000.0, "m_{VLB} [GeV]")
        // 1D histogram in Fig. 7 of arXiv:2308.02595
        const std::vector<double> mVLB_bins = {900, 1050, 1150, 1250, 1400, 1600, 1900, 2300};
        const std::vector<double> mVLB_obs = {41.0, 62, 54., 67., 24., 13., 4.};
        const std::vector<double> mVLB_bkg = {45.5, 61.2, 47.9, 51.0, 28.5, 14.8, 7.4};
        const std::vector<double> mVLB_bkg_err = {4.6, 5.6, 5.4, 6.2, 4.3, 2.8, 2.0};
        DEFINE_HISTOGRAM_SR_1D("m_VLB", mVLB_bins, mVLB_obs, mVLB_bkg, mVLB_bkg_err, "$m_{\\rm VLB}$ [GeV]")
        // End of definition of histograms
        set_analysis_name("ATLAS_EXOT_2019_04");
        set_luminosity(139.0);
      }

      void run(const HEPUtils::Event *event)
      {
#ifdef CHECK_CUTFLOW
        BEGIN_PRESELECTION
        Nevent += 1;
        if (Nevent % 200 == 0) { cout << "Complete " << Nevent << " Events" << endl; }
        END_PRESELECTION
#endif

        BASELINE_PARTICLES(event->electrons(), baselineEl1, 25., 0, DBL_MAX, 1.37)
        BASELINE_PARTICLES(event->electrons(), baselineEl2, 25., 1.52, DBL_MAX, 2.47)
        BASELINE_PARTICLES(event->muons(), baselineMuons, 25., 0, DBL_MAX, 2.5)
        BASELINE_PARTICLES(event->photons(), baselinePh1, 10., 0, DBL_MAX, 1.37)
        BASELINE_PARTICLES(event->photons(), baselinePh2, 10., 1.52, DBL_MAX, 2.47)

        BASELINE_PARTICLE_COMBINATION(baselineElectrons, baselineEl1, baselineEl2)
        BASELINE_PARTICLE_COMBINATION(baselinePhotons, baselinePh1, baselinePh2)

        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Loose"));
        applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
        applyEfficiency(baselinePhotons, ATLAS::eff1DPhoton.at("GAM_2018_03_Iso_Tight"));

        BASELINE_JETS(event->jets("antikt_R04"), baselineCentralJets, 25., 0, DBL_MAX, 2.5)
        BASELINE_JETS(event->jets("antikt_R04"), baselineForwardJets, 40., 2.5, DBL_MAX, 4.5)
        BASELINE_JETS(event->jets("antikt_R10"), baseLargeRJets, 480., 0, DBL_MAX, 2.0)
        BASELINE_JET_COMBINATION(BaselineJets, baselineCentralJets, baselineForwardJets)

        SIGNAL_PARTICLES(baselineElectrons, signalEl)
        SIGNAL_PARTICLES(baselineMuons, signalMu)
        SIGNAL_PARTICLES(baselinePhotons, signalPh)
        SIGNAL_PARTICLE_COMBINATION(signalLep, signalEl, signalMu)

        std::vector<const HEPUtils::Jet *> VR_jets;
        for (const HEPUtils::Jet *j : event->jets("VRTrackJets"))
        {
          if (j->pT() > 10. && j->abseta() < 2.5) VR_jets.push_back(j);
        }

        // Sort object by pT
        sortByPt(BaselineJets);
        sortByPt(baselineElectrons);
        sortByPt(baselineMuons);
        sortByPt(VR_jets);

        // Large-R jet trimming and selection (ATLAS EXOT-2019-04)
        const double Rtrim = 0.2; // R_sub
        const double fcut = 0.05; // pT fraction
        FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rtrim), fastjet::SelectorPtFractionMin(fcut));

        std::vector<std::unique_ptr<HEPUtils::Jet>> trimmedLargeRJets_owned;
        std::vector<const HEPUtils::Jet *> trimmedLargeRJets;

        for (size_t i = 0; i < baseLargeRJets.size(); ++i)
        {
          // Obtain the FastJet PseudoJet objects
          const fastjet::PseudoJet &pseudojet = baseLargeRJets[i]->pseudojet();
          // Make sure there are constituents inside the jet
          if (pseudojet.constituents().empty()) continue;

          // Trimming: Rsub=0.2, fcut=0.05
          fastjet::PseudoJet trimmedJet = trimmer(pseudojet);

          // Apply selection after trimming: pT > 480 GeV, |eta| < 2.0, mass > 50 GeV
          if (trimmedJet.pt() <= 480.) continue;
          if (std::fabs(trimmedJet.eta()) >= 2.0) continue;
          if (trimmedJet.m() <= 50.) continue;

          // Compute substructure variables (kept for potential future tuning)

          trimmedLargeRJets_owned.emplace_back(std::make_unique<HEPUtils::Jet>(trimmedJet));
          trimmedLargeRJets.push_back(trimmedLargeRJets_owned.back().get());
        }

        // --- Vetoes (paper preselection)
        // Lepton veto: no isolated electrons or muons
        if (!signalLep.empty()) return;

        // Diphoton resonance veto: reject events with m(gg) in [105,160] GeV
        bool diphoton_veto = false;
        if (baselinePhotons.size() >= 2)
        {
          for (size_t i = 0; i < baselinePhotons.size(); ++i)
          {
            for (size_t j = i + 1; j < baselinePhotons.size(); ++j)
            {
              const double m_gg = (baselinePhotons[i]->mom() + baselinePhotons[j]->mom()).m();
              if (m_gg > 105. && m_gg < 160.)
              {
                diphoton_veto = true;
                break;
              }
            }
            if (diphoton_veto) break;
          }
        }
        if (diphoton_veto) return;

        // Require at least one trimmed large-R jet candidate
        if (trimmedLargeRJets.empty()) return;

        // --- VR track-jet b-tagging (DL1r 70% WP): b=0.70119, c=0.10, light=0.0025
        std::map<const Jet *, bool> vr_btags = generateBTagsMap(VR_jets, 0.70119, 0.10, 0.0025);

        // Higgs candidate (HC): two leading associated track-jets, H2T2B
        const HEPUtils::Jet *HC = nullptr;
        std::vector<const HEPUtils::Jet *> HC_tjs;

        for (const HEPUtils::Jet *lr : trimmedLargeRJets)
        {
          std::vector<const HEPUtils::Jet *> tjs;
          for (const HEPUtils::Jet *tj : VR_jets)
          {
            if (tj->pT() <= 50.) continue;
            if (tj->mom().deltaR_eta(lr->mom()) < 1.0) tjs.push_back(tj);
          }
          if (tjs.size() < 2) continue;
          std::sort(tjs.begin(), tjs.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });
          if (tjs.size() > 2) tjs.resize(2);

          // Collinearity veto (approximate): reject if the two leading track-jets overlap within min(Reff)
          bool collinear_veto = false;
          {
            const HEPUtils::Jet *ji = tjs[0];
            const HEPUtils::Jet *jj = tjs[1];
            const double Ri = VR_Reff(ji->pT());
            const double Rj = VR_Reff(jj->pT());
            const double dR = ji->mom().deltaR_eta(jj->mom());
            const double Rmin_ij = std::min(Ri, Rj);
            if (dR < Rmin_ij) collinear_veto = true;
          }
          if (collinear_veto) continue;

          // Count b-tags among the two leading associated track-jets
          int nb = 0;
          for (const HEPUtils::Jet *tj : tjs)
          {
            auto it = vr_btags.find(tj);
            if (it != vr_btags.end() && it->second) nb += 1;
          }

          // Experimental report: require exactly two b-tagged track-jets (H2T2B)
          if (nb != 2) continue;

          // Keep the HC candidate with the largest mass (all eligible candidates are H2T2B)
          if (!HC || lr->mass() > HC->mass())
          {
            HC = lr;
            HC_tjs = tjs; // already pT-sorted and resized to 2 above
          }
        }

        if (!HC) return;

        if (HC_tjs.size() >= 2)
        {
          std::sort(HC_tjs.begin(), HC_tjs.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });
          if (HC_tjs.size() > 2) HC_tjs.resize(2);
        }

        // Preselection: require >=1 small-R jet with pT > 300 GeV and dR(smallR, HC) > 2.0
        bool has_smallR_pre = false;
        for (const HEPUtils::Jet *j : BaselineJets)
        {
          if (j->pT() > 300. && j->mom().deltaR_eta(HC->mom()) > 2.0)
          {
            has_smallR_pre = true;
            break;
          }
        }
        if (!has_smallR_pre) return;

        // --- Small-R jet b-tagging (70% WP used elsewhere in ColliderBit)
        std::map<const Jet *, bool> sr_btags = generateBTagsMap(BaselineJets, 0.70, 0.10, 0.002);

        // --- Build VLB candidates: HC + b-tagged small-R jet with pT>400, |eta|<2.5, dR>2.5
        struct VLBcand
        {
          const HEPUtils::Jet *j;
          double mB;
          double pT_B;
          double ratio_pT_HC_over_mB;
          double ratio_pT_B_over_mB;
        };
        std::vector<VLBcand> vlb_cands;
        for (const HEPUtils::Jet *j : BaselineJets)
        {
          if (j->pT() <= 400.) continue;
          if (j->abseta() >= 2.5) continue;
          auto it_sr = sr_btags.find(j);
          if (it_sr == sr_btags.end() || !it_sr->second) continue;
          // Experimental report: require the small-R b-jet to be well separated from the HC (ΔR(j,HC) > 2.0)
          if (j->mom().deltaR_eta(HC->mom()) <= 2.0) continue;

          const HEPUtils::P4 p4B = HC->mom() + j->mom();
          const double mB = p4B.m();
          if (mB <= 0.) continue;

          const double pT_B = p4B.pT();
          const double ratio_HC = HC->pT() / mB;
          const double ratio_B = pT_B / mB;
          vlb_cands.push_back({j, mB, pT_B, ratio_HC, ratio_B});
        }
        if (vlb_cands.empty()) return;
        // If multiple VLB candidates exist, choose the one with the lowest pT_B / mB
        std::sort(vlb_cands.begin(), vlb_cands.end(), [](const VLBcand &a, const VLBcand &b) { return a.ratio_pT_B_over_mB < b.ratio_pT_B_over_mB; });

        // --- Kinematic selection variables using the two leading track-jets associated with HC
        // logΔR* = log( ΔR(tj0,tj1) / min(Reff0,Reff1) )
        if (HC_tjs.size() < 2) return;

        const HEPUtils::Jet *tj0 = HC_tjs[0];
        const HEPUtils::Jet *tj1 = HC_tjs[1];

        const double dR_tj = tj0->mom().deltaR_eta(tj1->mom());
        const double Reff0 = VR_Reff(tj0->pT());
        const double Reff1 = VR_Reff(tj1->pT());
        const double denom = std::min(Reff0, Reff1);
        if (denom <= 0.) return;
        if (dR_tj <= 0.) return;

        const double logDeltaRstar = std::log(dR_tj / denom);

        // Apply logΔR* > 0.67
        if (logDeltaRstar <= 0.67) return;

        const VLBcand best = vlb_cands[0];
        if (best.ratio_pT_HC_over_mB <= 0.4) return;

        // Forward-jet requirement: at least one jet with pT>40 GeV and |eta| >2.5
        bool has_forward = false;
        for (const HEPUtils::Jet *fj : baselineForwardJets)
        {
          if (!fj) continue;

          // Defensive: baselineForwardJets already has pT>40 and |eta|>2.5 by construction, but keep explicit.
          if (fj->pT() <= 40.) continue;
          if (fj->abseta() <= 2.5) continue;

          // Exclude the VLB b-jet itself (and any jet overlapping with it)
          if (best.j && fj == best.j) continue;
          if (best.j && fj->mom().deltaR_eta(best.j->mom()) <= 0.4) continue;

          // Exclude jets overlapping with the Higgs candidate (avoid counting overlap/substructure)
          if (fj->mom().deltaR_eta(HC->mom()) <= 1.0) continue;

          has_forward = true;
          break;
        }
        if (!has_forward) return;

        // Signal region definition (region A): H2T2B and mHC in [105,135] GeV
        const double mHC = HC->mass();
        const bool in_H_window = (mHC >= 105. && mHC <= 135.);
        const bool is_H2T2B = true; // HC selection enforces H2T2B

        // Fill kinematic distribution histograms (before the mass-window cut)
        // FILL_HISTOGRAM_1D("m_HC", mHC)
        FILL_HISTOGRAM_1D("m_VLB", best.mB)

        if (in_H_window && is_H2T2B) { FILL_SIGNAL_REGION("SR"); }
      }

      virtual void collect_results()
      {
        COMMIT_SIGNAL_REGION("SR", 262, 260, 17)
        COMMIT_CUTFLOWS;
        COMMIT_HISTOGRAMS;
        COMMIT_HISTOGRAM_SRS("m_VLB");
        return;
      }

    protected:
      void analysis_specific_reset()
      {
        for (auto &pair : _counters) { pair.second.reset(); }
      }

    private:
      // ---- Helpers specific to this analysis ----
      double VR_Reff(double pt_GeV, double rho_GeV = 30.0, double Rmin = 0.02, double Rmax = 0.40)
      {
        if (pt_GeV <= 0.) return Rmax;
        const double r = rho_GeV / pt_GeV;
        return std::max(Rmin, std::min(Rmax, r));
      }
      // Note: ghost association is approximated here by ΔR matching where needed.
    };
    DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2019_04)
  } // namespace ColliderBit
} // namespace Gambit
