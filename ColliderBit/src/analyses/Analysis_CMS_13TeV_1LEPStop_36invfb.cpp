#include <fstream>
#include "gambit/ColliderBit/topness.h"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

using namespace std;

/* The CMS 0 lepton direct stop analysis (35.9fb^-1).

   Based on: https://arxiv.org/pdf/1706.04402.pdf
             http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-051/#AddTab

   By Yang Zhang

   Known errors:
        1. Modified topness is calculated with all b jets (not b-tagged)
           and up to three none-b jets, instead of up to three jets with
           highest CSV discriminator values.
   Known features:

*/

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_1LEPStop_36invfb : public Analysis {
    private:

        // Numbers passing cuts
        std::map<string, EventCounter> _counters = {
            // Aggregate SRs
            {"aggregateSR0", EventCounter("aggregateSR0")},
            {"aggregateSR1", EventCounter("aggregateSR1")},
            {"aggregateSR2", EventCounter("aggregateSR2")},
            {"aggregateSR3", EventCounter("aggregateSR3")},
            {"aggregateSR4", EventCounter("aggregateSR4")},
            {"aggregateSR5", EventCounter("aggregateSR5")},
            // Fine-binned SRs
            // {"SR0", EventCounter("SR0")},
            // {"SR1", EventCounter("SR1")},
            // {"SR2", EventCounter("SR2")},
            // {"SR3", EventCounter("SR3")},
            // {"SR4", EventCounter("SR4")},
            // {"SR5", EventCounter("SR5")},
            // {"SR6", EventCounter("SR6")},
            // {"SR7", EventCounter("SR7")},
            // {"SR8", EventCounter("SR8")},
            // {"SR9", EventCounter("SR9")},
            // {"SR10", EventCounter("SR10")},
            // {"SR11", EventCounter("SR11")},
            // {"SR12", EventCounter("SR12")},
            // {"SR13", EventCounter("SR13")},
            // {"SR14", EventCounter("SR14")},
            // {"SR15", EventCounter("SR15")},
            // {"SR16", EventCounter("SR16")},
            // {"SR17", EventCounter("SR17")},
            // {"SR18", EventCounter("SR18")},
            // {"SR19", EventCounter("SR19")},
            // {"SR20", EventCounter("SR20")},
            // {"SR21", EventCounter("SR21")},
            // {"SR22", EventCounter("SR22")},
            // {"SR23", EventCounter("SR23")},
            // {"SR24", EventCounter("SR24")},
            // {"SR25", EventCounter("SR25")},
            // {"SR26", EventCounter("SR26")},
            // {"SR27", EventCounter("SR27")},
            // {"SR28", EventCounter("SR28")},
            // {"SR29", EventCounter("SR29")},
            // {"SR30", EventCounter("SR30")},
        };

        static const size_t NUM_aggregateSR = 6;

        // Cut Flow
        Cutflow _cutflow;

        // Jet overlap removal
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

    public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_CMS_13TeV_1LEPStop_36invfb():
            _cutflow("CMS 0-lep stop 13 TeV", {
            "Trigger",
            "M_{T}>150",
            "N_b>=1",
            "N_l<2",
            "N_tau==0",
            "deltaPhi_j12>0.8",
            "MET>250",
            "**t_mod>0",
            "**t_mod>10",
            "**Mlb<175",
            "**Mlb>175"}) {

            set_analysis_name("CMS_13TeV_1LEPStop_36invfb");
            set_luminosity(35.9);
        }

        void run(const HEPUtils::Event* event) {

            _cutflow.fillinit();

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Online  trigger
            if (met<120) return;

            // Electron objects
            vector<const HEPUtils::Particle*> baselineElectrons;
            for (const HEPUtils::Particle* electron : event->electrons())
                if (electron->pT() > 5. && electron->abseta() < 2.4 ) baselineElectrons.push_back(electron);

            // Apply electron efficiency
            CMS::applyElectronEff(baselineElectrons);

            // Muon objects
            vector<const HEPUtils::Particle*> baselineMuons;
            for (const HEPUtils::Particle* muon : event->muons())
                if (muon->pT() > 5. && muon->abseta() < 2.4 ) baselineMuons.push_back(muon);

            // Apply muon efficiency
            CMS::applyMuonEff(baselineMuons);

            // Jets
            vector<const HEPUtils::Jet*> baselineJets;
            vector<const HEPUtils::Jet*> fullJets;
            for (const HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 30. && jet->abseta() < 2.4) baselineJets.push_back(jet);
                if (jet->abseta() < 5.0) fullJets.push_back(jet);
            }

            // Electron isolation
            vector<const HEPUtils::Particle*> Electrons;
            double Rrel;
            for (const HEPUtils::Particle* e : baselineElectrons) {
                if (e->pT() < 50.) Rrel=0.2;
                else if (e->pT() < 200.) Rrel=10./e->pT();
                else Rrel=0.05;
                double sumpt = -e->pT();
                for (const HEPUtils::Jet* j : fullJets)
                    if (e->mom().deltaR_eta(j->mom()) < Rrel) sumpt += j->pT();
                if (sumpt/e->pT() < 0.1) Electrons.push_back(e);
            }

            // Muon isolation
            vector<const HEPUtils::Particle*> Muons;
            for (const HEPUtils::Particle* mu : baselineMuons) {
                if (mu->pT() < 50.) Rrel=0.2;
                else if (mu->pT() < 200.) Rrel=10./mu->pT();
                else Rrel=0.05;
                double sumpt = -mu->pT();
                for (const HEPUtils::Jet* j : fullJets)
                    if (mu->mom().deltaR_eta(j->mom()) < Rrel) sumpt += j->pT();
                if (sumpt/mu->pT() < 0.2) Muons.push_back(mu);
            }

            // Selected lepton
            vector<const HEPUtils::Particle*> Leptons;
            for (const HEPUtils::Particle* e : Electrons) {
                if (e->pT() > 20. && e->abseta() < 1.442 ) Leptons.push_back(e);
            }
            for (const HEPUtils::Particle* mu : Muons) {
                if (mu->pT() > 20. && mu->abseta() < 2.4 ) Leptons.push_back(mu);
            }

            JetLeptonOverlapRemoval(baselineJets,Leptons,0.4);

            // Online trigger
            if (baselineJets.size()<2) return;
            if (Leptons.size()!=1) return;
            HEPUtils::P4 HTmiss(0,0,0,0);
            for (const HEPUtils::Jet* j : baselineJets) HTmiss += j->mom();
            bool lep_trigger=false;
            for (const HEPUtils::Particle* e : Electrons) {
                if ((HTmiss + e->mom()).pT()>120 ) lep_trigger=true;
                if (e->pT() > 25. && e->abseta() < 2.1 ) lep_trigger=true;
            }
            for (const HEPUtils::Particle* mu : Muons) {
                if ((HTmiss + mu->mom()).pT()>120 ) lep_trigger=true;
                if (mu->pT() > 22. && mu->abseta() < 2.4 ) lep_trigger=true;
            }
            if(!lep_trigger) return;
            _cutflow.fill(1); //"Trigger"

            // MT of lepton-MET system
            double MT=sqrt( 2.*Leptons.at(0)->pT()*met*(1.-std::cos(Leptons.at(0)->mom().deltaPhi(ptot))) );
            if(MT<150) return;
            _cutflow.fill(2); //"M_{T}>150"

            // b-tagged jets
            vector<const HEPUtils::Jet*> bJets;
            vector<const HEPUtils::Jet*> nobJets;
            vector<const HEPUtils::Jet*> mediumbJets;
            int N_tight_bJets=0;
            bool leadjet_nob = true;
            const std::vector<double>  a = {0,10.};
            const std::vector<double>  b = {0,10000.};
            const std::vector<double>  c1 = {0.60}; // medium
            const std::vector<double>  c2 = {0.35}; // tight
            HEPUtils::BinnedFn2D<double> _eff2d_1(a,b,c1);
            HEPUtils::BinnedFn2D<double> _eff2d_2(a,b,c2);
            for (size_t ii = 0; ii < baselineJets.size(); ii++) {
                if (baselineJets.at(ii)->btag())
                    bJets.push_back(baselineJets.at(ii));
                else
                    nobJets.push_back(baselineJets.at(ii));
                bool hasTag=has_tag(_eff2d_1, baselineJets.at(ii)->abseta(), baselineJets.at(ii)->pT());
                if(baselineJets.at(ii)->btag() && hasTag ) {
                    mediumbJets.push_back(baselineJets.at(ii));
                    if (ii==0) leadjet_nob =false;
                }
                hasTag=has_tag(_eff2d_2, baselineJets.at(ii)->abseta(), baselineJets.at(ii)->pT());
                if(baselineJets.at(ii)->btag() && hasTag )
                    N_tight_bJets++;
            }

            if(mediumbJets.size()<1) return;
            _cutflow.fill(3); //"N_b>=1"

            if(Electrons.size()+Muons.size()>1) return;
            _cutflow.fill(4); //"N_l<2"

            if(event->taus().size()>0) return;
            _cutflow.fill(5); //"N_tau==0"

            // Azimuthal angle between MET and two leading jets
            double deltaPhi_j1=baselineJets.at(0)->mom().deltaPhi(ptot);
            double deltaPhi_j2=baselineJets.at(1)->mom().deltaPhi(ptot);
            double deltaPhi_j12 = deltaPhi_j1<deltaPhi_j2 ? deltaPhi_j1:deltaPhi_j2;
            if (deltaPhi_j12<0.8) return;
            _cutflow.fill(6); //"deltaPhi_j12>0.8"

            if (met<250) return;
            _cutflow.fill(7); //"MET>250"

            // *MODIFIED* topness
            // 1612.03877 & 1212.4495
            const double sigmat=15.;
            const double sigmaW=5.;
            double pl[]={Leptons.at(0)->mom().px(), Leptons.at(0)->mom().py(), Leptons.at(0)->mom().pz(), Leptons.at(0)->E()};
            double MET[]={ptot.px(), ptot.py(), 0., 0.};
            double tmod=exp(9999.);
            // The experimental report consider all possible pairings of b jet candidates
            // with up to three jets with highest CSV discriminator values.
            int n_b=0;
            for (const HEPUtils::Jet* bj :bJets) {
                n_b++;
                double pb1[]={bj->mom().px(), bj->mom().py(), bj->mom().pz(), bj->E()};
                double tmod_tem=log(topnesscompute(pb1, pl, MET, sigmat, sigmaW));
                if(tmod>tmod_tem) tmod=tmod_tem;
            }
            // up to three jets
            for (const HEPUtils::Jet* nobj :nobJets) {
                if(n_b>3) break;
                n_b++;
                double pb1[]={nobj->mom().px(), nobj->mom().py(), nobj->mom().pz(), nobj->E()};
                double tmod_tem=log(topnesscompute(pb1, pl, MET, sigmat, sigmaW));
                if(tmod>tmod_tem) tmod=tmod_tem;
            }

            if (tmod>0 ) _cutflow.fill(8); //"**t_mod>0"
            if (tmod>10) _cutflow.fill(9); //"**t_mod>10"


            // Mlb
            double deltaRlb=9999.;
            double Mlb;
            for (const HEPUtils::Jet* bj :mediumbJets) {
                if (deltaRlb > bj->mom().deltaR_eta(Leptons.at(0)->mom())){
                    deltaRlb = bj->mom().deltaR_eta(Leptons.at(0)->mom());
                    Mlb= (bj->mom()+Leptons.at(0)->mom()).m();
                }
            }

            if (Mlb<175) _cutflow.fill(10); //"**Mlb<175"
            if (Mlb>175 and N_tight_bJets>0) _cutflow.fill(11); //"**Mlb>175"

            /*********************************************************/
            /*                                                       */
            /* SIGNAL REGIONS                                        */
            /*                                                       */
            /*********************************************************/

//            bool MET_250_350= met>250 and met<350;
//            bool MET_350_450= met>350 and met<450;
//            bool MET_450_600= met>450 and met<600;
//            bool MET_600= met>=600;
//            bool MET_250_450= met>250 and met<450;
//            bool MET_450_550= met>450 and met<550;
//            bool MET_550_650= met>550 and met<650;
//            bool MET_650= met>=650;
//            bool MET_550= met>=550;
//            bool MET_350_550= met>350 and met<550;
//            bool MET_450= met>=450;

//            if (baselineJets.size()<=3){
//                if(tmod>10){
//                    if(Mlb<175){
//                        if( MET_250_350) _counters.at("SR0").add_event(event);
//                        if( MET_350_450) _counters.at("SR1").add_event(event);
//                        if( MET_450_600) _counters.at("SR2").add_event(event);
//                        if( MET_600    ) _counters.at("SR3").add_event(event);
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450) _counters.at("SR4").add_event(event);
//                        if( MET_450_600) _counters.at("SR5").add_event(event);
//                        if( MET_600    ) _counters.at("SR6").add_event(event);
//                      }
//                    }
//                }
//            }
//            else{ // N_j>=4
//                if(tmod<=0){
//                    if(Mlb<175){
//                        if( MET_250_350) _counters.at("SR7").add_event(event);
//                        if( MET_350_450) _counters.at("SR8").add_event(event);
//                        if( MET_450_550) _counters.at("SR9").add_event(event);
//                        if( MET_550_650) _counters.at("SR10").add_event(event);
//                        if( MET_650    ) _counters.at("SR11").add_event(event);
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_350) _counters.at("SR12").add_event(event);
//                        if( MET_350_450) _counters.at("SR13").add_event(event);
//                        if( MET_450_550) _counters.at("SR14").add_event(event);
//                        if( MET_550    ) _counters.at("SR15").add_event(event);
//                      }
//                    }
//                }else if (tmod<=10){
//                    if(Mlb<175){
//                        if( MET_250_350) _counters.at("SR16").add_event(event);
//                        if( MET_350_550) _counters.at("SR17").add_event(event);
//                        if( MET_550    ) _counters.at("SR18").add_event(event);
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450) _counters.at("SR19").add_event(event);
//                        if( MET_450    ) _counters.at("SR20").add_event(event);
//                      }
//                    }
//                }else{ //tmod>10
//                    if(Mlb<175){
//                        if( MET_250_350) _counters.at("SR21").add_event(event);
//                        if( MET_350_450) _counters.at("SR22").add_event(event);
//                        if( MET_450_600) _counters.at("SR23").add_event(event);
//                        if( MET_600    ) _counters.at("SR24").add_event(event);
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450) _counters.at("SR25").add_event(event);
//                        if( MET_450    ) _counters.at("SR26").add_event(event);
//                      }
//                    }
//                }
//            }
//
//            // compressed region
//            if(baselineJets.size()>=5 and leadjet_nob and deltaPhi_j12 >0.5 and Leptons.at(0)->pT() < 150 and Leptons.at(0)->mom().deltaPhi(ptot)<2. ){
//                if( MET_250_350) _counters.at("SR27").add_event(event);
//                if( MET_350_450) _counters.at("SR28").add_event(event);
//                if( MET_450_550) _counters.at("SR29").add_event(event);
//                if( MET_550    ) _counters.at("SR30").add_event(event);
//            }

            // aggregate signal region
            if (baselineJets.size()<=3 and tmod>10              and met>=600) _counters.at("aggregateSR0").add_event(event);
            if (baselineJets.size()>=4 and tmod<=0 and Mlb<=175 and met>=550) _counters.at("aggregateSR1").add_event(event);
            if (baselineJets.size()>=4 and tmod>10 and Mlb<=175 and met>=450) _counters.at("aggregateSR2").add_event(event);
            if (baselineJets.size()>=4 and tmod<=0 and Mlb> 175 and met>=450) _counters.at("aggregateSR3").add_event(event);
            if (baselineJets.size()>=4 and tmod> 0 and Mlb> 175 and met>=450) _counters.at("aggregateSR4").add_event(event);
            if(baselineJets.size()>=5 and leadjet_nob and deltaPhi_j12 >0.5 and Leptons.at(0)->pT() < 150 and Leptons.at(0)->mom().deltaPhi(ptot)<2. ){
                if( met>=450 ) _counters.at("aggregateSR5").add_event(event);
            }
        return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_1LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_1LEPStop_36invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results() {

            // cout << _cutflow << endl;

            // aggregate signal regions
            add_result(SignalRegionData(_counters.at("aggregateSR0"), 4., {3.4, 0.9}));
            add_result(SignalRegionData(_counters.at("aggregateSR1"), 8., {10.7, 3.2}));
            add_result(SignalRegionData(_counters.at("aggregateSR2"), 3., {8.8, 1.8}));
            add_result(SignalRegionData(_counters.at("aggregateSR3"), 3., {5.3, 1.5}));
            add_result(SignalRegionData(_counters.at("aggregateSR4"), 2., {1.9, 0.5}));
            add_result(SignalRegionData(_counters.at("aggregateSR5"), 4., {8.6, 2.5}));

            // binned signal region
            // add_result(SignalRegionData(_counters.at("SR0"), 72., {65.8, 6.8}));
            // add_result(SignalRegionData(_counters.at("SR1"), 24., {20.5, 2.9}));
            // add_result(SignalRegionData(_counters.at("SR2"), 6., {6.4, 1.3}));
            // add_result(SignalRegionData(_counters.at("SR3"), 2., {2.4, 0.8}));
            // add_result(SignalRegionData(_counters.at("SR4"), 6., {8.9, 2.4}));
            // add_result(SignalRegionData(_counters.at("SR5"), 3., {1.9, 0.7}));
            // add_result(SignalRegionData(_counters.at("SR6"), 2., {1., 0.5}));
            // add_result(SignalRegionData(_counters.at("SR7"), 343., {383., 34.}));
            // add_result(SignalRegionData(_counters.at("SR8"), 68., {75.5, 8.5}));
            // add_result(SignalRegionData(_counters.at("SR9"), 13., {15.0, 2.9}));
            // add_result(SignalRegionData(_counters.at("SR10"), 6., {4.1, 1.5}));
            // add_result(SignalRegionData(_counters.at("SR11"), 2., {6.6, 2.9}));
            // add_result(SignalRegionData(_counters.at("SR12"), 38., {39.7, 6.2}));
            // add_result(SignalRegionData(_counters.at("SR13"), 8., {13.7, 2.8}));
            // add_result(SignalRegionData(_counters.at("SR14"), 2., {3.1, 1.1}));
            // add_result(SignalRegionData(_counters.at("SR15"), 1., {2.2, 1.0}));
            // add_result(SignalRegionData(_counters.at("SR16"), 65., {58.7, 7.2}));
            // add_result(SignalRegionData(_counters.at("SR17"), 23., {14.7, 2.4}));
            // add_result(SignalRegionData(_counters.at("SR18"), 1., {1.5, 0.6}));
            // add_result(SignalRegionData(_counters.at("SR19"), 9., {8.9, 1.9}));
            // add_result(SignalRegionData(_counters.at("SR20"), 0., {0.6, 0.2}));
            // add_result(SignalRegionData(_counters.at("SR21"), 12., {14.3, 2.7}));
            // add_result(SignalRegionData(_counters.at("SR22"), 9., {10., 2.1}));
            // add_result(SignalRegionData(_counters.at("SR23"), 3., {6.3, 1.5}));
            // add_result(SignalRegionData(_counters.at("SR24"), 0., {2.4, 1.0}));
            // add_result(SignalRegionData(_counters.at("SR25"), 0., {1.9, 0.7}));
            // add_result(SignalRegionData(_counters.at("SR26"), 2., {1.3, 0.4}));
            // add_result(SignalRegionData(_counters.at("SR27"), 72., {82., 11.}));
            // add_result(SignalRegionData(_counters.at("SR28"), 30., {18.9, 3.7}));
            // add_result(SignalRegionData(_counters.at("SR29"), 2., {3.7, 1.4}));
            // add_result(SignalRegionData(_counters.at("SR30"), 2., {4.8, 2.0}));

            return;
        }

    protected:
        void analysis_specific_reset() {
            for (auto& pair : _counters) { pair.second.reset(); }
        }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_1LEPStop_36invfb)


  }
}
