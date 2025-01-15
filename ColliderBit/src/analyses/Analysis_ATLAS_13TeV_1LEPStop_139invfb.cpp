
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"

#include <memory> // Required for std::shared_ptr
#include <YODA/Histo1D.h>
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

        // Now fill a results object with the result for our signal region
        // We have made up a number of observed events
        // We have also made up a number of predicted background events (with a made up uncertainty)

        // add_result(SignalRegionData(_counters["SR label"], n_obs, {n_bkg, n_bkg_err}));
        add_result(SignalRegionData(_counters["SR-tN_med"], 21., {21., 4.0}));
        add_result(SignalRegionData(_counters["SR-tN_high"], 17., {9.5, 1.6}));
        add_result(SignalRegionData(_counters["SR-tN_diag_low"], 21., {15., 4.0}));
        add_result(SignalRegionData(_counters["SR-tN_diag_high"], 11., {10.1, 3.4}));
        add_result(SignalRegionData(_counters["SR-bWN"], 35., {44., 9.0}));
        add_result(SignalRegionData(_counters["SR-bffN_btag"], 14., {11.3, 1.4}));
        add_result(SignalRegionData(_counters["SR-bffN_softb"], 10., {8.7, 2.3}));
        add_result(SignalRegionData(_counters["SR-DM"], 56., {56.0, 8.0}));
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
