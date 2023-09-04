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

#include "gambit/ColliderBit/analyses/Analysis.hpp"
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
    class Analysis_CMS_13TeV_MultiLEP_Full_36invfb : public Analysis {

    protected:
      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        // 2SSLep SRs
        {"SS01", EventCounter("SS01")},
        {"SS02", EventCounter("SS02")},
        {"SS03", EventCounter("SS03")},
        {"SS04", EventCounter("SS04")},
        {"SS05", EventCounter("SS05")},
        {"SS06", EventCounter("SS06")},
        {"SS07", EventCounter("SS07")},
        {"SS08", EventCounter("SS08")},
        {"SS09", EventCounter("SS09")},
        {"SS10", EventCounter("SS10")},
        {"SS11", EventCounter("SS11")},
        {"SS12", EventCounter("SS12")},
        {"SS13", EventCounter("SS13")},
        {"SS14", EventCounter("SS14")},
        {"SS15", EventCounter("SS15")},
        {"SS16", EventCounter("SS16")},
        {"SS17", EventCounter("SS17")},
        {"SS18", EventCounter("SS18")},
        {"SS19", EventCounter("SS19")},
        {"SS20", EventCounter("SS20")},
        {"SS21", EventCounter("SS21")},
        {"SS22", EventCounter("SS22")},
        {"SS23", EventCounter("SS23")},
        {"SS24", EventCounter("SS24")},
        {"SS25", EventCounter("SS25")},
        {"SS26", EventCounter("SS26")},
        {"SS27", EventCounter("SS27")},
        {"SS28", EventCounter("SS28")},
        {"SS29", EventCounter("SS29")},
        {"SS30", EventCounter("SS30")},
        // 3Lep SRs
        {"A01", EventCounter("A01")},
        {"A02", EventCounter("A02")},
        {"A03", EventCounter("A03")},
        {"A04", EventCounter("A04")},
        {"A05", EventCounter("A05")},
        {"A06", EventCounter("A06")},
        {"A07", EventCounter("A07")},
        {"A08", EventCounter("A08")},
        {"A09", EventCounter("A09")},
        {"A10", EventCounter("A10")},
        {"A11", EventCounter("A11")},
        {"A12", EventCounter("A12")},
        {"A13", EventCounter("A13")},
        {"A14", EventCounter("A14")},
        // SR A15 overlaps with a CR and is not used for the results in arxiv:1709.05406
        // {"A15", EventCounter("A16")},
        {"A16", EventCounter("A16")},
        {"A17", EventCounter("A17")},
        {"A18", EventCounter("A18")},
        {"A19", EventCounter("A19")},
        {"A20", EventCounter("A20")},
        {"A21", EventCounter("A21")},
        {"A22", EventCounter("A22")},
        {"A23", EventCounter("A23")},
        {"A24", EventCounter("A24")},
        {"A25", EventCounter("A25")},
        {"A26", EventCounter("A26")},
        {"A27", EventCounter("A27")},
        {"A28", EventCounter("A28")},
        {"A29", EventCounter("A29")},
        {"A30", EventCounter("A30")},
        {"A31", EventCounter("A31")},
        {"A32", EventCounter("A32")},
        {"A33", EventCounter("A33")},
        {"A34", EventCounter("A34")},
        {"A35", EventCounter("A35")},
        {"A36", EventCounter("A36")},
        {"A37", EventCounter("A37")},
        {"A38", EventCounter("A38")},
        {"A39", EventCounter("A39")},
        {"A40", EventCounter("A40")},
        {"A41", EventCounter("A41")},
        {"A42", EventCounter("A42")},
        {"A43", EventCounter("A43")},
        {"A44", EventCounter("A44")},
        // 3Lep_rebinned SRs
        {"SR01", EventCounter("SR01")},
        {"SR02", EventCounter("SR02")},
        {"SR03", EventCounter("SR03")},
        {"SR04", EventCounter("SR04")},
        {"SR05", EventCounter("SR05")},
        {"SR06", EventCounter("SR06")},
        {"SR07", EventCounter("SR07")},
        {"SR08", EventCounter("SR08")},
        {"SR09", EventCounter("SR09")},
        {"SR10", EventCounter("SR10")},
        {"SR11", EventCounter("SR11")},
        {"SR12", EventCounter("SR12")},
        {"SR13", EventCounter("SR13")},
        {"SR14", EventCounter("SR14")},
        {"SR15", EventCounter("SR15")},
        {"SR16", EventCounter("SR16")},
        {"SR17", EventCounter("SR17")},
        {"SR18", EventCounter("SR18")},
        {"SR19", EventCounter("SR19")},
        {"SR20", EventCounter("SR20")},
        {"SR21", EventCounter("SR21")},
        {"SR22", EventCounter("SR22")},
        {"SR23", EventCounter("SR23")},
        {"SR24", EventCounter("SR24")},
        {"SR25", EventCounter("SR25")},
        {"SR26", EventCounter("SR26")},
        {"SR27", EventCounter("SR27")},
        {"SR28", EventCounter("SR28")},
        {"SR29", EventCounter("SR29")},
        {"SR30", EventCounter("SR30")},
        {"SR31", EventCounter("SR31")},
        {"SR32", EventCounter("SR32")},
        {"SR33", EventCounter("SR33")},
        {"SR34", EventCounter("SR34")},
        {"SR35", EventCounter("SR35")},
        {"SR36", EventCounter("SR36")},
        {"SR37", EventCounter("SR37")},
        {"SR38", EventCounter("SR38")},
        {"SR39", EventCounter("SR39")},
        {"SR40", EventCounter("SR40")},
        {"SR41", EventCounter("SR41")},
        {"SR42", EventCounter("SR42")},
        {"SR43", EventCounter("SR43")},
        {"SR44", EventCounter("SR44")},
        {"SR45", EventCounter("SR45")},
        {"SR46", EventCounter("SR46")},
        {"SR47", EventCounter("SR47")},
        {"SR48", EventCounter("SR48")},
        {"SR49", EventCounter("SR49")},
        {"SR50", EventCounter("SR50")},
        {"SR51", EventCounter("SR51")},
        {"SR52", EventCounter("SR52")},
        {"SR53", EventCounter("SR53")},
        {"SR54", EventCounter("SR54")},
        {"SR55", EventCounter("SR55")},
        {"SR56", EventCounter("SR56")},
        {"SR57", EventCounter("SR57")},
        {"SR58", EventCounter("SR58")},
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
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
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
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          bool isEl=has_tag(_eff2dEl, fabs(electron->eta()), electron->pT());
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
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          bool isMu=has_tag(_eff2dMu, fabs(muon->eta()), muon->pT());
          if (muon->pT()>10. &&fabs(muon->eta())<2.4 && isMu)baselineMuons.push_back(muon);
        }

        // @note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/TauIDEfficiency_pT_DP2016_066.pdf
        const vector<double> aTau={0.,2.3};
        const vector<double> bTau={0.,25.,30.,35.,40.,45.,50.,60.,70.,80.,DBL_MAX};  // Assuming flat efficiency above pT = 100 GeV, where the CMS map stops.
        // The tau efficiencies should be corrected with a data/simulation scale factor of 0.95, as instructed here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
        const vector<double> cTau={0.38*0.95, 0.48*0.95, 0.5*0.95, 0.49*0.95, 0.51*0.95, 0.49*0.95, 0.47*0.95, 0.45*0.95, 0.48*0.95, 0.5*0.95};
        HEPUtils::BinnedFn2D<double> _eff2dTau(aTau,bTau,cTau);
        vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus()) {
          bool isTau=has_tag(_eff2dTau, fabs(tau->eta()), tau->pT());
          if (tau->pT()>20. &&fabs(tau->eta())<2.3 && isTau)baselineTaus.push_back(tau);
        }

        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT()>25. &&fabs(jet->eta())<2.4)baselineJets.push_back(jet);
        }

        // Signal objects
        vector<const HEPUtils::Particle*> signalElectrons=baselineElectrons;
        vector<const HEPUtils::Particle*> signalMuons=baselineMuons;
        vector<const HEPUtils::Particle*> signalTaus=baselineTaus;
        vector<const HEPUtils::Particle*> signalLightLeptons=signalElectrons;
        signalLightLeptons.insert(signalLightLeptons.end(),signalMuons.begin(),signalMuons.end());
        vector<const HEPUtils::Particle*> signalLeptons=signalTaus;
        signalLeptons.insert(signalLeptons.end(),signalLightLeptons.begin(),signalLightLeptons.end());
        sort(signalLightLeptons.begin(),signalLightLeptons.end(),comparePt);
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
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
        vector<vector<const HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
        vector<vector<const HEPUtils::Particle*>> OSpair_cont = getOSpairs(signalLeptons);

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
                if(mT < 100 && pT_ll < 50 && met < 100) _counters.at("SS01").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && pp) _counters.at("SS02").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && mm) _counters.at("SS03").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 150 && met < 200) _counters.at("SS04").add_event(event);
                if(mT < 100 && pT_ll < 50 && met > 200) _counters.at("SS05").add_event(event);
                if(mT < 100 && pT_ll > 50 && met < 100) _counters.at("SS06").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && pp) _counters.at("SS07").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && mm) _counters.at("SS08").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 150 && met < 200) _counters.at("SS09").add_event(event);
                if(mT < 100 && pT_ll > 50 && met > 200) _counters.at("SS10").add_event(event);
                if(mT > 100 && met < 100) _counters.at("SS11").add_event(event);
                if(mT > 100 && met >= 100 && met < 150 && pp) _counters.at("SS12").add_event(event);
                if(mT > 100 && met >= 100 && met < 150 && mm) _counters.at("SS13").add_event(event);
                if(mT > 100 && met >= 150 && met < 200) _counters.at("SS14").add_event(event);
                if(mT > 100 && met > 200) _counters.at("SS15").add_event(event);

              }

              if (num_ISRjets==1){

                // The 1 jet regions
                if(mT < 100 && pT_ll < 50 && met < 100) _counters.at("SS16").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && pp) _counters.at("SS17").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 100 && met < 150 && mm) _counters.at("SS18").add_event(event);
                if(mT < 100 && pT_ll < 50 && met >= 150 && met < 200) _counters.at("SS19").add_event(event);
                if(mT < 100 && pT_ll < 50 && met > 200) _counters.at("SS20").add_event(event);
                if(mT < 100 && pT_ll > 50 && met < 100) _counters.at("SS21").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && pp) _counters.at("SS22").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 100 && met < 150 && mm) _counters.at("SS23").add_event(event);
                if(mT < 100 && pT_ll > 50 && met >= 150 && met < 200) _counters.at("SS24").add_event(event);
                if(mT < 100 && pT_ll > 50 && met > 200) _counters.at("SS25").add_event(event);
                if(mT > 100 && met < 100) _counters.at("SS26").add_event(event);
                if(mT > 100 && met >= 100 && met < 150 && pp) _counters.at("SS27").add_event(event);
                if(mT > 100 && met >= 100 && met < 150 && mm) _counters.at("SS28").add_event(event);
                if(mT > 100 && met >= 150 && met < 200) _counters.at("SS29").add_event(event);
                if(mT > 100 && met > 200) _counters.at("SS30").add_event(event);

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

                if(mT < 100 && met >=50 && met < 100 && mll < 75) _counters.at("A01").add_event(event);
                if(mT < 100 && met >=100 && met < 150 && mll < 75) _counters.at("A02").add_event(event);
                if(mT < 100 && met >=150 && met < 200 && mll < 75) _counters.at("A03").add_event(event);
                if(mT < 100 && met >=200 && met < 250 && mll < 75) _counters.at("A04").add_event(event);
                if(mT < 100 && met >=250 && mll < 75) _counters.at("A05").add_event(event);

                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll < 75) _counters.at("A06").add_event(event);
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll < 75) _counters.at("A07").add_event(event);
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll < 75) _counters.at("A08").add_event(event);
                if(mT >= 100 && mT < 160 && met >=200 && mll < 75) _counters.at("A09").add_event(event);
                if(mT >= 160 && met >=50 && met < 100 && mll < 75) _counters.at("A10").add_event(event);
                if(mT >= 160 && met >=100 && met < 150 && mll < 75) _counters.at("A11").add_event(event);
                if(mT >= 160 && met >=150 && met < 200 && mll < 75) _counters.at("A12").add_event(event);
                if(mT >= 160 && met >=200 && met < 250 && mll < 75) _counters.at("A13").add_event(event);
                if(mT >= 160 && met >=250 && mll < 75) _counters.at("A14").add_event(event);

                // SR A15 overlaps with a CR and is not used for the results in arxiv:1709.05406
                // if(mT < 100 && met >=50 && met < 100 && mll >= 75 && mll < 105) _counters.at("A15").add_event(event);
                if(mT < 100 && met >=100 && met < 150 && mll >= 75 && mll < 105) _counters.at("A16").add_event(event);
                if(mT < 100 && met >=150 && met < 200 && mll >= 75 && mll < 105) _counters.at("A17").add_event(event);
                if(mT < 100 && met >=200 && met < 250 && mll >= 75 && mll < 105) _counters.at("A18").add_event(event);
                if(mT < 100 && met >=250 && met < 400 && mll >= 75 && mll < 105) _counters.at("A19").add_event(event);
                if(mT < 100 && met >=400 && met < 550 && mll >= 75 && mll < 105) _counters.at("A20").add_event(event);
                if(mT < 100 && met >=550 && mll >= 75 && mll < 105) _counters.at("A21").add_event(event);
                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll >= 75 && mll < 105) _counters.at("A22").add_event(event);
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll >= 75 && mll < 105) _counters.at("A23").add_event(event);
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll >= 75 && mll < 105) _counters.at("A24").add_event(event);
                if(mT >= 100 && mT < 160 && met >=200 && mll >= 75 && mll < 105) _counters.at("A25").add_event(event);

                if(mT >= 160 && met >=50 && met < 100 && mll >= 75 && mll < 105) _counters.at("A26").add_event(event);
                if(mT >= 160 && met >=100 && met < 150 && mll >= 75 && mll < 105) _counters.at("A27").add_event(event);
                if(mT >= 160 && met >=150 && met < 200 && mll >= 75 && mll < 105) _counters.at("A28").add_event(event);
                if(mT >= 160 && met >=200 && met < 250 && mll >= 75 && mll < 105) _counters.at("A29").add_event(event);
                if(mT >= 160 && met >=250 && met < 400 && mll >= 75 && mll < 105) _counters.at("A30").add_event(event);
                if(mT >= 160 && met >= 400 && mll >= 75 && mll < 105) _counters.at("A31").add_event(event);

                if(mT < 100 && met >=50 && met < 100 && mll >= 105) _counters.at("A32").add_event(event);
                if(mT < 100 && met >=100 && met < 150 && mll >= 105) _counters.at("A33").add_event(event);
                if(mT < 100 && met >=150 && met < 200 && mll >= 105) _counters.at("A34").add_event(event);
                if(mT < 100 && met >=200 && met < 250 && mll >= 105) _counters.at("A35").add_event(event);
                if(mT < 100 && met >=250 && mll >= 105) _counters.at("A36").add_event(event);

                if(mT >= 100 && mT < 160 && met >=50 && met < 100 && mll >= 105) _counters.at("A37").add_event(event);
                if(mT >= 100 && mT < 160 && met >=100 && met < 150 && mll >= 105) _counters.at("A38").add_event(event);
                if(mT >= 100 && mT < 160 && met >=150 && met < 200 && mll >= 105) _counters.at("A39").add_event(event);
                if(mT >= 100 && mT < 160 && met >=200 && mll >= 105) _counters.at("A40").add_event(event);
                if(mT >= 160 && met >=50 && met < 100 && mll >= 105) _counters.at("A41").add_event(event);
                if(mT >= 160 && met >=100 && met < 150 && mll >= 105) _counters.at("A42").add_event(event);
                if(mT >= 160 && met >=150 && met < 200 && mll >= 105) _counters.at("A43").add_event(event);
                if(mT >= 160 && met >=200 && mll >= 105) _counters.at("A44").add_event(event);

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
                if(mll < 75 && mT < 100 && HT < 200 && met > 50 && met < 100) _counters.at("SR01").add_event(event);
                if(mll < 75 && mT < 100 && HT < 200 && met > 100 && met < 150) _counters.at("SR02").add_event(event);
                if(mll < 75 && mT < 100 && HT < 200 && met > 150 && met < 200) _counters.at("SR03").add_event(event);
                if(mll < 75 && mT < 100 && HT < 200 && met > 200) _counters.at("SR04").add_event(event);

                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 50 && met < 100) _counters.at("SR05").add_event(event);
                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 100 && met < 150) _counters.at("SR06").add_event(event);
                if(mll < 75 && mT > 100 && mT < 160 && HT < 200 && met > 150) _counters.at("SR07").add_event(event);

                if(mll < 75 && mT > 160 && HT < 200 && met > 50 && met < 100) _counters.at("SR08").add_event(event);
                if(mll < 75 && mT > 160 && HT < 200 && met > 100 && met < 150) _counters.at("SR09").add_event(event);
                if(mll < 75 && mT > 160 && HT < 200 && met > 150 && met < 200) _counters.at("SR10").add_event(event);
                if(mll < 75 && mT > 160 && HT < 200 && met > 200) _counters.at("SR11").add_event(event);

                if(mll < 75 && mT < 100 && HT > 200 && met > 50) _counters.at("SR12").add_event(event);
                if(mll < 75 && mT > 100 && mT < 160 && HT > 200 && met > 50) _counters.at("SR13").add_event(event);
                if(mll < 75 && mT > 160 && HT > 200 && met > 50) _counters.at("SR14").add_event(event);

                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 100 && met < 150) _counters.at("SR15").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 150 && met < 200) _counters.at("SR16").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 200 && met < 250) _counters.at("SR17").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT < 100 && met > 250) _counters.at("SR18").add_event(event);

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 50 && met < 100) _counters.at("SR19").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 100 && met < 150) _counters.at("SR20").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 150 && met < 200) _counters.at("SR21").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT < 100 && met > 200) _counters.at("SR22").add_event(event);

                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 50 && met < 100) _counters.at("SR23").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 100 && met < 150) _counters.at("SR24").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 150 && met < 200) _counters.at("SR25").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT < 100 && met > 200) _counters.at("SR26").add_event(event);

                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 50 && met < 100) _counters.at("SR27").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 100 && met < 150) _counters.at("SR28").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 150 && met < 200) _counters.at("SR29").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 200 && met < 250) _counters.at("SR30").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 100 && HT < 200 && met > 250) _counters.at("SR31").add_event(event);

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 50 && met < 100) _counters.at("SR32").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 100 && met < 150) _counters.at("SR33").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 150 && met < 200) _counters.at("SR34").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 100 && HT < 200 && met > 200) _counters.at("SR35").add_event(event);

                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 50 && met < 100) _counters.at("SR36").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 100 && met < 150) _counters.at("SR37").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 150 && met < 200) _counters.at("SR38").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 100 && HT < 200 && met > 200) _counters.at("SR39").add_event(event);

                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 50 && met < 150) _counters.at("SR40").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 150 && met < 250) _counters.at("SR41").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 250 && met < 350) _counters.at("SR42").add_event(event);
                if(mll > 75 && mll < 105 && mT < 100 && HT > 200 && met > 350) _counters.at("SR43").add_event(event);

                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 50 && met < 100) _counters.at("SR44").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 100 && met < 150) _counters.at("SR45").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 150 && met < 200) _counters.at("SR46").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 200 && met < 250) _counters.at("SR47").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 250 && met < 300) _counters.at("SR48").add_event(event);
                if(mll > 75 && mll < 105 && mT > 100 && mT < 160 && HT > 200 && met > 300) _counters.at("SR49").add_event(event);

                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 50 && met < 100) _counters.at("SR50").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 100 && met < 150) _counters.at("SR51").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 150 && met < 200) _counters.at("SR52").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 200 && met < 250) _counters.at("SR53").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 250 && met < 300) _counters.at("SR54").add_event(event);
                if(mll > 75 && mll < 105 && mT > 160 && HT > 200 && met > 300) _counters.at("SR55").add_event(event);

                if(mll > 105 && mT < 100 && met > 50) _counters.at("SR56").add_event(event);
                if(mll > 105 && mT > 100 && mT < 160 && met > 50) _counters.at("SR57").add_event(event);
                if(mll > 105 && mT > 160 && met > 50) _counters.at("SR58").add_event(event);

              }
            }
          }
        }


      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_MultiLEP_Full_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_MultiLEP_Full_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

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

      }


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        //Now fill a results object with the results for each SR

        add_result(SignalRegionData(_counters.at("SS01"), 1193., {1430., 180.}));
        add_result(SignalRegionData(_counters.at("SS02"), 50., {56., 9.}));
        add_result(SignalRegionData(_counters.at("SS03"), 25., {36., 7.}));
        add_result(SignalRegionData(_counters.at("SS04"), 7., {5.9, 1.2}));
        add_result(SignalRegionData(_counters.at("SS05"), 2., {4.5, 3.5}));
        add_result(SignalRegionData(_counters.at("SS06"), 143., {163., 19.}));
        add_result(SignalRegionData(_counters.at("SS07"), 41., {38., 6.}));
        add_result(SignalRegionData(_counters.at("SS08"), 24., {23., 4.}));
        add_result(SignalRegionData(_counters.at("SS09"), 11., {14.4, 3.2}));
        add_result(SignalRegionData(_counters.at("SS10"), 6., {6.3, 0.9}));
        add_result(SignalRegionData(_counters.at("SS11"), 67., {82., 12.}));
        add_result(SignalRegionData(_counters.at("SS12"), 19., {27., 4.}));
        add_result(SignalRegionData(_counters.at("SS13"), 18., {18., 4.}));
        add_result(SignalRegionData(_counters.at("SS14"), 9., {5.0, 0.8}));
        add_result(SignalRegionData(_counters.at("SS15"), 3., {5.1, 2.6}));
        add_result(SignalRegionData(_counters.at("SS16"), 591., {603., 80.}));
        add_result(SignalRegionData(_counters.at("SS17"), 116., {98., 14.}));
        add_result(SignalRegionData(_counters.at("SS18"), 69., {66., 10.}));
        add_result(SignalRegionData(_counters.at("SS19"), 43., {33., 6.}));
        add_result(SignalRegionData(_counters.at("SS20"), 13., {11.4, 1.7}));
        add_result(SignalRegionData(_counters.at("SS21"), 232., {264., 31.}));
        add_result(SignalRegionData(_counters.at("SS22"), 52., {51., 7.}));
        add_result(SignalRegionData(_counters.at("SS23"), 35., {31., 4.}));
        add_result(SignalRegionData(_counters.at("SS24"), 28., {29., 5.}));
        add_result(SignalRegionData(_counters.at("SS25"), 27., {22.2, 3.4}));
        add_result(SignalRegionData(_counters.at("SS26"), 49., {44., 7.}));
        add_result(SignalRegionData(_counters.at("SS27"), 18., {16.4, 2.9}));
        add_result(SignalRegionData(_counters.at("SS28"), 13., {10.7, 1.9}));
        add_result(SignalRegionData(_counters.at("SS29"), 9., {6.7, 1.1}));
        add_result(SignalRegionData(_counters.at("SS30"), 7., {3.9, 0.8}));

        add_result(SignalRegionData(_counters.at("A01"), 186., {185., 22.}));
        add_result(SignalRegionData(_counters.at("A02"), 34., {35., 6.}));
        add_result(SignalRegionData(_counters.at("A03"), 11., {9.3, 2.2}));
        add_result(SignalRegionData(_counters.at("A04"), 1., {3.3, 1.0}));
        add_result(SignalRegionData(_counters.at("A05"), 5., {4., 1.}));
        add_result(SignalRegionData(_counters.at("A06"), 60., {50., 8.}));
        add_result(SignalRegionData(_counters.at("A07"), 19., {15., 4.}));
        add_result(SignalRegionData(_counters.at("A08"), 1., {1.9, 0.6}));
        add_result(SignalRegionData(_counters.at("A09"), 3., {0.8, 0.4}));
        add_result(SignalRegionData(_counters.at("A10"), 16., {13., 2.8}));
        add_result(SignalRegionData(_counters.at("A11"), 17., {11.9, 3.2}));
        add_result(SignalRegionData(_counters.at("A12"), 4., {3.1, 1.2}));
        add_result(SignalRegionData(_counters.at("A13"), 3., {2.1, 0.8}));
        add_result(SignalRegionData(_counters.at("A14"), 1., {0.9, 0.4}));
        // SR A15 overlaps with a CR and is not used for the results in arxiv:1709.05406
        // add_result(SignalRegionData(_counters.at("A15"), 2278., {2180., 260}));
        add_result(SignalRegionData(_counters.at("A16"), 429., {440., 70}));
        add_result(SignalRegionData(_counters.at("A17"), 123., {129., 28}));
        add_result(SignalRegionData(_counters.at("A18"), 37., {48., 10}));
        add_result(SignalRegionData(_counters.at("A19"), 38., {42., 9}));
        add_result(SignalRegionData(_counters.at("A20"), 5., {8.5, 2.1}));
        add_result(SignalRegionData(_counters.at("A21"), 2., {2.6, 0.8}));
        add_result(SignalRegionData(_counters.at("A22"), 391., {390, 50}));
        add_result(SignalRegionData(_counters.at("A23"), 61., {72, 19}));
        add_result(SignalRegionData(_counters.at("A24"), 9., {10, 4}));
        add_result(SignalRegionData(_counters.at("A25"), 8., {4.9, 1.9}));
        add_result(SignalRegionData(_counters.at("A26"), 35., {37, 9}));
        add_result(SignalRegionData(_counters.at("A27"), 17., {21., 8.}));
        add_result(SignalRegionData(_counters.at("A28"), 7., {8.9, 3.1}));
        add_result(SignalRegionData(_counters.at("A29"), 5., {3.6, 1.3}));
        add_result(SignalRegionData(_counters.at("A30"), 3., {4.1, 1.6}));
        add_result(SignalRegionData(_counters.at("A31"), 1., {1.0, 0.5}));
        add_result(SignalRegionData(_counters.at("A32"), 123., {121., 14.}));
        add_result(SignalRegionData(_counters.at("A33"), 32., {32.0, 5.}));
        add_result(SignalRegionData(_counters.at("A34"), 4., {11.6, 2.6}));
        add_result(SignalRegionData(_counters.at("A35"), 6., {2.9, 0.8}));
        add_result(SignalRegionData(_counters.at("A36"), 5., {3.7, 1.0}));
        add_result(SignalRegionData(_counters.at("A37"), 17., {32., 5.}));
        add_result(SignalRegionData(_counters.at("A38"), 9., {9.6, 2.4}));
        add_result(SignalRegionData(_counters.at("A39"), 0., {2.4, 0.7}));
        add_result(SignalRegionData(_counters.at("A40"), 2., {1.0, 0.4}));
        add_result(SignalRegionData(_counters.at("A41"), 9., {9.4, 2.4}));
        add_result(SignalRegionData(_counters.at("A42"), 3., {6.6, 2.1}));
        add_result(SignalRegionData(_counters.at("A43"), 0., {3.1, 1.0}));
        add_result(SignalRegionData(_counters.at("A44"), 1., {2.5, 0.8}));

        add_result(SignalRegionData(_counters.at("SR01"), 166., {175., 20.}));
        add_result(SignalRegionData(_counters.at("SR02"), 23., {27., 4.}));
        add_result(SignalRegionData(_counters.at("SR03"), 6., {5., 1.}));
        add_result(SignalRegionData(_counters.at("SR04"), 1., {2.5, 0.8}));
        add_result(SignalRegionData(_counters.at("SR05"), 56., {50., 8.}));
        add_result(SignalRegionData(_counters.at("SR06"), 13., {12., 3.}));
        add_result(SignalRegionData(_counters.at("SR07"), 1., {1.2, 0.4}));
        add_result(SignalRegionData(_counters.at("SR08"), 13., {12., 2.}));
        add_result(SignalRegionData(_counters.at("SR09"), 14., {11., 3.}));
        add_result(SignalRegionData(_counters.at("SR10"), 2., {2.6, 0.9}));
        add_result(SignalRegionData(_counters.at("SR11"), 1., {1.2, 0.5}));
        add_result(SignalRegionData(_counters.at("SR12"), 41., {39., 6.}));
        add_result(SignalRegionData(_counters.at("SR13"), 13., {10., 3.}));
        add_result(SignalRegionData(_counters.at("SR14"), 11., {6., 2.}));
        add_result(SignalRegionData(_counters.at("SR15"), 260., {286., 44.}));
        add_result(SignalRegionData(_counters.at("SR16"), 51., {62., 14.}));
        add_result(SignalRegionData(_counters.at("SR17"), 10., {20., 5.}));
        add_result(SignalRegionData(_counters.at("SR18"), 9., {16., 4.}));
        add_result(SignalRegionData(_counters.at("SR19"), 297., {321., 42.}));
        add_result(SignalRegionData(_counters.at("SR20"), 38., {50., 14.}));
        add_result(SignalRegionData(_counters.at("SR21"), 2., {5., 2.}));
        add_result(SignalRegionData(_counters.at("SR22"), 2., {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("SR23"), 18., {25., 6.}));
        add_result(SignalRegionData(_counters.at("SR24"), 13., {12., 5.}));
        add_result(SignalRegionData(_counters.at("SR25"), 5., {5., 2.}));
        add_result(SignalRegionData(_counters.at("SR26"), 2., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR27"), 250., {279., 34.}));
        add_result(SignalRegionData(_counters.at("SR28"), 81., {87., 13.}));
        add_result(SignalRegionData(_counters.at("SR29"), 20., {26., 6.}));
        add_result(SignalRegionData(_counters.at("SR30"), 10., {8., 2.}));
        add_result(SignalRegionData(_counters.at("SR31"), 5., {6., 1.}));
        add_result(SignalRegionData(_counters.at("SR32"), 49., {54., 8.}));
        add_result(SignalRegionData(_counters.at("SR33"), 11., {11., 3.}));
        add_result(SignalRegionData(_counters.at("SR34"), 2., {2.2, 0.9}));
        add_result(SignalRegionData(_counters.at("SR35"), 2., {0.5, 0.4}));
        add_result(SignalRegionData(_counters.at("SR36"), 5., {6., 2.}));
        add_result(SignalRegionData(_counters.at("SR37"), 2., {3.0, 1.3}));
        add_result(SignalRegionData(_counters.at("SR38"), 0., {1.1, 0.4}));
        add_result(SignalRegionData(_counters.at("SR39"), 3., {0.9, 0.4}));
        add_result(SignalRegionData(_counters.at("SR40"), 292., {310., 40.}));
        add_result(SignalRegionData(_counters.at("SR41"), 69., {81., 18.}));
        add_result(SignalRegionData(_counters.at("SR42"), 23., {25., 6.}));
        add_result(SignalRegionData(_counters.at("SR43"), 8., {13., 3.}));
        add_result(SignalRegionData(_counters.at("SR44"), 45., {45., 6.}));
        add_result(SignalRegionData(_counters.at("SR45"), 12., {14., 3.}));
        add_result(SignalRegionData(_counters.at("SR46"), 5., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR47"), 1., {1.9, 0.8}));
        add_result(SignalRegionData(_counters.at("SR48"), 2., {1.8, 0.8}));
        add_result(SignalRegionData(_counters.at("SR49"), 1., {1.0, 0.5}));
        add_result(SignalRegionData(_counters.at("SR50"), 12., {9., 3.}));
        add_result(SignalRegionData(_counters.at("SR51"), 2., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR52"), 2., {2.0, 0.7}));
        add_result(SignalRegionData(_counters.at("SR53"), 2., {1.5, 0.7}));
        add_result(SignalRegionData(_counters.at("SR54"), 1., {0.6, 0.3}));
        add_result(SignalRegionData(_counters.at("SR55"), 1., {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("SR56"), 170., {173., 21.}));
        add_result(SignalRegionData(_counters.at("SR57"), 28., {44., 7.}));
        add_result(SignalRegionData(_counters.at("SR58"), 12., {23., 6.}));

      }


      // Helper function to calculate mll and mT
      vector<double> get_mll_mT(vector<vector<const HEPUtils::Particle*>> pair_cont, vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 met, int type) {
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
      double get_mTmin(vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 met) {
        vector<double> mT_container;
        for (size_t iLe=0;iLe<leptons.size();iLe++) {
          mT_container.push_back(sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi()))));
        }
        sort(mT_container.begin(),mT_container.end());
        if (mT_container.size()>0) return mT_container.at(0);
        else return -1;
      }


    protected:
      void analysis_specific_reset() {

        for (auto& pair : _counters) { pair.second.reset(); }

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

        add_result(SignalRegionData(_counters.at("SS01"), 1193., {1430., 180.}));
        add_result(SignalRegionData(_counters.at("SS02"), 50., {56., 9.}));
        add_result(SignalRegionData(_counters.at("SS03"), 25., {36., 7.}));
        add_result(SignalRegionData(_counters.at("SS04"), 7., {5.9, 1.2}));
        add_result(SignalRegionData(_counters.at("SS05"), 2., {4.5, 3.5}));
        add_result(SignalRegionData(_counters.at("SS06"), 143., {163., 19.}));
        add_result(SignalRegionData(_counters.at("SS07"), 41., {38., 6.}));
        add_result(SignalRegionData(_counters.at("SS08"), 24., {23., 4.}));
        add_result(SignalRegionData(_counters.at("SS09"), 11., {14.4, 3.2}));
        add_result(SignalRegionData(_counters.at("SS10"), 6., {6.3, 0.9}));
        add_result(SignalRegionData(_counters.at("SS11"), 67., {82., 12.}));
        add_result(SignalRegionData(_counters.at("SS12"), 19., {27., 4.}));
        add_result(SignalRegionData(_counters.at("SS13"), 18., {18., 4.}));
        add_result(SignalRegionData(_counters.at("SS14"), 9., {5.0, 0.8}));
        add_result(SignalRegionData(_counters.at("SS15"), 3., {5.1, 2.6}));
        add_result(SignalRegionData(_counters.at("SS16"), 591., {603., 80.}));
        add_result(SignalRegionData(_counters.at("SS17"), 116., {98., 14.}));
        add_result(SignalRegionData(_counters.at("SS18"), 69., {66., 10.}));
        add_result(SignalRegionData(_counters.at("SS19"), 43., {33., 6.}));
        add_result(SignalRegionData(_counters.at("SS20"), 13., {11.4, 1.7}));
        add_result(SignalRegionData(_counters.at("SS21"), 232., {264., 31.}));
        add_result(SignalRegionData(_counters.at("SS22"), 52., {51., 7.}));
        add_result(SignalRegionData(_counters.at("SS23"), 35., {31., 4.}));
        add_result(SignalRegionData(_counters.at("SS24"), 28., {29., 5.}));
        add_result(SignalRegionData(_counters.at("SS25"), 27., {22.2, 3.4}));
        add_result(SignalRegionData(_counters.at("SS26"), 49., {44., 7.}));
        add_result(SignalRegionData(_counters.at("SS27"), 18., {16.4, 2.9}));
        add_result(SignalRegionData(_counters.at("SS28"), 13., {10.7, 1.9}));
        add_result(SignalRegionData(_counters.at("SS29"), 9., {6.7, 1.1}));
        add_result(SignalRegionData(_counters.at("SS30"), 7., {3.9, 0.8}));

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

        add_result(SignalRegionData(_counters.at("A01"), 186., {185., 22.}));
        add_result(SignalRegionData(_counters.at("A02"), 34., {35., 6.}));
        add_result(SignalRegionData(_counters.at("A03"), 11., {9.3, 2.2}));
        add_result(SignalRegionData(_counters.at("A04"), 1., {3.3, 1.0}));
        add_result(SignalRegionData(_counters.at("A05"), 5., {4., 1.}));
        add_result(SignalRegionData(_counters.at("A06"), 60., {50., 8.}));
        add_result(SignalRegionData(_counters.at("A07"), 19., {15., 4.}));
        add_result(SignalRegionData(_counters.at("A08"), 1., {1.9, 0.6}));
        add_result(SignalRegionData(_counters.at("A09"), 3., {0.8, 0.4}));
        add_result(SignalRegionData(_counters.at("A10"), 16., {13., 2.8}));
        add_result(SignalRegionData(_counters.at("A11"), 17., {11.9, 3.2}));
        add_result(SignalRegionData(_counters.at("A12"), 4., {3.1, 1.2}));
        add_result(SignalRegionData(_counters.at("A13"), 3., {2.1, 0.8}));
        add_result(SignalRegionData(_counters.at("A14"), 1., {0.9, 0.4}));
        // SR A15 overlaps with a CR and is not used for the results in arxiv:1709.05406
        // add_result(SignalRegionData(_counters.at("A15"), 2278., {2180., 260}));
        add_result(SignalRegionData(_counters.at("A16"), 429., {440., 70}));
        add_result(SignalRegionData(_counters.at("A17"), 123., {129., 28}));
        add_result(SignalRegionData(_counters.at("A18"), 37., {48., 10}));
        add_result(SignalRegionData(_counters.at("A19"), 38., {42., 9}));
        add_result(SignalRegionData(_counters.at("A20"), 5., {8.5, 2.1}));
        add_result(SignalRegionData(_counters.at("A21"), 2., {2.6, 0.8}));
        add_result(SignalRegionData(_counters.at("A22"), 391., {390, 50}));
        add_result(SignalRegionData(_counters.at("A23"), 61., {72, 19}));
        add_result(SignalRegionData(_counters.at("A24"), 9., {10, 4}));
        add_result(SignalRegionData(_counters.at("A25"), 8., {4.9, 1.9}));
        add_result(SignalRegionData(_counters.at("A26"), 35., {37, 9}));
        add_result(SignalRegionData(_counters.at("A27"), 17., {21., 8.}));
        add_result(SignalRegionData(_counters.at("A28"), 7., {8.9, 3.1}));
        add_result(SignalRegionData(_counters.at("A29"), 5., {3.6, 1.3}));
        add_result(SignalRegionData(_counters.at("A30"), 3., {4.1, 1.6}));
        add_result(SignalRegionData(_counters.at("A31"), 1., {1.0, 0.5}));
        add_result(SignalRegionData(_counters.at("A32"), 123., {121., 14.}));
        add_result(SignalRegionData(_counters.at("A33"), 32., {32.0, 5.}));
        add_result(SignalRegionData(_counters.at("A34"), 4., {11.6, 2.6}));
        add_result(SignalRegionData(_counters.at("A35"), 6., {2.9, 0.8}));
        add_result(SignalRegionData(_counters.at("A36"), 5., {3.7, 1.0}));
        add_result(SignalRegionData(_counters.at("A37"), 17., {32., 5.}));
        add_result(SignalRegionData(_counters.at("A38"), 9., {9.6, 2.4}));
        add_result(SignalRegionData(_counters.at("A39"), 0., {2.4, 0.7}));
        add_result(SignalRegionData(_counters.at("A40"), 2., {1.0, 0.4}));
        add_result(SignalRegionData(_counters.at("A41"), 9., {9.4, 2.4}));
        add_result(SignalRegionData(_counters.at("A42"), 3., {6.6, 2.1}));
        add_result(SignalRegionData(_counters.at("A43"), 0., {3.1, 1.0}));
        add_result(SignalRegionData(_counters.at("A44"), 1., {2.5, 0.8}));

        // Covariance matrix
        // Note that this is a 43x43 matrix, since the row & column corresponding to SR A15 has been removed
        static const vector< vector<double> > BKGCOV = {
          { 4.8400e+02,  2.6701e+01,  5.4861e+00,  9.6901e-01,  2.1481e+00,  5.0929e+01,  1.8513e+01,  7.5326e-01,  1.0618e+00,  1.0229e+01,  1.1877e+01,  3.8462e+00,  1.4500e+00,  1.4164e+00,  3.3675e+02, -8.5168e+00,  4.0671e+00, -4.2515e+00,  7.1028e-01,  2.0509e+00,  2.6071e+02, -6.6211e+00, -3.7499e+00,  3.0125e+00,  1.7092e+01, -2.7973e+00, -4.7666e+00,  1.6714e+00, -1.4996e+00,  1.1487e+00,  1.3766e+02,  2.2202e+01,  2.8447e+00,  1.7565e+00,  2.6699e+00,  1.1240e+01,  5.2180e+00,  1.2450e+00,  1.1831e+00,  3.4058e+00,  6.4227e-01,  2.0901e+00,  1.0565e+00},
          { 2.6701e+01,  3.6000e+01,  2.4650e+00,  1.2589e+00,  5.4240e-01,  1.5523e+01,  5.6846e+00,  2.9109e-01,  2.0650e-01,  3.4964e-01,  3.8924e+00,  1.1265e+00,  6.0643e-01,  2.6935e-01,  4.8145e+01,  1.3753e+01,  4.9347e+00,  5.2596e+00,  1.1989e+00,  6.1133e-01,  4.1481e+01, -1.0207e+00,  1.6485e+00,  7.8516e-01,  3.3322e+00,  6.5491e+00,  1.2734e+00,  9.5815e-01,  3.5404e-01,  3.8064e-01,  2.2005e+01,  4.8093e+00,  1.5380e+00,  2.0269e-01,  1.0693e+00,  8.3730e+00,  3.3454e+00,  1.3986e-01,  2.6837e-01,  1.0371e+00,  1.9110e+00,  5.4878e-01,  5.8637e-01},
          { 5.4861e+00,  2.4650e+00,  4.8400e+00,  3.1946e-01,  2.2832e-01,  3.7808e+00,  1.7149e+00,  1.0361e-01,  9.3746e-02,  3.5382e-01,  1.2180e+00,  3.1656e-01,  1.8380e-01,  8.6842e-02,  6.3231e+00,  7.4320e+00,  2.4911e+00,  2.2922e+00,  5.6868e-01,  1.2082e-01, -2.9585e+00,  1.6030e+00,  1.2869e+00,  5.3165e-01,  1.6283e+00,  2.4070e+00,  7.9849e-01,  3.5641e-01,  9.9049e-02,  1.9898e-01,  4.0006e+00,  9.6517e-01,  2.8769e-01,  1.0002e-01,  2.3910e-01,  1.5230e+00,  9.8900e-01,  1.0219e-01,  1.1135e-01,  5.9310e-01,  6.2689e-01,  1.5209e-01,  2.6641e-01},
          { 9.6901e-01,  1.2589e+00,  3.1946e-01,  1.0000e+00,  7.6767e-02,  1.0433e+00,  4.0552e-01,  5.5807e-02,  3.2132e-02,  1.3220e-01,  4.0080e-01,  1.3301e-01,  1.2791e-01,  6.1720e-02,  7.6272e+00,  5.9626e+00,  1.7149e+00,  2.3309e+00,  3.9497e-01,  1.5640e-01,  1.9198e+00,  5.5963e-01,  4.8628e-01,  1.7902e-01,  9.8712e-01,  1.5780e+00,  5.5633e-01,  2.0495e-01,  1.9666e-01,  9.3695e-02,  7.1858e-01,  3.6304e-01,  2.7414e-01,  1.0525e-02,  1.7454e-01,  7.1960e-01,  3.8851e-01,  3.9256e-02,  4.6016e-02,  3.3178e-01,  3.6017e-01,  1.5356e-01,  1.8912e-01},
          { 2.1481e+00,  5.4240e-01,  2.2832e-01,  7.6767e-02,  1.0000e+00,  5.6945e-01,  4.5756e-01,  5.7964e-02,  3.4446e-02,  1.0404e-01,  1.8829e-01,  3.1780e-02,  4.5478e-02,  4.5400e-02,  8.2565e+00,  5.2842e+00,  1.8962e+00,  1.3766e+00,  2.3942e-01,  7.4910e-02, -6.8635e-01,  1.9000e+00,  5.8752e-01,  2.1058e-01,  7.9898e-01,  1.2588e+00,  4.4745e-01,  1.2185e-01,  1.8619e-01,  5.2550e-02,  9.4384e-01,  4.8533e-01,  4.6023e-02,  4.2824e-02,  8.3210e-02,  1.0399e-02,  1.0255e-01,  4.5478e-02,  4.6944e-02,  9.1685e-02,  2.0265e-01,  5.6981e-02,  8.2416e-02},
          { 5.0929e+01,  1.5523e+01,  3.7808e+00,  1.0433e+00,  5.6945e-01,  6.4000e+01,  9.8611e+00,  1.1083e-02,  3.2966e-01,  1.8889e+00,  5.9482e+00,  2.2000e+00,  6.7917e-01,  3.6288e-01,  1.0140e+01, -1.2343e+01, -5.6482e+00, -2.1697e+00,  1.8005e-01,  4.9768e-01,  6.7332e+01, -6.1444e+00,  9.0810e-01,  1.3514e+00,  2.8292e+00,  4.7055e+00,  2.8366e-01,  1.2113e+00, -6.5010e-01,  3.4343e-01,  4.1642e+01,  4.6860e+00,  8.4209e-01,  3.7003e-01,  1.5590e+00,  1.2756e+01,  6.4295e+00,  3.6502e-01,  2.5506e-01,  1.1323e+00,  2.1964e+00,  4.0173e-01,  2.8149e-01},
          { 1.8513e+01,  5.6846e+00,  1.7149e+00,  4.0552e-01,  4.5756e-01,  9.8611e+00,  1.6000e+01,  1.3884e-01,  1.7568e-01,  1.3422e+00,  3.1487e+00,  9.9586e-01,  4.7043e-01,  1.7018e-01, -2.1310e+01, -3.4307e+00, -1.1448e+00, -5.8795e-01,  1.6535e-01,  1.7777e-01,  1.9015e+00,  6.8173e+00,  1.8162e+00,  1.0566e+00,  3.7926e+00,  4.2963e+00,  8.3932e-01,  7.1006e-01,  3.8325e-02,  3.9540e-01,  1.4385e+01,  3.0882e+00,  7.9414e-01,  3.9126e-01,  6.7252e-01,  3.1692e+00,  2.7651e+00,  1.5879e-01,  1.6642e-01,  9.1489e-01,  1.0167e+00,  4.2596e-01,  3.4883e-01},
          { 7.5326e-01,  2.9109e-01,  1.0361e-01,  5.5807e-02,  5.7964e-02,  1.1083e-02,  1.3884e-01,  3.6000e-01,  1.2020e-02,  1.6792e-01,  2.0498e-01,  3.1854e-02,  4.6738e-02,  3.1397e-02,  8.7213e-01,  1.8500e+00,  9.0120e-01,  8.1070e-01,  7.8046e-02,  4.3949e-02, -6.3615e-01,  1.9446e+00,  4.6313e-01,  1.6885e-01,  7.3062e-01,  5.4269e-01,  2.9991e-01,  6.5646e-02,  1.5600e-01,  4.4460e-02,  1.8294e-01,  2.2786e-01, -7.6554e-03,  6.7397e-02,  6.1890e-02, -5.0352e-03,  1.4874e-01,  4.7158e-02,  4.0267e-02,  2.0249e-01,  1.9574e-01,  5.8532e-02,  1.0308e-01},
          { 1.0618e+00,  2.0650e-01,  9.3746e-02,  3.2132e-02,  3.4446e-02,  3.2966e-01,  1.7568e-01,  1.2020e-02,  1.6000e-01,  8.0286e-02,  1.9069e-01,  2.5945e-02,  2.7682e-02,  1.7656e-02,  4.5525e-01,  4.8440e-01,  3.8540e-01,  2.7435e-01,  6.9971e-02,  3.0019e-02,  1.1392e-03,  4.9908e-01,  1.0929e-01,  9.7196e-02,  3.2982e-01,  1.5757e-01,  9.7814e-02,  2.7184e-02,  3.6078e-02,  2.0128e-02,  5.5054e-01,  1.3416e-01,  3.8647e-02,  2.2951e-02,  4.8080e-02,  7.4082e-02,  6.6765e-02,  1.3136e-02,  1.8970e-02,  1.2098e-01,  4.2794e-02,  3.5611e-02,  5.0666e-02},
          { 1.0229e+01,  3.4964e-01,  3.5382e-01,  1.3220e-01,  1.0404e-01,  1.8889e+00,  1.3422e+00,  1.6792e-01,  8.0286e-02,  7.8400e+00,  9.4438e-01,  3.8260e-01,  2.3511e-01,  1.3534e-01, -1.1950e+01,  4.7693e+00,  1.2628e+00, -1.1590e-01,  1.6372e-01,  5.8343e-02, -3.0261e+00,  1.0143e+01,  1.4815e+00,  6.9075e-01,  4.8399e+00,  3.7388e+00,  8.7251e-01,  2.6459e-01,  4.2605e-01,  1.2583e-01,  4.3390e+00,  8.4857e-01,  3.0650e-01,  1.7859e-01,  3.0453e-01, -2.0476e-01,  6.2314e-01,  2.2552e-01,  9.6665e-02,  8.2750e-01,  2.7869e-01,  9.5460e-02,  2.4918e-01},
          { 1.1877e+01,  3.8924e+00,  1.2180e+00,  4.0080e-01,  1.8829e-01,  5.9482e+00,  3.1487e+00,  2.0498e-01,  1.9069e-01,  9.4438e-01,  1.0240e+01,  5.0884e-01,  4.2314e-01,  1.3740e-01, -1.6603e+01,  2.3288e+00,  4.6826e-01,  9.6828e-01,  4.1645e-01,  2.2781e-01, -8.5710e+00,  3.2814e+00,  1.1783e+00,  5.2895e-01,  2.4315e+00,  2.8908e+00,  1.1384e+00,  5.6131e-01,  2.2034e-01,  2.2024e-01,  8.1290e+00,  2.0070e+00,  5.1339e-01,  1.6424e-01,  4.6285e-01,  1.6312e+00,  1.5606e+00,  1.7341e-01,  8.6075e-02,  7.8052e-01,  9.5679e-01,  2.3112e-01,  3.5318e-01},
          { 3.8462e+00,  1.1265e+00,  3.1656e-01,  1.3301e-01,  3.1780e-02,  2.2000e+00,  9.9586e-01,  3.1854e-02,  2.5945e-02,  3.8260e-01,  5.0884e-01,  1.4400e+00,  4.8991e-02,  4.7630e-02, -8.6629e-01,  1.0279e+00,  3.2101e-01,  8.2097e-02,  1.1526e-01,  7.9773e-02,  5.7706e+00,  2.8208e+00,  8.6602e-01,  2.2107e-01,  1.6398e+00,  8.8900e-01,  1.2956e-01,  1.8999e-01, -6.8243e-02,  5.9174e-02,  2.7498e+00,  4.0277e-01, -1.1485e-03,  7.9137e-02,  1.8644e-01,  1.2699e+00,  6.6298e-01,  3.4984e-02,  4.1921e-02,  3.9735e-01,  3.8611e-01,  4.8733e-02,  8.6654e-02},
          { 1.4500e+00,  6.0643e-01,  1.8380e-01,  1.2791e-01,  4.5478e-02,  6.7917e-01,  4.7043e-01,  4.6738e-02,  2.7682e-02,  2.3511e-01,  4.2314e-01,  4.8991e-02,  6.4000e-01,  3.8781e-02,  5.9080e-01,  2.9427e+00,  1.0946e+00,  1.3521e+00,  1.5576e-01,  9.6410e-02, -1.9481e+00,  8.1416e-01,  2.4981e-01,  7.0318e-02,  7.1410e-01,  1.0406e+00,  3.8318e-01,  1.1485e-01,  1.9355e-01,  6.3640e-02,  6.6732e-01,  5.1636e-01,  1.6455e-01,  2.9405e-02,  1.1824e-01,  7.7100e-02,  1.6023e-01,  2.6414e-02,  3.5130e-02,  1.0529e-01,  1.5928e-01,  9.7632e-02,  1.1649e-01},
          { 1.4164e+00,  2.6935e-01,  8.6842e-02,  6.1720e-02,  4.5400e-02,  3.6288e-01,  1.7018e-01,  3.1397e-02,  1.7656e-02,  1.3534e-01,  1.3740e-01,  4.7630e-02,  3.8781e-02,  1.6000e-01,  2.2254e+00,  1.4383e+00,  5.1984e-01,  4.1969e-01,  4.0035e-02,  6.7654e-02,  1.4673e+00,  9.1854e-01,  3.0346e-01,  6.7917e-02,  3.8815e-01,  3.7392e-01,  1.2677e-01,  4.3292e-02,  9.5821e-02,  5.5184e-02,  6.5750e-01,  2.1968e-01,  6.5015e-03,  2.9439e-02,  4.9744e-02,  1.2376e-01,  1.0305e-01,  2.6260e-02,  2.3274e-02,  7.6012e-02,  8.1280e-02,  6.1360e-02,  8.3149e-02},
          { 3.3675e+02,  4.8145e+01,  6.3231e+00,  7.6272e+00,  8.2565e+00,  1.0140e+01, -2.1310e+01,  8.7213e-01,  4.5525e-01, -1.1950e+01, -1.6603e+01, -8.6629e-01,  5.9080e-01,  2.2254e+00,  4.9000e+03,  1.0827e+03,  2.9681e+02,  2.0691e+02,  2.7859e+01,  8.4370e+00,  1.8458e+03,  9.4238e+01,  1.4466e+01, -4.4821e+00,  3.8754e+01,  3.5633e+01,  1.7274e+01,  2.3031e+00,  1.3597e+01,  2.7518e+00,  2.3329e+02,  6.6269e+01,  5.6970e+00,  1.4390e+00,  4.2256e+00,  2.9615e+01, -6.6318e+00,  2.5231e-01,  5.7814e-01, -6.9223e-01,  4.9388e+00,  4.1682e+00,  3.6467e+00},
          {-8.5168e+00,  1.3753e+01,  7.4320e+00,  5.9626e+00,  5.2842e+00, -1.2343e+01, -3.4307e+00,  1.8500e+00,  4.8440e-01,  4.7693e+00,  2.3288e+00,  1.0279e+00,  2.9427e+00,  1.4383e+00,  1.0827e+03,  7.8400e+02,  1.6767e+02,  1.1881e+02,  1.5341e+01,  4.4782e+00,  1.1913e+02,  1.5614e+02,  3.5409e+01,  6.2781e+00,  5.5987e+01,  8.9047e+01,  2.9137e+01,  4.9493e+00,  1.4577e+01,  2.2047e+00,  1.9018e+00,  1.6827e+01,  5.3241e+00,  5.9709e-01,  2.8678e+00, -2.5768e+00,  9.8549e-01,  8.2048e-01,  9.7990e-01,  6.2513e+00,  1.2059e+01,  2.9030e+00,  4.6579e+00},
          { 4.0671e+00,  4.9347e+00,  2.4911e+00,  1.7149e+00,  1.8962e+00, -5.6482e+00, -1.1448e+00,  9.0120e-01,  3.8540e-01,  1.2628e+00,  4.6826e-01,  3.2101e-01,  1.0946e+00,  5.1984e-01,  2.9681e+02,  1.6767e+02,  1.0000e+02,  4.1610e+01,  5.4279e+00,  1.5171e+00,  1.6931e+01,  4.2583e+01,  1.0411e+01,  2.6925e+00,  1.6902e+01,  2.4835e+01,  9.0985e+00,  1.5913e+00,  4.7024e+00,  8.9130e-01,  3.1581e-01,  5.8065e+00,  2.0641e+00,  6.1949e-01,  1.2085e+00, -4.8006e-01, -1.6491e-01,  5.9664e-01,  4.9684e-01,  2.7449e+00,  4.1315e+00,  1.4786e+00,  1.9230e+00},
          {-4.2515e+00,  5.2596e+00,  2.2922e+00,  2.3309e+00,  1.3766e+00, -2.1697e+00, -5.8795e-01,  8.1070e-01,  2.7435e-01, -1.1590e-01,  9.6828e-01,  8.2097e-02,  1.3521e+00,  4.1969e-01,  2.0691e+02,  1.1881e+02,  4.1610e+01,  8.1000e+01,  5.2398e+00,  1.5467e+00,  2.2042e+01,  2.3114e+01,  6.2298e+00,  1.9713e+00,  1.3713e+01,  2.1514e+01,  8.1476e+00,  2.0771e+00,  3.8588e+00,  6.0678e-01, -2.0756e+00,  6.5633e+00,  3.3925e+00,  3.5281e-02,  1.2696e+00,  1.3495e-01,  6.3774e-01,  4.0671e-01,  2.8039e-01,  2.5393e+00,  3.4521e+00,  1.7182e+00,  1.6585e+00},
          { 7.1028e-01,  1.1989e+00,  5.6868e-01,  3.9497e-01,  2.3942e-01,  1.8005e-01,  1.6535e-01,  7.8046e-02,  6.9971e-02,  1.6372e-01,  4.1645e-01,  1.1526e-01,  1.5576e-01,  4.0035e-02,  2.7859e+01,  1.5341e+01,  5.4279e+00,  5.2398e+00,  4.4100e+00,  1.9651e-01,  4.5005e-01,  1.0416e+00,  8.7058e-01,  2.8518e-01,  1.5048e+00,  2.5434e+00,  7.9852e-01,  2.1976e-01,  4.6963e-01,  1.2761e-01,  1.0070e-01,  8.0878e-01,  2.3760e-01,  1.1802e-01,  1.6937e-01,  7.8459e-01,  3.9218e-01,  1.1501e-01,  6.2402e-02,  6.1770e-01,  5.4940e-01,  1.8263e-01,  2.9390e-01},
          { 2.0509e+00,  6.1133e-01,  1.2082e-01,  1.5640e-01,  7.4910e-02,  4.9768e-01,  1.7777e-01,  4.3949e-02,  3.0019e-02,  5.8343e-02,  2.2781e-01,  7.9773e-02,  9.6410e-02,  6.7654e-02,  8.4370e+00,  4.4782e+00,  1.5171e+00,  1.5467e+00,  1.9651e-01,  6.4000e-01,  4.8556e+00,  5.3119e-01,  2.7441e-01,  1.4124e-01,  4.8558e-01,  5.6138e-01,  2.8009e-01,  1.2424e-01,  9.0728e-02,  9.7568e-02,  1.5378e+00,  5.3660e-01,  1.2181e-01,  5.5023e-02,  1.1277e-01,  2.5650e-01,  1.5688e-01,  3.2068e-02,  3.1100e-02,  1.7348e-01,  1.8917e-01,  1.5285e-01,  1.5232e-01},
          { 2.6071e+02,  4.1481e+01, -2.9585e+00,  1.9198e+00, -6.8635e-01,  6.7332e+01,  1.9015e+00, -6.3615e-01,  1.1392e-03, -3.0261e+00, -8.5710e+00,  5.7706e+00, -1.9481e+00,  1.4673e+00,  1.8458e+03,  1.1913e+02,  1.6931e+01,  2.2042e+01,  4.5005e-01,  4.8556e+00,  2.5000e+03,  1.4772e+02,  2.5012e+00, -1.7991e+00,  2.2354e+01, -4.7248e+01, -1.4209e+01,  1.6992e+00, -6.1162e+00,  2.0235e-01,  2.2574e+02,  3.6895e+01,  1.8955e+00,  2.0090e+00,  1.8541e+00,  5.9545e+01,  1.0413e+01, -2.0296e+00, -5.1804e-01,  2.3446e+00, -2.3941e+00, -3.2760e-02, -3.6326e-02},
          {-6.6211e+00, -1.0207e+00,  1.6030e+00,  5.5963e-01,  1.9000e+00, -6.1444e+00,  6.8173e+00,  1.9446e+00,  4.9908e-01,  1.0143e+01,  3.2814e+00,  2.8208e+00,  8.1416e-01,  9.1854e-01,  9.4238e+01,  1.5614e+02,  4.2583e+01,  2.3114e+01,  1.0416e+00,  5.3119e-01,  1.4772e+02,  3.6100e+02,  3.8370e+01,  9.9946e+00,  6.0231e+01,  4.1057e+01,  1.6746e+01,  1.9619e+00,  7.0267e+00,  9.0719e-01, -3.5439e+00,  7.7492e+00, -2.3276e+00,  2.8267e+00,  4.5874e-01, -3.4017e+00,  4.0688e+00,  2.7210e-01,  5.0158e-01,  6.3548e+00,  5.9930e+00,  6.5041e-01,  1.9458e+00},
          {-3.7499e+00,  1.6485e+00,  1.2869e+00,  4.8628e-01,  5.8752e-01,  9.0810e-01,  1.8162e+00,  4.6313e-01,  1.0929e-01,  1.4815e+00,  1.1783e+00,  8.6602e-01,  2.4981e-01,  3.0346e-01,  1.4466e+01,  3.5409e+01,  1.0411e+01,  6.2298e+00,  8.7058e-01,  2.7441e-01,  2.5012e+00,  3.8370e+01,  1.6000e+01,  1.7712e+00,  1.0931e+01,  9.6368e+00,  3.7317e+00,  5.8594e-01,  1.3844e+00,  4.1644e-01, -8.0819e-01,  6.4688e-01, -5.3162e-01,  6.2909e-01,  6.0632e-01,  1.1505e+00,  1.7252e+00,  2.1375e-01,  2.2518e-01,  1.7681e+00,  1.9527e+00,  2.8530e-01,  7.0448e-01},
          { 3.0125e+00,  7.8516e-01,  5.3165e-01,  1.7902e-01,  2.1058e-01,  1.3514e+00,  1.0566e+00,  1.6885e-01,  9.7196e-02,  6.9075e-01,  5.2895e-01,  2.2107e-01,  7.0318e-02,  6.7917e-02, -4.4821e+00,  6.2781e+00,  2.6925e+00,  1.9713e+00,  2.8518e-01,  1.4124e-01, -1.7991e+00,  9.9946e+00,  1.7712e+00,  3.6100e+00,  2.4592e+00,  2.0944e+00,  9.5872e-01,  3.2271e-01,  3.2513e-01,  1.4753e-01,  1.9861e+00,  7.6706e-01,  6.3632e-02,  2.3008e-01,  2.3661e-01,  3.2383e-01,  5.6001e-01,  1.2048e-01,  9.4764e-02,  6.1131e-01,  5.0485e-01,  1.5110e-01,  2.6016e-01},
          { 1.7092e+01,  3.3322e+00,  1.6283e+00,  9.8712e-01,  7.9898e-01,  2.8292e+00,  3.7926e+00,  7.3062e-01,  3.2982e-01,  4.8399e+00,  2.4315e+00,  1.6398e+00,  7.1410e-01,  3.8815e-01,  3.8754e+01,  5.5987e+01,  1.6902e+01,  1.3713e+01,  1.5048e+00,  4.8558e-01,  2.2354e+01,  6.0231e+01,  1.0931e+01,  2.4592e+00,  8.1000e+01,  1.8780e+01,  6.9856e+00,  1.4792e+00,  2.5201e+00,  5.3114e-01,  9.1238e+00,  1.5116e+00, -8.4289e-02,  6.6097e-01,  7.6373e-01,  2.2239e+00,  2.5471e+00,  4.9477e-01,  4.4874e-01,  4.3263e+00,  3.3296e+00,  7.3987e-01,  1.0464e+00},
          {-2.7973e+00,  6.5491e+00,  2.4070e+00,  1.5780e+00,  1.2588e+00,  4.7055e+00,  4.2963e+00,  5.4269e-01,  1.5757e-01,  3.7388e+00,  2.8908e+00,  8.8900e-01,  1.0406e+00,  3.7392e-01,  3.5633e+01,  8.9047e+01,  2.4835e+01,  2.1514e+01,  2.5434e+00,  5.6138e-01, -4.7248e+01,  4.1057e+01,  9.6368e+00,  2.0944e+00,  1.8780e+01,  6.4000e+01,  1.0271e+01,  2.4042e+00,  3.4157e+00,  5.3484e-01,  1.5706e-01,  2.2309e+00,  2.8013e+00,  1.0735e-01,  1.0780e+00,  2.1402e+00,  3.3844e+00,  2.4381e-01,  2.7390e-01,  2.2856e+00,  3.8227e+00,  1.0138e+00,  1.1777e+00},
          {-4.7666e+00,  1.2734e+00,  7.9849e-01,  5.5633e-01,  4.4745e-01,  2.8366e-01,  8.3932e-01,  2.9991e-01,  9.7814e-02,  8.7251e-01,  1.1384e+00,  1.2956e-01,  3.8318e-01,  1.2677e-01,  1.7274e+01,  2.9137e+01,  9.0985e+00,  8.1476e+00,  7.9852e-01,  2.8009e-01, -1.4209e+01,  1.6746e+01,  3.7317e+00,  9.5872e-01,  6.9856e+00,  1.0271e+01,  9.6100e+00,  8.0568e-01,  1.4519e+00,  2.4676e-01, -6.2743e-01,  1.0760e+00,  8.2945e-01,  9.4290e-02,  4.0362e-01,  7.7229e-01,  8.9079e-01,  1.3371e-01,  1.3768e-01,  1.1202e+00,  1.3220e+00,  4.0675e-01,  5.4409e-01},
          { 1.6714e+00,  9.5815e-01,  3.5641e-01,  2.0495e-01,  1.2185e-01,  1.2113e+00,  7.1006e-01,  6.5646e-02,  2.7184e-02,  2.6459e-01,  5.6131e-01,  1.8999e-01,  1.1485e-01,  4.3292e-02,  2.3031e+00,  4.9493e+00,  1.5913e+00,  2.0771e+00,  2.1976e-01,  1.2424e-01,  1.6992e+00,  1.9619e+00,  5.8594e-01,  3.2271e-01,  1.4792e+00,  2.4042e+00,  8.0568e-01,  1.6900e+00,  2.9438e-01,  1.0022e-01,  1.4553e+00,  4.0649e-01,  3.3912e-01,  4.2927e-02,  2.1204e-01,  7.5751e-01,  5.5452e-01,  5.8255e-03,  4.1462e-02,  2.7855e-01,  4.1744e-01,  1.5886e-01,  1.6229e-01},
          {-1.4996e+00,  3.5404e-01,  9.9049e-02,  1.9666e-01,  1.8619e-01, -6.5010e-01,  3.8325e-02,  1.5600e-01,  3.6078e-02,  4.2605e-01,  2.2034e-01, -6.8243e-02,  1.9355e-01,  9.5821e-02,  1.3597e+01,  1.4577e+01,  4.7024e+00,  3.8588e+00,  4.6963e-01,  9.0728e-02, -6.1162e+00,  7.0267e+00,  1.3844e+00,  3.2513e-01,  2.5201e+00,  3.4157e+00,  1.4519e+00,  2.9438e-01,  2.5600e+00,  1.0750e-01, -1.2053e+00,  3.1343e-01,  3.6897e-01,  1.1258e-01,  1.6682e-01, -4.5617e-01,  1.6730e-01,  8.7648e-02,  7.6998e-02,  2.4151e-01,  6.0826e-01,  1.9550e-01,  2.5619e-01},
          { 1.1487e+00,  3.8064e-01,  1.9898e-01,  9.3695e-02,  5.2550e-02,  3.4343e-01,  3.9540e-01,  4.4460e-02,  2.0128e-02,  1.2583e-01,  2.2024e-01,  5.9174e-02,  6.3640e-02,  5.5184e-02,  2.7518e+00,  2.2047e+00,  8.9130e-01,  6.0678e-01,  1.2761e-01,  9.7568e-02,  2.0235e-01,  9.0719e-01,  4.1644e-01,  1.4753e-01,  5.3114e-01,  5.3484e-01,  2.4676e-01,  1.0022e-01,  1.0750e-01,  2.5000e-01,  9.9015e-01,  2.5707e-01,  7.1657e-02,  5.2164e-02,  9.4440e-02,  1.0359e-01,  1.4311e-01,  3.9242e-02,  4.1460e-02,  1.8007e-01,  1.6800e-01,  8.5745e-02,  1.1555e-01},
          { 1.3766e+02,  2.2005e+01,  4.0006e+00,  7.1858e-01,  9.4384e-01,  4.1642e+01,  1.4385e+01,  1.8294e-01,  5.5054e-01,  4.3390e+00,  8.1290e+00,  2.7498e+00,  6.6732e-01,  6.5750e-01,  2.3329e+02,  1.9018e+00,  3.1581e-01, -2.0756e+00,  1.0070e-01,  1.5378e+00,  2.2574e+02, -3.5439e+00, -8.0819e-01,  1.9861e+00,  9.1238e+00,  1.5706e-01, -6.2743e-01,  1.4553e+00, -1.2053e+00,  9.9015e-01,  1.9600e+02,  1.3670e+01,  8.6566e-01,  1.0878e+00,  2.3706e+00,  1.3845e+01,  7.2287e+00,  5.0124e-01,  6.3034e-01,  2.3559e+00,  1.4205e+00,  6.8772e-01,  7.8590e-01},
          { 2.2202e+01,  4.8093e+00,  9.6517e-01,  3.6304e-01,  4.8533e-01,  4.6860e+00,  3.0882e+00,  2.2786e-01,  1.3416e-01,  8.4857e-01,  2.0070e+00,  4.0277e-01,  5.1636e-01,  2.1968e-01,  6.6269e+01,  1.6827e+01,  5.8065e+00,  6.5633e+00,  8.0878e-01,  5.3660e-01,  3.6895e+01,  7.7492e+00,  6.4688e-01,  7.6706e-01,  1.5116e+00,  2.2309e+00,  1.0760e+00,  4.0649e-01,  3.1343e-01,  2.5707e-01,  1.3670e+01,  2.5000e+01,  5.5237e-01,  4.6176e-01,  5.9445e-01,  1.9823e+00,  1.3156e+00,  2.3877e-01,  1.8823e-01,  3.7456e-01,  7.6012e-01,  4.0086e-01,  4.2860e-01},
          { 2.8447e+00,  1.5380e+00,  2.8769e-01,  2.7414e-01,  4.6023e-02,  8.4209e-01,  7.9414e-01, -7.6554e-03,  3.8647e-02,  3.0650e-01,  5.1339e-01, -1.1485e-03,  1.6455e-01,  6.5015e-03,  5.6970e+00,  5.3241e+00,  2.0641e+00,  3.3925e+00,  2.3760e-01,  1.2181e-01,  1.8955e+00, -2.3276e+00, -5.3162e-01,  6.3632e-02, -8.4289e-02,  2.8013e+00,  8.2945e-01,  3.3912e-01,  3.6897e-01,  7.1657e-02,  8.6566e-01,  5.5237e-01,  6.7600e+00, -5.5723e-02,  1.5700e-01,  2.2724e-01,  2.7943e-01,  2.1267e-02,  5.7560e-03, -4.5405e-02,  2.3508e-01,  1.2512e-01,  9.3558e-02},
          { 1.7565e+00,  2.0269e-01,  1.0002e-01,  1.0525e-02,  4.2824e-02,  3.7003e-01,  3.9126e-01,  6.7397e-02,  2.2951e-02,  1.7859e-01,  1.6424e-01,  7.9137e-02,  2.9405e-02,  2.9439e-02,  1.4390e+00,  5.9709e-01,  6.1949e-01,  3.5281e-02,  1.1802e-01,  5.5023e-02,  2.0090e+00,  2.8267e+00,  6.2909e-01,  2.3008e-01,  6.6097e-01,  1.0735e-01,  9.4290e-02,  4.2927e-02,  1.1258e-01,  5.2164e-02,  1.0878e+00,  4.6176e-01, -5.5723e-02,  6.4000e-01,  9.3680e-02, -4.0104e-02,  1.5423e-01,  8.1099e-02,  4.3075e-02,  1.7384e-01,  1.1908e-01,  2.4450e-02,  9.6698e-02},
          { 2.6699e+00,  1.0693e+00,  2.3910e-01,  1.7454e-01,  8.3210e-02,  1.5590e+00,  6.7252e-01,  6.1890e-02,  4.8080e-02,  3.0453e-01,  4.6285e-01,  1.8644e-01,  1.1824e-01,  4.9744e-02,  4.2256e+00,  2.8678e+00,  1.2085e+00,  1.2696e+00,  1.6937e-01,  1.1277e-01,  1.8541e+00,  4.5874e-01,  6.0632e-01,  2.3661e-01,  7.6373e-01,  1.0780e+00,  4.0362e-01,  2.1204e-01,  1.6682e-01,  9.4440e-02,  2.3706e+00,  5.9445e-01,  1.5700e-01,  9.3680e-02,  1.0000e+00,  8.9410e-01,  5.0398e-01,  6.8053e-02,  5.2568e-02,  1.6453e-01,  4.3283e-01,  1.0046e-01,  1.5118e-01},
          { 1.1240e+01,  8.3730e+00,  1.5230e+00,  7.1960e-01,  1.0399e-02,  1.2756e+01,  3.1692e+00, -5.0352e-03,  7.4082e-02, -2.0476e-01,  1.6312e+00,  1.2699e+00,  7.7100e-02,  1.2376e-01,  2.9615e+01, -2.5768e+00, -4.8006e-01,  1.3495e-01,  7.8459e-01,  2.5650e-01,  5.9545e+01, -3.4017e+00,  1.1505e+00,  3.2383e-01,  2.2239e+00,  2.1402e+00,  7.7229e-01,  7.5751e-01, -4.5617e-01,  1.0359e-01,  1.3845e+01,  1.9823e+00,  2.2724e-01, -4.0104e-02,  8.9410e-01,  2.5000e+01,  3.3571e+00,  1.5453e-02,  2.9858e-02,  6.1999e-01,  1.5555e+00, -3.4796e-03,  2.1590e-01},
          { 5.2180e+00,  3.3454e+00,  9.8900e-01,  3.8851e-01,  1.0255e-01,  6.4295e+00,  2.7651e+00,  1.4874e-01,  6.6765e-02,  6.2314e-01,  1.5606e+00,  6.6298e-01,  1.6023e-01,  1.0305e-01, -6.6318e+00,  9.8549e-01, -1.6491e-01,  6.3774e-01,  3.9218e-01,  1.5688e-01,  1.0413e+01,  4.0688e+00,  1.7252e+00,  5.6001e-01,  2.5471e+00,  3.3844e+00,  8.9079e-01,  5.5452e-01,  1.6730e-01,  1.4311e-01,  7.2287e+00,  1.3156e+00,  2.7943e-01,  1.5423e-01,  5.0398e-01,  3.3571e+00,  5.7600e+00,  3.8297e-02,  9.7373e-02,  9.2241e-01,  9.1164e-01,  2.2538e-01,  3.3873e-01},
          { 1.2450e+00,  1.3986e-01,  1.0219e-01,  3.9256e-02,  4.5478e-02,  3.6502e-01,  1.5879e-01,  4.7158e-02,  1.3136e-02,  2.2552e-01,  1.7341e-01,  3.4984e-02,  2.6414e-02,  2.6260e-02,  2.5231e-01,  8.2048e-01,  5.9664e-01,  4.0671e-01,  1.1501e-01,  3.2068e-02, -2.0296e+00,  2.7210e-01,  2.1375e-01,  1.2048e-01,  4.9477e-01,  2.4381e-01,  1.3371e-01,  5.8255e-03,  8.7648e-02,  3.9242e-02,  5.0124e-01,  2.3877e-01,  2.1267e-02,  8.1099e-02,  6.8053e-02,  1.5453e-02,  3.8297e-02,  4.9000e-01,  3.3258e-02,  1.8262e-01,  1.8334e-01,  5.9240e-02,  9.4332e-02},
          { 1.1831e+00,  2.6837e-01,  1.1135e-01,  4.6016e-02,  4.6944e-02,  2.5506e-01,  1.6642e-01,  4.0267e-02,  1.8970e-02,  9.6665e-02,  8.6075e-02,  4.1921e-02,  3.5130e-02,  2.3274e-02,  5.7814e-01,  9.7990e-01,  4.9684e-01,  2.8039e-01,  6.2402e-02,  3.1100e-02, -5.1804e-01,  5.0158e-01,  2.2518e-01,  9.4764e-02,  4.4874e-01,  2.7390e-01,  1.3768e-01,  4.1462e-02,  7.6998e-02,  4.1460e-02,  6.3034e-01,  1.8823e-01,  5.7560e-03,  4.3075e-02,  5.2568e-02,  2.9858e-02,  9.7373e-02,  3.3258e-02,  1.6000e-01,  8.7330e-02,  1.0757e-01,  4.2996e-02,  7.2787e-02},
          { 3.4058e+00,  1.0371e+00,  5.9310e-01,  3.3178e-01,  9.1685e-02,  1.1323e+00,  9.1489e-01,  2.0249e-01,  1.2098e-01,  8.2750e-01,  7.8052e-01,  3.9735e-01,  1.0529e-01,  7.6012e-02, -6.9223e-01,  6.2513e+00,  2.7449e+00,  2.5393e+00,  6.1770e-01,  1.7348e-01,  2.3446e+00,  6.3548e+00,  1.7681e+00,  6.1131e-01,  4.3263e+00,  2.2856e+00,  1.1202e+00,  2.7855e-01,  2.4151e-01,  1.8007e-01,  2.3559e+00,  3.7456e-01, -4.5405e-02,  1.7384e-01,  1.6453e-01,  6.1999e-01,  9.2241e-01,  1.8262e-01,  8.7330e-02,  5.7600e+00,  8.2278e-01,  2.3154e-01,  3.9348e-01},
          { 6.4227e-01,  1.9110e+00,  6.2689e-01,  3.6017e-01,  2.0265e-01,  2.1964e+00,  1.0167e+00,  1.9574e-01,  4.2794e-02,  2.7869e-01,  9.5679e-01,  3.8611e-01,  1.5928e-01,  8.1280e-02,  4.9388e+00,  1.2059e+01,  4.1315e+00,  3.4521e+00,  5.4940e-01,  1.8917e-01, -2.3941e+00,  5.9930e+00,  1.9527e+00,  5.0485e-01,  3.3296e+00,  3.8227e+00,  1.3220e+00,  4.1744e-01,  6.0826e-01,  1.6800e-01,  1.4205e+00,  7.6012e-01,  2.3508e-01,  1.1908e-01,  4.3283e-01,  1.5555e+00,  9.1164e-01,  1.8334e-01,  1.0757e-01,  8.2278e-01,  4.4100e+00,  2.1876e-01,  3.1102e-01},
          { 2.0901e+00,  5.4878e-01,  1.5209e-01,  1.5356e-01,  5.6981e-02,  4.0173e-01,  4.2596e-01,  5.8532e-02,  3.5611e-02,  9.5460e-02,  2.3112e-01,  4.8733e-02,  9.7632e-02,  6.1360e-02,  4.1682e+00,  2.9030e+00,  1.4786e+00,  1.7182e+00,  1.8263e-01,  1.5285e-01, -3.2760e-02,  6.5041e-01,  2.8530e-01,  1.5110e-01,  7.3987e-01,  1.0138e+00,  4.0675e-01,  1.5886e-01,  1.9550e-01,  8.5745e-02,  6.8772e-01,  4.0086e-01,  1.2512e-01,  2.4450e-02,  1.0046e-01, -3.4796e-03,  2.2538e-01,  5.9240e-02,  4.2996e-02,  2.3154e-01,  2.1876e-01,  1.0000e+00,  1.7952e-01},
          { 1.0565e+00,  5.8637e-01,  2.6641e-01,  1.8912e-01,  8.2416e-02,  2.8149e-01,  3.4883e-01,  1.0308e-01,  5.0666e-02,  2.4918e-01,  3.5318e-01,  8.6654e-02,  1.1649e-01,  8.3149e-02,  3.6467e+00,  4.6579e+00,  1.9230e+00,  1.6585e+00,  2.9390e-01,  1.5232e-01, -3.6326e-02,  1.9458e+00,  7.0448e-01,  2.6016e-01,  1.0464e+00,  1.1777e+00,  5.4409e-01,  1.6229e-01,  2.5619e-01,  1.1555e-01,  7.8590e-01,  4.2860e-01,  9.3558e-02,  9.6698e-02,  1.5118e-01,  2.1590e-01,  3.3873e-01,  9.4332e-02,  7.2787e-02,  3.9348e-01,  3.1102e-01,  1.7952e-01,  6.4000e-01},
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

        add_result(SignalRegionData(_counters.at("SR01"), 166., {175., 20.}));
        add_result(SignalRegionData(_counters.at("SR02"), 23., {27., 4.}));
        add_result(SignalRegionData(_counters.at("SR03"), 6., {5., 1.}));
        add_result(SignalRegionData(_counters.at("SR04"), 1., {2.5, 0.8}));
        add_result(SignalRegionData(_counters.at("SR05"), 56., {50., 8.}));
        add_result(SignalRegionData(_counters.at("SR06"), 13., {12., 3.}));
        add_result(SignalRegionData(_counters.at("SR07"), 1., {1.2, 0.4}));
        add_result(SignalRegionData(_counters.at("SR08"), 13., {12., 2.}));
        add_result(SignalRegionData(_counters.at("SR09"), 14., {11., 3.}));
        add_result(SignalRegionData(_counters.at("SR10"), 2., {2.6, 0.9}));
        add_result(SignalRegionData(_counters.at("SR11"), 1., {1.2, 0.5}));
        add_result(SignalRegionData(_counters.at("SR12"), 41., {39., 6.}));
        add_result(SignalRegionData(_counters.at("SR13"), 13., {10., 3.}));
        add_result(SignalRegionData(_counters.at("SR14"), 11., {6., 2.}));
        add_result(SignalRegionData(_counters.at("SR15"), 260., {286., 44.}));
        add_result(SignalRegionData(_counters.at("SR16"), 51., {62., 14.}));
        add_result(SignalRegionData(_counters.at("SR17"), 10., {20., 5.}));
        add_result(SignalRegionData(_counters.at("SR18"), 9., {16., 4.}));
        add_result(SignalRegionData(_counters.at("SR19"), 297., {321., 42.}));
        add_result(SignalRegionData(_counters.at("SR20"), 38., {50., 14.}));
        add_result(SignalRegionData(_counters.at("SR21"), 2., {5., 2.}));
        add_result(SignalRegionData(_counters.at("SR22"), 2., {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("SR23"), 18., {25., 6.}));
        add_result(SignalRegionData(_counters.at("SR24"), 13., {12., 5.}));
        add_result(SignalRegionData(_counters.at("SR25"), 5., {5., 2.}));
        add_result(SignalRegionData(_counters.at("SR26"), 2., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR27"), 250., {279., 34.}));
        add_result(SignalRegionData(_counters.at("SR28"), 81., {87., 13.}));
        add_result(SignalRegionData(_counters.at("SR29"), 20., {26., 6.}));
        add_result(SignalRegionData(_counters.at("SR30"), 10., {8., 2.}));
        add_result(SignalRegionData(_counters.at("SR31"), 5., {6., 1.}));
        add_result(SignalRegionData(_counters.at("SR32"), 49., {54., 8.}));
        add_result(SignalRegionData(_counters.at("SR33"), 11., {11., 3.}));
        add_result(SignalRegionData(_counters.at("SR34"), 2., {2.2, 0.9}));
        add_result(SignalRegionData(_counters.at("SR35"), 2., {0.5, 0.4}));
        add_result(SignalRegionData(_counters.at("SR36"), 5., {6., 2.}));
        add_result(SignalRegionData(_counters.at("SR37"), 2., {3.0, 1.3}));
        add_result(SignalRegionData(_counters.at("SR38"), 0., {1.1, 0.4}));
        add_result(SignalRegionData(_counters.at("SR39"), 3., {0.9, 0.4}));
        add_result(SignalRegionData(_counters.at("SR40"), 292., {310., 40.}));
        add_result(SignalRegionData(_counters.at("SR41"), 69., {81., 18.}));
        add_result(SignalRegionData(_counters.at("SR42"), 23., {25., 6.}));
        add_result(SignalRegionData(_counters.at("SR43"), 8., {13., 3.}));
        add_result(SignalRegionData(_counters.at("SR44"), 45., {45., 6.}));
        add_result(SignalRegionData(_counters.at("SR45"), 12., {14., 3.}));
        add_result(SignalRegionData(_counters.at("SR46"), 5., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR47"), 1., {1.9, 0.8}));
        add_result(SignalRegionData(_counters.at("SR48"), 2., {1.8, 0.8}));
        add_result(SignalRegionData(_counters.at("SR49"), 1., {1.0, 0.5}));
        add_result(SignalRegionData(_counters.at("SR50"), 12., {9., 3.}));
        add_result(SignalRegionData(_counters.at("SR51"), 2., {4., 2.}));
        add_result(SignalRegionData(_counters.at("SR52"), 2., {2.0, 0.7}));
        add_result(SignalRegionData(_counters.at("SR53"), 2., {1.5, 0.7}));
        add_result(SignalRegionData(_counters.at("SR54"), 1., {0.6, 0.3}));
        add_result(SignalRegionData(_counters.at("SR55"), 1., {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("SR56"), 170., {173., 21.}));
        add_result(SignalRegionData(_counters.at("SR57"), 28., {44., 7.}));
        add_result(SignalRegionData(_counters.at("SR58"), 12., {23., 6.}));

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 4.0000e+02,  1.3794e+01,  1.3360e+00,  2.7494e-01,  5.0560e+01,  1.5766e+01, -3.5831e-01,  5.1800e+00,  1.0689e+01,  8.7001e-01,  4.8201e-01,  1.8628e+01,  6.3414e+00,  4.7160e+00,  5.0329e+01, -3.4163e+01, -6.0535e+00, -5.8740e+00,  1.9491e+02,  1.1548e+01, -1.6408e+00,  7.4316e-01,  6.4866e+00, -6.2086e+00, -1.8616e+00, -4.5660e+00,  1.6077e+02,  1.1954e+00, -1.1702e+01,  7.1868e-01, -1.2237e+00,  3.0163e+01,  1.8019e+00,  3.3410e-01,  8.4752e-01, -6.8048e-01, -3.2115e-01,  2.8435e-01,  6.9055e-01,  3.4288e+01, -6.4249e+01, -1.4508e+01, -8.1048e+00,  1.0030e+01, -1.3999e-01,  5.9364e-01, -3.1859e-01,  1.9893e+00,  1.5947e-01, -1.7338e+00,  1.0700e+00,  6.2759e-01,  7.4728e-01,  1.8606e-01, -8.1154e-02,  1.1833e+02,  4.8905e+00, -5.9351e+00},
          { 1.3794e+01,  1.6000e+01,  3.6897e-01,  2.9837e-01,  7.7338e+00,  2.2488e+00,  6.8632e-03, -4.9868e-02,  1.6530e+00,  6.4663e-01,  3.1084e-01,  4.1230e+00,  2.2390e+00,  6.3822e-01,  3.2842e+00, -8.7063e-01,  7.5934e-01,  1.5774e+00,  1.6150e+01,  1.5643e+00,  7.4146e-01,  1.9076e-01,  1.4916e+00,  2.3292e+00,  4.2511e-01,  9.5936e-02,  1.6323e+01,  1.9234e+00, -5.3018e-01,  9.6960e-01,  7.6300e-02,  6.4909e+00, -6.2102e-02,  3.1071e-01,  2.0458e-01,  8.0400e-01, -3.2421e-02,  1.9523e-02,  1.3234e-01,  4.4347e+00, -7.5506e-01,  6.9434e-01, -4.2827e-01, -7.4489e-02,  7.7324e-01,  7.6373e-01, -3.9990e-02,  2.1823e-01,  2.3266e-01,  2.7584e-01,  3.8442e-01,  3.3569e-01,  3.0167e-01,  9.6467e-02,  1.5209e-01,  2.1285e+01,  5.4594e+00,  1.8844e+00},
          { 1.3360e+00,  3.6897e-01,  1.0000e+00,  5.9355e-02,  1.0594e+00,  2.7147e-01,  1.7412e-02,  5.7704e-02,  2.5843e-01,  8.5920e-02,  3.5771e-02,  5.3827e-01,  2.8392e-01,  2.1510e-01,  5.3117e-01,  1.1130e+00,  3.0771e-01,  2.5008e-01, -1.6178e+00,  1.0032e+00,  1.9140e-01,  2.1266e-02,  3.5668e-01,  6.6120e-01,  1.7221e-01,  8.1010e-02,  6.0493e-01, -5.3426e-02,  1.8377e-01,  1.6604e-01,  2.7915e-02,  1.7462e-01,  1.9310e-01,  5.8797e-02,  3.4158e-02,  2.1526e-02,  9.7005e-02,  2.3852e-02,  1.6044e-02, -2.0234e-01,  2.3537e-01,  3.1375e-01,  6.7338e-03, -5.1325e-01,  1.3286e-01,  1.4098e-01,  3.8597e-02,  3.2446e-02,  3.2806e-02,  5.2245e-02,  9.1466e-02,  5.3024e-02,  1.3167e-02,  1.5586e-02,  3.4236e-02,  3.6964e+00,  7.0119e-01,  1.8055e-01},
          { 2.7494e-01,  2.9837e-01,  5.9355e-02,  6.4000e-01,  3.7692e-01,  2.5622e-01,  6.8752e-03, -5.0240e-02,  1.2832e-01,  8.8452e-02,  6.6404e-02,  1.9447e-01, -4.5043e-03,  7.1304e-02, -1.0328e+00,  4.2650e-01,  5.4176e-01,  5.6208e-01,  2.0747e-01,  9.9053e-01,  6.3875e-02,  5.2456e-02,  3.6557e-01,  5.1252e-01,  1.3530e-01,  1.7802e-01,  1.0260e+00, -5.3040e-01,  4.3211e-01,  1.9170e-01,  1.8301e-02,  1.4073e-01,  1.3812e-01,  1.1492e-01,  2.8151e-02,  2.0472e-01, -2.9079e-02,  1.8826e-02,  2.2926e-02, -1.2483e+00,  4.6634e-01,  6.5261e-01,  8.7941e-02, -5.1888e-01,  2.8104e-01,  2.9787e-01,  2.8181e-02,  2.1355e-02,  6.2684e-02,  2.4336e-04,  1.7864e-01,  5.7574e-02,  4.2592e-02,  3.5491e-02,  6.5536e-02,  2.1077e+00,  4.8013e-01,  5.2531e-01},
          { 5.0560e+01,  7.7338e+00,  1.0594e+00,  3.7692e-01,  6.4000e+01,  5.5735e+00, -2.0669e-01,  1.2235e+00,  5.5735e+00,  1.0485e+00,  2.7418e-01,  7.7851e+00,  5.0074e+00,  1.8664e+00, -1.3382e+01, -1.5840e+01, -3.2510e+00, -1.5036e+00,  4.6973e+01, -2.0051e+00,  5.8261e-01,  1.9291e-01,  2.8119e+00, -2.1509e-01, -1.4388e-01, -1.4491e+00,  3.0712e+01,  4.7026e-01, -6.8602e+00,  1.0433e+00, -2.9719e-01,  1.4751e+01, -5.7360e-01, -2.7325e-02,  3.6144e-01, -2.3789e-01,  4.0743e-01, -5.2691e-02,  3.8691e-01, -9.2022e+00, -2.5047e+01, -5.9750e+00, -3.6156e+00,  1.0591e+00, -1.1069e+00,  6.9205e-02, -2.2302e-01,  3.5300e-01,  2.0181e-01, -7.9392e-01,  2.9992e-01,  5.2470e-01,  4.7160e-01,  6.2436e-02,  3.2349e-02,  5.0472e+01,  1.1472e+01, -2.5530e-01},
          { 1.5766e+01,  2.2488e+00,  2.7147e-01,  2.5622e-01,  5.5735e+00,  9.0000e+00, -3.9830e-02,  4.6367e-01,  1.6897e+00,  3.0964e-01,  2.4350e-01,  3.7136e+00,  1.5876e+00,  1.2527e+00, -2.4911e+01, -6.2786e+00, -6.1464e-01,  1.8604e-01, -3.3927e-01,  5.6024e+00,  2.0943e-01,  1.8924e-01,  7.2290e-01,  1.0685e+00,  3.0721e-01, -3.0737e-01,  4.5976e+00, -5.2209e+00, -7.7132e-03,  1.8915e-01, -1.2869e-01,  2.4295e+00,  8.5403e-01,  3.1309e-01,  2.1361e-01,  2.6843e-01,  8.4689e-02,  1.1080e-01,  1.5304e-01, -1.0303e+00, -4.2790e+00,  5.3339e-01, -1.9677e-01, -2.8017e-01,  1.3493e+00,  9.4326e-01,  1.6781e-01,  2.9249e-01,  2.4534e-01,  4.8036e-01,  6.4254e-01,  2.2329e-01,  1.8136e-01,  1.0057e-01,  1.7125e-01,  1.6375e+01,  1.6862e+00,  1.2828e+00},
          {-3.5831e-01,  6.8632e-03,  1.7412e-02,  6.8752e-03, -2.0669e-01, -3.9830e-02,  1.6000e-01,  8.1120e-02,  1.7222e-02,  2.6531e-02,  1.0698e-02, -3.9425e-02,  4.4254e-02, -5.5219e-04, -6.3737e-01,  6.7217e-01,  7.8808e-02,  5.4376e-02, -3.7096e-01,  1.4991e+00,  1.3246e-01,  1.4099e-02,  2.8039e-01,  2.3418e-01,  1.3814e-01,  1.0743e-01, -1.1670e+00, -1.3493e-01,  3.8054e-01,  4.3122e-02,  4.9360e-02,  1.2999e-02,  2.1522e-01,  4.3535e-02,  1.0558e-02,  1.6223e-02,  8.9326e-02,  1.6827e-02,  1.0419e-02,  2.4827e-01,  9.3593e-01,  3.4937e-01,  9.4288e-02,  1.0586e-01,  1.0454e-01,  1.6593e-01,  4.7302e-02,  4.7731e-03,  1.7320e-02,  9.7246e-02,  6.5817e-02,  1.9391e-02,  9.5959e-03,  1.0994e-02,  1.6326e-02,  4.2150e-01,  3.5258e-01,  3.9758e-01},
          { 5.1800e+00, -4.9868e-02,  5.7704e-02, -5.0240e-02,  1.2235e+00,  4.6367e-01,  8.1120e-02,  4.0000e+00,  3.3173e-01,  9.7709e-03, -1.6018e-02,  5.5390e-01,  6.3516e-01,  2.8679e-01, -9.4767e-02,  1.3110e+00, -4.6568e-01, -5.3508e-01,  2.5258e+00,  4.6936e+00,  4.1060e-01, -1.0730e-03,  1.5817e+00,  2.2105e-01,  3.0402e-01,  8.6424e-02, -5.6898e+00,  3.6808e-01,  3.1536e-01,  1.8338e-02,  1.1940e-01,  3.9653e-01,  6.4350e-01,  3.6329e-02,  8.4104e-03, -3.4982e-01,  4.6233e-01,  5.3734e-02,  4.1647e-02, -8.2688e-01,  1.1356e+00, -1.5041e-01, -8.2338e-02,  6.7727e-01,  1.0082e-02,  7.2844e-02,  2.0237e-01,  7.8528e-02,  9.8002e-04,  1.5778e-01,  1.2044e-01,  1.8669e-02,  2.0451e-03,  6.0942e-03, -2.7258e-02,  4.9808e+00,  1.8092e+00,  4.2982e-01},
          { 1.0689e+01,  1.6530e+00,  2.5843e-01,  1.2832e-01,  5.5735e+00,  1.6897e+00,  1.7222e-02,  3.3173e-01,  9.0000e+00,  3.6701e-01,  1.7583e-01,  2.6446e+00,  1.5043e+00,  9.7098e-01, -1.0131e+01, -2.1284e+00,  4.3006e-01,  5.7227e-01, -7.3069e+00,  1.7620e+00,  4.3648e-01,  1.6678e-01,  1.4936e+00,  1.5756e+00,  3.8432e-01,  3.8318e-01,  2.0970e+00, -2.3749e+00,  8.7205e-02,  5.6327e-01, -1.5615e-02,  1.7709e+00,  2.3434e-01,  2.6249e-01,  1.1328e-01,  1.3851e-01,  1.8338e-01,  8.2480e-02,  1.0461e-01, -1.3400e+00, -2.1220e+00,  1.0206e+00, -1.9186e-01, -9.6622e-01,  4.8300e-01,  6.6858e-01,  3.7037e-02,  2.3627e-01,  2.0136e-01,  3.9741e-01,  3.8404e-01,  3.0246e-01,  7.1406e-02,  5.2653e-02,  1.3980e-01,  1.9787e+01,  3.7174e+00,  1.0299e+00},
          { 8.7001e-01,  6.4663e-01,  8.5920e-02,  8.8452e-02,  1.0485e+00,  3.0964e-01,  2.6531e-02,  9.7709e-03,  3.6701e-01,  8.1000e-01,  6.8814e-02,  6.7046e-01,  4.3654e-01,  1.3528e-01, -3.6596e+00,  6.5061e-01,  1.2488e-01,  2.4977e-01,  5.8560e-01,  2.6090e+00,  3.9463e-01,  4.9851e-02,  8.1437e-01,  8.4996e-01,  2.0299e-01,  8.3866e-02,  1.8904e+00, -8.1092e-01,  4.5396e-01,  2.2482e-01,  5.5812e-02,  1.2123e+00,  3.2467e-01,  1.3634e-01,  4.3009e-02,  1.7174e-01,  1.3905e-01,  2.9048e-02,  3.6461e-02, -2.3246e-01,  1.3881e-01,  7.9904e-01,  1.2155e-01, -2.7779e-01,  3.9663e-01,  3.6023e-01,  4.5474e-02,  4.4423e-02,  8.1922e-02,  2.6863e-01,  1.6517e-01,  1.1674e-01,  7.7988e-02,  4.3457e-02,  6.9160e-02,  3.9476e+00,  1.6136e+00,  7.9169e-01},
          { 4.8201e-01,  3.1084e-01,  3.5771e-02,  6.6404e-02,  2.7418e-01,  2.4350e-01,  1.0698e-02, -1.6018e-02,  1.7583e-01,  6.8814e-02,  2.5000e-01,  3.1062e-01,  6.4033e-02,  1.2455e-01, -2.9165e+00, -2.5942e-01,  2.9975e-01,  4.0790e-01,  5.0866e-02,  1.0296e+00,  1.1563e-01,  5.0662e-02,  1.2806e-01,  3.5110e-01,  1.2117e-01,  1.0689e-01,  8.5012e-01, -8.4298e-01,  3.5799e-01,  1.4826e-01,  2.4772e-02,  7.3620e-02,  1.6118e-01,  1.0373e-01,  3.2928e-02,  1.8438e-01, -1.0197e-02,  1.8553e-02,  2.0582e-02, -2.1516e-01,  2.5548e-01,  5.1123e-01,  1.3830e-01, -1.3100e-01,  3.0804e-01,  2.9706e-01,  2.5822e-02,  4.8888e-02,  6.2628e-02,  6.0171e-02,  1.7807e-01,  5.1215e-02,  2.5891e-02,  4.1385e-02,  7.9098e-02,  1.8399e+00,  8.9187e-02,  4.3476e-01},
          { 1.8628e+01,  4.1230e+00,  5.3827e-01,  1.9447e-01,  7.7851e+00,  3.7136e+00, -3.9425e-02,  5.5390e-01,  2.6446e+00,  6.7046e-01,  3.1062e-01,  3.6000e+01,  3.5829e+00,  3.2182e+00, -4.2327e+01, -8.5252e+00,  1.6425e-02,  5.2183e-01, -2.4359e+01,  1.3227e+00,  6.1262e-01,  4.0152e-01,  1.0863e+00,  2.2588e+00,  1.1340e-01, -5.6752e-01,  1.7237e+01, -1.6164e+00,  1.1087e+00,  1.4498e+00, -1.6349e-01,  5.9016e+00,  1.9332e+00,  6.3855e-01,  2.3779e-01,  1.2749e+00,  3.7412e-01,  2.7007e-01,  1.4535e-01,  6.7061e+01,  2.3624e+01,  8.3992e+00,  3.2359e+00,  5.8028e+00,  3.7411e+00,  1.6261e+00,  3.0316e-01,  6.9235e-01,  3.8358e-01,  4.3387e+00,  1.8202e+00,  8.6419e-01,  4.4247e-01,  1.4663e-01,  3.8166e-01,  3.6278e+01,  6.9917e+00,  3.6857e+00},
          { 6.3414e+00,  2.2390e+00,  2.8392e-01, -4.5043e-03,  5.0074e+00,  1.5876e+00,  4.4254e-02,  6.3516e-01,  1.5043e+00,  4.3654e-01,  6.4033e-02,  3.5829e+00,  9.0000e+00,  8.4060e-01, -2.0828e+01, -1.8338e+00, -8.7707e-01, -6.6149e-01, -6.1958e+00,  3.5152e+00,  9.1074e-01,  2.7889e-02,  1.4579e+00,  1.2507e+00,  3.3923e-01, -1.5772e-01, -2.3046e+00, -8.3659e-01, -9.0329e-01,  1.7681e-01, -1.2923e-01,  4.5286e+00,  7.1723e-01,  9.3034e-02,  1.3888e-01, -3.9663e-02,  5.0302e-01,  5.1848e-02,  9.3854e-02,  7.1388e+00,  2.5378e+00,  1.2905e+00,  3.6207e-01,  1.1886e+00,  7.8252e-01,  5.1325e-01,  1.4631e-01,  2.2748e-01,  8.0781e-02,  9.9675e-01,  5.8043e-01,  3.3382e-01,  2.1309e-01,  5.0704e-02,  1.0392e-01,  1.3548e+01,  5.2002e+00,  1.4053e+00},
          { 4.7160e+00,  6.3822e-01,  2.1510e-01,  7.1304e-02,  1.8664e+00,  1.2527e+00, -5.5219e-04,  2.8679e-01,  9.7098e-01,  1.3528e-01,  1.2455e-01,  3.2182e+00,  8.4060e-01,  4.0000e+00, -2.0730e+01, -3.7475e+00, -3.4911e-01,  2.8737e-01, -1.3231e+01,  1.4491e+00,  3.6845e-01,  1.2668e-01,  5.3740e-01,  7.7559e-01,  1.5401e-01,  1.6122e-02, -2.1220e+00, -1.9726e+00,  3.2725e-01,  2.4553e-01,  1.4343e-02,  3.1512e-01,  6.1158e-01,  2.4048e-01,  8.1008e-02,  5.9988e-01,  1.3972e-01,  7.8652e-02,  9.6312e-02,  1.4320e+01,  5.9508e+00,  1.9603e+00,  9.6870e-01,  1.1067e+00,  1.3408e+00,  7.7608e-01,  1.2339e-01,  2.0973e-01,  1.4456e-01,  1.4492e+00,  7.1440e-01,  1.7073e-01,  1.5868e-01,  5.4204e-02,  1.5064e-01,  1.1621e+01,  1.3906e+00,  1.7168e+00},
          { 5.0329e+01,  3.2842e+00,  5.3117e-01, -1.0328e+00, -1.3382e+01, -2.4911e+01, -6.3737e-01, -9.4767e-02, -1.0131e+01, -3.6596e+00, -2.9165e+00, -4.2327e+01, -2.0828e+01, -2.0730e+01,  1.9360e+03,  3.4246e+02,  7.2690e+01,  3.2718e+01,  7.6389e+02, -2.1254e+01, -7.6581e+00, -2.8477e+00,  1.5992e+01,  2.4812e+01,  4.9980e+00,  1.5630e+01,  5.0960e+02,  2.8507e+02,  6.7587e+01,  6.6512e+00,  6.4068e+00,  1.4056e+01, -1.3126e+01, -3.1602e+00, -2.2496e+00,  3.3834e+00, -3.5091e+00, -1.4381e+00, -2.2452e+00,  1.3789e+02,  6.7467e+01, -1.1080e+01, -4.1431e+00, -1.7106e+01, -2.5067e+01, -1.6905e+01, -2.3125e+00, -5.0871e+00, -3.5427e+00, -2.4358e+01, -1.7149e+01, -6.4024e+00, -2.7465e+00, -1.6814e+00, -3.9358e+00,  5.5155e+01, -9.6980e+00, -3.3763e+01},
          {-3.4163e+01, -8.7063e-01,  1.1130e+00,  4.2650e-01, -1.5840e+01, -6.2786e+00,  6.7217e-01,  1.3110e+00, -2.1284e+00,  6.5061e-01, -2.5942e-01, -8.5252e+00, -1.8338e+00, -3.7475e+00,  3.4246e+02,  1.9600e+02,  3.0502e+01,  1.5611e+01,  3.5812e+01,  4.2587e+01,  3.6915e+00, -2.1103e-01,  1.4850e+01,  2.6568e+01,  9.2145e+00,  9.5183e+00,  2.9175e+01,  5.3584e+01,  3.6784e+01,  4.9392e+00,  3.8031e+00, -1.2229e+01,  4.3638e+00,  1.0246e+00, -2.6704e-01,  1.7167e+00,  2.1960e+00,  2.8599e-01, -2.6560e-01,  1.7142e+00,  7.4675e+01,  1.6635e+01,  3.7370e+00, -2.0185e+01, -5.5045e-01,  1.3589e+00,  1.6540e+00, -4.2631e-01, -6.2615e-01, -2.6685e+00, -1.0212e+00, -1.3466e+00, -9.6329e-02, -3.6328e-02, -1.8873e-01,  4.6705e+01,  1.7218e+01,  9.0619e+00},
          {-6.0535e+00,  7.5934e-01,  3.0771e-01,  5.4176e-01, -3.2510e+00, -6.1464e-01,  7.8808e-02, -4.6568e-01,  4.3006e-01,  1.2488e-01,  2.9975e-01,  1.6425e-02, -8.7707e-01, -3.4911e-01,  7.2690e+01,  3.0502e+01,  2.5000e+01,  7.6234e+00,  1.1931e+01,  5.6991e+00,  4.2717e-01,  2.6595e-01,  1.9475e+00,  9.6617e+00,  2.9258e+00,  3.3160e+00,  1.8805e+01,  8.1296e+00,  1.0188e+01,  2.6133e+00,  9.6475e-01, -5.2440e+00,  4.2863e-01,  8.5001e-01, -7.6402e-03,  2.7589e+00, -3.5558e-01,  7.2168e-02,  2.2202e-02,  3.1910e+00,  2.0789e+01,  9.2835e+00,  1.3100e+00, -7.5939e+00,  1.3414e+00,  1.4106e+00,  1.9982e-01, -2.9089e-03,  1.8114e-01,  2.3968e-01,  6.6505e-01, -1.7140e-01,  2.1854e-01,  1.8727e-01,  3.6617e-01,  2.6746e+01,  2.3659e+00,  4.2402e+00},
          {-5.8740e+00,  1.5774e+00,  2.5008e-01,  5.6208e-01, -1.5036e+00,  1.8604e-01,  5.4376e-02, -5.3508e-01,  5.7227e-01,  2.4977e-01,  4.0790e-01,  5.2183e-01, -6.6149e-01,  2.8737e-01,  3.2718e+01,  1.5611e+01,  7.6234e+00,  1.6000e+01, -2.6856e+00,  5.6364e+00,  7.1657e-01,  3.0756e-01,  1.0395e+00,  6.7636e+00,  1.7777e+00,  2.7370e+00,  8.1939e+00,  1.8500e+00,  6.7128e+00,  1.8492e+00,  7.7768e-01, -4.1174e+00,  5.1042e-01,  8.2343e-01,  1.1913e-01,  2.6494e+00, -3.1652e-01,  1.2578e-01,  1.3778e-01, -2.5379e+00,  1.3230e+01,  7.0637e+00,  2.8247e+00, -4.8142e+00,  1.5527e+00,  1.8846e+00,  1.7351e-01,  1.5557e-01,  3.4804e-01,  7.1428e-01,  9.1648e-01,  5.6969e-02,  2.5978e-01,  1.7602e-01,  4.3992e-01,  2.0079e+01,  1.1654e+00,  4.3716e+00},
          { 1.9491e+02,  1.6150e+01, -1.6178e+00,  2.0747e-01,  4.6973e+01, -3.3927e-01, -3.7096e-01,  2.5258e+00, -7.3069e+00,  5.8560e-01,  5.0866e-02, -2.4359e+01, -6.1958e+00, -1.3231e+01,  7.6389e+02,  3.5812e+01,  1.1931e+01, -2.6856e+00,  1.7640e+03,  1.1728e+02,  1.6650e+00, -1.1864e+00,  4.1154e+00, -2.3409e+01, -4.9389e+00, -2.2005e+00,  6.7493e+02,  1.4766e+02,  1.1716e+01, -1.4650e+00, -1.3901e+00,  1.3179e+02,  1.0010e+01, -9.5101e-01, -1.5593e-01,  1.0092e+00, -2.5778e+00, -7.7567e-01, -9.0399e-02,  1.9738e+02, -6.1461e+01, -2.4545e+01, -3.2633e+01,  6.9197e+01, -3.3880e+00, -3.2128e+00, -3.4228e+00, -6.3544e-01, -1.2161e+00, -9.5843e+00, -7.7775e+00,  4.6167e-01, -1.0760e+00, -2.0508e-01, -1.6588e+00,  6.4483e-02, -1.9495e+01, -2.5121e+01},
          { 1.1548e+01,  1.5643e+00,  1.0032e+00,  9.9053e-01, -2.0051e+00,  5.6024e+00,  1.4991e+00,  4.6936e+00,  1.7620e+00,  2.6090e+00,  1.0296e+00,  1.3227e+00,  3.5152e+00,  1.4491e+00, -2.1254e+01,  4.2587e+01,  5.6990e+00,  5.6364e+00,  1.1728e+02,  1.9600e+02,  1.1514e+01,  1.1892e+00,  2.0054e+01,  1.9023e+01,  7.4393e+00,  3.8528e+00, -1.3385e+01, -2.0894e+01,  2.9715e+01,  1.1840e+00,  7.4767e-01,  1.4357e+01,  2.0847e+01,  2.6683e+00,  1.1021e+00, -1.0629e+00,  4.4850e+00,  1.2477e+00,  7.7750e-01, -2.4064e+01,  3.1210e+01,  1.2228e+01,  1.1852e+00, -2.9505e+00,  1.5272e+01,  1.1956e+01,  3.2899e+00,  1.4064e+00,  9.7202e-01,  3.0194e+00,  3.6212e+00,  1.7027e+00,  3.2563e-01,  7.4911e-01,  8.4511e-01,  4.1004e+01,  1.7531e+01,  1.8704e+01},
          {-1.6408e+00,  7.4146e-01,  1.9140e-01,  6.3875e-02,  5.8261e-01,  2.0943e-01,  1.3246e-01,  4.1060e-01,  4.3648e-01,  3.9463e-01,  1.1563e-01,  6.1262e-01,  9.1074e-01,  3.6845e-01, -7.6581e+00,  3.6915e+00,  4.2717e-01,  7.1657e-01,  1.6650e+00,  1.1514e+01,  4.0000e+00,  7.5424e-02,  2.5932e+00,  2.3705e+00,  6.3756e-01,  6.1704e-01, -9.5928e+00, -1.8903e+00,  2.1564e+00,  2.2440e-01,  1.0762e-01,  1.5697e+00,  1.5565e+00,  2.7500e-01,  9.0960e-02,  1.9928e-01,  6.7418e-01,  9.3560e-02,  1.0644e-01, -7.4883e+00,  2.5700e+00,  1.2217e+00,  1.8157e-01, -2.5756e-01,  1.2545e+00,  1.0260e+00,  2.6365e-01,  1.6347e-01,  1.3302e-01,  6.0498e-01,  3.9545e-01,  2.6216e-01,  1.1001e-01,  8.8506e-02,  1.0472e-01,  5.7544e+00,  4.3268e+00,  2.3870e+00},
          { 7.4316e-01,  1.9076e-01,  2.1266e-02,  5.2456e-02,  1.9291e-01,  1.8924e-01,  1.4099e-02, -1.0730e-03,  1.6678e-01,  4.9851e-02,  5.0662e-02,  4.0152e-01,  2.7889e-02,  1.2668e-01, -2.8477e+00, -2.1103e-01,  2.6595e-01,  3.0756e-01, -1.1864e+00,  1.1892e+00,  7.5424e-02,  2.5000e-01, -1.1045e-02,  3.9442e-01,  1.2183e-01,  9.9510e-02,  9.0211e-01, -7.2715e-01,  3.3240e-01,  1.1197e-01,  3.0316e-02, -7.4296e-02,  2.1028e-01,  9.1103e-02,  2.1952e-02,  1.0889e-01,  1.0656e-02,  2.4712e-02,  1.8215e-02,  5.9876e-01,  2.0783e-01,  4.8534e-01,  1.3450e-01, -1.6128e-01,  2.8303e-01,  2.8239e-01,  3.4895e-02,  4.3564e-02,  5.1605e-02,  6.8382e-02,  1.2577e-01,  4.0547e-02,  1.6696e-02,  2.9372e-02,  5.2345e-02,  1.9107e+00,  9.0790e-02,  3.1365e-01},
          { 6.4866e+00,  1.4916e+00,  3.5668e-01,  3.6557e-01,  2.8119e+00,  7.2290e-01,  2.8039e-01,  1.5817e+00,  1.4936e+00,  8.1437e-01,  1.2806e-01,  1.0863e+00,  1.4579e+00,  5.3740e-01,  1.5992e+01,  1.4850e+01,  1.9475e+00,  1.0395e+00,  4.1154e+00,  2.0054e+01,  2.5932e+00, -1.1045e-02,  3.6000e+01,  5.0499e+00,  1.4791e+00,  1.0416e+00, -7.9607e+00,  3.8789e-01,  5.6812e+00,  1.0058e+00,  1.2353e-01,  3.6783e+00,  2.8273e+00,  4.5971e-01,  9.2897e-02,  6.4979e-01,  1.1040e+00,  1.6622e-01,  1.6248e-01, -5.2402e+00,  7.4933e+00,  2.9479e+00,  7.9427e-01, -2.1508e+00,  1.4687e+00,  1.2725e+00,  5.0803e-01,  2.6895e-01,  8.4561e-02,  1.1663e+00,  8.1943e-01,  3.5670e-01,  3.5529e-01,  5.5211e-02,  1.5782e-01,  1.9604e+01,  8.5764e+00,  5.7456e+00},
          {-6.2086e+00,  2.3292e+00,  6.6120e-01,  5.1252e-01, -2.1509e-01,  1.0685e+00,  2.3418e-01,  2.2105e-01,  1.5756e+00,  8.4996e-01,  3.5110e-01,  2.2588e+00,  1.2507e+00,  7.7559e-01,  2.4812e+01,  2.6568e+01,  9.6617e+00,  6.7636e+00, -2.3409e+01,  1.9023e+01,  2.3705e+00,  3.9442e-01,  5.0499e+00,  2.5000e+01,  3.4990e+00,  3.8380e+00, -1.7410e+01,  4.2777e-01,  1.0284e+01,  2.3375e+00,  8.4670e-01, -5.3576e+00,  2.6919e+00,  1.1188e+00,  2.2216e-01,  3.2493e+00,  4.3065e-01,  2.0186e-01,  1.7890e-01, -1.7516e+01,  1.9309e+01,  8.2791e+00,  1.7841e+00, -8.0796e+00,  3.2512e+00,  2.7135e+00,  7.2280e-01,  2.5183e-01,  3.5820e-01,  1.8281e+00,  1.3014e+00,  2.5348e-01,  2.7984e-01,  2.1766e-01,  4.4670e-01,  3.8533e+01,  8.9561e+00,  8.8350e+00},
          {-1.8616e+00,  4.2511e-01,  1.7221e-01,  1.3530e-01, -1.4388e-01,  3.0721e-01,  1.3814e-01,  3.0402e-01,  3.8432e-01,  2.0299e-01,  1.2117e-01,  1.1340e-01,  3.3923e-01,  1.5401e-01,  4.9980e+00,  9.2145e+00,  2.9258e+00,  1.7777e+00, -4.9389e+00,  7.4393e+00,  6.3756e-01,  1.2183e-01,  1.4791e+00,  3.4990e+00,  4.0000e+00,  1.1517e+00, -7.2828e+00,  5.4244e-01,  3.3420e+00,  6.9240e-01,  3.5018e-01, -1.2240e+00,  1.1316e+00,  3.5316e-01,  3.2394e-02,  6.1092e-01,  3.5269e-01,  9.6248e-02,  6.7257e-02, -4.0850e+00,  8.4074e+00,  2.8135e+00,  8.5968e-01, -1.9669e+00,  8.1150e-01,  8.6224e-01,  3.2450e-01,  8.5525e-02,  1.0745e-01,  4.0651e-01,  5.3976e-01,  6.1790e-02,  9.9518e-02,  7.7694e-02,  1.6208e-01,  9.0707e+00,  2.5175e+00,  2.5858e+00},
          {-4.5660e+00,  9.5936e-02,  8.1010e-02,  1.7802e-01, -1.4491e+00, -3.0737e-01,  1.0743e-01,  8.6424e-02,  3.8318e-01,  8.3866e-02,  1.0689e-01, -5.6752e-01, -1.5772e-01,  1.6122e-02,  1.5630e+01,  9.5183e+00,  3.3160e+00,  2.7370e+00, -2.2005e+00,  3.8528e+00,  6.1704e-01,  9.9510e-02,  1.0416e+00,  3.8380e+00,  1.1517e+00,  4.0000e+00, -1.1835e+01,  9.1676e-01,  3.6684e+00,  8.6112e-01,  3.1884e-01, -3.2733e+00,  2.1282e-01,  4.3479e-01,  5.6370e-03,  1.3604e+00,  1.4925e-01,  4.0086e-02,  3.8857e-02, -1.1858e+01,  7.4851e+00,  2.5722e+00,  5.3778e-01, -2.3200e+00,  6.1914e-01,  6.6752e-01,  1.4370e-01,  2.0792e-02,  7.6395e-02,  5.8848e-01,  3.3715e-01, -3.1084e-02,  8.6846e-02,  5.0152e-02,  1.3240e-01,  9.2194e+00,  2.3758e+00,  3.0283e+00},
          { 1.6077e+02,  1.6323e+01,  6.0493e-01,  1.0260e+00,  3.0712e+01,  4.5976e+00, -1.1670e+00, -5.6898e+00,  2.0970e+00,  1.8904e+00,  8.5012e-01,  1.7237e+01, -2.3046e+00, -2.1220e+00,  5.0960e+02,  2.9175e+01,  1.8805e+01,  8.1939e+00,  6.7493e+02, -1.3385e+01, -9.5928e+00,  9.0211e-01, -7.9607e+00, -1.7410e+01, -7.2828e+00, -1.1835e+01,  1.1560e+03,  1.4223e+02,  3.5847e+01,  7.7391e+00,  2.0835e+00,  8.8354e+01,  5.9463e+00, -3.3743e-01,  6.5440e-01,  1.0376e+00, -8.8882e+00,  9.1350e-01,  4.6214e-01,  6.9180e+02,  6.3972e+01,  3.2150e+01,  2.1464e+00,  5.8748e+01,  8.6852e+00,  6.7155e+00, -1.7210e+00, -1.1227e-01,  6.0148e-01, -2.8335e+00,  4.9843e-01,  4.7626e-01,  4.4549e-01,  8.0288e-01,  1.3386e+00,  6.8049e+01, -3.9013e+01, -8.6263e+00},
          { 1.1953e+00,  1.9234e+00, -5.3426e-02, -5.3040e-01,  4.7026e-01, -5.2209e+00, -1.3493e-01,  3.6808e-01, -2.3749e+00, -8.1092e-01, -8.4298e-01, -1.6164e+00, -8.3659e-01, -1.9726e+00,  2.8507e+02,  5.3584e+01,  8.1295e+00,  1.8500e+00,  1.4766e+02, -2.0894e+01, -1.8903e+00, -7.2715e-01,  3.8789e-01,  4.2777e-01,  5.4244e-01,  9.1676e-01,  1.4223e+02,  1.6900e+02,  1.2772e+01,  2.1727e+00,  1.2632e+00,  1.7801e+01, -1.7126e+00, -7.8852e-01, -6.0273e-01,  9.2048e-01,  4.1794e-01, -3.7818e-02, -4.8873e-01,  1.8570e+02,  6.0218e+01,  7.5736e+00,  4.5930e+00,  1.8709e+01, -2.0843e+00, -3.6444e+00, -6.6613e-01, -7.7457e-01, -6.0172e-01,  2.9324e-01, -1.4919e+00, -8.1895e-01,  4.9226e-02, -4.3766e-01, -4.6259e-01,  1.0930e+01,  2.6212e+00, -2.7373e-01},
          {-1.1702e+01, -5.3018e-01,  1.8377e-01,  4.3211e-01, -6.8602e+00, -7.7132e-03,  3.8054e-01,  3.1536e-01,  8.7205e-02,  4.5396e-01,  3.5799e-01,  1.1087e+00, -9.0329e-01,  3.2725e-01,  6.7587e+01,  3.6784e+01,  1.0188e+01,  6.7128e+00,  1.1716e+01,  2.9715e+01,  2.1564e+00,  3.3240e-01,  5.6812e+00,  1.0284e+01,  3.3420e+00,  3.6684e+00,  3.5847e+01,  1.2772e+01,  3.6000e+01,  2.3479e+00,  1.1074e+00, -3.3796e+00,  4.6301e+00,  1.0441e+00,  1.0427e-01,  2.2609e+00,  4.8421e-01,  4.7918e-01,  1.2766e-01,  4.7131e+01,  4.0107e+01,  1.3318e+01,  3.7645e+00, -1.9696e+00,  4.5227e+00,  3.6220e+00,  1.0264e+00,  2.6193e-01,  2.9679e-01,  1.8288e+00,  1.2168e+00,  3.0374e-01,  1.5755e-01,  1.9859e-01,  4.9734e-01,  2.1958e+01,  2.8238e+00,  1.0042e+01},
          { 7.1868e-01,  9.6960e-01,  1.6604e-01,  1.9170e-01,  1.0433e+00,  1.8915e-01,  4.3122e-02,  1.8338e-02,  5.6327e-01,  2.2482e-01,  1.4826e-01,  1.4498e+00,  1.7681e-01,  2.4553e-01,  6.6512e+00,  4.9392e+00,  2.6133e+00,  1.8492e+00, -1.4650e+00,  1.1840e+00,  2.2440e-01,  1.1197e-01,  1.0058e+00,  2.3375e+00,  6.9240e-01,  8.6112e-01,  7.7391e+00,  2.1727e+00,  2.3479e+00,  4.0000e+00,  3.1002e-01, -1.3773e-01,  1.9834e-01,  3.0535e-01,  4.6974e-02,  7.7592e-01, -1.0327e-02,  7.1759e-02,  4.3655e-02,  8.5128e+00,  6.4674e+00,  3.2957e+00,  6.5904e-01, -8.9962e-01,  7.2240e-01,  6.5600e-01,  1.4410e-01,  3.2214e-02,  1.2908e-01,  3.5067e-01,  4.0688e-01,  1.0455e-01,  1.5810e-01,  8.1738e-02,  1.7631e-01,  1.0214e+01,  1.6527e+00,  1.8856e+00},
          {-1.2237e+00,  7.6300e-02,  2.7915e-02,  1.8301e-02, -2.9719e-01, -1.2869e-01,  4.9360e-02,  1.1940e-01, -1.5615e-02,  5.5812e-02,  2.4772e-02, -1.6349e-01, -1.2923e-01,  1.4343e-02,  6.4068e+00,  3.8031e+00,  9.6475e-01,  7.7768e-01, -1.3901e+00,  7.4767e-01,  1.0762e-01,  3.0316e-02,  1.2353e-01,  8.4670e-01,  3.5018e-01,  3.1884e-01,  2.0835e+00,  1.2632e+00,  1.1074e+00,  3.1002e-01,  1.0000e+00, -4.5750e-01,  1.7550e-01,  7.7910e-02,  1.8668e-03,  1.0899e-01,  8.0714e-02,  2.2742e-02,  9.2520e-03,  3.8773e+00,  3.9595e+00,  1.4034e+00,  5.0748e-01, -2.0467e-01,  1.3783e-02,  1.4936e-01,  7.5728e-02, -3.6906e-03,  3.8015e-02,  1.0415e-01,  9.2360e-02, -9.4696e-03,  3.4698e-02,  1.3894e-02,  3.9110e-02,  2.0708e+00,  6.8463e-01,  6.7836e-01},
          { 3.0163e+01,  6.4909e+00,  1.7462e-01,  1.4073e-01,  1.4751e+01,  2.4295e+00,  1.2999e-02,  3.9653e-01,  1.7709e+00,  1.2123e+00,  7.3620e-02,  5.9016e+00,  4.5286e+00,  3.1512e-01,  1.4056e+01, -1.2229e+01, -5.2440e+00, -4.1174e+00,  1.3179e+02,  1.4357e+01,  1.5697e+00, -7.4296e-02,  3.6783e+00, -5.3576e+00, -1.2240e+00, -3.2733e+00,  8.8354e+01,  1.7801e+01, -3.3796e+00, -1.3773e-01, -4.5750e-01,  6.4000e+01,  2.6791e+00, -2.9707e-01,  2.5931e-01, -1.5723e+00,  7.2868e-01, -1.3546e-02,  2.9357e-01,  8.6186e+01, -4.6797e-01,  4.2705e-01, -1.9253e+00,  1.5453e+01,  2.0958e+00,  4.5822e-01, -4.3302e-02,  2.8817e-01,  1.9937e-01,  1.2662e+00,  3.2298e-01,  7.4413e-01,  2.4649e-01,  9.8753e-02,  7.3916e-02,  8.3892e+00,  7.4502e+00, -3.9815e-01},
          { 1.8019e+00, -6.2102e-02,  1.9310e-01,  1.3812e-01, -5.7360e-01,  8.5403e-01,  2.1522e-01,  6.4350e-01,  2.3434e-01,  3.2468e-01,  1.6118e-01,  1.9332e+00,  7.1723e-01,  6.1158e-01, -1.3126e+01,  4.3638e+00,  4.2862e-01,  5.1042e-01,  1.0010e+01,  2.0847e+01,  1.5565e+00,  2.1028e-01,  2.8273e+00,  2.6919e+00,  1.1316e+00,  2.1282e-01,  5.9463e+00, -1.7126e+00,  4.6301e+00,  1.9834e-01,  1.7550e-01,  2.6791e+00,  9.0000e+00,  4.4639e-01,  1.5718e-01,  5.9452e-03,  7.3523e-01,  2.4282e-01,  1.2713e-01,  2.0746e+01,  1.2302e+01,  4.1816e+00,  1.1490e+00,  1.7583e+00,  2.5765e+00,  1.9841e+00,  5.4893e-01,  2.4701e-01,  2.1183e-01,  1.3126e+00,  9.6030e-01,  3.5265e-01,  8.7402e-02,  1.2742e-01,  2.2941e-01,  7.9997e+00,  2.1334e+00,  3.8851e+00},
          { 3.3410e-01,  3.1071e-01,  5.8797e-02,  1.1492e-01, -2.7325e-02,  3.1309e-01,  4.3535e-02,  3.6329e-02,  2.6249e-01,  1.3634e-01,  1.0373e-01,  6.3855e-01,  9.3034e-02,  2.4048e-01, -3.1602e+00,  1.0246e+00,  8.5001e-01,  8.2343e-01, -9.5101e-01,  2.6683e+00,  2.7500e-01,  9.1103e-02,  4.5971e-01,  1.1188e+00,  3.5316e-01,  4.3479e-01, -3.3743e-01, -7.8852e-01,  1.0441e+00,  3.0535e-01,  7.7910e-02, -2.9707e-01,  4.4639e-01,  8.1000e-01,  4.1065e-02,  5.5172e-01,  9.2250e-02,  6.2633e-02,  4.0601e-02,  9.7243e-01,  2.7909e+00,  1.4965e+00,  4.1737e-01, -2.6650e-01,  5.9991e-01,  5.9107e-01,  8.3513e-02,  6.2549e-02,  1.0729e-01,  4.8041e-01,  3.6310e-01,  9.1526e-02,  6.1095e-02,  7.2930e-02,  1.3220e-01,  4.5543e+00,  6.4310e-01,  1.3437e+00},
          { 8.4752e-01,  2.0458e-01,  3.4158e-02,  2.8151e-02,  3.6144e-01,  2.1361e-01,  1.0558e-02,  8.4104e-03,  1.1328e-01,  4.3009e-02,  3.2928e-02,  2.3779e-01,  1.3888e-01,  8.1008e-02, -2.2496e+00, -2.6704e-01, -7.6402e-03,  1.1913e-01, -1.5593e-01,  1.1021e+00,  9.0960e-02,  2.1952e-02,  9.2897e-02,  2.2216e-01,  3.2394e-02,  5.6370e-03,  6.5440e-01, -6.0273e-01,  1.0427e-01,  4.6974e-02,  1.8668e-03,  2.5931e-01,  1.5718e-01,  4.1065e-02,  1.6000e-01,  4.3160e-02,  2.4385e-02,  1.4044e-02,  1.8419e-02,  3.5530e-01, -4.3271e-03,  1.8005e-01,  2.6786e-02, -1.4021e-03,  1.9012e-01,  1.8922e-01,  2.3203e-02,  2.3047e-02,  2.3710e-02,  5.4198e-02,  1.0019e-01,  2.5184e-02,  1.7818e-02,  1.4376e-02,  2.5726e-02,  1.0905e+00,  1.2001e-01,  2.0365e-01},
          {-6.8048e-01,  8.0400e-01,  2.1526e-02,  2.0472e-01, -2.3789e-01,  2.6843e-01,  1.6223e-02, -3.4982e-01,  1.3851e-01,  1.7174e-01,  1.8438e-01,  1.2749e+00, -3.9663e-02,  5.9988e-01,  3.3834e+00,  1.7167e+00,  2.7589e+00,  2.6494e+00,  1.0092e+00, -1.0629e+00,  1.9928e-01,  1.0889e-01,  6.4979e-01,  3.2493e+00,  6.1092e-01,  1.3604e+00,  1.0376e+00,  9.2048e-01,  2.2609e+00,  7.7592e-01,  1.0899e-01, -1.5723e+00,  5.9452e-03,  5.5172e-01,  4.3160e-02,  4.0000e+00, -2.1513e-01,  5.0693e-02,  4.5086e-02,  4.6223e+00,  7.6493e+00,  3.3641e+00,  1.1492e+00, -5.4614e-01,  1.2128e+00,  9.9928e-01,  6.6198e-03,  5.3107e-02,  1.9718e-01,  1.5355e+00,  6.3616e-01,  1.4445e-01,  1.3322e-01,  8.6400e-02,  2.4936e-01,  1.1251e+01,  6.7728e-01,  3.1638e+00},
          {-3.2115e-01, -3.2421e-02,  9.7005e-02, -2.9079e-02,  4.0743e-01,  8.4689e-02,  8.9326e-02,  4.6233e-01,  1.8338e-01,  1.3905e-01, -1.0197e-02,  3.7412e-01,  5.0302e-01,  1.3972e-01, -3.5091e+00,  2.1960e+00, -3.5558e-01, -3.1652e-01, -2.5778e+00,  4.4850e+00,  6.7418e-01,  1.0656e-02,  1.1040e+00,  4.3065e-01,  3.5269e-01,  1.4925e-01, -8.8882e+00,  4.1794e-01,  4.8421e-01, -1.0327e-02,  8.0714e-02,  7.2868e-01,  7.3523e-01,  9.2250e-02,  2.4385e-02, -2.1513e-01,  1.6900e+00,  3.5536e-02,  2.3094e-02, -9.9263e-01,  2.6047e+00,  4.3091e-01,  1.7406e-01,  5.4822e-01,  1.8116e-01,  1.0053e-01,  1.3047e-01,  6.8346e-02,  2.4667e-02,  3.9858e-01,  2.3129e-01,  1.0355e-01,  2.7108e-02, -1.9789e-03, -6.8146e-04,  1.4687e+00,  2.4176e+00,  9.3943e-01},
          { 2.8435e-01,  1.9523e-02,  2.3852e-02,  1.8826e-02, -5.2691e-02,  1.1080e-01,  1.6827e-02,  5.3734e-02,  8.2480e-02,  2.9048e-02,  1.8553e-02,  2.7007e-01,  5.1848e-02,  7.8652e-02, -1.4381e+00,  2.8599e-01,  7.2168e-02,  1.2578e-01, -7.7567e-01,  1.2477e+00,  9.3560e-02,  2.4712e-02,  1.6622e-01,  2.0186e-01,  9.6248e-02,  4.0086e-02,  9.1350e-01, -3.7818e-02,  4.7918e-01,  7.1759e-02,  2.2742e-02, -1.3546e-02,  2.4282e-01,  6.2633e-02,  1.4044e-02,  5.0693e-02,  3.5536e-02,  1.6000e-01,  1.1630e-02,  2.2589e+00,  1.3192e+00,  4.5806e-01,  1.2110e-01,  9.2054e-02,  2.2398e-01,  1.9049e-01,  3.6474e-02,  1.7315e-02,  2.7696e-02,  1.1554e-01,  9.6664e-02,  2.8762e-02,  1.3002e-02,  1.0803e-02,  3.1368e-02,  9.4777e-01,  1.4269e-01,  4.5048e-01},
          { 6.9055e-01,  1.3234e-01,  1.6044e-02,  2.2926e-02,  3.8691e-01,  1.5304e-01,  1.0419e-02,  4.1647e-02,  1.0461e-01,  3.6461e-02,  2.0582e-02,  1.4535e-01,  9.3854e-02,  9.6312e-02, -2.2452e+00, -2.6560e-01,  2.2202e-02,  1.3778e-01, -9.0399e-02,  7.7750e-01,  1.0644e-01,  1.8215e-02,  1.6248e-01,  1.7890e-01,  6.7257e-02,  3.8857e-02,  4.6214e-01, -4.8873e-01,  1.2766e-01,  4.3655e-02,  9.2520e-03,  2.9357e-01,  1.2713e-01,  4.0601e-02,  1.8419e-02,  4.5086e-02,  2.3094e-02,  1.1630e-02,  1.6000e-01,  3.0099e-01,  2.0291e-01,  1.6983e-01,  2.9856e-02,  8.5123e-02,  1.0190e-01,  1.3046e-01,  2.5155e-02,  1.9309e-02,  2.0918e-02,  5.7930e-02,  7.4905e-02,  2.1297e-02,  1.8545e-02,  1.3415e-02,  2.2290e-02,  1.3624e+00,  2.5994e-01,  2.6030e-01},
          { 3.4288e+01,  4.4347e+00, -2.0234e-01, -1.2483e+00, -9.2022e+00, -1.0303e+00,  2.4827e-01, -8.2688e-01, -1.3400e+00, -2.3246e-01, -2.1516e-01,  6.7061e+01,  7.1388e+00,  1.4320e+01,  1.3789e+02,  1.7142e+00,  3.1910e+00, -2.5379e+00,  1.9738e+02, -2.4064e+01, -7.4883e+00,  5.9876e-01, -5.2402e+00, -1.7516e+01, -4.0850e+00, -1.1858e+01,  6.9180e+02,  1.8570e+02,  4.7131e+01,  8.5128e+00,  3.8773e+00,  8.6186e+01,  2.0746e+01,  9.7243e-01,  3.5530e-01,  4.6223e+00, -9.9263e-01,  2.2589e+00,  3.0099e-01,  1.6000e+03,  4.2171e+02,  1.1464e+02,  5.4678e+01,  1.4218e+02,  3.3308e+01,  9.4864e+00,  1.7994e+00,  1.2595e+00,  1.6073e+00,  4.1928e+01,  1.2897e+01,  4.5189e+00,  2.7222e+00,  4.9007e-01,  3.4618e+00,  6.5881e+01, -1.5056e+01,  3.7666e+01},
          {-6.4249e+01, -7.5506e-01,  2.3537e-01,  4.6634e-01, -2.5047e+01, -4.2790e+00,  9.3593e-01,  1.1356e+00, -2.1220e+00,  1.3881e-01,  2.5548e-01,  2.3624e+01,  2.5378e+00,  5.9508e+00,  6.7467e+01,  7.4675e+01,  2.0789e+01,  1.3230e+01, -6.1461e+01,  3.1210e+01,  2.5700e+00,  2.0783e-01,  7.4933e+00,  1.9309e+01,  8.4074e+00,  7.4851e+00,  6.3972e+01,  6.0218e+01,  4.0107e+01,  6.4674e+00,  3.9595e+00, -4.6797e-01,  1.2302e+01,  2.7909e+00, -4.3271e-03,  7.6493e+00,  2.6047e+00,  1.3192e+00,  2.0291e-01,  4.2171e+02,  3.2400e+02,  6.5645e+01,  2.7997e+01,  3.4544e+01,  1.7547e+01,  6.9656e+00,  2.3016e+00,  7.3103e-01,  9.2484e-01,  2.1034e+01,  7.5337e+00,  1.8827e+00,  1.3992e+00,  3.4984e-01,  1.6711e+00,  6.3538e+01,  1.6604e+01,  3.2475e+01},
          {-1.4508e+01,  6.9434e-01,  3.1375e-01,  6.5261e-01, -5.9750e+00,  5.3339e-01,  3.4937e-01, -1.5041e-01,  1.0206e+00,  7.9904e-01,  5.1123e-01,  8.3992e+00,  1.2905e+00,  1.9603e+00, -1.1080e+01,  1.6635e+01,  9.2835e+00,  7.0637e+00, -2.4545e+01,  1.2228e+01,  1.2217e+00,  4.8534e-01,  2.9479e+00,  8.2791e+00,  2.8135e+00,  2.5722e+00,  3.2150e+01,  7.5736e+00,  1.3318e+01,  3.2957e+00,  1.4034e+00,  4.2705e-01,  4.1816e+00,  1.4965e+00,  1.8005e-01,  3.3641e+00,  4.3091e-01,  4.5806e-01,  1.6983e-01,  1.1464e+02,  6.5645e+01,  3.6000e+01,  9.0945e+00,  6.0707e+00,  6.2323e+00,  4.1473e+00,  8.5258e-01,  4.5232e-01,  7.4961e-01,  6.1909e+00,  3.3181e+00,  9.6596e-01,  5.7784e-01,  3.5374e-01,  1.0356e+00,  2.8116e+01,  4.4079e+00,  1.2473e+01},
          {-8.1048e+00, -4.2827e-01,  6.7338e-03,  8.7941e-02, -3.6156e+00, -1.9677e-01,  9.4288e-02, -8.2338e-02, -1.9186e-01,  1.2155e-01,  1.3830e-01,  3.2359e+00,  3.6207e-01,  9.6870e-01, -4.1431e+00,  3.7370e+00,  1.3100e+00,  2.8247e+00, -3.2633e+01,  1.1852e+00,  1.8157e-01,  1.3450e-01,  7.9427e-01,  1.7841e+00,  8.5968e-01,  5.3778e-01,  2.1464e+00,  4.5930e+00,  3.7645e+00,  6.5904e-01,  5.0748e-01, -1.9253e+00,  1.1490e+00,  4.1737e-01,  2.6786e-02,  1.1492e+00,  1.7406e-01,  1.2110e-01,  2.9856e-02,  5.4678e+01,  2.7997e+01,  9.0945e+00,  9.0000e+00,  4.5421e+00,  2.4851e+00,  1.1353e+00,  1.9591e-01,  1.7819e-01,  2.8029e-01,  2.9682e+00,  1.2662e+00,  3.1479e-01,  2.3033e-01,  1.2113e-01,  3.5233e-01,  5.1535e+00,  3.8126e-01,  4.2208e+00},
          { 1.0030e+01, -7.4489e-02, -5.1325e-01, -5.1888e-01,  1.0591e+00, -2.8017e-01,  1.0586e-01,  6.7727e-01, -9.6622e-01, -2.7779e-01, -1.3100e-01,  5.8028e+00,  1.1886e+00,  1.1067e+00, -1.7106e+01, -2.0185e+01, -7.5939e+00, -4.8142e+00,  6.9197e+01, -2.9505e+00, -2.5756e-01, -1.6128e-01, -2.1508e+00, -8.0796e+00, -1.9669e+00, -2.3200e+00,  5.8748e+01,  1.8709e+01, -1.9696e+00, -8.9962e-01, -2.0467e-01,  1.5453e+01,  1.7583e+00, -2.6650e-01, -1.4021e-03, -5.4614e-01,  5.4822e-01,  9.2054e-02,  8.5123e-02,  1.4218e+02,  3.4544e+01,  6.0707e+00,  4.5421e+00,  3.6000e+01,  2.5598e+00, -3.9570e-01, -2.1451e-01,  2.8892e-02,  1.3402e-01,  5.1244e+00,  1.0190e+00,  7.6453e-01,  2.6775e-01, -9.7142e-02,  1.7026e-01, -1.1808e+01, -1.9100e+00,  2.1701e+00},
          {-1.3999e-01,  7.7324e-01,  1.3286e-01,  2.8104e-01, -1.1069e+00,  1.3493e+00,  1.0454e-01,  1.0082e-02,  4.8300e-01,  3.9663e-01,  3.0804e-01,  3.7411e+00,  7.8252e-01,  1.3408e+00, -2.5067e+01, -5.5045e-01,  1.3414e+00,  1.5527e+00, -3.3880e+00,  1.5272e+01,  1.2545e+00,  2.8303e-01,  1.4687e+00,  3.2512e+00,  8.1150e-01,  6.1914e-01,  8.6852e+00, -2.0843e+00,  4.5227e+00,  7.2240e-01,  1.3783e-02,  2.0958e+00,  2.5765e+00,  5.9991e-01,  1.9012e-01,  1.2128e+00,  1.8116e-01,  2.2398e-01,  1.0190e-01,  3.3308e+01,  1.7547e+01,  6.2323e+00,  2.4851e+00,  2.5598e+00,  9.0000e+00,  2.4713e+00,  4.3135e-01,  3.2266e-01,  2.9056e-01,  2.4394e+00,  1.4469e+00,  4.6960e-01,  2.4106e-01,  2.1394e-01,  4.1701e-01,  1.2416e+01,  1.6312e+00,  5.4428e+00},
          { 5.9364e-01,  7.6373e-01,  1.4098e-01,  2.9787e-01,  6.9205e-02,  9.4326e-01,  1.6593e-01,  7.2844e-02,  6.6858e-01,  3.6023e-01,  2.9706e-01,  1.6261e+00,  5.1325e-01,  7.7608e-01, -1.6905e+01,  1.3589e+00,  1.4106e+00,  1.8846e+00, -3.2128e+00,  1.1956e+01,  1.0260e+00,  2.8239e-01,  1.2725e+00,  2.7135e+00,  8.6224e-01,  6.6752e-01,  6.7155e+00, -3.6444e+00,  3.6220e+00,  6.5600e-01,  1.4936e-01,  4.5822e-01,  1.9841e+00,  5.9107e-01,  1.8922e-01,  9.9928e-01,  1.0053e-01,  1.9049e-01,  1.3046e-01,  9.4864e+00,  6.9656e+00,  4.1473e+00,  1.1353e+00, -3.9570e-01,  2.4713e+00,  4.0000e+00,  3.4694e-01,  2.0648e-01,  2.8976e-01,  9.5082e-01,  8.7496e-01,  3.1675e-01,  1.6874e-01,  1.6081e-01,  3.3807e-01,  9.7175e+00,  1.2664e+00,  3.8938e+00},
          {-3.1859e-01, -3.9990e-02,  3.8597e-02,  2.8181e-02, -2.2302e-01,  1.6781e-01,  4.7302e-02,  2.0237e-01,  3.7037e-02,  4.5474e-02,  2.5822e-02,  3.0316e-01,  1.4631e-01,  1.2339e-01, -2.3125e+00,  1.6540e+00,  1.9982e-01,  1.7351e-01, -3.4228e+00,  3.2899e+00,  2.6365e-01,  3.4895e-02,  5.0803e-01,  7.2280e-01,  3.2450e-01,  1.4370e-01, -1.7210e+00, -6.6613e-01,  1.0264e+00,  1.4410e-01,  7.5728e-02, -4.3302e-02,  5.4893e-01,  8.3513e-02,  2.3203e-02,  6.6198e-03,  1.3047e-01,  3.6474e-02,  2.5155e-02,  1.7994e+00,  2.3016e+00,  8.5258e-01,  1.9591e-01, -2.1451e-01,  4.3135e-01,  3.4694e-01,  6.4000e-01,  2.6319e-02,  2.1177e-02,  1.0576e-01,  1.8842e-01,  5.9914e-02,  1.3922e-02,  2.0350e-02,  3.6248e-02,  2.1084e+00,  8.1357e-01,  9.4853e-01},
          { 1.9893e+00,  2.1823e-01,  3.2446e-02,  2.1355e-02,  3.5300e-01,  2.9249e-01,  4.7731e-03,  7.8528e-02,  2.3627e-01,  4.4423e-02,  4.8888e-02,  6.9235e-01,  2.2748e-01,  2.0973e-01, -5.0871e+00, -4.2631e-01, -2.9089e-03,  1.5557e-01, -6.3544e-01,  1.4064e+00,  1.6347e-01,  4.3564e-02,  2.6895e-01,  2.5183e-01,  8.5525e-02,  2.0792e-02, -1.1227e-01, -7.7457e-01,  2.6193e-01,  3.2214e-02, -3.6906e-03,  2.8817e-01,  2.4701e-01,  6.2549e-02,  2.3047e-02,  5.3107e-02,  6.8346e-02,  1.7315e-02,  1.9309e-02,  1.2595e+00,  7.3103e-01,  4.5232e-01,  1.7819e-01,  2.8892e-02,  3.2266e-01,  2.0648e-01,  2.6319e-02,  6.4000e-01,  2.7208e-02,  2.8039e-01,  1.7157e-01,  3.5538e-02,  2.4196e-02,  2.3933e-02,  4.2828e-02,  2.4132e+00,  2.1412e-01,  3.2982e-01},
          { 1.5947e-01,  2.3266e-01,  3.2806e-02,  6.2684e-02,  2.0181e-01,  2.4534e-01,  1.7320e-02,  9.8002e-04,  2.0136e-01,  8.1922e-02,  6.2628e-02,  3.8358e-01,  8.0781e-02,  1.4456e-01, -3.5427e+00, -6.2615e-01,  1.8114e-01,  3.4804e-01, -1.2161e+00,  9.7202e-01,  1.3302e-01,  5.1605e-02,  8.4561e-02,  3.5820e-01,  1.0745e-01,  7.6395e-02,  6.0148e-01, -6.0172e-01,  2.9679e-01,  1.2908e-01,  3.8015e-02,  1.9937e-01,  2.1183e-01,  1.0729e-01,  2.3710e-02,  1.9718e-01,  2.4667e-02,  2.7696e-02,  2.0918e-02,  1.6073e+00,  9.2484e-01,  7.4961e-01,  2.8029e-01,  1.3402e-01,  2.9056e-01,  2.8976e-01,  2.1177e-02,  2.7208e-02,  2.5000e-01,  2.3538e-01,  2.2452e-01,  6.8978e-02,  2.7919e-02,  3.2601e-02,  7.7887e-02,  1.5728e+00,  1.6601e-01,  6.3033e-01},
          {-1.7338e+00,  2.7584e-01,  5.2245e-02,  2.4336e-04, -7.9392e-01,  4.8036e-01,  9.7246e-02,  1.5778e-01,  3.9741e-01,  2.6863e-01,  6.0171e-02,  4.3387e+00,  9.9675e-01,  1.4492e+00, -2.4358e+01, -2.6685e+00,  2.3969e-01,  7.1428e-01, -9.5843e+00,  3.0194e+00,  6.0498e-01,  6.8382e-02,  1.1663e+00,  1.8280e+00,  4.0651e-01,  5.8848e-01, -2.8335e+00,  2.9324e-01,  1.8288e+00,  3.5067e-01,  1.0415e-01,  1.2662e+00,  1.3126e+00,  4.8041e-01,  5.4198e-02,  1.5355e+00,  3.9858e-01,  1.1554e-01,  5.7930e-02,  4.1928e+01,  2.1034e+01,  6.1909e+00,  2.9682e+00,  5.1244e+00,  2.4394e+00,  9.5082e-01,  1.0576e-01,  2.8039e-01,  2.3538e-01,  9.0000e+00,  1.1735e+00,  4.6360e-01,  2.4702e-01,  6.1480e-02,  2.5723e-01,  9.6434e+00,  2.9077e+00,  5.0168e+00},
          { 1.0700e+00,  3.8442e-01,  9.1466e-02,  1.7864e-01,  2.9992e-01,  6.4254e-01,  6.5817e-02,  1.2044e-01,  3.8404e-01,  1.6517e-01,  1.7807e-01,  1.8202e+00,  5.8043e-01,  7.1440e-01, -1.7149e+01, -1.0212e+00,  6.6505e-01,  9.1648e-01, -7.7775e+00,  3.6212e+00,  3.9545e-01,  1.2577e-01,  8.1943e-01,  1.3014e+00,  5.3976e-01,  3.3715e-01,  4.9843e-01, -1.4919e+00,  1.2168e+00,  4.0688e-01,  9.2360e-02,  3.2298e-01,  9.6030e-01,  3.6310e-01,  1.0019e-01,  6.3616e-01,  2.3129e-01,  9.6664e-02,  7.4905e-02,  1.2897e+01,  7.5337e+00,  3.3181e+00,  1.2662e+00,  1.0190e+00,  1.4469e+00,  8.7496e-01,  1.8842e-01,  1.7157e-01,  2.2452e-01,  1.1735e+00,  4.0000e+00,  1.8994e-01,  1.3447e-01,  7.5570e-02,  2.1076e-01,  5.7691e+00,  6.0747e-01,  2.6524e+00},
          { 6.2759e-01,  3.3569e-01,  5.3024e-02,  5.7574e-02,  5.2470e-01,  2.2329e-01,  1.9391e-02,  1.8669e-02,  3.0246e-01,  1.1674e-01,  5.1215e-02,  8.6419e-01,  3.3382e-01,  1.7073e-01, -6.4024e+00, -1.3466e+00, -1.7140e-01,  5.6969e-02,  4.6167e-01,  1.7027e+00,  2.6216e-01,  4.0547e-02,  3.5670e-01,  2.5348e-01,  6.1790e-02, -3.1084e-02,  4.7626e-01, -8.1895e-01,  3.0374e-01,  1.0455e-01, -9.4696e-03,  7.4413e-01,  3.5265e-01,  9.1526e-02,  2.5184e-02,  1.4445e-01,  1.0355e-01,  2.8762e-02,  2.1297e-02,  4.5189e+00,  1.8827e+00,  9.6596e-01,  3.1479e-01,  7.6453e-01,  4.6960e-01,  3.1675e-01,  5.9914e-02,  3.5538e-02,  6.8978e-02,  4.6360e-01,  1.8994e-01,  4.9000e-01,  4.1938e-02,  3.2363e-02,  6.8505e-02,  1.8481e+00,  8.1477e-01,  9.9061e-01},
          { 7.4728e-01,  3.0167e-01,  1.3167e-02,  4.2592e-02,  4.7160e-01,  1.8136e-01,  9.5959e-03,  2.0451e-03,  7.1406e-02,  7.7988e-02,  2.5891e-02,  4.4247e-01,  2.1309e-01,  1.5868e-01, -2.7465e+00, -9.6329e-02,  2.1854e-01,  2.5978e-01, -1.0760e+00,  3.2563e-01,  1.1001e-01,  1.6696e-02,  3.5529e-01,  2.7984e-01,  9.9518e-02,  8.6846e-02,  4.4549e-01,  4.9226e-02,  1.5755e-01,  1.5810e-01,  3.4698e-02,  2.4649e-01,  8.7402e-02,  6.1095e-02,  1.7818e-02,  1.3322e-01,  2.7108e-02,  1.3002e-02,  1.8545e-02,  2.7222e+00,  1.3992e+00,  5.7784e-01,  2.3033e-01,  2.6775e-01,  2.4106e-01,  1.6874e-01,  1.3922e-02,  2.4196e-02,  2.7919e-02,  2.4702e-01,  1.3447e-01,  4.1938e-02,  4.9000e-01,  2.1078e-02,  4.8265e-02,  2.3183e+00,  5.1553e-01,  5.4125e-01},
          { 1.8606e-01,  9.6467e-02,  1.5586e-02,  3.5491e-02,  6.2436e-02,  1.0057e-01,  1.0994e-02,  6.0942e-03,  5.2653e-02,  4.3457e-02,  4.1385e-02,  1.4663e-01,  5.0704e-02,  5.4204e-02, -1.6814e+00, -3.6328e-02,  1.8728e-01,  1.7602e-01, -2.0508e-01,  7.4911e-01,  8.8506e-02,  2.9372e-02,  5.5211e-02,  2.1766e-01,  7.7694e-02,  5.0152e-02,  8.0288e-01, -4.3766e-01,  1.9859e-01,  8.1738e-02,  1.3894e-02,  9.8753e-02,  1.2742e-01,  7.2930e-02,  1.4376e-02,  8.6400e-02, -1.9789e-03,  1.0803e-02,  1.3415e-02,  4.9007e-01,  3.4984e-01,  3.5374e-01,  1.2113e-01, -9.7142e-02,  2.1394e-01,  1.6081e-01,  2.0350e-02,  2.3933e-02,  3.2601e-02,  6.1480e-02,  7.5570e-02,  3.2363e-02,  2.1078e-02,  9.0000e-02,  3.7882e-02,  1.0447e+00,  6.2922e-02,  2.8876e-01},
          {-8.1154e-02,  1.5209e-01,  3.4236e-02,  6.5536e-02,  3.2349e-02,  1.7125e-01,  1.6326e-02, -2.7258e-02,  1.3980e-01,  6.9160e-02,  7.9098e-02,  3.8166e-01,  1.0392e-01,  1.5064e-01, -3.9358e+00, -1.8873e-01,  3.6617e-01,  4.3992e-01, -1.6588e+00,  8.4511e-01,  1.0472e-01,  5.2345e-02,  1.5782e-01,  4.4670e-01,  1.6208e-01,  1.3240e-01,  1.3386e+00, -4.6259e-01,  4.9734e-01,  1.7631e-01,  3.9110e-02,  7.3916e-02,  2.2941e-01,  1.3220e-01,  2.5726e-02,  2.4936e-01, -6.8146e-04,  3.1368e-02,  2.2290e-02,  3.4618e+00,  1.6711e+00,  1.0356e+00,  3.5233e-01,  1.7026e-01,  4.1701e-01,  3.3807e-01,  3.6248e-02,  4.2828e-02,  7.7887e-02,  2.5723e-01,  2.1076e-01,  6.8505e-02,  4.8265e-02,  3.7882e-02,  2.5000e-01,  1.8907e+00,  1.1872e-01,  6.5517e-01},
          { 1.1833e+02,  2.1285e+01,  3.6964e+00,  2.1077e+00,  5.0472e+01,  1.6375e+01,  4.2150e-01,  4.9808e+00,  1.9787e+01,  3.9476e+00,  1.8399e+00,  3.6278e+01,  1.3548e+01,  1.1621e+01,  5.5155e+01,  4.6705e+01,  2.6746e+01,  2.0079e+01,  6.4483e-02,  4.1004e+01,  5.7544e+00,  1.9107e+00,  1.9604e+01,  3.8533e+01,  9.0707e+00,  9.2194e+00,  6.8049e+01,  1.0930e+01,  2.1958e+01,  1.0214e+01,  2.0708e+00,  8.3892e+00,  7.9997e+00,  4.5543e+00,  1.0905e+00,  1.1251e+01,  1.4687e+00,  9.4777e-01,  1.3624e+00,  6.5881e+01,  6.3538e+01,  2.8116e+01,  5.1535e+00, -1.1808e+01,  1.2416e+01,  9.7175e+00,  2.1084e+00,  2.4132e+00,  1.5728e+00,  9.6434e+00,  5.7691e+00,  1.8481e+00,  2.3183e+00,  1.0447e+00,  1.8907e+00,  4.4100e+02,  4.1720e+01,  2.8208e+01},
          { 4.8905e+00,  5.4594e+00,  7.0119e-01,  4.8013e-01,  1.1472e+01,  1.6862e+00,  3.5258e-01,  1.8092e+00,  3.7174e+00,  1.6136e+00,  8.9187e-02,  6.9917e+00,  5.2002e+00,  1.3906e+00, -9.6980e+00,  1.7218e+01,  2.3659e+00,  1.1654e+00, -1.9495e+01,  1.7531e+01,  4.3268e+00,  9.0790e-02,  8.5764e+00,  8.9562e+00,  2.5175e+00,  2.3758e+00, -3.9013e+01,  2.6212e+00,  2.8238e+00,  1.6527e+00,  6.8463e-01,  7.4502e+00,  2.1334e+00,  6.4310e-01,  1.2001e-01,  6.7728e-01,  2.4176e+00,  1.4269e-01,  2.5994e-01, -1.5056e+01,  1.6604e+01,  4.4079e+00,  3.8126e-01, -1.9100e+00,  1.6312e+00,  1.2664e+00,  8.1357e-01,  2.1412e-01,  1.6601e-01,  2.9077e+00,  6.0747e-01,  8.1477e-01,  5.1553e-01,  6.2922e-02,  1.1872e-01,  4.1720e+01,  4.9000e+01,  8.9468e+00},
          {-5.9351e+00,  1.8844e+00,  1.8055e-01,  5.2531e-01, -2.5530e-01,  1.2828e+00,  3.9758e-01,  4.2982e-01,  1.0299e+00,  7.9169e-01,  4.3476e-01,  3.6857e+00,  1.4053e+00,  1.7168e+00, -3.3763e+01,  9.0619e+00,  4.2402e+00,  4.3716e+00, -2.5121e+01,  1.8704e+01,  2.3870e+00,  3.1365e-01,  5.7456e+00,  8.8350e+00,  2.5858e+00,  3.0283e+00, -8.6263e+00, -2.7373e-01,  1.0042e+01,  1.8856e+00,  6.7836e-01, -3.9815e-01,  3.8851e+00,  1.3437e+00,  2.0365e-01,  3.1638e+00,  9.3943e-01,  4.5048e-01,  2.6030e-01,  3.7666e+01,  3.2475e+01,  1.2473e+01,  4.2208e+00,  2.1701e+00,  5.4428e+00,  3.8938e+00,  9.4853e-01,  3.2982e-01,  6.3033e-01,  5.0168e+00,  2.6524e+00,  9.9061e-01,  5.4125e-01,  2.8876e-01,  6.5517e-01,  2.8208e+01,  8.9468e+00,  3.6000e+01},
        };

        set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb)


  }
}
