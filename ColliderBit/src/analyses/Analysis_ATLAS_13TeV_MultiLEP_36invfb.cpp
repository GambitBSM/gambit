///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2018 June
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2016-24/

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is a base class for three SR-specific analysis classes
    // defined further down:
    // - Analysis_ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb
    // - Analysis_ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb
    // - Analysis_ATLAS_13TeV_MultiLEP_3Lep_36invfb
    class Analysis_ATLAS_13TeV_MultiLEP_36invfb : public Analysis {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SR2_SF_loose", 0},
        {"SR2_SF_tight", 0},
        {"SR2_DF_100", 0},
        {"SR2_DF_150", 0},
        {"SR2_DF_200", 0},
        {"SR2_DF_300", 0},
        {"SR2_int", 0},
        {"SR2_high", 0},
        {"SR2_low", 0},
        {"SR3_slep_a", 0},
        {"SR3_slep_b", 0},
        {"SR3_slep_c", 0},
        {"SR3_slep_d", 0},
        {"SR3_slep_e", 0},
        {"SR3_WZ_0Ja", 0},
        {"SR3_WZ_0Jb", 0},
        {"SR3_WZ_0Jc", 0},
        {"SR3_WZ_1Ja", 0},
        {"SR3_WZ_1Jb", 0},
        {"SR3_WZ_1Jc", 0}
      };

    private:

      vector<int> cutFlowVector1;
      vector<string> cutFlowVector1_str;
      size_t NCUTS1;
      // vector<double> cutFlowVector1ATLAS_200_100;
      // double xsec1ATLAS_200_100;

      vector<int> cutFlowVector2;
      vector<string> cutFlowVector2_str;
      size_t NCUTS2;
      // vector<double> cutFlowVector2ATLAS_400_200;
      // double xsec2ATLAS_400_200;
      // vector<double> cutFlowVector2ATLAS_500_100;
      // double xsec2ATLAS_500_100;

      vector<int> cutFlowVector3;
      vector<string> cutFlowVector3_str;
      size_t NCUTS3;
      // vector<double> cutFlowVector3ATLAS_200_100;
      // double xsec3ATLAS_200_100;

      vector<int> cutFlowVector4;
      vector<string> cutFlowVector4_str;
      size_t NCUTS4;
      // vector<double> cutFlowVector4ATLAS_800_600;
      // double xsec4ATLAS_800_600;

      vector<int> cutFlowVector5;
      vector<string> cutFlowVector5_str;
      size_t NCUTS5;
      // vector<double> cutFlowVector5ATLAS_401_1;
      // double xsec5ATLAS_401_1;
      // vector<double> cutFlowVector5ATLAS_300_150;
      // double xsec5ATLAS_300_150;

      // ofstream cutflowFile;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_MultiLEP_36invfb() {

        set_analysis_name("ATLAS_13TeV_MultiLEP_36invfb");
        set_luminosity(36.1);

        NCUTS1=22;


        // xsec1ATLAS_200_100=1807.4;
        for (size_t i=0;i<NCUTS1;i++){
          cutFlowVector1.push_back(0);
          // cutFlowVector1ATLAS_200_100.push_back(0);
          cutFlowVector1_str.push_back("");
        }

        NCUTS2=14;
        // xsec2ATLAS_400_200=121.0269;
        // xsec2ATLAS_500_100=46.3576;
        for (size_t i=0;i<NCUTS2;i++){
          cutFlowVector2.push_back(0);
          // cutFlowVector2ATLAS_400_200.push_back(0);
          // cutFlowVector2ATLAS_500_100.push_back(0);
          cutFlowVector2_str.push_back("");
        }

        NCUTS3=24;
        // xsec3ATLAS_200_100=1807.4;
        for (size_t i=0;i<NCUTS3;i++){
          cutFlowVector3.push_back(0);
          // cutFlowVector3ATLAS_200_100.push_back(0);
          cutFlowVector3_str.push_back("");
        }

        NCUTS4=12;
        // xsec4ATLAS_800_600=3.803;
        for (size_t i=0;i<NCUTS4;i++){
          cutFlowVector4.push_back(0);
          // cutFlowVector4ATLAS_800_600.push_back(0);
          cutFlowVector4_str.push_back("");
        }

        NCUTS5=11;
        // xsec5ATLAS_401_1=5.43;
        // xsec5ATLAS_300_150=190.159;
        for (size_t i=0;i<NCUTS5;i++){
          cutFlowVector5.push_back(0);
          // cutFlowVector5ATLAS_401_1.push_back(0);
          // cutFlowVector5ATLAS_300_150.push_back(0);
          cutFlowVector5_str.push_back("");
        }

      }

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison {
        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      void run(const HEPUtils::Event* event) {

        double met = event->met();

        // Baseline objects
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT()>10. && electron->abseta()<2.47)baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Apply loose electron selection
        ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);

        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT()>10. && muon->abseta()<2.7)baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT()>20. && jet->abseta()<4.5)baselineJets.push_back(jet);
        }

        //Overlap Removal + Signal Objects
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Particle*> signalLeptons;
        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> signalBJets;

        const vector<double> aBJet={0,10.};
        const vector<double> bBJet={0,30., 40., 50., 70., 80., 90., 100.,150., 200., 10000.};
        const vector<double> cBJet={0.63, 0.705, 0.745, 0.76, 0.775, 0.79,0.795, 0.805, 0.795, 0.76};
        HEPUtils::BinnedFn2D<double> _eff2d(aBJet,bBJet,cBJet);

        vector<HEPUtils::Jet*> overlapJet;
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          vector<HEPUtils::Particle*> overlapEl;
          bool hasTag=has_tag(_eff2d, baselineJets.at(iJet)->eta(), baselineJets.at(iJet)->pT());
          for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
            if (baselineElectrons.at(iEl)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.2)overlapEl.push_back(baselineElectrons.at(iEl));
          }
          if (overlapEl.size()>0 && (baselineJets.at(iJet)->btag() && hasTag)) {
            for (size_t iO=0;iO<overlapEl.size();iO++) {
              baselineElectrons.erase(remove(baselineElectrons.begin(), baselineElectrons.end(), overlapEl.at(iO)), baselineElectrons.end());
            }
          }
          if (overlapEl.size()>0 && !(baselineJets.at(iJet)->btag() && hasTag))overlapJet.push_back(baselineJets.at(iJet));
        }
        for (size_t iO=0;iO<overlapJet.size();iO++) {
          baselineJets.erase(remove(baselineJets.begin(), baselineJets.end(), overlapJet.at(iO)), baselineJets.end());
        }

        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
          bool overlap=false;
          for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
            if (baselineElectrons.at(iEl)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4)overlap=true;
          }
          if (!overlap)signalElectrons.push_back(baselineElectrons.at(iEl));
        }
        ATLAS::applyMediumIDElectronSelectionR2(signalElectrons);

        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
            if (baselineMuons.at(iMu)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.2 && baselineMuons.at(iMu)->pT()>0.7*baselineJets.at(iJet)->pT())overlap=true;
          }
          if (!overlap) {
            bool hasTag=has_tag(_eff2d, baselineJets.at(iJet)->eta(), baselineJets.at(iJet)->pT());
            if(baselineJets.at(iJet)->abseta()<2.4)signalJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->btag() && hasTag && baselineJets.at(iJet)->abseta()<2.4)signalBJets.push_back(baselineJets.at(iJet));
          }
        }

        for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
          bool overlap=false;
          for (size_t iJet=0;iJet<signalJets.size();iJet++) {
            if (baselineMuons.at(iMu)->mom().deltaR_eta(signalJets.at(iJet)->mom())<0.4)overlap=true;
          }
          if (!overlap)signalMuons.push_back(baselineMuons.at(iMu));
        }

        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        sort(signalJets.begin(),signalJets.end(),compareJetPt);
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
        size_t nBaselineLeptons=baselineElectrons.size()+baselineMuons.size();
        size_t nSignalLeptons=signalLeptons.size();
        size_t nSignalJets=signalJets.size();
        size_t nSignalBJets=signalBJets.size();

        vector<vector<HEPUtils::Particle*>> SFOSpairs=getSFOSpairs(signalLeptons);
        vector<vector<HEPUtils::Particle*>> OSpairs=getOSpairs(signalLeptons);

        //Variables
        double pT_l0=0.;
        double pT_l1=0.;
        double pT_l2=0.;
        // double mlll=0.;
        double pTlll=999.;
        double mll=999.;
        double mT2=0;
        double deltaR_ll=999.;

        double pT_j0=0.;
        double pT_j1=0.;
        double pT_j2=0.;
        double mjj=0;
        double deltaR_jj=999.;

        HEPUtils::P4 Z;
        double deltaPhi_met_Z=999.;

        HEPUtils::P4 W;
        vector<HEPUtils::P4> W_ISR;
        double deltaPhi_met_W=0.;
        double deltaPhi_met_ISR=0.;
        double deltaPhi_met_jet0=0.;

        double mTmin=999;
        double mSFOS=999;

        bool central_jet_veto=true;
        bool bjet_veto=false;

        for (size_t iJet=0;iJet<nSignalJets;iJet++) {
          if (signalJets.at(iJet)->pT()>60 && signalJets.at(iJet)->abseta()<2.4)central_jet_veto=false;
        }
        if (nSignalBJets==0)bjet_veto=true;

        if (nSignalLeptons>0)pT_l0=signalLeptons.at(0)->pT();
        if (nSignalLeptons>1) {
          pT_l1=signalLeptons.at(1)->pT();
          mll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).m();
          deltaR_ll=signalLeptons.at(0)->mom().deltaR_eta(signalLeptons.at(1)->mom());

          double pLep1[3] = {signalLeptons.at(0)->mass(), signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py()};
          double pLep2[3] = {signalLeptons.at(1)->mass(), signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py()};
          double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep1,pLep2,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();

          Z=signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom();
          deltaPhi_met_Z=Z.deltaPhi(event->missingmom());
          for (size_t iPa=0;iPa<SFOSpairs.size();iPa++) {
            for (size_t iLep=0;iLep<signalLeptons.size();iLep++) {
              if (signalLeptons.at(iLep)!=SFOSpairs.at(iPa).at(0) && signalLeptons.at(iLep)!=SFOSpairs.at(iPa).at(1)) {
                double mT=sqrt(2*signalLeptons.at(iLep)->pT()*met*(1-cos(signalLeptons.at(iLep)->mom().deltaPhi(event->missingmom()))));
                if (mT<mTmin) {
                  mTmin=mT;
                  mSFOS=(SFOSpairs.at(iPa).at(0)->mom()+SFOSpairs.at(iPa).at(1)->mom()).m();
                }
              }
            }
          }
        }

        if (nSignalLeptons>2) {
          pT_l2=signalLeptons.at(2)->pT();
          // mlll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()+signalLeptons.at(2)->mom()).m();
          pTlll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()+signalLeptons.at(2)->mom()).pT();
        }

        if (nSignalJets>0) {
          pT_j0=signalJets.at(0)->pT();
          deltaPhi_met_jet0=signalJets.at(0)->mom().deltaPhi(event->missingmom());
        }
        if (nSignalJets>1) {
          pT_j1=signalJets.at(1)->pT();
          if (nSignalJets<3 && bjet_veto) {
            W=signalJets.at(0)->mom()+signalJets.at(1)->mom();
            mjj=W.m();
            deltaR_jj=signalJets.at(0)->mom().deltaR_eta(signalJets.at(1)->mom());
            deltaPhi_met_W=W.deltaPhi(event->missingmom());
          }
          if (nSignalJets>2 && nSignalJets<6 && nSignalLeptons>1 && bjet_veto) {
            W_ISR=get_W_ISR(signalJets,Z,event->missingmom());
            W=W_ISR.at(0);
            mjj=W.m();
            deltaR_jj=W_ISR.at(3).deltaR_eta(W_ISR.at(2));
            deltaPhi_met_W=W.deltaPhi(event->missingmom());
            deltaPhi_met_ISR=W_ISR.at(1).deltaPhi(event->missingmom());
          }
        }
        if (nSignalJets>2)pT_j2=signalJets.at(2)->pT();

        bool preselection=false;
        if ((nSignalLeptons==2 || nSignalLeptons==3) && nBaselineLeptons==nSignalLeptons && pT_l0>25 && pT_l1>20)preselection=true;


        // Signal Regions

        //2lep+0jet
        if (preselection && nSignalLeptons==2 && OSpairs.size()==1 && mll>40 && central_jet_veto && bjet_veto) {
          if (SFOSpairs.size()==1) {
            if (mT2>100 && mll>111) _numSR["SR2_SF_loose"]++;
            if (mT2>130 && mll>300) _numSR["SR2_SF_tight"]++;
          }
          if (SFOSpairs.size()==0) {
            if (mT2>100 && mll>111) _numSR["SR2_DF_100"]++;
            if (mT2>150 && mll>111) _numSR["SR2_DF_150"]++;
            if (mT2>200 && mll>111) _numSR["SR2_DF_200"]++;
            if (mT2>300 && mll>111) _numSR["SR2_DF_300"]++;
          }
        }

        //2lep+jets
        if (preselection && nSignalLeptons==2 && SFOSpairs.size()==1 && bjet_veto && nSignalJets>1 && pT_j0>30 && pT_j1>30 && pT_l1>25) {
          //SR2_int + SR2_high
          if (mll>81. && mll<101. && mjj>70. && mjj<100. && Z.pT()>80. && W.pT()>100. && mT2>100. && deltaR_jj<1.5 && deltaR_ll<1.8 && deltaPhi_met_W>0.5 && deltaPhi_met_W<3.0) {
            if (met>150) _numSR["SR2_int"]++;
            if (met>250) _numSR["SR2_high"]++;
          }
          //SR2_low_2J
          if (nSignalJets==2 && mll>81. && mll<101. && mjj>70. && mjj<90. && met>100. && Z.pT()>60. && deltaPhi_met_Z<0.8 && deltaPhi_met_W>1.5 && (met/Z.pT())>0.6 && (met/Z.pT())<1.6 && (met/W.pT())<0.8) _numSR["SR2_low"]++;
          //SR2_low_3J
          if (nSignalJets>2 && nSignalJets<6 && mll>86 && mll<96 && mjj>70. && mjj<90. && met>100 && Z.pT()>40 && deltaR_jj<2.2 && deltaPhi_met_W<2.2 && deltaPhi_met_ISR>2.4 && deltaPhi_met_jet0>2.6 && (met/W_ISR.at(1).pT())>0.4 && (met/W_ISR.at(1).pT())<0.8 && Z.abseta()<1.6 && pT_j2>30.) _numSR["SR2_low"]++;
        }

        //3lep
        if (preselection && nSignalLeptons==3 && bjet_veto && SFOSpairs.size()) {
          if (mSFOS<81.2 && met>130. && mTmin>110.) {
            if (pT_l2>20. && pT_l2<30.) _numSR["SR3_slep_a"]++;
            if (pT_l2>30.) _numSR["SR3_slep_b"]++;
          }
          if (mSFOS>101.2 && met>130. && mTmin>110.) {
            if (pT_l2>20. && pT_l2<50.) _numSR["SR3_slep_c"]++;
            if (pT_l2>50. && pT_l2<80.) _numSR["SR3_slep_d"]++;
            if (pT_l2>80.) _numSR["SR3_slep_e"]++;
          }
          if (mSFOS>81.2 && mSFOS<101.2 && nSignalJets==0 && mTmin>110.) {
            if (met>60. && met<120.) _numSR["SR3_WZ_0Ja"]++;
            if (met>120. && met<170.) _numSR["SR3_WZ_0Jb"]++;
            if (met>170.) _numSR["SR3_WZ_0Jc"]++;
          }
          if (mSFOS>81.2 && mSFOS<101.2 && nSignalJets>0) {
            if (met>120. && met<200. && mTmin>110. && pTlll<120. && pT_j1>70.) _numSR["SR3_WZ_1Ja"]++;
            if (met>200. && mTmin>110. && mTmin<160.) _numSR["SR3_WZ_1Jb"]++;
            if (met>200. && pT_l2>35. && mTmin>160.) _numSR["SR3_WZ_1Jc"]++;
          }
        }

        // if (analysis_name().find("200_100") != string::npos) {

 //       cutFlowVector1_str[0] = "All events";
 //          cutFlowVector1_str[1] = "$\\geq$ 2 signal leptons \\& SFOS";
 //          cutFlowVector1_str[2] = "3 signal leptons \\& extra lepton veto";
 //          cutFlowVector1_str[3] = "B-jet veto";
 //          cutFlowVector1_str[4] = "$p_{T}^{l0} > 25 GeV$";
 //          cutFlowVector1_str[5] = "$p_{T}^{l2} > 20 GeV$";
 //          cutFlowVector1_str[6] = "$m_{lll} > 20 GeV$";
 //          cutFlowVector1_str[7] = "$| m_{ll} - m_{Z} | < 10 GeV$";
 //          cutFlowVector1_str[8] = "0 jets";
 //          cutFlowVector1_str[9] = "$60 < E^{miss}_{T} < 120 GeV$";
 //          cutFlowVector1_str[10] = "$m_{T}^{min} > 110 GeV$";
 //          cutFlowVector1_str[11] = "$120 < E^{miss}_{T} < 170 GeV$";
 //          cutFlowVector1_str[12] = "$m_{T}^{min} > 110 GeV$";
 //          cutFlowVector1_str[13] = "$E^{miss}_{T} > 170 GeV$";
 //          cutFlowVector1_str[14] = "$m_{T}^{min} > 110 GeV$";
 //          cutFlowVector1_str[15] = "$\\geq$ 1 jet";
 //          cutFlowVector1_str[16] = "$120 < E^{miss}_{T} < 200 GeV$";
 //          cutFlowVector1_str[17] = "$m_{T}^{min} > 110 GeV$";
 //          cutFlowVector1_str[18] = "$p_{T}^{lll} < 120 GeV$";
 //          cutFlowVector1_str[19] = "$p_{T}^{j0} > 70 GeV$";
 //          cutFlowVector1_str[20] = "$E^{miss}_{T} > 200 GeV$";
 //          cutFlowVector1_str[21] = "$110 < m_{T}^{min} < 160 GeV$";

 //          cutFlowVector1ATLAS_200_100[0]=17682.;
        //   cutFlowVector1ATLAS_200_100[1]=425.63;
 //       cutFlowVector1ATLAS_200_100[2]=424.59;
        //   cutFlowVector1ATLAS_200_100[3]=414.43;
        //   cutFlowVector1ATLAS_200_100[4]=413.98;
        //   cutFlowVector1ATLAS_200_100[5]=306.91;
        //   cutFlowVector1ATLAS_200_100[6]=301.70;
        //   cutFlowVector1ATLAS_200_100[7]=227.15;
        //   cutFlowVector1ATLAS_200_100[8]=110.35;
        //   cutFlowVector1ATLAS_200_100[9]=43.24;
        //   cutFlowVector1ATLAS_200_100[10]=8.91;
        //   cutFlowVector1ATLAS_200_100[11]=6.02;
        //   cutFlowVector1ATLAS_200_100[12]=1.1;
        //   cutFlowVector1ATLAS_200_100[13]=3.15;
        //   cutFlowVector1ATLAS_200_100[14]=0.49;
        //   cutFlowVector1ATLAS_200_100[15]=116.81;
        //   cutFlowVector1ATLAS_200_100[16]=18.86;
        //   cutFlowVector1ATLAS_200_100[17]=5.8;
        //   cutFlowVector1ATLAS_200_100[18]=4.63;
        //   cutFlowVector1ATLAS_200_100[19]=3.18;
        //   cutFlowVector1ATLAS_200_100[20]=7.32;
        //   cutFlowVector1ATLAS_200_100[21]=1.85;

   //        for (size_t j=0;j<NCUTS1;j++){
   //          if(
   //            (j==0) ||

          //     (j==1 && nSignalLeptons>=2 && SFOSpairs.size()>0) ||

          //     (j==2 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3) ||

          //     (j==3 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto) ||

          //     (j==4 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25.) ||

          //     (j==5 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20.) ||

          //     (j==6 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20.) ||

          //     (j==7 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10.) ||

          //     (j==8 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets==0) ||

          //     (j==9 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && met>60. && met<120. && nSignalJets==0) ||

          //     (j==10 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && met>60. && met<120.&& nSignalJets==0 && mTmin>110.) ||

          //     (j==11 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets==0 && met>120. && met<170.) ||

          //     (j==12 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets==0 && met>120. && met<170. && mTmin>110.) ||

          //     (j==13 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets==0 && met>170.) ||

          //     (j==14 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets==0 && met>170. && mTmin>110.) ||

          //     (j==15 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0) ||

          //     (j==16 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>120. && met<200.) ||

          //     (j==17 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>120. && met<200. && mTmin>110.) ||

          //     (j==18 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>120. && met<200. && mTmin>110. && pTlll<120.) ||

          //     (j==19 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>120. && met<200. && mTmin>110. && pTlll<120. && pT_j0>70.) ||

          //     (j==20 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>200.) ||

          //     (j==21 && nSignalLeptons>=2 && SFOSpairs.size()>0 && nSignalLeptons==3 && nBaselineLeptons==3 && bjet_veto && pT_l0>25. && pT_l2>20. && mlll>20. && fabs(mSFOS-91.2)<10. && nSignalJets>0 && met>200. && mTmin>110. && mTmin<160.) )

          //     cutFlowVector1[j]++;
          // }

          // cutFlowVector3_str[0] = "All events";
          // cutFlowVector3_str[1] = "2 signal leptons \\& SFOS";
          // cutFlowVector3_str[2] = "B-jet veto";
          // cutFlowVector3_str[3] = "$E_{T}^{miss} > 100 GeV$";
          // cutFlowVector3_str[4] = "2 signal jets";
          // cutFlowVector3_str[5] = "$p_{T}^{j0}, p_{T}^{j1} > 30 GeV$";
          // cutFlowVector3_str[6] = "$81 < m_{Z} < 101 GeV$";
          // cutFlowVector3_str[7] = "$70 < m_{W} < 90 GeV$";
          // cutFlowVector3_str[8] = "$p_{T}^{Z} > 60 GeV$";
          // cutFlowVector3_str[9] = "$\\Delta\\phi(E_{T}^{miss},Z) < 0.8$";
          // cutFlowVector3_str[10] = "$\\Delta\\phi(E_{T}^{miss},W) > 1.5$";
          // cutFlowVector3_str[11] = "$E_{T}^{miss}/p_{T}^{W} < 0.8$";
          // cutFlowVector3_str[12] = "$0.6 < E_{T}^{miss}/p_{T}^{Z} < 1.6$";
          // cutFlowVector3_str[13] = "3-5 signal jets";
          // cutFlowVector3_str[14] = "$p_{T}^{j0}, p_{T}^{j1}, p_{T}^{j2} > 30 GeV$";
          // cutFlowVector3_str[15] = "$81 < m_{Z} < 101 GeV$";
          // cutFlowVector3_str[16] = "$70 < m_{W} < 90 GeV$";
          // cutFlowVector3_str[17] = "$||\\eta (Z)|| < 1.6$";
          // cutFlowVector3_str[18] = "$p_{T}^{Z} > 40 GeV$";
          // cutFlowVector3_str[19] = "$\\Delta\\phi (E_{T}^{miss},ISR) > 2.4$";
          // cutFlowVector3_str[20] = "$\\Delta\\phi (E_{T}^{miss},j1) > 2.6$";
          // cutFlowVector3_str[21] = "$\\Delta\\phi (E_{T}^{miss},W) < 2.2$ ";
          // cutFlowVector3_str[22] = "$0.4 < E_{T}^{miss}/ISR < 0.8$";
          // cutFlowVector3_str[23] = "$\\Delta R(W\\rightarrow 2j) < 2.2$";

     //      cutFlowVector3ATLAS_200_100[0]=20000.;
     //      cutFlowVector3ATLAS_200_100[1]=957.;
     //      cutFlowVector3ATLAS_200_100[2]=880.6;
     //      cutFlowVector3ATLAS_200_100[3]=120.8;
     //      cutFlowVector3ATLAS_200_100[4]=30.2;
     //      cutFlowVector3ATLAS_200_100[5]=20.6;
     //      cutFlowVector3ATLAS_200_100[6]=18.8;
     //      cutFlowVector3ATLAS_200_100[7]=6.2;
     //      cutFlowVector3ATLAS_200_100[8]=5.1;
     //      cutFlowVector3ATLAS_200_100[9]=2.7;
     //      cutFlowVector3ATLAS_200_100[10]=2.7;
     //      cutFlowVector3ATLAS_200_100[11]=2.6;
     //      cutFlowVector3ATLAS_200_100[12]=2.2;
     //      cutFlowVector3ATLAS_200_100[13]=71.7;
     //      cutFlowVector3ATLAS_200_100[14]=47.9;
     //      cutFlowVector3ATLAS_200_100[15]=37.1;
     //      cutFlowVector3ATLAS_200_100[16]=9.3;
     //      cutFlowVector3ATLAS_200_100[17]=7.1;
     //      cutFlowVector3ATLAS_200_100[18]=6.9;
     //      cutFlowVector3ATLAS_200_100[19]=6.3;
     //      cutFlowVector3ATLAS_200_100[20]=5.3;
     //      cutFlowVector3ATLAS_200_100[21]=4.8;
     //      cutFlowVector3ATLAS_200_100[22]=4.0;
     //      cutFlowVector3ATLAS_200_100[23]=3.6;

 //          for (size_t j=0;j<NCUTS3;j++){
 //            if(
 //              (j==0) ||

        //       (j==1 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0) ||

        //       (j==2 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto) ||

        //       (j==3 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100.) ||

        //       (j==4 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2) ||

        //       (j==5 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30.) ||

        //       (j==6 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101.) ||

        //       (j==7 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90.) ||

        //       (j==8 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.pT()>60.) ||

        //       (j==9 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.pT()>60. && deltaPhi_met_Z<0.8) ||

        //       (j==10 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.pT()>60. && deltaPhi_met_Z<0.8 && deltaPhi_met_W>1.5) ||

        //       (j==11 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.pT()>60. && deltaPhi_met_Z<0.8 && deltaPhi_met_W>1.5 && met/W.pT()<0.8) ||

        //       (j==12 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets==2 && pT_j0>30. && pT_j1>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.pT()>60. && deltaPhi_met_Z<0.8 && deltaPhi_met_W>1.5 && met/W.pT()<0.8 && met/Z.pT()>0.6 && met/Z.pT()<1.6) ||

        //       (j==13 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6) ||

        //       (j==14 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30.) ||

        //       (j==15 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101.) ||

        //       (j==16 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90.) ||

        //       (j==17 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6) ||

        //       (j==18 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40.) ||

        //       (j==19 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40. && deltaPhi_met_ISR>2.4) ||

        //       (j==20 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40. && deltaPhi_met_ISR>2.4 && deltaPhi_met_jet0>2.6) ||

        //       (j==21 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40. && deltaPhi_met_ISR>2.4 && deltaPhi_met_jet0>2.6 && deltaPhi_met_W<2.2) ||

        //       (j==22 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40. && deltaPhi_met_ISR>2.4 && deltaPhi_met_jet0>2.6 && deltaPhi_met_W<2.2 && met/W_ISR.at(1).pT()>0.4 && met/W_ISR.at(1).pT()<0.8) ||

        //       (j==23 && preselection && pT_l1>25. && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && met>100. && nSignalJets>2 && nSignalJets<6 && pT_j0>30. && pT_j1>30. && pT_j2>30. && mll>81. && mll<101. && mjj>70. && mjj<90. && Z.abseta()<1.6 && Z.pT()>40. && deltaPhi_met_ISR>2.4 && deltaPhi_met_jet0>2.6 && deltaPhi_met_W<2.2 && met/W_ISR.at(1).pT()>0.4 && met/W_ISR.at(1).pT()<0.8 && deltaR_jj<2.2) )

        //       cutFlowVector3[j]++;
        //   }

        // }

        // if ((analysis_name().find("400_200") != string::npos) || (analysis_name().find("500_100") != string::npos)){

 //       cutFlowVector2_str[0] = "All events";
 //       cutFlowVector2_str[1] = "2 signal leptons \\& SFOS";
 //       cutFlowVector2_str[2] = "B-jet veto";
 //       cutFlowVector2_str[3] = "$\\geq$ 2 signal jets";
 //       cutFlowVector2_str[4] = "$p_{T}^{j0}, p_{T}^{j1} > 30 GeV$";
 //       cutFlowVector2_str[5] = "$E_{T}^{miss} > 150 GeV$";
 //       cutFlowVector2_str[6] = "$p_{T}^{Z} > 80 GeV$";
 //       cutFlowVector2_str[7] = "$p_{T}^{W} > 100 GeV$";
 //       cutFlowVector2_str[8] = "$ 81 < m_{Z} < 101 GeV$";
 //       cutFlowVector2_str[9] = "$70 < m_{W} < 100 GeV$";
 //       cutFlowVector2_str[10] = "$m_{T2} > 100 GeV$";
 //       cutFlowVector2_str[11] = "$0.5 < \\Delta\\phi(E_{T}^{miss}, W) < 3.0$";
 //       cutFlowVector2_str[12] = "$\\Delta R(W\\rightarrow jj) <1.5$";
 //       cutFlowVector2_str[13] = "$\\Delta R(Z\\rightarrow ll) <1.8$";

 //          cutFlowVector2ATLAS_400_200[0]=10000.;
 //          cutFlowVector2ATLAS_400_200[1]=83.1;
 //          cutFlowVector2ATLAS_400_200[2]=75.8;
 //          cutFlowVector2ATLAS_400_200[3]=64.7;
 //          cutFlowVector2ATLAS_400_200[4]=53.3;
 //          cutFlowVector2ATLAS_400_200[5]=29.8;
 //          cutFlowVector2ATLAS_400_200[6]=25.0;
 //          cutFlowVector2ATLAS_400_200[7]=20.3;
 //          cutFlowVector2ATLAS_400_200[8]=18.4;
 //          cutFlowVector2ATLAS_400_200[9]=7.7;
 //          cutFlowVector2ATLAS_400_200[10]=5.8;
 //          cutFlowVector2ATLAS_400_200[11]=5.5;
 //          cutFlowVector2ATLAS_400_200[12]=5.4;
 //          cutFlowVector2ATLAS_400_200[13]=5.2;

 //          cutFlowVector2ATLAS_500_100[0]=5000.;
 //          cutFlowVector2ATLAS_500_100[1]=37.9;
 //          cutFlowVector2ATLAS_500_100[2]=33.7;
 //          cutFlowVector2ATLAS_500_100[3]=28.9;
 //          cutFlowVector2ATLAS_500_100[4]=25.3;
 //          cutFlowVector2ATLAS_500_100[5]=20.5;
 //          cutFlowVector2ATLAS_500_100[6]=19.4;
 //          cutFlowVector2ATLAS_500_100[7]=17.5;
 //          cutFlowVector2ATLAS_500_100[8]=15.6;
 //          cutFlowVector2ATLAS_500_100[9]=7.4;
 //          cutFlowVector2ATLAS_500_100[10]=6.7;
 //          cutFlowVector2ATLAS_500_100[11]=5.9;
 //          cutFlowVector2ATLAS_500_100[12]=5.9;
 //          cutFlowVector2ATLAS_500_100[13]=5.9;
        // //maybe add pt_l1>25.
 //          for (size_t j=0;j<NCUTS2;j++){
 //            if(
 //              (j==0) ||

        //       (j==1 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0) ||

        //       (j==2 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto) ||

        //       (j==3 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2) ||

        //       (j==4 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30.) ||

        //       (j==5 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150.) ||

        //       (j==6 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80.) ||

        //       (j==7 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100.) ||

        //       (j==8 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101.) ||

        //       (j==9 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101. && mjj>70. && mjj<100.) ||

        //       (j==10 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101. && mjj>70. && mjj<100. && mT2>100.) ||

        //       (j==11 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101. && mjj>70. && mjj<100. && mT2>100. && deltaPhi_met_W>0.5 && deltaPhi_met_W<3.0) ||

        //       (j==12 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101. && mjj>70. && mjj<100. && mT2>100. && deltaPhi_met_W>0.5 && deltaPhi_met_W<3.0 && deltaR_jj<1.5) ||

        //       (j==13 && preselection && nSignalLeptons==2 && SFOSpairs.size()>0 && bjet_veto && nSignalJets>=2 && pT_j0>30. && pT_j1>30. && met>150. && Z.pT()>80. && W.pT()>100. && mll>81. && mll<101. && mjj>70. && mjj<100. && mT2>100. && deltaPhi_met_W>0.5 && deltaPhi_met_W<3.0 && deltaR_jj<1.5 && deltaR_ll<1.8) )

        //       cutFlowVector2[j]++;
        //   }
        // }

        // if (analysis_name().find("800_600") != string::npos){

 //       cutFlowVector4_str[0] = "All events";
 //       cutFlowVector4_str[1] = "3 signal leptons \\& SFOS";
 //       cutFlowVector4_str[2] = "Pass event cleaning";
 //       cutFlowVector4_str[3] = "$m_{T}^{min} > 110 GeV$";
 //       cutFlowVector4_str[4] = "$E_{T}^{miss} > 130 GeV$";
 //       cutFlowVector4_str[5] = "$m^{min}_{SFOS} < 81.2 GeV$";
 //       cutFlowVector4_str[6] = "$20 < p_{T}^{l2} < 30 GeV$";
 //       cutFlowVector4_str[7] = "$p_{T}^{l2} > 30 GeV$";
 //       cutFlowVector4_str[8] = "$m^{min}_{SFOS} > 101.2 GeV$";
 //       cutFlowVector4_str[9] = "$20 < p_{T}^{l2} < 50 GeV$";
 //       cutFlowVector4_str[10] = "$50 < p_{T}^{l2} < 80 GeV$";
 //       cutFlowVector4_str[11] = "$p_{T}^{l2} > 80 GeV$";

 //          // cutFlowVector4ATLAS_800_600[0]=9291.;
 //          // cutFlowVector4ATLAS_800_600[1]=25.13;
 //          // cutFlowVector4ATLAS_800_600[2]=23.54;
 //          // cutFlowVector4ATLAS_800_600[3]=14.43;
 //          // cutFlowVector4ATLAS_800_600[4]=10.22;
 //          // cutFlowVector4ATLAS_800_600[5]=2.10;
 //          // cutFlowVector4ATLAS_800_600[6]=0.11;
 //          // cutFlowVector4ATLAS_800_600[7]=1.99;
 //          // cutFlowVector4ATLAS_800_600[8]=6.8;
 //          // cutFlowVector4ATLAS_800_600[9]=2.53;
 //          // cutFlowVector4ATLAS_800_600[10]=3.01;
 //          // cutFlowVector4ATLAS_800_600[11]=1.25;

 //          for (size_t j=0;j<NCUTS4;j++){
 //            if(
 //              (j==0) ||

        //       (j==1 && nSignalLeptons==3 && SFOSpairs.size()>0) ||

        //       (j==2 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto) ||

        //       (j==3 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110.) ||

        //       (j==4 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130.) ||

        //       (j==5 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS<81.2) ||

        //       (j==6 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS<81.2 && pT_l2>20. && pT_l2<30.) ||

        //       (j==7 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS<81.2 && pT_l2>30.) ||

        //       (j==8 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS>101.2) ||

        //       (j==9 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS>101.2 && pT_l2>20. && pT_l2<50.) ||

        //       (j==10 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS>101.2 && pT_l2>50. && pT_l2<80.) ||

        //       (j==11 && nSignalLeptons==3 && SFOSpairs.size()>0 && preselection && bjet_veto && mTmin>110. && met>130. && mSFOS>101.2 && pT_l2>80.) )

        //       cutFlowVector4[j]++;
        //   }
        // }

        // if ((analysis_name().find("401_1") != string::npos) || (analysis_name().find("300_150") != string::npos)){

 //       cutFlowVector5_str[0] = "All events";
 //       cutFlowVector5_str[1] = "2 signal leptons \\& OS";
 //       cutFlowVector5_str[2] = "$p_{T}^{l0} > 25 GeV$";
 //       cutFlowVector5_str[3] = "Jet veto";
 //       cutFlowVector5_str[4] = "$m_{ll} > 40 GeV$";
 //       cutFlowVector5_str[5] = "Same flavour";
 //       cutFlowVector5_str[6] = "$m_{ll} > 111 GeV$";
 //       cutFlowVector5_str[7] = "$m_{T2} > 100 GeV$";
 //       cutFlowVector5_str[8] = "Different flavour";
 //       cutFlowVector5_str[9] = "$m_{ll} > 111 GeV$";
 //       cutFlowVector5_str[10] = "$m_{T2} > 100 GeV$";

 //          cutFlowVector5ATLAS_401_1[0]=10000.;
 //          cutFlowVector5ATLAS_401_1[1]=89.7;
 //          cutFlowVector5ATLAS_401_1[2]=89.7;
 //          cutFlowVector5ATLAS_401_1[3]=89.5;
 //          cutFlowVector5ATLAS_401_1[4]=55.7;
 //          cutFlowVector5ATLAS_401_1[5]=55.7;
 //          cutFlowVector5ATLAS_401_1[6]=53.7;
 //          cutFlowVector5ATLAS_401_1[7]=40.4;

 //          cutFlowVector5ATLAS_300_150[0]=25000;
 //          cutFlowVector5ATLAS_300_150[1]=1797.;
 //          cutFlowVector5ATLAS_300_150[2]=1795.3;
 //          cutFlowVector5ATLAS_300_150[3]=1692.1;
 //          cutFlowVector5ATLAS_300_150[4]=1262.;
 //          cutFlowVector5ATLAS_300_150[5]=667.4;
 //          cutFlowVector5ATLAS_300_150[6]=405.;
 //          cutFlowVector5ATLAS_300_150[7]=46.9;
 //          cutFlowVector5ATLAS_300_150[8]=594.5;
 //          cutFlowVector5ATLAS_300_150[9]=363.8;
 //          cutFlowVector5ATLAS_300_150[10]=45.7;

 //          for (size_t j=0;j<NCUTS5;j++){
 //            if(
 //              (j==0) ||

        //       (j==1 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0) ||

        //       (j==2 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25.) ||

        //       (j==3 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto) ||

        //       (j==4 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40.) ||

        //       (j==5 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()>0) ||

        //       (j==6 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()>0 && mll>111.) ||

        //       (j==7 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()>0 && mll>111. && mT2>100.) ||

        //       (j==8 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()==0) ||

        //       (j==9 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()==0 && mll>111.) ||

        //       (j==10 && nBaselineLeptons==nSignalLeptons && nSignalLeptons==2 && OSpairs.size()>0 && pT_l0>25. && central_jet_veto && mll>40. && SFOSpairs.size()==0 && mll>111. && mT2>100.) )

        //       cutFlowVector5[j]++;
        //   }
        // }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_MultiLEP_36invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_MultiLEP_36invfb*>(other);

        if (NCUTS1 != specificOther->NCUTS1) NCUTS1 = specificOther->NCUTS1;
        for (size_t j = 0; j < NCUTS1; j++) {
          cutFlowVector1[j] += specificOther->cutFlowVector1[j];
          cutFlowVector1_str[j] = specificOther->cutFlowVector1_str[j];
        }
        if (NCUTS2 != specificOther->NCUTS2) NCUTS2 = specificOther->NCUTS2;
        for (size_t j = 0; j < NCUTS2; j++) {
          cutFlowVector2[j] += specificOther->cutFlowVector2[j];
          cutFlowVector2_str[j] = specificOther->cutFlowVector2_str[j];
        }

        for (auto& el : _numSR) {
          el.second += specificOther->_numSR.at(el.first);
        }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR2_SF_loose", 153., {_numSR["SR2_SF_loose"], 0.}, {133., 22.}));
        add_result(SignalRegionData("SR2_SF_tight", 9., {_numSR["SR2_SF_tight"], 0.}, {9.8, 2.9}));
        add_result(SignalRegionData("SR2_DF_100", 78., {_numSR["SR2_DF_100"], 0.}, {68., 7.}));
        add_result(SignalRegionData("SR2_DF_150", 11, {_numSR["SR2_DF_150"], 0.}, {11.5, 3.1}));
        add_result(SignalRegionData("SR2_DF_200", 6., {_numSR["SR2_DF_200"], 0.}, {2.1, 1.9}));
        add_result(SignalRegionData("SR2_DF_300", 2., {_numSR["SR2_DF_300"], 0.}, {0.6, 0.6}));
        add_result(SignalRegionData("SR2_int", 2., {_numSR["SR2_int"], 0.}, {4.1, 2.6}));
        add_result(SignalRegionData("SR2_high", 0., {_numSR["SR2_high"], 0.}, {1.6, 1.6}));
        add_result(SignalRegionData("SR2_low", 11., {_numSR["SR2_low"], 0.}, {4.2, 3.4}));
        add_result(SignalRegionData("SR3_slep_a", 4., {_numSR["SR3_slep_a"], 0.}, {2.2, 0.8}));
        add_result(SignalRegionData("SR3_slep_b", 3., {_numSR["SR3_slep_b"], 0.}, {2.8, 0.4}));
        add_result(SignalRegionData("SR3_slep_c", 9., {_numSR["SR3_slep_c"], 0.}, {5.4, 0.9}));
        add_result(SignalRegionData("SR3_slep_d", 0., {_numSR["SR3_slep_d"], 0.}, {1.4, 0.4}));
        add_result(SignalRegionData("SR3_slep_e", 0., {_numSR["SR3_slep_e"], 0.}, {1.1, 0.2}));
        add_result(SignalRegionData("SR3_WZ_0Ja", 21., {_numSR["SR3_WZ_0Ja"], 0.}, {21.7, 2.9}));
        add_result(SignalRegionData("SR3_WZ_0Jb", 1., {_numSR["SR3_WZ_0Jb"], 0.}, {2.7, 0.5}));
        add_result(SignalRegionData("SR3_WZ_0Jc", 2., {_numSR["SR3_WZ_0Jc"], 0.}, {1.6, 0.3}));
        add_result(SignalRegionData("SR3_WZ_1Ja", 1., {_numSR["SR3_WZ_1Ja"], 0.}, {2.2, 0.5}));
        add_result(SignalRegionData("SR3_WZ_1Jb", 3., {_numSR["SR3_WZ_1Jb"], 0.}, {1.8, 0.3}));
        add_result(SignalRegionData("SR3_WZ_1Jc", 4., {_numSR["SR3_WZ_1Jc"], 0.}, {1.3, 0.3}));
      }


      vector<HEPUtils::P4> get_W_ISR(vector<HEPUtils::Jet*> jets, HEPUtils::P4 Z, HEPUtils::P4 met) {
        HEPUtils::P4 Z_met_sys=Z+met;
        double deltaR_min=999;
        size_t Wjets_id1;
        size_t Wjets_id2;
        for (size_t i=0;i<jets.size();i++) {
          for (size_t j=0;j<jets.size();j++) {
            if (i!=j) {
              HEPUtils::P4 jj_sys=jets.at(i)->mom()+jets.at(j)->mom();
              double deltaR=fabs(jj_sys.deltaR_eta(Z_met_sys));
              if (deltaR<deltaR_min) {
                deltaR_min=deltaR;
                Wjets_id1=i;
                Wjets_id2=j;
              }
            }
          }
        }
        HEPUtils::P4 W=jets.at(Wjets_id2)->mom()+jets.at(Wjets_id1)->mom();
        HEPUtils::P4 ISR;
        HEPUtils::P4 j0=jets.at(Wjets_id2)->mom();
        HEPUtils::P4 j1=jets.at(Wjets_id1)->mom();
        for (size_t k=0;k<jets.size();k++) {
          if ((k!=Wjets_id1) && (k!=Wjets_id2))ISR+=(jets.at(k)->mom());
        }
        vector<HEPUtils::P4> W_ISR;
        W_ISR.push_back(W);
        W_ISR.push_back(ISR);
        W_ISR.push_back(j0);
        W_ISR.push_back(j1);
        return W_ISR;
      }


    protected:
      void analysis_specific_reset() {

        for (auto& el : _numSR) { el.second = 0.;}

        std::fill(cutFlowVector1.begin(), cutFlowVector1.end(), 0);
        std::fill(cutFlowVector2.begin(), cutFlowVector2.end(), 0);
        std::fill(cutFlowVector3.begin(), cutFlowVector3.end(), 0);
        std::fill(cutFlowVector4.begin(), cutFlowVector4.end(), 0);
        std::fill(cutFlowVector5.begin(), cutFlowVector5.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MultiLEP_36invfb)



    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb : public Analysis_ATLAS_13TeV_MultiLEP_36invfb {

    public:
      Analysis_ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb() {
        set_analysis_name("ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR2_SF_loose", 153., {_numSR["SR2_SF_loose"], 0.}, {133., 22.}));
        add_result(SignalRegionData("SR2_SF_tight", 9., {_numSR["SR2_SF_tight"], 0.}, {9.8, 2.9}));
        add_result(SignalRegionData("SR2_DF_100", 78., {_numSR["SR2_DF_100"], 0.}, {68., 7.}));
        add_result(SignalRegionData("SR2_DF_150", 11, {_numSR["SR2_DF_150"], 0.}, {11.5, 3.1}));
        add_result(SignalRegionData("SR2_DF_200", 6., {_numSR["SR2_DF_200"], 0.}, {2.1, 1.9}));
        add_result(SignalRegionData("SR2_DF_300", 2., {_numSR["SR2_DF_300"], 0.}, {0.6, 0.6}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb)



    // Derived analysis class for the 2LepPlusJets SRs
    class Analysis_ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb : public Analysis_ATLAS_13TeV_MultiLEP_36invfb {

    public:
      Analysis_ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb() {
        set_analysis_name("ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR2_int", 2., {_numSR["SR2_int"], 0.}, {4.1, 2.6}));
        add_result(SignalRegionData("SR2_high", 0., {_numSR["SR2_high"], 0.}, {1.6, 1.6}));
        add_result(SignalRegionData("SR2_low", 11., {_numSR["SR2_low"], 0.}, {4.2, 3.4}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb)



    // Derived analysis class for the 3Lep SRs
    class Analysis_ATLAS_13TeV_MultiLEP_3Lep_36invfb : public Analysis_ATLAS_13TeV_MultiLEP_36invfb {

    public:
      Analysis_ATLAS_13TeV_MultiLEP_3Lep_36invfb() {
        set_analysis_name("ATLAS_13TeV_MultiLEP_3Lep_36invfb");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR3_slep_a", 4., {_numSR["SR3_slep_a"], 0.}, {2.2, 0.8}));
        add_result(SignalRegionData("SR3_slep_b", 3., {_numSR["SR3_slep_b"], 0.}, {2.8, 0.4}));
        add_result(SignalRegionData("SR3_slep_c", 9., {_numSR["SR3_slep_c"], 0.}, {5.4, 0.9}));
        add_result(SignalRegionData("SR3_slep_d", 0., {_numSR["SR3_slep_d"], 0.}, {1.4, 0.4}));
        add_result(SignalRegionData("SR3_slep_e", 0., {_numSR["SR3_slep_e"], 0.}, {1.1, 0.2}));
        add_result(SignalRegionData("SR3_WZ_0Ja", 21., {_numSR["SR3_WZ_0Ja"], 0.}, {21.7, 2.9}));
        add_result(SignalRegionData("SR3_WZ_0Jb", 1., {_numSR["SR3_WZ_0Jb"], 0.}, {2.7, 0.5}));
        add_result(SignalRegionData("SR3_WZ_0Jc", 2., {_numSR["SR3_WZ_0Jc"], 0.}, {1.6, 0.3}));
        add_result(SignalRegionData("SR3_WZ_1Ja", 1., {_numSR["SR3_WZ_1Ja"], 0.}, {2.2, 0.5}));
        add_result(SignalRegionData("SR3_WZ_1Jb", 3., {_numSR["SR3_WZ_1Jb"], 0.}, {1.8, 0.3}));
        add_result(SignalRegionData("SR3_WZ_1Jc", 4., {_numSR["SR3_WZ_1Jc"], 0.}, {1.3, 0.3}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MultiLEP_3Lep_36invfb)



  }
}
