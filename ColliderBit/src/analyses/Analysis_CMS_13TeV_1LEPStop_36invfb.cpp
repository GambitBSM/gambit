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
//        static const size_t NUM_SR = 31;
//        double _SR[NUM_SR];

        static const size_t NUM_aggregateSR = 6;
        double _aggregateSR[NUM_aggregateSR];

        // Cut Flow
        Cutflow _cutflow;

        // Jet overlap removal
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
//            for (size_t i = 0; i < NUM_SR; ++i) _SR[i] = 0;
            for (size_t i = 0; i < NUM_aggregateSR; ++i) _aggregateSR[i] = 0;
        }

        void run(const HEPUtils::Event* event) {

            _cutflow.fillinit();

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Online  trigger
            if (met<120) return;

            // Electron objects
            vector<HEPUtils::Particle*> baselineElectrons;
            for (HEPUtils::Particle* electron : event->electrons())
                if (electron->pT() > 5. && electron->abseta() < 2.4 ) baselineElectrons.push_back(electron);

            // Apply electron efficiency
            CMS::applyElectronEff(baselineElectrons);

            // Muon objects
            vector<HEPUtils::Particle*> baselineMuons;
            for (HEPUtils::Particle* muon : event->muons())
                if (muon->pT() > 5. && muon->abseta() < 2.4 ) baselineMuons.push_back(muon);

            // Apply muon efficiency
            CMS::applyMuonEff(baselineMuons);

            // Jets
            vector<HEPUtils::Jet*> baselineJets;
            vector<HEPUtils::Jet*> fullJets;
            for (HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 30. && jet->abseta() < 2.4) baselineJets.push_back(jet);
                if (jet->abseta() < 5.0) fullJets.push_back(jet);
            }

            // Electron isolation
            vector<HEPUtils::Particle*> Electrons;
            double Rrel;
            for (HEPUtils::Particle* e : baselineElectrons) {
                if (e->pT() < 50.) Rrel=0.2;
                else if (e->pT() < 200.) Rrel=10./e->pT();
                else Rrel=0.05;
                double sumpt = -e->pT();
                for (HEPUtils::Jet* j : fullJets)
                    if (e->mom().deltaR_eta(j->mom()) < Rrel) sumpt += j->pT();
                if (sumpt/e->pT() < 0.1) Electrons.push_back(e);
            }

            // Muon isolation
            vector<HEPUtils::Particle*> Muons;
            for (HEPUtils::Particle* mu : baselineMuons) {
                if (mu->pT() < 50.) Rrel=0.2;
                else if (mu->pT() < 200.) Rrel=10./mu->pT();
                else Rrel=0.05;
                double sumpt = -mu->pT();
                for (HEPUtils::Jet* j : fullJets)
                    if (mu->mom().deltaR_eta(j->mom()) < Rrel) sumpt += j->pT();
                if (sumpt/mu->pT() < 0.2) Muons.push_back(mu);
            }

            // Selected lepton
            vector<HEPUtils::Particle*> Leptons;
            for (HEPUtils::Particle* e : Electrons) {
                if (e->pT() > 20. && e->abseta() < 1.442 ) Leptons.push_back(e);
            }
            for (HEPUtils::Particle* mu : Muons) {
                if (mu->pT() > 20. && mu->abseta() < 2.4 ) Leptons.push_back(mu);
            }

            JetLeptonOverlapRemoval(baselineJets,Leptons,0.4);

            // Online trigger
            if (baselineJets.size()<2) return;
            if (Leptons.size()!=1) return;
            HEPUtils::P4 HTmiss(0,0,0,0);
            for (HEPUtils::Jet* j : baselineJets) HTmiss += j->mom();
            bool lep_trigger=false;
            for (HEPUtils::Particle* e : Electrons) {
                if ((HTmiss + e->mom()).pT()>120 ) lep_trigger=true;
                if (e->pT() > 25. && e->abseta() < 2.1 ) lep_trigger=true;
            }
            for (HEPUtils::Particle* mu : Muons) {
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
            vector<HEPUtils::Jet*> bJets;
            vector<HEPUtils::Jet*> nobJets;
            vector<HEPUtils::Jet*> mediumbJets;
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
                bool hasTag=has_tag(_eff2d_1, baselineJets.at(ii)->eta(), baselineJets.at(ii)->pT());
                if(baselineJets.at(ii)->btag() && hasTag ) {
                    mediumbJets.push_back(baselineJets.at(ii));
                    if (ii==0) leadjet_nob =false;
                }
                hasTag=has_tag(_eff2d_2, baselineJets.at(ii)->eta(), baselineJets.at(ii)->pT());
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
            for (HEPUtils::Jet* bj :bJets) {
                n_b++;
                double pb1[]={bj->mom().px(), bj->mom().py(), bj->mom().pz(), bj->E()};
                double tmod_tem=log(topnesscompute(pb1, pl, MET, sigmat, sigmaW));
                if(tmod>tmod_tem) tmod=tmod_tem;
            }
            // up to three jets
            for (HEPUtils::Jet* nobj :nobJets) {
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
            for (HEPUtils::Jet* bj :mediumbJets) {
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
//                        if( MET_250_350)_SR[0]+=1;
//                        if( MET_350_450)_SR[1]+=1;
//                        if( MET_450_600)_SR[2]+=1;
//                        if( MET_600    )_SR[3]+=1;
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450)_SR[4]+=1;
//                        if( MET_450_600)_SR[5]+=1;
//                        if( MET_600    )_SR[6]+=1;
//                      }
//                    }
//                }
//            }
//            else{ // N_j>=4
//                if(tmod<=0){
//                    if(Mlb<175){
//                        if( MET_250_350)_SR[7]+=1;
//                        if( MET_350_450)_SR[8]+=1;
//                        if( MET_450_550)_SR[9]+=1;
//                        if( MET_550_650)_SR[10]+=1;
//                        if( MET_650    )_SR[11]+=1;
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_350)_SR[12]+=1;
//                        if( MET_350_450)_SR[13]+=1;
//                        if( MET_450_550)_SR[14]+=1;
//                        if( MET_550    )_SR[15]+=1;
//                      }
//                    }
//                }else if (tmod<=10){
//                    if(Mlb<175){
//                        if( MET_250_350)_SR[16]+=1;
//                        if( MET_350_550)_SR[17]+=1;
//                        if( MET_550    )_SR[18]+=1;
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450)_SR[19]+=1;
//                        if( MET_450    )_SR[20]+=1;
//                      }
//                    }
//                }else{ //tmod>10
//                    if(Mlb<175){
//                        if( MET_250_350)_SR[21]+=1;
//                        if( MET_350_450)_SR[22]+=1;
//                        if( MET_450_600)_SR[23]+=1;
//                        if( MET_600    )_SR[24]+=1;
//                    }else{//Mlb>175
//                      if(N_tight_bJets>0){
//                        if( MET_250_450)_SR[25]+=1;
//                        if( MET_450    )_SR[26]+=1;
//                      }
//                    }
//                }
//            }
//
//            // compressed region
//            if(baselineJets.size()>=5 and leadjet_nob and deltaPhi_j12 >0.5 and Leptons.at(0)->pT() < 150 and Leptons.at(0)->mom().deltaPhi(ptot)<2. ){
//                if( MET_250_350)_SR[27]+=1;
//                if( MET_350_450)_SR[28]+=1;
//                if( MET_450_550)_SR[29]+=1;
//                if( MET_550    )_SR[30]+=1;
//            }

            // aggregate signal region
            if (baselineJets.size()<=3 and tmod>10              and met>=600) _aggregateSR[0]+=1;
            if (baselineJets.size()>=4 and tmod<=0 and Mlb<=175 and met>=550) _aggregateSR[1]+=1;
            if (baselineJets.size()>=4 and tmod>10 and Mlb<=175 and met>=450) _aggregateSR[2]+=1;
            if (baselineJets.size()>=4 and tmod<=0 and Mlb> 175 and met>=450) _aggregateSR[3]+=1;
            if (baselineJets.size()>=4 and tmod> 0 and Mlb> 175 and met>=450) _aggregateSR[4]+=1;
            if(baselineJets.size()>=5 and leadjet_nob and deltaPhi_j12 >0.5 and Leptons.at(0)->pT() < 150 and Leptons.at(0)->mom().deltaPhi(ptot)<2. ){
                if( met>=450 ) _aggregateSR[5]+=1;
            }
        return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_1LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_1LEPStop_36invfb*>(other);

