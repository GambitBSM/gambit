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
	
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_3Lep_36invfb)


  }
}
