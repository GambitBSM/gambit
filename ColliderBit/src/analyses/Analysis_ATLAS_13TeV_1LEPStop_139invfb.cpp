
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

        // _counters["SR-tN_med"] = EventCounter("SR-tN_med");
        // _counters["SR-tN_high"] = EventCounter("SR-tN_high");
        // _counters["SR-tN_diag_low"] = EventCounter("SR-tN_diag_low");
        // _counters["SR-tN_diag_high"] = EventCounter("SR-tN_diag_high");
        // _counters["SR-bWN"] = EventCounter("SR-bWN");
        // _counters["SR-bffN_btag"] = EventCounter("SR-bffN_btag");
        // _counters["SR-bffN_softb"] = EventCounter("SR-bffN_softb");
        // _counters["SR-DM"] = EventCounter("SR-DM");

        // Set the analysis name
        set_analysis_name("ATLAS_13TeV_1LEPStop_139invfb");

        // Set the LHC luminosity
        set_luminosity(139.0);
      }

      void run(const HEPUtils::Event *event)
      {

        // Get the missing energy in the event
        double met = event->met();

        // Now define vectors of baseline objects,  including:
        // - retrieval of electron, muon and jets from the event)
        // - application of basic pT and eta cuts

        // Baseline electrons
        vector<const HEPUtils::Particle *> baselineElectrons;
        for (const HEPUtils::Particle *electron : event->electrons())
        {
          if (electron->pT() > 4.5 && fabs(electron->eta()) < 2.47)
            baselineElectrons.push_back(electron);
        }

        // Baseline muons
        vector<const HEPUtils::Particle *> baselineMuons;
        for (const HEPUtils::Particle *muon : event->muons())
        {
          if (muon->pT() > 4.0 && fabs(muon->eta()) < 2.7)
            baselineMuons.push_back(muon);
        }

        // Baseline jets
        vector<const HEPUtils::Jet *> baselineJets;
        for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
        {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5)
            baselineJets.push_back(jet);
        }

        vector<const HEPUtils::Jet *> bJets;
        vector<const HEPUtils::Jet *> nonbJets;

        // B-tag Efficiencies
        std::map<const Jet *, bool> analysisBtags = generateBTagsMap(baselineJets, 0.77, 1.0 / 6.0, 1.0 / 130.);
        for (const HEPUtils::Jet *jet : baselineJets)
        {
          bool isBTag = analysisBtags.at(jet);
          if (isBTag && jet->pT() > 20.)
            bJets.push_back(jet);
          else
            nonbJets.push_back(jet);
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
        for (auto *p : event->particles())
        {
          if (p->charge3() != 0 && p->pT() > 0.5 && std::fabs(p->eta()) < 2.5)
          {
            fastjet::PseudoJet pj(p->px(), p->py(), p->pz(), p->E());
            fj_tracks.push_back(pj);
          }
        }

        // 2. Define the anti-kt Variable‐R jet
        double rho = 30.0;
        double Rmin = 0.02;
        double Rmax = 0.4;

        fastjet::contrib::VariableRPlugin vr_plugin(rho, Rmin, Rmax);
        // fastjet::contrib::VariableRPlugin vr_plugin(rho, Rmin, Rmax, fastjet::contrib::VariableRPlugin::ONE_SCALE);
        fastjet::JetDefinition jet_def(&vr_plugin);
        // 3. Clustering the VR-Jet
        fastjet::ClusterSequence cseq(fj_tracks, jet_def);
        std::vector<fastjet::PseudoJet> vr_pseudojets = fastjet::sorted_by_pt(cseq.inclusive_jets(5.0));
        // 4. Converting into the HEPUtils Pseudo-Jet
        std::vector<HEPUtils::Jet *> VR_jets;
        for (auto &pj : vr_pseudojets)
        {
          HEPUtils::Jet *hj = new HEPUtils::Jet(pj);
          VR_jets.push_back(hj);
        }

        // Define the lowPT b-jet
        std::vector<HEPUtils::Jet *> bVRJets;
        std::vector<HEPUtils::Jet *> nonbVRJets;

        // B-tag Efficiencies: Figure 3 of ATLAS-CONF-2019-027
        std::map<const Jet *, bool> softB01 = generateBTagsMap(VR_jets, 0.35144, 0.17459, 0.01457); // 5-7
        std::map<const Jet *, bool> softB02 = generateBTagsMap(VR_jets, 0.52632, 0.19230, 0.01796); // 7-10
        std::map<const Jet *, bool> softB03 = generateBTagsMap(VR_jets, 0.61460, 0.15541, 0.01233); // 10-15
        std::map<const Jet *, bool> softB04 = generateBTagsMap(VR_jets, 0.69100, 0.17410, 0.01259); // 15-20
        std::map<const Jet *, bool> softB05 = generateBTagsMap(VR_jets, 0.75722, 0.17262, 0.01125); // 20-30

        for (const HEPUtils::Jet *jet : VR_jets)
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

        for (auto *j : vr_jets)
        {
          // Probability-based tagging, or look up flavor truth from the event record
          bool isBtag = random_bool(my_soft_b_eff) && j->btag();
          if (isBtag)
            bVRJets.push_back(j);
        }

        removeOverlap(baselineJets, baselineElectrons, 0.2, true);

        // Could add ATLAS style overlap removal here
        // See Analysis_ATLAS_0LEP_20invfb for example

        // Could add ATLAS or CMS efficiencies here
        // See Analysis_ATLAS_2LEPEW_20invfb.cpp for an example

        // int nElectrons = baselineElectrons.size();
        // int nMuons = baselineMuons.size();
        // int nJets = baselineJets.size();

        // std::cerr << "nElectrons " << nElectrons << " nMuons " << nMuons << " nJets " << nJets << " met " << met << std::endl;

        // Increment number of events passing signal region cuts
        // Dummy signal region: need 2 jets, met > 150 and no leptons

        // if((nElectrons+nMuons)==0 && nJets==2 && met>150.) _counters["SR"].add_event(event);

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
