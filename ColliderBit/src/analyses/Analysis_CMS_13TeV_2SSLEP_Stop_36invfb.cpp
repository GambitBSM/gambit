///
///  \author Yang Zhang
///  \date 2019 July
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-035/index.html
//          https://arxiv.org/abs/1704.07323

// Search for physics beyond the standard model in events with two leptons of same sign, missing transverse momentum, and jets in proton-proton collisions at sqrt(s) = 13 TeV

// Note:
// 1. Not fully validated.
// 2. Not sure how to deal with the case that there are more than one lepton pairs. Here just use the first one.
// 3. Apply ATLAS Jet-Lepton Overlap Removal

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

    class Analysis_CMS_13TeV_2SSLEP_Stop_36invfb : public Analysis {
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
            // LL
            {"SRLL-0", EventCounter("SRLL-0")},
            {"SRLL-1", EventCounter("SRLL-1")},
            {"SRLL-2", EventCounter("SRLL-2")},
            {"SRLL-3", EventCounter("SRLL-3")},
            {"SRLL-4", EventCounter("SRLL-4")},
            {"SRLL-5", EventCounter("SRLL-5")},
            {"SRLL-6", EventCounter("SRLL-6")},
            {"SRLL-7", EventCounter("SRLL-7")},
            // inc
            {"SRinc-0", EventCounter("SRinc-0")},
            {"SRinc-1", EventCounter("SRinc-1")},
            {"SRinc-2", EventCounter("SRinc-2")},
            {"SRinc-3", EventCounter("SRinc-3")},
            {"SRinc-4", EventCounter("SRinc-4")},
            {"SRinc-5", EventCounter("SRinc-5")},
            {"SRinc-6", EventCounter("SRinc-6")},
            {"SRinc-7", EventCounter("SRinc-7")},
            {"SRinc-8", EventCounter("SRinc-8")},
            {"SRinc-9", EventCounter("SRinc-9")},
            {"SRinc-10", EventCounter("SRinc-10")},
            {"SRinc-11", EventCounter("SRinc-11")},
            {"SRinc-12", EventCounter("SRinc-12")},
            {"SRinc-13", EventCounter("SRinc-13")},
            {"SRinc-14", EventCounter("SRinc-14")},
            // exc
            {"SRexc-0", EventCounter("SRexc-0")},
            {"SRexc-1", EventCounter("SRexc-1")},
            {"SRexc-2", EventCounter("SRexc-2")},
            {"SRexc-3", EventCounter("SRexc-3")},
            {"SRexc-4", EventCounter("SRexc-4")},
            {"SRexc-5", EventCounter("SRexc-5")},
            {"SRexc-6", EventCounter("SRexc-6")},
            {"SRexc-7", EventCounter("SRexc-7")},
            {"SRexc-8", EventCounter("SRexc-8")},
            {"SRexc-9", EventCounter("SRexc-9")},
            {"SRexc-10", EventCounter("SRexc-10")},
            {"SRexc-11", EventCounter("SRexc-11")},
            {"SRexc-12", EventCounter("SRexc-12")},
            {"SRexc-13", EventCounter("SRexc-13")},
            {"SRexc-14", EventCounter("SRexc-14")},
        };

        Cutflow _cutflow;

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Jet*> Survivors;

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

      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<const HEPUtils::Particle*> Survivors;

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


    public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_CMS_13TeV_2SSLEP_Stop_36invfb():
        _cutflow("CMS_13TeV_2SSLEP_Stop_36invfb", {"Trigger_and_2leptons", "At_least_one_SS_lepton_pair", "Baseline"})
        {
            set_analysis_name("CMS_13TeV_2SSLEP_Stop_36invfb");
            set_luminosity(36);
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
            const vector<double> bMu={0., 10, 15., 20., 25, 30, 40, 50, DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
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

            // Overlap removal
            JetLeptonOverlapRemoval(candJets,electrons,0.2);
            LeptonJetOverlapRemoval(electrons,candJets);
            JetLeptonOverlapRemoval(candJets,muons,0.4);
            LeptonJetOverlapRemoval(muons,candJets);

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
                else if( jet->pT() > 40. ) {
                    nonbJets.push_back(jet);
                }
            }

            size_t Nb=bJets.size();
            size_t Nj=nonbJets.size();

            // Leptons = electrons + muons
            vector<const HEPUtils::Particle*> leptons;
            leptons=electrons;
            leptons.insert(leptons.end(),muons.begin(),muons.end());
            sort(leptons.begin(),leptons.end(),comparePt);

            // At least two light leptons
            if (leptons.size()<2) return;

            // Triggers
            bool pure_dilepton_trigger=false;
            // Leading electron (muon) PT > 23 (17) GeV
            // Subleading electron (muon) PT > 12 (8) GeV
            if (leptons[0]->pT() > ( abs(leptons[0]->pid()) == 11 ? 23 : 17 ) \
            and leptons[1]->pT() > ( abs(leptons[1]->pid()) == 11 ? 12 : 8 ) ){
                pure_dilepton_trigger = true;
            }
            if ( not pure_dilepton_trigger and HT<300 ) return;
            _cutflow.fill(1); // Trigger and >=2 leptons

            // Find pair same sign (SS) leptons
            vector<size_t> SS_1,SS_2;
            for (size_t i=0; i<leptons.size(); ++i) {
                for (size_t j=i+1; j<leptons.size(); ++j) {
                    if (leptons[i]->pid()*leptons[j]->pid()>0 and (leptons[i]->mom()+leptons[j]->mom()).m()>8){
                        SS_1.push_back(i);
                        SS_2.push_back(j);
                    }
                }
            }

            // At least one SS lepton pair ( with an invari-ant mass above 8 GeV )
            if (SS_1.size()==0) return;
            _cutflow.fill(2); // At least one SS lepton pair

            // An additional loose lepton forms an opposite-sign same-flavor pair
            // withone of the two SS leptons, with an invariant mass less than 12 GeV
            // or between 76 and 106 GeV
            if (leptons.size()>2){
                for (size_t i=0; i<SS_1.size(); ++i) {
                    for (size_t j=0; j<leptons.size(); ++j) {
                        if ( j != SS_1[i] and j != SS_2[i]) {
                            if (leptons[j]->pid()+leptons[SS_1[i]]->pid()==0){
                                double mll_additional = (leptons[j]->mom()+leptons[SS_1[i]]->mom()).m();
                                if ( mll_additional < 12 or (mll_additional>76 and mll_additional<106)) return;
                            }
                            if (leptons[j]->pid()+leptons[SS_2[i]]->pid()==0){
                                double mll_additional = (leptons[j]->mom()+leptons[SS_2[i]]->mom()).m();
                                if ( mll_additional < 12 or (mll_additional>76 and mll_additional<106)) return;
                            }
                        }
                    }
                }
            }


            // At least two jets and MET>50
            if ( nonbJets.size()<2 or  met<50) return;
            _cutflow.fill(3); // Baseline (two jets and MET>50 GeV)

            // M_T^{miss}
            // The smallest of the transverse masses constructed between p^miss_T and each of the leptons.
            double MTmiss = 9999;
            for (const HEPUtils::Particle* lep : leptons) {
                double MTmiss_temp = sqrt(2.*lep->pT()*met*(1. - cos(lep->mom().deltaPhi(ptot))));
                if (MTmiss_temp<MTmiss) {
                    MTmiss = MTmiss_temp;
                }
            }

            bool pp = leptons[SS_1[0]]->pid()>0; // TODO: Not sure which lepton pair.
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
            bool SSHH_combine = (MTmiss_l_120 and met_50_200   and Nj_5 and HT_300) or \
                                (MTmiss_l_120 and met_200_300           and HT_300) or \
                                (MTmiss_g_120 and met<300               and HT_300);

            // SR HH
            if ( leptons[SS_1[0]]->pT() > 25. and leptons[SS_2[0]]->pT() > 25.) {
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
                    if (MTmiss_l_120 and met_50_200             and HT_300_1125 and pp)  _counters.at("SRHH-36").add_event(event);
                    if (MTmiss_l_120 and met_50_200             and HT_300_1125 and !pp) _counters.at("SRHH-37").add_event(event);
                    if (MTmiss_l_120 and met_200_300            and HT_300_1125)         _counters.at("SRHH-38").add_event(event);
                    if (MTmiss_g_120 and met<300                and HT_300)              _counters.at("SRHH-39").add_event(event);
                    if (MTmiss_g_120 and met<300                and HT_300_1125)         _counters.at("SRHH-40").add_event(event);
                }

                if (met_300_500 and HT>300       and pp)  _counters.at("SRHH-41").add_event(event);
                if (met_300_500 and HT>300       and !pp) _counters.at("SRHH-42").add_event(event);
                if (met_500     and HT>300       and pp)  _counters.at("SRHH-43").add_event(event);
                if (met_500     and HT>300       and !pp) _counters.at("SRHH-44").add_event(event);

                if (met<300     and HT_1125_1300 and pp)  _counters.at("SRHH-45").add_event(event);
                if (met<300     and HT_1125_1300 and !pp) _counters.at("SRHH-46").add_event(event);
                if (met<300     and HT_1300_1600 and pp)  _counters.at("SRHH-47").add_event(event);
                if (met<300     and HT_1300_1600 and !pp) _counters.at("SRHH-48").add_event(event);
                if (met<300     and HT_1600 and pp)  _counters.at("SRHH-48").add_event(event);
                if (met<300     and HT_1600 and !pp) _counters.at("SRHH-50").add_event(event);

            }

            bool SSHL_combine = MTmiss_l_120&&( (met_50_200&&Nj_5) or met_200_300 )&&HT_300 ;

            // SR HL
            if ( leptons[SS_1[0]]->pT() > 25. and leptons[SS_2[0]]->pT() < 25.) {
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
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHL-13").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHL-14").add_event(event);

                    if ( met_200_300 and Nj_5 and HT_300_1125 and pp)    _counters.at("SRHL-15").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125 and !pp)   _counters.at("SRHL-16").add_event(event);
                } else if(Nb==2 and MTmiss_l_120) {
                    if ( met_50_200  and Nj_2_4 and HT_300)              _counters.at("SRHL-17").add_event(event);
                    if ( met_50_200  and Nj_2_4 and HT_300_1125)         _counters.at("SRHL-18").add_event(event);
                    if ( SSHL_combine and pp)                            _counters.at("SRHL-19").add_event(event);
                    if ( SSHL_combine and !pp)                           _counters.at("SRHL-20").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and pp)    _counters.at("SRHL-21").add_event(event);
                    if ( met_50_200  and Nj_5 and HT_300_1125 and !pp)   _counters.at("SRHL-22").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and pp)  _counters.at("SRHL-23").add_event(event);
                    if ( met_200_300 and Nj_2_4 and HT_300_1125 and !pp) _counters.at("SRHL-24").add_event(event);
                    if ( met_200_300 and Nj_5 and HT_300_1125)           _counters.at("SRHL-25").add_event(event);
                }else if(Nb==3 and MTmiss_l_120) {
                    if ( met_50_200 and HT_300 and pp)                   _counters.at("SRHL-26").add_event(event);
                    if ( met_50_200 and HT_300 and !pp)                  _counters.at("SRHL-27").add_event(event);
                    if ( met_50_200 and HT_300_1125 and pp)              _counters.at("SRHL-28").add_event(event);
                    if ( met_50_200 and HT_300_1125 and !pp)             _counters.at("SRHL-29").add_event(event);
                    if ( met_200_300 and HT_300_1125)                    _counters.at("SRHL-30").add_event(event);
                }
                if (MTmiss_g_120 and met<300 and HT_300)       _counters.at("SRHL-31").add_event(event);
                if (MTmiss_g_120 and met<300 and HT_300_1125)  _counters.at("SRHL-32").add_event(event);

                if (met_300_500  and HT>300 and pp)  _counters.at("SRHL-33").add_event(event);
                if (met_300_500  and HT>300 and !pp) _counters.at("SRHL-34").add_event(event);
                if (met_500      and HT>300 and pp)  _counters.at("SRHL-35").add_event(event);
                if (met_500      and HT>300 and !pp) _counters.at("SRHL-36").add_event(event);

                if (met<300      and HT_1125_1300 and pp)  _counters.at("SRHL-37").add_event(event);
                if (met<300      and HT_1125_1300 and !pp) _counters.at("SRHL-38").add_event(event);
                if (met<300      and HT_1300 and pp)       _counters.at("SRHL-39").add_event(event);
                if (met<300      and HT_1300 and !pp)      _counters.at("SRHL-40").add_event(event);
            }

            // SR LL
            if (leptons[SS_1[0]]->pT() < 25. and leptons[SS_2[0]]->pT() < 25.) {
                if (HT>300) {
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

            // Inclusive SR
            if (  leptons[SS_1[0]]->pT() > 25. and leptons[SS_2[0]]->pT() > 25. ) {
                // Nj>=2 and met>50 have been applied
                if ( Nb==0 and HT>=1200)               _counters.at("SRinc-0").add_event(event);
                if ( Nb>=2 and HT>=1100)               _counters.at("SRinc-1").add_event(event);
                if ( Nb==0 and met>450)                _counters.at("SRinc-2").add_event(event);
                if ( Nb>=2 and met>300)                _counters.at("SRinc-3").add_event(event);
                if ( Nb==0 and met>250 and MTmiss>120) _counters.at("SRinc-4").add_event(event);
                if ( Nb>=2 and met>150 and MTmiss>120) _counters.at("SRinc-5").add_event(event);
                if ( Nb==0 and HT>900 and met>200)     _counters.at("SRinc-6").add_event(event);
                if ( Nb>=2 and HT>900 and met>200)     _counters.at("SRinc-7").add_event(event);
                if ( Nj>=7)                            _counters.at("SRinc-8").add_event(event);
                if ( Nj>=4 and MTmiss>120)             _counters.at("SRinc-9").add_event(event);
                if ( Nb>=3)                            _counters.at("SRinc-10").add_event(event);
                if ( HT>700)                           _counters.at("SRinc-11").add_event(event);
            }

            if (  leptons[SS_1[0]]->pT() < 25. and leptons[SS_2[0]]->pT() < 25. ) {
                // Nj>=2 and met>50 have been applied
                if (met>200) _counters.at("SRinc-12").add_event(event);
                if (Nj>=5)   _counters.at("SRinc-13").add_event(event);
                if (Nb>=3)   _counters.at("SRinc-14").add_event(event);
            }

            // Exclusive SR
            if (  leptons[SS_1[0]]->pT() > 25. and leptons[SS_2[0]]->pT() > 25. ) {
                // Nj>=2 and met>50 have been applied
                if (Nb==0 and met<300 and HT<1125 and (HT<300 or MTmiss<120)) _counters.at("SRexc-0").add_event(event);
                if (Nb==0 and met<300 and HT<1125 and HT>300 and MTmiss>120)  _counters.at("SRexc-1").add_event(event);
                if (Nb==1 and met<300 and HT<1125 and (HT<300 or MTmiss<120)) _counters.at("SRexc-2").add_event(event);
                if (Nb==1 and met<300 and HT<1125 and HT>300 and MTmiss>120)  _counters.at("SRexc-3").add_event(event);
                if (Nb==2 and met<300 and HT<1125 and (HT<300 or MTmiss<120)) _counters.at("SRexc-4").add_event(event);
                if (Nb==2 and met<300 and HT<1125 and HT>300 and MTmiss>120)  _counters.at("SRexc-5").add_event(event);
                if (Nb>=3 and met<300 and HT<1125 and (HT<300 or MTmiss<120)) _counters.at("SRexc-6").add_event(event);
                if (Nb>=3 and met<300 and HT<1125 and HT>300 and MTmiss>120)  _counters.at("SRexc-7").add_event(event);
                if (          met>300 and             HT>300)                 _counters.at("SRexc-8").add_event(event);
                if (          met<300 and HT>1125)                            _counters.at("SRexc-9").add_event(event);
            }

            if (  leptons[SS_1[0]]->pT() > 25. and leptons[SS_2[0]]->pT() < 25. ) {
                // Nj>=2 and met>50 have been applied
                if (met<300 and HT<1125 and MTmiss<120) _counters.at("SRexc-10").add_event(event);
                if (met<300 and HT<1125 and MTmiss>120) _counters.at("SRexc-11").add_event(event);
                if (met>300 and HT>300)                 _counters.at("SRexc-12").add_event(event);
                if (met<300 and HT>1125)                _counters.at("SRexc-13").add_event(event);
            }
            if (  leptons[SS_1[0]]->pT() < 25. and leptons[SS_2[0]]->pT() < 25. ) {
                // Nj>=2 and met>50 have been applied
                if (HT>300) _counters.at("SRexc-14").add_event(event);
            }

            return;
        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2SSLEP_Stop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2SSLEP_Stop_36invfb*>(other);
            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results() {

            #ifdef CHECK_CUTFLOW
            cout << _cutflow << endl;
            #endif

            // HH
            add_result(SignalRegionData(_counters.at("SRHH-0"), 435, {468, 98}));
            add_result(SignalRegionData(_counters.at("SRHH-1"), 166, {162, 25}));
            add_result(SignalRegionData(_counters.at("SRHH-2"), 30, {24.4, 5.4}));
            add_result(SignalRegionData(_counters.at("SRHH-3"), 24, {17.6, 3.0}));
            add_result(SignalRegionData(_counters.at("SRHH-4"), 22, {17.8, 3.9}));
            add_result(SignalRegionData(_counters.at("SRHH-5"), 6, {7.8, 1.5}));
            add_result(SignalRegionData(_counters.at("SRHH-6"), 2, {1.96, 0.47}));
            add_result(SignalRegionData(_counters.at("SRHH-7"), 5, {4.58, 0.81}));
            add_result(SignalRegionData(_counters.at("SRHH-8"), 3, {3.63, 0.75}));
            add_result(SignalRegionData(_counters.at("SRHH-9"), 3, {2.82, 0.56}));
            add_result(SignalRegionData(_counters.at("SRHH-10"), 304, {313, 87}));
            add_result(SignalRegionData(_counters.at("SRHH-11"), 111, {104, 20}));
            add_result(SignalRegionData(_counters.at("SRHH-12"), 13, {9.5, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-13"), 11, {8.7, 2.0}));
            add_result(SignalRegionData(_counters.at("SRHH-14"), 17, {14.4, 2.9}));
            add_result(SignalRegionData(_counters.at("SRHH-15"), 10, {12.7, 2.6}));
            add_result(SignalRegionData(_counters.at("SRHH-16"), 11, {7.3, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHH-17"), 2, {3.92, 0.79}));
            add_result(SignalRegionData(_counters.at("SRHH-18"), 3, {3.26, 0.74}));
            add_result(SignalRegionData(_counters.at("SRHH-19"), 4, {2.6, 2.7}));
            add_result(SignalRegionData(_counters.at("SRHH-20"), 3, {3.02, 0.75}));
            add_result(SignalRegionData(_counters.at("SRHH-21"), 1, {2.8, 0.57}));
            add_result(SignalRegionData(_counters.at("SRHH-22"), 90, {70, 12}));
            add_result(SignalRegionData(_counters.at("SRHH-23"), 40, {35.7, 5.9}));
            add_result(SignalRegionData(_counters.at("SRHH-24"), 2, {3.99, 0.73}));
            add_result(SignalRegionData(_counters.at("SRHH-25"), 0, {2.68, 0.8}));
            add_result(SignalRegionData(_counters.at("SRHH-26"), 9, {9.7, 1.8}));
            add_result(SignalRegionData(_counters.at("SRHH-27"), 8, {7.9, 2.5}));
            add_result(SignalRegionData(_counters.at("SRHH-28"), 1, {2.78, 0.58}));
            add_result(SignalRegionData(_counters.at("SRHH-29"), 1, {1.86, 0.38}));
            add_result(SignalRegionData(_counters.at("SRHH-30"), 1, {2.2, 0.54}));
            add_result(SignalRegionData(_counters.at("SRHH-31"), 5, {1.85, 0.39}));
            add_result(SignalRegionData(_counters.at("SRHH-32"), 0, {1.2, 0.32}));
            add_result(SignalRegionData(_counters.at("SRHH-33"), 3, {1.81, 0.42}));
            add_result(SignalRegionData(_counters.at("SRHH-34"), 1, {1.98, 0.61}));
            add_result(SignalRegionData(_counters.at("SRHH-35"), 2, {1.43, 0.37}));
            add_result(SignalRegionData(_counters.at("SRHH-36"), 2, {4.2, 1.3}));
            add_result(SignalRegionData(_counters.at("SRHH-37"), 4, {3.04, 0.68}));
            add_result(SignalRegionData(_counters.at("SRHH-38"), 1, {0.63, 0.17}));
            add_result(SignalRegionData(_counters.at("SRHH-39"), 0, {0.29, 0.34}));
            add_result(SignalRegionData(_counters.at("SRHH-40"), 3, {0.8, 0.22}));
            add_result(SignalRegionData(_counters.at("SRHH-41"), 19, {13.4, 1.9}));
            add_result(SignalRegionData(_counters.at("SRHH-42"), 8, {8.0, 3.0}));
            add_result(SignalRegionData(_counters.at("SRHH-43"), 3, {3.33, 0.74}));
            add_result(SignalRegionData(_counters.at("SRHH-44"), 1, {0.94, 0.26}));
            add_result(SignalRegionData(_counters.at("SRHH-45"), 3, {2.92, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHH-46"), 3, {1.78, 0.42}));
            add_result(SignalRegionData(_counters.at("SRHH-47"), 5, {1.95, 0.39}));
            add_result(SignalRegionData(_counters.at("SRHH-48"), 3, {1.23, 0.3}));
            add_result(SignalRegionData(_counters.at("SRHH-49"), 0, {1.46, 0.31}));
            add_result(SignalRegionData(_counters.at("SRHH-50"), 0, {0.74, 0.18}));

            // HL
            add_result(SignalRegionData(_counters.at("SRHL-0"), 442, {419, 100}));
            add_result(SignalRegionData(_counters.at("SRHL-1"), 101, {100, 20}));
            add_result(SignalRegionData(_counters.at("SRHL-2"), 6, {9.2, 2.4}));
            add_result(SignalRegionData(_counters.at("SRHL-3"), 13, {15.0, 4.5}));
            add_result(SignalRegionData(_counters.at("SRHL-4"), 14, {7.3, 1.5}));
            add_result(SignalRegionData(_counters.at("SRHL-5"), 5, {4.1, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHL-6"), 0, {1.01, 0.28}));
            add_result(SignalRegionData(_counters.at("SRHL-7"), 346, {300, 82}));
            add_result(SignalRegionData(_counters.at("SRHL-8"), 95, {73, 17}));
            add_result(SignalRegionData(_counters.at("SRHL-9"), 1, {2.3, 0.61}));
            add_result(SignalRegionData(_counters.at("SRHL-10"), 1, {2.24, 0.87}));
            add_result(SignalRegionData(_counters.at("SRHL-11"), 12, {12.8, 3.3}));
            add_result(SignalRegionData(_counters.at("SRHL-12"), 8, {8.9, 2.3}));
            add_result(SignalRegionData(_counters.at("SRHL-13"), 5, {4.5, 1.3}));
            add_result(SignalRegionData(_counters.at("SRHL-14"), 4, {4.7, 1.6}));
            add_result(SignalRegionData(_counters.at("SRHL-15"), 1, {2.3, 1.1}));
            add_result(SignalRegionData(_counters.at("SRHL-16"), 1, {0.73, 0.29}));
            add_result(SignalRegionData(_counters.at("SRHL-17"), 62, {54, 12}));
            add_result(SignalRegionData(_counters.at("SRHL-18"), 24, {23.7, 4.9}));
            add_result(SignalRegionData(_counters.at("SRHL-19"), 2, {0.59, 0.17}));
            add_result(SignalRegionData(_counters.at("SRHL-20"), 1, {0.34, 0.2}));
            add_result(SignalRegionData(_counters.at("SRHL-21"), 9, {5.2, 1.2}));
            add_result(SignalRegionData(_counters.at("SRHL-22"), 6, {4.9, 1.4}));
            add_result(SignalRegionData(_counters.at("SRHL-23"), 0, {0.97, 0.27}));
            add_result(SignalRegionData(_counters.at("SRHL-24"), 0, {1.79, 0.74}));
            add_result(SignalRegionData(_counters.at("SRHL-25"), 1, {1.01, 0.27}));
            add_result(SignalRegionData(_counters.at("SRHL-26"), 1, {1.03, 0.44}));
            add_result(SignalRegionData(_counters.at("SRHL-27"), 0, {1.33, 0.61}));
            add_result(SignalRegionData(_counters.at("SRHL-28"), 3, {2.89, 0.99}));
            add_result(SignalRegionData(_counters.at("SRHL-29"), 2, {2.24, 0.79}));
            add_result(SignalRegionData(_counters.at("SRHL-30"), 1, {0.27, 0.3}));
            add_result(SignalRegionData(_counters.at("SRHL-31"), 1, {0.79, 0.33}));
            add_result(SignalRegionData(_counters.at("SRHL-32"), 0, {0.53, 0.13}));
            add_result(SignalRegionData(_counters.at("SRHL-33"), 6, {6.3, 1.3}));
            add_result(SignalRegionData(_counters.at("SRHL-34"), 3, {2.92, 0.87}));
            add_result(SignalRegionData(_counters.at("SRHL-35"), 3, {0.51, 0.15}));
            add_result(SignalRegionData(_counters.at("SRHL-36"), 0, {0.15, 0.07}));
            add_result(SignalRegionData(_counters.at("SRHL-37"), 3, {1.07, 0.33}));
            add_result(SignalRegionData(_counters.at("SRHL-38"), 0, {0.81, 0.47}));
            add_result(SignalRegionData(_counters.at("SRHL-39"), 4, {1.54, 0.5}));
            add_result(SignalRegionData(_counters.at("SRHL-40"), 1, {1.23, 0.53}));

            // LL
            add_result(SignalRegionData(_counters.at("SRLL-0"), 12, {12.0, 3.9}));
            add_result(SignalRegionData(_counters.at("SRLL-1"), 3, {1.88, 0.62}));
            add_result(SignalRegionData(_counters.at("SRLL-2"), 17, {15.5, 4.7}));
            add_result(SignalRegionData(_counters.at("SRLL-3"), 4, {1.42, 0.69}));
            add_result(SignalRegionData(_counters.at("SRLL-4"), 5, {4.2, 1.4}));
            add_result(SignalRegionData(_counters.at("SRLL-5"), 2, {0.84, 0.48}));
            add_result(SignalRegionData(_counters.at("SRLL-6"), 0, {0.95, 0.52}));
            add_result(SignalRegionData(_counters.at("SRLL-7"), 0, {0.09, 0.07}));

            return;
        }

    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2SSLEP_Stop_36invfb)

    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_CMS_13TeV_2SSLEP_Stop_inclusive_36invfb : public Analysis_CMS_13TeV_2SSLEP_Stop_36invfb {

    public:
      Analysis_CMS_13TeV_2SSLEP_Stop_inclusive_36invfb() {
        set_analysis_name("CMS_13TeV_2SSLEP_Stop_inclusive_36invfb");
      }

        virtual void collect_results() {

            // inc
            add_result(SignalRegionData(_counters.at("SRinc-0"), 10, {4.0, 0.79}));
            add_result(SignalRegionData(_counters.at("SRinc-1"), 4, {3.63, 0.71}));
            add_result(SignalRegionData(_counters.at("SRinc-2"), 4, {3.72, 0.83}));
            add_result(SignalRegionData(_counters.at("SRinc-3"), 6, {3.32, 0.81}));
            add_result(SignalRegionData(_counters.at("SRinc-4"), 2, {1.68, 0.44}));
            add_result(SignalRegionData(_counters.at("SRinc-5"), 7, {3.82, 0.76}));
            add_result(SignalRegionData(_counters.at("SRinc-6"), 10, {5.6, 1.1}));
            add_result(SignalRegionData(_counters.at("SRinc-7"), 9, {5.8, 1.3}));
            add_result(SignalRegionData(_counters.at("SRinc-8"), 9, {10.1, 2.7}));
            add_result(SignalRegionData(_counters.at("SRinc-9"), 22, {15.2, 3.5}));
            add_result(SignalRegionData(_counters.at("SRinc-10"), 17, {13.3, 3.4}));
            add_result(SignalRegionData(_counters.at("SRinc-11"), 3, {3.6, 2.5}));
            add_result(SignalRegionData(_counters.at("SRinc-12"), 10, {4.9, 2.9}));
            add_result(SignalRegionData(_counters.at("SRinc-13"), 6, {7.3, 5.5}));
            add_result(SignalRegionData(_counters.at("SRinc-14"), 0, {1.06, 0.99}));

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2SSLEP_Stop_inclusive_36invfb)

    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_CMS_13TeV_2SSLEP_Stop_exclusive_36invfb : public Analysis_CMS_13TeV_2SSLEP_Stop_36invfb {

    public:
      Analysis_CMS_13TeV_2SSLEP_Stop_exclusive_36invfb() {
        set_analysis_name("CMS_13TeV_2SSLEP_Stop_exclusive_36invfb");
      }

        virtual void collect_results() {

            // exc
            add_result(SignalRegionData(_counters.at("SRexc-0"), 685, {700, 130}));
            add_result(SignalRegionData(_counters.at("SRexc-1"), 11, {11.0, 2.2}));
            add_result(SignalRegionData(_counters.at("SRexc-2"), 482, {477, 120}));
            add_result(SignalRegionData(_counters.at("SRexc-3"), 8, {8.4, 3.5}));
            add_result(SignalRegionData(_counters.at("SRexc-4"), 152, {137, 25}));
            add_result(SignalRegionData(_counters.at("SRexc-5"), 8, {4.9, 1.2}));
            add_result(SignalRegionData(_counters.at("SRexc-6"), 10, {11.6, 3.1}));
            add_result(SignalRegionData(_counters.at("SRexc-7"), 3, {0.8, 0.24}));
            add_result(SignalRegionData(_counters.at("SRexc-8"), 31, {25.7, 5.4}));
            add_result(SignalRegionData(_counters.at("SRexc-9"), 14, {10.1, 2.2}));
            add_result(SignalRegionData(_counters.at("SRexc-10"), 1167, {1070, 250}));
            add_result(SignalRegionData(_counters.at("SRexc-11"), 1, {1.33, 0.46}));
            add_result(SignalRegionData(_counters.at("SRexc-12"), 12, {9.9, 2.5}));
            add_result(SignalRegionData(_counters.at("SRexc-13"), 8, {4.7, 1.8}));
            add_result(SignalRegionData(_counters.at("SRexc-14"), 43, {37, 12}));

            static const vector< vector<double> > BKGCOV = {
                {17559.1, 111.4, 13059.1, 136.0, 1982.8, 34.0, 187.1, 14.8, 260.9, 80.2, 26183.7, 21.0, 134.9, 78.2, 987.5},
                {111.4, 3.8, 85.1, 1.9, 20.0, 0.6, 2.5, 0.2, 3.9, 1.7, 186.6, 0.2, 1.3, 0.8, 6.6},
                {13059.1, 85.1, 12489.9, 102.2, 1847.0, 32.4, 158.8, 11.1, 179.7, 58.6, 23663.6, 19.6, 123.0, 63.8, 881.1},
                {136.0, 1.9, 102.2, 10.4, 28.8, 1.1, 3.8, 0.3, 6.3, 2.3, 210.4, 0.3, 1.9, 1.4, 8.5},
                {1982.8, 20.0, 1847.0, 28.8, 525.1, 11.2, 36.6, 2.5, 43.8, 18.3, 3573.7, 3.7, 24.4, 12.8, 139.8},
                {34.0, 0.6, 32.4, 1.1, 11.2, 1.1, 1.3, 0.1, 1.8, 0.7, 60.2, 0.1, 0.7, 0.4, 2.4},
                {187.1, 2.5, 158.8, 3.8, 36.6, 1.3, 9.1, 0.3, 6.3, 2.4, 320.9, 0.3, 2.3, 1.4, 12.5},
                {14.8, 0.2, 11.1, 0.3, 2.5, 0.1, 0.3, 0.1, 0.5, 0.2, 21.4, 0.0, 0.2, 0.1, 0.8},
                {260.9, 3.9, 179.7, 6.3, 43.8, 1.8, 6.3, 0.5, 25.7, 3.6, 345.5, 0.4, 2.9, 2.3, 14.5},
                {80.2, 1.7, 58.6, 2.3, 18.3, 0.7, 2.4, 0.2, 3.6, 4.0, 126.8, 0.2, 1.2, 0.9, 4.2},
                {26183.7, 186.6, 23663.6, 210.4, 3573.7, 60.2, 320.9, 21.4, 345.5, 126.8, 60200.4, 45.8, 307.4, 170.1, 1998.6},
                {21.0, 0.2, 19.6, 0.3, 3.7, 0.1, 0.3, 0.0, 0.4, 0.2, 45.8, 0.2, 0.3, 0.1, 1.7},
                {134.9, 1.3, 123.0, 1.9, 24.4, 0.7, 2.3, 0.2, 2.9, 1.2, 307.4, 0.3, 6.2, 1.1, 11.2},
                {78.2, 0.8, 63.8, 1.4, 12.8, 0.4, 1.4, 0.1, 2.3, 0.9, 170.1, 0.1, 1.1, 3.3, 6.0},
                {987.5, 6.6, 881.1, 8.5, 139.8, 2.4, 12.5, 0.8, 14.5, 4.2, 1998.6, 1.7, 11.2, 6.0, 135.5}
            };

            set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2SSLEP_Stop_exclusive_36invfb)

  }
}
