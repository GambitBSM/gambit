///
///  \author Holly Pacey
///  \date 2025 January
///
///  \author Pengxuan Zhu
///  \date 2025 March
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2019-07/
// Luminosity: 139 fb^-1

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "fastjet/tools/Filter.hh"
#include "fastjet/Selector.hh"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_EXOT_2019_07 : public Analysis
    {
      // Legacy mJJ bins retained for future reconstruction of the binned distribution.
      // std::map<string, EventCounter> _counters = {
      //     {"SR_bin_mJJ_1p0_1p1", EventCounter("SR_bin_mJJ_1p0_1p1")},
      //     {"SR_bin_mJJ_1p1_1p2", EventCounter("SR_bin_mJJ_1p1_1p2")},
      //     {"SR_bin_mJJ_1p2_1p3", EventCounter("SR_bin_mJJ_1p2_1p3")},
      //     {"SR_bin_mJJ_1p3_1p4", EventCounter("SR_bin_mJJ_1p3_1p4")},
      //     {"SR_bin_mJJ_1p4_1p5", EventCounter("SR_bin_mJJ_1p4_1p5")},
      //     {"SR_bin_mJJ_1p5_1p6", EventCounter("SR_bin_mJJ_1p5_1p6")},
      //     {"SR_bin_mJJ_1p6_1p7", EventCounter("SR_bin_mJJ_1p6_1p7")},
      //     {"SR_bin_mJJ_1p7_1p8", EventCounter("SR_bin_mJJ_1p7_1p8")},
      //     {"SR_bin_mJJ_1p8_1p9", EventCounter("SR_bin_mJJ_1p8_1p9")},
      //     {"SR_bin_mJJ_1p9_2p0", EventCounter("SR_bin_mJJ_1p9_2p0")},
      //     {"SR_bin_mJJ_2p0_2p1", EventCounter("SR_bin_mJJ_2p0_2p1")},
      //     {"SR_bin_mJJ_2p1_2p2", EventCounter("SR_bin_mJJ_2p1_2p2")},
      //     {"SR_bin_mJJ_2p2_2p3", EventCounter("SR_bin_mJJ_2p2_2p3")},
      //     {"SR_bin_mJJ_2p3_2p4", EventCounter("SR_bin_mJJ_2p3_2p4")},
      //     {"SR_bin_mJJ_2p4_2p5", EventCounter("SR_bin_mJJ_2p4_2p5")},
      //     {"SR_bin_mJJ_2p5_3p1", EventCounter("SR_bin_mJJ_2p5_3p1")},
      // };

    public:
      #ifdef CHECK_CUTFLOW
        int Nents = 0;
      #endif

      // Required detector sim
      static constexpr const char *detector = "ATLAS";

      Analysis_ATLAS_EXOT_2019_07()
      {
        defineSignalRegion("SR");

        if (Histogram1D::check_histogram())
        {
          const std::vector<double> mJJ_bins = {1000., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800.,
                                                1900., 2000., 2100., 2200., 2300., 2400., 2500., 3100.};
          const std::vector<double> mJJ_obs = {100., 97., 77., 58., 29., 29., 21., 12., 15., 10., 7., 5., 3., 1., 0., 1.2};
          const std::vector<double> mJJ_bkg = {106.54, 101.55, 79.52, 60.08, 39.80, 22.82, 21.97, 16.16,
                                               11.58, 7.33, 6.21, 3.90, 3.38, 2.55, 1.65, 1.29};
          const std::vector<double> mJJ_bkg_err = {6.72, 6.06, 4.78, 4.27, 4.02, 3.33, 2.58, 1.70,
                                                   1.65, 0.92, 0.89, 0.61, 0.64, 0.58, 0.41, 0.18};
          DEFINE_HISTOGRAM_SR_1D("m_JJ", mJJ_bins, mJJ_obs, mJJ_bkg, mJJ_bkg_err, "$m_{JJ}$ [GeV]")
        }

        set_analysis_name("ATLAS_EXOT_2019_07");
        set_luminosity(140.);

        #ifdef CHECK_CUTFLOW
          _cutflows.addCutflow("Signal Region", {"Initial signal event", "Large-R jet pT and eta cuts", "Lepton veto", "Leading large-R jet mass in (100, 225) GeV",
                                                 "Second-leading large-R jet mass in (100, 225) GeV", "SR tagging requirements", "m_Ht > 1 TeV"});
        #endif

        // Legacy cutflow definitions for the binned mJJ reconstruction.
        // _cutflows.addCutflow( "SR_binAll", {"JetpTEta", "0LEP", "massJ1", "massJ2", "htTagging", "massHt",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p0_1p1", {"1.0 TeV < mJJ < 1.1 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p1_1p2", {"1.1 TeV < mJJ < 1.2 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p2_1p3", {"1.2 TeV < mJJ < 1.3 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p3_1p4", {"1.3 TeV < mJJ < 1.4 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p4_1p5", {"1.4 TeV < mJJ < 1.5 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p5_1p6", {"1.5 TeV < mJJ < 1.6 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p6_1p7", {"1.6 TeV < mJJ < 1.7 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p7_1p8", {"1.7 TeV < mJJ < 1.8 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p8_1p9", {"1.8 TeV < mJJ < 1.9 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_1p9_2p0", {"1.9 TeV < mJJ < 2.0 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p0_2p1", {"2.0 TeV < mJJ < 2.1 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p1_2p2", {"2.1 TeV < mJJ < 2.2 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p2_2p3", {"2.2 TeV < mJJ < 2.3 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p3_2p4", {"2.3 TeV < mJJ < 2.4 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p4_2p5", {"2.4 TeV < mJJ < 2.5 TeV",});
        // _cutflows.addCutflow( "SR_bin_mJJ_2p5_3p1", {"2.5 TeV < mJJ < 3.1 TeV",});

        //      Trigger: >1 Jet, various pT cuts up to 480 GeV, analysis on plateau.

        //      Electrons: ET > 25 GeV, |eta| < 2.47, exclude crack region 1.37 < |eta| < 1.52,
        //                 Gradient Isolation, Tight ID
        //      Muons: pT > 25 GeV, |eta| < 2.5,
        //             muons removed if within dR < 0.4 of a jet
        //      jets: AntiKt_R04, pT > 35 GeV, |eta| < 2.5
        //            JVT something for jets with |eta| < 2.4, pT < 60 GeV
        //      Jets: AntiKt_R10, pT > 350 GeV, |eta| < 2.0
        //            Trimming algorithm applied
        //      VR-jets: AntiKt_R002-04, pT > 35 GeV, |eta| < 2.5,
        //               associate to large-R jet if dR(VRj, J) < 1.0
        //               b-tagging 70% DL1, 10 (400) bg rejection for c (light) jets

        //      H-tag: 100 GeV < mJ < 140 GeV
        //             tau_21 selection binned in pT(J) with a 70% efficiency
        //             5-10 bg rejection factor for light quark and gluon jets.

        //      top-tag: 140 GeV < mJ < 225 GeV
        //               substructure-based DNN 80% efficiency

        //      Preselection: >=2 Large-R jets with pT > 350 GeV and |eta| < 2.0,
        //                    pT(J1) > 500 GeV
        //                    100 GeV < m(J1) < 225 GeV, 100 GeV < m(J2) < 225 GeV,
        //                    ==0 electrons, ==0 muons
        //      SR: one J is H-tagged and has >=2 associated b-jets
        //          other J is top-tagged and has >=1 associated b-jets
        //      Discriminant: 1 TeV < mJJ < 2.3 TeV, bin-width 0.1 TeV
      }

      void run(const HEPUtils::Event *event)
      {
        #ifdef CHECK_CUTFLOW
          _cutflows["Signal Region"].fillinit(event->weight());
          _cutflows["Signal Region"].fill(1, true, event->weight());
          Nents += 1;
        #endif

        // Baseline objects
        vector<const HEPUtils::Particle *> Electrons;
        vector<const HEPUtils::Particle *> Muons;
        vector<const HEPUtils::Jet *> largeR_Jets;
        vector<const HEPUtils::Jet *> smallR_Jets;

        // Electrons: pT > 25 GeV, |eta|<1.37 or 1.52 < |eta|<2.47. Tight ID, Gradient Iso.
        for (const HEPUtils::Particle *electron : event->electrons())
        {
          if (electron->pT() > 25 && (electron->abseta() < 1.37 || (electron->abseta() > 1.52 && electron->abseta() < 2.47))) Electrons.push_back(electron);
        }
        applyEfficiency(Electrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Tight"));
        applyEfficiency(Electrons, ATLAS::eff1DEl.at("EGAM_2018_01_Iso_Gradient"));

        // Muons: pT > 25 GeV, |eta| < 2.5. Medium ID, Gradient Iso. Remove muons within DeltaRy<0.4 of jet
        for (const HEPUtils::Particle *muon : event->muons())
        {
          if (muon->pT() > 25. && muon->abseta() < 2.5) Muons.push_back(muon);
        }
        applyEfficiency(Muons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
        applyEfficiency(Muons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Loose")); // Gradient not implemented, hopefully this is similar enough.

        // Small-R jets: pT > 25 GeV, |η| < 2.5, JVT.
        const double JVTeff = 0.90;
        for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
        {
          if (jet->pT() > 25. && jet->abseta() < 2.5)
          {
            if ((jet->pT() < 60. && jet->abseta() < 2.4 && random_bool(JVTeff)) || jet->pT() > 60. || jet->abseta() > 2.4) smallR_Jets.push_back(jet);
          }
        }
        // Large-R jets: pT > 350 GeV, |η| < 2.0.
        for (const HEPUtils::Jet *jet : event->jets("antikt_R10"))
        {
          if (jet->pT() > 350. && jet->abseta() < 2.0) largeR_Jets.push_back(jet);
        }
        vector<const HEPUtils::Jet *> VR_jets;
        for (auto &pj : event->jets("VRTrackJets"))
        {
          if (pj->pT() > 25.0 && pj->abseta() < 2.5) VR_jets.push_back(pj);
        }

        // Large-R jet Trimming
        vector<const HEPUtils::Jet *> signalLargeRJets;

        std::vector<std::unique_ptr<HEPUtils::Jet>> owned_trimmed_jets;
        owned_trimmed_jets.reserve(largeR_Jets.size());

        const double Rsub = 0.2;
        const double ptfrac = 0.05;
        FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::antikt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));
        for (const HEPUtils::Jet *largeRJet : largeR_Jets)
        {
          const fastjet::PseudoJet &pseudojet = largeRJet->pseudojet();
          if (pseudojet.constituents().empty()) continue;
          fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
          if (trimmedJet.pt() <= 350. || std::abs(trimmedJet.eta()) >= 2.0) continue;
          owned_trimmed_jets.emplace_back(std::make_unique<HEPUtils::Jet>(trimmedJet));
          signalLargeRJets.push_back(owned_trimmed_jets.back().get());
        }

        // Overlap Remove
        removeOverlap(Electrons, Muons, 0.01);
        removeOverlap(smallR_Jets, Electrons, 0.2);
        removeOverlap(VR_jets, Electrons, 0.2);
        removeOverlap(Electrons, smallR_Jets, 0.4);
        removeOverlap(Electrons, VR_jets, 0.4);

        removeOverlap(smallR_Jets, Muons, 0.2);
        removeOverlap(VR_jets, Muons, 0.2);
        removeOverlap(Muons, smallR_Jets, 0.4);
        removeOverlap(Muons, VR_jets, 0.4);

        removeOverlap(signalLargeRJets, Electrons, 1.0);
        removeOverlap(smallR_Jets, signalLargeRJets, 1.0);

        std::sort(signalLargeRJets.begin(), signalLargeRJets.end(),
                  [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });

        // B-tag the final VR-jet collection after overlap removal.
        vector<const HEPUtils::Jet *> bTagged_Jets;
        const auto vrbtag = generateBTagsMap(VR_jets, 0.70119, 0.09639, 0.00390);
        for (const HEPUtils::Jet *jet : VR_jets)
        {
          if (vrbtag.at(jet)) bTagged_Jets.push_back(jet);
        }

        // Apply H/top tagging only to the two leading trimmed large-R jets.
        const HEPUtils::Jet *higgsJet = nullptr;
        const HEPUtils::Jet *topJet = nullptr;
        for (size_t i = 0; i < std::min<size_t>(2, signalLargeRJets.size()); ++i)
        {
          const HEPUtils::Jet *jet = signalLargeRJets[i];
          const double mass = jet->mass();
          if (mass >= 140. && mass <= 225.)
          {
            if (random_bool(0.8)) topJet = jet;
          }
          else if (mass >= 105. && mass < 140.)
          {
            if (random_bool(0.7)) higgsJet = jet;
          }
        }

        bool leadingj = !signalLargeRJets.empty() && signalLargeRJets[0]->pT() > 500.;
        size_t n_leptons = Electrons.size() + Muons.size();
        double mJ1 = signalLargeRJets.size() >= 1 ? signalLargeRJets.at(0)->mass() : 0.;
        double mJ2 = signalLargeRJets.size() >= 2 ? signalLargeRJets.at(1)->mass() : 0.;

        int nbHiggs = 0;
        if (higgsJet)
        {
          for (const HEPUtils::Jet *jet : bTagged_Jets)
          {
            if (jet->mom().deltaR_eta(higgsJet->mom()) < 1.0) { nbHiggs += 1; }
          }
        }

        int nbtop = 0;
        if (topJet)
        {
          for (const HEPUtils::Jet *jet : bTagged_Jets)
          {
            if (jet->mom().deltaR_eta(topJet->mom()) < 1.0) { nbtop += 1; }
          }
        }
        bool srht = topJet && higgsJet;
        bool srnb = srht && (nbtop >= 1) && (nbHiggs >= 2);
        double mHt = srht ? (higgsJet->mom() + topJet->mom()).m() : 0.;

        bool pass_JetpTEta = (signalLargeRJets.size() >= 2) && leadingj;
        bool pass_JetpTEta_0LEP = pass_JetpTEta && (n_leptons == 0);
        bool pass_JetpTEta_0LEP_massJ1 = pass_JetpTEta_0LEP && (mJ1 >= 100.) && (mJ1 <= 225.);
        bool pass_JetpTEta_0LEP_massJ1_massJ2 = pass_JetpTEta_0LEP_massJ1 && (mJ2 >= 100.) && (mJ2 <= 225.);
        bool pass_JetpTEta_0LEP_massJ1_massJ2_htTagging = pass_JetpTEta_0LEP_massJ1_massJ2 && (srnb);
        bool pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht = pass_JetpTEta_0LEP_massJ1_massJ2_htTagging && (mHt >= 1000.);

        if (pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht)
        {
          _counters.at("SR").add_event(event);
          FILL_HISTOGRAM_1D("m_JJ", mHt)
        }

        #ifdef CHECK_CUTFLOW
          _cutflows["Signal Region"].fillnext({pass_JetpTEta, pass_JetpTEta_0LEP, pass_JetpTEta_0LEP_massJ1, pass_JetpTEta_0LEP_massJ1_massJ2,
                                               pass_JetpTEta_0LEP_massJ1_massJ2_htTagging, pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht},
                                               event->weight());
        #endif

        return;

      } // End run function

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        // Legacy binned mJJ data: observed, expected background, background uncertainty.
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p0_1p1"), 100., {106.54, 6.72}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p1_1p2"), 97. , {101.55, 6.06}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p2_1p3"), 77. , {79.52 , 4.78}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p3_1p4"), 58. , {60.08 , 4.27}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p4_1p5"), 29. , {39.80 , 4.02}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p5_1p6"), 29. , {22.82 , 3.33}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p6_1p7"), 21. , {21.97 , 2.58}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p7_1p8"), 12. , {16.16 , 1.70}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p8_1p9"), 15. , {11.58 , 1.65}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p9_2p0"), 10. , {7.33  , 0.92}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p0_2p1"), 7.  , {6.21  , 0.89}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p1_2p2"), 5.  , {3.90  , 0.61}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p2_2p3"), 3.  , {3.38  , 0.64}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p3_2p4"), 1.  , {2.55  , 0.58}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p4_2p5"), 0.  , {1.65  , 0.41}));
        // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p5_3p1"), 1.2 , {1.29  , 0.18}));

        add_result(SignalRegionData(_counters.at("SR"), 471., {494., 22.}));

        if (Histogram1D::check_histogram())
        {
          COMMIT_HISTOGRAMS;
          COMMIT_HISTOGRAM_SRS("m_JJ");
        }

        COMMIT_CUTFLOWS;
        return;
      }

    protected:
      void analysis_specific_reset()
      {
        for (auto &pair : _counters) { pair.second.reset(); }
        if (Histogram1D::check_histogram())
        {
          const std::vector<double> mJJ_bins = {1000., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800.,
                                                1900., 2000., 2100., 2200., 2300., 2400., 2500., 3100.};
          const std::vector<double> mJJ_obs = {100., 97., 77., 58., 29., 29., 21., 12., 15., 10., 7., 5., 3., 1., 0., 1.2};
          const std::vector<double> mJJ_bkg = {106.54, 101.55, 79.52, 60.08, 39.80, 22.82, 21.97, 16.16,
                                               11.58, 7.33, 6.21, 3.90, 3.38, 2.55, 1.65, 1.29};
          const std::vector<double> mJJ_bkg_err = {6.72, 6.06, 4.78, 4.27, 4.02, 3.33, 2.58, 1.70,
                                                   1.65, 0.92, 0.89, 0.61, 0.64, 0.58, 0.41, 0.18};
          DEFINE_HISTOGRAM_SR_1D("m_JJ", mJJ_bins, mJJ_obs, mJJ_bkg, mJJ_bkg_err, "$m_{JJ}$ [GeV]")
        }
      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2019_07)

  } // namespace ColliderBit
} // namespace Gambit
