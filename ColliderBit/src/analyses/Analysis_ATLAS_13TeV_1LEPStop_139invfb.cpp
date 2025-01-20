
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/VariableR.hh"

#include <memory> // Required for std::shared_ptr
#include <YODA/Histo1D.h>
#include <YODA/WriterYODA.h>
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>
// #define CHECK_CUTFLOW

/*  The ATLAS 1 Lepton direct stop analysis

    Based on:
        - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-07/#
        - arXiv:2012.03799
        - https://inspirehep.net/literature/1835604

    Code by Pengxuan Zhu (pengxuan.zhu@adelaide.edu.au, zhupx99@icloud.com)

*/

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {
    static bool sortByPT_jet(const HEPUtils::Jet *jet1, const HEPUtils::Jet *jet2) { return (jet1->pT() > jet2->pT()); }
    static bool sortByPT_lep(const HEPUtils::Particle *lep1, const HEPUtils::Particle *lep2) { return (lep1->pT() > lep2->pT()); }
    
    bool sortByPT_1l(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT_1l_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT_1l(jet1.get(), jet2.get()); }


    /// Basic analysis code for copying
    class Analysis_ATLAS_13TeV_1LEPStop_139invfb : public Analysis
    {
    private:
      // YODA::Histo1DPtr _hist_Topness;
      std::shared_ptr<YODA::Histo1D> _hist_Topness;

    public:
      // Required detector sim
      static constexpr const char *detector = "ATLAS";

      Analysis_ATLAS_13TeV_1LEPStop_139invfb()
      {
        _hist_Topness = std::make_shared<YODA::Histo1D>(10, 0.0, 100.0, "Topness", "My Topness");
        // Signal region counter
        DEFINE_SIGNAL_REGION("SR-tN_med");
        DEFINE_SIGNAL_REGION("SR-tN_high");
        DEFINE_SIGNAL_REGION("SR-tN_diag_low");
        DEFINE_SIGNAL_REGION("SR-tN_diag_high");
        DEFINE_SIGNAL_REGION("SR-bWN");
        DEFINE_SIGNAL_REGION("SR-bffN_btag");
        DEFINE_SIGNAL_REGION("SR-bffN_softb");
        DEFINE_SIGNAL_REGION("SR-DM");

        // Set the analysis name
        set_analysis_name("ATLAS_13TeV_1LEPStop_139invfb");

        // Set the LHC luminosity
        set_luminosity(139.0);
      }

      struct ClusteringHistory : public FJNS::PseudoJet::UserInfoBase
      {
        enum Status
        {
          GOOD,
          JET_TOO_SMALL,
          JET_TOO_LARGE,
          TOO_MANY_ITERATIONS,
          NONE,
        };

        struct Step
        {
          double pt;
          double r;
          size_t constit;
          Status status;
        };

        size_t id;  // a per-event unique jet id that is needed for the event dump
        std::vector<Step> steps;

        static ClusteringHistory* AddStep(ClusteringHistory& history, const Step& step)
        {
          auto newHistory = new ClusteringHistory(history);
          newHistory->steps.push_back(step);
          return newHistory;
        }
      };


      ClusteringHistory &GetHistory(const FJNS::PseudoJet &jet)
      {
        auto shared_ptr = jet.user_info_shared_ptr();
        return *dynamic_cast<ClusteringHistory *>(shared_ptr.get());
      }

      static std::vector<FJNS::PseudoJet> SortedByNConstit(std::vector<FJNS::PseudoJet> jets)
      {
        std::sort(jets.begin(), jets.end(), [](const FJNS::PseudoJet &a, const FJNS::PseudoJet &b)
                  {
                        if (a.constituents().size() != b.constituents().size())
                        return a.constituents().size() > b.constituents().size();
                        return a.pt() > b.pt(); });

        return jets;
      }

      inline double optimalRadius(const double pT, const double m) { return 2 * m / pT; }
      inline double minRadius(const double pT, const double m) { return optimalRadius(pT, m) - 0.3; }
      inline double maxRadius(const double pT, const double m) { return optimalRadius(pT, m) + 0.5; }

      std::pair<bool, FJNS::PseudoJet> RecursiveRecluster(const FJNS::PseudoJet &candidate, double candRadius,
                                                          const double mass, size_t step)
      {
        if (minRadius(candidate.pt(), mass) > candRadius)
        {
          GetHistory(candidate).steps.back().status = ClusteringHistory::JET_TOO_SMALL;
          return std::make_pair(false, candidate);
        }
        else if (maxRadius(candidate.pt(), mass) < candRadius)
        {
          const double newR = std::max(maxRadius(candidate.pt(), mass), candRadius / 2.);
          GetHistory(candidate).steps.back().status = ClusteringHistory::JET_TOO_LARGE;

          if (step > 10)
          {
            GetHistory(candidate).steps.back().status = ClusteringHistory::TOO_MANY_ITERATIONS;
            return std::make_pair(false, candidate);
          }

          FJNS::JetDefinition jetDef(FJNS::antikt_algorithm, newR);
          auto cs = new FJNS::ClusterSequence(candidate.constituents(), jetDef);

          std::vector<FJNS::PseudoJet> reclusteredJets;
          reclusteredJets = SortedByNConstit(cs->inclusive_jets());

          if (reclusteredJets.size() == 0)
          {
            delete cs;
            return std::make_pair(false, FJNS::PseudoJet());
          }

          cs->delete_self_when_unused();
          auto newCandidate = reclusteredJets[0];

          auto newHistory = ClusteringHistory::AddStep(
              GetHistory(candidate),
              {newCandidate.pt(), newR, newCandidate.constituents().size(), ClusteringHistory::NONE});
          newCandidate.set_user_info(newHistory);

          return RecursiveRecluster(newCandidate, newR, mass, step + 1);
        }
        else
        {
          GetHistory(candidate).steps.back().status = ClusteringHistory::GOOD;
          return std::make_pair(true, candidate);
        }
      }

      HEPUtils::P4 reclusteredParticle(vector<const HEPUtils::Jet *> jets, vector<const HEPUtils::Jet *> bjets,
                                       const double mass, const bool useBJets)
      {

        // AnalysisObject p = AnalysisObject(0., 0., 0., 0., 0, 0, AnalysisObjectType::JET, 0, 0);
        HEPUtils::P4 p;
        double r0 = 3.0;

        vector<const HEPUtils::Jet *> usejets;
        for (const HEPUtils::Jet *jet : jets)
        {
          usejets.push_back(jet);
        }

        if (useBJets && bjets.size())
        {
          for (const HEPUtils::Jet *bjet : bjets)
          {
            usejets.push_back(bjet);
          }
        }

        std::vector<FJNS::PseudoJet> initialJets;

        for (const HEPUtils::Jet *jet : usejets)
        {
          FJNS::PseudoJet Pjet(jet->mom().px(), jet->mom().py(), jet->mom().pz(), jet->mom().E());
          initialJets.push_back(Pjet);
        }

        FJNS::JetDefinition jetDef(FJNS::antikt_algorithm, r0);
        FJNS::ClusterSequence cs(initialJets, jetDef);

        auto candidates = FJNS::sorted_by_pt(cs.inclusive_jets());

        std::vector<FJNS::PseudoJet> selectedJets;
        selectedJets.reserve(candidates.size());
        std::vector<FJNS::PseudoJet> badJets;
        badJets.reserve(candidates.size());

        size_t i = 0;
        for (auto &cand : candidates)
        {
          auto history = new ClusteringHistory();
          history->id = i;
          history->steps.push_back({cand.pt(), r0, cand.constituents().size(), ClusteringHistory::NONE});
          cand.set_user_info(history);
          ++i;
        }

        for (const auto &cand : candidates)
        {
          bool selected = false;
          FJNS::PseudoJet jet;

          std::tie(selected, jet) = RecursiveRecluster(cand, r0, mass, 0);

          if (selected)
            selectedJets.push_back(jet);
          else
            badJets.push_back(jet);
        }

        if (selectedJets.size() < 1)
        {
          return p;
        }

        vector<std::shared_ptr<HEPUtils::Jet>> aoSelectedJets;
        for (const FJNS::PseudoJet &j : selectedJets)
          aoSelectedJets.push_back(std::make_shared<HEPUtils::Jet>(HEPUtils::mk_p4(j)));

        // for (const auto jet : selectedJets)
        //   aoSelectedJets.push_back(
        //      AnalysisObject(jet.px(), jet.py(), jet.pz(), jet.E(), 0, 0, AnalysisObjectType::COMBINED, 0, 0));

        std::sort(aoSelectedJets.begin(), aoSelectedJets.end(), sortByPT_1l_sharedptr);
        p = aoSelectedJets[0]->mom();

        return p;
      }

      void run(const HEPUtils::Event *event)
      {
        // Get the missing energy in the event
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Now define vectors of baseline objects,  including:
        // - retrieval of electron, muon and jets from the event)
        // - application of basic pT and eta cuts

        // Baseline electrons
        vector<const HEPUtils::Particle *> baselineElectrons4Hard;
        vector<const HEPUtils::Particle *> baselineElectrons4Soft;
        for (const HEPUtils::Particle *electron : event->electrons())
        {
          if (electron->pT() > 4.5 && fabs(electron->eta()) < 2.47)
            baselineElectrons4Hard.push_back(electron);
          baselineElectrons4Soft.push_back(electron);
        }
        applyEfficiency(baselineElectrons4Hard, ATLAS::eff2DEl.at("PERF_2017_01_ID_Loose"));
        applyEfficiency(baselineElectrons4Soft, ATLAS::eff2DEl.at("PERF_2017_01_ID_Tight"));

        // Baseline muons
        vector<const HEPUtils::Particle *> baselineMuons4Hard;
        vector<const HEPUtils::Particle *> baselineMuons4Soft;
        for (const HEPUtils::Particle *muon : event->muons())
        {
          if (muon->pT() > 4.0 && fabs(muon->eta()) < 2.7)
            baselineMuons4Hard.push_back(muon);
          baselineMuons4Soft.push_back(muon);
        }
        applyEfficiency(baselineMuons4Hard, ATLAS::eff1DMu.at("MUON_2018_03_ID_Loose"));
        applyEfficiency(baselineMuons4Soft, ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight"));

        // Baseline jets
        vector<const HEPUtils::Jet *> baselineJets;
        for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
        {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5)
            baselineJets.push_back(jet);
        }

        vector<const HEPUtils::Particle *> signalTaus;
        for (const HEPUtils::Particle *tau : event->taus())
        {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.5)
            signalTaus.push_back(tau);
        }
        applyEfficiency(signalTaus, ATLAS::effTau.at("R2_RNN_Loose"));

        // Defining the soft-b jet for Stop -> b f f' LSP Signal Region
        // According to the CERN report: ATLAS-CONF-2019-027
        //        URL: https://cds.cern.ch/record/2682131/files/ATLAS-CONF-2019-027.pdf
        // 1. Define the Fastjet track object
        std::vector<fastjet::PseudoJet> fj_tracks;

        // Suppose you consider all stable charged particles with pT>0.5 GeV, |eta|<2.5, etc.
        for (auto *p : event->visible_particles())
        {
          if (p->abspid() != 11 && p->abspid() != 13 && p->abspid() != 15 && p->abspid() != 22 && p->pT() > 0.5 && p->abseta() < 2.5)
          {
            // Create a PseudoJet from the particle's momentum
            fastjet::PseudoJet pj(p->mom().px(), p->mom().py(), p->mom().pz(), p->mom().E());
            // Further processing
            fj_tracks.push_back(pj);
          }
        }

        // 2. Define the anti-kt Variable‐R jet
        double rho = 30.0;
        double Rmin = 0.02;
        double Rmax = 0.4;

        // fastjet::contrib::VariableRPlugin vr_plugin(rho, Rmin, Rmax);
        fastjet::contrib::VariableRPlugin vr_plugin(rho, Rmin, Rmax, fastjet::contrib::VariableRPlugin::AKTLIKE);
        fastjet::JetDefinition jet_def(&vr_plugin);
        // 3. Clustering the VR-Jet
        fastjet::ClusterSequence cseq(fj_tracks, jet_def);
        vector<fastjet::PseudoJet> vr_pseudojets = fastjet::sorted_by_pt(cseq.inclusive_jets(5.0));
        // 4. Converting into the HEPUtils Pseudo-Jet
        vector<HEPUtils::Jet *> VR_jets;
        for (auto &pj : vr_pseudojets)
        {
          HEPUtils::Jet *hj = new HEPUtils::Jet(pj);
          VR_jets.push_back(hj);
        }
        sort(VR_jets.begin(), VR_jets.end(), sortByPT_jet);

        vector<const HEPUtils::Jet *> trackJets(VR_jets.begin(), VR_jets.end());
        // Define the lowPT b-jet
        vector<const HEPUtils::Jet *> bVRJets;
        vector<const HEPUtils::Jet *> nonbVRJets;

        // B-tag Efficiencies: Figure 3 of ATLAS-CONF-2019-027
        std::map<const Jet *, bool> softB01 = generateBTagsMap(trackJets, 0.35144, 0.17459, 0.01457); // 5-7
        std::map<const Jet *, bool> softB02 = generateBTagsMap(trackJets, 0.52632, 0.19230, 0.01796); // 7-10
        std::map<const Jet *, bool> softB03 = generateBTagsMap(trackJets, 0.61460, 0.15541, 0.01233); // 10-15
        std::map<const Jet *, bool> softB04 = generateBTagsMap(trackJets, 0.69100, 0.17410, 0.01259); // 15-20
        std::map<const Jet *, bool> softB05 = generateBTagsMap(trackJets, 0.75722, 0.17262, 0.01125); // 20-30

        for (const HEPUtils::Jet *jet : trackJets)
        {
          if (jet->pT() > 5. && jet->pT() < 7.)
            softB01.at(jet) ? bVRJets.push_back(jet) : nonbVRJets.push_back(jet);
          else if (jet->pT() > 7. && jet->pT() < 10.)
            softB02.at(jet) ? bVRJets.push_back(jet) : nonbVRJets.push_back(jet);
          else if (jet->pT() > 10. && jet->pT() < 15.)
            softB03.at(jet) ? bVRJets.push_back(jet) : nonbVRJets.push_back(jet);
          else if (jet->pT() > 15. && jet->pT() < 20.)
            softB04.at(jet) ? bVRJets.push_back(jet) : nonbVRJets.push_back(jet);
        }

        // Continue to Analysis Coding: remove overlaping objects
        removeOverlap(baselineJets, baselineElectrons4Hard, 0.2, true);
        removeOverlap(baselineJets, baselineElectrons4Soft, 0.2, true);
        removeOverlap(baselineJets, baselineMuons4Hard, 0.2, true);
        removeOverlap(baselineJets, baselineMuons4Soft, 0.2, true);

        removeOverlap(baselineElectrons4Hard, baselineJets, 0.4, true);
        removeOverlap(baselineElectrons4Soft, baselineJets, 0.4, true);
        removeOverlap(baselineMuons4Hard, baselineJets, 0.4, true);
        removeOverlap(baselineMuons4Soft, baselineJets, 0.4, true);

        vector<const HEPUtils::Jet *> signalJets;
        vector<const HEPUtils::Jet *> bJets;
        vector<const HEPUtils::Jet *> nonbJets;
        // B-tag Efficiencies
        std::map<const Jet *, bool> analysisBtags = generateBTagsMap(baselineJets, 0.77, 1.0 / 6.0, 1.0 / 130.);
        for (const HEPUtils::Jet *jet : baselineJets)
        {
          if (jet->pT() > 25. && jet->abseta() < 2.5)
            signalJets.push_back(jet);
          bool isBTag = analysisBtags.at(jet);
          if (isBTag && jet->pT() > 20.)
            bJets.push_back(jet);
          else
            nonbJets.push_back(jet);
        }

        vector<const HEPUtils::Particle *> signalElectron4Hard, signalElectron4Soft;
        vector<const HEPUtils::Particle *> signalMuon4Hard, signalMuon4Soft;
        vector<const HEPUtils::Particle *> signalLeptons4Hard, signalLeptons4Soft;
        for (const HEPUtils::Particle *electron : baselineElectrons4Hard)
        {
          signalElectron4Hard.push_back(electron);
          signalLeptons4Hard.push_back(electron);
        }
        for (const HEPUtils::Particle *electron : baselineElectrons4Soft)
        {
          signalElectron4Soft.push_back(electron);
          signalLeptons4Soft.push_back(electron);
        }
        for (const HEPUtils::Particle *muon : baselineMuons4Hard)
        {
          signalMuon4Hard.push_back(muon);
          signalLeptons4Hard.push_back(muon);
        }
        for (const HEPUtils::Particle *muon : baselineMuons4Soft)
        {
          signalMuon4Soft.push_back(muon);
          signalLeptons4Soft.push_back(muon);
        }

        std::sort(signalElectron4Hard.begin(), signalElectron4Hard.end(), sortByPT_lep);
        std::sort(signalElectron4Soft.begin(), signalElectron4Soft.end(), sortByPT_lep);
        std::sort(signalMuon4Hard.begin(), signalMuon4Hard.end(), sortByPT_lep);
        std::sort(signalMuon4Soft.begin(), signalMuon4Soft.end(), sortByPT_lep);
        std::sort(signalLeptons4Hard.begin(), signalLeptons4Hard.end(), sortByPT_lep);
        std::sort(signalLeptons4Soft.begin(), signalLeptons4Soft.end(), sortByPT_lep);

        std::sort(signalJets.begin(), signalJets.end(), sortByPT_jet);
        // Preselection Criteria
        bool pre_hardlep = false;
        bool pre_softlep = false;

        // hard-lepton preselection
        const int nlephard = signalLeptons4Hard.size();
        const int njet = signalJets.size();
        const int nbjet = bJets.size();
        const double l1PT_hard = nlephard > 0 ? signalLeptons4Hard[0]->pT() : 0.;
        const double dPhijet1ET = njet > 0 ? signalJets[0]->mom().deltaPhi(metVec) : 0.;
        const double dPhijet2ET = njet > 1 ? signalJets[1]->mom().deltaPhi(metVec) : 0.;
        const double mT = nlephard > 0 ? get_mT(signalElectron4Hard[0], metVec) : 0.;
        const double mT2tau = (signalTaus.size() > 0 && nlephard > 0) ? get_mT2(signalTaus[0]->mom(), signalLeptons4Hard[0]->mom(), metVec, 0.) : 100.;

        bool pre_hard = nlephard == 1 && njet >= 4 && l1PT_hard > 25. && met > 230. && dPhijet1ET > 0.4 && dPhijet2ET > 0.4 && nbjet >= 1 && mT > 30. && mT2tau > 80.;

        const int nlepsoft = signalLeptons4Soft.size();
        const bool softJet1 = njet >= 1 ? signalJets[0]->pT() > 200. : false;
        const bool softJet2 = njet >= 2 ? signalJets[1]->pT() > 20. : false;
        const double dPhijet2ET_soft = njet >= 2 ? signalJets[1]->mom().deltaPhi(metVec) : 0.5;

        // All soft lepton pass the pT requirement
        bool pre_soft = nlepsoft == 1 && (softJet1 || softJet2) && met > 230. && dPhijet1ET > 0.4 && dPhijet2ET_soft > 0.4;

        // Define signal region for stop -> t N1
        if (pre_hard)
        {
          HEPUtils::P4 topRecl = reclusteredParticle(nonbJets, bJets, 175., true);
        }

        return;
      }

      void collect_results()
      {
        // add_result(SignalRegionData(_counters["SR label"], n_obs, {n_bkg, n_bkg_err}));
        add_result(SignalRegionData(_counters["SR-tN_med"], 21., {21., 4.0}));
        add_result(SignalRegionData(_counters["SR-tN_high"], 17., {9.5, 1.6}));
        add_result(SignalRegionData(_counters["SR-tN_diag_low"], 21., {15., 4.0}));
        add_result(SignalRegionData(_counters["SR-tN_diag_high"], 11., {10.1, 3.4}));
        add_result(SignalRegionData(_counters["SR-bWN"], 35., {44., 9.0}));
        add_result(SignalRegionData(_counters["SR-bffN_btag"], 14., {11.3, 1.4}));
        add_result(SignalRegionData(_counters["SR-bffN_softb"], 10., {8.7, 2.3}));
        add_result(SignalRegionData(_counters["SR-DM"], 56., {56.0, 8.0}));

        std::vector<YODA::AnalysisObject *> ao_list;
        ao_list.push_back(_hist_Topness.get());
        YODA::WriterYODA::write("ATLAS-SUSY-2018-007.yoda", ao_list);
      }

    protected:
      void analysis_specific_reset()
      {
        for (auto &pair : _counters)
        {
          pair.second.reset();
        }
      }

      ///////////////////
    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_1LEPStop_139invfb)

  }
}
