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
        // int _SRSF[13], _SRDF[13], _SRALL[13],_SRA[3];
        static const size_t _SR_size = 13;
        static const size_t _SRA_size = 3;
        std::vector<int> _SRSF;
        std::vector<int> _SRDF;
        std::vector<int> _SRALL;
        std::vector<int> _SRA;

        // Cut Flow
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        int NCUTS;


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

        // Lepton overlap removal
        void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec, double DeltaRMax) {
            //Routine to do lepton-jet check
            //Discards leptons if they are within DeltaRMax of a jet

            vector<HEPUtils::Particle*> Survivors;

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

            for(size_t i=0;i<_SR_size;i++){
                _SRSF.push_back(0);
                _SRDF.push_back(0);
                _SRALL.push_back(0);
            }
            for(size_t i=0;i<_SRA_size;i++){
                _SRA.push_back(0);
            }
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
            vector<HEPUtils::Particle*> baselineElectrons, baselineMuons;
            for (HEPUtils::Particle* electron : event->electrons()) {
                bool hasTrig=has_tag(_eff2dEl, electron->eta(), electron->pT());
                if (electron->pT() > 15. && electron->abseta() < 2.4 && hasTrig) baselineElectrons.push_back(electron);
            }
            for (HEPUtils::Particle* muon : event->muons()) {
                bool hasTrig=has_tag(_eff2dMu, muon->eta(), muon->pT());
                if (muon->pT() > 15. && muon->abseta() < 2.4 && hasTrig) baselineMuons.push_back(muon);
            }
            ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);
            // Jets
            vector<HEPUtils::Jet*> baselineJets;
            for (HEPUtils::Jet* jet : event->jets()) {
                if (jet->pT() > 30. && fabs(jet->eta()) < 2.4) baselineJets.push_back(jet);
            }

            // Overlap removal
            JetLeptonOverlapRemoval(baselineJets,baselineElectrons,0.4);
            JetLeptonOverlapRemoval(baselineJets,baselineMuons,0.4);

            //Baseline Leptons
            int LooseLepNum = baselineElectrons.size()+baselineMuons.size();
            //Signal Leptons
            ATLAS::applyMediumIDElectronSelectionR2(baselineElectrons);
            vector<HEPUtils::Particle*> signalLeptons;
            for (HEPUtils::Particle* electron : baselineElectrons) {
                signalLeptons.push_back(electron);
            }
            for (HEPUtils::Particle* muon : baselineMuons) {
                signalLeptons.push_back(muon);
            }

            //Put signal jets／leptons in pT order
            //std::sort(signalJets.begin(), signalJets.end(), sortByPT_j);
            //std::sort(signalLeptons.begin(), signalLeptons.end(), sortByPT_l);
            //std::sort(sgJets.begin(), sgJets.end(), sortByPT_j);
            //std::sort(sgLeptons.begin(), sgLeptons.end(), sortByPT_l);

            // Function used to get b jets
            vector<HEPUtils::Jet*> bJets;
            vector<HEPUtils::Jet*> nobJets;
            //const std::vector<double>  a = {0,10.};
            //const std::vector<double>  b = {0,10000.};
            const std::vector<double> c = {0.60};
            HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
            for (HEPUtils::Jet* jet :baselineJets) {
                bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
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
                    for (HEPUtils::Jet* jet :baselineJets) {
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
                   )_SRSF[j]++;
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
                   )_SRDF[j]++;
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
                   )_SRALL[j]++;
            }
            for(size_t j=0;j<_SRA_size;j++){
                if(
                   (j==0  && pre_cut && sig_MT2ll_100 && sig_MET_200) ||
                   (j==1  && pre_cut && sig_MT2ll_140 && sig_MET_200)||
                   (j==2  && pre_cut && sig_MT2ll_240)
                   )_SRA[j]++;
            }
        return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2LEPStop_36invfb*>(other);

            if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;

            for (int j=0; j<NCUTS; j++)
            {
                cutFlowVector[j] += specificOther->cutFlowVector[j];
                cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
            }

            for (size_t j=0; j<_SR_size; j++)
            {
                _SRSF[j] += specificOther->_SRSF[j];
                _SRDF[j] += specificOther->_SRDF[j];
                _SRALL[j] += specificOther->_SRALL[j];
            }

            for (size_t j=0; j<_SRA_size; j++)
            {
                _SRA[j] += specificOther->_SRA[j];
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

            // Observed event counts, same-flavor signal regions
            static const double OBSNUM_SF[_SR_size] = {
                112., 7., 69., 1., 0., 2., 2., 2., 1., 1., 0., 2., 1.
            };
            // Background estimates, same-flavor signal regions
            static const double BKGNUM_SF[_SR_size] = {
                131., 4.1, 60., 4.8, 0.5, 1.9, 1.1, 0.6, 2.1, 1.6, 0.3, 1.7, 0.7
            };
            // Background uncertainties, same-flavor signal regions
            static const double BKGERR_SF[_SR_size] = {
                30., 1.1, 13., 1.2, 0.2, 0.5, 0.6, 0.3, 0.7, 0.4, 0.1, 0.4, 0.3
            };

            // Observed event counts, different-flavor signal regions
            static const double OBSNUM_DF[_SR_size] = {
                141., 6., 67., 5., 1., 1., 1., 0., 1., 0., 0., 1., 0.
            };
            // Background estimates, different-flavor signal regions
            static const double BKGNUM_DF[_SR_size] = {
                139., 4.0, 70., 3.9, 0.7, 2.1, 0.5, 0.3, 0.8, 0.9, 0.1, 1.2, 0.5
            };
            // Background uncertainties, different-flavor signal regions
            static const double BKGERR_DF[_SR_size] = {
                32., 1.1, 17., 1.0, 0.2, 0.5, 0.2, 0.2, 0.2, 0.3, 0.1, 0.3, 0.2
            };

            for (size_t ibin = 0; ibin < _SR_size; ++ibin)
            {
                stringstream ss_SF; ss_SF << "SF-SR-" << ibin;
                stringstream ss_DF; ss_DF << "DF-SR-" << ibin;
                // The ordering here is important -- first add SF then DF regions.
                // (Must match the ordering in the covariance matrix.)
                add_result(SignalRegionData(ss_SF.str(), OBSNUM_SF[ibin], {_SRSF[ibin],  0.}, {BKGNUM_SF[ibin], BKGERR_SF[ibin]}));
                add_result(SignalRegionData(ss_DF.str(), OBSNUM_DF[ibin], {_SRDF[ibin],  0.}, {BKGNUM_DF[ibin], BKGERR_DF[ibin]}));
            }

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

            // Same flavour
            /*SignalRegionData results_SRSF0;
            results_SRSF0.sr_label = "SRSF0";
            results_SRSF0.n_observed = 112.;
            results_SRSF0.n_background = 131.;
            results_SRSF0.background_sys = 30.;
            results_SRSF0.signal_sys = 0.;
            results_SRSF0.n_signal = _SRSF[0];
            add_result(results_SRSF0);

            SignalRegionData results_SRSF1;
            results_SRSF1.sr_label = "SRSF1";
            results_SRSF1.n_observed = 7.;
            results_SRSF1.n_background = 4.1;
            results_SRSF1.background_sys = 1.1;
            results_SRSF1.signal_sys = 0.;
            results_SRSF1.n_signal = _SRSF[1];
            add_result(results_SRSF1);

            SignalRegionData results_SRSF2;
            results_SRSF2.sr_label = "SRSF2";
            results_SRSF2.n_observed = 69.;
            results_SRSF2.n_background = 60.;
            results_SRSF2.background_sys = 13.;
            results_SRSF2.signal_sys = 0.;
            results_SRSF2.n_signal = _SRSF[2];
            add_result(results_SRSF2);

            SignalRegionData results_SRSF3;
            results_SRSF3.sr_label = "SRSF3";
            results_SRSF3.n_observed = 1.;
            results_SRSF3.n_background = 4.8;
            results_SRSF3.background_sys = 1.2;
            results_SRSF3.signal_sys = 0.;
            results_SRSF3.n_signal = _SRSF[3];
            add_result(results_SRSF3);

            SignalRegionData results_SRSF4;
            results_SRSF4.sr_label = "SRSF4";
            results_SRSF4.n_observed = 0.;
            results_SRSF4.n_background = 0.5;
            results_SRSF4.background_sys = 0.2;
            results_SRSF4.signal_sys = 0.;
            results_SRSF4.n_signal = _SRSF[4];
            add_result(results_SRSF4);

            SignalRegionData results_SRSF5;
            results_SRSF5.sr_label = "SRSF5";
            results_SRSF5.n_observed = 2.;
            results_SRSF5.n_background = 1.9;
            results_SRSF5.background_sys = 0.5;
            results_SRSF5.signal_sys = 0.;
            results_SRSF5.n_signal = _SRSF[5];
            add_result(results_SRSF5);

            SignalRegionData results_SRSF6;
            results_SRSF6.sr_label = "SRSF6";
            results_SRSF6.n_observed = 2.;
            results_SRSF6.n_background = 1.1;
            results_SRSF6.background_sys = 0.6;
            results_SRSF6.signal_sys = 0.;
            results_SRSF6.n_signal = _SRSF[6];
            add_result(results_SRSF6);

            SignalRegionData results_SRSF7;
            results_SRSF7.sr_label = "SRSF7";
            results_SRSF7.n_observed = 2.;
            results_SRSF7.n_background = 0.6;
            results_SRSF7.background_sys = 0.3;
            results_SRSF7.signal_sys = 0.;
            results_SRSF7.n_signal = _SRSF[7];
            add_result(results_SRSF7);

            SignalRegionData results_SRSF8;
            results_SRSF8.sr_label = "SRSF8";
            results_SRSF8.n_observed = 1.;
            results_SRSF8.n_background = 2.1;
            results_SRSF8.background_sys = 0.7;
            results_SRSF8.signal_sys = 0.;
            results_SRSF8.n_signal = _SRSF[8];
            add_result(results_SRSF8);

            SignalRegionData results_SRSF9;
            results_SRSF9.sr_label = "SRSF9";
            results_SRSF9.n_observed = 1.;
            results_SRSF9.n_background = 1.6;
            results_SRSF9.background_sys = 0.4;
            results_SRSF9.signal_sys = 0.;
            results_SRSF9.n_signal = _SRSF[9];
            add_result(results_SRSF9);

            SignalRegionData results_SRSF10;
            results_SRSF10.sr_label = "SRSF10";
            results_SRSF10.n_observed = 0.;
            results_SRSF10.n_background = 0.3;
            results_SRSF10.background_sys = 0.1;
            results_SRSF10.signal_sys = 0.;
            results_SRSF10.n_signal = _SRSF[10];
            add_result(results_SRSF10);

            SignalRegionData results_SRSF11;
            results_SRSF11.sr_label = "SRSF11";
            results_SRSF11.n_observed = 2.;
            results_SRSF11.n_background = 1.7;
            results_SRSF11.background_sys = 0.4;
            results_SRSF11.signal_sys = 0.;
            results_SRSF11.n_signal = _SRSF[11];
            add_result(results_SRSF11);

            SignalRegionData results_SRSF12;
            results_SRSF12.sr_label = "SRSF12";
            results_SRSF12.n_observed = 1.;
            results_SRSF12.n_background = 0.7;
            results_SRSF12.background_sys = 0.3;
            results_SRSF12.signal_sys = 0.;
            results_SRSF12.n_signal = _SRSF[12];
            add_result(results_SRSF12);

            // Different falvor
            SignalRegionData results_SRDF0;
            results_SRDF0.sr_label = "SRDF0";
            results_SRDF0.n_observed = 141.;
            results_SRDF0.n_background = 139.;
            results_SRDF0.background_sys = 32.;
            results_SRDF0.signal_sys = 0.;
            results_SRDF0.n_signal = _SRDF[0];
            add_result(results_SRDF0);

            SignalRegionData results_SRDF1;
            results_SRDF1.sr_label = "SRDF1";
            results_SRDF1.n_observed = 6.;
            results_SRDF1.n_background = 4.0;
            results_SRDF1.background_sys = 1.1;
            results_SRDF1.signal_sys = 0.;
            results_SRDF1.n_signal = _SRDF[1];
            add_result(results_SRDF1);

            SignalRegionData results_SRDF2;
            results_SRDF2.sr_label = "SRDF2";
            results_SRDF2.n_observed = 67.;
            results_SRDF2.n_background = 70.;
            results_SRDF2.background_sys = 17.;
            results_SRDF2.signal_sys = 0.;
            results_SRDF2.n_signal = _SRDF[2];
            add_result(results_SRDF2);

            SignalRegionData results_SRDF3;
            results_SRDF3.sr_label = "SRDF3";
            results_SRDF3.n_observed = 5.;
            results_SRDF3.n_background = 3.9;
            results_SRDF3.background_sys = 1.0;
            results_SRDF3.signal_sys = 0.;
            results_SRDF3.n_signal = _SRDF[3];
            add_result(results_SRDF3);

            SignalRegionData results_SRDF4;
            results_SRDF4.sr_label = "SRDF4";
            results_SRDF4.n_observed = 1.;
            results_SRDF4.n_background = 0.7;
            results_SRDF4.background_sys = 0.2;
            results_SRDF4.signal_sys = 0.;
            results_SRDF4.n_signal = _SRDF[4];
            add_result(results_SRDF4);

            SignalRegionData results_SRDF5;
            results_SRDF5.sr_label = "SRDF5";
            results_SRDF5.n_observed = 1.;
            results_SRDF5.n_background = 2.1;
            results_SRDF5.background_sys = 0.5;
            results_SRDF5.signal_sys = 0.;
            results_SRDF5.n_signal = _SRDF[5];
            add_result(results_SRDF5);

            SignalRegionData results_SRDF6;
            results_SRDF6.sr_label = "SRDF6";
            results_SRDF6.n_observed = 1.;
            results_SRDF6.n_background = 0.5;
            results_SRDF6.background_sys = 0.2;
            results_SRDF6.signal_sys = 0.;
            results_SRDF6.n_signal = _SRDF[6];
            add_result(results_SRDF6);

            SignalRegionData results_SRDF7;
            results_SRDF7.sr_label = "SRDF7";
            results_SRDF7.n_observed = 0.;
            results_SRDF7.n_background = 0.3;
            results_SRDF7.background_sys = 0.2;
            results_SRDF7.signal_sys = 0.;
            results_SRDF7.n_signal = _SRDF[7];
            add_result(results_SRDF7);

            SignalRegionData results_SRDF8;
            results_SRDF8.sr_label = "SRDF8";
            results_SRDF8.n_observed = 1.;
            results_SRDF8.n_background = 0.8;
            results_SRDF8.background_sys = 0.2;
            results_SRDF8.signal_sys = 0.;
            results_SRDF8.n_signal = _SRDF[8];
            add_result(results_SRDF8);

            SignalRegionData results_SRDF9;
            results_SRDF9.sr_label = "SRDF9";
            results_SRDF9.n_observed = 0.;
            results_SRDF9.n_background = 0.9;
            results_SRDF9.background_sys = 0.3;
            results_SRDF9.signal_sys = 0.;
            results_SRDF9.n_signal = _SRDF[9];
            add_result(results_SRDF9);

            SignalRegionData results_SRDF10;
            results_SRDF10.sr_label = "SRDF10";
            results_SRDF10.n_observed = 0.;
            results_SRDF10.n_background = 0.1;
            results_SRDF10.background_sys = 0.1;
            results_SRDF10.signal_sys = 0.;
            results_SRDF10.n_signal = _SRDF[10];
            add_result(results_SRDF10);

            SignalRegionData results_SRDF11;
            results_SRDF11.sr_label = "SRDF11";
            results_SRDF11.n_observed = 1.;
            results_SRDF11.n_background = 1.2;
            results_SRDF11.background_sys = 0.3;
            results_SRDF11.signal_sys = 0.;
            results_SRDF11.n_signal = _SRDF[11];
            add_result(results_SRDF11);

            SignalRegionData results_SRDF12;
            results_SRDF12.sr_label = "SRDF12";
            results_SRDF12.n_observed = 0.;
            results_SRDF12.n_background = 0.5;
            results_SRDF12.background_sys = 0.2;
            results_SRDF12.signal_sys = 0.;
            results_SRDF12.n_signal = _SRDF[12];
            add_result(results_SRDF12);

            // DF+SF
            SignalRegionData results_SRALL0;
            results_SRALL0.sr_label = "SRALL0";
            results_SRALL0.n_observed = 253.;
            results_SRALL0.n_background = 271.;
            results_SRALL0.background_sys = 61.;
            results_SRALL0.signal_sys = 0.;
            results_SRALL0.n_signal = _SRALL[0];
            add_result(results_SRALL0);

            SignalRegionData results_SRALL1;
            results_SRALL1.sr_label = "SRALL1";
            results_SRALL1.n_observed = 13.;
            results_SRALL1.n_background = 8.1;
            results_SRALL1.background_sys = 2.0;
            results_SRALL1.signal_sys = 0.;
            results_SRALL1.n_signal = _SRALL[1];
            add_result(results_SRALL1);

            SignalRegionData results_SRALL2;
            results_SRALL2.sr_label = "SRALL2";
            results_SRALL2.n_observed = 136.;
            results_SRALL2.n_background = 130.;
            results_SRALL2.background_sys = 29.;
            results_SRALL2.signal_sys = 0.;
            results_SRALL2.n_signal = _SRALL[2];
            add_result(results_SRALL2);

            SignalRegionData results_SRALL3;
            results_SRALL3.sr_label = "SRALL3";
            results_SRALL3.n_observed = 6.;
            results_SRALL3.n_background = 8.7;
            results_SRALL3.background_sys = 2.0;
            results_SRALL3.signal_sys = 0.;
            results_SRALL3.n_signal = _SRALL[3];
            add_result(results_SRALL3);

            SignalRegionData results_SRALL4;
            results_SRALL4.sr_label = "SRALL4";
            results_SRALL4.n_observed = 1.;
            results_SRALL4.n_background = 1.2;
            results_SRALL4.background_sys = 0.4;
            results_SRALL4.signal_sys = 0.;
            results_SRALL4.n_signal = _SRALL[4];
            add_result(results_SRALL4);

            SignalRegionData results_SRALL5;
            results_SRALL5.sr_label = "SRALL5";
            results_SRALL5.n_observed = 3.;
            results_SRALL5.n_background = 4.0;
            results_SRALL5.background_sys = 0.8;
            results_SRALL5.signal_sys = 0.;
            results_SRALL5.n_signal = _SRALL[5];
            add_result(results_SRALL5);

            SignalRegionData results_SRALL6;
            results_SRALL6.sr_label = "SRALL6";
            results_SRALL6.n_observed = 3.;
            results_SRALL6.n_background = 1.5;
            results_SRALL6.background_sys = 0.7;
            results_SRALL6.signal_sys = 0.;
            results_SRALL6.n_signal = _SRALL[6];
            add_result(results_SRALL6);

            SignalRegionData results_SRALL7;
            results_SRALL7.sr_label = "SRALL7";
            results_SRALL7.n_observed = 2.;
            results_SRALL7.n_background = 0.8;
            results_SRALL7.background_sys = 0.3;
            results_SRALL7.signal_sys = 0.;
            results_SRALL7.n_signal = _SRALL[7];
            add_result(results_SRALL7);

            SignalRegionData results_SRALL8;
            results_SRALL8.sr_label = "SRALL8";
            results_SRALL8.n_observed = 2.;
            results_SRALL8.n_background = 2.9;
            results_SRALL8.background_sys = 0.7;
            results_SRALL8.signal_sys = 0.;
            results_SRALL8.n_signal = _SRALL[8];
            add_result(results_SRALL8);

            SignalRegionData results_SRALL9;
            results_SRALL9.sr_label = "SRALL9";
            results_SRALL9.n_observed = 1.;
            results_SRALL9.n_background = 2.5;
            results_SRALL9.background_sys = 0.5;
            results_SRALL9.signal_sys = 0.;
            results_SRALL9.n_signal = _SRALL[9];
            add_result(results_SRALL9);

            SignalRegionData results_SRALL10;
            results_SRALL10.sr_label = "SRALL10";
            results_SRALL10.n_observed = 0.;
            results_SRALL10.n_background = 0.4;
            results_SRALL10.background_sys = 0.2;
            results_SRALL10.signal_sys = 0.;
            results_SRALL10.n_signal = _SRALL[10];
            add_result(results_SRALL10);

            SignalRegionData results_SRALL11;
            results_SRALL11.sr_label = "SRALL11";
            results_SRALL11.n_observed = 3.;
            results_SRALL11.n_background = 2.9;
            results_SRALL11.background_sys = 0.6;
            results_SRALL11.signal_sys = 0.;
            results_SRALL11.n_signal = _SRALL[11];
            add_result(results_SRALL11);

            SignalRegionData results_SRALL12;
            results_SRALL12.sr_label = "SRALL12";
            results_SRALL12.n_observed = 1.;
            results_SRALL12.n_background = 1.1;
            results_SRALL12.background_sys = 0.4;
            results_SRALL12.signal_sys = 0.;
            results_SRALL12.n_signal = _SRALL[12];
            add_result(results_SRALL12);*/

            /*//Signal region A
            SignalRegionData results_SRA0;
            results_SRA0.sr_label = "SRA0";
            results_SRA0.n_observed = 22.;
            results_SRA0.n_background = 20.8;
            results_SRA0.background_sys = 4.4;
            results_SRA0.signal_sys = 0.;
            results_SRA0.n_signal = _SRA[0];
            add_result(results_SRA0);

            SignalRegionData results_SRA1;
            results_SRA1.sr_label = "SRA1";
            results_SRA1.n_observed = 6.;
            results_SRA1.n_background = 6.2;
            results_SRA1.background_sys = 1.0;
            results_SRA1.signal_sys = 0.;
            results_SRA1.n_signal = _SRA[1];
            add_result(results_SRA1);

            SignalRegionData results_SRA2;
            results_SRA2.sr_label = "SRA2";
            results_SRA2.n_observed = 1.;
            results_SRA2.n_background = 1.1;
            results_SRA2.background_sys = 0.4;
            results_SRA2.signal_sys = 0.;
            results_SRA2.n_signal = _SRA[2];
            add_result(results_SRA2);*/

    protected:
      void analysis_specific_reset() {

        std::fill(_SRSF.begin(), _SRSF.end(), 0);
        std::fill(_SRDF.begin(), _SRDF.end(), 0);
        std::fill(_SRALL.begin(), _SRALL.end(), 0);
        std::fill(_SRA.begin(), _SRA.end(), 0);

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);

      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPStop_36invfb)

  }
}
