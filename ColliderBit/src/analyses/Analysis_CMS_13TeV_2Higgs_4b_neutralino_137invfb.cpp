///
///  \author Yang Zhang
///  \date 2023 September
///  *********************************************

// Based on: 
// - https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-20-004

// Search for higgsinos decaying to two Higgs bosons and missing transverse momentum in proton-proton collisions at 13 TeV
// https://arxiv.org/abs/2201.04206
// CMS-SUS-20-004, CERN-EP-2021-214
// 
// Note:
// 1. Not ready.

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb : public Analysis {
    protected:
        // Counters for the number of accepted events for each signal region
        std::map<string, EventCounter> _counters = {
            // HH
            {"SR1", EventCounter("SR1")},
            {"SR2", EventCounter("SR2")},
            {"SR3", EventCounter("SR3")},
            {"SR4", EventCounter("SR4")},
            {"SR5", EventCounter("SR5")},
            {"SR6", EventCounter("SR6")},
            {"SR7", EventCounter("SR7")},
            {"SR8", EventCounter("SR8")},
            {"SR9", EventCounter("SR9")},
            {"SR10", EventCounter("SR10")},
            {"SR11", EventCounter("SR11")},
            {"SR12", EventCounter("SR12")},
            {"SR13", EventCounter("SR13")},
            {"SR14", EventCounter("SR14")},
            {"SR15", EventCounter("SR15")},
            {"SR16", EventCounter("SR16")},
            {"SR17", EventCounter("SR17")},
            {"SR18", EventCounter("SR18")},
            {"SR19", EventCounter("SR19")},
            {"SR20", EventCounter("SR20")},
            {"SR21", EventCounter("SR21")},
            
        };

        Cutflow _cutflow;


    public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb():
        _cutflow("CMS_13TeV_2Higgs_4b_neutralino_137invfb", {
          "Filters", 
          "N_vl=N_tk=0", 
          "4<=N_jet<=5",
          "N_b>=2"})
        {
            set_analysis_name("CMS_13TeV_2Higgs_4b_neutralino_137invfb");
            set_luminosity(137);
        }

        struct ptComparison {
            bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
        } comparePt;

        void run(const HEPUtils::Event* event) {
            _cutflow.fillinit();

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Electrons
            //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_035_ttbar.pdf
            const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
            const vector<double> bEl={0., 15., 20., 25., 30., 40., 50, DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
            const vector<double> cEl={
                          // pT:  (0,15), (15,20), (20,25), (25,30), (30,40), (40,50), (50,inf)
                                   0.0,   0.398,   0.501,   0.556,   0.619,   0.669,   0.720,// eta: (0, 0.8)
                                   0.0,   0.344,   0.433,   0.498,   0.579,   0.600,   0.671,// eta: (0.8, 1.4429)
                                   0.0,   0.201,   0.156,   0.206,   0.222,   0.255,   0.307,// eta: (1.442, 1.556)
                                   0.0,   0.210,   0.302,   0.338,   0.428,   0.484,   0.561,// eta: (1.556, 2)
                                   0.0,   0.162,   0.172,   0.250,   0.339,   0.396,   0.444,// eta: (2, 2.5)
                                   0.0,   0.0,     0.0,     0.0,     0.0,     0.0,     0.0// eta > 2.5
                                  };
            HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
            vector<const HEPUtils::Particle*> electrons;
            for (const HEPUtils::Particle* electron : event->electrons()) {
                bool isEl=has_tag(_eff2dEl, fabs(electron->eta()), electron->pT());
                if (electron->pT() > 15. && fabs(electron->eta()) < 2.5 && isEl)
                    electrons.push_back(electron);
            }

            // Muons
            //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_035_ttbar.pdf
            const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
            const vector<double> bMu={0., 10, 15., 20., 25., 30, 40, 50, DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
            const vector<double> cMu={
                          // pT:  (0,10), (10,15), (15,20), (20,25), (25,30), (30,40), (40,50), (50,inf)
                                   0.0,   0.564,   0.645,    0.739,  0.803,   0.860,   0.894,   0.907, // eta: (0, 0.9)
                                   0.0,   0.525,   0.616,    0.700,  0.773,   0.825,   0.891,   0.898, // eta: (0.9, 1.2)
                                   0.0,   0.514,   0.572,    0.697,  0.748,   0.789,   0.837,   0.870, // eta: (1.2, 2.1)
                                   0.0,   0.440,   0.575,    0.604,  0.663,   0.696,   0.784,   0.794,// eta: (2.1, 2.4)
                                   0.0,   0.0,     0.0,      0.0,    0.0,     0.0,     0.0,     0.0// eta > 2.4
                                  };
            HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
            vector<const HEPUtils::Particle*> muons;
            for (const HEPUtils::Particle* muon : event->muons()) {
                bool isMu=has_tag(_eff2dMu, fabs(muon->eta()), muon->pT());
                if (muon->pT() > 10.&& fabs(muon->eta()) < 2.4 && isMu)
                    muons.push_back(muon);
            }

            double HT = 0.;
            // Jets
            vector<const HEPUtils::Jet*> candJets;
            for (const HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 25. && fabs(jet->eta()) < 2.4){
                    HT += jet->pT();
                    candJets.push_back(jet);
                }
            }

            // Jets
            vector<const HEPUtils::Jet*> bJets;
            vector<const HEPUtils::Jet*> nonbJets;

            // Find b-jets
            // Copied from ATLAS_13TeV_3b_24invfb
            double btag = 0.85; double cmisstag = 1/12.; double misstag = 1./381.;
            for (const HEPUtils::Jet* jet : candJets) {
                // Tag
                if( jet->btag() && random_bool(btag) ) bJets.push_back(jet);
                // Misstag c-jet
                else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
                // Misstag light jet
                else if( random_bool(misstag) ) bJets.push_back(jet);
                // Non b-jet
                else if( jet->pT() > 40. ) nonbJets.push_back(jet);
            }

//            // Overlap removal
//            JetLeptonOverlapRemoval(candJets,electrons,0.2);
//            LeptonJetOverlapRemoval(electrons,candJets);
//            JetLeptonOverlapRemoval(candJets,muons,0.4);
//            LeptonJetOverlapRemoval(muons,candJets);

            size_t Nb=bJets.size();
            size_t Nj=nonbJets.size();

            // Leptons = electrons + muons
            vector<const HEPUtils::Particle*> leptons;
            leptons=electrons;
            leptons.insert(leptons.end(),muons.begin(),muons.end());
            sort(leptons.begin(),leptons.end(),comparePt);

            // At least two light leptons
            if (leptons.size()<2) return;

            // Find pair same sign (SS) leptons
            vector<size_t> SS_1,SS_2;
            for (size_t i=0; i<leptons.size(); ++i) {
                for (size_t j=i+1; j<leptons.size(); ++j) {
                    if (leptons[i]->pid()*leptons[j]->pid()>0){
                        SS_1.push_back(i);
                        SS_2.push_back(j);
                    }
                    // mll>12 for an opposite-sign same flavor pair lepton
                    if (leptons[i]->pid()+leptons[j]->pid()==0 and (leptons[i]->mom()+leptons[j]->mom()).m()<12) return;
                    // mll>8 GeV for any pair of leptons
                    if ((leptons[i]->mom()+leptons[j]->mom()).m()<8) return;
                }
            }
            _cutflow.fill(1);

            // One SS lepton pair
            if (SS_1.size()==0) return;
            _cutflow.fill(2);

            // At least two jets and MET>50
            if (Nj<2 or  met<50) return;
            _cutflow.fill(3);

            // Find the only SS lepton pair
            size_t SS1 = SS_1[0];
            size_t SS2 = SS_2[0];
            bool find_one_muon = false;
            for (size_t i=1; i<SS_1.size(); ++i) {
                // SS_1 and SS_2 are already order by lepton PT sum
                if (fabs(leptons[SS_1[i]]->pid())==13 and fabs(leptons[SS_1[i]]->pid())==13) {
                    // both of the leptons are muon
                    SS1 = SS_1[i];
                    SS2 = SS_2[i];
                    break;
                }
                if ( (not find_one_muon) and (fabs(leptons[SS_1[i]]->pid())==13 or fabs(leptons[SS_1[i]]->pid())==13)){
                    // one of the leptons is muon
                    SS1 = SS_1[i];
                    SS2 = SS_2[i];
                    find_one_muon = true;
                }
            }

            // M_T^{miss}
            double MTmin = sqrt(2.*leptons[SS1]->pT()*met*(1. - cos(leptons[SS1]->mom().deltaPhi(ptot))));
            if (MTmin>sqrt(2.*leptons[SS2]->pT()*met*(1. - cos(leptons[SS2]->mom().deltaPhi(ptot))))) {
                MTmin = sqrt(2.*leptons[SS2]->pT()*met*(1. - cos(leptons[SS2]->mom().deltaPhi(ptot))));
            }

            // HH: exactly 2 leptons, both with PT>25 GeV, and MET>50 GeV
            if (leptons.size()==2 and leptons[1]->pT() > 25.) {
                if (Nb==0 and HT>1000 and met>250 )
                    _counters.at("ISR1").add_event(event);
                if (Nb>=2 and HT>1100 ) 
                    _counters.at("ISR2").add_event(event);
                if (Nb==0 and met>500 ) 
                    _counters.at("ISR3").add_event(event);
                if (Nb>=2 and met>300 ) 
                    _counters.at("ISR4").add_event(event);
                if (Nb==0 and met>250 and MTmin>120 )
                    _counters.at("ISR5").add_event(event);  
                if (Nb>=2 and met>200 and MTmin>120 )
                    _counters.at("ISR6").add_event(event); 
                if (Nj>=8)
                    _counters.at("ISR7").add_event(event); 
                if (Nj>=6 and MTmin>120)
                    _counters.at("ISR8").add_event(event);
                if (Nb>=3 and HT>800)
                    _counters.at("ISR9").add_event(event); 
            }
            
            // LL: exactly 2 leptons, both with PT<25 GeV, and MET>50 GeV
            if (leptons.size()==2 and leptons[0]->pT() < 25. and leptons[1]->pT() < 25.) {
                if (HT>700)
                    _counters.at("ISR10").add_event(event);
                if (met>200)
                    _counters.at("ISR11").add_event(event);
                if (Nj>=6)
                    _counters.at("ISR12").add_event(event);
                if (Nb>=3)
                    _counters.at("ISR13").add_event(event);
            }
            // LM: exactly 2 leptons, both with PT>25 GeV, and MET<50 GeV
            if (leptons.size()==2 and leptons[0]->pT() > 25. and leptons[1]->pT() > 25.) {
                if (Nb==0 and HT>1200 and met<50 )
                    _counters.at("ISR14").add_event(event);
                if (Nb>=2 and HT>1000 and met<50 )
                    _counters.at("ISR15").add_event(event);
            }
            // ML: >=3 leptons, at least one with PT>25 GeV, and MET>50 GeV
            if (leptons.size()>=3 and leptons[0]->pT() > 25.) {
                if (Nb==0 and HT>1000 and met>300 )
                    _counters.at("ISR16").add_event(event);
                if (Nb>=2 and HT>1000)
                    _counters.at("ISR17").add_event(event);
            }

            return;
        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results() {
            add_result(SignalRegionData(_counters.at("ISR1"), 16, {12.7, 7.4}));
            add_result(SignalRegionData(_counters.at("ISR2"), 14, {11.0, 3.8}));
            add_result(SignalRegionData(_counters.at("ISR3"), 13, {10.4, 9.7}));
            add_result(SignalRegionData(_counters.at("ISR4"), 17, {11.4, 3.8}));
            add_result(SignalRegionData(_counters.at("ISR5"), 10, {6.6, 5.7}));
            add_result(SignalRegionData(_counters.at("ISR6"), 8, {6.3, 1.3}));
            add_result(SignalRegionData(_counters.at("ISR7"), 12, {7.0, 2.8}));
            add_result(SignalRegionData(_counters.at("ISR8"), 10, {6.2, 1.4}));
            add_result(SignalRegionData(_counters.at("ISR9"), 8, {7.8, 3.5}));
            add_result(SignalRegionData(_counters.at("ISR10"), 12, {10.4, 9.0}));
            add_result(SignalRegionData(_counters.at("ISR11"), 13, {12.1, 5.6}));
            add_result(SignalRegionData(_counters.at("ISR12"), 7, {7.1, 4.3}));
            add_result(SignalRegionData(_counters.at("ISR13"), 3, {1.61, 0.39}));
            add_result(SignalRegionData(_counters.at("ISR14"), 3, {3.6, 3.6}));
            add_result(SignalRegionData(_counters.at("ISR15"), 4, {2.34, 0.51}));
            add_result(SignalRegionData(_counters.at("ISR16"), 7, {5.6, 1.6}));
            add_result(SignalRegionData(_counters.at("ISR17"), 7, {5.7, 1.9}));

            // static const vector< vector<double> > BKGCOV = {
            //     {},
            //     {}
            // };

            // set_covariance(BKGCOV);

            return;
        }

    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2Higgs_4b_neutralino_137invfb)

  }
}