//            for (size_t i = 0; i < NUM_SR; ++i)
//                _SR[i] += specificOther->_SR[i];

            for (size_t i = 0; i < NUM_aggregateSR; ++i)
                _aggregateSR[i] += specificOther->_aggregateSR[i];
        }


        void collect_results() {

            // cout << _cutflow << endl;

//            // binned signal region
//            static const double OBSNUM[NUM_SR] = {72.,      24.,    6.,     2.,     6.,     3.,     2.,
//                                                  343.,     68.,    13.,    6.,     2.,     38.,    8.,     2.,     1.,
//                                                  65.,      23.,    1.,     9.,     0.,     12.,    9.,     3.,     0.,
//                                                  0.,       2.,     72.,    30.,    2.,     2.};
//            static const double BKGNUM[NUM_SR] = {65.8,     20.5,   6.4,    2.4,    8.9,    1.9,    1.,
//                                                  383.,     75.5,   15.0,   4.1,    6.6,    39.7,   13.7,   3.1,    2.2,
//                                                  58.7,     14.7,   1.5,    8.9,    0.6,    14.3,   10.,    6.3,    2.4,
//                                                  1.9,      1.3,    82.,    18.9,   3.7,    4.8};
//            static const double BKGERR[NUM_SR] = {6.8,      2.9,    1.3,    0.8,    2.4,    0.7,    0.5,
//                                                  34.,      8.5,    2.9,    1.5,    2.9,    6.2,    2.8,    1.1,    1.0,
//                                                  7.2,      2.4,    0.6,    1.9,    0.2,    2.7,    2.1,    1.5,    1.0,
//                                                  0.7,      0.4,    11.,    3.7,    1.4,    2.0};

//            for (size_t ibin = 0; ibin < NUM_SR; ++ibin) {
//                stringstream ss; ss << "sr-" << ibin;
//                add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {_SR[ibin],  0.}, {BKGNUM[ibin], BKGERR[ibin]}));
//                //cout << ss.str() << ":  "<< _SR[ibin] << endl;
//            }

            // aggregate signal region
            static const double aggregateOBSNUM[NUM_aggregateSR] = {4.,     8.,     3.,     3.,     2.,     4.};
            static const double aggregateBKGNUM[NUM_aggregateSR] = {3.4,    10.7,   8.8,    5.3,    1.9,    8.6};
            static const double aggregateBKGERR[NUM_aggregateSR] = {0.9,    3.2,    1.8,    1.5,    0.5,    2.5};
            for (size_t ibin = 0; ibin < NUM_aggregateSR; ++ibin) {
                stringstream ass; ass << "aggregate_sr-" << ibin;
                add_result(SignalRegionData(ass.str(), aggregateOBSNUM[ibin], {_aggregateSR[ibin],  0.}, {aggregateBKGNUM[ibin], aggregateBKGERR[ibin]}));
                // cout << ass.str() << ":  "<< _aggregateSR[ibin] << endl;
            }

            return;
        }

    protected:
        void analysis_specific_reset() {
            for(size_t i=0;i<NUM_aggregateSR;i++) { _aggregateSR[i]=0; }
        }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_1LEPStop_36invfb)


  }
}
