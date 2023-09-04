#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

/// @todo Remove the ROOT classes

using namespace std;


// The ATLAS 1 lepton direct stop analysis (20fb^-1).
//
// based on: ATLAS-CONF-2013-037
//
//    Code by Martin White, Sky French.
//    Known errors:
//    a) The isolation is already applied in the simulation rather than after overlap removal
//    b) The ATLAS analysis uses the two jets with the highest b tag weight for the MT2 calculation. This is impossible for us. Instead, we should use the two truth b jets. However, the b efficiency will be applied when preselecting events.
//    c) The isolated track cut has not been applied
//
//    Known features:
//    a) Must run simulator with 75% b tagging efficiency and 2% mis-id rate


namespace Gambit {
  namespace ColliderBit {

    /// A useful MT2 class for this module
    class MT2 {
    public:
      MT2(){
        MT2tauB=0;
        aMT2_BM=0;
      }

      double MT2tauB;
      double aMT2_BM;
    };


    class Analysis_ATLAS_8TeV_1LEPStop_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      double _numTN1Shape_bin1, _numTN1Shape_bin2, _numTN1Shape_bin3,
        _numTN2, _numTN3, _numBC1, _numBC2,_numBC3;

      vector<int> cutFlowVector_alt;
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_8TeV_1LEPStop_20invfb() {
        set_analysis_name("ATLAS_8TeV_1LEPStop_20invfb");
        set_luminosity(20.7);

        _numTN1Shape_bin1 = 0; _numTN1Shape_bin2 = 0; _numTN1Shape_bin3 = 0;
        _numTN2 = 0; _numTN3 = 0; _numBC1 = 0;
        _numBC2 = 0; _numBC3 = 0; NCUTS = 41;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
          cutFlowVector_alt.push_back(0);
        }

      }


