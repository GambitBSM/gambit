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

#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_2LEPsoft_36invfb : public HEPUtilsAnalysis {
    private:

      // Numbers passing cuts
      double _numSR1, _numSR2, _numSR3, _numSR4, _numSR5, _numSR6, _numSR7, _numSR8, _numSR9, _numSR10, _numSR11, _numSR12; 
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      size_t NCUTS;
      vector<double> cutFlowVectorCMS_150_130;
      // double xsecCMS_150_143;
      // double xsecCMS_150_130;

      // ofstream cutflowFile;

    public:

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      Analysis_CMS_13TeV_2LEPsoft_36invfb() {

        set_analysis_name("CMS_13TeV_2LEPsoft_36invfb");
        set_luminosity(35.9);

        _numSR1=0;
        _numSR2=0;
        _numSR3=0;
        _numSR4=0;
        _numSR5=0; 
        _numSR6=0;
        _numSR7=0; 
        _numSR8=0;
        _numSR9=0;
        _numSR10=0; 
        _numSR11=0;
        _numSR12=0; 

        NCUTS=14;
        // xsecCMS_150_143=5180.;
        // xsecCMS_150_130=5180.;

        for (size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVectorCMS_150_130.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }


      void analyze(const HEPUtils::Event* event) {
        HEPUtilsAnalysis::analyze(event);
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
          if (m_ll>4. && m_ll<10.)_numSR1 += 0.65;
          if (m_ll>10. && m_ll<20.)_numSR2 += 0.65;
          if (m_ll>20. && m_ll<30.)_numSR3 += 0.65;
          if (m_ll>30. && m_ll<50.)_numSR4 += 0.65;
        }
        if (preselection && met>200. && met<250.) {
          if (m_ll>4. && m_ll<10.)_numSR5++;
          if (m_ll>10. && m_ll<20.)_numSR6++;
          if (m_ll>20. && m_ll<30.)_numSR7++;
          if (m_ll>30. && m_ll<50.)_numSR8++;
        }
        if (preselection && met>250.) {
          if (m_ll>4. && m_ll<10.)_numSR9++;
          if (m_ll>10. && m_ll<20.)_numSR10++;
          if (m_ll>20. && m_ll<30.)_numSR11++;
          if (m_ll>30. && m_ll<50.)_numSR12++;
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


      void add(BaseAnalysis* other) {
        // The base class add function handles the signal region vector and total # events.
        
        HEPUtilsAnalysis::add(other);

        Analysis_CMS_13TeV_2LEPsoft_36invfb* specificOther
                = dynamic_cast<Analysis_CMS_13TeV_2LEPsoft_36invfb*>(other);

        // Here we will add the subclass member variables:
        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j = 0; j < NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _numSR1 += specificOther->_numSR1;
        _numSR2 += specificOther->_numSR2;
        _numSR3 += specificOther->_numSR3;
        _numSR4 += specificOther->_numSR4;
        _numSR5 += specificOther->_numSR5;
        _numSR6 += specificOther->_numSR6;
        _numSR7 += specificOther->_numSR7;
        _numSR8 += specificOther->_numSR8;
        _numSR9 += specificOther->_numSR5;
        _numSR10 += specificOther->_numSR6;
        _numSR11 += specificOther->_numSR7;
        _numSR12 += specificOther->_numSR8;
      }


      void collect_results() {


        // string path = "ColliderBit/results/cutflow_";
        // path.append(analysis_name());
        // path.append(".txt");
        // cutflowFile.open(path.c_str());

 //        if (analysis_name().find("150_143") != string::npos) {
 //          cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $W^{*}/Z^{*}, [\\tilde{\\chi}_{2}^{0}\\tilde{\\chi}_{1}^{\\pm},\\tilde{\\chi}_{1}^{0}]: [150,143] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
 //          cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
 //          cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsecCMS_150_143<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<<xsec()/xsecCMS_150_143<<" & 1\\\\ \\hline"<<endl;
 //          cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
 //          for (size_t i=0; i<NCUTS; i++) {
 //            cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_150_143[i]<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_150_143[i]<<"&"<<setprecision(4)<<(xsecCMS_150_143/xsec())*cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_150_143[i]<<"\\\\"<< endl;
 //          }
 //          cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
 //          for (size_t i=1; i<NCUTS; i++) {
 //            cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_150_143[i]*100./cutFlowVectorCMS_150_143[1]<<"&"<<setprecision(4)<<cutFlowVector[i]*100./cutFlowVector[1]<<"& - & -\\\\"<< endl;
 //          }
 //          cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

 //        if (analysis_name().find("150_130") != string::npos) {
 //          cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $W^{*}/Z^{*}, [\\tilde{\\chi}_{2}^{0}\\tilde{\\chi}_{1}^{\\pm},\\tilde{\\chi}_{1}^{0}]: [150,130] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
 //          cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
 //          cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsecCMS_150_130<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<<xsec()/xsecCMS_150_130<<" & 1\\\\ \\hline"<<endl;
 //          cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
 //          for (size_t i=0; i<NCUTS; i++) {
 //            cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_150_130[i]<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_150_130[i]<<"&"<<setprecision(4)<<(xsecCMS_150_130/xsec())*cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_150_130[i]<<"\\\\"<< endl;
 //          }
 //          cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
 //          for (size_t i=1; i<NCUTS; i++) {
 //            cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_150_130[i]*100./cutFlowVectorCMS_150_130[1]<<"&"<<setprecision(4)<<cutFlowVector[i]*100./cutFlowVector[1]<<"& - & -\\\\"<< endl;
 //          }
 //          cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
        // }

 //        cutflowFile.close();

        // DEBUG
//        double L = 33.2;
//        double xsec = 5180.;
//        cout << "DEBUG:" << endl;
//        for (size_t i=0; i<NCUTS; i++)
//        {
//          double CMS_abs = cutFlowVectorCMS_150_130[i];
//          //double CMS_abs = cutFlowVectorCMS_150_143[i];
//          double GAMBIT_abs = cutFlowVector[i];
//          
//          double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];
//          if(i>6) eff *= 0.65;
//          // double eff = (double)cutFlowVector[i] / 100000.;
//
//          double GAMBIT_scaled = eff * xsec * L;
//
//          double ratio = GAMBIT_scaled/CMS_abs;
//          cout << "DEBUG 1: i: " << i << ":   " << setprecision(4) << CMS_abs << "\t" << GAMBIT_scaled << "\t" << "\t" << ratio << "\t\t" << cutFlowVector_str[i] << endl;
//        }
//        cout << "DEBUG:" << endl;
        

        // Signal region info for the covariance matrix
        static const size_t SR_size_cov = 12;
        const int SR_labels_cov[SR_size_cov] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        const double SR_nums_cov[SR_size_cov] = {
          _numSR1, _numSR2, _numSR3, _numSR4, _numSR5,  _numSR6, 
          _numSR7, _numSR8, _numSR9, _numSR10, _numSR11, _numSR12,
        };

        // Observed event counts
        static const double OBSNUM[SR_size_cov] = {
          2., 15., 19., 18., 1., 0., 3., 1., 2., 1., 2., 0., 
        };

        // Background estimates
        static const double BKGNUM[SR_size_cov] = {
          3.5, 12., 17., 11., 1.6, 3.5, 2., 0.51, 1.4, 1.5, 1.5, 1.2,
        };
        
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR[SR_size_cov] = {
          1., 2.3, 2.4, 2., 0.7, 0.9, 0.7, 0.52, 0.7, 0.6, 0.8, 0.6, 
        };

        for (size_t ibin = 0; ibin < SR_size_cov; ++ibin) 
        {
          stringstream ss; ss << "SR-" << SR_labels_cov[ibin];
          add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {SR_nums_cov[ibin], 0.}, {BKGNUM[ibin], BKGERR[ibin]}));
        }

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



        // //Now fill a results object with the results for each SR
        // SignalRegionData results_SR1;
        // results_SR1.sr_label = "SR1";
        // results_SR1.n_observed = 2.;
        // results_SR1.n_background = 3.5; 
        // results_SR1.background_sys = 1.;
        // results_SR1.signal_sys = 0.; 
        // results_SR1.n_signal = _numSR1;
        // add_result(results_SR1);

        // SignalRegionData results_SR2;
        // results_SR2.sr_label = "SR1";
        // results_SR2.n_observed = 15.;
        // results_SR2.n_background = 12.;
        // results_SR2.background_sys = 2.3;
        // results_SR2.signal_sys = 0.;
        // results_SR2.n_signal = _numSR2;
        // add_result(results_SR2);

        // SignalRegionData results_SR3;
        // results_SR3.sr_label = "SR3";
        // results_SR3.n_observed = 19.;
        // results_SR3.n_background = 17.;
        // results_SR3.background_sys = 2.4;
        // results_SR3.signal_sys = 0.;
        // results_SR3.n_signal = _numSR3;
        // add_result(results_SR3);

        // SignalRegionData results_SR4;
        // results_SR4.sr_label = "SR4";
        // results_SR4.n_observed = 18.;
        // results_SR4.n_background = 11.;
        // results_SR4.background_sys = 2.;
        // results_SR4.signal_sys = 0.;
        // results_SR4.n_signal = _numSR4;
        // add_result(results_SR4);

        // SignalRegionData results_SR5;
        // results_SR5.sr_label = "SR5";
        // results_SR5.n_observed = 1.;
        // results_SR5.n_background = 1.6;
        // results_SR5.background_sys = 0.7;
        // results_SR5.signal_sys = 0.;
        // results_SR5.n_signal = _numSR5;
        // add_result(results_SR5);

        // SignalRegionData results_SR6;
        // results_SR6.sr_label = "SR6";
        // results_SR6.n_observed = 0.;
        // results_SR6.n_background = 3.5;
        // results_SR6.background_sys = 0.9;
        // results_SR6.signal_sys = 0.;
        // results_SR6.n_signal = _numSR6;
        // add_result(results_SR6);

        // SignalRegionData results_SR7;
        // results_SR7.sr_label = "SR7";
        // results_SR7.n_observed = 3.;
        // results_SR7.n_background = 2.;
        // results_SR7.background_sys = 0.7;
        // results_SR7.signal_sys = 0.;
        // results_SR7.n_signal = _numSR7;
        // add_result(results_SR7);

        // SignalRegionData results_SR8;
        // results_SR8.sr_label = "SR8";
        // results_SR8.n_observed = 1.;
        // results_SR8.n_background = 0.51;
        // results_SR8.background_sys = 0.52;
        // results_SR8.signal_sys = 0.;
        // results_SR8.n_signal = _numSR8;
        // add_result(results_SR8);

        // SignalRegionData results_SR9;
        // results_SR9.sr_label = "SR9";
        // results_SR9.n_observed = 2.;
        // results_SR9.n_background = 1.4;
        // results_SR9.background_sys = 0.7;
        // results_SR9.signal_sys = 0.;
        // results_SR9.n_signal = _numSR9;
        // add_result(results_SR9);

        // SignalRegionData results_SR10;
        // results_SR10.sr_label = "SR10";
        // results_SR10.n_observed = 1.;
        // results_SR10.n_background = 1.5;
        // results_SR10.background_sys = 0.6;
        // results_SR10.signal_sys = 0.;
        // results_SR10.n_signal = _numSR10;
        // add_result(results_SR10);

        // SignalRegionData results_SR11;
        // results_SR11.sr_label = "SR11";
        // results_SR11.n_observed = 2.;
        // results_SR11.n_background = 1.5;
        // results_SR11.background_sys = 0.8;
        // results_SR11.signal_sys = 0.;
        // results_SR11.n_signal = _numSR11;
        // add_result(results_SR11);

        // SignalRegionData results_SR12;
        // results_SR12.sr_label = "SR12";
        // results_SR12.n_observed = 0.;
        // results_SR12.n_background = 1.2;
        // results_SR12.background_sys = 0.6;
        // results_SR12.signal_sys = 0.;
        // results_SR12.n_signal = _numSR12;
        // add_result(results_SR12);

      }


    protected:
      void clear() {
        _numSR1=0;
        _numSR2=0;
        _numSR3=0;
        _numSR4=0;
        _numSR5=0; 
        _numSR6=0;
        _numSR7=0; 
        _numSR8=0;
        _numSR9=0;
        _numSR10=0; 
        _numSR11=0;
        _numSR12=0; 
        
        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_36invfb)

  }
}
