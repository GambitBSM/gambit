///
///  \author Christopher Chang
///  \date 2021 March
///
///  *********************************************

// Based on https://arxiv.org/pdf/1909.09226.pdf

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisUtil.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

//#define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_1Lep2b_139invfb : public Analysis
    {

    public:

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        {"WREM_cuts_0", EventCounter("WREM_cuts_0")},
        {"STCREM_cuts_0", EventCounter("STCREM_cuts_0")},
        {"TRHMEM_cuts_0", EventCounter("TRHMEM_cuts_0")},
        {"TRMMEM_cuts_0", EventCounter("TRMMEM_cuts_0")},
        {"TRLMEM_cuts_0", EventCounter("TRLMEM_cuts_0")},
        {"SRHMEM_mct2_0", EventCounter("SRHMEM_mct2_0")},
        {"SRHMEM_mct2_1", EventCounter("SRHMEM_mct2_1")},
        {"SRHMEM_mct2_2", EventCounter("SRHMEM_mct2_2")},
        {"SRMMEM_mct2_0", EventCounter("SRMMEM_mct2_0")},
        {"SRMMEM_mct2_1", EventCounter("SRMMEM_mct2_1")},
        {"SRMMEM_mct2_2", EventCounter("SRMMEM_mct2_2")},
        {"SRLMEM_mct2_0", EventCounter("SRLMEM_mct2_0")},
        {"SRLMEM_mct2_1", EventCounter("SRLMEM_mct2_1")},
        {"SRLMEM_mct2_2", EventCounter("SRLMEM_mct2_2")},
      };

      #ifdef CHECK_CUTFLOW
        Cutflows _cutflows;
      #endif

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_1Lep2b_139invfb()
      {

        analysis_specific_reset();
        set_analysis_name("ATLAS_13TeV_1Lep2b_139invfb");
        set_luminosity(139.);
        set_bkgjson("ColliderBit/data/analyses_json_files/ATLAS_13TeV_1Lep2b_139invfb_bkgonly.json");

        #ifdef CHECK_CUTFLOW
          // Book Cutflows
          _cutflows.addCutflow("SR",{"no cut",
                                        "Njet > 2",
                                        "1st signal lepton",
                                        "2nd baseline lepton",
                                        "mT > 50 GeV",
                                        "MET > 180 GeV",
                                        "N jet < 3",
                                        "Nbjet = 2",
                                        "mbb > 50 GeV",
                                        "MET > 240 GeV",
                                        "mbb [100,140]",
                                        "mlb > 120 GeV",
                                        "mT cut"});
        #endif


      }

      // Lepton jet overlap removal
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*>& leptons, vector<const HEPUtils::Jet*>& jets)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* lepton : leptons)
        {
          bool overlap = false;
          double DeltaRMax = min(0.4,0.04 + 10 / (lepton->pT()));
          for(const HEPUtils::Jet* jet : jets)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(lepton);
        }
        leptons = survivors;
        return;
      }

      // Jet lepton overlap removal
      // Discards jets if they are within DeltaRMax of a lepton
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*>& jets, vector<const HEPUtils::Particle*>& leptons, double DeltaRMax)
      {
        vector<const HEPUtils::Jet*> survivors;
        for(const HEPUtils::Jet* jet : jets)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* lepton: leptons)
          {
            double dR = lepton->mom().deltaR_eta(jet->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(jet);
        }
        jets = survivors;
        return;
      }

      // Particle overlap removal
      // Discards particle (from "particles1") if it is within DeltaRMax of another particle
      void ParticleOverlapRemoval(vector<const HEPUtils::Particle*>& particles1, vector<const HEPUtils::Particle*>& particles2, double DeltaRMax)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* p1 : particles1)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* p2 : particles2)
          {
            double dR = p1->mom().deltaR_eta(p2->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(p1);
        }
        particles1 = survivors;
        return;
      }

      bool sortJetsByPt(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2)
      {
        return (jet1->pT() > jet2->pT());
      }

      void run(const HEPUtils::Event* event)
      {

        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          _cutflows.fillinit(w);
          _cutflows.fillnext(w); // no cut
        #endif

        HEPUtils::P4 pmiss = event->missingmom();
        double met = event->met();

        // Baseline lepton objects
        vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 7 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 6 && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        ATLAS::applyMuonEff(baselineMuons);


        vector<const Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT() > 20.0 && jet->abseta() < 4.5)
          {
            baselineJets.push_back(jet);
          }

        }

        // B-tag efficiencies
        std::map<const Jet*,bool> analysisBtags = generateBTagsMap(baselineJets,0.77,0.204,0.009);

        vector<const HEPUtils::Jet*> baselineNonBJets;
        vector<const HEPUtils::Jet*> baselineBJets;
        for (const HEPUtils::Jet* j : baselineJets)
        {
          if (j->abseta() < 2.5 && analysisBtags.at(j))
          {
            baselineBJets.push_back(j);
          }
          else
          {
            baselineNonBJets.push_back(j);
          }
        }

        // Remove Overlapped electrons, muons and jets
        // 1. If electrons or muons share the same track (by using small deltaR), reject electron
        ParticleOverlapRemoval(baselineElectrons, baselineMuons, 0.01);
        // 2. Jets are rejected if they lie within deltaR=0.2 of a muon
        JetLeptonOverlapRemoval(baselineNonBJets, baselineMuons, 0.2);
        JetLeptonOverlapRemoval(baselineBJets, baselineMuons, 0.2);
        JetLeptonOverlapRemoval(baselineNonBJets, baselineElectrons, 0.2);
        JetLeptonOverlapRemoval(baselineBJets, baselineElectrons, 0.2);
        // 3. Electrons are removed if theu lie in a cone (see function for size) around a jet
        LeptonJetOverlapRemoval(baselineElectrons, baselineNonBJets);
        LeptonJetOverlapRemoval(baselineElectrons, baselineBJets);
        // 4. Muons are removed if theu lie in a cone (see function for size) around a jet
        LeptonJetOverlapRemoval(baselineMuons, baselineNonBJets);
        LeptonJetOverlapRemoval(baselineMuons, baselineBJets);


        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Jet*> signalBJets;

        // Get jets (including b-tagged)
        for (const Jet* jet : baselineNonBJets) {
          if (jet->pT() > 30 && jet->abseta() < 2.8 ) {
            signalNonBJets.push_back(jet);
          }
        }

        for (const Jet* jet : baselineBJets) {
          if (jet->pT() > 30 && jet->abseta() < 2.8 ) {
            signalBJets.push_back(jet);
          }
        }

        vector<const HEPUtils::Jet*> signalJets = signalBJets;
        signalJets.insert(signalJets.end(), signalNonBJets.begin(), signalNonBJets.end());

        // electrons
        vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
        ATLAS::applyLooseIDElectronSelectionR2(signalElectrons);

        // muons
        vector<const HEPUtils::Particle*> signalMuons = baselineMuons;

        // all leptons
        vector<const HEPUtils::Particle*> signalLeptons;
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Sort in order of decreasing pT
        sortByPt(signalBJets);
        sortByPt(signalNonBJets);
        sortByPt(signalJets);
        sortByPt(signalElectrons);
        sortByPt(signalMuons);
        sortByPt(signalLeptons);

          /////////////////////
         // Event Selection //
        /////////////////////

        bool SR_njet_geq_2 = false;
        bool SR_nlep_gt_0 = false;
        bool SR_nlep_lt_2 = false;
        bool SR_mt_gt_50 = false;
        bool SR_ETmiss_gt_180 = false;
        bool SR_njet_leq_3 = false;
        bool SR_nbjet_eq_2 = false;
        bool SR_mbb_gt_50 = false;
        bool SR_ETmiss_gt_240 = false;

        bool SR_mbb_100_140 = false;

        bool SR_mlb_gt_120 = false;

        bool SR_mt_100_160 = false;
        bool SR_mt_160_240 = false;
        bool SR_mt_gt_240 = false;

        bool SR_mct_180_230 = false;
        bool SR_mct_230_280 = false;
        bool SR_mct_gt_280 = false;

        // Performing the Cuts
        while(true)
        {

          // Require at least 2 jets
          if (signalJets.size() >= 2) {SR_njet_geq_2 = true;}
          else break;

          // Require at least 1 signal lepton
          if (signalLeptons.size() > 0) {SR_nlep_gt_0 = true;}
          else break;

          // Require no more than 1 signal lepton
          if (signalLeptons.size() < 2) {SR_nlep_lt_2 = true;}
          else break;

          // Calculating mT
          double mT = sqrt(2* signalLeptons[0]->pT() * met * (1. - cos(deltaPhi(signalLeptons[0]->mom(), pmiss))));

          // Require mT > 50 GeV
          if (mT > 50) {SR_mt_gt_50 = true;}
          else break;

          // Require ETmiss > 180 GeV
          if (met > 180) {SR_ETmiss_gt_180 = true;}
          else break;

          // Require no more than three jets
          if (signalJets.size() <= 3) {SR_njet_leq_3 = true;}
          else break;

          // Require exactly 2 b-tagged jets
          if (signalBJets.size() == 2) {SR_nbjet_eq_2 = true;}
          else break;

          // Calculating mbb
          double mbb = (signalBJets[0]->mom() + signalBJets[1]->mom()).m();

          // Require mbb > 50 GeV
          if (mbb > 50) {SR_mbb_gt_50 = true;}
          else break;

          // Require ETmiss > 240 GeV
          if (met > 240) {SR_ETmiss_gt_240 = true;}
          else break;

          // Require mbb [100,140]
          if (mbb > 100 && mbb < 140) {SR_mbb_100_140 = true;}
          else break;

          // Calculating mlb
          double mlb = (signalBJets[0]->mom() + signalLeptons[0]->mom()).m();

          // Require mlb>120 (only for one signal region, hence no break until later)
          if (mlb > 120) {SR_mlb_gt_120 = true;}

          // Calculate mT bins
          if (mT > 100 && mT < 160) {SR_mt_100_160 = true;}
          else if (mT > 160 && mT < 240) {SR_mt_160_240 = true;}
          else if (mT > 240 && SR_mlb_gt_120) {SR_mt_gt_240 = true;} //This includes both mT and mlb cut
          else break; 

          // Calculating mCT
          double mCT = sqrt(2 * (signalBJets[0]->pT()) * (signalBJets[1]->pT()) * (1. + cos(deltaPhi(signalBJets[0]->mom(), signalBJets[1]->mom()) ) ));

          // Calculate mCT bins
          if (mCT > 180 && mCT < 230) {SR_mct_180_230 = true;}
          else if (mCT > 230 && mCT < 280) {SR_mct_230_280 = true;}
          else if (mCT > 280) {SR_mct_gt_280 = true;}
          else break; 

          // Applied all cuts
          break;
        }

        // Fill cutflow
        #ifdef CHECK_CUTFLOW
          if (SR_njet_geq_2) _cutflows["SR"].fillnext(w);
          if (SR_nlep_gt_0) _cutflows["SR"].fillnext(w);
          if (SR_nlep_lt_2) _cutflows["SR"].fillnext(w);
          if (SR_mt_gt_50) _cutflows["SR"].fillnext(w);
          if (SR_ETmiss_gt_180) _cutflows["SR"].fillnext(w);
          if (SR_njet_leq_3) _cutflows["SR"].fillnext(w);
          if (SR_nbjet_eq_2) _cutflows["SR"].fillnext(w);
          if (SR_mbb_gt_50) _cutflows["SR"].fillnext(w);
          if (SR_ETmiss_gt_240) _cutflows["SR"].fillnext(w);
          if (SR_mbb_100_140) _cutflows["SR"].fillnext(w);
          if (SR_mlb_gt_120) _cutflows["SR"].fillnext(w);
          
          // @todo change such that all three mT bin cuts be checked at once
          //if (SR_mt_100_160) _cutflows["SR"].fillnext(w);
          //if (SR_mt_160_240) _cutflows["SR"].fillnext(w);
          if (SR_mt_gt_240) _cutflows["SR"].fillnext(w);
        #endif

        // Fill SR's
        if (SR_njet_geq_2 && SR_nlep_gt_0 && SR_nlep_lt_2 && SR_mt_gt_50 && SR_ETmiss_gt_180 && SR_njet_leq_3 && SR_nbjet_eq_2 && SR_mbb_gt_50 && SR_ETmiss_gt_240 && SR_mbb_100_140)
        {
          // SR low mCT
          if (SR_mt_100_160)
          {
            if (SR_mct_180_230) _counters.at("SRLMEM_mct2_0").add_event(event);
            if (SR_mct_230_280) _counters.at("SRLMEM_mct2_1").add_event(event);
            if (SR_mct_gt_280) _counters.at("SRLMEM_mct2_2").add_event(event);
          }

          // SR med mCT
          if (SR_mt_160_240)
          {
            if (SR_mct_180_230) _counters.at("SRMMEM_mct2_0").add_event(event);
            if (SR_mct_230_280) _counters.at("SRMMEM_mct2_1").add_event(event);
            if (SR_mct_gt_280) _counters.at("SRMMEM_mct2_2").add_event(event);
          }

          // SR high mCT
          if (SR_mt_gt_240)
          {
            if (SR_mct_180_230) _counters.at("SRHMEM_mct2_0").add_event(event);
            if (SR_mct_230_280) _counters.at("SRHMEM_mct2_1").add_event(event);
            if (SR_mct_gt_280) _counters.at("SRHMEM_mct2_2").add_event(event);
          }

        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_1Lep2b_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_1Lep2b_139invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }

      void collect_results() { 
        //This data is used if not running ATLAS_FullLikes. 
        add_result(SignalRegionData(_counters.at("WREM_cuts_0"), 144, {144.0,0.0 })); //Hard-setting equal obs and pred
        add_result(SignalRegionData(_counters.at("STCREM_cuts_0"), 155, {155.0, 0.0})); //Hard-setting equal obs and pred
        add_result(SignalRegionData(_counters.at("TRHMEM_cuts_0"), 641, {641.0,0.0 })); //Hard-setting equal obs and pred
        add_result(SignalRegionData(_counters.at("TRMMEM_cuts_0"), 491, {491.0,0.0 })); //Hard-setting equal obs and pred
        add_result(SignalRegionData(_counters.at("TRLMEM_cuts_0"), 657, {657.0,0.0 })); //Hard-setting equal obs and pred
        add_result(SignalRegionData(_counters.at("SRHMEM_mct2_0"), 6, {4.1, 1.9}));
        add_result(SignalRegionData(_counters.at("SRHMEM_mct2_1"), 5, {2.9, 1.3}));
        add_result(SignalRegionData(_counters.at("SRHMEM_mct2_2"), 3, {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("SRMMEM_mct2_0"), 4, {4.6, 1.7}));
        add_result(SignalRegionData(_counters.at("SRMMEM_mct2_1"), 7, {2.6, 1.3}));
        add_result(SignalRegionData(_counters.at("SRMMEM_mct2_2"), 2, {1.4, 0.6}));
        add_result(SignalRegionData(_counters.at("SRLMEM_mct2_0"), 16 , {8.8, 2.8}));
        add_result(SignalRegionData(_counters.at("SRLMEM_mct2_1"), 11 , {11.3, 3.1}));
        add_result(SignalRegionData(_counters.at("SRLMEM_mct2_2"), 7 , {7.3, 1.5}));

        #ifdef CHECK_CUTFLOW
          // Cutflow printout
          cout << "\nCUTFLOWS:\n" << _cutflows << endl;
          cout << "\nSRCOUNTS:\n";
          for (auto& pair : _counters) cout << pair.first << ": " << pair.second.weight_sum() << "\n";
          cout << "\n" << endl;
        #endif

      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_1Lep2b_139invfb)

  }
}
