#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

/* The ATLAS 0 lepton direct stop analysis (20fb^-1) - `heavy stop'.

   Based originally on: ATLAS-CONF-2013-024
   Now updated to arXiv:1406.1122
   Code by Martin White, Sky French.
   Known errors:
   a) The isolation is already applied in the simulation rather than after overlap removal -> the electron and muon veto technically require a veto on base-line electrons/muons not overlapping with jets
   b) ETmiss-track cuts ignored...

   Known features:
   a) Have removed the tau veto since it disagrees with ATLAS cutflow (we lose ~2/3 of the events whilst ATLAS see a minimal effect. So ditching it is fine. In fact the implementation below is incorrect since it does not take into account the number of tracks associated to the jets.
   b) Using mt2 bisect method from H. Cheng, Z. Han, arXiv:0810.5178 for mT2 calculation

*/

namespace Gambit {
  namespace ColliderBit {

    bool sortByPT(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }

    class Analysis_ATLAS_8TeV_0LEPStop_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      double _numSRA1, _numSRA2, _numSRA3, _numSRA4;
      double _numSRC1, _numSRC2, _numSRC3;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=16;

      // Debug histos

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
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_8TeV_0LEPStop_20invfb() {

        set_analysis_name("ATLAS_8TeV_0LEPStop_20invfb");
        set_luminosity(20.1);

        _numSRA1 = 0 ; _numSRA2 = 0; _numSRA3 = 0; _numSRA4 = 0;
        _numSRC1 = 0 ; _numSRC2 = 0; _numSRC3 = 0;
        NCUTS=23;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }

      }



      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();