      MT2 MT2helper(vector<const HEPUtils::Jet*> jets, vector<const HEPUtils::Particle*>  electrons,  vector<const HEPUtils::Particle*> muons, HEPUtils::P4 metVec){

        MT2 results;

        bool passmu = false;
        if(muons.size()==1)passmu=true;

        bool passel = false;
        if(electrons.size()==1)passel=true;

        int nJet = jets.size();
        if(nJet < 2)return results;

        //ATLAS use the two jets with highest MV1 weights
        //DELPHES does not have a continuous b weight

        //We have all b jets tagged (with 100% efficiency), so can use the two highest pT b jets
        //This corresponds to using the 2 b jets that are first in the collection

        const HEPUtils::Jet* trueBjet1 = NULL; //need to assign this
        const HEPUtils::Jet* trueBjet2 = NULL; //nee to assign this

        int nTrueBJets=0;
        for(const HEPUtils::Jet* tmpJet: jets){
          if(tmpJet->btag()){
            trueBjet1=tmpJet;
            nTrueBJets++;
            break;
          }
        }

        for(const HEPUtils::Jet* tmpJet: jets){
          if(tmpJet->btag() && tmpJet!=trueBjet1){
            trueBjet2=tmpJet;
            nTrueBJets++;
            break;
          }
        }

        if(nTrueBJets<2)return results;


	HEPUtils::P4 jet1B, jet2B;
	jet1B.setXYZE(trueBjet1->mom().px(), trueBjet1->mom().py(), trueBjet1->mom().pz(), trueBjet1->E());
	jet2B.setXYZE(trueBjet2->mom().px(), trueBjet2->mom().py(), trueBjet2->mom().pz(), trueBjet2->E());


        HEPUtils::P4 leptontmp;
        // double leptonmass = 0;
        if(passel){
          // leptonmass = 0.510998910; //MeV
          leptontmp = electrons[0]->mom();
        }
        else if(passmu){
          // leptonmass =  105.658367; // MeV
          leptontmp = muons[0]->mom();
        }


	HEPUtils::P4 lepton;
	lepton.setXYZE(leptontmp.px(),leptontmp.py(),leptontmp.pz(),leptontmp.E());


	HEPUtils::P4 lepton_plus_jet1B;
	HEPUtils::P4 lepton_plus_jet2B;

        lepton_plus_jet1B = lepton+jet1B;
        lepton_plus_jet2B = lepton+jet2B;

        double pa_a[3] = { 0, lepton_plus_jet1B.px(), lepton_plus_jet1B.py() };
        double pb_a[3] = { 80, jet2B.px(), jet2B.py() };
        double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
        double mn_a = 0.;

        mt2_bisect::mt2 mt2_event_a;

        mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
        mt2_event_a.set_mn(mn_a);

        double mt2a = mt2_event_a.get_mt2();

        double pa_b[3] = { 0, lepton_plus_jet2B.px(), lepton_plus_jet2B.py() };
        double pb_b[3] = { 80, jet1B.px(), jet1B.py() };
        double pmiss_b[3] = { 0, metVec.px(), metVec.py() };
        double mn_b = 0.;

        mt2_bisect::mt2 mt2_event_b;

        mt2_event_b.set_momenta(pa_b,pb_b,pmiss_b);
        mt2_event_b.set_mn(mn_b);
        double mt2b = mt2_event_b.get_mt2();

        double aMT2_BM = min(mt2a,mt2b);
        results.aMT2_BM=aMT2_BM;

        if (nJet > 3){
          const HEPUtils::Jet* jet3=0;
          for(const HEPUtils::Jet* current: jets){
            if (current == trueBjet1)continue;
            if (current == trueBjet2)continue;
            jet3 = current;
            break;
          }


	  HEPUtils::P4 jet3B;
	  jet3B.setXYZE(jet3->mom().px(), jet3->mom().py(), jet3->mom().pz(), jet3->mom().E());

          double pa_tau[3] = { 0, jet3B.px(), jet3B.py() };
          double pb_tau[3] = { 0, lepton.px(), lepton.py() };
          double pmiss_tau[3] = { 0, metVec.px(), metVec.py() };
          double mn_tau = 0.;

          mt2_bisect::mt2 mt2_event_tau;

          mt2_event_tau.set_momenta(pa_tau,pb_tau,pmiss_tau);
          mt2_event_tau.set_mn(mn_tau);

          //ComputeMT2 stuff3(jet3B,lepton,MET,0.,0.);
          //double MT2tauB = stuff3.ComputeNumeric();
          double MT2tauB = mt2_event_tau.get_mt2();//calcMT2(0,jet3B.Pt(),jet3B.Eta(),jet3B.Phi(),jet3B.E(),0,lepton.Pt(),lepton.Eta(),lepton.Phi(),lepton.E(),MET.Px(),MET.Py(),0);
          results.MT2tauB=MT2tauB;
        }
        return results;
      }



      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Now define vector of baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && electron->abseta() < 2.47 &&
              !object_in_cone(*event, *electron, 0.1*electron->pT(), 0.2)) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Now define vector of baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && muon->abseta() < 2.4 &&
              !object_in_cone(*event, *muon, 1.8, 0.2)) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        // Get b jets with efficiency and mistag (fake) rates
        vector<const HEPUtils::Jet*> baselineJets, bJets; // trueBJets; //for debugging
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && jet->abseta() < 10.0) baselineJets.push_back(jet);
          if (jet->abseta() < 2.5 && jet->pT() > 25.) {
            if ((jet->btag() && Random::draw() < 0.75) || (!jet->btag() && Random::draw() < 0.02)) bJets.push_back(jet);
          }
        }

        // Lepton isolation
        // We don't have access to all particles, so our isolation will be relative to jets etc.


        // Overlap removal
        vector<const HEPUtils::Particle*> signalElectrons, signalMuons;
        vector<const HEPUtils::Particle*> electronsForVeto, muonsForVeto;
        vector<const HEPUtils::Jet*> goodJets, signalJets;

        // Note that ATLAS use |eta|<10 for removing jets close to electrons
        // Then 2.8 is used for the rest of the overlap process
        // Then the signal cut is applied for signal jets

        // Remove any jet within dR=0.2 of an electron
        for (const HEPUtils::Jet* j : baselineJets) {
          if (!any(baselineElectrons, [&](const HEPUtils::Particle* e){ return deltaR_eta(*e, *j) < 0.2; })) {
            if (j->abseta() < 2.8) goodJets.push_back(j);
            if (j->abseta() < 2.5 && j->pT() > 25) signalJets.push_back(j);
          }
        }

        // Remove electrons and muons within dR=0.4 of surviving jets
        for (const HEPUtils::Particle* e : baselineElectrons) {
          if (!any(goodJets, [&](const HEPUtils::Jet* j){ return deltaR_eta(*e, *j) < 0.4; })) {
            electronsForVeto.push_back(e);
            if (e->pT() > 25) signalElectrons.push_back(e);
          }
        }
        for (const HEPUtils::Particle* m : baselineMuons) {
          if (!any(goodJets, [&](const HEPUtils::Jet* j){ return deltaR_eta(*m, *j) < 0.4; })) {
            muonsForVeto.push_back(m);
            if (m->pT() > 25) signalMuons.push_back(m);
          }
        }

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        // Calculate common variables and cuts first

        ATLAS::applyTightIDElectronSelection(signalElectrons);

        int nElectrons = signalElectrons.size();
        int nMuons = signalMuons.size();
        int nJets = signalJets.size();
        int nBjets = bJets.size();

        //if(leptonsForVeto.size()>0 && leptonsForVeto[0]->pT()>25.)cout << "Leptons size " << leptonsForVeto.size() << " muons " << nMuons << " electrons " << nElectrons << endl;

        //Common preselection for all signal regions
        bool passJetCut=false;
        bool passBJetCut=false;

        if(nJets>=4){
          if(signalJets[0]->pT() > 80.
             && signalJets[1]->pT() > 60.
             && signalJets[2]->pT() > 40.
             && signalJets[3]->pT() > 25.)passJetCut=true;

          if(signalJets[0]->btag() ||
             signalJets[1]->btag() ||
             signalJets[2]->btag() ||
             signalJets[3]->btag())passBJetCut=true;
        }

        //Must have exactly one lepton
        //cout << "leptonsForVeto size" << leptonsForVeto.size() << endl;

        //Calculate dphi(jet,met) for the two leading jets
        double dphi_jetmet1=9999;
        if(nJets>0)dphi_jetmet1=std::acos(std::cos(signalJets.at(0)->phi()-ptot.phi()));
        double dphi_jetmet2=9999;
        if(nJets>1)dphi_jetmet2=std::acos(std::cos(signalJets.at(1)->phi()-ptot.phi()));

        //Calculate met/sqrt(HT) (use four leading jets only)
        double HT=0;
        if(nJets>=4)HT=signalJets[0]->pT()+signalJets[1]->pT()+signalJets[2]->pT()+signalJets[3]->pT();
        double metOverSqrtHT=met/sqrt(HT);

        //Calculate mT
        HEPUtils::P4 lepVec;
        if(nElectrons==1)lepVec=signalElectrons[0]->mom();
        if(nMuons==1)lepVec=signalMuons[0]->mom();
        //cout << "DPHI" << ptot.deltaPhi(lepVec) << endl;
        //Note: phi here should be in the range -pi to pi
        //double mT = sqrt(2.*lepVec.pT()*met*(1.-cos(ptot.deltaPhi(lepVec))));
        //This is the ATLAS definition of dphi for this analysis
        //Note that it gives different answers to our dphi function (given above)
        double mT=sqrt(2.*lepVec.pT()*met*(1. - cos(lepVec.deltaPhi(ptot))));

        //Calculate meff (all jets with pT>30 GeV, lepton pT and met)
        double meff = met + lepVec.pT();
        for (const HEPUtils::Jet* jet : signalJets) {
          if(jet->pT()>30.)meff += jet->pT();
        }
        //Cutflow flags
        bool cut_1SignalElectron=false;
        bool cut_1SignalMuon=false;
        bool cut_4jets=false;
        bool cut_Btag=false;
        bool cut_sigGt5=false;
        bool cut_dPhiJet2=false;
        bool cut_dPhiJet1=false;
        bool cut_METGt275=false;
        bool cut_METGt200=false;
        bool cut_METGt160=false;
        bool cut_METGt150=false;
        bool cut_METGt100=false;
        bool cut_sigGt13=false;
        bool cut_sigGt11=false;
        bool cut_sigGt8=false;
        bool cut_sigGt7=false;
        bool cut_mTGt120=false;
        bool cut_mTGt140=false;
        bool cut_mTGt180=false;
        bool cut_mTGt200=false;
        //bool cut_PassHadTop=false;
        bool cut_meffGt550=false;
        bool cut_meffGt700=false;

        if(signalElectrons.size()==1 && electronsForVeto.size()==1 && muonsForVeto.size()==0)cut_1SignalElectron=true;
        if(signalMuons.size()==1 && muonsForVeto.size()==1 && electronsForVeto.size()==0)cut_1SignalMuon=true;

        if(passJetCut)cut_4jets=true;
        if(passBJetCut)cut_Btag=true;
        if(dphi_jetmet2>0.8)cut_dPhiJet2=true;
        if(dphi_jetmet1>0.8)cut_dPhiJet1=true;
        if(met>100.)cut_METGt100=true;
        if(met>150.)cut_METGt150=true;
        if(met>160.)cut_METGt160=true;
        if(met>200.)cut_METGt200=true;
        if(met>275.)cut_METGt275=true;
        if(metOverSqrtHT>13.)cut_sigGt13=true;
        if(metOverSqrtHT>11.)cut_sigGt11=true;
        if(metOverSqrtHT>8.)cut_sigGt8=true;
        if(metOverSqrtHT>7.)cut_sigGt7=true;
        if(metOverSqrtHT>5.)cut_sigGt5=true;
        if(mT>120.)cut_mTGt120=true;
        if(mT>140.)cut_mTGt140=true;
        if(mT>180.)cut_mTGt180=true;
        if(mT>200.)cut_mTGt200=true;
        if(meff>500.)cut_meffGt550=true;
        if(meff>700.)cut_meffGt700=true;

        //Apply the basic preselection to save costly MT2 calculation
        if(!((cut_1SignalElectron || cut_1SignalMuon) && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2))return;
        //Do hadronic top reconstruction
        double mindR1=9999.;
        double mindR2=9999.;
        double index1=9999.;
        double index2=9999.;
        double index3=9999.;

        bool whad=false;
        bool Thad=false;
        double mHadTop=0;

        for(int iJet=0;iJet<nJets;iJet++){
          for(int jJet=0;jJet<nJets;jJet++){
            if(iJet != jJet){

	      HEPUtils::P4 iJetVec;
	      iJetVec.setXYZE(signalJets[iJet]->mom().px(),signalJets[iJet]->mom().py(),signalJets[iJet]->mom().pz(),signalJets[iJet]->E());


	      HEPUtils::P4 jJetVec;
	      jJetVec.setXYZE(signalJets[jJet]->mom().px(),signalJets[jJet]->mom().py(),signalJets[jJet]->mom().pz(),signalJets[jJet]->E());

              if(iJetVec.deltaR_eta(jJetVec) < mindR1 && (iJetVec+jJetVec).m() > 60.){
                mindR1 =iJetVec.deltaR_eta(jJetVec);
                index1 = iJet;
                index2 = jJet;
                whad   = true;
              }
            }
          }
        }
        if(whad){
          for(int kJet=0;kJet<nJets;kJet++){
            if(kJet !=index1 && kJet !=index2){


	      HEPUtils::P4 kJetVec;
	      kJetVec.setXYZE(signalJets[kJet]->mom().px(),signalJets[kJet]->mom().py(),signalJets[kJet]->mom().pz(),signalJets[kJet]->E());


	      HEPUtils::P4 JetVec1;
	      JetVec1.setXYZE(signalJets[index1]->mom().px(),signalJets[index1]->mom().py(),signalJets[index1]->mom().pz(),signalJets[index1]->E());


	      HEPUtils::P4 JetVec2;
	      JetVec2.setXYZE(signalJets[index2]->mom().px(),signalJets[index2]->mom().py(),signalJets[index2]->mom().pz(),signalJets[index2]->E());


              if(kJetVec.deltaR_eta(JetVec1+JetVec2)<mindR2 && (JetVec1+JetVec2+kJetVec).m() > 130.){
                mindR2=kJetVec.deltaR_eta(JetVec1+JetVec2);
                index3=kJet;
                Thad=true;
              }
            }
          }
        }
        if(Thad){

	  HEPUtils::P4 JetVec1;
	  JetVec1.setXYZE(signalJets[index1]->mom().px(),signalJets[index1]->mom().py(),signalJets[index1]->mom().pz(),signalJets[index1]->E());

	  HEPUtils::P4 JetVec2;
	  JetVec2.setXYZE(signalJets[index2]->mom().px(),signalJets[index2]->mom().py(),signalJets[index2]->mom().pz(),signalJets[index2]->E());

	  HEPUtils::P4 JetVec3;
	  JetVec3.setXYZE(signalJets[index3]->mom().px(),signalJets[index3]->mom().py(),signalJets[index3]->mom().pz(),signalJets[index3]->E());


          mHadTop = (JetVec1+JetVec2+JetVec3).m();
        }

        bool passHadTop=false;
        if(mHadTop>130. && mHadTop<205.)passHadTop=true;

        //if(passHadTop)cut_PassHadTop=true;

        //Do MT2 calculations (note: do these last, since they are slowest)

        MT2 mt2s = MT2helper(signalJets,signalElectrons,signalMuons,ptot);

        double amt2 = mt2s.aMT2_BM;
        double mt2tau = mt2s.MT2tauB;

        //std::cout<<amt2<<" "<<mt2tau<<std::endl;

        if(cut_1SignalElectron && cut_4jets && cut_Btag) {
          cutFlowVector_alt[0]++;
          if(mHadTop<205.) {
            cutFlowVector_alt[1]++;
            if(cut_dPhiJet1) {
              cutFlowVector_alt[2]++;
              if(cut_mTGt180) {
                cutFlowVector_alt[3]++;
                if(cut_sigGt11) {
                  cutFlowVector_alt[4]++;
                  if(amt2>200.) {
                    cutFlowVector_alt[5]++;
                    if(mt2tau>120.) {
                      cutFlowVector_alt[6]++;
                    }
                  }
                }
              }
            }
          }
        }

        //double amt2=0;
        //double mt2tau=0;

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "Electron (=1 signal) ";
        cutFlowVector_str[2] = "4 jets (80, 60, 40, 25) ";
        cutFlowVector_str[3] = ">=1 b. tag ";
        cutFlowVector_str[4] = "ETmiss > 100 GeV [all SRs] ";
        cutFlowVector_str[5] = "ETmiss / sqrt(HT) > 5 [all SRs] ";
        cutFlowVector_str[6] = "dPhi(jet2,MET) > 0.8 [all SRs] ";
        cutFlowVector_str[7] = "dPhi(jet1,MET) > 0.8 [not SRtN2] ";
        cutFlowVector_str[8] = "ETmiss > 200 GeV (SRtN2) ";
        cutFlowVector_str[9] = "ETmiss / sqrt(HT) > 13 (SRtN2) ";
        cutFlowVector_str[10] = "mT > 140 GeV (SRtN2) ";
        cutFlowVector_str[11] = "ETmiss > 275 GeV (SRtN3) ";
        cutFlowVector_str[12] = "ETmiss / sqrt(HT) > 11 (SRtN3) ";
        cutFlowVector_str[13] = "mT > 200 GeV (SRtN3) ";
        cutFlowVector_str[14] = "ETmiss > 150 GeV (SRbC1-SRbC3) ";
        cutFlowVector_str[15] = "ETmiss / sqrt(HT) > 7 (SRbC1-SRbC3) ";
        cutFlowVector_str[16] = "mT > 120 GeV (SRbC1-SRbC3) ";
        cutFlowVector_str[17] = "ETmiss > 160 GeV (SRbC2,SRbC3) ";
        cutFlowVector_str[18] = "ETmiss / sqrt(HT) > 8 (SRbC2,SRbC3) ";
        cutFlowVector_str[19] = "meff > 550 GeV (SRbC2) ";
        cutFlowVector_str[20] = "meff > 700 GeV (SRbC3) ";

        cutFlowVector_str[21] = "Muon (=1 signal) ";
        cutFlowVector_str[22] = "4 jets (80, 60, 40, 25) ";
        cutFlowVector_str[23] = ">=1 b. tag ";
        cutFlowVector_str[24] = "ETmiss > 100 GeV [all SRs] ";
        cutFlowVector_str[25] = "ETmiss / sqrt(HT) > 5 [all SRs] ";
        cutFlowVector_str[26] = "dPhi(jet2,MET) > 0.8 [all SRs] ";
        cutFlowVector_str[27] = "dPhi(jet1,MET) > 0.8 [not SRtN2] ";
        cutFlowVector_str[28] = "ETmiss > 200 GeV (SRtN2) ";
        cutFlowVector_str[29] = "ETmiss / sqrt(HT) > 13 (SRtN2) ";
        cutFlowVector_str[30] = "mT > 140 GeV (SRtN2) ";
        cutFlowVector_str[31] = "ETmiss > 275 GeV (SRtN3) ";
        cutFlowVector_str[32] = "ETmiss / sqrt(HT) > 11 (SRtN3) ";
        cutFlowVector_str[33] = "mT > 200 GeV (SRtN3) ";
        cutFlowVector_str[34] = "ETmiss > 150 GeV (SRbC1-SRbC3) ";
        cutFlowVector_str[35] = "ETmiss / sqrt(HT) > 7 (SRbC1-SRbC3) ";
        cutFlowVector_str[36] = "mT > 120 GeV (SRbC1-SRbC3) ";
        cutFlowVector_str[37] = "ETmiss > 160 GeV (SRbC2,SRbC3) ";
        cutFlowVector_str[38] = "ETmiss / sqrt(HT) > 8 (SRbC2,SRbC3) ";
        cutFlowVector_str[39] = "meff > 550 GeV (SRbC2) ";
        cutFlowVector_str[40] = "meff > 700 GeV (SRbC3) ";


        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             //Electron cutflow
             (j==1 && cut_1SignalElectron) ||

             (j==2 && cut_1SignalElectron && cut_4jets) ||

             (j==3 && cut_1SignalElectron && cut_4jets && cut_Btag) ||

             (j==4 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100) ||

             (j==5 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5) ||

             (j==6 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2) ||

             (j==7 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1) ||

             //SRtN2 - no cut_dPhiJet1

             (j==8 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200) ||

             (j==9 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200 && cut_sigGt13) ||

             (j==10 && cut_1SignalElectron && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200 && cut_sigGt13 && cut_mTGt140) ||

             //SRtN3

             (j==11 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275 ) ||

             (j==12 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275 && cut_sigGt11) ||

             (j==13 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275 && cut_sigGt11 && cut_mTGt200) ||

             //SRbC1 - SRbC3

             (j==14 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150) ||

             (j==15 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7) ||

             (j==16 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120) ||

             (j==17 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160) ||

             (j==18 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8) ||

             (j==19 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8 && cut_meffGt550) ||

             (j==20 && cut_1SignalElectron && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8 && cut_meffGt700) ||

             //Muon cutflow

             (j==21 && cut_1SignalMuon) ||

             (j==22 && cut_1SignalMuon && cut_4jets) ||

             (j==23 && cut_1SignalMuon && cut_4jets && cut_Btag) ||

             (j==24 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100) ||

             (j==25 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5) ||

             (j==26 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2) ||

             (j==27 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1) ||

             //SRtN2 - no cut_dPhiJet1

             (j==28 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200) ||

             (j==29 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200 && cut_sigGt13) ||

             (j==30 && cut_1SignalMuon && cut_4jets && cut_Btag && cut_METGt100 && cut_sigGt5 && cut_dPhiJet2 && cut_METGt200 && cut_sigGt13 && cut_mTGt140) ||

             //SRtN3

             (j==31 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275) ||

             (j==32 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275 && cut_sigGt11) ||

             (j==33 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt275 && cut_sigGt11 && cut_mTGt200) ||

             //SRbC1 - SRbC3

             (j==34 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150) ||

             (j==35 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7) ||

             (j==36 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120) ||

             (j==37 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160) ||

             (j==38 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8) ||

             (j==39 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8 && cut_meffGt550) ||

             (j==40 && cut_1SignalMuon && cut_4jets && cut_sigGt5 && cut_dPhiJet2 && cut_dPhiJet1 && cut_Btag && cut_METGt150 && cut_sigGt7 && cut_mTGt120 && cut_METGt160 && cut_sigGt8 && cut_meffGt700) )


            cutFlowVector[j]++;
        }

        //We're now ready to apply the cuts for each signal region
        //_numTN1Shape_bin1, _numTN1Shape_bin2, _numTN1Shape_bin3,_numTN2, _numTN3, _numBC1, _numBC2, _numBC3;

        //Do the three bins of the TN1 shape fit
        if(dphi_jetmet1>0.8 &&
           dphi_jetmet2>0.8 &&
           mT>140. && //use tightest mT bin only for now
           metOverSqrtHT>5. &&
           passHadTop &&
           nBjets >= 1 &&
           bJets[0]->pT()>25.){
          if(met>100. && met<125.) _numTN1Shape_bin1 += event->weight();
          if(met>125. && met<150.) _numTN1Shape_bin2 += event->weight();
          if(met>150.) _numTN1Shape_bin3 += event->weight();
        }

        //We're now ready to apply the cuts for each signal region
        //_numTN1Shape_bin1, _numTN1Shape_bin2, _numTN1Shape_bin3,_numTN2, _numTN3, _numBC1, _numBC2, _numBC3;

        //Do the three bins of the TN1 shape fit
        if(nBjets>=1) {
          if(dphi_jetmet1>0.8 &&
             dphi_jetmet2>0.8 &&
             mT>140. && //use tightest mT bin only for now
             metOverSqrtHT>5. &&
             passHadTop &&
             nBjets >= 1 &&
             bJets[0]->pT()>25.){

            if(met>100. && met<125.) _numTN1Shape_bin1 += event->weight();
            if(met>125. && met<150.) _numTN1Shape_bin2 += event->weight();
            if(met>150.) _numTN1Shape_bin3 += event->weight();
          }
        }

        //Do SRtN2
        if(nBjets>=1) {
          if(dphi_jetmet2>0.8 &&
             met>200. &&
             metOverSqrtHT>13. &&
             mT>140. &&
             amt2>170. &&
             passHadTop &&
             bJets[0]->pT()>25.) _numTN2 += event->weight();
        }

        //Do SRtN3
        if(nBjets>=1) {
          if(dphi_jetmet1>0.8 &&
             dphi_jetmet2>0.8 &&
             met>275. &&
             metOverSqrtHT>11. &&
             mT>200. &&
             amt2>175. &&
             mt2tau>80. &&
             passHadTop &&
             bJets[0]->pT()>25.) _numTN3 += event->weight();
        }

        //Do SRbC1
        if(nBjets>=1) {
          if(dphi_jetmet1>0.8 &&
             dphi_jetmet2>0.8 &&
             met>150. &&
             metOverSqrtHT>7. &&
             mT>120. &&
             bJets[0]->pT()>25.) _numBC1 += event->weight();
        }

        //Do SRbC2
        if(nBjets>=2) {
          if(dphi_jetmet1>0.8 &&
             dphi_jetmet2>0.8 &&
             met>160. &&
             metOverSqrtHT>8. &&
             mT>120. &&
             meff > 550. &&
             amt2>175. &&
             nBjets >=2 &&
             bJets[0]->pT()>100.&&
             bJets[1]->pT()>50) _numBC2 += event->weight();
        }

        //Do SRbC3
        if(nBjets>=2) {
          if(dphi_jetmet1>0.8 &&
             dphi_jetmet2>0.8 &&
             met>160. &&
             metOverSqrtHT>8. &&
             mT>120. &&
             meff > 700. &&
             amt2>200. &&
             nBjets >=2 &&
             bJets[0]->pT()>120.&&
             bJets[1]->pT()>90) _numBC3 += event->weight();
        }
        return;
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_8TeV_1LEPStop_20invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_8TeV_1LEPStop_20invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector.at(j);
          cutFlowVector_str[j] = specificOther->cutFlowVector_str.at(j);
          cutFlowVector_alt[j] += specificOther->cutFlowVector_alt.at(j);
        }
        _numTN1Shape_bin1 += specificOther->_numTN1Shape_bin1;
        _numTN1Shape_bin2 += specificOther->_numTN1Shape_bin2;
        _numTN1Shape_bin3 += specificOther->_numTN1Shape_bin3;
        _numTN2 += specificOther->_numTN2;
        _numTN3 += specificOther->_numTN3;
        _numBC1 += specificOther->_numBC1;
        _numBC2 += specificOther->_numBC2;
        _numBC3 += specificOther->_numBC3;
      }


      void collect_results() {
        //Note: am not using shape fit bins
        //They need to be added (but will probably update to paper result)

        // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

        add_result(SignalRegionData("BC1", 456., {_numBC1, 0.}, {482., 76.}));
        add_result(SignalRegionData("BC2", 25., {_numBC2, 0.}, {18., 5.}));
        add_result(SignalRegionData("BC3", 6., {_numBC3, 0.}, {7., 3.}));
        add_result(SignalRegionData("TN2", 14., {_numTN2, 0.}, {13., 3.}));
        add_result(SignalRegionData("TN3", 7., {_numTN3, 0.}, {5., 2.}));

        return;
      }


    protected:
      void analysis_specific_reset() {
        _numTN1Shape_bin1 = 0; _numTN1Shape_bin2 = 0; _numTN1Shape_bin3 = 0;
        _numTN2 = 0; _numTN3 = 0; _numBC1 = 0;
        _numBC2 = 0; _numBC3 = 0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_1LEPStop_20invfb)


  }
}
