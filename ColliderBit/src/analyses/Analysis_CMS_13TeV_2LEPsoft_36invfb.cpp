///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Are Raklev
///  \date 2018 June
///
///  \author Anders Kvellestad
///  \date 2018 June
///
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-16-048/index.html

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
    // Analysis_CMS_13TeV_2LEPsoft_36invfb_nocovar defined further down.
    // This is the same analysis, but it does not make use of the
    // SR covariance information.
    class Analysis_CMS_13TeV_2LEPsoft_36invfb : public Analysis {

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
        {"SR8", 0},
        {"SR9", 0},
        {"SR10", 0},
        {"SR11", 0},
        {"SR12", 0},
      };

    private:

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      size_t NCUTS;
      vector<double> cutFlowVectorCMS_150_130;
      // double xsecCMS_150_143;
      // double xsecCMS_150_130;

      // ofstream cutflowFile;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      Analysis_CMS_13TeV_2LEPsoft_36invfb() {

        set_analysis_name("CMS_13TeV_2LEPsoft_36invfb");
        set_luminosity(35.9);

        NCUTS=14;
        // xsecCMS_150_143=5180.;
        // xsecCMS_150_130=5180.;

        for (size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVectorCMS_150_130.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }


      void run(const HEPUtils::Event* event) {

        double met = event->met();

        // Signal objects
        vector<HEPUtils::Particle*> signalLeptons;
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> signalBJets;

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_048_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 5., 10., 15., 20., 25., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cEl={
                          // pT:  (0,5),  (5,10),  (10,15),  (15,20),  (20,25),  (25,inf)
                                   0.0,    0.336,   0.412,    0.465,    0.496,    0.503,   // eta: (0, 0.8)
                                   0.0,    0.344,   0.402,    0.448,    0.476,    0.482,   // eta: (0.8, 1.4429)
                                   0.0,    0.233,   0.229,    0.250,    0.261,    0.255,   // eta: (1.442, 1.556)
                                   0.0,    0.309,   0.359,    0.394,    0.408,    0.418,   // eta: (1.556, 2)
                                   0.0,    0.243,   0.287,    0.327,    0.341,    0.352,   // eta: (2, 2.5)
                                   0.0,    0.0,     0.0,      0.0,      0.0,      0.0,     // eta > 2.5
                                  };
        // const vector<double> aEl={0,0.8,1.442,1.556,2.,2.5};
        // const vector<double> bEl={5.,10.,15.,20.,25.,DBL_MAX};  // Assuming flat efficiency above pT = 30 GeV, where the CMS map stops.
        // const vector<double> cEl={0.336,0.412,0.465,0.496,0.503,0.344,0.402,0.448,0.476,0.482,0.233,0.299,0.25,0.261,0.255,0.309,0.359,0.394,0.408,0.418,0.243,0.287,0.327,0.341,0.352};
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        for (HEPUtils::Particle* electron : event->electrons()) {
          bool isEl=has_tag(_eff2dEl,electron->eta(),electron->pT());
          if (electron->pT()>5. && electron->pT()<30. && fabs(electron->eta())<2.5 && isEl)signalElectrons.push_back(electron);
        }

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_048_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 3.5, 10., 15., 20., 25., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cMu={
                          // pT:  (0,3.5),  (3.5,10),  (10,15),  (15,20),  (20,25),  (25,inf)
                                   0.0,      0.647,     0.718,    0.739,    0.760,    0.763,    // eta: (0, 0.9)
                                   0.0,      0.627,     0.662,    0.694,    0.725,    0.733,    // eta: (0.9, 1.2)
                                   0.0,      0.610,     0.660,    0.678,    0.685,    0.723,    // eta: (1.2, 2.1)
                                   0.0,      0.566,     0.629,    0.655,    0.670,    0.696,    // eta: (2.1, 2.4)
                                   0.0,      0.0,       0.0,      0.0,      0.0,      0.0,      // eta > 2.4
                                  };
        // const vector<double> aMu={0.,0.9,1.2,2.1,2.4};
        // const vector<double> bMu={3.5,10.,15.,20.,25.,DBL_MAX};  // Assuming flat efficiency above pT = 30 GeV, where the CMS map stops.
        // const vector<double> cMu={0.647,0.718,0.739,0.76,0.763,0.627,0.662,0.694,0.725,0.733,0.61,0.66,0.678,0.685,0.723,0.566,0.629,0.655,0.67,0.696};
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        for (HEPUtils::Particle* muon : event->muons()) {
          bool isMu=has_tag(_eff2dMu,muon->eta(),muon->pT());
          if (muon->pT()>5. && muon->pT()<30. && fabs(muon->eta())<2.4 && isMu) signalMuons.push_back(muon);
        }

        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT()>25. && fabs(jet->eta())<2.4) {
           signalJets.push_back(jet);
           if (jet->btag())signalBJets.push_back(jet);
          }
        }
        // Apply b-tag efficiencies and b-tag misidentification rate
        // for the CSVv2Loose working point
        CMS::applyCSVv2LooseBtagEffAndMisId(signalJets,signalBJets);

        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
        size_t nSignalLeptons=signalLeptons.size();
        size_t nSignalMuons=signalMuons.size();
        size_t nSignalJets=signalJets.size();
        size_t nSignalBJets=signalBJets.size();

        // Cut variables
        double m_ll=0;
        double pT_ll=0;
        double hT=0;
        double mTauTau=0;
        double metcorr=0;
        vector<double> mT;

        bool preselection=false;
        bool OS=false;

        // Muon corrected ETmiss
        double metcorrx = event->missingmom().px();
        double metcorry = event->missingmom().py();
        for (size_t iLep=0;iLep<nSignalMuons;iLep++){
          metcorrx += signalMuons.at(iLep)->mom().px();
          metcorry += signalMuons.at(iLep)->mom().py();
        }
        metcorr = sqrt(metcorrx*metcorrx+metcorry*metcorry);


        if (nSignalLeptons == 2) {
          m_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).m();
          pT_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).pT();

          // Calculation of $M_{\tau\tau}$ variable
          double determinant = signalLeptons.at(0)->mom().px()*signalLeptons.at(1)->mom().py()-signalLeptons.at(0)->mom().py()*signalLeptons.at(1)->mom().px();
          double xi_1 = (event->missingmom().px()*signalLeptons.at(1)->mom().py()-signalLeptons.at(1)->mom().px()*event->missingmom().py())/determinant;
          double xi_2 = (event->missingmom().py()*signalLeptons.at(0)->mom().px()-signalLeptons.at(0)->mom().py()*event->missingmom().px())/determinant;
          mTauTau = (1.+xi_1)*(1.+xi_2)*2*signalLeptons.at(0)->mom().dot(signalLeptons.at(1)->mom());
          if(mTauTau > 0) mTauTau = sqrt(mTauTau);
          if(mTauTau < 0) mTauTau = -sqrt(-mTauTau);
        }

        for (size_t iJet=0;iJet<nSignalJets;iJet++)hT+=signalJets.at(iJet)->pT();

        for (size_t iLep=0;iLep<nSignalLeptons;iLep++)mT.push_back(sqrt(2*signalLeptons.at(iLep)->pT()*met*(1-cos(signalLeptons.at(iLep)->phi()-event->missingmom().phi()))));
        if (nSignalLeptons==0) {
          mT.push_back(999);
          mT.push_back(999);
        }
        if (nSignalLeptons==1)mT.push_back(999);

        if (nSignalLeptons==2) OS=signalLeptons.at(0)->pid()*signalLeptons.at(1)->pid()<0.;

        if (nSignalLeptons==2 && nSignalBJets==0 && nSignalJets>0) {
          if (OS && signalLeptons.at(0)->abspid()==signalLeptons.at(1)->abspid()) {
            if (m_ll<50. && pT_ll>3. && met>125. && metcorr > 125. && met/hT<1.4 && met/hT>0.6 && hT>100. && m_ll>4. && (m_ll<9. || m_ll>10.5) && (mTauTau<0. || mTauTau>160.) && mT.at(0)<70. && mT.at(1)<70.) {
              preselection=true;
            }
          }
        }


        // Signal Regions
        // In the low ETmiss region, for each passing event we add 0.65 due to trigger efficiency
        if (preselection && met>125. && met<200. && nSignalMuons == 2) {
          if (m_ll>4. && m_ll<10.) _numSR["SR1"] += 0.65;
          if (m_ll>10. && m_ll<20.) _numSR["SR2"] += 0.65;
          if (m_ll>20. && m_ll<30.) _numSR["SR3"] += 0.65;
          if (m_ll>30. && m_ll<50.) _numSR["SR4"] += 0.65;
        }
        if (preselection && met>200. && met<250.) {
          if (m_ll>4. && m_ll<10.) _numSR["SR5"]++;
          if (m_ll>10. && m_ll<20.) _numSR["SR6"]++;
          if (m_ll>20. && m_ll<30.) _numSR["SR7"]++;
          if (m_ll>30. && m_ll<50.) _numSR["SR8"]++;
        }
        if (preselection && met>250.) {
          if (m_ll>4. && m_ll<10.) _numSR["SR9"]++;
          if (m_ll>10. && m_ll<20.) _numSR["SR10"]++;
          if (m_ll>20. && m_ll<30.) _numSR["SR11"]++;
          if (m_ll>30. && m_ll<50.) _numSR["SR12"]++;
        }

        cutFlowVector_str[0] = "All events";
        cutFlowVector_str[1] = "2 reconstructed $\\mu$'s with $5 < p_{T} < 30$ GeV";
        cutFlowVector_str[2] = "$\\mu$'s oppositely charged";
        cutFlowVector_str[3] = "$p_{T}(\\mu\\mu) > 3$ GeV";
        cutFlowVector_str[4] = "$M(\\mu\\mu) \\in [4,50]$ GeV";
        cutFlowVector_str[5] = "$M(\\mu\\mu)$ veto [9,10.5] $GeV$";
        cutFlowVector_str[6] = "$125 < p^{miss}_{T} < 200$ GeV";
        cutFlowVector_str[7] = "Trigger. Implemented as efficiency.";
        cutFlowVector_str[8] = "ISR jet";
        cutFlowVector_str[9] = "$H_{T} > 100$ GeV";
        cutFlowVector_str[10] = "$0.6 < p^{miss}_{T}/H_{T} < 1.4$";
        cutFlowVector_str[11] = "b-tag veto";
        cutFlowVector_str[12] = "$M(\\tau\\tau)$ veto";
        cutFlowVector_str[13] = "$M_{T}(\\mu_{x},p^{miss}_{T}), x = 1,2 < 70$ GeV";


        // Cut flow from CMS email
        cutFlowVectorCMS_150_130[0] = 172004.;
        cutFlowVectorCMS_150_130[1] = 1250.4;
        cutFlowVectorCMS_150_130[2] = 1199.6;
        cutFlowVectorCMS_150_130[3] = 1176.0;
        cutFlowVectorCMS_150_130[4] = 1095.2;
        cutFlowVectorCMS_150_130[5] = 988.6;
        cutFlowVectorCMS_150_130[6] = 46.8;
        cutFlowVectorCMS_150_130[7] = 30.7;
        cutFlowVectorCMS_150_130[8] = 27.9;
        cutFlowVectorCMS_150_130[9] = 23.6;
        cutFlowVectorCMS_150_130[10] = 17.2;
        cutFlowVectorCMS_150_130[11] = 14.0;
        cutFlowVectorCMS_150_130[12] = 12.3;
        cutFlowVectorCMS_150_130[13] = 9.3;

        for (size_t j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && nSignalMuons==2) ||

             (j==2 && nSignalMuons==2 && OS) ||

             (j==3 && nSignalMuons==2 && OS && pT_ll>3.) ||

             (j==4 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.)) ||

             (j==5 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5)) ||

             (j==6 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.)) ||

             (j==7 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.)) ||

             (j==8 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0) ||

             (j==9 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0 && hT>100.) ||

             (j==10 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0 && hT>100. && (met/hT<1.4 && met/hT>0.6)) ||

             (j==11 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0 && hT>100. && (met/hT<1.4 && met/hT>0.6) && nSignalBJets==0) ||

             (j==12 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0 && hT>100. && (met/hT<1.4 && met/hT>0.6) && nSignalBJets==0  && (mTauTau<0. || mTauTau>160.)) ||

             (j==13 && nSignalMuons==2 && OS && pT_ll>3. && (m_ll>4. && m_ll<50.) && (m_ll<9. || m_ll>10.5) && (met>125. && metcorr > 125. && met<200.) && nSignalJets>0 && hT>100. && (met/hT<1.4 && met/hT>0.6) && nSignalBJets==0  && (mTauTau<0. || mTauTau>160.) && (mT.at(0)<70. && mT.at(1)<70.)))
          cutFlowVector[j]++;
        }
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2LEPsoft_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2LEPsoft_36invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j = 0; j < NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }

        for (auto& el : _numSR) {
          el.second += specificOther->_numSR.at(el.first);
        }

      }


      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1",  2.,  {_numSR["SR1"],  0.}, {3.5, 1.}));
        add_result(SignalRegionData("SR2",  15., {_numSR["SR2"],  0.}, {12, 2.3}));
        add_result(SignalRegionData("SR3",  19., {_numSR["SR3"],  0.}, {17, 2.4}));
        add_result(SignalRegionData("SR4",  18., {_numSR["SR4"],  0.}, {11, 2.}));
        add_result(SignalRegionData("SR5",  1.,  {_numSR["SR5"],  0.}, {1.6, 0.7}));
        add_result(SignalRegionData("SR6",  0.,  {_numSR["SR6"],  0.}, {3.5, 0.9}));
        add_result(SignalRegionData("SR7",  3.,  {_numSR["SR7"],  0.}, {2., 0.7}));
        add_result(SignalRegionData("SR8",  1.,  {_numSR["SR8"],  0.}, {0.51, 0.52}));
        add_result(SignalRegionData("SR9",  2.,  {_numSR["SR9"],  0.}, {1.4, 0.7}));
        add_result(SignalRegionData("SR10", 1.,  {_numSR["SR10"], 0.}, {1.5, 0.6}));
        add_result(SignalRegionData("SR11", 2.,  {_numSR["SR11"], 0.}, {1.5, 0.8}));
        add_result(SignalRegionData("SR12", 0.,  {_numSR["SR12"], 0.}, {1.2, 0.6}));

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 1.29, 0.33, 0.45, 0.49, 0.06, 0.09, 0.12, 0.08, 0.12, 0.09, 0.07, 0.12 },
          { 0.33, 5.09, 1.01, 0.62, 0.12, 0.13, 0.20, 0.12, 0.12, 0.11, 0.15, 0.13 },
          { 0.45, 1.01, 6.44, 0.78, 0.21, 0.19, 0.18, 0.10, 0.18, 0.18, 0.15, 0.19 },
          { 0.49, 0.62, 0.78, 3.60, 0.09, 0.07, 0.12, 0.19, 0.19, 0.13, 0.17, 0.32 },
          { 0.06, 0.12, 0.21, 0.09, 0.59, 0.03, 0.06, 0.03, 0.02, 0.03, 0.03, 0.03 },
          { 0.09, 0.13, 0.19, 0.07, 0.03, 0.72, 0.03, 0.03, 0.03, 0.04, 0.03, 0.01 },
          { 0.12, 0.20, 0.18, 0.12, 0.06, 0.03, 0.60, 0.05, 0.04, 0.05, 0.04, 0.05 },
          { 0.08, 0.12, 0.10, 0.19, 0.03, 0.03, 0.05, 0.17, 0.05, 0.03, 0.04, 0.06 },
          { 0.12, 0.12, 0.18, 0.19, 0.02, 0.03, 0.04, 0.05, 0.26, 0.05, 0.07, 0.07 },
          { 0.09, 0.11, 0.18, 0.13, 0.03, 0.04, 0.05, 0.03, 0.05, 0.32, 0.05, 0.04 },
          { 0.07, 0.15, 0.15, 0.17, 0.03, 0.03, 0.04, 0.04, 0.07, 0.05, 0.20, 0.06 },
          { 0.12, 0.13, 0.19, 0.32, 0.03, 0.01, 0.05, 0.06, 0.07, 0.04, 0.06, 0.28 },
        };

        set_covariance(BKGCOV);
      }


    protected:
      void analysis_specific_reset() {

        for (auto& el : _numSR) { el.second = 0.;}

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_36invfb)


    //
    // Derived analysis class that does not make use of the SR covariance matrix
    //
    class Analysis_CMS_13TeV_2LEPsoft_36invfb_nocovar : public Analysis_CMS_13TeV_2LEPsoft_36invfb {

    public:
      Analysis_CMS_13TeV_2LEPsoft_36invfb_nocovar() {
        set_analysis_name("CMS_13TeV_2LEPsoft_36invfb_nocovar");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR1",  2.,  {_numSR["SR1"],  0.}, {3.5, 1.}));
        add_result(SignalRegionData("SR2",  15., {_numSR["SR2"],  0.}, {12, 2.3}));
        add_result(SignalRegionData("SR3",  19., {_numSR["SR3"],  0.}, {17, 2.4}));
        add_result(SignalRegionData("SR4",  18., {_numSR["SR4"],  0.}, {11, 2.}));
        add_result(SignalRegionData("SR5",  1.,  {_numSR["SR5"],  0.}, {1.6, 0.7}));
        add_result(SignalRegionData("SR6",  0.,  {_numSR["SR6"],  0.}, {3.5, 0.9}));
        add_result(SignalRegionData("SR7",  3.,  {_numSR["SR7"],  0.}, {2., 0.7}));
        add_result(SignalRegionData("SR8",  1.,  {_numSR["SR8"],  0.}, {0.51, 0.52}));
        add_result(SignalRegionData("SR9",  2.,  {_numSR["SR9"],  0.}, {1.4, 0.7}));
        add_result(SignalRegionData("SR10", 1.,  {_numSR["SR10"], 0.}, {1.5, 0.6}));
        add_result(SignalRegionData("SR11", 2.,  {_numSR["SR11"], 0.}, {1.5, 0.8}));
        add_result(SignalRegionData("SR12", 0.,  {_numSR["SR12"], 0.}, {1.2, 0.6}));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_36invfb_nocovar)


  }
}