        // Baseline lepton objects
        vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons, baselineTaus;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        for (const HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 10. && tau->abseta() < 2.47) baselineTaus.push_back(tau);
        }
        ATLAS::applyTauEfficiencyR1(baselineTaus);


        // Jets
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonBJets;
        vector<const HEPUtils::Jet*> trueBJets; //for debugging

        // Get b jets
        /// @note We assume that b jets have previously been 100% tagged
        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.7};
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) baselineJets.push_back(jet);
          bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) {
            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.){
              bJets.push_back(jet);
            } else {
              nonBJets.push_back(jet);
            }
          }
        }


        // Overlap removal
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> electronsForVeto;
        vector<const HEPUtils::Particle*> muonsForVeto;

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;

        JetLeptonOverlapRemoval(nonBJets,baselineElectrons,0.2);
        LeptonJetOverlapRemoval(baselineElectrons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineElectrons,bJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,bJets,0.4);

        for (const HEPUtils::Jet* jet : bJets) {
          if (jet->pT() > 35. && fabs(jet->eta()) < 2.8) {
            signalJets.push_back(jet);
            signalBJets.push_back(jet);
          }
        }

        for (const HEPUtils::Jet* jet : nonBJets) {
          if (jet->pT() > 35. && fabs(jet->eta()) < 2.8){
            signalJets.push_back(jet);
            signalNonBJets.push_back(jet);
          }
        }

        //Put signal jets in pT order
        std::sort(signalJets.begin(), signalJets.end(), sortByPT);
        std::sort(signalBJets.begin(), signalBJets.end(), sortByPT);
        std::sort(signalNonBJets.begin(), signalNonBJets.end(), sortByPT);

        for (const HEPUtils::Particle* electron : baselineElectrons) {
          signalElectrons.push_back(electron);
        }

        for (const HEPUtils::Particle* muon : baselineMuons) {
          signalMuons.push_back(muon);
        }

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        // Calculate common variables and cuts first
        int nElectrons = signalElectrons.size();
        int nMuons = signalMuons.size();
        int nJets = signalJets.size();

        //Lepton veto
        bool cut_LeptonVeto=true;
        if((nElectrons + nMuons)>0.)cut_LeptonVeto=false;

        //Calculate dphi(jet,met) for the three leading jets
        bool cut_dPhiJets=false;
        bool cut_dPhiJet3=false;
        bool cut_dPhiJet2=false;
        bool cut_dPhiJet1=false;
        double dphi_jetmet1=9999;
        if(nJets>0)dphi_jetmet1=std::acos(std::cos(signalJets.at(0)->phi()-ptot.phi()));
        double dphi_jetmet2=9999;
        if(nJets>1)dphi_jetmet2=std::acos(std::cos(signalJets.at(1)->phi()-ptot.phi()));
        double dphi_jetmet3=9999;
        if(nJets>2)dphi_jetmet3=std::acos(std::cos(signalJets.at(2)->phi()-ptot.phi()));

        if(dphi_jetmet3>3.14/fabs(5.0))cut_dPhiJet3=true;
        if(dphi_jetmet2>3.14/fabs(5.0))cut_dPhiJet2=true;
        if(dphi_jetmet1>3.14/fabs(5.0))cut_dPhiJet1=true;
        if(cut_dPhiJet1 && cut_dPhiJet2 && cut_dPhiJet3)cut_dPhiJets=true;

        //Number of b jets
        bool passBJetCut=false;
        if(signalBJets.size()>=2)passBJetCut=true;
        //MET > 150 GeV
        bool cut_METGt150=false;
        if(met>150.)cut_METGt150=true;

        //Calculate dphi(b,met) for the closest b-jet in phi to MET
        double dphi_bjetmet_min=9999.;
        double minphi =9999.;
        int whichb=0;
        for(size_t j=0; j<signalBJets.size(); j++) {
          if(fabs(std::acos(std::cos(signalBJets.at(j)->phi()-ptot.phi())))<minphi) {
            minphi = fabs(std::acos(std::cos(signalBJets.at(j)->phi()-ptot.phi())));
            dphi_bjetmet_min = minphi;
            whichb=j;

          }
        }


        double mT_bjetmet_min = 0;
        if(passBJetCut) mT_bjetmet_min = sqrt(2*signalBJets.at(whichb)->pT()*met*(1-std::cos(dphi_bjetmet_min)));

        bool cut_mTbjetmetGt175=false;
        if(mT_bjetmet_min>175.)cut_mTbjetmetGt175=true;

        //Calculate dphi(b,met) for the furthest b-jet in phi to MET
        double dphi_bjetmet_max=0.;
        double maxphi =0.;
        int whichb_max=0;
        for(size_t j=0; j<signalBJets.size(); j++) {

          if(fabs(std::acos(std::cos(signalBJets.at(j)->phi()-ptot.phi())))>maxphi) {
            maxphi = fabs(std::acos(std::cos(signalBJets.at(j)->phi()-ptot.phi())));
            dphi_bjetmet_max = maxphi;
            whichb_max=j;
          }
        }

        double mT_bjetmet_max = 0;

        if(passBJetCut) mT_bjetmet_max = sqrt(2*signalBJets.at(whichb_max)->pT()*met*(1-std::cos(dphi_bjetmet_max)));

        //Common preselection for all signal regions in the fully resolved case
        bool passJetCutSRA=false;

        if(nJets>=6){
          if(signalJets[0]->pT() > 80.
             && signalJets[1]->pT() > 80.
             && signalJets[2]->pT() > 35.
             && signalJets[3]->pT() > 35.
             && signalJets[4]->pT() > 35.
             && signalJets[5]->pT() > 35.)passJetCutSRA=true;
        }

        //mjjj combinations

        HEPUtils::P4 mbjj0, mbjj1;

        double mindphi_12 = 9999.;

        HEPUtils::P4 W1;
        HEPUtils::P4 W2;
        HEPUtils::P4 T1;
        HEPUtils::P4 T2;
        HEPUtils::P4 jet1;
        HEPUtils::P4 jet2;
        HEPUtils::P4 jet3;
        HEPUtils::P4 jet4;
        HEPUtils::P4 jet5;
        HEPUtils::P4 jet6;

        //Need to form top quark four vectors from jets
        //Use the two leading b jets as the b jets (a slight departure from ATLAS which uses the two jets with the highest b weight)

        vector<const HEPUtils::Jet*> selectBJets;
        vector<const HEPUtils::Jet*> selectNonBJets;
        int bjetcount=0;

        for (const HEPUtils::Jet* jet : signalBJets) {
          if(bjetcount<2){
            bjetcount++;
            selectBJets.push_back(jet);
          }
        }

        //Now take any remaining jets in b jet collection plus the non b jets
        int i=0;
        for (const HEPUtils::Jet* jet : signalBJets) {
          i++;
          if(i>2)selectNonBJets.push_back(jet);
        }

        for (const HEPUtils::Jet* jet : signalNonBJets){
          selectNonBJets.push_back(jet);
        }

        if(nJets>=6 and bjetcount==2) {
          unsigned int j1 = 0 ; unsigned int j2 = 0; //unsigned int j4 = 0; unsigned int j5 = 0; //int j6 = 0;
          unsigned int b1 = 0;
          for(unsigned int k=0; k<selectNonBJets.size(); k++) {
            for(unsigned int l=k+1; l<selectNonBJets.size(); l++) {
        jet1.setXYZE(selectNonBJets[k]->mom().px(),selectNonBJets[k]->mom().py(),selectNonBJets[k]->mom().pz(),selectNonBJets[k]->E());
        jet2.setXYZE(selectNonBJets[l]->mom().px(),selectNonBJets[l]->mom().py(),selectNonBJets[l]->mom().pz(),selectNonBJets[l]->E());

        if(jet1.deltaR_eta(jet2)<mindphi_12) {
                j1 = k;
                j2 = l;
                mindphi_12 = jet1.deltaR_eta(jet2);
                W1 = jet1+jet2;

              }

            }
          }


          double mindphi_w1j3 = 9999.;
          for(unsigned int p=0; p<selectBJets.size(); p++) {

            jet3.setXYZE(selectBJets[p]->mom().px(),selectBJets[p]->mom().py(),selectBJets[p]->mom().pz(),selectBJets[p]->E());
            if(jet3.deltaR_eta(W1)<mindphi_w1j3) {
              b1 = p;
              mindphi_w1j3 = jet3.deltaR_eta(W1);
              T1 = W1+jet3;

            }
          }

          double mindphi_45 = 9999.;
          for(unsigned int k=0; k<selectNonBJets.size(); k++) {
            for(unsigned int l=k; l<selectNonBJets.size(); l++) {
              if(k!=j1 && k!=j2 && l!=j1 && l!=j2) {

                jet4.setXYZE(selectNonBJets[k]->mom().px(),selectNonBJets[k]->mom().py(),selectNonBJets[k]->mom().pz(),selectNonBJets[k]->E());
                jet5.setXYZE(selectNonBJets[l]->mom().px(),selectNonBJets[l]->mom().py(),selectNonBJets[l]->mom().pz(),selectNonBJets[l]->E());

                if(jet4.deltaR_eta(jet5)<mindphi_45) {
                  //j4 = k;
                  //j5 = l;
                  mindphi_45 = jet4.deltaR_eta(jet5);
                  W2 = jet4+jet5;

                }
              }
            }
          }
          double mindphi_w2j6 = 9999.;
          for(unsigned int p=0; p<selectBJets.size(); p++) {
            if(p!=b1) {

              jet6.setXYZE(selectBJets[p]->mom().px(),selectBJets[p]->mom().py(),selectBJets[p]->mom().pz(),selectBJets[p]->E());

              if(jet6.deltaR_eta(W2)<mindphi_w2j6) {
                //j6 = p;
                mindphi_w2j6 = jet6.deltaR_eta(W2);
                T2 = W2+jet6;

              }
            }
          }
          mbjj0 = T1;
          mbjj1 = T2;
        }

        bool cut_tau=true;

        /*
        //Tau Veto
        for (int j=0; j<signalNonBJets.size(); j++) {
        if(std::acos(std::cos(signalNonBJets.at(j)->phi()-ptot.phi()))<0.2*3.14)
        cut_tau=false;
        }*/

        //Cutflow flags
        //bool cut_mjjj0=false;
        //bool cut_mjjj1=false;

        bool cut_6jets=false;
        bool cut_Btag=false;

        bool cut_METGt130=false;
        //bool cut_METGt200=false;
        bool cut_METGt250=false;
        bool cut_METGt300=false;
        bool cut_METGt350=false;


        if(passJetCutSRA)cut_6jets=true;
        if(passBJetCut)cut_Btag=true;
        if(met>130.)cut_METGt130=true;
        if(met>250.)cut_METGt250=true;
        if(met>300.)cut_METGt300=true;
        if(met>350.)cut_METGt350=true;
        //if(nJets>=6) {
        //if(mbjj0.m()<270 && mjjj0.m()>80) cut_mjjj0=true;
        //if(mjjj1.m()<270 && mjjj1.m()>80) cut_mjjj1=true;
        //}

        //Calculate min transverse mass between signal jets and ptmiss

        double mtMin=9999;
        for(const HEPUtils::Jet* jet : signalJets){
          double dphi_jetmet=std::acos(std::cos(jet->phi()-ptot.phi()));
          double mT=sqrt(2.*jet->pT()*met*(1. - cos(dphi_jetmet)));
          if(mT<mtMin)mtMin=mT;
        }

        bool isSRA1=false;
        bool isSRA2=false;
        bool isSRA3=false;
        bool isSRA4=false;

        if(cut_LeptonVeto && cut_Btag && cut_METGt150 && cut_dPhiJets && cut_mTbjetmetGt175 && cut_6jets && mbjj0.m() < 225. && mbjj1.m() < 250. && cut_tau && cut_METGt150)isSRA1=true;

        if(cut_LeptonVeto && cut_Btag && cut_METGt150 && cut_dPhiJets && cut_mTbjetmetGt175 && cut_6jets && mbjj0.m() < 225. && mbjj1.m() < 250. && cut_tau && cut_METGt250)isSRA2=true;

        if(cut_LeptonVeto && cut_Btag && cut_METGt150 && cut_dPhiJets && cut_mTbjetmetGt175 && cut_6jets && mbjj0.m() > 50. && mbjj0.m() < 250. && mbjj1.m() > 50. && mbjj1.m() < 400. && mtMin > 50. && cut_tau && cut_METGt300)isSRA3=true;

        if(cut_LeptonVeto && cut_Btag && cut_METGt150 && cut_dPhiJets && cut_mTbjetmetGt175 && cut_6jets && mbjj0.m() > 50. && mbjj0.m() < 250. && mbjj1.m() > 50. && mbjj1.m() < 400. && mtMin > 50. && cut_tau && cut_METGt350)isSRA4=true;

        //Now do the mixed regions

        //Find highest pT b jet
        //Should no longe be necessary due to sorting of b jet collection
        /*double leadBJetPt=0;
          double leadBJetID=0;

          if(passBJetCut){
          for(int j=0; j<nJets; j++) {
          if(signalJets[j]->btag()&&signalJets[j]->pT()>leadBJetPt){
          leadBJetPt=signalJets[j]->pT();
          leadBJetID=j;
          }
          }
          }

          //Find sub-leading pT b jet
          double subBJetPt=0;
          double subBJetID=0;

          if(passBJetCut){
          for(int j=0; j<nJets; j++) {
          if(signalJets[j]->btag()&&signalJets[j]->pT()>subBJetPt && j!=leadBJetPt){
          subBJetPt=signalJets[j]->pT();
          subBJetID=j;
          }
          }
          }*/

        //Work out dPhi between B jets
        double dPhiBB=0;
        double leadBJetID=0;
        double subBJetID=1;
        if(passBJetCut){
          dPhiBB=std::acos(std::cos(signalBJets.at(leadBJetID)->phi()-signalBJets.at(subBJetID)->phi()));
        }

        bool passJetCutSRC=false;

        /*std::cout << "JET PT CHECK ";
          for(const HEPUtils::Jet* jet : signalJets){
          std::cout << jet->pT() << " ";
          }
          std::cout << endl;*/

        if(nJets==5){
          if(signalJets[0]->pT() > 80.
             && signalJets[1]->pT() > 80.
             && signalJets[2]->pT() > 35.
             && signalJets[3]->pT() > 35.
             && signalJets[4]->pT() > 35.)passJetCutSRC=true;
        }

        bool isSRC1=false;
        bool isSRC2=false;
        bool isSRC3=false;

        if(cut_LeptonVeto && cut_Btag && cut_METGt150 && cut_dPhiJets && cut_mTbjetmetGt175 && cut_tau){

          if(passJetCutSRC && mT_bjetmet_min > 185. && mT_bjetmet_max>205. && met>160. && dPhiBB > (0.2*3.14))isSRC1=true;

          if(passJetCutSRC && mT_bjetmet_min > 200. && mT_bjetmet_max>290. && met>160. && dPhiBB > (0.2*3.14))isSRC2=true;

          if(passJetCutSRC && mT_bjetmet_min > 200. && mT_bjetmet_max>325. && met>215. && dPhiBB > (0.2*3.14))isSRC3=true;

        }

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "MET > 130 GeV ";
        cutFlowVector_str[2] = "Lepton veto ";
        cutFlowVector_str[3] = "MET > 150 GeV ";
        cutFlowVector_str[4] = "Jet multiplicity and pT ";
        cutFlowVector_str[5] = "dPhi(jet,MET) > pi/5 ";
        cutFlowVector_str[6] = ">=2 b jets ";
        cutFlowVector_str[7] = "tau veto ";
        cutFlowVector_str[8] = "mT(b,MET) > 175 ";
        cutFlowVector_str[9] = "SRA1 ";
        cutFlowVector_str[10] = "SRA2 ";
        cutFlowVector_str[11] = "SRA3 ";
        cutFlowVector_str[12] = "SRA4 ";
        cutFlowVector_str[13] = "SRC: exactly 5 jets ";
        cutFlowVector_str[14] = "SRC: dPhi(jet,MET) ";
        cutFlowVector_str[15] = "SRC: >=2 b jets ";
        cutFlowVector_str[16] = "SRC: tau veto ";
        cutFlowVector_str[17] = "SRC: dPhi(b,b) ";
        cutFlowVector_str[18] = "SRC1";
        cutFlowVector_str[19] = "SRC2";
        cutFlowVector_str[20] = "SRC3";

        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && cut_METGt130) ||

             (j==2 && cut_METGt130 && cut_LeptonVeto) ||

             (j==3 && cut_METGt150 && cut_LeptonVeto) ||

             (j==4 && cut_METGt150 && cut_LeptonVeto && cut_6jets) ||

             (j==5 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets) ||

             (j==6 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag) ||

             (j==7 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau) ||

             (j==8 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau && cut_mTbjetmetGt175) ||

             (j==9 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau && cut_mTbjetmetGt175 && isSRA1) ||

             (j==10 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau && cut_mTbjetmetGt175 && isSRA2) ||

             (j==11 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau && cut_mTbjetmetGt175 && isSRA3) ||

             (j==12 && cut_METGt150 && cut_LeptonVeto && cut_6jets && cut_dPhiJets && cut_Btag && cut_tau && cut_mTbjetmetGt175 && isSRA4) ||

             (j==13 && cut_METGt150 && cut_LeptonVeto && passJetCutSRC) ||

             (j==14 && cut_METGt150 && cut_LeptonVeto && passJetCutSRC && cut_dPhiJets) ||

             (j==15 && cut_METGt150 && cut_LeptonVeto && passJetCutSRC && cut_dPhiJets && cut_Btag) ||

             (j==16 && cut_METGt150 && cut_LeptonVeto && passJetCutSRC && cut_dPhiJets && cut_Btag && cut_tau) ||

             (j==17 && cut_METGt150 && cut_LeptonVeto && passJetCutSRC && cut_dPhiJets && cut_Btag && cut_tau && dPhiBB > (0.2*3.14)) ||

             (j==18 && isSRC1) ||

             (j==19 && isSRC2) ||

             (j==20 && isSRC3)

             ){

            cutFlowVector[j]++;

          }
        }


        /*for(int j=0;j<NCUTS;j++){
          if(
          (j==0) ||

          (j==1 && cut_MuonVeto) ||

          (j==2 && cut_ElectronVeto && cut_MuonVeto) ||

          (j==3 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130) ||

          (j==4 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets) ||

          (j==5 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets) ||

          (j==6 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau) ||

          (j==7 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag) ||

          (j==8 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175) ||

          (j==9 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0) ||

          (j==10 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1) ||

          (j==11 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1 && cut_METGt150) ||

          (j==12 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1 && cut_METGt200) ||

          (j==13 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1 && cut_METGt250) ||

          (j==14 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1 && cut_METGt300) ||

          (j==15 && cut_ElectronVeto && cut_MuonVeto && cut_METGt130 && cut_6jets && cut_dPhiJets && cut_tau && cut_Btag && cut_mTbjetmetGt175 && cut_mjjj0 && cut_mjjj1 && cut_METGt350) )


          cutFlowVector[j]++;
          }*/

        //We're now ready to apply the cuts for each signal region
        //_numSR1, _numSR2, _numSR3;

        if(isSRA1) _numSRA1 += event->weight();
        if(isSRA2) _numSRA2 += event->weight();
        if(isSRA3) _numSRA3 += event->weight();
        if(isSRA4) _numSRA4 += event->weight();

        if(isSRC1) _numSRC1 += event->weight();
        if(isSRC2) _numSRC2 += event->weight();
        if(isSRC3) _numSRC3 += event->weight();

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_8TeV_0LEPStop_20invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_8TeV_0LEPStop_20invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _numSRA1 += specificOther->_numSRA1;
        _numSRA2 += specificOther->_numSRA2;
        _numSRA3 += specificOther->_numSRA3;
        _numSRA4 += specificOther->_numSRA4;
        _numSRC1 += specificOther->_numSRC1;
        _numSRC2 += specificOther->_numSRC2;
        _numSRC3 += specificOther->_numSRC3;
      }


      void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

        add_result(SignalRegionData("SRA1", 11., {_numSRA1, 0.}, {15.8, 1.9}));
        add_result(SignalRegionData("SRA2", 4., {_numSRA2, 0.}, {4.1, 0.8}));
        add_result(SignalRegionData("SRA3", 5., {_numSRA3, 0.}, {4.1, 0.9}));
        add_result(SignalRegionData("SRA4", 4., {_numSRA4, 0.}, {2.4, 0.7}));
        add_result(SignalRegionData("SRC1", 59., {_numSRC1, 0.}, {68., 7.}));
        add_result(SignalRegionData("SRC2", 30., {_numSRC2, 0.}, {34., 5.}));
        add_result(SignalRegionData("SRC3", 15., {_numSRC3, 0.}, {20.3, 3.}));

        return;
      }


    protected:
      void analysis_specific_reset() {
        _numSRA1 = 0 ; _numSRA2 = 0; _numSRA3 = 0; _numSRA4 = 0;
        _numSRC1 = 0 ; _numSRC2 = 0; _numSRC3 = 0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_0LEPStop_20invfb)


  }
}
