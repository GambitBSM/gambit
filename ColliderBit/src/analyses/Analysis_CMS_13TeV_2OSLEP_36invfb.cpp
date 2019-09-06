///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  Updated to paper analysis by Martin White
///  Mar 2018
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-034/index.html
// Note that only the EW on-Z signal regions are included

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is also a base class for the class
    // Analysis_CMS_13TeV_2OSLEP_36invfb_nocovar defined further down.
    // This is the same analysis, but it does not make use of the
    // SR covariance information.
    class Analysis_CMS_13TeV_2OSLEP_36invfb : public Analysis {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SR1", 0},
        {"SR2", 0},
        {"SR3", 0},
        {"SR4", 0},
        {"SR5", 0},
        {"SR6", 0},
        {"SR7", 0},
      };

    private:

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      size_t NCUTS;
      vector<double> cutFlowVectorCMS_550_200;

      ofstream cutflowFile;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison {
        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      Analysis_CMS_13TeV_2OSLEP_36invfb()
      {
        set_analysis_name("CMS_13TeV_2OSLEP_36invfb");
        set_luminosity(35.9);
        // xsecCMS_550_200=30.2;

        NCUTS=13;

        for (size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVectorCMS_550_200.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }


      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        double met = event->met();

        // Apply electron efficiency and collect baseline electrons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_034_ttbar.pdf.
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 10., 20., 25., 30., 40., 50., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cEl={
                          // pT: (0,10),  (10,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                    0.0,    0.95,    0.619,     0.669,    0.7,     0.737,    0.79,  // eta: (0, 0.8)
                                    0.0,    0.95,    0.625,     0.658,    0.72,    0.712,    0.793, // eta: (0.8, 1.4429
                                    0.0,    0.95,    0.338,     0.372,    0.36,    0.365,    0.416, // eta: (1.442, 1.556)
                                    0.0,    0.85,    0.576,     0.531,    0.614,   0.644,    0.712, // eta: (1.556, 2)
                                    0.0,    0.85,    0.440,     0.527,    0.585,   0.606,    0.648, // eta: (2, 2.5)
                                    0.0,    0.0,     0.0,       0.0,      0.0,     0.0,      0.0,   // eta > 2.5
                                  };
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons())
        {
          bool isEl=has_tag(_eff2dEl, electron->eta(), electron->pT());
          if (isEl && electron->pT()>12. && fabs(electron->eta())<2.5) baselineElectrons.push_back(electron);
        }


        // Apply muon efficiency and collect baseline muons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_034_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 10., 20., 25., 30., 40., 50., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cMu={
                           // pT:   (0,10),  (10,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                     0.0,    0.950,    0.869,    0.889,    0.910,    0.929,    0.930,  // eta: (0, 0.9)
                                     0.0,    0.950,    0.857,    0.880,    0.893,    0.937,    0.930,  // eta: (0.9, 1.2)
                                     0.0,    0.950,    0.891,    0.894,    0.901,    0.912,    0.927,  // eta: (1.2, 2.1)
                                     0.0,    0.950,    0.803,    0.818,    0.817,    0.855,    0.869,  // eta: (2.1, 2.4)
                                     0.0,    0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.4
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons())
        {
          bool isMu=has_tag(_eff2dMu, muon->eta(), muon->pT());
          if (isMu && muon->pT()>8. && fabs(muon->eta())<2.4) baselineMuons.push_back(muon);
        }

        // Baseline photons
        vector<HEPUtils::Particle*> baselinePhotons;
        for (HEPUtils::Particle* photon : event->photons())
        {
          if (photon->pT()>25. && fabs(photon->eta())<2.4 && (fabs(photon->eta())<1.4 || fabs(photon->eta())>1.6) && fabs(photon->phi()-event->missingmom().phi())>0.4)baselinePhotons.push_back(photon);
        }

        // Baseline jets
        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets())
        {
          // We use 25 GeV rather than 35 GeV
          // if (jet->pT()>35. &&fabs(jet->eta())<2.4) baselineJets.push_back(jet);
          if (jet->pT()>25. &&fabs(jet->eta())<2.4) baselineJets.push_back(jet);
        }


        // Signal objects
        vector<HEPUtils::Particle*> signalLeptons;
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> signalBJets;

        // Signal electrons
        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++)
        {
          if (baselineElectrons.at(iEl)->pT()>20. && (fabs(baselineElectrons.at(iEl)->eta())<1.4 || fabs(baselineElectrons.at(iEl)->eta())>1.6)) signalElectrons.push_back(baselineElectrons.at(iEl));
        }

        // Signal muons
        for (size_t iMu=0;iMu<baselineMuons.size();iMu++)
        {
          if (baselineMuons.at(iMu)->pT()>20. && (fabs(baselineMuons.at(iMu)->eta())<1.4 || fabs(baselineMuons.at(iMu)->eta())>1.6))signalMuons.push_back(baselineMuons.at(iMu));
        }

        // Signal jets and b-jets
        sort(baselinePhotons.begin(),baselinePhotons.end(),comparePt);
        for (size_t iJet=0;iJet<baselineJets.size();iJet++)
        {
          bool overlap=false;
          for (size_t iLe=0;iLe<baselineElectrons.size();iLe++)
          {
            if (fabs(baselineElectrons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          for (size_t iLe=0;iLe<baselineMuons.size();iLe++)
          {
            if (fabs(baselineMuons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          if (baselinePhotons.size()!=0)
          {
            if (fabs(baselinePhotons.at(0)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          if (!overlap) {
            if (baselineJets.at(iJet)->pT() >= 35.)
            {
              signalJets.push_back(baselineJets.at(iJet));
            }
            // For the b-jets, jets down to pT > 25 should be considered
            if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
          }
        }
        CMS::applyCSVv2MediumBtagEffAndMisId(signalJets,signalBJets);

        // Signal leptons = electrons + muons
        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        int nSignalLeptons = signalLeptons.size();
        int nSignalJets = signalJets.size();
        int nSignalBJets = signalBJets.size();
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
        sort(signalJets.begin(),signalJets.end(),compareJetPt);
        sort(signalBJets.begin(),signalBJets.end(),compareJetPt);

        // Variables + Preselection
        bool preselection=false;

        double mT2=0;
        double mll=0;
        double mjj=0;
        double mbb=0;
        double pT_j1=0;
        double deltaPhi_met_j0=0;
        double deltaPhi_met_j1=0;

        // When picking out the SFOS lepton pair, should we loop through all leptons (use function getSFOSpairs)
        // or only check the two leptons with highest PT, as we currently do below?

        // vector<vector<HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
        vector<vector<HEPUtils::Particle*>> SFOSpair_cont;
        if (signalLeptons.size() >= 2)
        {
          if (signalLeptons.at(0)->abspid()==signalLeptons.at(1)->abspid() && signalLeptons.at(0)->pid()!=signalLeptons.at(1)->pid())
          {
            vector<HEPUtils::Particle*> SFOSpair;
            SFOSpair.push_back(signalLeptons.at(0));
            SFOSpair.push_back(signalLeptons.at(1));
            SFOSpair_cont.push_back(SFOSpair);
          }
        }

        for (size_t iPa=0;iPa<SFOSpair_cont.size();iPa++)
        {
          vector<HEPUtils::Particle*> pair = SFOSpair_cont.at(iPa);
          sort(pair.begin(),pair.end(),comparePt);
          if (pair.at(0)->pT()>25. && pair.at(1)->pT()>20. && fabs(pair.at(0)->mom().deltaR_eta(pair.at(1)->mom()))>0.1 && (pair.at(0)->mom()+pair.at(1)->mom()).pT()>25) preselection=true;
        }

        if (nSignalBJets>1)mbb=(signalBJets.at(0)->mom()+signalBJets.at(1)->mom()).m();
        if (nSignalJets>0)deltaPhi_met_j0=event->missingmom().deltaPhi(signalJets.at(0)->mom());
        if (nSignalJets>1)
        {
          pT_j1=signalJets.at(1)->pT();
          deltaPhi_met_j1=event->missingmom().deltaPhi(signalJets.at(1)->mom());
          mjj=get_mjj(signalJets);
        }


        if (nSignalLeptons>1)
        {
          mT2=get_mT2(signalLeptons,signalBJets,event->missingmom());
        }
        if (SFOSpair_cont.size() > 0)
        {
          mll=(SFOSpair_cont.at(0).at(0)->mom()+SFOSpair_cont.at(0).at(1)->mom()).m();
        }

        //Signal regions
        if (preselection && mll>86. && mll<96. && met>100. && nSignalJets>=2  && (baselineMuons.size()+baselineElectrons.size())==2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4)
        {
          //VZ
          if (nSignalBJets==0 && mT2>80. && mjj<110.)
          {
            if (met>100. && met<150.) _numSR["SR1"]++;
            if (met>150. && met<250.) _numSR["SR2"]++;
            if (met>250. && met<350.) _numSR["SR3"]++;
            if (met>350.) _numSR["SR4"]++;
          }
          //HZ
          if (nSignalBJets==2 && mbb<150. && mT2>200.)
          {
            if (met>100. && met<150.) _numSR["SR5"]++;
            if (met>150. && met<250.) _numSR["SR6"]++;
            if (met>250.) _numSR["SR7"]++;
          }
        }

        cutFlowVector_str[0] = "All events";
        cutFlowVector_str[1] = "$\\geq$ 2 SFOS leptons with (sub)leading $p_{T} > 25(20) GeV$";
        cutFlowVector_str[2] = "Extra lepton vetos";
        cutFlowVector_str[3] = "$86 < m_{ll} < 96 GeV$";
        cutFlowVector_str[4] = "2-3 Jets";
        cutFlowVector_str[5] = "$\\Delta\\Phi(E^{miss}_{T},j_{0}),\\Delta\\Phi(E^{miss}_{T},j_{1}) > 0.4$";
        cutFlowVector_str[6] = "Btag veto";
        cutFlowVector_str[7] = "$M_{T2}(ll) > 80 GeV$";
        cutFlowVector_str[8] = "$M_{jj}$ for min $\\Delta\\Phi$ jets $< 150 GeV$";
        cutFlowVector_str[9] = "$E^{miss}_{T} > 100 GeV$";
        cutFlowVector_str[10] = "$E^{miss}_{T} > 150 GeV$";
        cutFlowVector_str[11] = "$E^{miss}_{T} > 250 GeV$";
        cutFlowVector_str[12] = "$E^{miss}_{T} > 350 GeV$";

        cutFlowVectorCMS_550_200[0] = 109.35;
        cutFlowVectorCMS_550_200[1] = 24.21;
        cutFlowVectorCMS_550_200[2] = 18.37;
        cutFlowVectorCMS_550_200[3] = 14.13;
        cutFlowVectorCMS_550_200[4] = 11.98;
        cutFlowVectorCMS_550_200[5] = 10.95;
        cutFlowVectorCMS_550_200[6] = 9.92;
        cutFlowVectorCMS_550_200[7] = 8.04;
        cutFlowVectorCMS_550_200[8] = 5.62;
        cutFlowVectorCMS_550_200[9] = 5.41;
        cutFlowVectorCMS_550_200[10] = 4.96;
        cutFlowVectorCMS_550_200[11] = 3.59;
        cutFlowVectorCMS_550_200[12] = 1.94;

        for (size_t j=0;j<NCUTS;j++)
        {
          if(
            (j==0) ||

            (j==1 && preselection) ||

            (j==2 && preselection && (baselineMuons.size()+baselineElectrons.size())==2) ||

            (j==3 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96.) ||

            (j==4 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35.) ||

            (j==5 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4) ||

            (j==6 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0) ||

            (j==7 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80.) ||

            (j==8 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<110.) ||

            (j==9 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<110. && met>100.) ||

            (j==10 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<110. && met>150.) ||

            (j==11 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<110. && met>250.) ||

            (j==12 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && nSignalJets>=2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<110. && met>350.)
            )

          cutFlowVector[j]++;
        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2OSLEP_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2OSLEP_36invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j = 0; j < NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }

        for (auto& el : _numSR) {
          el.second += specificOther->_numSR.at(el.first);
        }

      }


      virtual void collect_results()
      {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1", 57., {_numSR["SR1"], 0.}, {54.9, 7.}));
        add_result(SignalRegionData("SR2", 29., {_numSR["SR2"], 0.}, {21.6, 5.6}));
        add_result(SignalRegionData("SR3", 2.,  {_numSR["SR3"], 0.}, {6., 1.9}));
        add_result(SignalRegionData("SR4", 0.,  {_numSR["SR4"], 0.}, {2.5, 0.9}));
        add_result(SignalRegionData("SR5", 9.,  {_numSR["SR5"], 0.}, {7.6, 2.8}));
        add_result(SignalRegionData("SR6", 5.,  {_numSR["SR6"], 0.}, {5.6, 1.6}));
        add_result(SignalRegionData("SR7", 1.,  {_numSR["SR7"], 0.}, {1.3, 0.4}));

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 52.8, 12.7,  3.0,  1.2,  4.5,  5.1,  1.2},
          { 12.7, 41.4,  3.6,  2.0,  2.5,  2.0,  0.7},
          {  3.0,  3.6,  1.6,  0.6,  0.4,  0.3,  0.1},
          {  1.2,  2.0,  0.6,  1.1,  0.3,  0.1,  0.1},
          {  4.5,  2.5,  0.4,  0.3,  6.5,  1.8,  0.4},
          {  5.1,  2.0,  0.3,  0.1,  1.8,  2.4,  0.4},
          {  1.2,  0.7,  0.1,  0.1,  0.4,  0.4,  0.2},
        };

        set_covariance(BKGCOV);
      }



      double get_mjj(vector<HEPUtils::Jet*> jets) {
        double mjj=0;
        double deltaPhi_min=999;
        for (size_t iJet1=0;iJet1<jets.size();iJet1++) {
          for (size_t iJet2=0;iJet2<jets.size();iJet2++) {
             if (iJet1!=iJet2) {
               double deltaPhi=fabs(jets.at(iJet1)->phi()-jets.at(iJet2)->phi());
               if (deltaPhi<deltaPhi_min) {
                 mjj=(jets.at(iJet1)->mom()+jets.at(iJet2)->mom()).m();
                 deltaPhi_min=deltaPhi;
               }
             }
           }
        }
        return mjj;
      }

      double get_mT2(vector<HEPUtils::Particle*> leptons, vector<HEPUtils::Jet*> bjets, HEPUtils::P4 met) {
        double mT2=0;
        if (bjets.size()<2) {
          double pLep0[3] = {leptons.at(0)->mass(), leptons.at(0)->mom().px(), leptons.at(0)->mom().py()};
          double pLep1[3] = {leptons.at(1)->mass(), leptons.at(1)->mom().px(), leptons.at(1)->mom().py()};
          double pMiss[3] = {0., met.px(), met.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep0,pLep1,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
        }
        if (bjets.size()>1) {
          mT2=999;
          for (size_t iJet=0;iJet<bjets.size();iJet++) {
            for (size_t iLep=0;iLep<leptons.size();iLep++) {
              double pLep[3] = {leptons.at(iLep)->mass(), leptons.at(iLep)->mom().px(), leptons.at(iLep)->mom().py()};
              double pJet[3] = {bjets.at(iJet)->mass(), bjets.at(iJet)->mom().px(), bjets.at(iJet)->mom().py()};
              double pMiss[3] = {0., met.px(), met.py() };
              double mn = 0.;

              mt2_bisect::mt2 mt2_calc;
              mt2_calc.set_momenta(pLep,pJet,pMiss);
              mt2_calc.set_mn(mn);
              double mT2_temp = mt2_calc.get_mt2();
              if (mT2_temp<mT2)mT2=mT2_temp;
            }
          }
        }
        return mT2;
      }


    protected:
      void analysis_specific_reset() {

        for (auto& el : _numSR) { el.second = 0.;}

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_36invfb)



    //
    // Derived analysis class that does not make use of the SR covariance matrix
    //
    class Analysis_CMS_13TeV_2OSLEP_36invfb_nocovar : public Analysis_CMS_13TeV_2OSLEP_36invfb {

    public:
      Analysis_CMS_13TeV_2OSLEP_36invfb_nocovar() {
        set_analysis_name("CMS_13TeV_2OSLEP_36invfb_nocovar");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1", 57., {_numSR["SR1"], 0.}, {54.9, 7.}));
        add_result(SignalRegionData("SR2", 29., {_numSR["SR2"], 0.}, {21.6, 5.6}));
        add_result(SignalRegionData("SR3", 2.,  {_numSR["SR3"], 0.}, {6., 1.9}));
        add_result(SignalRegionData("SR4", 0.,  {_numSR["SR4"], 0.}, {2.5, 0.9}));
        add_result(SignalRegionData("SR5", 9.,  {_numSR["SR5"], 0.}, {7.6, 2.8}));
        add_result(SignalRegionData("SR6", 5.,  {_numSR["SR6"], 0.}, {5.6, 1.6}));
        add_result(SignalRegionData("SR7", 1.,  {_numSR["SR7"], 0.}, {1.3, 0.4}));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_36invfb_nocovar)


  }
}
