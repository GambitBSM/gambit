#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

/* The CMS 2 lepton direct stop analysis (35.9fb^-1) - `heavy stop'.

   Based on: arXiv:1711.00752
   Yang Zhang

   Known errors:
        Using ATLASEfficiencies instead of CMSEfficiencies because "applyLooseIDElectronSelectionR2" and "applyMediumIDElectronSelectionR2" functions are important for this analysis.

*/

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_2LEPStop_36invfb : public Analysis {
    private:

        // Numbers passing cuts
        std::map<string, EventCounter> _counters = {
            {"SF-SR-0", EventCounter("SF-SR-0")},
            {"DF-SR-0", EventCounter("DF-SR-0")},
            {"SF-SR-1", EventCounter("SF-SR-1")},
            {"DF-SR-1", EventCounter("DF-SR-1")},
            {"SF-SR-2", EventCounter("SF-SR-2")},
            {"DF-SR-2", EventCounter("DF-SR-2")},
            {"SF-SR-3", EventCounter("SF-SR-3")},
            {"DF-SR-3", EventCounter("DF-SR-3")},
            {"SF-SR-4", EventCounter("SF-SR-4")},
            {"DF-SR-4", EventCounter("DF-SR-4")},
            {"SF-SR-5", EventCounter("SF-SR-5")},
            {"DF-SR-5", EventCounter("DF-SR-5")},
            {"SF-SR-6", EventCounter("SF-SR-6")},
            {"DF-SR-6", EventCounter("DF-SR-6")},
            {"SF-SR-7", EventCounter("SF-SR-7")},
            {"DF-SR-7", EventCounter("DF-SR-7")},
            {"SF-SR-8", EventCounter("SF-SR-8")},
            {"DF-SR-8", EventCounter("DF-SR-8")},
            {"SF-SR-9", EventCounter("SF-SR-9")},
            {"DF-SR-9", EventCounter("DF-SR-9")},
            {"SF-SR-10", EventCounter("SF-SR-10")},
            {"DF-SR-10", EventCounter("DF-SR-10")},
            {"SF-SR-11", EventCounter("SF-SR-11")},
            {"DF-SR-11", EventCounter("DF-SR-11")},
            {"SF-SR-12", EventCounter("SF-SR-12")},
            {"DF-SR-12", EventCounter("DF-SR-12")},
            //
            {"ALL-SR-0", EventCounter("ALL-SR-0")},
            {"ALL-SR-1", EventCounter("ALL-SR-1")},
            {"ALL-SR-2", EventCounter("ALL-SR-2")},
            {"ALL-SR-3", EventCounter("ALL-SR-3")},
            {"ALL-SR-4", EventCounter("ALL-SR-4")},
            {"ALL-SR-5", EventCounter("ALL-SR-5")},
            {"ALL-SR-6", EventCounter("ALL-SR-6")},
            {"ALL-SR-7", EventCounter("ALL-SR-7")},
            {"ALL-SR-8", EventCounter("ALL-SR-8")},
            {"ALL-SR-9", EventCounter("ALL-SR-9")},
            {"ALL-SR-10", EventCounter("ALL-SR-10")},
            {"ALL-SR-11", EventCounter("ALL-SR-11")},
            {"ALL-SR-12", EventCounter("ALL-SR-12")},
            //
            {"A-SR-0", EventCounter("A-SR-0")},
            {"A-SR-1", EventCounter("A-SR-1")},
            {"A-SR-2", EventCounter("A-SR-2")},
        };

        static const size_t _SR_size = 13;
        static const size_t _SRA_size = 3;

        // Cut Flow
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        int NCUTS;


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

        // Lepton overlap removal
        void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax) {
            //Routine to do lepton-jet check
            //Discards leptons if they are within DeltaRMax of a jet

            vector<const HEPUtils::Particle*> Survivors;

            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
                bool overlap = false;
                HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
                for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
                    HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
                    double dR;

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

        Analysis_CMS_13TeV_2LEPStop_36invfb() {

            set_analysis_name("CMS_13TeV_2LEPStop_36invfb");
            set_luminosity(35.9);

            NCUTS= 11;
            for(int i=0;i<NCUTS;i++){
                cutFlowVector.push_back(0);
                cutFlowVector_str.push_back("");
            }

        }

        void run(const HEPUtils::Event* event) {

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Baseline lepton objects
            const vector<double> a={0,10.};
            const vector<double> b={0,10000.};
            const vector<double> cEl={0.83};
            HEPUtils::BinnedFn2D<double> _eff2dEl(a,b,cEl);
            const vector<double> cMu={0.89};
            HEPUtils::BinnedFn2D<double> _eff2dMu(a,b,cMu);
            vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons;
            for (const HEPUtils::Particle* electron : event->electrons()) {
                bool hasTrig=has_tag(_eff2dEl, electron->abseta(), electron->pT());
                if (electron->pT() > 15. && electron->abseta() < 2.4 && hasTrig) baselineElectrons.push_back(electron);
            }
            for (const HEPUtils::Particle* muon : event->muons()) {
                bool hasTrig=has_tag(_eff2dMu, muon->abseta(), muon->pT());
                if (muon->pT() > 15. && muon->abseta() < 2.4 && hasTrig) baselineMuons.push_back(muon);
            }
            ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);
            // Jets
            vector<const HEPUtils::Jet*> baselineJets;
            for (const HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 30. && fabs(jet->eta()) < 2.4) baselineJets.push_back(jet);
            }

            // Overlap removal
            JetLeptonOverlapRemoval(baselineJets,baselineElectrons,0.4);
            JetLeptonOverlapRemoval(baselineJets,baselineMuons,0.4);

            //Baseline Leptons
            int LooseLepNum = baselineElectrons.size()+baselineMuons.size();
            //Signal Leptons
            ATLAS::applyMediumIDElectronSelectionR2(baselineElectrons);
            vector<const HEPUtils::Particle*> signalLeptons;
            for (const HEPUtils::Particle* electron : baselineElectrons) {
                signalLeptons.push_back(electron);
            }
            for (const HEPUtils::Particle* muon : baselineMuons) {
                signalLeptons.push_back(muon);
            }

            //Put signal jets／leptons in pT order
            //std::sort(signalJets.begin(), signalJets.end(), sortByPT_j);
            //std::sort(signalLeptons.begin(), signalLeptons.end(), sortByPT_l);
            //std::sort(sgJets.begin(), sgJets.end(), sortByPT_j);
            //std::sort(sgLeptons.begin(), sgLeptons.end(), sortByPT_l);

            // Function used to get b jets
            vector<const HEPUtils::Jet*> bJets;
            vector<const HEPUtils::Jet*> nobJets;
            //const std::vector<double>  a = {0,10.};
            //const std::vector<double>  b = {0,10000.};
            const std::vector<double> c = {0.60};
            HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
            for (const HEPUtils::Jet* jet :baselineJets) {
                bool hasTag=has_tag(_eff2d, jet->abseta(), jet->pT());
                if(jet->btag() && hasTag && jet->pT() > 25.) {
                        bJets.push_back(jet);
                    }else{
                        nobJets.push_back(jet);
                    }


            }
            int nbjet = bJets.size();
            int njet  = nobJets.size();

            // We now have the signal electrons, muons, jets and b jets- move on to the analysis
            /*********************************************************/
            /*                                                       */
            /* SIGNAL REGIONS                                        */
            /*                                                       */
            /*********************************************************/
            bool cut_2OSLep     =false;
            bool cut_mllGt20    =false;
            bool flg_SF         =false;
            bool cut_mllMZ      =true;
            bool cut_Njet       =false;
            bool cut_Nbjet      =false;
            bool cut_PTmis      =false;
            bool cut_SGt5       =false;
            bool cut_csj1       =false;
            bool cut_csj2       =false;
            bool cut_MT2ll140   =false;
            bool sig_MT2bl_0    =false;
            bool sig_MT2bl_100  =false;
            bool sig_MT2bl_200  =false;
            bool sig_MET_80     =false;
            bool sig_MET_200    =false;
            bool sig_MT2ll_100  =false;
            bool sig_MT2ll_140  =false;
            bool sig_MT2ll_240  =false;
            // Two opposite sign leptons, pT(l1,l2)>25,20GeV
            if(signalLeptons.size() == 2 && LooseLepNum ==2){
                if (signalLeptons[0]->pid()*signalLeptons[1]->pid()<0. && signalLeptons[0]->pT() > 25. && signalLeptons[1]->pT() > 20.){
                    cut_2OSLep = true;
                    /* Calculate variables */
                    // Invariant mass of two leptons
                    HEPUtils::P4 lepton0=signalLeptons.at(0)->mom();
                    HEPUtils::P4 lepton1=signalLeptons.at(1)->mom();
                    double Mll= (lepton0+lepton1).m();
                    // S=MET/sqrt(HT)
                    double HT = 0.;
                    for (const HEPUtils::Jet* jet :baselineJets) {
                        HT += jet->pT();
                    }
                    double S=met/sqrt(HT);

                    // Set flags
                    cut_mllGt20 = Mll>20.;
                    flg_SF      = signalLeptons[0]->pid()+signalLeptons[1]->pid()==0;
                    cut_mllMZ   = !(flg_SF && abs(Mll-91.2)<15.);
                    cut_Njet    = njet+nbjet>=2;
                    cut_Nbjet   = nbjet>=1;
                    cut_PTmis   = met>80.;
                    cut_SGt5    = S>5.;

                    // Angular speration of P_T^{miss} and (sub-)leading jet
                    if (cut_Njet) {
                        double cosj1 = cos(baselineJets[0]->phi() - ptot.phi());
                        double cosj2 = cos(baselineJets[1]->phi() - ptot.phi());
                        cut_csj1    = cosj1<0.80;
                        cut_csj2    = cosj2<0.96;
                    }
                    // only calculate mt2 after pass these cuts, to save time
                    if(cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5 && cut_csj1 && cut_csj2){
                        // MT2
                        double pmiss[3] = { 0, ptot.px(), ptot.py() };
                        mt2_bisect::mt2 mt2_event_bl,mt2_event_ll;
                        // MT2_{ll}
                        double mt2ll=0;
                        double pa_ll[3] = { 0, signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py() };
                        double pb_ll[3] = { 0, signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py() };
                        mt2_event_ll.set_momenta(pa_ll,pb_ll,pmiss);
                        mt2_event_ll.set_mn(0.);
                        mt2ll = mt2_event_ll.get_mt2();
                        // MT2_{blbl}
                        double mt2blbl=0;
                        // find lepton-jet pair minimizes the maximum invariant mass of lepton-jet pairs
                        HEPUtils::P4 bj1 = bJets.at(0)->mom();
                        HEPUtils::P4 bj2;
                        if (nbjet==1) {
                            bj2 = nobJets.at(0)->mom();
                        }else{
                            bj2 = bJets.at(1)->mom();
                        }

                        HEPUtils::P4 l1b1 = lepton0+bj1;
                        HEPUtils::P4 l2b2 = lepton1+bj2;

                        HEPUtils::P4 l1b2 = lepton0+bj2;
                        HEPUtils::P4 l2b1 = lepton1+bj1;
                        double pa_bl[3];
                        double pb_bl[3];
                        pa_bl[0] = 0;
                        pb_bl[0] = 0;
                        if (max(l1b1.m(),l2b2.m()) < max(l1b2.m(),l2b1.m())){
                            pa_bl[1] = l1b1.px();
                            pa_bl[2] = l1b1.py();
                            pb_bl[1] = l2b2.px();
                            pb_bl[2] = l2b2.py();
                        }else{
                            pa_bl[1] = l1b2.px();
                            pa_bl[2] = l1b2.py();
                            pb_bl[1] = l2b1.px();
                            pb_bl[2] = l2b1.py();
                        }
                        mt2_event_bl.set_momenta(pa_bl,pb_bl,pmiss);
                        mt2_event_bl.set_mn(0.);
                        mt2blbl = mt2_event_bl.get_mt2();
                        cut_MT2ll140   = mt2ll>140.;

                        sig_MET_80     = met<200.;
                        sig_MET_200    = met>200.;

                        sig_MT2bl_0    = (mt2blbl<100)&&(mt2blbl>0);
                        sig_MT2bl_100  = (mt2blbl>100)&& (mt2blbl<200);
                        sig_MT2bl_200  = mt2blbl>200;

                        sig_MT2ll_100  = (mt2ll>100.)&&(mt2ll<140.);
                        sig_MT2ll_140  = (mt2ll>140.)&&(mt2ll<240.);
                        sig_MT2ll_240  = (mt2ll>240.);
                    }
                }

            }
            /*********************************************************/
            /*                                                       */
            /* Cut Flow                                              */
            /*                                                       */
            /*********************************************************/
            cutFlowVector_str[0] = "Total ";
            cutFlowVector_str[1] = "2 OS lepton";
            cutFlowVector_str[2] = "m(ll)>20 GeV";
            cutFlowVector_str[3] = "|m(ll)-mZ|>15 GeV";
            cutFlowVector_str[4] = "Njets>2";
            cutFlowVector_str[5] = "Nbjets>1";
            cutFlowVector_str[6] = "MET>80 GeV";
            cutFlowVector_str[7] = "S>5 GeV^{1/2}";
            cutFlowVector_str[8] = "cosPhi(MET,j1)<0.80";
            cutFlowVector_str[9] = "cosPhi(MET,j2)<0.96";
            cutFlowVector_str[10] = "MT2(ll)>140";

            for(int j=0;j<NCUTS;j++){
                if(
                   (j==0) ||
                   (j==1  && cut_2OSLep)||
                   (j==2  && cut_2OSLep && cut_mllGt20)||
                   (j==3  && cut_2OSLep && cut_mllGt20 && cut_mllMZ)||
                   (j==4  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet)||
                   (j==5  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet)||
                   (j==6  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis)||
                   (j==7  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5)||
                   (j==8  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5 && cut_csj1) ||
                   (j==9  && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5 && cut_csj1 && cut_csj2) ||
                   (j==10 && cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5 && cut_csj1 && cut_csj2 && cut_MT2ll140)
                   )cutFlowVector[j]++;
            }
            bool pre_cut= cut_2OSLep && cut_mllGt20 && cut_mllMZ && cut_Njet && cut_Nbjet && cut_PTmis && cut_SGt5 && cut_csj1 && cut_csj2 ;
            // signal region
            for(size_t j=0;j<_SR_size;j++){
                // same flavour
                if(
                   (j==0 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==1 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_200)||
                   (j==2 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==3 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_200)||
                   (j==4 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==5 && pre_cut && flg_SF && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_200)||
                   (j==6  && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==7  && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_200)||
                   (j==8  && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==9  && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_200)||
                   (j==10 && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==11 && pre_cut && flg_SF && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_200)||
                   (j==12 && pre_cut && flg_SF && sig_MT2ll_240)
                   )
                {
                    stringstream sr_key; sr_key << "SF-SR-" << j;
                    _counters.at(sr_key.str()).add_event(event);
                }
                 // diferent flavour
                if(
                   (j==0 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==1 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_200)||
                   (j==2 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==3 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_200)||
                   (j==4 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==5 && pre_cut && !flg_SF && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_200)||
                   (j==6  && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==7  && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_200)||
                   (j==8  && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==9  && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_200)||
                   (j==10 && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==11 && pre_cut && !flg_SF && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_200)||
                   (j==12 && pre_cut && !flg_SF && sig_MT2ll_240)
                   )
                {
                    stringstream sr_key; sr_key << "DF-SR-" << j;
                    _counters.at(sr_key.str()).add_event(event);
                }
                 // all
                if(
                   (j==0 && pre_cut && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==1 && pre_cut && sig_MT2ll_100 && sig_MT2bl_0   && sig_MET_200)||
                   (j==2 && pre_cut && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==3 && pre_cut && sig_MT2ll_100 && sig_MT2bl_100 && sig_MET_200)||
                   (j==4 && pre_cut && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==5 && pre_cut && sig_MT2ll_100 && sig_MT2bl_200 && sig_MET_200)||
                   (j==6  && pre_cut && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_80 )||
                   (j==7  && pre_cut && sig_MT2ll_140 && sig_MT2bl_0   && sig_MET_200)||
                   (j==8  && pre_cut && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_80 )||
                   (j==9  && pre_cut && sig_MT2ll_140 && sig_MT2bl_100 && sig_MET_200)||
                   (j==10 && pre_cut && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_80 )||
                   (j==11 && pre_cut && sig_MT2ll_140 && sig_MT2bl_200 && sig_MET_200)||
                   (j==12 && pre_cut && sig_MT2ll_240)
                   )
                {
                    stringstream sr_key; sr_key << "ALL-SR-" << j;
                    _counters.at(sr_key.str()).add_event(event);
                }

            }
            for(size_t j=0;j<_SRA_size;j++){
                if(
                   (j==0  && pre_cut && sig_MT2ll_100 && sig_MET_200) ||
                   (j==1  && pre_cut && sig_MT2ll_140 && sig_MET_200)||
                   (j==2  && pre_cut && sig_MT2ll_240)
                   )
                {
                    stringstream sr_key; sr_key << "A-SR-" << j;
                    _counters.at(sr_key.str()).add_event(event);
                }

            }
        return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2LEPStop_36invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

            if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;

            for (int j=0; j<NCUTS; j++)
            {
                cutFlowVector[j] += specificOther->cutFlowVector[j];
                cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
            }

        }


        void collect_results() {

           //  double scale_by=1./10000*41.8*35.9;
           //  cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
           //  cout << "CUT FLOW: CMS 13 TeV 2 lep stop paper "<<endl;
           //  cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
           //  cout<< right << setw(40) << "CUT" <<  "," << setw(20) << "RAW" <<  "," << setw(20) << "SCALED"
           //  <<  "," << setw(20) << "%" <<  "," << setw(20) << "clean adj RAW"<<  "," << setw(20) << "clean adj %" << endl;
           //  for (int j=0; j<NCUTS; j++) {
           //      cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
           //      << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
           //      << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
           //      << cutFlowVector[j]*scale_by <<  "," << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
           //  }
           //  for (size_t j=0; j<_SR_size; j++) {
           //      cout << right <<  setw(40) << "SR_SF_"<<j <<  "," << setw(20)
           //      << _SRSF[j] <<  "," << setw(20) << _SRSF[j]*scale_by <<  "," << setw(20)
           //      << 100.*_SRSF[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
           //      << _SRSF[j]*scale_by <<  "," << setw(20) << 100.*_SRSF[j]/cutFlowVector[0]<< "%" << endl;
           //  }
           // for (size_t j=0; j<_SR_size; j++) {
           //      cout << right <<  setw(40) << "SR_DF_"<<j <<  "," << setw(20)
           //      << _SRDF[j] <<  "," << setw(20) << _SRDF[j]*scale_by <<  "," << setw(20)
           //      << 100.*_SRDF[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
           //      << _SRDF[j]*scale_by <<  "," << setw(20) << 100.*_SRDF[j]/cutFlowVector[0]<< "%" << endl;
           //  }
           // for (size_t j=0; j<_SR_size; j++) {
           //      cout << right <<  setw(40) << "SR_ALL_"<<j <<  "," << setw(20)
           //      << _SRALL[j] <<  "," << setw(20) << _SRALL[j]*scale_by <<  "," << setw(20)
           //      << 100.*_SRALL[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
           //      << _SRALL[j]*scale_by <<  "," << setw(20) << 100.*_SRALL[j]/cutFlowVector[0]<< "%" << endl;
           //  }
           // for (size_t j=0; j<_SRA_size; j++) {
           //      cout << right <<  setw(40) << "SR_A_"<<j <<  "," << setw(20)
           //      << _SRA[j] <<  "," << setw(20) << _SRA[j]*scale_by <<  "," << setw(20)
           //      << 100.*_SRA[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
           //      << _SRA[j]*scale_by <<  "," << setw(20) << 100.*_SRA[j]/cutFlowVector[0]<< "%" << endl;
           //  }
           //  cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;


            // The ordering here is important! (Must match the ordering in the covariance matrix.)

            add_result(SignalRegionData(_counters.at("SF-SR-0"), 112., {131., 30.}));
            add_result(SignalRegionData(_counters.at("DF-SR-0"), 141., {139., 32.}));
            add_result(SignalRegionData(_counters.at("SF-SR-1"), 7., {4.1, 1.1}));
            add_result(SignalRegionData(_counters.at("DF-SR-1"), 6., {4.0, 1.1}));
            add_result(SignalRegionData(_counters.at("SF-SR-2"), 69., {60., 13.}));
            add_result(SignalRegionData(_counters.at("DF-SR-2"), 67., {70., 17.}));
            add_result(SignalRegionData(_counters.at("SF-SR-3"), 1., {4.8, 1.2}));
            add_result(SignalRegionData(_counters.at("DF-SR-3"), 5., {3.9, 1.0}));
            add_result(SignalRegionData(_counters.at("SF-SR-4"), 0., {0.5, 0.2}));
            add_result(SignalRegionData(_counters.at("DF-SR-4"), 1., {0.7, 0.2}));
            add_result(SignalRegionData(_counters.at("SF-SR-5"), 2., {1.9, 0.5}));
            add_result(SignalRegionData(_counters.at("DF-SR-5"), 1., {2.1, 0.5}));
            add_result(SignalRegionData(_counters.at("SF-SR-6"), 2., {1.1, 0.6}));
            add_result(SignalRegionData(_counters.at("DF-SR-6"), 1., {0.5, 0.2}));
            add_result(SignalRegionData(_counters.at("SF-SR-7"), 2., {0.6, 0.3}));
            add_result(SignalRegionData(_counters.at("DF-SR-7"), 0., {0.3, 0.2}));
            add_result(SignalRegionData(_counters.at("SF-SR-8"), 1., {2.1, 0.7}));
            add_result(SignalRegionData(_counters.at("DF-SR-8"), 1., {0.8, 0.2}));
            add_result(SignalRegionData(_counters.at("SF-SR-9"), 1., {1.6, 0.4}));
            add_result(SignalRegionData(_counters.at("DF-SR-9"), 0., {0.9, 0.3}));
            add_result(SignalRegionData(_counters.at("SF-SR-10"), 0., {0.3, 0.1}));
            add_result(SignalRegionData(_counters.at("DF-SR-10"), 0., {0.1, 0.1}));
            add_result(SignalRegionData(_counters.at("SF-SR-11"), 2., {1.7, 0.4}));
            add_result(SignalRegionData(_counters.at("DF-SR-11"), 1., {1.2, 0.3}));
            add_result(SignalRegionData(_counters.at("SF-SR-12"), 1., {0.7, 0.3}));
            add_result(SignalRegionData(_counters.at("DF-SR-12"), 0., {0.5, 0.2}));

            // Covariance
            static const vector< vector<double> > BKGCOV = {
                { 5.3194e+02,  5.6771e+02,  1.8684e+01,  1.6492e+01,  2.3063e+02,  2.8905e+02,  1.9505e+01,  1.7490e+01,  2.6561e+00,  2.6653e+00,  5.0460e+00,  5.0163e+00,  8.9507e+00,  2.3766e+00,  9.8583e-01,  1.3022e+00,  3.9829e+00,  2.6211e+00,  4.9758e+00,  2.1205e+00,  1.0389e+00,  1.5502e+00,  1.9997e+00,  1.7448e+00,  1.3077e+00,  1.3214e+00 },
                { 5.6771e+02,  6.1906e+02,  1.9990e+01,  1.7052e+01,  2.5036e+02,  3.1355e+02,  2.0392e+01,  1.8370e+01,  2.8239e+00,  2.8702e+00,  5.4655e+00,  5.3022e+00,  9.5056e+00,  2.5391e+00,  1.0873e+00,  1.3742e+00,  3.8246e+00,  2.7103e+00,  5.0959e+00,  2.2521e+00,  1.0596e+00,  1.6599e+00,  2.1668e+00,  1.8156e+00,  1.1961e+00,  1.3860e+00 },
                { 1.8684e+01,  1.9990e+01,  8.0044e-01,  6.1691e-01,  8.1071e+00,  1.0332e+01,  7.5130e-01,  6.8902e-01,  1.0644e-01,  1.0291e-01,  1.8205e-01,  1.9331e-01,  3.9899e-01,  9.7319e-02,  4.1821e-02,  5.3172e-02,  1.6707e-01,  1.0554e-01,  2.1778e-01,  9.2657e-02,  4.4517e-02,  6.2436e-02,  9.5188e-02,  8.0067e-02,  5.9439e-02,  5.0877e-02 },
                { 1.6492e+01,  1.7052e+01,  6.1691e-01,  7.6473e-01,  6.9105e+00,  8.6205e+00,  7.4060e-01,  6.3375e-01,  9.6551e-02,  9.9212e-02,  1.7671e-01,  2.0168e-01,  3.0737e-01,  8.0554e-02,  2.9765e-02,  5.0244e-02,  1.7901e-01,  1.0966e-01,  2.0895e-01,  8.9960e-02,  4.3461e-02,  5.3985e-02,  7.4419e-02,  7.0960e-02,  8.3015e-02,  5.6826e-02 },
                { 2.3063e+02,  2.5036e+02,  8.1071e+00,  6.9105e+00,  1.0414e+02,  1.2760e+02,  8.2163e+00,  7.3665e+00,  1.1854e+00,  1.1945e+00,  2.2947e+00,  2.2128e+00,  4.1840e+00,  1.0313e+00,  4.5132e-01,  5.8788e-01,  1.5837e+00,  1.1135e+00,  2.0549e+00,  9.5650e-01,  4.3562e-01,  6.7523e-01,  1.0206e+00,  7.9693e-01,  5.0508e-01,  5.8693e-01 },
                { 2.8905e+02,  3.1355e+02,  1.0332e+01,  8.6205e+00,  1.2760e+02,  1.6215e+02,  1.0463e+01,  9.5654e+00,  1.4799e+00,  1.4686e+00,  2.7644e+00,  2.6835e+00,  5.2915e+00,  1.3538e+00,  5.8855e-01,  7.3332e-01,  2.0368e+00,  1.4079e+00,  2.7165e+00,  1.1773e+00,  5.6688e-01,  8.7317e-01,  1.2322e+00,  1.0113e+00,  6.4218e-01,  7.0242e-01 },
                { 1.9505e+01,  2.0392e+01,  7.5130e-01,  7.4060e-01,  8.2163e+00,  1.0463e+01,  1.0287e+00,  7.6637e-01,  1.0937e-01,  1.0463e-01,  1.9544e-01,  2.2336e-01,  3.7308e-01,  1.0539e-01,  4.6961e-02,  6.1891e-02,  2.2609e-01,  1.2628e-01,  2.5923e-01,  1.0512e-01,  5.2826e-02,  6.5884e-02,  1.0433e-01,  9.6370e-02,  9.5443e-02,  6.1743e-02 },
                { 1.7490e+01,  1.8370e+01,  6.8902e-01,  6.3375e-01,  7.3665e+00,  9.5654e+00,  7.6637e-01,  8.0269e-01,  1.0101e-01,  9.2154e-02,  1.6096e-01,  1.9015e-01,  3.9687e-01,  9.9379e-02,  4.3819e-02,  5.5038e-02,  2.1020e-01,  1.1305e-01,  2.4799e-01,  9.0312e-02,  5.0615e-02,  6.5191e-02,  1.0268e-01,  9.4560e-02,  8.2500e-02,  5.1264e-02 },
                { 2.6561e+00,  2.8239e+00,  1.0644e-01,  9.6551e-02,  1.1854e+00,  1.4799e+00,  1.0937e-01,  1.0101e-01,  2.9980e-02,  1.7717e-02,  3.0716e-02,  3.1868e-02,  9.5800e-02,  1.6825e-02,  8.7343e-03,  1.1184e-02,  3.0785e-02,  1.7567e-02,  3.6791e-02,  1.8716e-02,  8.1056e-03,  1.1309e-02,  2.2679e-02,  1.4927e-02,  1.2927e-02,  9.6934e-03 },
                { 2.6653e+00,  2.8702e+00,  1.0291e-01,  9.9212e-02,  1.1945e+00,  1.4686e+00,  1.0463e-01,  9.2154e-02,  1.7717e-02,  3.2637e-02,  3.7197e-02,  3.6867e-02,  6.4292e-02,  1.5286e-02,  7.0053e-03,  8.9835e-03,  2.5644e-02,  1.7595e-02,  3.2085e-02,  2.0321e-02,  6.3452e-03,  1.1104e-02,  1.8582e-02,  1.3061e-02,  1.0228e-02,  1.1229e-02 },
                { 5.0460e+00,  5.4655e+00,  1.8205e-01,  1.7671e-01,  2.2947e+00,  2.7644e+00,  1.9544e-01,  1.6096e-01,  3.0716e-02,  3.7197e-02,  1.3320e-01,  7.2853e-02,  1.0414e-01,  2.7724e-02,  1.6781e-02,  1.8456e-02,  5.0764e-02,  3.3388e-02,  5.9002e-02,  4.1474e-02,  1.2435e-02,  2.3334e-02,  4.6804e-02,  3.3895e-02,  2.4396e-02,  2.4601e-02 },
                { 5.0163e+00,  5.3022e+00,  1.9331e-01,  2.0168e-01,  2.2128e+00,  2.6835e+00,  2.2336e-01,  1.9015e-01,  3.1868e-02,  3.6867e-02,  7.2853e-02,  1.3749e-01,  1.0448e-01,  2.7933e-02,  1.6057e-02,  1.8609e-02,  6.5802e-02,  4.0306e-02,  7.5158e-02,  4.4161e-02,  1.5868e-02,  2.5403e-02,  5.7045e-02,  4.6043e-02,  3.3479e-02,  2.6702e-02 },
                { 8.9507e+00,  9.5056e+00,  3.9899e-01,  3.0737e-01,  4.1840e+00,  5.2915e+00,  3.7308e-01,  3.9687e-01,  9.5800e-02,  6.4292e-02,  1.0414e-01,  1.0448e-01,  1.1184e+00,  8.1500e-02,  5.4322e-02,  6.6261e-02,  1.7456e-01,  7.2330e-02,  1.6798e-01,  8.5680e-02,  4.1260e-02,  6.2930e-02,  1.5499e-01,  8.5152e-02,  7.3468e-02,  3.9911e-02 },
                { 2.3766e+00,  2.5391e+00,  9.7319e-02,  8.0554e-02,  1.0313e+00,  1.3538e+00,  1.0539e-01,  9.9379e-02,  1.6825e-02,  1.5286e-02,  2.7724e-02,  2.7933e-02,  8.1500e-02,  3.5721e-02,  1.2933e-02,  1.2922e-02,  4.1210e-02,  2.0006e-02,  4.3159e-02,  2.1719e-02,  8.9845e-03,  1.5637e-02,  2.3350e-02,  1.7656e-02,  1.4849e-02,  1.2072e-02 },
                { 9.8583e-01,  1.0873e+00,  4.1821e-02,  2.9765e-02,  4.5132e-01,  5.8855e-01,  4.6961e-02,  4.3819e-02,  8.7343e-03,  7.0053e-03,  1.6781e-02,  1.6057e-02,  5.4322e-02,  1.2933e-02,  4.5405e-02,  9.1447e-03,  3.3152e-02,  1.0576e-02,  2.6809e-02,  1.6087e-02,  5.2946e-03,  1.0817e-02,  2.2351e-02,  1.5041e-02,  1.2762e-02,  8.2640e-03 },
                { 1.3022e+00,  1.3742e+00,  5.3172e-02,  5.0244e-02,  5.8788e-01,  7.3332e-01,  6.1891e-02,  5.5038e-02,  1.1184e-02,  8.9835e-03,  1.8456e-02,  1.8609e-02,  6.6261e-02,  1.2922e-02,  9.1447e-03,  1.8988e-02,  2.8901e-02,  1.3199e-02,  2.5877e-02,  1.4781e-02,  5.7955e-03,  1.0012e-02,  2.1564e-02,  1.4831e-02,  1.3357e-02,  8.7491e-03 },
                { 3.9829e+00,  3.8246e+00,  1.6707e-01,  1.7901e-01,  1.5837e+00,  2.0368e+00,  2.2609e-01,  2.1020e-01,  3.0785e-02,  2.5644e-02,  5.0764e-02,  6.5802e-02,  1.7456e-01,  4.1210e-02,  3.3152e-02,  2.8901e-02,  5.2128e-01,  4.6476e-02,  1.1115e-01,  5.4605e-02,  2.4117e-02,  3.9149e-02,  6.2784e-02,  5.0293e-02,  5.6023e-02,  2.9498e-02 },
                { 2.6211e+00,  2.7103e+00,  1.0554e-01,  1.0966e-01,  1.1135e+00,  1.4079e+00,  1.2628e-01,  1.1305e-01,  1.7567e-02,  1.7595e-02,  3.3388e-02,  4.0306e-02,  7.2330e-02,  2.0006e-02,  1.0576e-02,  1.3199e-02,  4.6476e-02,  3.8988e-02,  5.0753e-02,  2.5412e-02,  1.0692e-02,  1.3569e-02,  2.8883e-02,  2.5439e-02,  2.0626e-02,  1.4548e-02 },
                { 4.9758e+00,  5.0959e+00,  2.1778e-01,  2.0895e-01,  2.0549e+00,  2.7165e+00,  2.5923e-01,  2.4799e-01,  3.6791e-02,  3.2085e-02,  5.9002e-02,  7.5158e-02,  1.6798e-01,  4.3159e-02,  2.6809e-02,  2.5877e-02,  1.1115e-01,  5.0753e-02,  1.7335e-01,  4.8780e-02,  2.3285e-02,  3.0358e-02,  6.4377e-02,  5.3819e-02,  4.6691e-02,  2.7065e-02 },
                { 2.1205e+00,  2.2521e+00,  9.2657e-02,  8.9960e-02,  9.5650e-01,  1.1773e+00,  1.0512e-01,  9.0312e-02,  1.8716e-02,  2.0321e-02,  4.1474e-02,  4.4161e-02,  8.5680e-02,  2.1719e-02,  1.6087e-02,  1.4781e-02,  5.4605e-02,  2.5412e-02,  4.8780e-02,  7.2753e-02,  1.0189e-02,  1.9951e-02,  3.6650e-02,  2.7780e-02,  2.0359e-02,  1.9194e-02 },
                { 1.0389e+00,  1.0596e+00,  4.4517e-02,  4.3461e-02,  4.3562e-01,  5.6688e-01,  5.2826e-02,  5.0615e-02,  8.1056e-03,  6.3452e-03,  1.2435e-02,  1.5868e-02,  4.1260e-02,  8.9845e-03,  5.2946e-03,  5.7955e-03,  2.4117e-02,  1.0692e-02,  2.3285e-02,  1.0189e-02,  8.8177e-03,  7.1401e-03,  1.4131e-02,  1.1504e-02,  1.0410e-02,  5.7238e-03 },
                { 1.5502e+00,  1.6599e+00,  6.2436e-02,  5.3985e-02,  6.7523e-01,  8.7317e-01,  6.5884e-02,  6.5191e-02,  1.1309e-02,  1.1104e-02,  2.3334e-02,  2.5403e-02,  6.2930e-02,  1.5637e-02,  1.0817e-02,  1.0012e-02,  3.9149e-02,  1.3569e-02,  3.0358e-02,  1.9951e-02,  7.1401e-03,  3.5878e-01,  2.1581e-02,  1.4489e-02,  1.3345e-02,  1.1549e-02 },
                { 1.9997e+00,  2.1668e+00,  9.5188e-02,  7.4419e-02,  1.0206e+00,  1.2322e+00,  1.0433e-01,  1.0268e-01,  2.2679e-02,  1.8582e-02,  4.6804e-02,  5.7045e-02,  1.5499e-01,  2.3350e-02,  2.2351e-02,  2.1564e-02,  6.2784e-02,  2.8883e-02,  6.4377e-02,  3.6650e-02,  1.4131e-02,  2.1581e-02,  1.3679e-01,  5.7687e-02,  3.5832e-02,  2.0300e-02 },
                { 1.7448e+00,  1.8156e+00,  8.0067e-02,  7.0960e-02,  7.9693e-01,  1.0113e+00,  9.6370e-02,  9.4560e-02,  1.4927e-02,  1.3061e-02,  3.3895e-02,  4.6043e-02,  8.5152e-02,  1.7656e-02,  1.5041e-02,  1.4831e-02,  5.0293e-02,  2.5439e-02,  5.3819e-02,  2.7780e-02,  1.1504e-02,  1.4489e-02,  5.7687e-02,  7.2829e-02,  2.7915e-02,  1.6751e-02 },
                { 1.3077e+00,  1.1961e+00,  5.9439e-02,  8.3015e-02,  5.0508e-01,  6.4218e-01,  9.5443e-02,  8.2500e-02,  1.2927e-02,  1.0228e-02,  2.4396e-02,  3.3479e-02,  7.3468e-02,  1.4849e-02,  1.2762e-02,  1.3357e-02,  5.6023e-02,  2.0626e-02,  4.6691e-02,  2.0359e-02,  1.0410e-02,  1.3345e-02,  3.5832e-02,  2.7915e-02,  7.5294e-02,  1.4477e-02 },
                { 1.3214e+00,  1.3860e+00,  5.0877e-02,  5.6826e-02,  5.8693e-01,  7.0242e-01,  6.1743e-02,  5.1264e-02,  9.6934e-03,  1.1229e-02,  2.4601e-02,  2.6702e-02,  3.9911e-02,  1.2072e-02,  8.2640e-03,  8.7491e-03,  2.9498e-02,  1.4548e-02,  2.7065e-02,  1.9194e-02,  5.7238e-03,  1.1549e-02,  2.0300e-02,  1.6751e-02,  1.4477e-02,  2.8456e-02 }
            };

            set_covariance(BKGCOV);

            return;
        }


    protected:
      void analysis_specific_reset() {

        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);

      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPStop_36invfb)

  }
}
