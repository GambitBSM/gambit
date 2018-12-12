///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2018 June
///
///  \author Martin White
///  \date 2018 July
///  *********************************************


#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// Based on https://arxiv.org/pdf/1709.05406.pdf
// This is for debugging: we have implemented all bins and will combine them
// naively by hand after running GAMBIT

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - Analysis_CMS_13TeV_MultiLEP_Full_2SSLep_36invfb
    // - Analysis_CMS_13TeV_MultiLEP_Full_3Lep_36invfb
    class Analysis_CMS_13TeV_MultiLEP_Full_36invfb : public HEPUtilsAnalysis {

    protected:
      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SS01", 0.},
        {"SS02", 0.},
        {"SS03", 0.},
        {"SS04", 0.},
        {"SS05", 0.},
        {"SS06", 0.},
        {"SS07", 0.},
        {"SS08", 0.},
        {"SS09", 0.},
        {"SS10", 0.},
        {"SS11", 0.},
        {"SS12", 0.},
        {"SS13", 0.},
        {"SS14", 0.},
        {"SS15", 0.},
        {"SS16", 0.},
        {"SS17", 0.},
        {"SS18", 0.},
        {"SS19", 0.},
        {"SS20", 0.},
        {"SS21", 0.},
        {"SS22", 0.},
        {"SS23", 0.},
        {"SS24", 0.},
        {"SS25", 0.},
        {"SS26", 0.},
        {"SS27", 0.},
        {"SS28", 0.},
        {"SS29", 0.},
        {"SS30", 0.},
        {"A01", 0.},
        {"A02", 0.},
        {"A03", 0.},
        {"A04", 0.},
        {"A05", 0.},
        {"A06", 0.},
        {"A07", 0.},
        {"A08", 0.},
        {"A09", 0.},
        {"A10", 0.},
        {"A11", 0.},
        {"A12", 0.},
        {"A13", 0.},
        {"A14", 0.},
        {"A15", 0.},
        {"A16", 0.},
        {"A17", 0.},
        {"A18", 0.},
        {"A19", 0.},
        {"A20", 0.},
        {"A21", 0.},
        {"A22", 0.},
        {"A23", 0.},
        {"A24", 0.},
        {"A25", 0.},
        {"A26", 0.},
        {"A27", 0.},
        {"A28", 0.},
        {"A29", 0.},
        {"A30", 0.},
        {"A31", 0.},
        {"A32", 0.},
        {"A33", 0.},
        {"A34", 0.},
        {"A35", 0.},
        {"A36", 0.},
        {"A37", 0.},
        {"A38", 0.},
        {"A39", 0.},
        {"A40", 0.},
        {"A41", 0.},
        {"A42", 0.},
        {"A43", 0.},
        {"A44", 0.},
      };

    private:

      vector<int> cutFlowVector1, cutFlowVector2, cutFlowVector3, cutFlowVector4;
      vector<string> cutFlowVector_str1, cutFlowVector_str2, cutFlowVector_str3, cutFlowVector_str4;
      // double xsec2CMS_200_100, xsec2CMS_500_150, xsec3CMS_250_150, xsec3CMS_600_1, xsec1CMS_500_350_05,xsec1CMS_500_350_5, xsec4CMS_100_1, xsec4CMS_800_1;
      // vector<double> cutFlowVector2CMS_200_100, cutFlowVector2CMS_500_150, cutFlowVector3CMS_250_150, cutFlowVector3CMS_600_1, cutFlowVector1CMS_500_350_05, cutFlowVector1CMS_500_350_5, cutFlowVector4CMS_100_1, cutFlowVector4CMS_800_1;
      size_t NCUTS1, NCUTS2, NCUTS3, NCUTS4;

      // ofstream cutflowFile;

    public:

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      Analysis_CMS_13TeV_MultiLEP_Full_36invfb() {

        set_analysis_name("CMS_13TeV_MultiLEP_Full_36invfb");
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


      void analyze(const HEPUtils::Event* event) {
        HEPUtilsAnalysis::analyze(event);
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
        // double mT2=0;
        double mll=0;
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
          // mT2 = mt2_calc.get_mt2();
        }
        if (nSignalLeptons==2 || (SFOSpair_cont.size()==0 && OSpair_cont.size()==0))mT=get_mTmin(signalLeptons, event->missingmom());   
        if (SFOSpair_cont.size()>0) {
          vector<double> mll_mT= get_mll_mT(SFOSpair_cont,signalLeptons,event->missingmom(),0);
          mll=mll_mT.at(0);
          mT=mll_mT.at(1);
        }
        if (SFOSpair_cont.size()==0 && OSpair_cont.size()>0) {
          vector<double> mll_mT= get_mll_mT(OSpair_cont,signalLeptons,event->missingmom(),1);
          mll=mll_mT.at(0);
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

              bool pp = false;
              bool mm = false;
              if(signalLeptons.at(0)->pid() > 0)pp = true;
              if(signalLeptons.at(0)->pid() < 0)mm = true;
              
              if (num_ISRjets==0) {

                // The 0 jet regions
                if(mT < 100 && pT_ll < 50 && met < 100) _numSR["SS01"]++;
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && pp) _numSR["SS02"]++;
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && mm) _numSR["SS03"]++;
                if(mT < 100 && pT_ll < 50 && met >= 150 && met < 200) _numSR["SS04"]++;
                if(mT < 100 && pT_ll < 50 && met > 200) _numSR["SS05"]++;
                if(mT < 100 && pT_ll > 50 && met < 100) _numSR["SS06"]++;
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && pp) _numSR["SS07"]++;
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && mm) _numSR["SS08"]++;
                if(mT < 100 && pT_ll > 50 && met >= 150 && met < 200) _numSR["SS09"]++;
                if(mT < 100 && pT_ll > 50 && met > 200) _numSR["SS10"]++;
                if(mT > 100 && met < 100) _numSR["SS11"]++;
                if(mT > 100 && met >= 100 && met < 150 && pp) _numSR["SS12"]++;
                if(mT > 100 && met >= 100 && met < 150 && mm) _numSR["SS13"]++;
                if(mT > 100 && met >= 150 && met < 200) _numSR["SS14"]++;
                if(mT > 100 && met > 200) _numSR["SS15"]++;

              }

              if (num_ISRjets==1){
                
                // The 1 jet regions
                if(mT < 100 && pT_ll < 50 && met < 100) _numSR["SS16"]++;
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && pp) _numSR["SS17"]++;
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && mm) _numSR["SS18"]++;
                if(mT < 100 && pT_ll < 50 && met >= 150 && met < 200) _numSR["SS19"]++;
                if(mT < 100 && pT_ll < 50 && met > 200) _numSR["SS20"]++;
                if(mT < 100 && pT_ll > 50 && met < 100) _numSR["SS21"]++;
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && pp) _numSR["SS22"]++;
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && mm) _numSR["SS23"]++;
                if(mT < 100 && pT_ll > 50 && met >= 150 && met < 200) _numSR["SS24"]++;
                if(mT < 100 && pT_ll > 50 && met > 200) _numSR["SS25"]++;
                if(mT > 100 && met < 100) _numSR["SS26"]++;
                if(mT > 100 && met >= 100 && met < 150 && pp) _numSR["SS27"]++;
                if(mT > 100 && met >= 100 && met < 150 && mm) _numSR["SS28"]++;
                if(mT > 100 && met >= 150 && met < 200) _numSR["SS29"]++;
                if(mT > 100 && met > 200) _numSR["SS30"]++;

              }
              
            }   
          }
        }
        
        //3 or more leptons
        if (preselection && met>50 && conversion_veto && nSignalLeptons>2) {
          
          if (nSignalTaus<2) {
            if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>25) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>20 && nSignalMuons>1) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25 && nSignalMuons==1)) {
              if (nSignalLightLeptons==3 && nSignalTaus==0) {
                
                // The three light lepton signal regions
                
                if(mT < 100 && met >=50 && met < 100 && mll < 75) _numSR["A01"]++;
                if(mT < 100 && met >=100 && met < 150 && mll < 75) _numSR["A02"]++;
                if(mT < 100 && met >=150 && met < 200 && mll < 75) _numSR["A03"]++;
                if(mT < 100 && met >=200 && met < 250 && mll < 75) _numSR["A04"]++;
                if(mT < 100 && met >=250 && mll < 75) _numSR["A05"]++;

                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll < 75) _numSR["A06"]++;
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll < 75) _numSR["A07"]++;
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll < 75) _numSR["A08"]++;
                if(mT >= 100 && mT < 160 && met >=200 && mll < 75) _numSR["A09"]++;
                if(mT >= 160 && met >=50 && met < 100 && mll < 75) _numSR["A10"]++;
                if(mT >= 160 && met >=100 && met < 150 && mll < 75) _numSR["A11"]++;
                if(mT >= 160 && met >=150 && met < 200 && mll < 75) _numSR["A12"]++;
                if(mT >= 160 && met >=200 && met < 250 && mll < 75) _numSR["A13"]++;
                if(mT >= 160 && met >=250 && mll < 75) _numSR["A14"]++;

                if(mT < 100 && met >=50 && met < 100 && mll >= 75 && mll < 105) _numSR["A15"]++;
                if(mT < 100 && met >=100 && met < 150 && mll >= 75 && mll < 105) _numSR["A16"]++;
                if(mT < 100 && met >=150 && met < 200 && mll >= 75 && mll < 105) _numSR["A17"]++;
                if(mT < 100 && met >=200 && met < 250 && mll >= 75 && mll < 105) _numSR["A18"]++;
                if(mT < 100 && met >=250 && met < 400 && mll >= 75 && mll < 105) _numSR["A19"]++;
                if(mT < 100 && met >=400 && met < 550 && mll >= 75 && mll < 105) _numSR["A20"]++;
                if(mT < 100 && met >=550 && mll >= 75 && mll < 105) _numSR["A21"]++;            
                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll >= 75 && mll < 105) _numSR["A22"]++;
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll >= 75 && mll < 105) _numSR["A23"]++;
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll >= 75 && mll < 105) _numSR["A24"]++;
                if(mT >= 100 && mT < 160 && met >=200 && mll >= 75 && mll < 105) _numSR["A25"]++;
                
                if(mT >= 160 && met >=50 && met < 100 && mll >= 75 && mll < 105) _numSR["A26"]++;
                if(mT >= 160 && met >=100 && met < 150 && mll >= 75 && mll < 105) _numSR["A27"]++;
                if(mT >= 160 && met >=150 && met < 200 && mll >= 75 && mll < 105) _numSR["A28"]++;
                if(mT >= 160 && met >=200 && met < 250 && mll >= 75 && mll < 105) _numSR["A29"]++;
                if(mT >= 160 && met >=250 && met < 400 && mll >= 75 && mll < 105) _numSR["A30"]++;
                if(mT >= 160 && met >= 400 && mll >= 75 && mll < 105) _numSR["A31"]++;

                if(mT < 100 && met >=50 && met < 100 && mll >= 105) _numSR["A32"]++;
                if(mT < 100 && met >=100 && met < 150 && mll >= 105) _numSR["A33"]++;
                if(mT < 100 && met >=150 && met < 200 && mll >= 105) _numSR["A34"]++;
                if(mT < 100 && met >=200 && met < 250 && mll >= 105) _numSR["A35"]++;
                if(mT < 100 && met >=250 && mll >= 105) _numSR["A36"]++;
                
                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll >= 105) _numSR["A37"]++;
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll >= 105) _numSR["A38"]++;
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll >= 105) _numSR["A39"]++;
                if(mT >= 100 && mT < 160 && met >=200 && mll >= 105) _numSR["A40"]++;
                if(mT >= 160 && met >=50 && met < 100 && mll >= 105) _numSR["A41"]++;
                if(mT >= 160 && met >=100 && met < 150 && mll >= 105) _numSR["A42"]++;
                if(mT >= 160 && met >=150 && met < 200 && mll >= 105) _numSR["A43"]++;
                if(mT >= 160 && met >=200 && mll >= 105) _numSR["A44"]++;
                
              }
            }
          }
          
        }
        
      }

      
      void add(BaseAnalysis* other) {
        // The base class add function handles the signal region vector and total # events.
        
        HEPUtilsAnalysis::add(other);

        Analysis_CMS_13TeV_MultiLEP_Full_36invfb* specificOther
                = dynamic_cast<Analysis_CMS_13TeV_MultiLEP_Full_36invfb*>(other);

        // Here we will add the subclass member variables:
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
          el.second += specificOther->_numSR[el.first];
        }
      }


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        //Now fill a results object with the results for each SR

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SS01", 1193., {_numSR["SS01"], 0.}, {1430., 180.}));
        add_result(SignalRegionData("SS02", 50., {_numSR["SS02"], 0.}, {56., 9.}));
        add_result(SignalRegionData("SS03", 25., {_numSR["SS03"], 0.}, {36., 7.}));
        add_result(SignalRegionData("SS04", 7., {_numSR["SS04"], 0.}, {5.9, 1.2}));
        add_result(SignalRegionData("SS05", 2., {_numSR["SS05"], 0.}, {4.5, 3.5}));
        add_result(SignalRegionData("SS06", 143., {_numSR["SS06"], 0.}, {163., 19.}));
        add_result(SignalRegionData("SS07", 41., {_numSR["SS07"], 0.}, {38., 6.}));
        add_result(SignalRegionData("SS08", 24., {_numSR["SS08"], 0.}, {23., 4.}));
        add_result(SignalRegionData("SS09", 11., {_numSR["SS09"], 0.}, {14.4, 3.2}));
        add_result(SignalRegionData("SS10", 6., {_numSR["SS10"], 0.}, {6.3, 0.9}));
        add_result(SignalRegionData("SS11", 67., {_numSR["SS11"], 0.}, {82., 12.}));
        add_result(SignalRegionData("SS12", 19., {_numSR["SS12"], 0.}, {27., 4.}));
        add_result(SignalRegionData("SS13", 18., {_numSR["SS13"], 0.}, {18., 4.}));
        add_result(SignalRegionData("SS14", 9., {_numSR["SS14"], 0.}, {5.0, 0.8}));
        add_result(SignalRegionData("SS15", 3., {_numSR["SS15"], 0.}, {5.1, 2.6}));
        add_result(SignalRegionData("SS16", 591., {_numSR["SS16"], 0.}, {603., 80.}));
        add_result(SignalRegionData("SS17", 116., {_numSR["SS17"], 0.}, {98., 14.}));
        add_result(SignalRegionData("SS18", 69., {_numSR["SS18"], 0.}, {66., 10.}));
        add_result(SignalRegionData("SS19", 43., {_numSR["SS19"], 0.}, {33., 6.}));
        add_result(SignalRegionData("SS20", 13., {_numSR["SS20"], 0.}, {11.4, 1.7}));
        add_result(SignalRegionData("SS21", 232., {_numSR["SS21"], 0.}, {264., 31.}));
        add_result(SignalRegionData("SS22", 52., {_numSR["SS22"], 0.}, {51., 7.}));
        add_result(SignalRegionData("SS23", 35., {_numSR["SS23"], 0.}, {31., 4.}));
        add_result(SignalRegionData("SS24", 28., {_numSR["SS24"], 0.}, {29., 5.}));
        add_result(SignalRegionData("SS25", 27., {_numSR["SS25"], 0.}, {22.2, 3.4}));
        add_result(SignalRegionData("SS26", 49., {_numSR["SS26"], 0.}, {44., 7.}));
        add_result(SignalRegionData("SS27", 18., {_numSR["SS27"], 0.}, {16.4, 2.9}));
        add_result(SignalRegionData("SS28", 13., {_numSR["SS28"], 0.}, {10.7, 1.9}));
        add_result(SignalRegionData("SS29", 9., {_numSR["SS29"], 0.}, {6.7, 1.1}));
        add_result(SignalRegionData("SS30", 7., {_numSR["SS30"], 0.}, {3.9, 0.8}));
        
        add_result(SignalRegionData("A01", 186., {_numSR["A01"], 0.}, {185., 22.}));
        add_result(SignalRegionData("A02", 34., {_numSR["A02"], 0.}, {35., 6.}));
        add_result(SignalRegionData("A03", 11., {_numSR["A03"], 0.}, {9.3, 2.2}));
        add_result(SignalRegionData("A04", 1., {_numSR["A04"], 0.}, {3.3, 1.0}));
        add_result(SignalRegionData("A05", 5., {_numSR["A05"], 0.}, {4., 1.}));
        add_result(SignalRegionData("A06", 60., {_numSR["A06"], 0.}, {50., 8.}));
        add_result(SignalRegionData("A07", 19., {_numSR["A07"], 0.}, {15., 4.}));
        add_result(SignalRegionData("A08", 1., {_numSR["A08"], 0.}, {1.9, 0.6}));
        add_result(SignalRegionData("A09", 3., {_numSR["A09"], 0.}, {0.8, 0.4}));
        add_result(SignalRegionData("A10", 16., {_numSR["A10"], 0.}, {13., 2.8}));
        add_result(SignalRegionData("A11", 17., {_numSR["A11"], 0.}, {11.9, 3.2}));
        add_result(SignalRegionData("A12", 4., {_numSR["A12"], 0.}, {3.1, 1.2}));
        add_result(SignalRegionData("A13", 3., {_numSR["A13"], 0.}, {2.1, 0.8}));
        add_result(SignalRegionData("A14", 1., {_numSR["A14"], 0.}, {0.9, 0.4}));
        add_result(SignalRegionData("A15", 2278., {_numSR["A15"], 0.}, {2180., 260}));
        add_result(SignalRegionData("A16", 429., {_numSR["A16"], 0.}, {440., 70}));
        add_result(SignalRegionData("A17", 123., {_numSR["A17"], 0.}, {129., 28}));
        add_result(SignalRegionData("A18", 37., {_numSR["A18"], 0.}, {48., 10}));
        add_result(SignalRegionData("A19", 38., {_numSR["A19"], 0.}, {42., 9}));
        add_result(SignalRegionData("A20", 5., {_numSR["A20"], 0.}, {8.5, 2.1}));
        add_result(SignalRegionData("A21", 2., {_numSR["A21"], 0.}, {2.6, 0.8}));
        add_result(SignalRegionData("A22", 391., {_numSR["A22"], 0.}, {390, 50}));
        add_result(SignalRegionData("A23", 61., {_numSR["A23"], 0.}, {72, 19}));
        add_result(SignalRegionData("A24", 9., {_numSR["A24"], 0.}, {10, 4}));
        add_result(SignalRegionData("A25", 8., {_numSR["A25"], 0.}, {4.9, 1.9}));
        add_result(SignalRegionData("A26", 35., {_numSR["A26"], 0.}, {37, 9}));
        add_result(SignalRegionData("A27", 17., {_numSR["A27"], 0.}, {21., 8.}));
        add_result(SignalRegionData("A28", 7., {_numSR["A28"], 0.}, {8.9, 3.1}));
        add_result(SignalRegionData("A29", 5., {_numSR["A29"], 0.}, {3.6, 1.3}));
        add_result(SignalRegionData("A30", 3., {_numSR["A30"], 0.}, {4.1, 1.6}));
        add_result(SignalRegionData("A31", 1., {_numSR["A31"], 0.}, {1.0, 0.5}));
        add_result(SignalRegionData("A32", 123., {_numSR["A32"], 0.}, {121., 14.}));
        add_result(SignalRegionData("A33", 32., {_numSR["A33"], 0.}, {32.0, 5.}));
        add_result(SignalRegionData("A34", 4., {_numSR["A34"], 0.}, {11.6, 2.6}));
        add_result(SignalRegionData("A35", 6., {_numSR["A35"], 0.}, {2.9, 0.8}));
        add_result(SignalRegionData("A36", 5., {_numSR["A36"], 0.}, {3.7, 1.0}));
        add_result(SignalRegionData("A37", 17., {_numSR["A37"], 0.}, {32., 5.}));
        add_result(SignalRegionData("A38", 9., {_numSR["A38"], 0.}, {9.6, 2.4}));
        add_result(SignalRegionData("A39", 0., {_numSR["A39"], 0.}, {2.4, 0.7}));
        add_result(SignalRegionData("A40", 2., {_numSR["A40"], 0.}, {1.0, 0.4}));
        add_result(SignalRegionData("A41", 9., {_numSR["A41"], 0.}, {9.4, 2.4}));
        add_result(SignalRegionData("A42", 3., {_numSR["A42"], 0.}, {6.6, 2.1}));
        add_result(SignalRegionData("A43", 0., {_numSR["A43"], 0.}, {3.1, 1.0}));
        add_result(SignalRegionData("A44", 1., {_numSR["A44"], 0.}, {2.5, 0.8}));
                        
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
      void clear() {

        for (auto& el : _numSR) { el.second = 0.;}

        std::fill(cutFlowVector1.begin(), cutFlowVector1.end(), 0);
        std::fill(cutFlowVector2.begin(), cutFlowVector2.end(), 0);
        std::fill(cutFlowVector3.begin(), cutFlowVector3.end(), 0);
        std::fill(cutFlowVector4.begin(), cutFlowVector4.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_36invfb)




    // 
    // Derived analysis class for the 2Lep0Jets SRs
    // 
    class Analysis_CMS_13TeV_MultiLEP_Full_2SSLep_36invfb : public Analysis_CMS_13TeV_MultiLEP_Full_36invfb {

    public:
      Analysis_CMS_13TeV_MultiLEP_Full_2SSLep_36invfb() {
        set_analysis_name("CMS_13TeV_MultiLEP_Full_2SSLep_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SS01", 1193., {_numSR["SS01"], 0.}, {1430., 180.}));
        add_result(SignalRegionData("SS02", 50., {_numSR["SS02"], 0.}, {56., 9.}));
        add_result(SignalRegionData("SS03", 25., {_numSR["SS03"], 0.}, {36., 7.}));
        add_result(SignalRegionData("SS04", 7., {_numSR["SS04"], 0.}, {5.9, 1.2}));
        add_result(SignalRegionData("SS05", 2., {_numSR["SS05"], 0.}, {4.5, 3.5}));
        add_result(SignalRegionData("SS06", 143., {_numSR["SS06"], 0.}, {163., 19.}));
        add_result(SignalRegionData("SS07", 41., {_numSR["SS07"], 0.}, {38., 6.}));
        add_result(SignalRegionData("SS08", 24., {_numSR["SS08"], 0.}, {23., 4.}));
        add_result(SignalRegionData("SS09", 11., {_numSR["SS09"], 0.}, {14.4, 3.2}));
        add_result(SignalRegionData("SS10", 6., {_numSR["SS10"], 0.}, {6.3, 0.9}));
        add_result(SignalRegionData("SS11", 67., {_numSR["SS11"], 0.}, {82., 12.}));
        add_result(SignalRegionData("SS12", 19., {_numSR["SS12"], 0.}, {27., 4.}));
        add_result(SignalRegionData("SS13", 18., {_numSR["SS13"], 0.}, {18., 4.}));
        add_result(SignalRegionData("SS14", 9., {_numSR["SS14"], 0.}, {5.0, 0.8}));
        add_result(SignalRegionData("SS15", 3., {_numSR["SS15"], 0.}, {5.1, 2.6}));
        add_result(SignalRegionData("SS16", 591., {_numSR["SS16"], 0.}, {603., 80.}));
        add_result(SignalRegionData("SS17", 116., {_numSR["SS17"], 0.}, {98., 14.}));
        add_result(SignalRegionData("SS18", 69., {_numSR["SS18"], 0.}, {66., 10.}));
        add_result(SignalRegionData("SS19", 43., {_numSR["SS19"], 0.}, {33., 6.}));
        add_result(SignalRegionData("SS20", 13., {_numSR["SS20"], 0.}, {11.4, 1.7}));
        add_result(SignalRegionData("SS21", 232., {_numSR["SS21"], 0.}, {264., 31.}));
        add_result(SignalRegionData("SS22", 52., {_numSR["SS22"], 0.}, {51., 7.}));
        add_result(SignalRegionData("SS23", 35., {_numSR["SS23"], 0.}, {31., 4.}));
        add_result(SignalRegionData("SS24", 28., {_numSR["SS24"], 0.}, {29., 5.}));
        add_result(SignalRegionData("SS25", 27., {_numSR["SS25"], 0.}, {22.2, 3.4}));
        add_result(SignalRegionData("SS26", 49., {_numSR["SS26"], 0.}, {44., 7.}));
        add_result(SignalRegionData("SS27", 18., {_numSR["SS27"], 0.}, {16.4, 2.9}));
        add_result(SignalRegionData("SS28", 13., {_numSR["SS28"], 0.}, {10.7, 1.9}));
        add_result(SignalRegionData("SS29", 9., {_numSR["SS29"], 0.}, {6.7, 1.1}));
        add_result(SignalRegionData("SS30", 7., {_numSR["SS30"], 0.}, {3.9, 0.8}));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_2SSLep_36invfb)



    // 
    // Derived analysis class for the 3Lep SRs
    // 
    class Analysis_CMS_13TeV_MultiLEP_Full_3Lep_36invfb : public Analysis_CMS_13TeV_MultiLEP_Full_36invfb {

    public:
      Analysis_CMS_13TeV_MultiLEP_Full_3Lep_36invfb() {
        set_analysis_name("CMS_13TeV_MultiLEP_Full_3Lep_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("A01", 186., {_numSR["A01"], 0.}, {185., 22.}));
        add_result(SignalRegionData("A02", 34., {_numSR["A02"], 0.}, {35., 6.}));
        add_result(SignalRegionData("A03", 11., {_numSR["A03"], 0.}, {9.3, 2.2}));
        add_result(SignalRegionData("A04", 1., {_numSR["A04"], 0.}, {3.3, 1.0}));
        add_result(SignalRegionData("A05", 5., {_numSR["A05"], 0.}, {4., 1.}));
        add_result(SignalRegionData("A06", 60., {_numSR["A06"], 0.}, {50., 8.}));
        add_result(SignalRegionData("A07", 19., {_numSR["A07"], 0.}, {15., 4.}));
        add_result(SignalRegionData("A08", 1., {_numSR["A08"], 0.}, {1.9, 0.6}));
        add_result(SignalRegionData("A09", 3., {_numSR["A09"], 0.}, {0.8, 0.4}));
        add_result(SignalRegionData("A10", 16., {_numSR["A10"], 0.}, {13., 2.8}));
        add_result(SignalRegionData("A11", 17., {_numSR["A11"], 0.}, {11.9, 3.2}));
        add_result(SignalRegionData("A12", 4., {_numSR["A12"], 0.}, {3.1, 1.2}));
        add_result(SignalRegionData("A13", 3., {_numSR["A13"], 0.}, {2.1, 0.8}));
        add_result(SignalRegionData("A14", 1., {_numSR["A14"], 0.}, {0.9, 0.4}));
        add_result(SignalRegionData("A15", 2278., {_numSR["A15"], 0.}, {2180., 260}));
        add_result(SignalRegionData("A16", 429., {_numSR["A16"], 0.}, {440., 70}));
        add_result(SignalRegionData("A17", 123., {_numSR["A17"], 0.}, {129., 28}));
        add_result(SignalRegionData("A18", 37., {_numSR["A18"], 0.}, {48., 10}));
        add_result(SignalRegionData("A19", 38., {_numSR["A19"], 0.}, {42., 9}));
        add_result(SignalRegionData("A20", 5., {_numSR["A20"], 0.}, {8.5, 2.1}));
        add_result(SignalRegionData("A21", 2., {_numSR["A21"], 0.}, {2.6, 0.8}));
        add_result(SignalRegionData("A22", 391., {_numSR["A22"], 0.}, {390, 50}));
        add_result(SignalRegionData("A23", 61., {_numSR["A23"], 0.}, {72, 19}));
        add_result(SignalRegionData("A24", 9., {_numSR["A24"], 0.}, {10, 4}));
        add_result(SignalRegionData("A25", 8., {_numSR["A25"], 0.}, {4.9, 1.9}));
        add_result(SignalRegionData("A26", 35., {_numSR["A26"], 0.}, {37, 9}));
        add_result(SignalRegionData("A27", 17., {_numSR["A27"], 0.}, {21., 8.}));
        add_result(SignalRegionData("A28", 7., {_numSR["A28"], 0.}, {8.9, 3.1}));
        add_result(SignalRegionData("A29", 5., {_numSR["A29"], 0.}, {3.6, 1.3}));
        add_result(SignalRegionData("A30", 3., {_numSR["A30"], 0.}, {4.1, 1.6}));
        add_result(SignalRegionData("A31", 1., {_numSR["A31"], 0.}, {1.0, 0.5}));
        add_result(SignalRegionData("A32", 123., {_numSR["A32"], 0.}, {121., 14.}));
        add_result(SignalRegionData("A33", 32., {_numSR["A33"], 0.}, {32.0, 5.}));
        add_result(SignalRegionData("A34", 4., {_numSR["A34"], 0.}, {11.6, 2.6}));
        add_result(SignalRegionData("A35", 6., {_numSR["A35"], 0.}, {2.9, 0.8}));
        add_result(SignalRegionData("A36", 5., {_numSR["A36"], 0.}, {3.7, 1.0}));
        add_result(SignalRegionData("A37", 17., {_numSR["A37"], 0.}, {32., 5.}));
        add_result(SignalRegionData("A38", 9., {_numSR["A38"], 0.}, {9.6, 2.4}));
        add_result(SignalRegionData("A39", 0., {_numSR["A39"], 0.}, {2.4, 0.7}));
        add_result(SignalRegionData("A40", 2., {_numSR["A40"], 0.}, {1.0, 0.4}));
        add_result(SignalRegionData("A41", 9., {_numSR["A41"], 0.}, {9.4, 2.4}));
        add_result(SignalRegionData("A42", 3., {_numSR["A42"], 0.}, {6.6, 2.1}));
        add_result(SignalRegionData("A43", 0., {_numSR["A43"], 0.}, {3.1, 1.0}));
        add_result(SignalRegionData("A44", 1., {_numSR["A44"], 0.}, {2.5, 0.8}));
        
        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 1.0000e+00,  2.0228e-01,  1.1335e-01,  4.4046e-02,  9.7641e-02,  2.8937e-01,  2.1038e-01,  5.7065e-02,  1.2066e-01,  1.6606e-01,  1.6871e-01,  1.4569e-01,  8.2387e-02,  1.6095e-01,  4.8131e-02,  2.1867e-01, -1.3826e-02,  1.8487e-02, -2.1472e-02,  1.5374e-02,  1.1653e-01,  2.3701e-01, -1.5840e-02, -4.2613e-02,  7.2070e-02,  8.6325e-02, -1.5894e-02, -6.9892e-02,  5.8441e-02, -4.2601e-02,  1.0443e-01,  4.4695e-01,  2.0184e-01,  4.9732e-02,  9.9801e-02,  1.2136e-01,  1.0218e-01,  9.8825e-02,  8.0846e-02,  1.3444e-01,  6.4504e-02,  1.3902e-02,  9.5006e-02,  6.0029e-02},
          { 2.0228e-01,  1.0000e+00,  1.8674e-01,  2.0982e-01,  9.0400e-02,  3.2339e-01,  2.3686e-01,  8.0859e-02,  8.6043e-02,  2.0812e-02,  2.0273e-01,  1.5646e-01,  1.2634e-01,  1.1223e-01,  1.0335e-01,  1.1463e-01,  8.1864e-02,  8.2245e-02,  9.7400e-02,  9.5148e-02,  1.2736e-01,  1.3827e-01, -8.9534e-03,  6.8687e-02,  6.8874e-02,  6.1708e-02,  1.3644e-01,  6.8463e-02,  1.2284e-01,  3.6879e-02,  1.2688e-01,  2.6196e-01,  1.6031e-01,  9.8590e-02,  4.2227e-02,  1.7822e-01,  2.7910e-01,  2.3232e-01,  3.3301e-02,  1.1182e-01,  7.2020e-02,  1.5167e-01,  9.1464e-02,  1.2216e-01},
          { 1.1335e-01,  1.8674e-01,  1.0000e+00,  1.4521e-01,  1.0378e-01,  2.1482e-01,  1.9487e-01,  7.8490e-02,  1.0653e-01,  5.7438e-02,  1.7301e-01,  1.1991e-01,  1.0443e-01,  9.8684e-02,  7.0766e-02,  4.1059e-02,  1.2065e-01,  1.1323e-01,  1.1577e-01,  1.2309e-01,  6.8645e-02, -2.6895e-02,  3.8350e-02,  1.4624e-01,  1.2719e-01,  8.2236e-02,  1.3676e-01,  1.1708e-01,  1.2462e-01,  2.8139e-02,  1.8089e-01,  1.2989e-01,  8.7743e-02,  5.0295e-02,  5.6829e-02,  1.0868e-01,  1.3845e-01,  1.8731e-01,  6.6360e-02,  1.2653e-01,  1.1233e-01,  1.3569e-01,  6.9131e-02,  1.5137e-01},
          { 4.4046e-02,  2.0982e-01,  1.4521e-01,  1.0000e+00,  7.6767e-02,  1.3041e-01,  1.0138e-01,  9.3012e-02,  8.0329e-02,  4.7214e-02,  1.2525e-01,  1.1084e-01,  1.5989e-01,  1.5430e-01,  1.1716e-01,  1.0896e-01,  2.1295e-01,  1.7149e-01,  2.5899e-01,  1.8808e-01,  1.9550e-01,  3.8396e-02,  2.9454e-02,  1.2157e-01,  9.4219e-02,  1.0968e-01,  1.9725e-01,  1.7946e-01,  1.5765e-01,  1.2291e-01,  1.8739e-01,  5.1327e-02,  7.2608e-02,  1.0544e-01,  1.3156e-02,  1.7454e-01,  1.4392e-01,  1.6188e-01,  5.6080e-02,  1.1504e-01,  1.3824e-01,  1.7151e-01,  1.5356e-01,  2.3640e-01},
          { 9.7641e-02,  9.0400e-02,  1.0378e-01,  7.6767e-02,  1.0000e+00,  7.1181e-02,  1.1439e-01,  9.6606e-02,  8.6115e-02,  3.7157e-02,  5.8842e-02,  2.6483e-02,  5.6847e-02,  1.1350e-01,  4.3633e-02,  1.1795e-01,  1.8872e-01,  1.8962e-01,  1.5296e-01,  1.1401e-01,  9.3638e-02, -1.3727e-02,  9.9999e-02,  1.4688e-01,  1.1083e-01,  8.8776e-02,  1.5735e-01,  1.4434e-01,  9.3733e-02,  1.1637e-01,  1.0510e-01,  6.7417e-02,  9.7065e-02,  1.7701e-02,  5.3530e-02,  8.3210e-02,  2.0798e-03,  4.2731e-02,  6.4968e-02,  1.1736e-01,  3.8202e-02,  9.6499e-02,  5.6981e-02,  1.0302e-01},
          { 2.8937e-01,  3.2339e-01,  2.1482e-01,  1.3041e-01,  7.1181e-02,  1.0000e+00,  3.0816e-01,  2.3089e-03,  1.0302e-01,  8.4324e-02,  2.3235e-01,  2.2917e-01,  1.0612e-01,  1.1340e-01,  6.8957e-02,  1.8108e-02, -5.5104e-02, -7.0603e-02, -3.0135e-02,  1.0717e-02,  7.7763e-02,  1.6833e-01, -4.0424e-02,  2.8378e-02,  8.8907e-02,  3.9294e-02,  7.3524e-02,  1.1438e-02,  1.1647e-01, -5.0789e-02,  8.5858e-02,  3.7180e-01,  1.1715e-01,  4.0485e-02,  5.7817e-02,  1.9487e-01,  3.1889e-01,  3.3487e-01,  6.5182e-02,  7.9706e-02,  5.8976e-02,  1.3074e-01,  5.0216e-02,  4.3983e-02},
          { 2.1038e-01,  2.3686e-01,  1.9487e-01,  1.0138e-01,  1.1439e-01,  3.0816e-01,  1.0000e+00,  5.7850e-02,  1.0980e-01,  1.1984e-01,  2.4599e-01,  2.0747e-01,  1.4701e-01,  1.0636e-01,  6.5179e-02, -7.6108e-02, -3.0631e-02, -2.8621e-02, -1.6332e-02,  1.9684e-02,  5.5554e-02,  9.5073e-03,  8.9701e-02,  1.1351e-01,  1.3903e-01,  1.0535e-01,  1.3426e-01,  6.7687e-02,  1.3655e-01,  5.9883e-03,  1.9770e-01,  2.5687e-01,  1.5441e-01,  7.6360e-02,  1.2227e-01,  1.6813e-01,  1.5846e-01,  2.8803e-01,  5.6710e-02,  1.0401e-01,  9.5301e-02,  1.2104e-01,  1.0649e-01,  1.0901e-01},
          { 5.7065e-02,  8.0859e-02,  7.8490e-02,  9.3012e-02,  9.6606e-02,  2.3089e-03,  5.7850e-02,  1.0000e+00,  5.0084e-02,  9.9954e-02,  1.0676e-01,  4.4242e-02,  9.7371e-02,  1.3082e-01,  7.6924e-02,  2.0765e-02,  1.1012e-01,  1.5020e-01,  1.5013e-01,  6.1941e-02,  9.1560e-02, -2.1205e-02,  1.7058e-01,  1.9297e-01,  1.4811e-01,  1.3530e-01,  1.1306e-01,  1.6124e-01,  8.4161e-02,  1.6250e-01,  1.4820e-01,  2.1779e-02,  7.5954e-02, -4.9073e-03,  1.4041e-01,  1.0315e-01, -1.6784e-03,  1.0329e-01,  1.1228e-01,  1.6778e-01,  1.4062e-01,  1.5535e-01,  9.7554e-02,  2.1475e-01},
          { 1.2066e-01,  8.6043e-02,  1.0653e-01,  8.0329e-02,  8.6115e-02,  1.0302e-01,  1.0980e-01,  5.0084e-02,  1.0000e+00,  7.1684e-02,  1.4898e-01,  5.4052e-02,  8.6505e-02,  1.1035e-01,  8.1210e-02,  1.6259e-02,  4.3250e-02,  9.6351e-02,  7.6209e-02,  8.3299e-02,  9.3809e-02,  5.6958e-05,  6.5669e-02,  6.8308e-02,  1.2789e-01,  9.1617e-02,  4.9242e-02,  7.8882e-02,  5.2276e-02,  5.6372e-02,  1.0064e-01,  9.8311e-02,  6.7082e-02,  3.7161e-02,  7.1722e-02,  1.2020e-01,  3.7041e-02,  6.9547e-02,  4.6915e-02,  1.1856e-01,  1.2602e-01,  5.0945e-02,  8.9028e-02,  1.5833e-01},
          { 1.6606e-01,  2.0812e-02,  5.7438e-02,  4.7214e-02,  3.7157e-02,  8.4324e-02,  1.1984e-01,  9.9954e-02,  7.1684e-02,  1.0000e+00,  1.0540e-01,  1.1387e-01,  1.0496e-01,  1.2084e-01,  6.4703e-02, -6.0968e-02,  6.0833e-02,  4.5100e-02, -4.5992e-03,  2.7843e-02,  2.6046e-02, -2.1615e-02,  1.9065e-01,  1.3228e-01,  1.2984e-01,  1.9206e-01,  1.6691e-01,  1.0052e-01,  7.2690e-02,  9.5101e-02,  8.9881e-02,  1.1069e-01,  6.0612e-02,  4.2101e-02,  7.9726e-02,  1.0876e-01, -1.4626e-02,  9.2729e-02,  1.1506e-01,  8.6308e-02,  1.2314e-01,  4.7397e-02,  3.4093e-02,  1.1124e-01},
          { 1.6871e-01,  2.0273e-01,  1.7301e-01,  1.2525e-01,  5.8842e-02,  2.3235e-01,  2.4599e-01,  1.0676e-01,  1.4898e-01,  1.0540e-01,  1.0000e+00,  1.3251e-01,  1.6529e-01,  1.0734e-01,  7.0865e-02, -7.4120e-02,  2.5991e-02,  1.4633e-02,  3.3621e-02,  6.1972e-02,  8.8990e-02, -5.3569e-02,  5.3970e-02,  9.2057e-02,  8.6998e-02,  8.4427e-02,  1.1292e-01,  1.1476e-01,  1.3493e-01,  4.3036e-02,  1.3765e-01,  1.8145e-01,  1.2544e-01,  6.1706e-02,  6.4158e-02,  1.4464e-01,  1.0195e-01,  2.0320e-01,  7.7415e-02,  6.7246e-02,  1.0163e-01,  1.4238e-01,  7.2226e-02,  1.3796e-01},
          { 1.4569e-01,  1.5646e-01,  1.1991e-01,  1.1084e-01,  2.6483e-02,  2.2917e-01,  2.0747e-01,  4.4242e-02,  5.4052e-02,  1.1387e-01,  1.3251e-01,  1.0000e+00,  5.1032e-02,  9.9229e-02,  4.5500e-02, -1.0313e-02,  3.0592e-02,  2.6751e-02,  7.6016e-03,  4.5740e-02,  8.3097e-02,  9.6176e-02,  1.2372e-01,  1.8042e-01,  9.6960e-02,  1.5183e-01,  9.2604e-02,  3.4829e-02,  1.2179e-01, -3.5543e-02,  9.8623e-02,  1.6368e-01,  6.7128e-02, -3.6812e-04,  8.2434e-02,  1.5537e-01,  2.1165e-01,  2.3020e-01,  4.1648e-02,  8.7335e-02,  1.3797e-01,  1.5322e-01,  4.0611e-02,  9.0265e-02},
          { 8.2387e-02,  1.2634e-01,  1.0443e-01,  1.5989e-01,  5.6847e-02,  1.0612e-01,  1.4701e-01,  9.7371e-02,  8.6505e-02,  1.0496e-01,  1.6529e-01,  5.1032e-02,  1.0000e+00,  1.2119e-01,  1.3232e-01,  1.0550e-02,  1.3137e-01,  1.3682e-01,  1.8779e-01,  9.2717e-02,  1.5064e-01, -4.8702e-02,  5.3563e-02,  7.8067e-02,  4.6262e-02,  9.9181e-02,  1.6259e-01,  1.5451e-01,  1.1043e-01,  1.5121e-01,  1.5910e-01,  5.9582e-02,  1.2909e-01,  7.9110e-02,  4.5945e-02,  1.4780e-01,  1.9275e-02,  8.3454e-02,  4.7167e-02,  1.0978e-01,  5.4840e-02,  9.4811e-02,  1.2204e-01,  1.8202e-01},
          { 1.6095e-01,  1.1223e-01,  9.8684e-02,  1.5430e-01,  1.1350e-01,  1.1340e-01,  1.0636e-01,  1.3082e-01,  1.1035e-01,  1.2084e-01,  1.0734e-01,  9.9229e-02,  1.2119e-01,  1.0000e+00,  1.5866e-01,  7.9477e-02,  1.2842e-01,  1.2996e-01,  1.1658e-01,  4.7661e-02,  2.1142e-01,  7.3365e-02,  1.2086e-01,  1.8966e-01,  8.9364e-02,  1.0782e-01,  1.1685e-01,  1.0223e-01,  8.3253e-02,  1.4972e-01,  2.7592e-01,  1.1741e-01,  1.0984e-01,  6.2514e-03,  9.1998e-02,  1.2436e-01,  6.1880e-02,  1.0734e-01,  9.3786e-02,  1.4546e-01,  7.9179e-02,  9.6762e-02,  1.5340e-01,  2.5984e-01},
          { 4.8131e-02,  1.0335e-01,  7.0766e-02,  1.1716e-01,  4.3633e-02,  6.8957e-02,  6.5179e-02,  7.6924e-02,  8.1210e-02,  6.4703e-02,  7.0865e-02,  4.5500e-02,  1.3232e-01,  1.5866e-01,  1.0000e+00, -4.8826e-02,  5.7428e-02,  7.6283e-02,  8.2259e-02,  6.2602e-02,  1.4526e-01, -5.9783e-02,  4.3072e-02,  6.9630e-02,  7.5870e-02,  1.7194e-02,  1.0399e-01,  1.2073e-01,  8.7657e-02,  8.0165e-02,  1.8625e-01,  2.8749e-03,  4.3064e-02,  5.9196e-02,  4.6893e-02,  9.6581e-02, -3.1017e-02,  6.6090e-02,  7.6704e-02,  1.1014e-01,  5.7752e-02,  5.7079e-02,  1.1345e-01,  1.9202e-01},
          { 2.1867e-01,  1.1463e-01,  4.1059e-02,  1.0896e-01,  1.1795e-01,  1.8108e-02, -7.6108e-02,  2.0765e-02,  1.6259e-02, -6.0968e-02, -7.4120e-02, -1.0313e-02,  1.0550e-02,  7.9477e-02, -4.8826e-02,  1.0000e+00,  5.5240e-01,  4.2402e-01,  3.2843e-01,  1.8952e-01,  1.5066e-01,  5.2737e-01,  7.0856e-02,  5.1666e-02, -3.3700e-02,  6.1515e-02,  6.3630e-02,  7.9605e-02,  2.5309e-02,  1.2140e-01,  7.8622e-02,  2.3805e-01,  1.8934e-01,  3.1302e-02,  2.5697e-02,  6.0366e-02,  8.4613e-02, -3.9475e-02,  5.1491e-03,  2.0648e-02, -4.1204e-03,  3.3597e-02,  5.9546e-02,  6.5120e-02},
          {-1.3826e-02,  8.1864e-02,  1.2065e-01,  2.1295e-01,  1.8872e-01, -5.5104e-02, -3.0631e-02,  1.1012e-01,  4.3250e-02,  6.0833e-02,  2.5991e-02,  3.0592e-02,  1.3137e-01,  1.2842e-01,  5.7428e-02,  5.5240e-01,  1.0000e+00,  5.9883e-01,  4.7147e-01,  2.6090e-01,  1.9992e-01,  8.5094e-02,  2.9350e-01,  3.1615e-01,  1.1801e-01,  2.2217e-01,  3.9753e-01,  3.3568e-01,  1.3597e-01,  3.2538e-01,  1.5748e-01,  4.8516e-03,  1.2019e-01,  7.3133e-02,  2.6656e-02,  1.0242e-01, -1.8406e-02,  1.4665e-02,  4.1861e-02,  8.7491e-02,  9.3026e-02,  2.0509e-01,  1.0368e-01,  2.0794e-01},
          { 1.8487e-02,  8.2245e-02,  1.1323e-01,  1.7149e-01,  1.8962e-01, -7.0603e-02, -2.8621e-02,  1.5020e-01,  9.6351e-02,  4.5100e-02,  1.4633e-02,  2.6751e-02,  1.3682e-01,  1.2996e-01,  7.6283e-02,  4.2402e-01,  5.9883e-01,  1.0000e+00,  4.6233e-01,  2.5847e-01,  1.8964e-01,  3.3862e-02,  2.2412e-01,  2.6027e-01,  1.4171e-01,  1.8780e-01,  3.1044e-01,  2.9350e-01,  1.2241e-01,  2.9390e-01,  1.7826e-01,  2.2558e-03,  1.1613e-01,  7.9387e-02,  7.7436e-02,  1.2085e-01, -9.6011e-03, -6.8713e-03,  8.5234e-02,  1.2421e-01,  1.1437e-01,  1.9674e-01,  1.4786e-01,  2.4037e-01},
          {-2.1472e-02,  9.7400e-02,  1.1577e-01,  2.5899e-01,  1.5296e-01, -3.0135e-02, -1.6332e-02,  1.5013e-01,  7.6209e-02, -4.5992e-03,  3.3621e-02,  7.6016e-03,  1.8779e-01,  1.1658e-01,  8.2259e-02,  3.2843e-01,  4.7147e-01,  4.6233e-01,  1.0000e+00,  2.7724e-01,  2.1482e-01,  4.8983e-02,  1.3517e-01,  1.7305e-01,  1.1528e-01,  1.6930e-01,  2.9881e-01,  2.9203e-01,  1.7753e-01,  2.6797e-01,  1.3484e-01, -1.6473e-02,  1.4585e-01,  1.4498e-01,  4.9001e-03,  1.4107e-01,  2.9989e-03,  2.9525e-02,  6.4557e-02,  7.7885e-02,  1.1756e-01,  1.8265e-01,  1.9091e-01,  2.3035e-01},
          { 1.5374e-02,  9.5148e-02,  1.2309e-01,  1.8808e-01,  1.1401e-01,  1.0717e-02,  1.9684e-02,  6.1941e-02,  8.3299e-02,  2.7843e-02,  6.1972e-02,  4.5740e-02,  9.2717e-02,  4.7661e-02,  6.2602e-02,  1.8952e-01,  2.6090e-01,  2.5847e-01,  2.7724e-01,  1.0000e+00,  1.1697e-01,  4.2862e-03,  2.6106e-02,  1.0364e-01,  7.1474e-02,  7.9620e-02,  1.5139e-01,  1.2266e-01,  8.0497e-02,  1.3977e-01,  1.2153e-01,  3.4252e-03,  7.7027e-02,  4.3517e-02,  7.0249e-02,  8.0653e-02,  7.4723e-02,  7.7814e-02,  7.8241e-02,  7.4288e-02,  1.2256e-01,  1.2458e-01,  8.6965e-02,  1.7494e-01},
          { 1.1653e-01,  1.2736e-01,  6.8645e-02,  1.9550e-01,  9.3638e-02,  7.7763e-02,  5.5554e-02,  9.1560e-02,  9.3809e-02,  2.6046e-02,  8.8990e-02,  8.3097e-02,  1.5064e-01,  2.1142e-01,  1.4526e-01,  1.5066e-01,  1.9992e-01,  1.8964e-01,  2.1482e-01,  1.1697e-01,  1.0000e+00,  1.2139e-01,  3.4947e-02,  8.5753e-02,  9.2919e-02,  6.7441e-02,  8.7716e-02,  1.1294e-01,  1.1946e-01,  7.0881e-02,  2.4392e-01,  1.3730e-01,  1.3415e-01,  5.8563e-02,  8.5974e-02,  1.4096e-01,  6.4124e-02,  8.1710e-02,  5.7265e-02,  9.7189e-02,  9.0355e-02,  1.1260e-01,  1.9106e-01,  2.3800e-01},
          { 2.3701e-01,  1.3827e-01, -2.6895e-02,  3.8396e-02, -1.3727e-02,  1.6833e-01,  9.5073e-03, -2.1205e-02,  5.6958e-05, -2.1615e-02, -5.3569e-02,  9.6176e-02, -4.8702e-02,  7.3365e-02, -5.9783e-02,  5.2737e-01,  8.5094e-02,  3.3862e-02,  4.8983e-02,  4.2862e-03,  1.2139e-01,  1.0000e+00,  1.5549e-01,  1.2506e-02, -1.8938e-02,  4.9676e-02, -1.1812e-01, -9.1671e-02,  2.6141e-02, -7.6453e-02,  8.0942e-03,  3.2249e-01,  1.4758e-01,  1.4581e-02,  5.0226e-02,  3.7083e-02,  2.3818e-01,  8.6773e-02, -5.7989e-02, -2.5902e-02,  1.9538e-02, -2.2801e-02, -6.5519e-04, -9.0815e-04},
          {-1.5840e-02, -8.9534e-03,  3.8350e-02,  2.9454e-02,  9.9999e-02, -4.0424e-02,  8.9701e-02,  1.7058e-01,  6.5669e-02,  1.9065e-01,  5.3970e-02,  1.2372e-01,  5.3563e-02,  1.2086e-01,  4.3072e-02,  7.0856e-02,  2.9350e-01,  2.2412e-01,  1.3517e-01,  2.6106e-02,  3.4947e-02,  1.5549e-01,  1.0000e+00,  5.0487e-01,  2.7686e-01,  3.5223e-01,  2.7011e-01,  2.8431e-01,  7.9431e-02,  2.3114e-01,  9.5494e-02, -1.3323e-02,  8.1571e-02, -4.7117e-02,  1.8597e-01,  2.4144e-02, -3.5807e-02,  8.9228e-02,  2.0459e-02,  6.5997e-02,  1.3936e-01,  1.5020e-01,  3.4232e-02,  1.2801e-01},
          {-4.2613e-02,  6.8687e-02,  1.4624e-01,  1.2157e-01,  1.4688e-01,  2.8378e-02,  1.1351e-01,  1.9297e-01,  6.8308e-02,  1.3228e-01,  9.2057e-02,  1.8042e-01,  7.8067e-02,  1.8966e-01,  6.9630e-02,  5.1666e-02,  3.1615e-01,  2.6027e-01,  1.7305e-01,  1.0364e-01,  8.5753e-02,  1.2506e-02,  5.0487e-01,  1.0000e+00,  2.3305e-01,  3.0365e-01,  3.0115e-01,  3.0094e-01,  1.1268e-01,  2.1632e-01,  2.0822e-01, -1.4432e-02,  3.2344e-02, -5.1117e-02,  1.9659e-01,  1.5158e-01,  5.7523e-02,  1.7971e-01,  7.6340e-02,  1.4074e-01,  1.8418e-01,  2.3247e-01,  7.1326e-02,  2.2015e-01},
          { 7.2070e-02,  6.8874e-02,  1.2719e-01,  9.4219e-02,  1.1083e-01,  8.8907e-02,  1.3903e-01,  1.4811e-01,  1.2789e-01,  1.2984e-01,  8.6998e-02,  9.6960e-02,  4.6262e-02,  8.9364e-02,  7.5870e-02, -3.3700e-02,  1.1801e-01,  1.4171e-01,  1.1528e-01,  7.1474e-02,  9.2919e-02, -1.8938e-02,  2.7686e-01,  2.3305e-01,  1.0000e+00,  1.4381e-01,  1.3779e-01,  1.6277e-01,  1.3065e-01,  1.0695e-01,  1.5529e-01,  7.4666e-02,  8.0743e-02,  1.2881e-02,  1.5137e-01,  1.2453e-01,  3.4087e-02,  1.2281e-01,  9.0588e-02,  1.2469e-01,  1.3406e-01,  1.2653e-01,  7.9526e-02,  1.7116e-01},
          { 8.6325e-02,  6.1708e-02,  8.2236e-02,  1.0968e-01,  8.8776e-02,  3.9294e-02,  1.0535e-01,  1.3530e-01,  9.1617e-02,  1.9206e-01,  8.4427e-02,  1.5183e-01,  9.9181e-02,  1.0782e-01,  1.7194e-02,  6.1515e-02,  2.2217e-01,  1.8780e-01,  1.6930e-01,  7.9620e-02,  6.7441e-02,  4.9676e-02,  3.5223e-01,  3.0365e-01,  1.4381e-01,  1.0000e+00,  2.6084e-01,  2.5038e-01,  1.2643e-01,  1.7501e-01,  1.1803e-01,  7.2411e-02,  3.3590e-02, -3.6021e-03,  9.1802e-02,  8.4859e-02,  4.9420e-02,  1.1792e-01,  7.8535e-02,  1.2465e-01,  2.0029e-01,  1.7617e-01,  8.2208e-02,  1.4534e-01},
          {-1.5894e-02,  1.3644e-01,  1.3676e-01,  1.9725e-01,  1.5735e-01,  7.3524e-02,  1.3426e-01,  1.1306e-01,  4.9242e-02,  1.6691e-01,  1.1292e-01,  9.2604e-02,  1.6259e-01,  1.1685e-01,  1.0399e-01,  6.3630e-02,  3.9753e-01,  3.1044e-01,  2.9881e-01,  1.5139e-01,  8.7716e-02, -1.1812e-01,  2.7011e-01,  3.0115e-01,  1.3779e-01,  2.6084e-01,  1.0000e+00,  4.1415e-01,  2.3117e-01,  2.6685e-01,  1.3371e-01,  1.4023e-03,  5.5772e-02,  1.3468e-01,  1.6773e-02,  1.3475e-01,  5.3504e-02,  1.7627e-01,  4.3538e-02,  8.5594e-02,  1.1904e-01,  2.2754e-01,  1.2673e-01,  1.8402e-01},
          {-6.9892e-02,  6.8463e-02,  1.1708e-01,  1.7946e-01,  1.4434e-01,  1.1438e-02,  6.7687e-02,  1.6124e-01,  7.8882e-02,  1.0052e-01,  1.1476e-01,  3.4829e-02,  1.5451e-01,  1.0223e-01,  1.2073e-01,  7.9605e-02,  3.3568e-01,  2.9350e-01,  2.9203e-01,  1.2266e-01,  1.1294e-01, -9.1671e-02,  2.8431e-01,  3.0094e-01,  1.6277e-01,  2.5038e-01,  4.1415e-01,  1.0000e+00,  1.9992e-01,  2.9272e-01,  1.5920e-01, -1.4457e-02,  6.9422e-02,  1.0291e-01,  3.8020e-02,  1.3020e-01,  4.9825e-02,  1.1973e-01,  6.1618e-02,  1.1103e-01,  1.5057e-01,  2.0307e-01,  1.3121e-01,  2.1939e-01},
          { 5.8441e-02,  1.2284e-01,  1.2462e-01,  1.5765e-01,  9.3733e-02,  1.1647e-01,  1.3655e-01,  8.4161e-02,  5.2276e-02,  7.2690e-02,  1.3493e-01,  1.2179e-01,  1.1043e-01,  8.3253e-02,  8.7657e-02,  2.5309e-02,  1.3597e-01,  1.2241e-01,  1.7753e-01,  8.0497e-02,  1.1946e-01,  2.6141e-02,  7.9431e-02,  1.1268e-01,  1.3065e-01,  1.2643e-01,  2.3117e-01,  1.9992e-01,  1.0000e+00,  1.4153e-01,  1.5419e-01,  7.9963e-02,  6.2537e-02,  1.0033e-01,  4.1276e-02,  1.6311e-01,  1.1654e-01,  1.7773e-01,  6.4017e-03,  7.9735e-02,  8.9278e-02,  1.5291e-01,  1.2220e-01,  1.5605e-01},
          {-4.2601e-02,  3.6879e-02,  2.8139e-02,  1.2291e-01,  1.1637e-01, -5.0789e-02,  5.9883e-03,  1.6250e-01,  5.6372e-02,  9.5101e-02,  4.3036e-02, -3.5543e-02,  1.5121e-01,  1.4972e-01,  8.0165e-02,  1.2140e-01,  3.2538e-01,  2.9390e-01,  2.6797e-01,  1.3977e-01,  7.0881e-02, -7.6453e-02,  2.3114e-01,  2.1632e-01,  1.0695e-01,  1.7501e-01,  2.6685e-01,  2.9272e-01,  1.4153e-01,  1.0000e+00,  1.3437e-01, -5.3806e-02,  3.9179e-02,  8.8695e-02,  8.7950e-02,  1.0426e-01, -5.7021e-02,  4.3569e-02,  7.8257e-02,  1.2031e-01,  6.2893e-02,  1.8103e-01,  1.2219e-01,  2.0015e-01},
          { 1.0443e-01,  1.2688e-01,  1.8089e-01,  1.8739e-01,  1.0510e-01,  8.5858e-02,  1.9770e-01,  1.4820e-01,  1.0064e-01,  8.9881e-02,  1.3765e-01,  9.8623e-02,  1.5910e-01,  2.7592e-01,  1.8625e-01,  7.8622e-02,  1.5748e-01,  1.7826e-01,  1.3484e-01,  1.2153e-01,  2.4392e-01,  8.0942e-03,  9.5494e-02,  2.0822e-01,  1.5529e-01,  1.1803e-01,  1.3371e-01,  1.5920e-01,  1.5419e-01,  1.3437e-01,  1.0000e+00,  1.4145e-01,  1.0283e-01,  5.5121e-02,  1.3041e-01,  1.8888e-01,  4.1437e-02,  1.1926e-01,  1.1212e-01,  2.0730e-01,  1.5006e-01,  1.6000e-01,  1.7149e-01,  2.8887e-01},
          { 4.4695e-01,  2.6196e-01,  1.2989e-01,  5.1327e-02,  6.7417e-02,  3.7180e-01,  2.5687e-01,  2.1779e-02,  9.8311e-02,  1.1069e-01,  1.8145e-01,  1.6368e-01,  5.9582e-02,  1.1741e-01,  2.8749e-03,  2.3805e-01,  4.8516e-03,  2.2558e-03, -1.6473e-02,  3.4252e-03,  1.3730e-01,  3.2249e-01, -1.3323e-02, -1.4432e-02,  7.4666e-02,  7.2411e-02,  1.4023e-03, -1.4457e-02,  7.9963e-02, -5.3806e-02,  1.4145e-01,  1.0000e+00,  1.9528e-01,  2.3782e-02,  9.7128e-02,  1.6933e-01,  1.9779e-01,  2.1514e-01,  5.1147e-02,  1.1256e-01,  7.0117e-02,  4.8318e-02,  4.9123e-02,  7.0170e-02},
          { 2.0184e-01,  1.6031e-01,  8.7743e-02,  7.2608e-02,  9.7065e-02,  1.1715e-01,  1.5441e-01,  7.5954e-02,  6.7082e-02,  6.0612e-02,  1.2544e-01,  6.7128e-02,  1.2909e-01,  1.0984e-01,  4.3064e-02,  1.8934e-01,  1.2019e-01,  1.1613e-01,  1.4585e-01,  7.7027e-02,  1.3415e-01,  1.4758e-01,  8.1571e-02,  3.2344e-02,  8.0743e-02,  3.3590e-02,  5.5772e-02,  6.9422e-02,  6.2537e-02,  3.9179e-02,  1.0283e-01,  1.9528e-01,  1.0000e+00,  4.2490e-02,  1.1544e-01,  1.1889e-01,  7.9291e-02,  1.0963e-01,  6.8220e-02,  9.4117e-02,  3.1213e-02,  7.2392e-02,  8.0171e-02,  1.0715e-01},
          { 4.9732e-02,  9.8590e-02,  5.0295e-02,  1.0544e-01,  1.7701e-02,  4.0485e-02,  7.6360e-02, -4.9073e-03,  3.7161e-02,  4.2101e-02,  6.1706e-02, -3.6812e-04,  7.9110e-02,  6.2514e-03,  5.9196e-02,  3.1302e-02,  7.3133e-02,  7.9387e-02,  1.4498e-01,  4.3517e-02,  5.8563e-02,  1.4581e-02, -4.7117e-02, -5.1117e-02,  1.2881e-02, -3.6021e-03,  1.3468e-01,  1.0291e-01,  1.0033e-01,  8.8695e-02,  5.5121e-02,  2.3782e-02,  4.2490e-02,  1.0000e+00, -2.6790e-02,  6.0383e-02,  1.7480e-02,  4.4780e-02,  1.1685e-02,  5.5346e-03, -7.2764e-03,  4.3055e-02,  4.8122e-02,  4.4980e-02},
          { 9.9801e-02,  4.2227e-02,  5.6829e-02,  1.3156e-02,  5.3530e-02,  5.7817e-02,  1.2227e-01,  1.4041e-01,  7.1722e-02,  7.9726e-02,  6.4158e-02,  8.2434e-02,  4.5945e-02,  9.1998e-02,  4.6893e-02,  2.5697e-02,  2.6656e-02,  7.7436e-02,  4.9001e-03,  7.0249e-02,  8.5974e-02,  5.0226e-02,  1.8597e-01,  1.9659e-01,  1.5137e-01,  9.1802e-02,  1.6773e-02,  3.8020e-02,  4.1276e-02,  8.7950e-02,  1.3041e-01,  9.7128e-02,  1.1544e-01, -2.6790e-02,  1.0000e+00,  1.1710e-01, -1.0026e-02,  8.0328e-02,  1.4482e-01,  1.3461e-01,  9.0543e-02,  7.0879e-02,  3.0563e-02,  1.5109e-01},
          { 1.2136e-01,  1.7822e-01,  1.0868e-01,  1.7454e-01,  8.3210e-02,  1.9487e-01,  1.6813e-01,  1.0315e-01,  1.2020e-01,  1.0876e-01,  1.4464e-01,  1.5537e-01,  1.4780e-01,  1.2436e-01,  9.6581e-02,  6.0366e-02,  1.0242e-01,  1.2085e-01,  1.4107e-01,  8.0653e-02,  1.4096e-01,  3.7083e-02,  2.4144e-02,  1.5158e-01,  1.2453e-01,  8.4859e-02,  1.3475e-01,  1.3020e-01,  1.6311e-01,  1.0426e-01,  1.8888e-01,  1.6933e-01,  1.1889e-01,  6.0383e-02,  1.1710e-01,  1.0000e+00,  1.7882e-01,  2.0999e-01,  9.7219e-02,  1.3142e-01,  6.8555e-02,  2.0611e-01,  1.0046e-01,  1.8898e-01},
          { 1.0218e-01,  2.7910e-01,  1.3845e-01,  1.4392e-01,  2.0798e-03,  3.1889e-01,  1.5846e-01, -1.6784e-03,  3.7041e-02, -1.4626e-02,  1.0195e-01,  2.1165e-01,  1.9275e-02,  6.1880e-02, -3.1017e-02,  8.4613e-02, -1.8406e-02, -9.6011e-03,  2.9989e-03,  7.4723e-02,  6.4124e-02,  2.3818e-01, -3.5807e-02,  5.7523e-02,  3.4087e-02,  4.9420e-02,  5.3504e-02,  4.9825e-02,  1.1654e-01, -5.7021e-02,  4.1437e-02,  1.9779e-01,  7.9291e-02,  1.7480e-02, -1.0026e-02,  1.7882e-01,  1.0000e+00,  2.7976e-01,  4.4151e-03,  1.4929e-02,  5.1666e-02,  1.4814e-01, -6.9593e-04,  5.3976e-02},
          { 9.8825e-02,  2.3232e-01,  1.8731e-01,  1.6188e-01,  4.2731e-02,  3.3487e-01,  2.8803e-01,  1.0329e-01,  6.9547e-02,  9.2729e-02,  2.0320e-01,  2.3020e-01,  8.3454e-02,  1.0734e-01,  6.6090e-02, -3.9475e-02,  1.4665e-02, -6.8713e-03,  2.9525e-02,  7.7814e-02,  8.1710e-02,  8.6773e-02,  8.9228e-02,  1.7971e-01,  1.2281e-01,  1.1792e-01,  1.7627e-01,  1.1973e-01,  1.7773e-01,  4.3569e-02,  1.1926e-01,  2.1514e-01,  1.0963e-01,  4.4780e-02,  8.0328e-02,  2.0999e-01,  2.7976e-01,  1.0000e+00,  2.2796e-02,  1.0143e-01,  1.6014e-01,  1.8088e-01,  9.3910e-02,  1.7642e-01},
          { 8.0846e-02,  3.3301e-02,  6.6360e-02,  5.6080e-02,  6.4968e-02,  6.5182e-02,  5.6710e-02,  1.1228e-01,  4.6915e-02,  1.1506e-01,  7.7415e-02,  4.1648e-02,  4.7167e-02,  9.3786e-02,  7.6704e-02,  5.1491e-03,  4.1861e-02,  8.5234e-02,  6.4557e-02,  7.8241e-02,  5.7265e-02, -5.7989e-02,  2.0459e-02,  7.6340e-02,  9.0588e-02,  7.8535e-02,  4.3538e-02,  6.1618e-02,  6.4017e-03,  7.8257e-02,  1.1212e-01,  5.1147e-02,  6.8220e-02,  1.1685e-02,  1.4482e-01,  9.7219e-02,  4.4151e-03,  2.2796e-02,  1.0000e+00,  1.1878e-01,  1.0870e-01,  1.2472e-01,  8.4628e-02,  1.6845e-01},
          { 1.3444e-01,  1.1182e-01,  1.2653e-01,  1.1504e-01,  1.1736e-01,  7.9706e-02,  1.0401e-01,  1.6778e-01,  1.1856e-01,  8.6308e-02,  6.7246e-02,  8.7335e-02,  1.0978e-01,  1.4546e-01,  1.1014e-01,  2.0648e-02,  8.7491e-02,  1.2421e-01,  7.7885e-02,  7.4288e-02,  9.7189e-02, -2.5902e-02,  6.5997e-02,  1.4074e-01,  1.2469e-01,  1.2465e-01,  8.5594e-02,  1.1103e-01,  7.9735e-02,  1.2031e-01,  2.0730e-01,  1.1256e-01,  9.4117e-02,  5.5346e-03,  1.3461e-01,  1.3142e-01,  1.4929e-02,  1.0143e-01,  1.1878e-01,  1.0000e+00,  9.0969e-02,  1.2806e-01,  1.0749e-01,  2.2746e-01},
          { 6.4504e-02,  7.2020e-02,  1.1233e-01,  1.3824e-01,  3.8202e-02,  5.8976e-02,  9.5301e-02,  1.4062e-01,  1.2602e-01,  1.2314e-01,  1.0163e-01,  1.3797e-01,  5.4840e-02,  7.9179e-02,  5.7752e-02, -4.1204e-03,  9.3026e-02,  1.1437e-01,  1.1756e-01,  1.2256e-01,  9.0355e-02,  1.9538e-02,  1.3936e-01,  1.8418e-01,  1.3406e-01,  2.0029e-01,  1.1904e-01,  1.5057e-01,  8.9278e-02,  6.2893e-02,  1.5006e-01,  7.0117e-02,  3.1213e-02, -7.2764e-03,  9.0543e-02,  6.8555e-02,  5.1666e-02,  1.6014e-01,  1.0870e-01,  9.0969e-02,  1.0000e+00,  1.6325e-01,  9.6476e-02,  2.0494e-01},
          { 1.3902e-02,  1.5167e-01,  1.3569e-01,  1.7151e-01,  9.6499e-02,  1.3074e-01,  1.2104e-01,  1.5535e-01,  5.0945e-02,  4.7397e-02,  1.4238e-01,  1.5322e-01,  9.4811e-02,  9.6762e-02,  5.7079e-02,  3.3597e-02,  2.0509e-01,  1.9674e-01,  1.8265e-01,  1.2458e-01,  1.1260e-01, -2.2801e-02,  1.5020e-01,  2.3247e-01,  1.2653e-01,  1.7617e-01,  2.2754e-01,  2.0307e-01,  1.5291e-01,  1.8103e-01,  1.6000e-01,  4.8318e-02,  7.2392e-02,  4.3055e-02,  7.0879e-02,  2.0611e-01,  1.4814e-01,  1.8088e-01,  1.2472e-01,  1.2806e-01,  1.6325e-01,  1.0000e+00,  1.0417e-01,  1.8513e-01},
          { 9.5006e-02,  9.1464e-02,  6.9131e-02,  1.5356e-01,  5.6981e-02,  5.0216e-02,  1.0649e-01,  9.7554e-02,  8.9028e-02,  3.4093e-02,  7.2226e-02,  4.0611e-02,  1.2204e-01,  1.5340e-01,  1.1345e-01,  5.9546e-02,  1.0368e-01,  1.4786e-01,  1.9091e-01,  8.6965e-02,  1.9106e-01, -6.5519e-04,  3.4232e-02,  7.1326e-02,  7.9526e-02,  8.2208e-02,  1.2673e-01,  1.3121e-01,  1.2220e-01,  1.2219e-01,  1.7149e-01,  4.9123e-02,  8.0171e-02,  4.8122e-02,  3.0563e-02,  1.0046e-01, -6.9593e-04,  9.3910e-02,  8.4628e-02,  1.0749e-01,  9.6476e-02,  1.0417e-01,  1.0000e+00,  2.2440e-01},
          { 6.0029e-02,  1.2216e-01,  1.5137e-01,  2.3640e-01,  1.0302e-01,  4.3983e-02,  1.0901e-01,  2.1475e-01,  1.5833e-01,  1.1124e-01,  1.3796e-01,  9.0265e-02,  1.8202e-01,  2.5984e-01,  1.9202e-01,  6.5120e-02,  2.0794e-01,  2.4037e-01,  2.3035e-01,  1.7494e-01,  2.3800e-01, -9.0815e-04,  1.2801e-01,  2.2015e-01,  1.7116e-01,  1.4534e-01,  1.8402e-01,  2.1939e-01,  1.5605e-01,  2.0015e-01,  2.8887e-01,  7.0170e-02,  1.0715e-01,  4.4980e-02,  1.5109e-01,  1.8898e-01,  5.3976e-02,  1.7642e-01,  1.6845e-01,  2.2746e-01,  2.0494e-01,  1.8513e-01,  2.2440e-01,  1.0000e+00},

        };        

        set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_3Lep_36invfb)


  }
}
