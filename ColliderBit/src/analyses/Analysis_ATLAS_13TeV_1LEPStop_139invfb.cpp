
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

    static double calcMT(HEPUtils::P4 lepmom, HEPUtils::P4 metMom)
    {
      // std::cout << "metMom.px() " << metMom.px() << " jetMom PT " << jetMom.pT() << std::endl;
      double met = sqrt(metMom.px() * metMom.px() + metMom.py() * metMom.py());
      double dphi = metMom.deltaPhi(lepmom);
      double mt = sqrt(2 * lepmom.pT() * met * (1 - std::cos(dphi)));
      return mt;
    }

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
        const double l1PT = nlephard > 0 ? signalLeptons4Hard[0]->pT() : 0.; 
        const double dPhijet1ET = njet > 0 ? signalJets[0]->mom().deltaPhi(metVec) : 0.;
        const double dPhijet2ET = njet > 1 ? signalJets[1]->mom().deltaPhi(metVec) : 0.;
        const double mT = nlephard > 0 ? get_mT(signalElectron4Hard[0], metVec) : 0.;
        const double mT2tau = (signalTaus.size() > 0 && nlephard > 0) ? get_mT2(signalTaus[0]->mom(), signalLeptons4Hard[0]->mom(), metVec, 0.) : 100.;

        bool pre_hard = nlephard == 1 && njet >= 4 && l1PT > 25. && met > 230. && dPhijet1ET > 0.4 && dPhijet2ET > 0.4 && nbjet >= 1 && mT > 30. && mT2tau > 80. ; 

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
