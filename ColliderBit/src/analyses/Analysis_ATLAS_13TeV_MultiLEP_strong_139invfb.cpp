// -*- C++ -*-
///
///  \author Anders Kvellestad
///  \date 2020 June
///  *********************************************
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
// #include "Eigen/Eigen"

// #define CHECK_CUTFLOW

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;

    /// @brief ATLAS Run 2 search for same-sign leptons and jets, with 139/fb of data
    ///
    /// Based on:
    ///   - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-09/
    ///   - https://arxiv.org/pdf/1909.08457
    ///   - https://www.hepdata.net/record/ins1754675
    ///   - C++ code example and SLHA benchmark files available on HEPData (link above)
    /// 
    /// Cross-sections for cutflows taken from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections#Cross_sections_for_various_subpr
    /// 

    /* 
      Notes on analysis logic:
      ------------------------

      *** From Sec 3: Event reconstruction ***

      - anti-kT R = 0.4

      - jet |eta| < 4.9
      - jet pT > 20 GeV
      - jet |eta| < 2.8 in "multiplicity-based requirements"

      - b-tagging for jets within |eta| < 2.5, using MV2c10 b-tagging algorithm

      - basline muons: 
        - |eta| < 2.5
        - pT > 10 GeV
      - signal muons:
        - sufficiently isolated from jets and other leptons

      - basline electrons: 
        - |eta| < 2.47, excluding the range (1.37, 1.52)
        - pT > 10 GeV
      - signal electrons:
        - |eta| < 2.0
        - sufficiently isolated from jets and other leptons

      - ETmiss has a "soft term" correction

      - Overlap removal:
        - Exclude any baseline leptons that are too close to a jet. 
          Requirement:

            Delta R > min(0.4, 0.1 + 9.6 [GeV] / pT_lepton)

          where Delta R = sqrt((Delta y)^2 + (Delta phi)^2)


      *** From Sec 4: Event selection ***
      
      - At least two signal leptons with pT > 20 GeV

      - If only two leptons: must have same sign
      - Else if more than two leptons (pT > 10 GeV): no sign requirement
      
      - [ETmiss-dependent trigger details in second paragraph of Sec 4 ignored for now]

      - Selection variables:

        - nl: number of signal leptons
        - nb: number of signal b-jets
        - nj: number of signal jets (with some pT requirement)
        - ETmiss (aka met)
        - meff: ETmiss + *scalar* sum of pTs for all jets and leptons (signal or baseline objects?)
        - ETmiss / meff
        - mee_near_mZ: is there a same-sign(!) electron pair with an invariant mass near mZ, i.e. in (81,101) GeV?

      - Five signal regions (units GeV):
        - Rpv2L: nl >= 2; nb >= 0; nj >= 6 (pT > 40); meff > 2600 
        - Rpc2L0b: nl >= 2; nb == 0; nj >= 6 (pT > 40); ETmiss > 200; meff > 1000; ETmiss/meff > 0.2 
        - Rpc2L1b: nl >= 2; nb >= 1; nj >= 6 (pT > 40); ETmiss/meff > 0.25 
        - Rpc2L2b: nl >= 2; nb >= 2; nj >= 6 (pT > 25); ETmiss > 300; meff > 1400; ETmiss/meff > 0.14 
        - Rpc3LSS1b: nl >= 3 (same sign); nb >= 1; not mee_near_mZmee; ETmiss/meff > 0.14 

    */


    class Analysis_ATLAS_13TeV_MultiLEP_strong_139invfb : public Analysis 
    {
    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      // Numbers passing cuts
      std::map<string, EventCounter> _counters = {
        {"Rpv2L", EventCounter("Rpv2L")},
        {"Rpc2L0b", EventCounter("Rpc2L0b")},
        {"Rpc2L1b", EventCounter("Rpc2L1b")},
        {"Rpc2L2b", EventCounter("Rpc2L2b")},
        {"Rpc3LSS1b", EventCounter("Rpc3LSS1b")},
      };

      #ifdef CHECK_CUTFLOW
        Cutflows _cutflows;
      #endif


      Analysis_ATLAS_13TeV_MultiLEP_strong_139invfb() 
      {
        set_analysis_name("ATLAS_13TeV_MultiLEP_strong_139invfb");
        set_luminosity(139.0);


        #ifdef CHECK_CUTFLOW
          // Book cutflows
          _cutflows.addCutflow("Rpc2L1b", {"no cut",
                                           "trigger",
                                           ">= 2 SS leptons (pT > 20)",
                                           ">= 1 b-jet",
                                           ">= 6 jets (pT > 40)",
                                           "met/meff >= 0.25"});
        #endif
      }


      void run(const Event* event) 
      {
        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          _cutflows.fillinit(w);
          _cutflows.fillnext(w);  // no cut
        #endif

        // Missing energy
        /// @todo Compute from hard objects instead?
        // const P4 pmiss = event->missingmom();
        // const double met = event->met();


        // Containers for baseline objects
        vector<const Particle*> baselineElectrons;
        vector<const Particle*> baselineMuons;
        vector<const Jet*> baselineJets;

        // Get baseline electrons and apply efficiency
        for (const Particle* electron : event->electrons()) 
        {
          if (electron->pT() > 10. && electron->abseta() < 2.47)
          {
            if (electron->abseta() < 1.37 || electron->abseta() > 1.52)
            {
              baselineElectrons.push_back(electron);
            }
          }
        }
        ATLAS::applyElectronEff(baselineElectrons);
        ATLAS::applyElectronIDEfficiency2019(baselineElectrons, "Loose");
        /// @todo Use applyElectronIsolationEfficiency2019 or something similar?

        // Get baseline muons and apply efficiency
        for (const Particle* muon : event->muons()) 
        {
          if (muon->pT() > 10. && muon->abseta() < 2.5)
          {
            baselineMuons.push_back(muon);
          }
        }
        ATLAS::applyMuonEff(baselineMuons);


        // Get baseline jets
        /// @todo Drop b-tag if |eta| > 2.5?
        for (const Jet* jet : event->jets()) 
        {
          if (jet->pT() > 20. && jet->abseta() < 2.8) 
          {
            baselineJets.push_back(jet);
          }
        }

        // Alternative met construction 1
        // P4 pmiss_sum;
        // for (const Particle* p : baselineElectrons) { pmiss_sum -= p->mom(); }
        // for (const Particle* p : baselineMuons) { pmiss_sum -= p->mom(); }
        // for (const Particle* p : event->photons()) { pmiss_sum -= p->mom(); }
        // for (const Jet* j : baselineJets) { pmiss_sum -= j->mom(); }
        // const double met = pmiss_sum.pT();

        // Alternative met construction 2
        double ht = 0;
        for (const Particle* p : event->visible_particles()) ht += p->pT();
        P4 pmiss = event->missingmom();
        ATLAS::smearMET(pmiss, ht);
        const double met = pmiss.pT();


        // DEBUG: Get number of true baseline b-jets
        int nBaseBjetsTrue = 0;
        for (const Jet* j : baselineJets)
        {
          if (j->btag()) { nBaseBjetsTrue++; }
        }


        // Get map<Jet*,bool> with generated btags for this analysis.
        // B-tag efficiencies:
        // - for correctly tagging a b-jet: 70%
        // - for misstagging a c-jet: 9%
        // - for misstagging a gluon or light-quark jet: 0.3%
        // Other inputs for tagging: 
        // - pTmin = 0 GeV (baselineJets anyways only includes jets with pT > 20 GeV)
        // - absEtaMax = 2.5
        std::map<const Jet*,bool> analysisBtags = generateBTagsMap(baselineJets, 0.7, 0.09, 0.003, 0., 2.5);


        // 
        // Overlap removal
        // 
        const bool use_rapidity = true;

        // 1) Remove jets within DeltaR = 0.2 of electron
        // If b-tagging efficiency > 85%, do not remove jet.
        removeOverlap(baselineJets, baselineElectrons, 0.2, use_rapidity, DBL_MAX, 0.85);
        // removeOverlap(baselineJets, baselineElectrons, 0.2, use_rapidity, DBL_MAX);
        // This is a guess, based on 1706.03731
        removeOverlapIfBjet(baselineElectrons, baselineJets, 0.2, use_rapidity, DBL_MAX);
        // Corresponding line from ATLAS code snippet:
        //   jets = overlapRemoval(jets, baselineElectrons, 0.2, NOT(BTag85MV2c10)); /// not entirely correct

        // 2) Remove jets within DeltaR = 0.4 of muon
        removeOverlap(baselineJets, baselineMuons, 0.4, use_rapidity, DBL_MAX);
        // This is a guess, based on 1706.03731
        removeOverlapIfBjet(baselineMuons, baselineJets, 0.4, use_rapidity, DBL_MAX);
        // Corresponding line from ATLAS code snippet:
        //   jets = overlapRemoval(jets, baselineMuons, 0.4, LessThan3Tracks); 

        // Construct a lambda function to calculate the DeltaR limit as function of lepton pT
        auto deltaRLimitFunc = [](double pT_lepton) { return std::min(0.4, 0.1 + 9.6 / pT_lepton); };

        // 3) Remove electrons within DeltaR = min(0.4, 0.1 + 9.6 GeV / pT(e)) of a jet
        removeOverlap(baselineElectrons, baselineJets, deltaRLimitFunc, use_rapidity, DBL_MAX);
        // Corresponding lines from ATLAS code snippet:
        //   auto radiusCalcEl = [] (const AnalysisObject& electron, const AnalysisObject& ) { return 0.1 + 9.6/electron.Pt(); };
        //   baselineElectrons = overlapRemoval(baselineElectrons, jets, radiusCalcEl); 

        // 4) Remove muons within DeltaR = min(0.4, 0.1 + 9.6 GeV / pT(e)) of a jet
        removeOverlap(baselineMuons, baselineJets, deltaRLimitFunc, use_rapidity, DBL_MAX);
        // Corresponding lines from ATLAS code snippet:
        //   auto radiusCalcMuon = [] (const AnalysisObject& muon, const AnalysisObject& ) { return 0.1 + 9.6/muon.Pt(); };
        //   baselineMuons = overlapRemoval(baselineMuons, jets, radiusCalcMuon); 

        // 5) Remove electrons within DeltaR = 0.01 of muons
        removeOverlap(baselineElectrons, baselineMuons, 0.01, use_rapidity, DBL_MAX);
        // Corresponding lines from ATLAS code snippet:
        //   baselineElectrons = overlapRemoval(baselineElectrons, baselineMuons,0.01);  

        // Collect all baseline leptons
        vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());


        // Signal object containers
        vector<const HEPUtils::Jet*> signalJets = baselineJets;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
        vector<const HEPUtils::Particle*> signalLeptons;

        // Require signalElectrons within |eta| < 2.0 and apply "Medium" ID efficiency
        // Corresponding lines from ATLAS code snippet:
        //   auto signalElectrons = filterObjects(baselineElectrons, 10, 2.0, EMediumLH|EIsoFCTight);  /// missing ECIDS
        for (const Particle* p : baselineElectrons)
        {
          if (p->abseta() < 2.0) { signalElectrons.push_back(p); }
        }
        ATLAS::applyElectronIDEfficiency2019(signalElectrons, "Medium");

        // Collect all signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Sort by pT
        sortByPt(baselineLeptons);
        sortByPt(signalLeptons);
        sortByPt(signalElectrons);
        sortByPt(signalMuons);
        sortByPt(signalJets);

        // Count signal objects
        // const size_t nBaseLeptons = baselineLeptons.size();
        const size_t nLeptons = signalLeptons.size();
        const size_t nElectrons = signalElectrons.size();
        // const size_t nMuons = signalMuons.size();


        // 
        // Preselection
        // 
        // Require at least two leptons
        if (nLeptons < 2) return;

        const Particle* lep0 = signalLeptons[0];
        const Particle* lep1 = signalLeptons[1];

        // Emulate lepton-based triggers
        if (met < 250.)
        {
          if (lep0->abspid() == 11 && lep1->abspid() == 11 && lep0->pT() < 24.) { return; }  // 2e trigger
          if (lep0->abspid() == 13 && lep1->abspid() == 13 && lep0->pT() < 21.) { return; }  // 2mu trigger
          if (lep0->abspid() == 11 && lep1->abspid() == 13 && lep0->pT() < 17 ) { return; }  // 1e1mu trigger, leading e
          if (lep0->abspid() == 13 && lep1->abspid() == 11 && lep0->pT() < 14 ) { return; }  // 1e1mu trigger, leading mu 
        }

        // Require pT > 20 GeV for the first two leptons
        if (lep1->pT() < 20) return;

        #ifdef CHECK_CUTFLOW
          _cutflows["Rpc2L1b"].fillnext(w);  // "trigger"
        #endif


        // If only two leptons, they must be same sign.
        if (nLeptons == 2 && (lep0->pid() * lep1->pid() < 0.)) return;

        #ifdef CHECK_CUTFLOW
          _cutflows["Rpc2L1b"].fillnext(w);  // >= 2 SS leptons (pT > 20)
        #endif


        //
        // Construct selection variables for the different SRs
        //

        int nJets25 = countPt(signalJets, 25.);
        int nJets40 = countPt(signalJets, 40.);

        double meff = scalarSumPt(signalLeptons) + scalarSumPt(signalJets) + met;
        double met_meff_ratio = met / meff; 


        // Count number of b-tagged jets in signalJets
        int nBJets20 = 0;
        int nBJets20true = 0;
        for (const Jet* j : signalJets)
        {
          if (j->btag()) { nBJets20true++; }
          if (analysisBtags.at(j)) { nBJets20++; }
        }

        // If three or more leptons, the Rpc3LSS1b SR requires 3 same-sign leptons
        bool is3LSS = false;
        int nPosLep = 0;
        int nNegLep = 0;
        for (const Particle* p : signalLeptons)
        {
          int pid = p->pid();
          if (pid == 11 || pid == 13) { nNegLep++; }  // electrons or muons
          else if (pid == -11 || pid == -13) { nPosLep++; }  // antielectron or antimuon
        }
        if (nPosLep >= 3 || nNegLep >= 3) { is3LSS = true; }

        // The Rpc3LSS1b SR vetos events with an same-sign electron pair 
        // with invariant mass close to the Z mass 
        bool mee_near_mZ = false;
        if (nElectrons >= 2)
        {
          vector<vector<const HEPUtils::Particle*>> elSSpairs = getSSpairs(signalElectrons);
          for(vector<const HEPUtils::Particle*>& pair : elSSpairs)
          {
            double mee = (pair.at(0)->mom() + pair.at(1)->mom()).m();
            if (mee > 81. && mee < 101.) 
            { 
              mee_near_mZ = true;
              break;
            }
          }
        }


        // 
        // Fill SR counters
        // 

        // Rpv2L:
        if (nLeptons >= 2 && nBJets20 >= 0 && nJets40 >= 6 && meff > 2600.) _counters.at("Rpv2L").add_event(event);

        // Rpc2L0b
        if (nLeptons >= 2 && nBJets20 == 0 && nJets40 >= 6 && met > 200. && meff > 1000. && met_meff_ratio > 0.2) _counters.at("Rpc2L0b").add_event(event);

        // Rpc2L1b
        #ifdef CHECK_CUTFLOW
          _cutflows["Rpc2L1b"].filltail({nBJets20 >= 1, nJets40 >= 6, met_meff_ratio > 0.25}, w);
        #endif
        if (nLeptons >= 2 && nBJets20 >= 1 && nJets40 >= 6 && met_meff_ratio > 0.25) _counters.at("Rpc2L1b").add_event(event);

        // Rpc2L2b
        if (nLeptons >= 2 && nBJets20 >= 2 && nJets25 >= 6 && met > 300. && meff > 1400. && met_meff_ratio > 0.14) _counters.at("Rpc2L2b").add_event(event);

        // Rpc3LSS1b
        if (nLeptons >= 3 && is3LSS && nBJets20 >= 1 && !mee_near_mZ && met_meff_ratio > 0.14) _counters.at("Rpc3LSS1b").add_event(event);

      }


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_MultiLEP_strong_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_MultiLEP_strong_139invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      /// Register results objects with the results for each SR; obs & bkg numbers from the paper
      void collect_results() 
      {
        // Using average, symmetrized background errors 
        add_result(SignalRegionData(_counters.at("Rpv2L"),      5., {5.5, 1.8}));
        add_result(SignalRegionData(_counters.at("Rpc2L0b"),    6., {4.7, 1.4}));
        add_result(SignalRegionData(_counters.at("Rpc2L1b"),   11., {6.5, 1.55}));
        add_result(SignalRegionData(_counters.at("Rpc2L2b"),   12., {7.8, 2.2}));
        add_result(SignalRegionData(_counters.at("Rpc3LSS1b"),  4., {3.5, 1.45}));

        #ifdef CHECK_CUTFLOW
          // Cutflow printout
          _cutflows["Rpc2L1b"].normalize(21.6 * 139., 0);
          cout << "\nCUTFLOWS:\n" << _cutflows << endl;
          cout << "\nSRCOUNTS:\n";
          // for (double x : _srnums) cout << x << "  ";
          for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
          cout << "\n" << endl;
        #endif
      }


    protected:

      void analysis_specific_reset() 
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MultiLEP_strong_139invfb)

  }
}
