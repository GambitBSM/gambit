///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2018 June, December
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

// Based on arxiv:1709.05406 and arxiv:1801.03957 (which is a rebinning of the 3-lepton analysis in arxiv:1709.05406)

// @todo Add covariance matrix for the rebinned analysis 
// @todo Validation!

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is a base class for three SR-specific analysis classes
    // defined further down:
    // - Analysis_CMS_13TeV_MultiLEP_Full_2SSLep_36invfb
    // - Analysis_CMS_13TeV_MultiLEP_Full_3Lep_36invfb
    // - Analysis_CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb
    class Analysis_CMS_13TeV_MultiLEP_Full_36invfb : public HEPUtilsAnalysis {

    protected:
      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        // 2SSLep SRs
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
        // 3Lep SRs
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
        // 3Lep_rebinned SRs
        {"SR01", 0.},
        {"SR02", 0.},
        {"SR03", 0.},
        {"SR04", 0.},
        {"SR05", 0.},
        {"SR06", 0.},
        {"SR07", 0.},
        {"SR08", 0.},
        {"SR09", 0.},
        {"SR10", 0.},
        {"SR11", 0.},
        {"SR12", 0.},
        {"SR13", 0.},
        {"SR14", 0.},
        {"SR15", 0.},
        {"SR16", 0.},
        {"SR17", 0.},
        {"SR18", 0.},
        {"SR19", 0.},
        {"SR20", 0.},
        {"SR21", 0.},
        {"SR22", 0.},
        {"SR23", 0.},
        {"SR24", 0.},
        {"SR25", 0.},
        {"SR26", 0.},
        {"SR27", 0.},
        {"SR28", 0.},
        {"SR29", 0.},
        {"SR30", 0.},
        {"SR31", 0.},
        {"SR32", 0.},
        {"SR33", 0.},
        {"SR34", 0.},
        {"SR35", 0.},
        {"SR36", 0.},
        {"SR37", 0.},
        {"SR38", 0.},
        {"SR39", 0.},
        {"SR40", 0.},
        {"SR41", 0.},
        {"SR42", 0.},
        {"SR43", 0.},
        {"SR44", 0.},
        {"SR45", 0.},
        {"SR46", 0.},
        {"SR47", 0.},
        {"SR48", 0.},
        {"SR49", 0.},
        {"SR50", 0.},
        {"SR51", 0.},
        {"SR52", 0.},
        {"SR53", 0.},
        {"SR45", 0.},
        {"SR55", 0.},
        {"SR56", 0.},
        {"SR57", 0.},
        {"SR58", 0.},
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
        double HT=0;
        vector<vector<HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
        vector<vector<HEPUtils::Particle*>> OSpair_cont = getOSpairs(signalLeptons);

        // Calculate HT
        for (size_t iJet=0; iJet<signalJets.size(); iJet++){
          double jetpT = signalJets.at(iJet)->pT();
          if (jetpT > 30.) HT += jetpT;           
        }

        // // Calculate mT2
        // if (nSignalLeptons>1)pT_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).pT();
        // if (nSignalLightLeptons>0 && nSignalTaus>0) {
        //   double pLep1[3] = {signalLightLeptons.at(0)->mass(), signalLightLeptons.at(0)->mom().px(), signalLightLeptons.at(0)->mom().py()};
        //   double pTau[3] = {signalTaus.at(0)->mass(), signalTaus.at(0)->mom().px(), signalTaus.at(0)->mom().py()};
        //   double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
        //   double mn = 0.;

        //   mt2_bisect::mt2 mt2_calc;
        //   mt2_calc.set_momenta(pLep1,pTau,pMiss);
        //   mt2_calc.set_mn(mn);
        //   // mT2 = mt2_calc.get_mt2();
        // }

        // Calculate mll and mT
        if (nSignalLeptons==2 || (SFOSpair_cont.size()==0 && OSpair_cont.size()==0)) mT=get_mTmin(signalLeptons, event->missingmom());   
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

        // Low mass veto, conversion veto, preselection
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


        // Increment signal region counters: 2 same-sign leptons
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
        
        // Increment signal region counters: 3 leptons (binning from arxiv:1709.05406)
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

        // Increment signal region counters: 3 leptons (rebinning from arxiv:1801.03957)
        if (preselection && met>50 && conversion_veto && nSignalLeptons>2) {
          
          if (nSignalTaus<2) {
            if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>25) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>20 && nSignalMuons>1) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25 && nSignalMuons==1)) {
              if (nSignalLightLeptons==3 && nSignalTaus==0) {
                
                // The three light lepton signal regions
                if(mll < 75 && mT < 100 && HT < 200 && met > 50 && met < 100) _numSR["SR01"]++;
                if(mll < 75 && mT < 100 && HT < 200 && met > 100 && met < 150) _numSR["SR02"]++;
                if(mll < 75 && mT < 100 && HT < 200 && met > 150 && met < 200) _numSR["SR03"]++;
                if(mll < 75 && mT < 100 && HT < 200 && met > 200) _numSR["SR04"]++;

                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 50 && met < 100) _numSR["SR05"]++;
                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 100 && met < 150) _numSR["SR06"]++;
                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 150) _numSR["SR07"]++;

                if(mll < 75 && mT > 160 && HT < 200 && met > 50 && met < 100) _numSR["SR08"]++;
                if(mll < 75 && mT > 160 && HT < 200 && met > 100 && met < 150) _numSR["SR09"]++;
                if(mll < 75 && mT > 160 && HT < 200 && met > 150 && met < 200) _numSR["SR10"]++;
                if(mll < 75 && mT > 160 && HT < 200 && met > 200) _numSR["SR11"]++;

                if(mll < 75 && mT < 100 && HT > 200 && met > 50) _numSR["SR12"]++;
                if(mll < 75 && mT > 100 && mT < 160 && HT > 200 && met > 50) _numSR["SR13"]++;
                if(mll < 75 && mT > 160 && HT > 200 && met > 50) _numSR["SR14"]++;

                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 100 && met < 150) _numSR["SR15"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 150 && met < 200) _numSR["SR16"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 200 && met < 250) _numSR["SR17"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 250) _numSR["SR18"]++;

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 50 && met < 100) _numSR["SR19"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 100 && met < 150) _numSR["SR20"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 150 && met < 200) _numSR["SR21"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 200) _numSR["SR22"]++;

                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 50 && met < 100) _numSR["SR23"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 100 && met < 150) _numSR["SR24"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 150 && met < 200) _numSR["SR25"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 200) _numSR["SR26"]++;

                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 50 && met < 100) _numSR["SR27"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 100 && met < 150) _numSR["SR28"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 150 && met < 200) _numSR["SR29"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 200 && met < 250) _numSR["SR30"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 250) _numSR["SR31"]++;

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 50 && met < 100) _numSR["SR32"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 100 && met < 150) _numSR["SR33"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 150 && met < 200) _numSR["SR34"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 200) _numSR["SR35"]++;

                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 50 && met < 100) _numSR["SR36"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 100 && met < 150) _numSR["SR37"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 150 && met < 200) _numSR["SR38"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 200) _numSR["SR39"]++;

                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 50 && met < 150) _numSR["SR40"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 150 && met < 250) _numSR["SR41"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 250 && met < 350) _numSR["SR42"]++;
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 350) _numSR["SR43"]++;

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 50 && met < 100) _numSR["SR44"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 100 && met < 150) _numSR["SR45"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 150 && met < 200) _numSR["SR46"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 200 && met < 250) _numSR["SR47"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 250 && met < 300) _numSR["SR48"]++;
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 300) _numSR["SR49"]++;

                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 50 && met < 100) _numSR["SR50"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 100 && met < 150) _numSR["SR51"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 150 && met < 200) _numSR["SR52"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 200 && met < 250) _numSR["SR53"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 250 && met < 300) _numSR["SR54"]++;
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 300) _numSR["SR55"]++;

                if(mll > 105 && mT < 100 && met > 50) _numSR["SR56"]++;
                if(mll > 105 && mT > 100 && mT < 160 && met > 50) _numSR["SR57"]++;
                if(mll > 105 && mT > 160 && met > 50) _numSR["SR58"]++;

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

        add_result(SignalRegionData("SR01", 166., {_numSR["SR01"], 0.}, {175., 20.}));
        add_result(SignalRegionData("SR02", 23., {_numSR["SR02"], 0.}, {27., 4.}));
        add_result(SignalRegionData("SR03", 6., {_numSR["SR03"], 0.}, {5., 1.}));
        add_result(SignalRegionData("SR04", 1., {_numSR["SR04"], 0.}, {2.5, 0.8}));
        add_result(SignalRegionData("SR05", 56., {_numSR["SR05"], 0.}, {50., 8.}));
        add_result(SignalRegionData("SR06", 13., {_numSR["SR06"], 0.}, {12., 3.}));
        add_result(SignalRegionData("SR07", 1., {_numSR["SR07"], 0.}, {1.2, 0.4}));
        add_result(SignalRegionData("SR08", 13., {_numSR["SR08"], 0.}, {12., 2.}));
        add_result(SignalRegionData("SR09", 14., {_numSR["SR09"], 0.}, {11., 3.}));
        add_result(SignalRegionData("SR10", 2., {_numSR["SR10"], 0.}, {2.6, 0.9}));
        add_result(SignalRegionData("SR11", 1., {_numSR["SR11"], 0.}, {1.2, 0.5}));
        add_result(SignalRegionData("SR12", 41., {_numSR["SR12"], 0.}, {39., 6.}));
        add_result(SignalRegionData("SR13", 13., {_numSR["SR13"], 0.}, {10., 3.}));
        add_result(SignalRegionData("SR14", 11., {_numSR["SR14"], 0.}, {6., 2.}));
        add_result(SignalRegionData("SR15", 260., {_numSR["SR15"], 0.}, {286., 44.}));
        add_result(SignalRegionData("SR16", 51., {_numSR["SR16"], 0.}, {62., 14.}));
        add_result(SignalRegionData("SR17", 10., {_numSR["SR17"], 0.}, {20., 5.}));
        add_result(SignalRegionData("SR18", 9., {_numSR["SR18"], 0.}, {16., 4.}));
        add_result(SignalRegionData("SR19", 297., {_numSR["SR19"], 0.}, {321., 42.}));
        add_result(SignalRegionData("SR20", 38., {_numSR["SR20"], 0.}, {50., 14.}));
        add_result(SignalRegionData("SR21", 2., {_numSR["SR21"], 0.}, {5., 2.}));
        add_result(SignalRegionData("SR22", 2., {_numSR["SR22"], 0.}, {1.1, 0.5}));
        add_result(SignalRegionData("SR23", 18., {_numSR["SR23"], 0.}, {25., 6.}));
        add_result(SignalRegionData("SR24", 13., {_numSR["SR24"], 0.}, {12., 5.}));
        add_result(SignalRegionData("SR25", 5., {_numSR["SR25"], 0.}, {5., 2.}));
        add_result(SignalRegionData("SR26", 2., {_numSR["SR26"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR27", 250., {_numSR["SR27"], 0.}, {279., 34.}));
        add_result(SignalRegionData("SR28", 81., {_numSR["SR28"], 0.}, {87., 13.}));
        add_result(SignalRegionData("SR29", 20., {_numSR["SR29"], 0.}, {26., 6.}));
        add_result(SignalRegionData("SR30", 10., {_numSR["SR30"], 0.}, {8., 2.}));
        add_result(SignalRegionData("SR31", 5., {_numSR["SR31"], 0.}, {6., 1.}));
        add_result(SignalRegionData("SR32", 49., {_numSR["SR32"], 0.}, {54., 8.}));
        add_result(SignalRegionData("SR33", 11., {_numSR["SR33"], 0.}, {11., 3.}));
        add_result(SignalRegionData("SR34", 2., {_numSR["SR34"], 0.}, {2.2, 0.9}));
        add_result(SignalRegionData("SR35", 2., {_numSR["SR35"], 0.}, {0.5, 0.4}));
        add_result(SignalRegionData("SR36", 5., {_numSR["SR36"], 0.}, {6., 2.}));
        add_result(SignalRegionData("SR37", 2., {_numSR["SR37"], 0.}, {3.0, 1.3}));
        add_result(SignalRegionData("SR38", 0., {_numSR["SR38"], 0.}, {1.1, 0.4}));
        add_result(SignalRegionData("SR39", 3., {_numSR["SR39"], 0.}, {0.9, 0.4}));
        add_result(SignalRegionData("SR40", 292., {_numSR["SR40"], 0.}, {310., 40.}));
        add_result(SignalRegionData("SR41", 69., {_numSR["SR41"], 0.}, {81., 18.}));
        add_result(SignalRegionData("SR42", 23., {_numSR["SR42"], 0.}, {25., 6.}));
        add_result(SignalRegionData("SR43", 8., {_numSR["SR43"], 0.}, {13., 3.}));
        add_result(SignalRegionData("SR44", 45., {_numSR["SR44"], 0.}, {45., 6.}));
        add_result(SignalRegionData("SR45", 12., {_numSR["SR45"], 0.}, {14., 3.}));
        add_result(SignalRegionData("SR46", 5., {_numSR["SR46"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR47", 1., {_numSR["SR47"], 0.}, {1.9, 0.8}));
        add_result(SignalRegionData("SR48", 2., {_numSR["SR48"], 0.}, {1.8, 0.8}));
        add_result(SignalRegionData("SR49", 1., {_numSR["SR49"], 0.}, {1.0, 0.5}));
        add_result(SignalRegionData("SR50", 12., {_numSR["SR50"], 0.}, {9., 3.}));
        add_result(SignalRegionData("SR51", 2., {_numSR["SR51"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR52", 2., {_numSR["SR52"], 0.}, {2.0, 0.7}));
        add_result(SignalRegionData("SR53", 2., {_numSR["SR53"], 0.}, {1.5, 0.7}));
        add_result(SignalRegionData("SR45", 1., {_numSR["SR45"], 0.}, {0.6, 0.3}));
        add_result(SignalRegionData("SR55", 1., {_numSR["SR55"], 0.}, {1.1, 0.5}));
        add_result(SignalRegionData("SR56", 170., {_numSR["SR56"], 0.}, {173., 21.}));
        add_result(SignalRegionData("SR57", 28., {_numSR["SR57"], 0.}, {44., 7.}));
        add_result(SignalRegionData("SR58", 12., {_numSR["SR58"], 0.}, {23., 6.}));
                        
      }
      

      // Helper function to calculate mll and mT
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

      // Helper function to get min mT 
      double get_mTmin(vector<HEPUtils::Particle*> leptons, HEPUtils::P4 met) { 
        vector<double> mT_container;
        for (size_t iLe=0;iLe<leptons.size();iLe++) {
          mT_container.push_back(sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi()))));
        }         
        sort(mT_container.begin(),mT_container.end());
        if (mT_container.size()>0) return mT_container.at(0);
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
          { 4.8400e+02,  2.6701e+01,  5.4861e+00,  9.6901e-01,  2.1481e+00,  5.0929e+01,  1.8513e+01,  7.5326e-01,  1.0618e+00,  1.0229e+01,  1.1877e+01,  3.8462e+00,  1.4500e+00,  1.4164e+00,  2.7531e+02,  3.3675e+02, -8.5168e+00,  4.0671e+00, -4.2515e+00,  7.1028e-01,  2.0509e+00,  2.6071e+02, -6.6211e+00, -3.7499e+00,  3.0125e+00,  1.7092e+01, -2.7973e+00, -4.7666e+00,  1.6714e+00, -1.4996e+00,  1.1487e+00,  1.3766e+02,  2.2202e+01,  2.8447e+00,  1.7565e+00,  2.6699e+00,  1.1240e+01,  5.2180e+00,  1.2450e+00,  1.1831e+00,  3.4058e+00,  6.4227e-01,  2.0901e+00,  1.0565e+00},
          { 2.6701e+01,  3.6000e+01,  2.4650e+00,  1.2589e+00,  5.4240e-01,  1.5523e+01,  5.6846e+00,  2.9109e-01,  2.0650e-01,  3.4964e-01,  3.8924e+00,  1.1265e+00,  6.0643e-01,  2.6935e-01,  1.6123e+02,  4.8145e+01,  1.3753e+01,  4.9347e+00,  5.2596e+00,  1.1989e+00,  6.1133e-01,  4.1481e+01, -1.0207e+00,  1.6485e+00,  7.8516e-01,  3.3322e+00,  6.5491e+00,  1.2734e+00,  9.5815e-01,  3.5404e-01,  3.8064e-01,  2.2005e+01,  4.8093e+00,  1.5380e+00,  2.0269e-01,  1.0693e+00,  8.3730e+00,  3.3454e+00,  1.3986e-01,  2.6837e-01,  1.0371e+00,  1.9110e+00,  5.4878e-01,  5.8637e-01},
          { 5.4861e+00,  2.4650e+00,  4.8400e+00,  3.1946e-01,  2.2832e-01,  3.7808e+00,  1.7149e+00,  1.0361e-01,  9.3746e-02,  3.5382e-01,  1.2180e+00,  3.1656e-01,  1.8380e-01,  8.6842e-02,  4.0478e+01,  6.3231e+00,  7.4320e+00,  2.4911e+00,  2.2922e+00,  5.6868e-01,  1.2082e-01, -2.9585e+00,  1.6030e+00,  1.2869e+00,  5.3165e-01,  1.6283e+00,  2.4070e+00,  7.9849e-01,  3.5641e-01,  9.9049e-02,  1.9898e-01,  4.0006e+00,  9.6517e-01,  2.8769e-01,  1.0002e-01,  2.3910e-01,  1.5230e+00,  9.8900e-01,  1.0219e-01,  1.1135e-01,  5.9310e-01,  6.2689e-01,  1.5209e-01,  2.6641e-01},
          { 9.6901e-01,  1.2589e+00,  3.1946e-01,  1.0000e+00,  7.6767e-02,  1.0433e+00,  4.0552e-01,  5.5807e-02,  3.2132e-02,  1.3220e-01,  4.0080e-01,  1.3301e-01,  1.2791e-01,  6.1720e-02,  3.0462e+01,  7.6272e+00,  5.9626e+00,  1.7149e+00,  2.3309e+00,  3.9497e-01,  1.5640e-01,  1.9198e+00,  5.5963e-01,  4.8628e-01,  1.7902e-01,  9.8712e-01,  1.5780e+00,  5.5633e-01,  2.0495e-01,  1.9666e-01,  9.3695e-02,  7.1858e-01,  3.6304e-01,  2.7414e-01,  1.0525e-02,  1.7454e-01,  7.1960e-01,  3.8851e-01,  3.9256e-02,  4.6016e-02,  3.3178e-01,  3.6017e-01,  1.5356e-01,  1.8912e-01},
          { 2.1481e+00,  5.4240e-01,  2.2832e-01,  7.6767e-02,  1.0000e+00,  5.6945e-01,  4.5756e-01,  5.7964e-02,  3.4446e-02,  1.0404e-01,  1.8829e-01,  3.1780e-02,  4.5478e-02,  4.5400e-02,  1.1345e+01,  8.2565e+00,  5.2842e+00,  1.8962e+00,  1.3766e+00,  2.3942e-01,  7.4910e-02, -6.8635e-01,  1.9000e+00,  5.8752e-01,  2.1058e-01,  7.9898e-01,  1.2588e+00,  4.4745e-01,  1.2185e-01,  1.8619e-01,  5.2550e-02,  9.4384e-01,  4.8533e-01,  4.6023e-02,  4.2824e-02,  8.3210e-02,  1.0399e-02,  1.0255e-01,  4.5478e-02,  4.6944e-02,  9.1685e-02,  2.0265e-01,  5.6981e-02,  8.2416e-02},
          { 5.0929e+01,  1.5523e+01,  3.7808e+00,  1.0433e+00,  5.6945e-01,  6.4000e+01,  9.8611e+00,  1.1083e-02,  3.2966e-01,  1.8889e+00,  5.9482e+00,  2.2000e+00,  6.7917e-01,  3.6288e-01,  1.4343e+02,  1.0140e+01, -1.2343e+01, -5.6482e+00, -2.1697e+00,  1.8005e-01,  4.9768e-01,  6.7332e+01, -6.1444e+00,  9.0810e-01,  1.3514e+00,  2.8292e+00,  4.7055e+00,  2.8366e-01,  1.2113e+00, -6.5010e-01,  3.4343e-01,  4.1642e+01,  4.6860e+00,  8.4209e-01,  3.7003e-01,  1.5590e+00,  1.2756e+01,  6.4295e+00,  3.6502e-01,  2.5506e-01,  1.1323e+00,  2.1964e+00,  4.0173e-01,  2.8149e-01},
          { 1.8513e+01,  5.6846e+00,  1.7149e+00,  4.0552e-01,  4.5756e-01,  9.8611e+00,  1.6000e+01,  1.3884e-01,  1.7568e-01,  1.3422e+00,  3.1487e+00,  9.9586e-01,  4.7043e-01,  1.7018e-01,  6.7786e+01, -2.1310e+01, -3.4307e+00, -1.1448e+00, -5.8795e-01,  1.6535e-01,  1.7777e-01,  1.9015e+00,  6.8173e+00,  1.8162e+00,  1.0566e+00,  3.7926e+00,  4.2963e+00,  8.3932e-01,  7.1006e-01,  3.8325e-02,  3.9540e-01,  1.4385e+01,  3.0882e+00,  7.9414e-01,  3.9126e-01,  6.7252e-01,  3.1692e+00,  2.7651e+00,  1.5879e-01,  1.6642e-01,  9.1489e-01,  1.0167e+00,  4.2596e-01,  3.4883e-01},
          { 7.5326e-01,  2.9109e-01,  1.0361e-01,  5.5807e-02,  5.7964e-02,  1.1083e-02,  1.3884e-01,  3.6000e-01,  1.2020e-02,  1.6792e-01,  2.0498e-01,  3.1854e-02,  4.6738e-02,  3.1397e-02,  1.2000e+01,  8.7213e-01,  1.8500e+00,  9.0120e-01,  8.1070e-01,  7.8046e-02,  4.3949e-02, -6.3615e-01,  1.9446e+00,  4.6313e-01,  1.6885e-01,  7.3062e-01,  5.4269e-01,  2.9991e-01,  6.5646e-02,  1.5600e-01,  4.4460e-02,  1.8294e-01,  2.2786e-01, -7.6554e-03,  6.7397e-02,  6.1890e-02, -5.0352e-03,  1.4874e-01,  4.7158e-02,  4.0267e-02,  2.0249e-01,  1.9574e-01,  5.8532e-02,  1.0308e-01},
          { 1.0618e+00,  2.0650e-01,  9.3746e-02,  3.2132e-02,  3.4446e-02,  3.2966e-01,  1.7568e-01,  1.2020e-02,  1.6000e-01,  8.0286e-02,  1.9069e-01,  2.5945e-02,  2.7682e-02,  1.7656e-02,  8.4458e+00,  4.5525e-01,  4.8440e-01,  3.8540e-01,  2.7435e-01,  6.9971e-02,  3.0019e-02,  1.1392e-03,  4.9908e-01,  1.0929e-01,  9.7196e-02,  3.2982e-01,  1.5757e-01,  9.7814e-02,  2.7184e-02,  3.6078e-02,  2.0128e-02,  5.5054e-01,  1.3416e-01,  3.8647e-02,  2.2951e-02,  4.8080e-02,  7.4082e-02,  6.6765e-02,  1.3136e-02,  1.8970e-02,  1.2098e-01,  4.2794e-02,  3.5611e-02,  5.0666e-02},
          { 1.0229e+01,  3.4964e-01,  3.5382e-01,  1.3220e-01,  1.0404e-01,  1.8889e+00,  1.3422e+00,  1.6792e-01,  8.0286e-02,  7.8400e+00,  9.4438e-01,  3.8260e-01,  2.3511e-01,  1.3534e-01,  4.7104e+01, -1.1950e+01,  4.7693e+00,  1.2628e+00, -1.1590e-01,  1.6372e-01,  5.8343e-02, -3.0261e+00,  1.0143e+01,  1.4815e+00,  6.9075e-01,  4.8399e+00,  3.7388e+00,  8.7251e-01,  2.6459e-01,  4.2605e-01,  1.2583e-01,  4.3390e+00,  8.4857e-01,  3.0650e-01,  1.7859e-01,  3.0453e-01, -2.0476e-01,  6.2314e-01,  2.2552e-01,  9.6665e-02,  8.2750e-01,  2.7869e-01,  9.5460e-02,  2.4918e-01},
          { 1.1877e+01,  3.8924e+00,  1.2180e+00,  4.0080e-01,  1.8829e-01,  5.9482e+00,  3.1487e+00,  2.0498e-01,  1.9069e-01,  9.4438e-01,  1.0240e+01,  5.0884e-01,  4.2314e-01,  1.3740e-01,  5.8960e+01, -1.6603e+01,  2.3288e+00,  4.6826e-01,  9.6828e-01,  4.1645e-01,  2.2781e-01, -8.5710e+00,  3.2814e+00,  1.1783e+00,  5.2895e-01,  2.4315e+00,  2.8908e+00,  1.1384e+00,  5.6131e-01,  2.2034e-01,  2.2024e-01,  8.1290e+00,  2.0070e+00,  5.1339e-01,  1.6424e-01,  4.6285e-01,  1.6312e+00,  1.5606e+00,  1.7341e-01,  8.6075e-02,  7.8052e-01,  9.5679e-01,  2.3112e-01,  3.5318e-01},
          { 3.8462e+00,  1.1265e+00,  3.1656e-01,  1.3301e-01,  3.1780e-02,  2.2000e+00,  9.9586e-01,  3.1854e-02,  2.5945e-02,  3.8260e-01,  5.0884e-01,  1.4400e+00,  4.8991e-02,  4.7630e-02,  1.4196e+01, -8.6629e-01,  1.0279e+00,  3.2101e-01,  8.2097e-02,  1.1526e-01,  7.9773e-02,  5.7706e+00,  2.8208e+00,  8.6602e-01,  2.2107e-01,  1.6398e+00,  8.8900e-01,  1.2956e-01,  1.8999e-01, -6.8243e-02,  5.9174e-02,  2.7498e+00,  4.0277e-01, -1.1485e-03,  7.9137e-02,  1.8644e-01,  1.2699e+00,  6.6298e-01,  3.4984e-02,  4.1921e-02,  3.9735e-01,  3.8611e-01,  4.8733e-02,  8.6654e-02},
          { 1.4500e+00,  6.0643e-01,  1.8380e-01,  1.2791e-01,  4.5478e-02,  6.7917e-01,  4.7043e-01,  4.6738e-02,  2.7682e-02,  2.3511e-01,  4.2314e-01,  4.8991e-02,  6.4000e-01,  3.8781e-02,  2.7523e+01,  5.9080e-01,  2.9427e+00,  1.0946e+00,  1.3521e+00,  1.5576e-01,  9.6410e-02, -1.9481e+00,  8.1416e-01,  2.4981e-01,  7.0318e-02,  7.1410e-01,  1.0406e+00,  3.8318e-01,  1.1485e-01,  1.9355e-01,  6.3640e-02,  6.6732e-01,  5.1636e-01,  1.6455e-01,  2.9405e-02,  1.1824e-01,  7.7100e-02,  1.6023e-01,  2.6414e-02,  3.5130e-02,  1.0529e-01,  1.5928e-01,  9.7632e-02,  1.1649e-01},
          { 1.4164e+00,  2.6935e-01,  8.6842e-02,  6.1720e-02,  4.5400e-02,  3.6288e-01,  1.7018e-01,  3.1397e-02,  1.7656e-02,  1.3534e-01,  1.3740e-01,  4.7630e-02,  3.8781e-02,  1.6000e-01,  1.6501e+01,  2.2254e+00,  1.4383e+00,  5.1984e-01,  4.1969e-01,  4.0035e-02,  6.7654e-02,  1.4673e+00,  9.1854e-01,  3.0346e-01,  6.7917e-02,  3.8815e-01,  3.7392e-01,  1.2677e-01,  4.3292e-02,  9.5821e-02,  5.5184e-02,  6.5750e-01,  2.1968e-01,  6.5015e-03,  2.9439e-02,  4.9744e-02,  1.2376e-01,  1.0305e-01,  2.6260e-02,  2.3274e-02,  7.6012e-02,  8.1280e-02,  6.1360e-02,  8.3149e-02},
          { 2.7531e+02,  1.6123e+02,  4.0478e+01,  3.0462e+01,  1.1345e+01,  1.4343e+02,  6.7786e+01,  1.2000e+01,  8.4458e+00,  4.7104e+01,  5.8960e+01,  1.4196e+01,  2.7523e+01,  1.6501e+01,  6.7600e+04, -8.8863e+02,  4.1808e+02,  1.9834e+02,  1.9249e+02,  3.4181e+01,  3.0214e+01, -7.7718e+02,  2.1278e+02,  7.2415e+01,  3.7480e+01,  4.0234e+01,  2.1630e+02,  9.7308e+01,  2.9628e+01,  3.3349e+01,  2.4212e+01,  1.0465e+01,  5.5983e+01,  4.0016e+01,  9.7537e+00,  2.5111e+01, -4.0322e+01,  4.1240e+01,  1.3960e+01,  1.1455e+01,  3.6037e+01,  3.1165e+01,  2.9497e+01,  3.9940e+01},
          { 3.3675e+02,  4.8145e+01,  6.3231e+00,  7.6272e+00,  8.2565e+00,  1.0140e+01, -2.1310e+01,  8.7213e-01,  4.5525e-01, -1.1950e+01, -1.6603e+01, -8.6629e-01,  5.9080e-01,  2.2254e+00, -8.8863e+02,  4.9000e+03,  1.0827e+03,  2.9681e+02,  2.0691e+02,  2.7859e+01,  8.4370e+00,  1.8458e+03,  9.4238e+01,  1.4466e+01, -4.4821e+00,  3.8754e+01,  3.5633e+01,  1.7274e+01,  2.3031e+00,  1.3597e+01,  2.7518e+00,  2.3329e+02,  6.6269e+01,  5.6970e+00,  1.4390e+00,  4.2256e+00,  2.9615e+01, -6.6318e+00,  2.5231e-01,  5.7814e-01, -6.9223e-01,  4.9388e+00,  4.1682e+00,  3.6467e+00},
          {-8.5168e+00,  1.3753e+01,  7.4320e+00,  5.9626e+00,  5.2842e+00, -1.2343e+01, -3.4307e+00,  1.8500e+00,  4.8440e-01,  4.7693e+00,  2.3288e+00,  1.0279e+00,  2.9427e+00,  1.4383e+00,  4.1808e+02,  1.0827e+03,  7.8400e+02,  1.6767e+02,  1.1881e+02,  1.5341e+01,  4.4782e+00,  1.1913e+02,  1.5614e+02,  3.5409e+01,  6.2781e+00,  5.5987e+01,  8.9047e+01,  2.9137e+01,  4.9493e+00,  1.4577e+01,  2.2047e+00,  1.9018e+00,  1.6827e+01,  5.3241e+00,  5.9709e-01,  2.8678e+00, -2.5768e+00,  9.8549e-01,  8.2048e-01,  9.7990e-01,  6.2513e+00,  1.2059e+01,  2.9030e+00,  4.6579e+00},
          { 4.0671e+00,  4.9347e+00,  2.4911e+00,  1.7149e+00,  1.8962e+00, -5.6482e+00, -1.1448e+00,  9.0120e-01,  3.8540e-01,  1.2628e+00,  4.6826e-01,  3.2101e-01,  1.0946e+00,  5.1984e-01,  1.9834e+02,  2.9681e+02,  1.6767e+02,  1.0000e+02,  4.1610e+01,  5.4279e+00,  1.5171e+00,  1.6931e+01,  4.2583e+01,  1.0411e+01,  2.6925e+00,  1.6902e+01,  2.4835e+01,  9.0985e+00,  1.5913e+00,  4.7024e+00,  8.9130e-01,  3.1581e-01,  5.8065e+00,  2.0641e+00,  6.1949e-01,  1.2085e+00, -4.8006e-01, -1.6491e-01,  5.9664e-01,  4.9684e-01,  2.7449e+00,  4.1315e+00,  1.4786e+00,  1.9230e+00},
          {-4.2515e+00,  5.2596e+00,  2.2922e+00,  2.3309e+00,  1.3766e+00, -2.1697e+00, -5.8795e-01,  8.1070e-01,  2.7435e-01, -1.1590e-01,  9.6828e-01,  8.2097e-02,  1.3521e+00,  4.1969e-01,  1.9249e+02,  2.0691e+02,  1.1881e+02,  4.1610e+01,  8.1000e+01,  5.2398e+00,  1.5467e+00,  2.2042e+01,  2.3114e+01,  6.2298e+00,  1.9713e+00,  1.3713e+01,  2.1514e+01,  8.1476e+00,  2.0771e+00,  3.8588e+00,  6.0678e-01, -2.0756e+00,  6.5633e+00,  3.3925e+00,  3.5281e-02,  1.2696e+00,  1.3495e-01,  6.3774e-01,  4.0671e-01,  2.8039e-01,  2.5393e+00,  3.4521e+00,  1.7182e+00,  1.6585e+00},
          { 7.1028e-01,  1.1989e+00,  5.6868e-01,  3.9497e-01,  2.3942e-01,  1.8005e-01,  1.6535e-01,  7.8046e-02,  6.9971e-02,  1.6372e-01,  4.1645e-01,  1.1526e-01,  1.5576e-01,  4.0035e-02,  3.4181e+01,  2.7859e+01,  1.5341e+01,  5.4279e+00,  5.2398e+00,  4.4100e+00,  1.9651e-01,  4.5005e-01,  1.0416e+00,  8.7058e-01,  2.8518e-01,  1.5048e+00,  2.5434e+00,  7.9852e-01,  2.1976e-01,  4.6963e-01,  1.2761e-01,  1.0070e-01,  8.0878e-01,  2.3760e-01,  1.1802e-01,  1.6937e-01,  7.8459e-01,  3.9218e-01,  1.1501e-01,  6.2402e-02,  6.1770e-01,  5.4940e-01,  1.8263e-01,  2.9390e-01},
          { 2.0509e+00,  6.1133e-01,  1.2082e-01,  1.5640e-01,  7.4910e-02,  4.9768e-01,  1.7777e-01,  4.3949e-02,  3.0019e-02,  5.8343e-02,  2.2781e-01,  7.9773e-02,  9.6410e-02,  6.7654e-02,  3.0214e+01,  8.4370e+00,  4.4782e+00,  1.5171e+00,  1.5467e+00,  1.9651e-01,  6.4000e-01,  4.8556e+00,  5.3119e-01,  2.7441e-01,  1.4124e-01,  4.8558e-01,  5.6138e-01,  2.8009e-01,  1.2424e-01,  9.0728e-02,  9.7568e-02,  1.5378e+00,  5.3660e-01,  1.2181e-01,  5.5023e-02,  1.1277e-01,  2.5650e-01,  1.5688e-01,  3.2068e-02,  3.1100e-02,  1.7348e-01,  1.8917e-01,  1.5285e-01,  1.5232e-01},
          { 2.6071e+02,  4.1481e+01, -2.9585e+00,  1.9198e+00, -6.8635e-01,  6.7332e+01,  1.9015e+00, -6.3615e-01,  1.1392e-03, -3.0261e+00, -8.5710e+00,  5.7706e+00, -1.9481e+00,  1.4673e+00, -7.7718e+02,  1.8458e+03,  1.1913e+02,  1.6931e+01,  2.2042e+01,  4.5005e-01,  4.8556e+00,  2.5000e+03,  1.4772e+02,  2.5012e+00, -1.7991e+00,  2.2354e+01, -4.7248e+01, -1.4209e+01,  1.6992e+00, -6.1162e+00,  2.0235e-01,  2.2574e+02,  3.6895e+01,  1.8955e+00,  2.0090e+00,  1.8541e+00,  5.9545e+01,  1.0413e+01, -2.0296e+00, -5.1804e-01,  2.3446e+00, -2.3941e+00, -3.2760e-02, -3.6326e-02},
          {-6.6211e+00, -1.0207e+00,  1.6030e+00,  5.5963e-01,  1.9000e+00, -6.1444e+00,  6.8173e+00,  1.9446e+00,  4.9908e-01,  1.0143e+01,  3.2814e+00,  2.8208e+00,  8.1416e-01,  9.1854e-01,  2.1278e+02,  9.4238e+01,  1.5614e+02,  4.2583e+01,  2.3114e+01,  1.0416e+00,  5.3119e-01,  1.4772e+02,  3.6100e+02,  3.8370e+01,  9.9946e+00,  6.0231e+01,  4.1057e+01,  1.6746e+01,  1.9619e+00,  7.0267e+00,  9.0719e-01, -3.5439e+00,  7.7492e+00, -2.3276e+00,  2.8267e+00,  4.5874e-01, -3.4017e+00,  4.0688e+00,  2.7210e-01,  5.0158e-01,  6.3548e+00,  5.9930e+00,  6.5041e-01,  1.9458e+00},
          {-3.7499e+00,  1.6485e+00,  1.2869e+00,  4.8628e-01,  5.8752e-01,  9.0810e-01,  1.8162e+00,  4.6313e-01,  1.0929e-01,  1.4815e+00,  1.1783e+00,  8.6602e-01,  2.4981e-01,  3.0346e-01,  7.2415e+01,  1.4466e+01,  3.5409e+01,  1.0411e+01,  6.2298e+00,  8.7058e-01,  2.7441e-01,  2.5012e+00,  3.8370e+01,  1.6000e+01,  1.7712e+00,  1.0931e+01,  9.6368e+00,  3.7317e+00,  5.8594e-01,  1.3844e+00,  4.1644e-01, -8.0819e-01,  6.4688e-01, -5.3162e-01,  6.2909e-01,  6.0632e-01,  1.1505e+00,  1.7252e+00,  2.1375e-01,  2.2518e-01,  1.7681e+00,  1.9527e+00,  2.8530e-01,  7.0448e-01},
          { 3.0125e+00,  7.8516e-01,  5.3165e-01,  1.7902e-01,  2.1058e-01,  1.3514e+00,  1.0566e+00,  1.6885e-01,  9.7196e-02,  6.9075e-01,  5.2895e-01,  2.2107e-01,  7.0318e-02,  6.7917e-02,  3.7480e+01, -4.4821e+00,  6.2781e+00,  2.6925e+00,  1.9713e+00,  2.8518e-01,  1.4124e-01, -1.7991e+00,  9.9946e+00,  1.7712e+00,  3.6100e+00,  2.4592e+00,  2.0944e+00,  9.5872e-01,  3.2271e-01,  3.2513e-01,  1.4753e-01,  1.9861e+00,  7.6706e-01,  6.3632e-02,  2.3008e-01,  2.3661e-01,  3.2383e-01,  5.6001e-01,  1.2048e-01,  9.4764e-02,  6.1131e-01,  5.0485e-01,  1.5110e-01,  2.6016e-01},
          { 1.7092e+01,  3.3322e+00,  1.6283e+00,  9.8712e-01,  7.9898e-01,  2.8292e+00,  3.7926e+00,  7.3062e-01,  3.2982e-01,  4.8399e+00,  2.4315e+00,  1.6398e+00,  7.1410e-01,  3.8815e-01,  4.0234e+01,  3.8754e+01,  5.5987e+01,  1.6902e+01,  1.3713e+01,  1.5048e+00,  4.8558e-01,  2.2354e+01,  6.0231e+01,  1.0931e+01,  2.4592e+00,  8.1000e+01,  1.8780e+01,  6.9856e+00,  1.4792e+00,  2.5201e+00,  5.3114e-01,  9.1238e+00,  1.5116e+00, -8.4289e-02,  6.6097e-01,  7.6373e-01,  2.2239e+00,  2.5471e+00,  4.9477e-01,  4.4874e-01,  4.3263e+00,  3.3296e+00,  7.3987e-01,  1.0464e+00},
          {-2.7973e+00,  6.5491e+00,  2.4070e+00,  1.5780e+00,  1.2588e+00,  4.7055e+00,  4.2963e+00,  5.4269e-01,  1.5757e-01,  3.7388e+00,  2.8908e+00,  8.8900e-01,  1.0406e+00,  3.7392e-01,  2.1630e+02,  3.5633e+01,  8.9047e+01,  2.4835e+01,  2.1514e+01,  2.5434e+00,  5.6138e-01, -4.7248e+01,  4.1057e+01,  9.6368e+00,  2.0944e+00,  1.8780e+01,  6.4000e+01,  1.0271e+01,  2.4042e+00,  3.4157e+00,  5.3484e-01,  1.5706e-01,  2.2309e+00,  2.8013e+00,  1.0735e-01,  1.0780e+00,  2.1402e+00,  3.3844e+00,  2.4381e-01,  2.7390e-01,  2.2856e+00,  3.8227e+00,  1.0138e+00,  1.1777e+00},
          {-4.7666e+00,  1.2734e+00,  7.9849e-01,  5.5633e-01,  4.4745e-01,  2.8366e-01,  8.3932e-01,  2.9991e-01,  9.7814e-02,  8.7251e-01,  1.1384e+00,  1.2956e-01,  3.8318e-01,  1.2677e-01,  9.7308e+01,  1.7274e+01,  2.9137e+01,  9.0985e+00,  8.1476e+00,  7.9852e-01,  2.8009e-01, -1.4209e+01,  1.6746e+01,  3.7317e+00,  9.5872e-01,  6.9856e+00,  1.0271e+01,  9.6100e+00,  8.0568e-01,  1.4519e+00,  2.4676e-01, -6.2743e-01,  1.0760e+00,  8.2945e-01,  9.4290e-02,  4.0362e-01,  7.7229e-01,  8.9079e-01,  1.3371e-01,  1.3768e-01,  1.1202e+00,  1.3220e+00,  4.0675e-01,  5.4409e-01},
          { 1.6714e+00,  9.5815e-01,  3.5641e-01,  2.0495e-01,  1.2185e-01,  1.2113e+00,  7.1006e-01,  6.5646e-02,  2.7184e-02,  2.6459e-01,  5.6131e-01,  1.8999e-01,  1.1485e-01,  4.3292e-02,  2.9628e+01,  2.3031e+00,  4.9493e+00,  1.5913e+00,  2.0771e+00,  2.1976e-01,  1.2424e-01,  1.6992e+00,  1.9619e+00,  5.8594e-01,  3.2271e-01,  1.4792e+00,  2.4042e+00,  8.0568e-01,  1.6900e+00,  2.9438e-01,  1.0022e-01,  1.4553e+00,  4.0649e-01,  3.3912e-01,  4.2927e-02,  2.1204e-01,  7.5751e-01,  5.5452e-01,  5.8255e-03,  4.1462e-02,  2.7855e-01,  4.1744e-01,  1.5886e-01,  1.6229e-01},
          {-1.4996e+00,  3.5404e-01,  9.9049e-02,  1.9666e-01,  1.8619e-01, -6.5010e-01,  3.8325e-02,  1.5600e-01,  3.6078e-02,  4.2605e-01,  2.2034e-01, -6.8243e-02,  1.9355e-01,  9.5821e-02,  3.3349e+01,  1.3597e+01,  1.4577e+01,  4.7024e+00,  3.8588e+00,  4.6963e-01,  9.0728e-02, -6.1162e+00,  7.0267e+00,  1.3844e+00,  3.2513e-01,  2.5201e+00,  3.4157e+00,  1.4519e+00,  2.9438e-01,  2.5600e+00,  1.0750e-01, -1.2053e+00,  3.1343e-01,  3.6897e-01,  1.1258e-01,  1.6682e-01, -4.5617e-01,  1.6730e-01,  8.7648e-02,  7.6998e-02,  2.4151e-01,  6.0826e-01,  1.9550e-01,  2.5619e-01},
          { 1.1487e+00,  3.8064e-01,  1.9898e-01,  9.3695e-02,  5.2550e-02,  3.4343e-01,  3.9540e-01,  4.4460e-02,  2.0128e-02,  1.2583e-01,  2.2024e-01,  5.9174e-02,  6.3640e-02,  5.5184e-02,  2.4212e+01,  2.7518e+00,  2.2047e+00,  8.9130e-01,  6.0678e-01,  1.2761e-01,  9.7568e-02,  2.0235e-01,  9.0719e-01,  4.1644e-01,  1.4753e-01,  5.3114e-01,  5.3484e-01,  2.4676e-01,  1.0022e-01,  1.0750e-01,  2.5000e-01,  9.9015e-01,  2.5707e-01,  7.1657e-02,  5.2164e-02,  9.4440e-02,  1.0359e-01,  1.4311e-01,  3.9242e-02,  4.1460e-02,  1.8007e-01,  1.6800e-01,  8.5745e-02,  1.1555e-01},
          { 1.3766e+02,  2.2005e+01,  4.0006e+00,  7.1858e-01,  9.4384e-01,  4.1642e+01,  1.4385e+01,  1.8294e-01,  5.5054e-01,  4.3390e+00,  8.1290e+00,  2.7498e+00,  6.6732e-01,  6.5750e-01,  1.0465e+01,  2.3329e+02,  1.9018e+00,  3.1581e-01, -2.0756e+00,  1.0070e-01,  1.5378e+00,  2.2574e+02, -3.5439e+00, -8.0819e-01,  1.9861e+00,  9.1238e+00,  1.5706e-01, -6.2743e-01,  1.4553e+00, -1.2053e+00,  9.9015e-01,  1.9600e+02,  1.3670e+01,  8.6566e-01,  1.0878e+00,  2.3706e+00,  1.3845e+01,  7.2287e+00,  5.0124e-01,  6.3034e-01,  2.3559e+00,  1.4205e+00,  6.8772e-01,  7.8590e-01},
          { 2.2202e+01,  4.8093e+00,  9.6517e-01,  3.6304e-01,  4.8533e-01,  4.6860e+00,  3.0882e+00,  2.2786e-01,  1.3416e-01,  8.4857e-01,  2.0070e+00,  4.0277e-01,  5.1636e-01,  2.1968e-01,  5.5983e+01,  6.6269e+01,  1.6827e+01,  5.8065e+00,  6.5633e+00,  8.0878e-01,  5.3660e-01,  3.6895e+01,  7.7492e+00,  6.4688e-01,  7.6706e-01,  1.5116e+00,  2.2309e+00,  1.0760e+00,  4.0649e-01,  3.1343e-01,  2.5707e-01,  1.3670e+01,  2.5000e+01,  5.5237e-01,  4.6176e-01,  5.9445e-01,  1.9823e+00,  1.3156e+00,  2.3877e-01,  1.8823e-01,  3.7456e-01,  7.6012e-01,  4.0086e-01,  4.2860e-01},
          { 2.8447e+00,  1.5380e+00,  2.8769e-01,  2.7414e-01,  4.6023e-02,  8.4209e-01,  7.9414e-01, -7.6554e-03,  3.8647e-02,  3.0650e-01,  5.1339e-01, -1.1485e-03,  1.6455e-01,  6.5015e-03,  4.0016e+01,  5.6970e+00,  5.3241e+00,  2.0641e+00,  3.3925e+00,  2.3760e-01,  1.2181e-01,  1.8955e+00, -2.3276e+00, -5.3162e-01,  6.3632e-02, -8.4289e-02,  2.8013e+00,  8.2945e-01,  3.3912e-01,  3.6897e-01,  7.1657e-02,  8.6566e-01,  5.5237e-01,  6.7600e+00, -5.5723e-02,  1.5700e-01,  2.2724e-01,  2.7943e-01,  2.1267e-02,  5.7560e-03, -4.5405e-02,  2.3508e-01,  1.2512e-01,  9.3558e-02},
          { 1.7565e+00,  2.0269e-01,  1.0002e-01,  1.0525e-02,  4.2824e-02,  3.7003e-01,  3.9126e-01,  6.7397e-02,  2.2951e-02,  1.7859e-01,  1.6424e-01,  7.9137e-02,  2.9405e-02,  2.9439e-02,  9.7537e+00,  1.4390e+00,  5.9709e-01,  6.1949e-01,  3.5281e-02,  1.1802e-01,  5.5023e-02,  2.0090e+00,  2.8267e+00,  6.2909e-01,  2.3008e-01,  6.6097e-01,  1.0735e-01,  9.4290e-02,  4.2927e-02,  1.1258e-01,  5.2164e-02,  1.0878e+00,  4.6176e-01, -5.5723e-02,  6.4000e-01,  9.3680e-02, -4.0104e-02,  1.5423e-01,  8.1099e-02,  4.3075e-02,  1.7384e-01,  1.1908e-01,  2.4450e-02,  9.6698e-02},
          { 2.6699e+00,  1.0693e+00,  2.3910e-01,  1.7454e-01,  8.3210e-02,  1.5590e+00,  6.7252e-01,  6.1890e-02,  4.8080e-02,  3.0453e-01,  4.6285e-01,  1.8644e-01,  1.1824e-01,  4.9744e-02,  2.5111e+01,  4.2256e+00,  2.8678e+00,  1.2085e+00,  1.2696e+00,  1.6937e-01,  1.1277e-01,  1.8541e+00,  4.5874e-01,  6.0632e-01,  2.3661e-01,  7.6373e-01,  1.0780e+00,  4.0362e-01,  2.1204e-01,  1.6682e-01,  9.4440e-02,  2.3706e+00,  5.9445e-01,  1.5700e-01,  9.3680e-02,  1.0000e+00,  8.9410e-01,  5.0398e-01,  6.8053e-02,  5.2568e-02,  1.6453e-01,  4.3283e-01,  1.0046e-01,  1.5118e-01},
          { 1.1240e+01,  8.3730e+00,  1.5230e+00,  7.1960e-01,  1.0399e-02,  1.2756e+01,  3.1692e+00, -5.0352e-03,  7.4082e-02, -2.0476e-01,  1.6312e+00,  1.2699e+00,  7.7100e-02,  1.2376e-01, -4.0322e+01,  2.9615e+01, -2.5768e+00, -4.8006e-01,  1.3495e-01,  7.8459e-01,  2.5650e-01,  5.9545e+01, -3.4017e+00,  1.1505e+00,  3.2383e-01,  2.2239e+00,  2.1402e+00,  7.7229e-01,  7.5751e-01, -4.5617e-01,  1.0359e-01,  1.3845e+01,  1.9823e+00,  2.2724e-01, -4.0104e-02,  8.9410e-01,  2.5000e+01,  3.3571e+00,  1.5453e-02,  2.9858e-02,  6.1999e-01,  1.5555e+00, -3.4796e-03,  2.1590e-01},
          { 5.2180e+00,  3.3454e+00,  9.8900e-01,  3.8851e-01,  1.0255e-01,  6.4295e+00,  2.7651e+00,  1.4874e-01,  6.6765e-02,  6.2314e-01,  1.5606e+00,  6.6298e-01,  1.6023e-01,  1.0305e-01,  4.1240e+01, -6.6318e+00,  9.8549e-01, -1.6491e-01,  6.3774e-01,  3.9218e-01,  1.5688e-01,  1.0413e+01,  4.0688e+00,  1.7252e+00,  5.6001e-01,  2.5471e+00,  3.3844e+00,  8.9079e-01,  5.5452e-01,  1.6730e-01,  1.4311e-01,  7.2287e+00,  1.3156e+00,  2.7943e-01,  1.5423e-01,  5.0398e-01,  3.3571e+00,  5.7600e+00,  3.8297e-02,  9.7373e-02,  9.2241e-01,  9.1164e-01,  2.2538e-01,  3.3873e-01},
          { 1.2450e+00,  1.3986e-01,  1.0219e-01,  3.9256e-02,  4.5478e-02,  3.6502e-01,  1.5879e-01,  4.7158e-02,  1.3136e-02,  2.2552e-01,  1.7341e-01,  3.4984e-02,  2.6414e-02,  2.6260e-02,  1.3960e+01,  2.5231e-01,  8.2048e-01,  5.9664e-01,  4.0671e-01,  1.1501e-01,  3.2068e-02, -2.0296e+00,  2.7210e-01,  2.1375e-01,  1.2048e-01,  4.9477e-01,  2.4381e-01,  1.3371e-01,  5.8255e-03,  8.7648e-02,  3.9242e-02,  5.0124e-01,  2.3877e-01,  2.1267e-02,  8.1099e-02,  6.8053e-02,  1.5453e-02,  3.8297e-02,  4.9000e-01,  3.3258e-02,  1.8262e-01,  1.8334e-01,  5.9240e-02,  9.4332e-02},
          { 1.1831e+00,  2.6837e-01,  1.1135e-01,  4.6016e-02,  4.6944e-02,  2.5506e-01,  1.6642e-01,  4.0267e-02,  1.8970e-02,  9.6665e-02,  8.6075e-02,  4.1921e-02,  3.5130e-02,  2.3274e-02,  1.1455e+01,  5.7814e-01,  9.7990e-01,  4.9684e-01,  2.8039e-01,  6.2402e-02,  3.1100e-02, -5.1804e-01,  5.0158e-01,  2.2518e-01,  9.4764e-02,  4.4874e-01,  2.7390e-01,  1.3768e-01,  4.1462e-02,  7.6998e-02,  4.1460e-02,  6.3034e-01,  1.8823e-01,  5.7560e-03,  4.3075e-02,  5.2568e-02,  2.9858e-02,  9.7373e-02,  3.3258e-02,  1.6000e-01,  8.7330e-02,  1.0757e-01,  4.2996e-02,  7.2787e-02},
          { 3.4058e+00,  1.0371e+00,  5.9310e-01,  3.3178e-01,  9.1685e-02,  1.1323e+00,  9.1489e-01,  2.0249e-01,  1.2098e-01,  8.2750e-01,  7.8052e-01,  3.9735e-01,  1.0529e-01,  7.6012e-02,  3.6037e+01, -6.9223e-01,  6.2513e+00,  2.7449e+00,  2.5393e+00,  6.1770e-01,  1.7348e-01,  2.3446e+00,  6.3548e+00,  1.7681e+00,  6.1131e-01,  4.3263e+00,  2.2856e+00,  1.1202e+00,  2.7855e-01,  2.4151e-01,  1.8007e-01,  2.3559e+00,  3.7456e-01, -4.5405e-02,  1.7384e-01,  1.6453e-01,  6.1999e-01,  9.2241e-01,  1.8262e-01,  8.7330e-02,  5.7600e+00,  8.2278e-01,  2.3154e-01,  3.9348e-01},
          { 6.4227e-01,  1.9110e+00,  6.2689e-01,  3.6017e-01,  2.0265e-01,  2.1964e+00,  1.0167e+00,  1.9574e-01,  4.2794e-02,  2.7869e-01,  9.5679e-01,  3.8611e-01,  1.5928e-01,  8.1280e-02,  3.1165e+01,  4.9388e+00,  1.2059e+01,  4.1315e+00,  3.4521e+00,  5.4940e-01,  1.8917e-01, -2.3941e+00,  5.9930e+00,  1.9527e+00,  5.0485e-01,  3.3296e+00,  3.8227e+00,  1.3220e+00,  4.1744e-01,  6.0826e-01,  1.6800e-01,  1.4205e+00,  7.6012e-01,  2.3508e-01,  1.1908e-01,  4.3283e-01,  1.5555e+00,  9.1164e-01,  1.8334e-01,  1.0757e-01,  8.2278e-01,  4.4100e+00,  2.1876e-01,  3.1102e-01},
          { 2.0901e+00,  5.4878e-01,  1.5209e-01,  1.5356e-01,  5.6981e-02,  4.0173e-01,  4.2596e-01,  5.8532e-02,  3.5611e-02,  9.5460e-02,  2.3112e-01,  4.8733e-02,  9.7632e-02,  6.1360e-02,  2.9497e+01,  4.1682e+00,  2.9030e+00,  1.4786e+00,  1.7182e+00,  1.8263e-01,  1.5285e-01, -3.2760e-02,  6.5041e-01,  2.8530e-01,  1.5110e-01,  7.3987e-01,  1.0138e+00,  4.0675e-01,  1.5886e-01,  1.9550e-01,  8.5745e-02,  6.8772e-01,  4.0086e-01,  1.2512e-01,  2.4450e-02,  1.0046e-01, -3.4796e-03,  2.2538e-01,  5.9240e-02,  4.2996e-02,  2.3154e-01,  2.1876e-01,  1.0000e+00,  1.7952e-01},
          { 1.0565e+00,  5.8637e-01,  2.6641e-01,  1.8912e-01,  8.2416e-02,  2.8149e-01,  3.4883e-01,  1.0308e-01,  5.0666e-02,  2.4918e-01,  3.5318e-01,  8.6654e-02,  1.1649e-01,  8.3149e-02,  3.9940e+01,  3.6467e+00,  4.6579e+00,  1.9230e+00,  1.6585e+00,  2.9390e-01,  1.5232e-01, -3.6326e-02,  1.9458e+00,  7.0448e-01,  2.6016e-01,  1.0464e+00,  1.1777e+00,  5.4409e-01,  1.6229e-01,  2.5619e-01,  1.1555e-01,  7.8590e-01,  4.2860e-01,  9.3558e-02,  9.6698e-02,  1.5118e-01,  2.1590e-01,  3.3873e-01,  9.4332e-02,  7.2787e-02,  3.9348e-01,  3.1102e-01,  1.7952e-01,  6.4000e-01},
        };        

        set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_3Lep_36invfb)



    // 
    // Derived analysis class for the 3Lep SRs (rebinned version)
    // 
    class Analysis_CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb : public Analysis_CMS_13TeV_MultiLEP_Full_36invfb {

    public:
      Analysis_CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb() {
        set_analysis_name("CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR01", 166., {_numSR["SR01"], 0.}, {175., 20.}));
        add_result(SignalRegionData("SR02", 23., {_numSR["SR02"], 0.}, {27., 4.}));
        add_result(SignalRegionData("SR03", 6., {_numSR["SR03"], 0.}, {5., 1.}));
        add_result(SignalRegionData("SR04", 1., {_numSR["SR04"], 0.}, {2.5, 0.8}));
        add_result(SignalRegionData("SR05", 56., {_numSR["SR05"], 0.}, {50., 8.}));
        add_result(SignalRegionData("SR06", 13., {_numSR["SR06"], 0.}, {12., 3.}));
        add_result(SignalRegionData("SR07", 1., {_numSR["SR07"], 0.}, {1.2, 0.4}));
        add_result(SignalRegionData("SR08", 13., {_numSR["SR08"], 0.}, {12., 2.}));
        add_result(SignalRegionData("SR09", 14., {_numSR["SR09"], 0.}, {11., 3.}));
        add_result(SignalRegionData("SR10", 2., {_numSR["SR10"], 0.}, {2.6, 0.9}));
        add_result(SignalRegionData("SR11", 1., {_numSR["SR11"], 0.}, {1.2, 0.5}));
        add_result(SignalRegionData("SR12", 41., {_numSR["SR12"], 0.}, {39., 6.}));
        add_result(SignalRegionData("SR13", 13., {_numSR["SR13"], 0.}, {10., 3.}));
        add_result(SignalRegionData("SR14", 11., {_numSR["SR14"], 0.}, {6., 2.}));
        add_result(SignalRegionData("SR15", 260., {_numSR["SR15"], 0.}, {286., 44.}));
        add_result(SignalRegionData("SR16", 51., {_numSR["SR16"], 0.}, {62., 14.}));
        add_result(SignalRegionData("SR17", 10., {_numSR["SR17"], 0.}, {20., 5.}));
        add_result(SignalRegionData("SR18", 9., {_numSR["SR18"], 0.}, {16., 4.}));
        add_result(SignalRegionData("SR19", 297., {_numSR["SR19"], 0.}, {321., 42.}));
        add_result(SignalRegionData("SR20", 38., {_numSR["SR20"], 0.}, {50., 14.}));
        add_result(SignalRegionData("SR21", 2., {_numSR["SR21"], 0.}, {5., 2.}));
        add_result(SignalRegionData("SR22", 2., {_numSR["SR22"], 0.}, {1.1, 0.5}));
        add_result(SignalRegionData("SR23", 18., {_numSR["SR23"], 0.}, {25., 6.}));
        add_result(SignalRegionData("SR24", 13., {_numSR["SR24"], 0.}, {12., 5.}));
        add_result(SignalRegionData("SR25", 5., {_numSR["SR25"], 0.}, {5., 2.}));
        add_result(SignalRegionData("SR26", 2., {_numSR["SR26"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR27", 250., {_numSR["SR27"], 0.}, {279., 34.}));
        add_result(SignalRegionData("SR28", 81., {_numSR["SR28"], 0.}, {87., 13.}));
        add_result(SignalRegionData("SR29", 20., {_numSR["SR29"], 0.}, {26., 6.}));
        add_result(SignalRegionData("SR30", 10., {_numSR["SR30"], 0.}, {8., 2.}));
        add_result(SignalRegionData("SR31", 5., {_numSR["SR31"], 0.}, {6., 1.}));
        add_result(SignalRegionData("SR32", 49., {_numSR["SR32"], 0.}, {54., 8.}));
        add_result(SignalRegionData("SR33", 11., {_numSR["SR33"], 0.}, {11., 3.}));
        add_result(SignalRegionData("SR34", 2., {_numSR["SR34"], 0.}, {2.2, 0.9}));
        add_result(SignalRegionData("SR35", 2., {_numSR["SR35"], 0.}, {0.5, 0.4}));
        add_result(SignalRegionData("SR36", 5., {_numSR["SR36"], 0.}, {6., 2.}));
        add_result(SignalRegionData("SR37", 2., {_numSR["SR37"], 0.}, {3.0, 1.3}));
        add_result(SignalRegionData("SR38", 0., {_numSR["SR38"], 0.}, {1.1, 0.4}));
        add_result(SignalRegionData("SR39", 3., {_numSR["SR39"], 0.}, {0.9, 0.4}));
        add_result(SignalRegionData("SR40", 292., {_numSR["SR40"], 0.}, {310., 40.}));
        add_result(SignalRegionData("SR41", 69., {_numSR["SR41"], 0.}, {81., 18.}));
        add_result(SignalRegionData("SR42", 23., {_numSR["SR42"], 0.}, {25., 6.}));
        add_result(SignalRegionData("SR43", 8., {_numSR["SR43"], 0.}, {13., 3.}));
        add_result(SignalRegionData("SR44", 45., {_numSR["SR44"], 0.}, {45., 6.}));
        add_result(SignalRegionData("SR45", 12., {_numSR["SR45"], 0.}, {14., 3.}));
        add_result(SignalRegionData("SR46", 5., {_numSR["SR46"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR47", 1., {_numSR["SR47"], 0.}, {1.9, 0.8}));
        add_result(SignalRegionData("SR48", 2., {_numSR["SR48"], 0.}, {1.8, 0.8}));
        add_result(SignalRegionData("SR49", 1., {_numSR["SR49"], 0.}, {1.0, 0.5}));
        add_result(SignalRegionData("SR50", 12., {_numSR["SR50"], 0.}, {9., 3.}));
        add_result(SignalRegionData("SR51", 2., {_numSR["SR51"], 0.}, {4., 2.}));
        add_result(SignalRegionData("SR52", 2., {_numSR["SR52"], 0.}, {2.0, 0.7}));
        add_result(SignalRegionData("SR53", 2., {_numSR["SR53"], 0.}, {1.5, 0.7}));
        add_result(SignalRegionData("SR45", 1., {_numSR["SR45"], 0.}, {0.6, 0.3}));
        add_result(SignalRegionData("SR55", 1., {_numSR["SR55"], 0.}, {1.1, 0.5}));
        add_result(SignalRegionData("SR56", 170., {_numSR["SR56"], 0.}, {173., 21.}));
        add_result(SignalRegionData("SR57", 28., {_numSR["SR57"], 0.}, {44., 7.}));
        add_result(SignalRegionData("SR58", 12., {_numSR["SR58"], 0.}, {23., 6.}));

        // // Covariance matrix
        // static const vector< vector<double> > BKGCOV = {
        //   // Turn this correlation matrix into a covariance matrix and add it here: 
        //   // http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-004/CMS-SUS-17-004_Figure-aux_005.png
        // };        

        // set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb)


  }
}
