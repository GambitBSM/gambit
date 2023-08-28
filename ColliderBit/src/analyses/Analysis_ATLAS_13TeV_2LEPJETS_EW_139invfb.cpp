///
///  \author Martin White
///  \date 2023 August
///
///  *********************************************

// Based on EW regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-05/
// Luminosity: 139 fb^-1
// Note that this uses the ATLAS object-based met significance
// Will approximate with event-based measure, but this will lead to discrepancies

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/METSignificance.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {

       // a/b is used to represent the first or second bin of the met significance
       {"SR_High_8_a", EventCounter("SR_High_8_a")},
       {"SR_High_8_b", EventCounter("SR_High_8_b")},
       {"SR_High_16_a",EventCounter("SR_High_16_a")},
       {"SR_High_16_b",EventCounter("SR_High_16_b")},
       {"SR_High_4",EventCounter("SR_High_4")},
       {"SR_llbb",EventCounter("SR_llbb")},
       {"SR_Int_a",EventCounter("SR_Int_a")},
       {"SR_Int_b",EventCounter("SR_Int_b")},
       {"SR_Low_a",EventCounter("SR_Low_a")},
       {"SR_Low_b",EventCounter("SR_Low_b")},
       {"SR_Low_2",EventCounter("SR_Low_2")},
       {"SR_OffShell_a",EventCounter("SR_OffShell_a")},
       {"SR_OffShell_b",EventCounter("SR_OffShell_b")}
      };

      vector<Cutflow> _cutflow;

      //vector<int> _test;
      //int _test2;

    private:

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb()
      {

        set_analysis_name("ATLAS_13TeV_2LEPJETS_EW_139invfb");
        set_luminosity(139);


        str cutflow_name = "ATLAS 2 opposite sign leptons at the Z peak 13 TeV";
        vector<str> SRZ1A = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 4", "MET > 250 GeV", "mT23l > 100 GeV"};
        vector<str> SRZ1B = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 5", "MET > 150 GeV", "pTll > 150 GeV", "Leading b-tagged jet pT > 100 GeV"};
        vector<str> SRZ2A = {"Trigger", "Third leading lepton pT < 20 GeV", "|mll - mZ| < 15 GeV", "Leading jet pT > 150 GeV", "MET > 200 GeV", "pTll < 50 GeV"};
        vector<str> SRZ2B = {"Trigger", "Third leading lepton pT < 60 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "MET > 350 GeV", "pTll > 150 GeV"};
        // vector<str> SRh1A = {"Trigger", "nb-tagged (pT > 30 GeV) >= 4", "nh-cand >= 1", "mT > 150 GeV", "njets (pT > 60 GeV) >= 4", "S > 12"};
        // vector<str> SRh1B = {"Trigger", "nb-tagged (pT > 30 GeV) >= 4", "nh-cand >= 1", "mT > 150 GeV", "njets (pT > 60 GeV) >= 6", "S > 7"};
        _cutflow = { Cutflow(cutflow_name, SRZ1A),
                     Cutflow(cutflow_name, SRZ1B),
                     Cutflow(cutflow_name, SRZ2A),
                     Cutflow(cutflow_name, SRZ2B),
                     // Cutflow(cutflow_name, SRh1A),
                     // Cutflow(cutflow_name, SRh1B)
        };
        //_test = {0,0,0,0,0};
        //_test2 = 0;

      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineLeptons;
        vector<const HEPUtils::Particle*> baselinePhotons;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineBJets;
        vector<const HEPUtils::Jet*> baselineNonBJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        //if(event->electrons().size() + event->muons().size() >= 3)
        //  _test2++;

        // Initialize cutflow
        for(size_t i=0; i<_cutflow.size(); i++)
        {
          _cutflow[i].fillinit();
        }

        // Baseline electrons have pT > 4.5 GeV, satisfy the "loose" criteria, and have |eta|<2.47.
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // Loose electron ID selection
        ATLAS::applyElectronIDEfficiency2019(baselineElectrons, "Loose");

        // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 3. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        // Missing: "Medium" muon ID criteria
        ATLAS::applyMuonEffR2(baselineMuons);

        // Missing: transverse and longitudinal impact parameter cuts


        // Only jet candidates with pT > 20 GeV and |η| < 2.8 are considered in the analysis
        // Jets with pT < 120 GeV and |η| < 2.8 have an efficiency of 90%
        // Missing:  cut based on detector noise and non-collision backgrounds

        // Baseline photons selection (used later in met significance)
        // pT > 25 GeV, and abseta < 2.37, and doesn't lie in 1.37 < abseta < 1.52
        // Missing: "tight" photon ID criteria
        for (const HEPUtils::Particle* photon : event->photons())
        {
          if ((photon->pT() > 25.) && (photon->abseta() < 2.37))
          {
            if (photon->abseta() < 1.37 || photon->abseta() > 1.52) baselinePhotons.push_back(photon);
          }
        }

        double jet_eff = 0.9;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
            if( (jet->pT() >= 120. || jet->abseta() >= 2.5) || random_bool(jet_eff) ) baselineJets.push_back(jet);
          }
        }

        // Overlap removal
        // 1) Remove muons with 0.01 of an electron, mimics shared tracks
        removeOverlap(baselineMuons, baselineElectrons, 0.01);
        // 2) Remove jets within DeltaR = 0.2 of electron
        removeOverlap(baselineJets, baselineElectrons, 0.2);
        // 3) If any lepton has Delta R < min(0.4, 0.04 + 10/pT(l)) with a jet, remove the lepton.
        auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
        removeOverlap(baselineElectrons, baselineJets, lambda);
        // 4) Remove muons within 0.2 of jets (incorporates shared track approximation) // TODO: I think this is the wrong way around. I think the jet should be removed. Check This
        //removeOverlap(baselineMuons, baselineJets, 0.2); // TODO: Old version, remove after checking
        removeOverlap(baselineJets, baselineMuons, 0.2);
        // 5) Remove muons subject to pT-dependent deltaR requirement
        removeOverlap(baselineMuons, baselineJets, lambda);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalLeptons;

        // Signal electrons must satisfy the “medium” identification requirement as defined in arXiv: 1902.04655 [hep-ex]
        ATLAS::applyElectronIDEfficiency2019(signalElectrons, "Medium");
        // Signal electrons must have pT > 25 GeV
        for (const HEPUtils::Particle* signalElectron : baselineElectrons)
        {
          if (signalElectron->pT() > 25.) signalElectrons.push_back(signalElectron);
        }

        // Signal muons must have pT > 25 GeV.
        for (const HEPUtils::Particle* signalMuon : baselineMuons)
        {
          if (signalMuon->pT() > 25. && signalMuon->abseta() < 2.6) signalMuons.push_back(signalMuon);
        }

        // Signal jets must have pT > 30 GeV
        for (const HEPUtils::Jet* signalJet : baselineJets)
        {
          if (signalJet->pT() > 30.) signalJets.push_back(signalJet);
        }

        // Find b-jets
        double btag = 0.77; double cmisstag = 1/16.; double misstag = 1./113.;
        for (const HEPUtils::Jet* jet : signalJets)
        {
          // Tag
          if( jet->btag() && random_bool(btag) ) signalBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) signalBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) signalBJets.push_back(jet);
          // Non b-jet
          else signalNonBJets.push_back(jet);
        }

        // Fill signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Fill baseline leptons
        baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Start of analysis code based on ATLAS public code snippet
        size_t n_baseline_leptons = baselineLeptons.size();
        size_t n_leptons = signalLeptons.size();
        size_t n_jets = signalJets.size();
        size_t nbjets = signalBJets.size();

        /* Preselection */
        // Require:
        // exactly two leptons (> 25 GeV)
        // both leptons of the Same Flavour (SF)
        // both leptons of Opposite Sign (OS) charge *** except VR_SS
        // lepton pair mass in (12, 111)
        // at least one jet (> 30 GeV)
        // missing energy: met > 100 GeV, met significance > 6 TODO: I can't see in the text, where the met > 100 GeV requirement comes from (I can see it in cutflows).


        // exactly two leptons (> 25 GeV)
        bool cut_2lep=true;
        if (n_leptons != 2 || n_baseline_leptons != 2) cut_2lep=false;

        // both leptons of the Same Flavour (SF)
        // since we have exactly two leptons,
        // 0 electron <=> 2 muon => SF
        // 1 electron <=> 1 muon => DF
        // 2 electron <=> 0 muon => SF
        bool cut_SF=true;
        if (signalElectrons.size() == 1) cut_SF=false;

        // lepton pair mass in (12, 111)
        bool cut_mll = true;
        HEPUtils::P4 dilepton = signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom();
        double mll = dilepton.m();
        if (!(12 < mll && mll < 111)) cut_mll = false;

        // at least one jet (> 30 GeV)
        bool cut_1jet = true;
        if (n_jets < 1) cut_1jet = false;

        // Approximate the significance using HT
        // Best we can do, but still rubbish compared to ATLAS definition :-(
        double HT = 0.0;
        for (const HEPUtils::Jet* j : baselineJets) HT += j->pT();
        for (const HEPUtils::Particle* p : event->photons()) HT += p->pT();
        for (const HEPUtils::Particle* e : baselineElectrons) HT += e->pT();
        for (const HEPUtils::Particle* mu : baselineMuons) HT += mu->pT();

        // missing energy: met > 100 GeV, met significance > 6
        if (!(met > 100)) return; // TODO: Still trying to understand why. Could it just be for testing
        bool cut_metsig = true;
        //double metsig = met/sqrt(HT); // TODO: The approximate method
        double metsig = 0;//calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons, baselineJets, event->taus(), metVec); // TODO: Using ATLAS' Simple Analysis Framework
        if (!(metsig > 6)) cut_metsig=false;

        /* More event variables */
        double dphiPllMet = fabs(dilepton.deltaPhi(metVec));
        double dphiJ1met = fabs(signalJets.at(0)->mom().deltaPhi(metVec));

        double mjj = 0.;
        double Rjj = 0.;
        if (n_jets >= 2)
        {
          HEPUtils::P4 dijets = signalJets.at(0)->mom() + signalJets.at(1)->mom();
          mjj = dijets.m();
          Rjj = fabs(signalJets.at(0)->mom().deltaR_eta(signalJets.at(1)->mom()));
        }

        double mbb = 0.;
        if (nbjets >= 2)
        {
          HEPUtils::P4 dibjets = signalBJets.at(0)->mom() + signalBJets.at(1)->mom();
          mbb = dibjets.m();
        }

        double jetpt1 = signalJets.at(0)->mom().pT();
        double jetm1 = signalJets.at(0)->mom().m();

        double Rll = fabs(signalLeptons.at(0)->mom().deltaR_eta(signalLeptons.at(1)->mom()));

        double mt2 = 0;
        if(cut_2lep)
        {
          double pLep1[3] = {signalLeptons.at(0)->mass(), signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py()};
          double pLep2[3] = {signalLeptons.at(1)->mass(), signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py()};
          double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };

          mt2_bisect::mt2 mt2_calc;
          double mn = 0;
          mt2_calc.set_momenta(pLep1, pLep2, pMiss);
          mt2_calc.set_mn(mn);
          mt2 = mt2_calc.get_mt2();
        }

        // both leptons of Opposite Sign (OS) charge
        bool cut_OS = true;
        if (signalLeptons.at(0)->pid() == signalLeptons.at(1)->pid()) cut_OS = false;

        bool EWK_2Ljets_presel = false;

        if(cut_2lep &&
           cut_SF &&
           cut_mll &&
           cut_1jet &&
           cut_metsig &&
           cut_OS) EWK_2Ljets_presel=true;

        /* Signal Regions */

        // SR High presel
        if (71 < mll && mll < 111 && mt2 > 80)
        {

          // SR_High_8_a
          if (n_jets >= 2
              && 18 < metsig && metsig < 21
              && Rjj < 0.8
              && 60 < mjj && mjj < 110
              && nbjets <= 1)
          {
            _counters.at("SR_High_8_a").add_event(event);
          }

          // SR_High_8_b
          if (n_jets >= 2
              && metsig > 21
              && Rjj < 0.8
              && 60 < mjj && mjj < 110
              && nbjets <= 1)
          {
            _counters.at("SR_High_8_b").add_event(event);
          }

          // SR_High_16_a
          if (n_jets >= 2
              && 18 < metsig && metsig < 21
              && 0.8 < Rjj && Rjj < 1.6
              && 60 < mjj && mjj < 110
              && nbjets <= 1)
          {
            _counters.at("SR_High_16_a").add_event(event);
          }

          // SR_High_16_b
          if (n_jets >= 2
              && metsig > 21
              && 0.8 < Rjj && Rjj < 1.6
              && 60 < mjj && mjj < 110
              && nbjets <= 1)
          {
            _counters.at("SR_High_16_b").add_event(event);
          }

          // SR_High_4
          if (n_jets == 1
              && metsig > 12
              && 60 < jetm1 && jetm1 < 110
             && nbjets <= 1)
          {
            _counters.at("SR_High_4").add_event(event);
          }

          // SR_llbb
          if (n_jets >= 2
              && metsig > 18
              && 60 < mbb && mbb < 150
              && nbjets >= 2)
          {
            _counters.at("SR_llbb").add_event(event);
          }

        } // End SR High


        // SR Int presel
        if (81 < mll && mll < 101
            && mt2 > 80
            && n_jets >= 2
            && nbjets == 0
            && 60 < mjj && mjj < 110
            && jetpt1 > 60)
        {

          // SR_Int_a
          if (12 < metsig && metsig < 15)
          {
            _counters.at("SR_Int_a").add_event(event);
          }

          // SR_Int_b
          if (15 < metsig && metsig < 18)
          {
            _counters.at("SR_Int_b").add_event(event);
          }

        } // End SR Int


        // SR Low presel
        if (81 < mll && mll < 101
            && n_jets == 2
            && nbjets == 0
            && 60 < mjj && mjj < 110)
        {

          // SR_Low_a
          if (mt2 > 80
              && 6 < metsig && metsig < 9
              && Rll < 1)
          {
            _counters.at("SR_Low_a").add_event(event);
          }

          // SR_Low_b
          if (mt2 > 80
              && 9 < metsig && metsig < 12
              && Rll < 1)
          {
            _counters.at("SR_Low_b").add_event(event);
          }

          // SR_Low_2
          if (mt2 < 80
              && 6 < metsig && metsig < 9
              && Rll < 1.6
              && dphiPllMet < 0.6)
          {
            _counters.at("SR_Low_2").add_event(event);
          }

        } // End SR Low


        // SR Off Shell
        if (metsig > 9
            && mt2 > 100
            && n_jets >= 2
            && nbjets == 0
            && jetpt1 > 100
            && dphiJ1met > 2)
        {

          // SR_OffShell_a
          if (12 < mll && mll < 40)
          {
            _counters.at("SR_OffShell_a").add_event(event);
          }

          // SR_OffShell_b
          if (40 < mll && mll < 71)
          {
            _counters.at("SR_OffShell_b").add_event(event);
          }

        } // End SR Off Shell

      } // End run function

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb*>(other);

        for (auto& pair : _counters)
        {
          pair.second += specificOther->_counters.at(pair.first);
        }
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        add_result(SignalRegionData(_counters.at("SR_High_8_a"), 0., {2.00, 0.23}));
        add_result(SignalRegionData(_counters.at("SR_High_8_b"), 0., {2.00, 0.33}));
        add_result(SignalRegionData(_counters.at("SR_High_16_a"), 4., {3.9, 0.7}));
        add_result(SignalRegionData(_counters.at("SR_High_16_b"), 3., {3.4, 0.9}));
        add_result(SignalRegionData(_counters.at("SR_High_4"), 1., {0.85, 0.34}));
        add_result(SignalRegionData(_counters.at("SR_llbb"), 0., {0.58, 0.20}));
        add_result(SignalRegionData(_counters.at("SR_Int_a"), 24., {22.8, 3.5 }));
        add_result(SignalRegionData(_counters.at("SR_Int_b"), 14., {10.1, 1.0}));
        add_result(SignalRegionData(_counters.at("SR_Low_a"), 10., {12.8, 3.4}));
        add_result(SignalRegionData(_counters.at("SR_Low_b"), 8., {10.5, 2.5}));
        add_result(SignalRegionData(_counters.at("SR_Low_2"), 8., {9, 4}));
        add_result(SignalRegionData(_counters.at("SR_OffShell_a"), 6., {9.2, 1.7}));
        add_result(SignalRegionData(_counters.at("SR_OffShell_b"), 15., {12.5, 1.9}));

        #ifdef CHECK_CUTFLOW
          cout << _cutflow << endl;
          //cout << "n signal leptons before = " << _test2 << endl;
          //cout << "n signal leptons = " << _test[0] << endl;
          //cout << "n baseline leptons = " << _test[1] << endl;
        #endif


      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters)
        {
          pair.second.reset();
        }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPJETS_EW_139invfb)


  }
}
