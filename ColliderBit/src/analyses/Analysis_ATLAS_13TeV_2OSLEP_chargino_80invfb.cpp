///
///  \author Yang Zhang
///  \date 2019 Jan
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2018-042/
// Search for direct chargino pair production with W-boson mediated decays in events with two leptons and missing transverse momentum at √s=13 TeV with the ATLAS detector

// Note:
// 1. Not fully validated.
// 2. Use event-based MET significance instead of object-based significance

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

#define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - ATLAS_13TeV_2OSLEP_chargino_binned_80invfb
    // - ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb
    class Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SR-DF-0J-100",     0},
        {"SR-DF-0J-160",     0},
        {"SR-DF-0J-100-120", 0},
        {"SR-DF-0J-120-160", 0},
        {"SR-DF-1J-100",     0},
        {"SR-DF-1J-160",     0},
        {"SR-DF-1J-100-120", 0},
        {"SR-DF-1J-120-160", 0},
        {"SR-SF-0J-100",     0},
        {"SR-SF-0J-160",     0},
        {"SR-SF-0J-100-120", 0},
        {"SR-SF-0J-120-160", 0},
        {"SR-SF-1J-100",     0},
        {"SR-SF-1J-160",     0},
        {"SR-SF-1J-100-120", 0},
        {"SR-SF-1J-120-160", 0}
      };

      std::map<string,double> _numSR_bin = {
        {"SR-DF-0J-100-105", 0},
        {"SR-DF-0J-105-110", 0},
        {"SR-DF-0J-110-120", 0},
        {"SR-DF-0J-120-140", 0},
        {"SR-DF-0J-140-160", 0},
        {"SR-DF-0J-160-180", 0},
        {"SR-DF-0J-180-220", 0},
        {"SR-DF-0J-220", 0},
        {"SR-DF-1J-100-105", 0},
        {"SR-DF-1J-105-110", 0},
        {"SR-DF-1J-110-120", 0},
        {"SR-DF-1J-120-140", 0},
        {"SR-DF-1J-140-160", 0},
        {"SR-DF-1J-160-180", 0},
        {"SR-DF-1J-180-220", 0},
        {"SR-DF-1J-220", 0},
        {"SR-SF-0J-100-105", 0},
        {"SR-SF-0J-105-110", 0},
        {"SR-SF-0J-110-120", 0},
        {"SR-SF-0J-120-140", 0},
        {"SR-SF-0J-140-160", 0},
        {"SR-SF-0J-160-180", 0},
        {"SR-SF-0J-180-220", 0},
        {"SR-SF-0J-220", 0},
        {"SR-SF-1J-100-105", 0},
        {"SR-SF-1J-105-110", 0},
        {"SR-SF-1J-110-120", 0},
        {"SR-SF-1J-120-140", 0},
        {"SR-SF-1J-140-160", 0},
        {"SR-SF-1J-160-180", 0},
        {"SR-SF-1J-180-220", 0},
        {"SR-SF-1J-220", 0}
      };

      Cutflow _cutflow;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb():
      _cutflow("ATLAS 2-lep chargino-W 13 TeV", {"Two_OS_leptons", "mll_25", "b_jet_veto", "MET_100", "MET_significance_10", "n_j<=1", "m_ll_m_Z"})
      {

        set_analysis_name("ATLAS_13TeV_2OSLEP_chargino_80invfb");
        set_luminosity(80.5);

      }

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
      void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*> &jetvec, vector<HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<HEPUtils::Jet*> Survivors;

        for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
          bool overlap = false;
          HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            double dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(jetvec.at(itjet));
        }
        jetvec=Survivors;

        return;
      }

      void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::min(0.4, 0.04 + 10 / lepmom.pT());
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;


      void run(const HEPUtils::Event* event)
      {
        _cutflow.fillinit();

        // Baseline objects
        double met = event->met();

        // Electrons
        vector<HEPUtils::Particle*> electrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10.
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(electrons);

        // Muons
        vector<HEPUtils::Particle*> muons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10.
              && fabs(muon->eta()) < 2.5)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(muons);

        // Jets
        vector<HEPUtils::Jet*> candJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.5)
            candJets.push_back(jet);
        }

        // Scalar sum of the transverse momenta from all the reconstructed hard objects
        double HT = 0.0;
        for (HEPUtils::Jet* j : candJets) HT += j->pT();
        for (HEPUtils::Particle* e : electrons) HT += e->pT();
        for (HEPUtils::Particle* mu : muons) HT += mu->pT();

        // Overlap removal
        JetLeptonOverlapRemoval(candJets,electrons,0.2);
        LeptonJetOverlapRemoval(electrons,candJets);
        JetLeptonOverlapRemoval(candJets,muons,0.4);
        LeptonJetOverlapRemoval(muons,candJets);

   	    // Jets
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> nonbJets;

        // Find b-jets
        // Copied from ATLAS_13TeV_3b_24invfb
        double btag = 0.85; double cmisstag = 1/12.; double misstag = 1./381.;
        for (HEPUtils::Jet* jet : candJets) {
          // Tag
          if( jet->btag() && random_bool(btag) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }


        // Find signal leptons with pT > 20 GeV
        vector<HEPUtils::Particle*> signalElectrons;
        for (HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 25.) signalElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> signalMuons;
        for (HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 25.) signalMuons.push_back(muon);
        }

        // Signal leptons = electrons + muons
        vector<HEPUtils::Particle*> signalLeptons;
        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);


        // Tow exactly opposite-sign lepton
        if (signalLeptons.size() != 2) return;
        if (signalLeptons[0]->pid()*signalLeptons[1]->pid()>0) return;
        _cutflow.fill(1);


        // m_{ll} > 25 GeV
        double mll=(signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
        if (mll<25) return;
        _cutflow.fill(2);

        // b-jet veto
        if (bJets.size()>0) return;
        _cutflow.fill(3);

        // MET>110 GeV
        if (met<110) return;
        _cutflow.fill(4);

        // The missing transverse momentum significance >10
        // TODO Use event-based MET significance instead of object-based significance
        // https://cds.cern.ch/record/2630948/files/ATLAS-CONF-2018-038.pdf
        double met_sig=met/sqrt(HT);
        if (met_sig<10) return;
        _cutflow.fill(5);

        // n_non_b_tagged_jets <= 1
        if (nonbJets.size()>1) return;
        _cutflow.fill(6);

        // Same flavour
        bool flag_SF = signalLeptons[0]->pid() + signalLeptons[1]->pid() == 0;
        if (flag_SF) {
            if (fabs(mll-91.2)<30) return ;
        }
        _cutflow.fill(7);

        // Mt2
        double pLep1[3] = {signalLeptons[0]->mass(), signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py()};
        double pLep2[3] = {signalLeptons[1]->mass(), signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py()};
        double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
        mt2_bisect::mt2 mt2_calc;
        mt2_calc.set_momenta(pLep1,pLep2,pMiss);
        mt2_calc.set_mn(0.0);
        double mT2 = mt2_calc.get_mt2();

        if (flag_SF) {
            if (nonbJets.size()==0){
                if (mT2>100)             _numSR["SR-SF-0J-100"]++;
                if (mT2>160)             _numSR["SR-SF-0J-160"]++;
                if (mT2>100 and mT2<120) _numSR["SR-SF-0J-100-120"]++;
                if (mT2>120 and mT2<160) _numSR["SR-SF-0J-120-160"]++;
                // binned SRs
                if (mT2>100 and mT2<105) _numSR_bin["SR-SF-0J-100-105"]++;
                if (mT2>105 and mT2<110) _numSR_bin["SR-SF-0J-105-110"]++;
                if (mT2>110 and mT2<120) _numSR_bin["SR-SF-0J-110-120"]++;
                if (mT2>120 and mT2<140) _numSR_bin["SR-SF-0J-120-140"]++;
                if (mT2>140 and mT2<160) _numSR_bin["SR-SF-0J-140-160"]++;
                if (mT2>160 and mT2<180) _numSR_bin["SR-SF-0J-160-180"]++;
                if (mT2>180 and mT2<220) _numSR_bin["SR-SF-0J-180-220"]++;
                if (mT2>220            ) _numSR_bin["SR-SF-0J-220"]++;
            } else {
                if (mT2>100)             _numSR["SR-SF-1J-100"]++;
                if (mT2>160)             _numSR["SR-SF-1J-160"]++;
                if (mT2>100 and mT2<120) _numSR["SR-SF-1J-100-120"]++;
                if (mT2>120 and mT2<160) _numSR["SR-SF-1J-120-160"]++;
                // binned SRs
                if (mT2>100 and mT2<105) _numSR_bin["SR-SF-1J-100-105"]++;
                if (mT2>105 and mT2<110) _numSR_bin["SR-SF-1J-105-110"]++;
                if (mT2>110 and mT2<120) _numSR_bin["SR-SF-1J-110-120"]++;
                if (mT2>120 and mT2<140) _numSR_bin["SR-SF-1J-120-140"]++;
                if (mT2>140 and mT2<160) _numSR_bin["SR-SF-1J-140-160"]++;
                if (mT2>160 and mT2<180) _numSR_bin["SR-SF-1J-160-180"]++;
                if (mT2>180 and mT2<220) _numSR_bin["SR-SF-1J-180-220"]++;
                if (mT2>220            ) _numSR_bin["SR-SF-1J-220"]++;
            }
        } else {
            if (nonbJets.size()==0){
                if (mT2>100)             _numSR["SR-DF-0J-100"]++;
                if (mT2>160)             _numSR["SR-DF-0J-160"]++;
                if (mT2>100 and mT2<120) _numSR["SR-DF-0J-100-120"]++;
                if (mT2>120 and mT2<160) _numSR["SR-DF-0J-120-160"]++;
                // binned SRs
                if (mT2>100 and mT2<105) _numSR_bin["SR-DF-0J-100-105"]++;
                if (mT2>105 and mT2<110) _numSR_bin["SR-DF-0J-105-110"]++;
                if (mT2>110 and mT2<120) _numSR_bin["SR-DF-0J-110-120"]++;
                if (mT2>120 and mT2<140) _numSR_bin["SR-DF-0J-120-140"]++;
                if (mT2>140 and mT2<160) _numSR_bin["SR-DF-0J-140-160"]++;
                if (mT2>160 and mT2<180) _numSR_bin["SR-DF-0J-160-180"]++;
                if (mT2>180 and mT2<220) _numSR_bin["SR-DF-0J-180-220"]++;
                if (mT2>220            ) _numSR_bin["SR-DF-0J-220"]++;
            } else {
                if (mT2>100)             _numSR["SR-DF-1J-100"]++;
                if (mT2>160)             _numSR["SR-DF-1J-160"]++;
                if (mT2>100 and mT2<120) _numSR["SR-DF-1J-100-120"]++;
                if (mT2>120 and mT2<160) _numSR["SR-DF-1J-120-160"]++;
                // binned SRs
                if (mT2>100 and mT2<105) _numSR_bin["SR-DF-1J-100-105"]++;
                if (mT2>105 and mT2<110) _numSR_bin["SR-DF-1J-105-110"]++;
                if (mT2>110 and mT2<120) _numSR_bin["SR-DF-1J-110-120"]++;
                if (mT2>120 and mT2<140) _numSR_bin["SR-DF-1J-120-140"]++;
                if (mT2>140 and mT2<160) _numSR_bin["SR-DF-1J-140-160"]++;
                if (mT2>160 and mT2<180) _numSR_bin["SR-DF-1J-160-180"]++;
                if (mT2>180 and mT2<220) _numSR_bin["SR-DF-1J-180-220"]++;
                if (mT2>220            ) _numSR_bin["SR-DF-1J-220"]++;
            }

        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb*>(other);

        for (auto& el : _numSR)
        {
          el.second += specificOther->_numSR.at(el.first);
        }

        for (auto& el : _numSR_bin)
        {
          el.second += specificOther->_numSR_bin.at(el.first);
        }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        #ifdef CHECK_CUTFLOW
        cout << _cutflow << endl;
        for (auto& el : _numSR) {
            cout << el.first << "\t" << _numSR[el.first] << endl;
        }
        for (auto& el : _numSR_bin) {
            cout << el.first << "\t" << _numSR_bin[el.first] << endl;
        }
        #endif

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR-SF-0J-100"    , 131., {_numSR["SR-SF-0J-100"],     0.}, {119.67, 9.0}));
        add_result(SignalRegionData("SR-SF-0J-160"    ,  31., {_numSR["SR-SF-0J-160"],     0.}, {27.1  , 2.7}));
        add_result(SignalRegionData("SR-SF-0J-100-120",  65., {_numSR["SR-SF-0J-100-120"], 0.}, {50.9  , 5.7}));
        add_result(SignalRegionData("SR-SF-0J-120-160",  35., {_numSR["SR-SF-0J-120-160"], 0.}, {42.3  , 3.4}));

        add_result(SignalRegionData("SR-SF-1J-100"    , 114., {_numSR["SR-SF-1J-100"],     0.}, {114.  , 13.}));
        add_result(SignalRegionData("SR-SF-1J-160"    ,  23., {_numSR["SR-SF-1J-160"],     0.}, {29.   , 5. }));
        add_result(SignalRegionData("SR-SF-1J-100-120",  56., {_numSR["SR-SF-1J-100-120"], 0.}, {51.7  , 10.}));
        add_result(SignalRegionData("SR-SF-1J-120-160",  35., {_numSR["SR-SF-1J-120-160"], 0.}, {33.   , 4. }));

        add_result(SignalRegionData("SR-DF-0J-100"    ,  84., {_numSR["SR-DF-0J-100"],     0.}, {100.8, 11.9}));
        add_result(SignalRegionData("SR-DF-0J-160"    ,  15., {_numSR["SR-DF-0J-160"],     0.}, {16.1 , 2.0 }));
        add_result(SignalRegionData("SR-DF-0J-100-120",  49., {_numSR["SR-DF-0J-100-120"], 0.}, {53.4 , 9.}));
        add_result(SignalRegionData("SR-DF-0J-120-160",  20., {_numSR["SR-DF-0J-120-160"], 0.}, {31.5 , 3.5}));

        add_result(SignalRegionData("SR-DF-1J-100"    ,  73., {_numSR["SR-DF-1J-100"],     0.}, {83.5 , 14.6}));
        add_result(SignalRegionData("SR-DF-1J-160"    ,   9., {_numSR["SR-DF-1J-160"],     0.}, {12.2 , 2.5 }));
        add_result(SignalRegionData("SR-DF-1J-100-120",  39., {_numSR["SR-DF-1J-100-120"], 0.}, {50.6 , 10.7}));
        add_result(SignalRegionData("SR-DF-1J-120-160",  25., {_numSR["SR-DF-1J-120-160"], 0.}, {21.2 , 4.0 }));
      }


    protected:
      void analysis_specific_reset() {
        for (auto& el : _numSR) { el.second = 0.;}
        for (auto& el : _numSR_bin) { el.second = 0.;}
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2OSLEP_chargino_80invfb)


    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb : public Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb {

    public:
      Analysis_ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb() {
        set_analysis_name("ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR-SF-0J-100"    , 131., {_numSR["SR-SF-0J-100"],     0.}, {119.67, 9.0}));
        add_result(SignalRegionData("SR-SF-0J-160"    ,  31., {_numSR["SR-SF-0J-160"],     0.}, {27.1  , 2.7}));
        add_result(SignalRegionData("SR-SF-0J-100-120",  65., {_numSR["SR-SF-0J-100-120"], 0.}, {50.9  , 5.7}));
        add_result(SignalRegionData("SR-SF-0J-120-160",  35., {_numSR["SR-SF-0J-120-160"], 0.}, {42.3  , 3.4}));

        add_result(SignalRegionData("SR-SF-1J-100"    , 114., {_numSR["SR-SF-1J-100"],     0.}, {114.  , 13.}));
        add_result(SignalRegionData("SR-SF-1J-160"    ,  23., {_numSR["SR-SF-1J-160"],     0.}, {29.   , 5. }));
        add_result(SignalRegionData("SR-SF-1J-100-120",  56., {_numSR["SR-SF-1J-100-120"], 0.}, {51.7  , 10.}));
        add_result(SignalRegionData("SR-SF-1J-120-160",  35., {_numSR["SR-SF-1J-120-160"], 0.}, {33.   , 4. }));

        add_result(SignalRegionData("SR-DF-0J-100"    ,  84., {_numSR["SR-DF-0J-100"],     0.}, {100.8, 11.9}));
        add_result(SignalRegionData("SR-DF-0J-160"    ,  15., {_numSR["SR-DF-0J-160"],     0.}, {16.1 , 2.0 }));
        add_result(SignalRegionData("SR-DF-0J-100-120",  49., {_numSR["SR-DF-0J-100-120"], 0.}, {53.4 , 9.}));
        add_result(SignalRegionData("SR-DF-0J-120-160",  20., {_numSR["SR-DF-0J-120-160"], 0.}, {31.5 , 3.5}));

        add_result(SignalRegionData("SR-DF-1J-100"    ,  73., {_numSR["SR-DF-1J-100"],     0.}, {83.5 , 14.6}));
        add_result(SignalRegionData("SR-DF-1J-160"    ,   9., {_numSR["SR-DF-1J-160"],     0.}, {12.2 , 2.5 }));
        add_result(SignalRegionData("SR-DF-1J-100-120",  39., {_numSR["SR-DF-1J-100-120"], 0.}, {50.6 , 10.7}));
        add_result(SignalRegionData("SR-DF-1J-120-160",  25., {_numSR["SR-DF-1J-120-160"], 0.}, {21.2 , 4.0 }));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb)

    //
    // Derived analysis class for the 3Lep SRs
    //
    class Analysis_ATLAS_13TeV_2OSLEP_chargino_binned_80invfb : public Analysis_ATLAS_13TeV_2OSLEP_chargino_80invfb {

    public:
      Analysis_ATLAS_13TeV_2OSLEP_chargino_binned_80invfb() {
        set_analysis_name("ATLAS_13TeV_2OSLEP_chargino_binned_80invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR-DF-0J-100-105",	13	,	{_numSR_bin["SR-DF-0J-100-105"],	0.},	{	17.051834	,	3.918484	}));
		add_result(SignalRegionData("SR-DF-0J-105-110",	16	,	{_numSR_bin["SR-DF-0J-105-110"],	0.},	{	16.017853	,	3.304676	}));
		add_result(SignalRegionData("SR-DF-0J-110-120",	20	,	{_numSR_bin["SR-DF-0J-110-120"],	0.},	{	20.199902	,	3.164856	}));
		add_result(SignalRegionData("SR-DF-0J-120-140",	12	,	{_numSR_bin["SR-DF-0J-120-140"],	0.},	{	21.925301	,	2.729999	}));
		add_result(SignalRegionData("SR-DF-0J-140-160",	8	,	{_numSR_bin["SR-DF-0J-140-160"],	0.},	{	9.249123	,	1.258392	}));
		add_result(SignalRegionData("SR-DF-0J-160-180",	7	,	{_numSR_bin["SR-DF-0J-160-180"],	0.},	{	5.797642	,	0.837528	}));
		add_result(SignalRegionData("SR-DF-0J-180-220",	5	,	{_numSR_bin["SR-DF-0J-180-220"],	0.},	{	5.394958	,	0.882271	}));
		add_result(SignalRegionData("SR-DF-0J-220",	    3	,	{_numSR_bin["SR-DF-0J-220"],	    0.},	{	4.923061	,	0.615914	}));
		add_result(SignalRegionData("SR-DF-1J-100-105",	16	,	{_numSR_bin["SR-DF-1J-100-105"],	0.},	{	22.418163	,	5.116753	}));
		add_result(SignalRegionData("SR-DF-1J-105-110",	11	,	{_numSR_bin["SR-DF-1J-105-110"],	0.},	{	12.466408	,	3.139675	}));
		add_result(SignalRegionData("SR-DF-1J-110-120",	12	,	{_numSR_bin["SR-DF-1J-110-120"],	0.},	{	15.303375	,	4.375695	}));
		add_result(SignalRegionData("SR-DF-1J-120-140",	20	,	{_numSR_bin["SR-DF-1J-120-140"],	0.},	{	14.805614	,	3.148068	}));
		add_result(SignalRegionData("SR-DF-1J-140-160",	5	,	{_numSR_bin["SR-DF-1J-140-160"],	0.},	{	6.249268	,	1.218536	}));
		add_result(SignalRegionData("SR-DF-1J-160-180",	5	,	{_numSR_bin["SR-DF-1J-160-180"],	0.},	{	3.536739	,	1.02978	}));
		add_result(SignalRegionData("SR-DF-1J-180-220",	2	,	{_numSR_bin["SR-DF-1J-180-220"],	0.},	{	4.82729	,	0.920711	}));
		add_result(SignalRegionData("SR-DF-1J-220",	    2	,	{_numSR_bin["SR-DF-1J-220"],	    0.},	{	3.910061	,	0.905338	}));
		add_result(SignalRegionData("SR-SF-0J-100-105",	12	,	{_numSR_bin["SR-SF-0J-100-105"],	0.},	{	15.497025	,	2.616752	}));
		add_result(SignalRegionData("SR-SF-0J-105-110",	19	,	{_numSR_bin["SR-SF-0J-105-110"],	0.},	{	13.017998	,	2.942539	}));
		add_result(SignalRegionData("SR-SF-0J-110-120",	34	,	{_numSR_bin["SR-SF-0J-110-120"],	0.},	{	23.588459	,	2.989388	}));
		add_result(SignalRegionData("SR-SF-0J-120-140",	24	,	{_numSR_bin["SR-SF-0J-120-140"],	0.},	{	26.485558	,	2.523765	}));
		add_result(SignalRegionData("SR-SF-0J-140-160",	11	,	{_numSR_bin["SR-SF-0J-140-160"],	0.},	{	15.316658	,	1.483498	}));
		add_result(SignalRegionData("SR-SF-0J-160-180",	12	,	{_numSR_bin["SR-SF-0J-160-180"],	0.},	{	8.523453	,	1.050754	}));
		add_result(SignalRegionData("SR-SF-0J-180-220",	6	,	{_numSR_bin["SR-SF-0J-180-220"],	0.},	{	10.497726	,	1.696732	}));
		add_result(SignalRegionData("SR-SF-0J-220",	    13	,	{_numSR_bin["SR-SF-0J-220"],	    0.},	{	8.087914	,	1.003913	}));
		add_result(SignalRegionData("SR-SF-1J-100-105",	16	,	{_numSR_bin["SR-SF-1J-100-105"],	0.},	{	21.87426	,	5.927711	}));
		add_result(SignalRegionData("SR-SF-1J-105-110",	14	,	{_numSR_bin["SR-SF-1J-105-110"],	0.},	{	14.086235	,	3.386467	}));
		add_result(SignalRegionData("SR-SF-1J-110-120",	26	,	{_numSR_bin["SR-SF-1J-110-120"],	0.},	{	15.789253	,	3.269711	}));
		add_result(SignalRegionData("SR-SF-1J-120-140",	16	,	{_numSR_bin["SR-SF-1J-120-140"],	0.},	{	18.984154	,	2.601387	}));
		add_result(SignalRegionData("SR-SF-1J-140-160",	19	,	{_numSR_bin["SR-SF-1J-140-160"],	0.},	{	14.026108	,	2.25811	}));
		add_result(SignalRegionData("SR-SF-1J-160-180",	6	,	{_numSR_bin["SR-SF-1J-160-180"],	0.},	{	6.74284	,	2.173508	}));
		add_result(SignalRegionData("SR-SF-1J-180-220",	7	,	{_numSR_bin["SR-SF-1J-180-220"],	0.},	{	8.888386	,	2.181206	}));
		add_result(SignalRegionData("SR-SF-1J-220",	    10	,	{_numSR_bin["SR-SF-1J-220"],	    0.},	{	13.481506	,	2.867035	}));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2OSLEP_chargino_binned_80invfb)


  }
}
