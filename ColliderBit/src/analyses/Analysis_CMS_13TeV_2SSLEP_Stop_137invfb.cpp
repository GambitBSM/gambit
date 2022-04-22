///
///  \author Yang Zhang
///  \date 2019 June
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-19-008/index.html
// Search for physics beyond the standard model in events with two same-sign leptons or at least three leptons and jets in proton-proton collisions at 13 TeV

// Note:
// 1. Not fully validated.

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

    class Analysis_CMS_13TeV_2SSLEP_Stop_137invfb : public Analysis {
    protected:
        // Counters for the number of accepted events for each signal region
        std::map<string, EventCounter> _counters = {
            // HH
            {"SRHH-0", EventCounter("SRHH-0")},
            {"SRHH-1", EventCounter("SRHH-1")},
            {"SRHH-2", EventCounter("SRHH-2")},
            {"SRHH-3", EventCounter("SRHH-3")},
            {"SRHH-4", EventCounter("SRHH-4")},
            {"SRHH-5", EventCounter("SRHH-5")},
            {"SRHH-6", EventCounter("SRHH-6")},
            {"SRHH-7", EventCounter("SRHH-7")},
            {"SRHH-8", EventCounter("SRHH-8")},
            {"SRHH-9", EventCounter("SRHH-9")},
            {"SRHH-10", EventCounter("SRHH-10")},
            {"SRHH-11", EventCounter("SRHH-11")},
            {"SRHH-12", EventCounter("SRHH-12")},
            {"SRHH-13", EventCounter("SRHH-13")},
            {"SRHH-14", EventCounter("SRHH-14")},
            {"SRHH-15", EventCounter("SRHH-15")},
            {"SRHH-16", EventCounter("SRHH-16")},
            {"SRHH-17", EventCounter("SRHH-17")},
            {"SRHH-18", EventCounter("SRHH-18")},
            {"SRHH-19", EventCounter("SRHH-19")},
            {"SRHH-20", EventCounter("SRHH-20")},
            {"SRHH-21", EventCounter("SRHH-21")},
            {"SRHH-22", EventCounter("SRHH-22")},
            {"SRHH-23", EventCounter("SRHH-23")},
            {"SRHH-24", EventCounter("SRHH-24")},
            {"SRHH-25", EventCounter("SRHH-25")},
            {"SRHH-26", EventCounter("SRHH-26")},
            {"SRHH-27", EventCounter("SRHH-27")},
            {"SRHH-28", EventCounter("SRHH-28")},
            {"SRHH-29", EventCounter("SRHH-29")},
            {"SRHH-30", EventCounter("SRHH-30")},
            {"SRHH-31", EventCounter("SRHH-31")},
            {"SRHH-32", EventCounter("SRHH-32")},
            {"SRHH-33", EventCounter("SRHH-33")},
            {"SRHH-34", EventCounter("SRHH-34")},
            {"SRHH-35", EventCounter("SRHH-35")},
            {"SRHH-36", EventCounter("SRHH-36")},
            {"SRHH-37", EventCounter("SRHH-37")},
            {"SRHH-38", EventCounter("SRHH-38")},
            {"SRHH-39", EventCounter("SRHH-39")},
            {"SRHH-40", EventCounter("SRHH-40")},
            {"SRHH-41", EventCounter("SRHH-41")},
            {"SRHH-42", EventCounter("SRHH-42")},
            {"SRHH-43", EventCounter("SRHH-43")},
            {"SRHH-44", EventCounter("SRHH-44")},
            {"SRHH-45", EventCounter("SRHH-45")},
            {"SRHH-46", EventCounter("SRHH-46")},
            {"SRHH-47", EventCounter("SRHH-47")},
            {"SRHH-48", EventCounter("SRHH-48")},
            {"SRHH-49", EventCounter("SRHH-49")},
            {"SRHH-50", EventCounter("SRHH-50")},
            {"SRHH-51", EventCounter("SRHH-51")},
            {"SRHH-52", EventCounter("SRHH-52")},
            {"SRHH-53", EventCounter("SRHH-53")},
            {"SRHH-54", EventCounter("SRHH-54")},
            {"SRHH-55", EventCounter("SRHH-55")},
            {"SRHH-56", EventCounter("SRHH-56")},
            {"SRHH-57", EventCounter("SRHH-57")},
            {"SRHH-58", EventCounter("SRHH-58")},
            {"SRHH-59", EventCounter("SRHH-59")},
            {"SRHH-60", EventCounter("SRHH-60")},
            {"SRHH-61", EventCounter("SRHH-61")},
            // HL
            {"SRHL-0", EventCounter("SRHL-0")},
            {"SRHL-1", EventCounter("SRHL-1")},
            {"SRHL-2", EventCounter("SRHL-2")},
            {"SRHL-3", EventCounter("SRHL-3")},
            {"SRHL-4", EventCounter("SRHL-4")},
            {"SRHL-5", EventCounter("SRHL-5")},
            {"SRHL-6", EventCounter("SRHL-6")},
            {"SRHL-7", EventCounter("SRHL-7")},
            {"SRHL-8", EventCounter("SRHL-8")},
            {"SRHL-9", EventCounter("SRHL-9")},
            {"SRHL-10", EventCounter("SRHL-10")},
            {"SRHL-11", EventCounter("SRHL-11")},
            {"SRHL-12", EventCounter("SRHL-12")},
            {"SRHL-13", EventCounter("SRHL-13")},
            {"SRHL-14", EventCounter("SRHL-14")},
            {"SRHL-15", EventCounter("SRHL-15")},
            {"SRHL-16", EventCounter("SRHL-16")},
            {"SRHL-17", EventCounter("SRHL-17")},
            {"SRHL-18", EventCounter("SRHL-18")},
            {"SRHL-19", EventCounter("SRHL-19")},
            {"SRHL-20", EventCounter("SRHL-20")},
            {"SRHL-21", EventCounter("SRHL-21")},
            {"SRHL-22", EventCounter("SRHL-22")},
            {"SRHL-23", EventCounter("SRHL-23")},
            {"SRHL-24", EventCounter("SRHL-24")},
            {"SRHL-25", EventCounter("SRHL-25")},
            {"SRHL-26", EventCounter("SRHL-26")},
            {"SRHL-27", EventCounter("SRHL-27")},
            {"SRHL-28", EventCounter("SRHL-28")},
            {"SRHL-29", EventCounter("SRHL-29")},
            {"SRHL-30", EventCounter("SRHL-30")},
            {"SRHL-31", EventCounter("SRHL-31")},
            {"SRHL-32", EventCounter("SRHL-32")},
            {"SRHL-33", EventCounter("SRHL-33")},
            {"SRHL-34", EventCounter("SRHL-34")},
            {"SRHL-35", EventCounter("SRHL-35")},
            {"SRHL-36", EventCounter("SRHL-36")},
            {"SRHL-37", EventCounter("SRHL-37")},
            {"SRHL-38", EventCounter("SRHL-38")},
            {"SRHL-39", EventCounter("SRHL-39")},
            {"SRHL-40", EventCounter("SRHL-40")},
            {"SRHL-41", EventCounter("SRHL-41")},
            {"SRHL-42", EventCounter("SRHL-42")},
            // LL
            {"SRLL-0", EventCounter("SRLL-0")},
            {"SRLL-1", EventCounter("SRLL-1")},
            {"SRLL-2", EventCounter("SRLL-2")},
            {"SRLL-3", EventCounter("SRLL-3")},
            {"SRLL-4", EventCounter("SRLL-4")},
            {"SRLL-5", EventCounter("SRLL-5")},
            {"SRLL-6", EventCounter("SRLL-6")},
            {"SRLL-7", EventCounter("SRLL-7")},
            // LM
            {"SRLM-0", EventCounter("SRLM-0")},
            {"SRLM-1", EventCounter("SRLM-1")},
            {"SRLM-2", EventCounter("SRLM-2")},
            {"SRLM-3", EventCounter("SRLM-3")},
            {"SRLM-4", EventCounter("SRLM-4")},
            {"SRLM-5", EventCounter("SRLM-5")},
            {"SRLM-6", EventCounter("SRLM-6")},
            {"SRLM-7", EventCounter("SRLM-7")},
            {"SRLM-8", EventCounter("SRLM-8")},
            {"SRLM-9", EventCounter("SRLM-9")},
            {"SRLM-10", EventCounter("SRLM-10")},
            // ML
            {"SRML-0", EventCounter("SRML-0")},
            {"SRML-1", EventCounter("SRML-1")},
            {"SRML-2", EventCounter("SRML-2")},
            {"SRML-3", EventCounter("SRML-3")},
            {"SRML-4", EventCounter("SRML-4")},
            {"SRML-5", EventCounter("SRML-5")},
            {"SRML-6", EventCounter("SRML-6")},
            {"SRML-7", EventCounter("SRML-7")},
            {"SRML-8", EventCounter("SRML-8")},
            {"SRML-9", EventCounter("SRML-9")},
            {"SRML-10", EventCounter("SRML-10")},
            {"SRML-11", EventCounter("SRML-11")},
            {"SRML-12", EventCounter("SRML-12")},
            {"SRML-13", EventCounter("SRML-13")},
            {"SRML-14", EventCounter("SRML-14")},
            {"SRML-15", EventCounter("SRML-15")},
            {"SRML-16", EventCounter("SRML-16")},
            {"SRML-17", EventCounter("SRML-17")},
            {"SRML-18", EventCounter("SRML-18")},
            {"SRML-19", EventCounter("SRML-19")},
            {"SRML-20", EventCounter("SRML-20")},
            {"SRML-21", EventCounter("SRML-21")},
            {"SRML-22", EventCounter("SRML-22")},
            {"SRML-23", EventCounter("SRML-23")},
            {"SRML-24", EventCounter("SRML-24")},
            {"SRML-25", EventCounter("SRML-25")},
            {"SRML-26", EventCounter("SRML-26")},
            {"SRML-27", EventCounter("SRML-27")},
            {"SRML-28", EventCounter("SRML-28")},
            {"SRML-29", EventCounter("SRML-29")},
            {"SRML-30", EventCounter("SRML-30")},
            {"SRML-31", EventCounter("SRML-31")},
            {"SRML-32", EventCounter("SRML-32")},
            {"SRML-33", EventCounter("SRML-33")},
            {"SRML-34", EventCounter("SRML-34")},
            {"SRML-35", EventCounter("SRML-35")},
            {"SRML-36", EventCounter("SRML-36")},
            {"SRML-37", EventCounter("SRML-37")},
            {"SRML-38", EventCounter("SRML-38")},
            {"SRML-39", EventCounter("SRML-39")},
            {"SRML-40", EventCounter("SRML-40")},
            {"SRML-41", EventCounter("SRML-41")},
            {"SRML-42", EventCounter("SRML-42")},
            {"SRML-43", EventCounter("SRML-43")},
        };

        Cutflow _cutflow;


    public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_CMS_13TeV_2SSLEP_Stop_137invfb():
        _cutflow("CMS_13TeV_2SSLEP_Stop_137invfb", {"Trigger_and_2leptons", "At_least_one_SS_lepton_pair", "Baseline"})
        {
            set_analysis_name("CMS_13TeV_2SSLEP_Stop_137invfb");
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
            if (nonbJets.size()<2 or  met<50) return;
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
            double MTmiss = sqrt(2.*leptons[SS1]->pT()*met*(1. - cos(leptons[SS1]->mom().deltaPhi(ptot))));
            if (MTmiss>sqrt(2.*leptons[SS2]->pT()*met*(1. - cos(leptons[SS2]->mom().deltaPhi(ptot))))) {
                MTmiss = sqrt(2.*leptons[SS2]->pT()*met*(1. - cos(leptons[SS2]->mom().deltaPhi(ptot))));
            }

            bool pp = leptons[SS1]->pid()>0;
            bool met_50_200 = met>50 and met<200;
            bool met_200_300 = met>200 and met<300;
            bool met_300_500 = met>300 and met<500;
            bool met_500 = met>500;
            bool MTmiss_l_120 = MTmiss<120;
            bool MTmiss_g_120 = MTmiss>120;
            bool Nj_2_4 = Nj>=2 and Nj<=4;
            bool Nj_5 = Nj>=5;
            bool HT_300 = HT<300;
            bool HT_300_1125 = HT>300 and HT<1125;
            bool HT_1125_1300 = HT>1125 and HT<1300;
            bool HT_1300_1600 = HT>1300 and HT<1600;
            bool HT_1300 = HT>1300;
            bool HT_1600 = HT>1600;
            bool SSHH_combine = ((MTmiss_l_120&&((met_50_200&&Nj_5)||met_200_300)) or (MTmiss_g_120&&met<300) )&&HT_300 ;

            // SSHH: exactly 2 leptons, both with PT>25 GeV, and MET>50 GeV
            if (leptons.size()==2 and leptons[1]->pT() > 25.) {
                if (Nb==0) {
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300)               _counters.at("SRHH-0").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300_1125)          _counters.at("SRHH-1").add_event(event);
                    if (SSHH_combine)                                                     _counters.at("SRHH-2").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_5   and HT_300_1125)          _counters.at("SRHH-3").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and pp)   _counters.at("SRHH-4").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and !pp)  _counters.at("SRHH-5").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_5   and HT_300_1125)          _counters.at("SRHH-6").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and pp)   _counters.at("SRHH-7").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and !pp)  _counters.at("SRHH-8").add_event(event);
                    if (MTmiss_g_120 and((met_50_200&&Nj_5)||met_200_300)and HT_300_1125) _counters.at("SRHH-9").add_event(event);
                } else if (Nb==1) {
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHH-10").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHH-11").add_event(event);
                    if (SSHH_combine and pp)                                             _counters.at("SRHH-12").add_event(event);
                    if (SSHH_combine and !pp)                                            _counters.at("SRHH-13").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_5   and HT_300_1125 and pp)  _counters.at("SRHH-14").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_5   and HT_300_1125 and !pp) _counters.at("SRHH-15").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-16").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-17").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_5   and HT_300_1125)         _counters.at("SRHH-18").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-19").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-20").add_event(event);
                    if (MTmiss_g_120 and((met_50_200&&Nj_5)||met_200_300)and HT_300_1125) _counters.at("SRHH-21").add_event(event);
                } else if (Nb==2){
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHH-22").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHH-23").add_event(event);
                    if (SSHH_combine and pp)                                             _counters.at("SRHH-24").add_event(event);
                    if (SSHH_combine and !pp)                                            _counters.at("SRHH-25").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_5   and HT_300_1125 and pp)  _counters.at("SRHH-26").add_event(event);
                    if (MTmiss_l_120 and met_50_200  and Nj_5   and HT_300_1125 and !pp) _counters.at("SRHH-27").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-28").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-29").add_event(event);
                    if (MTmiss_l_120 and met_200_300 and Nj_5   and HT_300_1125)         _counters.at("SRHH-30").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-31").add_event(event);
                    if (MTmiss_g_120 and met_50_200  and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-32").add_event(event);
                    if (MTmiss_g_120 and((met_50_200&&Nj_5)||met_200_300)and HT_300_1125) _counters.at("SRHH-33").add_event(event);
                } else if (Nb>=3){
                    if (MTmiss_l_120 and met<300                and HT_300 and pp)       _counters.at("SRHH-34").add_event(event);
                    if (MTmiss_l_120 and met<300                and HT_300 and !pp)      _counters.at("SRHH-35").add_event(event);
                    if (MTmiss_l_120 and met<300     and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-36").add_event(event);
                    if (MTmiss_l_120 and met<300     and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-37").add_event(event);
                    if (MTmiss_l_120 and met<300     and Nj_5   and HT_300_1125 and pp)  _counters.at("SRHH-38").add_event(event);
                    if (MTmiss_l_120 and met<300     and Nj_5   and HT_300_1125 and !pp) _counters.at("SRHH-39").add_event(event);
                    if (MTmiss_g_120                            and HT_300)              _counters.at("SRHH-40").add_event(event);
                    if (MTmiss_g_120 and met<300     and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHH-41").add_event(event);
                    if (MTmiss_g_120 and met<300     and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHH-42").add_event(event);
                    if (MTmiss_g_120 and met<300     and Nj_5   and HT_300_1125 and pp)  _counters.at("SRHH-43").add_event(event);
                    if (MTmiss_g_120 and met<300     and Nj_5   and HT_300_1125 and !pp) _counters.at("SRHH-44").add_event(event);
                }

                if (met_300_500 and Nj_2_4 and HT>300 and pp)  _counters.at("SRHH-45").add_event(event);
                if (met_300_500 and Nj_2_4 and HT>300 and !pp) _counters.at("SRHH-46").add_event(event);
                if (met_500     and Nj_2_4 and HT>300 and pp)  _counters.at("SRHH-47").add_event(event);
                if (met_500     and Nj_2_4 and HT>300 and !pp) _counters.at("SRHH-48").add_event(event);
                if (met_300_500 and Nj_5   and HT>300 and pp)  _counters.at("SRHH-49").add_event(event);
                if (met_300_500 and Nj_5   and HT>300 and !pp) _counters.at("SRHH-50").add_event(event);
                if (met_500     and Nj_5   and HT>300 and pp)  _counters.at("SRHH-51").add_event(event);
                if (met_500     and Nj_5   and HT>300 and !pp) _counters.at("SRHH-52").add_event(event);

                if (HT_1125_1300 and met<300 and Nj<5) _counters.at("SRHH-53").add_event(event);
                if (HT_1300_1600 and met<300 and Nj<5) _counters.at("SRHH-54").add_event(event);
                if (HT_1600      and met<300 and Nj<5) _counters.at("SRHH-55").add_event(event);

                if (HT_1125_1300 and met<300 and Nj==5 and Nj==6) _counters.at("SRHH-56").add_event(event);
                if (HT_1300_1600 and met<300 and Nj==5 and Nj==6) _counters.at("SRHH-57").add_event(event);
                if (HT_1600      and met<300 and Nj==5 and Nj==6) _counters.at("SRHH-58").add_event(event);

                if (HT_1125_1300 and met<300 and Nj<5) _counters.at("SRHH-59").add_event(event);
                if (HT_1300_1600 and met<300 and Nj<5) _counters.at("SRHH-60").add_event(event);
                if (HT_1600      and met<300 and Nj<5) _counters.at("SRHH-61").add_event(event);
            }

            bool SSHL_combine = MTmiss_l_120&&( (met_50_200&&Nj_5) or met_200_300 )&&HT_300 ;

            // SSHL: exactly 2 leptons, one with PT>25 GeV, one with PT<25 GeV,  and MET>50 GeV
            if (leptons.size()==2 and leptons[0]->pT() > 25. and leptons[1]->pT() < 25.) {
                if (Nb==0 and MTmiss_l_120) {
                    if ( met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHL-0").add_event(event);
                    if ( met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHL-1").add_event(event);
                    if ( SSHL_combine)                                   _counters.at("SRHL-2").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125)           _counters.at("SRHL-3").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHL-4").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHL-5").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125)           _counters.at("SRHL-6").add_event(event);

                } else if(Nb==1 and MTmiss_l_120) {
                    if ( met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHL-7").add_event(event);
                    if ( met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHL-8").add_event(event);
                    if ( SSHL_combine and pp)                            _counters.at("SRHL-9").add_event(event);
                    if ( SSHL_combine and !pp)                           _counters.at("SRHL-10").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and pp)    _counters.at("SRHL-11").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and !pp)   _counters.at("SRHL-12").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125)         _counters.at("SRHL-13").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125 and pp)    _counters.at("SRHL-14").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125 and !pp)   _counters.at("SRHL-15").add_event(event);
                } else if(Nb==2 and MTmiss_l_120) {
                    if ( met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHL-16").add_event(event);
                    if ( met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHL-17").add_event(event);
                    if ( SSHL_combine and pp)                            _counters.at("SRHL-18").add_event(event);
                    if ( SSHL_combine and !pp)                           _counters.at("SRHL-19").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and pp)    _counters.at("SRHL-20").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and !pp)   _counters.at("SRHL-21").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHL-22").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHL-23").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125)           _counters.at("SRHL-24").add_event(event);
                }else if(Nb==3 and MTmiss_l_120) {
                    if ( met_50_200 and HT_300 and pp)                   _counters.at("SRHL-25").add_event(event);
                    if ( met_50_200 and HT_300 and !pp)                  _counters.at("SRHL-26").add_event(event);
                    if ( met_50_200 and HT_300_1125 and pp)              _counters.at("SRHL-27").add_event(event);
                    if ( met_50_200 and HT_300_1125 and !pp)             _counters.at("SRHL-28").add_event(event);
                    if ( met_200_300 and HT_300_1125)                    _counters.at("SRHL-29").add_event(event);
                }
                if (MTmiss_g_120 and met<300 and HT_300)       _counters.at("SRHL-30").add_event(event);
                if (MTmiss_g_120 and met<300 and HT_300_1125)  _counters.at("SRHL-31").add_event(event);
                if (met_300_500 and Nj_2_4 and HT>300 and pp)  _counters.at("SRHL-32").add_event(event);
                if (met_300_500 and Nj_2_4 and HT>300 and !pp) _counters.at("SRHL-33").add_event(event);
                if (met_500 and Nj_2_4 and HT>300 and pp)      _counters.at("SRHL-34").add_event(event);
                if (met_500 and Nj_2_4 and HT>300 and !pp)     _counters.at("SRHL-35").add_event(event);
                if (met_300_500 and Nj_5 and HT>300 and pp)    _counters.at("SRHL-36").add_event(event);
                if (met_300_500 and Nj_5 and HT>300 and !pp)   _counters.at("SRHL-37").add_event(event);
                if (met_500 and Nj_5 and HT>300)               _counters.at("SRHL-38").add_event(event);

                if (HT_1125_1300 and pp)  _counters.at("SRHL-39").add_event(event);
                if (HT_1125_1300 and !pp) _counters.at("SRHL-40").add_event(event);
                if (HT_1300 and pp)       _counters.at("SRHL-41").add_event(event);
                if (HT_1300 and !pp)      _counters.at("SRHL-42").add_event(event);
            }

            // SSLL: exactly 2 leptons, both with PT<25 GeV, and MET>50 GeV
            if (leptons.size()==2 and leptons[0]->pT() < 25. and leptons[1]->pT() < 25.) {
                if (HT>400) {
                    if (MTmiss_l_120) {
                        if (Nb==0) {
                            if (met_50_200) _counters.at("SRLL-0").add_event(event);
                            else            _counters.at("SRLL-1").add_event(event);
                        } else if (Nb==1) {
                            if (met_50_200) _counters.at("SRLL-2").add_event(event);
                            else            _counters.at("SRLL-3").add_event(event);
                        } else if (Nb==2) {
                            if (met_50_200) _counters.at("SRLL-4").add_event(event);
                            else            _counters.at("SRLL-5").add_event(event);
                        } else if (Nb>=3)   _counters.at("SRLL-6").add_event(event);
                    } else                  _counters.at("SRLL-7").add_event(event);
                }
            }

            // LM: exactly 2 leptons, both with PT>25 GeV, and MET<50 GeV
            if (leptons.size()==2 and leptons[0]->pT() > 25. and leptons[1]->pT() > 25.) {
                if (HT_300_1125) {
                    if (Nb==0) {
                        if (Nj_2_4) _counters.at("SRLM-0").add_event(event);
                        if (Nj_5)   _counters.at("SRLM-1").add_event(event);
                    } else if (Nb==1){
                        if (Nj_2_4) _counters.at("SRLM-2").add_event(event);
                        if (Nj_5)   _counters.at("SRLM-3").add_event(event);
                    } else if (Nb==2){
                        if (Nj_2_4) _counters.at("SRLM-4").add_event(event);
                        if (Nj_5)   _counters.at("SRLM-5").add_event(event);
                    } else          _counters.at("SRLM-6").add_event(event);
                } else if (HT_1125_1300){
                    if (Nj_2_4) {
                        _counters.at("SRLM-7").add_event(event);
                    } else if (Nj_5) {
                        _counters.at("SRLM-8").add_event(event);
                    }
                } else if (HT_1300){
                    if (Nj_2_4) {
                        _counters.at("SRLM-9").add_event(event);
                    } else if (Nj_5) {
                        _counters.at("SRLM-1").add_event(event);
                    }
                }
            }

            // ML: >=3 leptons, at least one with PT>25 GeV, and MET>50 GeV
            if (leptons.size()>=3 and leptons[0]->pT() > 25.) {
                bool on_Z=false;
                size_t Z_l1;
                size_t Z_l2;
                for (size_t i=0; i<leptons.size(); ++i) {
                    for (size_t j=i+1; j<leptons.size(); ++j) {
                        if (leptons[i]->pid()+leptons[j]->pid()==0 and fabs((leptons[i]->mom()+leptons[j]->mom()).m()-91)<15) {
                            on_Z = true;
                            Z_l1=i;
                            Z_l2=j;
                            break;
                        }
                    }
                    if (on_Z) break;
                }

                if (not on_Z){ // off-Z
                    if (Nb==0) {
                        if (HT<400) {
                            if (met<150) {
                                if (MTmiss_l_120) _counters.at("SRML-0").add_event(event);
                                else              _counters.at("SRML-1").add_event(event);
                            } else if (met<300) {
                                if (MTmiss_l_120) _counters.at("SRML-2").add_event(event);
                                else              _counters.at("SRML-3").add_event(event);
                            }
                        }
                        else if (HT<600) {
                             if (met<150)         _counters.at("SRML-4").add_event(event);
                             else if (met<300)    _counters.at("SRML-5").add_event(event);
                        }
                    } else if (Nb==1) {
                        if (HT<400) {
                             if (met<150)         _counters.at("SRML-6").add_event(event);
                             else if (met<300)    _counters.at("SRML-7").add_event(event);
                        }
                        else if (HT<600) {
                             if (met<150)         _counters.at("SRML-8").add_event(event);
                             else if (met<300)    _counters.at("SRML-9").add_event(event);
                        }
                    } else if (Nb==2) {
                        if (HT<400) {
                             if (met<150)         _counters.at("SRML-10").add_event(event);
                             else if (met<300)    _counters.at("SRML-11").add_event(event);
                        }
                        else if (HT<600) {
                             if (met<150)         _counters.at("SRML-12").add_event(event);
                             else if (met<300)    _counters.at("SRML-13").add_event(event);
                        }
                    } else if (Nb>=3) {
                        if (HT<600)               _counters.at("SRML-14").add_event(event);
                    }
                    if (HT>=600) {
                        if (met<150) {
                            if (MTmiss_l_120)     _counters.at("SRML-15").add_event(event);
                            else                  _counters.at("SRML-16").add_event(event);
                        } else if (met<300) {
                            if (MTmiss_l_120)     _counters.at("SRML-17").add_event(event);
                            else                  _counters.at("SRML-18").add_event(event);
                        }
                    }
                    if (met>300) {
                        if (MTmiss_l_120)         _counters.at("SRML-19").add_event(event);
                        else                      _counters.at("SRML-20").add_event(event);
                    }
                } else { // on-Z
                    // M_T^{miss} for on-Z
                    double MTmiss_Z = 1000;
                    for (size_t i=0; i<leptons.size(); ++i) {
                        if ( (i != Z_l1) and (i != Z_l2)) {
                            double MTmiss_try = sqrt(2.*leptons[i]->pT()*met*(1. - cos(leptons[i]->mom().deltaPhi(ptot))));
                            if (MTmiss_try<MTmiss_Z) MTmiss_Z=MTmiss_try;
                        }
                    }
                    bool MTmiss_Z_l_120 = MTmiss_Z<120;
                    if (Nb==0) {
                        if (HT<400) {
                            if (met<150) {
                                if (MTmiss_Z_l_120) _counters.at("SRML-21").add_event(event);
                                else                _counters.at("SRML-22").add_event(event);
                            } else if (met<300) {
                                if (MTmiss_Z_l_120) _counters.at("SRML-23").add_event(event);
                                else                _counters.at("SRML-24").add_event(event);
                            }
                        }
                        else if (HT<600) {
                            if (met<150) {
                                if (MTmiss_Z_l_120) _counters.at("SRML-25").add_event(event);
                                else                _counters.at("SRML-26").add_event(event);
                            } else if (met<300) {
                                if (MTmiss_Z_l_120) _counters.at("SRML-27").add_event(event);
                                else                _counters.at("SRML-28").add_event(event);
                            }
                        }
                    } else if (Nb==1) {
                        if (HT<400) {
                             if (met<150)           _counters.at("SRML-29").add_event(event);
                             else if (met<300)      _counters.at("SRML-30").add_event(event);
                        }
                        else if (HT<600) {
                             if (met<150)           _counters.at("SRML-31").add_event(event);
                             else if (met<300)      _counters.at("SRML-32").add_event(event);
                        }
                    } else if (Nb==2) {
                        if (HT<400) {
                             if (met<150)           _counters.at("SRML-33").add_event(event);
                             else if (met<300)      _counters.at("SRML-34").add_event(event);
                        }
                        else if (HT<600) {
                             if (met<150)           _counters.at("SRML-35").add_event(event);
                             else if (met<300)      _counters.at("SRML-36").add_event(event);
                        }
                    } else if (Nb>=3) {
                        if (HT<600)                 _counters.at("SRML-37").add_event(event);
                    }
                    if (HT>=600) {
                        if (met<150) {
                            if (MTmiss_Z_l_120)     _counters.at("SRML-38").add_event(event);
                            else                    _counters.at("SRML-39").add_event(event);
                        } else if (met<300) {
                            if (MTmiss_Z_l_120)     _counters.at("SRML-40").add_event(event);
                            else                    _counters.at("SRML-41").add_event(event);
                        }
                    }
                    if (met>300) {
                        if (MTmiss_Z_l_120)         _counters.at("SRML-42").add_event(event);
                        else                        _counters.at("SRML-43").add_event(event);
                    }
                }
            }

            return;
        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2SSLEP_Stop_137invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2SSLEP_Stop_137invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results() {

            // HH
            add_result(SignalRegionData(_counters.at("SRHH-0"), 1609, {1510, 310}));
            add_result(SignalRegionData(_counters.at("SRHH-1"), 647, {590, 90}));
            add_result(SignalRegionData(_counters.at("SRHH-2"), 132, {103, 22}));
            add_result(SignalRegionData(_counters.at("SRHH-3"), 51, {38, 7}));
            add_result(SignalRegionData(_counters.at("SRHH-4"), 49, {57, 10}));
            add_result(SignalRegionData(_counters.at("SRHH-5"), 23, {32, 9}));
            add_result(SignalRegionData(_counters.at("SRHH-6"), 7, {5.5, 1.7}));
            add_result(SignalRegionData(_counters.at("SRHH-7"), 31, {25, 6}));
            add_result(SignalRegionData(_counters.at("SRHH-8"), 20, {21, 5}));
            add_result(SignalRegionData(_counters.at("SRHH-9"), 11, {9.4, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-10"), 1068, {930, 230}));
            add_result(SignalRegionData(_counters.at("SRHH-11"), 370, {330, 70}));
            add_result(SignalRegionData(_counters.at("SRHH-12"), 38, {36, 7}));
            add_result(SignalRegionData(_counters.at("SRHH-13"), 31, {25, 5}));
            add_result(SignalRegionData(_counters.at("SRHH-14"), 63, {44, 7}));
            add_result(SignalRegionData(_counters.at("SRHH-15"), 38, {39, 8}));
            add_result(SignalRegionData(_counters.at("SRHH-16"), 30, {27, 5}));
            add_result(SignalRegionData(_counters.at("SRHH-17"), 15, {14.8, 3.2}));
            add_result(SignalRegionData(_counters.at("SRHH-18"), 12, {11.5, 3.0}));
            add_result(SignalRegionData(_counters.at("SRHH-19"), 14, {11.8, 2.6}));
            add_result(SignalRegionData(_counters.at("SRHH-20"), 16, {9.6, 2.1}));
            add_result(SignalRegionData(_counters.at("SRHH-21"), 15, {10.0, 1.6}));
            add_result(SignalRegionData(_counters.at("SRHH-22"), 345, {270, 40}));
            add_result(SignalRegionData(_counters.at("SRHH-23"), 169, {143, 20}));
            add_result(SignalRegionData(_counters.at("SRHH-24"), 11, {15.2, 2.4}));
            add_result(SignalRegionData(_counters.at("SRHH-25"), 18, {13.8, 3.4}));
            add_result(SignalRegionData(_counters.at("SRHH-26"), 43, {33, 5}));
            add_result(SignalRegionData(_counters.at("SRHH-27"), 38, {29, 4}));
            add_result(SignalRegionData(_counters.at("SRHH-28"), 9, {11.5, 2.5}));
            add_result(SignalRegionData(_counters.at("SRHH-29"), 5, {6.7, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHH-30"), 6, {7.5, 1.8}));
            add_result(SignalRegionData(_counters.at("SRHH-31"), 14, {5.9, 1.0}));
            add_result(SignalRegionData(_counters.at("SRHH-32"), 7, {6.5, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-33"), 11, {6.7, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHH-34"), 17, {10.3, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-35"), 11, {8.6, 1.7}));
            add_result(SignalRegionData(_counters.at("SRHH-36"), 6, {10.6, 2.0}));
            add_result(SignalRegionData(_counters.at("SRHH-37"), 5, {7.3, 1.3}));
            add_result(SignalRegionData(_counters.at("SRHH-38"), 8, {9.6, 2.2}));
            add_result(SignalRegionData(_counters.at("SRHH-39"), 11, {9.2, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-40"), 2, {1.3, 0.6}));
            add_result(SignalRegionData(_counters.at("SRHH-41"), 1, {0.6, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-42"), 0, {0.8, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-43"), 1, {0.7, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-44"), 1, {0.7, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHH-45"), 59, {42, 7}));
            add_result(SignalRegionData(_counters.at("SRHH-46"), 23, {18, 4}));
            add_result(SignalRegionData(_counters.at("SRHH-47"), 10, {13, 9}));
            add_result(SignalRegionData(_counters.at("SRHH-48"), 4, {2.0, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHH-49"), 13, {6.3, 1.0}));
            add_result(SignalRegionData(_counters.at("SRHH-50"), 4, {3.7, 0.7}));
            add_result(SignalRegionData(_counters.at("SRHH-51"), 4, {1.26, 0.33}));
            add_result(SignalRegionData(_counters.at("SRHH-52"), 2, {0.4, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-53"), 24, {10.1, 1.5}));
            add_result(SignalRegionData(_counters.at("SRHH-54"), 4, {7.0, 1.1}));
            add_result(SignalRegionData(_counters.at("SRHH-55"), 5, {4.3, 0.9}));
            add_result(SignalRegionData(_counters.at("SRHH-56"), 7, {5.3, 0.8}));
            add_result(SignalRegionData(_counters.at("SRHH-57"), 6, {6, 6}));
            add_result(SignalRegionData(_counters.at("SRHH-58"), 3, {2.2, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-59"), 5, {1.8, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHH-60"), 4, {1.9, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHH-61"), 0, {1.3, 0.9}));

            // HL
            add_result(SignalRegionData(_counters.at("SRHL-0"), 1504, {1300, 310}));
            add_result(SignalRegionData(_counters.at("SRHL-1"), 319, {310, 70}));
            add_result(SignalRegionData(_counters.at("SRHL-2"), 32, {25, 6}));
            add_result(SignalRegionData(_counters.at("SRHL-3"), 32, {32, 8}));
            add_result(SignalRegionData(_counters.at("SRHL-4"), 32, {29, 6}));
            add_result(SignalRegionData(_counters.at("SRHL-5"), 11, {17, 6}));
            add_result(SignalRegionData(_counters.at("SRHL-6"), 6, {4.5, 2.5}));
            add_result(SignalRegionData(_counters.at("SRHL-7"), 1223, {1010, 250}));
            add_result(SignalRegionData(_counters.at("SRHL-8"), 307, {270, 60}));
            add_result(SignalRegionData(_counters.at("SRHL-9"), 5, {7.1, 1.7}));
            add_result(SignalRegionData(_counters.at("SRHL-10"), 7, {6.5, 1.6}));
            add_result(SignalRegionData(_counters.at("SRHL-11"), 42, {39, 9}));
            add_result(SignalRegionData(_counters.at("SRHL-12"), 37, {31, 8}));
            add_result(SignalRegionData(_counters.at("SRHL-13"), 27, {23, 5}));
            add_result(SignalRegionData(_counters.at("SRHL-14"), 7, {2.1, 1.1}));
            add_result(SignalRegionData(_counters.at("SRHL-15"), 2, {1.7, 0.9}));
            add_result(SignalRegionData(_counters.at("SRHL-16"), 256, {210, 40}));
            add_result(SignalRegionData(_counters.at("SRHL-17"), 104, {85, 14}));
            add_result(SignalRegionData(_counters.at("SRHL-18"), 4, {2.5, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHL-19"), 3, {3.0, 1.5}));
            add_result(SignalRegionData(_counters.at("SRHL-20"), 27, {18.9, 3.5}));
            add_result(SignalRegionData(_counters.at("SRHL-21"), 18, {15.9, 2.8}));
            add_result(SignalRegionData(_counters.at("SRHL-22"), 2, {3.3, 0.6}));
            add_result(SignalRegionData(_counters.at("SRHL-23"), 2, {4.4, 1.6}));
            add_result(SignalRegionData(_counters.at("SRHL-24"), 5, {4.5, 1.7}));
            add_result(SignalRegionData(_counters.at("SRHL-25"), 8, {8.2, 2.2}));
            add_result(SignalRegionData(_counters.at("SRHL-26"), 6, {8.1, 2.2}));
            add_result(SignalRegionData(_counters.at("SRHL-27"), 12, {9.7, 2.1}));
            add_result(SignalRegionData(_counters.at("SRHL-28"), 7, {10.8, 2.8}));
            add_result(SignalRegionData(_counters.at("SRHL-29"), 3, {1.1, 0.4}));
            add_result(SignalRegionData(_counters.at("SRHL-30"), 5, {2.2, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHL-31"), 3, {2.6, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHL-32"), 23, {22, 6}));
            add_result(SignalRegionData(_counters.at("SRHL-33"), 8, {7.2, 1.4}));
            add_result(SignalRegionData(_counters.at("SRHL-34"), 4, {2.3, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHL-35"), 1, {0.42, 0.33}));
            add_result(SignalRegionData(_counters.at("SRHL-36"), 3, {3.2, 1.5}));
            add_result(SignalRegionData(_counters.at("SRHL-37"), 0, {1.4, 0.6}));
            add_result(SignalRegionData(_counters.at("SRHL-38"), 0, {0.41, 0.25}));
            add_result(SignalRegionData(_counters.at("SRHL-39"), 7, {3.1, 0.7}));
            add_result(SignalRegionData(_counters.at("SRHL-40"), 0, {4, 4}));
            add_result(SignalRegionData(_counters.at("SRHL-41"), 8, {4.7, 0.9}));
            add_result(SignalRegionData(_counters.at("SRHL-42"), 6, {1.71, 0.35}));

            // LL
            add_result(SignalRegionData(_counters.at("SRLL-0"), 25, {20, 6}));
            add_result(SignalRegionData(_counters.at("SRLL-1"), 6, {4.9, 1.5}));
            add_result(SignalRegionData(_counters.at("SRLL-2"), 29, {23, 6}));
            add_result(SignalRegionData(_counters.at("SRLL-3"), 8, {4, 4}));
            add_result(SignalRegionData(_counters.at("SRLL-4"), 13, {7.7, 2.1}));
            add_result(SignalRegionData(_counters.at("SRLL-5"), 0, {1.5, 0.8}));
            add_result(SignalRegionData(_counters.at("SRLL-6"), 0, {2.5, 1.2}));
            add_result(SignalRegionData(_counters.at("SRLL-7"), 0, {0.07, 0.07}));

            // LM
            add_result(SignalRegionData(_counters.at("SRLM-0"), 314, {240, 50}));
            add_result(SignalRegionData(_counters.at("SRLM-1"), 22, {20, 5}));
            add_result(SignalRegionData(_counters.at("SRLM-2"), 159, {140, 31}));
            add_result(SignalRegionData(_counters.at("SRLM-3"), 37, {32, 7}));
            add_result(SignalRegionData(_counters.at("SRLM-4"), 66, {54, 8}));
            add_result(SignalRegionData(_counters.at("SRLM-5"), 33, {22, 4}));
            add_result(SignalRegionData(_counters.at("SRLM-6"), 23, {9.7, 2.1}));
            add_result(SignalRegionData(_counters.at("SRLM-7"), 3, {1.5, 0.5}));
            add_result(SignalRegionData(_counters.at("SRLM-8"), 1, {1.6, 0.4}));
            add_result(SignalRegionData(_counters.at("SRLM-9"), 1, {2.9, 2.9}));
            add_result(SignalRegionData(_counters.at("SRLM-10"), 3, {1.9, 1.4}));

            // ML
            add_result(SignalRegionData(_counters.at("SRML-0"), 263, {220, 40}));
            add_result(SignalRegionData(_counters.at("SRML-1"), 1, {2.5, 2.5}));
            add_result(SignalRegionData(_counters.at("SRML-2"), 34, {32, 6}));
            add_result(SignalRegionData(_counters.at("SRML-3"), 1, {0.9, 0.5}));
            add_result(SignalRegionData(_counters.at("SRML-4"), 28, {22, 4}));
            add_result(SignalRegionData(_counters.at("SRML-5"), 8, {9.5, 1.8}));
            add_result(SignalRegionData(_counters.at("SRML-6"), 265, {210, 40}));
            add_result(SignalRegionData(_counters.at("SRML-7"), 47, {36, 6}));
            add_result(SignalRegionData(_counters.at("SRML-8"), 20, {21.6, 3.2}));
            add_result(SignalRegionData(_counters.at("SRML-9"), 16, {11.6, 1.9}));
            add_result(SignalRegionData(_counters.at("SRML-10"), 105, {84, 11}));
            add_result(SignalRegionData(_counters.at("SRML-11"), 17, {15.5, 2.1}));
            add_result(SignalRegionData(_counters.at("SRML-12"), 21, {15.7, 2.2}));
            add_result(SignalRegionData(_counters.at("SRML-13"), 8, {5.3, 0.8}));
            add_result(SignalRegionData(_counters.at("SRML-14"), 12, {10.2, 2.1}));
            add_result(SignalRegionData(_counters.at("SRML-15"), 40, {27, 4}));
            add_result(SignalRegionData(_counters.at("SRML-16"), 2, {0.8, 0.5}));
            add_result(SignalRegionData(_counters.at("SRML-17"), 24, {17.8, 2.4}));
            add_result(SignalRegionData(_counters.at("SRML-18"), 0, {1.0, 0.4}));
            add_result(SignalRegionData(_counters.at("SRML-19"), 30, {17.8, 3.0}));
            add_result(SignalRegionData(_counters.at("SRML-20"), 2, {1.26, 0.33}));
            add_result(SignalRegionData(_counters.at("SRML-21"), 955, {830, 180}));
            add_result(SignalRegionData(_counters.at("SRML-22"), 136, {108, 22}));
            add_result(SignalRegionData(_counters.at("SRML-23"), 139, {117, 26}));
            add_result(SignalRegionData(_counters.at("SRML-24"), 8, {11.1, 2.3}));
            add_result(SignalRegionData(_counters.at("SRML-25"), 128, {111, 24}));
            add_result(SignalRegionData(_counters.at("SRML-26"), 20, {21, 5}));
            add_result(SignalRegionData(_counters.at("SRML-27"), 45, {42, 10}));
            add_result(SignalRegionData(_counters.at("SRML-28"), 3, {3.4, 0.9}));
            add_result(SignalRegionData(_counters.at("SRML-29"), 408, {320, 50}));
            add_result(SignalRegionData(_counters.at("SRML-30"), 50, {47, 8}));
            add_result(SignalRegionData(_counters.at("SRML-31"), 62, {51, 9}));
            add_result(SignalRegionData(_counters.at("SRML-32"), 24, {15.1, 2.6}));
            add_result(SignalRegionData(_counters.at("SRML-33"), 157, {131, 24}));
            add_result(SignalRegionData(_counters.at("SRML-34"), 24, {20, 4}));
            add_result(SignalRegionData(_counters.at("SRML-35"), 36, {27, 5}));
            add_result(SignalRegionData(_counters.at("SRML-36"), 11, {7.8, 1.5}));
            add_result(SignalRegionData(_counters.at("SRML-37"), 18, {12.9, 2.6}));
            add_result(SignalRegionData(_counters.at("SRML-38"), 117, {82, 14}));
            add_result(SignalRegionData(_counters.at("SRML-39"), 26, {18, 4}));
            add_result(SignalRegionData(_counters.at("SRML-40"), 29, {39, 8}));
            add_result(SignalRegionData(_counters.at("SRML-41"), 7, {4.9, 0.9}));
            add_result(SignalRegionData(_counters.at("SRML-42"), 44, {46, 10}));
            add_result(SignalRegionData(_counters.at("SRML-43"), 11, {5.7, 1.2}));

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


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2SSLEP_Stop_137invfb)

  }
}
