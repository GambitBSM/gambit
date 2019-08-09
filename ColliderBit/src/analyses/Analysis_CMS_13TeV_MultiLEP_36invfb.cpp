///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2018 June
///  *********************************************


#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// Based on http://cms-results.web.cern.ch/cms-results/public-results/superseded/SUS-16-039/index.html

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - Analysis_CMS_13TeV_MultiLEP_2SSLep_36invfb
    // - Analysis_CMS_13TeV_MultiLEP_3Lep_36invfb
    class Analysis_CMS_13TeV_MultiLEP_36invfb : public Analysis {

    protected:
      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SR1", 0.},
        {"SR2", 0.},
        {"SR3", 0.},
        {"SR4", 0.},
        {"SR5", 0.},
        {"SR6", 0.},
        {"SR7", 0.},
        {"SR8", 0.}
      };

    private:

      vector<int> cutFlowVector1, cutFlowVector2, cutFlowVector3, cutFlowVector4;
      vector<string> cutFlowVector_str1, cutFlowVector_str2, cutFlowVector_str3, cutFlowVector_str4;
      // double xsec2CMS_200_100, xsec2CMS_500_150, xsec3CMS_250_150, xsec3CMS_600_1, xsec1CMS_500_350_05,xsec1CMS_500_350_5, xsec4CMS_100_1, xsec4CMS_800_1;
      // vector<double> cutFlowVector2CMS_200_100, cutFlowVector2CMS_500_150, cutFlowVector3CMS_250_150, cutFlowVector3CMS_600_1, cutFlowVector1CMS_500_350_05, cutFlowVector1CMS_500_350_5, cutFlowVector4CMS_100_1, cutFlowVector4CMS_800_1;
      size_t NCUTS1, NCUTS2, NCUTS3, NCUTS4;

      // ofstream cutflowFile;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      Analysis_CMS_13TeV_MultiLEP_36invfb() {

        set_analysis_name("CMS_13TeV_MultiLEP_36invfb");
        set_luminosity(35.9);

        NCUTS1=10;
        NCUTS2=7;
        NCUTS3=7;
        NCUTS4=5;

       // xsec2CMS_200_100=1800.;
       // xsec2CMS_500_150=46.;
       // xsec3CMS_250_150=780.;
       // xsec3CMS_600_1=20.;
       // xsec1CMS_500_350_05=46.;
       // xsec1CMS_500_350_5=46.;
       // xsec4CMS_100_1=16800.;
       // xsec4CMS_800_1=3.5;

        for (size_t i=0;i<NCUTS1;i++){
          cutFlowVector1.push_back(0);
          // cutFlowVector1CMS_500_350_05.push_back(0);
          // cutFlowVector1CMS_500_350_5.push_back(0);
          cutFlowVector_str1.push_back("");
        }
        for (size_t i=0;i<NCUTS2;i++){
          cutFlowVector2.push_back(0);
          // cutFlowVector2CMS_200_100.push_back(0);
          // cutFlowVector2CMS_500_150.push_back(0);
          cutFlowVector_str2.push_back("");
        }
        for (size_t i=0;i<NCUTS3;i++){
          cutFlowVector3.push_back(0);
          // cutFlowVector3CMS_600_1.push_back(0);
          // cutFlowVector3CMS_250_150.push_back(0);
          cutFlowVector_str3.push_back("");
        }
        for (size_t i=0;i<NCUTS4;i++){
          cutFlowVector4.push_back(0);
          // cutFlowVector4CMS_100_1.push_back(0);
          // cutFlowVector4CMS_800_1.push_back(0);
          cutFlowVector_str4.push_back("");
        }

      }


      void run(const HEPUtils::Event* event) {

        double met = event->met();

        // Baseline objects

        // Note that CMS provides two different efficiency maps, one for the multi-lepton SR and one for the 2SS signal region:
        //   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
        // Here we have only implemented the multi-lepton efficiency map.

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_039_multi_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cEl={
                          // pT: (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                   0.0,    0.95,    0.507,    0.619,    0.682,    0.742,    0.798,    0.863,  // eta: (0, 0.8)
                                   0.0,    0.95,    0.429,    0.546,    0.619,    0.710,    0.734,    0.833,  // eta: (0.8, 1.4429
                                   0.0,    0.95,    0.256,    0.221,    0.315,    0.351,    0.373,    0.437,  // eta: (1.442, 1.556)
                                   0.0,    0.85,    0.249,    0.404,    0.423,    0.561,    0.642,    0.749,  // eta: (1.556, 2)
                                   0.0,    0.85,    0.195,    0.245,    0.380,    0.441,    0.533,    0.644,  // eta: (2, 2.5)
                                   0.0,    0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.5
                                  };
        // const vector<double> aEl={0,0.8,1.442,1.556,2.,2.5};
        // const vector<double> bEl={0.,20.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
        // const vector<double> cEl={0.507,0.619,0.682,0.742,0.798,0.863,0.429,0.546,0.619,0.710,0.734,0.833,0.256,0.221,0.315,0.351,0.373,0.437,0.249,0.404,0.423,0.561,0.642,0.749,0.195,0.245,0.380,0.441,0.533,0.644};
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          bool isEl=has_tag(_eff2dEl, electron->eta(), electron->pT());
          if (electron->pT()>15. && fabs(electron->eta())<2.5 && isEl)baselineElectrons.push_back(electron);
        }

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_039_multi_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cMu={
                           // pT:   (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                     0.0,     0.704,    0.797,    0.855,    0.880,    0.906,    0.927,    0.931,  // eta: (0, 0.9)
                                     0.0,     0.639,    0.776,    0.836,    0.875,    0.898,    0.940,    0.930,  // eta: (0.9, 1.2)
                                     0.0,     0.596,    0.715,    0.840,    0.862,    0.891,    0.906,    0.925,  // eta: (1.2, 2.1)
                                     0.0,     0.522,    0.720,    0.764,    0.803,    0.807,    0.885,    0.877,  // eta: (2.1, 2.4)
                                     0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.4
                                 };
        // const vector<double> aMu={0,0.9,1.2,2.1,2.4};
        // const vector<double> bMu={0.,15.,20.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
        // const vector<double> cMu={0.704,0.797,0.855,0.88,0.906,0.927,0.931,0.639,0.776,0.836,0.875,0.898,0.94,0.93,0.569,0.715,0.84,0.862,0.891,0.906,0.925,0.0522,0.720,0.764,0.803,0.807,0.885,0.877};
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          bool isMu=has_tag(_eff2dMu, muon->eta(), muon->pT());
          if (muon->pT()>10. &&fabs(muon->eta())<2.4 && isMu)baselineMuons.push_back(muon);
        }

        // @note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/TauIDEfficiency_pT_DP2016_066.pdf
        const vector<double> aTau={0.,2.3};
        const vector<double> bTau={0.,25.,30.,35.,40.,45.,50.,60.,70.,80.,DBL_MAX};  // Assuming flat efficiency above pT = 100 GeV, where the CMS map stops.
        // The tau efficiencies should be corrected with a data/simulation scale factor of 0.95, as instructed here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
        const vector<double> cTau={0.38*0.95, 0.48*0.95, 0.5*0.95, 0.49*0.95, 0.51*0.95, 0.49*0.95, 0.47*0.95, 0.45*0.95, 0.48*0.95, 0.5*0.95};
        HEPUtils::BinnedFn2D<double> _eff2dTau(aTau,bTau,cTau);
        vector<HEPUtils::Particle*> baselineTaus;
        for (HEPUtils::Particle* tau : event->taus()) {
          bool isTau=has_tag(_eff2dTau, tau->eta(), tau->pT());
          if (tau->pT()>20. &&fabs(tau->eta())<2.3 && isTau)baselineTaus.push_back(tau);
        }

        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT()>25. &&fabs(jet->eta())<2.4)baselineJets.push_back(jet);
        }

        // Signal objects
        vector<HEPUtils::Particle*> signalElectrons=baselineElectrons;
        vector<HEPUtils::Particle*> signalMuons=baselineMuons;
        vector<HEPUtils::Particle*> signalTaus=baselineTaus;
        vector<HEPUtils::Particle*> signalLightLeptons=signalElectrons;
        signalLightLeptons.insert(signalLightLeptons.end(),signalMuons.begin(),signalMuons.end());
        vector<HEPUtils::Particle*> signalLeptons=signalTaus;
        signalLeptons.insert(signalLeptons.end(),signalLightLeptons.begin(),signalLightLeptons.end());
        sort(signalLightLeptons.begin(),signalLightLeptons.end(),comparePt);
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);

        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> signalBJets;
        int num_ISRjets=0;
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          for (size_t iLe=0;iLe<signalLeptons.size();iLe++) {
            if (fabs(signalLeptons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          if (!overlap) {
            signalJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->pT()>40.)num_ISRjets++;
          }
        }
        CMS::applyCSVv2MediumBtagEff(signalBJets);

        // int nSignalElectrons=signalElectrons.size();
        int nSignalMuons=signalMuons.size();
        int nSignalTaus=signalTaus.size();
        int nSignalLightLeptons = signalLightLeptons.size();
        int nSignalLeptons=signalLeptons.size();
        // int nSignalJets=signalJets.size();

        //Variables
        bool preselection=false;
        bool bjet_veto=(signalBJets.size()==0);
        bool low_mass_veto=true;
        bool conversion_veto=true;
        // bool ISRjet=(num_ISRjets<2);

        double pT_ll=0;
        double mT=0;
        double mT2=0;
        // double mll=0;
        vector<vector<HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
        vector<vector<HEPUtils::Particle*>> OSpair_cont = getOSpairs(signalLeptons);

        if (nSignalLeptons>1)pT_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).pT();
        if (nSignalLightLeptons>0 && nSignalTaus>0) {
          double pLep1[3] = {signalLightLeptons.at(0)->mass(), signalLightLeptons.at(0)->mom().px(), signalLightLeptons.at(0)->mom().py()};
          double pTau[3] = {signalTaus.at(0)->mass(), signalTaus.at(0)->mom().px(), signalTaus.at(0)->mom().py()};
          double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep1,pTau,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
        }
        if (nSignalLeptons==2 || (SFOSpair_cont.size()==0 && OSpair_cont.size()==0))mT=get_mTmin(signalLeptons, event->missingmom());
        if (SFOSpair_cont.size()>0) {
          vector<double> mll_mT= get_mll_mT(SFOSpair_cont,signalLeptons,event->missingmom(),0);
          // mll=mll_mT.at(0);
          mT=mll_mT.at(1);
        }
        if (SFOSpair_cont.size()==0 && OSpair_cont.size()>0) {
          vector<double> mll_mT= get_mll_mT(OSpair_cont,signalLeptons,event->missingmom(),1);
          // mll=mll_mT.at(0);
          mT=mll_mT.at(1);
        }
        for (size_t iPa=0;iPa<SFOSpair_cont.size();iPa++) {
          double SFOSpair_mass=(SFOSpair_cont.at(iPa).at(0)->mom()+SFOSpair_cont.at(iPa).at(1)->mom()).m();
          if (SFOSpair_mass<12)low_mass_veto=false;
          if (nSignalLeptons==2 && abs(SFOSpair_mass-91.2)<15)conversion_veto=false;
          if (nSignalLeptons>2) {
            double m_lll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()+signalLeptons.at(2)->mom()).m();
            if (SFOSpair_cont.at(iPa).at(0)->abspid()!=15 && abs(m_lll-91.2)<15)conversion_veto=false;
          }
        }
        if (bjet_veto && low_mass_veto)preselection=true;

        //Signal regions
        //2 same-sign leptons
        if (preselection && nSignalLeptons==2 && nSignalTaus==0 && met>60 && conversion_veto) {
          if (signalLeptons.at(0)->pid()*signalLeptons.at(1)->pid()>0) {
            if ((signalLeptons.at(0)->abspid()==11 && signalLeptons.at(0)->pT()>25) || (signalLeptons.at(0)->abspid()==13 && signalLeptons.at(0)->pT()>20)) {
              if (num_ISRjets==0 && met>140 && mT>100) _numSR["SR1"]++;
              if (num_ISRjets==1 && met>200 && mT<100 && pT_ll<100) _numSR["SR2"]++;
            }
          }
        }

        //3 or more leptons
        if (preselection && met>50 && conversion_veto && nSignalLeptons>2) {

          if (nSignalTaus<2) {
            if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>25) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>20 && nSignalMuons>1) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25 && nSignalMuons==1)) {
              if (nSignalLightLeptons==3 && nSignalTaus==0) {
                if (mT>120 && met>200) _numSR["SR3"]++;
                if (met>250) _numSR["SR4"]++;
              }
              if (nSignalLightLeptons==2 && nSignalTaus==1 && mT2>50 && met>200) _numSR["SR5"]++;
              if (nSignalLeptons>3 && met>200) _numSR["SR8"]++;
            }
          }

          if (nSignalLightLeptons==1 && nSignalTaus==2) {
            if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>30) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25)) {
              if (signalLeptons.at(0)->abseta()<2.1 && signalLeptons.at(1)->abseta()<2.1 && signalLeptons.at(2)->abseta()<2.1) {
                if (mT2>50 && met>200) _numSR["SR6"]++;
                if (met>75) _numSR["SR7"]++;
              }
            }
          }
        }

 //        if (analysis_name().find("500_350") != string::npos){

 //          cutFlowVector_str1[0] = "All events";
 //          cutFlowVector_str1[1] = "2 light leptons";
 //          cutFlowVector_str1[2] = "Same-sign";
 //          cutFlowVector_str1[3] = "$3^{rd}$ lepton veto";
 //          cutFlowVector_str1[4] = "Low mass veto";
 //          cutFlowVector_str1[5] = "Bjet veto";
 //          cutFlowVector_str1[6] = "$E_{T}^{miss} > 60 GeV$";
 //          cutFlowVector_str1[7] = "0 or 1 ISR jet";
 //          cutFlowVector_str1[8] = "$m_{T} < 100 GeV$";
 //          cutFlowVector_str1[9] = "$p_{T}^{ll} > 100 GeV$";

 //          cutFlowVector1CMS_500_350_05[0]=485.36;
 //          cutFlowVector1CMS_500_350_05[1]=214.24;
 //          cutFlowVector1CMS_500_350_05[2]=91.09;
 //          cutFlowVector1CMS_500_350_05[3]=75.82;
 //          cutFlowVector1CMS_500_350_05[4]=73.61;
 //          cutFlowVector1CMS_500_350_05[5]=71.27;
 //          cutFlowVector1CMS_500_350_05[6]=62.79;
 //          cutFlowVector1CMS_500_350_05[7]=54.85;
 //          cutFlowVector1CMS_500_350_05[8]=18.3;
 //          cutFlowVector1CMS_500_350_05[9]=10.01;

 //          cutFlowVector1CMS_500_350_5[0]=632.16;
 //          cutFlowVector1CMS_500_350_5[1]=485.34;
 //          cutFlowVector1CMS_500_350_5[2]=128.59;
 //          cutFlowVector1CMS_500_350_5[3]=50.24;
 //          cutFlowVector1CMS_500_350_5[4]=49.86;
 //          cutFlowVector1CMS_500_350_5[5]=48.12;
 //          cutFlowVector1CMS_500_350_5[6]=38.92;
 //          cutFlowVector1CMS_500_350_5[7]=29.72;
 //          cutFlowVector1CMS_500_350_5[8]=15.17;
 //          cutFlowVector1CMS_500_350_5[9]=2.84;

 //          for (size_t j=0;j<NCUTS1;j++){
 //            if(
 //              (j==0) ||

 //           (j==1 && nSignalLightLeptons==2) ||

        //       (j==2 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0) ||

        //       (j==3 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2) ||

        //       (j==4 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto) ||

        //       (j==5 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto && bjet_veto)  ||

        //       (j==6 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto && bjet_veto && met>60) ||

        //       (j==7 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto && bjet_veto && met>60 && ISRjet) ||

 //              (j==8 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto && bjet_veto && met>60 && ISRjet && mT<100) ||

 //              (j==9 && nSignalLightLeptons==2 && signalLightLeptons.at(0)->pid()*signalLightLeptons.at(1)->pid()>0 && nSignalLeptons==2 && low_mass_veto && bjet_veto && met>60 && ISRjet && mT<100 && pT_ll>100) )

        //     cutFlowVector1[j]++;
 //       }

        // }

 //        if ((analysis_name().find("200_100") != string::npos) || (analysis_name().find("500_150") != string::npos)){

 //          cutFlowVector_str2[0] = "All events";
 //          cutFlowVector_str2[1] = "3 leptons";
 //          cutFlowVector_str2[2] = "Low mass \\& conversions veto";
 //          cutFlowVector_str2[3] = "Bjet veto";
 //          cutFlowVector_str2[4] = "$E_{T}^{miss} > 50 GeV$";
 //          cutFlowVector_str2[5] = "$m_{T} > 100 GeV$";
 //          cutFlowVector_str2[6] = "$m_{ll} > 75 GeV$";

 //          cutFlowVector2CMS_200_100[0] =3630.;
 //          cutFlowVector2CMS_200_100[1] =481.49;
 //          cutFlowVector2CMS_200_100[2] =463.71;
 //          cutFlowVector2CMS_200_100[3] =456.68;
 //          cutFlowVector2CMS_200_100[4] =317.;
 //          cutFlowVector2CMS_200_100[5] =111.97;
 //          cutFlowVector2CMS_200_100[6] =103.49;

 //          cutFlowVector2CMS_500_150[0] =115.79;
 //          cutFlowVector2CMS_500_150[1] =18.03;
 //          cutFlowVector2CMS_500_150[2] =17.79;
 //          cutFlowVector2CMS_500_150[3] =17.47;
 //          cutFlowVector2CMS_500_150[4] =16.98;
 //          cutFlowVector2CMS_500_150[5] =12.74;
 //          cutFlowVector2CMS_500_150[6] =11.71;

 //          for (size_t j=0;j<NCUTS2;j++){
 //            if(
 //              (j==0) ||

 //              (j==1 && nSignalLeptons==3) ||

 //              (j==2 && nSignalLeptons==3 && low_mass_veto && conversion_veto) ||

 //              (j==3 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto) ||

 //              (j==4 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50.) ||

 //              (j==5 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50. && mT>100.) ||

 //              (j==6 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50. && mT>100. && mll>75.) )

 //              cutFlowVector2[j]++;
 //          }
        // }

 //        if ((analysis_name().find("250_150") != string::npos) || (analysis_name().find("600_1") != string::npos)){

 //          cutFlowVector_str3[0] = "All events";
 //          cutFlowVector_str3[1] = "3 leptons";
 //          cutFlowVector_str3[2] = "Low mass \\& conversion veto";
 //          cutFlowVector_str3[3] = "Bjet veto";
 //          cutFlowVector_str3[4] = "$E_{T}^{miss} > 50 GeV$";
 //          cutFlowVector_str3[5] = "$m_{T2} < 100 GeV$";
 //          cutFlowVector_str3[6] = "$m_{ll} < 75 GeV$";

 //          cutFlowVector3CMS_250_150[0] =5304.;
 //          cutFlowVector3CMS_250_150[1] =188.58;
 //          cutFlowVector3CMS_250_150[2] =168.19;
 //          cutFlowVector3CMS_250_150[3] =166.26;
 //          cutFlowVector3CMS_250_150[4] =117.09;
 //          cutFlowVector3CMS_250_150[5] =112.26;
 //          cutFlowVector3CMS_250_150[6] =93.07;

 //          cutFlowVector3CMS_600_1[0] =220.23;
 //          cutFlowVector3CMS_600_1[1] =28.62;
 //          cutFlowVector3CMS_600_1[2] =28.31;
 //          cutFlowVector3CMS_600_1[3] =27.78;
 //          cutFlowVector3CMS_600_1[4] =25.67;
 //          cutFlowVector3CMS_600_1[5] =15.74;
 //          cutFlowVector3CMS_600_1[6] =3.85;

 //          for (size_t j=0;j<NCUTS3;j++){
 //            if(
 //              (j==0) ||

 //              (j==1 && nSignalLeptons==3) ||

 //              (j==2 && nSignalLeptons==3 && low_mass_veto && conversion_veto) ||

 //              (j==3 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto) ||

 //              (j==4 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50.) ||

 //              (j==5 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50. && mT2<100.) ||

 //              (j==6 && nSignalLeptons==3 && low_mass_veto && conversion_veto && bjet_veto && met>50. && mT2<100. && mll<75.) )

 //              cutFlowVector3[j]++;
 //          }
        // }

 //        if ((analysis_name().find("100_1") != string::npos) || (analysis_name().find("800_1") != string::npos)){

 //          cutFlowVector_str4[0] = "All events";
 //          cutFlowVector_str4[1] = "4 leptons";
 //          cutFlowVector_str4[2] = "Low mass veto";
 //          cutFlowVector_str4[3] = "Bjet veto";
 //          cutFlowVector_str4[4] = "$E_{T}^{miss} > 100 GeV$";

 //          cutFlowVector4CMS_100_1[0] =5497.;
 //          cutFlowVector4CMS_100_1[1] =869.14;
 //          cutFlowVector4CMS_100_1[2] =868.6;
 //          cutFlowVector4CMS_100_1[3] =855.41;
 //          cutFlowVector4CMS_100_1[4] =34.27;

 //          cutFlowVector4CMS_800_1[0] =1.14;
 //          cutFlowVector4CMS_800_1[1] =0.36;
 //          cutFlowVector4CMS_800_1[2] =0.36;
 //          cutFlowVector4CMS_800_1[0] =0.35;
 //          cutFlowVector4CMS_800_1[4] =0.34;

 //          for (size_t j=0;j<NCUTS4;j++){
 //            if(
 //              (j==0) ||

 //              (j==1 && nSignalLeptons==4) ||

 //              (j==2 && nSignalLeptons==4 && low_mass_veto) ||

 //              (j==3 && nSignalLeptons==4 && low_mass_veto && bjet_veto) ||

 //              (j==4 && nSignalLeptons==4 && low_mass_veto && bjet_veto && met>100.) )

 //              cutFlowVector4[j]++;
 //          }
        // }
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_MultiLEP_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_MultiLEP_36invfb*>(other);

        if (NCUTS1 != specificOther->NCUTS1) NCUTS1 = specificOther->NCUTS1;
        if (NCUTS2 != specificOther->NCUTS2) NCUTS2 = specificOther->NCUTS2;
        if (NCUTS3 != specificOther->NCUTS3) NCUTS3 = specificOther->NCUTS3;
        if (NCUTS4 != specificOther->NCUTS4) NCUTS4 = specificOther->NCUTS4;
        for (size_t j = 0; j < NCUTS1; j++) {
          cutFlowVector1[j] += specificOther->cutFlowVector1[j];
          cutFlowVector_str1[j] = specificOther->cutFlowVector_str1[j];
        }
        for (size_t j = 0; j < NCUTS2; j++) {
          cutFlowVector2[j] += specificOther->cutFlowVector2[j];
          cutFlowVector_str2[j] = specificOther->cutFlowVector_str2[j];
        }
        for (size_t j = 0; j < NCUTS3; j++) {
          cutFlowVector3[j] += specificOther->cutFlowVector3[j];
          cutFlowVector_str3[j] = specificOther->cutFlowVector_str3[j];
        }
        for (size_t j = 0; j < NCUTS4; j++) {
          cutFlowVector4[j] += specificOther->cutFlowVector4[j];
          cutFlowVector_str4[j] = specificOther->cutFlowVector_str4[j];
        }

        for (auto& el : _numSR) {
          el.second += specificOther->_numSR.at(el.first);
        }
      }


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        // string path = "ColliderBit/results/cutflow_";
        // path.append(analysis_name());
        // path.append(".txt");
        // cutflowFile.open(path.c_str());

        // if (analysis_name().find("500_350_05") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $\\tilde{l}/\\tilde{\\nu}$ (flavor-democratic), $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0},\\tilde{l}]: [500,350,357.5] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec1CMS_500_350_05<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec1CMS_500_350_05<<" & 1\\\\"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS1; i++) {
        //     cutflowFile<<cutFlowVector_str1[i]<<"&"<<setprecision(4)<<cutFlowVector1CMS_500_350_05[i]<<"&"<<setprecision(4)<<cutFlowVector1[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector1[i]*xsec_per_event()*luminosity()/cutFlowVector1CMS_500_350_05[i]<<"&"<<setprecision(4)<<(xsec1CMS_500_350_05/xsec())*cutFlowVector1[i]*xsec_per_event()*luminosity()/cutFlowVector1CMS_500_350_05[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS1; i++) {
        //     cutflowFile<<cutFlowVector_str1[i]<<"&"<<setprecision(4)<<cutFlowVector1CMS_500_350_05[i]*100./cutFlowVector1CMS_500_350_05[1]<<"&"<<setprecision(4)<<cutFlowVector1[i]*100./cutFlowVector1[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // if (analysis_name().find("500_350_5") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $\\tilde{l}/\\tilde{\\nu}$ (flavor-democratic), $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0},\\tilde{l}]: [500,350,425] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec1CMS_500_350_5<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec1CMS_500_350_5<<" & 1\\\\ \\hline"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS1; i++) {
        //     cutflowFile<<cutFlowVector_str1[i]<<"&"<<setprecision(4)<<cutFlowVector1CMS_500_350_5[i]<<"&"<<setprecision(4)<<cutFlowVector1[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector1[i]*xsec_per_event()*luminosity()/cutFlowVector1CMS_500_350_5[i]<<"&"<<setprecision(4)<<(xsec1CMS_500_350_5/xsec())*cutFlowVector1[i]*xsec_per_event()*luminosity()/cutFlowVector1CMS_500_350_5[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS1; i++) {
        //     cutflowFile<<cutFlowVector_str1[i]<<"&"<<setprecision(4)<<cutFlowVector1CMS_500_350_5[i]*100./cutFlowVector1CMS_500_350_5[1]<<"&"<<setprecision(4)<<cutFlowVector1[i]*100./cutFlowVector1[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // if (analysis_name().find("200_100") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $W/Z$, $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0}]: [200,100] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec2CMS_200_100<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec2CMS_200_100<<" & 1\\\\ \\hline"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS2; i++) {
        //     cutflowFile<<cutFlowVector_str2[i]<<"&"<<setprecision(4)<<cutFlowVector2CMS_200_100[i]<<"&"<<setprecision(4)<<cutFlowVector2[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector2[i]*xsec_per_event()*luminosity()/cutFlowVector2CMS_200_100[i]<<"&"<<setprecision(4)<<(xsec2CMS_200_100/xsec())*cutFlowVector2[i]*xsec_per_event()*luminosity()/cutFlowVector2CMS_200_100[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS2; i++) {
        //     cutflowFile<<cutFlowVector_str2[i]<<"&"<<setprecision(4)<<cutFlowVector2CMS_200_100[i]*100./cutFlowVector2CMS_200_100[1]<<"&"<<setprecision(4)<<cutFlowVector2[i]*100./cutFlowVector2[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // if (analysis_name().find("500_150") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $W/Z$, $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0}]: [500,150] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec2CMS_500_150<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec2CMS_500_150<<" & 1\\\\"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS2; i++) {
        //     cutflowFile<<cutFlowVector_str2[i]<<"&"<<setprecision(4)<<cutFlowVector2CMS_500_150[i]<<"&"<<setprecision(4)<<cutFlowVector2[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector2[i]*xsec_per_event()*luminosity()/cutFlowVector2CMS_500_150[i]<<"&"<<setprecision(4)<<(xsec2CMS_500_150/xsec())*cutFlowVector2[i]*xsec_per_event()*luminosity()/cutFlowVector2CMS_500_150[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS2; i++) {
        //     cutflowFile<<cutFlowVector_str2[i]<<"&"<<setprecision(4)<<cutFlowVector2CMS_500_150[i]*100./cutFlowVector2CMS_500_150[1]<<"&"<<setprecision(4)<<cutFlowVector2[i]*100./cutFlowVector2[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // if (analysis_name().find("250_150") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $\\tilde{\\tau}$, $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0}]: [250,150] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec3CMS_250_150<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec3CMS_250_150<<" & 1\\\\ \\hline"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS3; i++) {
        //     cutflowFile<<cutFlowVector_str3[i]<<"&"<<setprecision(4)<<cutFlowVector3CMS_250_150[i]<<"&"<<setprecision(4)<<cutFlowVector3[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector3[i]*xsec_per_event()*luminosity()/cutFlowVector3CMS_250_150[i]<<"&"<<setprecision(4)<<(xsec3CMS_250_150/xsec())*cutFlowVector3[i]*xsec_per_event()*luminosity()/cutFlowVector3CMS_250_150[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS3; i++) {
        //     cutflowFile<<cutFlowVector_str3[i]<<"&"<<setprecision(4)<<cutFlowVector3CMS_250_150[i]*100./cutFlowVector3CMS_250_150[1]<<"&"<<setprecision(4)<<cutFlowVector3[i]*100./cutFlowVector3[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // if (analysis_name().find("600_1") != string::npos) {
        //   cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $\\tilde{\\tau}$, $[\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0},\\tilde{\\chi}_{1}^{0}]: [600,1] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
        //   cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
        //   cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsec3CMS_600_1<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<< xsec()/xsec3CMS_600_1<<" & 1\\\\"<<endl;
        //   cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS3; i++) {
        //     cutflowFile<<cutFlowVector_str3[i]<<"&"<<setprecision(4)<<cutFlowVector3CMS_600_1[i]<<"&"<<setprecision(4)<<cutFlowVector3[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector3[i]*xsec_per_event()*luminosity()/cutFlowVector3CMS_600_1[i]<<"&"<<setprecision(4)<<(xsec3CMS_600_1/xsec())*cutFlowVector3[i]*xsec_per_event()*luminosity()/cutFlowVector3CMS_600_1[i]<<"\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
        //   for (size_t i=0; i<NCUTS3; i++) {
        //     cutflowFile<<cutFlowVector_str3[i]<<"&"<<setprecision(4)<<cutFlowVector3CMS_600_1[i]*100./cutFlowVector3CMS_600_1[1]<<"&"<<setprecision(4)<<cutFlowVector3[i]*100./cutFlowVector3[1]<<"& - & -\\\\"<< endl;
        //   }
        //   cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

        // cutflowFile.close();

        //Now fill a results object with the results for each SR

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1", 13., {_numSR["SR1"], 0.}, {12., 3.}));
        add_result(SignalRegionData("SR2", 18., {_numSR["SR2"], 0.}, {18., 4.}));
        add_result(SignalRegionData("SR3", 19., {_numSR["SR3"], 0.}, {19., 4.}));
        add_result(SignalRegionData("SR4", 128., {_numSR["SR4"], 0.}, {142, 34.}));
        add_result(SignalRegionData("SR5", 18., {_numSR["SR5"], 0.}, {22, 5.}));
        add_result(SignalRegionData("SR6", 2., {_numSR["SR6"], 0.}, {1, 0.6}));
        add_result(SignalRegionData("SR7", 82., {_numSR["SR7"], 0.}, {109, 28.}));
        add_result(SignalRegionData("SR8", 166., {_numSR["SR8"], 0.}, {197, 42.}));
      }



      vector<double> get_mll_mT(vector<vector<HEPUtils::Particle*>> pair_cont, vector<HEPUtils::Particle*> leptons, HEPUtils::P4 met, int type) {
        vector<double> mll_mT;
        vector<vector<double>> mll_mT_container;
        for (size_t iPa=0;iPa<pair_cont.size();iPa++) {
          double m_ll_temp=(pair_cont.at(iPa).at(0)->mom()+pair_cont.at(iPa).at(1)->mom()).m();
          double mT_temp=0;
          for (size_t iLe=0;iLe<leptons.size();iLe++) {
            if (leptons.at(iLe)!=pair_cont.at(iPa).at(0) && leptons.at(iLe)!=pair_cont.at(iPa).at(1))mT_temp=sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi())));
          }
          double mass=0;
          if (type==0)mass=91.2;
          if (type==1) {
            mass=50.;
            if (pair_cont.at(iPa).at(0)->abspid()==15 || pair_cont.at(iPa).at(1)->abspid()==15)mass=60;;
          }
          vector<double> temp;
          temp.push_back(m_ll_temp);
          temp.push_back(mT_temp);
          temp.push_back(fabs(m_ll_temp-mass));
          mll_mT_container.push_back(temp);
        }

        struct mllComparison {
          bool operator() (vector<double> i,vector<double> j) {return (i.at(2)<j.at(2));}
        } compare_mll;

        if (mll_mT_container.size()>0) {
          sort(mll_mT_container.begin(),mll_mT_container.end(),compare_mll);
          mll_mT_container.at(0).pop_back();
          mll_mT=mll_mT_container.at(0);
        }
        return mll_mT;
      }

      double get_mTmin(vector<HEPUtils::Particle*> leptons, HEPUtils::P4 met) {
        vector<double> mT_container;
        for (size_t iLe=0;iLe<leptons.size();iLe++) {
          mT_container.push_back(sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi()))));
        }
        sort(mT_container.begin(),mT_container.end());
        if (mT_container.size()>0)return mT_container.at(0);
        else return -1;
      }


    protected:
      void analysis_specific_reset() {

        for (auto& el : _numSR) { el.second = 0.;}

        std::fill(cutFlowVector1.begin(), cutFlowVector1.end(), 0);
        std::fill(cutFlowVector2.begin(), cutFlowVector2.end(), 0);
        std::fill(cutFlowVector3.begin(), cutFlowVector3.end(), 0);
        std::fill(cutFlowVector4.begin(), cutFlowVector4.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_36invfb)




    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_CMS_13TeV_MultiLEP_2SSLep_36invfb : public Analysis_CMS_13TeV_MultiLEP_36invfb {

    public:
      Analysis_CMS_13TeV_MultiLEP_2SSLep_36invfb() {
        set_analysis_name("CMS_13TeV_MultiLEP_2SSLep_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1", 13., {_numSR["SR1"], 0.}, {12., 3.}));
        add_result(SignalRegionData("SR2", 18., {_numSR["SR2"], 0.}, {18., 4.}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_2SSLep_36invfb)



    //
    // Derived analysis class for the 3Lep SRs
    //
    class Analysis_CMS_13TeV_MultiLEP_3Lep_36invfb : public Analysis_CMS_13TeV_MultiLEP_36invfb {

    public:
      Analysis_CMS_13TeV_MultiLEP_3Lep_36invfb() {
        set_analysis_name("CMS_13TeV_MultiLEP_3Lep_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR3", 19., {_numSR["SR3"], 0.}, {19., 4.}));
        add_result(SignalRegionData("SR4", 128., {_numSR["SR4"], 0.}, {142, 34.}));
        add_result(SignalRegionData("SR5", 18., {_numSR["SR5"], 0.}, {22, 5.}));
        add_result(SignalRegionData("SR6", 2., {_numSR["SR6"], 0.}, {1, 0.6}));
        add_result(SignalRegionData("SR7", 82., {_numSR["SR7"], 0.}, {109, 28.}));
        add_result(SignalRegionData("SR8", 166., {_numSR["SR8"], 0.}, {197, 42.}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_3Lep_36invfb)


  }
}
